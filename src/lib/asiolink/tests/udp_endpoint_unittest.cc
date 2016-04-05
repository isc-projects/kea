// Copyright (C) 2011-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/udp_endpoint.h>

#include <gtest/gtest.h>

#include <string>

using namespace isc::asiolink;
using namespace std;

// This test checks that the endpoint can manage its own internal
// boost::asio::ip::udp::endpoint object.

TEST(UDPEndpointTest, v4Address) {
    const string test_address("192.0.2.1");
    const unsigned short test_port = 5301;

    IOAddress address(test_address);
    UDPEndpoint endpoint(address, test_port);

    EXPECT_TRUE(address == endpoint.getAddress());
    EXPECT_EQ(test_port, endpoint.getPort());
    EXPECT_EQ(static_cast<short>(IPPROTO_UDP), endpoint.getProtocol());
    EXPECT_EQ(AF_INET, endpoint.getFamily());
}

TEST(UDPEndpointTest, v6Address) {
    const string test_address("2001:db8::1235");
    const unsigned short test_port = 5302;

    IOAddress address(test_address);
    UDPEndpoint endpoint(address, test_port);

    EXPECT_TRUE(address == endpoint.getAddress());
    EXPECT_EQ(test_port, endpoint.getPort());
    EXPECT_EQ(static_cast<short>(IPPROTO_UDP), endpoint.getProtocol());
    EXPECT_EQ(AF_INET6, endpoint.getFamily());
}
