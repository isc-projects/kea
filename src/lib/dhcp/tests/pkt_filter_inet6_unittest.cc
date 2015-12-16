// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcp/pkt_filter_inet6.h>
#include <dhcp/tests/pkt_filter6_test_utils.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// Port number used by tests.
const uint16_t PORT = 10546;
/// Size of the buffer holding received packets.
const size_t RECV_BUF_SIZE = 2048;

// Test fixture class inherits from the class common for all packet
// filter tests.
class PktFilterInet6Test : public isc::dhcp::test::PktFilter6Test {
public:
    PktFilterInet6Test() : PktFilter6Test(PORT) {
    }
};

// This test verifies that the INET6 datagram socket is correctly opened and
// bound to the appropriate address and port.
TEST_F(PktFilterInet6Test, openSocket) {
    // Create object representing loopback interface.
    Iface iface(ifname_, ifindex_);
    // Set loopback address.
    IOAddress addr("::1");

    // Try to open socket.
    PktFilterInet6 pkt_filter;
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, true);
    // For the packet filter in use, the fallback socket shouldn't be opened.
    // Fallback is typically opened for raw IPv4 sockets.
    EXPECT_LT(sock_info_.fallbackfd_, 0);

    // Test the primary socket.
    testDgramSocket(sock_info_.sockfd_);
}

// This test verifies that the packet is correctly sent over the INET6
// datagram socket.
TEST_F(PktFilterInet6Test, send) {
    // Packet will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("::1");

    // Create an instance of the class which we are testing.
    PktFilterInet6 pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, true);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // Send the packet over the socket.
    ASSERT_NO_THROW(pkt_filter.send(iface, sock_info_.sockfd_, test_message_));

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

    // Create the DHCPv6 packet from the received data.
    Pkt6Ptr rcvd_pkt(new Pkt6(rcv_buf, result));
    ASSERT_TRUE(rcvd_pkt);

    // Parse the packet.
    ASSERT_NO_THROW(rcvd_pkt->unpack());

    // Check if the received message is correct.
    testRcvdMessage(rcvd_pkt);

}

// This test verifies that the DHCPv6 packet is correctly received via
// INET6 datagram socket and that it matches sent packet.
TEST_F(PktFilterInet6Test, receive) {

    // Packet will be received over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("::1");

    // Create an instance of the class which we are testing.
    PktFilterInet6 pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT + 1, true);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // Send a DHCPv6 message to the local loopback address and server's port.
    //    ASSERT_NO_THROW(pkt_filter.send(iface, sock_info_.sockfd_, test_message_));
    sendMessage();

    // Receive the packet.
    Pkt6Ptr rcvd_pkt = pkt_filter.receive(sock_info_);
    // Check that the packet has been correctly received.
    ASSERT_TRUE(rcvd_pkt);

    // Parse the packet.
    ASSERT_NO_THROW(rcvd_pkt->unpack());

    // Check if the received message is correct.
    testRcvdMessage(rcvd_pkt);
    }

} // anonymous namespace
