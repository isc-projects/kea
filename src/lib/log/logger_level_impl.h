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

#ifndef __LOGGER_LEVEL_IMPL_H
#define __LOGGER_LEVEL_IMPL_H

#include <log4cplus/logger.h>
#include <log/logger_level.h>

namespace isc {
namespace log {

/// \brief Implementation aspects of logging levels
///
/// This extends the log4cplus level set to allow 100 debug levels.
///
/// First some terminology, as the use of the term "level" gets confusing.  The
/// code and comments here use the term "level" in two contexts:
///
/// Logging level: The category of messages to log.  By default log4cplus
/// defines the following logging levels: OFF_LOG_LEVEL, FATAL_LOG_LEVEL,
/// ERROR_LOG_LEVEL, WARN_LOG_LEVEL, INFO_LOG_LEVEL, DEBUG_LOG_LEVEL,
/// TRACE_LOG_LEVEL, ALL_LOG_LEVEL (which here will be abbreviated OFF, FATAL
/// etc.).  Within the context of BIND-10, OFF, TRACE and ALL are not used
/// and the idea of DEBUG has been extended, as will be seen below.  In
/// BIND 10 terms, this is known as "severity"; the "logging level" usage will
/// usually be used when talking about log4cplus aspects of the idea (as
/// log4cplus uses that teminology).
///
/// Debug level: This is a number that ranges from 0 to 99 and is used by the
/// application to control the detail of debug output.  A value of 0 gives the
/// highest-level debug output; a value of 99 gives the most verbose and most
/// detailed. Debug messages (or whatever debug level) are only ever output
/// when the logging level is set to DEBUG. (Note that the numbers 0 and 99
/// are not hard-coded - they are the constants MIN_DEBUG_LEVEL and
/// MAX_DEBUG_LEVEL.)
///
/// With log4cplus, the various logging levels have a numeric value associated
/// with them, such that FATAL > ERROR > WARNING etc.  This suggests that the
/// idea of debug levels can be incorporated into the existing logging level
/// scheme by assigning them appropriate numeric values, i.e.
///
/// WARNING > INFO > DEBUG > DEBUG - 1 > DEBUG - 2 > ... > DEBUG - 99
///
/// Setting a numeric level of DEBUG enables the basic messages; setting higher
/// debug levels (corresponding to lower numeric logging levels) will enable
/// progressively more messages.  The lowest debug level (0) is chosen such that
/// it corresponds to the default level of DEBUG.
///
/// This class comprises nothing more than static methods to aid the conversion
/// of logging levels between log4cplus and BIND 10, and to register those
/// levels with log4cplus.

class LoggerLevelImpl {
public:

    /// \brief Convert BIND 10 level to log4cplus logging level
    ///
    /// Converts the BIND 10 severity level into a log4cplus logging level.
    /// If the severity is DEBUG, the current BIND 10 debug level is taken
    /// into account when doing the conversion.
    ///
    /// \param level BIND 10 severity and debug level
    ///
    /// \return Equivalent log4cplus logging level.
    static
    log4cplus::LogLevel convertFromBindLevel(const isc::log::Level& level);

    /// \brief Convert log4cplus logging level to BIND 10 logging level
    ///
    /// Converts the log4cplus log level into a BIND 10 severity level.
    /// The log4cplus log level may be non-standard in which case it is
    /// encoding a BIND 10 debug level as well.
    ///
    /// \param loglevel log4cplus log level
    ///
    /// \return Equivalent BIND 10 severity and debug level
    static
    isc::log::Level convertToBindLevel(const log4cplus::LogLevel loglevel);

    /// \brief Convert string to log4cplus logging level
    ///
    /// BIND 10 extends the set of logging levels in log4cplus with a group
    /// of debug levels.  These are given names DEBUG0 through DEBUG99 (with
    /// DEBUG0 being equivalent to DEBUG, the standard log level.  If the name
    /// is DEBUGn but n lies outside the range of debug levels, debug level
    /// specifies is coerced to the nearest valid value.  If the string is just
    /// not recognised, a NOT_SET_LOG_LEVEL is returned.
    ///
    /// \param level String representing the logging level.
    ///
    /// \return Corresponding log4cplus log level
    static
    log4cplus::LogLevel logLevelFromString(const log4cplus::tstring& level);

    /// \brief Convert log level to string
    ///
    /// If the log level is one of the extended debug levels, the string DEBUG
    /// is returned, otherwise the empty string.
    ///
    /// \param level Extended logging level
    ///
    /// \return Equivalent string.
    static log4cplus::tstring logLevelToString(log4cplus::LogLevel level);

    /// \brief Initialize extended logging levels
    ///
    /// This must be called once, after log4cplus has been initialized.  It
    /// registers the level/string converter functions.
    static void init();
};

} // namespace log
} // namespace isc

#endif // __LOGGER_LEVEL_IMPL_H
