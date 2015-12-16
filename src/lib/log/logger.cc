// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdarg.h>
#include <stdio.h>

#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/logger_name.h>
#include <log/logger_support.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>

#include <util/strutil.h>

using namespace std;

namespace isc {
namespace log {

// Initialize underlying logger, but only if logging has been initialized.
void Logger::initLoggerImpl() {
    if (isLoggingInitialized()) {
        loggerptr_ = new LoggerImpl(name_);
    } else {
        isc_throw(LoggingNotInitialized, "attempt to access logging function "
                  "before logging has been initialized");
    }
}

// Destructor.

Logger::~Logger() {
    delete loggerptr_;

    // The next statement is required for the Kea hooks framework, where a
    // statically-linked Kea loads and unloads multiple libraries. See the hooks
    // documentation for more details.
    loggerptr_ = 0;
}

// Get Version
std::string
Logger::getVersion() {
    return (LoggerImpl::getVersion());
}

// Get Name of Logger

std::string
Logger::getName() {
    return (getLoggerPtr()->getName());
}

// Set the severity for logging.

void
Logger::setSeverity(isc::log::Severity severity, int dbglevel) {
    getLoggerPtr()->setSeverity(severity, dbglevel);
}

// Return the severity of the logger.

isc::log::Severity
Logger::getSeverity() {
    return (getLoggerPtr()->getSeverity());
}

// Get Effective Severity Level for Logger

isc::log::Severity
Logger::getEffectiveSeverity() {
    return (getLoggerPtr()->getEffectiveSeverity());
}

// Debug level (only relevant if messages of severity DEBUG are being logged).

int
Logger::getDebugLevel() {
    return (getLoggerPtr()->getDebugLevel());
}

// Effective debug level (only relevant if messages of severity DEBUG are being
// logged).

int
Logger::getEffectiveDebugLevel() {
    return (getLoggerPtr()->getEffectiveDebugLevel());
}

// Check on the current severity settings

bool
Logger::isDebugEnabled(int dbglevel) {
    return (getLoggerPtr()->isDebugEnabled(dbglevel));
}

bool
Logger::isInfoEnabled() {
    return (getLoggerPtr()->isInfoEnabled());
}

bool
Logger::isWarnEnabled() {
    return (getLoggerPtr()->isWarnEnabled());
}

bool
Logger::isErrorEnabled() {
    return (getLoggerPtr()->isErrorEnabled());
}

bool
Logger::isFatalEnabled() {
    return (getLoggerPtr()->isFatalEnabled());
}

// Format a message: looks up the message text in the dictionary and formats
// it, replacing tokens with arguments.
//
// Owing to the use of variable arguments, this must be inline (hence the
// definition of the macro).  Also note that it expects that the message buffer
// "message" is declared in the compilation unit.

// Output methods

void
Logger::output(const Severity& severity, const std::string& message) {
    getLoggerPtr()->outputRaw(severity, message);
}

Logger::Formatter
Logger::debug(int dbglevel, const isc::log::MessageID& ident) {
    if (isDebugEnabled(dbglevel)) {
        return (Formatter(DEBUG, getLoggerPtr()->lookupMessage(ident),
                          this));
    } else {
        return (Formatter());
    }
}

Logger::Formatter
Logger::info(const isc::log::MessageID& ident) {
    if (isInfoEnabled()) {
        return (Formatter(INFO, getLoggerPtr()->lookupMessage(ident),
                          this));
    } else {
        return (Formatter());
    }
}

Logger::Formatter
Logger::warn(const isc::log::MessageID& ident) {
    if (isWarnEnabled()) {
        return (Formatter(WARN, getLoggerPtr()->lookupMessage(ident),
                          this));
    } else {
        return (Formatter());
    }
}

Logger::Formatter
Logger::error(const isc::log::MessageID& ident) {
    if (isErrorEnabled()) {
        return (Formatter(ERROR, getLoggerPtr()->lookupMessage(ident),
                          this));
    } else {
        return (Formatter());
    }
}

Logger::Formatter
Logger::fatal(const isc::log::MessageID& ident) {
    if (isFatalEnabled()) {
        return (Formatter(FATAL, getLoggerPtr()->lookupMessage(ident),
                          this));
    } else {
        return (Formatter());
    }
}

// Replace the interprocess synchronization object

void
Logger::setInterprocessSync(isc::log::interprocess::InterprocessSync* sync) {
    getLoggerPtr()->setInterprocessSync(sync);
}

// Comparison (testing only)

bool
Logger::operator==(Logger& other) {
    return (*getLoggerPtr() == *other.getLoggerPtr());
}

} // namespace log
} // namespace isc
