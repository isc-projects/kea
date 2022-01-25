// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2015-2018 Deutsche Telekom AG.
//
// Authors: Razvan Becheriu <razvan.becheriu@qualitance.com>
//          Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <dhcpsrv/cql_lease_mgr.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>

#include <asiolink/io_address.h>
#include <boost/make_shared.hpp>

using namespace isc::data;
using namespace isc::db;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

static constexpr size_t HOSTNAME_MAX_LEN = 255u;
static constexpr size_t ADDRESS6_TEXT_MAX_LEN = 39u;
static constexpr char NULL_USER_CONTEXT[] = "";

/// @brief Common CQL and Lease Data Methods
///
/// The @ref CqlLease4Exchange and @ref CqlLease6Exchange classes provide the
/// functionality to set up binding information between variables in the
/// program and data extracted from the database. This class is the common
/// base to both of them, containing some common methods.
class CqlLeaseExchange : public CqlExchange {
public:

    /// @brief Constructor
    ///
    /// @param connection already open Cassandra connection.
    CqlLeaseExchange(const CqlConnection &connection)
        : connection_(connection), valid_lifetime_(0), expire_(0),
          current_expire_(0), subnet_id_(0), fqdn_fwd_(cass_false),
          fqdn_rev_(cass_false), state_(0), user_context_(NULL_USER_CONTEXT) {
    }

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeSelect() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statement_tag prepared statement being executed; defaults to an
    ///     invalid index
    virtual void
    createBindForSelect(AnyArray &data, StatementTag statement_tag = NULL) override = 0;

    /// @brief Copy received data into the derived class' object.
    ///
    /// Copies information about the entity to be retrieved into a holistic
    /// object. Called in @ref executeSelect(). Not implemented for base class
    /// CqlExchange. To be implemented in derived classes.
    ///
    /// @return a pointer to the object retrieved.
    virtual boost::any retrieve() override = 0;

protected:

    /// @brief Database connection
    const CqlConnection &connection_;

    /// @brief Hardware address
    CassBlob hwaddr_;

    /// @brief Lease timer
    cass_int64_t valid_lifetime_;

    /// @brief Lease expiry time
    cass_int64_t expire_;

    /// @brief Expiration time of lease before update
    cass_int64_t current_expire_;

    /// @brief Subnet identifier
    cass_int32_t subnet_id_;

    /// @brief Has forward DNS update been performed?
    cass_bool_t fqdn_fwd_;

    /// @brief Has reverse DNS update been performed?
    cass_bool_t fqdn_rev_;

    /// @brief Client hostname
    std::string hostname_;

    /// @brief Lease state
    cass_int32_t state_;

    /// @brief User context
    std::string user_context_;
};

/// @brief Exchange Lease4 information between Kea and CQL
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
    /// The initialization of the variables here is only to satisfy
    /// cppcheck - all variables are initialized/set in the methods before
    /// they are used.
    ///
    /// @param connection connection used for this query
    explicit CqlLease4Exchange(const CqlConnection &connection);

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease4 object to
    /// the database. Used for INSERT statements.
    ///
    /// @param lease The lease information to be inserted
    /// @param data Lease info will be stored here in CQL format
    void createBindForInsert(const Lease4Ptr &lease, AnyArray &data);

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease4 object to
    /// the database. Used for UPDATE statements.
    ///
    /// @param lease Updated lease information.
    /// @param data lease info in CQL format will be stored here
    /// @param statement_tag tag identifying the query (optional)
    void createBindForUpdate(const Lease4Ptr &lease, AnyArray &data,
                             StatementTag statement_tag = NULL);

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease4 object to
    /// the database. Used for DELETE statements.
    ///
    /// @param lease Deleted lease information.
    /// @param data lease info in CQL format will be stored here
    /// @param statement_tag tag identifying the query (optional)
    void createBindForDelete(const Lease4Ptr &lease,
                             AnyArray &data,
                             StatementTag statement_tag = NULL);

    /// @brief Create BIND array to receive data
    ///
    /// Creates a CQL_BIND array to receive Lease4 data from the database.
    ///
    /// @param data info returned by CQL will be stored here
    /// @param statement_tag tag identifying the query (optional)
    virtual void
    createBindForSelect(AnyArray &data, StatementTag statement_tag = NULL) override;

    /// @brief Retrieves the Lease4 object in Kea format
    ///
    /// @return C++ representation of the object being returned
    virtual boost::any retrieve() override;

    /// @brief Retrieves zero or more IPv4 leases
    ///
    /// @param statement_tag query to be executed
    /// @param data parameters for the query
    /// @param result this lease collection will be updated
    void getLeaseCollection(StatementTag &statement_tag, AnyArray &data,
                            Lease4Collection &result);

    /// @brief Retrieves one IPv4 lease
    ///
    /// @param statement_tag query to be executed
    /// @param data parameters for the query
    /// @param result pointer to the lease being returned (or null)
    void
    getLease(StatementTag &statement_tag, AnyArray &data, Lease4Ptr &result);

    /// @brief Returns expired leases.
    ///
    /// This method returns up to specified number (see max_leases) of
    /// expired leases.
    ///
    /// @param max_leases at most this number of leases will be returned
    /// @param expired_leases expired leases will be stored here
    void getExpiredLeases(const size_t &max_leases, Lease4Collection &expired_leases);

    /// @brief Cassandra statements
    static StatementMap tagged_statements_;

    /// @brief Statement tags definitions
    /// @{
    // Add entry to lease4 table
    static constexpr StatementTag INSERT_LEASE4 = "INSERT_LEASE4";
    // Update a Lease4 entry
    static constexpr StatementTag UPDATE_LEASE4 = "UPDATE_LEASE4";
    // Delete from lease4 by address
    static constexpr StatementTag DELETE_LEASE4 = "DELETE_LEASE4";
    // Delete expired lease4s in certain state
    static constexpr StatementTag GET_LEASE4_EXPIRE = "GET_LEASE4_EXPIRE";
    // Get lease4
    static constexpr StatementTag GET_LEASE4 = "GET_LEASE4";
    // Get lease4 by address
    static constexpr StatementTag GET_LEASE4_ADDR = "GET_LEASE4_ADDR";
    // Get lease4 by client ID
    static constexpr StatementTag GET_LEASE4_CLIENTID = "GET_LEASE4_CLIENTID";
    // Get lease4 by client ID & subnet ID
    static constexpr StatementTag GET_LEASE4_CLIENTID_SUBID = "GET_LEASE4_CLIENTID_SUBID";
    // Get lease4 by HW address
    static constexpr StatementTag GET_LEASE4_HWADDR = "GET_LEASE4_HWADDR";
    // Get lease4 by HW address & subnet ID
    static constexpr StatementTag GET_LEASE4_HWADDR_SUBID = "GET_LEASE4_HWADDR_SUBID";
    // Get range of lease4 from first lease with a limit
    static constexpr StatementTag GET_LEASE4_LIMIT = "GET_LEASE4_LIMIT";
    // Get range of lease4 from address with limit (paging)
    static constexpr StatementTag GET_LEASE4_PAGE = "GET_LEASE4_PAGE";
    // Get lease4 by subnet ID
    static constexpr StatementTag GET_LEASE4_SUBID = "GET_LEASE4_SUBID";
    // Get lease4 by hostname
    static constexpr StatementTag GET_LEASE4_HOSTNAME = "GET_LEASE4_HOSTNAME";
    /// @}

private:

    // Pointer to lease object
    Lease4Ptr lease_;
    // IPv4 address
    cass_int32_t address_;
    // Client identification
    CassBlob client_id_;
};  // CqlLease4Exchange

constexpr StatementTag CqlLease4Exchange::INSERT_LEASE4;
constexpr StatementTag CqlLease4Exchange::UPDATE_LEASE4;
constexpr StatementTag CqlLease4Exchange::DELETE_LEASE4;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_EXPIRE;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_ADDR;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_CLIENTID;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_CLIENTID_SUBID;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_HWADDR;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_HWADDR_SUBID;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_LIMIT;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_PAGE;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_SUBID;
constexpr StatementTag CqlLease4Exchange::GET_LEASE4_HOSTNAME;

