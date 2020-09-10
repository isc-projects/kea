// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ADDRESS_RANGE_H
#define ADDRESS_RANGE_H

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

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // ADDRESS_RANGE_H
