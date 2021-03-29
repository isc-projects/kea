// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_POOL_H
#define BASE_CONFIG_BACKEND_POOL_H

#include <cc/data.h>
#include <config_backend/base_config_backend.h>
#include <database/backend_selector.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <database/server_selector.h>
#include <functional>
#include <list>
#include <string>

namespace isc {
namespace cb {


/// @brief Base class for configuration backend pools.
///
/// Each Kea server supporting databases as a configuration repository can
/// use multiple database instances simultaneously. A pool is a collection
/// of database backends used by a particular server. Different Kea servers
/// use different pools because they store and fetch different configuration
/// information. For example: DHCPv4 server stores and fetches IPv4 subnets,
/// and DHCPv6 server stores and fetches IPv6 subnets. Therefore, each pool
/// type will expose a different API calls.
///
/// This template class is a base class for all pools used by various servers.
/// It implements mechanisms for managing multiple backends and for forwarding
/// API calls to one or many database backends depending on the selections
/// made via @c BackendSelector class.
///
/// @tparam ConfigBackendType Type of the configuration backend. This must
/// be a class deriving from @c BaseConfigBackend class. It is a class
/// dedicated to a particular server type, e.g. DHCPv4 server, and from
/// which database specific backends derive.
template<typename ConfigBackendType>
class BaseConfigBackendPool {
public:

    /// @brief Shared pointer to the Configuration Backend used.
    typedef boost::shared_ptr<ConfigBackendType> ConfigBackendTypePtr;

    /// @brief Virtual destructor.
    virtual ~BaseConfigBackendPool() { }

    /// @brief Adds a backend to the pool.
    ///
    /// @param backend Pointer to a backend to be added.
    void addBackend(ConfigBackendTypePtr backend) {
        backends_.push_back(backend);
    }

    /// @brief Deletes all backends from the pool.
    void delAllBackends() {
        backends_.clear();
    }

    /// @brief Deletes all backends of the given type from the pool.
    ///
    /// @param db_type Backend to remove.
    void delAllBackends(const std::string& db_type) {
        typename std::list<ConfigBackendTypePtr>::iterator backend = backends_.begin();

        while (backend != backends_.end()) {
            if ((*backend)->getType() == db_type) {
                backend = backends_.erase(backend);
            } else {
                ++backend;
            }
        }
    }

    /// @brief Deletes all backends of the given type from the pool.
    ///
    /// @param db_type Backend to remove.
    /// @param dbaccess Database access string being a collection of
    /// key=value pairs.
    /// @param if_unusable Flag which indicates if the config backend should be
    /// deleted only if it is unusable.
    /// @return false when not removed because it is not found or because it is
    /// still usable (if_unusable is true), true otherwise.
    bool del(const std::string& db_type, const std::string& dbaccess,
             bool if_unusable) {
        isc::db::DatabaseConnection::ParameterMap parameters =
            isc::db::DatabaseConnection::parse(dbaccess);
        bool deleted = false;
        if (if_unusable) {
            deleted = true;
        }

        typename std::list<ConfigBackendTypePtr>::iterator backend = backends_.begin();

        while (backend != backends_.end()) {
            if ((*backend)->getType() != db_type || (*backend)->getParameters() != parameters) {
                ++backend;
            } else if (if_unusable && (!(*backend)->isUnusable())) {
                deleted = false;
                ++backend;
            } else {
                backends_.erase(backend);
                return (true);
            }
        }
        return (deleted);
    }

protected:

