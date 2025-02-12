// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <icmp_endpoint.h>

#include <gtest/gtest.h>

#include <string>

using namespace isc::asiolink;
using namespace isc::ping_check;
using namespace std;

// This test checks that the endpoint can manage its own internal
// boost::asio::ip::icmp::endpoint object for IPv4.
TEST(ICMPEndpointTest, v4Address) {
    const string test_address("192.0.2.1");

    IOAddress address(test_address);
    ICMPEndpoint endpoint(address);

    EXPECT_TRUE(address == endpoint.getAddress());
    EXPECT_EQ(static_cast<short>(IPPROTO_ICMP), endpoint.getProtocol());
    EXPECT_EQ(AF_INET, endpoint.getFamily());
}

// This test checks that the endpoint can manage its own internal
// boost::asio::ip::icmp::endpoint object for IPv6.
TEST(ICMPEndpointTest, v6Address) {
    const string test_address("2001:db8::1235");

    IOAddress address(test_address);
    ICMPEndpoint endpoint(address);

    EXPECT_TRUE(address == endpoint.getAddress());
    EXPECT_EQ(static_cast<short>(IPPROTO_ICMPV6), endpoint.getProtocol());
    EXPECT_EQ(AF_INET6, endpoint.getFamily());
}
