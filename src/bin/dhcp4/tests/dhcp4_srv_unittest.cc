// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <sstream>

#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp/tests/pkt_captures.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_vendor.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/json_config_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/host_mgr.h>
#include <gtest/gtest.h>
#include <stats/stats_mgr.h>
#include <boost/scoped_ptr.hpp>

#include <iostream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::dhcp::test;

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
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
    "\"valid-lifetime\": 4000 }"
};

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
    req->setIndex(1);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);

    Pkt4Ptr resp = ex.getResponse();
    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));
    // Set hops value for the response.
    resp->setHops(req->getHops());

    // This function never throws.
    ASSERT_NO_THROW(NakedDhcpv4Srv::adjustIfaceData(ex));

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
    EXPECT_EQ(1, resp->getIndex());

    // Let's do another test and set other fields: ciaddr and
    // flags. By doing it, we want to make sure that the relay
    // address will take precedence.
    req->setGiaddr(IOAddress("192.0.1.50"));
    req->setCiaddr(IOAddress("192.0.1.11"));
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    resp->setYiaddr(IOAddress("192.0.1.100"));
    // Clear remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(NakedDhcpv4Srv::adjustIfaceData(ex));

    // Response should be sent back to the relay address.
    EXPECT_EQ("192.0.1.50", resp->getRemoteAddr().toText());
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
    req->setIndex(1);

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

    ASSERT_NO_THROW(NakedDhcpv4Srv::adjustIfaceData(ex));

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
    EXPECT_EQ(1, resp->getIndex());

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
    req->setIndex(1);

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
    // ddirect responses to the client which doesn't have an address yet. In
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
    ASSERT_NO_THROW(NakedDhcpv4Srv::adjustIfaceData(ex));

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
    EXPECT_EQ(1, resp->getIndex());

    // We also want to test the case when the server has capability to
    // respond directly to the client which is not configured. Server
    // makes decision whether it responds directly or broadcast its
    // response based on the capability reported by IfaceMgr. We can
    // control whether the current packet filter returns that it supports
    // direct responses or not.
    test_config.setDirectResponse(true);

    // Now we expect that the server will send its response to the
    // address assigned for the client.
    ASSERT_NO_THROW(NakedDhcpv4Srv::adjustIfaceData(ex));

    EXPECT_EQ("192.0.1.13", resp->getRemoteAddr().toText());
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
    req->setIndex(1);

    // Let's set the broadcast flag.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create the exchange using the req.
    Dhcpv4Exchange ex = createExchange(req);
    Pkt4Ptr resp = ex.getResponse();

    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.1.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(NakedDhcpv4Srv::adjustIfaceData(ex));

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
    EXPECT_EQ(1, resp->getIndex());

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

    // Add options which must be copied
    // client-id echo is optional
    // rai echo is done in relayAgentInfoEcho
    // Do subnet selection option
    OptionDefinitionPtr sbnsel_def = LibDHCP::getOptionDef(Option::V4,
                                                           DHO_SUBNET_SELECTION);
    ASSERT_TRUE(sbnsel_def);
    OptionCustomPtr sbnsel(new OptionCustom(*sbnsel_def, Option::V4));
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

// This test verifies that the server identifier option is appended to
// a specified DHCPv4 message and the server identifier is correct.
TEST_F(Dhcpv4SrvTest, appendServerID) {
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    Dhcpv4Exchange ex = createExchange(query);
    Pkt4Ptr response = ex.getResponse();

    // Set a local address. It is required by the function under test
    // to create the Server Identifier option.
    response->setLocalAddr(IOAddress("192.0.3.1"));

    // Append the Server Identifier.
    ASSERT_NO_THROW(NakedDhcpv4Srv::appendServerID(ex));

    // Make sure that the option has been added.
    OptionPtr opt = response->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    ASSERT_TRUE(opt);
    Option4AddrLstPtr opt_server_id =
        boost::dynamic_pointer_cast<Option4AddrLst>(opt);
    ASSERT_TRUE(opt_server_id);

    // The option is represented as a list of IPv4 addresses but with
    // only one address added.
    Option4AddrLst::AddressContainer addrs = opt_server_id->getAddresses();
    ASSERT_EQ(1, addrs.size());
    // This address should match the local address of the packet.
    EXPECT_EQ("192.0.3.1", addrs[0].toText());
}

// Sanity check. Verifies that both Dhcpv4Srv and its derived
// class NakedDhcpv4Srv can be instantiated and destroyed.
TEST_F(Dhcpv4SrvTest, basic) {

    // Check that the base class can be instantiated
    boost::scoped_ptr<Dhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000, false,
                                            false)));
    srv.reset();
    // We have to close open sockets because further in this test we will
    // call the Dhcpv4Srv constructor again. This constructor will try to
    // set the appropriate packet filter class for IfaceMgr. This requires
    // that all sockets are closed.
    IfaceMgr::instance().closeSockets();

    // Check that the derived class can be instantiated
    boost::scoped_ptr<NakedDhcpv4Srv> naked_srv;
    ASSERT_NO_THROW(
        naked_srv.reset(new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000)));
    // Close sockets again for the next test.
    IfaceMgr::instance().closeSockets();

    ASSERT_NO_THROW(naked_srv.reset(new NakedDhcpv4Srv(0)));
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

TEST_F(Dhcpv4SrvTest, processRelease) {
    NakedDhcpv4Srv srv;
    Pkt4Ptr pkt(new Pkt4(DHCPRELEASE, 1234));

    // Should not throw
    EXPECT_NO_THROW(srv.processRelease(pkt));
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

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_, true, true);

    // Check identifiers
    checkServerId(offer, srv->getServerID());
    checkClientId(offer, clientid);
}

