// Copyright (C) 2015 - 2016 Deutsche Telekom AG.
//
// Author: Razvan Becheriu <razvan.becheriu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/cql_lease_mgr.h>
#include <boost/static_assert.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace dhcp {

static const size_t HOSTNAME_MAX_LEN = 255;
static const size_t ADDRESS6_TEXT_MAX_LEN = 39;

static CassError CqlBindNone(CassStatement* statement, size_t index, void*) {
    return cass_statement_bind_null(statement, index);
}

static CassError CqlBindBool(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_bool(statement, index, *(static_cast<cass_bool_t*>(value)));
}

static CassError CqlBindInt32(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_int32(statement, index, *(static_cast<cass_int32_t*>(value)));
}

static CassError CqlBindInt64(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_int64(statement, index, *(static_cast<cass_int64_t*>(value)));
}

static CassError CqlBindTimestamp(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_int64(statement, index, *(static_cast<cass_int64_t*>(value)));
}

static CassError CqlBindString(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_string(statement, index, (static_cast<const char*>(value)));
}

static CassError CqlBindBytes(CassStatement* statement, size_t index, void* value) {
    return cass_statement_bind_bytes(statement, index, &(*(static_cast<std::vector<cass_byte_t>*>(value)))[0],
            static_cast<std::vector<cass_byte_t>*>(value)->size());
}

static CassError (*CqlBindFunctions[])(CassStatement* statement, size_t index, void* value) = {
    CqlBindNone,
    CqlBindBool,
    CqlBindInt32,
    CqlBindInt64,
    CqlBindTimestamp,
    CqlBindString,
    CqlBindBytes
};

struct ColumnInfo {
    ColumnInfo () : column_(NULL), type_(CQL_DATA_TYPE_NONE) {}
    ColumnInfo (const char *column, CqlDataType type) : column_(column), type_(type) {}
    const char* column_;
    CqlDataType type_;
};

/// @brief Catalog of all the SQL statements currently supported.  Note
/// that the order columns appear in statement body must match the order they
/// that the occur in the table.  This does not apply to the where clause.

static const char* delete_lease4_params[] = {
        static_cast<const char*>("address"),
        NULL };
static const char* delete_expired_lease4_params[] = {
        static_cast<const char*>("state"),
        static_cast<const char*>("expire"),
        NULL };
static const char* delete_lease6_params[] = {
        static_cast<const char*>("address"),
        NULL };
static const char* delete_expired_lease6_params[] = {
        static_cast<const char*>("state"),
        static_cast<const char*>("expire"),
        NULL };
static const char* get_lease4_addr_params[] = {
        static_cast<const char*>("address"),
        NULL };
static const char* get_lease4_clientid_params[] = {
        static_cast<const char*>("client_id"),
        NULL };
static const char* get_lease4_clientid_subid_params[] = {
        static_cast<const char*>("client_id"),
        static_cast<const char*>("subnet_id"),
        NULL };
static const char* get_lease4_hwaddr_params[] = {
        static_cast<const char*>("hwaddr"),
        NULL };
static const char* get_lease4_hwaddr_subid_params[] = {
        static_cast<const char*>("hwaddr"),
        static_cast<const char*>("subnet_id"),
        NULL };
static const char* get_lease4_expired_params[] = {
        static_cast<const char*>("state"),
        static_cast<const char*>("expire"),
        static_cast<const char*>("limit"),
        NULL };
static const char* get_lease6_addr_params[] = {
        static_cast<const char*>("address"),
        static_cast<const char*>("lease_type"),
        NULL };
static const char* get_lease6_duid_iaid_params[] = {
        static_cast<const char*>("duid"),
        static_cast<const char*>("iaid"),
        static_cast<const char*>("lease_type"),
        NULL };
static const char* get_lease6_duid_iaid_subid_params[] = {
        static_cast<const char*>("duid"),
        static_cast<const char*>("iaid"),
        static_cast<const char*>("subnet_id"),
        static_cast<const char*>("lease_type"),
        NULL };
static const char* get_lease6_expired_params[] = {
        static_cast<const char*>("state"),
        static_cast<const char*>("expire"),
        static_cast<const char*>("limit"),
        NULL };
static const char* get_version_params[] = {
        static_cast<const char*>("version"),
        NULL };
static const char* insert_lease4_params[] = {
        static_cast<const char*>("address"),
        static_cast<const char*>("hwaddr"),
        static_cast<const char*>("client_id"),
        static_cast<const char*>("valid_lifetime"),
        static_cast<const char*>("expire"),
        static_cast<const char*>("subnet_id"),
        static_cast<const char*>("fqdn_fwd"),
        static_cast<const char*>("fqdn_rev"),
        static_cast<const char*>("hostname"),
        static_cast<const char*>("state"),
        NULL };
static const char* insert_lease6_params[] = {
        static_cast<const char*>("address"),
        static_cast<const char*>("duid"),
        static_cast<const char*>("valid_lifetime"),
        static_cast<const char*>("expire"),
        static_cast<const char*>("subnet_id"),
        static_cast<const char*>("pref_lifetime"),
        static_cast<const char*>("lease_type"),
        static_cast<const char*>("iaid"),
        static_cast<const char*>("prefix_len"),
        static_cast<const char*>("fqdn_fwd"),
        static_cast<const char*>("fqdn_rev"),
        static_cast<const char*>("hostname"),
        static_cast<const char*>("hwaddr"),
        static_cast<const char*>("hwtype"),
        static_cast<const char*>("hwaddr_source"),
        static_cast<const char*>("state"),
        NULL };
static const char* update_lease4_params[] = {
        static_cast<const char*>("hwaddr"),
        static_cast<const char*>("client_id"),
        static_cast<const char*>("valid_lifetime"),
        static_cast<const char*>("expire"),
        static_cast<const char*>("subnet_id"),
        static_cast<const char*>("fqdn_fwd"),
        static_cast<const char*>("fqdn_rev"),
        static_cast<const char*>("hostname"),
        static_cast<const char*>("state"),
        static_cast<const char*>("address"),
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
        static_cast<const char*>("expire"),
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
        NULL };
static const char* update_lease6_params[] = {
        static_cast<const char*>("duid"),
        static_cast<const char*>("valid_lifetime"),
        static_cast<const char*>("expire"),
        static_cast<const char*>("subnet_id"),
        static_cast<const char*>("pref_lifetime"),
        static_cast<const char*>("lease_type"),
        static_cast<const char*>("iaid"),
        static_cast<const char*>("prefix_len"),
        static_cast<const char*>("fqdn_fwd"),
        static_cast<const char*>("fqdn_rev"),
        static_cast<const char*>("hostname"),
        static_cast<const char*>("hwaddr"),
        static_cast<const char*>("hwtype"),
        static_cast<const char*>("hwaddr_source"),
        static_cast<const char*>("state"),
        static_cast<const char*>("address"),
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
        static_cast<const char*>("expire"),
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
        NULL };

