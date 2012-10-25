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

#ifndef OPTION_DATA_TYPES_H_
#define OPTION_DATA_TYPES_H_

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

/// @brief Trait class for integer data types supported in DHCP option definitions.
///
/// This is useful to check whether the type specified as template parameter
/// is supported by classes like Option6Int, Option6IntArray and some template
/// factory functions in OptionDefinition class.
template<typename T>
struct OptionDataTypes {
    static const bool valid = false;
    static const int len = 0;
};

/// int8_t type is supported.
template<>
struct OptionDataTypes<int8_t> {
    static const bool valid = true;
    static const int len = 1;
};

/// int16_t type is supported.
template<>
struct OptionDataTypes<int16_t> {
    static const bool valid = true;
    static const int len = 2;
};

/// int32_t type is supported.
template<>
struct OptionDataTypes<int32_t> {
    static const bool valid = true;
    static const int len = 4;
};

/// uint8_t type is supported.
template<>
struct OptionDataTypes<uint8_t> {
    static const bool valid = true;
    static const int len = 1;
};

/// uint16_t type is supported.
template<>
struct OptionDataTypes<uint16_t> {
    static const bool valid = true;
    static const int len = 2;
};

/// uint32_t type is supported.
template<>
struct OptionDataTypes<uint32_t> {
    static const bool valid = true;
    static const int len = 4;
};


} // isc::dhcp namespace
} // isc namespace

#endif /* OPTION_DATA_TYPES_H_ */
