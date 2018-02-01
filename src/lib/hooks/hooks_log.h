// Copyright (C) 2013-2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_LOG_H
#define HOOKS_LOG_H

#include <log/macros.h>
#include <hooks/hooks_messages.h>

namespace isc {
namespace hooks {

/// @brief Hooks debug Logging levels
///
/// Defines the levels used to output debug messages in the Hooks framework.
/// Note that higher numbers equate to more verbose (and detailed) output.

// The first level traces normal operations,
extern const int HOOKS_DBG_TRACE;

// The next level traces each call to hook code.
extern const int HOOKS_DBG_CALLS;

// Additional information on the calls.  Report each call to a callout (even
// if there are multiple callouts on a hook) and each status return.
extern const int HOOKS_DBG_EXTENDED_CALLS;


/// @brief Hooks Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger hooks_logger;

/// @brief Callouts logger
///
/// This is the specialized logger used to log messages pertaining to the
/// callouts execution. In particular, it logs when the callout is invoked
/// and when it ends. It also logs the callout execution times.
extern isc::log::Logger callouts_logger;

} // namespace hooks
} // namespace isc

#endif // HOOKS_LOG_H
