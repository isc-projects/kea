// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/hosts_log.h>
#include <log/logger_support.h>

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

using namespace isc::db;
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
        if ((db_type == "mysql") ||
            (db_type == "postgresql") ||
            (db_type == "cql")) {
            string with = (db_type == "postgresql" ? "pgsql" : db_type);
            isc_throw(InvalidType, "The type of host backend: '" << db_type
                      << "' is not compiled in. Did you forget to use --with-"
                      << with << " during compilation?");
        }
        isc_throw(InvalidType, "The type of host backend: '" <<
                  db_type << "' is not supported");
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
        LOG_DEBUG(hosts_logger, DHCPSRV_DBG_TRACE, HOSTS_CFG_CLOSE_HOST_DATA_SOURCE)
            .arg(db_type);
        sources.erase(it);
        return (true);
    }
    return (false);
}

bool
HostDataSourceFactory::registerFactory(const string& db_type,
                                       const Factory& factory,
                                       bool no_log) {
    if (map_.count(db_type)) {
        return (false);
    }
    map_.insert(pair<string, Factory>(db_type, factory));

    // We are dealing here with static logger initialization fiasco.
    // registerFactory may be called from constructors of static global
    // objects for built in backends. The logging is not initialized yet,
    // so the LOG_DEBUG would throw.
    if (!no_log) {
        LOG_DEBUG(hosts_logger, DHCPSRV_DBG_TRACE, HOSTS_BACKEND_REGISTER)
            .arg(db_type);
    }
    return (true);
}

bool
HostDataSourceFactory::deregisterFactory(const string& db_type, bool no_log) {
    auto index = map_.find(db_type);
    if (index != map_.end()) {
        map_.erase(index);
        if (!no_log) {
            LOG_DEBUG(hosts_logger, DHCPSRV_DBG_TRACE,
                      HOSTS_BACKEND_DEREGISTER)
                .arg(db_type);
        }
        return (true);
    } else {
        return (false);
    }
}

bool
HostDataSourceFactory::registeredFactory(const std::string& db_type) {
    auto index = map_.find(db_type);
    return (index != map_.end());
}

void
HostDataSourceFactory::printRegistered() {
    std::stringstream txt;

    for (auto x : map_) {
        txt << x.first << " ";
    }

    LOG_INFO(hosts_logger, HOSTS_BACKENDS_REGISTERED).arg(txt.str());
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
        HostDataSourceFactory::registerFactory("mysql", factory, true);
    }

    // Destructor deregisters
    ~MySqlHostDataSourceInit() {
        HostDataSourceFactory::deregisterFactory("mysql", true);
    }

    // Factory class method
    static HostDataSourcePtr
    factory(const DatabaseConnection::ParameterMap& parameters) {
        LOG_INFO(hosts_logger, DHCPSRV_MYSQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        return (HostDataSourcePtr(new MySqlHostDataSource(parameters)));
    }
};

// Database backend will be registered at object initialization
MySqlHostDataSourceInit mysql_init_;
#endif

#ifdef HAVE_PGSQL
struct PgSqlHostDataSourceInit {
    // Constructor registers
    PgSqlHostDataSourceInit() {
        HostDataSourceFactory::registerFactory("postgresql", factory, true);
    }

    // Destructor deregisters
    ~PgSqlHostDataSourceInit() {
        HostDataSourceFactory::deregisterFactory("postgresql", true);
    }

    // Factory class method
    static HostDataSourcePtr
    factory(const DatabaseConnection::ParameterMap& parameters) {
        LOG_INFO(hosts_logger, DHCPSRV_PGSQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        return (HostDataSourcePtr(new PgSqlHostDataSource(parameters)));
    }
};

// Database backend will be registered at object initialization
PgSqlHostDataSourceInit pgsql_init_;
#endif

#ifdef HAVE_CQL
struct CqlHostDataSourceInit {
    // Constructor registers
    CqlHostDataSourceInit() {
        HostDataSourceFactory::registerFactory("cql", factory, true);
    }

    // Destructor deregisters
    ~CqlHostDataSourceInit() {
        HostDataSourceFactory::deregisterFactory("cql", true);
    }

    // Factory class method
    static HostDataSourcePtr
    factory(const DatabaseConnection::ParameterMap& parameters) {
        LOG_INFO(hosts_logger, DHCPSRV_CQL_HOST_DB)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        return (HostDataSourcePtr(new CqlHostDataSource(parameters)));
    }
};

// Database backend will be registered at object initialization
CqlHostDataSourceInit cql_init_;
#endif

} // end of anonymous namespace
