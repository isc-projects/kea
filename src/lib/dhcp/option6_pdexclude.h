// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_PDEXCLUDE_H
#define OPTION6_PDEXCLUDE_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief DHCPv6 option class representing Prefix Exclude Option (RFC 6603).
///
/// This class represents DHCPv6 Prefix Exclude option (67). This option is
/// carried in the IA Prefix option and it conveys a single prefix which is
/// used by the delegating router to communicate with a requesting router on
/// the requesting router's uplink. This prefix is not used on the
/// requesting router's downlinks (is excluded from other delegated prefixes).
class Option6PDExclude: public Option {
public:

    /// @brief Constructor.
    ///
    /// @param delegated_prefix Delegated prefix.
    /// @param delegated_prefix_length Delegated prefix length.
    /// @param excluded_prefix Excluded prefix.
    /// @param excluded_prefix_length Excluded prefix length.
    ///
    /// @throw BadValue if prefixes are invalid, if excluded prefix length
    /// is not greater than delegated prefix length or if common parts of
    /// prefixes does not match.
    Option6PDExclude(const isc::asiolink::IOAddress& delegated_prefix,
                     const uint8_t delegated_prefix_length,
                     const isc::asiolink::IOAddress& excluded_prefix,
                     const uint8_t excluded_prefix_length);

    /// @brief Constructor, creates option instance from part of the buffer.
    ///
    /// This constructor is mostly used to parse Prefix Exclude options in the
    /// received messages.
    ///
    /// @param begin Lower bound of the buffer to create option from.
    /// @param end Upper bound of the buffer to create option from.
    Option6PDExclude(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// The format of the option includes excluded prefix length specified as
    /// a number of bits. It also includes IPv6 subnet ID field which is
    /// computed from the delegated and excluded prefixes, according to the
    /// section 4.2 of RFC 6603.
    ///
    /// @param [out] buf Pointer to a buffer.
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

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

    /// @brief Returns Prefix Exclude option in textual format.
    ///
    /// @param indent Number of spaces to be inserted before the text.
    virtual std::string toText(int indent = 0) const;

    /// @brief Returns excluded prefix.
    ///
    /// Assembles excluded prefix from a delegated prefix and IPv6 subnet id
    /// specified as in RFC6603, section 4.2.
    ///
    /// @param delegated_prefix Delegated prefix for which excluded prefix will
    /// be returned.
    /// @param delegated_prefix_length Delegated prefix length.
    asiolink::IOAddress
    getExcludedPrefix(const asiolink::IOAddress& delegated_prefix,
                      const uint8_t delegated_prefix_length) const;

    /// @brief Returns excluded prefix length.
    uint8_t getExcludedPrefixLength() const {
        return (excluded_prefix_length_);
    }

    /// @brief Returns an excluded prefix in a binary format.
    const std::vector<uint8_t>& getExcludedPrefixSubnetID() const {
        return (subnet_id_);
    }

private:

    /// @brief Returns IPv6 subnet ID length in octets.
    ///
    /// The IPv6 subnet ID length is between 1 and 16 octets.
    uint8_t getSubnetIDLength(const uint8_t delegated_prefix_length,
                              const uint8_t excluded_prefix_length) const;

    /// @brief Holds excluded prefix length.
    uint8_t excluded_prefix_length_;

    /// @brief Subnet identifier as described in RFC6603, section 4.2.
    std::vector<uint8_t> subnet_id_;
};

/// @brief Pointer to the @ref Option6PDExclude object.
typedef boost::shared_ptr<Option6PDExclude> Option6PDExcludePtr;

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION6_PDEXCLUDE_H
