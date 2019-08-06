// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FUZZ_LOG_H
#define FUZZ_LOG_H

#include <dhcpsrv/fuzz_messages.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

///@{
/// \brief Logging levels for fuzzing output
///
/// Defines the levels used to output debug messages during fuzzing.

/// @brief Traces normal operations
///
/// An example of the normal operation is a report of a packet being received
/// from the fuzzer.
extern const int FUZZ_DBG_TRACE;

/// @brief Record detailed traces
///
/// Messages logged at this level will log detailed tracing information.
extern const int FUZZ_DBG_TRACE_DETAIL;

///@}

/// @brief Logger for the @c HostMgr and the code it calls.
///
/// Define the logger used to log messages in @c HostMgr and the code it
/// calls to manage host reservations.
extern isc::log::Logger fuzz_logger;

} // namespace dhcp
} // namespace isc

#endif // FUZZ_LOG_H
