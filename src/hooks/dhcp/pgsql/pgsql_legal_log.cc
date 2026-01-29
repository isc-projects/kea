// Copyright (C) 2018-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <pgsql_fb_log.h>
#include <pgsql_legal_log.h>
#include <dhcpsrv/legal_log_mgr_factory.h>
#include <dhcpsrv/legal_log_db_log.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/multi_threading_mgr.h>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Catalog of all the SQL statements currently supported.  Note
/// that the order columns appear in statement body must match the order they
/// that the occur in the table.  This does not apply to the where clause.
PgSqlTaggedStatement tagged_statements[] = {
    // INSERT_LOG
    { 2, { OID_VARCHAR, OID_TEXT },
      "insert_log",
      "INSERT INTO logs(address, log) VALUES ($1, $2)"},

    // End of list sentinel
    { 0,  { 0 }, NULL, NULL}
};

};

namespace isc {
namespace dhcp {

/// @brief Supports exchanging log entries with PostgreSQL.
class PgSqlLegLExchange : public PgSqlExchange {
private:

    /// @brief Column numbers for each column in the logs table.
    /// These are used for both retrieving data and for looking up
    /// column labels for logging.  Note that their numeric order
    /// MUST match that of the column order in the logs table.
    static const size_t ADDRES_COL = 0;
    static const size_t LOG_COL = 1;
    /// @brief Number of columns in the table holding log entries.
    static const size_t LOG_COLUMNS = 2;

public:
    /// @brief Constructor
    PgSqlLegLExchange() : address_(""), log_("") {

        static_assert(0 < LOG_COLUMNS, "0 < LOG_COLUMNS");

        // Set the column names (for error messages)
        columns_.push_back("log");
    }

    /// @brief Destructor
    ~PgSqlLegLExchange() = default;

    /// @brief Creates the bind array for sending log text to the database.
    ///
    /// Converts each member into the appropriate form and adds it
    /// to the bind array.  Note that the array additions must occur in the
    /// order the columns are specified in the SQL statement.  By convention
    /// all columns in the table are explicitly listed in the SQL statement(s)
    /// in the same order as they occur in the table.
    ///
    /// @param address address or prefix of the log entry
    /// @param log log entry that is to be written to the database
    /// @param[out] bind_array array to populate with the values
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    void createBindForSend(const string& address, const string& log,
                           PsqlBindArray& bind_array) {
        if (log.empty()) {
            isc_throw(BadValue, "createBindForSend:: log entry is NULL");
        }

        // Store arguments to ensure they remain valid.
        address_ = address;
        log_ = log;

        try {
            bind_array.add(address_);
            bind_array.add(log_);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from log: '"
                      << log_ << "', reason: " << ex.what());
        }
    }

private:
    /// @brief Members used for binding and conversion
    //@{
    string address_;
    string log_;
    //@}
};

// PgSqlStoreContext Constructor

PgSqlStoreContext::PgSqlStoreContext(const DatabaseConnection::ParameterMap& parameters,
                                     IOServiceAccessorPtr io_service_accessor,
                                     db::DbCallback db_reconnect_callback)
    : conn_(parameters, io_service_accessor, db_reconnect_callback) {
}

// PgSqlStoreContextAlloc Constructor and Destructor

PgSqlStore::PgSqlStoreContextAlloc::PgSqlStoreContextAlloc(PgSqlStore& store)
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
            isc_throw(Unexpected, "No available PostgreSQL store context?!");
        }
        ctx_ = store_.pool_->pool_.back();
    }
}

