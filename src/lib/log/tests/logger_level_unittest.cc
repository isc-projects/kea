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

#include <log/root_logger_name.h>
#include <log/logger.h>
#include <log/messagedef.h>

using namespace isc;
using namespace isc::log;
using namespace std;

class LoggerLevelTest : public ::testing::Test {
protected:
    LoggerLevelTest()
    {}

    ~LoggerLevelTest()
    {}
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
