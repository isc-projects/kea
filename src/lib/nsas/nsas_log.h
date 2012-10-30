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

#ifndef NSAS_LOG_H
#define NSAS_LOG_H

#include <log/macros.h>
#include "nsas_messages.h"

namespace isc {
namespace nsas {

/// \brief NSAS Logging
///
/// Defines the levels used to output debug messages in the NSAS.  Note that
/// higher numbers equate to more verbose (and detailed) output.

// The first level traces normal operations - asking the NSAS for an address,
// and cancelling a lookup.  It also records when the NSAS calls back to the
// resolver to resolve something.
const int NSAS_DBG_TRACE = DBGLVL_TRACE_BASIC;

// The next level extends the normal operations and records the results of the
// lookups.
const int NSAS_DBG_RESULTS = DBGLVL_TRACE_BASIC_DATA;

// Additional information on the usage of the names - the RTT values obtained
// when queries were done.
const int NSAS_DBG_RTT = DBGLVL_TRACE_DETAIL_DATA;


/// \brief NSAS Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger nsas_logger;    // isc::nsas::logger is the NSAS logger

} // namespace nsas
} // namespace isc

#endif // NSAS_LOG_H
