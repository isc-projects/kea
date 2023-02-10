// Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/db_exceptions.h>
#include <database/db_log.h>
#include <pgsql/pgsql_connection.h>

// PostgreSQL errors should be tested based on the SQL state code.  Each state
// code is 5 decimal, ASCII, digits, the first two define the category of
// error, the last three are the specific error.  PostgreSQL makes the state
// code as a char[5].  Macros for each code are defined in PostgreSQL's
// server/utils/errcodes.h, although they require a second macro,
// MAKE_SQLSTATE for completion.  For example, duplicate key error as:
//
// #define ERRCODE_UNIQUE_VIOLATION MAKE_SQLSTATE('2','3','5','0','5')
//
// PostgreSQL deliberately omits the MAKE_SQLSTATE macro so callers can/must
// supply their own.  We'll define it as an initialization list:
#define MAKE_SQLSTATE(ch1,ch2,ch3,ch4,ch5) {ch1,ch2,ch3,ch4,ch5}
// So we can use it like this: const char some_error[] = ERRCODE_xxxx;
#define PGSQL_STATECODE_LEN 5
#include <utils/errcodes.h>

#include <sstream>

using namespace std;

namespace isc {
namespace db {

// Default connection timeout

/// @todo: migrate this default timeout to src/bin/dhcpX/simple_parserX.cc
const int PGSQL_DEFAULT_CONNECTION_TIMEOUT = 5; // seconds

const char PgSqlConnection::DUPLICATE_KEY[] = ERRCODE_UNIQUE_VIOLATION;
const char PgSqlConnection::NULL_KEY[] = ERRCODE_NOT_NULL_VIOLATION;

bool PgSqlConnection::warned_about_tls = false;

PgSqlResult::PgSqlResult(PGresult *result)
    : result_(result), rows_(0), cols_(0) {
    if (!result) {
        // Certain failures, like a loss of connectivity, can return a
        // null PGresult and we still need to be able to create a PgSqlResult.
        // We'll set row and col counts to -1 to prevent anyone going off the
        // rails.
        rows_ = -1;
        cols_ = -1;
    } else {
        rows_ = PQntuples(result);
        cols_ = PQnfields(result);
    }
}

void
PgSqlResult::rowCheck(int row) const {
    if (row < 0 || row >= rows_) {
        isc_throw (db::DbOperationError, "row: " << row
                   << ", out of range: 0.." << rows_);
    }
}

PgSqlResult::~PgSqlResult() {
    if (result_)  {
        PQclear(result_);
    }
}

void
PgSqlResult::colCheck(int col) const {
    if (col < 0 || col >= cols_) {
        isc_throw (DbOperationError, "col: " << col
                   << ", out of range: 0.." << cols_);
    }
}

void
PgSqlResult::rowColCheck(int row, int col) const {
    rowCheck(row);
    colCheck(col);
}

std::string
PgSqlResult::getColumnLabel(const int col) const {
    const char* label = NULL;
    try {
        colCheck(col);
        label = PQfname(result_, col);
    } catch (...) {
        std::ostringstream os;
        os << "Unknown column:" << col;
        return (os.str());
    }

    return (label);
}

PgSqlTransaction::PgSqlTransaction(PgSqlConnection& conn)
    : conn_(conn), committed_(false) {
    conn_.startTransaction();
}

PgSqlTransaction::~PgSqlTransaction() {
    // If commit() wasn't explicitly called, rollback.
    if (!committed_) {
        conn_.rollback();
    }
}

void
PgSqlTransaction::commit() {
    conn_.commit();
    committed_ = true;
}

PgSqlConnection::~PgSqlConnection() {
    if (conn_) {
        // Deallocate the prepared queries.
        if (PQstatus(conn_) == CONNECTION_OK) {
            PgSqlResult r(PQexec(conn_, "DEALLOCATE all"));
            if (PQresultStatus(r) != PGRES_COMMAND_OK) {
                // Highly unlikely but we'll log it and go on.
                DB_LOG_ERROR(PGSQL_DEALLOC_ERROR)
                    .arg(PQerrorMessage(conn_));
            }
        }
    }
}

std::pair<uint32_t, uint32_t>
PgSqlConnection::getVersion(const ParameterMap& parameters) {
    // Get a connection.
    PgSqlConnection conn(parameters);

    // Open the database.
    conn.openDatabaseInternal(false);

    const char* version_sql =  "SELECT version, minor FROM schema_version;";
    PgSqlResult r(PQexec(conn.conn_, version_sql));
    if (PQresultStatus(r) != PGRES_TUPLES_OK) {
        isc_throw(DbOperationError, "unable to execute PostgreSQL statement <"
                  << version_sql << ", reason: " << PQerrorMessage(conn.conn_));
    }

    uint32_t version;
    PgSqlExchange::getColumnValue(r, 0, 0, version);

    uint32_t minor;
    PgSqlExchange::getColumnValue(r, 0, 1, minor);

    return (make_pair(version, minor));
}

void
PgSqlConnection::prepareStatement(const PgSqlTaggedStatement& statement) {
    // Prepare all statements queries with all known fields datatype
    PgSqlResult r(PQprepare(conn_, statement.name, statement.text,
                            statement.nbparams, statement.types));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        isc_throw(DbOperationError, "unable to prepare PostgreSQL statement: "
                  << " name: " << statement.name
                  << ", reason: " << PQerrorMessage(conn_)
                  << ", text: " << statement.text);
    }
}

void
PgSqlConnection::prepareStatements(const PgSqlTaggedStatement* start_statement,
                                   const PgSqlTaggedStatement* end_statement) {
    // Created the PostgreSQL prepared statements.
    for (const PgSqlTaggedStatement* tagged_statement = start_statement;
         tagged_statement != end_statement; ++tagged_statement) {
        prepareStatement(*tagged_statement);
    }
}

std::string
PgSqlConnection::getConnParameters() {
    return (getConnParametersInternal(false));
}

std::string
PgSqlConnection::getConnParametersInternal(bool logging) {
    string dbconnparameters;
    string shost = "localhost";
    try {
        shost = getParameter("host");
    } catch(...) {
        // No host. Fine, we'll use "localhost"
    }

    dbconnparameters += "host = '" + shost + "'" ;

    unsigned int port = 0;
    try {
        setIntParameterValue("port", 0, numeric_limits<uint16_t>::max(), port);

    } catch (const std::exception& ex) {
        isc_throw(DbInvalidPort, ex.what());
    }

    // Add port to connection parameters when not default.
    if (port > 0) {
        std::ostringstream oss;
        oss << port;
        dbconnparameters += " port = " + oss.str();
    }

    string suser;
    try {
        suser = getParameter("user");
        dbconnparameters += " user = '" + suser + "'";
    } catch(...) {
        // No user. Fine, we'll use NULL
    }

    string spassword;
    try {
        spassword = getParameter("password");
        dbconnparameters += " password = '" + spassword + "'";
    } catch(...) {
        // No password. Fine, we'll use NULL
    }

    string sname;
    try {
        sname = getParameter("name");
        dbconnparameters += " dbname = '" + sname + "'";
    } catch(...) {
        // No database name.  Throw a "NoDatabaseName" exception
        isc_throw(NoDatabaseName, "must specify a name for the database");
    }

    unsigned int connect_timeout = PGSQL_DEFAULT_CONNECTION_TIMEOUT;
    unsigned int tcp_user_timeout = 0;
    try {
        // The timeout is only valid if greater than zero, as depending on the
        // database, a zero timeout might signify something like "wait
        // indefinitely".
        setIntParameterValue("connect-timeout", 1, numeric_limits<int>::max(), connect_timeout);
        // This timeout value can be 0, meaning that the database client will
        // follow a default behavior. Earlier Postgres versions didn't have
        // this parameter, so we allow 0 to skip setting them for these
        // earlier versions.
        setIntParameterValue("tcp-user-timeout", 0, numeric_limits<int>::max(), tcp_user_timeout);

    } catch (const std::exception& ex) {
        isc_throw(DbInvalidTimeout, ex.what());
    }

    // Append connection timeout.
    std::ostringstream oss;
    oss << " connect_timeout = " << connect_timeout;

    if (tcp_user_timeout > 0) {
// tcp_user_timeout parameter is a PostgreSQL 12+ feature.
#ifdef HAVE_PGSQL_TCP_USER_TIMEOUT
        oss << " tcp_user_timeout = " << tcp_user_timeout * 1000;
        static_cast<void>(logging);
#else
        if (logging) {
            DB_LOG_WARN(PGSQL_TCP_USER_TIMEOUT_UNSUPPORTED).arg();
        }
#endif
    }
    dbconnparameters += oss.str();

    return (dbconnparameters);
}

void
PgSqlConnection::openDatabase() {
    openDatabaseInternal(true);
}

void
PgSqlConnection::openDatabaseInternal(bool logging) {
    std::string dbconnparameters = getConnParametersInternal(logging);
    // Connect to Postgres, saving the low level connection pointer
    // in the holder object
    PGconn* new_conn = PQconnectdb(dbconnparameters.c_str());
    if (!new_conn) {
        isc_throw(DbOpenError, "could not allocate connection object");
    }

    if (PQstatus(new_conn) != CONNECTION_OK) {
        // If we have a connection object, we have to call finish
        // to release it, but grab the error message first.
        std::string error_message = PQerrorMessage(new_conn);
        PQfinish(new_conn);
        isc_throw(DbOpenError, error_message);
    }

    // We have a valid connection, so let's save it to our holder
    conn_.setConnection(new_conn);
}

bool
PgSqlConnection::compareError(const PgSqlResult& r, const char* error_state) {
    const char* sqlstate = PQresultErrorField(r, PG_DIAG_SQLSTATE);
    // PostgreSQL guarantees it will always be 5 characters long
    return ((sqlstate != NULL) &&
            (memcmp(sqlstate, error_state, PGSQL_STATECODE_LEN) == 0));
}

void
PgSqlConnection::checkStatementError(const PgSqlResult& r,
                                     PgSqlTaggedStatement& statement) {
    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK && s != PGRES_TUPLES_OK) {
        // We're testing the first two chars of SQLSTATE, as this is the
        // error class. Note, there is a severity field, but it can be
        // misleadingly returned as fatal. However, a loss of connectivity
        // can lead to a NULL sqlstate with a status of PGRES_FATAL_ERROR.
        const char* sqlstate = PQresultErrorField(r, PG_DIAG_SQLSTATE);
        if ((sqlstate == NULL) ||
            ((memcmp(sqlstate, "08", 2) == 0) ||  // Connection Exception
             (memcmp(sqlstate, "53", 2) == 0) ||  // Insufficient resources
             (memcmp(sqlstate, "54", 2) == 0) ||  // Program Limit exceeded
             (memcmp(sqlstate, "57", 2) == 0) ||  // Operator intervention
             (memcmp(sqlstate, "58", 2) == 0))) { // System error
            DB_LOG_ERROR(PGSQL_FATAL_ERROR)
                .arg(statement.name)
                .arg(PQerrorMessage(conn_))
                .arg(sqlstate ? sqlstate : "<sqlstate null>");

            // Mark this connection as no longer usable.
            markUnusable();

            // Start the connection recovery.
            startRecoverDbConnection();

            // We still need to throw so caller can error out of the current
            // processing.
            isc_throw(DbConnectionUnusable,
                      "fatal database error or connectivity lost");
        }

        // Failure: check for the special case of duplicate entry.
        if (compareError(r, PgSqlConnection::DUPLICATE_KEY)) {
            isc_throw(DuplicateEntry, "statement: " << statement.name
                      << ", reason: " << PQerrorMessage(conn_));
        }

        // Failure: check for the special case of null key violation.
        if (compareError(r, PgSqlConnection::NULL_KEY)) {
            isc_throw(NullKeyError, "statement: " << statement.name
                      << ", reason: " << PQerrorMessage(conn_));
        }

        // Apparently it wasn't fatal, so we throw with a helpful message.
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "Statement exec failed for: "
                  << statement.name << ", status: " << s
                  << "sqlstate:[ " << (sqlstate ? sqlstate : "<null>")
                  << " ], reason: " << error_message);
    }
}

