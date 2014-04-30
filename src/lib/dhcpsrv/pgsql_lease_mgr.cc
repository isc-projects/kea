// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/pgsql_lease_mgr.h>

#include <boost/static_assert.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace {

// Maximum number of parameters used in any single query
const size_t MAX_PARAMETERS_IN_QUERY = 13;

/// @brief  Defines a single query
struct TaggedStatement {

    /// Query index
    /// @todo cppcheck flags index as unused
    // cppcheck-suppress unusedStructMember
    PgSqlLeaseMgr::StatementIndex index;

    /// Number of parameters for a given query
    int nbparams;

    /// @brief OID types
    ///
    /// Sspecify parameter types. See /usr/include/postgresql/catalog/pg_type.h.
    /// For some reason that header does not export those parameters.
    /// Those OIDs must match both input and output parameters.
    const Oid types[MAX_PARAMETERS_IN_QUERY];

    /// Short name of the query.
    const char* name;

    /// Text represenation of the actual query.
    const char* text;
};

#if 0
const OID_BOOL = 16;
const OID_BTYEA = 17;
const OID_INT8 = 20;  // 8 byte int
const OID_INT4 = 23;  // 8 byte int
const OID_INT2 = 21;  // 2 byte int
const OID_TIMESTAMP = 1114;
const OID_VARCHAR = 1043;  // ? what's diff between this and OID/25 = text
#endif

TaggedStatement tagged_statements[] = {
    {PgSqlLeaseMgr::DELETE_LEASE4, 1,
        { 20 },
        "delete_lease4",
     "DELETE FROM lease4 WHERE address = $1"},
    {PgSqlLeaseMgr::DELETE_LEASE6, 1,
        { 1043 },
        "delete_lease6",
     "DELETE FROM lease6 WHERE address = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_ADDR, 1,
        { 20 },
        "get_lease4_addr",
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire), subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE address = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_CLIENTID, 1,
        { 17 },
        "get_lease4_clientid",
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire), subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE client_id = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_CLIENTID_SUBID, 2,
        { 17, 20 },
        "get_lease4_clientid_subid",
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE client_id = $1 AND subnet_id = $2"},
    {PgSqlLeaseMgr::GET_LEASE4_HWADDR, 1,
         { 17 },
         "get_lease4_hwaddr",
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE hwaddr = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_HWADDR_SUBID, 2,
         { 17, 20 },
         "get_lease4_hwaddr_subid",
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE hwaddr = $1 AND subnet_id = $2"},
    {PgSqlLeaseMgr::GET_LEASE6_ADDR, 2,
        { 1043, 21 },
        "get_lease6_addr",
     "SELECT address, duid, valid_lifetime, "
     "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease6 "
     "WHERE address = $1 AND lease_type = $2"},
    {PgSqlLeaseMgr::GET_LEASE6_DUID_IAID, 3,
        { 17, 20, 21 },
        "get_lease6_duid_iaid",
     "SELECT address, duid, valid_lifetime, "
     "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease6 "
     "WHERE duid = $1 AND iaid = $2 AND lease_type = $3"},
    {PgSqlLeaseMgr::GET_LEASE6_DUID_IAID_SUBID, 4,
        { 21, 17, 20, 20 },
        "get_lease6_duid_iaid_subid",
     "SELECT address, duid, valid_lifetime, "
     "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease6 "
     "WHERE lease_type = $1 AND duid = $2 AND iaid = $3 AND subnet_id = $4"},
    {PgSqlLeaseMgr::GET_VERSION, 0,
        { 0 },
     "get_version",
     "SELECT version, minor FROM schema_version"},
    {PgSqlLeaseMgr::INSERT_LEASE4, 9,
         { 20, 17, 17, 20, 1114, 20, 16, 16, 1043 },
         "insert_lease4",
     "INSERT INTO lease4(address, hwaddr, client_id, "
     "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9)"},
    {PgSqlLeaseMgr::INSERT_LEASE6, 12,
        { 1043, 17, 20, 1114, 20, 20, 21, 20, 21, 16, 16, 1043 },
        "insert_lease6",
     "INSERT INTO lease6(address, duid, valid_lifetime, "
     "expire, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12)"},
    {PgSqlLeaseMgr::UPDATE_LEASE4, 10,
        { 20, 17, 17, 20, 1114, 20, 16, 16, 1043, 20 },
        "update_lease4",
     "UPDATE lease4 SET address = $1, hwaddr = $2, "
     "client_id = $3, valid_lifetime = $4, expire = $5, "
     "subnet_id = $6, fqdn_fwd = $7, fqdn_rev = $8, hostname = $9 "
     "WHERE address = $10"},
    {PgSqlLeaseMgr::UPDATE_LEASE6, 13,
        { 1043, 17, 20, 1114, 20, 20, 21, 20, 21, 16, 16, 1043, 1043 },
        "update_lease6",
     "UPDATE lease6 SET address = $1, duid = $2, "
     "valid_lifetime = $3, expire = $4, subnet_id = $5, "
     "pref_lifetime = $6, lease_type = $7, iaid = $8, "
     "prefix_len = $9, fqdn_fwd = $10, fqdn_rev = $11, hostname = $12 "
     "WHERE address = $13"},

    // End of list sentinel
    {PgSqlLeaseMgr::NUM_STATEMENTS, 0,  { 0 }, NULL, NULL}
};

};

