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
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease.h>
#include <asiolink/io_address.h>
#include <config/ccsession.h>

namespace isc {
namespace dhcp {
namespace test {

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

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_TEST_UTILS_H
