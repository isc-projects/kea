// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_CACHE_LOG_H
#define HOST_CACHE_LOG_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <host_cache_messages.h>

namespace isc {
namespace host_cache {

///@{
/// \brief Host Cache hooks library logging levels
///
/// Defines the levels used to output debug messages in the Host Cache hooks
/// library.  Note that higher numbers equate to more verbose (and detailed)
/// output.

/// @brief Traces normal operations
///
/// E.g. sending a query to the database etc.
const int HOST_CACHE_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;

/// @brief Records the results of the lookups
///
/// Using the example of tracing queries from the backend database, this will
/// just record the summary results.
const int HOST_CACHE_DBG_RESULTS = isc::log::DBGLVL_TRACE_BASIC_DATA;

///@}


/// @brief Host Cache Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger host_cache_logger;

} // end of namespace host_cache
} // end of namespace isc

#endif // HOST_CACHE_LOG_H