CqlTaggedStatement CqlLeaseMgr::tagged_statements_[] = {
    // DELETE_LEASE4
    { delete_lease4_params,
      "delete_lease4",
      "DELETE FROM lease4 WHERE address = ?" },

    // DELETE_LEASE4_STATE_EXPIRED
    { delete_expired_lease4_params,
      "delete_lease4_expired",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE state = ? AND expire < ? ALLOW FILTERING" },

    // DELETE_LEASE6
    { delete_lease6_params,
      "delete_lease6",
      "DELETE FROM lease6 WHERE address = ?" },

    // DELETE_LEASE6_STATE_EXPIRED
    { delete_expired_lease6_params,
      "delete_lease6_expired",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE state = ? AND expire < ? ALLOW FILTERING" },

    // GET_LEASE4_ADDR
    { get_lease4_addr_params,
      "get_lease4_addr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE address = ?" },

    // GET_LEASE4_CLIENTID
    { get_lease4_clientid_params,
      "get_lease4_clientid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE client_id = ?" },

    // GET_LEASE4_CLIENTID_SUBID
    { get_lease4_clientid_subid_params,
      "get_lease4_clientid_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE client_id = ? AND subnet_id = ? ALLOW FILTERING" },

    // GET_LEASE4_HWADDR
    { get_lease4_hwaddr_params,
      "get_lease4_hwaddr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE hwaddr = ?" },

    // GET_LEASE4_HWADDR_SUBID
    { get_lease4_hwaddr_subid_params,
      "get_lease4_hwaddr_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE hwaddr = ? AND subnet_id = ? ALLOW FILTERING" },

    // GET_LEASE4_EXPIRE
    { get_lease4_expired_params,
      "get_lease4_expired",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      //"WHERE state != ? AND expire < ? ORDER BY expire ASC "
      "WHERE state = ? AND expire < ? "
      "LIMIT ? ALLOW FILTERING" },

    // GET_LEASE6_ADDR
    { get_lease6_addr_params,
      "get_lease6_addr",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE address = ? AND lease_type = ? ALLOW FILTERING" },

    // GET_LEASE6_DUID_IAID
    { get_lease6_duid_iaid_params,
       "get_lease6_duid_iaid",
       "SELECT address, duid, valid_lifetime, "
         "expire, subnet_id, pref_lifetime, "
         "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
         "hwaddr, hwtype, hwaddr_source, state "
       "FROM lease6 "
       "WHERE duid = ? AND iaid = ? AND lease_type = ? ALLOW FILTERING" },

    // GET_LEASE6_DUID_IAID_SUBID
    { get_lease6_duid_iaid_subid_params,
      "get_lease6_duid_iaid_subid",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE duid = ? AND iaid = ? AND subnet_id = ? AND lease_type = ? ALLOW FILTERING" },

    // GET_LEASE6_EXPIRE
    { get_lease6_expired_params,
      "get_lease6_expired",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      //"WHERE state != ? AND expire < ? ORDER BY expire ASC "
      "WHERE state = ? AND expire < ? "
      "LIMIT ? ALLOW FILTERING" },

    // GET_VERSION
    { get_version_params,
      "get_version",
      "SELECT version, minor FROM schema_version" },

    // INSERT_LEASE4
    { insert_lease4_params,
      "insert_lease4",
      "INSERT INTO lease4(address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname, state) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
      "IF NOT EXISTS"
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    },

    // INSERT_LEASE6
    { insert_lease6_params,
      "insert_lease6",
      "INSERT INTO lease6(address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, hwaddr_source, state) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
      "IF NOT EXISTS"
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    },

    // UPDATE_LEASE4
    { update_lease4_params,
      "update_lease4",
      "UPDATE lease4 SET hwaddr = ?, "
        "client_id = ?, valid_lifetime = ?, expire = ?, "
        "subnet_id = ?, fqdn_fwd = ?, fqdn_rev = ?, hostname = ?, state = ? "
      "WHERE address = ? "
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
      "IF expire = ?"
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    },

    // UPDATE_LEASE6
    { update_lease6_params,
      "update_lease6",
      "UPDATE lease6 SET duid = ?, "
        "valid_lifetime = ?, expire = ?, subnet_id = ?, "
        "pref_lifetime = ?, lease_type = ?, iaid = ?, "
        "prefix_len = ?, fqdn_fwd = ?, fqdn_rev = ?, hostname = ?, "
        "hwaddr = ?, hwtype = ?, hwaddr_source = ?, state = ? "
      "WHERE address = ? "
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
      "IF expire = ?"
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    },

    // End of list sentinel
    { NULL, NULL, NULL }
};


/// @brief Common CQL and Lease Data Methods
///
/// The CqlLease4Exchange and CqlLease6Exchange classes provide the
/// functionality to set up binding information between variables in the
/// program and data extracted from the database.  This class is the common
/// base to both of them, containing some common methods.

class CqlLeaseExchange {
public:
    CqlLeaseExchange() : hwaddr_length_(0), expire_(0),
                            subnet_id_(0), valid_lifetime_(0),
                            fqdn_fwd_(false), fqdn_rev_(false), hostname_length_(0), state_(0) {
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(hostname_buffer_, 0, sizeof(hostname_buffer_));
    }
    // Time conversion methods.
    static void
    convertToDatabaseTime(const time_t& cltt,
                                             const uint32_t& valid_lifetime,
                                             uint64_t& expire) {
        // Calculate expiry time. Store it in the 64-bit value so as we can detect
        // overflows.
        int64_t expire_time = static_cast<int64_t>(cltt) +
            static_cast<int64_t>(valid_lifetime);

        if (expire_time > DatabaseConnection::MAX_DB_TIME) {
            isc_throw(BadValue, "Time value is too large: " << expire_time);
        }

        expire = expire_time;
    }

    static void
    convertFromDatabaseTime(const uint64_t& expire,
                                           const uint32_t& valid_lifetime,
                                           time_t& cltt) {
        // Convert to local time
        cltt = expire - static_cast<int64_t>(valid_lifetime);
    }

    std::vector<ColumnInfo> columns_;   ///< Column names and types
protected:
    std::vector<uint8_t> hwaddr_;       ///< Hardware address
    uint8_t         hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
                                        ///< Hardware address buffer
    unsigned long   hwaddr_length_;     ///< Hardware address length
    uint64_t        expire_;            ///< Lease expiry time
    uint32_t        subnet_id_;         ///< Subnet identification
    uint64_t        valid_lifetime_;    ///< Lease time
    uint32_t        fqdn_fwd_;          ///< Has forward DNS update been
                                        ///< performed
    uint32_t        fqdn_rev_;          ///< Has reverse DNS update been
                                        ///< performed
    char            hostname_buffer_[HOSTNAME_MAX_LEN];
                                        ///< Client hostname
    unsigned long   hostname_length_;   ///< Client hostname length
    uint32_t        state_;             ///< Lease state
};


/// @brief Exchange CQL and Lease4 Data
///
/// On any CQL operation, arrays of CQL BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the CQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all CqlLeaseMgr::xxx4() calls where it is used.

class CqlLease4Exchange : public CqlLeaseExchange {
public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    CqlLease4Exchange() : addr4_(0), client_id_length_(0),
                            client_id_null_(false) {
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));

        // Set the column names (for error messages)
        uint32_t size;
        uint32_t offset = 0;
        size = 12;
        columns_.resize(size);
        columns_[offset++] = ColumnInfo("address", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("hwaddr", CQL_DATA_TYPE_BYTES);
        columns_[offset++] = ColumnInfo("client_id", CQL_DATA_TYPE_BYTES);
        columns_[offset++] = ColumnInfo("valid_lifetime", CQL_DATA_TYPE_INT64);
        columns_[offset++] = ColumnInfo("expire", CQL_DATA_TYPE_TIMESTAMP);
        columns_[offset++] = ColumnInfo("subnet_id", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("fqdn_fwd", CQL_DATA_TYPE_BOOL);
        columns_[offset++] = ColumnInfo("fqdn_rev", CQL_DATA_TYPE_BOOL);
        columns_[offset++] = ColumnInfo("hostname", CQL_DATA_TYPE_STRING);
        columns_[offset++] = ColumnInfo("state", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("limit", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("version", CQL_DATA_TYPE_NONE);
    }

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease4 object to
    /// the database.
    void createBindForSend(const Lease4Ptr& lease, CqlBindArray& bind_array) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease4 object is NULL");
        }
        // Store lease object to ensure it remains valid.
        lease_ = lease;
        // Set up the structures for the various components of the lease4
        // structure.

        try {
            // address: uint32_t
            // The address in the Lease structure is an IOAddress object.  Convert
            // this to an integer for storage.
            addr4_ = static_cast<uint32_t>(lease_->addr_);
            bind_array.add(&addr4_);

            hwaddr_ = lease_->hwaddr_->hwaddr_;
            hwaddr_length_ = hwaddr_.size();
            bind_array.add(&hwaddr_);

            // client_id: varbinary(128)
            if (lease_->client_id_) {
                client_id_ = lease_->client_id_->getClientId();
            } else {
                client_id_.clear();
            }
            client_id_length_ = client_id_.size();
            bind_array.add(&client_id_);

            // valid lifetime: unsigned int
            valid_lifetime_ = lease_->valid_lft_;
            bind_array.add(&valid_lifetime_);
            // expire: timestamp
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            CqlLeaseExchange::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_, expire_);
            bind_array.add(&expire_);

            // subnet_id: unsigned int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            subnet_id_ = lease_->subnet_id_;
            bind_array.add(&subnet_id_);

            // fqdn_fwd: boolean
            fqdn_fwd_ = lease_->fqdn_fwd_;
            bind_array.add(&fqdn_fwd_);

            // fqdn_rev: boolean
            fqdn_rev_ = lease_->fqdn_rev_;
            bind_array.add(&fqdn_rev_);

            // hostname: varchar(255)
            hostname_length_  = lease_->hostname_.length();
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " << lease_->hostname_.c_str());
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, lease_->hostname_.c_str(), hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';
            bind_array.add(hostname_buffer_);

            // state: uint32_t
            state_ = lease_->state_;
            bind_array.add(&state_);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a CQL_BIND array to receive Lease4 data from the database.
    Lease4Ptr createBindForReceive(const CassRow* row) {
        try {
            const CassValue* value;
            unsigned char* buffer = NULL;
            const char* text_buffer = NULL;

            // address: uint32_t
            value = cass_row_get_column_by_name(row, columns_[0].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&addr4_));

            // hwaddr: varbinary(20)
            value = cass_row_get_column_by_name(row, columns_[1].column_);
            cass_value_get_bytes(value, const_cast<const cass_byte_t**>(&buffer), &hwaddr_length_);
            hwaddr_.assign(buffer, buffer + hwaddr_length_);

            // client_id: varbinary(128)
            value = cass_row_get_column_by_name(row, columns_[2].column_);
            cass_value_get_string(value, &text_buffer, &client_id_length_);
            client_id_.assign(text_buffer, text_buffer + client_id_length_);
            if (client_id_length_ >= sizeof(client_id_buffer_)) {
                isc_throw(BadValue, "client_id value is too large: " << text_buffer);
            }
            if (client_id_length_) {
                memcpy(client_id_buffer_, text_buffer, client_id_length_);
            }
            client_id_buffer_[client_id_length_] = '\0';

            // lease_time: unsigned int
            value = cass_row_get_column_by_name(row, columns_[3].column_);
            cass_value_get_int64(value, reinterpret_cast<cass_int64_t*>(&valid_lifetime_));

            // expire: timestamp
            value = cass_row_get_column_by_name(row, columns_[4].column_);
            cass_value_get_int64(value, reinterpret_cast<cass_int64_t*>(&expire_));

            // subnet_id: unsigned int
            value = cass_row_get_column_by_name(row, columns_[5].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&subnet_id_));

            // fqdn_fwd: boolean
            value = cass_row_get_column_by_name(row, columns_[6].column_);
            cass_value_get_bool(value, reinterpret_cast<cass_bool_t*>(&fqdn_fwd_));

            // fqdn_rev: boolean
            value = cass_row_get_column_by_name(row, columns_[7].column_);
            cass_value_get_bool(value, reinterpret_cast<cass_bool_t*>(&fqdn_rev_));

            // hostname: varchar(255)
            value = cass_row_get_column_by_name(row, columns_[8].column_);
            cass_value_get_string(value, &text_buffer, &hostname_length_);
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " << text_buffer);
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, text_buffer, hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';

            // state: uint32_t
            value = cass_row_get_column_by_name(row, columns_[9].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&state_));

            time_t cltt = 0;
            CqlLeaseExchange::convertFromDatabaseTime(expire_, valid_lifetime_, cltt);

            // Recreate the hardware address.
            HWAddrPtr hwaddr(new HWAddr(hwaddr_, HTYPE_ETHER));

            std::string hostname(hostname_buffer_,
                                 hostname_buffer_ + hostname_length_);

            Lease4Ptr result(new Lease4(addr4_, hwaddr,
                                                     client_id_buffer_, client_id_length_,
                                                     valid_lifetime_, 0, 0, cltt,
                                                     subnet_id_, fqdn_fwd_, fqdn_rev_,
                                                     hostname));

            result->state_ = state_;

            return (result);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not convert data to Lease4, reason: "
                       << ex.what());
        }
        return (Lease4Ptr());
    }

private:

    // Note: All array lengths are equal to the corresponding variable in the
    //       schema.
    // Note: Arrays are declared fixed length for speed of creation
    Lease4Ptr       lease_;             ///< Pointer to lease object
    uint32_t        addr4_;             ///< IPv4 address
    std::vector<uint8_t> client_id_;    ///< Client identification
    uint8_t         client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
                                        ///< Client ID buffer
    unsigned long   client_id_length_;  ///< Client ID address length
    bool            client_id_null_;    ///< Is Client ID null?
};



/// @brief Exchange CQL and Lease6 Data
///
/// On any CQL operation, arrays of CQL BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the CQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all CqlLeaseMgr::xxx6() calls where it is used.

class CqlLease6Exchange : public CqlLeaseExchange {
public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is nonly to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    CqlLease6Exchange() : addr6_length_(0), duid_length_(0),
                            iaid_(0), lease_type_(0), prefixlen_(0),
                            pref_lifetime_(0), hwaddr_null_(false), hwtype_(0),
                            hwaddr_source_(0) {
        memset(addr6_buffer_, 0, sizeof(addr6_buffer_));
        memset(duid_buffer_, 0, sizeof(duid_buffer_));

        // Set the column names (for error messages)
        uint32_t size;
        uint32_t offset = 0;
        size = 18;
        columns_.resize(size);
        columns_[offset++] = ColumnInfo("address", CQL_DATA_TYPE_STRING);
        columns_[offset++] = ColumnInfo("duid", CQL_DATA_TYPE_BYTES);
        columns_[offset++] = ColumnInfo("valid_lifetime", CQL_DATA_TYPE_INT64);
        columns_[offset++] = ColumnInfo("expire", CQL_DATA_TYPE_TIMESTAMP);
        columns_[offset++] = ColumnInfo("subnet_id", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("pref_lifetime", CQL_DATA_TYPE_INT64);
        columns_[offset++] = ColumnInfo("lease_type", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("iaid", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("prefix_len", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("fqdn_fwd", CQL_DATA_TYPE_BOOL);
        columns_[offset++] = ColumnInfo("fqdn_rev", CQL_DATA_TYPE_BOOL);
        columns_[offset++] = ColumnInfo("hostname", CQL_DATA_TYPE_STRING);
        columns_[offset++] = ColumnInfo("hwaddr", CQL_DATA_TYPE_BYTES);
        columns_[offset++] = ColumnInfo("hwtype", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("hwaddr_source", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("state", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("limit", CQL_DATA_TYPE_INT32);
        columns_[offset++] = ColumnInfo("version", CQL_DATA_TYPE_NONE);
    }

    /// @brief Create CQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease6 object to
    /// the database.
    void createBindForSend(const Lease6Ptr& lease, CqlBindArray& bind_array) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease6 object is NULL");
        }
        // Store lease object to ensure it remains valid.
        lease_ = lease;
        // Set up the structures for the various components of the lease4
        // structure.

        try {
            // address: varchar(39)
            std::string text_buffer = lease_->addr_.toText();
            addr6_length_ = text_buffer.size();
            if (addr6_length_ >= sizeof(addr6_buffer_)) {
                isc_throw(BadValue, "address value is too large: " << text_buffer);
            }
            if (addr6_length_) {
                memcpy(addr6_buffer_, text_buffer.c_str(), addr6_length_);
            }
            addr6_buffer_[addr6_length_] = '\0';
            bind_array.add(addr6_buffer_);

            // duid: varchar(128)
            if (!lease_->duid_) {
                isc_throw(DbOperationError, "lease6 for address " << addr6_buffer_
                          << " is missing mandatory client-id.");
            }
            duid_ = lease_->duid_->getDuid();
            duid_length_ = duid_.size();
            bind_array.add(&duid_);

            // valid lifetime: unsigned int
            valid_lifetime_ = lease_->valid_lft_;
            bind_array.add(&valid_lifetime_);

            // expire: timestamp
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            CqlLeaseExchange::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_, expire_);
            bind_array.add(&expire_);

            // subnet_id: unsigned int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            subnet_id_ = lease_->subnet_id_;
            bind_array.add(&subnet_id_);

            // pref_lifetime: unsigned int
            // Can use lease_->preferred_lft_ directly as it is of type uint32_t.
            pref_lifetime_ = lease_->preferred_lft_;
            bind_array.add(&pref_lifetime_);

            // lease_type: tinyint
            // Must convert to uint8_t as lease_->type_ is a LeaseType variable.
            lease_type_ = lease_->type_;
            bind_array.add(&lease_type_);

            // iaid: unsigned int
            // Can use lease_->iaid_ directly as it is of type uint32_t.
            iaid_ = lease_->iaid_;
            bind_array.add(&iaid_);

            // prefix_len: unsigned tinyint
            // Can use lease_->prefixlen_ directly as it is uint32_t.
            prefixlen_ = lease_->prefixlen_;
            bind_array.add(&prefixlen_);

            // fqdn_fwd: boolean
            fqdn_fwd_ = lease_->fqdn_fwd_;
            bind_array.add(&fqdn_fwd_);

            // fqdn_rev: boolean
            fqdn_rev_ = lease_->fqdn_rev_;
            bind_array.add(&fqdn_rev_);

            // hostname: varchar(255)
            hostname_length_  = lease_->hostname_.length();
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " << lease_->hostname_.c_str());
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, lease_->hostname_.c_str(), hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';
            bind_array.add(hostname_buffer_);

            // hwaddr: varbinary(20) - hardware/MAC address
            HWAddrPtr hwaddr = lease_->hwaddr_;
            if (hwaddr) {
                hwaddr_ = hwaddr->hwaddr_;
            } else {
                hwaddr_.clear();
            }
            hwaddr_length_ = hwaddr_.size();
            bind_array.add(&hwaddr_);

            // hwtype
            if (hwaddr) {
                hwtype_ = lease->hwaddr_->htype_;
            } else {
                hwtype_ = 0;
            }
            bind_array.add(&hwtype_);

            /// Hardware source
            if (hwaddr) {
                hwaddr_source_ = lease->hwaddr_->source_;
            } else {
                hwaddr_source_ = 0;
            }
            bind_array.add(&hwaddr_source_);

            // state: uint32_t
            state_ = lease_->state_;
            bind_array.add(&state_);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a CQL_BIND array to receive Lease6 data from the database.
    Lease6Ptr createBindForReceive(const CassRow* row) {
        try {
            const CassValue* value;
            unsigned char* buffer = NULL;
            const char* text_buffer = NULL;

            // address: varchar(39)
            value = cass_row_get_column_by_name(row, columns_[0].column_);
            cass_value_get_string(value, &text_buffer, &addr6_length_);
            if (addr6_length_ >= sizeof(addr6_buffer_)) {
                isc_throw(BadValue, "address value is too large: " << text_buffer);
            }
            if (addr6_length_) {
                memcpy(addr6_buffer_, text_buffer, addr6_length_);
            }
            addr6_buffer_[addr6_length_] = '\0';

            // duid: varbinary(128)
            value = cass_row_get_column_by_name(row, columns_[1].column_);
            cass_value_get_bytes(value, const_cast<const cass_byte_t**>(&buffer), &duid_length_);
            duid_.assign(buffer, buffer + duid_length_);

            // lease_time: unsigned int
            value = cass_row_get_column_by_name(row, columns_[2].column_);
            cass_value_get_int64(value, reinterpret_cast<cass_int64_t*>(&valid_lifetime_));

            // expire: timestamp
            value = cass_row_get_column_by_name(row, columns_[3].column_);
            cass_value_get_int64(value, reinterpret_cast<cass_int64_t*>(&expire_));

            // subnet_id: unsigned int
            value = cass_row_get_column_by_name(row, columns_[4].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&subnet_id_));

            // pref_lifetime: unsigned int
            value = cass_row_get_column_by_name(row, columns_[5].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&pref_lifetime_));

            // lease_type: tinyint
            value = cass_row_get_column_by_name(row, columns_[6].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&lease_type_));

            // iaid: unsigned int
            value = cass_row_get_column_by_name(row, columns_[7].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&iaid_));

            // prefix_len: unsigned tinyint
            value = cass_row_get_column_by_name(row, columns_[8].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&prefixlen_));

            // fqdn_fwd: boolean
            value = cass_row_get_column_by_name(row, columns_[9].column_);
            cass_value_get_bool(value, reinterpret_cast<cass_bool_t*>(&fqdn_fwd_));

            // fqdn_rev: boolean
            value = cass_row_get_column_by_name(row, columns_[10].column_);
            cass_value_get_bool(value, reinterpret_cast<cass_bool_t*>(&fqdn_rev_));

            // hostname: varchar(255)
            value = cass_row_get_column_by_name(row, columns_[11].column_);
            cass_value_get_string(value, &text_buffer, &hostname_length_);
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " << text_buffer);
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, text_buffer, hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';

            // hardware address
            // hwaddr: varbinary(20)
            value = cass_row_get_column_by_name(row, columns_[12].column_);
            cass_value_get_bytes(value, const_cast<const cass_byte_t**>(&buffer), &hwaddr_length_);
            hwaddr_.assign(buffer, buffer + hwaddr_length_);

            // hardware type: unsigned short int (16 bits)
            value = cass_row_get_column_by_name(row, columns_[13].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&hwtype_));

            // hardware source: unsigned int (32 bits)
            value = cass_row_get_column_by_name(row, columns_[14].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&hwaddr_source_));

            // state: uint32_t
            value = cass_row_get_column_by_name(row, columns_[15].column_);
            cass_value_get_int32(value, reinterpret_cast<cass_int32_t*>(&state_));

            if (lease_type_ != Lease::TYPE_NA && lease_type_ != Lease::TYPE_TA &&
                    lease_type_ != Lease::TYPE_PD) {
                isc_throw(BadValue, "invalid lease type returned (" <<
                    static_cast<int>(lease_type_) << ") for lease with "
                    << "address " << addr6_buffer_ << ". Only 0, 1, or 2 are "
                    << "allowed.");
            }

            isc::asiolink::IOAddress addr(addr6_buffer_);
            DuidPtr duid(new DUID(duid_));
            HWAddrPtr hwaddr;
            if (hwaddr_.size()) {
                hwaddr.reset(new HWAddr(hwaddr_, hwtype_));
                hwaddr->source_ = hwaddr_source_;
            }

            std::string hostname(hostname_buffer_,
                                 hostname_buffer_ + hostname_length_);

            // Create the lease and set the cltt (after converting from the
            // expire time retrieved from the database).
            Lease6Ptr result(new Lease6(static_cast<Lease::Type>(lease_type_), addr, duid, iaid_,
                                        pref_lifetime_, valid_lifetime_, 0, 0,
                                        subnet_id_, fqdn_fwd_, fqdn_rev_,
                                        hostname, hwaddr, prefixlen_));

            time_t cltt = 0;
            CqlLeaseExchange::convertFromDatabaseTime(expire_, valid_lifetime_, cltt);
            result->cltt_ = cltt;
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
            result->old_cltt_ = cltt;
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS

            result->state_ = state_;

            return (result);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not convert data to Lease4, reason: "
                       << ex.what());
        }
        return (Lease6Ptr());
    }

