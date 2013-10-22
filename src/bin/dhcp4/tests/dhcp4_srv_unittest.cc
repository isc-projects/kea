// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <config/ccsession.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
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
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/config_parser.h>
#include <hooks/server_hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <gtest/gtest.h>
#include <hooks/server_hooks.h>
#include <hooks/hooks_manager.h>

#include <boost/scoped_ptr.hpp>

#include <fstream>
#include <iostream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::hooks;

#if 0
namespace {

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:

    /// @brief Constructor.
    ///
    /// This constructor disables default modes of operation used by the
    /// Dhcpv4Srv class:
    /// - Send/receive broadcast messages through sockets on interfaces
    /// which support broadcast traffic.
    /// - Direct DHCPv4 traffic - communication with clients which do not
    /// have IP address assigned yet.
    ///
    /// Enabling these modes requires root privilges so they must be
    /// disabled for unit testing.
    ///
    /// Note, that disabling broadcast options on sockets does not impact
    /// the operation of these tests because they use local loopback
    /// interface which doesn't have broadcast capability anyway. It rather
    /// prevents setting broadcast options on other (broadcast capable)
    /// sockets which are opened on other interfaces in Dhcpv4Srv constructor.
    ///
    /// The Direct DHCPv4 Traffic capability can be disabled here because
    /// it is tested with PktFilterLPFTest unittest. The tests which belong
    /// to PktFilterLPFTest can be enabled on demand when root privileges can
    /// be guaranteed.
    ///
    /// @param port port number to listen on; the default value 0 indicates
    /// that sockets should not be opened.
    NakedDhcpv4Srv(uint16_t port = 0)
        : Dhcpv4Srv(port, "type=memfile", false, false) {
    }

    /// @brief fakes packet reception
    /// @param timeout ignored
    ///
    /// The method receives all packets queued in receive queue, one after
    /// another. Once the queue is empty, it initiates the shutdown procedure.
    ///
    /// See fake_received_ field for description
    virtual Pkt4Ptr receivePacket(int /*timeout*/) {

        // If there is anything prepared as fake incoming traffic, use it
        if (!fake_received_.empty()) {
            Pkt4Ptr pkt = fake_received_.front();
            fake_received_.pop_front();
            return (pkt);
        }

        // If not, just trigger shutdown and return immediately
        shutdown();
        return (Pkt4Ptr());
    }

    /// @brief fake packet sending
    ///
    /// Pretend to send a packet, but instead just store it in fake_send_ list
    /// where test can later inspect server's response.
    virtual void sendPacket(const Pkt4Ptr& pkt) {
        fake_sent_.push_back(pkt);
    }

    /// @brief adds a packet to fake receive queue
    ///
    /// See fake_received_ field for description
    void fakeReceive(const Pkt4Ptr& pkt) {
        fake_received_.push_back(pkt);
    }

    virtual ~NakedDhcpv4Srv() {
    }

    /// @brief packets we pretend to receive
    ///
    /// Instead of setting up sockets on interfaces that change between OSes, it
    /// is much easier to fake packet reception. This is a list of packets that
    /// we pretend to have received. You can schedule new packets to be received
    /// using fakeReceive() and NakedDhcpv4Srv::receivePacket() methods.
    list<Pkt4Ptr> fake_received_;

    list<Pkt4Ptr> fake_sent_;

    using Dhcpv4Srv::adjustRemoteAddr;
    using Dhcpv4Srv::processDiscover;
    using Dhcpv4Srv::processRequest;
    using Dhcpv4Srv::processRelease;
    using Dhcpv4Srv::processDecline;
    using Dhcpv4Srv::processInform;
    using Dhcpv4Srv::getServerID;
    using Dhcpv4Srv::loadServerID;
    using Dhcpv4Srv::generateServerID;
    using Dhcpv4Srv::writeServerID;
    using Dhcpv4Srv::sanityCheck;
    using Dhcpv4Srv::srvidToString;
    using Dhcpv4Srv::unpackOptions;
};
#endif

/// dummy server-id file location
static const char* SRVID_FILE = "server-id-test.txt";

namespace isc {
namespace dhcp {
namespace test {

// Sanity check. Verifies that both Dhcpv4Srv and its derived
// class NakedDhcpv4Srv can be instantiated and destroyed.
TEST_F(Dhcpv4SrvTest, basic) {

    // Check that the base class can be instantiated
    boost::scoped_ptr<Dhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000, "type=memfile",
                                            false, false)));
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
    EXPECT_TRUE(naked_srv->getServerID());
    // Close sockets again for the next test.
    IfaceMgr::instance().closeSockets();

    ASSERT_NO_THROW(naked_srv.reset(new NakedDhcpv4Srv(0)));
    EXPECT_TRUE(naked_srv->getServerID());
}

