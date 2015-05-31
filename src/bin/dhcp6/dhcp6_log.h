// Copyright (C) 2012, 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP6_LOG_H
#define DHCP6_LOG_H

#include <dhcp6/dhcp6_messages.h>
#include <dhcp6/sedhcp6_messages.h>
#include <log/logger_support.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

/// \brief DHCP6 Logging
///
/// Defines the levels used to output debug messages in the non-library part of
/// the kea-dhcp6 program.  Higher numbers equate to more verbose (and detailed)
/// output.

// Debug levels used to log information during startup and shutdown.
const int DBG_DHCP6_START = DBGLVL_START_SHUT;
const int DBG_DHCP6_SHUT = DBGLVL_START_SHUT;

// Debug level used to log setting information (such as configuration changes).
const int DBG_DHCP6_COMMAND = DBGLVL_COMMAND;

// Trace basic operations within the code.
const int DBG_DHCP6_BASIC = DBGLVL_TRACE_BASIC;

// Trace hook related operations
const int DBG_DHCP6_HOOKS = DBGLVL_TRACE_BASIC;

// Trace detailed operations, including errors raised when processing invalid
// packets.  (These are not logged at severities of WARN or higher for fear
// that a set of deliberately invalid packets set to the server could overwhelm
// the logging.)
const int DBG_DHCP6_DETAIL = DBGLVL_TRACE_DETAIL;

// This level is used to log the contents of packets received and sent.
const int DBG_DHCP6_DETAIL_DATA = DBGLVL_TRACE_DETAIL_DATA;

/// Define the logger for the "dhcp6" module part of kea-dhcp6.  We could define
/// a logger in each file, but we would want to define a common name to avoid
/// spelling mistakes, so it is just one small step from there to define a
/// module-common logger.
extern isc::log::Logger dhcp6_logger;

} // namespace dhcp6
} // namespace isc

#endif // DHCP6_LOG_H
