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

#ifndef __LOGGER_IMPL_H
#define __LOGGER_IMPL_H

#include <stdarg.h>
#include <time.h>

#include <cstdlib>
#include <string>
#include <map>
#include <utility>


// log4cplus logger header file
#include <log4cplus/logger.h>

// BIND-10 logger files
#include <log/debug_levels.h>
#include <log/logger.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>

namespace isc {
namespace log {

/// \brief Console Logger Implementation
///
/// The logger uses a "pimpl" idiom for implementation, where the base logger
/// class contains little more than a pointer to the implementation class, and
/// all actions are carried out by the latter.  This class is an implementation
/// class that just outputs to stdout.

class LoggerImpl {
public:

    /// \brief Information About Logger
    ///
    /// Holds a information about a logger, namely its severity and its debug
    /// level.  This could be a std::pair, except that it gets confusing when
    /// accessing the LoggerInfoMap: that returns a pair, so we to reference
    /// elements we would use constructs like ((i->first).second);
    struct LoggerInfo {
        isc::log::Severity  severity;
        int                 dbglevel;

        LoggerInfo(isc::log::Severity sev = isc::log::INFO,
            int dbg = MIN_DEBUG_LEVEL) : severity(sev), dbglevel(dbg)
        {}
    };


    /// \brief Information About All Loggers
    ///
    /// Information about all loggers in the system - except the root logger -
    /// is held in a map, linking name of the logger (excluding the root
    /// name component) and its set severity and debug levels.  The root
    /// logger information is held separately.
    typedef std::map<std::string, LoggerInfo>   LoggerInfoMap;


    /// \brief Constructor
    ///
    /// Creates a logger of the specific name.
    ///
    /// \param name Name of the logger.
    ///
    /// \param exit_delete This argument is present to get round a bug in
    /// the log4cxx implementation.  It is unused here.
    LoggerImpl(const std::string& name, bool);


    /// \brief Destructor
    virtual ~LoggerImpl();


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
    /// This can be in the range 1 to 100 and controls the verbosity.  A value
    /// outside these limits is silently coerced to the nearest boundary.
    virtual void setSeverity(isc::log::Severity severity, int dbglevel = 1);


    /// \brief Get Severity Level for Logger
    ///
    /// \return The current logging level of this logger.  In most cases though,
    /// the effective logging level is what is required.
    virtual isc::log::Severity getSeverity();


    /// \brief Get Effective Severity Level for Logger
    ///
    /// \return The effective severity level of the logger.  This is the same
    /// as getSeverity() if the logger has a severity level set, but otherwise
    /// is the severity of the parent.
    virtual isc::log::Severity getEffectiveSeverity();


    /// \brief Return DEBUG Level
    ///
    /// \return Current setting of debug level.  This is returned regardless of
    /// whether the
    virtual int getDebugLevel();


    /// \brief Returns if Debug Message Should Be Output
    ///
    /// \param dbglevel Level for which debugging is checked.  Debugging is
    /// enabled only if the logger has DEBUG enabled and if the dbglevel
    /// checked is less than or equal to the debug level set for the logger.
    virtual bool
    isDebugEnabled(int dbglevel = MIN_DEBUG_LEVEL);

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
    std::string* lookupMessage(const MessageID& id);

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    /// (This method is principally for testing.)
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(const LoggerImpl& other) {
        return (name_ == other.name_);
    }


    /// \brief Reset Global Data
    ///
    /// Only used for testing, this clears all the logger information and
    /// resets it back to default values.
    static void reset() {
        //root_logger_info_ = LoggerInfo(isc::log::INFO, MIN_DEBUG_LEVEL);
        //logger_info_.clear();
    }


private:
    /// \brief Convert Log Levels
    ///
    /// Converts a BIND 10 log level to a log4cplus log level.
    ///
    /// \param inlevel BIND 10 log level.
    ///
    /// \return Log4cplus log level.
    log4cplus::LogLevel convertFromBindSeverity(
        const isc::log::Severity& inlevel);

    /// \brief Convert Log Levels
    ///
    /// Converts a log4cplus log level to a BIND 10 log level.
    ///
    /// \param inlevel log4cplus log level.
    ///
    /// \return BIND 10 log level.
    isc::log::Severity convertToBindSeverity(
        const log4cplus::LogLevel& inlevel);

    /// \brief Initialize log4cplus
    ///
    /// Static method to perform one-time initialization of the log4cplus
    /// system.
    static void initLog4cplus();

    bool                is_root_;           ///< Is this BIND 10 root logger?
    std::string         name_;              ///< Full name of this logger
    std::string         fmt_name_;          ///< Formatted name
    log4cplus::Logger   logger_;            ///< Underlying log4cplus logger

};

} // namespace log
} // namespace isc


#endif // __LOGGER_IMPL_H
