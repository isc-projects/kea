// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_EXCHANGE_MGR_H
#define PGSQL_EXCHANGE_MGR_H

#include <dhcpsrv/pgsql_connection.h>

#include <vector>

namespace isc {
namespace dhcp {

/// @brief Structure used to bind C++ input values to dynamic SQL parameters
/// The structure contains three vectors which store the input values,
/// data lengths, and formats.  These vectors are passed directly into the
/// PostgreSQL execute call.
///
/// Note that the data values are stored as pointers. These pointers need to
/// valid for the duration of the PostgreSQL statement execution.  In other
/// words populating them with pointers to values that go out of scope before
/// statement is executed is a bad idea.
struct PsqlBindArray {
    /// @brief Vector of pointers to the data values.
    std::vector<const char *> values_;
    /// @brief Vector of data lengths for each value.
    std::vector<int> lengths_;
    /// @brief Vector of "format" for each value. A value of 0 means the
    /// value is text, 1 means the value is binary.
    std::vector<int> formats_;

    /// @brief Format value for text data.
    static const int TEXT_FMT;
    /// @brief Format value for binary data.
    static const int BINARY_FMT;

    /// @brief Constant string passed to DB for boolean true values.
    static const char* TRUE_STR;
    /// @brief Constant string passed to DB for boolean false values.
    static const char* FALSE_STR;

    /// @brief Fetches the number of entries in the array.
    /// @return Returns size_t containing the number of entries.
    size_t size() {
        return (values_.size());
    }

    /// @brief Indicates it the array is empty.
    /// @return Returns true if there are no entries in the array, false
    /// otherwise.
    bool empty() {

        return (values_.empty());
    }

    /// @brief Adds a char array to bind array based
    ///
    /// Adds a TEXT_FMT value to the end of the bind array, using the given
    /// char* as the data source. Note that value is expected to be NULL
    /// terminated.
    ///
    /// @param value char array containing the null-terminated text to add.
    void add(const char* value);

    /// @brief Adds an string value to the bind array
    ///
    /// Adds a TEXT formatted value to the end of the bind array using the
    /// given string as the data source.
    ///
    /// @param value std::string containing the value to add.
    void add(const std::string& value);

    /// @brief Adds a binary value to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source.
    ///
    /// @param data vector of binary bytes.
    void add(const std::vector<uint8_t>& data);

    /// @brief Adds a boolean value to the bind array.
    ///
    /// Converts the given boolean value to its corresponding to PostgreSQL
    /// string value and adds it as a TEXT_FMT value to the bind array.
    ///
    /// @param value bool value to add.
    void add(const bool& value);

    /// @brief Dumps the contents of the array to a string.
    /// @return std::string containing the dump
    std::string toText();
};

/// @brief Base class for marshalling data to and from PostgreSQL.
///
/// Provides the common functionality to set up binding information between
/// application objects in the program and their representation in the
/// database, and for retrieving column values from rows of a result set.
class PgSqlExchange {
public:
    /// @brief Constructor
    PgSqlExchange(){}

    /// @brief Destructor
    virtual ~PgSqlExchange(){}

    /// @brief Converts time_t value to a text representation in local time.
    ///
    /// @param input_time A time_t value representing time.
    /// @return std::string containing stringified time.
    static std::string convertToDatabaseTime(const time_t input_time);

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
    /// greater than the value of @c DataSource::MAX_DB_TIME.
    static std::string convertToDatabaseTime(const time_t cltt,
                                             const uint32_t valid_lifetime);

    /// @brief Converts time stamp from the database to a time_t
    ///
    /// @param db_time_val timestamp to be converted.  This value
    /// is expected to be the number of seconds since the epoch
    /// expressed as base-10 integer string.
    /// @return Converted timestamp as time_t value.
    static time_t convertFromDatabaseTime(const std::string& db_time_val);

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
    const char* getRawColumnValue(const PgSqlResult& r, const int row,
                                  const size_t col) const;

    /// @brief Fetches boolean text ('t' or 'f') as a bool.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(const PgSqlResult& r, const int row, const size_t col,
                        bool &value) const;

    /// @brief Fetches an integer text column as a uint32_t.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(const PgSqlResult& r, const int row, const size_t col,
                        uint32_t &value) const;

    /// @brief Fetches an integer text column as a int32_t.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(const PgSqlResult& r, const int row, const size_t col,
                        int32_t &value) const;

    /// @brief Fetches an integer text column as a uint8_t.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getColumnValue(const PgSqlResult& r, const int row, const size_t col,
                        uint8_t &value) const;

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
    void convertFromBytea(const PgSqlResult& r, const int row, const size_t col,
                          uint8_t* buffer, const size_t buffer_size,
                          size_t &bytes_converted) const;

    /// @brief Returns column label given a column number
    std::string getColumnLabel(const size_t column) const;

protected:
    /// @brief Stores text labels for columns, currently only used for
    /// logging and errors.
    std::vector<std::string>column_labels_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PGSQL_EXCHANGE_MGR_H
