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

#ifndef __LOGGER_MANAGER_IMPL_H
#define __LOGGER_MANAGER_IMPL_H

#include <string>

#include <log4cplus/appender.h>
#include <log/logger_level.h>

// Forward declaration to avoid need to include log4cplus header file here.
namespace log4cplus {
class Logger;
class Appender;
}

namespace isc {
namespace log {

// Forward declarations
class LoggerSpecification;
class OutputOption;

/// \brief Logger Manager Implementation
///
/// This is the implementation of the logger manager for the log4cplus
/// underlying logger.
///
/// As noted in logger_manager.h, the logger manager class exists to set up the
/// logging given a set of specifications.  This class handles the processing
/// of those specifications.
///
/// Note: the logging has been implemented using a "pimpl" idiom to conceal
/// the underlying implementation (log4cplus) from the BIND 10 interface.
/// This requires that there be an implementation class, even though in this
/// case, all the implementation class methods can be declared static.

class LoggerManagerImpl {
public:

    /// \brief Constructor
    LoggerManagerImpl()
    {}

    /// \brief Initialize Processing
    ///
    /// This resets the hierachy of loggers back to their defaults.  This means
    /// that all non-root loggers (if they exist) are set to NOT_SET, and the
    /// root logger reset to logging informational messages.
    ///
    /// \param root_name BIND 10 name of the root logger
    static void processInit();

    /// \brief Process Specification
    ///
    /// Processes the specification for a single logger.
    ///
    /// \param spec Logging specification for this logger
    static void processSpecification(const LoggerSpecification& spec);

    /// \brief End Processing
    ///
    /// Terminates the processing of the logging specifications.
    static void processEnd();

    /// \brief Implementation-specific initialization
    ///
    /// Performs any implementation-specific initialization.  It is assumed
    /// that the name of the BIND 10 root logger can be obtained from the
    /// global function getRootLoggerName().
    ///
    /// \param severity Severity to be associated with this logger
    /// \param dbglevel Debug level associated with the root logger
    static void init(isc::log::Severity severity = isc::log::INFO,
                     int dbglevel = 0);

    /// \brief Reset logging
    ///
    /// Resets to default configuration (root logger logging to the console
    /// with INFO severity).
    static void reset();

private:
    /// \brief Create console appender
    ///
    /// Creates an object that, when attached to a logger, will log to one
    /// of the output streams (stdout or stderr).
    ///
    /// \param logger Log4cplus logger to which the appender must be attached.
    /// \param opt Output options for this appender.
    static void createConsoleAppender(log4cplus::Logger& logger,
                                      const OutputOption& opt);

    /// \brief Create file appender
    ///
    /// Creates an object that, when attached to a logger, will log to a
    /// specified file.  This also includes the ability to "roll" files when
    /// they reach a specified size.
    ///
    /// \param logger Log4cplus logger to which the appender must be attached.
    /// \param opt Output options for this appender.
    static void createFileAppender(log4cplus::Logger& logger,
                                   const OutputOption& opt);

    /// \brief Create syslog appender
    ///
    /// Creates an object that, when attached to a logger, will log to the
    /// syslog file.
    ///
    /// \param logger Log4cplus logger to which the appender must be attached.
    /// \param opt Output options for this appender.
    static void createSyslogAppender(log4cplus::Logger& logger,
                                     const OutputOption& opt) {}

    /// \brief Set default layout and severity for root logger
    ///
    /// Initializes the root logger to BIND 10 defaults - console output and
    /// the passed severity/debug level.
    ///
    /// \param severity Severity of messages that the logger should output.
    /// \param dbglevel Debug level if severity = DEBUG
    static void initRootLogger(isc::log::Severity severity = isc::log::INFO,
                               int dbglevel = 0);

    /// \brief Set layout for console appender
    ///
    /// Sets the layout of the specified appender to one suitable for file
    /// or console output:
    ///
    /// YYYY-MM-DD HH:MM:SS.ssss <severity> [root.logger] message
    ///
    /// \param appender Appender for which this pattern is to be set.
    /// \param root_name Name of the BIND 10 root logger.
    static void setConsoleAppenderLayout(log4cplus::SharedAppenderPtr& appender);
};

} // namespace log
} // namespace isc

#endif // __LOGGER_MANAGER_IMPL_H
