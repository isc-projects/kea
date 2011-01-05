// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __LOGGER_H
#define __LOGGER_H

#include <string>
#include <boost/lexical_cast.hpp>
#include <log4cxx/logger.h>

#include <log/dbglevels.h>

namespace isc {
namespace log {

class Logger {
public:

    typedef int MessageCode;    ///< Type of the message code

    /// \brief Severity Levels
    typedef enum {
        DEFAULT,    // Default to logging level of parent
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL,
        NONE,       // Disable logging
        INFORMATION = INFO,
        WARN = WARNING,
        FATAL = CRITICAL
    } Severity;

    /// \brief Return a logger of a given name
    ///
    /// Returns a logger with the specified name. 
    ///
    /// \param name Name of the logger.  Unless specified as a root logger
    /// (with a call to setRootLoggerName), the returned logger is a child
    /// of the root logger.
    ///
    /// \return Pointer to Logger object
    // static Logger* getLogger(const char* name) {}

    /// \brief Set Root Logger Name
    ///
    /// One of the first calls in the program, this sets the name of the
    /// root logger.  (The name appears in logging messages.)
    ///
    /// \param name Name of the root logger.
    // static void setRootLoggerName(const char* name);

    /// \brief Constructor
    ///
    /// Creates/attaches to a logger of a specific name.
    ///
    /// \param name Name of the logger.  If the name is that of the root name,
    /// this creates an instance of the root logger; otherwise it creates a
    /// chold of the root logger.
    Logger(const std::string& name);

    /// \brief Get Name of Logger
    ///
    /// \return The full name of the logger (including the root name)
    virtual std::string getName() const {
        return loggerptr_->getName();
    }

    /// \brief Set Severity Level for Logger
    ///
    /// Sets the level at which this logger will log messages.  If none is set,
    /// the level is inherited from the parent.
    ///
    /// \param severity Severity level to log
    /// \param dbglevel If the severity is DEBUG, this is the debug level.
    /// This can be in the range 1 to 100 and controls the verbosity.  A value
    /// outside these limits is silently coerced to the nearest boundary.
    virtual void setSeverity(Severity severity, int dbglevel = 1);

    /// \brief Get Severity Level for Logger
    ///
    /// \return The current logging level of this logger.  In most cases though,
    /// the effective logging level is what is required.
    virtual Severity getSeverity() const {
        return getSeverityCommon(loggerptr_, false);
    }

    /// \brief Get Effective Severity Level for Logger
    ///
    /// \return The effective severity level of the logger.  This is the same
    /// as getSeverity() if the logger has a severity level set, but otherwise
    /// is the severity of the parent.
    virtual Severity getEffectiveSeverity() const {
        return getSeverityCommon(loggerptr_, true);
    }

    /// \brief Return DEBUG Level
    ///
    /// \return Current setting of debug level.  This is returned regardless of
    /// whether the 
    virtual int getDebugLevel() const;

    /// \brief Returns if Debug Message Should Be Output
    ///
    /// \param dbglevel Level for which debugging is checked.  Debugging is
    /// enabled only if the logger has DEBUG enabled and if the dbglevel
    /// checked is less than or equal to the debug level set for the logger.
    virtual bool
    isDebugEnabled(int dbglevel = MIN_DEBUG_LEVEL) const {
        return (loggerptr_->getEffectiveLevel()->toInt() <=
            (log4cxx::Level::DEBUG_INT - dbglevel));
    }

    /// \brief Is INFO Enabled?
    virtual bool isInfoEnabled() const {
        return (loggerptr_->isInfoEnabled());
    }

    /// \brief Is WARNING Enabled?
    virtual bool isWarnEnabled() const {
        return (loggerptr_->isWarnEnabled());
    }

    /// \brief Is WARNING Enabled?
    virtual bool isWarningEnabled() const {
        return (loggerptr_->isWarnEnabled());
    }

    /// \brief Is ERROR Enabled?
    virtual bool isErrorEnabled() const {
        return (loggerptr_->isErrorEnabled());
    }

