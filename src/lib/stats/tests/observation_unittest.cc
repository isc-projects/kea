// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stats/observation.h>
#include <exceptions/exceptions.h>
#include <util/chrono_time_utils.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <unistd.h>

using namespace isc;
using namespace isc::stats;
using namespace std::chrono;

namespace {

static const StatsDuration& dur1234(hours(1) + minutes(2) + seconds(3) +
                                    milliseconds(4));
static const StatsDuration& dur5678(hours(5) + minutes(6) + seconds(7) +
                                    milliseconds(8));
static const StatsDuration& dur681012(hours(6) + minutes(8) + seconds(10) +
                                      milliseconds(12));
static const StatsDuration& dur453(minutes(4) + seconds(5) + milliseconds(3));

// This test verifies that the number of seconds can be retrieved.
TEST(StatsDurationTest, toSeconds) {
    StatsDuration dur = StatsDuration::zero();
    dur += hours(1) + minutes(1) + seconds(1) + milliseconds(1);
    EXPECT_EQ(3661, toSeconds(dur));
}

/// @brief Test class for Observation
///
/// This simple fixture class initializes four observations:
/// a (integer), b (float), c(time duration) and d (string).
class ObservationTest : public ::testing::Test {
public:

    /// @brief Constructor
    /// Initializes four observations.
    ObservationTest() :
        a("alpha", static_cast<int64_t>(1234)), // integer
        b("beta", 12.34), // float
        c("gamma", dur1234), // duration
        d("delta", "1234") { // string
    }

