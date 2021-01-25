// Copyright (C) 2016-2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_EXCHANGE_H
#define PGSQL_EXCHANGE_H

#include <asiolink/io_address.h>
#include <pgsql/pgsql_connection.h>

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <stdint.h>
#include <vector>
#include <iostream>

namespace isc {
namespace db {

/// @brief Structure used to bind C++ input values to dynamic SQL parameters
/// The structure contains three vectors which store the input values,
/// data lengths, and formats.  These vectors are passed directly into the
/// PostgreSQL execute call.
///
/// Note that the data values are stored as pointers. These pointers need to
/// be valid for the duration of the PostgreSQL statement execution.  In other
/// words populating them with pointers to values that go out of scope before
/// statement is executed is a bad idea.
///
/// Other than vectors or buffers of binary data, all other values are currently
/// converted to their string representation prior to sending them to PostgreSQL.
/// All of the add() method variants which accept a non-string value internally
/// create the conversion string which is then retained in the bind array to ensure
/// scope.
///
/// @brief smart pointer to const std::strings used by PsqlBindArray to ensure scope
/// of strings supplying exchange values
typedef boost::shared_ptr<const std::string> ConstStringPtr;

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
    size_t size() const {
        return (values_.size());
    }

    /// @brief Indicates it the array is empty.
    /// @return Returns true if there are no entries in the array, false
    /// otherwise.
    bool empty() const {

        return (values_.empty());
    }

    /// @brief Adds a char array to bind array based
    ///
    /// Adds a TEXT_FMT value to the end of the bind array, using the given
    /// char* as the data source.  The value is expected to be NULL
    /// terminated.  The caller is responsible for ensuring that value
    /// remains in scope until the bind array has been discarded.
    ///
    /// @param value char array containing the null-terminated text to add.
    /// @throw DbOperationError if value is NULL.
    void add(const char* value);

    /// @brief Adds an string value to the bind array
    ///
    /// Adds a TEXT formatted value to the end of the bind array using the
    /// given string as the data source.  The caller is responsible for
    /// ensuring that string parameter remains in scope until the bind
    /// array has been discarded.
    ///
    /// @param value std::string containing the value to add.
    void add(const std::string& value);

    /// @brief Adds a vector of binary data to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source.  NOTE this does not replicate
    /// the vector, so it must remain in scope until the bind array
    /// is destroyed.
    ///
    /// @param data vector of binary bytes.
    void add(const std::vector<uint8_t>& data);

    /// @brief Adds a buffer of binary data to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source. NOTE this does not replicate
    /// the buffer, so it must remain in scope until the bind array
    /// is destroyed.
    ///
    /// @param data buffer of binary data.
    /// @param len  number of bytes of data in buffer
    /// @throw DbOperationError if data is NULL.
    void add(const uint8_t* data, const size_t len);

    /// @brief Adds a boolean value to the bind array.
    ///
    /// Converts the given boolean value to its corresponding to PostgreSQL
    /// string value and adds it as a TEXT_FMT value to the bind array.
    /// This creates an internally scoped string.
    ///
    /// @param value the boolean value to add.
    void add(const bool& value);

    /// @brief Adds a uint8_t value to the bind array.
    ///
    /// Converts the given uint8_t value to its corresponding numeric string
    /// literal and adds it as a TEXT_FMT value to the bind array.
    /// This creates an internally scoped string.
    ///
    /// @param byte the one byte value to add.
    void add(const uint8_t& byte);

    /// @brief Adds the given IOAddress value to the bind array.
    ///
    /// Converts the IOAddress, based on its protocol family, to the
    /// corresponding string literal and adds it as a TEXT_FMT value to
    /// the bind array.
    /// This creates an internally scoped string.
    ///
    /// @param addr IP address value to add.
    void add(const isc::asiolink::IOAddress& addr);

    /// @brief Adds the given value to the bind array.
    ///
    /// Converts the given value to its corresponding string literal
    /// boost::lexical_cast and adds it as a TEXT_FMT value to the bind array.
    /// This is intended primarily for numeric types.
    /// This creates an internally scoped string.
    ///
    /// @param value data value to add.
    template<typename T>
    void add(const T& value) {
        addTempString(boost::lexical_cast<std::string>(value));
    }

