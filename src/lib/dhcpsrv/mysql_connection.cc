// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/mysql_connection.h>
#include <exceptions/exceptions.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdint.h>
#include <string>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace dhcp {

/// @brief Maximum size of database fields
///
/// The following constants define buffer sizes for variable length database
/// fields.  The values should be greater than or equal to the length set in
/// the schema definition.
///
/// The exception is the length of any VARCHAR fields: buffers for these should
/// be set greater than or equal to the length of the field plus 1: this allows
/// for the insertion of a trailing null whatever data is returned.

const my_bool MLM_FALSE = 0;                ///< False value
const my_bool MLM_TRUE = 1;                 ///< True value

///@}


// Open the database using the parameters passed to the constructor.

void
MySqlConnection::openDatabase() {

    // Set up the values of the parameters
    const char* host = "localhost";
    string shost;
    try {
        shost = getParameter("host");
        host = shost.c_str();
    } catch (...) {
        // No host.  Fine, we'll use "localhost"
    }

    const char* user = NULL;
    string suser;
    try {
        suser = getParameter("user");
        user = suser.c_str();
    } catch (...) {
        // No user.  Fine, we'll use NULL
    }

    const char* password = NULL;
    string spassword;
    try {
        spassword = getParameter("password");
        password = spassword.c_str();
    } catch (...) {
        // No password.  Fine, we'll use NULL
    }

    const char* name = NULL;
    string sname;
    try {
        sname = getParameter("name");
        name = sname.c_str();
    } catch (...) {
        // No database name.  Throw a "NoName" exception
        isc_throw(NoDatabaseName, "must specified a name for the database");
    }

    // Set options for the connection:
    //
    // Automatic reconnection: after a period of inactivity, the client will
    // disconnect from the database.  This option causes it to automatically
    // reconnect when another operation is about to be done.
    my_bool auto_reconnect = MLM_TRUE;
    int result = mysql_options(mysql_, MYSQL_OPT_RECONNECT, &auto_reconnect);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set auto-reconnect option: " <<
                  mysql_error(mysql_));
    }

    // Set SQL mode options for the connection:  SQL mode governs how what
    // constitutes insertable data for a given column, and how to handle
    // invalid data.  We want to ensure we get the strictest behavior and
    // to reject invalid data with an error.
    const char *sql_mode = "SET SESSION sql_mode ='STRICT_ALL_TABLES'";
    result = mysql_options(mysql_, MYSQL_INIT_COMMAND, sql_mode);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set SQL mode options: " <<
                  mysql_error(mysql_));
    }

    // Open the database.
    //
    // The option CLIENT_FOUND_ROWS is specified so that in an UPDATE,
    // the affected rows are the number of rows found that match the
    // WHERE clause of the SQL statement, not the rows changed.  The reason
    // here is that MySQL apparently does not update a row if data has not
    // changed and so the "affected rows" (retrievable from MySQL) is zero.
    // This makes it hard to distinguish whether the UPDATE changed no rows
    // because no row matching the WHERE clause was found, or because a
    // row was found but no data was altered.
    MYSQL* status = mysql_real_connect(mysql_, host, user, password, name,
                                       0, NULL, CLIENT_FOUND_ROWS);
    if (status != mysql_) {
        isc_throw(DbOpenError, mysql_error(mysql_));
    }
}


// Prepared statement setup.  The textual form of an SQL statement is stored
// in a vector of strings (text_statements_) and is used in the output of
// error messages.  The SQL statement is also compiled into a "prepared
// statement" (stored in statements_), which avoids the overhead of compilation
// during use.  As prepared statements have resources allocated to them, the
// class destructor explicitly destroys them.

void
MySqlConnection::prepareStatement(uint32_t index, const char* text) {
    // Validate that there is space for the statement in the statements array
    // and that nothing has been placed there before.
    if ((index >= statements_.size()) || (statements_[index] != NULL)) {
        isc_throw(InvalidParameter, "invalid prepared statement index (" <<
                  static_cast<int>(index) << ") or indexed prepared " <<
                  "statement is not null");
    }

    // All OK, so prepare the statement
    text_statements_[index] = std::string(text);
    statements_[index] = mysql_stmt_init(mysql_);
    if (statements_[index] == NULL) {
        isc_throw(DbOperationError, "unable to allocate MySQL prepared "
                  "statement structure, reason: " << mysql_error(mysql_));
    }

    int status = mysql_stmt_prepare(statements_[index], text, strlen(text));
    if (status != 0) {
        isc_throw(DbOperationError, "unable to prepare MySQL statement <" <<
                  text << ">, reason: " << mysql_error(mysql_));
    }
}

