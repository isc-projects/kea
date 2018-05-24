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

#ifndef COMMAND_OPTIONS_H
#define COMMAND_OPTIONS_H

#include <boost/noncopyable.hpp>
#include <kea_config_tool/server_config.h>

#include <set>
#include <string>

namespace isc {
namespace config_tool {

/// \brief Command Options.
///
/// This class is responsible for parsing the command-line and storing the
/// specified options.
///
class CommandOptions : public boost::noncopyable {
public:
    enum HelpType { HT_COMMANDS, HT_SHARD_CONFIG, HT_MASTER_CONFIG };

    CommandOptions();
    ~CommandOptions();

    /// CommandOptions is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// \return the only existing instance of command options
    static CommandOptions& instance();

    /// @brief Prints Kea Config Tool Usage
    ///
    void usage();
    void usageCommands();
    void usageCmdShardConfig();
    void usageCmdMasterConfig();

    void parse(int argc, char* argv[]);

    bool Param_ShowHelp() const {
        return show_help_;
    }
    bool Param_ShowVersion() const {
        return show_version_;
    }
    bool Param_ShowDetailedVersion() const {
        return show_detailed_version_;
    }
    bool Param_VerboseMode() const {
        return verbose_mode_;
    }
    bool Param_RunAdminScript() const {
        return run_admin_script_;
    }
    std::string Param_AdminScriptParams() const {
        return admin_script_params_;
    }
    std::string Param_InputDbCredentialsFile() const {
        return input_db_credentials_file_;
    }
    std::string Param_ConfigPath() const {
        return config_path_;
    }
    bool Param_ShardSetConfig() const {
        return shard_set_config_;
    }
    bool Param_ShardGetConfig() const {
        return shard_get_config_;
    }
    bool Param_MasterSetServers() const {
        return master_set_servers_;
    }
    bool Param_MasterGetServers() const {
        return master_get_servers_;
    }
    DhcpSpaceType Param_DhcpSpaceType() const {
        return dhcp_space_type_;
    }
    HelpType Param_ShowHelpType() const {
        return show_help_type_;
    }
    const std::set<std::string>& Param_ItemsList() const {
        return items_list_;
    }
    void resetInternalData();

protected:
    void parseShardConfigCmdLine(int argc, char* argv[], int& paramIdx);
    void parseMasterConfigCmdLine(int argc, char* argv[], int& paramIdx);
    void parseDatabaseInitCmdLine(int argc, char* argv[], int& paramIdx);
    bool getParameter(int argc, char* argv[], int paramIdx, std::string& paramValue);
    bool getUnparsedCommandLine(int argc, char* argv[], int paramIdx, std::string& remainedLine);

    bool show_help_;
    bool show_version_;
    bool show_detailed_version_;
    bool verbose_mode_;
    bool run_admin_script_;
    std::string admin_script_params_;
    std::string input_db_credentials_file_;
    std::string config_path_;
    std::set<std::string> items_list_;
    bool shard_set_config_;
    bool shard_get_config_;
    bool master_set_servers_;
    bool master_get_servers_;
    DhcpSpaceType dhcp_space_type_;
    HelpType show_help_type_;
};

}  // namespace config_tool
}  // namespace isc

#endif  // COMMAND_OPTIONS_H
