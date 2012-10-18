// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <iostream>
#include <iomanip>
#include <string>
#include <config.h>

#include <dhcp/mysql_lease_mgr.h>

using namespace std;

namespace isc {
namespace dhcp {

void
MySqlLeaseMgr::openDatabase() {

    // Set up the values of the parameters
    const char* host = NULL;
    string shost;
    try {
        shost = getParameter("host");
        host = shost.c_str();
    } catch (...) {
        // No host.  Fine, we'll use NULL
        ;
    }

    const char* user = NULL;
    string suser;
    try {
        suser = getParameter("user");
        user = suser.c_str();
    } catch (...) {
        // No user.  Fine, we'll use NULL
        ;
    }

    const char* password = NULL;
    string spassword;
    try {
        spassword = getParameter("password");
        password = spassword.c_str();
    } catch (...) {
        // No password.  Fine, we'll use NULL
        ;
    }

    const char* name = NULL;
    string sname;
    try {
        sname = getParameter("name");
        name = sname.c_str();
    } catch (...) {
        // No database name.  Fine, we'll use NULL
        ;
    }

    // Open the database.  Use defaults for non-specified options.
    MYSQL* status = mysql_real_connect(mysql_, host, user, password, name,
                                       0, NULL, 0);
    if (status != mysql_) {
        isc_throw(DbOpenError, mysql_error(mysql_));
    }
}

void
MySqlLeaseMgr::prepareStatement(StatementIndex index, const char* text) {
    // Validate that there is space for the statement in the statements array
    // and that nothing has been placed there before.
    if ((index >= statements_.size()) || (statements_[index] != NULL)) {
        isc_throw(InvalidParameter, "invalid prepared statement index or "
                  "statement index not null");
    }

    // All OK, so prepare the statement
    raw_statements_[index] = std::string(text);

    statements_[index] = mysql_stmt_init(mysql_);
    if (statements_[index] == NULL) {
        isc_throw(DbOperationError, "unable to allocate MySQL prepared "
                  "statement structure" << mysql_error(mysql_));
    }

    int status = mysql_stmt_prepare(statements_[index], text, strlen(text));
    if (status != 0) {
        isc_throw(DbOperationError, "unable to prepare MySQL statement <" <<
                  text << ">, reason: " << mysql_error(mysql_));
    }
}

void
MySqlLeaseMgr::prepareStatements() {
    // Allocate space for all statements
    statements_.clear();
    statements_.resize(NUM_STATEMENTS, NULL);
    
    raw_statements_.clear();
    raw_statements_.resize(NUM_STATEMENTS, std::string(""));

    // Now allocate the statements
    prepareStatement(SELECT_VERSION,
                     "SELECT version, minor FROM schema_version");
}


MySqlLeaseMgr::MySqlLeaseMgr(const LeaseMgr::ParameterMap& parameters) 
    : LeaseMgr(parameters), mysql_(NULL) {

    // Allocate context for MySQL - it is destroyed in the destructor.
    mysql_ = mysql_init(NULL);

    // Open the database
    openDatabase();

    // Disable autocommit
    my_bool result = mysql_autocommit(mysql_, 0);
    if (result != 0) {
        isc_throw(DbOperationError, mysql_error(mysql_));
    }

    // Prepare all statements likely to be used.
    prepareStatements();
}

MySqlLeaseMgr::~MySqlLeaseMgr() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them - we're destroying this object and are not really concerned
    // with errors on a database connection that it about to go away.)
    for (int i = 0; i < statements_.size(); ++i) {
        if (statements_[i] != NULL) {
            (void) mysql_stmt_close(statements_[i]);
            statements_[i] = NULL;
        }
    }

    // Close the database
    mysql_close(mysql_);
    mysql_ = NULL;
}

bool
MySqlLeaseMgr::addLease(Lease4Ptr /* lease */) {
    return (false);
}

bool
MySqlLeaseMgr::addLease(Lease6Ptr /* lease */) {
    return (false);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(isc::asiolink::IOAddress /* addr */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(isc::asiolink::IOAddress /* addr */) const {
    return (Lease4Ptr());
}

Lease4Collection
MySqlLeaseMgr::getLease4(const HWAddr& /* hwaddr */) const {
    return (Lease4Collection());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const HWAddr& /* hwaddr */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease4Collection
MySqlLeaseMgr::getLease4(const ClientId& /* clientid */) const {
    return (Lease4Collection());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const ClientId& /* clientid */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease6Ptr
MySqlLeaseMgr::getLease6(isc::asiolink::IOAddress /* addr */) const {
    return (Lease6Ptr());
}

Lease6Collection
MySqlLeaseMgr::getLease6(const DUID& /* duid */, uint32_t /* iaid */) const {
    return (Lease6Collection());
}

Lease6Ptr
MySqlLeaseMgr::getLease6(const DUID& /* duid */, uint32_t /* iaid */,
                         SubnetID /* subnet_id */) const {
    return (Lease6Ptr());
}

void
MySqlLeaseMgr::updateLease4(Lease4Ptr /* lease4 */) {
}

void
MySqlLeaseMgr::updateLease6(Lease6Ptr /* lease6 */) {
}

bool
MySqlLeaseMgr::deleteLease4(uint32_t /* addr */) {
    return (false);
}

bool
MySqlLeaseMgr::deleteLease6(isc::asiolink::IOAddress /* addr */) {
    return (false);
}

std::string
MySqlLeaseMgr::getName() const {
    return (std::string(""));
}

std::string
MySqlLeaseMgr::getDescription() const {
    return (std::string(""));
}

std::pair<uint32_t, uint32_t>
MySqlLeaseMgr::getVersion() const {
    uint32_t    major;      // Major version number
    uint32_t    minor;      // Minor version number

    // Execute the prepared statement
    int status = mysql_stmt_execute(statements_[SELECT_VERSION]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to execute <"
                  << raw_statements_[SELECT_VERSION] << "> - reason: " <<
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

    status = mysql_stmt_bind_result(statements_[SELECT_VERSION], bind);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to bind result set: " <<
                  mysql_error(mysql_));
    }

    // Get the result
    status = mysql_stmt_fetch(statements_[SELECT_VERSION]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to obtain result set: " <<
                  mysql_error(mysql_));
    }

    return (std::make_pair(major, minor));
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
