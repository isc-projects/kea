// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option_classless_static_route.h>
#include <util/strutil.h>

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

// This test verifies adding one route to OptionClasslessStaticRoute class.
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
}

// This test verifies adding more routes to OptionClasslessStaticRoute class.
TEST(OptionClasslessStaticRouteTest, emptyCtorAddMoreRoutes) {
    // Create option instance. Check that constructor doesn't throw.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute()));
    ASSERT_TRUE(option);

    // Add 3 static routes.
    StaticRouteTuple route1 = std::make_tuple(IOAddress("0.0.0.0"), 0, IOAddress("10.198.122.1"));
    option->addRoute(route1);
    StaticRouteTuple route2 = std::make_tuple(IOAddress("1.2.3.4"), 32, IOAddress("10.20.30.40"));
    option->addRoute(route2);
    StaticRouteTuple route3 = std::make_tuple(IOAddress("5.6.0.0"), 16, IOAddress("50.60.70.80"));
    option->addRoute(route3);

    // Expected len: 2 (option code + option len headers) + 5 (1 dest descriptor + 4 router addr)
    // + 9 (5 d.d. + 4 r.a.) + 7 (3 d.d. + 4 r.a.).
    EXPECT_EQ(23, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=21, "
              "Route 1 (subnet 0.0.0.0/0, router IP 10.198.122.1), "
              "Route 2 (subnet 1.2.3.4/32, router IP 10.20.30.40), "
              "Route 3 (subnet 5.6.0.0/16, router IP 50.60.70.80)",
              option->toText());
}

// This test verifies constructor of the OptionClasslessStaticRoute class from config data.
// Only one static route is defined.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorWithOneRoute) {
    // Prepare data to decode - one route with mask width = 8.
    const std::string config = "'10.0.0.0/8 - 10.198.122.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor doesn't throw. Unpack is also tested here.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Expected len: 2 (option code + option len headers) + 6 (2 dest descriptor + 4 router addr).
    EXPECT_EQ(8, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=6, Route 1 (subnet 10.0.0.0/8,"
              " router IP 10.198.122.1)",
              option->toText());
}

