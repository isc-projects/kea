// Copyright (C) 2016-2018 Deutsche Telekom AG.
//
// Author: Cristian Secareanu <cristian.secareanu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <kea_config_tool/config_tool_controller.h>

#include <kea_config_tool/command_options.h>
#include <kea_config_tool/config_tool_log.h>
#include <kea_config_tool/kea_admin.h>
#include <kea_config_tool/server_config.h>

#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/macros.h>

#include <cc/command_interpreter.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcp6/json_config_parser.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/logging.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>
#include <dhcpsrv/srv_config_master_mgr_factory.h>
#include <dhcpsrv/srv_config_mgr_factory.h>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <dirent.h>
#include <stdio.h>

#include <algorithm>
#include <map>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::log;

namespace isc {
namespace config_tool {

/// @brief Defines the application name, it may be used to locate
/// configuration data and appears in log statements.
constexpr char ConfigToolController::config_tool_app_name_[] = "KeaConfigTool";

/// @brief Defines the executable name.
constexpr char ConfigToolController::config_tool_bin_name_[] = "kea-config-tool";

ConfigToolController::ConfigToolController() {
}

ConfigToolController::~ConfigToolController() {
}

ConfigToolController& ConfigToolController::instance() {
    static ConfigToolController config_tool;
    return (config_tool);
}

void ConfigToolController::launch(int argc, char* argv[]) {
    CommandOptions& cmdOptions = CommandOptions::instance();

    try {
        startLogger();

        cmdOptions.parse(argc, argv);

        if (cmdOptions.Param_ShowHelp()) {
            switch (cmdOptions.Param_ShowHelpType()) {
            case CommandOptions::HT_COMMANDS:
                cmdOptions.usage();
                break;
            case CommandOptions::HT_SHARD_CONFIG:
                cmdOptions.usageCmdShardConfig();
                break;
            case CommandOptions::HT_MASTER_CONFIG:
                cmdOptions.usageCmdMasterConfig();
                break;
            }

            return;
        }

        if (cmdOptions.Param_ShowVersion()) {
            showApplicationVersion(cmdOptions.Param_ShowDetailedVersion());
            return;
        }

        if (cmdOptions.Param_ShardSetConfig()) {
            setShardsConfig(cmdOptions.Param_DhcpSpaceType(),
                            cmdOptions.Param_InputDbCredentialsFile(),
                            cmdOptions.Param_ConfigPath(),  //
                            cmdOptions.Param_ItemsList());
            std::cout << "The operation has completed successfully." << std::endl;
            return;
        }

        if (cmdOptions.Param_ShardGetConfig()) {
            getShardsConfig(cmdOptions.Param_DhcpSpaceType(),
                            cmdOptions.Param_InputDbCredentialsFile(),
                            cmdOptions.Param_ConfigPath(),  //
                            cmdOptions.Param_ItemsList());
            std::cout << "The operation has completed successfully." << std::endl;
            return;
        }

        if (cmdOptions.Param_MasterSetServers()) {
            masterSetServers(cmdOptions.Param_DhcpSpaceType(),
                             cmdOptions.Param_InputDbCredentialsFile(),
                             cmdOptions.Param_ConfigPath(),  //
                             cmdOptions.Param_ItemsList());
            std::cout << "The operation has completed successfully." << std::endl;
            return;
        }

        if (cmdOptions.Param_MasterGetServers()) {
            masterGetServers(cmdOptions.Param_DhcpSpaceType(),
                             cmdOptions.Param_InputDbCredentialsFile(),
                             cmdOptions.Param_ConfigPath());
            std::cout << "The operation has completed successfully." << std::endl;
            return;
        }

        if (cmdOptions.Param_RunAdminScript()) {
            KeaAdmin::runAdminScript(cmdOptions.Param_AdminScriptParams());
            std::cout << "The operation has completed successfully." << std::endl;
            return;
        }
    } catch (const InvalidUsage& ex) {
        if (ex.getShowAppHelp()) {
            cmdOptions.usage();
        }
        throw;
    }
}

void ConfigToolController::startLogger() const {
    OutputOption option;
    LoggerManager manager;

    initLogger(config_tool_app_name_, DEBUG, 99, NULL, false);

    // Prepare the objects to define the logging specification
    LoggerSpecification spec(getRootLoggerName(), keaLoggerSeverity(DEBUG), keaLoggerDbglevel(99));

    // If we are running in verbose (debugging) mode
    // we send the output to the console, otherwise
    // by default we send it to the SYSLOG

    if (CommandOptions::instance().Param_VerboseMode()) {
        option.destination = OutputOption::DEST_CONSOLE;
    } else {
        option.destination = OutputOption::DEST_SYSLOG;
    }

    // ... and set the destination
    spec.addOutputOption(option);

    manager.process(spec);
}

std::string ConfigToolController::getVersion(bool extended) {
    std::stringstream tmp;

    tmp << VERSION;
    if (extended) {
        tmp << std::endl << EXTENDED_VERSION << std::endl;
    }

    return (tmp.str());
}

void ConfigToolController::showApplicationVersion(bool show_detailed_version) {
    std::cout << ConfigToolController::getVersion(show_detailed_version) << std::endl;
}

void ConfigToolController::setShardsConfig(DhcpSpaceType dhcp_space,
                                           const std::string& master_config_file,
                                           const std::string& input_shards_directory_path,
                                           const std::set<std::string>& optional_shards_list) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_UPDATE_SHARDS_CONFIG);

    if (dhcp_space == DHCP_SPACE_UNKNOWN) {
        isc_throw(InvalidUsage, "no DHCP space provided. Use the -4|-6 option");
    }

