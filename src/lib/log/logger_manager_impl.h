// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_MANAGER_IMPL_H
#define LOGGER_MANAGER_IMPL_H

#include <string>

#include <log4cplus/appender.h>
#include <log/logger_level.h>
#include <log/logger_specification.h>

// Forward declaration to avoid need to include log4cplus header file here.
namespace log4cplus {
class Logger;
class Appender;
}

namespace isc {
namespace log {

// Forward declarations
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
/// the underlying implementation (log4cplus) from the Kea interface.
/// This requires that there be an implementation class, even though in this
/// case, all the implementation class methods can be declared static.

class LoggerManagerImpl {
public:

    /// \brief Constructor
    LoggerManagerImpl() {}

    /// \brief Initialize Processing
    ///
    /// This resets the hierarchy of loggers back to their defaults.  This means
    /// that all non-root loggers (if they exist) are set to NOT_SET, and the
    /// root logger reset to logging informational messages.
    void processInit();

    /// \brief Process Specification
    ///
    /// Processes the specification for a single logger.
    ///
    /// \param spec Logging specification for this logger
    void processSpecification(const LoggerSpecification& spec);

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
    /// It is assumed here that the name of the Kea root logger can be
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
    /// @brief Decides what appender to create.
    ///
    /// Delegates to the other functions that create appenders based on what's
    /// in spec.
    ///
    /// @param logger log4cplus logger to which the appender must be attached
    /// @param spec the configured specification consisting of output options
    static void appenderFactory(log4cplus::Logger& logger,
                                LoggerSpecification const& spec);

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
    /// Initializes the root logger to Kea defaults - console or buffered
    /// output and the passed severity/debug level.
    ///
    /// \param severity Severity of messages that the logger should output.
    /// \param dbglevel Debug level if severity = DEBUG
    /// \param buffer If true, all log messages will be buffered until one of
    ///        the \c process() methods is called. If false, initial logging
    ///        shall go to the default output (i.e. stdout)
    static void initRootLogger(isc::log::Severity severity = isc::log::INFO,
                               int dbglevel = 0, bool buffer = false);

    /// \brief Set layout for an appender
    ///
    /// Sets the layout of the specified appender to one suitable for file
    /// or console output:
    ///
    /// \param appender Appender for which this pattern is to be set.
    /// \param pattern  Log message format pattern
    static void setAppenderLayout(log4cplus::SharedAppenderPtr& appender,
                                  std::string pattern);

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

    /// @brief Only used between processInit() and processEnd(), to temporarily
    /// store the buffer appenders in order to flush them after
    /// processSpecification() calls have been completed
    std::vector<log4cplus::SharedAppenderPtr> buffer_appender_store_;

    /// @brief A hard copy of the specification for the root logger used for
    /// inheritance by child loggers.
    LoggerSpecification root_spec_;
};

} // namespace log
} // namespace isc

#endif // LOGGER_MANAGER_IMPL_H
