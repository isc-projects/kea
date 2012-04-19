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

#include <cc/data.h>
#include <datasrc/memory_datasrc.h>
#include <datasrc/factory.h>
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
    /// \param server The \c AuthSrv object on which the command is executed.
    /// \param args Command specific argument.
    virtual void exec(AuthSrv& server, isc::data::ConstElementPtr args) = 0;
};

// Handle the "shutdown" command. An optional parameter "pid" is used to
// see if it is really for our instance.
class ShutdownCommand : public AuthCommand {
public:
    virtual void exec(AuthSrv& server, isc::data::ConstElementPtr args) {
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
                return;
            }
        }
        LOG_DEBUG(auth_logger, DBG_AUTH_SHUT, AUTH_SHUTDOWN);
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

        const ConstElementPtr zone_config = getZoneConfig(server);

        // Load a new zone and replace the current zone with the new one.
        // TODO: eventually this should be incremental or done in some way
        // that doesn't block other server operations.
        // TODO: we may (should?) want to check the "last load time" and
        // the timestamp of the file and skip loading if the file isn't newer.
        const ConstElementPtr type(zone_config->get("filetype"));
        boost::shared_ptr<InMemoryZoneFinder> zone_finder(
            new InMemoryZoneFinder(old_zone_finder_->getClass(),
                                   old_zone_finder_->getOrigin()));
        if (type && type->stringValue() == "sqlite3") {
            scoped_ptr<DataSourceClientContainer>
                container(new DataSourceClientContainer("sqlite3",
                                                        Element::fromJSON(
                    "{\"database_file\": \"" +
                    zone_config->get("file")->stringValue() + "\"}")));
            zone_finder->load(*container->getInstance().getIterator(
                old_zone_finder_->getOrigin()));
        } else {
            zone_finder->load(old_zone_finder_->getFileName());
        }
        old_zone_finder_->swap(*zone_finder);
        LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_LOAD_ZONE)
                  .arg(zone_finder->getOrigin()).arg(zone_finder->getClass());
    }

private:
    // zone finder to be updated with the new file.
    boost::shared_ptr<InMemoryZoneFinder> old_zone_finder_;

    // A helper private method to parse and validate command parameters.
    // On success, it sets 'old_zone_finder_' to the zone to be updated.
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
        const RRClass zone_class =
            class_elem ? RRClass(class_elem->stringValue()) : RRClass::IN();

        AuthSrv::InMemoryClientPtr datasrc(server.
                                           getInMemoryClient(zone_class));
        if (datasrc == NULL) {
            isc_throw(AuthCommandError, "Memory data source is disabled");
        }

        ConstElementPtr origin_elem = args->get("origin");
        if (!origin_elem) {
            isc_throw(AuthCommandError, "Zone origin is missing");
        }
        const Name origin = Name(origin_elem->stringValue());

        // Get the current zone
        const InMemoryClient::FindResult result = datasrc->findZone(origin);
        if (result.code != result::SUCCESS) {
            isc_throw(AuthCommandError, "Zone " << origin <<
                      " is not found in data source");
        }

        old_zone_finder_ = boost::dynamic_pointer_cast<InMemoryZoneFinder>(
            result.zone_finder);

        return (true);
    }

    ConstElementPtr getZoneConfig(const AuthSrv &server) {
        if (!server.getConfigSession()) {
            // FIXME: This is a hack to make older tests pass. We should
            // update these tests as well sometime and remove this hack.
            // (note that under normal situation, the
            // server.getConfigSession() does not return NULL)

            // We provide an empty map, which means no configuration --
            // defaults.
            return (ConstElementPtr(new MapElement()));
        }

        // Find the config corresponding to the zone.
        // We expect the configuration to be valid, as we have it and we
        // accepted it before, therefore it must be validated.
        const ConstElementPtr config(server.getConfigSession()->
                                     getValue("datasources"));
        ConstElementPtr zone_list;
        // Unfortunately, we need to walk the list to find the correct data
        // source.
        // TODO: Make it named sets. These lists are uncomfortable.
        for (size_t i(0); i < config->size(); ++i) {
            // We use the getValue to get defaults as well
            const ConstElementPtr dsrc_config(config->get(i));
            const ConstElementPtr class_config(dsrc_config->get("class"));
            const string class_type(class_config ?
                                    class_config->stringValue() : "IN");
            // It is in-memory and our class matches.
            // FIXME: Is it allowed to have two datasources for the same
            // type and class at once? It probably would not work now
            // anyway and we may want to change the configuration of
            // datasources somehow.
            if (dsrc_config->get("type")->stringValue() == "memory" &&
                RRClass(class_type) == old_zone_finder_->getClass()) {
                zone_list = dsrc_config->get("zones");
                break;
            }
        }

        if (!zone_list) {
            isc_throw(AuthCommandError,
                      "Corresponding data source configuration was not found");
        }

        // Now we need to walk the zones and find the correct one.
        for (size_t i(0); i < zone_list->size(); ++i) {
            const ConstElementPtr zone_config(zone_list->get(i));
            if (Name(zone_config->get("origin")->stringValue()) ==
                old_zone_finder_->getOrigin()) {
                // The origins are the same, so we consider this config to be
                // for the zone.
                return (zone_config);
            }
        }

        isc_throw(AuthCommandError,
                  "Corresponding zone configuration was not found");
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
