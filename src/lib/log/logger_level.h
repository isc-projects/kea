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

#ifndef LOGGER_LEVEL_H
#define LOGGER_LEVEL_H

#include <string>

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

/// Minimum/maximum debug levels.

const int MIN_DEBUG_LEVEL = 0;
const int MAX_DEBUG_LEVEL = 99;

/// \brief Log level structure
///
/// A simple pair structure that provides suitable names for the members.  It
/// holds a combination of logging severity and debug level.
struct Level {
    Severity    severity;   ///< Logging severity
    int         dbglevel;   ///< Debug level

    Level(Severity sev = DEFAULT, int dbg = MIN_DEBUG_LEVEL) :
        severity(sev), dbglevel(dbg)
    {}

    // Default assignment and copy constructor is appropriate
};

/// \brief Returns the isc::log::Severity value represented by the given string
///
/// This must be one of the strings "DEBUG", "INFO", "WARN", "ERROR", "FATAL" or
/// "NONE". (Case is not important, but the string most not contain leading or
/// trailing spaces.)
///
/// \param sev_str The string representing severity value
///
/// \return The severity. If the string is not recognized, an error will be
///         logged and the string will return  isc::log::INFO.
isc::log::Severity getSeverity(const std::string& sev_str);

}   // namespace log
}   // namespace isc

#endif // LOGGER_LEVEL_H
