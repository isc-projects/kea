// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <pgsql/pgsql_exchange.h>
#include <pgsql/pgsql_connection.h>
#include <exceptions/exceptions.h>

#include <boost/lexical_cast.hpp>

#include <iomanip>
#include <sstream>
#include <vector>

namespace isc {
namespace db {

const int PsqlBindArray::TEXT_FMT = 0;
const int PsqlBindArray::BINARY_FMT = 1;
const char* PsqlBindArray::TRUE_STR = "TRUE";
const char* PsqlBindArray::FALSE_STR = "FALSE";

void PsqlBindArray::add(const char* value) {
    if (!value) {
        isc_throw(BadValue, "PsqlBindArray::add - char* value cannot be NULL");
    }

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

void PsqlBindArray::add(const uint8_t* data, const size_t len) {
    if (!data) {
        isc_throw(BadValue, "PsqlBindArray::add - uint8_t data cannot be NULL");
    }

    values_.push_back(reinterpret_cast<const char*>(&(data[0])));
    lengths_.push_back(len);
    formats_.push_back(BINARY_FMT);
}

void PsqlBindArray::add(const bool& value)  {
    add(value ? TRUE_STR : FALSE_STR);
}

void PsqlBindArray::add(const uint8_t& byte) {
    // We static_cast to an unsigned int, otherwise lexical_cast may to
    // treat byte as a character, which yields "" for unprintable values
    addTempString(boost::lexical_cast<std::string>
                              (static_cast<unsigned int>(byte)));
}

void PsqlBindArray::add(const isc::asiolink::IOAddress& addr) {
    if (addr.isV4()) {
        addTempString(boost::lexical_cast<std::string>
                   (addr.toUint32()));
    } else {
        addTempString(addr.toText());
    }
}

void PsqlBindArray::addNull(const int format) {
    values_.push_back(NULL);
    lengths_.push_back(0);
    formats_.push_back(format);
}

/// @todo Eventually this could replace add(std::string&)? This would mean
/// all bound strings would be internally copies rather than perhaps belonging
/// to the originating object such as Host::hostname_.  One the one hand it
/// would make all strings handled one-way only, on the other hand it would
/// mean duplicating strings where it isn't strictly necessary.
void PsqlBindArray::addTempString(const std::string& str) {
    bound_strs_.push_back(ConstStringPtr(new std::string(str)));
    PsqlBindArray::add((bound_strs_.back())->c_str());
}

std::string PsqlBindArray::toText() const {
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
                for (int x = 0; x < lengths_[i]; ++x) {
                    stream << std::setfill('0') << std::setw(2)
                           << std::setbase(16)
                           << static_cast<unsigned int>(data[x]);
                }
                stream << std::endl;
                stream << std::setbase(10);
            }
        }
    }

    return (stream.str());
}

bool
PsqlBindArray::amNull(size_t index) const {
    if (values_.size() < index + 1) {
        isc_throw(OutOfRange, "The index " << index << " is larger than the "
        " array size " << values_.size());
    }

    // We assume lengths_.size() always equals values_.size(). If not, the
    // at() operator will throw.
    return ( (values_.at(index) == NULL) && (lengths_.at(index) == 0) );
}


std::string
PgSqlExchange::convertToDatabaseTime(const time_t input_time) {
    struct tm tinfo;
    char buffer[20];
    localtime_r(&input_time, &tinfo);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tinfo);
    return (std::string(buffer));
}

std::string
PgSqlExchange::convertToDatabaseTime(const time_t cltt,
                                     const uint32_t valid_lifetime) {
    // Calculate expiry time. Store it in the 64-bit value so as we can
    // detect overflows.
    int64_t expire_time_64 = static_cast<int64_t>(cltt)
                             + static_cast<int64_t>(valid_lifetime);

    // It has been observed that the PostgreSQL doesn't deal well with the
    // timestamp values beyond the DataSource::MAX_DB_TIME seconds since the
    // beginning of the epoch (around year 2038). The value is often
    // stored in the database but it is invalid when read back (overflow?).
    // Hence, the maximum timestamp value is restricted here.
    if (expire_time_64 > DatabaseConnection::MAX_DB_TIME) {
        isc_throw(isc::BadValue, "Time value is too large: " << expire_time_64);
    }

    return (convertToDatabaseTime(static_cast<time_t>(expire_time_64)));
}

time_t
PgSqlExchange::convertFromDatabaseTime(const std::string& db_time_val) {
    // Convert string time value to time_t
    time_t new_time;
    try  {
        new_time = (boost::lexical_cast<time_t>(db_time_val));
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "Database time value is invalid: " << db_time_val);
    }

    return (new_time);
}

