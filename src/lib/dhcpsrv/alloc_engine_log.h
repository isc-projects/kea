// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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
const int ALLOC_ENGINE_DBG_TRACE = DBGLVL_TRACE_BASIC;

/// @brief Records the results of various operations.
///
/// Messages logged at this level will typically contain summary of the
/// data retrieved.
const int ALLOC_ENGINE_DBG_RESULTS = DBGLVL_TRACE_BASIC_DATA;

/// @brief Record detailed traces
///
/// Messages logged at this level will log detailed tracing information.
const int ALLOC_ENGINE_DBG_TRACE_DETAIL = DBGLVL_TRACE_DETAIL;

/// @brief Records detailed results of various operations.
///
/// Messages logged at this level will contain detailed results.
const int ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA = DBGLVL_TRACE_DETAIL_DATA;

//@}

/// @brief Logger for the @c AllocEngine.
///
/// Define the logger used to log messages in @c AllocEngine.
extern isc::log::Logger alloc_engine_logger;

} // namespace dhcp
} // namespace isc

#endif // ALLOC_ENGINE_LOG_H
