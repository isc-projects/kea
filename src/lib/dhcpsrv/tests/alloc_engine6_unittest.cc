// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/tests/test_utils.h>
#include <stats/stats_mgr.h>

using namespace std;
using namespace isc::hooks;
using namespace isc::asiolink;
using namespace isc::stats;

namespace isc {
namespace dhcp {
namespace test {

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

// This test checks if the simple allocation (REQUEST) can succeed
// and the stats counter is properly bumped by 1
TEST_F(AllocEngine6Test, simpleAlloc6) {

    simpleAlloc6Test(pool_, IOAddress("::"), false);

    // We should have bumped the address counter by 1
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(101, stat->getInteger().first);
}

// This test checks if the simple PD allocation (REQUEST) can succeed
// and the stats counter is properly bumped by 1
TEST_F(AllocEngine6Test, pdSimpleAlloc6) {

    simpleAlloc6Test(pd_pool_, IOAddress("::"), false);

    // We should have bumped the address counter by 1
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-pds");
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(101, stat->getInteger().first);
}

// This test checks if the fake allocation (for SOLICIT) can succeed
// and the stats counter isn't bumped
TEST_F(AllocEngine6Test, fakeAlloc6) {

    simpleAlloc6Test(pool_, IOAddress("::"), true);

    // We should not have bumped the address counter
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(100, stat->getInteger().first);
}

// This test checks if the fake PD allocation (for SOLICIT) can succeed
// and the stats counter isn't bumped
TEST_F(AllocEngine6Test, pdFakeAlloc6) {
    simpleAlloc6Test(pd_pool_, IOAddress("::"), true);

    // We should not have bumped the address counter
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-pds");
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(100, stat->getInteger().first);
};

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
                          IOAddress("2001:db8:1::"), // allocate this prefix as used
                          IOAddress("2001:db8:1::"), // request this prefix
                          64);
}

// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine6Test, allocBogusHint6) {

    allocBogusHint6(Lease::TYPE_NA, IOAddress("3000::abc"), 128);
}

// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine6Test, pdAllocBogusHint6) {

    allocBogusHint6(Lease::TYPE_PD, IOAddress("3000::abc"), 64);
}

// This test checks that NULL values are handled properly
TEST_F(AllocEngine6Test, allocateAddress6Nulls) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx1(Subnet6Ptr(), duid_, iaid_, IOAddress("::"),
                                     Lease::TYPE_NA, false, false, "", false);
    ctx1.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx1)));
    ASSERT_FALSE(lease);

    // Allocations without DUID are not allowed either
    AllocEngine::ClientContext6 ctx2(subnet_, DuidPtr(), iaid_, IOAddress("::"),
                                     Lease::TYPE_NA, false, false, "", false);
    ctx2.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));
    ASSERT_FALSE(lease);
}


// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine6Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Lease::TYPE_NA));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
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
    EXPECT_EQ("2001:db8:1::1", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    // The second pool is easy - only one address here
    EXPECT_EQ("2001:db8:1::100", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
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
    EXPECT_EQ("2001:db8::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:20::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:30::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:40::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:50::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:60::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:70::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:80::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:90::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:a0::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:b0::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:c0::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:d0::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:e0::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:f0::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(), alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:0:10::", alloc.pickAddress(subnet_, duid_, IOAddress("::")).toText());
}

// This test verifies that the iterative allocator can step over addresses
TEST_F(AllocEngine6Test, IterativeAllocatorAddressIncrease) {
    NakedAllocEngine::NakedIterativeAllocator alloc(Lease::TYPE_NA);

    // Let's pick the first address
    IOAddress addr1 = alloc.pickAddress(subnet_, duid_, IOAddress("2001:db8:1::10"));

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
        IOAddress candidate = alloc.pickAddress(subnet_, duid_, IOAddress("::"));
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
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA, fqdn_fwd_, fqdn_rev_,
                                    hostname_, false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);

    EXPECT_EQ("2001:db8:1::ad", lease->addr_.toText());

    // Do all checks on the lease
    checkLease6(lease, Lease::TYPE_NA, 128);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // This is a new lease allocation. The old lease corresponding to a newly
    // allocated lease should be NULL.
    ASSERT_TRUE(ctx.old_leases_.empty());
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
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // There is just a single address in the pool and allocated it to someone
    // else, so the allocation should fail
    Lease6Ptr lease2;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA, false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));

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

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // CASE 1: Asking for any address
    AllocEngine::ClientContext6 ctx1(subnet_, duid_, iaid_, IOAddress("::"),
                                     Lease::TYPE_NA, fqdn_fwd_, fqdn_rev_, hostname_, true);
    ctx1.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));

    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx1)));
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(lease, Lease::TYPE_NA, 128);

    // CASE 2: Asking specifically for this address
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, iaid_, addr, Lease::TYPE_NA,
                                     false, false, "", true);
    ctx2.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx2)));

    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);
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

    // Let's create an expired lease
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    const SubnetID other_subnetid = 999;
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, other_duid, other_iaid,
                               501, 502, 503, 504, other_subnetid, HWAddrPtr(),
                               0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    lease->fqdn_fwd_ = true;
    lease->fqdn_rev_ = true;
    lease->hostname_ = "myhost.example.com.";
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // By default we pretend our subnet has 100 addresses
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    StatsMgr::instance().setValue(name, static_cast<int64_t>(100));

    // A client comes along, asking specifically for this address
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, addr, Lease::TYPE_NA,
                                    false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);
    // This reactivated lease should have updated FQDN data.
    EXPECT_TRUE(lease->hostname_.empty());
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);

    // Check that the old lease has been returned.
    Lease6Ptr old_lease = expectOneLease(ctx.old_leases_);
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

    // We should not have bumped the address counter
    // NOTE: when we start expiring addresses and removing them from
    // the stats this will no longer be true.
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(100, stat->getInteger().first);
}

// Checks if the lease lifetime is extended when the client sends the
// Request.
TEST_F(AllocEngine6Test, requestExtendLeaseLifetime) {
    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400, 100, 200,
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
                               duid_, iaid_, 300, 400, 100, 200,
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
                               duid_, iaid_, 300, 400, 100, 200,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(make_pair(IOAddress("2001:db8:1::15"), 128));

    // Client should receive a lease.
    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // And the lease lifetime should be extended.
    EXPECT_GT(renewed[0]->cltt_, lease_cltt)
        << "Lease lifetime was not extended, but it should";
}

