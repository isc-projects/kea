// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <config/command_mgr.h>
#include <cryptolink/crypto_hash.h>
#include <dhcp/libdhcp++.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6to4_ipc.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/parser_context.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/db_type.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <process/cfgrpt/config_report.h>
#include <stats/stats_mgr.h>
#include <util/encode/hex.h>
#include <util/multi_threading_mgr.h>

#include <signal.h>

#include <sstream>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::stats;
using namespace isc::util;
using namespace std;
namespace ph = std::placeholders;

namespace {

/// Structure that holds registered hook indexes.
struct CtrlDhcp6Hooks {
    int hooks_index_dhcp6_srv_configured_;

    /// Constructor that registers hook points for the DHCPv6 server.
    CtrlDhcp6Hooks() {
        hooks_index_dhcp6_srv_configured_ = HooksManager::registerHook("dhcp6_srv_configured");
    }

};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
CtrlDhcp6Hooks Hooks;

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

void
ControlledDhcpv6Srv::init(const std::string& file_name) {
    // Keep the call timestamp.
    start_ = boost::posix_time::second_clock::universal_time();

    // Configure the server using JSON file.
    ConstElementPtr result = loadConfigFile(file_name);

    int rcode;
    ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
    if (rcode != CONTROL_RESULT_SUCCESS) {
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
    signal_set_.reset(new IOSignalSet(getIOService(), signalHandler));

    signal_set_->add(SIGINT);
    signal_set_->add(SIGHUP);
    signal_set_->add(SIGTERM);
}

void ControlledDhcpv6Srv::cleanup() {
    signal_set_.reset();
    getIOService()->poll();
}

ConstElementPtr
ControlledDhcpv6Srv::loadConfigFile(const std::string& file_name) {
    // This is a configuration backend implementation that reads the
    // configuration from a JSON file.

    isc::data::ConstElementPtr json;
    isc::data::ConstElementPtr result;

    // Basic sanity check: file name must not be empty.
    try {
        if (file_name.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(isc::BadValue, "JSON configuration file not specified."
                      " Please use -c command line option.");
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
        ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
        if (rcode != CONTROL_RESULT_SUCCESS) {
            string reason = comment ? comment->stringValue() :
                "no details available";
            isc_throw(isc::BadValue, reason);
        }
    } catch (const std::exception& ex) {
        // If configuration failed at any stage, we drop the staging
        // configuration and continue to use the previous one.
        CfgMgr::instance().rollback();

        LOG_ERROR(dhcp6_logger, DHCP6_CONFIG_LOAD_FAIL)
            .arg(file_name).arg(ex.what());
        isc_throw(isc::BadValue, "configuration error using file '"
                  << file_name << "': " << ex.what());
    }

    LOG_WARN(dhcp6_logger, DHCP6_MULTI_THREADING_INFO)
        .arg(MultiThreadingMgr::instance().getMode() ? "yes" : "no")
        .arg(MultiThreadingMgr::instance().getThreadPoolSize())
        .arg(MultiThreadingMgr::instance().getPacketQueueSize());

    return (result);
}

ConstElementPtr
ControlledDhcpv6Srv::commandShutdownHandler(const string&, ConstElementPtr args) {
    if (!ControlledDhcpv6Srv::getInstance()) {
        LOG_WARN(dhcp6_logger, DHCP6_NOT_RUNNING);
        return (createAnswer(CONTROL_RESULT_ERROR, "Shutdown failure."));
    }

    int exit_value = 0;
    if (args) {
        // @todo Should we go ahead and shutdown even if the args are invalid?
        if (args->getType() != Element::map) {
            return (createAnswer(CONTROL_RESULT_ERROR, "Argument must be a map"));
        }

        ConstElementPtr param = args->get("exit-value");
        if (param)  {
            if (param->getType() != Element::integer) {
                return (createAnswer(CONTROL_RESULT_ERROR,
                                     "parameter 'exit-value' is not an integer"));
            }

            exit_value = param->intValue();
        }
    }

    ControlledDhcpv6Srv::getInstance()->shutdownServer(exit_value);
    return (createAnswer(CONTROL_RESULT_SUCCESS, "Shutting down."));
}

ConstElementPtr
ControlledDhcpv6Srv::commandLibReloadHandler(const string&, ConstElementPtr) {
    LOG_WARN(dhcp6_logger, DHCP6_DEPRECATED).arg("libreload command");

    // stop thread pool (if running)
    MultiThreadingCriticalSection cs;

    // Clear the packet queue.
    MultiThreadingMgr::instance().getThreadPool().reset();

    try {
        /// Get list of currently loaded libraries and reload them.
        HookLibsCollection loaded = HooksManager::getLibraryInfo();
        HooksManager::prepareUnloadLibraries();
        static_cast<void>(HooksManager::unloadLibraries());
        bool multi_threading_enabled = true;
        uint32_t thread_count = 0;
        uint32_t queue_size = 0;
        CfgMultiThreading::extract(CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading(),
                                   multi_threading_enabled, thread_count, queue_size);
        bool status = HooksManager::loadLibraries(loaded, multi_threading_enabled);
        if (!status) {
            isc_throw(Unexpected, "Failed to reload hooks libraries "
                                  "(WARNING: libreload is deprecated).");
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_HOOKS_LIBS_RELOAD_FAIL);
        ConstElementPtr answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
        return (answer);
    }
    ConstElementPtr answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS,
                             "Hooks libraries successfully reloaded "
                             "(WARNING: libreload is deprecated).");
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigReloadHandler(const string&,
                                                ConstElementPtr /*args*/) {
    // Get configuration file name.
    string file = ControlledDhcpv6Srv::getInstance()->getConfigFile();
    try {
        LOG_INFO(dhcp6_logger, DHCP6_DYNAMIC_RECONFIGURATION).arg(file);
        auto result = loadConfigFile(file);
        LOG_INFO(dhcp6_logger, DHCP6_DYNAMIC_RECONFIGURATION_SUCCESS).arg(file);
        return (result);
    } catch (const std::exception& ex) {
        // Log the unsuccessful reconfiguration. The reason for failure
        // should be already logged. Don't rethrow an exception so as
        // the server keeps working.
        LOG_FATAL(dhcp6_logger, DHCP6_DYNAMIC_RECONFIGURATION_FAIL)
            .arg(file);
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Config reload failed: " + string(ex.what())));
    }
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigGetHandler(const string&,
                                             ConstElementPtr /*args*/) {
    ElementPtr config = CfgMgr::instance().getCurrentCfg()->toElement();
    string hash = BaseCommandMgr::getHash(config);
    config->set("hash", Element::create(hash));

    return (createAnswer(CONTROL_RESULT_SUCCESS, config));
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigHashGetHandler(const string&,
                                                 ConstElementPtr /*args*/) {
    ConstElementPtr config = CfgMgr::instance().getCurrentCfg()->toElement();
    string hash = BaseCommandMgr::getHash(config);

    ElementPtr params = Element::createMap();
    params->set("hash", Element::create(hash));
    return (createAnswer(CONTROL_RESULT_SUCCESS, params));
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigWriteHandler(const string&,
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
        // from the command-line
        filename = getConfigFile();
        if (filename.empty()) {
            return (createAnswer(CONTROL_RESULT_ERROR, "Unable to determine filename."
                                 "Please specify filename explicitly."));
        }
    } else {
        try {
            checkWriteConfigFile(filename);
        } catch (const isc::Exception& ex) {
            std::ostringstream msg;
            msg << "not allowed to write config into " << filename
                << ": " << ex.what();
            return (createAnswer(CONTROL_RESULT_ERROR, msg.str()));
        }
    }

    // Ok, it's time to write the file.
    size_t size = 0;
    try {
        ConstElementPtr cfg = CfgMgr::instance().getCurrentCfg()->toElement();
        size = writeConfigFile(filename, cfg);
    } catch (const isc::Exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, string("Error during write-config: ")
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
    // { "Dhcp6": { ... } }
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

    // Check unsupported objects.
    if (message.empty()) {
        for (auto obj : args->mapValue()) {
            const string& obj_name = obj.first;
            if (obj_name != "Dhcp6") {
                LOG_ERROR(dhcp6_logger, DHCP6_CONFIG_UNSUPPORTED_OBJECT)
                    .arg(obj_name);
                if (message.empty()) {
                    message = "Unsupported '" + obj_name + "' parameter";
                } else {
                    message += " (and '" + obj_name + "')";
                }
            }
        }
        if (!message.empty()) {
            message += ".";
        }
    }

    if (!message.empty()) {
        // Something is amiss with arguments, return a failure response.
        ConstElementPtr result = isc::config::createAnswer(status_code,
                                                           message);
        return (result);
    }

    // stop thread pool (if running)
    MultiThreadingCriticalSection cs;

    // We are starting the configuration process so we should remove any
    // staging configuration that has been created during previous
    // configuration attempts.
    CfgMgr::instance().rollback();

    // Parse the logger configuration explicitly into the staging config.
    // Note this does not alter the current loggers, they remain in
    // effect until we apply the logging config below.  If no logging
    // is supplied logging will revert to default logging.
    Daemon::configureLogger(dhcp6, CfgMgr::instance().getStagingCfg());

    // Let's apply the new logging. We do it early, so we'll be able to print
    // out what exactly is wrong with the new config in case of problems.
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
    } else if (CfgMgr::instance().getCurrentCfg()->getSequence() != 0) {
        // Ok, we applied the logging from the upcoming configuration, but
        // there were problems with the config. As such, we need to back off
        // and revert to the previous logging configuration. This is not done if
        // sequence == 0, because that would mean always reverting to stdout by
        // default, and it is arguably more helpful to have the error in a
        // potential file or syslog configured in the upcoming configuration.
        CfgMgr::instance().getCurrentCfg()->applyLoggingCfg();

        // Not initial configuration so someone can believe we reverted
        // to the previous configuration. It is not the case so be clear
        // about this.
        LOG_FATAL(dhcp6_logger, DHCP6_CONFIG_UNRECOVERABLE_ERROR);
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
    // { "Dhcp6": { ... } }
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

    // Check unsupported objects.
    if (message.empty()) {
        for (auto obj : args->mapValue()) {
            const string& obj_name = obj.first;
            if (obj_name != "Dhcp6") {
                LOG_ERROR(dhcp6_logger, DHCP6_CONFIG_UNSUPPORTED_OBJECT)
                    .arg(obj_name);
                if (message.empty()) {
                    message = "Unsupported '" + obj_name + "' parameter";
                } else {
                    message += " (and '" + obj_name + "')";
                }
            }
        }
        if (!message.empty()) {
            message += ".";
        }
    }

    if (!message.empty()) {
        // Something is amiss with arguments, return a failure response.
        ConstElementPtr result = isc::config::createAnswer(status_code,
                                                           message);
        return (result);
    }

    // stop thread pool (if running)
    MultiThreadingCriticalSection cs;

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
    std::string origin;

    // If the args map does not contain 'origin' parameter, the default type
    // will be used (user command).
    NetworkState::Origin type = NetworkState::Origin::USER_COMMAND;

    // Parse arguments to see if the 'max-period' or 'origin' parameters have
    // been specified.
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
                }
            }
            ConstElementPtr origin_element = args->get("origin");
            // The 'origin' parameter is optional.
            if (origin_element) {
                // It must be a string, if specified.
                if (origin_element->getType() != Element::string) {
                    message << "'origin' argument must be a string";

                } else {
                    origin = origin_element->stringValue();
                    if (origin == "ha-partner") {
                        type = NetworkState::Origin::HA_COMMAND;
                    } else if (origin != "user") {
                        if (origin.empty()) {
                            origin = "(empty string)";
                        }
                        message << "invalid value used for 'origin' parameter: "
                                << origin;
                    }
                }
            }
        }
    }

    // No error occurred, so let's disable the service.
    if (message.tellp() == 0) {
        message << "DHCPv6 service disabled";
        if (max_period > 0) {
            message << " for " << max_period << " seconds";

            // The user specified that the DHCP service should resume not
            // later than in max-period seconds. If the 'dhcp-enable' command
            // is not sent, the DHCP service will resume automatically.
            network_state_->delayedEnableAll(static_cast<unsigned>(max_period),
                                             type);
        }
        network_state_->disableService(type);

        // Success.
        return (config::createAnswer(CONTROL_RESULT_SUCCESS, message.str()));
    }

    // Failure.
    return (config::createAnswer(CONTROL_RESULT_ERROR, message.str()));
}

ConstElementPtr
ControlledDhcpv6Srv::commandDhcpEnableHandler(const std::string&,
                                              ConstElementPtr args) {
    std::ostringstream message;
    std::string origin;

    // If the args map does not contain 'origin' parameter, the default type
    // will be used (user command).
    NetworkState::Origin type = NetworkState::Origin::USER_COMMAND;

    // Parse arguments to see if the 'origin' parameter has been specified.
    if (args) {
        // Arguments must be a map.
        if (args->getType() != Element::map) {
            message << "arguments for the 'dhcp-enable' command must be a map";

        } else {
            ConstElementPtr origin_element = args->get("origin");
            // The 'origin' parameter is optional.
            if (origin_element) {
                // It must be a string, if specified.
                if (origin_element->getType() != Element::string) {
                    message << "'origin' argument must be a string";

                } else {
                    origin = origin_element->stringValue();
                    if (origin == "ha-partner") {
                        type = NetworkState::Origin::HA_COMMAND;
                    } else if (origin != "user") {
                        if (origin.empty()) {
                            origin = "(empty string)";
                        }
                        message << "invalid value used for 'origin' parameter: "
                                << origin;
                    }
                }
            }
        }
    }

    // No error occurred, so let's enable the service.
    if (message.tellp() == 0) {
        network_state_->enableService(type);

        // Success.
        return (config::createAnswer(CONTROL_RESULT_SUCCESS,
                                     "DHCP service successfully enabled"));
    }

    // Failure.
    return (config::createAnswer(CONTROL_RESULT_ERROR, message.str()));
}

ConstElementPtr
ControlledDhcpv6Srv::commandVersionGetHandler(const string&, ConstElementPtr) {
    ElementPtr extended = Element::create(Dhcpv6Srv::getVersion(true));
    ElementPtr arguments = Element::createMap();
    arguments->set("extended", extended);
    ConstElementPtr answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS,
                                Dhcpv6Srv::getVersion(false),
                                arguments);
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandBuildReportHandler(const string&,
                                               ConstElementPtr) {
    ConstElementPtr answer =
        isc::config::createAnswer(CONTROL_RESULT_SUCCESS, isc::detail::getConfigReport());
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandLeasesReclaimHandler(const string&,
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
            server_->alloc_engine_->reclaimExpiredLeases6(0, 0, remove_lease);
            status_code = 0;
            message = "Reclamation of expired leases is complete.";
        }
    }
    ConstElementPtr answer = isc::config::createAnswer(status_code, message);
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandServerTagGetHandler(const std::string&,
                                                ConstElementPtr) {
    const std::string& tag =
        CfgMgr::instance().getCurrentCfg()->getServerTag();
    ElementPtr response = Element::createMap();
    response->set("server-tag", Element::create(tag));

    return (createAnswer(CONTROL_RESULT_SUCCESS, response));
}

ConstElementPtr
ControlledDhcpv6Srv::commandConfigBackendPullHandler(const std::string&,
                                                     ConstElementPtr) {
    auto ctl_info = CfgMgr::instance().getCurrentCfg()->getConfigControlInfo();
    if (!ctl_info) {
        return (createAnswer(CONTROL_RESULT_EMPTY, "No config backend."));
    }

    // stop thread pool (if running)
    MultiThreadingCriticalSection cs;

    // Reschedule the periodic CB fetch.
    if (TimerMgr::instance()->isTimerRegistered("Dhcp6CBFetchTimer")) {
        TimerMgr::instance()->cancel("Dhcp6CBFetchTimer");
        TimerMgr::instance()->setup("Dhcp6CBFetchTimer");
    }

    // Code from cbFetchUpdates.
    // The configuration to use is the current one because this is called
    // after the configuration manager commit.
    try {
        auto srv_cfg = CfgMgr::instance().getCurrentCfg();
        auto mode = CBControlDHCPv6::FetchMode::FETCH_UPDATE;
        server_->getCBControl()->databaseConfigFetch(srv_cfg, mode);
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_CB_ON_DEMAND_FETCH_UPDATES_FAIL)
            .arg(ex.what());
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "On demand configuration update failed: " +
                             string(ex.what())));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "On demand configuration update successful."));
}