// This test verifies that the destination address of the response
// message is set to giaddr, when giaddr is set to non-zero address
// in the received message.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressRelay) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create the instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr to non-zero address as if it was relayed.
    req->setGiaddr(IOAddress("192.0.2.1"));
    // Set ciaddr to zero. This simulates the client which applies
    // for the new lease.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // Clear broadcast flag.
    req->setFlags(0x0000);

    // Create a response packet. Assume that the new lease have
    // been created and new address allocated. This address is
    // stored in yiaddr field.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    resp->setYiaddr(IOAddress("192.0.2.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // This function never throws.
    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Now the destination address should be relay's address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());

    // Let's do another test and set other fields: ciaddr and
    // flags. By doing it, we want to make sure that the relay
    // address will take precedence.
    req->setGiaddr(IOAddress("192.0.2.50"));
    req->setCiaddr(IOAddress("192.0.2.11"));
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    resp->setYiaddr(IOAddress("192.0.2.100"));
    // Clear remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Response should be sent back to the relay address.
    EXPECT_EQ("192.0.2.50", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to ciaddr when giaddr is set to zero and the ciaddr is set to
// non-zero address in the received message. This is the case when the
// client is in Renew or Rebind state.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressRenewRebind) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Set ciaddr to non-zero address. The response should be sent to this
    // address as the client is in renewing or rebinding state (it is fully
    // configured).
    req->setCiaddr(IOAddress("192.0.2.15"));
    // Let's configure broadcast flag. It should be ignored because
    // we are responding directly to the client having an address
    // and trying to extend his lease. Broadcast flag is only used
    // when new lease is acquired and server must make a decision
    // whether to unicast the response to the acquired address or
    // broadcast it.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create a response.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    // Let's extend the lease for the client in such a way that
    // it will actually get different address. The response
    // should not be sent to this address but rather to ciaddr
    // as client still have ciaddr configured.
    resp->setYiaddr(IOAddress("192.0.2.13"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Check that server responds to ciaddr
    EXPECT_EQ("192.0.2.15", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set correctly when giaddr and ciaddr is zeroed in the received message
// and the new lease is acquired. The lease address is carried in the
// response message in the yiaddr field. In this case destination address
// of the response should be set to yiaddr if server supports direct responses
// to the client which doesn't have an address yet or broadcast if the server
// doesn't support direct responses.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressSelect) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));

    // Let's clear the broadcast flag.
    req->setFlags(0);

    // Create a response.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.2.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // When running unit tests, the IfaceMgr is using the default Packet
    // Filtering class, PktFilterInet. This class does not support direct
    // responses to clients without address assigned. When giaddr and ciaddr
    // are zero and client has just got new lease, the assigned address is
    // carried in yiaddr. In order to send this address to the client,
    // server must broadcast its response.
    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Check that the response is sent to broadcast address as the
    // server doesn't have capability to respond directly.
    EXPECT_EQ("255.255.255.255", resp->getRemoteAddr().toText());

    // We also want to test the case when the server has capability to
    // respond directly to the client which is not configured. Server
    // makes decision whether it responds directly or broadcast its
    // response based on the capability reported by IfaceMgr. In order
    // to set this capability we have to provide a dummy Packet Filter
    // class which would report the support for direct responses.
    // This class is called PktFilterTest.
    IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterTest()));

    // Now we expect that the server will send its response to the
    // address assigned for the client.
    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    EXPECT_EQ("192.0.2.13", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to broadcast address when client set broadcast flag in its
// query. Client sets this flag to indicate that it can't receive direct
// responses from the server when it doesn't have its interface configured.
// Server must respect broadcast flag.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressBroadcast) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));

    // Let's set the broadcast flag.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create a response.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.2.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // When running unit tests, the IfaceMgr is using the default Packet
    // Filtering class, PktFilterInet. This class does not support direct
    // responses to the clients without address assigned. If giaddr and
    // ciaddr are zero and client has just got the new lease, the assigned
    // address is carried in yiaddr. In order to send this address to the
    // client, server must send the response to the broadcast address when
    // direct response is not supported. This conflicts with the purpose
    // of this test which is supposed to verify that responses are sent
    // to broadcast address only, when broadcast flag is set. Therefore,
    // in order to simulate that direct responses are supported we have
    // to replace the default packet filtering class with a dummy class
    // which reports direct response capability.
    IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterTest()));

    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Server must repond to broadcast address when client desired that
    // by setting the broadcast flag in its request.
    EXPECT_EQ("255.255.255.255", resp->getRemoteAddr().toText());
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

TEST_F(Dhcpv4SrvTest, processDecline) {
    NakedDhcpv4Srv srv;
    Pkt4Ptr pkt(new Pkt4(DHCPDECLINE, 1234));

    // Should not throw
    EXPECT_NO_THROW(srv.processDecline(pkt));
}

TEST_F(Dhcpv4SrvTest, processInform) {
    NakedDhcpv4Srv srv;
    Pkt4Ptr pkt(new Pkt4(DHCPINFORM, 1234));

    // Should not throw
    EXPECT_NO_THROW(srv.processInform(pkt));

    // Should return something
    EXPECT_TRUE(srv.processInform(pkt));

    // @todo Implement more reasonable tests before starting
    // work on processSomething() method.
}

TEST_F(Dhcpv4SrvTest, serverReceivedPacketName) {
    // Check all possible packet types
    for (int itype = 0; itype < 256; ++itype) {
        uint8_t type = itype;

        switch (type) {
        case DHCPDECLINE:
            EXPECT_STREQ("DECLINE", Dhcpv4Srv::serverReceivedPacketName(type));
            break;

        case DHCPDISCOVER:
            EXPECT_STREQ("DISCOVER", Dhcpv4Srv::serverReceivedPacketName(type));
            break;

        case DHCPINFORM:
            EXPECT_STREQ("INFORM", Dhcpv4Srv::serverReceivedPacketName(type));
            break;

        case DHCPRELEASE:
            EXPECT_STREQ("RELEASE", Dhcpv4Srv::serverReceivedPacketName(type));
            break;

        case DHCPREQUEST:
            EXPECT_STREQ("REQUEST", Dhcpv4Srv::serverReceivedPacketName(type));
            break;

        default:
            EXPECT_STREQ("UNKNOWN", Dhcpv4Srv::serverReceivedPacketName(type));
        }
    }
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
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

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
// - address set to specific value as hint
//
// expected returned OFFER message:
// - copy of client-id
// - server-id
// - offered address
TEST_F(Dhcpv4SrvTest, DiscoverHint) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_EQ(offer->getYiaddr().toText(), hint.toText());

    // Check identifiers
    checkServerId(offer, srv->getServerID());
    checkClientId(offer, clientid);
}


// This test verifies that incoming DISCOVER can be handled properly, that an
// OFFER is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed very simple DISCOVER message with:
// - address set to specific value as hint
//
// expected returned OFFER message:
// - copy of client-id
// - server-id
// - offered address
TEST_F(Dhcpv4SrvTest, DiscoverNoClientId) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setYiaddr(hint);
    dis->setHWAddr(generateHWAddr(6));

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_EQ(offer->getYiaddr().toText(), hint.toText());

    // Check identifiers
    checkServerId(offer, srv->getServerID());
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
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("10.1.2.3");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.107"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_NE(offer->getYiaddr().toText(), hint.toText());

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
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis1 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr dis2 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 2345));
    Pkt4Ptr dis3 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 3456));

    dis1->setRemoteAddr(IOAddress("192.0.2.1"));
    dis2->setRemoteAddr(IOAddress("192.0.2.2"));
    dis3->setRemoteAddr(IOAddress("192.0.2.3"));

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
    checkAddressParams(offer1, subnet_);
    checkAddressParams(offer2, subnet_);
    checkAddressParams(offer3, subnet_);

    // Check server-ids
    checkServerId(offer1, srv->getServerID());
    checkServerId(offer2, srv->getServerID());
    checkServerId(offer3, srv->getServerID());
    checkClientId(offer1, clientid1);
    checkClientId(offer2, clientid2);
    checkClientId(offer3, clientid3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1.toText(), addr2.toText());
    EXPECT_NE(addr2.toText(), addr3.toText());
    EXPECT_NE(addr3.toText(), addr1.toText());
    cout << "Offered address to client1=" << addr1.toText() << endl;
    cout << "Offered address to client2=" << addr2.toText() << endl;
    cout << "Offered address to client3=" << addr3.toText() << endl;
}

