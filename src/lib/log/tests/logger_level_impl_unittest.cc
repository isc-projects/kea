// Copyright (C) 2011,2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include <boost/static_assert.hpp>
#include <boost/lexical_cast.hpp>

#include <log/logger_level_impl.h>
#include <log/logger_support.h>
#include <log4cplus/logger.h>

using namespace isc::log;
using namespace std;

class LoggerLevelImplTest : public ::testing::Test {
protected:
    LoggerLevelImplTest() {
        // Ensure logging set to default for unit tests
        setDefaultLoggingOutput();
    }

    ~LoggerLevelImplTest()
    {}
};


// Checks that the log4cplus and Kea levels convert correctly
TEST_F(LoggerLevelImplTest, DefaultConversionFromBind) {
    log4cplus::LogLevel fatal =
        LoggerLevelImpl::convertFromBindLevel(Level(FATAL));
    EXPECT_EQ(log4cplus::FATAL_LOG_LEVEL, fatal);

    log4cplus::LogLevel error =
        LoggerLevelImpl::convertFromBindLevel(Level(ERROR));
    EXPECT_EQ(log4cplus::ERROR_LOG_LEVEL, error);

    log4cplus::LogLevel warn =
        LoggerLevelImpl::convertFromBindLevel(Level(WARN));
    EXPECT_EQ(log4cplus::WARN_LOG_LEVEL, warn);

    log4cplus::LogLevel info =
        LoggerLevelImpl::convertFromBindLevel(Level(INFO));
    EXPECT_EQ(log4cplus::INFO_LOG_LEVEL, info);

    log4cplus::LogLevel debug =
        LoggerLevelImpl::convertFromBindLevel(Level(DEBUG));
    EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL, debug);
}

// Checks that the debug severity and level converts correctly
TEST_F(LoggerLevelImplTest, DebugConversionFromBind) {
    log4cplus::LogLevel debug0 =
        LoggerLevelImpl::convertFromBindLevel(Level(DEBUG, 0));
    EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - 0, debug0);

    log4cplus::LogLevel debug1 =
        LoggerLevelImpl::convertFromBindLevel(Level(DEBUG, 1));
    EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - 1, debug1);

    log4cplus::LogLevel debug99 =
        LoggerLevelImpl::convertFromBindLevel(Level(DEBUG, 99));
    EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - 99, debug99);

    // Out of range should be coerced to the nearest boundary
    log4cplus::LogLevel debug_1 =
        LoggerLevelImpl::convertFromBindLevel(Level(DEBUG, MIN_DEBUG_LEVEL - 1));
    EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL, debug_1);

    log4cplus::LogLevel debug100 =
        LoggerLevelImpl::convertFromBindLevel(Level(DEBUG, MAX_DEBUG_LEVEL + 1));
    EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - MAX_DEBUG_LEVEL, debug100);
}

// Do the checks the other way
static void
test_convert_to(const char* trace, isc::log::Severity severity, int dbglevel,
                log4cplus::LogLevel level)
{
    SCOPED_TRACE(trace);
    Level test = LoggerLevelImpl::convertToBindLevel(level);
    EXPECT_EQ(severity, test.severity);
    EXPECT_EQ(dbglevel, test.dbglevel);
}

