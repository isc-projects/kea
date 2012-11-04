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
#include <mysql/mysqld_error.h>

#include <dhcp/mysql_lease_mgr.h>
#include <asiolink/io_address.h>

using namespace isc;
using namespace std;

namespace {
///@{
/// @brief Maximum Size of Database Fields
///
/// The following constants define buffer sizes for variable length database
/// fields.  The values should be greater than or equal to the length set in
/// the schema definition.
///
/// The exception is the length of any VARCHAR fields: these should be set
/// greater than or equal to the length of the field plus 2: this allows for
/// the insertion of a trailing null regardless of whether the data returned
/// contains a trailing null (the documentation is not clear on this point).

const size_t ADDRESS6_TEXT_MAX_LEN = 42;    // Max size of a IPv6 text buffer
const size_t DUID_MAX_LEN = 128;            // Max size of a DUID
///@}
};

namespace isc {
namespace dhcp {

/// @brief Exchange MySQL and Lease6 Data
///
/// On any MySQL operation, arrays of MYSQL_BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical - it defines data values in the Lease6 structure.
///
/// This class handles the creation of that array.  For maximum flexibility,
/// the data is appended to an array of MYSQL_BIND elemements, so allowing
/// additional elements to be prepended/appended to it.
///
/// Owing to the MySQL API, the process requires some intermediate variables
/// to hold things like length etc.  This object holds the intermediate
/// variables as well.

class MySqlLease6Exchange {
public:
    /// @brief Constructor
    ///
    /// Apart from the initialization of false_ and true_, the other
    /// initializations are to satisfy cppcheck: none are really needed, as all
    /// variables are initialized/set in the methods.
    MySqlLease6Exchange() : addr6_length_(0), duid_length_(0), false_(0), true_(1) {
        memset(addr6_buffer_, 0, sizeof(addr6_buffer_));
        memset(duid_buffer_, 0, sizeof(duid_buffer_));
    }

    /// @brief Create MYSQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the MYSQL_BIND objects for the Lease6 passed to it.
    ///
    /// @param lease Lease object to be added to the database
    /// @param bindvec Vector of MySQL BIND objects: the elements describing the
    ///        lease are appended to this vector.  The data added to the vector
    ///        only remain valid while both the lease and this object are valid.
    void
    createBindForSend(const Lease6Ptr& lease, std::vector<MYSQL_BIND>& bindvec) {
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Ensure bind_ array clear for constructing the MYSQL_BIND structures
        // for this lease.
        memset(bind_, 0, sizeof(bind_));

        // address: varchar(40)
        addr6_ = lease_->addr_.toText();
        addr6_length_ = addr6_.size();

        bind_[0].buffer_type = MYSQL_TYPE_STRING;
        bind_[0].buffer = const_cast<char*>(addr6_.c_str());
        bind_[0].buffer_length = addr6_length_;
        bind_[0].length = &addr6_length_;

        // duid: varchar(128)
        duid_ = lease_->duid_->getDuid();
        duid_length_ = duid_.size();

        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(&(duid_[0]));
        bind_[1].buffer_length = duid_length_;
        bind_[1].length = &duid_length_;

        // valid lifetime: unsigned int
        bind_[2].buffer_type = MYSQL_TYPE_LONG;
        bind_[2].buffer = reinterpret_cast<char*>(&lease->valid_lft_);
        bind_[2].is_unsigned = true_;

        // expire: timestamp
        // The lease structure holds the client last transmission time (cltt_)
        // For convenience for external tools, this is converted to lease
        /// expiry time (expire).  The relationship is given by:
        //
        // expire = cltt_ + valid_lft_
        //
        // @TODO Handle overflows
        MySqlLeaseMgr::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                             expire_);
        bind_[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_[3].buffer = reinterpret_cast<char*>(&expire_);
        bind_[3].buffer_length = sizeof(expire_);

        // subnet_id: unsigned int
        // Can use lease_->subnet_id_ directly as it is of type uint32_t.
        bind_[4].buffer_type = MYSQL_TYPE_LONG;
        bind_[4].buffer = reinterpret_cast<char*>(&lease_->subnet_id_);
        bind_[4].is_unsigned = true_;

        // pref_lifetime: unsigned int
        // Can use lease_->preferred_lft_ directly as it is of type uint32_t.
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&lease_->preferred_lft_);
        bind_[5].is_unsigned = true_;

