// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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
