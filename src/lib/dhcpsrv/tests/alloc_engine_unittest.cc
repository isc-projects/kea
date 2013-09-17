// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <hooks/server_hooks.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks_manager.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <time.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Allocation engine with some internal methods exposed
class NakedAllocEngine : public AllocEngine {
public:

    /// @brief the sole constructor
    /// @param engine_type specifies engine type (e.g. iterative)
    /// @param attempts number of lease selection attempts before giving up
    /// @param ipv6 specifies if the engine is IPv6 or IPv4
    NakedAllocEngine(AllocEngine::AllocType engine_type,
                     unsigned int attempts, bool ipv6 = true)
        :AllocEngine(engine_type, attempts, ipv6) {
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

    /// @brief attempts to convert leases collection to a single lease
    ///
    /// This operation makes sense if there is at most one lease in the
    /// collection. Otherwise it will throw.
    ///
    /// @param col collection of leases (zero or one leases allowed)
    /// @throw MultipleRecords if there is more than one lease
    /// @return Lease6 pointer (or NULL if collection was empty)
    Lease6Ptr expectOneLease(const Lease6Collection& col) {
        if (col.size() > 1) {
            isc_throw(MultipleRecords, "More than one lease found in collection");
        }
        if (col.empty()) {
            return (Lease6Ptr());
        }
        return (*col.begin());
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

    virtual ~AllocEngine6Test() {
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
        // Check that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());
        EXPECT_TRUE(subnet_->inRange(lease->addr_));
        EXPECT_TRUE(subnet_->inPool(lease->addr_));

        // Check that it has proper parameters
        EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);
        EXPECT_EQ(subnet_->getT1(), lease->t1_);
        EXPECT_EQ(subnet_->getT2(), lease->t2_);
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

    virtual ~AllocEngine4Test() {
        factory_.destroy();
    }

    ClientIdPtr clientid_;    ///< Client-identifier (value used in tests)
    HWAddrPtr hwaddr_;        ///< Hardware address (value used in tests)
    Subnet4Ptr subnet_;       ///< Subnet4 (used in tests)
    Pool4Ptr pool_;           ///< Pool belonging to subnet_
    LeaseMgrFactory factory_; ///< Pointer to LeaseMgr factory
    Lease4Ptr old_lease_;     ///< Holds previous instance of the lease.
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

    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", false,
                    CalloutHandlePtr())));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks if the fake allocation (for SOLICIT) can succeed
TEST_F(AllocEngine6Test, fakeAlloc6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", true,
                    CalloutHandlePtr())));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is NOT in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_FALSE(from_mgr);
}

// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngine6Test, allocWithValidHint6) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                            duid_, iaid_, IOAddress("2001:db8:1::15"), false,
                            false, "", false, CalloutHandlePtr())));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We should get what we asked for
    EXPECT_EQ(lease->addr_.toText(), "2001:db8:1::15");

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
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

    // Let's create a lease and put it in the LeaseMgr
    DuidPtr duid2 = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0xff)));
    time_t now = time(NULL);
    Lease6Ptr used(new Lease6(Lease6::LEASE_IA_NA, IOAddress("2001:db8:1::1f"),
                              duid2, 1, 2, 3, 4, now, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Another client comes in and request an address that is in pool, but
    // unfortunately it is used already. The same address must not be allocated
    // twice.
    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("2001:db8:1::1f"), false, false, "",
                    false, CalloutHandlePtr())));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Allocated address must be different
    EXPECT_TRUE(used->addr_.toText() != lease->addr_.toText());

    // We should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "2001:db8:1::1f");

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
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
    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("3000::abc"), false, false, "",
                    false, CalloutHandlePtr())));

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "3000::abc");

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
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
    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(
                    Subnet6Ptr(), duid_, iaid_, IOAddress("::"), false, false,
                    "", false, CalloutHandlePtr())));
    ASSERT_FALSE(lease);

    // Allocations without DUID are not allowed either
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    DuidPtr(), iaid_, IOAddress("::"), false, false, "", false,
                    CalloutHandlePtr())));
    ASSERT_FALSE(lease);
}


// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngine6Test, IterativeAllocator) {
    boost::scoped_ptr<NakedAllocEngine::Allocator>
        alloc(new NakedAllocEngine::IterativeAllocator(Pool6::TYPE_IA));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(candidate));
    }
}


// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space and must start over.
TEST_F(AllocEngine6Test, IterativeAllocator_manyPools6) {
    NakedAllocEngine::IterativeAllocator alloc(Pool6::TYPE_IA);

    // let's start from 2, as there is 2001:db8:1::10 - 2001:db8:1::20 pool already.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;

        min << "2001:db8:1::" << hex << i*16 + 1;
        max << "2001:db8:1::" << hex << i*16 + 9;

        Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, IOAddress(min.str()),
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
        EXPECT_TRUE(subnet_->inPool(candidate));

        // One way to easily verify that the iterative allocator really works is
        // to uncomment the following line and observe its output that it
        // covers all defined subnets.
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
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteSubnets6(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
    pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet6(subnet_);

    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", false,
                    CalloutHandlePtr())));

    // Check that we got that single lease
    ASSERT_TRUE(lease);

    EXPECT_EQ("2001:db8:1::ad", lease->addr_.toText());

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
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
    Lease6Ptr lease2;
    EXPECT_NO_THROW(lease2 = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", false,
                    CalloutHandlePtr())));
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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", true,
                    CalloutHandlePtr())));
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(lease);

    // CASE 2: Asking specifically for this address
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress(addr.toText()), false, false, "",
                    true, CalloutHandlePtr())));

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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress(addr.toText()), false, false, "",
                    false, CalloutHandlePtr())));

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Check that the lease is indeed updated in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease6::LEASE_IA_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// --- IPv4 ---

// This test checks if the simple IPv4 allocation can succeed
TEST_F(AllocEngine4Test, simpleAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               false, true,
                                               "somehost.example.com.",
                                               false, CalloutHandlePtr(),
                                               old_lease_);
    // The new lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               false, true, "host.example.com.",
                                               true, CalloutHandlePtr(),
                                               old_lease_);

    // The new lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("192.0.2.105"),
                                               true, true, "host.example.com.",
                                               false, CalloutHandlePtr(),
                                               old_lease_);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We have allocated the new lease, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
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
                                               false, false, "",
                                               false, CalloutHandlePtr(),
                                               old_lease_);

    // New lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Client would like to get a 3000::abc lease, which does not belong to any
    // supported lease. Allocation engine should ignore it and carry on
    // with the normal allocation
    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("10.1.1.1"),
                                               false, false, "",
                                               false, CalloutHandlePtr(),
                                               old_lease_);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We have allocated a new lease, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    Lease4Ptr lease = engine->allocateAddress4(SubnetPtr(), clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               false, false, "",
                                               false, CalloutHandlePtr(),
                                               old_lease_);
    EXPECT_FALSE(lease);

    // Allocations without HW address are not allowed
    lease = engine->allocateAddress4(subnet_, clientid_, HWAddrPtr(),
                                     IOAddress("0.0.0.0"),
                                     false, false, "",
                                     false, CalloutHandlePtr(),
                                     old_lease_);
    EXPECT_FALSE(lease);
    EXPECT_FALSE(old_lease_);

    // Allocations without client-id are allowed
    clientid_ = ClientIdPtr();
    lease = engine->allocateAddress4(subnet_, ClientIdPtr(), hwaddr_,
                                     IOAddress("0.0.0.0"),
                                     true, true, "myhost.example.com.",
                                     false, CalloutHandlePtr(),
                                     old_lease_);
    // Check that we got a lease
    ASSERT_TRUE(lease);
    // New lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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
        alloc(new NakedAllocEngine::IterativeAllocator(Pool6::TYPE_V4));

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
    NakedAllocEngine::IterativeAllocator alloc(Pool6::TYPE_V4);

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
        EXPECT_TRUE(subnet_->inPool(candidate));

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
    cfg_mgr.deleteSubnets4(); // Get rid of the default test configuration

    // Create configuration similar to other tests, but with a single address pool
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    pool_ = Pool4Ptr(new Pool4(addr, addr)); // just a single address
    subnet_->addPool(pool_);
    cfg_mgr.addSubnet4(subnet_);

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               true, true, "host.example.com.",
                                               false, CalloutHandlePtr(),
                                               old_lease_);

    // Check that we got that single lease
    ASSERT_TRUE(lease);

    // We have allocated new lease, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

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
    Lease4Ptr lease(new Lease4(addr, hwaddr2, sizeof(hwaddr2), clientid2,
                               sizeof(clientid2), 501, 502, 503, now,
                               subnet_->getID()));
    lease->cltt_ = time(NULL) - 10; // Allocated 10 seconds ago
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // There is just a single address in the pool and allocated it to someone
    // else, so the allocation should fail

    Lease4Ptr lease2 = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                                IOAddress("0.0.0.0"),
                                                false, false, "",
                                                false, CalloutHandlePtr(),
                                                old_lease_);
    EXPECT_FALSE(lease2);
    EXPECT_FALSE(old_lease_);
}

