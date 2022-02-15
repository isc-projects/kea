// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/pkt4.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option_int.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <testutils/gtest_utils.h>
#include <hooks/hooks_manager.h>
#include <hooks/callout_handle.h>
#include <stats/stats_mgr.h>

#if defined HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#endif

#if defined HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#endif

#if defined HAVE_CQL
#include <cql/testutils/cql_schema.h>
#endif

using namespace std;
using namespace isc::hooks;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::stats;
using namespace isc::util;

namespace isc {
namespace dhcp {
namespace test {

// This test checks if the v4 Allocation Engine can be instantiated, parses
// parameters string and allocators are created.
TEST_F(AllocEngine4Test, constructor) {
    boost::scoped_ptr<AllocEngine> x;

    // Hashed and random allocators are not supported yet
    ASSERT_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_HASHED, 5, false)),
                 NotImplemented);
    ASSERT_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_RANDOM, 5, false)),
                 NotImplemented);

    // Create V4 (ipv6=false) Allocation Engine that will try at most
    // 100 attempts to pick up a lease
    ASSERT_NO_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100,
                                            false)));

    // There should be V4 allocator
    ASSERT_TRUE(x->getAllocator(Lease::TYPE_V4));

    // Check that allocators for V6 stuff are not created
    EXPECT_THROW(x->getAllocator(Lease::TYPE_NA), BadValue);
    EXPECT_THROW(x->getAllocator(Lease::TYPE_TA), BadValue);
    EXPECT_THROW(x->getAllocator(Lease::TYPE_PD), BadValue);
}

// This test checks if two simple IPv4 allocations succeed and that the
// statistics is properly updated. Prior to the second allocation it
// resets the pointer to the last allocated address within the address
// pool. This causes the engine to walk over the already allocated
// address and then pick the first available address for the second
// allocation. Because the allocation engine checks the callouts next
// step status after each attempt to allocate an address, this test
// also sets this status to non-default value prior to the second
// allocation attempt, to make sure that this unexpected status will
// not interfere with the allocation.
TEST_F(AllocEngine4Test, simpleAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Assigned addresses should be zero.
    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Assigned addresses should have incremented.
    EXPECT_TRUE(testStatistics("assigned-addresses", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));

    // Second allocation starts here.
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    AllocEngine::ClientContext4 ctx2(subnet_, ClientIdPtr(), hwaddr2, IOAddress("0.0.0.0"),
                                     false, true, "anotherhost.example.com.",
                                     false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Set the next step to non-default value to verify that it doesn't
    // affect the allocation.
    ctx2.callout_handle_ = HooksManager::createCalloutHandle();
    ctx2.callout_handle_->setStatus(CalloutHandle::NEXT_STEP_SKIP);

    // Set the last allocated to the beginning of the pool. The allocation
    // engine should detect that the first address is already allocated and
    // assign the first available one.
    pool_->resetLastAllocated();

    lease = engine->allocateLease4(ctx2);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx2.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that the lease is indeed in LeaseMgr
    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Assigned addresses should have incremented.
    EXPECT_TRUE(testStatistics("assigned-addresses", 2, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));
}

// This test checks that simple allocation uses the default valid lifetime.
TEST_F(AllocEngine4Test, defaultAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check the valid lifetime has the default.
    EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks that simple allocation uses the specified valid lifetime.
TEST_F(AllocEngine4Test, hintAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Specify the valid lifetime we want.
    OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 4));
    ctx.query_->addOption(opt);

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check the valid lifetime has the wanted value.
    EXPECT_EQ(opt->getValue(), lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks that simple allocation uses the min valid lifetime.
TEST_F(AllocEngine4Test, minAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(2, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Specify the valid lifetime we want, as it is lower than the min value
    // we'll get this min value instead.
    OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 1));
    ctx.query_->addOption(opt);

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check the valid lifetime has the wanted value.
    EXPECT_EQ(subnet_->getValid().getMin(), lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks that simple allocation uses the max valid lifetime.
TEST_F(AllocEngine4Test, maxAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Specify the valid lifetime we want, as it is greater than the max value
    // we'll get this max value instead.
    OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 6));
    ctx.query_->addOption(opt);

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check the valid lifetime has the wanted value.
    EXPECT_EQ(subnet_->getValid().getMax(), lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks that simple allocation handles BOOTP queries.
TEST_F(AllocEngine4Test, bootpAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the fake allocation (for DHCPDISCOVER) can succeed
TEST_F(AllocEngine4Test, fakeAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Assigned addresses should be zero.
    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, true,
                                    "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is NOT in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_FALSE(from_mgr);

    // Assigned addresses should still be zero.
    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-addresses", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-addresses"));
}

// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngine4Test, allocWithValidHint4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("192.0.2.105"), true, true,
                                    "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We have allocated the new lease, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // We should get what we asked for
    EXPECT_EQ(lease->addr_.toText(), "192.0.2.105");

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the allocation with a hint that is in range,
// in pool, but is currently used can succeed
TEST_F(AllocEngine4Test, allocWithUsedHint4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL);
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              clientid2, sizeof(clientid2), 1, now, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Another client comes in and request an address that is in pool, but
    // unfortunately it is used already. The same address must not be allocated
    // twice.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("192.0.2.106"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx);

    // New lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Allocated address must be different
    EXPECT_NE(used->addr_, lease->addr_);

    // We should NOT get what we asked for, because it is used already
    EXPECT_NE("192.0.2.106", lease->addr_.toText());

    // Do all checks on the lease
    checkLease4(lease);

    // The lease should not be in the LeaseMgr because it was a failed allocation.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_FALSE(from_mgr);
}

// This test checks if an allocation with a hint that is out of the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine4Test, allocBogusHint4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Client would like to get a 10.1.1.1 lease, which does not belong to any
    // supported lease. Allocation engine should ignore it and carry on
    // with the normal allocation
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("10.1.1.1"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We have allocated a new lease, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // We should NOT get what we asked for, because it is used already
    EXPECT_NE("10.1.1.1", lease->addr_.toText());

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is not in the LeaseMgr as it is a fake allocation.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    EXPECT_FALSE(from_mgr);
}

// This test checks that NULL values are handled properly
TEST_F(AllocEngine4Test, allocateLease4Nulls) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    AllocEngine::ClientContext4 ctx1(Subnet4Ptr(), clientid_, hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx1);

    ASSERT_FALSE(lease);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Allocations without HW address are not allowed
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, HWAddrPtr(),
                                     IOAddress("0.0.0.0"), false, false,
                                     "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx2);
    ASSERT_FALSE(lease);
    ASSERT_FALSE(ctx2.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Allocations without client-id are allowed
    clientid_.reset();
    AllocEngine::ClientContext4 ctx3(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", false);
    ctx3.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx3);

    // Check that we got a lease
    ASSERT_TRUE(lease);
    // New lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx3.old_lease_);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if a returning client can renew an
// an existing lease and assigned-leases increments accordingly
TEST_F(AllocEngine4Test, simpleRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease);
    checkLease4(lease);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // We should have incremented assigned-addresses
    EXPECT_TRUE(testStatistics("assigned-addresses", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease2);
    checkLease4(lease2);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Should NOT have bumped assigned-addresses
    EXPECT_TRUE(testStatistics("assigned-addresses", 1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));
}

// This test checks simple renewal uses the default valid lifetime.
TEST_F(AllocEngine4Test, defaultRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease);
    checkLease4(lease);

    // Check the valid lifetime has the default.
    EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease2);
    checkLease4(lease2);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the default.
    EXPECT_EQ(subnet_->getValid(), lease2->valid_lft_);
}

// This test checks simple renewal uses the specified valid lifetime.
TEST_F(AllocEngine4Test, hintRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Specify the valid lifetime we want.
    OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 4));
    ctx.query_->addOption(opt);

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease);
    checkLease4(lease);

    // Check the valid lifetime has the wanted value.
    EXPECT_EQ(opt->getValue(), lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease2);
    checkLease4(lease2);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the wanted value.
    EXPECT_EQ(opt->getValue(), lease2->valid_lft_);
}

// This test checks simple renewal uses the min valid lifetime.
TEST_F(AllocEngine4Test, minRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(2, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Specify the valid lifetime we want, as it is lower than the min value
    // we'll get this min value instead.
    OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 1));
    ctx.query_->addOption(opt);

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease);
    checkLease4(lease);

    // Check the valid lifetime has the min value.
    EXPECT_EQ(subnet_->getValid().getMin(), lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease2);
    checkLease4(lease2);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the min value.
    EXPECT_EQ(subnet_->getValid().getMin(), lease2->valid_lft_);
}

// This test checks simple renewal uses the max valid lifetime.
TEST_F(AllocEngine4Test, maxRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Specify the valid lifetime we want, as it is greater than the max value
    // we'll get this max value instead.
    OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 6));
    ctx.query_->addOption(opt);

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease);
    checkLease4(lease);

    // Check the valid lifetime has the max value.
    EXPECT_EQ(subnet_->getValid().getMax(), lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease and it's sane
    ASSERT_TRUE(lease2);
    checkLease4(lease2);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the max value.
    EXPECT_EQ(subnet_->getValid().getMax(), lease2->valid_lft_);
}

// This test checks simple renewal handles BOOTP queries.
TEST_F(AllocEngine4Test, bootpRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease2);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease2->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease2->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease2->addr_));
    ASSERT_TRUE(lease2->client_id_);
    EXPECT_TRUE(*lease2->client_id_ == *clientid_);
    ASSERT_TRUE(lease2->hwaddr_);
    EXPECT_TRUE(*lease2->hwaddr_ == *hwaddr_);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the max value.
    EXPECT_EQ(infinity_lft, lease2->valid_lft_);
}

// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine4Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Lease::TYPE_V4));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, cc_, clientid_,
                                                 IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
    }
}

// This test verifies that the allocator picks addresses that belong to the
// pool using classification
TEST_F(AllocEngine4Test, IterativeAllocator_class) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Lease::TYPE_V4));

    // Restrict pool_ to the foo class. Add a second pool with bar class.
    pool_->allowClientClass("foo");
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.200"),
                            IOAddress("192.0.2.209")));
    pool->allowClientClass("bar");
    subnet_->addPool(pool);

    // Clients are in bar
    cc_.insert("bar");

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, cc_, clientid_,
                                                 IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
    }
}

// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space and must start over.
TEST_F(AllocEngine4Test, IterativeAllocator_manyPools4) {
    NakedAllocEngine::IterativeAllocator alloc(Lease::TYPE_V4);

    // Let's start from 2, as there is 2001:db8:1::10 - 2001:db8:1::20 pool already.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;

        min << "192.0.2." << i * 10 + 1;
        max << "192.0.2." << i * 10 + 9;

        Pool4Ptr pool(new Pool4(IOAddress(min.str()),
                                IOAddress(max.str())));
        // cout << "Adding pool: " << min.str() << "-" << max.str() << endl;
        subnet_->addPool(pool);
    }

    int total = 10 + 8 * 9; // first pool (.100 - .109) has 10 addresses in it,
                            // there are 8 extra pools with 9 addresses in each.

    // Let's keep picked addresses here and check their uniqueness.
    std::set<IOAddress> generated_addrs;
    int cnt = 0;
    while (++cnt) {
        IOAddress candidate = alloc.pickAddress(subnet_, cc_, clientid_, IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));

        // One way to easily verify that the iterative allocator really works is
        // to uncomment the following line and observe its output that it
        // covers all defined subnets.
        // cout << candidate.toText() << endl;

        if (generated_addrs.find(candidate) == generated_addrs.end()) {
            // We haven't had this
            generated_addrs.insert(candidate);
        } else {
            // We have seen this address before. That should mean that we
            // iterated over all addresses.
            if (generated_addrs.size() == total) {
                // We have exactly the number of address in all pools
                break;
            }
            ADD_FAILURE() << "Too many or not enough unique addresses generated.";
            break;
        }

        if ( cnt>total ) {
            ADD_FAILURE() << "Too many unique addresses generated.";
            break;
        }
    }
}

// This test checks if really small pools are working
TEST_F(AllocEngine4Test, smallPool4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.17");
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Get rid of the default subnet configuration.
    cfg_mgr.clear();

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got that single lease
    ASSERT_TRUE(lease);

    // We have allocated new lease, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    EXPECT_EQ("192.0.2.17", lease->addr_.toText());

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if all addresses in a pool are currently used, the attempt
// to find out a new lease fails.
TEST_F(AllocEngine4Test, outOfAddresses4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.17");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Get rid of the default test configuration.
    cfg_mgr.clear();

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL);
    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2,
                               sizeof(clientid2), 501, now,
                               subnet_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // There is just a single address in the pool and allocated it to someone
    // else, so the allocation should fail

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease2 = engine->allocateLease4(ctx);
    ASSERT_FALSE(lease2);
    ASSERT_FALSE(ctx.old_lease_);

    EXPECT_EQ(1, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(1, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(1, getStatistics("v4-allocation-fail", 2));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 2));
    EXPECT_EQ(1, getStatistics("v4-allocation-fail-subnet", 2));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 2));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 2));
}

/// @brief This test class is dedicated to testing shared networks
///
/// It uses one common configuration:
/// 1 shared network with 2 subnets:
///   - 192.0.2.0/24 subnet with a small pool of single address: 192.0.2.17
///   - 10.1.2.0/24 subnet with pool with 96 addresses.
class SharedNetworkAlloc4Test : public AllocEngine4Test {
public:

    /// @brief Initializes configuration (2 subnets, 1 shared network)
    SharedNetworkAlloc4Test()
        :engine_(AllocEngine::ALLOC_ITERATIVE, 0, false) {
        // Create two subnets, each with a single address pool. The first subnet
        // has only one address in its address pool to make it easier to simulate
        // address exhaustion.
        subnet1_.reset(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, SubnetID(1)));
        subnet2_.reset(new Subnet4(IOAddress("10.1.2.0"), 24, 1, 2, 3, SubnetID(2)));
        pool1_.reset(new Pool4(IOAddress("192.0.2.17"), IOAddress("192.0.2.17")));
        pool2_.reset(new Pool4(IOAddress("10.1.2.5"), IOAddress("10.1.2.100")));

        subnet1_->addPool(pool1_);
        subnet2_->addPool(pool2_);

        // Both subnets belong to the same network so they can be used
        // interchangeably.
        network_.reset(new SharedNetwork4("test_network"));
        network_->add(subnet1_);
        network_->add(subnet2_);

        std::vector<uint8_t> hwaddr_vec = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
        hwaddr2_.reset(new HWAddr(hwaddr_vec, HTYPE_ETHER));
    }

    /// @brief Inserts a new lease for specified address
    ///
    /// Creates a new lease for specified address and subnet-id and inserts
    /// it into database. This is not particularly fancy method, it is used
    /// just to mark existing addresses as used. It uses hwaddr2_ to allocate
    /// the lease.
    ///
    /// @param addr text representation of the address
    /// @param subnet_id ID of the subnet
    /// @param return pointer to the lease
    Lease4Ptr
    insertLease(std::string addr, SubnetID subnet_id) {
        Lease4Ptr lease(new Lease4(IOAddress(addr), hwaddr2_, ClientIdPtr(),
                                   501, time(NULL), subnet_id));
        lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
        if (!LeaseMgrFactory::instance().addLease(lease)) {
            ADD_FAILURE() << "Attempt to add a lease for IP " << addr
                          << " in subnet " << subnet_id << " failed";
        }

        return (lease);
    }

    /// Convenience pointers to configuration elements. These are initialized
    /// in the constructor and are used throughout the tests.
    AllocEngine engine_;
    Subnet4Ptr subnet1_;
    Subnet4Ptr subnet2_;
    Pool4Ptr pool1_;
    Pool4Ptr pool2_;
    SharedNetwork4Ptr network_;

    HWAddrPtr hwaddr2_; // Note there's hwaddr_ already defined in base class.
};

// This test verifies that the server can offer an address from a
// subnet and the introduction of shared network doesn't break anything here.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetworkSimple) {

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);

    // The allocation engine should have assigned an address from the first
    // subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.17", lease->addr_.toText());

    // Make sure the lease is not in the lease mgr (this is only
    // discover).
    ASSERT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));
}

// This test verifies that the server will pick a second subnet out of two
// shared subnets if there is a hint for the second subnet.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetworkHint) {

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.

    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress("10.1.2.25"),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);

    // The allocation engine should have assigned an address from the second
    // subnet, because that's what the hint requested.
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));
}

// This test verifies that the server can offer an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet is exhausted.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetwork) {
    // Create a lease for a single address in the first address pool. The
    // pool is now exhausted.
    Lease4Ptr lease = insertLease("192.0.2.17", subnet1_->getID());

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease2 = engine_.allocateLease4(ctx);
    // The allocation engine should have assigned an address from the second
    // subnet. We could guess that this is 10.1.2.5, being the first address
    // in the address pool, but to make the test more generic, we merely
    // verify that the address is in the given address pool.
    ASSERT_TRUE(lease2);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease2->addr_));

    // The client should also be offered a lease when it specifies a hint
    // that doesn't match the subnet from which the lease is offered. The
    // engine should check alternative subnets to match the hint to
    // a subnet. The requested lease is available, so it should be offered.
    ctx.subnet_ = subnet1_;
    ctx.requested_address_ = IOAddress("10.1.2.25");
    lease2 = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease2);
    EXPECT_EQ("10.1.2.25", lease2->addr_.toText());

    // The returning client (the one that has a lease) should also be able
    // to renew its lease regardless of a subnet it begins with. So, it has
    // an address assigned from subnet1, but we use subnet2 as a selected
    // subnet.
    AllocEngine::ClientContext4 ctx2(subnet2_, ClientIdPtr(), hwaddr2_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "host.example.com.", true);
    ctx2.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease2 = engine_.allocateLease4(ctx2);
    // The existing lease should be returned.
    ASSERT_TRUE(lease2);
    EXPECT_EQ("192.0.2.17", lease2->addr_.toText());
}

// This test verifies that the server can offer an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet is exhausted.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetworkClassification) {

    // Try to offer address from subnet1. There is one address available
    // so it should be offered.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet1_->inPool(Lease::TYPE_V4, lease->addr_));

    // Apply restrictions on the subnet1. This should be only assigned
    // to clients belonging to cable-modem class.
    subnet1_->allowClientClass("cable-modem");

    // The allocation engine should determine that the subnet1 is not
    // available for the client not belonging to the cable-modem class.
    // Instead, it should offer an address from subnet2 that belongs
    // to the same shared network.
    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));

    // Create reservation for the client in subnet1. Because this subnet is
    // not allowed for the client the client should still be offered a
    // lease from subnet2.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet1_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.17")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();
    AllocEngine::findReservation(ctx);

    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));

    // Assign cable-modem class and try again. This time, we should
    // offer an address from the subnet1.
    ctx.query_->addClass(ClientClass("cable-modem"));

    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.17", lease->addr_.toText());
}

// This test verifies that the server can offer an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet requires another class.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetworkPoolClassification) {

    // Try to offer address from subnet1. There is one address available
    // so it should be offered.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet1_->inPool(Lease::TYPE_V4, lease->addr_));

    // Apply restrictions on the pool1. This should be only assigned
    // to clients belonging to cable-modem class.
    pool1_->allowClientClass("cable-modem");

    // The allocation engine should determine that the pool1 is not
    // available for the client not belonging to the cable-modem class.
    // Instead, it should offer an address from subnet2 that belongs
    // to the same shared network.
    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));

    // Assign cable-modem class and try again. This time, we should
    // offer an address from the pool1.
    ctx.query_->addClass(ClientClass("cable-modem"));

    // Restrict access to pool2 for this client, to make sure that the
    // server doesn't accidentally get an address from this pool.
    pool2_->allowClientClass("telephone");

    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.17", lease->addr_.toText());
}

// Test that reservations within shared network take precedence over the
// existing leases regardless in which subnet belonging to a shared network
// reservations belong.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetworkReservations) {

    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());

    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet2_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("10.2.3.23")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Start allocation from subnet1. The engine should determine that the
    // client has reservations in subnet2 and should rather assign reserved
    // addresses.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());

    // Let's create a lease for the client to make sure the lease is not
    // renewed but a reserved lease is offered.
    Lease4Ptr lease2(new Lease4(IOAddress("192.0.2.17"), hwaddr_, ClientIdPtr(),
                                501, time(NULL), subnet1_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease2));
    ctx.subnet_ = subnet1_;
    AllocEngine::findReservation(ctx);
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());
}

// Test that reservations within shared network take precedence over the
// existing leases regardless in which subnet belonging to a shared network
// reservations belong. Host lookups returning a collection are disabled.
// As it is only an optimization the behavior (so the test) must stay
// unchanged.
TEST_F(SharedNetworkAlloc4Test, discoverSharedNetworkReservationsNoColl) {

    // Disable host lookups returning a collection.
    ASSERT_FALSE(HostMgr::instance().getDisableSingleQuery());
    HostMgr::instance().setDisableSingleQuery(true);

    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet2_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("10.2.3.23")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Start allocation from subnet1. The engine should determine that the
    // client has reservations in subnet2 and should rather assign reserved
    // addresses.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());

    // Let's create a lease for the client to make sure the lease is not
    // renewed but a reserved lease is offered.
    Lease4Ptr lease2(new Lease4(IOAddress("192.0.2.17"), hwaddr_, ClientIdPtr(),
                                501, time(NULL), subnet1_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease2));
    ctx.subnet_ = subnet1_;
    AllocEngine::findReservation(ctx);
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());
}