    if (master_config_file.empty() || input_shards_directory_path.empty()) {
        isc_throw(InvalidUsage, "neither the master database config file nor the input config"
                                "directory have been specified");
    }

    std::vector<FileInfo> shard_directories;
    populateDirectories(input_shards_directory_path, true, false, shard_directories);

    std::string credentials_config;
    isc::data::ConstElementPtr dhcp_config =
        ConfigToolController::configureConfigToolConfigSource(dhcp_space, master_config_file);
    SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();
    CfgSrvConfigType::ConfigurationType data_type = srv_cfg->getConfigurationType().type_;
    if (data_type == CfgSrvConfigType::MASTER_DATABASE) {
        if (!ConfigToolController::configureConfigToolId(dhcp_config)) {
            isc_throw(RunTimeFail, "config tool id not set in configuration as"
                                   " mandatory 'instance-id' parameter is missing");
        }

        CfgDbAccessPtr cfg_db = srv_cfg->getCfgDbAccess();
        if (dhcp_space == DHCP_SPACE_V6) {
            cfg_db->setAppendedParameters("universe=6");
        } else if (dhcp_space == DHCP_SPACE_V4) {
            cfg_db->setAppendedParameters("universe=4");
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }
        cfg_db->createSrvMasterCfgManagers();
    } else if (data_type == CfgSrvConfigType::CONFIG_DATABASE) {
        // Get 'config-database' component from the config.
        auto config_database = dhcp_config->get("config-database");
        if (!config_database) {
            isc_throw(isc::BadValue, "no mandatory 'config-database' entry in"
                                     " the configuration");
        }
        credentials_config = config_database->str();
        std::string database_name_key = "name";
        auto database_name_node = config_database->get(database_name_key);
        if (!database_name_node) {
            database_name_key = "keyspace";
            database_name_node = config_database->get(database_name_key);
        }
        if (!database_name_node) {
            isc_throw(isc::BadValue, "neither 'name' nor 'keyspace' entry in 'config-database'");
        }
        if (database_name_node->getType() != isc::data::Element::string) {
            isc_throw(isc::BadValue, "'" + database_name_key + "' is not of type string");
        }
        std::string shard_database = database_name_node->stringValue();
        std::cout << "Searching credentials for " << shard_database << std::endl;
        std::vector<FileInfo> filtered_shard_directories;
        for (int idxShard = 0; idxShard < shard_directories.size(); idxShard++) {
            std::string shard_name = shard_directories[idxShard].name;
            if (shard_database == shard_name) {
                std::cout << "Detected credentials for " << shard_name << std::endl;
                filtered_shard_directories.push_back(shard_directories[idxShard]);
            } else {
                std::cout << "Unknown credentials for shard " << shard_name << std::endl;
            }
        }
        shard_directories = filtered_shard_directories;
    } else {
        isc_throw(RunTimeFail, "unknown configuration type");
    }

    if (shard_directories.size() == 0) {
        isc_throw(RunTimeFail, "there are no shards in the provided directory to match"
                               " used credentials");
    }

    for (int idxShard = 0; idxShard < shard_directories.size(); idxShard++) {
        std::string shard_name = shard_directories[idxShard].name;
        std::string shard_cfg_path = shard_directories[idxShard].full_path;

        if (!optional_shards_list.empty()) {
            std::set<std::string>::const_iterator it = optional_shards_list.find(shard_name);
            if (it == optional_shards_list.end()) {
                continue;
            }
        }

        std::string credentials_cfg_file = shard_cfg_path + "/credentials.json";
        std::string json_cfg_file = shard_cfg_path + "/config.json";
        std::string generic_cfg_file = shard_cfg_path + "/config.generic";
        std::string timestamp_file = shard_cfg_path + "/config.timestamp";

        if (data_type == CfgSrvConfigType::MASTER_DATABASE) {
            parseMasterCredentialsJson(shard_name, credentials_cfg_file, credentials_config);
        }

        updateShardConfig(dhcp_space, shard_name, credentials_config, json_cfg_file,
                          generic_cfg_file, timestamp_file);
    }
}

