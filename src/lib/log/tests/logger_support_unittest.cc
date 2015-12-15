// Copyright (C) 2011,2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <log/logger_support.h>
#include <log/log_messages.h>

using namespace isc::log;

class LoggerSupportTest : public ::testing::Test {
protected:
    LoggerSupportTest() {
        // Logger initialization is done in main().  As logging tests may
        // alter the default logging output, it is reset here.
        setDefaultLoggingOutput();
    }
    ~LoggerSupportTest() {
    }
};

// Check that the initialized flag can be manipulated.  This is a bit chicken-
// -and-egg: we want to reset to the flag to the original value at the end
// of the test, so use the functions to do that.  But we are trying to check
// that these functions in fact work.

TEST_F(LoggerSupportTest, InitializedFlag) {
    bool current_flag = isLoggingInitialized();

    // check we can flip the flag.
    setLoggingInitialized(!current_flag);
    EXPECT_NE(current_flag, isLoggingInitialized());
    setLoggingInitialized(!isLoggingInitialized());
    EXPECT_EQ(current_flag, isLoggingInitialized());

    // Check we can set it to explicit values (tests that a call to the "set"
    // function does not just flip the flag).
    setLoggingInitialized(false);
    EXPECT_FALSE(isLoggingInitialized());
    setLoggingInitialized(false);
    EXPECT_FALSE(isLoggingInitialized());

    setLoggingInitialized(true);
    EXPECT_TRUE(isLoggingInitialized());
    setLoggingInitialized(true);
    EXPECT_TRUE(isLoggingInitialized());

    // Reset to original value
    setLoggingInitialized(current_flag);
}

// Check that a logger will throw an exception if logging has not been
// initialized.

TEST_F(LoggerSupportTest, LoggingInitializationCheck) {

    // Assert that logging has been initialized (it should be in main()).
    bool current_flag = isLoggingInitialized();
    EXPECT_TRUE(current_flag);

    // Flag that it has not been initialized and declare a logger. Any logging
    // operation should then throw.
    setLoggingInitialized(false);
    isc::log::Logger test_logger("test");

    EXPECT_THROW(test_logger.isDebugEnabled(), LoggingNotInitialized);
    EXPECT_THROW(test_logger.info(LOG_INPUT_OPEN_FAIL), LoggingNotInitialized);

    // ... and check that they work when logging is initialized.
    setLoggingInitialized(true);
    EXPECT_NO_THROW(test_logger.isDebugEnabled());
    EXPECT_NO_THROW(test_logger.info(LOG_INPUT_OPEN_FAIL).arg("foo").arg("bar"));
}
