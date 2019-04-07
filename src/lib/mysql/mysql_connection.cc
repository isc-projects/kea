// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/db_log.h>
#include <exceptions/exceptions.h>
#include <mysql/mysql_connection.h>

#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <stdint.h>
#include <string>
#include <limits>

using namespace isc;
using namespace std;

namespace isc {
namespace db {

bool MySqlHolder::atexit_ = []{atexit([]{mysql_library_end();});return true;};

void
MySqlHolder::openDatabase(MySqlConnection& connection) {
    if (connected_) {
        return;
    }
    connected_ = true;
    prepared_ = true;
    connection.openDatabase();
    prepared_ = false;
}

void
MySqlHolder::prepareStatements(MySqlConnection& connection) {
    if (prepared_) {
        return;
    }
    clearPrepared();
    statements_.resize(connection.text_statements_.size(), NULL);
    uint32_t index = 0;
    for (auto it = connection.text_statements_.begin();
        it != connection.text_statements_.end(); ++it) {
        statements_[index] = mysql_stmt_init(mysql_);
        if (statements_[index] == NULL) {
            isc_throw(DbOperationError, "unable to allocate MySQL prepared "
                      "statement structure, reason: " << mysql_error(mysql_));
        }

        int status = mysql_stmt_prepare(statements_[index], it->c_str(), it->size());
        if (status != 0) {
            isc_throw(DbOperationError, "unable to prepare MySQL statement <" <<
                      *it << ">, reason: " << mysql_error(mysql_));
        }
        ++index;
    }
    prepared_ = true;
}

/// @todo: Migrate this default value to src/bin/dhcpX/simple_parserX.cc
const int MYSQL_DEFAULT_CONNECTION_TIMEOUT = 5; // seconds

MySqlTransaction::MySqlTransaction(MySqlConnection& conn)
    : conn_(conn), committed_(false) {
    conn_.startTransaction();
}

MySqlTransaction::~MySqlTransaction() {
    // Rollback if the MySqlTransaction::commit wasn't explicitly
    // called.
    if (!committed_) {
        try {
            conn_.rollback();
        } catch (...) {
        }
    }
}

void
MySqlTransaction::commit() {
    conn_.commit();
    committed_ = true;
}


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

    unsigned int port = 0;
    string sport;
    try {
        sport = getParameter("port");
    } catch (...) {
        // No port parameter, we are going to use the default port.
        sport = "";
    }

    if (sport.size() > 0) {
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
        isc_throw(NoDatabaseName, "must specify a name for the database");
    }

    unsigned int connect_timeout = MYSQL_DEFAULT_CONNECTION_TIMEOUT;
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

    // Set options for the connection:
    //
    // Set options for the connection:
    // Make sure auto_reconnect is OFF! Enabling it leaves us with an unusable
    // connection after a reconnect as among other things, it drops all our
    // pre-compiled statements.
    my_bool auto_reconnect = MLM_FALSE;
    int result = mysql_options(handle(), MYSQL_OPT_RECONNECT, &auto_reconnect);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set auto-reconnect option: " <<
                  mysql_error(handle()));
    }

    // Make sure we have a large idle time window ... say 30 days...
    const char *wait_time = "SET SESSION wait_timeout = 30 * 86400";
    result = mysql_options(handle(), MYSQL_INIT_COMMAND, wait_time);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set wait_timeout " <<
                  mysql_error(handle()));
    }

    // Set SQL mode options for the connection:  SQL mode governs how what
    // constitutes insertable data for a given column, and how to handle
    // invalid data.  We want to ensure we get the strictest behavior and
    // to reject invalid data with an error.
    const char *sql_mode = "SET SESSION sql_mode ='STRICT_ALL_TABLES'";
    result = mysql_options(handle(), MYSQL_INIT_COMMAND, sql_mode);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set SQL mode options: " <<
                  mysql_error(handle()));
    }

    // Connection timeout, the amount of time taken for the client to drop
    // the connection if the server is not responding.
    result = mysql_options(handle(), MYSQL_OPT_CONNECT_TIMEOUT, &connect_timeout);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set database connection timeout: " <<
                  mysql_error(handle()));
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
    MYSQL* status = mysql_real_connect(handle(), host, user, password, name,
                                       port, NULL, CLIENT_FOUND_ROWS);
    if (status != handle()) {
        isc_throw(DbOpenError, mysql_error(handle()));
    }

    // Enable autocommit. In case transaction is explicitly used, this
    // setting will be overwritten for the transaction. However, there are
    // cases when lack of autocommit could cause transactions to hang
    // until commit or rollback is explicitly called. This already
    // caused issues for some unit tests which were unable to cleanup
    // the database after the test because of pending transactions.
    // Use of autocommit will eliminate this problem.
    my_bool auto_commit = mysql_autocommit(handle(), 1);
    if (auto_commit != MLM_FALSE) {
        isc_throw(DbOperationError, mysql_error(handle()));
    }
    handle().connected_ = true;
    connected_ = true;
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
    if (index >= text_statements_.size()) {
        isc_throw(InvalidParameter, "invalid prepared statement index (" <<
                  static_cast<int>(index) << ")");
    }

    // All OK, so prepare the statement
    text_statements_[index] = std::string(text);
}

void
MySqlConnection::prepareStatements(const TaggedStatement* start_statement,
                                   const TaggedStatement* end_statement) {
    // Created the MySQL prepared statements for each DML statement.
    for (const TaggedStatement* tagged_statement = start_statement;
         tagged_statement != end_statement; ++tagged_statement) {
        if (tagged_statement->index >= text_statements_.size()) {
            text_statements_.resize(tagged_statement->index + 1,
                                    std::string(""));
        }
        prepareStatement(tagged_statement->index,
                         tagged_statement->text);
    }
    prepared_ = true;
}

/// @brief Destructor
MySqlConnection::~MySqlConnection() {
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
    MySqlBinding::convertToDatabaseTime(input_time, output_time);
}

void
MySqlConnection::convertToDatabaseTime(const time_t cltt,
                                       const uint32_t valid_lifetime,
                                       MYSQL_TIME& expire) {
    MySqlBinding::convertToDatabaseTime(cltt, valid_lifetime, expire);
}

void
MySqlConnection::convertFromDatabaseTime(const MYSQL_TIME& expire,
                                         uint32_t valid_lifetime, time_t& cltt) {
    MySqlBinding::convertFromDatabaseTime(expire, valid_lifetime, cltt);
}

void
MySqlConnection::startTransaction() {
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, MYSQL_START_TRANSACTION);
    // We create prepared statements for all other queries, but MySQL
    // don't support prepared statements for START TRANSACTION.
    int status = mysql_query(handle(), "START TRANSACTION");
    if (status != 0) {
        isc_throw(DbOperationError, "unable to start transaction, "
                  "reason: " << mysql_error(handle()));
    }
}

void
MySqlConnection::commit() {
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, MYSQL_COMMIT);
    if (mysql_commit(handle()) != 0) {
        isc_throw(DbOperationError, "commit failed: "
                  << mysql_error(handle()));
    }
}

void
MySqlConnection::rollback() {
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, MYSQL_ROLLBACK);
    if (mysql_rollback(handle()) != 0) {
        isc_throw(DbOperationError, "rollback failed: "
                  << mysql_error(handle()));
    }
}

}  // namespace db
}  // namespace isc
