// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_BINDING_H
#define MYSQL_BINDING_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <database/database_connection.h>
#include <exceptions/exceptions.h>
#include <util/optional.h>
#include <boost/date_time/posix_time/conversion.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <mysql/mysql_constants.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>

namespace isc {
namespace db {

/// @brief Trait class for column types supported in MySQL.
///
/// This class is used to map C++ types to MySQL column types
/// defined in MySQL C API and their sizes. Specializations of
/// this class provide such mapping. The default is a BLOB type
/// which can be used for various input types.
template<typename T>
struct MySqlBindingTraits {
    /// @brief Column type represented in MySQL C API.
    static const enum_field_types column_type = MYSQL_TYPE_BLOB;
    /// @brief Length of data in this column.
    ///
    /// The value of 0 is used for variable size columns.
    static const size_t length = 0;
    /// @brief Boolean value indicating if the numeric value is
    /// unsigned.
    static const bool am_unsigned = false;
};

/// @brief Specialization for MySQL TEXT type.
template<>
struct MySqlBindingTraits<std::string> {
    static const enum_field_types column_type = MYSQL_TYPE_STRING;
    static const size_t length = 0;
    static const bool am_unsigned = false;
};

/// @brief Specialization for MySQL TIMESTAMP type.
template<>
struct MySqlBindingTraits<boost::posix_time::ptime> {
    static const enum_field_types column_type = MYSQL_TYPE_TIMESTAMP;
    static const size_t length = sizeof(MYSQL_TIME);
    static const bool am_unsignged = false;
};

/// @brief Specialization for MySQL TINYINT type.
template<>
struct MySqlBindingTraits<int8_t> {
    static const enum_field_types column_type = MYSQL_TYPE_TINY;
    static const size_t length = 1;
    static const bool am_unsigned = false;
};

/// @brief Specialization for MySQL TINYINT UNSIGNED type.
template<>
struct MySqlBindingTraits<uint8_t> {
    static const enum_field_types column_type = MYSQL_TYPE_TINY;
    static const size_t length = 1;
    static const bool am_unsigned = true;
};

/// @brief Speclialization for MySQL SMALLINT type.
template<>
struct MySqlBindingTraits<int16_t> {
    static const enum_field_types column_type = MYSQL_TYPE_SHORT;
    static const size_t length = 2;
    static const bool am_unsigned = false;
};

/// @brief Specialization for MySQL SMALLINT UNSIGNED type.
template<>
struct MySqlBindingTraits<uint16_t> {
    static const enum_field_types column_type = MYSQL_TYPE_SHORT;
    static const size_t length = 2;
    static const bool am_unsigned = true;
};

/// @brief Specialization for MySQL INT type.
template<>
struct MySqlBindingTraits<int32_t> {
    static const enum_field_types column_type = MYSQL_TYPE_LONG;
    static const size_t length = 4;
    static const bool am_unsigned = false;
};

/// @brief Specialization for MySQL INT UNSIGNED type.
template<>
struct MySqlBindingTraits<uint32_t> {
    static const enum_field_types column_type = MYSQL_TYPE_LONG;
    static const size_t length = 4;
    static const bool am_unsigned = true;
};

/// @brief Specialization for MySQL BIGINT type.
template<>
struct MySqlBindingTraits<int64_t> {
    static const enum_field_types column_type = MYSQL_TYPE_LONGLONG;
    static const size_t length = 8;
    static const bool am_unsigned = false;
};

/// @brief Specialization for MySQL BIGINT UNSIGNED type.
template<>
struct MySqlBindingTraits<uint64_t> {
    static const enum_field_types column_type = MYSQL_TYPE_LONGLONG;
    static const size_t length = 8;
    static const bool am_unsigned = true;
};

template<>
struct MySqlBindingTraits<float> {
    static const enum_field_types column_type = MYSQL_TYPE_FLOAT;
    static const size_t length = 4;
    static const bool am_unsigned = false;
};

/// @brief Forward declaration of @c MySqlBinding class.
class MySqlBinding;

/// @brief Shared pointer to the @c Binding class.
typedef boost::shared_ptr<MySqlBinding> MySqlBindingPtr;

/// @brief MySQL binding used in prepared statements.
///
/// Kea uses prepared statements to execute queries in a database.
/// Prepared statements include placeholders for the input parameters.
/// These parameters are passed to the prepared statements via a
/// collection of @c MYSQL_BIND structures. The same structures are
/// used to receive the values from the database as a result of
/// SELECT statements.
///
/// The @c MYSQL_BIND structure contains information about the
/// data type and length. It also contains pointer to the buffer
/// actually holding the data to be passed to the database, a
/// flag indicating if the value is null etc.
///
/// The @c MySqlBinding is a C++ wrapper around this structure which
/// is meant to ease management of the MySQL bindings. The major
/// benefit is that the @c MySqlBinding class owns the buffer,
/// holding the data as well as other variables which are assigned
/// to the @c MYSQL_BIND structure. It also automatically detects
/// the appropriate @c enum_field_types value based on the C++
/// type used in the binding.
class MySqlBinding {
public:

