// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp6.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
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
    /// @param expected_in_subnet whether the lease is expected to be in subnet
    /// @param expected_in_pool whether the lease is expected to be in dynamic
    void checkLease6(const Lease6Ptr& lease, Lease::Type exp_type,
                     uint8_t exp_pd_len = 128, bool expected_in_subnet = true,
                     bool expected_in_pool = true) {

        // that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());

        if (expected_in_subnet) {
            EXPECT_TRUE(subnet_->inRange(lease->addr_));
        } else {
            EXPECT_FALSE(subnet_->inRange(lease->addr_));
        }

        if (expected_in_pool) {
            EXPECT_TRUE(subnet_->inPool(exp_type, lease->addr_));
        } else {
            EXPECT_FALSE(subnet_->inPool(exp_type, lease->addr_));
        }

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
    /// @param in_pool specifies whether the lease is expected to be in pool
    /// @return allocated lease (or NULL)
    Lease6Ptr simpleAlloc6Test(const Pool6Ptr& pool, const IOAddress& hint,
                               bool fake, bool in_pool = true) {
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
        AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, hint, type,
                                        false, false, "", fake);

        EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

        // Check that we got a lease
        EXPECT_TRUE(lease);
        if (!lease) {
            return (Lease6Ptr());
        }

        // Do all checks on the lease
        checkLease6(lease, type, expected_len, in_pool, in_pool);

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

    /// @brief Checks if the allocation can succeed.
    ///
    /// The type of lease is determined by pool type (pool->getType()).
    /// This test is particularly useful in connection with @ref renewTest.
    ///
    /// @param engine a reference to Allocation Engine
    /// @param pool pool from which the lease will be allocated from
    /// @param hint address to be used as a hint
    /// @param fake true - this is fake allocation (SOLICIT)
    /// @param in_pool specifies whether the lease is expected to be in pool
    /// @return allocated lease(s) (may be empty)
    Lease6Collection allocateTest(AllocEngine& engine, const Pool6Ptr& pool,
                                  const IOAddress& hint, bool fake, bool in_pool = true) {
        Lease::Type type = pool->getType();
        uint8_t expected_len = pool->getLength();

        AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, hint, type,
                                        false, false, "", fake);

        Lease6Collection leases;
        EXPECT_NO_THROW(leases = engine.allocateLeases6(ctx));

        for (Lease6Collection::iterator it = leases.begin(); it != leases.end(); ++it) {

            // Do all checks on the lease
            checkLease6(*it, type, expected_len, in_pool, in_pool);

            // Check that the lease is indeed in LeaseMgr
            Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(type,
                                                                       (*it)->addr_);
            if (!fake) {
                // This is a real (REQUEST) allocation, the lease must be in the DB
                EXPECT_TRUE(from_mgr) << "Lease " << from_mgr->addr_.toText()
                                      << " returned by allocateLeases6(), "
                                      << "but was not present in LeaseMgr";
                if (!from_mgr) {
                    return (leases);
                }

                // Now check that the lease in LeaseMgr has the same parameters
                detailCompareLease(*it, from_mgr);
            } else {
                // This is a fake (SOLICIT) allocation, the lease must not be in DB
                EXPECT_FALSE(from_mgr) << "Lease " << from_mgr->addr_.toText()
                                       << " returned by allocateLeases6(), "
                                       << "was present in LeaseMgr (expected to be"
                                       << " not present)";
                if (from_mgr) {
                    return (leases);
                }
            }
        }

        return (leases);
    }

    /// @brief Checks if the allocation can be renewed.
    ///
    /// The type of lease is determined by pool type (pool->getType()).
    /// This test is particularly useful as a follow up to @ref allocateTest.
    ///
    /// @param engine a reference to Allocation Engine
    /// @param pool pool from which the lease will be allocated from
    /// @param hint address to be used as a hint
    /// @param fake true - this is fake allocation (SOLICIT)
    /// @param in_pool specifies whether the lease is expected to be in pool
    /// @return allocated lease(s) (may be empty)
    Lease6Collection renewTest(AllocEngine& engine, const Pool6Ptr& pool,
                               AllocEngine::HintContainer& hints,
                               bool allow_new_leases_in_renewal,
                               bool in_pool = true) {

        Lease::Type type = pool->getType();
        uint8_t expected_len = pool->getLength();

        AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                        type, false, false, "", false);
        ctx.hints_ = hints;
        ctx.query_.reset(new Pkt6(DHCPV6_RENEW, 123));
        ctx.allow_new_leases_in_renewals_ = allow_new_leases_in_renewal;

        Lease6Collection leases = engine.renewLeases6(ctx);


        for (Lease6Collection::iterator it = leases.begin(); it != leases.end(); ++it) {

            // Do all checks on the lease
            checkLease6(*it, type, expected_len, in_pool, in_pool);

            // Check that the lease is indeed in LeaseMgr
            Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(type,
                                                                       (*it)->addr_);

            // This is a real (REQUEST) allocation, the lease must be in the DB
            EXPECT_TRUE(from_mgr) << "Lease " << from_mgr->addr_.toText()
                                  << " returned by allocateLeases6(), "
                                  << "but was not present in LeaseMgr";
            if (!from_mgr) {
                return (leases);
            }

            // Now check that the lease in LeaseMgr has the same parameters
            detailCompareLease(*it, from_mgr);
        }

        return (leases);
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
        AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, requested, type,
                                        false, false, "", false);
        EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

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
    /// can succeed. The invalid hint should be ignored completely.
    ///
    /// @param type Lease type
    /// @param hint hint (as send by a client)
    /// @param expected_pd_len (used in validation)
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
        AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, hint, type, false,
                                        false, "", false);
        EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));

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

    /// @brief Utility function that creates a host reservation
    ///
    /// @param add_to_host_mgr true if the reservation should be added
    /// @param type specifies reservation type
    /// @param addr specifies reserved address or prefix
    /// @param prefix_len prefix length (should be 128 for addresses)
    /// @return created Host object.
    HostPtr
    createHost6(bool add_to_host_mgr, IPv6Resrv::Type type,
                const asiolink::IOAddress& addr, uint8_t prefix_len) {
        HostPtr host(new Host(&duid_->getDuid()[0], duid_->getDuid().size(),
                              Host::IDENT_DUID, SubnetID(0), subnet_->getID(),
                              IOAddress("0.0.0.0")));
        IPv6Resrv resv(type, addr, prefix_len);
        host->addReservation(resv);

        if (add_to_host_mgr) {
            CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
            CfgMgr::instance().commit();
        }
        return (host);
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
};

/// @brief Used in Allocation Engine tests for IPv4
class AllocEngine4Test : public ::testing::Test {
public:

    /// @brief Default constructor
    ///
    /// Sets clientid_, hwaddr_, subnet_, pool_ fields to example values
    /// used in many tests, initializes cfg_mgr configuration and creates
    /// lease database.
    ///
    /// It also re-initializes the Host Manager.
    AllocEngine4Test() {
        // Create fresh instance of the HostMgr, and drop any previous HostMgr
        // state.
        HostMgr::instance().create();

        clientid_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x44)));
        uint8_t mac[] = { 0, 1, 22, 33, 44, 55};

        // Let's use odd hardware type to check if there is no Ethernet
        // hardcoded anywhere.
        hwaddr_ = HWAddrPtr(new HWAddr(mac, sizeof(mac), HTYPE_FDDI));

        // Allocate different MAC address for the tests that require two
        // different MAC addresses.
        ++mac[sizeof(mac) - 1];
        hwaddr2_ = HWAddrPtr(new HWAddr(mac, sizeof (mac), HTYPE_FDDI));

        // instantiate cfg_mgr
        CfgMgr& cfg_mgr = CfgMgr::instance();

        initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.109"));
        cfg_mgr.commit();

        factory_.create("type=memfile universe=4 persist=false");

        // Create a default context. Note that remaining parameters must be
        // assigned when needed.
        ctx_.subnet_ = subnet_;
        ctx_.clientid_ = clientid_;
        ctx_.hwaddr_ = hwaddr_;
        ctx_.callout_handle_ = HooksManager::createCalloutHandle();
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

    /// @brief Create a subnet with a specified pool of addresses.
    ///
    /// @param pool_start First address in the pool.
    /// @param pool_end Last address in the pool.
    void initSubnet(const IOAddress& pool_start, const IOAddress& pool_end) {
        CfgMgr& cfg_mgr = CfgMgr::instance();

        subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
        pool_ = Pool4Ptr(new Pool4(pool_start, pool_end));
        subnet_->addPool(pool_);

        cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet_);
    }

    virtual ~AllocEngine4Test() {
        factory_.destroy();
    }

    ClientIdPtr clientid_;      ///< Client-identifier (value used in tests)
    HWAddrPtr hwaddr_;          ///< Hardware address (value used in tests)
    HWAddrPtr hwaddr2_;         ///< Alternative hardware address.
    Subnet4Ptr subnet_;         ///< Subnet4 (used in tests)
    Pool4Ptr pool_;             ///< Pool belonging to subnet_
    LeaseMgrFactory factory_;   ///< Pointer to LeaseMgr factory
    Lease4Ptr old_lease_;       ///< Holds previous instance of the lease.
    AllocEngine::ClientContext4 ctx_; ///< Context information passed to various
                                     ///< allocation engine functions.
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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx1)));
    ASSERT_FALSE(lease);

    // Allocations without DUID are not allowed either
    AllocEngine::ClientContext6 ctx2(subnet_, DuidPtr(), iaid_, IOAddress("::"),
                                     Lease::TYPE_NA, false, false, "", false);
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
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx1)));
    // Check that we got that single lease
    ASSERT_TRUE(lease);
    EXPECT_EQ(addr, lease->addr_);

    // Do all checks on the lease (if subnet-id, preferred/valid times are ok etc.)
    checkLease6(lease, Lease::TYPE_NA, 128);

    // CASE 2: Asking specifically for this address
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, iaid_, addr, Lease::TYPE_NA,
                                     false, false, "", true);
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

    // A client comes along, asking specifically for this address
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, addr, Lease::TYPE_NA,
                                    false, false, "", false);
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
// Note that DHCPv6 client can, but don't have to send any hints in its
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
// - Client has an in-pool reservation.
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
TEST_F(AllocEngine6Test, reservedAddressOutOfPoolRequestNoHint) {
    // Create reservation for the client. This is out-of-pool reservation,
    // as the pool is 2001:db8:1::10 - 2001:db8:1::20.
    createHost6(true, IPv6Resrv::TYPE_NA, IOAddress("2001:db8::abcd"), 128);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    Lease6Ptr lease = simpleAlloc6Test(pool_, IOAddress("::"), false, false);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8::abcd", lease->addr_.toText());
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
TEST_F(AllocEngine6Test, reservedAddressInPoolReassignedThis) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Client gets an address
    Lease6Ptr lease1 = simpleAlloc6Test(pool_, IOAddress("::"), false);
    ASSERT_TRUE(lease1);

    // Just check that if the client requests again, it will get the same
    // address.
    Lease6Ptr lease2 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease2);
    detailCompareLease(lease1, lease2);

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

    // Just check that if the client requests again, it will get the same
    // address.
    Lease6Ptr lease2 = simpleAlloc6Test(pool_, lease1->addr_, false);
    ASSERT_TRUE(lease2);
    detailCompareLease(lease1, lease2);

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
    Lease6Collection leases1;
    EXPECT_NO_THROW(leases1 = engine.allocateLeases6(ctx1));
    ASSERT_EQ(1, leases1.size());
    EXPECT_EQ("2001:db8:1::babe", leases1[0]->addr_.toText());

    // Double check that repeating the same duid/type/iaid will end up with
    // the same address.
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, iaid_, IOAddress("::"),
                                    pool_->getType(), false, false, "", true);
    Lease6Collection leases2;
    EXPECT_NO_THROW(leases2 = engine.allocateLeases6(ctx2));
    EXPECT_EQ(1, leases2.size());
    EXPECT_EQ("2001:db8:1::babe", leases2[0]->addr_.toText());

    // Ok, now the tricky part. Request allocation for the same duid and type, but
    // different iaid. The second address should be assigned.
    AllocEngine::ClientContext6 ctx3(subnet_, duid_, iaid_ + 1, IOAddress("::"),
                                    pool_->getType(), false, false, "", true);
    Lease6Collection leases3;
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
    Lease6Collection leases1;
    EXPECT_NO_THROW(leases1 = engine.allocateLeases6(ctx1));
    ASSERT_EQ(1, leases1.size());
    EXPECT_EQ("2001:db8:1::babe", leases1[0]->addr_.toText());

    // Double check that repeating the same duid/type/iaid will end up with
    // the same address.
    AllocEngine::ClientContext6 ctx2(subnet_, duid_, iaid_, IOAddress("::"),
                                    pool_->getType(), false, false, "", false);
    Lease6Collection leases2;
    EXPECT_NO_THROW(leases2 = engine.allocateLeases6(ctx2));
    EXPECT_EQ(1, leases2.size());
    EXPECT_EQ("2001:db8:1::babe", leases2[0]->addr_.toText());

    // Ok, now the tricky part. Request allocation for the same duid and type, but
    // different iaid. The second address should be assigned.
    AllocEngine::ClientContext6 ctx3(subnet_, duid_, iaid_ + 1, IOAddress("::"),
                                    pool_->getType(), false, false, "", false);
    Lease6Collection leases3;
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