void
MySqlConnection::prepareStatements(const TaggedStatement tagged_statements[],
                                   size_t num_statements) {
    // Allocate space for all statements
    statements_.clear();
    statements_.resize(num_statements, NULL);

    text_statements_.clear();
    text_statements_.resize(num_statements, std::string(""));

    // Created the MySQL prepared statements for each DML statement.
    for (int i = 0; tagged_statements[i].text != NULL; ++i) {
        prepareStatement(tagged_statements[i].index,
                         tagged_statements[i].text);
    }
}

/// @brief Destructor
MySqlConnection::~MySqlConnection() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them? We're destroying this object and are not really concerned
    // with errors on a database connection that is about to go away.)
    for (int i = 0; i < statements_.size(); ++i) {
        if (statements_[i] != NULL) {
            (void) mysql_stmt_close(statements_[i]);
            statements_[i] = NULL;
        }
    }
    statements_.clear();
    text_statements_.clear();
}

// Time conversion methods.
//
// Note that the MySQL TIMESTAMP data type (used for "expire") converts data
// from the current timezone to UTC for storage, and from UTC to the current
// timezone for retrieval.
//
// This causes no problems providing that:
// a) cltt is given in local time
// b) We let the system take care of timezone conversion when converting
//    from a time read from the database into a local time.
void
MySqlConnection::convertToDatabaseTime(const time_t input_time,
                                       MYSQL_TIME& output_time) {

    // Convert to broken-out time
    struct tm time_tm;
    (void) localtime_r(&input_time, &time_tm);

    // Place in output expire structure.
    output_time.year = time_tm.tm_year + 1900;
    output_time.month = time_tm.tm_mon + 1;     // Note different base
    output_time.day = time_tm.tm_mday;
    output_time.hour = time_tm.tm_hour;
    output_time.minute = time_tm.tm_min;
    output_time.second = time_tm.tm_sec;
    output_time.second_part = 0;                // No fractional seconds
    output_time.neg = my_bool(0);               // Not negative
}

void
MySqlConnection::convertToDatabaseTime(const time_t cltt,
                                     const uint32_t valid_lifetime,
                                     MYSQL_TIME& expire) {

    // Calculate expiry time. Store it in the 64-bit value so as we can detect
    // overflows.
    int64_t expire_time_64 = static_cast<int64_t>(cltt) +
        static_cast<int64_t>(valid_lifetime);

    // Even on 64-bit systems MySQL doesn't seem to accept the timestamps
    // beyond the max value of int32_t.
    if (expire_time_64 > DatabaseConnection::MAX_DB_TIME) {
        isc_throw(BadValue, "Time value is too large: " << expire_time_64);
    }

    const time_t expire_time = static_cast<const time_t>(expire_time_64);

    // Convert to broken-out time
    struct tm expire_tm;
    (void) localtime_r(&expire_time, &expire_tm);

    // Place in output expire structure.
    expire.year = expire_tm.tm_year + 1900;
    expire.month = expire_tm.tm_mon + 1;     // Note different base
    expire.day = expire_tm.tm_mday;
    expire.hour = expire_tm.tm_hour;
    expire.minute = expire_tm.tm_min;
    expire.second = expire_tm.tm_sec;
    expire.second_part = 0;                  // No fractional seconds
    expire.neg = my_bool(0);                 // Not negative
}

void
MySqlConnection::convertFromDatabaseTime(const MYSQL_TIME& expire,
                                       uint32_t valid_lifetime, time_t& cltt) {

    // Copy across fields from MYSQL_TIME structure.
    struct tm expire_tm;
    memset(&expire_tm, 0, sizeof(expire_tm));

    expire_tm.tm_year = expire.year - 1900;
    expire_tm.tm_mon = expire.month - 1;
    expire_tm.tm_mday = expire.day;
    expire_tm.tm_hour = expire.hour;
    expire_tm.tm_min = expire.minute;
    expire_tm.tm_sec = expire.second;
    expire_tm.tm_isdst = -1;    // Let the system work out about DST

    // Convert to local time
    cltt = mktime(&expire_tm) - valid_lifetime;
}

void MySqlConnection::commit() {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
        if (mysql_commit(mysql_) != 0) {
                isc_throw(DbOperationError, "commit failed: "
                        << mysql_error(mysql_));
        }
}

void MySqlConnection::rollback() {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
        if (mysql_rollback(mysql_) != 0) {
                isc_throw(DbOperationError, "rollback failed: "
                        << mysql_error(mysql_));
        }
}


} // namespace isc::dhcp
} // namespace isc
