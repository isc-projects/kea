// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EVAL_LOG_H
#define EVAL_LOG_H

#include <log/macros.h>
#include <eval/eval_messages.h>

namespace isc {
namespace dhcp {

/// @brief Eval debug Logging levels
///
/// Defines the levels used to output debug messages in the eval (classification) code.
/// Note that higher numbers equate to more verbose (and detailed) output.

// The first level traces normal operations,
extern const int EVAL_DBG_TRACE;

// Additional information on the calls.  Report the values that were
// popped from or pushed to the value stack.
extern const int EVAL_DBG_STACK;

/// @brief Eval Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger eval_logger;

} // namespace dhcp
} // namespace isc

#endif // EVAL_LOG_H