    /// @brief Retrieve a single configuration property from the pool.
    ///
    /// This is common method for retrieving a single configuration property
    /// from the databases. The server specific backends call this method to
    /// retrieve a single object. For example, the DHCPv4 configuration backend
    /// pool may use this function to implement a @c getSubnet4 method:
    ///
    /// @code
    /// Subnet4Ptr getSubnet4(const SubnetID& subnet_id,
    ///                       const BackendSelector& backend_selector,
    ///                       const ServerSelector& server_selector) const {
    ///     Subnet4Ptr subnet;
    ///     getPropertyPtrConst<Subnet4Ptr, const SubnetID&>
    ///         (&ConfigBackendDHCPv4::getSubnet4, backend_selector,
    ///          server_selector, subnet, subnet_id);
    ///     return (subnet);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv4::getSubnet4 has the following signature:
    ///
    /// @code
    /// Subnet4Ptr getSubnet4(const ServerSelector&, const SubnetID&) const;
    /// @endcode
    ///
    /// If the backend selector is set to "unspecified", this method will iterate
    /// over the existing backends and call the @c MethodPointer method on each
    /// backend. It will return the first non-null (or non-zero) value returned
    /// by this call. For example: if the first backend returns non-null value,
    /// this value is returned via @c property argument and the calls for the
    /// rest of the backends are skipped.
    ///
    /// @tparam PropertyType Type of the object returned by the backend call.
    /// @tparam FnPtrArgs Parameter pack holding argument types of the backend
    /// method to be invoked.
    /// @tparam Args Parameter pack holding types of the arguments provided
    /// in the call to this method.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param [out] property Reference to the shared pointer where retrieved
    /// property should be assigned.
    /// @param input Values to be used as input to the backend call.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    template<typename PropertyType, typename... FnPtrArgs, typename... Args>
    void getPropertyPtrConst(PropertyType (ConfigBackendType::*MethodPointer)
                             (const db::ServerSelector&, FnPtrArgs...) const,
                             const db::BackendSelector& backend_selector,
                             const db::ServerSelector& server_selector,
                             PropertyType& property,
                             Args... input) const {

        // If no particular backend is selected, call each backend and return
        // the first non-null (non zero) value.
        if (backend_selector.amUnspecified()) {
            for (auto backend : backends_) {
                property = ((*backend).*MethodPointer)(server_selector, input...);
                if (property) {
                    break;
                }
            }

        } else {
            // Backend selected, find the one that matches selection.
            auto backends = selectBackends(backend_selector);
            if (!backends.empty()) {
                for (auto backend : backends) {
                    property = ((*backend).*MethodPointer)(server_selector, input...);
                    if (property) {
                        break;
                    }
                }

            } else {
                isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                          << backend_selector.toText());
            }
        }
    }

    /// @brief Retrieve a single configuration property from the backend.
    ///
    /// This is common method for retrieving a single configuration property
    /// from the selected database without specifying the server selector. The
    /// server specific backends call this method to retrieve a single object.
    /// For example, the DHCPv4 configuration backend pool may use this function
    /// to implement a @c getServer4 method:
    ///
    /// @code
    /// ServerPtr getServer4(const BackendSelector& backend_selector,
    ///                      const std::string& server_tag) const {
    ///     ServerPtr server;
    ///     getPropertyPtrConst<ServerPtr, const std::string&>
    ///         (&ConfigBackendDHCPv4::getServer4, backend_selector,
    ///          server_tag);
    ///     return (server);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv4::getServer4 has the following signature:
    ///
    /// @code
    /// ServerPtr getServer4(const std::string&) const;
    /// @endcode
    ///
    /// This method is used in cases when server selector is not applicable.
    ///
    /// @tparam PropertyType Type of the object returned by the backend call.
    /// @tparam FnPtrArgs Parameter pack holding argument types of the backend
    /// method to be invoked.
    /// @tparam Args Parameter pack holding types of the arguments provided
    /// in the call to this method.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param [out] property Reference to the shared pointer where retrieved
    /// property should be assigned.
    /// @param input Values to be used as input to the backend call.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    /// @throw db::AmbiguousDatabase if multiple databases matching the selector
    /// were found.
    template<typename PropertyType, typename... FnPtrArgs, typename... Args>
    void getBackendPropertyPtrConst(PropertyType (ConfigBackendType::*MethodPointer)
                                    (FnPtrArgs...) const,
                                    const db::BackendSelector& backend_selector,
                                    PropertyType& property,
                                    Args... input) const {
        auto backends = selectBackends(backend_selector);
        if (backends.empty()) {
            isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                      << backend_selector.toText());

        } else if (backends.size() > 1) {
            isc_throw(db::AmbiguousDatabase, "more than one database found for "
                      "selector: " << backend_selector.toText());
        }

        property = ((*(*(backends.begin())).*MethodPointer)(input...));
    }

