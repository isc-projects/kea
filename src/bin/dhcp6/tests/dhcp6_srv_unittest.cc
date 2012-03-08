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

#include <dhcp/dhcp6.h>
#include <dhcp/option6_ia.h>
#include <dhcp6/dhcp6_srv.h>
#include <util/buffer.h>
#include <util/range_utilities.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {
const char* const INTERFACE_FILE = "interfaces.txt";

class NakedDhcpv6Srv: public Dhcpv6Srv {
    // "naked" Interface Manager, exposes internal fields
public:
    NakedDhcpv6Srv():Dhcpv6Srv(DHCP6_SERVER_PORT + 10000) { }

    boost::shared_ptr<Pkt6>
    processSolicit(boost::shared_ptr<Pkt6>& request) {
        return Dhcpv6Srv::processSolicit(request);
    }
    boost::shared_ptr<Pkt6>
    processRequest(boost::shared_ptr<Pkt6>& request) {
        return Dhcpv6Srv::processRequest(request);
    }
};

class Dhcpv6SrvTest : public ::testing::Test {
public:
    Dhcpv6SrvTest() {
        unlink(INTERFACE_FILE);
        fstream fakeifaces(INTERFACE_FILE, ios::out | ios::trunc);
        if (if_nametoindex("lo") > 0) {
            fakeifaces << "lo ::1";
        } else if (if_nametoindex("lo0") > 0) {
            fakeifaces << "lo0 ::1";
        }
        fakeifaces.close();
    }
    ~Dhcpv6SrvTest() {
        unlink(INTERFACE_FILE);
    };
};

TEST_F(Dhcpv6SrvTest, basic) {
    // srv has stubbed interface detection. It will read
    // interfaces.txt instead. It will pretend to have detected
    // fe80::1234 link-local address on eth0 interface. Obviously
    // an attempt to bind this socket will fail.
    Dhcpv6Srv* srv = NULL;
    ASSERT_NO_THROW( {
        // open an unpriviledged port
        srv = new Dhcpv6Srv(DHCP6_SERVER_PORT + 10000);
    });

    delete srv;
}

TEST_F(Dhcpv6SrvTest, DUID) {
    // tests that DUID is generated properly

    Dhcpv6Srv* srv = NULL;
    ASSERT_NO_THROW( {
        srv = new Dhcpv6Srv(DHCP6_SERVER_PORT + 10000);
    });

    OptionPtr srvid = srv->getServerID();
    ASSERT_TRUE(srvid);

    EXPECT_EQ(D6O_SERVERID, srvid->getType());

    OutputBuffer buf(32);
    srvid->pack(buf);

    // length of the actual DUID
    size_t len = buf.getLength() - srvid->getHeaderLen();

    InputBuffer data(buf.getData(), buf.getLength());

    // ignore first four bytes (standard DHCPv6 header)
    data.readUint32();

    uint16_t duid_type = data.readUint16();
    cout << "Duid-type=" << duid_type << endl;
    switch(duid_type) {
    case DUID_LLT: {
        // DUID must contain at least 6 bytes long MAC
        // + 8 bytes of fixed header
        EXPECT_GE(14, len);

        uint16_t hw_type = data.readUint16();
        // there's no real way to find out "correct"
        // hardware type
        EXPECT_GT(hw_type, 0);

        // check that timer is counted since 1.1.2000,
        // not from 1.1.1970.
        uint32_t seconds = data.readUint32();
        EXPECT_LE(seconds, DUID_TIME_EPOCH);
        // this test will start failing after 2030.
        // Hopefully we will be at BIND12 by then.

        // MAC must not be zeros
        vector<uint8_t> mac(len-8);
        vector<uint8_t> zeros(len-8, 0);
        data.readVector(mac, len-8);
        EXPECT_NE(mac, zeros);
        break;
    }
    case DUID_EN: {
        // there's not much we can check. Just simple
        // check if it is not all zeros
        vector<uint8_t> content(len-2);
        data.readVector(content, len-2);
        EXPECT_FALSE(isRangeZero(content.begin(), content.end()));
    }
    case DUID_LL: // not supported yet
    case DUID_UUID: // not supported yet
    default:
        cout << "Not supported duid type=" << duid_type << endl;
        FAIL();
    }
}

TEST_F(Dhcpv6SrvTest, Solicit_basic) {
    NakedDhcpv6Srv* srv = NULL;
    ASSERT_NO_THROW( srv = new NakedDhcpv6Srv(); );

    // a dummy content for client-id
    OptionBuffer clntDuid(32);
    for (int i = 0; i < 32; i++) {
        clntDuid[i] = 100 + i;
    }

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));

    boost::shared_ptr<Option6IA> ia =
        boost::shared_ptr<Option6IA>(new Option6IA(D6O_IA_NA, 234));
    ia->setT1(1501);
    ia->setT2(2601);
    sol->addOption(ia);

    // Let's not send address in solicit yet
    // boost::shared_ptr<Option6IAAddr> addr(new Option6IAAddr(D6O_IAADDR,
    //    IOAddress("2001:db8:1234:ffff::ffff"), 5001, 7001));
    // ia->addOption(addr);
    // sol->addOption(ia);

    // constructed very simple SOLICIT message with:
    // - client-id option (mandatory)
    // - IA option (a request for address, without any addresses)

    // expected returned ADVERTISE message:
    // - copy of client-id
    // - server-id
    // - IA that includes IAADDR

    OptionPtr clientid = OptionPtr(new Option(Option::V6, D6O_CLIENTID,
                                              clntDuid.begin(),
                                              clntDuid.begin() + 16));
    sol->addOption(clientid);

    boost::shared_ptr<Pkt6> reply = srv->processSolicit(sol);

    // check if we get response at all
    ASSERT_TRUE( reply != boost::shared_ptr<Pkt6>() );

    EXPECT_EQ( DHCPV6_ADVERTISE, reply->getType() );
    EXPECT_EQ( 1234, reply->getTransid() );

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE( tmp );

    Option6IA* reply_ia = dynamic_cast<Option6IA*>(tmp.get());
    EXPECT_EQ( 234, reply_ia->getIAID() );

    // check that there's an address included
    EXPECT_TRUE( reply_ia->getOption(D6O_IAADDR));

    // check that server included our own client-id
    tmp = reply->getOption(D6O_CLIENTID);
    ASSERT_TRUE( tmp );
    EXPECT_EQ(clientid->getType(), tmp->getType() );
    ASSERT_EQ(clientid->len(), tmp->len() );

    EXPECT_TRUE( clientid->getData() == tmp->getData() );

    // check that server included its server-id
    tmp = reply->getOption(D6O_SERVERID);
    EXPECT_EQ(tmp->getType(), srv->getServerID()->getType() );
    ASSERT_EQ(tmp->len(),  srv->getServerID()->len() );

    EXPECT_TRUE(tmp->getData() == srv->getServerID()->getData());

    // more checks to be implemented
    delete srv;

}

}
