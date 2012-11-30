// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LOG_BUFFER_H
#define LOG_BUFFER_H

#include <exceptions/exceptions.h>

#include <log4cplus/logger.h>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace log {

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

/// \brief Buffering class for logging event
///
/// This class is used to store logging events; it simply keeps any
/// event that is passed to \c add(), and will replay them to the
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
/// an exception if \c add() is called after flush().
///
/// If the LogBuffer instance is destroyed before being flushed, it will
/// dump any event it has left to stdout.
class LogBuffer {
    // For testing purposes, we make this a friend class, so that
    // it can inspect the stored_ vector
    friend class LogBufferTest;

public:
    LogBuffer();
    ~LogBuffer();
    /// \brief add the given event to the list of stored events
    ///
    /// This is called by the BufferAppender.
    ///
    /// \param event The event to store
    /// \exception LogBufferAddAfterFlush if this method is called
    ///            when \c flush() has been called previously
    void add(const log4cplus::spi::InternalLoggingEvent& event);
    void flush();
private:
    void flush_stdout();
    std::vector<log4cplus::spi::InternalLoggingEvent> stored_;
    bool flushed_;
};

/// \brief Log4cplus appender for our buffer
///
/// This class can be set as an Appender for log4cplus loggers
///
/// When logging an event, it will not actually log anything, but
/// merely add it to the singleton LogBuffer instance
class BufferAppender : public log4cplus::Appender {
public:
    /// \brief Constructor
    ///
    /// \note Only a reference to the LogBuffer is stored, so
    /// this buffer must remain in scope during the lifetime of
    /// the appender. In general, only one buffer would be needed,
    /// and for that purpose there is the singleton instance
    /// that can be reached using \c getLogBuffer()
    BufferAppender(LogBuffer& buffer) : buffer_(buffer) {}
    virtual void close() {}
    virtual void append(const log4cplus::spi::InternalLoggingEvent& event);
private:
    LogBuffer& buffer_;
};

/// \brief Getter for the singleton instance of the log buffer
LogBuffer& getLogBuffer();

} // end namespace log
} // end namespace isc

#endif // LOG_BUFFER_H

