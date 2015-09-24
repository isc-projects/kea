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

#include <boost/asio.hpp>
#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>
#include <util/stopwatch.h>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <unistd.h>

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

    /// @brief Wait for one or many ready handlers.
    ///
    /// @param timeout Wait timeout in milliseconds.
    /// @param call_receive Indicates if the @c IfaceMgr::receive6
    /// should be called to run pending callbacks and clear
    /// watch sockets.
    void doWait(const long timeout, const bool call_receive = true);

    /// @brief Generic callback for timers under test.
    ///
    /// This callback increases the calls count for specified timer name.
    ///
    /// @param timer_name Name of the timer for which callback counter should
    /// be increased.
    void timerCallback(const std::string& timer_name);

    /// @brief Callback which generates exception.
    ///
    /// This callback is used to test that the @c TimerMgr can handle
    /// the case when the callback generates exceptions.
    void timerCallbackWithException();

    /// @brief Create a generic callback function for the timer.
    ///
    /// This is just a wrapped to make it a bit more convenient
    /// in the test.
    boost::function<void ()> makeCallback(const std::string& timer_name);

    /// @brief Create a callback which generates exception.
    boost::function<void ()> makeCallbackWithException();

    /// @brief Callback for timeout.
    ///
    /// This callback indicates the test timeout by setting the
    /// @c timeout_ member.
    void timeoutCallback();

    /// @brief Type definition for a map holding calls counters for
    /// timers.
    typedef std::map<std::string, unsigned int> CallsCount;

    /// @brief Holds the calls count for test timers.
    ///
    /// The key of this map holds the timer names. The value holds the number
    /// of calls to the timer handlers.
    CallsCount calls_count_;

    /// @brief Instance of @c TimerMgr used by the tests.
    TimerMgrPtr timer_mgr_;
};

void
TimerMgrTest::SetUp() {
    timer_mgr_ = TimerMgr::instance();
    calls_count_.clear();
    // Make sure there are no dangling threads.
    timer_mgr_->stopThread();
}

void
TimerMgrTest::TearDown() {
    // Make sure there are no dangling threads.
    timer_mgr_->stopThread();
    // Remove all timers.
    timer_mgr_->unregisterTimers();
}

void
TimerMgrTest::registerTimer(const std::string& timer_name, const long timer_interval,
                            const IntervalTimer::Mode& timer_mode) {
    // Register the timer with the generic callback that counts the
    // number of callback invocations.
    ASSERT_NO_THROW(
        timer_mgr_->registerTimer(timer_name, makeCallback(timer_name), timer_interval,
                                 timer_mode)
    );

    calls_count_[timer_name] = 0;

}

void
TimerMgrTest::doWait(const long timeout, const bool call_receive) {
    util::Stopwatch stopwatch;
    while (stopwatch.getTotalMilliseconds() < timeout) {
        if (call_receive) {
            // Block for one 1 millisecond.
            IfaceMgr::instancePtr()->receive6(0, 1000);
        }
    }
}

void
TimerMgrTest::timerCallback(const std::string& timer_name) {
    // Accumulate the number of calls to the timer handler.
    ++calls_count_[timer_name];

    // The timer installed is the ONE_SHOT timer, so we have
    // to reschedule the timer.
    timer_mgr_->setup(timer_name);
}

void
TimerMgrTest::timerCallbackWithException() {
    isc_throw(Exception, "timerCallbackWithException");
}

boost::function<void ()>
TimerMgrTest::makeCallback(const std::string& timer_name) {
    return (boost::bind(&TimerMgrTest::timerCallback, this, timer_name));
}

boost::function<void ()>
TimerMgrTest::makeCallbackWithException() {
    return (boost::bind(&TimerMgrTest::timerCallbackWithException, this));
}

// This test checks that certain errors are returned when invalid
// parameters are specified when registering a timer, or when
// the registration can't be made.
TEST_F(TimerMgrTest, registerTimer) {
    // Empty timer name is not allowed.
    ASSERT_THROW(timer_mgr_->registerTimer("", makeCallback("timer1"), 1,
                                           IntervalTimer::ONE_SHOT),
                 BadValue);

    // Add a timer with a correct name.
    ASSERT_NO_THROW(timer_mgr_->registerTimer("timer2", makeCallback("timer2"), 1,
                                              IntervalTimer::ONE_SHOT));
    // Adding the timer with the same name as the existing timer is not
    // allowed.
    ASSERT_THROW(timer_mgr_->registerTimer("timer2", makeCallback("timer2"), 1,
                                           IntervalTimer::ONE_SHOT),
                 BadValue);

    // Start worker thread.
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Can't register the timer when the thread is running.
    ASSERT_THROW(timer_mgr_->registerTimer("timer1", makeCallback("timer1"), 1,
                                           IntervalTimer::ONE_SHOT),
                 InvalidOperation);

    // Stop the thread and retry.
    ASSERT_NO_THROW(timer_mgr_->stopThread());
    EXPECT_NO_THROW(timer_mgr_->registerTimer("timer1", makeCallback("timer1"), 1,
                                              IntervalTimer::ONE_SHOT));

}

