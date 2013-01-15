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

#include <asiolink/io_address.h>
#include <config/ccsession.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int_array.h>
#include <dhcp6/config_parser.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <util/buffer.h>
#include <util/range_utilities.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {

class NakedDhcpv6Srv: public Dhcpv6Srv {
    // "naked" Interface Manager, exposes internal members
public:
    NakedDhcpv6Srv(uint16_t port):Dhcpv6Srv(port) { }

    using Dhcpv6Srv::processSolicit;
    using Dhcpv6Srv::processRequest;
    using Dhcpv6Srv::processRenew;
    using Dhcpv6Srv::processRelease;
    using Dhcpv6Srv::createStatusCode;
    using Dhcpv6Srv::selectSubnet;
    using Dhcpv6Srv::sanityCheck;
};

class Dhcpv6SrvTest : public ::testing::Test {
public:
    // these are empty for now, but let's keep them around
    Dhcpv6SrvTest() : rcode_(-1) {
        subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 48, 1000,
                                         2000, 3000, 4000));
        pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:1::"), 64));
        subnet_->addPool(pool_);

        CfgMgr::instance().deleteSubnets6();
        CfgMgr::instance().addSubnet6(subnet_);
    }

    // Generate IA_NA option with specified parameters
    boost::shared_ptr<Option6IA> generateIA(uint32_t iaid, uint32_t t1, uint32_t t2) {
        boost::shared_ptr<Option6IA> ia =
            boost::shared_ptr<Option6IA>(new Option6IA(D6O_IA_NA, iaid));
        ia->setT1(t1);
        ia->setT2(t2);
        return (ia);
    }

    // Generate client-id option
    OptionPtr generateClientId(size_t duid_size = 32) {

        OptionBuffer clnt_duid(duid_size);
        for (int i = 0; i < duid_size; i++) {
            clnt_duid[i] = 100 + i;
        }

        duid_ = DuidPtr(new DUID(clnt_duid));

        return (OptionPtr(new Option(Option::V6, D6O_CLIENTID,
                                     clnt_duid.begin(),
                                     clnt_duid.begin() + duid_size)));
    }

    // Checks if server response (ADVERTISE or REPLY) includes proper server-id.
    void checkServerId(const Pkt6Ptr& rsp, const OptionPtr& expected_srvid) {
        // check that server included its server-id
        OptionPtr tmp = rsp->getOption(D6O_SERVERID);
        EXPECT_EQ(tmp->getType(), expected_srvid->getType() );
        ASSERT_EQ(tmp->len(), expected_srvid->len() );
        EXPECT_TRUE(tmp->getData() == expected_srvid->getData());
    }

    // Checks if server response (ADVERTISE or REPLY) includes proper client-id.
    void checkClientId(const Pkt6Ptr& rsp, const OptionPtr& expected_clientid) {
        // check that server included our own client-id
        OptionPtr tmp = rsp->getOption(D6O_CLIENTID);
        ASSERT_TRUE(tmp);
        EXPECT_EQ(expected_clientid->getType(), tmp->getType());
        ASSERT_EQ(expected_clientid->len(), tmp->len());

        // check that returned client-id is valid
        EXPECT_TRUE(expected_clientid->getData() == tmp->getData());
    }

    // Checks that server response (ADVERTISE or REPLY) contains proper IA_NA option
    // It returns IAADDR option for each chaining with checkIAAddr method.
    boost::shared_ptr<Option6IAAddr> checkIA_NA(const Pkt6Ptr& rsp, uint32_t expected_iaid,
                                         uint32_t expected_t1, uint32_t expected_t2) {
        OptionPtr tmp = rsp->getOption(D6O_IA_NA);
        // Can't use ASSERT_TRUE() in method that returns something
        if (!tmp) {
            ADD_FAILURE() << "IA_NA option not present in response";
            return (boost::shared_ptr<Option6IAAddr>());
        }

        boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
        EXPECT_EQ(expected_iaid, ia->getIAID() );
        EXPECT_EQ(expected_t1, ia->getT1());
        EXPECT_EQ(expected_t2, ia->getT2());

        tmp = ia->getOption(D6O_IAADDR);
        boost::shared_ptr<Option6IAAddr> addr = boost::dynamic_pointer_cast<Option6IAAddr>(tmp);
        return (addr);
    }

    // Checks that server rejected IA_NA, i.e. that it has no addresses and
    // that expected status code really appears there. In some limited cases
    // (reply to RELEASE) it may be used to verify positive case, where
    // IA_NA response is expected to not include address.
    //
    // Status code indicates type of error encountered (in theory it can also
    // indicate success, but servers typically don't send success status
    // as this is the default result and it saves bandwidth)
    void checkIA_NAStatusCode(const boost::shared_ptr<Option6IA>& ia,
                            uint16_t expected_status_code) {
        // Make sure there is no address assigned.
        EXPECT_FALSE(ia->getOption(D6O_IAADDR));

        // T1, T2 should be zeroed
        EXPECT_EQ(0, ia->getT1());
        EXPECT_EQ(0, ia->getT2());

        boost::shared_ptr<OptionCustom> status =
            boost::dynamic_pointer_cast<OptionCustom>(ia->getOption(D6O_STATUS_CODE));

        // It is ok to not include status success as this is the default behavior
        if (expected_status_code == STATUS_Success && !status) {
            return;
        }

        EXPECT_TRUE(status);

        if (status) {
            // We don't have dedicated class for status code, so let's just interpret
            // first 2 bytes as status. Remainder of the status code option content is
            // just a text explanation what went wrong.
            EXPECT_EQ(static_cast<uint16_t>(expected_status_code),
                      status->readInteger<uint16_t>(0));
        }
    }


    void checkMsgStatusCode(const Pkt6Ptr& msg, uint16_t expected_status) {
        boost::shared_ptr<OptionCustom> status =
            boost::dynamic_pointer_cast<OptionCustom>(msg->getOption(D6O_STATUS_CODE));

        // It is ok to not include status success as this is the default behavior
        if (expected_status == STATUS_Success && !status) {
            return;
        }

        EXPECT_TRUE(status);
        if (status) {
            // We don't have dedicated class for status code, so let's just interpret
            // first 2 bytes as status. Remainder of the status code option content is
            // just a text explanation what went wrong.
            EXPECT_EQ(static_cast<uint16_t>(expected_status),
                      status->readInteger<uint16_t>(0));
        }
    }

    // Check that generated IAADDR option contains expected address.
    void checkIAAddr(const boost::shared_ptr<Option6IAAddr>& addr,
                     const IOAddress& expected_addr,
                     uint32_t expected_preferred, uint32_t expected_valid) {

        // Check that the assigned address is indeed from the configured pool.
        // Note that when comparing addresses, we compare the textual
        // representation. IOAddress does not support being streamed to
        // an ostream, which means it can't be used in EXPECT_EQ.
        EXPECT_TRUE(subnet_->inPool(addr->getAddress()));
        EXPECT_EQ(expected_addr.toText(), addr->getAddress().toText());
        EXPECT_EQ(addr->getPreferred(), subnet_->getPreferred());
        EXPECT_EQ(addr->getValid(), subnet_->getValid());
    }

    // Basic checks for generated response (message type and transaction-id).
    void checkResponse(const Pkt6Ptr& rsp, uint8_t expected_message_type,
                       uint32_t expected_transid) {
        ASSERT_TRUE(rsp);
        EXPECT_EQ(expected_message_type, rsp->getType());
        EXPECT_EQ(expected_transid, rsp->getTransid());
    }

    // Checks if the lease sent to client is present in the database
    Lease6Ptr checkLease(const DuidPtr& duid, const OptionPtr& ia_na,
                         boost::shared_ptr<Option6IAAddr> addr) {
        boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(ia_na);

        Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(addr->getAddress());
        if (!lease) {
            cout << "Lease for " << addr->getAddress().toText()
                 << " not found in the database backend.";
            return (Lease6Ptr());
        }

        EXPECT_EQ(addr->getAddress().toText(), lease->addr_.toText());
        EXPECT_TRUE(*lease->duid_ == *duid);
        EXPECT_EQ(ia->getIAID(), lease->iaid_);
        EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

        return (lease);
    }

    ~Dhcpv6SrvTest() {
        CfgMgr::instance().deleteSubnets6();
    };

    // A subnet used in most tests
    Subnet6Ptr subnet_;

    // A pool used in most tests
    Pool6Ptr pool_;

    // A DUID used in most tests (typically as client-id)
    DuidPtr duid_;

    int rcode_;
    ConstElementPtr comment_;
};

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
        srv.reset(new Dhcpv6Srv(0));
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
    string config = "{ \"interface\": [ \"all\" ],"
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
    sol->addOption(generateIA(234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    boost::shared_ptr<Pkt6> adv = srv.processSolicit(sol);

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
    sol->addOption(generateIA(234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv.processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    // check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr, addr->getAddress(), subnet_->getPreferred(), subnet_->getValid());

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
    boost::shared_ptr<Option6IA> ia = generateIA(234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    ASSERT_TRUE(subnet_->inPool(hint));
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

    // check that we've got the address we requested
    checkIAAddr(addr, hint, subnet_->getPreferred(), subnet_->getValid());

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
    boost::shared_ptr<Option6IA> ia = generateIA(234, 1500, 3000);
    IOAddress hint("2001:db8:1::cafe:babe");
    ASSERT_FALSE(subnet_->inPool(hint));
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

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr, addr->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    EXPECT_TRUE(subnet_->inPool(addr->getAddress()));

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

    sol1->addOption(generateIA(1, 1500, 3000));
    sol2->addOption(generateIA(2, 1500, 3000));
    sol3->addOption(generateIA(3, 1500, 3000));

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

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr1, addr1->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr2, addr2->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr3, addr3->getAddress(), subnet_->getPreferred(), subnet_->getValid());

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
    boost::shared_ptr<Option6IA> ia = generateIA(234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    ASSERT_TRUE(subnet_->inPool(hint));
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
    boost::shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());

    // check that we've got the address we requested
    checkIAAddr(addr, hint, subnet_->getPreferred(), subnet_->getValid());

    // check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    // check that the lease is really in the database
    Lease6Ptr l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr);
    EXPECT_TRUE(l);
    LeaseMgrFactory::instance().deleteLease(addr->getAddress());
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

    Pkt6Ptr req1 = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    Pkt6Ptr req2 = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 2345));
    Pkt6Ptr req3 = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 3456));

    req1->setRemoteAddr(IOAddress("fe80::abcd"));
    req2->setRemoteAddr(IOAddress("fe80::1223"));
    req3->setRemoteAddr(IOAddress("fe80::3467"));

    req1->addOption(generateIA(1, 1500, 3000));
    req2->addOption(generateIA(2, 1500, 3000));
    req3->addOption(generateIA(3, 1500, 3000));

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

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr1, addr1->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr2, addr2->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr3, addr3->getAddress(), subnet_->getPreferred(), subnet_->getValid());

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
// - returned REPLY message has IA that includes IAADDR
// - lease is actually renewed in LeaseMgr
TEST_F(Dhcpv6SrvTest, RenewBasic) {
    NakedDhcpv6Srv srv(0);

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->t1_, subnet_->getT1());
    EXPECT_NE(l->t2_, subnet_->getT2());
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(iaid, 1500, 3000);

    OptionPtr renewed_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(renewed_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt = checkIA_NA(reply, 234, subnet_->getT1(),
                                                           subnet_->getT2());

    // Check that we've got the address we requested
    checkIAAddr(addr_opt, addr, subnet_->getPreferred(), subnet_->getValid());

    // Check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt were really updated
    EXPECT_EQ(l->t1_, subnet_->getT1());
    EXPECT_EQ(l->t2_, subnet_->getT2());
    EXPECT_EQ(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_EQ(l->valid_lft_, subnet_->getValid());

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr_opt->getAddress()));
}

