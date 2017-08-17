// Copyright (C) 2015 - 2017 Deutsche Telekom AG.
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

static const size_t HOSTNAME_MAX_LEN = 255U;
static const size_t ADDRESS6_TEXT_MAX_LEN = 39U;

/// @name CqlBind auxiliary methods for binding data into Cassandra format:
/// @{

/// @todo These void* cast are unsafe. See ticket #4525.
static CassError CqlBindNone(CassStatement* statement, size_t index, void*) {
    return cass_statement_bind_null(statement, index);
}

static CassError CqlBindBool(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_bool(statement, index,
        *(static_cast<cass_bool_t*>(value)));
}

static CassError CqlBindInt32(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_int32(statement, index,
        *(static_cast<cass_int32_t*>(value)));
}

static CassError CqlBindInt64(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_int64(statement, index,
        *(static_cast<cass_int64_t*>(value)));
}

static CassError CqlBindTimestamp(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_int64(statement, index,
        *(static_cast<cass_int64_t*>(value)));
}

static CassError CqlBindString(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_string(statement, index,
        (static_cast<const char*>(value)));
}

static CassError CqlBindBytes(CassStatement* statement, size_t index,
        void* value) {
    return cass_statement_bind_bytes(statement, index,
        static_cast<std::vector<cass_byte_t>*>(value)->data(),
        static_cast<std::vector<cass_byte_t>*>(value)->size());
}
/// @}

static CassError CqlGetNone(const CassValue*, void*, size_t*) {
    return CASS_OK;
}

static CassError CqlGetBool(const CassValue* value, void* data, size_t*) {
    return cass_value_get_bool(value, static_cast<cass_bool_t*>(data));
}

static CassError CqlGetInt32(const CassValue* value, void* data, size_t*) {
    return cass_value_get_int32(value, static_cast<cass_int32_t*>(data));
}

static CassError CqlGetInt64(const CassValue* value, void* data, size_t*) {
    return cass_value_get_int64(value, static_cast<cass_int64_t*>(data));
}

static CassError CqlGetTimestamp(const CassValue* value, void* data, size_t*) {
    return cass_value_get_int64(value, static_cast<cass_int64_t*>(data));
}

static CassError CqlGetString(const CassValue* value, void* data,
        size_t* size) {
    return cass_value_get_string(value, static_cast<const char**>(data), size);
}

static CassError CqlGetBytes(const CassValue* value, void* data, size_t* size) {
    return cass_value_get_bytes(value, static_cast<const cass_byte_t**>(data),
        size);
}

typedef CassError (*CqlBindFunction)(CassStatement* statement, size_t index,
        void* value);
typedef CassError (*CqlGetFunction)(const CassValue* value, void* data,
        size_t* size);

struct CqlFunctionData {
    CqlBindFunction sqlBindFunction_;
    CqlGetFunction sqlGetFunction_;
};

static struct CqlFunctionData CqlFunctions[] = {
    {CqlBindNone, CqlGetNone},
    {CqlBindBool, CqlGetBool},
    {CqlBindInt32, CqlGetInt32},
    {CqlBindInt64, CqlGetInt64},
    {CqlBindTimestamp, CqlGetTimestamp},
    {CqlBindString, CqlGetString},
    {CqlBindBytes, CqlGetBytes}
};

/// @brief Catalog of all the SQL statements currently supported. Note
/// that the order columns appear in statement body must match the order they
/// that the occur in the table. This does not apply to the where clause.

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
        NULL };

