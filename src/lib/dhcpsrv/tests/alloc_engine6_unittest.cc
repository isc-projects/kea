// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>

using namespace std;
using namespace isc::hooks;
using namespace isc::asiolink;
using namespace isc::stats;
using namespace isc::data;

namespace isc {
namespace dhcp {
namespace test {

// Test convenience method adding hints to IA context.
TEST(ClientContext6Test, addHint) {
   AllocEngine::ClientContext6 ctx;
   ctx.currentIA().addHint(IOAddress("2001:db8:1::1"));
   ctx.currentIA().addHint(IOAddress("3000:1::"), 64);
   ctx.currentIA().addHint(IOAddress("3001:2::"), 64, 100, 200);

   ASSERT_EQ(3, ctx.currentIA().hints_.size());
   EXPECT_EQ("2001:db8:1::1", ctx.currentIA().hints_[0].getAddress().toText());
   EXPECT_EQ("3000:1::", ctx.currentIA().hints_[1].getAddress().toText());
   EXPECT_EQ("3001:2::", ctx.currentIA().hints_[2].getAddress().toText());
   EXPECT_EQ(100, ctx.currentIA().hints_[2].getPreferred());
   EXPECT_EQ(200, ctx.currentIA().hints_[2].getValid());
}

// Test convenience method adding allocated prefixes and addresses to
// a context.
TEST(ClientContext6Test, addAllocatedResource) {
   AllocEngine::ClientContext6 ctx;
   ctx.addAllocatedResource(IOAddress("2001:db8:1::1"));
   ctx.addAllocatedResource(IOAddress("3000:1::"), 64);

   ASSERT_EQ(2, ctx.allocated_resources_.size());
   EXPECT_TRUE(ctx.isAllocated(IOAddress("2001:db8:1::1")));
   EXPECT_TRUE(ctx.isAllocated(IOAddress("3000:1::"), 64));
}

// This test checks if the v6 Allocation Engine can be instantiated, parses
// parameters string and allocators are created.
TEST_F(AllocEngine6Test, constructor) {
    boost::scoped_ptr<AllocEngine> x;

    // Hashed and random allocators are not supported yet
    ASSERT_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_HASHED, 5)), NotImplemented);
    ASSERT_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_RANDOM, 5)), NotImplemented);

    ASSERT_NO_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100, true)));

    // Check that allocator for normal addresses is created
    ASSERT_TRUE(x->getAllocator(Lease::TYPE_NA));

    // Check that allocator for temporary address is created
    ASSERT_TRUE(x->getAllocator(Lease::TYPE_TA));

    // Check that allocator for prefixes is created
    ASSERT_TRUE(x->getAllocator(Lease::TYPE_PD));

    // There should be no V4 allocator
    EXPECT_THROW(x->getAllocator(Lease::TYPE_V4), BadValue);
}

// This test checks if two simple IPv6 allocations succeed and that the
// statistics is properly updated. Prior to the second allocation it
// resets the pointer to the last allocated address within the address
// pool. This causes the engine to walk over the already allocated
// address and then pick the first available address for the second
// allocation. Because the allocation engine checks the callouts next
// step status after each attempt to allocate an address, this test
// also sets this status to non-default value prior to the second
// allocation attempt, to make sure that this unexpected status will
// not interfere with the allocation.
TEST_F(AllocEngine6Test, simpleAlloc6) {
    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    simpleAlloc6Test(pool_, IOAddress("::"), false);

    // We should have bumped the assigned counter by 1
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // Reset last allocated address to check that the other client will
    // be refused the already allocated address and will get the one
    // available.
    pool_->resetLastAllocated();

    // Simulate another client. This client should be assigned a different
    // address.
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 0x84)));
    simpleAlloc6Test(pool_, duid, IOAddress("::"), false);

    // We should have bumped the assigned counter by 2
    EXPECT_TRUE(testStatistics("assigned-nas", 2, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// This test checks that simple allocation uses default lifetimes.
TEST_F(AllocEngine6Test, defaultAlloc6) {
    simpleAlloc6Test(pool_, IOAddress("::"), 0, 0, 300, 400);
}

// This test checks that simple allocation uses specified lifetimes.
TEST_F(AllocEngine6Test, hintAlloc6) {
    simpleAlloc6Test(pd_pool_, IOAddress("::"), 301, 399, 301, 399);
}

// This test checks that simple allocation uses min lifetimes.
TEST_F(AllocEngine6Test, minAlloc6) {
    simpleAlloc6Test(pool_, IOAddress("::"), 100, 200, 200, 300);
}

// This test checks that simple allocation uses max lifetimes.
TEST_F(AllocEngine6Test, maxAlloc6) {
    simpleAlloc6Test(pd_pool_, IOAddress("::"), 500, 600, 400, 500);
}

// This test checks if the simple PD allocation (REQUEST) can succeed
// and the stats counter is properly bumped by 1
TEST_F(AllocEngine6Test, pdSimpleAlloc6) {
    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-pds", 0, subnet_->getID()));

    // Get the cumulative count of assigned prefixes.
    int64_t cumulative = getStatistics("cumulative-assigned-pds",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-pds");

    simpleAlloc6Test(pd_pool_, IOAddress("::"), false);

    // We should have bumped the assigned counter by 1
    EXPECT_TRUE(testStatistics("assigned-pds", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-pds",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-pds", glbl_cumulative));
}

// This test checks if the fake allocation (for SOLICIT) can succeed
// and the stats counter isn't bumped
TEST_F(AllocEngine6Test, fakeAlloc6) {
    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    simpleAlloc6Test(pool_, IOAddress("::"), true);

    // We should not have bumped the assigned counter.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// This test checks if the fake PD allocation (for SOLICIT) can succeed
// and the stats counter isn't bumped
TEST_F(AllocEngine6Test, pdFakeAlloc6) {
    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-pds", 0, subnet_->getID()));

    // Get the cumulative count of assigned prefixes.
    int64_t cumulative = getStatistics("cumulative-assigned-pds",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-pds");

    simpleAlloc6Test(pd_pool_, IOAddress("::"), true);

    // We should not have bumped the assigned counter
    EXPECT_TRUE(testStatistics("assigned-pds", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-pds", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-pds"));
}

// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngine6Test, allocWithValidHint6) {

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::15"),
                                       false);
    ASSERT_TRUE(lease);

    // We should get what we asked for
    EXPECT_EQ("2001:db8:1::15", lease->addr_.toText());
}

// This test checks if the address allocation with a hint that is in range,
// in pool, but is currently used, can succeed
TEST_F(AllocEngine6Test, allocWithUsedHint6) {
    allocWithUsedHintTest(Lease::TYPE_NA,
                          IOAddress("2001:db8:1::1f"), // allocate this as used
                          IOAddress("2001:db8:1::1f"), // request this addr
                          128);
}

// This test checks if the PD allocation with a hint that is in range,
// in pool, but is currently used, can succeed
TEST_F(AllocEngine6Test, pdAllocWithUsedHint6) {
    allocWithUsedHintTest(Lease::TYPE_PD,
                          IOAddress("2001:db8:1:2::"), // allocate this prefix as used
                          IOAddress("2001:db8:1:2::"), // request this prefix
                          80);
}

// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine6Test, allocBogusHint6) {

    allocBogusHint6(Lease::TYPE_NA, IOAddress("3000::abc"), 128);
}

// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine6Test, pdAllocBogusHint6) {

    allocBogusHint6(Lease::TYPE_PD, IOAddress("3000::abc"), 80);
}

// This test checks that NULL values are handled properly
TEST_F(AllocEngine6Test, allocateAddress6Nulls) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx1(Subnet6Ptr(), duid_, false, false, "", false,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx1.currentIA().iaid_ = iaid_;

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx1)));
    ASSERT_FALSE(lease);

    // Allocations without DUID are not allowed either
    AllocEngine::ClientContext6 ctx2(subnet_, DuidPtr(), false, false, "", false,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));
    ASSERT_FALSE(lease);
}


// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine6Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Lease::TYPE_NA));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, cc_,
                                                 duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
    }
}

// This test verifies that the allocator picks addresses that belong to the
// pool using classification
TEST_F(AllocEngine6Test, IterativeAllocator_class) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Lease::TYPE_NA));

    // Restrict pool_ to the foo class. Add a second pool with bar class.
    pool_->allowClientClass("foo");
    Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                            IOAddress("2001:db8:1::109")));
    pool->allowClientClass("bar");
    subnet_->addPool(pool);

    // Clients are in bar
    cc_.insert("bar");

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, cc_,
                                                 duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
    }
}

TEST_F(AllocEngine6Test, IterativeAllocatorAddrStep) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_NA);

    subnet_->delPools(Lease::TYPE_NA); // Get rid of default pool

    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::5")));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                             IOAddress("2001:db8:1::100")));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::105"),
                             IOAddress("2001:db8:1::106")));
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    // Let's check the first pool (5 addresses here)
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // The second pool is easy - only one address here
    EXPECT_EQ("2001:db8:1::100",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
}

TEST_F(AllocEngine6Test, IterativeAllocatorAddrStepInClass) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_NA);

    subnet_->delPools(Lease::TYPE_NA); // Get rid of default pool

    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::5")));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                             IOAddress("2001:db8:1::100")));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::105"),
                             IOAddress("2001:db8:1::106")));
    // Set pool1 and pool3 but not pool2 in foo class
    pool1->allowClientClass("foo");
    pool3->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    // Clients are in foo
    cc_.insert("foo");

    // Let's check the first pool (5 addresses here)
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // The second pool is easy - only one address here
    EXPECT_EQ("2001:db8:1::100",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
}

TEST_F(AllocEngine6Test, IterativeAllocatorAddrStepOutClass) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_NA);

    subnet_->delPools(Lease::TYPE_NA); // Get rid of default pool

    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::5")));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                             IOAddress("2001:db8:1::100")));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::105"),
                             IOAddress("2001:db8:1::106")));
    // Set pool2 in foo
    pool2->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    // Let's check the first pool (5 addresses here)
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // The second pool is skipped

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
}

TEST_F(AllocEngine6Test, IterativeAllocatorPrefixStep) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_PD);

    subnet_.reset(new Subnet6(IOAddress("2001:db8::"), 32, 1, 2, 3, 4));

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
}

TEST_F(AllocEngine6Test, IterativeAllocatorPrefixStepInClass) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_PD);

    subnet_.reset(new Subnet6(IOAddress("2001:db8::"), 32, 1, 2, 3, 4));

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    // Set pool1 and pool3 but not pool2 in foo class
    pool1->allowClientClass("foo");
    pool3->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    // Clients are in foo
    cc_.insert("foo");

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
}

TEST_F(AllocEngine6Test, IterativeAllocatorPrefixStepOutClass) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_PD);

    subnet_.reset(new Subnet6(IOAddress("2001:db8::"), 32, 1, 2, 3, 4));

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    // Set pool2 in foo
    pool2->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // The second pool is skipped

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickAddress(subnet_, cc_, duid_, IOAddress("::")).toText());
}

// This test verifies that the iterative allocator can step over addresses
TEST_F(AllocEngine6Test, IterativeAllocatorAddressIncrease) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_NA);

    // Let's pick the first address
    IOAddress addr1 = alloc.pickAddress(subnet_, cc_, duid_, IOAddress("2001:db8:1::10"));

    // Check that we can indeed pick the first address from the pool
    EXPECT_EQ("2001:db8:1::10", addr1.toText());

    // Check that addresses can be increased properly
    checkAddrIncrease(alloc, "2001:db8::9", "2001:db8::a");
    checkAddrIncrease(alloc, "2001:db8::f", "2001:db8::10");
    checkAddrIncrease(alloc, "2001:db8::10", "2001:db8::11");
    checkAddrIncrease(alloc, "2001:db8::ff", "2001:db8::100");
    checkAddrIncrease(alloc, "2001:db8::ffff", "2001:db8::1:0");
    checkAddrIncrease(alloc, "::", "::1");
    checkAddrIncrease(alloc, "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "::");
}

// This test verifies that the allocator can step over prefixes
TEST_F(AllocEngine6Test, IterativeAllocatorPrefixIncrease) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_PD);

    // For /128 prefix, increasePrefix should work the same as addressIncrease
    checkPrefixIncrease(alloc, "2001:db8::9", 128, "2001:db8::a");
    checkPrefixIncrease(alloc, "2001:db8::f", 128, "2001:db8::10");
    checkPrefixIncrease(alloc, "2001:db8::10", 128, "2001:db8::11");
    checkPrefixIncrease(alloc, "2001:db8::ff", 128, "2001:db8::100");
    checkPrefixIncrease(alloc, "2001:db8::ffff", 128, "2001:db8::1:0");
    checkPrefixIncrease(alloc, "::", 128, "::1");
    checkPrefixIncrease(alloc, "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", 128, "::");

    // Check that /64 prefixes can be generated
    checkPrefixIncrease(alloc, "2001:db8::", 64, "2001:db8:0:1::");

    // Check that prefix length not divisible by 8 are working
    checkPrefixIncrease(alloc, "2001:db8::", 128, "2001:db8::1");
    checkPrefixIncrease(alloc, "2001:db8::", 127, "2001:db8::2");
    checkPrefixIncrease(alloc, "2001:db8::", 126, "2001:db8::4");
    checkPrefixIncrease(alloc, "2001:db8::", 125, "2001:db8::8");
    checkPrefixIncrease(alloc, "2001:db8::", 124, "2001:db8::10");
    checkPrefixIncrease(alloc, "2001:db8::", 123, "2001:db8::20");
    checkPrefixIncrease(alloc, "2001:db8::", 122, "2001:db8::40");
    checkPrefixIncrease(alloc, "2001:db8::", 121, "2001:db8::80");
    checkPrefixIncrease(alloc, "2001:db8::", 120, "2001:db8::100");

    // These are not really useful cases, because there are bits set
    // int the last (128 - prefix_len) bits. Nevertheless, it shows
    // that the algorithm is working even in such cases
    checkPrefixIncrease(alloc, "2001:db8::1", 128, "2001:db8::2");
    checkPrefixIncrease(alloc, "2001:db8::1", 127, "2001:db8::3");
    checkPrefixIncrease(alloc, "2001:db8::1", 126, "2001:db8::5");
    checkPrefixIncrease(alloc, "2001:db8::1", 125, "2001:db8::9");
    checkPrefixIncrease(alloc, "2001:db8::1", 124, "2001:db8::11");
    checkPrefixIncrease(alloc, "2001:db8::1", 123, "2001:db8::21");
    checkPrefixIncrease(alloc, "2001:db8::1", 122, "2001:db8::41");
    checkPrefixIncrease(alloc, "2001:db8::1", 121, "2001:db8::81");
    checkPrefixIncrease(alloc, "2001:db8::1", 120, "2001:db8::101");

    // Let's try out couple real life scenarios
    checkPrefixIncrease(alloc, "2001:db8:1:abcd::", 64, "2001:db8:1:abce::");
    checkPrefixIncrease(alloc, "2001:db8:1:abcd::", 60, "2001:db8:1:abdd::");
    checkPrefixIncrease(alloc, "2001:db8:1:abcd::", 56, "2001:db8:1:accd::");
    checkPrefixIncrease(alloc, "2001:db8:1:abcd::", 52, "2001:db8:1:bbcd::");

    // And now let's try something over the top
    checkPrefixIncrease(alloc, "::", 1, "8000::");
}

// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space and must start over.
TEST_F(AllocEngine6Test, IterativeAllocator_manyPools6) {
    NakedAllocEngine::IterativeAllocator alloc(Lease::TYPE_NA);

    // let's start from 2, as there is 2001:db8:1::10 - 2001:db8:1::20 pool already.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;

        min << "2001:db8:1::" << hex << i*16 + 1;
        max << "2001:db8:1::" << hex << i*16 + 9;

        Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress(min.str()),
                                IOAddress(max.str())));
        subnet_->addPool(pool);
    }

    int total = 17 + 8 * 9; // First pool (::10 - ::20) has 17 addresses in it,
                            // there are 8 extra pools with 9 addresses in each.

    // Let's keep picked addresses here and check their uniqueness.
    std::set<IOAddress> generated_addrs;
    int cnt = 0;
    while (++cnt) {
        IOAddress candidate = alloc.pickAddress(subnet_, cc_,
                                                duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));

        // One way to easily verify that the iterative allocator really works is
        // to uncomment the following line and observe its output that it
        // covers all defined pools.
        // cout << candidate.toText() << endl;

        if (generated_addrs.find(candidate) == generated_addrs.end()) {
            // We haven't had this.
            generated_addrs.insert(candidate);
        } else {
            // We have seen this address before. That should mean that we
            // iterated over all addresses.
            if (generated_addrs.size() == total) {
                // We have exactly the number of address in all pools.
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
TEST_F(AllocEngine6Test, smallPool6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");

    // Create a subnet with a pool that has one address.
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);

    // Initialize FQDN for a lease.
    initFqdn("myhost.example.com", true, true);

    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, fqdn_fwd_, fqdn_rev_,
                                    hostname_, false,
                                    Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx.currentIA().iaid_ = iaid_;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);

    EXPECT_EQ("2001:db8:1::ad", lease->addr_.toText());

    // Do all checks on the lease
    checkLease6(duid_, lease, Lease::TYPE_NA, 128);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // This is a new lease allocation. The old lease corresponding to a newly
    // allocated lease should be NULL.
    ASSERT_TRUE(ctx.currentIA().old_leases_.empty());
}

// This test checks if all addresses in a pool are currently used, the attempt
// to find out a new lease fails.
TEST_F(AllocEngine6Test, outOfAddresses6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets6()->add(subnet_);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // There is just a single address in the pool and allocated it to someone
    // else, so the allocation should fail
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    Lease6Ptr lease2;
    EXPECT_NO_THROW(lease2 = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_FALSE(lease2);

}


// This test checks if an expired lease can be reused in SOLICIT (fake allocation)
TEST_F(AllocEngine6Test, solicitReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");

    // Create one subnet with a pool holding one address.
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);

    // Initialize FQDN data for the lease.
    initFqdn("myhost.example.com", true, true);

    // Verify the all of relevant stats are zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // CASE 1: Asking for any address
    AllocEngine::ClientContext6 ctx1(subnet_, duid_, fqdn_fwd_, fqdn_rev_, hostname_,
                                     true, Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234)));
    ctx1.currentIA().iaid_ = iaid_;

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx1)));
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(duid_, lease, Lease::TYPE_NA, 128);

    // CASE 2: Asking specifically for this address
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Verify the none of relevant stats were altered.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0, subnet_->getID()));
}

// This test checks if an expired lease can be reused using default lifetimes.
TEST_F(AllocEngine6Test, defaultReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");

    // Create one subnet with a pool holding one address.
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // Initialize FQDN data for the lease.
    initFqdn("myhost.example.com", true, true);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // Asking specifically for this address with zero lifetimes
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().addHint(addr, 128, 0, 0);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Check lifetimes: defaults are expected.
    EXPECT_EQ(300, lease->preferred_lft_);
    EXPECT_EQ(400, lease->valid_lft_);
}

// This test checks if an expired lease can be reused using specified lifetimes.
TEST_F(AllocEngine6Test, hintReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");

    // Create one subnet with a pool holding one address.
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // Initialize FQDN data for the lease.
    initFqdn("myhost.example.com", true, true);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // Asking specifically for this address with zero lifetimes
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().addHint(addr, 128, 299, 401);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Check lifetimes: specified values are expected.
    EXPECT_EQ(299, lease->preferred_lft_);
    EXPECT_EQ(401, lease->valid_lft_);
}

// This test checks if an expired lease can be reused using min lifetimes.
TEST_F(AllocEngine6Test, minReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");

    // Create one subnet with a pool holding one address.
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // Initialize FQDN data for the lease.
    initFqdn("myhost.example.com", true, true);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // Asking specifically for this address with zero lifetimes
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().addHint(addr, 128, 100, 200);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Check lifetimes: min values are expected.
    EXPECT_EQ(200, lease->preferred_lft_);
    EXPECT_EQ(300, lease->valid_lft_);
}

// This test checks if an expired lease can be reused using max lifetimes.
TEST_F(AllocEngine6Test, maxReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");

    // Create one subnet with a pool holding one address.
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // Initialize FQDN data for the lease.
    initFqdn("myhost.example.com", true, true);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // Asking specifically for this address with zero lifetimes
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().addHint(addr, 128, 500, 600);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Check lifetimes: max values are expected.
    EXPECT_EQ(400, lease->preferred_lft_);
    EXPECT_EQ(500, lease->valid_lft_);
}

// This test checks if an expired lease can be reused in REQUEST (actual allocation)
TEST_F(AllocEngine6Test, requestReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets6()->add(subnet_);
    cfg_mgr.commit();
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's create an expired lease
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;

    const SubnetID other_subnetid = 999;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, other_subnetid, HWAddrPtr(),
                               0));
    int64_t other_cumulative =
        getStatistics("cumulative-assigned-nas", other_subnetid);

    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    lease->fqdn_fwd_ = true;
    lease->fqdn_rev_ = true;
    lease->hostname_ = "myhost.example.com.";
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // A client comes along, asking specifically for this address
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);
    // This reactivated lease should have updated FQDN data.
    EXPECT_TRUE(lease->hostname_.empty());
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);

    // Check that the old lease has been returned.
    Lease6Ptr old_lease = expectOneLease(ctx.currentIA().old_leases_);
    // It should at least have the same IPv6 address.
    EXPECT_EQ(lease->addr_, old_lease->addr_);
    // Check that it carries not updated FQDN data.
    EXPECT_EQ("myhost.example.com.", old_lease->hostname_);
    EXPECT_TRUE(old_lease->fqdn_fwd_);
    EXPECT_TRUE(old_lease->fqdn_rev_);

    // Check that the lease is indeed updated in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Verify the stats got adjusted correctly
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
    EXPECT_TRUE(testStatistics("assigned-nas", -1, other_subnetid));
    EXPECT_EQ(other_cumulative,
              getStatistics("cumulative-assigned-nas", other_subnetid));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 1));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 1, other_subnetid));
}

// Checks if the lease lifetime is extended when the client sends the
// Request.
TEST_F(AllocEngine6Test, requestExtendLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Client should receive a lease.
    Lease6Ptr new_lease = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(new_lease);

    // And the lease lifetime should be extended.
    EXPECT_GT(new_lease->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";
}

// Checks if the lease lifetime is extended when the client sends the
// Request and the client has a reservation for the lease.
TEST_F(AllocEngine6Test, requestExtendLeaseLifetimeForReservation) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1c"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Client should receive a lease.
    Lease6Ptr new_lease = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(new_lease);

    // And the lease lifetime should be extended.
    EXPECT_GT(new_lease->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";
}

// Checks if the lease lifetime is extended when the client sends the
// Renew.
TEST_F(AllocEngine6Test, renewExtendLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::15"), 128));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";
}

// Checks that a renewed lease uses default lifetimes.
TEST_F(AllocEngine6Test, defaultRenewLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::15"),
                                          128, 0, 0));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";

    // Checks that default values are used for lifetimes.
    EXPECT_EQ(300, renewed[0]->preferred_lft_);
    EXPECT_EQ(400, renewed[0]->valid_lft_);
}

// Checks that a renewed lease uses specified lifetimes.
TEST_F(AllocEngine6Test, hintRenewLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::15"),
                                          128, 301, 399));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";

    // Checks that specified values are used for lifetimes.
    EXPECT_EQ(301, renewed[0]->preferred_lft_);
    EXPECT_EQ(399, renewed[0]->valid_lft_);
}

// Checks that a renewed lease uses min lifetimes.
TEST_F(AllocEngine6Test, minRenewLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::15"),
                                          128, 100, 200));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";

    // Checks that min values are used for lifetimes.
    EXPECT_EQ(200, renewed[0]->preferred_lft_);
    EXPECT_EQ(300, renewed[0]->valid_lft_);
}

// Checks that a renewed lease uses max lifetimes.
TEST_F(AllocEngine6Test, maxRenewLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::15"),
                                          128, 500, 600));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";

    // Checks that max values are used for lifetimes.
    EXPECT_EQ(400, renewed[0]->preferred_lft_);
    EXPECT_EQ(500, renewed[0]->valid_lft_);
}

// Checks if the lease lifetime is extended when the client sends the
// Renew and the client has a reservation for the lease.
TEST_F(AllocEngine6Test, renewExtendLeaseLifetimeForReservation) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::15"), 128);

    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::15"), 128));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";
}

