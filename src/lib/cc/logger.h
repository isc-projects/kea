// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CC_LOGGER_H
#define CC_LOGGER_H

#include <cc/cc_messages.h>
#include <log/macros.h>

/// \file cc/logger.h
/// \brief Command Channel library global logger
///
/// This holds the logger for the CC library. It is a private header
/// and should not be included in any publicly used header, only in local
/// cc files.

namespace isc {
namespace cc {

/// Trace basic operation
const int DBG_TRACE_BASIC = DBGLVL_TRACE_BASIC;

/// This includes messages being sent and received, waiting for messages
/// and alike.
const int DBG_TRACE_DETAILED = DBGLVL_TRACE_DETAIL;

// Declaration of the logger.
extern isc::log::Logger logger;

} // namespace cc
} // namespace isc

/// \brief Logger for this library

#endif
