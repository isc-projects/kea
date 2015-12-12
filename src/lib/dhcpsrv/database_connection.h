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

#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <boost/noncopyable.hpp>
#include <exceptions/exceptions.h>
#include <map>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Exception thrown if name of database is not specified
class NoDatabaseName : public Exception {
public:
    NoDatabaseName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception thrown on failure to open database
class DbOpenError : public Exception {
public:
    DbOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception thrown on failure to execute a database function
class DbOperationError : public Exception {
public:
    DbOperationError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


/// @brief Common database connection class.
///
/// This class provides functions that are common for establishing
/// connection with different types of databases; enables operations
/// on access parameters strings. In particular, it provides a way
/// to parse parameters in key=value format. This class is expected
/// to be a base class for all @ref LeaseMgr and possibly
/// @ref BaseHostDataSource derived classes.
class DatabaseConnection : public boost::noncopyable {
public:

    /// @brief Defines maximum value for time that can be reliably stored.
    ///
    /// @todo: Is this common for MySQL and Postgres? Maybe we should have
    /// specific values for each backend?
    ///
    /// If I'm still alive I'll be too old to care. You fix it.
    static const time_t MAX_DB_TIME;

    /// @brief Database configuration parameter map
    typedef std::map<std::string, std::string> ParameterMap;

    /// @brief Constructor
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    explicit DatabaseConnection(const ParameterMap& parameters)
        : parameters_(parameters) {
    }

    /// @brief Returns value of a connection parameter.
    ///
    /// @param name Name of the parameter which value should be returned.
    /// @return Value of one of the connection parameters.
    /// @throw BadValue if parameter is not found
    std::string getParameter(const std::string& name) const;

    /// @brief Parse database access string
    ///
    /// Parses the string of "keyword=value" pairs and separates them
    /// out into the map.
    ///
    /// @param dbaccess Database access string.
    ///
    /// @return @ref ParameterMap of keyword/value pairs.
    static ParameterMap parse(const std::string& dbaccess);

    /// @brief Redact database access string
    ///
    /// Takes the database parameters and returns a database access string
    /// passwords replaced by asterisks. This string is used in log messages.
    ///
    /// @param parameters Database access parameters (output of "parse").
    ///
    /// @return Redacted database access string.
    static std::string redactedAccessString(const ParameterMap& parameters);

private:

    /// @brief List of parameters passed in dbconfig
    ///
    /// That will be mostly used for storing database name, username,
    /// password and other parameters required for DB access. It is not
    /// intended to keep any DHCP-related parameters.
    ParameterMap parameters_;

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DATABASE_CONNECTION_H