// --- v6 host reservation ---

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends SOLICIT without any hints.
// - Client is allocated a reserved address.
//
// Note that a DHCPv6 client can, but doesn't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressInPoolSolicitNoHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), true);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends REQUEST without any hints.
// - Client is allocated a reserved address.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressInPoolRequestNoHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // Assigned count should have been incremented by one.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends SOLICIT with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressInPoolSolicitValidHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), true);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // Assigned count should not have been incremented.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends REQUEST with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressInPoolRequestValidHint) {
    // Create reservation for the client This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // Assigned count should have been incremented.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends SOLICIT with a hint that does matches reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressInPoolSolicitMatchingHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), true);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // Assigned count should not have been incremented.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends REQUEST with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressInPoolRequestMatchingHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // Assigned count should have been incremented.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// Checks that a client gets the address reserved (out-of-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an out-of-pool reservation.
// - Client sends SOLICIT without any hints.
// - Client is allocated a reserved address.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolSolicitNoHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), true, false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // Assigned count should not have been incremented.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (out-of-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an out-of-pool reservation.
// - Client sends REQUEST without any hints.
// - Client is allocated a reserved address.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolRequestNoHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), false, false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // We should not have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends SOLICIT with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolSolicitValidHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), true, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // We should not have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (out-of-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an out-of-pool reservation.
// - Client sends REQUEST with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolRequestValidHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), false, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // We should not have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (out-of-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an out-of-pool reservation.
// - Client sends SOLICIT with a hint that does matches reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolSolicitMatchingHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), true, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // We should not have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// Checks that a client gets the address reserved (out-of-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an out-of-pool reservation.
// - Client sends REQUEST with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolRequestMatchingHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), false, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // We should not have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
}

// In the following situation:
// - client is assigned an address A
// - HR is made for *this* client to get B
// - client tries to get address A:
//    Check that his existing lease for lease A is removed
//    Check that he is assigned a new lease for B
// - verify that the number of assigned address behaves as expected
TEST_F(AllocEngine6Test, reservedAddressInPoolReassignedThis) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Client gets an address
    Lease6Ptr lease1 = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease1);

    // We should have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // Just check that if the client requests again, it will get the same
    // address.
    Lease6Ptr lease2 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease2);
    detailCompareLease(lease1, lease2);

    // We should not have bumped the address counter again
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // Now admin creates a reservation for this client. This is in-pool
    // reservation, as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    // Just check that this time the client will get.
    Lease6Ptr lease3 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease3);

    // Check that previous lease was not used anymore.
    EXPECT_NE(lease1->addr_.toText(), lease3->addr_.toText());

    // Check that the reserved address was indeed assigned.
    EXPECT_EQ("2001:db8:1::1c", lease3->addr_.toText());

    // Check that the old lease is gone.
    Lease6Ptr old = LeaseMgrFactory::instance().getLease6(lease1->type_,
                                                          lease1->addr_);
    EXPECT_FALSE(old);

    // Check that the reserved lease is in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease1->type_,
                                                  IOAddress("2001:db8:1::1c"));

    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease3, from_mgr);

    // Lastly check to see that the address counter is still 1, we should have
    // have decremented it on the implied release and incremented it on the reserved
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// In the following situation:
// - client X is assigned an address A
// - HR is made for client Y (*other* client) to get A
// - client X tries to get address A:
//    Check that his existing lease for lease A is removed
//    Check that he is assigned a new lease
TEST_F(AllocEngine6Test, reservedAddressInPoolReassignedOther) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Assigned count should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Client gets an address
    Lease6Ptr lease1 = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease1);

    // We should have bumped the address counter
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // Just check that if the client requests again, it will get the same
    // address.
    Lease6Ptr lease2 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease2);
    detailCompareLease(lease1, lease2);

    // We should not have bumped the address counter again
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // Now admin creates a reservation for this client. Let's use the
    // address client X just received. Let's generate a host, but don't add it
    // to the HostMgr yet.
    HostPtr host = createHost6(false, IPv6Resrv::TYPE_NA, lease1->addr_, 128);

    // We need to tweak reservation id: use a different DUID for client Y
    vector<uint8_t> other_duid(8, 0x45);
    host->setIdentifier(&other_duid[0], other_duid.size(), Host::IDENT_DUID);

    // Ok, now add it to the HostMgr
    addHost(host);

    // Just check that this time the client will get a different lease.
    Lease6Ptr lease3 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease3);

    // Check that previous lease was not used anymore.
    EXPECT_NE(lease1->addr_.toText(), lease3->addr_.toText());

    // Check that the old lease is gone.
    Lease6Ptr old = LeaseMgrFactory::instance().getLease6(lease1->type_,
                                                          lease1->addr_);
    EXPECT_FALSE(old);

    // Check that the reserved lease is in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease1->type_,
                                                               lease3->addr_);

    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease3, from_mgr);

    // Lastly check to see that the address counter is still 1 we should have
    // have decremented it on the implied release and incremented it on the reserved
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// Checks that a reserved address for client A is not assigned when
// other clients are requesting addresses. The scenario is as follows:
// we use a regular pool with 17 addresses in it. One of them is
// reserved for client A. Now we try to allocate addresses for 30 clients
// (A is not one of them). The first 16 attempts should succeed. Then
// we run out of addresses and remaining 14 clients will get nothing.
// Finally, we check that client A still can get his reserved address.
TEST_F(AllocEngine6Test, reservedAddress) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, true);

    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::12"), 128);

    // Let's generate 30 DUIDs, each of them 16 bytes long
    vector<DuidPtr> clients;
    for (int i = 0; i < 30; i++) {
        vector<uint8_t> data(16, i);
        clients.push_back(DuidPtr(new DUID(data)));
    }

    // The default pool is 2001:db8:1::10 to 2001:db8:1::20. There's 17
    // addresses in it. One of them is reserved, so this means that we should
    // get 16 successes and 14 (20-16) failures.
    int success = 0;
    int failure = 0;
    for (int i = 0; i < 30; i++) {
        Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
        AllocEngine::ClientContext6 ctx(subnet_, clients[i], false, false, "",
                                        false, query);
        ctx.currentIA().iaid_ = iaid_;

        findReservation(engine, ctx);
        Lease6Collection leases = engine.allocateLeases6(ctx);
        if (leases.empty()) {
            failure++;
            std::cout << "Alloc for client " << (int)i << " failed." << std::endl;
        } else {
            success++;
            std::cout << "Alloc for client " << (int)i << " succeeded:"
                      << leases[0]->addr_.toText() << std::endl;

            // The assigned addresses must not match the one reserved.
            EXPECT_NE("2001:db8:1::12", leases[0]->addr_.toText());
        }
    }

    EXPECT_EQ(16, success);
    EXPECT_EQ(14, failure);

    // We're now pretty sure that any clients other than the reserved address
    // will not get any service. Now let's check if the client that has the
    // address reserved, will get it (despite the pool being depleted).
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx.currentIA().iaid_ = iaid_;

    findReservation(engine, ctx);
    Lease6Collection leases = engine.allocateLeases6(ctx);
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ("2001:db8:1::12", leases[0]->addr_.toText());
}

// Checks if the allocateLeases throws exceptions for invalid input data.
TEST_F(AllocEngine6Test, allocateLeasesInvalidData) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, true);

    // That looks like a valid context.
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx.currentIA().iaid_ = iaid_;

    Lease6Collection leases;

    // Let's break it!
    ctx.subnet_.reset();

    // Subnet is required for allocation, so we should get no leases.
    EXPECT_NO_THROW(leases = engine.allocateLeases6(ctx));
    EXPECT_TRUE(leases.empty());

    // Let's fix this and break it in a different way.
    ctx.subnet_ = subnet_;
    ctx.duid_.reset();

    // We must know who we're allocating for. No duid = no service.
    EXPECT_NO_THROW(leases = engine.allocateLeases6(ctx));
    EXPECT_TRUE(leases.empty());

}

// Checks whether an address can be renewed (simple case, no reservation tricks)
TEST_F(AllocEngine6Test, addressRenewal) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    // Assigned count should zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    Lease6Collection leases;

    leases = allocateTest(engine, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());

    // Assigned count should be one.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(leases[0]->addr_, 128));

    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // Check that the lease was indeed renewed and hasn't changed
    // (i.e. the same address, preferred and valid lifetimes)

    /// @todo: use leaseCompare, but ignore cltt_
    EXPECT_EQ(leases[0]->addr_, renewed[0]->addr_);
    EXPECT_EQ(leases[0]->type_, renewed[0]->type_);
    EXPECT_EQ(leases[0]->preferred_lft_, renewed[0]->preferred_lft_);
    EXPECT_EQ(leases[0]->valid_lft_, renewed[0]->valid_lft_);

    // Assigned count should still be one.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// Checks whether an address can be renewed (in-pool reservation)
TEST_F(AllocEngine6Test, reservedAddressRenewal) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    // Assigned count should zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    Lease6Collection leases;

    leases = allocateTest(engine, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());
    ASSERT_EQ("2001:db8:1::1c", leases[0]->addr_.toText());

    // Assigned count should be one.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(leases[0]->addr_, 128));

    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());
    ASSERT_EQ("2001:db8:1::1c", leases[0]->addr_.toText());

    // Assigned count should still be one.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
}

// Checks whether a single host can have more than one reservation.
//
/// @todo: as of #3677, this does not work. When processing solicit with two
/// IA_NAs and two reservations, there currently no way to indicate that
/// the first reservation should be used for the first IA and the second
/// reservation for the second IA. This works for Requests and Renews, though.
/// In both of those messages, when processing of the first IA is complete,
/// we have a lease in the database. Based on that, when processing the second
/// IA we can detect that the first reserved address is in use already and
/// use the second reservation.
TEST_F(AllocEngine6Test, DISABLED_reserved2AddressesSolicit) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    // Two addresses are reserved: 2001:db8:1::babe and 2001:db8:1::cafe
    HostPtr host = createHost6(true, IPv6Resrv::TYPE_NA,
                               IOAddress("2001:db8:1::babe"), 128);

    IPv6Resrv resv2(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::cafe"), 128);
    host->addReservation(resv2);
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    AllocEngine::ClientContext6 ctx1(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234)));
    ctx1.currentIA().iaid_ = iaid_;
    ctx1.currentIA().type_ = pool_->getType();

    Lease6Collection leases1;
    findReservation(engine, ctx1);
    EXPECT_NO_THROW(leases1 = engine.allocateLeases6(ctx1));
    ASSERT_EQ(1, leases1.size());
    EXPECT_EQ("2001:db8:1::babe", leases1[0]->addr_.toText());

    // Double check that repeating the same duid/type/iaid will end up with
    // the same address.
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().type_ = pool_->getType();

    Lease6Collection leases2;
    findReservation(engine, ctx2);
    EXPECT_NO_THROW(leases2 = engine.allocateLeases6(ctx2));
    EXPECT_EQ(1, leases2.size());
    EXPECT_EQ("2001:db8:1::babe", leases2[0]->addr_.toText());

    // Ok, now the tricky part. Request allocation for the same duid and type, but
    // different iaid. The second address should be assigned.
    AllocEngine::ClientContext6 ctx3(subnet_, duid_, false, false, "", true,
                                     Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234)));
    ctx3.currentIA().iaid_ = iaid_ + 1;
    ctx3.currentIA().type_ = pool_->getType();

    Lease6Collection leases3;
    findReservation(engine, ctx3);
    EXPECT_NO_THROW(leases3 = engine.allocateLeases6(ctx3));
    ASSERT_EQ(1, leases3.size());
    EXPECT_EQ("2001:db8:1::cafe", leases3[0]->addr_.toText());
}