// This test verifies that incoming REQUEST can be handled properly, that an
// ACK is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed a single REQUEST message with:
// - client-id option
// - hwaddr information
// - requested address (that the client received in DISCOVER/OFFER exchange)
//
// expected returned ACK message:
// - copy of client-id
// - server-id
// - assigned address
//
// Test verifies that the lease is actually in the database.
TEST_F(Dhcpv4SrvTest, RequestBasic) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    IOAddress hint("192.0.2.107");
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setYiaddr(hint);

    // Pass it to the server and get an advertise
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(hint.toText(), ack->getYiaddr().toText());

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(ack, subnet_);

    // Check identifiers
    checkServerId(ack, srv->getServerID());
    checkClientId(ack, clientid);

    // Check that the lease is really in the database
    Lease4Ptr l = checkLease(ack, clientid, req->getHWAddr(), hint);

    ASSERT_TRUE(l);
    LeaseMgrFactory::instance().deleteLease(l->addr_);
}

// This test verifies that incoming REQUEST can be handled properly, that an
// ACK is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed 3 REQUEST messages with:
// - client-id option (differs between messages)
// - hwaddr information (differs between messages)
//
// expected returned ACK message:
// - copy of client-id
// - server-id
// - assigned address (different for each client)
TEST_F(Dhcpv4SrvTest, ManyRequests) {

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress req_addr1("192.0.2.105");
    const IOAddress req_addr2("192.0.2.101");
    const IOAddress req_addr3("192.0.2.109");
    const IOAddress relay("192.0.2.1");

    Pkt4Ptr req1 = Pkt4Ptr(new Pkt4(DHCPOFFER, 1234));
    Pkt4Ptr req2 = Pkt4Ptr(new Pkt4(DHCPOFFER, 2345));
    Pkt4Ptr req3 = Pkt4Ptr(new Pkt4(DHCPOFFER, 3456));

    req1->setRemoteAddr(relay);
    req2->setRemoteAddr(relay);
    req3->setRemoteAddr(relay);

    req1->setYiaddr(req_addr1);
    req2->setYiaddr(req_addr2);
    req3->setYiaddr(req_addr3);

    req1->setHWAddr(generateHWAddr(6));
    req2->setHWAddr(generateHWAddr(7));
    req3->setHWAddr(generateHWAddr(8));

    // Different client-id sizes
    OptionPtr clientid1 = generateClientId(4); // length 4
    OptionPtr clientid2 = generateClientId(5); // length 5
    OptionPtr clientid3 = generateClientId(6); // length 6

    req1->addOption(clientid1);
    req2->addOption(clientid2);
    req3->addOption(clientid3);

    // Pass it to the server and get an advertise
    Pkt4Ptr ack1 = srv->processRequest(req1);
    Pkt4Ptr ack2 = srv->processRequest(req2);
    Pkt4Ptr ack3 = srv->processRequest(req3);

    // Check if we get response at all
    checkResponse(ack1, DHCPACK, 1234);
    checkResponse(ack2, DHCPACK, 2345);
    checkResponse(ack3, DHCPACK, 3456);

    IOAddress addr1 = ack1->getYiaddr();
    IOAddress addr2 = ack2->getYiaddr();
    IOAddress addr3 = ack3->getYiaddr();

    // Check that every client received the address it requested
    EXPECT_EQ(req_addr1.toText(), addr1.toText());
    EXPECT_EQ(req_addr2.toText(), addr2.toText());
    EXPECT_EQ(req_addr3.toText(), addr3.toText());

    // Check that the assigned address is indeed from the configured pool
    checkAddressParams(ack1, subnet_);
    checkAddressParams(ack2, subnet_);
    checkAddressParams(ack3, subnet_);

    // Check DUIDs
    checkServerId(ack1, srv->getServerID());
    checkServerId(ack2, srv->getServerID());
    checkServerId(ack3, srv->getServerID());
    checkClientId(ack1, clientid1);
    checkClientId(ack2, clientid2);
    checkClientId(ack3, clientid3);

    // Check that leases are in the database
    Lease4Ptr l = checkLease(ack1, clientid1, req1->getHWAddr(), addr1);
    EXPECT_TRUE(l);
    l = checkLease(ack2, clientid2, req2->getHWAddr(), addr2);
    l = checkLease(ack3, clientid3, req3->getHWAddr(), addr3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1.toText(), addr2.toText());
    EXPECT_NE(addr2.toText(), addr3.toText());
    EXPECT_NE(addr3.toText(), addr1.toText());
    cout << "Offered address to client1=" << addr1.toText() << endl;
    cout << "Offered address to client2=" << addr2.toText() << endl;
    cout << "Offered address to client3=" << addr3.toText() << endl;
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
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2, sizeof(hwaddr2),
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

    req->addOption(clientid);
    req->addOption(srv->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(addr.toText(), ack->getYiaddr().toText());

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(ack, subnet_);

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

// @todo: Implement tests for rejecting renewals

// This test verifies if the sanityCheck() really checks options presence.
TEST_F(Dhcpv4SrvTest, sanityCheck) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    pkt->setHWAddr(generateHWAddr(6));

    // Server-id is optional for information-request, so
    EXPECT_NO_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::OPTIONAL));

    // Empty packet, no server-id
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY), RFCViolation);

    pkt->addOption(srv->getServerID());

    // Server-id is mandatory and present = no exception
    EXPECT_NO_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY));

    // Server-id is forbidden, but present => exception
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::FORBIDDEN),
                 RFCViolation);

    // There's no client-id and no HWADDR. Server needs something to
    // identify the client
    pkt->setHWAddr(generateHWAddr(0));
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY), RFCViolation);
}