const char*
PgSqlExchange::getRawColumnValue(const PgSqlResult& r, const int row,
                                 const size_t col) {
    r.rowColCheck(row,col);
    const char* value = PQgetvalue(r, row, col);
    if (!value) {
        isc_throw(DbOperationError, "getRawColumnValue no data for :"
                    << getColumnLabel(r, col) << " row:" << row);
    }
    return (value);
}

bool
PgSqlExchange::isColumnNull(const PgSqlResult& r, const int row,
                            const size_t col) {
    r.rowColCheck(row,col);
    return (PQgetisnull(r, row, col));
}

void
PgSqlExchange::getColumnValue(const PgSqlResult& r, const int row,
                              const size_t col, std::string& value) {
    value = getRawColumnValue(r, row, col);
}

void
PgSqlExchange::getColumnValue(const PgSqlResult& r, const int row,
                              const size_t col, bool &value) {
    const char* data = getRawColumnValue(r, row, col);
    if (!strlen(data) || *data == 'f') {
        value = false;
    } else if (*data == 't') {
        value = true;
    } else {
        isc_throw(DbOperationError, "Invalid boolean data: " << data
                  << " for: " << getColumnLabel(r, col) << " row:" << row
                  << " : must be 't' or 'f'");
    }
}

void
PgSqlExchange::getColumnValue(const PgSqlResult& r, const int row,
                              const size_t col, uint8_t &value) {
    const char* data = getRawColumnValue(r, row, col);
    try {
        // lexically casting as uint8_t doesn't convert from char
        // so we use uint16_t and implicitly convert.
        value = boost::lexical_cast<uint16_t>(data);
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Invalid uint8_t data: " << data
                  << " for: " << getColumnLabel(r, col) << " row:" << row
                  << " : " << ex.what());
    }
}

isc::asiolink::IOAddress
PgSqlExchange::getIPv6Value(const PgSqlResult& r, const int row,
                            const size_t col) {
    const char* data = getRawColumnValue(r, row, col);
    try {
        return (isc::asiolink::IOAddress(data));
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "Cannot convert data: " << data
                  << " for: " << getColumnLabel(r, col) << " row:" << row
                  << " : " << ex.what());
    }
}

void
PgSqlExchange::convertFromBytea(const PgSqlResult& r, const int row,
                                const size_t col, uint8_t* buffer,
                                const size_t buffer_size,
                                size_t &bytes_converted) {
    // Returns converted bytes in a dynamically allocated buffer, and
    // sets bytes_converted.
    unsigned char* bytes = PQunescapeBytea((const unsigned char*)
                                           (getRawColumnValue(r, row, col)),
                                           &bytes_converted);

    // Unlikely it couldn't allocate it but you never know.
    if (!bytes) {
        isc_throw (DbOperationError, "PQunescapeBytea failed for:"
                   << getColumnLabel(r, col) << " row:" << row);
    }

    // Make sure it's not larger than expected.
    if (bytes_converted > buffer_size) {
        // Free the allocated buffer first!
        PQfreemem(bytes);
        isc_throw (DbOperationError, "Converted data size: "
                   << bytes_converted << " is too large for: "
                   << getColumnLabel(r, col) << " row:" << row);
    }

    // Copy from the allocated buffer to caller's buffer the free up
    // the allocated buffer.
    memcpy(buffer, bytes, bytes_converted);
    PQfreemem(bytes);
}

std::string
PgSqlExchange::getColumnLabel(const PgSqlResult& r, const size_t column) {
    return (r.getColumnLabel(column));
}

std::string
PgSqlExchange::dumpRow(const PgSqlResult& r, int row) {
    r.rowCheck(row);
    std::ostringstream stream;
    int columns = r.getCols();
    for (int col = 0; col < columns; ++col) {
        const char* val = getRawColumnValue(r, row, col);
        std::string name = r.getColumnLabel(col);
        int format = PQfformat(r, col);

        stream << col << "   " << name << " : " ;
        if (format == PsqlBindArray::TEXT_FMT) {
            stream << "\"" << val << "\"" << std::endl;
        } else {
            const char *data = val;
            int length = PQfsize(r, col);
            if (length == 0) {
                stream << "empty" << std::endl;
            } else {
                stream << "0x";
                for (int i = 0; i < length; ++i) {
                    stream << std::setfill('0') << std::setw(2)
                           << std::setbase(16)
                           << static_cast<unsigned int>(data[i]);
                }
                stream << std::endl;
            }
        }
    }

    return (stream.str());
}

}; // end of isc::db namespace
}; // end of isc namespace
