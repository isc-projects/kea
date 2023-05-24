// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/ip_range_permutation.h>

#include <gtest/gtest.h>

#include <set>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

// This test verifies that the object can be successfully constructed for
// both IPv4 and IPv6 address range.
TEST(IPRangePermutationTest, constructor) {
    ASSERT_NO_THROW({
        AddressRange range(IOAddress("192.0.2.10"), IOAddress("192.0.2.100"));
        IPRangePermutation perm(range);
    });
    ASSERT_NO_THROW({
        AddressRange range(IOAddress("3000::"), IOAddress("3000::10"));
        IPRangePermutation perm(range);
    });
}

// This test verifies that a permutation of IPv4 address range can
// be generated and each time a different permutation is generated.
TEST(IPRangePermutationTest, ipv4) {
    // Create address range with 91 addresses.
    AddressRange range(IOAddress("192.0.2.10"), IOAddress("192.0.2.100"));

    std::vector<std::vector<IOAddress>> iterations;
    for (auto i = 0; i < 2; ++i) {
        IPRangePermutation perm(range);
        // This set will record unique IP addresses generated.
        std::set<IOAddress> addrs;
        // This vector will record the addresses assignment order.
        std::vector<IOAddress> ordered_addrs;
        bool done = false;
        // Call the next() function 95 times. The first 91 calls should return non-zero
        // IP addresses.
        for (auto i = 0; i < 95; ++i) {
            auto next = perm.next(done);
            if (!next.isV4Zero()) {
                // Make sure the returned address is within the range.
                EXPECT_LE(range.start_, next);
                EXPECT_LE(next, range.end_);
            }
            // If we went over all addresses in the range, the flags indicating that
            // the permutation is exhausted should be set to true.
            if (i >= 90) {
                EXPECT_TRUE(done);
                EXPECT_TRUE(perm.exhausted());
            } else {
                // We're not done yet, so these flag should still be false.
                EXPECT_FALSE(done);
                EXPECT_FALSE(perm.exhausted());
            }
            // Insert the address returned to the set and vector.
            addrs.insert(next);
            ordered_addrs.push_back(next);
        }

        // We should have recorded 92 unique addresses, including the zero address.
        EXPECT_EQ(92, addrs.size());
        EXPECT_TRUE(addrs.begin()->isV4Zero());

        iterations.push_back(ordered_addrs);
    }

    // We want to make sure that each new permutation instance produces a different
    // sequence of addresses. It checks whether or not the random device has been
    // initialized properly. If the random device uses the same seed for each
    // new permutation, the output sequence is always the same. The test below
    // checks that the sequences are different by comparing the respective addresses
    // for two different permutations. It is ok if some of them are equal because it
    // is statistically probable. The threshold of 20% should guard against some
    // of them being equal without a risk of sporadic test failures.
    int overlaps = 0;
    for (auto i = 0; i < iterations[0].size(); ++i) {
        if (iterations[0][i] == iterations[1][i]) {
            ++overlaps;
        }
    }

    EXPECT_LE(overlaps, iterations[0].size()/5)
        << "The number of overlapping random address between the test two iterations"
        << " is greater than 20% of all allocated addresses in each iteration."
        << " It means that the permutation mechanism does not sufficiently randomize"
        << " addresses. Perhaps the randomization device is not properly initialized?";
}

// This test verifies that a permutation of IPv6 address range can
// be generated and each time a different permutation is generated.
TEST(IPRangePermutationTest, ipv6) {
    AddressRange range(IOAddress("2001:db8:1::1:fea0"),
                       IOAddress("2001:db8:1::2:abcd"));

    std::vector<std::vector<IOAddress>> iterations;
    for (auto i = 0; i < 2; ++i) {
        IPRangePermutation perm(range);
        std::set<IOAddress> addrs;
        std::vector<IOAddress> ordered_addrs;
        bool done = false;
        for (auto i = 0; i < 44335; ++i) {
            auto next = perm.next(done);
            if (!next.isV6Zero()) {
                // Make sure that the address is within the range.
                EXPECT_LE(range.start_, next);
                EXPECT_LE(next, range.end_);
            }
            // If we went over all addresses in the range, the flags indicating that
            // the permutation is exhausted should be set to true.
            if (i >= 44333) {
                EXPECT_TRUE(done);
                EXPECT_TRUE(perm.exhausted());
            } else {
                // We're not done yet, so these flag should still be false.
                EXPECT_FALSE(done);
                EXPECT_FALSE(perm.exhausted());
            }
            // Insert the address returned to the set and vector.
            addrs.insert(next);
            ordered_addrs.push_back(next);
        }
        // We should have recorded 44335 unique addresses, including the zero address.
        EXPECT_EQ(44335, addrs.size());
        EXPECT_TRUE(addrs.begin()->isV6Zero());

        iterations.push_back(ordered_addrs);
    }

    // We want to make sure that each new permutation instance produces a different
    // sequence of addresses. It checks whether or not the random device has been
    // initialized properly. If the random device uses the same seed for each
    // new permutation, the output sequence is always the same. The test below
    // checks that the sequences are different by comparing the respective addresses
    // for two different permutations. It is ok if some of them are equal because it
    // is statistically probable. The threshold of 20% should guard against some
    // of them being equal without a risk of sporadic test failures.
    int overlaps = 0;
    for (auto i = 0; i < iterations[0].size(); ++i) {
        if (iterations[0][i] == iterations[1][i]) {
            ++overlaps;
        }
    }

    EXPECT_LE(overlaps, iterations[0].size()/5)
        << "The number of overlapping random address between the test two iterations"
        << " is greater than 20% of all allocated addresses in each iteration."
        << " It means that the permutation mechanism does not sufficiently randomize"
        << " addresses. Perhaps the randomization device is not properly initialized?";
}

