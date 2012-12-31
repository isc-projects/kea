// Copyright (C) 2011-2012  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp/option.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {
const char* const INTERFACE_FILE = "interfaces.txt";

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "naked" DHCPv4 server, exposes internal fields
public:
    NakedDhcpv4Srv(uint16_t port = 0):Dhcpv4Srv(port) { }

    using Dhcpv4Srv::processDiscover;
    using Dhcpv4Srv::processRequest;
    using Dhcpv4Srv::processRelease;
    using Dhcpv4Srv::processDecline;
    using Dhcpv4Srv::processInform;
    using Dhcpv4Srv::getServerID;
    using Dhcpv4Srv::sanityCheck;
};

class Dhcpv4SrvTest : public ::testing::Test {
public:
    Dhcpv4SrvTest() {
        subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1000,
                                         2000, 3000));
        pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"), IOAddress("192.0.2.110")));
        subnet_->addPool(pool_);

        CfgMgr::instance().deleteSubnets4();
        CfgMgr::instance().addSubnet4(subnet_);
    }

    void MessageCheck(const boost::shared_ptr<Pkt4>& q,
                      const boost::shared_ptr<Pkt4>& a) {
        ASSERT_TRUE(q);
        ASSERT_TRUE(a);

        EXPECT_EQ(q->getHops(),   a->getHops());
        EXPECT_EQ(q->getIface(),  a->getIface());
        EXPECT_EQ(q->getIndex(),  a->getIndex());
        EXPECT_EQ(q->getGiaddr(), a->getGiaddr());

        // check that bare minimum of required options are there
        EXPECT_TRUE(a->getOption(DHO_SUBNET_MASK));
        EXPECT_TRUE(a->getOption(DHO_ROUTERS));
        EXPECT_TRUE(a->getOption(DHO_DHCP_SERVER_IDENTIFIER));
        EXPECT_TRUE(a->getOption(DHO_DHCP_LEASE_TIME));
        EXPECT_TRUE(a->getOption(DHO_SUBNET_MASK));
        EXPECT_TRUE(a->getOption(DHO_ROUTERS));
        EXPECT_TRUE(a->getOption(DHO_DOMAIN_NAME));
        EXPECT_TRUE(a->getOption(DHO_DOMAIN_NAME_SERVERS));

        // check that something is offered
        EXPECT_TRUE(a->getYiaddr().toText() != "0.0.0.0");
    }

    // Generate client-id option
    OptionPtr generateClientId(size_t size = 4) {

        OptionBuffer clnt_id(size);
        for (int i = 0; i < size; i++) {
            clnt_id[i] = 100 + i;
        }

        client_id_ = ClientIdPtr(new ClientId(clnt_id));

        return (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                     clnt_id.begin(),
                                     clnt_id.begin() + size)));
    }

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    void checkAddressParams(const Pkt4Ptr& rsp, const SubnetPtr subnet,
                            bool t1_mandatory = false, bool t2_mandatory = false) {

        // Technically inPool implies inRange, but let's be on the safe
        // side and check both.
        EXPECT_TRUE(subnet->inRange(rsp->getYiaddr()));
        EXPECT_TRUE(subnet->inPool(rsp->getYiaddr()));

        // Check lease time
        OptionPtr tmp = rsp->getOption(DHO_DHCP_LEASE_TIME);
        if (!tmp) {
            ADD_FAILURE() << "Lease time option missing in response";
        } else {
            EXPECT_EQ(tmp->getUint32(), subnet->getValid());
        }

        // Check T1 timer
        tmp = rsp->getOption(DHO_DHCP_RENEWAL_TIME);
        if (tmp) {
            EXPECT_EQ(tmp->getUint32(), subnet->getT1());
        } else {
            if (t1_mandatory) {
                ADD_FAILURE() << "Required T1 option missing";
            }
        }

        // Check T2 timer
        tmp = rsp->getOption(DHO_DHCP_REBINDING_TIME);
        if (tmp) {
            EXPECT_EQ(tmp->getUint32(), subnet->getT2());
        } else {
            if (t1_mandatory) {
                ADD_FAILURE() << "Required T2 option missing";
            }
        }
    }

    // Basic checks for generated response (message type and transaction-id).
    void checkResponse(const Pkt4Ptr& rsp, uint8_t expected_message_type,
                       uint32_t expected_transid) {
        ASSERT_TRUE(rsp);
        EXPECT_EQ(expected_message_type, rsp->getType());
        EXPECT_EQ(expected_transid, rsp->getTransid());
    }

    // Checks if the lease sent to client is present in the database
    Lease4Ptr checkLease(const Pkt4Ptr& rsp, const OptionPtr& client_id,
                         const HWAddrPtr& hwaddr, const IOAddress& expected_addr) {

        ClientIdPtr id;
        if (client_id) {
            OptionBuffer data = client_id->getData();
            id.reset(new ClientId(data));
        }

        Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(expected_addr);
        if (!lease) {
            cout << "Lease for " << expected_addr.toText()
                 << " not found in the database backend.";
            return (Lease4Ptr());
        }

        EXPECT_EQ(expected_addr.toText(), lease->addr_.toText());
        if (client_id) {
            EXPECT_TRUE(*lease->client_id_ == *id);
        }
        EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

        return (lease);
    }

    // Checks if server response (OFFER, ACK, NAK) includes proper server-id.
    void checkServerId(const Pkt4Ptr& rsp, const OptionPtr& expected_srvid) {
        // check that server included its server-id
        OptionPtr tmp = rsp->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        ASSERT_TRUE(tmp);
        EXPECT_EQ(tmp->getType(), expected_srvid->getType() );
        EXPECT_EQ(tmp->len(), expected_srvid->len() );
        EXPECT_TRUE(tmp->getData() == expected_srvid->getData());
    }

    // Checks if server response (OFFER, ACK, NAK) includes proper client-id.
    void checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid) {
        // check that server included our own client-id
        OptionPtr tmp = rsp->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        ASSERT_TRUE(tmp);
        EXPECT_EQ(expected_clientid->getType(), tmp->getType());
        EXPECT_EQ(expected_clientid->len(), tmp->len());
        EXPECT_TRUE(expected_clientid->getData() == tmp->getData());
    }

    ~Dhcpv4SrvTest() {
        CfgMgr::instance().deleteSubnets4();
    };

    // A subnet used in most tests
    Subnet4Ptr subnet_;

    // A pool used in most tests
    Pool4Ptr pool_;

    // A client-id used in most tests
    ClientIdPtr client_id_;
};

