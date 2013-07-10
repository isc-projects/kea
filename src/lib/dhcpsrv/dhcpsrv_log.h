// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
const int DHCPSRV_DBG_TRACE = DBGLVL_TRACE_BASIC;

/// @brief Records the results of the lookups
///
/// Using the example of tracing queries from the backend database, this will
/// just record the summary results.
const int DHCPSRV_DBG_RESULTS = DBGLVL_TRACE_BASIC_DATA;

/// @brief Additional information
///
/// Record detailed tracing. This is generally reserved for tracing access to
/// the lease database.
const int DHCPSRV_DBG_TRACE_DETAIL = DBGLVL_TRACE_DETAIL;

/// @brief Additional information
///
/// Record detailed (and verbose) data on the server.
const int DHCPSRV_DBG_TRACE_DETAIL_DATA = DBGLVL_TRACE_DETAIL_DATA;

// Trace hook related operations
const int DHCPSRV_DBG_HOOKS = DBGLVL_TRACE_BASIC;

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
