// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_POOL_H
#define BASE_CONFIG_BACKEND_POOL_H

#include <cc/data.h>
#include <config_backend/base_config_backend.h>
#include <database/db_exceptions.h>
#include <cstdint>
#include <functional>
#include <list>
#include <string>

namespace isc {
namespace cb {

/// @brief Config Backend selector.
///
/// Each Kea server using database as a configuration respository
/// may use multiple configuration backends simultaneously. The most
/// typical case is to use a single configuration backend per server,
/// but there are use cases when configuration information is distributed
/// accross multiple database instances. In the future, there may be
/// also caching mechanisms implemented, which will allow for storing
/// results of certain database queries in memory.
///
/// From the server perspective, the most common use of the configuration
/// backend is to fetch entire configuration information from the
/// databases (upon startup) or fetch the latest updates to the
/// configuration, e.g. new subnet added, DHCP option modified etc.
/// In those cases, it is not so important from the server which backend
/// this data come from. Therefore, the server would fetch this information
/// from all available backends.
///
/// When the server administrator wants to insert some new data into
/// the database, modify existing data or simply wants to check the
/// contents of one of the database instance, he would specify which
/// database backend he wants to direct queries to.
///
/// The @c BackendSelector class provides means to specify whether
/// the queries should be directed to any backend (see server case
/// above) or to a specific backend (data insertion case above).
/// In addition, the @c BackendSelector allows for using various
/// criteria for selecting a backend to use. Currently those criteria
/// are: database type (e.g. mysql), database host and database port.
/// In order to use a specific port, the database host must also be
/// specified. Note that in a general case multiple backends of the
/// same type can be used simultaneously, e.g. multiple MySQL backends.
/// In that case, it may be necessary to specify host (and port) to
/// issue a query to the right one.
///
/// The @c BackendSelector class may be extended in the future to provide
/// additional backend selection criteria.
class BackendSelector {
public:

    /// @brief Supported database types.
    ///
    /// The @c UNSPEC indicates that the database type is not specified
    /// as selection criteria.
    enum class Type {
        MYSQL,
        PGSQL,
        CQL,
        UNSPEC
    };

    /// @brief Default constructor.
    ///
    /// It sets the selector to "unspecified". When this selector is used
    /// the backend pool will use "any" backend. This has a different meaning
    /// for each type of query. See the @c BaseConfigBackendPool for details.
    explicit BackendSelector();

    /// @brief Constructor specifying backend type as a selection criteria.
    ///
    /// @param backend_type Type of the backend to be selected.
    explicit BackendSelector(const Type& backend_type);

    /// @brief Constructor for specifying host and optionally port as a
    /// selection criteria.
    ///
    /// @param host Hostname to be used for selecting a backend.
    /// @param port Port number to be used for selecting a backend. This value
    /// is optional and is ignored when set to 0. It must be used on conjuction
    /// with hostname.
    explicit BackendSelector(const std::string& host, const uint16_t port = 0);

    /// @brief Constructor for selecting a backend using JSON access map.
    ///
    /// The provided access map must have the same structure as an element
    /// of the "config-databases" configuration parameter. However, it merely
    /// takes into account: "type", "host" and "port" parameters. In addition,
    /// these parameters are optional. The following are valid combinations:
    ///
    /// @code
    /// {
    ///     "type": "mysql"
    /// }
    /// @endcode
    ///
    /// @code
    /// {
    ///     "host": "somehost.example.org"
    /// }
    /// @endcode
    ///
    /// @code
    /// {
    ///     "host": "somehost.example.org",
    ///     "port": 1234
    /// }
    /// @endcode
    ///
    /// @code
    /// {
    ///     "type": "mysql"
    ///     "host": "somehost.example.org",
    /// }
    /// @endcode
    ///
    /// @code
    /// {
    ///     "type": "mysql"
    ///     "host": "somehost.example.org",
    ///     "port": 1234
    /// }
    /// @endcode
    ///
    /// where "type" can be any of the supported backend types.
    ///
    /// This constructor is useful for creating backend selectors from the
    /// received control commands.
    ///
    /// @param access_map Access map as provided above.
    explicit BackendSelector(const data::ConstElementPtr& access_map);

    /// @brief Returns instance of the "unspecified" backend selector.
    static const BackendSelector& UNSPEC();