ConstElementPtr
ControlledDhcpv6Srv::commandStatusGetHandler(const string&,
                                             ConstElementPtr /*args*/) {
    ElementPtr status = Element::createMap();
    status->set("pid", Element::create(static_cast<int>(getpid())));

    auto now = boost::posix_time::second_clock::universal_time();
    // Sanity check: start_ is always initialized.
    if (!start_.is_not_a_date_time()) {
        auto uptime = now - start_;
        status->set("uptime", Element::create(uptime.total_seconds()));
    }

    auto last_commit = CfgMgr::instance().getCurrentCfg()->getLastCommitTime();
    if (!last_commit.is_not_a_date_time()) {
        auto reload = now - last_commit;
        status->set("reload", Element::create(reload.total_seconds()));
    }

    auto& mt_mgr = MultiThreadingMgr::instance();
    if (mt_mgr.getMode()) {
        status->set("multi-threading-enabled", Element::create(true));
        status->set("thread-pool-size", Element::create(static_cast<int32_t>(
                        MultiThreadingMgr::instance().getThreadPoolSize())));
        status->set("packet-queue-size", Element::create(static_cast<int32_t>(
                        MultiThreadingMgr::instance().getPacketQueueSize())));
        ElementPtr queue_stats = Element::createList();
        queue_stats->add(Element::create(mt_mgr.getThreadPool().getQueueStat(10)));
        queue_stats->add(Element::create(mt_mgr.getThreadPool().getQueueStat(100)));
        queue_stats->add(Element::create(mt_mgr.getThreadPool().getQueueStat(1000)));
        status->set("packet-queue-statistics", queue_stats);

    } else {
        status->set("multi-threading-enabled", Element::create(false));
    }

    // Iterate through the interfaces and get all the errors.
    ElementPtr socket_errors(Element::createList());
    for (IfacePtr const& interface : IfaceMgr::instance().getIfaces()) {
        for (std::string const& error : interface->getErrors()) {
            socket_errors->add(Element::create(error));
        }
    }

    // Abstract the information from all sockets into a single status.
    ElementPtr sockets(Element::createMap());
    if (socket_errors->empty()) {
        sockets->set("status", Element::create("ready"));
    } else {
        ReconnectCtlPtr const reconnect_ctl(
            CfgMgr::instance().getCurrentCfg()->getCfgIface()->getReconnectCtl());
        if (reconnect_ctl && reconnect_ctl->retriesLeft()) {
            sockets->set("status", Element::create("retrying"));
        } else {
            sockets->set("status", Element::create("failed"));
        }
        sockets->set("errors", socket_errors);
    }
    status->set("sockets", sockets);

    return (createAnswer(CONTROL_RESULT_SUCCESS, status));
}

