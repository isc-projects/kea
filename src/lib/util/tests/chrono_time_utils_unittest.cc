// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/chrono_time_utils.h>

#include <string.h>
#include <time.h>

#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace isc::util;

/// Check the clockToText() function returns a numeric month.
TEST(ChronoTimeUtilsTest, epoch) {
    // The system clock is a wall clock using the local time zone so
    // the epoch is zero only at some places or of course if the
    // system is in UTC...
    struct tm epoch;
    memset(&epoch, 0, sizeof(epoch));
    epoch.tm_year = 70;
    epoch.tm_mday = 1;
    epoch.tm_isdst = -1;
    time_t tepoch = mktime(&epoch);
    system_clock::time_point pepoch = system_clock::from_time_t(tepoch);

    // We're going to loop through precision values starting with 0 through
    // the max supported precision.  Each pass should after the first, should
    // add an additional level of precision: secs, secs/10, secs/100,
    // secs/1000 and so on.  The initial string has no fraction seconds.
    std::string expected("1970-01-01 00:00:00");
    std::string sepoch;
    for (int precision = 0; precision <= MAX_FSECS_PRECISION; ++precision) {
        if (precision == 1) {
            // Adding fractional seconds so we need append a decimal point.
            expected.push_back('.');
        }

        if (precision >= 1) {
            // Adding an additional level of precision, append a zero.
            expected.push_back('0');
        }

        // Now let's see if we get the correct precision in the text.
        sepoch = clockToText(pepoch, precision);
        EXPECT_EQ(expected, sepoch) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    sepoch = clockToText(pepoch);
    EXPECT_EQ(expected, sepoch);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    sepoch = clockToText(pepoch, MAX_FSECS_PRECISION + 1);
    EXPECT_EQ(expected, sepoch);

}

/// Check the durationToText() works as expected.
/// Note durationToText() is not called by clockToText().
TEST(ChronoTimeUtilsTest, duration) {
    system_clock::duration p123 = hours(1) + minutes(2) + seconds(3);

    // We're going to loop through precision values starting with 0 through
    // the max supported precision.  Each pass should after the first, should
    // add an additional level of precision: secs, secs/10, secs/100,
    // secs/1000 and so on.  The initial string has no fraction seconds.
    std::string expected("01:02:03");
    std::string s123;
    for (int precision = 0; precision <= MAX_FSECS_PRECISION; ++precision) {
        if (precision == 1) {
            // Adding fractional seconds so we need append a decimal point.
            expected.push_back('.');
        }

        if (precision >= 1) {
            // Adding an additional level of precision, append a zero.
            expected.push_back('0');
        }

        // Now let's see if we get the correct precision in the text.
        s123 = durationToText(p123, precision);
        EXPECT_EQ(expected, s123) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    s123 = durationToText(p123);
    EXPECT_EQ(expected, s123);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    s123 = durationToText(p123, MAX_FSECS_PRECISION + 1);
    EXPECT_EQ(expected, s123);
}

// The 2015 Bastille day
TEST(ChronoTimeUtilsTest, bastilleDay) {
    struct tm tm;
    tm.tm_year = 2015 - 1900;
    tm.tm_mon = 7 - 1;
    tm.tm_mday = 14;
    tm.tm_hour = 12;
    tm.tm_min = 13;
    tm.tm_sec = 14;
    tm.tm_isdst = -1;
    time_t tbast = mktime(&tm);
    system_clock::time_point tpbast = system_clock::from_time_t(tbast);
    tpbast += milliseconds(500);

    // We're going to loop through precision values starting with 0 through
    // the max supported precision.  Each pass should after the first, should
    // add an additional level of precision: secs, secs/10, secs/100,
    // secs/1000 and so on.  The initial string has no fraction seconds.
    std::string expected("2015-07-14 12:13:14");
    std::string sbast;
    for (int precision = 0; precision <= MAX_FSECS_PRECISION; ++precision) {
        if (precision == 1) {
            // Adding fractional seconds so we need append a decimal point
            // and the digit 5 (i.e. 500 ms = .5 secs).
            expected.push_back('.');
            expected.push_back('5');
        } else if (precision > 1) {
            // Adding an additional level of precision, append a zero.
            expected.push_back('0');
        }

        // Now let's see if we get the correct precision in the text.
        sbast = clockToText(tpbast, precision);
        EXPECT_EQ(expected, sbast) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    sbast = clockToText(tpbast);
    EXPECT_EQ(expected, sbast);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    sbast = clockToText(tpbast, MAX_FSECS_PRECISION + 1);
    EXPECT_EQ(expected, sbast);
}

// Try steady clock duration.
TEST(ChronoTimeUtilsTest, steadyClock) {
    steady_clock::duration p12345 = hours(1) + minutes(2) + seconds(3) +
        milliseconds(4) + microseconds(5);
    std::string expected("01:02:03.004005");
    std::string s12345 = durationToText(p12345, 6);
    EXPECT_EQ(expected, s12345);
}
