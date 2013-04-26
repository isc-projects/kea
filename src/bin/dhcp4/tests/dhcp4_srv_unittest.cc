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
#include <sstream>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
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

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:

    /// @brief Constructor.
    ///
    /// It disables configuration of broadcast options on
    /// sockets that are opened by the Dhcpv4Srv constructor.
    /// Setting broadcast options requires root privileges
    /// which is not the case when running unit tests.
    NakedDhcpv4Srv(uint16_t port = 0)
        : Dhcpv4Srv(port, "type=memfile", false) {
    }

    using Dhcpv4Srv::processDiscover;
    using Dhcpv4Srv::processRequest;
    using Dhcpv4Srv::processRelease;
    using Dhcpv4Srv::processDecline;
    using Dhcpv4Srv::processInform;
    using Dhcpv4Srv::getServerID;
    using Dhcpv4Srv::loadServerID;
    using Dhcpv4Srv::generateServerID;
    using Dhcpv4Srv::writeServerID;
    using Dhcpv4Srv::sanityCheck;
    using Dhcpv4Srv::srvidToString;
};

static const char* SRVID_FILE = "server-id-test.txt";

class Dhcpv4SrvTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// Initializes common objects used in many tests.
    /// Also sets up initial configuration in CfgMgr.
    Dhcpv4SrvTest() {
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
    }

    /// @brief Add 'Parameter Request List' option to the packet.
    ///
    /// This function PRL option comprising the following option codes:
    /// - 5 - Name Server
    /// - 15 - Domain Name
    /// - 7 - Log Server
    /// - 8 - Quotes Server
    /// - 9 - LPR Server
    ///
    /// @param pkt packet to add PRL option to.
    void addPrlOption(Pkt4Ptr& pkt) {

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

    /// @brief Configures options being requested in the PRL option.
    ///
    /// The lpr-servers option is NOT configured here although it is
    /// added to the 'Parameter Request List' option in the
    /// \ref addPrlOption. When requested option is not configured
    /// the server should not return it in its response. The goal
    /// of not configuring the requested option is to verify that
    /// the server will not return it.
    void configureRequestedOptions() {
        // dns-servers
        Option4AddrLstPtr
            option_dns_servers(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS));
        option_dns_servers->addAddress(IOAddress("192.0.2.1"));
        option_dns_servers->addAddress(IOAddress("192.0.2.100"));
        ASSERT_NO_THROW(subnet_->addOption(option_dns_servers, false, "dhcp4"));

        // domain-name
        OptionDefinition def("domain-name", DHO_DOMAIN_NAME, OPT_FQDN_TYPE);
        boost::shared_ptr<OptionCustom>
            option_domain_name(new OptionCustom(def, Option::V4));
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

    /// @brief checks that the response matches request
    /// @param q query (client's message)
    /// @param a answer (server's message)
    void messageCheck(const boost::shared_ptr<Pkt4>& q,
                      const boost::shared_ptr<Pkt4>& a) {
        ASSERT_TRUE(q);
        ASSERT_TRUE(a);

        EXPECT_EQ(q->getHops(),   a->getHops());
        EXPECT_EQ(q->getIface(),  a->getIface());
        EXPECT_EQ(q->getIndex(),  a->getIndex());
        EXPECT_EQ(q->getGiaddr(), a->getGiaddr());

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

    /// @brief Check that requested options are present.
    ///
    /// @param pkt packet to be checked.
    void optionsCheck(const Pkt4Ptr& pkt) {
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

    /// @brief generates client-id option
    ///
    /// Generate client-id option of specified length
    /// Ids with different lengths are sufficent to generate
    /// unique ids. If more fine grained control is required,
    /// tests generate client-ids on their own.
    /// Sets client_id_ field.
    /// @param size size of the client-id to be generated
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

    /// @brief generate hardware address
    ///
    /// @param size size of the generated MAC address
    /// @param pointer to Hardware Address object
    HWAddrPtr generateHWAddr(size_t size = 6) {
        const uint8_t hw_type = 123; // Just a fake number (typically 6=HTYPE_ETHER, see dhcp4.h)
        OptionBuffer mac(size);
        for (int i = 0; i < size; ++i) {
            mac[i] = 50 + i;
        }
        return (HWAddrPtr(new HWAddr(mac, hw_type)));
    }

    /// Check that address was returned from proper range, that its lease
    /// lifetime is correct, that T1 and T2 are returned properly
    /// @param rsp response to be checked
    /// @param subnet subnet that should be used to verify assigned address
    ///        and options
    /// @param t1_mandatory is T1 mandatory?
    /// @param t2_mandatory is T2 mandatory?
    void checkAddressParams(const Pkt4Ptr& rsp, const SubnetPtr subnet,
                            bool t1_mandatory = false,
                            bool t2_mandatory = false) {

        // Technically inPool implies inRange, but let's be on the safe
        // side and check both.
        EXPECT_TRUE(subnet->inRange(rsp->getYiaddr()));
        EXPECT_TRUE(subnet->inPool(rsp->getYiaddr()));

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

    /// @brief Basic checks for generated response (message type and trans-id).
    ///
    /// @param rsp response packet to be validated
    /// @param expected_message_type expected message type
    /// @param expected_transid expected transaction-id
    void checkResponse(const Pkt4Ptr& rsp, uint8_t expected_message_type,
                       uint32_t expected_transid) {
        ASSERT_TRUE(rsp);
        EXPECT_EQ(expected_message_type, rsp->getType());
        EXPECT_EQ(expected_transid, rsp->getTransid());
    }

    /// @brief Checks if the lease sent to client is present in the database
    ///
    /// @param rsp response packet to be validated
    /// @param client_id expected client-identifier (or NULL)
    /// @param HWAddr expected hardware address (not used now)
    /// @param expected_addr expected address
    Lease4Ptr checkLease(const Pkt4Ptr& rsp, const OptionPtr& client_id,
                         const HWAddrPtr&, const IOAddress& expected_addr) {

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
    void checkServerId(const Pkt4Ptr& rsp, const OptionPtr& expected_srvid) {
        // Check that server included its server-id
        OptionPtr opt = rsp->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        ASSERT_TRUE(opt);
        EXPECT_EQ(opt->getType(), expected_srvid->getType() );
        EXPECT_EQ(opt->len(), expected_srvid->len() );
        EXPECT_TRUE(opt->getData() == expected_srvid->getData());
    }

    /// @brief Checks if server response (OFFER, ACK, NAK) includes proper client-id
    /// @param rsp response packet to be validated
    /// @param expected_clientid expected value of client-id
    void checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid) {
        // check that server included our own client-id
        OptionPtr opt = rsp->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        ASSERT_TRUE(opt);
        EXPECT_EQ(expected_clientid->getType(), opt->getType());
        EXPECT_EQ(expected_clientid->len(), opt->len());
        EXPECT_TRUE(expected_clientid->getData() == opt->getData());
    }

    /// @brief Tests if Discover or Request message is processed correctly
    ///
    /// @param msg_type DHCPDISCOVER or DHCPREQUEST
    /// @param client_addr client address
    /// @param relay_addr relay address
    void testDiscoverRequest(const uint8_t msg_type,
                             const IOAddress& client_addr,
                             const IOAddress& relay_addr) {

        boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));
        vector<uint8_t> mac(6);
        for (int i = 0; i < 6; i++) {
            mac[i] = i*10;
        }

        boost::shared_ptr<Pkt4> req(new Pkt4(msg_type, 1234));
        boost::shared_ptr<Pkt4> rsp;

        req->setIface("eth0");
        req->setIndex(17);
        req->setHWAddr(1, 6, mac);
        req->setRemoteAddr(IOAddress(client_addr));
        req->setGiaddr(relay_addr);

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
            ASSERT_NO_THROW(
                rsp = srv->processRequest(req);
            );

            // Should return ACK
            ASSERT_TRUE(rsp);
            EXPECT_EQ(DHCPACK, rsp->getType());

        }

        if (relay_addr.toText() != "0.0.0.0") {
            // This is relayed message. It should be sent brsp to relay address.
            EXPECT_EQ(req->getGiaddr().toText(),
                      rsp->getRemoteAddr().toText());

        } else if (client_addr.toText() != "0.0.0.0") {
            // This is a message from a client having an IP address.
            EXPECT_EQ(req->getRemoteAddr().toText(),
                      rsp->getRemoteAddr().toText());

        } else {
            // This is a message from a client having no IP address yet.
            // If IfaceMgr supports direct traffic the response should
            // be sent to the new address assigned to the client.
            if (IfaceMgr::instance().isDirectResponseSupported()) {
                EXPECT_EQ(rsp->getYiaddr(),
                          rsp->getRemoteAddr().toText());

            // If direct response to the client having no IP address is
            // not supported, response should go to broadcast.
            } else {
                EXPECT_EQ("255.255.255.255", rsp->getRemoteAddr().toText());

            }

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
            ASSERT_NO_THROW(
                rsp = srv->processDiscover(req);
            );

            // Should return non-NULL packet.
            ASSERT_TRUE(rsp);
            EXPECT_EQ(DHCPOFFER, rsp->getType());

        } else {
            ASSERT_NO_THROW(
                rsp = srv->processRequest(req);
            );

            // Should return non-NULL packet.
            ASSERT_TRUE(rsp);
            EXPECT_EQ(DHCPACK, rsp->getType());

        }

        // Check that the requested options are returned.
        optionsCheck(rsp);

    }

    ~Dhcpv4SrvTest() {
        CfgMgr::instance().deleteSubnets4();

        // Let's clean up if there is such a file.
        unlink(SRVID_FILE);
    };

    /// @brief A subnet used in most tests
    Subnet4Ptr subnet_;

    /// @brief A pool used in most tests
    Pool4Ptr pool_;

    /// @brief A client-id used in most tests
    ClientIdPtr client_id_;
};

