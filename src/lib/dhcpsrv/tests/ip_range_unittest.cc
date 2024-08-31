// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/ip_range.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

// This test verifies that an exception is thrown upon an attempt to
// create an address range from invalid values and that no exception
// is thrown when the values are correct.
TEST(AddressRangeTest, constructor) {
    // The start address must be lower or equal the end address.
    EXPECT_THROW(AddressRange(IOAddress("192.0.2.100"), IOAddress("192.0.2.99")),
                 BadValue);
    // The start and end address must be of the same family.
    EXPECT_THROW(AddressRange(IOAddress("192.0.2.100"), IOAddress("2001:db8:1::1")),
                 BadValue);
    // It is allowed to create address range with a single IP address.
    EXPECT_NO_THROW(AddressRange(IOAddress("192.0.2.100"), IOAddress("192.0.2.100")));
}

// This test verifies successful construction of the prefix range.
TEST(PrefixRangeTest, constructor) {
    boost::scoped_ptr<PrefixRange> range;
    ASSERT_NO_THROW(range.reset(new PrefixRange(IOAddress("2001:db8:1::"), 64, 96)));
    EXPECT_EQ("2001:db8:1::", range->start_.toText());
    EXPECT_EQ("2001:db8:1:0:ffff:ffff:ffff:ffff", range->end_.toText());
    EXPECT_EQ(64, range->prefix_length_);
    EXPECT_EQ(96, range->delegated_length_);

    ASSERT_NO_THROW(range.reset(new PrefixRange(IOAddress("2001:db8:1:2::"), 80, 120)));
    EXPECT_EQ("2001:db8:1:2::", range->start_.toText());
    EXPECT_EQ("2001:db8:1:2:0:ffff:ffff:ffff", range->end_.toText());
    EXPECT_EQ(80, range->prefix_length_);
    EXPECT_EQ(120, range->delegated_length_);

    ASSERT_NO_THROW(range.reset(new PrefixRange(IOAddress("2001:db8:1:2::"), 120, 127)));
    EXPECT_EQ("2001:db8:1:2::", range->start_.toText());
    EXPECT_EQ("2001:db8:1:2::ff", range->end_.toText());
    EXPECT_EQ(120, range->prefix_length_);
    EXPECT_EQ(127, range->delegated_length_);

    ASSERT_NO_THROW(range.reset(new PrefixRange(IOAddress("2001:db8:1::"), IOAddress("2001:db8:1:0:ffff:ffff:ffff:ffff"), 96)));
    EXPECT_EQ("2001:db8:1::", range->start_.toText());
    EXPECT_EQ("2001:db8:1:0:ffff:ffff:ffff:ffff", range->end_.toText());
    EXPECT_EQ(64, range->prefix_length_);
    EXPECT_EQ(96, range->delegated_length_);

    ASSERT_NO_THROW(range.reset(new PrefixRange(IOAddress("2001:db8:1:2::"), IOAddress("2001:db8:1:2:0:ffff:ffff:ffff"), 120)));
    EXPECT_EQ("2001:db8:1:2::", range->start_.toText());
    EXPECT_EQ("2001:db8:1:2:0:ffff:ffff:ffff", range->end_.toText());
    EXPECT_EQ(80, range->prefix_length_);
    EXPECT_EQ(120, range->delegated_length_);

    ASSERT_NO_THROW(range.reset(new PrefixRange(IOAddress("2001:db8:1:2::"), IOAddress("2001:db8:1:2::ff"), 127)));
    EXPECT_EQ("2001:db8:1:2::", range->start_.toText());
    EXPECT_EQ("2001:db8:1:2::ff", range->end_.toText());
    EXPECT_EQ(120, range->prefix_length_);
    EXPECT_EQ(127, range->delegated_length_);
}

// This test verifies that exception is thrown upon an attempt to
// create a prefix range from invalid values.
TEST(PrefixRangeTest, constructorWithInvalidValues) {
    boost::scoped_ptr<PrefixRange> range;
    // It must be IPv6 prefix.
    EXPECT_THROW(PrefixRange(IOAddress("192.0.2.0"), 8, 16), BadValue);
    // Delegated length must not be lower than prefix length.
    EXPECT_THROW(PrefixRange(IOAddress("2001:db8:1::"), 96, 64), BadValue);
    // Lengths must not exceed 128.
    EXPECT_THROW(PrefixRange(IOAddress("2001:db8:1::"), 200, 204), BadValue);
    // End must not be lower than start.
    EXPECT_THROW(PrefixRange(IOAddress("2001:db8:1:1::6:0"), IOAddress("2001:db8:1::5:0"), 112),
                 BadValue);
    // Length must not exceed 128.
    EXPECT_THROW(PrefixRange(IOAddress("2001:db8:1:1::"), IOAddress("2001:db8:1:f::"), 200),
                 BadValue);
    // The upper boundary of the prefix range must have non-significant
    // bits set to 1.
    EXPECT_THROW(PrefixRange(IOAddress("2001:db8:1:1::"), IOAddress("2001:db8:1:1::ff00"), 112),
                 BadValue);
}

} // end of anonymous namespace
