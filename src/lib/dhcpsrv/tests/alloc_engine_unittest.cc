// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
    using AllocEngine::getAllocator;

    /// @brief IterativeAllocator with internal methods exposed
    class NakedIterativeAllocator: public AllocEngine::IterativeAllocator {
    public:

        /// @brief constructor
        /// @param type pool types that will be interated
        NakedIterativeAllocator(Lease::Type type)
            :IterativeAllocator(type) {
        }

        using AllocEngine::IterativeAllocator::increaseAddress;
        using AllocEngine::IterativeAllocator::increasePrefix;
    };
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
        CfgMgr::instance().clear();

        duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        iaid_ = 42;

        // Initialize a subnet and short address pool.
        initSubnet(IOAddress("2001:db8:1::"),
                   IOAddress("2001:db8:1::10"),
                   IOAddress("2001:db8:1::20"));

        initFqdn("", false, false);

        factory_.create("type=memfile universe=6 persist=false");
    }

    /// @brief Configures a subnet and adds one pool to it.
    ///
    /// This function removes existing v6 subnets before configuring
    /// a new one.
    ///
    /// @param subnet Address of a subnet to be configured.
    /// @param pool_start First address in the address pool.
    /// @param pool_end Last address in the address pool.
    void initSubnet(const IOAddress& subnet, const IOAddress& pool_start,
                    const IOAddress& pool_end) {
        CfgMgr& cfg_mgr = CfgMgr::instance();

        subnet_ = Subnet6Ptr(new Subnet6(subnet, 56, 1, 2, 3, 4));
        pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, pool_start, pool_end));

        subnet_->addPool(pool_);

        pd_pool_ = Pool6Ptr(new Pool6(Lease::TYPE_PD, subnet, 56, 64));
        subnet_->addPool(pd_pool_);

        cfg_mgr.getStagingCfg()->getCfgSubnets6()->add(subnet_);
        cfg_mgr.commit();

    }

    /// @brief Initializes FQDN data for a test.
    ///
    /// The initialized values are used by the test fixture class members to
    /// verify the correctness of a lease.
    ///
    /// @param hostname Hostname to be assigned to a lease.
    /// @param fqdn_fwd Indicates whether or not to perform forward DNS update
    /// for a lease.
    /// @param fqdn_fwd Indicates whether or not to perform reverse DNS update
    /// for a lease.
    void initFqdn(const std::string& hostname, const bool fqdn_fwd,
                  const bool fqdn_rev) {
        hostname_ = hostname;
        fqdn_fwd_ = fqdn_fwd;
        fqdn_rev_ = fqdn_rev;
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
    /// @param exp_type expected lease type
    /// @param exp_pd_len expected prefix length
    void checkLease6(const Lease6Ptr& lease, Lease::Type exp_type,
                     uint8_t exp_pd_len = 128) {

        // that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());
        EXPECT_TRUE(subnet_->inRange(lease->addr_));
        EXPECT_TRUE(subnet_->inPool(exp_type, lease->addr_));

        // that it have proper parameters
        EXPECT_EQ(exp_type, lease->type_);
        EXPECT_EQ(iaid_, lease->iaid_);
        EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);
        EXPECT_EQ(subnet_->getPreferred(), lease->preferred_lft_);
        EXPECT_EQ(subnet_->getT1(), lease->t1_);
        EXPECT_EQ(subnet_->getT2(), lease->t2_);
        EXPECT_EQ(exp_pd_len, lease->prefixlen_);
        EXPECT_EQ(fqdn_fwd_, lease->fqdn_fwd_);
        EXPECT_EQ(fqdn_rev_, lease->fqdn_rev_);
        EXPECT_EQ(hostname_, lease->hostname_);
        EXPECT_TRUE(*lease->duid_ == *duid_);
        /// @todo: check cltt
    }

    /// @brief Checks if specified address is increased properly
    ///
    /// Method uses gtest macros to mark check failure.
    ///
    /// @param alloc IterativeAllocator that is tested
    /// @param input address to be increased
    /// @param exp_output expected address after increase
    void
    checkAddrIncrease(NakedAllocEngine::NakedIterativeAllocator& alloc,
                      std::string input, std::string exp_output) {
        EXPECT_EQ(exp_output, alloc.increaseAddress(IOAddress(input)).toText());
    }

    /// @brief Checks if increasePrefix() works as expected
    ///
    /// Method uses gtest macros to mark check failure.
    ///
    /// @param alloc allocator to be tested
    /// @param input IPv6 prefix (as a string)
    /// @param prefix_len prefix len
    /// @param exp_output expected output (string)
    void
    checkPrefixIncrease(NakedAllocEngine::NakedIterativeAllocator& alloc,
                        std::string input, uint8_t prefix_len,
                        std::string exp_output) {
        EXPECT_EQ(exp_output, alloc.increasePrefix(IOAddress(input), prefix_len)
                  .toText());
    }

    /// @brief Checks if the simple allocation can succeed
    ///
    /// The type of lease is determined by pool type (pool->getType()
    ///
    /// @param pool pool from which the lease will be allocated from
    /// @param hint address to be used as a hint
    /// @param fake true - this is fake allocation (SOLICIT)
    /// @return allocated lease (or NULL)
    Lease6Ptr simpleAlloc6Test(const Pool6Ptr& pool, const IOAddress& hint,
                               bool fake) {
        Lease::Type type = pool->getType();
        uint8_t expected_len = pool->getLength();

        boost::scoped_ptr<AllocEngine> engine;
        EXPECT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                     100)));
        // We can't use ASSERT macros in non-void methods
        EXPECT_TRUE(engine);
        if (!engine) {
            return (Lease6Ptr());
        }

        Lease6Ptr lease;
        EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                        duid_, iaid_, hint, type, false, false,
                        "", fake, CalloutHandlePtr(), old_leases_, HWAddrPtr())));

        // Check that we got a lease
        EXPECT_TRUE(lease);
        if (!lease) {
            return (Lease6Ptr());
        }

        // Do all checks on the lease
        checkLease6(lease, type, expected_len);

        // Check that the lease is indeed in LeaseMgr
        Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(type,
                                                                   lease->addr_);
        if (!fake) {
            // This is a real (REQUEST) allocation, the lease must be in the DB
            EXPECT_TRUE(from_mgr);
            if (!from_mgr) {
                return (Lease6Ptr());
            }

            // Now check that the lease in LeaseMgr has the same parameters
            detailCompareLease(lease, from_mgr);
        } else {
            // This is a fake (SOLICIT) allocation, the lease must not be in DB
            EXPECT_FALSE(from_mgr);
            if (from_mgr) {
                return (Lease6Ptr());
            }
        }

        return (lease);
    }

    /// @brief Checks if the address allocation with a hint that is in range,
    ///        in pool, but is currently used, can succeed
    ///
    /// Method uses gtest macros to mark check failure.
    ///
    /// @param type lease type
    /// @param used_addr address should be preallocated (simulates prior
    ///        allocation by some other user)
    /// @param requested address requested by the client
    /// @param expected_pd_len expected PD len (128 for addresses)
    void allocWithUsedHintTest(Lease::Type type, IOAddress used_addr,
                               IOAddress requested, uint8_t expected_pd_len) {
        boost::scoped_ptr<AllocEngine> engine;
        ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                     100)));
        ASSERT_TRUE(engine);

        // Let's create a lease and put it in the LeaseMgr
        DuidPtr duid2 = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0xff)));
        time_t now = time(NULL);
        Lease6Ptr used(new Lease6(type, used_addr,
                                  duid2, 1, 2, 3, 4, now, subnet_->getID()));
        ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

        // Another client comes in and request an address that is in pool, but
        // unfortunately it is used already. The same address must not be allocated
        // twice.
        Lease6Ptr lease;
        EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                        duid_, iaid_, requested, type, false, false, "", false,
                        CalloutHandlePtr(), old_leases_, HWAddrPtr())));

        // Check that we got a lease
        ASSERT_TRUE(lease);

        // Allocated address must be different
        EXPECT_NE(used_addr, lease->addr_);

        // We should NOT get what we asked for, because it is used already
        EXPECT_NE(requested, lease->addr_);

        // Do all checks on the lease
        checkLease6(lease, type, expected_pd_len);

        // Check that the lease is indeed in LeaseMgr
        Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                                   lease->addr_);
        ASSERT_TRUE(from_mgr);

        // Now check that the lease in LeaseMgr has the same parameters
        detailCompareLease(lease, from_mgr);
    }

    /// @brief checks if bogus hint can be ignored and the allocation succeeds
    ///
    /// This test checks if the allocation with a hing that is out of the blue
    /// can succeed. The invalid hint should be ingored completely.
    ///
    /// @param type Lease type
    /// @param hint hint (as send by a client)
    /// @param expectd_pd_len (used in validation)
    void allocBogusHint6(Lease::Type type, IOAddress hint,
                         uint8_t expected_pd_len) {
        boost::scoped_ptr<AllocEngine> engine;
        ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                     100)));
        ASSERT_TRUE(engine);

        // Client would like to get a 3000::abc lease, which does not belong to any
        // supported lease. Allocation engine should ignore it and carry on
        // with the normal allocation
        Lease6Ptr lease;
        EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                        duid_, iaid_, hint, type, false,
                        false, "", false, CalloutHandlePtr(), old_leases_,
                        HWAddrPtr())));

        // Check that we got a lease
        ASSERT_TRUE(lease);

        // We should NOT get what we asked for, because it is used already
        EXPECT_NE(hint, lease->addr_);

        // Do all checks on the lease
        checkLease6(lease, type, expected_pd_len);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);




    }


    virtual ~AllocEngine6Test() {
        factory_.destroy();
    }

    DuidPtr duid_;            ///< client-identifier (value used in tests)
    uint32_t iaid_;           ///< IA identifier (value used in tests)
    Subnet6Ptr subnet_;       ///< subnet6 (used in tests)
    Pool6Ptr pool_;           ///< NA pool belonging to subnet_
    Pool6Ptr pd_pool_;        ///< PD pool belonging to subnet_
    std::string hostname_;    ///< Hostname
    bool fqdn_fwd_;           ///< Perform forward update for a lease.
    bool fqdn_rev_;           ///< Perform reverse update for a lease.
    LeaseMgrFactory factory_; ///< pointer to LeaseMgr factory

    /// @brief Collection of leases being replaced by newly allocated or renewed
    /// leases.
    Lease6Collection old_leases_;
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
        cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);
        cfg_mgr.commit();

        factory_.create("type=memfile universe=4 persist=false");
    }

    /// @brief checks if Lease4 matches expected configuration
    ///
    /// @param lease lease to be checked
    void checkLease4(const Lease4Ptr& lease) {
        // Check that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());
        EXPECT_TRUE(subnet_->inRange(lease->addr_));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));

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
        EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);
        /// @todo: check cltt
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
TEST_F(AllocEngine6Test, simpleAlloc6) {
    simpleAlloc6Test(pool_, IOAddress("::"), false);
}

