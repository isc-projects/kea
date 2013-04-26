// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/dhcp4.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>

#include <dhcpsrv/tests/test_utils.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <set>
#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Allocation engine with some internal methods exposed
class NakedAllocEngine : public AllocEngine {
public:

    /// @brief the sole constructor
    /// @param engine_type specifies engine type (e.g. iterative)
    /// @param attempts number of lease selection attempts before giving up
    NakedAllocEngine(AllocEngine::AllocType engine_type, unsigned int attempts)
        :AllocEngine(engine_type, attempts) {
    }

    // Expose internal classes for testing purposes
    using AllocEngine::Allocator;
    using AllocEngine::IterativeAllocator;
};

/// @brief Used in Allocation Engine tests for IPv6
class AllocEngine6Test : public ::testing::Test {
public:

    /// @brief Default constructor
    ///
    /// Sets duid_, iaid_, subnet_, pool_ fields to example values used
    /// in many tests, initializes cfg_mgr configuration and creates
    /// lease database.
    AllocEngine6Test() {
        duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        iaid_ = 42;

        // instantiate cfg_mgr
        CfgMgr& cfg_mgr = CfgMgr::instance();

        subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
        pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1::10"),
                                   IOAddress("2001:db8:1::20")));
        subnet_->addPool(pool_);
        cfg_mgr.addSubnet6(subnet_);

        factory_.create("type=memfile");
    }

    /// @brief checks if Lease6 matches expected configuration
    ///
    /// @param lease lease to be checked
    void checkLease6(const Lease6Ptr& lease) {
        // that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());
        EXPECT_TRUE(subnet_->inRange(lease->addr_));
        EXPECT_TRUE(subnet_->inPool(lease->addr_));

        // that it have proper parameters
        EXPECT_EQ(iaid_, lease->iaid_);
        EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);
        EXPECT_EQ(subnet_->getPreferred(), lease->preferred_lft_);
        EXPECT_EQ(subnet_->getT1(), lease->t1_);
        EXPECT_EQ(subnet_->getT2(), lease->t2_);
        EXPECT_EQ(0, lease->prefixlen_); // this is IA_NA, not IA_PD
        EXPECT_TRUE(false == lease->fqdn_fwd_);
        EXPECT_TRUE(false == lease->fqdn_rev_);
        EXPECT_TRUE(*lease->duid_ == *duid_);
        // @todo: check cltt
     }

    ~AllocEngine6Test() {
        factory_.destroy();
    }

    DuidPtr duid_;            ///< client-identifier (value used in tests)
    uint32_t iaid_;           ///< IA identifier (value used in tests)
    Subnet6Ptr subnet_;       ///< subnet6 (used in tests)
    Pool6Ptr pool_;           ///< pool belonging to subnet_
    LeaseMgrFactory factory_; ///< pointer to LeaseMgr factory
};

/// @brief Used in Allocation Engine tests for IPv4
class AllocEngine4Test : public ::testing::Test {
public:

    /// @brief Default constructor
    ///
    /// Sets clientid_, hwaddr_, subnet_, pool_ fields to example values
    /// used in many tests, initializes cfg_mgr configuration and creates
    /// lease database.
    AllocEngine4Test() {
        clientid_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x44)));
        static uint8_t mac[] = { 0, 1, 22, 33, 44, 55};

        // Let's use odd hardware type to check if there is no Ethernet
        // hardcoded anywhere.
        hwaddr_ = HWAddrPtr(new HWAddr(mac, sizeof(mac), HTYPE_FDDI));

        // instantiate cfg_mgr
        CfgMgr& cfg_mgr = CfgMgr::instance();

        subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
        pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                                   IOAddress("192.0.2.109")));
        subnet_->addPool(pool_);
        cfg_mgr.addSubnet4(subnet_);

        factory_.create("type=memfile");
    }

    /// @brief checks if Lease4 matches expected configuration
    ///
    /// @param lease lease to be checked
    void checkLease4(const Lease4Ptr& lease) {
        // that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());
        EXPECT_TRUE(subnet_->inRange(lease->addr_));
        EXPECT_TRUE(subnet_->inPool(lease->addr_));

        // that it have proper parameters
        EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);
        EXPECT_EQ(subnet_->getT1(), lease->t1_);
        EXPECT_EQ(subnet_->getT2(), lease->t2_);
        EXPECT_TRUE(false == lease->fqdn_fwd_);
        EXPECT_TRUE(false == lease->fqdn_rev_);
        if (lease->client_id_ && !clientid_) {
            ADD_FAILURE() << "Lease4 has a client-id, while it should have none.";
        } else
        if (!lease->client_id_ && clientid_) {
            ADD_FAILURE() << "Lease4 has no client-id, but it was expected to have one.";
        } else
        if (lease->client_id_ && clientid_) {
            EXPECT_TRUE(*lease->client_id_ == *clientid_);
        }
        EXPECT_TRUE(lease->hwaddr_ == hwaddr_->hwaddr_);
        // @todo: check cltt
     }

    ~AllocEngine4Test() {
        factory_.destroy();
    }

    ClientIdPtr clientid_;    ///< client-identifier (value used in tests)
    HWAddrPtr hwaddr_;        ///< hardware address (value used in tests)
    Subnet4Ptr subnet_;       ///< subnet4 (used in tests)
    Pool4Ptr pool_;           ///< pool belonging to subnet_
    LeaseMgrFactory factory_; ///< pointer to LeaseMgr factory
};

