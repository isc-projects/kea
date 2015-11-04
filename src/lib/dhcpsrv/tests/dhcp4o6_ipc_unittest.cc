// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/iface_mgr.h>
#include <dhcp/option_vendor.h>
#include <dhcp/pkt6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

/// @brief Test port.
const uint16_t TEST_PORT = 12345;

/// @brief Number of iterations used by the tests.
const uint16_t TEST_ITERATIONS = 10;

/// @brief Defines the DHCPv4 endpoint of IPC.
const int ENDPOINT_TYPE_V4 = 4;

/// @brief Defines the DHCPv6 endpoint of IPC.
const int ENDPOINT_TYPE_V6 = 6;

/// @brief Implements a simple IPC for the test.
class TestIpc : public  Dhcp4o6IpcBase {
public:

    /// @brief Constructor.
    ///
    /// @param port Desired port.
    /// @param endpoint_type Type of the IPC endpoint. It should be 4 or 6.
    TestIpc(const uint16_t port, const int endpoint_type);

    /// @brief Sets new port to be used with @c open.
    ///
    /// @param desired_port New desired port.
    void setDesiredPort(const uint16_t desired_port) {
        desired_port_ = desired_port;
    }

    /// @brief Opens the IPC socket and registers it in @c IfaceMgr.
    ///
    /// This method opens the IPC socket and registers it as external
    /// socket in the IfaceMgr. The @c TestIpc::receiveHandler is used as a
    /// callback to be called by the @c IfaceMgr when the data is received
    /// over the socket.
    virtual void open();

    /// @brief Retrieve port which socket is bound to.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Retrieve socket descriptor.
    int getSocketFd() const {
        return (socket_fd_);
    }

    /// @brief Pops and returns a received message.
    ///
    /// @return Pointer to the received message over the IPC.
    Pkt6Ptr popPktReceived() {
        // Copy the received message.
        Pkt6Ptr pkt_copy(pkt_received_);
        // Set the received message to NULL (pop).
        pkt_received_.reset();
        // Return the copy.
        return (pkt_copy);
    }

private:

    /// @brief Callback for the IPC socket.
    ///
    /// This callback is called by the @c IfaceMgr when the data is received
    /// over the IPC socket.
    void receiveHandler();

    /// @brief Port number.
    uint16_t desired_port_;

    /// @brief Endpoint type, i.e. 4 or 6.
    int endpoint_type_;

    /// @brief Pointer to the last received message.
    Pkt6Ptr pkt_received_;
};

TestIpc::TestIpc(const uint16_t port, const int endpoint_type)
    : desired_port_(port), endpoint_type_(endpoint_type), pkt_received_() {
}

void
TestIpc::open() {
    // Use the base IPC to open the socket.
    socket_fd_ = Dhcp4o6IpcBase::open(desired_port_, endpoint_type_);
    // If the socket has been opened correctly, register it in the @c IfaceMgr.
    if (socket_fd_ != -1) {
        IfaceMgr& iface_mgr = IfaceMgr::instance();
        iface_mgr.addExternalSocket(socket_fd_,
                                    boost::bind(&TestIpc::receiveHandler,
                                                this));
    }
}

void
TestIpc::receiveHandler() {
    pkt_received_ = receive();
}

/// @brief Test fixture class for @c Dhcp4o6IpcBase.
class Dhcp4o6IpcBaseTest : public ::testing::Test {
protected:

    /// @brief Constructor.
    ///
    /// Replaces the real configuration of interfaces with a fake configuration.
    /// The IPC uses the @c IfaceMgr to check whether the interfaces which names
    /// are carried within DHCP options exist in the system. Providing the fake
    /// configuration for the @c IfaceMgr guarantees that the configuration is
    /// consistent on any machine running the unit tests.
    Dhcp4o6IpcBaseTest();

    /// @brief Concatenates the prefix and postfix.
    ///
    /// @param prefix Prefix.
    /// @param postfix Postfix.
    /// @return String representing concatenated prefix and postfix.
    std::string concatenate(const std::string& prefix,
                            const uint16_t postfix) const;

