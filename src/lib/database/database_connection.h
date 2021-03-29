// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Invalid 'readonly' value specification.
///
/// Thrown when the value of the 'readonly' boolean parameter is invalid.
class DbInvalidReadOnly : public Exception {
public:
    DbInvalidReadOnly(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Type of action to take on connection loss.
enum class OnFailAction {
    STOP_RETRY_EXIT,
    SERVE_RETRY_EXIT,
    SERVE_RETRY_CONTINUE
};

/// @brief Warehouses DB reconnect control values
///
/// When a DatabaseConnection loses connectivity to its backend, it
/// creates an instance of this class based on its configuration parameters and
/// passes the instance into connection's DB lost callback.  This allows
/// the layer(s) above the connection to know how to proceed.
///
class ReconnectCtl {
public:
    /// @brief Constructor.
    ///
    /// @param backend_type type of the caller backend.
    /// @param timer_name timer associated to this object.
    /// @param max_retries maximum number of reconnect attempts to make.
    /// @param retry_interval amount of time to between reconnect attempts.
    /// @param action which should be taken on connection loss.
    ReconnectCtl(const std::string& backend_type, const std::string& timer_name,
                 unsigned int max_retries, unsigned int retry_interval,
                 OnFailAction action) :
          backend_type_(backend_type), timer_name_(timer_name),
          max_retries_(max_retries), retries_left_(max_retries),
          retry_interval_(retry_interval), action_(action) {}

    /// @brief Returns the type of the caller backend.
    std::string backendType() const {
        return (backend_type_);
    }

    /// @brief Returns the associated timer name.
    ///
    /// @return the associated timer.
    std::string timerName() const {
        return (timer_name_);
    }

    /// @brief Decrements the number of retries remaining
    ///
    /// Each call decrements the number of retries by one until zero is reached.
    /// @return true the number of retries remaining is greater than zero.
    bool checkRetries() {
        return (retries_left_ ? --retries_left_ : false);
    }

    /// @brief Returns the maximum number of retries allowed.
    unsigned int maxRetries() {
        return (max_retries_);
    }

    /// @brief Returns the number for retries remaining.
    unsigned int retriesLeft() {
        return (retries_left_);
    }

    /// @brief Returns the amount of time to wait between reconnect attempts.
    unsigned int retryInterval() {
        return (retry_interval_);
    }

    /// @brief Resets the retries count.
    void resetRetries() {
        retries_left_ = max_retries_;
    }

    /// @brief Return true if the connection loss should affect the service,
    /// false otherwise
    bool alterServiceState() {
        return (action_ == OnFailAction::STOP_RETRY_EXIT);
    }

    /// @brief Return true if the connection recovery mechanism should shut down
    /// the server on failure, false otherwise.
    bool exitOnFailure() {
        return ((action_ == OnFailAction::STOP_RETRY_EXIT) ||
                (action_ == OnFailAction::SERVE_RETRY_EXIT));
    }

    /// @brief Convert action to string.
    ///
    /// @param action The action type to be converted to text.
    /// @return The text representation of the action type.
    static std::string onFailActionToText(OnFailAction action);

    /// @brief Convert string to action.
    ///
    /// @param text The text to be converted to action type.
    /// @return The action type corresponding to the text representation.
    static OnFailAction onFailActionFromText(const std::string& text);

private:

    /// @brief Caller backend type.
    const std::string backend_type_;

    /// @brief Timer associated to this object.
    std::string timer_name_;

    /// @brief Maximum number of retry attempts to make.
    unsigned int max_retries_;

    /// @brief Number of attempts remaining.
    unsigned int retries_left_;

    /// @brief The amount of time to wait between reconnect attempts.
    unsigned int retry_interval_;

    /// @brief Action to take on connection loss.
    OnFailAction action_;
};

/// @brief Pointer to an instance of ReconnectCtl
typedef boost::shared_ptr<ReconnectCtl> ReconnectCtlPtr;

/// @brief Defines a callback prototype for propagating events upward
typedef std::function<bool (ReconnectCtlPtr db_reconnect_ctl)> DbCallback;

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
    ReconnectCtlPtr reconnectCtl() {
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
    static bool invokeDbLostCallback(const ReconnectCtlPtr& db_reconnect_ctl);

    /// @brief Invokes the connection's restored connectivity callback
    ///
    /// @return Returns the result of the callback or false if there is no
    /// callback.
    static bool invokeDbRecoveredCallback(const ReconnectCtlPtr& db_reconnect_ctl);

    /// @brief Invokes the connection's restore failed connectivity callback
    ///
    /// @return Returns the result of the callback or false if there is no
    /// callback.
    static bool invokeDbFailedCallback(const ReconnectCtlPtr& db_reconnect_ctl);

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
    ReconnectCtlPtr reconnect_ctl_;
};

}  // namespace db
}  // namespace isc

#endif // DATABASE_CONNECTION_H