// Checks if the lease lifetime is extended when the client sends the
// Renew and the client has a reservation for the lease.
TEST_F(AllocEngine6Test, renewExtendLeaseLifetimeForReservation) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::15"), 128);

    // Create a lease for the client.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::15"),
                               duid_, iaid_, 300, 400, 100, 200,
                               subnet_->getID(), HWAddrPtr(), 128));

    // Allocated 200 seconds ago - half of the lifetime.
    time_t lease_cltt = time(NULL) - 200;
    lease->cltt_ = lease_cltt;

    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(make_pair(IOAddress("2001:db8:1::15"), 128));

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

    // By default we pretend our subnet has 100 addresses
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    StatsMgr::instance().setValue(name, static_cast<int64_t>(100));

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());

    // We should have bumped the address counter
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(101, stat->getInteger().first);
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
TEST_F(AllocEngine6Test, reservedAddressInPoolRequestValidHint) {
    // Create reservation for the client This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
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

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), true);
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
TEST_F(AllocEngine6Test, reservedAddressInPoolRequestMatchingHint) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8:1::1c", lease->addr_.toText());
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

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), true, false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

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

    // By default we pretend our subnet has 100 addresses
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    StatsMgr::instance().setValue(name, static_cast<int64_t>(100));

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), false, false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());

    // We should not have bumped the address counter
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(100, stat->getInteger().first);
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

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), true, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());
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

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::10"), false, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());
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

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), true, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());
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

    // Let's pretend the client sends hint 2001:db8:1::10.
    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::1c"), false, false);
    ASSERT_TRUE(lease);

    // The hint should be ignored and the reserved address should be assigned
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());
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

    // Client gets an address
    Lease6Ptr lease1 = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease1);

    // We should have bumped the address counter
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(101, stat->getInteger().first);

    // Just check that if the client requests again, it will get the same
    // address.
    Lease6Ptr lease2 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease2);
    detailCompareLease(lease1, lease2);

    // We should not have bumped the address counter again
    EXPECT_EQ(101, stat->getInteger().first);

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

    // Lastly check to see that the address counter is still 101 we should have
    // have decremented it on the implied release and incremented it on the reserved
    EXPECT_EQ(101, stat->getInteger().first);
}
// In the following situation:
// - client X is assigned an address A
// - HR is made for client Y (*other* client) to get A
// - client X tries to get address A:
//    Check that his existing lease for lease A is removed
//    Check that he is assigned a new lease
TEST_F(AllocEngine6Test, reservedAddressInPoolReassignedOther) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Client gets an address
    Lease6Ptr lease1 = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease1);

    // We should have bumped the address counter
    string name = StatsMgr::generateName("subnet", subnet_->getID(), "assigned-nas");
    ObservationPtr stat = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(stat);
    EXPECT_EQ(101, stat->getInteger().first);

    // Just check that if the client requests again, it will get the same
    // address.
    Lease6Ptr lease2 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease2);
    detailCompareLease(lease1, lease2);

    // We should not have bumped the address counter again
    EXPECT_EQ(101, stat->getInteger().first);

    // Now admin creates a reservation for this client. Let's use the
    // address client X just received. Let's generate a host, but don't add it
    // to the HostMgr yet.
    HostPtr host = createHost6(false, IPv6Resrv::TYPE_NA, lease1->addr_, 128);

    // We need to tweak reservation id: use a different DUID for client Y
    vector<uint8_t> other_duid(8, 0x45);
    host->setIdentifier(&other_duid[0], other_duid.size(), Host::IDENT_DUID);

    // Ok, now add it to the HostMgr
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

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

    // Lastly check to see that the address counter is still 101 we should have
    // have decremented it on the implied release and incremented it on the reserved
    EXPECT_EQ(101, stat->getInteger().first);
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
        AllocEngine::ClientContext6 ctx(subnet_, clients[i], iaid_, IOAddress("::"),
                                        Lease::TYPE_NA,  false, false, "", false);
        ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
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
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA,  false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));

    findReservation(engine, ctx);
    Lease6Collection leases = engine.allocateLeases6(ctx);
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ("2001:db8:1::12", leases[0]->addr_.toText());
}

// Checks if the allocateLeases throws exceptions for invalid input data.
TEST_F(AllocEngine6Test, allocateLeasesInvalidData) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, true);

    // That looks like a valid context.
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA,  false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
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

    Lease6Collection leases;

    leases = allocateTest(engine, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(make_pair(leases[0]->addr_, 128));

    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());

    // Check that the lease was indeed renewed and hasn't changed
    // (i.e. the same address, preferred and valid lifetimes)

    /// @todo: use leaseCompare, but ignore cltt_
    EXPECT_EQ(leases[0]->addr_, renewed[0]->addr_);
    EXPECT_EQ(leases[0]->type_, renewed[0]->type_);
    EXPECT_EQ(leases[0]->preferred_lft_, renewed[0]->preferred_lft_);
    EXPECT_EQ(leases[0]->valid_lft_, renewed[0]->valid_lft_);
}

// Checks whether an address can be renewed (in-pool reservation)
TEST_F(AllocEngine6Test, reservedAddressRenewal) {
    // Create reservation for the client. This is in-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1c"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100);

    Lease6Collection leases;

    leases = allocateTest(engine, pool_, IOAddress("::"), false, true);
    ASSERT_EQ(1, leases.size());
    ASSERT_EQ("2001:db8:1::1c", leases[0]->addr_.toText());

    // This is what the client will send in his renew message.
    AllocEngine::HintContainer hints;
    hints.push_back(make_pair(leases[0]->addr_, 128));

    Lease6Collection renewed = renewTest(engine, pool_, hints, true);
    ASSERT_EQ(1, renewed.size());
    ASSERT_EQ("2001:db8:1::1c", leases[0]->addr_.toText());
}

