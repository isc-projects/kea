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

#ifndef LOGGER_MANAGER_IMPL_H
#define LOGGER_MANAGER_IMPL_H

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
struct OutputOption;

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
    LoggerManagerImpl() {}

    /// \brief Initialize Processing
    ///
    /// This resets the hierachy of loggers back to their defaults.  This means
    /// that all non-root loggers (if they exist) are set to NOT_SET, and the
    /// root logger reset to logging informational messages.
    void processInit();

    /// \brief Process Specification
    ///
    /// Processes the specification for a single logger.
    ///
    /// \param spec Logging specification for this logger
    static void processSpecification(const LoggerSpecification& spec);

    /// \brief End Processing
    ///
    /// Terminates the processing of the logging specifications.
    void processEnd();

    /// \brief Implementation-specific initialization
    ///
    /// Sets the basic configuration for logging (the root logger has INFO and
    /// more severe messages routed to stdout).  Unless this function (or
    /// process() with a valid specification for all loggers that will log
    /// messages) is called before a message is logged, log4cplus will output
    /// a message to stderr noting that logging has not been initialized.
    ///
    /// It is assumed here that the name of the BIND 10 root logger can be
    /// obtained from the global function getRootLoggerName().
    ///
    /// \param severity Severity to be associated with this logger
    /// \param dbglevel Debug level associated with the root logger
    /// \param buffer If true, all log messages will be buffered until one of
    ///        the \c process() methods is called. If false, initial logging
    ///        shall go to the default output (i.e. stdout)
    static void init(isc::log::Severity severity = isc::log::INFO,
                     int dbglevel = 0, bool buffer = false);

    /// \brief Reset logging
    ///
    /// Resets to default configuration (root logger logging to the console
    /// with INFO severity).
    ///
    /// \param severity Severity to be associated with this logger
    /// \param dbglevel Debug level associated with the root logger
    static void reset(isc::log::Severity severity = isc::log::INFO,
                      int dbglevel = 0);

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
                                     const OutputOption& opt);

    /// \brief Create buffered appender
    ///
    /// Appends an object to the logger that will store the log events sent
    /// to the logger. These log messages are replayed to the logger in
    /// processEnd().
    ///
    /// \param logger Log4cplus logger to which the appender must be attached.
    static void createBufferAppender(log4cplus::Logger& logger);

    /// \brief Set default layout and severity for root logger
    ///
    /// Initializes the root logger to BIND 10 defaults - console or buffered
    /// output and the passed severity/debug level.
    ///
    /// \param severity Severity of messages that the logger should output.
    /// \param dbglevel Debug level if severity = DEBUG
    /// \param buffer If true, all log messages will be buffered until one of
    ///        the \c process() methods is called. If false, initial logging
    ///        shall go to the default output (i.e. stdout)
    static void initRootLogger(isc::log::Severity severity = isc::log::INFO,
                               int dbglevel = 0, bool buffer = false);

    /// \brief Set layout for console appender
    ///
    /// Sets the layout of the specified appender to one suitable for file
    /// or console output:
    ///
    /// YYYY-MM-DD HH:MM:SS.ssss SEVERITY [root.logger] message
    ///
    /// \param appender Appender for which this pattern is to be set.
    static void setConsoleAppenderLayout(log4cplus::SharedAppenderPtr& appender);

    /// \brief Set layout for syslog appender
    ///
    /// Sets the layout of the specified appender to one suitable for the
    /// syslog file:
    ///
    /// SEVERITY [root.logger] message
    ///
    /// \param appender Appender for which this pattern is to be set.
    static void setSyslogAppenderLayout(log4cplus::SharedAppenderPtr& appender);

    /// \brief Store all buffer appenders
    ///
    /// When processing a new specification, this method can be used
    /// to keep a list of the buffer appenders; the caller can then
    /// process the specification, and call \c flushBufferAppenders()
    /// to flush and clear the list
    void storeBufferAppenders();

    /// \brief Flush the stored buffer appenders
    ///
    /// This flushes the list of buffer appenders stored in
    /// \c storeBufferAppenders(), and clears it
    void flushBufferAppenders();

    /// Only used between processInit() and processEnd(), to temporarily
    /// store the buffer appenders in order to flush them after
    /// processSpecification() calls have been completed
    std::vector<log4cplus::SharedAppenderPtr> buffer_appender_store_;
};

} // namespace log
} // namespace isc

#endif // LOGGER_MANAGER_IMPL_H