// This test verifies that incoming (invalid) RENEW can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA that includes STATUS-CODE
// - No lease in LeaseMgr
TEST_F(Dhcpv6SrvTest, RenewReject) {
    NakedDhcpv6Srv srv(0);

    const IOAddress addr("2001:db8:1:1::dead");
    const uint32_t transid = 1234;
    const uint32_t valid_iaid = 234;
    const uint32_t bogus_iaid = 456;

    // Quick sanity check that the address we're about to use is ok
    ASSERT_TRUE(subnet_->inPool(addr));

    // GenerateClientId() also sets duid_
    OptionPtr clientid = generateClientId();

    // Check that the lease is NOT in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_FALSE(l);

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, transid));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(bogus_iaid, 1500, 3000);

    OptionPtr renewed_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(renewed_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Case 1: No lease known to server

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, transid);
    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);

    // Check that there is no lease added
    l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_FALSE(l);

    // CASE 2: Lease is known and belongs to this client, but to a different IAID

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, duid_, valid_iaid,
                               501, 502, 503, 504, subnet_->getID(), 0));
    lease->cltt_ = 123; // Let's use it as an indicator that the lease
                        // was NOT updated.
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Pass it to the server and hope for a REPLY
    reply = srv.processRenew(req);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);

    // There is a iaid mis-match, so server should respond that there is
    // no such address to renew.

    // CASE 3: Lease belongs to a client with different client-id
    req->delOption(D6O_CLIENTID);
    ia = boost::dynamic_pointer_cast<Option6IA>(req->getOption(D6O_IA_NA));
    ia->setIAID(valid_iaid); // Now iaid in renew matches that in leasemgr
    req->addOption(generateClientId(13)); // generate different DUID
                                          // (with length 13)

    reply = srv.processRenew(req);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);

    lease = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_TRUE(lease);
    // Verify that the lease was not updated.
    EXPECT_EQ(123, lease->cltt_);

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

