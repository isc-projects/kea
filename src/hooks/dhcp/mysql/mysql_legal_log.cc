// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <mysql_fb_log.h>
#include <mysql_legal_log.h>
#include <dhcpsrv/legal_log_mgr_factory.h>
#include <dhcpsrv/legal_log_db_log.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/multi_threading_mgr.h>

#include <boost/array.hpp>
#include <mysqld_error.h>

#include <iomanip>
#include <limits.h>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace {

boost::array<TaggedStatement, MySqlStore::NUM_STATEMENTS>
tagged_statements = { {
    {MySqlStore::INSERT_LOG,
                 "INSERT INTO logs(address, log) VALUES (?, ?)"},
    }
};

};

namespace isc {
namespace dhcp {

/// @brief Supports exchanging log entries with MySQL.
class MySqlLegLExchange {
    /// @brief Set number of database columns for this log structure
    static const size_t LOG_COLUMNS = 2;

public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlLegLExchange() : addr_(""), log_(""),
                          addr_length_(0), addr_null_(MLM_FALSE) {

        std::fill(&error_[0], &error_[LOG_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[0] = "address";
        columns_[1] = "log";
        static_assert(1 < LOG_COLUMNS, "1 < LOG_COLUMNS");
    }

    /// @brief Destructor
    ~MySqlLegLExchange() = default;

    /// @brief Set error indicators
    ///
    /// Sets the error indicator for each of the MYSQL_BIND elements.  It points
    /// the "error" field within an element of the input array to the
    /// corresponding element of the passed error array.
    ///
    /// @param bind Array of BIND elements
    /// @param error Array of error elements.  If there is an error in getting
    ///        data associated with one of the "bind" elements, the
    ///        corresponding element in the error array is set to MLM_TRUE.
    /// @param count Size of each of the arrays.
    static void setErrorIndicators(MYSQL_BIND* bind, my_bool* error,
                                   size_t count) {
        for (size_t i = 0; i < count; ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<my_bool*>(&error[i]);
        }
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static string getColumnsInError(my_bool* error, std::string* names,
                                    size_t count) {
        string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < count; ++i) {
            if (error[i] == MLM_TRUE) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += names[i];
            }
        }

        if (result.empty()) {
            result = "(None)";
        }

        return (result);
    }

    /// @brief Create MYSQL_BIND objects for log entry
    ///
    /// Fills in the MYSQL_BIND array for sending data in the log entry to
    /// the database.
    ///
    /// @param addr address or prefix of the log entry
    /// @param log log entry to be added to the database.
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    vector<MYSQL_BIND> createBindForSend(const string& addr,
                                         const string& log) {

        // Store arguments to ensure they remain valid.
        addr_ = addr;
        log_ = log;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // Set up the structures for the various components of the log entry.

        try {
            // address : VARCHAR(43) NULL
            // Note that previously we used MYSQL_TYPE_VARCHAR instead of
            // MYSQL_TYPE_STRING. However, that caused 'buffer type not supported'
            // errors on some systems running MariaDB.
            if (!addr_.empty()) {
                addr_length_ = addr_.size();
                bind_[0].buffer_type = MYSQL_TYPE_STRING;
                bind_[0].buffer = const_cast<char*>(addr_.c_str());
                bind_[0].buffer_length = addr_length_;
                bind_[0].length = &addr_length_;
                // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                                  // reasons, see memset() above
            } else {
                bind_[0].buffer_type = MYSQL_TYPE_NULL;

                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                addr_null_ = MLM_TRUE;
                bind_[0].buffer = NULL;
                bind_[0].is_null = &addr_null_;
            }

            // log : TEXT NOT NULL
            bind_[1].buffer_type = MYSQL_TYPE_STRING;
            bind_[1].buffer = &log_[0];
            bind_[1].buffer_length = log_.length();
            // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // Add the error flags
            setErrorIndicators(bind_, error_, LOG_COLUMNS);

            // .. and check that we have the numbers correct at compile time.
            static_assert(1 < LOG_COLUMNS, "1 < LOG_COLUMNS");

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from log: '"
                      << log << "', reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (vector<MYSQL_BIND>(&bind_[0], &bind_[LOG_COLUMNS]));
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    string getErrorColumns() {
        return (getColumnsInError(error_, columns_, LOG_COLUMNS));
    }

private:

    MYSQL_BIND      bind_[LOG_COLUMNS];    ///< Bind array
    string          columns_[LOG_COLUMNS]; ///< Column names
    my_bool         error_[LOG_COLUMNS];   ///< Error array
    string          addr_;                 ///< Address or prefix
    string          log_;                  ///< Log entry
    unsigned long   addr_length_;          ///< Address length
    my_bool         addr_null_;            ///< Used when address is null
};

// MySqlStoreContext Constructor

MySqlStoreContext::MySqlStoreContext(const DatabaseConnection::ParameterMap& parameters,
                                     IOServiceAccessorPtr io_service_accessor,
                                     db::DbCallback db_reconnect_callback)
    : conn_(parameters, io_service_accessor, db_reconnect_callback) {
}

// MySqlStoreContextAlloc Constructor and Destructor

MySqlStore::MySqlStoreContextAlloc::MySqlStoreContextAlloc(MySqlStore& store)
    : ctx_(), store_(store) {

    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        {
            // we need to protect the whole pool_ operation, hence extra scope {}
            lock_guard<mutex> lock(store_.pool_->mutex_);
            if (!store_.pool_->pool_.empty()) {
                ctx_ = store_.pool_->pool_.back();
                store_.pool_->pool_.pop_back();
            }
        }
        if (!ctx_) {
            ctx_ = store_.createContext();
        }
    } else {
        // single-threaded
        if (store_.pool_->pool_.empty()) {
            isc_throw(Unexpected, "No available MySQL store context?!");
        }
        ctx_ = store_.pool_->pool_.back();
    }
}

MySqlStore::MySqlStoreContextAlloc::~MySqlStoreContextAlloc() {
    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        lock_guard<mutex> lock(store_.pool_->mutex_);
        store_.pool_->pool_.push_back(ctx_);
        if (ctx_->conn_.isUnusable()) {
            store_.unusable_ = true;
        }
    } else if (ctx_->conn_.isUnusable()) {
        store_.unusable_ = true;
    }
}

// MySqlStore

MySqlStore::MySqlStore(const DatabaseConnection::ParameterMap& parameters)
    : LegalLogMgr(parameters), timer_name_(""), unusable_(false) {

    // Create unique timer name per instance.
    timer_name_ = "MySqlLegalStore[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";
}

void MySqlStore::open() {
    LegalLogDbLogger pushed(mysql_legal_log_db_logger);

    // Test schema version first.
    std::pair<uint32_t, uint32_t> code_version(MYSQL_SCHEMA_VERSION_MAJOR,
                                               MYSQL_SCHEMA_VERSION_MINOR);

    string timer_name;
    bool retry = false;
    if (LegalLogMgr::getParameters().count("retry-on-startup")) {
        if (LegalLogMgr::getParameters().at("retry-on-startup") == "true") {
            retry = true;
        }
    }
    if (retry) {
        timer_name = timer_name_;
    }

    std::pair<uint32_t, uint32_t> db_version = getVersion(timer_name);
    if (code_version != db_version) {
        isc_throw(DbOpenError,
                  "MySQL schema version mismatch: need version: "
                  << code_version.first << "." << code_version.second
                  << " found version:  " << db_version.first << "."
                  << db_version.second);
    }

    // Create an initial context.
    pool_.reset(new MySqlStoreContextPool());
    pool_->pool_.push_back(createContext());
}

// Create context.

MySqlStoreContextPtr
MySqlStore::createContext() const {
    MySqlStoreContextPtr ctx(new MySqlStoreContext(getParameters(),
        IOServiceAccessorPtr(new IOServiceAccessor(&DatabaseConnection::getIOService)),
        &MySqlStore::dbReconnect));

    // Open the database.
    ctx->conn_.openDatabase();

    // Check if we have TLS when we required it.
    if (ctx->conn_.getTls()) {
        std::string cipher = ctx->conn_.getTlsCipher();
        if (cipher.empty()) {
            LOG_ERROR(mysql_fb_logger, LEGAL_LOG_MYSQL_NO_TLS);
        } else {
            LOG_DEBUG(mysql_fb_logger, DB_DBG_TRACE_DETAIL,
                      LEGAL_LOG_MYSQL_TLS_CIPHER)
                .arg(cipher);
        }
    }

    // Prepare all statements likely to be used.
    ctx->conn_.prepareStatements(tagged_statements.begin(),
                                 tagged_statements.end());

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    ctx->exchange_.reset(new MySqlLegLExchange());

    // Create ReconnectCtl for this connection.
    ctx->conn_.makeReconnectCtl(timer_name_, NetworkState::DB_CONNECTION + 31);

    return (ctx);
}

MySqlStore::~MySqlStore() {
    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the mysql_ member variable.
}

void
MySqlStore::close() {
}

void
MySqlStore::writeln(const string& text, const std::string& addr) {
    if (text.empty()) {
        return;
    }

    LOG_DEBUG(mysql_fb_logger, DB_DBG_TRACE_DETAIL,
              LEGAL_LOG_MYSQL_INSERT_LOG).arg(text);

    LegalLogDbLogger pushed(mysql_legal_log_db_logger);

    // Get a context
    MySqlStoreContextAlloc get_context(*this);
    MySqlStoreContextPtr ctx = get_context.ctx_;

    // Create the MYSQL_BIND array for the log entry
    vector<MYSQL_BIND> bind = ctx->exchange_->createBindForSend(addr, text);

    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.getStatement(INSERT_LOG),
                                       &bind[0]);
    checkError(ctx, status, INSERT_LOG, "unable to bind parameters");

