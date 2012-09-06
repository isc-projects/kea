// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp/dhcp4.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp/option.h>
#include <asiolink/io_address.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {
const char* const INTERFACE_FILE = "interfaces.txt";

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "naked" DHCPv4 server, exposes internal fields
public:
    NakedDhcpv4Srv():Dhcpv4Srv(DHCP4_SERVER_PORT + 10000) { }

    boost::shared_ptr<Pkt4> processDiscover(boost::shared_ptr<Pkt4>& discover) {
        return Dhcpv4Srv::processDiscover(discover);
    }
    boost::shared_ptr<Pkt4> processRequest(boost::shared_ptr<Pkt4>& request) {
        return Dhcpv4Srv::processRequest(request);
    }
    void processRelease(boost::shared_ptr<Pkt4>& release) {
        return Dhcpv4Srv::processRelease(release);
    }
    void processDecline(boost::shared_ptr<Pkt4>& decline) {
        Dhcpv4Srv::processDecline(decline);
    }
    boost::shared_ptr<Pkt4> processInform(boost::shared_ptr<Pkt4>& inform) {
        return Dhcpv4Srv::processInform(inform);
    }
};

class Dhcpv4SrvTest : public ::testing::Test {
public:
    Dhcpv4SrvTest() {
        unlink(INTERFACE_FILE);
        fstream fakeifaces(INTERFACE_FILE, ios::out | ios::trunc);
        if (if_nametoindex("lo") > 0) {
            fakeifaces << "lo 127.0.0.1";
        } else if (if_nametoindex("lo0") > 0) {
            fakeifaces << "lo0 127.0.0.1";
        }
        fakeifaces.close();
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

    ~Dhcpv4SrvTest() {
        unlink(INTERFACE_FILE);
    };
};

TEST_F(Dhcpv4SrvTest, basic) {
    // nothing to test. DHCPv4_srv instance is created
    // in test fixture. It is destroyed in destructor

    Dhcpv4Srv* srv = NULL;
    ASSERT_NO_THROW({
        srv = new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000);
    });

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processDiscover) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();
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
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();
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

} // end of anonymous namespace
