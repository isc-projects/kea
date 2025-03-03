// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <legal_log_mgr_factory.h>
#include <dhcpsrv/dhcpsrv_log.h>

using namespace isc::db;
using namespace std;

namespace isc {
namespace dhcp {

isc::asiolink::IOServicePtr LegalLogMgrFactory::io_service_;
map<string, pair<LegalLogMgrFactory::Factory, LegalLogMgrFactory::DBVersion>> LegalLogMgrFactory::map_;
LegalLogMgrPool LegalLogMgrFactory::pool_;

bool
LegalLogMgrFactory::registerBackendFactory(const string& db_type,
                                            const Factory& factory,
                                            bool no_log,
                                            DBVersion db_version) {
    if (map_.count(db_type)) {
        return (false);
    }

    static auto default_db_version = []() -> string {
        return (string());
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
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_FORENSIC_BACKEND_REGISTER)
            .arg(db_type);
    }
    return (true);
}

bool
LegalLogMgrFactory::unregisterBackendFactory(const string& db_type, bool no_log) {
    // Look for it.
    auto index = map_.find(db_type);

    // If it's there remove it
    if (index != map_.end()) {
        map_.erase(index);
        delAllBackends(db_type);
        if (!no_log) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                    DHCPSRV_FORENSIC_BACKEND_DEREGISTER)
                .arg(db_type);
        }
        return (true);
    }
    return (false);
}

void
LegalLogMgrFactory::addBackend(DatabaseConnection::ParameterMap& parameters, ManagerID id) {
    // Get the database type to locate a factory function.
    auto it = parameters.find("type");
    if (it == parameters.end()) {
        isc_throw(InvalidParameter, "Forensic log backend specification lacks the "
                  "'type' keyword");
    }

    string db_type = it->second;
    auto index = map_.find(db_type);

    // No match?
    if (index == map_.end()) {
        if ((db_type == "mysql") || (db_type == "postgresql")) {
            string with = (db_type == "postgresql" ? "pgsql" : db_type);
            isc_throw(InvalidType, "The Kea server has not been compiled with "
                      "support for configuration database type: " << db_type
                      << ". Did you forget to use --with-"
                      << with << " during compilation or to load libdhcp_"
                      << with << " hook library?");
        }
        isc_throw(InvalidType, "The type of the forensic log backend: '" <<
                  db_type << "' is not supported");
    }

    // Call the factory and push the pointer on sources.
    auto backend = index->second.first(parameters);
    if (!backend) {
        isc_throw(Unexpected, "Forensic log database " << db_type <<
                  " factory returned NULL");
    }

    backend->open();

    // Apply extra parameters.
    if (parameters.find("request-parser-format") != parameters.end()) {
        backend->setRequestFormatExpression(parameters["request-parser-format"]);
    }
    if (parameters.find("response-parser-format") != parameters.end()) {
        backend->setResponseFormatExpression(parameters["response-parser-format"]);
    }
    if (parameters.find("timestamp-format") != parameters.end()) {
        backend->setTimestampFormat(parameters["timestamp-format"]);
    }

    // Backend instance created successfully.
    pool_[id] = pair<DatabaseConnection::ParameterMap, LegalLogMgrPtr>(parameters, backend);
}

LegalLogMgrPtr&
LegalLogMgrFactory::instance(ManagerID id) {
    auto it = pool_.find(id);
    if (it != pool_.end()) {
        return (it->second.second);
    }
    // Usually the unit tests do not create the instances using LegalLogMgrFactory::addBackend or by
    // calling parseConfig or parseDatabase or parseFile, so an empty instance must be returned when
    // calling LegalLogMgrFactory::instance() - this function returns a reference, so it can not be
    // created on the stack, it must be stored as a static variable.
    static LegalLogMgrPtr backend;
    if (!id) {
        DatabaseConnection::ParameterMap parameters;
        pool_[id] = pair<DatabaseConnection::ParameterMap, LegalLogMgrPtr>(parameters, backend);
        return (pool_[id].second);
    }
    return (backend);
}

void
LegalLogMgrFactory::setParameters(DatabaseConnection::ParameterMap parameters, ManagerID id) {
    // Call LegalLogMgrFactory::instance first so that unit tests can have access to the empty
    // entry in the pool.
    LegalLogMgrFactory::instance(id);
    auto it = pool_.find(id);
    if (it != pool_.end()) {
        it->second.first = parameters;
        return;
    }
}

DatabaseConnection::ParameterMap
LegalLogMgrFactory::getParameters(ManagerID id) {
    auto it = pool_.find(id);
    if (it != pool_.end()) {
        return (it->second.first);
    }
    return (DatabaseConnection::ParameterMap());
}

bool
LegalLogMgrFactory::delBackend(const string& db_type,
                                DatabaseConnection::ParameterMap& parameters,
                                bool if_unusable) {
    bool deleted = false;
    if (if_unusable) {
        deleted = true;
    }

    for (auto it = pool_.begin(); it != pool_.end(); ++it) {
        if (!it->second.second || it->second.second->getType() != db_type || it->second.first != parameters) {
            continue;
        }
        if (if_unusable && (!(it->second.second->isUnusable()))) {
            deleted = false;
            continue;
        }
        it->second.second = LegalLogMgrPtr();
        return (true);
    }
    return (deleted);
}

bool
LegalLogMgrFactory::delBackend(ManagerID id,
                                bool if_unusable) {
    bool deleted = false;
    if (if_unusable) {
        deleted = true;
    }

    auto it = pool_.find(id);
    if (it != pool_.end()) {
        if (if_unusable && it->second.second && !it->second.second->isUnusable()) {
            return (false);
        }
        it->second.second = LegalLogMgrPtr();
        return (true);
    }
    return (deleted);
}

bool
LegalLogMgrFactory::registeredFactory(const string& db_type) {
    auto index = map_.find(db_type);
    return (index != map_.end());
}

void
LegalLogMgrFactory::logRegistered() {
    stringstream txt;

    for (auto const& x : map_) {
        if (!txt.str().empty()) {
            txt << " ";
        }
        txt << x.first;
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_FORENSIC_BACKENDS_REGISTERED)
        .arg(txt.str());
}

list<string>
LegalLogMgrFactory::getDBVersions() {
    list<string> result;
    for (auto const& x : map_) {
        auto version = x.second.second();
        if (!version.empty()) {
            result.push_back(version);
        }
    }

    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc

