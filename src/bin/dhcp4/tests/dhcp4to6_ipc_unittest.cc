// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/pkt4o6.h>
#include <dhcp/pkt6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4to6_ipc.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/testutils/dhcp4o6_test_ipc.h>
#include <stats/stats_mgr.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>

#include <gtest/gtest.h>
#include <stdint.h>
#include <utility>

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
class Dhcp4to6IpcTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor
    ///
    /// Configures IPC to use a test port. It also provides a fake
    /// configuration of interfaces.
    Dhcp4to6IpcTest()
        : Dhcpv4SrvTest(),
        iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();
        configurePort(TEST_PORT);
        // Install buffer4_receive_callout
        EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().
                        registerCallout("buffer4_receive",
                                        buffer4_receive_callout));
        // Install buffer4_send_callout
        EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().
                        registerCallout("buffer4_send", buffer4_send_callout));
        // Verify we have a controlled server
        ControlledDhcpv4Srv* srv = NULL;
        EXPECT_NO_THROW(srv = ControlledDhcpv4Srv::getInstance());
        EXPECT_TRUE(srv);
        // Let's wipe all existing statistics.
        StatsMgr::instance().removeAll();

        // Set the flags to false as we expect them to be set in callouts.
        callback_recv_pkt_options_copy_ = std::make_pair(false, false);
        callback_sent_pkt_options_copy_ = std::make_pair(false, false);
    }

    /// @brief Destructor
    ///
    /// Various cleanups.
    virtual ~Dhcp4to6IpcTest() {
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer4_send");
        callback_recv_pkt_.reset();
        callback_sent_pkt_.reset();
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            cerr << "(fixture dtor) unloadLibraries failed" << endl;
        }
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

    /// @brief Handler for the buffer4_receive hook
    ///
    /// This hook is at the beginning of processPacket
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int buffer4_receive_callout(CalloutHandle& callout_handle) {
        callout_handle.getArgument("query4", callback_recv_pkt_);
        Pkt4o6Ptr pkt4 = boost::dynamic_pointer_cast<Pkt4o6>(callback_recv_pkt_);
        if (pkt4) {
            callback_recv_pkt_options_copy_.first = pkt4->isCopyRetrievedOptions();
            Pkt6Ptr pkt6 = pkt4->getPkt6();
            if (pkt6) {
                callback_recv_pkt_options_copy_.second =
                    pkt6->isCopyRetrievedOptions();
            }
        }
        return (0);
    }

    /// @brief Handler for the buffer4_send hook
    ///
    /// This hook is at the end of the DHCPv4o6 packet handler
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int buffer4_send_callout(CalloutHandle& callout_handle) {
        callout_handle.getArgument("response4", callback_sent_pkt_);
        Pkt4o6Ptr pkt4 = boost::dynamic_pointer_cast<Pkt4o6>(callback_sent_pkt_);
        if (pkt4) {
            callback_sent_pkt_options_copy_.first = pkt4->isCopyRetrievedOptions();
            Pkt6Ptr pkt6 = pkt4->getPkt6();
            if (pkt6) {
                callback_sent_pkt_options_copy_.second =
                    pkt6->isCopyRetrievedOptions();
            }
        }
        return (0);
    }

    /// @brief Response Pkt4 shared pointer returned in the receive callout
    static Pkt4Ptr callback_recv_pkt_;

    /// @brief Response Pkt4 shared pointer returned in the send callout
    static Pkt4Ptr callback_sent_pkt_;

    /// Flags indicating if copying retrieved options was enabled for
    /// a received packet during callout execution.
    static std::pair<bool, bool> callback_recv_pkt_options_copy_;

    /// Flags indicating if copying retrieved options was enabled for
    /// a sent packet during callout execution.
    static std::pair<bool, bool> callback_sent_pkt_options_copy_;

    /// @brief reference to a controlled server
    ///
    /// Dhcp4to6Ipc::handler() uses the instance of the controlled server
    /// so it has to be build. This reference does this.
    ControlledDhcpv4Srv srv_;

