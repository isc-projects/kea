// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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


namespace {

const time_t MySqlConnection::MAX_DB_TIME = 2147483647;

/// @brief MySQL Selection Statements
///
/// Each statement is associated with an index, which is used to reference the
/// associated prepared statement.

struct TaggedStatement {
    MySqlConnection::StatementIndex index;
    const char*                   text;
};

TaggedStatement tagged_statements[] = {
    {MySqlLeaseMgr::DELETE_LEASE4,
                    "DELETE FROM lease4 WHERE address = ?"},
    {MySqlLeaseMgr::DELETE_LEASE6,
                    "DELETE FROM lease6 WHERE address = ?"},
    {MySqlLeaseMgr::GET_LEASE4_ADDR,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname "
                            "FROM lease4 "
                            "WHERE address = ?"},
    {MySqlLeaseMgr::GET_LEASE4_CLIENTID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname "
                            "FROM lease4 "
                            "WHERE client_id = ?"},
    {MySqlLeaseMgr::GET_LEASE4_CLIENTID_SUBID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname "
                            "FROM lease4 "
                            "WHERE client_id = ? AND subnet_id = ?"},
    {MySqlLeaseMgr::GET_LEASE4_HWADDR,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname "
                            "FROM lease4 "
                            "WHERE hwaddr = ?"},
    {MySqlLeaseMgr::GET_LEASE4_HWADDR_SUBID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname "
                            "FROM lease4 "
                            "WHERE hwaddr = ? AND subnet_id = ?"},
    {MySqlLeaseMgr::GET_LEASE6_ADDR,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source "
                            "FROM lease6 "
                            "WHERE address = ? AND lease_type = ?"},
    {MySqlLeaseMgr::GET_LEASE6_DUID_IAID,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source "
                            "FROM lease6 "
                            "WHERE duid = ? AND iaid = ? AND lease_type = ?"},
    {MySqlLeaseMgr::GET_LEASE6_DUID_IAID_SUBID,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source "
                            "FROM lease6 "
                            "WHERE duid = ? AND iaid = ? AND subnet_id = ? "
                            "AND lease_type = ?"},
    {MySqlLeaseMgr::GET_VERSION,
                    "SELECT version, minor FROM schema_version"},
    {MySqlLeaseMgr::INSERT_LEASE4,
                    "INSERT INTO lease4(address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"},
    {MySqlLeaseMgr::INSERT_LEASE6,
                    "INSERT INTO lease6(address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"},
    {MySqlLeaseMgr::UPDATE_LEASE4,
                    "UPDATE lease4 SET address = ?, hwaddr = ?, "
                        "client_id = ?, valid_lifetime = ?, expire = ?, "
                        "subnet_id = ?, fqdn_fwd = ?, fqdn_rev = ?, "
                        "hostname = ? "
                            "WHERE address = ?"},
    {MySqlLeaseMgr::UPDATE_LEASE6,
                    "UPDATE lease6 SET address = ?, duid = ?, "
                        "valid_lifetime = ?, expire = ?, subnet_id = ?, "
                        "pref_lifetime = ?, lease_type = ?, iaid = ?, "
                        "prefix_len = ?, fqdn_fwd = ?, fqdn_rev = ?, "
                        "hostname = ?, hwaddr = ?, hwtype = ?, hwaddr_source = ? "
                            "WHERE address = ?"},
    // End of list sentinel
    {MySqlLeaseMgr::NUM_STATEMENTS, NULL}
};


};  // Anonymous namespace

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

/// @brief Maximum size of an IPv6 address represented as a text string.
///
/// This is 32 hexadecimal characters written in 8 groups of four, plus seven
/// colon separators.
const size_t ADDRESS6_TEXT_MAX_LEN = 39;

/// @brief MySQL True/False constants
///
/// Declare typed values so as to avoid problems of data conversion.  These
/// are local to the file but are given the prefix MLM (MySql Lease Manager) to
/// avoid any likely conflicts with variables in header files named TRUE or
/// FALSE.

