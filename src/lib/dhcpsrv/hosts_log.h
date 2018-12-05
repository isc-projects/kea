// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOSTS_LOG_H
#define HOSTS_LOG_H

#include <dhcpsrv/hosts_messages.h>
#include <log/macros.h>

namespace isc {
namespace dhcp {

///@{
/// \brief Logging levels for the host reservations management.
///
/// Defines the levels used to output debug messages during the host
/// reservations management, i.e. retrieving and adding host reservations.
/// Note that higher numbers equate to more verbose(and detailed) output.

/// @brief Traces normal operations
///
/// An example of the normal operation is the call to one of the functions
/// which retrieve the reservations or add new reservation.
extern const int HOSTS_DBG_TRACE;

/// @brief Records the results of the lookups
///
/// Messages logged at this level will typically contain summary of the
/// data retrieved.
extern const int HOSTS_DBG_RESULTS;

/// @brief Record detailed traces
///
/// Messages logged at this level will log detailed tracing information.
extern const int HOSTS_DBG_TRACE_DETAIL;

/// @brief Records detailed results of lookups.
///
/// Messages logged at this level will contain detailed results.
extern const int HOSTS_DBG_TRACE_DETAIL_DATA;

///@}

/// @brief Logger for the @c HostMgr and the code it calls.
///
/// Define the logger used to log messages in @c HostMgr and the code it
/// calls to manage host reservations.
extern isc::log::Logger hosts_logger;

} // namespace dhcp
} // namespace isc

#endif // HOSTS_LOG_H
