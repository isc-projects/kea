// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HWADDR_H
#define HWADDR_H

#include <vector>
#include <stdint.h>
#include <stddef.h>
#include <dhcp/dhcp4.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Hardware type that represents information from DHCPv4 packet
struct HWAddr {
public:

    /// @brief Size of an ethernet hardware address.
    static const size_t ETHERNET_HWADDR_LEN = 6;

    /// @brief Maximum size of a hardware address.
    static const size_t MAX_HWADDR_LEN = 20;

    /// @defgroup hw_sources Specifies where a given MAC/hardware address was
    ///                      obtained.
    ///
    /// @brief The list covers all possible MAC/hw address sources.
    ///
    /// @{

    /// Not really a type, only used in getMAC() calls.
    static const uint32_t HWADDR_SOURCE_ANY;

    /// Used when actual origin is not known, e.g. when reading from a
    /// lease database that didn't store that information.
    static const uint32_t HWADDR_SOURCE_UNKNOWN;

    /// Obtained first hand from raw socket (100% reliable).
    static const uint32_t HWADDR_SOURCE_RAW;

    /// Extracted from DUID-LL or DUID-LLT (not 100% reliable as the client
    /// can send fake DUID).
    static const uint32_t HWADDR_SOURCE_DUID;

    /// Extracted from IPv6 link-local address. Not 100% reliable, as the
    /// client can use different IID other than EUI-64, e.g. Windows supports
    /// RFC4941 and uses random values instead of EUI-64.
    static const uint32_t HWADDR_SOURCE_IPV6_LINK_LOCAL;

    /// Get it from RFC6939 option. (A relay agent can insert client link layer
    /// address option). Note that a skilled attacker can fake that by sending
    /// his request relayed, so the legitimate relay will think it's a second
    /// relay.
    static const uint32_t HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION;

    /// A relay can insert remote-id. In some deployments it contains a MAC
    /// address (RFC4649).
    static const uint32_t HWADDR_SOURCE_REMOTE_ID;

    /// A relay can insert a subscriber-id option. In some deployments it
    /// contains a MAC address (RFC4580).
    static const uint32_t HWADDR_SOURCE_SUBSCRIBER_ID;

    /// A CMTS (acting as DHCP relay agent) that supports DOCSIS standard
    /// can insert DOCSIS options that contain client's MAC address.
    /// This specific option is suboption 1026 in vendor-class option with
    /// vendor-id=4491. Client in this context would be a cable modem.
    static const uint32_t HWADDR_SOURCE_DOCSIS_CMTS;

    /// A cable modem (acting as DHCP client) that supports DOCSIS standard
    /// can insert DOCSIS options that contain client's MAC address.
    /// This specific option is suboption 36 in vendor-class option with
    /// vendor-id=4491.
    static const uint32_t HWADDR_SOURCE_DOCSIS_MODEM;

    /// @}

    /// @brief default constructor
    HWAddr();

    /// @brief constructor, based on C-style pointer and length
    /// @param hwaddr pointer to hardware address
    /// @param len length of the address pointed by hwaddr
    /// @param htype hardware type
    HWAddr(const uint8_t* hwaddr, size_t len, uint16_t htype);

    /// @brief constructor, based on C++ vector<uint8_t>
    /// @param hwaddr const reference to hardware address
    /// @param htype hardware type
    HWAddr(const std::vector<uint8_t>& hwaddr, uint16_t htype);

    // Vector that keeps the actual hardware address
    std::vector<uint8_t> hwaddr_;

    /// Hardware type
    ///
    /// @note It used to be uint8_t as used in DHCPv4. However, since we're
    /// expanding MAC addresses support to DHCPv6 that uses hw_type as
    /// 16 bits, we need to be able to store that wider format.
    uint16_t htype_;

    /// @brief Hardware address source
    ///
    /// This variable specifies how the hardware address was obtained.
    /// @todo This is a stub implementation. Proper implementation will move
    /// constants from Pkt::HWADDR_SOURCE_* here. Currently always initialized
    /// to zero.
    uint32_t source_;

    /// @brief Returns textual representation of a hardware address
    /// (e.g. 00:01:02:03:04:05)
    ///
    /// @param include_htype Boolean value which controls whether the hardware
    /// type is included in the returned string (true), or not (false).
    ///
    /// @return Hardware address in the textual format.
    std::string toText(bool include_htype = true) const;

    /// @brief Creates instance of the hardware address from textual format.
    ///
    /// This function parses HW address specified as text and creates the
    /// corresponding @c HWAddr instance. The hexadecimal digits representing
    /// individual bytes of the hardware address should be separated with
    /// colons. Typically, two digits per byte are used. However, this function
    /// allows for 1 digit per HW address byte. In this case, the digit is
    /// prepended with '0' during conversion to binary value.
    ///
    /// This function can be used to perform a reverse operation to the
    /// @c HWAddr::toText(false).
    ///
    /// The instance created by this function sets HTYPE_ETHER as a hardware
    /// type.
    ///
    /// @param text HW address in the textual format.
    /// @param htype Hardware type.
    ///
    /// @return Instance of the HW address created from text.
    static HWAddr fromText(const std::string& text,
                           const uint16_t htype = HTYPE_ETHER);

    /// @brief Compares two hardware addresses for equality
    bool operator==(const HWAddr& other) const;

    /// @brief Compares two hardware addresses for inequality
    bool operator!=(const HWAddr& other) const;
};

/// @brief Shared pointer to a hardware address structure
typedef boost::shared_ptr<HWAddr> HWAddrPtr;

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // HWADDR_H
