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

#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/messagedef.h>

using namespace isc;
using namespace isc::log;
using namespace std;

namespace isc {
namespace log {

/// \brief Test Logger
///
/// This logger is a subclass of the logger class under test, but makes
/// protected methods public (for testing)

class TestLogger : public Logger {
public:
    /// \brief constructor
    TestLogger(const string& name) : Logger(name, true)
    {}

    static void reset() {
        Logger::reset();
    }
};

} // namespace log
} // namespace isc


class LoggerTest : public ::testing::Test {
protected:
    LoggerTest()
    {
    }

    ~LoggerTest() {
        TestLogger::reset();
    }
};


// Checks that the logger is named correctly.

TEST_F(LoggerTest, Name) {

    // Create a logger
    setRootLoggerName("test1");
    Logger logger("alpha");

    // ... and check the name
    EXPECT_EQ(string("test1.alpha"), logger.getName());
}

// This test attempts to get two instances of a logger with the same name
// and checks that they are in fact the same logger.

TEST_F(LoggerTest, GetLogger) {

    // Set the root logger name (not strictly needed, but this will be the
    // case in the program(.
    setRootLoggerName("test2");

    const string name1 = "alpha";
    const string name2 = "beta";

    // Instantiate two loggers that should be the same
    TestLogger logger1(name1);
    TestLogger logger2(name1);
    // And check they equal
    EXPECT_TRUE(logger1 == logger2);

    // Instantiate another logger with another name and check that it
    // is different to the previously instantiated ones.
    TestLogger logger3(name2);
    EXPECT_FALSE(logger1 == logger3);
}

// Check that the logger levels are get set properly.

TEST_F(LoggerTest, Severity) {

    // Create a logger
    setRootLoggerName("test3");
    TestLogger logger("alpha");

    // Now check the levels
    logger.setSeverity(isc::log::NONE);
    EXPECT_EQ(isc::log::NONE, logger.getSeverity());

    logger.setSeverity(isc::log::FATAL);
    EXPECT_EQ(isc::log::FATAL, logger.getSeverity());

    logger.setSeverity(isc::log::ERROR);
    EXPECT_EQ(isc::log::ERROR, logger.getSeverity());

    logger.setSeverity(isc::log::WARN);
    EXPECT_EQ(isc::log::WARN, logger.getSeverity());

    logger.setSeverity(isc::log::INFO);
    EXPECT_EQ(isc::log::INFO, logger.getSeverity());

    logger.setSeverity(isc::log::DEBUG);
    EXPECT_EQ(isc::log::DEBUG, logger.getSeverity());

    logger.setSeverity(isc::log::DEFAULT);
    EXPECT_EQ(isc::log::DEFAULT, logger.getSeverity());
}

// Check that the debug level is set correctly.

TEST_F(LoggerTest, DebugLevels) {

    // Create a logger
    setRootLoggerName("test4");
    TestLogger logger("alpha");

    // Debug level should be 0 if not at debug severity
    logger.setSeverity(isc::log::NONE, 20);
    EXPECT_EQ(0, logger.getDebugLevel());

    logger.setSeverity(isc::log::INFO, 42);
    EXPECT_EQ(0, logger.getDebugLevel());

    // Should be the value set if the severity is set to DEBUG though.
    logger.setSeverity(isc::log::DEBUG, 32);
    EXPECT_EQ(32, logger.getDebugLevel());

    logger.setSeverity(isc::log::DEBUG, 97);
    EXPECT_EQ(97, logger.getDebugLevel());

    // Try the limits
    logger.setSeverity(isc::log::DEBUG, -1);
    EXPECT_EQ(0, logger.getDebugLevel());

    logger.setSeverity(isc::log::DEBUG, 0);
    EXPECT_EQ(0, logger.getDebugLevel());

    logger.setSeverity(isc::log::DEBUG, 1);
    EXPECT_EQ(1, logger.getDebugLevel());

    logger.setSeverity(isc::log::DEBUG, 98);
    EXPECT_EQ(98, logger.getDebugLevel());

    logger.setSeverity(isc::log::DEBUG, 99);
    EXPECT_EQ(99, logger.getDebugLevel());

    logger.setSeverity(isc::log::DEBUG, 100);
    EXPECT_EQ(99, logger.getDebugLevel());
}

// Check that changing the parent and child severity does not affect the
// other.

TEST_F(LoggerTest, SeverityInheritance) {

    // Create to loggers.  We cheat here as we know that the underlying
    // implementation (in this case log4cxx) will set a parent-child
    // relationship if the loggers are named <parent> and <parent>.<child>.

    setRootLoggerName("test5");
    TestLogger parent("alpha");
    TestLogger child("alpha.beta");

    // By default, newly created loggers should have a level of DEFAULT
    // (i.e. default to parent)
    EXPECT_EQ(isc::log::DEFAULT, parent.getSeverity());
    EXPECT_EQ(isc::log::DEFAULT, child.getSeverity());

    // Set the severity of the child to something other than the default -
    // check it changes and that of the parent does not.
    child.setSeverity(isc::log::INFO);
    EXPECT_EQ(isc::log::DEFAULT, parent.getSeverity());
    EXPECT_EQ(isc::log::INFO, child.getSeverity());

    // Reset the child severity and set that of the parent
    child.setSeverity(isc::log::DEFAULT);
    EXPECT_EQ(isc::log::DEFAULT, parent.getSeverity());
    EXPECT_EQ(isc::log::DEFAULT, child.getSeverity());
    parent.setSeverity(isc::log::WARN);
    EXPECT_EQ(isc::log::WARN, parent.getSeverity());
    EXPECT_EQ(isc::log::DEFAULT, child.getSeverity());
}

