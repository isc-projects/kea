// Copyright (C) 2011, 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/unittests/resource.h>
#include <util/unittests/check_valgrind.h>

#include <log/logger.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/log_messages.h>
#include <log/interprocess/interprocess_sync_file.h>
#include <log/tests/log_test_messages.h>

#include <iostream>
#include <string>

using namespace isc;
using namespace isc::log;
using namespace std;

/// \brief Logger Test
///
/// As the logger is only a shell around the implementation, this tests also
/// checks the logger implementation class as well.

class LoggerTest : public ::testing::Test {
public:
    LoggerTest() {
        // Initialization of logging is done in main()
    }
    ~LoggerTest() {
        LoggerManager::reset();
    }
};

// Check version

TEST_F(LoggerTest, Version) {
    EXPECT_NO_THROW(Logger::getVersion());
}

// Checks that the logger is named correctly.

TEST_F(LoggerTest, Name) {

    // Create a logger
    Logger logger("alpha");

    // ... and check the name
    EXPECT_EQ(getRootLoggerName() + string(".alpha"), logger.getName());
}

// This test attempts to get two instances of a logger with the same name
// and checks that they are in fact the same logger.

TEST_F(LoggerTest, GetLogger) {

    const char* name1 = "alpha";
    const char* name2 = "beta";

    // Instantiate two loggers that should be the same
    Logger logger1(name1);
    Logger logger2(name1);
    // And check they equal
    EXPECT_TRUE(logger1 == logger2);

    // Instantiate another logger with another name and check that it
    // is different to the previously instantiated ones.
    Logger logger3(name2);
    EXPECT_FALSE(logger1 == logger3);
}

// Check that the logger levels are get set properly.

TEST_F(LoggerTest, Severity) {

    // Create a logger
    Logger logger("alpha");

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
    Logger logger("alpha");

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

    // Create two loggers.  We cheat here as we know that the underlying
    // implementation will set a parent-child relationship if the loggers
    // are named <parent> and <parent>.<child>.
    Logger parent("alpha");
    Logger child("alpha.beta");

    // By default, newly created loggers should have a level of DEFAULT
    // (i.e. default to parent)
    EXPECT_EQ(isc::log::DEFAULT, parent.getSeverity());
    EXPECT_EQ(isc::log::DEFAULT, child.getSeverity());

    // Set the severity of the parent to debug and check what is
    // reported by the child.
    parent.setSeverity(isc::log::DEBUG, 42);
    EXPECT_EQ(42, parent.getDebugLevel());
    EXPECT_EQ(0,  child.getDebugLevel());
    EXPECT_EQ(42, child.getEffectiveDebugLevel());

    // Setting the child to DEBUG severity should set its own
    // debug level.
    child.setSeverity(isc::log::DEBUG, 53);
    EXPECT_EQ(53,  child.getDebugLevel());
    EXPECT_EQ(53, child.getEffectiveDebugLevel());

    // If the child severity is set to something other than DEBUG,
    // the debug level should be reported as 0.
    child.setSeverity(isc::log::ERROR);
    EXPECT_EQ(0,  child.getDebugLevel());
    EXPECT_EQ(0, child.getEffectiveDebugLevel());
}

// Check that changing the parent and child debug level does not affect
// the other.

TEST_F(LoggerTest, DebugLevelInheritance) {

    // Create two loggers.  We cheat here as we know that the underlying
    // implementation will set a parent-child relationship if the loggers
    // are named <parent> and <parent>.<child>.
    Logger parent("alpha");
    Logger child("alpha.beta");

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

    // Create two loggers.  We cheat here as we know that the underlying
    // implementation will set a parent-child relationship if the loggers
    // are named <parent> and <parent>.<child>.
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

    // Change the parent's severity and check it is reflects in the child.
    parent.setSeverity(isc::log::WARN);
    EXPECT_EQ(isc::log::WARN, parent.getEffectiveSeverity());
    EXPECT_EQ(isc::log::WARN, child.getEffectiveSeverity());
}

// Test the isXxxxEnabled methods.

TEST_F(LoggerTest, IsXxxEnabled) {

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

// Check that loggers with invalid names give an error.

TEST_F(LoggerTest, LoggerNameLength) {
    // Null name
    EXPECT_THROW(Logger(NULL), LoggerNameNull);

    // Declare space for the logger name.  The length of names checked
    // will range from 0 through MAX_LOGGER_NAME_SIZE + 1: to allow for
    // the trailing null, at least one more byte than the longest name size
    // must be reserved.
    char name[Logger::MAX_LOGGER_NAME_SIZE + 2];

    // Zero-length name should throw an exception
    name[0] = '\0';
    EXPECT_THROW({
            Logger dummy(name);
            }, LoggerNameError);

    // Work through all valid names.
    for (size_t i = 0; i < Logger::MAX_LOGGER_NAME_SIZE; ++i) {

        // Append a character to the name and check that a logger with that
        // name can be created without throwing an exception.
        name[i] = 'X';
        name[i + 1] = '\0';
        EXPECT_NO_THROW({
                Logger dummy(name);
                }) << "Size of logger name is " << (i + 1);
    }

    // ... and check that an overly long name throws an exception.
    name[Logger::MAX_LOGGER_NAME_SIZE] = 'X';
    name[Logger::MAX_LOGGER_NAME_SIZE + 1] = '\0';
    EXPECT_THROW({
            Logger dummy(name);
            }, LoggerNameError);

}

TEST_F(LoggerTest, setInterprocessSync) {
    // Create a logger
    Logger logger("alpha");

    EXPECT_THROW(logger.setInterprocessSync(NULL), BadInterprocessSync);
}

class MockSync : public isc::log::interprocess::InterprocessSync {
public:
    /// \brief Constructor
    MockSync(const std::string& component_name) :
        InterprocessSync(component_name), was_locked_(false),
        was_unlocked_(false)
    {}

    bool wasLocked() const {
        return (was_locked_);
    }

    bool wasUnlocked() const {
        return (was_unlocked_);
    }

protected:
    bool lock() {
        was_locked_ = true;
        return (true);
    }

    bool tryLock() {
        return (true);
    }

    bool unlock() {
        was_unlocked_ = true;
        return (true);
    }

private:
    bool was_locked_;
    bool was_unlocked_;
};

// Checks that the logger logs exclusively and other Kea components
// are locked out.

TEST_F(LoggerTest, Lock) {
    // Create a logger
    Logger logger("alpha");

    // Setup our own mock sync object so that we can intercept the lock
    // call and check if a lock has been taken.
    MockSync* sync = new MockSync("logger");
    logger.setInterprocessSync(sync);

    // Log a message and put things into play.
    logger.setSeverity(isc::log::INFO, 100);
    logger.info(LOG_LOCK_TEST_MESSAGE);

    EXPECT_TRUE(sync->wasLocked());
    EXPECT_TRUE(sync->wasUnlocked());
}
