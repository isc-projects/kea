// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <limits>
#include <sstream>
#include <string>
#include <time.h>

// PostgreSQL errors should be tested based on the SQL state code.  Each state
// code is 5 decimal, ASCII, digits, the first two define the category of
// error, the last three are the specific error.  PostgreSQL makes the state
// code as a char[5].  Macros for each code are defined in PostgreSQL's
// errorcodes.h, although they require a second macro, MAKE_SQLSTATE for
// completion.  PostgreSQL deliberately omits this macro from errocodes.h
// so callers can supply their own.
#define MAKE_SQLSTATE(ch1,ch2,ch3,ch4,ch5) {ch1,ch2,ch3,ch4,ch5}
#include <utils/errcodes.h>
const size_t STATECODE_LEN = 5;

// Currently the only one we care to look for is duplicate key.
const char DUPLICATE_KEY[] = ERRCODE_UNIQUE_VIOLATION;

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace {

// Maximum number of parameters used in any single query
const size_t MAX_PARAMETERS_IN_QUERY = 14;

/// @brief  Defines a single query
struct TaggedStatement {

    /// Number of parameters for a given query
    int nbparams;

    /// @brief OID types
    ///
    /// Specify parameter types. See /usr/include/postgresql/catalog/pg_type.h.
    /// For some reason that header does not export those parameters.
    /// Those OIDs must match both input and output parameters.
    const Oid types[MAX_PARAMETERS_IN_QUERY];

    /// Short name of the query.
    const char* name;

    /// Text representation of the actual query.
    const char* text;
};

/// @brief Constants for PostgreSQL data types
/// This are defined by PostreSQL in <catalog/pg_type.h>, but including
/// this file is extrordinarily convoluted, so we'll use these to fill-in.
const size_t OID_NONE = 0;   // PostgreSQL infers proper type
const size_t OID_BOOL = 16;
const size_t OID_BYTEA = 17;
const size_t OID_INT8 = 20;  // 8 byte int
const size_t OID_INT2 = 21;  // 2 byte int
const size_t OID_TIMESTAMP = 1114;
const size_t OID_VARCHAR = 1043;

/// @brief Catalog of all the SQL statements currently supported.  Note
/// that the order columns appear in statement body must match the order they
/// that the occur in the table.  This does not apply to the where clause.
TaggedStatement tagged_statements[] = {
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

void PsqlBindArray::add(const bool& value)  {
    add(value ? TRUE_STR : FALSE_STR);
}

std::string PsqlBindArray::toText() {
    std::ostringstream stream;
    for (int i = 0; i < values_.size(); ++i) {
        stream << i << " : ";
        if (formats_[i] == TEXT_FMT) {
            stream << "\"" << values_[i] << "\"" << std::endl;
        } else {
            const char *data = values_[i];
            if (lengths_[i] == 0) {
                stream << "empty" << std::endl;
            } else {
                stream << "0x";
                for (int i = 0; i < lengths_[i]; ++i) {
                    stream << setfill('0') << setw(2) << setbase(16)
                         << static_cast<unsigned int>(data[i]);
                }
                stream << std::endl;
            }
        }
    }

    return (stream.str());
}

/// @brief Base class for marshalling leases to and from PostgreSQL.
///
/// Provides the common functionality to set up binding information between
/// lease objects in the program and their database representation in the
/// database.
class PgSqlLeaseExchange {
public:


    PgSqlLeaseExchange()
        : addr_str_(""), valid_lifetime_(0), valid_lft_str_(""),
          expire_(0), expire_str_(""), subnet_id_(0), subnet_id_str_(""),
          cltt_(0), fqdn_fwd_(false), fqdn_rev_(false), hostname_(""),
          state_str_("") {
    }

    virtual ~PgSqlLeaseExchange(){}

    /// @brief Converts time_t value to a text representation in local time.
    ///
    /// @param input_time A time_t value representing time.
    /// @return std::string containing stringified time.
    static std::string
    convertToDatabaseTime(const time_t input_time) {
        struct tm tinfo;
        char buffer[20];
        localtime_r(&input_time, &tinfo);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tinfo);
        return (std::string(buffer));
    }

    /// @brief Converts lease expiration time to a text representation in
    /// local time.
    ///
    /// The expiration time is calculated as a sum of the cltt (client last
    /// transmit time) and the valid lifetime.
    ///
    /// The format of the output string is "%Y-%m-%d %H:%M:%S".  Database
    /// table columns using this value should be typed as TIMESTAMP WITH
    /// TIME ZONE. For such columns PostgreSQL assumes input strings without
    /// timezones should be treated as in local time and are converted to UTC
    /// when stored.  Likewise, these columns are automatically adjusted
    /// upon retrieval unless fetched via "extract(epoch from <column>))".
    ///
    /// @param cltt Client last transmit time
    /// @param valid_lifetime Valid lifetime
    ///
    /// @return std::string containing the stringified time
    /// @throw isc::BadValue if the sum of the calculated expiration time is
    /// greater than the value of @c LeaseMgr::MAX_DB_TIME.
    static std::string
    convertToDatabaseTime(const time_t cltt, const uint32_t valid_lifetime) {
        // Calculate expiry time. Store it in the 64-bit value so as we can detect
        // overflows.
        int64_t expire_time_64 = static_cast<int64_t>(cltt) +
            static_cast<int64_t>(valid_lifetime);

        // It has been observed that the PostgreSQL doesn't deal well with the
        // timestamp values beyond the LeaseMgr::MAX_DB_TIME seconds since the
        // beginning of the epoch (around year 2038). The value is often
        // stored in the database but it is invalid when read back (overflow?).
        // Hence, the maximum timestamp value is restricted here.
        if (expire_time_64 > LeaseMgr::MAX_DB_TIME) {
            isc_throw(isc::BadValue, "Time value is too large: " << expire_time_64);
        }

        return (convertToDatabaseTime(static_cast<time_t>(expire_time_64)));
    }

    /// @brief Converts time stamp from the database to a time_t
    ///
    /// @param db_time_val timestamp to be converted.  This value
    /// is expected to be the number of seconds since the epoch
    /// expressed as base-10 integer string.
    /// @return Converted timestamp as time_t value.
    static time_t convertFromDatabaseTime(const std::string& db_time_val) {
        // Convert string time value to time_t
        try  {
            return (boost::lexical_cast<time_t>(db_time_val));
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "Database time value is invalid: "
                                << db_time_val);
        }
    }

    /// @brief Gets a pointer to the raw column value in a result set row
    ///
    /// Given a result set, row, and column return a const char* pointer to
    /// the data value in the result set.  The pointer is valid as long as
    /// the result set has not been freed.  It may point to text or binary
    /// data depending on how query was structured.  You should not attempt
    /// to free this pointer.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return a const char* pointer to the column's raw data
    /// @throw  DbOperationError if the value cannot be fetched.
    const char* getRawColumnValue(PGresult*& r, const int row,
                                  const size_t col) const {
        const char* value = PQgetvalue(r, row, col);
        if (!value) {
            isc_throw(DbOperationError, "getRawColumnValue no data for :"
                      << getColumnLabel(col) << " row:" << row);
        }

        return (value);
    }

    /// @brief Converts a column in a row in a result set to a boolean.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(PGresult*& r, const int row, const size_t col,
                        bool &value) const {
        const char* data = getRawColumnValue(r, row, col);
        if (!strlen(data) || *data == 'f') {
            value = false;
        } else if (*data == 't') {
            value = true;
        } else {
            isc_throw(DbOperationError, "Invalid boolean data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : must be 't' or 'f'");
        }
    }

    /// @brief Converts a column in a row in a result set to a uint32_t.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(PGresult*& r, const int row, const size_t col,
                        uint32_t &value) const {
        const char* data = getRawColumnValue(r, row, col);
        try {
            value = boost::lexical_cast<uint32_t>(data);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Invalid uint32_t data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : " << ex.what());
        }
    }

    /// @brief Converts a column in a row in a result set to a uint8_t.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(PGresult*& r, const int row, const size_t col,
                        uint8_t &value) const {
        const char* data = getRawColumnValue(r, row, col);
        try {
            // lexically casting as uint8_t doesn't convert from char
            // so we use uint16_t and implicitly convert.
            value = boost::lexical_cast<uint16_t>(data);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Invalid uint8_t data: " << data
                      << " for: " << getColumnLabel(col) << " row:" << row
                      << " : " << ex.what());
        }
    }

    /// @brief Converts a column in a row in a result set to a Lease6::Type
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(PGresult*& r, const int row, const size_t col,
                        Lease6::Type& value) const {
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

    /// @brief Converts a column in a row in a result set to a binary bytes
    ///
    /// Method is used to convert columns stored as BYTEA into a buffer of
    /// binary bytes, (uint8_t).  It uses PQunescapeBytea to do the conversion.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] buffer pre-allocated buffer to which the converted bytes
    /// will be stored.
    /// @param buffer_size size of the output buffer
    /// @param[out] bytes_converted number of bytes converted
    /// value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void convertFromBytea(PGresult*& r, const int row, const size_t col,
                          uint8_t* buffer,
                          const size_t buffer_size,
                          size_t &bytes_converted) const {

        // Returns converted bytes in a dynamically allocated buffer, and
        // sets bytes_converted.
        unsigned char* bytes = PQunescapeBytea((const unsigned char*)
                                               (getRawColumnValue(r, row, col)),
                                               &bytes_converted);

        // Unlikely it couldn't allocate it but you never know.
        if (!bytes) {
            isc_throw (DbOperationError, "PQunescapeBytea failed for:"
                       << getColumnLabel(col) << " row:" << row);
        }

        // Make sure it's not larger than expected.
        if (bytes_converted > buffer_size) {
            // Free the allocated buffer first!
            PQfreemem(bytes);
            isc_throw (DbOperationError, "Converted data size: "
                       << bytes_converted << " is too large for: "
                       << getColumnLabel(col) << " row:" << row);
        }

        // Copy from the allocated buffer to caller's buffer the free up
        // the allocated buffer.
        memcpy(buffer, bytes, bytes_converted);
        PQfreemem(bytes);
    }

    /// @brief Returns column label given a column number
    std::string getColumnLabel(const size_t column) const {
        if (column > column_labels_.size()) {
            ostringstream os;
            os << "Unknown column:" << column;
            return (os.str());
        }

        return (column_labels_[column]);
    }

