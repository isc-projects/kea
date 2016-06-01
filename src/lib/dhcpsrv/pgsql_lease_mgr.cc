// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/pgsql_lease_mgr.h>

#include <boost/static_assert.hpp>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace {

/// @brief Catalog of all the SQL statements currently supported.  Note
/// that the order columns appear in statement body must match the order they
/// that the occur in the table.  This does not apply to the where clause.
PgSqlTaggedStatement tagged_statements[] = {
    // DELETE_LEASE4
    { 1, { OID_INT8 },
      "delete_lease4",
      "DELETE FROM lease4 WHERE address = $1"},

    // DELETE_LEASE4_STATE_EXPIRED
    { 2, { OID_INT8, OID_TIMESTAMP },
      "delete_lease4_state_expired",
      "DELETE FROM lease4 "
          "WHERE state = $1 AND expire < $2"},

    // DELETE_LEASE6
    { 1, { OID_VARCHAR },
      "delete_lease6",
      "DELETE FROM lease6 WHERE address = $1"},

    // DELETE_LEASE6_STATE_EXPIRED
    { 2, { OID_INT8, OID_TIMESTAMP },
      "delete_lease6_state_expired",
      "DELETE FROM lease6 "
          "WHERE state = $1 AND expire < $2"},

    // GET_LEASE4_ADDR
    { 1, { OID_INT8 },
      "get_lease4_addr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE address = $1"},

    // GET_LEASE4_CLIENTID
    { 1, { OID_BYTEA },
      "get_lease4_clientid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE client_id = $1"},

    // GET_LEASE4_CLIENTID_SUBID
    { 2, { OID_BYTEA, OID_INT8 },
      "get_lease4_clientid_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE client_id = $1 AND subnet_id = $2"},

    // GET_LEASE4_HWADDR
    { 1, { OID_BYTEA },
      "get_lease4_hwaddr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE hwaddr = $1"},

    // GET_LEASE4_HWADDR_SUBID
    { 2, { OID_BYTEA, OID_INT8 },
      "get_lease4_hwaddr_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, state "
      "FROM lease4 "
      "WHERE hwaddr = $1 AND subnet_id = $2"},

    // GET_LEASE4_EXPIRE
    { 3, { OID_INT8, OID_TIMESTAMP, OID_INT8 },
      "get_lease4_expire",
      "SELECT address, hwaddr, client_id, "
          "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
          "fqdn_fwd, fqdn_rev, hostname, state "
              "FROM lease4 "
              "WHERE state != $1 AND expire < $2 "
              "ORDER BY expire "
              "LIMIT $3"},

    // GET_LEASE6_ADDR
    { 2, { OID_VARCHAR, OID_INT2 },
      "get_lease6_addr",
      "SELECT address, duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease6 "
      "WHERE address = $1 AND lease_type = $2"},

    // GET_LEASE6_DUID_IAID
    {  3, { OID_BYTEA, OID_INT8, OID_INT2 },
       "get_lease6_duid_iaid",
       "SELECT address, duid, valid_lifetime, "
         "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
         "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
         "state "
       "FROM lease6 "
       "WHERE duid = $1 AND iaid = $2 AND lease_type = $3"},

    // GET_LEASE6_DUID_IAID_SUBID
    { 4, { OID_INT2, OID_BYTEA, OID_INT8, OID_INT8 },
      "get_lease6_duid_iaid_subid",
      "SELECT address, duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "state "
      "FROM lease6 "
      "WHERE lease_type = $1 "
        "AND duid = $2 AND iaid = $3 AND subnet_id = $4"},

    // GET_LEASE6_EXPIRE
    { 3, { OID_INT8, OID_TIMESTAMP, OID_INT8 },
      "get_lease6_expire",
      "SELECT address, duid, valid_lifetime, "
          "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
          "lease_type, iaid, prefix_len, "
          "fqdn_fwd, fqdn_rev, hostname, state "
          "state "
              "FROM lease6 "
              "WHERE state != $1 AND expire < $2 "
              "ORDER BY expire "
              "LIMIT $3"},

    // GET_VERSION
    { 0, { OID_NONE },
      "get_version",
      "SELECT version, minor FROM schema_version"},

    // INSERT_LEASE4
    { 10, { OID_INT8, OID_BYTEA, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8,
            OID_BOOL, OID_BOOL, OID_VARCHAR, OID_INT8, OID_INT8 },
      "insert_lease4",
      "INSERT INTO lease4(address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname, "
        "state) "
      "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10)"},

    // INSERT_LEASE6
    { 13, { OID_VARCHAR, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8,
            OID_INT8, OID_INT2, OID_INT8, OID_INT2, OID_BOOL, OID_BOOL,
            OID_VARCHAR, OID_INT8 },
      "insert_lease6",
      "INSERT INTO lease6(address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, state) "
      "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13)"},

    // UPDATE_LEASE4
    { 11, { OID_INT8, OID_BYTEA, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8,
            OID_BOOL, OID_BOOL, OID_VARCHAR, OID_INT8, OID_INT8 },
      "update_lease4",
      "UPDATE lease4 SET address = $1, hwaddr = $2, "
        "client_id = $3, valid_lifetime = $4, expire = $5, "
        "subnet_id = $6, fqdn_fwd = $7, fqdn_rev = $8, hostname = $9, "
        "state = $10"
      "WHERE address = $11"},

    // UPDATE_LEASE6
    { 14, { OID_VARCHAR, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8, OID_INT8,
            OID_INT2, OID_INT8, OID_INT2, OID_BOOL, OID_BOOL, OID_VARCHAR,
            OID_INT8, OID_VARCHAR },
      "update_lease6",
      "UPDATE lease6 SET address = $1, duid = $2, "
        "valid_lifetime = $3, expire = $4, subnet_id = $5, "
        "pref_lifetime = $6, lease_type = $7, iaid = $8, "
        "prefix_len = $9, fqdn_fwd = $10, fqdn_rev = $11, hostname = $12, "
        "state = $13 "
      "WHERE address = $14"},

    // End of list sentinel
    { 0,  { 0 }, NULL, NULL}
};

};

