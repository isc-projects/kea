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

#include <asio.hpp>
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

    /// @brief IO service used by the test fixture class.
    IOService io_service_;

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

    /// @brief Wait for one or many ready handlers.
    ///
    /// @param timeout Wait timeout.
    void doWait(const long timeout);

    /// @brief Generic callback for timers under test.
    ///
    /// This callback increases the calls count for specified timer name.
    ///
    /// @param timer_name Name of the timer for which callback counter should
    /// be increased.
    void timerCallback(const std::string& timer_name);

    /// @brief Callback for timeout.
    void timeoutCallback();

    /// @brief Holds the calls count for test timers.
    ///
    /// The key of this map holds the timer names. The value holds the number
    /// of calls to the timer handlers.
    std::map<std::string, unsigned int> calls_count_;

};

void
TimerMgrTest::SetUp() {
    calls_count_.clear();
//    TimerMgr::instance().startThread();
}

void
TimerMgrTest::TearDown() {
//    TimerMgr::instance().stopThread();
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

void
TimerMgrTest::doWait(const long timeout) {
    IntervalTimer timeout_timer(io_service_);
    timeout_timer.setup(boost::bind(&TimerMgrTest::timeoutCallback, this), timeout,
                        IntervalTimer::ONE_SHOT);

    io_service_.run_one();
}

void
TimerMgrTest::timerCallback(const std::string& timer_name) {
    // Accumulate the number of calls to the timer handler.
    ++calls_count_[timer_name];

    TimerMgr::instance().setup(timer_name);
}

void
TimerMgrTest::timeoutCallback() {
    io_service_.stop();
}

TEST_F(TimerMgrTest, registerTimer) {
    TimerMgr& timer_mgr = TimerMgr::instance();

    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));

    TimerMgr::instance().startThread();
    TimerMgr::instance().setup("timer1");

    doWait(500);

    TimerMgr::instance().stopThread();

    EXPECT_GT(calls_count_["timer1"], 1);
}

} // end of anonymous namespace