CqlTaggedStatement CqlLeaseMgr::tagged_statements_[] = {
    // DELETE_LEASE4
    { delete_lease4_params,
      "delete_lease4",
      "DELETE FROM lease4 WHERE address = ? "
      "IF EXISTS" },

    // DELETE_LEASE4_STATE_EXPIRED
    { delete_expired_lease4_params,
      "delete_lease4_expired",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE state = ? AND expire < ? "
      "ALLOW FILTERING" },

    // DELETE_LEASE6
    { delete_lease6_params,
      "delete_lease6",
      "DELETE FROM lease6 WHERE address = ? "
      "IF EXISTS" },

    // DELETE_LEASE6_STATE_EXPIRED
    { delete_expired_lease6_params,
      "delete_lease6_expired",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE state = ? AND expire < ? "
      "ALLOW FILTERING" },

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
      "WHERE client_id = ? AND subnet_id = ? "
      "ALLOW FILTERING" },

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
      "WHERE hwaddr = ? AND subnet_id = ? "
      "ALLOW FILTERING" },

    // GET_LEASE4_EXPIRE
    { get_lease4_expired_params,
      "get_lease4_expired",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE state = ? AND expire < ? "
      "LIMIT ? "
      "ALLOW FILTERING" },

    // GET_LEASE6_ADDR
    { get_lease6_addr_params,
      "get_lease6_addr",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE address = ? AND lease_type = ? "
      "ALLOW FILTERING" },

    // GET_LEASE6_DUID_IAID
    { get_lease6_duid_iaid_params,
       "get_lease6_duid_iaid",
       "SELECT address, duid, valid_lifetime, "
         "expire, subnet_id, pref_lifetime, "
         "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
         "hwaddr, hwtype, hwaddr_source, state "
       "FROM lease6 "
       "WHERE duid = ? AND iaid = ? AND lease_type = ? "
       "ALLOW FILTERING" },

    // GET_LEASE6_DUID_IAID_SUBID
    { get_lease6_duid_iaid_subid_params,
      "get_lease6_duid_iaid_subid",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE duid = ? AND iaid = ? AND subnet_id = ? AND lease_type = ? "
      "ALLOW FILTERING" },

    // GET_LEASE6_EXPIRE
    { get_lease6_expired_params,
      "get_lease6_expired",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, state "
      "FROM lease6 "
      "WHERE state = ? AND expire < ? "
      "LIMIT ? "
      "ALLOW FILTERING" },

    // GET_VERSION
    { get_version_params,
      "get_version",
      "SELECT version, minor FROM schema_version" },

    // INSERT_LEASE4
    { insert_lease4_params,
      "insert_lease4",
      "INSERT INTO lease4(address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname, "
        "state) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
      "IF NOT EXISTS" },

    // INSERT_LEASE6
    { insert_lease6_params,
      "insert_lease6",
      "INSERT INTO lease6(address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, "
        "hwtype, hwaddr_source, state) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
      "IF NOT EXISTS" },

    // UPDATE_LEASE4
    { update_lease4_params,
      "update_lease4",
      "UPDATE lease4 SET hwaddr = ?, "
        "client_id = ?, valid_lifetime = ?, expire = ?, "
        "subnet_id = ?, fqdn_fwd = ?, fqdn_rev = ?, hostname = ?, state = ? "
      "WHERE address = ? "
      "IF EXISTS" },

    // UPDATE_LEASE6
    { update_lease6_params,
      "update_lease6",
      "UPDATE lease6 SET duid = ?, "
        "valid_lifetime = ?, expire = ?, subnet_id = ?, "
        "pref_lifetime = ?, lease_type = ?, iaid = ?, "
        "prefix_len = ?, fqdn_fwd = ?, fqdn_rev = ?, hostname = ?, "
        "hwaddr = ?, hwtype = ?, hwaddr_source = ?, state = ? "
      "WHERE address = ? "
      "IF EXISTS" },

    // End of list sentinel
    { NULL, NULL, NULL }
};

/// @brief Common CQL and Lease Data Methods
///
/// The CqlLease4Exchange and CqlLease6Exchange classes provide the
/// functionality to set up binding information between variables in the
/// program and data extracted from the database. This class is the common
/// base to both of them, containing some common methods.
class CqlLeaseExchange : public CqlExchange {
public:
    CqlLeaseExchange() : hwaddr_length_(0), expire_(0), subnet_id_(0),
                         valid_lifetime_(0), fqdn_fwd_(false), fqdn_rev_(false),
                         hostname_length_(0), state_(0) {
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(hostname_buffer_, 0, sizeof(hostname_buffer_));
    }
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
    char            hostname_buffer_[HOSTNAME_MAX_LEN + 1];
                                        ///< Client hostname
    unsigned long   hostname_length_;   ///< Client hostname length
    uint32_t        state_;             ///< Lease state
};

