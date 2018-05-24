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
#include <kea_config_tool/server_config.h>

#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>
#include <dhcpsrv/srv_config_master_mgr_factory.h>
#include <dhcpsrv/srv_config_mgr_factory.h>
#include <kea_config_tool/config_tool_controller.h>
#include <kea_config_tool/config_tool_log.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr/make_shared.hpp>

using namespace std;
using namespace isc::dhcp;

namespace isc {
namespace config_tool {

ServerConfig::ServerConfig() {
}

ServerConfig::~ServerConfig() {
}

SrvConfigInfoPtr ServerConfig::readShardGenericConfig(const std::string& config_database_name,
                                                      DhcpSpaceType dhcp_space,
                                                      const std::string& credentials_config) {
    auto stagingCfg = CfgMgr::instance().getStagingCfg();
    CfgSrvConfigType& configurationType = stagingCfg->getConfigurationType();

    isc::data::ConstElementPtr configDatabase = isc::data::Element::fromJSON(credentials_config);
    if (!configDatabase) {
        isc_throw(isc::BadValue, "no configuration found");
    }

    // Update the config manager with the server configuration type
    configurationType.type_ = CfgSrvConfigType::CONFIG_DATABASE;

    DbAccessParser parser(DBType::CONFIG_DB);
    CfgDbAccessPtr stagingCfgDbAccess = stagingCfg->getCfgDbAccess();
    parser.parse(stagingCfgDbAccess, configDatabase);

    // Re-open configuration database with new parameters.
    if (dhcp_space == DHCP_SPACE_V6) {
        stagingCfgDbAccess->setAppendedParameters("universe=6");
    } else if (dhcp_space == DHCP_SPACE_V4) {
        stagingCfgDbAccess->setAppendedParameters("universe=4");
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }

    try {
        stagingCfgDbAccess->createSrvCfgManagers();
    } catch (const std::exception& ex) {
        isc_throw(RunTimeFail, "unable to open the database: " << config_database_name
                                                               << ". Reason: " << ex.what());
    }

    SrvConfigInfoPtr configData;

    SrvConfigMgrFactory::instance().startTransaction();
    try {
        // Read the contents from database.
        if (dhcp_space == DHCP_SPACE_V6) {
            configData = SrvConfigMgrFactory::instance().getGenericConfig6();
        } else if (dhcp_space == DHCP_SPACE_V4) {
            configData = SrvConfigMgrFactory::instance().getGenericConfig4();
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }
    } catch (const std::exception& ex) {
        SrvConfigMgrFactory::instance().rollback();
        throw;
    }
    SrvConfigMgrFactory::instance().commit();

    if (configData == SrvConfigInfoPtr()) {
        isc_throw(RunTimeFail, "no entry found in database");
    }

    return configData;
}

SrvConfigInfoPtr ServerConfig::readShardJsonConfig(const std::string& config_database_name,
                                                   DhcpSpaceType dhcp_space,
                                                   const std::string& credentials_config) {
    auto stagingCfg = CfgMgr::instance().getStagingCfg();
    CfgSrvConfigType& configurationType = stagingCfg->getConfigurationType();

    isc::data::ConstElementPtr configDatabase = isc::data::Element::fromJSON(credentials_config);
    if (!configDatabase) {
        isc_throw(isc::BadValue, "no configuration found");
    }

    // Update the config manager with the server configuration type
    configurationType.type_ = CfgSrvConfigType::CONFIG_DATABASE;

    DbAccessParser parser(DBType::CONFIG_DB);
    CfgDbAccessPtr stagingCfgDbAccess = stagingCfg->getCfgDbAccess();
    parser.parse(stagingCfgDbAccess, configDatabase);

    // Re-open configuration database with new parameters.
    if (dhcp_space == DHCP_SPACE_V6) {
        stagingCfgDbAccess->setAppendedParameters("universe=6");
    } else if (dhcp_space == DHCP_SPACE_V4) {
        stagingCfgDbAccess->setAppendedParameters("universe=4");
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }

    try {
        stagingCfgDbAccess->createSrvCfgManagers();
    } catch (const std::exception& ex) {
        isc_throw(RunTimeFail, "unable to open the database: " << config_database_name
                                                               << ". Reason: " << ex.what());
    }

    SrvConfigInfoPtr configData;

    SrvConfigMgrFactory::instance().startTransaction();
    try {
        // Read the contents from database
        if (dhcp_space == DHCP_SPACE_V6) {
            configData = SrvConfigMgrFactory::instance().getJsonConfig6();
        } else if (dhcp_space == DHCP_SPACE_V4) {
            configData = SrvConfigMgrFactory::instance().getJsonConfig4();
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }
    } catch (const std::exception& ex) {
        SrvConfigMgrFactory::instance().rollback();
        throw;
    }
    SrvConfigMgrFactory::instance().commit();

    if (configData == SrvConfigInfoPtr()) {
        isc_throw(RunTimeFail, "no entry found in database");
    }

    return configData;
}

void ServerConfig::updateShardConfig(const std::string& config_database_name,
                                     DhcpSpaceType dhcp_space,
                                     const std::string& config_timestamp,
                                     const std::string& json_config,
                                     const std::string& generic_config,
                                     const std::string& credentials_config) {
    auto stagingCfg = CfgMgr::instance().getStagingCfg();
    CfgSrvConfigType& configurationType = stagingCfg->getConfigurationType();

    isc::data::ConstElementPtr configDatabase = isc::data::Element::fromJSON(credentials_config);
    if (!configDatabase) {
        isc_throw(isc::BadValue, "no configuration found");
    }

    // Update the config manager with the server configuration type
    configurationType.type_ = CfgSrvConfigType::CONFIG_DATABASE;

    DbAccessParser parser(DBType::CONFIG_DB);
    CfgDbAccessPtr stagingCfgDbAccess = stagingCfg->getCfgDbAccess();
    parser.parse(stagingCfgDbAccess, configDatabase);

    // Re-open configuration database with new parameters.
    if (dhcp_space == DHCP_SPACE_V6) {
        stagingCfgDbAccess->setAppendedParameters("universe=6");
    } else if (dhcp_space == DHCP_SPACE_V4) {
        stagingCfgDbAccess->setAppendedParameters("universe=4");
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }

    try {
        stagingCfgDbAccess->createSrvCfgManagers();
    } catch (const std::exception& ex) {
        isc_throw(RunTimeFail, "unable to open the database: " << config_database_name
                                                               << ". Reason: " << ex.what());
    }

    // Write the contents to database
    bool res = false;
    int64_t timestamp = 0;

    stringstream timestampStream(config_timestamp);
    timestampStream >> timestamp;

    SrvConfigMgrFactory::instance().startTransaction();
    try {
        if (dhcp_space == DHCP_SPACE_V6) {
            res = SrvConfigMgrFactory::instance().updateConfig6(timestamp, json_config,
                                                                generic_config);
        } else if (dhcp_space == DHCP_SPACE_V4) {
            res = SrvConfigMgrFactory::instance().updateConfig4(timestamp, json_config,
                                                                generic_config);
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }
    } catch (const std::exception& ex) {
        SrvConfigMgrFactory::instance().rollback();
        throw;
    }
    SrvConfigMgrFactory::instance().commit();

    if (res == false) {
        isc_throw(RunTimeFail, "could not update the database "
                               "server configuration because the timestamp of the database record "
                               "has been changed");
    }
}

void ServerConfig::updateSrvMasterConfig(DhcpSpaceType dhcp_space,
                                         ServerMasterConfigContainer& serversMasterConfig) {
    if (dhcp_space == DHCP_SPACE_V6) {
        SrvConfigMasterMgrFactory::instance().clearServersConfig6();
    } else if (dhcp_space == DHCP_SPACE_V4) {
        SrvConfigMasterMgrFactory::instance().clearServersConfig4();
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }

    for (ServerMasterConfigPtr server_config : serversMasterConfig) {
        if (dhcp_space == DHCP_SPACE_V6) {
            SrvConfigMasterMgrFactory::instance().addServerConfig6(
                server_config->instance_id_, server_config->server_config_,
                server_config->config_database_, server_config->config_database_name_);
        } else if (dhcp_space == DHCP_SPACE_V4) {
            SrvConfigMasterMgrFactory::instance().addServerConfig4(
                server_config->instance_id_, server_config->server_config_,
                server_config->config_database_, server_config->config_database_name_);
        } else {
            isc_throw(isc::BadValue, "invalid DHCP space type");
        }
    }
}

void ServerConfig::getMasterSrvConfigShardsName(DhcpSpaceType dhcp_space,
                                                std::set<std::string>& shards_list) {
    if (dhcp_space == DHCP_SPACE_V6) {
        SrvConfigMasterMgrFactory::instance().getServersConfig6ShardsName(shards_list);
    } else if (dhcp_space == DHCP_SPACE_V4) {
        SrvConfigMasterMgrFactory::instance().getServersConfig4ShardsName(shards_list);
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }
}

void ServerConfig::getMasterSrvConfig(DhcpSpaceType dhcp_space,
                                      const std::string& config_database_name,
                                      std::vector<SrvConfigMasterInfoPtr>& server_info) {
    if (dhcp_space == DHCP_SPACE_V6) {
        SrvConfigMasterMgrFactory::instance().getConfig6(config_database_name, server_info);
    } else if (dhcp_space == DHCP_SPACE_V4) {
        SrvConfigMasterMgrFactory::instance().getConfig4(config_database_name, server_info);
    } else {
        isc_throw(isc::BadValue, "invalid DHCP space type");
    }
}

}  // namespace config_tool
}  // namespace isc
