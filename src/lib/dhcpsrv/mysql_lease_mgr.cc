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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/mysql_lease_mgr.h>
#include <dhcpsrv/mysql_connection.h>

#include <boost/static_assert.hpp>
#include <mysqld_error.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

/// @file
///
/// This file holds the implementation of the Lease Manager using MySQL.  The
/// implementation uses MySQL's C API, as it comes as standard with the MySQL
/// client libraries.
///
/// In general, each of the database access methods corresponds to one SQL
/// statement.  To avoid the overhead of parsing a statement every time it is
/// used, when the database is opened "prepared statements" are created -
/// essentially doing the SQL parsing up front.  Every time a method is used
/// to access data, the corresponding prepared statement is referenced. Each
/// prepared statement contains a set of placeholders for data, each
/// placeholder being for:
///
/// - data being added to the database (as in adding or updating a lease)
/// - data being retrieved from the database (as in getting lease information)
/// - selection criteria used to determine which records to update/retrieve.
///
/// All such data is associated with the prepared statment using an array of
/// MYSQL_BIND structures.  Each element in the array corresponds to one
/// parameter in the prepared statement - the first element in the array is
/// associated with the first parameter, the second element with the second
/// parameter etc.
///
/// Within this file, the setting up of the MYSQL_BIND arrays for data being
/// passed to and retrieved from the database is handled in the
/// isc::dhcp::MySqlLease4Exchange and isc::dhcp::MySqlLease6Exchange classes.
/// The classes also hold intermediate variables required for exchanging some
/// of the data.
///
/// With these exchange objects in place, many of the methods follow similar
/// logic:
/// - Set up the MYSQL_BIND array for data being transferred to/from the
///   database.  For data being transferred to the database, some of the
///   data is extracted from the lease to intermediate variables, whilst
///   in other cases the MYSQL_BIND arrays point to the data in the lease.
/// - Set up the MYSQL_BIND array for the data selection parameters.
/// - Bind these arrays to the prepared statement.
/// - Execute the statement.
/// - If there is output, copy the data from the bound variables to the output
///   lease object.

namespace {
/// @brief Maximum length of the hostname stored in DNS.
///
/// This length is restricted by the length of the domain-name carried
/// in the Client FQDN %Option (see RFC4702 and RFC4704).
const size_t HOSTNAME_MAX_LEN = 255;

/// @brief Maximum size of an IPv6 address represented as a text string.
///
/// This is 32 hexadecimal characters written in 8 groups of four, plus seven
/// colon separators.
const size_t ADDRESS6_TEXT_MAX_LEN = 39;

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

};

namespace isc {
namespace dhcp {

/// @brief Common MySQL and Lease Data Methods
///
/// The MySqlLease4Exchange and MySqlLease6Exchange classes provide the
/// functionaility to set up binding information between variables in the
/// program and data extracted from the database.  This class is the common
/// base to both of them, containing some common methods.

class MySqlLeaseExchange {
public:
    /// @brief Set error indicators
    ///
    /// Sets the error indicator for each of the MYSQL_BIND elements.  It points
    /// the "error" field within an element of the input array to the
    /// corresponding element of the passed error array.
    ///
    /// @param bind Array of BIND elements
    /// @param error Array of error elements.  If there is an error in getting
    ///        data associated with one of the "bind" elements, the
    ///        corresponding element in the error array is set to MLM_TRUE.
    /// @param count Size of each of the arrays.
    static void setErrorIndicators(MYSQL_BIND* bind, my_bool* error,
                                   size_t count) {
        for (size_t i = 0; i < count; ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<char*>(&error[i]);
        }
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static std::string getColumnsInError(my_bool* error, std::string* names,
                                         size_t count) {
        std::string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < count; ++i) {
            if (error[i] == MLM_TRUE) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += names[i];
            }
        }

        if (result.empty()) {
            result = "(None)";
        }