// Checks whether a single host can have more than one reservation.
TEST_F(AllocEngine6Test, reserved2Addresses) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    // Two addresses are reserved: 2001:db8:1::babe and 2001:db8:1::cafe
    HostPtr host = createHost6(true, IPv6Resrv::TYPE_NA,
                               IOAddress("2001:db8:1::babe"), 128);

    IPv6Resrv resv2(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::cafe"), 128);
    host->addReservation(resv2);
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    AllocEngine::ClientContext6 ctx1(subnet_, duid_, false, false, "", false,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx1.currentIA().iaid_ = iaid_;
    ctx1.currentIA().type_ = pool_->getType();

    Lease6Collection leases1;
    findReservation(engine, ctx1);
    EXPECT_NO_THROW(leases1 = engine.allocateLeases6(ctx1));
    ASSERT_EQ(1, leases1.size());
    EXPECT_EQ("2001:db8:1::babe", leases1[0]->addr_.toText());

    // Double check that repeating the same duid/type/iaid will end up with
    // the same address.
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", false,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.currentIA().type_ = pool_->getType();

    Lease6Collection leases2;
    findReservation(engine, ctx2);
    EXPECT_NO_THROW(leases2 = engine.allocateLeases6(ctx2));
    EXPECT_EQ(1, leases2.size());
    EXPECT_EQ("2001:db8:1::babe", leases2[0]->addr_.toText());

    // Ok, now the tricky part. Request allocation for the same duid and type, but
    // different iaid. The second address should be assigned.
    AllocEngine::ClientContext6 ctx3(subnet_, duid_, false, false, "", false,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ctx3.currentIA().iaid_ = iaid_ + 1;
    ctx3.currentIA().type_ = pool_->getType();

    Lease6Collection leases3;
    findReservation(engine, ctx3);
    EXPECT_NO_THROW(leases3 = engine.allocateLeases6(ctx3));
    ASSERT_EQ(1, leases3.size());
    EXPECT_EQ("2001:db8:1::cafe", leases3[0]->addr_.toText());
}

// Checks whether address can change during renew (if there is a new
// reservation for this client)
TEST_F(AllocEngine6Test, reservedAddressRenewChange) {

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    Lease6Collection leases;

    leases = allocateTest(engine, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());
    ASSERT_NE("2001:db8:1::1c", leases[0]->addr_.toText());

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(leases[0]->addr_, 128));

    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());
    ASSERT_EQ("2001:db8:1::1c", renewed[0]->addr_.toText());
}

// Checks whether address can change during renew (if there is a new
// reservation for this address for another client)
TEST_F(AllocEngine6Test, reservedAddressRenewReserved) {

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    Lease6Collection leases;

    leases = allocateTest(engine, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(leases[0]->addr_, 128));

    // Create reservation for this address, but for another client.
    // This is in-pool reservation, as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    HostPtr host = createHost6(false, IPv6Resrv::TYPE_NA, leases[0]->addr_, 128);

    // We need to tweak reservation id: use a different DUID for client Y
    vector<uint8_t> other_duid(8, 0x45);
    host->setIdentifier(&other_duid[0], other_duid.size(), Host::IDENT_DUID);
    // Ok, now add it to the HostMgr
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // Check that we no longer have the reserved address.
    ASSERT_NE(leases[0]->addr_.toText(), renewed[0]->addr_.toText());

    // Check that the lease for the now reserved address is no longer in
    // the lease database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               leases[0]->addr_);
    EXPECT_FALSE(from_mgr);
}

/// @todo: The following methods are tested indirectly by allocateLeases6()
/// tests, but could use more direct testing:
/// - AllocEngine::allocateUnreservedLeases6
/// - AllocEngine::allocateReservedLeases6
/// - AllocEngine::removeNonmatchingReservedLeases6
/// - AllocEngine::removeLeases
/// - AllocEngine::removeNonreservedLeases6

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends SOLICIT without any hints.
// - Client is allocated a reserved address.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressByMacInPoolSolicitNoHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6HWAddr(true, IPv6Resrv::TYPE_NA, hwaddr_,
                      IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), true);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends REQUEST without any hints.
// - Client is allocated a reserved address.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressByMacInPoolRequestNoHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6HWAddr(true, IPv6Resrv::TYPE_NA, hwaddr_,
                      IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
}


// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends SOLICIT with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client can, but don't have to send any hints in its
// Solicit message.
TEST_F(AllocEngine6Test, reservedAddressByMacInPoolSolicitValidHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6HWAddr(true, IPv6Resrv::TYPE_NA, hwaddr_,
                      IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), true);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
}

// Checks that a client gets the address reserved (in-pool case)
// This test checks the behavior of the allocation engine in the following
// scenario:
// - Client has no lease in the database.
// - Client has an in-pool reservation.
// - Client sends REQUEST with a hint that does not match reservation
// - Client is allocated a reserved address, not the hint.
//
// Note that DHCPv6 client must send an address in REQUEST that the server
// offered in Advertise. Nevertheless, the client may ignore this requirement.
TEST_F(AllocEngine6Test, reservedAddressByMacInPoolRequestValidHint) {
    // Create reservation for the client This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6HWAddr(true, IPv6Resrv::TYPE_NA, hwaddr_,
                      IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
}

// This test checks that the allocation engine can delegate the long prefix.
// The pool with prefix of 64 and with long delegated prefix has a very
// high capacity. The number of attempts that the allocation engine makes
// to allocate the prefix for high capacity pools is equal to the capacity
// value. This test verifies that the prefix can be allocated in that
// case.
TEST_F(AllocEngine6Test, largePDPool) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0);

    // Remove the default PD pool.
    subnet_->delPools(Lease::TYPE_PD);

    // Configure the PD pool with the prefix length of /64 and the delegated
    // length /96.
    Pool6Ptr pool(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:2::"), 80, 96));
    subnet_->addPool(pool);

    // We should have got exactly one lease.
    Lease6Collection leases = allocateTest(engine, pool, IOAddress("::"),
                                           false, true);
    ASSERT_EQ(1, leases.size());
}

// This test checks that the allocation engine can delegate addresses
// from ridiculously large pool. The configuration provides 2^80 or
// 1208925819614629174706176 addresses. We used to have a bug that would
// confuse the allocation engine if the number of available addresses
// was larger than 2^32.
TEST_F(AllocEngine6Test, largePoolOver32bits) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 0);

    // Configure 2001:db8::/32 subnet
    subnet_.reset(new Subnet6(IOAddress("2001:db8::"), 32, 1, 2, 3, 4));

    // Configure the NA pool of /48. So there are 2^80 addresses there. Make
    // sure that we still can handle cases where number of available addresses
    // is over max_uint64
    Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 48));
    subnet_->addPool(pool);

    // We should have got exactly one lease.
    Lease6Collection leases = allocateTest(engine, pool, IOAddress("::"),
                                           false, true);
    ASSERT_EQ(1, leases.size());
}

// This test verifies that it is possible to override the number of allocation
// attempts made by the allocation engine for a single lease.
TEST_F(AllocEngine6Test, largeAllocationAttemptsOverride) {
    // Remove the default NA pools.
    subnet_->delPools(Lease::TYPE_NA);
    subnet_->delPools(Lease::TYPE_PD);

    // Add exactly one pool with many addresses.
    Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 56));
    subnet_->addPool(pool);

    // Allocate 5 addresses from the pool configured.
    for (int i = 0; i < 5; ++i) {
        DuidPtr duid = DuidPtr(new DUID(vector<uint8_t>(12,
                                                        static_cast<uint8_t>(i))));
        // Get the unique IAID.
        const uint32_t iaid = 3568 + i;

        // Construct the unique address from the pool.
        std::ostringstream address;
        address << "2001:db8:1::";
        address << i;

        // Allocate the lease.
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress(address.str()),
                                   duid, iaid, 501, 502, subnet_->getID(),
                                   HWAddrPtr(), 0));
        ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));
    }

    // Try to use the allocation engine to allocate the lease. The iterative
    // allocator will pick the addresses already allocated until it finds the
    // available address. Since, we have restricted the number of attempts the
    // allocation should fail.
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 3);
    Lease6Collection leases = allocateTest(engine, pool_, IOAddress("::"),
                                           false, true);
    ASSERT_EQ(0, leases.size());

    // This time, lets allow more attempts, and expect that the allocation will
    // be successful.
    AllocEngine engine2(AllocEngine::ALLOC_ITERATIVE, 6);
    leases = allocateTest(engine2, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());
}

// This test checks if an expired declined lease can be reused in SOLICIT (fake allocation)
TEST_F(AllocEngine6Test, solicitReuseDeclinedLease6) {

    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    // Create one subnet with a pool holding one address.
    string addr_txt("2001:db8:1::ad");
    IOAddress addr(addr_txt);
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);

    // Use information that is different than what we'll request
    Lease6Ptr declined = generateDeclinedLease(addr_txt, 100, -10);
    ASSERT_TRUE(declined->expired());

    // CASE 1: Asking for any address
    Lease6Ptr assigned;
    testReuseLease6(engine, declined, "::", true, SHOULD_PASS, assigned);

    // Check that we got that single lease
    ASSERT_TRUE(assigned);
    EXPECT_EQ(addr, assigned->addr_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(duid_, assigned, Lease::TYPE_NA, 128);

    // CASE 2: Asking specifically for this address
    testReuseLease6(engine, declined, addr_txt, true, SHOULD_PASS, assigned);

    // Check that we got that single lease
    ASSERT_TRUE(assigned);
    EXPECT_EQ(addr, assigned->addr_);
}

// This test checks if an expired declined lease can be reused when responding
// to REQUEST (actual allocation)
TEST_F(AllocEngine6Test, requestReuseDeclinedLease6) {

    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100, true));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    string addr_txt("2001:db8::7");
    IOAddress addr(addr_txt);
    initSubnet(IOAddress("2001:db8::"), addr, addr);

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease6Ptr declined = generateDeclinedLease(addr_txt, 100, -10);

    // Asking specifically for this address
    Lease6Ptr assigned;
    testReuseLease6(engine, declined, addr_txt, false, SHOULD_PASS, assigned);
    // Check that we got it.
    ASSERT_TRUE(assigned);
    EXPECT_EQ(addr, assigned->addr_);

    // Check that the lease is indeed updated in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(assigned, from_mgr);
}

// This test checks if statistics are not updated when expired declined lease
// is reused when responding to SOLICIT (fake allocation)
TEST_F(AllocEngine6Test, solicitReuseDeclinedLease6Stats) {

    // Now prepare for SOLICIT processing
    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                          100, true));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    string addr_txt("2001:db8:1::1");
    IOAddress addr(addr_txt);
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);

    // Stats should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("declined-addresses", 0));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0));
    EXPECT_TRUE(testStatistics("declined-addresses", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease6Ptr declined = generateDeclinedLease(addr_txt, 100, -10);

    // Ask for any address. There's only one address in the pool, so it doesn't
    // matter much.
    Lease6Ptr assigned;
    testReuseLease6(engine, declined, "::", true, SHOULD_PASS, assigned);

    // Check that the stats were not modified
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_EQ(cumulative,
              getStatistics("cumulative-assigned-nas", subnet_->getID()));
    EXPECT_EQ(glbl_cumulative, getStatistics("cumulative-assigned-nas"));
    EXPECT_TRUE(testStatistics("declined-addresses", 0));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0));
    EXPECT_TRUE(testStatistics("declined-addresses", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0, subnet_->getID()));
}

// This test checks if statistics are updated when expired declined lease
// is reused when responding to REQUEST (actual allocation)
TEST_F(AllocEngine6Test, requestReuseDeclinedLease6Stats) {

    // Prepare for REQUEST processing.
    AllocEnginePtr engine(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                          100, true));
    ASSERT_TRUE(engine);

    // Now prepare a configuration with single address pool.
    string addr_txt("2001:db8::1");
    IOAddress addr(addr_txt);
    initSubnet(IOAddress("2001:db8::"), addr, addr);

    // Stats should be zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("declined-addresses", 0));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0));
    EXPECT_TRUE(testStatistics("declined-addresses", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Now create a declined lease, decline it and rewind its cltt, so it
    // is expired.
    Lease6Ptr declined = generateDeclinedLease(addr_txt, 100, -10);

    // Ask for any address. There's only one address in the pool, so it doesn't
    // matter much.
    Lease6Ptr assigned;
    testReuseLease6(engine, declined, "::", false, SHOULD_PASS, assigned);

    // Check that the stats were modified as expected.
    // assigned-nas should NOT get incremented. Currently we do not adjust assigned
    // counts when we declines
    // declined-addresses will -1, as the artificial creation of declined lease
    // doesn't increment it from zero.  reclaimed-declined-addresses will be 1
    // because the leases are implicitly reclaimed before they can be assigned.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
    EXPECT_TRUE(testStatistics("declined-addresses", -1));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 1));
    EXPECT_TRUE(testStatistics("declined-addresses", -1, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-declined-addresses", 1, subnet_->getID()));

}

// This test checks if an expired-reclaimed lease can be reused by
// a returning client via REQUEST, rather than renew/rebind.  This
// would be typical of cable modem clients which do not retain lease
// data across reboots.
TEST_F(AllocEngine6Test, reuseReclaimedExpiredViaRequest) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.clear(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.getStagingCfg()->getCfgSubnets6()->add(subnet_);
    cfg_mgr.commit();

    // Verify relevant stats are zero.
    EXPECT_TRUE(testStatistics("assigned-nas", 0, subnet_->getID()));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0, subnet_->getID()));

    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Let's create an expired lease
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               501, 502, subnet_->getID(), HWAddrPtr(),
                               0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    lease->fqdn_fwd_ = true;
    lease->fqdn_rev_ = true;
    lease->hostname_ = "myhost.example.com.";
    lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Verify that the lease state is indeed expired-reclaimed
    EXPECT_EQ(lease->state_, Lease::STATE_EXPIRED_RECLAIMED);

    // Same client comes along and issues a request
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that he got the original lease back.
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Check that the lease is indeed updated in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // Verify that the lease state has been set back to the default.
    EXPECT_EQ(lease->state_, Lease::STATE_DEFAULT);

    // Verify assigned-nas got bumped.  Reclaimed stats should still
    // be zero as we artificially marked it reclaimed.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0));
    EXPECT_TRUE(testStatistics("reclaimed-leases", 0, subnet_->getID()));
}