namespace isc {
namespace dhcp {

const int PsqlBindArray::TEXT_FMT = 0;
const int PsqlBindArray::BINARY_FMT = 1;
const char* PsqlBindArray::TRUE_STR = "TRUE";
const char* PsqlBindArray::FALSE_STR = "FALSE";

void PsqlBindArray::add(const char* value) {
    values_.push_back(value);
    lengths_.push_back(strlen(value));
    formats_.push_back(TEXT_FMT);
}

void PsqlBindArray::add(const std::string& value) {
    values_.push_back(value.c_str());
    lengths_.push_back(value.size());
    formats_.push_back(TEXT_FMT);
}

void PsqlBindArray::add(const std::vector<uint8_t>& data) {
    values_.push_back(reinterpret_cast<const char*>(&(data[0])));
    lengths_.push_back(data.size());
    formats_.push_back(BINARY_FMT);
}

/// @todo not using yet
void PsqlBindArray::add(const uint32_t& value)  {
    values_.push_back(reinterpret_cast<const char*>(&value));
    lengths_.push_back(sizeof(uint32_t));
    formats_.push_back(BINARY_FMT);
}

void PsqlBindArray::add(const bool& value)  {
    add(value ? TRUE_STR : FALSE_STR);
}

std::string PsqlBindArray::toText() {
    std::ostringstream stream;
    for (int i = 0; i < values_.size(); ++i) {
        stream << i << " : [";
        if (formats_[i] == TEXT_FMT) {
            stream << values_[i];
        } else {
           stream << toHexText(values_[i], lengths_[i]);
        }
        stream <<  "]\n";
    }

    return (stream.str());
}

std::string PsqlBindArray::toHexText(const char* data, size_t len) {
    std::ostringstream stream;
    stream << "Data length is: " << len << std::endl;
    for (int i = 0; i < len; ++i) {
        if (i > 0 && ((i % 16) == 0)) {
            stream << std::endl;
        }

        stream << setfill('0') << setw(2) << setbase(16)
               << static_cast<unsigned int>(data[i]) << " ";
    }

    return (stream.str());
}

/// @brief Auxiliary PostgreSQL exchange class
class PgSqlLeaseExchange {
public:

    /// @brief Converts time_t structure to a text representation in local time.
    ///
    /// The format of the output string is "%Y-%m-%d %H:%M:%S".  Database
    /// table columns using this value should be typed as TIMESTAMP WITH
    /// TIME ZONE. For such columns Postgres assumes input strings without
    /// timezones should be treated as in local time and are converted to UTC
    /// when stored.  Likewise, these columns are automatically adjusted
    /// upon retrieval unless fetched via "extract(epoch from <column>))".
    ///
    /// @param time_val timestamp to be converted
    /// @return std::string containing the stringified time
    std::string
    convertToDatabaseTime(const time_t& time_val) {
        struct tm tinfo;
        char buffer[20];
        localtime_r(&time_val, &tinfo);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tinfo);
        return (std::string(buffer));
    }

    /// @brief Converts time stamp from the database to a time_t
    ///
    /// @param db_time_val timestamp to be converted.  This value
    /// is expected to be the number of seconds since the epoch
    /// expressed as base-10 integer string.
    /// @return Converted timestamp as time_t value.
    time_t convertFromDatabaseTime(const std::string& db_time_val) {
        // Convert string time value to time_t
        try  {
            return (boost::lexical_cast<time_t>(db_time_val));
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "Database time value is invalid: "
                                << db_time_val);
        }
    }

