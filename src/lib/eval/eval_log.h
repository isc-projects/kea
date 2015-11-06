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
const int EVAL_DBG_TRACE = DBGLVL_TRACE_BASIC;

// The next level traces each call to hook code.
const int EVAL_DBG_CALLS = DBGLVL_TRACE_BASIC_DATA;

// Additional information on the calls.  Report each call to a callout (even
// if there are multiple callouts on a hook) and each status return.
const int EVAL_DBG_EXTENDED_CALLS = DBGLVL_TRACE_DETAIL_DATA;

/// @brief Eval Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger eval_logger;

} // namespace dhcp
} // namespace isc

#endif // EVAL_LOG_H
