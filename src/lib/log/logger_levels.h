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

// $Id$

#ifndef __LOGGER_LEVELS_H
#define __LOGGER_LEVELS_H

namespace isc {
namespace log {

/// \brief Severity Levels
///
/// Defines the severity levels for logging.  This is shared between the logger
/// and the implementations classes.
///
/// N.B. The order of the levels - DEBUG less than INFO less that WARN etc. is
/// implicitly assumed in several implementations.  They must not be changed.

typedef enum {
    DEFAULT = 0,    // Default to logging level of the parent
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5,
    NONE = 6    // Disable logging
} Severity;

}   // namespace log
}   // namespace isc

#endif // __LOGGER_LEVELS_H
