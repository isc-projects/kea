// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_UTIL_DHCP_SPACE_H
#define ISC_UTIL_DHCP_SPACE_H 1

#include <string>

#include <boost/algorithm/string/replace.hpp>

namespace isc {
namespace util {

enum DhcpSpace {
    DHCPv4,
    DHCPv6,
};

/// @brief Provides the C string representation of the DHCP space.
///
/// @tparam D DHCP space
///
/// @return "4" or "6"
template <DhcpSpace D>
char const* cStringDhcpSpace();

/// @brief Replaces all occurrences of {} with 4 or 6 based on the templated DHCP space.
///
/// @tparam D DHCP space
///
/// @return the formatted string
template <DhcpSpace D>
std::string formatDhcpSpace(char const* const format_string) {
    std::string result(format_string);
    boost::replace_all(result, "{}", cStringDhcpSpace<D>());
    return result;
}

}  // namespace util
}  // namespace isc

#endif  // ISC_UTIL_DHCP_SPACE_H
