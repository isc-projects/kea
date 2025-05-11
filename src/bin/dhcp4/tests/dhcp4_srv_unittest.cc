// Copyright (C) 2011-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <config/unix_command_mgr.h>
#include <config_backend/base_config_backend.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp/testutils/pkt_captures.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/host_mgr.h>
#include <process/redact_config.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <util/encode/encode.h>

#ifdef HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#include <hooks/dhcp/mysql/mysql_host_data_source.h>
#endif

#ifdef HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#include <hooks/dhcp/pgsql/pgsql_host_data_source.h>
#endif

#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <cstdlib>

#include <arpa/inet.h>
#include <dirent.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::cb;
using namespace isc::config;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace isc::util;
using namespace std;

namespace {

const char* CONFIGS[] = {
    // Configuration 0:
    // - 1 subnet: 10.254.226.0/25
    // - used for recorded traffic (see PktCaptures::captureRelayedDiscover)
    "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.254.226.0/25\" } ],"
        "    \"subnet\": \"10.254.226.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
    "\"valid-lifetime\": 4000 }",

    // Configuration 1:
    // - 1 subnet: 192.0.2.0/24
    // - MySQL Host Data Source configured
    "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"hosts-database\": {"
        "    \"type\": \"mysql\","
        "    \"name\": \"keatest\","
        "    \"user\": \"keatest\","
        "    \"password\": \"keatest\""
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
    "\"valid-lifetime\": 4000 }",

    // Configuration 2:
    // - 1 subnet, 2 global options (one forced with always-send)
    "{"
    "    \"interfaces-config\": {"
    "    \"interfaces\": [ \"*\" ] }, "
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"valid-lifetime\": 4000, "
    "    \"subnet4\": [ {"
    "        \"id\": 1,"
    "        \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
    "        \"subnet\": \"192.0.2.0/24\""
    "    } ], "
    "    \"option-data\": ["
    "        {"
    "            \"name\": \"default-ip-ttl\", "
    "            \"data\": \"FF\", "
    "            \"csv-format\": false"
    "        }, "
    "        {"
    "            \"name\": \"ip-forwarding\", "
    "            \"data\": \"false\", "
    "            \"always-send\": true"
    "        }"
    "    ]"
    "}",

    // Configuration 3:
    // - 1 subnet with never-send option
    // - 2 global options (one forced with always-send)
    "{"
    "    \"interfaces-config\": {"
    "    \"interfaces\": [ \"*\" ] }, "
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"valid-lifetime\": 4000, "
    "    \"subnet4\": [ {"
    "        \"id\": 1,"
    "        \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
    "        \"subnet\": \"192.0.2.0/24\","
    "        \"option-data\": ["
    "            {"
    "                \"name\": \"ip-forwarding\", "
    "                \"never-send\": true"
    "            }"
    "        ]"
    "    } ], "
    "    \"option-data\": ["
    "        {"
    "            \"name\": \"default-ip-ttl\", "
    "            \"data\": \"FF\", "
    "            \"csv-format\": false"
    "        }, "
    "        {"
    "            \"name\": \"ip-forwarding\", "
    "            \"data\": \"false\", "
    "            \"always-send\": true"
    "        }"
    "    ]"
    "}",

    // Configuration 4:
    // - one subnet, with one pool
    // - user-contexts defined in both subnet and pool
    "{"
        "    \"subnet4\": [ { "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.254.226.0/25\","
        "                   \"user-context\": { \"value\": 42 } } ],"
        "    \"subnet\": \"10.254.226.0/24\", "
        "    \"user-context\": {"
        "        \"secure\": false"
        "    }"
        " } ],"
    "\"valid-lifetime\": 4000 }",
};

// Convenience function for comparing option buffer to an expected string value
// @param exp_string expected string value
// @param buffer OptionBuffer whose contents are to be tested
void checkStringInBuffer( const std::string& exp_string, const OptionBuffer& buffer) {
    std::string buffer_string(buffer.begin(), buffer.end());
    EXPECT_EQ(exp_string, std::string(buffer_string.c_str()));
}

// This test verifies that the destination address of the response
// message is set to giaddr, when giaddr is set to non-zero address
// in the received message.
TEST_F(Dhcpv4SrvTest, adjustIfaceDataRelay) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create the instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr to non-zero address and hops to non-zero value
    // as if it was relayed.
    req->setGiaddr(IOAddress("192.0.1.1"));
    req->setHops(2);
    // Set ciaddr to zero. This simulates the client which applies
    // for the new lease.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // Clear broadcast flag.
    req->setFlags(0x0000);

    // Set local address, port and interface.
    req->setLocalAddr(IOAddress("192.0.2.5"));
    req->setLocalPort(1001);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Set remote port (it will be used in the next test).
    req->setRemotePort(1234);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);

    Pkt4Ptr resp = ex.getResponse();
    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Set hops value for the response.
    resp->setHops(req->getHops());

    // This function never throws.
    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Now the destination address should be relay's address.
    EXPECT_EQ("192.0.1.1", resp->getRemoteAddr().toText());
    // The query has been relayed, so the response must be sent to the port 67.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getRemotePort());
    // Local address should be the address assigned to interface eth1.
    EXPECT_EQ("192.0.2.5", resp->getLocalAddr().toText());
    // The local port is always DHCPv4 server port 67.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());
    // We will send response over the same interface which was used to receive
    // query.
    EXPECT_EQ("eth1", resp->getIface());
    EXPECT_EQ(ETH1_INDEX, resp->getIndex());

    // Let's do another test and set other fields: ciaddr and
    // flags. By doing it, we want to make sure that the relay
    // address will take precedence.
    req->setGiaddr(IOAddress("192.0.1.50"));
    req->setCiaddr(IOAddress("192.0.1.11"));
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // Set the client and server ports.
    srv_->client_port_ = 1234;
    srv_->server_port_ = 2345;

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Response should be sent back to the relay address.
    EXPECT_EQ("192.0.1.50", resp->getRemoteAddr().toText());

    // Remote port was enforced to the client port.
    EXPECT_EQ(srv_->client_port_, resp->getRemotePort());

    // Local port was enforced to the server port.
    EXPECT_EQ(srv_->server_port_, resp->getLocalPort());
}

// This test verifies that the remote port is adjusted when
// the query carries a relay port RAI sub-option.
TEST_F(Dhcpv4SrvTest, adjustIfaceDataRelayPort) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create the instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr to non-zero address and hops to non-zero value
    // as if it was relayed.
    req->setGiaddr(IOAddress("192.0.1.1"));
    req->setHops(2);
    // Set ciaddr to zero. This simulates the client which applies
    // for the new lease.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // Clear broadcast flag.
    req->setFlags(0x0000);

    // Set local address, port and interface.
    req->setLocalAddr(IOAddress("192.0.2.5"));
    req->setLocalPort(1001);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Set remote port.
    req->setRemotePort(1234);

    // Add a RAI relay-port sub-option (the only difference with the previous test).
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));
    ASSERT_TRUE(rai);
    req->addOption(rai);
    OptionPtr relay_port(new Option(Option::V4, RAI_OPTION_RELAY_PORT));
    ASSERT_TRUE(relay_port);
    rai->addOption(relay_port);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);

    Pkt4Ptr resp = ex.getResponse();
    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Set hops value for the response.
    resp->setHops(req->getHops());

    // Set the remote port to 67 as we know it will be updated.
    resp->setRemotePort(67);

    // This function never throws.
    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Now the destination address should be relay's address.
    EXPECT_EQ("192.0.1.1", resp->getRemoteAddr().toText());
    // The query has been relayed, so the response should be sent to the
    // port 67, but here there is a relay port RAI so another value is used.
    EXPECT_EQ(1234, resp->getRemotePort());
    // Local address should be the address assigned to interface eth1.
    EXPECT_EQ("192.0.2.5", resp->getLocalAddr().toText());
    // The local port is always DHCPv4 server port 67.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());
    // We will send response over the same interface which was used to receive
    // query.
    EXPECT_EQ("eth1", resp->getIface());
    EXPECT_EQ(ETH1_INDEX, resp->getIndex());
}

// This test verifies that it is possible to configure the server to use
// routing information to determine the right outbound interface to sent
// responses to a relayed client.
TEST_F(Dhcpv4SrvTest, adjustIfaceDataUseRouting) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create configuration for interfaces. It includes the outbound-interface
    // setting which indicates that the responses aren't necessarily sent
    // over the same interface via which a request has been received, but routing
    // information is used to determine this interface.
    CfgMgr::instance().clear();
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    cfg_iface->useSocketType(AF_INET, CfgIface::SOCKET_UDP);
    cfg_iface->use(AF_INET, "eth0");
    cfg_iface->use(AF_INET, "eth1");
    cfg_iface->setOutboundIface(CfgIface::USE_ROUTING);
    CfgMgr::instance().commit();

    // Create the instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr to non-zero address and hops to non-zero value
    // as if it was relayed.
    req->setGiaddr(IOAddress("192.0.1.1"));
    req->setHops(2);
    // Set ciaddr to zero. This simulates the client which applies
    // for the new lease.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // Clear broadcast flag.
    req->setFlags(0x0000);

    // Set local address, port and interface.
    req->setLocalAddr(IOAddress("192.0.2.5"));
    req->setLocalPort(1001);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);

    Pkt4Ptr resp = ex.getResponse();
    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Set hops value for the response.
    resp->setHops(req->getHops());

    // This function never throws.
    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Now the destination address should be relay's address.
    EXPECT_EQ("192.0.1.1", resp->getRemoteAddr().toText());
    // The query has been relayed, so the response must be sent to the port 67.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getRemotePort());

    // The local port is always DHCPv4 server port 67.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());

    // No specific interface is selected as outbound interface and no specific
    // local address is provided. The IfaceMgr will figure out which interface to use.
    EXPECT_TRUE(resp->getLocalAddr().isV4Zero());
    EXPECT_FALSE(resp->indexSet());

    // Fixed in #5515 so now the interface name is never empty.
    EXPECT_FALSE(resp->getIface().empty());

    // Another test verifies that setting outbound interface to same as inbound will
    // cause the server to set interface and local address as expected.

    cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    cfg_iface->useSocketType(AF_INET, CfgIface::SOCKET_UDP);
    cfg_iface->use(AF_INET, "eth0");
    cfg_iface->use(AF_INET, "eth1");
    cfg_iface->setOutboundIface(CfgIface::SAME_AS_INBOUND);
    CfgMgr::instance().commit();

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    EXPECT_EQ("192.0.2.5", resp->getLocalAddr().toText());
    EXPECT_EQ("eth1", resp->getIface());
    EXPECT_EQ(ETH1_INDEX, resp->getIndex());
}

// This test verifies that the destination address of the response
// message is set to source address when the testing mode is enabled.
// Relayed message: not testing mode was tested in adjustIfaceDataRelay.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressRelaySendToSourceTestingModeEnabled) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create the instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr to non-zero address and hops to non-zero value
    // as if it was relayed.
    req->setGiaddr(IOAddress("192.0.1.1"));
    req->setHops(2);
    // Set ciaddr to zero. This simulates the client which applies
    // for the new lease.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // Clear broadcast flag.
    req->setFlags(0x0000);

    // Set local address, port and interface.
    req->setLocalAddr(IOAddress("192.0.2.5"));
    req->setLocalPort(1001);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Set remote address and port.
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    req->setRemotePort(1234);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);

    Pkt4Ptr resp = ex.getResponse();
    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Set hops value for the response.
    resp->setHops(req->getHops());

    // Set the testing mode.
    srv_->setSendResponsesToSource(true);

    // This function never throws.
    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Now the destination address should be source address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to ciaddr when giaddr is set to zero and the ciaddr is set to
// non-zero address in the received message. This is the case when the
// client is in Renew or Rebind state.
TEST_F(Dhcpv4SrvTest, adjustIfaceDataRenew) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Set ciaddr to non-zero address. The response should be sent to this
    // address as the client is in renewing or rebinding state (it is fully
    // configured).
    req->setCiaddr(IOAddress("192.0.1.15"));
    // Let's configure broadcast flag. It should be ignored because
    // we are responding directly to the client having an address
    // and trying to extend his lease. Broadcast flag is only used
    // when new lease is acquired and server must make a decision
    // whether to unicast the response to the acquired address or
    // broadcast it.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);
    // This is a direct message, so the hops should be cleared.
    req->setHops(0);
    // Set local unicast address as if we are renewing a lease.
    req->setLocalAddr(IOAddress("192.0.2.1"));
    // Request is received on the DHCPv4 server port.
    req->setLocalPort(DHCP4_SERVER_PORT);
    // Set the interface. The response should be sent over the same interface.
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();

    // Let's extend the lease for the client in such a way that
    // it will actually get different address. The response
    // should not be sent to this address but rather to ciaddr
    // as client still have ciaddr configured.
    resp->setYiaddr(IOAddress("192.0.1.13"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Copy hops value from the query.
    resp->setHops(req->getHops());

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Check that server responds to ciaddr
    EXPECT_EQ("192.0.1.15", resp->getRemoteAddr().toText());
    // The query was non-relayed, so the response should be sent to a DHCPv4
    // client port 68.
    EXPECT_EQ(DHCP4_CLIENT_PORT, resp->getRemotePort());
    // The response should be sent from the unicast address on which the
    // query has been received.
    EXPECT_EQ("192.0.2.1", resp->getLocalAddr().toText());
    // The response should be sent from the DHCPv4 server port.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());
    // The interface data should match the data in the query.
    EXPECT_EQ("eth1", resp->getIface());
    EXPECT_EQ(ETH1_INDEX, resp->getIndex());
}

// This test verifies that the destination address of the response message
// is set to source address when the testing mode is enabled.
// Renew: not testing mode was tested in adjustIfaceDataRenew.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressRenewSendToSourceTestingModeEnabled) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Set ciaddr to non-zero address. The response should be sent to this
    // address as the client is in renewing or rebinding state (it is fully
    // configured).
    req->setCiaddr(IOAddress("192.0.1.15"));
    // Let's configure broadcast flag. It should be ignored because
    // we are responding directly to the client having an address
    // and trying to extend his lease. Broadcast flag is only used
    // when new lease is acquired and server must make a decision
    // whether to unicast the response to the acquired address or
    // broadcast it.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);
    // This is a direct message, so the hops should be cleared.
    req->setHops(0);
    // Set local unicast address as if we are renewing a lease.
    req->setLocalAddr(IOAddress("192.0.2.1"));
    // Request is received on the DHCPv4 server port.
    req->setLocalPort(DHCP4_SERVER_PORT);
    // Set the interface. The response should be sent over the same interface.
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);
    // Set remote address.
    req->setRemoteAddr(IOAddress("192.0.2.1"));

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();

    // Let's extend the lease for the client in such a way that
    // it will actually get different address. The response
    // should not be sent to this address but rather to ciaddr
    // as client still have ciaddr configured.
    resp->setYiaddr(IOAddress("192.0.1.13"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Copy hops value from the query.
    resp->setHops(req->getHops());

    // Set the testing mode.
    srv_->setSendResponsesToSource(true);

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Check that server responds to source address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set correctly when giaddr and ciaddr is zeroed in the received message
// and the new lease is acquired. The lease address is carried in the
// response message in the yiaddr field. In this case destination address
// of the response should be set to yiaddr if server supports direct responses
// to the client which doesn't have an address yet or broadcast if the server
// doesn't support direct responses.
TEST_F(Dhcpv4SrvTest, adjustIfaceDataSelect) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));

    // Let's clear the broadcast flag.
    req->setFlags(0);

    // This is a non-relayed message, so let's clear hops count.
    req->setHops(0);
    // The query is sent to the broadcast address in the Select state.
    req->setLocalAddr(IOAddress("255.255.255.255"));
    // The query has been received on the DHCPv4 server port 67.
    req->setLocalPort(DHCP4_SERVER_PORT);
    // Set the interface. The response should be sent via the same interface.
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();
    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.1.13"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Copy hops count.
    resp->setHops(req->getHops());

    // We want to test the case, when the server (packet filter) doesn't support
    // direct responses to the client which doesn't have an address yet. In
    // case, the server should send its response to the broadcast address.
    // We can control whether the current packet filter returns that its support
    // direct responses or not.
    test_config.setDirectResponse(false);

    // When running unit tests, the IfaceMgr is using the default Packet
    // Filtering class, PktFilterInet. This class does not support direct
    // responses to clients without address assigned. When giaddr and ciaddr
    // are zero and client has just got new lease, the assigned address is
    // carried in yiaddr. In order to send this address to the client,
    // server must broadcast its response.
    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Check that the response is sent to broadcast address as the
    // server doesn't have capability to respond directly.
    EXPECT_EQ("255.255.255.255", resp->getRemoteAddr().toText());

    // Although the query has been sent to the broadcast address, the
    // server should select a unicast address on the particular interface
    // as a source address for the response.
    EXPECT_EQ("192.0.2.3", resp->getLocalAddr().toText());

    // The response should be sent from the DHCPv4 server port.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());

    // The response should be sent via the same interface through which
    // query has been received.
    EXPECT_EQ("eth1", resp->getIface());
    EXPECT_EQ(ETH1_INDEX, resp->getIndex());

    // We also want to test the case when the server has capability to
    // respond directly to the client which is not configured. Server
    // makes decision whether it responds directly or broadcast its
    // response based on the capability reported by IfaceMgr. We can
    // control whether the current packet filter returns that it supports
    // direct responses or not.
    test_config.setDirectResponse(true);

    // Now we expect that the server will send its response to the
    // address assigned for the client.
    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    EXPECT_EQ("192.0.1.13", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to source address when the testing mode is enabled.
// Select cases: not testing mode were tested in adjustIfaceDataSelect.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressSelectSendToSourceTestingModeEnabled) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));

    // Let's clear the broadcast flag.
    req->setFlags(0);

    // This is a non-relayed message, so let's clear hops count.
    req->setHops(0);
    // The query is sent to the broadcast address in the Select state.
    req->setLocalAddr(IOAddress("255.255.255.255"));
    // The query has been received on the DHCPv4 server port 67.
    req->setLocalPort(DHCP4_SERVER_PORT);
    // Set the interface. The response should be sent via the same interface.
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);
    // Set remote address.
    req->setRemoteAddr(IOAddress("192.0.2.1"));

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();
    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.1.13"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Copy hops count.
    resp->setHops(req->getHops());

    // Disable direct responses.
    test_config.setDirectResponse(false);

    // Set the testing mode.
    srv_->setSendResponsesToSource(true);

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Check that server responds to source address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());

    // Enable direct responses.
    test_config.setDirectResponse(true);

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Check that server still responds to source address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to broadcast address when client set broadcast flag in its
// query. Client sets this flag to indicate that it can't receive direct
// responses from the server when it doesn't have its interface configured.
// Server must respect broadcast flag.
TEST_F(Dhcpv4SrvTest, adjustIfaceDataBroadcast) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // The query is sent to the broadcast address in the Select state.
    req->setLocalAddr(IOAddress("255.255.255.255"));
    // The query has been received on the DHCPv4 server port 67.
    req->setLocalPort(DHCP4_SERVER_PORT);
    // Set the interface. The response should be sent via the same interface.
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Let's set the broadcast flag.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();

    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.1.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Server must respond to broadcast address when client desired that
    // by setting the broadcast flag in its request.
    EXPECT_EQ("255.255.255.255", resp->getRemoteAddr().toText());

    // Although the query has been sent to the broadcast address, the
    // server should select a unicast address on the particular interface
    // as a source address for the response.
    EXPECT_EQ("192.0.2.3", resp->getLocalAddr().toText());

    // The response should be sent from the DHCPv4 server port.
    EXPECT_EQ(DHCP4_SERVER_PORT, resp->getLocalPort());

    // The response should be sent via the same interface through which
    // query has been received.
    EXPECT_EQ("eth1", resp->getIface());
    EXPECT_EQ(ETH1_INDEX, resp->getIndex());
}