const my_bool MLM_FALSE = 0;                ///< False value
const my_bool MLM_TRUE = 1;                 ///< True value

/// @brief Maximum length of the hostname stored in DNS.
///
/// This length is restricted by the length of the domain-name carried
/// in the Client FQDN %Option (see RFC4702 and RFC4704).
const size_t HOSTNAME_MAX_LEN = 255;

///@}


std::string MySqlConnection::getParameter(const std::string& name) const {
    ParameterMap::const_iterator param = parameters_.find(name);
    if (param == parameters_.end()) {
        isc_throw(BadValue, "Parameter not found");
    }
    return (param->second);
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
MySqlConnection::prepareStatement(StatementIndex index, const char* text) {
    // Validate that there is space for the statement in the statements array
    // and that nothing has been placed there before.
    if ((index >= this->statements_.size()) || (this->statements_[index] != NULL)) {
        isc_throw(InvalidParameter, "invalid prepared statement index (" <<
                  static_cast<int>(index) << ") or indexed prepared " <<
                  "statement is not null");
    }

    // All OK, so prepare the statement
    this->text_statements_[index] = std::string(text);
    this->statements_[index] = mysql_stmt_init(mysql_);
    if (this->statements_[index] == NULL) {
        isc_throw(DbOperationError, "unable to allocate MySQL prepared "
                  "statement structure, reason: " << mysql_error(mysql_));
    }

    int status = mysql_stmt_prepare(this->statements_[index], text, strlen(text));
    if (status != 0) {
        isc_throw(DbOperationError, "unable to prepare MySQL statement <" <<
                  text << ">, reason: " << mysql_error(mysql_));
    }
}


void
MySqlConnection::prepareStatements() {
    // Allocate space for all statements
    statements_.clear();
    statements_.resize(NUM_STATEMENTS, NULL);

    text_statements_.clear();
    text_statements_.resize(NUM_STATEMENTS, std::string(""));


    // Created the MySQL prepared statements for each DML statement.
    for (int i = 0; tagged_statements[i].text != NULL; ++i) {
        prepareStatement(tagged_statements[i].index,
                         tagged_statements[i].text);
    }
}



// Miscellaneous database methods.

std::string
MySqlConnection::getName() const {
    std::string name = "";
    try {
        name = getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}


std::string
MySqlConnection::getDescription() const {
    return (std::string("MySQL Database"));
}


std::pair<uint32_t, uint32_t>
MySqlConnection::getVersion() const {
    const StatementIndex stindex = GET_VERSION;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_VERSION);

    uint32_t    major;      // Major version number
    uint32_t    minor;      // Minor version number

    // Execute the prepared statement
    int status = mysql_stmt_execute(statements_[stindex]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to execute <"
                  << text_statements_[stindex] << "> - reason: " <<
                  mysql_error(mysql_));
    }

    // Bind the output of the statement to the appropriate variables.
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].is_unsigned = 1;
    bind[0].buffer = &major;
    bind[0].buffer_length = sizeof(major);

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].is_unsigned = 1;
    bind[1].buffer = &minor;
    bind[1].buffer_length = sizeof(minor);

    status = mysql_stmt_bind_result(statements_[stindex], bind);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to bind result set: " <<
                  mysql_error(mysql_));
    }

    // Fetch the data and set up the "release" object to release associated
    // resources when this method exits then retrieve the data.
    MySqlFreeResult fetch_release(statements_[stindex]);
    status = mysql_stmt_fetch(statements_[stindex]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to obtain result set: " <<
                  mysql_error(mysql_));
    }

    return (std::make_pair(major, minor));
}


void
MySqlConnection::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
    if (mysql_commit(mysql_) != 0) {
        isc_throw(DbOperationError, "commit failed: " << mysql_error(mysql_));
    }
}


void
MySqlConnection::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
    if (mysql_rollback(mysql_) != 0) {
        isc_throw(DbOperationError, "rollback failed: " << mysql_error(mysql_));
    }
}

} // namespace isc::dhcp
} // namespace isc
