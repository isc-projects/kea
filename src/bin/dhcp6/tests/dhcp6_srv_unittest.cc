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

#include <asiolink/io_address.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_string.h>
#include <dhcp/iface_mgr.h>
#include <dhcp6/config_parser.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <util/buffer.h>
#include <util/range_utilities.h>
#include <hooks/server_hooks.h>

#include <dhcp6/tests/dhcp6_test_utils.h>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::test;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::util;
using namespace isc::hooks;
using namespace std;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {

// This is a test fixture class for testing the processing of the DHCPv6 Client
// FQDN Option.
class FqdnDhcpv6SrvTest : public Dhcpv6SrvTest {
public:
    // Constructor
    FqdnDhcpv6SrvTest()
        : Dhcpv6SrvTest() {
        // generateClientId assigns DUID to duid_.
        generateClientId();
        lease_.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                                duid_, 1234, 501, 502, 503,
                                504, 1, 0));

    }

    // Destructor
    virtual ~FqdnDhcpv6SrvTest() {
    }

    // Construct the DHCPv6 Client FQDN Option using flags and domain-name.
    Option6ClientFqdnPtr
    createClientFqdn(const uint8_t flags,
                     const std::string& fqdn_name,
                     const Option6ClientFqdn::DomainNameType fqdn_type) {
        return (Option6ClientFqdnPtr(new Option6ClientFqdn(flags,
                                                           fqdn_name,
                                                           fqdn_type)));
    }

    // Create a message holding DHCPv6 Client FQDN Option.
    Pkt6Ptr generatePktWithFqdn(uint8_t msg_type,
                                const uint8_t fqdn_flags,
                                const std::string& fqdn_domain_name,
                                const Option6ClientFqdn::DomainNameType
                                fqdn_type,
                                const bool include_oro,
                                OptionPtr srvid = OptionPtr()) {
        Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(msg_type, 1234));
        pkt->setRemoteAddr(IOAddress("fe80::abcd"));
        Option6IAPtr ia = generateIA(D6O_IA_NA, 234, 1500, 3000);

        if (msg_type != DHCPV6_REPLY) {
            IOAddress hint("2001:db8:1:1::dead:beef");
            OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
            ia->addOption(hint_opt);
            pkt->addOption(ia);
        }

        OptionPtr clientid = generateClientId();
        pkt->addOption(clientid);
        if (srvid && (msg_type != DHCPV6_SOLICIT)) {
            pkt->addOption(srvid);
        }

        pkt->addOption(createClientFqdn(fqdn_flags, fqdn_domain_name,
                                        fqdn_type));

        if (include_oro) {
            OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6,
                                                           D6O_ORO));
            oro->addValue(D6O_CLIENT_FQDN);
            pkt->addOption(oro);
        }

        return (pkt);
    }

    // Creates instance of the DHCPv6 message with client id and server id.
    Pkt6Ptr generateMessageWithIds(const uint8_t msg_type,
                                   NakedDhcpv6Srv& srv) {
        Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(msg_type, 1234));
        // Generate client-id.
        OptionPtr opt_clientid = generateClientId();
        pkt->addOption(opt_clientid);

        if (msg_type != DHCPV6_SOLICIT) {
            // Generate server-id.
            pkt->addOption(srv.getServerID());
        }

        return (pkt);
    }

    // Returns an instance of the option carrying FQDN.
    Option6ClientFqdnPtr getClientFqdnOption(const Pkt6Ptr& pkt) {
        return (boost::dynamic_pointer_cast<Option6ClientFqdn>
                (pkt->getOption(D6O_CLIENT_FQDN)));
    }

    // Adds IA option to the message. Option holds an address.
    void addIA(const uint32_t iaid, const IOAddress& addr, Pkt6Ptr& pkt) {
        Option6IAPtr opt_ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);
        Option6IAAddrPtr opt_iaaddr(new Option6IAAddr(D6O_IAADDR, addr,
                                                      300, 500));
        opt_ia->addOption(opt_iaaddr);
        pkt->addOption(opt_ia);
    }

    // Adds IA option to the message. Option holds status code.
    void addIA(const uint32_t iaid, const uint16_t status_code, Pkt6Ptr& pkt) {
        Option6IAPtr opt_ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);
        addStatusCode(status_code, "", opt_ia);
        pkt->addOption(opt_ia);
    }

    // Creates status code with the specified code and message.
    OptionCustomPtr createStatusCode(const uint16_t code,
                                     const std::string& msg) {
        OptionDefinition def("status-code", D6O_STATUS_CODE, "record");
        def.addRecordField("uint16");
        def.addRecordField("string");
        OptionCustomPtr opt_status(new OptionCustom(def, Option::V6));
        opt_status->writeInteger(code);
        if (!msg.empty()) {
            opt_status->writeString(msg, 1);
        }
        return (opt_status);
    }

    // Adds Status Code option to the IA.
    void addStatusCode(const uint16_t code, const std::string& msg,
                       Option6IAPtr& opt_ia) {
        opt_ia->addOption(createStatusCode(code, msg));
    }

    // Test processing of the DHCPv6 Client FQDN Option.
    void testFqdn(const uint16_t msg_type,
                  const bool use_oro,
                  const uint8_t in_flags,
                  const std::string& in_domain_name,
                  const Option6ClientFqdn::DomainNameType in_domain_type,
                  const uint8_t exp_flags,
                  const std::string& exp_domain_name) {
        NakedDhcpv6Srv srv(0);
        Pkt6Ptr question = generatePktWithFqdn(msg_type,
                                               in_flags,
                                               in_domain_name,
                                               in_domain_type,
                                               use_oro);
        ASSERT_TRUE(getClientFqdnOption(question));

        Option6ClientFqdnPtr answ_fqdn;
        ASSERT_NO_THROW(answ_fqdn = srv.processClientFqdn(question));
        ASSERT_TRUE(answ_fqdn);

        const bool flag_n = (exp_flags & Option6ClientFqdn::FLAG_N) != 0;
        const bool flag_s = (exp_flags & Option6ClientFqdn::FLAG_S) != 0;
        const bool flag_o = (exp_flags & Option6ClientFqdn::FLAG_O) != 0;

        EXPECT_EQ(flag_n, answ_fqdn->getFlag(Option6ClientFqdn::FLAG_N));
        EXPECT_EQ(flag_s, answ_fqdn->getFlag(Option6ClientFqdn::FLAG_S));
        EXPECT_EQ(flag_o, answ_fqdn->getFlag(Option6ClientFqdn::FLAG_O));

        EXPECT_EQ(exp_domain_name, answ_fqdn->getDomainName());
        EXPECT_EQ(Option6ClientFqdn::FULL, answ_fqdn->getDomainNameType());
    }

    // Tests that the client message holding an FQDN is processed and the
    // lease is acquired.
    void testProcessMessage(const uint8_t msg_type,
                            const std::string& hostname,
                            NakedDhcpv6Srv& srv) {
        // Create a message of a specified type, add server id and
        // FQDN option.
        OptionPtr srvid = srv.getServerID();
        Pkt6Ptr req = generatePktWithFqdn(msg_type, Option6ClientFqdn::FLAG_S,
                                          hostname,
                                          Option6ClientFqdn::FULL,
                                          true, srvid);

        // For different client's message types we have to invoke different
        // functions to generate response.
        Pkt6Ptr reply;
        if (msg_type == DHCPV6_SOLICIT) {
            ASSERT_NO_THROW(reply = srv.processSolicit(req));

        } else if (msg_type == DHCPV6_REQUEST) {
            ASSERT_NO_THROW(reply = srv.processRequest(req));

        } else if (msg_type == DHCPV6_RENEW) {
            ASSERT_NO_THROW(reply = srv.processRequest(req));

        } else if (msg_type == DHCPV6_RELEASE) {
            // For Release no lease will be acquired so we have to leave
            // function here.
            ASSERT_NO_THROW(reply = srv.processRelease(req));
            return;
        } else {
            // We are not interested in testing other message types.
            return;
        }

        // For Solicit, we will get different message type obviously.
        if (msg_type == DHCPV6_SOLICIT) {
            checkResponse(reply, DHCPV6_ADVERTISE, 1234);

        } else {
            checkResponse(reply, DHCPV6_REPLY, 1234);
        }

        // Check verify that IA_NA is correct.
        Option6IAAddrPtr addr =
            checkIA_NA(reply, 234, subnet_->getT1(), subnet_->getT2());
        ASSERT_TRUE(addr);

        // Check that we have got the address we requested.
        checkIAAddr(addr, IOAddress("2001:db8:1:1::dead:beef"),
                    Lease::TYPE_NA);

        if (msg_type != DHCPV6_SOLICIT) {
            // Check that the lease exists.
            Lease6Ptr lease =
                checkLease(duid_, reply->getOption(D6O_IA_NA), addr);
            ASSERT_TRUE(lease);
        }
    }

    // Verify that NameChangeRequest holds valid values.
    void verifyNameChangeRequest(NakedDhcpv6Srv& srv,
                                 const isc::dhcp_ddns::NameChangeType type,
                                 const bool reverse, const bool forward,
                                 const std::string& addr,
                                 const std::string& dhcid,
                                 const uint16_t expires,
                                 const uint16_t len) {
        NameChangeRequest ncr = srv.name_change_reqs_.front();
        EXPECT_EQ(type, ncr.getChangeType());
        EXPECT_EQ(forward, ncr.isForwardChange());
        EXPECT_EQ(reverse, ncr.isReverseChange());
        EXPECT_EQ(addr, ncr.getIpAddress());
        EXPECT_EQ(dhcid, ncr.getDhcid().toStr());
        EXPECT_EQ(expires, ncr.getLeaseExpiresOn());
        EXPECT_EQ(len, ncr.getLeaseLength());
        EXPECT_EQ(isc::dhcp_ddns::ST_NEW, ncr.getStatus());
        srv.name_change_reqs_.pop();
    }

    // Holds a lease used by a test.
    Lease6Ptr lease_;

};

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
    checkNakResponse (reply, DHCPV6_ADVERTISE, 1234, STATUS_NoAddrsAvail);
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
    checkNakResponse (reply, DHCPV6_REPLY, 1234, STATUS_NoAddrsAvail);
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
    checkNakResponse (reply, DHCPV6_REPLY, 1234, STATUS_NoBinding);
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
    checkNakResponse (reply, DHCPV6_REPLY, 1234, STATUS_NoBinding);
}


