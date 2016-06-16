// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_PDEXCLUDE_H
#define OPTION6_PDEXCLUDE_H

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

    Option6PDExclude(const isc::asiolink::IOAddress& addr,
                     uint8_t prefix_len,
                     const isc::asiolink::IOAddress& prefix_excluded,
                     uint8_t prefix_excluded_len);

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    ///
    /// @throw BadValue Universe of the option is neither V4 nor V6.
    virtual void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// Returns length of the complete option (data length + DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual uint16_t len();

protected:
    uint8_t excludedPrefixLenBytes();

protected:
    isc::asiolink::IOAddress addr_;
    uint8_t prefix_len_;

    isc::asiolink::IOAddress prefix_excluded_;
    uint8_t prefix_excluded_len_;
};

/// @brief Pointer to the @c Option6PDExclude object.
typedef boost::shared_ptr<Option6PDExclude> Option6PDExcludePtr;

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION6_PDEXCLUDE_H
