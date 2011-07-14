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

#ifndef __RESOLVE_LOG__H
#define __RESOLVE_LOG__H

#include <log/macros.h>
#include "resolve_messages.h"

namespace isc {
namespace resolve {

/// \brief Resolver Library Logging
///
/// Defines the levels used to output debug messages in the resolver library.
/// Note that higher numbers equate to more verbose (and detailed) output.

// The first level traces normal operations
const int RESLIB_DBG_TRACE = 10;

// The next level extends the normal operations and records the results of the
// lookups.
const int RESLIB_DBG_RESULTS = 20;

// Report cache lookups and results
const int RESLIB_DBG_CACHE = 40;

// Indicate when callbacks are called
const int RESLIB_DBG_CB = 50;


/// \brief Resolver Library Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger logger;

} // namespace resolve
} // namespace isc

#endif // __RESOLVE_LOG__H
