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

#include <util/stopwatch.h>
#include <util/stopwatch_impl.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <unistd.h>

namespace {

using namespace isc;
using namespace isc::util;
using namespace boost::posix_time;

/// @brief @c StopwatchImpl mock object.
///
/// This class derives from the @c StopwatchImpl to override the
/// @c StopwatchImpl::getCurrentTime. This method is internally called by
/// the @c StopwatchImpl to determine the current time. By providing the
/// implementation of this method which returns the fixed (well known)
/// timestamp value we can obtain the deterministic values from the accessors
/// of this class.
///
/// This class also includes some convenience methods to return the time
/// durations in milliseconds.
class StopwatchMock : public StopwatchImpl {
public:

    /// @brief Constructor.
    ///
    /// @param ref_time Reference time, i.e. the arbitrary time value from
    /// which time is measured. The @c current_time_ value returned by the
    /// @c StopwatchMock::getCurrentTime is initialized to this value.
    /// Subsequent calls to the @c StopwatchMock::ffwd move the value of
    /// the @c current_time_ forward.
    StopwatchMock(const ptime& ref_time);

    /// @brief Fast forward time.
    ///
    /// Moves the value of the @c current_time_ forward by the specified
    /// number of milliseconds (microseconds). As a result the timestamp
    /// returned by the @c StopwatchMock::getCurrentTime moves by this value.
    /// This simulates the time progress.
    ///
    /// @param ms Specifies the number of milliseconds to move current time.
    /// @param us Specifies the number of fractional microseconds to move
    /// current time.
    void ffwd(const uint32_t ms, const uint32_t us = 0);

    /// @brief Returns the last duration in milliseconds.
    uint32_t getLastDurationInMs() const;

    /// @brief Returns the total duration in milliseconds.
    uint32_t getTotalDurationInMs() const;

protected:

    /// @brief Returs the current time.
    ///
    /// This method returns the fixed @c current_time_ timestamp.
    virtual ptime getCurrentTime() const;

private:

    /// @brief Holds the current time to be returned by the
    /// @c StopwatchMock::getCurrentTime.
    ptime current_time_;

};

StopwatchMock::StopwatchMock(const ptime& ref_time)
    : StopwatchImpl(), current_time_(ref_time) {
}

void
StopwatchMock::ffwd(const uint32_t ms, const uint32_t us) {
    current_time_ += milliseconds(ms);
    current_time_ += microseconds(us);
}

uint32_t
StopwatchMock::getLastDurationInMs() const {
    return (getLastDuration().total_milliseconds());
}

uint32_t
StopwatchMock::getTotalDurationInMs() const {
    return (getTotalDuration().total_milliseconds());
}

ptime
StopwatchMock::getCurrentTime() const {
    return (current_time_);
}

/// @brief Test fixture class for testing @c StopwatchImpl.
class StopwatchTest : public ::testing::Test {
protected:

    /// @brief Set up the test.
    ///
    /// Initializes the reference time to be used to create the instances
    /// of the @c StopwatchMock objects.
    virtual void SetUp();

