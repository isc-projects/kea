// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/buffer_appender_impl.h>

#include <log4cplus/loglevel.h>
#include <boost/scoped_ptr.hpp>
#include <cstdio>

namespace isc {
namespace log {
namespace internal {

BufferAppender::~BufferAppender() {
    // If there is anything left in the buffer,
    // it means no reconfig has been done, and
    // we can assume the logging system was either
    // never setup, or broke while doing so.
    // So dump all that is left to stdout
    try {
        flushStdout();
        destructorImpl();
    } catch (...) {
        // Ok if we can't even seem to dump to stdout, never mind.
    }
}

void
BufferAppender::flushStdout() {
    // This does not show a bit of information normal log messages
    // do, so perhaps we should try and setup a new logger here
    // However, as this is called from a destructor, it may not
    // be a good idea; as we can't reliably know whether in what
    // state the logger instance is now (or what the specific logger's
    // settings were).
    LogEventList::const_iterator it;
    for (it = stored_.begin(); it != stored_.end(); ++it) {
        const std::string level(it->first);
        LogEventPtr event(it->second);
        std::printf("%s [%s]: %s\n", level.c_str(),
                    event->getLoggerName().c_str(),
                    event->getMessage().c_str());
    }
    stored_.clear();
}

void
BufferAppender::flush() {
    LogEventList stored_copy;
    stored_.swap(stored_copy);

    LogEventList::const_iterator it;
    for (it = stored_copy.begin(); it != stored_copy.end(); ++it) {
        LogEventPtr event(it->second);
        log4cplus::Logger logger =
            log4cplus::Logger::getInstance(event->getLoggerName());

        logger.log(event->getLogLevel(), event->getMessage());
    }
    flushed_ = true;
}

size_t
BufferAppender::getBufferSize() const {
    return (stored_.size());
}

void
BufferAppender::append(const log4cplus::spi::InternalLoggingEvent& event) {
    if (flushed_) {
        isc_throw(LogBufferAddAfterFlush,
                  "Internal log buffer has been flushed already");
    }
    // get a clone, and put the pointer in a shared_ptr in the list
    std::auto_ptr<log4cplus::spi::InternalLoggingEvent> event_aptr =
        event.clone();
    // Also store the string representation of the log level, to be
    // used in flushStdout if necessary
    stored_.push_back(LevelAndEvent(
                log4cplus::LogLevelManager().toString(event.getLogLevel()),
                LogEventPtr(event_aptr.release())));
}

} // end namespace internal
} // end namespace log
} // end namespace isc
