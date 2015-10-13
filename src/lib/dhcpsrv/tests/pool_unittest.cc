// Copyright (C) 2012-2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/pool.h>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <sstream>

using boost::scoped_ptr;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

TEST(Pool4Test, constructor_first_last) {

    // let's construct 192.0.2.1-192.0.2.255 pool
    Pool4 pool1(IOAddress("192.0.2.1"), IOAddress("192.0.2.255"));

    EXPECT_EQ(IOAddress("192.0.2.1"), pool1.getFirstAddress());
    EXPECT_EQ(IOAddress("192.0.2.255"), pool1.getLastAddress());

    // This is Pool4, IPv6 addresses do not belong here
    EXPECT_THROW(Pool4(IOAddress("2001:db8::1"),
                       IOAddress("192.168.0.5")), BadValue);
    EXPECT_THROW(Pool4(IOAddress("192.168.0.2"),
                       IOAddress("2001:db8::1")), BadValue);

    // Should throw. Range should be 192.0.2.1-192.0.2.2, not
    // the other way around.
    EXPECT_THROW(Pool4(IOAddress("192.0.2.2"), IOAddress("192.0.2.1")),
                 BadValue);
}

TEST(Pool4Test, constructor_prefix_len) {

    // let's construct 2001:db8:1::/96 pool
    Pool4 pool1(IOAddress("192.0.2.0"), 25);

    EXPECT_EQ("192.0.2.0", pool1.getFirstAddress().toText());
    EXPECT_EQ("192.0.2.127", pool1.getLastAddress().toText());

    // No such thing as /33 prefix
    EXPECT_THROW(Pool4(IOAddress("192.0.2.1"), 33), BadValue);

    // /0 prefix does not make sense
    EXPECT_THROW(Pool4(IOAddress("192.0.2.0"), 0), BadValue);

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool4(IOAddress("2001:db8::1"), 20), BadValue);
}

TEST(Pool4Test, in_range) {
   Pool4 pool1(IOAddress("192.0.2.10"), IOAddress("192.0.2.20"));

   EXPECT_FALSE(pool1.inRange(IOAddress("192.0.2.0")));
   EXPECT_TRUE(pool1.inRange(IOAddress("192.0.2.10")));
   EXPECT_TRUE(pool1.inRange(IOAddress("192.0.2.17")));
   EXPECT_TRUE(pool1.inRange(IOAddress("192.0.2.20")));
   EXPECT_FALSE(pool1.inRange(IOAddress("192.0.2.21")));
   EXPECT_FALSE(pool1.inRange(IOAddress("192.0.2.255")));
   EXPECT_FALSE(pool1.inRange(IOAddress("255.255.255.255")));
   EXPECT_FALSE(pool1.inRange(IOAddress("0.0.0.0")));
}

// Checks if the number of possible leases in range is reported correctly.
TEST(Pool4Test, leasesCount) {
    Pool4 pool1(IOAddress("192.0.2.10"), IOAddress("192.0.2.20"));
    EXPECT_EQ(11, pool1.getCapacity());

    Pool4 pool2(IOAddress("192.0.2.0"), IOAddress("192.0.2.255"));
    EXPECT_EQ(256, pool2.getCapacity());

    Pool4 pool3(IOAddress("192.168.0.0"), IOAddress("192.168.255.255"));
    EXPECT_EQ(65536, pool3.getCapacity());

    Pool4 pool4(IOAddress("10.0.0.0"), IOAddress("10.255.255.255"));
    EXPECT_EQ(16777216, pool4.getCapacity());
}

// This test creates 100 pools and verifies that their IDs are unique.
TEST(Pool4Test, unique_id) {

    const int num_pools = 100;
    std::vector<Pool4Ptr> pools;

    for (int i = 0; i < num_pools; ++i) {
        pools.push_back(Pool4Ptr(new Pool4(IOAddress("192.0.2.0"),
                                           IOAddress("192.0.2.255"))));
    }

    for (int i = 0; i < num_pools; ++i) {
        for (int j = i + 1; j < num_pools; ++j) {
            if (pools[i]->getId() == pools[j]->getId()) {
                FAIL() << "Pool-ids must be unique";
            }
        }
    }
}

// Simple check if toText returns reasonable values
TEST(Pool4Test,toText) {
    Pool4 pool1(IOAddress("192.0.2.7"), IOAddress("192.0.2.17"));
    EXPECT_EQ("type=V4, 192.0.2.7-192.0.2.17", pool1.toText());

    Pool4 pool2(IOAddress("192.0.2.128"), 28);
    EXPECT_EQ("type=V4, 192.0.2.128-192.0.2.143", pool2.toText());
}

TEST(Pool6Test, constructor_first_last) {

    // let's construct 2001:db8:1:: - 2001:db8:1::ffff:ffff:ffff:ffff pool
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8:1::"),
                IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"));

    EXPECT_EQ(Lease::TYPE_NA, pool1.getType());
    EXPECT_EQ(IOAddress("2001:db8:1::"), pool1.getFirstAddress());
    EXPECT_EQ(IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"),
              pool1.getLastAddress());

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                       IOAddress("192.168.0.5")), BadValue);
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("192.168.0.2"),
                       IOAddress("2001:db8::1")), BadValue);

    // Should throw. Range should be 2001:db8::1 - 2001:db8::2, not
    // the other way around.
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::2"),
                       IOAddress("2001:db8::1")), BadValue);
}