class CqlVersionExchange : public virtual CqlExchange {
public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    CqlVersionExchange() {
        const size_t MAX_COLUMNS = 2U;
        // Set the column names
        size_t offset = 0U;
        BOOST_STATIC_ASSERT(2U == MAX_COLUMNS);
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("version",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("minor",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        BOOST_ASSERT(parameters_.size() == MAX_COLUMNS);
    }
};

/// @brief Exchange CQL and Lease4 Data
///
/// On any CQL operation, arrays of CQL BIND structures must be built to
/// describe the parameters in the prepared statements. Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical. This class handles the creation of that array.
///
/// Owing to the CQL API, the process requires some intermediate variables
/// to hold things like data length etc. This object holds those variables.
///
/// @note There are no unit tests for this class. It is tested indirectly
/// in all CqlLeaseMgr::xxx4() calls where it is used.

class CqlLease4Exchange : public CqlLeaseExchange {
public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    CqlLease4Exchange() : addr4_(0), client_id_length_(0),
                            client_id_null_(false) {
        const size_t MAX_COLUMNS = 12U;
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));

        // Set the column names
        size_t offset = 0U;
        BOOST_STATIC_ASSERT(12U == MAX_COLUMNS);
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("address",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("hwaddr",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("client_id",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("valid_lifetime",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT64)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("expire",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_TIMESTAMP)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("subnet_id",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("fqdn_fwd",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("fqdn_rev",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("hostname",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("state",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("limit",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("[applied]",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BOOL)));
        BOOST_ASSERT(parameters_.size() == MAX_COLUMNS);
    }

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease4 object to
    /// the database.
    void createBindForSend(const Lease4Ptr& lease, CqlDataArray& data) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease4 object is NULL");
        }
        // Store lease object to ensure it remains valid.
        lease_ = lease;
        // Set up the structures for the various components of the lease4
        // structure.

        try {
            // address: int
            // The address in the Lease structure is an IOAddress object.
            // Convert this to an integer for storage.
            addr4_ = lease_->addr_.toUint32();
            data.add(&addr4_);

            // hwaddr: blob
            HWAddrPtr hwaddr = lease_->hwaddr_;
            if (hwaddr) {
                if (hwaddr->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                    isc_throw(DbOperationError, "Hardware address length " <<
                              lease_->hwaddr_->hwaddr_.size() <<
                              " exceeds maximum allowed of " <<
                              HWAddr::MAX_HWADDR_LEN);
                }
                hwaddr_ = hwaddr->hwaddr_;
            } else {
                hwaddr_.clear();
            }
            hwaddr_length_ = hwaddr_.size();
            data.add(&hwaddr_);

            // client_id: blob
            if (lease_->client_id_) {
                client_id_ = lease_->client_id_->getClientId();
            } else {
                client_id_.clear();
            }
            client_id_length_ = client_id_.size();
            data.add(&client_id_);

            // valid lifetime: bigint
            valid_lifetime_ = lease_->valid_lft_;
            data.add(&valid_lifetime_);

            // expire: bigint
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire). The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            CqlLeaseExchange::convertToDatabaseTime(lease_->cltt_,
                lease_->valid_lft_, expire_);
            data.add(&expire_);

            // subnet_id: int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            subnet_id_ = lease_->subnet_id_;
            data.add(&subnet_id_);

            // fqdn_fwd: boolean
            fqdn_fwd_ = lease_->fqdn_fwd_;
            data.add(&fqdn_fwd_);

            // fqdn_rev: boolean
            fqdn_rev_ = lease_->fqdn_rev_;
            data.add(&fqdn_rev_);

            // hostname: varchar
            hostname_length_ = lease_->hostname_.length();
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " <<
                    lease_->hostname_.c_str());
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, lease_->hostname_.c_str(),
                    hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';
            data.add(hostname_buffer_);

            // state: int
            state_ = lease_->state_;
            data.add(&state_);

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
            unsigned char* hwaddr_buffer = NULL;
            const char* client_id_buffer = NULL;
            const char* hostname_buffer = NULL;
            CqlDataArray data;
            CqlDataArray size;

            // address: int
            data.add(reinterpret_cast<void*>(&addr4_));
            size.add(NULL);

            // hwaddr: blob
            data.add(reinterpret_cast<void*>(&hwaddr_buffer));
            size.add(reinterpret_cast<void*>(&hwaddr_length_));

            // client_id: blob
            data.add(reinterpret_cast<void*>(&client_id_buffer));
            size.add(reinterpret_cast<void*>(&client_id_length_));

            // valid_lifetime: bigint
            data.add(reinterpret_cast<void*>(&valid_lifetime_));
            size.add(NULL);

            // expire: bigint
            data.add(reinterpret_cast<void*>(&expire_));
            size.add(NULL);

            // subnet_id: int
            data.add(reinterpret_cast<void*>(&subnet_id_));
            size.add(NULL);

            // fqdn_fwd: boolean
            data.add(reinterpret_cast<void*>(&fqdn_fwd_));
            size.add(NULL);

            // fqdn_rev: boolean
            data.add(reinterpret_cast<void*>(&fqdn_rev_));
            size.add(NULL);

            // hostname: varchar
            data.add(reinterpret_cast<void*>(&hostname_buffer));
            size.add(reinterpret_cast<void*>(&hostname_length_));

            // state: int
            data.add(reinterpret_cast<void*>(&state_));
            size.add(NULL);

            for (size_t i = 0; i < data.size(); i++) {
                CqlLeaseMgr::getData(row, i, data, size, i, *this);
            }

            // hwaddr: blob
            hwaddr_.assign(hwaddr_buffer, hwaddr_buffer + hwaddr_length_);

            // client_id: blob
            client_id_.assign(client_id_buffer, client_id_buffer +
                client_id_length_);
            if (client_id_length_ >= sizeof(client_id_buffer_)) {
                isc_throw(BadValue, "client id value is too large: " <<
                    client_id_buffer);
            }
            if (client_id_length_) {
                memcpy(client_id_buffer_, client_id_buffer, client_id_length_);
            }
            client_id_buffer_[client_id_length_] = '\0';

            // hostname: varchar
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " <<
                    hostname_buffer);
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, hostname_buffer, hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';

            time_t cltt = 0;
            CqlLeaseExchange::convertFromDatabaseTime(expire_, valid_lifetime_,
                cltt);

            // Recreate the hardware address.
            HWAddrPtr hwaddr(new HWAddr(hwaddr_, HTYPE_ETHER));

            std::string hostname(hostname_buffer_,
                                 hostname_buffer_ + hostname_length_);

            Lease4Ptr result(new Lease4(addr4_, hwaddr, client_id_buffer_,
                                        client_id_length_, valid_lifetime_, 0,
                                        0, cltt, subnet_id_, fqdn_fwd_,
                                        fqdn_rev_, hostname));

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
/// describe the parameters in the prepared statements. Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical. This class handles the creation of that array.
///
/// Owing to the CQL API, the process requires some intermediate variables
/// to hold things like data length etc. This object holds those variables.
///
/// @note There are no unit tests for this class. It is tested indirectly
/// in all CqlLeaseMgr::xxx6() calls where it is used.

class CqlLease6Exchange : public CqlLeaseExchange {
public:
    /// @brief Constructor
    ///
    /// The initialization of the variables here is nonly to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    CqlLease6Exchange() : addr6_length_(0), duid_length_(0), iaid_(0),
                          lease_type_(0), prefixlen_(0), pref_lifetime_(0),
                          hwaddr_null_(false), hwtype_(0), hwaddr_source_(0) {
        const size_t MAX_COLUMNS = 18U;
        memset(addr6_buffer_, 0, sizeof(addr6_buffer_));
        memset(duid_buffer_, 0, sizeof(duid_buffer_));

        // Set the column names
        size_t offset = 0U;
        BOOST_STATIC_ASSERT(18U == MAX_COLUMNS);
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("address",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("duid",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("valid_lifetime",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT64)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("expire",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_TIMESTAMP)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("subnet_id",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("pref_lifetime",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT64)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("lease_type",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("iaid",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("prefix_len",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("fqdn_fwd",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("fqdn_rev",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("hostname",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("hwaddr",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("hwtype",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("hwaddr_source",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("state",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("limit",
            offset++, EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo("[applied]",
            offset++, EXCHANGE_DATA_TYPE_IO_OUT, EXCHANGE_DATA_TYPE_BOOL)));
        BOOST_ASSERT(parameters_.size() == MAX_COLUMNS);
    }

    /// @brief Create CQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease6 object to
    /// the database.
    void createBindForSend(const Lease6Ptr& lease, CqlDataArray& data) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease6 object is NULL");
        }
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Set up the structures for the various components of the lease4
        // structure.
        try {
            // address: varchar
            std::string text_buffer = lease_->addr_.toText();
            addr6_length_ = text_buffer.size();
            if (addr6_length_ >= sizeof(addr6_buffer_)) {
                isc_throw(BadValue, "address value is too large: " <<
                    text_buffer);
            }
            if (addr6_length_) {
                memcpy(addr6_buffer_, text_buffer.c_str(), addr6_length_);
            }
            addr6_buffer_[addr6_length_] = '\0';
            data.add(addr6_buffer_);

            // duid: blob
            if (!lease_->duid_) {
                isc_throw(DbOperationError, "lease6 for address " <<
                    addr6_buffer_ << " is missing mandatory client-id");
            }
            duid_ = lease_->duid_->getDuid();
            duid_length_ = duid_.size();
            data.add(&duid_);

            // valid lifetime: bigint
            valid_lifetime_ = lease_->valid_lft_;
            data.add(&valid_lifetime_);

            // expire: bigint
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire). The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            CqlLeaseExchange::convertToDatabaseTime(lease_->cltt_,
                lease_->valid_lft_, expire_);
            data.add(&expire_);

            // subnet_id: int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            subnet_id_ = lease_->subnet_id_;
            data.add(&subnet_id_);

            // pref_lifetime: bigint
            // Can use lease_->preferred_lft_ directly as it is of type uint32_t.
            pref_lifetime_ = lease_->preferred_lft_;
            data.add(&pref_lifetime_);

            // lease_type: int
            // Must convert to uint8_t as lease_->type_ is a LeaseType variable.
            lease_type_ = lease_->type_;
            data.add(&lease_type_);

            // iaid: int
            // Can use lease_->iaid_ directly as it is of type uint32_t.
            iaid_ = lease_->iaid_;
            data.add(&iaid_);

            // prefix_len: int
            // Can use lease_->prefixlen_ directly as it is uint32_t.
            prefixlen_ = lease_->prefixlen_;
            data.add(&prefixlen_);

            // fqdn_fwd: boolean
            fqdn_fwd_ = lease_->fqdn_fwd_;
            data.add(&fqdn_fwd_);

            // fqdn_rev: boolean
            fqdn_rev_ = lease_->fqdn_rev_;
            data.add(&fqdn_rev_);

            // hostname: varchar
            hostname_length_ = lease_->hostname_.length();
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " <<
                    lease_->hostname_.c_str());
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, lease_->hostname_.c_str(),
                    hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';
            data.add(hostname_buffer_);

            // hwaddr: blob
            HWAddrPtr hwaddr = lease_->hwaddr_;
            if (hwaddr) {
                if (hwaddr->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                    isc_throw(DbOperationError, "Hardware address length : "
                              << lease_->hwaddr_->hwaddr_.size()
                              << " exceeds maximum allowed of: "
                              << HWAddr::MAX_HWADDR_LEN);
                }
                hwaddr_ = hwaddr->hwaddr_;
            } else {
                hwaddr_.clear();
            }
            hwaddr_length_ = hwaddr_.size();
            data.add(&hwaddr_);

            // hwtype: int
            if (hwaddr) {
                hwtype_ = lease->hwaddr_->htype_;
            } else {
                hwtype_ = 0;
            }
            data.add(&hwtype_);

            // hwaddr_source: int
            if (hwaddr) {
                hwaddr_source_ = lease->hwaddr_->source_;
            } else {
                hwaddr_source_ = 0;
            }
            data.add(&hwaddr_source_);

            // state: int
            state_ = lease_->state_;
            data.add(&state_);

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
            unsigned char* duid_buffer = NULL;
            unsigned char* hwaddr_buffer = NULL;
            const char* address_buffer = NULL;
            const char* hostname_buffer = NULL;
            CqlDataArray data;
            CqlDataArray size;

            // address: varchar
            data.add(reinterpret_cast<void*>(&address_buffer));
            size.add(reinterpret_cast<void*>(&addr6_length_));

            // duid: blob
            data.add(reinterpret_cast<void*>(&duid_buffer));
            size.add(reinterpret_cast<void*>(&duid_length_));

            // valid_lifetime_: bigint
            data.add(reinterpret_cast<void*>(&valid_lifetime_));
            size.add(NULL);

            // expire: bigint
            data.add(reinterpret_cast<void*>(&expire_));
            size.add(NULL);

            // subnet_id: int
            data.add(reinterpret_cast<void*>(&subnet_id_));
            size.add(NULL);

            // pref_lifetime: bigint
            data.add(reinterpret_cast<void*>(&pref_lifetime_));
            size.add(NULL);

            // lease_type: int
            data.add(reinterpret_cast<void*>(&lease_type_));
            size.add(NULL);

            // iaid: int
            data.add(reinterpret_cast<void*>(&iaid_));
            size.add(NULL);

            // prefix_len: int
            data.add(reinterpret_cast<void*>(&prefixlen_));
            size.add(NULL);

            // fqdn_fwd: boolean
            data.add(reinterpret_cast<void*>(&fqdn_fwd_));
            size.add(NULL);

            // fqdn_rev: boolean
            data.add(reinterpret_cast<void*>(&fqdn_rev_));
            size.add(NULL);

            // hostname: varchar
            data.add(reinterpret_cast<void*>(&hostname_buffer));
            size.add(reinterpret_cast<void*>(&hostname_length_));

            // hwaddr: blob
            data.add(reinterpret_cast<void*>(&hwaddr_buffer));
            size.add(reinterpret_cast<void*>(&hwaddr_length_));

            // hwtype: int
            data.add(reinterpret_cast<void*>(&hwtype_));
            size.add(NULL);

            // hwaddr_source: int
            data.add(reinterpret_cast<void*>(&hwaddr_source_));
            size.add(NULL);

            // state: int
            data.add(reinterpret_cast<void*>(&state_));
            size.add(NULL);

            for (size_t i = 0; i < data.size(); i++) {
                CqlLeaseMgr::getData(row, i, data, size, i, *this);
            }

            // address: varchar
            if (addr6_length_ >= sizeof(addr6_buffer_)) {
                isc_throw(BadValue, "address value is too large: " <<
                    address_buffer);
            }
            if (addr6_length_) {
                memcpy(addr6_buffer_, address_buffer, addr6_length_);
            }
            addr6_buffer_[addr6_length_] = '\0';

            // duid: blob
            duid_.assign(duid_buffer, duid_buffer + duid_length_);

            // hostname: varchar
            if (hostname_length_ >= sizeof(hostname_buffer_)) {
                isc_throw(BadValue, "hostname value is too large: " <<
                    hostname_buffer);
            }
            if (hostname_length_) {
                memcpy(hostname_buffer_, hostname_buffer, hostname_length_);
            }
            hostname_buffer_[hostname_length_] = '\0';

            // hwaddr: blob
            hwaddr_.assign(hwaddr_buffer, hwaddr_buffer + hwaddr_length_);

            if (lease_type_ != Lease::TYPE_NA && lease_type_ != Lease::TYPE_TA &&
                    lease_type_ != Lease::TYPE_PD) {
                isc_throw(BadValue, "invalid lease type returned (" <<
                    static_cast<int>(lease_type_) << ") for lease with "
                    << "address " << addr6_buffer_ << ". Only 0, 1, or 2 are "
                    << "allowed");
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
            Lease6Ptr result(new Lease6(static_cast<Lease::Type>(lease_type_),
                                        addr, duid, iaid_, pref_lifetime_,
                                        valid_lifetime_, 0, 0, subnet_id_,
                                        fqdn_fwd_, fqdn_rev_, hostname, hwaddr,
                                        prefixlen_));

            time_t cltt = 0;
            CqlLeaseExchange::convertFromDatabaseTime(expire_, valid_lifetime_,
                cltt);
            result->cltt_ = cltt;

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

CqlLeaseMgr::CqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : LeaseMgr(), dbconn_(parameters), exchange4_(new CqlLease4Exchange()),
    exchange6_(new CqlLease6Exchange()), versionExchange_(new CqlVersionExchange()) {
    dbconn_.openDatabase();
    dbconn_.prepareStatements(CqlLeaseMgr::tagged_statements_);
}

CqlLeaseMgr::~CqlLeaseMgr() {
    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the dbconn_ member variable.
}

std::string
CqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "CQL backend " << CQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << CQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << "cassandra_static";
    return (tmp.str());
}

ExchangeDataType
CqlLeaseMgr::getDataType(const StatementIndex stindex, int pindex,
        const SqlExchange& exchange) {
    if (CqlLeaseMgr::tagged_statements_[stindex].params_ &&
            CqlLeaseMgr::tagged_statements_[stindex].params_[pindex]) {
        const ExchangeColumnInfoContainerName& idx = exchange.parameters_.get<1>();
        const ExchangeColumnInfoContainerNameRange& range =
            idx.equal_range(CqlLeaseMgr::tagged_statements_[stindex].params_[pindex]);
        if (std::distance(range.first, range.second) > 0) {
            return (*range.first)->type_;
        }
    }
    return EXCHANGE_DATA_TYPE_NONE;
}

void
CqlLeaseMgr::bindData(CassStatement* statement, const StatementIndex stindex,
        CqlDataArray& data, const SqlExchange& exchange) {
    if (CqlLeaseMgr::tagged_statements_[stindex].params_ == NULL) {
        return;
    }
    for (int i = 0; CqlLeaseMgr::tagged_statements_[stindex].params_[i]; i++) {
        ExchangeDataType type = CqlLeaseMgr::getDataType(stindex, i, exchange);
        if (type >= sizeof(CqlFunctions) / sizeof(CqlFunctions[0])) {
            isc_throw(BadValue, "index " << stindex << " out of bounds");
        }
        CqlFunctions[type].sqlBindFunction_(statement, i, data.values_[i]);
    }
}

void
CqlLeaseMgr::getData(const CassRow* row, const int pindex, CqlDataArray& data,
        CqlDataArray& size, const int dindex, const SqlExchange& exchange) {
    if (pindex >= exchange.parameters_.size()) {
        return;
    }
    const ExchangeColumnInfoContainerIndex& idx = exchange.parameters_.get<2>();
    const ExchangeColumnInfoContainerIndexRange& range = idx.equal_range(pindex);
    if (std::distance(range.first, range.second) > 0) {
        std::string name = (*range.first)->name_;
        ExchangeDataType type = (*range.first)->type_;
        const CassValue* value = cass_row_get_column_by_name(row, name.c_str());
        if (NULL == value) {
            isc_throw(BadValue, "column name " << name << " doesn't exist");
        }
        if (type >= sizeof(CqlFunctions) / sizeof(CqlFunctions[0])) {
            isc_throw(BadValue, "index " << type << " out of bounds");
        }
        CqlFunctions[type].sqlGetFunction_(value, data.values_[dindex],
            reinterpret_cast<size_t *>(size.values_[dindex]));
    }
}

bool
CqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              CqlDataArray& data, CqlLeaseExchange& exchange) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (NULL == statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    CqlLeaseMgr::bindData(statement, stindex, data, exchange);

    future = cass_session_execute(dbconn_.session_, statement);
    if (NULL == future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, "unable to execute statement");
    }
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, stindex, "unable to INSERT");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        return false;
    }

    // Check if statement has been applied.
    const CassResult* resultCollection = cass_future_get_result(future);
    CassIterator* rows = cass_iterator_from_result(resultCollection);
    CqlDataArray appliedData;
    CqlDataArray appliedSize;
    bool applied = false;
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // [applied]: bool
        appliedData.add(reinterpret_cast<void*>(&applied));
        appliedSize.add(NULL);
        CqlLeaseMgr::getData(row, exchange.parameters_.size() - 1, appliedData,
                             appliedSize, 0, exchange);
    }

    // Free resources.
    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

    return applied;
}

bool
CqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_ADD_ADDR4).arg(lease->addr_.toText());

    CqlDataArray data;
    exchange4_->createBindForSend(lease, data);
    return (addLeaseCommon(INSERT_LEASE4, data, *exchange4_));
}

bool
CqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_ADD_ADDR6).arg(lease->addr_.toText());

    CqlDataArray data;
    exchange6_->createBindForSend(lease, data);
    return (addLeaseCommon(INSERT_LEASE6, data, *exchange6_));
}

template <typename Exchange, typename LeaseCollection>
void CqlLeaseMgr::getLeaseCollection(StatementIndex stindex,
                                       CqlDataArray& data,
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
    if (NULL == statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    CqlLeaseMgr::bindData(statement, stindex, data, leaseExchange);

    future = cass_session_execute(dbconn_.session_, statement);
    if (NULL == future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, "unable to execute statement");
    }
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
        if (single && rowCount > 1) {
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
CqlLeaseMgr::getLease(StatementIndex stindex, CqlDataArray& data,
                             Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria. The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(stindex, data, exchange4_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
CqlLeaseMgr::getLease(StatementIndex stindex, CqlDataArray& data,
                             Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria. The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(stindex, data, exchange6_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

// Basic lease access methods. Obtain leases from the database using various
// criteria.

Lease4Ptr
CqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_ADDR4).arg(addr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    uint32_t addr4_data = addr.toUint32();
    data.add(&addr4_data);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_HWADDR).arg(hwaddr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<uint8_t>hwaddr_data = hwaddr.hwaddr_;
    data.add(&hwaddr_data);

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, data, result);

    return (result);
}

Lease4Ptr
CqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SUBID_HWADDR)
              .arg(subnet_id).arg(hwaddr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<uint8_t>hwaddr_data = hwaddr.hwaddr_;
    data.add(&hwaddr_data);

    uint32_t subnet_id_data = subnet_id;
    data.add(&subnet_id_data);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_CLIENTID).arg(clientid.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<uint8_t> client_id_data = clientid.getClientId();
    data.add(&client_id_data);

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, data, result);

    return (result);
}

Lease4Ptr
CqlLeaseMgr::getLease4(const ClientId& clientid, const HWAddr& hwaddr,
        SubnetID subnet_id) const {
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
    CqlDataArray data;

    std::vector<uint8_t> client_id_data = clientid.getClientId();
    data.add(&client_id_data);

    uint32_t subnet_id_data = subnet_id;
    data.add(&subnet_id_data);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, data, result);

    return (result);
}

Lease6Ptr
CqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_ADDR6).arg(addr.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    CqlDataArray data;

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
    data.add(addr6_buffer);

    uint32_t lease_type_data = lease_type;
    data.add(&lease_type_data);

    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, data, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type,
                          const DUID& duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_IAID_DUID).arg(iaid).arg(duid.toText())
              .arg(lease_type);

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<uint8_t> duid_data = duid.getDuid();
    data.add(&duid_data);

    uint32_t iaid_data = iaid;
    data.add(&iaid_data);

    uint32_t lease_type_data = lease_type;
    data.add(&lease_type_data);

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, data, result);

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
    CqlDataArray data;

    std::vector<uint8_t> duid_data = duid.getDuid();
    data.add(&duid_data);

    uint32_t iaid_data = iaid;
    data.add(&iaid_data);

    uint32_t subnet_id_data = subnet_id;
    data.add(&subnet_id_data);

    uint32_t lease_type_data = lease_type;
    data.add(&lease_type_data);

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, data, result);

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
    uint32_t keepState = Lease::STATE_EXPIRED_RECLAIMED;
    uint64_t timestamp = static_cast<int64_t>(time(NULL));

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    uint32_t limit = max_leases > 0 ? static_cast<int32_t>(max_leases) :
        std::numeric_limits<int32_t>::max();

    for (uint32_t state = Lease::STATE_DEFAULT;
            state <= Lease::STATE_EXPIRED_RECLAIMED; state++) {
        if (state == keepState) {
            continue;
        }
        LeaseCollection tempCollection;
        CqlDataArray data;

        data.add(&state);
        data.add(&timestamp);
        data.add(&limit);

        // Retrieve leases from the database.
        getLeaseCollection(statement_index, data, tempCollection);

        typedef typename LeaseCollection::iterator LeaseCollectionIt;

        for (LeaseCollectionIt it = tempCollection.begin();
                it != tempCollection.end(); ++it) {
            expired_leases.push_back((*it));
        }
    }
}

template <typename LeasePtr>
void
CqlLeaseMgr::updateLeaseCommon(StatementIndex stindex,
                                 CqlDataArray& data,
                                 const LeasePtr&, CqlLeaseExchange& exchange) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_ADD_ADDR4).arg(dbconn_.tagged_statements_[stindex].name_);

    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (NULL == statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    CqlLeaseMgr::bindData(statement, stindex, data, exchange);

    future = cass_session_execute(dbconn_.session_, statement);
    if (NULL == future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, "unable to execute statement");
    }
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, stindex, "unable to UPDATE");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Check if statement has been applied.
    const CassResult* resultCollection = cass_future_get_result(future);
    CassIterator* rows = cass_iterator_from_result(resultCollection);
    CqlDataArray appliedData;
    CqlDataArray appliedSize;
    bool applied = false;
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // [applied]: bool
        appliedData.add(reinterpret_cast<void*>(&applied));
        appliedSize.add(NULL);
        CqlLeaseMgr::getData(row, exchange.parameters_.size() - 1, appliedData,
                             appliedSize, 0, exchange);
    }