// Check that option 58 and 59 are not included if they are not specified.
TEST_F(Dhcpv4SrvTest, DiscoverNoTimers) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");

    // Recreate a subnet but set T1 and T2 to "unspecified".
    subnet_.reset(new Subnet4(IOAddress("192.0.2.0"), 24,
                              Triplet<uint32_t>(),
                              Triplet<uint32_t>(),
                              3000));
    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // T1 and T2 timers must not be present.
    checkAddressParams(offer, subnet_, false, false);

    // Check identifiers
    checkServerId(offer, srv->getServerID());
    checkClientId(offer, clientid);
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

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("10.1.2.3");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.107"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);
    dis->setIface("eth1");

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_, true, true);

    EXPECT_NE(offer->getYiaddr(), hint);

    // Check identifiers
    checkServerId(offer, srv->getServerID());
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

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis1 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr dis2 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 2345));
    Pkt4Ptr dis3 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 3456));

    dis1->setRemoteAddr(IOAddress("192.0.2.1"));
    dis2->setRemoteAddr(IOAddress("192.0.2.2"));
    dis3->setRemoteAddr(IOAddress("192.0.2.3"));

    // Assign interfaces
    dis1->setIface("eth1");
    dis2->setIface("eth1");
    dis3->setIface("eth1");

    // Different client-id sizes
    OptionPtr clientid1 = generateClientId(4); // length 4
    OptionPtr clientid2 = generateClientId(5); // length 5
    OptionPtr clientid3 = generateClientId(6); // length 6

    dis1->addOption(clientid1);
    dis2->addOption(clientid2);
    dis3->addOption(clientid3);

    // Pass it to the server and get an offer
    Pkt4Ptr offer1 = srv->processDiscover(dis1);
    Pkt4Ptr offer2 = srv->processDiscover(dis2);
    Pkt4Ptr offer3 = srv->processDiscover(dis3);

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
    checkServerId(offer1, srv->getServerID());
    checkServerId(offer2, srv->getServerID());
    checkServerId(offer3, srv->getServerID());
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

    NakedDhcpv4Srv srv(0);

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv.processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);
    checkClientId(offer, clientid);

    CfgMgr::instance().echoClientId(false);
    offer = srv.processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);
    checkClientId(offer, clientid);
}

// Check that option 58 and 59 are not included if they are not specified.
TEST_F(Dhcpv4SrvTest, RequestNoTimers) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setIface("eth1");

    // Recreate a subnet but set T1 and T2 to "unspecified".
    subnet_.reset(new Subnet4(IOAddress("192.0.2.0"), 24,
                              Triplet<uint32_t>(),
                              Triplet<uint32_t>(),
                              3000));
    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"),
                               IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    // Pass it to the server and get an ACK.
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);

    // T1 and T2 timers must not be present.
    checkAddressParams(ack, subnet_, false, false);

    // Check identifiers
    checkServerId(ack, srv->getServerID());
    checkClientId(ack, clientid);
}

// Checks whether echoing back client-id is controllable
TEST_F(Dhcpv4SrvTest, requestEchoClientId) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setIface("eth1");

    // Pass it to the server and get ACK
    Pkt4Ptr ack = srv.processRequest(dis);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    checkClientId(ack, clientid);

    CfgMgr::instance().echoClientId(false);
    ack = srv.processRequest(dis);

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

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
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
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              temp_valid, temp_t1, temp_t2, temp_timestamp,
                              subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set.
    // Constructed lease looks as if it was assigned 10 seconds ago
    // EXPECT_EQ(l->t1_, temp_t1);
    // EXPECT_EQ(l->t2_, temp_t2);
    EXPECT_EQ(l->valid_lft_, temp_valid);
    EXPECT_EQ(l->cltt_, temp_timestamp);

    // Let's create a RENEW
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress(addr));
    req->setYiaddr(addr);
    req->setCiaddr(addr); // client's address
    req->setIface("eth0");
    req->setHWAddr(hwaddr2);

    req->addOption(clientid);
    req->addOption(srv->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(addr, ack->getYiaddr());

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(ack, subnet_, true, true);

    // Check identifiers
    checkServerId(ack, srv->getServerID());
    checkClientId(ack, clientid);

    // Check that the lease is really in the database
    l = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt were really updated
    EXPECT_EQ(l->t1_, subnet_->getT1());
    EXPECT_EQ(l->t2_, subnet_->getT2());
    EXPECT_EQ(l->valid_lft_, subnet_->getValid());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

// This test verifies that the logic which matches server identifier in the
// received message with server identifiers used by a server works correctly:
// - a message with no server identifier is accepted,
// - a message with a server identifier which matches one of the server
// identifiers used by a server is accepted,
// - a message with a server identifier which doesn't match any server
// identifier used by a server, is not accepted.
TEST_F(Dhcpv4SrvTest, acceptServerId) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    Pkt4Ptr pkt(new Pkt4(DHCPREQUEST, 1234));
    // If no server identifier option is present, the message is always
    // accepted.
    EXPECT_TRUE(srv.acceptServerId(pkt));

    // Create definition of the server identifier option.
    OptionDefinition def("server-identifier", DHO_DHCP_SERVER_IDENTIFIER,
                         "ipv4-address", false);

    // Add a server identifier option which doesn't match server ids being
    // used by the server. The accepted server ids are the IPv4 addresses
    // configured on the interfaces. The 10.1.2.3 is not configured on
    // any interfaces.
    OptionCustomPtr other_serverid(new OptionCustom(def, Option::V6));
    other_serverid->writeAddress(IOAddress("10.1.2.3"));
    pkt->addOption(other_serverid);
    EXPECT_FALSE(srv.acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on eth0 interface.
    // A DHCPv4 message holding this server identifier should be accepted.
    OptionCustomPtr eth0_serverid(new OptionCustom(def, Option::V6));
    eth0_serverid->writeAddress(IOAddress("192.0.2.3"));
    ASSERT_NO_THROW(pkt->addOption(eth0_serverid));
    EXPECT_TRUE(srv.acceptServerId(pkt));

    // Remove the server identifier.
    ASSERT_NO_THROW(pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Add a server id being an IPv4 address configured on eth1 interface.
    // A DHCPv4 message holding this server identifier should be accepted.
    OptionCustomPtr eth1_serverid(new OptionCustom(def, Option::V6));
    eth1_serverid->writeAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(pkt->addOption(eth1_serverid));
    EXPECT_TRUE(srv.acceptServerId(pkt));

}

// @todo: Implement tests for rejecting renewals

// This test verifies if the sanityCheck() really checks options presence.
TEST_F(Dhcpv4SrvTest, sanityCheck) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    pkt->setHWAddr(generateHWAddr(6));

    // Server-id is optional for information-request, so
    EXPECT_NO_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::OPTIONAL));

    // Empty packet, no server-id
    EXPECT_THROW(NakedDhcpv4Srv::sanityCheck(pkt, Dhcpv4Srv::MANDATORY),
                 RFCViolation);

    pkt->addOption(srv->getServerID());

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

