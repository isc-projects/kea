// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcp4/config_parser.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for testing message processing from directly
/// connected clients.
///
/// This class provides mechanisms for testing processing of DHCPv4 messages
/// from directly connected clients.
class DirectClientTest : public Dhcpv4SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Initializes DHCPv4 server object used by various tests.
    DirectClientTest();

    /// @brief Configures the server with one subnet.
    ///
    /// This creates new configuration for the DHCPv4 with one subnet having
    /// a specified prefix.
    ///
    /// The subnet parameters (such as options, timers etc.) are aribitrarily
    /// selected. The subnet and pool mask is always /24.
    ///
    /// @param prefix Prefix for a subnet.
    void configureSubnet(const std::string& prefix);

    /// @brief Configures the server with two subnets.
    ///
    /// This function configures DHCPv4 server with two different subnets.
    /// The subnet parameters (such as options, timers etc.) are aribitrarily
    /// selected. The subnet and pool mask is /24.
    ///
    /// @param prefix1 Prefix of the first subnet to be configured.
    /// @param prefix2 Prefix of the second subnet to be configured.
    void configureTwoSubnets(const std::string& prefix1,
                             const std::string& prefix2);

    /// @brief Creates simple message from a client.
    ///
    /// This function creates a DHCPv4 message having a specified type
    /// (e.g. Discover, Request) and sets the interface property of this
    /// message. The interface property indicates on which interface
    /// interface a message has been received. The interface is used by
    /// the DHCPv4 server to determine the subnet from which the address
    /// should be allocated for the client.
    ///
    /// @param msg_type Type of the message to be created.
    /// @param iface Name of the interface on which the message has been
    /// "received" by the server.
    ///
    /// @return Generated message.
    Pkt4Ptr createClientMessage(const uint16_t msg_type,
                                const std::string& iface);

    /// @brief Runs DHCPv4 configuration from the JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    void configure(const std::string& config);

    /// @brief Server object to be unit tested.
    NakedDhcpv4Srv srv_;

};

DirectClientTest::DirectClientTest()
    : srv_(0) {
}

void
DirectClientTest::configureSubnet(const std::string& prefix) {
    std::ostringstream config;
    config << "{ \"interfaces\": [ \"*\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ ],"
        "\"subnet4\": [ { "
        "    \"pool\": [ \"" << prefix << "/24\" ],"
        "    \"subnet\": \"" << prefix << "/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000"
        "} ],"
        "\"valid-lifetime\": 4000 }";

    configure(config.str());

}

void
DirectClientTest::configureTwoSubnets(const std::string& prefix1,
                                      const std::string& prefix2) {
    std::ostringstream config;
    config << "{ \"interfaces\": [ \"*\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ ],"
        "\"subnet4\": [ { "
        "    \"pool\": [ \"" << prefix1 << "/24\" ],"
        "    \"subnet\": \"" << prefix1 << "/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000"
        " },"
        "{ "
        "    \"pool\": [ \"" << prefix2 << "/24\" ],"
        "    \"subnet\": \"" << prefix2 << "/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000"
        "} ],"
        "\"valid-lifetime\": 4000 }";

    configure(config.str());
}

Pkt4Ptr
DirectClientTest:: createClientMessage(const uint16_t msg_type,
                                       const std::string& iface) {
    // Create a source packet.
    Pkt4Ptr msg = Pkt4Ptr(new Pkt4(msg_type, 1234));
    msg->setRemoteAddr(IOAddress("255.255.255.255"));
    msg->addOption(generateClientId());
    msg->setIface(iface);
    // Create on-wire format of this packet as it has been sent by the client.
    msg->pack();

    // Create copy of this packet by parsing its wire data. Make sure that the
    // local and remote address are set like it was a message sent from the
    // directly connected client.
    Pkt4Ptr received;
    createPacketFromBuffer(msg, received);
    received->setIface(iface);
    received->setLocalAddr(IOAddress("255.255.255.255"));
    received->setRemoteAddr(IOAddress("0.0.0.0"));

    return (received);
}

void
DirectClientTest::configure(const std::string& config) {
    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv_, json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode);
}

// This test checks that the message from directly connected client
// is processed and that client is offered IPv4 address from the subnet which
// is suitable for the local interface on which the client's message is
// received. This test uses two subnets, with two active interfaces which IP
// addresses belong to these subnets. The address offered to the client
// which message has been sent over eth0 should belong to a different
// subnet than the address offered for the client sending its message
// via eth1.
TEST_F(DirectClientTest,  twoSubnets) {
    // Configure IfaceMgr with fake interfaces lo, eth0 and eth1.
    IfaceMgrTestConfig iface_config(true);
    // After creating interfaces we have to open sockets as it is required
    // by the message processing code.
    ASSERT_NO_THROW(IfaceMgr::instance().openSockets4());
    // Add two subnets: address on eth0 belongs to the second subnet,
    // address on eth1 belongs to the first subnet.
    ASSERT_NO_FATAL_FAILURE(configureTwoSubnets("192.0.2.0", "10.0.0.0"));
    // Create Discover and simulate reception of this message through eth0.
    Pkt4Ptr dis = createClientMessage(DHCPDISCOVER, "eth0");
    srv_.fakeReceive(dis);
    // Create Request and simulate reception of this message through eth1.
    Pkt4Ptr req = createClientMessage(DHCPREQUEST, "eth1");
    srv_.fakeReceive(req);

    // Process clients' messages.
    srv_.run();

    // Check that the server did send reposonses.
    ASSERT_EQ(2, srv_.fake_sent_.size());

    // Make sure that we received a responses.
    Pkt4Ptr response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);
    srv_.fake_sent_.pop_front();

    // Client should get an Offer (not a NAK).
    ASSERT_EQ(DHCPOFFER, response->getType());
    // Check that the offered address belongs to the suitable subnet.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(response->getYiaddr());
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.0.0.0", subnet->get().first.toText());

    // A client that sent Request over the other interface should get Ack.
    response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);

    // Client should get an Ack (not a NAK).
    ASSERT_EQ(DHCPACK, response->getType());
    // Check that the offered address belongs to the suitable subnet.
    subnet = CfgMgr::instance().getSubnet4(response->getYiaddr());
    ASSERT_TRUE(subnet);
    EXPECT_EQ("192.0.2.0", subnet->get().first.toText());

}

}
