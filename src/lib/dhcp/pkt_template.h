// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_PKT_TEMPLATE_H
#define ISC_PKT_TEMPLATE_H

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <util/dhcp_space.h>

namespace isc {

namespace dhcp {

/// @brief adapters for linking templates to qualified names
/// @{
namespace {

template <isc::util::DhcpSpace D>
struct AdapterPkt {};

template <>
struct AdapterPkt<isc::util::DHCPv4> {
    using type = Pkt4;
};

template <>
struct AdapterPkt<isc::util::DHCPv6> {
    using type = Pkt6;
};

}  // namespace

template <isc::util::DhcpSpace D>
using PktT = typename AdapterPkt<D>::type;

template <isc::util::DhcpSpace D>
using PktTPtr = boost::shared_ptr<PktT<D>>;
/// @}

}  // namespace dhcp
}  // namespace isc

#endif  // ISC_PKT_TEMPLATE_H
