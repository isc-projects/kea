// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IP_RANGE_H
#define IP_RANGE_H

#include <asiolink/io_address.h>

namespace isc {
namespace dhcp {

/// @brief Structure representing IP address range.
struct AddressRange {
    /// IP address denoting the start of the address range.
    asiolink::IOAddress start_;
    /// IP address denoting the end of the address range.
    asiolink::IOAddress end_;

    /// @brief Constructor.
    ///
    /// @param start beginning of the address range.
    /// @param end end of the address range.
    /// @throw BadValue if the @c start is greater than the end or
    /// specified boundaries do not belong to the same family.
    AddressRange(const asiolink::IOAddress& start, const asiolink::IOAddress& end);
};

/// @brief Structure representing delegated prefix range.
struct PrefixRange {
    /// IP address denoting the start of the prefix range.
    asiolink::IOAddress start_;
    /// IP address denoting the first address within the last prefix
    /// in the prefix range.
    asiolink::IOAddress end_;
    /// Prefix length.
    uint8_t prefix_length_;
    /// Delegated prefix length.
    uint8_t delegated_length_;

    /// @brief Constructor.
    ///
    /// @param prefix prefix from which prefixes are delegated.
    /// @param length length of the prefix from which prefixes are delegated.
    /// @param delegated delegated prefix length.
    /// @throw BadValue if the values provided to the constructor are invalid,
    /// e.g. it is not IPv6 prefix, delegated length is lower than prefix length
    /// etc.
    PrefixRange(const asiolink::IOAddress& prefix, const uint8_t length, const uint8_t delegated);

    /// @brief Constructor.
    ///
    /// @param start beginning of the prefix range.
    /// @param end end of the prefix range.
    /// @param delegated delegated prefix length.
    /// @throw BadValue if the values provided to the constructor are invalid,
    /// e.g. it is not IPv6 prefix.
    PrefixRange(const asiolink::IOAddress& start, const asiolink::IOAddress& end,
                const uint8_t delegated);
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // IP_RANGE_H
