// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <exceptions/exceptions.h>
#include <util/reconnect_ctl.h>
#include <functional>
#include <map>
#include <string>

namespace isc {
namespace db {

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

/// @brief Exception thrown when a specific connection has been rendered unusable
/// either through loss of connectivity or API lib error
class DbConnectionUnusable : public Exception {
public:
    DbConnectionUnusable(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


/// @brief Invalid type exception
///
/// Thrown when the factory doesn't recognize the type of the backend.
class InvalidType : public Exception {
public:
    InvalidType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Invalid Timeout
///
/// Thrown when the timeout specified for the database connection is invalid.
class DbInvalidTimeout : public Exception {
public:
    DbInvalidTimeout(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Invalid port number
///
/// Thrown when the port number specified for the database connection is invalid.
class DbInvalidPort : public Exception {
public:
    DbInvalidPort(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Invalid 'readonly' value specification.
///
/// Thrown when the value of the 'readonly' boolean parameter is invalid.
class DbInvalidReadOnly : public Exception {
public:
    DbInvalidReadOnly(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Defines a callback prototype for propagating events upward
typedef std::function<bool (util::ReconnectCtlPtr db_reconnect_ctl)> DbCallback;

/// @brief Function which returns the IOService that can be used to recover the
/// connection.
///
/// This accessor is used to lazy retrieve the IOService when the connection is
/// lost. It is useful to retrieve it at a later time to support hook libraries
/// which create managers on load and set IOService later on by using the
/// dhcp4_srv_configured and dhcp6_srv_configured hooks.
typedef std::function<isc::asiolink::IOServicePtr ()> IOServiceAccessor;

/// @brief Pointer to an instance of IOServiceAccessor
typedef boost::shared_ptr<IOServiceAccessor> IOServiceAccessorPtr;

/// @brief Common database connection class.
///
/// This class provides functions that are common for establishing
/// connection with different types of databases; enables operations
/// on access parameters strings. In particular, it provides a way
/// to parse parameters in key=value format. This class is expected
/// to be a base class for all @ref isc::dhcp::LeaseMgr and possibly
/// @ref isc::dhcp::BaseHostDataSource derived classes.
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
    /// @param callback The connection recovery callback.
    DatabaseConnection(const ParameterMap& parameters,
                       DbCallback callback = DbCallback())
        : parameters_(parameters), callback_(callback), unusable_(false) {
    }

    /// @brief Destructor
    virtual ~DatabaseConnection(){};

    /// @brief Instantiates a ReconnectCtl based on the connection's
    /// reconnect parameters
    ///
    /// @param timer_name of the timer used for the ReconnectCtl object.
    virtual void makeReconnectCtl(const std::string& timer_name);

    /// @brief The reconnect settings.
    ///
    /// @return The reconnect settings.
    util::ReconnectCtlPtr reconnectCtl() {
        return (reconnect_ctl_);
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
    /// out into the map. A value of the password parameter may include
    /// whitespace in which case it must be surrounded by apostrophes.
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

    /// @brief Convenience method checking if database should be opened with
    /// read only access.
    ///
    /// @return true if "readonly" parameter is specified and set to true;
    /// false if "readonly" parameter is not specified or it is specified
    /// and set to false.
    bool configuredReadOnly() const;

    /// @brief Invokes the connection's lost connectivity callback
    ///
    /// @return Returns the result of the callback or false if there is no
    /// callback.
    static bool invokeDbLostCallback(const util::ReconnectCtlPtr& db_reconnect_ctl);

    /// @brief Invokes the connection's restored connectivity callback
    ///
    /// @return Returns the result of the callback or false if there is no
    /// callback.
    static bool invokeDbRecoveredCallback(const util::ReconnectCtlPtr& db_reconnect_ctl);

    /// @brief Invokes the connection's restore failed connectivity callback
    ///
    /// @return Returns the result of the callback or false if there is no
    /// callback.
    static bool invokeDbFailedCallback(const util::ReconnectCtlPtr& db_reconnect_ctl);

    /// @brief Unparse a parameter map
    ///
    /// @param params the parameter map to unparse
    /// @return a pointer to configuration
    static isc::data::ElementPtr toElement(const ParameterMap& params);

    /// @brief Unparse an access string
    ///
    /// @param dbaccess the database access string
    /// @return a pointer to configuration
    static isc::data::ElementPtr toElementDbAccessString(const std::string& dbaccess);

    /// @brief Optional callback function to invoke if an opened connection is
    /// lost
    static DbCallback db_lost_callback_;

    /// @brief Optional callback function to invoke if an opened connection
    /// recovery succeeded
    static DbCallback db_recovered_callback_;

    /// @brief Optional callback function to invoke if an opened connection
    /// recovery failed
    static DbCallback db_failed_callback_;

    /// @brief Throws an exception if the connection is not usable.
    /// @throw DbConnectionUnusable
    void checkUnusable() {
        if (unusable_)  {
            isc_throw (DbConnectionUnusable, "Attempt to use an invalid connection");
        }
    }

    /// @brief Flag which indicates if connection is unusable.
    ///
    /// @return true if the connection is unusable, false otherwise
    bool isUnusable() {
        return (unusable_);
    }

protected:
    /// @brief Sets the unusable flag to true.
    void markUnusable() { unusable_ = true; }

private:

    /// @brief List of parameters passed in dbconfig
    ///
    /// That will be mostly used for storing database name, username,
    /// password and other parameters required for DB access. It is not
    /// intended to keep any DHCP-related parameters.
    ParameterMap parameters_;

protected:

    /// @brief The callback used to recover the connection.
    DbCallback callback_;

private:

    /// @brief Indicates if the connection can no longer be used for normal
    /// operations. Typically a connection is marked unusable after an unrecoverable
    /// DB error. There may be a time when the connection exists, after
    /// such an event, during which it cannot be used for anything beyond checking
    /// parameters and error information. This flag can be used as a guard in
    /// code to prevent inadvertent use of a broken connection.
    bool unusable_;

    /// @brief Reconnect settings.
    util::ReconnectCtlPtr reconnect_ctl_;
};

}  // namespace db
}  // namespace isc

#endif // DATABASE_CONNECTION_H