// This test verifies that incoming (positive) RELEASE can be handled properly.
// As there is no REPLY in DHCPv4, the only thing to verify here is that
// the lease is indeed removed from the database.
TEST_F(Dhcpv4SrvTest, ReleaseBasic) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, mac_addr, sizeof(mac_addr),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              temp_valid, temp_t1, temp_t2, temp_timestamp,
                              subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv->getServerID());
    rel->setHWAddr(hw);

    // Pass it to the server and hope for a REPLY
    // Note: this is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv->processRelease(rel));

    // The lease should be gone from LeaseMgr
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);

    // Try to get the lease by hardware address
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(hw->hwaddr_);
    EXPECT_EQ(leases.size(), 0);

    // Try to get it by hw/subnet_id combination
    l = LeaseMgrFactory::instance().getLease4(hw->hwaddr_, subnet_->getID());
    EXPECT_FALSE(l);

    // Try by client-id
    leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    EXPECT_EQ(leases.size(), 0);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_FALSE(l);

    // Ok, the lease is *really* not there.
}

// This test verifies that incoming (invalid) RELEASE can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
TEST_F(Dhcpv4SrvTest, ReleaseReject) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress addr("192.0.2.106");
    const uint32_t t1 = 50;
    const uint32_t t2 = 75;
    const uint32_t valid = 100;
    const time_t timestamp = time(NULL) - 10;

    // Let's create a lease and put it in the LeaseMgr
    uint8_t bogus_mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr bogus_hw(new HWAddr(bogus_mac_addr, sizeof(bogus_mac_addr), HTYPE_ETHER));
    OptionPtr bogus_clientid = generateClientId(7); // different length

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv->getServerID());
    rel->setHWAddr(bogus_hw);

    // Case 1: No lease known to server
    SCOPED_TRACE("CASE 1: Lease is not known to the server");

    // There is nothing to check here. The lease is not there and server does
    // not send anything back. This case is enumerated here just for keeping
    // parity with similar test in DHCPv6.
    EXPECT_NO_THROW(srv->processRelease(rel));

    // CASE 2: Lease is known and belongs to this client, but to a different hardware
    SCOPED_TRACE("CASE 2: Lease is known and belongs to this client, but uses different HW addr");

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0x1, 0x2, 0x3, 0x4, 0x5};
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, mac_addr, sizeof(mac_addr),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              valid, t1, t2, timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));
    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    rel->setHWAddr(bogus_hw);

    EXPECT_NO_THROW(srv->processRelease(rel));

    // Check that the lease was not removed (due to hardware address mis-match)
    l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // CASE 3: Lease belongs to a client with different client-id
    SCOPED_TRACE("CASE 3: Lease belongs to a client with different client-id");

    rel->setHWAddr(hw); // proper HW address this time
    rel->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    rel->addOption(bogus_clientid); // but invalid client-id

    OptionPtr x = rel->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    EXPECT_NO_THROW(srv->processRelease(rel));

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Final sanity check. Verify that with valid hw and client-id release is successful
    rel->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    rel->addOption(clientid);

    // It should work this time
    EXPECT_NO_THROW(srv->processRelease(rel));

    // Check that the lease is not there
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);
}

// This test verifies if the server-id disk operations (read, write) are
// working properly.
TEST_F(Dhcpv4SrvTest, ServerID) {
    NakedDhcpv4Srv srv(0);

    string srvid_text = "192.0.2.100";
    IOAddress srvid(srvid_text);

    fstream file1(SRVID_FILE, ios::out | ios::trunc);
    file1 << srvid_text;
    file1.close();

    // Test reading from a file
    EXPECT_TRUE(srv.loadServerID(SRVID_FILE));
    ASSERT_TRUE(srv.getServerID());
    EXPECT_EQ(srvid_text, srv.srvidToString(srv.getServerID()));

    // Now test writing to a file
    EXPECT_EQ(0, unlink(SRVID_FILE));
    EXPECT_NO_THROW(srv.writeServerID(SRVID_FILE));

    fstream file2(SRVID_FILE, ios::in);
    ASSERT_TRUE(file2.good());
    string text;
    file2 >> text;
    file2.close();

    EXPECT_EQ(srvid_text, text);
}

// Checks if received relay agent info option is echoed back to the client
TEST_F(Dhcpv4SrvTest, relayAgentInfoEcho) {

    NakedDhcpv4Srv srv(0);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv.fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv.run();

    // Check that the server did send a reposonse
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

    EXPECT_TRUE(rai_response->equal(rai_query));
}

