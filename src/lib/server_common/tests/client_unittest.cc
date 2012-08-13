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

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <string>
#include <sstream>

#include <boost/scoped_ptr.hpp>

#include <acl/ip_check.h>

#include <asiolink/io_address.h>
#include <asiolink/io_socket.h>
#include <asiolink/io_message.h>

#include <server_common/client.h>

#include <gtest/gtest.h>

using boost::lexical_cast;
using boost::scoped_ptr;
using namespace isc::acl;
using namespace isc::asiolink;
using namespace isc::server_common;

namespace {

class ClientTest : public ::testing::Test {
protected:
    ClientTest() {
        endpoint4.reset(IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.1"),
                                           53214));
        endpoint6.reset(IOEndpoint::create(IPPROTO_TCP,
                                           IOAddress("2001:db8::1"), 53216));
        request4.reset(new IOMessage(NULL, 0, IOSocket::getDummyUDPSocket(),
                                     *endpoint4));
        request6.reset(new IOMessage(NULL, 0, IOSocket::getDummyTCPSocket(),
                                     *endpoint6));
        client4.reset(new Client(*request4));
        client6.reset(new Client(*request6));
    }
    scoped_ptr<const IOEndpoint> endpoint4;
    scoped_ptr<const IOEndpoint> endpoint6;
    scoped_ptr<const IOMessage> request4;
    scoped_ptr<const IOMessage> request6;
    scoped_ptr<const Client> client4;
    scoped_ptr<const Client> client6;
};

TEST_F(ClientTest, constructIPv4) {
    EXPECT_EQ(AF_INET, client4->getRequestSourceEndpoint().getFamily());
    EXPECT_EQ(IPPROTO_UDP, client4->getRequestSourceEndpoint().getProtocol());
    EXPECT_EQ("192.0.2.1",
              client4->getRequestSourceEndpoint().getAddress().toText());
    EXPECT_EQ(53214, client4->getRequestSourceEndpoint().getPort());

    const uint8_t expected_data[] = { 192, 0, 2, 1 };
    EXPECT_EQ(AF_INET, client4->getRequestSourceIPAddress().getFamily());
    ASSERT_EQ(4, client4->getRequestSourceIPAddress().getLength());
    EXPECT_EQ(0, memcmp(expected_data,
                        client4->getRequestSourceIPAddress().getData(), 4));
}

TEST_F(ClientTest, constructIPv6) {
    EXPECT_EQ(AF_INET6, client6->getRequestSourceEndpoint().getFamily());
    EXPECT_EQ(IPPROTO_TCP, client6->getRequestSourceEndpoint().getProtocol());
    EXPECT_EQ("2001:db8::1",
              client6->getRequestSourceEndpoint().getAddress().toText());
    EXPECT_EQ(53216, client6->getRequestSourceEndpoint().getPort());

    const uint8_t expected_data[] = { 0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x01 };
    EXPECT_EQ(AF_INET6, client6->getRequestSourceIPAddress().getFamily());
    ASSERT_EQ(16, client6->getRequestSourceIPAddress().getLength());
    EXPECT_EQ(0, memcmp(expected_data,
                        client6->getRequestSourceIPAddress().getData(), 16));
}

TEST_F(ClientTest, toText) {
    EXPECT_EQ("192.0.2.1#53214", client4->toText());
    EXPECT_EQ("2001:db8::1#53216", client6->toText());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(ClientTest, LeftShiftOperator) {
    std::ostringstream oss;
    oss << *client4 << "more text";
    EXPECT_EQ(client4->toText() + std::string("more text"), oss.str());
}
}