    Observation a;
    Observation b;
    Observation c;
    Observation d;
};

// Basic tests for the Observation constructors. This test checks whether
// parameters passed to the constructor initialize the object properly.
TEST_F(ObservationTest, constructor) {
    EXPECT_EQ(Observation::STAT_INTEGER, a.getType());
    EXPECT_EQ(Observation::STAT_FLOAT, b.getType());
    EXPECT_EQ(Observation::STAT_DURATION, c.getType());
    EXPECT_EQ(Observation::STAT_STRING, d.getType());

    EXPECT_EQ(1234, a.getInteger().first);
    EXPECT_EQ(12.34, b.getFloat().first);
    EXPECT_EQ(dur1234, c.getDuration().first);
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
    EXPECT_NO_THROW(c.setValue(dur5678));
    EXPECT_NO_THROW(d.setValue("fiveSixSevenEight"));


    EXPECT_EQ(5678, a.getInteger().first);
    EXPECT_EQ(56e+78, b.getFloat().first);
    EXPECT_EQ(dur5678, c.getDuration().first);
    EXPECT_EQ("fiveSixSevenEight", d.getString().first);

    // Now check whether setting value to a different type does
    // throw an exception
    EXPECT_THROW(a.setValue(56e+78), InvalidStatType);
    EXPECT_THROW(a.setValue(dur5678), InvalidStatType);
    EXPECT_THROW(a.setValue("fiveSixSevenEight"), InvalidStatType);

    EXPECT_THROW(b.setValue(static_cast<int64_t>(5678)), InvalidStatType);
    EXPECT_THROW(b.setValue(dur5678), InvalidStatType);
    EXPECT_THROW(b.setValue("fiveSixSevenEight"), InvalidStatType);

    EXPECT_THROW(c.setValue(static_cast<int64_t>(5678)), InvalidStatType);
    EXPECT_THROW(c.setValue(56e+78), InvalidStatType);
    EXPECT_THROW(c.setValue("fiveSixSevenEight"), InvalidStatType);

    EXPECT_THROW(d.setValue(static_cast<int64_t>(5678)), InvalidStatType);
    EXPECT_THROW(d.setValue(56e+78), InvalidStatType);
    EXPECT_THROW(d.setValue(dur5678), InvalidStatType);
}

// This test checks whether it is possible to add value to existing
// counter.
TEST_F(ObservationTest, addValue) {
    // Note: all Observations were set to 1234, 12.34 or similar in
    // ObservationTest constructor.

    EXPECT_NO_THROW(a.addValue(static_cast<int64_t>(5678)));
    EXPECT_NO_THROW(b.addValue(56.78));
    EXPECT_NO_THROW(c.addValue(dur5678));
    EXPECT_NO_THROW(d.addValue("fiveSixSevenEight"));

    EXPECT_EQ(6912, a.getInteger().first);
    EXPECT_EQ(69.12, b.getFloat().first);
    EXPECT_EQ(dur681012, c.getDuration().first);
    EXPECT_EQ("1234fiveSixSevenEight", d.getString().first);

    ASSERT_EQ(a.getSize(), 2);
    ASSERT_EQ(b.getSize(), 2);
    ASSERT_EQ(c.getSize(), 2);
    ASSERT_EQ(d.getSize(), 2);
}

// This test checks if collecting more than one sample
// works well.
TEST_F(ObservationTest, moreThanOne) {
    // Arrays of 4 types of samples
    int64_t int_samples[3] = {1234, 6912, 5678};
    double float_samples[3] = {12.34, 69.12, 56e+78};
    StatsDuration duration_samples[3] = {dur1234,
        dur681012, dur5678};
    std::string string_samples[3] = {"1234", "1234fiveSixSevenEight", "fiveSixSevenEight"};

    EXPECT_NO_THROW(a.addValue(static_cast<int64_t>(5678)));
    EXPECT_NO_THROW(b.addValue(56.78));
    EXPECT_NO_THROW(c.addValue(dur5678));
    EXPECT_NO_THROW(d.addValue("fiveSixSevenEight"));

    EXPECT_NO_THROW(a.setValue(static_cast<int64_t>(5678)));
    EXPECT_NO_THROW(b.setValue(56e+78));
    EXPECT_NO_THROW(c.setValue(dur5678));
    EXPECT_NO_THROW(d.setValue("fiveSixSevenEight"));

    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(b.getSize(), 3);
    ASSERT_EQ(c.getSize(), 3);
    ASSERT_EQ(d.getSize(), 3);

    ASSERT_NO_THROW(a.getIntegers());
    ASSERT_NO_THROW(b.getFloats());
    ASSERT_NO_THROW(c.getDurations());
    ASSERT_NO_THROW(d.getStrings());

    std::list<IntegerSample> samples_int = a.getIntegers(); // List of all integer samples
    std::list<FloatSample> samples_float = b.getFloats(); // List of all float samples
    std::list<DurationSample> samples_dur = c.getDurations(); // List of all duration samples
    std::list<StringSample> samples_str = d.getStrings(); // List of all string samples

    uint32_t i = 2; // Index pointed to the end of array of samples

    for (std::list<IntegerSample>::iterator it = samples_int.begin(); it != samples_int.end(); ++it) {
        EXPECT_EQ(int_samples[i], static_cast<int64_t>((*it).first));
        --i;
    }
    i = 2;
    for (std::list<FloatSample>::iterator it = samples_float.begin(); it != samples_float.end(); ++it) {
        EXPECT_EQ(float_samples[i], (*it).first);
        --i;
    }
    i = 2;
    for (std::list<DurationSample>::iterator it = samples_dur.begin(); it != samples_dur.end(); ++it) {
        EXPECT_EQ(duration_samples[i], (*it).first);
        --i;
    }
    i = 2;
    for (std::list<StringSample>::iterator it = samples_str.begin(); it != samples_str.end(); ++it) {
        EXPECT_EQ(string_samples[i], (*it).first);
        --i;
    }
}

// This test checks whether the size of storage
// is equal to the true value
TEST_F(ObservationTest, getSize) {
    // Check if size of storages is equal to 1
    ASSERT_EQ(a.getSize(), 1);
    ASSERT_EQ(b.getSize(), 1);
    ASSERT_EQ(c.getSize(), 1);
    ASSERT_EQ(d.getSize(), 1);

    a.addValue(static_cast<int64_t>(5678));
    b.addValue(56.78);
    c.addValue(dur5678);
    d.addValue("fiveSixSevenEight");

    EXPECT_NO_THROW(a.getSize());
    EXPECT_NO_THROW(b.getSize());
    EXPECT_NO_THROW(c.getSize());
    EXPECT_NO_THROW(d.getSize());

    // Check if size of storages is equal to 2
    ASSERT_EQ(a.getSize(), 2);
    ASSERT_EQ(b.getSize(), 2);
    ASSERT_EQ(c.getSize(), 2);
    ASSERT_EQ(d.getSize(), 2);

    a.setValue(static_cast<int64_t>(5678));
    b.setValue(56e+78);
    c.setValue(dur5678);
    d.setValue("fiveSixSevenEight");

    EXPECT_NO_THROW(a.getSize());
    EXPECT_NO_THROW(b.getSize());
    EXPECT_NO_THROW(c.getSize());
    EXPECT_NO_THROW(d.getSize());

    // Check if size of storages is equal to 3
    ASSERT_EQ(a.getSize(), 3);
    ASSERT_EQ(b.getSize(), 3);
    ASSERT_EQ(c.getSize(), 3);
    ASSERT_EQ(d.getSize(), 3);
}

// Checks whether setting amount limits works properly
TEST_F(ObservationTest, setCountLimit) {
    // Preparing of 21 test's samples for each type of storage
    int64_t int_samples[22] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
            14, 15, 16, 17, 18, 19, 20, 21};
    double float_samples[22] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0,
            20.0, 21.0};
    std::string string_samples[22] = {"a", "b", "c", "d", "e", "f", "g", "h",
            "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u",
            "v"};
    StatsDuration duration_samples[22];

    for (uint32_t i = 0; i < 22; ++i) {
        duration_samples[i] = milliseconds(i);
    }

    // By default the max_sample_count is set to 20 and max_sample_age
    // is deactivated
    // Adding 21 samples to each type of Observation
    for (uint32_t i = 0; i < 21; ++i) {
        a.setValue(int_samples[i]);
    }
    for (uint32_t i = 0; i < 21; ++i) {
        b.setValue(float_samples[i]);
    }
    for (uint32_t i = 0; i < 21; ++i) {
        c.setValue(duration_samples[i]);
    }
    for (uint32_t i = 0; i < 21; ++i) {
        d.setValue(string_samples[i]);
    }

    // Getting all 4 types of samples after inserting 21 values
    std::list<IntegerSample> samples_int = a.getIntegers();
    std::list<FloatSample> samples_float = b.getFloats();
    std::list<DurationSample> samples_duration = c.getDurations();
    std::list<StringSample> samples_string = d.getStrings();

    // Check if size of storages is equal to 20
    ASSERT_EQ(a.getSize(), 20);
    ASSERT_EQ(b.getSize(), 20);
    ASSERT_EQ(c.getSize(), 20);
    ASSERT_EQ(d.getSize(), 20);

    // And whether stored values are correct
    uint32_t i = 20; // index of the last element in array of test's samples
    for (std::list<IntegerSample>::iterator it = samples_int.begin(); it != samples_int.end(); ++it) {
        EXPECT_EQ((*it).first, int_samples[i]);
        --i;
    }
    i = 20; // index of last element in array of test's samples
    for (std::list<FloatSample>::iterator it = samples_float.begin(); it != samples_float.end(); ++it) {
        EXPECT_EQ((*it).first, float_samples[i]);
        --i;
    }
    i = 20; // index of last element in array of test's samples
    for (std::list<DurationSample>::iterator it = samples_duration.begin(); it != samples_duration.end(); ++it) {
        EXPECT_EQ((*it).first, duration_samples[i]);
        --i;
    }
    i = 20; // index of last element in array of test's samples
    for (std::list<StringSample>::iterator it = samples_string.begin(); it != samples_string.end(); ++it) {
        EXPECT_EQ((*it).first, string_samples[i]);
        --i;
    }

    // Change size of storage to smaller one
    ASSERT_NO_THROW(a.setMaxSampleCount(10));
    ASSERT_NO_THROW(b.setMaxSampleCount(10));
    ASSERT_NO_THROW(c.setMaxSampleCount(10));
    ASSERT_NO_THROW(d.setMaxSampleCount(10));

    samples_int = a.getIntegers();
    samples_float = b.getFloats();
    samples_duration = c.getDurations();
    samples_string = d.getStrings();

    // Check if size of storages is equal to 10
    ASSERT_EQ(a.getSize(), 10);
    ASSERT_EQ(b.getSize(), 10);
    ASSERT_EQ(c.getSize(), 10);
    ASSERT_EQ(d.getSize(), 10);

    // And whether storages contain only the 10 newest values
    i = 20; // index of last element in array of test's samples
    for (std::list<IntegerSample>::iterator it = samples_int.begin(); it != samples_int.end(); ++it) {
        EXPECT_EQ((*it).first, int_samples[i]);
        --i;
    }
    i = 20; // index of last element in array of test's samples
    for (std::list<FloatSample>::iterator it = samples_float.begin(); it != samples_float.end(); ++it) {
        EXPECT_EQ((*it).first, float_samples[i]);
        --i;
    }
    i = 20; // index of last element in array of test's samples
    for (std::list<DurationSample>::iterator it = samples_duration.begin(); it != samples_duration.end(); ++it) {
        EXPECT_EQ((*it).first, duration_samples[i]);
        --i;
    }
    i = 20; // index of last element in array of test's samples
    for (std::list<StringSample>::iterator it = samples_string.begin(); it != samples_string.end(); ++it) {
        EXPECT_EQ((*it).first, string_samples[i]);
        --i;
    }

    // Resize max_sample_count to greater
    ASSERT_NO_THROW(a.setMaxSampleCount(50));
    ASSERT_NO_THROW(b.setMaxSampleCount(50));
    ASSERT_NO_THROW(c.setMaxSampleCount(50));
    ASSERT_NO_THROW(d.setMaxSampleCount(50));

    // Check if size of storages did not change without adding new value
    ASSERT_EQ(a.getSize(), 10);
    ASSERT_EQ(b.getSize(), 10);
    ASSERT_EQ(c.getSize(), 10);
    ASSERT_EQ(d.getSize(), 10);

    // Add new values to each type of Observation
    a.setValue(static_cast<int64_t>(21));
    b.setValue(21.0);
    c.setValue(milliseconds(21));
    d.setValue("v");

    samples_int = a.getIntegers();
    samples_float = b.getFloats();
    samples_duration = c.getDurations();
    samples_string = d.getStrings();

    ASSERT_EQ(a.getSize(), 11);
    ASSERT_EQ(b.getSize(), 11);
    ASSERT_EQ(c.getSize(), 11);
    ASSERT_EQ(d.getSize(), 11);

    i = 21; // index of last element in array of test's samples
    for (std::list<IntegerSample>::iterator it = samples_int.begin(); it != samples_int.end(); ++it) {
        EXPECT_EQ((*it).first, int_samples[i]);
        --i;
    }
    i = 21; // index of last element in array of test's samples
    for (std::list<FloatSample>::iterator it = samples_float.begin(); it != samples_float.end(); ++it) {
        EXPECT_EQ((*it).first, float_samples[i]);
        --i;
    }
    i = 21; // index of last element in array of test's samples
    for (std::list<DurationSample>::iterator it = samples_duration.begin(); it != samples_duration.end(); ++it) {
        EXPECT_EQ((*it).first, duration_samples[i]);
        --i;
    }
    i = 21; // index of last element in array of test's samples
    for (std::list<StringSample>::iterator it = samples_string.begin(); it != samples_string.end(); ++it) {
        EXPECT_EQ((*it).first, string_samples[i]);
        --i;
    }

}

