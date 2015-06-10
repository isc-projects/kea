// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @file   dhcp4_test_utils.h
///
/// @brief  This file contains utility classes used for DHCPv4 server testing

#ifndef DHCP4_TEST_UTILS_H
#define DHCP4_TEST_UTILS_H

#include <gtest/gtest.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp4/dhcp4_srv.h>
#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <list>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Dummy Packet Filtering class.
///
/// This class reports capability to respond directly to the client which
/// doesn't have address configured yet.
///
/// All packet and socket handling functions do nothing because they are not
/// used in unit tests.
class PktFilterTest : public PktFilter {
public:

    /// @brief Constructor.
    ///
    /// Sets the 'direct response' capability to true.
    PktFilterTest()
        : direct_resp_supported_(true) {
    }

    /// @brief Reports 'direct response' capability.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const {
        return (direct_resp_supported_);
    }

    /// Does nothing.
    virtual SocketInfo openSocket(Iface&,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port, const bool, const bool) {
        return (SocketInfo(addr, port, 0));
    }

    /// Does nothing.
    virtual Pkt4Ptr receive(Iface&, const SocketInfo&) {
        return Pkt4Ptr();
    }

    /// Does nothing.
    virtual int send(const Iface&, uint16_t, const Pkt4Ptr&) {
        return (0);
    }

    /// @brief Holds a boolean value which indicates whether direct response
    /// capability is supported (true) or not (false).
    bool direct_resp_supported_;

};

typedef boost::shared_ptr<PktFilterTest> PktFilterTestPtr;

/// @brief "Naked" DHCPv4 server, exposes internal fields
class NakedDhcpv4Srv: public Dhcpv4Srv {
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
    /// Enabling these modes requires root privileges so they must be
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
        : Dhcpv4Srv(port, false, false) {
        // Create a default lease database backend.
        std::string dbconfig = "type=memfile universe=4 persist=false";
        isc::dhcp::LeaseMgrFactory::create(dbconfig);
        // Create fixed server id.
        server_id_.reset(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                            asiolink::IOAddress("192.0.3.1")));
    }

    /// @brief Returns fixed server identifier assigned to the naked server
    /// instance.
    OptionPtr getServerID() const {
        return (server_id_);
    }

    /// @brief fakes packet reception
    /// @param timeout ignored
    ///
    /// The method receives all packets queued in receive queue, one after
    /// another. Once the queue is empty, it initiates the shutdown procedure.
    ///
    /// See fake_received_ field for description
    virtual Pkt4Ptr receivePacket(int /*timeout*/) {

        // If there is anything prepared as fake incoming traffic, use it
        if (!fake_received_.empty()) {
            Pkt4Ptr pkt = fake_received_.front();
            fake_received_.pop_front();
            return (pkt);
        }

        // If not, just trigger shutdown and return immediately
        shutdown();
        return (Pkt4Ptr());
    }

    /// @brief fake packet sending
    ///
    /// Pretend to send a packet, but instead just store it in fake_send_ list
    /// where test can later inspect server's response.
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

    /// @brief Dummy server identifier option used by various tests.
    OptionPtr server_id_;

    /// @brief packets we pretend to receive
    ///
    /// Instead of setting up sockets on interfaces that change between OSes, it
    /// is much easier to fake packet reception. This is a list of packets that
    /// we pretend to have received. You can schedule new packets to be received
    /// using fakeReceive() and NakedDhcpv4Srv::receivePacket() methods.
    std::list<Pkt4Ptr> fake_received_;

    std::list<Pkt4Ptr> fake_sent_;

    using Dhcpv4Srv::adjustIfaceData;
    using Dhcpv4Srv::appendServerID;
    using Dhcpv4Srv::processDiscover;
    using Dhcpv4Srv::processRequest;
    using Dhcpv4Srv::processRelease;
    using Dhcpv4Srv::processDecline;
    using Dhcpv4Srv::processInform;
    using Dhcpv4Srv::processClientName;
    using Dhcpv4Srv::computeDhcid;
    using Dhcpv4Srv::createNameChangeRequests;
    using Dhcpv4Srv::acceptServerId;
    using Dhcpv4Srv::sanityCheck;
    using Dhcpv4Srv::srvidToString;
    using Dhcpv4Srv::unpackOptions;
    using Dhcpv4Srv::classifyPacket;
    using Dhcpv4Srv::accept;
    using Dhcpv4Srv::acceptMessageType;
    using Dhcpv4Srv::selectSubnet;
    using Dhcpv4Srv::VENDOR_CLASS_PREFIX;
    using Dhcpv4Srv::shutdown_;
    using Dhcpv4Srv::alloc_engine_;
};

