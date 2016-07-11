// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// Author: Cristian Secareanu <cristian.secareanu@qualitance.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_PDEXCLUDE_H
#define OPTION6_PDEXCLUDE_H

#include <dhcp/option.h>

#include <asiolink/io_address.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief DHCPv6 Option class for handling list of IPv6 addresses.
///
/// This class handles a list of IPv6 addresses. An example of such option
/// is dns-servers option. It can also be used to handle single address.
class Option6PDExclude: public Option {

public:

    Option6PDExclude(const isc::asiolink::IOAddress& delegated_address,
            uint8_t delegated_prefix_length,
            const isc::asiolink::IOAddress& excluded_address,
            uint8_t excluded_prefix_length);

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    ///
    /// @throw BadValue Universe of the option is neither V4 nor V6.
    virtual void pack(isc::util::OutputBuffer& buf) const;

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Returns length of the complete option (data length + DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual uint16_t len() const;

    /// @brief Returns the address of the delegated address space.
    ///
    /// @return address of delegated address space
    isc::asiolink::IOAddress getDelegatedAddress() const {
        return delegated_address_;
    }

    /// @brief Returns the prefix length of the delegated address space.
    ///
    /// @return prefix length of delegated address space
    uint8_t getDelegatedPrefixLength() const {
        return delegated_prefix_length_;
    }

    /// @brief Returns the address of the excluded address space.
    ///
    /// @return address of excluded address space
    isc::asiolink::IOAddress getExcludedAddress() const {
        return excluded_address_;
    }

    /// @brief Returns the prefix length of the excluded address space.
    ///
    /// @return prefix length of excluded address space
    uint8_t getExcludedPrefixLength() const {
        return excluded_prefix_length_;
    }

protected:
    /// @brief Returns the prefix length of the excluded prefix.
    ///
    /// @return prefix length of excluded prefix
    uint8_t getSubtractedPrefixesOctetLength() const;

    /// @brief The address and prefix length identifying the delegated IPV6
    /// prefix.
    /// {
    isc::asiolink::IOAddress delegated_address_;
    uint8_t delegated_prefix_length_;
    /// }

    /// @brief The address and prefix length identifying the excluded IPV6
    /// prefix.
    /// {
    isc::asiolink::IOAddress excluded_address_;
    uint8_t excluded_prefix_length_;
    /// }
};

/// @brief Pointer to the @c Option6PDExclude object.
typedef boost::shared_ptr<Option6PDExclude> Option6PDExcludePtr;

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION6_PDEXCLUDE_H
