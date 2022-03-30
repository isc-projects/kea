// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_CONFIG_BACKEND_H
#define BASE_CONFIG_BACKEND_H

#include <database/database_connection.h>

#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <set>
#include <string>

namespace isc {
namespace cb {

/// @brief Interface for Kea server specific configuration backend
/// implementations.
///
/// Each Kea server (e.g. DHCPv4 server) needs to implement its own
/// interface to store and fetch its configuration from the databases.
/// This is because each Kea server uses a different set of
/// configuration information. This is a base interface which should
/// be implemented (and extended) by respective Kea servers to provide
/// API to store and fetch configuration information from a database.
/// Such implementation is called configuration backend. Each
/// configuration backend facilitates a single database type, e.g. MySQL
/// database. In order to support multiple database types, i.e. MySQL,
/// PostgreSQL, each Kea server will have to implement 2 separate configuration
/// backends, one for each database type.
class BaseConfigBackend {
public:

    /// @brief Virtual destructor.
    virtual ~BaseConfigBackend() { }

    /// @brief Returns backend type in the textual format.
    ///
    /// @return Name of the storage for configurations, e.g. "mysql",
    /// "postgresql" and so forth.
    virtual std::string getType() const = 0;

    /// @brief Returns backend host.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return host on which the database is located.
    virtual std::string getHost() const = 0;

    /// @brief Returns backend port number.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return Port number on which database service is available.
    virtual uint16_t getPort() const = 0;

    /// @brief Flag which indicates if the config backend has an unusable
    /// connection.
    ///
    /// @return true if there is at least one unusable connection, false
    /// otherwise.
    virtual bool isUnusable() {
        return (false);
    }

    /// @brief Return backend parameters.
    ///
    /// Returns the backend parameters.
    ///
    /// @return Parameters of the backend.
    virtual isc::db::DatabaseConnection::ParameterMap getParameters() const {
        return (isc::db::DatabaseConnection::ParameterMap());
    }
};

/// @brief Shared pointer to the @c BaseConfigBackend.
typedef boost::shared_ptr<BaseConfigBackend> BaseConfigBackendPtr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // BASE_CONFIG_BACKEND_H