// Checks if vendor options are parsed correctly and requested vendor options
// are echoed back.
TEST_F(Dhcpv4SrvTest, vendorOptionsDocsis) {

    NakedDhcpv4Srv srv(0);

    string config = "{ \"interfaces\": [ \"*\" ],"
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
        "    \"pool\": [ \"10.254.226.0/25\" ],"
        "    \"subnet\": \"10.254.226.0/24\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pool\": [ \"192.0.3.0/25\" ],"
        "    \"subnet\": \"192.0.3.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Let's create a relayed DISCOVER. This particular relayed DISCOVER has
    // added option 82 (relay agent info) with 3 suboptions. The server
    // is supposed to echo it back in its response.
    Pkt4Ptr dis;
    ASSERT_NO_THROW(dis = captureRelayedDiscover());

    // Simulate that we have received that traffic
    srv.fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv.run();

    // Check that the server did send a reposonse
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

// Checks if hooks are registered properly.
TEST_F(Dhcpv4SrvTest, Hooks) {
    NakedDhcpv4Srv srv(0);

    // check if appropriate hooks are registered
    int hook_index_buffer4_receive = -1;
    int hook_index_pkt4_receive    = -1;
    int hook_index_select_subnet   = -1;
    int hook_index_lease4_release  = -1;
    int hook_index_pkt4_send       = -1;
    int hook_index_buffer4_send    = -1;

    // check if appropriate indexes are set
    EXPECT_NO_THROW(hook_index_buffer4_receive = ServerHooks::getServerHooks()
                    .getIndex("buffer4_receive"));
    EXPECT_NO_THROW(hook_index_pkt4_receive = ServerHooks::getServerHooks()
                    .getIndex("pkt4_receive"));
    EXPECT_NO_THROW(hook_index_select_subnet = ServerHooks::getServerHooks()
                    .getIndex("subnet4_select"));
    EXPECT_NO_THROW(hook_index_lease4_release = ServerHooks::getServerHooks()
                    .getIndex("lease4_release"));
    EXPECT_NO_THROW(hook_index_pkt4_send = ServerHooks::getServerHooks()
                    .getIndex("pkt4_send"));
    EXPECT_NO_THROW(hook_index_buffer4_send = ServerHooks::getServerHooks()
                    .getIndex("buffer4_send"));

    EXPECT_TRUE(hook_index_buffer4_receive > 0);
    EXPECT_TRUE(hook_index_pkt4_receive > 0);
    EXPECT_TRUE(hook_index_select_subnet > 0);
    EXPECT_TRUE(hook_index_lease4_release > 0);
    EXPECT_TRUE(hook_index_pkt4_send > 0);
    EXPECT_TRUE(hook_index_buffer4_send > 0);
}

// This test verifies that the following option structure can be parsed:
// - option (option space 'foobar')
//   - sub option (option space 'foo')
//      - sub option (option space 'bar')
// @todo Add more thorough unit tests for unpackOptions.
TEST_F(Dhcpv4SrvTest, unpackOptions) {
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
    CfgMgr& cfgmgr = CfgMgr::instance();
    ASSERT_NO_THROW(cfgmgr.addOptionDef(opt_def, "space-foobar"));
    ASSERT_NO_THROW(cfgmgr.addOptionDef(opt_def2, "space-foo"));
    ASSERT_NO_THROW(cfgmgr.addOptionDef(opt_def3, "space-bar"));

    // Create the buffer holding the structure of options.
    const char raw_data[] = {
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
    OptionBuffer buf(raw_data, raw_data + sizeof(raw_data));

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

// a dummy MAC address
const uint8_t dummyMacAddr[] = {0, 1, 2, 3, 4, 5};

// A dummy MAC address, padded with 0s
const uint8_t dummyChaddr[16] = {0, 1, 2, 3, 4, 5, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0 };

// Let's use some creative test content here (128 chars + \0)
const uint8_t dummyFile[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit. Proin mollis placerat metus, at "
    "lacinia orci ornare vitae. Mauris amet.";

// Yet another type of test content (64 chars + \0)
const uint8_t dummySname[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit posuere.";

/// @brief a class dedicated to Hooks testing in DHCPv4 server
///
/// This class has a number of static members, because each non-static
/// method has implicit 'this' parameter, so it does not match callout
/// signature and couldn't be registered. Furthermore, static methods
/// can't modify non-static members (for obvious reasons), so many
/// fields are declared static. It is still better to keep them as
/// one class rather than unrelated collection of global objects.
class HooksDhcpv4SrvTest : public Dhcpv4SrvTest {

public:

    /// @brief creates Dhcpv4Srv and prepares buffers for callouts
    HooksDhcpv4SrvTest() {

        // Allocate new DHCPv6 Server
        srv_ = new NakedDhcpv4Srv(0);

        // clear static buffers
        resetCalloutBuffers();
    }

    /// @brief destructor (deletes Dhcpv4Srv)
    virtual ~HooksDhcpv4SrvTest() {

        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer4_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer4_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("pkt4_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("pkt4_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("subnet4_select");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_renew");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_release");

        delete srv_;
    }

    /// @brief creates an option with specified option code
    ///
    /// This method is static, because it is used from callouts
    /// that do not have a pointer to HooksDhcpv4SSrvTest object
    ///
    /// @param option_code code of option to be created
    ///
    /// @return pointer to create option object
    static OptionPtr createOption(uint16_t option_code) {

        char payload[] = {
            0xa, 0xb, 0xc, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14
        };

        OptionBuffer tmp(payload, payload + sizeof(payload));
        return OptionPtr(new Option(Option::V4, option_code, tmp));
    }

    /// @brief Generates test packet.
    ///
    /// Allocates and generates on-wire buffer that represents test packet, with all
    /// fixed fields set to non-zero values.  Content is not always reasonable.
    ///
    /// See generateTestPacket1() function that returns exactly the same packet as
    /// Pkt4 object.
    ///
    /// @return pointer to allocated Pkt4 object
    // Returns a vector containing a DHCPv4 packet header.
    Pkt4Ptr
    generateSimpleDiscover() {

        // That is only part of the header. It contains all "short" fields,
        // larger fields are constructed separately.
        uint8_t hdr[] = {
            1, 6, 6, 13,            // op, htype, hlen, hops,
            0x12, 0x34, 0x56, 0x78, // transaction-id
            0, 42, 0x80, 0x00,      // 42 secs, BROADCAST flags
            192, 0, 2, 1,           // ciaddr
            1, 2, 3, 4,             // yiaddr
            192, 0, 2, 255,         // siaddr
            255, 255, 255, 255,     // giaddr
        };

        // Initialize the vector with the header fields defined above.
        vector<uint8_t> buf(hdr, hdr + sizeof(hdr));

        // Append the large header fields.
        copy(dummyChaddr, dummyChaddr + Pkt4::MAX_CHADDR_LEN, back_inserter(buf));
        copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN, back_inserter(buf));
        copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN, back_inserter(buf));

        // Should now have all the header, so check.  The "static_cast" is used
        // to get round an odd bug whereby the linker appears not to find the
        // definition of DHCPV4_PKT_HDR_LEN if it appears within an EXPECT_EQ().
        EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), buf.size());

        // Add magic cookie
        buf.push_back(0x63);
        buf.push_back(0x82);
        buf.push_back(0x53);
        buf.push_back(0x63);

        // Add message type DISCOVER
        buf.push_back(static_cast<uint8_t>(DHO_DHCP_MESSAGE_TYPE));
        buf.push_back(1); // length (just one byte)
        buf.push_back(static_cast<uint8_t>(DHCPDISCOVER));

        return (Pkt4Ptr(new Pkt4(&buf[0], buf.size())));
    }

    /// Test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer4_receive");

        callout_handle.getArgument("query4", callback_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that changes hwaddr value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_change_hwaddr(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // If there is at least one option with data
        if (pkt->data_.size() >= Pkt4::DHCPV4_PKT_HDR_LEN) {
            // Offset of the first byte of the CHWADDR field. Let's the first
            // byte to some new value that we could later check
            pkt->data_[28] = 0xff;
        }

        // Carry on as usual
        return buffer4_receive_callout(callout_handle);
    }

    /// Test callback that deletes MAC address
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_delete_hwaddr(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        pkt->data_[2] = 0; // offset 2 is hlen, let's set it to zero
        memset(&pkt->data_[28], 0, Pkt4::MAX_CHADDR_LEN); // Clear CHADDR content

        // carry on as usual
        return buffer4_receive_callout(callout_handle);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_skip(CalloutHandle& callout_handle) {

        callout_handle.setSkip(true);

        // Carry on as usual
        return buffer4_receive_callout(callout_handle);
    }

    /// test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt4_receive");

        callout_handle.getArgument("query4", callback_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// test callback that changes client-id value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_change_clientid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // get rid of the old client-id
        pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER);

        // add a new option
        pkt->addOption(createOption(DHO_DHCP_CLIENT_IDENTIFIER));

        // carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// test callback that deletes client-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_delete_clientid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // get rid of the old client-id (and no HWADDR)
        vector<uint8_t> mac;
        pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
        pkt->setHWAddr(1, 0, mac); // HWtype 1, hwardware len = 0

        // carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_skip(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        callout_handle.setSkip(true);

        // carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt4_send");

        callout_handle.getArgument("response4", callback_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    // Test callback that changes server-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_change_serverid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // get rid of the old server-id
        pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER);

        // add a new option
        pkt->addOption(createOption(DHO_DHCP_SERVER_IDENTIFIER));

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// test callback that deletes server-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_delete_serverid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // get rid of the old client-id
        pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER);

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_skip(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        callout_handle.setSkip(true);

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer4_send");

        callout_handle.getArgument("response4", callback_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback changes the output buffer to a hardcoded value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_send_change_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // modify buffer to set a diffferent payload
        pkt->getBuffer().clear();
        pkt->getBuffer().writeData(dummyFile, sizeof(dummyFile));

        return (0);
    }

    /// Test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    skip_callout(CalloutHandle& callout_handle) {

        callout_handle.setSkip(true);

        return (0);
    }

    /// Test callback that stores received callout name and subnet4 values
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("subnet4_select");

        callout_handle.getArgument("query4", callback_pkt4_);
        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("subnet4collection", callback_subnet4collection_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that picks the other subnet if possible.
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_different_subnet_callout(CalloutHandle& callout_handle) {

        // Call the basic calllout to record all passed values
        subnet4_select_callout(callout_handle);

        const Subnet4Collection* subnets;
        Subnet4Ptr subnet;
        callout_handle.getArgument("subnet4", subnet);
        callout_handle.getArgument("subnet4collection", subnets);

        // Let's change to a different subnet
        if (subnets->size() > 1) {
            subnet = (*subnets)[1]; // Let's pick the other subnet
            callout_handle.setArgument("subnet4", subnet);
        }

        return (0);
    }

    /// Test callback that stores received callout name passed parameters
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_release_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_release");

        callout_handle.getArgument("query4", callback_pkt4_);
        callout_handle.getArgument("lease4", callback_lease4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that stores received callout name and subnet4 values
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_renew_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_renew");

        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("lease4", callback_lease4_);
        callout_handle.getArgument("hwaddr", callback_hwaddr_);
        callout_handle.getArgument("clientid", callback_clientid_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }


    /// resets buffers used to store data received by callouts
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_pkt4_.reset();
        callback_lease4_.reset();
        callback_hwaddr_.reset();
        callback_clientid_.reset();
        callback_subnet4_.reset();
        callback_subnet4collection_ = NULL;
        callback_argument_names_.clear();
    }

    /// pointer to Dhcpv4Srv that is used in tests
    NakedDhcpv4Srv* srv_;

    // The following fields are used in testing pkt4_receive_callout

    /// String name of the received callout
    static string callback_name_;

    /// Pkt4 structure returned in the callout
    static Pkt4Ptr callback_pkt4_;

    /// Lease4 structure returned in the callout
    static Lease4Ptr callback_lease4_;

    /// Hardware address returned in the callout
    static HWAddrPtr callback_hwaddr_;

    /// Client-id returned in the callout
    static ClientIdPtr callback_clientid_;

    /// Pointer to a subnet received by callout
    static Subnet4Ptr callback_subnet4_;

    /// A list of all available subnets (received by callout)
    static const Subnet4Collection* callback_subnet4collection_;

    /// A list of all received arguments
    static vector<string> callback_argument_names_;
};

// The following fields are used in testing pkt4_receive_callout.
// See fields description in the class for details
string HooksDhcpv4SrvTest::callback_name_;
Pkt4Ptr HooksDhcpv4SrvTest::callback_pkt4_;
Subnet4Ptr HooksDhcpv4SrvTest::callback_subnet4_;
HWAddrPtr HooksDhcpv4SrvTest::callback_hwaddr_;
ClientIdPtr HooksDhcpv4SrvTest::callback_clientid_;
Lease4Ptr HooksDhcpv4SrvTest::callback_lease4_;
const Subnet4Collection* HooksDhcpv4SrvTest::callback_subnet4collection_;
vector<string> HooksDhcpv4SrvTest::callback_argument_names_;

// Checks if callouts installed on pkt4_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "buffer4_receive".
TEST_F(HooksDhcpv4SrvTest, Buffer4ReceiveSimple) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr dis = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(dis);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer4_receive", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == dis.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query4"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on buffer4_receive is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv4SrvTest, buffer4RreceiveValueChange) {

    // Install callback that modifies MAC addr of incoming packet
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_change_hwaddr));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server did send a reposonse
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv_->fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get client-id...
    HWAddrPtr hwaddr = offer->getHWAddr();

    ASSERT_TRUE(hwaddr); // basic sanity check. HWAddr is always present

    // ... and check if it is the modified value
    ASSERT_FALSE(hwaddr->hwaddr_.empty()); // there must be a MAC address
    EXPECT_EQ(0xff, hwaddr->hwaddr_[0]); // check that its first byte was modified
}

