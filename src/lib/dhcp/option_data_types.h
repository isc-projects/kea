// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_DATA_TYPES_H
#define OPTION_DATA_TYPES_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Exception to be thrown when invalid type specified as template parameter.
class InvalidDataType : public Exception {
public:
    InvalidDataType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception to be thrown when cast to the data type was unsuccessful.
class BadDataTypeCast : public Exception {
public:
    BadDataTypeCast(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Data types of DHCP option fields.
enum OptionDataType {
    OPT_EMPTY_TYPE,
    OPT_BINARY_TYPE,
    OPT_BOOLEAN_TYPE,
    OPT_INT8_TYPE,
    OPT_INT16_TYPE,
    OPT_INT32_TYPE,
    OPT_UINT8_TYPE,
    OPT_UINT16_TYPE,
    OPT_UINT32_TYPE,
    OPT_ANY_ADDRESS_TYPE,
    OPT_IPV4_ADDRESS_TYPE,
    OPT_IPV6_ADDRESS_TYPE,
    OPT_STRING_TYPE,
    OPT_FQDN_TYPE,
    OPT_RECORD_TYPE,
    OPT_UNKNOWN_TYPE
};

/// @brief Trait class for data types supported in DHCP option definitions.
///
/// This is useful to check whether the type specified as template parameter
/// is supported by classes like Option6Int, Option6IntArray and some template
/// factory functions in OptionDefinition class.
template<typename T>
struct OptionDataTypeTraits {
    static const bool valid = false;
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_UNKNOWN_TYPE;
};

/// binary type is supported
template<>
struct OptionDataTypeTraits<OptionBuffer> {
    static const bool valid = true;
    static const int len = sizeof(OptionBuffer);
    static const bool integer_type = false;
    static const OptionDataType type = OPT_BINARY_TYPE;
};

/// bool type is supported
template<>
struct OptionDataTypeTraits<bool> {
    static const bool valid = true;
    static const int len = sizeof(bool);
    static const bool integer_type = false;
    static const OptionDataType type = OPT_BOOLEAN_TYPE;
};

/// int8_t type is supported.
template<>
struct OptionDataTypeTraits<int8_t> {
    static const bool valid = true;
    static const int len = 1;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_INT8_TYPE;
};

/// int16_t type is supported.
template<>
struct OptionDataTypeTraits<int16_t> {
    static const bool valid = true;
    static const int len = 2;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_INT16_TYPE;
};

/// int32_t type is supported.
template<>
struct OptionDataTypeTraits<int32_t> {
    static const bool valid = true;
    static const int len = 4;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_INT32_TYPE;
};

/// uint8_t type is supported.
template<>
struct OptionDataTypeTraits<uint8_t> {
    static const bool valid = true;
    static const int len = 1;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_UINT8_TYPE;
};

/// uint16_t type is supported.
template<>
struct OptionDataTypeTraits<uint16_t> {
    static const bool valid = true;
    static const int len = 2;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_UINT16_TYPE;
};

/// uint32_t type is supported.
template<>
struct OptionDataTypeTraits<uint32_t> {
    static const bool valid = true;
    static const int len = 4;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_UINT32_TYPE;
};

/// IPv4 and IPv6 address type is supported
template<>
struct OptionDataTypeTraits<asiolink::IOAddress> {
    static const bool valid = true;
    // The len value is used to determine the size of the data
    // to be written to an option buffer. IOAddress object may
    // either represent an IPv4 or IPv6 addresses which have
    // different lengths. Thus we can't put fixed value here.
    // The length of a data to be written into an option buffer
    // have to be determined in the runtime for a particular
    // IOAddress object. Thus setting len to zero.
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_ANY_ADDRESS_TYPE;
};

/// string type is supported
template<>
struct OptionDataTypeTraits<std::string> {
    static const bool valid = true;
    // The len value is used to determine the size of the data
    // to be written to an option buffer. For strings this
    // size is unknown until we actually deal with the particular
    // string to be written. Thus setting it to zero.
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_STRING_TYPE;
};

/// @brief Utility class to write/read data to/from a buffer.
class OptionDataTypeUtil {
public:
    /// @brief Write IPv4 or IPv6 address into a buffer.
    ///
    /// @param address IPv4 or IPv6 address.
    /// @param [out] buf output buffer.
    static void writeAddress(const asiolink::IOAddress& address,
                                     std::vector<uint8_t>& buf);

    /// @brief Write hex-encoded binary values into a buffer.
    ///
    /// @param hex_str string representing a binary value encoded
    /// with hexadecimal digits (without 0x prefix).
    /// @param [out] output buffer.
    static void writeBinary(const std::string& hex_str,
                                    std::vector<uint8_t>& buf);

    /// @brief Write boolean value into a buffer.
    ///
    /// The bool value is encoded in a buffer in such a way that
    /// "1" means "true" and "0" means "false".
    ///
    /// @param boolean value to be written.
    /// @param [out] buf output buffer.
    static void writeBool(const bool value, std::vector<uint8_t>& buf);

    /// @brief Write integer or unsiged integer value into a buffer.
    ///
    /// @param value an integer value to be written into a buffer.
    /// @param [out] buf output buffer.
    /// @tparam data type of the value.
    template<typename T>
    static void writeInt(const T value,
                         std::vector<uint8_t>& buf) {
        if (!OptionDataTypeTraits<T>::is_integer) {
            isc_throw(InvalidDataType, "provided data type is not the supported.");
        }
        switch (OptionDataTypeTraits<T>::len) {
        case 1:
            buf.push_back(static_cast<uint8_t>(value));
            break;
        case 2:
            buf.resize(buf.size() + 2);
            isc::util::writeUint16(static_cast<uint16_t>(value), &buf[buf.size() - 2]);
            break;
        case 4:
            buf.resize(buf.size() + 4);
            isc::util::writeUint32(static_cast<uint32_t>(value), &buf[buf.size() - 4]);
            break;
        default:
            // The cases above cover whole range of possible data lengths because
            // we check at the beginning of this function that given data type is
            // a supported integer type which can be only 1,2 or 4 bytes long.
            ;
        }
    }

    /// @brief Write utf8-encoded string into a buffer.
    ///
    /// @param value string value to be written into a buffer.
    /// @param [out] buf output buffer.
    static void writeString(const std::string& value,
                            std::vector<uint8_t>& buf);

};


} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_DATA_TYPES_H