        return (result);
    }
};


/// @brief Exchange MySQL and Lease4 Data
///
/// On any MySQL operation, arrays of MYSQL_BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the MySQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all MySqlLeaseMgr::xxx4() calls where it is used.

class MySqlLease4Exchange : public MySqlLeaseExchange {
    /// @brief Set number of database columns for this lease structure
    static const size_t LEASE_COLUMNS = 9;

public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlLease4Exchange() : addr4_(0), hwaddr_length_(0), client_id_length_(0),
                            client_id_null_(MLM_FALSE),
                            fqdn_fwd_(false), fqdn_rev_(false), hostname_length_(0) {
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));
        memset(hostname_buffer_, 0, sizeof(hostname_buffer_));
        std::fill(&error_[0], &error_[LEASE_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[0] = "address";
        columns_[1] = "hwaddr";
        columns_[2] = "client_id";
        columns_[3] = "valid_lifetime";
        columns_[4] = "expire";
        columns_[5] = "subnet_id";
        columns_[6] = "fqdn_fwd";
        columns_[7] = "fqdn_rev";
        columns_[8] = "hostname";
        BOOST_STATIC_ASSERT(8 < LEASE_COLUMNS);
    }

    /// @brief Create MYSQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data in the Lease4 object to
    /// the database.
    ///
    /// @param lease Lease object to be added to the database.  None of the
    ///        fields in the lease are modified - the lease data is only read.
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const Lease4Ptr& lease) {

        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // Set up the structures for the various components of the lease4
        // structure.

        try {
            // Address: uint32_t
            // The address in the Lease structure is an IOAddress object.  Convert
            // this to an integer for storage.
            addr4_ = static_cast<uint32_t>(lease_->addr_);
            bind_[0].buffer_type = MYSQL_TYPE_LONG;
            bind_[0].buffer = reinterpret_cast<char*>(&addr4_);
            bind_[0].is_unsigned = MLM_TRUE;
            // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // hwaddr: varbinary(128)
            // For speed, we avoid copying the data into temporary storage and
            // instead extract it from the lease structure directly.
            hwaddr_length_ = lease_->hwaddr_->hwaddr_.size();
            bind_[1].buffer_type = MYSQL_TYPE_BLOB;
            bind_[1].buffer = reinterpret_cast<char*>(&(lease_->hwaddr_->hwaddr_[0]));
            bind_[1].buffer_length = hwaddr_length_;
            bind_[1].length = &hwaddr_length_;
            // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // client_id: varbinary(128)
            if (lease_->client_id_) {
                client_id_ = lease_->client_id_->getClientId();
                client_id_length_ = client_id_.size();
                bind_[2].buffer_type = MYSQL_TYPE_BLOB;
                bind_[2].buffer = reinterpret_cast<char*>(&client_id_[0]);
                bind_[2].buffer_length = client_id_length_;
                bind_[2].length = &client_id_length_;
                // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                                 // reasons, see memset() above
            } else {
                bind_[2].buffer_type = MYSQL_TYPE_NULL;

                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                client_id_null_ = MLM_TRUE;
                bind_[2].buffer = NULL;
                bind_[2].is_null = &client_id_null_;
            }

            // valid lifetime: unsigned int
            bind_[3].buffer_type = MYSQL_TYPE_LONG;
            bind_[3].buffer = reinterpret_cast<char*>(&lease_->valid_lft_);
            bind_[3].is_unsigned = MLM_TRUE;
            // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // expire: timestamp
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            MySqlLeaseMgr::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                                 expire_);
            bind_[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
            bind_[4].buffer = reinterpret_cast<char*>(&expire_);
            bind_[4].buffer_length = sizeof(expire_);
            // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // subnet_id: unsigned int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&lease_->subnet_id_);
            bind_[5].is_unsigned = MLM_TRUE;
            // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_fwd: boolean
            bind_[6].buffer_type = MYSQL_TYPE_TINY;
            bind_[6].buffer = reinterpret_cast<char*>(&lease_->fqdn_fwd_);
            bind_[6].is_unsigned = MLM_TRUE;
            // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_rev: boolean
            bind_[7].buffer_type = MYSQL_TYPE_TINY;
            bind_[7].buffer = reinterpret_cast<char*>(&lease_->fqdn_rev_);
            bind_[7].is_unsigned = MLM_TRUE;
            // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // hostname: varchar(255)
            bind_[8].buffer_type = MYSQL_TYPE_VARCHAR;
            bind_[8].buffer = const_cast<char*>(lease_->hostname_.c_str());
            bind_[8].buffer_length = lease_->hostname_.length();
            // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // Add the error flags
            setErrorIndicators(bind_, error_, LEASE_COLUMNS);

            // .. and check that we have the numbers correct at compile time.
            BOOST_STATIC_ASSERT(8 < LEASE_COLUMNS);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease4 data from the database.
    /// After data is successfully received, getLeaseData() can be used to copy
    /// it to a Lease6 object.
    ///
    std::vector<MYSQL_BIND> createBindForReceive() {

        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // address:  uint32_t
        bind_[0].buffer_type = MYSQL_TYPE_LONG;
        bind_[0].buffer = reinterpret_cast<char*>(&addr4_);
        bind_[0].is_unsigned = MLM_TRUE;
        // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // hwaddr: varbinary(20)
        hwaddr_length_ = sizeof(hwaddr_buffer_);
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(hwaddr_buffer_);
        bind_[1].buffer_length = hwaddr_length_;
        bind_[1].length = &hwaddr_length_;
        // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // client_id: varbinary(128)
        client_id_length_ = sizeof(client_id_buffer_);
        bind_[2].buffer_type = MYSQL_TYPE_BLOB;
        bind_[2].buffer = reinterpret_cast<char*>(client_id_buffer_);
        bind_[2].buffer_length = client_id_length_;
        bind_[2].length = &client_id_length_;
        bind_[2].is_null = &client_id_null_;
        // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // lease_time: unsigned int
        bind_[3].buffer_type = MYSQL_TYPE_LONG;
        bind_[3].buffer = reinterpret_cast<char*>(&valid_lifetime_);
        bind_[3].is_unsigned = MLM_TRUE;
        // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // expire: timestamp
        bind_[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_[4].buffer = reinterpret_cast<char*>(&expire_);
        bind_[4].buffer_length = sizeof(expire_);
        // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // subnet_id: unsigned int
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&subnet_id_);
        bind_[5].is_unsigned = MLM_TRUE;
        // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_fwd: boolean
        bind_[6].buffer_type = MYSQL_TYPE_TINY;
        bind_[6].buffer = reinterpret_cast<char*>(&fqdn_fwd_);
        bind_[6].is_unsigned = MLM_TRUE;
        // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_rev: boolean
        bind_[7].buffer_type = MYSQL_TYPE_TINY;
        bind_[7].buffer = reinterpret_cast<char*>(&fqdn_rev_);
        bind_[7].is_unsigned = MLM_TRUE;
        // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // hostname: varchar(255)
        hostname_length_ = sizeof(hostname_buffer_);
        bind_[8].buffer_type = MYSQL_TYPE_STRING;
        bind_[8].buffer = reinterpret_cast<char*>(hostname_buffer_);
        bind_[8].buffer_length = hostname_length_;
        bind_[8].length = &hostname_length_;
        // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // Add the error flags
        setErrorIndicators(bind_, error_, LEASE_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(8 < LEASE_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return(std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Copy Received Data into Lease6 Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a Lease4 objec.
    ///
    /// @return Lease4Ptr Pointer to a Lease6 object holding the relevant
    ///         data.
    Lease4Ptr getLeaseData() {
        // Convert times received from the database to times for the lease
        // structure
        time_t cltt = 0;
        MySqlLeaseMgr::convertFromDatabaseTime(expire_, valid_lifetime_, cltt);

        if (client_id_null_==MLM_TRUE) {
            // There's no client-id, so we pass client-id_length_ set to 0
            client_id_length_ = 0;
        }

        // Hostname is passed to Lease4 as a string object. We have to create
        // it from the buffer holding hostname and the buffer length.
        std::string hostname(hostname_buffer_,
                             hostname_buffer_ + hostname_length_);

        // Recreate the hardware address.
        HWAddrPtr hwaddr(new HWAddr(hwaddr_buffer_, hwaddr_length_, HTYPE_ETHER));

        // note that T1 and T2 are not stored
        return (Lease4Ptr(new Lease4(addr4_, hwaddr,
                                     client_id_buffer_, client_id_length_,
                                     valid_lifetime_, 0, 0, cltt, subnet_id_,
                                     fqdn_fwd_, fqdn_rev_, hostname)));
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    std::string getErrorColumns() {
        return (getColumnsInError(error_, columns_, LEASE_COLUMNS));
    }

private:

    // Note: All array lengths are equal to the corresponding variable in the
    //       schema.
    // Note: Arrays are declared fixed length for speed of creation
    uint32_t        addr4_;             ///< IPv4 address
    MYSQL_BIND      bind_[LEASE_COLUMNS]; ///< Bind array
    std::string     columns_[LEASE_COLUMNS];///< Column names
    my_bool         error_[LEASE_COLUMNS];  ///< Error array
    std::vector<uint8_t> hwaddr_;       ///< Hardware address
    uint8_t         hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
                                        ///< Hardware address buffer
    unsigned long   hwaddr_length_;     ///< Hardware address length
    std::vector<uint8_t> client_id_;    ///< Client identification
    uint8_t         client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
                                        ///< Client ID buffer
    unsigned long   client_id_length_;  ///< Client ID address length
    my_bool         client_id_null_;    ///< Is Client ID null?

    MYSQL_TIME      expire_;            ///< Lease expiry time
    Lease4Ptr       lease_;             ///< Pointer to lease object
    uint32_t        subnet_id_;         ///< Subnet identification
    uint32_t        valid_lifetime_;    ///< Lease time

    my_bool         fqdn_fwd_;          ///< Has forward DNS update been
                                        ///< performed
    my_bool         fqdn_rev_;          ///< Has reverse DNS update been
                                        ///< performed
    char            hostname_buffer_[HOSTNAME_MAX_LEN];
                                        ///< Client hostname
    unsigned long   hostname_length_;   ///< Client hostname length

};



/// @brief Exchange MySQL and Lease6 Data
///
/// On any MySQL operation, arrays of MYSQL_BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the MySQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all MySqlLeaseMgr::xxx6() calls where it is used.

class MySqlLease6Exchange : public MySqlLeaseExchange {
    /// @brief Set number of database columns for this lease structure
    static const size_t LEASE_COLUMNS = 15;

public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is nonly to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlLease6Exchange() : addr6_length_(0), duid_length_(0),
                            fqdn_fwd_(false), fqdn_rev_(false),
                            hostname_length_(0), hwaddr_length_(0),
                            hwaddr_null_(MLM_FALSE), hwtype_(0), hwaddr_source_(0) {
        memset(addr6_buffer_, 0, sizeof(addr6_buffer_));
        memset(duid_buffer_, 0, sizeof(duid_buffer_));
        memset(hostname_buffer_, 0, sizeof(hostname_buffer_));
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        std::fill(&error_[0], &error_[LEASE_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[0]  = "address";
        columns_[1]  = "duid";
        columns_[2]  = "valid_lifetime";
        columns_[3]  = "expire";
        columns_[4]  = "subnet_id";
        columns_[5]  = "pref_lifetime";
        columns_[6]  = "lease_type";
        columns_[7]  = "iaid";
        columns_[8]  = "prefix_len";
        columns_[9]  = "fqdn_fwd";
        columns_[10] = "fqdn_rev";
        columns_[11] = "hostname";
        columns_[12] = "hwaddr";
        columns_[13] = "hwtype";
        columns_[14] = "hwaddr_source";
        BOOST_STATIC_ASSERT(14 < LEASE_COLUMNS);
    }

    /// @brief Create MYSQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data in the Lease4 object to
    /// the database.
    ///
    /// @param lease Lease object to be added to the database.
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const Lease6Ptr& lease) {
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Ensure bind_ array clear for constructing the MYSQL_BIND structures
        // for this lease.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        try {
            // address: varchar(39)
            addr6_ = lease_->addr_.toText();
            addr6_length_ = addr6_.size();

            // In the following statement, the string is being read.  However, the
            // MySQL C interface does not use "const", so the "buffer" element
            // is declared as "char*" instead of "const char*".  To resolve this,
            // the "const" is discarded.  (Note that the address of addr6_.c_str()
            // is guaranteed to be valid until the next non-const operation on
            // addr6_.)
            //
            // The const_cast could be avoided by copying the string to a writeable
            // buffer and storing the address of that in the "buffer" element.
            // However, this introduces a copy operation (with additional overhead)
            // purely to get round the structures introduced by design of the
            // MySQL interface (which uses the area pointed to by "buffer" as input
            // when specifying query parameters and as output when retrieving data).
            // For that reason, "const_cast" has been used.
            bind_[0].buffer_type = MYSQL_TYPE_STRING;
            bind_[0].buffer = const_cast<char*>(addr6_.c_str());
            bind_[0].buffer_length = addr6_length_;
            bind_[0].length = &addr6_length_;
            // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // duid: varchar(128)
            if (!lease_->duid_) {
                isc_throw(DbOperationError, "lease6 for address " << addr6_
                          << " is missing mandatory client-id.");
            }
            duid_ = lease_->duid_->getDuid();
            duid_length_ = duid_.size();

            bind_[1].buffer_type = MYSQL_TYPE_BLOB;
            bind_[1].buffer = reinterpret_cast<char*>(&(duid_[0]));
            bind_[1].buffer_length = duid_length_;
            bind_[1].length = &duid_length_;
            // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // valid lifetime: unsigned int
            bind_[2].buffer_type = MYSQL_TYPE_LONG;
            bind_[2].buffer = reinterpret_cast<char*>(&lease_->valid_lft_);
            bind_[2].is_unsigned = MLM_TRUE;
            // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // expire: timestamp
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            /// expiry time (expire).  The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            //
            MySqlLeaseMgr::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                                 expire_);
            bind_[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
            bind_[3].buffer = reinterpret_cast<char*>(&expire_);
            bind_[3].buffer_length = sizeof(expire_);
            // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // subnet_id: unsigned int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            bind_[4].buffer_type = MYSQL_TYPE_LONG;
            bind_[4].buffer = reinterpret_cast<char*>(&lease_->subnet_id_);
            bind_[4].is_unsigned = MLM_TRUE;
            // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // pref_lifetime: unsigned int
            // Can use lease_->preferred_lft_ directly as it is of type uint32_t.
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&lease_->preferred_lft_);
            bind_[5].is_unsigned = MLM_TRUE;
            // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // lease_type: tinyint
            // Must convert to uint8_t as lease_->type_ is a LeaseType variable.
            lease_type_ = lease_->type_;
            bind_[6].buffer_type = MYSQL_TYPE_TINY;
            bind_[6].buffer = reinterpret_cast<char*>(&lease_type_);
            bind_[6].is_unsigned = MLM_TRUE;
            // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // iaid: unsigned int
            // Can use lease_->iaid_ directly as it is of type uint32_t.
            bind_[7].buffer_type = MYSQL_TYPE_LONG;
            bind_[7].buffer = reinterpret_cast<char*>(&lease_->iaid_);
            bind_[7].is_unsigned = MLM_TRUE;
            // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // prefix_len: unsigned tinyint
            // Can use lease_->prefixlen_ directly as it is uint32_t.
            bind_[8].buffer_type = MYSQL_TYPE_TINY;
            bind_[8].buffer = reinterpret_cast<char*>(&lease_->prefixlen_);
            bind_[8].is_unsigned = MLM_TRUE;
            // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_fwd: boolean
            bind_[9].buffer_type = MYSQL_TYPE_TINY;
            bind_[9].buffer = reinterpret_cast<char*>(&lease_->fqdn_fwd_);
            bind_[9].is_unsigned = MLM_TRUE;
            // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_rev: boolean
            bind_[10].buffer_type = MYSQL_TYPE_TINY;
            bind_[10].buffer = reinterpret_cast<char*>(&lease_->fqdn_rev_);
            bind_[10].is_unsigned = MLM_TRUE;
            // bind_[10].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // hostname: varchar(255)
            bind_[11].buffer_type = MYSQL_TYPE_VARCHAR;
            bind_[11].buffer = const_cast<char*>(lease_->hostname_.c_str());
            bind_[11].buffer_length = lease_->hostname_.length();
            // bind_[11].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // hwaddr: varbinary(20) - hardware/MAC address
            HWAddrPtr hwaddr = lease_->hwaddr_;
            if (hwaddr) {
                hwaddr_ = hwaddr->hwaddr_;
                hwaddr_length_ = hwaddr->hwaddr_.size();

                bind_[12].buffer_type = MYSQL_TYPE_BLOB;
                bind_[12].buffer = reinterpret_cast<char*>(&(hwaddr_[0]));
                bind_[12].buffer_length = hwaddr_length_;
                bind_[12].length = &hwaddr_length_;
            } else {
                bind_[12].buffer_type = MYSQL_TYPE_NULL;

                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[12].buffer = NULL;
                bind_[12].is_null = &hwaddr_null_;
            }

            // hwtype
            if (hwaddr) {
                hwtype_ = lease->hwaddr_->htype_;
                bind_[13].buffer_type = MYSQL_TYPE_SHORT;
                bind_[13].buffer = reinterpret_cast<char*>(&hwtype_);
                bind_[13].is_unsigned = MLM_TRUE;
            } else {
                hwtype_ = 0;
                bind_[13].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[13].buffer = NULL;
                bind_[13].is_null = &hwaddr_null_;
            }

            /// Hardware source
            if (hwaddr) {
                hwaddr_source_ = lease->hwaddr_->source_;
                bind_[14].buffer_type = MYSQL_TYPE_LONG;
                bind_[14].buffer = reinterpret_cast<char*>(&hwaddr_source_);
                bind_[14].is_unsigned = MLM_TRUE;
            } else {
                hwaddr_source_ = 0;

                bind_[14].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[14].buffer = NULL;
                bind_[14].is_null = &hwaddr_null_;
            }

            // Add the error flags
            setErrorIndicators(bind_, error_, LEASE_COLUMNS);

            // .. and check that we have the numbers correct at compile time.
            BOOST_STATIC_ASSERT(14 < LEASE_COLUMNS);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease6 data from the database.
    /// After data is successfully received, getLeaseData() is used to copy
    /// it to a Lease6 object.
    ///
    /// @return Vector of MySQL BIND objects passed to the MySQL data retrieval
    ///         functions.
    std::vector<MYSQL_BIND> createBindForReceive() {

        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // address:  varchar(39)
        // A Lease6_ address has a maximum of 39 characters.  The array is
        // one byte longer than this to guarantee that we can always null
        // terminate it whatever is returned.
        addr6_length_ = sizeof(addr6_buffer_) - 1;
        bind_[0].buffer_type = MYSQL_TYPE_STRING;
        bind_[0].buffer = addr6_buffer_;
        bind_[0].buffer_length = addr6_length_;
        bind_[0].length = &addr6_length_;
        // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // client_id: varbinary(128)
        duid_length_ = sizeof(duid_buffer_);
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(duid_buffer_);
        bind_[1].buffer_length = duid_length_;
        bind_[1].length = &duid_length_;
        // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // lease_time: unsigned int
        bind_[2].buffer_type = MYSQL_TYPE_LONG;
        bind_[2].buffer = reinterpret_cast<char*>(&valid_lifetime_);
        bind_[2].is_unsigned = MLM_TRUE;
        // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // expire: timestamp
        bind_[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_[3].buffer = reinterpret_cast<char*>(&expire_);
        bind_[3].buffer_length = sizeof(expire_);
        // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // subnet_id: unsigned int
        bind_[4].buffer_type = MYSQL_TYPE_LONG;
        bind_[4].buffer = reinterpret_cast<char*>(&subnet_id_);
        bind_[4].is_unsigned = MLM_TRUE;
        // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // pref_lifetime: unsigned int
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&pref_lifetime_);
        bind_[5].is_unsigned = MLM_TRUE;
        // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // lease_type: tinyint
        bind_[6].buffer_type = MYSQL_TYPE_TINY;
        bind_[6].buffer = reinterpret_cast<char*>(&lease_type_);
        bind_[6].is_unsigned = MLM_TRUE;
        // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // iaid: unsigned int
        bind_[7].buffer_type = MYSQL_TYPE_LONG;
        bind_[7].buffer = reinterpret_cast<char*>(&iaid_);
        bind_[7].is_unsigned = MLM_TRUE;
        // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // prefix_len: unsigned tinyint
        bind_[8].buffer_type = MYSQL_TYPE_TINY;
        bind_[8].buffer = reinterpret_cast<char*>(&prefixlen_);
        bind_[8].is_unsigned = MLM_TRUE;
        // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_fwd: boolean
        bind_[9].buffer_type = MYSQL_TYPE_TINY;
        bind_[9].buffer = reinterpret_cast<char*>(&fqdn_fwd_);
        bind_[9].is_unsigned = MLM_TRUE;
        // bind_[9].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_rev: boolean
        bind_[10].buffer_type = MYSQL_TYPE_TINY;
        bind_[10].buffer = reinterpret_cast<char*>(&fqdn_rev_);
        bind_[10].is_unsigned = MLM_TRUE;
        // bind_[10].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // hostname: varchar(255)
        hostname_length_ = sizeof(hostname_buffer_);
        bind_[11].buffer_type = MYSQL_TYPE_STRING;
        bind_[11].buffer = reinterpret_cast<char*>(hostname_buffer_);
        bind_[11].buffer_length = hostname_length_;
        bind_[11].length = &hostname_length_;
        // bind_[11].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // hardware address
        // hwaddr: varbinary(20)
        hwaddr_null_ = MLM_FALSE;
        hwaddr_length_ = sizeof(hwaddr_buffer_);
        bind_[12].buffer_type = MYSQL_TYPE_BLOB;
        bind_[12].buffer = reinterpret_cast<char*>(hwaddr_buffer_);
        bind_[12].buffer_length = hwaddr_length_;
        bind_[12].length = &hwaddr_length_;
        bind_[12].is_null = &hwaddr_null_;

        // hardware type: unsigned short int (16 bits)
        bind_[13].buffer_type = MYSQL_TYPE_SHORT;
        bind_[13].buffer = reinterpret_cast<char*>(&hwtype_);
        bind_[13].is_unsigned = MLM_TRUE;

        // hardware source: unsigned int (32 bits)
        bind_[14].buffer_type = MYSQL_TYPE_LONG;
        bind_[14].buffer = reinterpret_cast<char*>(&hwaddr_source_);
        bind_[14].is_unsigned = MLM_TRUE;

        // Add the error flags
        setErrorIndicators(bind_, error_, LEASE_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(14 < LEASE_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return(std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Copy Received Data into Lease6 Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a Lease6 object.
    ///
    /// @return Lease6Ptr Pointer to a Lease6 object holding the relevant
    ///         data.
    ///
    /// @throw isc::BadValue Unable to convert Lease Type value in database
    Lease6Ptr getLeaseData() {
        // The address buffer is declared larger than the buffer size passed
        // to the access function so that we can always append a null byte.
        // Create the IOAddress object corresponding to the received data.
        addr6_buffer_[addr6_length_] = '\0';
        std::string address = addr6_buffer_;
        isc::asiolink::IOAddress addr(address);

        // Set the lease type in a variable of the appropriate data type, which
        // has been initialized with an arbitrary (but valid) value.
        Lease::Type type = Lease::TYPE_NA;
        switch (lease_type_) {
            case Lease::TYPE_NA:
                type = Lease::TYPE_NA;
                break;

            case Lease::TYPE_TA:
                type = Lease::TYPE_TA;
                break;

            case Lease::TYPE_PD:
                type = Lease::TYPE_PD;
                break;

            default:
                isc_throw(BadValue, "invalid lease type returned (" <<
                          static_cast<int>(lease_type_) << ") for lease with "
                          << "address " << address << ". Only 0, 1, or 2 are "
                          << "allowed.");
        }

        // Set up DUID,
        DuidPtr duid_ptr(new DUID(duid_buffer_, duid_length_));

        // Hostname is passed to Lease6 as a string object, so we have to
        // create it from the hostname buffer and length.
        std::string hostname(hostname_buffer_,
                             hostname_buffer_ + hostname_length_);

        /// Set hardware address if it was set
        HWAddrPtr hwaddr;
        if (hwaddr_null_ == MLM_FALSE) {
            hwaddr.reset(new HWAddr(hwaddr_buffer_, hwaddr_length_, hwtype_));
            hwaddr->source_ = hwaddr_source_;
        }

        // Create the lease and set the cltt (after converting from the
        // expire time retrieved from the database).
        Lease6Ptr result(new Lease6(type, addr, duid_ptr, iaid_,
                                    pref_lifetime_, valid_lifetime_, 0, 0,
                                    subnet_id_, fqdn_fwd_, fqdn_rev_,
                                    hostname, hwaddr, prefixlen_));
        time_t cltt = 0;
        MySqlLeaseMgr::convertFromDatabaseTime(expire_, valid_lifetime_, cltt);
        result->cltt_ = cltt;

        return (result);
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    std::string getErrorColumns() {
        return (getColumnsInError(error_, columns_, LEASE_COLUMNS));
    }

private:
    // Note: All array lengths are equal to the corresponding variable in the
    // schema.
    // Note: arrays are declared fixed length for speed of creation
    std::string     addr6_;             ///< String form of address
    char            addr6_buffer_[ADDRESS6_TEXT_MAX_LEN + 1];  ///< Character
                                        ///< array form of V6 address
    unsigned long   addr6_length_;      ///< Length of the address
    MYSQL_BIND      bind_[LEASE_COLUMNS]; ///< Bind array
    std::string     columns_[LEASE_COLUMNS];///< Column names
    std::vector<uint8_t> duid_;         ///< Client identification
    uint8_t         duid_buffer_[DUID::MAX_DUID_LEN]; ///< Buffer form of DUID
    unsigned long   duid_length_;       ///< Length of the DUID
    my_bool         error_[LEASE_COLUMNS]; ///< Error indicators
    MYSQL_TIME      expire_;            ///< Lease expiry time
    uint32_t        iaid_;              ///< Identity association ID
    Lease6Ptr       lease_;             ///< Pointer to lease object
    uint8_t         lease_type_;        ///< Lease type
    uint8_t         prefixlen_;         ///< Prefix length
    uint32_t        pref_lifetime_;     ///< Preferred lifetime
    uint32_t        subnet_id_;         ///< Subnet identification
    uint32_t        valid_lifetime_;    ///< Lease time
    my_bool         fqdn_fwd_;          ///< Has forward DNS update been
                                        ///< performed
    my_bool         fqdn_rev_;          ///< Has reverse DNS update been
                                        ///< performed
    char            hostname_buffer_[HOSTNAME_MAX_LEN];
                                        ///< Client hostname
    unsigned long   hostname_length_;   ///< Client hostname length
    uint8_t         hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
                                        ///< Buffer for Hardware address
    std::vector<uint8_t> hwaddr_;       ///< Hardware address (optional)
    unsigned long   hwaddr_length_;     ///< Aux. variable denoting hwaddr_ size()
    my_bool         hwaddr_null_;       ///< Used when HWAddr is null
    uint16_t        hwtype_;            ///< Hardware type
    uint32_t        hwaddr_source_;     ///< Source of the hardware address
};




// MySqlLeaseMgr Constructor and Destructor

MySqlLeaseMgr::MySqlLeaseMgr(const MySqlConnection::ParameterMap& parameters)
    : MySqlConnection(parameters) {

    // Open the database.
    openDatabase();

    // Enable autocommit.  To avoid a flush to disk on every commit, the global
    // parameter innodb_flush_log_at_trx_commit should be set to 2.  This will
    // cause the changes to be written to the log, but flushed to disk in the
    // background every second.  Setting the parameter to that value will speed
    // up the system, but at the risk of losing data if the system crashes.
    my_bool result = mysql_autocommit(mysql_, 1);
    if (result != 0) {
        isc_throw(DbOperationError, mysql_error(mysql_));
    }

    // Prepare all statements likely to be used.
    prepareStatements(tagged_statements, MySqlLeaseMgr::NUM_STATEMENTS);

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    exchange4_.reset(new MySqlLease4Exchange());
    exchange6_.reset(new MySqlLease6Exchange());
}


MySqlLeaseMgr::~MySqlLeaseMgr() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them? We're destroying this object and are not really concerned
    // with errors on a database connection that is about to go away.)
    for (int i = 0; i < statements_.size(); ++i) {
        if (statements_[i] != NULL) {
            (void) mysql_stmt_close(statements_[i]);
            statements_[i] = NULL;
        }
    }

    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the mysql_ member variable.
}

std::string
MySqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "MySQL backend " << CURRENT_VERSION_VERSION;
    tmp << "." << CURRENT_VERSION_MINOR;
    tmp << ", library " << mysql_get_client_info();
    return (tmp.str());
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
MySqlLeaseMgr::convertToDatabaseTime(const time_t cltt,
                                     const uint32_t valid_lifetime,
                                     MYSQL_TIME& expire) {

    // Calculate expiry time. Store it in the 64-bit value so as we can detect
    // overflows.
    int64_t expire_time_64 = static_cast<int64_t>(cltt) +
        static_cast<int64_t>(valid_lifetime);

    // Even on 64-bit systems MySQL doesn't seem to accept the timestamps
    // beyond the max value of int32_t.
    if (expire_time_64 > LeaseMgr::MAX_DB_TIME) {
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


// Add leases to the database.  The two public methods accept a lease object
// (either V4 of V6), bind the contents to the appropriate prepared
// statement, then call common code to execute the statement.

bool
MySqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              std::vector<MYSQL_BIND>& bind) {

    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(statements_[stindex], &bind[0]);
    checkError(status, stindex, "unable to bind parameters");

    // Execute the statement
    status = mysql_stmt_execute(statements_[stindex]);
    if (status != 0) {

        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (mysql_errno(mysql_) == ER_DUP_ENTRY) {
            return (false);
        }
        checkError(status, stindex, "unable to execute");
    }

    // Insert succeeded
    return (true);
}

bool
MySqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_ADD_ADDR4).arg(lease->addr_.toText());

    // Create the MYSQL_BIND array for the lease
    std::vector<MYSQL_BIND> bind = exchange4_->createBindForSend(lease);

    // ... and drop to common code.
    return (addLeaseCommon(INSERT_LEASE4, bind));
}

bool
MySqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_ADD_ADDR6).arg(lease->addr_.toText())
              .arg(lease->type_);

    // Create the MYSQL_BIND array for the lease
    std::vector<MYSQL_BIND> bind = exchange6_->createBindForSend(lease);

    // ... and drop to common code.
    return (addLeaseCommon(INSERT_LEASE6, bind));
}

// Extraction of leases from the database.
//
// All getLease() methods ultimately call getLeaseCollection().  This
// binds the input parameters passed to it with the appropriate prepared
// statement and executes the statement.  It then gets the results from the
// database.  getlease() methods that expect a single result back call it
// with the "single" parameter set true: this causes an exception to be
// generated if multiple records can be retrieved from the result set. (Such
// an occurrence either indicates corruption in the database, or that an
// assumption that a query can only return a single record is incorrect.)
// Methods that require a collection of records have "single" set to the
// default value of false.  The logic is the same for both Lease4 and Lease6
// objects,  so the code is templated.
//
// Methods that require a collection of objects access this method through
// two interface methods (also called getLeaseCollection()).  These are
// short enough as to be defined in the header file: all they do is to supply
// the appropriate MySqlLeaseXExchange object depending on the type of the
// LeaseCollection objects passed to them.
//
// Methods that require a single object to be returned access the method
// through two interface methods (called getLease()).  As well as supplying
// the appropriate exchange object, they convert between lease collection
// holding zero or one leases into an appropriate Lease object.

template <typename Exchange, typename LeaseCollection>
void MySqlLeaseMgr::getLeaseCollection(StatementIndex stindex,
                                       MYSQL_BIND* bind,
                                       Exchange& exchange,
                                       LeaseCollection& result,
                                       bool single) const {

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(statements_[stindex], bind);
    checkError(status, stindex, "unable to bind WHERE clause parameter");

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange->createBindForReceive();
    status = mysql_stmt_bind_result(statements_[stindex], &outbind[0]);
    checkError(status, stindex, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(statements_[stindex]);
    checkError(status, stindex, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(statements_[stindex]);
    int count = 0;
    while ((status = mysql_stmt_fetch(statements_[stindex])) == 0) {
        try {
            result.push_back(exchange->getLeaseData());

        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      text_statements_[stindex] << ">");
        }

        if (single && (++count > 1)) {
            isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << text_statements_[stindex]);
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, stindex, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, text_statements_[stindex]
                  << " returned truncated data: columns affected are "
                  << exchange->getErrorColumns());
    }
}


void MySqlLeaseMgr::getLease(StatementIndex stindex, MYSQL_BIND* bind,
                             Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" paraeter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(stindex, bind, exchange4_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}


void MySqlLeaseMgr::getLease(StatementIndex stindex, MYSQL_BIND* bind,
                             Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" paraeter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(stindex, bind, exchange6_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}


// Basic lease access methods.  Obtain leases from the database using various
// criteria.

Lease4Ptr
MySqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_ADDR4).arg(addr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    uint32_t addr4 = static_cast<uint32_t>(addr);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&addr4);
    inbind[0].is_unsigned = MLM_TRUE;

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, inbind, result);

    return (result);
}


Lease4Collection
MySqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_HWADDR).arg(hwaddr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    // As "buffer" is "char*" - even though the data is being read - we need
    // to cast away the "const"ness as well as reinterpreting the data as
    // a "char*". (We could avoid the "const_cast" by copying the data to a
    // local variable, but as the data is only being read, this introduces
    // an unnecessary copy).
    unsigned long hwaddr_length = hwaddr.hwaddr_.size();
    uint8_t* data = const_cast<uint8_t*>(&hwaddr.hwaddr_[0]);

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(data);
    inbind[0].buffer_length = hwaddr_length;
    inbind[0].length = &hwaddr_length;

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, inbind, result);

    return (result);
}


Lease4Ptr
MySqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SUBID_HWADDR)
        .arg(subnet_id).arg(hwaddr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // As "buffer" is "char*" - even though the data is being read - we need
    // to cast away the "const"ness as well as reinterpreting the data as
    // a "char*". (We could avoid the "const_cast" by copying the data to a
    // local variable, but as the data is only being read, this introduces
    // an unnecessary copy).
    unsigned long hwaddr_length = hwaddr.hwaddr_.size();
    uint8_t* data = const_cast<uint8_t*>(&hwaddr.hwaddr_[0]);

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(data);
    inbind[0].buffer_length = hwaddr_length;
    inbind[0].length = &hwaddr_length;

    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[1].is_unsigned = MLM_TRUE;

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, inbind, result);

    return (result);
}


Lease4Collection
MySqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_CLIENTID).arg(clientid.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    std::vector<uint8_t> client_data = clientid.getClientId();
    unsigned long client_data_length = client_data.size();
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&client_data[0]);
    inbind[0].buffer_length = client_data_length;
    inbind[0].length = &client_data_length;

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, inbind, result);

    return (result);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const ClientId&, const HWAddr&, SubnetID) const {
    /// This function is currently not implemented because allocation engine
    /// searches for the lease using HW address or client identifier.
    /// It never uses both parameters in the same time. We need to
    /// consider if this function is needed at all.
    isc_throw(NotImplemented, "The MySqlLeaseMgr::getLease4 function was"
              " called, but it is not implemented");
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_SUBID_CLIENTID)
              .arg(subnet_id).arg(clientid.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    std::vector<uint8_t> client_data = clientid.getClientId();
    unsigned long client_data_length = client_data.size();
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&client_data[0]);
    inbind[0].buffer_length = client_data_length;
    inbind[0].length = &client_data_length;

    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[1].is_unsigned = MLM_TRUE;

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, inbind, result);

    return (result);
}


