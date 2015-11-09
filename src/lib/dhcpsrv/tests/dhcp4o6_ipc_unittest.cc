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

/// @brief Defines the DHCPv4 endpoint of IPC.
const int ENDPOINT_TYPE_V4 = 4;

/// @brief Defines the DHCPv6 endpoint of IPC.
const int ENDPOINT_TYPE_V6 = 6;

/// @brief Type definition for the function creating DHCP message.
typedef boost::function<Pkt6Ptr(const uint16_t, const uint16_t)> CreateMsgFun;

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
    /// The vendor option appended to the message has ISC entprise id and
    /// comprises option @c ISC_V6_4O6_INTERFACE and @c ISC_V6_4O6_SRC_ADDRESS.
    /// This is useful to test scenarios when the IPC is forwarding messages
    /// that contain options also inserted by IPC. The duplicate options are
    /// allowed and IPC should deal with this with no error.
    ///
    /// @param msg_type Message type.
    /// @param postfix Postfix to be appended to the remote address. See the
    /// documentation of @c createDHCPv4o6Message for details.
    ///
    /// @return Pointer to the created message.
    static Pkt6Ptr createDHCPv4o6MsgWithVendorOption(const uint16_t msg_type,
                                                     const uint16_t postfix);

    /// @brief Creates an instance of the DHCPv4-query Message option.
    ///
    /// @param src Type of the source endpoint. It can be 4 or 6.
    /// @return Pointer to the instance of the DHCPv4-query Message option.
    static OptionPtr createDHCPv4MsgOption(const int src);

    /// @brief Tests sending and receiving packets over the IPC.
    ///
    /// @param iterations_num Number of packets to be sent over the IPC.
    /// @param src Type of the source IPC endpoint. It can be 4 or 6.
    /// @param dest Type of the destination IPC endpoint. It can be 4 or 6.
    void testSendReceive(const uint16_t iterations_num, const int src,
                         const int dest, const CreateMsgFun& create_msg_fun);

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
    const int src = (msg_type ==  DHCPV6_DHCPV4_QUERY) ?
        ENDPOINT_TYPE_V6 : ENDPOINT_TYPE_V4;

    // Add DHCPv4 Message option to make sure it is conveyed by the IPC.
    pkt->addOption(createDHCPv4MsgOption(src));

    return (pkt);
}

Pkt6Ptr
Dhcp4o6IpcBaseTest::createDHCPv4o6MsgWithVendorOption(const uint16_t msg_type,
                                                      const uint16_t postfix) {
    Pkt6Ptr pkt = createDHCPv4o6Message(msg_type, postfix);

    // Create vendor option with ISC enterprise id.
    OptionVendorPtr option_vendor(new OptionVendor(Option::V6, ENTERPRISE_ID_ISC));

    // Add interface. Such interface doesn't have to exist in the system because
    // IPC should not use this option when it is received. It should rather use
    // the option that the sender side is appending to the message.
    option_vendor->addOption(OptionStringPtr(new OptionString(Option::V6,
                                                              ISC_V6_4O6_INTERFACE,
                                                              "non-existing")));
    // Add some remote address.
    option_vendor->addOption(Option6AddrLstPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                                                  IOAddress("3000::10"))));
    // Add vendor option to the message.
    pkt->addOption(option_vendor);

    return (pkt);
}



OptionPtr
Dhcp4o6IpcBaseTest::createDHCPv4MsgOption(const int src) {
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
                                    const int src, const int dest,
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
    uint16_t msg_type = (src == 6 ? DHCPV6_DHCPV4_QUERY :
                         DHCPV6_DHCPV4_RESPONSE);

    // Send the number of messages configured for the test.
    for (uint16_t i = 1; i <= iterations_num; ++i) {
        // Create the DHCPv4o6 message.
        Pkt6Ptr pkt = create_msg_fun(msg_type, i);

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

void
Dhcp4o6IpcBaseTest::testReceiveError(const Pkt6Ptr& pkt) {
    TestIpc ipc_src(TEST_PORT, ENDPOINT_TYPE_V6);
    TestIpc ipc_dest(TEST_PORT, ENDPOINT_TYPE_V4);

    // Open the IPC on both ends.
    ASSERT_NO_THROW(ipc_src.open());
    ASSERT_NO_THROW(ipc_dest.open());

    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::1"));
    pkt->addOption(createDHCPv4MsgOption(ENDPOINT_TYPE_V6));

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
// DHCPv6 and DHCPv4 server.
TEST_F(Dhcp4o6IpcBaseTest, send4To6) {
    testSendReceive(TEST_ITERATIONS, ENDPOINT_TYPE_V4, ENDPOINT_TYPE_V6,
                    &createDHCPv4o6Message);
}

// This test verifies taht the IPC can transmit messages between the
// DHCPv4 and DHCPv6 server.
TEST_F(Dhcp4o6IpcBaseTest, send6To4) {
    testSendReceive(TEST_ITERATIONS, ENDPOINT_TYPE_V6, ENDPOINT_TYPE_V4,
                    &createDHCPv4o6Message);
}

TEST_F(Dhcp4o6IpcBaseTest, send6To4WithVendorOption) {
    testSendReceive(TEST_ITERATIONS, ENDPOINT_TYPE_V6, ENDPOINT_TYPE_V4,
                    &createDHCPv4o6MsgWithVendorOption);
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
    ASSERT_THROW(ipc.open(), isc::dhcp::Dhcp4o6IpcError);

    EXPECT_EQ(sock_fd, ipc.getSocketFd());
    EXPECT_EQ(TEST_PORT, ipc.getPort());

    ASSERT_NO_THROW(ipc_bound.close());
    ASSERT_NO_THROW(ipc.open());
    EXPECT_NE(-1, ipc.getSocketFd());
    EXPECT_EQ(TEST_PORT + 10, ipc.getPort());
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
    TestIpc ipc(TEST_PORT, ENDPOINT_TYPE_V4);
    ASSERT_NO_THROW(ipc.open());

    // NULL message.
    EXPECT_THROW(ipc.send(Pkt6Ptr()), Dhcp4o6IpcError);
}

// This test verifies that send method throws exception when the IPC
// socket is not opened.
TEST_F(Dhcp4o6IpcBaseTest, sendOverClosedSocket) {
    TestIpc ipc(TEST_PORT, ENDPOINT_TYPE_V4);

    // Create a message.
    Pkt6Ptr pkt(createDHCPv4o6Message(DHCPV6_DHCPV4_QUERY));

    // Sending over the closed socket should fail.
    EXPECT_THROW(ipc.send(pkt), Dhcp4o6IpcError);
}

// This test verifies that send method throws exception when the IPC
// socket has been unexpectedly closed.
TEST_F(Dhcp4o6IpcBaseTest, sendOverUnexpectedlyClosedSocket) {
    TestIpc ipc(TEST_PORT, ENDPOINT_TYPE_V4);
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