// This test checks if an expired lease can be reused in DISCOVER (fake allocation)
TEST_F(AllocEngine4Test, discoverReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
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
    Lease4Ptr lease(new Lease4(addr, clientid2, sizeof(clientid2),
                               hwaddr2, sizeof(hwaddr2),
                               495, 100, 200, now, subnet_->getID()));
    // Copy the lease, so as it can be compared with the old lease returned
    // by the allocation engine.
    Lease4 original_lease(*lease);

    // Lease was assigned 500 seconds ago, but its valid lifetime is 495, so it
    // is expired already
    ASSERT_TRUE(lease->expired());
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // CASE 1: Asking for any address
    lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                     IOAddress("0.0.0.0"),
                                     false, false, "",
                                     true, CalloutHandlePtr(),
                                     old_lease_);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // We are reusing expired lease, the old (expired) instance should be
    // returned. The returned instance should be the same as the original
    // lease.
    ASSERT_TRUE(old_lease_);
    EXPECT_TRUE(original_lease == *old_lease_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease4(lease);

    // CASE 2: Asking specifically for this address
    lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                     IOAddress(addr.toText()),
                                     false, false, "",
                                     true, CalloutHandlePtr(),
                                     old_lease_);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // We are updating expired lease. The copy of the old lease should be
    // returned and it should be equal to the original lease.
    ASSERT_TRUE(old_lease_);
    EXPECT_TRUE(*old_lease_ == original_lease);
}

// This test checks if an expired lease can be reused in REQUEST (actual allocation)
TEST_F(AllocEngine4Test, requestReuseExpiredLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    IOAddress addr("192.0.2.105");

    // Just a different hw/client-id for the second client
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    time_t now = time(NULL) - 500; // Allocated 500 seconds ago
    Lease4Ptr lease(new Lease4(addr, clientid2, sizeof(clientid2), hwaddr2,
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
    lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                     IOAddress(addr.toText()),
                                     false, true, "host.example.com.",
                                     false, CalloutHandlePtr(),
                                     old_lease_);

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr.toText(), lease->addr_.toText());

    // Check that the lease is indeed updated in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);

    // The allocation engine should return a copy of the old lease. This
    // lease should be equal to the original lease.
    ASSERT_TRUE(old_lease_);
    EXPECT_TRUE(*old_lease_ == original_lease);
}

/// @todo write renewLease6

