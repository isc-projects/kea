// Copyright (C) 2016 Deutsche Telekom AG.
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

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/srv_config_mgr_factory.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_srv_config_mgr.h>
#endif
#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_srv_config_mgr.h>
#endif
#ifdef HAVE_CQL
#include <dhcpsrv/cql_srv_config_mgr.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <utility>

using namespace std;

namespace isc {
namespace dhcp {

boost::scoped_ptr<SrvConfigMgr>& SrvConfigMgrFactory::getConfigurationMgrPtr() {
    static boost::scoped_ptr<SrvConfigMgr> configurationMgrPtr;
    return (configurationMgrPtr);
}

void SrvConfigMgrFactory::create(const std::string& dbaccess) {
    const std::string type = "type";

    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(dbaccess);
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);

    // Is "type" present?
    if (parameters.find(type) == parameters.end()) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_NOTYPE_DB).arg(dbaccess);
        isc_throw(InvalidParameter, "Database configuration parameters do not "
                                    "contain the 'type' keyword");
    }

// Yes, check what it is.
#ifdef HAVE_MYSQL
    if (parameters[type] == string("mysql")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_DB).arg(redacted);
        getConfigurationMgrPtr().reset(new MySqlSrvConfigMgr(parameters));
        return;
    }
#endif
#ifdef HAVE_PGSQL
    if (parameters[type] == string("postgresql")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_DB).arg(redacted);
        getConfigurationMgrPtr().reset(new PgSqlSrvConfigMgr(parameters));
        return;
    }
#endif
#ifdef HAVE_CQL
    if (parameters[type] == string("cql")) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_CQL_DB).arg(redacted);
        getConfigurationMgrPtr().reset(new CqlSrvConfigMgr(parameters));
        return;
    }
#endif

    // Get here on no match
    LOG_ERROR(dhcpsrv_logger, DHCPSRV_UNKNOWN_DB).arg(parameters[type]);
    isc_throw(InvalidType, "Database access parameter 'type' does "
                           "not specify a supported database backend");
}

void SrvConfigMgrFactory::destroy() {
    // Destroy current lease manager.  This is a no-op if no lease manager
    // is available.
    if (getConfigurationMgrPtr()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CLOSE_DB)
            .arg(getConfigurationMgrPtr()->getType());
    }
    getConfigurationMgrPtr().reset();
}

SrvConfigMgr& SrvConfigMgrFactory::instance() {
    SrvConfigMgr* cfgptr = getConfigurationMgrPtr().get();
    if (cfgptr == NULL) {
        isc_throw(NoServerConfigManager, "no current server configuration manager is available");
    }
    return (*cfgptr);
}

bool SrvConfigMgrFactory::initialized() {
    SrvConfigMgr* cfgptr = getConfigurationMgrPtr().get();
    return (cfgptr != NULL);
}

}  // namespace dhcp
}  // namespace isc