// This test verifies constructor of the OptionClasslessStaticRoute class from config data.
// 3 static routes are defined.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorWithMoreRoutes) {
    // Prepare data to decode - 3 static routes
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,10.229.0.128/25-10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor doesn't throw. Unpack is also tested here.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Expected len: 2 (option code + option len headers) + 5 (1 dest descriptor + 4 router addr)
    // + 9 (5 dest descriptor + 4 router addr) + 8 (4 dest descriptor + 4 router addr).
    EXPECT_EQ(24, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=22, "
              "Route 1 (subnet 0.0.0.0/0, router IP 10.17.0.1), "
              "Route 2 (subnet 10.229.0.128/25, router IP 10.229.0.1), "
              "Route 3 (subnet 10.27.129.0/24, router IP 10.27.129.1)",
              option->toText());
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorMissingDash) {
    // Prepare data to decode - second route has missing dash separator
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,10.229.0.128/25 10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorMissingPrefixLen) {
    // Prepare data to decode - second route has missing "/prefix len"
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,10.229.0.128 - 10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorDestIpV6Given) {
    // Prepare data to decode - second route has IPv6 prefix
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,3001::5/64 - 10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorDestInvalidAddr) {
    // Prepare data to decode - second route has invalid IP address
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,1.2.3.a/32 - 10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorInvalidPrefixLen) {
    // Prepare data to decode - second route has invalid prefix len
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,1.2.3.4/a - 10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorPrefixLenTooBig) {
    // Prepare data to decode - second route has prefix len too big for IPv4
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,1.2.3.4/64 - 10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorRouterInvalidAddr) {
    // Prepare data to decode - second route has invalid router IP address
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,1.2.3.4/31 - 10.229.0.a, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorRouterIpV6Given) {
    // Prepare data to decode - second route has IPv6 router address
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,1.2.3.4/31 - 3001::5, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer has wrong format.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorCommaMissing) {
    // Prepare data to decode - comma separators are missing
    const std::string config = "'0.0.0.0/0 - 10.17.0.1 1.2.3.4/31 - 1.2.3.4 "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from config data throws an exception
// when data in the buffer is truncated.
TEST(OptionClasslessStaticRouteTest, bufferFromStrCtorDataTruncated) {
    // Prepare data to decode - truncated data
    const std::string config = "'0.0.'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Create option instance. Check that constructor throws OutOfRange during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::OutOfRange);
    ASSERT_FALSE(option);
}

// This test verifies constructor of the OptionClasslessStaticRoute class from
// on wire binary hex data.
// Only one static route is defined.
TEST(OptionClasslessStaticRouteTest, wireDatabufferCtorWithOneRoute) {
    // Prepare data to decode - one route with mask width = 8.
    const uint8_t buf_data[] = {
        8,               // mask width
        10,              // significant subnet octet for 10.0.0.0/8
        10, 198, 122, 1  // router IP address
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor doesn't throw. Unpack is also tested here.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Expected len: 2 (option code + option len headers) + 6 (2 dest descriptor + 4 router addr).
    EXPECT_EQ(8, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=6, Route 1 (subnet 10.0.0.0/8,"
              " router IP 10.198.122.1)",
              option->toText());
}

// This test verifies constructor of the OptionClasslessStaticRoute class from
// on wire binary hex data.
// 3 static routes are defined.
TEST(OptionClasslessStaticRouteTest, wireDatabufferCtorWithMoreRoutes) {
    // Prepare data to decode - 3 static routes
    const uint8_t buf_data[] = {
        0,                  // mask width
        10, 17,  0,   1,    // router IP address
        25,                 // mask width
        10, 229, 0,   128,  // significant subnet octets for 10.229.0.128/25
        10, 229, 0,   1,    // router IP address
        24,                 // mask width
        10, 27,  129,       // significant subnet octets for 10.27.129.0/24
        10, 27,  129, 1     // router IP address
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor doesn't throw. Unpack is also tested here.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Expected len: 2 (option code + option len headers) + 5 (1 dest descriptor + 4 router addr)
    // + 9 (5 dest descriptor + 4 router addr) + 8 (4 dest descriptor + 4 router addr).
    EXPECT_EQ(24, option->len());

    // Verify toText() is working fine.
    EXPECT_EQ("type=121(CLASSLESS_STATIC_ROUTE), len=22, "
              "Route 1 (subnet 0.0.0.0/0, router IP 10.17.0.1), "
              "Route 2 (subnet 10.229.0.128/25, router IP 10.229.0.1), "
              "Route 3 (subnet 10.27.129.0/24, router IP 10.27.129.1)",
              option->toText());
}

// This test verifies that constructor from on wire binary hex data throws an exception
// when data in the buffer is truncated.
TEST(OptionClasslessStaticRouteTest, wireDatabufferCtorDataTruncated) {
    // Prepare data to decode - truncated data
    const uint8_t buf_data[] = {
        8,   // mask width
        10,  // significant subnet octet for 10.0.0.0/8
        10,  // router IP address truncated
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws OutOfRange during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::OutOfRange);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from on wire binary hex data throws an exception
// when data of the second static route in the buffer is truncated.
TEST(OptionClasslessStaticRouteTest, wireDatabufferCtorSecondRouteDataTruncated) {
    // Prepare data to decode - truncated data
    const uint8_t buf_data[] = {
        0,             // mask width
        10, 17, 0, 1,  // router IP address
        25,            // mask width
        10, 229        // significant subnet octets truncated
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws OutOfRange during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::OutOfRange);
    ASSERT_FALSE(option);
}

// This test verifies that constructor from on wire binary hex data throws an exception
// when data of the second static route in the buffer contains bad subnet width.
TEST(OptionClasslessStaticRouteTest, wireDatabufferCtorSecondRouteBadSubnetWidth) {
    // Prepare data to decode - truncated data
    const uint8_t buf_data[] = {
        0,                 // mask width
        10,  17,  0, 1,    // router IP address
        125,               // bad mask width
        10,  229, 0, 128,  // significant subnet octets for 10.229.0.128/25
        10,  229, 0, 1     // router IP address
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws BadValue during Unpack.
    OptionClasslessStaticRoutePtr option;
    EXPECT_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())),
                 isc::BadValue);
    ASSERT_FALSE(option);
}

// This test verifies toText() method
TEST(OptionClasslessStaticRouteTest, toText) {
    // Prepare data to decode - 3 static routes
    const uint8_t buf_data[] = {
        0,                  // mask width
        10, 17,  0,   1,    // router IP address
        25,                 // mask width
        10, 229, 0,   128,  // significant subnet octets for 10.229.0.128/25
        10, 229, 0,   1,    // router IP address
        24,                 // mask width
        10, 27,  129,       // significant subnet octets for 10.27.129.0/24
        10, 27,  129, 1     // router IP address
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor doesn't throw. Unpack is also tested here.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    const uint8_t indent = 4;

    // Verify toText() is working fine.
    EXPECT_EQ("    type=121(CLASSLESS_STATIC_ROUTE), len=22, "  // 4 spaces of indentation
              "Route 1 (subnet 0.0.0.0/0, router IP 10.17.0.1), "
              "Route 2 (subnet 10.229.0.128/25, router IP 10.229.0.1), "
              "Route 3 (subnet 10.27.129.0/24, router IP 10.27.129.1)",
              option->toText(indent));
}

// This test verifies pack() method
TEST(OptionClasslessStaticRouteTest, pack) {
    // Prepare data to decode - 3 static routes
    const std::string config = "'0.0.0.0/0 - 10.17.0.1,10.229.0.128/25-10.229.0.1, "
                               "10.27.129.0/24 - 10.27.129.1'";
    OptionBuffer buf = isc::util::str::quotedStringToBinary(config);

    // Prepare expected packed data
    const uint8_t ref_data[] = {
        DHO_CLASSLESS_STATIC_ROUTE, // option code
        22,                         // data len
        0,                          // mask width
        10, 17,  0,   1,            // router IP address
        25,                         // mask width
        10, 229, 0,   128,          // significant subnet octets for 10.229.0.128/25
        10, 229, 0,   1,            // router IP address
        24,                         // mask width
        10, 27,  129,               // significant subnet octets for 10.27.129.0/24
        10, 27,  129, 1             // router IP address
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Create option instance. Check that constructor doesn't throw. Unpack is also tested here.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer output_buf(10);
    ASSERT_NO_THROW(option->pack(output_buf));

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, output_buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, output_buf.getData(), output_buf.getLength()));
}

// This test verifies that pack() method throws an exception when option len to be packed is
// bigger than 255 octets.
TEST(OptionClasslessStaticRouteTest, packThrows) {
    // Create option instance. Check that constructor doesn't throw.
    OptionClasslessStaticRoutePtr option;
    EXPECT_NO_THROW(option.reset(new OptionClasslessStaticRoute()));
    ASSERT_TRUE(option);

    // Create 9 octets long static route.
    StaticRouteTuple route = std::make_tuple(IOAddress("1.2.3.4"), 32, IOAddress("10.198.122.1"));
    // Add 50 routes
    uint8_t i = 0;
    while (i < 50) {
        option->addRoute(route);
        ++i;
    }

    // Expected len: 2 (headers) + 50x9 = 452
    EXPECT_EQ(452, option->len());

    // Check that pack() method throws an exception for option len > 255
    isc::util::OutputBuffer output_buf(10);
    ASSERT_THROW(option->pack(output_buf), isc::OutOfRange);
}

}  // namespace
