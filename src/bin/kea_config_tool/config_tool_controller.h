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

#ifndef CONFIG_TOOL_H
#define CONFIG_TOOL_H

#include <kea_config_tool/server_config.h>

#include <dhcpsrv/cfg_db_access.h>
#include <exceptions/exceptions.h>

#include <set>
#include <string>
#include <vector>

namespace isc {
namespace config_tool {

/// @brief Exception thrown when the command line is invalid.
class InvalidUsage : public isc::Exception {
public:
    InvalidUsage(const char* file, size_t line, const char* what, bool show_app_help = false)
        : isc::Exception(file, line, what), show_app_help_(show_app_help) {
    }

    bool getShowAppHelp() const {
        return show_app_help_;
    }

private:
    bool show_app_help_;
};

/// @brief Exceptions thrown when a method is unable to manipulate
/// (remove or rename) a file.
class RunTimeFail : public isc::Exception {
public:
    RunTimeFail(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

class ConfigToolController {
public:
    /// @brief Defines the application name, it may be used to locate
    /// configuration data and appears in log statements.
    static const char config_tool_app_name_[];

    /// @brief Defines the executable name, by convention this should match
    /// the executable name.
    static const char config_tool_bin_name_[];

    struct FileInfo {
        std::string name;
        std::string full_path;
    };

public:
    ConfigToolController();
    ~ConfigToolController();

    /// ConfigToolController is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// \return the only existing instance of command options
    static ConfigToolController& instance();

    /// @brief Acts as the primary entry point to start execution
    /// of the process.
    ///
    /// Provides the control logic to upload and download server configuration
    /// file on database back-ends
    ///
    /// -# parse command line arguments
    /// -# verify that it is the only instance
    /// -# parse the database credentials file provided and connects to database
    /// -# upload/download server configuration file
    /// -# exit to the caller
    ///
    /// @param argc Number of strings in the @c argv array.
    /// @param argv Array of arguments passed in via the program's main
    /// function.
    ///
    /// @throw InvalidUsage if the command line parameters are invalid.
    /// @throw BadValue if wrong values are provided in the database credentials
    /// file
    /// @throw RunTimeFail if an unexpected error occurs at runtime
    /// (e.g. cannot connect to the database)
    void launch(int argc, char* argv[]);

    ///@brief Start up the logging system
    ///
    /// @param test_mode indicates if we have have been started from the test
    /// system (true) or are running normally (false)
    void startLogger() const;

protected:
    /// @brief returns Kea version.
    static std::string getVersion(bool extended);

    static void showApplicationVersion(bool show_detailed_version);

    static void setShardsConfig(DhcpSpaceType dhcp_space,
                                const std::string& master_config_file,
                                const std::string& input_shards_directory_path,
                                const std::set<std::string>& optional_shards_list);

    static void getShardsConfig(DhcpSpaceType dhcp_space,
                                const std::string& master_config_file,
                                const std::string& output_shards_directory_path,
                                const std::set<std::string>& shards_list);

    static void getShardGenericConfig(DhcpSpaceType dhcp_space,
                                      const std::string& config_database_name,
                                      const std::string& credentials_config,
                                      const std::string& output_config_path);

    static void getShardJsonConfig(DhcpSpaceType dhcp_space,
                                   const std::string& config_database_name,
                                   const std::string& credentials_config,
                                   const std::string& output_config_path);

    static void updateShardConfig(DhcpSpaceType dhcp_space,
                                  const std::string& config_database_name,
                                  const std::string& credentials_config,
                                  const std::string& input_json_config_file,
                                  const std::string& input_generic_config_file,
                                  const std::string& input_timestamp_config_file);

    static void masterSetServers(DhcpSpaceType dhcp_space,
                                 const std::string& master_config_file,
                                 const std::string& input_servers_directory_path,
                                 const std::set<std::string>& optional_shards_list);

    static void masterGetServers(DhcpSpaceType dhcp_space,
                                 const std::string& master_config_file,
                                 const std::string& output_shards_directory_path);

    static void masterGetShardServers(DhcpSpaceType dhcp_space,
                                      const std::string& config_database_name,
                                      const std::string& output_shards_directory_path);

    static isc::data::ConstElementPtr configureConfigToolConfigSource(DhcpSpaceType dhcp_space,
                                                                      const std::string& file_name);

    static bool configureConfigToolId(isc::data::ConstElementPtr config_set);

    /// @brief Utility methods
    /// @{
    static void populateDirectories(const std::string& directory_path,
                                    bool listFiles,
                                    bool listDirectories,
                                    std::vector<FileInfo>& directoryContent);

    static void
    parseMasterServersJson(const std::string& directory_shard_name,
                           const std::string& servers_config_file,
                           ServerConfig::ServerMasterConfigContainer& serversMasterConfig);

    static void parseMasterCredentialsJson(const std::string& directory_shard_name,
                                           const std::string& credentials_config_file,
                                           std::string& credentials_config);

    static std::string
    masterSrvConfigDataToJSON(std::vector<isc::dhcp::SrvConfigMasterInfoPtr>& server_info);

    static std::string
    masterCredentialsToJSON(std::vector<isc::dhcp::SrvConfigMasterInfoPtr>& server_info);

    static bool directoryExists(const std::string& path);
    static bool createDirectory(const std::string& path);
    /// @}
};

}  // namespace config_tool
}  // namespace isc

#endif  // CONFIG_TOOL_H
