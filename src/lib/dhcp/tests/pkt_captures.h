// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_CAPTURES_H
#define PKT_CAPTURES_H

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

namespace isc {
namespace dhcp {
namespace test {

class PktCaptures {
public:

    /// @brief returns captured DISCOVER that went through a relay
    ///
    /// See method code for a detailed explanation. This is a discover from
    /// docsis3.0 device (Cable Modem)
    ///
    /// @return relayed DISCOVER
    static isc::dhcp::Pkt4Ptr captureRelayedDiscover();

    /// @brief returns captured DISCOVER that went through a relay
    ///
    /// See method code for a detailed explanation. This is a discover from
    /// eRouter1.0 device (CPE device integrated with cable modem)
    ///
    /// @return relayed DISCOVER
    static isc::dhcp::Pkt4Ptr captureRelayedDiscover2();

    /// @brief returns captured DISCOVER that went through a relay
    ///
    /// See method code for a detailed explanation. This is a discover from
    /// a buggy relay device with a bad suboption.
    ///
    /// @return relayed DISCOVER
    static isc::dhcp::Pkt4Ptr captureBadRelayedDiscover();

    /// @brief returns captured DISCOVER that contains a valid VIVSO option
    ///
    /// See method code for a detailed explanation.
    ///
    /// @return relayed DISCOVER
    static isc::dhcp::Pkt4Ptr discoverWithValidVIVSO();

    /// @brief returns captured DISCOVER that contains a truncated VIVSO option
    ///
    /// See method code for a detailed explanation.
    ///
    /// @return relayed DISCOVER
    static isc::dhcp::Pkt4Ptr discoverWithTruncatedVIVSO();

    /// @brief returns captured DISCOVER from Genexis hardware.
    ///
    /// This device in uncommon, because it doesn't send VIVSO in Dicover, but
    /// expects one in Offer.
    /// @return DISCOVER.
    static isc::dhcp::Pkt4Ptr discoverGenexis();

    // see pkt_captures6.cc for descriptions
    // The descriptions are too large and too closely related to the
    // code, so it is kept in .cc rather than traditionally in .h
    static isc::dhcp::Pkt6Ptr captureSimpleSolicit();
    static isc::dhcp::Pkt6Ptr captureRelayedSolicit();
    static isc::dhcp::Pkt6Ptr captureDocsisRelayedSolicit();
    static isc::dhcp::Pkt6Ptr captureeRouterRelayedSolicit();
    static isc::dhcp::Pkt6Ptr captureCableLabsShortVendorClass();
    static isc::dhcp::Pkt6Ptr captureRelayed2xRSOO();
    static isc::dhcp::Pkt6Ptr captureSolicitWithVIVSO();
    static isc::dhcp::Pkt6Ptr captureSolicitWithTruncatedVIVSO();

protected:
    /// @brief Auxiliary method that sets Pkt6 fields
    ///
    /// Used to reconstruct captured packets. Sets UDP ports, interface names,
    /// and other fields to some believable values.
    /// @param pkt packet that will have its fields set
    static void captureSetDefaultFields(const isc::dhcp::Pkt6Ptr& pkt);


    /// @brief generates a DHCPv4 packet based on provided hex string
    ///
    /// @return created packet
    static isc::dhcp::Pkt4Ptr packetFromCapture(const std::string& hex_string);

    /// @brief sets default fields in a captured packet
    ///
    /// Sets UDP ports, addresses and interface.
    ///
    /// @param pkt packet to have default fields set
    static void captureSetDefaultFields(const isc::dhcp::Pkt4Ptr& pkt);
};

}; // end of namespace isc::dhcp::test
}; // end of namespace isc::dhcp
}; // end of namespace isc

#endif