    // Execute the statement
    status = MysqlExecuteStatement(ctx->conn_.getStatement(INSERT_LOG));
    if (status != 0) {
        checkError(ctx, status, INSERT_LOG, "unable to execute");
    }

    // Insert succeeded
}

pair<uint32_t, uint32_t>
MySqlStore::getVersion(const std::string& timer_name) const {
    LOG_DEBUG(mysql_fb_logger, DB_DBG_TRACE_DETAIL,
              LEGAL_LOG_MYSQL_GET_VERSION);

    LegalLogDbLogger pushed(mysql_legal_log_db_logger);

    IOServiceAccessorPtr ac(new IOServiceAccessor(&DatabaseConnection::getIOService));
    DbCallback cb(&MySqlStore::dbReconnect);

    return (MySqlConnection::getVersion(getParameters(), ac, cb, timer_name, NetworkState::DB_CONNECTION + 31));
}

std::string
MySqlStore::getDBVersion() {
    std::stringstream tmp;
    tmp << "MySQL backend " << MYSQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << MYSQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << mysql_get_client_info();
    return (tmp.str());
}

void
MySqlStore::checkError(MySqlStoreContextPtr& ctx,
                       int status,
                       StatementIndex index,
                       const char* what) const {
    ctx->conn_.checkError(status, index, what);
}

bool
MySqlStore::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
    MultiThreadingCriticalSection cs;