ConstElementPtr
ControlledDhcpv6Srv::commandStatisticSetMaxSampleCountAllHandler(const string&,
                                                                 ConstElementPtr args) {
    StatsMgr& stats_mgr = StatsMgr::instance();
    ConstElementPtr answer = stats_mgr.statisticSetMaxSampleCountAllHandler(args);
    // Update the default parameter.
    long max_samples = stats_mgr.getMaxSampleCountDefault();
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal(
        "statistic-default-sample-count", Element::create(max_samples));
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::commandStatisticSetMaxSampleAgeAllHandler(const string&,
                                                               ConstElementPtr args) {
    StatsMgr& stats_mgr = StatsMgr::instance();
    ConstElementPtr answer = stats_mgr.statisticSetMaxSampleAgeAllHandler(args);
    // Update the default parameter.
    auto duration = stats_mgr.getMaxSampleAgeDefault();
    long max_age = toSeconds(duration);
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal(
        "statistic-default-sample-age", Element::create(max_age));
    return (answer);
}

ConstElementPtr
ControlledDhcpv6Srv::processCommand(const string& command,
                                    ConstElementPtr args) {
    string txt = args ? args->str() : "(none)";

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_COMMAND_RECEIVED)
              .arg(command).arg(txt);

    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(CONTROL_RESULT_ERROR,
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

        } else if (command == "config-hash-get") {
            return (srv->commandConfigHashGetHandler(command, args));

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

        } else if (command == "server-tag-get") {
            return (srv->commandServerTagGetHandler(command, args));

        } else if (command == "config-backend-pull") {
            return (srv->commandConfigBackendPullHandler(command, args));

        } else if (command == "status-get") {
            return (srv->commandStatusGetHandler(command, args));
        }

        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, "Unrecognized command:"
                                          + command));

    } catch (const isc::Exception& ex) {
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, "Error while processing command '"
                                          + command + "': " + ex.what() +
                                          ", params: '" + txt + "'"));
    }
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::processConfig(isc::data::ConstElementPtr config) {
    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    // Single stream instance used in all error clauses
    std::ostringstream err;

    if (!srv) {
        err << "Server object not initialized, can't process config.";
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_RECEIVED)
        .arg(srv->redactConfig(config)->str());

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
        err << "Failed to process configuration:" << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Re-open lease and host database with new parameters.
    try {
        DatabaseConnection::db_lost_callback_ =
            std::bind(&ControlledDhcpv6Srv::dbLostCallback, srv, ph::_1);

        DatabaseConnection::db_recovered_callback_ =
            std::bind(&ControlledDhcpv6Srv::dbRecoveredCallback, srv, ph::_1);

        DatabaseConnection::db_failed_callback_ =
            std::bind(&ControlledDhcpv6Srv::dbFailedCallback, srv, ph::_1);

        CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
        string params = "universe=6";
        if (cfg_db->getExtendedInfoTablesEnabled()) {
            params += " extended-info-tables=true";
        }
        cfg_db->setAppendedParameters(params);
        cfg_db->createManagers();
        // Reset counters related to connections as all managers have been recreated.
        srv->getNetworkState()->reset(NetworkState::Origin::DB_CONNECTION);
    } catch (const std::exception& ex) {
        err << "Unable to open database: " << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Regenerate server identifier if needed.
    try {
        const std::string duid_file =
            std::string(CfgMgr::instance().getDataDir()) + "/" +
            std::string(SERVER_DUID_FILE);
        DuidPtr duid = CfgMgr::instance().getStagingCfg()->getCfgDUID()->create(duid_file);
        server_->serverid_.reset(new Option(Option::V6, D6O_SERVERID, duid->getDuid()));
        if (duid) {
            LOG_INFO(dhcp6_logger, DHCP6_USING_SERVERID)
                .arg(duid->toText())
                .arg(duid_file);
        }

    } catch (const std::exception& ex) {
        err << "unable to configure server identifier: " << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Server will start DDNS communications if its enabled.
    try {
        srv->startD2();
    } catch (const std::exception& ex) {
        err << "Error starting DHCP_DDNS client after server reconfiguration: "
            << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Setup DHCPv4-over-DHCPv6 IPC
    try {
        Dhcp6to4Ipc::instance().open();
    } catch (const std::exception& ex) {
        err << "error starting DHCPv4-over-DHCPv6 IPC "
               " after server reconfiguration: " << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Configure DHCP packet queueing
    try {
        data::ConstElementPtr qc;
        qc = CfgMgr::instance().getStagingCfg()->getDHCPQueueControl();
        if (IfaceMgr::instance().configureDHCPPacketQueue(AF_INET6, qc)) {
            LOG_INFO(dhcp6_logger, DHCP6_CONFIG_PACKET_QUEUE)
                     .arg(IfaceMgr::instance().getPacketQueue6()->getInfoStr());
        }

    } catch (const std::exception& ex) {
        err << "Error setting packet queue controls after server reconfiguration: "
            << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Configure a callback to shut down the server when the bind socket
    // attempts exceeded.
    CfgIface::open_sockets_failed_callback_ =
        std::bind(&ControlledDhcpv6Srv::openSocketsFailedCallback, srv, ph::_1);

    // Configuration may change active interfaces. Therefore, we have to reopen
    // sockets according to new configuration. It is possible that this
    // operation will fail for some interfaces but the openSockets function
    // guards against exceptions and invokes a callback function to
    // log warnings. Since we allow that this fails for some interfaces there
    // is no need to rollback configuration if socket fails to open on any
    // of the interfaces.
    CfgMgr::instance().getStagingCfg()->getCfgIface()->
        openSockets(AF_INET6, srv->getServerPort());

    // Install the timers for handling leases reclamation.
    try {
        CfgMgr::instance().getStagingCfg()->getCfgExpiration()->
            setupTimers(&ControlledDhcpv6Srv::reclaimExpiredLeases,
                        &ControlledDhcpv6Srv::deleteExpiredReclaimedLeases,
                        server_);

    } catch (const std::exception& ex) {
        err << "unable to setup timers for periodically running the"
            " reclamation of the expired leases: "
            << ex.what() << ".";
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    // Setup config backend polling, if configured for it.
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
                registerTimer("Dhcp6CBFetchTimer",
                              std::bind(&ControlledDhcpv6Srv::cbFetchUpdates,
                                        server_, CfgMgr::instance().getStagingCfg(),
                                        failure_count),
                              fetch_time,
                              asiolink::IntervalTimer::ONE_SHOT);
            TimerMgr::instance()->setup("Dhcp6CBFetchTimer");
        }
    }

    // Finally, we can commit runtime option definitions in libdhcp++. This is
    // exception free.
    LibDHCP::commitRuntimeOptionDefs();

    auto notify_libraries = ControlledDhcpv6Srv::finishConfigHookLibraries(config);
    if (notify_libraries) {
        return (notify_libraries);
    }

    // Initialize the allocators. If the user selected a Free Lease Queue Allocator
    // for any of the subnets, the server will now populate free leases to the queue.
    // It may take a while!
    try {
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->initAllocatorsAfterConfigure();

    } catch (const std::exception& ex) {
        err << "Error initializing the lease allocators: " << ex.what();
    }

    // Apply multi threading settings.
    // @note These settings are applied/updated only if no errors occur while
    // applying the new configuration.
    // @todo This should be fixed.
    try {
        CfgMultiThreading::apply(CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading());
    } catch (const std::exception& ex) {
        err << "Error applying multi threading settings: "
            << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    return (answer);
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::finishConfigHookLibraries(isc::data::ConstElementPtr config) {
    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();
    // This hook point notifies hooks libraries that the configuration of the
    // DHCPv6 server has completed. It provides the hook library with the pointer
    // to the common IO service object, new server configuration in the JSON
    // format and with the pointer to the configuration storage where the
    // parsed configuration is stored.
    if (HooksManager::calloutsPresent(Hooks.hooks_index_dhcp6_srv_configured_)) {
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

        callout_handle->setArgument("io_context", srv->getIOService());
        callout_handle->setArgument("network_state", srv->getNetworkState());
        callout_handle->setArgument("json_config", config);
        callout_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());

        HooksManager::callCallouts(Hooks.hooks_index_dhcp6_srv_configured_,
                                   *callout_handle);

        // If next step is DROP, report a configuration error.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            string error;
            try {
                callout_handle->getArgument("error", error);
            } catch (NoSuchArgument const& ex) {
                error = "unknown error";
            }
            return (isc::config::createAnswer(CONTROL_RESULT_ERROR, error));
        }
    }

    return (ConstElementPtr());
}

isc::data::ConstElementPtr
ControlledDhcpv6Srv::checkConfig(isc::data::ConstElementPtr config) {
    ControlledDhcpv6Srv* srv = ControlledDhcpv6Srv::getInstance();

    if (!srv) {
        ConstElementPtr no_srv = isc::config::createAnswer(CONTROL_RESULT_ERROR,
            "Server object not initialized, can't process config.");
        return (no_srv);
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_RECEIVED)
        .arg(srv->redactConfig(config)->str());

    return (configureDhcp6Server(*srv, config, true));
}

ControlledDhcpv6Srv::ControlledDhcpv6Srv(uint16_t server_port /*= DHCP6_SERVER_PORT*/,
                                         uint16_t client_port /*= 0*/)
    : Dhcpv6Srv(server_port, client_port), timer_mgr_(TimerMgr::instance()) {
    if (getInstance()) {
        isc_throw(InvalidOperation,
                  "There is another Dhcpv6Srv instance already.");
    }
    server_ = this; // remember this instance for later use in handlers

    // TimerMgr uses IO service to run asynchronous timers.
    TimerMgr::instance()->setIOService(getIOService());

    // CommandMgr uses IO service to run asynchronous socket operations.
    CommandMgr::instance().setIOService(getIOService());

    // LeaseMgr uses IO service to run asynchronous timers.
    LeaseMgr::setIOService(getIOService());

    // HostMgr uses IO service to run asynchronous timers.
    HostMgr::setIOService(getIOService());

    // These are the commands always supported by the DHCPv6 server.
    // Please keep the list in alphabetic order.
    CommandMgr::instance().registerCommand("build-report",
        std::bind(&ControlledDhcpv6Srv::commandBuildReportHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-backend-pull",
        std::bind(&ControlledDhcpv6Srv::commandConfigBackendPullHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-get",
        std::bind(&ControlledDhcpv6Srv::commandConfigGetHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-hash-get",
        std::bind(&ControlledDhcpv6Srv::commandConfigHashGetHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-reload",
        std::bind(&ControlledDhcpv6Srv::commandConfigReloadHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-set",
        std::bind(&ControlledDhcpv6Srv::commandConfigSetHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-test",
        std::bind(&ControlledDhcpv6Srv::commandConfigTestHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("config-write",
        std::bind(&ControlledDhcpv6Srv::commandConfigWriteHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("dhcp-enable",
        std::bind(&ControlledDhcpv6Srv::commandDhcpEnableHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("dhcp-disable",
        std::bind(&ControlledDhcpv6Srv::commandDhcpDisableHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("libreload",
        std::bind(&ControlledDhcpv6Srv::commandLibReloadHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("leases-reclaim",
        std::bind(&ControlledDhcpv6Srv::commandLeasesReclaimHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("server-tag-get",
        std::bind(&ControlledDhcpv6Srv::commandServerTagGetHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("shutdown",
        std::bind(&ControlledDhcpv6Srv::commandShutdownHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("status-get",
        std::bind(&ControlledDhcpv6Srv::commandStatusGetHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("version-get",
        std::bind(&ControlledDhcpv6Srv::commandVersionGetHandler, this, ph::_1, ph::_2));

    // Register statistic related commands
    CommandMgr::instance().registerCommand("statistic-get",
        std::bind(&StatsMgr::statisticGetHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-reset",
        std::bind(&StatsMgr::statisticResetHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-remove",
        std::bind(&StatsMgr::statisticRemoveHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-get-all",
        std::bind(&StatsMgr::statisticGetAllHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-reset-all",
        std::bind(&StatsMgr::statisticResetAllHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-remove-all",
        std::bind(&StatsMgr::statisticRemoveAllHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-sample-age-set",
        std::bind(&StatsMgr::statisticSetMaxSampleAgeHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-sample-age-set-all",
        std::bind(&ControlledDhcpv6Srv::commandStatisticSetMaxSampleAgeAllHandler, this, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-sample-count-set",
        std::bind(&StatsMgr::statisticSetMaxSampleCountHandler, ph::_1, ph::_2));

    CommandMgr::instance().registerCommand("statistic-sample-count-set-all",
        std::bind(&ControlledDhcpv6Srv::commandStatisticSetMaxSampleCountAllHandler, this, ph::_1, ph::_2));
}

void ControlledDhcpv6Srv::shutdownServer(int exit_value) {
    setExitValue(exit_value);
    getIOService()->stop();   // Stop ASIO transmissions
    shutdown();               // Initiate DHCPv6 shutdown procedure.
}

ControlledDhcpv6Srv::~ControlledDhcpv6Srv() {
    try {
        MultiThreadingMgr::instance().apply(false, 0, 0);
        LeaseMgrFactory::destroy();
        HostMgr::create();
        cleanup();

        // The closure captures either a shared pointer (memory leak)
        // or a raw pointer (pointing to a deleted object).
        DatabaseConnection::db_lost_callback_ = 0;
        DatabaseConnection::db_recovered_callback_ = 0;
        DatabaseConnection::db_failed_callback_ = 0;

        timer_mgr_->unregisterTimers();

        // Close the command socket (if it exists).
        CommandMgr::instance().closeCommandSocket();

        // Deregister any registered commands (please keep in alphabetic order)
        CommandMgr::instance().deregisterCommand("build-report");
        CommandMgr::instance().deregisterCommand("config-backend-pull");
        CommandMgr::instance().deregisterCommand("config-get");
        CommandMgr::instance().deregisterCommand("config-hash-get");
        CommandMgr::instance().deregisterCommand("config-reload");
        CommandMgr::instance().deregisterCommand("config-set");
        CommandMgr::instance().deregisterCommand("config-test");
        CommandMgr::instance().deregisterCommand("config-write");
        CommandMgr::instance().deregisterCommand("dhcp-disable");
        CommandMgr::instance().deregisterCommand("dhcp-enable");
        CommandMgr::instance().deregisterCommand("leases-reclaim");
        CommandMgr::instance().deregisterCommand("libreload");
        CommandMgr::instance().deregisterCommand("server-tag-get");
        CommandMgr::instance().deregisterCommand("shutdown");
        CommandMgr::instance().deregisterCommand("statistic-get");
        CommandMgr::instance().deregisterCommand("statistic-get-all");
        CommandMgr::instance().deregisterCommand("statistic-remove");
        CommandMgr::instance().deregisterCommand("statistic-remove-all");
        CommandMgr::instance().deregisterCommand("statistic-reset");
        CommandMgr::instance().deregisterCommand("statistic-reset-all");
        CommandMgr::instance().deregisterCommand("statistic-sample-age-set");
        CommandMgr::instance().deregisterCommand("statistic-sample-age-set-all");
        CommandMgr::instance().deregisterCommand("statistic-sample-count-set");
        CommandMgr::instance().deregisterCommand("statistic-sample-count-set-all");
        CommandMgr::instance().deregisterCommand("status-get");
        CommandMgr::instance().deregisterCommand("version-get");

        // LeaseMgr uses IO service to run asynchronous timers.
        LeaseMgr::setIOService(IOServicePtr());

        // HostMgr uses IO service to run asynchronous timers.
        HostMgr::setIOService(IOServicePtr());
    } catch (...) {
        // Don't want to throw exceptions from the destructor. The server
        // is shutting down anyway.
        ;
    }

    server_ = NULL; // forget this instance. There should be no callback anymore
                    // at this stage anyway.
}

void
ControlledDhcpv6Srv::reclaimExpiredLeases(const size_t max_leases,
                                          const uint16_t timeout,
                                          const bool remove_lease,
                                          const uint16_t max_unwarned_cycles) {
    try {
        server_->alloc_engine_->reclaimExpiredLeases6(max_leases, timeout,
                                                      remove_lease,
                                                      max_unwarned_cycles);
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_RECLAIM_EXPIRED_LEASES_FAIL)
            .arg(ex.what());
    }
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME);
}

void
ControlledDhcpv6Srv::deleteExpiredReclaimedLeases(const uint32_t secs) {
    server_->alloc_engine_->deleteExpiredReclaimedLeases6(secs);
    // We're using the ONE_SHOT timer so there is a need to re-schedule it.
    TimerMgr::instance()->setup(CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME);
}

bool
ControlledDhcpv6Srv::dbLostCallback(ReconnectCtlPtr db_reconnect_ctl) {
    if (!db_reconnect_ctl) {
        // This should never happen
        LOG_ERROR(dhcp6_logger, DHCP6_DB_RECONNECT_NO_DB_CTL);
        return (false);
    }

    // Disable service until the connection is recovered.
    if (db_reconnect_ctl->retriesLeft() == db_reconnect_ctl->maxRetries() &&
        db_reconnect_ctl->alterServiceState()) {
        network_state_->disableService(NetworkState::Origin::DB_CONNECTION);
    }

    LOG_INFO(dhcp6_logger, DHCP6_DB_RECONNECT_LOST_CONNECTION);

    // If reconnect isn't enabled log it, initiate a shutdown if needed and
    // return false.
    if (!db_reconnect_ctl->retriesLeft() ||
        !db_reconnect_ctl->retryInterval()) {
        LOG_INFO(dhcp6_logger, DHCP6_DB_RECONNECT_DISABLED)
            .arg(db_reconnect_ctl->retriesLeft())
            .arg(db_reconnect_ctl->retryInterval());
        if (db_reconnect_ctl->exitOnFailure()) {
            shutdownServer(EXIT_FAILURE);
        }
        return (false);
    }

    return (true);
}

bool
ControlledDhcpv6Srv::dbRecoveredCallback(ReconnectCtlPtr db_reconnect_ctl) {
    if (!db_reconnect_ctl) {
        // This should never happen
        LOG_ERROR(dhcp6_logger, DHCP6_DB_RECONNECT_NO_DB_CTL);
        return (false);
    }

    // Enable service after the connection is recovered.
    if (db_reconnect_ctl->alterServiceState()) {
        network_state_->enableService(NetworkState::Origin::DB_CONNECTION);
    }

    LOG_INFO(dhcp6_logger, DHCP6_DB_RECONNECT_SUCCEEDED);

    db_reconnect_ctl->resetRetries();

    return (true);
}

bool
ControlledDhcpv6Srv::dbFailedCallback(ReconnectCtlPtr db_reconnect_ctl) {
    if (!db_reconnect_ctl) {
        // This should never happen
        LOG_ERROR(dhcp6_logger, DHCP6_DB_RECONNECT_NO_DB_CTL);
        return (false);
    }

    LOG_INFO(dhcp6_logger, DHCP6_DB_RECONNECT_FAILED)
            .arg(db_reconnect_ctl->maxRetries());

    if (db_reconnect_ctl->exitOnFailure()) {
        shutdownServer(EXIT_FAILURE);
    }

    return (true);
}

void
ControlledDhcpv6Srv::openSocketsFailedCallback(ReconnectCtlPtr reconnect_ctl) {
    if (!reconnect_ctl) {
        // This should never happen
        LOG_ERROR(dhcp6_logger, DHCP6_OPEN_SOCKETS_NO_RECONNECT_CTL);
        return;
    }

    LOG_INFO(dhcp6_logger, DHCP6_OPEN_SOCKETS_FAILED)
            .arg(reconnect_ctl->maxRetries());

    if (reconnect_ctl->exitOnFailure()) {
        shutdownServer(EXIT_FAILURE);
    }
}

void
ControlledDhcpv6Srv::cbFetchUpdates(const SrvConfigPtr& srv_cfg,
                                    boost::shared_ptr<unsigned> failure_count) {
    // stop thread pool (if running)
    MultiThreadingCriticalSection cs;

    try {
        // Fetch any configuration backend updates since our last fetch.
        server_->getCBControl()->databaseConfigFetch(srv_cfg,
                                                     CBControlDHCPv6::FetchMode::FETCH_UPDATE);
        (*failure_count) = 0;

    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_CB_PERIODIC_FETCH_UPDATES_FAIL)
            .arg(ex.what());

        // We allow at most 10 consecutive failures after which we stop
        // making further attempts to fetch the configuration updates.
        // Let's return without re-scheduling the timer.
        if (++(*failure_count) > 10) {
            LOG_ERROR(dhcp6_logger,
                      DHCP6_CB_PERIODIC_FETCH_UPDATES_RETRIES_EXHAUSTED);
            return;
        }
    }

    // Reschedule the timer to fetch new updates or re-try if
    // the previous attempt resulted in an error.
    if (TimerMgr::instance()->isTimerRegistered("Dhcp6CBFetchTimer")) {
        TimerMgr::instance()->setup("Dhcp6CBFetchTimer");
    }
}

}  // namespace dhcp
}  // namespace isc