    /// @brief Returns MySQL column type for the binding.
    ///
    /// @return column type, e.g. MYSQL_TYPE_STRING.
    enum_field_types getType() const {
        return (bind_.buffer_type);
    }

    /// @brief Returns reference to the native binding.
    ///
    /// The returned reference is only valid for the lifetime of the
    /// object. Make sure that the object is not destroyed as long
    /// as the binding is required. In particular, do not destroy this
    /// object before database query is complete.
    ///
    /// @return Reference to native MySQL binding.
    MYSQL_BIND& getMySqlBinding() {
        return (bind_);
    }

    /// @brief Returns value held in the binding as string.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @throw InvalidOperation if the value is NULL or the binding
    /// type is not @c MYSQL_TYPE_STRING.
    ///
    /// @return String value.
    std::string getString() const;

    /// @brief Returns value held in the binding as string.
    ///
    /// If the value to be returned is null, a default value is returned.
    ///
    /// @param default_value Default value.
    ///
    /// @throw InvalidOperation if the binding type is not @c MYSQL_TYPE_STRING.
    ///
    /// @return String value.
    std::string getStringOrDefault(const std::string& default_value) const;

    /// @brief Returns value held in the binding as JSON.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @throw InvalidOperation if the binding is not @c MYSQL_TYPE_STRING.
    /// @throw data::JSONError if the string value is not a valid JSON.
    ///
    /// @return JSON structure or NULL if the string is null.
    data::ElementPtr getJSON() const;

    /// @brief Returns value held in the binding as blob.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @throw InvalidOperation if the value is NULL or the binding
    /// type is not @c MYSQL_TYPE_BLOB.
    ///
    /// @return Blob in a vactor.
    std::vector<uint8_t> getBlob() const;

    /// @brief Returns value held in the binding as blob.
    ///
    /// If the value to be returned is null, a default value is returned.
    ///
    /// @param default_value Default value.
    ///
    /// @throw InvalidOperation if the binding type is not @c MYSQL_TYPE_BLOB.
    ///
    /// @return Blob in a vactor.
    std::vector<uint8_t>
    getBlobOrDefault(const std::vector<uint8_t>& default_value) const;

    /// @brief Returns numeric value held in the binding.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @tparam Numeric type corresponding to the binding type, e.g.
    /// @c uint8_t, @c uint16_t etc.
    ///
    /// @throw InvalidOperation if the value is NULL or the binding
    /// type does not match the template parameter.
    ///
    /// @return Numeric value of a specified type.
    template<typename T>
    T getInteger() const {
        // Make sure that the binding type is numeric.
        validateAccess<T>();

        // Convert the buffer to a numeric type and then return a copy.
        const T* value = reinterpret_cast<const T*>(&buffer_[0]);
        return (*value);
    }

    /// @brief Returns numeric value held in the binding.
    ///
    /// If the value to be returned is null, a default value is returned.
    ///
    /// @tparam Numeric type corresponding to the binding type, e.g.
    /// @c uint8_t, @c uint16_t etc.
    /// @param default_value Default value.
    ///
    /// @throw InvalidOperation if the binding type does not match the
    /// template parameter.
    ///
    /// @return Numeric value of a specified type.
    template<typename T>
    T getIntegerOrDefault(T default_value) const {
        if (amNull()) {
            return (default_value);
        }
        return (getInteger<T>());
    }

