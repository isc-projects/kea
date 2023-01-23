// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/iterative_allocator.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {

using IterativeAllocatorTest4 = AllocEngine4Test;

// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(IterativeAllocatorTest4, basic) {
    boost::scoped_ptr<Allocator> alloc(new IterativeAllocator(Lease::TYPE_V4, subnet_));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
    }
}

// This test verifies that the allocator picks addresses that belong to the
// pool using classification
TEST_F(IterativeAllocatorTest4, clientClass) {
    boost::scoped_ptr<Allocator> alloc(new IterativeAllocator(Lease::TYPE_V4, subnet_));

    // Restrict pool_ to the foo class. Add a second pool with bar class.
    pool_->allowClientClass("foo");
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.200"),
                            IOAddress("192.0.2.209")));
    pool->allowClientClass("bar");
    subnet_->addPool(pool);

    // Clients are in bar
    cc_.insert("bar");

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, candidate, cc_));
    }
}

// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space.
TEST_F(IterativeAllocatorTest4, manyPools) {
    IterativeAllocator alloc(Lease::TYPE_V4, subnet_);

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
        IOAddress candidate = alloc.pickAddress(cc_, clientid_, IOAddress("0.0.0.0"));
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

        if (cnt > total) {
            ADD_FAILURE() << "Too many unique addresses generated.";
            break;
        }
    }
}

using IterativeAllocatorTest6 = AllocEngine6Test;

// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(IterativeAllocatorTest6, basic) {
    boost::scoped_ptr<Allocator> alloc(new NakedIterativeAllocator(Lease::TYPE_NA, subnet_));

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
    }
}

// This test verifies that the allocator picks addresses that belong to the
// pool using classification
TEST_F(IterativeAllocatorTest6, clientClass) {
    boost::scoped_ptr<Allocator> alloc(new NakedIterativeAllocator(Lease::TYPE_NA, subnet_));

    // Restrict pool_ to the foo class. Add a second pool with bar class.
    pool_->allowClientClass("foo");
    Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                            IOAddress("2001:db8:1::109")));
    pool->allowClientClass("bar");
    subnet_->addPool(pool);

    // Clients are in bar
    cc_.insert("bar");

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(cc_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate));
        EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, candidate, cc_));
    }
}

// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice.
// unless it runs out of pool space.
TEST_F(IterativeAllocatorTest6, manyPools) {
    NakedIterativeAllocator alloc(Lease::TYPE_NA, subnet_);

    // let's start from 2, as there is 2001:db8:1::10 - 2001:db8:1::20 pool already.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;

        min << "2001:db8:1::" << hex << i * 16 + 1;
        max << "2001:db8:1::" << hex << i * 16 + 9;

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
        IOAddress candidate = alloc.pickAddress(cc_, duid_, IOAddress("::"));
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

        if (cnt > total) {
            ADD_FAILURE() << "Too many unique addresses generated.";
            break;
        }
    }
}

// This test verifies that the allocator walks over the addresses in the
// non-contiguous pools.
TEST_F(IterativeAllocatorTest6, addrStep) {
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

    NakedIterativeAllocator alloc(Lease::TYPE_NA, subnet_);

    // Let's check the first pool (5 addresses here)
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // The second pool is easy - only one address here
    EXPECT_EQ("2001:db8:1::100",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
}

// This test verifies that the allocator walks over the addresses in the
// non-contiguous pools when pools contain class guards.
TEST_F(IterativeAllocatorTest6, addrStepInClass) {
    subnet_->delPools(Lease::TYPE_NA); // Get rid of default pool

    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::5")));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                             IOAddress("2001:db8:1::100")));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::105"),
                             IOAddress("2001:db8:1::106")));
    // Set pool1 and pool3 but not pool2 in foo class
    pool1->allowClientClass("foo");
    pool3->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_NA, subnet_);

    // Clients are in foo
    cc_.insert("foo");

    // Let's check the first pool (5 addresses here)
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // The second pool is easy - only one address here
    EXPECT_EQ("2001:db8:1::100",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
}

