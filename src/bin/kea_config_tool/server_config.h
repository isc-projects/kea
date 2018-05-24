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

#ifndef DHCP_SERVER_CONFIG_H
#define DHCP_SERVER_CONFIG_H

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/srv_config_master_mgr.h>
#include <dhcpsrv/srv_config_mgr.h>

#include <string>
#include <vector>

namespace isc {
namespace config_tool {

/* DHCP space types: */
enum DhcpSpaceType { DHCP_SPACE_UNKNOWN, DHCP_SPACE_V4, DHCP_SPACE_V6 };

class ServerConfig {
public:
    struct ServerMasterConfig {
        std::string instance_id_;
        std::string server_config_;
        std::string config_database_;
        std::string config_database_name_;
    };

    typedef boost::shared_ptr<ServerMasterConfig> ServerMasterConfigPtr;
    typedef std::vector<ServerConfig::ServerMasterConfigPtr> ServerMasterConfigContainer;

private:
    ServerConfig();
    ~ServerConfig();

public:
    static isc::dhcp::SrvConfigInfoPtr
    readShardGenericConfig(const std::string& config_database_name,
                           DhcpSpaceType dhcp_space,
                           const std::string& credentials_config);

    static isc::dhcp::SrvConfigInfoPtr readShardJsonConfig(const std::string& config_database_name,
                                                           DhcpSpaceType dhcp_space,
                                                           const std::string& credentials_config);

    static void updateShardConfig(const std::string& config_database_name,
                                  DhcpSpaceType dhcp_space,
                                  const std::string& config_timestamp,
                                  const std::string& json_config,
                                  const std::string& generic_config,
                                  const std::string& credentials_config);

    static void updateSrvMasterConfig(DhcpSpaceType dhcp_space,
                                      ServerMasterConfigContainer& serversMasterConfig);

    static void getMasterSrvConfigShardsName(DhcpSpaceType dhcp_space,
                                             std::set<std::string>& shards_list);

    static void getMasterSrvConfig(DhcpSpaceType dhcp_space,
                                   const std::string& config_database_name,
                                   std::vector<isc::dhcp::SrvConfigMasterInfoPtr>& server_info);
};

}  // namespace config_tool
}  // namespace isc

#endif  // DHCP_SERVER_CONFIG_H