// Checks if callouts installed on buffer4_receive is able to set skip flag that
// will cause the server to not parse the packet. Even though the packet is valid,
// the server should eventually drop it, because there won't be mandatory options
// (or rather option objects) in it.
TEST_F(HooksDhcpv4SrvTest, buffer4ReceiveSkip) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_skip));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());
}

// Checks if callouts installed on pkt4_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "pkt4_receive".
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveSimple) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt4_receive", callback_name_);

    // check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == sol.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query4"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on pkt4_received is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv4SrvTest, valueChange_pkt4_receive) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_change_clientid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server did send a reposonce
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(DHO_DHCP_CLIENT_IDENTIFIER);
    EXPECT_TRUE(clientid->equal(expected));
}

// Checks if callouts installed on pkt4_received is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveDeleteClientId) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_delete_clientid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not send a response
    ASSERT_EQ(0, srv_->fake_sent_.size());
}

// Checks if callouts installed on pkt4_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveSkip) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_skip));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());
}


// Checks if callouts installed on pkt4_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv4SrvTest, pkt4SendSimple) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt4_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("response4"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on pkt4_send is able to change
// the values and the packet sent contains those changes
TEST_F(HooksDhcpv4SrvTest, pkt4SendValueChange) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_change_serverid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server did send a reposonce
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(DHO_DHCP_SERVER_IDENTIFIER);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(DHO_DHCP_SERVER_IDENTIFIER);
    EXPECT_TRUE(clientid->equal(expected));
}

