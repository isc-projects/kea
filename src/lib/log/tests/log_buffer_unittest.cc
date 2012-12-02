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

#include "config.h"
#include <gtest/gtest.h>

#include <log/macros.h>
#include <log/logger_support.h>
#include <log/log_messages.h>
#include <log/log_buffer.h>

#include <log4cplus/loggingmacros.h>
#include <log4cplus/logger.h>
#include <log4cplus/nullappender.h>

using namespace isc::log;

namespace isc {
namespace log {

class LogBufferTest : public ::testing::Test {
public:
    LogBufferTest() : appender1(new BufferAppender(buffer1)),
                      appender2(new BufferAppender(buffer2)),
                      logger(log4cplus::Logger::getInstance("buffer"))
    {
        logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
    }

    ~LogBufferTest() {
        // If any log messages are left, we don't care, get rid of them,
        // by flushing them to a null appender
        log4cplus::SharedAppenderPtr null_appender(
            new log4cplus::NullAppender());
        logger.removeAllAppenders();
        logger.addAppender(null_appender);
        buffer1.flush();
        buffer2.flush();
    }

    void checkBufferedSize(LogBuffer& buffer, size_t expected) {
        ASSERT_EQ(expected, buffer.stored_.size());
    }

    LogBuffer buffer1;
    LogBuffer buffer2;
    log4cplus::SharedAppenderPtr appender1;
    log4cplus::SharedAppenderPtr appender2;
    log4cplus::Logger logger;
};

// Test that log events are indeed stored, and that they are
// flushed to the new appenders of their logger
TEST_F(LogBufferTest, flush) {
    checkBufferedSize(buffer1, 0);
    checkBufferedSize(buffer2, 0);

    // Create a Logger, log a few messages with the first appender
    logger.addAppender(appender1);
    LOG4CPLUS_INFO(logger, "Foo");
    checkBufferedSize(buffer1, 1);
    LOG4CPLUS_INFO(logger, "Foo");
    checkBufferedSize(buffer1, 2);
    LOG4CPLUS_INFO(logger, "Foo");
    checkBufferedSize(buffer1, 3);

    // Second buffer should still be empty
    checkBufferedSize(buffer2, 0);

    // Replace the appender by the second one, and call flush;
    // this should cause all events to be moved to the second buffer
    logger.removeAllAppenders();
    logger.addAppender(appender2);
    buffer1.flush();
    checkBufferedSize(buffer1, 0);
    checkBufferedSize(buffer2, 3);
}

// Once flushed, logging new messages with the same buffer should fail
TEST_F(LogBufferTest, addAfterFlush) {
    logger.addAppender(appender1);
    buffer1.flush();
    EXPECT_THROW(LOG4CPLUS_INFO(logger, "Foo"), LogBufferAddAfterFlush);
    // It should not have been added
    checkBufferedSize(buffer1, 0);

    // But logging should work again as long as a different buffer is used
    logger.removeAllAppenders();
    logger.addAppender(appender2);
    LOG4CPLUS_INFO(logger, "Foo");
    checkBufferedSize(buffer2, 1);
}

}
}
