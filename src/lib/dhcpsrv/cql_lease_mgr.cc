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
#include <dhcpsrv/cql_lease_mgr.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <limits>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace dhcp {

static const size_t HOSTNAME_MAX_LEN = 255U;
static const size_t ADDRESS6_TEXT_MAX_LEN = 39U;

/// @{
///
/// @brief Catalog of all the CQL statements currently supported. Note
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
/// @}

CqlTaggedStatement CqlLeaseMgr::tagged_statements_[] = {
    // DELETE_LEASE4
    { delete_lease4_params,
      "delete_lease4",
      "DELETE FROM lease4 WHERE address = ? "
      "IF EXISTS "
    },

    // DELETE_LEASE4_STATE_EXPIRED
    { delete_expired_lease4_params,
      "delete_lease4_expired",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE state = ? "
      "AND expire < ? "
      "ALLOW FILTERING "
    },

    // DELETE_LEASE6
    { delete_lease6_params,
      "delete_lease6",
      "DELETE FROM lease6 WHERE address = ? "
      "IF EXISTS "
    },

    // DELETE_LEASE6_STATE_EXPIRED
    { delete_expired_lease6_params,
      "delete_lease6_expired",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state "
      "FROM lease6 "
      "WHERE state = ? "
      "AND expire < ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE4_ADDR
    { get_lease4_addr_params,
      "get_lease4_addr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE address = ? "
    },

    // GET_LEASE4_CLIENTID
    { get_lease4_clientid_params,
      "get_lease4_clientid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE client_id = ? "
    },

    // GET_LEASE4_CLIENTID_SUBID
    { get_lease4_clientid_subid_params,
      "get_lease4_clientid_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE client_id = ? "
      "AND subnet_id = ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE4_HWADDR
    { get_lease4_hwaddr_params,
      "get_lease4_hwaddr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE hwaddr = ? "
    },

    // GET_LEASE4_HWADDR_SUBID
    { get_lease4_hwaddr_subid_params,
      "get_lease4_hwaddr_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE hwaddr = ? "
      "AND subnet_id = ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE4_EXPIRE
    { get_lease4_expired_params,
      "get_lease4_expired",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease4 "
      "WHERE state = ? "
      "AND expire < ? "
      "LIMIT ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE6_ADDR
    { get_lease6_addr_params,
      "get_lease6_addr",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state "
      "FROM lease6 "
      "WHERE address = ? "
      "AND lease_type = ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE6_DUID_IAID
    { get_lease6_duid_iaid_params,
      "get_lease6_duid_iaid",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state "
      "FROM lease6 "
      "WHERE duid = ? "
      "AND iaid = ? "
      "AND lease_type = ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE6_DUID_IAID_SUBID
    { get_lease6_duid_iaid_subid_params,
      "get_lease6_duid_iaid_subid",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state "
      "FROM lease6 "
      "WHERE duid = ? "
      "AND iaid = ? "
      "AND subnet_id = ? "
      "AND lease_type = ? "
      "ALLOW FILTERING "
    },

    // GET_LEASE6_EXPIRE
    { get_lease6_expired_params,
      "get_lease6_expired",
      "SELECT address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state "
      "FROM lease6 "
      "WHERE state = ? "
      "AND expire < ? "
      "LIMIT ? "
      "ALLOW FILTERING "
    },

    // GET_VERSION
    { get_version_params,
      "get_version",
      "SELECT version, minor FROM schema_version "
    },

    // INSERT_LEASE4
    { insert_lease4_params,
      "insert_lease4",
      "INSERT INTO lease4(address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname, "
        "state) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, "
      "?) "
      "IF NOT EXISTS "
    },

    // INSERT_LEASE6
    { insert_lease6_params,
      "insert_lease6",
      "INSERT INTO lease6(address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, "
        "hwtype, hwaddr_source, "
        "state) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
      "?) "
      "IF NOT EXISTS "
    },

    // UPDATE_LEASE4
    { update_lease4_params,
      "update_lease4",
      "UPDATE lease4 SET hwaddr = ?, "
        "client_id = ?, valid_lifetime = ?, expire = ?, "
        "subnet_id = ?, fqdn_fwd = ?, fqdn_rev = ?, hostname = ?, "
        "state = ? "
      "WHERE address = ? "
      "IF EXISTS "
    },

    // UPDATE_LEASE6
    { update_lease6_params,
      "update_lease6",
      "UPDATE lease6 SET duid = ?, "
        "valid_lifetime = ?, expire = ?, subnet_id = ?, "
        "pref_lifetime = ?, lease_type = ?, iaid = ?, "
        "prefix_len = ?, fqdn_fwd = ?, fqdn_rev = ?, hostname = ?, "
        "hwaddr = ?, hwtype = ?, hwaddr_source = ?, "
        "state = ? "
      "WHERE address = ? "
      "IF EXISTS "
    },


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
    CqlLeaseExchange()
        : valid_lifetime_(0), expire_(0), subnet_id_(0), fqdn_fwd_(cass_false),
          fqdn_rev_(cass_false), state_(0) {
    }

protected:
    std::vector<cass_byte_t> hwaddr_;  ///< Hardware address
    cass_int64_t valid_lifetime_;      ///< Lease time
    cass_int64_t expire_;              ///< Lease expiry time
    cass_int32_t subnet_id_;           ///< Subnet identification
    cass_bool_t fqdn_fwd_;             ///< Has forward DNS update
                                       /// been performed
    cass_bool_t fqdn_rev_;             ///< Has reverse DNS update
                                       /// been performed
    std::string hostname_;             ///< Client hostname
    cass_int32_t state_;               ///< Lease state
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
    CqlLease4Exchange() : addr4_(0) {
        // Set the column names
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "address", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "hwaddr", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "client_id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "valid_lifetime", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT64)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "expire", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_TIMESTAMP)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "subnet_id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "fqdn_fwd", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "fqdn_rev", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "hostname", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_STRING)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "state", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "limit", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "[applied]", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BOOL)));
        BOOST_ASSERT(parameters_.size() == 12U);
    }

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease4 object to
    /// the database.
    void createBindForSend(const Lease4Ptr& lease, CqlDataArray& data) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend(): Lease4 object is NULL");
        }
        // Store lease object to ensure it remains valid.
        lease_ = lease;
        // Set up the structures for the various components of the lease4
        // structure.

        try {
            // address: int
            // The address in the Lease structure is an IOAddress object.
            // Convert this to an integer for storage.
            addr4_ = static_cast<cass_int32_t>(lease_->addr_.toUint32());
            data.add(reinterpret_cast<void*>(&addr4_));

            // hwaddr: blob
            if (lease_->hwaddr_) {
                if (lease_->hwaddr_->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                    isc_throw(DbOperationError,
                              "hardware address "
                                  << lease_->hwaddr_->toText() << " of length "
                                  << lease_->hwaddr_->hwaddr_.size()
                                  << " exceeds maximum allowed length of "
                                  << HWAddr::MAX_HWADDR_LEN);
                }
                hwaddr_ = lease_->hwaddr_->hwaddr_;
            } else {
                hwaddr_.clear();
            }
            data.add(reinterpret_cast<void*>(&hwaddr_));

            // client_id: blob
            if (lease_->client_id_) {
                client_id_ = lease_->client_id_->getClientId();
            } else {
                client_id_.clear();
            }
            data.add(reinterpret_cast<void*>(&client_id_));

            // valid lifetime: bigint
            valid_lifetime_ = static_cast<cass_int32_t>(lease_->valid_lft_);
            data.add(reinterpret_cast<void*>(&valid_lifetime_));

            // expire: bigint
            // The lease structure holds the client last transmission time
            /// (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire). The relationship is given by:
            // expire = cltt_ + valid_lft_
            CqlExchange::convertToDatabaseTime(lease_->cltt_,
                                               lease_->valid_lft_, expire_);
            data.add(reinterpret_cast<void*>(&expire_));

            // subnet_id: int
            subnet_id_ = static_cast<cass_int32_t>(lease_->subnet_id_);
            data.add(reinterpret_cast<void*>(&subnet_id_));

            // fqdn_fwd: boolean
            fqdn_fwd_ = lease_->fqdn_fwd_ ? cass_true : cass_false;
            data.add(reinterpret_cast<void*>(&fqdn_fwd_));

            // fqdn_rev: boolean
            fqdn_rev_ = lease_->fqdn_rev_ ? cass_true : cass_false;
            data.add(reinterpret_cast<void*>(&fqdn_rev_));

            // hostname: varchar
            if (lease_->hostname_.size() > HOSTNAME_MAX_LEN) {
                isc_throw(BadValue, "hostname "
                                        << lease_->hostname_ << " of length "
                                        << lease_->hostname_.size()
                                        << " exceeds maximum allowed length of "
                                        << HOSTNAME_MAX_LEN);
            }
            hostname_ = lease_->hostname_;
            data.add(reinterpret_cast<void*>(&hostname_));

            // state: int
            state_ = static_cast<cass_int32_t>(lease_->state_);
            data.add(reinterpret_cast<void*>(&state_));
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "could not create bind array from Lease4: "
                          << lease_->addr_.toText()
                          << ", reason: " << ex.what());
        }
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a CQL_BIND array to receive Lease4 data from the database.
    virtual void createBindForReceive(CqlDataArray& data,
                                      const int /* statementIndex */ = -1) {
        // address: int
        data.add(reinterpret_cast<void*>(&addr4_));

        // hwaddr: blob
        data.add(reinterpret_cast<void*>(&hwaddr_));

        // client_id: blob
        data.add(reinterpret_cast<void*>(&client_id_));

        // valid_lifetime: bigint
        data.add(reinterpret_cast<void*>(&valid_lifetime_));

        // expire: bigint
        data.add(reinterpret_cast<void*>(&expire_));

        // subnet_id: int
        data.add(reinterpret_cast<void*>(&subnet_id_));

        // fqdn_fwd: boolean
        data.add(reinterpret_cast<void*>(&fqdn_fwd_));

        // fqdn_rev: boolean
        data.add(reinterpret_cast<void*>(&fqdn_rev_));

        // hostname: varchar
        data.add(reinterpret_cast<void*>(&hostname_));

        // state: int
        data.add(reinterpret_cast<void*>(&state_));
    }

    Lease4Ptr retrieveLease() {
        try {
            // Sanity checks
            if (hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                isc_throw(BadValue, "hardware address "
                                        << HWAddr(hwaddr_, HTYPE_ETHER).toText()
                                        << " of length " << hwaddr_.size()
                                        << " exceeds maximum allowed length of "
                                        << HWAddr::MAX_HWADDR_LEN);
            }
            if (client_id_.size() > ClientId::MAX_CLIENT_ID_LEN) {
                isc_throw(BadValue, "client ID "
                                        << ClientId(client_id_).toText()
                                        << " of length " << client_id_.size()
                                        << " exceeds maximum allowed length of "
                                        << ClientId::MAX_CLIENT_ID_LEN);
            }
            if (hostname_.size() > HOSTNAME_MAX_LEN) {
                isc_throw(BadValue, "hostname"
                                        << hostname_ << " of length "
                                        << hostname_.size()
                                        << " exceeds maximum allowed length of "
                                        << HOSTNAME_MAX_LEN);
            }

            time_t cltt = 0;
            CqlExchange::convertFromDatabaseTime(expire_, valid_lifetime_,
                                                 cltt);

            // Recreate the hardware address.
            HWAddrPtr hwaddr(new HWAddr(hwaddr_, HTYPE_ETHER));

            Lease4Ptr result(new Lease4(addr4_, hwaddr, client_id_.data(),
                                        client_id_.size(), valid_lifetime_, 0,
                                        0, cltt, subnet_id_, fqdn_fwd_,
                                        fqdn_rev_, hostname_));

            result->state_ = state_;

            return result;
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "createBindForReceive(): "
                      "could not convert data to Lease4, reason: "
                          << ex.what());
        }
        return Lease4Ptr();
    }

    void* retrieve() {
        isc_throw(NotImplemented, "retrieve(): Not implemented yet.");
    }

