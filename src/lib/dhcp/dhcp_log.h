// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_LOG_H
#define DHCP_LOG_H

#include <dhcp/dhcp_messages.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

/// \brief DHCP library Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger dhcp_logger;

} // namespace dhcp
} // namespace isc

#endif // DHCP_LOG_H