// Test verifies that the Dhcpv6_srv class can be instantiated. It checks a mode
// without open sockets and with sockets opened on a high port (to not require
// root privileges).
TEST_F(Dhcpv6SrvTest, basic) {
    // srv has stubbed interface detection. It will read
    // interfaces.txt instead. It will pretend to have detected
    // fe80::1234 link-local address on eth0 interface. Obviously
    // an attempt to bind this socket will fail.
    boost::scoped_ptr<Dhcpv6Srv> srv;

    ASSERT_NO_THROW( {
        // Skip opening any sockets
        srv.reset(new Dhcpv6Srv(0));
    });
    srv.reset();
    ASSERT_NO_THROW({
        // open an unpriviledged port
        srv.reset(new Dhcpv6Srv(DHCP6_SERVER_PORT + 10000));
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
    ConstElementPtr x;
    string config = "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/64\" ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
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

    ElementPtr json = Element::fromJSON(config);

    NakedDhcpv6Srv srv(0);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);

    ASSERT_EQ(0, rcode_);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr adv = srv.processSolicit(sol);

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
    adv = srv.processSolicit(sol);
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
    EXPECT_NE(addr1->getAddress().toText(), addr2->getAddress().toText());
    EXPECT_NE(addr2->getAddress().toText(), addr3->getAddress().toText());
    EXPECT_NE(addr3->getAddress().toText(), addr1->getAddress().toText());
    cout << "Offered address to client1=" << addr1->getAddress().toText() << endl;
    cout << "Offered address to client2=" << addr2->getAddress().toText() << endl;
    cout << "Offered address to client3=" << addr3->getAddress().toText() << endl;
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
    EXPECT_NE(addr1->getAddress().toText(), addr2->getAddress().toText());
    EXPECT_NE(addr2->getAddress().toText(), addr3->getAddress().toText());
    EXPECT_NE(addr3->getAddress().toText(), addr1->getAddress().toText());
    cout << "Assigned address to client1=" << addr1->getAddress().toText() << endl;
    cout << "Assigned address to client2=" << addr2->getAddress().toText() << endl;
    cout << "Assigned address to client3=" << addr3->getAddress().toText() << endl;
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
TEST_F(Dhcpv6SrvTest, RenewReject) {
    testRenewReject(Lease::TYPE_NA, IOAddress("2001:db8:1:1::dead"));
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

// This test verifies if the status code option is generated properly.
TEST_F(Dhcpv6SrvTest, StatusCode) {
    NakedDhcpv6Srv srv(0);

    // a dummy content for client-id
    uint8_t expected[] = {
        0x0, 0xD, // option code = 13
        0x0, 0x7, // option length = 7
        0x0, 0x3, // status code = 3
        0x41, 0x42, 0x43, 0x44, 0x45 // string value ABCDE
    };
    // Create the option.
    OptionPtr status = srv.createStatusCode(3, "ABCDE");
    // Allocate an output buffer. We will store the option
    // in wire format here.
    OutputBuffer buf(sizeof(expected));
    // Prepare the wire format.
    ASSERT_NO_THROW(status->pack(buf));
    // Check that the option buffer has valid length (option header + data).
    ASSERT_EQ(sizeof(expected), buf.getLength());
    // Verify the contents of the option.
    EXPECT_EQ(0, memcmp(expected, buf.getData(), sizeof(expected)));
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

// This test verifies if selectSubnet() selects proper subnet for a given
// source address.
TEST_F(Dhcpv6SrvTest, selectSubnetAddr) {
    NakedDhcpv6Srv srv(0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    // CASE 1: We have only one subnet defined and we received local traffic.
    // The only available subnet should be selected
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1); // just a single subnet

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    pkt->setRemoteAddr(IOAddress("fe80::abcd"));

    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet1);

    // CASE 2: We have only one subnet defined and we received relayed traffic.
    // We should NOT select it.

    // Identical steps as in case 1, but repeated for clarity
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1); // just a single subnet
    pkt->setRemoteAddr(IOAddress("2001:db8:abcd::2345"));
    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 3: We have three subnets defined and we received local traffic.
    // Nothing should be selected.
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);
    pkt->setRemoteAddr(IOAddress("fe80::abcd"));
    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 4: We have three subnets defined and we received relayed traffic
    // that came out of subnet 2. We should select subnet2 then
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);
    pkt->setRemoteAddr(IOAddress("2001:db8:2::baca"));
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 5: We have three subnets defined and we received relayed traffic
    // that came out of undefined subnet. We should select nothing
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);
    pkt->setRemoteAddr(IOAddress("2001:db8:4::baca"));
    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

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
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1); // just a single subnet

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    pkt->setIface("eth0");

    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet1);

    // CASE 2: We have only one subnet defined and it is available via eth0.
    // Packet came from eth1. We should not select it
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1); // just a single subnet

    pkt->setIface("eth1");

    selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 3: We have only 3 subnets defined, one over eth0, one remote and
    // one over wifi1.
    // Packet came from eth1. We should not select it
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);

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
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1); // just a single subnet

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    pkt->relay_info_.push_back(relay);

    Subnet6Ptr selected = srv.selectSubnet(pkt);
    EXPECT_FALSE(selected);

    // CASE 2: We have three subnets defined and we received relayed traffic.
    // Nothing should be selected.
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 3: We have three subnets defined and we received relayed traffic
    // that came out of subnet 2. We should select subnet2 then
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);

    // Source of the packet should have no meaning. Selection is based
    // on linkaddr field in the relay
    pkt->setRemoteAddr(IOAddress("2001:db8:1::baca"));
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 4: We have three subnets defined and we received relayed traffic
    // that came out of undefined subnet. We should select nothing
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);
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
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1); // just a single subnet

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
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet2); // just a single subnet
    selected = srv.selectSubnet(pkt);
    EXPECT_EQ(selected, subnet2);

    // CASE 3: We have only 3 subnets defined: one remote for interface-id "relay1",
    // one remote for interface-id "relay2" and third local
    // packet comes with interface-id "relay2". We should select subnet2
    CfgMgr::instance().deleteSubnets6();
    CfgMgr::instance().addSubnet6(subnet1);
    CfgMgr::instance().addSubnet6(subnet2);
    CfgMgr::instance().addSubnet6(subnet3);

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