private:
    Lease4Ptr lease_;                     ///< Pointer to lease object
    cass_int32_t addr4_;                  ///< IPv4 address
    std::vector<cass_byte_t> client_id_;  ///< Client identification
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
    CqlLease6Exchange()
        : pref_lifetime_(0), lease_type_(0), iaid_(0), prefixlen_(0),
          hwtype_(0), hwaddr_source_(0) {
        // Set the column names
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "address", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_STRING)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "duid", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "valid_lifetime", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT64)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "expire", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_TIMESTAMP)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "subnet_id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "pref_lifetime", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT64)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "lease_type", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "iaid", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "prefix_len", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "fqdn_fwd", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "fqdn_rev", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BOOL)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "hostname", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_STRING)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "hwaddr", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BYTES)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "hwtype", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "hwaddr_source", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "state", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "limit", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_INT32)));
        parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
            "[applied]", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
            EXCHANGE_DATA_TYPE_BOOL)));
        BOOST_ASSERT(parameters_.size() == 18U);
    }

    /// @brief Create CQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease6 object to
    /// the database.
    void createBindForSend(const Lease6Ptr& lease, CqlDataArray& data) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend(): Lease6 object is NULL");
        }
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Set up the structures for the various components of the lease4
        // structure.
        try {
            // address: varchar
            addr6_ = lease_->addr_.toText();
            if (addr6_.size() > ADDRESS6_TEXT_MAX_LEN) {
                isc_throw(BadValue,
                          "address " << addr6_ << " of length " << addr6_.size()
                                     << " exceeds maximum allowed length of "
                                     << ADDRESS6_TEXT_MAX_LEN);
            }
            data.add(reinterpret_cast<void*>(&addr6_));

            // duid: blob
            if (!lease_->duid_) {
                isc_throw(DbOperationError,
                          "lease6 for address "
                              << addr6_ << " is missing mandatory duid");
            }
            duid_ = lease_->duid_->getDuid();
            data.add(reinterpret_cast<void*>(&duid_));

            // valid lifetime: bigint
            valid_lifetime_ = static_cast<cass_int64_t>(lease_->valid_lft_);
            data.add(reinterpret_cast<void*>(&valid_lifetime_));

            // expire: bigint
            // The lease structure holds the client last transmission time
            // (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire). The relationship is given by:
            // expire = cltt_ + valid_lft_
            CqlExchange::convertToDatabaseTime(lease_->cltt_,
                                               lease_->valid_lft_, expire_);
            data.add(reinterpret_cast<void*>(&expire_));

            // subnet_id: int
            subnet_id_ = static_cast<cass_int32_t>(lease_->subnet_id_);
            data.add(reinterpret_cast<void*>(&subnet_id_));

            // pref_lifetime: bigint
            pref_lifetime_ = static_cast<cass_int64_t>(lease_->preferred_lft_);
            data.add(reinterpret_cast<void*>(&pref_lifetime_));

            // lease_type: int
            lease_type_ = static_cast<cass_int32_t>(lease_->type_);
            data.add(reinterpret_cast<void*>(&lease_type_));

            // iaid: int
            iaid_ = static_cast<cass_int32_t>(lease_->iaid_);
            data.add(reinterpret_cast<void*>(&iaid_));

            // prefix_len: int
            prefixlen_ = static_cast<cass_int32_t>(lease_->prefixlen_);
            data.add(reinterpret_cast<void*>(&prefixlen_));

            // fqdn_fwd: boolean
            fqdn_fwd_ = lease_->fqdn_fwd_ ? cass_true : cass_false;
            data.add(reinterpret_cast<void*>(&fqdn_fwd_));

            // fqdn_rev: boolean
            fqdn_rev_ = lease_->fqdn_rev_ ? cass_true : cass_false;
            data.add(reinterpret_cast<void*>(&fqdn_rev_));

            // hostname: varchar
            if (lease_->hostname_.size() > HOSTNAME_MAX_LEN) {
                isc_throw(BadValue, "hostname"
                                        << lease_->hostname_ << " of length "
                                        << lease_->hostname_.size()
                                        << " exceeds maximum allowed length of "
                                        << HOSTNAME_MAX_LEN);
            }
            hostname_ = lease_->hostname_;
            data.add(reinterpret_cast<void*>(&hostname_));

            // hwaddr: blob
            if (lease_->hwaddr_) {
                if (lease_->hwaddr_->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                    isc_throw(BadValue,
                              "hardware address "
                                  << lease_->hwaddr_->toText() << " of length "
                                  << lease_->hwaddr_->hwaddr_.size()
                                  << " exceeds maximum allowed length of "
                                  << HWAddr::MAX_HWADDR_LEN);
                }
                hwaddr_ = lease_->hwaddr_->hwaddr_;
            } else {
                hwaddr_.clear();
            }
            data.add(reinterpret_cast<void*>(&hwaddr_));

            // hwtype: int
            if (lease_->hwaddr_) {
                hwtype_ = static_cast<cass_int32_t>(lease_->hwaddr_->htype_);
            } else {
                hwtype_ = 0;
            }
            data.add(reinterpret_cast<void*>(&hwtype_));

            // hwaddr_source: int
            if (lease_->hwaddr_) {
                hwaddr_source_ =
                    static_cast<cass_int32_t>(lease_->hwaddr_->source_);
            } else {
                hwaddr_source_ = 0;
            }
            data.add(reinterpret_cast<void*>(&hwaddr_source_));

            // state: int
            state_ = static_cast<cass_int32_t>(lease_->state_);
            data.add(reinterpret_cast<void*>(&state_));
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "createBindForSend(): "
                      "could not create bind array from Lease6: "
                          << lease_->addr_.toText()
                          << ", reason: " << ex.what());
        }
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a CQL_BIND array to receive Lease6 data from the database.
    void createBindForReceive(CqlDataArray& data,
                              const int /* statementIndex */ = -1) {
        // address: varchar
        data.add(reinterpret_cast<void*>(&addr6_));

        // duid: blob
        data.add(reinterpret_cast<void*>(&duid_));

        // valid_lifetime_: bigint
        data.add(reinterpret_cast<void*>(&valid_lifetime_));

        // expire: bigint
        data.add(reinterpret_cast<void*>(&expire_));

        // subnet_id: int
        data.add(reinterpret_cast<void*>(&subnet_id_));

        // pref_lifetime: bigint
        data.add(reinterpret_cast<void*>(&pref_lifetime_));

        // lease_type: int
        data.add(reinterpret_cast<void*>(&lease_type_));

        // iaid: int
        data.add(reinterpret_cast<void*>(&iaid_));

        // prefix_len: int
        data.add(reinterpret_cast<void*>(&prefixlen_));

        // fqdn_fwd: boolean
        data.add(reinterpret_cast<void*>(&fqdn_fwd_));

        // fqdn_rev: boolean
        data.add(reinterpret_cast<void*>(&fqdn_rev_));

        // hostname: varchar
        data.add(reinterpret_cast<void*>(&hostname_));

        // hwaddr: blob
        data.add(reinterpret_cast<void*>(&hwaddr_));

        // hwtype: int
        data.add(reinterpret_cast<void*>(&hwtype_));

        // hwaddr_source: int
        data.add(reinterpret_cast<void*>(&hwaddr_source_));

        // state: int
        data.add(reinterpret_cast<void*>(&state_));
    }

    Lease6Ptr retrieveLease() {
        try {
            // Sanity checks
            if (addr6_.size() > ADDRESS6_TEXT_MAX_LEN) {
                isc_throw(BadValue,
                          "address " << addr6_ << " of length " << addr6_.size()
                                     << " exceeds maximum allowed length of "
                                     << ADDRESS6_TEXT_MAX_LEN);
            }
            if (duid_.size() > DUID::MAX_DUID_LEN) {
                isc_throw(BadValue, "duid "
                                        << DUID(duid_).toText() << " of length "
                                        << duid_.size()
                                        << " exceeds maximum allowed length of "
                                        << DUID::MAX_DUID_LEN);
            }
            if (lease_type_ != Lease::TYPE_NA &&
                lease_type_ != Lease::TYPE_TA &&
                lease_type_ != Lease::TYPE_PD) {
                isc_throw(BadValue, "invalid lease type "
                                        << lease_type_
                                        << " for lease with address " << addr6_
                                        << ". Expected 0, 1 or 2.");
            }
            if (hostname_.size() > HOSTNAME_MAX_LEN) {
                isc_throw(BadValue, "hostname "
                                        << hostname_ << " of length "
                                        << hostname_.size()
                                        << " exceeds maximum allowed length of "
                                        << HOSTNAME_MAX_LEN);
            }
            if (hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                isc_throw(BadValue,
                          "hwaddr " << HWAddr(hwaddr_, hwtype_).toText(false)
                                    << " of length " << hwaddr_.size()
                                    << " exceeds maximum allowed length of "
                                    << HWAddr::MAX_HWADDR_LEN);
            }

            isc::asiolink::IOAddress addr(addr6_);
            DuidPtr duid(new DUID(duid_));
            HWAddrPtr hwaddr;
            if (hwaddr_.size()) {
                hwaddr.reset(new HWAddr(hwaddr_, hwtype_));
                hwaddr->source_ = hwaddr_source_;
            }

            // Create the lease and set the cltt (after converting from the
            // expire time retrieved from the database).
            Lease6Ptr result(new Lease6(
                static_cast<Lease::Type>(lease_type_), addr, duid, iaid_,
                pref_lifetime_, valid_lifetime_, 0, 0, subnet_id_, fqdn_fwd_,
                fqdn_rev_, hostname_, hwaddr, prefixlen_));

            time_t cltt = 0;
            CqlExchange::convertFromDatabaseTime(expire_, valid_lifetime_,
                                                 cltt);
            result->cltt_ = cltt;

            result->state_ = state_;
            return result;
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "createBindForReceive(): "
                      "could not convert data to Lease4, reason: "
                          << ex.what());
        }
        return Lease6Ptr();
    }

    void* retrieve() {
        isc_throw(NotImplemented, "retrieve(): Not implemented yet.");
    }

