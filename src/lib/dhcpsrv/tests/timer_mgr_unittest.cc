// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

#include <functional>
#include <sstream>
#include <unistd.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::test;

namespace {

/// @brief Test fixture class for @c TimerMgr.
class TimerMgrTest : public ::testing::Test {
public:

    /// @brief Constructor
    TimerMgrTest() = default;

    /// @brief Destructor
    virtual ~TimerMgrTest() = default;

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
    std::function<void ()> makeCallback(const std::string& timer_name);

    /// @brief Create a callback which generates exception.
    std::function<void ()> makeCallbackWithException();

    /// @brief Callback for timeout.
    ///
    /// This callback indicates the test timeout by setting the
    /// @c timeout_ member.
    void timeoutCallback();

    // @brief This test checks that certain errors are returned when invalid
    // parameters are specified when registering a timer, or when
    // the registration can't be made.
    void testRegisterTimer();

    /// @brief This test verifies that it is possible to unregister a timer from
    /// the TimerMgr.
    void testUnregisterTimer();

    /// @brief This test verifies that it is possible to unregister all timers.
    void testUnregisterTimers();

    /// @brief This test verifies that the timer execution can be cancelled.
    void testCancel();

    /// @brief This test verifies that the callbacks for the scheduled timers
    /// are actually called.
    void testScheduleTimers();

    /// @brief  This test verifies that exceptions emitted from the callback
    /// would be handled by the TimerMgr.
    void testCallbackWithException();

    /// @brief Type definition for a map holding calls counters for
    /// timers.
    typedef std::map<std::string, unsigned int> CallsCount;

    /// @brief Pointer to IO service used by the tests.
    IOServicePtr io_service_;

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
    io_service_.reset(new IOService());
    timer_mgr_ = TimerMgr::instance();
    timer_mgr_->setIOService(io_service_);
    calls_count_.clear();
}

void
TimerMgrTest::TearDown() {
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
TimerMgrTest::doWait(const long timeout, const bool /*call_receive*/) {
    IntervalTimer timer(*io_service_);
    timer.setup([this]() {
        io_service_->stop();
    }, timeout, IntervalTimer::ONE_SHOT);
    io_service_->run();
    io_service_->get_io_service().reset();
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

std::function<void ()>
TimerMgrTest::makeCallback(const std::string& timer_name) {
    return (std::bind(&TimerMgrTest::timerCallback, this, timer_name));
}

std::function<void ()>
TimerMgrTest::makeCallbackWithException() {
    return (std::bind(&TimerMgrTest::timerCallbackWithException, this));
}

// This test checks that certain errors are returned when invalid
// parameters are specified when registering a timer, or when
// the registration can't be made.
void
TimerMgrTest::testRegisterTimer() {
    // Empty timer name is not allowed.
    ASSERT_THROW(timer_mgr_->registerTimer("", makeCallback("timer1"), 1,
                                           IntervalTimer::ONE_SHOT),
                 BadValue);

    // Add a timer with a correct name.
    ASSERT_NO_THROW(timer_mgr_->registerTimer("timer2", makeCallback("timer2"), 1,
                                              IntervalTimer::ONE_SHOT));
    EXPECT_TRUE(timer_mgr_->isTimerRegistered("timer2"));

    // Adding the timer with the same name as the existing timer is not
    // allowed.
    ASSERT_THROW(timer_mgr_->registerTimer("timer2", makeCallback("timer2"), 1,
                                           IntervalTimer::ONE_SHOT),
                 BadValue);
}

TEST_F(TimerMgrTest, registerTimer) {
    // Disable Multi-Threading.
    MultiThreadingTest mt(false);
    testRegisterTimer();
}

TEST_F(TimerMgrTest, registerTimerMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);
    testRegisterTimer();
}

void
TimerMgrTest::testUnregisterTimer() {
    // Register a timer and start it.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));
    ASSERT_EQ(1, timer_mgr_->timersCount());
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));

    // Wait for the timer to execute several times.
    doWait(100);

    // Remember how many times the timer's callback was executed.
    const unsigned int calls_count = calls_count_["timer1"];
    ASSERT_GT(calls_count, 0);

    // Check that an attempt to unregister a non-existing timer would
    // result in exception.
    ASSERT_THROW(timer_mgr_->unregisterTimer("timer2"), BadValue);
    // Number of timers shouldn't have changed.
    ASSERT_EQ(1, timer_mgr_->timersCount());

    // Now unregister the correct one.
    ASSERT_NO_THROW(timer_mgr_->unregisterTimer("timer1"));
    ASSERT_EQ(0, timer_mgr_->timersCount());
    EXPECT_FALSE(timer_mgr_->isTimerRegistered("timer1"));

    doWait(100);

    // The number of calls for the timer1 shouldn't change as the
    // timer had been unregistered.
    EXPECT_EQ(calls_count_["timer1"], calls_count);
}

TEST_F(TimerMgrTest, unregisterTimer) {
    // Disable Multi-Threading.
    MultiThreadingTest mt(false);
    testUnregisterTimer();
}

TEST_F(TimerMgrTest, unregisterTimerMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);
    testUnregisterTimer();
}

