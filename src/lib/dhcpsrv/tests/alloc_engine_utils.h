// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBDHCPSRV_ALLOC_ENGINE_UTILS_H
#define LIBDHCPSRV_ALLOC_ENGINE_UTILS_H

#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/cfgmgr.h>
#include <asiolink/io_address.h>
#include <gtest/gtest.h>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @file   alloc_engine_utils.h
///
/// @brief This is a header file for all Allocation Engine tests.
///
/// There used to be one, huge (over 3kloc) alloc_engine_unittest.cc. It is now
/// split into serveral smaller files:
/// alloc_engine_utils.h - contains test class definitions (this file)
/// alloc_engine_utils.cc - contains test class implementation
/// alloc_engine4_unittest.cc - all unit-tests dedicated to IPv4
/// alloc_engine6_unittest.cc - all unit-tests dedicated to IPv6
/// alloc_engine_hooks_unittest.cc - all unit-tests dedicated to hooks


/// @brief Test that statistic manager holds a given value.
///
/// This function may be used in many allocation tests and there's no
/// single base class for it. @todo consider moving it src/lib/util.
///
/// @param stat_name Statistic name.
/// @param exp_value Expected value.
///
/// @return true if the statistic manager holds a particular value,
/// false otherwise.
bool testStatistics(const std::string& stat_name, const int64_t exp_value);

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

        using AllocEngine::IterativeAllocator::increasePrefix;
    };
};

/// @brief Used in Allocation Engine tests for IPv6
class AllocEngine6Test : public ::testing::Test {
public:

    /// @brief Specified expected result of a given operation
    enum ExpectedResult {
        SHOULD_PASS,
        SHOULD_FAIL
    };

    /// @brief Default constructor
    ///
    /// Sets duid_, iaid_, subnet_, pool_ fields to example values used
    /// in many tests, initializes cfg_mgr configuration and creates
    /// lease database.
    AllocEngine6Test();

    /// @brief Configures a subnet and adds one pool to it.
    ///
    /// This function removes existing v6 subnets before configuring
    /// a new one.
    ///
    /// @param subnet Address of a subnet to be configured.
    /// @param pool_start First address in the address pool.
    /// @param pool_end Last address in the address pool.
    void initSubnet(const asiolink::IOAddress& subnet,
                    const asiolink::IOAddress& pool_start,
                    const asiolink::IOAddress& pool_end);

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

    /// @brief Wrapper around call to AllocEngine6::findRervation
    ///
    /// If a reservation is found by the engine, the function sets
    /// ctx.hostname_ accordingly.
    ///
    /// @param engine allocation engine to use
    /// @param ctx client context to pass into engine's findReservation method
    void findReservation(AllocEngine& engine, AllocEngine::ClientContext6& ctx);

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
    /// Method uses gtest macros to mark check failure. This is a proxy
    /// method, since increaseAddress was moved to IOAddress class.
    ///
    /// @param alloc IterativeAllocator that is tested
    /// @param input address to be increased
    /// @param exp_output expected address after increase
    void
    checkAddrIncrease(NakedAllocEngine::NakedIterativeAllocator&,
                      std::string input, std::string exp_output) {
        EXPECT_EQ(exp_output, asiolink::IOAddress::increase(
                      asiolink::IOAddress(input)).toText());
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
        EXPECT_EQ(exp_output, alloc.increasePrefix(asiolink::IOAddress(input),
                                                   prefix_len).toText());
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
    Lease6Ptr simpleAlloc6Test(const Pool6Ptr& pool,
                               const asiolink::IOAddress& hint,
                               bool fake, bool in_pool = true);

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
                                  const asiolink::IOAddress& hint, bool fake,
                                  bool in_pool = true);

    /// @brief Checks if the allocation can be renewed.
    ///
    /// The type of lease is determined by pool type (pool->getType()).
    /// This test is particularly useful as a follow up to @ref allocateTest.
    ///
    /// @param engine a reference to Allocation Engine
    /// @param pool pool from which the lease will be allocated from
    /// @param hints address to be used as a hint
    /// @param in_pool specifies whether the lease is expected to be in pool
    /// @return allocated lease(s) (may be empty)
    Lease6Collection renewTest(AllocEngine& engine, const Pool6Ptr& pool,
                               AllocEngine::HintContainer& hints,
                               bool in_pool = true);

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
    void allocWithUsedHintTest(Lease::Type type, asiolink::IOAddress used_addr,
                               asiolink::IOAddress requested,
                               uint8_t expected_pd_len);

    /// @brief Generic test used for IPv6 lease allocation and reuse
    ///
    /// This test inserts existing_lease (if specified, may be null) into the
    /// LeaseMgr, then conducts lease allocation (pretends that client
    /// sent either Solicit or Request, depending on fake_allocation).
    /// Allocated lease is then returned (using result) for further inspection.
    ///
    /// @param alloc_engine allocation engine
    /// @param existing_lease optional lease to be inserted in the database
    /// @param addr address to be requested by client
    /// @param fake_allocation true = SOLICIT, false = REQUEST
    /// @param exp_result expected result
    /// @param result [out] allocated lease
    void testReuseLease6(const AllocEnginePtr& alloc_engine,
                         Lease6Ptr& existing_lease,
                         const std::string& addr,
                         const bool fake_allocation,
                         ExpectedResult exp_result,
                         Lease6Ptr& result);

