// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/unittests/wiredata.h>

#include <gtest/gtest.h>

#include <algorithm>            // for std::min
#include <stdint.h>

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
        // Once we find a mismatch, it's quite likely that there will be many
        // mismatches after this point.  So we stop here by using ASSERT not
        // to be too noisy.
        ASSERT_EQ(ebyte, abyte) << "Wire data mismatch at " << i << "th byte\n"
                                << "  Actual: " << abyte << "\n"
                                << "Expected: " << ebyte << "\n";
    }
    EXPECT_EQ(expected_len, actual_len)
        << "Wire data mismatch in length:\n"
        << "  Actual: " << actual_len << "\n"
        << "Expected: " << expected_len << "\n";
}

} // unittests
} // util
} // isc