// Checks whether setting age limits works properly
TEST_F(ObservationTest, setAgeLimit) {
    // Set max_sample_age to 1 second
    ASSERT_NO_THROW(c.setMaxSampleAge(seconds(1)));
    // Add some value
    c.setValue(milliseconds(5));
    // Wait 1 second
    sleep(1);
    // and add new value
    c.setValue(milliseconds(3));

    // get the list of all samples
    std::list<DurationSample> samples_duration = c.getDurations();
    // check whether the size of samples is equal to 1
    ASSERT_EQ(c.getSize(), 1);
    // and whether it contains an expected value
    EXPECT_EQ((*samples_duration.begin()).first, milliseconds(3));

    // Wait 1 second to ensure removing previously set value
    sleep(1);
    // add 10 new values
    for (uint32_t i = 0; i < 10; ++i) {
        c.setValue(milliseconds(i));
    }
    // change the max_sample_age to smaller
    ASSERT_NO_THROW(c.setMaxSampleAge(milliseconds(300)));

    samples_duration = c.getDurations();
    // check whether the size of samples is equal to 10
    ASSERT_EQ(c.getSize(), 10);

    // and whether it contains expected values
    uint32_t i = 9;
    for (std::list<DurationSample>::iterator it = samples_duration.begin(); it != samples_duration.end(); ++it) {
        EXPECT_EQ((*it).first, milliseconds(i));
        --i;
    }
}