void ConfigToolController::getShardsConfig(DhcpSpaceType dhcp_space,
                                           const std::string& master_config_file,
                                           const std::string& output_shards_directory_path,
                                           const std::set<std::string>& shards_list) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_GET_SHARDS_CONFIG);

    if (dhcp_space == DHCP_SPACE_UNKNOWN) {
        isc_throw(InvalidUsage, "no DHCP space provided. Use the -4|-6 option");
    }

    if (master_config_file.empty() || output_shards_directory_path.empty()) {
        isc_throw(InvalidUsage, "neither the master database config file nor the output config"
                                "directory have been specified");
    }

    std::set<std::string> filtered_shards_list;
    std::string credentials_config;
    isc::data::ConstElementPtr dhcp_config =
        ConfigToolController::configureConfigToolConfigSource(dhcp_space, master_config_file);
    SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();
    CfgSrvConfigType::ConfigurationType data_type = srv_cfg->getConfigurationType().type_;
    if (data_type == CfgSrvConfigType::MASTER_DATABASE) {
        if (!ConfigToolController::configureConfigToolId(dhcp_config)) {
            isc_throw(RunTimeFail, "config tool id not set in configuration as"
                                   " mandatory 'instance-id' parameter is missing");
        }

        CfgDbAccessPtr cfg_db = srv_cfg->getCfgDbAccess();
        if (dhcp_space == DHCP_SPACE_V6) {
            cfg_db->setAppendedParameters("universe=6");
        } else if (dhcp_space == DHCP_SPACE_V4) {
            cfg_db->setAppendedParameters("universe=4");
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }
        cfg_db->createSrvMasterCfgManagers();
        filtered_shards_list = shards_list;
    } else if (data_type == CfgSrvConfigType::CONFIG_DATABASE) {
        // Get 'config-database' component from the config.
        auto config_database = dhcp_config->get("config-database");
        if (!config_database) {
            isc_throw(isc::BadValue, "no mandatory 'config-database' entry in"
                                     " the configuration");
        }
        credentials_config = config_database->str();
        std::string database_name_key = "name";
        auto database_name_node = config_database->get(database_name_key);
        if (!database_name_node) {
            database_name_key = "keyspace";
            database_name_node = config_database->get(database_name_key);
        }
        if (!database_name_node) {
            isc_throw(isc::BadValue, "neither 'name' nor 'keyspace' entry in 'config-database'");
        }
        if (database_name_node->getType() != isc::data::Element::string) {
            isc_throw(isc::BadValue, "'" + database_name_key + "' is not of type string");
        }
        std::string shard_database = database_name_node->stringValue();
        std::set<std::string>::const_iterator it = shards_list.find(shard_database);
        if (it != shards_list.end()) {
            std::cout << "Detected credentials for " << shard_database << std::endl;
            filtered_shards_list.insert(database_name_node->stringValue());
        }
        for (std::string const& shard_name : shards_list) {
            std::set<std::string>::const_iterator it = filtered_shards_list.find(shard_name);
            if (it == filtered_shards_list.end()) {
                std::cout << "Unknown credentials for shard " << shard_name << std::endl;
            }
        }
    } else {
        isc_throw(RunTimeFail, "unknown configuration type");
    }

    std::string const tab = "    ";
    std::string const tabs[] = {"", tab, tab + tab, tab + tab + tab};

    for (std::string const& shard_name : filtered_shards_list) {
        std::string output_config_path = output_shards_directory_path;

        if (data_type == CfgSrvConfigType::MASTER_DATABASE) {
            std::string tool_id = CfgMgr::instance().getStagingCfg()->getInstanceId();

            // Read the contents from database
            SrvConfigMasterInfoPtr tool_config;
            if (dhcp_space == DHCP_SPACE_V6) {
                tool_config =
                    SrvConfigMasterMgrFactory::instance().getConfig6(tool_id + "@" + shard_name);
            } else if (dhcp_space == DHCP_SPACE_V4) {
                tool_config =
                    SrvConfigMasterMgrFactory::instance().getConfig4(tool_id + "@" + shard_name);
            } else {
                isc_throw(isc::BadValue, "invalid DHCP space type");
            }

            if (tool_config == SrvConfigMasterInfoPtr()) {
                std::cout << "No credentials found in master database for config tool id: "
                          << tool_id << " for shard " << shard_name << std::endl;
                continue;
            }
            credentials_config = tool_config->config_database_;
        }

        if (output_config_path.length() > 0 &&
            output_config_path[output_config_path.length() - 1] != '/') {
            output_config_path += '/';
        }
        output_config_path += shard_name;

        if (!ConfigToolController::directoryExists(output_config_path)) {
            if (!ConfigToolController::createDirectory(output_config_path)) {
                isc_throw(RunTimeFail, "could not create the '" << output_config_path
                                                                << "' directory in order to store "
                                                                   "the shard configuration");
            }
        }

        getShardGenericConfig(dhcp_space, shard_name, credentials_config, output_config_path);
        getShardJsonConfig(dhcp_space, shard_name, credentials_config, output_config_path);

        std::ostringstream json_data;
        json_data << "{" << std::endl
                  << tabs[1] << "\"config-database\": " << credentials_config << std::endl
                  << "}" << std::endl;

        boost::filesystem::path fileFullPath(output_config_path);
        boost::filesystem::path credentialsFileFullPath = fileFullPath;
        credentialsFileFullPath += "/credentials.json";

        std::ofstream credentials_file(credentialsFileFullPath.c_str());
        // Check for permissions to write into the file
        if (!credentials_file.is_open()) {
            isc_throw(RunTimeFail, "cannot write the configuration file in the specified path.");
        }
        credentials_file << json_data.str();
        credentials_file.close();
    }
}

void ConfigToolController::getShardGenericConfig(DhcpSpaceType dhcp_space,
                                                 const std::string& shard_name,
                                                 const std::string& credentials_config,
                                                 const std::string& output_config_path) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_GET_GENERIC_CONFIG);
    std::cout << "Starting to retrieve the GENERIC configuration for shard '" << shard_name
              << "'..." << std::endl;

    if (shard_name.empty() || output_config_path.empty()) {
        isc_throw(InvalidUsage, "neither the shard name nor the output config directory have"
                                "been specified");
    }

    SrvConfigInfoPtr configData =
        ServerConfig::readShardGenericConfig(shard_name, dhcp_space, credentials_config);

    if (configData == SrvConfigInfoPtr()) {
        isc_throw(RunTimeFail, "could not obtain configuration data from database.");
    }

    std::string timestampFileFullPath = output_config_path + "/config.timestamp";
    std::ofstream timestamp_file(timestampFileFullPath.c_str());
    // Check for permissions to write into the file
    if (!timestamp_file.is_open()) {
        isc_throw(RunTimeFail, "cannot write the version file in the specified path.");
    }
    timestamp_file << configData->timestamp_;
    timestamp_file.close();

    boost::filesystem::path genericFileFullPath(output_config_path);
    genericFileFullPath += "/config.generic";
    std::ofstream generic_file(genericFileFullPath.c_str());
    // Check for permissions to write into the file
    if (!generic_file.is_open()) {
        isc_throw(RunTimeFail, "cannot write the generic file in the specified path.");
    }
    generic_file << configData->generic_data_;
    generic_file.close();
}