// This test verifies that the server can offer an address from a shared
// subnet if there's at least 1 address left there, but will not offer
// anything if both subnets are completely full.
TEST_F(SharedNetworkAlloc4Test, runningOut) {

    // Allocate everything in subnet1
    insertLease("192.0.2.17", subnet1_->getID());

    // Allocate everything, except one address in subnet2.
    for (int i = 5; i < 100; i++) {
        stringstream tmp;
        tmp << "10.1.2." << i;
        insertLease(tmp.str(), subnet2_->getID());
    }

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    EXPECT_TRUE(lease);

    // Now allocate the last address. Now both subnets are exhausted.
    insertLease("10.1.2.100", subnet2_->getID());

    // Ok, we're out. We should not get anything now.
    lease = engine_.allocateLease4(ctx);
    ASSERT_FALSE(lease);

    EXPECT_EQ(1, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(1, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(1, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(1, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));
}

// This test verifies that the server can offer an address from a
// subnet and the introduction of shared network doesn't break anything here.
TEST_F(SharedNetworkAlloc4Test, requestSharedNetworkSimple) {

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);

    // The allocation engine should have assigned an address from the first
    // subnet.
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.17", lease->addr_.toText());

    // Make sure the lease is in the lease mgr.
    ASSERT_TRUE(LeaseMgrFactory::instance().getLease4(lease->addr_));
}

// This test verifies that the server can allocate an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet is exhausted.
TEST_F(SharedNetworkAlloc4Test, requestSharedNetwork) {

    // Create a lease for a single address in the first address pool. The
    // pool is now exhausted.
    Lease4Ptr lease = insertLease("192.0.2.17", subnet1_->getID());

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease2 = engine_.allocateLease4(ctx);
    // The allocation engine should have assigned an address from the second
    // subnet. We could guess that this is 10.1.2.5, being the first address
    // in the address pool, but to make the test more generic, we merely
    // verify that the address is in the given address pool.
    ASSERT_TRUE(lease2);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease2->addr_));

    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease2));

    // The client should also be assigned a lease when it specifies a hint
    // that doesn't match the subnet from which the lease is offered. The
    // engine should check alternative subnets to match the hint to
    // a subnet. The requested lease is available, so it should be offered.
    ctx.subnet_ = subnet1_;
    ctx.requested_address_ = IOAddress("10.1.2.25");
    lease2 = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease2);
    EXPECT_EQ("10.1.2.25", lease2->addr_.toText());

    // The returning client (the one that has a lease) should also be able
    // to renew its lease regardless of a subnet it begins with. So, it has
    // an address assigned from subnet1, but we use subnet2 as a selected
    // subnet.
    AllocEngine::ClientContext4 ctx2(subnet2_, ClientIdPtr(), hwaddr2_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "host.example.com.", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease2 = engine_.allocateLease4(ctx2);
    // The existing lease should be returned.
    ASSERT_TRUE(lease2);
    EXPECT_EQ("192.0.2.17", lease2->addr_.toText());
}

// This test verifies that the server can assign an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet is exhausted.
TEST_F(SharedNetworkAlloc4Test, requestSharedNetworkClassification) {
    // Try to offer address from subnet1. There is one address available
    // so it should be offered.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet1_->inPool(Lease::TYPE_V4, lease->addr_));

    // Remove the lease so as we can start over.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Apply restrictions on the subnet1. This should be only assigned
    // to clients belonging to cable-modem class.
    subnet1_->allowClientClass("cable-modem");

    // The allocation engine should determine that the subnet1 is not
    // available for the client not belonging to the cable-modem class.
    // Instead, it should assign an address from subnet2 that belongs
    // to the same shared network.
    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));

    // Remove the lease so as we can start over.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Assign cable-modem class and try again. This time, we should
    // offer an address from the subnet1.
    ctx.query_->addClass(ClientClass("cable-modem"));

    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet1_->inPool(Lease::TYPE_V4, lease->addr_));

    // Let's now remove the client from the cable-modem class and try
    // to renew the address. The engine should determine that the
    // client doesn't have access to the subnet1 pools anymore and
    // assign an address from unrestricted subnet.
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));
}

// This test verifies that the server can assign an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet requires another class.
TEST_F(SharedNetworkAlloc4Test, requestSharedNetworkPoolClassification) {
    // Try to offer address from subnet1. There is one address available
    // so it should be offered.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet1_->inPool(Lease::TYPE_V4, lease->addr_));

    // Remove the lease so as we can start over.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Apply restrictions on the pool1. This should be only assigned
    // to clients belonging to cable-modem class.
    pool1_->allowClientClass("cable-modem");

    // The allocation engine should determine that the pool1 is not
    // available for the client not belonging to the cable-modem class.
    // Instead, it should assign an address from subnet2 that belongs
    // to the same shared network.
    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));

    // Remove the lease so as we can start over.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Assign cable-modem class and try again. This time, we should
    // offer an address from the pool1.
    ctx.query_->addClass(ClientClass("cable-modem"));

    // Restrict access to pool2 for this client, to make sure that the
    // server doesn't accidentally get an address from this pool.
    pool2_->allowClientClass("telephone");

    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet1_->inPool(Lease::TYPE_V4, lease->addr_));

    // Let's now remove the client from the cable-modem class and try
    // to renew the address. The engine should determine that the
    // client doesn't have access to the pool1 anymore and
    // assign an address from another pool.
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    ctx.query_->addClass(ClientClass("telephone"));
    ctx.subnet_ = subnet1_;
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_TRUE(subnet2_->inPool(Lease::TYPE_V4, lease->addr_));
}

// Test that reservations within shared network take precedence over the
// existing leases regardless in which subnet belonging to a shared network
// reservations belong (DHCPREQUEST case).
TEST_F(SharedNetworkAlloc4Test, requestSharedNetworkReservations) {

    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());

    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet2_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("10.2.3.23")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Start allocation from subnet1. The engine should determine that the
    // client has reservations in subnet2 and should rather assign reserved
    // addresses.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());

    // Remove the lease for another test below.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Let's create a lease for the client to make sure the lease is not
    // renewed but a reserved lease is allocated again.
    Lease4Ptr lease2(new Lease4(IOAddress("192.0.2.17"), hwaddr_, ClientIdPtr(),
                                501, time(NULL), subnet1_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease2));
    ctx.subnet_ = subnet1_;
    AllocEngine::findReservation(ctx);
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());
}

// Test that reservations within shared network take precedence over the
// existing leases regardless in which subnet belonging to a shared network
// reservations belong (DHCPREQUEST case). Host lookups returning a collection
// are disabled. As it is only an optimization the behavior (so the test)
// must stay unchanged.
TEST_F(SharedNetworkAlloc4Test, requestSharedNetworkReservationsNoColl) {

    // Disable host lookups returning a collection.
    ASSERT_FALSE(HostMgr::instance().getDisableSingleQuery());
    HostMgr::instance().setDisableSingleQuery(true);

    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet2_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("10.2.3.23")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Start allocation from subnet1. The engine should determine that the
    // client has reservations in subnet2 and should rather assign reserved
    // addresses.
    AllocEngine::ClientContext4
        ctx(subnet1_, ClientIdPtr(), hwaddr_, IOAddress::IPV4_ZERO_ADDRESS(),
            false, false, "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());

    // Remove the lease for another test below.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Let's create a lease for the client to make sure the lease is not
    // renewed but a reserved lease is allocated again.
    Lease4Ptr lease2(new Lease4(IOAddress("192.0.2.17"), hwaddr_, ClientIdPtr(),
                                501, time(NULL), subnet1_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease2));
    ctx.subnet_ = subnet1_;
    AllocEngine::findReservation(ctx);
    lease = engine_.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("10.2.3.23", lease->addr_.toText());
}

// This test checks if an expired lease can be reused in DHCPDISCOVER (fake
// allocation)
TEST_F(AllocEngine4Test, discoverReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.15");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Get rid of the default test configuration.
    cfg_mgr.clear();

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago
    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2, sizeof(clientid2),
                               495, now, subnet_->getID()));
    // Copy the lease, so as it can be compared with the old lease returned
    // by the allocation engine.
    Lease4 original_lease(*lease);

    // Lease was assigned 500 seconds ago, but its valid lifetime is 495, so it
    // is expired already
    ASSERT_TRUE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // CASE 1: Asking for any address
    AllocEngine::ClientContext4 ctx1(subnet_, clientid_, hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", true);
    ctx1.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx1);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // We are reusing expired lease, the old (expired) instance should be
    // returned. The returned instance should be the same as the original
    // lease.
    ASSERT_TRUE(ctx1.old_lease_);
    EXPECT_TRUE(original_lease == *ctx1.old_lease_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease4(lease);

    // CASE 2: Asking specifically for this address
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress(addr), false, false,
                                     "", true);
    ctx2.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx2);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // We are updating expired lease. The copy of the old lease should be
    // returned and it should be equal to the original lease.
    ASSERT_TRUE(ctx2.old_lease_);
    EXPECT_TRUE(*ctx2.old_lease_ == original_lease);
}

// This test checks if an expired lease can be reused in REQUEST (actual allocation)
TEST_F(AllocEngine4Test, requestReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.105");

    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0, subnet_->getID()));

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago

    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2, sizeof(clientid2),
                               495, now, subnet_->getID()));
    // Make a copy of the lease, so as we can compare that with the old lease
    // instance returned by the allocation engine.
    Lease4 original_lease(*lease);

    // Lease was assigned 500 seconds ago, but its valid lifetime is 495, so it
    // is expired already
    ASSERT_TRUE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // A client comes along, asking specifically for this address
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress(addr), false, false,
                                    "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx);

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Check that the lease is indeed updated in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // The allocation engine should return a copy of the old lease. This
    // lease should be equal to the original lease.
    ASSERT_TRUE(ctx.old_lease_);
    EXPECT_TRUE(*ctx.old_lease_ == original_lease);

    // Check that the stats declined stats were modified correctly.  Note, because
    // added the lease directly, assigned-leases never bumped to one, so when we
    // reclaim it gets decremented to -1, then on assignment back to 0.
    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 1));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 1, subnet_->getID()));
}

