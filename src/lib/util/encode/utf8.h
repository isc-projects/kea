// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UTF8_H
#define UTF8_H 1

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace util {
namespace encode {
/// @brief Encode value string into UTF-8.
///
/// @param value A string in latin1 i.e. no encoding.
/// @return A vector object storing the data encoded in UTF-8.
std::vector<uint8_t> encodeUtf8(const std::string& value);

} // namespace encode
} // namespace util
} // namespace isc

#endif // UTF8_H