// Check that severity is inherited.

TEST_F(LoggerTest, EffectiveSeverityInheritance) {

    // Create to loggers.  We cheat here as we know that the underlying
    // implementation (in this case log4cxx) will set a parent-child
    // relationship if the loggers are named <parent> and <parent>.<child>.

    setRootLoggerName("test6");
    Logger parent("test6");
    Logger child("test6.beta");

    // By default, newly created loggers should have a level of DEFAULT
    // (i.e. default to parent) and the root should have a default severity
    // of INFO.  However, the latter is only enforced when created by the
    // RootLogger class, so explicitly set it for the parent for now.
    parent.setSeverity(isc::log::INFO);
    EXPECT_EQ(isc::log::INFO, parent.getEffectiveSeverity());

    EXPECT_EQ(isc::log::DEFAULT, child.getSeverity());
    EXPECT_EQ(isc::log::INFO, child.getEffectiveSeverity());

    // Set the severity of the child to something other than the default -
    // check it changes and that of the parent does not.
    child.setSeverity(isc::log::FATAL);
    EXPECT_EQ(isc::log::INFO, parent.getEffectiveSeverity());
    EXPECT_EQ(isc::log::FATAL, child.getEffectiveSeverity());

    // Reset the child severity and check again.
    child.setSeverity(isc::log::DEFAULT);
    EXPECT_EQ(isc::log::INFO, parent.getEffectiveSeverity());
    EXPECT_EQ(isc::log::INFO, child.getEffectiveSeverity());

    // Change the parwnt's severity and check it is reflects in the child.
    parent.setSeverity(isc::log::WARN);
    EXPECT_EQ(isc::log::WARN, parent.getEffectiveSeverity());
    EXPECT_EQ(isc::log::WARN, child.getEffectiveSeverity());
}

// Test the isXxxxEnabled methods.

TEST_F(LoggerTest, IsXxxEnabled) {

    setRootLoggerName("test7");
    Logger logger("test7");

    logger.setSeverity(isc::log::INFO);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_TRUE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(isc::log::WARN);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_FALSE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(isc::log::ERROR);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_FALSE(logger.isInfoEnabled());
    EXPECT_FALSE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(isc::log::FATAL);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_FALSE(logger.isInfoEnabled());
    EXPECT_FALSE(logger.isWarnEnabled());
    EXPECT_FALSE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    // Check various debug levels

    logger.setSeverity(isc::log::DEBUG);
    EXPECT_TRUE(logger.isDebugEnabled());
    EXPECT_TRUE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(isc::log::DEBUG, 45);
    EXPECT_TRUE(logger.isDebugEnabled());
    EXPECT_TRUE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    // Create a child logger with no severity set, and check that it reflects
    // the severity of the parent logger.

    Logger child("test7.child");
    logger.setSeverity(isc::log::FATAL);
    EXPECT_FALSE(child.isDebugEnabled());
    EXPECT_FALSE(child.isInfoEnabled());
    EXPECT_FALSE(child.isWarnEnabled());
    EXPECT_FALSE(child.isErrorEnabled());
    EXPECT_TRUE(child.isFatalEnabled());

    logger.setSeverity(isc::log::INFO);
    EXPECT_FALSE(child.isDebugEnabled());
    EXPECT_TRUE(child.isInfoEnabled());
    EXPECT_TRUE(child.isWarnEnabled());
    EXPECT_TRUE(child.isErrorEnabled());
    EXPECT_TRUE(child.isFatalEnabled());
}

// Within the Debug level there are 100 debug levels.  Test that we know
// when to issue a debug message.

TEST_F(LoggerTest, IsDebugEnabledLevel) {

    setRootLoggerName("test8");
    Logger logger("test8");

    int MID_LEVEL = (MIN_DEBUG_LEVEL + MAX_DEBUG_LEVEL) / 2;

    logger.setSeverity(isc::log::DEBUG);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));

    logger.setSeverity(isc::log::DEBUG, MIN_DEBUG_LEVEL);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));

    logger.setSeverity(isc::log::DEBUG, MID_LEVEL);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_TRUE(logger.isDebugEnabled(MID_LEVEL - 1));
    EXPECT_TRUE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MID_LEVEL + 1));
    EXPECT_FALSE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));

    logger.setSeverity(isc::log::DEBUG, MAX_DEBUG_LEVEL);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_TRUE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_TRUE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));
}
