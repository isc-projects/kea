// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <mysql/mysql_binding.h>

using namespace boost::posix_time;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace db {

std::string
MySqlBinding::getString() const {
    // Make sure the binding type is text.
    validateAccess<std::string>();
    if (length_ == 0) {
        return (std::string());
    }
    return (std::string(buffer_.begin(), buffer_.begin() + length_));
}

std::string
MySqlBinding::getStringOrDefault(const std::string& default_value) const {
    if (amNull()) {
        return (default_value);
    }
    return (getString());
}

ElementPtr
MySqlBinding::getJSON() const {
    if (amNull()) {
        return (ElementPtr());
    }
    std::string s = getString();
    return (Element::fromJSON(s));
}

std::vector<uint8_t>
MySqlBinding::getBlob() const {
    // Make sure the binding type is blob.
    validateAccess<std::vector<uint8_t> >();
    if (length_ == 0) {
        return (std::vector<uint8_t>());
    }
    return (std::vector<uint8_t>(buffer_.begin(), buffer_.begin() + length_));
}

std::vector<uint8_t>
MySqlBinding::getBlobOrDefault(const std::vector<uint8_t>& default_value) const {
    if (amNull()) {
        return (default_value);
    }
    return (getBlob());
}

float
MySqlBinding::getFloat() const {
    // It may seem a bit weird that we use getInteger template method
    // for getting a floating point value. However, the getInteger method
    // seems to be generic enough to support it. If we were to redo the
    // API of this class we would probably introduce a getNumericValue
    // method instead of getInteger. However, we already have getInteger
    // used in many places so we should stick to it.
    return (getInteger<float>());
}

ptime
MySqlBinding::getTimestamp() const {
    // Make sure the binding type is timestamp.
    validateAccess<ptime>();
    // Copy the buffer contents into native timestamp structure and
    // then convert it to posix time.
    const MYSQL_TIME* database_time = reinterpret_cast<const MYSQL_TIME*>(&buffer_[0]);
    return (convertFromDatabaseTime(*database_time));
}

ptime
MySqlBinding::getTimestampOrDefault(const ptime& default_value) const {
    if (amNull()) {
        return (default_value);
    }
    return (getTimestamp());
}

MySqlBindingPtr
MySqlBinding::createString(const unsigned long length) {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<std::string>::column_type,
                                             length));
    return (binding);
}

MySqlBindingPtr
MySqlBinding::createString(const std::string& value) {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<std::string>::column_type,
                                             value.size()));
    binding->setBufferValue(value.begin(), value.end());
    return (binding);
}

MySqlBindingPtr
MySqlBinding::condCreateString(const Optional<std::string>& value) {
    return (value.unspecified() ? MySqlBinding::createNull() : createString(value));
}

MySqlBindingPtr
MySqlBinding::createBlob(const unsigned long length) {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<std::vector<uint8_t> >::column_type,
                                   length));
    return (binding);
}

MySqlBindingPtr
MySqlBinding::createFloat(const float value) {
    // It may seem a bit weird that we use createInteger template method
    // for setting a floating point value. However, the setInteger method
    // seems to be generic enough to support it. If we were to redo the
    // API of this class we would probably introduce a createNumericValue
    // method instead of createInteger. However, we already have createInteger
    // used in many places so we should stick to it.
    return (createInteger<float>(value));
}

MySqlBindingPtr
MySqlBinding::createBool(const bool value) {
    return (createInteger<uint8_t>(static_cast<uint8_t>(value)));
}

MySqlBindingPtr
MySqlBinding::condCreateBool(const util::Optional<bool>& value) {
    if (value.unspecified()) {
        return (MySqlBinding::createNull());
    }

    return (createInteger<uint8_t>(static_cast<uint8_t>(value.get())));
}

MySqlBindingPtr
MySqlBinding::condCreateIPv4Address(const Optional<IOAddress>& value) {
    // If the value is unspecified it doesn't matter what the value is.
    if (value.unspecified()) {
        return (MySqlBinding::createNull());
    }

    // Make sure it is an IPv4 address.
    if (!value.get().isV4()) {
        isc_throw(BadValue, "unable to create a MySQL binding: specified value '"
                  << value.get().toText() << "' is not an IPv4 address");
    }

    return (createInteger<uint32_t>(value.get().toUint32()));
}

MySqlBindingPtr
MySqlBinding::createTimestamp(const boost::posix_time::ptime& timestamp) {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<ptime>::column_type,
                                   MySqlBindingTraits<ptime>::length));
    binding->setTimestampValue(timestamp);
    return (binding);
}

MySqlBindingPtr
MySqlBinding::createTimestamp() {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<ptime>::column_type,
                                             MySqlBindingTraits<ptime>::length));
    return (binding);
}

MySqlBindingPtr
MySqlBinding::createNull() {
    MySqlBindingPtr binding(new MySqlBinding(MYSQL_TYPE_NULL, 0));
    return (binding);
}

void
MySqlBinding::convertToDatabaseTime(const time_t input_time,
                                    MYSQL_TIME& output_time) {

    // Convert to broken-out time
    struct tm time_tm;
    (void) localtime_r(&input_time, &time_tm);

    // Place in output expire structure.
    output_time.year = time_tm.tm_year + 1900;
    output_time.month = time_tm.tm_mon + 1;     // Note different base
    output_time.day = time_tm.tm_mday;
    output_time.hour = time_tm.tm_hour;
    output_time.minute = time_tm.tm_min;
    output_time.second = time_tm.tm_sec;
    output_time.second_part = 0;                // No fractional seconds
    output_time.neg = my_bool(0);               // Not negative
}

