// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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
    EXPECT_TRUE(strncmp(sepoch.c_str(), "1970-01-01 00:00:00.000", 23) == 0);
}

// The 2015 Bastille day
TEST(BoostTimeUtilsTest, bastilleDay) {
    time_duration tdbast =
	hours(12) + minutes(13) + seconds(14) + milliseconds(500);
    ptime pbast(date(2015, Jul, 14), tdbast);
    string sbast = ptimeToText(pbast);
    EXPECT_TRUE(strncmp(sbast.c_str(), "2015-07-14 12:13:14.500", 23) == 0);
}
