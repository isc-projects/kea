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
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <dhcpsrv/testutils/dhcp4o6_test_ipc.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
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

/// @brief Type definition for the function creating DHCP message.
typedef boost::function<Pkt6Ptr(const uint16_t, const uint16_t)> CreateMsgFun;

/// @brief Define short name for test IPC class.
typedef Dhcp4o6TestIpc TestIpc;

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
    static std::string concatenate(const std::string& prefix, const uint16_t postfix);

    /// @brief Creates an instance of the DHCPv4o6 message.
    ////
    /// @param msg_type Message type.
    /// @param postfix Postfix to be appended to the remote address. For example,
    /// for postfix = 5 the resulting remote address will be 2001:db8:1::5.
    /// The postifx value is also used to generate the postfix for the interface.
    /// The possible interface names are "eth0" and "eth1". For even postfix values
    /// the "eth0" will be used, for odd postfix values "eth1" will be used.
    ///
    /// @return Pointer to the created message.
    static Pkt6Ptr createDHCPv4o6Message(const uint16_t msg_type,
                                         const uint16_t postfix = 0);

    /// @brief Creates an instance of the DHCPv4o6 message with vendor option.
    ///
    /// @param msg_type Message type.
    /// @param postfix Postfix to be appended to the remote address. See the
    /// documentation of @c createDHCPv4o6Message for details.
    ///
    /// @return Pointer to the created message.
    static Pkt6Ptr createDHCPv4o6MsgWithVendorOption(const uint16_t msg_type,
                                                     const uint16_t postfix,
                                                     const uint32_t enterprise_id);

    /// @brief Creates an instance of the DHCPv4o6 message with ISC
    /// vendor option.
    ///
    /// This is useful to test scenarios when the IPC is forwarding messages
    /// that contain vendor option with ISC enterprise ID.
    ///
    /// @param msg_type Message type.
    /// @param postfix Postfix to be appended to the remote address. See the
    /// documentation of @c createDHCPv4o6Message for details.
    ///
    /// @return Pointer to the created message.
    static Pkt6Ptr createDHCPv4o6MsgWithISCVendorOption(const uint16_t msg_type,
                                                        const uint16_t postfix);

    /// @brief Creates an instance of the DHCPv4o6 message with vendor
    /// option holding enterprise id of 32000.
    ///
    /// This is useful to test scenarios when the IPC is forwarding messages
    /// that contain some vendor option and when IPC also appends the ISC
    /// vendor option to carry some DHCPv4o6 specific information.
    ///
    /// @param msg_type Message type.
    /// @param postfix Postfix to be appended to the remote address. See the
    /// documentation of @c createDHCPv4o6Message for details.
    ///
    /// @return Pointer to the created message.
    static Pkt6Ptr createDHCPv4o6MsgWithAnyVendorOption(const uint16_t msg_type,
                                                        const uint16_t postfix);

    /// @brief Creates an instance of the DHCPv4o6 Message option.
    ///
    /// @param src Type of the source endpoint. It can be 4 or 6.
    /// @return Pointer to the instance of the option.
    static OptionPtr createDHCPv4MsgOption(const TestIpc::EndpointType& src);

    /// @brief Tests sending and receiving packets over the IPC.
    ///
    /// @param iterations_num Number of packets to be sent over the IPC.
    /// @param src Type of the source IPC endpoint. It can be 4 or 6.
    /// @param dest Type of the destination IPC endpoint. It can be 4 or 6.
    void testSendReceive(const uint16_t iterations_num,
                         const TestIpc::EndpointType& src,
                         const TestIpc::EndpointType& dest,
                         const CreateMsgFun& create_msg_fun);

    /// @brief Tests that error is reported when invalid message is received.
    ///
    /// @param pkt Pointer to the invalid message.
    void testReceiveError(const Pkt6Ptr& pkt);

private:

    /// @brief Holds the fake configuration of the interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