// This test verifies that a permutation of delegated prefixes can be
// generated and each time a different permutation is generated.
TEST(IPRangePermutationTest, pd) {
    PrefixRange range(IOAddress("3000::"), 112, 120);

    std::vector<std::vector<IOAddress>> iterations;
    for (auto i = 0; i < 2; ++i) {
        IPRangePermutation perm(range);
        std::set<IOAddress> addrs;
        std::vector<IOAddress> ordered_addrs;
        bool done = false;
        for (auto i = 0; i < 257; ++i) {
            auto next = perm.next(done);
            if (!next.isV6Zero()) {
                // Make sure the prefix is within the range.
                EXPECT_LE(range.start_, next);
                EXPECT_LE(next, range.end_);
            }
            // If we went over all delegated prefixes in the range, the flags indicating
            // that the permutation is exhausted should be set to true.
            if (i >= 255) {
                EXPECT_TRUE(done);
                EXPECT_TRUE(perm.exhausted());
            } else {
                // We're not done yet, so these flag should still be false.
                EXPECT_FALSE(done);
                EXPECT_FALSE(perm.exhausted());
            }
            // Insert the prefix returned to the set and vector.
            addrs.insert(next);
            ordered_addrs.push_back(next);
        }
        // We should have recorded 257 unique addresses, including the zero address.
        EXPECT_EQ(257, addrs.size());
        EXPECT_TRUE(addrs.begin()->isV6Zero());

        iterations.push_back(ordered_addrs);
    }

    ASSERT_EQ(2, iterations.size());

    // We want to make sure that each new permutation instance produces a different
    // sequence of prefixes. It checks whether or not the random device has been
    // initialized properly. If the random device uses the same seed for each
    // new permutation, the output sequence is always the same. The test below
    // checks that the sequences are different by comparing the respective prefixes
    // for two different permutations. It is ok if some of them are equal because it
    // is statistically probable. The threshold of 20% should guard against some
    // of them being equal without a risk of sporadic test failures.
    int overlaps = 0;
    for (auto i = 0; i < iterations[0].size(); ++i) {
        if (iterations[0][i] == iterations[1][i]) {
            ++overlaps;
        }
    }

    EXPECT_LE(overlaps, iterations[0].size()/5)
        << "The number of overlapping random prefixes between the test two iterations"
        << " is greater than 20% of all allocated addresses in each iteration."
        << " It means that the permutation mechanism does not sufficiently randomize"
        << " prefixes. Perhaps the randomization device is not properly initialized?";
}

// This test verifies that a permutation of delegated prefixes is
// generated from the prefix range specified using first and last
// address.
TEST(IPRangePermutationTest, pdStartEnd) {
    PrefixRange range(IOAddress("3000::"), IOAddress("3000::ffff"), 120);
    IPRangePermutation perm(range);

    std::set<IOAddress> addrs;
    bool done = false;
    for (auto i = 0; i < 257; ++i) {
        auto next = perm.next(done);
        if (!next.isV6Zero()) {
            // Make sure the prefix is within the range.
            EXPECT_LE(range.start_, next);
            EXPECT_LE(next, range.end_);
        }
        // If we went over all delegated prefixes in the range, the flags indicating
        // that the permutation is exhausted should be set to true.
        if (i >= 255) {
            EXPECT_TRUE(done);
            EXPECT_TRUE(perm.exhausted());
        } else {
            // We're not done yet, so these flag should still be false.
            EXPECT_FALSE(done);
            EXPECT_FALSE(perm.exhausted());
        }
        // Insert the prefix returned to the set.
        addrs.insert(next);
    }

    // We should have recorded 257 unique addresses, including the zero address.
    EXPECT_EQ(257, addrs.size());
    EXPECT_TRUE(addrs.begin()->isV6Zero());
}

// This test verifies that it is possible to reset the permutation state.
TEST(IPRangePermutationTest, reset) {
    // Create address range with 11 addresses.
    AddressRange range(IOAddress("192.0.2.10"), IOAddress("192.0.2.20"));
    IPRangePermutation perm(range);

    // This set will record unique IP addresses generated.
    std::set<IOAddress> addrs;
    bool done = false;

    // Call the next() function several times to consume several addresses.
    for (auto i = 0; i < 5; ++i) {
        auto next = perm.next(done);
        EXPECT_FALSE(next.isV4Zero());
        addrs.insert(next);
    }
    EXPECT_EQ(5, addrs.size());

    // Reset the permutation. We should be able to get all addresses again.
    perm.reset();

    for (auto i = 0; i < 11; ++i) {
        auto next = perm.next(done);
        EXPECT_FALSE(next.isV4Zero());
        addrs.insert(next);
    }
    EXPECT_EQ(11, addrs.size());
}

} // end of anonymous namespace