// This test verifies that the destination address of the response message
// is set to source address when the testing mode is enabled.
// Broadcast case: not testing mode was tested in adjustIfaceDataBroadcast.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressBroadcastSendToSourceTestingModeEnabled) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // The query is sent to the broadcast address in the Select state.
    req->setLocalAddr(IOAddress("255.255.255.255"));
    // The query has been received on the DHCPv4 server port 67.
    req->setLocalPort(DHCP4_SERVER_PORT);
    // Set the interface. The response should be sent via the same interface.
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);
    // Set remote address.
    req->setRemoteAddr(IOAddress("192.0.2.1"));

    // Let's set the broadcast flag.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();

    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.1.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // Set the testing mode.
    srv_->setSendResponsesToSource(true);

    ASSERT_NO_THROW(srv_->adjustIfaceData(ex));

    // Check that server responds to source address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());
}

// This test verifies that the mandatory to copy fields and options
// are really copied into the response.
TEST_F(Dhcpv4SrvTest, initResponse) {
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));

    // Set fields which must be copied
    query->setIface("foo");
    query->setIndex(111);
    query->setHops(5);
    const HWAddr& hw = HWAddr::fromText("11:22:33:44:55:66:77:88", 10);
    HWAddrPtr hw_addr(new HWAddr(hw));
    query->setHWAddr(hw_addr);
    query->setGiaddr(IOAddress("10.10.10.10"));
    const HWAddr& src_hw = HWAddr::fromText("e4:ce:8f:12:34:56");
    HWAddrPtr src_hw_addr(new HWAddr(src_hw));
    query->setLocalHWAddr(src_hw_addr);
    const HWAddr& dst_hw = HWAddr::fromText("e8:ab:cd:78:9a:bc");
    HWAddrPtr dst_hw_addr(new HWAddr(dst_hw));
    query->setRemoteHWAddr(dst_hw_addr);
    query->setFlags(BOOTP_BROADCAST);

    // Add options which must be copied
    // client-id echo is optional
    // rai echo is done in relayAgentInfoEcho
    // Do subnet selection option
    const OptionDefinition& sbnsel_def = LibDHCP::DHO_SUBNET_SELECTION_DEF();
    OptionCustomPtr sbnsel(new OptionCustom(sbnsel_def, Option::V4));
    ASSERT_TRUE(sbnsel);
    sbnsel->writeAddress(IOAddress("192.0.2.3"));
    query->addOption(sbnsel);

    // Create exchange and get Response
    Dhcpv4Exchange ex = createExchange(query);
    Pkt4Ptr response = ex.getResponse();
    ASSERT_TRUE(response);

    // Check fields
    EXPECT_EQ("foo", response->getIface());
    EXPECT_EQ(111, response->getIndex());
    EXPECT_TRUE(response->getSiaddr().isV4Zero());
    EXPECT_TRUE(response->getCiaddr().isV4Zero());
    EXPECT_EQ(5, response->getHops());
    EXPECT_TRUE(hw == *response->getHWAddr());
    EXPECT_EQ(IOAddress("10.10.10.10"), response->getGiaddr());
    EXPECT_TRUE(src_hw == *response->getLocalHWAddr());
    EXPECT_TRUE(dst_hw == *response->getRemoteHWAddr());
    EXPECT_TRUE(BOOTP_BROADCAST == response->getFlags());

    // Check options (i.e., subnet selection option)
    OptionPtr resp_sbnsel = response->getOption(DHO_SUBNET_SELECTION);
    ASSERT_TRUE(resp_sbnsel);
    OptionCustomPtr resp_custom =
        boost::dynamic_pointer_cast<OptionCustom>(resp_sbnsel);
    ASSERT_TRUE(resp_custom);
    IOAddress subnet_addr("0.0.0.0");
    ASSERT_NO_THROW(subnet_addr = resp_custom->readAddress());
    EXPECT_EQ(IOAddress("192.0.2.3"), subnet_addr);
}

// This test verifies that recovered stashed agent options are not copied
// into responses.
TEST_F(Dhcpv4SrvTest, stashAgentOption) {
    // Get a DISCOVER with a RAI.
    Pkt4Ptr query = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(query->unpack());

    // Get Relay Agent Info from query...
    OptionPtr rai_query = query->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);

    // Create exchange and get Response.
    Dhcpv4Exchange ex = createExchange(query);
    Pkt4Ptr response = ex.getResponse();
    ASSERT_TRUE(response);

    // Get Relay Agent Info from response...
    OptionPtr rai_response = response->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_response);
    EXPECT_TRUE(rai_response->equals(rai_query));

    // Set the stash-agent-options.
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->
        addConfiguredGlobal("stash-agent-options", Element::create(true));
    CfgMgr::instance().commit();

    // Create exchange and get Response.
    ex = createExchange(query);
    response = ex.getResponse();
    ASSERT_TRUE(response);
    rai_response = response->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_response);
    EXPECT_TRUE(rai_response->equals(rai_query));

    // Put the query in the STASH_AGENT_OPTIONS class.
    query->addClass("STASH_AGENT_OPTIONS");

    // Retry: this time the RAI is not copied.
    ex = createExchange(query);
    response = ex.getResponse();
    ASSERT_TRUE(response);
    rai_response = response->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_response);
}

// This test verifies that the server identifier option is appended to
// a specified DHCPv4 message and the server identifier is correct.
TEST_F(Dhcpv4SrvTest, appendServerID) {
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    Dhcpv4Exchange ex = createExchange(query);
    Pkt4Ptr response = ex.getResponse();

    // Set a local address. It is required by the function under test
    // to create the Server Identifier option.
    query->setLocalAddr(IOAddress("192.0.3.1"));

    // Append the Server Identifier.
    ASSERT_NO_THROW(NakedDhcpv4Srv::appendServerID(ex));

    // Make sure that the option has been added.
    OptionPtr opt = response->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    ASSERT_TRUE(opt);
    OptionCustomPtr opt_serverid = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(opt_serverid);
    EXPECT_EQ("192.0.3.1", opt_serverid->readAddress().toText());
}

// Sanity check. Verifies that both Dhcpv4Srv and its derived
// class NakedDhcpv4Srv can be instantiated and destroyed.
TEST_F(Dhcpv4SrvTest, basic) {
    boost::shared_ptr<Dhcpv4Srv> srv;
    // Check that the base class can be instantiated
    ASSERT_NO_THROW(srv.reset(new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000, false,
                                            false)));

    // We have to close open sockets because further in this test we will
    // call the Dhcpv4Srv constructor again. This constructor will try to
    // set the appropriate packet filter class for IfaceMgr. This requires
    // that all sockets are closed.
    IfaceMgr::instance().closeSockets();

    srv_.reset();

    // Check that the derived class can be instantiated
    ASSERT_NO_THROW(
        srv_.reset(new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000)));
    // Close sockets again for the next test.
    IfaceMgr::instance().closeSockets();

    srv_.reset();

    ASSERT_NO_THROW(srv_.reset(new NakedDhcpv4Srv(0)));
}

// This test verifies the test_send_responses_to_source_ is false by default
// and sets by the KEA_TEST_SEND_RESPONSES_TO_SOURCE environment variable.
TEST_F(Dhcpv4SrvTest, testSendResponsesToSource) {
    srv_.reset();

    ASSERT_FALSE(std::getenv("KEA_TEST_SEND_RESPONSES_TO_SOURCE"));
    ASSERT_NO_THROW(
        srv_.reset(new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000)));
    EXPECT_FALSE(srv_->getSendResponsesToSource());
    ::setenv("KEA_TEST_SEND_RESPONSES_TO_SOURCE", "ENABLED", 1);

    srv_.reset();

    // Do not use ASSERT as we want unsetenv to be always called.
    EXPECT_NO_THROW(
        srv_.reset(new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000)));
    EXPECT_TRUE(srv_->getSendResponsesToSource());
    ::unsetenv("KEA_TEST_SEND_RESPONSES_TO_SOURCE");
}

// Verifies that DISCOVER message can be processed correctly,
// that the OFFER message generated in response is valid and
// contains necessary options.
//
// Note: this test focuses on the packet correctness. There
// are other tests that verify correctness of the allocation
// engine. See DiscoverBasic, DiscoverHint, DiscoverNoClientId
// and DiscoverInvalidHint.
TEST_F(Dhcpv4SrvTest, processDiscover) {
    testDiscoverRequest(DHCPDISCOVER);
}

// Verifies that REQUEST message can be processed correctly,
// that the OFFER message generated in response is valid and
// contains necessary options.
//
// Note: this test focuses on the packet correctness. There
// are other tests that verify correctness of the allocation
// engine. See DiscoverBasic, DiscoverHint, DiscoverNoClientId
// and DiscoverInvalidHint.
TEST_F(Dhcpv4SrvTest, processRequest) {
    testDiscoverRequest(DHCPREQUEST);
}

// Verifies that DHCPDISCOVERs are sanity checked correctly.
// 1. They must have either hardware address or client id
// 2. They must not have server id
TEST_F(Dhcpv4SrvTest, sanityCheckDiscover) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 1234));

    // Should throw, no hardware address or client id
    ASSERT_THROW_MSG(srv_->processDiscover(pkt), RFCViolation,
                     "Missing or useless client-id and no HW address"
                     " provided in message DHCPDISCOVER");

    // Add a hardware address. This should not throw.
    std::vector<uint8_t> data = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr(new HWAddr(data, HTYPE_ETHER));
    pkt->setHWAddr(hwaddr);
    ASSERT_NO_THROW(srv_->processDiscover(pkt));

    // Now let's make a new pkt with client-id only, it should not throw.
    pkt.reset(new Pkt4(DHCPDISCOVER, 1234));
    pkt->addOption(generateClientId());
    ASSERT_NO_THROW(srv_->processDiscover(pkt));

    // Now let's add a server-id. This should throw.
    const OptionDefinition& server_id_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();

    OptionCustomPtr server_id(new OptionCustom(server_id_def, Option::V4));
    server_id->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(server_id);
    EXPECT_THROW_MSG(srv_->processDiscover(pkt), RFCViolation,
                     "Server-id option was not expected,"
                     " but received in message DHCPDISCOVER");
}

// Verifies that DHCPREQEUSTs are sanity checked correctly.
// 1. They must have either hardware address or client id
// 2. They must have a requested address
// 3. They may or may not have a server id
TEST_F(Dhcpv4SrvTest, sanityCheckRequest) {
    Pkt4Ptr pkt(new Pkt4(DHCPREQUEST, 1234));

    // Should throw, no hardware address or client id
    ASSERT_THROW_MSG(srv_->processRequest(pkt), RFCViolation,
                     "Missing or useless client-id and no HW address"
                     " provided in message DHCPREQUEST");

    // Add a hardware address. Should not throw.
    std::vector<uint8_t> data = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr(new HWAddr(data, HTYPE_ETHER));
    pkt->setHWAddr(hwaddr);
    EXPECT_NO_THROW(srv_->processRequest(pkt));

    // Now let's add a requested address. This should not throw.
    const OptionDefinition& req_addr_def = LibDHCP::DHO_DHCP_REQUESTED_ADDRESS_DEF();
    OptionCustomPtr req_addr(new OptionCustom(req_addr_def, Option::V4));
    req_addr->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(req_addr);
    ASSERT_NO_THROW(srv_->processRequest(pkt));

    // Now let's make a new pkt with client-id only and an address, it should not throw.
    pkt.reset(new Pkt4(DHCPREQUEST, 1234));
    pkt->addOption(generateClientId());
    pkt->addOption(req_addr);
    ASSERT_NO_THROW(srv_->processRequest(pkt));

    // Now let's add a server-id. This should not throw.
    const OptionDefinition& server_id_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();

    OptionCustomPtr server_id(new OptionCustom(server_id_def, Option::V4));
    server_id->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(server_id);
    EXPECT_NO_THROW(srv_->processRequest(pkt));
}

// Verifies that DHCPDECLINEs are sanity checked correctly.
// 1. They must have either hardware address or client id
// 2. They must have a requested address
// 3. They may or may not have a server id
TEST_F(Dhcpv4SrvTest, sanityCheckDecline) {
    Pkt4Ptr pkt(new Pkt4(DHCPDECLINE, 1234));

    // Should throw, no hardware address or client id
    ASSERT_THROW_MSG(srv_->processDecline(pkt), RFCViolation,
                     "Missing or useless client-id and no HW address"
                     " provided in message DHCPDECLINE");

    // Add a hardware address. Should throw because of missing address.
    std::vector<uint8_t> data = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr(new HWAddr(data, HTYPE_ETHER));
    pkt->setHWAddr(hwaddr);
    ASSERT_THROW_MSG(srv_->processDecline(pkt), RFCViolation,
                    "Mandatory 'Requested IP address' option missing in DHCPDECLINE"
                    " sent from [hwtype=1 00:fe:fe:fe:fe:fe], cid=[no info], tid=0x4d2");

    // Now let's add a requested address. This should not throw.
    const OptionDefinition& req_addr_def = LibDHCP::DHO_DHCP_REQUESTED_ADDRESS_DEF();
    OptionCustomPtr req_addr(new OptionCustom(req_addr_def, Option::V4));
    req_addr->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(req_addr);
    ASSERT_NO_THROW(srv_->processDecline(pkt));

    // Now let's make a new pkt with client-id only and an address, it should not throw.
    pkt.reset(new Pkt4(DHCPDECLINE, 1234));
    pkt->addOption(generateClientId());
    pkt->addOption(req_addr);
    ASSERT_NO_THROW(srv_->processDecline(pkt));

    // Now let's add a server-id. This should not throw.
    const OptionDefinition& server_id_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();

    OptionCustomPtr server_id(new OptionCustom(server_id_def, Option::V4));
    server_id->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(server_id);
    EXPECT_NO_THROW(srv_->processDecline(pkt));
}

// Verifies that DHCPRELEASEs are sanity checked correctly.
// 1. They must have either hardware address or client id
// 2. They may or may not have a server id
TEST_F(Dhcpv4SrvTest, sanityCheckRelease) {
    Pkt4Ptr pkt(new Pkt4(DHCPRELEASE, 1234));

    // Should throw, no hardware address or client id
    ASSERT_THROW_MSG(srv_->processRelease(pkt), RFCViolation,
                     "Missing or useless client-id and no HW address"
                     " provided in message DHCPRELEASE");

    // Add a hardware address. Should not throw.
    std::vector<uint8_t> data = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr(new HWAddr(data, HTYPE_ETHER));
    pkt->setHWAddr(hwaddr);
    EXPECT_NO_THROW(srv_->processRelease(pkt));

    // Make a new pkt with client-id only.  Should not throw.
    pkt.reset(new Pkt4(DHCPRELEASE, 1234));
    pkt->addOption(generateClientId());
    ASSERT_NO_THROW(srv_->processRelease(pkt));

    // Now let's add a server-id. This should not throw.
    const OptionDefinition& server_id_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();

    OptionCustomPtr server_id(new OptionCustom(server_id_def, Option::V4));
    server_id->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(server_id);
    EXPECT_NO_THROW(srv_->processRelease(pkt));
}

// Verifies that DHCPINFORMs are sanity checked correctly.
// 1. They must have either hardware address or client id
// 2. They may or may not have requested address
// 3. They may or may not have a server id
TEST_F(Dhcpv4SrvTest, sanityCheckInform) {
    Pkt4Ptr pkt(new Pkt4(DHCPINFORM, 1234));

    // Should throw, no hardware address or client id
    ASSERT_THROW_MSG(srv_->processInform(pkt), RFCViolation,
                     "Missing or useless client-id and no HW address"
                     " provided in message DHCPINFORM");

    // Add a hardware address. Should not throw.
    std::vector<uint8_t> data = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr(new HWAddr(data, HTYPE_ETHER));
    pkt->setHWAddr(hwaddr);
    ASSERT_NO_THROW(srv_->processInform(pkt));

    // Now let's add a requested address. This should not throw.
    const OptionDefinition& req_addr_def = LibDHCP::DHO_DHCP_REQUESTED_ADDRESS_DEF();
    OptionCustomPtr req_addr(new OptionCustom(req_addr_def, Option::V4));
    req_addr->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(req_addr);
    ASSERT_NO_THROW(srv_->processInform(pkt));

    // Now let's make a new pkt with client-id only and an address, it should not throw.
    pkt.reset(new Pkt4(DHCPINFORM, 1234));
    pkt->addOption(generateClientId());
    pkt->addOption(req_addr);
    ASSERT_NO_THROW(srv_->processInform(pkt));

    // Now let's add a server-id. This should not throw.
    const OptionDefinition& server_id_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();

    OptionCustomPtr server_id(new OptionCustom(server_id_def, Option::V4));
    server_id->writeAddress(IOAddress("192.0.2.3"));
    pkt->addOption(server_id);
    EXPECT_NO_THROW(srv_->processInform(pkt));
}

// This test verifies that incoming DISCOVER can be handled properly, that an
// OFFER is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed very simple DISCOVER message with:
// - client-id option
//
// expected returned OFFER message:
// - copy of client-id
// - server-id
// - offered address
TEST_F(Dhcpv4SrvTest, DiscoverBasic) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_, true, true);

    // Check identifiers
    checkServerId(offer, srv_->getServerID());
    checkClientId(offer, clientid);
}

// This test verifies that OFFERs return expected valid lifetimes.
TEST_F(Dhcpv4SrvTest, DiscoverValidLifetime) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    // Struct for describing an individual lifetime test scenario
    struct LifetimeTest {
        // logged test description
        std::string description_;
        // lifetime hint (0 means not send dhcp-lease-time option)
        uint32_t hint;
        // expected returned value
        uint32_t expected;
    };

    // Test scenarios
    std::vector<LifetimeTest> tests = {
        { "default valid lifetime", 0, 1000 },
        { "specified valid lifetime", 1001, 1001 },
        { "too small valid lifetime", 100, 500 },
        { "too large valid lifetime", 2000, 1500 }
    };

    // Iterate over the test scenarios.
    for (auto const& test : tests) {
        SCOPED_TRACE(test.description_);

        // Create a discover packet to use
        Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
        dis->setRemoteAddr(IOAddress("192.0.2.1"));
        OptionPtr clientid = generateClientId();
        dis->addOption(clientid);
        dis->setIface("eth1");
        dis->setIndex(ETH1_INDEX);

        // Add dhcp-lease-time option.
        if (test.hint) {
            OptionUint32Ptr opt(new OptionUint32(Option::V4,
                                                 DHO_DHCP_LEASE_TIME,
                                                 test.hint));
            dis->addOption(opt);
        }

        // Pass it to the server and get an offer
        Pkt4Ptr offer = srv_->processDiscover(dis);

        // Check if we get response at all
        checkResponse(offer, DHCPOFFER, 1234);

        // Check that address was returned from proper range, that its lease
        // lifetime is correct and has the expected value.
        checkAddressParams(offer, subnet_, false, false, test.expected);

        // Check identifiers
        checkServerId(offer, srv_->getServerID());
        checkClientId(offer, clientid);
    }
}