// This test checks if the Allocation Engine can be instantiated and that it
// parses parameters string properly.
TEST_F(AllocEngine6Test, constructor) {
    boost::scoped_ptr<AllocEngine> x;

    // Hashed and random allocators are not supported yet
    ASSERT_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_HASHED, 5)), NotImplemented);
    ASSERT_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_RANDOM, 5)), NotImplemented);

    ASSERT_NO_THROW(x.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
}

// This test checks if the simple allocation can succeed
TEST_F(AllocEngine6Test, simpleAlloc6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress("::"),
                                               false);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the fake allocation (for SOLICIT) can succeed
TEST_F(AllocEngine6Test, fakeAlloc6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress("::"),
                                               true);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is NOT in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->addr_);
    ASSERT_FALSE(from_mgr);
}

// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngine6Test, allocWithValidHint6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                               IOAddress("2001:db8:1::15"),
                                               false);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // we should get what we asked for
    EXPECT_EQ(lease->addr_.toText(), "2001:db8:1::15");

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the allocation with a hint that is in range,
// in pool, but is currently used) can succeed
TEST_F(AllocEngine6Test, allocWithUsedHint6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // let's create a lease and put it in the LeaseMgr
    DuidPtr duid2 = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0xff)));
    time_t now = time(NULL);
    Lease6Ptr used(new Lease6(Lease6::LEASE_IA_NA, IOAddress("2001:db8:1::1f"),
                              duid2, 1, 2, 3, 4, now, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // another client comes in and request an address that is in pool, but
    // unfortunately it is used already. The same address must not be allocated
    // twice.
    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                               IOAddress("2001:db8:1::1f"),
                                               false);
    // check that we got a lease
    ASSERT_TRUE(lease);

    // allocated address must be different
    EXPECT_TRUE(used->addr_.toText() != lease->addr_.toText());

    // we should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "2001:db8:1::1f");

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine6Test, allocBogusHint6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Client would like to get a 3000::abc lease, which does not belong to any
    // supported lease. Allocation engine should ignore it and carry on
    // with the normal allocation
    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                               IOAddress("3000::abc"),
                                               false);
    // check that we got a lease
    ASSERT_TRUE(lease);

    // we should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "3000::abc");

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks that NULL values are handled properly
TEST_F(AllocEngine6Test, allocateAddress6Nulls) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    Lease6Ptr lease = engine->allocateAddress6(Subnet6Ptr(), duid_, iaid_,
                                               IOAddress("::"), false);
    ASSERT_FALSE(lease);

    // Allocations without DUID are not allowed either
    lease = engine->allocateAddress6(subnet_, DuidPtr(), iaid_,
                                     IOAddress("::"), false);
    ASSERT_FALSE(lease);
}


// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine6Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator());

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(candidate));
    }
}


// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space and must start over.
TEST_F(AllocEngine6Test, IterativeAllocator_manyPools6) {
    NakedAllocEngine::IterativeAllocator* alloc = new NakedAllocEngine::IterativeAllocator();

    // let's start from 2, as there is 2001:db8:1::10 - 2001:db8:1::20 pool already.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;

        min << "2001:db8:1::" << hex << i*16 + 1;
        max << "2001:db8:1::" << hex << i*16 + 9;

        Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, IOAddress(min.str()),
                                IOAddress(max.str())));
        // cout << "Adding pool: " << min.str() << "-" << max.str() << endl;
        subnet_->addPool(pool);
    }

    int total = 17 + 8*9; // first pool (::10 - ::20) has 17 addresses in it,
                          // there are 8 extra pools with 9 addresses in each.

    // Let's keep picked addresses here and check their uniqueness.
    std::set<IOAddress> generated_addrs;
    int cnt = 0;
    while (++cnt) {
        IOAddress candidate = alloc->pickAddress(subnet_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(candidate));

        // One way to easily verify that the iterative allocator really works is
        // to uncomment the following line and observe its output that it
        // covers all defined subnets.
        // cout << candidate.toText() << endl;

        if (generated_addrs.find(candidate) == generated_addrs.end()) {
            // we haven't had this
            generated_addrs.insert(candidate);
        } else {
            // we have seen this address before. That should mean that we
            // iterated over all addresses.
            if (generated_addrs.size() == total) {
                // we have exactly the number of address in all pools
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

    delete alloc;
}

// This test checks if really small pools are working
TEST_F(AllocEngine6Test, smallPool6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets6(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet6(subnet_);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress("::"),
                                               false);

    // Check that we got that single lease
    ASSERT_TRUE(lease);

    EXPECT_EQ("2001:db8:1::ad", lease->addr_.toText());

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if all addresses in a pool are currently used, the attempt
// to find out a new lease fails.
TEST_F(AllocEngine6Test, outOfAddresses6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets6(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet6(subnet_);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, other_duid, other_iaid,
                               501, 502, 503, 504, subnet_->getID(), 0));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // There is just a single address in the pool and allocated it to someone
    // else, so the allocation should fail
    Lease6Ptr lease2 = engine->allocateAddress6(subnet_, duid_, iaid_,
                                                IOAddress("::"), false);
    EXPECT_FALSE(lease2);
}

// This test checks if an expired lease can be reused in SOLICIT (fake allocation)
TEST_F(AllocEngine6Test, solicitReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets6(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet6(subnet_);

    // Just a different duid
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, other_duid, other_iaid,
                               501, 502, 503, 504, subnet_->getID(), 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Make sure that we really created expired lease
    ASSERT_TRUE(lease->expired());

    // CASE 1: Asking for any address
    lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress("::"),
                                     true);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(lease);

    // CASE 2: Asking specifically for this address
    lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress(addr.toText()),
                                     true);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());
}

// This test checks if an expired lease can be reused in REQUEST (actual allocation)
TEST_F(AllocEngine6Test, requestReuseExpiredLease6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("2001:db8:1::ad");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets6(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet6(subnet_);

    // Let's create an expired lease
    DuidPtr other_duid = DuidPtr(new DUID(vector<uint8_t>(12, 0xff)));
    const uint32_t other_iaid = 3568;
    const SubnetID other_subnetid = 999;
    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, other_duid, other_iaid,
                               501, 502, 503, 504, other_subnetid, 0));
    lease->cltt_ = time(NULL) - 500; // Allocated 500 seconds ago
    lease->valid_lft_ = 495; // Lease was valid for 495 seconds
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // A client comes along, asking specifically for this address
    lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                     IOAddress(addr.toText()), false);

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Check that the lease is indeed updated in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// --- IPv4 ---

// This test checks if the simple IPv4 allocation can succeed
TEST_F(AllocEngine4Test, simpleAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"), false);

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
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"), true);

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
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("192.0.2.105"),
                                               false);

    // Check that we got a lease
    ASSERT_TRUE(lease);

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
// in pool, but is currently used) can succeed
TEST_F(AllocEngine4Test, allocWithUsedHint4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL);
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2, sizeof(hwaddr2),
                              clientid2, sizeof(clientid2), 1, 2, 3, now, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Another client comes in and request an address that is in pool, but
    // unfortunately it is used already. The same address must not be allocated
    // twice.
    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("192.0.2.106"),
                                               false);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Allocated address must be different
    EXPECT_TRUE(used->addr_.toText() != lease->addr_.toText());

    // We should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "192.0.2.106");

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}


// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngine4Test, allocBogusHint4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Client would like to get a 3000::abc lease, which does not belong to any
    // supported lease. Allocation engine should ignore it and carry on
    // with the normal allocation
    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("10.1.1.1"),
                                               false);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "10.1.1.1");

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}


