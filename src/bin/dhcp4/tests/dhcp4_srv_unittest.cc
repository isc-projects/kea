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
#include <config/ccsession.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/config_parser.h>
#include <hooks/server_hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <gtest/gtest.h>
#include <hooks/server_hooks.h>
#include <hooks/hooks_manager.h>

#include <boost/scoped_ptr.hpp>

#include <fstream>
#include <iostream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::hooks;

namespace {

class NakedDhcpv4Srv: public Dhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:

    /// @brief Constructor.
    ///
    /// This constructor disables default modes of operation used by the
    /// Dhcpv4Srv class:
    /// - Send/receive broadcast messages through sockets on interfaces
    /// which support broadcast traffic.
    /// - Direct DHCPv4 traffic - communication with clients which do not
    /// have IP address assigned yet.
    ///
    /// Enabling these modes requires root privilges so they must be
    /// disabled for unit testing.
    ///
    /// Note, that disabling broadcast options on sockets does not impact
    /// the operation of these tests because they use local loopback
    /// interface which doesn't have broadcast capability anyway. It rather
    /// prevents setting broadcast options on other (broadcast capable)
    /// sockets which are opened on other interfaces in Dhcpv4Srv constructor.
    ///
    /// The Direct DHCPv4 Traffic capability can be disabled here because
    /// it is tested with PktFilterLPFTest unittest. The tests which belong
    /// to PktFilterLPFTest can be enabled on demand when root privileges can
    /// be guaranteed.
    ///
    /// @param port port number to listen on; the default value 0 indicates
    /// that sockets should not be opened.
    NakedDhcpv4Srv(uint16_t port = 0)
        : Dhcpv4Srv(port, "type=memfile", false, false) {
    }

    /// @brief fakes packet reception
    /// @param timeout ignored
    ///
    /// The method receives all packets queued in receive
    /// queue, one after another. Once the queue is empty,
    /// it initiates the shutdown procedure.
    ///
    /// See fake_received_ field for description
    virtual Pkt4Ptr receivePacket(int /*timeout*/) {

        // If there is anything prepared as fake incoming
        // traffic, use it
        if (!fake_received_.empty()) {
            Pkt4Ptr pkt = fake_received_.front();
            fake_received_.pop_front();
            return (pkt);
        }

        // If not, just trigger shutdown and
        // return immediately
        shutdown();
        return (Pkt4Ptr());
    }

    /// @brief fake packet sending
    ///
    /// Pretend to send a packet, but instead just store
    /// it in fake_send_ list where test can later inspect
    /// server's response.
    virtual void sendPacket(const Pkt4Ptr& pkt) {
        fake_sent_.push_back(pkt);
    }

    /// @brief adds a packet to fake receive queue
    ///
    /// See fake_received_ field for description
    void fakeReceive(const Pkt4Ptr& pkt) {
        fake_received_.push_back(pkt);
    }

    virtual ~NakedDhcpv4Srv() {
    }

    /// @brief packets we pretend to receive
    ///
    /// Instead of setting up sockets on interfaces that change between OSes, it
    /// is much easier to fake packet reception. This is a list of packets that
    /// we pretend to have received. You can schedule new packets to be received
    /// using fakeReceive() and NakedDhcpv4Srv::receivePacket() methods.
    list<Pkt4Ptr> fake_received_;

    list<Pkt4Ptr> fake_sent_;

    using Dhcpv4Srv::adjustRemoteAddr;
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

/// @brief Dummy Packet Filtering class.
///
/// This class reports capability to respond directly to the
/// client which doesn't have address configured yet.
///
/// All packet and socket handling functions do nothing because
/// they are not used in unit tests.
class PktFilterTest : public PktFilter {
public:

    /// @brief Reports 'direct response' capability.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const {
        return (true);
    }

    /// Does nothing.
    virtual int openSocket(const Iface&, const IOAddress&, const uint16_t,
                           const bool, const bool) {
        return (0);
    }

    /// Does nothing.
    virtual Pkt4Ptr receive(const Iface&, const SocketInfo&) {
        return Pkt4Ptr();
    }

