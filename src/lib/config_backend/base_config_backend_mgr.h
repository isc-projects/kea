// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_MGR_H
#define BASE_CONFIG_BACKEND_MGR_H

#include <database/database_connection.h>
#include <config_backend/base_config_backend.h>
#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <map>
#include <string>

namespace isc {
namespace cb {

template<typename ConfigBackendPoolType>
class BaseConfigBackendMgr {
public:

    typedef boost::shared_ptr<ConfigBackendPoolType> ConfigBackendPoolPtr;

    typedef std::function<typename ConfigBackendPoolType::ConfigBackendTypePtr
                          (const db::DatabaseConnection::ParameterMap&)> Factory;

    BaseConfigBackendMgr()
        : factories_(), backends_(new ConfigBackendPoolType()) {
    }

    bool registerBackendFactory(const std::string& db_type,
                                const Factory& factory) {
        if (factories_.count(db_type)) {
            return (false);
        }

        factories_.insert(std::make_pair(db_type, factory));

        return (true);
    }

    void addBackend(const std::string& dbaccess) {
        // Parse the access string and create a redacted string for logging.
        db::DatabaseConnection::ParameterMap parameters =
            db::DatabaseConnection::parse(dbaccess);

        // Get the database type and open the corresponding database
        db::DatabaseConnection::ParameterMap::iterator it = parameters.find("type");
        if (it == parameters.end()) {
            isc_throw(InvalidParameter, "Host database configuration does not "
                      "contain the 'type' keyword");
        }

        std::string db_type = it->second;
        auto index = factories_.find(db_type);

        // No match?
        if (index == factories_.end()) {
            isc_throw(db::InvalidType, "The type of host backend: '" <<
                      db_type << "' is not currently supported");
    }

        // Call the factory and push the pointer on sources.
        auto backend = index->second(parameters);
        if (!backend) {
            isc_throw(Unexpected, "Config database " << db_type <<
                      " factory returned NULL");
        }

        backends_->addBackend(backend);
    }

    void delAllBackends() {
        backends_->delAllBackends();
    }

    ConfigBackendPoolPtr getPool() const {
        return (backends_);
    }

protected:

    std::map<std::string, Factory> factories_;

    ConfigBackendPoolPtr backends_;

};

} // end of namespace isc::cb
} // end of namespace isc

#endif // BASE_CONFIG_BACKEND_MGR_H