Lease6Ptr
MySqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_ADDR6).arg(addr.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    std::string addr6 = addr.toText();
    unsigned long addr6_length = addr6.size();

    // See the earlier description of the use of "const_cast" when accessing
    // the address for an explanation of the reason.
    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(addr6.c_str());
    inbind[0].buffer_length = addr6_length;
    inbind[0].length = &addr6_length;

    // LEASE_TYPE
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&lease_type);
    inbind[1].is_unsigned = MLM_TRUE;

    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, inbind, result);

    return (result);
}


Lease6Collection
MySqlLeaseMgr::getLeases6(Lease::Type lease_type,
                          const DUID& duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_IAID_DUID).arg(iaid).arg(duid.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // In the following statement, the DUID is being read.  However, the
    // MySQL C interface does not use "const", so the "buffer" element
    // is declared as "char*" instead of "const char*".  To resolve this,
    // the "const" is discarded before the uint8_t* is cast to char*.
    //
    // Note that the const_cast could be avoided by copying the DUID to
    // a writeable buffer and storing the address of that in the "buffer"
    // element.  However, this introduces a copy operation (with additional
    // overhead) purely to get round the structures introduced by design of
    // the MySQL interface (which uses the area pointed to by "buffer" as
    // input when specifying query parameters and as output when retrieving
    // data).  For that reason, "const_cast" has been used.
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
    inbind[1].is_unsigned = MLM_TRUE;

    // LEASE_TYPE
    inbind[2].buffer_type = MYSQL_TYPE_TINY;
    inbind[2].buffer = reinterpret_cast<char*>(&lease_type);
    inbind[2].is_unsigned = MLM_TRUE;

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, inbind, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6(Lease::Type lease_type,
                          const DUID& duid, uint32_t iaid,
                          SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_IAID_SUBID_DUID)
              .arg(iaid).arg(subnet_id).arg(duid.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[4];
    memset(inbind, 0, sizeof(inbind));

    // See the earlier description of the use of "const_cast" when accessing
    // the DUID for an explanation of the reason.
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
    inbind[1].is_unsigned = MLM_TRUE;

    // Subnet ID
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[2].is_unsigned = MLM_TRUE;

    // LEASE_TYPE
    inbind[3].buffer_type = MYSQL_TYPE_TINY;
    inbind[3].buffer = reinterpret_cast<char*>(&lease_type);
    inbind[3].is_unsigned = MLM_TRUE;

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, inbind, result);

    return (result);
}

