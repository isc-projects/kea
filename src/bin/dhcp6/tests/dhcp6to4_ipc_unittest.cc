// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/pkt6.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_filter6_test_stub.h>
#include <dhcp6/dhcp6to4_ipc.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/testutils/dhcp4o6_test_ipc.h>
#include <stats/stats_mgr.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <hooks/library_handle.h>

#include <gtest/gtest.h>
#include <stdint.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;
using namespace isc::hooks;
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
        // Install buffer6_send_callout
        EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().
                        registerCallout("buffer6_send", buffer6_send_callout));
        // Let's wipe all existing statistics.
        StatsMgr::instance().removeAll();

        // Reset the flag which we expect to be set in the callout.
        callback_pkt_options_copy_ = false;
    }

    /// @brief Configure DHCP4o6 port.
    ///
    /// @param port New port.
    void configurePort(const uint16_t port);

    /// @brief Creates an instance of the DHCPv4o6 Message option.
    ///
    /// The option will contain an empty DHCPREQUEST message, with
    /// just the Message Type option inside and nothing else.
    ///
    /// @return Pointer to the instance of the DHCPv4-query Message option.
    OptionPtr createDHCPv4MsgOption() const;

    /// @brief Handler for the buffer6_send hook
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_send_callout(CalloutHandle& callout_handle) {
        callout_handle.getArgument("response6", callback_pkt_);
        if (callback_pkt_) {
            callback_pkt_options_copy_ = callback_pkt_->isCopyRetrievedOptions();
        }
        return (0);
    }

    /// @brief Response Pkt6 shared pointer returned in the callout
    static Pkt6Ptr callback_pkt_;

    /// Flag indicating if copying retrieved options was enabled for
    /// a received packet during callout execution.
    static bool callback_pkt_options_copy_;

private:

    /// @brief Provides fake configuration of interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

Pkt6Ptr Dhcp6to4IpcTest::callback_pkt_;
bool Dhcp6to4IpcTest::callback_pkt_options_copy_;

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

// This test verifies that the IPC returns an error when trying to bind
// to the out of range port.
TEST_F(Dhcp6to4IpcTest, invalidPortError) {
    // Create instance of the IPC endpoint under test with out-of-range port.
    configurePort(65535);
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();
    EXPECT_THROW(ipc.open(), isc::OutOfRange);
}

// This test verifies that the DHCPv4 endpoint of the DHCPv4o6 IPC can
// receive messages.
TEST_F(Dhcp6to4IpcTest, receive) {
    // Create instance of the IPC endpoint under test.
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);

    // Reset the IPC.
    ASSERT_NO_THROW(ipc.close());

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Get statistics
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt6_snd = mgr.getObservation("pkt6-sent");
    ObservationPtr d4_resp = mgr.getObservation("pkt6-dhcpv4-response-sent");
    EXPECT_FALSE(pkt6_snd);
    EXPECT_FALSE(d4_resp);

    // Create message to be sent over IPC.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_RESPONSE, 1234));
    pkt->addOption(createDHCPv4MsgOption());
    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the callout cached packet
    Dhcp6to4IpcTest::callback_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // Make sure that the received packet was configured to return copy of
    // retrieved options within a callout.
    EXPECT_TRUE(callback_pkt_options_copy_);

    // Get the forwarded packet from the callout
    Pkt6Ptr forwarded = Dhcp6to4IpcTest::callback_pkt_;
    ASSERT_TRUE(forwarded);

    // Verify the packet received.
    EXPECT_EQ(DHCP6_CLIENT_PORT, forwarded->getRemotePort());
    EXPECT_EQ(forwarded->getType(), pkt->getType());
    EXPECT_TRUE(forwarded->getOption(D6O_DHCPV4_MSG));
    EXPECT_EQ("eth0", forwarded->getIface());
    EXPECT_EQ("2001:db8:1::123", forwarded->getRemoteAddr().toText());

    // Verify statistics
    pkt6_snd = mgr.getObservation("pkt6-sent");
    d4_resp = mgr.getObservation("pkt6-dhcpv4-response-sent");
    ASSERT_TRUE(pkt6_snd);
    ASSERT_TRUE(d4_resp);
    EXPECT_EQ(1, pkt6_snd->getInteger().first);
    EXPECT_EQ(1, d4_resp->getInteger().first);
}

// This test verifies that the DHCPv4 endpoint of the DHCPv4o6 IPC can
// receive relayed messages.
// This is currently not supported: it is a known defect addressed by #4296.
TEST_F(Dhcp6to4IpcTest, DISABLED_receiveRelayed) {
    // Create instance of the IPC endpoint under test.
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);

    // Reset the IPC.
    ASSERT_NO_THROW(ipc.close());

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Get statistics
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt6_snd = mgr.getObservation("pkt6-sent");
    ObservationPtr d4_resp = mgr.getObservation("pkt6-dhcpv4-response-sent");
    EXPECT_FALSE(pkt6_snd);
    EXPECT_FALSE(d4_resp);

    // Create relayed message to be sent over IPC.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_RESPONSE, 1234));
    pkt->addOption(createDHCPv4MsgOption());
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("3000:1::1");
    relay.peeraddr_ = IOAddress("fe80::1");
    relay.msg_type_ = DHCPV6_RELAY_FORW;
    relay.hop_count_ = 1;
    pkt->relay_info_.push_back(relay);
    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the callout cached packet
    Dhcp6to4IpcTest::callback_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // Get the forwarded packet from the callout
    Pkt6Ptr forwarded = Dhcp6to4IpcTest::callback_pkt_;
    ASSERT_TRUE(forwarded);

    // Verify the packet received.
    EXPECT_EQ(DHCP6_CLIENT_PORT, forwarded->getRemotePort());
    EXPECT_EQ(forwarded->getType(), pkt->getType());
    EXPECT_TRUE(forwarded->getOption(D6O_DHCPV4_MSG));
    EXPECT_EQ("eth0", forwarded->getIface());
    EXPECT_EQ("2001:db8:1::123", forwarded->getRemoteAddr().toText());
    EXPECT_EQ(DHCP6_CLIENT_PORT, forwarded->getRemotePort());

    // Verify statistics
    pkt6_snd = mgr.getObservation("pkt6-sent");
    d4_resp = mgr.getObservation("pkt6-dhcpv4-response-sent");
    ASSERT_TRUE(pkt6_snd);
    ASSERT_TRUE(d4_resp);
    EXPECT_EQ(1, pkt6_snd->getInteger().first);
    EXPECT_EQ(1, d4_resp->getInteger().first);
}

// This test verifies the client port is enforced also with DHCP4o6.
TEST_F(Dhcp6to4IpcTest, clientPort) {
    // Create instance of the IPC endpoint under test.
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();
    // Set the client port.
    ipc.client_port = 1234;
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V4);

    // Reset the IPC.
    ASSERT_NO_THROW(ipc.close());

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Create message to be sent over IPC.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_RESPONSE, 1234));
    pkt->addOption(createDHCPv4MsgOption());
    pkt->setIface("eth0");
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the callout cached packet
    Dhcp6to4IpcTest::callback_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // Make sure that the received packet was configured to return copy of
    // retrieved options within a callout.
    EXPECT_TRUE(callback_pkt_options_copy_);

    // Get the forwarded packet from the callout
    Pkt6Ptr forwarded = Dhcp6to4IpcTest::callback_pkt_;
    ASSERT_TRUE(forwarded);

    // Verify the packet received.
    EXPECT_EQ(ipc.client_port, forwarded->getRemotePort());

    // Reset the value in case tests are not in order.
    ipc.client_port = 0;
}

} // end of anonymous namespace