// A set of tests verifying server's behaviour when it receives the DHCPv6
// Client Fqdn Option.
// @todo: Extend these tests once appropriate configuration parameters are
// implemented (ticket #3034).

// Test server's response when client requests that server performs AAAA update.
TEST_F(FqdnDhcpv6SrvTest, serverAAAAUpdate) {
    testFqdn(DHCPV6_SOLICIT, true, Option6ClientFqdn::FLAG_S,
             "myhost.example.com",
             Option6ClientFqdn::FULL, Option6ClientFqdn::FLAG_S,
             "myhost.example.com.");
}

// Test server's response when client provides partial domain-name and requests
// that server performs AAAA update.
TEST_F(FqdnDhcpv6SrvTest, serverAAAAUpdatePartialName) {
    testFqdn(DHCPV6_SOLICIT, true, Option6ClientFqdn::FLAG_S, "myhost",
             Option6ClientFqdn::PARTIAL, Option6ClientFqdn::FLAG_S,
             "myhost.example.com.");
}

// Test server's response when client provides empty domain-name and requests
// that server performs AAAA update.
TEST_F(FqdnDhcpv6SrvTest, serverAAAAUpdateNoName) {
    testFqdn(DHCPV6_SOLICIT, true, Option6ClientFqdn::FLAG_S, "",
             Option6ClientFqdn::PARTIAL, Option6ClientFqdn::FLAG_S,
             "myhost.example.com.");
}

