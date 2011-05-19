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
// PERFORMANCE OF THIS SOFTWARE

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <stdarg.h>
#include <stdio.h>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>

#include <log4cplus/configurator.h>

#include <log/debug_levels.h>
#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/logger_levels.h>
#include <log/logger_impl.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>

#include <util/strutil.h>

using namespace std;

namespace isc {
namespace log {

// Static initializations


// Constructor
LoggerImpl::LoggerImpl(const std::string& name, bool)
{
    // Are we the root logger?
    if (name == getRootLoggerName()) {
        is_root_ = true;
        name_ = name;
    } else {
        is_root_ = false;
        name_ = getRootLoggerName() + "." + name;
    }
    fmt_name_ = std::string("[") + name_ + std::string("] ");

    // Initialize log4cplus if not already done
    initLog4cplus();

    // Return existing instance of logger, creating it if it does not exist.
    logger_ = log4cplus::Logger::getInstance(name_);
}

// Destructor. (Here because of virtual declaration.)

LoggerImpl::~LoggerImpl() {
}

// Set the severity for logging.
// TODO IGNORE DEBUG LEVEL FOR NOW

void
LoggerImpl::setSeverity(isc::log::Severity severity, int /*dbglevel*/) {

    // Silently coerce the debug level into the valid range of 0 to 99

    //int debug_level = max(MIN_DEBUG_LEVEL, min(MAX_DEBUG_LEVEL, dbglevel));
    logger_.setLogLevel(convertFromBindSeverity(severity));
}

// Return severity level

isc::log::Severity
LoggerImpl::getSeverity() {
    return convertToBindSeverity(logger_.getLogLevel());
}

// Get effective severity.  Either the current severity or, if not set, the
// severity of the root level.

isc::log::Severity
LoggerImpl::getEffectiveSeverity() {
    return convertToBindSeverity(logger_.getChainedLogLevel());
}


// Get the debug level.  This returns 0 unless the severity is DEBUG.
// TODO: DEBUG LEVEL IGNORED FOR NOW

int
LoggerImpl::getDebugLevel() {
    return (0);
}

// The code for isXxxEnabled is quite simple and is in the header.  The only
// exception is isDebugEnabled() where we have the complication of the debug
// levels.
// TODO: DEBUG LEVEL IGNORED FOR NOW

bool
LoggerImpl::isDebugEnabled(int dbglevel) {
    return logger_.isEnabledFor(log4cplus::DEBUG_LOG_LEVEL);
}


// Output a general message
string*
LoggerImpl::lookupMessage(const MessageID& ident) {
    return (new string(string(ident) + ", " +
                       MessageDictionary::globalDictionary().getText(ident)));
}

void
LoggerImpl::outputRaw(const Severity& severity, const string& message) {
    switch (severity) {
        case DEBUG:
            LOG4CPLUS_DEBUG(logger_, fmt_name_ << message);
            break;

        case INFO:
            LOG4CPLUS_INFO(logger_, fmt_name_ << message);
            break;

        case WARN:
            LOG4CPLUS_WARN(logger_, fmt_name_ << message);
            break;

        case ERROR:
            LOG4CPLUS_ERROR(logger_, fmt_name_ << message);
            break;

        case FATAL:
            LOG4CPLUS_FATAL(logger_, fmt_name_ << message);
    }
}

// Convert levels - from BIND 10 level to log4cplus level.
// Namespaces explicitly used to clarify what level we are talking about
log4cplus::LogLevel
LoggerImpl::convertFromBindSeverity(const isc::log::Severity& inlevel) {

    // BIND 10 logging levels are small integers so we can do a table lookup
    static const log4cplus::LogLevel level[] = {
        log4cplus::NOT_SET_LOG_LEVEL,
        log4cplus::DEBUG_LOG_LEVEL,
        log4cplus::INFO_LOG_LEVEL,
        log4cplus::WARN_LOG_LEVEL,
        log4cplus::ERROR_LOG_LEVEL,
        log4cplus::FATAL_LOG_LEVEL,
        log4cplus::OFF_LOG_LEVEL
    };

    // ... with compile-time checks to ensure that table indexes are correct.
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::DEFAULT) == 0);
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::DEBUG) == 1);
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::INFO) == 2);
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::WARN) == 3);
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::ERROR) == 4);
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::FATAL) == 5);
    BOOST_STATIC_ASSERT(static_cast<int>(isc::log::NONE) == 6);

    // No need to check that the iundex is out of range.  Setting the type of
    // the argument to isc::log::Severity ensures that it must be one of the
    // Severity enum members - conversion of a numeric value to an enum is not
    // permitted.
    return (level[inlevel]);
}

// Convert levels - from log4plus level to BIND 10 level
// Namespaces explicitly used to clarify what level we are talking about
isc::log::Severity
LoggerImpl::convertToBindSeverity(const log4cplus::LogLevel& inlevel) {

    // Not easy to do a table lookup as the numerical values of log4cplus levels
    // are quite high.
    switch (inlevel) {
        case log4cplus::NOT_SET_LOG_LEVEL:
            return (isc::log::DEFAULT);

        case log4cplus::DEBUG_LOG_LEVEL:
            return (isc::log::DEBUG);

        case log4cplus::INFO_LOG_LEVEL:
            return (isc::log::INFO);

        case log4cplus::WARN_LOG_LEVEL:
            return (isc::log::WARN);

        case log4cplus::ERROR_LOG_LEVEL:
            return (isc::log::ERROR);

        case log4cplus::FATAL_LOG_LEVEL:
            return (isc::log::FATAL);
    }

    return (isc::log::NONE);
}

// One-time initialization of log4cplus


void
LoggerImpl::initLog4cplus() {
    static bool not_initialized = true;

    if (not_initialized) {
        log4cplus::BasicConfigurator config;
        config.configure();
        not_initialized = false;
    }
}

} // namespace log
} // namespace isc