StatementMap CqlLease4Exchange::tagged_statements_{

    // Inserts new IPv4 lease
    {INSERT_LEASE4,
     {INSERT_LEASE4,
      "INSERT INTO lease4( "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      ") VALUES ( "
      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? "
      ") "
      "IF NOT EXISTS "
     }},

    // Updates existing IPv4 lease
    {UPDATE_LEASE4,
     {UPDATE_LEASE4,
      "UPDATE lease4 SET "
      "hwaddr = ?, "
      "client_id = ?, "
      "subnet_id = ?, "
      "valid_lifetime = ?, "
      "expire = ?, "
      "fqdn_fwd = ?, "
      "fqdn_rev = ?, "
      "hostname = ?, "
      "state = ?, "
      "user_context = ? "
      "WHERE address = ? "
      "IF expire = ? "
     }},

    // Deletes existing IPv4 lease
    {DELETE_LEASE4,
     {DELETE_LEASE4,
      "DELETE FROM lease4 "
      "WHERE address = ? "
      "IF expire = ? "
     }},

    // Gets up to a certain number of expired IPv4 leases
    {GET_LEASE4_EXPIRE,
     {GET_LEASE4_EXPIRE,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE state = ? "
      "AND valid_lifetime < 4294967295 "
      "AND expire < ? "
      "LIMIT ? "
      "ALLOW FILTERING "
     }},

     // Gets an IPv4 lease(s)
     {GET_LEASE4,
      {GET_LEASE4,
       "SELECT "
       "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
       "fqdn_fwd, fqdn_rev, hostname, state, user_context "
       "FROM lease4 "
     }},

    // Gets an IPv4 lease with specified IPv4 address
    {GET_LEASE4_ADDR,
     {GET_LEASE4_ADDR,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE address = ? "
     }},

    // Gets an IPv4 lease(s) with specified client-id
    {GET_LEASE4_CLIENTID,
     {GET_LEASE4_CLIENTID,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE client_id = ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv4 lease with specified client-id and subnet-id
    {GET_LEASE4_CLIENTID_SUBID,
     {GET_LEASE4_CLIENTID_SUBID,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE client_id = ? "
      "AND subnet_id = ? "
      "ALLOW FILTERING "
     }},

    // Gets all IPv4 leases with specified hardware address
    {GET_LEASE4_HWADDR,
     {GET_LEASE4_HWADDR,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE hwaddr = ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv4 lease with specified hardware addr and subnet-id
    {GET_LEASE4_HWADDR_SUBID,
     {GET_LEASE4_HWADDR_SUBID,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE hwaddr = ? "
      "AND subnet_id = ? "
      "ALLOW FILTERING "
     }},

    // Get range of lease4 from first lease with a limit (paging)
    {GET_LEASE4_LIMIT,
     {GET_LEASE4_LIMIT,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "LIMIT ? "
      "ALLOW FILTERING "
     }},

    // Get range of lease4 from address with a limit (paging)
    {GET_LEASE4_PAGE,
     {GET_LEASE4_PAGE,
      "SELECT "
      "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
      "fqdn_fwd, fqdn_rev, hostname, state, user_context "
      "FROM lease4 "
      "WHERE TOKEN(address) > TOKEN(?) "
      "LIMIT ? "
      "ALLOW FILTERING "
     }},

     // Gets an IPv4 lease(s) with specified subnet-id
     {GET_LEASE4_SUBID,
      {GET_LEASE4_SUBID,
       "SELECT "
       "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
       "fqdn_fwd, fqdn_rev, hostname, state, user_context "
       "FROM lease4 "
       "WHERE subnet_id = ? "
       "ALLOW FILTERING "}},

     // Gets an IPv4 lease(s) with specified hostname
     {GET_LEASE4_HOSTNAME,
      {GET_LEASE4_HOSTNAME,
       "SELECT "
       "address, hwaddr, client_id, valid_lifetime, expire, subnet_id, "
       "fqdn_fwd, fqdn_rev, hostname, state, user_context "
       "FROM lease4 "
       "WHERE hostname = ? "
       "ALLOW FILTERING "
     }}
};

CqlLease4Exchange::CqlLease4Exchange(const CqlConnection &connection)
    : CqlLeaseExchange(connection), address_(0) {
}

void
CqlLease4Exchange::createBindForInsert(const Lease4Ptr &lease, AnyArray &data) {
    if (!lease) {
        isc_throw(BadValue, "CqlLease4Exchange::createBindForInsert(): "
                            "Lease4 object is NULL");
    }
    // Store lease object to ensure it remains valid.
    lease_ = lease;
    // Set up the structures for the various components of the lease4
    // structure.

    try {
        // address: int
        // The address in the Lease structure is an IOAddress object.
        // Convert this to an integer for storage.
        address_ = static_cast<cass_int32_t>(lease->addr_.toUint32());

        // hwaddr: blob
        if (lease_->hwaddr_ && lease_->hwaddr_->hwaddr_.size() > 0) {
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

        // client_id: blob
        if (lease_->client_id_ && lease_->client_id_->getClientId().size() > 0) {
            client_id_ = lease_->client_id_->getClientId();
        } else {
            client_id_.clear();
        }

        // valid lifetime: bigint
        valid_lifetime_ = static_cast<cass_int64_t>(lease_->valid_lft_);

        // expire: bigint
        // The lease structure holds the client last transmission time
        /// (cltt_)
        // For convenience for external tools, this is converted to lease
        // expiry time (expire). The relationship is given by:
        // expire = cltt_ + valid_lft_
        CqlExchange::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                           expire_);

        // subnet_id: int
        subnet_id_ = static_cast<cass_int32_t>(lease_->subnet_id_);

        // fqdn_fwd: boolean
        fqdn_fwd_ = lease_->fqdn_fwd_ ? cass_true : cass_false;

        // fqdn_rev: boolean
        fqdn_rev_ = lease_->fqdn_rev_ ? cass_true : cass_false;

        // hostname: varchar
        if (lease_->hostname_.size() > HOSTNAME_MAX_LEN) {
            isc_throw(BadValue,
                      "hostname " << lease_->hostname_ << " of length "
                                  << lease_->hostname_.size()
                                  << " exceeds maximum allowed length of "
                                  << HOSTNAME_MAX_LEN);
        }
        hostname_ = lease_->hostname_;

        // state: int
        state_ = static_cast<cass_int32_t>(lease_->state_);

        // user_context: text
        ConstElementPtr ctx = lease_->getContext();
        if (ctx) {
            user_context_ = ctx->str();
        } else {
            user_context_ = NULL_USER_CONTEXT;
        }

        // Start with a fresh array.
        data.clear();
        data.add(&address_);
        data.add(&hwaddr_);
        data.add(&client_id_);
        data.add(&valid_lifetime_);
        data.add(&expire_);
        data.add(&subnet_id_);
        data.add(&fqdn_fwd_);
        data.add(&fqdn_rev_);
        data.add(&hostname_);
        data.add(&state_);
        data.add(&user_context_);

    } catch (const Exception &ex) {
        isc_throw(DbOperationError, "CqlLease4Exchange::createBindForInsert(): "
                  "could not create bind array from Lease4: " << lease_->addr_.toText()
                  << ", reason: " << ex.what());
    }
}

void
CqlLease4Exchange::createBindForUpdate(const Lease4Ptr &lease, AnyArray &data,
                                       StatementTag /* unused */) {
    if (!lease) {
        isc_throw(BadValue, "CqlLease4Exchange::createBindForUpdate(): "
                            "Lease4 object is NULL");
    }
    // Store lease object to ensure it remains valid.
    lease_ = lease;
    // Set up the structures for the various components of the lease4
    // structure.

    try {
        // address: int
        // The address in the Lease structure is an IOAddress object.
        // Convert this to an integer for storage.
        address_ = static_cast<cass_int32_t>(lease->addr_.toUint32());

        // hwaddr: blob
        if (lease_->hwaddr_ && lease_->hwaddr_->hwaddr_.size() > 0) {
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

        // client_id: blob
        if (lease_->client_id_ && lease_->client_id_->getClientId().size() > 0) {
            client_id_ = lease_->client_id_->getClientId();
        } else {
            client_id_.clear();
        }

        // valid lifetime: bigint
        valid_lifetime_ = static_cast<cass_int64_t>(lease_->valid_lft_);

        // expire: bigint
        // The lease structure holds the client last transmission time
        /// (cltt_)
        // For convenience for external tools, this is converted to lease
        // expiry time (expire). The relationship is given by:
        // expire = cltt_ + valid_lft_
        CqlExchange::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                           expire_);

        // subnet_id: int
        subnet_id_ = static_cast<cass_int32_t>(lease_->subnet_id_);

        // fqdn_fwd: boolean
        fqdn_fwd_ = lease_->fqdn_fwd_ ? cass_true : cass_false;

        // fqdn_rev: boolean
        fqdn_rev_ = lease_->fqdn_rev_ ? cass_true : cass_false;

        // hostname: varchar
        if (lease_->hostname_.size() > HOSTNAME_MAX_LEN) {
            isc_throw(BadValue,
                      "hostname " << lease_->hostname_ << " of length "
                                  << lease_->hostname_.size()
                                  << " exceeds maximum allowed length of "
                                  << HOSTNAME_MAX_LEN);
        }
        hostname_ = lease_->hostname_;

        // state: int
        state_ = static_cast<cass_int32_t>(lease_->state_);

        // user_context: text
        ConstElementPtr ctx = lease_->getContext();
        if (ctx) {
            user_context_ = ctx->str();
        } else {
            user_context_ = NULL_USER_CONTEXT;
        }

        // Start with a fresh array.
        data.clear();
        data.add(&hwaddr_);
        data.add(&client_id_);
        data.add(&subnet_id_);
        data.add(&valid_lifetime_);
        data.add(&expire_);
        data.add(&fqdn_fwd_);
        data.add(&fqdn_rev_);
        data.add(&hostname_);
        data.add(&state_);
        data.add(&user_context_);
        data.add(&address_);

        CqlExchange::convertToDatabaseTime(lease_->current_cltt_,
                                           lease_->current_valid_lft_,
                                           current_expire_);
        data.add(&current_expire_);
    } catch (const Exception &ex) {
        isc_throw(DbOperationError,
                  "CqlLease4Exchange::createBindUpdate(): "
                  "could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
    }
}

void
CqlLease4Exchange::createBindForDelete(const Lease4Ptr &lease, AnyArray &data,
                                       StatementTag /* unused */) {
    if (!lease) {
        isc_throw(BadValue, "CqlLease4Exchange::createBindForDelete(): "
                            "Lease4 object is NULL");
    }
    // Store lease object to ensure it remains valid.
    lease_ = lease;

    // Set up the structures for the various components of the lease4
    // structure.
    try {
        // address: int
        address_ = static_cast<cass_int32_t>(lease_->addr_.toUint32());

        // Start with a fresh array.
        data.clear();
        data.add(&address_);

        CqlExchange::convertToDatabaseTime(lease_->current_cltt_,
                                           lease_->current_valid_lft_,
                                           current_expire_);
        data.add(&current_expire_);
    } catch (const Exception &ex) {
        isc_throw(DbOperationError,
                  "CqlLease4Exchange::createBindForDelete(): "
                  "could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
    }
}

void
CqlLease4Exchange::createBindForSelect(AnyArray &data, StatementTag /* unused */) {
    // Start with a fresh array.
    data.clear();

    // address: blob
    data.add(&address_);

    // hwaddr: blob
    data.add(&hwaddr_);

    // client_id: blob
    data.add(&client_id_);

    // valid_lifetime: bigint
    data.add(&valid_lifetime_);

    // expire: bigint
    data.add(&expire_);

    // subnet_id: int
    data.add(&subnet_id_);

    // fqdn_fwd: boolean
    data.add(&fqdn_fwd_);

    // fqdn_rev: boolean
    data.add(&fqdn_rev_);

    // hostname: varchar
    data.add(&hostname_);

    // state: int
    data.add(&state_);

    // user_context: text
    data.add(&user_context_);
}

boost::any
CqlLease4Exchange::retrieve() {
    try {
        // Sanity checks
        if (hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
            isc_throw(BadValue,
                      "hardware address "
                          << HWAddr(hwaddr_, HTYPE_ETHER).toText()
                          << " of length " << hwaddr_.size()
                          << " exceeds maximum allowed length of "
                          << HWAddr::MAX_HWADDR_LEN);
        }
        if (client_id_.size() > ClientId::MAX_CLIENT_ID_LEN) {
            isc_throw(BadValue,
                      "client ID " << ClientId(client_id_).toText()
                                   << " of length " << client_id_.size()
                                   << " exceeds maximum allowed length of "
                                   << ClientId::MAX_CLIENT_ID_LEN);
        }
        if (hostname_.size() > HOSTNAME_MAX_LEN) {
            isc_throw(BadValue,
                      "hostname" << hostname_ << " of length "
                                 << hostname_.size()
                                 << " exceeds maximum allowed length of "
                                 << HOSTNAME_MAX_LEN);
        }

        time_t cltt = 0;
        CqlExchange::convertFromDatabaseTime(expire_, valid_lifetime_, cltt);

        HWAddrPtr hwaddr = boost::make_shared<HWAddr>(hwaddr_, HTYPE_ETHER);

        uint32_t addr4 = static_cast<uint32_t>(address_);

        ConstElementPtr ctx;
        if (!user_context_.empty()) {
            ctx = Element::fromJSON(user_context_);
            if (!ctx || (ctx->getType() != Element::map)) {
                isc_throw(BadValue, "user context '" << user_context_
                          << "' is not a JSON map");
            }
        }

        Lease4Ptr result(boost::make_shared<Lease4>(addr4, hwaddr, client_id_.data(),
                                                    client_id_.size(), valid_lifetime_,
                                                    cltt, subnet_id_, fqdn_fwd_, fqdn_rev_,
                                                    hostname_));

        result->state_ = state_;

        if (ctx) {
            result->setContext(ctx);
        }

        return (result);
    } catch (const Exception &ex) {
        isc_throw(DbOperationError,
                  "CqlLease4Exchange::retrieve(): "
                  "could not convert data to Lease4, reason: "
                      << ex.what());
    }
}

void
CqlLease4Exchange::getLeaseCollection(StatementTag &statement_tag, AnyArray &data,
                                      Lease4Collection &result) {
    AnyArray collection = executeSelect(connection_, data, statement_tag);

    // Transfer Lease4 objects to result.
    for (boost::any &element : collection) {
        result.push_back(boost::any_cast<Lease4Ptr>(element));
    }
}

void
CqlLease4Exchange::getLease(StatementTag &statement_tag, AnyArray &data,
                            Lease4Ptr &result) {
    // This particular method is called when only one or zero matches is
    // expected.
    Lease4Collection collection;
    getLeaseCollection(statement_tag, data, collection);

    // Return single record if present, else clear the lease.
    const size_t collection_size = collection.size();
    if (collection_size >= 2u) {
        isc_throw(MultipleRecords,
                  "CqlLease4Exchange::getLease(): multiple records were found in "
                  "the database where only one was expected for statement "
                  << statement_tag);
    } else if (collection_size == 0u) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
CqlLease4Exchange::getExpiredLeases(const size_t &max_leases,
                                    Lease4Collection &expired_leases) {
    // Set up the WHERE clause value
    cass_int32_t keep_state = Lease::STATE_EXPIRED_RECLAIMED;
    cass_int64_t timestamp = static_cast<cass_int64_t>(time(NULL));

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    cass_int32_t limit = max_leases > 0u ? static_cast<cass_int32_t>(max_leases) :
                                           std::numeric_limits<cass_int32_t>::max();

    for (cass_int32_t state = Lease::STATE_DEFAULT;
         state <= Lease::STATE_EXPIRED_RECLAIMED; ++state) {
        if (state == keep_state) {
            continue;
        }

        AnyArray data;
        data.add(&state);
        data.add(&timestamp);
        data.add(&limit);

        // Retrieve leases from the database.
        Lease4Collection temp_collection;
        getLeaseCollection(CqlLease4Exchange::GET_LEASE4_EXPIRE, data,
                           temp_collection);

        for (Lease4Ptr &lease : temp_collection) {
            expired_leases.push_back(lease);
        }
    }
}

/// @brief Exchange Lease6 information between Kea and CQL
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
    /// The initialization of the variables here is only to satisfy
    /// cppcheck - all variables are initialized/set in the methods before
    /// they are used.
    ///
    /// @param connection connection used for this query
    explicit CqlLease6Exchange(const CqlConnection &connection);

    /// @brief Create CQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease6 object to
    /// the database. Used for INSERT statements.
    ///
    /// @param lease The lease information to be inserted
    /// @param data Lease info will be stored here in CQL format
    void createBindForInsert(const Lease6Ptr &lease, AnyArray &data);

    /// @brief Create CQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease6 object to
    /// the database. Used for UPDATE statements.
    ///
    /// @param lease Updated lease information.
    /// @param data lease info in CQL format will be stored here
    /// @param statement_tag tag identifying the query (optional)
    void createBindForUpdate(const Lease6Ptr &lease, AnyArray &data,
                             StatementTag statement_tag = NULL);

    /// @brief Create CQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the CQL_BIND array for sending data in the Lease6 object to
    /// the database. Used for DELETE statements.
    ///
    /// @param lease address of the lease to be deleted
    /// @param data lease info in CQL format will be stored here
    /// @param statement_tag tag identifying the query (optional)
    void createBindForDelete(const Lease6Ptr &lease,
                             AnyArray &data,
                             StatementTag statement_tag = NULL);

    /// @brief Create BIND array to receive data
    ///
    /// Creates a CQL_BIND array to receive Lease6 data from the database.
    ///
    /// @param data info returned by CQL will be stored here
    /// @param statement_tag tag identifying the query (optional)
    virtual void
    createBindForSelect(AnyArray &data, StatementTag statement_tag = NULL) override;

    /// @brief Retrieves the Lease6 object in Kea format
    ///
    /// @return C++ representation of the object being returned
    virtual boost::any retrieve() override;

    /// @brief Retrieves zero or more IPv6 leases
    ///
    /// @param statement_tag query to be executed
    /// @param data parameters for the query
    /// @param result this lease collection will be updated
    void getLeaseCollection(StatementTag &statement_tag, AnyArray &data,
                            Lease6Collection &result);

    /// @brief Retrieves one IPv6 lease
    ///
    /// @param statement_tag query to be executed
    /// @param data parameters for the query
    /// @param result pointer to the lease being returned (or null)
    void
    getLease(StatementTag &statement_tag, AnyArray &data, Lease6Ptr &result);

    /// @brief Returns expired leases.
    ///
    /// This method returns up to specified number (see max_leases) of
    /// expired leases.
    ///
    /// @param max_leases at most this number of leases will be returned
    /// @param expired_leases expired leases will be stored here
    void getExpiredLeases(const size_t &max_leases, Lease6Collection &expired_leases);

    /// @brief Cassandra statements
    static StatementMap tagged_statements_;

    /// @brief Statement tags definitions
    /// @{
    static constexpr StatementTag INSERT_LEASE6 = "INSERT_LEASE6";
    static constexpr StatementTag UPDATE_LEASE6 = "UPDATE_LEASE6";
    static constexpr StatementTag DELETE_LEASE6 = "DELETE_LEASE6";
    static constexpr StatementTag GET_LEASE6_EXPIRE = "GET_LEASE6_EXPIRE";
    static constexpr StatementTag GET_LEASE6_ADDR = "GET_LEASE6_ADDR";
    static constexpr StatementTag GET_LEASE6_DUID = "GET_LEASE6_DUID";
    static constexpr StatementTag GET_LEASE6_DUID_IAID = "GET_LEASE6_DUID_IAID";
    static constexpr StatementTag GET_LEASE6_DUID_IAID_SUBID = "GET_LEASE6_DUID_IAID_SUBID";
    static constexpr StatementTag GET_LEASE6_LIMIT = "GET_LEASE6_LIMIT";
    static constexpr StatementTag GET_LEASE6_PAGE = "GET_LEASE6_PAGE";
    static constexpr StatementTag GET_LEASE6_HOSTNAME = "GET_LEASE6_HOSTNAME";
    // @}

private:

    /// @brief Lease
    Lease6Ptr lease_;

    /// @brief IPv6 address
    std::string address_;

    /// @brief Preferred lifetime
    cass_int64_t pref_lifetime_;

    /// @brief Client identifier
    CassBlob duid_;

    /// @brief Identity association identifier
    cass_int32_t iaid_;

    /// @brief Lease type (NA, TA or PD)
    cass_int32_t lease_type_;

    /// @brief Prefix length
    cass_int32_t prefix_len_;

    /// @brief Hardware type
    cass_int32_t hwtype_;

    /// @brief Source of the hardware address
    cass_int32_t hwaddr_source_;
};  // CqlLease6Exchange

constexpr StatementTag CqlLease6Exchange::INSERT_LEASE6;
constexpr StatementTag CqlLease6Exchange::UPDATE_LEASE6;
constexpr StatementTag CqlLease6Exchange::DELETE_LEASE6;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_EXPIRE;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_ADDR;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_DUID;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_DUID_IAID;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_DUID_IAID_SUBID;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_LIMIT;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_PAGE;
constexpr StatementTag CqlLease6Exchange::GET_LEASE6_HOSTNAME;

StatementMap CqlLease6Exchange::tagged_statements_ = {

    // Inserts new IPv6 lease
    {INSERT_LEASE6,
     {INSERT_LEASE6,
      "INSERT INTO lease6("
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      ") VALUES ("
      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?"
      ") "
      "IF NOT EXISTS "
     }},

    // Updates existing IPv6 lease
    {UPDATE_LEASE6,
     {UPDATE_LEASE6,
      "UPDATE lease6 SET "
      "valid_lifetime = ?, "
      "expire = ?, "
      "pref_lifetime = ?, "
      "duid = ?, "
      "iaid = ?, "
      "subnet_id = ?, "
      "lease_type = ?, "
      "prefix_len = ?, "
      "fqdn_fwd = ?, "
      "fqdn_rev = ?, "
      "hostname = ?, "
      "hwaddr = ?, "
      "hwtype = ?, "
      "hwaddr_source = ?, "
      "state = ?, "
      "user_context = ? "
      "WHERE address = ? "
      "IF expire = ? "
     }},

    // Deletes existing IPv6 lease
    {DELETE_LEASE6,
     {DELETE_LEASE6,
      "DELETE FROM lease6 "
      "WHERE address = ? "
      "IF expire = ? "
     }},

    // Gets up to a certain number of expired IPv6 leases
    {GET_LEASE6_EXPIRE,
     {GET_LEASE6_EXPIRE,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE state = ? "
      "AND valid_lifetime < 4294967295 "
      "AND expire < ? "
      "LIMIT ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv6 lease with specified IPv6 address
    {GET_LEASE6_ADDR,
     {GET_LEASE6_ADDR,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE address = ? "
      "AND lease_type = ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv6 lease with specified duid
    {GET_LEASE6_DUID,
     {GET_LEASE6_DUID,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE duid = ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv6 lease(s) with specified duid and iaid
    {GET_LEASE6_DUID_IAID,
     {GET_LEASE6_DUID_IAID,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE duid = ? AND iaid = ? "
      "AND lease_type = ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv6 lease with specified duid, iaid and subnet-id
    {GET_LEASE6_DUID_IAID_SUBID,
     {GET_LEASE6_DUID_IAID_SUBID,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE duid = ? AND iaid = ? "
      "AND lease_type = ? "
      "AND subnet_id = ? "
      "ALLOW FILTERING "
     }},

    // Get range of IPv6 leases from first lease with a limit (paging)
    {GET_LEASE6_LIMIT,
     {GET_LEASE6_LIMIT,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "LIMIT ? "
      "ALLOW FILTERING "
     }},

    // Get range of IPv6 leases from address with a limit (paging)
    {GET_LEASE6_PAGE,
     {GET_LEASE6_PAGE,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE TOKEN(address) > TOKEN(?) "
      "LIMIT ? "
      "ALLOW FILTERING "
     }},

    // Gets an IPv6 lease(s) with specified hostname
    {GET_LEASE6_HOSTNAME,
     {GET_LEASE6_HOSTNAME,
      "SELECT "
      "address, valid_lifetime, expire, subnet_id, pref_lifetime, duid, iaid, "
      "lease_type, prefix_len, fqdn_fwd, fqdn_rev, hostname, hwaddr, hwtype, "
      "hwaddr_source, state, user_context "
      "FROM lease6 "
      "WHERE hostname = ? "
      "ALLOW FILTERING "
     }}
};

CqlLease6Exchange::CqlLease6Exchange(const CqlConnection &connection)
    : CqlLeaseExchange(connection), pref_lifetime_(0), iaid_(0), lease_type_(0),
      prefix_len_(0), hwtype_(0), hwaddr_source_(0) {
}

void
CqlLease6Exchange::createBindForInsert(const Lease6Ptr &lease, AnyArray &data) {
    if (!lease) {
        isc_throw(BadValue, "CqlLease6Exchange::createBindForInsert(): "
                            "Lease6 object is NULL");
    }
    // Store lease object to ensure it remains valid.
    lease_ = lease;

    // Set up the structures for the various components of the lease4
    // structure.
    try {
        // address: varchar
        address_ = lease_->addr_.toText();
        if (address_.size() > ADDRESS6_TEXT_MAX_LEN) {
            isc_throw(BadValue, "address " << address_ << " of length " << address_.size()
                      << " exceeds maximum allowed length of " << ADDRESS6_TEXT_MAX_LEN);
        }

        // valid lifetime: bigint
        valid_lifetime_ = static_cast<cass_int64_t>(lease_->valid_lft_);

        // expire: bigint
        // The lease structure holds the client last transmission time
        // (cltt_)
        // For convenience for external tools, this is converted to lease
        // expiry time (expire). The relationship is given by:
        // expire = cltt_ + valid_lft_
        CqlExchange::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                           expire_);

        // subnet_id: int
        subnet_id_ = static_cast<cass_int32_t>(lease_->subnet_id_);

        // pref_lifetime: bigint
        pref_lifetime_ = static_cast<cass_int64_t>(lease_->preferred_lft_);

        // duid: blob
        if (!lease_->duid_) {
            isc_throw(DbOperationError, "lease6 with address " << address_
                      << " is missing mandatory duid");
        }
        duid_ = lease_->duid_->getDuid();

        // iaid: int
        iaid_ = static_cast<cass_int32_t>(lease_->iaid_);

        // lease_type: int
        lease_type_ = static_cast<cass_int32_t>(lease_->type_);

        // prefix_len: int
        prefix_len_ = static_cast<cass_int32_t>(lease_->prefixlen_);

        // fqdn_fwd: boolean
        fqdn_fwd_ = lease_->fqdn_fwd_ ? cass_true : cass_false;

        // fqdn_rev: boolean
        fqdn_rev_ = lease_->fqdn_rev_ ? cass_true : cass_false;

        // hostname: varchar
        if (lease_->hostname_.size() > HOSTNAME_MAX_LEN) {
            isc_throw(BadValue, "hostname" << lease_->hostname_ << " of length "
                      << lease_->hostname_.size() << " exceeds maximum allowed length of "
                      << HOSTNAME_MAX_LEN);
        }
        hostname_ = lease_->hostname_;

        // hwaddr: blob
        if (lease_->hwaddr_ && lease_->hwaddr_->hwaddr_.size() > 0) {
            if (lease_->hwaddr_->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                isc_throw(DbOperationError, "hardware address " << lease_->hwaddr_->toText()
                          << " of length " << lease_->hwaddr_->hwaddr_.size()
                          << " exceeds maximum allowed length of " << HWAddr::MAX_HWADDR_LEN);
            }
            hwaddr_ = lease_->hwaddr_->hwaddr_;
        } else {
            hwaddr_.clear();
        }

        // hwtype: int
        if (lease_->hwaddr_) {
            hwtype_ = static_cast<cass_int32_t>(lease_->hwaddr_->htype_);
        } else {
            hwtype_ = 0;
        }

        // hwaddr_source: int
        if (lease_->hwaddr_) {
            hwaddr_source_ = static_cast<cass_int32_t>(lease_->hwaddr_->source_);
        } else {
            hwaddr_source_ = 0;
        }

        // state: int
        state_ = static_cast<cass_int32_t>(lease_->state_);

        // user_context: text
        ConstElementPtr ctx = lease_->getContext();
        if (ctx) {
            user_context_ = ctx->str();
        } else {
            user_context_ = NULL_USER_CONTEXT;
        }

        // Start with a fresh array.
        data.clear();

        // Add them all to data.
        data.add(&address_);
        data.add(&valid_lifetime_);
        data.add(&expire_);
        data.add(&subnet_id_);
        data.add(&pref_lifetime_);
        data.add(&duid_);
        data.add(&iaid_);
        data.add(&lease_type_);
        data.add(&prefix_len_);
        data.add(&fqdn_fwd_);
        data.add(&fqdn_rev_);
        data.add(&hostname_);
        data.add(&hwaddr_);
        data.add(&hwtype_);
        data.add(&hwaddr_source_);
        data.add(&state_);
        data.add(&user_context_);

    } catch (const Exception &ex) {
        isc_throw(DbOperationError, "CqlLease6Exchange::createBindForInsert(): "
                  "could not create bind array from Lease6: " << lease_->addr_.toText()
                  << ", reason: " << ex.what());
    }
}

void
CqlLease6Exchange::createBindForUpdate(const Lease6Ptr &lease, AnyArray &data,
                                       StatementTag /* unused */) {
    if (!lease) {
        isc_throw(BadValue, "CqlLease6Exchange::createBindForUpdate(): "
                            "Lease6 object is NULL");
    }
    // Store lease object to ensure it remains valid.
    lease_ = lease;

    // Set up the structures for the various components of the lease4
    // structure.
    try {
        // address: varchar
        address_ = lease_->addr_.toText();
        if (address_.size() > ADDRESS6_TEXT_MAX_LEN) {
            isc_throw(BadValue,
                      "address " << address_ << " of length " << address_.size()
                                 << " exceeds maximum allowed length of "
                                 << ADDRESS6_TEXT_MAX_LEN);
        }

        // valid lifetime: bigint
        valid_lifetime_ = static_cast<cass_int64_t>(lease_->valid_lft_);

        // expire: bigint
        // The lease structure holds the client last transmission time
        // (cltt_)
        // For convenience for external tools, this is converted to lease
        // expiry time (expire). The relationship is given by:
        // expire = cltt_ + valid_lft_
        CqlExchange::convertToDatabaseTime(lease_->cltt_, lease_->valid_lft_,
                                           expire_);

        // subnet_id: int
        subnet_id_ = static_cast<cass_int32_t>(lease_->subnet_id_);

        // pref_lifetime: bigint
        pref_lifetime_ = static_cast<cass_int64_t>(lease_->preferred_lft_);

        // duid: blob
        if (!lease_->duid_) {
            isc_throw(DbOperationError,
                      "lease6 with address " << address_
                                             << " is missing mandatory duid");
        }
        duid_ = lease_->duid_->getDuid();

        // iaid: int
        iaid_ = static_cast<cass_int32_t>(lease_->iaid_);

        // lease_type: int
        lease_type_ = static_cast<cass_int32_t>(lease_->type_);

        // prefix_len: int
        prefix_len_ = static_cast<cass_int32_t>(lease_->prefixlen_);

        // fqdn_fwd: boolean
        fqdn_fwd_ = lease_->fqdn_fwd_ ? cass_true : cass_false;

        // fqdn_rev: boolean
        fqdn_rev_ = lease_->fqdn_rev_ ? cass_true : cass_false;

        // hostname: varchar
        if (lease_->hostname_.size() > HOSTNAME_MAX_LEN) {
            isc_throw(BadValue,
                      "hostname" << lease_->hostname_ << " of length "
                                 << lease_->hostname_.size()
                                 << " exceeds maximum allowed length of "
                                 << HOSTNAME_MAX_LEN);
        }
        hostname_ = lease_->hostname_;

        // hwaddr: blob
        if (lease_->hwaddr_ && lease_->hwaddr_->hwaddr_.size() > 0) {
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

        // hwtype: int
        if (lease_->hwaddr_) {
            hwtype_ = static_cast<cass_int32_t>(lease_->hwaddr_->htype_);
        } else {
            hwtype_ = 0;
        }

        // hwaddr_source: int
        if (lease_->hwaddr_) {
            hwaddr_source_ = static_cast<cass_int32_t>(lease_->hwaddr_->source_);
        } else {
            hwaddr_source_ = 0;
        }

        // state: int
        state_ = static_cast<cass_int32_t>(lease_->state_);

        // user_context: text
        ConstElementPtr ctx = lease_->getContext();
        if (ctx) {
            user_context_ = ctx->str();
        } else {
            user_context_ = NULL_USER_CONTEXT;
        }

        // Start with a fresh array.
        data.clear();

        // Add them all to data.
        data.add(&valid_lifetime_);
        data.add(&expire_);
        data.add(&pref_lifetime_);
        data.add(&duid_);
        data.add(&iaid_);
        data.add(&subnet_id_);
        data.add(&lease_type_);
        data.add(&prefix_len_);
        data.add(&fqdn_fwd_);
        data.add(&fqdn_rev_);
        data.add(&hostname_);
        data.add(&hwaddr_);
        data.add(&hwtype_);
        data.add(&hwaddr_source_);
        data.add(&state_);
        data.add(&user_context_);
        data.add(&address_);

        CqlExchange::convertToDatabaseTime(lease_->current_cltt_,
                                           lease_->current_valid_lft_,
                                           current_expire_);
        data.add(&current_expire_);
    } catch (const Exception &ex) {
        isc_throw(DbOperationError,
                  "CqlLease6Exchange::createBindForUpdate(): "
                  "could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
    }
}

void
CqlLease6Exchange::createBindForDelete(const Lease6Ptr &lease, AnyArray &data,
                                       StatementTag /* unused */) {
    if (!lease) {
        isc_throw(BadValue, "CqlLease6Exchange::createBindForDelete(): "
                            "Lease6 object is NULL");
    }
    // Store lease object to ensure it remains valid.
    lease_ = lease;

    // Set up the structures for the various components of the lease4
    // structure.
    try {
        // address: varchar
        address_ = lease_->addr_.toText();
        if (address_.size() > ADDRESS6_TEXT_MAX_LEN) {
            isc_throw(BadValue,
                      "address " << address_ << " of length " << address_.size()
                                 << " exceeds maximum allowed length of "
                                 << ADDRESS6_TEXT_MAX_LEN);
        }

        // Start with a fresh array.
        data.clear();
        data.add(&address_);

        CqlExchange::convertToDatabaseTime(lease_->current_cltt_,
                                           lease_->current_valid_lft_,
                                           current_expire_);
        data.add(&current_expire_);
    } catch (const Exception &ex) {
        isc_throw(DbOperationError,
                  "CqlLease6Exchange::createBindForDelete(): "
                  "could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
    }
}

void
CqlLease6Exchange::createBindForSelect(AnyArray &data, StatementTag /* unused */) {
    // Start with a fresh array.
    data.clear();

    // address: varchar
    data.add(&address_);

    // valid_lifetime_: bigint
    data.add(&valid_lifetime_);

    // expire: bigint
    data.add(&expire_);

    // subnet_id: int
    data.add(&subnet_id_);

    // pref_lifetime: bigint
    data.add(&pref_lifetime_);

    // duid: blob
    data.add(&duid_);

    // iaid: int
    data.add(&iaid_);

    // lease_type: int
    data.add(&lease_type_);

    // prefix_len: int
    data.add(&prefix_len_);

    // fqdn_fwd: boolean
    data.add(&fqdn_fwd_);

    // fqdn_rev: boolean
    data.add(&fqdn_rev_);

    // hostname: varchar
    data.add(&hostname_);

    // hwaddr: blob
    data.add(&hwaddr_);

    // hwtype: int
    data.add(&hwtype_);

    // hwaddr_source: int
    data.add(&hwaddr_source_);

    // state: int
    data.add(&state_);

    // user_context: text
    data.add(&user_context_);
}

boost::any
CqlLease6Exchange::retrieve() {
    try {
        // Sanity checks
        if (address_.size() > ADDRESS6_TEXT_MAX_LEN) {
            isc_throw(BadValue,
                      "address " << address_ << " of length " << address_.size()
                                 << " exceeds maximum allowed length of "
                                 << ADDRESS6_TEXT_MAX_LEN);
        }
        if (duid_.size() > DUID::MAX_DUID_LEN) {
            isc_throw(BadValue,
                      "duid " << DUID(duid_).toText() << " of length "
                              << duid_.size()
                              << " exceeds maximum allowed length of "
                              << DUID::MAX_DUID_LEN);
        }
        if (lease_type_ != Lease::TYPE_NA && lease_type_ != Lease::TYPE_TA &&
            lease_type_ != Lease::TYPE_PD) {
            isc_throw(BadValue,
                      "invalid lease type "
                          << lease_type_ << " for lease with address "
                          << address_ << ". Expected 0, 1 or 2.");
        }
        if (hostname_.size() > HOSTNAME_MAX_LEN) {
            isc_throw(BadValue,
                      "hostname " << hostname_ << " of length "
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

        IOAddress addr(address_);

        DuidPtr duid(boost::make_shared<DUID>(duid_));

        HWAddrPtr hwaddr;
        if (hwaddr_.size()) {
            hwaddr = boost::make_shared<HWAddr>(hwaddr_, hwtype_);
            hwaddr->source_ = hwaddr_source_;
        }

        ConstElementPtr ctx;
        if (!user_context_.empty()) {
            ctx = Element::fromJSON(user_context_);
            if (!ctx ||(ctx->getType() != Element::map)) {
                isc_throw(BadValue, "user context '" << user_context_
                          << "' is not a JSON map");
            }
        }

        // Create the lease and set the cltt (after converting from the
        // expire time retrieved from the database).
        Lease6Ptr result(boost::make_shared<Lease6>(static_cast<Lease::Type>(lease_type_), addr, duid,
                                                    iaid_, pref_lifetime_, valid_lifetime_,
                                                    subnet_id_, fqdn_fwd_, fqdn_rev_, hostname_,
                                                    hwaddr, prefix_len_));

        time_t cltt = 0;
        CqlExchange::convertFromDatabaseTime(expire_, valid_lifetime_, cltt);
        // Update cltt_ and current_cltt_ explicitly.
        result->cltt_ = cltt;
        result->current_cltt_ = cltt;

        result->state_ = state_;

        if (ctx) {
            result->setContext(ctx);
        }

        return (result);
    } catch (const Exception &ex) {
        isc_throw(DbOperationError,
                  "CqlLease6Exchange::retrieve(): "
                  "could not convert data to Lease6, reason: "
                      << ex.what());
    }
    return Lease6Ptr();
}

void
CqlLease6Exchange::getLeaseCollection(StatementTag &statement_tag, AnyArray &data,
                                      Lease6Collection &result) {
    AnyArray collection = executeSelect(connection_, data, statement_tag);

    // Transfer Lease6 objects to result.
    for (boost::any &lease : collection) {
        result.push_back(boost::any_cast<Lease6Ptr>(lease));
    }
}

void
CqlLease6Exchange::getLease(StatementTag &statement_tag, AnyArray &data,
                            Lease6Ptr &result) {
    // This particular method is called when only one or zero matches is
    // expected.
    Lease6Collection collection;
    getLeaseCollection(statement_tag, data, collection);

    // Return single record if present, else clear the lease.
    const size_t collection_size = collection.size();
    if (collection_size >= 2u) {
        isc_throw(MultipleRecords,
                  "CqlLease6Exchange::getLease(): multiple records were found in "
                  "the database where only one was expected for statement "
                  << statement_tag);
    } else if (collection_size == 0u) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
CqlLease6Exchange::getExpiredLeases(const size_t &max_leases,
                                    Lease6Collection &expired_leases) {
    // Set up the WHERE clause value
    cass_int32_t keep_state = Lease::STATE_EXPIRED_RECLAIMED;
    cass_int64_t timestamp = static_cast<cass_int64_t>(time(NULL));

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    cass_int32_t limit = max_leases > 0u ? static_cast<cass_int32_t>(max_leases) :
                                           std::numeric_limits<cass_int32_t>::max();

    for (cass_int32_t state = Lease::STATE_DEFAULT;
         state <= Lease::STATE_EXPIRED_RECLAIMED; ++state) {
        if (state == keep_state) {
            continue;
        }

        AnyArray data;
        data.add(&state);
        data.add(&timestamp);
        data.add(&limit);

        // Retrieve leases from the database.
        Lease6Collection temp_collection;
        getLeaseCollection(CqlLease6Exchange::GET_LEASE6_EXPIRE, data,
                           temp_collection);

        for (Lease6Ptr &lease : temp_collection) {
            expired_leases.push_back(lease);
        }
    }
}

/// @brief Base CQL derivation of the statistical lease data query
///
/// This class provides the functionality such as results storage and row
/// fetching common to fulfilling the statistical lease data query.
///
class CqlLeaseStatsQuery : public LeaseStatsQuery {
public:

    /// @brief Constructor to query for all subnets' stats
    ///
    ///  The query created will return statistics for all subnets
    ///
    /// @param conn An open connection to the database housing the lease data
    /// @param statement The lease data SQL prepared statement tag to execute
    /// @param fetch_type Indicates whether or not lease_type should be
    /// fetched from the result set (should be true for v6)
    CqlLeaseStatsQuery(CqlConnection& conn, StatementTag& statement,
                       const bool fetch_type)
        : conn_(conn), statement_(statement), fetch_type_(fetch_type),
          cumulative_rows_(), next_row_(cumulative_rows_.begin()),
          subnet_id_(0), lease_type_(0), state_(0) {
    }

    /// @brief Constructor to query for a single subnet's stats
    ///
    /// The query created will return statistics for a single subnet
    ///
    /// @param conn An open connection to the database housing the lease data
    /// @param statement The lease data SQL prepared statement tag to execute
    /// @param fetch_type Indicates whether or not lease_type should be
    /// fetched from the result set (should be true for v6)
    /// @param subnet_id id of the subnet for which stats are desired
    CqlLeaseStatsQuery(CqlConnection& conn, StatementTag& statement,
                       const bool fetch_type, const SubnetID& subnet_id)
        : LeaseStatsQuery(subnet_id), conn_(conn), statement_(statement),
          fetch_type_(fetch_type), cumulative_rows_(),
          next_row_(cumulative_rows_.begin()),
          subnet_id_(0), lease_type_(0), state_(0) {
    }

    /// @brief Constructor to query for the stats for a range of subnets
    ///
    /// The query created will return statistics for the inclusive range of
    /// subnets described by first and last subnet IDs.
    ///
    /// @param conn An open connection to the database housing the lease data
    /// @param statement The lease data SQL prepared statement tag to execute
    /// @param fetch_type Indicates whether or not lease_type should be
    /// fetched from the result set (should be true for v6)
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    CqlLeaseStatsQuery(CqlConnection& conn, StatementTag& statement,
                       const bool fetch_type, const SubnetID& first_subnet_id,
                       const SubnetID& last_subnet_id)
        : LeaseStatsQuery(first_subnet_id, last_subnet_id), conn_(conn),
          statement_(statement), fetch_type_(fetch_type), cumulative_rows_(),
          next_row_(cumulative_rows_.begin()),
          subnet_id_(0), lease_type_(0), state_(0) {
    }

    /// @brief Destructor
    virtual ~CqlLeaseStatsQuery() {};

    /// @brief Creates the lease statistical data result set
    ///
    /// The result set is populated by executing a  prepared SQL query
    /// against the database which sums the leases per lease state per
    /// subnet id.  Positions internal row tracking to point to the
    /// first row of the aggregate results.
    void start();

    /// @brief Executes protocol specific lease query SELECT statement
    ///
    /// Currently we do not have a good way for Cassandra to roll up the
    /// lease counts per subnet, type, and state as we do the other back
    /// ends.  This method executes the select statement which returns
    /// a result set containing a row of data for every lease:
    /// -v4 - subnet-id, lease-state
    /// -v6 - subnet-id, lease-type, lease-state
    ///
    /// It then iterates over this result set, aggregating the data into a
    /// a map of LeaseStatRows.
    ///
    /// If we didn't have to roll up the raw lease data first, we could
    /// have derived this class from CqlExchange and used it's executeSelect
    /// (from which this method borrows heavily). However, that would mean
    /// copying all the raw lease  data into a collection returned by
    /// executeSelect and then aggregating that into cumulative rows.
    /// The way we are now we go turn the raw lease data directly into the
    /// cumulative row map.
    ///
    /// @param connection connection used to communicate with the Cassandra
    /// database
    /// @param data array of bound objects used to filter the results
    /// @param statement_tag prepared statement being executed
    ///
    /// @throw DbOperationError
    void executeSelect(const CqlConnection& connection, const AnyArray& data,
                       StatementTag statement_tag);

    /// @brief Fetches the next row in the result set
    ///
    /// Once the internal result set has been populated by invoking the
    /// the start() method, this method is used to iterate over the
    /// result set rows. Once the last row has been fetched, subsequent
    /// calls will return false.
    ///
    /// @param row Storage for the fetched row
    ///
    /// @return True if the fetch succeeded, false if there are no more
    /// rows to fetch.
    bool getNextRow(LeaseStatsRow& row);

    /// @brief Create BIND array to receive C++ data.
    ///
    /// Used in executeSelect() to retrieve from database
    ///
    /// @param data array of bound objects representing data to be retrieved
    /// @param statement_tag prepared statement being executed; defaults to an
    ///     invalid index
    virtual void
    createBindForSelect(AnyArray& data, StatementTag statement_tag = NULL);

    /// @brief Statement tags definitions
    /// @{
    // Return lease4 lease statistics for all subnets
    static constexpr StatementTag ALL_LEASE4_STATS = "ALL_LEASE4_STATS";
    /// Return lease4 lease statistics for a single subnet
    static constexpr StatementTag SUBNET_LEASE4_STATS = "SUBNET_LEASE4_STATS";
    /// Return lease4 lease statistics for a range of subnets
    static constexpr StatementTag SUBNET_RANGE_LEASE4_STATS = "SUBNET_RANGE_LEASE4_STATS";

    // Return lease6 lease statistics for all subnets
    static constexpr StatementTag ALL_LEASE6_STATS = "ALL_LEASE6_STATS";
    /// Return lease6 lease statistics for a single subnet
    static constexpr StatementTag SUBNET_LEASE6_STATS = "SUBNET_LEASE6_STATS";
    /// Return lease6 lease statistics for a range of subnets
    static constexpr StatementTag SUBNET_RANGE_LEASE6_STATS = "SUBNET_RANGE_LEASE6_STATS";
    /// @}

    /// @brief Cassandra statements
    static StatementMap tagged_statements_;

private:

    /// @brief Database connection to use to execute the query
    CqlConnection& conn_;

    /// @brief The query's prepared statement tag
    StatementTag statement_;

    /// @brief Indicates if query supplies lease type
    bool fetch_type_;


    /// @brief map containing the aggregated lease counts
    std::map<LeaseStatsRow, int> cumulative_rows_;

    /// @brief cursor pointing to the next row to read in aggregate map
    std::map<LeaseStatsRow, int>::iterator next_row_;

    /// @brief Subnet identifier
    cass_int32_t subnet_id_;

    /// @brief Lease type (NA, TA or PD)
    cass_int32_t lease_type_;

    /// @brief Lease state
    cass_int32_t state_;
};

constexpr StatementTag CqlLeaseStatsQuery::ALL_LEASE4_STATS;
constexpr StatementTag CqlLeaseStatsQuery::SUBNET_LEASE4_STATS;
constexpr StatementTag CqlLeaseStatsQuery::SUBNET_RANGE_LEASE4_STATS;
constexpr StatementTag CqlLeaseStatsQuery::ALL_LEASE6_STATS;
constexpr StatementTag CqlLeaseStatsQuery::SUBNET_LEASE6_STATS;
constexpr StatementTag CqlLeaseStatsQuery::SUBNET_RANGE_LEASE6_STATS;

StatementMap CqlLeaseStatsQuery::tagged_statements_{
    // Return subnet_id and state of each v4 lease
    {ALL_LEASE4_STATS,
        {ALL_LEASE4_STATS,
        "SELECT "
        "subnet_id, state "
        "FROM lease4 "
    }},

    // Return state of each v4 lease for a single subnet
    {SUBNET_LEASE4_STATS,
        {SUBNET_LEASE4_STATS,
        "SELECT "
        "subnet_id, state "
        "FROM lease4 "
        "WHERE subnet_id = ? "
    }},

    // Return state of each v4 lease for a subnet range
    {SUBNET_RANGE_LEASE4_STATS,
        {SUBNET_RANGE_LEASE4_STATS,
        "SELECT "
        "subnet_id, state "
        "FROM lease4 "
        "WHERE subnet_id >= ? and subnet_id <= ? "
        "ALLOW FILTERING "
    }},

    // Return subnet_id, lease_type, and state of each v6 lease
    {ALL_LEASE6_STATS,
        {ALL_LEASE6_STATS,
        "SELECT "
        "subnet_id, lease_type, state "
        "FROM lease6 "
    }},

    // Return type and state of each v6 lease for a single subnet
    {SUBNET_LEASE6_STATS,
        {SUBNET_LEASE6_STATS,
        "SELECT "
        "subnet_id, lease_type, state "
        "FROM lease6 "
        "WHERE subnet_id = ? "
    }},

    // Return type and state of each v6 lease for single range
    {SUBNET_RANGE_LEASE6_STATS,
        {SUBNET_RANGE_LEASE6_STATS,
        "SELECT "
        "subnet_id, lease_type, state "
        "FROM lease6 "
        "WHERE subnet_id >= ? and subnet_id <= ? "
        "ALLOW FILTERING "
    }},
};

void
CqlLeaseStatsQuery::start() {
    // Set up where clause parameters as needed
    AnyArray data;
    cass_int32_t first_subnet_id_data;
    cass_int32_t last_subnet_id_data;
    if (getSelectMode() != ALL_SUBNETS) {
        first_subnet_id_data = static_cast<cass_int32_t>(first_subnet_id_);
        data.add(&first_subnet_id_data);

        if (getSelectMode() == SUBNET_RANGE) {
            last_subnet_id_data = static_cast<cass_int32_t>(last_subnet_id_);
            data.add(&last_subnet_id_data);
        }
    }

    // This gets a collection of "raw" data for all leases that match
    // the subnet selection criteria (all, range, or single subnets)
    // then rolls them up into cumulative_rows_
    executeSelect(conn_, data, statement_);

    // Set our row iterator to the beginning
    next_row_ = cumulative_rows_.begin();
}

bool
CqlLeaseStatsQuery::getNextRow(LeaseStatsRow& row) {
    // If we're past the end, punt.
    if (next_row_ == cumulative_rows_.end()) {
        return (false);
    }

    // Start by copying from the map row key
    row.subnet_id_ = next_row_->first.subnet_id_;
    row.lease_type_ = next_row_->first.lease_type_;
    row.lease_state_ = next_row_->first.lease_state_;

    // Grab the count from the map value
    row.state_count_ = next_row_->second;

    // Point to the next row.
    ++next_row_;
    return (true);
}

void
CqlLeaseStatsQuery::createBindForSelect(AnyArray& data, StatementTag) {
    data.clear();
    data.add(&subnet_id_);
    if (fetch_type_) {
        data.add(&lease_type_);
    }

    data.add(&state_);
}

void
CqlLeaseStatsQuery::executeSelect(const CqlConnection& connection, const AnyArray& data,
                                  StatementTag statement_tag)  {
    CassError rc;
    CassStatement* statement = NULL;
    CassFuture* future = NULL;
    AnyArray local_data = data;

    // Find the query statement first.
    StatementMap::const_iterator it = connection.statements_.find(statement_tag);
    if (it == connection.statements_.end()) {
        isc_throw(DbOperationError,
                  "CqlLeastStatsQuery::executeSelect(): Statement "
                      << statement_tag << "has not been prepared.");
    }

    // Bind the data before the query is executed.
    CqlTaggedStatement tagged_statement = it->second;
    if (tagged_statement.is_raw_) {
        // The entire query is the first element in data.
        std::string* query = boost::any_cast<std::string*>(local_data.back());
        local_data.pop_back();
        statement = cass_statement_new(query->c_str(), local_data.size());
    } else {
        statement = cass_prepared_bind(tagged_statement.prepared_statement_);
        if (!statement) {
            isc_throw(DbOperationError,
                      "CqlLeaseStatsQuery::executeSelect(): unable to bind statement "
                          << tagged_statement.name_);
        }
    }

    // Set specific level of consistency if we're told to do so.
    if (connection.force_consistency_) {
        rc = cass_statement_set_consistency(statement, connection.consistency_);
        if (rc != CASS_OK) {
            cass_statement_free(statement);
            isc_throw(DbOperationError,
                      "CqlLeaseStatsQuery::executeSelect(): unable to set statement "
                      "consistency for statement "
                          << tagged_statement.name_
                          << ", Cassandra error code: " << cass_error_desc(rc));
        }
        if (connection.serial_consistency_ != CASS_CONSISTENCY_UNKNOWN) {
            rc = cass_statement_set_serial_consistency(statement, connection.serial_consistency_);
            if (rc != CASS_OK) {
                cass_statement_free(statement);
                isc_throw(DbOperationError,
                          "CqlExchange::executeSelect(): unable to set statement "
                          "serial consistency for statement "
                              << tagged_statement.name_
                              << ", Cassandra error code: " << cass_error_desc(rc));
            }
        }
    }

    CqlCommon::bindData(local_data, statement);

    // Everything's ready. Call the actual statement.
    future = cass_session_execute(connection.session_, statement);
    if (!future) {
        cass_statement_free(statement);
        isc_throw(DbOperationError,
                  "CqlLeaseStatsQuery::executeSelect(): no CassFuture for statement "
                      << tagged_statement.name_);
    }

    // Wait for the statement execution to complete.
    cass_future_wait(future);
    const std::string error = connection.checkFutureError(
        "CqlLeaseStatsQuery::executeSelect(): cass_session_execute() != CASS_OK",
        future, statement_tag);
    rc = cass_future_error_code(future);
    if (rc != CASS_OK) {
        cass_future_free(future);
        cass_statement_free(statement);
        isc_throw(DbOperationError, error);
    }

    // Get column values.
    const CassResult* result_collection = cass_future_get_result(future);

    // lease type is always NA for v4
    if (!fetch_type_)  {
        lease_type_ = Lease::TYPE_NA;
    }

    // Since we're currently forced to pull data for all leases, we
    // iterate over them, aggregating them into cumulative LeaseStatsRows
    AnyArray return_values;
    CassIterator* rows = cass_iterator_from_result(result_collection);
    while (cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        createBindForSelect(return_values, statement_tag);
        CqlCommon::getData(row, return_values);

        if (state_ != Lease::STATE_DEFAULT &&
            state_ != Lease::STATE_DECLINED) {
            continue;
        }

        LeaseStatsRow raw_row(subnet_id_, static_cast<Lease::Type>(lease_type_),
                              state_, 1);

        auto cum_row = cumulative_rows_.find(raw_row);
        if (cum_row != cumulative_rows_.end()) {
            cumulative_rows_[raw_row] = cum_row->second + 1;
        } else {
            cumulative_rows_.insert(std::make_pair(raw_row, 1));
        }
    }

    // Free resources.
    cass_iterator_free(rows);
    cass_result_free(result_collection);
    cass_future_free(future);
    cass_statement_free(statement);
    return;
}

CqlLeaseMgr::CqlLeaseMgr(const DatabaseConnection::ParameterMap &parameters)
    : parameters_(parameters), dbconn_(parameters) {
    // Validate the schema version first.
    std::pair<uint32_t, uint32_t> code_version(CQL_SCHEMA_VERSION_MAJOR,
                                               CQL_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError, "Cassandra schema version mismatch: need version: "
                  << code_version.first << "." << code_version.second
                  << " found version:  " << db_version.first << "."
                  << db_version.second);
    }

    // Cassandra support is now deprecated.
    LOG_WARN(dhcpsrv_logger, DHCPSRV_DEPRECATED).arg("Cassandra lease backend");

    // Check TLS support.
    bool tls(false);
    try {
        dbconn_.getParameter("trust-anchor");
        tls = true;
    } catch (...) {
        // No trust anchor.
    }
    try {
        dbconn_.getParameter("cert-file");
        tls = true;
    } catch (...) {
        // No certificate file.
    }
    try {
        dbconn_.getParameter("key-file");
        tls = true;
    } catch (...) {
        // No private key file.
    }
    try {
        dbconn_.getParameter("cipher-list");
        tls = true;
    } catch (...) {
        // No cipher list.
    }
    if (tls) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_CQL_NO_TLS_SUPPORT)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        isc_throw(DbOpenError, "Attempt to configure TLS for CQL");
    }

    // Open the database.
    dbconn_.openDatabase();

    // Now prepare the rest of the exchanges.
    dbconn_.prepareStatements(CqlLease4Exchange::tagged_statements_);
    dbconn_.prepareStatements(CqlLease6Exchange::tagged_statements_);
    dbconn_.prepareStatements(CqlLeaseStatsQuery::tagged_statements_);
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
    tmp << ", library cassandra";
    return tmp.str();
}

bool
CqlLeaseMgr::addLease(const Lease4Ptr &lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ADD_ADDR4)
        .arg(lease->addr_.toText());

    AnyArray data;

    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->createBindForInsert(lease, data);
    try {
        exchange4->executeMutation(dbconn_, data, CqlLease4Exchange::INSERT_LEASE4);
    } catch (const Exception &exception) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_LEASE_EXCEPTION_THROWN)
            .arg(exception.what());
        return false;
    }

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    return true;
}

bool
CqlLeaseMgr::addLease(const Lease6Ptr &lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ADD_ADDR6)
        .arg(lease->addr_.toText());

    AnyArray data;

    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->createBindForInsert(lease, data);
    try {
        exchange6->executeMutation(dbconn_, data, CqlLease6Exchange::INSERT_LEASE6);
    } catch (const Exception &exception) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_LEASE_EXCEPTION_THROWN)
            .arg(exception.what());
        return false;
    }

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    return true;
}

Lease4Ptr
CqlLeaseMgr::getLease4(const IOAddress &addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_ADDR4)
        .arg(addr.toText());

    // Set up the WHERE clause value
    AnyArray data;

    cass_int32_t addr4 = static_cast<cass_int32_t>(addr.toUint32());
    data.add(&addr4);

    // Get the data.
    Lease4Ptr result;

    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLease(CqlLease4Exchange::GET_LEASE4_ADDR, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLease4(const HWAddr &hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_HWADDR)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob hwaddr_data(hwaddr.hwaddr_);
    data.add(&hwaddr_data);

    // Get the data.
    Lease4Collection result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(CqlLease4Exchange::GET_LEASE4_HWADDR, data, result);

    return (result);
}

Lease4Ptr
CqlLeaseMgr::getLease4(const HWAddr &hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_GET_SUBID_HWADDR)
        .arg(subnet_id)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob hwaddr_data(hwaddr.hwaddr_);
    data.add(&hwaddr_data);

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(&subnet_id_data);

    // Get the data.
    Lease4Ptr result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLease(CqlLease4Exchange::GET_LEASE4_HWADDR_SUBID, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLease4(const ClientId &clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_CLIENTID)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob client_id_data(clientid.getClientId());
    data.add(&client_id_data);

    // Get the data.
    Lease4Collection result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(CqlLease4Exchange::GET_LEASE4_CLIENTID, data, result);

    return (result);
}

Lease4Ptr
CqlLeaseMgr::getLease4(const ClientId &clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_SUBID_CLIENTID)
        .arg(subnet_id)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob client_id_data(clientid.getClientId());
    data.add(&client_id_data);

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(&subnet_id_data);

    // Get the data.
    Lease4Ptr result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLease(CqlLease4Exchange::GET_LEASE4_CLIENTID_SUBID, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLeases4(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_SUBID4)
        .arg(subnet_id);

    // Set up the WHERE clause value
    AnyArray data;

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(&subnet_id_data);

    // Get the data.
    Lease4Collection result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(CqlLease4Exchange::GET_LEASE4_SUBID, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLeases4(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_HOSTNAME4)
        .arg(hostname);

    // Set up the WHERE clause value
    AnyArray data;

    std::string hostname_data(hostname);
    data.add(&hostname_data);

    // Get the data.
    Lease4Collection result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(CqlLease4Exchange::GET_LEASE4_HOSTNAME, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLeases4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET4);

    // Set up the WHERE clause value
    AnyArray data;

    // Get the data.
    Lease4Collection result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(CqlLease4Exchange::GET_LEASE4, data, result);

    return (result);
}

Lease4Collection
CqlLeaseMgr::getLeases4(const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size) const {
    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    if (page_size.page_size_ == 0) {
        isc_throw(OutOfRange, "page size of retrieved leases must not be 0");
    }

    if (page_size.page_size_ > std::numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "page size of retrieved leases must not be greater than "
                  << std::numeric_limits<uint32_t>::max());
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_PAGE4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    AnyArray data;

    cass_int32_t address_data = 0;
    if (!lower_bound_address.isV4Zero()) {
        address_data = static_cast<cass_int32_t>(lower_bound_address.toUint32());
        data.add(&address_data);
    }

    cass_int32_t page_size_data = static_cast<cass_int32_t>(page_size.page_size_);
    data.add(&page_size_data);

    // Get the data.
    Lease4Collection result;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(lower_bound_address.isV4Zero() ?
                                  CqlLease4Exchange::GET_LEASE4_LIMIT :
                                  CqlLease4Exchange::GET_LEASE4_PAGE,
                                  data, result);

    return (result);
}

Lease6Ptr
CqlLeaseMgr::getLease6(Lease::Type lease_type, const IOAddress &addr) const {
    std::string addr_data = addr.toText();
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_ADDR6)
        .arg(addr_data)
        .arg(lease_type);

    // Set up the WHERE clause value
    AnyArray data;

    if (addr_data.size() > ADDRESS6_TEXT_MAX_LEN) {
        isc_throw(BadValue,
                  "CqlLeaseMgr::getLease6(): "
                  "address "
                      << addr_data << " of length " << addr_data.size()
                      << " exceeds maximum allowed length of "
                      << ADDRESS6_TEXT_MAX_LEN);
    }
    data.add(&addr_data);

    cass_int32_t lease_type_data = static_cast<cass_int32_t>(lease_type);
    data.add(&lease_type_data);

    Lease6Ptr result;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLease(CqlLease6Exchange::GET_LEASE6_ADDR, data, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6(const DUID& duid) const {

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob duid_data(duid.getDuid());

    data.add(&duid_data);

    // Get the data.
    Lease6Collection result;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLeaseCollection(CqlLease6Exchange::GET_LEASE6_DUID,
                                  data, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID &duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_IAID_DUID)
        .arg(iaid)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob duid_data(duid.getDuid());
    cass_int32_t iaid_data = static_cast<cass_int32_t>(iaid);

    data.add(&duid_data);
    data.add(&iaid_data);

    cass_int32_t lease_type_data = static_cast<cass_int32_t>(lease_type);
    data.add(&lease_type_data);

    // Get the data.
    Lease6Collection result;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLeaseCollection(CqlLease6Exchange::GET_LEASE6_DUID_IAID, data, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID &duid, uint32_t iaid,
                        SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_IAID_SUBID_DUID)
        .arg(iaid)
        .arg(subnet_id)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    AnyArray data;

    CassBlob duid_data(duid.getDuid());
    cass_int32_t iaid_data = static_cast<cass_int32_t>(iaid);

    data.add(&duid_data);
    data.add(&iaid_data);

    cass_int32_t lease_type_data = static_cast<cass_int32_t>(lease_type);
    data.add(&lease_type_data);

    cass_int32_t subnet_id_data = static_cast<cass_int32_t>(subnet_id);
    data.add(&subnet_id_data);

    // Get the data.
    Lease6Collection result;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLeaseCollection(CqlLease6Exchange::GET_LEASE6_DUID_IAID_SUBID, data, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6(SubnetID) const {
    isc_throw(NotImplemented, "getLeases6(subnet_id) is not implemented");
}

Lease6Collection
CqlLeaseMgr::getLeases6(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_HOSTNAME6)
        .arg(hostname);

    // Set up the WHERE clause value
    AnyArray data;

    std::string hostname_data(hostname);
    data.add(&hostname_data);

    // Get the data.
    Lease6Collection result;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLeaseCollection(CqlLease6Exchange::GET_LEASE6_HOSTNAME, data, result);

    return (result);
}

Lease6Collection
CqlLeaseMgr::getLeases6() const {
    isc_throw(NotImplemented, "getLeases6() is not implemented");
}

Lease6Collection
CqlLeaseMgr::getLeases6(const asiolink::IOAddress& lower_bound_address,
                        const LeasePageSize& page_size) const {
    // Expecting IPv6 address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    if (page_size.page_size_ == 0) {
        isc_throw(OutOfRange, "page size of retrieved leases must not be 0");
    }

    if (page_size.page_size_ > std::numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "page size of retrieved leases must not be greater than "
                  << std::numeric_limits<uint32_t>::max());
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_PAGE6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    AnyArray data;

    std::string lb_address_data;
    if (!lower_bound_address.isV6Zero()) {
        lb_address_data = lower_bound_address.toText();
        if (lb_address_data.size() > ADDRESS6_TEXT_MAX_LEN) {
            isc_throw(BadValue,
                      "CqlLeaseMgr::getLeases6(lower_bound_address, page_size): "
                      "address "
                      << lb_address_data << " of length " << lb_address_data.size()
                      << " exceeds maximum allowed length of "
                      << ADDRESS6_TEXT_MAX_LEN);
        }
        data.add(&lb_address_data);
    }

    cass_int32_t page_size_data = static_cast<cass_int32_t>(page_size.page_size_);
    data.add(&page_size_data);

    // Get the leases.
    Lease6Collection result;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLeaseCollection(lower_bound_address.isV6Zero() ?
                                  CqlLease6Exchange::GET_LEASE6_LIMIT :
                                  CqlLease6Exchange::GET_LEASE6_PAGE,
                                  data, result);

    return (result);
}

void
CqlLeaseMgr::getExpiredLeases4(Lease4Collection &expired_leases,
                               const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_EXPIRED4)
        .arg(max_leases);

    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getExpiredLeases(max_leases, expired_leases);
}

void
CqlLeaseMgr::getExpiredLeases6(Lease6Collection &expired_leases,
                               const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_EXPIRED6)
        .arg(max_leases);

    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getExpiredLeases(max_leases, expired_leases);
}

void
CqlLeaseMgr::updateLease4(const Lease4Ptr &lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_UPDATE_ADDR4)
        .arg(lease->addr_.toText());

    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));

    try {
        AnyArray data;
        exchange4->createBindForUpdate(lease, data, CqlLease4Exchange::UPDATE_LEASE4);
        exchange4->executeMutation(dbconn_, data, CqlLease4Exchange::UPDATE_LEASE4);
    } catch (const StatementNotApplied &exception) {
        isc_throw(NoSuchLease, exception.what());
    }

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();
}

void
CqlLeaseMgr::updateLease6(const Lease6Ptr &lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_UPDATE_ADDR6)
        .arg(lease->addr_.toText());

    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));

    try {
        AnyArray data;
        exchange6->createBindForUpdate(lease, data, CqlLease6Exchange::UPDATE_LEASE6);
        exchange6->executeMutation(dbconn_, data, CqlLease6Exchange::UPDATE_LEASE6);
    } catch (const StatementNotApplied &exception) {
        isc_throw(NoSuchLease, exception.what());
    }

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();
}

bool
CqlLeaseMgr::deleteLease(const Lease4Ptr &lease) {
    const IOAddress &addr = lease->addr_;
    std::string addr_data = addr.toText();
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_DELETE_ADDR)
        .arg(addr_data);

    // Set up the WHERE clause value
    AnyArray data;

    std::unique_ptr<CqlLease4Exchange> exchange4(
        new CqlLease4Exchange(dbconn_));

    try {
        exchange4->createBindForDelete(lease, data, CqlLease4Exchange::DELETE_LEASE4);
        exchange4->executeMutation(dbconn_, data, CqlLease4Exchange::DELETE_LEASE4);
    } catch (const Exception &exception) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_LEASE_EXCEPTION_THROWN)
            .arg(exception.what());
        return false;
    }
    return true;
}

bool
CqlLeaseMgr::deleteLease(const Lease6Ptr &lease) {
    const IOAddress &addr = lease->addr_;
    std::string addr_data = addr.toText();
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_DELETE_ADDR)
        .arg(addr_data);

    // Set up the WHERE clause value
    AnyArray data;

    std::unique_ptr<CqlLease6Exchange> exchange6(
        new CqlLease6Exchange(dbconn_));

    try {
        exchange6->createBindForDelete(lease, data, CqlLease6Exchange::DELETE_LEASE6);
        exchange6->executeMutation(dbconn_, data, CqlLease6Exchange::DELETE_LEASE6);
    } catch (const Exception &exception) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_LEASE_EXCEPTION_THROWN)
            .arg(exception.what());
        return false;
    }
    return true;
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    AnyArray data;
    uint64_t deleted = 0u;
    cass_int32_t limit = 1024;

    // State is reclaimed.
    cass_int32_t state = static_cast<cass_int32_t>(Lease::STATE_EXPIRED_RECLAIMED);
    data.add(&state);

    // Expiration timestamp.
    cass_int64_t expiration = static_cast<cass_int64_t>(time(NULL) - static_cast<time_t>(secs));
    data.add(&expiration);

    data.add(&limit);

    // Get the data.
    Lease4Collection leases;
    std::unique_ptr<CqlLease4Exchange> exchange4(new CqlLease4Exchange(dbconn_));
    exchange4->getLeaseCollection(CqlLease4Exchange::GET_LEASE4_EXPIRE, data, leases);
    for (Lease4Ptr &lease : leases) {
        if (deleteLease(lease)) {
            ++deleted;
        }
    }
    return (deleted);
}