    /// @brief Converts Postgres text boolean representations to bool
    ///
    /// Allowed values are "t" or "f", or "" which is false.
    //  Any other will throw.
    /// @param value text value to be converted
    /// @throw BadValue if passed any value other than "t" or "f"
    bool stringToBool(const char* value) {
        if (!value || !strlen(value)) {
            return (false);
        }
        switch (value[0]) {
        case 't':
            return (true);
        case 'f':
            return (false);
        default:
            isc_throw(BadValue, "invalid bool value: " << value);
        }
    }


    const char* getColumnValue(PGresult* &r, const int row, const size_t col) {
        const char* value = PQgetvalue(r, row, col);
        if (!value) {
            isc_throw(DbOperationError, "getColumnValue no data for :"
                      << getColumnLabel(col) << " row:" << row);
        }

        return (value);
    }

    void getColumnValue(PGresult* &r, const int row, const size_t col,
                        bool &value) {
        const char* data = getColumnValue(r, row, col);
        if (!strlen(data) || *data == 'f') {
            value = false;
        } else if (*data == 't') {
            value = true;
        } else {
            isc_throw(DbOperationError, "Cannot convert data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row);
        }
    }

    void getColumnValue(PGresult* &r, const int row, const size_t col,
                        uint32_t &value) {
        const char* data = getColumnValue(r, row, col);
        try {
            value = boost::lexical_cast<uint32_t>(data);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Cannot convert data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : " << ex.what());
        }
    }

    void getColumnValue(PGresult* &r, const int row, const size_t col,
                        uint8_t &value) {
        const char* data = getColumnValue(r, row, col);
        try {
            // lexically casting as uint8_t doesn't convert from char
            value = boost::lexical_cast<uint16_t>(data);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "uint8_t:Cannot convert data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : " << ex.what());
        }
    }


    void getColumnValue(PGresult* &r, const int row, const size_t col,
                        Lease6::Type& value) {
        uint32_t raw_value = 0;
        getColumnValue(r, row , col, raw_value);
        switch (raw_value) {
            case Lease6::TYPE_NA:
                value = Lease6::TYPE_NA;
                break;

            case Lease6::TYPE_TA:
                value = Lease6::TYPE_TA;
                break;

            case Lease6::TYPE_PD:
                value = Lease6::TYPE_PD;
                break;

            default:
                isc_throw(DbOperationError, "Invalid lease type: " << raw_value
                      << " for: " << getColumnLabel(col) << " row:" << row);
        }
    }

    void convertFromBytea(PGresult* &r, const int row, const size_t col,
                          uint8_t* dest,
                          const size_t max, size_t &bytes_converted) {

        unsigned char* bytes
            = PQunescapeBytea((const unsigned char*)
                              (getColumnValue(r, row, col)), &bytes_converted);
        if (!bytes) {
            isc_throw (DbOperationError, "PQunescapeBytea failed for:"
                       << getColumnLabel(col) << " row:" << row);
        }

        if (bytes_converted > max) {
            PQfreemem(bytes);
            isc_throw (DbOperationError, "Converted data size: "
                       << bytes_converted << " is too large for: "
                       << getColumnLabel(col) << " row:" << row);
        }

        memcpy(dest, bytes, bytes_converted);
        PQfreemem(bytes);
    }

    /// Compiled statement bind parameters
    BindParams params;

    std::vector<std::string>columnLabels_;

    std::string getColumnLabel(const size_t index) {
        if (index > columnLabels_.size()) {
            ostringstream os;
            os << "Unknown column:" << index;
            return (os.str());
        }

        return (columnLabels_[index]);
    }
};


/// @brief Represents a single Lease4 exchange
class PgSqlLease4Exchange : public PgSqlLeaseExchange {
private:

    static const size_t ADDRESS_COL = 0;
    static const size_t HWADDR_COL = 1;
    static const size_t CLIENT_ID_COL = 2;
    static const size_t VALID_LIFETIME_COL = 3;
    static const size_t EXPIRE_COL = 4;
    static const size_t SUBNET_ID_COL = 5;
    static const size_t FQDN_FWD_COL = 6;
    static const size_t FQDN_REV_COL = 7;
    static const size_t HOSTNAME_COL = 8;
    /// @brief Number of columns in the table holding DHCPv4 leases.
    static const size_t LEASE_COLUMNS = 9;

public:

    /// @brief Default constructor
    PgSqlLease4Exchange() : addr4_(0), hwaddr_length_(0), client_id_length_(0) {

        BOOST_STATIC_ASSERT(8 < LEASE_COLUMNS);

        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));

        // Set the column names (for error messages)
        /// @todo something more elegant than this
        columnLabels_.push_back("address");
        columnLabels_.push_back("hwaddr");
        columnLabels_.push_back("client_id");
        columnLabels_.push_back("valid_lifetime");
        columnLabels_.push_back("expire");
        columnLabels_.push_back("subnet_id");
        columnLabels_.push_back("fqdn_fwd");
        columnLabels_.push_back("fqdn_rev");
        columnLabels_.push_back("hostname");
    }

    void
    createBindForSend(const Lease4Ptr& lease, PsqlBindArray& bind_array) {
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        addr4_str_ = boost::lexical_cast<std::string>
                     (static_cast<uint32_t>(lease->addr_));

        bind_array.add(addr4_str_);

        // Although HWADDR object will always be there, it may be just an
        // empty vector
        if (!lease->hwaddr_.empty()) {
            if (lease->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                isc_throw(DbOperationError, "Hardware address length : "
                          << lease->hwaddr_.size()
                          << " exceeds maximum allowed of: "
                          << HWAddr::MAX_HWADDR_LEN);
            }

            bind_array.add(lease->hwaddr_);
        } else {
            bind_array.add("");
        }

        if (lease->client_id_) {
            bind_array.add(lease->client_id_->getClientId());
        } else {
            bind_array.add("");
        }

        valid_lft_str_ = boost::lexical_cast<std::string>(lease->valid_lft_);
        bind_array.add(valid_lft_str_);

        expire_str_ = convertToDatabaseTime(lease->valid_lft_ + lease->cltt_);
        bind_array.add(expire_str_);

        subnet_id_str_ = boost::lexical_cast<std::string>(lease->subnet_id_);
        bind_array.add(subnet_id_str_);

        bind_array.add(lease->fqdn_fwd_);
        bind_array.add(lease->fqdn_rev_);

        bind_array.add(lease->hostname_);
    }

    Lease4Ptr
    convertFromDatabase(PGresult *& r, int row) {

        getColumnValue(r, row, ADDRESS_COL, addr4_);

        convertFromBytea(r, row, HWADDR_COL, hwaddr_buffer_,
                         sizeof(hwaddr_buffer_), hwaddr_length_);

        convertFromBytea(r, row, CLIENT_ID_COL, client_id_buffer_,
                         sizeof(client_id_buffer_), client_id_length_);

        getColumnValue(r, row, VALID_LIFETIME_COL, valid_lifetime_);

        expire_ = convertFromDatabaseTime(getColumnValue(r, row, EXPIRE_COL));

        getColumnValue(r, row , SUBNET_ID_COL, subnet_id_);

        cltt_ = expire_ - valid_lifetime_;

        getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);
        getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

        hostname_ = getColumnValue(r, row, HOSTNAME_COL);

        return (Lease4Ptr(new Lease4(addr4_, hwaddr_buffer_, hwaddr_length_,
                                     client_id_buffer_, client_id_length_,
                                     valid_lifetime_, 0, 0, cltt_, subnet_id_,
                                     fqdn_fwd_, fqdn_rev_, hostname_)));
    }

private:
    uint32_t        addr4_;
    std::string     columns_[LEASE_COLUMNS];
    std::vector<uint8_t> hwaddr_;
    uint8_t         hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
    uint8_t         client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
    Lease4Ptr       lease_;
    time_t          expire_;
    time_t          cltt_;
    uint32_t        subnet_id_;
    uint32_t        valid_lifetime_;
    unsigned long   hwaddr_length_;
    unsigned long   client_id_length_;
    bool fqdn_fwd_;
    bool fqdn_rev_;
    std::string hostname_;

    std::string addr4_str_;
    std::string valid_lft_str_;
    std::string expire_str_;
    std::string subnet_id_str_;

};


class PgSqlLease6Exchange : public PgSqlLeaseExchange {
private:
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
    static const size_t LEASE_COLUMNS = 12;

public:
    PgSqlLease6Exchange() : duid_length_(0) {

        BOOST_STATIC_ASSERT(11 < LEASE_COLUMNS);

        memset(duid_buffer_, 0, sizeof(duid_buffer_));

        // Set the column names (for error messages)
        columnLabels_.push_back("address");
        columnLabels_.push_back("duid");
        columnLabels_.push_back("valid_lifetime");
        columnLabels_.push_back("expire");
        columnLabels_.push_back("subnet_id");
        columnLabels_.push_back("pref_lifetime");
        columnLabels_.push_back("lease_type");
        columnLabels_.push_back("iaid");
        columnLabels_.push_back("prefix_len");
        columnLabels_.push_back("fqdn_fwd");
        columnLabels_.push_back("fqdn_rev");
        columnLabels_.push_back("hostname");

        params.reserve(LEASE_COLUMNS);
    }