    /// @brief Returns float value held in the binding.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @throw InvalidOperation if the value is NULL or the binding
    /// type does not match the template parameter.
    ///
    /// @return Float value.
    float getFloat() const;

    /// @brief Returns boolean value held in the binding.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @throw InvalidOperation if the value is NULL or the binding
    /// type is not uint8_t.
    ///
    /// @return Boolean value.
    bool getBool() const {
        return (static_cast<bool>(getInteger<uint8_t>()));
    }

    /// @brief Returns timestamp value held in the binding.
    ///
    /// Call @c MySqlBinding::amNull to verify that the value is not
    /// null prior to calling this method.
    ///
    /// @throw InvalidOperation if the value is NULL or the binding
    /// type is not @c MYSQL_TYPE_TIMESTAMP.
    ///
    /// @return Timestamp converted to POSIX time.
    boost::posix_time::ptime getTimestamp() const;

    /// @brief Returns timestamp value held in the binding.
    ///
    /// If the value to be returned is null, a default value is returned.
    ///
    /// @param default_value Default value.
    ///
    /// @throw InvalidOperation if the binding type is not @c MYSQL_TYPE_TIMESTAMP.
    ///
    /// @return Timestamp converted to POSIX time.
    boost::posix_time::ptime
    getTimestampOrDefault(const boost::posix_time::ptime& default_value) const;

    /// @brief Checks if the bound value is NULL.
    ///
    /// @return true if the value in the binding is NULL, false otherwise.
    bool amNull() const {
        return (null_value_ == MLM_TRUE);
    }

    /// @brief Creates binding of text type for receiving data.
    ///
    /// @param length Length of the buffer into which received data will
    /// be stored.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createString(const unsigned long length);

    /// @brief Creates binding of text type for sending data.
    ///
    /// @param value String value to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createString(const std::string& value);

    /// @brief Conditionally creates binding of text type for sending
    /// data if provided value is unspecified.
    ///
    /// @param value String value to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr condCreateString(const util::Optional<std::string>& value);

    /// @brief Creates binding of blob type for receiving data.
    ///
    /// @param length Length of the buffer into which received data will
    /// be stored.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createBlob(const unsigned long length);

    /// @brief Creates binding of blob type for sending data.
    ///
    /// @tparam Iterator Type of the iterator.
    ///
    /// @param begin Iterator pointing to the beginning of the input
    /// buffer holding the data to be sent to the database.
    /// @param end Iterator pointing to the end of the input buffer
    /// holding the data to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    template<typename Iterator>
    static MySqlBindingPtr createBlob(Iterator begin, Iterator end) {
        MySqlBindingPtr binding(new MySqlBinding(MYSQL_TYPE_BLOB,
                                                 std::distance(begin, end)));
        binding->setBufferValue(begin, end);
        return (binding);
    }

    /// @brief Creates binding of numeric type for receiving data.
    ///
    /// @tparam Numeric type corresponding to the binding type, e.g.
    /// @c uint8_t, @c uint16_t etc.
    ///
    /// @return Pointer to the created binding.
    template<typename T>
    static MySqlBindingPtr createInteger() {
        MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<T>::column_type,
                                                 MySqlBindingTraits<T>::length));
        binding->setValue<T>(0);
        return (binding);
    }