        // lease_type: tinyint
        // Must convert to uint8_t as lease_->type_ is a LeaseType variable
        lease_type_ = lease_->type_;
        bind_[6].buffer_type = MYSQL_TYPE_TINY;
        bind_[6].buffer = reinterpret_cast<char*>(&lease_type_);
        bind_[6].is_unsigned = true_;

        // iaid: unsigned int
        // Can use lease_->iaid_ directly as it is of type uint32_t.
        bind_[7].buffer_type = MYSQL_TYPE_LONG;
        bind_[7].buffer = reinterpret_cast<char*>(&lease_->iaid_);
        bind_[7].is_unsigned = true_;

        // prefix_len: unsigned tinyint
        // Can use lease_->prefixlen_ directly as it is uint32_t.
        bind_[8].buffer_type = MYSQL_TYPE_TINY;
        bind_[8].buffer = reinterpret_cast<char*>(&lease_->prefixlen_);
        bind_[8].is_unsigned = true_;

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        bindvec.insert(bindvec.end(), &bind_[0], &bind_[9]);
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease6 data from the database.
    /// After data is successfully received, getLeaseData() is used to copy
    /// it to a Lease6 object.
    ///
    /// @param bindvec Vector of MySQL BIND objects: the elements describing the
    ///        lease are appended to this vector.  The data added to the vector
    ///        only remain valid while both the lease and this object are valid.

    void createBindForReceive(std::vector<MYSQL_BIND>& bindvec) {

        // Ensure both the array of MYSQL_BIND structures and the error array
        // are clear.
        memset(bind_, 0, sizeof(bind_));
        memset(error_, 0, sizeof(error_));

        // address:  varchar
        // A Lease6_ address has a maximum of 39 characters.  The array is
        // a few bites longer than this to guarantee that we can always null
        // terminate it.
        addr6_length_ = sizeof(addr6_buffer_) - 1;
        bind_[0].buffer_type = MYSQL_TYPE_STRING;
        bind_[0].buffer = addr6_buffer_;
        bind_[0].buffer_length = addr6_length_;
        bind_[0].length = &addr6_length_;
        bind_[0].error = &error_[0];

        // client_id: varbinary(128)
        duid_length_ = sizeof(duid_buffer_);
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(duid_buffer_);
        bind_[1].buffer_length = duid_length_;
        bind_[1].length = &duid_length_;
        bind_[1].error = &error_[1];

        // lease_time: unsigned int
        bind_[2].buffer_type = MYSQL_TYPE_LONG;
        bind_[2].buffer = reinterpret_cast<char*>(&valid_lifetime_);
        bind_[2].is_unsigned = true_;
        bind_[2].error = &error_[2];

        // expire: timestamp
        bind_[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_[3].buffer = reinterpret_cast<char*>(&expire_);
        bind_[3].buffer_length = sizeof(expire_);
        bind_[3].error = &error_[3];

        // subnet_id: unsigned int
        bind_[4].buffer_type = MYSQL_TYPE_LONG;
        bind_[4].buffer = reinterpret_cast<char*>(&subnet_id_);
        bind_[4].is_unsigned = true_;
        bind_[4].error = &error_[4];

        // pref_lifetime: unsigned int
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&pref_lifetime_);
        bind_[5].is_unsigned = true_;
        bind_[5].error = &error_[5];

        // lease_type: tinyint
        bind_[6].buffer_type = MYSQL_TYPE_TINY;
        bind_[6].buffer = reinterpret_cast<char*>(&lease_type_);
        bind_[6].is_unsigned = true_;
        bind_[6].error = &error_[6];

        // iaid: unsigned int
        bind_[7].buffer_type = MYSQL_TYPE_LONG;
        bind_[7].buffer = reinterpret_cast<char*>(&iaid_);
        bind_[7].is_unsigned = true_;
        bind_[7].error = &error_[7];
 
        // prefix_len: unsigned tinyint
        bind_[8].buffer_type = MYSQL_TYPE_TINY;
        bind_[8].buffer = reinterpret_cast<char*>(&prefixlen_);
        bind_[8].is_unsigned = true_;
        bind_[8].error = &error_[8];

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        bindvec.insert(bindvec.end(), &bind_[0], &bind_[9]);
    }

