// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/flq_allocator.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test fixture class for the DHCPv4 Free Lease Queue allocator.
class FreeLeaseQueueAllocatorTest4 : public AllocEngine4Test {
public:

    /// @brief Creates a DHCPv4 lease for an address and MAC address.
    ///
    /// @param address Lease address.
    /// @param hw_address_seed a seed from which the hardware address is generated.
    /// @return Created lease pointer.
    Lease4Ptr
    createLease4(const IOAddress& address, uint64_t hw_address_seed) const {
        vector<uint8_t> hw_address_vec(sizeof(hw_address_seed));
        for (auto i = 0; i < sizeof(hw_address_seed); ++i) {
            hw_address_vec[i] = (hw_address_seed >> i) & 0xFF;
        }
        auto hw_address = boost::make_shared<HWAddr>(hw_address_vec, HTYPE_ETHER);
        auto lease = boost::make_shared<Lease4>(address, hw_address, ClientIdPtr(),
                                                3600, time(0), subnet_->getID());
        return (lease);
    }
};

// Test that the allocator returns the correct type.
TEST_F(FreeLeaseQueueAllocatorTest4, getType) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);
    EXPECT_EQ("flq", alloc.getType());
}

// Test populating free DHCPv4 leases to the queue.
TEST_F(FreeLeaseQueueAllocatorTest4, populateFreeAddressLeases) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

    auto& lease_mgr = LeaseMgrFactory::instance();

    EXPECT_TRUE(lease_mgr.addLease((createLease4(IOAddress("192.0.2.100"), 0))));
    EXPECT_TRUE(lease_mgr.addLease((createLease4(IOAddress("192.0.2.102"), 1))));
    EXPECT_TRUE(lease_mgr.addLease((createLease4(IOAddress("192.0.2.104"), 2))));
    EXPECT_TRUE(lease_mgr.addLease((createLease4(IOAddress("192.0.2.106"), 3))));
    EXPECT_TRUE(lease_mgr.addLease((createLease4(IOAddress("192.0.2.108"), 4))));

    EXPECT_NO_THROW(alloc.initAfterConfigure());

    auto pool_state = boost::dynamic_pointer_cast<PoolFreeLeaseQueueAllocationState>(pool_->getAllocationState());
    ASSERT_TRUE(pool_state);
    EXPECT_FALSE(pool_state->exhausted());

    std::set<IOAddress> addresses;
    for (auto i = 0; i < 5; ++i) {
        auto lease = pool_state->offerFreeLease();
        ASSERT_FALSE(lease.isV4Zero());
        addresses.insert(lease);
    }
    ASSERT_EQ(5, addresses.size());
    EXPECT_EQ(1, addresses.count(IOAddress("192.0.2.101")));
    EXPECT_EQ(1, addresses.count(IOAddress("192.0.2.103")));
    EXPECT_EQ(1, addresses.count(IOAddress("192.0.2.105")));
    EXPECT_EQ(1, addresses.count(IOAddress("192.0.2.107")));
    EXPECT_EQ(1, addresses.count(IOAddress("192.0.2.109")));
}

// Test allocating IPv4 addresses when a subnet has a single pool.
TEST_F(FreeLeaseQueueAllocatorTest4, singlePool) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

    ASSERT_NO_THROW(alloc.initAfterConfigure());

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::set<IOAddress> addresses;
    for (auto i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        addresses.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
    }
    // The pool comprises 10 addresses. All should be returned.
    EXPECT_EQ(10, addresses.size());
}

// Test allocating IPv4 addresses and re-allocating these that are
// deleted (released).
TEST_F(FreeLeaseQueueAllocatorTest4, singlePoolWithAllocations) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::map<IOAddress, Lease4Ptr> leases;
    for (auto i = 0; i < 10; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        auto lease = createLease4(candidate, i);
        leases[candidate] = lease;
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }
    // The pool comprises 10 addresses. All should be returned.
    EXPECT_EQ(10, leases.size());

    IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
    EXPECT_TRUE(candidate.isV4Zero());

    auto i = 0;
    for (auto const& address_lease : leases) {
        if (i % 2) {
            EXPECT_TRUE(lease_mgr.deleteLease(address_lease.second));
        }
        ++i;
    }

    for (auto i = 0; i < 5; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
        auto lease = createLease4(candidate, i);
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }

    candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
    EXPECT_TRUE(candidate.isV4Zero());
}

