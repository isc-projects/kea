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

#ifndef __RESOLVER_LOG__H
#define __RESOLVER_LOG__H

#include <log/macros.h>
#include "resolverdef.h"

/// \brief Resolver Logging
///
/// Defines the levels used to output debug messages in the resolver.  Note that
/// higher numbers equate to more verbose (and detailed) output.

// Initialization
const int RESOLVER_DBG_INIT = 10;

// Configuration messages
const int RESOLVER_DBG_CONFIG = 30;

// Trace sending and receiving of messages
const int RESOLVER_DBG_IO = 50;

// Trace processing of messages
const int RESOLVER_DBG_PROCESS = 70;

// Detailed message information
const int RESOLVER_DBG_DETAIL = 90;


/// \brief Resolver Logger
///
/// Define the logger used to log messages.  We could define it in multiple
/// modules, but defining in a single module and linking to it saves time and
/// space.
extern isc::log::Logger resolver_logger;

#endif // __RESOLVER_LOG__H