// Checks if received relay agent info option is echoed back to the client
TEST_F(Dhcpv4SrvTest, relayAgentInfoEcho) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

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
    srv.fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv.run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv.fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv.fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    OptionPtr rai_query = dis->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_query);

    // Get Relay Agent Info from response...
    OptionPtr rai_response = offer->getOption(DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_response);

    EXPECT_TRUE(rai_response->equals(rai_query));
}

/// @todo move vendor options tests to a separate file.
/// @todo Add more extensive vendor options tests, including multiple
///       vendor options

// Checks if vendor options are parsed correctly and requested vendor options
// are echoed back.
TEST_F(Dhcpv4SrvTest, vendorOptionsDocsis) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"data\": \"10.253.175.16\","
        "          \"csv-format\": True"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"10.254.226.0/25\" } ],"
        "    \"subnet\": \"10.254.226.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = PktCaptures::captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv.fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv.run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv.fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv.fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get Relay Agent Info from query...
    OptionPtr vendor_opt_response = offer->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(vendor_opt_response);

    // Check if it's of a correct type
    boost::shared_ptr<OptionVendor> vendor_opt =
        boost::dynamic_pointer_cast<OptionVendor>(vendor_opt_response);
    ASSERT_TRUE(vendor_opt);

    // Get Relay Agent Info from response...
    OptionPtr tftp_servers_generic = vendor_opt->getOption(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(tftp_servers_generic);

    Option4AddrLstPtr tftp_servers =
        boost::dynamic_pointer_cast<Option4AddrLst>(tftp_servers_generic);

    ASSERT_TRUE(tftp_servers);

    Option4AddrLst::AddressContainer addrs = tftp_servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.253.175.16", addrs[0].toText());
}


/// @todo Implement tests for subnetSelect See tests in dhcp6_srv_unittest.cc:
/// selectSubnetAddr, selectSubnetIface, selectSubnetRelayLinkaddr,
/// selectSubnetRelayInterfaceId. Note that the concept of interface-id is not
/// present in the DHCPv4, so not everything is applicable directly.
/// See ticket #3057


// This test verifies that the following option structure can be parsed:
// - option (option space 'foobar')
//   - sub option (option space 'foo')
//      - sub option (option space 'bar')
// @todo Add more thorough unit tests for unpackOptions.
TEST_F(Dhcpv4SrvTest, unpackSubOptions) {
    // Create option definition for each level of encapsulation. Each option
    // definition is for the option code 1. Options may have the same
    // option code because they belong to different option spaces.

    // Top level option encapsulates options which belong to 'space-foo'.
    OptionDefinitionPtr opt_def(new OptionDefinition("option-foobar", 1, "uint32",
                                                      "space-foo"));\
    // Middle option encapsulates options which belong to 'space-bar'
    OptionDefinitionPtr opt_def2(new OptionDefinition("option-foo", 1, "uint16",
                                                      "space-bar"));
    // Low level option doesn't encapsulate any option space.
    OptionDefinitionPtr opt_def3(new OptionDefinition("option-bar", 1,
                                                      "uint8"));

    // Add option definitions to the Configuration Manager. Each goes under
    // different option space.
    CfgOptionDefPtr cfg_option_def =
        CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    ASSERT_NO_THROW(cfg_option_def->add(opt_def, "space-foobar"));
    ASSERT_NO_THROW(cfg_option_def->add(opt_def2, "space-foo"));
    ASSERT_NO_THROW(cfg_option_def->add(opt_def3, "space-bar"));
    CfgMgr::instance().commit();

    // Create the buffer holding the structure of options.
    const uint8_t raw_data[] = {
        // First option starts here.
        0x01,                   // option code = 1
        0x0B,                   // option length = 11
        0x00, 0x01, 0x02, 0x03, // This option carries uint32 value
        // Sub option starts here.
        0x01,                   // option code = 1
        0x05,                   // option length = 5
        0x01, 0x02,             // this option carries uint16 value
        // Last option starts here.
        0x01,                   // option code = 1
        0x01,                   // option length = 1
        0x00                    // This option carries a single uint8
                                // value and has no sub options.
    };
    size_t raw_data_len = sizeof(raw_data) / sizeof(uint8_t);
    OptionBuffer buf(raw_data, raw_data + raw_data_len);

    // Parse options.
    NakedDhcpv4Srv srv(0);
    OptionCollection options;
    ASSERT_NO_THROW(srv.unpackOptions(buf, "space-foobar", options));

    // There should be one top level option.
    ASSERT_EQ(1, options.size());
    boost::shared_ptr<OptionInt<uint32_t> > option_foobar =
        boost::dynamic_pointer_cast<OptionInt<uint32_t> >(options.begin()->
                                                          second);
    ASSERT_TRUE(option_foobar);
    EXPECT_EQ(1, option_foobar->getType());
    EXPECT_EQ(0x00010203, option_foobar->getValue());
    // There should be a middle level option held in option_foobar.
    boost::shared_ptr<OptionInt<uint16_t> > option_foo =
        boost::dynamic_pointer_cast<OptionInt<uint16_t> >(option_foobar->
                                                          getOption(1));
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(1, option_foo->getType());
    EXPECT_EQ(0x0102, option_foo->getValue());
    // Finally, there should be a low level option under option_foo.
    boost::shared_ptr<OptionInt<uint8_t> > option_bar =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >(option_foo->getOption(1));
    ASSERT_TRUE(option_bar);
    EXPECT_EQ(1, option_bar->getType());
    EXPECT_EQ(0x0, option_bar->getValue());
}

// Check parsing of an empty option
TEST_F(Dhcpv4SrvTest, unpackEmptyOption) {
    // Create option definition for the option code 1 without fields.
    OptionDefinitionPtr opt_def(new OptionDefinition("option-empty", 1,
                                                     "empty", false));

    // Add it to the Configuration Manager.
    CfgOptionDefPtr cfg_option_def =
        CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    ASSERT_NO_THROW(cfg_option_def->add(opt_def, "space-empty"));
    CfgMgr::instance().commit();

    // Create the buffer holding the structure of the empty option.
    const uint8_t raw_data[] = {
      0x01,                     // option code = 1
      0x00                      // option length = 0
    };
    size_t raw_data_len = sizeof(raw_data) / sizeof(uint8_t);
    OptionBuffer buf(raw_data, raw_data + raw_data_len);

    // Parse options.
    NakedDhcpv4Srv srv(0);
    OptionCollection options;
    ASSERT_NO_THROW(srv.unpackOptions(buf, "space-empty", options));

    // There should be one option.
    ASSERT_EQ(1, options.size());
    OptionPtr option_empty = options.begin()->second;
    ASSERT_TRUE(option_empty);
    EXPECT_EQ(1, option_empty->getType());
    EXPECT_EQ(2, option_empty->len());
}

// Check parsing of an empty VSI sub option
TEST_F(Dhcpv4SrvTest, unpackVSIOption) {
    // Create the buffer holding the structure of the Vendor-Specific Info
    const uint8_t raw_data[] = {
      43,     // option code = DHO_VENDOR_ENCAPSULATED_OPTIONS
      2,      // option length
      0xdc,   // suboption code
      0       // suboption length
    };
    size_t raw_data_len = sizeof(raw_data) / sizeof(uint8_t);
    OptionBuffer buf(raw_data, raw_data + raw_data_len);

    // Parse options.
    NakedDhcpv4Srv srv(0);
    OptionCollection options;
    ASSERT_NO_THROW(srv.unpackOptions(buf, "dhcp4", options));

    // There should be one option: the VSI
    ASSERT_EQ(1, options.size());
    OptionPtr vsi = options.begin()->second;
    ASSERT_TRUE(vsi);
    EXPECT_EQ(DHO_VENDOR_ENCAPSULATED_OPTIONS, vsi->getType());
    OptionCollection suboptions = vsi->getOptions();

    // There should be one suboption
    ASSERT_EQ(1, suboptions.size());
    OptionPtr eso = suboptions.begin()->second;
    ASSERT_TRUE(eso);
    EXPECT_EQ(0xdc, eso->getType());
    EXPECT_EQ(2, eso->len());
}

// Check parsing of an empty VIVSI sub option
TEST_F(Dhcpv4SrvTest, unpackVIVSIOption) {
    // Create the buffer holding the structure of the Vendor-Identifying
    // Vendor-Specific Info
    const uint8_t raw_data[] = {
      125,            // option code = DHO_VIVSO_SUBOPTIONS
      7,              // option length
      0, 0, 9, 0xbf,  // ISC enterprise number (2495)
      2,              // option data length
      0xdc,           // suboption code
      0               // suboption length
    };
    size_t raw_data_len = sizeof(raw_data) / sizeof(uint8_t);
    OptionBuffer buf(raw_data, raw_data + raw_data_len);

    // Parse options.
    NakedDhcpv4Srv srv(0);
    OptionCollection options;
    ASSERT_NO_THROW(srv.unpackOptions(buf, "dhcp4", options));

    // There should be one option: the VIVSI
    ASSERT_EQ(1, options.size());
    OptionPtr vivsi = options.begin()->second;
    ASSERT_TRUE(vivsi);
    EXPECT_EQ(DHO_VIVSO_SUBOPTIONS, vivsi->getType());

    // Cast to OptionVendor
    OptionVendorPtr vsi = boost::dynamic_pointer_cast<OptionVendor>(vivsi);
    ASSERT_TRUE(vsi);
    EXPECT_EQ(2495, vsi->getVendorId());
    OptionCollection suboptions = vsi->getOptions();

    // There should be one suboption
    ASSERT_EQ(1, suboptions.size());
    OptionPtr eso = suboptions.begin()->second;
    ASSERT_TRUE(eso);
    EXPECT_EQ(0xdc, eso->getType());
    EXPECT_EQ(2, eso->len());
}

// Checks whether the server uses default (0.0.0.0) siaddr value, unless
// explicitly specified
TEST_F(Dhcpv4SrvTest, siaddrDefault) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);
    dis->setIface("eth1");

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);
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

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    subnet_->setSiaddr(IOAddress("192.0.2.123"));

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth1");
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);
    ASSERT_TRUE(offer);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Verify that its value is proper
    EXPECT_EQ("192.0.2.123", offer->getSiaddr().toText());
}