// Test allocating IPv4 addresses and re-allocating these that are
// reclaimed.
TEST_F(FreeLeaseQueueAllocatorTest4, singlePoolWithReclamations) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::map<IOAddress, Lease4Ptr> leases;
    for (auto i = 0; i < 10; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        auto lease = createLease4(candidate, i);
        leases[candidate] = lease;
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }
    // The pool comprises 10 addresses. All should be returned.
    EXPECT_EQ(10, leases.size());

    IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
    EXPECT_TRUE(candidate.isV4Zero());

    auto i = 0;
    for (auto const& address_lease : leases) {
        if (i % 2) {
            auto lease = address_lease.second;
            lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
            EXPECT_NO_THROW(lease_mgr.updateLease4(lease));
        }
        ++i;
    }
    for (auto i = 0; i < 5; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
        auto lease = lease_mgr.getLease4(candidate);
        lease->state_ = Lease::STATE_DEFAULT;
        EXPECT_NO_THROW(lease_mgr.updateLease4(lease));
    }

    candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
    EXPECT_TRUE(candidate.isV4Zero());
}

// Test allocating DHCPv4 leases for many pools in a subnet.
TEST_F(FreeLeaseQueueAllocatorTest4, manyPools) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

    // Add several more pools.
    for (int i = 1; i < 10; ++i) {
        stringstream min, max;
        min << "192.0.2." << i * 10;
        max << "192.0.2." << i * 10 + 9;
        auto pool = boost::make_shared<Pool4>(IOAddress(min.str()),
                                              IOAddress(max.str()));
        subnet_->addPool(pool);
    }

    // There are ten pools with 10 addresses each.
    int total = 100;

    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    std::set<IOAddress> addresses_set;
    std::vector<IOAddress> addresses_vector;
    std::vector<PoolPtr> pools_vector;

    // Pick random addresses the number of times equal to the
    // subnet capacity to ensure that all addresses are returned.
    for (auto i = 0; i < total; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        addresses_set.insert(candidate);
        addresses_vector.push_back(candidate);
        auto lease = createLease4(candidate, i);
        EXPECT_TRUE(lease_mgr.addLease(lease));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
        pools_vector.push_back(subnet_->getPool(Lease::TYPE_V4, candidate));
    }
    // Make sure that unique addresses have been returned.
    EXPECT_EQ(total, addresses_set.size());

    // Verify that the addresses are returned in the random order.
    // Count how many times we found consecutive addresses. It should
    // be 0 or close to 0.
    int consecutive_addresses = 0;
    for (auto k = 0; k < addresses_vector.size()-1; ++k) {
        if (addresses_vector[k].toUint32() == addresses_vector[k+1].toUint32()-1) {
            ++consecutive_addresses;
        }
    }
    // Ideally, the number of consecutive occurrences should be 0 but we
    // allow some to make sure the test doesn't fall over sporadically.
    EXPECT_LT(consecutive_addresses, addresses_vector.size()/4);

    // Repeat similar check for pools. The pools should be picked in the
    // random order too.
    int consecutive_pools = 0;
    for (auto k = 0; k < pools_vector.size()-1; ++k) {
        // Check if the pools are adjacent (i.e., last address of the
        // previous pool is a neighbor of the first address of the next
        // pool).
        if (pools_vector[k]->getLastAddress().toUint32()+1 ==
            pools_vector[k+1]->getFirstAddress().toUint32()) {
            ++consecutive_pools;
        }
    }
    EXPECT_LT(consecutive_pools, pools_vector.size()/2);
}

// Test that the allocator returns a zero address when there are no pools
// in a subnet.
TEST_F(FreeLeaseQueueAllocatorTest4, noPools) {
   FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

   subnet_->delPools(Lease::TYPE_V4);

   IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
   EXPECT_TRUE(candidate.isV4Zero());
}