    void
    createBindForSend(const Lease6Ptr& lease, PsqlBindArray& bind_array) {
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        addr6_ = lease_->addr_.toText();
        bind_array.add(addr6_);

        bind_array.add(lease_->duid_->getDuid());

        valid_lft_str_ = boost::lexical_cast<std::string>(lease->valid_lft_);
        bind_array.add(valid_lft_str_);

        expire_str_ = convertToDatabaseTime(lease->valid_lft_ + lease->cltt_);
        bind_array.add(expire_str_);

        subnet_id_str_ = boost::lexical_cast<std::string>(lease->subnet_id_);
        bind_array.add(subnet_id_str_);

        preferred_lft_str_ = boost::lexical_cast<std::string>
                            (lease_->preferred_lft_);
        bind_array.add(preferred_lft_str_);

        type_str_ = boost::lexical_cast<std::string>(lease_->type_);
        bind_array.add(type_str_);

        iaid_str_ = boost::lexical_cast<std::string>(lease_->iaid_);
        bind_array.add(iaid_str_);

        prefix_len_str_ = boost::lexical_cast<std::string>
                          (static_cast<unsigned int>(lease_->prefixlen_));

        bind_array.add(prefix_len_str_);

        bind_array.add(lease->fqdn_fwd_);
        bind_array.add(lease->fqdn_rev_);

        bind_array.add(lease->hostname_);
    }

    Lease6Ptr
    convertFromDatabase(PGresult * r, int row) {

        isc::asiolink::IOAddress addr(getIPv6Value(r, row, ADDRESS_COL));

        convertFromBytea(r, row, DUID_COL, duid_buffer_,
                         sizeof(duid_buffer_), duid_length_);
        DuidPtr duid_ptr(new DUID(duid_buffer_, duid_length_));

        getColumnValue(r, row, VALID_LIFETIME_COL, valid_lifetime_);

        expire_ = convertFromDatabaseTime(getColumnValue(r, row, EXPIRE_COL));

        cltt_ = expire_ - valid_lifetime_;

        getColumnValue(r, row , SUBNET_ID_COL, subnet_id_);

        getColumnValue(r, row , PREF_LIFETIME_COL, pref_lifetime_);

        getColumnValue(r, row, LEASE_TYPE_COL, lease_type_);

        getColumnValue(r, row , IAID_COL, iaid_);

        getColumnValue(r, row , PREFIX_LEN_COL, prefix_len_);

        getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);
        getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

        hostname_ = getColumnValue(r, row, HOSTNAME_COL);

        Lease6Ptr result(new Lease6(lease_type_, addr, duid_ptr, iaid_,
                                    pref_lifetime_, valid_lifetime_, 0, 0,
                                    subnet_id_, fqdn_fwd_, fqdn_rev_,
                                    hostname_, prefix_len_));

        result->cltt_ = cltt_;

        return (result);
    }

    isc::asiolink::IOAddress
    getIPv6Value(PGresult* &r, const int row, const size_t col) {
        const char* data = getColumnValue(r, row, col);
        try {
            return (isc::asiolink::IOAddress(data));
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Cannot convert data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : " << ex.what());
        }
    }

private:
    string     addr6_;
    string     columns_[LEASE_COLUMNS];
    time_t          expire_;
    vector<uint8_t> duid_;
    uint8_t         duid_buffer_[DUID::MAX_DUID_LEN];
    uint32_t        iaid_;
    Lease6Ptr       lease_;
    Lease6::Type    lease_type_;
    uint8_t         prefix_len_;
    uint32_t        pref_lifetime_;
    uint32_t        subnet_id_;
    uint32_t        valid_lifetime_;
    unsigned long   duid_length_;
    bool fqdn_fwd_;
    bool fqdn_rev_;
    std::string hostname_;
    time_t          cltt_;

    std::string valid_lft_str_;
    std::string expire_str_;
    std::string subnet_id_str_;
    std::string preferred_lft_str_;
    std::string type_str_;
    std::string iaid_str_;
    std::string prefix_len_str_;
};

