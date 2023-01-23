// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/iterative_allocation_state.h>
#include <testutils/multi_threading_utils.h>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

// Checks that last allocated IPv4 address is remembered in the iterative
// allocation state.
TEST(IterativeAllocationStateTest, subnetLastAllocated4) {
    IOAddress addr("192.0.2.17");

    IOAddress last("192.0.2.255");

    auto subnet(boost::make_shared<Subnet4>(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    auto state = SubnetIterativeAllocationState::create(subnet);

    // Check initial conditions (all should be set to the last address in range)
    EXPECT_EQ(last.toText(), state->getLastAllocated().toText());

    // Now set last allocated.
    EXPECT_NO_THROW(state->setLastAllocated(addr));
    EXPECT_EQ(addr.toText(), state->getLastAllocated().toText());
}

// Checks that the last allocated IPv4 address is remembered in the
// iterative allocation state when multi threading is turned on.
TEST(IterativeAllocationStateTest, subnetLastAllocated4MultiThreading) {
    MultiThreadingTest mt(true);
    IOAddress addr("192.0.2.17");

    IOAddress last("192.0.2.255");

    auto subnet(boost::make_shared<Subnet4>(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    auto state = SubnetIterativeAllocationState::create(subnet);

    // Check initial conditions (all should be set to the last address in range)
    EXPECT_EQ(last.toText(), state->getLastAllocated().toText());

    // Now set last allocated.
    EXPECT_NO_THROW(state->setLastAllocated(addr));
    EXPECT_EQ(addr.toText(), state->getLastAllocated().toText());
}

// Checks if last allocated address/prefix is stored/retrieved properly.
TEST(IterativeAllocationStateTest, subnetLastAllocated6) {
    IOAddress na("2001:db8:1::1");
    IOAddress ta("2001:db8:1::abcd");
    IOAddress pd("2001:db8:1::1234:5678");

    IOAddress last("2001:db8:1::ffff:ffff:ffff:ffff");

    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4);
    auto state_na = boost::dynamic_pointer_cast<SubnetIterativeAllocationState>
        (subnet->getAllocationState(Lease::TYPE_NA));
    auto state_ta = boost::dynamic_pointer_cast<SubnetIterativeAllocationState>
        (subnet->getAllocationState(Lease::TYPE_TA));
    auto state_pd = boost::dynamic_pointer_cast<SubnetIterativeAllocationState>
        (subnet->getAllocationState(Lease::TYPE_PD));

    // Check initial conditions (all should be set to the last address in range)
    EXPECT_EQ(last.toText(), state_na->getLastAllocated().toText());
    EXPECT_EQ(last.toText(), state_ta->getLastAllocated().toText());
    EXPECT_EQ(last.toText(), state_pd->getLastAllocated().toText());

    // Now set last allocated for IA
    EXPECT_NO_THROW(state_na->setLastAllocated(na));
    EXPECT_EQ(na.toText(), state_na->getLastAllocated().toText());

    // TA and PD should be unchanged
    EXPECT_EQ(last.toText(), state_ta->getLastAllocated().toText());
    EXPECT_EQ(last.toText(), state_pd->getLastAllocated().toText());

    // Now set TA and PD
    EXPECT_NO_THROW(state_ta->setLastAllocated(ta));
    EXPECT_NO_THROW(state_pd->setLastAllocated(pd));

    EXPECT_EQ(na.toText(), state_na->getLastAllocated().toText());
    EXPECT_EQ(ta.toText(), state_ta->getLastAllocated().toText());
    EXPECT_EQ(pd.toText(), state_pd->getLastAllocated().toText());
}

// Checks if last allocated address/prefix is stored/retrieved properly when
// multi threading is turned on.
TEST(IterativeAllocationStateTest, subnetLastAllocated6MultiThreading) {
    MultiThreadingTest mt(true);
    IOAddress na("2001:db8:1::1");
    IOAddress ta("2001:db8:1::abcd");
    IOAddress pd("2001:db8:1::1234:5678");

    IOAddress last("2001:db8:1::ffff:ffff:ffff:ffff");

    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4);
    auto state_na = boost::dynamic_pointer_cast<SubnetIterativeAllocationState>
        (subnet->getAllocationState(Lease::TYPE_NA));
    auto state_ta = boost::dynamic_pointer_cast<SubnetIterativeAllocationState>
        (subnet->getAllocationState(Lease::TYPE_TA));
    auto state_pd = boost::dynamic_pointer_cast<SubnetIterativeAllocationState>
        (subnet->getAllocationState(Lease::TYPE_PD));

    // Check initial conditions (all should be set to the last address in range)
    EXPECT_EQ(last.toText(), state_na->getLastAllocated().toText());
    EXPECT_EQ(last.toText(), state_ta->getLastAllocated().toText());
    EXPECT_EQ(last.toText(), state_pd->getLastAllocated().toText());

    // Now set last allocated for IA
    EXPECT_NO_THROW(state_na->setLastAllocated(na));
    EXPECT_EQ(na.toText(), state_na->getLastAllocated().toText());

    // TA and PD should be unchanged
    EXPECT_EQ(last.toText(), state_ta->getLastAllocated().toText());
    EXPECT_EQ(last.toText(), state_pd->getLastAllocated().toText());

    // Now set TA and PD
    EXPECT_NO_THROW(state_ta->setLastAllocated(ta));
    EXPECT_NO_THROW(state_pd->setLastAllocated(pd));

    EXPECT_EQ(na.toText(), state_na->getLastAllocated().toText());
    EXPECT_EQ(ta.toText(), state_ta->getLastAllocated().toText());
    EXPECT_EQ(pd.toText(), state_pd->getLastAllocated().toText());
}

// Checks that last allocated IPv4 address is stored in the pool-specific
// allocation state.
TEST(IterativeAllocationStateTest, poolLastAllocated4) {
    // Create a pool.
    IOAddress first("192.0.2.0");
    auto pool = boost::make_shared<Pool4>(first, IOAddress("192.0.2.255"));
    auto state = PoolIterativeAllocationState::create(pool);

    // Initial values are first invalid.
    EXPECT_EQ(first.toText(), state->getLastAllocated().toText());
    EXPECT_FALSE(state->isLastAllocatedValid());

    // Now set last allocated
    IOAddress addr("192.0.2.100");
    EXPECT_NO_THROW(state->setLastAllocated(addr));
    EXPECT_EQ(addr.toText(), state->getLastAllocated().toText());
    EXPECT_TRUE(state->isLastAllocatedValid());

    // Reset makes it invalid and does not touch address
    state->resetLastAllocated();
    EXPECT_EQ(addr.toText(), state->getLastAllocated().toText());
    EXPECT_FALSE(state->isLastAllocatedValid());
}

// Checks that last allocated IPv6 lease is stored in the pool-specific
// allocation state.
TEST(IterativeAllocationStateTest, poolLastAllocated6) {
    // Create a pool.
    IOAddress first("2001:db8::1");
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_NA, first, IOAddress("2001:db8::200"));
    auto state = PoolIterativeAllocationState::create(pool);

    // Initial values are first invalid.
    EXPECT_EQ(first.toText(), state->getLastAllocated().toText());
    EXPECT_FALSE(state->isLastAllocatedValid());

    // Now set last allocated
    IOAddress addr("2001:db8::100");
    EXPECT_NO_THROW(state->setLastAllocated(addr));
    EXPECT_EQ(addr.toText(), state->getLastAllocated().toText());
    EXPECT_TRUE(state->isLastAllocatedValid());

    // Reset makes it invalid and does not touch address
    state->resetLastAllocated();
    EXPECT_EQ(addr.toText(), state->getLastAllocated().toText());
    EXPECT_FALSE(state->isLastAllocatedValid());
}

}  // anonymous namespace
