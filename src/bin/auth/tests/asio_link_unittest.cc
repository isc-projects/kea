// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdint.h>

#include <functional>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/tests/unittest_util.h>

#include <auth/asio_link.h>

using isc::UnitTestUtil;
using namespace std;
using namespace asio_link;

namespace {
const char* const TEST_PORT = "53535";
const char* const TEST_IPV6_ADDR = "::1";
const char* const TEST_IPV4_ADDR = "127.0.0.1";
// This data is intended to be valid as a DNS/TCP-like message: the first
// two octets encode the length of the rest of the data.  This is crucial
// for the tests below.
const uint8_t test_data[] = {0, 4, 1, 2, 3, 4};

TEST(IOAddressTest, fromText) {
    IOAddress io_address_v4("192.0.2.1");
    EXPECT_EQ("192.0.2.1", io_address_v4.toText());

    IOAddress io_address_v6("2001:db8::1234");
    EXPECT_EQ("2001:db8::1234", io_address_v6.toText());

    // bogus IPv4 address-like input
    EXPECT_THROW(IOAddress("192.0.2.2.1"), IOError);

    // bogus IPv6 address-like input
    EXPECT_THROW(IOAddress("2001:db8:::1234"), IOError);
}

TEST(IOEndpointTest, create) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.1"), 5300);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    delete ep;

    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.1"), 5300);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    delete ep;

    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::1234"), 5300);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    delete ep;

    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("2001:db8::1234"), 5300);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    delete ep;

    EXPECT_THROW(IOEndpoint::create(IPPROTO_IP, IOAddress("192.0.2.1"),
                                    5300)->getAddress().toText(),
                 IOError);
}

TEST(IOSocketTest, dummySockets) {
    EXPECT_EQ(IPPROTO_UDP, IOSocket::getDummyUDPSocket().getProtocol());
    EXPECT_EQ(IPPROTO_TCP, IOSocket::getDummyTCPSocket().getProtocol());
    EXPECT_EQ(-1, IOSocket::getDummyUDPSocket().getNative());
    EXPECT_EQ(-1, IOSocket::getDummyTCPSocket().getNative());
}

TEST(IOServiceTest, badPort) {
    EXPECT_THROW(IOService(NULL, *"65536", true, false), IOError);
    EXPECT_THROW(IOService(NULL, *"5300.0", true, false), IOError);
    EXPECT_THROW(IOService(NULL, *"-1", true, false), IOError);
    EXPECT_THROW(IOService(NULL, *"domain", true, false), IOError);
}

TEST(IOServiceTest, badAddress) {
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"192.0.2.1.1"),
                 IOError);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"2001:db8:::1"),
                 IOError);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"localhost"),
                 IOError);
}

TEST(IOServiceTest, unavailableAddress) {
    // These addresses should generally be unavailable as a valid local
    // address, although there's no guarantee in theory.
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"ffff:ffff::"), IOError);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"255.255.255.255"), IOError);
}

TEST(IOServiceTest, duplicateBind) {
    // In each sub test case, second attempt should fail due to duplicate bind

    // IPv6, "any" address
    IOService* io_service = new IOService(NULL, *TEST_PORT, false, true);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, false, true), IOError);
    delete io_service;

    // IPv6, specific address
    io_service = new IOService(NULL, *TEST_PORT, *TEST_IPV6_ADDR);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *TEST_IPV6_ADDR), IOError);
    delete io_service;

    // IPv4, "any" address
    io_service = new IOService(NULL, *TEST_PORT, true, false);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, true, false), IOError);
    delete io_service;

    // IPv4, specific address
    io_service = new IOService(NULL, *TEST_PORT, *TEST_IPV4_ADDR);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *TEST_IPV4_ADDR), IOError);
    delete io_service;
}

struct addrinfo*
resolveAddress(const int family, const int sock_type, const int protocol) {
    const char* const addr = (family == AF_INET6) ?
        TEST_IPV6_ADDR : TEST_IPV4_ADDR;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = sock_type;
    hints.ai_protocol = protocol;

    struct addrinfo* res;
    const int error = getaddrinfo(addr, TEST_PORT, &hints, &res);
    if (error != 0) {
        isc_throw(IOError, "getaddrinfo failed: " << gai_strerror(error));
    }

    return (res);
}