private:
    Lease6Ptr lease_;                ///< Pointer to lease object
    std::string addr6_;              ///< IPv6 address
    std::vector<cass_byte_t> duid_;  ///< Client identification
    cass_int64_t pref_lifetime_;     ///< Preferred lifetime
    cass_int32_t lease_type_;        ///< Lease type
    cass_int32_t iaid_;              ///< Identity association ID
    cass_int32_t prefixlen_;         ///< Prefix length
    cass_int32_t hwtype_;            ///< Hardware type
    cass_int32_t hwaddr_source_;     ///< Source of the hardware
                                     /// address
};

CqlLeaseMgr::CqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : LeaseMgr(), dbconn_(parameters), exchange4_(new CqlLease4Exchange()),
      exchange6_(new CqlLease6Exchange()),
      versionExchange_(new CqlVersionExchange()) {
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
    tmp << ", library cassandra_static";
    return tmp.str();
}

bool
CqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                            CqlDataArray& data,
                            CqlLeaseExchange& exchange) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (!statement) {
        isc_throw(DbOperationError,
                  "unable to bind statement "
                      << dbconn_.tagged_statements_[stindex].name_);
    }

    if (dbconn_.force_consistency_) {
        rc = cass_statement_set_consistency(statement, dbconn_.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << dbconn_.tagged_statements_[stindex].name_);
        }
    }

    CqlCommon::bindData(statement, stindex, data, exchange,
                        CqlLeaseMgr::tagged_statements_);

    future = cass_session_execute(dbconn_.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << dbconn_.tagged_statements_[stindex].name_);
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
    bool applied = exchange.hasStatementBeenApplied(future);

    // Free resources.
    cass_future_free(future);
    cass_statement_free(statement);
    return applied;
}

