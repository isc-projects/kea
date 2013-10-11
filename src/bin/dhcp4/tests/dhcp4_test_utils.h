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

/// @file   dhcp4_test_utils.h
///
/// @brief  This file contains utility classes used for DHCPv4 server testing

#ifndef DHCP4_TEST_UTILS_H
#define DHCP4_TEST_UTILS_H

#include <gtest/gtest.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease.h>
#include <dhcp4/dhcp4_srv.h>
#include <asiolink/io_address.h>
#include <config/ccsession.h>
#include <list>

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

    /// @brief Reports 'direct response' capability.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const {
        return (true);
    }

    /// Does nothing.
    virtual int openSocket(const Iface&, const isc::asiolink::IOAddress&,
                           const uint16_t, const bool, const bool) {
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
    Dhcpv4SrvTest();

    /// @brief destructor
    virtual ~Dhcpv4SrvTest() {
    }

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

    /// @brief Check that requested options are present.
    ///
    /// @param pkt packet to be checked.
    void optionsCheck(const Pkt4Ptr& pkt);

    /// @brief generates client-id option
    ///
    /// Generate client-id option of specified length
    /// Ids with different lengths are sufficent to generate
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
    /// @param t1_mandatory is T1 mandatory?
    /// @param t2_mandatory is T2 mandatory?
    void checkAddressParams(const Pkt4Ptr& rsp, const SubnetPtr subnet,
                            bool t1_mandatory = false,
                            bool t2_mandatory = false);

    /// @brief Basic checks for generated response (message type and trans-id).
    ///
    /// @param rsp response packet to be validated
    /// @param expected_message_type expected message type
    /// @param expected_transid expected transaction-id
    void checkResponse(const Pkt4Ptr& rsp, uint8_t expected_message_type,
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
    /// @param rsp response packet to be validated
    /// @param expected_clientid expected value of client-id
    void checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid);

    /// @brief sets default fields in a captured packet
    ///
    /// Sets UDP ports, addresses and interface.
    ///
    /// @param pkt packet to have default fields set
    void captureSetDefaultFields(const Pkt4Ptr& pkt);

    /// @brief returns captured DISCOVER that went through a relay
    ///
    /// See method code for a detailed explanation.
    ///
    /// @return relayed DISCOVER
    Pkt4Ptr captureRelayedDiscover();

    /// @brief generates a DHCPv4 packet based on provided hex string
    ///
    /// @return created packet
    Pkt4Ptr packetFromCapture(const std::string& hex_string);

    /// @brief Tests if Discover or Request message is processed correctly
    ///
    /// @param msg_type DHCPDISCOVER or DHCPREQUEST
    void testDiscoverRequest(const uint8_t msg_type);

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

    // Name of a valid network interface
    std::string valid_iface_;
};

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

    /// @brief packets we pretend to receive
    ///
    /// Instead of setting up sockets on interfaces that change between OSes, it
    /// is much easier to fake packet reception. This is a list of packets that
    /// we pretend to have received. You can schedule new packets to be received
    /// using fakeReceive() and NakedDhcpv4Srv::receivePacket() methods.
    std::list<Pkt4Ptr> fake_received_;

    std::list<Pkt4Ptr> fake_sent_;

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

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_TEST_UTILS_H
