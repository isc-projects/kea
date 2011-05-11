// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __CONFIG_LOG__H
#define __CONFIG_LOG__H

#include <log/macros.h>
#include "configdef.h"

namespace isc {
namespace config {

/// \brief Config Logging
///
/// Defines the levels used to output debug messages in the CONFIG.  Note that
/// higher numbers equate to more verbose (and detailed) output.

// The first level traces normal operations - asking the CONFIG for an address,
// and cancelling a lookup.  It also records when the CONFIG calls back to the
// resolver to resolve something.
//const int CONFIG_DBG_TRACE = 10;

// The next level extends the normal operations and records the results of the
// lookups.
//const int CONFIG_DBG_RESULTS = 20;

// Additional information on the usage of the names - the RTT values obtained
// when queries were done.
//const int CONFIG_DBG_RTT = 30;


/// \brief Config Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger config_logger;    // isc::config::logger is the CONFIG logger

} // namespace config
} // namespace isc

#endif // __CONFIG_LOG__H