// Check that option 58 and 59 are only included if they were specified
// (and calculate-tee-times = false) and the values are sane:
//  T2 is less than valid lft;  T1 is less than T2 (if given) or valid
// lft if T2 is not given.
TEST_F(Dhcpv4SrvTest, DiscoverTimers) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(1000);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    // Struct for describing an individual timer test scenario
    struct TimerTest {
        // logged test description
        std::string description_;
        // configured value for subnet's T1
        Triplet<uint32_t> cfg_t1_;
        // configured value for subnet's T1
        Triplet<uint32_t> cfg_t2_;
        // True if Offer should contain Subnet's T1 value
        bool exp_t1_;
        // True if Offer should contain Subnet's T2 value
        bool exp_t2_;
    };

    // Convenience constants
    bool T1 = true;
    bool T2 = true;

    // Test scenarios
    std::vector<TimerTest> tests = {
    {
        "T1:unspecified, T2:unspecified",
        unspecified, unspecified,
        // Client should neither.
        !T1, !T2
    },
    {
        "T1 unspecified, T2 < VALID",
        unspecified, valid_lft - 1,
        // Client should only get T2.
        !T1, T2
    },
    {
        "T1:unspecified, T2 = VALID",
        unspecified, valid_lft,
        // Client should get neither.
        !T1, !T2
    },
    {
        "T1:unspecified, T2 > VALID",
        unspecified, valid_lft + 1,
        // Client should get neither.
        !T1, !T2
    },

    {
        "T1 < VALID, T2:unspecified",
        valid_lft - 1, unspecified,
        // Client should only get T1.
        T1, !T2
    },
    {
        "T1 = VALID, T2:unspecified",
        valid_lft, unspecified,
        // Client should get neither.
        !T1, !T2
    },
    {
        "T1 > VALID, T2:unspecified",
        valid_lft + 1, unspecified,
        // Client should get neither.
        !T1, !T2
    },
    {
        "T1 < T2 < VALID",
        valid_lft - 2, valid_lft - 1,
        // Client should get both.
        T1, T2
    },
    {
        "T1 = T2 < VALID",
        valid_lft - 1, valid_lft - 1,
        // Client should only get T2.
        !T1, T2
    },
    {
        "T1 > T2 < VALID",
        valid_lft - 1, valid_lft - 2,
        // Client should only get T2.
        !T1, T2
    },
    {
       "T1 = T2 = VALID",
        valid_lft, valid_lft,
        // Client should get neither.
        !T1, !T2
    },
    {
       "T1 > VALID < T2, T2 > VALID",
        valid_lft + 1, valid_lft + 2,
        // Client should get neither.
        !T1, !T2
    }
    };

    // Create a discover packet to use
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Iterate over the test scenarios.
    for (auto const& test : tests) {
        {
            SCOPED_TRACE(test.description_);
            // Configure subnet's timer values
            subnet_->setT1(test.cfg_t1_);
            subnet_->setT2(test.cfg_t2_);

            // Discover/Offer exchange with the server
            Pkt4Ptr offer = srv_->processDiscover(dis);

            // Verify we have an offer
            checkResponse(offer, DHCPOFFER, 1234);

            // Verify the timers are as expected.
            checkAddressParams(offer, subnet_,
                               test.exp_t1_, test.exp_t2_);
        }
    }
}

// Check that option 58 and 59 are included when calculate-tee-times
// is enabled, but only when they are not explicitly specified via
// renew-timer and rebinding-timer.  This test does not check whether
// the subnet's for t1-percent and t2-percent are valid, as this is
// enforced by parsing and tested elsewhere.
TEST_F(Dhcpv4SrvTest, calculateTeeTimers) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(1000);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    // Struct for describing an individual timer test scenario
    struct TimerTest {
        // logged test description
        std::string description_;
        // configured value for subnet's T1
        Triplet<uint32_t> cfg_t1_;
        // configured value for subnet's T1
        Triplet<uint32_t> cfg_t2_;
        // configured value for subnet's t1_percent.
        double t1_percent_;
        // configured value for subnet's t2_percent.
        double t2_percent_;
        // expected value for T1 in server response.
        // A value of 0 means server should not have sent T1.
        uint32_t t1_exp_value_;
        // expected value for T2 in server response.
        // A value of 0 means server should not have sent T2.
        uint32_t t2_exp_value_;
    };

    // Convenience constant
    uint32_t not_expected = 0;

    // Test scenarios
    std::vector<TimerTest> tests = {
    {
        "T1 and T2 calculated",
        unspecified, unspecified,
        0.4, 0.8,
        400, 800
    },
    {
        "T1 and T2 specified insane",
        valid_lft + 1,  valid_lft + 2,
        0.4, 0.8,
        not_expected, not_expected
    },
    {
        "T1 should be calculated, T2 specified",
        unspecified, valid_lft - 1,
        0.4, 0.8,
        400, valid_lft - 1
    },
    {
        "T1 specified, T2 should be calculated",
        299, unspecified,
        0.4, 0.8,
        299, 800
    },
    {
        "T1 specified > T2, T2 should be calculated",
        valid_lft - 1, unspecified,
        0.4, 0.8,
        not_expected, 800
    }
    };

    // Calculation is enabled for all the scenarios.
    subnet_->setCalculateTeeTimes(true);

    // Create a discover packet to use
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Iterate over the test scenarios.
    for (auto const& test : tests) {
        {
            SCOPED_TRACE(test.description_);
            // Configure subnet's timer values
            subnet_->setT1(test.cfg_t1_);
            subnet_->setT2(test.cfg_t2_);

            subnet_->setT1Percent(test.t1_percent_);
            subnet_->setT2Percent(test.t2_percent_);

            // Discover/Offer exchange with the server
            Pkt4Ptr offer = srv_->processDiscover(dis);

            // Verify we have an offer
            checkResponse(offer, DHCPOFFER, 1234);

            // Check T1 timer
            OptionUint32Ptr opt = boost::dynamic_pointer_cast
                                  <OptionUint32> (offer->getOption(DHO_DHCP_RENEWAL_TIME));

            if (test.t1_exp_value_ == not_expected) {
                EXPECT_FALSE(opt) << "T1 present and shouldn't be";
            } else {
                ASSERT_TRUE(opt) << "Required T1 option missing or it has"
                                    " an unexpected type";
                EXPECT_EQ(opt->getValue(), test.t1_exp_value_);
            }

            // Check T2 timer
             opt = boost::dynamic_pointer_cast
                   <OptionUint32>(offer->getOption(DHO_DHCP_REBINDING_TIME));

            if (test.t2_exp_value_ == not_expected) {
                EXPECT_FALSE(opt) << "T2 present and shouldn't be";
            } else {
                ASSERT_TRUE(opt) << "Required T2 option missing or it has"
                                    " an unexpected type";
                EXPECT_EQ(opt->getValue(), test.t2_exp_value_);
            }
        }
    }
}

// This test verifies that incoming DISCOVER can be handled properly, that an
// OFFER is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed very simple DISCOVER message with:
// - client-id option
// - address set to specific value as hint, but that hint is invalid
//
// expected returned OFFER message:
// - copy of client-id
// - server-id
// - offered address (!= hint)
TEST_F(Dhcpv4SrvTest, DiscoverInvalidHint) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    IOAddress hint("10.1.2.3");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.107"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_, true, true);

    EXPECT_NE(offer->getYiaddr(), hint);

    // Check identifiers
    checkServerId(offer, srv_->getServerID());
    checkClientId(offer, clientid);
}

/// @todo: Add a test that client sends hint that is in pool, but currently
/// being used by a different client.

// This test checks that the server is offering different addresses to different
// clients in OFFERs. Please note that OFFER is not a guarantee that such
// an address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same offer as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. OFFER is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv4SrvTest, ManyDiscovers) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr dis1 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr dis2 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 2345));
    Pkt4Ptr dis3 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 3456));

    dis1->setRemoteAddr(IOAddress("192.0.2.1"));
    dis2->setRemoteAddr(IOAddress("192.0.2.2"));
    dis3->setRemoteAddr(IOAddress("192.0.2.3"));

    // Assign interfaces
    dis1->setIface("eth1");
    dis1->setIndex(ETH1_INDEX);
    dis2->setIface("eth1");
    dis2->setIndex(ETH1_INDEX);
    dis3->setIface("eth1");
    dis3->setIndex(ETH1_INDEX);

    // Different client-id sizes
    OptionPtr clientid1 = generateClientId(4); // length 4
    OptionPtr clientid2 = generateClientId(5); // length 5
    OptionPtr clientid3 = generateClientId(6); // length 6

    dis1->addOption(clientid1);
    dis2->addOption(clientid2);
    dis3->addOption(clientid3);

    // Pass it to the server and get an offer
    Pkt4Ptr offer1 = srv_->processDiscover(dis1);
    Pkt4Ptr offer2 = srv_->processDiscover(dis2);
    Pkt4Ptr offer3 = srv_->processDiscover(dis3);

    // Check if we get response at all
    checkResponse(offer1, DHCPOFFER, 1234);
    checkResponse(offer2, DHCPOFFER, 2345);
    checkResponse(offer3, DHCPOFFER, 3456);

    IOAddress addr1 = offer1->getYiaddr();
    IOAddress addr2 = offer2->getYiaddr();
    IOAddress addr3 = offer3->getYiaddr();

    // Check that the assigned address is indeed from the configured pool
    checkAddressParams(offer1, subnet_, true, true);
    checkAddressParams(offer2, subnet_, true, true);
    checkAddressParams(offer3, subnet_, true, true);

    // Check server-ids
    checkServerId(offer1, srv_->getServerID());
    checkServerId(offer2, srv_->getServerID());
    checkServerId(offer3, srv_->getServerID());
    checkClientId(offer1, clientid1);
    checkClientId(offer2, clientid2);
    checkClientId(offer3, clientid3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1, addr2);
    EXPECT_NE(addr2, addr3);
    EXPECT_NE(addr3, addr1);
    cout << "Offered address to client1=" << addr1 << endl;
    cout << "Offered address to client2=" << addr2 << endl;
    cout << "Offered address to client3=" << addr3 << endl;
}

// Checks whether echoing back client-id is controllable, i.e.
// whether the server obeys echo-client-id and sends (or not)
// client-id
TEST_F(Dhcpv4SrvTest, discoverEchoClientId) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);
    checkClientId(offer, clientid);

    ConstSrvConfigPtr cfg = CfgMgr::instance().getCurrentCfg();
    const Subnet4Collection* subnets = cfg->getCfgSubnets4()->getAll();
    ASSERT_EQ(1, subnets->size());
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(*subnets->begin());
    CfgMgr::instance().getStagingCfg()->setEchoClientId(false);
    CfgMgr::instance().commit();

    offer = srv_->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);
    checkClientId(offer, clientid);
}

// This test verifies that incoming DISCOVER can reuse an existing lease.
TEST_F(Dhcpv4SrvTest, DiscoverCache) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Enable lease reuse.
    subnet_->setCacheThreshold(.1);

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = subnet_->getValid();
    const int delta = 100;
    const time_t temp_timestamp = time(NULL) - delta;

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              &client_id_->getClientId()[0], client_id_->getClientId().size(),
                              temp_valid, temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set.
    // Constructed lease looks as if it was assigned 100 seconds ago
    EXPECT_EQ(l->valid_lft_, temp_valid);
    EXPECT_EQ(l->cltt_, temp_timestamp);

    // Let's create a DISCOVER
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress(addr));
    dis->addOption(clientid);
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    dis->setHWAddr(hwaddr2);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check valid lifetime (temp_valid - age)
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(offer->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_NEAR(subnet_->getValid() - delta, opt->getValue(), 1);

    // Check address
    EXPECT_EQ(addr, offer->getYiaddr());

    // Check T1
    opt = boost::dynamic_pointer_cast<
        OptionUint32>(offer->getOption(DHO_DHCP_RENEWAL_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->getValue(), subnet_->getT1());

    // Check T2
    opt = boost::dynamic_pointer_cast<
        OptionUint32>(offer->getOption(DHO_DHCP_REBINDING_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->getValue(), subnet_->getT2());

    // Check identifiers
    checkServerId(offer, srv_->getServerID());
    checkClientId(offer, clientid);
}

// Check that option 58 and 59 are not included if they are not specified.
TEST_F(Dhcpv4SrvTest, RequestNoTimers) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Recreate a subnet but set T1 and T2 to "unspecified".
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              Triplet<uint32_t>(),
                              Triplet<uint32_t>(),
                              3000,
                              subnet_->getID());
    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    // Pass it to the server and get an ACK.
    Pkt4Ptr ack = srv_->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);

    // T1 and T2 timers must not be present.
    checkAddressParams(ack, subnet_, false, false);

    // Check identifiers
    checkServerId(ack, srv_->getServerID());
    checkClientId(ack, clientid);
}

// Checks whether echoing back client-id is controllable
TEST_F(Dhcpv4SrvTest, requestEchoClientId) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Pass it to the server and get ACK
    Pkt4Ptr ack = srv_->processRequest(dis);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    checkClientId(ack, clientid);

    ConstSrvConfigPtr cfg = CfgMgr::instance().getCurrentCfg();
    const Subnet4Collection* subnets = cfg->getCfgSubnets4()->getAll();
    ASSERT_EQ(1, subnets->size());
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(*subnets->begin());
    CfgMgr::instance().getStagingCfg()->setEchoClientId(false);
    CfgMgr::instance().commit();

    ack = srv_->processRequest(dis);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    checkClientId(ack, clientid);
}

// This test verifies that incoming (positive) REQUEST/Renewing can be handled properly, that a
// REPLY is generated, that the response has an address and that address
// really belongs to the configured pool and that lease is actually renewed.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA that includes IAADDR
// - lease is actually renewed in LeaseMgr
TEST_F(Dhcpv4SrvTest, RenewBasic) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              &client_id_->getClientId()[0], client_id_->getClientId().size(),
                              temp_valid, temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set.
    // Constructed lease looks as if it was assigned 10 seconds ago
    EXPECT_EQ(l->valid_lft_, temp_valid);
    EXPECT_EQ(l->cltt_, temp_timestamp);

    // Let's create a RENEW
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress(addr));
    req->setYiaddr(addr);
    req->setCiaddr(addr); // client's address
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    req->setHWAddr(hwaddr2);

    req->addOption(clientid);
    req->addOption(srv_->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv_->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(addr, ack->getYiaddr());

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(ack, subnet_, true, true);

    // Check identifiers
    checkServerId(ack, srv_->getServerID());
    checkClientId(ack, clientid);

    // Check that the lease is really in the database
    l = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt were really updated
    EXPECT_EQ(l->valid_lft_, subnet_->getValid());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_NEAR(cltt, expected, 1);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));
}

// Renew*Lifetime common code.
namespace {

struct ctx {
    Dhcpv4SrvTest* test;
    NakedDhcpv4Srv* srv;
    const IOAddress& addr;
    const uint32_t temp_valid;
    const time_t temp_timestamp;
    OptionPtr clientid;
    HWAddrPtr hwaddr;
    Lease4Ptr used;
    Lease4Ptr l;
    OptionPtr opt;
    Pkt4Ptr req;
    Pkt4Ptr ack;
};

void prepare(struct ctx& c) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(c.test->subnet_->inPool(Lease::TYPE_V4, c.addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    c.hwaddr.reset(new HWAddr(hwaddr_data, sizeof(hwaddr_data), HTYPE_ETHER));

    c.used.reset(new Lease4(c.addr, c.hwaddr,
                            &c.test->client_id_->getClientId()[0],
                            c.test->client_id_->getClientId().size(),
                            c.temp_valid, c.temp_timestamp,
                            c.test->subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(c.used));

    // Check that the lease is really in the database
    c.l = LeaseMgrFactory::instance().getLease4(c.addr);
    ASSERT_TRUE(c.l);

    // Check that valid and cltt really set.
    // Constructed lease looks as if it was assigned 10 seconds ago
    EXPECT_EQ(c.l->valid_lft_, c.temp_valid);
    EXPECT_EQ(c.l->cltt_, c.temp_timestamp);

    // Set the valid lifetime interval.
    c.test->subnet_->setValid(Triplet<uint32_t>(2000, 3000, 4000));

    // Let's create a RENEW
    c.req.reset(new Pkt4(DHCPREQUEST, 1234));
    c.req->setRemoteAddr(IOAddress(c.addr));
    c.req->setYiaddr(c.addr);
    c.req->setCiaddr(c.addr); // client's address
    c.req->setIface("eth0");
    c.req->setIndex(ETH0_INDEX);
    c.req->setHWAddr(c.hwaddr);

    c.req->addOption(c.clientid);
    c.req->addOption(c.srv->getServerID());

    if (c.opt) {
        c.req->addOption(c.opt);
    }

    // Pass it to the server and hope for a REPLY
    c.ack = c.srv->processRequest(c.req);

    // Check if we get response at all
    c.test->checkResponse(c.ack, DHCPACK, 1234);
    EXPECT_EQ(c.addr, c.ack->getYiaddr());

    // Check identifiers
    c.test->checkServerId(c.ack, c.srv->getServerID());
    c.test->checkClientId(c.ack, c.clientid);

    // Check that the lease is really in the database
    c.l = c.test->checkLease(c.ack, c.clientid, c.req->getHWAddr(), c.addr);
    ASSERT_TRUE(c.l);
}

// This test verifies that renewal returns the default valid lifetime
// when the client does not specify a value.
TEST_F(Dhcpv4SrvTest, RenewDefaultLifetime) {

    struct ctx c = {
        this,                           // test
        srv_.get(),                     // srv
        IOAddress("192.0.2.106"),       // addr
        100,                            // temp_valid
        time(NULL) - 10,                // temp_timestamp
        // Generate client-id also sets client_id_ member
        generateClientId(),             // clientid
        HWAddrPtr(),                    // hwaddr
        Lease4Ptr(),                    // used
        Lease4Ptr(),                    // l
        OptionPtr(),                    // opt
        Pkt4Ptr(),                      // req
        Pkt4Ptr()                       // acka
    };

    prepare(c);

    // There is no valid lifetime hint so the default will be returned.

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(c.ack, subnet_, true, true, subnet_->getValid());

    // Check that valid and cltt were really updated
    EXPECT_EQ(c.l->valid_lft_, subnet_->getValid());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(c.l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_NEAR(cltt, expected, 1);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(c.addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));
}

// This test verifies that renewal returns the specified valid lifetime
// when the client adds an in-bound hint in the DISCOVER.
TEST_F(Dhcpv4SrvTest, RenewHintLifetime) {

    struct ctx c = {
        this,                           // test
        srv_.get(),                     // srv
        IOAddress("192.0.2.106"),       // addr
        100,                            // temp_valid
        time(NULL) - 10,                // temp_timestamp
        // Generate client-id also sets client_id_ member
        generateClientId(),             // clientid
        HWAddrPtr(),                    // hwaddr
        Lease4Ptr(),                    // used
        Lease4Ptr(),                    // l
        OptionPtr(),                    // opt
        Pkt4Ptr(),                      // req
        Pkt4Ptr()                       // acka
    };

    // Add a dhcp-lease-time with an in-bound valid lifetime hint
    // which will be returned in the OFFER.
    uint32_t hint = 3001;
    c.opt.reset(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, hint));

    prepare(c);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(c.ack, subnet_, true, true, hint);

    // Check that valid and cltt were really updated
    EXPECT_EQ(c.l->valid_lft_, hint);

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(c.l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_NEAR(cltt, expected, 1);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(c.addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));
}

// This test verifies that renewal returns the min valid lifetime
// when the client adds a too small hint in the DISCOVER.
TEST_F(Dhcpv4SrvTest, RenewMinLifetime) {

    struct ctx c = {
        this,                           // test
        srv_.get(),                     // srv
        IOAddress("192.0.2.106"),       // addr
        100,                            // temp_valid
        time(NULL) - 10,                // temp_timestamp
        // Generate client-id also sets client_id_ member
        generateClientId(),             // clientid
        HWAddrPtr(),                    // hwaddr
        Lease4Ptr(),                    // used
        Lease4Ptr(),                    // l
        OptionPtr(),                    // opt
        Pkt4Ptr(),                      // req
        Pkt4Ptr()                       // acka
    };

    // Add a dhcp-lease-time with too small valid lifetime hint.
    // The min valid lifetime will be returned in the OFFER.
    c.opt.reset(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 1000));

    prepare(c);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    // Note that T2 should be false for a reason which does not matter...
    checkAddressParams(c.ack, subnet_, true, false, subnet_->getValid().getMin());

    // Check that valid and cltt were really updated
    EXPECT_EQ(c.l->valid_lft_, subnet_->getValid().getMin());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(c.l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_NEAR(cltt, expected, 1);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(c.addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));
}

// This test verifies that renewal returns the max valid lifetime
// when the client adds a too large hint in the DISCOVER.
TEST_F(Dhcpv4SrvTest, RenewMaxLifetime) {

    struct ctx c = {
        this,                           // test
        srv_.get(),                     // srv
        IOAddress("192.0.2.106"),       // addr
        100,                            // temp_valid
        time(NULL) - 10,                // temp_timestamp
        // Generate client-id also sets client_id_ member
        generateClientId(),             // clientid
        HWAddrPtr(),                    // hwaddr
        Lease4Ptr(),                    // used
        Lease4Ptr(),                    // l
        OptionPtr(),                    // opt
        Pkt4Ptr(),                      // req
        Pkt4Ptr()                       // acka
    };

    // Add a dhcp-lease-time with too large valid lifetime hint.
    // The max valid lifetime will be returned in the OFFER.
    c.opt.reset(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME, 5000));