private:

    /// @brief Provides fake configuration of interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

Pkt4Ptr Dhcp4to6IpcTest::callback_recv_pkt_;
Pkt4Ptr Dhcp4to6IpcTest::callback_sent_pkt_;
std::pair<bool, bool> Dhcp4to6IpcTest::callback_recv_pkt_options_copy_;
std::pair<bool, bool> Dhcp4to6IpcTest::callback_sent_pkt_options_copy_;

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
    pkt->setIndex(ETH0_INDEX);
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the received packet
    Dhcp4to6IpcTest::callback_recv_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // Make sure that the message has been received.
    // The buffer4_receive hook is at the beginning of processPacket
    // so this proves it was passed to it.
    Pkt4Ptr pkt4_received = Dhcp4to6IpcTest::callback_recv_pkt_;
    ASSERT_TRUE(pkt4_received);
    Pkt4o6Ptr pkt_received =
        boost::dynamic_pointer_cast<Pkt4o6>(pkt4_received);
    ASSERT_TRUE(pkt_received);
    Pkt6Ptr pkt6_received = pkt_received->getPkt6();
    ASSERT_TRUE(pkt6_received);
    EXPECT_EQ("eth0", pkt6_received->getIface());
    EXPECT_EQ(ETH0_INDEX, pkt6_received->getIndex());
    EXPECT_EQ("2001:db8:1::123", pkt6_received->getRemoteAddr().toText());

    // Both DHCP4o6 and encapsulated DHCPv6 packet should have the
    // flag enabled.
    EXPECT_TRUE(callback_recv_pkt_options_copy_.first);
    EXPECT_TRUE(callback_recv_pkt_options_copy_.second);
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
    pkt->setIndex(ETH0_INDEX);
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the received packet
    Dhcp4to6IpcTest::callback_recv_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    EXPECT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // No message should has been sent.
    Pkt4Ptr pkt4_received = Dhcp4to6IpcTest::callback_recv_pkt_;
    EXPECT_FALSE(pkt4_received);
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
    pkt->setIndex(ETH0_INDEX);
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the received packet
    Dhcp4to6IpcTest::callback_recv_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    EXPECT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // No message should has been sent.
    Pkt4Ptr pkt4_received = Dhcp4to6IpcTest::callback_recv_pkt_;
    EXPECT_FALSE(pkt4_received);
}

// This test verifies that the DHCPv4 endpoint of the DHCPv4o6 IPC can
// process messages.
TEST_F(Dhcp4to6IpcTest, process) {
    // Create instance of the IPC endpoint under test.
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();
    // Create instance of the IPC endpoint being used as a source of messages.
    TestIpc src_ipc(TEST_PORT, TestIpc::ENDPOINT_TYPE_V6);

    // Open both endpoints.
    ASSERT_NO_THROW(ipc.open());
    ASSERT_NO_THROW(src_ipc.open());

    // Get statistics
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt4_snd = mgr.getObservation("pkt4-sent");
    ObservationPtr pkt4_ack = mgr.getObservation("pkt4-ack-sent");
    EXPECT_FALSE(pkt4_snd);
    EXPECT_FALSE(pkt4_ack);

    // Create an information request message
    Pkt4Ptr infreq(new Pkt4(DHCPINFORM, 1234));
    infreq->setHWAddr(generateHWAddr(6));
    infreq->setCiaddr(IOAddress("192.0.1.2"));
    // Make a wire representation of the DHCPv4 message.
    infreq->pack();
    OutputBuffer& output_buffer = infreq->getBuffer();
    const uint8_t* data = static_cast<const uint8_t*>(output_buffer.getData());
    OptionBuffer option_buffer(data, data + output_buffer.getLength());

    // Create the DHCPv4 Message option holding the created message.
    OptionPtr opt_msg(new Option(Option::V6, D6O_DHCPV4_MSG, option_buffer));

    // Create message to be sent over IPC.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_DHCPV4_QUERY, 1234));
    pkt->addOption(opt_msg);
    pkt->setIface("eth0");
    pkt->setIndex(ETH0_INDEX);
    pkt->setRemoteAddr(IOAddress("2001:db8:1::123"));
    ASSERT_NO_THROW(pkt->pack());

    // Reset the received packet
    Dhcp4to6IpcTest::callback_recv_pkt_.reset();

    // Send and wait up to 1 second to receive it.
    ASSERT_NO_THROW(src_ipc.send(pkt));
    ASSERT_NO_THROW(IfaceMgr::instance().receive6(1, 0));

    // Make sure that the message has been received.
    Pkt4Ptr pkt4_received = Dhcp4to6IpcTest::callback_recv_pkt_;
    ASSERT_TRUE(pkt4_received);
    Pkt4o6Ptr pkt_received =
        boost::dynamic_pointer_cast<Pkt4o6>(pkt4_received);
    ASSERT_TRUE(pkt_received);
    Pkt6Ptr pkt6_received = pkt_received->getPkt6();
    ASSERT_TRUE(pkt6_received);
    EXPECT_EQ("eth0", pkt6_received->getIface());
    EXPECT_EQ(ETH0_INDEX, pkt6_received->getIndex());
    EXPECT_EQ("2001:db8:1::123", pkt6_received->getRemoteAddr().toText());

    // Make sure that the message has been processed.
    // Using the buffer4_send hook
    Pkt4Ptr pkt4_sent = Dhcp4to6IpcTest::callback_sent_pkt_;
    ASSERT_TRUE(pkt4_sent);
    EXPECT_EQ(DHCPACK, pkt4_sent->getType());
    Pkt4o6Ptr pkt_sent = boost::dynamic_pointer_cast<Pkt4o6>(pkt4_sent);
    ASSERT_TRUE(pkt_sent);
    Pkt6Ptr pkt6_sent = pkt_sent->getPkt6();
    ASSERT_TRUE(pkt6_sent);
    EXPECT_EQ(DHCPV6_DHCPV4_RESPONSE, pkt6_sent->getType());
    EXPECT_EQ("eth0", pkt6_sent->getIface());
    EXPECT_EQ(ETH0_INDEX, pkt6_sent->getIndex());
    EXPECT_EQ("2001:db8:1::123", pkt6_sent->getRemoteAddr().toText());

    // Both DHCP4o6 and encapsulated DHCPv6 packet should have the
    // flag enabled.
    EXPECT_TRUE(callback_sent_pkt_options_copy_.first);
    EXPECT_TRUE(callback_sent_pkt_options_copy_.second);

    // Verify the 4o6 part
    OptionCollection sent_msgs = pkt6_sent->getOptions(D6O_DHCPV4_MSG);
    ASSERT_EQ(1, sent_msgs.size());
    OptionPtr sent_msg = sent_msgs.begin()->second;
    ASSERT_TRUE(sent_msg);
    const OptionBuffer sent_buf = sent_msg->getData();
    Pkt4Ptr pkt4_opt;
    ASSERT_NO_THROW(pkt4_opt.reset(new Pkt4(&sent_buf[0], sent_buf.size())));
    ASSERT_NO_THROW(pkt4_opt->unpack());
    EXPECT_EQ(DHCPACK, pkt4_sent->getType());
    EXPECT_EQ(pkt4_sent->len(), pkt4_opt->len());

    // Verify statistics
    pkt4_snd = mgr.getObservation("pkt4-sent");
    pkt4_ack = mgr.getObservation("pkt4-ack-sent");
    ASSERT_TRUE(pkt4_snd);
    ASSERT_TRUE(pkt4_ack);
    EXPECT_EQ(1, pkt4_snd->getInteger().first);
    EXPECT_EQ(1, pkt4_ack->getInteger().first);
}

} // end of anonymous namespace