// Test server's response when client requests no DNS update.
TEST_F(FqdnDhcpv6SrvTest, noUpdate) {
    testFqdn(DHCPV6_SOLICIT, true, Option6ClientFqdn::FLAG_N,
             "myhost.example.com",
             Option6ClientFqdn::FULL, Option6ClientFqdn::FLAG_N,
             "myhost.example.com.");
}

// Test server's response when client requests that server delegates the AAAA
// update to the client and this delegation is not allowed.
TEST_F(FqdnDhcpv6SrvTest, clientAAAAUpdateNotAllowed) {
    testFqdn(DHCPV6_SOLICIT, true, 0, "myhost.example.com.",
             Option6ClientFqdn::FULL,
             Option6ClientFqdn::FLAG_S | Option6ClientFqdn::FLAG_O,
             "myhost.example.com.");
}

// Test that exception is thrown if supplied NULL answer packet when
// creating NameChangeRequests.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoAnswer) {
    NakedDhcpv6Srv srv(0);

    Pkt6Ptr answer;
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "myhost.example.com",
                                                 Option6ClientFqdn::FULL);
    EXPECT_THROW(srv.createNameChangeRequests(answer, fqdn),
                 isc::Unexpected);

}

// Test that exception is thrown if supplied answer from the server
// contains no DUID when creating NameChangeRequests.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoDUID) {
    NakedDhcpv6Srv srv(0);

    Pkt6Ptr answer = Pkt6Ptr(new Pkt6(DHCPV6_REPLY, 1234));
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "myhost.example.com",
                                                 Option6ClientFqdn::FULL);

    EXPECT_THROW(srv.createNameChangeRequests(answer, fqdn),
                 isc::Unexpected);

}