    prepare(c);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(c.ack, subnet_, true, true, subnet_->getValid().getMax());

    // Check that valid and cltt were really updated
    EXPECT_EQ(c.l->valid_lft_, subnet_->getValid().getMax());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(c.l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_NEAR(cltt, expected, 1);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(c.addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));
}

} // end of Renew*Lifetime

// This test verifies that incoming RENEW can reuse an existing lease.
TEST_F(Dhcpv4SrvTest, RenewCache) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Enable lease reuse.
    subnet_->setCacheThreshold(.1);

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = subnet_->getValid();
    const int delta = 100;
    const time_t temp_timestamp = time(NULL) - delta;

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              &client_id_->getClientId()[0], client_id_->getClientId().size(),
                              temp_valid, temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set.
    // Constructed lease looks as if it was assigned 100 seconds ago
    EXPECT_EQ(l->valid_lft_, temp_valid);
    EXPECT_EQ(l->cltt_, temp_timestamp);

    // Let's create a RENEW
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress(addr));
    req->setYiaddr(addr);
    req->setCiaddr(addr); // client's address
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);

    req->addOption(clientid);
    req->setHWAddr(hwaddr2);

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv_->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);

    // Check valid lifetime (temp_valid - age)
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(ack->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_NEAR(subnet_->getValid() - delta, opt->getValue(), 1);

    // Check address
    EXPECT_EQ(addr, ack->getYiaddr());

    // Check T1
    opt = boost::dynamic_pointer_cast<
        OptionUint32>(ack->getOption(DHO_DHCP_RENEWAL_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->getValue(), subnet_->getT1());

    // Check T2
    opt = boost::dynamic_pointer_cast<
        OptionUint32>(ack->getOption(DHO_DHCP_REBINDING_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->getValue(), subnet_->getT2());

    // Check identifiers
    checkServerId(ack, srv_->getServerID());
    checkClientId(ack, clientid);

    // Check that the lease is really in the database
    Lease4Ptr lease = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(lease);

    // Check that the lease was not updated
    EXPECT_EQ(temp_timestamp, lease->cltt_);
}

// Exercises Dhcpv4Srv::buildCfgOptionList().
TEST_F(Dhcpv4SrvTest, buildCfgOptionsList) {
    configureServerIdentifier();
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr query(new Pkt4(DHCPREQUEST, 1234));
    query->addOption(generateClientId());
    query->setHWAddr(generateHWAddr(6));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);

    {
        SCOPED_TRACE("Pool value");

        // Server id should come from subnet2's first pool.
        buildCfgOptionTest(IOAddress("192.0.2.254"), query, IOAddress("192.0.2.101"), IOAddress("192.0.2.254"));
    }

    {
        SCOPED_TRACE("Subnet value");

        // Server id should come from subnet3.
        buildCfgOptionTest(IOAddress("192.0.3.254"), query, IOAddress("192.0.3.101"), IOAddress("192.0.3.254"));
    }

    {
        SCOPED_TRACE("Shared-network value");

        // Server id should come from subnet4's shared-network.
        buildCfgOptionTest(IOAddress("192.0.4.254"), query, IOAddress("192.0.4.101"), IOAddress("192.0.4.254"));
    }

    {
        SCOPED_TRACE("Client-class value");

        Pkt4Ptr query_with_classes(new Pkt4(DHCPREQUEST, 1234));
        query_with_classes->addOption(generateClientId());
        query_with_classes->setHWAddr(generateHWAddr(6));
        query_with_classes->setIface("eth0");
        query_with_classes->setIndex(ETH0_INDEX);
        query_with_classes->addClass("foo");

        // Server id should come from subnet5's client-class value.
        buildCfgOptionTest(IOAddress("192.0.5.254"), query_with_classes, IOAddress("192.0.5.101"), IOAddress("192.0.5.254"));
    }

    {
        SCOPED_TRACE("Global value if client class does not define it");

        Pkt4Ptr query_with_classes(new Pkt4(DHCPREQUEST, 1234));
        query_with_classes->addOption(generateClientId());
        query_with_classes->setHWAddr(generateHWAddr(6));
        query_with_classes->setIface("eth0");
        query_with_classes->setIndex(ETH0_INDEX);
        query_with_classes->addClass("bar");

        // Server id should be global value as subnet6's client-class does not define it.
        buildCfgOptionTest(IOAddress("10.0.0.254"), query_with_classes, IOAddress("192.0.6.101"), IOAddress("192.0.6.100"));
    }

    {
        SCOPED_TRACE("Global value if client class does not define any option");

        Pkt4Ptr query_with_classes(new Pkt4(DHCPREQUEST, 1234));
        query_with_classes->addOption(generateClientId());
        query_with_classes->setHWAddr(generateHWAddr(6));
        query_with_classes->setIface("eth0");
        query_with_classes->setIndex(ETH0_INDEX);
        query_with_classes->addClass("xyz");

        // Server id should be global value as subnet7's client-class does not define any option.
        buildCfgOptionTest(IOAddress("10.0.0.254"), query_with_classes, IOAddress("192.0.7.101"), IOAddress("192.0.7.100"));
    }

    {
        SCOPED_TRACE("Global value");

        // Server id should be global value as lease is from subnet2's second pool.
        buildCfgOptionTest(IOAddress("10.0.0.254"), query, IOAddress("192.0.2.201"), IOAddress("10.0.0.254"));
    }
}

// This test verifies that the logic which matches server identifier in the
// received message with server identifiers used by a server works correctly:
// - a message with no server identifier is accepted,
// - a message with a server identifier which matches one of the server
// identifiers used by a server is accepted,
// - a message with a server identifier which doesn't match any server
// identifier used by a server, is not accepted.
// - a message with a server identifier which doesn't match any server
// identifier used by a server is accepted when the DHCP Server Identifier
// option is configured to be ignored.
TEST_F(Dhcpv4SrvTest, acceptServerId) {
    configureServerIdentifier();
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr pkt(new Pkt4(DHCPREQUEST, 1234));
    // If no server identifier option is present, the message is always
    // accepted.
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Create definition of the server identifier option.
    OptionDefinition def("server-identifier", DHO_DHCP_SERVER_IDENTIFIER,
                         DHCP4_OPTION_SPACE, "ipv4-address", false);

    // Add a server identifier option which doesn't match server ids being
    // used by the server. The accepted server ids are the IPv4 addresses
    // configured on the interfaces. The 10.1.2.3 is not configured on
    // any interfaces.
    OptionCustomPtr other_serverid(new OptionCustom(def, Option::V4));
    other_serverid->writeAddress(IOAddress("10.1.2.3"));
    pkt->addOption(other_serverid);
    EXPECT_FALSE(srv_->acceptServerId(pkt));

    // Configure the DHCP Server Identifier to be ignored.
    ASSERT_FALSE(CfgMgr::instance().getCurrentCfg()->getIgnoreServerIdentifier());
    CfgMgr::instance().getCurrentCfg()->setIgnoreServerIdentifier(true);
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Restore the ignore-dhcp-server-identifier compatibility flag.
    CfgMgr::instance().getCurrentCfg()->setIgnoreServerIdentifier(false);
    EXPECT_FALSE(srv_->acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on eth1 interface.
    // A DHCPv4 message holding this server identifier should be accepted.
    OptionCustomPtr eth1_serverid(new OptionCustom(def, Option::V4));
    eth1_serverid->writeAddress(IOAddress("192.0.2.3"));
    ASSERT_NO_THROW(pkt->addOption(eth1_serverid));
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on eth0 interface.
    // A DHCPv4 message holding this server identifier should be accepted.
    OptionCustomPtr eth0_serverid(new OptionCustom(def, Option::V4));
    eth0_serverid->writeAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(pkt->addOption(eth0_serverid));
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on subnet3.
    // A DHCPv4 message holding this server identifier should be accepted.
    OptionCustomPtr subnet_serverid(new OptionCustom(def, Option::V4));
    subnet_serverid->writeAddress(IOAddress("192.0.3.254"));
    ASSERT_NO_THROW(pkt->addOption(subnet_serverid));
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on shared network1.
    // A DHCPv4 message holding this server identifier should be accepted.
    OptionCustomPtr network_serverid(new OptionCustom(def, Option::V4));
    network_serverid->writeAddress(IOAddress("192.0.4.254"));
    ASSERT_NO_THROW(pkt->addOption(network_serverid));
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on client class.
    // A DHCPv4 message holding this server identifier should be accepted.
    Pkt4Ptr pkt_with_classes(new Pkt4(DHCPREQUEST, 1234));
    OptionCustomPtr class_serverid(new OptionCustom(def, Option::V4));
    class_serverid->writeAddress(IOAddress("192.0.5.254"));
    ASSERT_NO_THROW(pkt_with_classes->addOption(class_serverid));
    pkt_with_classes->addClass("foo");
    EXPECT_TRUE(srv_->acceptServerId(pkt_with_classes));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt_with_classes->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on global level.
    // The configured class does not define the server id option.
    // A DHCPv4 message holding this server identifier should be accepted.
    Pkt4Ptr pkt_with_classes_option_not_defined(new Pkt4(DHCPREQUEST, 1234));
    OptionCustomPtr global_serverid(new OptionCustom(def, Option::V4));
    global_serverid->writeAddress(IOAddress("10.0.0.254"));
    ASSERT_NO_THROW(pkt_with_classes_option_not_defined->addOption(global_serverid));
    pkt_with_classes_option_not_defined->addClass("bar");
    EXPECT_TRUE(srv_->acceptServerId(pkt_with_classes_option_not_defined));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt_with_classes_option_not_defined->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on global level.
    // The configured class does not define any option.
    // A DHCPv4 message holding this server identifier should be accepted.
    Pkt4Ptr pkt_with_classes_no_options(new Pkt4(DHCPREQUEST, 1234));
    ASSERT_NO_THROW(pkt_with_classes_no_options->addOption(global_serverid));
    pkt_with_classes_no_options->addClass("xyz");
    EXPECT_TRUE(srv_->acceptServerId(pkt_with_classes_no_options));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt_with_classes_no_options->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on global level.
    // A DHCPv4 message holding this server identifier should be accepted.
    ASSERT_NO_THROW(pkt->addOption(global_serverid));
    EXPECT_TRUE(srv_->acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    OptionBuffer override_server_id_buf(IOAddress("10.0.0.128").toBytes());

    // Create RAI option.
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));
    OptionPtr rai_override_server_id(new Option(Option::V4,
                                                RAI_OPTION_SERVER_ID_OVERRIDE,
                                                override_server_id_buf));
    rai->addOption(rai_override_server_id);

    // Add a server id being an IPv4 address matching RAI sub-option 11
    // (RAI_OPTION_SERVER_ID_OVERRIDE).
    // A DHCPv4 message holding this server identifier should be accepted.
    Pkt4Ptr pkt_with_override_server_id(new Pkt4(DHCPREQUEST, 1234));
    OptionCustomPtr override_serverid(new OptionCustom(def, Option::V4));
    override_serverid->writeAddress(IOAddress("10.0.0.128"));

    ASSERT_NO_THROW(pkt_with_override_server_id->addOption(override_serverid));
    ASSERT_NO_THROW(pkt_with_override_server_id->addOption(rai));
    EXPECT_TRUE(srv_->acceptServerId(pkt_with_override_server_id));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt_with_override_server_id->delOption(DHO_DHCP_SERVER_IDENTIFIER));
}

// @todo: Implement tests for rejecting renewals

// This test verifies if the sanityCheck() really checks options presence.
TEST_F(Dhcpv4SrvTest, sanityCheck) {

    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    pkt->setHWAddr(generateHWAddr(6));

    // Server-id is optional for information-request, so
    EXPECT_NO_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::OPTIONAL));

    // Empty packet, no server-id
    EXPECT_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::MANDATORY),
                 RFCViolation);

    pkt->addOption(srv_->getServerID());

    // Server-id is mandatory and present = no exception
    EXPECT_NO_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::MANDATORY));

    // Server-id is forbidden, but present => exception
    EXPECT_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::FORBIDDEN),
                 RFCViolation);

    // There's no client-id and no HWADDR. Server needs something to
    // identify the client
    pkt->setHWAddr(generateHWAddr(0));
    EXPECT_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::MANDATORY),
                 RFCViolation);
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {
namespace test {

void
Dhcpv4SrvTest::relayAgentInfoEcho() {
    IfaceMgrTestConfig test_config(true);

    // Use of the captured DHCPDISCOVER packet requires that
    // subnet 10.254.226.0/24 is in use, because this packet
    // contains the giaddr which belongs to this subnet and
    // this giaddr is used to select the subnet
    configure(CONFIGS[0]);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv_->fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    OptionPtr rai_query = dis->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);

    // Get Relay Agent Info from response...
    OptionPtr rai_response = offer->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_response);

    EXPECT_TRUE(rai_response->equals(rai_query));
}

void
Dhcpv4SrvTest::badRelayAgentInfoEcho() {
    IfaceMgrTestConfig test_config(true);
    // Use of the captured DHCPDISCOVER packet requires that
    // subnet 10.254.226.0/24 is in use, because this packet
    // contains the giaddr which belongs to this subnet and
    // this giaddr is used to select the subnet
    configure(CONFIGS[0]);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with a sub-option which does not
    // fit in the option. Unpacking it gave an empty option which is
    // supposed to not be echoed back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::captureBadRelayedDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv_->fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    OptionPtr rai_query = dis->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);
    ASSERT_EQ(2, rai_query->len());

    // Get Relay Agent Info from response...
    OptionPtr rai_response = offer->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_FALSE(rai_response);
}

void
Dhcpv4SrvTest::portsClientPort() {
    IfaceMgrTestConfig test_config(true);

    // By default te client port is supposed to be zero.
    EXPECT_EQ(0, srv_->client_port_);

    // Use of the captured DHCPDISCOVER packet requires that
    // subnet 10.254.226.0/24 is in use, because this packet
    // contains the giaddr which belongs to this subnet and
    // this giaddr is used to select the subnet
    configure(CONFIGS[0]);
    srv_->client_port_ = 1234;

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv_->fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    EXPECT_EQ(srv_->client_port_, offer->getRemotePort());
}

void
Dhcpv4SrvTest::portsServerPort() {
    IfaceMgrTestConfig test_config(true);

    // Do not use DHCP4_SERVER_PORT here as 0 means don't open sockets.
    EXPECT_EQ(0, srv_->server_port_);

    // Use of the captured DHCPDISCOVER packet requires that
    // subnet 10.254.226.0/24 is in use, because this packet
    // contains the giaddr which belongs to this subnet and
    // this giaddr is used to select the subnet
    configure(CONFIGS[0]);
    srv_->server_port_ = 1234;

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv_->fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    EXPECT_EQ(srv_->server_port_, offer->getLocalPort());
}

/// @brief Remove TLS parameters from configuration element.
void removeTlsParameters(ConstElementPtr elem) {
    if (elem) {
        ElementPtr mutable_elem = boost::const_pointer_cast<Element>(elem);
        std::vector<std::string> tls_parameters= {
            "trust-anchor",
            "cert-file",
            "key-file",
            "cipher-list"
        };
        for (auto const& parameter : tls_parameters) {
            mutable_elem->remove(parameter);
        }
    }
}

/// @brief Remove authentication files.
void removeAuthFiles(ConstElementPtr elem) {
    if (!elem) {
        return;
    }
    ConstElementPtr auth = elem->get("authentication");
    if (!auth) {
        return;
    }
    ConstElementPtr clients = auth->get("clients");
    if (!clients || clients->empty()) {
        return;
    }
    ElementPtr mutable_clients = boost::const_pointer_cast<Element>(clients);
    for (;;) {
        bool found = false;
        for (unsigned i = 0; i < clients->size(); ++i) {
            ConstElementPtr client = clients->get(i);
            if (client->contains("user-file") ||
                client->contains("password-file")) {
                mutable_clients->remove(i);
                found = true;
                break;
            }
        }
        if (!found) {
            return;
        }
    }
}

