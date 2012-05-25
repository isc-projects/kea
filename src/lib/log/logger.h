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

#ifndef __LOGGER_H
#define __LOGGER_H

#include <cassert>
#include <cstdlib>
#include <string>
#include <cstring>

#include <exceptions/exceptions.h>
#include <log/logger_level.h>
#include <log/message_types.h>
#include <log/log_formatter.h>

#include <util/interprocess_sync.h>

namespace isc {
namespace log {

/// \page LoggingApi Logging API
/// \section LoggingApiOverview Overview
/// BIND 10 logging uses the concepts of the widely-used Java logging
/// package log4j (http://logging.apache.log/log4j), albeit implemented 
/// in C++ using an open-source port.  Features of the system are:
/// 
/// - Within the code objects - known as loggers - can be created and
/// used to log messages.  These loggers have names; those with the
/// same name share characteristics (such as output destination).
/// - Loggers have a hierarchical relationship, with each logger being
/// the child of another logger, except for the top of the hierarchy, the
/// root logger.  If a logger does not log a message, it is passed to the
/// parent logger.
/// - Messages can be logged at severity levels of FATAL, ERROR, WARN, INFO
/// or DEBUG.  The DEBUG level has further sub-levels numbered 0 (least
/// informative) to 99 (most informative).
/// - Each logger has a severity level set associated with it.  When a
/// message is logged, it is output only if it is logged at a level equal
/// to the logger severity level or greater, e.g. if the logger's severity
/// is WARN, only messages logged at WARN, ERROR or FATAL will be output.
/// 
/// \section LoggingApiLoggerNames BIND 10 Logger Names
/// Within BIND 10, the root logger root logger is given the name of the
/// program (via the stand-alone function setRootLoggerName()). Other loggers
/// are children of the root logger and are named "<program>.<sublogger>".
/// This name appears in logging output, allowing users to identify both
/// the BIND 10 program and the component within the program that generated
/// the message.
/// 
/// When creating a logger, the abbreviated name "<sublogger>" can be used;
/// the program name will be prepended to it when the logger is created.
/// In this way, individual libraries can have their own loggers without
/// worrying about the program in which they are used, but:
/// - The origin of the message will be clearly identified.
/// - The same component can have different options (e.g. logging severity)
/// in different programs at the same time.
/// 
/// \section LoggingApiLoggingMessages Logging Messages
/// Instead of embedding the text of messages within the code, each message
/// is referred to using a symbolic name.  The logging code uses this name as
/// a key in a dictionary from which the message text is obtained.  Such a
/// system allows for the optional replacement of message text at run time.
/// More details about the message dictionary (and the compiler used to create
/// the symbol definitions) can be found in other modules in the src/lib/log
/// directory.
///
/// \section LoggingApiImplementationIssues Implementation Issues
/// Owing to the way that the logging is implemented, notably that loggers can
/// be declared as static external objects, there is a restriction on the
/// length of the name of a logger component (i.e. the length of
/// the string passed to the Logger constructor) to a maximum of 31 characters.
/// There is no reason for this particular value other than limiting the amount
/// of memory used.  It is defined by the constant Logger::MAX_LOGGER_NAME_SIZE,
/// and can be made larger (or smaller) if so desired.  Note however, using a
/// logger name larger than this limit will cause an assertion failure.

class LoggerImpl;   // Forward declaration of the implementation class

/// \brief Logging Not Initialized
///
/// Exception thrown if an attempt is made to access a logging function
/// if the logging system has not been initialized.
class LoggingNotInitialized : public isc::Exception {
public:
    LoggingNotInitialized(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// \brief Logger Class
///
/// This class is the main class used for logging.  Use comprises:
///
/// 1. Constructing a logger by instantiating it with a specific name. (If the
/// same logger is in multiple functions within a file, overhead can be
/// minimised by declaring it as a file-wide static variable.)
/// 2. Using the error(), info() etc. methods to log an error.  (However, it is
/// recommended to use the LOG_ERROR, LOG_INFO etc. macros defined in macros.h.
/// These will avoid the potentially-expensive evaluation of arguments if the
/// severity is such that the message will be suppressed.)

class Logger {
public:
    /// Maximum size of a logger name
    static const size_t MAX_LOGGER_NAME_SIZE = 31;

    /// \brief Constructor
    ///
    /// Creates/attaches to a logger of a specific name.
    ///
    /// \param name Name of the logger.  If the name is that of the root name,
    /// this creates an instance of the root logger; otherwise it creates a
    /// child of the root logger.
    ///
    /// \note The name of the logger may be no longer than MAX_LOGGER_NAME_SIZE
    /// else the program will halt with an assertion failure.  This restriction
    /// allows loggers to be declared statically: the name is stored in a
    /// fixed-size array to avoid the need to allocate heap storage during
    /// program initialization (which causes problems on some operating
    /// systems).
    ///
    /// \note Note also that there is no constructor taking a std::string. This
    /// minimises the possibility of initializing a static logger with a
    /// string, so leading to problems mentioned above.
    Logger(const char* name) : loggerptr_(NULL) {
        assert(std::strlen(name) < sizeof(name_));
        // Do the copy.  Note that the assertion above has checked that the
        // contents of "name" and a trailing null will fit within the space
        // allocated for name_, so we could use strcpy here and be safe.
        // However, a bit of extra paranoia doesn't hurt.
        std::strncpy(name_, name, sizeof(name_));
        assert(name_[sizeof(name_) - 1] == '\0');
    }

    /// \brief Destructor
    virtual ~Logger();

    /// \brief The formatter used to replace placeholders
    typedef isc::log::Formatter<Logger> Formatter;

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
    /// whether the severity is set to debug.
    virtual int getDebugLevel();

    /// \brief Get Effective Debug Level for Logger
    ///
    /// \return The effective debug level of the logger.  This is the same
    /// as getDebugLevel() if the logger has a debug level set, but otherwise
    /// is the debug level of the parent.
    virtual int getEffectiveDebugLevel();

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
    Formatter debug(int dbglevel, const MessageID& ident);

    /// \brief Output Informational Message
    ///
    /// \param ident Message identification.
    Formatter info(const MessageID& ident);

    /// \brief Output Warning Message
    ///
    /// \param ident Message identification.
    Formatter warn(const MessageID& ident);

    /// \brief Output Error Message
    ///
    /// \param ident Message identification.
    Formatter error(const MessageID& ident);

    /// \brief Output Fatal Message
    ///
    /// \param ident Message identification.
    Formatter fatal(const MessageID& ident);

    /// \brief Replace the interprocess synchronization object
    ///
    /// \param sync The logger uses this synchronization object for
    /// synchronizing output of log messages.
    void setInterprocessSync(isc::util::InterprocessSync* sync);

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(Logger& other);

private:
    friend class isc::log::Formatter<Logger>;

    /// \brief Raw output function
    ///
    /// This is used by the formatter to output formatted output.
    ///
    /// \param severity Severity of the message being output.
    /// \param message Text of the message to be output.
    void output(const Severity& severity, const std::string& message);

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
    /// Returns the logger pointer.  If not yet set, the implementation class is
    /// initialized.
    ///
    /// The main reason for this is to allow loggers to be declared statically
    /// before the underlying logging system is initialized.  However, any
    /// attempt to access a logging method on any logger before initialization -
    /// regardless of whether is is statically or automatically declared -  will
    /// cause a "LoggingNotInitialized" exception to be thrown.
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

    LoggerImpl* loggerptr_;                  ///< Pointer to underlying logger
    char        name_[MAX_LOGGER_NAME_SIZE + 1]; ///< Copy of the logger name
};

} // namespace log
} // namespace isc


#endif // __LOGGER_H
