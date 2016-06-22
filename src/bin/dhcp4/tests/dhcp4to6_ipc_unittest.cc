// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/pkt4o6.h>
#include <dhcp/pkt6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/dhcp4to6_ipc.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/testutils/dhcp4o6_test_ipc.h>
#include <gtest/gtest.h>
#include <stdint.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

/// @brief Port number used in tests.
const uint16_t TEST_PORT = 32000;

/// @brief Define short name for the test IPC.
typedef Dhcp4o6TestIpc TestIpc;

/// @brief Test fixture class for DHCPv4 endpoint of DHCPv4o6 IPC.
class Dhcp4to6IpcTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// Configures IPC to use a test port. It also provides a fake
    /// configuration of interfaces.
    Dhcp4to6IpcTest()
        : iface_mgr_test_config_(true) {
        configurePort(TEST_PORT);
    }

    /// @brief Configure DHCP4o6 port.
    ///
    /// @param port New port.
    void configurePort(uint16_t port);

    /// @brief Creates an instance of the DHCPv4o6 Message option.
    ///
    /// The option will contain an empty DHCPREQUEST message, with
    /// just the Message Type option inside and nothing else.
    ///
    /// @return Pointer to the instance of the DHCPv4-query Message option.
    OptionPtr createDHCPv4MsgOption() const;

private:

    /// @brief Provides fake configuration of interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

void
Dhcp4to6IpcTest::configurePort(uint16_t port) {
    CfgMgr::instance().getStagingCfg()->setDhcp4o6Port(port);
}

OptionPtr
Dhcp4to6IpcTest::createDHCPv4MsgOption() const {
    // Create the DHCPv4 message.
    Pkt4Ptr pkt(new Pkt4(DHCPREQUEST, 1234));
    // Make a wire representation of the DHCPv4 message.
    pkt->pack();
    OutputBuffer& output_buffer = pkt->getBuffer();
    const uint8_t* data = static_cast<const uint8_t*>(output_buffer.getData());
    OptionBuffer option_buffer(data, data + output_buffer.getLength());

    // Create the DHCPv4 Message option holding the created message.
    OptionPtr opt_msg(new Option(Option::V6, D6O_DHCPV4_MSG, option_buffer));
    return (opt_msg);
}

// This test verifies that the IPC returns an error when trying to bind
// to the out of range port.
TEST_F(Dhcp4to6IpcTest, invalidPortError) {
    // Create instance of the IPC endpoint under test with out-of-range port.
    configurePort(65535);
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();
    EXPECT_THROW(ipc.open(), isc::OutOfRange);
}

// This test verifies that the DHCPv4 endpoint of the DHCPv4o6 IPC can
// receive messages.
TEST_F(Dhcp4to6IpcTest, receive) {
    // Create instance of the IPC endpoint under test.
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V6);

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Create message to be sent over IPC.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 1234));
    pkt->addOption(createDHCPv4MsgOption());
    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // Make sure that the message has been received.
    Pkt4o6Ptr pkt_received = ipc.getReceived();
    ASSERT_TRUE(pkt_received);
    Pkt6Ptr pkt6_received = pkt_received->getPkt6();
    ASSERT_TRUE(pkt6_received);
    EXPECT_EQ("eth0", pkt6_received->getIface());
    EXPECT_EQ("2001:db8:1::123", pkt6_received->getRemoteAddr().toText());
}

// This test verifies that message with multiple DHCPv4 query options
// is rejected.
TEST_F(Dhcp4to6IpcTest, receiveMultipleQueries) {
    // Create instance of the IPC endpoint under test.
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V6);

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Create message to be sent over IPC.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 1234));
    // Add two DHCPv4 query options.
    pkt->addOption(createDHCPv4MsgOption());
    pkt->addOption(createDHCPv4MsgOption());
    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Send message.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    // Reception handler should throw exception.
    EXPECT_THROW(IfaceMgr::instance().receive6(1, 0), Dhcp4o6IpcError);
}

// This test verifies that message with no DHCPv4 query options is rejected.
TEST_F(Dhcp4to6IpcTest, receiveNoQueries) {
    // Create instance of the IPC endpoint under test.
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V6);

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Create message to be sent over IPC without DHCPv4 query option.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 1234));
    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Send message.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    // Reception handler should throw exception.
    EXPECT_THROW(IfaceMgr::instance().receive6(1, 0), Dhcp4o6IpcError);
}

} // end of anonymous namespace