void ConfigToolController::getShardJsonConfig(DhcpSpaceType dhcp_space,
                                              const std::string& shard_name,
                                              const std::string& credentials_config,
                                              const std::string& output_config_path) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_GET_JSON_CONFIG);
    std::cout << "Starting to retrieve the JSON configuration for shard '" << shard_name << "'..."
              << std::endl;

    if (shard_name.empty() || output_config_path.empty()) {
        isc_throw(InvalidUsage, "neither the shard name nor the output config directory have "
                                "been specified");
    }

    SrvConfigInfoPtr configData =
        ServerConfig::readShardJsonConfig(shard_name, dhcp_space, credentials_config);

    if (configData == SrvConfigInfoPtr()) {
        isc_throw(RunTimeFail, "could not obtain configuration data from database.");
    }

    std::string timestampFileFullPath = output_config_path + "/config.timestamp";
    std::ofstream timestamp_file(timestampFileFullPath.c_str());
    // Check for permissions to write into the file
    if (!timestamp_file.is_open()) {
        isc_throw(RunTimeFail, "cannot write the version file in the specified path.");
    }
    timestamp_file << configData->timestamp_;
    timestamp_file.close();

    boost::filesystem::path jsonFileFullPath(output_config_path);
    jsonFileFullPath += "/config.json";
    std::ofstream json_file(jsonFileFullPath.c_str());
    // Check for permissions to write into the file
    if (!json_file.is_open()) {
        isc_throw(RunTimeFail, "cannot write the JSON file in the specified path.");
    }
    json_file << configData->json_data_;
    json_file.close();
}

void ConfigToolController::updateShardConfig(DhcpSpaceType dhcp_space,
                                             const std::string& shard_name,
                                             const std::string& credentials_config,
                                             const std::string& input_json_config_file,
                                             const std::string& input_generic_config_file,
                                             const std::string& input_timestamp_config_file) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_UPDATE_CONFIG).arg(shard_name);
    std::cout << "Starting to update the configuration for shard '" << shard_name << "'..."
              << std::endl;

    if (shard_name.empty()) {
        isc_throw(InvalidUsage, "the shard name cannot be empty");
    }

    if (input_json_config_file.empty() || input_generic_config_file.empty() ||
        input_timestamp_config_file.empty()) {
        isc_throw(InvalidUsage, "master input database credentials file, "
                                "the json config file, the generic config file and "
                                "the time timestamp file cannot be empty");
    }

    std::ifstream json_file(input_json_config_file.c_str(), std::ifstream::in);
    // Check if the file has been opened
    if (!json_file.is_open()) {
        isc_throw(RunTimeFail, "cannot open json file " << input_json_config_file.c_str());
    }
    std::string json_config((std::istreambuf_iterator<char>(json_file)),
                            (std::istreambuf_iterator<char>()));
    json_file.close();

    std::ifstream generic_file(input_generic_config_file.c_str(), std::ifstream::in);
    // Check if the file has been opened
    if (!generic_file.is_open()) {
        isc_throw(RunTimeFail, "cannot open generic file" << input_generic_config_file.c_str());
    }
    std::string generic_config((std::istreambuf_iterator<char>(generic_file)),
                               (std::istreambuf_iterator<char>()));
    generic_file.close();

    std::string config_timestamp;
    std::ifstream timestamp_file(input_timestamp_config_file.c_str(), std::ifstream::in);
    // Check if the file has been opened.
    // The timestamp file may miss.
    if (timestamp_file.is_open()) {
        config_timestamp = std::string((std::istreambuf_iterator<char>(timestamp_file)),
                                       (std::istreambuf_iterator<char>()));
        timestamp_file.close();
    }

    IfaceMgr::instance().setServerMode(false);

    isc::data::ConstElementPtr answer, dhcp_element, json;

    json = isc::data::Element::fromJSON(json_config, true);

    if (dhcp_space == DHCP_SPACE_V6) {
        dhcp_element = json->get("Dhcp6");
        if (dhcp_element) {
            boost::scoped_ptr<Dhcpv6Srv> server(new Dhcpv6Srv(0));
            answer = configureDhcp6Server(*server, dhcp_element);
        }
    } else if (dhcp_space == DHCP_SPACE_V4) {
        dhcp_element = json->get("Dhcp4");
        if (dhcp_element) {
            boost::scoped_ptr<Dhcpv4Srv> server(new Dhcpv4Srv(0));
            answer = configureDhcp4Server(*server, dhcp_element);
        }
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }

    // Check answer.
    if (dhcp_element) {
        try {
            int rcode = 0;
            auto returnedAnswer = isc::config::parseAnswer(rcode, answer);
            if (rcode != 0) {
                isc_throw(RunTimeFail, "updateShardConfig() failed: " << *returnedAnswer);
            }
        } catch (const std::exception& ex) {
            isc_throw(RunTimeFail, "updateShardConfig() failed: " << ex.what());
        }
    }

    ServerConfig::updateShardConfig(shard_name, dhcp_space, config_timestamp, json_config,
                                    generic_config, credentials_config);

    HostMgr::instance().syncReservations();
}

