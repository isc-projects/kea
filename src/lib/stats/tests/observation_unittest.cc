// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <stats/observation.h>
#include <exceptions/exceptions.h>
#include <util/boost_time_utils.h>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <unistd.h>

using namespace isc;
using namespace isc::stats;
using namespace boost::posix_time;

namespace {

/// @brief Test class for Observation
///
/// This simple fixture class initializes four observations:
/// a (integer), b (float), c(time duration) and d (string).
class ObservationTest : public ::testing::Test {
public:

    /// @brief Constructor
    /// Initializes four observations.
    ObservationTest()
        :a("alpha", static_cast<int64_t>(1234)), // integer
         b("beta", 12.34), // float
         c("gamma", millisec::time_duration(1,2,3,4)), // duration
         d("delta", "1234") { // string
    }

    Observation a;
    Observation b;
    Observation c;
    Observation d;
};

// Basic tests for the Obseration constructors. This test checks whether
// parameters passed to the constructor initialize the object properly.
TEST_F(ObservationTest, constructor) {

    EXPECT_EQ(Observation::STAT_INTEGER, a.getType());
    EXPECT_EQ(Observation::STAT_FLOAT, b.getType());
    EXPECT_EQ(Observation::STAT_DURATION, c.getType());
    EXPECT_EQ(Observation::STAT_STRING, d.getType());

    EXPECT_EQ(1234, a.getInteger().first);
    EXPECT_EQ(12.34, b.getFloat().first);
    EXPECT_EQ(millisec::time_duration(1,2,3,4),
              c.getDuration().first);
    EXPECT_EQ("1234", d.getString().first);

    // Let's check that attempting to get a different type
    // than used will cause an exception.
    EXPECT_THROW(a.getFloat(), InvalidStatType);
    EXPECT_THROW(a.getDuration(), InvalidStatType);
    EXPECT_THROW(a.getString(), InvalidStatType);

    EXPECT_THROW(b.getInteger(), InvalidStatType);
    EXPECT_THROW(b.getDuration(), InvalidStatType);
    EXPECT_THROW(b.getString(), InvalidStatType);

    EXPECT_THROW(c.getInteger(), InvalidStatType);
    EXPECT_THROW(c.getFloat(), InvalidStatType);
    EXPECT_THROW(c.getString(), InvalidStatType);

    EXPECT_THROW(d.getInteger(), InvalidStatType);
    EXPECT_THROW(d.getFloat(), InvalidStatType);
    EXPECT_THROW(d.getDuration(), InvalidStatType);
}

// This test checks whether it is possible to set to an absolute value for all
// given types.
TEST_F(ObservationTest, setValue) {

    EXPECT_NO_THROW(a.setValue(static_cast<int64_t>(5678)));
    EXPECT_NO_THROW(b.setValue(56e+78));
    EXPECT_NO_THROW(c.setValue(millisec::time_duration(5,6,7,8)));
    EXPECT_NO_THROW(d.setValue("fiveSixSevenEight"));


    EXPECT_EQ(5678, a.getInteger().first);
    EXPECT_EQ(56e+78, b.getFloat().first);
    EXPECT_EQ(millisec::time_duration(5,6,7,8),
              c.getDuration().first);
    EXPECT_EQ("fiveSixSevenEight", d.getString().first);

    // Now check whether setting value to a different type does
    // throw an exception
    EXPECT_THROW(a.setValue(56e+78), InvalidStatType);
    EXPECT_THROW(a.setValue(millisec::time_duration(5,6,7,8)), InvalidStatType);
    EXPECT_THROW(a.setValue("fiveSixSevenEight"), InvalidStatType);

    EXPECT_THROW(b.setValue(static_cast<int64_t>(5678)), InvalidStatType);
    EXPECT_THROW(b.setValue(millisec::time_duration(5,6,7,8)), InvalidStatType);
    EXPECT_THROW(b.setValue("fiveSixSevenEight"), InvalidStatType);

    EXPECT_THROW(c.setValue(static_cast<int64_t>(5678)), InvalidStatType);
    EXPECT_THROW(c.setValue(56e+78), InvalidStatType);
    EXPECT_THROW(c.setValue("fiveSixSevenEight"), InvalidStatType);

    EXPECT_THROW(d.setValue(static_cast<int64_t>(5678)), InvalidStatType);
    EXPECT_THROW(d.setValue(56e+78), InvalidStatType);
    EXPECT_THROW(d.setValue(millisec::time_duration(5,6,7,8)), InvalidStatType);
}

// This test checks whether it is possible to add value to existing
// counter.
TEST_F(ObservationTest, addValue) {

    // Note: all Observations were set to 1234,12.34 or similar in
    // ObservationTest constructor.

    EXPECT_NO_THROW(a.addValue(static_cast<int64_t>(5678)));
    EXPECT_NO_THROW(b.addValue(56.78));
    EXPECT_NO_THROW(c.addValue(millisec::time_duration(5,6,7,8)));
    EXPECT_NO_THROW(d.addValue("fiveSixSevenEight"));

    EXPECT_EQ(6912, a.getInteger().first);
    EXPECT_EQ(69.12, b.getFloat().first);

    EXPECT_EQ(millisec::time_duration(6,8,10,12), c.getDuration().first);
    EXPECT_EQ("1234fiveSixSevenEight", d.getString().first);
}

// Test checks whether timing is reported properly.
TEST_F(ObservationTest, timers) {
    ptime before = microsec_clock::local_time();
    b.setValue(123.0); // Set it to a random value and record the time.

    // Allow a bit of inprecision. This test allows 50ms. That should be ok,
    // when running on virtual machines.
    ptime after = before + millisec::time_duration(0,0,0,50);

    // Now wait some time. We want to confirm that the timestamp recorded is the
    // time the observation took place, not current time.
    sleep(1);

    FloatSample sample = b.getFloat();

    // Let's check that the timestamp is within (before,after) range:
    // before < sample-time < after
    EXPECT_TRUE(before <= sample.second);
    EXPECT_TRUE(sample.second <= after);
}

// Checks whether an integer statistic can generate proper JSON structures.
// See http://kea.isc.org/wiki/StatsDesign for details.
TEST_F(ObservationTest, integerToJSON) {

    a.setValue(static_cast<int64_t>(1234));

    std::string exp = "[ [ 1234, \""
        + isc::util::ptimeToText(a.getInteger().second) + "\" ] ]";

    std::cout << a.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, a.getJSON()->str());
}

