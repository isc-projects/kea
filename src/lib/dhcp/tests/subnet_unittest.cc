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

}


};