// Test no NameChangeRequests are added if FQDN option is NULL.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoFQDN) {
    NakedDhcpv6Srv srv(0);

    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY, srv);

    // Pass NULL FQDN option. No NameChangeRequests should be created.
    Option6ClientFqdnPtr fqdn;
    ASSERT_NO_THROW(srv.createNameChangeRequests(answer, fqdn));

    // There should be no new NameChangeRequests.
    EXPECT_TRUE(srv.name_change_reqs_.empty());
}

// Test that NameChangeRequests are not generated if an answer message
// contains no addresses.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoAddr) {
    NakedDhcpv6Srv srv(0);

    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY, srv);

    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "myhost.example.com",
                                                 Option6ClientFqdn::FULL);

    ASSERT_NO_THROW(srv.createNameChangeRequests(answer, fqdn));

    // We didn't add any IAs, so there should be no NameChangeRequests in th
    // queue.
    ASSERT_TRUE(srv.name_change_reqs_.empty());
}

// Test that a number of NameChangeRequests is created as a result of
// processing the answer message which holds 3 IAs and when FQDN is
// specified.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequests) {
    NakedDhcpv6Srv srv(0);

    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY, srv);

    // Create three IAs, each having different address.
    addIA(1234, IOAddress("2001:db8:1::1"), answer);
    addIA(2345, IOAddress("2001:db8:1::2"), answer);
    addIA(3456, IOAddress("2001:db8:1::3"), answer);

    // Use domain name in upper case. It should be converted to lower-case
    // before DHCID is calculated. So, we should get the same result as if
    // we typed domain name in lower-case.
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "MYHOST.EXAMPLE.COM",
                                                 Option6ClientFqdn::FULL);

    // Create NameChangeRequests. Since we have added 3 IAs, it should
    // result in generation of 3 distinct NameChangeRequests.
    ASSERT_NO_THROW(srv.createNameChangeRequests(answer, fqdn));
    ASSERT_EQ(3, srv.name_change_reqs_.size());

    // Verify that NameChangeRequests are correct. Each call to the
    // verifyNameChangeRequest will pop verified request from the queue.

    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1::1",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 500);

    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1::2",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 500);

    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1::3",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 500);

}

