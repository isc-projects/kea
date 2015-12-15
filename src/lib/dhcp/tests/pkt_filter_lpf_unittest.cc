// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_lpf.h>
#include <dhcp/protocol_util.h>
#include <dhcp/tests/pkt_filter_test_utils.h>
#include <util/buffer.h>

#include <gtest/gtest.h>

#include <linux/if_packet.h>
#include <sys/socket.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// Port number used by tests.
const uint16_t PORT = 10067;
/// Size of the buffer holding received packets.
const size_t RECV_BUF_SIZE = 2048;

// Test fixture class inherits from the class common for all packet
// filter tests.
class PktFilterLPFTest : public isc::dhcp::test::PktFilterTest {
public:
    PktFilterLPFTest() : PktFilterTest(PORT) {
    }
};

// This test verifies that the PktFilterLPF class reports its capability
// to send packets to the host having no IP address assigned.
TEST_F(PktFilterLPFTest, isDirectResponseSupported) {
    // Create object under test.
    PktFilterLPF pkt_filter;
    // Must support direct responses.
    EXPECT_TRUE(pkt_filter.isDirectResponseSupported());
}

// All tests below require root privileges to execute successfully. If
// they are run as non-root user they will fail due to insufficient privileges
// to open raw network sockets. Therefore, they should remain disabled by default
// and "DISABLED_" tags should not be removed. If one is willing to run these
// tests please run "make check" as root and enable execution of disabled tests
// by setting GTEST_ALSO_RUN_DISABLED_TESTS to a value other than 0. In order
// to run tests from this particular file, set the GTEST_FILTER environmental
// variable to "PktFilterLPFTest.*" apart from GTEST_ALSO_RUN_DISABLED_TESTS
// setting.

// This test verifies that the raw AF_PACKET family socket can
// be opened and bound to the specific interface.
TEST_F(PktFilterLPFTest, DISABLED_openSocket) {
    // Create object representing loopback interface.
    Iface iface(ifname_, ifindex_);
    // Set loopback address.
    IOAddress addr("127.0.0.1");

    // Try to open socket.
    PktFilterLPF pkt_filter;
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);

    // Check that the primary socket has been opened.
    ASSERT_GE(sock_info_.sockfd_, 0);
    // Check that the fallback socket has been opened too.
    ASSERT_GE(sock_info_.fallbackfd_, 0);

    // Verify that the socket belongs to AF_PACKET family.
    sockaddr_ll sock_address;
    socklen_t sock_address_len = sizeof(sock_address);
    ASSERT_EQ(0, getsockname(sock_info_.sockfd_,
                             reinterpret_cast<sockaddr*>(&sock_address),
                             &sock_address_len));
    EXPECT_EQ(AF_PACKET, sock_address.sll_family);

    // Verify that the socket is bound to appropriate interface.
    EXPECT_EQ(ifindex_, sock_address.sll_ifindex);

    // Verify that the socket has SOCK_RAW type.
    int sock_type;
    socklen_t sock_type_len = sizeof(sock_type);
    ASSERT_EQ(0, getsockopt(sock_info_.sockfd_, SOL_SOCKET, SO_TYPE,
                            &sock_type, &sock_type_len));
    EXPECT_EQ(SOCK_RAW, sock_type);
}

// This test verifies correctness of sending DHCP packet through the raw
// socket, whereby all IP stack headers are hand-crafted.
TEST_F(PktFilterLPFTest, DISABLED_send) {
    // Packet will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterLPF pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.

    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);

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

    Pkt4Ptr dummy_pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 0));

    InputBuffer buf(rcv_buf, result);

    // Decode ethernet, ip and udp headers.
    decodeEthernetHeader(buf, dummy_pkt);
    decodeIpUdpHeader(buf, dummy_pkt);

    // Create the DHCPv4 packet from the received data.
    std::vector<uint8_t> dhcp_buf;
    buf.readVector(dhcp_buf, buf.getLength() - buf.getPosition());
    Pkt4Ptr rcvd_pkt(new Pkt4(&dhcp_buf[0], dhcp_buf.size()));
    ASSERT_TRUE(rcvd_pkt);

    // Parse the packet.
    ASSERT_NO_THROW(rcvd_pkt->unpack());

    // Check if the received message is correct.
    testRcvdMessage(rcvd_pkt);
}

// This test verifies correctness of reception of the DHCP packet over
// raw socket, whereby all IP stack headers are hand-crafted.
TEST_F(PktFilterLPFTest, DISABLED_receive) {

    // Packet will be received over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterLPF pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // Send DHCPv4 message to the local loopback address and server's port.
    sendMessage();

    // Receive the packet using LPF packet filter.
    Pkt4Ptr rcvd_pkt = pkt_filter.receive(iface, sock_info_);
    // Check that the packet has been correctly received.
    ASSERT_TRUE(rcvd_pkt);

    // Parse the packet.
    ASSERT_NO_THROW(rcvd_pkt->unpack());

    // Check if the received message is correct.
    testRcvdMessage(rcvd_pkt);
}

// This test verifies that if the packet is received over the raw
// socket and its destination address doesn't match the address
// to which the socket is "bound", the packet is dropped.
TEST_F(PktFilterLPFTest, DISABLED_filterOutUnicast) {

    // Packet will be received over loopback interface.
    Iface iface(ifname_, ifindex_);
    iface.flag_loopback_ = true;
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterLPF pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // The message sent to the local loopback interface will have an
    // invalid (non-existing) destination address. The socket should
    // drop this packet.
    sendMessage(IOAddress("128.0.0.1"));

    // Perform select on the socket to make sure that the packet has
    // been dropped.

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock_info_.sockfd_, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    int result = select(sock_info_.sockfd_ + 1, &readfds, NULL, NULL, &timeout);
    ASSERT_LE(result, 0);
}

} // anonymous namespace
