// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
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
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <cfgrpt/config_report.h>
#include <signal.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::stats;
using namespace std;

namespace {

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

    // We're going to modify the timers configuration. This is not allowed
    // when the thread is running.
    try {
        TimerMgr::instance()->stopThread();
    } catch (const std::exception& ex) {
        err << "Unable to stop worker thread running timers: "
            << ex.what() << ".";
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

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. It is possible that this
    // operation will fail for some interfaces but the openSockets function
    // guards against exceptions and invokes a callback function to
    // log warnings. Since we allow that this fails for some interfaces there
    // is no need to rollback configuration if socket fails to open on any
    // of the interfaces.
    CfgMgr::instance().getStagingCfg()->getCfgIface()->
        openSockets(AF_INET, srv->getPort(), getInstance()->useBroadcast());

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

    // Start worker thread if there are any timers installed.
    if (TimerMgr::instance()->timersCount() > 0) {
        try {
            TimerMgr::instance()->startThread();
        } catch (const std::exception& ex) {
            err << "Unable to start worker thread running timers: "
                << ex.what() << ".";
            return (isc::config::createAnswer(1, err.str()));
        }
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

ControlledDhcpv4Srv::ControlledDhcpv4Srv(uint16_t port /*= DHCP4_SERVER_PORT*/)
    : Dhcpv4Srv(port), io_service_(), timer_mgr_(TimerMgr::instance()) {
    if (getInstance()) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv4Srv instance already.");
    }
    server_ = this; // remember this instance for later use in handlers

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

        // Stop worker thread running timers, if it is running. Then
        // unregister any timers.
        timer_mgr_->stopThread();
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

}; // end of isc::dhcp namespace
}; // end of isc namespace