// Test creation of the NameChangeRequest to remove both forward and reverse
// mapping for the given lease.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestFwdRev) {
    NakedDhcpv6Srv srv(0);

    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    // Part of the domain name is in upper case, to test that it gets converted
    // to lower case before DHCID is computed. So, we should get the same DHCID
    // as if we typed domain-name in lower case.
    lease_->hostname_ = "MYHOST.example.com.";

    ASSERT_NO_THROW(srv.createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(1, srv.name_change_reqs_.size());

    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1::1",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 502);

}

// Test creation of the NameChangeRequest to remove reverse mapping for the
// given lease.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestRev) {
    NakedDhcpv6Srv srv(0);

    lease_->fqdn_fwd_ = false;
    lease_->fqdn_rev_ = true;
    lease_->hostname_ = "myhost.example.com.";

    ASSERT_NO_THROW(srv.createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(1, srv.name_change_reqs_.size());

    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_REMOVE, true, false,
                            "2001:db8:1::1",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 502);

}

// Test that NameChangeRequest to remove DNS records is not generated when
// neither forward nor reverse DNS update has been performed for a lease.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestNoUpdate) {
    NakedDhcpv6Srv srv(0);

    lease_->fqdn_fwd_ = false;
    lease_->fqdn_rev_ = false;

    ASSERT_NO_THROW(srv.createRemovalNameChangeRequest(lease_));

    EXPECT_TRUE(srv.name_change_reqs_.empty());

}