    // Free resources.
    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

    if (!applied) {
        isc_throw(NoSuchLease, "Statement has not been applied.");
    }
}

void
CqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_ADDR4).arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    CqlDataArray data;
    exchange4_->createBindForSend(lease, data);
    data.remove(0);

    // Set up the WHERE clause and append it to the SQL_BIND array
    uint32_t addr4_data = lease->addr_.toUint32();
    data.add(&addr4_data);

    // Drop to common update code
    updateLeaseCommon(stindex, data, lease, *exchange4_);
}

void
CqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_ADDR6).arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    CqlDataArray data;
    exchange6_->createBindForSend(lease, data);
    data.remove(0);

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
    data.add(addr6_buffer);

    // Drop to common update code
    updateLeaseCommon(stindex, data, lease, *exchange6_);
}

bool
CqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex,
                                 CqlDataArray& data, CqlLeaseExchange& exchange) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (NULL == statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    CqlLeaseMgr::bindData(statement, stindex, data, exchange);

    future = cass_session_execute(dbconn_.session_, statement);
    if (NULL == future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, "unable to execute statement");
    }
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, stindex, "unable to DELETE");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Check if statement has been applied.
    const CassResult* resultCollection = cass_future_get_result(future);
    CassIterator* rows = cass_iterator_from_result(resultCollection);
    CqlDataArray appliedData;
    CqlDataArray appliedSize;
    bool applied = false;
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // [applied]: bool
        appliedData.add(reinterpret_cast<void*>(&applied));
        appliedSize.add(NULL);
        CqlLeaseMgr::getData(row, exchange.parameters_.size() - 1, appliedData,
                             appliedSize, 0, exchange);
    }

    // Free resources.
    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

    return applied;
}