protected:
    /// @brief Stores text labels for columns, currently only used for
    /// logging and errors.
    std::vector<std::string>column_labels_;

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
    Lease4Ptr convertFromDatabase(PGresult*& r, int row) {
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
        : lease_(), duid_length_(0), duid_(), iaid_(0), iaid_str_(""),
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

            iaid_str_ = boost::lexical_cast<std::string>(lease_->iaid_);
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
    Lease6Ptr convertFromDatabase(PGresult*& r, int row) {
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

            getColumnValue(r, row, LEASE_TYPE_COL, lease_type_);

            getColumnValue(r, row , IAID_COL, iaid_);

            getColumnValue(r, row , PREFIX_LEN_COL, prefix_len_);

            getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);
            getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

            hostname_ = getRawColumnValue(r, row, HOSTNAME_COL);

            /// @todo: implement this in #3557.
            HWAddrPtr hwaddr;

            Lease6Ptr result(new Lease6(lease_type_, addr, duid_ptr, iaid_,
                                        pref_lifetime_, valid_lifetime_, 0, 0,
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

    /// @brief Converts a column in a row in a result set into IPv6 address.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv6 address.
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    isc::asiolink::IOAddress getIPv6Value(PGresult*& r, const int row,
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
    uint32_t        iaid_;
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
    exchange6_(new PgSqlLease6Exchange()), dbconn_(parameters), conn_(NULL) {
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

std::string
PgSqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "PostgreSQL backend " << PG_CURRENT_VERSION;
    tmp << "." << PG_CURRENT_MINOR;
    tmp << ", library " << PQlibVersion();
    return (tmp.str());
}

void
PgSqlLeaseMgr::prepareStatements() {
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

        PQclear(r);
    }
}

void
PgSqlLeaseMgr::openDatabase() {
    string dbconnparameters;
    string shost = "localhost";
    try {
        shost = dbconn_.getParameter("host");
    } catch(...) {
        // No host. Fine, we'll use "localhost"
    }

    dbconnparameters += "host = '" + shost + "'" ;

    string suser;
    try {
        suser = dbconn_.getParameter("user");
        dbconnparameters += " user = '" + suser + "'";
    } catch(...) {
        // No user. Fine, we'll use NULL
    }

    string spassword;
    try {
        spassword = dbconn_.getParameter("password");
        dbconnparameters += " password = '" + spassword + "'";
    } catch(...) {
        // No password. Fine, we'll use NULL
    }

    string sname;
    try {
        sname= dbconn_.getParameter("name");
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
    PGresult* r = PQexecPrepared(conn_, tagged_statements[stindex].name,
                                  tagged_statements[stindex].nbparams,
                                  &bind_array.values_[0],
                                  &bind_array.lengths_[0],
                                  &bind_array.formats_[0], 0);

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (compareError(r, DUPLICATE_KEY)) {
            PQclear(r);
            return (false);
        }

        const char* errorMsg = PQerrorMessage(conn_);
        PQclear(r);
        isc_throw(DbOperationError, "unable to INSERT for " <<
                  tagged_statements[stindex].name << ", reason: " <<
                  errorMsg);
    }

    PQclear(r);

    return (true);
}

bool PgSqlLeaseMgr::compareError(PGresult*& r, const char* error_state) {
    const char* sqlstate = PQresultErrorField(r, PG_DIAG_SQLSTATE);
    // PostgreSQL garuantees it will always be 5 characters long
    return ((sqlstate != NULL) &&
            (memcmp(sqlstate, error_state, STATECODE_LEN) == 0));
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

    PGresult* r = PQexecPrepared(conn_, tagged_statements[stindex].name,
                       tagged_statements[stindex].nbparams,
                       &bind_array.values_[0],
                       &bind_array.lengths_[0],
                       &bind_array.formats_[0], 0);

    checkStatementError(r, stindex);

    int rows = PQntuples(r);
    if (single && rows > 1) {
        PQclear(r);
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << tagged_statements[stindex].name);
    }

    for(int i = 0; i < rows; ++ i) {
        result.push_back(exchange->convertFromDatabase(r, i));
    }

    PQclear(r);
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
    bind_array.add(boost::lexical_cast<std::string>(Lease::STATE_EXPIRED_RECLAIMED));

    // Expiration timestamp.
    bind_array.add(PgSqlLeaseExchange::convertToDatabaseTime(time(NULL)));

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    uint32_t limit = max_leases > 0 ? static_cast<uint32_t>(max_leases) :
        std::numeric_limits<uint32_t>::max();
    bind_array.add(boost::lexical_cast<std::string>(limit));

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

    PGresult* r = PQexecPrepared(conn_, tagged_statements[stindex].name,
                                  tagged_statements[stindex].nbparams,
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
    PGresult* r = PQexecPrepared(conn_, tagged_statements[stindex].name,
                                  tagged_statements[stindex].nbparams,
                                  &bind_array.values_[0],
                                  &bind_array.lengths_[0],
                                  &bind_array.formats_[0], 0);

    checkStatementError(r, stindex);
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    PQclear(r);

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
    bind_array.add(boost::lexical_cast<std::string>(Lease::STATE_EXPIRED_RECLAIMED));

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
        name = dbconn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

void
PgSqlLeaseMgr::checkStatementError(PGresult*& r, StatementIndex index) const {
    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK && s != PGRES_TUPLES_OK) {
        const char* error_message = PQerrorMessage(conn_);
        PQclear(r);
        isc_throw(DbOperationError, "Statement exec faild:" << " for: "
                  << tagged_statements[index].name << ", reason: "
                  << error_message);
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
    PGresult* r = PQexec(conn_, "COMMIT");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        PQclear(r);
        isc_throw(DbOperationError, "commit failed: " << error_message);
    }

    PQclear(r);
}

void
PgSqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_ROLLBACK);
    PGresult* r = PQexec(conn_, "ROLLBACK");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        const char* error_message = PQerrorMessage(conn_);
        PQclear(r);
        isc_throw(DbOperationError, "rollback failed: " << error_message);
    }

    PQclear(r);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