// This test checks if an expired declined lease can be reused when responding
// to DHCPDISCOVER (fake allocation)
TEST_F(AllocEngine4Test, discoverReuseDeclinedLease4) {

    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                          0, false));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    IOAddress addr("192.0.2.15");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear();
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease4Ptr declined = generateDeclinedLease("192.0.2.15", 100, -10);

    // CASE 1: Ask for any address
    Lease4Ptr assigned;
    testReuseLease4(engine, declined, "0.0.0.0", true, SHOULD_PASS, assigned);

    // Check that we got that single lease
    ASSERT_TRUE(assigned);
    EXPECT_EQ(addr, assigned->addr_);

    // CASE 2: Asking specifically for this address
    testReuseLease4(engine, declined, "192.0.2.15", true, SHOULD_PASS, assigned);

    // Check that we get it again
    ASSERT_TRUE(assigned);
    EXPECT_EQ(addr, assigned->addr_);
}

// This test checks if statistics are not updated when expired declined lease
// is reused when responding to DHCPDISCOVER (fake allocation)
TEST_F(AllocEngine4Test, discoverReuseDeclinedLease4Stats) {

    // Now prepare for DISCOVER processing
    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                          0, false));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    IOAddress addr("192.0.2.15");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear();
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);
    cfg_mgr.commit(); // so we will recalc stats
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease4Ptr declined = generateDeclinedLease("192.0.2.15", 100, -10);

    // Ask for any address. There's only one address in the pool, so it doesn't
    // matter much.
    Lease4Ptr assigned;
    testReuseLease4(engine, declined, "0.0.0.0", true, SHOULD_PASS, assigned);

    // Check that the stats declined stats were not modified
    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-addresses", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-addresses"));
    EXPECT_TRUE(testStatistics("declined-addresses", 0));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0));
    EXPECT_TRUE(testStatistics("declined-addresses", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0, subnet_->getID()));
}

// This test checks if an expired declined lease can be reused when responding
// to REQUEST (actual allocation)
TEST_F(AllocEngine4Test, requestReuseDeclinedLease4) {

    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                          0, false));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    IOAddress addr("192.0.2.15");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear();
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease4Ptr declined = generateDeclinedLease("192.0.2.15", 100, -10);

    // Asking specifically for this address
    Lease4Ptr assigned;
    testReuseLease4(engine, declined, "192.0.2.15", false, SHOULD_PASS, assigned);
    // Check that we got it.
    ASSERT_TRUE(assigned);
    EXPECT_EQ(addr, assigned->addr_);

    // Check that the lease is indeed updated in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(assigned, from_mgr);
}

// This test checks if statistics are not updated when expired declined lease
// is reused when responding to DHCPREQUEST (actual allocation)
TEST_F(AllocEngine4Test, requestReuseDeclinedLease4Stats) {

    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                          0, false));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    IOAddress addr("192.0.2.15");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear();
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);
    cfg_mgr.commit();
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease4Ptr declined = generateDeclinedLease("192.0.2.15", 100, -10);

    // Asking specifically for this address
    Lease4Ptr assigned;
    testReuseLease4(engine, declined, "192.0.2.15", false, SHOULD_PASS, assigned);
    // Check that we got it.
    ASSERT_TRUE(assigned);

    // Check that the stats are correct.  Note that assigned-addresses does
    // not get decremented when a lease is declined, ergo not incremented
    // when it is reused.  Declined address stats will be -1 since
    // lease was created as declined which does not increment the stat.
    EXPECT_TRUE(testStatistics("assigned-addresses", 0, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));
    EXPECT_TRUE(testStatistics("declined-addresses", -1));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 1));
    EXPECT_TRUE(testStatistics("declined-addresses", -1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 1, subnet_->getID()));
}

// This test checks that the Allocation Engine correctly identifies the
// existing client's lease in the lease database, using the client
// identifier and HW address.
TEST_F(AllocEngine4Test, identifyClientLease) {
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, clientid_,
                               100, time(NULL), subnet_->getID()));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress::IPV4_ZERO_ADDRESS(),
                                    false, false, "", true);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    Lease4Ptr identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_EQ("192.0.2.101", identified_lease->addr_.toText());

    ctx.hwaddr_ = hwaddr2_;
    ctx.clientid_ = clientid_;
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_EQ("192.0.2.101", identified_lease->addr_.toText());

    ctx.hwaddr_ = hwaddr_;
    ctx.clientid_ = clientid2_;
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_NE(identified_lease->addr_.toText(), "192.0.2.101");

    ctx.hwaddr_ = hwaddr_;
    ctx.clientid_.reset();
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_EQ("192.0.2.101", identified_lease->addr_.toText());

    ctx.hwaddr_ = hwaddr2_;
    ctx.clientid_.reset();
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_NE(identified_lease->addr_.toText(), "192.0.2.101");

    lease->client_id_.reset();
    ASSERT_NO_THROW(LeaseMgrFactory::instance().updateLease4(lease));

    ctx.hwaddr_ = hwaddr_;
    ctx.clientid_ = clientid_;
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_EQ("192.0.2.101", identified_lease->addr_.toText());

    ctx.hwaddr_ = hwaddr_;
    ctx.clientid_.reset();
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_EQ("192.0.2.101", identified_lease->addr_.toText());

    ctx.hwaddr_ = hwaddr2_;
    ctx.clientid_ = clientid_;
    identified_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(identified_lease);
    EXPECT_NE(identified_lease->addr_.toText(), "192.0.2.101");
}

