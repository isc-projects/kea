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

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp/iface_mgr.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <util/buffer.h>
#include <util/range_utilities.h>
#include <stats/stats_mgr.h>

#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcp/tests/pkt_captures.h>
#include <cc/command_interpreter.h>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::test;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;
using namespace std;

namespace {

// This test verifies that incoming SOLICIT can be handled properly when
// there are no subnets configured.
//
// This test sends a SOLICIT and the expected response
// is an ADVERTISE with STATUS_NoAddrsAvail and no address provided in the
// response
TEST_F(NakedDhcpv6SrvTest, SolicitNoSubnet) {
    NakedDhcpv6Srv srv(0);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv.processSolicit(sol);

    // check that we get the right NAK
    checkNakResponse(reply, DHCPV6_ADVERTISE, 1234, STATUS_NoAddrsAvail,
                     0, 0);
}

// This test verifies that incoming REQUEST can be handled properly when
// there are no subnets configured.
//
// This test sends a REQUEST and the expected response
// is an REPLY with STATUS_NoAddrsAvail and no address provided in the
// response
TEST_F(NakedDhcpv6SrvTest, RequestNoSubnet) {
    NakedDhcpv6Srv srv(0);

    // Let's create a REQUEST
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, 234, 1500, 3000);

    // with a hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    req->addOption(ia);
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);

    // server-id is mandatory in REQUEST
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRequest(req);

    // check that we get the right NAK
    checkNakResponse (reply, DHCPV6_REPLY, 1234, STATUS_NoAddrsAvail,
                      0, 0);
}

// This test verifies that incoming RENEW can be handled properly, even when
// no subnets are configured.
//
// This test sends a RENEW and the expected response
// is an REPLY with STATUS_NoBinding and no address provided in the
// response
TEST_F(NakedDhcpv6SrvTest, RenewNoSubnet) {
    NakedDhcpv6Srv srv(0);

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr renewed_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(renewed_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);

    // check that we get the right NAK
    checkNakResponse (reply, DHCPV6_REPLY, 1234, STATUS_NoBinding,
                      0, 0);
}

// This test verifies that incoming RELEASE can be handled properly, even when
// no subnets are configured.
//
// This test sends a RELEASE and the expected response
// is an REPLY with STATUS_NoBinding and no address provided in the
// response
TEST_F(NakedDhcpv6SrvTest, ReleaseNoSubnet) {
    NakedDhcpv6Srv srv(0);

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RELEASE
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    // check that we get the right NAK
    checkNakResponse (reply, DHCPV6_REPLY, 1234, STATUS_NoBinding, 0, 0);
}

// Test verifies that the Dhcpv6_srv class can be instantiated. It checks a mode
// without open sockets and with sockets opened on a high port (to not require
// root privileges).
TEST_F(Dhcpv6SrvTest, basic) {
    boost::scoped_ptr<Dhcpv6Srv> srv;

    ASSERT_NO_THROW( {
        // Skip opening any sockets
        srv.reset(new NakedDhcpv6Srv(0));
    });
    srv.reset();
    ASSERT_NO_THROW({
        // open an unpriviledged port
        srv.reset(new NakedDhcpv6Srv(DHCP6_SERVER_PORT + 10000));
    });
}

// Test checks that DUID is generated properly
TEST_F(Dhcpv6SrvTest, DUID) {

    boost::scoped_ptr<Dhcpv6Srv> srv;
    ASSERT_NO_THROW( {
        srv.reset(new NakedDhcpv6Srv(0));
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
    case DUID::DUID_LLT: {
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
    case DUID::DUID_EN: {
        // there's not much we can check. Just simple
        // check if it is not all zeros
        vector<uint8_t> content(len-2);
        data.readVector(content, len-2);
        EXPECT_FALSE(isRangeZero(content.begin(), content.end()));
        break;
    }
    case DUID::DUID_LL: {
        // not supported yet
        cout << "Test not implemented for DUID-LL." << endl;

        // No failure here. There's really no way for test LL DUID. It doesn't
        // even make sense to check if that Link Layer is actually present on
        // a physical interface. RFC3315 says a server should write its DUID
        // and keep it despite hardware changes.
        break;
    }
    case DUID::DUID_UUID: // not supported yet
    default:
        ADD_FAILURE() << "Not supported duid type=" << duid_type << endl;
        break;
    }
}

// This test checks if Option Request Option (ORO) is parsed correctly
// and the requested options are actually assigned.
TEST_F(Dhcpv6SrvTest, advertiseOptions) {

    IfaceMgrTestConfig test_config(true);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth0\", "
        "    \"option-data\": [ {"
        "          \"name\": \"dns-servers\","
        "          \"space\": \"dhcp6\","
        "          \"code\": 23,"
        "          \"data\": \"2001:db8:1234:FFFF::1, 2001:db8:1234:FFFF::2\","
        "          \"csv-format\": True"
        "        },"
        "        {"
        "          \"name\": \"subscriber-id\","
        "          \"space\": \"dhcp6\","
        "          \"code\": 38,"
        "          \"data\": \"1234\","
        "          \"csv-format\": False"
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";
    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr adv = srv_.processSolicit(sol);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // We have not requested any options so they should not
    // be included in the response.
    ASSERT_FALSE(adv->getOption(D6O_SUBSCRIBER_ID));
    ASSERT_FALSE(adv->getOption(D6O_NAME_SERVERS));

    // Let's now request some options. We expect that the server
    // will include them in its response.
    boost::shared_ptr<OptionIntArray<uint16_t> >
        option_oro(new OptionIntArray<uint16_t>(Option::V6, D6O_ORO));
    // Create vector with two option codes.
    std::vector<uint16_t> codes(2);
    codes[0] = D6O_SUBSCRIBER_ID;
    codes[1] = D6O_NAME_SERVERS;
    // Pass this code to option.
    option_oro->setValues(codes);
    // Append ORO to SOLICIT message.
    sol->addOption(option_oro);

    // Need to process SOLICIT again after requesting new option.
    adv = srv_.processSolicit(sol);
    ASSERT_TRUE(adv);

    OptionPtr tmp = adv->getOption(D6O_NAME_SERVERS);
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
    tmp = adv->getOption(D6O_SUBSCRIBER_ID);
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


// There are no dedicated tests for Dhcpv6Srv::handleIA_NA and Dhcpv6Srv::assignLeases
// as they are indirectly tested in Solicit and Request tests.

// This test verifies that incoming SOLICIT can be handled properly, that an
// ADVERTISE is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// This test sends a SOLICIT without any hint in IA_NA.
//
// constructed very simple SOLICIT message with:
// - client-id option (mandatory)
// - IA option (a request for address, without any addresses)
//
// expected returned ADVERTISE message:
// - copy of client-id
// - server-id
// - IA that includes IAADDR
TEST_F(Dhcpv6SrvTest, SolicitBasic) {
    NakedDhcpv6Srv srv(0);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv.processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());
    ASSERT_TRUE(addr);

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr, addr->getAddress(), Lease::TYPE_NA);

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);
}

// This test verifies that incoming SOLICIT can be handled properly, that an
// ADVERTISE is generated, that the response has a prefix and that prefix
// really belongs to the configured pool.
//
// This test sends a SOLICIT without any hint in IA_PD.
//
// constructed very simple SOLICIT message with:
// - client-id option (mandatory)
// - IA option (a request for address, without any addresses)
//
// expected returned ADVERTISE message:
// - copy of client-id
// - server-id
// - IA that includes IAPREFIX
TEST_F(Dhcpv6SrvTest, pdSolicitBasic) {

    NakedDhcpv6Srv srv(0);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    sol->addOption(generateIA(D6O_IA_PD, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv.processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAPrefix> prefix = checkIA_PD(reply, 234, subnet_->getT1(),
                                                           subnet_->getT2());
    ASSERT_TRUE(prefix);

    // Check that the assigned prefix is indeed from the configured pool
    checkIAAddr(prefix, prefix->getAddress(), Lease::TYPE_PD);
    EXPECT_EQ(pd_pool_->getLength(), prefix->getLength());

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);
}

// This test verifies that incoming SOLICIT can be handled properly, that an
// ADVERTISE is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// This test sends a SOLICIT with IA_NA that contains a valid hint.
//
// constructed very simple SOLICIT message with:
// - client-id option (mandatory)
// - IA option (a request for address, with an address that belongs to the
//              configured pool, i.e. is valid as hint)
//
// expected returned ADVERTISE message:
// - copy of client-id
// - server-id
// - IA that includes IAADDR
TEST_F(Dhcpv6SrvTest, SolicitHint) {
    NakedDhcpv6Srv srv(0);

    // Let's create a SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, 234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, hint));
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    sol->addOption(ia);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv.processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());
    ASSERT_TRUE(addr);

    // check that we've got the address we requested
    checkIAAddr(addr, hint, Lease::TYPE_NA);

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);
}

