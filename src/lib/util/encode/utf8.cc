// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/encode/utf8.h>

namespace isc {
namespace util {
namespace encode {

std::vector<uint8_t> encodeUtf8(const std::string& value) {
    std::vector<uint8_t> result;
    if (value.empty()) {
        return (result);
    }
    const uint8_t* start = reinterpret_cast<const uint8_t*>(value.c_str());
    std::vector<uint8_t> binary(start, start + value.size());
    for (uint8_t ch : binary) {
        if (ch < 0x80) {
            result.push_back(ch);
        } else {
            result.push_back(0xc0 | (ch >> 6));
            result.push_back(0x80 | (ch & 0x3f));
        }
    }
    return (result);
}

} // namespace encode
} // namespace util
} // namespace isc