private:
    // Note: All array lengths are equal to the corresponding variable in the
    // schema.
    // Note: arrays are declared fixed length for speed of creation
    Lease6Ptr       lease_;             ///< Pointer to lease object
    char            addr6_buffer_[ADDRESS6_TEXT_MAX_LEN + 1];  ///< Character
                                        ///< array form of V6 address
    unsigned long   addr6_length_;      ///< Length of the address
    std::vector<uint8_t> duid_;         ///< Client identification
    uint8_t         duid_buffer_[DUID::MAX_DUID_LEN]; ///< Buffer form of DUID
    unsigned long   duid_length_;       ///< Length of the DUID
    uint32_t        iaid_;              ///< Identity association ID
    uint32_t        lease_type_;        ///< Lease type
    uint32_t        prefixlen_;         ///< Prefix length
    uint32_t        pref_lifetime_;     ///< Preferred lifetime
    bool            hwaddr_null_;       ///< Used when HWAddr is null
    uint32_t        hwtype_;            ///< Hardware type
    uint32_t        hwaddr_source_;     ///< Source of the hardware address
};

#ifdef TERASTREAM_DB_LOGIC
class CqlCustomLeaseExchange : public virtual SqlLeaseExchange {
public:
    CqlCustomLeaseExchange() {}
    virtual ~CqlCustomLeaseExchange() {}
    virtual void executeInternal(LeaseExchangeData& exchange, bool has_allocated_ip, bool has_requested_ip, bool has_reserved_ip) {
        if (has_allocated_ip) {
        }
        if (has_requested_ip) {
        }
        if (has_reserved_ip) {
        }
        if (exchange.in_fake_) {
        }
    }
};