// This test verifies that incoming SOLICIT can be handled properly, that an
// ADVERTISE is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// This test sends a SOLICIT with IA_NA that contains an invalid hint.
//
// constructed very simple SOLICIT message with:
// - client-id option (mandatory)
// - IA option (a request for address, with an address that does not
//              belong to the configured pool, i.e. is valid as hint)
//
// expected returned ADVERTISE message:
// - copy of client-id
// - server-id
// - IA that includes IAADDR
TEST_F(Dhcpv6SrvTest, SolicitInvalidHint) {
    NakedDhcpv6Srv srv(0);

    // Let's create a SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    IOAddress hint("2001:db8:1::cafe:babe");
    ASSERT_FALSE(subnet_->inPool(Lease::TYPE_NA, hint));
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    sol->addOption(ia);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv.processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());
    ASSERT_TRUE(addr);

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr, addr->getAddress(), Lease::TYPE_NA);
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr->getAddress()));

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);
}

/// @todo: Add a test that client sends hint that is in pool, but currently
/// being used by a different client.

// This test checks that the server is offering different addresses to different
// clients in ADVERTISEs. Please note that ADVERTISE is not a guarantee that such
// an address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same advertise as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. ADVERTISE is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv6SrvTest, ManySolicits) {
    NakedDhcpv6Srv srv(0);

    Pkt6Ptr sol1 = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr sol2 = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 2345));
    Pkt6Ptr sol3 = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 3456));

    sol1->setRemoteAddr(IOAddress("fe80::abcd"));
    sol2->setRemoteAddr(IOAddress("fe80::1223"));
    sol3->setRemoteAddr(IOAddress("fe80::3467"));

    sol1->setIface("eth0");
    sol2->setIface("eth0");
    sol3->setIface("eth0");

    sol1->addOption(generateIA(D6O_IA_NA, 1, 1500, 3000));
    sol2->addOption(generateIA(D6O_IA_NA, 2, 1500, 3000));
    sol3->addOption(generateIA(D6O_IA_NA, 3, 1500, 3000));

    // different client-id sizes
    OptionPtr clientid1 = generateClientId(12);
    OptionPtr clientid2 = generateClientId(14);
    OptionPtr clientid3 = generateClientId(16);

    sol1->addOption(clientid1);
    sol2->addOption(clientid2);
    sol3->addOption(clientid3);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply1 = srv.processSolicit(sol1);
    Pkt6Ptr reply2 = srv.processSolicit(sol2);
    Pkt6Ptr reply3 = srv.processSolicit(sol3);

    // check if we get response at all
    checkResponse(reply1, DHCPV6_ADVERTISE, 1234);
    checkResponse(reply2, DHCPV6_ADVERTISE, 2345);
    checkResponse(reply3, DHCPV6_ADVERTISE, 3456);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr1 = checkIA_NA(reply1, 1, subnet_->getT1(),
                                                subnet_->getT2());
    boost::shared_ptr<Option6IAAddr> addr2 = checkIA_NA(reply2, 2, subnet_->getT1(),
                                                subnet_->getT2());
    boost::shared_ptr<Option6IAAddr> addr3 = checkIA_NA(reply3, 3, subnet_->getT1(),
                                                subnet_->getT2());
    ASSERT_TRUE(addr1);
    ASSERT_TRUE(addr2);
    ASSERT_TRUE(addr3);

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr1, addr1->getAddress(), Lease::TYPE_NA);
    checkIAAddr(addr2, addr2->getAddress(), Lease::TYPE_NA);
    checkIAAddr(addr3, addr3->getAddress(), Lease::TYPE_NA);

    // check DUIDs
    checkServerId(reply1, srv.getServerID());
    checkServerId(reply2, srv.getServerID());
    checkServerId(reply3, srv.getServerID());
    checkClientId(reply1, clientid1);
    checkClientId(reply2, clientid2);
    checkClientId(reply3, clientid3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1->getAddress(), addr2->getAddress());
    EXPECT_NE(addr2->getAddress(), addr3->getAddress());
    EXPECT_NE(addr3->getAddress(), addr1->getAddress());
    cout << "Offered address to client1=" << addr1->getAddress() << endl;
    cout << "Offered address to client2=" << addr2->getAddress() << endl;
    cout << "Offered address to client3=" << addr3->getAddress() << endl;
}

// This test verifies that incoming REQUEST can be handled properly, that a
// REPLY is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// This test sends a REQUEST with IA_NA that contains a valid hint.
//
// constructed very simple REQUEST message with:
// - client-id option (mandatory)
// - IA option (a request for address, with an address that belongs to the
//              configured pool, i.e. is valid as hint)
//
// expected returned REPLY message:
// - copy of client-id
// - server-id
// - IA that includes IAADDR
TEST_F(Dhcpv6SrvTest, RequestBasic) {
    NakedDhcpv6Srv srv(0);

    // Let's create a REQUEST
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, 234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, hint));
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    req->addOption(ia);
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);

    // server-id is mandatory in REQUEST
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRequest(req);

    // check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234,
                                                       subnet_->getT1(),
                                                       subnet_->getT2());
    ASSERT_TRUE(addr);

    // check that we've got the address we requested
    checkIAAddr(addr, hint, Lease::TYPE_NA);

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    // check that the lease is really in the database
    Lease6Ptr l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr);
    EXPECT_TRUE(l);
    LeaseMgrFactory::instance().deleteLease(addr->getAddress());
}

// This test verifies that incoming REQUEST can be handled properly, that a
// REPLY is generated, that the response has a prefix and that prefix
// really belongs to the configured pool.
//
// This test sends a REQUEST with IA_PD that contains a valid hint.
//
// constructed very simple REQUEST message with:
// - client-id option (mandatory)
// - IA option (a request for address, with an address that belongs to the
//              configured pool, i.e. is valid as hint)
//
// expected returned REPLY message:
// - copy of client-id
// - server-id
// - IA that includes IAPREFIX
TEST_F(Dhcpv6SrvTest, pdRequestBasic) {

    NakedDhcpv6Srv srv(0);

    // Let's create a REQUEST
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_PD, 234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:2:f::");
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_PD, hint));
    OptionPtr hint_opt(new Option6IAPrefix(D6O_IAPREFIX, hint, 64, 300, 500));
    ia->addOption(hint_opt);
    req->addOption(ia);
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);

    // server-id is mandatory in REQUEST
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRequest(req);

    // check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_PD);
    ASSERT_TRUE(tmp);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAPrefix> prf = checkIA_PD(reply, 234,
                                                        subnet_->getT1(),
                                                        subnet_->getT2());
    ASSERT_TRUE(prf);

    // check that we've got the address we requested
    checkIAAddr(prf, hint, Lease::TYPE_PD);
    EXPECT_EQ(pd_pool_->getLength(), prf->getLength());

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    // check that the lease is really in the database
    Lease6Ptr l = checkPdLease(duid_, reply->getOption(D6O_IA_PD), prf);
    EXPECT_TRUE(l);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(prf->getAddress()));
}

