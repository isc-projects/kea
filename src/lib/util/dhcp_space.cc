// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/dhcp_space.h>

namespace isc {
namespace util {

template <>
char const* cStringDhcpSpace<DHCPv4>() {
    return "4";
}

template <>
char const* cStringDhcpSpace<DHCPv6>() {
    return "6";
}

} // namespace util
} // namespace isc
