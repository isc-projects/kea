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

#ifndef __LOGGER_IMPL_H
#define __LOGGER_IMPL_H

#include <time.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <utility>

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
    LoggerImpl(const std::string& name, bool) : name_(name)
    {}


    /// \brief Destructor
    virtual ~LoggerImpl();


    /// \brief Get the full name of the logger (including the root name)
    virtual std::string getName();


    /// \brief Check if this is the root logger
    ///
    /// \return true if the name of this logger is the same as that of the
    /// root logger.
    virtual bool isRootLogger() const {
        return (name_ == RootLoggerName::getName());
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
        return (isEnabled(isc::log::INFO));
    }

    /// \brief Is WARNING Enabled?
    virtual bool isWarnEnabled() {
        return (isEnabled(isc::log::WARN));
    }

    /// \brief Is ERROR Enabled?
    virtual bool isErrorEnabled() {
        return (isEnabled(isc::log::ERROR));
    }

    /// \brief Is FATAL Enabled?
    virtual bool isFatalEnabled() {
        return (isEnabled(isc::log::FATAL));
    }


    /// \brief Common Severity check
    ///
    /// Implements the common severity check.  As an optimisation, this checks
    /// to see if any logger-specific levels have been set (a quick check as it
    /// just involves seeing if the collection of logger information is empty).
    /// if not, it returns the information for the root level; if so, it has
    /// to take longer and look up the information in the map holding the
    /// logging details.
    virtual bool isEnabled(isc::log::Severity severity) {
        if (logger_info_.empty()) {
            return (root_logger_info_.severity <= severity);
        }
        else {
            return (getSeverity() <= severity);
        }
    }


    /// \brief Output General Message
    ///
    /// The message is formatted to include the date and time, the severity
    /// and the logger generating the message.
    ///
    /// \param sev_text Severity lovel as a text string
    /// \param text Text to log
    void output(const char* sev_text, const std::string& message);


    /// \brief Output Debug Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void debug(MessageID ident, const char* text);


    /// \brief Output Informational Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void info(MessageID ident, const char* text);


    /// \brief Output Warning Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void warn(MessageID ident, const char* text);


    /// \brief Output Error Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void error(MessageID ident, const char* text);


    /// \brief Output Fatal Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void fatal(MessageID ident, const char* text);


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
        root_logger_info_ = LoggerInfo(isc::log::INFO, MIN_DEBUG_LEVEL);
        logger_info_.clear();
    }


private:
    std::string          name_;                 ///< Name of this logger
    
    // Split the status of the root logger from this logger.  If - is will
    // probably be the usual case - no per-logger setting is enabled, a
    // quick check of logger_info_.empty() will return true and we can quickly
    // return the root logger status without a length lookup in the map.

    static LoggerInfo       root_logger_info_;  ///< Status of root logger
    static LoggerInfoMap    logger_info_;       ///< Store of debug levels etc.
};

} // namespace log
} // namespace isc


#endif // __LOGGER_IMPL_H