// Test checks whether we can get max_sample_age_ and max_sample_count_
// properly.
TEST_F(ObservationTest, getLimits) {
    // First checks whether getting default values works properly
    EXPECT_EQ(a.getMaxSampleAge().first, false);
    EXPECT_EQ(b.getMaxSampleAge().first, false);
    EXPECT_EQ(c.getMaxSampleAge().first, false);
    EXPECT_EQ(d.getMaxSampleAge().first, false);

    EXPECT_EQ(a.getMaxSampleCount().first, true);
    EXPECT_EQ(b.getMaxSampleCount().first, true);
    EXPECT_EQ(c.getMaxSampleCount().first, true);
    EXPECT_EQ(d.getMaxSampleCount().first, true);

    EXPECT_EQ(a.getMaxSampleCount().second, 20);
    EXPECT_EQ(b.getMaxSampleCount().second, 20);
    EXPECT_EQ(c.getMaxSampleCount().second, 20);
    EXPECT_EQ(d.getMaxSampleCount().second, 20);

    // change limit to time duration
    ASSERT_NO_THROW(a.setMaxSampleAge(dur453));
    ASSERT_NO_THROW(b.setMaxSampleAge(dur453));
    ASSERT_NO_THROW(c.setMaxSampleAge(dur453));
    ASSERT_NO_THROW(d.setMaxSampleAge(dur453));

    EXPECT_EQ(a.getMaxSampleAge().first, true);
    EXPECT_EQ(b.getMaxSampleAge().first, true);
    EXPECT_EQ(c.getMaxSampleAge().first, true);
    EXPECT_EQ(d.getMaxSampleAge().first, true);

    EXPECT_EQ(a.getMaxSampleAge().second, dur453);
    EXPECT_EQ(b.getMaxSampleAge().second, dur453);
    EXPECT_EQ(c.getMaxSampleAge().second, dur453);
    EXPECT_EQ(d.getMaxSampleAge().second, dur453);

    EXPECT_EQ(a.getMaxSampleCount().first, false);
    EXPECT_EQ(b.getMaxSampleCount().first, false);
    EXPECT_EQ(c.getMaxSampleCount().first, false);
    EXPECT_EQ(d.getMaxSampleCount().first, false);

    EXPECT_EQ(a.getMaxSampleCount().second, 20);
    EXPECT_EQ(b.getMaxSampleCount().second, 20);
    EXPECT_EQ(c.getMaxSampleCount().second, 20);
    EXPECT_EQ(d.getMaxSampleCount().second, 20);
}