    /// @brief Copy Received Data into Lease6 Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member vairables
    /// into a Lease6 object.
    ///
    /// @return Lease6Ptr Pointer to a Lease6 object holding the relevant
    ///         data.
    ///
    /// @exception BadValue Unable to convert Lease Type value in database
    Lease6Ptr getLeaseData() {

        // Create the object to be returned.
        Lease6Ptr result(new Lease6());

        // Put the data in the lease object

        // The address buffer is declared larger than the buffer size passed
        // to the access function so that we can always append a null byte.
        addr6_buffer_[addr6_length_] = '\0';
        std::string address = addr6_buffer_;

        // Set the other data, converting time as needed.
        result->addr_ = isc::asiolink::IOAddress(address);
        result->duid_.reset(new DUID(duid_buffer_, duid_length_));
        MySqlLeaseMgr::convertFromDatabaseTime(expire_, valid_lifetime_,
                                               result->cltt_);
        result->valid_lft_ = valid_lifetime_;
        result->subnet_id_ = subnet_id_;
        result->preferred_lft_ = pref_lifetime_;

        // We can't convert from a numeric value to an enum, hence:
        switch (lease_type_) {
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
                isc_throw(BadValue, "invalid lease type returned (" <<
                          lease_type_ << ") for lease with address " <<
                          result->addr_.toText() << ". Only 0, 1, or 2 "
                          "are allowed.");
        }
        result->iaid_ = iaid_;
        result->prefixlen_ = prefixlen_;

        return (result);
    }

private:
    // Note: All array legths are equal to the corresponding variable in the
    // schema.
    std::string     addr6_;             ///< String form of address
    char            addr6_buffer_[ADDRESS6_TEXT_MAX_LEN];  ///< Character 
                                        ///< array form of V6 address
    unsigned long   addr6_length_;      ///< Length of the address
    MYSQL_BIND      bind_[9];           ///< Static array for speed of access
    std::vector<uint8_t> duid_;         ///< Client identification
    uint8_t         duid_buffer_[DUID_MAX_LEN]; ///< Buffer form of DUID
    unsigned long   duid_length_;       ///< Length of the DUID
    my_bool         error_[9];          ///< For error reporting
    MYSQL_TIME      expire_;            ///< Lease expiry time
    const my_bool   false_;             ///< "false" for MySql
    uint32_t        iaid_;              ///< Identity association ID
    Lease6Ptr       lease_;             ///< Pointer to lease object
    uint32_t        valid_lifetime_;    ///< Lease time
    uint8_t         lease_type_;        ///< Lease type
    uint8_t         prefixlen_;         ///< Prefix length
    uint32_t        pref_lifetime_;     ///< Preferred lifetime
    uint32_t        subnet_id_;         ///< Subnet identification
    const my_bool   true_;              ///< "true_" for MySql
};


MySqlLeaseMgr::MySqlLeaseMgr(const LeaseMgr::ParameterMap& parameters) 
    : LeaseMgr(parameters), mysql_(NULL) {

    // Allocate context for MySQL - it is destroyed in the destructor.
    mysql_ = mysql_init(NULL);
    if (mysql_ == NULL) {
        isc_throw(DbOpenError, "unable to initialize MySQL");
    }

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
MySqlLeaseMgr::convertToDatabaseTime(time_t cltt, uint32_t valid_lifetime,
                                    MYSQL_TIME& expire) {

    // Calculate expiry time and convert to various date/time fields.
    // @TODO: handle overflows
    time_t expire_time = cltt + valid_lifetime;

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
    expire.second_part = 0;                    // No fractional seconds
    expire.neg = static_cast<my_bool>(0);      // Not negative
}

void
MySqlLeaseMgr::convertFromDatabaseTime(const MYSQL_TIME& expire,
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

void
MySqlLeaseMgr::openDatabase() {

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
        // No database name.  Throw a "NoName" exception
        isc_throw(NoDatabaseName, "must specified a name for the database");
    }

    // Set options for the connection:
    // - automatic reconnection
    my_bool auto_reconnect = 1;
    int result = mysql_options(mysql_, MYSQL_OPT_RECONNECT, &auto_reconnect);
    if (result != 0) {
        isc_throw(DbOpenError, "unable to set auto-reconnect option: " <<
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
    // row was found by no data was altered.
    MYSQL* status = mysql_real_connect(mysql_, host, user, password, name,
                                       0, NULL, CLIENT_FOUND_ROWS);
    if (status != mysql_) {
        isc_throw(DbOpenError, mysql_error(mysql_));
    }
}

void
MySqlLeaseMgr::prepareStatement(StatementIndex index, const char* text) {
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
    
    text_statements_.clear();
    text_statements_.resize(NUM_STATEMENTS, std::string(""));

    // Now allocate the statements
    prepareStatement(DELETE_LEASE6,
                     "DELETE FROM lease6 WHERE address = ?");
    prepareStatement(GET_LEASE6_ADDR,
                     "SELECT address, duid, valid_lifetime, "
                         "expire, subnet_id, pref_lifetime, "
                         "lease_type, iaid, prefix_len "
                             "FROM lease6 "
                             "WHERE address = ?");
    prepareStatement(GET_LEASE6_DUID_IAID,
                     "SELECT address, duid, valid_lifetime, "
                         "expire, subnet_id, pref_lifetime, "
                         "lease_type, iaid, prefix_len "
                             "FROM lease6 "
                             "WHERE duid = ? AND iaid = ?");
    prepareStatement(GET_LEASE6_DUID_IAID_SUBID,
                     "SELECT address, duid, valid_lifetime, "
                         "expire, subnet_id, pref_lifetime, "
                         "lease_type, iaid, prefix_len "
                             "FROM lease6 "
                             "WHERE duid = ? AND iaid = ? AND subnet_id = ?");
    prepareStatement(GET_VERSION,
                     "SELECT version, minor FROM schema_version");
    prepareStatement(INSERT_LEASE6,
                     "INSERT INTO lease6(address, duid, valid_lifetime, "
                         "expire, subnet_id, pref_lifetime, "
                         "lease_type, iaid, prefix_len) "
                             "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    prepareStatement(UPDATE_LEASE6,
                     "UPDATE lease6 SET address = ?, duid = ?, "
                         "valid_lifetime = ?, expire = ?, subnet_id = ?, "
                         "pref_lifetime = ?, lease_type = ?, iaid = ?, "
                         "prefix_len = ? "
                             "WHERE address = ?");
}

bool
MySqlLeaseMgr::addLease(const Lease4Ptr& /* lease */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::addLease(const Lease4Ptr&) "
              "not implemented yet");
    return (false);
}

bool
MySqlLeaseMgr::addLease(const Lease6Ptr& lease) {

    // Create the MYSQL_BIND array for the lease
    MySqlLease6Exchange exchange;
    std::vector<MYSQL_BIND> bind;
    exchange.createBindForSend(lease, bind);

    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(statements_[INSERT_LEASE6], &bind[0]);
    checkError(status, INSERT_LEASE6, "unable to bind parameters");

    // Execute the statement
    status = mysql_stmt_execute(statements_[INSERT_LEASE6]);
    if (status != 0) {

        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (mysql_errno(mysql_) == ER_DUP_ENTRY) {
            return (false);
        }
        checkError(status, INSERT_LEASE6, "unable to execute");
    }

    // Insert succeeded
    return (true);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& /* addr */,
                         SubnetID /* subnet_id */) const {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLease4(const IOAddress&, SubnetID) "
              "not implemented yet");
    return (Lease4Ptr());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& /* addr */) const {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLease4(const IOAddress&) "
              "not implemented yet");
    return (Lease4Ptr());
}

Lease4Collection
MySqlLeaseMgr::getLease4(const HWAddr& /* hwaddr */) const {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLease4(const HWAddr&) "
              "not implemented yet");
    return (Lease4Collection());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const HWAddr& /* hwaddr */,
                         SubnetID /* subnet_id */) const {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLease4(const HWAddr&, SubnetID) "
              "not implemented yet");
    return (Lease4Ptr());
}

