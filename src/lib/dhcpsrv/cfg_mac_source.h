// Copyright (C) 2014-2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_MAC_SOURCE_H
#define CFG_MAC_SOURCE_H

#include <cc/cfg_to_element.h>
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
class CfgMACSource : public isc::data::CfgToElement {

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


    /// @brief Adds additional MAC/hardware address acquisition.
    ///
    /// @param source MAC source (see constants in Pkt::HWADDR_SOURCE_*)
    ///
    /// Specified source is being added to the mac_sources_ array.
    /// @throw InvalidParameter if such a source is already defined.
    void add(uint32_t source);

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

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

 protected:
    /// @brief Actual MAC sources storage
    CfgMACSources mac_sources_;

};

};
};

#endif