// This test checks that NULL values are handled properly
TEST_F(AllocEngine4Test, allocateAddress4Nulls) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    Lease4Ptr lease = engine->allocateAddress4(SubnetPtr(), clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"), false);
    EXPECT_FALSE(lease);

    // Allocations without HW address are not allowed
    lease = engine->allocateAddress4(subnet_, clientid_, HWAddrPtr(),
                                     IOAddress("0.0.0.0"), false);
    EXPECT_FALSE(lease);

    // Allocations without client-id are allowed
    clientid_ = ClientIdPtr();
    lease = engine->allocateAddress4(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("0.0.0.0"), false);
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



// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine4Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator());

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, clientid_,
                                                 IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(candidate));
    }
}


// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space and must start over.
TEST_F(AllocEngine4Test, IterativeAllocator_manyPools4) {
    NakedAllocEngine::IterativeAllocator* alloc = new NakedAllocEngine::IterativeAllocator();

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
        IOAddress candidate = alloc->pickAddress(subnet_, clientid_, IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(candidate));

        // One way to easily verify that the iterative allocator really works is
        // to uncomment the following line and observe its output that it
        // covers all defined subnets.
        // cout << candidate.toText() << endl;

        if (generated_addrs.find(candidate) == generated_addrs.end()) {
            // We haven't had this
            generated_addrs.insert(candidate);
        } else {
            // we have seen this address before. That should mean that we
            // iterated over all addresses.
            if (generated_addrs.size() == total) {
                // we have exactly the number of address in all pools
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

    delete alloc;
}


// This test checks if really small pools are working
TEST_F(AllocEngine4Test, smallPool4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.17");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets4(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet4(subnet_);

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                               false);

    // Check that we got that single lease
    ASSERT_TRUE(lease);

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
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.17");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets4(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet4(subnet_);

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL);
    Lease4Ptr lease(new Lease4(addr, hwaddr2, sizeof(hwaddr2), clientid2, sizeof(clientid2),
                               501, 502, 503, now, subnet_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // There is just a single address in the pool and allocated it to someone
    // else, so the allocation should fail

    Lease4Ptr lease2 = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                                IOAddress("0.0.0.0"), false);
    EXPECT_FALSE(lease2);
}

// This test checks if an expired lease can be reused in DISCOVER (fake allocation)
TEST_F(AllocEngine4Test, discoverReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.15");
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets4(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet4(subnet_);

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago
    Lease4Ptr lease(new Lease4(addr, clientid2, sizeof(clientid2), hwaddr2, sizeof(hwaddr2),
                               495, 100, 200, now, subnet_->getID()));
    // Lease was assigned 500 seconds ago, but its valid lifetime is 495, so it
    // is expired already
    ASSERT_TRUE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // CASE 1: Asking for any address
    lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                     true);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease4(lease);

    // CASE 2: Asking specifically for this address
    lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_, IOAddress(addr.toText()),
                                     true);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());
}

// This test checks if an expired lease can be reused in REQUEST (actual allocation)
TEST_F(AllocEngine4Test, requestReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.105");

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago
    Lease4Ptr lease(new Lease4(addr, clientid2, sizeof(clientid2), hwaddr2, sizeof(hwaddr2),
                               495, 100, 200, now, subnet_->getID()));
    // lease was assigned 500 seconds ago, but its valid lifetime is 495, so it
    // is expired already
    ASSERT_TRUE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // A client comes along, asking specifically for this address
    lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                     IOAddress(addr.toText()), false);

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Check that the lease is indeed updated in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if a lease is really renewed when renewLease4 method is
// called
TEST_F(AllocEngine4Test, renewLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.102");
    const uint32_t old_lifetime = 100;
    const uint32_t old_t1 = 50;
    const uint32_t old_t2 = 75;
    const time_t old_timestamp = time(NULL) - 45; // Allocated 45 seconds ago

    // Just a different hw/client-id for the second client
    const uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    const uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    Lease4Ptr lease(new Lease4(addr, clientid2, sizeof(clientid2), hwaddr2,
                               sizeof(hwaddr2), old_lifetime, old_t1, old_t2,
                               old_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Lease was assigned 45 seconds ago and is valid for 100 seconds. Let's
    // renew it.
    ASSERT_FALSE(lease->expired());
    lease = engine->renewLease4(subnet_, clientid_, hwaddr_, lease, false);
    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Check that the lease matches subnet_, hwaddr_,clientid_ parameters
    checkLease4(lease);

    // Check that the lease is indeed updated in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

}; // end of anonymous namespace
