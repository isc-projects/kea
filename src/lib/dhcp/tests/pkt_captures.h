// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

namespace isc {
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

    // see pkt_captures6.cc for descriptions
    // The descriptions are too large and too closely related to the
    // code, so it is kept in .cc rather than traditionally in .h
    static isc::dhcp::Pkt6Ptr captureSimpleSolicit();
    static isc::dhcp::Pkt6Ptr captureRelayedSolicit();
    static isc::dhcp::Pkt6Ptr captureDocsisRelayedSolicit();
    static isc::dhcp::Pkt6Ptr captureeRouterRelayedSolicit();
    static isc::dhcp::Pkt6Ptr captureCableLabsShortVendorClass();
    static isc::dhcp::Pkt6Ptr captureRelayed2xRSOO();

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

};
};
