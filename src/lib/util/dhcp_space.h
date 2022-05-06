// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_DHCP_SPACE_H
#define ISC_DHCP_SPACE_H 1

#include <cstdint>

namespace isc {
namespace util {

enum DhcpSpace {
    DHCPv4,
    DHCPv6,
};

template <DhcpSpace D>
constexpr uint16_t integerDhcpSpace();

template <DhcpSpace D>
constexpr char const* cStringDhcpSpace();

}  // namespace util
}  // namespace isc

#endif  // ISC_DHCP_SPACE_H