void
Dhcpv4SrvTest::loadConfigFile(const string& path) {
    CfgMgr::instance().clear();

    LibDHCP::clearRuntimeOptionDefs();

    IfaceMgrTestConfig test_config(true);

    // Do not use DHCP4_SERVER_PORT here as 0 means don't open sockets.
    EXPECT_EQ(0, srv_->server_port_);

    ConfigBackendDHCPv4Mgr::instance().registerBackendFactory("mysql",
            [](const db::DatabaseConnection::ParameterMap&) -> ConfigBackendDHCPv4Ptr {
                return (ConfigBackendDHCPv4Ptr());
            });

    ConfigBackendDHCPv4Mgr::instance().registerBackendFactory("postgresql",
            [](const db::DatabaseConnection::ParameterMap&) -> ConfigBackendDHCPv4Ptr {
                return (ConfigBackendDHCPv4Ptr());
            });

    Parser4Context parser;
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parser.parseFile(path, Parser4Context::PARSER_DHCP4));
    ASSERT_TRUE(json);

    // Check the logic next.
    ConstElementPtr dhcp4 = json->get("Dhcp4");
    ASSERT_TRUE(dhcp4);
    ElementPtr mutable_config = boost::const_pointer_cast<Element>(dhcp4);
    mutable_config->set(string("hooks-libraries"), Element::createList());
    // Remove TLS parameters
    ConstElementPtr hosts = dhcp4->get("hosts-database");
    if (hosts) {
        removeTlsParameters(hosts);
        hosts = redactConfig(hosts, { "*" }, "keatest");
        mutable_config->set("hosts-database", hosts);
    }
    hosts = dhcp4->get("hosts-databases");
    if (hosts) {
        for (auto const& host : hosts->listValue()) {
            removeTlsParameters(host);
        }
        hosts = redactConfig(hosts, { "*" }, "keatest");
        mutable_config->set("hosts-databases", hosts);
    }
    // Remove authentication clients using files.
    ConstElementPtr control_sockets = dhcp4->get("control-socket");
    if (control_sockets) {
        removeAuthFiles(control_sockets);
        control_sockets = redactConfig(control_sockets, { "*" }, "-----");
        mutable_config->set("control-socket", control_sockets);
    }
    control_sockets = dhcp4->get("control-sockets");
    if (control_sockets) {
        for (unsigned i = 0; i < control_sockets->size(); ++i) {
            removeAuthFiles(control_sockets->get(i));
        }
        control_sockets = redactConfig(control_sockets, { "*" }, "-----");
        mutable_config->set("control-sockets", control_sockets);
    }

    ASSERT_NO_THROW(Dhcpv4SrvTest::configure(dhcp4->str(), true, true, true, true));

    LeaseMgrFactory::destroy();
    HostMgr::create();

    TimerMgr::instance()->unregisterTimers();

    // Close the command socket (if it exists).
    UnixCommandMgr::instance().closeCommandSocket();

    // Reset CommandMgr IO service.
    UnixCommandMgr::instance().setIOService(IOServicePtr());

    // Reset DatabaseConnection IO service.
    DatabaseConnection::setIOService(IOServicePtr());

    // Reset ProcessSpawn IO service.
    ProcessSpawn::setIOService(IOServicePtr());
}

/// @brief Class which handles initialization of database
/// backend for testing configurations.
class DBInitializer {
    public:
        /// @brief Constructor.
        ///
        /// Created database schema.
        DBInitializer() {
#if defined (HAVE_MYSQL)
            db::test::createMySQLSchema();
#endif
#if defined (HAVE_PGSQL)
            db::test::createPgSQLSchema();
#endif
        }

        /// @brief Destructor.
        ///
        /// Destroys database schema.
        ~DBInitializer() {
#if defined (HAVE_MYSQL)
            db::test::destroyMySQLSchema();
#endif
#if defined (HAVE_PGSQL)
            db::test::destroyPgSQLSchema();
#endif
        }
};

void
Dhcpv4SrvTest::checkConfigFiles() {
#if defined (HAVE_MYSQL)
    MySqlHostDataSourceInit mysql_init;
#endif
#if defined (HAVE_PGSQL)
    PgSqlHostDataSourceInit pgsql_init;
#endif
    DBInitializer dbi;
    IfaceMgrTestConfig test_config(true);
    string path = CFG_EXAMPLES;
    vector<string> examples = {
        "advanced.json",
#if defined (HAVE_MYSQL) && defined (HAVE_PGSQL)
        "all-keys.json",
        "all-keys-netconf.json",
        "all-options.json",
#endif
        "backends.json",
        "classify.json",
        "classify2.json",
        "comments.json",
#if defined (HAVE_MYSQL)
        "config-backend.json",
#endif
        "dhcpv4-over-dhcpv6.json",
        "global-reservations.json",
        "ha-load-balancing-server1-mt-with-tls.json",
        "ha-load-balancing-server2-mt.json",
        "hooks.json",
        "hooks-radius.json",
        "leases-expiration.json",
        "multiple-options.json",
#if defined (HAVE_MYSQL)
        "mysql-reservations.json",
#endif
#if defined (HAVE_PGSQL)
        "pgsql-reservations.json",
#endif
        "reservations.json",
        "several-subnets.json",
        "shared-network.json",
        "single-subnet.json",
        "vendor-specific.json",
        "vivso.json",
        "with-ddns.json",
    };
    vector<string> files;
    for (auto const& example : examples) {
        string file = path + "/" + example;
        files.push_back(file);
    }
    for (auto const& file : files) {
        string label("Checking configuration from file: ");
        label += file;
        SCOPED_TRACE(label);
        loadConfigFile(file);
    }
}

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace

namespace {

TEST_F(Dhcpv4SrvTest, relayAgentInfoEcho) {
    Dhcpv4SrvMTTestGuard guard(*this, false);
    relayAgentInfoEcho();
}

TEST_F(Dhcpv4SrvTest, relayAgentInfoEchoMultiThreading) {
    Dhcpv4SrvMTTestGuard guard(*this, true);
    relayAgentInfoEcho();
}

TEST_F(Dhcpv4SrvTest, badRelayAgentInfoEcho) {
    Dhcpv4SrvMTTestGuard guard(*this, false);
    badRelayAgentInfoEcho();
}

TEST_F(Dhcpv4SrvTest, badRelayAgentInfoEchoMultiThreading) {
    Dhcpv4SrvMTTestGuard guard(*this, true);
    badRelayAgentInfoEcho();
}

TEST_F(Dhcpv4SrvTest, portsClientPort) {
    Dhcpv4SrvMTTestGuard guard(*this, false);
    portsClientPort();
}

TEST_F(Dhcpv4SrvTest, portsClientPortMultiThreading) {
    Dhcpv4SrvMTTestGuard guard(*this, true);
    portsClientPort();
}

TEST_F(Dhcpv4SrvTest, portsServerPort) {
    Dhcpv4SrvMTTestGuard guard(*this, false);
    portsServerPort();
}

TEST_F(Dhcpv4SrvTest, portsServerPortMultiThreading) {
    Dhcpv4SrvMTTestGuard guard(*this, true);
    portsServerPort();
}

/// @brief Check that example files from documentation are valid (can be parsed
/// and loaded).
TEST_F(Dhcpv4SrvTest, checkConfigFiles) {
    checkConfigFiles();
}

/// @todo Implement tests for subnetSelect See tests in dhcp6_srv_unittest.cc:
/// selectSubnetAddr, selectSubnetIface, selectSubnetRelayLinkaddr,
/// selectSubnetRelayInterfaceId. Note that the concept of interface-id is not
/// present in the DHCPv4, so not everything is applicable directly.
/// See ticket #3057

// Checks whether the server uses default (0.0.0.0) siaddr value, unless
// explicitly specified
TEST_F(Dhcpv4SrvTest, siaddrDefault) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Verify that it is 0.0.0.0
    EXPECT_EQ("0.0.0.0", offer->getSiaddr().toText());
}

// Checks whether the server uses specified siaddr value
TEST_F(Dhcpv4SrvTest, siaddr) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    subnet_->setSiaddr(IOAddress("192.0.2.123"));

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Verify that its value is proper
    EXPECT_EQ("192.0.2.123", offer->getSiaddr().toText());
}

// Checks if the next-server defined as global value is overridden by subnet
// specific value and returned in server messages. There's also similar test for
// checking parser only configuration, see Dhcp4ParserTest.nextServerOverride in
// config_parser_unittest.cc. This test was extended to other BOOTP fixed fields.
TEST_F(Dhcpv4SrvTest, nextServerOverride) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ConstElementPtr status;

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"next-server\": \"192.0.0.1\", "
        "\"server-hostname\": \"nohost\", "
        "\"boot-file-name\": \"nofile\", "
        "\"subnet4\": [ { "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"next-server\": \"1.2.3.4\", "
        "    \"server-hostname\": \"some-name.example.org\", "
        "    \"boot-file-name\": \"bootfile.efi\", "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));

    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());

    EXPECT_EQ("1.2.3.4", offer->getSiaddr().toText());
    std::string sname("some-name.example.org");
    uint8_t sname_buf[Pkt4::MAX_SNAME_LEN];
    std::memset(sname_buf, 0, Pkt4::MAX_SNAME_LEN);
    std::memcpy(sname_buf, sname.c_str(), sname.size());
    EXPECT_EQ(0, std::memcmp(sname_buf, &offer->getSname()[0], Pkt4::MAX_SNAME_LEN));
    std::string filename("bootfile.efi");
    uint8_t filename_buf[Pkt4::MAX_FILE_LEN];
    std::memset(filename_buf, 0, Pkt4::MAX_FILE_LEN);
    std::memcpy(filename_buf, filename.c_str(), filename.size());
    EXPECT_EQ(0, std::memcmp(filename_buf, &offer->getFile()[0], Pkt4::MAX_FILE_LEN));
}

// Checks if the next-server defined as global value is used in responses
// when there is no specific value defined in subnet and returned to the client
// properly. There's also similar test for checking parser only configuration,
// see Dhcp4ParserTest.nextServerGlobal in config_parser_unittest.cc.
TEST_F(Dhcpv4SrvTest, nextServerGlobal) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ConstElementPtr status;

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"next-server\": \"192.0.0.1\", "
        "\"server-hostname\": \"some-name.example.org\", "
        "\"boot-file-name\": \"bootfile.efi\", "
        "\"subnet4\": [ { "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));

    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());

    EXPECT_EQ("192.0.0.1", offer->getSiaddr().toText());
    std::string sname("some-name.example.org");
    uint8_t sname_buf[Pkt4::MAX_SNAME_LEN];
    std::memset(sname_buf, 0, Pkt4::MAX_SNAME_LEN);
    std::memcpy(sname_buf, sname.c_str(), sname.size());
    EXPECT_EQ(0, std::memcmp(sname_buf, &offer->getSname()[0], Pkt4::MAX_SNAME_LEN));
    std::string filename("bootfile.efi");
    uint8_t filename_buf[Pkt4::MAX_FILE_LEN];
    std::memset(filename_buf, 0, Pkt4::MAX_FILE_LEN);
    std::memcpy(filename_buf, filename.c_str(), filename.size());
    EXPECT_EQ(0, std::memcmp(filename_buf, &offer->getFile()[0], Pkt4::MAX_FILE_LEN));
}

// Checks if client packets are classified properly using match expressions.
TEST_F(Dhcpv4SrvTest, matchClassification) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // The router class matches incoming packets with foo in a host-name
    // option (code 12) and sets an ip-forwarding option in the response.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[12].text == 'foo'\" },"
        "{   \"name\": \"template-client-id\","
        "    \"template-test\": \"substring(option[61].hex,0,3)\" },"
        "{   \"name\": \"SPAWN_template-hostname_foo\" },"
        "{   \"name\": \"template-hostname\","
        "    \"template-test\": \"option[12].text\"} ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create packets with enough to select the subnet
    OptionPtr clientid = generateClientId();
    Pkt4Ptr query1(new Pkt4(DHCPDISCOVER, 1234));
    query1->setRemoteAddr(IOAddress("192.0.2.1"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);
    Pkt4Ptr query2(new Pkt4(DHCPDISCOVER, 1234));
    query2->setRemoteAddr(IOAddress("192.0.2.1"));
    query2->addOption(clientid);
    query2->setIface("eth1");
    query2->setIndex(ETH1_INDEX);
    Pkt4Ptr query3(new Pkt4(DHCPDISCOVER, 1234));
    query3->setRemoteAddr(IOAddress("192.0.2.1"));
    query3->addOption(clientid);
    query3->setIface("eth1");
    query3->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the first 2 queries
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_IP_FORWARDING);
    query1->addOption(prl);
    query2->addOption(prl);

    // Create and add a host-name option to the first and last queries
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query1->addOption(hostname);
    query3->addOption(hostname);

    // Classify packets
    srv_->classifyPacket(query1);
    srv_->classifyPacket(query2);
    srv_->classifyPacket(query3);

    EXPECT_EQ(query1->classes_.size(), 6);
    EXPECT_EQ(query2->classes_.size(), 3);
    EXPECT_EQ(query3->classes_.size(), 6);

    EXPECT_TRUE(query1->inClass("ALL"));
    EXPECT_TRUE(query2->inClass("ALL"));
    EXPECT_TRUE(query3->inClass("ALL"));

    // Packets with the exception of the second should be in the router class
    EXPECT_TRUE(query1->inClass("router"));
    EXPECT_FALSE(query2->inClass("router"));
    EXPECT_TRUE(query3->inClass("router"));

    EXPECT_TRUE(query1->inClass("template-hostname"));
    EXPECT_FALSE(query2->inClass("template-hostname"));
    EXPECT_TRUE(query3->inClass("template-hostname"));

    EXPECT_TRUE(query1->inClass("SPAWN_template-hostname_foo"));
    EXPECT_FALSE(query2->inClass("SPAWN_template-hostname_foo"));
    EXPECT_TRUE(query3->inClass("SPAWN_template-hostname_foo"));

    EXPECT_TRUE(query1->inClass("template-client-id"));
    EXPECT_TRUE(query2->inClass("template-client-id"));
    EXPECT_TRUE(query3->inClass("template-client-id"));

    EXPECT_TRUE(query1->inClass("SPAWN_template-client-id_def"));
    EXPECT_TRUE(query2->inClass("SPAWN_template-client-id_def"));
    EXPECT_TRUE(query3->inClass("SPAWN_template-client-id_def"));

    // Process queries
    Pkt4Ptr response1 = srv_->processDiscover(query1);
    Pkt4Ptr response2 = srv_->processDiscover(query2);
    Pkt4Ptr response3 = srv_->processDiscover(query3);

    // Classification processing should add an ip-forwarding option
    OptionPtr opt1 = response1->getOption(DHO_IP_FORWARDING);
    EXPECT_TRUE(opt1);

    // But only for the first query: second was not classified
    OptionPtr opt2 = response2->getOption(DHO_IP_FORWARDING);
    EXPECT_FALSE(opt2);

    // But only for the first query: third has no PRL
    OptionPtr opt3 = response3->getOption(DHO_IP_FORWARDING);
    EXPECT_FALSE(opt3);
}

// Checks if client packets are classified properly using match expressions
// using option names
TEST_F(Dhcpv4SrvTest, matchClassificationOptionName) {

    // The router class matches incoming packets with foo in a host-name
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"test\": \"option[host-name].text == 'foo'\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify packets
    srv_->classifyPacket(query);

    // The query should be in the router class
    EXPECT_TRUE(query->inClass("router"));
}

// Checks if client packets are classified properly using match expressions
// using option names and definitions
TEST_F(Dhcpv4SrvTest, matchClassificationOptionDef) {

    // The router class matches incoming packets with foo in a defined
    // option
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"test\": \"option[my-host-name].text == 'foo'\" } ], "
        "\"option-def\": [ {"
        "    \"name\": \"my-host-name\", "
        "    \"code\": 250, "
        "    \"type\": \"string\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));

    // Create and add a my-host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 250, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify packets
    srv_->classifyPacket(query);

    // The query should be in the router class
    EXPECT_TRUE(query->inClass("router"));
}

// Checks subnet options have the priority over class options
TEST_F(Dhcpv4SrvTest, subnetClassPriority) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Subnet sets an ip-forwarding option in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 12) and sets an ip-forwarding option in the response.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"false\" } ] } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\","
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[12].text == 'foo'\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_IP_FORWARDING);
    query->addOption(prl);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify the packet
    srv_->classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    Pkt4Ptr response = srv_->processDiscover(query);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(DHO_IP_FORWARDING);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Classification sets the value to true/1, subnet to false/0
    // Here subnet has the priority
    EXPECT_EQ(0, opt->getUint8());
}

// Checks subnet options have the priority over global options
TEST_F(Dhcpv4SrvTest, subnetGlobalPriority) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Subnet and global set an ip-forwarding option in the response.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"false\" } ] } ], "
        "\"option-data\": ["
        "    {    \"name\": \"ip-forwarding\", "
        "         \"data\": \"true\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_IP_FORWARDING);
    query->addOption(prl);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Process the query
    Pkt4Ptr response = srv_->processDiscover(query);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(DHO_IP_FORWARDING);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Global sets the value to true/1, subnet to false/0
    // Here subnet has the priority
    EXPECT_EQ(0, opt->getUint8());
}

// Checks class options have the priority over global options
TEST_F(Dhcpv4SrvTest, classGlobalPriority) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // A global ip-forwarding option is set in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 12) and sets an ip-forwarding option in the response.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"option-data\": ["
        "    {    \"name\": \"ip-forwarding\", "
        "         \"data\": \"false\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\","
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[12].text == 'foo'\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_IP_FORWARDING);
    query->addOption(prl);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify the packet
    srv_->classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    Pkt4Ptr response = srv_->processDiscover(query);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(DHO_IP_FORWARDING);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Classification sets the value to true/1, global to false/0
    // Here class has the priority
    EXPECT_NE(0, opt->getUint8());
}

// Checks class options have the priority over global persistent options
TEST_F(Dhcpv4SrvTest, classGlobalPersistency) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // A global ip-forwarding option is set in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 12) and sets an ip-forwarding option in the response.
    // Note the persistency flag follows a "OR" semantic so to set
    // it to false (or to leave the default) has no effect.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"option-data\": ["
        "    {    \"name\": \"ip-forwarding\", "
        "         \"data\": \"false\", "
        "         \"always-send\": true } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\","
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"true\", "
        "             \"always-send\": false } ], "
        "    \"test\": \"option[12].text == 'foo'\" } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Do not add a PRL
    OptionPtr prl = query->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST);
    EXPECT_FALSE(prl);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify the packet
    srv_->classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    Pkt4Ptr response = srv_->processDiscover(query);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(DHO_IP_FORWARDING);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Classification sets the value to true/1, global to false/0
    // Here class has the priority
    EXPECT_NE(0, opt->getUint8());
}