TEST_F(Dhcpv4SrvTest, basic) {
    // nothing to test. DHCPv4_srv instance is created
    // in test fixture. It is destroyed in destructor

    Dhcpv4Srv* srv = NULL;
    ASSERT_NO_THROW({
        srv = new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000);
    });
    delete srv;

    NakedDhcpv4Srv* naked_srv = NULL;
    ASSERT_NO_THROW({
        naked_srv = new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000);
    });
    EXPECT_TRUE(naked_srv->getServerID());

    ASSERT_NO_THROW({
        naked_srv = new NakedDhcpv4Srv(0);
    });
    EXPECT_TRUE(naked_srv->getServerID());

    delete srv;



}

TEST_F(Dhcpv4SrvTest, processDiscover) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv(0);
    vector<uint8_t> mac(6);
    for (int i = 0; i < 6; i++) {
        mac[i] = 255 - i;
    }

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPDISCOVER, 1234));
    boost::shared_ptr<Pkt4> offer;

    pkt->setIface("eth0");
    pkt->setIndex(17);
    pkt->setHWAddr(1, 6, mac);
    pkt->setRemoteAddr(IOAddress("192.0.2.56"));
    pkt->setGiaddr(IOAddress("192.0.2.67"));

    // let's make it a relayed message
    pkt->setHops(3);
    pkt->setRemotePort(DHCP4_SERVER_PORT);

    // should not throw
    EXPECT_NO_THROW(
        offer = srv->processDiscover(pkt);
    );

    // should return something
    ASSERT_TRUE(offer);

    EXPECT_EQ(DHCPOFFER, offer->getType());

    // this is relayed message. It should be sent back to relay address.
    EXPECT_EQ(pkt->getGiaddr(), offer->getRemoteAddr());

    MessageCheck(pkt, offer);

    // now repeat the test for directly sent message
    pkt->setHops(0);
    pkt->setGiaddr(IOAddress("0.0.0.0"));
    pkt->setRemotePort(DHCP4_CLIENT_PORT);

    EXPECT_NO_THROW(
        offer = srv->processDiscover(pkt);
    );

    // should return something
    ASSERT_TRUE(offer);

    EXPECT_EQ(DHCPOFFER, offer->getType());

    // this is direct message. It should be sent back to origin, not
    // to relay.
    EXPECT_EQ(pkt->getRemoteAddr(), offer->getRemoteAddr());

    MessageCheck(pkt, offer);

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processRequest) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv(0);
    vector<uint8_t> mac(6);
    for (int i = 0; i < 6; i++) {
        mac[i] = i*10;
    }

    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPREQUEST, 1234));
    boost::shared_ptr<Pkt4> ack;

    req->setIface("eth0");
    req->setIndex(17);
    req->setHWAddr(1, 6, mac);
    req->setRemoteAddr(IOAddress("192.0.2.56"));
    req->setGiaddr(IOAddress("192.0.2.67"));

    // should not throw
    ASSERT_NO_THROW(
        ack = srv->processRequest(req);
    );

    // should return something
    ASSERT_TRUE(ack);

    EXPECT_EQ(DHCPACK, ack->getType());

    // this is relayed message. It should be sent back to relay address.
    EXPECT_EQ(req->getGiaddr(), ack->getRemoteAddr());

    MessageCheck(req, ack);

    // now repeat the test for directly sent message
    req->setHops(0);
    req->setGiaddr(IOAddress("0.0.0.0"));
    req->setRemotePort(DHCP4_CLIENT_PORT);

    EXPECT_NO_THROW(
        ack = srv->processDiscover(req);
    );

    // should return something
    ASSERT_TRUE(ack);

    EXPECT_EQ(DHCPOFFER, ack->getType());

    // this is direct message. It should be sent back to origin, not
    // to relay.
    EXPECT_EQ(ack->getRemoteAddr(), req->getRemoteAddr());

    MessageCheck(req, ack);

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processRelease) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPRELEASE, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processRelease(pkt);
    );

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processDecline) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPDECLINE, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processDecline(pkt);
    );

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.
    delete srv;
}

TEST_F(Dhcpv4SrvTest, processInform) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPINFORM, 1234));

    // should not throw
    EXPECT_NO_THROW(
        srv->processInform(pkt);
    );

    // should return something
    EXPECT_TRUE(srv->processInform(pkt));

    // TODO: Implement more reasonable tests before starting
    // work on processSomething() method.

    delete srv;
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
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv->processDiscover(dis);

    // check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    // check identifiers
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
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv->processDiscover(dis);

    // check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_EQ(offer->getYiaddr().toText(), hint.toText());

    // check identifiers
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
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setYiaddr(hint);

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv->processDiscover(dis);

    // check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_EQ(offer->getYiaddr().toText(), hint.toText());

    // check identifiers
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
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );
    IOAddress hint("10.1.2.3");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.107"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);

    // Pass it to the server and get an advertise
    Pkt4Ptr offer = srv->processDiscover(dis);

    // check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_NE(offer->getYiaddr().toText(), hint.toText());

    // check identifiers
    checkServerId(offer, srv->getServerID());
    checkClientId(offer, clientid);
}

/// @todo: Add a test that client sends hint that is in pool, but currently
/// being used by a different client.

// This test checks that the server is offering different addresses to different
// clients in ADVERTISEs. Please note that ADVERTISE is not a guarantee that such
// and address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same advertise as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. ADVERTISE is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv4SrvTest, ManyDiscovers) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );

    Pkt4Ptr dis1 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr dis2 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 2345));
    Pkt4Ptr dis3 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 3456));

    dis1->setRemoteAddr(IOAddress("192.0.2.1"));
    dis2->setRemoteAddr(IOAddress("192.0.2.2"));
    dis3->setRemoteAddr(IOAddress("192.0.2.3"));

    // different client-id sizes
    OptionPtr clientid1 = generateClientId(4); // length 4
    OptionPtr clientid2 = generateClientId(5); // length 5
    OptionPtr clientid3 = generateClientId(6); // length 6

    dis1->addOption(clientid1);
    dis2->addOption(clientid2);
    dis3->addOption(clientid3);

    // Pass it to the server and get an advertise
    Pkt4Ptr reply1 = srv->processDiscover(dis1);
    Pkt4Ptr reply2 = srv->processDiscover(dis2);
    Pkt4Ptr reply3 = srv->processDiscover(dis3);

    // check if we get response at all
    checkResponse(reply1, DHCPOFFER, 1234);
    checkResponse(reply2, DHCPOFFER, 2345);
    checkResponse(reply3, DHCPOFFER, 3456);

    IOAddress addr1 = reply1->getYiaddr();
    IOAddress addr2 = reply2->getYiaddr();
    IOAddress addr3 = reply3->getYiaddr();

    // Check that the assigned address is indeed from the configured pool
    checkAddressParams(reply1, subnet_);
    checkAddressParams(reply2, subnet_);
    checkAddressParams(reply3, subnet_);

    // check DUIDs
    checkServerId(reply1, srv->getServerID());
    checkServerId(reply2, srv->getServerID());
    checkServerId(reply3, srv->getServerID());
    checkClientId(reply1, clientid1);
    checkClientId(reply2, clientid2);
    checkClientId(reply3, clientid3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1.toText(), addr2.toText());
    EXPECT_NE(addr2.toText(), addr3.toText());
    EXPECT_NE(addr3.toText(), addr1.toText());
    cout << "Offered address to client1=" << addr1.toText() << endl;
    cout << "Offered address to client2=" << addr2.toText() << endl;
    cout << "Offered address to client3=" << addr3.toText() << endl;
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
TEST_F(Dhcpv4SrvTest, RequestBasic) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );

    IOAddress hint("192.0.2.107");
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setYiaddr(hint);

    // Pass it to the server and get an advertise
    Pkt4Ptr ack = srv->processRequest(req);

    // check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(hint.toText(), ack->getYiaddr().toText());

    // check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(ack, subnet_);

    // check identifiers
    checkServerId(ack, srv->getServerID());
    checkClientId(ack, clientid);

    // check that the lease is really in the database
    Lease4Ptr l = checkLease(ack, clientid, req->getHWAddr(), hint);

    ASSERT_TRUE(l);
    LeaseMgrFactory::instance().deleteLease(l->addr_);
}

// This test verifies that incoming (positive) RENEW can be handled properly, that a
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
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );

    const IOAddress addr("192.0.2.106");
    uint32_t temp_t1 = 50;
    uint32_t temp_t2 = 75;
    uint32_t temp_valid = 100;
    time_t temp_timestamp = time(NULL) - 10;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    uint8_t clientid2[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
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

    req->addOption(clientid);
    req->addOption(srv->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(addr.toText(), ack->getYiaddr().toText());

    // check that address was returned from proper range, that its lease
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
    // equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

// @todo: Implement tests for rejecting renewals

// This test verifies if the sanityCheck() really checks options presence.
TEST_F(Dhcpv4SrvTest, sanityCheck) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv4Srv(0)) );

    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));

    // check that the packets originating from local addresses can be
    pkt->setRemoteAddr(IOAddress("192.0.2.1"));

    // client-id is optional for information-request, so
    EXPECT_NO_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::OPTIONAL));

    // empty packet, no server-id
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY), RFCViolation);

    pkt->addOption(srv->getServerID());

    // server-id is mandatory and present = no exception
    EXPECT_NO_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY));

    // server-id is forbidden, but present => exception
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::FORBIDDEN),
                 RFCViolation);
}

// @todo: write tests for RELEASE

} // end of anonymous namespace
