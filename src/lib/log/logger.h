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

#include <cstdlib>
#include <string>

#include <log/debug_levels.h>
#include <log/logger_levels.h>
#include <log/message_types.h>

namespace isc {
namespace log {

/// \brief Logging API
///
/// This module forms the interface into the logging subsystem. Features of the
/// system and its implementation are:
///
/// # Multiple logging objects can be created, each given a name; those with the
///   same name share characteristics (like destination, level being logged
///   etc.)
/// # Messages can be logged at severity levels of FATAL, ERROR, WARN, INFO or
///   DEBUG.  The DEBUG level has further sub-levels numbered 0 (least
///   informative) to 99 (most informative).
/// # Each logger has a severity level set associated with it.  When a message
///   is logged, it is output only if it is logged at a level equal to the
///   logger severity level or greater, e.g. if the logger's severity is WARN,
///   only messages logged at WARN, ERROR or FATAL will be output.
/// # Messages are identified by message identifiers, which are keys into a
///   message dictionary.

class LoggerImpl;   // Forward declaration of the implementation class

class Logger {
public:

    /// \brief Constructor
    ///
    /// Creates/attaches to a logger of a specific name.
    ///
    /// \param name Name of the logger.  If the name is that of the root name,
    /// this creates an instance of the root logger; otherwise it creates a
    /// child of the root logger.
    ///
    /// \param infunc This argument is present to get round a bug in some
    /// implementations of the logging system.  If the logger is declared in
    /// a function (such that it will be deleted when the function exits,
    /// before the program ends), set this true.  If declared outside a
    /// function (such that it gets deleted during program rundown), set false
    /// (the default).\n
    /// \n
    /// The problems encountered was that during program rundown, one logging
    /// implementation (log4cxx) threw a MutexException (this is described in
    /// https://issues.apache.org/jira/browse/LOGCXX-322).  As this only occurs
    /// during program rundown, the issue is not serious - it just looks bad to
    /// have the program crash instead of shut down cleanly.\n
    /// \n
    /// If log4cxx is chosen as the implementation, this flag controls the
    /// deletion of the underlying log4cxx data structures when the logger is
    /// deleted.  Setting it false for externally-declared loggers inhibits
    /// their deletion; so at program exit the memory is not reclaimed during
    /// program rundown, only when the process is delected.  Setting it true
    /// for loggers that will be deleted in the normal running of the program
    /// enables their deletion - which causes no issues as the problem only
    /// manifests itself during program rundown.
    /// \n
    /// The flag has no effect on non-log4cxx implementations.
    Logger(const std::string& name, bool infunc = false) :
        loggerptr_(NULL), name_(name), infunc_(infunc)
    {}


    /// \brief Destructor
    virtual ~Logger();


    /// \brief Get Name of Logger
    ///
    /// \return The full name of the logger (including the root name)
    virtual std::string getName();


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
    virtual bool isDebugEnabled(int dbglevel = MIN_DEBUG_LEVEL);


    /// \brief Is INFO Enabled?
    virtual bool isInfoEnabled();


    /// \brief Is WARNING Enabled?
    virtual bool isWarnEnabled();


    /// \brief Is ERROR Enabled?
    virtual bool isErrorEnabled();


    /// \brief Is FATAL Enabled?
    virtual bool isFatalEnabled();


    /// \brief Output Debug Message
    ///
    /// \param dbglevel Debug level, ranging between 0 and 99.  Higher numbers
    /// are used for more verbose output.
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void debug(int dbglevel, const MessageID& ident, ...);


    /// \brief Output Informational Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void info(const MessageID& ident, ...);


    /// \brief Output Warning Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void warn(const MessageID& ident, ...);


    /// \brief Output Error Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void error(const MessageID& ident, ...);


    /// \brief Output Fatal Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void fatal(const MessageID& ident, ...);

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    /// (This method is principally for testing.)
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(Logger& other);

protected:

    /// \brief Reset Global Data
    ///
    /// Used for testing, this calls upon the underlying logger implementation
    /// to clear any global data.
    static void reset();

private:
    /// \brief Copy Constructor
    ///
    /// Disabled (marked private) as it makes no sense to copy the logger -
    /// just create another one of the same name.
    Logger(const Logger&);

    /// \brief Assignment Operator
    ///
    /// Disabled (marked private) as it makes no sense to copy the logger -
    /// just create another one of the same name.
    Logger& operator=(const Logger&);

    /// \brief Initialize Implementation
    ///
    /// Returns the logger pointer.  If not yet set, the underlying
    /// implementation class is initialized.\n
    /// \n
    /// The reason for this indirection is to avoid the "static initialization
    /// fiacso", whereby we cannot rely on the order of static initializations.
    /// The main problem is the root logger name - declared statically - which
    /// is referenced by various loggers.  By deferring a reference to it until
    /// after the program starts executing - by which time the root name object
    /// will be initialized - we avoid this problem.
    ///
    /// \return Returns pointer to implementation
    LoggerImpl* getLoggerPtr() {
        if (!loggerptr_) {
            initLoggerImpl();
        }
        return (loggerptr_);
    }

    /// \brief Initialize Underlying Implementation and Set loggerptr_
    void initLoggerImpl();

    LoggerImpl*     loggerptr_;     ///< Pointer to the underlying logger
    std::string     name_;          ///< Copy of the logger name
    bool            infunc_;        ///< Copy of the infunc argument
};

} // namespace log
} // namespace isc


#endif // __LOGGER_H
