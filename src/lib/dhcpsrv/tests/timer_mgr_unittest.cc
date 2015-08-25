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
#include <dhcpsrv/timer_mgr.h>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

/// @brief Test fixture class for @c TimerMgr.
class TimerMgrTest : public ::testing::Test {
private:
    /// @brief Prepares the class for a test.
    virtual void SetUp();

    /// @brief Cleans up after the test.
    virtual void TearDown();

public:

    /// @brief Wrapper method for registering a new timer.
    ///
    /// This method registers a new timer in the @c TimerMgr. It associates a
    /// @c timerCallback method with a timer. This method registers a number of
    /// calls to the particular timer in the @c calls_count_ map.
    ///
    /// @param timer_name Unique timer name.
    /// @param timer_interval Timer interval.
    /// @param mode Interval timer mode, which defaults to
    /// @c IntervalTimer::ONE_SHOT.
    void registerTimer(const std::string& timer_name, const long timer_interval,
                       const IntervalTimer::Mode& timer_mode = IntervalTimer::ONE_SHOT);

    /// @brief Waits for one ready handler to be executed.
    ///
    /// @param timeout Wait timeout.
    /// @return false if the timeout has occurred, true otherwise. The returned
    /// value of true indicates that the test was successful, i.e. the timer
    /// ready handler had been executed before the timeout occurred.
    bool waitForOne(const long timeout);

    /// @brief Waits for a specified amount of time to execute ready handlers.
    ///
    /// This method waits for exactly @c timeout amount of time for all ready
    /// handlers to be executed. A caller can determine whether the expected
    /// handlers have been executed by checking the @c calls_count_ entries.
    ///
    /// @param timeout Wait timeout.
    void waitForMany(const long timeout);

private:

    /// @brief Wait for one or many ready handlers.
    ///
    /// This method is called internally by the public methods
    /// @c waitForOne and @c waitForMany.
    ///
    /// @param timeout Wait timeout.
    /// @param wait_for_many A boolean flag indicating if the method should
    /// wait for the specified amount of time to execute all handlers (if true)
    /// or should wait for one ready handlers (if false).
    ///
    /// @return false if the timeout has occurred, true otherwise.
    bool doWait(const long timeout, const bool wait_for_many);

    /// @brief Generic callback for timers under test.
    ///
    /// This callback increases the calls count for specified timer name.
    ///
    /// @param timer_name Name of the timer for which callback counter should
    /// be increased.
    void timerCallback(const std::string& timer_name);

    /// @brief Callback for timeout.
    ///
    /// This callback is installed when the @c waitForOne or @c waitForMany
    /// is executed to stop waiting after a given amount of time. It stops
    /// the io service in the @c TimerMgr.
    void timeoutCallback(asiolink::IOService& io_service);

    /// @brief Internal flag indicating if test timeout occurred.
    ///
    /// This flag is set by the @c timeoutCallback function when the timeout
    /// has occurred. The @c waitWithTimeout returns 'false' if this value
    /// is 'true', and 'true' if this value is 'false'.
    bool timeout_occurred_;

public:

    /// @brief Holds the calls count for test timers.
    ///
    /// The key of this map holds the timer names. The value holds the number
    /// of calls to the timer handlers.
    std::map<std::string, unsigned int> calls_count_;

};

void
TimerMgrTest::SetUp() {
    calls_count_.clear();
    timeout_occurred_ = false;
}

void
TimerMgrTest::TearDown() {
}

void
TimerMgrTest::registerTimer(const std::string& timer_name, const long timer_interval,
                            const IntervalTimer::Mode& timer_mode) {
    TimerMgr& timer_mgr = TimerMgr::instance();

    ASSERT_NO_THROW(
        timer_mgr.registerTimer(timer_name, boost::bind(&TimerMgrTest::timerCallback,
                                                        this, timer_name),
                                timer_interval, timer_mode)
    );

    calls_count_[timer_name] = 0;

}

bool
TimerMgrTest::waitForOne(const long timeout) {
    return (doWait(timeout, false));
}

void
TimerMgrTest::waitForMany(const long timeout) {
    static_cast<void>(doWait(timeout, true));
}

bool
TimerMgrTest::doWait(const long timeout, const bool wait_for_many) {
    IOService& io_service = TimerMgr::instance().getIOService();
    IntervalTimer timeout_timer(io_service);
    timeout_timer.setup(boost::bind(&TimerMgrTest::timeoutCallback, this,
                                    boost::ref(io_service)), timeout,
                        IntervalTimer::ONE_SHOT);
    if (wait_for_many) {
        io_service.run();

    } else {
        io_service.run_one();
    }

    if (timeout_occurred_) {
        // Reset the flag so as it is set to false for another test.
        timeout_occurred_ = false;
        return (false);
    }

    // No timeout, some ready handlers have been executed.
    return (true);

}

void
TimerMgrTest::timerCallback(const std::string& timer_name) {
    // Accumulate the number of calls to the timer handler.
    ++calls_count_[timer_name];
}

void
TimerMgrTest::timeoutCallback(asiolink::IOService& io_service) {
    // Timeout has occurred. Stop the io service to stop waiting for
    // ready handlers.
    io_service.stop();
    // Indicate that we hit the timeout.
    timeout_occurred_ = true;
}

TEST_F(TimerMgrTest, registerTimer) {
    TimerMgr& timer_mgr = TimerMgr::instance();

    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));
    TimerMgr::instance().setup("timer1");

    EXPECT_TRUE(waitForOne(5));

    EXPECT_EQ(1, calls_count_["timer1"]);
}

} // end of anonymous namespace