// Update lease methods.  These comprise common code that handles the actual
// update, and type-specific methods that set up the parameters for the prepared
// statement depending on the type of lease.

template <typename LeasePtr>
void
MySqlLeaseMgr::updateLeaseCommon(StatementIndex stindex, MYSQL_BIND* bind,
                                 const LeasePtr& lease) {

    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(statements_[stindex], bind);
    checkError(status, stindex, "unable to bind parameters");

    // Execute
    status = mysql_stmt_execute(statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // See how many rows were affected.  The statement should only update a
    // single row.
    int affected_rows = mysql_stmt_affected_rows(statements_[stindex]);
    if (affected_rows == 0) {
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_ << " as it does not exist");
    } else if (affected_rows > 1) {
        // Should not happen - primary key constraint should only have selected
        // one row.
        isc_throw(DbOperationError, "apparently updated more than one lease "
                  "that had the address " << lease->addr_);
    }
}


void
MySqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_UPDATE_ADDR4).arg(lease->addr_.toText());

    // Create the MYSQL_BIND array for the data being updated
    std::vector<MYSQL_BIND> bind = exchange4_->createBindForSend(lease);

    // Set up the WHERE clause and append it to the MYSQL_BIND array
    MYSQL_BIND where;
    memset(&where, 0, sizeof(where));

    uint32_t addr4 = static_cast<uint32_t>(lease->addr_);
    where.buffer_type = MYSQL_TYPE_LONG;
    where.buffer = reinterpret_cast<char*>(&addr4);
    where.is_unsigned = MLM_TRUE;
    bind.push_back(where);

    // Drop to common update code
    updateLeaseCommon(stindex, &bind[0], lease);
}


