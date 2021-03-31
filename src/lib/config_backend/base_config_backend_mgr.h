// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_MGR_H
#define BASE_CONFIG_BACKEND_MGR_H

#include <config_backend/base_config_backend.h>
#include <database/database_connection.h>
#include <database/backend_selector.h>
#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <map>
#include <string>

namespace isc {
namespace cb {

/// @brief Base class for Configuration Backend Managers (CBM).
///
/// Each Kea server supporting Configuration Backend feature implements
/// a "manager" class which holds information about supported and
/// configured backends and provides access to the backends. This is
/// similar to @c HostMgr and @c LeaseMgr singletons being used by the
/// DHCP servers.
///
/// The Config Backend Managers are typically implemented as singletons
/// which can be accessed from any place within the server code. This
/// includes server configuration, data fetching during normal server
/// operation and data management, including processing of control
/// commands implemented within hooks libraries.
///
/// The @c BaseConfigBackendMgr is a base class for all CBMs implemented
/// for respective Kea servers. It includes mechanisms to register config
/// backend factory functions and to create instances of the backends using
/// those factory functions as a result of server configuration. The mechanism
/// of factory functions registration is useful in cases when the config
/// backend is implemented within the hook library. Such hook library
/// registers factory function in its @c load function and the server
/// simply calls this function to create the instance of this backend when
/// instructed to do so via configuration. Similar mechanism exists in
/// DHCP @c HostMgr.
///
/// Unlike @c HostMgr, the CBMs do not directly expose API to fetch and
/// manipulate the data in the database. This is done via, so called,
/// Configuration Backends Pools. See @c BaseConfigBackendPool for
/// details. The @c BaseConfigBackendMgr is provided with the pool type
/// via class template parameter. Respective CBM implementations
/// use their own pools, which provide APIs appropriate for those
/// implementations.
///
/// @tparam ConfgBackendPoolType Type of the configuration backend pool
/// to be used by the manager. It must derive from @c BaseConfigBackendPool
/// template class.
template<typename ConfigBackendPoolType>
class BaseConfigBackendMgr {
public:

    /// @brief Pointer to the configuration backend pool.
    typedef boost::shared_ptr<ConfigBackendPoolType> ConfigBackendPoolPtr;

    /// @brief Type of the backend factory function.
    ///
    /// Factory function returns a pointer to the instance of the configuration
    /// backend created.
    typedef std::function<typename ConfigBackendPoolType::ConfigBackendTypePtr
                          (const db::DatabaseConnection::ParameterMap&)> Factory;

    /// @brief Constructor.
    BaseConfigBackendMgr()
        : factories_(), pool_(new ConfigBackendPoolType()) {
    }

    /// @brief Registers new backend factory function for a given backend type.
    ///
    /// The typical usage of this function is to make the CBM aware of a
    /// configuration backend implementation. This implementation may exist
    /// in a hooks library. In such case, this function should be called from
    /// the @c load function in this library. When the backend is registered,
    /// the server will use it when required by the configuration, i.e. a
    /// user includes configuration backend of that type in the
    /// "config-databases" list.
    ///
    /// If the backend of the given type has already been registered, perhaps
    /// by another hooks library, the CBM will refuse to register another
    /// backend of the same type.
    ///
    /// @param db_type Backend type, e.g. "mysql".
    /// @param factory Pointer to the backend factory function.
    ///
    /// @return true if the backend has been successfully registered, false
    /// if another backend of this type already exists.
    bool registerBackendFactory(const std::string& db_type,
                                const Factory& factory) {
        // Check if this backend has been already registered.
        if (factories_.count(db_type)) {
            return (false);
        }

        // Register the new backend.
        factories_.insert(std::make_pair(db_type, factory));
        return (true);
    }

    /// @brief Unregisters the backend factory function for a given backend type.
    ///
    /// This function is used to remove the factory function and all backend instances
    /// for a given backend type.  Typically, it would be called when unloading the
    /// a config backend hook library, and thus called by the library's @c unload
    /// function.
    ///
    /// @param db_type Backend type, e.g. "mysql".
    ///
    /// @return false if no factory for the given type was unregistered, true
    /// if the factory was removed.
    bool unregisterBackendFactory(const std::string& db_type) {
        // Look for it.
        auto index = factories_.find(db_type);

        // If it's there remove it
        if (index != factories_.end()) {
            factories_.erase(index);
            pool_->delAllBackends(db_type);
            return (true);

        }

        return (false);
    }

    /// @brief Create an instance of a configuration backend.
    ///
    /// This method uses provided @c dbaccess string representing database
    /// connection information to create an instance of the database
    /// backend. If the specified backend type is not supported, i.e. there
    /// is no relevant factory function registered, an exception is thrown.
    ///
    /// @param dbaccess Database access string being a collection of
    /// key=value pairs.
    ///
    /// @throw InvalidParameter if access string lacks database type value.
    /// @throw db::InvalidType if the type of the database backend is not
    /// supported.
    /// @throw Unexpected if the backend factory function returned NULL.
    void addBackend(const std::string& dbaccess) {
        // Parse the access string into a map of parameters.
        db::DatabaseConnection::ParameterMap parameters =
            db::DatabaseConnection::parse(dbaccess);

        // Get the database type to locate a factory function.
        db::DatabaseConnection::ParameterMap::iterator it = parameters.find("type");
        if (it == parameters.end()) {
            isc_throw(InvalidParameter, "Config backend specification lacks the "
                      "'type' keyword");
        }

        std::string db_type = it->second;
        auto index = factories_.find(db_type);

        // No match?
        if (index == factories_.end()) {
            isc_throw(db::InvalidType, "The type of the configuration backend: '" <<
                      db_type << "' is not supported");
        }

        // Call the factory and push the pointer on sources.
        auto backend = index->second(parameters);
        if (!backend) {
            isc_throw(Unexpected, "Config database " << db_type <<
                      " factory returned NULL");
        }

        // Backend instance created successfully.
        pool_->addBackend(backend);
    }

    /// @brief Removes all backends from the pool.
    void delAllBackends() {
        pool_->delAllBackends();
    }

    /// @brief Delete a config backend manager.
    ///
    /// Delete the first instance of a config database manager which matches
    /// specific parameters.
    /// This should have the effect of closing the database connection.
    ///
    /// @param db_type Backend to remove.
    /// @param dbaccess Database access string being a collection of
    /// key=value pairs.
    /// @param if_unusable Flag which indicates if the config backend should be
    /// deleted only if it is unusable.
    /// @return false when not removed because it is not found or because it is
    /// still usable (if_unusable is true), true otherwise.
    bool delBackend(const std::string& db_type, const std::string& dbaccess,
                    bool if_unusable) {
        return (pool_->del(db_type, dbaccess, if_unusable));
    }

    /// @brief Returns underlying config backend pool.
    ConfigBackendPoolPtr getPool() const {
        return (pool_);
    }

protected:

    /// @brief A map holding registered backend factory functions.
    std::map<std::string, Factory> factories_;

    /// @brief Pointer to the configuration backends pool.
    ConfigBackendPoolPtr pool_;
};

} // end of namespace isc::cb
} // end of namespace isc

#endif // BASE_CONFIG_BACKEND_MGR_H