TEST_F(AllocEngine6Test, prefixRenewal) {


}



/// @todo: The following methods are tested indirectly by allocateLeases6()
/// tests, but could use more direct testing:
/// - AllocEngine::allocateUnreservedLeases6
/// - AllocEngine::allocateReservedLeases6
/// - AllocEngine::removeNonmatchingReservedLeases6
/// - AllocEngine::removeLeases
/// - AllocEngine::removeNonreservedLeases6

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
    ctx_.fwd_dns_update_ = true;
    ctx_.rev_dns_update_ = true;
    ctx_.hostname_ = "host.example.com.";
    ctx_.fake_allocation_ = false;
    lease = engine->renewLease4(lease, ctx_);

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
    Lease4Ptr lease = engine.allocateLease4(subnet_, clientid_, hwaddr_,
                                            IOAddress("0.0.0.0"),
                                            false, false, "",
                                            false, CalloutHandlePtr(),
                                            old_lease_);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // Make sure that the lease has been committed to the lease database.
    // And that the committed lease is equal to the one returned.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);

    // Initially, there was no lease for this client, so the returned old
    // lease should be NULL.
    EXPECT_FALSE(old_lease_);
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
    Lease4Ptr lease = engine.allocateLease4(subnet_, clientid_, hwaddr_,
                                            IOAddress("0.0.0.0"),
                                            false, false, "",
                                            true, CalloutHandlePtr(),
                                            old_lease_);
    ASSERT_TRUE(lease);
    // The allocation engine should return a reserved address.
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    // Client had no lease in the database, so the old lease returned should
    // be NULL.
    EXPECT_FALSE(old_lease_);
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

    Lease4Ptr lease = engine.allocateLease4(subnet_, clientid_, hwaddr_,
                                            IOAddress("192.0.2.234"),
                                            false, false, "",
                                            false, CalloutHandlePtr(),
                                            old_lease_);
    // The client requested a different address than reserved, so
    // the allocation engine should return NULL lease. When the server
    // receives a NULL lease for the client, it will send a DHCPNAK.
    ASSERT_FALSE(lease);
    ASSERT_FALSE(old_lease_);

    // Now, request a correct address. The client should obtain it.
    lease = engine.allocateLease4(subnet_, clientid_, hwaddr_,
                                  IOAddress("192.0.2.123"),
                                  false, false, "",
                                  false, CalloutHandlePtr(),
                                  old_lease_);
    ASSERT_TRUE(lease);
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // Make sure that the lease has been committed to the lease database.
    // And that the committed lease is equal to the one returned.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);

    EXPECT_FALSE(old_lease_);
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
    Lease4Ptr lease = engine.allocateLease4(subnet_, clientid_, hwaddr_,
                                            IOAddress("192.0.2.234"),
                                            false, false, "",
                                            true, CalloutHandlePtr(),
                                            old_lease_);
    ASSERT_TRUE(lease);
    // Allocation engine should return reserved address.
    EXPECT_EQ("192.0.2.123", lease->addr_.toText());

    // This is a "fake" allocation so the returned lease should not be committed
    // to the lease database.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(lease->addr_));

    EXPECT_FALSE(old_lease_);
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
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Request allocation of the reserved address.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("192.0.2.123"),
                                                      false, false, "",
                                                      false, CalloutHandlePtr(),
                                                      old_lease_);
    ASSERT_TRUE(allocated_lease);
    // The engine should have allocated the reserved address.
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // Make sure that the lease has been committed to the lease database.
    Lease4Ptr from_mgr =
        LeaseMgrFactory::instance().getLease4(allocated_lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(allocated_lease, from_mgr);

    // The previous lease should have been replaced by a new one. The previous
    // lease should be returned by the allocation engine to the caller.
    ASSERT_TRUE(old_lease_);
    EXPECT_EQ("192.0.2.101", old_lease_->addr_.toText());
    detailCompareLease(old_lease_, lease);
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
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("192.0.2.123"),
                                                      false, false, "",
                                                      false, CalloutHandlePtr(),
                                                      old_lease_);
    // The lease is allocated to someone else, so the allocation should not
    // succeed.
    ASSERT_FALSE(allocated_lease);
    EXPECT_FALSE(old_lease_);

    // Make sure that the allocation engine didn't modify the lease of the
    // client A.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    detailCompareLease(lease, from_mgr);

    // Try doing the same thing, but this time do not request any specific
    // address. It should have the same effect.
    allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                            hwaddr_,
                                            IOAddress("0.0.0.0"),
                                            false, false, "",
                                            false, CalloutHandlePtr(),
                                            old_lease_);
    ASSERT_FALSE(allocated_lease);
    EXPECT_FALSE(old_lease_);

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
// and that it can't allocate a lease to the client B.
//
// In the scenario presented here, the allocation engine should return a
// NULL lease to the server. When the server receives NULL pointer from the
// allocation engine the proper action for the server will be to not
// respond to the client. Instead it should report to the administrator
// that it was unable to allocate the (reserved) lease.
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
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("192.0.2.123"),
                                                      false, false, "",
                                                      true, CalloutHandlePtr(),
                                                      old_lease_);
    // The allocation engine should return no lease.
    ASSERT_FALSE(allocated_lease);
    EXPECT_FALSE(old_lease_);

    // Do the same test. But, this time do not specify any address to be
    // allocated.
    allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                            hwaddr_,
                                            IOAddress("0.0.0.0"),
                                            false, false, "",
                                            true, CalloutHandlePtr(),
                                            old_lease_);
    EXPECT_FALSE(allocated_lease);
    EXPECT_FALSE(old_lease_);
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
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Try to allocate a lease and specify a different address than reserved
    // and different from the one that client is currently using.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("192.0.2.102"),
                                                      false, false, "",
                                                      false, CalloutHandlePtr(),
                                                      old_lease_);
    ASSERT_FALSE(allocated_lease);
    ASSERT_FALSE(old_lease_);

    // Repeat the test, but this time ask for the address that the client
    // has allocated.
    allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                            hwaddr_,
                                            IOAddress("192.0.2.101"),
                                            false, false, "",
                                            false, CalloutHandlePtr(),
                                            old_lease_);
    // The client has reservation so the server wants to allocate a
    // reserved address and doesn't want to renew the address that the
    // client is currently using. This is equivalent of the case when
    // the client tries to renew the lease but there is a new reservation
    // for this client. The server doesn't allow for the renewal and
    // responds with DHCPNAK to force the client to return to the
    // DHCP server discovery.
    EXPECT_FALSE(allocated_lease);
    EXPECT_FALSE(old_lease_);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a lease in the database.
