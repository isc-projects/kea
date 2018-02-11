// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_DATA_SOURCE_FACTORY_H
#define HOST_DATA_SOURCE_FACTORY_H

#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/database_connection.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <string>
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
/// This class comprises nothing but static methods used to create a host data source object.
/// It analyzes the database information passed to the creation function and instantiates
/// an appropriate host data source object based on the type requested.
///
/// Strictly speaking these functions could be stand-alone functions.  However,
/// it is convenient to encapsulate them in a class for naming purposes.

class HostDataSourceFactory {
public:
    /// @brief Create an instance of a host data source.
    ///
    /// Each database backend has its own host data source type. This static
    /// method sets the "current" host data source to be an object of the
    /// appropriate type.  The actual host data source is returned by the
    /// "instance" method.
    ///
    /// @note When called, the current host data source is <b>always</b> destroyed
    ///       and a new one created - even if the parameters are the same.
    ///
    /// dbaccess is a generic way of passing parameters. Parameters are passed
    /// in the "name=value" format, separated by spaces.  The data MUST include
    /// a keyword/value pair of the form "type=dbtype" giving the database
    /// type, e.q. "mysql" or "sqlite3".
    ///
    /// @param dbaccess Database access parameters.  These are in the form of
    ///        "keyword=value" pairs, separated by spaces. They are backend-
    ///        -end specific, although must include the "type" keyword which
    ///        gives the backend in use.
    ///
    /// @throw isc::InvalidParameter dbaccess string does not contain the "type"
    ///        keyword.
    /// @throw isc::dhcp::InvalidType The "type" keyword in dbaccess does not
    ///        identify a supported backend.
    static void create(const std::string& dbaccess);

    /// @brief Destroy host data source
    ///
    /// Destroys the current host data source object. This should have the effect
    /// of closing the database connection.  The method is a no-op if no
    /// host data source is available.
    static void destroy();

    /// @brief Hold pointer to host data source instance
    ///
    /// Holds a pointer to the singleton host data source.  The singleton
    /// is encapsulated in this method to avoid a "static initialization
    /// fiasco" if defined in an external static variable.
    static HostDataSourcePtr& getHostDataSourcePtr();

    /// @brief Type of host data source factory
    ///
    /// A factory takes a parameter map and returns a pointer to a host
    /// data source. In case of failure it must throw and not return NULL.
    typedef boost::function<BaseHostDataSource*(const DatabaseConnection::ParameterMap&)> Factory;

    /// @brief Register a host data source factory
    ///
    /// Associate the factory to a database type in the map.
    ///
    /// @param db_type database type
    /// @param factory host data source factory
    /// @return true if the factory was successfully added to the map, false
    /// if it already exists.
    static bool registerFactory(const std::string& db_type,
                                const Factory& factory);

    /// @brief Deregister a host data source factory
    ///
    /// Disassociate the factory to a database type in the map.
    ///
    /// @param db_type database type
    /// @return true if the factory was successfully removed from the map,
    /// false if it was not found.
    static bool deregisterFactory(const std::string& db_type);

private:
    /// @brief Factory map
    static std::map<std::string, Factory> map_;
};


}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