bool
CqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ADD_ADDR4)
        .arg(lease->addr_.toText());

    CqlDataArray data;
    exchange4_->createBindForSend(lease, data);
    return addLeaseCommon(INSERT_LEASE4, data, *exchange4_);
}

bool
CqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ADD_ADDR6)
        .arg(lease->addr_.toText());

    CqlDataArray data;
    exchange6_->createBindForSend(lease, data);
    return addLeaseCommon(INSERT_LEASE6, data, *exchange6_);
}

template <typename Exchange, typename LeaseCollection>
void
CqlLeaseMgr::getLeaseCollection(StatementIndex stindex,
                                CqlDataArray& data,
                                Exchange& exchange,
                                LeaseCollection& result,
                                bool single) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_ADDR4)
        .arg(dbconn_.tagged_statements_[stindex].name_);

    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (!statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    if (dbconn_.force_consistency_) {
        rc = cass_statement_set_consistency(statement, dbconn_.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << dbconn_.tagged_statements_[stindex].name_);
        }
    }

    CqlCommon::bindData(statement, stindex, data,
                        static_cast<SqlExchange>(*exchange),
                        CqlLeaseMgr::tagged_statements_);

    future = cass_session_execute(dbconn_.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << dbconn_.tagged_statements_[stindex].name_);
    }
    cass_future_wait(future);
    std::string error;
    std::stringstream message;
    message << "unable to GET using statement "
            << CqlLeaseMgr::tagged_statements_[stindex].name_;
    dbconn_.checkStatementError(error, future, message.str().c_str());
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
        CqlDataArray data;
        exchange->createBindForReceive(data);
        // Get data.
        for (size_t i = 0U; i < data.size(); i++) {
            CqlCommon::getData(row, i, i, *exchange, data);
        }
        result.push_back(exchange->retrieveLease());
    }

    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);
    if (single && rowCount > 1) {
        isc_throw(MultipleRecords,
                  "multiple records were found in the "
                  "database where only one was expected for statement "
                      << dbconn_.tagged_statements_[stindex].name_);
    }
}