void ConfigToolController::masterSetServers(DhcpSpaceType dhcp_space,
                                            const std::string& master_config_file,
                                            const std::string& input_servers_directory_path,
                                            const std::set<std::string>& optional_shards_list) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_MASTER_UPDATE_SERVERS);
    std::cout << "Starting to update the configuration in the master database..." << std::endl;

    if (dhcp_space == DHCP_SPACE_UNKNOWN) {
        isc_throw(InvalidUsage, "No DHCP space provided");
    }

    if (master_config_file.empty() || input_servers_directory_path.empty()) {
        isc_throw(InvalidUsage, "neither the master database config file "
                                "nor the input config directory cannot be empty");
    }

    isc::data::ConstElementPtr dhcp_config =
        ConfigToolController::configureConfigToolConfigSource(dhcp_space, master_config_file);
    SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();
    if (srv_cfg->getConfigurationType().type_ != CfgSrvConfigType::MASTER_DATABASE) {
        isc_throw(isc::BadValue, "no mandatory 'master-database' entry in the configuration");
    }

    if (!ConfigToolController::configureConfigToolId(dhcp_config)) {
        isc_throw(RunTimeFail, "config tool id not set in configuration as"
                               " mandatory 'instance-id' parameter is missing");
    }

    std::string tool_id = CfgMgr::instance().getStagingCfg()->getInstanceId();

    CfgDbAccessPtr cfg_db = srv_cfg->getCfgDbAccess();
    if (dhcp_space == DHCP_SPACE_V6) {
        cfg_db->setAppendedParameters("universe=6");
    } else if (dhcp_space == DHCP_SPACE_V4) {
        cfg_db->setAppendedParameters("universe=4");
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }
    cfg_db->createSrvMasterCfgManagers();

    std::vector<FileInfo> shard_directories;
    populateDirectories(input_servers_directory_path, true, false, shard_directories);

    if (shard_directories.size() == 0) {
        isc_throw(RunTimeFail, "there are no shards in the provided directory");
    }

    ServerConfig::ServerMasterConfigContainer serversMasterConfig;

    for (int idxShard = 0; idxShard < shard_directories.size(); idxShard++) {
        std::string shard_name = shard_directories[idxShard].name;
        std::string shard_cfg_path = shard_directories[idxShard].full_path;

        if (!optional_shards_list.empty()) {
            std::set<std::string>::const_iterator it = optional_shards_list.find(shard_name);
            if (it == optional_shards_list.end()) {
                continue;
            }
        }

        std::string credentials_cfg_file = shard_cfg_path + "/credentials.json";
        std::string credentials_config;
        parseMasterCredentialsJson(shard_name, credentials_cfg_file, credentials_config);
        std::string servers_config_file = shard_cfg_path + "/servers.json";
        parseMasterServersJson(shard_name, servers_config_file, serversMasterConfig);
        ServerConfig::ServerMasterConfigPtr config_tool_config =
            boost::make_shared<ServerConfig::ServerMasterConfig>();
        config_tool_config->config_database_ = credentials_config;
        config_tool_config->config_database_name_ = shard_name;
        config_tool_config->instance_id_ = tool_id + "@" + shard_name;
        serversMasterConfig.push_back(config_tool_config);
    }

    SrvConfigMasterMgrFactory::instance().startTransaction();
    try {
        ServerConfig::updateSrvMasterConfig(dhcp_space, serversMasterConfig);
    } catch (const std::exception& ex) {
        SrvConfigMasterMgrFactory::instance().rollback();
        throw;
    }
    SrvConfigMasterMgrFactory::instance().commit();
}

void ConfigToolController::masterGetServers(DhcpSpaceType dhcp_space,
                                            const std::string& master_config_file,
                                            const std::string& output_shards_directory_path) {
    LOG_INFO(config_tool_logger, CONFIG_TOOL_MASTER_GET_SERVERS);

    std::cout << "Starting to retrieve the configuration from the master database..." << std::endl;

    if (dhcp_space == DHCP_SPACE_UNKNOWN) {
        isc_throw(InvalidUsage, "No DHCP space provided");
    }

    if (master_config_file.empty() || output_shards_directory_path.empty()) {
        isc_throw(InvalidUsage, "neither the master database config file "
                                "nor the output config directory cannot be empty");
    }

    isc::data::ConstElementPtr dhcp_config =
        ConfigToolController::configureConfigToolConfigSource(dhcp_space, master_config_file);
    SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();
    if (srv_cfg->getConfigurationType().type_ != CfgSrvConfigType::MASTER_DATABASE) {
        isc_throw(isc::BadValue, "no mandatory 'master-database' entry in the configuration");
    }

    if (!ConfigToolController::configureConfigToolId(dhcp_config)) {
        isc_throw(RunTimeFail, "config tool id not set in configuration as"
                               " mandatory 'instance-id' parameter is missing");
    }

    CfgDbAccessPtr cfg_db = srv_cfg->getCfgDbAccess();
    if (dhcp_space == DHCP_SPACE_V6) {
        cfg_db->setAppendedParameters("universe=6");
    } else if (dhcp_space == DHCP_SPACE_V4) {
        cfg_db->setAppendedParameters("universe=4");
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }
    cfg_db->createSrvMasterCfgManagers();

    SrvConfigMasterMgrFactory::instance().startTransaction();
    try {
        std::set<std::string> shards_list;
        ServerConfig::getMasterSrvConfigShardsName(dhcp_space, shards_list);

        for (std::string const& shard_name : shards_list) {
            masterGetShardServers(dhcp_space, shard_name, output_shards_directory_path);
        }
    } catch (const std::exception& ex) {
        SrvConfigMasterMgrFactory::instance().rollback();
        throw;
    }
    SrvConfigMasterMgrFactory::instance().commit();
}

