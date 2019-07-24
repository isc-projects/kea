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

    std::string expected("1970-01-01 00:00:00");
    std::string sepoch;
    for (int precision = 0; precision <= DEFAULT_FRAC_SECS; ++precision) {
        if (precision == 1) {
            expected.push_back('.');
        }

        if (precision >= 1) {
            expected.push_back('0');
        }

        sepoch = ptimeToText(pepoch, precision);
        EXPECT_EQ(expected, sepoch) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    sepoch = ptimeToText(pepoch);
    EXPECT_EQ(expected, sepoch);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    sepoch = ptimeToText(pepoch, DEFAULT_FRAC_SECS + 1);
    EXPECT_EQ(expected, sepoch);

}

// The 2015 Bastille day
TEST(BoostTimeUtilsTest, bastilleDay) {
    time_duration tdbast =
        hours(12) + minutes(13) + seconds(14) + milliseconds(500);
    ptime pbast(date(2015, Jul, 14), tdbast);

    std::string expected("2015-07-14 12:13:14");
    std::string sbast;
    for (int precision = 0; precision <= DEFAULT_FRAC_SECS; ++precision) {
        if (precision == 1) {
            expected.push_back('.');
            expected.push_back('5');
        } else if (precision > 1) {
            expected.push_back('0');
        }

        sbast = ptimeToText(pbast, precision);
        EXPECT_EQ(expected, sbast) << " test precision:" << precision;
    }

    // Expected string should have same precision as default, so
    // test the default.
    sbast = ptimeToText(pbast);
    EXPECT_EQ(expected, sbast);

    // Now test a requested precision beyond default.  We should
    // get the default precision.
    sbast = ptimeToText(pbast, DEFAULT_FRAC_SECS + 1);
    EXPECT_EQ(expected, sbast);
}
