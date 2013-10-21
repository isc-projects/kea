// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_custom.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>

using namespace std;
using namespace isc::asiolink;


namespace isc {
namespace dhcp {
namespace test {

/// dummy server-id file location
static const char* SRVID_FILE = "server-id-test.txt";

Dhcpv4SrvTest::Dhcpv4SrvTest()
:rcode_(-1) {
    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1000,
                                     2000, 3000));
    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"), IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);

    CfgMgr::instance().deleteSubnets4();
    CfgMgr::instance().addSubnet4(subnet_);

    // Add Router option.
    Option4AddrLstPtr opt_routers(new Option4AddrLst(DHO_ROUTERS));
    opt_routers->setAddress(IOAddress("192.0.2.2"));
    subnet_->addOption(opt_routers, false, "dhcp4");

    // it's ok if that fails. There should not be such a file anyway
    unlink(SRVID_FILE);

    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

    // There must be some interface detected
    if (ifaces.empty()) {
        // We can't use ASSERT in constructor
        ADD_FAILURE() << "No interfaces detected.";
    }

    valid_iface_ = ifaces.begin()->getName();
}

void Dhcpv4SrvTest::addPrlOption(Pkt4Ptr& pkt) {

    OptionUint8ArrayPtr option_prl =
        OptionUint8ArrayPtr(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));

    // Let's request options that have been configured for the subnet.
    option_prl->addValue(DHO_DOMAIN_NAME_SERVERS);
    option_prl->addValue(DHO_DOMAIN_NAME);
    option_prl->addValue(DHO_LOG_SERVERS);
    option_prl->addValue(DHO_COOKIE_SERVERS);
    // Let's also request the option that hasn't been configured. In such
    // case server should ignore request for this particular option.
    option_prl->addValue(DHO_LPR_SERVERS);
    // And add 'Parameter Request List' option into the DISCOVER packet.
    pkt->addOption(option_prl);
}

void Dhcpv4SrvTest::configureRequestedOptions() {
    // dns-servers
    Option4AddrLstPtr
        option_dns_servers(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS));
    option_dns_servers->addAddress(IOAddress("192.0.2.1"));
    option_dns_servers->addAddress(IOAddress("192.0.2.100"));
    ASSERT_NO_THROW(subnet_->addOption(option_dns_servers, false, "dhcp4"));

    // domain-name
    OptionDefinition def("domain-name", DHO_DOMAIN_NAME, OPT_FQDN_TYPE);
    OptionCustomPtr option_domain_name(new OptionCustom(def, Option::V4));
    option_domain_name->writeFqdn("example.com");
    subnet_->addOption(option_domain_name, false, "dhcp4");

    // log-servers
    Option4AddrLstPtr option_log_servers(new Option4AddrLst(DHO_LOG_SERVERS));
    option_log_servers->addAddress(IOAddress("192.0.2.2"));
    option_log_servers->addAddress(IOAddress("192.0.2.10"));
    ASSERT_NO_THROW(subnet_->addOption(option_log_servers, false, "dhcp4"));

    // cookie-servers
    Option4AddrLstPtr option_cookie_servers(new Option4AddrLst(DHO_COOKIE_SERVERS));
    option_cookie_servers->addAddress(IOAddress("192.0.2.1"));
    ASSERT_NO_THROW(subnet_->addOption(option_cookie_servers, false, "dhcp4"));
}

void Dhcpv4SrvTest::messageCheck(const Pkt4Ptr& q, const Pkt4Ptr& a) {
    ASSERT_TRUE(q);
    ASSERT_TRUE(a);

    EXPECT_EQ(q->getHops(),   a->getHops());
    EXPECT_EQ(q->getIface(),  a->getIface());
    EXPECT_EQ(q->getIndex(),  a->getIndex());
    EXPECT_EQ(q->getGiaddr(), a->getGiaddr());
    // When processing an incoming packet the remote address
    // is copied as a src address, and the source address is
    // copied as a remote address to the response.
    EXPECT_TRUE(q->getLocalHWAddr() == a->getLocalHWAddr());
    EXPECT_TRUE(q->getRemoteHWAddr() == a->getRemoteHWAddr());

    // Check that bare minimum of required options are there.
    // We don't check options requested by a client. Those
    // are checked elsewhere.
    EXPECT_TRUE(a->getOption(DHO_SUBNET_MASK));
    EXPECT_TRUE(a->getOption(DHO_ROUTERS));
    EXPECT_TRUE(a->getOption(DHO_DHCP_SERVER_IDENTIFIER));
    EXPECT_TRUE(a->getOption(DHO_DHCP_LEASE_TIME));
    EXPECT_TRUE(a->getOption(DHO_SUBNET_MASK));
    EXPECT_TRUE(a->getOption(DHO_DOMAIN_NAME));
    EXPECT_TRUE(a->getOption(DHO_DOMAIN_NAME_SERVERS));

    // Check that something is offered
    EXPECT_TRUE(a->getYiaddr().toText() != "0.0.0.0");
}

