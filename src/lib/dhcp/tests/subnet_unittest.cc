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
#include <dhcp/subnet.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <asiolink/io_address.h>

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

TEST(Subnet4Test, constructor) {
    EXPECT_NO_THROW(Subnet4 subnet1(IOAddress("192.0.2.2"), 16,
                                    1, 2, 3));

    EXPECT_THROW(Subnet4 subnet2(IOAddress("192.0.2.0"), 33, 1, 2, 3),
                BadValue); // invalid prefix length
    EXPECT_THROW(Subnet4 subnet3(IOAddress("2001:db8::1"), 24, 1, 2, 3),
                BadValue); // IPv6 addresses are not allowed in Subnet4
}

TEST(Subnet4Test, in_range) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    EXPECT_EQ(1000, subnet.getT1());
    EXPECT_EQ(2000, subnet.getT2());
    EXPECT_EQ(3000, subnet.getValid());

    EXPECT_FALSE(subnet.inRange(IOAddress("192.0.0.0")));
    EXPECT_TRUE(subnet.inRange(IOAddress("192.0.2.0")));
    EXPECT_TRUE(subnet.inRange(IOAddress("192.0.2.1")));
    EXPECT_TRUE(subnet.inRange(IOAddress("192.0.2.255")));
    EXPECT_FALSE(subnet.inRange(IOAddress("192.0.3.0")));
    EXPECT_FALSE(subnet.inRange(IOAddress("0.0.0.0")));
    EXPECT_FALSE(subnet.inRange(IOAddress("255.255.255.255")));
}

TEST(Subnet4Test, Pool4InSubnet4) {

    Subnet4Ptr subnet(new Subnet4(IOAddress("192.1.2.0"), 24, 1, 2, 3));

    Pool4Ptr pool1(new Pool4(IOAddress("192.1.2.0"), 25));
    Pool4Ptr pool2(new Pool4(IOAddress("192.1.2.128"), 26));
    Pool4Ptr pool3(new Pool4(IOAddress("192.1.2.192"), 30));

    subnet->addPool4(pool1);

    // If there's only one pool, get that pool
    Pool4Ptr mypool = subnet->getPool4();
    EXPECT_EQ(mypool, pool1);


    subnet->addPool4(pool2);
    subnet->addPool4(pool3);

    // If there are more than one pool and we didn't provide hint, we
    // should get the first pool
    mypool = subnet->getPool4();

    EXPECT_EQ(mypool, pool1);

    // If we provide a hint, we should get a pool that this hint belongs to
    mypool = subnet->getPool4(IOAddress("192.1.2.195"));

    EXPECT_EQ(mypool, pool3);

}

TEST(Subnet4Test, Subnet4_Pool4_checks) {

    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 8, 1, 2, 3));

    // this one is in subnet
    Pool4Ptr pool1(new Pool4(IOAddress("192.255.0.0"), 16));
    subnet->addPool4(pool1);

    // this one is larger than the subnet!
    Pool4Ptr pool2(new Pool4(IOAddress("193.0.0.0"), 24));

    EXPECT_THROW(subnet->addPool4(pool2), BadValue);

    // this one is totally out of blue
    Pool4Ptr pool3(new Pool4(IOAddress("1.2.3.4"), 16));
    EXPECT_THROW(subnet->addPool4(pool3), BadValue);
}

// This test verifies that inRange() and inPool() methods work properly.
TEST(Subnet4Test, inRangeinPool) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.0.0"), 8, 1, 2, 3));

    // this one is in subnet
    Pool4Ptr pool1(new Pool4(IOAddress("192.2.0.0"), 16));
    subnet->addPool4(pool1);

    // 192.1.1.1 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("192.1.1.1")));

    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(IOAddress("192.1.1.1")));

    // the last address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.1.255.255")));
    EXPECT_FALSE(subnet->inPool(IOAddress("192.1.255.255")));

    // the first address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.0.0")));
    EXPECT_TRUE (subnet->inPool(IOAddress("192.2.0.0")));

    // let's try something in the middle as well
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.3.4")));
    EXPECT_TRUE (subnet->inPool(IOAddress("192.2.3.4")));

    // the last address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.255.255")));
    EXPECT_TRUE (subnet->inPool(IOAddress("192.2.255.255")));

    // the first address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.3.0.0")));
    EXPECT_FALSE(subnet->inPool(IOAddress("192.3.0.0")));
}

// Tests for Subnet6

TEST(Subnet6Test, constructor) {

    EXPECT_NO_THROW(Subnet6 subnet1(IOAddress("2001:db8:1::"), 64,
                                    1, 2, 3, 4));

    EXPECT_THROW(Subnet6 subnet2(IOAddress("2001:db8:1::"), 129, 1, 2, 3, 4),
                BadValue); // invalid prefix length
    EXPECT_THROW(Subnet6 subnet3(IOAddress("192.168.0.0"), 32, 1, 2, 3, 4),
                BadValue); // IPv4 addresses are not allowed in Subnet6
}

TEST(Subnet6Test, in_range) {
    Subnet6 subnet(IOAddress("2001:db8:1::"), 64, 1000, 2000, 3000, 4000);

    EXPECT_EQ(1000, subnet.getT1());
    EXPECT_EQ(2000, subnet.getT2());
    EXPECT_EQ(3000, subnet.getPreferred());
    EXPECT_EQ(4000, subnet.getValid());

    EXPECT_FALSE(subnet.inRange(IOAddress("2001:db8:0:ffff:ffff:ffff:ffff:ffff")));
    EXPECT_TRUE(subnet.inRange(IOAddress("2001:db8:1::0")));
    EXPECT_TRUE(subnet.inRange(IOAddress("2001:db8:1::1")));
    EXPECT_TRUE(subnet.inRange(IOAddress("2001:db8:1::ffff:ffff:ffff:ffff")));
    EXPECT_FALSE(subnet.inRange(IOAddress("2001:db8:1:1::")));
    EXPECT_FALSE(subnet.inRange(IOAddress("::")));
}

TEST(Subnet6Test, Pool6InSubnet6) {

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    Pool6Ptr pool1(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:1::"), 64));
    Pool6Ptr pool2(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:2::"), 64));
    Pool6Ptr pool3(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:3::"), 64));

    subnet->addPool6(pool1);

    // If there's only one pool, get that pool
    Pool6Ptr mypool = subnet->getPool6();
    EXPECT_EQ(mypool, pool1);


    subnet->addPool6(pool2);
    subnet->addPool6(pool3);

    // If there are more than one pool and we didn't provide hint, we
    // should get the first pool
    mypool = subnet->getPool6();

    EXPECT_EQ(mypool, pool1);

    // If we provide a hint, we should get a pool that this hint belongs to
    mypool = subnet->getPool6(IOAddress("2001:db8:1:3::dead:beef"));

    EXPECT_EQ(mypool, pool3);
}

TEST(Subnet6Test, Subnet6_Pool6_checks) {

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:1::"), 64));
    subnet->addPool6(pool1);

    // this one is larger than the subnet!
    Pool6Ptr pool2(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::"), 48));

    EXPECT_THROW(subnet->addPool6(pool2), BadValue);


    // this one is totally out of blue
    Pool6Ptr pool3(new Pool6(Pool6::TYPE_IA, IOAddress("3000::"), 16));
    EXPECT_THROW(subnet->addPool6(pool3), BadValue);


    Pool6Ptr pool4(new Pool6(Pool6::TYPE_IA, IOAddress("4001:db8:1::"), 80));
    EXPECT_THROW(subnet->addPool6(pool4), BadValue);
}

// This test verifies that inRange() and inPool() methods work properly.
TEST(Subnet6Test, inRangeinPool) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 32, 1, 2, 3, 4));

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::10"),
                             IOAddress("2001:db8::20")));
    subnet->addPool6(pool1);

    // 192.1.1.1 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::1")));
    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(IOAddress("2001:db8::1")));

    // the last address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::f")));
    EXPECT_FALSE(subnet->inPool(IOAddress("2001:db8::f")));

    // the first address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::10")));
    EXPECT_TRUE (subnet->inPool(IOAddress("2001:db8::10")));

    // let's try something in the middle as well
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::18")));
    EXPECT_TRUE (subnet->inPool(IOAddress("2001:db8::18")));

    // the last address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::20")));
    EXPECT_TRUE (subnet->inPool(IOAddress("2001:db8::20")));

    // the first address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::21")));
    EXPECT_FALSE(subnet->inPool(IOAddress("2001:db8::21")));
}


};