// Sanity check. Verifies that both Dhcpv4Srv and its derived
// class NakedDhcpv4Srv can be instantiated and destroyed.
TEST_F(Dhcpv4SrvTest, basic) {

    // Check that the base class can be instantiated
    Dhcpv4Srv* srv = NULL;
    ASSERT_NO_THROW({
        srv = new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000);
    });
    delete srv;

    // Check that the derived class can be instantiated
    NakedDhcpv4Srv* naked_srv = NULL;
    ASSERT_NO_THROW({
        naked_srv = new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000);
    });
    EXPECT_TRUE(naked_srv->getServerID());
    delete naked_srv;

    ASSERT_NO_THROW({
        naked_srv = new NakedDhcpv4Srv(0);
    });
    EXPECT_TRUE(naked_srv->getServerID());

    delete naked_srv;
}

// Verifies that DISCOVER received via relay can be processed correctly,
// that the OFFER message generated in response is valid and
// contains necessary options.
//
// Note: this test focuses on the packet correctness. There
// are other tests that verify correctness of the allocation
// engine. See DiscoverBasic, DiscoverHint, DiscoverNoClientId
// and DiscoverInvalidHint.
TEST_F(Dhcpv4SrvTest, processDiscoverRelay) {
    testDiscoverRequest(DHCPDISCOVER,
                        IOAddress("192.0.2.56"),
                        IOAddress("192.0.2.67"));
}

