// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_EXCHANGE_H
#define PGSQL_EXCHANGE_H

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <cc/data.h>
#include <util/triplet.h>
#include <util/boost_time_utils.h>
#include <exceptions/exceptions.h>

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <libpq-fe.h>

#include <stdint.h>
#include <vector>
#include <iostream>

namespace isc {
namespace db {

/// @brief RAII wrapper for PostgreSQL Result sets
///
/// When a Postgresql statement is executed, the results are returned
/// in a pointer allocated structure, PGresult*. Data and status information
/// are accessed via calls to functions such as PQgetvalue() which require
/// the results pointer.  In order to ensure this structure is freed, any
/// invocation of Psql function which returns a PGresult* (e.g. PQexec,
/// PQExecPrepared, ...) must save the result to an instance of this
/// class. Example:
/// {{{
///       PgSqlResult r(PQexec(conn_, "ROLLBACK"));
/// }}}
///
/// This eliminates the need for an explicit release via, PQclear() and
/// guarantees that the resources are released even if the an exception is
/// thrown.

class PgSqlResult : public boost::noncopyable {
public:
    /// @brief Constructor
    ///
    /// Store the pointer to the fetched result set.  Set row and column
    /// counts for convenience.
    ///
    /// @param result pointer to the Postgresql client layer result
    /// If the value of is NULL, row and col values will be set to -1.
    /// This allows PgSqlResult to be passed into statement error
    /// checking.
    PgSqlResult(PGresult *result);

    /// @brief Destructor
    ///
    /// Frees the result set
    ~PgSqlResult();

    /// @brief Returns the number of rows in the result set.
    int getRows() const {
        return (rows_);
    }

    /// @brief Returns the number of columns in the result set.
    int getCols() const {
        return (cols_);
    }

    /// @brief Determines if a row index is valid
    ///
    /// @param row index to range check
    ///
    /// @throw DbOperationError if the row index is out of range
    void rowCheck(int row) const;

    /// @brief Determines if a column index is valid
    ///
    /// @param col index to range check
    ///
    /// @throw DbOperationError if the column index is out of range
    void colCheck(int col) const;

    /// @brief Determines if both a row and column index are valid
    ///
    /// @param row index to range check
    /// @param col index to range check
    ///
    /// @throw DbOperationError if either the row or column index
    /// is out of range
    void rowColCheck(int row, int col) const;

    /// @brief Fetches the name of the column in a result set
    ///
    /// Returns the column name of the column from the result set.
    /// If the column index is out of range it will return the
    /// string "Unknown column:<index>"
    ///
    /// @param col index of the column name to fetch
    /// @return string containing the name of the column
    /// This method is exception safe.
    std::string getColumnLabel(const int col) const;

    /// @brief Conversion Operator
    ///
    /// Allows the PgSqlResult object to be passed as the result set argument to
    /// PQxxxx functions.
    operator PGresult*() const {
        return (result_);
    }

    /// @brief Boolean Operator
    ///
    /// Allows testing the PgSqlResult object for emptiness: "if (result)"
    operator bool() const {
        return (result_);
    }

private:
    PGresult*     result_;     ///< Result set to be freed
    int rows_;   ///< Number of rows in the result set
    int cols_;   ///< Number of columns in the result set
};

typedef boost::shared_ptr<PgSqlResult> PgSqlResultPtr;

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
    /// @brief Constructor.
    PsqlBindArray() : values_(0), lengths_(0), formats_(0) {}

    /// @brief Vector of pointers to the data values.
    std::vector<const char*> values_;

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

    /// @brief Adds a string value to the bind array
    ///
    /// Adds a TEXT formatted value to the end of the bind array using the
    /// given string as the data source.  The caller is responsible for
    /// ensuring that string parameter remains in scope until the bind
    /// array has been discarded.
    ///
    /// @param value std::string containing the value to add.
    void add(const std::string& value);

    /// @brief Inserts a string value to the bind array before the given index
    ///
    /// Inserts a TEXT_FMT value into the bind array before the element
    /// position given by index, using the given char* as the data source.
    /// The value is expected to be NULL terminated.  The caller is responsible
    /// for ensuring that value remains in scope until the bind array has been
    /// discarded.
    ///
    /// @param value char array containing the null-terminated text to add.
    /// @param index element position before which the string should be inserted.
    ///
    /// @throw DbOperationError if value is NULL.
    /// @throw OutOfRange if the index is beyond the end of the array.
    void insert(const char* value, size_t index);

