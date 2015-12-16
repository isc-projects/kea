// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOG_BUFFER_H
#define LOG_BUFFER_H

#include <exceptions/exceptions.h>

#include <log4cplus/logger.h>
#include <log4cplus/spi/loggingevent.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace log {
namespace internal {

/// \brief Buffer add after flush
///
/// This exception is thrown if the log buffer's add() method
/// is called after the log buffer has been flushed; the buffer
/// is only supposed to be used once (until the first time a
/// logger specification is processed)
class LogBufferAddAfterFlush : public isc::Exception {
public:
    LogBufferAddAfterFlush(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// Convenience typedef for a pointer to a log event
typedef boost::shared_ptr<log4cplus::spi::InternalLoggingEvent> LogEventPtr;

/// Convenience typedef for a pair string/logeventptr, the string representing
/// the logger level, as returned by LogLevelManager::toString() at the
/// time of initial logging
typedef std::pair<std::string, LogEventPtr> LevelAndEvent;

/// Convenience typedef for a vector of LevelAndEvent instances
typedef std::vector<LevelAndEvent> LogEventList;

/// \brief Buffering Logger Appender
///
/// This class can be set as an Appender for log4cplus loggers,
/// and is used to store logging events; it simply keeps any
/// event that is passed to \c append(), and will replay them to the
/// logger that they were originally created for when \c flush() is
/// called.
///
/// The idea is that initially, a program may want to do some logging,
/// but does not know where to yet (for instance because it has yet to
/// read and parse its configuration). Any log messages before this time
/// would normally go to some default (say, stdout), and be lost in the
/// real logging destination. By buffering them (and flushing them once
/// the logger has been configured), these log messages are kept in a
/// consistent place, and are not lost.
///
/// Given this goal, this class has an extra check; it will raise
/// an exception if \c append() is called after flush().
///
/// If the BufferAppender instance is destroyed before being flushed,
/// it will dump any event it has left to stdout.
class BufferAppender : public log4cplus::Appender {
public:
    /// \brief Constructor
    ///
    /// Constructs a BufferAppender that buffers log evens
    BufferAppender() : flushed_(false) {}

    /// \brief Destructor
    ///
    /// Any remaining events are flushed to stdout (there should
    /// only be any events remaining if flush() was never called)
    virtual ~BufferAppender();

    /// \brief Close the appender
    ///
    /// This class has no specialized handling for this method
    virtual void close() {}

    /// \brief Flush the internal buffer
    ///
    /// Events that have been stored (after calls to \c append()
    /// are replayed to the logger. Should only be called after
    /// new appenders have been set to the logger.
    void flush();

    /// \brief Returns the number of stored logging events
    ///
    /// Mainly useful for testing
    size_t getBufferSize() const;

protected:
    virtual void append(const log4cplus::spi::InternalLoggingEvent& event);
private:
    /// \brief Helper for the destructor, flush events to stdout
    void flushStdout();

    LogEventList stored_;
    bool flushed_;
};

} // end namespace internal
} // end namespace log
} // end namespace isc

#endif // LOG_BUFFER_H