// This test checks that when the client requests the address which belongs
// to another client, the allocation engine returns NULL (for the
// DHCPREQUEST case) or a lease for the address which belongs to this
// client (DHCPDISCOVER case).
TEST_F(AllocEngine4Test, requestOtherClientLease) {
    // Create the first lease.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    // Create the second lease. Note that we use the same client id here and
    // we expect that the allocation engine will figure out that the hardware
    // address is different.
    Lease4Ptr lease2(new Lease4(IOAddress("192.0.2.102"), hwaddr2_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    // Add leases for both clients to the Lease Manager.
    LeaseMgrFactory::instance().addLease(lease);
    LeaseMgrFactory::instance().addLease(lease2);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // First client requests the lease which belongs to the second client.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("192.0.2.102"),
                                    false, false, "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr new_lease = engine.allocateLease4(ctx);
    // Allocation engine should return NULL.
    ASSERT_FALSE(new_lease);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Now simulate the DHCPDISCOVER case when the provided address is
    // treated as a hint. The engine should return a lease for a
    // different address than requested.
    ctx.fake_allocation_ = true;
    new_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(new_lease);
    EXPECT_EQ("192.0.2.101", new_lease->addr_.toText());
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a reservation.
// - Client sends DHCPREQUEST without requested IP Address, nor ciaddr.
// - Client is allocated a reserved address.
//
// Note that client must normally include a requested IP address or ciaddr
// in its message. But, we still want to provision clients that don't do that.
// The server simply picks reserved address or any other available one if there
// is no reservation.
TEST_F(AllocEngine4Test, reservedAddressNoHint) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Try to allocate a lease without specifying a hint. This is actually
    // incorrect behavior of the client to not send an address it wants to
    // obtain but the server should handle this gracefully.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine.allocateLease4(ctx);

    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // Make sure that the lease has been committed to the lease database.
    // And that the committed lease is equal to the one returned.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);

    // Initially, there was no lease for this client, so the returned old
    // lease should be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks behavior of the allocation engine in the following scenario:
// - Client has no lease in the database.
// - Client has a reservation.
// - Client sends DHCPDISCOVER without requested IP Address.
// - Server returns DHCPOFFER with the reserved address.
TEST_F(AllocEngine4Test,reservedAddressNoHintFakeAllocation) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine.allocateLease4(ctx);

    ASSERT_TRUE(lease);
    // The allocation engine should return a reserved address.
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a reservation.
// - Client sends DHCPREQUEST with a requested IP address
// - Server returns DHCPNAK when requested IP address is different than
//   the reserved address. Note that the allocation engine returns NULL
//   to indicate to the server that it should send DHCPNAK.
// - Server allocates a reserved address to the client when the client requests
// this address using requested IP address option.
TEST_F(AllocEngine4Test, reservedAddressHint) {
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    AllocEngine::ClientContext4 ctx1(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.234"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr lease = engine.allocateLease4(ctx1);

    // The client requested a different address than reserved, so
    // the allocation engine should return NULL lease. When the server
    // receives a NULL lease for the client, it will send a DHCPNAK.
    ASSERT_FALSE(lease);
    ASSERT_FALSE(ctx1.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Now, request a correct address. The client should obtain it.
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.123"), false, false,
                                     "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    lease = engine.allocateLease4(ctx2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // Make sure that the lease has been committed to the lease database.
    // And that the committed lease is equal to the one returned.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);

    ASSERT_FALSE(ctx2.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a reservation.
// - Client sends DHCPDISCOVER with a requested IP address as a hint.
// - Server offers a reserved address, even though it is different than the
// requested address.
TEST_F(AllocEngine4Test, reservedAddressHintFakeAllocation) {
    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Query the allocation engine for the lease to be assigned to the client
    // and specify a hint being a different address than the reserved one.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("192.0.2.234"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr lease = engine.allocateLease4(ctx);

    ASSERT_TRUE(lease);
    // Allocation engine should return reserved address.
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a lease for the address from the dynamic pool in the database.
// - Client has a reservation for a different address than the one for which
// the client has a lease.
// - Client sends DHCPREQUEST, asking for the reserved address (as it has been
// offered to it when it sent DHCPDISCOVER).
// - Server allocates a reserved address and removes the lease for the address
// previously allocated to the client.
TEST_F(AllocEngine4Test, reservedAddressExistingLease) {
    // Create the reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client with a different address than the reserved
    // one.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Request allocation of the reserved address.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("192.0.2.123"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx);

    ASSERT_TRUE(allocated_lease);
    // The engine should have allocated the reserved address.
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // Make sure that the lease has been committed to the lease database.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(allocated_lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(allocated_lease, from_mgr);

    // The previous lease should have been replaced by a new one. The previous
    // lease should be returned by the allocation engine to the caller.
    ASSERT_TRUE(ctx.old_lease_);
    EXPECT_EQ("192.0.2.101", ctx.old_lease_->addr_.toText());
    detailCompareLease(ctx.old_lease_, lease);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client A has a lease in the database.
// - Client B has a reservation for the address in use by client A.
// - Client B sends a DHCPREQUEST requesting the allocation of the reserved
// lease (in use by client A).
// - Server determines that the reserved address is in use by a different client
// and returns DHCPNAK to client B.
TEST_F(AllocEngine4Test, reservedAddressHijacked) {
    // Create host reservation for the client B.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Allocate a lease for the client A for the same address as reserved
    // for the client B.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.123"), hwaddr2_, 0, 0,
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Try to allocate the reserved lease to client B.
    AllocEngine::ClientContext4 ctx1(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.123"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);
    // The lease is allocated to someone else, so the allocation should not
    // succeed.
    ASSERT_FALSE(allocated_lease);
    ASSERT_FALSE(ctx1.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Make sure that the allocation engine didn't modify the lease of the
    // client A.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);

    // Try doing the same thing, but this time do not request any specific
    // address. It should have the same effect.
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    allocated_lease = engine.allocateLease4(ctx2);
    ASSERT_FALSE(allocated_lease);
    ASSERT_FALSE(ctx2.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client A has a lease in the database.
// - Client B has a reservation for the address in use by client A.
// - Client B sends a DHCPDISCOVER.
// - Server determines that the reserved address is in use by a different client
//   so it offers an address from the dynamic pool.
TEST_F(AllocEngine4Test, reservedAddressHijackedFakeAllocation) {
    // Create a reservation for the client B.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client A.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.123"), hwaddr2_, 0, 0,
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Query allocation engine for the lease to be allocated to the client B.
    // The allocation engine is not able to allocate the lease to the client
    // B, because the address is in use by client A.
    AllocEngine::ClientContext4 ctx1(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.123"), false, false,
                                     "", true);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);

    // The allocation engine should return a lease but for a different address
    // than requested because this address is in use.
    ASSERT_TRUE(allocated_lease);
    ASSERT_FALSE(ctx1.old_lease_);
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.123");
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, allocated_lease->addr_));

    // Do the same test. But, this time do not specify any address to be
    // allocated.
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", true);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    allocated_lease = engine.allocateLease4(ctx2);

    ASSERT_TRUE(allocated_lease);
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.123");
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, allocated_lease->addr_));
    ASSERT_FALSE(ctx2.old_lease_);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a reservation.
// - Client has a lease in the database for a different address than reserved.
// - Client sends a DHCPREQUEST and asks for a different address than reserved,
// and different than it has in a database.
// - Server doesn't allocate the reserved address to the client because the
// client asked for the different address.
//
// Note that in this case the client should get the DHCPNAK and should fall back
// to the DHCPDISCOVER.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseInvalidHint) {
    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, ClientIdPtr(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Try to allocate a lease and specify a different address than reserved
    // and different from the one that client is currently using.
    AllocEngine::ClientContext4 ctx1(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.102"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);
    ASSERT_FALSE(allocated_lease);
    ASSERT_FALSE(ctx1.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Repeat the test, but this time ask for the address that the client
    // has allocated.
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.101"), false, false,
                                     "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    allocated_lease = engine.allocateLease4(ctx2);
    // The client has reservation so the server wants to allocate a
    // reserved address and doesn't want to renew the address that the
    // client is currently using. This is equivalent of the case when
    // the client tries to renew the lease but there is a new reservation
    // for this client. The server doesn't allow for the renewal and
    // responds with DHCPNAK to force the client to return to the
    // DHCP server discovery.
    ASSERT_FALSE(allocated_lease);
    ASSERT_FALSE(ctx2.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a lease in the database.
// - Client has a reservation for a different address than the one for which it
// has a lease.
// - Client sends a DHCPDISCOVER and asks for a different address than reserved
//   and different from which it has a lease for.
// - Server ignores the client's hint and offers a reserved address.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseFakeAllocation) {
    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Try to allocate a lease and use a completely different address
    // as a hint.
    AllocEngine::ClientContext4 ctx1(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.102"), false, false,
                                     "", true);
    ctx1.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);

    // Server should offer a lease for a reserved address.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // The lease should not be allocated until the client sends a DHCPREQUEST.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(allocated_lease->addr_));

    // Old lease should contain the currently used lease.
    ASSERT_TRUE(ctx1.old_lease_);
    EXPECT_EQ("192.0.2.101", ctx1.old_lease_->addr_.toText());

    // Repeat the test but this time ask for the address for which the
    // client has a lease.
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.101"), false, false,
                                     "", true);
    ctx2.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    AllocEngine::findReservation(ctx2);
    allocated_lease = engine.allocateLease4(ctx2);

    // The server should offer the lease, but not for the address that
    // the client requested. The server should offer a reserved address.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // Old lease should contain the currently used lease.
    ASSERT_TRUE(ctx2.old_lease_);
    EXPECT_EQ("192.0.2.101", ctx2.old_lease_->addr_.toText());
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a reservation.
// - Client has a lease for a different address than reserved.
// - Client sends a DHCPREQUEST to allocate a lease.
// - The server determines that the client has a reservation for the
// different address than it is currently using and should assign
// a reserved address and remove the previous lease.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseNoHint) {
    // Create a reservation.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Try to allocate a lease with providing no hint.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx);

    // The reserved address should be allocated.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // The previous lease should be removed.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Make sure that the allocated lease is committed in the lease database.
    Lease4Ptr from_mgr =
        LeaseMgrFactory::instance().getLease4(allocated_lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(allocated_lease, from_mgr);

    // Old lease should be returned.
    ASSERT_TRUE(ctx.old_lease_);
    detailCompareLease(lease, ctx.old_lease_);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a reservation.
// - Client has a lease for a different address than reserved.
// - Client sends a DHCPDISCOVER with no hint.
// - Server determines that there is a reservation for the client and that
//   the reserved address should be offered when the client sends a
//   DHCPDISCOVER.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseNoHintFakeAllocation) {
    // Create a reservation.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Query the allocation engine for the lease to be allocated for the
    // client.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx);

    // The server should offer the reserved address.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // The lease should not be committed to the lease database until the
    // client sends a DHCPREQUEST.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(allocated_lease->addr_));

    // The old lease should reflect what is in the database.
    ASSERT_TRUE(ctx.old_lease_);
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client A has a lease for the address.
// - Client B has a reservation for the same address that the Client A is using.
// - Client B requests allocation of the reserved address.
// - Server returns DHCPNAK to the client to indicate that the requested address
// can't be allocated.
// - Client A renews the lease.
// - Server determines that the lease that the Client A is trying to renew
// is for the address reserved for Client B. Therefore, the server returns
// DHCPNAK to force the client to return to the server discovery.
// - The Client A sends DHCPDISCOVER.
// - The server offers an address to the Client A, which is different than
// the address reserved for Client B.
// - The Client A requests allocation of the offered address.
// - The server allocates the new address to Client A.
// - The Client B sends DHCPDISCOVER to the server.
// - The server offers a reserved address to the Client B.
// - The Client B requests the offered address.
// - The server allocates the reserved address to the Client B.
TEST_F(AllocEngine4Test, reservedAddressConflictResolution) {
    // Create a reservation for client B.
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr2_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.101")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for Client A.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Client B sends a DHCPREQUEST to allocate a reserved lease. The
    // allocation engine can't allocate a reserved lease for this client
    // because this specific address is in use by the Client A.
    AllocEngine::ClientContext4 ctx1(subnet_, ClientIdPtr(), hwaddr2_,
                                     IOAddress("192.0.2.101"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr offered_lease = engine.allocateLease4(ctx1);
    ASSERT_FALSE(offered_lease);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Client A tries to renew the lease. The renewal should fail because
    // server detects that Client A doesn't have reservation for this
    // address.
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.101"), false, false,
                                     "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    ASSERT_FALSE(engine.allocateLease4(ctx2));
    ASSERT_FALSE(ctx2.old_lease_);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // Client A returns to DHCPDISCOVER and should be offered a lease.
    // The offered lease address must be different than the one the
    // Client B has reservation for.
    AllocEngine::ClientContext4 ctx3(subnet_, clientid_, hwaddr_,
                                     IOAddress("192.0.2.101"), false, false,
                                     "", true);
    ctx3.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx3);
    offered_lease = engine.allocateLease4(ctx3);
    ASSERT_TRUE(offered_lease);
    EXPECT_NE(offered_lease->addr_.toText(), "192.0.2.101");

    // Client A tries to acquire the lease. It should succeed. At this point
    // the previous lease should be released and become available for the
    // Client B.
    AllocEngine::ClientContext4 ctx4(subnet_, clientid_, hwaddr_,
                                     offered_lease->addr_, false, false,
                                     "", false);
    ctx4.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx4);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx4);

    ASSERT_TRUE(allocated_lease);
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.101");

    // Client B tries to get the lease again. It should be offered
    // a reserved lease.
    AllocEngine::ClientContext4 ctx5(subnet_, ClientIdPtr(), hwaddr2_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", true);
    ctx5.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx5);
    offered_lease = engine.allocateLease4(ctx5);

    ASSERT_TRUE(offered_lease);
    EXPECT_EQ("192.0.2.101", offered_lease->addr_.toText());

    // Client B requests allocation of the lease and it should succeed.
    AllocEngine::ClientContext4 ctx6(subnet_, ClientIdPtr(), hwaddr2_,
                                     offered_lease->addr_, false, false,
                                     "", false);
    ctx6.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    allocated_lease = engine.allocateLease4(ctx6);

    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.101", allocated_lease->addr_.toText());
}

// This test checks that the address is not assigned from the dynamic
// pool if it has been reserved for another client.
TEST_F(AllocEngine4Test, reservedAddressVsDynamicPool) {
    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Different client tries to allocate a lease. Note, that we're using
    // an iterative allocator which would pick the first address from the
    // dynamic pool, i.e. 192.0.2.100. This address is reserved so we expect
    // that a different address will be allocated.
    AllocEngine::ClientContext4 ctx(subnet_, ClientIdPtr(), hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx);

    ASSERT_TRUE(allocated_lease);
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.100");

    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(allocated_lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(allocated_lease, from_mgr);
}

// This test checks that the client requesting an address which is
// reserved for another client will get no lease or a different
// address will be assigned if the client is sending a DHCPDISCOVER.
TEST_F(AllocEngine4Test, reservedAddressHintUsedByOtherClient) {
    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Different client is requesting this address.
    AllocEngine::ClientContext4 ctx1(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("192.0.2.100"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);

    // The client should get no lease (DHCPNAK).
    ASSERT_FALSE(allocated_lease);

    EXPECT_EQ(0, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(0, getStatistics("v4-allocation-fail", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-subnet", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 1));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 1));

    // The same client should get a different lease than requested if
    // if is sending a DHCPDISCOVER (fake allocation is true).
    AllocEngine::ClientContext4 ctx2(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("192.0.2.100"), false, false,
                                     "", true);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    allocated_lease = engine.allocateLease4(ctx2);

    ASSERT_TRUE(allocated_lease);
    // Make sure the lease obtained is for a different address.
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.100");
}

// This test checks that the allocation engine refuses to allocate an
// address when the pool is exhausted, and the only available
// address is reserved for a different client.
TEST_F(AllocEngine4Test, reservedAddressShortPool) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Create short pool with only one address.
    initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.100"));
    // Reserve the address for a different client.
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr2_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Allocation engine should determine that the available address is
    // reserved for someone else and not allocate it.
    AllocEngine::ClientContext4 ctx1(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);

    ASSERT_FALSE(allocated_lease);

    EXPECT_EQ(1, getStatistics("v4-allocation-fail"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network"));
    EXPECT_EQ(1, getStatistics("v4-allocation-fail-subnet"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools"));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes"));

    EXPECT_EQ(1, getStatistics("v4-allocation-fail", 2));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-shared-network", 2));
    EXPECT_EQ(1, getStatistics("v4-allocation-fail-subnet", 2));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-no-pools", 2));
    EXPECT_EQ(0, getStatistics("v4-allocation-fail-classes", 2));

    // Now, let's remove the reservation.
    initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.100"));
    CfgMgr::instance().commit();

    // Address should be successfully allocated.
    AllocEngine::ClientContext4 ctx2(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("0.0.0.0"), false, false,
                                     "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx2);
    allocated_lease = engine.allocateLease4(ctx2);

    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.100", allocated_lease->addr_.toText());
}

// This test checks that the AllocEngine allocates an address from the
// dynamic pool if the client's reservation is made for a hostname but
// not for an address.
TEST_F(AllocEngine4Test, reservedHostname) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Create a reservation for a hostname. Address is set to 0 which
    // indicates that there is no reservation.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress::IPV4_ZERO_ADDRESS(),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Try to allocate a lease.
    AllocEngine::ClientContext4 ctx(subnet_, ClientIdPtr(), hwaddr_,
                                    IOAddress("192.0.2.109"), false, false,
                                    "foo.example.org", true);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(allocated_lease);
    ASSERT_FALSE(allocated_lease->addr_.isV4Zero());
    ASSERT_EQ("192.0.2.109", allocated_lease->addr_.toText());

    ctx.requested_address_ = allocated_lease->addr_;
    ctx.fake_allocation_ = false;
    allocated_lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.109", allocated_lease->addr_.toText());
}

// This test checks that the AllocEngine::findReservation method finds
// and returns host reservation for the DHCPv4 client using the data from
// the client context. If the host reservation can't be found, it sets
// the value of NULL in the host_ field of the client context.
TEST_F(AllocEngine4Test, findReservation) {
    // Create the instance of the allocation engine.
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Context is required to call the AllocEngine::findReservation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    ctx.addHostIdentifier(Host::IDENT_HWADDR, hwaddr_->hwaddr_);
    ctx.addHostIdentifier(Host::IDENT_DUID, clientid_->getDuid());

    // There is no reservation in the database so no host should be returned.
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.currentHost());

    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // This time the reservation should be returned.
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // It shouldn't be returned when reservations-in-subnet is disabled.
    subnet_->setReservationsInSubnet(false);
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.currentHost());

    // Check the reservations-in-subnet and reservations-out-of-pool flags.
    subnet_->setReservationsInSubnet(true);
    subnet_->setReservationsOutOfPool(true);
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // This time use the client identifier to search for the host.
    host.reset(new Host(&clientid_->getClientId()[0],
                        clientid_->getClientId().size(),
                        Host::IDENT_DUID, subnet_->getID(),
                        SUBNET_ID_UNUSED, IOAddress("192.0.2.101")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // Remove the subnet. Subnet id is required to find host reservations, so
    // if it is set to NULL, no reservation should be returned
    ctx.subnet_.reset();
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.currentHost());

    // The same if there is a mismatch of the subnet id between the reservation
    // and the context.
    ctx.subnet_ = subnet_;
    host.reset(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                        Host::IDENT_HWADDR, subnet_->getID() + 1,
                        SUBNET_ID_UNUSED, IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.currentHost());
}

// This test checks if the simple IPv4 allocation can succeed and that
// statistic for allocated addresses is increased appropriately.
TEST_F(AllocEngine4Test, simpleAlloc4Stats) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Let's pretend 100 addresses were allocated already
    string name = StatsMgr::generateName("subnet", subnet_->getID(),
                                         "assigned-addresses");
    StatsMgr::instance().addValue(name, static_cast<int64_t>(100));
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // The statistic should be there and it should be increased by 1 (to 101).
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(101, stat->getInteger().first);
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));
}

// This test checks if the fake allocation (for DHCPDISCOVER) can succeed
// and that it doesn't increase allocated-addresses statistic.
TEST_F(AllocEngine4Test, fakeAlloc4Stat) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, true,
                                    "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Let's pretend 100 addresses were allocated already
    string name = StatsMgr::generateName("subnet", subnet_->getID(),
                                         "assigned-addresses");
    StatsMgr::instance().addValue(name, static_cast<int64_t>(100));
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // The statistic should be there and it should not be increased
    // (should be still equal to 100).
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(100, stat->getInteger().first);
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-addresses", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-addresses"));
}

// This test checks that the allocated-addresses statistic is decreased when
// the client has a lease and a reservation for a different address is
// available.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseStat) {
    // Create the reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client with a different address than the reserved
    // one.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Let's pretend 100 addresses were allocated already
    string name = StatsMgr::generateName("subnet", subnet_->getID(),
                                         "assigned-addresses");
    StatsMgr::instance().addValue(name, static_cast<int64_t>(100));
    int64_t cumulative = getStatistics("cumulative-assigned-addresses",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-addresses");

    // Request allocation of the reserved address.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("192.0.2.123"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx);

    Lease4Ptr allocated_lease = engine.allocateLease4(ctx);

    ASSERT_TRUE(allocated_lease);

    // The statistic should be still at 100. Note that it was decreased
    // (because old lease was removed), but also increased (because the
    // new lease was immediately allocated).
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(100, stat->getInteger().first);
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-addresses", glbl_cumulative));

    // Lets' double check that the actual allocation took place.
    EXPECT_FALSE(ctx.fake_allocation_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a global reservation.
// - Client sends DISCOVER
// - Client is allocated the reserved address.
// - Lease is not added to the lease database
TEST_F(AllocEngine4Test, globalReservationReservedAddressDiscover) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, SUBNET_ID_GLOBAL,
                          SUBNET_ID_UNUSED, IOAddress("192.0.77.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate the reserved address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.77.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a global reservation.
// - Client sends REQUEST
// - Client is allocated the reserved address.
// - Lease is added to the lease database
TEST_F(AllocEngine4Test, globalReservationReservedAddressRequest) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, SUBNET_ID_GLOBAL,
                          SUBNET_ID_UNUSED, IOAddress("192.0.77.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate the reserved address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.77.123", lease->addr_.toText());

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a global reservation.
// - Client sends DISCOVER
// - Client is allocated a dynamic address from matched subnet
// - Lease is not added to the lease database
TEST_F(AllocEngine4Test, globalReservationDynamicDiscover) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, SUBNET_ID_GLOBAL,
                          SUBNET_ID_UNUSED, IOAddress::IPV4_ZERO_ADDRESS(),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate a dynamic address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.100", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a global reservation.
// - Client sends REQUEST
// - Client is allocated a dynamic address from matched subnet
// - Lease is added to the lease database
TEST_F(AllocEngine4Test, globalReservationDynamicRequest) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, SUBNET_ID_GLOBAL,
                          SUBNET_ID_UNUSED, IOAddress::IPV4_ZERO_ADDRESS(),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate a dynamic address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.100", lease->addr_.toText());

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a subnet reservation.
// - Client sends DISCOVER
// - Client is allocated the reserved address.
// - Lease is not added to the lease database
TEST_F(AllocEngine4Test, mixedReservationReservedAddressDiscover) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123"),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate the reserved address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a subnet reservation.
// - Client sends REQUEST
// - Client is allocated the reserved address.
// - Lease is added to the lease database
TEST_F(AllocEngine4Test, mixedReservationReservedAddressRequest) {
    // Create reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123"),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate the reserved address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a global and a subnet reservation.
// - Client sends DISCOVER
// - Client is allocated the reserved address.
// - Lease is not added to the lease database
TEST_F(AllocEngine4Test, bothReservationReservedAddressDiscover) {
    // Create reservations for the client.
    HostPtr ghost(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                           Host::IDENT_HWADDR, SUBNET_ID_GLOBAL,
                           SUBNET_ID_UNUSED, IOAddress("192.0.77.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(ghost);
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123"),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate the reserved address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has a global and a subnet reservation.
// - Client sends REQUEST
// - Client is allocated the reserved address.
// - Lease is added to the lease database
TEST_F(AllocEngine4Test, bothReservationReservedAddressRequest) {
    // Create reservations for the client.
    HostPtr ghost(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                           Host::IDENT_HWADDR, SUBNET_ID_GLOBAL,
                           SUBNET_ID_UNUSED, IOAddress("192.0.77.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(ghost);
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SUBNET_ID_UNUSED, IOAddress("192.0.2.123"),
                          "foo.example.org"));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);

    // Query allocation engine for the lease to be assigned to this
    // client without specifying the address to be assigned.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Look up the host.
    AllocEngine::findReservation(ctx);

    // We should have the correct current host
    EXPECT_TRUE(ctx.currentHost());
    EXPECT_EQ(ctx.currentHost()->getHostname(), host->getHostname());
    EXPECT_EQ(ctx.currentHost()->getIPv4Reservation(), host->getIPv4Reservation());

    // We should allocate the reserved address.
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    ASSERT_FALSE(ctx.old_lease_);
}

// Exercises AllocEnginer4Test::updateExtendedInfo4() through various
// permutations of client packet content.
TEST_F(AllocEngine4Test, updateExtendedInfo4) {

    // Structure that defines a test scenario.
    struct Scenario {
        std::string description_;       // test description
        std::string orig_context_json_; // user context the lease begins with
        std::string rai_data_;          // RAI option the client packet contains
        std::string exp_context_json_;  // expected user context on the lease
        bool exp_ret;                   // expected returned value
    };

    // Test scenarios.
    std::vector<Scenario> scenarios {
    {
        "no context, no rai",
        "",
        "",
        "",
        false
    },
    {
        "some original context, no rai",
        "{\"foo\": 123}",
        "",
        "{\"foo\": 123}",
        false
    },
    {
        "no original context, rai",
        "",
        "0x52050104aabbccdd",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104AABBCCDD\" } }",
        true
    },
    {
        "some original context, rai",
        "{\"foo\": 123}",
        "0x52050104aabbccdd",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104AABBCCDD\" }, \"foo\": 123 }",
        true
    },
    {
        "original rai context, no rai",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104AABBCCDD\" } }",
        "",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104AABBCCDD\" } }",
        false
    },
    {
        "original rai context, different rai",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104AABBCCDD\" } }",
        "0x52050104ddeeffaa",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104DDEEFFAA\" } }",
        true
    }};

    // Create the allocation engine, context and lease.
    NakedAllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress::IPV4_ZERO_ADDRESS(),
                                    false, false, "", true);

    // All scenarios require storage to be enabled.
    ctx.subnet_->setStoreExtendedInfo(true);

    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine.allocateLease4(ctx);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.100", lease->addr_.toText());

    // Verify that the lease begins with no user context.
    ConstElementPtr user_context = lease->getContext();
    ASSERT_FALSE(user_context);

    // Iterate over the test scenarios.
    ElementPtr orig_context;
    ElementPtr exp_context;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Create the original user context from JSON.
        if (scenario.orig_context_json_.empty()) {
            orig_context.reset();
        } else {
            ASSERT_NO_THROW(orig_context = Element::fromJSON(scenario.orig_context_json_))
                            << "invalid orig_context_json_, test is broken";
        }

        // Create the expected user context from JSON.
        if (scenario.exp_context_json_.empty()) {
            exp_context.reset();
        } else {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(scenario.exp_context_json_))
                            << "invalid exp_context_json_, test is broken";
        }

        // Initialize lease's user context.
        lease->setContext(orig_context);
        if (!orig_context) {
            ASSERT_FALSE(lease->getContext());
        } else {
            ASSERT_TRUE(lease->getContext());
            ASSERT_TRUE(orig_context->equals(*(lease->getContext())));
        }

        // Create the client packet and the add RAI option (if one).
        ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
        if (!scenario.rai_data_.empty()) {
            std::vector<uint8_t> opt_data;
            ASSERT_NO_THROW(util::str::decodeFormattedHexString(scenario.rai_data_, opt_data))
                            << "scenario.rai_data_ is invalid, test is broken";
            OptionPtr rai;
            ASSERT_NO_THROW(rai.reset(new Option(Option::V4, 0x52, opt_data)))
                            << "could not create rai option, test is broken";

            ctx.query_->addOption(rai);
        }

        // Call AllocEngine::updateLease4ExtendeInfo().
        bool ret = false;
        ASSERT_NO_THROW_LOG(ret = engine.callUpdateLease4ExtendedInfo(lease, ctx));
        ASSERT_EQ(scenario.exp_ret, ret);

        // Verify the lease has the expected user context content.
        if (!exp_context) {
            ASSERT_FALSE(lease->getContext());
        } else {
            ASSERT_TRUE(lease->getContext());
            ASSERT_TRUE(exp_context->equals(*(lease->getContext())))
                << "expected: " << *(exp_context) << std::endl
                << "  actual: " << *(lease->getContext()) << std::endl;
        }
    }
}

// Verifies that the extended data (e.g. RAI option for now) is
// added to a V4 lease when leases are created and/or renewed,
// when store-extended-info is true.
TEST_F(AllocEngine4Test, storeExtendedInfoEnabled4) {

    // Structure that defines a test scenario.
    struct Scenario {
        std::string description_;       // test description
        std::vector<uint8_t> mac_;      // MAC address
        std::string rai_data_;          // RAI option the client packet contains
        std::string exp_context_json_;  // expected user context on the lease
        std::string exp_address_;        // expected lease address
    };

    std::vector<uint8_t> mac1 = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0x01 };
    std::string mac1_addr = "192.0.2.100";

    std::vector<uint8_t> mac2 = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0x02 };
    std::string mac2_addr = "192.0.2.101";

    // Test scenarios.
    std::vector<Scenario> scenarios {
    {
        "create client one without rai",
        mac1,
        "",
        "",
        mac1_addr
    },
    {
        "renew client one without rai",
        {},
        "",
        "",
        mac1_addr
    },
    {
        "create client two with rai",
        mac2,
        "0x52050104a1b1c1d1",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104A1B1C1D1\" } }",
        mac2_addr
    },
    {
        "renew client two without rai",
        {},
        "",
        "{ \"ISC\": { \"relay-agent-info\": \"0x52050104A1B1C1D1\" } }",
        mac2_addr
    }};

    // Create the allocation engine, context and lease.
    NakedAllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // All of the scenarios require storage to be enabled.
    subnet_->setStoreExtendedInfo(true);

    AllocEngine::ClientContext4 ctx(subnet_, ClientIdPtr(), hwaddr_,
                                    IOAddress::IPV4_ZERO_ADDRESS(),
                                    false, false, "", false);

    // Iterate over the test scenarios.
    Lease4Ptr lease;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        ElementPtr exp_context;
        // Create the expected user context from JSON.
        if (!scenario.exp_context_json_.empty()) {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(scenario.exp_context_json_))
                            << "invalid exp_context_json_, test is broken";
        }

        // If we have a MAC address this scenario is for a new client.
        if (!scenario.mac_.empty()) {
            std::cout << "setting mac address" << std::endl;
            ASSERT_NO_THROW(ctx.hwaddr_.reset(new HWAddr(scenario.mac_, HTYPE_ETHER)))
                            << "invalid MAC address, test is broken";
        }

        // Create the client packet and the add RAI option (if one).
        ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
        if (!scenario.rai_data_.empty()) {
            std::vector<uint8_t> opt_data;
            ASSERT_NO_THROW(util::str::decodeFormattedHexString(scenario.rai_data_, opt_data))
                            << "scenario.rai_data_ is invalid, test is broken";
            OptionPtr rai;
            ASSERT_NO_THROW(rai.reset(new Option(Option::V4, 0x52, opt_data)))
                            << "could not create rai option, test is broken";

            ctx.query_->addOption(rai);
        }

        // Create or renew the lease.
        Lease4Ptr lease = engine.allocateLease4(ctx);
        ASSERT_TRUE(lease);
        EXPECT_EQ(scenario.exp_address_, lease->addr_.toText());

        // Verify the lease has the expected user context content.
        if (!exp_context) {
            ASSERT_FALSE(lease->getContext());
        } else {
            ASSERT_TRUE(lease->getContext());
            ASSERT_TRUE(exp_context->equals(*(lease->getContext())))
                << "expected: " << *(exp_context) << std::endl
                << "  actual: " << *(lease->getContext()) << std::endl;
        }
    }
}

// Verifies that the extended data (e.g. RAI option for now) is
// not added to a V4 lease when leases are created and/or renewed,
// when store-extended-info is false.
TEST_F(AllocEngine4Test, storeExtendedInfoDisabled4) {

    // Structure that defines a test scenario.
    struct Scenario {
        std::string description_;       // test description
        std::vector<uint8_t> mac_;      // MAC address
        std::string rai_data_;          // RAI option the client packet contains
        std::string exp_address_;       // expected lease address
    };

    std::vector<uint8_t> mac1 = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0x01 };
    std::string mac1_addr = "192.0.2.100";

    std::vector<uint8_t> mac2 = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0x02 };
    std::string mac2_addr = "192.0.2.101";

    // Test scenarios.
    std::vector<Scenario> scenarios {
    {
        "create client one without rai",
        mac1,
        "",
        mac1_addr
    },
    {
        "renew client one without rai",
        {},
        "",
        mac1_addr
    },
    {
        "create client two with rai",
        mac2,
        "0x52050104a1b1c1d1",
        mac2_addr
    },
    {
        "renew client two with rai",
        {},
        "0x52050104a1b1c1d1",
        mac2_addr
    }};

    // Create the allocation engine, context and lease.
    NakedAllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // All of the scenarios require storage to be disabled.
    subnet_->setStoreExtendedInfo(false);

    AllocEngine::ClientContext4 ctx(subnet_, ClientIdPtr(), hwaddr_,
                                    IOAddress::IPV4_ZERO_ADDRESS(),
                                    false, false, "", false);

    Lease4Ptr lease;

    // Iterate over the test scenarios.
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // If we have a MAC address this scenario is for a new client.
        if (!scenario.mac_.empty()) {
            std::cout << "setting mac address" << std::endl;
            ASSERT_NO_THROW(ctx.hwaddr_.reset(new HWAddr(scenario.mac_, HTYPE_ETHER)))
                            << "invalid MAC address, test is broken";
        }

        // Create the client packet and the add RAI option (if one).
        ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
        if (!scenario.rai_data_.empty()) {
            std::vector<uint8_t> opt_data;
            ASSERT_NO_THROW(util::str::decodeFormattedHexString(scenario.rai_data_, opt_data))
                            << "scenario.rai_data_ is invalid, test is broken";
            OptionPtr rai;
            ASSERT_NO_THROW(rai.reset(new Option(Option::V4, 0x52, opt_data)))
                            << "could not create rai option, test is broken";

            ctx.query_->addOption(rai);
        }

        // Create or renew the lease.
        Lease4Ptr lease = engine.allocateLease4(ctx);
        ASSERT_TRUE(lease);
        EXPECT_EQ(scenario.exp_address_, lease->addr_.toText());

        // Verify the lease does not have user context content.
        ASSERT_FALSE(lease->getContext());
    }
}

// This test checks if a lease can be reused in DHCPDISCOVER (fake allocation)
// using cache threshold.
TEST_F(AllocEngine4Test, discoverCacheThreshold4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for fake allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", true);

    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(valid - age, lease->reuseable_valid_lft_);

    // Check other lease parameters.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);
}

// This test checks if a lease can be reused in DHCPREQUEST (real allocation)
// using cache threshold.
TEST_F(AllocEngine4Test, requestCacheThreshold4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease4Ptr original_lease(new Lease4(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for real allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", false);

    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(valid - age, lease->reuseable_valid_lft_);

    // Check other lease parameters.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the lease was not updated in the database.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

/// We proved that there is no different from the "cache" feature between
/// discovers and request at the exception of the lease database update.

// This test checks if a lease can be reused in DHCPDISCOVER (fake allocation)
// using cache max age.
TEST_F(AllocEngine4Test, discoverCacheMaxAge4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the max age to 200.
    subnet_->setCacheMaxAge(200);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for fake allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", true);

    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(valid - age, lease->reuseable_valid_lft_);

    // Check other lease parameters.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);
}

// This test checks if a lease can be reused in DHCPREQUEST (real allocation)
// using both cache threshold and max age.
TEST_F(AllocEngine4Test, requestCacheBoth4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 200.
    subnet_->setCacheMaxAge(200);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease4Ptr original_lease(new Lease4(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for real allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", false);

    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(valid - age, lease->reuseable_valid_lft_);

    // Check other lease parameters.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the lease was not updated in the database.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// This test checks if a lease can't be reused in DHCPDISCOVER (fake allocation)
// using too small cache threshold.
TEST_F(AllocEngine4Test, discoverCacheBadThreshold4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the threshold to 10%.
    subnet_->setCacheThreshold(.10);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for fake allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", true);

    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);
}

// This test checks if a lease can't be reused in DHCPREQUEST (real allocation)
// using too small cache max age.
TEST_F(AllocEngine4Test, requestCacheBadMaxAge4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 50.
    subnet_->setCacheMaxAge(50);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());

    // Create a context for real allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", false);

    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// This test checks if a lease can't be reused in DHCPDISCOVER (fake allocation)
// when the valid lifetime was reduced.
TEST_F(AllocEngine4Test, discoverCacheReducedValid4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 200.
    subnet_->setValid(200);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    uint32_t valid = 500; // Used a value greater than subnet_->getValid().
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for fake allocation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "", true);

    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);
}

// This test checks if a lease can't be reused in DHCPREQUEST (real allocation)
// when DDNS parameter changed.
TEST_F(AllocEngine4Test, requestCacheFwdDDNS4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the max age to 200.
    subnet_->setCacheMaxAge(200);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());

    // Create a context for real allocation with fwd_dns_update changed.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    true, false, "", false);

    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// This test checks if a lease can't be reused in DHCPDISCOVER (fake allocation)
// when DDNS parameter changed.
TEST_F(AllocEngine4Test, discoverCacheRevDDNS4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 200.
    subnet_->setCacheMaxAge(200);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID()));
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for fake allocation with rev_dns_update changed.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, true, "", true);

    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);
}

// This test checks if a lease can't be reused in DHCPREQUEST (real allocation)
// when hostname changed.
TEST_F(AllocEngine4Test, requestCacheHostname4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 500.
    uint32_t valid = 500;
    subnet_->setValid(valid);

    // Set the max age to 200.
    subnet_->setCacheMaxAge(200);

    IOAddress addr("192.0.2.105");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease4Ptr lease(new Lease4(addr, hwaddr_, clientid_,
                               valid, now, subnet_->getID(),
                               false, false, "foo"));
    ASSERT_FALSE(lease->expired());

    // Create a context for real allocation with fwd_dns_update changed.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, addr,
                                    false, false, "bar", false);

    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx);
    // Check that we got that single lease.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);
    EXPECT_EQ("bar", lease->hostname_);

    // Check the lease was updated in the database.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Verifies that AllocEngine::getValidLft(ctx4) returns the appropriate
// lifetime value based on the context content.
TEST_F(AllocEngine4Test, getValidLft4) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0, false);

    // Let's make three classes, two with valid-lifetime and one without,
    // and add them to the dictionary.
    ClientClassDictionaryPtr dictionary = CfgMgr::instance().getStagingCfg()->getClientClassDictionary();

    ClientClassDefPtr class_def(new ClientClassDef("valid_one", ExpressionPtr()));
    Triplet<uint32_t> valid_one(50, 100, 150);
    class_def->setValid(valid_one);
    dictionary->addClass(class_def);

    class_def.reset(new ClientClassDef("valid_two", ExpressionPtr()));
    Triplet<uint32_t>valid_two(200, 250, 300);
    class_def->setValid(valid_two);
    dictionary->addClass(class_def);

    class_def.reset(new ClientClassDef("valid_unspec", ExpressionPtr()));
    dictionary->addClass(class_def);

    // Commit our class changes.
    CfgMgr::instance().commit();

    // Update the subnet's triplet to something more useful.
    subnet_->setValid(Triplet<uint32_t>(500, 1000, 1500));

    // Describes a test scenario.
    struct Scenario {
        std::string desc_;                  // descriptive text for logging
        std::vector<std::string> classes_;  // class list of assigned classes
        uint32_t requested_lft_;            // use as option 51 is > 0
        uint32_t exp_valid_;                // expected lifetime
    };

    // Scenarios to test.
    std::vector<Scenario> scenarios = {
        {
            "BOOTP",
            { "BOOTP" },
            0,
            Lease::INFINITY_LFT
        },
        {
            "no classes, no option",
            {},
            0,
            subnet_->getValid()
        },
        {
            "no classes, option",
            {},
            subnet_->getValid().getMin() + 50,
            subnet_->getValid().getMin() + 50
        },
        {
            "no classes, option too small",
            {},
            subnet_->getValid().getMin() - 50,
            subnet_->getValid().getMin()
        },
        {
            "no classes, option too big",
            {},
            subnet_->getValid().getMax() + 50,
            subnet_->getValid().getMax()
        },
        {
            "class unspecified, no option",
            { "valid_unspec" },
            0,
            subnet_->getValid()
        },
        {
            "from last class, no option",
            { "valid_unspec", "valid_one" },
            0,
            valid_one.get()
        },
        {
            "from first class, no option",
            { "valid_two", "valid_one" },
            0,
            valid_two.get()
        },
        {
            "class plus option",
            { "valid_one" },
            valid_one.getMin() + 25,
            valid_one.getMin() + 25
        },
        {
            "class plus option too small",
            { "valid_one" },
            valid_one.getMin() - 25,
            valid_one.getMin()
        },
        {
            "class plus option too big",
            { "valid_one" },
            valid_one.getMax() + 25,
            valid_one.getMax()
        }
    };

    // Iterate over the scenarios and verify the correct outcome.
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.desc_); {
            // Create a context;
            AllocEngine::ClientContext4 ctx(subnet_, ClientIdPtr(), hwaddr_,
                                            IOAddress("0.0.0.0"), false, false,
                                            "", false);
            ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

            // Add client classes (if any)
            for (auto class_name : scenario.classes_) {
                ctx.query_->addClass(class_name);
            }

            // Add client option (if one)
            if (scenario.requested_lft_) {
                OptionUint32Ptr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME,
                                                     scenario.requested_lft_));
                ctx.query_->addOption(opt);
            }

            Lease4Ptr lease = engine.allocateLease4(ctx);
            ASSERT_TRUE(lease);
            EXPECT_EQ(lease->valid_lft_, scenario.exp_valid_);
        }
    }
}