/// @brief This test class is dedicated to testing shared networks
///
/// It uses one common configuration:
/// 1 shared network with 2 subnets:
///   - 2001:db8:1::/56 subnet with a small pool of single address
///   - 2001:db8:1::/56 subnet with pool with 64K addresses.
class SharedNetworkAlloc6Test : public AllocEngine6Test {
public:
    SharedNetworkAlloc6Test()
        :engine_(AllocEngine::ALLOC_ITERATIVE, 0) {

        subnet1_.reset(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
        subnet2_.reset(new Subnet6(IOAddress("2001:db8:2::"), 56, 1, 2, 3, 4));
        pool1_.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                               IOAddress("2001:db8:1::1")));
        pool2_.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:2::"),
                               IOAddress("2001:db8:2::FF")));
        subnet1_->addPool(pool1_);
        subnet2_->addPool(pool2_);

        // Both subnets belong to the same network so they can be used
        // interchangeably.
        network_.reset(new SharedNetwork6("test_network"));
        network_->add(subnet1_);
        network_->add(subnet2_);
    }

    Lease6Ptr
    insertLease(std::string addr, SubnetID subnet_id) {
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress(addr), duid_, iaid_,
                                   501, 502, subnet_->getID(),
                                   HWAddrPtr(), 0));
        lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
        if (!LeaseMgrFactory::instance().addLease(lease)) {
            ADD_FAILURE() << "Failed to add a lease for address " << addr
                          << " in subnet with subnet-id " << subnet_id;
            return (Lease6Ptr());
        }
        return (lease);
    }

    /// Convenience pointers to configuration elements. These are initialized
    /// in the constructor and are used throughout the tests.
    AllocEngine engine_;
    Subnet6Ptr subnet1_;
    Subnet6Ptr subnet2_;
    Pool6Ptr pool1_;
    Pool6Ptr pool2_;
    SharedNetwork6Ptr network_;
};

// This test verifies that the server can offer an address from a
// subnet and the introduction of shared network doesn't break anything here.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkSimple) {

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_TRUE(subnet1_->inRange(lease->addr_));
}


// This test verifies that the server can pick a subnet from shared subnets
// based on hints.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkHint) {

    // Create context which will be used to try to allocate leases from the
    // shared network. There's a hint that points to the subnet2. The
    // shared network mechanism should be able to pick the second subnet
    // based on it.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(IOAddress("2001:db8:2::12"));

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);

    // The second subnet should be selected.
    ASSERT_TRUE(subnet2_->inRange(lease->addr_));
}

// This test verifies that the client is offerred an address from an
// alternative subnet within shared network when the address pool is
// exhausted in the first address pool.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkOutOfAddresses) {

    // Create a lease for a single address in the first address pool. The
    // pool is now exhausted.
    DuidPtr other_duid(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                               other_duid, other_iaid, 501, 502,
                               subnet1_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet1, which address space
    // is exhausted. We expect the allocation engine to find another subnet
    // within the same shared network and offer an address from there.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    Lease6Ptr lease2;
    ASSERT_NO_THROW(lease2 = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease2);
    ASSERT_TRUE(subnet2_->inRange(lease2->addr_));

    // The client having a lease should be offerred this lease, even if
    // the client starts allocation from the second subnet. The code should
    // determine that the client has a lease in subnet1 and use this subnet
    // instead.
    AllocEngine::ClientContext6 ctx2(subnet2_, other_duid, false, false, "",
                                     true, query);
    ctx2.currentIA().iaid_ = other_iaid;
    ASSERT_NO_THROW(lease2 = expectOneLease(engine_.allocateLeases6(ctx2)));
    ASSERT_TRUE(lease2);
    ASSERT_EQ("2001:db8:1::1", lease2->addr_.toText());

    // Delete the lease in the first subnet.
    ASSERT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Now, try requesting this address by providing a hint. The engine
    // should try to honor the hint even though we start from the subnet2.
    ctx.subnet_ = subnet2_;
    ctx.currentIA().addHint(IOAddress("2001:db8:1::1"));
    ASSERT_NO_THROW(lease2 = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease2);
    ASSERT_TRUE(subnet1_->inRange(lease2->addr_));
}

// This test verifies that the server can offer an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet is exhausted.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkClassification) {
    // Try to offer address from subnet1. There is an address available so
    // it should be offerred.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_TRUE(subnet1_->inRange(lease->addr_));

    // Apply restrictions on the subnet1. This should be only assigned
    // to clients belonging to cable-modem class.
    subnet1_->allowClientClass("cable-modem");

    // The allocation engine should determine that the subnet1 is not
    // available for the client not belonging to the cable-modem class.
    // Instead, it should offer an address from subnet2 that belongs
    // to the same shared network.
    AllocEngine::ClientContext6 ctx2(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.query_ = query;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx2)));
    ASSERT_TRUE(lease);
    ASSERT_TRUE(subnet2_->inRange(lease->addr_));

    AllocEngine::ClientContext6 ctx3(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx3.currentIA().iaid_ = iaid_;
    ctx3.query_ = query;

    // Create host reservation in the first subnet for this client. The
    // allocation engine should not assign reserved address to the client
    // because client classification doesn't allow that.
    subnet_ = subnet1_;
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1"), 128);
    AllocEngine::findReservation(ctx3);
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_TRUE(subnet2_->inRange(lease->addr_));

    AllocEngine::ClientContext6 ctx4(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx4.currentIA().iaid_ = iaid_;
    ctx4.query_ = query;

    // Assign cable-modem class and try again. This time, we should
    // offer an address from the subnet1_.
    ctx4.query_->addClass(ClientClass("cable-modem"));

    AllocEngine::findReservation(ctx4);
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx4)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1", lease->addr_.toText());
}

// This test verifies that the server can offer an address from a
// different subnet than orginally selected, when the address pool in
// the first subnet requires another class.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkPoolClassification) {
    // Try to offer address from subnet1. There is an address available so
    // it should be offerred.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_TRUE(subnet1_->inRange(lease->addr_));

    // Apply restrictions on the pool1. This should be only assigned
    // to clients belonging to cable-modem class.
    pool1_->allowClientClass("cable-modem");

    // The allocation engine should determine that the pool1 is not
    // available for the client not belonging to the cable-modem class.
    // Instead, it should offer an address from subnet2 that belongs
    // to the same shared network.
    AllocEngine::ClientContext6 ctx2(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx2.currentIA().iaid_ = iaid_;
    ctx2.query_ = query;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx2)));
    ASSERT_TRUE(lease);
    ASSERT_TRUE(subnet2_->inRange(lease->addr_));

    AllocEngine::ClientContext6 ctx3(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx3.currentIA().iaid_ = iaid_;
    ctx3.query_ = query;

    AllocEngine::ClientContext6 ctx4(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx4.currentIA().iaid_ = iaid_;
    ctx4.query_ = query;

    // Assign cable-modem class and try again. This time, we should
    // offer an address from the pool1_.
    ctx4.query_->addClass(ClientClass("cable-modem"));

    // Restrict access to pool2 for this client, to make sure that the
    // server doesn't accidentally get a lease from this pool.
    pool2_->allowClientClass("telephone");

    AllocEngine::findReservation(ctx4);
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx4)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1", lease->addr_.toText());
}

// This test verifies that the client is offerred a reserved address
// even if this address belongs to another subnet within the same
// shared network.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkReservations) {
    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());

    // Create reservation for the client in the second subnet.
    subnet_ = subnet2_;
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:2::15"), 128);

    // Start allocation from subnet1_. The engine should determine that the
    // client has reservations in subnet2_ and should rather assign reserved
    // addresses.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    // Find reservations for this subnet/shared network.
    AllocEngine::findReservation(ctx);

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_EQ("2001:db8:2::15", lease->addr_.toText());
}

// This test verifies that the client is offerred a reserved address
// even if this address belongs to another subnet within the same
// shared network. Host lookups returning a collection are disabled.
// As it is only an optimization the behavior (so the test) must stay
// unchanged.
TEST_F(SharedNetworkAlloc6Test, solicitSharedNetworkReservationsNoColl) {
    // Disable host lookups returning a collection.
    ASSERT_FALSE(HostMgr::instance().getDisableSingleQuery());
    HostMgr::instance().setDisableSingleQuery(true);

    // Create reservation for the client in the second subnet.
    subnet_ = subnet2_;
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:2::15"), 128);

    // Start allocation from subnet1_. The engine should determine that the
    // client has reservations in subnet2_ and should rather assign reserved
    // addresses.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    // Find reservations for this subnet/shared network.
    AllocEngine::findReservation(ctx);

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_EQ("2001:db8:2::15", lease->addr_.toText());
}

// This test verifies that the client is allocated a reserved address
// even if this address belongs to another subnet within the same
// shared network.
TEST_F(SharedNetworkAlloc6Test, requestSharedNetworkReservations) {
    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());

    // Create reservation for the client in the second subnet.
    subnet_ = subnet2_;
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:2::15"), 128);

    // Start allocation from subnet1_. The engine should determine that the
    // client has reservations in subnet2_ and should rather assign reserved
    // addresses.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    // Find reservations for this subnet/shared network.
    AllocEngine::findReservation(ctx);

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_EQ("2001:db8:2::15", lease->addr_.toText());
}

// This test verifies that the client is allocated a reserved address
// even if this address belongs to another subnet within the same
// shared network. Host lookups returning a collection are disabled.
// As it is only an optimization the behavior (so the test) must stay
// unchanged.
TEST_F(SharedNetworkAlloc6Test, requestSharedNetworkReservationsNoColl) {
    // Disable host lookups returning a collection.
    ASSERT_FALSE(HostMgr::instance().getDisableSingleQuery());
    HostMgr::instance().setDisableSingleQuery(true);

    // Create reservation for the client in the second subnet.
    subnet_ = subnet2_;
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:2::15"), 128);

    // Start allocation from subnet1_. The engine should determine that the
    // client has reservations in subnet2_ and should rather assign reserved
    // addresses.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    // Find reservations for this subnet/shared network.
    AllocEngine::findReservation(ctx);

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    ASSERT_EQ("2001:db8:2::15", lease->addr_.toText());
}

