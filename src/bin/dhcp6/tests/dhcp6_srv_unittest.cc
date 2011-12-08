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
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "dhcp/dhcp6.h"
#include "dhcp6/dhcp6_srv.h"
#include "dhcp/option6_ia.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace test {

class NakedDhcpv6Srv: public Dhcpv6Srv {
    // "naked" Interface Manager, exposes internal fields
public:
    NakedDhcpv6Srv() { }

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
    }
};

TEST_F(Dhcpv6SrvTest, basic) {
    // there's almost no code now. What's there provides echo capability
    // that is just a proof of concept and will be removed soon
    // No need to thoroughly test it

    // srv has stubbed interface detection. It will read
    // interfaces.txt instead. It will pretend to have detected
    // fe80::1234 link-local address on eth0 interface. Obviously
    // an attempt to bind this socket will fail.
    EXPECT_NO_THROW( {
        Dhcpv6Srv * srv = new Dhcpv6Srv();

        delete srv;
        });

}

TEST_F(Dhcpv6SrvTest, Solicit_basic) {
    NakedDhcpv6Srv * srv = 0;
    EXPECT_NO_THROW( srv = new NakedDhcpv6Srv(); );

    // a dummy content for client-id
    boost::shared_array<uint8_t> clntDuid(new uint8_t[32]);
    for (int i=0; i<32; i++)
        clntDuid[i] = 100+i;

    boost::shared_ptr<Pkt6> sol =
        boost::shared_ptr<Pkt6>(new Pkt6(DHCPV6_SOLICIT,
                                         1234, Pkt6::UDP));

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

    boost::shared_ptr<Option> clientid =
        boost::shared_ptr<Option>(new Option(Option::V6, D6O_CLIENTID,
                                             clntDuid, 0, 16));
    sol->addOption(clientid);

    boost::shared_ptr<Pkt6> reply = srv->processSolicit(sol);

    // check if we get response at all
    ASSERT_TRUE( reply != boost::shared_ptr<Pkt6>() );

    EXPECT_EQ( DHCPV6_ADVERTISE, reply->getType() );
    EXPECT_EQ( 1234, reply->getTransid() );

    boost::shared_ptr<Option> tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE( tmp );

    Option6IA * reply_ia = dynamic_cast<Option6IA*> ( tmp.get() );
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