class CqlLease4DiscoverNoReqNoResExchange : public SqlLease4DiscoverNoReqNoResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4DiscoverNoReqNoResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4DiscoverNoReqNoResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, true, false, false);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for discover.
class CqlLease4DiscoverNoReqResExchange : public SqlLease4DiscoverNoReqResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4DiscoverNoReqResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4DiscoverNoReqResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, true, false, true);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for discover.
class CqlLease4DiscoverReqNoResExchange : public SqlLease4DiscoverReqNoResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4DiscoverReqNoResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4DiscoverReqNoResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, true, true, false);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for discover.
class CqlLease4DiscoverReqResExchange : public SqlLease4DiscoverReqResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4DiscoverReqResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4DiscoverReqResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, true, true, true);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for request.
class CqlLease4RequestNoReqNoResExchange : public SqlLease4RequestNoReqNoResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4RequestNoReqNoResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4RequestNoReqNoResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, true, false, false);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for request.
class CqlLease4RequestNoReqResExchange : public SqlLease4RequestNoReqResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4RequestNoReqResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4RequestNoReqResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, false, false, true);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for request.
class CqlLease4RequestReqNoResExchange : public SqlLease4RequestReqNoResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4RequestReqNoResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4RequestReqNoResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, false, true, false);
    }