// Test that NameChangeRequest is not generated if the hostname hasn't been
// specified for a lease for which forward and reverse mapping has been set.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestNoHostname) {
    NakedDhcpv6Srv srv(0);

    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    lease_->hostname_ = "";

    ASSERT_NO_THROW(srv.createRemovalNameChangeRequest(lease_));

    EXPECT_TRUE(srv.name_change_reqs_.empty());

}

// Test that NameChangeRequest is not generated if the invalid hostname has
// been specified for a lease for which forward and reverse mapping has been
// set.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestWrongHostname) {
    NakedDhcpv6Srv srv(0);

    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    lease_->hostname_ = "myhost..example.com.";

    ASSERT_NO_THROW(srv.createRemovalNameChangeRequest(lease_));

    EXPECT_TRUE(srv.name_change_reqs_.empty());

}

// Test that Advertise message generated in a response to the Solicit will
// not result in generation if the NameChangeRequests.
TEST_F(FqdnDhcpv6SrvTest, processSolicit) {
    NakedDhcpv6Srv srv(0);

    // Create a Solicit message with FQDN option and generate server's
    // response using processSolicit function.
    testProcessMessage(DHCPV6_SOLICIT, "myhost.example.com", srv);
    EXPECT_TRUE(srv.name_change_reqs_.empty());
}

// Test that client may send two requests, each carrying FQDN option with
// a different domain-name. Server should use existing lease for the second
// request but modify the DNS entries for the lease according to the contents
// of the FQDN sent in the second request.
TEST_F(FqdnDhcpv6SrvTest, processTwoRequests) {
    NakedDhcpv6Srv srv(0);

    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com", srv);
    ASSERT_EQ(1, srv.name_change_reqs_.size());
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // Client may send another request message with a new domain-name. In this
    // case the same lease will be returned. The existing DNS entry needs to
    // be replaced with a new one. Server should determine that the different
    // FQDN has been already added to the DNS. As a result, the old DNS
    // entries should be removed and the entries for the new domain-name
    // should be added. Therefore, we expect two NameChangeRequests. One to
    // remove the existing entries, one to add new entries.
    testProcessMessage(DHCPV6_REQUEST, "otherhost.example.com", srv);
    ASSERT_EQ(2, srv.name_change_reqs_.size());
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201D422AA463306223D269B6CB7AFE7AAD265FC"
                            "EA97F93623019B2E0D14E5323D5A",
                            0, 4000);

}

// Test that client may send Request followed by the Renew, both holding
// FQDN options, but each option holding different domain-name. The Renew
// should result in generation of the two NameChangeRequests, one to remove
// DNS entry added previously when Request was processed, another one to
// add a new entry for the FQDN held in the Renew.
TEST_F(FqdnDhcpv6SrvTest, processRequestRenew) {
    NakedDhcpv6Srv srv(0);

    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com", srv);
    ASSERT_EQ(1, srv.name_change_reqs_.size());
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // Client may send Renew message with a new domain-name. In this
    // case the same lease will be returned. The existing DNS entry needs to
    // be replaced with a new one. Server should determine that the different
    // FQDN has been already added to the DNS. As a result, the old DNS
    // entries should be removed and the entries for the new domain-name
    // should be added. Therefore, we expect two NameChangeRequests. One to
    // remove the existing entries, one to add new entries.
    testProcessMessage(DHCPV6_RENEW, "otherhost.example.com", srv);
    ASSERT_EQ(2, srv.name_change_reqs_.size());
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201D422AA463306223D269B6CB7AFE7AAD265FC"
                            "EA97F93623019B2E0D14E5323D5A",
                            0, 4000);

}