namespace isc {
namespace dhcp {

/// @brief Base class for marshalling leases to and from PostgreSQL.
///
/// Provides the common functionality to set up binding information between
/// lease objects in the program and their database representation in the
/// database.
class PgSqlLeaseExchange : public PgSqlExchange {
public:

    PgSqlLeaseExchange()
        : addr_str_(""), valid_lifetime_(0), valid_lft_str_(""),
          expire_(0), expire_str_(""), subnet_id_(0), subnet_id_str_(""),
          cltt_(0), fqdn_fwd_(false), fqdn_rev_(false), hostname_(""),
          state_str_("") {
    }

    virtual ~PgSqlLeaseExchange(){}

protected:
    /// @brief Common Instance members used for binding and conversion
    //@{
    std::string addr_str_;
    uint32_t valid_lifetime_;
    std::string valid_lft_str_;
    time_t expire_;
    std::string expire_str_;
    uint32_t subnet_id_;
    std::string subnet_id_str_;
    time_t cltt_;
    bool fqdn_fwd_;
    bool fqdn_rev_;
    std::string hostname_;
    std::string state_str_;
    //@}

};


/// @brief Supports exchanging IPv4 leases with PostgreSQL.
class PgSqlLease4Exchange : public PgSqlLeaseExchange {
private:

    /// @brief Column numbers for each column in the Lease4 table.
    /// These are used for both retrieving data and for looking up
    /// column labels for logging.  Note that their numeric order
    /// MUST match that of the column order in the Lease4 table.
    static const size_t ADDRESS_COL = 0;
    static const size_t HWADDR_COL = 1;
    static const size_t CLIENT_ID_COL = 2;
    static const size_t VALID_LIFETIME_COL = 3;
    static const size_t EXPIRE_COL = 4;
    static const size_t SUBNET_ID_COL = 5;
    static const size_t FQDN_FWD_COL = 6;
    static const size_t FQDN_REV_COL = 7;
    static const size_t HOSTNAME_COL = 8;
    static const size_t STATE_COL = 9;
    /// @brief Number of columns in the table holding DHCPv4 leases.
    static const size_t LEASE_COLUMNS = 10;

public:

