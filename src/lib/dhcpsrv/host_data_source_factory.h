// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef HOST_DATA_SOURCE_FACTORY_H
#define HOST_DATA_SOURCE_FACTORY_H

#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/database_connection.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Invalid type exception
///
/// Thrown when the factory doesn't recognise the type of the backend.
class InvalidType : public Exception {
public:
    InvalidType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

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
};


}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