// Verifies that the non-relayed DISCOVER is processed correctly when
// client source address is specified.
TEST_F(Dhcpv4SrvTest, processDiscoverNoRelay) {
    testDiscoverRequest(DHCPDISCOVER,
                        IOAddress("0.0.0.0"),
                        IOAddress("192.0.2.67"));
}

// Verified that the non-relayed DISCOVER is processed correctly when
// client source address is not specified.
TEST_F(Dhcpv4SrvTest, processDiscoverNoClientAddr) {
    testDiscoverRequest(DHCPDISCOVER,
                        IOAddress("0.0.0.0"),
                        IOAddress("0.0.0.0"));
}

// Verifies that REQUEST received via relay can be processed correctly,
// that the OFFER message generated in response is valid and
// contains necessary options.
//
// Note: this test focuses on the packet correctness. There
// are other tests that verify correctness of the allocation
// engine. See DiscoverBasic, DiscoverHint, DiscoverNoClientId
// and DiscoverInvalidHint.
TEST_F(Dhcpv4SrvTest, processRequestRelay) {
    testDiscoverRequest(DHCPREQUEST,
                        IOAddress("192.0.2.56"),
                        IOAddress("192.0.2.67"));
}

// Verifies that the non-relayed REQUEST is processed correctly when
// client source address is specified.
TEST_F(Dhcpv4SrvTest, processRequestNoRelay) {
    testDiscoverRequest(DHCPREQUEST,
                        IOAddress("0.0.0.0"),
                        IOAddress("192.0.2.67"));
}