    /// @brief Default constructor
    PgSqlLease4Exchange()
        : lease_(), addr4_(0), hwaddr_length_(0), hwaddr_(hwaddr_length_),
        client_id_length_(0) {

        BOOST_STATIC_ASSERT(9 < LEASE_COLUMNS);

        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));

        // Set the column names (for error messages)
        column_labels_.push_back("address");
        column_labels_.push_back("hwaddr");
        column_labels_.push_back("client_id");
        column_labels_.push_back("valid_lifetime");
        column_labels_.push_back("expire");
        column_labels_.push_back("subnet_id");
        column_labels_.push_back("fqdn_fwd");
        column_labels_.push_back("fqdn_rev");
        column_labels_.push_back("hostname");
        column_labels_.push_back("state");
    }

    /// @brief Creates the bind array for sending Lease4 data to the database.
    ///
    /// Converts each Lease4 member into the appropriate form and adds it
    /// to the bind array.  Note that the array additions must occur in the
    /// order the columns are specified in the SQL statement.  By convention
    /// all columns in the table are explicitly listed in the SQL statement(s)
    /// in the same order as they occur in the table.
    ///
    /// @param lease Lease4 object that is to be written to the database
    /// @param[out] bind_array array to populate with the lease data values
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    void createBindForSend(const Lease4Ptr& lease, PsqlBindArray& bind_array) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease4 object is NULL");
        }

        // Store lease object to ensure it remains valid.
        lease_ = lease;

        try {
            addr_str_ = boost::lexical_cast<std::string>
                        (static_cast<uint32_t>(lease->addr_));
            bind_array.add(addr_str_);

            if (lease->hwaddr_ && !lease->hwaddr_->hwaddr_.empty()) {
                // PostgreSql does not provide MAX on variable length types
                // so we have to enforce it ourselves.
                if (lease->hwaddr_->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                        isc_throw(DbOperationError, "Hardware address length : "
                                  << lease_->hwaddr_->hwaddr_.size()
                                  << " exceeds maximum allowed of: "
                                  << HWAddr::MAX_HWADDR_LEN);
                }

                bind_array.add(lease->hwaddr_->hwaddr_);
            } else {
                bind_array.add("");
            }

            if (lease->client_id_) {
                bind_array.add(lease->client_id_->getClientId());
            } else {
                bind_array.add("");
            }

            valid_lft_str_ = boost::lexical_cast<std::string>
                             (lease->valid_lft_);
            bind_array.add(valid_lft_str_);

            expire_str_ = convertToDatabaseTime(lease->cltt_, lease_->valid_lft_);
            bind_array.add(expire_str_);

            subnet_id_str_ = boost::lexical_cast<std::string>
                             (lease->subnet_id_);
            bind_array.add(subnet_id_str_);

            bind_array.add(lease->fqdn_fwd_);
            bind_array.add(lease->fqdn_rev_);

            bind_array.add(lease->hostname_);

            state_str_ = boost::lexical_cast<std::string>(lease->state_);
            bind_array.add(state_str_);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }
    }

    /// @brief Creates a Lease4 object from a given row in a result set.
    ///
    /// @param r result set containing one or rows from the Lease4 table
    /// @param row row number within the result set from to create the Lease4
    /// object.
    ///
    /// @return Lease4Ptr to the newly created Lease4 object
    /// @throw DbOperationError if the lease cannot be created.
    Lease4Ptr convertFromDatabase(const PgSqlResult& r, int row) {
        try {
            getColumnValue(r, row, ADDRESS_COL, addr4_);

            convertFromBytea(r, row, HWADDR_COL, hwaddr_buffer_,
                             sizeof(hwaddr_buffer_), hwaddr_length_);

            convertFromBytea(r, row, CLIENT_ID_COL, client_id_buffer_,
                             sizeof(client_id_buffer_), client_id_length_);

            getColumnValue(r, row, VALID_LIFETIME_COL, valid_lifetime_);

            expire_ = convertFromDatabaseTime(getRawColumnValue(r, row,
                                                                EXPIRE_COL));

            getColumnValue(r, row , SUBNET_ID_COL, subnet_id_);

            cltt_ = expire_ - valid_lifetime_;

            getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);
            getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

            hostname_ = getRawColumnValue(r, row, HOSTNAME_COL);

            HWAddrPtr hwaddr(new HWAddr(hwaddr_buffer_, hwaddr_length_,
                                        HTYPE_ETHER));

            return (Lease4Ptr(new Lease4(addr4_, hwaddr,
                                         client_id_buffer_, client_id_length_,
                                         valid_lifetime_, 0, 0, cltt_,
                                         subnet_id_, fqdn_fwd_, fqdn_rev_,
                                         hostname_)));
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not convert data to Lease4, reason: "
                       << ex.what());
        }
    }