// This test checks if a lease is really renewed when renewLease4 method is
// called
TEST_F(AllocEngine4Test, renewLease4) {
    boost::scoped_ptr<AllocEngine> engine;
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
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
    lease = engine->renewLease4(subnet_, clientid_, hwaddr_, true,
                                true, "host.example.com.", lease,
                                callout_handle, false);
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

/// @brief helper class used in Hooks testing in AllocEngine6
///
/// It features a couple of callout functions and buffers to store
/// the data that is accessible via callouts.
class HookAllocEngine6Test : public AllocEngine6Test {
public:
    HookAllocEngine6Test() {
        resetCalloutBuffers();
    }

    virtual ~HookAllocEngine6Test() {
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
            "lease6_select");
    }

    /// @brief clears out buffers, so callouts can store received arguments
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_subnet6_.reset();
        callback_fake_allocation_ = false;
        callback_lease6_.reset();
        callback_argument_names_.clear();
        callback_addr_original_ = IOAddress("::");
        callback_addr_updated_ = IOAddress("::");
    }

    /// callback that stores received callout name and received values
    static int
    lease6_select_callout(CalloutHandle& callout_handle) {

        callback_name_ = string("lease6_select");

        callout_handle.getArgument("subnet6", callback_subnet6_);
        callout_handle.getArgument("fake_allocation", callback_fake_allocation_);
        callout_handle.getArgument("lease6", callback_lease6_);

        callback_addr_original_ = callback_lease6_->addr_;

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// callback that overrides the lease with different values
    static int
    lease6_select_different_callout(CalloutHandle& callout_handle) {

        // Let's call the basic callout, so it can record all parameters
        lease6_select_callout(callout_handle);

        // Now we need to tweak the least a bit
        Lease6Ptr lease;
        callout_handle.getArgument("lease6", lease);
        callback_addr_updated_ = addr_override_;
        lease->addr_ = callback_addr_updated_;
        lease->t1_ = t1_override_;
        lease->t2_ = t2_override_;
        lease->preferred_lft_ = pref_override_;
        lease->valid_lft_ = valid_override_;

        return (0);
    }

    // Values to be used in callout to override lease6 content
    static const IOAddress addr_override_;
    static const uint32_t t1_override_;
    static const uint32_t t2_override_;
    static const uint32_t pref_override_;
    static const uint32_t valid_override_;

    // Callback will store original and overridden values here
    static IOAddress callback_addr_original_;
    static IOAddress callback_addr_updated_;

    // Buffers (callback will store received values here)
    static string callback_name_;
    static Subnet6Ptr callback_subnet6_;
    static Lease6Ptr callback_lease6_;
    static bool callback_fake_allocation_;
    static vector<string> callback_argument_names_;
};

// For some reason intialization within a class makes the linker confused.
// linker complains about undefined references if they are defined within
// the class declaration.
const IOAddress HookAllocEngine6Test::addr_override_("2001:db8::abcd");
const uint32_t HookAllocEngine6Test::t1_override_ = 6000;
const uint32_t HookAllocEngine6Test::t2_override_ = 7000;
const uint32_t HookAllocEngine6Test::pref_override_ = 8000;
const uint32_t HookAllocEngine6Test::valid_override_ = 9000;

IOAddress HookAllocEngine6Test::callback_addr_original_("::");
IOAddress HookAllocEngine6Test::callback_addr_updated_("::");

string HookAllocEngine6Test::callback_name_;
Subnet6Ptr HookAllocEngine6Test::callback_subnet6_;
Lease6Ptr HookAllocEngine6Test::callback_lease6_;
bool HookAllocEngine6Test::callback_fake_allocation_;
vector<string> HookAllocEngine6Test::callback_argument_names_;

// This test checks if the lease6_select callout is executed and expected
// parameters as passed.
TEST_F(HookAllocEngine6Test, lease6_select) {

    // Note: The following order is working as expected:
    // 1. create AllocEngine (that register hook points)
    // 2. call loadLibraries()
    //
    // This order, however, causes segfault in HooksManager
    // 1. call loadLibraries()
    // 2. create AllocEngine (that register hook points)

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_select", lease6_select_callout));

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", false,
                    callout_handle)));
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check that callouts were indeed called
    EXPECT_EQ("lease6_select", callback_name_);

    // Now check that the lease in LeaseMgr has the same parameters
    ASSERT_TRUE(callback_lease6_);
    detailCompareLease(callback_lease6_, from_mgr);

    ASSERT_TRUE(callback_subnet6_);
    EXPECT_EQ(subnet_->toText(), callback_subnet6_->toText());

    EXPECT_FALSE(callback_fake_allocation_);

    // Check if all expected parameters are reported. It's a bit tricky, because
    // order may be different. If the test starts failing, because someone tweaked
    // hooks engine, we'll have to implement proper vector matching (ignoring order)
    vector<string> expected_argument_names;
    expected_argument_names.push_back("fake_allocation");
    expected_argument_names.push_back("lease6");
    expected_argument_names.push_back("subnet6");

    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());

    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);
}