// This test checks that the server is offering different addresses to different
// clients in REQUEST. Please note that ADVERTISE is not a guarantee that such
// and address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same advertise as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. ADVERTISE is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv6SrvTest, ManyRequests) {
    NakedDhcpv6Srv srv(0);

    ASSERT_TRUE(subnet_);

    Pkt6Ptr req1 = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    Pkt6Ptr req2 = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 2345));
    Pkt6Ptr req3 = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 3456));

    req1->setRemoteAddr(IOAddress("fe80::abcd"));
    req2->setRemoteAddr(IOAddress("fe80::1223"));
    req3->setRemoteAddr(IOAddress("fe80::3467"));

    req1->setIface("eth0");
    req2->setIface("eth0");
    req3->setIface("eth0");

    req1->addOption(generateIA(D6O_IA_NA, 1, 1500, 3000));
    req2->addOption(generateIA(D6O_IA_NA, 2, 1500, 3000));
    req3->addOption(generateIA(D6O_IA_NA, 3, 1500, 3000));

    // different client-id sizes
    OptionPtr clientid1 = generateClientId(12);
    OptionPtr clientid2 = generateClientId(14);
    OptionPtr clientid3 = generateClientId(16);

    req1->addOption(clientid1);
    req2->addOption(clientid2);
    req3->addOption(clientid3);

    // server-id is mandatory in REQUEST
    req1->addOption(srv.getServerID());
    req2->addOption(srv.getServerID());
    req3->addOption(srv.getServerID());

    // Pass it to the server and get an advertise
    Pkt6Ptr reply1 = srv.processRequest(req1);
    Pkt6Ptr reply2 = srv.processRequest(req2);
    Pkt6Ptr reply3 = srv.processRequest(req3);

    // check if we get response at all
    checkResponse(reply1, DHCPV6_REPLY, 1234);
    checkResponse(reply2, DHCPV6_REPLY, 2345);
    checkResponse(reply3, DHCPV6_REPLY, 3456);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr1 = checkIA_NA(reply1, 1, subnet_->getT1(),
                                                subnet_->getT2());
    boost::shared_ptr<Option6IAAddr> addr2 = checkIA_NA(reply2, 2, subnet_->getT1(),
                                                subnet_->getT2());
    boost::shared_ptr<Option6IAAddr> addr3 = checkIA_NA(reply3, 3, subnet_->getT1(),
                                                subnet_->getT2());

    ASSERT_TRUE(addr1);
    ASSERT_TRUE(addr2);
    ASSERT_TRUE(addr3);

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr1, addr1->getAddress(), Lease::TYPE_NA);
    checkIAAddr(addr2, addr2->getAddress(), Lease::TYPE_NA);
    checkIAAddr(addr3, addr3->getAddress(), Lease::TYPE_NA);

    // check DUIDs
    checkServerId(reply1, srv.getServerID());
    checkServerId(reply2, srv.getServerID());
    checkServerId(reply3, srv.getServerID());
    checkClientId(reply1, clientid1);
    checkClientId(reply2, clientid2);
    checkClientId(reply3, clientid3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1->getAddress(), addr2->getAddress());
    EXPECT_NE(addr2->getAddress(), addr3->getAddress());
    EXPECT_NE(addr3->getAddress(), addr1->getAddress());
    cout << "Assigned address to client1=" << addr1->getAddress() << endl;
    cout << "Assigned address to client2=" << addr2->getAddress() << endl;
    cout << "Assigned address to client3=" << addr3->getAddress() << endl;
}

// This test verifies that incoming (positive) RENEW can be handled properly, that a
// REPLY is generated, that the response has an address and that address
// really belongs to the configured pool and that lease is actually renewed.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_NA that includes IAADDR
// - lease is actually renewed in LeaseMgr
TEST_F(Dhcpv6SrvTest, renewBasic) {
    testRenewBasic(Lease::TYPE_NA, "2001:db8:1:1::cafe:babe",
                   "2001:db8:1:1::cafe:babe", 128);
}

// This test verifies that incoming (positive) PD RENEW can be handled properly,
// that a REPLY is generated, that the response has a prefix and that prefix
// really belongs to the configured pool and that lease is actually renewed.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_PD that includes IAPREFIX
// - lease is actually renewed in LeaseMgr
TEST_F(Dhcpv6SrvTest, pdRenewBasic) {
    testRenewBasic(Lease::TYPE_PD, "2001:db8:1:2::",
                   "2001:db8:1:2::", pd_pool_->getLength());
}

// This test verifies that incoming (invalid) RENEW with an address
// can be handled properly. This has changed with #3565. The server
// is now able to allocate a lease in Renew if it's available.
// Previous testRenewReject is now split into 3 tests.
//
// This test checks the first scenario: There is no lease at all.
// The server will try to assign it. Since it is not used by anyone else,
// the server will assign it. This is convenient for various types
// of recoveries, e.g. when the server lost its database.
TEST_F(Dhcpv6SrvTest, RenewUnknown) {
    // False means that the lease should not be created before renewal attempt
    testRenewBasic(Lease::TYPE_NA, "2001:db8:1:1::abc", "2001:db8:1:1::abc",
                   128, false);
}

// This test checks that a client that renews existing lease, but uses
// a wrong IAID, will be processed correctly. As there is no lease for
// this (duid, type, iaid) tuple, this is treated as a new IA, regardless
// if the client inserted an address that is used in a different IA.
// After #3565 was implemented, the server will attempt to assign a lease.
// The one that client requested is already used with different IAID, so
// it will just pick a different lease. This is the second out of three
// scenarios tests by old RenewReject test.
TEST_F(Dhcpv6SrvTest, RenewWrongIAID) {
    testRenewWrongIAID(Lease::TYPE_NA, IOAddress("2001:db8:1:1::abc"));
}

// This test checks whether client A can renew an address that is currently
// leased by client B. The server should detect that the lease belong to
// someone else and assign a different lease. This is the third out of three
// scenarios tests by old RenewReject test.
TEST_F(Dhcpv6SrvTest, RenewSomeoneElesesLease) {
    testRenewSomeoneElsesLease(Lease::TYPE_NA, IOAddress("2001:db8::1"));
}

// This test verifies that incoming (invalid) RENEW with a prefix
// can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_PD that includes STATUS-CODE
// - No lease in LeaseMgr
TEST_F(Dhcpv6SrvTest, pdRenewReject) {
    testRenewReject(Lease::TYPE_PD, IOAddress("2001:db8:1:2::"));
}

// This test verifies that incoming (positive) RELEASE with address can be
// handled properly, that a REPLY is generated, that the response has status
// code and that the lease is indeed removed from the database.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_NA that does not include an IAADDR
// - lease is actually removed from LeaseMgr
TEST_F(Dhcpv6SrvTest, ReleaseBasic) {
    testReleaseBasic(Lease::TYPE_NA, IOAddress("2001:db8:1:1::cafe:babe"),
                     IOAddress("2001:db8:1:1::cafe:babe"));
}

// This test verifies that incoming (positive) RELEASE with prefix can be
// handled properly, that a REPLY is generated, that the response has
// status code and that the lease is indeed removed from the database.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_PD that does not include an IAPREFIX
// - lease is actually removed from LeaseMgr
TEST_F(Dhcpv6SrvTest, pdReleaseBasic) {
    testReleaseBasic(Lease::TYPE_PD, IOAddress("2001:db8:1:2::"),
                     IOAddress("2001:db8:1:2::"));
}

// This test verifies that incoming (invalid) RELEASE with an address
// can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_NA that includes STATUS-CODE
// - No lease in LeaseMgr
TEST_F(Dhcpv6SrvTest, ReleaseReject) {
    testReleaseReject(Lease::TYPE_NA, IOAddress("2001:db8:1:1::dead"));
}

// This test verifies that incoming (invalid) RELEASE with a prefix
// can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA_PD that includes STATUS-CODE
// - No lease in LeaseMgr
TEST_F(Dhcpv6SrvTest, pdReleaseReject) {
    testReleaseReject(Lease::TYPE_PD, IOAddress("2001:db8:1:2::"));
}

