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


#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/cfgmgr.h>
#include <dhcp/option.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp6/dhcp6_srv.h>
#include <util/buffer.h>
#include <util/range_utilities.h>
#include <dhcp/lease_mgr.h>
#include <boost/scoped_ptr.hpp>
#include <config.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::asiolink;
using namespace boost;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {

class NakedDhcpv6Srv: public Dhcpv6Srv {
    // "naked" Interface Manager, exposes internal members
public:
    NakedDhcpv6Srv(uint16_t port):Dhcpv6Srv(port) { }

    using Dhcpv6Srv::processSolicit;
    using Dhcpv6Srv::processRequest;
    using Dhcpv6Srv::createStatusCode;
    using Dhcpv6Srv::selectSubnet;
};

class Dhcpv6SrvTest : public ::testing::Test {
public:
    // these are empty for now, but let's keep them around
    Dhcpv6SrvTest() {
        subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 48, 1000,
                                         2000, 3000, 4000));
        pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:1::"), 64));
        subnet_->addPool6(pool_);

        CfgMgr::instance().addSubnet6(subnet_);
    }

    // Generate IA_NA option with specified parameters
    shared_ptr<Option6IA> generateIA(uint32_t iaid, uint32_t t1, uint32_t t2) {
        shared_ptr<Option6IA> ia =
            shared_ptr<Option6IA>(new Option6IA(D6O_IA_NA, iaid));
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
    shared_ptr<Option6IAAddr> checkIA_NA(const Pkt6Ptr& rsp, uint32_t expected_iaid,
                                         uint32_t expected_t1, uint32_t expected_t2) {
        OptionPtr tmp = rsp->getOption(D6O_IA_NA);
        // Can't use ASSERT_TRUE() in method that returns something
        if (!tmp) {
            ADD_FAILURE() << "IA_NA option not present in response";
            return (shared_ptr<Option6IAAddr>());
        }

        shared_ptr<Option6IA> ia = dynamic_pointer_cast<Option6IA>(tmp);
        EXPECT_EQ(expected_iaid, ia->getIAID() );
        EXPECT_EQ(expected_t1, ia->getT1());
        EXPECT_EQ(expected_t2, ia->getT2());

        tmp = ia->getOption(D6O_IAADDR);
        shared_ptr<Option6IAAddr> addr = dynamic_pointer_cast<Option6IAAddr>(tmp);
        return (addr);
    }

    // Check that generated IAADDR option contains expected address.
    void checkIAAddr(shared_ptr<Option6IAAddr> addr, const IOAddress& expected_addr,
                     uint32_t expected_preferred, uint32_t expected_valid) {
        // Check that the assigned address is indeed from the configured pool
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
                         shared_ptr<Option6IAAddr> addr) {
        shared_ptr<Option6IA> ia = dynamic_pointer_cast<Option6IA>(ia_na);

        Lease6Ptr lease = LeaseMgr::instance().getLease6(addr->getAddress());
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
};

// Test verifies that the Dhcpv6_srv class can be instantiated. It checks a mode
// without open sockets and with sockets opened on a high port (to not require
// root privileges).
TEST_F(Dhcpv6SrvTest, basic) {
    // srv has stubbed interface detection. It will read
    // interfaces.txt instead. It will pretend to have detected
    // fe80::1234 link-local address on eth0 interface. Obviously
    // an attempt to bind this socket will fail.
    Dhcpv6Srv* srv = NULL;
    ASSERT_NO_THROW( {
        // Skip opening any sockets
        srv = new Dhcpv6Srv(0);
    });

    delete srv;

    ASSERT_NO_THROW( {
        // open an unpriviledged port
        srv = new Dhcpv6Srv(DHCP6_SERVER_PORT + 10000);
    });
    delete srv;
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
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));

    sol->setRemoteAddr(IOAddress("fe80::abcd"));

    sol->addOption(generateIA(234, 1500, 3000));

    OptionPtr clientid = generateClientId();

    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv->processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    // check that IA_NA was returned and that there's an address included
    shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr, addr->getAddress(), subnet_->getPreferred(), subnet_->getValid());

    // check DUIDs
    checkServerId(reply, srv->getServerID());
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
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

    // Let's create a SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    shared_ptr<Option6IA> ia = generateIA(234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    ASSERT_TRUE(subnet_->inPool(hint));
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    sol->addOption(ia);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv->processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // check that IA_NA was returned and that there's an address included
    shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());

    // check that we've got the address we requested
    checkIAAddr(addr, hint, subnet_->getPreferred(), subnet_->getValid());

    // check DUIDs
    checkServerId(reply, srv->getServerID());
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
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

    // Let's create a SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    shared_ptr<Option6IA> ia = generateIA(234, 1500, 3000);
    IOAddress hint("2001:db8:1::cafe:babe");
    ASSERT_FALSE(subnet_->inPool(hint));
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    sol->addOption(ia);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr reply = srv->processSolicit(sol);

    // check if we get response at all
    checkResponse(reply, DHCPV6_ADVERTISE, 1234);

    // check that IA_NA was returned and that there's an address included
    shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr, addr->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    EXPECT_TRUE(subnet_->inPool(addr->getAddress()));

    // check DUIDs
    checkServerId(reply, srv->getServerID());
    checkClientId(reply, clientid);
}