private:
    /// @brief Lease4 object currently being sent to the database.
    /// Storing this value ensures that it remains in scope while any bindings
    /// that refer to its contents are in use.
    Lease4Ptr       lease_;

    /// @Brief Lease4 specific members used for binding and conversion.
    uint32_t        addr4_;
    size_t          hwaddr_length_;
    std::vector<uint8_t> hwaddr_;
    uint8_t         hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
    size_t          client_id_length_;
    uint8_t         client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
};

/// @brief Supports exchanging IPv6 leases with PostgreSQL.
class PgSqlLease6Exchange : public PgSqlLeaseExchange {
private:

    /// @brief Column numbers for each column in the Lease6 table.
    /// These are used for both retrieving data and for looking up
    /// column labels for logging.  Note that their numeric order
    /// MUST match that of the column order in the Lease6 table.
    //@{
    static const int ADDRESS_COL = 0;
    static const int DUID_COL = 1;
    static const int VALID_LIFETIME_COL = 2;
    static const int EXPIRE_COL = 3;
    static const int SUBNET_ID_COL = 4;
    static const int PREF_LIFETIME_COL = 5;
    static const int LEASE_TYPE_COL =  6;
    static const int IAID_COL = 7;
    static const int PREFIX_LEN_COL = 8;
    static const int FQDN_FWD_COL = 9;
    static const int FQDN_REV_COL = 10;
    static const int HOSTNAME_COL = 11;
    static const int STATE_COL = 12;
    //@}
    /// @brief Number of columns in the table holding DHCPv6 leases.
    static const size_t LEASE_COLUMNS = 13;

public:
    PgSqlLease6Exchange()
        : lease_(), duid_length_(0), duid_(), iaid_u_(0), iaid_str_(""),
          lease_type_(Lease6::TYPE_NA), lease_type_str_(""), prefix_len_(0),
          prefix_len_str_(""), pref_lifetime_(0), preferred_lft_str_("") {

        BOOST_STATIC_ASSERT(12 < LEASE_COLUMNS);

        memset(duid_buffer_, 0, sizeof(duid_buffer_));

        // Set the column names (for error messages)
        column_labels_.push_back("address");
        column_labels_.push_back("duid");
        column_labels_.push_back("valid_lifetime");
        column_labels_.push_back("expire");
        column_labels_.push_back("subnet_id");
        column_labels_.push_back("pref_lifetime");
        column_labels_.push_back("lease_type");
        column_labels_.push_back("iaid");
        column_labels_.push_back("prefix_len");
        column_labels_.push_back("fqdn_fwd");
        column_labels_.push_back("fqdn_rev");
        column_labels_.push_back("hostname");
        column_labels_.push_back("state");
    }

