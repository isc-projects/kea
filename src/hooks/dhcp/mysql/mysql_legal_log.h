// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_LEGAL_LOG_H
#define MYSQL_LEGAL_LOG_H

#include <dhcpsrv/legal_log_mgr_factory.h>
#include <mysql/mysql_connection.h>
#include <util/reconnect_ctl.h>

#include <boost/scoped_ptr.hpp>
#include <mysql.h>

#include <mutex>
#include <vector>

namespace isc {
namespace dhcp {

// Forward declaration of the exchange object. The class is defined in
// the .cc file.
class MySqlLegLExchange;

/// @brief MySQL Store Context
///
/// This class stores the thread context for the store pool.
/// The class is needed by writeln function which must use an exchange
/// to perform database operations.
/// Each context provides such exchange for each thread.
/// The context instances are lazy initialized by the requesting thread by using
/// the store's createContext function and are destroyed when the store's
/// pool instance is destroyed.
class MySqlStoreContext {
public:

    /// @brief Constructor
    ///
    /// @param parameters See MySqlStore constructor.
    /// @param io_service_accessor The IOService accessor function.
    /// @param db_reconnect_callback The connection recovery callback.
    MySqlStoreContext(const db::DatabaseConnection::ParameterMap& parameters,
                      db::IOServiceAccessorPtr io_service_accessor,
                      db::DbCallback db_reconnect_callback);

    /// The exchange objects is used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)
    boost::scoped_ptr<MySqlLegLExchange> exchange_; ///< Exchange object

    /// @brief MySQL connection
    db::MySqlConnection conn_;
};

/// @brief Type of pointers to contexts.
typedef boost::shared_ptr<MySqlStoreContext> MySqlStoreContextPtr;

/// @brief MySQL Store Context Pool
///
/// This class provides a pool of contexts
/// The store will use this class to handle available contexts.
class MySqlStoreContextPool {
public:

    /// @brief The vector of available contexts.
    std::vector<MySqlStoreContextPtr> pool_;

    /// @brief The mutex to protect pool access.
    std::mutex mutex_;
};

/// @brief Type of pointers to context pools.
typedef boost::shared_ptr<MySqlStoreContextPool> MySqlStoreContextPoolPtr;

/// @brief MySQL Store
///
/// This class provides the @ref isc::legal_log::LegalLogMgr
/// interface to the MySQL database. Use of this backend presupposes
/// that a MySQL database is available and that the Kea legal log
/// schema has been created within it.

class MySqlStore : public LegalLogMgr {
public:

    /// @brief Constructor
    ///
    /// @note The supported parameters are:
    /// - database parameters:
    ///       - name
    ///       - host
    ///       - password
    ///       - port
    ///       - user
    ///       - trust-anchor
    ///       - cert-file
    ///       - key-file
    ///       - cipher-list (MySQL only)
    ///       - reconnect-wait-time
    ///       - max-reconnect-tries
    ///       - on-fail
    ///       - retry-on-startup
    ///       - connect-timeout
    ///       - read-timeout (MySQL only)
    ///       - write-timeout (MySQL only)
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @throw isc::db::NoDatabaseName Mandatory database name not given
    MySqlStore(const isc::db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (close database)
    virtual ~MySqlStore();

    /// @brief Create a new context.
    ///
    /// The database is opened with all the SQL commands pre-compiled.
    ///
    /// @return A new (never null) context.
    ///
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given.
    /// @throw isc::db::DbOperationError An operation on the open database has
    /// failed.
    MySqlStoreContextPtr createContext() const;

    /// @brief Attempts to reconnect the server to the forensic log DB backend.
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's forensic log DB backends after connectivity has been lost. Upon
    /// entry it will attempt to reconnect via @ref MySqlStore::open.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters.
    /// @return true if connection has been recovered, false otherwise.
    static bool dbReconnect(isc::util::ReconnectCtlPtr db_reconnect_ctl);

    /// If the database is successfully opened, the version number in the
    /// legal_logschema_version table will be checked against hard-coded
    /// value in the implementation file.
    ///
    /// Finally, all the SQL commands are pre-compiled.
    ///
    /// @throw isc::db::DbOpenError Error opening the database
    /// @throw isc::db::DbOperationError An operation on the open
    ///        database has failed.
    virtual void open();

    /// @brief Closes the store.
    virtual void close();

    /// @brief Stores the string with a timestamp.
    ///
    /// @param addr Address or prefix
    /// @param text String to store
    /// @throw LegalLogMgrError if the write fails
    virtual void writeln(const std::string& text, const std::string& addr);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "logfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("mysql"));
    }

    /// @brief Returns backend version.
    ///
    /// @param timer_name The DB reconnect timer name.
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::db::DbOperationError An operation on the open
    ///        database has failed.
    virtual std::pair<uint32_t, uint32_t> getVersion(const std::string& timer_name = std::string()) const;

    /// @brief Local version of getDBVersion() class method.
    static std::string getDBVersion();

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements
    enum StatementIndex {
        INSERT_LOG,             // Add entry to logs table
        NUM_STATEMENTS          // Number of statements
    };

    /// @brief Flag which indicates if the store has at least one
    /// unusable connection.
    ///
    /// @return true if there is at least one unusable connection, false
    /// otherwise
    virtual bool isUnusable();

    /// @brief Context RAII Allocator.
    class MySqlStoreContextAlloc {
    public:

        /// @brief Constructor
        ///
        /// This constructor takes a context of the pool if one is available
        /// or creates a new one.
        ///
        /// @param store A parent instance
        MySqlStoreContextAlloc(MySqlStore& store);

        /// @brief Destructor
        ///
        /// This destructor puts back the context in the pool.
        ~MySqlStoreContextAlloc();

        /// @brief The context
        MySqlStoreContextPtr ctx_;

    private:
        /// @brief The store
        MySqlStore& store_;
    };

private:

    /// @brief Check Error and Throw Exception
    ///
    /// This method invokes @ref MySqlConnection::checkError.
    ///
    /// @param ctx Context
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @throw isc::db::DbOperationError An operation on the open
    ///        database has failed.
    void checkError(MySqlStoreContextPtr& ctx,
                    int status,
                    StatementIndex index,
                    const char* what) const;

    // Members

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;

    /// @brief The pool of contexts
    MySqlStoreContextPoolPtr pool_;

    /// @brief Indicates if there is at least one connection that can no longer
    /// be used for normal operations.
    bool unusable_;

public:
    /// @brief Factory class method.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @return The MySQL Store.
    static LegalLogMgrPtr
    factory(const isc::db::DatabaseConnection::ParameterMap& parameters);
};

/// @brief Initialization structure used to register and deregister MySQL Forensic Backend.
struct MySqlForensicBackendInit {
    // Constructor registers
    MySqlForensicBackendInit() {
        LegalLogMgrFactory::registerBackendFactory("mysql",
                                                    MySqlStore::factory,
                                                    true,
                                                    MySqlStore::getDBVersion);
    }

    // Destructor deregisters
    ~MySqlForensicBackendInit() {
        LegalLogMgrFactory::unregisterBackendFactory("mysql", true);
    }
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // MYSQL_LEGAL_LOG_H