    /// Does nothing.
    virtual int send(const Iface&, uint16_t, const Pkt4Ptr&) {
        return (0);
    }

};

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

        const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

        // There must be some interface detected
        if (ifaces.empty()) {
            // We can't use ASSERT in constructor
            ADD_FAILURE() << "No interfaces detected.";
        }

        valid_iface_ = ifaces.begin()->getName();
    }

    virtual ~Dhcpv4SrvTest() {
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

    /// @brief checks that the response matches request
    /// @param q query (client's message)
    /// @param a answer (server's message)
    void messageCheck(const Pkt4Ptr& q, const Pkt4Ptr& a) {
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
    void testDiscoverRequest(const uint8_t msg_type) {
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
            ASSERT_NO_THROW(
                rsp = srv->processRequest(req);
            );

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

    /// @brief This function cleans up after the test.
    virtual void TearDown() {

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

    /// @brief A subnet used in most tests
    Subnet4Ptr subnet_;

    /// @brief A pool used in most tests
    Pool4Ptr pool_;

    /// @brief A client-id used in most tests
    ClientIdPtr client_id_;

    int rcode_;

    ConstElementPtr comment_;

    // Name of a valid network interface
    string valid_iface_;
};

// Sanity check. Verifies that both Dhcpv4Srv and its derived
// class NakedDhcpv4Srv can be instantiated and destroyed.
TEST_F(Dhcpv4SrvTest, basic) {

    // Check that the base class can be instantiated
    boost::scoped_ptr<Dhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new Dhcpv4Srv(DHCP4_SERVER_PORT + 10000, "type=memfile",
                                            false, false)));
    srv.reset();
    // We have to close open sockets because further in this test we will
    // call the Dhcpv4Srv constructor again. This constructor will try to
    // set the appropriate packet filter class for IfaceMgr. This requires
    // that all sockets are closed.
    IfaceMgr::instance().closeSockets();

    // Check that the derived class can be instantiated
    boost::scoped_ptr<NakedDhcpv4Srv> naked_srv;
    ASSERT_NO_THROW(
        naked_srv.reset(new NakedDhcpv4Srv(DHCP4_SERVER_PORT + 10000)));
    EXPECT_TRUE(naked_srv->getServerID());
    // Close sockets again for the next test.
    IfaceMgr::instance().closeSockets();

    ASSERT_NO_THROW(naked_srv.reset(new NakedDhcpv4Srv(0)));
    EXPECT_TRUE(naked_srv->getServerID());
}

// This test verifies that the destination address of the response
// message is set to giaddr, when giaddr is set to non-zero address
// in the received message.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressRelay) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create the instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));
    // Set the giaddr to non-zero address as if it was relayed.
    req->setGiaddr(IOAddress("192.0.2.1"));
    // Set ciaddr to zero. This simulates the client which applies
    // for the new lease.
    req->setCiaddr(IOAddress("0.0.0.0"));
    // Clear broadcast flag.
    req->setFlags(0x0000);

    // Create a response packet. Assume that the new lease have
    // been created and new address allocated. This address is
    // stored in yiaddr field.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    resp->setYiaddr(IOAddress("192.0.2.100"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // This function never throws.
    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Now the destination address should be relay's address.
    EXPECT_EQ("192.0.2.1", resp->getRemoteAddr().toText());

    // Let's do another test and set other fields: ciaddr and
    // flags. By doing it, we want to make sure that the relay
    // address will take precedence.
    req->setGiaddr(IOAddress("192.0.2.50"));
    req->setCiaddr(IOAddress("192.0.2.11"));
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    resp->setYiaddr(IOAddress("192.0.2.100"));
    // Clear remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Response should be sent back to the relay address.
    EXPECT_EQ("192.0.2.50", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to ciaddr when giaddr is set to zero and the ciaddr is set to
// non-zero address in the received message. This is the case when the
// client is in Renew or Rebind state.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressRenewRebind) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Set ciaddr to non-zero address. The response should be sent to this
    // address as the client is in renewing or rebinding state (it is fully
    // configured).
    req->setCiaddr(IOAddress("192.0.2.15"));
    // Let's configure broadcast flag. It should be ignored because
    // we are responding directly to the client having an address
    // and trying to extend his lease. Broadcast flag is only used
    // when new lease is acquired and server must make a decision
    // whether to unicast the response to the acquired address or
    // broadcast it.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create a response.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    // Let's extend the lease for the client in such a way that
    // it will actually get different address. The response
    // should not be sent to this address but rather to ciaddr
    // as client still have ciaddr configured.
    resp->setYiaddr(IOAddress("192.0.2.13"));
    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Check that server responds to ciaddr
    EXPECT_EQ("192.0.2.15", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set correctly when giaddr and ciaddr is zeroed in the received message
// and the new lease is acquired. The lease address is carried in the
// response message in the yiaddr field. In this case destination address
// of the response should be set to yiaddr if server supports direct responses
// to the client which doesn't have an address yet or broadcast if the server
// doesn't support direct responses.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressSelect) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));

    // Let's clear the broadcast flag.
    req->setFlags(0);

    // Create a response.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.2.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // When running unit tests, the IfaceMgr is using the default Packet
    // Filtering class, PktFilterInet. This class does not support direct
    // responses to clients without address assigned. When giaddr and ciaddr
    // are zero and client has just got new lease, the assigned address is
    // carried in yiaddr. In order to send this address to the client,
    // server must broadcast its response.
    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Check that the response is sent to broadcast address as the
    // server doesn't have capability to respond directly.
    EXPECT_EQ("255.255.255.255", resp->getRemoteAddr().toText());

    // We also want to test the case when the server has capability to
    // respond directly to the client which is not configured. Server
    // makes decision whether it responds directly or broadcast its
    // response based on the capability reported by IfaceMgr. In order
    // to set this capability we have to provide a dummy Packet Filter
    // class which would report the support for direct responses.
    // This class is called PktFilterTest.
    IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterTest()));

    // Now we expect that the server will send its response to the
    // address assigned for the client.
    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    EXPECT_EQ("192.0.2.13", resp->getRemoteAddr().toText());
}