    /// \brief Is CRITICAL Enabled?
    virtual bool isCriticalEnabled() const {
        return (loggerptr_->isFatalEnabled());
    }

    /// \brief Is FATAL Enabled?
    ///
    /// FATAL is a synonym for CRITICAL.
    virtual bool isFatalEnabled() const {
        return (loggerptr_->isFatalEnabled());
    }
/*
    /// \brief Add Appender
    ///
    /// Adds an appender to the list of appenders for this logger.  The
    /// appender is assumed to have an independent existence so although
    /// a pointer to the appender is added here, the logger does not
    /// assume responsibility for its destruction.
    ///
    /// \param appender Pointer to the appender that should be added.
    /// If the appender is already added to this logger, a duplicate
    /// is not added.
    ///
    /// \return true if the logger was added, false if it was already in the
    /// list of appenders for this logger.
    virtual bool addAppender(AbstractAppender* appender);

    /// \brief Remove Appender
    ///
    /// Removes the appender from the list of appenders for this logger.
    /// 
    /// \param appender Pointer to the appender that should be removed.
    ///
    /// \return true if the appender was removed, false if it could not be
    /// found in the list.
    virtual bool removeAppender(AbstractAppender* appender);

    /// \brief Get Effective Level for Logger
    ///
    /// Gets the current effective logging level.  If the current logger does
    /// not have a level set, the inheritance tree is traversed until a level
    /// is found.
    virtual Level getEffectiveLevel() const;
    /// \brief Debug Messages
    ///
    /// A set of functions that control the output of the message and up to
    /// four parameters.
    void debugCommon(MessageCode code, std::string arg);

    template <typename T1>
    void debug(Level level, MessageCode code, T1 arg1) {
        if (shouldOutputDebug(level)) {
            debugCommon(code,
                boost::lexical_cast<std::string>(arg1)
            );
        }
    }

    template <typename T1, typename T2>
    void debug(MessageCode code, T1 arg1, T2 arg2) {
        if (shouldOutputDebug(level)) {
            debugCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2)
            );
        }
    }

    template <typename T1, typename T2, typename T3>
    void debug(MessageCode code, T1 arg1, T2 arg2, T3 arg3) {
        if (shouldOutputDebug(level)) {
            debugCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3)
            );
        }
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void debug(MessageCode code, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (shouldOutputDebug(level)) {
            debugCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3) + std::string('\0') +
                boost::lexical_cast<std::string>(arg4)
            );
        }
    }

    /// \brief Informational Messages
    ///
    /// A set of functions that control the output of the message and up to
    /// four parameters.
    void infoCommon(MessageCode code, std::string arg);

    template <typename T1>
    void info(MessageCode code, T1 arg1) {
        if (isInfoEnabled()) {
            infoCommon(code,
                boost::lexical_cast<std::string>(arg1)
            );
        }
    }

    template <typename T1, typename T2>
    void info(MessageCode code, T1 arg1, T2 arg2) {
        if (isInfoEnabled()) {
            infoCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2)
            );
        }
    }

    template <typename T1, typename T2, typename T3>
    void info(MessageCode code, T1 arg1, T2 arg2, T3 arg3) {
        if (isInfoEnabled()) {
            infoCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3)
            );
        }
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void info(MessageCode code, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (isInfoEnabled()) {
            infoCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3) + std::string('\0') +
                boost::lexical_cast<std::string>(arg4)
            );
        }
    }

    /// \brief Warning Messages
    ///
    /// A set of functions that control the output of the message and up to
    /// four parameters.
    void warnCommon(MessageCode code, std::string arg);

    template <typename T1>
    void warn(MessageCode code, T1 arg1) {
        if (isWarnEnabled()) {
            warnCommon(code,
                boost::lexical_cast<std::string>(arg1)
            );
        }
    }

    template <typename T1, typename T2>
    void warn(MessageCode code, T1 arg1, T2 arg2) {
        if (isWarnEnabled()) {
            warnCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2)
            );
        }
    }

    template <typename T1, typename T2, typename T3>
    void warn(MessageCode code, T1 arg1, T2 arg2, T3 arg3) {
        if (isWarnEnabled()) {
            warnCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3)
            );
        }
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void warn(MessageCode code, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (isWarnEnabled()) {
            warnCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3) + std::string('\0') +
                boost::lexical_cast<std::string>(arg4)
            );
        }
    }

    /// \brief Error Messages
    ///
    /// A set of functions that control the output of the message and up to
    /// four parameters.
    void errorCommon(MessageCode code, std::string arg);

    template <typename T1>
    void error(MessageCode code, T1 arg1) {
        if (isErrorEnabled()) {
            errorCommon(code,
                boost::lexical_cast<std::string>(arg1)
            );
        }
    }

    template <typename T1, typename T2>
    void error(MessageCode code, T1 arg1, T2 arg2) {
        if (isErrorEnabled()) {
            errorCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2)
            );
        }
    }

    template <typename T1, typename T2, typename T3>
    void error(MessageCode code, T1 arg1, T2 arg2, T3 arg3) {
        if (isErrorEnabled()) {
            errorCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3)
            );
        }
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void error(MessageCode code, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (isErrorEnabled()) {
            errorCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3) + std::string('\0') +
                boost::lexical_cast<std::string>(arg4)
            );
        }
    }

    /// \brief Critical Messages
    ///
    /// A set of functions that control the output of the message and up to
    /// four parameters.
    void criticalCommon(MessageCode code, std::string arg);

    template <typename T1>
    void critical(MessageCode code, T1 arg1) {
        if (isCriticalEnabled()) {
            criticalCommon(code,
                boost::lexical_cast<std::string>(arg1)
            );
        }
    }

    template <typename T1, typename T2>
    void critical(MessageCode code, T1 arg1, T2 arg2) {
        if (isCriticalEnabled()) {
            criticalCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2)
            );
        }
    }

    template <typename T1, typename T2, typename T3>
    void critical(MessageCode code, T1 arg1, T2 arg2, T3 arg3) {
        if (isCriticalEnabled()) {
            criticalCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3)
            );
        }
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void critical(MessageCode code, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (isCriticalEnabled()) {
            errorCommon(code,
                boost::lexical_cast<std::string>(arg1) + std::string('\0') +
                boost::lexical_cast<std::string>(arg2) + std::string('\0') +
                boost::lexical_cast<std::string>(arg3) + std::string('\0') +
                boost::lexical_cast<std::string>(arg4)
            );
        }
    }
*/

protected:

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    /// (This method is principally for testing.)
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(const Logger& other) const {
        return (loggerptr_ == other.loggerptr_);
    }

