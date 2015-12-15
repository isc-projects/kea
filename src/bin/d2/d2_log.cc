// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the top-level component of kea-dhcp-ddns.

#include <d2/d2_log.h>

namespace isc {
namespace d2 {

/// @brief Defines the logger used within D2.
isc::log::Logger dctl_logger("dhcpddns");
isc::log::Logger dhcp_to_d2_logger("dhcp-to-d2");
isc::log::Logger d2_to_dns_logger("d2-to-dns");

} // namespace d2
} // namespace isc