// Test that the allocator respects client class guards.
TEST_F(FreeLeaseQueueAllocatorTest4, clientClasses) {
   FreeLeaseQueueAllocator alloc(Lease::TYPE_V4, subnet_);

   // First pool only allows the client class foo.
   pool_->allowClientClass("foo");

   // Second pool. It only allows client class bar.
   auto pool1 = boost::make_shared<Pool4>(IOAddress("192.0.2.120"),
                                         IOAddress("192.0.2.129"));
   pool1->allowClientClass("bar");
   subnet_->addPool(pool1);

   // Third pool. It only allows client class foo.
   auto pool2 = boost::make_shared<Pool4>(IOAddress("192.0.2.140"),
                                          IOAddress("192.0.2.149"));
   pool2->allowClientClass("foo");
   subnet_->addPool(pool2);

   // Forth pool. It only allows client class bar.
   auto pool3 = boost::make_shared<Pool4>(IOAddress("192.0.2.160"),
                                          IOAddress("192.0.2.169"));
   pool3->allowClientClass("bar");
   subnet_->addPool(pool3);

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

   // Remember offered addresses.
   std::set<IOAddress> addresses_set;

   // Simulate client's request belonging to the class bar.
   cc_.insert("bar");
   for (auto i = 0; i < 20; ++i) {
       // Allocate random addresses and make sure they belong to the
       // pools associated with the class bar.
       IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
       EXPECT_FALSE(candidate.isV4Zero());
       EXPECT_TRUE(lease_mgr.addLease(createLease4(candidate, i+50)));
       addresses_set.insert(candidate);
       EXPECT_TRUE(pool1->inRange(candidate) || pool3->inRange(candidate));
   }
   EXPECT_EQ(20, addresses_set.size());

   addresses_set.clear();

   // Simulate the case that the client also belongs to the class foo.
   // All pools should now be available.
   cc_.insert("foo");
   for (auto i = 0; i < 20; ++i) {
       IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
       addresses_set.insert(candidate);
       EXPECT_TRUE(lease_mgr.addLease(createLease4(candidate, i+100)));
       EXPECT_TRUE(subnet_->inRange(candidate));
   }
   EXPECT_EQ(20, addresses_set.size());

   // When the client does not belong to any client class the allocator
   // can't offer any address to the client.
   cc_.clear();
   IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
   EXPECT_TRUE(candidate.isV4Zero());
}

/// @brief Test fixture class for the DHCPv6 Free Lease Queue allocator.
class FreeLeaseQueueAllocatorTest6 : public AllocEngine6Test {
public:

    /// @brief Creates a DHCPv6 lease for an address and DUID.
    ///
    /// @param type lease type.
    /// @param address Lease address.
    /// @param duid_seed a seed from which the DUID is generated.
    /// @return Created lease pointer.
    Lease6Ptr
    createLease6(Lease::Type type, const IOAddress& address, uint64_t duid_seed) const {
        vector<uint8_t> duid_vec(sizeof(duid_seed));
        for (auto i = 0; i < sizeof(duid_seed); ++i) {
            duid_vec[i] = (duid_seed >> i) & 0xFF;
        }
        auto duid = boost::make_shared<DUID>(duid_vec);
        auto lease = boost::make_shared<Lease6>(type, address, duid, 1, 1800,
                                                3600, subnet_->getID());
        return (lease);
    }

};

// Test that the allocator returns the correct type.
TEST_F(FreeLeaseQueueAllocatorTest6, getType) {
    FreeLeaseQueueAllocator allocNA(Lease::TYPE_NA, subnet_);
    EXPECT_EQ("flq", allocNA.getType());

    FreeLeaseQueueAllocator allocPD(Lease::TYPE_PD, subnet_);
    EXPECT_EQ("flq", allocPD.getType());
}

// Test populating free DHCPv6 address leases to the queue.
TEST_F(FreeLeaseQueueAllocatorTest6, populateFreeAddressLeases) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);

    auto& lease_mgr = LeaseMgrFactory::instance();

    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::10"), 0))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::12"), 1))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::14"), 2))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::16"), 3))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::18"), 4))));

    EXPECT_NO_THROW(alloc.initAfterConfigure());

    auto pool_state = boost::dynamic_pointer_cast<PoolFreeLeaseQueueAllocationState>(pool_->getAllocationState());
    ASSERT_TRUE(pool_state);
    EXPECT_FALSE(pool_state->exhausted());

    std::set<IOAddress> addresses;
    for (auto i = 0; i < 12; ++i) {
        auto lease = pool_state->offerFreeLease();
        ASSERT_FALSE(lease.isV6Zero());
        addresses.insert(lease);
    }
    ASSERT_EQ(12, addresses.size());
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::11")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::13")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::15")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::17")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::19")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::1a")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::1b")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::1c")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::1d")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::1e")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::1f")));
    EXPECT_EQ(1, addresses.count(IOAddress("2001:db8:1::20")));
}