// This test verifies that client is assigned an existing lease from a
// shared network, regardless of the default subnet. It also verifies that
// the client is assigned a reserved address from a shared network which
// replaces existing lease within this shared network.
TEST_F(SharedNetworkAlloc6Test, requestSharedNetworkExistingLeases) {
    // Get the cumulative count of assigned addresses.
    int64_t cumulative = getStatistics("cumulative-assigned-nas",
                                       subnet2_->getID());
    int64_t glbl_cumulative = getStatistics("cumulative-assigned-nas");

    // Create a lease in subnet 2 for this client. The lease is in expired
    // reclaimed state initially to allow for checking whether the lease
    // gets renewed.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1"),
                               duid_, iaid_, 501, 502,
                               subnet2_->getID(), HWAddrPtr(), 128));
    lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet 1 initially, but the
    // allocation engine should determine that there are existing leases
    // in subnet 2 and renew those.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet1_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;

    // Check that we have been allocated the existing lease.
    Lease6Ptr lease2;
    ASSERT_NO_THROW(lease2 = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease2);
    EXPECT_EQ("2001:db8:2::1", lease2->addr_.toText());

    // Statistics should be bumped when the lease is re-assigned.
    EXPECT_TRUE(testStatistics("assigned-nas", 1, subnet2_->getID()));
    cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas",
                               cumulative, subnet2_->getID()));
    glbl_cumulative += 1;
    EXPECT_TRUE(testStatistics("cumulative-assigned-nas", glbl_cumulative));

    // Another interesting case is when there is a reservation in a different
    // subnet than the one from which the ease has been assigned.
    subnet_ = subnet1_;
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1"), 128);

    // The reserved lease should take precedence.
    ctx.subnet_ = subnet1_;
    ctx.currentIA().iaid_ = iaid_;
    AllocEngine::findReservation(ctx);
    ASSERT_NO_THROW(lease2 = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease2);
    EXPECT_EQ("2001:db8:1::1", lease2->addr_.toText());

    // The previous lease should have been removed.
    ASSERT_EQ(1, ctx.currentIA().old_leases_.size());
    EXPECT_EQ("2001:db8:2::1", ctx.currentIA().old_leases_[0]->addr_.toText());
}

// This test verifies that the server can offer an address from a shared
// subnet if there's at least 1 address left there, but will not offer
// anything if both subnets are completely full.
TEST_F(SharedNetworkAlloc6Test, requestRunningOut) {

    // Allocate everything in subnet1
    insertLease("2001:db8:1::1", subnet1_->getID());

    // Allocate everything, except one address in subnet2.
    for (int i = 0; i < 255; i++) {
        stringstream tmp;
        tmp << "2001:db8:2::" << hex << i;
        insertLease(tmp.str(), subnet2_->getID());
    }

    // Create context which will be used to try to allocate leases from the
    // shared network. The context points to subnet 1 initially, but the
    // allocation engine should determine that there are existing leases
    // in subnet 2 and renew those.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx1(subnet1_, duid_, false, false, "", false,
                                    query);
    ctx1.currentIA().iaid_ = iaid_;

    // Check that we have been allocated the existing lease (there's only
    // one lease left, so we know exactly which one will be given out.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx1)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:2::ff", lease->addr_.toText());

    // Ok, now try for another client. We should be completely full.
    DuidPtr other_duid(new DUID(vector<uint8_t>(12, 0xff)));
    AllocEngine::ClientContext6 ctx2(subnet2_, other_duid, false, false, "", false,
                                    query);
    Lease6Collection leases = engine_.allocateLeases6(ctx2);

    // Bugger off, we're full!
    EXPECT_TRUE(leases.empty());
}

// Verifies that client with a hostname reservation can
// 1. Get a dynamic lease
// 2. Renew the same lease via REQUEST (calls allocateLease6)
// 3. Renew the same lease via RENEW/REBIND (calls renewLeases6)
// renew a dynamic lease from their selected subnet.
TEST_F(AllocEngine6Test, hostDynamicAddress) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, subnet_->getID(),
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("host1");

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsInSubnet(true);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);

    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("host1", current->getHostname());

    // Check that we have been allocated a dynamic address.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::10", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    ASSERT_NO_FATAL_FAILURE(rollbackPersistedCltt(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::10"), 128));

    // Set test fixture hostname_ to the expected value. This gets checked in
    // renewTest.
    hostname_ = "host1";

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    Lease6Ptr renewed_lease = renewed[0];
    EXPECT_EQ("2001:db8:1::10", renewed_lease->addr_.toText());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed_lease->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";

    // Now let's verify that if the client returns via SARR, they get the same
    // lease and the cltt gets extended.

    // First, we're going to rollback the clock again so we can verify the
    // allocation updates the expiry.
    ASSERT_NO_FATAL_FAILURE(rollbackPersistedCltt(renewed_lease));

    // Create a new context which will be used to try to allocate leases
    query.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", false, query);
    ctx2.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx2);

    // Make sure we found our host.
    current = ctx2.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("host1", current->getHostname());

    // Check that we have been allocated the original dynamic address.
    Lease6Ptr lease2;
    ASSERT_NO_THROW(lease2 = expectOneLease(engine->allocateLeases6(ctx2)));
    ASSERT_TRUE(lease2);
    EXPECT_EQ("2001:db8:1::10", lease2->addr_.toText());

    // And the lease lifetime should be extended.
    EXPECT_GT(lease2->cltt_, renewed_lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a global hostname reservation can:
// 1. Get a dynamic lease
// 2. Renew the same lease via REQUEST (calls allocateLease6)
// 3. Renew the same lease via RENEW/REBIND (calls renewLeases6)
TEST_F(AllocEngine6Test, globalHostDynamicAddress) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, SUBNET_ID_GLOBAL,
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("ghost1");

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("ghost1", current->getHostname());

    // Check that we have been allocated a dynamic address.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::10", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    ASSERT_NO_FATAL_FAILURE(rollbackPersistedCltt(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::10"), 128));

    // Set test fixture hostname_ to the expected value. This gets checked in
    // renewTest.
    hostname_ = "ghost1";

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    ASSERT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";

    // Now let's verify that if the client returns via SARR, they get the same
    // lease. Create a new context which will be used to try to allocate leases

    // First, we're going to rollback the clock again so we can verify the
    // allocation updates the expiry.
    Lease6Ptr renewed_lease = renewed[0];
    ASSERT_NO_FATAL_FAILURE(rollbackPersistedCltt(renewed_lease));

    query.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, false, false, "", false, query);
    ctx2.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx2);

    // Make sure we found our host.
    current = ctx2.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("ghost1", current->getHostname());

    // Check that we have been allocated a dynamic address.
    Lease6Ptr lease2;
    ASSERT_NO_THROW(lease2 = expectOneLease(engine->allocateLeases6(ctx2)));
    ASSERT_TRUE(lease2);
    EXPECT_EQ("2001:db8:1::10", lease2->addr_.toText());

    // And the lease lifetime should be extended.
    EXPECT_GT(lease2->cltt_, renewed_lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a global address reservation can get and
// renew a lease for an arbitrary address.
TEST_F(AllocEngine6Test, globalHostReservedAddress) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, SUBNET_ID_GLOBAL,
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("ghost1");
    IPv6Resrv resv(IPv6Resrv::TYPE_NA, asiolink::IOAddress("3001::1"), 128);
    host->addReservation(resv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("ghost1", current->getHostname());

    // Check that we have been allocated the fixed address.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("3001::1", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    --lease->cltt_;
    EXPECT_NO_THROW(LeaseMgrFactory::instance().updateLease6(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("3001::1"), 128));

    // Set test fixture hostname_ to the expected value. This gets checked in
    // renewTest.
    hostname_ = "ghost1";

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, pool_, hints, false);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a global prefix reservation can get and
// renew a lease for an arbitrary prefix.
TEST_F(AllocEngine6Test, globalHostReservedPrefix) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, SUBNET_ID_GLOBAL,
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("ghost1");
    IPv6Resrv resv(IPv6Resrv::TYPE_PD, asiolink::IOAddress("3001::"), 64);
    host->addReservation(resv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("ghost1", current->getHostname());

    // Check that we have been allocated the fixed address.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("3001::", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    --lease->cltt_;
    EXPECT_NO_THROW(LeaseMgrFactory::instance().updateLease6(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("3001::"), 64));

    // Set test fixture hostname_ to the expected value. This gets checked via
    // renewTest.
    hostname_ = "ghost1";

    // We need a PD pool to fake renew_test
    Pool6Ptr dummy_pool(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 64, 64));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, dummy_pool, hints, false);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a subnet address reservation can get and