    /// \brief Logger Initialized
    ///
    /// Check that the logger has been properly initialized.  (This method
    /// is principally for testing.)
    ///
    /// \return true if this logger object has been initialized.
    bool isInitialized() const {
        return (loggerptr_ != log4cxx::LoggerPtr());
    }

    /// \brief Get Severity Level for Logger
    ///
    /// This is common code for getSeverity() and getEffectiveSeverity() -
    /// it returns the severity of the logger; if not set (and the check_parent)
    /// flag is set, it searches up the parent-child tree until a severity
    /// level is found and uses that.
    ///
    /// \param ptrlogger Pointer to the log4cxx logger to check.
    /// \param check_parent true to search up the tree, false to return the
    /// current level.
    ///
    /// \return The effective severity level of the logger.  This is the same
    /// as getSeverity() if the logger has a severity level set, but otherwise
    /// is the severity of the parent.
    Logger::Severity getSeverityCommon(const log4cxx::LoggerPtr& ptrlogger,
        bool check_parent) const;

    /// \brief Convert Between BIND-10 and log4cxx Logging Levels
    ///
    /// Converts between the numeric value of the log4cxx logging level
    /// and the BIND-10 severity level.
    ///
    /// \param value log4cxx numeric logging level
    ///
    /// \return BIND-10 logging severity
    Severity convertLevel(int value) const;

private:
    log4cxx::LoggerPtr  loggerptr_; ///< Pointer to the underlying logger
    std::string         fullname_;  ///< Full name of this logger
};

} // namespace log
} // namespace isc


#endif // __LOGGER_H
