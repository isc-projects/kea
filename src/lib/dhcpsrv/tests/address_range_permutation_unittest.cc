// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/address_range_permutation.h>

#include <gtest/gtest.h>

#include <set>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

// This test verifies that the object can be successfully constructed for
// both IPv4 and IPv6 address range.
TEST(AddressRangePermutationTest, constructor) {
    ASSERT_NO_THROW({
        AddressRangePermutation::Range range(IOAddress("192.0.2.10"), IOAddress("192.0.2.100"));
        AddressRangePermutation perm(range);
    });
    ASSERT_NO_THROW({
        AddressRangePermutation::Range range(IOAddress("3000::"), IOAddress("3000::10"));
        AddressRangePermutation perm(range);
    });
}

// This test verifies that a permutation of IPv4 address range can
// be generated.
TEST(AddressRangePermutationTest, ipv4) {
    // Create address range with 91 addresses.
    AddressRangePermutation::Range range(IOAddress("192.0.2.10"), IOAddress("192.0.2.100"));
    AddressRangePermutation perm(range);

    // This set will record unique IP addresses generated.
    std::set<IOAddress> addrs;
    bool done = false;

    // Call the next() function 95 tims. The first 91 calls should return non-zero
    // IP addresses.
    for (auto i = 0; i < 95; ++i) {
        auto next = perm.next(done);
        if (!next.isV4Zero()) {
            // Make sure the returned address is within the range.
            EXPECT_LE(range.start_, next);
            EXPECT_LE(next, range.end_);
        } else {
            // The IPv4 zero address marks the end of the permutation. In this case
            // the done flag should be set.
            EXPECT_TRUE(done);
            EXPECT_TRUE(perm.exhausted());
        }
        // Insert the address returned to the set.
        addrs.insert(next);
    }

    // We should have recorded 92 unique addresses, including the zero address.
    EXPECT_EQ(92, addrs.size());
    EXPECT_TRUE(addrs.begin()->isV4Zero());
}

// This test verifies that a permutation of IPv4 address range can
// be generated.
TEST(AddressRangePermutationTest, ipv6) {
    AddressRangePermutation::Range range(IOAddress("2001:db8:1::1:fea0"),
                                         IOAddress("2001:db8:1::2:abcd"));
    AddressRangePermutation perm(range);

    std::set<IOAddress> addrs;
    bool done = false;
    for (auto i = 0; i < 44335; ++i) {
        auto next = perm.next(done);
        if (!next.isV6Zero()) {
            // The IPv6 zero address marks the end of the permutation. In this case
            // the done flag should be set.
            EXPECT_LE(range.start_, next);
            EXPECT_LE(next, range.end_);
        } else {
            EXPECT_TRUE(done);
            EXPECT_TRUE(perm.exhausted());
        }
        // Insert the address returned to the set.
        addrs.insert(next);
    }
    // We should have recorded 44335 unique addresses, including the zero address.
    EXPECT_EQ(44335, addrs.size());
    EXPECT_TRUE(addrs.begin()->isV6Zero());
}

} // end of anonymous namespace