Dhcp4o6IpcBaseTest::Dhcp4o6IpcBaseTest()
    : iface_mgr_test_config_(true) {
}

std::string
Dhcp4o6IpcBaseTest::concatenate(const std::string& prefix,
                                const uint16_t postfix) {
    std::ostringstream s;
    s << prefix << postfix;
    return (s.str());
}

Pkt6Ptr
Dhcp4o6IpcBaseTest::createDHCPv4o6Message(const uint16_t msg_type,
                                          const uint16_t postfix) {
    // Create the DHCPv4o6 message.
    Pkt6Ptr pkt(new Pkt6(msg_type, 0));

    // The interface name is carried in the dedicated option between
    // the servers. The receiving server will check that such interface
    // is present in the system. The fake configuration we're using for
    // this test includes two interfaces: "eth0" and "eth1". Therefore,
    // we pick one or another, depending on the index of the interation.
    pkt->setIface(concatenate("eth", postfix % 2));

    // The remote address of the sender of the DHCPv6 packet is carried
    // between the servers in the dedicated option. We use different
    // address for each iteration to make sure that the IPC delivers the
    // right address.
    pkt->setRemoteAddr(IOAddress(concatenate("2001:db8:1::", postfix)));

    // Determine the endpoint type using the message type.
    const TestIpc::EndpointType src = (msg_type ==  DHCPV6_DHCPV4_QUERY) ?
        TestIpc::ENDPOINT_TYPE_V6 : TestIpc::ENDPOINT_TYPE_V4;

    // Add DHCPv4 Message option to make sure it is conveyed by the IPC.
    pkt->addOption(createDHCPv4MsgOption(src));

    return (pkt);
}

Pkt6Ptr
Dhcp4o6IpcBaseTest::createDHCPv4o6MsgWithVendorOption(const uint16_t msg_type,
                                                      const uint16_t postfix,
                                                      const uint32_t enterprise_id) {
    Pkt6Ptr pkt = createDHCPv4o6Message(msg_type, postfix);

    // Create vendor option with ISC enterprise id.
    OptionVendorPtr option_vendor(new OptionVendor(Option::V6, enterprise_id));

    // Add some option to the vendor option.
    option_vendor->addOption(OptionPtr(new Option(Option::V6, 100)));

    // Add vendor option to the message.
    pkt->addOption(option_vendor);

    return (pkt);
}

Pkt6Ptr
Dhcp4o6IpcBaseTest::createDHCPv4o6MsgWithISCVendorOption(const uint16_t msg_type,
                                                         const uint16_t postfix) {
    return (createDHCPv4o6MsgWithVendorOption(msg_type, postfix, ENTERPRISE_ID_ISC));
}

Pkt6Ptr
Dhcp4o6IpcBaseTest::createDHCPv4o6MsgWithAnyVendorOption(const uint16_t msg_type,
                                                         const uint16_t postfix) {
    return (createDHCPv4o6MsgWithVendorOption(msg_type, postfix, 32000));
}

