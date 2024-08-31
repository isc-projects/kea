// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_IMPL_H
#define LOGGER_IMPL_H

#include <stdarg.h>
#include <time.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <utility>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

// log4cplus logger header file
#include <log4cplus/logger.h>

// Kea logger files
#include <log/logger_level_impl.h>
#include <log/message_types.h>
#include <log/interprocess/interprocess_sync.h>
#include <log/output_option.h>

namespace isc {
namespace log {

/// \brief Console Logger Implementation
///
/// The logger uses a "pimpl" idiom for implementation, where the base logger
/// class contains little more than a pointer to the implementation class, and
/// all actions are carried out by the latter.
///
/// This particular implementation is based on log4cplus (from sourceforge:
/// http://log4cplus.sourceforge.net).  Particular items of note:
///
/// a) Kea loggers have names of the form "program.sublogger".  In other
/// words, each of the loggers is a sub-logger of the main program logger.
/// In log4cplus, there is a root logger (called "root" according to the
/// documentation, but actually unnamed) and all loggers created are subloggers
/// if it.
///
/// In this implementation, the log4cplus root logger is unused.  Instead, the
/// Kea root logger is created as a child of the log4cplus root logger,
/// and all other loggers used in the program are created as sub-loggers of
/// that.  In this way, the logging system can just include the name of the
/// logger in each message without the need to specially consider if the
/// message is the root logger or not.
///
/// b) The idea of debug levels is implemented.  See logger_level.h and
/// logger_level_impl.h for more details on this.

class LoggerImpl : public boost::noncopyable {
public:

    /// \brief Constructor
    ///
    /// Creates a logger of the specific name.
    ///
    /// \param name Name of the logger.
    LoggerImpl(const std::string& name);


    /// \brief Destructor
    virtual ~LoggerImpl();


    /// \brief Version
    static std::string getVersion();


    /// \brief Get the full name of the logger (including the root name)
    virtual std::string getName() {
        return (name_);
    }


    /// \brief Set Severity Level for Logger
    ///
    /// Sets the level at which this logger will log messages.  If none is set,
    /// the level is inherited from the parent.
    ///
    /// \param severity Severity level to log
    /// \param dbglevel If the severity is DEBUG, this is the debug level.
    /// This can be in the range 0 to 99 and controls the verbosity.  A value
    /// outside these limits is silently coerced to the nearest boundary.
    virtual void setSeverity(Severity severity, int dbglevel = 1);


    /// \brief Get Severity Level for Logger
    ///
    /// \return The current logging level of this logger.  In most cases though,
    /// the effective logging level is what is required.
    virtual Severity getSeverity();


    /// \brief Get Effective Severity Level for Logger
    ///
    /// \return The effective severity level of the logger.  This is the same
    /// as getSeverity() if the logger has a severity level set, but otherwise
    /// is the severity of the parent.
    virtual Severity getEffectiveSeverity();


    /// \brief Return debug level
    ///
    /// \return Current setting of debug level.  This will be zero if the
    ///         the current severity level is not DEBUG.
    virtual int getDebugLevel();


    /// \brief Return effective debug level
    ///
    /// \return Current setting of effective debug level.  This will be zero if
    ///         the current effective severity level is not DEBUG.
    virtual int getEffectiveDebugLevel();


    /// \brief Returns if Debug Message Should Be Output
    ///
    /// \param dbglevel Level for which debugging is checked.  Debugging is
    /// enabled only if the logger has DEBUG enabled and if the dbglevel
    /// checked is less than or equal to the debug level set for the logger.
    virtual bool isDebugEnabled(int dbglevel = MIN_DEBUG_LEVEL) {
        Level level(DEBUG, dbglevel);
        return logger_.isEnabledFor(LoggerLevelImpl::convertFromBindLevel(level));
    }

    /// \brief Is INFO Enabled?
    virtual bool isInfoEnabled() {
        return (logger_.isEnabledFor(log4cplus::INFO_LOG_LEVEL));
    }

    /// \brief Is WARNING Enabled?
    virtual bool isWarnEnabled() {
        return (logger_.isEnabledFor(log4cplus::WARN_LOG_LEVEL));
    }

    /// \brief Is ERROR Enabled?
    virtual bool isErrorEnabled() {
        return (logger_.isEnabledFor(log4cplus::ERROR_LOG_LEVEL));
    }

    /// \brief Is FATAL Enabled?
    virtual bool isFatalEnabled() {
        return (logger_.isEnabledFor(log4cplus::FATAL_LOG_LEVEL));
    }

    /// \brief Raw output
    ///
    /// Writes the message with time into the log. Used by the Formatter
    /// to produce output.
    ///
    /// \param severity Severity of the message. (This controls the prefix
    ///        label output with the message text.)
    /// \param message Text of the message.
    void outputRaw(const Severity& severity, const std::string& message);

    /// \brief Look up message text in dictionary
    ///
    /// This gets you the unformatted text of message for given ID.
    boost::shared_ptr<std::string> lookupMessage(const MessageID& id);

    /// \brief Replace the interprocess synchronization object
    ///
    /// If this method is called with NULL as the argument, it throws a
    /// BadInterprocessSync exception.
    ///
    /// \param sync The logger uses this synchronization object for
    /// synchronizing output of log messages. It should be deletable and
    /// the ownership is transferred to the logger implementation.
    /// If NULL is passed, a BadInterprocessSync exception is thrown.
    void setInterprocessSync(isc::log::interprocess::InterprocessSync* sync);

    /// @brief Check if this logger has an appender of the given type.
    ///
    /// @param destination the appender type to be checked: console, file or syslog
    ///
    /// @return true if an appender of the given type is found, false otherwise
    bool hasAppender(OutputOption::Destination const destination);

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    /// (This method is principally for testing.)
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(const LoggerImpl& other) const {
        return (name_ == other.name_);
    }

private:
    std::string                  name_;   ///< Full name of this logger
    log4cplus::Logger            logger_; ///< Underlying log4cplus logger
    isc::log::interprocess::InterprocessSync* sync_;
};

} // namespace log
} // namespace isc


#endif // LOGGER_IMPL_H