// Verified that the non-relayed REQUEST is processed correctly when
// client source address is not specified.
TEST_F(Dhcpv4SrvTest, processRequestNoClientAddr) {
    testDiscoverRequest(DHCPREQUEST,
                        IOAddress("0.0.0.0"),
                        IOAddress("0.0.0.0"));
}

TEST_F(Dhcpv4SrvTest, processRelease) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPRELEASE, 1234));

    // Should not throw
    EXPECT_NO_THROW(
        srv->processRelease(pkt);
    );

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processDecline) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPDECLINE, 1234));

    // Should not throw
    EXPECT_NO_THROW(
        srv->processDecline(pkt);
    );

    delete srv;
}

TEST_F(Dhcpv4SrvTest, processInform) {
    NakedDhcpv4Srv* srv = new NakedDhcpv4Srv();

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPINFORM, 1234));

    // Should not throw
    EXPECT_NO_THROW(
        srv->processInform(pkt);
    );

    // Should return something
    EXPECT_TRUE(srv->processInform(pkt));

    // @todo Implement more reasonable tests before starting
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
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    // Check identifiers
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
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_EQ(offer->getYiaddr().toText(), hint.toText());

    // Check identifiers
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
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("192.0.2.107");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.1"));
    dis->setYiaddr(hint);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_EQ(offer->getYiaddr().toText(), hint.toText());

    // Check identifiers
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
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));
    IOAddress hint("10.1.2.3");

    Pkt4Ptr dis = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    dis->setRemoteAddr(IOAddress("192.0.2.107"));
    OptionPtr clientid = generateClientId();
    dis->addOption(clientid);
    dis->setYiaddr(hint);

    // Pass it to the server and get an offer
    Pkt4Ptr offer = srv->processDiscover(dis);

    // Check if we get response at all
    checkResponse(offer, DHCPOFFER, 1234);

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(offer, subnet_);

    EXPECT_NE(offer->getYiaddr().toText(), hint.toText());

    // Check identifiers
    checkServerId(offer, srv->getServerID());
    checkClientId(offer, clientid);
}

/// @todo: Add a test that client sends hint that is in pool, but currently
/// being used by a different client.

// This test checks that the server is offering different addresses to different
// clients in OFFERs. Please note that OFFER is not a guarantee that such
// an address will be assigned. Had the pool was very small and contained only
// 2 addresses, the third client would get the same offer as the first one
// and this is a correct behavior. It is REQUEST that will fail for the third
// client. OFFER is basically saying "if you send me a request, you will
// probably get an address like this" (there are no guarantees).
TEST_F(Dhcpv4SrvTest, ManyDiscovers) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr dis1 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr dis2 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 2345));
    Pkt4Ptr dis3 = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 3456));

    dis1->setRemoteAddr(IOAddress("192.0.2.1"));
    dis2->setRemoteAddr(IOAddress("192.0.2.2"));
    dis3->setRemoteAddr(IOAddress("192.0.2.3"));

    // Different client-id sizes
    OptionPtr clientid1 = generateClientId(4); // length 4
    OptionPtr clientid2 = generateClientId(5); // length 5
    OptionPtr clientid3 = generateClientId(6); // length 6

    dis1->addOption(clientid1);
    dis2->addOption(clientid2);
    dis3->addOption(clientid3);

    // Pass it to the server and get an offer
    Pkt4Ptr offer1 = srv->processDiscover(dis1);
    Pkt4Ptr offer2 = srv->processDiscover(dis2);
    Pkt4Ptr offer3 = srv->processDiscover(dis3);

    // Check if we get response at all
    checkResponse(offer1, DHCPOFFER, 1234);
    checkResponse(offer2, DHCPOFFER, 2345);
    checkResponse(offer3, DHCPOFFER, 3456);

    IOAddress addr1 = offer1->getYiaddr();
    IOAddress addr2 = offer2->getYiaddr();
    IOAddress addr3 = offer3->getYiaddr();

    // Check that the assigned address is indeed from the configured pool
    checkAddressParams(offer1, subnet_);
    checkAddressParams(offer2, subnet_);
    checkAddressParams(offer3, subnet_);

    // Check server-ids
    checkServerId(offer1, srv->getServerID());
    checkServerId(offer2, srv->getServerID());
    checkServerId(offer3, srv->getServerID());
    checkClientId(offer1, clientid1);
    checkClientId(offer2, clientid2);
    checkClientId(offer3, clientid3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1.toText(), addr2.toText());
    EXPECT_NE(addr2.toText(), addr3.toText());
    EXPECT_NE(addr3.toText(), addr1.toText());
    cout << "Offered address to client1=" << addr1.toText() << endl;
    cout << "Offered address to client2=" << addr2.toText() << endl;
    cout << "Offered address to client3=" << addr3.toText() << endl;
}