// Checks if the client-class field is indeed used for subnet selection.
// Note that packet classification is already checked in Dhcpv4SrvTest
// .*Classification above.
TEST_F(Dhcpv4SrvTest, clientClassify) {

    // This test configures 2 subnets. We actually only need the
    // first one, but since there's still this ugly hack that picks
    // the pool if there is only one, we must use more than one
    // subnet. That ugly hack will be removed in #3242, currently
    // under review.

    // The second subnet does not play any role here. The client's
    // IP address belongs to the first subnet, so only that first
    // subnet is being tested.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"client-class\": \"foo\", "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"client-class\": \"xyzzy\", "
        "    \"id\": 2, "
        "    \"subnet\": \"192.0.3.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config, true, false));

    // Create a simple packet that we'll use for classification
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setCiaddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This discover does not belong to foo class, so it will not
    // be serviced
    bool drop = false;
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Let's add the packet to bar class and try again.
    dis->addClass("bar");

    // Still not supported, because it belongs to wrong class.
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Let's add it to matching class.
    dis->addClass("foo");

    // This time it should work
    EXPECT_TRUE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
}

// Checks if the client-class field is indeed used for pool selection.
TEST_F(Dhcpv4SrvTest, clientPoolClassify) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // This test configures 2 pools.
    // The second pool does not play any role here. The client's
    // IP address belongs to the first pool, so only that first
    // pool is being tested.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { "
        "      \"pool\": \"192.0.2.1 - 192.0.2.100\", "
        "      \"client-class\": \"foo\" }, "
        "    { \"pool\": \"192.0.3.1 - 192.0.3.100\", "
        "      \"client-class\": \"xyzzy\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.0.0/16\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Create a simple packet that we'll use for classification
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setCiaddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This discover does not belong to foo class, so it will not
    // be serviced
    Pkt4Ptr offer = srv_->processDiscover(dis);
    EXPECT_FALSE(offer);

    // Let's add the packet to bar class and try again.
    dis->addClass("bar");

    // Still not supported, because it belongs to wrong class.
    offer = srv_->processDiscover(dis);
    EXPECT_FALSE(offer);

    // Let's add it to matching class.
    dis->addClass("foo");

    // This time it should work
    offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());
    EXPECT_FALSE(offer->getYiaddr().isV4Zero());
}

// Checks if the KNOWN built-in classes is indeed used for pool selection.
TEST_F(Dhcpv4SrvTest, clientPoolClassifyKnown) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // This test configures 2 pools.
    // The first one requires reservation, the second does the opposite.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { "
        "      \"pool\": \"192.0.2.1 - 192.0.2.100\", "
        "      \"client-class\": \"KNOWN\" }, "
        "    { \"pool\": \"192.0.3.1 - 192.0.3.100\", "
        "      \"client-class\": \"UNKNOWN\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.0.0/16\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Create a simple packet that we'll use for classification
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setCiaddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // First pool requires reservation so the second will be used
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());
    EXPECT_EQ("192.0.3.1", offer->getYiaddr().toText());
}

// Checks if the UNKNOWN built-in classes is indeed used for pool selection.
TEST_F(Dhcpv4SrvTest, clientPoolClassifyUnknown) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // This test configures 2 pools.
    // The first one requires no reservation, the second does the opposite.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { "
        "      \"pool\": \"192.0.2.1 - 192.0.2.100\", "
        "      \"client-class\": \"UNKNOWN\" }, "
        "    { \"pool\": \"192.0.3.1 - 192.0.3.100\", "
        "      \"client-class\": \"KNOWN\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.0.0/16\", "
        "    \"reservations\": [ { "
        "       \"hw-address\": \"00:00:00:11:22:33\", "
        "       \"hostname\": \"foo.bar\" } ] } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Create a simple packet that we'll use for classification
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setCiaddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Set hardware address / identifier
    const HWAddr& hw = HWAddr::fromText("00:00:00:11:22:33");
    HWAddrPtr hw_addr(new HWAddr(hw));
    dis->setHWAddr(hw_addr);

    // First pool requires no reservation so the second will be used
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());
    EXPECT_EQ("192.0.3.1", offer->getYiaddr().toText());
}

// Verifies private option deferred processing
TEST_F(Dhcpv4SrvTest, privateOption) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Same than option43Class but with private options
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"private\", "
        "    \"test\": \"option[234].exists\", "
        "    \"option-def\": [ "
        "    {   \"code\": 245, "
        "        \"name\": \"privint\", "
        "        \"type\": \"uint32\" } ],"
        "    \"option-data\": [ "
        "    {   \"code\": 234, "
        "        \"data\": \"01\" }, "
        "    {   \"name\": \"privint\", "
        "        \"data\": \"12345678\" } ] } ] }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Create and add a private option with code 234
    OptionBuffer buf;
    buf.push_back(0x01);
    OptionPtr opt1(new Option(Option::V4, 234, buf));
    query->addOption(opt1);
    query->getDeferredOptions().push_back(234);

    // Create and add a private option with code 245
    buf.clear();
    buf.push_back(0x87);
    buf.push_back(0x65);
    buf.push_back(0x43);
    buf.push_back(0x21);
    OptionPtr opt2(new Option(Option::V4, 245, buf));
    query->addOption(opt2);
    query->getDeferredOptions().push_back(245);

    // Create and add a PRL option to the query
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(234);
    prl->addValue(245);
    query->addOption(prl);

    srv_->classifyPacket(query);
    ASSERT_NO_THROW(srv_->deferredUnpack(query));

    // Check if the option 245 was re-unpacked
    opt2 = query->getOption(245);
    OptionUint32Ptr opt32 = boost::dynamic_pointer_cast<OptionUint32>(opt2);
    EXPECT_TRUE(opt32);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv_->processDiscover(query);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Processing should add an option with code 234
    OptionPtr opt = offer->getOption(234);
    EXPECT_TRUE(opt);

    // And an option with code 245
    opt = offer->getOption(245);
    ASSERT_TRUE(opt);
    // Verifies the content
    opt32 = boost::dynamic_pointer_cast<OptionUint32>(opt);
    ASSERT_TRUE(opt32);
    EXPECT_EQ(12345678, opt32->getValue());
}

// Checks effect of persistency (aka always-send) flag on the PRL.
TEST_F(Dhcpv4SrvTest, prlPersistency) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(CONFIGS[2]));

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option for another option
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_ARP_CACHE_TIMEOUT);
    query->addOption(prl);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Let the server process it.
    Pkt4Ptr response = srv_->processDiscover(query);

    // Processing should add an ip-forwarding option
    ASSERT_TRUE(response->getOption(DHO_IP_FORWARDING));
    // But no default-ip-ttl
    ASSERT_FALSE(response->getOption(DHO_DEFAULT_IP_TTL));
    // Nor an arp-cache-timeout
    ASSERT_FALSE(response->getOption(DHO_ARP_CACHE_TIMEOUT));

    // Reset PRL adding default-ip-ttl
    query->delOption(DHO_DHCP_PARAMETER_REQUEST_LIST);
    prl->addValue(DHO_DEFAULT_IP_TTL);
    query->addOption(prl);

    // Let the server process it again.
    response = srv_->processDiscover(query);

    // Processing should add an ip-forwarding option
    ASSERT_TRUE(response->getOption(DHO_IP_FORWARDING));
    // and now a default-ip-ttl
    ASSERT_TRUE(response->getOption(DHO_DEFAULT_IP_TTL));
    // and still no arp-cache-timeout
    ASSERT_FALSE(response->getOption(DHO_ARP_CACHE_TIMEOUT));
}

// Checks effect of cancellation (aka never-send) flag.
TEST_F(Dhcpv4SrvTest, neverSend) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(CONFIGS[3]));

    // Create a packet with enough to select the subnet and go through
    // the DISCOVER processing
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->setIndex(ETH1_INDEX);

    // Create and add a PRL option for another option
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_ARP_CACHE_TIMEOUT);
    query->addOption(prl);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V4, 12, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Let the server process it.
    Pkt4Ptr response = srv_->processDiscover(query);

    // Processing should not add an ip-forwarding option
    ASSERT_FALSE(response->getOption(DHO_IP_FORWARDING));
    // And no default-ip-ttl
    ASSERT_FALSE(response->getOption(DHO_DEFAULT_IP_TTL));
    // Nor an arp-cache-timeout
    ASSERT_FALSE(response->getOption(DHO_ARP_CACHE_TIMEOUT));

    // Reset PRL adding default-ip-ttl
    query->delOption(DHO_DHCP_PARAMETER_REQUEST_LIST);
    prl->addValue(DHO_DEFAULT_IP_TTL);
    query->addOption(prl);

    // Let the server process it again.
    response = srv_->processDiscover(query);

    // Processing should not add an ip-forwarding option
    ASSERT_FALSE(response->getOption(DHO_IP_FORWARDING));
    // And now a default-ip-ttl
    ASSERT_TRUE(response->getOption(DHO_DEFAULT_IP_TTL));
    // And still no arp-cache-timeout
    ASSERT_FALSE(response->getOption(DHO_ARP_CACHE_TIMEOUT));
}

// Checks if relay IP address specified in the relay-info structure in
// subnet4 is being used properly.
TEST_F(Dhcpv4SrvTest, relayOverride) {

    // We have 2 subnets defined. Note that both have a relay address
    // defined. Both are not belonging to the subnets. That is
    // important, because if the relay belongs to the subnet, there's
    // no need to specify relay override.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.2 - 192.0.2.100\" } ],"
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.5.1\" ]"
        "    },"
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.5.2\" ]"
        "    },"
        "    \"id\": 2, "
        "    \"subnet\": \"192.0.3.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config, true, false));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet4Ptr subnet1 = *subnets->begin();
    Subnet4Ptr subnet2 = *std::next(subnets->begin());
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This is just a sanity check, we're using regular method: ciaddr 192.0.2.1
    // belongs to the first subnet, so it is selected
    dis->setGiaddr(IOAddress("192.0.2.1"));
    bool drop = false;
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Relay belongs to the second subnet, so it should be selected.
    dis->setGiaddr(IOAddress("192.0.3.1"));
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Now let's check if the relay override for the first subnets works
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // The same check for the second subnet...
    dis->setGiaddr(IOAddress("192.0.5.2"));
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // And finally, let's check if mis-matched relay address will end up
    // in not selecting a subnet at all
    dis->setGiaddr(IOAddress("192.0.5.3"));
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Finally, check that the relay override works only with relay address
    // (GIADDR) and does not affect client address (CIADDR)
    dis->setGiaddr(IOAddress("0.0.0.0"));
    dis->setHops(0);
    dis->setCiaddr(IOAddress("192.0.5.1"));
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
}

// Checks if relay IP address specified in the relay-info structure can be
// used together with client-classification.
TEST_F(Dhcpv4SrvTest, relayOverrideAndClientClass) {

    // This test configures 2 subnets. They both are on the same link, so they
    // have the same relay-ip address. Furthermore, the first subnet is
    // reserved for clients that belong to class "foo".
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.2 - 192.0.2.100\" } ],"
        "    \"client-class\": \"foo\", "
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.5.1\" ]"
        "    },"
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.5.1\" ]"
        "    },"
        "    \"id\": 2, "
        "    \"subnet\": \"192.0.3.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config, true, false));

    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet4Ptr subnet1 = *subnets->begin();
    Subnet4Ptr subnet2 = *std::next(subnets->begin());
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    dis->setHops(1);
    dis->setGiaddr(IOAddress("192.0.5.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This packet does not belong to class foo, so it should be rejected in
    // subnet[0], even though the relay-ip matches. It should be accepted in
    // subnet[1], because the subnet matches and there are no class
    // requirements.
    bool drop = false;
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Now let's add this packet to class foo and recheck. This time it should
    // be accepted in the first subnet, because both class and relay-ip match.
    dis->addClass("foo");
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
}

// Checks if a RAI link selection sub-option works as expected
TEST_F(Dhcpv4SrvTest, relayLinkSelect) {

    // We have 3 subnets defined.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.2 - 192.0.2.100\" } ],"
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.5.1\" ]"
        "    },"
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"id\": 2, "
        "    \"subnet\": \"192.0.3.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.4.1 - 192.0.4.100\" } ],"
        "    \"client-class\": \"foo\", "
        "    \"id\": 3, "
        "    \"subnet\": \"192.0.4.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config, true, false));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(3, subnets->size());

    // Let's get them for easy reference
    auto subnet_it = subnets->begin();
    Subnet4Ptr subnet1 = *subnet_it;
    ++subnet_it;
    Subnet4Ptr subnet2 = *subnet_it;
    ++subnet_it;
    Subnet4Ptr subnet3 = *subnet_it;
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);
    ASSERT_TRUE(subnet3);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Let's create a Relay Agent Information option
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));
    ASSERT_TRUE(rai);
    IOAddress addr("192.0.3.2");
    OptionPtr ols(new Option(Option::V4,
                             RAI_OPTION_LINK_SELECTION,
                             addr.toBytes()));
    ASSERT_TRUE(ols);
    rai->addOption(ols);

    // This is just a sanity check, we're using regular method: ciaddr 192.0.3.1
    // belongs to the second subnet, so it is selected
    dis->setGiaddr(IOAddress("192.0.3.1"));
    bool drop = false;
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Setup a relay override for the first subnet as it has a high precedence
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Put a RAI to select back the second subnet as it has
    // the highest precedence
    dis->addOption(rai);
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Subnet select option has a lower precedence
    const OptionDefinition& sbnsel_def = LibDHCP::DHO_SUBNET_SELECTION_DEF();
    OptionCustomPtr sbnsel(new OptionCustom(sbnsel_def, Option::V4));
    ASSERT_TRUE(sbnsel);
    sbnsel->writeAddress(IOAddress("192.0.2.3"));
    dis->addOption(sbnsel);
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // But, when RAI exists without the link selection option, we should
    // fall back to the subnet selection option.
    rai->delOption(RAI_OPTION_LINK_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    dis->addOption(rai);
    dis->setGiaddr(IOAddress("192.0.4.1"));
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Check client-classification still applies
    IOAddress addr_foo("192.0.4.2");
    ols.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                         addr_foo.toBytes()));
    dis->delOption(DHO_SUBNET_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    rai->addOption(ols);
    dis->addOption(rai);

    // Note it shall fail (vs. try the next criterion).
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
    // Add the packet to the class and check again: now it shall succeed
    dis->addClass("foo");
    EXPECT_TRUE(subnet3 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Check it fails with a bad address in the sub-option
    IOAddress addr_bad("10.0.0.1");
    ols.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                         addr_bad.toBytes()));
    rai->delOption(RAI_OPTION_LINK_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    rai->addOption(ols);
    dis->addOption(rai);
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
}

// Checks if a RAI link selection compatibility preferences work as expected
TEST_F(Dhcpv4SrvTest, relayIgnoreLinkSelect) {

    // We have 3 subnets defined.
    string config = "{ \"interfaces-config\": {"
                    "    \"interfaces\": [ \"*\" ]"
                    "},"
                    "\"rebind-timer\": 2000, "
                    "\"renew-timer\": 1000, "
                    "\"compatibility\": { \"ignore-rai-link-selection\": true },"
                    "\"subnet4\": [ "
                    "{   \"pools\": [ { \"pool\": \"192.0.2.2 - 192.0.2.100\" } ],"
                    "    \"relay\": { "
                    "        \"ip-addresses\": [ \"192.0.5.1\" ]"
                    "    },"
                    "    \"id\": 1, "
                    "    \"subnet\": \"192.0.2.0/24\" }, "
                    "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
                    "    \"id\": 2, "
                    "    \"subnet\": \"192.0.3.0/24\" }, "
                    "{   \"pools\": [ { \"pool\": \"192.0.4.1 - 192.0.4.100\" } ],"
                    "    \"client-class\": \"foo\", "
                    "    \"id\": 3, "
                    "    \"subnet\": \"192.0.4.0/24\" } "
                    "],"
                    "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config, true, false));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(3, subnets->size());

    // Let's get them for easy reference
    auto subnet_it = subnets->begin();
    Subnet4Ptr subnet1 = *subnet_it;
    ++subnet_it;
    Subnet4Ptr subnet2 = *subnet_it;
    ++subnet_it;
    Subnet4Ptr subnet3 = *subnet_it;
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);
    ASSERT_TRUE(subnet3);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Let's create a Relay Agent Information option
    const OptionDefinition& rai_def = LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF();
    OptionCustomPtr rai(new OptionCustom(rai_def, Option::V4));
    ASSERT_TRUE(rai);
    IOAddress addr("192.0.3.2");
    OptionPtr ols(new Option(Option::V4,
                             RAI_OPTION_LINK_SELECTION,
                             addr.toBytes()));
    ASSERT_TRUE(ols);
    rai->addOption(ols);

    // This is just a sanity check, we're using regular method: ciaddr 192.0.3.1
    // belongs to the second subnet, so it is selected
    dis->setGiaddr(IOAddress("192.0.3.1"));
    bool drop = false;
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Setup a relay override for the first subnet as it has a high precedence
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Put a RAI to select back the second subnet as it has
    // the highest precedence, but it should be ignored due
    // to the ignore-rai-link-selection compatibility config
    dis->addOption(rai);
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Subnet select option has a lower precedence, but will succeed
    // because RAI link selection suboptions are being ignored
    const OptionDefinition& sbnsel_def = LibDHCP::DHO_SUBNET_SELECTION_DEF();
    OptionCustomPtr sbnsel(new OptionCustom(sbnsel_def, Option::V4));
    ASSERT_TRUE(sbnsel);
    sbnsel->writeAddress(IOAddress("192.0.2.3"));
    dis->addOption(sbnsel);
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // But, when RAI exists without the link selection option, we should
    // fall back to the subnet selection option.
    rai->delOption(RAI_OPTION_LINK_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    dis->addOption(rai);
    dis->setGiaddr(IOAddress("192.0.4.1"));
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Check client-classification still applies
    IOAddress addr_foo("192.0.4.2");
    ols.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                         addr_foo.toBytes()));
    dis->delOption(DHO_SUBNET_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    rai->addOption(ols);
    dis->addOption(rai);

    // Note it shall fail (vs. try the next criterion).
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
    // Add the packet to the class and check again: now it shall succeed
    dis->addClass("foo");
    EXPECT_TRUE(subnet3 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Check it succeeds even with a bad address in the sub-option
    IOAddress addr_bad("10.0.0.1");
    ols.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                         addr_bad.toBytes()));
    rai->delOption(RAI_OPTION_LINK_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    rai->addOption(ols);
    dis->addOption(rai);
    EXPECT_TRUE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
}