// This test checks if the simple PD allocation (REQUEST) can succeed
TEST_F(AllocEngine6Test, pdSimpleAlloc6) {
    simpleAlloc6Test(pd_pool_, IOAddress("::"), false);
}

// This test checks if the fake allocation (for SOLICIT) can succeed
TEST_F(AllocEngine6Test, fakeAlloc6) {

    simpleAlloc6Test(pool_, IOAddress("::"), true);
}

// This test checks if the fake PD allocation (for SOLICIT) can succeed
TEST_F(AllocEngine6Test, pdFakeAlloc6) {
    simpleAlloc6Test(pd_pool_, IOAddress("::"), true);
};

// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngine6Test, allocWithValidHint6) {

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("2001:db8:1::15"),
                                       false);

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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(
                    Subnet6Ptr(), duid_, iaid_, IOAddress("::"), Lease::TYPE_NA,
                    false, false, "", false, CalloutHandlePtr(), old_leases_,
                    HWAddrPtr())));
    ASSERT_FALSE(lease);

    // Allocations without DUID are not allowed either
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    DuidPtr(), iaid_, IOAddress("::"), Lease::TYPE_NA, false,
                    false, "", false, CalloutHandlePtr(), old_leases_,
                    HWAddrPtr())));
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

    // Third pool (256 leases, let's check first and last explictly and the
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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, IOAddress("::"), Lease::TYPE_NA, fqdn_fwd_,
                    fqdn_rev_, hostname_, false, CalloutHandlePtr(),
                    old_leases_, HWAddrPtr())));

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
    ASSERT_EQ(1, old_leases_.size());
    EXPECT_FALSE(old_leases_[0]);
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
    EXPECT_NO_THROW(lease2 = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, IOAddress("::"), Lease::TYPE_NA, false, false,
                    "", false, CalloutHandlePtr(), old_leases_, HWAddrPtr())));
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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, IOAddress("::"), Lease::TYPE_NA, fqdn_fwd_,
                    fqdn_rev_, hostname_, true, CalloutHandlePtr(),
                    old_leases_, HWAddrPtr())));
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(lease, Lease::TYPE_NA, 128);

    // CASE 2: Asking specifically for this address
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, addr, Lease::TYPE_NA, false, false, "",
                    true, CalloutHandlePtr(), old_leases_, HWAddrPtr())));

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

    // A client comes along, asking specifically for this address
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, addr, Lease::TYPE_NA, false, false, "",
                    false, CalloutHandlePtr(), old_leases_, HWAddrPtr())));

    // Check that he got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);
    // This reactivated lease should have updated FQDN data.
    EXPECT_TRUE(lease->hostname_.empty());
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);

    // Check that the old lease has been returned.
    Lease6Ptr old_lease = expectOneLease(old_leases_);
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
}