    /// @brief Binds the given string to the bind array.
    ///
    /// Prior to add the given string the vector of exchange values,
    /// it duplicated as a ConstStringPtr and saved internally.  This guarantees
    /// the string remains in scope until the PsqlBindArray is destroyed,
    /// without the caller maintaining the string values.
    ///
    /// @param str string value to add.
    void addTempString(const std::string& str);

    /// @brief Adds a NULL value to the bind array
    ///
    /// This should be used whenever the value for a parameter specified
    /// in the SQL statement should be NULL.
    void addNull(const int format = PsqlBindArray::TEXT_FMT);

    //std::vector<const std::string> getBoundStrs() {
    std::vector<ConstStringPtr> getBoundStrs() {
        return (bound_strs_);
    }

    /// @brief Dumps the contents of the array to a string.
    /// @return std::string containing the dump
    std::string toText() const;

private:
    /// @brief vector of strings which supplied the values
    std::vector<ConstStringPtr> bound_strs_;

};

/// @brief Defines a smart pointer to PsqlBindArray
typedef boost::shared_ptr<PsqlBindArray> PsqlBindArrayPtr;

/// @brief Base class for marshalling data to and from PostgreSQL.
///
/// Provides the common functionality to set up binding information between
/// application objects in the program and their representation in the
/// database, and for retrieving column values from rows of a result set.
class PgSqlExchange {
public:
    /// @brief Constructor
    PgSqlExchange(const size_t num_columns = 0) : columns_(num_columns) {}

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
    /// Unless we start using binary input, timestamp columns must be input as
    /// date/time strings.
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
    /// We're fetching timestamps as an integer string of seconds since the
    /// epoch.  This method converts such a string int a time_t.
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
    static const char* getRawColumnValue(const PgSqlResult& r, const int row,
                                         const size_t col);

    /// @brief Fetches the name of the column in a result set
    ///
    /// Returns the column name of the column from the result set.
    /// If the column index is out of range it will return the
    /// string "Unknown column:<index>".  Note this is NOT from the
    /// list of columns defined in the exchange.
    ///
    /// @param r the result set containing the query results
    /// @param col index of the column name to fetch
    ///
    /// @return string containing the name of the column
    static std::string getColumnLabel(const PgSqlResult& r, const size_t col);

    /// @brief Fetches text column value as a string
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the string value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void getColumnValue(const PgSqlResult& r, const int row,
                               const size_t col, std::string& value);

    /// @brief Fetches boolean text ('t' or 'f') as a bool.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void getColumnValue(const PgSqlResult& r, const int row,
                               const size_t col, bool &value);

    /// @brief Fetches an integer text column as a uint8_t.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void getColumnValue(const PgSqlResult& r, const int row,
                               const size_t col, uint8_t &value);

    /// @brief Converts a column in a row in a result set into IPv6 address.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv6 address.
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static isc::asiolink::IOAddress getIPv6Value(const PgSqlResult& r,
                                                 const int row,
                                                 const size_t col);

    /// @brief Returns true if a column within a row is null
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return True if the column values in the row is NULL, false otherwise.
    static bool isColumnNull(const PgSqlResult& r, const int row,
                             const size_t col);

    /// @brief Fetches a text column as the given value type
    ///
    /// Uses boost::lexicalcast to convert the text column value into
    /// a value of type T.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    template<typename T>
    static void getColumnValue(const PgSqlResult& r, const int row,
                               const size_t col, T& value) {
        const char* data = getRawColumnValue(r, row, col);
        try {
            value = boost::lexical_cast<T>(data);
        } catch (const std::exception& ex) {
            isc_throw(db::DbOperationError, "Invalid data:[" << data
                      << "] for row: " << row << " col: " << col << ","
                      << getColumnLabel(r, col) << " : " << ex.what());
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
    static void convertFromBytea(const PgSqlResult& r, const int row,
                                 const size_t col, uint8_t* buffer,
                                 const size_t buffer_size,
                                 size_t &bytes_converted);

    /// @brief Diagnostic tool which dumps the Result row contents as a string
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    ///
    /// @return A string depiction of the row contents.
    static std::string dumpRow(const PgSqlResult& r, int row);

protected:
    /// @brief Stores text labels for columns, currently only used for
    /// logging and errors.
    std::vector<std::string>columns_;
};

}; // end of isc::db namespace
}; // end of isc namespace

#endif // PGSQL_EXCHANGE_H