private:
};

/// @brief Supports exchanging IPv4 leases with SQL for request.
class CqlLease4RequestReqResExchange : public SqlLease4RequestReqResExchange, public CqlCustomLeaseExchange {
public:
    CqlLease4RequestReqResExchange() : CqlCustomLeaseExchange() {}
    virtual ~CqlLease4RequestReqResExchange() {}
    virtual void execute(LeaseExchangeData& exchange) {
        executeInternal(exchange, false, true, true);
    }
private:
};
#endif // TERASTREAM_DB_LOGIC

CqlLeaseMgr::CqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : LeaseMgr(), dbconn_(parameters), exchange4_(new CqlLease4Exchange()),
    exchange6_(new CqlLease6Exchange()) {
    dbconn_.openDatabase();
    dbconn_.prepareStatements(CqlLeaseMgr::tagged_statements_);
}

CqlLeaseMgr::~CqlLeaseMgr() {
}

std::string
CqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "CQL backend " << CQL_CURRENT_VERSION;
    tmp << "." << CQL_CURRENT_MINOR;
    tmp << ", library " << "cassandra_static";
    return (tmp.str());
}


void
CqlLeaseMgr::getDataType(const StatementIndex stindex, int pindex, const CqlLeaseExchange& exchange, CqlDataType& type) {
    if (CqlLeaseMgr::tagged_statements_[stindex].params_ &&
            CqlLeaseMgr::tagged_statements_[stindex].params_[pindex]) {
        for (int i = 0; exchange.columns_.size(); i++) {
            if (!strcmp(CqlLeaseMgr::tagged_statements_[stindex].params_[pindex], exchange.columns_[i].column_)) {
                type = exchange.columns_[i].type_;
                return;
            }
        }
    }
    type = CQL_DATA_TYPE_NONE;
}

