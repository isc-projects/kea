// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <log/logger.h>
#include <log/logger_manager.h>
#include <log/log_messages.h>
#include <log/logger_support.h>

using namespace isc;
using namespace isc::log;
using namespace std;

class LoggerLevelTest : public ::testing::Test {
protected:
    LoggerLevelTest() {
        // Logger initialization is done in main().  As logging tests may
        // alter the default logging output, it is reset here.
        setDefaultLoggingOutput();
    }
    ~LoggerLevelTest() {
        LoggerManager::reset();
    }
};


// Checks that the logger is named correctly.

TEST_F(LoggerLevelTest, Creation) {

    // Default
    isc::log::Level level1;
    EXPECT_EQ(isc::log::DEFAULT, level1.severity);
    EXPECT_EQ(isc::log::MIN_DEBUG_LEVEL, level1.dbglevel);

    // Single argument constructor.
    isc::log::Level level2(isc::log::FATAL);
    EXPECT_EQ(isc::log::FATAL, level2.severity);
    EXPECT_EQ(isc::log::MIN_DEBUG_LEVEL, level2.dbglevel);

    // Two-argument constructor
    isc::log::Level level3(isc::log::DEBUG, 42);
    EXPECT_EQ(isc::log::DEBUG, level3.severity);
    EXPECT_EQ(42, level3.dbglevel);
}

TEST_F(LoggerLevelTest, getSeverity) {
    EXPECT_EQ(DEBUG, getSeverity("DEBUG"));
    EXPECT_EQ(DEBUG, getSeverity("debug"));
    EXPECT_EQ(DEBUG, getSeverity("DeBuG"));
    EXPECT_EQ(INFO, getSeverity("INFO"));
    EXPECT_EQ(INFO, getSeverity("info"));
    EXPECT_EQ(INFO, getSeverity("iNfO"));
    EXPECT_EQ(WARN, getSeverity("WARN"));
    EXPECT_EQ(WARN, getSeverity("warn"));
    EXPECT_EQ(WARN, getSeverity("wARn"));
    EXPECT_EQ(ERROR, getSeverity("ERROR"));
    EXPECT_EQ(ERROR, getSeverity("error"));
    EXPECT_EQ(ERROR, getSeverity("ERRoR"));
    EXPECT_EQ(FATAL, getSeverity("FATAL"));
    EXPECT_EQ(FATAL, getSeverity("fatal"));
    EXPECT_EQ(FATAL, getSeverity("FAtaL"));

    // bad values should default to stdout
    EXPECT_EQ(INFO, getSeverity("some bad value"));
    EXPECT_EQ(INFO, getSeverity(""));

    LoggerManager::reset();
}