    // Invoke application layer connection lost callback.
    if (!DatabaseConnection::invokeDbLostCallback(db_reconnect_ctl)) {
        return (false);
    }

    bool reopened = false;

    const std::string timer_name = db_reconnect_ctl->timerName();
    bool check = db_reconnect_ctl->checkRetries();

    // At least one connection was lost.
    try {
        auto pool = LegalLogMgrFactory::getPool();
        for (auto backend : pool) {
            if (LegalLogMgrFactory::delBackend(backend.first, true)) {
                LegalLogMgrFactory::addBackend(backend.second.first, backend.first);
            }
        }
        reopened = true;
    } catch (const std::exception& ex) {
        LOG_ERROR(mysql_fb_logger, LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED)
                .arg(ex.what());
    }

    if (reopened) {
        // Cancel the timer.
        if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->unregisterTimer(timer_name);
        }

        // Invoke application layer connection recovered callback.
        if (!DatabaseConnection::invokeDbRecoveredCallback(db_reconnect_ctl)) {
            return (false);
        }
    } else {
        if (!check) {
            // We're out of retries, log it and initiate shutdown.
            LOG_ERROR(mysql_fb_logger, LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED)
                    .arg(db_reconnect_ctl->maxRetries());

            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection failed callback.
            DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);
            return (false);
        }

        LOG_INFO(mysql_fb_logger, LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        // Start the timer.
        if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->registerTimer(timer_name,
                std::bind(&MySqlStore::dbReconnect, db_reconnect_ctl),
                          db_reconnect_ctl->retryInterval(),
                          asiolink::IntervalTimer::ONE_SHOT);
        }
        TimerMgr::instance()->setup(timer_name);
    }

    return (true);
}

bool
MySqlStore::isUnusable() {
    return (unusable_);
}

LegalLogMgrPtr
MySqlStore::factory(const isc::db::DatabaseConnection::ParameterMap& parameters) {
    LOG_INFO(mysql_fb_logger, MYSQL_FB_DB)
        .arg(isc::db::DatabaseConnection::redactedAccessString(parameters));
    return (LegalLogMgrPtr(new MySqlStore(parameters)));
}

} // end of isc::dhcp namespace
} // end of isc namespace