void
CqlLeaseMgr::bindData(CassStatement* statement, const StatementIndex stindex, CqlBindArray& bind_array, const CqlLeaseExchange& exchange) {
    if (CqlLeaseMgr::tagged_statements_[stindex].params_ == NULL) {
        return;
    }
    for (int i = 0; CqlLeaseMgr::tagged_statements_[stindex].params_[i]; i++) {
        CqlDataType type;
        CqlLeaseMgr::getDataType(stindex, i, exchange, type);
        CqlBindFunctions[type](statement, i, bind_array.values_[i]);
    }
}

bool
CqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              CqlBindArray& bind_array, CqlLeaseExchange& exchange) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);

    CqlLeaseMgr::bindData(statement, stindex, bind_array, exchange);

    future = cass_session_execute(dbconn_.session_, statement);
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, stindex, "unable to INSERT");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }
    const CassResult* resultCollection = cass_future_get_result(future);
    int row_count = cass_result_row_count(resultCollection);
    int column_count = cass_result_column_count(resultCollection);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);
#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    if (row_count != 1) {
        return (false);
    } else if (column_count != 1) {
        isc_throw(TransactionException, "add transaction failed");
    }
#else
    if (row_count && column_count) {
    }
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS

    return (true);
}

bool
CqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_ADD_ADDR4).arg(lease->addr_.toText());

    CqlBindArray bind_array;
    exchange4_->createBindForSend(lease, bind_array);
    return (addLeaseCommon(INSERT_LEASE4, bind_array, *exchange4_));
}

bool
CqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_ADD_ADDR6).arg(lease->addr_.toText());

    CqlBindArray bind_array;
    exchange6_->createBindForSend(lease, bind_array);
    return (addLeaseCommon(INSERT_LEASE6, bind_array, *exchange6_));
}

template <typename Exchange, typename LeaseCollection>
void CqlLeaseMgr::getLeaseCollection(StatementIndex stindex,
                                       CqlBindArray& bind_array,
                                       Exchange& exchange,
                                       LeaseCollection& result,
                                       bool single) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_ADDR4).arg(dbconn_.tagged_statements_[stindex].name_);

    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;
    const CqlLeaseExchange& leaseExchange = static_cast<CqlLeaseExchange>(*exchange);

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);

    CqlLeaseMgr::bindData(statement, stindex, bind_array, leaseExchange);

    future = cass_session_execute(dbconn_.session_, statement);
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, "unable to GET");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    const CassResult* resultCollection = cass_future_get_result(future);
    CassIterator* rows = cass_iterator_from_result(resultCollection);

    int rowCount = 0;
    while (cass_iterator_next(rows)) {
        rowCount++;
        if (single && rowCount > 1)
        {
            result.clear();
            break;
        }
        const CassRow* row = cass_iterator_get_row(rows);
        result.push_back(exchange->createBindForReceive(row));
    }

    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);
    if (single && rowCount > 1) {
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << dbconn_.tagged_statements_[stindex].name_);
    }
}

