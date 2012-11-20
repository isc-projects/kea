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
#include <exceptions/exceptions.h>

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
    static const int len = sizeof(asiolink::IOAddress);
    static const bool integer_type = false;
    static const OptionDataType type = OPT_ANY_ADDRESS_TYPE;
};

/// string type is supported
template<>
struct OptionDataTypeTraits<std::string> {
    static const bool valid = true;
    static const int len = sizeof(std::string);
    static const bool integer_type = false;
    static const OptionDataType type = OPT_STRING_TYPE;
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_DATA_TYPES_H