// This test verifies that incoming (positive) RELEASE can be handled properly,
// that a REPLY is generated, that the response has status code and that the
// lease is indeed removed from the database.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA that does not include an IAADDR
// - lease is actually removed from LeaseMgr
TEST_F(Dhcpv6SrvTest, ReleaseBasic) {
    NakedDhcpv6Srv srv(0);

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RELEASE
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    checkIA_NAStatusCode(ia, STATUS_Success);
    checkMsgStatusCode(reply, STATUS_Success);

    // There should be no address returned in RELEASE (see RFC3315, 18.2.6)
    EXPECT_FALSE(tmp->getOption(D6O_IAADDR));

    // Check DUIDs
    checkServerId(reply, srv.getServerID());
    checkClientId(reply, clientid);

    // Check that the lease is really gone in the database
    // get lease by address
    l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_FALSE(l);

    // get lease by subnetid/duid/iaid combination
    l = LeaseMgrFactory::instance().getLease6(*duid_, iaid, subnet_->getID());
    ASSERT_FALSE(l);
}

// This test verifies that incoming (invalid) RELEASE can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA that includes STATUS-CODE
// - No lease in LeaseMgr
TEST_F(Dhcpv6SrvTest, ReleaseReject) {

    NakedDhcpv6Srv srv(0);

    const IOAddress addr("2001:db8:1:1::dead");
    const uint32_t transid = 1234;
    const uint32_t valid_iaid = 234;
    const uint32_t bogus_iaid = 456;

    // Quick sanity check that the address we're about to use is ok
    ASSERT_TRUE(subnet_->inPool(addr));

    // GenerateClientId() also sets duid_
    OptionPtr clientid = generateClientId();

    // Check that the lease is NOT in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_FALSE(l);

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, transid));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(bogus_iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Case 1: No lease known to server
    SCOPED_TRACE("CASE 1: No lease known to server");

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, transid);
    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is not there
    l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_FALSE(l);

    // CASE 2: Lease is known and belongs to this client, but to a different IAID
    SCOPED_TRACE("CASE 2: Lease is known and belongs to this client, but to a different IAID");

    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, duid_, valid_iaid,
                               501, 502, 503, 504, subnet_->getID(), 0));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Pass it to the server and hope for a REPLY
    reply = srv.processRelease(req);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_TRUE(l);

    // CASE 3: Lease belongs to a client with different client-id
    SCOPED_TRACE("CASE 3: Lease belongs to a client with different client-id");

    req->delOption(D6O_CLIENTID);
    ia = boost::dynamic_pointer_cast<Option6IA>(req->getOption(D6O_IA_NA));
    ia->setIAID(valid_iaid); // Now iaid in renew matches that in leasemgr
    req->addOption(generateClientId(13)); // generate different DUID
                                          // (with length 13)

    reply = srv.processRelease(req);
    checkResponse(reply, DHCPV6_REPLY, transid);
    tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    // Check that IA_NA was returned and that there's an address included
    ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    checkIA_NAStatusCode(ia, STATUS_NoBinding);
    checkMsgStatusCode(reply, STATUS_NoBinding);

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease6(addr);
    ASSERT_TRUE(l);

    // Finally, let's cleanup the database
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
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

/// @todo: Add more negative tests for processX(), e.g. extend sanityCheck() test
/// to call processX() methods.

}   // end of anonymous namespace
