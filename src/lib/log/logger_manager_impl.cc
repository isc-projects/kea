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
#include <log4cplus/hierarchy.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/syslogappender.h>

#include <log/logger.h>
#include <log/logger_support.h>
#include <log/logger_level_impl.h>
#include <log/logger_manager.h>
#include <log/logger_manager_impl.h>
#include <log/log_messages.h>
#include <log/logger_name.h>
#include <log/logger_specification.h>
#include <log/buffer_appender_impl.h>

using namespace std;

namespace isc {
namespace log {

// Reset hierarchy of loggers back to default settings.  This removes all
// appenders from loggers, sets their severity to NOT_SET (so that events are
// passed back to the parent) and resets the root logger to logging
// informational messages.  (This last is not a log4cplus default, so we have to
// explicitly reset the logging severity.)
void
LoggerManagerImpl::processInit() {
    storeBufferAppenders();

    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();
    initRootLogger();
}

// Flush the LogBuffer at the end of processing a new specification
void
LoggerManagerImpl::processEnd() {
    flushBufferAppenders();
}

// Process logging specification.  Set up the common states then dispatch to
// add output specifications.
void
LoggerManagerImpl::processSpecification(const LoggerSpecification& spec) {
    log4cplus::Logger logger = log4cplus::Logger::getInstance(
                                   expandLoggerName(spec.getName()));

    // Set severity level according to specification entry.
    logger.setLogLevel(LoggerLevelImpl::convertFromBindLevel(
                       Level(spec.getSeverity(), spec.getDbglevel())));

    // Set the additive flag.
    logger.setAdditivity(spec.getAdditive());

    // Output options given?
    if (spec.optionCount() > 0) {
        // Replace all appenders for this logger.
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
                // Not a valid destination.  As we are in the middle of updating
                // logging destinations, we could be in the situation where
                // there are no valid appenders.  For this reason, throw an
                // exception.
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
    // Append to existing file
    std::ios::openmode mode = std::ios::app;

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

void
LoggerManagerImpl::createBufferAppender(log4cplus::Logger& logger) {
    log4cplus::SharedAppenderPtr bufferapp(new internal::BufferAppender());
    bufferapp->setName("buffer");
    logger.addAppender(bufferapp);
    // Since we do not know at what level the loggers will end up
    // running, set it to the highest for now
    logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
}

// Syslog appender.
void
LoggerManagerImpl::createSyslogAppender(log4cplus::Logger& logger,
                                         const OutputOption& opt)
{
    log4cplus::SharedAppenderPtr syslogapp(
        new log4cplus::SysLogAppender(opt.facility));
    setSyslogAppenderLayout(syslogapp);
    logger.addAppender(syslogapp);
}


// One-time initialization of the log4cplus system
void
LoggerManagerImpl::init(isc::log::Severity severity, int dbglevel,
                        bool buffer)
{
    // Set up basic configurator.  This attaches a ConsoleAppender to the
    // root logger with suitable output.  This is used until we we have
    // actually read the logging configuration, in which case the output
    // may well be changed.
    log4cplus::BasicConfigurator config;
    config.configure();

    // Add the additional debug levels
    LoggerLevelImpl::init();

    initRootLogger(severity, dbglevel, buffer);
}

// Reset logging to default configuration.  This closes all appenders
// and resets the root logger to output INFO messages to the console.
// It is principally used in testing.
void
LoggerManagerImpl::reset(isc::log::Severity severity, int dbglevel)
{
    // Initialize the root logger
    initRootLogger(severity, dbglevel);
}

// Initialize the root logger
void LoggerManagerImpl::initRootLogger(isc::log::Severity severity,
                                       int dbglevel, bool buffer)
{
    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();

    // Set the log4cplus root to not output anything - effectively we are
    // ignoring it.
    log4cplus::Logger::getRoot().setLogLevel(log4cplus::OFF_LOG_LEVEL);

    // Set the level for the BIND 10 root logger to the given severity and
    // debug level.
    log4cplus::Logger b10root = log4cplus::Logger::getInstance(
                                                    getRootLoggerName());
    b10root.setLogLevel(LoggerLevelImpl::convertFromBindLevel(
                                                    Level(severity, dbglevel)));

    if (buffer) {
        createBufferAppender(b10root);
    } else {
        OutputOption opt;
        createConsoleAppender(b10root, opt);
    }
}

void LoggerManagerImpl::setConsoleAppenderLayout(
        log4cplus::SharedAppenderPtr& appender)
{
    // Create the pattern we want for the output - local time.
    string pattern = "%D{%Y-%m-%d %H:%M:%S.%q} %-5p [%c/%i] %m\n";

    // Finally the text of the message
    auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(pattern));
    appender->setLayout(layout);
}

// Set the the "syslog" layout for the given appenders.  This is the same
// as the console, but without the timestamp (which is expected to be
// set by syslogd).

void LoggerManagerImpl::setSyslogAppenderLayout(
        log4cplus::SharedAppenderPtr& appender)
{
    // Create the pattern we want for the output - local time.
    string pattern = "%-5p [%c] %m\n";

    // Finally the text of the message
    auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(pattern));
    appender->setLayout(layout);
}

void LoggerManagerImpl::storeBufferAppenders() {
    // Walk through all loggers, and find any buffer appenders there
    log4cplus::LoggerList loggers = log4cplus::Logger::getCurrentLoggers();
    log4cplus::LoggerList::iterator it;
    for (it = loggers.begin(); it != loggers.end(); ++it) {
        log4cplus::SharedAppenderPtr buffer_appender =
            it->getAppender("buffer");
        if (buffer_appender) {
            buffer_appender_store_.push_back(buffer_appender);
        }
    }
}

void LoggerManagerImpl::flushBufferAppenders() {
    std::vector<log4cplus::SharedAppenderPtr> copy;
    buffer_appender_store_.swap(copy);

    std::vector<log4cplus::SharedAppenderPtr>::iterator it;
    for (it = copy.begin(); it != copy.end(); ++it) {
        internal::BufferAppender* app =
            dynamic_cast<internal::BufferAppender*>(it->get());
        assert(app != NULL);
        app->flush();
    }
}

} // namespace log
} // namespace isc