// limit defaults are tested with StatsMgr.

// Test checks whether timing is reported properly.
TEST_F(ObservationTest, timers) {
    auto before = SampleClock::now();
    b.setValue(123.0); // Set it to a random value and record the time.

    // Allow a bit of imprecision. This test allows 500ms. That should be ok,
    // when running on virtual machines.
    auto after = before + milliseconds(500);

    // Now wait some time. We want to confirm that the timestamp recorded is the
    // time the observation took place, not current time.
    sleep(1);

    FloatSample sample = b.getFloat();

    // Let's check that the timestamp is within (before, after) range:
    // before < sample-time < after
    EXPECT_TRUE(before <= sample.second);
    EXPECT_TRUE(sample.second <= after);
}

// Checks whether an integer statistic can generate proper JSON structures.
// See https://gitlab.isc.org/isc-projects/kea/wikis/designs/Stats-design
/// for details.
TEST_F(ObservationTest, integerToJSON) {
    // String which contains first added sample
    std::string first_sample = ", [ 1234, \"" +
        isc::util::clockToText(a.getInteger().second) + "\" ] ]";

    a.setValue(static_cast<int64_t>(1234));

    std::string exp = "[ [ 1234, \"" +
        isc::util::clockToText(a.getInteger().second) + "\" ]" + first_sample;

    std::cout << a.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, a.getJSON()->str());
}