    /// @brief Inserts a string value to the bind array before the given index
    ///
    /// Inserts a TEXT_FMT value into the bind array before the element
    /// position given by index, using the given given string as the data
    /// source. This creates an internally scoped copy of the string.
    ///
    /// @param value char array containing the null-terminated text to add.
    /// @param index element position before which the string should be
    /// inserted.
    ///
    /// @throw DbOperationError if value is NULL.
    /// @throw OutOfRange if the index is beyond the end of the array.
    void insert(const std::string& value, size_t index);

    /// @brief Removes the last entry in the bind array.
    ///
    /// @throw OutOfRange if array is empty.
    void popBack();

    /// @brief Adds a vector of binary data to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source.  NOTE this does not replicate
    /// the vector, so it must remain in scope until the bind array
    /// is destroyed.
    ///
    /// @param data vector of binary bytes.
    void add(const std::vector<uint8_t>& data);

    /// @brief Adds a vector of binary data to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source. This creates an internally scoped
    /// copy of the vector.
    ///
    /// @param data vector of binary bytes.
    void addTempBinary(const std::vector<uint8_t>& data);

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

    /// @brief Adds a temporary buffer of binary data to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source.
    /// Prior to adding the buffer, it is duplicated as a ConstStringPtr
    /// and saved internally.  This guarantees the buffer remains in scope
    /// until the PsqlBindArray is destroyed, without the caller maintaining
    /// the buffer values.
    ///
    /// @param data buffer of binary data.
    /// @param len number of bytes of data in buffer
    /// @throw DbOperationError if data is NULL.
    void addTempBuffer(const uint8_t* data, const size_t len);

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

    /// @brief Adds an integer Triplet's value to the bind array
    ///
    /// Stores the current value of a triplet to the bind array.
    /// If it is unspecified it stores a NULL.
    ///
    /// @param triplet Triplet instance from which to get the value.
    void add(const isc::util::Triplet<uint32_t>& triplet);

    /// @brief Adds an integer Triplet's minimum value to the bind array
    ///
    /// Stores the minimum value of a triplet to the bind array.
    /// If it is unspecified it stores a NULL.
    ///
    /// @param triplet Triplet instance from which to get the value.
    void addMin(const isc::util::Triplet<uint32_t>& triplet);

    /// @brief Adds an integer Triplet's maximum value to the bind array
    ///
    /// Stores the maximum value of a triplet to the bind array.
    /// If it is unspecified it stores a NULL.
    ///
    /// @param triplet Triplet instance from which to get the value.
    void addMax(const isc::util::Triplet<uint32_t>& triplet);

    /// @brief Adds an @c Optional string to the bind array.
    ///
    /// Optional strings require adding a temp string to the
    /// bind array, unlike other types which implicitly do so.
    ///
    /// @param value Optional string value to add
    void addOptional(const util::Optional<std::string>& value);

    /// @brief Adds an @c Optional<type> value to the bind array.
    ///
    /// @tparam T variable type corresponding to the binding type, e.g.
    /// @c string, bool, uint8_t, @c uint16_t etc.
    /// @param value Optional of type T.
    template<typename T>
    void addOptional(const util::Optional<T>& value) {
        if (value.unspecified()) {
            addNull();
        } else {
            add(value);
        }
    }

    /// @brief Adds an IPv4 address to the bind array.
    ///
    /// This is used for inet type columns.
    ///
    /// @param value Optional boolean value to add
    /// @throw BadValue if the address is not a IPv4 address.
    void addInet4(const isc::asiolink::IOAddress& value);

    /// @brief Adds an IPv6 address to the bind array.
    ///
    /// This is used for inet type columns.
    ///
    /// @param value Optional boolean value to add
    /// @throw BadValue if the address is not a IPv6 address.
    void addInet6(const isc::asiolink::IOAddress& value);