// - Client has a reservation for a different address than the one for which it
// has a lease.
// - Client sends a DHCPDISCOVER and asks for a different address than reserved
// and different from which it has a lease for.
// - Server ignores the client's hint and offers a reserved address.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseFakeAllocation) {
    // Create a reservation for the client.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Try to allocate a lease and use a completely different address
    // as a hint.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("192.0.2.102"),
                                                      false, false, "",
                                                      true, CalloutHandlePtr(),
                                                      old_lease_);
    // Server should offer a lease for a reserved address.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // The lease should not be allocated until the client sends a DHCPREQUEST.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(allocated_lease->addr_));

    // Old lease should contain the currently used lease.
    ASSERT_TRUE(old_lease_);
    EXPECT_EQ("192.0.2.101", old_lease_->addr_.toText());

    // Repeat the test but this time ask for the address for which the
    // client has a lease.
    allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                            hwaddr_,
                                            IOAddress("192.0.2.101"),
                                            false, false, "",
                                            true, CalloutHandlePtr(),
                                            old_lease_);
    // The server should offer the lease, but not for the address that
    // the client requested. The server should offer a reserved address.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // Old lease should contain the currently used lease.
    ASSERT_TRUE(old_lease_);
    EXPECT_EQ("192.0.2.101", old_lease_->addr_.toText());
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
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Try to allocate a lease with providing no hint.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("0.0.0.0"),
                                                      false, false, "",
                                                      false, CalloutHandlePtr(),
                                                      old_lease_);
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
    ASSERT_TRUE(old_lease_);
    detailCompareLease(lease, old_lease_);
}