// This test checks that deleteRelease handles BOOTP leases.
TEST_F(AllocEngine4Test, bootpDelete) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now delete it.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = LeaseMgrFactory::instance().deleteLease(lease));
    EXPECT_TRUE(deleted);
    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    EXPECT_FALSE(from_mgr);
}

#ifdef HAVE_MYSQL
/// @brief Extension of the fixture class to use the MySQL backend.
class MySqlAllocEngine4Test : public AllocEngine4Test {
public:
    /// @brief Constructor.
    MySqlAllocEngine4Test() {
        // Ensure we have the proper schema with no transient data.
        db::test::createMySQLSchema();
        factory_.create(db::test::validMySQLConnectionString());
    }

    /// @brief Destructor.
    ~MySqlAllocEngine4Test() {
        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        db::test::destroyMySQLSchema();
        LeaseMgrFactory::destroy();
    }
};

// This test checks that simple allocation handles BOOTP queries.
TEST_F(MySqlAllocEngine4Test, bootpAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    // The MySQL database does not keep the hwtype for DHCPv4 leases.
    from_mgr->hwaddr_->htype_ = HTYPE_FDDI;

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks simple renewal handles BOOTP queries.
TEST_F(MySqlAllocEngine4Test, bootpRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease2);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease2->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease2->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease2->addr_));
    ASSERT_TRUE(lease2->client_id_);
    EXPECT_TRUE(*lease2->client_id_ == *clientid_);
    ASSERT_TRUE(lease2->hwaddr_);
    EXPECT_TRUE(*lease2->hwaddr_ == *hwaddr_);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the max value.
    EXPECT_EQ(infinity_lft, lease2->valid_lft_);
}