    /// @brief Adds an @c Optional IPv4 address to the bind array.
    ///
    /// This is used for inet type columns.
    ///
    /// @param value Optional boolean value to add
    /// @throw BadValue if the address is not a IPv4 address.
    void addOptionalInet4(const util::Optional<isc::asiolink::IOAddress>& value);

    /// @brief Adds an @c Optional IPv6 address to the bind array.
    ///
    /// This is used for inet type columns which expect
    /// v4 addresses to be inserted in string form:
    /// '3001::1'
    ///
    /// @param value Optional boolean value to add
    /// @throw BadValue if the address is not a IPv6 address.
    void addOptionalInet6(const util::Optional<isc::asiolink::IOAddress>& value);


    /// @brief Adds a timestamp from a ptime to the bind array.
    ///
    /// Precision is seconds.
    ///
    /// @param timestamp Timestamp value to be sent to the database.
    /// @throw BadValue if the timestamp exceeds DatabaseConnection::MAX_DB_TIME.
    void addTimestamp(const boost::posix_time::ptime& timestamp);

    /// @brief Adds a timestamp of the current time to the bind array.
    ///
    /// Precision is seconds.
    void addTimestamp();

    /// @brief Adds an ElementPtr to the bind array
    ///
    /// Adds a TEXT_FMT value to the end of the bind array containing
    /// the JSON text output by given ElementPtr::toJSON().
    ///
    /// @param value ElementPtr containing Element tree to add.
    /// @throw DbOperationError if value is NULL.
    void add(const data::ElementPtr& value);

    /// @brief Adds a ConstElementPtr to the bind array
    ///
    /// Adds a TEXT_FMT value to the end of the bind array containing
    /// the JSON text output by given ElementPtr::toJSON().
    ///
    /// @param value ElementPtr containing Element tree to add.
    /// @throw DbOperationError if value is NULL.
    void add(const data::ConstElementPtr& value);

    /// @brief Dumps the contents of the array to a string.
    /// @return std::string containing the dump
    std::string toText() const;

    // --- the following methods are mostly useful for testing -----

    /// @brief Determines if specified value is null
    /// @param index if array holds more than one value, this index determines
    ///         which column to use
    /// @return true if the column is defined and is null
    bool amNull(size_t index = 0) const;

    /// @brief Returns the value as an integer.
    /// @param index if array holds more than one value, this index determines
    ///         which column to use
    /// @return value interpreted as specified integer type
    /// @throw OutOfRange if the offset is too large
    /// @throw BadValue if the data is null
    /// @throw boost::bad_lexical_cast if value is not an integer
    template<typename T>
    T getInteger(size_t index = 0) {
        if (values_.size() < index + 1) {
            isc_throw(OutOfRange, "Invalid index " << index << ", the values array has "
                                << values_.size() << " element(s)");
        }
        auto x = values_.at(index);
        if (!x) {
            isc_throw(BadValue, "the data in column " << index << " is null");
        }
        return (boost::lexical_cast<T>(x));
    }

    /// @brief Returns the column type
    /// @param index if array holds more than one value, this index determines
    ///         which column to use
    /// @return the type of specified column
    /// @throw BadValue if the offset is too large
    int getType(size_t index = 0 ) {
        if (formats_.size() < index + 1) {
            isc_throw(OutOfRange, "Invalid index " << index << ", the formats_ array has "
                                << formats_.size() << " element(s)");
        }
        return (formats_.at(index));
    }

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
    virtual ~PgSqlExchange() {}

    /// @brief Converts UTC time_t value to a text representation in local time.
    ///
    /// @param input_time A time_t value representing time.
    /// @return std::string containing stringified time.
    static std::string convertToDatabaseTime(const time_t input_time);

    /// @brief Converts local time_t value to a text representation in local time.
    ///
    /// @param input_time A time_t value representing time.
    /// @return std::string containing stringified time.
    static std::string convertLocalToDatabaseTime(const time_t input_time);

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
    /// epoch.  This method converts such a string to a time_t.
    ///
    /// @param db_time_val timestamp to be converted.  This value
    /// is expected to be the number of seconds since the epoch
    /// expressed as base-10 integer string.
    /// @return Converted timestamp as time_t value.
    static time_t convertFromDatabaseTime(const std::string& db_time_val);

