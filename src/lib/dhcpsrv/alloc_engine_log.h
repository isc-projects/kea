// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ALLOC_ENGINE_LOG_H
#define ALLOC_ENGINE_LOG_H

#include <dhcpsrv/alloc_engine_messages.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

//@{
/// @brief Logging levels for the @c AllocEngine.
///
/// Defines the levels used to output debug messages from the @c AllocEngine.

/// @brief Traces normal operations
extern const int ALLOC_ENGINE_DBG_TRACE;

/// @brief Records the results of various operations.
///
/// Messages logged at this level will typically contain summary of the
/// data retrieved.
extern const int ALLOC_ENGINE_DBG_RESULTS;

/// @brief Record detailed traces
///
/// Messages logged at this level will log detailed tracing information.
extern const int ALLOC_ENGINE_DBG_TRACE_DETAIL;

/// @brief Records detailed results of various operations.
///
/// Messages logged at this level will contain detailed results.
extern const int ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA;

//@}

/// @brief Logger for the @c AllocEngine.
///
/// Define the logger used to log messages in @c AllocEngine.
extern isc::log::Logger alloc_engine_logger;

} // namespace dhcp
} // namespace isc

#endif // ALLOC_ENGINE_LOG_H
