// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <string>

#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <asiolink/io_address.h>
#include <asiolink/tcp_endpoint.h>

using namespace isc::asiolink;
using namespace std;

// This test checks that the endpoint can manage its own internal
// boost::asio::ip::tcp::endpoint object.

TEST(TCPEndpointTest, v4Address) {
    const string test_address("192.0.2.1");
    const unsigned short test_port = 5301;

    IOAddress address(test_address);
    TCPEndpoint endpoint(address, test_port);

    EXPECT_TRUE(address == endpoint.getAddress());
    EXPECT_EQ(test_port, endpoint.getPort());
    EXPECT_EQ(static_cast<short>(IPPROTO_TCP), endpoint.getProtocol());
    EXPECT_EQ(AF_INET, endpoint.getFamily());
}

TEST(TCPEndpointTest, v6Address) {
    const string test_address("2001:db8::1235");
    const unsigned short test_port = 5302;

    IOAddress address(test_address);
    TCPEndpoint endpoint(address, test_port);

    EXPECT_TRUE(address == endpoint.getAddress());
    EXPECT_EQ(test_port, endpoint.getPort());
    EXPECT_EQ(static_cast<short>(IPPROTO_TCP), endpoint.getProtocol());
    EXPECT_EQ(AF_INET6, endpoint.getFamily());
}
