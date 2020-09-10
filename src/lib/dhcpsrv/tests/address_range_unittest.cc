// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/address_range.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

// This test verifies that an exception is thrown upon an attempt to
// create an address range from invalid values and that no exception
// is thrown when the values are correct.
TEST(AddressRangeTest, constructorWithInvalidValues) {
    // The start address must be lower or equal the end address.
    EXPECT_THROW(AddressRange(IOAddress("192.0.2.100"), IOAddress("192.0.2.99")),
                 BadValue);
    // The start and end address must be of the same family.
    EXPECT_THROW(AddressRange(IOAddress("192.0.2.100"), IOAddress("2001:db8:1::1")),
                 BadValue);
    // It is allowed to create address range with a single IP address.
    EXPECT_NO_THROW(AddressRange(IOAddress("192.0.2.100"), IOAddress("192.0.2.100")));
}

} // end of anonymous namespace
