// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <algorithm>
#include <string.h>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include <log4cplus/logger.h>

#include <log/logger_level.h>
#include <log/logger_level_impl.h>
#include <log/logimpl_messages.h>
#include <log/macros.h>

using namespace log4cplus;
using namespace std;

namespace {
isc::log::Logger logger("log");
}

namespace isc {
namespace log {

// Convert Kea level to a log4cplus logging level.
log4cplus::LogLevel
LoggerLevelImpl::convertFromBindLevel(const Level& level) {

    // Kea logging levels are small integers so we can do a table lookup
    static const log4cplus::LogLevel log4cplus_levels[] = {
        log4cplus::NOT_SET_LOG_LEVEL,
        log4cplus::DEBUG_LOG_LEVEL,
        log4cplus::INFO_LOG_LEVEL,
        log4cplus::WARN_LOG_LEVEL,
        log4cplus::ERROR_LOG_LEVEL,
        log4cplus::FATAL_LOG_LEVEL,
        log4cplus::OFF_LOG_LEVEL
    };

    // ... with compile-time checks to ensure that table indexes are correct.
    BOOST_STATIC_ASSERT(static_cast<int>(DEFAULT) == 0);
    BOOST_STATIC_ASSERT(static_cast<int>(DEBUG) == 1);
    BOOST_STATIC_ASSERT(static_cast<int>(INFO) == 2);
    BOOST_STATIC_ASSERT(static_cast<int>(WARN) == 3);
    BOOST_STATIC_ASSERT(static_cast<int>(ERROR) == 4);
    BOOST_STATIC_ASSERT(static_cast<int>(FATAL) == 5);
    BOOST_STATIC_ASSERT(static_cast<int>(NONE) == 6);

    // Do the conversion
    if (level.severity == DEBUG) {

        // Debug severity, so the log4cplus level returned depends on the
        // debug level.  Silently limit the debug level to the range
        // MIN_DEBUG_LEVEL to MAX_DEBUG_LEVEL (avoids the hassle of throwing
        // and catching exceptions and besides, this is for debug information).
        int limited = std::max(MIN_DEBUG_LEVEL,
                               std::min(level.dbglevel, MAX_DEBUG_LEVEL));
        LogLevel newlevel = static_cast<int>(DEBUG_LOG_LEVEL -
                                            (limited - MIN_DEBUG_LEVEL));
        return (static_cast<log4cplus::LogLevel>(newlevel));

    } else {

        // Can do a table lookup to speed things up.  There is no need to check
        // that the index is out of range.  That the variable is of type
        // isc::log::Severity ensures that it must be one of the Severity enum
        // members - conversion of a numeric value to an enum is not permitted.
        return (log4cplus_levels[level.severity]);
    }
}

// Convert log4cplus logging level to Kea debug level.  It is up to the
// caller to validate that the debug level is valid.
Level
LoggerLevelImpl::convertToBindLevel(const log4cplus::LogLevel loglevel) {

    // Not easy to do a table lookup as the numerical values of log4cplus levels
    // are quite high.
    if (loglevel <= log4cplus::NOT_SET_LOG_LEVEL) {
        return (Level(DEFAULT));

    } else if (loglevel <= log4cplus::DEBUG_LOG_LEVEL) {

        // Debug severity, so extract the debug level from the numeric value.
        // If outside the limits, change the severity to the level above or
        // below.
        int dbglevel = MIN_DEBUG_LEVEL +
                       static_cast<int>(log4cplus::DEBUG_LOG_LEVEL) -
                       static_cast<int>(loglevel);
        if (dbglevel > MAX_DEBUG_LEVEL) {
            return (Level(DEFAULT));
        } else if (dbglevel < MIN_DEBUG_LEVEL) {
            return (Level(INFO));
        }
        return (Level(DEBUG, dbglevel));

    } else if (loglevel <= log4cplus::INFO_LOG_LEVEL) {
        return (Level(INFO));

    } else if (loglevel <= log4cplus::WARN_LOG_LEVEL) {
        return (Level(WARN));

    } else if (loglevel <= log4cplus::ERROR_LOG_LEVEL) {
        return (Level(ERROR));

    } else if (loglevel <= log4cplus::FATAL_LOG_LEVEL) {
        return (Level(FATAL));

    }

    return (Level(NONE));
}


// Convert string to appropriate logging level
log4cplus::LogLevel
LoggerLevelImpl::logLevelFromString(const log4cplus::tstring& level) {

    std::string name = level;       // Get to known type
    size_t length = name.size();    // Length of the string

    if (length < 5) {

        // String can't possibly start DEBUG so we don't know what it is.
        // As per documentation, return NOT_SET level.
        return (NOT_SET_LOG_LEVEL);
    }
    else {
        if (strncasecmp(name.c_str(), "DEBUG", 5) == 0) {

            // String starts "DEBUG" (or "debug" or any case mixture).  The
            // rest of the string - if any - should be a number.
            if (length == 5) {

                // It is plain "DEBUG".  Take this as level 0.
                return (DEBUG_LOG_LEVEL);
            }
            else {

                // Try converting the remainder to an integer.  The "5" is
                // the length of the string "DEBUG".  Note that if the number
                // is outside the range of debug levels, it is coerced to the
                // nearest limit.  Thus a level of DEBUG509 will end up as
                // if DEBUG99 has been specified.
                try {
                    int dbglevel = boost::lexical_cast<int>(name.substr(5));
                    if (dbglevel < MIN_DEBUG_LEVEL) {
                        LOG_WARN(logger, LOGIMPL_BELOW_MIN_DEBUG).arg(dbglevel)
                            .arg(MIN_DEBUG_LEVEL);
                        dbglevel = MIN_DEBUG_LEVEL;

                    } else if (dbglevel > MAX_DEBUG_LEVEL) {
                        LOG_WARN(logger, LOGIMPL_ABOVE_MAX_DEBUG).arg(dbglevel)
                            .arg(MAX_DEBUG_LEVEL);
                        dbglevel = MAX_DEBUG_LEVEL;

                    }
                    return convertFromBindLevel(Level(DEBUG, dbglevel));
                }
                catch (boost::bad_lexical_cast&) {
                    LOG_ERROR(logger, LOGIMPL_BAD_DEBUG_STRING).arg(name);
                    return (NOT_SET_LOG_LEVEL);
                }
            }
        } else {

            // Unknown string - return default.  Log4cplus will call any other
            // registered conversion functions to interpret it.
            return (NOT_SET_LOG_LEVEL);
        }
    }
}

// Convert logging level to string.  If the level is a valid debug level,
// return the string DEBUG, else return the empty string.
LoggerLevelImpl::LogLevelString
LoggerLevelImpl::logLevelToString(log4cplus::LogLevel level) {
    static const tstring debug_string("DEBUG");
    static const tstring empty_string;
    Level bindlevel = convertToBindLevel(level);
    Severity& severity = bindlevel.severity;
    int& dbglevel = bindlevel.dbglevel;

    if ((severity == DEBUG) &&
        ((dbglevel >= MIN_DEBUG_LEVEL) && (dbglevel <= MAX_DEBUG_LEVEL))) {
        return (debug_string);
    }

    // Unknown, so return empty string for log4cplus to try other conversion
    // functions.
    return (empty_string);
}

// Initialization.  Register the conversion functions with the LogLevelManager.
void
LoggerLevelImpl::init() {

    // Get the singleton log-level manager.
    LogLevelManager& manager = getLogLevelManager();

    // Register the conversion functions
    manager.pushFromStringMethod(LoggerLevelImpl::logLevelFromString);
    manager.pushToStringMethod(LoggerLevelImpl::logLevelToString);
}

} // namespace log
} // namespace isc