void
CqlLeaseMgr::getLease(StatementIndex stindex, CqlBindArray& bind_array,
                             Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(stindex, bind_array, exchange4_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}


void
CqlLeaseMgr::getLease(StatementIndex stindex, CqlBindArray& bind_array,
                             Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(stindex, bind_array, exchange6_, collection, true);

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
CqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_ADDR4).arg(addr.toText());

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    uint32_t addr4_data = static_cast<uint32_t>(addr);
    bind_array.add(&addr4_data);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, bind_array, result);

    return (result);
}


Lease4Collection
CqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_HWADDR).arg(hwaddr.toText());

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::vector<uint8_t>hwaddr_data = hwaddr.hwaddr_;
    bind_array.add(&hwaddr_data);

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, bind_array, result);

    return (result);
}


Lease4Ptr
CqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SUBID_HWADDR)
              .arg(subnet_id).arg(hwaddr.toText());

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::vector<uint8_t>hwaddr_data = hwaddr.hwaddr_;
    bind_array.add(&hwaddr_data);

    uint32_t subnet_id_data = subnet_id;
    bind_array.add(&subnet_id_data);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, bind_array, result);

    return (result);
}


Lease4Collection
CqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_CLIENTID).arg(clientid.toText());

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::vector<uint8_t> client_id_data = clientid.getClientId();
    bind_array.add(&client_id_data);

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, bind_array, result);

    return (result);
}

Lease4Ptr
CqlLeaseMgr::getLease4(const ClientId& clientid, const HWAddr& hwaddr, SubnetID subnet_id) const {
    /// This function is currently not implemented because allocation engine
    /// searches for the lease using HW address or client identifier.
    /// It never uses both parameters in the same time. We need to
    /// consider if this function is needed at all.
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_CLIENTID_HWADDR_SUBID).arg(clientid.toText())
              .arg(hwaddr.toText()).arg(subnet_id);

    isc_throw(NotImplemented, "The CqlLeaseMgr::getLease4 function was"
              " called, but it is not implemented");
}

Lease4Ptr
CqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SUBID_CLIENTID)
              .arg(subnet_id).arg(clientid.toText());

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::vector<uint8_t> client_id_data = clientid.getClientId();
    bind_array.add(&client_id_data);

    uint32_t subnet_id_data = subnet_id;
    bind_array.add(&subnet_id_data);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, bind_array, result);

    return (result);
}


Lease6Ptr
CqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_ADDR6).arg(addr.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::string text_buffer = addr.toText();
    uint32_t addr6_length = text_buffer.size();
    char addr6_buffer[ADDRESS6_TEXT_MAX_LEN + 1];
    if (addr6_length >= sizeof(addr6_buffer)) {
        isc_throw(BadValue, "address value is too large: " << text_buffer);
    }
    if (addr6_length) {
        memcpy(addr6_buffer, text_buffer.c_str(), addr6_length);
    }
    addr6_buffer[addr6_length] = '\0';
    bind_array.add(addr6_buffer);

    uint32_t lease_type_data = lease_type;
    bind_array.add(&lease_type_data);

    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, bind_array, result);

    return (result);
}


Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type,
                          const DUID& duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_IAID_DUID).arg(iaid).arg(duid.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::vector<uint8_t> duid_data = duid.getDuid();
    bind_array.add(&duid_data);

    uint32_t iaid_data = iaid;
    bind_array.add(&iaid_data);

    uint32_t lease_type_data = lease_type;
    bind_array.add(&lease_type_data);

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, bind_array, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type,
                          const DUID& duid, uint32_t iaid,
                          SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_IAID_SUBID_DUID)
              .arg(iaid).arg(subnet_id).arg(duid.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    std::vector<uint8_t> duid_data = duid.getDuid();
    bind_array.add(&duid_data);

    uint32_t iaid_data = iaid;
    bind_array.add(&iaid_data);

    uint32_t subnet_id_data = subnet_id;
    bind_array.add(&subnet_id_data);

    uint32_t lease_type_data = lease_type;
    bind_array.add(&lease_type_data);

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, bind_array, result);

    return (result);
}

void
CqlLeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_EXPIRED6)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE6_EXPIRE);
}

void
CqlLeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_EXPIRED4)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE4_EXPIRE);
}

template<typename LeaseCollection>
void
CqlLeaseMgr::getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                       const size_t max_leases,
                                       StatementIndex statement_index) const {
    // Set up the WHERE clause value
    //"WHERE state != ? AND expire < ? ORDER BY expire ASC "
    uint32_t keepState = Lease::STATE_EXPIRED_RECLAIMED;
    uint64_t timestamp = static_cast<int64_t>(time(NULL));

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    uint32_t limit = max_leases > 0 ? static_cast<uint32_t>(max_leases) :
        std::numeric_limits<uint32_t>::max();

    for (uint32_t state = Lease::STATE_DEFAULT; state <= Lease::STATE_EXPIRED_RECLAIMED; state++) {
        if (state == keepState) {
            continue;
        }
        LeaseCollection tempCollection;
        CqlBindArray bind_array;

        bind_array.add(&state);
        bind_array.add(&timestamp);
        bind_array.add(&limit);

        // Retrieve leases from the database.
        getLeaseCollection(statement_index, bind_array, tempCollection);

        typedef typename LeaseCollection::iterator LeaseCollectionIt;

        for (LeaseCollectionIt it = tempCollection.begin(); it != tempCollection.end(); ++it) {
            expired_leases.push_back((*it));
        }
    }
}

template <typename LeasePtr>
void
CqlLeaseMgr::updateLeaseCommon(StatementIndex stindex,
                                 CqlBindArray& bind_array,
                                 const LeasePtr& lease, CqlLeaseExchange& exchange) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_ADD_ADDR4).arg(dbconn_.tagged_statements_[stindex].name_);

    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);

    CqlLeaseMgr::bindData(statement, stindex, bind_array, exchange);

    future = cass_session_execute(dbconn_.session_, statement);
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, stindex, "unable to UPDATE");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    const CassResult* resultCollection = cass_future_get_result(future);
    int row_count = cass_result_row_count(resultCollection);
    int column_count = cass_result_column_count(resultCollection);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    // Check success case first as it is the most likely outcome.
    if (row_count > 1) {
        // Should not happen - primary key constraint should only have selected
        // one row.
        isc_throw(DbOperationError, "apparently updated more than one lease "
                      "that had the address " << lease->addr_.toText());
    }

    // If no rows affected, lease doesn't exist.
    if (row_count == 0) {
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_.toText() << " as it does not exist");
    }

    if (row_count != 1) {
        isc_throw(DbOperationError, "apparently updated transaction failed for the lease "
                              "that had the address " << lease->addr_.toText());
    } else if (column_count != 1) {
        isc_throw(TransactionException, "update transaction failed");
    }
#else
        if (row_count && column_count && lease) {
        }
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
}