// This test verifies that incoming REQUEST can be handled properly, that an
// ACK is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed a single REQUEST message with:
// - client-id option
// - hwaddr information
// - requested address (that the client received in DISCOVER/OFFER exchange)
//
// expected returned ACK message:
// - copy of client-id
// - server-id
// - assigned address
//
// Test verifies that the lease is actually in the database.
TEST_F(Dhcpv4SrvTest, RequestBasic) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    IOAddress hint("192.0.2.107");
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress("192.0.2.1"));
    OptionPtr clientid = generateClientId();
    req->addOption(clientid);
    req->setYiaddr(hint);

    // Pass it to the server and get an advertise
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(hint.toText(), ack->getYiaddr().toText());

    // Check that address was returned from proper range, that its lease
    // lifetime is correct, that T1 and T2 are returned properly
    checkAddressParams(ack, subnet_);

    // Check identifiers
    checkServerId(ack, srv->getServerID());
    checkClientId(ack, clientid);

    // Check that the lease is really in the database
    Lease4Ptr l = checkLease(ack, clientid, req->getHWAddr(), hint);

    ASSERT_TRUE(l);
    LeaseMgrFactory::instance().deleteLease(l->addr_);
}

// This test verifies that incoming REQUEST can be handled properly, that an
// ACK is generated, that the response has an address and that address
// really belongs to the configured pool.
//
// constructed 3 REQUEST messages with:
// - client-id option (differs between messages)
// - hwaddr information (differs between messages)
//
// expected returned ACK message:
// - copy of client-id
// - server-id
// - assigned address (different for each client)
TEST_F(Dhcpv4SrvTest, ManyRequests) {

    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress req_addr1("192.0.2.105");
    const IOAddress req_addr2("192.0.2.101");
    const IOAddress req_addr3("192.0.2.109");
    const IOAddress relay("192.0.2.1");

    Pkt4Ptr req1 = Pkt4Ptr(new Pkt4(DHCPOFFER, 1234));
    Pkt4Ptr req2 = Pkt4Ptr(new Pkt4(DHCPOFFER, 2345));
    Pkt4Ptr req3 = Pkt4Ptr(new Pkt4(DHCPOFFER, 3456));

    req1->setRemoteAddr(relay);
    req2->setRemoteAddr(relay);
    req3->setRemoteAddr(relay);

    req1->setYiaddr(req_addr1);
    req2->setYiaddr(req_addr2);
    req3->setYiaddr(req_addr3);

    req1->setHWAddr(generateHWAddr(6));
    req2->setHWAddr(generateHWAddr(7));
    req3->setHWAddr(generateHWAddr(8));

    // Different client-id sizes
    OptionPtr clientid1 = generateClientId(4); // length 4
    OptionPtr clientid2 = generateClientId(5); // length 5
    OptionPtr clientid3 = generateClientId(6); // length 6

    req1->addOption(clientid1);
    req2->addOption(clientid2);
    req3->addOption(clientid3);

    // Pass it to the server and get an advertise
    Pkt4Ptr ack1 = srv->processRequest(req1);
    Pkt4Ptr ack2 = srv->processRequest(req2);
    Pkt4Ptr ack3 = srv->processRequest(req3);

    // Check if we get response at all
    checkResponse(ack1, DHCPACK, 1234);
    checkResponse(ack2, DHCPACK, 2345);
    checkResponse(ack3, DHCPACK, 3456);

    IOAddress addr1 = ack1->getYiaddr();
    IOAddress addr2 = ack2->getYiaddr();
    IOAddress addr3 = ack3->getYiaddr();

    // Check that every client received the address it requested
    EXPECT_EQ(req_addr1.toText(), addr1.toText());
    EXPECT_EQ(req_addr2.toText(), addr2.toText());
    EXPECT_EQ(req_addr3.toText(), addr3.toText());

    // Check that the assigned address is indeed from the configured pool
    checkAddressParams(ack1, subnet_);
    checkAddressParams(ack2, subnet_);
    checkAddressParams(ack3, subnet_);

    // Check DUIDs
    checkServerId(ack1, srv->getServerID());
    checkServerId(ack2, srv->getServerID());
    checkServerId(ack3, srv->getServerID());
    checkClientId(ack1, clientid1);
    checkClientId(ack2, clientid2);
    checkClientId(ack3, clientid3);

    // Check that leases are in the database
    Lease4Ptr l = checkLease(ack1, clientid1, req1->getHWAddr(), addr1);
    EXPECT_TRUE(l);
    l = checkLease(ack2, clientid2, req2->getHWAddr(), addr2);
    l = checkLease(ack3, clientid3, req3->getHWAddr(), addr3);

    // Finally check that the addresses offered are different
    EXPECT_NE(addr1.toText(), addr2.toText());
    EXPECT_NE(addr2.toText(), addr3.toText());
    EXPECT_NE(addr3.toText(), addr1.toText());
    cout << "Offered address to client1=" << addr1.toText() << endl;
    cout << "Offered address to client2=" << addr2.toText() << endl;
    cout << "Offered address to client3=" << addr3.toText() << endl;
}