// Test allocating IPv6 addresses when a subnet has a single pool.
TEST_F(FreeLeaseQueueAllocatorTest6, singlePool) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);
    ASSERT_NO_THROW(alloc.initAfterConfigure());

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::set<IOAddress> addresses;
    for (auto i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_FALSE(candidate.isV6Zero());
        addresses.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
    }
    // The pool comprises 17 addresses. All should be returned.
    EXPECT_EQ(17, addresses.size());
}

// Test allocating IPv6 addresses and re-allocating these that are
// deleted (released).
TEST_F(FreeLeaseQueueAllocatorTest6, singlePoolWithAllocations) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);
    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::map<IOAddress, Lease6Ptr> leases;
    for (auto i = 0; i < 17; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_FALSE(candidate.isV6Zero());
        auto lease = createLease6(Lease::TYPE_NA, candidate, i);
        leases[candidate] = lease;
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }
    // The pool comprises 17 addresses. All should be returned.
    EXPECT_EQ(17, leases.size());

    IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
    EXPECT_TRUE(candidate.isV6Zero());

    auto i = 0;
    for (auto const& address_lease : leases) {
        if (i % 2) {
            EXPECT_TRUE(lease_mgr.deleteLease(address_lease.second));
        }
        ++i;
    }

    for (auto i = 0; i < 8; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
        auto lease = createLease6(Lease::TYPE_NA, candidate, i);
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }

    candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
    EXPECT_TRUE(candidate.isV6Zero());
}

// Test allocating IPv6 addresses and re-allocating these that are
// reclaimed.
TEST_F(FreeLeaseQueueAllocatorTest6, singlePoolWithReclamations) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);
    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::map<IOAddress, Lease6Ptr> leases;
    for (auto i = 0; i < 17; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_FALSE(candidate.isV6Zero());
        auto lease = createLease6(Lease::TYPE_NA, candidate, i);
        leases[candidate] = lease;
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }
    // The pool comprises 17 addresses. All should be returned.
    EXPECT_EQ(17, leases.size());

    IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
    EXPECT_TRUE(candidate.isV6Zero());

    auto i = 0;
    for (auto const& address_lease : leases) {
        if (i % 2) {
            auto lease = address_lease.second;
            lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
            EXPECT_NO_THROW(lease_mgr.updateLease6(lease));
        }
        ++i;
    }

    for (auto i = 0; i < 8; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
        auto lease = lease_mgr.getLease6(Lease::TYPE_NA, candidate);
        lease->state_ = Lease::STATE_DEFAULT;
        EXPECT_NO_THROW(lease_mgr.updateLease6(lease));
    }

    candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
    EXPECT_TRUE(candidate.isV6Zero());
}

// Test allocating DHCPv6 leases for many pools in a subnet.
TEST_F(FreeLeaseQueueAllocatorTest6, manyPools) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);

    // Add several more pools.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;
        min << "2001:db8:1::" << hex << i * 16 + 1;
        max << "2001:db8:1::" << hex << i * 16 + 16;
        auto pool = boost::make_shared<Pool6>(Lease::TYPE_NA,
                                              IOAddress(min.str()),
                                              IOAddress(max.str()));
        subnet_->addPool(pool);
    }

    // First pool (::10 - ::20) has 17 addresses.
    // There are 8 extra pools with 16 addresses in each.
    int total = 17 + 8 * 16;

    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    std::set<IOAddress> addresses_set;
    std::vector<IOAddress> addresses_vector;
    std::vector<PoolPtr> pools_vector;

    // Pick random addresses the number of times equal to the
    // subnet capacity to ensure that all addresses are returned.
    for (auto i = 0; i < total; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        addresses_set.insert(candidate);
        addresses_vector.push_back(candidate);
        auto lease = createLease6(Lease::TYPE_NA, candidate, i);
        EXPECT_TRUE(lease_mgr.addLease(lease));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
        pools_vector.push_back(subnet_->getPool(Lease::TYPE_NA, candidate));
    }
    // Make sure that unique addresses have been returned.
    EXPECT_EQ(total, addresses_set.size());

    // Verify that the addresses are returned in the random order.
    // Count how many times we found consecutive addresses. It should
    // be 0 or close to 0.
    int consecutive_addresses = 0;
    for (auto k = 0; k < addresses_vector.size()-1; ++k) {
        if (IOAddress::increase(addresses_vector[k]) == addresses_vector[k+1]) {
            ++consecutive_addresses;
        }
    }
    // Ideally, the number of consecutive occurrences should be 0 but we
    // allow some to make sure the test doesn't fall over sporadically.
    EXPECT_LT(consecutive_addresses, addresses_vector.size()/4);

    // Repeat similar check for pools. The pools should be picked in the
    // random order too.
    int consecutive_pools = 0;
    for (auto k = 0; k < pools_vector.size()-1; ++k) {
        if (IOAddress::increase(pools_vector[k]->getLastAddress()) ==
            pools_vector[k]->getFirstAddress()) {
            ++consecutive_pools;
        }
    }
    EXPECT_LT(consecutive_pools, pools_vector.size()/2);
}

