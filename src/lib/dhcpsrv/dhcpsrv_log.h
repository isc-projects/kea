// Copyright (C) 2011-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCPSRV_LOG_H
#define DHCPSRV_LOG_H

#include <dhcpsrv/dhcpsrv_messages.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

///@{
/// \brief DHCP server library logging levels
///
/// Defines the levels used to output debug messages in the DHCP server
/// library.  Note that higher numbers equate to more verbose (and detailed)
/// output.

/// @brief Traces normal operations
///
/// E.g. sending a query to the database etc.
extern const int DHCPSRV_DBG_TRACE;

/// @brief Records the results of the lookups
///
/// Using the example of tracing queries from the backend database, this will
/// just record the summary results.
extern const int DHCPSRV_DBG_RESULTS;

/// @brief Additional information
///
/// Record detailed tracing. This is generally reserved for tracing access to
/// the lease database.
extern const int DHCPSRV_DBG_TRACE_DETAIL;

/// @brief Additional information
///
/// Record detailed (and verbose) data on the server.
extern const int DHCPSRV_DBG_TRACE_DETAIL_DATA;

// Trace hook related operations
extern const int DHCPSRV_DBG_HOOKS;

///@}


/// \brief DHCP server library Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger dhcpsrv_logger;

} // namespace dhcp
} // namespace isc

#endif // DHCPSRV_LOG_H