// Checks if the next-server defined as global value is overridden by subnet
// specific value and returned in server messages. There's also similar test for
// checking parser only configuration, see Dhcp4ParserTest.nextServerOverride in
// config_parser_unittest.cc.
TEST_F(Dhcpv4SrvTest, nextServerOverride) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    ConstElementPtr status;

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"next-server\": \"192.0.0.1\", "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"next-server\": \"1.2.3.4\", "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth1");
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv.processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());

    EXPECT_EQ("1.2.3.4", offer->getSiaddr().toText());
}

// Checks if the next-server defined as global value is used in responses
// when there is no specific value defined in subnet and returned to the client
// properly. There's also similar test for checking parser only configuration,
// see Dhcp4ParserTest.nextServerGlobal in config_parser_unittest.cc.
TEST_F(Dhcpv4SrvTest, nextServerGlobal) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    ConstElementPtr status;

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"next-server\": \"192.0.0.1\", "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));

    CfgMgr::instance().commit();

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth1");
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv.processDiscover(dis);
    ASSERT_TRUE(offer);
    EXPECT_EQ(DHCPOFFER, offer->getType());

    EXPECT_EQ("192.0.0.1", offer->getSiaddr().toText());
}

// Checks if server is able to handle a relayed traffic from DOCSIS3.0 modems
TEST_F(Dhcpv4SrvTest, docsisVendorOptionsParse) {

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt4Ptr dis = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(dis->unpack());

    // Check if the packet contain
    OptionPtr opt = dis->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    // This particular capture that we have included options 1 and 5
    EXPECT_TRUE(vendor->getOption(1));
    EXPECT_TRUE(vendor->getOption(5));

    // It did not include options any other options
    EXPECT_FALSE(vendor->getOption(2));
    EXPECT_FALSE(vendor->getOption(3));
    EXPECT_FALSE(vendor->getOption(17));
}

// Checks if server is able to parse incoming docsis option and extract suboption 1 (docsis ORO)
TEST_F(Dhcpv4SrvTest, docsisVendorORO) {

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt4Ptr dis = PktCaptures::captureRelayedDiscover();
    EXPECT_NO_THROW(dis->unpack());

    // Check if the packet contains vendor specific information option
    OptionPtr opt = dis->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    opt = vendor->getOption(DOCSIS3_V4_ORO);
    ASSERT_TRUE(opt);

    OptionUint8ArrayPtr oro = boost::dynamic_pointer_cast<OptionUint8Array>(opt);
    EXPECT_TRUE(oro);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(Dhcpv4SrvTest, vendorOptionsORO) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 2,"
        "          \"data\": \"192.0.2.1, 192.0.2.2\","
        "          \"csv-format\": True"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"eth0\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    boost::shared_ptr<Pkt4> dis(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr and hops to non-zero address as if it was relayed.
    dis->setGiaddr(IOAddress("192.0.2.1"));
    dis->setHops(1);

    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    // Set interface. It is required by the server to generate server id.
    dis->setIface("eth0");

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv.processDiscover(dis);

    // check if we get response at all
    ASSERT_TRUE(offer);

    // We did not include any vendor opts in DISCOVER, so there should be none
    // in OFFER.
    ASSERT_FALSE(offer->getOption(DHO_VIVSO_SUBOPTIONS));

    // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
    // That suboption has code 1 and is a docsis ORO option.
    boost::shared_ptr<OptionUint8Array> vendor_oro(new OptionUint8Array(Option::V4,
                                                                        DOCSIS3_V4_ORO));
    vendor_oro->addValue(DOCSIS3_V4_TFTP_SERVERS); // Request option 33
    OptionPtr vendor(new OptionVendor(Option::V4, 4491));
    vendor->addOption(vendor_oro);
    dis->addOption(vendor);

    // Need to process SOLICIT again after requesting new option.
    offer = srv.processDiscover(dis);
    ASSERT_TRUE(offer);

    // Check if there is a vendor option response
    OptionPtr tmp = offer->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    OptionPtr docsis2 = vendor_resp->getOption(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(docsis2);

    Option4AddrLstPtr tftp_srvs = boost::dynamic_pointer_cast<Option4AddrLst>(docsis2);
    ASSERT_TRUE(tftp_srvs);

    Option4AddrLst::AddressContainer addrs = tftp_srvs->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("192.0.2.1", addrs[0].toText());
    EXPECT_EQ("192.0.2.2", addrs[1].toText());
}

// Test checks whether it is possible to use option definitions defined in
// src/lib/dhcp/docsis3_option_defs.h.
TEST_F(Dhcpv4SrvTest, vendorOptionsDocsisDefinitions) {
    ConstElementPtr x;
    string config_prefix = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-data\": [ {"
        "          \"name\": \"tftp-servers\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": ";
    string config_postfix = ","
        "          \"data\": \"192.0.2.1\","
        "          \"csv-format\": True"
        "        }],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.50\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"valid-lifetime\": 4000,"
        "    \"interface\": \"\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // There is docsis3 (vendor-id=4491) vendor option 2, which is a
    // tftp-server. Its format is list of IPv4 addresses.
    string config_valid = config_prefix + "2" + config_postfix;

    // There is no option 99 defined in vendor-id=4491. As there is no
    // definition, the config should fail.
    string config_bogus = config_prefix + "99" + config_postfix;

    ElementPtr json_bogus = Element::fromJSON(config_bogus);
    ElementPtr json_valid = Element::fromJSON(config_valid);

    NakedDhcpv4Srv srv(0);

    // This should fail (missing option definition)
    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json_bogus));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = configureDhcp4Server(srv, json_valid));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);
}

