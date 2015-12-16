// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_DDNS_LOG_H
#define DHCP_DDNS_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <dhcp_ddns/dhcp_ddns_messages.h>

namespace isc {
namespace dhcp_ddns {

/// Define the logger for the "dhcp_ddns" logging.
extern isc::log::Logger dhcp_ddns_logger;

} // namespace dhcp_ddns
} // namespace isc

#endif // DHCP_DDNS_LOG_H
