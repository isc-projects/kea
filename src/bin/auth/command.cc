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

#include <string>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/rrclass.h>

#include <cc/data.h>

#include <datasrc/memory_datasrc.h>

#include <config/ccsession.h>

#include <auth/auth_log.h>
#include <auth/auth_srv.h>
#include <auth/command.h>

using boost::scoped_ptr;
using boost::shared_ptr;
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
    /// \param server The \c AuthSrv object on which the command is executed.
    /// \param args Command specific argument.
    virtual void exec(AuthSrv& server, isc::data::ConstElementPtr args) = 0;
};

// Handle the "shutdown" command.  No argument is assumed.
class ShutdownCommand : public AuthCommand {
public:
    virtual void exec(AuthSrv& server, isc::data::ConstElementPtr) {
        server.stop();
    }
};

// Handle the "sendstats" command.  No argument is assumed.
class SendStatsCommand : public AuthCommand {
public:
    virtual void exec(AuthSrv& server, isc::data::ConstElementPtr) {
        LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_RECEIVED_SENDSTATS);
        server.submitStatistics();
    }
};

// Handle the "loadzone" command.
class LoadZoneCommand : public AuthCommand {
public:
    virtual void exec(AuthSrv& server, isc::data::ConstElementPtr args) {
        // parse and validate the args.
        if (!validate(server, args)) {
            return;
        }

        // Load a new zone and replace the current zone with the new one.
        // TODO: eventually this should be incremental or done in some way
        // that doesn't block other server operations.
        // TODO: we may (should?) want to check the "last load time" and
        // the timestamp of the file and skip loading if the file isn't newer.
        shared_ptr<MemoryZone> newzone(new MemoryZone(oldzone->getClass(),
                                                      oldzone->getOrigin()));
        newzone->load(oldzone->getFileName());
        oldzone->swap(*newzone);
        LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_LOAD_ZONE)
                  .arg(newzone->getOrigin()).arg(newzone->getClass());
    }

private:
    shared_ptr<MemoryZone> oldzone; // zone to be updated with the new file.

    // A helper private method to parse and validate command parameters.
    // On success, it sets 'oldzone' to the zone to be updated.
    // It returns true if everything is okay; and false if the command is
    // valid but there's no need for further process.
    bool validate(AuthSrv& server, isc::data::ConstElementPtr args) {
        if (args == NULL) {
            isc_throw(AuthCommandError, "Null argument");
        }

        // In this initial implementation, we assume memory data source
        // for class IN by default.
        ConstElementPtr datasrc_elem = args->get("datasrc");
        if (datasrc_elem) {
            if (datasrc_elem->stringValue() == "sqlite3") {
                LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_SQLITE3);
                return (false);
            } else if (datasrc_elem->stringValue() != "memory") {
                // (note: at this point it's guaranteed that datasrc_elem
                // is of string type)
                isc_throw(AuthCommandError,
                          "Data source type " << datasrc_elem->stringValue()
                          << " is not supported");
            }
        }

        ConstElementPtr class_elem = args->get("class");
        const RRClass zone_class = class_elem ?
            RRClass(class_elem->stringValue()) : RRClass::IN();

        AuthSrv::MemoryDataSrcPtr datasrc(server.getMemoryDataSrc(zone_class));
        if (datasrc == NULL) {
            isc_throw(AuthCommandError, "Memory data source is disabled");
        }

        ConstElementPtr origin_elem = args->get("origin");
        if (!origin_elem) {
            isc_throw(AuthCommandError, "Zone origin is missing");
        }
        const Name origin(origin_elem->stringValue());

        // Get the current zone
        const MemoryDataSrc::FindResult result = datasrc->findZone(origin);
        if (result.code != result::SUCCESS) {
            isc_throw(AuthCommandError, "Zone " << origin <<
                      " is not found in data source");
        }

        oldzone = boost::dynamic_pointer_cast<MemoryZone>(result.zone);

        return (true);
    }
};

// The factory of command objects.
AuthCommand*
createAuthCommand(const string& command_id) {
    // For the initial implementation we use a naive if-else blocks
    // (see also createAuthConfigParser())
    if (command_id == "shutdown") {
        return (new ShutdownCommand());
    } else if (command_id == "sendstats") {
        return (new SendStatsCommand());
    } else if (command_id == "loadzone") {
        return (new LoadZoneCommand());
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
        scoped_ptr<AuthCommand>(createAuthCommand(command_id))->exec(server,
                                                                     args);
    } catch (const isc::Exception& ex) {
        LOG_ERROR(auth_logger, AUTH_COMMAND_FAILED).arg(command_id)
                                                   .arg(ex.what());
        return (createAnswer(1, ex.what()));
    }

    return (createAnswer());
}