uint64_t
CqlLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    AnyArray data;
    uint64_t deleted = 0u;
    cass_int32_t limit = 1024;

    // State is reclaimed.
    cass_int32_t state = static_cast<cass_int32_t>(Lease::STATE_EXPIRED_RECLAIMED);
    data.add(&state);

    // Expiration timestamp.
    cass_int64_t expiration = static_cast<cass_int64_t>(time(NULL) - static_cast<time_t>(secs));
    data.add(&expiration);

    data.add(&limit);

    // Get the data.
    Lease6Collection leases;
    std::unique_ptr<CqlLease6Exchange> exchange6(new CqlLease6Exchange(dbconn_));
    exchange6->getLeaseCollection(CqlLease6Exchange::GET_LEASE6_EXPIRE, data, leases);
    for (Lease6Ptr &lease : leases) {
        if (deleteLease(lease)) {
            ++deleted;
        }
    }
    return (deleted);
}

LeaseStatsQueryPtr
CqlLeaseMgr::startLeaseStatsQuery4() {
    LeaseStatsQueryPtr query(
        new CqlLeaseStatsQuery(dbconn_, CqlLeaseStatsQuery::ALL_LEASE4_STATS,
                               false));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
CqlLeaseMgr::startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) {
    LeaseStatsQueryPtr query(
        new CqlLeaseStatsQuery(dbconn_, CqlLeaseStatsQuery::SUBNET_LEASE4_STATS,
                               false, subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
CqlLeaseMgr::startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                              const SubnetID& last_subnet_id) {
    LeaseStatsQueryPtr query(
        new CqlLeaseStatsQuery(dbconn_, CqlLeaseStatsQuery::SUBNET_RANGE_LEASE4_STATS,
                               false, first_subnet_id, last_subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
CqlLeaseMgr::startLeaseStatsQuery6() {
    LeaseStatsQueryPtr query(
        new CqlLeaseStatsQuery(dbconn_, CqlLeaseStatsQuery::ALL_LEASE6_STATS,
                               true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
CqlLeaseMgr::startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) {
    LeaseStatsQueryPtr query(
        new CqlLeaseStatsQuery(dbconn_, CqlLeaseStatsQuery::SUBNET_LEASE6_STATS,
                               true, subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
CqlLeaseMgr::startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                              const SubnetID& last_subnet_id) {
    LeaseStatsQueryPtr query(
        new CqlLeaseStatsQuery(dbconn_, CqlLeaseStatsQuery::SUBNET_RANGE_LEASE6_STATS,
                               true, first_subnet_id, last_subnet_id));
    query->start();
    return(query);
}

size_t
CqlLeaseMgr::wipeLeases4(const SubnetID & /*subnet_id*/) {
    /// @todo: Need to implement this, so wipe leases would work.
    isc_throw(NotImplemented, "wipeLeases4 is not implemented for Cassandra backend");
}

size_t
CqlLeaseMgr::wipeLeases6(const SubnetID & /*subnet_id*/) {
    /// @todo: Need to implement this, so wipe leases would work.
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

VersionPair
CqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_GET_VERSION);

    return CqlConnection::getVersion(parameters_);
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
