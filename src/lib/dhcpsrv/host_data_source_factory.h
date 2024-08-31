// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_DATA_SOURCE_FACTORY_H
#define HOST_DATA_SOURCE_FACTORY_H

#include <database/database_connection.h>
#include <dhcpsrv/base_host_data_source.h>
#include <exceptions/exceptions.h>

#include <functional>
#include <string>
#include <vector>
#include <map>

namespace isc {
namespace dhcp {

/// @brief No host data source instance exception
///
/// Thrown if an attempt is made to get a reference to the current
/// host data source instance and none is currently available.
class NoHostDataSourceManager : public Exception {
public:
    NoHostDataSourceManager(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Host Data Source Factory
///
/// This class comprises nothing but static methods used to create a host data
/// source object. It analyzes the database information passed to the creation
/// function and instantiates an appropriate host data source object based on
/// the type requested.
///
/// Strictly speaking these functions could be stand-alone functions.  However,
/// it is convenient to encapsulate them in a class for naming purposes.

class HostDataSourceFactory {
public:
    /// @brief Create and add an instance of a host data source.
    ///
    /// Each database backend has its own host data source type. This static
    /// method adds an object of the appropriate type to a list of
    /// host data sources.
    ///
    /// dbaccess is a generic way of passing parameters. Parameters are passed
    /// in the "name=value" format, separated by spaces.  The data MUST include
    /// a keyword/value pair of the form "type=dbtype" giving the database
    /// type, e.q. "mysql" or "sqlite3".
    ///
    /// @param sources host data source list (new backend will be added here)
    /// @param dbaccess Database access parameters.  These are in the form of
    ///        "keyword=value" pairs, separated by spaces. They are backend-
    ///        -end specific, although must include the "type" keyword which
    ///        gives the backend in use.
    ///
    /// @throw isc::InvalidParameter dbaccess string does not contain the "type"
    ///        keyword.
    /// @throw isc::dhcp::InvalidType The "type" keyword in dbaccess does not
    ///        identify a supported backend.
    static void add(HostDataSourceList& sources, const std::string& dbaccess);

    /// @brief Delete a host data source.
    ///
    /// Delete the first instance of a host data source of the given type.
    /// This should have the effect of closing the database connection.
    ///
    /// @param sources host data source list.
    /// @param db_type database backend type.
    /// @return true when found and removed, false when not found.
    static bool del(HostDataSourceList& sources, const std::string& db_type);

    /// @brief Delete a host data source.
    ///
    /// Delete the first instance of a host data source which matches specific
    /// parameters.
    /// This should have the effect of closing the database connection.
    ///
    /// @param sources host data source list.
    /// @param db_type database backend type.
    /// @param dbaccess Database access parameters.  These are in the form of
    ///        "keyword=value" pairs, separated by spaces. They are backend-
    ///        -end specific, although must include the "type" keyword which
    ///        gives the backend in use.
    /// @param if_unusable flag which indicates if the host data source should
    ///        be deleted only if it is unusable.
    /// @return false when not removed because it is not found or because it is
    /// still usable (if_unusable is true), true otherwise.
    static bool del(HostDataSourceList& sources, const std::string& db_type,
                    const std::string& dbaccess, bool if_unusable = true);

    /// @brief Type of host data source factory
    ///
    /// A factory takes a parameter map and returns a pointer to a host
    /// data source. In case of failure it must throw and not return NULL.
    typedef std::function<HostDataSourcePtr (const db::DatabaseConnection::ParameterMap&)> Factory;

    /// @brief Register a host data source factory
    ///
    /// Associate the factory to a database type in the map.
    /// The no_log is to avoid logging before the logger is initialized
    /// as when called at global object initialization.
    ///
    /// @param db_type database type
    /// @param factory host data source factory
    /// @param no_log do not log (default false)
    /// @return true if the factory was successfully added to the map, false
    /// if it already exists.
    static bool registerFactory(const std::string& db_type,
                                const Factory& factory, bool no_log = false);

    /// @brief Deregister a host data source factory
    ///
    /// Disassociate the factory to a database type in the map.
    /// The no_log is to avoid logging during global object deinitialization.
    ///
    /// @param db_type database type
    /// @param no_log do not log (default false)
    /// @return true if the factory was successfully removed from the map,
    /// false if it was not found.
    static bool deregisterFactory(const std::string& db_type,
                                  bool no_log = false);

    /// @brief Check if a host data source factory was registered
    ///
    /// @param db_type database type
    /// @return true if a factory was registered for db_type, false if not.
    static bool registeredFactory(const std::string& db_type);

    /// @brief Prints out all registered backends.
    ///
    /// We need a dedicated method for this, because we sometimes can't log
    /// the backend type when doing early initialization for backends
    /// initialized statically.
    static void printRegistered();

private:
    /// @brief Factory map
    static std::map<std::string, Factory> map_;
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif
