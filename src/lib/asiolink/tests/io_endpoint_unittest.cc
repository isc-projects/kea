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

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include <boost/shared_ptr.hpp>

#include <asiolink/io_endpoint.h>
#include <asiolink/io_error.h>

using boost::shared_ptr;
using namespace isc::asiolink;

namespace {
typedef shared_ptr<const IOEndpoint> ConstIOEndpointPtr;

TEST(IOEndpointTest, createUDPv4) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_UDP,
                                             IOAddress("192.0.2.1"), 53210));
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(53210, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_UDP, ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv4) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_TCP,
                                             IOAddress("192.0.2.1"), 5301));
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(5301, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_TCP, ep->getProtocol());
}

TEST(IOEndpointTest, createUDPv6) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_UDP,
                                             IOAddress("2001:db8::1234"),
                                             5302));
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5302, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_UDP, ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv6) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_TCP,
                                             IOAddress("2001:db8::1234"),
                                             5303));
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5303, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_TCP, ep->getProtocol());
}

TEST(IOEndpointTest, equality) {
    std::vector<ConstIOEndpointPtr> epv;
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("2001:db8::1234"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("2001:db8::1234"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("2001:db8::1234"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("2001:db8::1234"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("2001:db8::1235"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("2001:db8::1235"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("2001:db8::1235"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("2001:db8::1235"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("192.0.2.1"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("192.0.2.1"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("192.0.2.1"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("192.0.2.1"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("192.0.2.2"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("192.0.2.2"), 5303)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_TCP,
                                         IOAddress("192.0.2.2"), 5304)));
    epv.push_back(ConstIOEndpointPtr(
                      IOEndpoint::create(IPPROTO_UDP,
                                         IOAddress("192.0.2.2"), 5304)));

    for (size_t i = 0; i < epv.size(); ++i) {
        for (size_t j = 0; j < epv.size(); ++j) {
            if (i != j) {
                // We use EXPECT_TRUE/FALSE instead of _EQ here, since
                // _EQ requires there is an operator<< as well
                EXPECT_FALSE(*epv[i] == *epv[j]);
                EXPECT_TRUE(*epv[i] != *epv[j]);
            }
        }
    }

    // Create a second array with exactly the same values. We use create()
    // again to make sure we get different endpoints
    std::vector<ConstIOEndpointPtr> epv2;
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP,
                                          IOAddress("2001:db8::1234"), 5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP,
                                          IOAddress("2001:db8::1234"), 5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP,
                                          IOAddress("2001:db8::1234"), 5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP,
                                          IOAddress("2001:db8::1234"), 5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP,
                                          IOAddress("2001:db8::1235"), 5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP,
                                          IOAddress("2001:db8::1235"), 5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP,
                                          IOAddress("2001:db8::1235"), 5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP,
                                          IOAddress("2001:db8::1235"), 5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP,
                                          IOAddress("192.0.2.1"), 5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP,
                                          IOAddress("192.0.2.1"), 5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.1"),
                                          5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.1"),
                                          5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.2"),
                                          5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.2"),
                                          5303)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.2"),
                                          5304)));
    epv2.push_back(ConstIOEndpointPtr(
                       IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.2"),
                                          5304)));

    for (size_t i = 0; i < epv.size(); ++i) {
        EXPECT_TRUE(*epv[i] == *epv2[i]);
        EXPECT_FALSE(*epv[i] != *epv2[i]);
    }
}

TEST(IOEndpointTest, createIPProto) {
    EXPECT_THROW(IOEndpoint::create(IPPROTO_IP, IOAddress("192.0.2.1"),
                                    53210)->getAddress().toText(),
                 IOError);
}

void
sockAddrMatch(const struct sockaddr& actual_sa,
              const char* const expected_addr_text,
              const char* const expected_port_text)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM; // this shouldn't matter
    hints.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;

    struct addrinfo* res;
    ASSERT_EQ(0, getaddrinfo(expected_addr_text, expected_port_text, &hints,
                             &res));
    EXPECT_EQ(res->ai_family, actual_sa.sa_family);
#ifdef HAVE_SA_LEN
    // ASIO doesn't seem to set sa_len, so we set it to the expected value
    res->ai_addr->sa_len = actual_sa.sa_len;
#endif
    EXPECT_EQ(0, memcmp(res->ai_addr, &actual_sa, res->ai_addrlen));
    freeaddrinfo(res);
}

TEST(IOEndpointTest, getSockAddr) {
    // UDP/IPv4
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_UDP,
                                             IOAddress("192.0.2.1"), 53210));
    sockAddrMatch(ep->getSockAddr(), "192.0.2.1", "53210");

    // UDP/IPv6
    ep.reset(IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::53"), 53));
    sockAddrMatch(ep->getSockAddr(), "2001:db8::53", "53");

    // TCP/IPv4
    ep.reset(IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.2"), 53211));
    sockAddrMatch(ep->getSockAddr(), "192.0.2.2", "53211");

    // TCP/IPv6
    ep.reset(IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::5300"), 35));
    sockAddrMatch(ep->getSockAddr(), "2001:db8::5300", "35");
}

}
