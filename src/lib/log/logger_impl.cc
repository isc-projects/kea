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

#include <iomanip>
#include <algorithm>

#include <stdarg.h>
#include <stdio.h>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>

#include <log4cplus/configurator.h>

#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/logger_level.h>
#include <log/logger_level_impl.h>
#include <log/logger_impl.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>

#include <util/strutil.h>

using namespace std;
using namespace log4cplus;

namespace isc {
namespace log {

// Static initializations


// Constructor
LoggerImpl::LoggerImpl(const std::string& name)
{
    // Initialize log4cplus if not already done
    initLog4cplus();

    // Are we the root logger?
    if (name == getRootLoggerName()) {
        name_ = name;
        logger_ = log4cplus::Logger::getRoot();

    } else {
        name_ = getRootLoggerName() + "." + name;
        logger_ = log4cplus::Logger::getInstance(name_);
    }

    // Create a formatted name for use in messages (speeds up formatting if
    // we do it now.)
    fmt_name_ = std::string("[") + name_ + std::string("] ");
}

// Destructor. (Here because of virtual declaration.)

LoggerImpl::~LoggerImpl() {
}

// Set the severity for logging.
void
LoggerImpl::setSeverity(isc::log::Severity severity, int dbglevel) {
    isc::log::Level level(severity, dbglevel);
    logger_.setLogLevel(LoggerLevelImpl::convertFromBindLevel(level));
}

// Return severity level
isc::log::Severity
LoggerImpl::getSeverity() {
    isc::log::Level level =
        LoggerLevelImpl::convertToBindLevel(logger_.getLogLevel());
    return level.severity;
}

// Return current debug level (only valid if current severity level is DEBUG).
int
LoggerImpl::getDebugLevel() {
    isc::log::Level level =
        LoggerLevelImpl::convertToBindLevel(logger_.getLogLevel());
    return level.dbglevel;
}

// Get effective severity.  Either the current severity or, if not set, the
// severity of the root level.
isc::log::Severity
LoggerImpl::getEffectiveSeverity() {
    isc::log::Level level = 
        LoggerLevelImpl::convertToBindLevel(logger_.getChainedLogLevel());
    return level.severity;
}

// Return effective debug level (only valid if current effective severity level
// is DEBUG).
int
LoggerImpl::getEffectiveDebugLevel() {
    isc::log::Level level =
        LoggerLevelImpl::convertToBindLevel(logger_.getChainedLogLevel());
    return level.dbglevel;
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

// One-time initialization of log4cplus


void
LoggerImpl::initLog4cplus() {
    static bool not_initialized = true;

    if (not_initialized) {
        // Set up basic configurator
        log4cplus::BasicConfigurator config;
        config.configure();

        // Add additional debug levels
        LoggerLevelImpl::init();

        // All done.
        not_initialized = false;
    }
}

} // namespace log
} // namespace isc
