// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.


#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/mysql_connection.h>
#include <exceptions/exceptions.h>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

#include <time.h>

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

} // namespace isc::dhcp
} // namespace isc
