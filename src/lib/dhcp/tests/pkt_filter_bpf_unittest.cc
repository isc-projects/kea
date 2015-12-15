// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_bpf.h>
#include <dhcp/protocol_util.h>
#include <dhcp/tests/pkt_filter_test_utils.h>
#include <util/buffer.h>

#include <gtest/gtest.h>

#include <net/bpf.h>
#include <sys/socket.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// Port number used by tests.
const uint16_t PORT = 10067;
/// Size of the buffer holding received packets.
const size_t RECV_BUF_SIZE = 4096;

// Test fixture class inherits from the class common for all packet
// filter tests.
class PktFilterBPFTest : public isc::dhcp::test::PktFilterTest {
public:
    PktFilterBPFTest() : PktFilterTest(PORT) {
    }
};

// This test verifies that the PktFilterBPF class reports its capability
// to send packets to the host having no IP address assigned.
TEST_F(PktFilterBPFTest, isDirectResponseSupported) {
    // Create object under test.
    PktFilterBPF pkt_filter;
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
// variable to "PktFilterBPFTest.*" apart from GTEST_ALSO_RUN_DISABLED_TESTS
// setting.

// This test verifies that the raw AF_PACKET family socket can
// be opened and bound to the specific interface.
TEST_F(PktFilterBPFTest, DISABLED_openSocket) {
    // Create object representing loopback interface.
    Iface iface(ifname_, ifindex_);
    iface.flag_loopback_ = true;
    // Set loopback address.
    IOAddress addr("127.0.0.1");

    // Try to open socket.
    PktFilterBPF pkt_filter;
    ASSERT_NO_THROW(
        sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    );

    // Check that the primary socket has been opened.
    ASSERT_GE(sock_info_.sockfd_, 0);
    // Check that the fallback socket has been opened too.
    ASSERT_GE(sock_info_.fallbackfd_, 0);
}

// This test verifies correctness of sending DHCP packet through the BPF
// device attached to local loopback interface. Note that this is not exactly
// the same as sending over the hardware interface (e.g. ethernet) because the
// packet format is different on local loopback interface when using the
// BPF. The key difference is that the pseudo header containing address
// family is sent instead of link-layer header. Ideally we would run this
// test over the real interface but since we don't know what interfaces
// are present in the particular system we have to stick to local loopback
// interface as this one is almost always present.
TEST_F(PktFilterBPFTest, DISABLED_send) {
    // Packet will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    iface.flag_loopback_ = true;
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterBPF pkt_filter;

    // Open BPF device.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    // Returned descriptor must not be negative. 0 is valid.
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

    /// Get the actual data.
    uint8_t rcv_buf[RECV_BUF_SIZE];
    result = read(sock_info_.sockfd_, rcv_buf, RECV_BUF_SIZE);
    ASSERT_GT(result, 0);

    // Each packet is prepended with the BPF header structure. We have to
    // parse this structure to locate the position of the address family
    // pseudo header.
    struct bpf_hdr bpfh;
    memcpy(static_cast<void*>(&bpfh), static_cast<void*>(rcv_buf),
           sizeof(bpf_hdr));
    // bh_hdrlen contains the total length of the BPF header, including
    // alignment. We will use this value to skip over the BPF header and
    // parse the contents of the packet that we are interested in.
    uint32_t bpfh_len = bpfh.bh_hdrlen;
    // Address Family pseudo header contains the address family of the
    // packet (used for local loopback interface instead of the link-layer
    // header such as ethernet frame header).
    uint32_t af = 0;
    memcpy(static_cast<void*>(&af),
           static_cast<void*>(rcv_buf + bpfh_len), 4);
    // Check the value in the pseudo header. If this is incorrect, something
    // is really broken, so let's exit.
    ASSERT_EQ(AF_INET, af);

    Pkt4Ptr dummy_pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 0));
    // Create the input buffer from the reminder of the packet. This should
    // only contain the IP/UDP headers and the DHCP message.
    InputBuffer buf(rcv_buf + bpfh_len + 4, result - bpfh_len - 4);
    ASSERT_GE(buf.getLength(), test_message_->len());

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
TEST_F(PktFilterBPFTest, DISABLED_receive) {

    // Packet will be received over loopback interface.
    Iface iface(ifname_, ifindex_);
    iface.flag_loopback_ = true;
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterBPF pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    sock_info_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(sock_info_.sockfd_, 0);

    // Send DHCPv4 message to the local loopback address and server's port.
    sendMessage();

    // Receive the packet using LPF packet filter.
    Pkt4Ptr rcvd_pkt;
    ASSERT_NO_THROW(rcvd_pkt = pkt_filter.receive(iface, sock_info_));
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
TEST_F(PktFilterBPFTest, DISABLED_filterOutUnicast) {

    // Packet will be received over loopback interface.
    Iface iface(ifname_, ifindex_);
    iface.flag_loopback_ = true;
    IOAddress addr("127.0.0.1");

    // Create an instance of the class which we are testing.
    PktFilterBPF pkt_filter;
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
