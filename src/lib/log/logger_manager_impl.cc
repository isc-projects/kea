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

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>

#include "log/logger_level_impl.h"
#include "log/logger_manager_impl.h"
#include "log/logger_specification.h"
#include "log/root_logger_name.h"

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

namespace isc {
namespace log {

// Reset hierarchy back to default.  Note that this does not delete existing
// loggers, it makes them inactive.  (So a logger is never removed, even if a
// configuration update removes the logger.)

void
LoggerManagerImpl::processInit() {
    log4cplus::Logger::getDefaultHierarchy().resetConfiguration();
    log4cplus::Logger::getRoot().setLogLevel(log4cplus::INFO_LOG_LEVEL);
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
                      "Unknown logging destination, code = " << i->destination);
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
    logger.addAppender(console);
}


} // namespace log
} // namespace isc