class Dhcpv4SrvTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// Initializes common objects used in many tests.
    /// Also sets up initial configuration in CfgMgr.
    Dhcpv4SrvTest();

    /// @brief destructor
    virtual ~Dhcpv4SrvTest();

    /// @brief Add 'Parameter Request List' option to the packet.
    ///
    /// This function adds PRL option comprising the following option codes:
    /// - 5 - Name Server
    /// - 15 - Domain Name
    /// - 7 - Log Server
    /// - 8 - Quotes Server
    /// - 9 - LPR Server
    ///
    /// @param pkt packet to add PRL option to.
    void addPrlOption(Pkt4Ptr& pkt);

    /// @brief Configures options being requested in the PRL option.
    ///
    /// The lpr-servers option is NOT configured here although it is
    /// added to the 'Parameter Request List' option in the
    /// \ref addPrlOption. When requested option is not configured
    /// the server should not return it in its response. The goal
    /// of not configuring the requested option is to verify that
    /// the server will not return it.
    void configureRequestedOptions();

    /// @brief checks that the response matches request
    /// @param q query (client's message)
    /// @param a answer (server's message)
    void messageCheck(const Pkt4Ptr& q, const Pkt4Ptr& a);

    /// @brief Check that certain basic (always added when lease is acquired)
    /// are present in a message.
    ///
    /// @param pkt A message to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult basicOptionsPresent(const Pkt4Ptr& pkt);

    /// @brief Check that certain basic (always added when lease is acquired)
    /// are not present.
    ///
    /// @param pkt A packet to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult noBasicOptions(const Pkt4Ptr& pkt);

    /// @brief Check that certain requested options are present in the message.
    ///
    /// @param pkt A message to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult requestedOptionsPresent(const Pkt4Ptr& pkt);

    /// @brief Check that certain options (requested with PRL option)
    /// are not present.
    ///
    /// @param pkt A packet to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult noRequestedOptions(const Pkt4Ptr& pkt);

    /// @brief generates client-id option
    ///
    /// Generate client-id option of specified length
    /// Ids with different lengths are sufficient to generate
    /// unique ids. If more fine grained control is required,
    /// tests generate client-ids on their own.
    /// Sets client_id_ field.
    /// @param size size of the client-id to be generated
    OptionPtr generateClientId(size_t size = 4);

    /// @brief generate hardware address
    ///
    /// @param size size of the generated MAC address
    /// @param pointer to Hardware Address object
    HWAddrPtr generateHWAddr(size_t size = 6);

    /// Check that address was returned from proper range, that its lease
    /// lifetime is correct, that T1 and T2 are returned properly
    /// @param rsp response to be checked
    /// @param subnet subnet that should be used to verify assigned address
    ///        and options
    /// @param t1_present check that t1 must be present (true) or must not be
    /// present (false)
    /// @param t2_present check that t2 must be present (true) or must not be
    /// present (false)
    void checkAddressParams(const Pkt4Ptr& rsp, const SubnetPtr subnet,
                            bool t1_present = false,
                            bool t2_present = false);

    /// @brief Basic checks for generated response (message type and trans-id).
    ///
    /// @param rsp response packet to be validated
    /// @param expected_message_type expected message type
    /// @param expected_transid expected transaction-id
    void checkResponse(const Pkt4Ptr& rsp, int expected_message_type,
                       uint32_t expected_transid);

    /// @brief Checks if the lease sent to client is present in the database
    ///
    /// @param rsp response packet to be validated
    /// @param client_id expected client-identifier (or NULL)
    /// @param HWAddr expected hardware address (not used now)
    /// @param expected_addr expected address
    Lease4Ptr checkLease(const Pkt4Ptr& rsp, const OptionPtr& client_id,
                         const HWAddrPtr&,
                         const isc::asiolink::IOAddress& expected_addr);

    /// @brief Checks if server response (OFFER, ACK, NAK) includes proper server-id
    /// @param rsp response packet to be validated
    /// @param expected_srvid expected value of server-id
    void checkServerId(const Pkt4Ptr& rsp, const OptionPtr& expected_srvid);

    /// @brief Checks if server response (OFFER, ACK, NAK) includes proper client-id
    ///
    /// This method follows values reported by CfgMgr in echoClientId() method.
    /// Depending on its configuration, the client-id is either mandatory or
    /// forbidden to appear in the response.
    ///
    /// @param rsp response packet to be validated
    /// @param expected_clientid expected value of client-id
    void checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid);

    /// @brief Create packet from output buffer of another packet.
    ///
    /// This function creates a packet using an output buffer from another
    /// packet. This imitates reception of a packet from the wire. The
    /// unpack function is then called to parse packet contents and to
    /// create a collection of the options carried by this packet.
    ///
    /// This function is useful for unit tests which verify that the received
    /// packet is parsed correctly. In those cases it is usually inappropriate
    /// to create an instance of the packet, add options, set packet
    /// fields and use such packet as an input to processDiscover or
    /// processRequest function. This is because, such a packet has certain
    /// options already initialized and there is no way to verify that they
    /// have been initialized when packet instance was created or wire buffer
    /// processing. By creating a packet from the buffer we guarantee that the
    /// new packet is entirely initialized during wire data parsing.
    ///
    /// @param src_pkt A source packet, to be copied.
    /// @param [out] dst_pkt A destination packet.
    ///
    /// @return assertion result indicating if a function completed with
    /// success or failure.
    static ::testing::AssertionResult
    createPacketFromBuffer(const isc::dhcp::Pkt4Ptr& src_pkt,
                           isc::dhcp::Pkt4Ptr& dst_pkt);

    /// @brief Tests if Discover or Request message is processed correctly
    ///
    /// This test verifies that the Parameter Request List option is handled
    /// correctly, i.e. it checks that certain options are present in the
    /// server's response when they are requested and that they are not present
    /// when they are not requested or NAK occurs.
    ///
    /// @todo We need an additional test for PRL option using real traffic
    /// capture.
    ///
    /// @param msg_type DHCPDISCOVER or DHCPREQUEST
    void testDiscoverRequest(const uint8_t msg_type);

    /// @brief Runs DHCPv4 configuration from the JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    void configure(const std::string& config, const bool commit = true);

    /// @brief Configure specified DHCP server using JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param srv Instance of the server to be configured.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    void configure(const std::string& config, NakedDhcpv4Srv& srv,
                   const bool commit = true);

    /// @brief Pretents a packet of specified type was received.
    ///
    /// Instantiates fake network interfaces, configures passed Dhcpv4Srv,
    /// then creates a message of specified type and sends it to the
    /// server and then checks whether expected statstics were set
    /// appropriately.
    ///
    /// @param srv the DHCPv4 server to be used
    /// @param config JSON configuration to be used
    /// @param pkt_type type of the packet to be faked
    /// @param stat_name name of the expected statistic
    void pretendReceivingPkt(NakedDhcpv4Srv& srv, const std::string& config,
                             uint8_t pkt_type, const std::string& stat_name);

    /// @brief Create @c Dhcpv4Exchange from client's query.
    Dhcpv4Exchange createExchange(const Pkt4Ptr& query);

    /// @brief This function cleans up after the test.
    virtual void TearDown();

    /// @brief A subnet used in most tests
    Subnet4Ptr subnet_;

    /// @brief A pool used in most tests
    Pool4Ptr pool_;

    /// @brief A client-id used in most tests
    ClientIdPtr client_id_;

    int rcode_;

    isc::data::ConstElementPtr comment_;

    /// @brief Server object under test.
    NakedDhcpv4Srv srv_;
};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_TEST_UTILS_H
