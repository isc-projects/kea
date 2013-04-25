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
#include <dhcp/pkt_filter_lpf.h>
#include <dhcp/protocol_util.h>
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

/// This class handles has simple algorithm checking
/// presence of loopback interface and initializing
/// its index.
class PktFilterLPFTest : public ::testing::Test {
public:
    PktFilterLPFTest() {
        // Initialize ifname_ and ifindex_.
        loInit();
    }

    ~PktFilterLPFTest() {
        // Cleanup after each test. This guarantees
        // that the socket does not hang after a test.
        close(socket_);
    }

    /// @brief Detect loopback interface.
    ///
    /// @todo this function will be removed once cross-OS interface
    /// detection is implemented
    void loInit() {
        if (if_nametoindex("lo") > 0) {
            ifname_ = "lo";
            ifindex_ = if_nametoindex("lo");

        } else if (if_nametoindex("lo0") > 0) {
            ifname_ = "lo0";
            ifindex_ = if_nametoindex("lo0");

        } else {
            std::cout << "Failed to detect loopback interface. Neither "
                      << "lo nor lo0 worked. Giving up." << std::endl;
            FAIL();



        }
    }

    std::string ifname_; ///< Loopback interface name
    uint16_t ifindex_;   ///< Loopback interface index.
    int socket_;         ///< Socket descriptor.

};

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
    socket_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    // Check that socket has been opened.
    ASSERT_GE(socket_, 0);

    // Verify that the socket belongs to AF_PACKET family.
    sockaddr_ll sock_address;
    socklen_t sock_address_len = sizeof(sock_address);
    ASSERT_EQ(0, getsockname(socket_, reinterpret_cast<sockaddr*>(&sock_address),
                             &sock_address_len));
    EXPECT_EQ(AF_PACKET, sock_address.sll_family);

    // Verify that the socket is bound to appropriate interface.
    EXPECT_EQ(ifindex_, sock_address.sll_ifindex);

    // Verify that the socket has SOCK_RAW type.
    int sock_type;
    socklen_t sock_type_len = sizeof(sock_type);
    ASSERT_EQ(0, getsockopt(socket_, SOL_SOCKET, SO_TYPE, &sock_type, &sock_type_len));
    EXPECT_EQ(SOCK_RAW, sock_type);
}

// This test verifies correctness of sending DHCP packet through the raw
// socket, whereby all IP stack headers are hand-crafted.
TEST_F(PktFilterLPFTest, DISABLED_send) {
        // Let's create a DHCPv4 packet.
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 0));
    ASSERT_TRUE(pkt);

    // Set required fields.
    pkt->setLocalAddr(IOAddress("127.0.0.1"));
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
    PktFilterLPF pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    socket_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(socket_, 0);

    // Send the packet over the socket.
    ASSERT_NO_THROW(pkt_filter.send(iface, socket_, pkt));

    // Read the data from socket.
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket_, &readfds);
    
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int result = select(socket_ + 1, &readfds, NULL, NULL, &timeout);
    // We should receive some data from loopback interface.
    ASSERT_GT(result, 0);

    // Get the actual data.
    uint8_t rcv_buf[RECV_BUF_SIZE];
    result = recv(socket_, rcv_buf, RECV_BUF_SIZE, 0);
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

// This test verifies correctness of reception of the DHCP packet over
// raw socket, whereby all IP stack headers are hand-crafted.
TEST_F(PktFilterLPFTest, DISABLED_receive) {

    // Let's create a DHCPv4 packet.
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 0));
    ASSERT_TRUE(pkt);

    // Set required fields.
    pkt->setLocalAddr(IOAddress("127.0.0.1"));
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
    PktFilterLPF pkt_filter;
    // Open socket. We don't check that the socket has appropriate
    // options and family set because we have checked that in the
    // openSocket test already.
    socket_ = pkt_filter.openSocket(iface, addr, PORT, false, false);
    ASSERT_GE(socket_, 0);

    // Send the packet over the socket.
    ASSERT_NO_THROW(pkt_filter.send(iface, socket_, pkt));

    // Receive the packet.
    SocketInfo socket_info(socket_, IOAddress("127.0.0.1"), PORT);
    Pkt4Ptr rcvd_pkt = pkt_filter.receive(iface, socket_info);
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