void
MySqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_UPDATE_ADDR6).arg(lease->addr_.toText())
              .arg(lease->type_);

    // Create the MYSQL_BIND array for the data being updated
    std::vector<MYSQL_BIND> bind = exchange6_->createBindForSend(lease);

    // Set up the WHERE clause value
    MYSQL_BIND where;
    memset(&where, 0, sizeof(where));

    std::string addr6 = lease->addr_.toText();
    unsigned long addr6_length = addr6.size();

    // See the earlier description of the use of "const_cast" when accessing
    // the address for an explanation of the reason.
    where.buffer_type = MYSQL_TYPE_STRING;
    where.buffer = const_cast<char*>(addr6.c_str());
    where.buffer_length = addr6_length;
    where.length = &addr6_length;
    bind.push_back(where);

    // Drop to common update code
    updateLeaseCommon(stindex, &bind[0], lease);
}

// Delete lease methods.  Similar to other groups of methods, these comprise
// a per-type method that sets up the relevant MYSQL_BIND array (in this
// case, a single method for both V4 and V6 addresses) and a common method that
// handles the common processing.

bool
MySqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex, MYSQL_BIND* bind) {

    // Bind the input parameters to the statement
    int status = mysql_stmt_bind_param(statements_[stindex], bind);
    checkError(status, stindex, "unable to bind WHERE clause parameter");

    // Execute
    status = mysql_stmt_execute(statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // See how many rows were affected.  Note that the statement may delete
    // multiple rows.
    return (mysql_stmt_affected_rows(statements_[stindex]) > 0);
}


bool
MySqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_DELETE_ADDR).arg(addr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    if (addr.isV4()) {
        uint32_t addr4 = static_cast<uint32_t>(addr);

        inbind[0].buffer_type = MYSQL_TYPE_LONG;
        inbind[0].buffer = reinterpret_cast<char*>(&addr4);
        inbind[0].is_unsigned = MLM_TRUE;

        return (deleteLeaseCommon(DELETE_LEASE4, inbind));

    } else {
        std::string addr6 = addr.toText();
        unsigned long addr6_length = addr6.size();

        // See the earlier description of the use of "const_cast" when accessing
        // the address for an explanation of the reason.
        inbind[0].buffer_type = MYSQL_TYPE_STRING;
        inbind[0].buffer = const_cast<char*>(addr6.c_str());
        inbind[0].buffer_length = addr6_length;
        inbind[0].length = &addr6_length;

        return (deleteLeaseCommon(DELETE_LEASE6, inbind));
    }
}

// Miscellaneous database methods.

std::string
MySqlLeaseMgr::getName() const {
    std::string name = "";
    try {
        name = getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}


std::string
MySqlLeaseMgr::getDescription() const {
    return (std::string("MySQL Database"));
}


std::pair<uint32_t, uint32_t>
MySqlLeaseMgr::getVersion() const {
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
MySqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
    if (mysql_commit(mysql_) != 0) {
        isc_throw(DbOperationError, "commit failed: " << mysql_error(mysql_));
    }
}


void
MySqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
    if (mysql_rollback(mysql_) != 0) {
        isc_throw(DbOperationError, "rollback failed: " << mysql_error(mysql_));
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
