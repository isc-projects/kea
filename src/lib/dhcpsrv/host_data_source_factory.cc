// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/hosts_log.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_host_data_source.h>
#endif

#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_host_data_source.h>
#endif

#ifdef HAVE_CQL
#include <dhcpsrv/cql_host_data_source.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <utility>

using namespace std;

namespace isc {
namespace dhcp {

map<string, HostDataSourceFactory::Factory> HostDataSourceFactory::map_;

void
HostDataSourceFactory::add(HostDataSourceList& sources,
                           const string& dbaccess) {
    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters =
            DatabaseConnection::parse(dbaccess);

    // Get the database type and open the corresponding database
    DatabaseConnection::ParameterMap::iterator it = parameters.find("type");
    if (it == parameters.end()) {
        isc_throw(InvalidParameter, "Host database configuration does not "
                  "contain the 'type' keyword");
    }

    string db_type = it->second;
    auto index = map_.find(db_type);

    // No match?
    if (index == map_.end()) {
        isc_throw(InvalidType, "Hosts database access parameter 'type': " <<
                  db_type << " is invalid");
    }

    // Call the factory and push the pointer on sources.
    sources.push_back(boost::shared_ptr<BaseHostDataSource>(index->second(parameters)));

    // Check the factory did not return NULL.
    if (!sources.back()) {
        sources.pop_back();
        isc_throw(Unexpected, "Hosts database " << db_type <<
                  " factory returned NULL");
    }
}

bool
HostDataSourceFactory::del(HostDataSourceList& sources,
                           const string& db_type) {
    for (auto it = sources.begin(); it != sources.end(); ++it) {
        if ((*it)->getType() != db_type) {
            continue;
        }
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, HOSTS_CFG_CLOSE_HOST_DATA_SOURCE)
            .arg(db_type);
        sources.erase(it);
        return (true);
    }
    return (false);
}

bool
HostDataSourceFactory::registerFactory(const string& db_type,
                                       const Factory& factory) {
    if (map_.count(db_type)) {
        return (false);
    }
    map_.insert(pair<string, Factory>(db_type, factory));
    return (true);
}

bool
HostDataSourceFactory::deregisterFactory(const string& db_type) {
    auto index = map_.find(db_type);
    if (index != map_.end()) {
        map_.erase(index);
        return (true);
    } else {
        return (false);
    }
}

}  // namespace dhcp
}  // namespace isc

//
// Register database backends
//

using namespace isc::dhcp;

namespace {

#ifdef HAVE_MYSQL
struct MySqlHostDataSourceInit {
    // Constructor registers
    MySqlHostDataSourceInit() {
        HostDataSourceFactory::registerFactory("mysql", factory);
    }

    // Destructor deregisters
    ~MySqlHostDataSourceInit() {
        HostDataSourceFactory::deregisterFactory("mysql");
    }

    // Factory class method
    static BaseHostDataSource*
    factory(const DatabaseConnection::ParameterMap& parameters) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        return (new MySqlHostDataSource(parameters));
    }
};

// Database backend will be registered at object initialization
MySqlHostDataSourceInit mysql_init;
#endif

#ifdef HAVE_PGSQL
struct PgSqlHostDataSourceInit {
    // Constructor registers
    PgSqlHostDataSourceInit() {
        HostDataSourceFactory::registerFactory("postgresql", factory);
    }

    // Destructor deregisters
    ~PgSqlHostDataSourceInit() {
        HostDataSourceFactory::deregisterFactory("postgresql");
    }

    // Factory class method
    static BaseHostDataSource*
    factory(const DatabaseConnection::ParameterMap& parameters) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        return (new PgSqlHostDataSource(parameters));
    }
};

// Database backend will be registered at object initialization
PgSqlHostDataSourceInit mysql_init;
#endif

#ifdef HAVE_CQL
struct CqlHostDataSourceInit {
    // Constructor registers
    CqlHostDataSourceInit() {
        HostDataSourceFactory::registerFactory("cql", factory);
    }

    // Destructor deregisters
    ~CqlHostDataSourceInit() {
        HostDataSourceFactory::deregisterFactory("cql");
    }

    // Factory class method
    static BaseHostDataSource*
    factory(const DatabaseConnection::ParameterMap& parameters) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_CQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        return (new CqlHostDataSource(parameters));
    }
};

// Database backend will be registered at object initialization
CqlHostDataSourceInit mysql_init;
#endif

} // end of anonymous namespace
