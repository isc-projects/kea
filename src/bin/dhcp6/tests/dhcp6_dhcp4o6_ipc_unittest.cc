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
#include <asiolink/io_address.h>
#include <dhcp/pkt6.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_filter6_test_stub.h>
#include <dhcp6/dhcp6_dhcp4o6_ipc.h>
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
class Dhcp6to4IpcTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// Configures IPC to use a test port. It also provides a fake
    /// configuration of interfaces and opens IPv6 sockets.
    Dhcp6to4IpcTest()
        : iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets6();
        configurePort(TEST_PORT);
    }

    /// @brief Configure DHCP4o6 port.
    ///
    /// @param port New port.
    void configurePort(const uint16_t port);

    /// @brief Creates an instance of the DHCPv4o6 Message option.
    ///
    /// @return Pointer to the instance of the DHCPv4-query Message option.
    OptionPtr createDHCPv4MsgOption() const;

private:

    /// @brief Provides fake configuration of interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

void
Dhcp6to4IpcTest::configurePort(const uint16_t port) {
    CfgMgr::instance().getStagingCfg()->setDhcp4o6Port(port);
}

OptionPtr
Dhcp6to4IpcTest::createDHCPv4MsgOption() const {
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

// This test verifies that the DHCPv4 endpoint of the DHCPv4o6 IPC can
// receive messages.
TEST_F(Dhcp6to4IpcTest, receive) {
    // Create instance of the IPC endpoint under test.
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);

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


    // The stub packet filter exposes static function to retrieve messages
    // sent over the fake sockets/interfaces. This is the message that the
    // IPC endpoint should forward to the client after receiving it
    // from the DHCPv4 server.
    Pkt6Ptr forwarded = PktFilter6TestStub::popSent();
    ASSERT_TRUE(forwarded);

    // Verify the packet received.
    EXPECT_EQ(DHCP6_CLIENT_PORT, forwarded->getRemotePort());
    EXPECT_EQ(forwarded->getType(), pkt->getType());
    EXPECT_TRUE(forwarded->getOption(D6O_DHCPV4_MSG));
    EXPECT_EQ("eth0", forwarded->getIface());
    EXPECT_EQ("2001:db8:1::123", forwarded->getRemoteAddr().toText());
}

} // end of anonymous namespace
