// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include "wiredata.h"

#include <gtest/gtest.h>

#include <algorithm>            // for std::min

using namespace std;

namespace isc {
namespace util {
namespace unittests {

void
matchWireData(const void* expected_data, size_t expected_len,
              const void* actual_data, size_t actual_len)
{
    const size_t cmplen = std::min(expected_len, actual_len);

    for (size_t i = 0; i < cmplen; ++i) {
        const int ebyte = static_cast<const uint8_t*>(expected_data)[i];
        const int abyte = static_cast<const uint8_t*>(actual_data)[i];
        if (ebyte != abyte) {
            FAIL() << "Wire data mismatch at " << i << "th byte\n"
                   << "  Actual: " << abyte << "\n"
                   << "Expected: " << ebyte << "\n";
            return;
        }
    }
    if (expected_len != actual_len) {
        FAIL() << "Wire data mismatch in length:\n"
               << "  Actual: " << actual_len << "\n"
               << "Expected: " << expected_len << "\n";
    }
}

} // unittests
} // util
} // isc