// Checks if a subnet selection option works as expected
TEST_F(Dhcpv4SrvTest, subnetSelect) {

    // We have 3 subnets defined.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.2 - 192.0.2.100\" } ],"
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.5.1\" ]"
        "    },"
        "    \"id\": 1, "
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"id\": 2, "
        "    \"subnet\": \"192.0.3.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.4.1 - 192.0.4.100\" } ],"
        "    \"client-class\": \"foo\", "
        "    \"id\": 3, "
        "    \"subnet\": \"192.0.4.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config, true, false));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(3, subnets->size());

    // Let's get them for easy reference
    auto subnet_it = subnets->begin();
    Subnet4Ptr subnet1 = *subnet_it;
    ++subnet_it;
    Subnet4Ptr subnet2 = *subnet_it;
    ++subnet_it;
    Subnet4Ptr subnet3 = *subnet_it;
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);
    ASSERT_TRUE(subnet3);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setIndex(ETH0_INDEX);
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Let's create a Subnet Selection option
    const OptionDefinition& sbnsel_def = LibDHCP::DHO_SUBNET_SELECTION_DEF();
    OptionCustomPtr sbnsel(new OptionCustom(sbnsel_def, Option::V4));
    ASSERT_TRUE(sbnsel);
    sbnsel->writeAddress(IOAddress("192.0.3.2"));

    // This is just a sanity check, we're using regular method: ciaddr 192.0.3.1
    // belongs to the second subnet, so it is selected
    dis->setGiaddr(IOAddress("192.0.3.1"));
    bool drop = false;
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Setup a relay override for the first subnet as it has a high precedence
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Put a subnet select option to select back the second subnet as
    // it has the second highest precedence
    dis->addOption(sbnsel);
    EXPECT_TRUE(subnet2 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Check client-classification still applies
    sbnsel->writeAddress(IOAddress("192.0.4.2"));
    // Note it shall fail (vs. try the next criterion).
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
    // Add the packet to the class and check again: now it shall succeed
    dis->addClass("foo");
    EXPECT_TRUE(subnet3 == srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);

    // Check it fails with a bad address in the sub-option
    sbnsel->writeAddress(IOAddress("10.0.0.1"));
    EXPECT_FALSE(srv_->selectSubnet(dis, drop));
    EXPECT_FALSE(drop);
}

// This test verifies that the direct message is dropped when it has been
// received by the server via an interface for which there is no subnet
// configured. It also checks that the message is not dropped (is processed)
// when it is relayed or unicast.
TEST_F(Dhcpv4SrvTest, acceptDirectRequest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 1234));
    // Set Giaddr and local server's unicast address, but don't set hops.
    // Hops value should not matter. The server will treat the message
    // with the hops value of 0 and non-zero giaddr as relayed.
    pkt->setGiaddr(IOAddress("192.0.10.1"));
    pkt->setRemoteAddr(IOAddress("0.0.0.0"));
    pkt->setLocalAddr(IOAddress("192.0.2.3"));
    pkt->setIface("eth1");
    pkt->setIndex(ETH1_INDEX);
    EXPECT_TRUE(srv_->accept(pkt));

    // Let's set hops and check that the message is still accepted as
    // a relayed message.
    pkt->setHops(1);
    EXPECT_TRUE(srv_->accept(pkt));

    // Make it a direct message but keep unicast server's address. The
    // messages sent to unicast address should be accepted as they are
    // most likely to renew existing leases. The server should respond
    // to renews so they have to be accepted and processed.
    pkt->setHops(0);
    pkt->setGiaddr(IOAddress("0.0.0.0"));
    EXPECT_TRUE(srv_->accept(pkt));

    // Direct message is now sent to a broadcast address. The server
    // should accept this message because it has been received via
    // eth1 for which there is a subnet configured (see test fixture
    // class constructor).
    pkt->setLocalAddr(IOAddress("255.255.255.255"));
    EXPECT_TRUE(srv_->accept(pkt));

    // For eth0, there is no subnet configured. Such message is expected
    // to be silently dropped.
    pkt->setIface("eth0");
    pkt->setIndex(ETH0_INDEX);
    EXPECT_FALSE(srv_->accept(pkt));

    // But, if the message is unicast it should be accepted, even though
    // it has been received via eth0.
    pkt->setLocalAddr(IOAddress("10.0.0.1"));
    EXPECT_TRUE(srv_->accept(pkt));

    // For the DHCPINFORM the ciaddr should be set or at least the source
    // address.
    pkt->setType(DHCPINFORM);
    pkt->setRemoteAddr(IOAddress("10.0.0.101"));
    EXPECT_TRUE(srv_->accept(pkt));

    // When neither ciaddr nor source address is present, the packet should
    // be dropped.
    pkt->setRemoteAddr(IOAddress("0.0.0.0"));
    EXPECT_FALSE(srv_->accept(pkt));

    // When ciaddr is set, the packet should be accepted.
    pkt->setCiaddr(IOAddress("10.0.0.1"));
    EXPECT_TRUE(srv_->accept(pkt));
}

// This test checks that the server rejects a message with invalid type.
TEST_F(Dhcpv4SrvTest, acceptMessageType) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Specify messages to be accepted by the server.
    int allowed[] = {
        DHCPDISCOVER,
        DHCPREQUEST,
        DHCPRELEASE,
        DHCPDECLINE,
        DHCPINFORM
    };
    size_t allowed_size = sizeof(allowed) / sizeof(allowed[0]);
    // Check that the server actually accepts these message types.
    for (size_t i = 0; i < allowed_size; ++i) {
        EXPECT_TRUE(srv_->acceptMessageType(Pkt4Ptr(new Pkt4(allowed[i], 1234))))
            << "Test failed for message type " << i;
    }
    // Specify messages which server is supposed to drop.
    int not_allowed[] = {
        DHCPOFFER,
        DHCPACK,
        DHCPNAK,
        DHCPLEASEQUERY,
        DHCPLEASEUNASSIGNED,
        DHCPLEASEUNKNOWN,
        DHCPLEASEACTIVE,
        DHCPBULKLEASEQUERY,
        DHCPLEASEQUERYDONE,
    };
    size_t not_allowed_size = sizeof(not_allowed) / sizeof(not_allowed[0]);
    // Actually check that the server will drop these messages.
    for (size_t i = 0; i < not_allowed_size; ++i) {
        EXPECT_FALSE(srv_->acceptMessageType(Pkt4Ptr(new Pkt4(not_allowed[i],
                                                            1234))))
            << "Test failed for message type " << i;
    }

    // Verify that we drop packets with no option 53
    // Make a BOOTP packet (i.e. no option 53)
    std::vector<uint8_t> bin;
    const char* bootp_txt =
        "01010601002529b629b600000000000000000000000000000ace5001944452fe711700"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000063825363521b010400"
        "020418020600237453fc48090b0000118b06010401020300ff00000000000000000000"
        "0000000000000000000000000000000000000000";

    isc::util::encode::decodeHex(bootp_txt, bin);
    Pkt4Ptr pkt(new Pkt4(&bin[0], bin.size()));
    pkt->unpack();
    ASSERT_EQ(DHCP_NOTYPE, pkt->getType());
    EXPECT_FALSE(srv_->acceptMessageType(Pkt4Ptr(new Pkt4(&bin[0], bin.size()))));

    // Verify that we drop packets with types >= DHCP_TYPES_EOF
    // Make Discover with type changed to 0xff
    std::vector<uint8_t> bin2;
    const char* invalid_msg_type =
        "010106015d05478d000000000000000000000000000000000afee20120e52ab8151400"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000638253633501ff3707"
        "0102030407067d3c0a646f63736973332e303a7d7f0000118b7a010102057501010102"
        "010303010104010105010106010107010f0801100901030a01010b01180c01010d0200"
        "400e0200100f010110040000000211010014010015013f160101170101180104190104"
        "1a01041b01201c01021d01081e01201f01102001102101022201012301002401002501"
        "01260200ff2701012b59020345434d030b45434d3a45524f55544552040d3242523232"
        "39553430303434430504312e3034060856312e33332e30330707322e332e3052320806"
        "30303039354209094347333030304443520a074e657467656172fe01083d0fff2ab815"
        "140003000120e52ab81514390205dc5219010420000002020620e52ab8151409090000"
        "118b0401020300ff";

    bin.clear();
    isc::util::encode::decodeHex(invalid_msg_type, bin);
    pkt.reset(new Pkt4(&bin[0], bin.size()));
    pkt->unpack();
    ASSERT_EQ(0xff, pkt->getType());
    EXPECT_FALSE(srv_->acceptMessageType(pkt));
}

// Test checks whether statistic is bumped up appropriately when Decline
// message is received.
TEST_F(Dhcpv4SrvTest, statisticsDecline) {
    pretendReceivingPkt(*srv_, CONFIGS[0], DHCPDECLINE, "pkt4-decline-received");
}

// Test checks whether statistic is bumped up appropriately when Offer
// message is received (this should never happen in a sane network).
TEST_F(Dhcpv4SrvTest, statisticsOfferRcvd) {
    pretendReceivingPkt(*srv_, CONFIGS[0], DHCPOFFER, "pkt4-offer-received");
}

// Test checks whether statistic is bumped up appropriately when Ack
// message is received (this should never happen in a sane network).
TEST_F(Dhcpv4SrvTest, statisticsAckRcvd) {
    pretendReceivingPkt(*srv_, CONFIGS[0], DHCPACK, "pkt4-ack-received");
}

// Test checks whether statistic is bumped up appropriately when Nak
// message is received (this should never happen in a sane network).
TEST_F(Dhcpv4SrvTest, statisticsNakRcvd) {
    pretendReceivingPkt(*srv_, CONFIGS[0], DHCPNAK, "pkt4-nak-received");
}

// Test checks whether statistic is bumped up appropriately when Release
// message is received.
TEST_F(Dhcpv4SrvTest, statisticsReleaseRcvd) {
    pretendReceivingPkt(*srv_, CONFIGS[0], DHCPRELEASE, "pkt4-release-received");
}

// Test checks whether statistic is bumped up appropriately when unknown
// message is received.
TEST_F(Dhcpv4SrvTest, statisticsUnknownRcvd) {
    pretendReceivingPkt(*srv_, CONFIGS[0], 200, "pkt4-unknown-received");

    // There should also be pkt4-receive-drop stat bumped up
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr drop_stat = mgr.getObservation("pkt4-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test verifies that the server is able to handle an empty client-id
// in incoming client message.
TEST_F(Dhcpv4SrvTest, emptyClientId) {
    IfaceMgrTestConfig test_config(true);
    Dhcp4Client client(srv_);

    EXPECT_NO_THROW(configure(CONFIGS[0], *client.getServer()));

    // Tell the client to not send client-id on its own.
    client.includeClientId("");

    // Instead, tell him to send this extra option, which happens to be
    // an empty client-id.
    OptionPtr empty_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER));
    client.addExtraOption(empty_client_id);

    // Let's check whether the server is able to process this packet without
    // throwing any exceptions. We don't care whether the server sent any
    // responses or not. The goal is to check that the server didn't throw
    // any exceptions.
    EXPECT_NO_THROW(client.doDORA());
}

// This test verifies that the server is able to handle too long client-id
// in incoming client message.
TEST_F(Dhcpv4SrvTest, tooLongClientId) {
    IfaceMgrTestConfig test_config(true);
    Dhcp4Client client(srv_);

    EXPECT_NO_THROW(configure(CONFIGS[0], *client.getServer()));

    // Tell the client to not send client-id on its own.
    client.includeClientId("");

    // Instead, tell him to send this extra option, which happens to be
    // an empty client-id.
    std::vector<uint8_t> data(250, 250);
    OptionPtr long_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                        data));
    client.addExtraOption(long_client_id);

    // Let's check whether the server is able to process this packet without
    // throwing any exceptions. We don't care whether the server sent any
    // responses or not. The goal is to check that the server didn't throw
    // any exceptions.
    EXPECT_NO_THROW(client.doDORA());
}

// Checks if user-contexts are parsed properly.
TEST_F(Dhcpv4SrvTest, userContext) {

    IfaceMgrTestConfig test_config(true);

    // This config has one subnet with user-context with one
    // pool (also with context). Make sure the configuration could be accepted.
    EXPECT_NO_THROW(configure(CONFIGS[4]));

    // Now make sure the data was not lost.
    ConstSrvConfigPtr cfg = CfgMgr::instance().getCurrentCfg();
    const Subnet4Collection* subnets = cfg->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());

    // Let's get the subnet and check its context.
    Subnet4Ptr subnet1 = *subnets->begin();
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet1->getContext());
    EXPECT_EQ("{ \"secure\": false }", subnet1->getContext()->str());

    // Ok, not get the sole pool in it and check its context, too.
    PoolCollection pools = subnet1->getPools(Lease::TYPE_V4);
    ASSERT_EQ(1, pools.size());
    ASSERT_TRUE(pools[0]);
    ASSERT_TRUE(pools[0]->getContext());
    EXPECT_EQ("{ \"value\": 42 }", pools[0]->getContext()->str());
}

// Verify that fixed fields are set from classes in the same order
// as class options.
TEST_F(Dhcpv4SrvTest, fixedFieldsInClassOrder) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    std::string config = R"(
    {
        "interfaces-config": { "interfaces": [ "*" ] },
        "client-classes": [
        {
            "name":"one",
            "server-hostname": "server_one",
            "next-server": "192.0.2.111",
            "boot-file-name":"one.boot",
            "option-data": [
            {
                "name": "domain-name",
                "data": "one.example.com"
            }]
        },
        {
            "name":"two",
            "server-hostname": "server_two",
            "next-server":"192.0.2.222",
            "boot-file-name":"two.boot",
            "option-data": [
            {
                "name": "domain-name",
                "data": "two.example.com"
            }]
        },
        {
            "name":"next-server-only",
            "next-server":"192.0.2.100"
        },
        {
            "name":"server-hostname-only",
            "server-hostname": "server_only"
        },
        {
            "name":"bootfile-only",
            "boot-file-name": "only.boot"
        }],

        "subnet4": [
        {
            "id": 1,
            "subnet": "192.0.2.0/24",
            "pools": [ { "pool": "192.0.2.1 - 192.0.2.100" } ],
            "reservations": [
            {
                "hw-address": "08:00:27:25:d3:01",
                "client-classes": [ "one", "two" ]
            },
            {
                "hw-address": "08:00:27:25:d3:02",
                "client-classes": [ "two", "one" ]
            },
            {
                "hw-address": "08:00:27:25:d3:03",
                "client-classes": [ "server-hostname-only", "bootfile-only", "next-server-only" ]
            }]
        }]
    }
    )";

    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    struct Scenario {
        std::string hw_str_;
        std::string exp_classes_;
        std::string exp_server_hostname_;
        std::string exp_next_server_;
        std::string exp_bootfile_;
        std::string exp_domain_name_;
    };

    const std::vector<Scenario> scenarios = {
       {
        "08:00:27:25:d3:01",
        "ALL, one, two, KNOWN",
        "server_one",
        "192.0.2.111",
        "one.boot",
        "one.example.com"
       },
       {
        "08:00:27:25:d3:02",
        "ALL, two, one, KNOWN",
        "server_two",
        "192.0.2.222",
        "two.boot",
        "two.example.com"
       },
       {
        "08:00:27:25:d3:03",
        "ALL, server-hostname-only, bootfile-only, next-server-only, KNOWN",
        "server_only",
        "192.0.2.100",
        "only.boot",
        ""
       }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.hw_str_); {
            // Build a DISCOVER
            Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
            query->setRemoteAddr(IOAddress("192.0.2.1"));
            query->setIface("eth1");

            HWAddrPtr hw_addr(new HWAddr(HWAddr::fromText(scenario.hw_str_, 10)));
            query->setHWAddr(hw_addr);

            srv_->classifyPacket(query);

            // Process it.
            Pkt4Ptr response = srv_->processDiscover(query);

            // Make sure class list is as expected.
            ASSERT_EQ(scenario.exp_classes_, query->getClasses().toText());

            // Now check the fixed fields.
            checkStringInBuffer(scenario.exp_server_hostname_, response->getSname());
            EXPECT_EQ(scenario.exp_next_server_, response->getSiaddr().toText());
            checkStringInBuffer(scenario.exp_bootfile_, response->getFile());

            // Check domain name option.
            OptionPtr opt = response->getOption(DHO_DOMAIN_NAME);
            if (scenario.exp_domain_name_.empty()) {
                ASSERT_FALSE(opt);
            } else {
                ASSERT_TRUE(opt);
                OptionStringPtr opstr = boost::dynamic_pointer_cast<OptionString>(opt);
                ASSERT_TRUE(opstr);
                EXPECT_EQ(scenario.exp_domain_name_,  opstr->getValue());
            }
        }
    }
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is offered
// only when the option is configured.
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredDiscover) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // An address was offered.
    EXPECT_FALSE(offer->getYiaddr().isV4Zero());

    // No v6-only-preferred option.
    EXPECT_FALSE(offer->getOption(DHO_V6_ONLY_PREFERRED));
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is offered
// only when the option is configured.
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredRequest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // An address was offered.
    EXPECT_FALSE(ack->getYiaddr().isV4Zero());

    // No v6-only-preferred option.
    EXPECT_FALSE(ack->getOption(DHO_V6_ONLY_PREFERRED));
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in the subnet.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredDiscover) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet_->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(offer->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = offer->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in the subnet.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredRequest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet_->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(ack->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = ack->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in another subnet of the shared network.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredDiscoverAnother) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the domain name "foo".
    OptionStringPtr dn(new OptionString(Option::V4, DHO_DOMAIN_NAME, "foo"));
    subnet_->getCfgOption()->add(dn, false, false, DHCP4_OPTION_SPACE);
    // Add another subnet,
    Subnet4Ptr subnet2 = Subnet4::create(IOAddress("192.0.3.0"), 24,
                                         unspecified,
                                         unspecified,
                                         valid_lft,
                                         subnet_->getID() + 1);
    // Add the domain name "bar".
    OptionStringPtr dn2(new OptionString(Option::V4, DHO_DOMAIN_NAME, "bar"));
    subnet2->getCfgOption()->add(dn2, false, false, DHCP4_OPTION_SPACE);
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet2->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    network->add(subnet2);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(offer->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = offer->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());

    // domain-name option "bar" was added.
    got_opt = offer->getOption(DHO_DOMAIN_NAME);
    ASSERT_TRUE(got_opt);
    OptionStringPtr got_dn_opt =
        boost::dynamic_pointer_cast<OptionString>(got_opt);
    ASSERT_TRUE(got_dn_opt);
    EXPECT_EQ("bar", got_dn_opt->getValue());
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in another subnet of the shared network.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredRequestAnother) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the domain name "foo".
    OptionStringPtr dn(new OptionString(Option::V4, DHO_DOMAIN_NAME, "foo"));
    subnet_->getCfgOption()->add(dn, false, false, DHCP4_OPTION_SPACE);
    // Add another subnet,
    Subnet4Ptr subnet2 = Subnet4::create(IOAddress("192.0.3.0"), 24,
                                         unspecified,
                                         unspecified,
                                         valid_lft,
                                         subnet_->getID() + 1);
    // Add the domain name "bar".
    OptionStringPtr dn2(new OptionString(Option::V4, DHO_DOMAIN_NAME, "bar"));
    subnet2->getCfgOption()->add(dn2, false, false, DHCP4_OPTION_SPACE);
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet2->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    network->add(subnet2);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(ack->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = ack->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());

    // domain-name option "bar" was added.
    got_opt = ack->getOption(DHO_DOMAIN_NAME);
    ASSERT_TRUE(got_opt);
    OptionStringPtr got_dn_opt =
        boost::dynamic_pointer_cast<OptionString>(got_opt);
    ASSERT_TRUE(got_dn_opt);
    EXPECT_EQ("bar", got_dn_opt->getValue());
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in another subnet of the shared network
// with a matching guard (another subnet is used when subnet selection
// skips not matching guards).
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredDiscoverGuarded) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the domain name "foo".
    OptionStringPtr dn(new OptionString(Option::V4, DHO_DOMAIN_NAME, "foo"));
    subnet_->getCfgOption()->add(dn, false, false, DHCP4_OPTION_SPACE);
    // Add another subnet,
    Subnet4Ptr subnet2 = Subnet4::create(IOAddress("192.0.3.0"), 24,
                                         unspecified,
                                         unspecified,
                                         valid_lft,
                                         subnet_->getID() + 1);
    // Add the "guard" guard to subnet2.
    subnet2->allowClientClass("guard");
    // Add the domain name "bar".
    OptionStringPtr dn2(new OptionString(Option::V4, DHO_DOMAIN_NAME, "bar"));
    subnet2->getCfgOption()->add(dn2, false, false, DHCP4_OPTION_SPACE);
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet2->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    network->add(subnet2);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Put into the "guard" class.
    srv_->classifyPacket(dis);
    dis->addClass("guard");

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(offer->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = offer->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());

    // domain-name option "bar" was added.
    got_opt = offer->getOption(DHO_DOMAIN_NAME);
    ASSERT_TRUE(got_opt);
    OptionStringPtr got_dn_opt =
        boost::dynamic_pointer_cast<OptionString>(got_opt);
    ASSERT_TRUE(got_dn_opt);
    EXPECT_EQ("bar", got_dn_opt->getValue());
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in another subnet of the shared network
// with a matching guard (another subnet is used when subnet selection
// skips not matching guards).
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredRequestGuarded) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the domain name "foo".
    OptionStringPtr dn(new OptionString(Option::V4, DHO_DOMAIN_NAME, "foo"));
    subnet_->getCfgOption()->add(dn, false, false, DHCP4_OPTION_SPACE);
    // Add another subnet,
    Subnet4Ptr subnet2 = Subnet4::create(IOAddress("192.0.3.0"), 24,
                                         unspecified,
                                         unspecified,
                                         valid_lft,
                                         subnet_->getID() + 1);
    // Add the "guard" guard to subnet2.
    subnet2->allowClientClass("guard");
    // Add the domain name "bar".
    OptionStringPtr dn2(new OptionString(Option::V4, DHO_DOMAIN_NAME, "bar"));
    subnet2->getCfgOption()->add(dn2, false, false, DHCP4_OPTION_SPACE);
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet2->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    network->add(subnet2);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Put into the "guard" class.
    srv_->classifyPacket(req);
    req->addClass("guard");

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(ack->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = ack->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());

    // domain-name option "bar" was added.
    got_opt = ack->getOption(DHO_DOMAIN_NAME);
    ASSERT_TRUE(got_opt);
    OptionStringPtr got_dn_opt =
        boost::dynamic_pointer_cast<OptionString>(got_opt);
    ASSERT_TRUE(got_dn_opt);
    EXPECT_EQ("bar", got_dn_opt->getValue());
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is not offered
// when the option is configured in another subnet of the shared network
// with a not matching guard.
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredDiscoverGuarded) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet with a pool.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);

    // Add another subnet,
    Subnet4Ptr subnet2 = Subnet4::create(IOAddress("192.0.3.0"), 24,
                                         unspecified,
                                         unspecified,
                                         valid_lft,
                                         subnet_->getID() + 1);
    // Add the "guard" guard to subnet2.
    subnet2->allowClientClass("guard");
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet2->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    network->add(subnet2);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Not in the "guard" class.
    srv_->classifyPacket(dis);
    EXPECT_FALSE(dis->inClass("guard"));

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // An address was offered.
    EXPECT_FALSE(offer->getYiaddr().isV4Zero());

    // No v6-only-preferred option.
    EXPECT_FALSE(offer->getOption(DHO_V6_ONLY_PREFERRED));
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is not offered
// when the option is configured in another subnet of the shared network
// with a not matching guard.
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredRequestGuarded) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet with a pool.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);

    // Add another subnet,
    Subnet4Ptr subnet2 = Subnet4::create(IOAddress("192.0.3.0"), 24,
                                         unspecified,
                                         unspecified,
                                         valid_lft,
                                         subnet_->getID() + 1);
    // Add the "guard" guard to subnet2.
    subnet2->allowClientClass("guard");
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet2->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    network->add(subnet2);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Not in the "guard" class.
    srv_->classifyPacket(req);
    EXPECT_FALSE(req->inClass("guard"));

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // An address was offered.
    EXPECT_FALSE(ack->getYiaddr().isV4Zero());

    // No v6-only-preferred option.
    EXPECT_FALSE(ack->getOption(DHO_V6_ONLY_PREFERRED));
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in the shared network.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredDiscoverSharedNetwork) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    network->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);

    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(offer->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = offer->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is offered
// when the option is configured in the shared network.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredRequestSharedNetwork) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Create a shared network.
    SharedNetwork4Ptr network(new SharedNetwork4("one"));
    network->add(subnet_);
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    network->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);

    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(network);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // 0.0.0.0 was offered.
    EXPECT_TRUE(ack->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = ack->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is not offered
// when the option is configured in a pool (i.e. either the pool is used
// to assign the address or the pool is not used to add options).
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredDiscoverPool) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet with a pool.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);

    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    pool_->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);

    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // Address 192.0.2.100 was offered.
    EXPECT_EQ("192.0.2.100", offer->getYiaddr().toText());

    // v6-only-preferred option was added because the address is from the pool.
    OptionPtr got_opt = offer->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is not offered