void
CqlLeaseMgr::getLease(StatementIndex stindex,
                      CqlDataArray& data,
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
CqlLeaseMgr::getLease(StatementIndex stindex,
                      CqlDataArray& data,
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
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_ADDR4)
        .arg(addr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    cass_int32_t addr4_data = static_cast<cass_int32_t>(addr.toUint32());
    data.add(reinterpret_cast<void*>(&addr4_data));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, data, result);

    return result;
}

Lease4Collection
CqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_HWADDR)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<cass_byte_t> hwaddr_data = hwaddr.hwaddr_;
    data.add(reinterpret_cast<void*>(&hwaddr_data));

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, data, result);

    return result;
}

Lease4Ptr
CqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SUBID_HWADDR)
        .arg(subnet_id)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<cass_byte_t> hwaddr_data = hwaddr.hwaddr_;
    data.add(reinterpret_cast<void*>(&hwaddr_data));

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(reinterpret_cast<void*>(&subnet_id_data));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, data, result);

    return result;
}

Lease4Collection
CqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_CLIENTID)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<cass_byte_t> client_id_data = clientid.getClientId();
    data.add(reinterpret_cast<void*>(&client_id_data));

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, data, result);

    return result;
}

Lease4Ptr
CqlLeaseMgr::getLease4(const ClientId& clientid,
                       const HWAddr& hwaddr,
                       SubnetID subnet_id) const {
    /// This method is currently not implemented because allocation engine
    /// searches for the lease using HW address or client identifier.
    /// It never uses both parameters in the same time. We need to
    /// consider if this method is needed at all.
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_CLIENTID_HWADDR_SUBID)
        .arg(clientid.toText())
        .arg(hwaddr.toText())
        .arg(subnet_id);

    isc_throw(NotImplemented, "The CqlLeaseMgr::getLease4 method was"
                              " called, but it is not implemented");
}

