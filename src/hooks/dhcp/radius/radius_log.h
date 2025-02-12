// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_LOG_H
#define RADIUS_LOG_H

#include <log/message_initializer.h>
#include <log/macros.h>
#include <radius_messages.h>

namespace isc {
namespace radius {

///@{
/// @brief Radius logging levels.
///
/// Defines the levels used to output debug messages in Radius.
/// Note that higher numbers equate to more verbose (and detailed) output.

/// @brief Traces normal operations.
///
/// E.g. server communication etc.
const int RADIUS_DBG_TRACE = isc::log::DBGLVL_TRACE_BASIC;

///@}

/// @brief Radius Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger radius_logger;

} // end of namespace radius
} // end of namespace isc

#endif // RADIUS_LOG_H
