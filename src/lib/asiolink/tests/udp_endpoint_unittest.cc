// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <asiolink/io_address.h>
#include <asiolink/udp_endpoint.h>

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
