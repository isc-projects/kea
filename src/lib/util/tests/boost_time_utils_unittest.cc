// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
    string sepoch = ptimeToText(pepoch);
    EXPECT_EQ("1970-01-01 00:00:00.000", sepoch.substr(0, 23));
}

// The 2015 Bastille day
TEST(BoostTimeUtilsTest, bastilleDay) {
    time_duration tdbast =
	hours(12) + minutes(13) + seconds(14) + milliseconds(500);
    ptime pbast(date(2015, Jul, 14), tdbast);
    string sbast = ptimeToText(pbast);
    EXPECT_EQ("2015-07-14 12:13:14.500", sbast.substr(0, 23));
}
