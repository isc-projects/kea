// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

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

    PoolPtr pool1(new Pool4(IOAddress("192.1.2.0"), 25));
    PoolPtr pool2(new Pool4(IOAddress("192.1.2.128"), 26));
    PoolPtr pool3(new Pool4(IOAddress("192.1.2.192"), 30));

    EXPECT_NO_THROW(subnet->addPool(pool1));

    // If there's only one pool, get that pool
    PoolPtr mypool = subnet->getAnyPool(Lease::TYPE_V4);
    EXPECT_EQ(mypool, pool1);


    EXPECT_NO_THROW(subnet->addPool(pool2));
    EXPECT_NO_THROW(subnet->addPool(pool3));

    // If there are more than one pool and we didn't provide hint, we
    // should get the first pool
    EXPECT_NO_THROW(mypool = subnet->getAnyPool(Lease::TYPE_V4));

    EXPECT_EQ(mypool, pool1);

    // If we provide a hint, we should get a pool that this hint belongs to
    EXPECT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4,
                                             IOAddress("192.1.2.195")));

    EXPECT_EQ(mypool, pool3);

}

TEST(Subnet4Test, Subnet4_Pool4_checks) {

    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 8, 1, 2, 3));

    // this one is in subnet
    Pool4Ptr pool1(new Pool4(IOAddress("192.255.0.0"), 16));
    subnet->addPool(pool1);

    // this one is larger than the subnet!
    Pool4Ptr pool2(new Pool4(IOAddress("193.0.0.0"), 24));

    EXPECT_THROW(subnet->addPool(pool2), BadValue);

    // this one is totally out of blue
    Pool4Ptr pool3(new Pool4(IOAddress("1.2.3.4"), 16));
    EXPECT_THROW(subnet->addPool(pool3), BadValue);
}

TEST(Subnet4Test, addInvalidOption) {
    // Create the V4 subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 8, 1, 2, 3));

    // Some dummy option code.
    uint16_t code = 100;
    // Create option with invalid universe (V6 instead of V4).
    // Attempt to add this option should result in exception.
    OptionPtr option1(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
    EXPECT_THROW(subnet->addOption(option1, false, "dhcp4"),
                 isc::BadValue);

    // Create NULL pointer option. Attempt to add NULL option
    // should result in exception.
    OptionPtr option2;
    ASSERT_FALSE(option2);
    EXPECT_THROW(subnet->addOption(option2, false, "dhcp4"),
                 isc::BadValue);
}

// This test verifies that inRange() and inPool() methods work properly.
TEST(Subnet4Test, inRangeinPool) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.0.0"), 8, 1, 2, 3));

    // this one is in subnet
    Pool4Ptr pool1(new Pool4(IOAddress("192.2.0.0"), 16));
    subnet->addPool(pool1);

    // 192.1.1.1 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("192.1.1.1")));

    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.1.1.1")));

    // the last address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.1.255.255")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.1.255.255")));

    // the first address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.0.0")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.0.0")));

    // let's try something in the middle as well
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.3.4")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4")));

    // the last address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.255.255")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.255.255")));

    // the first address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.3.0.0")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.3.0.0")));
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


// Checks if last allocated address/prefix is stored/retrieved properly
TEST(Subnet4Test, lastAllocated) {
    IOAddress addr("192.0.2.17");

    IOAddress last("192.0.2.255");

    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));

    // Check initial conditions (all should be set to the last address in range)
    EXPECT_EQ(last.toText(), subnet->getLastAllocated(Lease::TYPE_V4).toText());

    // Now set last allocated for IA
    EXPECT_NO_THROW(subnet->setLastAllocated(Lease::TYPE_V4, addr));
    EXPECT_EQ(addr.toText(), subnet->getLastAllocated(Lease::TYPE_V4).toText());

    // No, you can't set the last allocated IPv6 address in IPv4 subnet
    EXPECT_THROW(subnet->setLastAllocated(Lease::TYPE_TA, addr), BadValue);
    EXPECT_THROW(subnet->setLastAllocated(Lease::TYPE_TA, addr), BadValue);
    EXPECT_THROW(subnet->setLastAllocated(Lease::TYPE_PD, addr), BadValue);
}

