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

#include <boost/scoped_ptr.hpp>

using namespace std;

namespace isc {
namespace log {

class LogBuffer {
public:
    LogBuffer() {
        flushed_ = false;
    }

    ~LogBuffer() {
        // If there is anything left in the buffer,
        // it means no reconfig has been done, and
        // we can assume the logging system was either
        // never setup, or broke while doing so.
        // So dump all that is left to stdout
        flush_stdout();
    }
    void add(const log4cplus::spi::InternalLoggingEvent& event) {
        if (flushed_) {
            isc_throw(isc::Exception, "BUFFER APPEND AFTER FLUSH");
        }
        stored_.push_back(log4cplus::spi::InternalLoggingEvent(event));
    }
    void flush_stdout() {
        // This does not show a bit of information normal log messages
        // do, so perhaps we should try and setup a new logger here
        // However, as this is called from a destructor, it may not
        // be a good idea.
        for (size_t i = 0; i < stored_.size(); ++i) {
            std::cout << stored_.at(i).getMessage() << std::endl;
            log4cplus::Logger logger = log4cplus::Logger::getInstance(stored_.at(i).getLoggerName());

            logger.log(stored_.at(i).getLogLevel(), stored_.at(i).getMessage());
        }
        stored_.clear();
    }
    //void flush(log4cplus::Logger& logger) {
    void flush() {
        for (size_t i = 0; i < stored_.size(); ++i) {
            const log4cplus::spi::InternalLoggingEvent event(stored_.at(i));
            //logger.log(event.getLogLevel(), event.getMessage());
            // Flush to the last defined logger
            log4cplus::Logger logger = log4cplus::Logger::getInstance(event.getLoggerName());

            logger.log(event.getLogLevel(), event.getMessage());
        }
        stored_.clear();
        flushed_ = true;
    }
private:
    std::vector<log4cplus::spi::InternalLoggingEvent> stored_;
    bool flushed_;
};

LogBuffer& getLogBuffer() {
    static boost::scoped_ptr<LogBuffer> log_buffer(NULL);
    if (!log_buffer) {
        log_buffer.reset(new LogBuffer);
    }
    return (*log_buffer);
}



// Reset hierarchy of loggers back to default settings.  This removes all
// appenders from loggers, sets their severity to NOT_SET (so that events are
// passed back to the parent) and resets the root logger to logging
// informational messages.  (This last is not a log4cplus default, so we have to
// explicitly reset the logging severity.)
void
LoggerManagerImpl::processInit() {
    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();
    initRootLogger();
}

// Process logging specification.  Set up the common states then dispatch to
// add output specifications.
void
LoggerManagerImpl::processSpecification(const LoggerSpecification& spec) {
    log4cplus::Logger logger;
    // If this is an 'empty' specification, just set the root logger
    if (spec.getName() == "") {
        logger = log4cplus::Logger::getInstance(getRootLoggerName());
    } else {
        logger = log4cplus::Logger::getInstance(
                                   expandLoggerName(spec.getName()));
    }

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
                // Not a valid destination.  As we are in the middle of updating
                // logging destinations, we could be in the situation where
                // there are no valid appenders.  For this reason, throw an
                // exception.
                isc_throw(UnknownLoggingDestination,
                          "Unknown logging destination, code = " <<
                          i->destination);
            }
        }
    } else {
        // If no output options are given, use a default appender
        // Yes, so replace all appenders for this logger.
        logger.removeAllAppenders();
        OutputOption opt;
        createConsoleAppender(logger, opt);
    }
    // Should anything be left in the buffer, this is the time to flush it.
    getLogBuffer().flush();
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

class BufferAppender : public log4cplus::Appender {
public:
    BufferAppender() {}

    virtual void close() {
        //relog();
        //log2out();
    }
    virtual void append(const log4cplus::spi::InternalLoggingEvent& event) {
        getLogBuffer().add(event);
    }
};

void
LoggerManagerImpl::createBufferAppender(log4cplus::Logger& logger)
{
    log4cplus::SharedAppenderPtr bufferapp(new BufferAppender());
    bufferapp->setName("buffer");
    logger.addAppender(bufferapp);
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

    reset(severity, dbglevel, buffer);
}

// Reset logging to default configuration.  This closes all appenders
// and resets the root logger to output INFO messages to the console.
// It is principally used in testing.
void
LoggerManagerImpl::reset(isc::log::Severity severity, int dbglevel,
                         bool buffer)
{
    // Initialize the root logger
    initRootLogger(severity, dbglevel, buffer);
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

} // namespace log
} // namespace isc