void ConfigToolController::masterGetShardServers(DhcpSpaceType dhcp_space,
                                                 const std::string& shard_name,
                                                 const std::string& output_shards_directory_path) {
    std::cout << "Starting to retrieve the configuration for shard '" << shard_name
              << "' from the master database..." << std::endl;

    std::vector<SrvConfigMasterInfoPtr> server_info;
    ServerConfig::getMasterSrvConfig(dhcp_space, shard_name, server_info);

    std::string json_data = masterSrvConfigDataToJSON(server_info);
    std::string credentials_data = masterCredentialsToJSON(server_info);

    std::string output_config_path = output_shards_directory_path;

    if (output_config_path.length() > 0 &&
        output_config_path[output_config_path.length() - 1] != '/') {
        output_config_path += '/';
    }
    output_config_path += shard_name;

    if (!ConfigToolController::directoryExists(output_config_path)) {
        if (!ConfigToolController::createDirectory(output_config_path)) {
            isc_throw(RunTimeFail, "could not create the '" << output_config_path
                                                            << "' directory in order to store the "
                                                               "shard configuration");
        }
    }

    boost::filesystem::path fileFullPath(output_config_path);

    boost::filesystem::path serversFileFullPath = fileFullPath;
    serversFileFullPath += "/servers.json";

    std::ofstream servers_file(serversFileFullPath.c_str());
    // Check for permissions to write into the file
    if (!servers_file.is_open()) {
        isc_throw(RunTimeFail, "cannot write the configuration file in the specified path.");
    }
    servers_file << json_data;
    servers_file.close();

    boost::filesystem::path credentialsFileFullPath = fileFullPath;
    credentialsFileFullPath += "/credentials.json";

    std::ofstream credentials_file(credentialsFileFullPath.c_str());
    // Check for permissions to write into the file
    if (!credentials_file.is_open()) {
        isc_throw(RunTimeFail, "cannot write the configuration file in the specified path.");
    }
    credentials_file << credentials_data;
    credentials_file.close();

    return;
}

bool ConfigToolController::configureConfigToolId(isc::data::ConstElementPtr config_set) {
    // Check if an 'instance-id' parameter is provided.
    isc::data::ConstElementPtr tool_id = config_set->get("instance-id");
    if (tool_id) {
        std::string id;
        if (tool_id->getValue(id)) {
            CfgMgr::instance().getStagingCfg()->getInstanceId() = id;
            return true;
        }
    }

    return false;
}

isc::data::ConstElementPtr
ConfigToolController::configureConfigToolConfigSource(DhcpSpaceType dhcp_space,
                                                      const std::string& file_name) {
    isc::data::ConstElementPtr json;
    isc::data::ConstElementPtr dhcp_node;

    try {
        if (file_name.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(isc::BadValue, "the file name is empty");
        }

        // Read contents of the file and parse it as JSON
        json = isc::data::Element::fromJSONFile(file_name, true);
        if (!json) {
            isc_throw(isc::BadValue, "no configuration found");
        }

        // Let's do sanity check before we call json->get() which
        // works only for map.
        if (json->getType() != isc::data::Element::map) {
            isc_throw(isc::BadValue,
                      "configuration file is expected to be a map, i.e., start with { and end with "
                      "} and contain at least an entry called 'Dhcp6/Dchp4' that itself is a map. "
                          << file_name
                          << " is a valid JSON, but its top element is not a map. Did you forget "
                             "to add { } around your configuration?");
        }

        // Get Dhcp6/Dhcp4 component from the config

        if (dhcp_space == DHCP_SPACE_V6) {
            dhcp_node = json->get("Dhcp6");
        } else if (dhcp_space == DHCP_SPACE_V4) {
            dhcp_node = json->get("Dhcp4");
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }

        if (!dhcp_node) {
            isc_throw(isc::BadValue, "no mandatory 'Dhcp' entry in the configuration");
        }

        SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();

        // check if a 'configuration-type' parameter is provided
        isc::data::ConstElementPtr cfg_type_elem = dhcp_node->get("configuration-type");
        if (cfg_type_elem) {
            std::string type;
            if (cfg_type_elem->getValue(type)) {
                // Valid values for "configuration-type" : "database" and "file"
                if (type == "database") {
                    // The configuration type specifies that the server configuration should be
                    // read from the database.

                    // Parse the 'master-database' parameter in order to update the config manager
                    // with the configuration database type and credentials.
                    isc::data::ConstElementPtr config_database = dhcp_node->get("master-database");
                    if (config_database) {
                        // Update the config manager with the server configuration type
                        srv_cfg->getConfigurationType().type_ = CfgSrvConfigType::MASTER_DATABASE;

                        DbAccessParser parser(DBType::MASTER_DB);
                        CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                        parser.parse(cfg_db_access, config_database);
                    } else {
                        // There has not been specified a "master-database" parameter.
                        // Check if a "config-database" parameter has been specified
                        isc::data::ConstElementPtr config_database =
                            dhcp_node->get("config-database");
                        if (config_database) {
                            // Update the config manager with the server configuration type
                            srv_cfg->getConfigurationType().type_ =
                                CfgSrvConfigType::CONFIG_DATABASE;

                            DbAccessParser parser(DBType::CONFIG_DB);
                            CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                            parser.parse(cfg_db_access, config_database);
                        }
                    }
                } else if (type == "file") {
                    // Update the config manager with the server configuration type
                    srv_cfg->getConfigurationType().type_ = CfgSrvConfigType::FILE;
                    isc_throw(isc::BadValue, "invalid value for 'configuration-type' parameter, "
                                             "only 'database' type supported.");
                } else {
                    // Update the config manager with the server configuration type
                    srv_cfg->getConfigurationType().type_ = CfgSrvConfigType::UNKNOWN;
                    isc_throw(
                        isc::BadValue,
                        "invalid value for 'configuration-type' parameter, can't process config.");
                }
            }
        } else {
            isc_throw(isc::BadValue,
                      "no mandatory 'configuration-type' entry in the configuration");
        }
    } catch (const std::exception& ex) {
        isc_throw(isc::BadValue, "configuration error using database credentials file '"
                                     << file_name << "': " << ex.what());
    }

    return dhcp_node;
}

