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

#include <log4cxx/level.h>
#include <log/xdebuglevel.h>
#include <log/dbglevels.h>

/// \brief XDebugLevel (Debug Extension to Level Class)
///
/// The class is an extension of the log4cxx Level class; this set of tests
/// only test the extensions, they do not test the underlying Level class
/// itself.

using namespace log4cxx;

class XDebugLevelTest : public ::testing::Test {
protected:
    XDebugLevelTest()
    {
    }
};

// Check a basic assertion about the numeric values of the debug levels

TEST_F(XDebugLevelTest, NumericValues) {
    EXPECT_EQ(XDebugLevel::XDEBUG_MIN_LEVEL_INT, Level::DEBUG_INT);
    EXPECT_EQ(XDebugLevel::XDEBUG_MAX_LEVEL_INT,
        Level::DEBUG_INT - MAX_DEBUG_LEVEL);

    // ... and check that assumptions used below - that the debug levels
    // range from 0 to 99 - are valid.
    EXPECT_EQ(0, MIN_DEBUG_LEVEL);
    EXPECT_EQ(99, MAX_DEBUG_LEVEL);
}


// Checks that the main function for generating logging level objects from
// debug levels is working.

TEST_F(XDebugLevelTest, GetExtendedDebug) {

    // Get a debug level of 0.  This should be the same as the main DEBUG
    // level.
    LevelPtr debug0 = XDebugLevel::getExtendedDebug(0);
    EXPECT_EQ(std::string("DEBUG"), debug0->toString());
    EXPECT_EQ(Level::DEBUG_INT, debug0->toInt());
    EXPECT_TRUE(*Level::getDebug() == *debug0);

    // Get an arbitrary debug level in the allowed range.
    LevelPtr debug32 = XDebugLevel::getExtendedDebug(32);
    EXPECT_EQ(std::string("DEBUG32"), debug32->toString());
    EXPECT_TRUE((XDebugLevel::XDEBUG_MIN_LEVEL_INT - 32) == debug32->toInt());

    // Check that a value outside the range gives the nearest level.
    LevelPtr debug_more = XDebugLevel::getExtendedDebug(MAX_DEBUG_LEVEL + 1);
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(MAX_DEBUG_LEVEL) == *debug_more);

    LevelPtr debug_less = XDebugLevel::getExtendedDebug(MIN_DEBUG_LEVEL - 1);
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(MIN_DEBUG_LEVEL) == *debug_less);
}


// Creation of a level from an int - should return the default debug level
// if outside the range.

TEST_F(XDebugLevelTest, FromIntOneArg) {

    // Check that a valid debug level is as expected
    LevelPtr debug42 = XDebugLevel::toLevel(
        XDebugLevel::XDEBUG_MIN_LEVEL_INT - 42);
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(42) == *debug42);

    // ... and that an invalid one returns an object of type debug.
    LevelPtr debug_invalid = XDebugLevel::toLevel(Level::getInfo()->toInt());
    EXPECT_TRUE(*Level::getDebug() == *debug_invalid);
}


// Creation of a level from an int - should return the default level
// if outside the range.

TEST_F(XDebugLevelTest, FromIntTwoArg) {

    // Check that a valid debug level is as expected
    LevelPtr debug42 = XDebugLevel::toLevel(
        (XDebugLevel::XDEBUG_MIN_LEVEL_INT - 42), Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(42) == *debug42);

    // ... and that an invalid one returns an object of type debug.
    LevelPtr debug_invalid = XDebugLevel::toLevel(
        Level::getInfo()->toInt(), Level::getFatal());
    EXPECT_TRUE(*Level::getFatal() == *debug_invalid);
}


// Creation of a level from a string - should return the default debug level
// if outside the range.

TEST_F(XDebugLevelTest, FromStringOneArg) {

    // Check that a valid debug levels are as expected
    LevelPtr debug85 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG85"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(85) == *debug85);

    LevelPtr debug92 = XDebugLevel::toLevelLS(LOG4CXX_STR("debug92"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(92) == *debug92);

    LevelPtr debug27 = XDebugLevel::toLevelLS(LOG4CXX_STR("Debug27"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(27) == *debug27);

    LevelPtr debug0 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(0) == *debug0);

    // ... and that an invalid one returns an object of type debug (which is
    // the equivalent of a debug level 0 object).
    LevelPtr debug_invalid1 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBU"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(0) == *debug_invalid1);

    LevelPtr debug_invalid2 = XDebugLevel::toLevelLS(LOG4CXX_STR("EBU"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(0) == *debug_invalid2);

    LevelPtr debug_invalid3 = XDebugLevel::toLevelLS(LOG4CXX_STR(""));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(0) == *debug_invalid3);

    LevelPtr debug_invalid4 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUGTEN"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(0) == *debug_invalid4);

    LevelPtr debug_invalid5 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG105"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(MAX_DEBUG_LEVEL) ==
        *debug_invalid5);

    LevelPtr debug_invalid6 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG-7"));
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(MIN_DEBUG_LEVEL) ==
        *debug_invalid6);
}


// Creation of a level from a string - should return the default level
// if outside the range.

TEST_F(XDebugLevelTest, FromStringTwoArg) {

    // Check that a valid debug levels are as expected
    LevelPtr debug85 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG85"),
            Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(85) == *debug85);

    LevelPtr debug92 = XDebugLevel::toLevelLS(LOG4CXX_STR("debug92"),
            Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(92) == *debug92);

    LevelPtr debug27 = XDebugLevel::toLevelLS(LOG4CXX_STR("Debug27"),
            Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(27) == *debug27);

    LevelPtr debug0 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG"),
            Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(0) == *debug0);

    // ... and that an invalid one returns an object of type debug (which is
    // the equivalent of a debug level 0 object).
    LevelPtr debug_invalid1 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBU"),
            Level::getFatal());
    EXPECT_TRUE(*Level::getFatal() == *debug_invalid1);

    LevelPtr debug_invalid2 = XDebugLevel::toLevelLS(LOG4CXX_STR("EBU"),
            Level::getFatal());
    EXPECT_TRUE(*Level::getFatal() == *debug_invalid2);

    LevelPtr debug_invalid3 = XDebugLevel::toLevelLS(LOG4CXX_STR(""),
            Level::getFatal());
    EXPECT_TRUE(*Level::getFatal() == *debug_invalid3);

    LevelPtr debug_invalid4 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUGTEN"),
            Level::getFatal());
    EXPECT_TRUE(*Level::getFatal() == *debug_invalid4);

    LevelPtr debug_invalid5 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG105"),
            Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(MAX_DEBUG_LEVEL) ==
        *debug_invalid5);

    LevelPtr debug_invalid6 = XDebugLevel::toLevelLS(LOG4CXX_STR("DEBUG-7"),
            Level::getFatal());
    EXPECT_TRUE(*XDebugLevel::getExtendedDebug(MIN_DEBUG_LEVEL) ==
        *debug_invalid6);
}