OptionPtr
Dhcp4o6IpcBaseTest::createDHCPv4MsgOption(const TestIpc::EndpointType& src) {
    // Create the DHCPv4 message.
    Pkt4Ptr pkt(new Pkt4(src == TestIpc::ENDPOINT_TYPE_V4 ? DHCPACK : DHCPREQUEST,
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
                                    const TestIpc::EndpointType& src,
                                    const TestIpc::EndpointType& dest,
                                    const CreateMsgFun& create_msg_fun) {
    // Create IPC instances representing the source and destination endpoints.
    TestIpc ipc_src(TEST_PORT, src);
    TestIpc ipc_dest(TEST_PORT, dest);

    // Open the IPC on both ends.
    ASSERT_NO_THROW(ipc_src.open());
    ASSERT_NO_THROW(ipc_dest.open());

    // Depnding if we're sending from DHCPv6 to DHCPv4 or the opposite
    // direction we use different message type. This is not really required
    // for testing IPC, but it better simulates the real use case.
    uint16_t msg_type = (src == TestIpc::ENDPOINT_TYPE_V6 ? DHCPV6_DHCPV4_QUERY :
                         DHCPV6_DHCPV4_RESPONSE);

    std::vector<bool> has_vendor_option;

    // Send the number of messages configured for the test.
    for (uint16_t i = 1; i <= iterations_num; ++i) {
        // Create the DHCPv4o6 message.
        Pkt6Ptr pkt = create_msg_fun(msg_type, i);

        // Remember if the vendor option exists in the source packet. The
        // received packet should also contain this option if it exists
        // in the source packet.
        has_vendor_option.push_back(static_cast<bool>(pkt->getOption(D6O_VENDOR_OPTS)));

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

        if (has_vendor_option[i - 1]) {
            // Make sure that the vendor option wasn't deleted when the packet was
            // received.
            OptionPtr option_vendor = pkt_received->getOption(D6O_VENDOR_OPTS);
            ASSERT_TRUE(option_vendor)
                << "vendor option deleted in the received DHCPv4o6 packet for"
                " iteration " << i;

            // ISC_V6_4O6_INTERFACE shouldn't be present.
            EXPECT_FALSE(option_vendor->getOption(ISC_V6_4O6_INTERFACE));

            // ISC_V6_4O6_SRC_ADDRESS shouldn't be present.
            EXPECT_FALSE(option_vendor->getOption(ISC_V6_4O6_SRC_ADDRESS));

        } else {
            EXPECT_FALSE(pkt_received->getOption(D6O_VENDOR_OPTS));
        }
    }
}

void
Dhcp4o6IpcBaseTest::testReceiveError(const Pkt6Ptr& pkt) {
    TestIpc ipc_src(TEST_PORT, TestIpc::ENDPOINT_TYPE_V6);
    TestIpc ipc_dest(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);

    // Open the IPC on both ends.
    ASSERT_NO_THROW(ipc_src.open());
    ASSERT_NO_THROW(ipc_dest.open());

    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::1"));
    pkt->addOption(createDHCPv4MsgOption(TestIpc::ENDPOINT_TYPE_V6));

    OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    ASSERT_NO_THROW(pkt->pack());

    ASSERT_NE(-1, ::send(ipc_src.getSocketFd(), buf.getData(),
                         buf.getLength(), 0));

    // Call receive with a timeout. The data should appear on the socket
    // within this time.
    ASSERT_THROW(IfaceMgr::instance().receive6(1, 0), Dhcp4o6IpcError);
}


// This test verifies that the IPC can transmit messages between the
// DHCPv4 and DHCPv6 server.
TEST_F(Dhcp4o6IpcBaseTest, send4To6) {
    testSendReceive(TEST_ITERATIONS, TestIpc::ENDPOINT_TYPE_V4,
                    TestIpc::ENDPOINT_TYPE_V6, &createDHCPv4o6Message);
}

// This test verifies that the IPC can transmit messages between the
// DHCPv6 and DHCPv4 server.
TEST_F(Dhcp4o6IpcBaseTest, send6To4) {
    testSendReceive(TEST_ITERATIONS, TestIpc::ENDPOINT_TYPE_V6,
                    TestIpc::ENDPOINT_TYPE_V4, &createDHCPv4o6Message);
}

// This test verifies that the IPC will transmit message already containing
// vendor option with ISC enterprise ID, between the DHCPv6 and DHCPv4
// server.
TEST_F(Dhcp4o6IpcBaseTest, send6To4WithISCVendorOption) {
    testSendReceive(TEST_ITERATIONS, TestIpc::ENDPOINT_TYPE_V6,
                    TestIpc::ENDPOINT_TYPE_V4,
                    &createDHCPv4o6MsgWithISCVendorOption);
}

// This test verifies that the IPC will transmit message already containing
// vendor option with ISC enterprise ID, between the DHCPv6 and DHCPv4
// server.
TEST_F(Dhcp4o6IpcBaseTest, send4To6WithISCVendorOption) {
    testSendReceive(TEST_ITERATIONS, TestIpc::ENDPOINT_TYPE_V4,
                    TestIpc::ENDPOINT_TYPE_V6,
                    &createDHCPv4o6MsgWithISCVendorOption);
}

// This test verifies that the IPC will transmit message already containing
// vendor option with enterprise id different than ISC, between the DHCPv6
// and DHCPv4 server.
TEST_F(Dhcp4o6IpcBaseTest, send6To4WithAnyVendorOption) {
    testSendReceive(TEST_ITERATIONS, TestIpc::ENDPOINT_TYPE_V6,
                    TestIpc::ENDPOINT_TYPE_V4,
                    &createDHCPv4o6MsgWithAnyVendorOption);
}

// This test verifies that the IPC will transmit message already containing
// vendor option with enterprise id different than ISC, between the DHCPv4
// and DHCPv6 server.
TEST_F(Dhcp4o6IpcBaseTest, send4To6WithAnyVendorOption) {
    testSendReceive(TEST_ITERATIONS, TestIpc::ENDPOINT_TYPE_V4,
                    TestIpc::ENDPOINT_TYPE_V6,
                    &createDHCPv4o6MsgWithAnyVendorOption);
}

// This test checks that the values of the socket descriptor are correct
// when the socket is opened and then closed.
TEST_F(Dhcp4o6IpcBaseTest, openClose) {
    TestIpc ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);
    EXPECT_EQ(-1, ipc.getSocketFd());

    ASSERT_NO_THROW(ipc.open());
    EXPECT_NE(-1, ipc.getSocketFd());

    ASSERT_NO_THROW(ipc.close());
    EXPECT_EQ(-1, ipc.getSocketFd());
}

// This test verifies that it is call open() while the socket is already
// opened. If the port changes, the new socket should be opened.
TEST_F(Dhcp4o6IpcBaseTest, openMultipleTimes) {
   TestIpc ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V6);
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
    TestIpc ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc.open());
    int sock_fd = ipc.getSocketFd();
    ASSERT_NE(-1, sock_fd);

    TestIpc ipc_bound(TEST_PORT + 10, TestIpc::ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc_bound.open());
    ASSERT_NE(-1, ipc_bound.getSocketFd());

    ipc.setDesiredPort(TEST_PORT + 10);
    ASSERT_THROW(ipc.open(), isc::dhcp::Dhcp4o6IpcError);

    EXPECT_EQ(sock_fd, ipc.getSocketFd());
    EXPECT_EQ(TEST_PORT, ipc.getPort());

    ASSERT_NO_THROW(ipc_bound.close());
    ASSERT_NO_THROW(ipc.open());
    EXPECT_NE(-1, ipc.getSocketFd());
    EXPECT_EQ(TEST_PORT + 10, ipc.getPort());
}

