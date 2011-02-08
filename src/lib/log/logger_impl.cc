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
// PERFORMANCE OF THIS SOFTWARE

// $Id$

#include <iostream>
#include <algorithm>

#include <stdarg.h>
#include <stdio.h>
#include <boost/lexical_cast.hpp>

#include <log/debug_levels.h>
#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>
#include <log/strutil.h>

using namespace std;

namespace isc {
namespace log {

// Static initializations

LoggerImpl::LoggerInfoMap LoggerImpl::logger_info_;
LoggerImpl::LoggerInfo LoggerImpl::root_logger_info_(isc::log::INFO, 0);

// Destructor. (Here because of virtual declaration.)

LoggerImpl::~LoggerImpl() {
}

// Return the name of the logger (fully-qualified with the root name if
// possible).

string LoggerImpl::getName() {
    string root_name = RootLoggerName::getName();
    if (root_name.empty() || (name_ == root_name)) {
        return (name_);
    }
    else {
        return (root_name + "." + name_);
    }
}

// Set the severity for logging.

void
LoggerImpl::setSeverity(isc::log::Severity severity, int dbglevel) {

    // Silently coerce the debug level into the valid range of 0 to 99

    int debug_level = max(MIN_DEBUG_LEVEL, min(MAX_DEBUG_LEVEL, dbglevel));
    if (isRootLogger()) {
        
        // Can only set severity for the root logger, you can't disable it.
        // Any attempt to do so is silently ignored.
        if (severity != isc::log::DEFAULT) {
            root_logger_info_ = LoggerInfo(severity, debug_level);
        }

    } else if (severity == isc::log::DEFAULT) {

        // Want to set to default; this means removing the information
        // about this logger from the logger_info_ if it is set.
        LoggerInfoMap::iterator i = logger_info_.find(name_);
        if (i != logger_info_.end()) {
            logger_info_.erase(i);
        }

    } else {

        // Want to set this information
        logger_info_[name_] = LoggerInfo(severity, debug_level);
    }
}

// Return severity level

isc::log::Severity
LoggerImpl::getSeverity() {

    if (isRootLogger()) {
        return (root_logger_info_.severity);
    }
    else {
        LoggerInfoMap::iterator i = logger_info_.find(name_);
        if (i != logger_info_.end()) {
           return ((i->second).severity);
        }
        else {
            return (isc::log::DEFAULT);
        }
    }
}

// Get effective severity.  Either the current severity or, if not set, the
// severity of the root level.

isc::log::Severity
LoggerImpl::getEffectiveSeverity() {
    if (! isRootLogger()) {

        // Not root logger, look this logger up in the map.
        LoggerInfoMap::iterator i = logger_info_.find(name_);
        if (i != logger_info_.end()) {

            // Found, so return the severity.
            return ((i->second).severity);
        }
    }

    // Must be the root logger, or this logger is defaulting to the root logger
    // settings.
    return (root_logger_info_.severity);
}

// Get the debug level.  This returns 0 unless the severity is DEBUG.

int
LoggerImpl::getDebugLevel() {

    if (! isRootLogger()) {

        // Not root logger, look this logger up in the map.
        LoggerInfoMap::iterator i = logger_info_.find(name_);
        if (i != logger_info_.end()) {

            // Found, so return the debug level.
            if ((i->second).severity == isc::log::DEBUG) {
                return ((i->second).dbglevel);
            } else {
                return (0);
            }
        }
    }

    // Must be the root logger, or this logger is defaulting to the root logger
    // settings.
    if (root_logger_info_.severity == isc::log::DEBUG) {
        return (root_logger_info_.dbglevel);
    } else {
        return (0);
    }
}

// The code for isXxxEnabled is quite simple and is in the header.  The only
// exception is isDebugEnabled() where we have the complication of the debug
// levels.

bool
LoggerImpl::isDebugEnabled(int dbglevel) {

    if (logger_info_.empty()) {

        // Nothing set, return information from the root logger.
        return ((root_logger_info_.severity <= isc::log::DEBUG) &&
            (root_logger_info_.dbglevel >= dbglevel));
    }

    // Something is in the general logger map, so we need to look up the
    // information.  We don't use getSeverity() and getDebugLevel() separately
    // as each involves a lookup in the map, something that we can optimise
    // here.

    if (! isRootLogger()) {

        // Not root logger, look this logger up in the map.
        LoggerInfoMap::iterator i = logger_info_.find(name_);
        if (i != logger_info_.end()) {

            // Found, so return the debug level.
            if ((i->second).severity <= isc::log::DEBUG) {
                return ((i->second).dbglevel >= dbglevel);
            } else {
                return (false); // Nothing lower than debug
            }
        }
    }

    // Must be the root logger, or this logger is defaulting to the root logger
    // settings.
    if (root_logger_info_.severity <= isc::log::DEBUG) {
        return (root_logger_info_.dbglevel > dbglevel);
    } else {
        return (false);
    }
}

// Output a general message

void
LoggerImpl::output(const char* sev_text, const MessageID& ident,
    const char* text)
{
    
    // Get the time in a struct tm format, and convert to text
    time_t t_time;
    time(&t_time);
    struct tm* tm_time = localtime(&t_time);

    char chr_time[32];
    (void) strftime(chr_time, sizeof(chr_time), "%Y-%m-%d %H:%M:%S", tm_time);
    chr_time[sizeof(chr_time) - 1] = '\0';  // Guarantee a trailing NULL

    // Now output.
    std::cout << chr_time << " " << sev_text << " [" << getName() << "] " <<
        ident << ", " << text << "\n";
}

} // namespace log
} // namespace isc