class ASIOLinkTest : public ::testing::Test {
protected:
    ASIOLinkTest();
    ~ASIOLinkTest() {
        if (res_ != NULL) {
            freeaddrinfo(res_);
        }
        if (sock_ != -1) {
            close(sock_);
        }
    }
    void sendUDP(const int family) {
        res_ = resolveAddress(family, SOCK_DGRAM, IPPROTO_UDP);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        const int cc = sendto(sock_, test_data, sizeof(test_data), 0,
                              res_->ai_addr, res_->ai_addrlen);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected sendto result: " << cc);
        }
        io_service_.run();
    }
    void sendTCP(const int family) {
        res_ = resolveAddress(family, SOCK_STREAM, IPPROTO_TCP);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        if (connect(sock_, res_->ai_addr, res_->ai_addrlen) < 0) {
            isc_throw(IOError, "failed to connect to the test server");
        }
        const int cc = send(sock_, test_data, sizeof(test_data), 0);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected sendto result: " << cc);
        }
        io_service_.run();
    }
public:
    void callBack(const IOMessage& io_message) {
        callback_protocol_ = io_message.getSocket().getProtocol();
        callback_native_ = io_message.getSocket().getNative();
        callback_address_ =
            io_message.getRemoteEndpoint().getAddress().toText();
        callback_data_.assign(
            static_cast<const uint8_t*>(io_message.getData()),
            static_cast<const uint8_t*>(io_message.getData()) +
            io_message.getDataSize());
        io_service_.stop();
    }
protected:
    IOService io_service_;
    int callback_protocol_;
    int callback_native_;
    string callback_address_;
    vector<uint8_t> callback_data_;
    int sock_;
private:
    struct addrinfo* res_;
};

class ASIOCallBack : public std::unary_function<IOMessage, void> {
public:
    ASIOCallBack(ASIOLinkTest* test_obj) : test_obj_(test_obj) {}
    void operator()(const IOMessage& io_message) const {
        test_obj_->callBack(io_message);
    }
private:
    ASIOLinkTest* test_obj_;
};

ASIOLinkTest::ASIOLinkTest() :
    io_service_(NULL, *TEST_PORT, true, true),
    sock_(-1), res_(NULL)
{
    io_service_.setCallBack(ASIOCallBack(this));
}

TEST_F(ASIOLinkTest, v6UDPSend) {
    sendUDP(AF_INET6);
    // There doesn't seem to be an effective test for the validity of 'native'.
    // One thing we are sure is it must be different from our local socket.
    EXPECT_NE(callback_native_, sock_);
    EXPECT_EQ(IPPROTO_UDP, callback_protocol_);
    EXPECT_EQ(TEST_IPV6_ADDR, callback_address_);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &callback_data_[0],
                        callback_data_.size(), test_data, sizeof(test_data));
}

TEST_F(ASIOLinkTest, v6TCPSend) {
    sendTCP(AF_INET6);
    EXPECT_NE(callback_native_, sock_);
    EXPECT_EQ(IPPROTO_TCP, callback_protocol_);
    EXPECT_EQ(TEST_IPV6_ADDR, callback_address_);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &callback_data_[0],
                        callback_data_.size(),
                        test_data + 2, sizeof(test_data) - 2);
}

TEST_F(ASIOLinkTest, v4UDPSend) {
    sendUDP(AF_INET);
    EXPECT_NE(callback_native_, sock_);
    EXPECT_EQ(IPPROTO_UDP, callback_protocol_);
    EXPECT_EQ(TEST_IPV4_ADDR, callback_address_);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &callback_data_[0],
                        callback_data_.size(), test_data, sizeof(test_data));
}

TEST_F(ASIOLinkTest, v4TCPSend) {
    sendTCP(AF_INET);
    EXPECT_NE(callback_native_, sock_);
    EXPECT_EQ(IPPROTO_TCP, callback_protocol_);
    EXPECT_EQ(TEST_IPV4_ADDR, callback_address_);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &callback_data_[0],
                        callback_data_.size(),
                        test_data + 2, sizeof(test_data) - 2);
}

}
