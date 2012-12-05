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

#include <log/log_buffer.h>
#include <log4cplus/loglevel.h>

#include <boost/scoped_ptr.hpp>
namespace isc {
namespace log {

LogBuffer& getLogBuffer() {
    static boost::scoped_ptr<LogBuffer> log_buffer(NULL);
    if (!log_buffer) {
        log_buffer.reset(new LogBuffer);
    }
    return (*log_buffer);
}

LogBuffer::~LogBuffer() {
    // If there is anything left in the buffer,
    // it means no reconfig has been done, and
    // we can assume the logging system was either
    // never setup, or broke while doing so.
    // So dump all that is left to stdout
    try {
        flushStdout();
    } catch (...) {
        // Ok if we can't even seem to dump to stdout, never mind.
    }
}

void
LogBuffer::add(const log4cplus::spi::InternalLoggingEvent& event) {
    if (flushed_) {
        isc_throw(LogBufferAddAfterFlush,
                  "Internal log buffer has been flushed already");
    }
    // get a clone, and put the pointer in a shared_pt
    std::auto_ptr<log4cplus::spi::InternalLoggingEvent> event_aptr =
        event.clone();
    boost::shared_ptr<log4cplus::spi::InternalLoggingEvent> event_sptr(
        event_aptr.release());
    stored_.push_back(event_sptr);
}

void
LogBuffer::flushStdout() {
    // This does not show a bit of information normal log messages
    // do, so perhaps we should try and setup a new logger here
    // However, as this is called from a destructor, it may not
    // be a good idea; as we can't reliably know whether in what
    // state the logger instance is now (or what the specific logger's
    // settings were).
    // So we print a slightly shortened format (it really only excludes
    // the time and the pid)
    LoggerEventPtrList::const_iterator it;
    const log4cplus::LogLevelManager& manager =
        log4cplus::getLogLevelManager();
    for (it = stored_.begin(); it != stored_.end(); ++it) {
        std::cout << manager.toString((*it)->getLogLevel()) << " " <<
                     "[" << (*it)->getLoggerName() << "] " <<
                     (*it)->getMessage() << std::endl;
    }
    stored_.clear();
}

void
LogBuffer::flush() {
    LoggerEventPtrList::const_iterator it;
    for (it = stored_.begin(); it != stored_.end(); ++it) {
        log4cplus::Logger logger =
            log4cplus::Logger::getInstance((*it)->getLoggerName());

        logger.log((*it)->getLogLevel(), (*it)->getMessage());
    }
    stored_.clear();
    flushed_ = true;
}

size_t
LogBuffer::getBufferSize() const {
    return (stored_.size());
}

void
BufferAppender::append(const log4cplus::spi::InternalLoggingEvent& event) {
    buffer_.add(event);
}

} // end namespace log
} // end namespace isc
