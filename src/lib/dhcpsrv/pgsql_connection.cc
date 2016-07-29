// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/pgsql_connection.h>

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
// supply their own.  We'll define it as an initlizer_list:
#define MAKE_SQLSTATE(ch1,ch2,ch3,ch4,ch5) {ch1,ch2,ch3,ch4,ch5}
// So we can use it like this: const char some_error[] = ERRCODE_xxxx;
#define PGSQL_STATECODE_LEN 5
#include <utils/errcodes.h>

using namespace std;

namespace isc {
namespace dhcp {

// Default connection timeout
const int PGSQL_DEFAULT_CONNECTION_TIMEOUT = 5; // seconds

const char PgSqlConnection::DUPLICATE_KEY[] = ERRCODE_UNIQUE_VIOLATION;

PgSqlResult::PgSqlResult(PGresult *result) 
    : result_(result), rows_(0), cols_(0) {
    if (!result) {
        isc_throw (BadValue, "PgSqlResult result pointer cannot be null");
    }

    rows_ = PQntuples(result);
    cols_ = PQnfields(result);
}

void 
PgSqlResult::rowCheck(int row) const {
    if (row < 0 || row >= rows_) {
        isc_throw (DbOperationError, "row: " << row 
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
        PgSqlResult r(PQexec(conn_, "DEALLOCATE all"));
        if(PQresultStatus(r) != PGRES_COMMAND_OK) {
            // Highly unlikely but we'll log it and go on.
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_DEALLOC_ERROR)
                      .arg(PQerrorMessage(conn_));
        }
    }
}

void
PgSqlConnection::prepareStatement(const PgSqlTaggedStatement& statement) {
    // Prepare all statements queries with all known fields datatype
    PgSqlResult r(PQprepare(conn_, statement.name, statement.text,
                            statement.nbparams, statement.types));
    if(PQresultStatus(r) != PGRES_COMMAND_OK) {
        isc_throw(DbOperationError, "unable to prepare PostgreSQL statement: "
                  << statement.text << ", reason: " << PQerrorMessage(conn_));
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
        // database, a zero timeout might signify someting like "wait
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
    // PostgreSQL garuantees it will always be 5 characters long
    return ((sqlstate != NULL) &&
            (memcmp(sqlstate, error_state, PGSQL_STATECODE_LEN) == 0));
}

void
PgSqlConnection::checkStatementError(const PgSqlResult& r,
                                     PgSqlTaggedStatement& statement) const {
    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK && s != PGRES_TUPLES_OK) {
        // We're testing the first two chars of SQLSTATE, as this is the
        // error class. Note, there is a severity field, but it can be
        // misleadingly returned as fatal.
        const char* sqlstate = PQresultErrorField(r, PG_DIAG_SQLSTATE);
        if ((sqlstate != NULL) &&
            ((memcmp(sqlstate, "08", 2) == 0) ||  // Connection Exception
             (memcmp(sqlstate, "53", 2) == 0) ||  // Insufficient resources
             (memcmp(sqlstate, "54", 2) == 0) ||  // Program Limit exceeded
             (memcmp(sqlstate, "57", 2) == 0) ||  // Operator intervention
             (memcmp(sqlstate, "58", 2) == 0))) { // System error
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_FATAL_ERROR)
                         .arg(statement.name)
                         .arg(PQerrorMessage(conn_))
                         .arg(sqlstate);
            exit (-1);
        }

        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "Statement exec failed:" << " for: "
                  << statement.name << ", reason: "
                  << error_message);
    }
}

void
PgSqlConnection::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_START_TRANSACTION);
    PgSqlResult r(PQexec(conn_, "START TRANSACTION"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "unable to start transaction"
                  << error_message);
    }
}

void
PgSqlConnection::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_COMMIT);
    PgSqlResult r(PQexec(conn_, "COMMIT"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "commit failed: " << error_message);
    }
}

void
PgSqlConnection::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_ROLLBACK);
    PgSqlResult r(PQexec(conn_, "ROLLBACK"));
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        isc_throw(DbOperationError, "rollback failed: " << error_message);
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