    /// @brief Checks if selector is "unspecified".
    ///
    /// @return true if backend type is @c UNSPEC, hostname is empty and
    /// port number 0, false otherwise.
    bool amUnspecified() const;

    /// @brief Returns backend type selected.
    Type getBackendType() const {
        return (backend_type_);
    }

    /// @brief Returns host selected.
    ///
    /// @return host if specified or empty string if host is not
    /// specified.
    std::string getBackendHost() const {
        return (host_);
    }

    /// @brief Returns port selected.
    ///
    /// @return port number of the selected backend or 0 if port number
    /// is not specified.
    uint16_t getBackendPort() const {
        return (port_);
    }

    /// @brief Returns selections as text.
    ///
    /// @return Collection of comma separated selections, e.g.
    /// "type=mysql,host=somehost.example.org,port=1234".
    std::string toText() const;

    /// @brief Converts string to backend type.
    ///
    /// @param type Backend type as string.
    static Type stringToBackendType(const std::string& type);

    /// @brief Converts backend type to string.
    ///
    /// @param type Backend type to be converted.
    static std::string backendTypeToString(const Type& type);


private:

    /// @brief Checks if the specified selector is valid.
    ///
    /// It checks if the port number is specified in conjuction with
    /// host.
    /// @throw BadValue if selector validation fails.
    void validate() const;

    /// @brief Backend type selected.
    Type backend_type_;

    /// @brief Host selected.
    std::string host_;