// This test verifies that the destination address of the response message
// is set to broadcast address when client set broadcast flag in its
// query. Client sets this flag to indicate that it can't receive direct
// responses from the server when it doesn't have its interface configured.
// Server must respect broadcast flag.
TEST_F(Dhcpv4SrvTest, adjustRemoteAddressBroadcast) {
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Create instance of the incoming packet.
    boost::shared_ptr<Pkt4> req(new Pkt4(DHCPDISCOVER, 1234));

    // Clear giaddr to simulate direct packet.
    req->setGiaddr(IOAddress("0.0.0.0"));
    // Clear client address as it hasn't got any address configured yet.
    req->setCiaddr(IOAddress("0.0.0.0"));

    // Let's set the broadcast flag.
    req->setFlags(Pkt4::FLAG_BROADCAST_MASK);

    // Create a response.
    boost::shared_ptr<Pkt4> resp(new Pkt4(DHCPOFFER, 1234));
    // Assign some new address for this client.
    resp->setYiaddr(IOAddress("192.0.2.13"));

    // Clear the remote address.
    resp->setRemoteAddr(IOAddress("0.0.0.0"));

    // When running unit tests, the IfaceMgr is using the default Packet
    // Filtering class, PktFilterInet. This class does not support direct
    // responses to the clients without address assigned. If giaddr and
    // ciaddr are zero and client has just got the new lease, the assigned
    // address is carried in yiaddr. In order to send this address to the
    // client, server must send the response to the broadcast address when
    // direct response is not supported. This conflicts with the purpose
    // of this test which is supposed to verify that responses are sent
    // to broadcast address only, when broadcast flag is set. Therefore,
    // in order to simulate that direct responses are supported we have
    // to replace the default packet filtering class with a dummy class
    // which reports direct response capability.
    IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterTest()));

    ASSERT_NO_THROW(srv->adjustRemoteAddr(req, resp));

    // Server must repond to broadcast address when client desired that
    // by setting the broadcast flag in its request.
    EXPECT_EQ("255.255.255.255", resp->getRemoteAddr().toText());
}

// Verifies that DISCOVER message can be processed correctly,
// that the OFFER message generated in response is valid and
// contains necessary options.
//
// Note: this test focuses on the packet correctness. There
// are other tests that verify correctness of the allocation
// engine. See DiscoverBasic, DiscoverHint, DiscoverNoClientId
// and DiscoverInvalidHint.
TEST_F(Dhcpv4SrvTest, processDiscover) {
    testDiscoverRequest(DHCPDISCOVER);
}

// Verifies that REQUEST message can be processed correctly,
// that the OFFER message generated in response is valid and
// contains necessary options.
//
// Note: this test focuses on the packet correctness. There
// are other tests that verify correctness of the allocation
// engine. See DiscoverBasic, DiscoverHint, DiscoverNoClientId
// and DiscoverInvalidHint.
TEST_F(Dhcpv4SrvTest, processRequest) {
    testDiscoverRequest(DHCPREQUEST);
}

TEST_F(Dhcpv4SrvTest, processRelease) {
    NakedDhcpv4Srv srv;
    Pkt4Ptr pkt(new Pkt4(DHCPRELEASE, 1234));

    // Should not throw
    EXPECT_NO_THROW(srv.processRelease(pkt));
}