// when the option is configured in a pool (i.e. either the pool is used
// to assign the address or the pool is not used to add options).
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredRequestPool) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet with a pool.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());

    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);

    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    pool_->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);

    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // Address 192.0.2.100 was offered.
    EXPECT_EQ("192.0.2.100", ack->getYiaddr().toText());

    // v6-only-preferred option was added because the address is from the pool.
    OptionPtr got_opt = ack->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that discover requesting v6-only-preferred 0.0.0.0 is not offered
// when the option is configured at the global level.
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredDiscoverGlobal) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgOption()->
        add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // Get the DHCPOFFER.
    Pkt4Ptr offer = srv_->processDiscover(dis);
    ASSERT_TRUE(offer);
    checkResponse(offer, DHCPOFFER, 1234);

    // An address was offered.
    EXPECT_FALSE(offer->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = offer->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that request requesting v6-only-preferred 0.0.0.0 is not offered
// when the option is configured at the global level.
TEST_F(Dhcpv4SrvTest, noV6OnlyPreferredRequestGlobal) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().getStagingCfg()->getCfgOption()->
        add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // Get the DHCPACK.
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);
    checkResponse(ack, DHCPACK, 1234);

    // An address was offered.
    EXPECT_FALSE(ack->getYiaddr().isV4Zero());

    // v6-only-preferred option was added.
    OptionPtr got_opt = ack->getOption(DHO_V6_ONLY_PREFERRED);
    ASSERT_TRUE(got_opt);
    OptionUint32Ptr got_v6op_opt =
        boost::dynamic_pointer_cast<OptionUint32>(got_opt);
    ASSERT_TRUE(got_v6op_opt);
    EXPECT_EQ(v6only_wait, got_v6op_opt->getValue());
}

// Verify that when discover requesting v6-only-preferred 0.0.0.0 is offered
// but the option is not added to the response is an error case.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredDiscoverError) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet_->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    // Cancel the v6-only-preferred option at the global level.
    CfgMgr::instance().getStagingCfg()->getCfgOption()->
        add(v6op_opt, false, true, DHCP4_OPTION_SPACE);
    CfgMgr::instance().commit();

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");
    dis->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    dis->addOption(prl);

    // No DHCPOFFER is returned.
    EXPECT_FALSE(srv_->processDiscover(dis));
}

// Verify that when request requesting v6-only-preferred 0.0.0.0 is offered
// but the option is not added to the response is an error case.
TEST_F(Dhcpv4SrvTest, v6OnlyPreferredRequestError) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Recreate subnet.
    Triplet<uint32_t> unspecified;
    Triplet<uint32_t> valid_lft(500, 1000, 1500);
    subnet_ = Subnet4::create(IOAddress("192.0.2.0"), 24,
                              unspecified,
                              unspecified,
                              valid_lft,
                              subnet_->getID());
    // Add the v6-only-preferred option data.
    const uint32_t v6only_wait(3600);
    OptionUint32Ptr v6op_opt(new OptionUint32(Option::V4,
                                              DHO_V6_ONLY_PREFERRED,
                                              v6only_wait));
    subnet_->getCfgOption()->add(v6op_opt, false, false, DHCP4_OPTION_SPACE);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    // Cancel the v6-only-preferred option at the global level.
    CfgMgr::instance().getStagingCfg()->getCfgOption()->
        add(v6op_opt, false, true, DHCP4_OPTION_SPACE);
    CfgMgr::instance().commit();

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");
    req->setIndex(ETH1_INDEX);

    // Add a PRL with v6-only-preferred.
    OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));
    ASSERT_TRUE(prl);
    prl->addValue(DHO_V6_ONLY_PREFERRED);
    req->addOption(prl);

    // No DHCPACK is returned.
    EXPECT_FALSE(srv_->processRequest(req));
}

/// @brief Test fixture for recoverStashedAgentOption.
class StashAgentOptionTest : public Dhcpv4SrvTest {
public:
    /// @brief Constructor.
    StashAgentOptionTest() : addr_("192.0.1.2") {
        query_.reset(new Pkt4(DHCPREQUEST, 1234));
        query_->addOption(generateClientId());
        hwaddr_ = generateHWAddr();
        query_->setHWAddr(hwaddr_);
        query_->setCiaddr(addr_);

        rai_.reset(new OptionCustom(LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF(),
                                    Option::V4));
        rai_sub_.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                                  addr_.toBytes()));
        rai_->addOption(rai_sub_);

        lease_.reset(new Lease4(addr_, hwaddr_, client_id_, 100, time(0), 1));
        user_context_ = Element::createMap();
        lease_->setContext(user_context_);
        isc_ = Element::createMap();
        user_context_->set("ISC", isc_);
        relay_agent_info_ = Element::createMap();
        isc_->set("relay-agent-info", relay_agent_info_);
        sub_options_ = Element::create(rai_->toHexString());
        relay_agent_info_->set("sub-options", sub_options_);

        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=4");

        CfgMgr::instance().clear();
        CfgMgr::instance().getStagingCfg()->
            addConfiguredGlobal("stash-agent-options", Element::create(true));
    }

    /// @brief Destructor.
    virtual ~StashAgentOptionTest() {
        CfgMgr::instance().clear();
        LeaseMgrFactory::destroy();
    }

    /// @brief Client address.
    IOAddress addr_;

    /// @brief Query.
    Pkt4Ptr query_;

    /// @brief Hardware address.
    HWAddrPtr hwaddr_;

    /// @brief RAI option.
    OptionPtr rai_;

    /// @brief RAI suboption.
    OptionPtr rai_sub_;

    /// @brief Lease.
    Lease4Ptr lease_;

    /// @brief Lease user context.
    ElementPtr user_context_;

    /// @brief ISC map.
    ElementPtr isc_;

    /// @brief Relay agent info (map or string).
    ElementPtr relay_agent_info_;

    /// @brief Sub-options i.e. RAI content (hexstring).
    ElementPtr sub_options_;
};

// Verify the basic positive case.
TEST_F(StashAgentOptionTest, basic) {
    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);
    EXPECT_EQ(rai_query->toHexString(true), rai_->toHexString(true));
    EXPECT_TRUE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the client id has priority i.e. when the client id
// is present the hardware address is ignored.
TEST_F(StashAgentOptionTest, clientId) {
    // Change the hardware address.
    auto hwaddr2 = generateHWAddr(8);
    ASSERT_NE(hwaddr_, hwaddr2);
    query_->setHWAddr(hwaddr2);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);
    EXPECT_EQ(rai_query->toHexString(true), rai_->toHexString(true));
    EXPECT_TRUE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the hardware address is used when there is no client id.
TEST_F(StashAgentOptionTest, hardwareAddress) {
    // No longer use the client id.
    query_->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    lease_.reset(new Lease4(addr_, hwaddr_, ClientIdPtr(), 100, time(0), 1));
    lease_->setContext(user_context_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);
    EXPECT_EQ(rai_query->toHexString(true), rai_->toHexString(true));
    EXPECT_TRUE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that old extended info format is supported.
TEST_F(StashAgentOptionTest, oldExtendedInfo) {
    // Use the old extended info format.
    isc_->set("relay-agent-info", sub_options_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);
    EXPECT_EQ(rai_query->toHexString(true), rai_->toHexString(true));
    EXPECT_TRUE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that empty RAI is supported.
TEST_F(StashAgentOptionTest, emptyRelayAgentInfo) {
    // Add an empty RAI.
    OptionPtr empty_rai(new OptionCustom(LibDHCP::DHO_DHCP_AGENT_OPTIONS_DEF(),
                                         Option::V4));
    query_->addOption(empty_rai);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);
    EXPECT_FALSE(rai_query->getOptions().empty());
    EXPECT_EQ(rai_query->toHexString(true), rai_->toHexString(true));
    EXPECT_TRUE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the client address must be not zero.
TEST_F(StashAgentOptionTest, clientAddress) {
    // Set the client address to 0.0.0.0.
    query_->setCiaddr(IOAddress::IPV4_ZERO_ADDRESS());

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the gateway address must be zero.
TEST_F(StashAgentOptionTest, gatewayAddress) {
    // Set the gateway address to not zero.
    query_->setGiaddr(IOAddress("192.0.2.1"));

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));

    // Even broadcast is not accepted.
    query_->setGiaddr(IOAddress::IPV4_BCAST_ADDRESS());
    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the stash-agent-options is required.
TEST_F(StashAgentOptionTest, stashAgentOption) {
    // Not commit the config.

    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the message type must be DHCPREQUEST.
TEST_F(StashAgentOptionTest, request) {
    // Build a DISCOVER query.
    query_.reset(new Pkt4(DHCPDISCOVER, 1234));
    query_->addOption(generateClientId());
    hwaddr_ = generateHWAddr();
    query_->setHWAddr(hwaddr_);
    query_->setCiaddr(addr_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that if there is a not empty RAI it will fail.
TEST_F(StashAgentOptionTest, notEmptyRelayAgentInfo) {
    // Add a not empty RAI.
    query_->addOption(rai_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that if the query is already in STASH_AGENT_OPTIONS it will fail.
TEST_F(StashAgentOptionTest, inClass) {
    // Add the STASH_AGENT_OPTIONS class.
    query_->addClass("STASH_AGENT_OPTIONS");

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_TRUE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the lease is required.
TEST_F(StashAgentOptionTest, lease) {
    CfgMgr::instance().commit();
    // Not add the lease.

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that if the lease is expired it will fail.
TEST_F(StashAgentOptionTest, expired) {
    // Expired the lease.
    lease_.reset(new Lease4(addr_, hwaddr_, client_id_, 100,
                            time(0) - 1000, 1));
    lease_->setContext(user_context_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the lease user context is required.
TEST_F(StashAgentOptionTest, userContext) {
    // Remove lease user context.
    lease_->setContext(ElementPtr());

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the lease user context must be a map.
// getLeaseClientClasses throws BadValue on addLease.

// Verify that the ISC entry in the lease user context is required.
TEST_F(StashAgentOptionTest, iscEntry) {
    // Remove the isc entry.
    user_context_ = Element::createMap();
    user_context_->set("foo", Element::create("bar"));
    lease_->setContext(user_context_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the ISC entry in the lease user context must be a map.
// getLeaseClientClasses throws BadValue on addLease.

// Verify that the relay-agent-info entry is required.
TEST_F(StashAgentOptionTest, relayAgentInfoEntry) {
    // Remove the relay-agent-info entry.
    isc_ = Element::createMap();
    isc_->set("foo", Element::create("bar"));
    user_context_->set("ISC", isc_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the relay-agent-info entry must be a map or a string.
TEST_F(StashAgentOptionTest, badRelayAgentInfoEntry) {
    // Set the relay-agent-info entry to a boolean.
    relay_agent_info_ = Element::create(true);
    isc_->set("relay-agent-info", relay_agent_info_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the sub-options entry is required in new extended info format.
TEST_F(StashAgentOptionTest, subOptionsEntry) {
    // Remove the sub-options entry.
    relay_agent_info_ = Element::createMap();
    relay_agent_info_->set("foo", Element::create("bar"));
    isc_->set("relay-agent-info", relay_agent_info_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the sub-options entry must be a string.
TEST_F(StashAgentOptionTest, badSubOptionsEntry) {
    // Set the sub-options entry to a boolean.
    sub_options_ = Element::create(true);
    relay_agent_info_->set("sub-options", sub_options_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the sub-options entry must be not empty.
TEST_F(StashAgentOptionTest, emptySubOptionsEntry) {
    // Set the sub-options entry to empty.
    sub_options_ = Element::create("");
    relay_agent_info_->set("sub-options", sub_options_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the sub-options entry must be a valid hexstring.
TEST_F(StashAgentOptionTest, hexString) {
    // Set the sub-options entry to invalid hexstring.
    sub_options_ = Element::create("foobar");
    relay_agent_info_->set("sub-options", sub_options_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_THROW(srv_->recoverStashedAgentOption(query_), BadValue);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the sub-options entry must be a valid RAI content.
TEST_F(StashAgentOptionTest, badRelayAgentInfo) {
    // Set the sub-options entry to truncated RAI content.
    string content = sub_options_->stringValue();
    ASSERT_LT(2, content.size());
    content.resize(content.size() - 2);
    sub_options_ = Element::create(content);
    relay_agent_info_->set("sub-options", sub_options_);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));

    // Set the sub-options entry to invalid RAI content.
    content = rai_->toHexString();
    // length is in the second octet so patch the third hexdigit.
    ASSERT_LE(5, content.size());
    ASSERT_EQ('4', content[5]);
    content[5] = '3';
    sub_options_ = Element::create(content);
    relay_agent_info_->set("sub-options", sub_options_);

    EXPECT_THROW(srv_->recoverStashedAgentOption(query_), OptionParseError);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that the client id when set must match.
TEST_F(StashAgentOptionTest, badClientId) {
    // Use another the client id.
    query_->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    query_->addOption(generateClientId(8));

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

// Verify that when the client id is not used the hardware address must match.
TEST_F(StashAgentOptionTest, badHwareAddress) {
    // No longer use the client id.
    query_->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    lease_.reset(new Lease4(addr_, hwaddr_, ClientIdPtr(), 100, time(0), 1));
    lease_->setContext(user_context_);

    // Change the hardware address.
    auto hwaddr2 = generateHWAddr(8);
    ASSERT_NE(hwaddr_, hwaddr2);
    query_->setHWAddr(hwaddr2);

    CfgMgr::instance().commit();
    EXPECT_NO_THROW(LeaseMgrFactory::instance().addLease(lease_));

    EXPECT_NO_THROW(srv_->recoverStashedAgentOption(query_));
    OptionPtr rai_query = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    EXPECT_FALSE(rai_query);
    EXPECT_FALSE(query_->inClass("STASH_AGENT_OPTIONS"));
}

/// @todo: lease ownership

/// @todo: Implement proper tests for MySQL lease/host database,
///        see ticket #4214.

} // end of anonymous namespace