void
PgSqlConnection::startTransaction() {
    // If it is nested transaction, do nothing.
    if (++transaction_ref_count_ > 1) {
        return;
    }

    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, PGSQL_START_TRANSACTION);
    checkUnusable();
    PgSqlResult r(PQexec(conn_, "START TRANSACTION"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "unable to start transaction"
                  << error_message);
    }
}

bool
PgSqlConnection::isTransactionStarted() const {
    return (transaction_ref_count_ > 0);
}

void
PgSqlConnection::commit() {
    if (transaction_ref_count_ <= 0) {
        isc_throw(Unexpected, "commit called for not started transaction - coding error");
    }

    // When committing nested transaction, do nothing.
    if (--transaction_ref_count_ > 0) {
        return;
    }

    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, PGSQL_COMMIT);
    checkUnusable();
    PgSqlResult r(PQexec(conn_, "COMMIT"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "commit failed: " << error_message);
    }
}

void
PgSqlConnection::rollback() {
    if (transaction_ref_count_ <= 0) {
        isc_throw(Unexpected, "rollback called for not started transaction - coding error");
    }

    // When rolling back nested transaction, do nothing.
    if (--transaction_ref_count_ > 0) {
        return;
    }

    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, PGSQL_ROLLBACK);
    checkUnusable();
    PgSqlResult r(PQexec(conn_, "ROLLBACK"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "rollback failed: " << error_message);
    }
}