    /// @brief Creates the bind array for sending Lease6 data to the database.
    ///
    /// Converts each Lease6 member into the appropriate form and adds it
    /// to the bind array.  Note that the array additions must occur in the
    /// order the columns are specified in the SQL statement.  By convention
    /// all columns in the table are explicitly listed in the SQL statement(s)
    /// in the same order as they occur in the table.
    ///
    /// @param lease Lease6 object that is to be written to the database
    /// @param[out] bind_array array to populate with the lease data values
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    void createBindForSend(const Lease6Ptr& lease, PsqlBindArray& bind_array) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease6 object is NULL");
        }

        // Store lease object to ensure it remains valid.
        lease_ = lease;
        try {
            addr_str_ = lease_->addr_.toText();
            bind_array.add(addr_str_);

            if (lease_->duid_) {
                bind_array.add(lease_->duid_->getDuid());
            } else {
                isc_throw (BadValue, "IPv6 Lease cannot have a null DUID");
            }

            valid_lft_str_ = boost::lexical_cast<std::string>
                             (lease->valid_lft_);
            bind_array.add(valid_lft_str_);

            expire_str_ = convertToDatabaseTime(lease->cltt_, lease_->valid_lft_);
            bind_array.add(expire_str_);

            subnet_id_str_ = boost::lexical_cast<std::string>
                             (lease->subnet_id_);
            bind_array.add(subnet_id_str_);

            preferred_lft_str_ = boost::lexical_cast<std::string>
                                 (lease_->preferred_lft_);
            bind_array.add(preferred_lft_str_);

            lease_type_str_ = boost::lexical_cast<std::string>(lease_->type_);
            bind_array.add(lease_type_str_);

            // The iaid is stored as an INT in lease6 table, so we must
            // lexically cast from an integer version to avoid out of range
            // exception failure upon insert.
            iaid_u_.uval_ = lease_->iaid_;
            iaid_str_ = boost::lexical_cast<std::string>(iaid_u_.ival_);
            bind_array.add(iaid_str_);

            prefix_len_str_ = boost::lexical_cast<std::string>
                              (static_cast<unsigned int>(lease_->prefixlen_));

            bind_array.add(prefix_len_str_);

            bind_array.add(lease->fqdn_fwd_);
            bind_array.add(lease->fqdn_rev_);

            bind_array.add(lease->hostname_);

            state_str_ = boost::lexical_cast<std::string>(lease->state_);
            bind_array.add(state_str_);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }
    }

    /// @brief Creates a Lease6 object from a given row in a result set.
    ///
    /// @param r result set containing one or rows from the Lease6 table
    /// @param row row number within the result set from to create the Lease6
    /// object.
    ///
    /// @return Lease6Ptr to the newly created Lease4 object
    /// @throw DbOperationError if the lease cannot be created.
    Lease6Ptr convertFromDatabase(const PgSqlResult& r, int row) {
        try {
            isc::asiolink::IOAddress addr(getIPv6Value(r, row, ADDRESS_COL));

            convertFromBytea(r, row, DUID_COL, duid_buffer_,
                             sizeof(duid_buffer_), duid_length_);
            DuidPtr duid_ptr(new DUID(duid_buffer_, duid_length_));

            getColumnValue(r, row, VALID_LIFETIME_COL, valid_lifetime_);

            expire_ = convertFromDatabaseTime(getRawColumnValue(r, row,
                                                                EXPIRE_COL));

            cltt_ = expire_ - valid_lifetime_;

            getColumnValue(r, row , SUBNET_ID_COL, subnet_id_);

            getColumnValue(r, row , PREF_LIFETIME_COL, pref_lifetime_);

            getLeaseTypeColumnValue(r, row, LEASE_TYPE_COL, lease_type_);

            getColumnValue(r, row , IAID_COL, iaid_u_.ival_);

            getColumnValue(r, row , PREFIX_LEN_COL, prefix_len_);

            getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);
            getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

            hostname_ = getRawColumnValue(r, row, HOSTNAME_COL);

            /// @todo: implement this in #3557.
            HWAddrPtr hwaddr;

            Lease6Ptr result(new Lease6(lease_type_, addr, duid_ptr,
                                        iaid_u_.uval_, pref_lifetime_,
                                        valid_lifetime_, 0, 0,
                                        subnet_id_, fqdn_fwd_, fqdn_rev_,
                                        hostname_, hwaddr, prefix_len_));
            result->cltt_ = cltt_;
            return (result);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not convert data to Lease6, reason: "
                       << ex.what());
        }
    }

    /// @brief Fetches an integer text column as a Lease6::Type
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// Note we depart from overloading getColumnValue to avoid ambiguity
    /// with base class methods for integers.
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getLeaseTypeColumnValue(const PgSqlResult& r, const int row,
                                 const size_t col, Lease6::Type& value) const {
        uint32_t raw_value = 0;
        getColumnValue(r, row , col, raw_value);
        switch (raw_value) {
            case Lease6::TYPE_NA:
            case Lease6::TYPE_TA:
            case Lease6::TYPE_PD:
                value = static_cast<Lease6::Type>(raw_value);
                break;

            default:
                isc_throw(DbOperationError, "Invalid lease type: " << raw_value
                      << " for: " << getColumnLabel(col) << " row:" << row);
        }
    }

    /// @brief Converts a column in a row in a result set into IPv6 address.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv6 address.
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    isc::asiolink::IOAddress getIPv6Value(const PgSqlResult& r, const int row,
                                          const size_t col) const {
        const char* data = getRawColumnValue(r, row, col);
        try {
            return (isc::asiolink::IOAddress(data));
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Cannot convert data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : " << ex.what());
        }
    }