TEST_F(LoggerLevelImplTest, ConversionToBind) {
    test_convert_to("FATAL", FATAL, MIN_DEBUG_LEVEL, log4cplus::FATAL_LOG_LEVEL);
    test_convert_to("ERROR", ERROR, MIN_DEBUG_LEVEL, log4cplus::ERROR_LOG_LEVEL);
    test_convert_to("WARN",  WARN , MIN_DEBUG_LEVEL, log4cplus::WARN_LOG_LEVEL);
    test_convert_to("INFO",  INFO , MIN_DEBUG_LEVEL, log4cplus::INFO_LOG_LEVEL);
    test_convert_to("DEBUG",  DEBUG, MIN_DEBUG_LEVEL, log4cplus::DEBUG_LOG_LEVEL);

    test_convert_to("DEBUG0",  DEBUG, MIN_DEBUG_LEVEL + 0,
            (log4cplus::DEBUG_LOG_LEVEL));
    test_convert_to("DEBUG1",  DEBUG, MIN_DEBUG_LEVEL + 1,
            (log4cplus::DEBUG_LOG_LEVEL - 1));
    test_convert_to("DEBUG2",  DEBUG, MIN_DEBUG_LEVEL + 2,
            (log4cplus::DEBUG_LOG_LEVEL - 2));
    test_convert_to("DEBUG99",  DEBUG, MIN_DEBUG_LEVEL + 99,
            (log4cplus::DEBUG_LOG_LEVEL - 99));

    // ... and some invalid valid values
    test_convert_to("DEBUG-1",  INFO, MIN_DEBUG_LEVEL,
            (log4cplus::DEBUG_LOG_LEVEL + 1));
    BOOST_STATIC_ASSERT(MAX_DEBUG_LEVEL == 99);
    test_convert_to("DEBUG+100",  DEFAULT, 0,
            (log4cplus::DEBUG_LOG_LEVEL - MAX_DEBUG_LEVEL - 1));
}

// Check that we can convert from a string to the new log4cplus levels
TEST_F(LoggerLevelImplTest, FromString) {

    // Test all valid values
    for (int i = MIN_DEBUG_LEVEL; i <= MAX_DEBUG_LEVEL; ++i) {
        std::string token = string("DEBUG") + boost::lexical_cast<std::string>(i);
        EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - i,
                  LoggerLevelImpl::logLevelFromString(token));
    }

    // ... in lowercase too
    for (int i = MIN_DEBUG_LEVEL; i <= MAX_DEBUG_LEVEL; ++i) {
        std::string token = string("debug") + boost::lexical_cast<std::string>(i);
        EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - i,
                  LoggerLevelImpl::logLevelFromString(token));
    }

    // A few below the minimum
    for (int i = MIN_DEBUG_LEVEL - 5; i < MIN_DEBUG_LEVEL; ++i) {
        std::string token = string("DEBUG") + boost::lexical_cast<std::string>(i);
        EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL, LoggerLevelImpl::logLevelFromString(token));
    }

    // ... and above the maximum
    for (int i = MAX_DEBUG_LEVEL + 1; i < MAX_DEBUG_LEVEL + 5; ++i) {
        std::string token = string("DEBUG") + boost::lexical_cast<std::string>(i);
        EXPECT_EQ(log4cplus::DEBUG_LOG_LEVEL - MAX_DEBUG_LEVEL,
                  LoggerLevelImpl::logLevelFromString(token));
    }

    // Invalid strings.
    EXPECT_EQ(log4cplus::NOT_SET_LOG_LEVEL,
              LoggerLevelImpl::logLevelFromString("DEBU"));
    EXPECT_EQ(log4cplus::NOT_SET_LOG_LEVEL,
              LoggerLevelImpl::logLevelFromString("unrecognized"));
}

// ... and check the conversion back again.  All levels should convert to "DEBUG".
TEST_F(LoggerLevelImplTest, ToString) {

    for (int i = MIN_DEBUG_LEVEL; i <= MAX_DEBUG_LEVEL; ++i) {
        EXPECT_EQ(std::string("DEBUG"),
                  LoggerLevelImpl::logLevelToString(log4cplus::DEBUG_LOG_LEVEL - i));
    }

    // ... and that out of range stuff returns an empty string.
    EXPECT_EQ(std::string(),
              LoggerLevelImpl::logLevelToString(log4cplus::DEBUG_LOG_LEVEL + 1));
    EXPECT_EQ(std::string(),
              LoggerLevelImpl::logLevelToString(
                               log4cplus::DEBUG_LOG_LEVEL - MAX_DEBUG_LEVEL - 100));
}
