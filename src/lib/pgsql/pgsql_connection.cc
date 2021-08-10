// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/db_log.h>
#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>

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
    conn.openDatabase();

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
                  << statement.text << ", reason: " << PQerrorMessage(conn_));
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

void
PgSqlConnection::openDatabase() {
    string dbconnparameters;
    string shost = "localhost";
    try {
        shost = getParameter("host");
    } catch(...) {
        // No host. Fine, we'll use "localhost"
    }

    dbconnparameters += "host = '" + shost + "'" ;

    string sport;
    try {
        sport = getParameter("port");
    } catch (...) {
        // No port parameter, we are going to use the default port.
        sport = "";
    }

    if (sport.size() > 0) {
        unsigned int port = 0;

        // Port was given, so try to convert it to an integer.
        try {
            port = boost::lexical_cast<unsigned int>(sport);
        } catch (...) {
            // Port given but could not be converted to an unsigned int.
            // Just fall back to the default value.
            port = 0;
        }

        // The port is only valid when it is in the 0..65535 range.
        // Again fall back to the default when the given value is invalid.
        if (port > numeric_limits<uint16_t>::max()) {
            port = 0;
        }

        // Add it to connection parameters when not default.
        if (port > 0) {
            std::ostringstream oss;
            oss << port;
            dbconnparameters += " port = " + oss.str();
        }
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
    string stimeout;
    try {
        stimeout = getParameter("connect-timeout");
    } catch (...) {
        // No timeout parameter, we are going to use the default timeout.
        stimeout = "";
    }

    if (stimeout.size() > 0) {
        // Timeout was given, so try to convert it to an integer.

        try {
            connect_timeout = boost::lexical_cast<unsigned int>(stimeout);
        } catch (...) {
            // Timeout given but could not be converted to an unsigned int. Set
            // the connection timeout to an invalid value to trigger throwing
            // of an exception.
            connect_timeout = 0;
        }

        // The timeout is only valid if greater than zero, as depending on the
        // database, a zero timeout might signify something like "wait
        // indefinitely".
        //
        // The check below also rejects a value greater than the maximum
        // integer value.  The lexical_cast operation used to obtain a numeric
        // value from a string can get confused if trying to convert a negative
        // integer to an unsigned int: instead of throwing an exception, it may
        // produce a large positive value.
        if ((connect_timeout == 0) ||
            (connect_timeout > numeric_limits<int>::max())) {
            isc_throw(DbInvalidTimeout, "database connection timeout (" <<
                      stimeout << ") must be an integer greater than 0");
        }
    }

    std::ostringstream oss;
    oss << connect_timeout;
    dbconnparameters += " connect_timeout = " + oss.str();

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
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, PGSQL_START_TRANSACTION);
    checkUnusable();
    PgSqlResult r(PQexec(conn_, "START TRANSACTION"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "unable to start transaction"
                  << error_message);
    }
}

void
PgSqlConnection::commit() {
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
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, PGSQL_ROLLBACK);
    checkUnusable();
    PgSqlResult r(PQexec(conn_, "ROLLBACK"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "rollback failed: " << error_message);
    }
}

} // end of isc::db namespace
} // end of isc namespace