PgSqlStore::PgSqlStoreContextAlloc::~PgSqlStoreContextAlloc() {
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

// PgSqlStore

PgSqlStore::PgSqlStore(const DatabaseConnection::ParameterMap& parameters)
    : LegalLogMgr(parameters), timer_name_(""), unusable_(false) {

    // Store connection parameters.
    LegalLogMgr::setParameters(parameters);

    // Create unique timer name per instance.
    timer_name_ = "PgSqlLegalStore[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";
}

void PgSqlStore::open() {
    LegalLogDbLogger pushed(pgsql_legal_log_db_logger);

    // Test schema version first.
    pair<uint32_t, uint32_t> code_version(PGSQL_SCHEMA_VERSION_MAJOR,
                                          PGSQL_SCHEMA_VERSION_MINOR);

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

    pair<uint32_t, uint32_t> db_version = getVersion(timer_name);
    if (code_version != db_version) {
        isc_throw(DbOpenError,
                  "PostgreSQL schema version mismatch: need version: "
                  << code_version.first << "." << code_version.second
                  << " found version:  " << db_version.first << "."
                  << db_version.second);
    }

    // Create an initial context.
    pool_.reset(new PgSqlStoreContextPool());
    pool_->pool_.push_back(createContext());
}

// Create context.

PgSqlStoreContextPtr
PgSqlStore::createContext() const {
    PgSqlStoreContextPtr ctx(new PgSqlStoreContext(getParameters(),
        IOServiceAccessorPtr(new IOServiceAccessor(&DatabaseConnection::getIOService)),
        &PgSqlStore::dbReconnect));

    // Open the database.
    ctx->conn_.openDatabase();

    size_t i = 0;
    for (; tagged_statements[i].text != NULL; ++i) {
        ctx->conn_.prepareStatement(tagged_statements[i]);
    }

    // Just in case somebody fubared things
    if (i != NUM_STATEMENTS) {
        isc_throw(DbOpenError, "Number of statements prepared: " << i
                  << " does not match expected count:" << NUM_STATEMENTS);
    }

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    ctx->exchange_.reset(new PgSqlLegLExchange());

    // Create ReconnectCtl for this connection.
    ctx->conn_.makeReconnectCtl(timer_name_, NetworkState::DB_CONNECTION + 32);

    return (ctx);
}

PgSqlStore::~PgSqlStore() {
}

void PgSqlStore::close() {
}

void
PgSqlStore::writeln(const string& text, const std::string& addr) {
    if (text.empty()) {
        return;
    }

    LOG_DEBUG(pgsql_fb_logger, DB_DBG_TRACE_DETAIL,
              LEGAL_LOG_PGSQL_INSERT_LOG).arg(text);

    LegalLogDbLogger pushed(pgsql_legal_log_db_logger);

    // Get a context
    PgSqlStoreContextAlloc get_context(*this);
    PgSqlStoreContextPtr ctx = get_context.ctx_;

    PsqlBindArray bind_array;
    ctx->exchange_->createBindForSend(addr, text, bind_array);

    PgSqlResult r(PQexecPrepared(ctx->conn_,
                                 tagged_statements[INSERT_LOG].name,
                                 tagged_statements[INSERT_LOG].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        ctx->conn_.checkStatementError(r, tagged_statements[INSERT_LOG]);
    }
}

pair<uint32_t, uint32_t>
PgSqlStore::getVersion(const std::string& timer_name) const {
    LOG_DEBUG(pgsql_fb_logger, DB_DBG_TRACE_DETAIL,
              LEGAL_LOG_PGSQL_GET_VERSION);

    LegalLogDbLogger pushed(pgsql_legal_log_db_logger);

    IOServiceAccessorPtr ac(new IOServiceAccessor(&DatabaseConnection::getIOService));
    DbCallback cb(&PgSqlStore::dbReconnect);

    return (PgSqlConnection::getVersion(getParameters(), ac, cb, timer_name, NetworkState::DB_CONNECTION + 32));
}

std::string
PgSqlStore::getDBVersion() {
    std::stringstream tmp;
    tmp << "PostgreSQL backend " << PGSQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << PGSQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << PQlibVersion();
    return (tmp.str());
}

bool
PgSqlStore::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
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
        LOG_ERROR(pgsql_fb_logger, LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED)
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
            LOG_ERROR(pgsql_fb_logger, LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED)
                    .arg(db_reconnect_ctl->maxRetries());

            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection failed callback.
            DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);
            return (false);
        }

        LOG_INFO(pgsql_fb_logger, LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        // Start the timer.
        if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->registerTimer(timer_name,
                std::bind(&PgSqlStore::dbReconnect, db_reconnect_ctl),
                          db_reconnect_ctl->retryInterval(),
                          asiolink::IntervalTimer::ONE_SHOT);
        }
        TimerMgr::instance()->setup(timer_name);
    }

    return (true);
}

bool
PgSqlStore::isUnusable() {
    return (unusable_);
}

LegalLogMgrPtr
PgSqlStore::factory(const isc::db::DatabaseConnection::ParameterMap& parameters) {
    LOG_INFO(pgsql_fb_logger, PGSQL_FB_DB)
        .arg(isc::db::DatabaseConnection::redactedAccessString(parameters));
    return (LegalLogMgrPtr(new PgSqlStore(parameters)));
}

} // end of isc::dhcp namespace
} // end of isc namespace
