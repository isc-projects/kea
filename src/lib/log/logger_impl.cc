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

// Note: as log4cplus and the BIND 10 logger have many concepts in common, and
// thus many similar names, to disambiguate types we don't "use" the log4cplus
// namespace: instead, all log4cplus types are explicitly qualified.

using namespace std;

namespace isc {
namespace log {

// Constructor
LoggerImpl::LoggerImpl(const string& name)
{
    // Initialize log4cplus if not already done
    initLog4cplus();

    // Are we the root logger?
    if (name == getRootLoggerName()) {
        name_ = name;
        logger_ = log4cplus::Logger::getRoot();

    } else {
        name_ = getRootLoggerName() + "." + name;
        logger_ = log4cplus::Logger::getInstance(name);
    }
}

// Destructor. (Here because of virtual declaration.)

LoggerImpl::~LoggerImpl() {
}

// Set the severity for logging.
void
LoggerImpl::setSeverity(isc::log::Severity severity, int dbglevel) {
    Level level(severity, dbglevel);
    logger_.setLogLevel(LoggerLevelImpl::convertFromBindLevel(level));
}

// Return severity level
isc::log::Severity
LoggerImpl::getSeverity() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getLogLevel());
    return level.severity;
}

// Return current debug level (only valid if current severity level is DEBUG).
int
LoggerImpl::getDebugLevel() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getLogLevel());
    return level.dbglevel;
}

// Get effective severity.  Either the current severity or, if not set, the
// severity of the root level.
isc::log::Severity
LoggerImpl::getEffectiveSeverity() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getChainedLogLevel());
    return level.severity;
}

// Return effective debug level (only valid if current effective severity level
// is DEBUG).
int
LoggerImpl::getEffectiveDebugLevel() {
    Level level = LoggerLevelImpl::convertToBindLevel(logger_.getChainedLogLevel());
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
            LOG4CPLUS_DEBUG(logger_, message);
            break;

        case INFO:
            LOG4CPLUS_INFO(logger_, message);
            break;

        case WARN:
            LOG4CPLUS_WARN(logger_, message);
            break;

        case ERROR:
            LOG4CPLUS_ERROR(logger_, message);
            break;

        case FATAL:
            LOG4CPLUS_FATAL(logger_, message);
    }
}

// Initialization.  This is one initialization for all loggers, so requires
// a singleton to hold the initialization flag.  The flag is held within a
// static method to ensure that it is created (and initialized) when needed.
// This avoids a static initialization fiasco.

bool&
LoggerImpl::initialized() {
    static bool initialized = false;
    return (initialized);
}

void
LoggerImpl::initLog4cplus() {

    if (! initialized()) {

        // Set up basic configurator.  This attaches a ConsoleAppender to the
        // root logger with suitable output.  This is used until we we have
        // actually read the logging configuration, in which case the output
        // may well be changed.
        log4cplus::BasicConfigurator config;
        config.configure();
        setRootAppenderLayout();

        // Add additional debug levels
        LoggerLevelImpl::init();

        // All done.
        initialized() = true;
    }
}

void LoggerImpl::setRootAppenderLayout() {

    // Create the pattern we want for the output - local time.
    string pattern = "%D{%Y-%m-%d %H:%M:%S.%q} %-5p [";
    pattern += getRootLoggerName() + string(".%c] %m\n");

    // Retrieve the appenders on the root instance and set the layout to
    // use that pattern.
    log4cplus::SharedAppenderPtrList list =
        log4cplus::Logger::getRoot().getAllAppenders();

    for (log4cplus::SharedAppenderPtrList::iterator i = list.begin();
         i != list.end(); ++i) {
        auto_ptr<log4cplus::Layout> layout(
            new log4cplus::PatternLayout(pattern));
        (*i)->setLayout(layout);
    }
}

// Reset.  Just reset logger hierarchy to default settings (don't remove the
// loggers - this appears awkward); this is effectively the same as removing
// them.
void
LoggerImpl::reset() {
    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();
    initialized() = false;

    // N.B.  The documentation is not clear, but it does not appear that the
    // methods used to format the new logging levels are removed from the
    // log4cxx LogLevelManager class - indeed, there appears to be no way
    // to do this.  This would seem to suggest that a re-initialization may
    // well add another instance of the toString/fromString to the manager's
    // list of methods.
    //
    // We could get round this by making setting the LogManager a truly
    // one-shot process.  However, apart from taking up memory there is little
    // overhead if multiple instances are added.  The manager walks the list and
    // uses the first method that processes the argument, so multiple methods
    // doing the same think will not affect functionality.  Besides, this
    // reset() method is only used in testing and not in the distributed
    // software.
}


} // namespace log
} // namespace isc
