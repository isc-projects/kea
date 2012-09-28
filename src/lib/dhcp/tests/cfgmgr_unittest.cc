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
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <dhcp/cfgmgr.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

// constructor validation
TEST(TripletTest, constructor) {

    const uint32_t min = 10;
    const uint32_t value = 20;
    const uint32_t max = 30;

    Triplet<uint32_t> x(min, value, max);

    EXPECT_EQ(min, x.getMin());
    EXPECT_EQ(value, x.get());
    EXPECT_EQ(max, x.getMax());

    // requested values below min should return allowed min value
    EXPECT_EQ(min, x.get(min - 5));

    EXPECT_EQ(min, x.get(min));

    // requesting a value from within the range (min < x < max) should
    // return the requested value
    EXPECT_EQ(17, x.get(17));

    EXPECT_EQ(max, x.get(max));

    EXPECT_EQ(max, x.get(max + 5));

    // this will be boring. It is expected to return 42 no matter what
    Triplet<uint32_t> y(42);

    EXPECT_EQ(42, y.getMin()); // min, default and max are equal to 42
    EXPECT_EQ(42, y.get());    // it returns ...
    EXPECT_EQ(42, y.getMax()); // the exact value...

    // requested values below or above are ignore
    EXPECT_EQ(42, y.get(5));   // all...
    EXPECT_EQ(42, y.get(42));  // the...
    EXPECT_EQ(42, y.get(80));  // time!
}

// Triplets must be easy to use.
// Simple to/from int conversions must be done on the fly.
TEST(TripletTest, operator) {

    uint32_t x = 47;

    Triplet<uint32_t> foo(1,2,3);
    Triplet<uint32_t> bar(4,5,6);

    foo = bar;

    EXPECT_EQ(4, foo.getMin());
    EXPECT_EQ(5, foo.get());
    EXPECT_EQ(6, foo.getMax());

    // assignment operator: uint32_t => triplet
    Triplet<uint32_t> y(0);
    y = x;

    EXPECT_EQ(x, y.get());

    // let's try the other way around: triplet => uint32_t
    uint32_t z = 0;
    z = y;

    EXPECT_EQ(x, z);
}

// check if specified values are sane
TEST(TripletTest, sanity_check) {

    // min is larger than default
    EXPECT_THROW(Triplet<uint32_t>(6,5,5), BadValue);

    // max is smaller than default
    EXPECT_THROW(Triplet<uint32_t>(5,5,4), BadValue);

}

TEST(Pool6Test, constructor_first_last) {

    // let's construct 2001:db8:1:: - 2001:db8:1::ffff:ffff:ffff:ffff pool
    Pool6 pool1(Pool6::TYPE_IA, IOAddress("2001:db8:1::"),
                IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"));

    EXPECT_EQ(Pool6::TYPE_IA, pool1.getType());
    EXPECT_EQ(IOAddress("2001:db8:1::"), pool1.getFirstAddress());
    EXPECT_EQ(IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"),
              pool1.getLastAddress());

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::1"),
                       IOAddress("192.168.0.5")), BadValue);
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("192.168.0.2"),
                       IOAddress("2001:db8::1")), BadValue);

    // Should throw. Range should be 2001:db8::1 - 2001:db8::2, not
    // the other way around.
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::2"),
                       IOAddress("2001:db8::1")), BadValue);
}

TEST(Pool6Test, constructor_prefix_len) {

    // let's construct 2001:db8:1::/96 pool
    Pool6 pool1(Pool6::TYPE_IA, IOAddress("2001:db8:1::"), 96);

    EXPECT_EQ(Pool6::TYPE_IA, pool1.getType());
    EXPECT_EQ("2001:db8:1::", pool1.getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1.getLastAddress().toText());

    // No such thing as /130 prefix
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::"), 130),
                 BadValue);

    // /0 prefix does not make sense
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::"), 0),
                 BadValue);

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("192.168.0.2"), 96),
                 BadValue);
}

TEST(Pool6Test, in_range) {
   Pool6 pool1(Pool6::TYPE_IA, IOAddress("2001:db8:1::1"),
               IOAddress("2001:db8:1::f"));

   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::1")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::7")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::f")));
   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::10")));
   EXPECT_FALSE(pool1.inRange(IOAddress("::")));
}

// This test creates 100 pools and verifies that their IDs are unique.
TEST(Pool6Test, unique_id) {

    const int num_pools = 100;
    vector<Pool6Ptr> pools;

    for (int i = 0; i < num_pools; ++i) {
        pools.push_back(Pool6Ptr(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1::"),
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

// This test verifies if the configuration manager is able to hold and return
// valid leases
TEST(CfgMgrTest, subnet6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    ASSERT_TRUE(&cfg_mgr != 0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // there shouldn't be any subnet configured at this stage
    EXPECT_EQ( Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("2000::1")));

    cfg_mgr.addSubnet6(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2001:db8::1")));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(IOAddress("4000::123")));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("3000::dead:beef")));
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("5000::1")));

    cfg_mgr.deleteSubnets6();
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("200::123")));
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("3000::123")));
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("4000::123")));
}

} // end of anonymous namespace