// --- IPv4 ---

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

    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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

    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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

    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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
    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
                                               IOAddress("192.0.2.106"),
                                               false, false, "",
                                               false, CalloutHandlePtr(),
                                               old_lease_);

    // New lease has been allocated, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Allocated address must be different
    EXPECT_NE(used->addr_, lease->addr_);

    // We should NOT get what we asked for, because it is used already
    EXPECT_NE("192.0.2.106", lease->addr_.toText());

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
    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
                                               IOAddress("10.1.1.1"),
                                               false, false, "",
                                               false, CalloutHandlePtr(),
                                               old_lease_);
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // We have allocated a new lease, so the old lease should not exist.
    EXPECT_FALSE(old_lease_);

    // We should NOT get what we asked for, because it is used already
    EXPECT_NE("10.1.1.1", lease->addr_.toText());

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}


// This test checks that NULL values are handled properly
TEST_F(AllocEngine4Test, allocateLease4Nulls) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Allocations without subnet are not allowed
    Lease4Ptr lease = engine->allocateLease4(SubnetPtr(), clientid_, hwaddr_,
                                               IOAddress("0.0.0.0"),
                                               false, false, "",
                                               false, CalloutHandlePtr(),
                                               old_lease_);
    EXPECT_FALSE(lease);

    // Allocations without HW address are not allowed
    lease = engine->allocateLease4(subnet_, clientid_, HWAddrPtr(),
                                     IOAddress("0.0.0.0"),
                                     false, false, "",
                                     false, CalloutHandlePtr(),
                                     old_lease_);
    EXPECT_FALSE(lease);
    EXPECT_FALSE(old_lease_);

    // Allocations without client-id are allowed
    clientid_ = ClientIdPtr();
    lease = engine->allocateLease4(subnet_, ClientIdPtr(), hwaddr_,
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

    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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

    Lease4Ptr lease2 = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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
    lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
                                     IOAddress("0.0.0.0"),
                                     false, false, "",
                                     true, CalloutHandlePtr(),
                                     old_lease_);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // We are reusing expired lease, the old (expired) instance should be
    // returned. The returned instance should be the same as the original
    // lease.
    ASSERT_TRUE(old_lease_);
    EXPECT_TRUE(original_lease == *old_lease_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease4(lease);

    // CASE 2: Asking specifically for this address
    lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
                                     IOAddress(addr),
                                     false, false, "",
                                     true, CalloutHandlePtr(),
                                     old_lease_);
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

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
    lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
                                     IOAddress(addr),
                                     false, true, "host.example.com.",
                                     false, CalloutHandlePtr(),
                                     old_lease_);

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
    const uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    const uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
    Lease4Ptr lease(new Lease4(addr, hwaddr2, clientid2, sizeof(clientid2),
                               old_lifetime, old_t1, old_t2,
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
    EXPECT_EQ(addr, lease->addr_);

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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, IOAddress("::"), Lease::TYPE_NA, false, false,
                    "", false, callout_handle, old_leases_, HWAddrPtr())));
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease6(lease, Lease::TYPE_NA, 128);

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

    // Normally, dhcpv6_srv would passed the handle when calling allocateLeases6,
    // but in tests we need to create it on our own.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    // Call allocateLeases6. Callouts should be triggered here.
    Lease6Ptr lease;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(subnet_,
                    duid_, iaid_, IOAddress("::"), Lease::TYPE_NA, false, false,
                    "", false, callout_handle, old_leases_, HWAddrPtr())));
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

    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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

    // Normally, dhcpv4_srv would passed the handle when calling allocateLease4,
    // but in tests we need to create it on our own.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    // Call allocateLease4. Callouts should be triggered here.
    Lease4Ptr lease = engine->allocateLease4(subnet_, clientid_, hwaddr_,
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