// This test verifies if the sanityCheck() really checks options presence.
TEST_F(Dhcpv6SrvTest, sanityCheck) {
    NakedDhcpv6Srv srv(0);

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));

    // Set link-local sender address, so appropriate subnet can be
    // selected for this packet.
    pkt->setRemoteAddr(IOAddress("fe80::abcd"));

    // client-id is optional for information-request, so
    EXPECT_NO_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::OPTIONAL, Dhcpv6Srv::OPTIONAL));

    // empty packet, no client-id, no server-id
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::FORBIDDEN),
                 RFCViolation);

    // This doesn't make much sense, but let's check it for completeness
    EXPECT_NO_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::FORBIDDEN, Dhcpv6Srv::FORBIDDEN));

    OptionPtr clientid = generateClientId();
    pkt->addOption(clientid);

    // client-id is mandatory, server-id is forbidden (as in SOLICIT or REBIND)
    EXPECT_NO_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::FORBIDDEN));

    pkt->addOption(srv.getServerID());

    // both client-id and server-id are mandatory (as in REQUEST, RENEW, RELEASE, DECLINE)
    EXPECT_NO_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::MANDATORY));

    // sane section ends here, let's do some negative tests as well

    pkt->addOption(clientid);
    pkt->addOption(clientid);

    // with more than one client-id it should throw, no matter what
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::OPTIONAL, Dhcpv6Srv::OPTIONAL),
                 RFCViolation);
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::OPTIONAL),
                 RFCViolation);
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::OPTIONAL, Dhcpv6Srv::MANDATORY),
                 RFCViolation);
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::MANDATORY),
                 RFCViolation);

    pkt->delOption(D6O_CLIENTID);
    pkt->delOption(D6O_CLIENTID);

    // again we have only one client-id

    // let's try different type of insanity - several server-ids
    pkt->addOption(srv.getServerID());
    pkt->addOption(srv.getServerID());

    // with more than one server-id it should throw, no matter what
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::OPTIONAL, Dhcpv6Srv::OPTIONAL),
                 RFCViolation);
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::OPTIONAL),
                 RFCViolation);
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::OPTIONAL, Dhcpv6Srv::MANDATORY),
                 RFCViolation);
    EXPECT_THROW(srv.sanityCheck(pkt, Dhcpv6Srv::MANDATORY, Dhcpv6Srv::MANDATORY),
                 RFCViolation);
}
// Check that the server is testing if server identifier received in the
// query, matches server identifier used by the server.
TEST_F(Dhcpv6SrvTest, testServerID) {
        NakedDhcpv6Srv srv(0);

        Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    std::vector<uint8_t> bin;

    // duid_llt constructed with: time = 0, macaddress = 00:00:00:00:00:00
    // it's necessary to generate server identifier option
    isc::util::encode::decodeHex("0001000100000000000000000000", bin);
    // Now create server identifier option
    OptionPtr serverid = OptionPtr(new Option(Option::V6, D6O_SERVERID, bin));

    // Server identifier option is MANDATORY in Request message.
    // Add server identifier option with different value from one that
    // server is using.
    req->addOption(serverid);

    // Message should be dropped
    EXPECT_FALSE(srv.testServerID(req));

    // Delete server identifier option and add new one, with same value as
    // server's server identifier.
    req->delOption(D6O_SERVERID);
    req->addOption(srv.getServerID());

    // With proper server identifier we expect true
    EXPECT_TRUE(srv.testServerID(req));

    // server-id MUST NOT appear in Solicit, so check if server is
    // not dropping a message without server id.
    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));

    EXPECT_TRUE(srv.testServerID(req));
}

// Test that some messages are discarded by the server if they are sent to
// unicast address.
TEST_F(Dhcpv6SrvTest, testUnicast) {
    NakedDhcpv6Srv srv(0);
    // Explicitly list client's message types which must be discarded if
    // sent to unicast address.
    const uint8_t not_allowed_unicast[] = {
        DHCPV6_SOLICIT,
        DHCPV6_CONFIRM,
        DHCPV6_REBIND,
        DHCPV6_INFORMATION_REQUEST
    };
    // Iterate over these messages and make sure they are discarded.
    for (int i = 0; i < sizeof(not_allowed_unicast); ++i) {
        Pkt6Ptr msg = Pkt6Ptr(new Pkt6(not_allowed_unicast[i], 1234));
        msg->setLocalAddr(IOAddress("2001:db8:1::1"));
        EXPECT_FALSE(srv.testUnicast(msg))
            << "server accepts message type "
            << static_cast<int>(not_allowed_unicast[i])
            << "being sent to unicast address; this message should"
            " be discarded according to section 15 of RFC3315";
    }
    // Explicitly list client/relay message types which are allowed to
    // be sent to unicast.
    const uint8_t allowed_unicast[] = {
        DHCPV6_REQUEST,
        DHCPV6_RENEW,
        DHCPV6_RELEASE,
        DHCPV6_DECLINE,
        DHCPV6_RELAY_FORW
    };
    // Iterate over these messages and check that they are accepted being
    // sent to unicast.
    for (int i = 0; i < sizeof(allowed_unicast); ++i) {
        Pkt6Ptr msg = Pkt6Ptr(new Pkt6(allowed_unicast[i], 1234));
        msg->setLocalAddr(IOAddress("2001:db8:1::1"));
        msg->addOption(srv.getServerID());
        EXPECT_TRUE(srv.testUnicast(msg))
            << "server doesn't accept message type "
            << static_cast<int>(allowed_unicast[i])
            << "being sent to unicast address";
    }


}

// This test verifies if selectSubnet() selects proper subnet for a given
// source address.
TEST_F(Dhcpv6SrvTest, selectSubnetAddr) {
    NakedDhcpv6Srv srv(0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    // CASE 1: We have only one subnet defined and we received local traffic.
    // The only available subnet used to be picked, but not anymore
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1); // just a single subnet
    CfgMgr::instance().commit();

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    pkt->setRemoteAddr(IOAddress("fe80::abcd"));

    // The clause for assuming local subnet if there is only one subnet is was
    // removed.
    EXPECT_FALSE(srv.selectSubnet(pkt));

    // CASE 2: We have only one subnet defined and we received relayed traffic.
    // We should NOT select it.

    // Identical steps as in case 1, but repeated for clarity
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1); // just a single subnet
    CfgMgr::instance().commit();
    pkt->setRemoteAddr(IOAddress("2001:db8:abcd::2345"));
    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 3: We have three subnets defined and we received local traffic.
    // Nothing should be selected.
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();
    pkt->setRemoteAddr(IOAddress("fe80::abcd"));
    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 4: We have three subnets defined and we received relayed traffic
    // that came out of subnet 2. We should select subnet2 then
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();
    pkt->setRemoteAddr(IOAddress("2001:db8:2::baca"));
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 5: We have three subnets defined and we received relayed traffic
    // that came out of undefined subnet. We should select nothing
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();
    pkt->setRemoteAddr(IOAddress("2001:db8:4::baca"));
    EXPECT_FALSE(srv.selectSubnet(pkt));
}

// This test verifies if selectSubnet() selects proper subnet for a given
// network interface name.
TEST_F(Dhcpv6SrvTest, selectSubnetIface) {
    NakedDhcpv6Srv srv(0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    subnet1->setIface("eth0");
    subnet3->setIface("wifi1");

    // CASE 1: We have only one subnet defined and it is available via eth0.
    // Packet came from eth0. The only available subnet should be selected
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1); // just a single subnet
    CfgMgr::instance().commit();

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    pkt->setIface("eth0");

    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet1);

    // CASE 2: We have only one subnet defined and it is available via eth0.
    // Packet came from eth1. We should not select it
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1); // just a single subnet
    CfgMgr::instance().commit();

    pkt->setIface("eth1");

    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 3: We have only 3 subnets defined, one over eth0, one remote and
    // one over wifi1.
    // Packet came from eth1. We should not select it
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();

    pkt->setIface("eth0");
    EXPECT_EQ(subnet1, srv.selectSubnet(pkt));

    pkt->setIface("eth3"); // no such interface
    EXPECT_EQ(Subnet6Ptr(), srv.selectSubnet(pkt)); // nothing selected

    pkt->setIface("wifi1");
    EXPECT_EQ(subnet3, srv.selectSubnet(pkt));
}