// Test that the allocator returns a zero address when there are no pools
// in a subnet.
TEST_F(FreeLeaseQueueAllocatorTest6, noPools) {
   FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);

   subnet_->delPools(Lease::TYPE_NA);

   IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
   EXPECT_TRUE(candidate.isV6Zero());
}

// Test that the allocator respects client class guards.
TEST_F(FreeLeaseQueueAllocatorTest6, clientClasses) {
   FreeLeaseQueueAllocator alloc(Lease::TYPE_NA, subnet_);

   // First pool only allows the client class foo.
   pool_->allowClientClass("foo");

   // Second pool. It only allows client class bar.
   auto pool1 = boost::make_shared<Pool6>(Lease::TYPE_NA,
                                          IOAddress("2001:db8:1::120"),
                                          IOAddress("2001:db8:1::129"));
   pool1->allowClientClass("bar");
   subnet_->addPool(pool1);

   // Third pool. It only allows client class foo.
   auto pool2 = boost::make_shared<Pool6>(Lease::TYPE_NA,
                                          IOAddress("2001:db8:1::140"),
                                          IOAddress("2001:db8:1::149"));
   pool2->allowClientClass("foo");
   subnet_->addPool(pool2);

   // Forth pool. It only allows client class bar.
   auto pool3 = boost::make_shared<Pool6>(Lease::TYPE_NA,
                                          IOAddress("2001:db8:1::160"),
                                          IOAddress("2001:db8:1::169"));
   pool3->allowClientClass("bar");
   subnet_->addPool(pool3);

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

   // When the client does not belong to any client class the allocator
   // can't offer any address to the client.
   IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
   EXPECT_TRUE(candidate.isV6Zero());

   // Remember offered addresses.
   std::set<IOAddress> addresses_set;

   // Simulate client's request belonging to the class bar.
   cc_.insert("bar");
   for (auto i = 0; i < 20; ++i) {
       // Allocate random addresses and make sure they belong to the
       // pools associated with the class bar.
       IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
       EXPECT_FALSE(candidate.isV6Zero());
       EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_NA, candidate, i+50)));
       addresses_set.insert(candidate);
       EXPECT_TRUE(pool1->inRange(candidate) || pool3->inRange(candidate));
   }
   EXPECT_EQ(20, addresses_set.size());

   // Simulate the case that the client also belongs to the class foo.
   // All pools should now be available.
   cc_.insert("foo");
   for (auto i = 0; i < 27; ++i) {
       IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
       addresses_set.insert(candidate);
       EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_NA, candidate, i+100)));
       EXPECT_TRUE(subnet_->inRange(candidate));
   }
   EXPECT_EQ(47, addresses_set.size());
}

// Test populating free DHCPv6 prefix leases to the queue.
TEST_F(FreeLeaseQueueAllocatorTest6, populateFreePrefixDelegationLeases) {
    subnet_->delPools(Lease::TYPE_PD);

    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);

    auto pool = Pool6::create(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 112, 120);
    subnet_->addPool(pool);

    auto& lease_mgr = LeaseMgrFactory::instance();

    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 0))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_PD, IOAddress("2001:db8:2::1000"), 1))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_PD, IOAddress("2001:db8:2::2000"), 2))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_PD, IOAddress("2001:db8:2::3000"), 3))));
    EXPECT_TRUE(lease_mgr.addLease((createLease6(Lease::TYPE_PD, IOAddress("2001:db8:2::4000"), 4))));

    EXPECT_NO_THROW(alloc.initAfterConfigure());

    auto pool_state = boost::dynamic_pointer_cast<PoolFreeLeaseQueueAllocationState>(pool->getAllocationState());
    ASSERT_TRUE(pool_state);
    EXPECT_FALSE(pool_state->exhausted());

    std::set<IOAddress> addresses;
    for (auto i = 0; i < 256; ++i) {
        auto lease = pool_state->offerFreeLease();
        ASSERT_FALSE(lease.isV6Zero());
        addresses.insert(lease);
    }
    ASSERT_EQ(251, addresses.size());
    EXPECT_EQ(0, addresses.count(IOAddress("2001:db8:2::")));
    EXPECT_EQ(0, addresses.count(IOAddress("2001:db8:2::1000")));
    EXPECT_EQ(0, addresses.count(IOAddress("2001:db8:2::2000")));
    EXPECT_EQ(0, addresses.count(IOAddress("2001:db8:2::3000")));
    EXPECT_EQ(0, addresses.count(IOAddress("2001:db8:2::4000")));
}

