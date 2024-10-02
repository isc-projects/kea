// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_HB_LOG_H
#define MYSQL_HB_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <mysql_hb_messages.h>

namespace isc {
namespace dhcp {

///@{
/// @brief MySQL Host Mgr logging levels
///
/// Defines the levels used to output debug messages in the MySQL Lease Mgr
/// Note that higher numbers equate to more verbose (and detailed) output.

/// @brief Traces normal operations
///
/// E.g. sending a query to the database etc.
extern const int MYSQL_HB_DBG_TRACE;

/// @brief Records the results of the lookups
///
/// Using the example of tracing queries from the backend database, this will
/// just record the summary results.
extern const int MYSQL_HB_DBG_RESULTS;

/// @brief Additional information
///
/// Record detailed tracing. This is generally reserved for tracing access to
/// the lease database.
extern const int MYSQL_HB_DBG_TRACE_DETAIL;

/// @brief Additional information
///
/// Record detailed (and verbose) data on the server.
extern const int MYSQL_HB_DBG_TRACE_DETAIL_DATA;

// Trace hook related operations
extern const int MYSQL_HB_DBG_HOOKS;
///@}

/// @brief MySQL Host Mgr Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger mysql_hb_logger;

}  // namespace dhcp
}  // namespace isc

#endif