void
MySqlBinding::convertToDatabaseTime(const boost::posix_time::ptime& input_time,
                                    MYSQL_TIME& output_time) {
    if (input_time.is_not_a_date_time()) {
        isc_throw(BadValue, "Time value is not a valid posix time");
    }

    output_time.year = input_time.date().year();
    output_time.month = input_time.date().month();
    output_time.day = input_time.date().day();
    output_time.hour = input_time.time_of_day().hours();
    output_time.minute = input_time.time_of_day().minutes();
    output_time.second = input_time.time_of_day().seconds();
    /// @todo Use fractional seconds instead of 0 when minimum supported
    /// MySQL version has it.
    output_time.second_part = 0;
/*    output_time.second_part = input_time.time_of_day().fractional_seconds()
        *1000000/time_duration::ticks_per_second(); */
    output_time.neg = my_bool(0);
}

void
MySqlBinding::convertToDatabaseTime(const time_t cltt,
                                    const uint32_t valid_lifetime,
                                    MYSQL_TIME& expire) {

    // Calculate expiry time. Store it in the 64-bit value so as we can detect
    // overflows.
    int64_t expire_time_64 = static_cast<int64_t>(cltt) +
        static_cast<int64_t>(valid_lifetime);

    // Even on 64-bit systems MySQL doesn't seem to accept the timestamps
    // beyond the max value of int32_t.
    if (expire_time_64 > DatabaseConnection::MAX_DB_TIME) {
        isc_throw(BadValue, "Time value is too large: " << expire_time_64);
    }

    const time_t expire_time = static_cast<time_t>(expire_time_64);

    // Convert to broken-out time
    struct tm expire_tm;
    (void) localtime_r(&expire_time, &expire_tm);

    // Place in output expire structure.
    expire.year = expire_tm.tm_year + 1900;
    expire.month = expire_tm.tm_mon + 1;     // Note different base
    expire.day = expire_tm.tm_mday;
    expire.hour = expire_tm.tm_hour;
    expire.minute = expire_tm.tm_min;
    expire.second = expire_tm.tm_sec;
    expire.second_part = 0;                  // No fractional seconds
    expire.neg = my_bool(0);                 // Not negative
}

void
MySqlBinding::convertFromDatabaseTime(const MYSQL_TIME& expire,
                                 uint32_t valid_lifetime,
                                 time_t& cltt) {
    // Copy across fields from MYSQL_TIME structure.
    struct tm expire_tm;
    memset(&expire_tm, 0, sizeof(expire_tm));

    expire_tm.tm_year = expire.year - 1900;
    expire_tm.tm_mon = expire.month - 1;
    expire_tm.tm_mday = expire.day;
    expire_tm.tm_hour = expire.hour;
    expire_tm.tm_min = expire.minute;
    expire_tm.tm_sec = expire.second;
    expire_tm.tm_isdst = -1;    // Let the system work out about DST

    // Convert to local time
    cltt = mktime(&expire_tm) - valid_lifetime;
}

ptime
MySqlBinding::convertFromDatabaseTime(const MYSQL_TIME& database_time) {
    /// @todo Use fractional seconds instead of 0 when minimum supported
    /// MySQL version has it.
    long fractional = 0;
    // long fractional = database_time.second_part * time_duration::ticks_per_second()/1000000;
    ptime pt(boost::gregorian::date(database_time.year,
                                    boost::gregorian::greg_month(database_time.month),
                                    database_time.day),
             time_duration(database_time.hour, database_time.minute,
                           database_time.second, fractional));

    return (pt);
}

MySqlBinding::MySqlBinding(enum_field_types buffer_type,
                           const size_t length)
    // Make sure that the buffer has non-zero length in case we need to
    // reference its first element to assign it to the MySQL binding.
    : buffer_(length > 0 ? length : 1), length_(length),
      null_value_(buffer_type == MYSQL_TYPE_NULL) {
    memset(&bind_, 0, sizeof(MYSQL_BIND));
    bind_.buffer_type = buffer_type;

    if (buffer_type != MYSQL_TYPE_NULL) {
        bind_.buffer = &buffer_[0];
        bind_.buffer_length = length_;
        bind_.length = &length_;
        bind_.is_null = &null_value_;
    }
}

void
MySqlBinding::setBufferLength(const unsigned long length) {
    length_ = length;
    // It appears that the MySQL connectors sometimes require that the
    // buffer is specified (set to a non-zero value), even if the buffer
    // length is 0. We have found that setting the buffer to 0 value would
    // cause the value inserted to the database be NULL. In order to avoid
    // it, we simply make sure that the buffer length is at least 1 byte and
    // provide the pointer to this byte within the binding.
    buffer_.resize(length_ > 0 ? length_ : 1);
    bind_.buffer = &buffer_[0];
    bind_.buffer_length = length_;
}

void
MySqlBinding::setTimestampValue(const ptime& timestamp) {
    MYSQL_TIME database_time;
    convertToDatabaseTime(timestamp, database_time);
    // Copy database time into the buffer.
    memcpy(static_cast<void*>(&buffer_[0]), reinterpret_cast<char*>(&database_time),
           sizeof(MYSQL_TIME));
    bind_.buffer = &buffer_[0];
}

} // end of namespace isc::db
} // end of namespace isc