PgSqlLeaseMgr::PgSqlLeaseMgr(const LeaseMgr::ParameterMap& parameters)
    : LeaseMgr(parameters), exchange4_(new PgSqlLease4Exchange()),
    exchange6_(new PgSqlLease6Exchange()), conn_(NULL) {
    openDatabase();
    prepareStatements();
}

PgSqlLeaseMgr::~PgSqlLeaseMgr() {
    if (conn_) {
        // Deallocate the prepared queries.
        PGresult* r = PQexec(conn_, "DEALLOCATE all");
        if(PQresultStatus(r) != PGRES_COMMAND_OK) {
            // Highly unlikely but we'll log it and go on.
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_DEALLOC_ERROR)
                      .arg(PQerrorMessage(conn_));
        }

        PQclear(r);
        PQfinish(conn_);
        conn_ = NULL;
    }
}

void PgSqlLeaseMgr::prepareStatements() {
    statements_.clear();
    statements_.resize(NUM_STATEMENTS, PgSqlStatementBind());

    for(int i = 0; tagged_statements[i].text != NULL; ++ i) {
        // Prepare all statements queries with all known fields datatype
        PGresult* r = PQprepare(conn_, tagged_statements[i].name,
                                tagged_statements[i].text,
                                tagged_statements[i].nbparams,
                                tagged_statements[i].types);

        if(PQresultStatus(r) != PGRES_COMMAND_OK) {
            PQclear(r);
            isc_throw(DbOperationError,
                      "unable to prepare PostgreSQL statement: "
                      << tagged_statements[i].text << ", reason: "
                      << PQerrorMessage(conn_));
        }

        statements_[i].stmt_name = tagged_statements[i].name;
        statements_[i].stmt_nbparams = tagged_statements[i].nbparams;
        PQclear(r);
    }
}

void
PgSqlLeaseMgr::openDatabase() {
    string dbconnparameters;
    string shost = "localhost";
    try {
        shost = getParameter("host");
    } catch(...) {
        // No host. Fine, we'll use "localhost"
    }

    dbconnparameters += "host = '" + shost + "'" ;

    string suser;
    try {
        suser = getParameter("user");
        dbconnparameters += " user = '" + suser + "'";
    } catch(...) {
        // No user. Fine, we'll use NULL
    }

    string spassword;
    try {
        spassword = getParameter("password");
        dbconnparameters += " password = '" + spassword + "'";
    } catch(...) {
        // No password. Fine, we'll use NULL
    }

    string sname;
    try {
        sname= getParameter("name");
        dbconnparameters += " dbname = '" + sname + "'";
    } catch(...) {
        // No database name.  Throw a "NoDatabaseName" exception
        isc_throw(NoDatabaseName, "must specify a name for the database");
    }

    conn_ = PQconnectdb(dbconnparameters.c_str());
    if (conn_ == NULL) {
        isc_throw(DbOpenError, "could not allocate connection object");
    }

    if (PQstatus(conn_) != CONNECTION_OK) {
        // If we have a connection object, we have to call finish
        // to release it, but grab the error message first.
        std::string error_message = PQerrorMessage(conn_);
        PQfinish(conn_);
        conn_ = NULL;
        isc_throw(DbOpenError, error_message);
    }
}

bool
PgSqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              PsqlBindArray& bind_array) {

    std::cout << "addLeaseCommon: bind_array: " << bind_array.toText();
    PGresult * r = PQexecPrepared(conn_, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &bind_array.values_[0],
                                  &bind_array.lengths_[0],
                                  &bind_array.formats_[0], 0);

    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK) {
        const char * errorMsg = PQerrorMessage(conn_);
        PQclear(r);

        /// @todo - ok, do we have to rely on error message text??
        /// and why is failing on duplicate key NOT an error?
        /// should be looking at global sqlca struct
        if(!strncmp(errorMsg, "ERROR:  duplicate key",
           sizeof("ERROR:  duplicate key") - 1)) {
            return (false);
        }

        isc_throw(DbOperationError, "unable to INSERT for " <<
                  statements_[stindex].stmt_name << ", reason: " <<
                  errorMsg);
    }

    PQclear(r);

    return (true);
}