// Checks whether a floating point statistic can generate proper JSON
// structures. See http://kea.isc.org/wiki/StatsDesign for details.
TEST_F(ObservationTest, floatToJSON) {

    // Let's use a value that converts easily to floating point.
    // No need to deal with infinite fractions in binary systems.
    b.setValue(1234.5);

    std::string exp = "[ [ 1234.5, \""
        + isc::util::ptimeToText(b.getFloat().second) + "\" ] ]";

    std::cout << b.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, b.getJSON()->str());
}

// Checks whether a time duration statistic can generate proper JSON structures.
// See http://kea.isc.org/wiki/StatsDesign for details.
TEST_F(ObservationTest, durationToJSON) {

    // 1 hour 2 minutes 3 seconds and 4 milliseconds
    c.setValue(time_duration(1,2,3,4));

    std::string exp = "[ [ \"01:02:03.000004\", \""
        + isc::util::ptimeToText(c.getDuration().second) + "\" ] ]";

    std::cout << c.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, c.getJSON()->str());
}

// Checks whether a string statistic can generate proper JSON structures.
// See http://kea.isc.org/wiki/StatsDesign for details.
TEST_F(ObservationTest, stringToJSON) {

    //
    d.setValue("Lorem ipsum dolor sit amet");

    std::string exp = "[ [ \"Lorem ipsum dolor sit amet\", \""
        + isc::util::ptimeToText(d.getString().second) + "\" ] ]";

    std::cout << d.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, d.getJSON()->str());
}

// Checks whether reset() resets the statistics properly.
TEST_F(ObservationTest, reset) {
    a.reset(); // integer
    b.reset(); // float
    c.reset(); // duration
    d.reset(); // string

    EXPECT_EQ(0, a.getInteger().first);
    EXPECT_EQ(0.0, b.getFloat().first);
    EXPECT_EQ(time_duration(0,0,0,0), c.getDuration().first);
    EXPECT_EQ("", d.getString().first);
}

// Checks whether an observation can keep its name.
TEST_F(ObservationTest, names) {
    EXPECT_EQ("alpha", a.getName());
    EXPECT_EQ("beta", b.getName());
    EXPECT_EQ("gamma", c.getName());
    EXPECT_EQ("delta", d.getName());
}

};