// This test verifies if selectSubnet() selects proper subnet for a given
// linkaddr in RELAY-FORW message
TEST_F(Dhcpv6SrvTest, selectSubnetRelayLinkaddr) {
    NakedDhcpv6Srv srv(0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("2001:db8:2::1234");
    relay.peeraddr_ = IOAddress("fe80::1");

    // CASE 1: We have only one subnet defined and we received relayed traffic.
    // The only available subnet should NOT be selected.
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1); // just a single subnet
    CfgMgr::instance().commit();

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    pkt->relay_info_.push_back(relay);

    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 2: We have three subnets defined and we received relayed traffic.
    // Nothing should be selected.
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 3: We have three subnets defined and we received relayed traffic
    // that came out of subnet 2. We should select subnet2 then
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();

    // Source of the packet should have no meaning. Selection is based
    // on linkaddr field in the relay
    pkt->setRemoteAddr(IOAddress("2001:db8:1::baca"));
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 4: We have three subnets defined and we received relayed traffic
    // that came out of undefined subnet. We should select nothing
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();
    pkt->relay_info_.clear();
    relay.linkaddr_ = IOAddress("2001:db8:4::1234");
    pkt->relay_info_.push_back(relay);
    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

}

// This test verifies if selectSubnet() selects proper subnet for a given
// interface-id option
TEST_F(Dhcpv6SrvTest, selectSubnetRelayInterfaceId) {
    NakedDhcpv6Srv srv(0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    subnet1->setInterfaceId(generateInterfaceId("relay1"));
    subnet2->setInterfaceId(generateInterfaceId("relay2"));

    // CASE 1: We have only one subnet defined and it is for interface-id "relay1"
    // Packet came with interface-id "relay2". We should not select subnet1
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1); // just a single subnet
    CfgMgr::instance().commit();

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("2001:db8:2::1234");
    relay.peeraddr_ = IOAddress("fe80::1");
    OptionPtr opt = generateInterfaceId("relay2");
    relay.options_.insert(make_pair(opt->getType(), opt));
    pkt->relay_info_.push_back(relay);

    // There is only one subnet configured and we are outside of that subnet
    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 2: We have only one subnet defined and it is for interface-id "relay2"
    // Packet came with interface-id "relay2". We should select it
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2); // just a single subnet
    CfgMgr::instance().commit();
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 3: We have only 3 subnets defined: one remote for interface-id "relay1",
    // one remote for interface-id "relay2" and third local
    // packet comes with interface-id "relay2". We should select subnet2
    CfgMgr::instance().clear();
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet1);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet2);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet3);
    CfgMgr::instance().commit();

    EXPECT_EQ(subnet2, srv.selectSubnet(pkt));
}

// This test verifies if the server-id disk operations (read, write) are
// working properly.
TEST_F(Dhcpv6SrvTest, ServerID) {
    NakedDhcpv6Srv srv(0);

    string duid1_text = "01:ff:02:03:06:80:90:ab:cd:ef";
    uint8_t duid1[] = { 0x01, 0xff, 2, 3, 6, 0x80, 0x90, 0xab, 0xcd, 0xef };
    OptionBuffer expected_duid1(duid1, duid1 + sizeof(duid1));

    fstream file1(DUID_FILE, ios::out | ios::trunc);
    file1 << duid1_text;
    file1.close();

    // Test reading from a file
    EXPECT_TRUE(srv.loadServerID(DUID_FILE));
    ASSERT_TRUE(srv.getServerID());
    ASSERT_EQ(sizeof(duid1) + Option::OPTION6_HDR_LEN, srv.getServerID()->len());
    ASSERT_TRUE(expected_duid1 == srv.getServerID()->getData());

    // Now test writing to a file
    EXPECT_EQ(0, unlink(DUID_FILE));
    EXPECT_NO_THROW(srv.writeServerID(DUID_FILE));

    fstream file2(DUID_FILE, ios::in);
    ASSERT_TRUE(file2.good());
    string text;
    file2 >> text;
    file2.close();

    EXPECT_EQ(duid1_text, text);
}

// Checks if server responses are sent to the proper port.
TEST_F(Dhcpv6SrvTest, portsDirectTraffic) {

    NakedDhcpv6Srv srv(0);

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = PktCaptures::captureSimpleSolicit();

    // Simulate that we have received that traffic
    srv.fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    srv.run();

    // Get Advertise...
    ASSERT_FALSE(srv.fake_sent_.empty());
    Pkt6Ptr adv = srv.fake_sent_.front();
    ASSERT_TRUE(adv);

    // This is sent back to client directly, should be port 546
    EXPECT_EQ(DHCP6_CLIENT_PORT, adv->getRemotePort());
}

// Checks if server responses are sent to the proper port.
TEST_F(Dhcpv6SrvTest, portsRelayedTraffic) {

    NakedDhcpv6Srv srv(0);

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = PktCaptures::captureRelayedSolicit();

    // Simulate that we have received that traffic
    srv.fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    srv.run();

    // Get Advertise...
    ASSERT_FALSE(srv.fake_sent_.empty());
    Pkt6Ptr adv = srv.fake_sent_.front();
    ASSERT_TRUE(adv);

    // This is sent back to relay, so port is 547
    EXPECT_EQ(DHCP6_SERVER_PORT, adv->getRemotePort());
}

// Checks if server is able to handle a relayed traffic from DOCSIS3.0 modems
// @todo Uncomment this test as part of #3180 work.
// Kea code currently fails to handle docsis traffic.
TEST_F(Dhcpv6SrvTest, docsisTraffic) {

    NakedDhcpv6Srv srv(0);

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = PktCaptures::captureDocsisRelayedSolicit();

    // Simulate that we have received that traffic
    srv.fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    srv.run();

    // We should have an Advertise in response
    ASSERT_FALSE(srv.fake_sent_.empty());
    Pkt6Ptr adv = srv.fake_sent_.front();
    ASSERT_TRUE(adv);
}

// Checks if server is able to handle a relayed traffic from DOCSIS3.0 modems
TEST_F(Dhcpv6SrvTest, docsisVendorOptionsParse) {

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = PktCaptures::captureDocsisRelayedSolicit();
    EXPECT_NO_THROW(sol->unpack());

    // Check if the packet contain
    OptionPtr opt = sol->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    EXPECT_TRUE(vendor->getOption(DOCSIS3_V6_ORO));
    EXPECT_TRUE(vendor->getOption(36));
    EXPECT_TRUE(vendor->getOption(35));
    EXPECT_TRUE(vendor->getOption(DOCSIS3_V6_DEVICE_TYPE));
    EXPECT_TRUE(vendor->getOption(3));
    EXPECT_TRUE(vendor->getOption(4));
    EXPECT_TRUE(vendor->getOption(5));
    EXPECT_TRUE(vendor->getOption(6));
    EXPECT_TRUE(vendor->getOption(7));
    EXPECT_TRUE(vendor->getOption(8));
    EXPECT_TRUE(vendor->getOption(9));
    EXPECT_TRUE(vendor->getOption(DOCSIS3_V6_VENDOR_NAME));
    EXPECT_TRUE(vendor->getOption(15));

    EXPECT_FALSE(vendor->getOption(20));
    EXPECT_FALSE(vendor->getOption(11));
    EXPECT_FALSE(vendor->getOption(17));
}

// Checks if server is able to parse incoming docsis option and extract suboption 1 (docsis ORO)
TEST_F(Dhcpv6SrvTest, docsisVendorORO) {

    NakedDhcpv6Srv srv(0);

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = PktCaptures::captureDocsisRelayedSolicit();
    ASSERT_NO_THROW(sol->unpack());

    // Check if the packet contains vendor options option
    OptionPtr opt = sol->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    opt = vendor->getOption(DOCSIS3_V6_ORO);
    ASSERT_TRUE(opt);

    OptionUint16ArrayPtr oro = boost::dynamic_pointer_cast<OptionUint16Array>(opt);
    EXPECT_TRUE(oro);
}