TEST_F(FqdnDhcpv6SrvTest, processRequestRelease) {
    NakedDhcpv6Srv srv(0);

    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com", srv);
    ASSERT_EQ(1, srv.name_change_reqs_.size());
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // Client may send Release message. In this case the lease should be
    // removed and all existing DNS entries for this lease should be
    // also removed. Therefore, we expect that single NameChangeRequest to
    // remove DNS entries is generated.
    testProcessMessage(DHCPV6_RELEASE, "otherhost.example.com", srv);
    ASSERT_EQ(1, srv.name_change_reqs_.size());
    verifyNameChangeRequest(srv, isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

}

// Checks if server responses are sent to the proper port.
TEST_F(Dhcpv6SrvTest, portsDirectTraffic) {

    NakedDhcpv6Srv srv(0);

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = captureSimpleSolicit();

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
    Pkt6Ptr sol = captureRelayedSolicit();

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
    Pkt6Ptr sol = captureDocsisRelayedSolicit();

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

    NakedDhcpv6Srv srv(0);

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = captureDocsisRelayedSolicit();
    EXPECT_NO_THROW(sol->unpack());

    // Check if the packet contain
    OptionPtr opt = sol->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);

    boost::shared_ptr<OptionVendor> vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    EXPECT_TRUE(vendor->getOption(1));
    EXPECT_TRUE(vendor->getOption(36));
    EXPECT_TRUE(vendor->getOption(35));
    EXPECT_TRUE(vendor->getOption(2));
    EXPECT_TRUE(vendor->getOption(3));
    EXPECT_TRUE(vendor->getOption(4));
    EXPECT_TRUE(vendor->getOption(5));
    EXPECT_TRUE(vendor->getOption(6));
    EXPECT_TRUE(vendor->getOption(7));
    EXPECT_TRUE(vendor->getOption(8));
    EXPECT_TRUE(vendor->getOption(9));
    EXPECT_TRUE(vendor->getOption(10));
    EXPECT_TRUE(vendor->getOption(15));

    EXPECT_FALSE(vendor->getOption(20));
    EXPECT_FALSE(vendor->getOption(11));
    EXPECT_FALSE(vendor->getOption(17));
}

// Checks if server is able to parse incoming docsis option and extract suboption 1 (docsis ORO)
TEST_F(Dhcpv6SrvTest, docsisVendorORO) {

    NakedDhcpv6Srv srv(0);

    // Let's get a traffic capture from DOCSIS3.0 modem
    Pkt6Ptr sol = captureDocsisRelayedSolicit();
    EXPECT_NO_THROW(sol->unpack());

    // Check if the packet contain
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
    ConstElementPtr x;
    string config = "{ \"interfaces\": [ \"all\" ],"
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
        "    \"pool\": [ \"2001:db8:1::/64\" ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"renew-timer\": 1000, "
        "    \"rebind-timer\": 1000, "
        "    \"preferred-lifetime\": 3000,"
        "    \"valid-lifetime\": 4000,"
        "    \"interface-id\": \"\","
        "    \"interface\": \"\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    NakedDhcpv6Srv srv(0);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);

    ASSERT_EQ(0, rcode_);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr adv = srv.processSolicit(sol);

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
    adv = srv.processSolicit(sol);
    ASSERT_TRUE(adv);

    // Check if thre is vendor option response
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
    string config_prefix = "{ \"interfaces\": [ \"all\" ],"
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
        "    \"pool\": [ \"2001:db8:1::/64\" ],"
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
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(1, rcode_);

    // This should work (option definition present)
    EXPECT_NO_THROW(x = configureDhcp6Server(srv, json_valid));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
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
    CfgMgr& cfgmgr = CfgMgr::instance();
    ASSERT_NO_THROW(cfgmgr.addOptionDef(opt_def, "space-foobar"));
    ASSERT_NO_THROW(cfgmgr.addOptionDef(opt_def2, "space-foo"));
    ASSERT_NO_THROW(cfgmgr.addOptionDef(opt_def3, "space-bar"));

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


/// @todo: Add more negative tests for processX(), e.g. extend sanityCheck() test
/// to call processX() methods.

}   // end of anonymous namespace
