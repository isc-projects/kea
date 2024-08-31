// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/random_allocation_state.h>
#include <testutils/multi_threading_utils.h>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>
#include <set>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

// Test creating the random allocation state for an IPv4 pool.
TEST(PoolRandomAllocationStateTest, ipv4Pool) {
    // Create the pool and state.
    IOAddress first("192.0.2.1");
    IOAddress last("192.0.2.255");
    auto pool = boost::make_shared<Pool4>(first, last);
    auto state = PoolRandomAllocationState::create(pool);
    ASSERT_TRUE(state);

    // Make sure that the permutation has been initialized.
    auto permutation = state->getPermutation();
    ASSERT_TRUE(permutation);

    // Keep the record of the addresses returned by the permutation
    // to ensure it returns unique addresses.
    std::set<IOAddress> addresses;
    for (auto i = 0; i < 10; ++i) {
        auto done = true;
        auto next = permutation->next(done);
        // Returned address must belong to the pool.
        EXPECT_TRUE(pool->inRange(next));
        EXPECT_FALSE(done);
        addresses.insert(next);
    }
    // Make sure that unique addresses were returned.
    EXPECT_EQ(10, addresses.size());
}

// Test creating the random allocation state for an IPv6 pool.
TEST(PoolRandomAllocationStateTest, ipv6AddressPool) {
    // Create the pool and state.
    IOAddress first("2001:db8::1");
    IOAddress last("2001:db8::1:0");
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_NA, first, last);
    auto state = PoolRandomAllocationState::create(pool);
    ASSERT_TRUE(state);

    // Make sure that the permutation has been initialized.
    auto permutation = state->getPermutation();
    ASSERT_TRUE(permutation);

    // Keep the record of the addresses returned by the permutation
    // to ensure it returns unique addresses.
    std::set<IOAddress> addresses;
    for (auto i = 0; i < 10; ++i) {
        auto done = true;
        auto next = permutation->next(done);
        // Returned address must belong to the pool.
        EXPECT_TRUE(pool->inRange(next));
        EXPECT_FALSE(done);
        addresses.insert(next);
    }
    // Make sure that unique addresses were returned.
    EXPECT_EQ(10, addresses.size());
}

// Test creating the random allocation state for an IPv6 prefix pool.
TEST(PoolRandomAllocationStateTest, ipv6PrefixPool) {
    // Create the pool and state.
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD, IOAddress("2001:db8::"), 64, 96);
    auto state = PoolRandomAllocationState::create(pool);
    ASSERT_TRUE(state);

    // Make sure that the permutation has been initialized.
    auto permutation = state->getPermutation();
    ASSERT_TRUE(permutation);

    // Keep the record of the addresses returned by the permutation
    // to ensure it returns unique prefixes.
    std::set<IOAddress> prefixes;
    for (auto i = 0; i < 10; ++i) {
        auto done = true;
        auto next = permutation->next(done);
        // Returned prefix must belong to the pool.
        EXPECT_TRUE(pool->inRange(next));
        EXPECT_FALSE(done);
        prefixes.insert(next);
    }
    // Make sure that unique prefixes were returned.
    EXPECT_EQ(10, prefixes.size());
}

} // end of anonymous namespace