TEST_F(Dhcpv4SrvTest, processDecline) {
    NakedDhcpv4Srv srv;
    Pkt4Ptr pkt(new Pkt4(DHCPDECLINE, 1234));

    // Should not throw
    EXPECT_NO_THROW(srv.processDecline(pkt));
}

TEST_F(Dhcpv4SrvTest, processInform) {
    NakedDhcpv4Srv srv;
    Pkt4Ptr pkt(new Pkt4(DHCPINFORM, 1234));

    // Should not throw
    EXPECT_NO_THROW(srv.processInform(pkt));

    // Should return something
    EXPECT_TRUE(srv.processInform(pkt));

    // @todo Implement more reasonable tests before starting
    // work on processSomething() method.
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

// Checks if hooks are registered properly.
TEST_F(Dhcpv4SrvTest, Hooks) {
    NakedDhcpv4Srv srv(0);

    // check if appropriate hooks are registered
    int hook_index_pkt4_received = -1;
    int hook_index_select_subnet = -1;
    int hook_index_pkt4_send     = -1;

    // check if appropriate indexes are set
    EXPECT_NO_THROW(hook_index_pkt4_received = ServerHooks::getServerHooks()
                    .getIndex("pkt4_receive"));
    EXPECT_NO_THROW(hook_index_select_subnet = ServerHooks::getServerHooks()
                    .getIndex("subnet4_select"));
    EXPECT_NO_THROW(hook_index_pkt4_send     = ServerHooks::getServerHooks()
                    .getIndex("pkt4_send"));

    EXPECT_TRUE(hook_index_pkt4_received > 0);
    EXPECT_TRUE(hook_index_select_subnet > 0);
    EXPECT_TRUE(hook_index_pkt4_send > 0);
}

    // a dummy MAC address
    const uint8_t dummyMacAddr[] = {0, 1, 2, 3, 4, 5};

    // A dummy MAC address, padded with 0s
    const uint8_t dummyChaddr[16] = {0, 1, 2, 3, 4, 5, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0 };

    // Let's use some creative test content here (128 chars + \0)
    const uint8_t dummyFile[] = "Lorem ipsum dolor sit amet, consectetur "
        "adipiscing elit. Proin mollis placerat metus, at "
        "lacinia orci ornare vitae. Mauris amet.";

    // Yet another type of test content (64 chars + \0)
    const uint8_t dummySname[] = "Lorem ipsum dolor sit amet, consectetur "
        "adipiscing elit posuere.";

/// @brief a class dedicated to Hooks testing in DHCPv4 server
///
/// This class has a number of static members, because each non-static
/// method has implicit 'this' parameter, so it does not match callout
/// signature and couldn't be registered. Furthermore, static methods
/// can't modify non-static members (for obvious reasons), so many
/// fields are declared static. It is still better to keep them as
/// one class rather than unrelated collection of global objects.
class HooksDhcpv4SrvTest : public Dhcpv4SrvTest {

public:

    /// @brief creates Dhcpv4Srv and prepares buffers for callouts
    HooksDhcpv4SrvTest() {

        // Allocate new DHCPv6 Server
        srv_ = new NakedDhcpv4Srv(0);

        // clear static buffers
        resetCalloutBuffers();
    }

    /// @brief destructor (deletes Dhcpv4Srv)
    virtual ~HooksDhcpv4SrvTest() {
        delete srv_;
    }

    /// @brief creates an option with specified option code
    ///
    /// This method is static, because it is used from callouts
    /// that do not have a pointer to HooksDhcpv4SSrvTest object
    ///
    /// @param option_code code of option to be created
    ///
    /// @return pointer to create option object
    static OptionPtr createOption(uint16_t option_code) {

        char payload[] = {
            0xa, 0xb, 0xc, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14
        };

        OptionBuffer tmp(payload, payload + sizeof(payload));
        return OptionPtr(new Option(Option::V4, option_code, tmp));
    }

    /// @brief Generates test packet.
    ///
    /// Allocates and generates on-wire buffer that represents test packet, with all
    /// fixed fields set to non-zero values.  Content is not always reasonable.
    ///
    /// See generateTestPacket1() function that returns exactly the same packet as
    /// Pkt4 object.
    ///
    /// @return pointer to allocated Pkt4 object
    // Returns a vector containing a DHCPv4 packet header.
    Pkt4Ptr
    generateSimpleDiscover() {

        // That is only part of the header. It contains all "short" fields,
        // larger fields are constructed separately.
        uint8_t hdr[] = {
            1, 6, 6, 13,            // op, htype, hlen, hops,
            0x12, 0x34, 0x56, 0x78, // transaction-id
            0, 42, 0x80, 0x00,      // 42 secs, BROADCAST flags
            192, 0, 2, 1,           // ciaddr
            1, 2, 3, 4,             // yiaddr
            192, 0, 2, 255,         // siaddr
            255, 255, 255, 255,     // giaddr
        };

        // Initialize the vector with the header fields defined above.
        vector<uint8_t> buf(hdr, hdr + sizeof(hdr));

        // Append the large header fields.
        copy(dummyChaddr, dummyChaddr + Pkt4::MAX_CHADDR_LEN, back_inserter(buf));
        copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN, back_inserter(buf));
        copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN, back_inserter(buf));

        // Should now have all the header, so check.  The "static_cast" is used
        // to get round an odd bug whereby the linker appears not to find the
        // definition of DHCPV4_PKT_HDR_LEN if it appears within an EXPECT_EQ().
        EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), buf.size());

        // Add magic cookie
        buf.push_back(0x63);
        buf.push_back(0x82);
        buf.push_back(0x53);
        buf.push_back(0x63);

        // Add message type DISCOVER
        buf.push_back(static_cast<uint8_t>(DHO_DHCP_MESSAGE_TYPE));
        buf.push_back(1); // length (just one byte)
        buf.push_back(static_cast<uint8_t>(DHCPDISCOVER));

        return (Pkt4Ptr(new Pkt4(&buf[0], buf.size())));
    }

    /// test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt4_receive");

        callout_handle.getArgument("query4", callback_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// test callback that changes client-id value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_change_clientid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // get rid of the old client-id
        pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER);

        // add a new option
        pkt->addOption(createOption(DHO_DHCP_CLIENT_IDENTIFIER));

        // carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// test callback that deletes client-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_delete_clientid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // get rid of the old client-id
        pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER);

        // carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_skip(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        callout_handle.setSkip(true);

        // carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt4 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt4_send");

        callout_handle.getArgument("response4", callback_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    // Test callback that changes server-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_change_serverid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // get rid of the old server-id
        pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER);

        // add a new option
        pkt->addOption(createOption(DHO_DHCP_SERVER_IDENTIFIER));

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// test callback that deletes server-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_delete_serverid(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // get rid of the old client-id
        pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER);

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_skip(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        callout_handle.setSkip(true);

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// Test callback that stores received callout name and subnet4 values
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("subnet4_select");

        callout_handle.getArgument("query4", callback_pkt4_);
        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("subnet4collection", callback_subnet4collection_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that picks the other subnet if possible.
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_different_subnet_callout(CalloutHandle& callout_handle) {

        // Call the basic calllout to record all passed values
        subnet4_select_callout(callout_handle);

        Subnet4Collection subnets;
        Subnet4Ptr subnet;
        callout_handle.getArgument("subnet4", subnet);
        callout_handle.getArgument("subnet4collection", subnets);

        // Let's change to a different subnet
        if (subnets.size() > 1) {
            subnet = subnets[1]; // Let's pick the other subnet
            callout_handle.setArgument("subnet4", subnet);
        }

        return (0);
    }

    /// resets buffers used to store data received by callouts
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_pkt4_.reset();
        callback_subnet4_.reset();
        callback_subnet4collection_ = NULL;
        callback_argument_names_.clear();
    }

    /// pointer to Dhcpv4Srv that is used in tests
    NakedDhcpv4Srv* srv_;

    // The following fields are used in testing pkt4_receive_callout

    /// String name of the received callout
    static string callback_name_;

    /// Pkt4 structure returned in the callout
    static Pkt4Ptr callback_pkt4_;

    /// Pointer to a subnet received by callout
    static Subnet4Ptr callback_subnet4_;

    /// A list of all available subnets (received by callout)
    static const Subnet4Collection* callback_subnet4collection_;

    /// A list of all received arguments
    static vector<string> callback_argument_names_;
};

