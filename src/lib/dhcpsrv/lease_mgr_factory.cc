// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>
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

map<string, pair<LeaseMgrFactory::Factory, LeaseMgrFactory::DBVersion>> LeaseMgrFactory::map_;

namespace {

/// @brief Initializer.
isc::dhcp::MemfileLeaseMgrInit memfile_init;

}

TrackingLeaseMgrPtr&
LeaseMgrFactory::getLeaseMgrPtr() {
    static TrackingLeaseMgrPtr lease_mgr_ptr;
    return (lease_mgr_ptr);
}

void
LeaseMgrFactory::create(const std::string& dbaccess) {
    const std::string type = "type";

    // Parse the access string and create a redacted string for logging.
    DatabaseConnection::ParameterMap parameters = DatabaseConnection::parse(dbaccess);
    std::string redacted = DatabaseConnection::redactedAccessString(parameters);

    // Get the database type and open the corresponding database.
    DatabaseConnection::ParameterMap::iterator it = parameters.find(type);
    if (it == parameters.end()) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_NOTYPE_DB).arg(dbaccess);
        isc_throw(InvalidParameter, "Database configuration parameters do not "
                  "contain the 'type' keyword");
    }

    string db_type = it->second;
    auto index = map_.find(db_type);

    // No match?
    if (index == map_.end()) {
        if ((db_type == "mysql") || (db_type == "postgresql")) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_UNKNOWN_DB).arg(db_type);
            string with = (db_type == "postgresql" ? "pgsql" : db_type);
            isc_throw(InvalidType, "The Kea server has not been compiled with "
                      "support for database type: " << db_type
                      << ". Did you forget to use --with-"
                      << with << " during compilation or to load libdhcp_"
                      << with << "_lb hook library?");
        }
        // Get here on no match
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_UNKNOWN_DB).arg(parameters[type]);
        isc_throw(InvalidType, "Database access parameter 'type' does "
                  "not specify a supported database backend: " << parameters[type]);
    }

    // Call the factory.
    getLeaseMgrPtr() = index->second.first(parameters);

    // Check the factory did not return null.
    if (!getLeaseMgrPtr()) {
        isc_throw(Unexpected, "Lease database " << db_type <<
                  " factory returned null");
    }
}

void
LeaseMgrFactory::destroy() {
    // Destroy current lease manager.  This is a no-op if no lease manager
    // is available.
    if (getLeaseMgrPtr()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CLOSE_DB)
            .arg(getLeaseMgrPtr()->getType());
    }
    getLeaseMgrPtr().reset();
}

void
LeaseMgrFactory::recreate(const std::string& dbaccess, bool preserve_callbacks) {
    TrackingLeaseMgr::CallbackContainerPtr callbacks;
    // Preserve the callbacks if needed.
    if (preserve_callbacks && haveInstance()) {
        callbacks = instance().callbacks_;
    }

    // Re-create the manager.
    destroy();
    create(dbaccess);

    if (callbacks) {
        // Copy the callbacks to the new instance. It should be fast
        // because we merely copy the pointer.
        instance().callbacks_ = callbacks;
    }
}

bool
LeaseMgrFactory::haveInstance() {
    return (!!getLeaseMgrPtr());
}

TrackingLeaseMgr&
LeaseMgrFactory::instance() {
    TrackingLeaseMgr* lmptr = getLeaseMgrPtr().get();
    if (!lmptr) {
        isc_throw(NoLeaseManager, "no current lease manager is available");
    }
    return (*lmptr);
}

bool
LeaseMgrFactory::registerFactory(const string& db_type,
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
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_LEASE_MGR_BACKEND_REGISTER)
            .arg(db_type);
    }
    return (true);
}

bool
LeaseMgrFactory::deregisterFactory(const string& db_type, bool no_log) {
    auto index = map_.find(db_type);
    if (index != map_.end()) {
        map_.erase(index);
        if (!no_log) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                    DHCPSRV_LEASE_MGR_BACKEND_DEREGISTER)
                .arg(db_type);
        }
        return (true);
    } else {
        return (false);
    }
}

bool
LeaseMgrFactory::registeredFactory(const std::string& db_type) {
    auto index = map_.find(db_type);
    return (index != map_.end());
}

void
LeaseMgrFactory::logRegistered() {
    std::stringstream txt;

    for (auto const& x : map_) {
        if (!txt.str().empty()) {
            txt << " ";
        }
        txt << x.first;
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_LEASE_MGR_BACKENDS_REGISTERED)
        .arg(txt.str());
}

std::list<std::string>
LeaseMgrFactory::getDBVersions() {
    std::list<std::string> result;
    for (auto const& x : map_) {
        auto version = x.second.second();
        if (!version.empty()) {
            result.push_back(version);
        }
    }

    return (result);
}

} // namespace dhcp
} // namespace isc