// renew a lease for an address in the subnet.
TEST_F(AllocEngine6Test, mixedHostReservedAddress) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, subnet_->getID(),
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("mhost1");
    IPv6Resrv resv(IPv6Resrv::TYPE_NA, asiolink::IOAddress("2001:db8:1::1c"), 128);
    host->addReservation(resv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);
    subnet_->setReservationsOutOfPool(false);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("mhost1", current->getHostname());

    // Check that we have been allocated the fixed address.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    --lease->cltt_;
    EXPECT_NO_THROW(LeaseMgrFactory::instance().updateLease6(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::1c"), 128));

    // Set test fixture hostname_ to the expected value. This gets checked in
    // renewTest.
    hostname_ = "mhost1";

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a subnet prefix reservation can get and
// renew a lease for a prefix in the subnet.
TEST_F(AllocEngine6Test, mixedHostReservedPrefix) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, subnet_->getID(),
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("mhost1");
    IPv6Resrv resv(IPv6Resrv::TYPE_PD, asiolink::IOAddress("2001:db8:1:2::"), 64);
    host->addReservation(resv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("mhost1", current->getHostname());

    // Check that we have been allocated the fixed prefix.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:2::", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    --lease->cltt_;
    EXPECT_NO_THROW(LeaseMgrFactory::instance().updateLease6(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1:2::"), 64));

    // Set test fixture hostname_ to the expected value. This gets checked via
    // renewTest.
    hostname_ = "mhost1";

    // We need a PD pool to fake renew_test
    Pool6Ptr dummy_pool(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 64, 64));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, dummy_pool, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a subnet and a global address reservation
// can get and renew a lease for an address in the subnet.
TEST_F(AllocEngine6Test, bothHostReservedAddress) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr ghost(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                           Host::IDENT_DUID, SUBNET_ID_UNUSED, SUBNET_ID_GLOBAL,
                           asiolink::IOAddress("0.0.0.0")));
    ghost->setHostname("ghost1");
    IPv6Resrv gresv(IPv6Resrv::TYPE_NA, asiolink::IOAddress("3001::1"), 128);
    ghost->addReservation(gresv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(ghost);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, subnet_->getID(),
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("mhost1");
    IPv6Resrv resv(IPv6Resrv::TYPE_NA, asiolink::IOAddress("2001:db8:1::1c"), 128);
    host->addReservation(resv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);
    subnet_->setReservationsOutOfPool(false);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("mhost1", current->getHostname());

    // Check that we have been allocated the fixed address.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    --lease->cltt_;
    EXPECT_NO_THROW(LeaseMgrFactory::instance().updateLease6(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1::1c"), 128));

    // Set test fixture hostname_ to the expected value. This gets checked in
    // renewTest.
    hostname_ = "mhost1";

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

// Verifies that client with a subnet and a global prefix reservation
// can get and renew a lease for a prefix in the subnet.
TEST_F(AllocEngine6Test, bothHostReservedPrefix) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    HostPtr ghost(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                           Host::IDENT_DUID, SUBNET_ID_UNUSED, SUBNET_ID_GLOBAL,
                           asiolink::IOAddress("0.0.0.0")));
    ghost->setHostname("ghost1");
    IPv6Resrv gresv(IPv6Resrv::TYPE_PD, asiolink::IOAddress("3001::"), 64);
    ghost->addReservation(gresv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(ghost);

    HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                          Host::IDENT_DUID, SUBNET_ID_UNUSED, subnet_->getID(),
                          asiolink::IOAddress("0.0.0.0")));
    host->setHostname("mhost1");
    IPv6Resrv resv(IPv6Resrv::TYPE_PD, asiolink::IOAddress("2001:db8:1:2::"), 64);
    host->addReservation(resv);

    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    subnet_->setReservationsGlobal(true);
    subnet_->setReservationsInSubnet(true);

    // Create context which will be used to try to allocate leases
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false, query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;

    // Look up the reservation.
    findReservation(*engine, ctx);
    // Make sure we found our host.
    ConstHostPtr current = ctx.currentHost();
    ASSERT_TRUE(current);
    ASSERT_EQ("mhost1", current->getHostname());

    // Check that we have been allocated the fixed prefix.
    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:2::", lease->addr_.toText());

    // We're going to rollback the clock a little so we can verify a renewal.
    --lease->cltt_;
    EXPECT_NO_THROW(LeaseMgrFactory::instance().updateLease6(lease));

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(AllocEngine::Resource(IOAddress("2001:db8:1:2::"), 64));

    // Set test fixture hostname_ to the expected value. This gets checked via
    // renewTest.
    hostname_ = "mhost1";

    // We need a PD pool to fake renew_test
    Pool6Ptr dummy_pool(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 64, 64));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(*engine, dummy_pool, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease->cltt_)
        << "Lease lifetime was not extended, but it should";
}

/// @brief Test fixture class for testing storage of extended lease data.
/// It primarily creates several configuration items common to the
/// extended info tests.
class AllocEngine6ExtendedInfoTest : public AllocEngine6Test {
public:
    /// @brief Constructor
    AllocEngine6ExtendedInfoTest()
        : engine_(AllocEngine::ALLOC_ITERATIVE, 100, true), duid1_(), duid2_(),
          relay1_(), relay2_(), duid1_addr_("::"), duid2_addr_("::") {
        duid1_.reset(new DUID(std::vector<uint8_t>(8, 0x84)));
        duid2_.reset(new DUID(std::vector<uint8_t>(8, 0x74)));

        relay1_.msg_type_ = DHCPV6_RELAY_FORW;
        relay1_.hop_count_ = 33;
        relay1_.linkaddr_ = IOAddress("2001:db8::1");
        relay1_.peeraddr_ = IOAddress("2001:db8::2");
        relay1_.relay_msg_len_ = 0;

        uint8_t relay_opt_data[] = { 1, 2, 3, 4, 5, 6, 7, 8};
        vector<uint8_t> relay_data(relay_opt_data,
                                   relay_opt_data + sizeof(relay_opt_data));
        OptionPtr optRelay1(new Option(Option::V6, 200, relay_data));

        relay1_.options_.insert(make_pair(optRelay1->getType(), optRelay1));

        relay2_.msg_type_ = DHCPV6_RELAY_FORW;
        relay2_.hop_count_ = 77;
        relay2_.linkaddr_ = IOAddress("2001:db8::3");
        relay2_.peeraddr_ = IOAddress("2001:db8::4");
        relay2_.relay_msg_len_ = 0;

        duid1_addr_ = IOAddress("2001:db8:1::10");
        duid2_addr_ = IOAddress("2001:db8:1::11");

        // Create the allocation engine, context and lease.
        NakedAllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, true);
    }

    /// @brief Destructor
    virtual ~AllocEngine6ExtendedInfoTest(){};

    /// Configuration elements. These are initialized in the constructor
    /// and are used throughout the tests.
    NakedAllocEngine engine_;
    DuidPtr duid1_;
    DuidPtr duid2_;
    Pkt6::RelayInfo relay1_;
    Pkt6::RelayInfo relay2_;
    IOAddress duid1_addr_;
    IOAddress duid2_addr_;
};


// Exercises AllocEnginer6Test::updateExtendedInfo6() through various
// permutations of client packet content.
TEST_F(AllocEngine6ExtendedInfoTest, updateExtendedInfo6) {
    // Structure that defines a test scenario.
    struct Scenario {
        std::string description_;       // test description
        std::string orig_context_json_; // user context the lease begins with
        std::vector<Pkt6::RelayInfo> relays_; // vector of relays from pkt
        std::string exp_context_json_;  // expected user context on the lease
        bool exp_ret;                   // expected returned value
    };

    // Test scenarios.
    std::vector<Scenario> scenarios {
    {
        "no context, no relay",
        "",
        {},
        "",
        false
    },
    {
        "some original context, no relay",
        "{\"foo\": 123}",
        {},
        "{\"foo\": 123}",
        false
    },
    {
        "no original context, one relay",
        "",
        { relay1_ },
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" } ] } }",
        true
    },
    {
        "some original context, one relay",
        "{\"foo\": 123}",
        { relay1_ },
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" } ] },"
        " \"foo\": 123 }",
        true
    },
    {
        "no original context, two relays",
        "",
        { relay1_, relay2_ },
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" },"
        " {\"hop\": 77, \"link\": \"2001:db8::3\", \"peer\": \"2001:db8::4\" } ] } }",
        true
    },
    {
        "original relay context, no relay",
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" } ] } }",
        {},
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" } ] } }",
        false
    },
    {
        "original relay context, different relay",
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" } ] } }",
        { relay2_ },
        "{ \"ISC\": { \"relays\": [ { \"hop\": 77, \"link\": \"2001:db8::3\","
        " \"peer\": \"2001:db8::4\" } ] } }",
        true
    }};

    // Allocate a lease.
    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234)));
    ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
    ASSERT_TRUE(lease);

    // All scenarios require storage to be enabled.
    ctx.subnet_->setStoreExtendedInfo(true);

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
        }
        else {
            ASSERT_TRUE(lease->getContext());
            ASSERT_TRUE(orig_context->equals(*(lease->getContext())));
        }

        // Set the client packet relay vector from the scenario.
        ctx.query_->relay_info_ = scenario.relays_;

        // Call AllocEngine::updateLease6ExtendeInfo().
        bool ret;
        ASSERT_NO_THROW_LOG(ret = engine_.callUpdateLease6ExtendedInfo(lease, ctx));
        ASSERT_EQ(scenario.exp_ret, ret);

        // Verify the lease has the expected user context content.
        if (!exp_context) {
            ASSERT_FALSE(lease->getContext());
        }
        else {
            ASSERT_TRUE(lease->getContext());
            ASSERT_TRUE(exp_context->equals(*(lease->getContext())))
                << "expected: " << *(exp_context) << std::endl
                << "  actual: " << *(lease->getContext()) << std::endl;
        }
    }
}

// Verifies that the extended data (RelayInfos for now) is
// added to a V6 lease when leases are created and/or renewed,
// when store-extended-info is true.
TEST_F(AllocEngine6ExtendedInfoTest, storeExtendedInfoEnabled6) {
    // Structure that defines a test scenario.
    struct Scenario {
        std::string description_;             // test description
        DuidPtr duid_;                        // client DUID
        std::vector<Pkt6::RelayInfo> relays_; // vector of relays from pkt
        std::string exp_context_json_;        // expected user context on the lease
        IOAddress exp_address_;               // expected lease address
    };

    // Test scenarios.
    std::vector<Scenario> scenarios {
    {
        "create client one without relays",
        duid1_,
        {},
        "",
        duid1_addr_
    },
    {
        "renew client one without relays",
        DuidPtr(),
        {},
        "",
        duid1_addr_
    },
    {
        "create client two with relays",
        duid2_,
        { relay1_, relay2_ },
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" },"
        " { \"hop\": 77, \"link\": \"2001:db8::3\", \"peer\": \"2001:db8::4\" } ] } }",
        duid2_addr_
    },
    {
        "renew client two without rai",
        DuidPtr(),
        {},
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" },"
        " { \"hop\": 77, \"link\": \"2001:db8::3\", \"peer\": \"2001:db8::4\" } ] } }",
        duid2_addr_
    }};

    // All of the scenarios require storage to be enabled.
    subnet_->setStoreExtendedInfo(true);

    // Iterate over the test scenarios.
    DuidPtr current_duid;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        ElementPtr exp_context;
        // Create the expected user context from JSON.
        if (!scenario.exp_context_json_.empty()) {
            ASSERT_NO_THROW(exp_context = Element::fromJSON(scenario.exp_context_json_))
                            << "invalid exp_context_json_, test is broken";
        }

        Pkt6Ptr pkt;
        if (scenario.duid_) {
            current_duid = scenario.duid_;
            pkt.reset(new Pkt6(DHCPV6_REQUEST, 1234));
        } else {
            pkt.reset(new Pkt6(DHCPV6_RENEW, 1234));
        }

        // Set packet relay vector from the scenario.
        pkt->relay_info_ = scenario.relays_;

        // Create the context;
        AllocEngine::ClientContext6 ctx(subnet_, current_duid, false, false, "", false, pkt);

        // Create or renew the lease.
        Lease6Ptr lease;
        ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
        ASSERT_TRUE(lease);

        EXPECT_EQ(scenario.exp_address_, lease->addr_);

        // Verify the lease has the expected user context content.
        if (!exp_context) {
            ASSERT_FALSE(lease->getContext());
        }
        else {
            ASSERT_TRUE(lease->getContext());
            ASSERT_TRUE(exp_context->equals(*(lease->getContext())))
                << "expected: " << *(exp_context) << std::endl
                << "  actual: " << *(lease->getContext()) << std::endl;
        }
    }
}

// Verifies that the extended data (RelayInfos for now) is
// not added to a V6 lease when leases are created and/or renewed,
// when store-extended-info is false.
TEST_F(AllocEngine6ExtendedInfoTest, storeExtendedInfoDisabled6) {
    // Structure that defines a test scenario.
    struct Scenario {
        std::string description_;             // test description
        DuidPtr duid_;                        // client DUID
        std::vector<Pkt6::RelayInfo> relays_; // vector of relays from pkt
        IOAddress exp_address_;               // expected lease address
    };

    // Test scenarios.
    std::vector<Scenario> scenarios {
    {
        "create client one without relays",
        duid1_,
        {},
        duid1_addr_
    },
    {
        "renew client one without relays",
        DuidPtr(),
        {},
        duid1_addr_
    },
    {
        "create client two with relays",
        duid2_,
        { relay1_, relay2_ },
        duid2_addr_
    },
    {
        "renew client two with relays",
        DuidPtr(),
        { relay1_, relay2_ },
        duid2_addr_
    }
    };

    // All of the scenarios require storage to be disabled.
    subnet_->setStoreExtendedInfo(false);

    // Iterate over the test scenarios.
    DuidPtr current_duid;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        Pkt6Ptr pkt;
        if (scenario.duid_) {
            current_duid = scenario.duid_;
            pkt.reset(new Pkt6(DHCPV6_REQUEST, 1234));
        } else {
            pkt.reset(new Pkt6(DHCPV6_RENEW, 1234));
        }

        // Set packet relay vector from the scenario.
        pkt->relay_info_ = scenario.relays_;

        // Create the context;
        AllocEngine::ClientContext6 ctx(subnet_, current_duid, false, false, "", false, pkt);

        // Create or renew the lease.
        Lease6Ptr lease;
        ASSERT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));
        ASSERT_TRUE(lease);

        EXPECT_EQ(scenario.exp_address_, lease->addr_);

        // Verify the lease had no user context content.
        ASSERT_FALSE(lease->getContext());
    }
}