// The following fields are used in testing pkt4_receive_callout.
// See fields description in the class for details
string HooksDhcpv4SrvTest::callback_name_;
Pkt4Ptr HooksDhcpv4SrvTest::callback_pkt4_;
Subnet4Ptr HooksDhcpv4SrvTest::callback_subnet4_;
const Subnet4Collection* HooksDhcpv4SrvTest::callback_subnet4collection_;
vector<string> HooksDhcpv4SrvTest::callback_argument_names_;


// Checks if callouts installed on pkt4_received are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "pkt4_receive".
TEST_F(HooksDhcpv4SrvTest, simple_pkt4_receive) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt4_receive", callback_name_);

    // check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == sol.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query4"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on pkt4_received is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv4SrvTest, valueChange_pkt4_receive) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_change_clientid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server did send a reposonce
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(DHO_DHCP_CLIENT_IDENTIFIER);
    EXPECT_TRUE(clientid->equal(expected));
}

// Checks if callouts installed on pkt4_received is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv4SrvTest, deleteClientId_pkt4_receive) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_delete_clientid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not send a response
    ASSERT_EQ(0, srv_->fake_sent_.size());
}

// Checks if callouts installed on pkt4_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, skip_pkt4_receive) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_skip));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());
}


// Checks if callouts installed on pkt4_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv4SrvTest, simple_pkt4_send) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt4_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("response4"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on pkt4_send is able to change
// the values and the packet sent contains those changes
TEST_F(HooksDhcpv4SrvTest, valueChange_pkt4_send) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_change_serverid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server did send a reposonce
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(DHO_DHCP_SERVER_IDENTIFIER);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(DHO_DHCP_SERVER_IDENTIFIER);
    EXPECT_TRUE(clientid->equal(expected));
}

