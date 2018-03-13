// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/database_connection.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6to4_ipc.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/parser_context.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <cfgrpt/config_report.h>
#include <signal.h>
#include <sstream>

using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::stats;
using namespace std;

namespace {

// Name of the file holding server identifier.
static const char* SERVER_DUID_FILE = "kea-dhcp6-serverid";

/// @brief Signals handler for DHCPv6 server.
///
/// This signal handler handles the following signals received by the DHCPv6
/// server process:
/// - SIGHUP - triggers server's dynamic reconfiguration.
/// - SIGTERM - triggers server's shut down.
/// - SIGINT - triggers server's shut down.
///
/// @param signo Signal number received.
void signalHandler(int signo) {
    // SIGHUP signals a request to reconfigure the server.
    if (signo == SIGHUP) {
        ControlledDhcpv6Srv::processCommand("config-reload",
                                            ConstElementPtr());
    } else if ((signo == SIGTERM) || (signo == SIGINT)) {
        ControlledDhcpv6Srv::processCommand("shutdown",
                                            ConstElementPtr());
    }
}

}

namespace isc {
namespace dhcp {

ControlledDhcpv6Srv* ControlledDhcpv6Srv::server_ = NULL;

/// @brief Configure DHCPv6 server using the configuration file specified.
///
/// This function is used to both configure the DHCP server on its startup
/// and dynamically reconfigure the server when SIGHUP signal is received.
///
/// It fetches DHCPv6 server's configuration from the 'Dhcp6' section of
/// the JSON configuration file.
///
/// @param file_name Configuration file location.
/// @return status of the command
ConstElementPtr
ControlledDhcpv6Srv::loadConfigFile(const std::string& file_name) {
    // This is a configuration backend implementation that reads the
    // configuration from a JSON file.

    isc::data::ConstElementPtr json;
    isc::data::ConstElementPtr dhcp6;
    isc::data::ConstElementPtr logger;
    isc::data::ConstElementPtr result;

    // Basic sanity check: file name must not be empty.
    try {
        if (file_name.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(isc::BadValue, "JSON configuration file not specified. Please "
                      "use -c command line option.");
        }

        // Read contents of the file and parse it as JSON
        Parser6Context parser;
        json = parser.parseFile(file_name, Parser6Context::PARSER_DHCP6);
        if (!json) {
            isc_throw(isc::BadValue, "no configuration found");
        }

        // Let's do sanity check before we call json->get() which
        // works only for map.
        if (json->getType() != isc::data::Element::map) {
            isc_throw(isc::BadValue, "Configuration file is expected to be "
                      "a map, i.e., start with { and end with } and contain "
                      "at least an entry called 'Dhcp6' that itself is a map. "
                      << file_name
                      << " is a valid JSON, but its top element is not a map."
                      " Did you forget to add { } around your configuration?");
        }

        // Use parsed JSON structures to configure the server
        result = ControlledDhcpv6Srv::processCommand("config-set", json);
        if (!result) {
            // Undetermined status of the configuration. This should never
            // happen, but as the configureDhcp6Server returns a pointer, it is
            // theoretically possible that it will return NULL.
            isc_throw(isc::BadValue, "undefined result of "
                      "processCommand(\"config-set\", json)");
        }

        // Now check is the returned result is successful (rcode=0) or not
        // (see @ref isc::config::parseAnswer).
        int rcode;
        isc::data::ConstElementPtr comment =
            isc::config::parseAnswer(rcode, result);
        if (rcode != 0) {
            string reason = comment ? comment->stringValue() :
                "no details available";
            isc_throw(isc::BadValue, reason);
        }
    }  catch (const std::exception& ex) {
        // If configuration failed at any stage, we drop the staging
        // configuration and continue to use the previous one.
        CfgMgr::instance().rollback();

        LOG_ERROR(dhcp6_logger, DHCP6_CONFIG_LOAD_FAIL)
            .arg(file_name).arg(ex.what());
        isc_throw(isc::BadValue, "configuration error using file '"
                  << file_name << "': " << ex.what());
    }

    return (result);
}


void
ControlledDhcpv6Srv::init(const std::string& file_name) {
    // Configure the server using JSON file.
    ConstElementPtr result = loadConfigFile(file_name);
    int rcode;
    ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
    if (rcode != 0) {
        string reason = comment ? comment->stringValue() :
            "no details available";
        isc_throw(isc::BadValue, reason);
    }

    // We don't need to call openActiveSockets() or startD2() as these
    // methods are called in processConfig() which is called by
    // processCommand("config-set", ...)

    // Set signal handlers. When the SIGHUP is received by the process
    // the server reconfiguration will be triggered. When SIGTERM or
    // SIGINT will be received, the server will start shutting down.
    signal_set_.reset(new isc::util::SignalSet(SIGINT, SIGHUP, SIGTERM));
    // Set the pointer to the handler function.
    signal_handler_ = signalHandler;
}

void ControlledDhcpv6Srv::cleanup() {
    // Nothing to do here. No need to disconnect from anything.
}


ConstElementPtr
ControlledDhcpv6Srv::commandShutdownHandler(const string&, ConstElementPtr) {
    if (ControlledDhcpv6Srv::server_) {
        ControlledDhcpv6Srv::server_->shutdown();
    } else {
        LOG_WARN(dhcp6_logger, DHCP6_NOT_RUNNING);
        ConstElementPtr answer = isc::config::createAnswer(1, "Shutdown failure.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0, "Shutting down.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandLibReloadHandler(const string&, ConstElementPtr) {
    /// @todo delete any stored CalloutHandles referring to the old libraries
    /// Get list of currently loaded libraries and reload them.
    HookLibsCollection loaded = HooksManager::getLibraryInfo();
    bool status = HooksManager::loadLibraries(loaded);
    if (!status) {
        LOG_ERROR(dhcp6_logger, DHCP6_HOOKS_LIBS_RELOAD_FAIL);
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 "Failed to reload hooks libraries.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Hooks libraries successfully reloaded.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigReloadHandler(const string&,
                                                ConstElementPtr /*args*/) {
    // Get configuration file name.
    std::string file = ControlledDhcpv6Srv::getInstance()->getConfigFile();
    try {
        LOG_INFO(dhcp6_logger, DHCP6_DYNAMIC_RECONFIGURATION).arg(file);
        return (loadConfigFile(file));
    } catch (const std::exception& ex) {
        // Log the unsuccessful reconfiguration. The reason for failure
        // should be already logged. Don't rethrow an exception so as
        // the server keeps working.
        LOG_ERROR(dhcp6_logger, DHCP6_DYNAMIC_RECONFIGURATION_FAIL)
            .arg(file);
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Config reload failed:" + string(ex.what())));
    }
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigGetHandler(const string&,
                                             ConstElementPtr /*args*/) {
    ConstElementPtr config = CfgMgr::instance().getCurrentCfg()->toElement();

    return (createAnswer(0, config));
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigWriteHandler(const string&, ConstElementPtr args) {
    string filename;

    if (args) {
        if (args->getType() != Element::map) {
            return (createAnswer(CONTROL_RESULT_ERROR, "Argument must be a map"));
        }
        ConstElementPtr filename_param = args->get("filename");
        if (filename_param) {
            if (filename_param->getType() != Element::string) {
                return (createAnswer(CONTROL_RESULT_ERROR,
                                     "passed parameter 'filename' is not a string"));
            }
            filename = filename_param->stringValue();
        }
    }

    if (filename.empty()) {
        // filename parameter was not specified, so let's use whatever we remember
        // from the command-line
        filename = getConfigFile();
    }

    if (filename.empty()) {
        return (createAnswer(CONTROL_RESULT_ERROR, "Unable to determine filename."
                             "Please specify filename explicitly."));
    }

    // Ok, it's time to write the file.
    size_t size = 0;
    try {
        size = writeConfigFile(filename);
    } catch (const isc::Exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, string("Error during write-config:")
                             + ex.what()));
    }
    if (size == 0) {
        return (createAnswer(CONTROL_RESULT_ERROR, "Error writing configuration to "
                             + filename));
    }

    // Ok, it's time to return the successful response.
    ElementPtr params = Element::createMap();
    params->set("size", Element::create(static_cast<long long>(size)));
    params->set("filename", Element::create(filename));

    return (createAnswer(CONTROL_RESULT_SUCCESS, "Configuration written to "
                         + filename + " successful", params));
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigSetHandler(const string&,
                                             ConstElementPtr args) {
    const int status_code = CONTROL_RESULT_ERROR;
    ConstElementPtr dhcp6;
    string message;

    // Command arguments are expected to be:
    // { "Dhcp6": { ... }, "Logging": { ... } }
    // The Logging component is technically optional. If it's not supplied
    // logging will revert to default logging.
    if (!args) {
        message = "Missing mandatory 'arguments' parameter.";
    } else {
        dhcp6 = args->get("Dhcp6");
        if (!dhcp6) {
            message = "Missing mandatory 'Dhcp6' parameter.";
        } else if (dhcp6->getType() != Element::map) {
            message = "'Dhcp6' parameter expected to be a map.";
        }
    }

    if (!message.empty()) {
        // Something is amiss with arguments, return a failure response.
        ConstElementPtr result = isc::config::createAnswer(status_code,
                                                           message);
        return (result);
    }

    // We are starting the configuration process so we should remove any
    // staging configuration that has been created during previous
    // configuration attempts.
    CfgMgr::instance().rollback();

    // Logging is a sibling element and must be parsed explicitly.
    // The call to configureLogger parses the given Logging element if
    // not null, into the staging config.  Note this does not alter the
    // current loggers, they remain in effect until we apply the
    // logging config below.  If no logging is supplied logging will
    // revert to default logging.
    Daemon::configureLogger(args->get("Logging"),
                            CfgMgr::instance().getStagingCfg());

    // Let's apply the new logging. We do it early, so we'll be able to print
    // out what exactly is wrong with the new socnfig in case of problems.
    CfgMgr::instance().getStagingCfg()->applyLoggingCfg();

    // Now we configure the server proper.
    ConstElementPtr result = processConfig(dhcp6);

    // If the configuration parsed successfully, apply the new logger
    // configuration and the commit the new configuration.  We apply
    // the logging first in case there's a configuration failure.
    int rcode = 0;
    isc::config::parseAnswer(rcode, result);
    if (rcode == CONTROL_RESULT_SUCCESS) {
        CfgMgr::instance().getStagingCfg()->applyLoggingCfg();

        // Use new configuration.
        CfgMgr::instance().commit();
    } else {
        // Ok, we applied the logging from the upcoming configuration, but
        // there were problems with the config. As such, we need to back off
        // and revert to the previous logging configuration.
        CfgMgr::instance().getCurrentCfg()->applyLoggingCfg();
    }

    return (result);
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigTestHandler(const string&,
                                              ConstElementPtr args) {
    const int status_code = CONTROL_RESULT_ERROR; // 1 indicates an error
    ConstElementPtr dhcp6;
    string message;

    // Command arguments are expected to be:
    // { "Dhcp6": { ... }, "Logging": { ... } }
    // The Logging component is technically optional. If it's not supplied
    // logging will revert to default logging.
    if (!args) {
        message = "Missing mandatory 'arguments' parameter.";
    } else {
        dhcp6 = args->get("Dhcp6");
        if (!dhcp6) {
            message = "Missing mandatory 'Dhcp6' parameter.";
        } else if (dhcp6->getType() != Element::map) {
            message = "'Dhcp6' parameter expected to be a map.";
        }
    }

    if (!message.empty()) {
        // Something is amiss with arguments, return a failure response.
        ConstElementPtr result = isc::config::createAnswer(status_code,
                                                           message);
        return (result);
    }

    // We are starting the configuration process so we should remove any
    // staging configuration that has been created during previous
    // configuration attempts.
    CfgMgr::instance().rollback();

    // Now we check the server proper.
    return (checkConfig(dhcp6));
}

ConstElementPtr
ControlledDhcpv6Srv::commandDhcpDisableHandler(const std::string&,
                                               ConstElementPtr args) {
    std::ostringstream message;
    int64_t max_period = 0;

    // Parse arguments to see if the 'max-period' parameter has been specified.
    if (args) {
        // Arguments must be a map.
        if (args->getType() != Element::map) {
            message << "arguments for the 'dhcp-disable' command must be a map";

        } else {
            ConstElementPtr max_period_element = args->get("max-period");
            // max-period is optional.
            if (max_period_element) {
                // It must be an integer, if specified.
                if (max_period_element->getType() != Element::integer) {
                    message << "'max-period' argument must be a number";

                } else {
                    // It must be positive integer.
                    max_period = max_period_element->intValue();
                    if (max_period <= 0) {
                        message << "'max-period' must be positive integer";
                    }

                    // The user specified that the DHCP service should resume not
                    // later than in max-period seconds. If the 'dhcp-enable' command
                    // is not sent, the DHCP service will resume automatically.
                    network_state_.delayedEnableAll(static_cast<unsigned>(max_period));
                }
            }
        }
    }

    // No error occurred, so let's disable the service.
    if (message.tellp() == 0) {
        network_state_.disableService();

        message << "DHCPv6 service disabled";
        if (max_period > 0) {
            message << " for " << max_period << " seconds";
        }
        // Success.
        return (config::createAnswer(CONTROL_RESULT_SUCCESS, message.str()));
    }

    // Failure.
    return (config::createAnswer(CONTROL_RESULT_ERROR, message.str()));
}

ConstElementPtr
ControlledDhcpv6Srv::commandDhcpEnableHandler(const std::string&, ConstElementPtr) {
    network_state_.enableService();
    return (config::createAnswer(CONTROL_RESULT_SUCCESS, "DHCP service successfully enabled"));
}

ConstElementPtr
ControlledDhcpv6Srv::commandVersionGetHandler(const string&, ConstElementPtr) {
    ElementPtr extended = Element::create(Dhcpv6Srv::getVersion(true));
    ElementPtr arguments = Element::createMap();
    arguments->set("extended", extended);
    ConstElementPtr answer = isc::config::createAnswer(0,
                                Dhcpv6Srv::getVersion(false),
                                arguments);
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandBuildReportHandler(const string&, ConstElementPtr) {
    ConstElementPtr answer =
        isc::config::createAnswer(0, isc::detail::getConfigReport());
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandLeasesReclaimHandler(const string&,
                                                 ConstElementPtr args) {
    int status_code = 1;
    string message;

    // args must be { "remove": <bool> }
    if (!args) {
        message = "Missing mandatory 'remove' parameter.";
    } else {
        ConstElementPtr remove_name = args->get("remove");
        if (!remove_name) {
            message = "Missing mandatory 'remove' parameter.";
        } else if (remove_name->getType() != Element::boolean) {
            message = "'remove' parameter expected to be a boolean.";
        } else {
            bool remove_lease = remove_name->boolValue();
            server_->alloc_engine_->reclaimExpiredLeases6(0, 0, remove_lease);
            status_code = 0;
            message = "Reclamation of expired leases is complete.";
        }
    }
    ConstElementPtr answer = isc::config::createAnswer(status_code, message);
    return (answer);
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::processCommand(const std::string& command,
                                    isc::data::ConstElementPtr args) {
    string txt = args ? args->str() : "(none)";

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_COMMAND_RECEIVED)
              .arg(command).arg(txt);

    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
          "Server object not initialized, can't process command '" +
          command + "', arguments: '" + txt + "'.");
        return (no_srv);
    }

    try {
        if (command == "shutdown") {
            return (srv->commandShutdownHandler(command, args));

        } else if (command == "libreload") {
            return (srv->commandLibReloadHandler(command, args));

        } else if (command == "config-reload") {
            return (srv->commandConfigReloadHandler(command, args));

        } else if (command == "config-set") {
            return (srv->commandConfigSetHandler(command, args));

        } else if (command == "config-get") {
            return (srv->commandConfigGetHandler(command, args));

        } else if (command == "config-test") {
            return (srv->commandConfigTestHandler(command, args));

        } else if (command == "dhcp-disable") {
            return (srv->commandDhcpDisableHandler(command, args));

        } else if (command == "dhcp-enable") {
            return (srv->commandDhcpEnableHandler(command, args));

        } else if (command == "version-get") {
            return (srv->commandVersionGetHandler(command, args));

        } else if (command == "build-report") {
            return (srv->commandBuildReportHandler(command, args));

        } else if (command == "leases-reclaim") {
            return (srv->commandLeasesReclaimHandler(command, args));

        } else if (command == "config-write") {
            return (srv->commandConfigWriteHandler(command, args));

        }

        return (isc::config::createAnswer(1, "Unrecognized command:"
                                          + command));

    } catch (const Exception& ex) {
        return (isc::config::createAnswer(1, "Error while processing command '"
                                          + command + "':" + ex.what()));
    }
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::processConfig(isc::data::ConstElementPtr config) {

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_RECEIVED)
              .arg(config->str());

    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(
            CONTROL_RESULT_ERROR,
            "Server object not initialized, can't process config.");
        return (no_srv);
    }

    ConstElementPtr answer = configureDhcp6Server(*srv, config);

    // Check that configuration was successful. If not, do not reopen sockets
    // and don't bother with DDNS stuff.
    try {
        int rcode = 0;
        isc::config::parseAnswer(rcode, answer);
        if (rcode != 0) {
            return (answer);
        }
    } catch (const std::exception& ex) {
        return (isc::config::createAnswer(1, "Failed to process configuration:"
                                          + string(ex.what())));
    }

    // Re-open lease and host database with new parameters.
    try {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
        cfg_db->setAppendedParameters("universe=6");
        cfg_db->createManagers(boost::bind(&ControlledDhcpv6Srv::dbLostCallback, srv, _1));
    } catch (const std::exception& ex) {
        return (isc::config::createAnswer(1, "Unable to open database: "
                                          + std::string(ex.what())));
    }

    // Regenerate server identifier if needed.
    try {
        const std::string duid_file = CfgMgr::instance().getDataDir() + "/" +
            std::string(SERVER_DUID_FILE);
        DuidPtr duid = CfgMgr::instance().getStagingCfg()->getCfgDUID()->create(duid_file);
        server_->serverid_.reset(new Option(Option::V6, D6O_SERVERID, duid->getDuid()));
        if (duid) {
            LOG_INFO(dhcp6_logger, DHCP6_USING_SERVERID)
                .arg(duid->toText())
                .arg(duid_file);
        }

    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "unable to configure server identifier: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Server will start DDNS communications if its enabled.
    try {
        srv->startD2();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "error starting DHCP_DDNS client "
                " after server reconfiguration: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Setup DHCPv4-over-DHCPv6 IPC
    try {
        Dhcp6to4Ipc::instance().open();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "error starting DHCPv4-over-DHCPv6 IPC "
               " after server reconfiguration: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. It is possible that this
    // operation will fail for some interfaces but the openSockets function
    // guards against exceptions and invokes a callback function to
    // log warnings. Since we allow that this fails for some interfaces there
    // is no need to rollback configuration if socket fails to open on any
    // of the interfaces.
    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET6, srv->getPort());

    // Install the timers for handling leases reclamation.
    try {
        CfgMgr::instance().getStagingCfg()->getCfgExpiration()->
            setupTimers(&ControlledDhcpv6Srv::reclaimExpiredLeases,
                        &ControlledDhcpv6Srv::deleteExpiredReclaimedLeases,
                        server_);

    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "unable to setup timers for periodically running the"
            " reclamation of the expired leases: "
            << ex.what() << ".";
        return (isc::config::createAnswer(1, err.str()));
    }

    // Finally, we can commit runtime option definitions in libdhcp++. This is
    // exception free.
    LibDHCP::commitRuntimeOptionDefs();

    return (answer);
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::checkConfig(isc::data::ConstElementPtr config) {

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_RECEIVED)
        .arg(config->str());

    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
            "Server object not initialized, can't process config.");
        return (no_srv);
    }

    return (configureDhcp6Server(*srv, config, true));
}

ControlledDhcpv6Srv::ControlledDhcpv6Srv(uint16_t port)
    : Dhcpv6Srv(port), io_service_(), timer_mgr_(TimerMgr::instance()) {
    if (server_) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv6Srv instance already.");
    }
    server_ = this; // remember this instance for use in callback

    // TimerMgr uses IO service to run asynchronous timers.
    TimerMgr::instance()->setIOService(getIOService());

    // CommandMgr uses IO service to run asynchronous socket operations.
    CommandMgr::instance().setIOService(getIOService());

    // These are the commands always supported by the DHCPv6 server.
    // Please keep the list in alphabetic order.
    CommandMgr::instance().registerCommand("build-report",
        boost::bind(&ControlledDhcpv6Srv::commandBuildReportHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-get",
        boost::bind(&ControlledDhcpv6Srv::commandConfigGetHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-reload",
        boost::bind(&ControlledDhcpv6Srv::commandConfigReloadHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-test",
        boost::bind(&ControlledDhcpv6Srv::commandConfigTestHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-write",
        boost::bind(&ControlledDhcpv6Srv::commandConfigWriteHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("dhcp-disable",
        boost::bind(&ControlledDhcpv6Srv::commandDhcpDisableHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("dhcp-enable",
        boost::bind(&ControlledDhcpv6Srv::commandDhcpEnableHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("leases-reclaim",
        boost::bind(&ControlledDhcpv6Srv::commandLeasesReclaimHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("libreload",
        boost::bind(&ControlledDhcpv6Srv::commandLibReloadHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-set",
        boost::bind(&ControlledDhcpv6Srv::commandConfigSetHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("shutdown",
        boost::bind(&ControlledDhcpv6Srv::commandShutdownHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("version-get",
        boost::bind(&ControlledDhcpv6Srv::commandVersionGetHandler, this, _1, _2));

    // Register statistic related commands
    CommandMgr::instance().registerCommand("statistic-get",
        boost::bind(&StatsMgr::statisticGetHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-get-all",
        boost::bind(&StatsMgr::statisticGetAllHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-reset",
        boost::bind(&StatsMgr::statisticResetHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-reset-all",
        boost::bind(&StatsMgr::statisticResetAllHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-remove",
        boost::bind(&StatsMgr::statisticRemoveHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-remove-all",
        boost::bind(&StatsMgr::statisticRemoveAllHandler, _1, _2));
}

void ControlledDhcpv6Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv6Srv::shutdown(); // Initiate DHCPv6 shutdown procedure.
}

ControlledDhcpv6Srv::~ControlledDhcpv6Srv() {
    try {
        cleanup();

        timer_mgr_->unregisterTimers();

        // Close the command socket (if it exists).
        CommandMgr::instance().closeCommandSocket();

        // Deregister any registered commands (please keep in alphabetic order)
        CommandMgr::instance().deregisterCommand("build-report");
        CommandMgr::instance().deregisterCommand("config-get");
        CommandMgr::instance().deregisterCommand("config-set");
        CommandMgr::instance().deregisterCommand("config-reload");
        CommandMgr::instance().deregisterCommand("config-test");
        CommandMgr::instance().deregisterCommand("config-write");
        CommandMgr::instance().deregisterCommand("dhcp-disable");
        CommandMgr::instance().deregisterCommand("dhcp-enable");
        CommandMgr::instance().deregisterCommand("leases-reclaim");
        CommandMgr::instance().deregisterCommand("libreload");
        CommandMgr::instance().deregisterCommand("shutdown");
        CommandMgr::instance().deregisterCommand("statistic-get");
        CommandMgr::instance().deregisterCommand("statistic-get-all");
        CommandMgr::instance().deregisterCommand("statistic-remove");
        CommandMgr::instance().deregisterCommand("statistic-remove-all");
        CommandMgr::instance().deregisterCommand("statistic-reset");
        CommandMgr::instance().deregisterCommand("statistic-reset-all");
        CommandMgr::instance().deregisterCommand("version-get");

    } catch (...) {
        // Don't want to throw exceptions from the destructor. The server
        // is shutting down anyway.
        ;
    }

    server_ = NULL; // forget this instance. There should be no callback anymore
                    // at this stage anyway.
}

void ControlledDhcpv6Srv::sessionReader(void) {
    // Process one asio event. If there are more events, iface_mgr will call
    // this callback more than once.
    if (server_) {
        server_->io_service_.run_one();
    }
}

void
ControlledDhcpv6Srv::reclaimExpiredLeases(const size_t max_leases,
                                          const uint16_t timeout,
                                          const bool remove_lease,
                                          const uint16_t max_unwarned_cycles) {
    server_->alloc_engine_->reclaimExpiredLeases6(max_leases, timeout,
                                                  remove_lease,
                                                  max_unwarned_cycles);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME);
}

void
ControlledDhcpv6Srv::deleteExpiredReclaimedLeases(const uint32_t secs) {
    server_->alloc_engine_->deleteExpiredReclaimedLeases6(secs);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME);
}

void
ControlledDhcpv6Srv::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
    bool reopened = false;

    // Re-open lease and host database with new parameters.
    try {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getCurrentCfg()->getCfgDbAccess();
        cfg_db->createManagers(boost::bind(&ControlledDhcpv6Srv::dbLostCallback, this, _1));
        reopened = true;
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_DB_RECONNECT_ATTEMPT_FAILED).arg(ex.what());
    }

    if (reopened) {
        // Cancel the timer.
        if (TimerMgr::instance()->isTimerRegistered("Dhcp6DbReconnectTimer")) {
            TimerMgr::instance()->cancel("Dhcp6DbReconnectTimer"); }

        // Set network state to service enabled
        network_state_.enableService();

        // Toss the reconnct control, we're done with it
        db_reconnect_ctl.reset();
    } else {
        if (!db_reconnect_ctl->checkRetries()) {
            LOG_ERROR(dhcp6_logger, DHCP6_DB_RECONNECT_RETRIES_EXHAUSTED)
            .arg(db_reconnect_ctl->maxRetries());
            shutdown();
            return;
        }

        LOG_INFO(dhcp6_logger, DHCP6_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        if (!TimerMgr::instance()->isTimerRegistered("Dhcp6DbReconnectTimer")) {
            TimerMgr::instance()->registerTimer("Dhcp6DbReconnectTimer",
                            boost::bind(&ControlledDhcpv6Srv::dbReconnect, this,
                            db_reconnect_ctl),
                            db_reconnect_ctl->retryInterval() * 1000,
                            asiolink::IntervalTimer::ONE_SHOT);
        }

        TimerMgr::instance()->setup("Dhcp6DbReconnectTimer");
    }
}

bool
ControlledDhcpv6Srv::dbLostCallback(ReconnectCtlPtr db_reconnect_ctl) {
    // Disable service until we recover
    network_state_.disableService();

    if (!db_reconnect_ctl) {
        // This shouldn't never happen
        LOG_ERROR(dhcp6_logger, DHCP6_DB_RECONNECT_NO_DB_CTL);
        return (false);
    }

    // If reconnect isn't enabled, log it and return false
    if (!db_reconnect_ctl->retriesLeft() ||
        !db_reconnect_ctl->retryInterval()) {
        LOG_INFO(dhcp6_logger, DHCP6_DB_RECONNECT_DISABLED)
            .arg(db_reconnect_ctl->retriesLeft())
            .arg(db_reconnect_ctl->retryInterval());
        return(false);
    }

    // Invoke reconnect method
    dbReconnect(db_reconnect_ctl);

    return(true);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