    /// @brief Creates a declined IPv6 lease with specified expiration time
    ///
    /// expired parameter controls probation period. Positive value
    /// means that the lease will expire in X seconds. Negative means
    /// that the lease expired X seconds ago. 0 means it expires now.
    /// Probation period is a parameter that specifies for how long
    /// a lease will stay unavailable after decline.
    ///
    /// @param addr address of the lease
    /// @param probation_period expressed in seconds
    /// @param expired number of seconds when the lease will expire
    Lease6Ptr generateDeclinedLease(const std::string& addr,
                                    time_t probation_period,
                                    int32_t expired);

    /// @brief checks if bogus hint can be ignored and the allocation succeeds
    ///
    /// This test checks if the allocation with a hing that is out of the blue
    /// can succeed. The invalid hint should be ignored completely.
    ///
    /// @param type Lease type
    /// @param hint hint (as send by a client)
    /// @param expected_pd_len (used in validation)
    void allocBogusHint6(Lease::Type type, asiolink::IOAddress hint,
                         uint8_t expected_pd_len);

    /// @brief Utility function that creates a host reservation (duid)
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
                              asiolink::IOAddress("0.0.0.0")));
        IPv6Resrv resv(type, addr, prefix_len);
        host->addReservation(resv);

        if (add_to_host_mgr) {
            CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
            CfgMgr::instance().commit();
        }
        return (host);
    }

    /// @brief Utility function that creates a host reservation (hwaddr)
    ///
    /// @param add_to_host_mgr true if the reservation should be added
    /// @param type specifies reservation type
    /// @param hwaddr hardware address to be reserved to
    /// @param addr specifies reserved address or prefix
    /// @param prefix_len prefix length (should be 128 for addresses)
    /// @return created Host object.
    HostPtr
    createHost6HWAddr(bool add_to_host_mgr, IPv6Resrv::Type type,
                      HWAddrPtr& hwaddr, const asiolink::IOAddress& addr,
                      uint8_t prefix_len);

    virtual ~AllocEngine6Test() {
        factory_.destroy();
    }

    DuidPtr duid_;            ///< client-identifier (value used in tests)
    HWAddrPtr hwaddr_;        ///< client's hardware address
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

    /// @brief Specified expected result of a given operation
    enum ExpectedResult {
        SHOULD_PASS,
        SHOULD_FAIL
    };

    /// @brief Default constructor
    ///
    /// Sets clientid_, hwaddr_, subnet_, pool_ fields to example values
    /// used in many tests, initializes cfg_mgr configuration and creates
    /// lease database.
    ///
    /// It also re-initializes the Host Manager.
    AllocEngine4Test();

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

    /// @brief Generic test used for IPv4 lease allocation and reuse
    ///
    /// This test inserts existing_lease (if specified, may be null) into the
    /// LeaseMgr, then conducts lease allocation (pretends that client
    /// sent either Discover or Request, depending on fake_allocation).
    /// Allocated lease is then returned (using result) for further inspection.
    ///
    /// @param alloc_engine allocation engine
    /// @param existing_lease optional lease to be inserted in the database
    /// @param addr address to be requested by client
    /// @param fake_allocation true = DISCOVER, false = REQUEST
    /// @param exp_result expected result
    /// @param result [out] allocated lease
    void testReuseLease4(const AllocEnginePtr& alloc_engine,
                         Lease4Ptr& existing_lease,
                         const std::string& addr,
                         const bool fake_allocation,
                         ExpectedResult exp_result,
                         Lease4Ptr& result);

    /// @brief Creates a declined IPv4 lease with specified expiration time
    ///
    /// expired parameter controls probation period. Positive value
    /// means that the lease will expire in X seconds. Negative means
    /// that the lease expired X seconds ago. 0 means it expires now.
    /// Probation period is a parameter that specifies for how long
    /// a lease will stay unavailable after decline.
    ///
    /// @param addr address of the lease
    /// @param probation_period expressed in seconds
    /// @param expired number of seconds when the lease will expire
    Lease4Ptr generateDeclinedLease(const std::string& addr,
                                    time_t probation_period,
                                    int32_t expired);

    /// @brief Create a subnet with a specified pool of addresses.
    ///
    /// @param pool_start First address in the pool.
    /// @param pool_end Last address in the pool.
    void initSubnet(const asiolink::IOAddress& pool_start,
                    const asiolink::IOAddress& pool_end);

    virtual ~AllocEngine4Test() {
        factory_.destroy();
    }

    ClientIdPtr clientid_;      ///< Client-identifier (value used in tests)
    ClientIdPtr clientid2_;     ///< Alternative client-identifier.
    HWAddrPtr hwaddr_;          ///< Hardware address (value used in tests)
    HWAddrPtr hwaddr2_;         ///< Alternative hardware address.
    Subnet4Ptr subnet_;         ///< Subnet4 (used in tests)
    Pool4Ptr pool_;             ///< Pool belonging to subnet_
    LeaseMgrFactory factory_;   ///< Pointer to LeaseMgr factory
    AllocEngine::ClientContext4 ctx_; ///< Context information passed to various
                                     ///< allocation engine functions.
};

}; // namespace test
}; // namespace dhcp
}; // namespace isc

#endif