void
CqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_ADDR4).arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    CqlBindArray bind_array;
    exchange4_->createBindForSend(lease, bind_array);
    bind_array.remove(0);

    // Set up the WHERE clause and append it to the SQL_BIND array
    uint32_t addr4_data = static_cast<uint32_t>(lease->addr_);
    bind_array.add(&addr4_data);

#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    uint64_t old_expire;
    CqlLeaseExchange::convertToDatabaseTime(lease->old_cltt_, lease->old_valid_lft_, old_expire);
    bind_array.add(&old_expire);
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS

    // Drop to common update code
    updateLeaseCommon(stindex, bind_array, lease, *exchange4_);
}

void
CqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_ADDR6).arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    CqlBindArray bind_array;
    exchange6_->createBindForSend(lease, bind_array);
    bind_array.remove(0);

    // Set up the WHERE clause and append it to the BIND array
    std::string text_buffer = lease->addr_.toText();
    uint32_t addr6_length = text_buffer.size();
    char addr6_buffer[ADDRESS6_TEXT_MAX_LEN + 1];
    if (addr6_length >= sizeof(addr6_buffer)) {
        isc_throw(BadValue, "address value is too large: " << text_buffer);
    }
    if (addr6_length) {
        memcpy(addr6_buffer, text_buffer.c_str(), addr6_length);
    }
    addr6_buffer[addr6_length] = '\0';
    bind_array.add(addr6_buffer);

#ifdef TERASTREAM_LIGHTWEIGHT_TRANSACTIONS
    uint64_t old_expire;
    CqlLeaseExchange::convertToDatabaseTime(lease->old_cltt_, lease->old_valid_lft_, old_expire);
    bind_array.add(&old_expire);
#endif // TERASTREAM_LIGHTWEIGHT_TRANSACTIONS

    // Drop to common update code
    updateLeaseCommon(stindex, bind_array, lease, *exchange6_);
}

bool
CqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex,
                                 CqlBindArray& bind_array, CqlLeaseExchange& exchange) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);

    CqlLeaseMgr::bindData(statement, stindex, bind_array, exchange);

    future = cass_session_execute(dbconn_.session_, statement);
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, stindex, "unable to DELETE");
    rc = cass_future_error_code(future);
    cass_future_free(future);
    cass_statement_free(statement);
    if (rc != CASS_OK) {
       isc_throw(DbOperationError, error);
    }

    return (true);
}

bool
CqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_ADDR).arg(addr.toText());

    // Set up the WHERE clause value
    CqlBindArray bind_array;

    if (addr.isV4()) {
        uint32_t addr4_data = static_cast<uint32_t>(addr);
        bind_array.add(&addr4_data);
        return (deleteLeaseCommon(DELETE_LEASE4, bind_array, *exchange4_));
    } else {
        std::string text_buffer = addr.toText();
        uint32_t addr6_length = text_buffer.size();
        char addr6_buffer[ADDRESS6_TEXT_MAX_LEN + 1];
        if (addr6_length >= sizeof(addr6_buffer)) {
            isc_throw(BadValue, "address value is too large: " << text_buffer);
        }
        if (addr6_length) {
            memcpy(addr6_buffer, text_buffer.c_str(), addr6_length);
        }
        addr6_buffer[addr6_length] = '\0';
        bind_array.add(addr6_buffer);
        return (deleteLeaseCommon(DELETE_LEASE6, bind_array, *exchange6_));
    }
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE4_STATE_EXPIRED));
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE6_STATE_EXPIRED));
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeasesCommon(const uint32_t secs, StatementIndex statement_index) {
    // Set up the WHERE clause value
    //"WHERE state = ? AND expire < ? ALLOW FILTERING"

    CqlBindArray bind_array;
    uint32_t result = 0;

    // State is reclaimed.
    uint32_t state = Lease::STATE_EXPIRED_RECLAIMED;
    bind_array.add(&state);

    // Expiration timestamp.
    uint64_t expiration = static_cast<int64_t>(time(NULL) - static_cast<time_t>(secs));
    bind_array.add(&expiration);

    // Get the data
    Lease4Collection result4Leases;
    Lease6Collection result6Leases;
    switch (statement_index) {
    case DELETE_LEASE4_STATE_EXPIRED:
        getLeaseCollection(statement_index, bind_array, result4Leases);
        break;
    case DELETE_LEASE6_STATE_EXPIRED:
        getLeaseCollection(statement_index, bind_array, result6Leases);
        break;
    default:
        break;
    }
    for (Lease4Collection::iterator it = result4Leases.begin(); it != result4Leases.end(); ++it) {
        if (deleteLease((*it)->addr_)) {
            result++;
        }
    }
    for (Lease6Collection::iterator it = result6Leases.begin(); it != result6Leases.end(); ++it) {
        if (deleteLease((*it)->addr_)) {
            result++;
        }
    }
    return (result);
}

string
CqlLeaseMgr::getName() const {
    string name = "";
    try {
        name = dbconn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

string
CqlLeaseMgr::getDescription() const {
    return (string("Cassandra Database"));
}

pair<uint32_t, uint32_t>
CqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_VERSION);

    uint32_t version = CASS_VERSION_MAJOR;
    uint32_t minor = CASS_VERSION_MINOR;

    return make_pair<uint32_t, uint32_t>(version, minor);
}

void
CqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);
}

void
CqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);
}

#ifdef TERASTREAM_DB_LOGIC
void
CqlLeaseMgr::discoverLease4NoReqNoRes(LeaseExchangeData &data) {
    CqlLease4DiscoverNoReqNoResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::discoverLease4NoReqRes(LeaseExchangeData &data) {
    CqlLease4DiscoverNoReqResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::discoverLease4ReqNoRes(LeaseExchangeData &data) {
    CqlLease4DiscoverReqNoResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::discoverLease4ReqRes(LeaseExchangeData &data) {
    CqlLease4DiscoverReqResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::requestLease4NoReqNoRes(LeaseExchangeData &data) {
    CqlLease4RequestNoReqNoResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::requestLease4NoReqRes(LeaseExchangeData &data) {
    CqlLease4RequestNoReqResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::requestLease4ReqNoRes(LeaseExchangeData &data) {
    CqlLease4RequestReqNoResExchange exchange;
    exchange.execute(data);
}

void
CqlLeaseMgr::requestLease4ReqRes(LeaseExchangeData &data) {
    CqlLease4RequestReqResExchange exchange;
    exchange.execute(data);
}
#endif // TERASTREAM_DB_LOGIC

}; // end of isc::dhcp namespace
}; // end of isc namespace
