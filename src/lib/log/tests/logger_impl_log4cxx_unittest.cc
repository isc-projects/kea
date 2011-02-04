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

// $Id: $

#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/messagedef.h>

using namespace isc;
using namespace isc::log;
using namespace std;

/// \brief Log4cxx Implementation Tests
///
/// Some tests of methods that are not directly tested by the logger unit tests
/// (when the logger is configured to use log4cxx)

namespace isc {
namespace log {

/// \brief Test Logger
///
/// This logger is a subclass of the logger implementation class under test, but
/// makes protected methods public (for testing)

class TestLoggerImpl : public LoggerImpl {
public:
    /// \brief constructor
    TestLoggerImpl(const string& name) : LoggerImpl(name, true)
    {}


    /// \brief Conversion Between log4cxx Number and BIND-10 Severity
    Severity convertLevel(int value) {
        return LoggerImpl::convertLevel(value);
    }
};

} // namespace log
} // namespace isc


class LoggerImplTest : public ::testing::Test {
protected:
    LoggerImplTest()
    {
    }
};

// Test the number to severity conversion function

TEST_F(LoggerImplTest, ConvertLevel) {

    // Create a logger
    RootLoggerName::setName("test3");
    TestLoggerImpl logger("alpha");

    // Basic 1:1
    EXPECT_EQ(isc::log::DEBUG, logger.convertLevel(log4cxx::Level::DEBUG_INT));
    EXPECT_EQ(isc::log::INFO, logger.convertLevel(log4cxx::Level::INFO_INT));
    EXPECT_EQ(isc::log::WARN, logger.convertLevel(log4cxx::Level::WARN_INT));
    EXPECT_EQ(isc::log::WARN, logger.convertLevel(log4cxx::Level::WARN_INT));
    EXPECT_EQ(isc::log::ERROR, logger.convertLevel(log4cxx::Level::ERROR_INT));
    EXPECT_EQ(isc::log::FATAL, logger.convertLevel(log4cxx::Level::FATAL_INT));
    EXPECT_EQ(isc::log::FATAL, logger.convertLevel(log4cxx::Level::FATAL_INT));
    EXPECT_EQ(isc::log::NONE, logger.convertLevel(log4cxx::Level::OFF_INT));

    // Now some debug levels
    EXPECT_EQ(isc::log::DEBUG,
        logger.convertLevel(log4cxx::Level::DEBUG_INT - 1));
    EXPECT_EQ(isc::log::DEBUG,
        logger.convertLevel(log4cxx::Level::DEBUG_INT - MAX_DEBUG_LEVEL));
    EXPECT_EQ(isc::log::DEBUG,
        logger.convertLevel(log4cxx::Level::DEBUG_INT - 2 * MAX_DEBUG_LEVEL));
}
