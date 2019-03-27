// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4to6_ipc.h>
#include <dhcp4/parser_context.h>
#include <dhcp4/json_config_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_db_access.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <cfgrpt/config_report.h>
#include <signal.h>
#include <sstream>

using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::stats;
using namespace std;

namespace {

/// Structure that holds registered hook indexes.
struct CtrlDhcp4Hooks {
    int hooks_index_dhcp4_srv_configured_;

    /// Constructor that registers hook points for the DHCPv4 server.
    CtrlDhcp4Hooks() {
        hooks_index_dhcp4_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
    }

};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
CtrlDhcp4Hooks Hooks;

/// @brief Signals handler for DHCPv4 server.
///
/// This signal handler handles the following signals received by the DHCPv4
/// server process:
/// - SIGHUP - triggers server's dynamic reconfiguration.
/// - SIGTERM - triggers server's shut down.
/// - SIGINT - triggers server's shut down.
///
/// @param signo Signal number received.
void signalHandler(int signo) {
    // SIGHUP signals a request to reconfigure the server.
    if (signo == SIGHUP) {
        ControlledDhcpv4Srv::processCommand("config-reload",
                                            ConstElementPtr());
    } else if ((signo == SIGTERM) || (signo == SIGINT)) {
        ControlledDhcpv4Srv::processCommand("shutdown",
                                            ConstElementPtr());
    }
}

}