// This test verifies that it is possible to unregister a timer from
// the TimerMgr.
TEST_F(TimerMgrTest, unregisterTimer) {
    // Register a timer and start it.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Wait for the timer to execute several times.
    doWait(100);

    // Stop the thread but execute pending callbacks.
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));

    // Remember how many times the timer's callback was executed.
    const unsigned int calls_count = calls_count_["timer1"];
    ASSERT_GT(calls_count, 0);

    // Check that an attempt to unregister a non-existing timer would
    // result in exeception.
    EXPECT_THROW(timer_mgr_->unregisterTimer("timer2"), BadValue);

    // Now unregister the correct one.
    ASSERT_NO_THROW(timer_mgr_->unregisterTimer("timer1"));

    // Start the thread again and wait another 100ms.
    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(100);
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));

    // The number of calls for the timer1 shouldn't change as the
    // timer had been unregistered.
    EXPECT_EQ(calls_count_["timer1"], calls_count);
}

// This test verifies taht it is possible to unregister all timers.
/// @todo This test is disabled because it may occassionally hang
/// due to bug in the ASIO implementation shipped with Kea.
/// Replacing it with the ASIO implementation from BOOST does
/// solve the problem. See ticket #4009. Until this ticket is
/// implemented, the test should remain disabled.
TEST_F(TimerMgrTest, unregisterTimers) {
    // Register 10 timers.
    for (int i = 1; i <= 20; ++i) {
        std::ostringstream s;
        s << "timer" << i;
        ASSERT_NO_FATAL_FAILURE(registerTimer(s.str(), 1))
            << "fatal failure occurred while registering "
            << s.str();
        ASSERT_NO_THROW(timer_mgr_->setup(s.str()))
            << "exception thrown while calling setup() for the "
            << s.str();
    }

    // Start worker thread and wait for 500ms.
    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(500);
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));

    // Make sure that all timers have been executed at least once.
    for (CallsCount::iterator it = calls_count_.begin();
         it != calls_count_.end(); ++it) {
        unsigned int calls_count = it->second;
        ASSERT_GT(calls_count, 0)
            << "expected calls counter for timer"
            << (std::distance(calls_count_.begin(), it) + 1)
            << " greater than 0";
    }

    // Copy counters for all timers.
    CallsCount calls_count(calls_count_);

    // Let's unregister all timers.
    ASSERT_NO_THROW(timer_mgr_->unregisterTimers());

    // Start worker thread again and wait for 500ms.
    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(500);
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));

    // The calls counter shouldn't change because there are
    // no timers registered.
    EXPECT_TRUE(calls_count == calls_count_);
}

// This test checks that it is not possible to unregister timers
// while the thread is running.
TEST_F(TimerMgrTest, unregisterTimerWhileRunning) {
    // Register two timers.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer2", 1));

    // Start the thread and make sure we can't unregister them.
    ASSERT_NO_THROW(timer_mgr_->startThread());
    EXPECT_THROW(timer_mgr_->unregisterTimer("timer1"), InvalidOperation);
    EXPECT_THROW(timer_mgr_->unregisterTimers(), InvalidOperation);

    // No need to stop the thread as it will be stopped by the
    // test fixture destructor.
}

// This test verifies that the timer execution can be cancelled.
TEST_F(TimerMgrTest, cancel) {
    // Register timer.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));

    // Kick in the timer and wait for 500ms.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));
    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(500);
    ASSERT_NO_THROW(timer_mgr_->stopThread());

    // Cancelling non-existing timer should fail.
    EXPECT_THROW(timer_mgr_->cancel("timer2"), BadValue);

    // Cancelling the good one should pass, even when the worker
    // thread is running.
    ASSERT_NO_THROW(timer_mgr_->cancel("timer1"));

    // Remember how many calls have been invoked and wait for
    // another 500ms.
    unsigned int calls_count = calls_count_["timer1"];

    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(500);
    // Stop thread before we setup again.
    ASSERT_NO_THROW(timer_mgr_->stopThread());

    // The number of calls shouldn't change because the timer had been
    // cancelled.
    ASSERT_EQ(calls_count, calls_count_["timer1"]);

    // Setup the timer again.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));

    // Restart the thread.
    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(500);

    // New calls should be recorded.
    EXPECT_GT(calls_count_["timer1"], calls_count);
}