private:
    /// @brief Lease6 object currently being sent to the database.
    /// Storing this value ensures that it remains in scope while any bindings
    /// that refer to its contents are in use.
    Lease6Ptr       lease_;

    /// @brief Lease6 specific members for binding and conversion.
    //@{
    size_t          duid_length_;
    vector<uint8_t> duid_;
    uint8_t         duid_buffer_[DUID::MAX_DUID_LEN];

    /// @brief Union for marshalling IAID into and out of the database
    /// IAID is defined in the RFC as 4 octets, which Kea code handles as
    /// a uint32_t.  Postgresql however, offers only signed integer types
    /// of sizes 2, 4, and 8 bytes (SMALLINT, INT, and BIGINT respectively).
    /// IAID is used in several indexes so rather than use the BIGINT, we
    /// use this union to safely move the value into and out of an INT column.
    union Uiaid {
        Uiaid(uint32_t val) : uval_(val){};
        Uiaid(int32_t val) : ival_(val){};
        uint32_t uval_;
        int32_t ival_;
    } iaid_u_;

    std::string iaid_str_;
    Lease6::Type    lease_type_;
    std::string lease_type_str_;
    uint8_t         prefix_len_;
    std::string prefix_len_str_;
    uint32_t        pref_lifetime_;
    std::string preferred_lft_str_;
    //@}
};

PgSqlLeaseMgr::PgSqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : LeaseMgr(), exchange4_(new PgSqlLease4Exchange()),
    exchange6_(new PgSqlLease6Exchange()), conn_(parameters) {
    conn_.openDatabase();
    int i = 0;
    for( ; tagged_statements[i].text != NULL ; ++i) {
        conn_.prepareStatement(tagged_statements[i]);
    }

    // Just in case somebody foo-barred things
    if (i != NUM_STATEMENTS) {
        isc_throw(DbOpenError, "Number of statements prepared: " << i
                  << " does not match expected count:" << NUM_STATEMENTS);
    }
}

PgSqlLeaseMgr::~PgSqlLeaseMgr() {
}

std::string
PgSqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "PostgreSQL backend " << PG_CURRENT_VERSION;
    tmp << "." << PG_CURRENT_MINOR;
    tmp << ", library " << PQlibVersion();
    return (tmp.str());
}

bool
PgSqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              PsqlBindArray& bind_array) {
    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (conn_.compareError(r, PgSqlConnection::DUPLICATE_KEY)) {
            return (false);
        }

        conn_.checkStatementError(r, tagged_statements[stindex]);
    }

    return (true);
}

bool
PgSqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(lease->addr_.toText());

    PsqlBindArray bind_array;
    exchange4_->createBindForSend(lease, bind_array);
    return (addLeaseCommon(INSERT_LEASE4, bind_array));
}

bool
PgSqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR6).arg(lease->addr_.toText());
    PsqlBindArray bind_array;
    exchange6_->createBindForSend(lease, bind_array);

    return (addLeaseCommon(INSERT_LEASE6, bind_array));
}

template <typename Exchange, typename LeaseCollection>
void PgSqlLeaseMgr::getLeaseCollection(StatementIndex stindex,
                                       PsqlBindArray& bind_array,
                                       Exchange& exchange,
                                       LeaseCollection& result,
                                       bool single) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_ADDR4).arg(tagged_statements[stindex].name);

    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    conn_.checkStatementError(r, tagged_statements[stindex]);

    int rows = PQntuples(r);
    if (single && rows > 1) {
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << tagged_statements[stindex].name);
    }

    for(int i = 0; i < rows; ++ i) {
        result.push_back(exchange->convertFromDatabase(r, i));
    }
}


