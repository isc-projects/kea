// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BACKEND_SELECTOR_H
#define BACKEND_SELECTOR_H

#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <cstdint>
#include <string>

namespace isc {
namespace db {

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
class BackendSelector : public data::CfgToElement {
public:

    /// @brief Supported database types.
    ///
    /// The @c UNSPEC indicates that the database type is not specified
    /// as selection criteria.
    enum class Type {
        MYSQL,
        POSTGRESQL,
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
    /// is optional and is ignored when set to 0. It must be used in conjunction
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

    /// @brief Unparse a backend selector object.
    ///
    /// The caller must ensure that the selector type is specified.
    ///
    /// @return A pointer to unparsed backend selector configuration.
    /// @throw BadValue If the backend selector type is unspecified.
    virtual data::ElementPtr toElement() const;

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
    /// It checks if the port number is specified in conjunction with
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


} // end of namespace isc::db
} // end of namespace isc

#endif