// This test verifies that the IPC returns an error when trying to bind
// to the out of range port.
TEST_F(Dhcp4o6IpcBaseTest, invalidPortError4) {
    TestIpc ipc(65535, TestIpc::ENDPOINT_TYPE_V4);
    EXPECT_THROW(ipc.open(), Dhcp4o6IpcError);
}

// This test verifies that the IPC returns an error when trying to bind
// to the out of range port.
TEST_F(Dhcp4o6IpcBaseTest, invalidPortError6) {
    TestIpc ipc(65535, TestIpc::ENDPOINT_TYPE_V6);
    EXPECT_THROW(ipc.open(), Dhcp4o6IpcError);
}

// This test verifies that receiving packet over the IPC fails when there
// is no vendor option present.
TEST_F(Dhcp4o6IpcBaseTest, receiveWithoutVendorOption) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 0));
    testReceiveError(pkt);
}

// This test verifies that receving packet over the IPC fails when the
// enterprise ID carried in the vendor option is invalid.
TEST_F(Dhcp4o6IpcBaseTest, receiveInvalidEnterpriseId) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 0));
    OptionVendorPtr option_vendor(new OptionVendor(Option::V6, 1));
    option_vendor->addOption(
        OptionStringPtr(new OptionString(Option::V6, ISC_V6_4O6_INTERFACE,
                                         "eth0")));
    option_vendor->addOption(
        Option6AddrLstPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                             IOAddress("2001:db8:1::1")))
    );

    pkt->addOption(option_vendor);
    testReceiveError(pkt);
}