// This test checks if lease6_select callout is able to override the values
// in a lease6.
TEST_F(HookAllocEngine6Test, change_lease6_select) {

    // Make sure that the overridden values are different than the ones from
    // subnet originally used to create the lease
    ASSERT_NE(t1_override_, subnet_->getT1());
    ASSERT_NE(t2_override_, subnet_->getT2());
    ASSERT_NE(pref_override_, subnet_->getPreferred());
    ASSERT_NE(valid_override_, subnet_->getValid());
    ASSERT_FALSE(subnet_->inRange(addr_override_));

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_select", lease6_select_different_callout));

    // Normally, dhcpv6_srv would passed the handle when calling allocateAddress6,
    // but in tests we need to create it on our own.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    // Call allocateAddress6. Callouts should be triggered here.
    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateAddress6(subnet_,
                    duid_, iaid_, IOAddress("::"), false, false, "", false,
                    callout_handle)));
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // See if the values overridden by callout are there
    EXPECT_TRUE(lease->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, lease->t1_);
    EXPECT_EQ(t2_override_, lease->t2_);
    EXPECT_EQ(pref_override_, lease->preferred_lft_);
    EXPECT_EQ(valid_override_, lease->valid_lft_);

    // Now check if the lease is in the database
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check if values in the database are overridden
    EXPECT_TRUE(from_mgr->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, from_mgr->t1_);
    EXPECT_EQ(t2_override_, from_mgr->t2_);
    EXPECT_EQ(pref_override_, from_mgr->preferred_lft_);
    EXPECT_EQ(valid_override_, from_mgr->valid_lft_);
}


/// @brief helper class used in Hooks testing in AllocEngine4
///
/// It features a couple of callout functions and buffers to store
/// the data that is accessible via callouts.
///
/// Note: lease4_renew callout is tested from DHCPv4 server.
/// See HooksDhcpv4SrvTest.basic_lease4_renew in
/// src/bin/dhcp4/tests/dhcp4_srv_unittest.cc
class HookAllocEngine4Test : public AllocEngine4Test {
public:
    HookAllocEngine4Test() {
        resetCalloutBuffers();
    }

    virtual ~HookAllocEngine4Test() {
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
            "lease4_select");
    }

    /// @brief clears out buffers, so callouts can store received arguments
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_subnet4_.reset();
        callback_fake_allocation_ = false;
        callback_lease4_.reset();
        callback_argument_names_.clear();
        callback_addr_original_ = IOAddress("::");
        callback_addr_updated_ = IOAddress("::");
    }

    /// callback that stores received callout name and received values
    static int
    lease4_select_callout(CalloutHandle& callout_handle) {

        callback_name_ = string("lease4_select");

        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("fake_allocation", callback_fake_allocation_);
        callout_handle.getArgument("lease4", callback_lease4_);

        callback_addr_original_ = callback_lease4_->addr_;

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// callback that overrides the lease with different values
    static int
    lease4_select_different_callout(CalloutHandle& callout_handle) {

        // Let's call the basic callout, so it can record all parameters
        lease4_select_callout(callout_handle);

        // Now we need to tweak the least a bit
        Lease4Ptr lease;
        callout_handle.getArgument("lease4", lease);
        callback_addr_updated_ = addr_override_;
        lease->addr_ = callback_addr_updated_;
        lease->t1_ = t1_override_;
        lease->t2_ = t2_override_;
        lease->valid_lft_ = valid_override_;

        return (0);
    }

    // Values to be used in callout to override lease4 content
    static const IOAddress addr_override_;
    static const uint32_t t1_override_;
    static const uint32_t t2_override_;
    static const uint32_t valid_override_;

    // Callback will store original and overridden values here
    static IOAddress callback_addr_original_;
    static IOAddress callback_addr_updated_;

    // Buffers (callback will store received values here)
    static string callback_name_;
    static Subnet4Ptr callback_subnet4_;
    static Lease4Ptr callback_lease4_;
    static bool callback_fake_allocation_;
    static vector<string> callback_argument_names_;
};

