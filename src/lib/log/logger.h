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
#include <boost/lexical_cast.hpp>
#include <log4cxx/logger.h>

#include <log/dbglevels.h>
#include <log/message_types.h>

namespace isc {
namespace log {

class Logger {
public:

    /// \brief Severity Levels
    typedef enum {
        DEFAULT,    // Default to logging level of parent
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NONE        // Disable logging
    } Severity;

    /// \brief Constructor
    ///
    /// Creates/attaches to a logger of a specific name.
    ///
    /// \param name Name of the logger.  If the name is that of the root name,
    /// this creates an instance of the root logger; otherwise it creates a
    /// child of the root logger.
    ///
    /// \param exit_delete This argument is present to get round a bug in
    /// log4cxx.  If a log4cxx logger is declared outside an execution unit, it
    /// is not deleted until the program runs down.  At that point all such
    /// objects - including internal log4cxx objects - are deleted.  However,
    /// there seems to be a bug in log4cxx where the way that such objects are
    /// destroyed causes a MutexException to be thrown (this is described in
    /// https://issues.apache.org/jira/browse/LOGCXX-322).  As this only occurs
    /// during program rundown, the issue is not serious - it just looks bad to
    /// have the program crash instead of shut down cleanly.\n
    /// \n
    /// The original implementation of the isc::log::Logger had as a member a
    /// log4cxx logger (actually a LoggerPtr).  If the isc:: Logger was declared
    /// statically, when it was destroyed at the end of the program the internal
    /// LoggerPtr was destroyed, which triggered the problem.  The problem did
    /// not occur if the isc::log::Logger was created on the stack.  To get
    /// round this, the internal LoggerPtr is now created dynamically.  The
    /// exit_delete argument controls its destruction: if true, it is destroyed
    /// in the ISC Logger destructor.  If false, it is not.\n
    /// \n
    /// When creating an isc::log::Logger on the stack, the argument should be
    /// false (the default); when the Logger is destroyed, all the internal
    /// log4cxx objects are destroyed.  As only the logger (and not the internal
    /// log4cxx data structures are being destroyed), all is well.  However,
    /// when creating the logger statically, the argument should be false.  This
    /// means that the log4cxx objects are not destroyed at program rundown;
    /// instead memory is reclaimed and files are closed when the process is
    /// destroyed, something that does not trigger the bug.
    Logger(const std::string& name, bool exit_delete = false) :
        loggerptr_(), name_(name), exit_delete_(exit_delete)
    {}


    /// \brief Destructor
    virtual ~Logger();


    /// \brief Configure Options
    ///
    /// TEMPORARY: Pass in the command-line options to set the logging severity
    /// for the root logger.  Future versions of the logger will get this
    /// information from the configuration database.
    ///
    /// \param severity Severity level to log
    /// \param dbglevel If the severity is DEBUG, this is the debug level.
    /// This can be in the range 1 to 100 and controls the verbosity.  A value
    /// outside these limits is silently coerced to the nearest boundary.
    /// \param local_file If provided, the name of a message file to read in and
    /// supersede one or more of the current messages.
    static void runTimeInit(Severity severity = INFO, int dbglevel = 1,
        const char* local_file = NULL);


    /// \brief Get Name of Logger
    ///
    /// \return The full name of the logger (including the root name)
    virtual std::string getName() {
        return getLogger()->getName();
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
    virtual Severity getSeverity() {
        return getSeverityCommon(getLogger(), false);
    }

    /// \brief Get Effective Severity Level for Logger
    ///
    /// \return The effective severity level of the logger.  This is the same
    /// as getSeverity() if the logger has a severity level set, but otherwise
    /// is the severity of the parent.
    virtual Severity getEffectiveSeverity() {
        return getSeverityCommon(getLogger(), true);
    }


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
    isDebugEnabled(int dbglevel = MIN_DEBUG_LEVEL) {
        return (getLogger()->getEffectiveLevel()->toInt() <=
            (log4cxx::Level::DEBUG_INT - dbglevel));
    }


    /// \brief Is INFO Enabled?
    virtual bool isInfoEnabled() {
        return (getLogger()->isInfoEnabled());
    }


    /// \brief Is WARNING Enabled?
    virtual bool isWarnEnabled() {
        return (getLogger()->isWarnEnabled());
    }


    /// \brief Is ERROR Enabled?
    virtual bool isErrorEnabled() {
        return (getLogger()->isErrorEnabled());
    }


    /// \brief Is FATAL Enabled?
    virtual bool isFatalEnabled() {
        return (getLogger()->isFatalEnabled());
    }


    /// \brief Output Debug Message
    ///
    /// \param dbglevel Debug level, ranging between 0 and 99.  Higher numbers
    /// are used for more verbose output.
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void debug(int dbglevel, MessageID ident, ...);


    /// \brief Output Informational Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void info(MessageID ident, ...);


    /// \brief Output Warning Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void warn(MessageID ident, ...);


    /// \brief Output Error Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void error(MessageID ident, ...);


    /// \brief Output Fatal Message
    ///
    /// \param ident Message identification.
    /// \param ... Optional arguments for the message.
    void fatal(MessageID ident, ...);


protected:

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    /// (This method is principally for testing.)
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(const Logger& other) const {
        return (*loggerptr_ == *other.loggerptr_);
    }


    /// \brief Logger Initialized
    ///
    /// Check that the logger has been properly initialized.  (This method
    /// is principally for testing.)
    ///
    /// \return true if this logger object has been initialized.
    bool isInitialized() const {
        return (loggerptr_ != NULL);
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


    /// \brief Initialize log4cxx Logger
    ///
    /// Creates the log4cxx logger used internally.  A function is provided for
    /// this so that the creation does not take place when this Logger object
    /// is created but when it is used.  As the latter occurs in executable
    /// code but the former can occur during initialization, this order
    /// guarantees that anything that is statically initialized has completed
    /// its initialization by the time the logger is used.
    void initLogger();


    /// \brief Return log4cxx Logger
    ///
    /// Returns the log4cxx logger, initializing it if not already initialized.
    ///
    /// \return Loggerptr object
    log4cxx::LoggerPtr& getLogger() {
        if (loggerptr_ == NULL) {
            initLogger();
        }
        return *loggerptr_;
    }


    /// \brief Read Local Message File
    ///
    /// Reads a local message file into the global dictionary, replacing any
    /// definitions there.  Any messages found in the local file that do not
    /// replace ones in the global dictionary are listed.
    ///
    /// \param file Local message file to be read.
    static void readLocalMessageFile(const char* file);

private:
    // Note that loggerptr_ is a pointer to a LoggerPtr, which is itself a
    // pointer to the underlying log4cxx logger.  This is due to the problems
    // with memory deletion on program exit, explained in the comments for
    // the "exit_delete" parameter in this class's constructor.

    log4cxx::LoggerPtr*  loggerptr_;    ///< Pointer to the underlying logger
    std::string          name_;         ///< Name of this logger]
    bool                 exit_delete_;  ///< Delete loggerptr_ on exit?

    // NOTE - THIS IS A PLACE HOLDER
    static bool         init_;      ///< Set true when initialized
};

} // namespace log
} // namespace isc


#endif // __LOGGER_H