    /// @brief Retrieve multiple configuration properties from the pool.
    ///
    /// This is a common method for retrieving multiple configuration properties
    /// from the databases. The server specific backends call this method to
    /// retrieve multiple objects of the same type. For example, the DHCPv6
    /// configuration backend pool may use this function to implement a
    /// @c getSubnets6 method:
    ///
    /// @code
    /// Subnet6Collection getModifiedSubnets6(const BackendSelector& backend_selector,
    ///                                       const ServerSelector& server_selector,
    ///                                       const ptime& modification_time) const {
    ///     Subnet6Collection subnets;
    ///     getMultiplePropertiesConst<Subnet6Collection, const ptime&>
    ///         (&ConfigBackendDHCPv6::getSubnets6, backend_selector, server_selector,
    ///          subnets, modification_time);
    ///     return (subnets);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv6::getSubnets6 has the following signature:
    ///
    /// @code
    /// Subnet6Collection getSubnets6(const ServerSelector&, const ptime&) const;
    /// @endcode
    ///
    /// If the backend selector is set to "unspecified", this method will iterate
    /// over existing backends and call the @c MethodPointer method on each
    /// backend. It will return the first non-empty list returned by one of the
    /// backends.
    ///
    /// @tparam PropertyCollectionType Type of the container into which the
    /// properties are stored.
    /// @tparam FnPtrArgs Parameter pack holding argument types of the backend
    /// method to be invoked.
    /// @tparam Args Parameter pack holding types of the arguments provided
    /// in the call to this method.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param [out] properties Reference to the collection of retrieved properties.
    /// @param input Values to be used as input to the backend call.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    template<typename PropertyCollectionType, typename... FnPtrArgs, typename... Args>
    void getMultiplePropertiesConst(PropertyCollectionType (ConfigBackendType::*MethodPointer)
                                    (const db::ServerSelector&, FnPtrArgs...) const,
                                    const db::BackendSelector& backend_selector,
                                    const db::ServerSelector& server_selector,
                                    PropertyCollectionType& properties,
                                    Args... input) const {
        if (backend_selector.amUnspecified()) {
            for (auto backend : backends_) {
                properties = ((*backend).*MethodPointer)(server_selector, input...);
                if (!properties.empty()) {
                    break;
                }
            }

        } else {
            auto backends = selectBackends(backend_selector);
            if (!backends.empty()) {
                for (auto backend : backends) {
                    properties = ((*backend).*MethodPointer)(server_selector, input...);
                    if (!properties.empty()) {
                        break;
                    }
                }

            } else {
                isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                          << backend_selector.toText());
            }
        }
    }

    /// @brief Retrieve all configuration properties from the pool.
    ///
    /// This is a common method for retrieving all configuration properties
    /// from the databases. The server specific backends call this method
    /// to retrieve all objects of the same type. For example, the DHCPv4
    /// configuration backend pool may use this function to implement a
    /// @c getAllSubnets4 method:
    ///
    /// @code
    /// Subnet4Collection getAllSubnets4(const BackendSelector&, const ServerSelector&) const {
    ///     Subnet4Collection subnets;
    ///     getAllPropertiesConst<Subnet6Collection>
    ///         (&ConfigBackendDHCPv4::getAllSubnets4, subnets, backend_selector,
    ///          server_selector);
    ///     return (subnets);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv4::getAllSubnets4 has the following signature:
    ///
    /// @code
    /// Subnet4Collection getAllSubnets4(const ServerSelector&) const;
    /// @endcode
    ///
    /// If the backend selector is set to "unspecified", this method will iterate
    /// over existing backends and call the @c MethodPointer method on each
    /// backend. It will return the first non-empty list returned by one of the
    /// backends.
    ///
    /// @tparam PropertyCollectionType Type of the container into which the
    /// properties are stored.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param [out] properties Reference to the collection of retrieved properties.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    template<typename PropertyCollectionType>
    void getAllPropertiesConst(PropertyCollectionType (ConfigBackendType::*MethodPointer)
                               (const db::ServerSelector&) const,
                               const db::BackendSelector& backend_selector,
                               const db::ServerSelector& server_selector,
                               PropertyCollectionType& properties) const {
        if (backend_selector.amUnspecified()) {
            for (auto backend : backends_) {
                properties = ((*backend).*MethodPointer)(server_selector);
                if (!properties.empty()) {
                    break;
                }
            }

        } else {
            auto backends = selectBackends(backend_selector);
            if (!backends.empty()) {
                for (auto backend : backends) {
                    properties = ((*backend).*MethodPointer)(server_selector);
                    if (!properties.empty()) {
                        break;
                    }
                }

            } else {
                isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                          << backend_selector.toText());
            }
        }
    }

    /// @brief Get all configuration properties from the backend.
    ///
    /// This is a common method for retrieving all configuration properties
    /// from the selected database without specifying the server selector. The
    /// server specific backends call this method to retrieve all objects of
    /// the same type. For example, the DHCPv4 configuration backend pool may
    /// use this function to implement a @c getAllServers4 method:
    ///
    /// @code
    /// ServerCollection getAllServers4(const BackendSelector&) const {
    ///     ServerCollection servers;
    ///     getAllBackendPropertiesConst<ServerCollection>
    ///         (&ConfigBackendDHCPv4::getAllServers4, backend_selector, servers);
    ///     return (servers);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv4::getAllServers4 has the following signature:
    ///
    /// @code
    /// ServerCollection getAllServers4() const;
    /// @endcode
    ///
    /// This method is used in cases when server selector is not applicable.
    ///
    /// @tparam PropertyCollectionType Type of the container into which the
    /// properties are stored.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param [out] properties Reference to the collection of retrieved properties.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    /// @throw db::AmbiguousDatabase if multiple databases matching the selector
    /// were found.
    template<typename PropertyCollectionType>
    void getAllBackendPropertiesConst(PropertyCollectionType (ConfigBackendType::*MethodPointer)() const,
                                      const db::BackendSelector& backend_selector,
                                      PropertyCollectionType& properties) const {
        auto backends = selectBackends(backend_selector);
        if (backends.empty()) {
            isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                      << backend_selector.toText());

        } else if (backends.size() > 1) {
            isc_throw(db::AmbiguousDatabase, "more than one database found for "
                      "selector: " << backend_selector.toText());
        }

        properties = (*(*(backends.begin())).*MethodPointer)();
    }

    /// @brief Add, update or delete property from the backend.
    ///
    /// This is a common method for storing a single configuration property in
    /// a database, updating an existing property or deleting the property.
    /// The server specific backends call this method. For example,
    /// the DHCPv6 configuration backend pool may use this function to implement
    /// a @c createUpdateSubnet6 method:
    ///
    /// @code
    /// void createUpdateSubnet6(const Subnet6Ptr& subnet,
    ///                          const BackendSelector& backend_selector,
    ///                          const ServerSelector& server_selector) {
    ///     createUpdateDeleteProperty<void, const Subnet6Ptr&>
    ///         (&ConfigBackendDHCPv6::createUpdateSubnet6, backend_selector,
    ///          server_selector, subnet, selector);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv6::createUpdateSubnet6 has the following
    /// signature:
    ///
    /// @code
    /// void createUpdateSubnet6(const ServerSelector&, const Subnet6Ptr&);
    /// @endcode
    ///
    /// The backend selector must point to exactly one backend. If more than one
    /// backend is selected, an exception is thrown. If no backend is selected
    /// an exception is thrown either.
    ///
    /// @tparam ReturnValue Returned value, typically void or uint64_t.
    /// @tparam FnPtrArgs Parameter pack holding argument types of the backend
    /// method to be invoked.
    /// @tparam Args Parameter pack holding types of the arguments provided
    /// in the call to this method.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param input Objects used as arguments to the backend method to be
    /// called.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    /// @throw db::AmbiguousDatabase if multiple databases matching the selector
    /// were found.
    /// @return Number of affected properties, if the value is non void.
    template<typename ReturnValue, typename... FnPtrArgs, typename... Args>
    ReturnValue createUpdateDeleteProperty(ReturnValue (ConfigBackendType::*MethodPointer)
                                           (const db::ServerSelector&, FnPtrArgs...),
                                           const db::BackendSelector& backend_selector,
                                           const db::ServerSelector& server_selector,
                                           Args... input) {
        auto backends = selectBackends(backend_selector);
        if (backends.empty()) {
            isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                      << backend_selector.toText());

        } else if (backends.size() > 1) {
            isc_throw(db::AmbiguousDatabase, "more than one database found for "
                      "selector: " << backend_selector.toText());
        }

        return ((*(*(backends.begin())).*MethodPointer)(server_selector, input...));
    }

    /// @brief Add, update or delete property from the backend.
    ///
    /// This is a common method for storing a single configuration property in
    /// a database, updating an existing property or deleting the property
    /// without specifying the server selector. The server specific backends
    /// call this method. For example, the DHCPv4 configuration backend pool
    /// may use this function to implement the @c createUpdateServer4 method:
    ///
    /// @code
    /// void createUpdateServer4(const BackendSelector& backend_selector,
    ///                          const ServerSelector& server_selector,
    ///                          const ServerPtr& server) {
    ///     createUpdateDeleteBackendProperty<void, const ServerPtr&>
    ///         (&ConfigBackendDHCPv4::createUpdateServer4, backend_selector,
    ///          server);
    /// }
    /// @endcode
    ///
    /// where @c ConfigBackendDHCPv4::createUpdateServer4 has the following
    /// signature:
    ///
    /// @code
    /// void createUpdateServer4(const ServerPtr&);
    /// @endcode
    ///
    /// This method is used in cases when server selector is not applicable.
    ///
    /// @tparam ReturnValue Returned value, typically void or uint64_t.
    /// @tparam FnPtrArgs Parameter pack holding argument types of the backend
    /// method to be invoked.
    /// @tparam Args Parameter pack holding types of the arguments provided
    /// in the call to this method.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param backend_selector Backend selector.
    /// @param input Objects used as arguments to the backend method to be
    /// called.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    /// @throw db::AmbiguousDatabase if multiple databases matching the selector
    /// were found.
    /// @return Number of affected properties, if the value is non void.
    template<typename ReturnValue, typename... FnPtrArgs, typename... Args>
    ReturnValue createUpdateDeleteBackendProperty(ReturnValue (ConfigBackendType::*MethodPointer)
                                                  (FnPtrArgs...),
                                                  const db::BackendSelector& backend_selector,
                                                  Args... input) {
        auto backends = selectBackends(backend_selector);
        if (backends.empty()) {
            isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                      << backend_selector.toText());

        } else if (backends.size() > 1) {
            isc_throw(db::AmbiguousDatabase, "more than one database found for "
                      "selector: " << backend_selector.toText());
        }

        return ((*(*(backends.begin())).*MethodPointer)(input...));
    }

    /// @brief Selects existing backends matching the selector.
    ///
    /// This method selects backends matching the selector. If the selector is
    /// "unspecified" or there is no backend in the pool, an empty list is returned.
    ///
    /// @param backend_selector Selector for which matching backends should be selected.
    std::list<ConfigBackendTypePtr>
    selectBackends(const db::BackendSelector& backend_selector) const {

        std::list<ConfigBackendTypePtr> selected;

        // In case there is only one backend and the caller hasn't specified
        // any particular backend, simply return it.
        if ((backends_.size() == 1) && backend_selector.amUnspecified()) {
            selected.push_back(*backends_.begin());
            return (selected);
        }

        // For other cases we return empty list.
        if (backends_.empty() || backend_selector.amUnspecified()) {
            return (selected);
        }

        // Go over all backends.
        for (auto backend : backends_) {
            // If backend type is specified and it is not matching,
            // do not select this backend.
            if ((backend_selector.getBackendType() != db::BackendSelector::Type::UNSPEC) &&
                (backend_selector.getBackendType() !=
                 db::BackendSelector::stringToBackendType(backend->getType()))) {
                continue;
            }

            // If the host has been specified by the backend's host is not
            // matching, do not select this backend.
            if ((!backend_selector.getBackendHost().empty()) &&
                (backend_selector.getBackendHost() != backend->getHost())) {
                continue;
            }

            // If the port has been specified by the backend's port is not
            // matching, do not select this backend.
            if ((backend_selector.getBackendPort() != 0) &&
                (backend_selector.getBackendPort() != backend->getPort())) {
                continue;
            }

            // Passed all checks, so the backend is matching. Add it to the list.
            selected.push_back(backend);
        }

        return (selected);
    }

    /// @brief Holds configuration backends belonging to the pool.
    std::list<ConfigBackendTypePtr> backends_;
};

} // end of namespace isc::cb
} // end of namespace isc

#endif // BASE_CONFIG_BACKEND_POOL_H