void
TimerMgrTest::testUnregisterTimers() {
    // Register 10 timers.
    for (int i = 1; i <= 20; ++i) {
        std::ostringstream s;
        s << "timer" << i;
        ASSERT_NO_FATAL_FAILURE(registerTimer(s.str(), 1))
            << "fatal failure occurred while registering "
            << s.str();
        ASSERT_EQ(i, timer_mgr_->timersCount())
            << "invalid number of registered timers returned";
        ASSERT_NO_THROW(timer_mgr_->setup(s.str()))
            << "exception thrown while calling setup() for the "
            << s.str();
    }

    doWait(500);

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

    // Make sure there are no timers registered.
    ASSERT_EQ(0, timer_mgr_->timersCount());

    doWait(500);

    // The calls counter shouldn't change because there are
    // no timers registered.
    EXPECT_TRUE(calls_count == calls_count_);
}

TEST_F(TimerMgrTest, unregisterTimers) {
    // Disable Multi-Threading.
    MultiThreadingTest mt(false);
    testUnregisterTimers();
}

TEST_F(TimerMgrTest, unregisterTimersMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);
    testUnregisterTimers();
}

void
TimerMgrTest::testCancel() {
    // Register timer.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 1));

    // Kick in the timer and wait for 500ms.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));

    doWait(500);

    // Canceling non-existing timer should fail.
    EXPECT_THROW(timer_mgr_->cancel("timer2"), BadValue);

    // Canceling the good one should pass, even when the worker
    // thread is running.
    ASSERT_NO_THROW(timer_mgr_->cancel("timer1"));

    // Remember how many calls have been invoked and wait for
    // another 500ms.
    unsigned int calls_count = calls_count_["timer1"];

    doWait(500);

    // The number of calls shouldn't change because the timer had been
    // cancelled.
    ASSERT_EQ(calls_count, calls_count_["timer1"]);

    // Setup the timer again.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));

    // Restart the thread.
    doWait(500);

    // New calls should be recorded.
    EXPECT_GT(calls_count_["timer1"], calls_count);
}

TEST_F(TimerMgrTest, cancel) {
    // Disable Multi-Threading.
    MultiThreadingTest mt(false);
    testCancel();
}

TEST_F(TimerMgrTest, cancelMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);
    testCancel();
}

void
TimerMgrTest::testScheduleTimers() {
    // Register two timers: 'timer1' and 'timer2'. The first timer will
    // be executed at the 50ms interval. The second one at the 100ms
    // interval.
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer1", 50));
    ASSERT_NO_FATAL_FAILURE(registerTimer("timer2", 100));

    // Kick in the timers.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));
    ASSERT_NO_THROW(timer_mgr_->setup("timer2"));

    // Run IfaceMgr::receive6() in the loop for 1000ms. This function
    // will read data from the watch sockets created when the timers
    // were registered. The data is delivered to the watch sockets
    // at the interval of the timers, which should break the blocking
    // call to receive6(). As a result, the callbacks associated
    // with the watch sockets should be called.
    doWait(1000);

    // We have been running the timer for 1000ms at the interval of
    // 50ms. The maximum number of callbacks is 20. However, the
    // callback itself takes time. Stopping the thread takes time.
    // So, the real number differs significantly. We don't know
    // exactly how many have been executed. It should be more
    // than 10 for sure. But we really made up the numbers here.
    EXPECT_GT(calls_count_["timer1"], 10);
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

    // Wait another 500ms. The 'timer1' was unregistered so it
    // should not make any more calls. The 'timer2' should still
    // work as previously.
    doWait(500);

    // The number of calls shouldn't have changed.
    EXPECT_EQ(calls_count_timer1, calls_count_["timer1"]);
    // There should be some new calls registered for the 'timer2'.
    EXPECT_GT(calls_count_["timer2"], calls_count_timer2);
}

TEST_F(TimerMgrTest, scheduleTimers) {
    // Disable Multi-Threading.
    MultiThreadingTest mt(false);
    testScheduleTimers();
}

TEST_F(TimerMgrTest, scheduleTimersMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);
    testScheduleTimers();
}

void
TimerMgrTest::testCallbackWithException() {
    // Create timer which will trigger callback generating exception.
    ASSERT_NO_THROW(
        timer_mgr_->registerTimer("timer1", makeCallbackWithException(), 1,
                                  IntervalTimer::ONE_SHOT)
    );

    // Setup the timer.
    ASSERT_NO_THROW(timer_mgr_->setup("timer1"));

    // Start thread. We hope that exception will be caught by the @c TimerMgr
    // and will not kill the process.
    doWait(500);
}

TEST_F(TimerMgrTest, callbackWithException) {
    // Disable Multi-Threading.
    MultiThreadingTest mt(false);
    testCallbackWithException();
}

TEST_F(TimerMgrTest, callbackWithExceptionMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);
    testCallbackWithException();
}

// This test verifies that IO service specified for the TimerMgr
// must not be null.
TEST_F(TimerMgrTest, setIOService) {
    EXPECT_THROW(timer_mgr_->setIOService(IOServicePtr()),
                 BadValue);
}

} // end of anonymous namespace