// This test verifies that the callbacks for the scheduled timers are
// actually called.
TEST_F(TimerMgrTest, scheduleTimers) {
    // Register two timers: 'timer1' and 'timer2'. The first timer will
    // be executed at the 1ms interval. The second one at the 5ms
    // interval.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer2", 5));

    // Kick in the timers.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));
    ASSERT_NO_THROW(timer_mgr_->setup("timer2"));

    // We can start the worker thread before we even kick in the timers.
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Run IfaceMgr::receive6() in the loop for 500ms. This function
    // will read data from the watch sockets created when the timers
    // were registered. The data is delivered to the watch sockets
    // at the interval of the timers, which should break the blocking
    // call to receive6(). As a result, the callbacks associated
    // with the watch sockets should be called.
    doWait(500);

    // Stop the worker thread, which would halt the execution of
    // the timers.
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));

    // We have been running the timer for 500ms at the interval of
    // 1 ms. The maximum number of callbacks is 500. However, the
    // callback itself takes time. Stoping the thread takes time.
    // So, the real number differs significantly. We don't know
    // exactly how many have been executed. It should be more
    // than 10 for sure. But we really made up the numbers here.
    EXPECT_GT(calls_count_["timer1"], 25);
    // For the second timer it should be more than 5.
    EXPECT_GT(calls_count_["timer2"], 5);

    // Because the interval of the 'timer1' is lower than the
    // interval of the 'timer2' the number of calls should
    // be higher for the 'timer1'.
    EXPECT_GT(calls_count_["timer1"], calls_count_["timer2"]);

    // Remember the number of calls from 'timer1' and 'timer2'.
    unsigned int calls_count_timer1 = calls_count_["timer1"];
    unsigned int calls_count_timer2 = calls_count_["timer2"];

    // Unregister the 'timer1'.
    ASSERT_NO_THROW(timer_mgr_->unregisterTimer("timer1"));

    // Restart the thread.
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Wait another 500ms. The 'timer1' was unregistered so it
    // should not make any more calls. The 'timer2' should still
    // work as previously.
    doWait(500);

    // The number of calls shouldn't have changed.
    EXPECT_EQ(calls_count_timer1, calls_count_["timer1"]);
    // There should be some new calls registered for the 'timer2'.
    EXPECT_GT(calls_count_["timer2"], calls_count_timer2);
}

// This test verifies that it is possible to force that the pending
// timer callbacks are executed when the worker thread is stopped.
TEST_F(TimerMgrTest, stopThreadWithRunningHandlers) {
    // Register 'timer1'.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));

    // Kick in the timer.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Run the thread for 100ms. This should run some timers. The 'false'
    // value indicates that the IfaceMgr::receive6 is not called, so the
    // watch socket is never cleared.
    doWait(100, false);

    // There should be no calls registered for the timer1.
    EXPECT_EQ(0, calls_count_["timer1"]);

    // Stop the worker thread without completing pending callbacks.
    ASSERT_NO_THROW(timer_mgr_->stopThread(false));

    // There should be still not be any calls registered.
    EXPECT_EQ(0, calls_count_["timer1"]);

    // We can restart the worker thread before we even kick in the timers.
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Run the thread for 100ms. This should run some timers. The 'false'
    // value indicates that the IfaceMgr::receive6 is not called, so the
    // watch socket is never cleared.
    doWait(100, false);

    // There should be no calls registered for the timer1.
    EXPECT_EQ(0, calls_count_["timer1"]);

    // Stop the worker thread with completing pending callbacks.
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));

    // There should be one call registered.
    EXPECT_EQ(1, calls_count_["timer1"]);
}

// This test verifies that exceptions emitted from the callback would
// be handled by the TimerMgr.
TEST_F(TimerMgrTest, callbackWithException) {
    // Create timer which will trigger callback generating exception.
    ASSERT_NO_THROW(
        timer_mgr_->registerTimer("timer1", makeCallbackWithException(), 1,
                                  IntervalTimer::ONE_SHOT)
    );

    // Setup the timer.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));

    // Start thread. We hope that exception will be caught by the @c TimerMgr
    // and will not kill the process.
    ASSERT_NO_THROW(timer_mgr_->startThread());
    doWait(500);
    ASSERT_NO_THROW(timer_mgr_->stopThread(true));
}

} // end of anonymous namespace
