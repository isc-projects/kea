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
#include <kea_config_tool/command_options.h>
#include <kea_config_tool/config_tool_controller.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>

namespace isc {
namespace config_tool {

CommandOptions::CommandOptions() {
    resetInternalData();
}

CommandOptions::~CommandOptions() {
}

CommandOptions& CommandOptions::instance() {
    static CommandOptions options;
    return (options);
}

void CommandOptions::usage() {
    switch (show_help_type_) {
    case HT_COMMANDS:
        usageCommands();
        break;
    case HT_SHARD_CONFIG:
        usageCmdShardConfig();
        break;
    case HT_MASTER_CONFIG:
        usageCmdMasterConfig();
        break;
    default:
        isc_throw(InvalidUsage, "unknown help type: " << static_cast<int>(show_help_type_));
    }
}

void CommandOptions::usageCommands() {
    std::cout << ConfigToolController::config_tool_bin_name_
              << " [options...] [<command> [args...]]" << std::endl
              << std::endl;

    std::cout << "  Options:" << std::endl
              << "\t  -v: print version number and exit" << std::endl
              << "\t  -V: print detailed version number and exit" << std::endl
              << "\t  -d: debug mode with extra verbose data" << std::endl
              << "\t  -h: print this help" << std::endl
              << std::endl;

    std::cout << "  Commands ('command name' -h for help):" << std::endl
              << "\t  -dbinit: Database initialization. " << std::endl
              << "\t  -shard: Operations with shards databases." << std::endl
              << "\t  -master: Operation with master databases." << std::endl;
}

void CommandOptions::usageCmdShardConfig() {
    std::cout << "  NAME " << std::endl
              << "\t -shard: Configures a shard database" << std::endl
              << std::endl;

    std::cout << "  SYNOPSIS " << std::endl
              << "\t -shard -set-config -4|-6 master-config-file "
                 "input-shards-directory-path [list-of-shards]"
              << std::endl
              << "\t -shard -get-config -4|-6 master-config-file "
                 "output-shards-directory-path list-of-shards"
              << std::endl
              << std::endl;

    std::cout << "  DESCRIPTION" << std::endl
              << "\t -set-config writes the provided server configuration "
                 "into shards."
              << std::endl
              << "\t -get-config retrieves server configuration from shards "
                 "and writes it locally."
              << std::endl
              << std::endl;

    std::cout << "  OPTIONS" << std::endl
              << "\t -4|-6 - specifies DHCPV6 or DHCPV4 operation." << std::endl
              << "\t master-config-file - configuration file which provides the "
                 "master database backend credentials."
              << std::endl
              << "\t input-shards-directory-path - The path from the "
                 "shards configuration is loaded."
              << std::endl
              << "\t output-shards-directory-path - The path where the "
                 "shards configuration will be stored."
              << std::endl
              << "\t list-of-shards - the shards names (comma separated) for "
                 "which the command is applied"
              << std::endl
              << "\t\t\t (for the case when list-of-shards is optional and no "
                 "value "
              << std::endl
              << "\t\t\t is provided then the command is applied for all found "
                 "shards)."
              << std::endl;
}

void CommandOptions::usageCmdMasterConfig() {
    std::cout << "  NAME " << std::endl
              << "\t -master - Configures a master database" << std::endl
              << std::endl;

    std::cout << "  SYNOPSIS " << std::endl
              << "\t -master -set-servers -4|-6 master-config-file "
                 "input-shards-directory-path [list-of-shards]"
              << std::endl
              << "\t -master -get-servers -4|-6 master-config-file "
                 "output-shards-directory-path"
              << std::endl
              << std::endl;

    std::cout << "  DESCRIPTION" << std::endl
              << "\t -set-servers write the provided servers configuration "
                 "into master database."
              << std::endl
              << "\t -get-servers retrieves servers configuration from the "
                 "master database and writes them locally."
              << std::endl
              << std::endl;

    std::cout << "  OPTIONS" << std::endl
              << "\t -4|-6 - specifies DHCPV6 or DHCPV4 operation." << std::endl
              << "\t master-config-file - configuration file which provides the "
                 "master database backend credentials."
              << std::endl
              << "\t input-shards-directory-path - The path from the "
                 "master configuration is loaded."
              << std::endl
              << "\t output-shards-directory-path - The path where the "
                 "master configuration will be stored."
              << std::endl
              << "\t list-of-shards - the shards names (comma separated) for "
                 "which the command is applied"
              << std::endl
              << "\t\t\t (for the case when list-of-shards is optional and not "
                 "specified"
              << std::endl
              << "\t\t\t is provided then the command is applied for all found "
                 "shards)."
              << std::endl;
}

void CommandOptions::parse(int argc, char* argv[]) {
    resetInternalData();

    if (argc == 1) {
        isc_throw_1(InvalidUsage, "missing command", true);
        return;
    }

    int paramIdx = 1;

    std::string param;
    while (getParameter(argc, argv, paramIdx++, param)) {
        if (param.compare("-h") == 0) {
            show_help_ = true;
            show_help_type_ = HT_COMMANDS;
        } else if (param.compare("-d") == 0) {
            verbose_mode_ = true;
        } else if (param.compare("-v") == 0) {
            show_version_ = true;
            show_detailed_version_ = false;
        } else if (param.compare("-V") == 0) {
            show_version_ = true;
            show_detailed_version_ = true;
        } else if (param.compare("-dbinit") == 0) {
            parseDatabaseInitCmdLine(argc, argv, paramIdx);
        } else if (param.compare("-shard") == 0) {
            parseShardConfigCmdLine(argc, argv, paramIdx);
        } else if (param.compare("-master") == 0) {
            parseMasterConfigCmdLine(argc, argv, paramIdx);
        } else {
            isc_throw(InvalidUsage, "unknown parameter '" << param << "'");
        }
    }
}

void CommandOptions::resetInternalData() {
    dhcp_space_type_ = DHCP_SPACE_UNKNOWN;
    run_admin_script_ = false;
    admin_script_params_ = "";
    verbose_mode_ = false;
    input_db_credentials_file_ = "";
    config_path_ = "";
    shard_set_config_ = false;
    shard_get_config_ = false;
    master_set_servers_ = false;
    master_get_servers_ = false;
    show_help_ = false;
    show_version_ = false;
    show_detailed_version_ = false;
    show_help_type_ = HT_COMMANDS;
    items_list_.clear();
}

void CommandOptions::parseShardConfigCmdLine(int argc, char* argv[], int& paramIdx) {
    std::string param;
    while (getParameter(argc, argv, paramIdx++, param)) {
        if (param.compare("-h") == 0) {
            show_help_ = true;
            show_help_type_ = HT_SHARD_CONFIG;
        } else if (param.compare("-get-config") == 0) {
            shard_get_config_ = true;
            std::string param;
            if (!getParameter(argc, argv, paramIdx++, param)) {
                isc_throw(InvalidUsage, "missing DHCP space parameter");
            }
            if (param.compare("-4") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V4;
            } else if (param.compare("-6") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V6;
            } else {
                isc_throw(InvalidUsage, "unknown parameter '" << param << "'");
            }
            if (!getParameter(argc, argv, paramIdx++, input_db_credentials_file_)) {
                isc_throw(InvalidUsage, "missing parameter 'input_db_credentials_file'");
            }
            if (!getParameter(argc, argv, paramIdx++, config_path_)) {
                isc_throw(InvalidUsage, "missing parameter 'output_config_path'");
            }
            std::string shards_list;
            if (!getParameter(argc, argv, paramIdx++, shards_list)) {
                isc_throw(InvalidUsage, "missing parameter 'list_of_shards'");
            }
            boost::char_separator<char> sep(",");
            boost::tokenizer<boost::char_separator<char>> tokens(shards_list, sep);
            for (const std::string& shard : tokens) {
                if (!shard.empty()) {
                    items_list_.insert(shard);
                }
            }
        } else if (param.compare("-set-config") == 0) {
            shard_set_config_ = true;
            std::string param;
            if (!getParameter(argc, argv, paramIdx++, param)) {
                isc_throw(InvalidUsage, "missing DHCP space parameter");
            }
            if (param.compare("-4") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V4;
            } else if (param.compare("-6") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V6;
            } else {
                isc_throw(InvalidUsage, "missing DHCP space parameter");
            }
            if (!getParameter(argc, argv, paramIdx++, input_db_credentials_file_)) {
                isc_throw(InvalidUsage, "missing parameter 'master-config-file'");
            }
            if (!getParameter(argc, argv, paramIdx++, config_path_)) {
                isc_throw(InvalidUsage, "missing parameter 'shards-directory-path'");
            }
            std::string shards_list;
            if (!getParameter(argc, argv, paramIdx++, shards_list)) {
                return;
            }
            boost::char_separator<char> sep(",");
            boost::tokenizer<boost::char_separator<char>> tokens(shards_list, sep);
            for (const std::string& shard : tokens) {
                if (!shard.empty()) {
                    items_list_.insert(shard);
                }
            }
        } else {
            isc_throw(InvalidUsage, "unknown parameter '" << param << "'");
        }
    }
}

void CommandOptions::parseMasterConfigCmdLine(int argc, char* argv[], int& paramIdx) {
    std::string param;
    while (getParameter(argc, argv, paramIdx++, param)) {
        if (param.compare("-h") == 0) {
            show_help_ = true;
            show_help_type_ = HT_MASTER_CONFIG;
        } else if (param.compare("-set-servers") == 0) {
            master_set_servers_ = true;
            std::string param;
            if (!getParameter(argc, argv, paramIdx++, param)) {
                isc_throw(InvalidUsage, "missing DHCP space parameter");
            }
            if (param.compare("-4") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V4;
            } else if (param.compare("-6") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V6;
            } else {
                isc_throw(InvalidUsage, "unknown parameter '" << param << "'");
            }
            if (!getParameter(argc, argv, paramIdx++, input_db_credentials_file_)) {
                isc_throw(InvalidUsage, "missing parameter 'input_db_credentials_file'");
            }
            if (!getParameter(argc, argv, paramIdx++, config_path_)) {
                isc_throw(InvalidUsage, "missing parameter 'input_config_path'");
            }

            std::string shards_list;
            if (!getParameter(argc, argv, paramIdx++, shards_list)) {
                return;
            }
            boost::char_separator<char> sep(",");
            boost::tokenizer<boost::char_separator<char>> tokens(shards_list, sep);
            for (const std::string& shard : tokens) {
                if (!shard.empty()) {
                    items_list_.insert(shard);
                }
            }
        } else if (param.compare("-get-servers") == 0) {
            master_get_servers_ = true;
            std::string param;
            if (!getParameter(argc, argv, paramIdx++, param)) {
                isc_throw(InvalidUsage, "missing DHCP space parameter");
            }
            if (param.compare("-4") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V4;
            } else if (param.compare("-6") == 0) {
                dhcp_space_type_ = DHCP_SPACE_V6;
            } else {
                isc_throw(InvalidUsage, "unknown parameter '" << param << "'");
            }
            if (!getParameter(argc, argv, paramIdx++, input_db_credentials_file_)) {
                isc_throw(InvalidUsage, "missing parameter 'input_db_credentials_file'");
            }
            if (!getParameter(argc, argv, paramIdx++, config_path_)) {
                isc_throw(InvalidUsage, "missing parameter 'output_config_path'");
            }
        } else {
            isc_throw(InvalidUsage, "unknown parameter '" << param << "'");
        }
    }
}

void CommandOptions::parseDatabaseInitCmdLine(int argc, char* argv[], int& paramIdx) {
    run_admin_script_ = true;
    // There is no need to throw exception if the function returns false
    // because admin script parameters may miss.
    getUnparsedCommandLine(argc, argv, paramIdx, admin_script_params_);
    // All parameters are sent to kea-admin script, so there are
    // no more parameters to parse
    paramIdx = argc;
}

bool CommandOptions::getParameter(int argc, char* argv[], int paramIdx, std::string& paramValue) {
    if (paramIdx >= argc) {
        return false;
    }
    paramValue = std::string(argv[paramIdx]);
    return true;
}

bool CommandOptions::getUnparsedCommandLine(int argc,
                                            char* argv[],
                                            int paramIdx,
                                            std::string& unparsed) {
    if (paramIdx >= argc) {
        return false;
    }
    unparsed = "";
    for (int nIdx = paramIdx; nIdx < argc; nIdx++) {
        if (nIdx > paramIdx) {
            unparsed += ' ';
        }
        unparsed += std::string(argv[nIdx]);
    }
    return true;
}

}  // namespace config_tool
}  // namespace isc