bool
PgSqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              BindParams& params) {
    vector<const char *> out_values;
    vector<int> out_lengths;
    vector<int> out_formats;
    convertToQuery(params, out_values, out_lengths, out_formats);

    PGresult * r = PQexecPrepared(conn_, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &out_values[0], &out_lengths[0],
                                  &out_formats[0], 0);

    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK) {
        const char * errorMsg = PQerrorMessage(conn_);
        PQclear(r);

        /// @todo - ok, do we have to rely on error message text??
        /// and why is failing on duplicate key NOT an error?
        /// should be looking at global sqlca struct
        if(!strncmp(errorMsg, "ERROR:  duplicate key",
           sizeof("ERROR:  duplicate key") - 1)) {
            return (false);
        }

        isc_throw(DbOperationError, "unable to INSERT for " <<
                  statements_[stindex].stmt_name << ", reason: " <<
                  errorMsg);
    }

    PQclear(r);

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
                                       BindParams & params,
                                       Exchange& exchange,
                                       LeaseCollection& result,
                                       bool single) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_ADDR4).arg(statements_[stindex].stmt_name);

    vector<const char *> out_values;
    vector<int> out_lengths;
    vector<int> out_formats;
    convertToQuery(params, out_values, out_lengths, out_formats);

    PGresult* r = PQexecPrepared(conn_, statements_[stindex].stmt_name,
                       statements_[stindex].stmt_nbparams, &out_values[0],
                       &out_lengths[0], &out_formats[0], 0);

    checkStatementError(r, stindex);

    int rows = PQntuples(r);
    if (single && rows > 1) {
        PQclear(r);
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << statements_[stindex].stmt_name);
    }

    for(int i = 0; i < rows; ++ i) {
        result.push_back(exchange->convertFromDatabase(r, i));
    }

    PQclear(r);
}

void
PgSqlLeaseMgr::getLease(StatementIndex stindex, BindParams & params,
                             Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" paraeter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(stindex, params, exchange4_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
PgSqlLeaseMgr::getLease(StatementIndex stindex, BindParams & params,
                             Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" paraeter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(stindex, params, exchange6_, collection, true);

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
    BindParams inparams;
    ostringstream tmp;

    tmp << static_cast<uint32_t>(addr);
    inparams.push_back(PgSqlParam(tmp.str()));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, inparams, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_HWADDR).arg(hwaddr.toText());

    // Set up the WHERE clause value
    BindParams inparams;

    if (!hwaddr.hwaddr_.empty()) {
        inparams.push_back(PgSqlParam(hwaddr.hwaddr_));
    } else {
        inparams.push_back(PgSqlParam());
    }

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, inparams, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_HWADDR)
              .arg(subnet_id).arg(hwaddr.toText());

    // Set up the WHERE clause value
    BindParams inparams;
    ostringstream tmp;

    if (!hwaddr.hwaddr_.empty()) {
        inparams.push_back(PgSqlParam(hwaddr.hwaddr_));
    } else {
        inparams.push_back(PgSqlParam());
    }

    tmp << static_cast<unsigned long>(subnet_id);
    inparams.push_back(PgSqlParam(tmp.str()));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, inparams, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_CLIENTID).arg(clientid.toText());

    // Set up the WHERE clause value
    BindParams inparams;

    // CLIENT_ID
    inparams.push_back(PgSqlParam(clientid.getClientId()));

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, inparams, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_CLIENTID)
              .arg(subnet_id).arg(clientid.toText());

    // Set up the WHERE clause value
    BindParams inparams;
    ostringstream tmp;

    // CLIENT_ID
    inparams.push_back(PgSqlParam(clientid.getClientId()));

    tmp << static_cast<unsigned long>(subnet_id);
    inparams.push_back(PgSqlParam(tmp.str()));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, inparams, result);

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
    BindParams inparams;
    ostringstream tmp;

    // ADDRESS
    inparams.push_back(PgSqlParam(addr.toText()));

    // LEASE_TYPE
    tmp << static_cast<uint16_t>(lease_type);
    inparams.push_back(PgSqlParam(tmp.str()));

    // ... and get the data
    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, inparams, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type type, const DUID& duid,
                          uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_IAID_DUID)
              .arg(iaid).arg(duid.toText()).arg(type);

    // Set up the WHERE clause value
    BindParams inparams;
    ostringstream tmp;

    // DUID
    inparams.push_back(PgSqlParam(duid.getDuid()));

    // IAID
    tmp << static_cast<unsigned long>(iaid);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // LEASE_TYPE
    tmp << static_cast<uint16_t>(type);
    inparams.push_back(PgSqlParam(tmp.str()));

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, inparams, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_IAID_SUBID_DUID)
              .arg(iaid).arg(subnet_id).arg(duid.toText()).arg(lease_type);

    // Set up the WHERE clause value
    BindParams inparams;
    ostringstream tmp;

    // LEASE_TYPE
    tmp << static_cast<uint16_t>(lease_type);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // DUID
    inparams.push_back(PgSqlParam(duid.getDuid()));

    // IAID
    tmp << static_cast<unsigned long>(iaid);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // Subnet ID
    tmp << static_cast<unsigned long>(subnet_id);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, inparams, result);

    return (result);
}