// Checks if DOCSIS client packets are classified properly
TEST_F(Dhcpv4SrvTest, docsisClientClassification) {

    NakedDhcpv4Srv srv(0);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // vendor-class set to docsis3.0
    Pkt4Ptr dis1;
    ASSERT_NO_THROW(dis1 = PktCaptures::captureRelayedDiscover());
    ASSERT_NO_THROW(dis1->unpack());

    srv.classifyPacket(dis1);

    EXPECT_TRUE(dis1->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0"));
    EXPECT_FALSE(dis1->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // vendor-class set to eRouter1.0
    Pkt4Ptr dis2;
    ASSERT_NO_THROW(dis2 = PktCaptures::captureRelayedDiscover2());
    ASSERT_NO_THROW(dis2->unpack());

    srv.classifyPacket(dis2);

    EXPECT_TRUE(dis2->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));
    EXPECT_FALSE(dis2->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0"));
}

// Checks if client packets are classified properly using match expressions.
TEST_F(Dhcpv4SrvTest, matchClassification) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    // The router class matches incoming packets with foo in a host-name
    // option (code 12) and sets an ip-forwarding option in the response.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[12].text == 'foo'\" } ] }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
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
    Pkt4Ptr query2(new Pkt4(DHCPDISCOVER, 1234));
    query2->setRemoteAddr(IOAddress("192.0.2.1"));
    query2->addOption(clientid);
    query2->setIface("eth1");
    Pkt4Ptr query3(new Pkt4(DHCPDISCOVER, 1234));
    query3->setRemoteAddr(IOAddress("192.0.2.1"));
    query3->addOption(clientid);
    query3->setIface("eth1");

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
    srv.classifyPacket(query1);
    srv.classifyPacket(query2);
    srv.classifyPacket(query3);

    // Packets with the exception of the second should be in the router class
    EXPECT_TRUE(query1->inClass("router"));
    EXPECT_FALSE(query2->inClass("router"));
    EXPECT_TRUE(query3->inClass("router"));

    // Process queries
    Pkt4Ptr response1 = srv.processDiscover(query1);
    Pkt4Ptr response2 = srv.processDiscover(query2);
    Pkt4Ptr response3 = srv.processDiscover(query3);

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
    NakedDhcpv4Srv srv(0);

    // The router class matches incoming packets with foo in a host-name
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"test\": \"option[host-name].text == 'foo'\" } ] }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
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
    srv.classifyPacket(query);

    // The queey should be in the router class
    EXPECT_TRUE(query->inClass("router"));
}

// Checks if client packets are classified properly using match expressions
// using option names and definitions
TEST_F(Dhcpv4SrvTest, matchClassificationOptionDef) {
    NakedDhcpv4Srv srv(0);

    // The router class matches incoming packets with foo in a defined
    // option
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"test\": \"option[my-host-name].text == 'foo'\" } ], "
        "\"option-def\": [ {"
        "    \"name\": \"my-host-name\", "
        "    \"code\": 250, "
        "    \"type\": \"string\" } ] }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
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
    srv.classifyPacket(query);

    // The queey should be in the router class
    EXPECT_TRUE(query->inClass("router"));
}

// Checks subnet options have the priority over class options
TEST_F(Dhcpv4SrvTest, subnetClassPriority) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

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

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
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
    srv.classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    Pkt4Ptr response = srv.processDiscover(query);

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

    NakedDhcpv4Srv srv(0);

    // Subnet and global set an ip-forwarding option in the response.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"subnet4\": [ "
        "{   \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ip-forwarding\", "
        "             \"data\": \"false\" } ] } ], "
        "\"option-data\": ["
        "    {    \"name\": \"ip-forwarding\", "
        "         \"data\": \"true\" } ] }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
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
    Pkt4Ptr response = srv.processDiscover(query);

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

    NakedDhcpv4Srv srv(0);

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

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
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
    srv.classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    Pkt4Ptr response = srv.processDiscover(query);

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
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"client-class\": \"xyzzy\", "
        "    \"subnet\": \"192.0.3.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    // Create a simple packet that we'll use for classification
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setCiaddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This discover does not belong to foo class, so it will not
    // be serviced
    EXPECT_FALSE(srv_.selectSubnet(dis));

    // Let's add the packet to bar class and try again.
    dis->addClass("bar");

    // Still not supported, because it belongs to wrong class.
    EXPECT_FALSE(srv_.selectSubnet(dis));

    // Let's add it to matching class.
    dis->addClass("foo");

    // This time it should work
    EXPECT_TRUE(srv_.selectSubnet(dis));
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
        "        \"ip-address\": \"192.0.5.1\""
        "    },"
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"relay\": { "
        "        \"ip-address\": \"192.0.5.2\""
        "    },"
        "    \"subnet\": \"192.0.3.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet4Ptr subnet1 = (*subnets)[0];
    Subnet4Ptr subnet2 = (*subnets)[1];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This is just a sanity check, we're using regular method: ciaddr 192.0.2.1
    // belongs to the first subnet, so it is selected
    dis->setGiaddr(IOAddress("192.0.2.1"));
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(dis));

    // Relay belongs to the second subnet, so it  should be selected.
    dis->setGiaddr(IOAddress("192.0.3.1"));
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // Now let's check if the relay override for the first subnets works
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(dis));

    // The same check for the second subnet...
    dis->setGiaddr(IOAddress("192.0.5.2"));
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // And finally, let's check if mis-matched relay address will end up
    // in not selecting a subnet at all
    dis->setGiaddr(IOAddress("192.0.5.3"));
    EXPECT_FALSE(srv_.selectSubnet(dis));

    // Finally, check that the relay override works only with relay address
    // (GIADDR) and does not affect client address (CIADDR)
    dis->setGiaddr(IOAddress("0.0.0.0"));
    dis->setHops(0);
    dis->setCiaddr(IOAddress("192.0.5.1"));
    EXPECT_FALSE(srv_.selectSubnet(dis));
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
        "        \"ip-address\": \"192.0.5.1\""
        "    },"
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"relay\": { "
        "        \"ip-address\": \"192.0.5.1\""
        "    },"
        "    \"subnet\": \"192.0.3.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet4Ptr subnet1 = (*subnets)[0];
    Subnet4Ptr subnet2 = (*subnets)[1];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setHops(1);
    dis->setGiaddr(IOAddress("192.0.5.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // This packet does not belong to class foo, so it should be rejected in
    // subnet[0], even though the relay-ip matches. It should be accepted in
    // subnet[1], because the subnet matches and there are no class
    // requirements.
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // Now let's add this packet to class foo and recheck. This time it should
    // be accepted in the first subnet, because both class and relay-ip match.
    dis->addClass("foo");
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(dis));
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
        "        \"ip-address\": \"192.0.5.1\""
        "    },"
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"subnet\": \"192.0.3.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.4.1 - 192.0.4.100\" } ],"
        "    \"client-class\": \"foo\", "
        "    \"subnet\": \"192.0.4.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(3, subnets->size());

    // Let's get them for easy reference
    Subnet4Ptr subnet1 = (*subnets)[0];
    Subnet4Ptr subnet2 = (*subnets)[1];
    Subnet4Ptr subnet3 = (*subnets)[2];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);
    ASSERT_TRUE(subnet3);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Let's create a Relay Agent Information option
    OptionDefinitionPtr rai_def = LibDHCP::getOptionDef(Option::V4,
                                                        DHO_DHCP_AGENT_OPTIONS);
    ASSERT_TRUE(rai_def);
    OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4));
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
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // Setup a relay override for the first subnet as it has a high precedence
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(dis));

    // Put a RAI to select back the second subnet as it has
    // the highest precedence
    dis->addOption(rai);
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // Subnet select option has a lower precedence
    OptionDefinitionPtr sbnsel_def = LibDHCP::getOptionDef(Option::V4,
                                                           DHO_SUBNET_SELECTION);
    ASSERT_TRUE(sbnsel_def);
    OptionCustomPtr sbnsel(new OptionCustom(*sbnsel_def, Option::V4));
    ASSERT_TRUE(sbnsel);
    sbnsel->writeAddress(IOAddress("192.0.2.3"));
    dis->addOption(sbnsel);
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));
    dis->delOption(DHO_SUBNET_SELECTION);

    // Check client-classification still applies
    IOAddress addr_foo("192.0.4.2");
    ols.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                         addr_foo.toBytes()));
    rai->delOption(RAI_OPTION_LINK_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    rai->addOption(ols);
    dis->addOption(rai);
    // Note it shall fail (vs. try the next criterion).
    EXPECT_FALSE(srv_.selectSubnet(dis));
    // Add the packet to the class and check again: now it shall succeed
    dis->addClass("foo");
    EXPECT_TRUE(subnet3 == srv_.selectSubnet(dis));

    // Check it fails with a bad address in the sub-option
    IOAddress addr_bad("10.0.0.1");
    ols.reset(new Option(Option::V4, RAI_OPTION_LINK_SELECTION,
                         addr_bad.toBytes()));
    rai->delOption(RAI_OPTION_LINK_SELECTION);
    dis->delOption(DHO_DHCP_AGENT_OPTIONS);
    rai->addOption(ols);
    dis->addOption(rai);
    EXPECT_FALSE(srv_.selectSubnet(dis));
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
        "        \"ip-address\": \"192.0.5.1\""
        "    },"
        "    \"subnet\": \"192.0.2.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"subnet\": \"192.0.3.0/24\" }, "
        "{   \"pools\": [ { \"pool\": \"192.0.4.1 - 192.0.4.100\" } ],"
        "    \"client-class\": \"foo\", "
        "    \"subnet\": \"192.0.4.0/24\" } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    // Let's get the subnet configuration objects
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(3, subnets->size());

    // Let's get them for easy reference
    Subnet4Ptr subnet1 = (*subnets)[0];
    Subnet4Ptr subnet2 = (*subnets)[1];
    Subnet4Ptr subnet3 = (*subnets)[2];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);
    ASSERT_TRUE(subnet3);

    // Let's create a packet.
    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setIface("eth0");
    dis->setHops(1);
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Let's create a Subnet Selection option
    OptionDefinitionPtr sbnsel_def = LibDHCP::getOptionDef(Option::V4,
                                                           DHO_SUBNET_SELECTION);
    ASSERT_TRUE(sbnsel_def);
    OptionCustomPtr sbnsel(new OptionCustom(*sbnsel_def, Option::V4));
    ASSERT_TRUE(sbnsel);
    sbnsel->writeAddress(IOAddress("192.0.3.2"));

    // This is just a sanity check, we're using regular method: ciaddr 192.0.3.1
    // belongs to the second subnet, so it is selected
    dis->setGiaddr(IOAddress("192.0.3.1"));
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // Setup a relay override for the first subnet as it has a high precedence
    dis->setGiaddr(IOAddress("192.0.5.1"));
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(dis));

    // Put a subnet select option to select back the second subnet as
    // it has the second highest precedence
    dis->addOption(sbnsel);
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(dis));

    // Check client-classification still applies
    sbnsel->writeAddress(IOAddress("192.0.4.2"));
    // Note it shall fail (vs. try the next criterion).
    EXPECT_FALSE(srv_.selectSubnet(dis));
    // Add the packet to the class and check again: now it shall succeed
    dis->addClass("foo");
    EXPECT_TRUE(subnet3 == srv_.selectSubnet(dis));

    // Check it fails with a bad address in the sub-option
    sbnsel->writeAddress(IOAddress("10.0.0.1"));
    EXPECT_FALSE(srv_.selectSubnet(dis));
}

