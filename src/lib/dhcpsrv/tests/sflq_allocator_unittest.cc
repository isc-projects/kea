// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
//#include <database/database_connection.h>
//#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/sflq_allocator.h>
#include <dhcpsrv/testutils/sflqtest_lease_mgr.h>
#include <gtest/gtest.h>
#include <testutils/gtest_utils.h>

using namespace isc::asiolink;
using namespace isc::db;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {


/// @brief Test fixture class for the DHCPv4 SharedFlqAllocator.
class SharedFlqAllocatorTest4 : public testing::Test {
public:

    /// @brief Pre-test setup.
    ///
    /// Installs the lease manager factory, creates a manager instance
    /// and initializes a V4 subnet.
    virtual void SetUp() {
        LeaseMgrFactory::registerFactory("sflqtest", SflqTestLeaseMgr::factory);
        ASSERT_NO_THROW_LOG(LeaseMgrFactory::create("type=sflqtest universe=4"));
        ASSERT_TRUE(LeaseMgrFactory::haveInstance());
        ASSERT_EQ(LeaseMgrFactory::instance().getType(), "sflqtest");
        initSubnet4();
        SharedFlqAllocator::setInUse(false);
    }

    /// @brief Post-test cleanup.
    virtual void TearDown() {
        SharedFlqAllocator::setInUse(false);
    }

    /// @brief Initializes the test subnet for V4 tests.
    void initSubnet4() {
        static SubnetID id(1);
        subnet_ = Subnet4::create(IOAddress("192.0.0.0"), 8, 1, 2, 3, id);
        PoolPtr pool(new Pool4(IOAddress("192.0.1.0"), IOAddress("192.0.1.1")));
        pool->allowClientClass("ALL");
        pool->allowClientClass("one");
        subnet_->addPool(pool);

        pool = PoolPtr(new Pool4(IOAddress("192.0.2.0"), IOAddress("192.0.2.1")));
        pool->allowClientClass("ALL");
        pool->allowClientClass("two");
        subnet_->addPool(pool);

        pool = PoolPtr(new Pool4(IOAddress("192.0.3.0"), IOAddress("192.0.3.1")));
        pool->allowClientClass("ALL");
        pool->allowClientClass("three");
        subnet_->addPool(pool);

        subnet_->setAllocatorType("shared-flq");
        subnet_->createAllocators();
    }

    /// @brief Subnet used in tests.
    Subnet4Ptr subnet_;
};

// Test that the allocator returns the correct type.
TEST_F(SharedFlqAllocatorTest4, getType) {
    SharedFlqAllocator alloc(Lease::TYPE_V4, subnet_);
    EXPECT_EQ("shared-flq", alloc.getType());
}

// Tests initAfterConfigure() function. It should create
// an SFLQ pool for each pool in the subnet.
TEST_F(SharedFlqAllocatorTest4, initAfterConfigure) {
    EXPECT_FALSE(SharedFlqAllocator::inUse());
    auto alloc = subnet_->getAllocator(Lease::TYPE_V4);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());
    EXPECT_TRUE(SharedFlqAllocator::inUse());

    SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());

    for (auto pool : subnet_->getPools(Lease::TYPE_V4)) {
        auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
    }
}

// Exercises SharedFlqAllocator::pickAddressInternal() for a V4 subnet.
TEST_F(SharedFlqAllocatorTest4, pickAddress) {
    IOAddress zero_address = IOAddress::IPV4_ZERO_ADDRESS();

    auto alloc = subnet_->getAllocator(Lease::TYPE_V4);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());

    SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());
    for (auto pool : subnet_->getPools(Lease::TYPE_V4)) {
        auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
    }

    // Verify that all addresses can be picked with client_class = 'ALL'.
    // We use a set to collect the picked addresses. This way we do not
    // rely on the order they are picked but can still verify they
    // all get picked.
    std::set<IOAddress> picked;
    ClientClasses client_classes;
    client_classes.insert("ALL");
    for (int i = 0; i < 6; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickAddress(client_classes,
                                               IdentifierBaseTypePtr(),
                                               zero_address));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 6U);
    ASSERT_TRUE(picked.count(IOAddress("192.0.1.0")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.1.1")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.2.0")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.2.1")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.3.0")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.3.1")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickAddress(client_classes, IdentifierBaseTypePtr(), zero_address),
              zero_address);

    // Verify that only pool 2 addresses are picked for class "two"
    slm.repopulateFlqPools();
    picked.clear();
    client_classes.clear();
    client_classes.insert("two");
    for (int i = 0; i < 2; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickAddress(client_classes,
                                               IdentifierBaseTypePtr(),
                                               zero_address))
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 2U);
    ASSERT_TRUE(picked.count(IOAddress("192.0.2.0")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.2.1")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickAddress(client_classes, IdentifierBaseTypePtr(), zero_address),
              zero_address);

    // Verify that only pool 1 and 3 addresses are picked for classes "one" or "three"
    slm.repopulateFlqPools();
    picked.clear();
    client_classes.clear();
    client_classes.insert("one");
    client_classes.insert("three");
    for (int i = 0; i < 4; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickAddress(client_classes,
                                               IdentifierBaseTypePtr(),
                                               zero_address));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 4U);
    ASSERT_TRUE(picked.count(IOAddress("192.0.1.0")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.1.1")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.3.0")));
    ASSERT_TRUE(picked.count(IOAddress("192.0.3.1")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickAddress(client_classes, IdentifierBaseTypePtr(), zero_address),
              zero_address);
}

/// @brief Test fixture class for the DHCPv6 SharedFlqAllocator.
class SharedFlqAllocatorTest6 : public testing::Test {
public:

    /// @brief Pre-test setup.
    ///
    /// Installs the lease manager factory, creates a manager instance
    /// and initializes a V4 subnet.
    virtual void SetUp() {
        LeaseMgrFactory::registerFactory("sflqtest", SflqTestLeaseMgr::factory);
        ASSERT_NO_THROW_LOG(LeaseMgrFactory::create("type=sflqtest universe=6"));
        ASSERT_TRUE(LeaseMgrFactory::haveInstance());
        ASSERT_EQ(LeaseMgrFactory::instance().getType(), "sflqtest");
        initSubnet6();
        SharedFlqAllocator::setInUse(false);
    }

    /// @brief Post-test cleanup.
    virtual void TearDown() {
        SharedFlqAllocator::setInUse(false);
    }

    /// @brief Initializes the test subnet for V4 tests.
    void initSubnet6() {
        static SubnetID id(1);

        subnet_ = Subnet6::create(IOAddress("3001::"), 64, 0, 0, 0, 0 , id);
        PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("3001::10"), IOAddress("3001::11")));
        pool->allowClientClass("ALL");
        pool->allowClientClass("one");
        subnet_->addPool(pool);

        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("3001::20"), IOAddress("3001::21")));
        pool->allowClientClass("ALL");
        pool->allowClientClass("two");
        subnet_->addPool(pool);

        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("3001::30"), IOAddress("3001::31")));
        pool->allowClientClass("ALL");
        pool->allowClientClass("three");
        subnet_->addPool(pool);

        // Now add PD pools to match classes, we use same length to make it
        // verification easy .
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("2001::10"), 127, 128));
        pool->allowClientClass("ALL");
        pool->allowClientClass("one");
        subnet_->addPool(pool);

        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("2001::20"), 127, 128));
        pool->allowClientClass("ALL");
        pool->allowClientClass("two");
        subnet_->addPool(pool);

        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("2001::30"), 127, 128));
        pool->allowClientClass("ALL");
        pool->allowClientClass("three");
        subnet_->addPool(pool);

        // Now add PD pools of with low, middle, high for testing prefix
        // hint logic.
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("4001:10::"), 124, 124));
        pool->allowClientClass("LENGTH_HINT");
        subnet_->addPool(pool);

        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("4001:20::"), 124, 126));
        pool->allowClientClass("LENGTH_HINT");
        subnet_->addPool(pool);

        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("4001:30::"), 124, 128));
        pool->allowClientClass("LENGTH_HINT");
        subnet_->addPool(pool);

        subnet_->setAllocatorType("shared-flq");
        subnet_->setPdAllocatorType("shared-flq");
        subnet_->createAllocators();
    }

    /// @brief Subnet used in tests.
    Subnet6Ptr subnet_;
};

// Test that the allocator returns the correct type.
TEST_F(SharedFlqAllocatorTest6, getType) {
    {
        SharedFlqAllocator alloc(Lease::TYPE_NA, subnet_);
        EXPECT_EQ("shared-flq", alloc.getType());
    }

    {
        SharedFlqAllocator alloc(Lease::TYPE_PD, subnet_);
        EXPECT_EQ("shared-flq", alloc.getType());
    }
}

// Tests initAfterConfigure() for V6/TYPE_NA pools.
TEST_F(SharedFlqAllocatorTest6, initAfterConfigureNA) {
    EXPECT_FALSE(SharedFlqAllocator::inUse());
    auto alloc = subnet_->getAllocator(Lease::TYPE_NA);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());
    EXPECT_TRUE(SharedFlqAllocator::inUse());

    // Verify the NA pools.
   SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());

    for (auto pool : subnet_->getPools(Lease::TYPE_NA)) {
       auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
        ASSERT_EQ(sflq_pool->lease_type_, Lease::TYPE_NA);
    }
}

