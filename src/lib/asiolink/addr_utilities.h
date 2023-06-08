// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ADDR_UTILITIES_H
#define ADDR_UTILITIES_H

#include <asiolink/io_address.h>
#include <util/bigints.h>

namespace isc {
namespace asiolink {

/// This code is based on similar code from the Dibbler project. I, Tomasz Mrugalski,
/// as a sole creator of that code hereby release it under BSD license for the benefit
/// of the Kea project.

/// @brief returns a first address in a given prefix
///
/// Example: For 2001:db8:1\::deaf:beef and length /120 the function will return
/// 2001:db8:1\::dead:be00. See also @ref lastAddrInPrefix.
///
/// @param prefix and address that belongs to a prefix
/// @param len prefix length
///
/// @return first address from a prefix
IOAddress firstAddrInPrefix(const IOAddress& prefix, uint8_t len);

/// @brief returns a last address in a given prefix
///
/// Example: For 2001:db8:1\::deaf:beef and length /112 the function will return
/// 2001:db8:1\::dead:ffff. See also @ref firstAddrInPrefix.
///
/// @param prefix and address that belongs to a prefix
/// @param len prefix length
///
/// @return first address from a prefix
IOAddress lastAddrInPrefix(const IOAddress& prefix, uint8_t len);

/// @brief Generates an IPv4 netmask of specified length
/// @throw BadValue if len is greater than 32
/// @return netmask
IOAddress getNetmask4(uint8_t len);


/// @brief Returns number of available addresses in the specified range (min - max).
///
/// Note that for min equal max case, the number of addresses is one.
///
/// @throw BadValue if min and max are not of the same family (both must be
///        either IPv4 or IPv6) or if max < min.
///
/// @param min the first address in range
/// @param max the last address in range
/// @return number of addresses in range
isc::util::uint128_t addrsInRange(const IOAddress& min, const IOAddress& max);

/// @brief Returns prefix length from the specified range (min - max).
///
/// This can be considered as log2(addrsInRange)
///
/// @throw BadValue if min and max do not define a prefix.
///
/// @param min the first address in range
/// @param max the last address in range
/// @return the prefix length or -1 if the range is not from a prefix
int prefixLengthFromRange(const IOAddress& min, const IOAddress& max);

/// @brief Returns number of available IPv6 prefixes in the specified prefix.
///
/// Note that if the answer is bigger than uint64_t can hold, it will return
/// the max value of uint64_t type.
///
/// Example: prefixesInRange(48, 64) returns 65536, as there are /48 pool
/// can be split into 65536 prefixes, each /64 large.
///
/// @param pool_len length of the pool in bits
/// @param delegated_len length of the prefixes to be delegated from the pool
/// @return number of prefixes in range
isc::util::uint128_t prefixesInRange(const uint8_t pool_len, const uint8_t delegated_len);

/// @brief Finds the address increased by offset.
///
/// Adds offset to the IPv4 or iPv6 address and finds the resulting address.
/// Note that the current limitation is the maximum value of the offset,
/// i.e. max uint64_t. If the sum of the IPv4 address and the offset exceeds
/// the maximum value of uint32_t type, the 255.255.255.255 is returned.
///
/// @param addr input address
/// @param offset distance of the returned address from the input address.
/// @return address being offset greater than the input address
IOAddress offsetAddress(const IOAddress& addr, isc::util::uint128_t offset);

}  // namespace asiolink
}  // namespace isc

#endif // ADDR_UTILITIES_H
