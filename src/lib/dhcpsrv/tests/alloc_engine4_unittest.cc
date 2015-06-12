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
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/tests/test_utils.h>

using namespace std;
using namespace isc::hooks;
using namespace isc::asiolink;

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


// This test checks if the simple IPv4 allocation can succeed
TEST_F(AllocEngine4Test, simpleAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the fake allocation (for DISCOVER) can succeed
TEST_F(AllocEngine4Test, fakeAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, true,
                                    "host.example.com.", true);
    ctx.query_.reset(new Pkt4(DHCPDISCOVER, 1234));

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // The new lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is NOT in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_FALSE(from_mgr);
}


// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngine4Test, allocWithValidHint4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("192.0.2.105"), true, true,
                                    "host.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We have allocated the new lease, so the old lease should not exist.
    EXPECT_FALSE(ctx.old_lease_);

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
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL);
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              clientid2, sizeof(clientid2), 1, 2, 3, now, subnet_->getID()));
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
    EXPECT_FALSE(ctx.old_lease_);

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
                                                 100, false)));
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
    EXPECT_FALSE(ctx.old_lease_);

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
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    AllocEngine::ClientContext4 ctx1(Subnet4Ptr(), clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr lease = engine->allocateLease4(ctx1);

    EXPECT_FALSE(lease);

    // Allocations without HW address are not allowed
    AllocEngine::ClientContext4 ctx2(subnet_, clientid_, HWAddrPtr(),
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);
    ctx2.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    lease = engine->allocateLease4(ctx2);
    EXPECT_FALSE(lease);
    EXPECT_FALSE(ctx2.old_lease_);

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
    EXPECT_FALSE(ctx3.old_lease_);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}



// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine4Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Lease::TYPE_V4));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, clientid_,
                                                 IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
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
        IOAddress candidate = alloc.pickAddress(subnet_, clientid_, IOAddress("0.0.0.0"));
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
                                                 100, false)));
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
    EXPECT_FALSE(ctx.old_lease_);

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
                                                 100, false)));
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
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL);
    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2,
                               sizeof(clientid2), 501, 502, 503, now,
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
    EXPECT_FALSE(lease2);
    EXPECT_FALSE(ctx.old_lease_);
}

// This test checks if an expired lease can be reused in DISCOVER (fake allocation)
TEST_F(AllocEngine4Test, discoverReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
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
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago
    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2, sizeof(clientid2),
                               495, 100, 200, now, subnet_->getID()));
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
                                                 100, false)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.105");

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago
    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2, sizeof(clientid2),
                               sizeof(hwaddr2), 495, 100, 200, now,
                               subnet_->getID()));
    // Make a copy of the lease, so as we can comapre that with the old lease
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
}

// This test checks that the Allocation Engine correcly identifies the
// existing client's lease in the lease database, using the client
// identifier and HW address.
TEST_F(AllocEngine4Test, identifyClientLease) {
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, clientid_,
                               100, 30, 60, time(NULL), subnet_->getID()));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);
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
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    // Create the second lease. Note that we use the same client id here and
    // we expect that the allocation engine will figure out that the hardware
    // address is different.
    Lease4Ptr lease2(new Lease4(IOAddress("192.0.2.102"), hwaddr2_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    // Add leases for both clients to the Lease Manager.
    LeaseMgrFactory::instance().addLease(lease);
    LeaseMgrFactory::instance().addLease(lease2);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // First client requests the lease which belongs to the second client.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("192.0.2.102"),
                                    false, false, "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    Lease4Ptr new_lease = engine.allocateLease4(ctx);
    // Allocation engine should return NULL.
    ASSERT_FALSE(new_lease);

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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
    EXPECT_FALSE(ctx.old_lease_);
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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
    EXPECT_FALSE(ctx.old_lease_);
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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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

    EXPECT_FALSE(ctx2.old_lease_);
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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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

    EXPECT_FALSE(ctx.old_lease_);
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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client with a different address than the reserved
    // one.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Allocate a lease for the client A for the same address as reserved
    // for the client B.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.123"), hwaddr2_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
    EXPECT_FALSE(ctx1.old_lease_);

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
    EXPECT_FALSE(ctx2.old_lease_);

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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client A.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.123"), hwaddr2_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
    EXPECT_FALSE(ctx1.old_lease_);
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
    EXPECT_FALSE(ctx2.old_lease_);
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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for the client for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, ClientIdPtr(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
    EXPECT_FALSE(allocated_lease);
    EXPECT_FALSE(ctx2.old_lease_);
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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
                          SubnetID(0), IOAddress("192.0.2.101")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for Client A.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_,
                               &clientid_->getClientId()[0],
                               clientid_->getClientId().size(),
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);


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
                          SubnetID(0), IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

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
                          SubnetID(0), IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Different client is requesting this address.
    AllocEngine::ClientContext4 ctx1(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("192.0.2.100"), false, false,
                                     "", false);
    ctx1.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    AllocEngine::findReservation(ctx1);
    Lease4Ptr allocated_lease = engine.allocateLease4(ctx1);

    // The client should get no lease (DHCPNAK).
    ASSERT_FALSE(allocated_lease);

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
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Create short pool with only one address.
    initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.100"));
    // Reserve the address for a different client.
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr2_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress("192.0.2.100")));
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

    EXPECT_FALSE(allocated_lease);

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
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Create a reservation for a hostname. Address is set to 0 which
    // indicates that there is no reservation.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress::IPV4_ZERO_ADDRESS(),
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
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Context is required to call the AllocEngine::findReservation.
    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"), false, false,
                                    "", false);

    // There is no reservation in the database so no host should be
    // retruned.
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.host_);

    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // This time the reservation should be returned.
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_TRUE(ctx.host_);
    EXPECT_EQ(ctx.host_->getIPv4Reservation(), host->getIPv4Reservation());

    // If the host reservation mode for the subnet is disabled, the
    // host should not be returned, even though it exists in the
    // host database.
    subnet_->setHostReservationMode(Subnet::HR_DISABLED);
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.host_);

    // Check the third possible reservation mode.
    subnet_->setHostReservationMode(Subnet::HR_OUT_OF_POOL);
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_TRUE(ctx.host_);
    EXPECT_EQ(ctx.host_->getIPv4Reservation(), host->getIPv4Reservation());

    // This time use the client identifier to search for the host.
    host.reset(new Host(&clientid_->getClientId()[0],
                        clientid_->getClientId().size(),
                        Host::IDENT_DUID, subnet_->getID(),
                        SubnetID(0), IOAddress("192.0.2.101")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_TRUE(ctx.host_);
    EXPECT_EQ(ctx.host_->getIPv4Reservation(), host->getIPv4Reservation());

    // Remove the subnet. Subnet id is required to find host reservations, so
    // if it is set to NULL, no reservation should be returned
    ctx.subnet_.reset();
    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.host_);

    // The same if there is a mismatch of the subnet id between the reservation
    // and the context.
    ctx.subnet_ = subnet_;
    host.reset(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                        Host::IDENT_HWADDR, subnet_->getID() + 1,
                        SubnetID(0), IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    ASSERT_NO_THROW(engine.findReservation(ctx));
    EXPECT_FALSE(ctx.host_);
}

}; // namespace test
}; // namespace dhcp
}; // namespace isc