bool
CqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_ADDR).arg(addr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    if (addr.isV4()) {
        uint32_t addr4_data = addr.toUint32();
        data.add(&addr4_data);
        return (deleteLeaseCommon(DELETE_LEASE4, data, *exchange4_));
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
        data.add(addr6_buffer);
        return (deleteLeaseCommon(DELETE_LEASE6, data, *exchange6_));
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
CqlLeaseMgr::deleteExpiredReclaimedLeasesCommon(const uint32_t secs,
        StatementIndex statement_index) {
    // Set up the WHERE clause value

    CqlDataArray data;
    uint32_t result = 0;

    // State is reclaimed.
    uint32_t state = Lease::STATE_EXPIRED_RECLAIMED;
    data.add(&state);

    // Expiration timestamp.
    uint64_t expiration = static_cast<int64_t>(time(NULL) -
        static_cast<time_t>(secs));
    data.add(&expiration);

    // Get the data
    Lease4Collection result4Leases;
    Lease6Collection result6Leases;
    switch (statement_index) {
    case DELETE_LEASE4_STATE_EXPIRED:
        getLeaseCollection(statement_index, data, result4Leases);
        break;
    case DELETE_LEASE6_STATE_EXPIRED:
        getLeaseCollection(statement_index, data, result6Leases);
        break;
    default:
        break;
    }
    for (Lease4Collection::iterator it = result4Leases.begin();
            it != result4Leases.end(); ++it) {
        if (deleteLease((*it)->addr_)) {
            result++;
        }
    }
    for (Lease6Collection::iterator it = result6Leases.begin();
            it != result6Leases.end(); ++it) {
        if (deleteLease((*it)->addr_)) {
            result++;
        }
    }
    return (result);
}

size_t
CqlLeaseMgr::wipeLeases4(const SubnetID& /*subnet_id*/) {
    isc_throw(NotImplemented, "wipeLeases4 is not implemented for Cassandra backend");
}

size_t
CqlLeaseMgr::wipeLeases6(const SubnetID& /*subnet_id*/) {
    isc_throw(NotImplemented, "wipeLeases6 is not implemented for Cassandra backend");
}

std::string
CqlLeaseMgr::getName() const {
    std::string name = "";
    try {
        name = dbconn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string
CqlLeaseMgr::getDescription() const {
    return std::string("Cassandra Database");
}

pair<uint32_t, uint32_t>
CqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_VERSION);
    uint32_t version;
    uint32_t minor;
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[GET_VERSION]);
    if (NULL == statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    future = cass_session_execute(dbconn_.session_, statement);
    if (NULL == future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError, "unable to execute statement");
    }
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, "unable to GET");
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Get major and minor versions.
    const CassResult* resultCollection = cass_future_get_result(future);
    CassIterator* rows = cass_iterator_from_result(resultCollection);
    CqlDataArray data;
    CqlDataArray size;
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // version: uint32_t
        data.add(reinterpret_cast<void*>(&version));
        size.add(NULL);
        // minor: uint32_t
        data.add(reinterpret_cast<void*>(&minor));
        size.add(NULL);
        for (size_t i = 0; i < data.size(); i++) {
            CqlLeaseMgr::getData(row, i, data, size, i, *versionExchange_);
        }
    }

    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

    return (make_pair(version, minor));
}

void
CqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);
}

void
CqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