// This test checks if Option Request Option (ORO) in docsis (vendor-id=4491)
// vendor options is parsed correctly and the requested options are actually assigned.
TEST_F(Dhcpv6SrvTest, vendorOptionsORO) {

    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-def\": [ {"
        "        \"name\": \"config-file\","
        "        \"code\": 33,"
        "        \"type\": \"string\","
        "        \"array\": False,"
        "        \"record-types\": \"\","
        "        \"space\": \"vendor-4491\","
        "        \"encapsulate\": \"\""
        "     } ],"
        "    \"option-data\": [ {"
        "          \"name\": \"config-file\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": 33,"
        "          \"data\": \"normal_erouter_v6.cm\","
        "          \"csv-format\": True"
        "        }],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"preferred-lifetime\": 3000,"
        "    \"valid-lifetime\": 4000,"
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface("eth0");
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr adv = srv_.processSolicit(sol);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // We did not include any vendor opts in SOLCIT, so there should be none
    // in ADVERTISE.
    ASSERT_FALSE(adv->getOption(D6O_VENDOR_OPTS));

    // Let's add a vendor-option (vendor-id=4491) with a single sub-option.
    // That suboption has code 1 and is a docsis ORO option.
    boost::shared_ptr<OptionUint16Array> vendor_oro(new OptionUint16Array(Option::V6,
                                                                          DOCSIS3_V6_ORO));
    vendor_oro->addValue(DOCSIS3_V6_CONFIG_FILE); // Request option 33
    OptionPtr vendor(new OptionVendor(Option::V6, 4491));
    vendor->addOption(vendor_oro);
    sol->addOption(vendor);

    // Need to process SOLICIT again after requesting new option.
    adv = srv_.processSolicit(sol);
    ASSERT_TRUE(adv);

    // Check if there is vendor option response
    OptionPtr tmp = adv->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(tmp);

    // The response should be OptionVendor object
    boost::shared_ptr<OptionVendor> vendor_resp =
        boost::dynamic_pointer_cast<OptionVendor>(tmp);
    ASSERT_TRUE(vendor_resp);

    OptionPtr docsis33 = vendor_resp->getOption(33);
    ASSERT_TRUE(docsis33);

    OptionStringPtr config_file = boost::dynamic_pointer_cast<OptionString>(docsis33);
    ASSERT_TRUE(config_file);
    EXPECT_EQ("normal_erouter_v6.cm", config_file->getValue());
}

// Test checks whether it is possible to use option definitions defined in
// src/lib/dhcp/docsis3_option_defs.h.
TEST_F(Dhcpv6SrvTest, vendorOptionsDocsisDefinitions) {
    ConstElementPtr x;
    string config_prefix = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "    \"option-data\": [ {"
        "          \"name\": \"config-file\","
        "          \"space\": \"vendor-4491\","
        "          \"code\": ";
    string config_postfix = ","
        "          \"data\": \"normal_erouter_v6.cm\","
        "          \"csv-format\": True"
        "        }],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"preferred-lifetime\": 3000,"
        "    \"valid-lifetime\": 4000,"
        "    \"interface-id\": \"\","
        "    \"interface\": \"\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // There is docsis3 (vendor-id=4491) vendor option 33, which is a
    // config-file. Its format is a single string.
    string config_valid = config_prefix + "33" + config_postfix;

    // There is no option 99 defined in vendor-id=4491. As there is no
    // definition, the config should fail.
    string config_bogus = config_prefix + "99" + config_postfix;

    ElementPtr json_bogus = Element::fromJSON(config_bogus);
    ElementPtr json_valid = Element::fromJSON(config_valid);

    NakedDhcpv6Srv srv(0);

    // This should fail (missing option definition)
    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json_bogus));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json_valid));
    ASSERT_TRUE(x);
    comment_ = isc::config::parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);
}

// This test verifies that the following option structure can be parsed:
// - option (option space 'foobar')
//   - sub option (option space 'foo')
//      - sub option (option space 'bar')
TEST_F(Dhcpv6SrvTest, unpackOptions) {
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
    const char raw_data[] = {
        // First option starts here.
        0x00, 0x01,   // option code = 1
        0x00, 0x0F,   // option length = 15
        0x00, 0x01, 0x02, 0x03, // This option carries uint32 value
        // Sub option starts here.
        0x00, 0x01,  // option code = 1
        0x00, 0x07,  // option length = 7
        0x01, 0x02,  // this option carries uint16 value
        // Last option starts here.
        0x00, 0x01,  // option code = 1
        0x00, 0x01,  // option length = 1
        0x00 // This option carries a single uint8 value and has no sub options.
    };
    OptionBuffer buf(raw_data, raw_data + sizeof(raw_data));

    // Parse options.
    NakedDhcpv6Srv srv(0);
    OptionCollection options;
    ASSERT_NO_THROW(srv.unpackOptions(buf, "space-foobar", options, 0, 0));

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

// Checks if client packets are classified properly
TEST_F(Dhcpv6SrvTest, clientClassification) {

    NakedDhcpv6Srv srv(0);

    // Let's create a relayed SOLICIT. This particular relayed SOLICIT has
    // vendor-class set to docsis3.0
    Pkt6Ptr sol1;
    ASSERT_NO_THROW(sol1 = PktCaptures::captureDocsisRelayedSolicit());
    ASSERT_NO_THROW(sol1->unpack());

    srv.classifyPacket(sol1);

    // It should belong to docsis3.0 class. It should not belong to eRouter1.0
    EXPECT_TRUE(sol1->inClass("VENDOR_CLASS_docsis3.0"));
    EXPECT_FALSE(sol1->inClass("eRouter1.0"));

    // Let's get a relayed SOLICIT. This particular relayed SOLICIT has
    // vendor-class set to eRouter1.0
    Pkt6Ptr sol2;
    ASSERT_NO_THROW(sol2 = PktCaptures::captureeRouterRelayedSolicit());
    ASSERT_NO_THROW(sol2->unpack());

    srv.classifyPacket(sol2);

    EXPECT_TRUE(sol2->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));
    EXPECT_FALSE(sol2->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0"));
}

// Checks if the client-class field is indeed used for subnet selection.
// Note that packet classification is already checked in Dhcpv6SrvTest
// .clientClassification above.
TEST_F(Dhcpv6SrvTest, clientClassify2) {

    // This test configures 2 subnets. We actually only need the
    // first one, but since there's still this ugly hack that picks
    // the pool if there is only one, we must use more than one
    // subnet. That ugly hack will be removed in #3242, currently
    // under review.

    // The second subnet does not play any role here. The client's
    // IP address belongs to the first subnet, so only that first
    // subnet it being tested.
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " {  \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"client-class\": \"foo\" "
        " }, "
        " {  \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"client-class\": \"xyzzy\" "
        " } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // This discover does not belong to foo class, so it will not
    // be serviced
    EXPECT_FALSE(srv_.selectSubnet(sol));

    // Let's add the packet to bar class and try again.
    sol->addClass("bar");

    // Still not supported, because it belongs to wrong class.
    EXPECT_FALSE(srv_.selectSubnet(sol));

    // Let's add it to matching class.
    sol->addClass("foo");

    // This time it should work
    EXPECT_TRUE(srv_.selectSubnet(sol));
}

// Tests whether a packet with custom vendor-class (not erouter or docsis)
// is classified properly.
TEST_F(Dhcpv6SrvTest, clientClassification3) {
    NakedDhcpv6Srv srv(0);

    // Let's create a SOLICIT.
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Now let's add a vendor-class with id=1234 and content "foo"
    OptionVendorClassPtr vendor_class(new OptionVendorClass(Option::V6, 1234));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "foo";
    vendor_class->addTuple(tuple);
    sol->addOption(vendor_class);

    // Now the server classifies the packet.
    srv.classifyPacket(sol);

    // The packet should now belong to VENDOR_CLASS_foo.
    EXPECT_TRUE(sol->inClass(srv.VENDOR_CLASS_PREFIX + "foo"));

    // It should not belong to "foo"
    EXPECT_FALSE(sol->inClass("foo"));

}


// This test checks that the server will handle a Solicit with the Vendor Class
// having a length of 4 (enterprise-id only).
TEST_F(Dhcpv6SrvTest, cableLabsShortVendorClass) {
    NakedDhcpv6Srv srv(0);

    // Create a simple Solicit with the 4-byte long vendor class option.
    Pkt6Ptr sol = PktCaptures::captureCableLabsShortVendorClass();

    // Simulate that we have received that traffic
    srv.fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    srv.run();

    // Get Advertise...
    ASSERT_FALSE(srv.fake_sent_.empty());
    Pkt6Ptr adv = srv.fake_sent_.front();
    ASSERT_TRUE(adv);

    // This is sent back to client, so port is 546
    EXPECT_EQ(DHCP6_CLIENT_PORT, adv->getRemotePort());
}

// Checks if relay IP address specified in the relay-info structure in
// subnet6 is being used properly.
TEST_F(Dhcpv6SrvTest, relayOverride) {

    // We have 2 subnets defined. Note that both have a relay address
    // defined. Both are not belonging to the subnets. That is
    // important, because if the relay belongs to the subnet, there's
    // no need to specify relay override.
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " {  \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:3::1\""
        "    }"
        " }, "
        " {  \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:3::2\""
        "    }"
        " } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    // Let's get the subnet configuration objects
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet6Ptr subnet1 = (*subnets)[0];
    Subnet6Ptr subnet2 = (*subnets)[1];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Now pretend the packet came via one relay.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("2001:db8:1::1");
    relay.peeraddr_ = IOAddress("fe80::1");

    sol->relay_info_.push_back(relay);

    // This is just a sanity check, we're using regular method: the relay
    // belongs to the first (2001:db8:1::/64) subnet, so it's an easy decision.
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(sol));

    // Relay belongs to the second subnet, so it should be selected.
    sol->relay_info_.back().linkaddr_ = IOAddress("2001:db8:2::1");
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(sol));

    // Now let's check if the relay override for the first subnets works
    sol->relay_info_.back().linkaddr_ = IOAddress("2001:db8:3::1");
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(sol));

    // Now repeat that for relay matching the second subnet.
    sol->relay_info_.back().linkaddr_ = IOAddress("2001:db8:3::2");
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(sol));

    // Finally, let's check that completely mismatched relay will not get us
    // anything
    sol->relay_info_.back().linkaddr_ = IOAddress("2001:db8:1234::1");
    EXPECT_FALSE(srv_.selectSubnet(sol));
}

