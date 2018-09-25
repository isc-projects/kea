// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <mysql/mysql_binding.h>

using namespace isc::data;

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

boost::posix_time::ptime
MySqlBinding::getTimestamp() const {
    // Make sure the binding type is timestamp.
    validateAccess<boost::posix_time::ptime>();
    // Copy the buffer contents into native timestamp structure and
    // then convert it to posix time.
    const MYSQL_TIME* database_time = reinterpret_cast<const MYSQL_TIME*>(&buffer_[0]);
    return (convertFromDatabaseTime(*database_time));
}

boost::posix_time::ptime
MySqlBinding::getTimestampOrDefault(const boost::posix_time::ptime& default_value) const {
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
MySqlBinding::condCreateString(const std::string& value) {
    return (value.empty() ? MySqlBinding::createNull() : createString(value));
}

MySqlBindingPtr
MySqlBinding::createBlob(const unsigned long length) {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<std::vector<uint8_t> >::column_type,
                                   length));
    return (binding);
}

MySqlBindingPtr
MySqlBinding::createTimestamp(const boost::posix_time::ptime& timestamp) {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<boost::posix_time::ptime>::column_type,
                                   MySqlBindingTraits<boost::posix_time::ptime>::length));
    binding->setTimestampValue(timestamp);
    return (binding);
}

MySqlBindingPtr
MySqlBinding::createTimestamp() {
    MySqlBindingPtr binding(new MySqlBinding(MySqlBindingTraits<boost::posix_time::ptime>::column_type,
                                             MySqlBindingTraits<boost::posix_time::ptime>::length));
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

    const time_t expire_time = static_cast<const time_t>(expire_time_64);

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

boost::posix_time::ptime
MySqlBinding::convertFromDatabaseTime(const MYSQL_TIME& database_time) {
    // Copy across fields from MYSQL_TIME structure.
    struct tm converted_tm;
    memset(&converted_tm, 0, sizeof(converted_tm));

    converted_tm.tm_year = database_time.year - 1900;
    converted_tm.tm_mon = database_time.month - 1;
    converted_tm.tm_mday = database_time.day;
    converted_tm.tm_hour = database_time.hour;
    converted_tm.tm_min = database_time.minute;
    converted_tm.tm_sec = database_time.second;
    converted_tm.tm_isdst = -1;    // Let the system work out about DST

    // Convert to local time
    return (boost::posix_time::ptime_from_tm(converted_tm));
}

MySqlBinding::MySqlBinding(enum_field_types buffer_type,
                           const size_t length)
    : buffer_(length), length_(length),
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
    buffer_.resize(length_);
    bind_.buffer = &buffer_[0];
    bind_.buffer_length = length_;
}

void
MySqlBinding::setTimestampValue(const boost::posix_time::ptime& timestamp) {
    // Convert timestamp to tm structure.
    tm td_tm = to_tm(timestamp);
    // Convert tm value to time_t.
    time_t tt = mktime(&td_tm);
    // Convert time_t to database time.
    MYSQL_TIME database_time;
    convertToDatabaseTime(tt, database_time);
    // Copy database time into the buffer.
    memcpy(static_cast<void*>(&buffer_[0]), reinterpret_cast<char*>(&database_time),
           sizeof(MYSQL_TIME));
    bind_.buffer = &buffer_[0];
}

} // end of namespace isc::db
} // end of namespace isc