void ConfigToolController::populateDirectories(const std::string& directory_path,
                                               bool populateDirectories,
                                               bool populateFiles,
                                               std::vector<FileInfo>& directoryContent) {
    DIR* dir;
    dirent* ent;
    struct stat st;

    directoryContent.clear();

    // Open directory.
    dir = opendir(directory_path.c_str());
    if (dir == NULL) {
        isc_throw(isc::BadValue,
                  "the specified directory does not exists '" << directory_path << "'");
    }

    while ((ent = readdir(dir)) != NULL) {
        // Skip current directory '.'.
        if (ent->d_name[0] == '.') {
            continue;
        }

        // Form full filename.
        std::string const full_file_name = directory_path + '/' + ent->d_name;

        // For any error, continue.
        if (stat(full_file_name.c_str(), &st) == -1) {
            continue;
        }

        // Check if it should be populated.
        const bool is_directory = (st.st_mode & S_IFDIR) != 0;
        if ((is_directory && populateDirectories) || (!is_directory && populateFiles)) {
            FileInfo directory;
            directory.name = ent->d_name;
            directory.full_path = full_file_name;
            directoryContent.push_back(directory);
        }
    }

    closedir(dir);
}

// This function appends data to existing servers information in
// the 'serversMasterConfig' parameter.
// The 'serversMasterConfig' parameter is a vector of shared pointers
// in order to avoid to keep too much information on the stack.
void ConfigToolController::parseMasterServersJson(
    const std::string& directory_shard_name,
    const std::string& servers_config_file,
    ServerConfig::ServerMasterConfigContainer& serversMasterConfig) {
    try {
        // Basic sanity check: file name must not be empty.
        if (servers_config_file.empty()) {
            isc_throw(isc::BadValue, "the file name is empty");
        }

        // Read contents of the file and parse it as JSON.
        auto json = isc::data::Element::fromJSONFile(servers_config_file, true);
        if (!json) {
            isc_throw(isc::BadValue, "no configuration found");
        }

        // Let's do sanity check before we call json->get() which
        // works only for map.
        if (json->getType() != isc::data::Element::map) {
            isc_throw(isc::BadValue,
                      "configuration file is expected to be a map, i.e., start with { and end with "
                      "} and contain an entry called 'master-config' that itself is a map. "
                          << servers_config_file
                          << " is a valid JSON, but its top element is not a map. Did you forget "
                             "to add { } around your configuration?");
        }

        // Get 'config-database' component from the config.
        auto config_database = json->get("config-database");
        if (!config_database) {
            isc_throw(isc::BadValue, "no mandatory 'config-database' entry in the configuration");
        }
        std::string database_name_key = "name";
        auto database_name_node = config_database->get(database_name_key);
        if (!database_name_node) {
            database_name_key = "keyspace";
            database_name_node = config_database->get(database_name_key);
        }
        if (!database_name_node) {
            isc_throw(isc::BadValue, "neither 'name' nor 'keyspace' entry in 'config-database'");
        }
        if (database_name_node->getType() != isc::data::Element::string) {
            isc_throw(isc::BadValue, "'" + database_name_key + "' is not of type string");
        }

        if (database_name_node->stringValue() != directory_shard_name) {
            isc_throw(isc::BadValue, "the shard's directory name '"
                                         << directory_shard_name
                                         << "' should be the same as the shard's database name "
                                         << database_name_node->stringValue()
                                         << "' specified in `config-database`.");
        }

        // Get 'master-config' component from the config.
        auto master_config_node = json->get("master-config");
        if (!master_config_node) {
            isc_throw(isc::BadValue, "no mandatory 'master-config' entry in the configuration");
        }

        for (isc::data::ConstElementPtr server_config_node : master_config_node->listValue()) {
            ServerConfig::ServerMasterConfigPtr server_config =
                boost::make_shared<ServerConfig::ServerMasterConfig>();

            server_config->config_database_ = config_database->str();
            server_config->config_database_name_ = directory_shard_name;

            for (ConfigPair param : server_config_node->mapValue()) {
                std::string entry(param.first);
                isc::data::ConstElementPtr value = param.second;
                if (entry == "instance-id") {
                    if (value->getType() != isc::data::Element::string) {
                        isc_throw(isc::BadValue, "instance-id is not of type string");
                    }
                    server_config->instance_id_ = value->stringValue();

                } else if (entry == "server-config") {
                    server_config->server_config_ = value->str();
                }
            }

            serversMasterConfig.push_back(server_config);
        }
    } catch (const std::exception& ex) {
        isc_throw(isc::BadValue, "configuration error using server master config file '"
                                     << servers_config_file << "': " << ex.what());
    }
}