// This test verifies that the direct message is dropped when it has been
// received by the server via an interface for which there is no subnet
// configured. It also checks that the message is not dropped (is processed)
// when it is relayed or unicast.
TEST_F(Dhcpv4SrvTest, acceptDirectRequest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 1234));
    // Set Giaddr and local server's unicast address, but don't set hops.
    // Hops value should not matter. The server will treat the message
    // with the hops value of 0 and non-zero giaddr as relayed.
    pkt->setGiaddr(IOAddress("192.0.10.1"));
    pkt->setRemoteAddr(IOAddress("0.0.0.0"));
    pkt->setLocalAddr(IOAddress("192.0.2.3"));
    pkt->setIface("eth1");
    EXPECT_TRUE(srv.accept(pkt));

    // Let's set hops and check that the message is still accepted as
    // a relayed message.
    pkt->setHops(1);
    EXPECT_TRUE(srv.accept(pkt));

    // Make it a direct message but keep unicast server's address. The
    // messages sent to unicast address should be accepted as they are
    // most likely to renew existing leases. The server should respond
    // to renews so they have to be accepted and processed.
    pkt->setHops(0);
    pkt->setGiaddr(IOAddress("0.0.0.0"));
    EXPECT_TRUE(srv.accept(pkt));

    // Direct message is now sent to a broadcast address. The server
    // should accept this message because it has been received via
    // eth1 for which there is a subnet configured (see test fixture
    // class constructor).
    pkt->setLocalAddr(IOAddress("255.255.255.255"));
    EXPECT_TRUE(srv.accept(pkt));

    // For eth0, there is no subnet configured. Such message is expected
    // to be silently dropped.
    pkt->setIface("eth0");
    EXPECT_FALSE(srv.accept(pkt));

    // But, if the message is unicast it should be accepted, even though
    // it has been received via eth0.
    pkt->setLocalAddr(IOAddress("10.0.0.1"));
    EXPECT_TRUE(srv.accept(pkt));

    // For the DHCPINFORM the ciaddr should be set or at least the source
    // address.
    pkt->setType(DHCPINFORM);
    pkt->setRemoteAddr(IOAddress("10.0.0.101"));
    EXPECT_TRUE(srv.accept(pkt));

    // When neither ciaddr nor source address is present, the packet should
    // be dropped.
    pkt->setRemoteAddr(IOAddress("0.0.0.0"));
    EXPECT_FALSE(srv.accept(pkt));

    // When ciaddr is set, the packet should be accepted.
    pkt->setCiaddr(IOAddress("10.0.0.1"));
    EXPECT_TRUE(srv.accept(pkt));
}

