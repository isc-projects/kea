// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BUILD_RA_H
#define BUILD_RA_H

#include <slaac/nd.h>
#include <slaac/nd_pkt_ra.h>
#include <slaac/nd_option_lladdr.h>
#include <slaac/nd_option_mtu.h>
#include <slaac/nd_option_pref_info.h>
#include <slaac/nd_option_univ_ra.h>
#include <slaac/slaac_cfg_mgr.h>

namespace isc {
namespace slaac {

/// @brief Build a Router Advertisement packet.
///
/// @param config The configuration of Slaac.
/// @return the configured Router Advertisement packet.
/// @throw Many errors can happen.
RAPktPtr buildRA(const SlaacConfigPtr& config);

} // namespace isc::slaac
} // namespace isc

#endif