// This test verifies that the allocator omits pools with non-matching class guards.
TEST_F(IterativeAllocatorTest6, addrStepOutClass) {
    subnet_->delPools(Lease::TYPE_NA); // Get rid of default pool

    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::5")));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::100"),
                             IOAddress("2001:db8:1::100")));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::105"),
                             IOAddress("2001:db8:1::106")));
    // Set pool2 in foo
    pool2->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_NA, subnet_);

    // Let's check the first pool (5 addresses here)
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::3",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::4",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::5",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // The second pool is skipped

    // This is the third and last pool, with 2 addresses in it
    EXPECT_EQ("2001:db8:1::105",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::106",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());

    // We iterated over all addresses and reached to the end of the last pool.
    // Let's wrap around and start from the beginning
    EXPECT_EQ("2001:db8:1::1",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
    EXPECT_EQ("2001:db8:1::2",
              alloc.pickAddress(cc_, duid_, IOAddress("::")).toText());
}

// This test verifies that the allocator picks delegated prefixes from several
// pools.
TEST_F(IterativeAllocatorTest6, prefixStep) {
    subnet_ = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
}

// This test verifies that the allocator picks delegated prefixes from several
// pools.
TEST_F(IterativeAllocatorTest6, prefixStepPreferLower) {
    subnet_ = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_LOWER, IOAddress("::"), 64).toText());
}

// This test verifies that the allocator picks delegated prefixes from several
// pools.
TEST_F(IterativeAllocatorTest6, prefixStepPreferEqual) {
    subnet_ = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_EQUAL, IOAddress("::"), 48).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over second pool again)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_EQUAL, IOAddress("::"), 48).toText());
}

// This test verifies that the allocator picks delegated prefixes from several
// pools.
TEST_F(IterativeAllocatorTest6, prefixStepPreferHigher) {
    subnet_ = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 60).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 60).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 60).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over third pool again)
    EXPECT_EQ("2001:db8:2::",
                  alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 60).toText());
}

// This test verifies that the allocator picks delegated prefixes from the pools
// with class guards.
TEST_F(IterativeAllocatorTest6, prefixStepInClass) {
    subnet_ = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    // Set pool1 and pool3 but not pool2 in foo class
    pool1->allowClientClass("foo");
    pool3->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // Clients are in foo
    cc_.insert("foo");

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Second pool (just one lease here)
    EXPECT_EQ("2001:db8:1::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
}

// This test verifies that the allocator omits pools with non-matching client classes.
TEST_F(IterativeAllocatorTest6, prefixStepOutClass) {
    subnet_ = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 56, 60));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 48));
    Pool6Ptr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 56, 64));
    // Set pool2 in foo
    pool2->allowClientClass("foo");
    subnet_->addPool(pool1);
    subnet_->addPool(pool2);
    subnet_->addPool(pool3);

    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

    Pool6Ptr pool;

    // We have a 2001:db8::/48 subnet that has 3 pools defined in it:
    // 2001:db8::/56 split into /60 prefixes (16 leases) (or 2001:db8:0:X0::)
    // 2001:db8:1::/48 split into a single /48 prefix (just 1 lease)
    // 2001:db8:2::/56 split into /64 prefixes (256 leases) (or 2001:db8:2:XX::)

    // First pool check (Let's check over all 16 leases)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:20::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:30::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:40::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:50::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:60::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:70::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:80::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:90::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:a0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:b0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:c0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:d0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:e0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:f0::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // The second pool is skipped

    // Third pool (256 leases, let's check first and last explicitly and the
    // rest over in a pool
    EXPECT_EQ("2001:db8:2::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    for (int i = 1; i < 255; i++) {
        stringstream exp;
        exp << "2001:db8:2:" << hex << i << dec << "::";
        EXPECT_EQ(exp.str(),
                  alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    }
    EXPECT_EQ("2001:db8:2:ff::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());

    // Ok, we've iterated over all prefixes in all pools. We now wrap around.
    // We're looping over now (iterating over first pool again)
    EXPECT_EQ("2001:db8::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
    EXPECT_EQ("2001:db8:0:10::",
              alloc.pickPrefix(cc_, pool, duid_, Allocator::PREFIX_LEN_HIGHER, IOAddress("::"), 0).toText());
}

// This test verifies that the iterative allocator can step over addresses.
TEST_F(IterativeAllocatorTest6, addressIncrease) {
    NakedIterativeAllocator alloc(Lease::TYPE_NA, subnet_);

    // Let's pick the first address
    IOAddress addr1 = alloc.pickAddress(cc_, duid_, IOAddress("2001:db8:1::10"));

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

// This test verifies that the allocator can step over prefixes.
TEST_F(IterativeAllocatorTest6, prefixIncrease) {
    NakedIterativeAllocator alloc(Lease::TYPE_PD, subnet_);

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

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
