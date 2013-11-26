// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/tests/pkt_filter_test_utils.h>

#include <gtest/gtest.h>

#include <sys/socket.h>

using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// Port number used by tests.
const uint16_t PORT = 10067;
/// Size of the buffer holding received packets.
const size_t RECV_BUF_SIZE = 2048;

// Test fixture class inherits from the class common for all packet
// filter tests.
class PktFilterInetTest : public isc::dhcp::test::PktFilterTest {
public:
    PktFilterInetTest() : PktFilterTest(PORT) {
    }
};

// This test verifies that the PktFilterInet class reports its lack
// of capability to send packets to the host having no IP address
// assigned.
TEST_F(PktFilterInetTest, isDirectResponseSupported) {
    // Create object under test.
    PktFilterInet pkt_filter;
    // This Packet Filter class does not support direct responses
    // under any conditions.
    EXPECT_FALSE(pkt_filter.isDirectResponseSupported());
}

// This test verifies that the INET datagram socket is correctly opened and
// bound to the appropriate address and port.
TEST_F(PktFilterInetTest, openSocket) {
    // Create object representing loopback interface.
    Iface iface(ifname_, ifindex_);
    // Set loopback address.
    IOAddress addr("127.0.0.1");

    // Try to open socket.
    PktFilterInet pkt_filter;
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT,
                                       false, false);
    // For the packet filter in use, the fallback socket shouldn't be opened.
    // Fallback is typically opened for raw sockets.
    EXPECT_LT(sock_info_.fallbackfd_, 0);

    // Test the primary socket.
    testDgramSocket(sock_info_.sockfd_);
}

// This test verifies that the packet is correctly sent over the INET
// datagram socket.
TEST_F(PktFilterInetTest, send) {
    // Let's create a DHCPv4 packet.
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 0));
    ASSERT_TRUE(pkt);

    // Set required fields.
    pkt->setLocalAddr(IOAddress("127.0.0.1"));
    pkt->setRemoteAddr(IOAddress("127.0.0.1"));
    pkt->setRemotePort(PORT);
    pkt->setLocalPort(PORT + 1);
    pkt->setIndex(ifindex_);
    pkt->setIface(ifname_);
    pkt->setHops(6);
    pkt->setSecs(42);
    pkt->setCiaddr(IOAddress("192.0.2.1"));
    pkt->setSiaddr(IOAddress("192.0.2.2"));
    pkt->setYiaddr(IOAddress("192.0.2.3"));
    pkt->setGiaddr(IOAddress("192.0.2.4"));

    // Create the on-wire data.
    ASSERT_NO_THROW(pkt->pack());

    // Packet will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterInet pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // Send the packet over the socket.
    ASSERT_NO_THROW(pkt_filter.send(iface, sock_info_.sockfd_, pkt));

    // Read the data from socket.
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock_info_.sockfd_, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int result = select(sock_info_.sockfd_ + 1, &readfds, NULL, NULL, &timeout);
    // We should receive some data from loopback interface.
    ASSERT_GT(result, 0);

    // Get the actual data.
    uint8_t rcv_buf[RECV_BUF_SIZE];
    result = recv(sock_info_.sockfd_, rcv_buf, RECV_BUF_SIZE, 0);
    ASSERT_GT(result, 0);

    // Create the DHCPv4 packet from the received data.
    Pkt4Ptr rcvd_pkt(new Pkt4(rcv_buf, result));
    ASSERT_TRUE(rcvd_pkt);

    // Parse the packet.
    ASSERT_NO_THROW(rcvd_pkt->unpack());

    // Verify that the received packet matches sent packet.
    EXPECT_EQ(pkt->getHops(), rcvd_pkt->getHops());
    EXPECT_EQ(pkt->getOp(),   rcvd_pkt->getOp());
    EXPECT_EQ(pkt->getSecs(), rcvd_pkt->getSecs());
    EXPECT_EQ(pkt->getFlags(), rcvd_pkt->getFlags());
    EXPECT_EQ(pkt->getCiaddr(), rcvd_pkt->getCiaddr());
    EXPECT_EQ(pkt->getSiaddr(), rcvd_pkt->getSiaddr());
    EXPECT_EQ(pkt->getYiaddr(), rcvd_pkt->getYiaddr());
    EXPECT_EQ(pkt->getGiaddr(), rcvd_pkt->getGiaddr());
    EXPECT_EQ(pkt->getTransid(), rcvd_pkt->getTransid());
    EXPECT_TRUE(pkt->getSname() == rcvd_pkt->getSname());
    EXPECT_TRUE(pkt->getFile() == rcvd_pkt->getFile());
    EXPECT_EQ(pkt->getHtype(), rcvd_pkt->getHtype());
    EXPECT_EQ(pkt->getHlen(), rcvd_pkt->getHlen());
}

// This test verifies that the DHCPv4 packet is correctly received via
// INET datagram socket and that it matches sent packet.
TEST_F(PktFilterInetTest, receive) {
    // Let's create a DHCPv4 packet.
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 0));
    ASSERT_TRUE(pkt);

    // Set required fields.
    pkt->setLocalAddr(IOAddress("127.0.0.1"));
    pkt->setRemoteAddr(IOAddress("127.0.0.1"));
    pkt->setRemotePort(PORT);
    pkt->setLocalPort(PORT + 1);
    pkt->setIndex(ifindex_);
    pkt->setIface(ifname_);
    pkt->setHops(6);
    pkt->setSecs(42);
    pkt->setCiaddr(IOAddress("192.0.2.1"));
    pkt->setSiaddr(IOAddress("192.0.2.2"));
    pkt->setYiaddr(IOAddress("192.0.2.3"));
    pkt->setGiaddr(IOAddress("192.0.2.4"));

    // Create the on-wire data.
    ASSERT_NO_THROW(pkt->pack());

    // Packet will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterInet pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // Send the packet over the socket.
    ASSERT_NO_THROW(pkt_filter.send(iface, sock_info_.sockfd_, pkt));

    // Receive the packet.
    Pkt4Ptr rcvd_pkt = pkt_filter.receive(iface, sock_info_);
    // Check that the packet has been correctly received.
    ASSERT_TRUE(rcvd_pkt);

    // Parse the packet.
    ASSERT_NO_THROW(rcvd_pkt->unpack());

    // Verify that the received packet matches sent packet.
    EXPECT_EQ(pkt->getHops(), rcvd_pkt->getHops());
    EXPECT_EQ(pkt->getOp(),   rcvd_pkt->getOp());
    EXPECT_EQ(pkt->getSecs(), rcvd_pkt->getSecs());
    EXPECT_EQ(pkt->getFlags(), rcvd_pkt->getFlags());
    EXPECT_EQ(pkt->getCiaddr(), rcvd_pkt->getCiaddr());
    EXPECT_EQ(pkt->getSiaddr(), rcvd_pkt->getSiaddr());
    EXPECT_EQ(pkt->getYiaddr(), rcvd_pkt->getYiaddr());
    EXPECT_EQ(pkt->getGiaddr(), rcvd_pkt->getGiaddr());
    EXPECT_EQ(pkt->getTransid(), rcvd_pkt->getTransid());
    EXPECT_TRUE(pkt->getSname() == rcvd_pkt->getSname());
    EXPECT_TRUE(pkt->getFile() == rcvd_pkt->getFile());
    EXPECT_EQ(pkt->getHtype(), rcvd_pkt->getHtype());
    EXPECT_EQ(pkt->getHlen(), rcvd_pkt->getHlen());
}

} // anonymous namespace