Lease4Ptr
CqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SUBID_CLIENTID)
        .arg(subnet_id)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<uint8_t> client_id_data = clientid.getClientId();
    data.add(reinterpret_cast<void*>(&client_id_data));

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(reinterpret_cast<void*>(&subnet_id_data));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, data, result);

    return result;
}

Lease6Ptr
CqlLeaseMgr::getLease6(Lease::Type lease_type,
                       const isc::asiolink::IOAddress& addr) const {
    std::string addr_data = addr.toText();
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_ADDR6)
        .arg(addr_data)
        .arg(lease_type);

    // Set up the WHERE clause value
    CqlDataArray data;

    if (addr_data.size() > ADDRESS6_TEXT_MAX_LEN) {
        isc_throw(BadValue, "getLease6(): "
                            "address "
                                << addr_data << " of length "
                                << addr_data.size()
                                << " exceeds maximum allowed length of "
                                << ADDRESS6_TEXT_MAX_LEN);
    }
    data.add(reinterpret_cast<void*>(&addr_data));

    cass_int32_t lease_type_data = static_cast<cass_int32_t>(lease_type);
    data.add(reinterpret_cast<void*>(&lease_type_data));

    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, data, result);

    return result;
}

Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type,
                        const DUID& duid,
                        uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_IAID_DUID)
        .arg(iaid)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<cass_byte_t> duid_data = duid.getDuid();
    data.add(reinterpret_cast<void*>(&duid_data));

    cass_int32_t iaid_data = static_cast<cass_int32_t>(iaid);
    data.add(reinterpret_cast<void*>(&iaid_data));

    cass_int32_t lease_type_data = static_cast<cass_int32_t>(lease_type);
    data.add(reinterpret_cast<void*>(&lease_type_data));

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, data, result);

    return result;
}

Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type,
                        const DUID& duid,
                        uint32_t iaid,
                        SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_IAID_SUBID_DUID)
        .arg(iaid)
        .arg(subnet_id)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    CqlDataArray data;

    std::vector<cass_byte_t> duid_data = duid.getDuid();
    data.add(reinterpret_cast<void*>(&duid_data));

    cass_int32_t iaid_data = static_cast<cass_int32_t>(iaid);
    data.add(reinterpret_cast<void*>(&iaid_data));

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(reinterpret_cast<void*>(&subnet_id_data));

    cass_int32_t lease_type_data = static_cast<cass_int32_t>(lease_type);
    data.add(reinterpret_cast<void*>(&lease_type_data));

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, data, result);

    return result;
}