// Checks if callouts installed on pkt4_send is able to delete
// existing options and that server applies those changes. In particular,
// we are trying to send a packet without server-id. The packet should
// be sent
TEST_F(HooksDhcpv4SrvTest, deleteServerId_pkt4_send) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_delete_serverid));

    // Let's create a simple DISCOVER
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server indeed sent a malformed ADVERTISE
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get that ADVERTISE
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure that it does not have server-id
    EXPECT_FALSE(adv->getOption(DHO_DHCP_SERVER_IDENTIFIER));
}

// Checks if callouts installed on pkt4_skip is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, skip_pkt4_send) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_skip));

    // Let's create a simple REQUEST
    Pkt4Ptr sol = Pkt4Ptr(generateSimpleDiscover());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());
}

// This test checks if subnet4_select callout is triggered and reports
// valid parameters
TEST_F(HooksDhcpv4SrvTest, subnet4_select) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_callout));

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"2001:db8:1::/44\" ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pool\": [ \"2001:db8:2::/44\" ],"
        "    \"subnet\": \"2001:db8:2::/48\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Prepare discover packet. Server should select first subnet for it
    Pkt4Ptr sol = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr adv = srv_->processDiscover(sol);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("subnet4_select", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt4_.get() == sol.get());

    const Subnet4Collection* exp_subnets = CfgMgr::instance().getSubnets4();

    // The server is supposed to pick the first subnet, because of matching
    // interface. Check that the value is reported properly.
    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(exp_subnets->front().get(), callback_subnet4_.get());

    // Server is supposed to report two subnets
    ASSERT_EQ(exp_subnets->size(), callback_subnet4collection_->size());

    // Compare that the available subnets are reported as expected
    EXPECT_TRUE((*exp_subnets)[0].get() == (*callback_subnet4collection_)[0].get());
    EXPECT_TRUE((*exp_subnets)[1].get() == (*callback_subnet4collection_)[1].get());
}

// This test checks if callout installed on subnet4_select hook point can pick
// a different subnet.
TEST_F(HooksDhcpv4SrvTest, subnet_select_change) {

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_different_subnet_callout));

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"2001:db8:1::/44\" ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pool\": [ \"2001:db8:2::/44\" ],"
        "    \"subnet\": \"2001:db8:2::/48\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Prepare discover packet. Server should select first subnet for it
    Pkt4Ptr sol = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr adv = srv_->processDiscover(sol);

    // check if we get response at all
    ASSERT_TRUE(adv);

    // The response should have an address from second pool, so let's check it
    IOAddress addr = adv->getYiaddr();
    EXPECT_NE("0.0.0.0", addr.toText());

    // Get all subnets and use second subnet for verification
    const Subnet4Collection* subnets = CfgMgr::instance().getSubnets4();
    ASSERT_EQ(2, subnets->size());

    // Advertised address must belong to the second pool (in subnet's range,
    // in dynamic pool)
    EXPECT_TRUE((*subnets)[1]->inRange(addr));
    EXPECT_TRUE((*subnets)[1]->inPool(addr));
}



} // end of anonymous namespace
