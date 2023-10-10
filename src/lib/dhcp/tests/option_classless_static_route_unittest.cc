// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option_classless_static_route.h>

#include <gtest/gtest.h>

using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

// This test verifies constructor of the empty OptionClasslessStaticRoute class.
TEST(OptionClasslessStaticRouteTest, emptyCtor) {
    // Create option instance. Check that constructor doesn't throw.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute()));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_CLASSLESS_STATIC_ROUTE, option->getType());
}

TEST(OptionClasslessStaticRouteTest, emptyCtorAddOneRoute) {
    // Create option instance. Check that constructor doesn't throw.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute()));
    ASSERT_TRUE(option);

    // Add one static route.
    StaticRouteTuple route = std::make_tuple(IOAddress("0.0.0.0"), 0, IOAddress("10.198.122.1"));
    option->addRoute(route);

    // Expected len: 2 (option code + option len headers) + 5 (1 dest descriptor + 4 router addr).
    EXPECT_EQ(7, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=5, Route 1 (subnet 0.0.0.0/0,"
              " router IP 10.198.122.1)",
              option->toText());

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_CLASSLESS_STATIC_ROUTE, option->getType());
}

TEST(OptionClasslessStaticRouteTest, bufferCtorWithOneRoute) {
    // Prepare data to decode - one route with 0 mask width
    const uint8_t buf_data[] = {
        10, 0, 0, 0,    // subnet nr
        255, 0, 0, 0,   // mask
        10, 198, 122, 1 // router IP
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor doesn't throw.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Expected len: 2 (option code + option len headers) + 6 (2 dest descriptor + 4 router addr).
    EXPECT_EQ(8, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=6, Route 1 (subnet 10.0.0.0/8,"
              " router IP 10.198.122.1)",
              option->toText());

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_CLASSLESS_STATIC_ROUTE, option->getType());
}

}