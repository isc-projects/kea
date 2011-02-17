// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <gtest/gtest.h>

#include <asiolink/asiolink.h>

using namespace asiolink;

TEST(IOEndpointTest, createUDPv4) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.1"), 5300);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(5300, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_UDP, ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv4) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.1"), 5301);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(5301, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_TCP, ep->getProtocol());
}

TEST(IOEndpointTest, createUDPv6) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::1234"), 5302);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5302, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_UDP, ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv6) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("2001:db8::1234"), 5303);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5303, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_TCP, ep->getProtocol());
}

TEST(IOEndpointTest, createIPProto) {
    EXPECT_THROW(IOEndpoint::create(IPPROTO_IP, IOAddress("192.0.2.1"),
                                    5300)->getAddress().toText(),
                 IOError);
}