// Checks whether a floating point statistic can generate proper JSON
// structures. See
/// https://gitlab.isc.org/isc-projects/kea/wikis/designs/Stats-design
/// for details.
TEST_F(ObservationTest, floatToJSON) {
    // String which contains first added sample
    std::string first_sample = ", [ 12.34, \"" +
        isc::util::clockToText(b.getFloat().second) + "\" ] ]";

    // Let's use a value that converts easily to floating point.
    // No need to deal with infinite fractions in binary systems.

    b.setValue(1234.5);

    std::string exp = "[ [ 1234.5, \"" +
        isc::util::clockToText(b.getFloat().second) + "\" ]" + first_sample;

    std::cout << b.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, b.getJSON()->str());
}

// Checks whether a time duration statistic can generate proper JSON structures.
// See https://gitlab.isc.org/isc-projects/kea/wikis/designs/Stats-design for
// details.
TEST_F(ObservationTest, durationToJSON) {
    // String which contains first added sample
    std::string first_sample = ", [ \"01:02:03.004000\", \"" +
        isc::util::clockToText(c.getDuration().second) + "\" ] ]";

    // 1 hour 2 minutes 3 seconds and 4 milliseconds
    c.setValue(dur1234);

    std::string exp = "[ [ \"01:02:03.004000\", \"" +
        isc::util::clockToText(c.getDuration().second) + "\" ]" + first_sample;

    std::cout << c.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, c.getJSON()->str());
}

// Checks whether a string statistic can generate proper JSON structures.
// See https://gitlab.isc.org/isc-projects/kea/wikis/designs/Stats-design
// for details.
TEST_F(ObservationTest, stringToJSON) {
    // String which contains first added sample
    std::string first_sample = ", [ \"1234\", \"" +
        isc::util::clockToText(d.getString().second) + "\" ] ]";

    d.setValue("Lorem ipsum dolor sit amet");

    std::string exp = "[ [ \"Lorem ipsum dolor sit amet\", \"" +
        isc::util::clockToText(d.getString().second) + "\" ]" + first_sample;

    std::cout << d.getJSON()->str() << std::endl;
    EXPECT_EQ(exp, d.getJSON()->str());
}

// Checks whether reset() resets the statistics properly.
TEST_F(ObservationTest, reset) {
    EXPECT_NO_THROW(a.addValue(static_cast<int64_t>(5678)));
    EXPECT_NO_THROW(b.addValue(56.78));
    EXPECT_NO_THROW(c.addValue(dur5678));
    EXPECT_NO_THROW(d.addValue("fiveSixSevenEight"));

    a.reset(); // integer
    b.reset(); // float
    c.reset(); // duration
    d.reset(); // string

    EXPECT_EQ(0, a.getInteger().first);
    EXPECT_EQ(0.0, b.getFloat().first);
    EXPECT_EQ(StatsDuration::zero(), c.getDuration().first);
    EXPECT_EQ("", d.getString().first);

    ASSERT_EQ(a.getSize(), 1);
    ASSERT_EQ(b.getSize(), 1);
    ASSERT_EQ(c.getSize(), 1);
    ASSERT_EQ(d.getSize(), 1);
}

// Checks whether an observation can keep its name.
TEST_F(ObservationTest, names) {
    EXPECT_EQ("alpha", a.getName());
    EXPECT_EQ("beta", b.getName());
    EXPECT_EQ("gamma", c.getName());
    EXPECT_EQ("delta", d.getName());
}

}