void
PgSqlLeaseMgr::getLease(StatementIndex stindex, PsqlBindArray& bind_array,
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
PgSqlLeaseMgr::getLease(StatementIndex stindex, PsqlBindArray& bind_array,
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

Lease4Ptr
PgSqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_ADDR4).arg(addr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // LEASE ADDRESS
    std::string addr_str = boost::lexical_cast<std::string>
                           (static_cast<uint32_t>(addr));
    bind_array.add(addr_str);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_HWADDR).arg(hwaddr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // HWADDR
    if (!hwaddr.hwaddr_.empty()) {
        bind_array.add(hwaddr.hwaddr_);
    } else {
        bind_array.add("");
    }

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, bind_array, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_HWADDR)
              .arg(subnet_id).arg(hwaddr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // HWADDR
    if (!hwaddr.hwaddr_.empty()) {
        bind_array.add(hwaddr.hwaddr_);
    } else {
        bind_array.add("");
    }

    // SUBNET_ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_CLIENTID).arg(clientid.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // CLIENT_ID
    bind_array.add(clientid.getClientId());

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, bind_array, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_CLIENTID)
              .arg(subnet_id).arg(clientid.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // CLIENT_ID
    bind_array.add(clientid.getClientId());

    // SUBNET_ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, bind_array, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const ClientId&, const HWAddr&, SubnetID) const {
    /// This function is currently not implemented because allocation engine
    /// searches for the lease using HW address or client identifier.
    /// It never uses both parameters in the same time. We need to
    /// consider if this function is needed at all.
    isc_throw(NotImplemented, "The PgSqlLeaseMgr::getLease4 function was"
              " called, but it is not implemented");
}

Lease6Ptr
PgSqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_ADDR6)
              .arg(addr.toText()).arg(lease_type);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // LEASE ADDRESS
    std::string addr_str = addr.toText();
    bind_array.add(addr_str);

    // LEASE_TYPE
    std::string type_str_ = boost::lexical_cast<std::string>(lease_type);
    bind_array.add(type_str_);

    // ... and get the data
    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_IAID_DUID)
              .arg(iaid).arg(duid.toText()).arg(lease_type);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // DUID
    bind_array.add(duid.getDuid());

    // IAID
    std::string iaid_str = boost::lexical_cast<std::string>(iaid);
    bind_array.add(iaid_str);

    // LEASE_TYPE
    std::string lease_type_str = boost::lexical_cast<std::string>(lease_type);
    bind_array.add(lease_type_str);

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_IAID_SUBID_DUID)
              .arg(iaid).arg(subnet_id).arg(duid.toText()).arg(lease_type);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // LEASE_TYPE
    std::string lease_type_str = boost::lexical_cast<std::string>(lease_type);
    bind_array.add(lease_type_str);

    // DUID
    bind_array.add(duid.getDuid());

    // IAID
    std::string iaid_str = boost::lexical_cast<std::string>(iaid);
    bind_array.add(iaid_str);

    // SUBNET ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, bind_array, result);

    return (result);
}

void
PgSqlLeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_EXPIRED6)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE6_EXPIRE);
}

void
PgSqlLeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_EXPIRED4)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE4_EXPIRE);
}

template<typename LeaseCollection>
void
PgSqlLeaseMgr::getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                       const size_t max_leases,
                                       StatementIndex statement_index) const {
    PsqlBindArray bind_array;

    // Exclude reclaimed leases.
    std::string state_str = boost::lexical_cast<std::string>(Lease::STATE_EXPIRED_RECLAIMED);
    bind_array.add(state_str);

    // Expiration timestamp.
    std::string timestamp_str = PgSqlLeaseExchange::convertToDatabaseTime(time(NULL));
    bind_array.add(timestamp_str);

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    uint32_t limit = max_leases > 0 ? static_cast<uint32_t>(max_leases) :
        std::numeric_limits<uint32_t>::max();
    std::string limit_str = boost::lexical_cast<std::string>(limit);
    bind_array.add(limit_str);

    // Retrieve leases from the database.
    getLeaseCollection(statement_index, bind_array, expired_leases);
}