// This test checks that the server rejects a message with invalid type.
TEST_F(Dhcpv4SrvTest, acceptMessageType) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    NakedDhcpv4Srv srv(0);

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
        EXPECT_TRUE(srv.acceptMessageType(Pkt4Ptr(new Pkt4(allowed[i], 1234))))
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
        DHCPLEASEQUERYDONE
    };
    size_t not_allowed_size = sizeof(not_allowed) / sizeof(not_allowed[0]);
    // Actually check that the server will drop these messages.
    for (size_t i = 0; i < not_allowed_size; ++i) {
        EXPECT_FALSE(srv.acceptMessageType(Pkt4Ptr(new Pkt4(not_allowed[i],
                                                            1234))))
            << "Test failed for message type " << i;
    }
}

// Test checks whether statistic is bumped up appropriately when Decline
// message is received.
TEST_F(Dhcpv4SrvTest, statisticsDecline) {
    NakedDhcpv4Srv srv(0);

    pretendReceivingPkt(srv, CONFIGS[0], DHCPDECLINE, "pkt4-decline-received");
}

// Test checks whether statistic is bumped up appropriately when Offer
// message is received (this should never happen in a sane metwork).
TEST_F(Dhcpv4SrvTest, statisticsOfferRcvd) {
    NakedDhcpv4Srv srv(0);

    pretendReceivingPkt(srv, CONFIGS[0], DHCPOFFER, "pkt4-offer-received");
}

// Test checks whether statistic is bumped up appropriately when Ack
// message is received (this should never happen in a sane metwork).
TEST_F(Dhcpv4SrvTest, statisticsAckRcvd) {
    NakedDhcpv4Srv srv(0);

    pretendReceivingPkt(srv, CONFIGS[0], DHCPACK, "pkt4-ack-received");
}

// Test checks whether statistic is bumped up appropriately when Nak
// message is received (this should never happen in a sane metwork).
TEST_F(Dhcpv4SrvTest, statisticsNakRcvd) {
    NakedDhcpv4Srv srv(0);

    pretendReceivingPkt(srv, CONFIGS[0], DHCPNAK, "pkt4-nak-received");
}

// Test checks whether statistic is bumped up appropriately when Release
// message is received.
TEST_F(Dhcpv4SrvTest, statisticsReleaseRcvd) {
    NakedDhcpv4Srv srv(0);

    pretendReceivingPkt(srv, CONFIGS[0], DHCPRELEASE, "pkt4-release-received");
}

// Test checks whether statistic is bumped up appropriately when unknown
// message is received.
TEST_F(Dhcpv4SrvTest, statisticsUnknownRcvd) {
    NakedDhcpv4Srv srv(0);

    pretendReceivingPkt(srv, CONFIGS[0], 200, "pkt4-unknown-received");

    // There should also be pkt4-receive-drop stat bumped up
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr drop_stat = mgr.getObservation("pkt4-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

/// @todo: Implement proper tests for MySQL lease/host database,
///        see ticket #4214.

}; // end of anonymous namespace