// Checks if relay IP address specified in the relay-info structure can be
// used together with client-classification.
TEST_F(Dhcpv6SrvTest, relayOverrideAndClientClass) {

    // This test configures 2 subnets. They both are on the same link, so they
    // have the same relay-ip address. Furthermore, the first subnet is
    // reserved for clients that belong to class "foo".
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " {  \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"client-class\": \"foo\", "
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:3::1\""
        "    }"
        " }, "
        " {  \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:3::1\""
        "    }"
        " } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    // Let's get the subnet configuration objects
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet6Ptr subnet1 = (*subnets)[0];
    Subnet6Ptr subnet2 = (*subnets)[1];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Now pretend the packet came via one relay.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("2001:db8:3::1");
    relay.peeraddr_ = IOAddress("fe80::1");

    sol->relay_info_.push_back(relay);

    // This packet does not belong to class foo, so it should be rejected in
    // subnet[0], even though the relay-ip matches. It should be accepted in
    // subnet[1], because the subnet matches and there are no class
    // requirements.
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(sol));

    // Now let's add this packet to class foo and recheck. This time it should
    // be accepted in the first subnet, because both class and relay-ip match.
    sol->addClass("foo");
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(sol));
}

/// @brief Creates RSOO option with suboptions
///
/// Creates Relay-Supplied Options option that includes nested options. The
/// codes of those nested options are specified in codes parameter. Content of
/// the options is controlled with payload parameter. When it is zero, option
/// code will be used (e.g. option 100 will contain repeating bytes of value 100).
/// When non-zero is used, payload will be used. Each suboption length is always
/// set to the arbitrarily chosen value of 10.
///
/// @param codes a vector of option codes to be created
/// @param payload specified payload (0 = fill payload with repeating option code)
/// @return RSOO with nested options
OptionPtr createRSOO(const std::vector<uint16_t> codes, uint8_t payload = 0) {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(Option::V6, D6O_RSOO);
    if (!def) {
        isc_throw(BadValue, "Can't find RSOO definition");
    }
    OptionPtr rsoo_container(new OptionCustom(*def, Option::V6));

    for (size_t i = 0; i < codes.size(); ++i) {
        OptionBuffer buf(10, payload ? payload : codes[i]); // let's make the option 10 bytes long
        rsoo_container->addOption(OptionPtr(new Option(Option::V6, codes[i], buf)));
    }

    return (rsoo_container);
}

// Test that the server processes RSOO (Relay Supplied Options option) correctly,
// i.e. it includes in its response the options that are inserted by the relay.
// The server must do this only for options that are RSOO-enabled.
TEST_F(Dhcpv6SrvTest, rsoo) {

    Dhcp6Client client;

    string config =
        "{"
        "    \"relay-supplied-options\": [ \"110\", \"120\", \"130\" ],"
        "    \"preferred-lifetime\": 3000,"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"subnet6\": [ { "
        "        \"pools\": [ { \"pool\": \"2001:db8::/64\" } ],"
        "        \"subnet\": \"2001:db8::/48\" "
        "     } ],"
        "    \"valid-lifetime\": 4000"
        "}";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Now pretend the packet came via one relay.
    Pkt6::RelayInfo relay;
    relay.msg_type_ = DHCPV6_RELAY_FORW;
    relay.hop_count_ = 1;
    relay.linkaddr_ = IOAddress("2001:db8::1");
    relay.peeraddr_ = IOAddress("fe80::1");
    vector<uint16_t> rsoo1;
    rsoo1.push_back(109);
    rsoo1.push_back(110);
    rsoo1.push_back(111);

    // The relay will request echoing back 3 options: 109, 110, 111.
    // The configuration allows echoing back only 110.
    OptionPtr opt = createRSOO(rsoo1);
    relay.options_.insert(make_pair(opt->getType(), opt));
    client.relay_info_.push_back(relay);

    client.doSARR();

    // Option 110 should be copied to the client
    EXPECT_FALSE(client.config_.options_.find(110) == client.config_.options_.end());

    // Options 109 and 111 should not be copied (they are not RSOO-enabled)
    EXPECT_TRUE(client.config_.options_.find(109) == client.config_.options_.end());
    EXPECT_TRUE(client.config_.options_.find(111) == client.config_.options_.end());
}