void Dhcpv4SrvTest::optionsCheck(const Pkt4Ptr& pkt) {
    // Check that the requested and configured options are returned
    // in the ACK message.
    EXPECT_TRUE(pkt->getOption(DHO_DOMAIN_NAME))
        << "domain-name not present in the response";
    EXPECT_TRUE(pkt->getOption(DHO_DOMAIN_NAME_SERVERS))
        << "dns-servers not present in the response";
    EXPECT_TRUE(pkt->getOption(DHO_LOG_SERVERS))
        << "log-servers not present in the response";
    EXPECT_TRUE(pkt->getOption(DHO_COOKIE_SERVERS))
        << "cookie-servers not present in the response";
    // Check that the requested but not configured options are not
    // returned in the ACK message.
    EXPECT_FALSE(pkt->getOption(DHO_LPR_SERVERS))
        << "domain-name present in the response but it is"
        << " expected not to be present";
}

OptionPtr Dhcpv4SrvTest::generateClientId(size_t size /*= 4*/) {

    OptionBuffer clnt_id(size);
    for (int i = 0; i < size; i++) {
        clnt_id[i] = 100 + i;
    }

    client_id_ = ClientIdPtr(new ClientId(clnt_id));

    return (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                 clnt_id.begin(),
                                 clnt_id.begin() + size)));
}

HWAddrPtr Dhcpv4SrvTest::generateHWAddr(size_t size /*= 6*/) {
    const uint8_t hw_type = 123; // Just a fake number (typically 6=HTYPE_ETHER, see dhcp4.h)
    OptionBuffer mac(size);
    for (int i = 0; i < size; ++i) {
        mac[i] = 50 + i;
    }
    return (HWAddrPtr(new HWAddr(mac, hw_type)));
}

void Dhcpv4SrvTest::checkAddressParams(const Pkt4Ptr& rsp, const SubnetPtr subnet,
                                       bool t1_mandatory /*= false*/,
                                       bool t2_mandatory /*= false*/) {

    // Technically inPool implies inRange, but let's be on the safe
    // side and check both.
    EXPECT_TRUE(subnet->inRange(rsp->getYiaddr()));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, rsp->getYiaddr()));

    // Check lease time
    OptionPtr opt = rsp->getOption(DHO_DHCP_LEASE_TIME);
    if (!opt) {
        ADD_FAILURE() << "Lease time option missing in response";
    } else {
        EXPECT_EQ(opt->getUint32(), subnet->getValid());
    }

    // Check T1 timer
    opt = rsp->getOption(DHO_DHCP_RENEWAL_TIME);
    if (opt) {
        EXPECT_EQ(opt->getUint32(), subnet->getT1());
    } else {
        if (t1_mandatory) {
            ADD_FAILURE() << "Required T1 option missing";
        }
    }

    // Check T2 timer
    opt = rsp->getOption(DHO_DHCP_REBINDING_TIME);
    if (opt) {
        EXPECT_EQ(opt->getUint32(), subnet->getT2());
    } else {
        if (t2_mandatory) {
            ADD_FAILURE() << "Required T2 option missing";
        }
    }
}

void Dhcpv4SrvTest::checkResponse(const Pkt4Ptr& rsp, uint8_t expected_message_type,
                                  uint32_t expected_transid) {
    ASSERT_TRUE(rsp);
    EXPECT_EQ(expected_message_type, rsp->getType());
    EXPECT_EQ(expected_transid, rsp->getTransid());
}

Lease4Ptr Dhcpv4SrvTest::checkLease(const Pkt4Ptr& rsp,
                                    const OptionPtr& client_id,
                                    const HWAddrPtr&,
                                    const IOAddress& expected_addr) {

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

    EXPECT_EQ(rsp->getYiaddr().toText(), expected_addr.toText());

    EXPECT_EQ(expected_addr.toText(), lease->addr_.toText());
    if (client_id) {
        EXPECT_TRUE(*lease->client_id_ == *id);
    }
    EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

    return (lease);
}

