// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/pgsql_connection.h>

#include <boost/static_assert.hpp>

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <time.h>

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

const char PgSqlConnection::DUPLICATE_KEY[] = ERRCODE_UNIQUE_VIOLATION;

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
PgSqlConnection::compareError(PGresult*& r, const char* error_state) {
    const char* sqlstate = PQresultErrorField(r, PG_DIAG_SQLSTATE);
    // PostgreSQL garuantees it will always be 5 characters long
    return ((sqlstate != NULL) &&
            (memcmp(sqlstate, error_state, PGSQL_STATECODE_LEN) == 0));
}

void
PgSqlConnection::checkStatementError(PGresult*& r, 
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
