// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
    /// @brief Maximum size of a hardware address.
    static const size_t MAX_HWADDR_LEN = 20;

    /// @brief default constructor
    HWAddr();

    /// @brief constructor, based on C-style pointer and length
    /// @param hwaddr pointer to hardware address
    /// @param len length of the address pointed by hwaddr
    /// @param htype hardware type
    HWAddr(const uint8_t* hwaddr, size_t len, uint8_t htype);

    /// @brief constructor, based on C++ vector<uint8_t>
    /// @param hwaddr const reference to hardware address
    /// @param htype hardware type
    HWAddr(const std::vector<uint8_t>& hwaddr, uint8_t htype);

    // Vector that keeps the actual hardware address
    std::vector<uint8_t> hwaddr_;

    // Hardware type
    uint8_t htype_;

    /// @brief Returns textual representation of a client-id (e.g. 00:01:02:03)
    std::string toText() const;

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