template <typename LeasePtr>
void
PgSqlLeaseMgr::updateLeaseCommon(StatementIndex stindex,
                                 PsqlBindArray& bind_array,
                                 const LeasePtr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(statements_[stindex].stmt_name);

    PGresult * r = PQexecPrepared(conn_, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &bind_array.values_[0],
                                  &bind_array.lengths_[0],
                                  &bind_array.formats_[0], 0);

    checkStatementError(r, stindex);

    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    PQclear(r);

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


template <typename LeasePtr>
void
PgSqlLeaseMgr::updateLeaseCommon(StatementIndex stindex, BindParams & params,
                                 const LeasePtr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(statements_[stindex].stmt_name);

    vector<const char *> params_;
    vector<int> lengths_;
    vector<int> formats_;
    convertToQuery(params, params_, lengths_, formats_);

    PGresult * r = PQexecPrepared(conn_, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &params_[0], &lengths_[0], &formats_[0], 0);
    checkStatementError(r, stindex);

    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    PQclear(r);

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

bool
PgSqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex, BindParams & params) {
    vector<const char *> params_;
    vector<int> lengths_;
    vector<int> formats_;
    convertToQuery(params, params_, lengths_, formats_);

    PGresult * r = PQexecPrepared(conn_, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &params_[0], &lengths_[0], &formats_[0], 0);
    checkStatementError(r, stindex);
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    PQclear(r);

    return (affected_rows > 0);
}

bool
PgSqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_DELETE_ADDR).arg(addr.toText());

    // Set up the WHERE clause value
    BindParams inparams;

    if (addr.isV4()) {
        ostringstream tmp;
        tmp << static_cast<uint32_t>(addr);
        inparams.push_back(PgSqlParam(tmp.str()));
        return (deleteLeaseCommon(DELETE_LEASE4, inparams));
    }

    inparams.push_back(PgSqlParam(addr.toText()));
    return (deleteLeaseCommon(DELETE_LEASE6, inparams));
}

string
PgSqlLeaseMgr::getName() const {
    string name = "";
    try {
        name = getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

void
PgSqlLeaseMgr::checkStatementError(PGresult* r, StatementIndex index) const {
    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK && s != PGRES_TUPLES_OK) {
        PQclear(r);

        isc_throw(DbOperationError, "Statement exec faild:" << " for: " <<
                  statements_[index].stmt_name << ", reason: " <<
                  PQerrorMessage(conn_));
    }
}

void
PgSqlLeaseMgr::convertToQuery(const BindParams& params,
                              std::vector<const char *>& out_values,
                              std::vector<int>& out_lengths,
                              std::vector<int>& out_formats) const {
    out_values.reserve(params.size());
    out_lengths.reserve(params.size());
    out_formats.reserve(params.size());

    for(BindParams::const_iterator it = params.begin(); it != params.end();
        ++it) {
        out_values.push_back((* it).value.c_str());
        out_lengths.push_back((* it).binarylen);
        out_formats.push_back((* it).isbinary);
    }
}

string
PgSqlLeaseMgr::getDescription() const {
    return (string("PostgreSQL Database"));
}

pair<uint32_t, uint32_t>
PgSqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_VERSION);

    PGresult* r = PQexecPrepared(conn_, "get_version", 0, NULL, NULL, NULL, 0);
    checkStatementError(r, GET_VERSION);

    istringstream tmp;
    uint32_t version;
    tmp.str(PQgetvalue(r, 0, 0));
    tmp >> version;
    tmp.str("");
    tmp.clear();

    uint32_t minor;
    tmp.str(PQgetvalue(r, 0, 1));
    tmp >> minor;

    PQclear(r);

    return make_pair<uint32_t, uint32_t>(version, minor);
}

void
PgSqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_COMMIT);
    PGresult * r = PQexec(conn_, "COMMIT");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        isc_throw(DbOperationError, "commit failed: " << PQerrorMessage(conn_));
    }

    PQclear(r);
}

void
PgSqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_ROLLBACK);
    PGresult * r = PQexec(conn_, "ROLLBACK");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        isc_throw(DbOperationError, "rollback failed: "
                                    << PQerrorMessage(conn_));
    }

    PQclear(r);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