    /// @brief Holds the reference time to be used to create the instances
    /// of the @c StopwatchMock objects.
    ptime ref_time_;
};

void
StopwatchTest::SetUp() {
    ref_time_ = microsec_clock::universal_time();
}

/// This test checks the behavior of the stopwatch when it is started
/// and stopped multiple times. It uses the StopwatchMock object to
/// control the "time flow" by setting the current time to arbitrary
/// values using the StopwatchMock::ffwd. In addition, this test
/// checks that the stopwatch can be reset.
TEST_F(StopwatchTest, multipleMeasurements) {
    StopwatchMock stopwatch(ref_time_);
    // The stopwatch shouldn't automatically start. The initial
    // durations should be set to 0.
    EXPECT_EQ(0, stopwatch.getLastDurationInMs());
    EXPECT_EQ(0, stopwatch.getTotalDurationInMs());

    stopwatch.start();

    // Even though the stopwatch is started, the time is still set to
    // the initial value. The durations should not be affected.
    EXPECT_EQ(0, stopwatch.getLastDurationInMs());
    EXPECT_EQ(0, stopwatch.getTotalDurationInMs());

    // Move the time by 10 ms.
    stopwatch.ffwd(10);

    // It should be possible to retrieve the durations even when the
    // stopwatch is running.
    EXPECT_EQ(10, stopwatch.getLastDurationInMs());
    EXPECT_EQ(10, stopwatch.getTotalDurationInMs());

    // Now stop it and make sure that the same values are returned.
    stopwatch.stop();

    EXPECT_EQ(10, stopwatch.getLastDurationInMs());
    EXPECT_EQ(10, stopwatch.getTotalDurationInMs());

    // Start it again, but don't move the time forward yet.
    stopwatch.start();

    // The new duration should be 0, but the total should be equal to
    // the previously measured duration.
    EXPECT_EQ(0, stopwatch.getLastDurationInMs());
    EXPECT_EQ(10, stopwatch.getTotalDurationInMs());

    // Move time by 5 ms.
    stopwatch.ffwd(5);

    // New measured duration should be 5 ms. The total should be 15 ms.
    EXPECT_EQ(5, stopwatch.getLastDurationInMs());
    EXPECT_EQ(15, stopwatch.getTotalDurationInMs());

    // Stop it again and make sure the values returned are the same.
    stopwatch.stop();

    EXPECT_EQ(5, stopwatch.getLastDurationInMs());
    EXPECT_EQ(15, stopwatch.getTotalDurationInMs());

    // Move the time forward while the stopwatch is stopped.
    stopwatch.ffwd(8);

    // The measured values should not be affected.
    EXPECT_EQ(5, stopwatch.getLastDurationInMs());
    EXPECT_EQ(15, stopwatch.getTotalDurationInMs());

    // Stop should be no-op in this case.
    stopwatch.stop();

    EXPECT_EQ(5, stopwatch.getLastDurationInMs());
    EXPECT_EQ(15, stopwatch.getTotalDurationInMs());

    // Start the stopwatch again.
    stopwatch.start();

    // Move time by 3 ms.
    stopwatch.ffwd(3);

    // Since the stopwatch is running, the measured duration should
    // get updated again.
    EXPECT_EQ(3, stopwatch.getLastDurationInMs());
    EXPECT_EQ(18, stopwatch.getTotalDurationInMs());

    // Move the time by 2 ms.
    stopwatch.ffwd(2);

    // Start should be no-op in this case.
    stopwatch.start();

    // But the durations should be updated.
    EXPECT_EQ(5, stopwatch.getLastDurationInMs());
    EXPECT_EQ(20, stopwatch.getTotalDurationInMs());

    // Make sure we can reset.
    stopwatch.reset();

    EXPECT_EQ(0, stopwatch.getLastDurationInMs());
    EXPECT_EQ(0, stopwatch.getTotalDurationInMs());
}

// This test checks that the stopwatch works when the real clock is in use.
TEST_F(StopwatchTest, realTime) {
    // Initially, the measured time should be 0.
    Stopwatch stopwatch;
    EXPECT_EQ(0, stopwatch.getLastMilliseconds());
    EXPECT_EQ(0, stopwatch.getTotalMilliseconds());

    // Start the stopwatch.
    stopwatch.start();

    // Sleep for 1 ms. The stopwatch should measure this duration.
    usleep(1000);

    stopwatch.stop();

    // The measured duration should be greater or equal 1 ms.
    long current_duration = stopwatch.getLastMilliseconds();
    EXPECT_GE(current_duration, 1);
    EXPECT_EQ(current_duration, stopwatch.getTotalMilliseconds());

    // Sleep for another 2 ms while the stopwatch is in the stopped state.
    usleep(2000);

    // In the stopped state, we should still have old durations measured.
    EXPECT_EQ(current_duration, stopwatch.getLastMilliseconds());
    EXPECT_EQ(current_duration, stopwatch.getTotalMilliseconds());

    // Start it again.
    stopwatch.start();

    // Slee for 1 ms.
    usleep(1000);

    // The durations should get updated as appropriate.
    current_duration = stopwatch.getLastMilliseconds();
    EXPECT_GE(stopwatch.getLastMilliseconds(), 1);
    EXPECT_GE(stopwatch.getTotalMilliseconds(), 2);
}

// Make sure that we can obtain the durations as microseconds.
TEST_F(StopwatchTest, getLastMicroseconds) {
    Stopwatch stopwatch;
    stopwatch.start();

    usleep(1000);

    stopwatch.stop();

    long current_duration = stopwatch.getLastMicroseconds();
    EXPECT_GE(current_duration, 1000);
    EXPECT_EQ(current_duration, stopwatch.getTotalMicroseconds());
}

// Make sure that we can use the "autostart" option to start the time
// measurement in the constructor.
TEST_F(StopwatchTest, autostart) {
    Stopwatch stopwatch(true);
    usleep(1000);

    stopwatch.stop();

    EXPECT_GE(stopwatch.getLastMilliseconds(), 1);
    EXPECT_EQ(stopwatch.getLastMilliseconds(), stopwatch.getTotalMilliseconds());
}

// Make sure that the conversion to the loggable string works as expected.
TEST_F(StopwatchTest, logFormat) {
    time_duration duration = microseconds(223043);
    EXPECT_EQ("223.043 ms", StopwatchImpl::logFormat(duration));

    duration = microseconds(1234);
    EXPECT_EQ("1.234 ms", StopwatchImpl::logFormat(duration));

    duration = microseconds(2000);
    EXPECT_EQ("2.000 ms", StopwatchImpl::logFormat(duration));
}

} // end of anonymous namespace