// This test verifies that receiving packet over the IPC fails when the
// interface option is not present.
TEST_F(Dhcp4o6IpcBaseTest, receiveWithoutInterfaceOption) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 0));
    OptionVendorPtr option_vendor(new OptionVendor(Option::V6,
                                                   ENTERPRISE_ID_ISC));
    option_vendor->addOption(
        Option6AddrLstPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                             IOAddress("2001:db8:1::1")))
    );

    pkt->addOption(option_vendor);
    testReceiveError(pkt);
}

// This test verifies that receiving packet over the IPC fails when the
// interface which name is carried in the option is not present in the
// system.
TEST_F(Dhcp4o6IpcBaseTest, receiveWithInvalidInterface) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 0));
    OptionVendorPtr option_vendor(new OptionVendor(Option::V6,
                                                   ENTERPRISE_ID_ISC));
    option_vendor->addOption(
        OptionStringPtr(new OptionString(Option::V6, ISC_V6_4O6_INTERFACE,
                                         "ethX")));
    option_vendor->addOption(
        Option6AddrLstPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                             IOAddress("2001:db8:1::1")))
    );

    pkt->addOption(option_vendor);
    testReceiveError(pkt);
}


// This test verifies that receving packet over the IPC fails when the
// source address option is not present.
TEST_F(Dhcp4o6IpcBaseTest, receiveWithoutSourceAddressOption) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 0));
    OptionVendorPtr option_vendor(new OptionVendor(Option::V6,
                                                   ENTERPRISE_ID_ISC));
    option_vendor->addOption(
        OptionStringPtr(new OptionString(Option::V6, ISC_V6_4O6_INTERFACE,
                                         "eth0")));

    pkt->addOption(option_vendor);
    testReceiveError(pkt);
}

// This test verifies that send method throws exception when the packet
// is NULL.
TEST_F(Dhcp4o6IpcBaseTest, sendNullMessage) {
    TestIpc ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc.open());

    // NULL message.
    EXPECT_THROW(ipc.send(Pkt6Ptr()), Dhcp4o6IpcError);
}

// This test verifies that send method throws exception when the IPC
// socket is not opened.
TEST_F(Dhcp4o6IpcBaseTest, sendOverClosedSocket) {
    TestIpc ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);

    // Create a message.
    Pkt6Ptr pkt(createDHCPv4o6Message(DHCPV6_DHCPV4_QUERY));

    // Sending over the closed socket should fail.
    EXPECT_THROW(ipc.send(pkt), Dhcp4o6IpcError);
}

// This test verifies that send method throws exception when the IPC
// socket has been unexpectedly closed.
TEST_F(Dhcp4o6IpcBaseTest, sendOverUnexpectedlyClosedSocket) {
    TestIpc ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc.open());

    // Close the socket behind the scenes. The IPC doesn't know that the
    // socket has been closed and it still holds the descriptor.
    ::close(ipc.getSocketFd());

    // Create a message.
    Pkt6Ptr pkt(createDHCPv4o6Message(DHCPV6_DHCPV4_QUERY));

    // Sending over the closed socket should fail.
    EXPECT_THROW(ipc.send(pkt), Dhcp4o6IpcError);
}

} // end of anonymous namespace