/// @brief Checks if server response (OFFER, ACK, NAK) includes proper server-id
/// @param rsp response packet to be validated
/// @param expected_srvid expected value of server-id
void Dhcpv4SrvTest::checkServerId(const Pkt4Ptr& rsp, const OptionPtr& expected_srvid) {
    // Check that server included its server-id
    OptionPtr opt = rsp->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->getType(), expected_srvid->getType() );
    EXPECT_EQ(opt->len(), expected_srvid->len() );
    EXPECT_TRUE(opt->getData() == expected_srvid->getData());
}

void Dhcpv4SrvTest::checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid) {
    // check that server included our own client-id
    OptionPtr opt = rsp->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    ASSERT_TRUE(opt);
    EXPECT_EQ(expected_clientid->getType(), opt->getType());
    EXPECT_EQ(expected_clientid->len(), opt->len());
    EXPECT_TRUE(expected_clientid->getData() == opt->getData());
}

void Dhcpv4SrvTest::testDiscoverRequest(const uint8_t msg_type) {
    // Create an instance of the tested class.
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Initialize the source HW address.
    vector<uint8_t> mac(6);
    for (int i = 0; i < 6; ++i) {
        mac[i] = i * 10;
    }
    // Initialized the destination HW address.
    vector<uint8_t> dst_mac(6);
    for (int i = 0; i < 6; ++i) {
        dst_mac[i] = i * 20;
    }
    // Create a DHCP message. It will be used to simulate the
    // incoming message.
    boost::shared_ptr<Pkt4> req(new Pkt4(msg_type, 1234));
    // Create a response message. It will hold a reponse packet.
    // Initially, set it to NULL.
    boost::shared_ptr<Pkt4> rsp;
    // Set the name of the interface on which packet is received.
    req->setIface("eth0");
    // Set the interface index. It is just a dummy value and will
    // not be interpreted.
    req->setIndex(17);
    // Set the target HW address. This value is normally used to
    // construct the data link layer header.
    req->setRemoteHWAddr(1, 6, dst_mac);
    // Set the HW address. This value is set on DHCP level (in chaddr).
    req->setHWAddr(1, 6, mac);
    // Set local HW address. It is used to construct the data link layer
    // header.
    req->setLocalHWAddr(1, 6, mac);
    // Set target IP address.
    req->setRemoteAddr(IOAddress("192.0.2.55"));
    // Set relay address.
    req->setGiaddr(IOAddress("192.0.2.10"));

    // We are going to test that certain options are returned
    // in the response message when requested using 'Parameter
    // Request List' option. Let's configure those options that
    // are returned when requested.
    configureRequestedOptions();

    if (msg_type == DHCPDISCOVER) {
        ASSERT_NO_THROW(
            rsp = srv->processDiscover(req);
        );

        // Should return OFFER
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPOFFER, rsp->getType());

    } else {
        ASSERT_NO_THROW(rsp = srv->processRequest(req););

        // Should return ACK
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPACK, rsp->getType());

    }

    messageCheck(req, rsp);

    // We did not request any options so these should not be present
    // in the RSP.
    EXPECT_FALSE(rsp->getOption(DHO_LOG_SERVERS));
    EXPECT_FALSE(rsp->getOption(DHO_COOKIE_SERVERS));
    EXPECT_FALSE(rsp->getOption(DHO_LPR_SERVERS));

    // Repeat the test but request some options.
    // Add 'Parameter Request List' option.
    addPrlOption(req);

    if (msg_type == DHCPDISCOVER) {
        ASSERT_NO_THROW(rsp = srv->processDiscover(req););

        // Should return non-NULL packet.
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPOFFER, rsp->getType());

    } else {
        ASSERT_NO_THROW(rsp = srv->processRequest(req););

        // Should return non-NULL packet.
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPACK, rsp->getType());
    }

    // Check that the requested options are returned.
    optionsCheck(rsp);
}

/// @brief This function cleans up after the test.
void Dhcpv4SrvTest::TearDown() {

    CfgMgr::instance().deleteSubnets4();

    // Let's clean up if there is such a file.
    unlink(SRVID_FILE);

    // Close all open sockets.
    IfaceMgr::instance().closeSockets();

    // Some unit tests override the default packet filtering class, used
    // by the IfaceMgr. The dummy class, called PktFilterTest, reports the
    // capability to directly respond to the clients without IP address
    // assigned. This capability is not supported by the default packet
    // filtering class: PktFilterInet. Therefore setting the dummy class
    // allows to test scenarios, when server responds to the broadcast address
    // on client's request, despite having support for direct response.
    // The following call restores the use of original packet filtering class
    // after the test.
    try {
        IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterInet()));

    } catch (const Exception& ex) {
        FAIL() << "Failed to restore the default (PktFilterInet) packet filtering"
               << " class after the test. Exception has been caught: "
               << ex.what();
    }
}

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace
