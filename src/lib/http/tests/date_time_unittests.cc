// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/date_time.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace isc::http;

namespace {

/// @brief Test fixture class for @ref HttpDateTime.
class HttpDateTimeTest : public ::testing::Test {
public:

    /// @brief Checks time value against expected values.
    ///
    /// This method uses value of @ref date_time_ for the test.
    ///
    /// @param exp_day_of_week Expected day of week.
    /// @param exp_day Expected day of month.
    /// @param exp_month Expected month.
    /// @param exp_year Expected year.
    /// @param exp_hours Expected hour value.
    /// @param exp_minutes Expected minutes value.
    /// @param exp_seconds Expected seconds value.
    void testDateTime(const unsigned short exp_day_of_week,
                      const unsigned short exp_day,
                      const unsigned short exp_month,
                      const unsigned short exp_year,
                      const long exp_hours,
                      const long exp_minutes,
                      const long exp_seconds) {
        // Retrieve @c boost::posix_time::ptime value.
        ptime as_ptime = date_time_.getPtime();
        // Date is contained within this object.
        date date_part = as_ptime.date();

        // Verify weekday.
        greg_weekday day_of_week = date_part.day_of_week();
        EXPECT_EQ(exp_day_of_week, day_of_week.as_number());

        // Verify day of month.
        greg_day day = date_part.day();
        EXPECT_EQ(exp_day, day.as_number());

        // Verify month.
        greg_month month = date_part.month();
        EXPECT_EQ(exp_month, month.as_number());

        // Verify year.
        greg_year year = date_part.year();
        EXPECT_EQ(exp_year, static_cast<unsigned short>(year));

        // Retrieve time of the day and verify hour, minute and second.
        time_duration time_of_day = as_ptime.time_of_day();
        EXPECT_EQ(exp_hours, time_of_day.hours());
        EXPECT_EQ(exp_minutes, time_of_day.minutes());
        EXPECT_EQ(exp_seconds, time_of_day.seconds());
    }

    /// @brief Date/time value which should be set by the tests.
    HttpDateTime date_time_;

};

// Test formatting as specified in RFC 1123.
TEST_F(HttpDateTimeTest, rfc1123Format) {
    date gdate(greg_year(2002), greg_month(1), greg_day(20));
    time_duration tm(23, 59, 59, 0);
    ptime t = ptime(gdate, tm);
    HttpDateTime date_time(t);
    std::string formatted;
    ASSERT_NO_THROW(formatted = date_time.rfc1123Format());
    EXPECT_EQ("Sun, 20 Jan 2002 23:59:59 GMT", formatted);
}

// Test formatting as specified in RFC 850.
TEST_F(HttpDateTimeTest, rfc850Format) {
    date gdate(greg_year(1994), greg_month(8), greg_day(6));
    time_duration tm(11, 12, 13, 0);
    ptime t = ptime(gdate, tm);

    HttpDateTime date_time(t);
    std::string formatted;
    ASSERT_NO_THROW(formatted = date_time.rfc850Format());
    EXPECT_EQ("Saturday, 06-Aug-94 11:12:13 GMT", formatted);
}

// Test formatting as output of asctime().
TEST_F(HttpDateTimeTest, asctimeFormat) {
    date gdate(greg_year(1999), greg_month(11), greg_day(2));
    time_duration tm(03, 57, 12, 0);
    ptime t = ptime(gdate, tm);

    HttpDateTime date_time(t);
    std::string formatted;
    ASSERT_NO_THROW(formatted = date_time.asctimeFormat());
    EXPECT_EQ("Tue Nov  2 03:57:12 1999", formatted);
}

// Test parsing time in RFC 1123 format.
TEST_F(HttpDateTimeTest, fromRfc1123) {
    ASSERT_NO_THROW(
        date_time_ = HttpDateTime::fromRfc1123("Wed, 21 Dec 2016 18:53:45 GMT")
    );
    testDateTime(3, 21, 12, 2016, 18, 53, 45);
    EXPECT_THROW(HttpDateTime::fromRfc1123("Wed, 21 Dex 2016 18:53:45 GMT"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc1123("Wed, 43 Dec 2016 18:53:45 GMT"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc1123("Wed, 21 Dec 16 18:53:45 GMT"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc1123("Wed, 21 Dec 2016 18:53:45"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc1123("Wed, 21 Dec 2016 1853:45 GMT"),
                 HttpTimeConversionError);
}

// Test parsing time in RFC 850 format.
TEST_F(HttpDateTimeTest, fromRfc850) {
    ASSERT_NO_THROW(
        date_time_ = HttpDateTime::fromRfc850("Wednesday, 21-Dec-16 18:53:45 GMT");
    );
    testDateTime(3, 21, 12, 2016, 18, 53, 45);
    EXPECT_THROW(HttpDateTime::fromRfc850("Wednesday, 55-Dec-16 18:53:45 GMT"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc850("Wednesday, 21-Dex-16 18:53:45 GMT"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc850("Wednesday, 21-Dec-2016 18:53:45 GMT"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromRfc850("Wednesday, 21-Dec-16 1853:45 GMT"),
                 HttpTimeConversionError);
}

// Test parsing time in asctime() format.
TEST_F(HttpDateTimeTest, fromRfcAsctime) {
    ASSERT_NO_THROW(
        date_time_ = HttpDateTime::fromAsctime("Wed Dec 21 08:49:37 2016");
    );
    testDateTime(3, 21, 12, 2016, 8, 49, 37);
    EXPECT_THROW(HttpDateTime::fromAsctime("Wed Dex 21 08:49:37 2016"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromAsctime("Wed Dec 55 08:49:37 2016"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromAsctime("Wed Dec 21 08:49:37 16"),
                 HttpTimeConversionError);
    EXPECT_THROW(HttpDateTime::fromAsctime("Wed Dec 21 08:4937 2016"),
                 HttpTimeConversionError);
}

// Test parsing time in RFC 1123 format using HttpDateTime::fromAny().
TEST_F(HttpDateTimeTest, fromAnyRfc1123) {
    ASSERT_NO_THROW(
        date_time_ = HttpDateTime::fromAny("Thu, 05 Jan 2017 09:15:06 GMT");
    );
    testDateTime(4, 5, 1, 2017, 9, 15, 06);
}

// Test parsing time in RFC 850 format using HttpDateTime::fromAny().
TEST_F(HttpDateTimeTest, fromAnyRfc850) {
    ASSERT_NO_THROW(
        date_time_ = HttpDateTime::fromAny("Saturday, 18-Feb-17 01:02:10 GMT");
    );
    testDateTime(6, 18, 2, 2017, 1, 2, 10);
}

// Test parsing time in asctime() format using HttpDateTime::fromAny().
TEST_F(HttpDateTimeTest, fromAnyAsctime) {
    ASSERT_NO_THROW(
        date_time_ = HttpDateTime::fromAny("Wed Mar  1 15:45:07 2017 GMT");
    );
    testDateTime(3, 1, 3, 2017, 15, 45, 7);
}

// Test that HttpDateTime::fromAny throws exception if unsupported format is
// used.
TEST_F(HttpDateTimeTest, fromAnyInvalidFormat) {
    EXPECT_THROW(HttpDateTime::fromAsctime("20020131T235959"),
                 HttpTimeConversionError);
}

}