// Checks if the V4 is the only allowed type for Pool4 and if getPool()
// is working properly.
TEST(Subnet4Test, PoolType) {

    Subnet4Ptr subnet(new Subnet4(IOAddress("192.2.0.0"), 16, 1, 2, 3));

    PoolPtr pool1(new Pool4(IOAddress("192.2.1.0"), 24));
    PoolPtr pool2(new Pool4(IOAddress("192.2.2.0"), 24));
    PoolPtr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:3::"), 64));
    PoolPtr pool4(new Pool6(Lease::TYPE_TA, IOAddress("2001:db8:1:4::"), 64));
    PoolPtr pool5(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:1::"), 64));

    // There should be no pools of any type by default
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_V4));

    // It should not be possible to ask for V6 pools in Subnet4
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_NA), BadValue);
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_TA), BadValue);
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_PD), BadValue);

    // Let's add a single V4 pool and check that it can be retrieved
    EXPECT_NO_THROW(subnet->addPool(pool1));

    // If there's only one IA pool, get that pool (without and with hint)
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_V4));
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.1.167")));

    // Let's add additional V4 pool
    EXPECT_NO_THROW(subnet->addPool(pool2));

    // Try without hints
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_V4));

    // Try with valid hints
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_V4, IOAddress("192.2.1.5")));
    EXPECT_EQ(pool2, subnet->getPool(Lease::TYPE_V4, IOAddress("192.2.2.254")));

    // Try with bogus hints (hints should be ingored)
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_V4, IOAddress("10.1.1.1")));

    // Trying to add Pool6 to Subnet4 is a big no,no!
    EXPECT_THROW(subnet->addPool(pool3), BadValue);
    EXPECT_THROW(subnet->addPool(pool4), BadValue);
    EXPECT_THROW(subnet->addPool(pool5), BadValue);
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

    PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    PoolPtr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::"), 64));
    PoolPtr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:3::"), 64));

    subnet->addPool(pool1);

    // If there's only one pool, get that pool
    PoolPtr mypool = subnet->getAnyPool(Lease::TYPE_NA);
    EXPECT_EQ(mypool, pool1);

    subnet->addPool(pool2);
    subnet->addPool(pool3);

    // If there are more than one pool and we didn't provide hint, we
    // should get the first pool
    mypool = subnet->getAnyPool(Lease::TYPE_NA);

    EXPECT_EQ(mypool, pool1);

    // If we provide a hint, we should get a pool that this hint belongs to
    mypool = subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:3::dead:beef"));

    EXPECT_EQ(mypool, pool3);
}

// Check if Subnet6 supports different types of pools properly.
TEST(Subnet6Test, PoolTypes) {

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    PoolPtr pool2(new Pool6(Lease::TYPE_TA, IOAddress("2001:db8:1:2::"), 64));
    PoolPtr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:3::"), 64));
    PoolPtr pool4(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:4::"), 64));

    PoolPtr pool5(new Pool4(IOAddress("192.0.2.0"), 24));

    // There should be no pools of any type by default
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_NA));
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_TA));
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_PD));

    // Trying to get IPv4 pool from Subnet6 is not allowed
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_V4), BadValue);

    // Let's add a single IA pool and check that it can be retrieved
    EXPECT_NO_THROW(subnet->addPool(pool1));

    // If there's only one IA pool, get that pool
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_NA));
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:1::1")));

    // Check if pools of different type are not returned
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_TA));
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_PD));

    // We ask with good hints, but wrong types, should return nothing
    EXPECT_EQ(PoolPtr(), subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:2::1")));
    EXPECT_EQ(PoolPtr(), subnet->getPool(Lease::TYPE_TA, IOAddress("2001:db8:1:3::1")));

    // Let's add TA and PD pools
    EXPECT_NO_THROW(subnet->addPool(pool2));
    EXPECT_NO_THROW(subnet->addPool(pool3));

    // Try without hints
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_NA));
    EXPECT_EQ(pool2, subnet->getAnyPool(Lease::TYPE_TA));
    EXPECT_EQ(pool3, subnet->getAnyPool(Lease::TYPE_PD));

    // Try with valid hints
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:1::1")));
    EXPECT_EQ(pool2, subnet->getPool(Lease::TYPE_TA, IOAddress("2001:db8:1:2::1")));
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:3::1")));

    // Try with bogus hints (hints should be ingored)
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:7::1")));
    EXPECT_EQ(pool2, subnet->getPool(Lease::TYPE_TA, IOAddress("2001:db8:1:7::1")));
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:7::1")));

    // Let's add a second PD pool
    EXPECT_NO_THROW(subnet->addPool(pool4));

    // Without hints, it should return the first pool
    EXPECT_EQ(pool3, subnet->getAnyPool(Lease::TYPE_PD));

    // With valid hint, it should return that hint
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:3::1")));
    EXPECT_EQ(pool4, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:4::1")));

    // With invalid hint, it should return the first pool
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8::123")));

    // Adding Pool4 to Subnet6 is a big no, no!
    EXPECT_THROW(subnet->addPool(pool5), BadValue);
}

TEST(Subnet6Test, Subnet6_Pool6_checks) {

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    subnet->addPool(pool1);

    // this one is larger than the subnet!
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 48));

    EXPECT_THROW(subnet->addPool(pool2), BadValue);


    // this one is totally out of blue
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("3000::"), 16));
    EXPECT_THROW(subnet->addPool(pool3), BadValue);


    Pool6Ptr pool4(new Pool6(Lease::TYPE_NA, IOAddress("4001:db8:1::"), 80));
    EXPECT_THROW(subnet->addPool(pool4), BadValue);
}

TEST(Subnet6Test, addOptions) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->addOption(option, false, "dhcp6"));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->addOption(option, false, "isc"));
    }

    // Get options from the Subnet and check if all 10 are there.
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (Subnet::OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    options = subnet->getOptionDescriptors("isc");
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (Subnet::OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = subnet->getOptionDescriptors("abcd");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());

    // Delete options from all spaces.
    subnet->delOptions();

    // Make sure that all options have been removed.
    options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());

    options = subnet->getOptionDescriptors("isc");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

TEST(Subnet6Test, addNonUniqueOptions) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Create a set of options with non-unique codes.
    for (int i = 0;  i < 2; ++i) {
        // In the inner loop we create options with unique codes (100-109).
        for (uint16_t code = 100; code < 110; ++code) {
            OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
            ASSERT_NO_THROW(subnet->addOption(option, false, "dhcp6"));
        }
    }

    // Sanity check that all options are there.
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_EQ(20, options->size());

    // Use container index #1 to get the options by their codes.
    Subnet::OptionContainerTypeIndex& idx = options->get<1>();
    // Look for the codes 100-109.
    for (uint16_t code = 100; code < 110; ++ code) {
        // For each code we should get two instances of options->
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

    options = subnet->getOptionDescriptors("dhcp6");
    EXPECT_EQ(0, options->size());
}

TEST(Subnet6Test, addInvalidOption) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Some dummy option code.
    uint16_t code = 100;
    // Create option with invalid universe (V4 instead of V6).
    // Attempt to add this option should result in exception.
    OptionPtr option1(new Option(Option::V4, code, OptionBuffer(10, 0xFF)));
    EXPECT_THROW(subnet->addOption(option1, false, "dhcp6"), isc::BadValue);

    // Create NULL pointer option. Attempt to add NULL option
    // should result in exception.
    OptionPtr option2;
    ASSERT_FALSE(option2);
    EXPECT_THROW(subnet->addOption(option2, false, "dhcp6"), isc::BadValue);
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
        // Code values: 102, 105 and 108 are divisible by 3
        // and options with these codes will be flagged non-persistent.
        // Options with other codes will be flagged persistent.
        bool persistent = (code % 3) ? true : false;
        ASSERT_NO_THROW(subnet->addOption(option, persistent, "dhcp6"));
    }

    // Get added options from the subnet.
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");

    // options->get<2> returns reference to container index #2. This
    // index is used to access options by the 'persistent' flag.
    Subnet::OptionContainerPersistIndex& idx = options->get<2>();

    // Get all persistent options->
    std::pair<Subnet::OptionContainerPersistIndex::const_iterator,
              Subnet::OptionContainerPersistIndex::const_iterator> range_persistent =
        idx.equal_range(true);
    // 3 out of 10 options have been flagged persistent.
    ASSERT_EQ(7, distance(range_persistent.first, range_persistent.second));

    // Get all non-persistent options->
    std::pair<Subnet::OptionContainerPersistIndex::const_iterator,
              Subnet::OptionContainerPersistIndex::const_iterator> range_non_persistent =
        idx.equal_range(false);
    // 7 out of 10 options have been flagged persistent.
    ASSERT_EQ(3, distance(range_non_persistent.first, range_non_persistent.second));

    subnet->delOptions();

    options = subnet->getOptionDescriptors("dhcp6");
    EXPECT_EQ(0, options->size());
}

TEST(Subnet6Test, getOptionDescriptor) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 56, 1, 2, 3, 4));

    // Add 10 options to a "dhcp6" option space in the subnet.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->addOption(option, false, "dhcp6"));
    }

    // Check that we can get each added option descriptor using
    // individually.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream stream;
        // First, try the invalid option space name.
        Subnet::OptionDescriptor desc = subnet->getOptionDescriptor("isc", code);
        // Returned descriptor should contain NULL option ptr.
        EXPECT_FALSE(desc.option);
        // Now, try the valid option space.
        desc = subnet->getOptionDescriptor("dhcp6", code);
        // Test that the option code matches the expected code.
        ASSERT_TRUE(desc.option);
        EXPECT_EQ(code, desc.option->getType());
    }
}


TEST(Subnet6Test, addVendorOptions) {

    uint32_t vendor_id1 = 12345678;
    uint32_t vendor_id2 = 87654321;
    uint32_t vendor_id_bogus = 1111111;

    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->addVendorOption(option, false, vendor_id1));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->addVendorOption(option, false, vendor_id2));
    }

    // Get options from the Subnet and check if all 10 are there.
    Subnet::OptionContainerPtr options = subnet->getVendorOptionDescriptors(vendor_id1);
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (Subnet::OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    options = subnet->getVendorOptionDescriptors(vendor_id2);
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (Subnet::OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option);
        EXPECT_EQ(expected_code, option_desc->option->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = subnet->getVendorOptionDescriptors(vendor_id_bogus);
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());

    // Delete options from all spaces.
    subnet->delVendorOptions();

    // Make sure that all options have been removed.
    options = subnet->getVendorOptionDescriptors(vendor_id1);
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());

    options = subnet->getVendorOptionDescriptors(vendor_id2);
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}



// This test verifies that inRange() and inPool() methods work properly.
TEST(Subnet6Test, inRangeinPool) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 32, 1, 2, 3, 4));

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                             IOAddress("2001:db8::20")));
    subnet->addPool(pool1);

    // 192.1.1.1 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::1")));
    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::1")));

    // the last address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::f")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::f")));

    // the first address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::10")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::10")));

    // let's try something in the middle as well
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::18")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18")));

    // the last address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::20")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::20")));

    // the first address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::21")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::21")));
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

// This trivial test checks if interface name is stored properly
// in Subnet6 objects.
TEST(Subnet6Test, iface) {
    Subnet6 subnet(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    EXPECT_TRUE(subnet.getIface().empty());

    subnet.setIface("en1");
    EXPECT_EQ("en1", subnet.getIface());
}

// This trivial test checks if the interface-id option can be set and
// later retrieved for a subnet6 object.
TEST(Subnet6Test, interfaceId) {
    // Create as subnet to add options to it.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    EXPECT_FALSE(subnet->getInterfaceId());

    OptionPtr option(new Option(Option::V6, D6O_INTERFACE_ID, OptionBuffer(10, 0xFF)));
    subnet->setInterfaceId(option);

    EXPECT_EQ(option, subnet->getInterfaceId());

}

// Checks if last allocated address/prefix is stored/retrieved properly
TEST(Subnet6Test, lastAllocated) {
    IOAddress ia("2001:db8:1::1");
    IOAddress ta("2001:db8:1::abcd");
    IOAddress pd("2001:db8:1::1234:5678");

    IOAddress last("2001:db8:1::ffff:ffff:ffff:ffff");

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4));

    // Check initial conditions (all should be set to the last address in range)
    EXPECT_EQ(last.toText(), subnet->getLastAllocated(Lease::TYPE_NA).toText());
    EXPECT_EQ(last.toText(), subnet->getLastAllocated(Lease::TYPE_TA).toText());
    EXPECT_EQ(last.toText(), subnet->getLastAllocated(Lease::TYPE_PD).toText());

    // Now set last allocated for IA
    EXPECT_NO_THROW(subnet->setLastAllocated(Lease::TYPE_NA, ia));
    EXPECT_EQ(ia.toText(), subnet->getLastAllocated(Lease::TYPE_NA).toText());

    // TA and PD should be unchanged
    EXPECT_EQ(last.toText(), subnet->getLastAllocated(Lease::TYPE_TA).toText());
    EXPECT_EQ(last.toText(), subnet->getLastAllocated(Lease::TYPE_PD).toText());

    // Now set TA and PD
    EXPECT_NO_THROW(subnet->setLastAllocated(Lease::TYPE_TA, ta));
    EXPECT_NO_THROW(subnet->setLastAllocated(Lease::TYPE_PD, pd));

    EXPECT_EQ(ia.toText(), subnet->getLastAllocated(Lease::TYPE_NA).toText());
    EXPECT_EQ(ta.toText(), subnet->getLastAllocated(Lease::TYPE_TA).toText());
    EXPECT_EQ(pd.toText(), subnet->getLastAllocated(Lease::TYPE_PD).toText());

    // No, you can't set the last allocated IPv4 address in IPv6 subnet
    EXPECT_THROW(subnet->setLastAllocated(Lease::TYPE_V4, ia), BadValue);
}

};