Lease4Collection
MySqlLeaseMgr::getLease4(const ClientId& /* clientid */) const {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLease4(const ClientID&) "
              "not implemented yet");
    return (Lease4Collection());
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const ClientId& /* clientid */,
                         SubnetID /* subnet_id */) const {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLease4(const ClientID&, SubnetID) "
              "not implemented yet");
    return (Lease4Ptr());
}

Lease6Ptr
MySqlLeaseMgr::getLease6(const isc::asiolink::IOAddress& addr) const {
    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    std::string addr6 = addr.toText();
    unsigned long addr6_length = addr6.size();

    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(addr6.c_str());
    inbind[0].buffer_length = addr6_length;
    inbind[0].length = &addr6_length;

    // Bind the input parameters to the statement
    int status = mysql_stmt_bind_param(statements_[GET_LEASE6_ADDR], inbind);
    checkError(status, GET_LEASE6_ADDR, "unable to bind WHERE clause parameter");

    // Set up the SELECT clause
    MySqlLease6Exchange exchange;
    std::vector<MYSQL_BIND> outbind;
    exchange.createBindForReceive(outbind);

    // Bind the output parameters to the statement
    status = mysql_stmt_bind_result(statements_[GET_LEASE6_ADDR], &outbind[0]);
    checkError(status, GET_LEASE6_ADDR, "unable to bind SELECT caluse parameters");

    // Execute the statement
    status = mysql_stmt_execute(statements_[GET_LEASE6_ADDR]);
    checkError(status, GET_LEASE6_ADDR, "unable to execute");

    // Fetch the data.
    status = mysql_stmt_fetch(statements_[GET_LEASE6_ADDR]);

    Lease6Ptr result;
    if (status == 0) {
        try {
            result = exchange.getLeaseData();
        } catch (const isc::BadValue& ex) {
            // Free up result set.

            (void) mysql_stmt_free_result(statements_[GET_LEASE6_ADDR]);
            // Lease type is returned, to rethrow the exception with a bit
            // more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      text_statements_[GET_LEASE6_ADDR] << ">");
        }

        // As the address is the primary key in the table, we can't return
        // two rows, so we don't bother checking whether multiple rows have
        // been returned.

    } else if (status == 1) {
        checkError(status, GET_LEASE6_ADDR, "unable to fetch results");

    } else {
        // @TODO Handle truncation
        // We are ignoring truncation for now, so the only other result is
        // no data was found.  In that case, we return a null Lease6 structure.
        // This has already been set, so the action is a no-op.
    }

    // Free data structures associated with information returned.
    (void) mysql_stmt_free_result(statements_[GET_LEASE6_ADDR]);
    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLease6(const DUID& duid, uint32_t iaid) const {
    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // DUID.  The complex casting is needed to obtain the "const" vector of
    // uint8_t from the DUID, point to the start of it (discarding the
    // "const"ness) and finally casing it to "char*" for the MySQL buffer
    // element.
    const vector<uint8_t>& duid_vector = duid.getDuid();
    unsigned long duid_length = duid_vector.size();
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(
            const_cast<uint8_t*>(&duid_vector[0]));
    inbind[0].buffer_length = duid_length;
    inbind[0].length = &duid_length;

    // IAID
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&iaid);
    inbind[1].is_unsigned = static_cast<my_bool>(1);

    // Bind the input parameters to the statement
    int status = mysql_stmt_bind_param(statements_[GET_LEASE6_DUID_IAID], inbind);
    checkError(status, GET_LEASE6_DUID_IAID, "unable to bind WHERE clause parameter");

    // Set up the SELECT clause
    MySqlLease6Exchange exchange;
    std::vector<MYSQL_BIND> outbind;
    exchange.createBindForReceive(outbind);

    // Bind the output parameters to the statement
    status = mysql_stmt_bind_result(statements_[GET_LEASE6_DUID_IAID], &outbind[0]);
    checkError(status, GET_LEASE6_DUID_IAID, "unable to bind SELECT clause parameters");

    // Execute the query.
    status = mysql_stmt_execute(statements_[GET_LEASE6_DUID_IAID]);
    checkError(status, GET_LEASE6_DUID_IAID, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid overhead
    // of going back and forth between client and server.
    status = mysql_stmt_store_result(statements_[GET_LEASE6_DUID_IAID]);
    checkError(status, GET_LEASE6_DUID_IAID, "unable to set up for storing all results");

    // Fetch the data.  There could be multiple rows, so we need to iterate
    // until all data has been retrieved.
    Lease6Collection result;
    while ((status = mysql_stmt_fetch(statements_[GET_LEASE6_DUID_IAID])) == 0) {
        try {
            Lease6Ptr lease = exchange.getLeaseData();
            result.push_back(lease);

        } catch (const isc::BadValue& ex) {
            // Free up result set.
            (void) mysql_stmt_free_result(statements_[GET_LEASE6_DUID_IAID]);

            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      text_statements_[GET_LEASE6_DUID_IAID] << ">");
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fecth results
        checkError(status, GET_LEASE6_DUID_IAID, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // @TODO Handle truncation
        ;
    }

    // Free up resources assoicated with the fetched data.
    (void) mysql_stmt_free_result(statements_[GET_LEASE6_DUID_IAID]);
    return (result);
}

Lease6Ptr
MySqlLeaseMgr::getLease6(const DUID& duid, uint32_t iaid,
                         SubnetID subnet_id) const {
    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // DUID.  The complex casting is needed to obtain the "const" vector of
    // uint8_t from the DUID, point to the start of it (discarding the
    // "const"ness) and finally casing it to "char*" for the MySQL buffer
    // element.
    const vector<uint8_t>& duid_vector = duid.getDuid();
    unsigned long duid_length = duid_vector.size();
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(
            const_cast<uint8_t*>(&duid_vector[0]));
    inbind[0].buffer_length = duid_length;
    inbind[0].length = &duid_length;

    // IAID
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&iaid);
    inbind[1].is_unsigned = static_cast<my_bool>(1);

    // Subnet ID
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[2].is_unsigned = static_cast<my_bool>(1);

    // Bind the input parameters to the statement
    int status = mysql_stmt_bind_param(statements_[GET_LEASE6_DUID_IAID_SUBID], inbind);
    checkError(status, GET_LEASE6_DUID_IAID_SUBID, "unable to bind WHERE clause parameter");

    // Set up the SELECT clause
    MySqlLease6Exchange exchange;
    std::vector<MYSQL_BIND> outbind;
    exchange.createBindForReceive(outbind);

    // Bind the output parameters to the statement
    status = mysql_stmt_bind_result(statements_[GET_LEASE6_DUID_IAID_SUBID], &outbind[0]);
    checkError(status, GET_LEASE6_DUID_IAID_SUBID, "unable to bind SELECT clause parameters");

    // Execute the query.
    status = mysql_stmt_execute(statements_[GET_LEASE6_DUID_IAID_SUBID]);
    checkError(status, GET_LEASE6_DUID_IAID_SUBID, "unable to execute");

    Lease6Ptr result;
    status = mysql_stmt_fetch(statements_[GET_LEASE6_DUID_IAID_SUBID]);
    if (status == 0) {
        try {
            result = exchange.getLeaseData();

            // TODO: check for more than one row returned.  At present, just ignore
            // the excess and take the first.

        } catch (const isc::BadValue& ex) {
            // Free up result set.

            (void) mysql_stmt_free_result(statements_[GET_LEASE6_DUID_IAID_SUBID]);
            // Lease type is returned, to rethrow the exception with a bit
            // more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      text_statements_[GET_LEASE6_DUID_IAID_SUBID] << ">");
        }

        // As the address is the primary key in the table, we can't return
        // two rows, so we don't bother checking whether multiple rows have
        // been returned.

    } else if (status == 1) {
        checkError(status, GET_LEASE6_DUID_IAID_SUBID, "unable to fetch results");

    } else {
        // @TODO Handle truncation
        // We are ignoring truncation for now, so the only other result is
        // no data was found.  In that case, we return a null Lease6 structure.
        // This has already been set, so the action is a no-op.
    }

    // Free data structures associated with information returned.
    (void) mysql_stmt_free_result(statements_[GET_LEASE6_DUID_IAID_SUBID]);
    return (result);
}

void
MySqlLeaseMgr::updateLease4(const Lease4Ptr& /* lease4 */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::updateLease4(const Lease4Ptr&) "
              "not implemented yet");
}

