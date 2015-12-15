// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_endpoint.h>
#include <asiolink/io_error.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#include <sstream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

using namespace isc::asiolink;

namespace {
typedef boost::shared_ptr<const IOEndpoint> ConstIOEndpointPtr;

TEST(IOEndpointTest, createUDPv4) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_UDP,
                                             IOAddress("192.0.2.1"), 53210));
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(53210, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(static_cast<short>(IPPROTO_UDP), ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv4) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_TCP,
                                             IOAddress("192.0.2.1"), 5301));
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(5301, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(static_cast<short>(IPPROTO_TCP), ep->getProtocol());
}

TEST(IOEndpointTest, createUDPv6) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_UDP,
                                             IOAddress("2001:db8::1234"),
                                             5302));
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5302, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(static_cast<short>(IPPROTO_UDP), ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv6) {
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_TCP,
                                             IOAddress("2001:db8::1234"),
                                             5303));
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5303, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(static_cast<short>(IPPROTO_TCP), ep->getProtocol());
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

// A faked IOEndpoint for an uncommon address family.  It wouldn't be possible
// to create via the normal factory, so we define a special derived class
// for it.
class TestIOEndpoint : public IOEndpoint {
    virtual IOAddress getAddress() const {
        return IOAddress("2001:db8::bad:add");
    }
    virtual uint16_t getPort() const { return (42); }
    virtual short getProtocol() const { return (IPPROTO_UDP); }
    virtual short getFamily() const { return (AF_UNSPEC); }
    virtual const struct sockaddr& getSockAddr() const {
        static struct sockaddr sa_placeholder;
        return (sa_placeholder);
    }
};

void
checkEndpointText(const std::string& expected, const IOEndpoint& ep) {
    std::ostringstream oss;
    oss << ep;
    EXPECT_EQ(expected, oss.str());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST(IOEndpointTest, LeftShiftOperator) {
    // UDP/IPv4
    ConstIOEndpointPtr ep(IOEndpoint::create(IPPROTO_UDP,
                                             IOAddress("192.0.2.1"), 53210));
    checkEndpointText("192.0.2.1:53210", *ep);

    // UDP/IPv6
    ep.reset(IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::53"), 53));
    checkEndpointText("[2001:db8::53]:53", *ep);

    // Same for TCP: shouldn't be different
    ep.reset(IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.1"), 53210));
    checkEndpointText("192.0.2.1:53210", *ep);
    ep.reset(IOEndpoint::create(IPPROTO_TCP, IOAddress("2001:db8::53"), 53));
    checkEndpointText("[2001:db8::53]:53", *ep);

    // Uncommon address family.  The actual behavior doesn't matter much
    // in practice, but we check such input doesn't make it crash.
    // We explicitly instantiate the test EP because otherwise some compilers
    // would be confused and complain.
    TestIOEndpoint test_ep;
    checkEndpointText("2001:db8::bad:add:42", test_ep);
}
}
