// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <auth/command.h>
#include <auth/auth_log.h>
#include <auth/auth_srv.h>
#include <auth/datasrc_clients_mgr.h>

#include <cc/data.h>
#include <datasrc/client_list.h>
#include <config/ccsession.h>
#include <exceptions/exceptions.h>
#include <dns/rrclass.h>

#include <string>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <sys/types.h>
#include <unistd.h>

using boost::scoped_ptr;
using namespace isc::auth;
using namespace isc::config;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::dns;
using namespace std;

namespace {
/// An exception that is thrown if an error occurs while handling a command
/// on an \c AuthSrv object.
///
/// Currently it's only used internally, since \c execAuthServerCommand()
/// (which is the only interface to this module) catches all \c isc::
/// exceptions and converts them.
class AuthCommandError : public isc::Exception {
public:
    AuthCommandError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// An abstract base class that represents a single command identifier
/// for an \c AuthSrv object.
///
/// Each of derived classes of \c AuthCommand, which are hidden inside the
/// implementation, corresponds to a command executed on \c AuthSrv, such as
/// "shutdown".  The derived class is responsible to execute the corresponding
/// command with the given command arguments (if any) in its \c exec()
/// method.
///
/// In the initial implementation the existence of the command classes is
/// hidden inside the implementation since the only public interface is
/// \c execAuthServerCommand(), which does not expose this class.
/// In future, we may want to make this framework more dynamic, i.e.,
/// registering specific derived classes run time outside of this
/// implementation.  If and when that happens the definition of the abstract
/// class will be published.
class AuthCommand {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:
    AuthCommand(const AuthCommand& source);
    AuthCommand& operator=(const AuthCommand& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    AuthCommand() {}
public:
    /// The destructor.
    virtual ~AuthCommand() {}
    //@}

    /// Execute a single control command.
    ///
    /// Specific derived methods can throw exceptions.  When called via
    /// \c execAuthServerCommand(), all BIND 10 exceptions are caught
    /// and converted into an error code.
    /// The derived method may also throw an exception of class
    /// \c AuthCommandError when it encounters an internal error, such as
    /// semantics error on the command arguments.
    ///
    /// This method should return the execution result in the form of
    /// \c ConstElementPtr.  It will be transparently used as the return
    /// value from the command handler called from the corresponding
    /// \c CCSession object.  For a successful completion of the command,
    /// it should suffice to return the return value of
    /// \c isc::config::createAnswer() with no argument.
    ///
    /// \param server The \c AuthSrv object on which the command is executed.
    /// \param args Command specific argument.
    /// \return Command execution result.
    virtual ConstElementPtr exec(AuthSrv& server,
                                 isc::data::ConstElementPtr args) = 0;
};

// Handle the "shutdown" command. An optional parameter "pid" is used to
// see if it is really for our instance.
class ShutdownCommand : public AuthCommand {
public:
    virtual ConstElementPtr exec(AuthSrv& server,
                                 isc::data::ConstElementPtr args)
    {
        // Is the pid argument provided?
        if (args && args->contains("pid")) {
            // If it is, we check it is the same as our PID

            // This might throw in case the type is not an int, but that's
            // OK, as it'll get converted to an error on higher level.
            const int pid(args->get("pid")->intValue());
            const pid_t my_pid(getpid());
            if (my_pid != pid) {
                // It is not for us
                //
                // Note that this is completely expected situation, if
                // there are multiple instances of the server running and
                // another instance is being shut down, we get the message
                // too, due to the multicast nature of our message bus.
                return (createAnswer());
            }
        }
        LOG_DEBUG(auth_logger, DBG_AUTH_SHUT, AUTH_SHUTDOWN);
        server.stop();
        return (createAnswer());
    }
};

// Handle the "getstats" command.  The argument is a list.
class GetStatsCommand : public AuthCommand {
public:
    virtual ConstElementPtr exec(AuthSrv& server, isc::data::ConstElementPtr) {
        return (createAnswer(0, server.getStatistics()));
    }
};

class StartDDNSForwarderCommand : public AuthCommand {
public:
    virtual ConstElementPtr exec(AuthSrv& server,
                                 isc::data::ConstElementPtr) {
        server.createDDNSForwarder();
        return (createAnswer());
    }
};

class StopDDNSForwarderCommand : public AuthCommand {
public:
    virtual ConstElementPtr exec(AuthSrv& server,
                                 isc::data::ConstElementPtr) {
        server.destroyDDNSForwarder();
        return (createAnswer());
    }
};

// Handle the "loadzone" command.
class LoadZoneCommand : public AuthCommand {
public:
    virtual ConstElementPtr exec(AuthSrv& server,
                                 isc::data::ConstElementPtr args)
    {
        server.getDataSrcClientsMgr().loadZone(args);
        return (createAnswer());
    }
};

// The factory of command objects.
AuthCommand*
createAuthCommand(const string& command_id) {
    // For the initial implementation we use a naive if-else blocks
    // (see also createAuthConfigParser())
    if (command_id == "shutdown") {
        return (new ShutdownCommand());
    } else if (command_id == "getstats") {
        return (new GetStatsCommand());
    } else if (command_id == "loadzone") {
        return (new LoadZoneCommand());
    } else if (command_id == "start_ddns_forwarder") {
        return (new StartDDNSForwarderCommand());
    } else if (command_id == "stop_ddns_forwarder") {
        return (new StopDDNSForwarderCommand());
    } else if (false && command_id == "_throw_exception") {
        // This is for testing purpose only and should not appear in the
        // actual configuration syntax.
        // XXX: ModuleCCSession doesn't seem to validate commands (unlike
        // config), so we should disable this case for now.
        throw runtime_error("throwing for test");
    }

    isc_throw(AuthCommandError, "Unknown command identifier: " << command_id);
}
} // end of unnamed namespace

ConstElementPtr
execAuthServerCommand(AuthSrv& server, const string& command_id,
                      ConstElementPtr args)
{
    LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_RECEIVED_COMMAND).arg(command_id);
    try {
        return (scoped_ptr<AuthCommand>(
                    createAuthCommand(command_id))->exec(server, args));
    } catch (const isc::Exception& ex) {
        LOG_ERROR(auth_logger, AUTH_COMMAND_FAILED).arg(command_id)
                                                   .arg(ex.what());
        return (createAnswer(1, ex.what()));
    }
}
