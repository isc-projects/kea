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
#include <time.h>
#include <dhcp/mysql_lease_mgr.h>
#include <asiolink/io_address.h>

using namespace std;

namespace isc {
namespace dhcp {

// Time conversion methods.
//
// Note that the MySQL TIMESTAMP data type (used for "expire") converts data
// from the current timezone to UTC for storage, and from UTC to the current
// timezone for retrieval.  This means that the external interface - cltt -
// must be local time.

void
MySqlLeaseMgr::convertFromLeaseTime(time_t cltt, uint32_t valid_lft,
                                    MYSQL_TIME& expire, uint32_t& lease_time) {

    // Calculate expiry time and convert to various date/time fields.
    time_t expire_time = cltt + valid_lft;
    struct tm expire_tm;
    (void) localtime_r(&expire_time, &expire_tm);

    // Place in output expire structure.
    expire.year = expire_tm.tm_year + 1900;
    expire.month = expire_tm.tm_mon + 1;     // Note different base
    expire.day = expire_tm.tm_mday;
    expire.hour = expire_tm.tm_hour;
    expire.minute = expire_tm.tm_min;
    expire.second = expire_tm.tm_sec;
    expire.second_part = 0;                    // No fractional seconds
    expire.neg = static_cast<my_bool>(0);      // Not negative

    // Set the lease time.
    lease_time = valid_lft;
}

void
MySqlLeaseMgr::convertToLeaseTime(const MYSQL_TIME& expire, uint32_t lease_time,
                                  time_t& cltt, uint32_t& valid_lft) {
    valid_lft = lease_time;

    // Copy across fields from MYSQL_TIME structure.
    struct tm expire_tm;

    expire_tm.tm_year = expire.year - 1900;
    expire_tm.tm_mon = expire.month - 1;
    expire_tm.tm_mday = expire.day;
    expire_tm.tm_hour = expire.hour;
    expire_tm.tm_min = expire.minute;
    expire_tm.tm_sec = expire.second;

    // Convert to local time
    cltt = mktime(&expire_tm) - valid_lft;
}

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
    prepareStatement(GET_LEASE6,
                     "SELECT hwaddr, client_id, "
                         "lease_time, expire, subnet_id, pref_lifetime, "
                         "lease_type, iaid, prefix_len "
                         "FROM lease6 WHERE address = ?");
    prepareStatement(GET_VERSION,
                     "SELECT version, minor FROM schema_version");
    prepareStatement(INSERT_LEASE6,
                     "INSERT INTO lease6(address, hwaddr, client_id, "
                         "lease_time, expire, subnet_id, pref_lifetime, "
                         "lease_type, iaid, prefix_len) "
                         "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
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
MySqlLeaseMgr::addLease(const Lease4Ptr& /* lease */) {

    return (false);
}

bool
MySqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    my_bool MLM_FALSE = 0;
    MYSQL_BIND bind[10];
    memset(bind, 0, sizeof(bind));

    // address: varchar(40)
    std::string addr6 = lease->addr_.toText();
    unsigned long addr6_length = addr6.size();

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(addr6.c_str());
    bind[0].buffer_length = addr6_length;
    bind[0].length = &addr6_length;
    bind[0].is_null = &MLM_FALSE;

    // hwaddr: binary(20)
    unsigned long hwaddr_length = lease->hwaddr_.size();

    bind[1].buffer_type = MYSQL_TYPE_BLOB;

    bind[1].buffer = reinterpret_cast<char*>(&(lease->hwaddr_[0]));
    bind[1].buffer_length = hwaddr_length;
    bind[1].length = &hwaddr_length;
    bind[1].is_null = &MLM_FALSE;

    // client_id: varchar(128)
    vector<uint8_t> clientid = lease->duid_->getDuid();
    unsigned long clientid_length = clientid.size();

    bind[2].buffer_type = MYSQL_TYPE_BLOB;
    bind[2].buffer = reinterpret_cast<char*>(&(clientid[0]));
    bind[2].buffer_length = clientid_length;
    bind[2].length = &clientid_length;
    bind[2].is_null = &MLM_FALSE;

    // The lease structure holds the client last transmission time (cltt_)
    // and the valid lifetime (valid_lft_).  For convenience, the data stored
    // in the database is expiry time (expire) and lease time (lease+time).
    // The relationship is given by:
    //
    // lease_time - valid_lft_
    // expire = cltt_ + valid_lft_
    MYSQL_TIME mysql_expire;
    uint32_t lease_time;
    convertFromLeaseTime(lease->cltt_, lease->valid_lft_,
                         mysql_expire, lease_time);

    // lease_time: unsigned int
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = reinterpret_cast<char*>(&lease_time);
    bind[3].is_unsigned = 1;
    bind[3].is_null = &MLM_FALSE;

    // expire: timestamp
    bind[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
    bind[4].buffer = reinterpret_cast<char*>(&mysql_expire);
    bind[4].buffer_length = sizeof(mysql_expire);
    bind[4].is_null = &MLM_FALSE;

    // subnet_id: unsigned int
    bind[5].buffer_type = MYSQL_TYPE_LONG;
    bind[5].buffer = reinterpret_cast<char*>(&(lease->subnet_id_));
    bind[5].is_unsigned = static_cast<my_bool>(1);
    bind[5].is_null = &MLM_FALSE;

    // pref_lifetime: unsigned int
    bind[6].buffer_type = MYSQL_TYPE_LONG;
    bind[6].buffer = reinterpret_cast<char*>(&(lease->preferred_lft_));
    bind[6].is_unsigned = static_cast<my_bool>(1);
    bind[6].is_null = &MLM_FALSE;

    // lease_type: tinyint
    uint8_t lease_type = lease->type_;  // Needed for int -> uint8_t conversion
    bind[7].buffer_type = MYSQL_TYPE_TINY;
    bind[7].buffer = reinterpret_cast<char*>(&lease_type);
    bind[7].is_unsigned = static_cast<my_bool>(1);
    bind[7].is_null = &MLM_FALSE;

    // iaid: unsigned int
    bind[8].buffer_type = MYSQL_TYPE_LONG;
    bind[8].buffer = reinterpret_cast<char*>(&(lease->iaid_));
    bind[8].is_unsigned = static_cast<my_bool>(1);
    bind[8].is_null = &MLM_FALSE;

    // prefix_len: unsigned tinyint
    bind[9].buffer_type = MYSQL_TYPE_TINY;
    bind[9].buffer = reinterpret_cast<char*>(&(lease->prefixlen_));
    bind[9].is_unsigned = static_cast<my_bool>(1);
    bind[9].is_null = &MLM_FALSE;

    // Bind the parameters to the statement
    my_bool status = mysql_stmt_bind_param(statements_[INSERT_LEASE6], bind);
    checkError(status, INSERT_LEASE6, "unable to bind parameters");

    // Execute the statement
    status = mysql_stmt_execute(statements_[INSERT_LEASE6]);
    checkError(status, INSERT_LEASE6, "unable to execute");

    // ... and find out whether a row as inserted.
    return (mysql_stmt_affected_rows(statements_[INSERT_LEASE6]) == 1);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& /* addr */,
                         SubnetID /* subnet_id */) const {
    return (Lease4Ptr());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& /* addr */) const {
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
MySqlLeaseMgr::getLease6(const isc::asiolink::IOAddress& addr) const {
    my_bool MLM_FALSE = 0;    // MySqlLeaseMgr false
    my_bool MLM_TRUE = 1;     // MySqlLeaseMgr true

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    std::string addr6 = addr.toText();
    unsigned long addr6_length = addr6.size();

    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(addr6.c_str());
    inbind[0].buffer_length = addr6_length;
    inbind[0].length = &addr6_length;
    inbind[0].is_null = &MLM_FALSE;

    // Bind the parameters to the statement
    my_bool status = mysql_stmt_bind_param(statements_[GET_LEASE6], inbind);
    checkError(status, GET_LEASE6, "unable to bind WHERE clause parameter");

    // Output values
    MYSQL_BIND outbind[9];
    memset(outbind, 0, sizeof(outbind));

    // address:  Not obtained - because of the WHERE clause, it will always be
    // the same as the input parameter.

    // hwaddr: varbinary(20)
    uint8_t hwaddr[20];
    unsigned long hwaddr_length;

    outbind[0].buffer_type = MYSQL_TYPE_BLOB;
    outbind[0].buffer = reinterpret_cast<char*>(hwaddr);
    outbind[0].buffer_length = sizeof(hwaddr);
    outbind[0].length = &hwaddr_length;

    // client_id: varbinary(128)
    uint8_t clientid[128];
    unsigned long clientid_length;

    outbind[1].buffer_type = MYSQL_TYPE_BLOB;
    outbind[1].buffer = reinterpret_cast<char*>(clientid);
    outbind[1].buffer_length = sizeof(clientid);
    outbind[1].length = &clientid_length;

    // lease_time: unsigned int
    unsigned lease_time;
    outbind[2].buffer_type = MYSQL_TYPE_LONG;
    outbind[2].buffer = reinterpret_cast<char*>(&lease_time);
    outbind[2].is_unsigned = MLM_TRUE;

    // expire: timestamp
    MYSQL_TIME mysql_expire;
    outbind[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
    outbind[3].buffer = reinterpret_cast<char*>(&mysql_expire);
    outbind[3].buffer_length = sizeof(mysql_expire);

    // subnet_id: unsigned int
    unsigned subnet_id;
    outbind[4].buffer_type = MYSQL_TYPE_LONG;
    outbind[4].buffer = reinterpret_cast<char*>(&subnet_id);
    outbind[4].is_unsigned = MLM_TRUE;

    // pref_lifetime: unsigned int
    unsigned pref_lifetime;
    outbind[5].buffer_type = MYSQL_TYPE_LONG;
    outbind[5].buffer = reinterpret_cast<char*>(&pref_lifetime);
    outbind[5].is_unsigned = MLM_TRUE;

    // lease_type: tinyint
    uint8_t lease_type;
    outbind[6].buffer_type = MYSQL_TYPE_TINY;
    outbind[6].buffer = reinterpret_cast<char*>(&lease_type);
    outbind[6].is_unsigned = MLM_TRUE;

    // iaid: unsigned int
    unsigned iaid;
    outbind[7].buffer_type = MYSQL_TYPE_LONG;
    outbind[7].buffer = reinterpret_cast<char*>(&iaid);
    outbind[7].is_unsigned = MLM_TRUE;

    // prefix_len: unsigned tinyint
    uint8_t prefixlen;
    outbind[8].buffer_type = MYSQL_TYPE_TINY;
    outbind[8].buffer = reinterpret_cast<char*>(&prefixlen);
    outbind[8].is_unsigned = MLM_TRUE;

    // Bind the parameters to the statement
    status = mysql_stmt_bind_result(statements_[GET_LEASE6], outbind);
    checkError(status, GET_LEASE6, "unable to bind SELECT caluse parameters");

    // Execute the statement
    status = mysql_stmt_execute(statements_[GET_LEASE6]);
    checkError(status, GET_LEASE6, "unable to execute");

    // Fetch the data.
    Lease6Ptr result(new Lease6());
    status = mysql_stmt_fetch(statements_[GET_LEASE6]);
    if (status == 0) {
        // Success - put the data in the lease object
        result->addr_ = addr;
        result->hwaddr_ = vector<uint8_t>(&hwaddr[0], &hwaddr[hwaddr_length]);
        result->duid_.reset(new DUID(clientid, clientid_length));
        convertToLeaseTime(mysql_expire, lease_time,
                           result->cltt_, result->valid_lft_);
        result->subnet_id_ = subnet_id;
        result->preferred_lft_ = pref_lifetime;
        switch (lease_type) {
            case Lease6::LEASE_IA_NA:
                result->type_ = Lease6::LEASE_IA_NA;
                break;

            case Lease6::LEASE_IA_TA:
                result->type_ = Lease6::LEASE_IA_TA;
                break;

            case Lease6::LEASE_IA_PD:
                result->type_ = Lease6::LEASE_IA_PD;
                break;

            default:
                isc_throw(BadValue, "invalid lease type returned for <" <<
                          raw_statements_[GET_LEASE6] << ">");
        }
        result->iaid_ = iaid;
        result->prefixlen_ = prefixlen;

        // As the address is the primary key in the table, we can't return
        // two rows, so we don't bother checking.

    } else if (status == 1) {
        checkError(status, GET_LEASE6, "unable to fetch results");

    } else {
    //     We are ignoring truncation for now, so the only other result is
    //     no data was found.  In that case, we returrn a null Lease6 structure.
    //     This has already been set, so ther action is a no-op.
    }

    return (result);
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
MySqlLeaseMgr::updateLease4(const Lease4Ptr& /* lease4 */) {
}

void
MySqlLeaseMgr::updateLease6(const Lease6Ptr& /* lease6 */) {
}

bool
MySqlLeaseMgr::deleteLease4(const isc::asiolink::IOAddress& /* addr */) {
    return (false);
}

bool
MySqlLeaseMgr::deleteLease6(const isc::asiolink::IOAddress& /* addr */) {
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
    int status = mysql_stmt_execute(statements_[GET_VERSION]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to execute <"
                  << raw_statements_[GET_VERSION] << "> - reason: " <<
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

    status = mysql_stmt_bind_result(statements_[GET_VERSION], bind);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to bind result set: " <<
                  mysql_error(mysql_));
    }

    // Get the result
    status = mysql_stmt_fetch(statements_[GET_VERSION]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to obtain result set: " <<
                  mysql_error(mysql_));
    }

    return (std::make_pair(major, minor));
}

void
MySqlLeaseMgr::commit() {
    if (mysql_commit(mysql_) != 0) {
        isc_throw(DbOperationError, "commit failed: " << mysql_error(mysql_));
    }
}

void
MySqlLeaseMgr::rollback() {
    if (mysql_rollback(mysql_) != 0) {
        isc_throw(DbOperationError, "rollback failed: " << mysql_error(mysql_));
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