template<typename LeasePtr>
void
PgSqlLeaseMgr::updateLeaseCommon(StatementIndex stindex,
                                 PsqlBindArray& bind_array,
                                 const LeasePtr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(tagged_statements[stindex].name);

    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    conn_.checkStatementError(r, tagged_statements[stindex]);

    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));

    // Check success case first as it is the most likely outcome.
    if (affected_rows == 1) {
      return;
    }

    // If no rows affected, lease doesn't exist.
    if (affected_rows == 0) {
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_.toText() << " as it does not exist");
    }

    // Should not happen - primary key constraint should only have selected
    // one row.
    isc_throw(DbOperationError, "apparently updated more than one lease "
                  "that had the address " << lease->addr_.toText());
}


void
PgSqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_UPDATE_ADDR4).arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    PsqlBindArray bind_array;
    exchange4_->createBindForSend(lease, bind_array);

    // Set up the WHERE clause and append it to the SQL_BIND array
    std::string addr4_ = boost::lexical_cast<std::string>
                         (static_cast<uint32_t>(lease->addr_));
    bind_array.add(addr4_);

    // Drop to common update code
    updateLeaseCommon(stindex, bind_array, lease);
}

void
PgSqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_UPDATE_ADDR6).arg(lease->addr_.toText());

    // Create the BIND array for the data being updated
    PsqlBindArray bind_array;
    exchange6_->createBindForSend(lease, bind_array);

    // Set up the WHERE clause and append it to the BIND array
    std::string addr_str = lease->addr_.toText();
    bind_array.add(addr_str);

    // Drop to common update code
    updateLeaseCommon(stindex, bind_array, lease);
}

uint64_t
PgSqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex,
                                 PsqlBindArray& bind_array) {
    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    conn_.checkStatementError(r, tagged_statements[stindex]);
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));

    return (affected_rows);
}

bool
PgSqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_DELETE_ADDR).arg(addr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    if (addr.isV4()) {
        std::string addr4_str = boost::lexical_cast<std::string>
                                 (static_cast<uint32_t>(addr));
        bind_array.add(addr4_str);
        return (deleteLeaseCommon(DELETE_LEASE4, bind_array) > 0);
    }

    std::string addr6_str = addr.toText();
    bind_array.add(addr6_str);
    return (deleteLeaseCommon(DELETE_LEASE6, bind_array) > 0);
}

uint64_t
PgSqlLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE4_STATE_EXPIRED));
}

uint64_t
PgSqlLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE6_STATE_EXPIRED));
}

uint64_t
PgSqlLeaseMgr::deleteExpiredReclaimedLeasesCommon(const uint32_t secs,
                                                  StatementIndex statement_index) {
    PsqlBindArray bind_array;

    // State is reclaimed.
    std::string state_str = boost::lexical_cast<std::string>(Lease::STATE_EXPIRED_RECLAIMED);
    bind_array.add(state_str);

    // Expiration timestamp.
    std::string expiration_str =
        PgSqlLeaseExchange::convertToDatabaseTime(time(NULL) - static_cast<time_t>(secs));
    bind_array.add(expiration_str);

    // Delete leases.
    return (deleteLeaseCommon(statement_index, bind_array));
}

string
PgSqlLeaseMgr::getName() const {
    string name = "";
    try {
        name = conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

string
PgSqlLeaseMgr::getDescription() const {
    return (string("PostgreSQL Database"));
}

pair<uint32_t, uint32_t>
PgSqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_VERSION);

    PgSqlResult r(PQexecPrepared(conn_, "get_version", 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[GET_VERSION]);

    istringstream tmp;
    uint32_t version;
    tmp.str(PQgetvalue(r, 0, 0));
    tmp >> version;
    tmp.str("");
    tmp.clear();

    uint32_t minor;
    tmp.str(PQgetvalue(r, 0, 1));
    tmp >> minor;

    return make_pair<uint32_t, uint32_t>(version, minor);
}

void
PgSqlLeaseMgr::commit() {
    conn_.commit();
}

void
PgSqlLeaseMgr::rollback() {
    conn_.rollback();
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