// This test checks that the server is offering different addresses to different
// clients in ADVERTISEs. Please note that ADVERTISE is not a guarantee that such
// and address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same advertise as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. ADVERTISE is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv6SrvTest, ManySolicits) {
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

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
    Pkt6Ptr reply1 = srv->processSolicit(sol1);
    Pkt6Ptr reply2 = srv->processSolicit(sol2);
    Pkt6Ptr reply3 = srv->processSolicit(sol3);

    // check if we get response at all
    checkResponse(reply1, DHCPV6_ADVERTISE, 1234);
    checkResponse(reply2, DHCPV6_ADVERTISE, 2345);
    checkResponse(reply3, DHCPV6_ADVERTISE, 3456);

    // check that IA_NA was returned and that there's an address included
    shared_ptr<Option6IAAddr> addr1 = checkIA_NA(reply1, 1, subnet_->getT1(),
                                                subnet_->getT2());
    shared_ptr<Option6IAAddr> addr2 = checkIA_NA(reply2, 2, subnet_->getT1(),
                                                subnet_->getT2());
    shared_ptr<Option6IAAddr> addr3 = checkIA_NA(reply3, 3, subnet_->getT1(),
                                                subnet_->getT2());

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr1, addr1->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr2, addr2->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr3, addr3->getAddress(), subnet_->getPreferred(), subnet_->getValid());

    // check DUIDs
    checkServerId(reply1, srv->getServerID());
    checkServerId(reply2, srv->getServerID());
    checkServerId(reply3, srv->getServerID());
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
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

    // Let's create a REQUEST
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REQUEST, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    shared_ptr<Option6IA> ia = generateIA(234, 1500, 3000);

    // with a valid hint
    IOAddress hint("2001:db8:1:1::dead:beef");
    ASSERT_TRUE(subnet_->inPool(hint));
    OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
    ia->addOption(hint_opt);
    req->addOption(ia);
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv->processRequest(req);

    // check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // check that IA_NA was returned and that there's an address included
    shared_ptr<Option6IAAddr> addr = checkIA_NA(reply, 234, subnet_->getT1(),
                                                subnet_->getT2());

    // check that we've got the address we requested
    checkIAAddr(addr, hint, subnet_->getPreferred(), subnet_->getValid());

    // check DUIDs
    checkServerId(reply, srv->getServerID());
    checkClientId(reply, clientid);

    // check that the lease is really in the database
    Lease6Ptr l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr);
    EXPECT_TRUE(l);
    LeaseMgr::instance().deleteLease6(addr->getAddress());
}

// This test checks that the server is offering different addresses to different
// clients in REQUEST. Please note that ADVERTISE is not a guarantee that such
// and address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same advertise as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. ADVERTISE is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv6SrvTest, ManyRequests) {
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

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

    // Pass it to the server and get an advertise
    Pkt6Ptr reply1 = srv->processRequest(req1);
    Pkt6Ptr reply2 = srv->processRequest(req2);
    Pkt6Ptr reply3 = srv->processRequest(req3);

    // check if we get response at all
    checkResponse(reply1, DHCPV6_REPLY, 1234);
    checkResponse(reply2, DHCPV6_REPLY, 2345);
    checkResponse(reply3, DHCPV6_REPLY, 3456);

    // check that IA_NA was returned and that there's an address included
    shared_ptr<Option6IAAddr> addr1 = checkIA_NA(reply1, 1, subnet_->getT1(),
                                                subnet_->getT2());
    shared_ptr<Option6IAAddr> addr2 = checkIA_NA(reply2, 2, subnet_->getT1(),
                                                subnet_->getT2());
    shared_ptr<Option6IAAddr> addr3 = checkIA_NA(reply3, 3, subnet_->getT1(),
                                                subnet_->getT2());

    // Check that the assigned address is indeed from the configured pool
    checkIAAddr(addr1, addr1->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr2, addr2->getAddress(), subnet_->getPreferred(), subnet_->getValid());
    checkIAAddr(addr3, addr3->getAddress(), subnet_->getPreferred(), subnet_->getValid());

    // check DUIDs
    checkServerId(reply1, srv->getServerID());
    checkServerId(reply2, srv->getServerID());
    checkServerId(reply3, srv->getServerID());
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

// This test verifies if the status code option is generated properly.
TEST_F(Dhcpv6SrvTest, StatusCode) {
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

    // a dummy content for client-id
    uint8_t expected[] = {0x0, 0x3, 0x41, 0x42, 0x43, 0x44, 0x45};
    OptionBuffer exp(expected, expected + sizeof(expected));

    OptionPtr status = srv->createStatusCode(3, "ABCDE");

    EXPECT_TRUE(status->getData() == exp);
}

// This test verifies if the selectSubnet() method works as expected.
TEST_F(Dhcpv6SrvTest, SelectSubnet) {
    boost::scoped_ptr<NakedDhcpv6Srv> srv;
    ASSERT_NO_THROW( srv.reset(new NakedDhcpv6Srv(0)) );

    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));

    // check that the packets originating from local addresses can be
    pkt->setRemoteAddr(IOAddress("fe80::abcd"));
    EXPECT_EQ(subnet_, srv->selectSubnet(pkt));

    // packets originating from subnet A will select subnet A
    pkt->setRemoteAddr(IOAddress("2001:db8:1::6789"));
    EXPECT_EQ(subnet_, srv->selectSubnet(pkt));

    // packets from a subnet that is not supported will not get
    // a subnet
    pkt->setRemoteAddr(IOAddress("3000::faf"));
    EXPECT_FALSE(srv->selectSubnet(pkt));

    /// @todo: expand this test once support for relays is implemented
}

}   // end of anonymous namespace
