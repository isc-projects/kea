// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>

#include <log/macros.h>
#include <log/logger_support.h>
#include <log/log_messages.h>
#include <log/buffer_appender_impl.h>

#include <log4cplus/loggingmacros.h>
#include <log4cplus/logger.h>
#include <log4cplus/nullappender.h>
#include <log4cplus/spi/loggingevent.h>

using namespace isc::log;
using namespace isc::log::internal;

namespace isc {
namespace log {

/// \brief Specialized test class
///
/// In order to test append() somewhat directly, this
/// class implements one more method (addEvent)
class TestBufferAppender : public BufferAppender {
public:
    void addEvent(const log4cplus::spi::InternalLoggingEvent& event) {
        append(event);
    }
};

class BufferAppenderTest : public ::testing::Test {
protected:
    BufferAppenderTest() : buffer_appender1(new TestBufferAppender()),
                      appender1(buffer_appender1),
                      buffer_appender2(new TestBufferAppender()),
                      appender2(buffer_appender2),
                      logger(log4cplus::Logger::getInstance("buffer"))
    {
        logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
    }

    ~BufferAppenderTest() {
        // If any log messages are left, we don't care, get rid of them,
        // by flushing them to a null appender
        // Given the 'messages should not get lost' approach of the logging
        // system, not flushing them to a null appender would cause them
        // to be dumped to stdout as the test is destroyed, making
        // unnecessarily messy test output.
        log4cplus::SharedAppenderPtr null_appender(
            new log4cplus::NullAppender());
        logger.removeAllAppenders();
        logger.addAppender(null_appender);
        buffer_appender1->flush();
        buffer_appender2->flush();
    }

    TestBufferAppender* buffer_appender1;
    log4cplus::SharedAppenderPtr appender1;
    TestBufferAppender* buffer_appender2;
    log4cplus::SharedAppenderPtr appender2;
    log4cplus::Logger logger;
};

// Test that log events are indeed stored, and that they are
// flushed to the new appenders of their logger
TEST_F(BufferAppenderTest, flush) {
    ASSERT_EQ(0, buffer_appender1->getBufferSize());
    ASSERT_EQ(0, buffer_appender2->getBufferSize());

    // Create a Logger, log a few messages with the first appender
    logger.addAppender(appender1);
    LOG4CPLUS_INFO(logger, "Foo");
    ASSERT_EQ(1, buffer_appender1->getBufferSize());
    LOG4CPLUS_INFO(logger, "Foo");
    ASSERT_EQ(2, buffer_appender1->getBufferSize());
    LOG4CPLUS_INFO(logger, "Foo");
    ASSERT_EQ(3, buffer_appender1->getBufferSize());

    // Second buffer should still be empty
    ASSERT_EQ(0, buffer_appender2->getBufferSize());

    // Replace the appender by the second one, and call flush;
    // this should cause all events to be moved to the second buffer
    logger.removeAllAppenders();
    logger.addAppender(appender2);
    buffer_appender1->flush();
    ASSERT_EQ(0, buffer_appender1->getBufferSize());
    ASSERT_EQ(3, buffer_appender2->getBufferSize());
}

// Once flushed, logging new messages with the same buffer should fail
TEST_F(BufferAppenderTest, addAfterFlush) {
    logger.addAppender(appender1);
    buffer_appender1->flush();
    EXPECT_THROW(LOG4CPLUS_INFO(logger, "Foo"), LogBufferAddAfterFlush);
    // It should not have been added
    ASSERT_EQ(0, buffer_appender1->getBufferSize());

    // But logging should work again as long as a different buffer is used
    logger.removeAllAppenders();
    logger.addAppender(appender2);
    LOG4CPLUS_INFO(logger, "Foo");
    ASSERT_EQ(1, buffer_appender2->getBufferSize());
}

TEST_F(BufferAppenderTest, addDirectly) {
    // A few direct calls
    log4cplus::spi::InternalLoggingEvent event("buffer",
                                               log4cplus::INFO_LOG_LEVEL,
                                               "Bar", "file", 123);
    buffer_appender1->addEvent(event);
    ASSERT_EQ(1, buffer_appender1->getBufferSize());

    // Do one from a smaller scope to make sure destruction doesn't harm
    {
        log4cplus::spi::InternalLoggingEvent event2("buffer",
                                                    log4cplus::INFO_LOG_LEVEL,
                                                    "Bar", "file", 123);
        buffer_appender1->addEvent(event2);
    }
    ASSERT_EQ(2, buffer_appender1->getBufferSize());

    // And flush them to the next
    logger.removeAllAppenders();
    logger.addAppender(appender2);
    buffer_appender1->flush();
    ASSERT_EQ(0, buffer_appender1->getBufferSize());
    ASSERT_EQ(2, buffer_appender2->getBufferSize());
}

}
}