// This test verifies that incoming (positive) REQUEST/Renewing can be handled properly, that a
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
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
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
    req->setCiaddr(addr); // client's address

    req->addOption(clientid);
    req->addOption(srv->getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt4Ptr ack = srv->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);
    EXPECT_EQ(addr.toText(), ack->getYiaddr().toText());

    // Check that address was returned from proper range, that its lease
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
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr));
}

// @todo: Implement tests for rejecting renewals

// This test verifies if the sanityCheck() really checks options presence.
TEST_F(Dhcpv4SrvTest, sanityCheck) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));

    // Client-id is optional for information-request, so
    EXPECT_NO_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::OPTIONAL));

    // Empty packet, no server-id
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY), RFCViolation);

    pkt->addOption(srv->getServerID());

    // Server-id is mandatory and present = no exception
    EXPECT_NO_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::MANDATORY));

    // Server-id is forbidden, but present => exception
    EXPECT_THROW(srv->sanityCheck(pkt, Dhcpv4Srv::FORBIDDEN),
                 RFCViolation);
}

// This test verifies that incoming (positive) RELEASE can be handled properly.
// As there is no REPLY in DHCPv4, the only thing to verify here is that
// the lease is indeed removed from the database.
TEST_F(Dhcpv4SrvTest, ReleaseBasic) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_t1 = 50;
    const uint32_t temp_t2 = 75;
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, mac_addr, sizeof(mac_addr),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              temp_valid, temp_t1, temp_t2, temp_timestamp,
                              subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv->getServerID());
    rel->setHWAddr(hw);

    // Pass it to the server and hope for a REPLY
    // Note: this is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv->processRelease(rel));

    // The lease should be gone from LeaseMgr
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);

    // Try to get the lease by hardware address
    // @todo: Uncomment this once trac2592 is implemented
    // Lease4Collection leases = LeaseMgrFactory::instance().getLease4(hw->hwaddr_);
    // EXPECT_EQ(leases.size(), 0);

    // Try to get it by hw/subnet_id combination
    l = LeaseMgrFactory::instance().getLease4(hw->hwaddr_, subnet_->getID());
    EXPECT_FALSE(l);

    // Try by client-id
    // @todo: Uncomment this once trac2592 is implemented
    //Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    //EXPECT_EQ(leases.size(), 0);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_FALSE(l);

    // Ok, the lease is *really* not there.
}