void
CqlLeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                               const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_EXPIRED6)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE6_EXPIRE);
}

void
CqlLeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                               const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_EXPIRED4)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE4_EXPIRE);
}

template <typename LeaseCollection>
void
CqlLeaseMgr::getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                    const size_t max_leases,
                                    StatementIndex statement_index) const {
    // Set up the WHERE clause value
    cass_int32_t keepState = Lease::STATE_EXPIRED_RECLAIMED;
    cass_int64_t timestamp = static_cast<cass_int64_t>(time(NULL));

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    cass_int32_t limit = max_leases > 0 ?
                             static_cast<cass_int32_t>(max_leases) :
                             std::numeric_limits<cass_int32_t>::max();

    for (cass_int32_t state = Lease::STATE_DEFAULT;
         state <= Lease::STATE_EXPIRED_RECLAIMED; state++) {
        if (state == keepState) {
            continue;
        }
        LeaseCollection tempCollection;
        CqlDataArray data;

        data.add(reinterpret_cast<void*>(&state));
        data.add(reinterpret_cast<void*>(&timestamp));
        data.add(reinterpret_cast<void*>(&limit));

        // Retrieve leases from the database.
        getLeaseCollection(statement_index, data, tempCollection);

        typedef typename LeaseCollection::iterator LeaseCollectionIt;

        for (LeaseCollectionIt it = tempCollection.begin();
             it != tempCollection.end(); ++it) {
            expired_leases.push_back((*it));
        }
    }
}

void
CqlLeaseMgr::updateLeaseCommon(StatementIndex stindex,
                               CqlDataArray& data,
                               CqlLeaseExchange& exchange) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ADD_ADDR4)
        .arg(dbconn_.tagged_statements_[stindex].name_);

    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (!statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    if (dbconn_.force_consistency_) {
        rc = cass_statement_set_consistency(statement, dbconn_.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << dbconn_.tagged_statements_[stindex].name_);
        }
    }

    CqlCommon::bindData(statement, stindex, data, exchange,
                        CqlLeaseMgr::tagged_statements_);

    future = cass_session_execute(dbconn_.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << dbconn_.tagged_statements_[stindex].name_);
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
    size_t row_count;
    size_t column_count;
    bool applied =
        exchange.hasStatementBeenApplied(future, &row_count, &column_count);

    // Free resources.
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
              DHCPSRV_CQL_UPDATE_ADDR4)
        .arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    CqlDataArray data;
    exchange4_->createBindForSend(lease, data);
    data.remove(0);

    // Set up the WHERE clause and append it to the bind array.
    cass_int32_t addr4_data =
        static_cast<cass_int32_t>(lease->addr_.toUint32());
    data.add(reinterpret_cast<void*>(&addr4_data));

    // Drop to common update code
    updateLeaseCommon(stindex, data, *exchange4_);
}

void
CqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;
    std::string lease_addr_data = lease->addr_.toText();
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_UPDATE_ADDR6)
        .arg(lease_addr_data);

    // Create the BIND array for the data being updated
    CqlDataArray data;
    exchange6_->createBindForSend(lease, data);
    data.remove(0);

    // Set up the WHERE clause and append it to the BIND array
    if (lease_addr_data.size() > ADDRESS6_TEXT_MAX_LEN) {
        isc_throw(BadValue, "updateLease6(): "
                            "address "
                                << lease_addr_data << " of length "
                                << lease_addr_data.size()
                                << " exceeds maximum allowed length "
                                   "of "
                                << ADDRESS6_TEXT_MAX_LEN);
    }
    data.add(reinterpret_cast<void*>(&lease_addr_data));

    // Drop to common update code
    updateLeaseCommon(stindex, data, *exchange6_);
}

bool
CqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex,
                               CqlDataArray& data,
                               CqlLeaseExchange& exchange) {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[stindex]);
    if (!statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    if (dbconn_.force_consistency_) {
        rc = cass_statement_set_consistency(statement, dbconn_.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << dbconn_.tagged_statements_[stindex].name_);
        }
    }

    CqlCommon::bindData(statement, stindex, data, exchange,
                        CqlLeaseMgr::tagged_statements_);

    future = cass_session_execute(dbconn_.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << dbconn_.tagged_statements_[stindex].name_);
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
    bool applied = exchange.hasStatementBeenApplied(future);

    // Free resources.
    cass_future_free(future);
    cass_statement_free(statement);

    return applied;
}

bool
CqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    std::string addr_data = addr.toText();
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_DELETE_ADDR)
        .arg(addr_data);

    // Set up the WHERE clause value
    CqlDataArray data;

    if (addr.isV4()) {
        cass_int32_t addr4_data = static_cast<cass_int32_t>(addr.toUint32());
        data.add(reinterpret_cast<void*>(&addr4_data));
        return deleteLeaseCommon(DELETE_LEASE4, data, *exchange4_);
    } else {
        if (addr_data.size() > ADDRESS6_TEXT_MAX_LEN) {
            isc_throw(BadValue, "deleteLease(): "
                                "address "
                                    << addr_data << " of length "
                                    << addr_data.size()
                                    << " exceeds maximum allowed length "
                                       "of "
                                    << ADDRESS6_TEXT_MAX_LEN);
        }
        data.add(reinterpret_cast<void*>(&addr_data));
        return deleteLeaseCommon(DELETE_LEASE6, data, *exchange6_);
    }
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    return deleteExpiredReclaimedLeasesCommon(secs,
                                              DELETE_LEASE4_STATE_EXPIRED);
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    return deleteExpiredReclaimedLeasesCommon(secs,
                                              DELETE_LEASE6_STATE_EXPIRED);
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeasesCommon(
    const uint32_t secs, StatementIndex statement_index) {
    // Set up the WHERE clause value

    CqlDataArray data;
    uint64_t result = 0;

    // State is reclaimed.
    cass_int32_t state =
        static_cast<cass_int32_t>(Lease::STATE_EXPIRED_RECLAIMED);
    data.add(reinterpret_cast<void*>(&state));

    // Expiration timestamp.
    cass_int64_t expiration =
        static_cast<cass_int64_t>(time(NULL) - static_cast<time_t>(secs));
    data.add(reinterpret_cast<void*>(&expiration));

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
    return result;
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
    return name;
}

std::string
CqlLeaseMgr::getDescription() const {
    return std::string("Cassandra Database");
}

std::pair<unsigned int, unsigned int>
CqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_VERSION);
    cass_int32_t version;
    cass_int32_t minor;
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;

    statement = cass_prepared_bind(dbconn_.statements_[GET_VERSION]);
    if (!statement) {
        isc_throw(DbOperationError, "unable to bind statement");
    }

    if (dbconn_.force_consistency_) {
        rc = cass_statement_set_consistency(statement, dbconn_.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(
                DbOperationError,
                "unable to set statement consistency for statement "
                    << dbconn_.tagged_statements_[GET_VERSION].name_);
        }
    }

    future = cass_session_execute(dbconn_.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "unable to execute statement "
                      << dbconn_.tagged_statements_[GET_VERSION].name_);
    }
    cass_future_wait(future);
    std::string error;
    dbconn_.checkStatementError(error, future, "unable to GET version");
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
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        // version: int
        data.add(reinterpret_cast<void*>(&version));
        // minor: int
        data.add(reinterpret_cast<void*>(&minor));
        for (size_t i = 0U; i < data.size(); i++) {
            CqlCommon::getData(row, i, i, *versionExchange_, data);
        }
    }

    cass_iterator_free(rows);
    cass_result_free(resultCollection);
    cass_future_free(future);
    cass_statement_free(statement);

    return std::pair<unsigned int, unsigned int>(
        static_cast<unsigned int>(version), static_cast<unsigned int>(minor));
}

void
CqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);
    dbconn_.commit();
}

void
CqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);
    dbconn_.rollback();
}

}  // namespace dhcp
}  // namespace isc