void
MySqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    // Create the MYSQL_BIND array for the data being updated
    MySqlLease6Exchange exchange;
    std::vector<MYSQL_BIND> bind;
    exchange.createBindForSend(lease, bind);

    // Set up the WHERE clause value
    MYSQL_BIND where;
    memset(&where, 0, sizeof(where));

    std::string addr6 = lease->addr_.toText();
    unsigned long addr6_length = addr6.size();

    where.buffer_type = MYSQL_TYPE_STRING;
    where.buffer = const_cast<char*>(addr6.c_str());
    where.buffer_length = addr6_length;
    where.length = &addr6_length;
    bind.push_back(where);

    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(statements_[UPDATE_LEASE6], &bind[0]);
    checkError(status, UPDATE_LEASE6, "unable to bind parameters");

    // Execute
    status = mysql_stmt_execute(statements_[UPDATE_LEASE6]);
    checkError(status, UPDATE_LEASE6, "unable to execute");

    // See how many rows were affected.  The statement should only delete a
    // single row.
    int affected_rows = mysql_stmt_affected_rows(statements_[UPDATE_LEASE6]);
    if (affected_rows == 0) {
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  addr6 << " as it does not exist");
    } else if (affected_rows > 1) {
        // Should not happen - primary key constraint should only have selected
        // one row.
        isc_throw(DbOperationError, "apparently updated more than one lease "
                  "that had the address " << addr6);
    }
}