// This test checks that deleteRelease handles BOOTP leases.
TEST_F(MySqlAllocEngine4Test, bootpDelete) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now delete it.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = LeaseMgrFactory::instance().deleteLease(lease));
    EXPECT_TRUE(deleted);
    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    EXPECT_FALSE(from_mgr);
}
#endif

#ifdef HAVE_PGSQL
/// @brief Extension of the fixture class to use the PostgreSql backend.
class PgSqlAllocEngine4Test : public AllocEngine4Test {
public:
    /// @brief Constructor.
    PgSqlAllocEngine4Test() {
        // Ensure we have the proper schema with no transient data.
        db::test::createPgSQLSchema();
        factory_.create(db::test::validPgSQLConnectionString());
    }

    /// @brief Destructor.
    ~PgSqlAllocEngine4Test() {
        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        db::test::destroyPgSQLSchema();
        LeaseMgrFactory::destroy();
    }
};

// This test checks that simple allocation handles BOOTP queries.
TEST_F(PgSqlAllocEngine4Test, bootpAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    // The PostgreSql database does not keep the hwtype for DHCPv4 leases.
    from_mgr->hwaddr_->htype_ = HTYPE_FDDI;

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks simple renewal handles BOOTP queries.
TEST_F(PgSqlAllocEngine4Test, bootpRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease2);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease2->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease2->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease2->addr_));
    ASSERT_TRUE(lease2->client_id_);
    EXPECT_TRUE(*lease2->client_id_ == *clientid_);
    ASSERT_TRUE(lease2->hwaddr_);
    EXPECT_TRUE(*lease2->hwaddr_ == *hwaddr_);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the max value.
    EXPECT_EQ(infinity_lft, lease2->valid_lft_);
}

// This test checks that deleteRelease handles BOOTP leases.
TEST_F(PgSqlAllocEngine4Test, bootpDelete) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now delete it.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = LeaseMgrFactory::instance().deleteLease(lease));
    EXPECT_TRUE(deleted);
    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    EXPECT_FALSE(from_mgr);
}
#endif

#ifdef HAVE_CQL
/// @brief Extension of the fixture class to use the Cassandra backend.
class CqlAllocEngine4Test : public AllocEngine4Test {
public:
    /// @brief Constructor.
    CqlAllocEngine4Test() {
        // Ensure we have the proper schema with no transient data.
        db::test::createCqlSchema();
        factory_.create(db::test::validCqlConnectionString());
    }

    /// @brief Destructor.
    ~CqlAllocEngine4Test() {
        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        db::test::destroyCqlSchema();
        LeaseMgrFactory::destroy();
    }
};

// This test checks that simple allocation handles BOOTP queries.
TEST_F(CqlAllocEngine4Test, bootpAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    // The Cassandra database does not keep the hwtype for DHCPv4 leases.
    from_mgr->hwaddr_->htype_ = HTYPE_FDDI;

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks simple renewal handles BOOTP queries.
TEST_F(CqlAllocEngine4Test, bootpRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease2);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease2->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease2->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease2->addr_));
    ASSERT_TRUE(lease2->client_id_);
    EXPECT_TRUE(*lease2->client_id_ == *clientid_);
    ASSERT_TRUE(lease2->hwaddr_);
    EXPECT_TRUE(*lease2->hwaddr_ == *hwaddr_);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the max value.
    EXPECT_EQ(infinity_lft, lease2->valid_lft_);
}

// This test checks that deleteRelease handles BOOTP leases.
TEST_F(CqlAllocEngine4Test, bootpDelete) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 0, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now delete it.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = LeaseMgrFactory::instance().deleteLease(lease));
    EXPECT_TRUE(deleted);
    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    EXPECT_FALSE(from_mgr);
}
#endif

}  // namespace test
}  // namespace dhcp
}  // namespace isc