TEST(Pool6Test, constructor_prefix_len) {

    // let's construct 2001:db8:1::/96 pool
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 96);

    EXPECT_EQ(Lease::TYPE_NA, pool1.getType());
    EXPECT_EQ("2001:db8:1::", pool1.getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1.getLastAddress().toText());

    // No such thing as /130 prefix
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 130),
                 BadValue);

    // /0 prefix does not make sense
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 0),
                 BadValue);

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("192.168.0.2"), 96),
                 BadValue);

    // Delegated prefix length for addresses must be /128
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 96, 125),
                 BadValue);
}

TEST(Pool6Test, in_range) {
   Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
               IOAddress("2001:db8:1::f"));

   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::1")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::7")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::f")));
   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::10")));
   EXPECT_FALSE(pool1.inRange(IOAddress("::")));
}

// Checks that Prefix Delegation pools are handled properly
TEST(Pool6Test, PD) {

    // Let's construct 2001:db8:1::/96 PD pool, split into /112 prefixes
    Pool6 pool1(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);

    EXPECT_EQ(Lease::TYPE_PD, pool1.getType());
    EXPECT_EQ(112, pool1.getLength());
    EXPECT_EQ("2001:db8:1::", pool1.getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1.getLastAddress().toText());

    // Check that it's not possible to have min-max range for PD
    EXPECT_THROW(Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::f")), BadValue);

    // Check that it's not allowed to delegate bigger prefix than the pool
    // Let's try to split /64 prefix into /56 chunks (should be impossible)
    EXPECT_THROW(Pool6 pool3(Lease::TYPE_PD, IOAddress("2001:db8:1::"),
                             64, 56), BadValue);

    // It should be possible to have a pool split into just a single chunk
    // Let's try to split 2001:db8:1::/77 into a single /77 delegated prefix
    EXPECT_NO_THROW(Pool6 pool4(Lease::TYPE_PD, IOAddress("2001:db8:1::"),
                                77, 77));
}

// Checks that temporary address pools are handled properly
TEST(Pool6Test, TA) {
    // Note: since we defined TA pool types during PD work, we can test it
    // now. Although the configuration to take advantage of it is not
    // planned for now, we will support it some day.

    // Let's construct 2001:db8:1::/96 temporary addresses
    Pool6Ptr pool1;
    EXPECT_NO_THROW(pool1.reset(new Pool6(Lease::TYPE_TA,
                                          IOAddress("2001:db8:1::"), 96)));

    // Check that TA range can be only defined for single addresses
    EXPECT_THROW(Pool6(Lease::TYPE_TA, IOAddress("2001:db8:1::"), 96, 127),
                 BadValue);

    ASSERT_TRUE(pool1);
    EXPECT_EQ(Lease::TYPE_TA, pool1->getType());
    EXPECT_EQ(128, pool1->getLength()); // singular addresses, not prefixes
    EXPECT_EQ("2001:db8:1::", pool1->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1->getLastAddress().toText());

    // Check that it's possible to have min-max range for TA
    Pool6Ptr pool2;
    EXPECT_NO_THROW(pool2.reset(new Pool6(Lease::TYPE_TA,
                                          IOAddress("2001:db8:1::1"),
                                          IOAddress("2001:db8:1::f"))));
    ASSERT_TRUE(pool2);
    EXPECT_EQ(Lease::TYPE_TA, pool2->getType());
    EXPECT_EQ(128, pool2->getLength()); // singular addresses, not prefixes
    EXPECT_EQ("2001:db8:1::1", pool2->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::f", pool2->getLastAddress().toText());
}

// This test creates 100 pools and verifies that their IDs are unique.
TEST(Pool6Test, unique_id) {

    const int num_pools = 100;
    std::vector<Pool6Ptr> pools;

    for (int i = 0; i < num_pools; ++i) {
        pools.push_back(Pool6Ptr(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"),
                                           IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"))));
    }

    for (int i = 0; i < num_pools; ++i) {
        for (int j = i + 1; j < num_pools; ++j) {
            if (pools[i]->getId() == pools[j]->getId()) {
                FAIL() << "Pool-ids must be unique";
            }
        }
    }

}

// Simple check if toText returns reasonable values
TEST(Poo6Test,toText) {
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));
    EXPECT_EQ("type=IA_NA, 2001:db8::1-2001:db8::2, delegated_len=128",
              pool1.toText());

    Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);
    EXPECT_EQ("type=IA_PD, 2001:db8:1::-2001:db8:1::ffff:ffff, delegated_len=112",
              pool2.toText());
}

// Checks if the number of possible leases in range is reported correctly.
TEST(Pool6Test, leasesCount) {
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));
    EXPECT_EQ(2, pool1.getCapacity());

    Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);
    EXPECT_EQ(65536, pool2.getCapacity());
}


}; // end of anonymous namespace
