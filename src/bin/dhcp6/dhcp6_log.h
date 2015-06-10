// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <log/logger_support.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

/// @name Constants defining debug levels for logging in DHCPv6 server.
//@{

/// @brief Debug level used to log information during server startup.
const int DBG_DHCP6_START = DBGLVL_START_SHUT;

/// @brief Debug level used to log information during server shutdown.
const int DBG_DHCP6_SHUT = DBGLVL_START_SHUT;

/// @brief Debug level used to log receiving commands.
const int DBG_DHCP6_COMMAND = DBGLVL_COMMAND;

/// @brief Debug level used to trace basic operations within the code.
const int DBG_DHCP6_BASIC = DBGLVL_TRACE_BASIC;

/// @brief Debug level used to trace hook related operations
const int DBG_DHCP6_HOOKS = DBGLVL_TRACE_BASIC;

/// @brief Debug level used to log the traces with some basic data.
///
/// The basic data includes summary information, e.g. summary of the
/// information returned by a particular function. It may also include
/// more detailed information in cases when it is warranted and the
/// extraction of the data doesn't impact the server's performance
/// significantly.
const int DBG_DHCP6_BASIC_DATA = DBGLVL_TRACE_BASIC_DATA;

/// @brief Debug level used to trace detailed errors.
///
/// Trace detailed operations, including errors raised when processing invalid
/// packets.  (These are not logged at severities of WARN or higher for fear
/// that a set of deliberately invalid packets set to the server could overwhelm
/// the logging.)
const int DBG_DHCP6_DETAIL = DBGLVL_TRACE_DETAIL;

/// @brief This level is used to log the contents of packets received and sent.
const int DBG_DHCP6_DETAIL_DATA = DBGLVL_TRACE_DETAIL_DATA;

//@}

/// @name Constants holding names of loggers for the DHCPv6 server.
//@{

/// @brief Defines the name of the root level (default) logger.
extern const char* DHCP6_ROOT_LOGGER_NAME;

/// @brief Name of the base logger for DHCPv6 server.
extern const char* DHCP6_APP_LOGGER_NAME;

/// @brief Name of the logger for rejected packets.
extern const char* DHCP6_BAD_PACKET_LOGGER_NAME;

/// @brief Name of the logger for processed packets.
extern const char* DHCP6_PACKET_LOGGER_NAME;

/// @brief Name of the logger for options parser.
extern const char* DHCP6_OPTIONS_LOGGER_NAME;

/// @brief Name of the logger for hostname or FQDN processing.
extern const char* DHCP6_DDNS_LOGGER_NAME;

/// @brief Name of the logger for lease allocation logic.
extern const char* DHCP6_LEASE_LOGGER_NAME;

//@}

/// @name Loggers used by the DHCPv6 server
//@{

/// @brief Base logger for DHCPv6 server.
extern isc::log::Logger dhcp6_logger;

/// @brief Logger for rejected packets.
///
/// Here "bad packets" are packets that are either dropped (i.e malformed,
/// unsupported types) or packets that are rejected for logical reasons.
extern isc::log::Logger bad_packet_logger;

/// @brief Logger for processed packets.
///
/// This logger is used to issue log messages related to the reception and
/// sending DHCP packets.
extern isc::log::Logger packet_logger;

/// @brief Logger for options parser.
///
/// This logger is used to issue log messages related to processing of the
/// DHCP options 
extern isc::log::Logger options_logger;

/// @brief Logger for Hostname or FQDN processing.
///
/// This logger is used to issue log messages related to processing the
/// hostnames, FQDNs and sending name change requests to D2.
extern isc::log::Logger ddns_logger;

/// @brief Logger for lease allocation logic.
///
/// This logger is used to issue log messages related to lease allocation.
extern isc::log::Logger lease_logger;

//@}

} // namespace dhcp6
} // namespace isc

#endif // DHCP6_LOG_H