bool
MySqlLeaseMgr::deleteLease4(const isc::asiolink::IOAddress& /* addr */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::deleteLease4(const IOAddress&) "
              "not implemented yet");
    return (false);
}

bool
MySqlLeaseMgr::deleteLease6(const isc::asiolink::IOAddress& addr) {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    std::string addr6 = addr.toText();
    unsigned long addr6_length = addr6.size();

    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(addr6.c_str());
    inbind[0].buffer_length = addr6_length;
    inbind[0].length = &addr6_length;

    // Bind the input parameters to the statement
    int status = mysql_stmt_bind_param(statements_[DELETE_LEASE6], inbind);
    checkError(status, DELETE_LEASE6, "unable to bind WHERE clause parameter");

    // Execute
    status = mysql_stmt_execute(statements_[DELETE_LEASE6]);
    checkError(status, DELETE_LEASE6, "unable to execute");

    // See how many rows were affected.  Note that the statement may delete
    // multiple rows.
    return (mysql_stmt_affected_rows(statements_[DELETE_LEASE6]) > 0);

    return false;
}

std::string
MySqlLeaseMgr::getName() const {
    std::string name = "";
    try {
        name = getParameter("name");
    } catch (...) {
        ;
    }
    return (name);
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
                  << text_statements_[GET_VERSION] << "> - reason: " <<
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
        (void) mysql_stmt_free_result(statements_[GET_VERSION]);
        isc_throw(DbOperationError, "unable to obtain result set: " <<
                  mysql_error(mysql_));
    }

    (void) mysql_stmt_free_result(statements_[GET_VERSION]);
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
