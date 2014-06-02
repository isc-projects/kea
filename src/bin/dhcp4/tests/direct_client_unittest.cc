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

#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/classify.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcp4/json_config_parser.h>
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
    /// selected. The subnet and pool mask is always /24. The real configuration
    /// would exclude .0 (network address) and .255 (broadcast address), but we
    /// ignore that fact for the sake of test simplicity.
    ///
    /// @param prefix Prefix for a subnet.
    void configureSubnet(const std::string& prefix);

    /// @brief Configures the server with two subnets.
    ///
    /// This function configures DHCPv4 server with two different subnets.
    /// The subnet parameters (such as options, timers etc.) are aribitrarily
    /// selected. The subnet and pool mask is /24. The real configuration
    /// would exclude .0 (network address) and .255 (broadcast address), but we
    /// ignore that fact for the sake of test simplicity.
    ///
    /// @param prefix1 Prefix of the first subnet to be configured.
    /// @param prefix2 Prefix of the second subnet to be configured.
    void configureTwoSubnets(const std::string& prefix1,
                             const std::string& prefix2);

    /// @brief Creates simple message from a client.
    ///
    /// This function creates a DHCPv4 message having a specified type
    /// (e.g. Discover, Request) and sets some properties of this
    /// message: client identifier, address and interface. The copy of
    /// this message is then created by parsing wire data of the original
    /// message. This simulates the case when the message is received and
    /// parsed by the server.
    ///
    /// @param msg_type Type of the message to be created.
    /// @param iface Name of the interface on which the message has been
    /// "received" by the server.
    ///
    /// @return Generated message.
    Pkt4Ptr createClientMessage(const uint16_t msg_type,
                                const std::string& iface);

    /// @brief Creates simple message from a client.
    ///
    /// This function configures a client's message by adding client identifier,
    /// setting interface and addresses. The copy of this message is then
    /// created by parsing wire data of the original message. This simulates the
    /// case when the message is received and parsed by the server.
    ///
    /// @param msg Caller supplied message to be configured. This object must
    /// not be NULL.
    /// @param iface Name of the interface on which the message has been
    /// "received" by the server.
    ///
    /// @return Configured and parsed message.
    Pkt4Ptr createClientMessage(const Pkt4Ptr &msg, const std::string& iface);

    /// @brief classes the client belongs to
    ///
    /// This is empty in most cases, but it is needed as a parameter for all
    /// getSubnet4() calls.
    ClientClasses classify_;
};

DirectClientTest::DirectClientTest() : Dhcpv4SrvTest() {
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
    return (createClientMessage(msg, iface));

}

Pkt4Ptr
DirectClientTest::createClientMessage(const Pkt4Ptr& msg,
                                      const std::string& iface) {
    msg->setRemoteAddr(IOAddress("255.255.255.255"));
    msg->addOption(generateClientId());
    msg->setIface(iface);

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

    // Make sure that we received a response.
    Pkt4Ptr response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);
    srv_.fake_sent_.pop_front();

    // Client should get an Offer (not a NAK).
    ASSERT_EQ(DHCPOFFER, response->getType());
    // Check that the offered address belongs to the suitable subnet.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(response->getYiaddr(),
                                                      classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.0.0.0", subnet->get().first.toText());

    // A client that sent Request over the other interface should get Ack.
    response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);

    // Client should get an Ack (not a NAK).
    ASSERT_EQ(DHCPACK, response->getType());
    // Check that the offered address belongs to the suitable subnet.
    subnet = CfgMgr::instance().getSubnet4(response->getYiaddr(), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ("192.0.2.0", subnet->get().first.toText());

}

// This test checks that server selects a subnet when receives a message
// through an interface for which the subnet has been configured. This
// interface has IPv4 address assigned which belongs to this subnet.
// This test also verifies that when the message is received through
// the interface for which there is no suitable subnet, the message
// is discarded.
TEST_F(DirectClientTest, oneSubnet) {
    // Configure IfaceMgr with fake interfaces lo, eth0 and eth1.
    IfaceMgrTestConfig iface_config(true);
    // After creating interfaces we have to open sockets as it is required
    // by the message processing code.
    ASSERT_NO_THROW(IfaceMgr::instance().openSockets4());
    // Add a subnet which will be selected when a message from directly
    // connected client is received through interface eth0.
    ASSERT_NO_FATAL_FAILURE(configureSubnet("10.0.0.0"));
    // Create Discover and simulate reception of this message through eth0.
    Pkt4Ptr dis = createClientMessage(DHCPDISCOVER, "eth0");
    srv_.fakeReceive(dis);
    // Create Request and simulate reception of this message through eth1.
    Pkt4Ptr req = createClientMessage(DHCPDISCOVER, "eth1");
    srv_.fakeReceive(req);

    // Process clients' messages.
    srv_.run();

    // Check that the server sent one response for the message received
    // through eth0. The other client's message should be dicarded.
    ASSERT_EQ(1, srv_.fake_sent_.size());

    // Check the response. The first Discover was sent via eth0 for which
    // the subnet has been configured.
    Pkt4Ptr response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);
    srv_.fake_sent_.pop_front();

    // Since Discover has been received through the interface for which
    // the subnet has been configured, the server should respond with
    // an Offer message.
    ASSERT_EQ(DHCPOFFER, response->getType());
    // Check that the offered address belongs to the suitable subnet.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(response->getYiaddr(),
                                                      classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.0.0.0", subnet->get().first.toText());

}