// Exercises SharedFlqAllocator::pickAddressInternal() for V6/TYPE_NA
// using various class matches.
TEST_F(SharedFlqAllocatorTest6, pickAddress) {
    IOAddress zero_address = IOAddress::IPV6_ZERO_ADDRESS();

    auto alloc = subnet_->getAllocator(Lease::TYPE_NA);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());

    SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());
    for (auto pool : subnet_->getPools(Lease::TYPE_NA)) {
        auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
    }

    // Verify that all addresses can be picked with client_class = 'ALL'.
    // We use a set to collect the picked addresses. This way we do not
    // rely on the order they are picked but can still verify they
    // all get picked.
    std::set<IOAddress> picked;
    ClientClasses client_classes;
    client_classes.insert("ALL");
    for (int i = 0; i < 6; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickAddress(client_classes,
                                               IdentifierBaseTypePtr(),
                                               zero_address));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 6U);
    ASSERT_TRUE(picked.count(IOAddress("3001::10")));
    ASSERT_TRUE(picked.count(IOAddress("3001::11")));
    ASSERT_TRUE(picked.count(IOAddress("3001::20")));
    ASSERT_TRUE(picked.count(IOAddress("3001::21")));
    ASSERT_TRUE(picked.count(IOAddress("3001::30")));
    ASSERT_TRUE(picked.count(IOAddress("3001::31")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickAddress(client_classes, IdentifierBaseTypePtr(), zero_address),
              zero_address);

    // Verify that only pool 2 addresses are picked for class "two"
    slm.repopulateFlqPools();
    picked.clear();
    client_classes.clear();
    client_classes.insert("two");
    for (int i = 0; i < 2; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickAddress(client_classes,
                                              IdentifierBaseTypePtr(),
                                              zero_address))
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 2U);
    ASSERT_TRUE(picked.count(IOAddress("3001::20")));
    ASSERT_TRUE(picked.count(IOAddress("3001::21")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickAddress(client_classes, IdentifierBaseTypePtr(), zero_address),
              zero_address);

    // Verify that only pool 1 and 3 addresses are picked for classes "one" or "three"
    slm.repopulateFlqPools();
    picked.clear();
    client_classes.clear();
    client_classes.insert("one");
    client_classes.insert("three");
    for (int i = 0; i < 4; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickAddress(client_classes,
                                               IdentifierBaseTypePtr(),
                                               zero_address));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 4U);
    ASSERT_TRUE(picked.count(IOAddress("3001::10")));
    ASSERT_TRUE(picked.count(IOAddress("3001::11")));
    ASSERT_TRUE(picked.count(IOAddress("3001::30")));
    ASSERT_TRUE(picked.count(IOAddress("3001::31")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickAddress(client_classes, IdentifierBaseTypePtr(), zero_address),
              zero_address);
}

// Tests initAfterConfigure() for V6/TYPE_PD pools.
TEST_F(SharedFlqAllocatorTest6, initAfterConfigurePD) {
    subnet_->setPdAllocatorType("shared-flq");
    ASSERT_NO_THROW(subnet_->createAllocators());

    EXPECT_FALSE(SharedFlqAllocator::inUse());

    auto alloc = subnet_->getAllocator(Lease::TYPE_PD);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());
    EXPECT_TRUE(SharedFlqAllocator::inUse());

    // Verify the PD pools.
    SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());

    for (auto pool : subnet_->getPools(Lease::TYPE_PD)) {
        auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
        ASSERT_EQ(sflq_pool->lease_type_, Lease::TYPE_PD);
    }
}

// Exercises SharedFlqAllocator::pickPrefixInternal() V6/TYPE_PD using
// various class matches.
TEST_F(SharedFlqAllocatorTest6, pickPrefix) {
    IOAddress zero_address = IOAddress::IPV6_ZERO_ADDRESS();

    subnet_->setPdAllocatorType("shared-flq");
    ASSERT_NO_THROW(subnet_->createAllocators());
    auto alloc = subnet_->getAllocator(Lease::TYPE_PD);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());

    SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());

    // Verify we have the expected SFLQ PD pools.
    for (auto pool : subnet_->getPools(Lease::TYPE_PD)) {
        auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
    }

    // Verify that all addresses can be picked with client_class = 'ALL'.
    // We use a set to collect the picked addresses. This way we do not
    // rely on the order they are picked but can still verify they
    // all get picked.
    std::set<IOAddress> picked;
    ClientClasses client_classes;
    client_classes.insert("ALL");
    auto dummy = Pool6Ptr();
    for (int i = 0; i < 6; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickPrefix(client_classes,
                                              dummy,
                                              IdentifierBaseTypePtr(),
                                              Allocator::PREFIX_LEN_EQUAL,
                                              zero_address,
                                              0));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 6U);
    ASSERT_TRUE(picked.count(IOAddress("2001::10")));
    ASSERT_TRUE(picked.count(IOAddress("2001::11")));
    ASSERT_TRUE(picked.count(IOAddress("2001::20")));
    ASSERT_TRUE(picked.count(IOAddress("2001::21")));
    ASSERT_TRUE(picked.count(IOAddress("2001::30")));
    ASSERT_TRUE(picked.count(IOAddress("2001::31")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickPrefix(client_classes, dummy, IdentifierBaseTypePtr(),
                                Allocator::PREFIX_LEN_EQUAL, zero_address, 0),
               zero_address);

    // Verify that only pool 2 addresses are picked for class "two"
    slm.repopulateFlqPools();
    picked.clear();
    client_classes.clear();
    client_classes.insert("two");
    for (int i = 0; i < 2; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address =
                            alloc->pickPrefix(client_classes,
                                              dummy,
                                              IdentifierBaseTypePtr(),
                                              Allocator::PREFIX_LEN_EQUAL,
                                              zero_address,
                                              0));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 2U);
    ASSERT_TRUE(picked.count(IOAddress("2001::20")));
    ASSERT_TRUE(picked.count(IOAddress("2001::21")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickPrefix(client_classes, dummy, IdentifierBaseTypePtr(),
                                Allocator::PREFIX_LEN_EQUAL, zero_address, 0),
               zero_address);

    // Verify that only pool 1 and 3 addresses are picked for classes "one" or "three"
    slm.repopulateFlqPools();
    picked.clear();
    client_classes.clear();
    client_classes.insert("one");
    client_classes.insert("three");
    for (int i = 0; i < 4; ++i) {
        IOAddress picked_address = zero_address;
        ASSERT_NO_THROW_LOG(picked_address = alloc->pickPrefix(client_classes,
                                                              dummy,
                                                              IdentifierBaseTypePtr(),
                                                              Allocator::PREFIX_LEN_EQUAL,
                                                              zero_address,
                                                              0));
        ASSERT_NE(picked_address, zero_address);
        picked.emplace(picked_address);
    }

    ASSERT_EQ(picked.size(), 4U);
    ASSERT_TRUE(picked.count(IOAddress("2001::10")));
    ASSERT_TRUE(picked.count(IOAddress("2001::11")));
    ASSERT_TRUE(picked.count(IOAddress("2001::30")));
    ASSERT_TRUE(picked.count(IOAddress("2001::31")));

    // Verify an additional pick returns zero address.
    ASSERT_EQ(alloc->pickPrefix(client_classes, dummy, IdentifierBaseTypePtr(),
                               Allocator::PREFIX_LEN_EQUAL, zero_address, 0),
               zero_address);
}

// Exercises SharedFlqAllocator::pickPrefixInternal() V6/TYPE_PD
// when specifying a prefix length mode and hint.
TEST_F(SharedFlqAllocatorTest6, pickPrefixLenHint) {
    IOAddress zero_address = IOAddress::IPV6_ZERO_ADDRESS();

    subnet_->setPdAllocatorType("shared-flq");
    ASSERT_NO_THROW(subnet_->createAllocators());
    auto alloc = subnet_->getAllocator(Lease::TYPE_PD);
    ASSERT_TRUE(alloc);
    ASSERT_NO_THROW_LOG(alloc->initAfterConfigure());

    SflqTestLeaseMgr& slm = dynamic_cast<SflqTestLeaseMgr&>(LeaseMgrFactory::instance());

    // Verify we have the expected SFLQ PD pools.
    for (auto pool : subnet_->getPools(Lease::TYPE_PD)) {
        auto sflq_pool = slm.findPool(pool->getFirstAddress(), pool->getLastAddress());
        ASSERT_TRUE(sflq_pool) << "no sflq pool for: " << pool->toText();
    }

    auto dummy = Pool6Ptr();
    ClientClasses client_classes;
    client_classes.insert("LENGTH_HINT");

    IOAddress picked_address = zero_address;
    ASSERT_NO_THROW_LOG(picked_address = alloc->pickPrefix(client_classes,
                                                           dummy,
                                                           IdentifierBaseTypePtr(),
                                                           Allocator::PREFIX_LEN_EQUAL,
                                                           zero_address,
                                                           126));
    EXPECT_EQ(picked_address, IOAddress("4001:20::"));

    ASSERT_NO_THROW_LOG(picked_address = alloc->pickPrefix(client_classes,
                                                           dummy,
                                                           IdentifierBaseTypePtr(),
                                                           Allocator::PREFIX_LEN_LOWER,
                                                           zero_address,
                                                           126));
    EXPECT_EQ(picked_address, IOAddress("4001:10::"));

    ASSERT_NO_THROW_LOG(picked_address = alloc->pickPrefix(client_classes,
                                                           dummy,
                                                           IdentifierBaseTypePtr(),
                                                           Allocator::PREFIX_LEN_HIGHER,
                                                           zero_address,
                                                           126));
    EXPECT_EQ(picked_address, IOAddress("4001:30::"));
}


} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