// Verifies that the extended data (RelayInfos for now) is
// added to a V6 lease when an expired lease is reused and
// store-extended-info is true.  We don't bother testing the
// disabled case as this is tested thoroughly elsewhere.
TEST_F(AllocEngine6ExtendedInfoTest, reuseExpiredLease6) {
    // Create one subnet with a pool holding one address.
    IOAddress addr("2001:db8:1::ad");
    initSubnet(IOAddress("2001:db8:1::"), addr, addr);
    subnet_->setPreferred(Triplet<uint32_t>(200, 300, 400));
    subnet_->setValid(Triplet<uint32_t>(300, 400, 500));

    // Create an expired lease for duid1_.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid1_, 1234,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495;         // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // Asking specifically for this address with zero lifetimes
    AllocEngine::ClientContext6 ctx(subnet_, duid2_, false, false, "", false,
                                     Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 5678)));
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr, 128, 0, 0);

    // Add a relay to the packet relay vector.
    ctx.query_->relay_info_.push_back(relay1_);

    // Enable extended info storage.
    subnet_->setStoreExtendedInfo(true);

    // Reuse the expired lease.
    EXPECT_NO_THROW(lease = expectOneLease(engine_.allocateLeases6(ctx)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Now let's verify that the extended info is in the user-context.
    ASSERT_TRUE(lease->getContext());
    std::string exp_content_json =
        "{ \"ISC\": { \"relays\": [ { \"hop\": 33, \"link\": \"2001:db8::1\","
        " \"options\": \"0x00C800080102030405060708\", \"peer\": \"2001:db8::2\" } ] } }";
    ConstElementPtr exp_context;
    ASSERT_NO_THROW(exp_context = Element::fromJSON(exp_content_json))
                            << "invalid exp_context_json_, test is broken";
    ASSERT_TRUE(exp_context->equals(*(lease->getContext())))
                << "expected: " << *(exp_context) << std::endl
                << "  actual: " << *(lease->getContext()) << std::endl;
}

// Checks whether fake allocation does not use the cache feature.
TEST_F(AllocEngine6Test, solicitNoCache) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for fake allocation..
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", true,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can be reused (request) using cache threshold.
TEST_F(AllocEngine6Test, requestCacheThreshold6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 33%.
    subnet_->setCacheThreshold(.33);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(400 - age, lease->reuseable_valid_lft_);
    EXPECT_EQ(300 - age, lease->reuseable_preferred_lft_);

    // Check other lease parameters.
    EXPECT_TRUE(*lease->duid_ == *duid_);
    EXPECT_TRUE(ctx.isAllocated(addr));

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can be reused (renew) using cache threshold.
TEST_F(AllocEngine6Test, renewCacheThreshold6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(400 - age, lease->reuseable_valid_lft_);
    EXPECT_EQ(300 - age, lease->reuseable_preferred_lft_);

    // Check other lease parameters.
    EXPECT_TRUE(*lease->duid_ == *duid_);
    EXPECT_TRUE(ctx.isAllocated(prefix, prefixlen));

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can be reused (request) using cache max age.
TEST_F(AllocEngine6Test, requestCacheMaxAge6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the max age to 150.
    subnet_->setCacheMaxAge(150);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(400 - age, lease->reuseable_valid_lft_);
    EXPECT_EQ(300 - age, lease->reuseable_preferred_lft_);

    // Check other lease parameters.
    EXPECT_TRUE(*lease->duid_ == *duid_);
    EXPECT_TRUE(ctx.isAllocated(addr));

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can be reused (renew) using cache max age.
TEST_F(AllocEngine6Test, renewCacheMaxAge6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the max age to 150.
    subnet_->setCacheMaxAge(150);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(400 - age, lease->reuseable_valid_lft_);
    EXPECT_EQ(300 - age, lease->reuseable_preferred_lft_);

    // Check other lease parameters.
    EXPECT_TRUE(*lease->duid_ == *duid_);
    EXPECT_TRUE(ctx.isAllocated(prefix, prefixlen));

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can be reused (request) using both cache threshold
// and max age.
TEST_F(AllocEngine6Test, requestCacheBoth6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 150.
    subnet_->setCacheMaxAge(150);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(400 - age, lease->reuseable_valid_lft_);
    EXPECT_EQ(300 - age, lease->reuseable_preferred_lft_);

    // Check other lease parameters.
    EXPECT_TRUE(*lease->duid_ == *duid_);
    EXPECT_TRUE(ctx.isAllocated(addr));

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can be reused (renew) using both cache threshold
// and max age.
TEST_F(AllocEngine6Test, renewCacheBoth6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 150.
    subnet_->setCacheMaxAge(150);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    // Copy the lease, so as it can be compared with.
    Lease6Ptr original_lease(new Lease6(*lease));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was reused.
    time_t age = lease->cltt_ - now;
    EXPECT_GE(age, 100);
    EXPECT_LE(age, 110);
    EXPECT_EQ(400 - age, lease->reuseable_valid_lft_);
    EXPECT_EQ(300 - age, lease->reuseable_preferred_lft_);

    // Check other lease parameters.
    EXPECT_TRUE(*lease->duid_ == *duid_);
    EXPECT_TRUE(ctx.isAllocated(prefix, prefixlen));

    // Check the lease was not updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(original_lease, from_mgr);
}

// Checks whether a lease can't be reused (request) using too small
// cache threshold.
TEST_F(AllocEngine6Test, requestCacheBadThreshold6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 10%.
    subnet_->setCacheThreshold(.1);

    // Set the max age to 150.
    subnet_->setCacheMaxAge(150);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) using too small
// cache threshold.
TEST_F(AllocEngine6Test, renewCacheBadThreshold6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 10%.
    subnet_->setCacheThreshold(.1);

    // Set the max age to 150.
    subnet_->setCacheMaxAge(150);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (request) using too small
// cache max age.
TEST_F(AllocEngine6Test, requestCacheBadMaxAge6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 50.
    subnet_->setCacheMaxAge(50);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) using too small
// cache max age.
TEST_F(AllocEngine6Test, renewCacheBadMaxAge6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    // Set the max age to 50.
    subnet_->setCacheMaxAge(50);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) when the valid
// lifetime was reduced.
// This works only when the lifetime is recomputed.
TEST_F(AllocEngine6Test, renewCacheReducedValid6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set valid lifetime to 200.
    subnet_->setValid(200);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) when the preferred
// lifetime was reduced.
// This works only when the lifetime is recomputed.
TEST_F(AllocEngine6Test, renewCacheReducedPreferred6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set preferred lifetime to 100.
    subnet_->setPreferred(100);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (request) when DDNS parameter changed.
TEST_F(AllocEngine6Test, requestCacheFwdDDNS6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, true, false, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) when DDNS parameter changed.
TEST_F(AllocEngine6Test, renewCacheFwdDDNS6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, true, false, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (request) when DDNS parameter changed.
TEST_F(AllocEngine6Test, requestCacheRevDDNS6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID()));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, true, "", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) when DDNS parameter changed.
TEST_F(AllocEngine6Test, renewCacheRevDDNS6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, true, "", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (request) when hostname changed.
TEST_F(AllocEngine6Test, requestCacheHostname6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress addr("2001:db8:1::15");
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               false, false, "foo"));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for request.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "bar", false,
                                    query);
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(addr);

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    EXPECT_EQ(addr, lease->addr_);
    EXPECT_EQ(128, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);
    EXPECT_EQ("bar", lease->hostname_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Checks whether a lease can't be reused (renew) when hostname changed.
TEST_F(AllocEngine6Test, renewCacheHostname6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Set the threshold to 25%.
    subnet_->setCacheThreshold(.25);

    IOAddress prefix("2001:db8:1:2::");
    uint8_t prefixlen = 80;
    time_t now = time(NULL) - 100; // Allocated 100 seconds ago.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid_,
                               300, 400, subnet_->getID(),
                               false, false, "foo",
                               HWAddrPtr(), prefixlen));
    lease->cltt_ = now;
    ASSERT_FALSE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Create a context for renew.
    Pkt6Ptr query(new Pkt6(DHCPV6_RENEW, 1234));
    AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "bar", false,
                                    query);
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().iaid_ = iaid_;
    ctx.currentIA().addHint(prefix, prefixlen);

    EXPECT_NO_THROW(lease = expectOneLease(engine->renewLeases6(ctx)));
    EXPECT_EQ(prefix, lease->addr_);
    EXPECT_EQ(prefixlen, lease->prefixlen_);

    // The lease was not reused.
    EXPECT_EQ(0, lease->reuseable_valid_lft_);
    EXPECT_EQ("bar", lease->hostname_);

    // Check the lease was updated in the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    detailCompareLease(lease, from_mgr);
}

// Verifies that AllocEngine::getLifetimes6() returns the appropriate
// valid lifetime value based on the context content.
TEST_F(AllocEngine6Test, getValidLifetime) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Let's make three classes, two with valid-lifetime and one without,
    // and add them to the dictionary.
    ClientClassDictionaryPtr dictionary = 
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary();

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
            "no classes, no hint",
            {},
            0,
            subnet_->getValid()
        },
        {
            "no classes, hint",
            {},
            subnet_->getValid().getMin() + 50,
            subnet_->getValid().getMin() + 50
        },
        {
            "no classes, hint too small",
            {},
            subnet_->getValid().getMin() - 50,
            subnet_->getValid().getMin()
        },
        {
            "no classes, hint too big",
            {},
            subnet_->getValid().getMax() + 50,
            subnet_->getValid().getMax()
        },
        {
            "class unspecified, no hint",
            { "valid_unspec" },
            0,
            subnet_->getValid()
        },
        {
            "from last class, no hint",
            { "valid_unspec", "valid_one" },
            0,
            valid_one.get()
        },
        {
            "from first class, no hint",
            { "valid_two", "valid_one" },
            0,
            valid_two.get()
        },
        {
            "class plus hint",
            { "valid_one" },
            valid_one.getMin() + 25,
            valid_one.getMin() + 25
        },
        {
            "class plus hint too small",
            { "valid_one" },
            valid_one.getMin() - 25,
            valid_one.getMin()
        },
        {
            "class plus hint too big",
            { "valid_one" },
            valid_one.getMax() + 25,
            valid_one.getMax()
        }
    };

    // Iterate over the scenarios and verify the correct outcome.
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.desc_); {
            // Create a context;
            AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", true,
                                            Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234)));
            // Add client classes (if any)
            for (auto class_name : scenario.classes_) {
                ctx.query_->addClass(class_name);
            }

            // Add hint
            ctx.currentIA().iaid_ = iaid_;

            // prefix,prefixlen, preferred, valid
            ctx.currentIA().addHint(IOAddress("::"), 128, 0, scenario.requested_lft_);

            Lease6Ptr lease;
            ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
            ASSERT_TRUE(lease);
            EXPECT_EQ(lease->valid_lft_, scenario.exp_valid_);
        }
    }
}

// Verifies that AllocEngine::getLifetimes6() returns the appropriate
// preferred lifetime value based on the context content.
TEST_F(AllocEngine6Test, getPreferredLifetime) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Let's make three classes, two with preferred-lifetime and one without,
    // and add them to the dictionary.
    ClientClassDictionaryPtr dictionary =
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary();

    ClientClassDefPtr class_def(new ClientClassDef("preferred_one", ExpressionPtr()));
    Triplet<uint32_t> preferred_one(50, 100, 150);
    class_def->setPreferred(preferred_one);
    dictionary->addClass(class_def);

    class_def.reset(new ClientClassDef("preferred_two", ExpressionPtr()));
    Triplet<uint32_t>preferred_two(200, 250, 300);
    class_def->setPreferred(preferred_two);
    dictionary->addClass(class_def);

    class_def.reset(new ClientClassDef("preferred_unspec", ExpressionPtr()));
    dictionary->addClass(class_def);

    // Commit our class changes.
    CfgMgr::instance().commit();

    // Update the subnet's triplet to something more useful.
    subnet_->setPreferred(Triplet<uint32_t>(500, 1000, 1500));

    // Describes a test scenario.
    struct Scenario {
        std::string desc_;                  // descriptive text for logging
        std::vector<std::string> classes_;  // class list of assigned classes
        uint32_t requested_lft_;            // use as option 51 is > 0
        uint32_t exp_preferred_;                // expected lifetime
    };

    // Scenarios to test.
    std::vector<Scenario> scenarios = {
        {
            "no classes, no hint",
            {},
            0,
            subnet_->getPreferred()
        },
        {
            "no classes, hint",
            {},
            subnet_->getPreferred().getMin() + 50,
            subnet_->getPreferred().getMin() + 50
        },
        {
            "no classes, hint too small",
            {},
            subnet_->getPreferred().getMin() - 50,
            subnet_->getPreferred().getMin()
        },
        {
            "no classes, hint too big",
            {},
            subnet_->getPreferred().getMax() + 50,
            subnet_->getPreferred().getMax()
        },
        {
            "class unspecified, no hint",
            { "preferred_unspec" },
            0,
            subnet_->getPreferred()
        },
        {
            "from last class, no hint",
            { "preferred_unspec", "preferred_one" },
            0,
            preferred_one.get()
        },
        {
            "from first class, no hint",
            { "preferred_two", "preferred_one" },
            0,
            preferred_two.get()
        },
        {
            "class plus hint",
            { "preferred_one" },
            preferred_one.getMin() + 25,
            preferred_one.getMin() + 25
        },
        {
            "class plus hint too small",
            { "preferred_one" },
            preferred_one.getMin() - 25,
            preferred_one.getMin()
        },
        {
            "class plus hint too big",
            { "preferred_one" },
            preferred_one.getMax() + 25,
            preferred_one.getMax()
        }
    };

    // Iterate over the scenarios and verify the correct outcome.
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.desc_); {
            // Create a context;
            AllocEngine::ClientContext6 ctx(subnet_, duid_, false, false, "", true,
                                            Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234)));
            // Add client classes (if any)
            for (auto class_name : scenario.classes_) {
                ctx.query_->addClass(class_name);
            }

            // Add hint
            ctx.currentIA().iaid_ = iaid_;

            // prefix,prefixlen, preferred, preferred
            ctx.currentIA().addHint(IOAddress("::"), 128, scenario.requested_lft_, 0);

            Lease6Ptr lease;
            ASSERT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
            ASSERT_TRUE(lease);
            EXPECT_EQ(lease->preferred_lft_, scenario.exp_preferred_);
        }
    }
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