    /// @brief Port number selected.
    uint16_t port_;
};

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
    ///                       const BackendSelector& selector,
    ///                       const ServerSelector& server_selector) const {
    ///     Subnet4Ptr subnet;
    ///     getPropertyPtrConst<Subnet4Ptr, const SubnetID&, ConfigBackendDHCPv4::getSubnet4>
    ///         (&ConfigBackendDHCPv4::getSubnet4, selector, subnet, subnet_id);
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
    /// @tparam InputType Type of the objects used as input to the backend call.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param selector Backend selector.
    /// @param server_selector Server selector.
    /// @param [out] property Reference to the shared pointer where retrieved
    /// property should be assigned.
    /// @param input Values to be used as input to the backend call.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    template<typename PropertyType, typename... InputType>
    void getPropertyPtrConst(PropertyType (ConfigBackendType::*MethodPointer)
                             (const ServerSelector&, InputType...) const,
                             const BackendSelector& selector,
                             const ServerSelector& server_selector,
                             PropertyType& property,
                             InputType... input) const {

        // If no particular backend is selected, call each backend and return
        // the first non-null (non zero) value.
        if (selector.amUnspecified()) {
            for (auto backend : backends_) {
                property = ((*backend).*MethodPointer)(server_selector, input...);
                if (property) {
                    break;
                }
            }

        } else {
            // Backend selected, find the one that matches selection.
            auto backends = selectBackends(selector);
            if (!backends.empty()) {
                for (auto backend : backends) {
                    property = ((*backend).*MethodPointer)(server_selector, input...);
                    if (property) {
                        break;
                    }
                }

            } else {
                isc_throw(db::NoSuchDatabase, "no such database found for selector: "
                          << selector.toText());
            }
        }
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
    /// Subnet6Collection getModifiedSubnets6(const BackendSelector& selector,
    ///                                       const ServerSelector& server_selector,
    ///                                       const ptime& modification_time) const {
    ///     Subnet6Collection subnets;
    ///     getMultiplePropertiesConst<Subnet6Collection, const ptime&>
    ///         (&ConfigBackendDHCPv6::getSubnets6, selector, subnets,
    ///          modification_time);
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
    /// @tparam InputType Type of the objects used as input to the backend call.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param selector Backend selector.
    /// @param server_selector Server selector.
    /// @param [out] properties Reference to the collection of retrieved properties.
    /// @param input Values to be used as input to the backend call.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    template<typename PropertyCollectionType, typename... InputType>
    void getMultiplePropertiesConst(PropertyCollectionType (ConfigBackendType::*MethodPointer)
                                    (const ServerSelector&, InputType...) const,
                                    const BackendSelector& selector,
                                    const ServerSelector& server_selector,
                                    PropertyCollectionType& properties,
                                    InputType... input) const {
        if (selector.amUnspecified()) {
            for (auto backend : backends_) {
                properties = ((*backend).*MethodPointer)(server_selector, input...);
                if (!properties.empty()) {
                    break;
                }
            }

        } else {
            auto backends = selectBackends(selector);
            if (!backends.empty()) {
                for (auto backend : backends) {
                    properties = ((*backend).*MethodPointer)(server_selector, input...);
                    if (!properties.empty()) {
                        break;
                    }
                }

            } else {
                isc_throw(db::NoSuchDatabase, "no database found for selector: "
                          << selector.toText());
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
    ///         (&ConfigBackendDHCPv4::getAllSubnets4, subnets, selector,
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
    /// @param selector Backend selector.
    /// @param server_selector Server selector.
    /// @param [out] properties Reference to the collection of retrieved properties.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    template<typename PropertyCollectionType>
    void getAllPropertiesConst(PropertyCollectionType (ConfigBackendType::*MethodPointer)
                               (const ServerSelector&) const,
                               const BackendSelector& selector,
                               const ServerSelector& server_selector,
                               PropertyCollectionType& properties) const {
        if (selector.amUnspecified()) {
            for (auto backend : backends_) {
                properties = ((*backend).*MethodPointer)(server_selector);
                if (!properties.empty()) {
                    break;
                }
            }

        } else {
            auto backends = selectBackends(selector);
            if (!backends.empty()) {
                for (auto backend : backends) {
                    properties = ((*backend).*MethodPointer)(server_selector);
                    if (!properties.empty()) {
                        break;
                    }
                }

            } else {
                isc_throw(db::NoSuchDatabase, "no database found for selector: "
                          << selector.toText());
            }
        }
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
    ///                          const BackendSelector& selector,
    ///                          const ServerSelector& server_selector) {
    ///     createUpdateDeleteProperty<const Subnet6Ptr&>
    ///         (&ConfigBackendDHCPv6::createUpdateSubnet6, selector,
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
    /// @tparam InputType Type of the objects being used as arguments of the
    /// backend method, e.g. new property to be added, updated or deleted.
    ///
    /// @param MethodPointer Pointer to the backend method to be called.
    /// @param selector Backend selector.
    /// @param server_selector Server selector.
    /// @param input Objects used as arguments to the backend method to be
    /// called.
    ///
    /// @throw db::NoSuchDatabase if no database matching the given selector
    /// was found.
    /// @throw db::AmbiguousDatabase if multiple databases matching the selector
    /// were found.
    template<typename... InputType>
    void createUpdateDeleteProperty(void (ConfigBackendType::*MethodPointer)
                                    (const ServerSelector&, InputType...),
                                    const BackendSelector& selector,
                                    const ServerSelector& server_selector,
                                    InputType... input) {
        auto backends = selectBackends(selector);
        if (backends.empty()) {
            isc_throw(db::NoSuchDatabase, "no database found for selector: "
                      << selector.toText());

        } else if (backends.size() > 1) {
            isc_throw(db::AmbiguousDatabase, "more than 1 database found for "
                      "selector: " << selector.toText());
        }

        (*(*(backends.begin())).*MethodPointer)(server_selector, input...);
    }

    /// @brief Selects existing backends matching the selector.
    ///
    /// This method selects backends matching the selector. If the selector is
    /// "unspecified" or there is no backend in the pool, an empty list is returned.
    ///
    /// @param selector Selector for which matching backends should be selected.
    std::list<ConfigBackendTypePtr> selectBackends(const BackendSelector& selector) const {

        std::list<ConfigBackendTypePtr> selected;

        // In case there is only one backend, it is allowed to not select the
        // database backend.
        if ((backends_.size() == 1) && selector.amUnspecified()) {
            selected.push_back(*backends_.begin());
            return (selected);
        }

        // For other cases we return empty list.
        if (backends_.empty() || selector.amUnspecified()) {
            return (selected);
        }

        // Go over all backends.
        for (auto backend : backends_) {
            // If backend type is specified and it is not matching,
            // do not select this backend.
            if ((selector.getBackendType() != BackendSelector::Type::UNSPEC) &&
                (selector.getBackendType() !=
                 BackendSelector::stringToBackendType(backend->getType()))) {
                continue;
            }

            // If the host has been specified by the backend's host is not
            // matching, do not select this backend.
            if ((!selector.getBackendHost().empty()) &&
                (selector.getBackendHost() != backend->getHost())) {
                continue;
            }

            // If the port has been specified by the backend's port is not
            // matching, do not select this backend.
            if ((selector.getBackendPort() != 0) &&
                (selector.getBackendPort() != backend->getPort())) {
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
