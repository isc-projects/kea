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

#ifndef __LOGGER_IMPL_LOG4CXX_H
#define __LOGGER_IMPL_LOG4CXX_H

#include <cstdlib>
#include <string>
#include <boost/lexical_cast.hpp>
#include <log4cxx/logger.h>
#include <log4cxx/logger.h>

#include <log/debug_levels.h>
#include <log/logger.h>
#include <log/message_types.h>

namespace isc {
namespace log {

/// \brief Log4cxx Logger Implementation
///
/// The logger uses a "pimpl" idiom for implementation, where the base logger
/// class contains little more than a pointer to the implementation class, and
/// all actions are carried out by the latter.  This class is an implementation
/// class interfacing to the log4cxx logging system.

class LoggerImpl {
public:

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
    LoggerImpl(const std::string& name, bool exit_delete = false) :
        loggerptr_(NULL), name_(name), exit_delete_(exit_delete)
    {}


    /// \brief Destructor
    virtual ~LoggerImpl();


    /// \brief Get the full name of the logger (including the root name)
    virtual std::string getName() {
        return (getLogger()->getName());
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
    virtual isc::log::Severity getSeverity() {
        return (getSeverityCommon(getLogger(), false));
    }


    /// \brief Get Effective Severity Level for Logger
    ///
    /// \return The effective severity level of the logger.  This is the same
    /// as getSeverity() if the logger has a severity level set, but otherwise
    /// is the severity of the parent.
    virtual isc::log::Severity getEffectiveSeverity() {
        return (getSeverityCommon(getLogger(), true));
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
    /// \param ident Message identification.
    /// \param text Text to log
    void debug(const MessageID& ident, const char* text) {
        LOG4CXX_DEBUG(getLogger(), ident << ", " << text);
    }


    /// \brief Output Informational Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void info(const MessageID& ident, const char* text) {
        LOG4CXX_INFO(getLogger(), ident << ", " << text);
    }


    /// \brief Output Warning Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void warn(const MessageID& ident, const char* text) {
        LOG4CXX_WARN(getLogger(), ident << ", " << text);
    }


    /// \brief Output Error Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void error(const MessageID& ident, const char* text) {
        LOG4CXX_ERROR(getLogger(), ident << ", " << text);
    }


    /// \brief Output Fatal Message
    ///
    /// \param ident Message identification.
    /// \param text Text to log
    void fatal(const MessageID& ident, const char* text) {
        LOG4CXX_FATAL(getLogger(), ident << ", " << text);
    }

    //@{
    /// \brief Testing Methods
    ///
    /// The next set of methods are used in testing.  As they are accessed from
    /// the main logger class, they must be public.

    /// \brief Equality
    ///
    /// Check if two instances of this logger refer to the same stream.
    /// (This method is principally for testing.)
    ///
    /// \return true if the logger objects are instances of the same logger.
    bool operator==(LoggerImpl& other) {
        return (*loggerptr_ == *other.loggerptr_);
    }


    /// \brief Logger Initialized
    ///
    /// Check that the logger has been properly initialized.  (This method
    /// is principally for testing.)
    ///
    /// \return true if this logger object has been initialized.
    bool isInitialized() {
        return (loggerptr_ != NULL);
    }

    /// \brief Reset Global Data
    ///
    /// Only used for testing, this clears all the logger information and
    /// resets it back to default values.  This is a no-op for log4cxx.
    static void reset() {
    }

    //@}

protected:

    /// \brief Convert Between BIND-10 and log4cxx Logging Levels
    ///
    /// This method is marked protected to allow for unit testing.
    ///
    /// \param value log4cxx numeric logging level
    ///
    /// \return BIND-10 logging severity
    isc::log::Severity convertLevel(int value);

private:

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
    isc::log::Severity getSeverityCommon(const log4cxx::LoggerPtr& ptrlogger,
        bool check_parent);



    /// \brief Initialize log4cxx Logger
    ///
    /// Creates the log4cxx logger used internally.  A function is provided for
    /// this so that the creation does not take place when this Logger object
    /// is created but when it is used.  As the latter occurs in executable
    /// code but the former can occur during initialization, this order
    /// guarantees that anything that is statically initialized has completed
    /// its initialization by the time the logger is used.
    void initLogger();


    /// \brief Return underlying log4cxx logger, initializing it if necessary
    ///
    /// \return Loggerptr object
    log4cxx::LoggerPtr& getLogger() {
        if (loggerptr_ == NULL) {
            initLogger();
        }
        return (*loggerptr_);
    }

    // Members.  Note that loggerptr_ is a pointer to a LoggerPtr, which is
    // itself a pointer to the underlying log4cxx logger.  This is due to the
    // problems with memory deletion on program exit, explained in the comments
    // for the "exit_delete" parameter in this class's constructor.

    log4cxx::LoggerPtr*  loggerptr_;    ///< Pointer to the underlying logger
    std::string          name_;         ///< Name of this logger]
    bool                 exit_delete_;  ///< Delete loggerptr_ on exit?

    // NOTE - THIS IS A PLACE HOLDER
    static bool         init_;      ///< Set true when initialized
};

} // namespace log
} // namespace isc


#endif // __LOGGER_IMPL_LOG4CXX_H
