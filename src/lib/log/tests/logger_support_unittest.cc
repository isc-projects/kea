// Copyright (C) 2011, 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>
#include <log/logger_support.h>
#include <log/log_messages.h>
#include <util/unittests/test_exceptions.h>

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

    EXPECT_THROW_WITH(test_logger.isDebugEnabled(),
                      LoggingNotInitialized,
                      "attempt to access logging function "
                      "before logging has been initialized");
    EXPECT_THROW_WITH(test_logger.info(LOG_INPUT_OPEN_FAIL),
                      LoggingNotInitialized,
                      "attempt to access logging function "
                      "before logging has been initialized");

    // ... and check that they work when logging is initialized.
    setLoggingInitialized(true);
    EXPECT_NO_THROW(test_logger.isDebugEnabled());
    EXPECT_NO_THROW(test_logger.info(LOG_INPUT_OPEN_FAIL).arg("foo").arg("bar"));
}