namespace isc {
namespace dhcp {

ControlledDhcpv4Srv* ControlledDhcpv4Srv::server_ = NULL;

void
ControlledDhcpv4Srv::init(const std::string& file_name) {
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

void ControlledDhcpv4Srv::cleanup() {
    // Nothing to do here. No need to disconnect from anything.
}

/// @brief Configure DHCPv4 server using the configuration file specified.
///
/// This function is used to both configure the DHCP server on its startup
/// and dynamically reconfigure the server when SIGHUP signal is received.
///
/// It fetches DHCPv4 server's configuration from the 'Dhcp4' section of
/// the JSON configuration file.
///
/// @param file_name Configuration file location.
/// @return status of the command
ConstElementPtr
ControlledDhcpv4Srv::loadConfigFile(const std::string& file_name) {
    // This is a configuration backend implementation that reads the
    // configuration from a JSON file.

    isc::data::ConstElementPtr json;
    isc::data::ConstElementPtr dhcp4;
    isc::data::ConstElementPtr logger;
    isc::data::ConstElementPtr result;

    // Basic sanity check: file name must not be empty.
    try {
        if (file_name.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(isc::BadValue, "JSON configuration file not specified."
                      " Please use -c command line option.");
        }

        // Read contents of the file and parse it as JSON
        Parser4Context parser;
        json = parser.parseFile(file_name, Parser4Context::PARSER_DHCP4);
        if (!json) {
            isc_throw(isc::BadValue, "no configuration found");
        }

        // Let's do sanity check before we call json->get() which
        // works only for map.
        if (json->getType() != isc::data::Element::map) {
            isc_throw(isc::BadValue, "Configuration file is expected to be "
                      "a map, i.e., start with { and end with } and contain "
                      "at least an entry called 'Dhcp4' that itself is a map. "
                      << file_name
                      << " is a valid JSON, but its top element is not a map."
                      " Did you forget to add { } around your configuration?");
        }

        // Use parsed JSON structures to configure the server
        result = ControlledDhcpv4Srv::processCommand("config-set", json);
        if (!result) {
            // Undetermined status of the configuration. This should never
            // happen, but as the configureDhcp4Server returns a pointer, it is
            // theoretically possible that it will return NULL.
            isc_throw(isc::BadValue, "undefined result of "
                      "processCommand(\"config-set\", json)");
        }

        // Now check is the returned result is successful (rcode=0) or not
        // (see @ref isc::config::parseAnswer).
        int rcode;
        ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
        if (rcode != 0) {
            string reason = comment ? comment->stringValue() :
                "no details available";
            isc_throw(isc::BadValue, reason);
        }
    }  catch (const std::exception& ex) {
        // If configuration failed at any stage, we drop the staging
        // configuration and continue to use the previous one.
        CfgMgr::instance().rollback();

        LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL)
            .arg(file_name).arg(ex.what());
        isc_throw(isc::BadValue, "configuration error using file '"
                  << file_name << "': " << ex.what());
    }

    return (result);
}


ConstElementPtr
ControlledDhcpv4Srv::commandShutdownHandler(const string&, ConstElementPtr) {
    if (ControlledDhcpv4Srv::getInstance()) {
        ControlledDhcpv4Srv::getInstance()->shutdown();
    } else {
        LOG_WARN(dhcp4_logger, DHCP4_NOT_RUNNING);
        ConstElementPtr answer = isc::config::createAnswer(1,
                                              "Shutdown failure.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0, "Shutting down.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::commandLibReloadHandler(const string&, ConstElementPtr) {

    /// @todo delete any stored CalloutHandles referring to the old libraries
    /// Get list of currently loaded libraries and reload them.
    HookLibsCollection loaded = HooksManager::getLibraryInfo();
    bool status = HooksManager::loadLibraries(loaded);
    if (!status) {
        LOG_ERROR(dhcp4_logger, DHCP4_HOOKS_LIBS_RELOAD_FAIL);
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 "Failed to reload hooks libraries.");
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(0,
                             "Hooks libraries successfully reloaded.");
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::commandConfigReloadHandler(const string&,
                                                ConstElementPtr /*args*/) {

    // Get configuration file name.
    std::string file = ControlledDhcpv4Srv::getInstance()->getConfigFile();
    try {
        LOG_INFO(dhcp4_logger, DHCP4_DYNAMIC_RECONFIGURATION).arg(file);
        return (loadConfigFile(file));
    } catch (const std::exception& ex) {
        // Log the unsuccessful reconfiguration. The reason for failure
        // should be already logged. Don't rethrow an exception so as
        // the server keeps working.
        LOG_ERROR(dhcp4_logger, DHCP4_DYNAMIC_RECONFIGURATION_FAIL)
            .arg(file);
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Config reload failed:" + string(ex.what())));
    }
}

ConstElementPtr
ControlledDhcpv4Srv::commandConfigGetHandler(const string&,
                                             ConstElementPtr /*args*/) {
    ConstElementPtr config = CfgMgr::instance().getCurrentCfg()->toElement();

    return (createAnswer(0, config));
}

ConstElementPtr
ControlledDhcpv4Srv::commandConfigWriteHandler(const string&,
                                               ConstElementPtr args) {
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
        filename = getConfigFile();
    }

    if (filename.empty()) {
        return (createAnswer(CONTROL_RESULT_ERROR, "Unable to determine filename."
                             "Please specify filename explicitly."));
    }

    // Ok, it's time to write the file.
    size_t size = 0;
    try {
        ConstElementPtr cfg = CfgMgr::instance().getCurrentCfg()->toElement();
        size = writeConfigFile(filename, cfg);
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
ControlledDhcpv4Srv::commandConfigSetHandler(const string&,
                                             ConstElementPtr args) {
    const int status_code = CONTROL_RESULT_ERROR; // 1 indicates an error
    ConstElementPtr dhcp4;
    string message;

    // Command arguments are expected to be:
    // { "Dhcp4": { ... }, "Logging": { ... } }
    // The Logging component is technically optional. If it's not supplied
    // logging will revert to default logging.
    if (!args) {
        message = "Missing mandatory 'arguments' parameter.";
    } else {
        dhcp4 = args->get("Dhcp4");
        if (!dhcp4) {
            message = "Missing mandatory 'Dhcp4' parameter.";
        } else if (dhcp4->getType() != Element::map) {
            message = "'Dhcp4' parameter expected to be a map.";
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
    ConstElementPtr result = processConfig(dhcp4);

    // If the configuration parsed successfully, apply the new logger
    // configuration and the commit the new configuration.  We apply
    // the logging first in case there's a configuration failure.
    int rcode = 0;
    isc::config::parseAnswer(rcode, result);
    if (rcode == 0) {
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
ControlledDhcpv4Srv::commandConfigTestHandler(const string&,
                                              ConstElementPtr args) {
    const int status_code = CONTROL_RESULT_ERROR; // 1 indicates an error
    ConstElementPtr dhcp4;
    string message;

    // Command arguments are expected to be:
    // { "Dhcp4": { ... }, "Logging": { ... } }
    // The Logging component is technically optional. If it's not supplied
    // logging will revert to default logging.
    if (!args) {
        message = "Missing mandatory 'arguments' parameter.";
    } else {
        dhcp4 = args->get("Dhcp4");
        if (!dhcp4) {
            message = "Missing mandatory 'Dhcp4' parameter.";
        } else if (dhcp4->getType() != Element::map) {
            message = "'Dhcp4' parameter expected to be a map.";
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
    return (checkConfig(dhcp4));
}

ConstElementPtr
ControlledDhcpv4Srv::commandDhcpDisableHandler(const std::string&,
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
                    network_state_->delayedEnableAll(static_cast<unsigned>(max_period));
                }
            }
        }
    }

    // No error occurred, so let's disable the service.
    if (message.tellp() == 0) {
        network_state_->disableService();

        message << "DHCPv4 service disabled";
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
ControlledDhcpv4Srv::commandDhcpEnableHandler(const std::string&, ConstElementPtr) {
    network_state_->enableService();
    return (config::createAnswer(CONTROL_RESULT_SUCCESS, "DHCP service successfully enabled"));
}

ConstElementPtr
ControlledDhcpv4Srv::commandVersionGetHandler(const string&, ConstElementPtr) {
    ElementPtr extended = Element::create(Dhcpv4Srv::getVersion(true));
    ElementPtr arguments = Element::createMap();
    arguments->set("extended", extended);
    ConstElementPtr answer = isc::config::createAnswer(0,
                                Dhcpv4Srv::getVersion(false),
                                arguments);
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::commandBuildReportHandler(const string&,
                                               ConstElementPtr) {
    ConstElementPtr answer =
        isc::config::createAnswer(0, isc::detail::getConfigReport());
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::commandLeasesReclaimHandler(const string&,
                                                 ConstElementPtr args) {
    int status_code = CONTROL_RESULT_ERROR;
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
            server_->alloc_engine_->reclaimExpiredLeases4(0, 0, remove_lease);
            status_code = 0;
            message = "Reclamation of expired leases is complete.";
        }
    }
    ConstElementPtr answer = isc::config::createAnswer(status_code, message);
    return (answer);
}

ConstElementPtr
ControlledDhcpv4Srv::processCommand(const string& command,
                                    ConstElementPtr args) {
    string txt = args ? args->str() : "(none)";

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_COMMAND_RECEIVED)
              .arg(command).arg(txt);

    ControlledDhcpv4Srv* srv = ControlledDhcpv4Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(1,
          "Server object not initialized, so can't process command '" +
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
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 "Unrecognized command:" + command);
        return (answer);
    } catch (const Exception& ex) {
        return (isc::config::createAnswer(1, "Error while processing command '"
                                          + command + "':" + ex.what() +
                                          ", params: '" + txt + "'"));
    }
}

isc::data::ConstElementPtr
ControlledDhcpv4Srv::processConfig(isc::data::ConstElementPtr config) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_RECEIVED)
              .arg(config->str());

    ControlledDhcpv4Srv* srv = ControlledDhcpv4Srv::getInstance();

    // Single stream instance used in all error clauses
    std::ostringstream err;

    if (!srv) {
        err << "Server object not initialized, can't process config.";
        return (isc::config::createAnswer(1, err.str()));
    }

    ConstElementPtr answer = configureDhcp4Server(*srv, config);

    // Check that configuration was successful. If not, do not reopen sockets
    // and don't bother with DDNS stuff.
    try {
        int rcode = 0;
        isc::config::parseAnswer(rcode, answer);
        if (rcode != 0) {
            return (answer);
        }
    } catch (const std::exception& ex) {
        err << "Failed to process configuration:" << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Re-open lease and host database with new parameters.
    try {
        DatabaseConnection::db_lost_callback =
            boost::bind(&ControlledDhcpv4Srv::dbLostCallback, srv, _1);
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
        cfg_db->setAppendedParameters("universe=4");
        cfg_db->createManagers();
    } catch (const std::exception& ex) {
        err << "Unable to open database: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Server will start DDNS communications if its enabled.
    try {
        srv->startD2();
    } catch (const std::exception& ex) {
        err << "Error starting DHCP_DDNS client after server reconfiguration: "
            << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Setup DHCPv4-over-DHCPv6 IPC
    try {
        Dhcp4to6Ipc::instance().open();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "error starting DHCPv4-over-DHCPv6 IPC "
               " after server reconfiguration: " << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Configure DHCP packet queueing
    try {
        data::ConstElementPtr qc;
        qc  = CfgMgr::instance().getStagingCfg()->getDHCPQueueControl();
        if (IfaceMgr::instance().configureDHCPPacketQueue(AF_INET, qc)) {
            LOG_INFO(dhcp4_logger, DHCP4_CONFIG_PACKET_QUEUE)
                      .arg(IfaceMgr::instance().getPacketQueue4()->getInfoStr());
        }

    } catch (const std::exception& ex) {
        err << "Error setting packet queue controls after server reconfiguration: "
            << ex.what();
        return (isc::config::createAnswer(1, err.str()));
    }

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. It is possible that this
    // operation will fail for some interfaces but the openSockets function
    // guards against exceptions and invokes a callback function to
    // log warnings. Since we allow that this fails for some interfaces there
    // is no need to rollback configuration if socket fails to open on any
    // of the interfaces.
    CfgMgr::instance().getStagingCfg()->getCfgIface()->
        openSockets(AF_INET, srv->getServerPort(),
                    getInstance()->useBroadcast());

    // Install the timers for handling leases reclamation.
    try {
        CfgMgr::instance().getStagingCfg()->getCfgExpiration()->
            setupTimers(&ControlledDhcpv4Srv::reclaimExpiredLeases,
                        &ControlledDhcpv4Srv::deleteExpiredReclaimedLeases,
                        server_);

    } catch (const std::exception& ex) {
        err << "unable to setup timers for periodically running the"
            " reclamation of the expired leases: "
            << ex.what() << ".";
        return (isc::config::createAnswer(1, err.str()));
    }

    auto ctl_info = CfgMgr::instance().getStagingCfg()->getConfigControlInfo();
    if (ctl_info) {
        long fetch_time = static_cast<long>(ctl_info->getConfigFetchWaitTime());
        // Only schedule the CB fetch timer if the fetch wait time is greater
        // than 0.
        if (fetch_time > 0) {
            // When we run unit tests, we want to use milliseconds unit for the
            // specified interval. Otherwise, we use seconds. Note that using
            // milliseconds as a unit in unit tests prevents us from waiting 1
            // second on more before the timer goes off. Instead, we wait one
            // millisecond which significantly reduces the test time.
            if (!server_->inTestMode()) {
                fetch_time = 1000 * fetch_time;
            }

            boost::shared_ptr<unsigned> failure_count(new unsigned(0));
            TimerMgr::instance()->
                registerTimer("Dhcp4CBFetchTimer",
                              boost::bind(&ControlledDhcpv4Srv::cbFetchUpdates,
                                          server_, CfgMgr::instance().getStagingCfg(),
                                          failure_count),
                              fetch_time,
                              asiolink::IntervalTimer::ONE_SHOT);
            TimerMgr::instance()->setup("Dhcp4CBFetchTimer");
        }
    }

    // This hook point notifies hooks libraries that the configuration of the
    // DHCPv4 server has completed. It provides the hook library with the pointer
    // to the common IO service object, new server configuration in the JSON
    // format and with the pointer to the configuration storage where the
    // parsed configuration is stored.
    if (HooksManager::calloutsPresent(Hooks.hooks_index_dhcp4_srv_configured_)) {
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

        callout_handle->setArgument("io_context", srv->getIOService());
        callout_handle->setArgument("network_state", srv->getNetworkState());
        callout_handle->setArgument("json_config", config);
        callout_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());

        HooksManager::callCallouts(Hooks.hooks_index_dhcp4_srv_configured_,
                                   *callout_handle);

        // Ignore status code as none of them would have an effect on further
        // operation.
    }

    return (answer);
}

isc::data::ConstElementPtr
ControlledDhcpv4Srv::checkConfig(isc::data::ConstElementPtr config) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_RECEIVED)
              .arg(config->str());

    ControlledDhcpv4Srv* srv = ControlledDhcpv4Srv::getInstance();

    // Single stream instance used in all error clauses
    std::ostringstream err;

    if (!srv) {
        err << "Server object not initialized, can't process config.";
        return (isc::config::createAnswer(1, err.str()));
    }

    return (configureDhcp4Server(*srv, config, true));
}

ControlledDhcpv4Srv::ControlledDhcpv4Srv(uint16_t server_port /*= DHCP4_SERVER_PORT*/,
                                         uint16_t client_port /*= 0*/)
    : Dhcpv4Srv(server_port, client_port), io_service_(),
      timer_mgr_(TimerMgr::instance()) {
    if (getInstance()) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv4Srv instance already.");
    }
    server_ = this; // remember this instance for later use in handlers

    // TimerMgr uses IO service to run asynchronous timers.
    TimerMgr::instance()->setIOService(getIOService());

    // CommandMgr uses IO service to run asynchronous socket operations.
    CommandMgr::instance().setIOService(getIOService());

    // These are the commands always supported by the DHCPv4 server.
    // Please keep the list in alphabetic order.
    CommandMgr::instance().registerCommand("build-report",
        boost::bind(&ControlledDhcpv4Srv::commandBuildReportHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-get",
        boost::bind(&ControlledDhcpv4Srv::commandConfigGetHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-reload",
        boost::bind(&ControlledDhcpv4Srv::commandConfigReloadHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-set",
        boost::bind(&ControlledDhcpv4Srv::commandConfigSetHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-test",
        boost::bind(&ControlledDhcpv4Srv::commandConfigTestHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("config-write",
        boost::bind(&ControlledDhcpv4Srv::commandConfigWriteHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("dhcp-enable",
        boost::bind(&ControlledDhcpv4Srv::commandDhcpEnableHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("dhcp-disable",
        boost::bind(&ControlledDhcpv4Srv::commandDhcpDisableHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("libreload",
        boost::bind(&ControlledDhcpv4Srv::commandLibReloadHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("leases-reclaim",
        boost::bind(&ControlledDhcpv4Srv::commandLeasesReclaimHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("shutdown",
        boost::bind(&ControlledDhcpv4Srv::commandShutdownHandler, this, _1, _2));

    CommandMgr::instance().registerCommand("version-get",
        boost::bind(&ControlledDhcpv4Srv::commandVersionGetHandler, this, _1, _2));

    // Register statistic related commands
    CommandMgr::instance().registerCommand("statistic-get",
        boost::bind(&StatsMgr::statisticGetHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-reset",
        boost::bind(&StatsMgr::statisticResetHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-remove",
        boost::bind(&StatsMgr::statisticRemoveHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-get-all",
        boost::bind(&StatsMgr::statisticGetAllHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-reset-all",
        boost::bind(&StatsMgr::statisticResetAllHandler, _1, _2));

    CommandMgr::instance().registerCommand("statistic-remove-all",
        boost::bind(&StatsMgr::statisticRemoveAllHandler, _1, _2));

}

void ControlledDhcpv4Srv::shutdown() {
    io_service_.stop(); // Stop ASIO transmissions
    Dhcpv4Srv::shutdown(); // Initiate DHCPv4 shutdown procedure.
}

ControlledDhcpv4Srv::~ControlledDhcpv4Srv() {
    try {
        cleanup();

        // The closure captures either a shared pointer (memory leak)
        // or a raw pointer (pointing to a deleted object).
        DatabaseConnection::db_lost_callback = 0;

        timer_mgr_->unregisterTimers();

        // Close the command socket (if it exists).
        CommandMgr::instance().closeCommandSocket();

        // Deregister any registered commands (please keep in alphabetic order)
        CommandMgr::instance().deregisterCommand("build-report");
        CommandMgr::instance().deregisterCommand("config-get");
        CommandMgr::instance().deregisterCommand("config-reload");
        CommandMgr::instance().deregisterCommand("config-test");
        CommandMgr::instance().deregisterCommand("config-write");
        CommandMgr::instance().deregisterCommand("leases-reclaim");
        CommandMgr::instance().deregisterCommand("libreload");
        CommandMgr::instance().deregisterCommand("config-set");
        CommandMgr::instance().deregisterCommand("dhcp-disable");
        CommandMgr::instance().deregisterCommand("dhcp-enable");
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

    server_ = NULL; // forget this instance. Noone should call any handlers at
                    // this stage.
}

void ControlledDhcpv4Srv::sessionReader(void) {
    // Process one asio event. If there are more events, iface_mgr will call
    // this callback more than once.
    if (getInstance()) {
        getInstance()->io_service_.run_one();
    }
}

void
ControlledDhcpv4Srv::reclaimExpiredLeases(const size_t max_leases,
                                          const uint16_t timeout,
                                          const bool remove_lease,
                                          const uint16_t max_unwarned_cycles) {
    server_->alloc_engine_->reclaimExpiredLeases4(max_leases, timeout,
                                                  remove_lease,
                                                  max_unwarned_cycles);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME);
}

void
ControlledDhcpv4Srv::deleteExpiredReclaimedLeases(const uint32_t secs) {
    server_->alloc_engine_->deleteExpiredReclaimedLeases4(secs);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME);
}

void
ControlledDhcpv4Srv::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
    bool reopened = false;

    // Re-open lease and host database with new parameters.
    try {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getCurrentCfg()->getCfgDbAccess();
        cfg_db->createManagers();
        reopened = true;
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_DB_RECONNECT_ATTEMPT_FAILED).arg(ex.what());
    }

    if (reopened) {
        // Cancel the timer.
        if (TimerMgr::instance()->isTimerRegistered("Dhcp4DbReconnectTimer")) {
            TimerMgr::instance()->cancel("Dhcp4DbReconnectTimer");
        }

        // Set network state to service enabled
        network_state_->enableService();

        // Toss the reconnect control, we're done with it
        db_reconnect_ctl.reset();
    } else {
        if (!db_reconnect_ctl->checkRetries()) {
            LOG_ERROR(dhcp4_logger, DHCP4_DB_RECONNECT_RETRIES_EXHAUSTED)
            .arg(db_reconnect_ctl->maxRetries());
            shutdown();
            return;
        }

        LOG_INFO(dhcp4_logger, DHCP4_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        if (!TimerMgr::instance()->isTimerRegistered("Dhcp4DbReconnectTimer")) {
            TimerMgr::instance()->registerTimer("Dhcp4DbReconnectTimer",
                            boost::bind(&ControlledDhcpv4Srv::dbReconnect, this,
                                        db_reconnect_ctl),
                            db_reconnect_ctl->retryInterval(),
                            asiolink::IntervalTimer::ONE_SHOT);
        }

        TimerMgr::instance()->setup("Dhcp4DbReconnectTimer");
    }
}

bool
ControlledDhcpv4Srv::dbLostCallback(ReconnectCtlPtr db_reconnect_ctl) {
    // Disable service until we recover
    network_state_->disableService();

    if (!db_reconnect_ctl) {
        // This shouldn't never happen
        LOG_ERROR(dhcp4_logger, DHCP4_DB_RECONNECT_NO_DB_CTL);
        return (false);
    }

    // If reconnect isn't enabled, log it and return false
    if (!db_reconnect_ctl->retriesLeft() ||
        !db_reconnect_ctl->retryInterval()) {
        LOG_INFO(dhcp4_logger, DHCP4_DB_RECONNECT_DISABLED)
            .arg(db_reconnect_ctl->retriesLeft())
            .arg(db_reconnect_ctl->retryInterval());
        return(false);
    }

    // Invoke reconnect method
    dbReconnect(db_reconnect_ctl);

    return(true);
}

void
ControlledDhcpv4Srv::cbFetchUpdates(const SrvConfigPtr& srv_cfg,
                                    boost::shared_ptr<unsigned> failure_count) {
    try {
        // Fetch any configuration backend updates since our last fetch.
        server_->getCBControl()->databaseConfigFetch(srv_cfg,
                                                     CBControlDHCPv4::FetchMode::FETCH_UPDATE);
        (*failure_count) = 0;

    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_CB_FETCH_UPDATES_FAIL)
            .arg(ex.what());

        // We allow at most 10 consecutive failures after which we stop
        // making further attempts to fetch the configuration updates.
        // Let's return without re-scheduling the timer.
        if (++(*failure_count) > 10) {
            LOG_ERROR(dhcp4_logger, DHCP4_CB_FETCH_UPDATES_RETRIES_EXHAUSTED);
            return;
        }
    }

    // Reschedule the timer to fetch new updates or re-try if
    // the previous attempt resulted in an error.
    if (TimerMgr::instance()->isTimerRegistered("Dhcp4CBFetchTimer")) {
        TimerMgr::instance()->setup("Dhcp4CBFetchTimer");
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
