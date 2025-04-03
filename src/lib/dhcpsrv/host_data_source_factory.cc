// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/hosts_log.h>
#include <log/logger_support.h>

#include <boost/algorithm/string.hpp>

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

map<string, pair<HostDataSourceFactory::Factory, HostDataSourceFactory::DBVersion>> HostDataSourceFactory::map_;

void
HostDataSourceFactory::add(HostDataSourceList& sources,
                           const string& dbaccess) {
    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters =
            DatabaseConnection::parse(dbaccess);

    // Get the database type and open the corresponding database.
    DatabaseConnection::ParameterMap::iterator it = parameters.find("type");
    if (it == parameters.end()) {
        isc_throw(InvalidParameter, "Host database configuration does not "
                  "contain the 'type' keyword");
    }

    string db_type = it->second;
    auto index = map_.find(db_type);

    // No match?
    if (index == map_.end()) {
        if ((db_type == "mysql") || (db_type == "postgresql")) {
            string with = (db_type == "postgresql" ? "pgsql" : db_type);
            isc_throw(InvalidType, "The Kea server has not been compiled with "
                      "support for host database type: " << db_type
                      << ". Did you forget to use -D"
                      << with << " during compilation or to load libdhcp_"
                      << with << " hook library?");
        }
        isc_throw(InvalidType, "The type of host backend: '" <<
                  db_type << "' is not supported");
    }

    // Call the factory and push the pointer on sources.
    sources.push_back(index->second.first(parameters));

    // Check the factory did not return null.
    if (!sources.back()) {
        sources.pop_back();
        isc_throw(Unexpected, "Hosts database " << db_type <<
                  " factory returned null");
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
HostDataSourceFactory::del(HostDataSourceList& sources,
                           const string& db_type,
                           const string& dbaccess,
                           bool if_unusable) {
    DatabaseConnection::ParameterMap parameters =
            DatabaseConnection::parse(dbaccess);
    bool deleted = false;
    if (if_unusable) {
        deleted = true;
    }

    for (auto it = sources.begin(); it != sources.end(); ++it) {
        if ((*it)->getType() != db_type || (*it)->getParameters() != parameters) {
            continue;
        }
        if (if_unusable && (!(*it)->isUnusable())) {
            deleted = false;
            continue;
        }
        LOG_DEBUG(hosts_logger, DHCPSRV_DBG_TRACE, HOSTS_CFG_CLOSE_HOST_DATA_SOURCE)
            .arg((*it)->getType());
        sources.erase(it);
        return (true);
    }
    return (deleted);
}

bool
HostDataSourceFactory::registerFactory(const string& db_type,
                                       const Factory& factory,
                                       bool no_log,
                                       DBVersion db_version) {
    if (map_.count(db_type)) {
        return (false);
    }

    static auto default_db_version = []() -> std::string {
        return (std::string());
    };

    if (!db_version) {
        db_version = default_db_version;
    }

    map_.insert(pair<string, pair<Factory, DBVersion>>(db_type, pair<Factory, DBVersion>(factory, db_version)));

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
    }
    return (false);
}

bool
HostDataSourceFactory::registeredFactory(const std::string& db_type) {
    auto index = map_.find(db_type);
    return (index != map_.end());
}

void
HostDataSourceFactory::logRegistered() {
    std::stringstream txt;

    for (auto const& x : map_) {
        if (!txt.str().empty()) {
            txt << " ";
        }
        txt << x.first;
    }

    LOG_INFO(hosts_logger, HOSTS_BACKENDS_REGISTERED)
        .arg(txt.str());
}

std::list<std::string>
HostDataSourceFactory::getDBVersions() {
    std::list<std::string> result;
    for (auto const& x : map_) {
        auto version = x.second.second();
        if (!version.empty()) {
            result.push_back(version);
        }
    }

    return (result);
}

}  // namespace dhcp
}  // namespace isc
