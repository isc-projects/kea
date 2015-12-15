// Copyright (C) 2013, 2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the top-level component of kea-dhcp_ddns.

#include <dhcp_ddns/dhcp_ddns_log.h>

namespace isc {
namespace dhcp_ddns {

/// @brief Defines the logger used within lib dhcp_ddns.
isc::log::Logger dhcp_ddns_logger("libdhcp-ddns");

} // namespace dhcp_ddns
} // namespace isc