    /// @brief Converts time stamp from the database to a boost::posix::ptime
    ///
    /// We're fetching timestamps as an integer string of seconds since the
    /// epoch. This method converts such a string to a boost::posix_time::ptime.
    ///
    /// @param db_time_val timestamp to be converted.  This value
    /// is expected to be the number of seconds since the epoch
    /// expressed as base-10 integer string.
    /// @param[out] conv_time resulting time as a ptime (UTC)
    static void convertFromDatabaseTime(const std::string& db_time_val,
                                        boost::posix_time::ptime& conv_time);

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

    /// @brief Converts a column in a row in a result set into IPv4 address.
    ///
    /// This is used to fetch values from inet type columns.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv4 address.
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static isc::asiolink::IOAddress getInetValue4(const PgSqlResult& r,
                                                  const int row,
                                                  const size_t col);

    /// @brief Converts a column in a row in a result set into IPv6 address.
    ///
    /// This is used to fetch values from inet type columns.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv6 address.
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static isc::asiolink::IOAddress getInetValue6(const PgSqlResult& r,
                                                  const int row,
                                                  const size_t col);

    /// @brief Converts a column in a row in a result set into IPv6 address.
    ///
    /// This used for IPv6 columns stored as varchar.
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

    /// @brief Fetches a timestamp column as a ptime.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value ptime parameter to receive the converted timestamp
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void getColumnValue(const PgSqlResult& r, const int row,
                               const size_t col, boost::posix_time::ptime& value);

    /// @brief Fetches a JSON column as an ElementPtr.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value ElementPtr to receive the column data
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void getColumnValue(const PgSqlResult& r, const int row,
                               const size_t col, data::ElementPtr& value);

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
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void convertFromBytea(const PgSqlResult& r, const int row,
                                 const size_t col, uint8_t* buffer,
                                 const size_t buffer_size,
                                 size_t &bytes_converted);

    /// @brief Converts a column in a row in a result set to a binary bytes
    ///
    /// Method is used to convert columns stored as BYTEA into a vector of
    /// binary bytes, (uint8_t).  It uses PQunescapeBytea to do the conversion.
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value vector to receive the converted bytes
    /// value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static void convertFromBytea(const PgSqlResult& r, const int row,
                                 const size_t col, std::vector<uint8_t>& value);

    /// @brief Fetches a uint32_t value into a Triplet using a single
    /// column value
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row.  If the column
    /// is null, the Triplet is returned as unspecified.
    /// @return Triplet to receive the column value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static isc::util::Triplet<uint32_t> getTripletValue(const PgSqlResult& r,
                                                        const int row,
                                                        const size_t col);

    /// @brief Fetches a uint32_t value into a Triplet using a three
    /// column values: default, minimum, and maximum
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param def_col the column number within the row that contains the
    /// default value.  If this column is null, the Triplet is returned
    /// as unspecified.
    /// @param min_col the column number within the row that contains the
    /// minimum value.
    /// @param max_col the column number within the row that contains the
    /// maximum value.
    /// @return Triplet to receive the column value
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    static isc::util::Triplet<uint32_t> getTripletValue(const PgSqlResult& r,
                                                        const int row,
                                                        const size_t def_col,
                                                        const size_t min_col,
                                                        const size_t max_col);

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
    std::vector<std::string> columns_;
};

/// @brief Convenience class which facilitates fetching column values
/// from a result set row.
class PgSqlResultRowWorker {
public:
    /// @brief Constructor
    ///
    /// @param r result set containing the fetched rows of data.
    /// @param row zero-based index of the desired row, (e.g.
    /// 0 .. n - 1 where n = number of rows in r)
    /// @throw DbOperationError if row value is invalid.
    PgSqlResultRowWorker(const PgSqlResult& r, const int row);

    /// @brief Indicates whether or not the given column value is null.
    ///
    /// @param col the column number within the row
    ///
    /// @return true if the value is null, false otherwise.
    bool isColumnNull(const size_t col);

    /// @brief Fetches the column value as a string.
    ///
    /// @param col the column number within the row
    ///
    /// @return std::string containing the column value.
    std::string getString(const size_t col);

    /// @brief Fetches the boolean value at the given column.
    ///
    /// @param col the column number within the row
    ///
    /// @return bool containing the column value.
    bool getBool(const size_t col);

    /// @brief Fetches the floating point value at the given column.
    ///
    /// @param col the column number within the row
    ///
    /// @return double containing the column value.
    double getDouble(const size_t col);

    /// @brief Gets a pointer to the raw column value in a result set row
    ///
    /// Given a column return a const char* pointer to the data value in
    /// the result set row.  The pointer is valid as long as the underlying
    /// result set has not been freed.  It may point to text or binary
    /// data depending on how query was structured.  You should not attempt
    /// to free this pointer.
    ///
    /// @param col the column number within the row
    ///
    /// @return a const char* pointer to the column's raw data
    const char* getRawColumnValue(const size_t col);

    /// @brief Fetches the uint64_t value at the given column.
    ///
    /// @param col the column number within the row
    ///
    /// @return uint64_t containing the column value
    uint64_t getBigInt(const size_t col);

    /// @brief Fetches the uint32_t value at the given column.
    ///
    /// @param col the column number within the row
    ///
    /// @return uint32_t containing the column value
    uint32_t getInt(const size_t col);

    /// @brief Fetches the uint16_t value at the given column.
    ///
    /// @param col the column number within the row
    ///
    /// @return uint16_t containing the column value
    uint16_t getSmallInt(const size_t col);

    /// @brief Fetches binary data at the given column into a vector.
    ///
    /// @param col the column number within the row
    /// @param[out] value vector to receive the fetched data.
    void getBytes(const size_t col, std::vector<uint8_t>& value);

    /// @brief Fetches the v4 IP address at the given column.
    ///
    /// This is used to fetch values from inet type columns.
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv4 address.
    isc::asiolink::IOAddress getInet4(const size_t col);

    /// @brief Fetches the v6 IP address at the given column.
    ///
    /// This is used to fetch values from inet type columns.
    /// @param col the column number within the row
    ///
    /// @return isc::asiolink::IOAddress containing the IPv6 address.
    isc::asiolink::IOAddress getInet6(const size_t col);

    /// @brief Fetches a text column as the given value type
    ///
    /// Uses boost::lexicalcast to convert the text column value into
    /// a value of type T.
    ///
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    template<typename T>
    void getColumnValue(const size_t col, T& value) {
        PgSqlExchange::getColumnValue(r_, row_, col, value);
    }

    /// @brief Fetches a timestamp column as a ptime.
    ///
    /// @param col the column number within the row
    /// @return ptime parameter to receive the converted timestamp
    boost::posix_time::ptime getTimestamp(const size_t col);

    /// @brief Fetches a JSON column as an ElementPtr.
    ///
    /// @param col the column number within the row
    /// @return ElementPtr parameter to receive the column value
    data::ElementPtr getJSON(const size_t col);

    /// @brief Fetches a uint32_t value into a Triplet using a single
    /// column value
    ///
    /// @param col the column number within the row If the column
    /// is null, the Triplet is returned as unspecified.
    /// @return Triplet to receive the column value
    isc::util::Triplet<uint32_t> getTriplet(const size_t col);

    /// @brief Fetches a uint32_t value into a Triplet using a three
    /// column values: default, minimum, and maximum
    ///
    /// @param def_col the column number within the row that contains the
    /// default value.  If this column is null, the Triplet is returned
    /// as unspecified.
    /// @param min_col the column number within the row that contains the
    /// minimum value.
    /// @param max_col the column number within the row that contains the
    /// maximum value.
    /// @return Triplet to receive the column value
    isc::util::Triplet<uint32_t> getTriplet(const size_t def_col,
                                            const size_t min_col,
                                            const size_t max_col);

    /// @brief Diagnostic tool which dumps the Result row contents as a string
    ///
    /// @return A string representation of the row contents.
    std::string dumpRow();

private:
    /// @brief Result set containing the row.
    const PgSqlResult& r_;

    /// @brief Index of the desired row.
    size_t row_;
};

/// @brief Pointer to a result row worker.
typedef boost::shared_ptr<PgSqlResultRowWorker> PgSqlResultRowWorkerPtr;

} // end of isc::db namespace
} // end of isc namespace

#endif // PGSQL_EXCHANGE_H