    /// @brief Creates an instance of the DHCPv4-query Message option.
    ///
    /// @param src Type of the source endpoint. It can be 4 or 6.
    /// @return Pointer to the instance of the DHCPv4-query Message option.
    OptionPtr createDHCPv4MsgOption(const int src) const;

    /// @brief Tests sending and receiving packets over the IPC.
    ///
    /// @param iterations_num Number of packets to be sent over the IPC.
    /// @param src Type of the source IPC endpoint. It can be 4 or 6.
    /// @param dest Type of the destination IPC endpoint. It can be 4 or 6.
    void testSendReceive(const uint16_t iterations_num, const int src,
                         const int dest);

private:

    /// @brief Holds the fake configuration of the interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

Dhcp4o6IpcBaseTest::Dhcp4o6IpcBaseTest()
    : iface_mgr_test_config_(true) {
}

std::string
Dhcp4o6IpcBaseTest::concatenate(const std::string& prefix,
                                const uint16_t postfix) const {
    std::ostringstream s;
    s << prefix << postfix;
    return (s.str());
}

OptionPtr
Dhcp4o6IpcBaseTest::createDHCPv4MsgOption(const int src) const {
    // Create the DHCPv4 message.
    Pkt4Ptr pkt(new Pkt4(src == ENDPOINT_TYPE_V4 ? DHCPACK : DHCPREQUEST,
                         1234));
    // Make a wire representation of the DHCPv4 message.
    pkt->pack();
    OutputBuffer& output_buffer = pkt->getBuffer();
    const uint8_t* data = static_cast<const uint8_t*>(output_buffer.getData());
    OptionBuffer option_buffer(data, data + output_buffer.getLength());

    // Create the DHCPv4 Message option holding the created message.
    OptionPtr opt_msg(new Option(Option::V6, D6O_DHCPV4_MSG, option_buffer));
    return (opt_msg);
}


void
Dhcp4o6IpcBaseTest::testSendReceive(const uint16_t iterations_num,
                                    const int src,
                                    const int dest) {
    // Create IPC instances representing the source and destination endpoints.
    TestIpc ipc_src(TEST_PORT, src);
    TestIpc ipc_dest(TEST_PORT, dest);

    // Open the IPC on both ends.
    ASSERT_NO_THROW(ipc_src.open());
    ASSERT_NO_THROW(ipc_dest.open());

    // Depnding if we're sending from DHCPv6 to DHCPv4 or the opposite
    // direction we use different message type. This is not really required
    // for testing IPC, but it better simulates the real use case.
    uint16_t msg_type = (src == 6 ? DHCPV6_DHCPV4_QUERY :
                         DHCPV6_DHCPV4_RESPONSE);

    // Send the number of messages configured for the test.
    for (uint16_t i = 1; i <= iterations_num; ++i) {
        // Create the DHCPv4o6 message.
        Pkt6Ptr pkt(new Pkt6(msg_type, 0));

        // The interface name is carried in the dedicated option between
        // the servers. The receiving server will check that such interface
        // is present in the system. The fake configuration we're using for
        // this test includes two interfaces: "eth0" and "eth1". Therefore,
        // we pick one or another, depending on the index of the interation.
        pkt->setIface(concatenate("eth", i % 2));

        // The remote address of the sender of the DHCPv6 packet is carried
        // between the servers in the dedicated option. We use different
        // address for each iteration to make sure that the IPC delivers the
        // right address.
        pkt->setRemoteAddr(IOAddress(concatenate("2001:db8:1::", i)));

        // Add DHCPv4 Message option to make sure it is conveyed by the IPC.
        pkt->addOption(createDHCPv4MsgOption(src));

        // Actaully send the message through the IPC.
        ASSERT_NO_THROW(ipc_src.send(pkt))
            << "Failed to send the message over the IPC for iteration " << i;
    }

    // Try to receive all messages.
    for (uint16_t i = 1; i <= iterations_num; ++i) {
        // Call receive with a timeout. The data should appear on the socket
        // within this time.
        ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

        // Pop the received message.
        Pkt6Ptr pkt_received = ipc_dest.popPktReceived();
        ASSERT_TRUE(pkt_received);

        // Check that the message type is correct.
        EXPECT_EQ(msg_type, pkt_received->getType());

        // Check that the interface is correct.
        EXPECT_EQ(concatenate("eth", i % 2), pkt_received->getIface());

        // Check taht the address conveyed is correct.
        EXPECT_EQ(concatenate("2001:db8:1::", i),
                  pkt_received->getRemoteAddr().toText());

        // Check that encapsulated DHCPv4 message has been received.
        EXPECT_TRUE(pkt_received->getOption(D6O_DHCPV4_MSG));
    }
}

// This test verifies that the IPC can transmit messages between the
// DHCPv6 and DHCPv4 server.
TEST_F(Dhcp4o6IpcBaseTest, send4To6) {
    testSendReceive(TEST_ITERATIONS, ENDPOINT_TYPE_V4, ENDPOINT_TYPE_V6);
}

// This test verifies taht the IPC can transmit messages between the
// DHCPv4 and DHCPv6 server.
TEST_F(Dhcp4o6IpcBaseTest, send6To4) {
    testSendReceive(TEST_ITERATIONS, ENDPOINT_TYPE_V6, ENDPOINT_TYPE_V4);
}

// This test checks that the values of the socket descriptor are correct
// when the socket is opened and then closed.
TEST_F(Dhcp4o6IpcBaseTest, openClose) {
    TestIpc ipc(TEST_PORT, ENDPOINT_TYPE_V4);
    EXPECT_EQ(-1, ipc.getSocketFd());

    ASSERT_NO_THROW(ipc.open());
    EXPECT_NE(-1, ipc.getSocketFd());

    ASSERT_NO_THROW(ipc.close());
    EXPECT_EQ(-1, ipc.getSocketFd());
}

// This test verifies that it is call open() while the socket is already
// opened. If the port changes, the new socket should be opened.
TEST_F(Dhcp4o6IpcBaseTest, openMultipleTimes) {
   TestIpc ipc(TEST_PORT, ENDPOINT_TYPE_V6);
   ASSERT_NO_THROW(ipc.open());
   int sock_fd = ipc.getSocketFd();
   ASSERT_NE(-1, sock_fd);
   ASSERT_EQ(TEST_PORT, ipc.getPort());

   ASSERT_NO_THROW(ipc.open());
   ASSERT_EQ(sock_fd, ipc.getSocketFd());
   ASSERT_EQ(TEST_PORT, ipc.getPort());

   ipc.setDesiredPort(TEST_PORT + 10);
   ASSERT_NO_THROW(ipc.open());
   ASSERT_NE(-1, ipc.getSocketFd());

   EXPECT_EQ(TEST_PORT + 10, ipc.getPort());
}

// This test verifies that the socket remains open if there is a failure
// to open a new socket.
TEST_F(Dhcp4o6IpcBaseTest, openError) {
    TestIpc ipc(TEST_PORT, ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc.open());
    int sock_fd = ipc.getSocketFd();
    ASSERT_NE(-1, sock_fd);

    TestIpc ipc_bound(TEST_PORT + 10, ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc_bound.open());
    ASSERT_NE(-1, ipc_bound.getSocketFd());

    ipc.setDesiredPort(TEST_PORT + 10);
    ASSERT_THROW(ipc.open(), isc::Unexpected);

    EXPECT_EQ(sock_fd, ipc.getSocketFd());
    EXPECT_EQ(TEST_PORT, ipc.getPort());

    ASSERT_NO_THROW(ipc_bound.close());
    ASSERT_NO_THROW(ipc.open());
    EXPECT_NE(-1, ipc.getSocketFd());
    EXPECT_EQ(TEST_PORT + 10, ipc.getPort());
}


} // end of anonymous namespace
