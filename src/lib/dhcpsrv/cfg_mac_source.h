// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CFG_MAC_SOURCE_H
#define CFG_MAC_SOURCE_H

#include <stdint.h>
#include <vector>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Container for defined MAC/hardware address sources
typedef std::vector<uint32_t> CfgMACSources;

/// @brief Wrapper class that holds MAC/hardware address sources
///
/// It's a simple wrapper around a vector of uint32_t, with each entry
/// holding one MAC source.
class CfgMACSource {

 public:
    /// @brief Default constructor.
    ///
    /// Sets source to 'any'.
    CfgMACSource();

    /// @brief Attempts to convert known hardware address sources to uint32_t
    ///
    /// Supported strings are: \li any => 0xffffffff
    ///                        \li raw => 0x00000001
    ///                        \li duid => 0x00000002
    ///                        \li ipv6-link-local 0x00000004
    ///                        \li client-link-addr-option, rfc6939 => 0x00000008
    ///                        \li remote-id, rfc4649 => 0x00000010
    ///                        \li subscriber-id, rfc4580 => 0x00000020
    ///                        \li docsis => 0x00000040
    ///
    /// For specific constants, see @ref isc::dhcp::HWAddr class.
    ///
    /// @throw BadValue if specified string is unknown
    /// @return bitmask version of a given method
    static uint32_t MACSourceFromText(const std::string& name);


    /// @brief Adds additional MAC/hardware address aquisition.
    ///
    /// @param source MAC source (see constants in Pkt::HWADDR_SOURCE_*)
    ///
    /// Specified source is being added to the mac_sources_ array.
    /// @todo implement add(string) version of this method.
    void add(uint32_t source) {
        mac_sources_.push_back(source);
    }

    /// @brief Provides access to the configure MAC/Hardware address sources.
    ///
    /// @note The const reference returned is only valid as long as the
    /// object that returned it.
    const CfgMACSources& get() const {
        return mac_sources_;
    }

    /// @brief Removes any configured MAC/Hardware address sources.
    void clear() {
        mac_sources_.clear();
    }

 protected:
    /// @brief Actual MAC sources storage
    CfgMACSources mac_sources_;

};

};
};

#endif