// This test verifies that incoming (invalid) RELEASE can be handled properly.
//
// This test checks 3 scenarios:
// 1. there is no such lease at all
// 2. there is such a lease, but it is assigned to a different IAID
// 3. there is such a lease, but it belongs to a different client
TEST_F(Dhcpv4SrvTest, ReleaseReject) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedDhcpv4Srv(0)));

    const IOAddress addr("192.0.2.106");
    const uint32_t t1 = 50;
    const uint32_t t2 = 75;
    const uint32_t valid = 100;
    const time_t timestamp = time(NULL) - 10;

    // Let's create a lease and put it in the LeaseMgr
    uint8_t bogus_mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe};
    HWAddrPtr bogus_hw(new HWAddr(bogus_mac_addr, sizeof(bogus_mac_addr), HTYPE_ETHER));
    OptionPtr bogus_clientid = generateClientId(7); // different length

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(addr));

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv->getServerID());
    rel->setHWAddr(bogus_hw);

    // Case 1: No lease known to server
    SCOPED_TRACE("CASE 1: Lease is not known to the server");

    // There is nothing to check here. The lease is not there and server does
    // not send anything back. This case is enumerated here just for keeping
    // parity with similar test in DHCPv6.
    EXPECT_NO_THROW(srv->processRelease(rel));

    // CASE 2: Lease is known and belongs to this client, but to a different hardware
    SCOPED_TRACE("CASE 2: Lease is known and belongs to this client, but uses different HW addr");

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0x1, 0x2, 0x3, 0x4, 0x5};
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, mac_addr, sizeof(mac_addr),
                              &client_id_->getDuid()[0], client_id_->getDuid().size(),
                              valid, t1, t2, timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));
    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    rel->setHWAddr(bogus_hw);

    EXPECT_NO_THROW(srv->processRelease(rel));

    // Check that the lease was not removed (due to hardware address mis-match)
    l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // CASE 3: Lease belongs to a client with different client-id
    SCOPED_TRACE("CASE 3: Lease belongs to a client with different client-id");

    rel->setHWAddr(hw); // proper HW address this time
    rel->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    rel->addOption(bogus_clientid); // but invalid client-id

    OptionPtr x = rel->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    EXPECT_NO_THROW(srv->processRelease(rel));

    // Check that the lease is still there
    l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Final sanity check. Verify that with valid hw and client-id release is successful
    rel->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
    rel->addOption(clientid);

    // It should work this time
    EXPECT_NO_THROW(srv->processRelease(rel));

    // Check that the lease is not there
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);
}

// This test verifies if the server-id disk operations (read, write) are
// working properly.
TEST_F(Dhcpv4SrvTest, ServerID) {
    NakedDhcpv4Srv srv(0);

    string srvid_text = "192.0.2.100";
    IOAddress srvid(srvid_text);

    fstream file1(SRVID_FILE, ios::out | ios::trunc);
    file1 << srvid_text;
    file1.close();

    // Test reading from a file
    EXPECT_TRUE(srv.loadServerID(SRVID_FILE));
    ASSERT_TRUE(srv.getServerID());
    EXPECT_EQ(srvid_text, srv.srvidToString(srv.getServerID()));

    // Now test writing to a file
    EXPECT_EQ(0, unlink(SRVID_FILE));
    EXPECT_NO_THROW(srv.writeServerID(SRVID_FILE));

    fstream file2(SRVID_FILE, ios::in);
    ASSERT_TRUE(file2.good());
    string text;
    file2 >> text;
    file2.close();

    EXPECT_EQ(srvid_text, text);
}

} // end of anonymous namespace
