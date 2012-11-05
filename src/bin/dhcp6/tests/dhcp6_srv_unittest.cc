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
#include <iostream>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp6/config_parser.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_int_array.h>
#include <config/ccsession.h>
#include <util/buffer.h>
#include <util/range_utilities.h>
#include <boost/scoped_ptr.hpp>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiolink;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {

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
    Dhcpv6SrvTest()
        : rcode_(-1) {
    }
    ~Dhcpv6SrvTest() {
    };

    int rcode_;
    ConstElementPtr comment_;
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

    boost::scoped_ptr<Dhcpv6Srv> srv;
    ASSERT_NO_THROW( {
        srv.reset(new Dhcpv6Srv(DHCP6_SERVER_PORT + 10000));
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
        EXPECT_TRUE(mac != zeros);
        break;
    }
    case DUID_EN: {
        // there's not much we can check. Just simple
        // check if it is not all zeros
        vector<uint8_t> content(len-2);
        data.readVector(content, len-2);
        EXPECT_FALSE(isRangeZero(content.begin(), content.end()));
        break;
    }
    case DUID_LL: {
        // not supported yet
        cout << "Test not implemented for DUID-LL." << endl;

        // No failure here. There's really no way for test LL DUID. It doesn't
        // even make sense to check if that Link Layer is actually present on
        // a physical interface. RFC3315 says a server should write its DUID
        // and keep it despite hardware changes.
        break;
    }
    case DUID_UUID: // not supported yet
    default:
        ADD_FAILURE() << "Not supported duid type=" << duid_type << endl;
        break;
    }
}

TEST_F(Dhcpv6SrvTest, solicitBasic) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1234::/80\" ],"
        "    \"subnet\": \"2001:db8:1234::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"OPTION_DNS_SERVERS\","
        "          \"code\": 23,"
        "          \"data\": \"2001 0DB8 1234 FFFF 0000 0000 0000 0001"
        "2001 0DB8 1234 FFFF 0000 0000 0000 0002\""
        "        },"
        "        {"
        "          \"name\": \"OPTION_FOO\","
        "          \"code\": 1000,"
        "          \"data\": \"1234\""
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv()) );

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);

    ASSERT_EQ(0, rcode_);

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
    /*    boost::shared_ptr<Option6IAAddr>
        addr(new Option6IAAddr(D6O_IAADDR, IOAddress("2001:db8:1234:ffff::ffff"), 5001, 7001));
    ia->addOption(addr);
    sol->addOption(ia); */

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
    ASSERT_TRUE(reply);

    EXPECT_EQ( DHCPV6_ADVERTISE, reply->getType() );
    EXPECT_EQ( 1234, reply->getTransid() );

    // We have not requested option with code 1000 so it should not
    // be included in the response.
    ASSERT_FALSE(reply->getOption(1000));

    // Let's now request option with code 1000.
    // We expect that server will include this option in its reply.
    boost::shared_ptr<Option6IntArray<uint16_t> >
        option_oro(new Option6IntArray<uint16_t>(D6O_ORO));
    // Create vector with one code equal to 1000.
    std::vector<uint16_t> codes(1, 1000);
    // Pass this code to option.
    option_oro->setValues(codes);
    // Append ORO to SOLICIT message.
    sol->addOption(option_oro);
    
    // Need to process SOLICIT again after requesting new option.
    reply = srv->processSolicit(sol);
    ASSERT_TRUE(reply);

    EXPECT_EQ(DHCPV6_ADVERTISE, reply->getType());

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE( tmp );

    boost::shared_ptr<Option6IA> reply_ia =
        boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(reply_ia);
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
 
    tmp = reply->getOption(D6O_NAME_SERVERS);
    ASSERT_TRUE(tmp);
    
    boost::shared_ptr<Option6AddrLst> reply_nameservers =
        boost::dynamic_pointer_cast<Option6AddrLst>(tmp);
    ASSERT_TRUE(reply_nameservers);

    Option6AddrLst::AddressContainer addrs = reply_nameservers->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_TRUE(addrs[0] == IOAddress("2001:db8:1234:FFFF::1"));
    EXPECT_TRUE(addrs[1] == IOAddress("2001:db8:1234:FFFF::2"));

    // There is a dummy option with code 1000 we requested from a server.
    // Expect that this option is in server's response.
    tmp = reply->getOption(1000);
    ASSERT_TRUE(tmp);

    // Check that the option contains valid data (from configuration).
    std::vector<uint8_t> data = tmp->getData();
    ASSERT_EQ(2, data.size());

    const uint8_t foo_expected[] = {
        0x12, 0x34
    };
    EXPECT_EQ(0, memcmp(&data[0], foo_expected, 2));

    // more checks to be implemented
}

TEST_F(Dhcpv6SrvTest, serverReceivedPacketName) {
    // Check all possible packet types
    for (int itype = 0; itype < 256; ++itype) {
        uint8_t type = itype;

        switch (type) {
        case DHCPV6_CONFIRM:
            EXPECT_STREQ("CONFIRM", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_DECLINE:
            EXPECT_STREQ("DECLINE", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_INFORMATION_REQUEST:
            EXPECT_STREQ("INFORMATION_REQUEST",
                         Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_REBIND:
            EXPECT_STREQ("REBIND", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_RELEASE:
            EXPECT_STREQ("RELEASE", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_RENEW:
            EXPECT_STREQ("RENEW", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_REQUEST:
            EXPECT_STREQ("REQUEST", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        case DHCPV6_SOLICIT:
            EXPECT_STREQ("SOLICIT", Dhcpv6Srv::serverReceivedPacketName(type));
            break;

        default:
            EXPECT_STREQ("UNKNOWN", Dhcpv6Srv::serverReceivedPacketName(type));
        }
    }
}

}   // end of anonymous namespace