// This test verifies that the server uses ciaddr to select a subnet for a
// client which renews its lease.
TEST_F(DirectClientTest, renew) {
    // Configure IfaceMgr with fake interfaces lo, eth0 and eth1.
    IfaceMgrTestConfig iface_config(true);
    // After creating interfaces we have to open sockets as it is required
    // by the message processing code.
    ASSERT_NO_THROW(IfaceMgr::instance().openSockets4());
    // Add a subnet.
    ASSERT_NO_FATAL_FAILURE(configureSubnet("10.0.0.0"));
    // Make sure that the subnet has been really added. Also, the subnet
    // will be needed to create a lease for a client.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("10.0.0.10"),
                                                      classify_);
    // Create a lease for a client that we will later renewed. By explicitly
    // creating a lease we will get to know the lease parameters, such as
    // leased address etc.
    const uint8_t hwaddr[] = { 1, 2, 3, 4, 5, 6 };
    Lease4Ptr lease(new Lease4(IOAddress("10.0.0.10"), hwaddr, sizeof(hwaddr),
                               &generateClientId()->getData()[0],
                               generateClientId()->getData().size(),
                               100, 50, 75, time(NULL),
                               subnet->getID()));
    LeaseMgrFactory::instance().addLease(lease);

    // Create a Request to renew client's lease. The renew request is unicast
    // through eth1. Note, that in case of renewal the client unicasts its
    // Request and sets the ciaddr. The server is supposed to use ciaddr to
    // pick the subnet for the client. In order to make sure that the server
    // uses ciaddr, we simulate reception of the packet through eth1, for which
    // there is no subnet for directly connected clients.
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setCiaddr(IOAddress("10.0.0.10"));
    req = createClientMessage(req, "eth1");
    req->setLocalAddr(IOAddress("10.0.0.1"));
    req->setRemoteAddr(req->getCiaddr());

    srv_.fakeReceive(req);

    // Process clients' messages.
    srv_.run();

    // Check that the server did send reposonse.
    ASSERT_EQ(1, srv_.fake_sent_.size());
    Pkt4Ptr response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);

    ASSERT_EQ(DHCPACK, response->getType());
    // Check that the offered address belongs to the suitable subnet.
    subnet = CfgMgr::instance().getSubnet4(response->getYiaddr(), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.0.0.0", subnet->get().first.toText());

}

// This test verifies that when a client in the Rebinding state broadcasts
// a Request message through an interface for which a subnet is configured,
// the server responds to this Request. It also verifies that when such a
// Request is sent through the interface for which there is no subnet configured
// the client's message is discarded.
TEST_F(DirectClientTest, rebind) {
    // Configure IfaceMgr with fake interfaces lo, eth0 and eth1.
    IfaceMgrTestConfig iface_config(true);
    // After creating interfaces we have to open sockets as it is required
    // by the message processing code.
    ASSERT_NO_THROW(IfaceMgr::instance().openSockets4());
    // Add a subnet.
    ASSERT_NO_FATAL_FAILURE(configureSubnet("10.0.0.0"));
    // Make sure that the subnet has been really added. Also, the subnet
    // will be needed to create a lease for a client.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("10.0.0.10"),
                                                      classify_);
    // Create a lease, which will be later renewed. By explicitly creating a
    // lease we will know the lease parameters, such as leased address etc.
    const uint8_t hwaddr[] = { 1, 2, 3, 4, 5, 6 };
    Lease4Ptr lease(new Lease4(IOAddress("10.0.0.10"), hwaddr, sizeof(hwaddr),
                               &generateClientId()->getData()[0],
                               generateClientId()->getData().size(),
                               100, 50, 75, time(NULL),
                               subnet->getID()));
    LeaseMgrFactory::instance().addLease(lease);

    // Broadcast Request through an interface for which there is no subnet
    // configured. This messag should be discarded by the server.
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setCiaddr(IOAddress("10.0.0.10"));
    req = createClientMessage(req, "eth1");
    req->setRemoteAddr(req->getCiaddr());

    srv_.fakeReceive(req);

    // Broadcast another Request through an interface for which there is
    // a subnet configured. The server should generate a response.
    req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 5678));
    req->setCiaddr(IOAddress("10.0.0.10"));
    req = createClientMessage(req, "eth0");
    req->setRemoteAddr(req->getCiaddr());

    srv_.fakeReceive(req);

    // Process clients' messages.
    srv_.run();

    // Check that the server did send exactly one reposonse.
    ASSERT_EQ(1, srv_.fake_sent_.size());
    Pkt4Ptr response = srv_.fake_sent_.front();
    ASSERT_TRUE(response);

    // Make sure that the server responsed with ACK, not NAK.
    ASSERT_EQ(DHCPACK, response->getType());
    // Make sure that the response is generated for the second Request
    // (transmitted over eth0).
    EXPECT_EQ(5678, response->getTransid());
    // Check that the offered address belongs to the suitable subnet.
    subnet = CfgMgr::instance().getSubnet4(response->getYiaddr(), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.0.0.0", subnet->get().first.toText());

}

}