// For some reason intialization within a class makes the linker confused.
// linker complains about undefined references if they are defined within
// the class declaration.
const IOAddress HookAllocEngine4Test::addr_override_("192.0.3.1");
const uint32_t HookAllocEngine4Test::t1_override_ = 4000;
const uint32_t HookAllocEngine4Test::t2_override_ = 7000;
const uint32_t HookAllocEngine4Test::valid_override_ = 9000;

IOAddress HookAllocEngine4Test::callback_addr_original_("::");
IOAddress HookAllocEngine4Test::callback_addr_updated_("::");

string HookAllocEngine4Test::callback_name_;
Subnet4Ptr HookAllocEngine4Test::callback_subnet4_;
Lease4Ptr HookAllocEngine4Test::callback_lease4_;
bool HookAllocEngine4Test::callback_fake_allocation_;
vector<string> HookAllocEngine4Test::callback_argument_names_;

// This test checks if the lease4_select callout is executed and expected
// parameters as passed.
TEST_F(HookAllocEngine4Test, lease4_select) {

    // Note: The following order is working as expected:
    // 1. create AllocEngine (that register hook points)
    // 2. call loadLibraries()
    //
    // This order, however, causes segfault in HooksManager
    // 1. call loadLibraries()
    // 2. create AllocEngine (that register hook points)

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_select", lease4_select_callout));

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               false, false, "",
                                               false, callout_handle,
                                               old_lease_);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check that callouts were indeed called
    EXPECT_EQ("lease4_select", callback_name_);

    // Now check that the lease in LeaseMgr has the same parameters
    ASSERT_TRUE(callback_lease4_);
    detailCompareLease(callback_lease4_, from_mgr);

    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(subnet_->toText(), callback_subnet4_->toText());

    EXPECT_EQ(callback_fake_allocation_, false);

    // Check if all expected parameters are reported. It's a bit tricky, because
    // order may be different. If the test starts failing, because someone tweaked
    // hooks engine, we'll have to implement proper vector matching (ignoring order)
    vector<string> expected_argument_names;
    expected_argument_names.push_back("fake_allocation");
    expected_argument_names.push_back("lease4");
    expected_argument_names.push_back("subnet4");
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);
}

// This test checks if lease4_select callout is able to override the values
// in a lease4.
TEST_F(HookAllocEngine4Test, change_lease4_select) {

    // Make sure that the overridden values are different than the ones from
    // subnet originally used to create the lease
    ASSERT_NE(t1_override_, subnet_->getT1());
    ASSERT_NE(t2_override_, subnet_->getT2());
    ASSERT_NE(valid_override_, subnet_->getValid());
    ASSERT_FALSE(subnet_->inRange(addr_override_));

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_select", lease4_select_different_callout));

    // Normally, dhcpv4_srv would passed the handle when calling allocateAddress4,
    // but in tests we need to create it on our own.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    // Call allocateAddress4. Callouts should be triggered here.
    Lease4Ptr lease = engine->allocateAddress4(subnet_, clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               false, false, "",
                                               false, callout_handle,
                                               old_lease_);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // See if the values overridden by callout are there
    EXPECT_TRUE(lease->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, lease->t1_);
    EXPECT_EQ(t2_override_, lease->t2_);
    EXPECT_EQ(valid_override_, lease->valid_lft_);

    // Now check if the lease is in the database
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check if values in the database are overridden
    EXPECT_TRUE(from_mgr->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, from_mgr->t1_);
    EXPECT_EQ(t2_override_, from_mgr->t2_);
    EXPECT_EQ(valid_override_, from_mgr->valid_lft_);
}

}; // End of anonymous namespace