// Checks if callouts installed on pkt4_send is able to delete
// existing options and that server applies those changes. In particular,
// we are trying to send a packet without server-id. The packet should
// be sent
TEST_F(HooksDhcpv4SrvTest, pkt4SendDeleteServerId) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_delete_serverid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server indeed sent a malformed ADVERTISE
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get that ADVERTISE
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure that it does not have server-id
    EXPECT_FALSE(adv->getOption(DHO_DHCP_SERVER_IDENTIFIER));
}

// Checks if callouts installed on pkt4_skip is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, skip_pkt4_send) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_skip));

    // Let's create a simple REQUEST
    Pkt4Ptr sol = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_send callback.
    srv_->run();

    // Check that the server sent the message
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get the first packet and check that it has zero length (i.e. the server
    // did not do packing on its own)
    Pkt4Ptr sent = srv_->fake_sent_.front();
    EXPECT_EQ(0, sent->getBuffer().getLength());
}

// Checks if callouts installed on buffer4_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv4SrvTest, buffer4SendSimple) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", buffer4_send_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer4_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("response4"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on buffer4_send are indeed called and that
// the output buffer can be changed.
TEST_F(HooksDhcpv4SrvTest, buffer4Send) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", buffer4_send_change_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // The callout is supposed to fill the output buffer with dummyFile content
    ASSERT_EQ(sizeof(dummyFile), adv->getBuffer().getLength());
    EXPECT_EQ(0, memcmp(adv->getBuffer().getData(), dummyFile, sizeof(dummyFile)));
}

// Checks if callouts installed on buffer4_send can set skip flag and that flag
// causes the packet to not be sent
TEST_F(HooksDhcpv4SrvTest, buffer4SendSkip) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", skip_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that there is no packet sent.
    ASSERT_EQ(0, srv_->fake_sent_.size());
}


