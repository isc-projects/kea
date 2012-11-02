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
#include <dhcp/option.h>
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

TEST(Subnet4Test, addInvalidOption) {
    // Create the V4 subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 8, 1, 2, 3));

    // Some dummy option code.
    uint16_t code = 100;
    // Create option with invalid universe (V6 instead of V4).
    // Attempt to add this option should result in exception.
    OptionPtr option1(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
    EXPECT_THROW(subnet->addOption(option1), isc::BadValue);

    // Create NULL pointer option. Attempt to add NULL option
    // should result in exception.
    OptionPtr option2;
    ASSERT_FALSE(option2);
    EXPECT_THROW(subnet->addOption(option2), isc::BadValue);
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

// This test checks if the toText() method returns text representation
TEST(Subnet4Test, toText) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
}

// This test checks if the get() method returns proper parameters
TEST(Subnet4Test, get) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 28, 1, 2, 3));
    EXPECT_EQ("192.0.2.0", subnet->get().first.toText());
    EXPECT_EQ(28, subnet->get().second);
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

TEST(Subnet6Test, addOptions) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->addOption(option));
    }

    // Get options from the Subnet and check if all 10 are there.
    Subnet::OptionContainer options = subnet->getOptions();
    ASSERT_EQ(10, options.size());

    // Validate codes of added options.
    uint16_t expected_code = 100;
    for (Subnet::OptionContainer::const_iterator option_desc = options.begin();
         option_desc != options.end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    subnet->delOptions();

    options = subnet->getOptions();
    EXPECT_EQ(0, options.size());
}

TEST(Subnet6Test, addNonUniqueOptions) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Create a set of options with non-unique codes.
    for (int i = 0;  i < 2; ++i) {
        // In the inner loop we create options with unique codes (100-109).
        for (uint16_t code = 100; code < 110; ++code) {
            OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
            ASSERT_NO_THROW(subnet->addOption(option));
        }
    }

    // Sanity check that all options are there.
    Subnet::OptionContainer options = subnet->getOptions();
    ASSERT_EQ(20, options.size());

    // Use container index #1 to get the options by their codes.
    Subnet::OptionContainerTypeIndex& idx = options.get<1>();
    // Look for the codes 100-109.
    for (uint16_t code = 100; code < 110; ++ code) {
        // For each code we should get two instances of options.
        std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
                  Subnet::OptionContainerTypeIndex::const_iterator> range =
            idx.equal_range(code);
        // Distance between iterators indicates how many options
        // have been retured for the particular code.
        ASSERT_EQ(2, distance(range.first, range.second));
        // Check that returned options actually have the expected option code.
        for (Subnet::OptionContainerTypeIndex::const_iterator option_desc = range.first;
             option_desc != range.second; ++option_desc) {
            ASSERT_TRUE(option_desc->option);
            EXPECT_EQ(code, option_desc->option->getType());
        }
    }

    // Let's try to find some non-exiting option.
    const uint16_t non_existing_code = 150;
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(non_existing_code);
    // Empty set is expected.
    EXPECT_EQ(0, distance(range.first, range.second));

    subnet->delOptions();

    options = subnet->getOptions();
    EXPECT_EQ(0, options.size());
}

TEST(Subnet6Test, addInvalidOption) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Some dummy option code.
    uint16_t code = 100;
    // Create option with invalid universe (V4 instead of V6).
    // Attempt to add this option should result in exception.
    OptionPtr option1(new Option(Option::V4, code, OptionBuffer(10, 0xFF)));
    EXPECT_THROW(subnet->addOption(option1), isc::BadValue);

    // Create NULL pointer option. Attempt to add NULL option
    // should result in exception.
    OptionPtr option2;
    ASSERT_FALSE(option2);
    EXPECT_THROW(subnet->addOption(option2), isc::BadValue);
}

TEST(Subnet6Test, addPersistentOption) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Add 10 options to the subnet with option codes 100 - 109.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        // We create 10 options and want some of them to be flagged
        // persistent and some non-persistent. Persistent options are
        // those that server sends to clients regardless if they ask
        // for them or not. We pick 3 out of 10 options and mark them
        // non-persistent and 7 other options persistent.
        // Code values: 102, 105 and 108 are divisable by 3
        // and options with these codes will be flagged non-persistent.
        // Options with other codes will be flagged persistent.
        bool persistent = (code % 3) ? true : false;
        ASSERT_NO_THROW(subnet->addOption(option, persistent));
    }

    // Get added options from the subnet.
    Subnet::OptionContainer options = subnet->getOptions();

    // options.get<2> returns reference to container index #2. This
    // index is used to access options by the 'persistent' flag.
    Subnet::OptionContainerPersistIndex& idx = options.get<2>();

    // Get all persistent options.
    std::pair<Subnet::OptionContainerPersistIndex::const_iterator,
              Subnet::OptionContainerPersistIndex::const_iterator> range_persistent =
        idx.equal_range(true);
    // 3 out of 10 options have been flagged persistent.
    ASSERT_EQ(7, distance(range_persistent.first, range_persistent.second));

    // Get all non-persistent options.
    std::pair<Subnet::OptionContainerPersistIndex::const_iterator,
              Subnet::OptionContainerPersistIndex::const_iterator> range_non_persistent =
        idx.equal_range(false);
    // 7 out of 10 options have been flagged persistent.
    ASSERT_EQ(3, distance(range_non_persistent.first, range_non_persistent.second));

    subnet->delOptions();

    options = subnet->getOptions();
    EXPECT_EQ(0, options.size());
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

// This test checks if the toText() method returns text representation
TEST(Subnet6Test, toText) {
    Subnet6 subnet(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);
    EXPECT_EQ("2001:db8::/32", subnet.toText());
}

// This test checks if the get() method returns proper parameters
TEST(Subnet6Test, get) {
    Subnet6 subnet(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);
    EXPECT_EQ("2001:db8::", subnet.get().first.toText());
    EXPECT_EQ(32, subnet.get().second);
}

};
