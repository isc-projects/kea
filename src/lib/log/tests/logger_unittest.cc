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
    TestLogger(const string& name) : Logger(name)
    {}

    /// \brief Logger Equality
    bool operator==(const TestLogger& other) {
        return Logger::operator==(other);
    }

    /// \brief Logger is Null
    bool isInitialized() const {
        return Logger::isInitialized();
    }

    /// \brief Conversion Between log4cxx Number and BIND-10 Severity
    Severity convertLevel(int value) {
        return Logger::convertLevel(value);
    }
};

} // namespace log
} // namespace isc


class LoggerTest : public ::testing::Test {
protected:
    LoggerTest()
    {
    }
};


// Checks that the logger is named correctly.

TEST_F(LoggerTest, Name) {

    // Create a logger
    RootLoggerName::setName("test1");
    Logger logger("alpha");

    // ... and check the name
    EXPECT_EQ(string("test1.alpha"), logger.getName());
}

// This test attempts to get two instances of a logger with the same name
// and checks that they are in fact the same logger.

TEST_F(LoggerTest, GetLogger) {

    // Set the root logger name (not strictly needed, but this will be the
    // case in the program(.
    RootLoggerName::setName("test2");

    const string name1 = "alpha";
    const string name2 = "beta";

    // Instantiate two loggers that should be the same
    TestLogger logger1(name1);
    TestLogger logger2(name1);

    // And check they are equal and non-null
    EXPECT_TRUE(logger1.isInitialized());
    EXPECT_TRUE(logger2.isInitialized());
    EXPECT_TRUE(logger1 == logger2);

    // Instantiate another logger with another name and check that it
    // is different to the previously instantiated ones.
    TestLogger logger3(name2);
    EXPECT_TRUE(logger3.isInitialized());
    EXPECT_FALSE(logger1 == logger3);
}

// Test the number to severity conversion function

TEST_F(LoggerTest, ConvertLevel) {

    // Create a logger
    RootLoggerName::setName("test3");
    TestLogger logger("alpha");

    // Basic 1:1
    EXPECT_EQ(Logger::DEBUG, logger.convertLevel(log4cxx::Level::DEBUG_INT));
    EXPECT_EQ(Logger::INFO, logger.convertLevel(log4cxx::Level::INFO_INT));
    EXPECT_EQ(Logger::WARN, logger.convertLevel(log4cxx::Level::WARN_INT));
    EXPECT_EQ(Logger::WARNING, logger.convertLevel(log4cxx::Level::WARN_INT));
    EXPECT_EQ(Logger::ERROR, logger.convertLevel(log4cxx::Level::ERROR_INT));
    EXPECT_EQ(Logger::FATAL, logger.convertLevel(log4cxx::Level::FATAL_INT));
    EXPECT_EQ(Logger::CRITICAL, logger.convertLevel(log4cxx::Level::FATAL_INT));
    EXPECT_EQ(Logger::NONE, logger.convertLevel(log4cxx::Level::OFF_INT));

    // Now some debug levels
    EXPECT_EQ(Logger::DEBUG,
        logger.convertLevel(log4cxx::Level::DEBUG_INT - 1));
    EXPECT_EQ(Logger::DEBUG,
        logger.convertLevel(log4cxx::Level::DEBUG_INT - MAX_DEBUG_LEVEL));
    EXPECT_EQ(Logger::DEBUG,
        logger.convertLevel(log4cxx::Level::DEBUG_INT - 2 * MAX_DEBUG_LEVEL));
}

// Check that the logger levels are get set properly.

TEST_F(LoggerTest, Severity) {

    // Create a logger
    RootLoggerName::setName("test3");
    Logger logger("alpha");

    // Now check the levels
    logger.setSeverity(Logger::NONE);
    EXPECT_EQ(Logger::NONE, logger.getSeverity());

    logger.setSeverity(Logger::CRITICAL);
    EXPECT_EQ(Logger::CRITICAL, logger.getSeverity());

    logger.setSeverity(Logger::ERROR);
    EXPECT_EQ(Logger::ERROR, logger.getSeverity());

    logger.setSeverity(Logger::WARNING);
    EXPECT_EQ(Logger::WARNING, logger.getSeverity());

    logger.setSeverity(Logger::INFO);
    EXPECT_EQ(Logger::INFO, logger.getSeverity());

    logger.setSeverity(Logger::DEBUG);
    EXPECT_EQ(Logger::DEBUG, logger.getSeverity());

    logger.setSeverity(Logger::DEFAULT);
    EXPECT_EQ(Logger::DEFAULT, logger.getSeverity());
}

// Check that the debug level is set correctly.

TEST_F(LoggerTest, DebugLevels) {

    // Create a logger
    RootLoggerName::setName("test4");
    Logger logger("alpha");

    // Debug level should be 0 if not at debug severity
    logger.setSeverity(Logger::NONE, 20);
    EXPECT_EQ(0, logger.getDebugLevel());

    logger.setSeverity(Logger::INFO, 42);
    EXPECT_EQ(0, logger.getDebugLevel());

    // Should be the value set if the severity is set to DEBUG though.
    logger.setSeverity(Logger::DEBUG, 32);
    EXPECT_EQ(32, logger.getDebugLevel());

    logger.setSeverity(Logger::DEBUG, 97);
    EXPECT_EQ(97, logger.getDebugLevel());

    // Try the limits
    logger.setSeverity(Logger::DEBUG, -1);
    EXPECT_EQ(0, logger.getDebugLevel());

    logger.setSeverity(Logger::DEBUG, 0);
    EXPECT_EQ(0, logger.getDebugLevel());

    logger.setSeverity(Logger::DEBUG, 1);
    EXPECT_EQ(1, logger.getDebugLevel());

    logger.setSeverity(Logger::DEBUG, 98);
    EXPECT_EQ(98, logger.getDebugLevel());

    logger.setSeverity(Logger::DEBUG, 99);
    EXPECT_EQ(99, logger.getDebugLevel());

    logger.setSeverity(Logger::DEBUG, 100);
    EXPECT_EQ(99, logger.getDebugLevel());
}

// Check that changing the parent and child severity does not affect the
// other.

TEST_F(LoggerTest, SeverityInheritance) {

    // Create to loggers.  We cheat here as we know that the underlying
    // implementation (in this case log4cxx) will set a parent-child
    // relationship if the loggers are named <parent> and <parent>.<child>.

    RootLoggerName::setName("test5");
    Logger parent("alpha");
    Logger child("alpha.beta");

    // By default, newly created loggers should have a level of DEFAULT
    // (i.e. default to parent)
    EXPECT_EQ(Logger::DEFAULT, parent.getSeverity());
    EXPECT_EQ(Logger::DEFAULT, child.getSeverity());

    // Set the severity of the child to something other than the default -
    // check it changes and that of the parent does not.
    child.setSeverity(Logger::INFO);
    EXPECT_EQ(Logger::DEFAULT, parent.getSeverity());
    EXPECT_EQ(Logger::INFO, child.getSeverity());

    // Reset the child severity and set that of the parent
    child.setSeverity(Logger::DEFAULT);
    EXPECT_EQ(Logger::DEFAULT, parent.getSeverity());
    EXPECT_EQ(Logger::DEFAULT, child.getSeverity());
    parent.setSeverity(Logger::WARN);
    EXPECT_EQ(Logger::WARN, parent.getSeverity());
    EXPECT_EQ(Logger::DEFAULT, child.getSeverity());
}

// Check that severity is inherited.

TEST_F(LoggerTest, EffectiveSeverityInheritance) {

    // Create to loggers.  We cheat here as we know that the underlying
    // implementation (in this case log4cxx) will set a parent-child
    // relationship if the loggers are named <parent> and <parent>.<child>.

    RootLoggerName::setName("test6");
    Logger parent("test6");
    Logger child("test6.beta");

    // By default, newly created loggers should have a level of DEFAULT
    // (i.e. default to parent) and the root should have a default severity
    // of INFO.  However, the latter is only enforced when created by the
    // RootLogger class, so explicitly set it for the parent for now.
    parent.setSeverity(Logger::INFO);
    EXPECT_EQ(Logger::INFO, parent.getEffectiveSeverity());

    EXPECT_EQ(Logger::DEFAULT, child.getSeverity());
    EXPECT_EQ(Logger::INFO, child.getEffectiveSeverity());

    // Set the severity of the child to something other than the default -
    // check it changes and that of the parent does not.
    child.setSeverity(Logger::FATAL);
    EXPECT_EQ(Logger::INFO, parent.getEffectiveSeverity());
    EXPECT_EQ(Logger::FATAL, child.getEffectiveSeverity());

    // Reset the child severity and check again.
    child.setSeverity(Logger::DEFAULT);
    EXPECT_EQ(Logger::INFO, parent.getEffectiveSeverity());
    EXPECT_EQ(Logger::INFO, child.getEffectiveSeverity());

    // Change the parwnt's severity and check it is reflects in the child.
    parent.setSeverity(Logger::WARN);
    EXPECT_EQ(Logger::WARN, parent.getEffectiveSeverity());
    EXPECT_EQ(Logger::WARN, child.getEffectiveSeverity());
}

// Test the isXxxxEnabled methods.

TEST_F(LoggerTest, IsXxxEnabled) {

    RootLoggerName::setName("test7");
    Logger logger("test7");

    logger.setSeverity(Logger::INFO);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_TRUE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(Logger::WARN);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_FALSE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(Logger::ERROR);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_FALSE(logger.isInfoEnabled());
    EXPECT_FALSE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(Logger::FATAL);
    EXPECT_FALSE(logger.isDebugEnabled());
    EXPECT_FALSE(logger.isInfoEnabled());
    EXPECT_FALSE(logger.isWarnEnabled());
    EXPECT_FALSE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    // Check various debug levels

    logger.setSeverity(Logger::DEBUG);
    EXPECT_TRUE(logger.isDebugEnabled());
    EXPECT_TRUE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    logger.setSeverity(Logger::DEBUG, 45);
    EXPECT_TRUE(logger.isDebugEnabled());
    EXPECT_TRUE(logger.isInfoEnabled());
    EXPECT_TRUE(logger.isWarnEnabled());
    EXPECT_TRUE(logger.isErrorEnabled());
    EXPECT_TRUE(logger.isFatalEnabled());

    // Create a child logger with no severity set, and check that it reflects
    // the severity of the parent logger.

    Logger child("test7.child");
    logger.setSeverity(Logger::FATAL);
    EXPECT_FALSE(child.isDebugEnabled());
    EXPECT_FALSE(child.isInfoEnabled());
    EXPECT_FALSE(child.isWarnEnabled());
    EXPECT_FALSE(child.isErrorEnabled());
    EXPECT_TRUE(child.isFatalEnabled());

    logger.setSeverity(Logger::INFO);
    EXPECT_FALSE(child.isDebugEnabled());
    EXPECT_TRUE(child.isInfoEnabled());
    EXPECT_TRUE(child.isWarnEnabled());
    EXPECT_TRUE(child.isErrorEnabled());
    EXPECT_TRUE(child.isFatalEnabled());
}

// Within the Debug level there are 100 debug levels.  Test that we know
// when to issue a debug message.

TEST_F(LoggerTest, IsDebugEnabledLevel) {

    RootLoggerName::setName("test8");
    Logger logger("test8");

    int MID_LEVEL = (MIN_DEBUG_LEVEL + MAX_DEBUG_LEVEL) / 2;

    logger.setSeverity(Logger::DEBUG);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));

    logger.setSeverity(Logger::DEBUG, MIN_DEBUG_LEVEL);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));

    logger.setSeverity(Logger::DEBUG, MID_LEVEL);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_TRUE(logger.isDebugEnabled(MID_LEVEL - 1));
    EXPECT_TRUE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_FALSE(logger.isDebugEnabled(MID_LEVEL + 1));
    EXPECT_FALSE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));

    logger.setSeverity(Logger::DEBUG, MAX_DEBUG_LEVEL);
    EXPECT_TRUE(logger.isDebugEnabled(MIN_DEBUG_LEVEL));
    EXPECT_TRUE(logger.isDebugEnabled(MID_LEVEL));
    EXPECT_TRUE(logger.isDebugEnabled(MAX_DEBUG_LEVEL));
}

// Check that the message formatting is correct.  As this test program is
// linking with the logger library - which includes messages from the logger
// itself - we'll use those messages for testing.

TEST_F(LoggerTest, Format) {
    RootLoggerName::setName("test9");
    Logger logger("test9");

// Individual arguments
    string result = logger.formatMessage(MSG_OPENIN);
    EXPECT_EQ(string("OPENIN, unable to open %s for input: %s"), result);

    vector<string> args;
    args.push_back("alpha.txt");

    result = logger.formatMessage(MSG_OPENIN, &args);
    EXPECT_EQ(string("OPENIN, unable to open alpha.txt for input: %s"), result);

    args.push_back("test");
    result = logger.formatMessage(MSG_OPENIN, &args);
    EXPECT_EQ(string("OPENIN, unable to open alpha.txt for input: test"), result);

    // Excess arguments should be ignored
    args.push_back("ignore me");
    result = logger.formatMessage(MSG_OPENIN, &args);
    EXPECT_EQ(string("OPENIN, unable to open alpha.txt for input: test"), result);

    // Try the same using concatenated arguments
    string strarg = "alpha.txt";
    result = logger.formatMessage(MSG_OPENIN, strarg);
    EXPECT_EQ(string("OPENIN, unable to open alpha.txt for input: %s"), result);

    strarg += "\0test";
    result = logger.formatMessage(MSG_OPENIN, &args);
    EXPECT_EQ(string("OPENIN, unable to open alpha.txt for input: test"), result);

    // With the latter method, try a few "unusual" argument strings
    strarg = "";
    result = logger.formatMessage(MSG_OPENIN, strarg);
    EXPECT_EQ(string("OPENIN, unable to open %s for input: %s"), result);
    
    strarg="\0";
    result = logger.formatMessage(MSG_OPENIN, strarg);
    EXPECT_EQ(string("OPENIN, unable to open %s for input: %s"), result);

}