// Checks whether a single host can have more than one reservation.
//
/// @todo: as of #3677, this does not work. When processing solicit with two
/// IA_NAs and two reservations, there currently no way to indicate that
/// the first reservation should be used for the first IA and the second
/// reservation for the second IA. This works for Requests and Renews, though.
/// In both of those messages, when processing of the first IA is complete,
/// we have a lease in the database. Based on that, when processing the second
/// IA we can detect that the first reservated address is in use already and
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

    AllocEngine::ClientContext6 ctx1(subnet_, duid_, iaid_, IOAddress("::"),
                                    pool_->getType(), false, false, "", true);
    ctx1.query_.reset(new Pkt6(DHCPV6_SOLICIT, 1234));
    Lease6Collection leases1;
    findReservation(engine, ctx1);
    EXPECT_NO_THROW(leases1 = engine.allocateLeases6(ctx1));
    ASSERT_EQ(1, leases1.size());
    EXPECT_EQ("2001:db8:1::babe", leases1[0]->addr_.toText());

    // Double check that repeating the same duid/type/iaid will end up with
    // the same address.
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, iaid_, IOAddress("::"),
                                    pool_->getType(), false, false, "", true);
    ctx2.query_.reset(new Pkt6(DHCPV6_SOLICIT, 1234));
    Lease6Collection leases2;
    findReservation(engine, ctx2);
    EXPECT_NO_THROW(leases2 = engine.allocateLeases6(ctx2));
    EXPECT_EQ(1, leases2.size());
    EXPECT_EQ("2001:db8:1::babe", leases2[0]->addr_.toText());

    // Ok, now the tricky part. Request allocation for the same duid and type, but
    // different iaid. The second address should be assigned.
    AllocEngine::ClientContext6 ctx3(subnet_, duid_, iaid_ + 1, IOAddress("::"),
                                    pool_->getType(), false, false, "", true);
    ctx3.query_.reset(new Pkt6(DHCPV6_SOLICIT, 1234));
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

    AllocEngine::ClientContext6 ctx1(subnet_, duid_, iaid_, IOAddress("::"),
                                    pool_->getType(), false, false, "", false);
    ctx1.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    Lease6Collection leases1;
    findReservation(engine, ctx1);
    EXPECT_NO_THROW(leases1 = engine.allocateLeases6(ctx1));
    ASSERT_EQ(1, leases1.size());
    EXPECT_EQ("2001:db8:1::babe", leases1[0]->addr_.toText());

    // Double check that repeating the same duid/type/iaid will end up with
    // the same address.
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, iaid_, IOAddress("::"),
                                    pool_->getType(), false, false, "", false);
    ctx2.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));

    Lease6Collection leases2;
    findReservation(engine, ctx2);
    EXPECT_NO_THROW(leases2 = engine.allocateLeases6(ctx2));
    EXPECT_EQ(1, leases2.size());
    EXPECT_EQ("2001:db8:1::babe", leases2[0]->addr_.toText());

    // Ok, now the tricky part. Request allocation for the same duid and type, but
    // different iaid. The second address should be assigned.
    AllocEngine::ClientContext6 ctx3(subnet_, duid_, iaid_ + 1, IOAddress("::"),
                                    pool_->getType(), false, false, "", false);
    ctx3.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    
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
    hints.push_back(make_pair(leases[0]->addr_, 128));

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
    hints.push_back(make_pair(leases[0]->addr_, 128));

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
    Pool6Ptr pool(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 64, 96));
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

        // Allocate the leease.
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, IOAddress(address.str()),
                                   duid, iaid, 501, 502, 503, 504, subnet_->getID(),
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

}; // namespace test
}; // namespace dhcp
}; // namespace isc
