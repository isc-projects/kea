// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/flq_allocation_state.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/pool.h>
#include <testutils/multi_threading_utils.h>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

// Test creating a new free lease queue allocation state for an IPv4
// address pool.
TEST(PoolFreeLeaseAllocationState, createV4) {
    auto pool = boost::make_shared<Pool4>(IOAddress("192.0.2.1"), IOAddress("192.0.2.10"));
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    EXPECT_TRUE(state->exhausted());
}

// Test adding and deleting free IPv4 leases.
TEST(PoolFreeLeaseAllocationState, addDeleteFreeLeaseV4) {
    auto pool = boost::make_shared<Pool4>(IOAddress("192.0.2.1"), IOAddress("192.0.2.10"));
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    // A new state lacks free leases until we add them.
    EXPECT_EQ(0, state->getFreeLeaseCount());

    // Add the first free lease. The pool should now have one free lease
    // that is always offered.
    state->addFreeLease(IOAddress("192.0.2.1"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(1, state->getFreeLeaseCount());
    // The same lease is always offered.
    EXPECT_EQ("192.0.2.1", state->offerFreeLease().toText());
    EXPECT_EQ("192.0.2.1", state->offerFreeLease().toText());

    // Add another free lease. We should now have two free leases.
    state->addFreeLease(IOAddress("192.0.2.3"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(2, state->getFreeLeaseCount());
    // The new free lease is appended at the end of the queue. Thus, our
    // first lease should be offered now.
    EXPECT_EQ("192.0.2.1", state->offerFreeLease().toText());
    // Now, the second lease should be offered.
    EXPECT_EQ("192.0.2.3", state->offerFreeLease().toText());

    // Try to delete a non-existing lease. It should not affect the
    // existing leases.
    state->deleteFreeLease(IOAddress("192.0.2.2"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(2, state->getFreeLeaseCount());
    EXPECT_EQ("192.0.2.1", state->offerFreeLease().toText());
    EXPECT_EQ("192.0.2.3", state->offerFreeLease().toText());

    // Delete one of the free leases.
    state->deleteFreeLease(IOAddress("192.0.2.1"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(1, state->getFreeLeaseCount());
    // The sole lease should be now offered.
    EXPECT_EQ("192.0.2.3", state->offerFreeLease().toText());
    EXPECT_EQ("192.0.2.3", state->offerFreeLease().toText());

    // Delete the remaining lease. The pool is now exhausted.
    state->deleteFreeLease(IOAddress("192.0.2.3"));
    EXPECT_TRUE(state->exhausted());
    EXPECT_TRUE(state->offerFreeLease().isV4Zero());
}

// Test that duplicate leases are not added to the queue.
TEST(PoolFreeLeaseAllocationState, addFreeLeaseV4SeveralTimes) {
    auto pool = boost::make_shared<Pool4>(IOAddress("192.0.2.1"), IOAddress("192.0.2.10"));
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    EXPECT_EQ(0, state->getFreeLeaseCount());

    // Add the free lease for the first time.
    state->addFreeLease(IOAddress("192.0.2.1"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ("192.0.2.1", state->offerFreeLease().toText());
    EXPECT_EQ(1, state->getFreeLeaseCount());

    // Add the same lease the second time. The second lease instance should
    // not be inserted.
    state->addFreeLease(IOAddress("192.0.2.1"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ("192.0.2.1", state->offerFreeLease().toText());
    EXPECT_EQ(1, state->getFreeLeaseCount());

    // Delete the sole lease and ensure there are no more leases.
    state->deleteFreeLease(IOAddress("192.0.2.1"));
    EXPECT_TRUE(state->exhausted());
    EXPECT_EQ(0, state->getFreeLeaseCount());
}


// Test creating a new free lease queue allocation state for an IPv6
// address pool.
TEST(PoolFreeLeaseAllocationState, createNA) {
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_NA, IOAddress("2001:db8:1::"),
                                          IOAddress("2001:db8:1::10"));
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    EXPECT_TRUE(state->exhausted());
}

// Test adding and deleting free IPv6 address leases.
TEST(PoolFreeLeaseAllocationState, addDeleteFreeLeaseNA) {
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_NA, IOAddress("2001:db8:1::"),
                                          IOAddress("2001:db8:1::10"));
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    // A new state lacks free leases until we add them.
    EXPECT_EQ(0, state->getFreeLeaseCount());

    // Add the first free lease. The pool should now have one free lease
    // that is always offered.
    state->addFreeLease(IOAddress("2001:db8:1::1"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(1, state->getFreeLeaseCount());
    // The same lease is always offered.
    EXPECT_EQ("2001:db8:1::1", state->offerFreeLease().toText());
    EXPECT_EQ("2001:db8:1::1", state->offerFreeLease().toText());

    // Add another free lease. We should now have two free leases.
    state->addFreeLease(IOAddress("2001:db8:1::3"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(2, state->getFreeLeaseCount());
    // The new free lease is appended at the end of the queue. Thus, our
    // first lease should be offered now.
    EXPECT_EQ("2001:db8:1::1", state->offerFreeLease().toText());
    // Now, the second lease should be offered.
    EXPECT_EQ("2001:db8:1::3", state->offerFreeLease().toText());

    // Try to delete a non-existing lease. It should not affect the
    // existing leases.
    state->deleteFreeLease(IOAddress("2001:db8:1::2"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(2, state->getFreeLeaseCount());
    EXPECT_EQ("2001:db8:1::1", state->offerFreeLease().toText());
    EXPECT_EQ("2001:db8:1::3", state->offerFreeLease().toText());

    // Delete one of the free leases.
    state->deleteFreeLease(IOAddress("2001:db8:1::1"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(1, state->getFreeLeaseCount());
    // The sole lease should be now offered.
    EXPECT_EQ("2001:db8:1::3", state->offerFreeLease().toText());
    EXPECT_EQ("2001:db8:1::3", state->offerFreeLease().toText());

    // Delete the remaining lease. The pool is now exhausted.
    state->deleteFreeLease(IOAddress("2001:db8:1::3"));
    EXPECT_TRUE(state->exhausted());
    EXPECT_TRUE(state->offerFreeLease().isV6Zero());
}

// Test that duplicate leases are not added to the queue.
TEST(PoolFreeLeaseAllocationState, addFreeLeaseNASeveralTimes) {
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_NA, IOAddress("2001:db8:1::"),
                                          IOAddress("2001:db8:1::10"));
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    EXPECT_EQ(0, state->getFreeLeaseCount());

    // Add the free lease for the first time.
    state->addFreeLease(IOAddress("2001:db8:1::5"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ("2001:db8:1::5", state->offerFreeLease().toText());
    EXPECT_EQ(1, state->getFreeLeaseCount());

    // Add the same lease the second time. The second lease instance should
    // not be inserted.
    state->addFreeLease(IOAddress("2001:db8:1::5"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ("2001:db8:1::5", state->offerFreeLease().toText());
    EXPECT_EQ(1, state->getFreeLeaseCount());

    // Delete the sole lease and ensure there are no more leases.
    state->deleteFreeLease(IOAddress("2001:db8:1::5"));
    EXPECT_TRUE(state->exhausted());
}

// Test creating a new free lease queue allocation state for an IPv6
// prefix pool.
TEST(PoolFreeLeaseAllocationState, createPD) {
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD, IOAddress("3000::"), 112, 120);
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    EXPECT_TRUE(state->exhausted());
}

// Test creating a new free lease queue allocation state for a
// delegated prefix pool.
TEST(PoolFreeLeaseAllocationState, addDeleteFreeLeasePD) {
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD, IOAddress("3000::"), 112, 120);
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    // A new state lacks free leases until we add them.
    EXPECT_EQ(0, state->getFreeLeaseCount());

    // Add the first free lease. The pool should now have one free lease
    // that is always offered.
    state->addFreeLease(IOAddress("3000::5600"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(1, state->getFreeLeaseCount());
    // The same lease is always offered.
    EXPECT_EQ("3000::5600", state->offerFreeLease().toText());

    // Add another free lease. We should now have two free leases.
    state->addFreeLease(IOAddress("3000::7800"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(2, state->getFreeLeaseCount());
    // The new free lease is appended at the end of the queue. Thus, our
    // first lease should be offered now.
    EXPECT_EQ("3000::5600", state->offerFreeLease().toText());
    // Now, the second lease should be offered.
    EXPECT_EQ("3000::7800", state->offerFreeLease().toText());

    // Try to delete a non-existing lease. It should not affect the
    // existing leases.
    state->deleteFreeLease(IOAddress("3000::6400"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(2, state->getFreeLeaseCount());
    EXPECT_EQ("3000::5600", state->offerFreeLease().toText());
    EXPECT_EQ("3000::7800", state->offerFreeLease().toText());

    // Delete one of the free leases.
    state->deleteFreeLease(IOAddress("3000::5600"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ(1, state->getFreeLeaseCount());
    // The sole lease should be now offered.
    EXPECT_EQ("3000::7800", state->offerFreeLease().toText());
    EXPECT_EQ("3000::7800", state->offerFreeLease().toText());

    // Delete the remaining lease. The pool is now exhausted.
    state->deleteFreeLease(IOAddress("3000::7800"));
    EXPECT_TRUE(state->exhausted());
    EXPECT_TRUE(state->offerFreeLease().isV6Zero());
}

// Test that duplicate leases are not added to the queue.
TEST(PoolFreeLeaseAllocationState, addFreeLeasPDSeveralTimes) {
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD, IOAddress("3000::"), 112, 120);
    auto state = PoolFreeLeaseQueueAllocationState::create(pool);
    ASSERT_TRUE(state);
    EXPECT_EQ(0, state->getFreeLeaseCount());

    // Add the free lease for the first time.
    state->addFreeLease(IOAddress("3000::5600"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ("3000::5600", state->offerFreeLease().toText());
    EXPECT_EQ(1, state->getFreeLeaseCount());

    // Add the same lease the second time. The second lease instance should
    // not be inserted.
    state->addFreeLease(IOAddress("3000::5600"));
    EXPECT_FALSE(state->exhausted());
    EXPECT_EQ("3000::5600", state->offerFreeLease().toText());
    EXPECT_EQ(1, state->getFreeLeaseCount());

    // Delete the sole lease and ensure there are no more leases.
    state->deleteFreeLease(IOAddress("3000::5600"));
    EXPECT_TRUE(state->exhausted());
}


} // end of anonymous namespace
