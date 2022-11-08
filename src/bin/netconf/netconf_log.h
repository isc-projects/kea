// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf_log.h
/// Contains declarations for loggers used by the Kea netconf agent.

#ifndef NETCONF_LOG_H
#define NETCONF_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <netconf/netconf_messages.h>

namespace isc {
namespace netconf {

///@{
/// \brief Netconf agent logging levels.
///
/// Defines the levels used to output debug messages in the Netconf agent.
/// Note that higher numbers equate to more verbose (and detailed) output.

/// @brief Traces normal operations.
///
/// E.g. sending a command to a server etc.
extern const int NETCONF_DBG_TRACE;

/// @brief Records the results of the commands.
///
/// Using the example of tracing commands to a server, this will just record
/// the summary results.
extern const int NETCONF_DBG_RESULTS;

/// @brief Additional information.
///
/// Record detailed tracing. This is generally reserved for tracing
/// configurations from or to a server.
extern const int NETCONF_DBG_TRACE_DETAIL_DATA;

///@}

/// @brief Defines the name of the root level (default) logger.
extern const char* NETCONF_LOGGER_NAME;

/// @brief Base logger for the netconf agent
extern isc::log::Logger netconf_logger;

}  // namespace netconf
}  // namespace isc

#endif  // NETCONF_LOG_H