void
PgSqlConnection::createSavepoint(const std::string& name) {
    if (transaction_ref_count_ <= 0) {
        isc_throw(InvalidOperation, "no transaction, cannot create savepoint: " << name);
    }

    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, PGSQL_CREATE_SAVEPOINT).arg(name);
    std::string sql("SAVEPOINT " + name);
    executeSQL(sql);
}

void
PgSqlConnection::rollbackToSavepoint(const std::string& name) {
    if (transaction_ref_count_ <= 0) {
        isc_throw(InvalidOperation, "no transaction, cannot rollback to savepoint: " << name);
    }

    std::string sql("ROLLBACK TO SAVEPOINT " + name);
    executeSQL(sql);
}

void
PgSqlConnection::executeSQL(const std::string& sql) {
    // Use a TaggedStatement so we can call checkStatementError and ensure
    // we detect connectivity issues properly.
    PgSqlTaggedStatement statement({0, {OID_NONE}, "run-statement", sql.c_str()});
    checkUnusable();
    PgSqlResult r(PQexec(conn_, statement.text));
    checkStatementError(r, statement);
}

PgSqlResultPtr
PgSqlConnection::executePreparedStatement(PgSqlTaggedStatement& statement,
                                          const PsqlBindArray& in_bindings) {
    checkUnusable();

    if (statement.nbparams != in_bindings.size()) {
        isc_throw (InvalidOperation, "executePreparedStatement:"
                   << " expected: " << statement.nbparams
                   << " parameters, given: " << in_bindings.size()
                   << ", statement: " << statement.name
                   << ", SQL: " << statement.text);
    }

    const char* const* values = 0;
    const int* lengths = 0;
    const int* formats = 0;
    if (statement.nbparams > 0) {
        values = static_cast<const char* const*>(&in_bindings.values_[0]);
        lengths = static_cast<const int *>(&in_bindings.lengths_[0]);
        formats = static_cast<const int *>(&in_bindings.formats_[0]);
    }

    PgSqlResultPtr result_set;
    result_set.reset(new PgSqlResult(PQexecPrepared(conn_, statement.name, statement.nbparams,
                                                    values, lengths, formats, 0)));

    checkStatementError(*result_set, statement);
    return (result_set);
}

