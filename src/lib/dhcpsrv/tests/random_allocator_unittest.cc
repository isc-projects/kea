// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/random_allocator.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <sstream>

using namespace isc::asiolink;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {

using RandomAllocatorTest4 = AllocEngine4Test;

// Test allocating IPv4 addresses when a subnet has a single pool.
TEST_F(RandomAllocatorTest4, singlePool) {
    RandomAllocator alloc(Lease::TYPE_V4, subnet_);

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

// Test allocating IPv4 addresses from multiple pools.
TEST_F(RandomAllocatorTest4, manyPools) {
    RandomAllocator alloc(Lease::TYPE_V4, subnet_);

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

    // Repeat allocation of all addresses several times. Make sure that
    // the same addresses are returned when all pools are exhausted.
    for (auto j = 0; j < 6; ++j) {
        std::set<IOAddress> addresses_set;
        std::vector<IOAddress> addresses_vector;
        std::vector<PoolPtr> pools_vector;

        // Pick random addresses the number of times equal to the
        // subnet capacity to ensure that all addresses are returned.
        for (auto i = 0; i < total; ++i) {
            IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
            addresses_set.insert(candidate);
            addresses_vector.push_back(candidate);
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
}

// Test that the allocator returns a zero address when there are no
// pools.
TEST_F(RandomAllocatorTest4, noPools) {
   RandomAllocator alloc(Lease::TYPE_V4, subnet_);

   subnet_->delPools(Lease::TYPE_V4);

   IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
   EXPECT_TRUE(candidate.isV4Zero());
}

// Test that the allocator respects client classes while it picks
// pools and addresses.
TEST_F(RandomAllocatorTest4, clientClasses) {
   RandomAllocator alloc(Lease::TYPE_V4, subnet_);

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

   // Remember offered addresses.
   std::set<IOAddress> addresses_set;

   // Simulate client's request belonging to the class bar.
   cc_.insert("bar");
   for (auto i = 0; i < 40; ++i) {
       // Allocate random addresses and make sure they belong to the
       // pools associated with the class bar.
       IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
       addresses_set.insert(candidate);
       EXPECT_TRUE(pool1->inRange(candidate) || pool3->inRange(candidate));
   }
   EXPECT_EQ(20, addresses_set.size());

   addresses_set.clear();

   // Simulate the case that the client also belongs to the class foo.
   // All pools should now be available.
   cc_.insert("foo");
   for (auto i = 0; i < 60; ++i) {
       IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
       addresses_set.insert(candidate);
       EXPECT_TRUE(subnet_->inRange(candidate));
   }
   EXPECT_EQ(40, addresses_set.size());

   // When the client does not belong to any client class the allocator
   // can't offer any address to the client.
   cc_.clear();
   IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
   EXPECT_TRUE(candidate.isV4Zero());
}

using RandomAllocatorTest6 = AllocEngine6Test;

// Test allocating IPv6 addresses when a subnet has a single pool.
TEST_F(RandomAllocatorTest6, singlePool) {
    RandomAllocator alloc(Lease::TYPE_NA, subnet_);

    // Remember returned addresses, so we can verify that unique addresses
    // are returned.
    std::set<IOAddress> addresses;
    for (auto i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
        addresses.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
    }
    // The pool comprises 17 addresses. All should be returned.
    EXPECT_EQ(17, addresses.size());
}

// Test allocating IPv6 addresses from multiple pools.
TEST_F(RandomAllocatorTest6, manyPools) {
    RandomAllocator alloc(Lease::TYPE_NA, subnet_);

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

    // Repeat allocation of all addresses several times. Make sure that
    // the same addresses are returned when all pools are exhausted.
    for (auto j = 0; j < 6; ++j) {
        std::set<IOAddress> addresses_set;
        std::vector<IOAddress> addresses_vector;
        std::vector<PoolPtr> pools_vector;

        // Pick random addresses the number of times equal to the
        // subnet capacity to ensure that all addresses are returned.
        for (auto i = 0; i < total; ++i) {
            IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
            addresses_set.insert(candidate);
            addresses_vector.push_back(candidate);
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
}

// Test that the allocator respects client classes while it picks
// pools and addresses.
TEST_F(RandomAllocatorTest6, clientClasses) {
   RandomAllocator alloc(Lease::TYPE_NA, subnet_);

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

   // Remember offered addresses.
   std::set<IOAddress> addresses_set;

   // Simulate client's request belonging to the class bar.
   cc_.insert("bar");
   for (auto i = 0; i < 60; ++i) {
       // Allocate random addresses and make sure they belong to the
       // pools associated with the class bar.
       IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
       addresses_set.insert(candidate);
       EXPECT_TRUE(pool1->inRange(candidate) || pool3->inRange(candidate));
   }
   EXPECT_EQ(20, addresses_set.size());

   addresses_set.clear();

   // Simulate the case that the client also belongs to the class foo.
   // All pools should now be available.
   cc_.insert("foo");
   for (auto i = 0; i < 100; ++i) {
       IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
       addresses_set.insert(candidate);
       EXPECT_TRUE(subnet_->inRange(candidate));
   }
   EXPECT_EQ(47, addresses_set.size());

   // When the client does not belong to any client class the allocator
   // can't offer any address to the client.
   cc_.clear();
   IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("0.0.0.0"));
   EXPECT_TRUE(candidate.isV4Zero());
}

// Test allocating delegated prefixes when a subnet has a single pool.
TEST_F(RandomAllocatorTest6, singlePdPool) {
    RandomAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // Remember returned prefixes, so we can verify that unique addresses
    // are returned.
    std::set<IOAddress> prefixes;
    for (auto i = 0; i < 66000; ++i) {
        IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
        prefixes.insert(candidate);
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
    }
    // The pool comprises 65536 prefixes. All should be returned.
    EXPECT_EQ(65536, prefixes.size());
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(RandomAllocatorTest6, manyPdPools) {
    RandomAllocator alloc(Lease::TYPE_PD, subnet_);

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

    Pool6Ptr pool;

    for (auto j = 0; j < 2; ++j) {
        std::set<IOAddress> prefixes;
        for (auto i = 0; i < total; ++i) {
            IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0);
            prefixes.insert(candidate);
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        }
        // Make sure that unique prefixes have been returned.
        EXPECT_EQ(total, prefixes.size());
    }
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(RandomAllocatorTest6, manyPdPoolsPreferLower) {
    RandomAllocator alloc(Lease::TYPE_PD, subnet_);

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

    Pool6Ptr pool;

    for (auto j = 0; j < 2; ++j) {
        std::set<IOAddress> prefixes;
        for (auto i = 0; i < total; ++i) {
            IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 120);
            prefixes.insert(candidate);
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        }
        // Make sure that unique prefixes have been returned.
        EXPECT_EQ(total, prefixes.size());
    }
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(RandomAllocatorTest6, manyPdPoolsPreferEqual) {
    RandomAllocator alloc(Lease::TYPE_PD, subnet_);

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

    Pool6Ptr pool;

    for (auto j = 0; j < 2; ++j) {
        std::set<IOAddress> prefixes;
        for (auto i = 0; i < total; ++i) {
            IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_EQUAL, IOAddress("::"), 128);
            prefixes.insert(candidate);
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        }
        // Make sure that unique prefixes have been returned.
        EXPECT_EQ(total, prefixes.size());
    }
}

// Test allocating delegated prefixes from multiple pools.
TEST_F(RandomAllocatorTest6, manyPdPoolsPreferHigher) {
    RandomAllocator alloc(Lease::TYPE_PD, subnet_);

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

    Pool6Ptr pool;

    for (auto j = 0; j < 2; ++j) {
        std::set<IOAddress> prefixes;
        for (auto i = 0; i < total; ++i) {
            IOAddress candidate = alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 64);
            prefixes.insert(candidate);
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate));
            EXPECT_TRUE(subnet_->inPool(Lease::TYPE_PD, candidate, cc_));
        }
        // Make sure that unique prefixes have been returned.
        EXPECT_EQ(total, prefixes.size());
    }
}

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