// This function receives credentials data for shard into credentialsConfig
void ConfigToolController::parseMasterCredentialsJson(const std::string& directory_shard_name,
                                                      const std::string& credentials_config_file,
                                                      std::string& credentials_config) {
    try {
        // Basic sanity check: file name must not be empty.
        if (credentials_config_file.empty()) {
            isc_throw(isc::BadValue, "the file name is empty");
        }

        // Read contents of the file and parse it as JSON.
        auto json = isc::data::Element::fromJSONFile(credentials_config_file, true);
        if (!json) {
            isc_throw(isc::BadValue, "no configuration found");
        }

        // Let's do sanity check before we call json->get() which
        // works only for map.
        if (json->getType() != isc::data::Element::map) {
            isc_throw(isc::BadValue,
                      "configuration file is expected to be a map, i.e., start with { and end with "
                      "} and contain an entry called 'master-config' that itself is a map. "
                          << credentials_config_file
                          << " is a valid JSON, but its top element is not a map. Did you forget "
                             "to add { } around your configuration?");
        }

        // Get 'config-database' component from the config.
        auto config_database = json->get("config-database");
        if (!config_database) {
            isc_throw(isc::BadValue, "no mandatory 'config-database' entry in"
                                     " the configuration");
        }
        std::string database_name_key = "name";
        auto database_name_node = config_database->get(database_name_key);
        if (!database_name_node) {
            database_name_key = "keyspace";
            database_name_node = config_database->get(database_name_key);
        }
        if (!database_name_node) {
            isc_throw(isc::BadValue, "neither 'name' nor 'keyspace' entry in 'config-database'");
        }
        if (database_name_node->getType() != isc::data::Element::string) {
            isc_throw(isc::BadValue, "'" + database_name_key + "' is not of type string");
        }

        if (database_name_node->stringValue() != directory_shard_name) {
            isc_throw(isc::BadValue, "the shard's directory name '"
                                         << directory_shard_name
                                         << "' should be the same as the shard's database name "
                                         << database_name_node->stringValue()
                                         << "' specified in `config-database`.");
        }

        credentials_config = config_database->str();
    } catch (const std::exception& ex) {
        isc_throw(isc::BadValue, "configuration error using server master config file '"
                                     << credentials_config_file << "': " << ex.what());
    }
}

std::string
ConfigToolController::masterSrvConfigDataToJSON(std::vector<SrvConfigMasterInfoPtr>& servers) {
    // Tabs
    std::string const tab = "    ";
    std::string const tabs[] = {"", tab, tab + tab, tab + tab + tab};

    // Start serializing root-level JSON.
    std::ostringstream json_data;
    json_data << "{" << std::endl << tabs[1] << "\"master-config\": [";

    // Serialize all 'master-config' elements.
    bool first = true;
    std::string config_database;
    for (SrvConfigMasterInfoPtr const& server : servers) {
        if (server->instance_id_ == CfgMgr::instance().getStagingCfg()->getInstanceId() + "@" +
                                        server->config_database_name_) {
            continue;
        }
        // Populate config-database while checking to be the same for all master servers.
        if (config_database.empty()) {
            // if 'config-database' was indeed empty than it should have been an empty map "{}".
            if (server->config_database_.empty()) {
                isc_throw(isc::BadValue,
                          "'config-database' is empty, would result in invalid JSON");
            }
            config_database = server->config_database_;
        } else if (config_database != server->config_database_) {
            isc_throw(isc::BadValue, "expected the same 'config-database' for all master servers, "
                                     "but they are different: "
                                         << std::endl
                                         << config_database << std::endl
                                         << server->config_database_ << std::endl);
        }

        // Add the comma between elements.
        if (first) {
            first = false;
        } else {
            json_data << ",";
        }

        // Add the element's children.
        json_data << std::endl
                  << tabs[2] << "{" << std::endl
                  << tabs[3] << "\"server-config\": " << server->server_config_ << "," << std::endl
                  << tabs[3] << "\"instance-id\": \"" << server->instance_id_ << "\"," << std::endl
                  << tabs[3] << "\"update_timestamp\": \"" << server->timestamp_ << "\""
                  << std::endl
                  << tabs[2] << "}";
    }

    // End serializing root-level JSON.
    json_data << std::endl  //
              << tabs[1] << "]," << std::endl
              << tabs[1] << "\"config-database\": " << config_database << std::endl
              << "}" << std::endl;

    return json_data.str();
}

std::string
ConfigToolController::masterCredentialsToJSON(std::vector<SrvConfigMasterInfoPtr>& servers) {
    // Tabs
    std::string const tab = "    ";
    std::string const tabs[] = {"", tab, tab + tab, tab + tab + tab};

    std::string config_database;
    for (SrvConfigMasterInfoPtr const& server : servers) {
        if (server->instance_id_ == CfgMgr::instance().getStagingCfg()->getInstanceId() + "@" +
                                        server->config_database_name_) {
            config_database = server->config_database_;
            break;
        }
    }

    if (config_database.empty()) {
        isc_throw(isc::BadValue, "'config-database' is empty, would result in invalid JSON");
    }

    // Serializing root-level JSON.
    std::ostringstream json_data;
    json_data << "{" << std::endl
              << tabs[1] << "\"config-database\": " << config_database << std::endl
              << "}" << std::endl;

    return json_data.str();
}

bool ConfigToolController::directoryExists(const std::string& path) {
    DIR* pDir;
    bool bExists = false;

    pDir = opendir(path.c_str());

    if (pDir != NULL) {
        bExists = true;
        closedir(pDir);
    }

    return bExists;
}

bool ConfigToolController::createDirectory(const std::string& path) {
    int status;
    // read/write/search permissions for owner and group,
    // and with read/search permissions for others
    status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    return status == 0;
}

}  // namespace config_tool
}  // namespace isc