void
PgSqlConnection::selectQuery(PgSqlTaggedStatement& statement,
                             const PsqlBindArray& in_bindings,
                             ConsumeResultRowFun process_result_row) {
    // Execute the prepared statement.
    PgSqlResultPtr result_set = executePreparedStatement(statement, in_bindings);

    // Iterate over the returned rows and invoke the row consumption
    // function on each one.
    int rows = result_set->getRows();
    for (int row = 0; row < rows; ++row) {
        try {
            process_result_row(*result_set, row);
        } catch (const std::exception& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      statement.text << ">");
        }
    }
}

void
PgSqlConnection::insertQuery(PgSqlTaggedStatement& statement,
                             const PsqlBindArray& in_bindings) {
    // Execute the prepared statement.
    PgSqlResultPtr result_set = executePreparedStatement(statement, in_bindings);
}

uint64_t
PgSqlConnection::updateDeleteQuery(PgSqlTaggedStatement& statement,
                                   const PsqlBindArray& in_bindings) {
    // Execute the prepared statement.
    PgSqlResultPtr result_set = executePreparedStatement(statement, in_bindings);

    return (boost::lexical_cast<int>(PQcmdTuples(*result_set)));
}

template<typename T>
void
PgSqlConnection::setIntParameterValue(const std::string& name, int64_t min, int64_t max, T& value) {
    string svalue;
    try {
        svalue = getParameter(name);
    } catch (...) {
        // Do nothing if the parameter is not present.
    }
    if (svalue.empty()) {
        return;
    }
    try {
        // Try to convert the value.
        auto parsed_value = boost::lexical_cast<T>(svalue);
        // Check if the value is within the specified range.
        if ((parsed_value < min) || (parsed_value > max)) {
            isc_throw(BadValue, "bad " << svalue << " value");
        }
        // Everything is fine. Return the parsed value.
        value = parsed_value;

    } catch (...) {
        // We may end up here when lexical_cast fails or when the
        // parsed value is not within the desired range. In both
        // cases let's throw the same general error.
        isc_throw(BadValue, name << " parameter (" <<
                  svalue << ") must be an integer between "
                  << min << " and " << max);
    }
}


} // end of isc::db namespace
} // end of isc namespace