// This test checks that the behavior of the allocation engine in the following
// scenario:
// - Client has a reservation.
// - Client has a lease for a different address than reserved.
// - Client sends a DHCPDISCOVER with no hint.
// - Server determines that there is a reservation for the client and that
// the current lease should be removed and the reserved address should be
// allocated.
TEST_F(AllocEngine4Test, reservedAddressExistingLeaseNoHintFakeAllocation) {
    // Create a reservation.
    HostPtr host(new Host(&hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress("192.0.2.123")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for a different address than reserved.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Query the allocation engine for the lease to be allocated for the
    // client.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      IOAddress("0.0.0.0"),
                                                      false, false, "",
                                                      true, CalloutHandlePtr(),
                                                      old_lease_);
    // The server should offer the reserved address.
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.123", allocated_lease->addr_.toText());

    // The lease should not be committed to the lease database until the
    // client sends a DHCPREQUEST.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(allocated_lease->addr_));

    // The old lease should reflect what is in the database.
    ASSERT_TRUE(old_lease_);
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
// - Server determines that the lease that the Client A is trying to renews
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
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress("192.0.2.101")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Create a lease for Client A.
    Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr_, 0, 0,
                               100, 30, 60, time(NULL), subnet_->getID(),
                               false, false, ""));
    LeaseMgrFactory::instance().addLease(lease);

    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);


    // Client B sends a DHCPREQUEST to allocate a reserved lease. The
    // allocation engine declines allocation of the address for the
    // client because Client A has a lease for it.
    ASSERT_FALSE(engine.allocateLease4(subnet_, ClientIdPtr(), hwaddr2_,
                                       IOAddress("192.0.2.101"), false,
                                       false, "", false, CalloutHandlePtr(),
                                       old_lease_));

    // Client A tries to renew the lease. The renewal should fail because
    // server detects that Client A doesn't have reservation for this
    // address.
    ASSERT_FALSE(engine.allocateLease4(subnet_, clientid_, hwaddr_,
                                       IOAddress("192.0.2.101"), false, false,
                                       "", false, CalloutHandlePtr(),
                                       old_lease_));
    ASSERT_TRUE(old_lease_);
    EXPECT_EQ("192.0.2.101", old_lease_->addr_.toText());

    // Client A returns to DHCPDISCOVER and should be offered a lease.
    // The offered lease address must be different than the one the
    // Client B has reservation for.
    Lease4Ptr offered_lease = engine.allocateLease4(subnet_, clientid_,
                                                    hwaddr_,
                                                    IOAddress("192.0.2.101"),
                                                    false, false, "", true,
                                                    CalloutHandlePtr(),
                                                    old_lease_);
    ASSERT_TRUE(offered_lease);
    EXPECT_NE(offered_lease->addr_.toText(), "192.0.2.101");

    // Client A tried to acquire the lease. It should succeed. At this point
    // the previous lease should be released and become available for the
    // Client B.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, clientid_,
                                                      hwaddr_,
                                                      offered_lease->addr_,
                                                      false, false, "", false,
                                                      CalloutHandlePtr(),
                                                      old_lease_);
    ASSERT_TRUE(allocated_lease);
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.101");

    // Client B tries to get the lease again. It should be offered
    // a reserved lease.
    offered_lease = engine.allocateLease4(subnet_, ClientIdPtr(),
                                          hwaddr2_,
                                          IOAddress("0.0.0.0"),
                                          false, false, "", true,
                                          CalloutHandlePtr(),
                                          old_lease_);
    ASSERT_TRUE(offered_lease);
    EXPECT_EQ("192.0.2.101", offered_lease->addr_.toText());

    // Client B requests allocation of the lease and it should succeed.
    allocated_lease = engine.allocateLease4(subnet_, ClientIdPtr(),
                                            hwaddr2_,
                                            offered_lease->addr_,
                                            false, false, "", false,
                                            CalloutHandlePtr(),
                                            old_lease_);
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
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, ClientIdPtr(),
                                                      hwaddr_,
                                                      IOAddress("0.0.0.0"),
                                                      false, false, "", false,
                                                      CalloutHandlePtr(),
                                                      old_lease_);
    ASSERT_TRUE(allocated_lease);
    EXPECT_NE(allocated_lease->addr_.toText(), "192.0.2.100");
}

