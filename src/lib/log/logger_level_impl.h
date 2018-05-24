// Copyright (C) 2011-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_LEVEL_IMPL_H
#define LOGGER_LEVEL_IMPL_H

#include <log4cplus/logger.h>
#include <log4cplus/version.h>
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
/// etc.).  Within the context of Kea, OFF, TRACE and ALL are not used
/// and the idea of DEBUG has been extended, as will be seen below.  In
/// Kea terms, this is known as "severity"; the "logging level" usage will
/// usually be used when talking about log4cplus aspects of the idea (as
/// log4cplus uses that terminology).
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
/// of logging levels between log4cplus and Kea, and to register those
/// levels with log4cplus.

class LoggerLevelImpl {
public:

typedef log4cplus::tstring LogLevelString;

    /// \brief Convert Kea level to log4cplus logging level
    ///
    /// Converts the Kea severity level into a log4cplus logging level.
    /// If the severity is DEBUG, the current Kea debug level is taken
    /// into account when doing the conversion.
    ///
    /// \param level Kea severity and debug level
    ///
    /// \return Equivalent log4cplus logging level.
    static
    log4cplus::LogLevel convertFromBindLevel(const isc::log::Level& level);

    /// \brief Convert log4cplus logging level to Kea logging level
    ///
    /// Converts the log4cplus log level into a Kea severity level.
    /// The log4cplus log level may be non-standard in which case it is
    /// encoding a Kea debug level as well.
    ///
    /// \param loglevel log4cplus log level
    ///
    /// \return Equivalent Kea severity and debug level
    static
    isc::log::Level convertToBindLevel(const log4cplus::LogLevel loglevel);

    /// \brief Convert string to log4cplus logging level
    ///
    /// Kea extends the set of logging levels in log4cplus with a group
    /// of debug levels.  These are given names DEBUG0 through DEBUG99 (with
    /// DEBUG0 being equivalent to DEBUG, the standard log level.  If the name
    /// is DEBUGn but n lies outside the range of debug levels, debug level
    /// specifies is coerced to the nearest valid value.  If the string is just
    /// not recognized, a NOT_SET_LOG_LEVEL is returned.
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
#if LOG4CPLUS_VERSION < LOG4CPLUS_MAKE_VERSION(2, 0, 0)
    static LogLevelString logLevelToString(log4cplus::LogLevel level);
#else
    static const LogLevelString& logLevelToString(log4cplus::LogLevel level);
#endif

    /// \brief Initialize extended logging levels
    ///
    /// This must be called once, after log4cplus has been initialized.  It
    /// registers the level/string converter functions.
    static void init();
};

} // namespace log
} // namespace isc

#endif // LOGGER_LEVEL_IMPL_H