// Test allocating delegated prefixes when a subnet has a single pool.
TEST_F(FreeLeaseQueueAllocatorTest6, singlePdPool) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);
    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

    Pool6Ptr pool;

    // Remember returned prefixes, so we can verify that unique addresses
    // are returned.
    std::set<IOAddress> prefixes;
    for (auto i = 0; i < 65536; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        EXPECT_EQ(pd_pool_, pool);
        EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_PD, candidate, i)));
        prefixes.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }
    // The pool comprises 65536 prefixes. All should be returned.
    EXPECT_EQ(65536, prefixes.size());
}

// Test allocating IPv6 addresses and re-allocating these that are
// deleted (released).
TEST_F(FreeLeaseQueueAllocatorTest6, singlePdPoolWithAllocations) {
    // Remove the default pool because it is too large for this test case.
    subnet_->delPools(Lease::TYPE_PD);
    // Add a smaller pool.
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                          IOAddress("3000::"),
                                          120,
                                          128);
    subnet_->addPool(pool);

    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);
    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::map<IOAddress, Lease6Ptr> leases;
    for (auto i = 0; i < 256; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        EXPECT_FALSE(candidate.isV6Zero());
        auto lease = createLease6(Lease::TYPE_PD, candidate, i);
        leases[candidate] = lease;
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }
    // The pool comprises 256 delegated prefixes. All should be returned.
    EXPECT_EQ(256, leases.size());

    IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
    EXPECT_TRUE(candidate.isV6Zero());

    auto i = 0;
    for (auto const& address_lease : leases) {
        if (i % 2) {
            EXPECT_TRUE(lease_mgr.deleteLease(address_lease.second));
        }
        ++i;
    }

    for (auto i = 0; i < 128; ++i) {
        candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        auto lease = createLease6(Lease::TYPE_PD, candidate, i);
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }

    candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
    EXPECT_TRUE(candidate.isV6Zero());
}

// Test allocating IPv6 addresses and re-allocating these that are
// reclaimed.
TEST_F(FreeLeaseQueueAllocatorTest6, singlePdPoolWithReclamations) {
    // Remove the default pool because it is too large for this test case.
    subnet_->delPools(Lease::TYPE_PD);
    // Add a smaller pool.
    auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                          IOAddress("3000::"),
                                          120,
                                          128);
    subnet_->addPool(pool);

    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);
    ASSERT_NO_THROW(alloc.initAfterConfigure());

    auto& lease_mgr = LeaseMgrFactory::instance();

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::map<IOAddress, Lease6Ptr> leases;
    for (auto i = 0; i < 256; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        EXPECT_FALSE(candidate.isV6Zero());
        auto lease = createLease6(Lease::TYPE_PD, candidate, i);
        leases[candidate] = lease;
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        EXPECT_TRUE(lease_mgr.addLease(lease));
    }
    // The pool comprises 256 delegated prefixes. All should be returned.
    EXPECT_EQ(256, leases.size());

    IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
    EXPECT_TRUE(candidate.isV6Zero());

    auto i = 0;
    for (auto const& address_lease : leases) {
        if (i % 2) {
            auto lease = address_lease.second;
            lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
            EXPECT_NO_THROW(lease_mgr.updateLease6(lease));
        }
        ++i;
    }

    for (auto i = 0; i < 128; ++i) {
        candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        auto lease = lease_mgr.getLease6(Lease::TYPE_PD, candidate);
        lease->state_ = Lease::STATE_DEFAULT;
        EXPECT_NO_THROW(lease_mgr.updateLease6(lease));
    }

    candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
    EXPECT_TRUE(candidate.isV6Zero());
}


