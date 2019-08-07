// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/boost_time_utils.h>

#include <string.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::util;
using namespace boost::posix_time;
using namespace boost::gregorian;

/// Check the ptimeToText() function returns a numeric month.
/// Note durationToText() is called by ptimeToText() so is tested too.

// The Posix time epoch is 1970
TEST(BoostTimeUtilsTest, epoch) {
    time_t tepoch = 0;
    ptime pepoch = from_time_t(tepoch);

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
        sepoch = ptimeToText(pepoch, precision);
        EXPECT_EQ(expected, sepoch) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    sepoch = ptimeToText(pepoch);
    EXPECT_EQ(expected, sepoch);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    sepoch = ptimeToText(pepoch, MAX_FSECS_PRECISION + 1);
    EXPECT_EQ(expected, sepoch);

}

// The 2015 Bastille day
TEST(BoostTimeUtilsTest, bastilleDay) {
    time_duration tdbast =
        hours(12) + minutes(13) + seconds(14) + milliseconds(500);
    ptime pbast(date(2015, Jul, 14), tdbast);

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
        sbast = ptimeToText(pbast, precision);
        EXPECT_EQ(expected, sbast) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    sbast = ptimeToText(pbast);
    EXPECT_EQ(expected, sbast);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    sbast = ptimeToText(pbast, MAX_FSECS_PRECISION + 1);
    EXPECT_EQ(expected, sbast);
}