// This test checks that the allocation engine refuses to allocate an
// address when the pool is exhausted, and the only one available
// address is reserved for a different client.
TEST_F(AllocEngine4Test, reservedAddressShortPool) {
    AllocEngine engine(AllocEngine::ALLOC_ITERATIVE, 100, false);

    // Create short pool with only one address.
    initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.100"));
    // Reserve the address for a different client.
    HostPtr host(new Host(&hwaddr2_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                          Host::IDENT_HWADDR, subnet_->getID(),
                          SubnetID(0), IOAddress("192.0.2.100")));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
    CfgMgr::instance().commit();

    // Allocation engine should determine that the available address is
    // reserved for someone else and not allocate it.
    Lease4Ptr allocated_lease = engine.allocateLease4(subnet_, ClientIdPtr(),
                                                      hwaddr_,
                                                      IOAddress("0.0.0.0"),
                                                      false, false, "", false,
                                                      CalloutHandlePtr(),
                                                      old_lease_);
    EXPECT_FALSE(allocated_lease);

    // Now, let's remove the reservation.
    initSubnet(IOAddress("192.0.2.100"), IOAddress("192.0.2.100"));
    CfgMgr::instance().commit();

    // Address should be successfully allocated.
    allocated_lease = engine.allocateLease4(subnet_, ClientIdPtr(), hwaddr_,
                                            IOAddress("0.0.0.0"), false, false,
                                            "", false, CalloutHandlePtr(),
                                            old_lease_);
    ASSERT_TRUE(allocated_lease);
    EXPECT_EQ("192.0.2.100", allocated_lease->addr_.toText());
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
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA, false, false, "", false);
    ctx.callout_handle_ = callout_handle;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
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
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA, false, false, "", false);
    ctx.callout_handle_ = callout_handle;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
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