// Test that the server processes RSOO (Relay Supplied Options option) correctly
// when there are more relays. In particular, the following case is tested:
// if relay1 inserts option A and B, relay2 inserts option B and C, the response
// should include options A, B and C. The server must use instance of option B
// that comes from the first relay, not the second one.
TEST_F(Dhcpv6SrvTest, rsoo2relays) {

    Dhcp6Client client;

    string config =
        "{"
        "    \"relay-supplied-options\": [ \"110\", \"120\", \"130\" ],"
        "    \"preferred-lifetime\": 3000,"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"subnet6\": [ { "
        "        \"pools\": [ { \"pool\": \"2001:db8::/64\" } ],"
        "        \"subnet\": \"2001:db8::/48\" "
        "     } ],"
        "    \"valid-lifetime\": 4000"
        "}";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Now pretend the packet came via two relays.

    // This situation reflects the following case:
    // client----relay1----relay2----server

    // Fabricate the first relay.
    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_FORW;
    relay1.hop_count_ = 1;
    relay1.linkaddr_ = IOAddress("2001:db8::1");
    relay1.peeraddr_ = IOAddress("fe80::1");
    vector<uint16_t> rsoo1;
    rsoo1.push_back(110); // The relay1 will send 2 options: 110, 120
    rsoo1.push_back(120);
    OptionPtr opt = createRSOO(rsoo1, 1); // use 0x1 as payload
    relay1.options_.insert(make_pair(opt->getType(), opt));

    // Now the second relay.
    Pkt6::RelayInfo relay2;
    relay2.msg_type_ = DHCPV6_RELAY_FORW;
    relay2.hop_count_ = 2;
    relay2.linkaddr_ = IOAddress("2001:db8::2");
    relay2.peeraddr_ = IOAddress("fe80::2");
    vector<uint16_t> rsoo2;
    rsoo2.push_back(120); // The relay2 will send 2 options: 120, 130
    rsoo2.push_back(130);
    opt = createRSOO(rsoo2, 2); // use 0x2 as payload
    relay2.options_.insert(make_pair(opt->getType(), opt));

    // The relays ecapsulate packet in this order: relay1, relay2, but the server
    // decapsulates the packet in reverse order.
    client.relay_info_.push_back(relay2);
    client.relay_info_.push_back(relay1);

    // There's a conflict here. Both relays want the server to echo back option
    // 120. According to RFC6422, section 6:
    //
    // When such a conflict exists, the DHCP server MUST choose no more than
    // one of these options to forward to the client.  The DHCP server MUST
    // NOT forward more than one of these options to the client.
    //
    // By default, the DHCP server MUST choose the innermost value -- the
    // value supplied by the relay agent closest to the DHCP client -- to
    // forward to the DHCP client.

    // Let the client do his thing.
    client.doSARR();

    int count110 = 0; // Let's count how many times option 110 was echoed back
    int count120 = 0; // Let's count how many times option 120 was echoed back
    int count130 = 0; // Let's count how many times option 130 was echoed back
    OptionPtr opt120;
    for (OptionCollection::const_iterator it = client.config_.options_.begin();
         it != client.config_.options_.end(); ++it) {
        switch (it->second->getType()) {
        case 110:
            count110++;
            break;
        case 120:
            count120++;
            opt120 = it->second;
            break;
        case 130:
            count130++;
            break;
        default:
            break;
        }
    }

    // We expect to have exactly one instance of each option code.
    EXPECT_EQ(1, count110);
    EXPECT_EQ(1, count120);
    EXPECT_EQ(1, count130);

    // Now, let's check if the proper instance of option 120 was sent. It should
    // match the content of what the first relay had sent.
    ASSERT_TRUE(opt120);
    vector<uint8_t> expected(10, 1);
    EXPECT_TRUE(expected == opt120->getData());
}

// This test verifies that the server will send the option for which it
// has a candidate, rather than the option sent by the relay in the RSOO.
TEST_F(Dhcpv6SrvTest, rsooOverride) {
    Dhcp6Client client;
    // The client will be requesting specific options.
    client.useORO(true);

    // The following configuration enables RSOO options: 110 and 120.
    // It also configures the server with option 120 which should
    // "override" the option 120 sent in the RSOO by the relay.
    string config =
        "{"
        "    \"relay-supplied-options\": [ \"110\", \"120\" ],"
        "    \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 120,"
        "      \"type\": \"binary\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"dhcp6\","
        "      \"encapsulate\": \"\""
        "    } ],"
        "    \"option-data\": [ {"
        "      \"code\": 120,"
        "      \"data\": \"05\""
        "    } ],"
        "    \"preferred-lifetime\": 3000,"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"subnet6\": [ { "
        "        \"pools\": [ { \"pool\": \"2001:db8::/64\" } ],"
        "        \"subnet\": \"2001:db8::/48\" "
        "     } ],"
        "    \"valid-lifetime\": 4000"
        "}";

    EXPECT_NO_THROW(configure(config, *client.getServer()));

    // Fabricate the relay.
    Pkt6::RelayInfo relay;
    relay.msg_type_ = DHCPV6_RELAY_FORW;
    relay.hop_count_ = 1;
    relay.linkaddr_ = IOAddress("2001:db8::1");
    relay.peeraddr_ = IOAddress("fe80::1");
    vector<uint16_t> rsoo;
    // The relay will send 2 options: 110, 120
    rsoo.push_back(110);
    rsoo.push_back(120);
    // Use 0x1 as payload
    OptionPtr opt = createRSOO(rsoo, 1);
    relay.options_.insert(make_pair(opt->getType(), opt));
    client.relay_info_.push_back(relay);

    // Client should request option 120 in the ORO so as the server
    // sends the configured option 120 to the client.
    client.requestOption(120);
    client.doSARR();

    // The option 110 should be the one injected by the relay.
    opt = client.config_.findOption(110);
    ASSERT_TRUE(opt);
    // We check that this is the option injected by the relay by
    // checking option length. It should have 10 bytes long payload.
    ASSERT_EQ(10, opt->getData().size());

    // The second option should be the one configured on the server,
    // rather than the one injected by the relay.
    opt = client.config_.findOption(120);
    ASSERT_TRUE(opt);
    // It should have the size of 1.
    ASSERT_EQ(1, opt->getData().size());
}

// Test checks if pkt6-advertise-received is bumped up correctly.
// Note that in properly configured network the server never receives Advertise
// messages.
TEST_F(Dhcpv6SrvTest, receiveAdvertiseStat) {
    testReceiveStats(DHCPV6_ADVERTISE, "pkt6-advertise-received");
}

// Test checks if pkt6-reply-received is bumped up correctly.
// Note that in properly configured network the server never receives Reply
// messages.
TEST_F(Dhcpv6SrvTest, receiveReplyStat) {
    testReceiveStats(DHCPV6_ADVERTISE, "pkt6-advertise-received");
}

// Test checks if pkt6-unknown-received is bumped up correctly.
TEST_F(Dhcpv6SrvTest, receiveUnknownStat) {
    testReceiveStats(123, "pkt6-unknown-received");
}

// Test checks if pkt6-renew-received is bumped up correctly.
TEST_F(Dhcpv6SrvTest, receiveRenewStat) {
    testReceiveStats(DHCPV6_RENEW, "pkt6-renew-received");
}

// Test checks if pkt6-rebind-received is bumped up correctly.
TEST_F(Dhcpv6SrvTest, receiveRebindStat) {
    testReceiveStats(DHCPV6_REBIND, "pkt6-rebind-received");
}

// Test checks if pkt6-release-received is bumped up correctly.
TEST_F(Dhcpv6SrvTest, receiveReleaseStat) {
    testReceiveStats(DHCPV6_RELEASE, "pkt6-release-received");
}

// Test checks if pkt6-decline-received is bumped up correctly.
TEST_F(Dhcpv6SrvTest, receiveDeclineStat) {
    testReceiveStats(DHCPV6_DECLINE, "pkt6-decline-received");
}

// Test checks if reception of a malformed packet increases pkt-parse-failed
// and pkt6-receive-drop
TEST_F(Dhcpv6SrvTest, receiveParseFailedStat) {
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    NakedDhcpv6Srv srv(0);

    // Let's get a simple SOLICIT...
    Pkt6Ptr pkt = PktCaptures::captureSimpleSolicit();

    // And pretend it's packet is only 3 bytes long.
    pkt->data_.resize(3);

    // Check that those statistics are not set before the test
    ObservationPtr pkt6_rcvd = mgr.getObservation("pkt6-received");
    ObservationPtr parse_fail = mgr.getObservation("pkt6-parse-failed");
    ObservationPtr recv_drop = mgr.getObservation("pkt6-receive-drop");
    EXPECT_FALSE(pkt6_rcvd);
    EXPECT_FALSE(parse_fail);
    EXPECT_FALSE(recv_drop);

    // Simulate that we have received that traffic
    srv.fakeReceive(pkt);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    srv.run();

    // All expected statstics must be present.
    pkt6_rcvd = mgr.getObservation("pkt6-received");
    parse_fail = mgr.getObservation("pkt6-parse-failed");
    recv_drop = mgr.getObservation("pkt6-receive-drop");
    ASSERT_TRUE(pkt6_rcvd);
    ASSERT_TRUE(parse_fail);
    ASSERT_TRUE(recv_drop);

    // They also must have expected values.
    EXPECT_EQ(1, pkt6_rcvd->getInteger().first);
    EXPECT_EQ(1, parse_fail->getInteger().first);
    EXPECT_EQ(1, recv_drop->getInteger().first);
}

/// @todo: Add more negative tests for processX(), e.g. extend sanityCheck() test
/// to call processX() methods.


}   // end of anonymous namespace