    /// @brief Creates binding of numeric type for sending data.
    ///
    /// @tparam Numeric type corresponding to the binding type, e.g.
    /// @c uint8_t, @c uint16_t etc.
    ///
    /// @param value Numeric value to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    template<typename T>
    static MySqlBindingPtr createInteger(T value) {
        MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<T>::column_type,
                                                 MySqlBindingTraits<T>::length));
        binding->setValue(value);
        return (binding);
    }

    /// @brief Conditionally creates binding of numeric type for sending
    /// data if provided value is specified.
    ///
    /// @tparam T Numeric type corresponding to the binding type, e.g.
    /// @c uint8_t, @c uint16_t etc.
    ///
    /// @param value Numeric value to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    template<typename T>
    static MySqlBindingPtr condCreateInteger(const util::Optional<T>& value) {
        return (value.unspecified() ? createNull() : createInteger<T>(value.get()));
    }

    /// @brief Creates binding having a float type for sending data.
    ///
    /// @param value Float value to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createFloat(const float value);

    /// @Conditionally creates binding of float type for sending data if
    /// provided value is specified.
    ///
    /// @tparam T Floating point type to be converted to float.
    ///
    /// @param value Value to be stored in the database as float.
    ///
    /// @return Pointer to the created binding.
    template<typename T>
    static MySqlBindingPtr condCreateFloat(const util::Optional<T>& value) {
        return (value.unspecified() ? createNull() :
                createInteger<float> (static_cast<float>(value.get())));
    }

    /// @brief Creates binding having a bool type for sending data.
    ///
    /// @param value Boolean value to be sent to the database.
    ///
    /// @return Pointer to the created binding holding an @c uint8_t
    /// value representing the boolean value.
    static MySqlBindingPtr createBool(const bool value);

    /// @brief Conditionally creates binding of @c uint8_t type representing
    /// a boolean value if provided value is specified.
    ///
    /// @param value Boolean value for which the binding should be created.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr condCreateBool(const util::Optional<bool>& value);

    /// @brief Conditionally creates binding of @c uint32_t type representing
    /// an IPv4 address if provided value is specified.
    ///
    /// @param value @c IOAddress encapsulating an IPv4 address.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr
    condCreateIPv4Address(const util::Optional<asiolink::IOAddress>& value);

    /// @brief Creates binding of timestamp type for receiving data.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createTimestamp();

    /// @brief Creates binding of timestamp type for sending data.
    ///
    /// @param timestamp Timestamp value to be sent to the database.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createTimestamp(const boost::posix_time::ptime& timestamp);

    /// @brief Creates binding encapsulating a NULL value.
    ///
    /// This method is used to create a binding encapsulating a NULL
    /// value, which can be used to assign NULL to any type of column.
    ///
    /// @return Pointer to the created binding.
    static MySqlBindingPtr createNull();

    /// @brief Converts time_t value to database time.
    ///
    /// @param input_time A time_t value representing time.
    /// @param output_time Reference to MYSQL_TIME object where converted time
    ///        will be put.
    static void convertToDatabaseTime(const time_t input_time,
                                      MYSQL_TIME& output_time);

    /// @brief Converts POSIX time value to database time.
    ///
    /// @param input_time A POSIX time value representing local time.
    /// @param output_time Reference to MYSQL_TIME object where converted time
    ///        will be put.
    static void convertToDatabaseTime(const boost::posix_time::ptime& input_time,
                                      MYSQL_TIME& output_time);

    /// @brief Converts Lease Time to Database Times
    ///
    /// Within the DHCP servers, times are stored as client last transmit time
    /// and valid lifetime.  In the database, the information is stored as
    /// valid lifetime and "expire" (time of expiry of the lease).  They are
    /// related by the equation:
    ///
    /// - expire = client last transmit time + valid lifetime
    ///
    /// This method converts from the times in the lease object into times
    /// able to be added to the database.
    ///
    /// @param cltt Client last transmit time
    /// @param valid_lifetime Valid lifetime
    /// @param expire Reference to MYSQL_TIME object where the expiry time of
    ///        the DHCP lease will be put.
    ///
    /// @throw isc::BadValue if the sum of the calculated expiration time is
    /// greater than the value of @c LeaseMgr::MAX_DB_TIME.
    static void convertToDatabaseTime(const time_t cltt,
                                      const uint32_t valid_lifetime,
                                      MYSQL_TIME& expire);

    /// @brief Converts Database Time to Lease Times
    ///
    /// Within the database, time is stored as "expire" (time of expiry of the
    /// lease) and valid lifetime.  In the DHCP server, the information is
    /// stored client last transmit time and valid lifetime.  These are related
    /// by the equation:
    ///
    /// - client last transmit time = expire - valid_lifetime
    ///
    /// This method converts from the times in the database into times
    /// able to be inserted into the lease object.
    ///
    /// @param expire Reference to MYSQL_TIME object from where the expiry
    ///        time of the lease is taken.
    /// @param valid_lifetime lifetime of the lease.
    /// @param cltt Reference to location where client last transmit time
    ///        is put.
    static void convertFromDatabaseTime(const MYSQL_TIME& expire,
                                        uint32_t valid_lifetime,
                                        time_t& cltt);

    /// @brief Converts database time to POSIX time.
    ///
    /// @param database_time Reference to MYSQL_TIME object where database
    /// time is stored.
    ///
    /// @return Database time converted to local POSIX time.
    static boost::posix_time::ptime
    convertFromDatabaseTime(const MYSQL_TIME& database_time);

private:

    /// @brief Private constructor.
    ///
    /// This constructor is private because MySQL bindings should only be
    /// created using static factory functions.
    ///
    /// @param buffer_type MySQL buffer type as defined in MySQL C API.
    /// @param length Buffer length.
    MySqlBinding(enum_field_types buffer_type, const size_t length);

    /// @brief Assigns new value to a buffer.
    ///
    /// @tparam Iterator Type of the iterators marking beginning and end
    /// of the range to be assigned to the buffer.
    ///
    /// @param begin Iterator pointing to the beginning of the assigned
    /// range.
    /// @param end Iterator pointing to the end of the assigned range.
    template<typename Iterator>
    void setBufferValue(Iterator begin, Iterator end) {
        length_ = std::distance(begin, end);
        buffer_.assign(begin, end);
        // It appears that the MySQL connectors sometimes require that the
        // buffer is specified (set to a non-zero value), even if the buffer
        // length is 0. We have found that setting the buffer to 0 value would
        // cause the value inserted to the database be NULL. In order to avoid
        // it, we simply make sure that the buffer length is at least 1 byte and
        // provide the pointer to this byte within the binding.
        if (buffer_.empty()) {
            buffer_.resize(1);
        }
        bind_.buffer = &buffer_[0];
        bind_.buffer_length = length_;
    }

    /// @brief Resizes the buffer and assigns new length to the binding.
    ///
    /// @param length New buffer length to be used.
    void setBufferLength(const unsigned long length);

    /// @brief Copies numeric value to a buffer and modifies "unsigned" flag
    /// accoriding to the numeric type used.
    ///
    /// @tparam T Type of the numeric value.
    ///
    /// @param value Value to be copied to the buffer.
    template<typename T>
    void setValue(T value) {
        memcpy(static_cast<void*>(&buffer_[0]), reinterpret_cast<char*>(&value),
               sizeof(value));
        bind_.buffer = &buffer_[0];
        bind_.is_unsigned = (MySqlBindingTraits<T>::am_unsigned ? MLM_TRUE : MLM_FALSE);
    }

    /// @brief Converts timestamp to database time value and copies it to
    /// the buffer.
    ///
    /// @param timestamp Timestamp value as POSIX time.
    void setTimestampValue(const boost::posix_time::ptime& timestamp);

    /// @brief Checks if the data accessor called is matching the type
    /// of the data held in the binding.
    ///
    /// @tparam Data type requested, e.g. @c std::string.
    ///
    /// @throw InvalidOperation if the requested data type is not matching
    /// the type of the binding, e.g. called @c getString but the binding
    /// type is @c MYSQL_TYPE_LONG.
    template<typename T>
    void validateAccess() const {
        // Can't retrieve null value.
        if (amNull()) {
            isc_throw(InvalidOperation, "retrieved value is null");
        }
        // The type of the accessor must match the stored data type.
        if (MySqlBindingTraits<T>::column_type != getType()) {
            isc_throw(InvalidOperation, "mismatched column type");
        }
    }

    /// @brief Data buffer (both input and output).
    std::vector<uint8_t> buffer_;

    /// @brief Buffer length.
    unsigned long length_;

    /// @brief Flag indicating whether the value of the binding is NULL.
    my_bool null_value_;

    /// @brief Native MySQL binding wrapped by this class.
    MYSQL_BIND bind_;
};

/// @brief Collection of bindings.
typedef std::vector<MySqlBindingPtr> MySqlBindingCollection;


} // end of namespace isc::db
} // end of namespace isc

#endif