// Test allocating delegated prefixes from multiple pools.
TEST_F(FreeLeaseQueueAllocatorTest6, manyPdPools) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);

    for (auto i = 0; i < 10; ++i) {
        ostringstream s;
        s << "300" << hex << i + 1 << "::";
        auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                              IOAddress(s.str()),
                                              120,
                                              128);
        subnet_->addPool(pool);
    }
    size_t total = 65536 + 10 * 256;

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

    Pool6Ptr pool;

    std::set<IOAddress> prefixes;
    for (auto i = 0; i < total; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        EXPECT_TRUE(pool);
        EXPECT_FALSE(candidate.isV6Zero());
        EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_PD, candidate, i)));
        prefixes.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }
    // Make sure that unique prefixes have been returned.
    EXPECT_EQ(total, prefixes.size());
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(FreeLeaseQueueAllocatorTest6, manyPdPoolsPreferLower) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);

    for (auto i = 0; i < 10; ++i) {
        ostringstream s;
        s << "300" << hex << i + 1 << "::";
        auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                              IOAddress(s.str()),
                                              120,
                                              128);
        subnet_->addPool(pool);
    }

    size_t total = 65536;

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();


    Pool6Ptr pool;

    std::set<IOAddress> prefixes;
    for (auto i = 0; i < total; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 120);
        EXPECT_FALSE(candidate.isV6Zero());
        EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_PD, candidate, i)));
        prefixes.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }
    // Make sure that unique prefixes have been returned.
    EXPECT_EQ(total, prefixes.size());
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(FreeLeaseQueueAllocatorTest6, manyPdPoolsPreferEqual) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);

    for (auto i = 0; i < 10; ++i) {
        ostringstream s;
        s << "300" << hex << i + 1 << "::";
        auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                              IOAddress(s.str()),
                                              120,
                                              128);
        subnet_->addPool(pool);
    }

    size_t total = 10 * 256;

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

    Pool6Ptr pool;

    std::set<IOAddress> prefixes;
    for (auto i = 0; i < total; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_EQUAL, IOAddress("::"), 128);
        EXPECT_FALSE(candidate.isV6Zero());
        EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_PD, candidate, i)));
        prefixes.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }
    // Make sure that unique prefixes have been returned.
    EXPECT_EQ(total, prefixes.size());
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(FreeLeaseQueueAllocatorTest6, manyPdPoolsPreferHigher) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);

    for (auto i = 0; i < 10; ++i) {
        ostringstream s;
        s << "300" << hex << i + 1 << "::";
        auto pool = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                              IOAddress(s.str()),
                                              120,
                                              128);
        subnet_->addPool(pool);
    }

    size_t total = 10 * 256;

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

    Pool6Ptr pool;

    std::set<IOAddress> prefixes;
    for (auto i = 0; i < total; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 64);
        EXPECT_FALSE(candidate.isV6Zero());
        EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_PD, candidate, i)));
        prefixes.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }
    // Make sure that unique prefixes have been returned.
    EXPECT_EQ(total, prefixes.size());
}

// Test that the allocator respects client class guards.
TEST_F(FreeLeaseQueueAllocatorTest6, pdPoolsClientClasses) {
    FreeLeaseQueueAllocator alloc(Lease::TYPE_PD, subnet_);

    // First pool only allows the client class foo.
    pd_pool_->allowClientClass("foo");

    auto pool2 = boost::make_shared<Pool6>(Lease::TYPE_PD,
                                           IOAddress("3000:1::"),
                                           120,
                                           128);
    // Second pool only allows the client class bar.
    pool2->allowClientClass("bar");
    subnet_->addPool(pool2);

    ASSERT_NO_THROW(alloc.initAfterConfigure());
    auto& lease_mgr = LeaseMgrFactory::instance();

    Pool6Ptr pool;

    IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 64);
    EXPECT_TRUE(candidate.isV6Zero());

    cc_.insert("bar");
    for (auto i = 0; i < 256; ++i) {
        candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 64);
        EXPECT_FALSE(candidate.isV6Zero());
        EXPECT_TRUE(lease_mgr.addLease(createLease6(Lease::TYPE_PD, candidate, i)));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }

    candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 64);
    EXPECT_TRUE(candidate.isV6Zero());
}


} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
