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

#include <algorithm>
#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>

#include "log/logger_level_impl.h"
#include "log/logger_manager_impl.h"
#include "log/logger_specification.h"
#include "log/root_logger_name.h"

#include "log/logger.h"
#include "log/messagedef.h"

#include "exceptions/exceptions.h"

// Generated exceptions.  Methods in this file can't log exceptions as they may
// occur when logging is disabled or in an inconsistent state.
class UnknownLoggingDestination : public isc::Exception {
public:
    UnknownLoggingDestination(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

// Reset hierarchy of loggers back to default settings.  This removes all
// appenders from loggers, sets their severity to NOT_SET (so that events are
// passed back to the parent) and resets the root logger to logging
// informational messages.  (This last is not a log4cplus default, so we have to
// explicitly reset the logging severity.)

using namespace std;

namespace isc {
namespace log {

// Reset hierarchy back to default.  Note that this does not delete existing
// loggers, it makes them inactive.  (So a logger is never removed, even if a
// configuration update removes the logger.)

void
LoggerManagerImpl::processInit() {
    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();
    initRootLogger();
}

// Process logging specification.  Set up the common states then dispatch to
// add output specifications.

void
LoggerManagerImpl::processSpecification(const LoggerSpecification& spec) {

    // Get/construct the logger for which this specification applies.
    log4cplus::Logger logger = (spec.getName() == getRootLoggerName()) ?
                               log4cplus::Logger::getRoot() :
                               log4cplus::Logger::getInstance(spec.getName());

    // Set severity level according to specification entry.
    logger.setLogLevel(LoggerLevelImpl::convertFromBindLevel(
                       Level(spec.getSeverity(), spec.getDbglevel())));

    // Set the additive flag.
    logger.setAdditivity(spec.getAdditive());

    // Output options given?
    if (spec.optionCount() > 0) {

        // Yes, so replace all appenders for this logger.
        logger.removeAllAppenders();

        // Now process output specifications.
        for (LoggerSpecification::const_iterator i = spec.begin();
             i != spec.end(); ++i) {
            switch (i->destination) {
            case OutputOption::DEST_CONSOLE:
                createConsoleAppender(logger, *i);
                break;

            case OutputOption::DEST_FILE:
                createFileAppender(logger, *i);
                break;

            case OutputOption::DEST_SYSLOG:
                createSyslogAppender(logger, *i);
                break;

            default:
                isc_throw(UnknownLoggingDestination,
                          "Unknown logging destination, code = " <<
                          i->destination);
            }
        }
    }
}

// Console appender - log to either stdout or stderr.
void
LoggerManagerImpl::createConsoleAppender(log4cplus::Logger& logger,
                                         const OutputOption& opt)
{
    log4cplus::SharedAppenderPtr console(
        new log4cplus::ConsoleAppender(
            (opt.stream == OutputOption::STR_STDERR), opt.flush));
    setConsoleAppenderLayout(console);
    logger.addAppender(console);
}

// File appender.  Depending on whether a maximum size is given, either
// a standard file appender or a rolling file appender will be created.
void
LoggerManagerImpl::createFileAppender(log4cplus::Logger& logger,
                                         const OutputOption& opt)
{
    LOG4CPLUS_OPEN_MODE_TYPE mode = 
        LOG4CPLUS_FSTREAM_NAMESPACE::ios::app;  // Append to existing file

    log4cplus::SharedAppenderPtr fileapp;
    if (opt.maxsize == 0) {
        fileapp = log4cplus::SharedAppenderPtr(new log4cplus::FileAppender(
            opt.filename, mode, opt.flush));
    } else {
        fileapp = log4cplus::SharedAppenderPtr(
            new log4cplus::RollingFileAppender(opt.filename, opt.maxsize,
                                               opt.maxver, opt.flush));
    }

    // use the same console layout for the files.
    setConsoleAppenderLayout(fileapp);
    logger.addAppender(fileapp);
}


// One-time initialization of the log4cplus system

void
LoggerManagerImpl::init(isc::log::Severity severity, int dbglevel) {

    // Set up basic configurator.  This attaches a ConsoleAppender to the
    // root logger with suitable output.  This is used until we we have
    // actually read the logging configuration, in which case the output
    // may well be changed.
    log4cplus::BasicConfigurator config;
    config.configure();

    // Add the additional debug levels
    LoggerLevelImpl::init();

    reset();
}

// Reset logging to default configuration.  This closes all appenders
// and resets the root logger to output INFO messages to the console.
// It is principally used in testing.
void
LoggerManagerImpl::reset() {

    // Initialize the root logger
    initRootLogger();
}

// Initialize the root logger
void LoggerManagerImpl::initRootLogger(isc::log::Severity severity,
                                       int dbglevel)
{
    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();

    // Set the severity for the root logger
    log4cplus::Logger::getRoot().setLogLevel(
            LoggerLevelImpl::convertFromBindLevel(Level(severity, dbglevel)));

    // Set the root to use a console logger.
    OutputOption opt;
    log4cplus::Logger root = log4cplus::Logger::getRoot();
    createConsoleAppender(root, opt);
}

// Set the the "console" layout for the given appenders.  This layout includes
// a date/time and the name of the logger.

void LoggerManagerImpl::setConsoleAppenderLayout(
        log4cplus::SharedAppenderPtr& appender)
{
    // Create the pattern we want for the output - local time.
    string pattern = "%D{%Y-%m-%d %H:%M:%S.%q} %-5p [";
    pattern += getRootLoggerName() + string(".%c] %m\n");

    // Finally the text of the message
    auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(pattern));
    appender->setLayout(layout);
}

} // namespace log
} // namespace isc