// This test checks if subnet4_select callout is triggered and reports
// valid parameters
TEST_F(HooksDhcpv4SrvTest, subnet4SelectSimple) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_callout));

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces\": [ \"*\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.0/25\" ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pool\": [ \"192.0.3.0/25\" ],"
        "    \"subnet\": \"192.0.3.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Prepare discover packet. Server should select first subnet for it
    Pkt4Ptr sol = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    sol->setRemoteAddr(IOAddress("192.0.2.1"));
    sol->setIface(valid_iface_);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr adv = srv_->processDiscover(sol);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("subnet4_select", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == sol.get());

    const Subnet4Collection* exp_subnets = CfgMgr::instance().getSubnets4();

    // The server is supposed to pick the first subnet, because of matching
    // interface. Check that the value is reported properly.
    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(exp_subnets->front().get(), callback_subnet4_.get());

    // Server is supposed to report two subnets
    ASSERT_EQ(exp_subnets->size(), callback_subnet4collection_->size());

    // Compare that the available subnets are reported as expected
    EXPECT_TRUE((*exp_subnets)[0].get() == (*callback_subnet4collection_)[0].get());
    EXPECT_TRUE((*exp_subnets)[1].get() == (*callback_subnet4collection_)[1].get());
}

// This test checks if callout installed on subnet4_select hook point can pick
// a different subnet.
TEST_F(HooksDhcpv4SrvTest, subnet4SelectChange) {

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_different_subnet_callout));

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces\": [ \"*\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.0/25\" ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pool\": [ \"192.0.3.0/25\" ],"
        "    \"subnet\": \"192.0.3.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Prepare discover packet. Server should select first subnet for it
    Pkt4Ptr sol = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    sol->setRemoteAddr(IOAddress("192.0.2.1"));
    sol->setIface(valid_iface_);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr adv = srv_->processDiscover(sol);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // The response should have an address from second pool, so let's check it
    IOAddress addr = adv->getYiaddr();
    EXPECT_NE("0.0.0.0", addr.toText());

    // Get all subnets and use second subnet for verification
    const Subnet4Collection* subnets = CfgMgr::instance().getSubnets4();
    ASSERT_EQ(2, subnets->size());

    // Advertised address must belong to the second pool (in subnet's range,
    // in dynamic pool)
    EXPECT_TRUE((*subnets)[1]->inRange(addr));
    EXPECT_TRUE((*subnets)[1]->inPool(Lease::TYPE_V4, addr));
}

// This test verifies that incoming (positive) REQUEST/Renewing can be handled
// properly and that callout installed on lease4_renew is triggered with
// expected parameters.
TEST_F(HooksDhcpv4SrvTest, lease4RenewSimple) {

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_renew", lease4_renew_callout));

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2, sizeof(hwaddr2),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              temp_valid, temp_t1, temp_t2, temp_timestamp,
                              subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RENEW
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress(addr));
    req->setYiaddr(addr);
    req->setCiaddr(addr); // client's address

    req->addOption(clientid);
    req->addOption(srv_->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv_->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);

    // Check that the lease is really in the database
    l = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt were really updated
    EXPECT_EQ(l->t1_, subnet_->getT1());
    EXPECT_EQ(l->t2_, subnet_->getT2());
    EXPECT_EQ(l->valid_lft_, subnet_->getValid());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_renew", callback_name_);

    // Check that hwaddr parameter is passed properly
    ASSERT_TRUE(callback_hwaddr_);
    EXPECT_TRUE(*callback_hwaddr_ == *req->getHWAddr());

    // Check that the subnet is passed properly
    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(callback_subnet4_->toText(), subnet_->toText());

    ASSERT_TRUE(callback_clientid_);
    ASSERT_TRUE(client_id_);
    EXPECT_TRUE(*client_id_ == *callback_clientid_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("subnet4");
    expected_argument_names.push_back("clientid");
    expected_argument_names.push_back("hwaddr");
    expected_argument_names.push_back("lease4");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

// This test verifies that a callout installed on lease4_renew can trigger
// the server to not renew a lease.
TEST_F(HooksDhcpv4SrvTest, lease4RenewSkip) {

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_renew", skip_callout));

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2, sizeof(hwaddr2),
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

    req->addOption(clientid);
    req->addOption(srv_->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);

    // Check that the lease is really in the database
    l = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, valid and cltt were NOT updated
    EXPECT_EQ(temp_t1, l->t1_);
    EXPECT_EQ(temp_t2, l->t2_);
    EXPECT_EQ(temp_valid, l->valid_lft_);
    EXPECT_EQ(temp_timestamp, l->cltt_);

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

// This test verifies that valid RELEASE triggers lease4_release callouts
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseSimple) {

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", lease4_release_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, mac_addr, sizeof(mac_addr),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              temp_valid, temp_t1, temp_t2, temp_timestamp,
                              subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Pass it to the server and hope for a REPLY
    // Note: this is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should be gone from LeaseMgr
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);

    // Try to get the lease by hardware address
    // @todo: Uncomment this once trac2592 is implemented
    // Lease4Collection leases = LeaseMgrFactory::instance().getLease4(hw->hwaddr_);
    // EXPECT_EQ(leases.size(), 0);

    // Try to get it by hw/subnet_id combination
    l = LeaseMgrFactory::instance().getLease4(hw->hwaddr_, subnet_->getID());
    EXPECT_FALSE(l);

    // Try by client-id
    // @todo: Uncomment this once trac2592 is implemented
    //Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    //EXPECT_EQ(leases.size(), 0);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_FALSE(l);

    // Ok, the lease is *really* not there.

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_release", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == rel.get());

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("lease4");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);
}

// This test verifies that skip flag returned by a callout installed on the
// lease4_release hook point will keep the lease
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseSkip) {

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", skip_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, mac_addr, sizeof(mac_addr),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              temp_valid, temp_t1, temp_t2, temp_timestamp,
                              subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Pass it to the server and hope for a REPLY
    // Note: this is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should be still there
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(l);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_TRUE(l);

    // Try to get the lease by hardware address
    // @todo: Uncomment this once trac2592 is implemented
    // Lease4Collection leases = LeaseMgrFactory::instance().getLease4(hw->hwaddr_);
    // EXPECT_EQ(leases.size(), 1);

    // Try by client-id
    // @todo: Uncomment this once trac2592 is implemented
    //Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    //EXPECT_EQ(leases.size(), 1);
}

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace
