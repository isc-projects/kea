// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <gtest/gtest.h>

#include <asiolink/asiolink.h>

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace {
// TODO: Consider this margin
const boost::posix_time::time_duration TIMER_MARGIN_MSEC =
    boost::posix_time::milliseconds(50);
}

using namespace asiolink;

// This fixture is for testing IntervalTimer. Some callback functors are 
// registered as callback function of the timer to test if they are called
// or not.
class IntervalTimerTest : public ::testing::Test {
protected:
    IntervalTimerTest() : io_service_() {}
    ~IntervalTimerTest() {}
    class TimerCallBack : public std::unary_function<void, void> {
    public:
        TimerCallBack(IntervalTimerTest* test_obj) : test_obj_(test_obj) {}
        void operator()() const {
            test_obj_->timer_called_ = true;
            test_obj_->io_service_.stop();
            return;
        }
    private:
        IntervalTimerTest* test_obj_;
    };
    class TimerCallBackCounter : public std::unary_function<void, void> {
    public:
        TimerCallBackCounter(IntervalTimerTest* test_obj) : test_obj_(test_obj) {
            counter_ = 0;
        }
        void operator()() {
            ++counter_;
            return;
        }
        int counter_;
    private:
        IntervalTimerTest* test_obj_;
    };
    class TimerCallBackCancelDeleter : public std::unary_function<void, void> {
    public:
        TimerCallBackCancelDeleter(IntervalTimerTest* test_obj,
                                   IntervalTimer* timer,
                                   TimerCallBackCounter& counter)
            : test_obj_(test_obj), timer_(timer), counter_(counter), count_(0)
        {}
        void operator()() {
            ++count_;
            if (count_ == 1) {
                // First time of call back.
                // Store the value of counter_.counter_.
                prev_counter_ = counter_.counter_;
                delete timer_;
            } else if (count_ == 2) {
                // Second time of call back.
                // Stop io_service to stop all timers.
                test_obj_->io_service_.stop();
                // Compare the value of counter_.counter_ with stored one.
                // If TimerCallBackCounter was not called (expected behavior),
                // they are same.
                if (counter_.counter_ == prev_counter_) {
                    test_obj_->timer_cancel_success_ = true;
                }
            }
            return;
        }
    private:
        IntervalTimerTest* test_obj_;
        IntervalTimer* timer_;
        TimerCallBackCounter& counter_;
        int count_;
        int prev_counter_;
    };
    class TimerCallBackCanceller {
    public:
        TimerCallBackCanceller(unsigned int& counter, IntervalTimer& itimer) :
            counter_(counter), itimer_(itimer)
        {}
        void operator()() {
            ++counter_;
            itimer_.cancel();
        }
    private:
        unsigned int& counter_;
        IntervalTimer& itimer_;
    };
    class TimerCallBackOverwriter : public std::unary_function<void, void> {
    public:
        TimerCallBackOverwriter(IntervalTimerTest* test_obj,
                                IntervalTimer& timer)
            : test_obj_(test_obj), timer_(timer), count_(0)
        {}
        void operator()() {
            ++count_;
            if (count_ == 1) {
                // First time of call back.
                // Call setup() to update callback function to TimerCallBack.
                test_obj_->timer_called_ = false;
                timer_.setup(TimerCallBack(test_obj_), 100);
            } else if (count_ == 2) {
                // Second time of call back.
                // If it reaches here, re-setup() is failed (unexpected).
                // We should stop here.
                test_obj_->io_service_.stop();
            }
            return;
        }
    private:
        IntervalTimerTest* test_obj_;
        IntervalTimer& timer_;
        int count_;
    };
protected:
    IOService io_service_;
    bool timer_called_;
    bool timer_cancel_success_;
};

TEST_F(IntervalTimerTest, invalidArgumentToIntervalTimer) {
    // Create asio_link::IntervalTimer and setup.
    IntervalTimer itimer(io_service_);
    // expect throw if call back function is empty
    EXPECT_THROW(itimer.setup(IntervalTimer::Callback(), 1),
                 isc::InvalidParameter);
    // expect throw if interval is not greater than 0
    EXPECT_THROW(itimer.setup(TimerCallBack(this), 0), isc::BadValue);
    EXPECT_THROW(itimer.setup(TimerCallBack(this), -1), isc::BadValue);
}

TEST_F(IntervalTimerTest, startIntervalTimer) {
    // Create asio_link::IntervalTimer and setup.
    // Then run IOService and test if the callback function is called.
    IntervalTimer itimer(io_service_);
    timer_called_ = false;
    // store start time
    boost::posix_time::ptime start;
    start = boost::posix_time::microsec_clock::universal_time();
    // setup timer
    itimer.setup(TimerCallBack(this), 100);
    EXPECT_EQ(100, itimer.getInterval());
    io_service_.run();
    // reaches here after timer expired
    // delta: difference between elapsed time and 100 milliseconds.
    boost::posix_time::time_duration delta =
        (boost::posix_time::microsec_clock::universal_time() - start)
         - boost::posix_time::millisec(100);
    if (delta.is_negative()) {
        delta.invert_sign();
    }
    // expect TimerCallBack is called; timer_called_ is true
    EXPECT_TRUE(timer_called_);
    // expect interval is 100 milliseconds +/- TIMER_MARGIN_MSEC.
    EXPECT_TRUE(delta < TIMER_MARGIN_MSEC);
}

TEST_F(IntervalTimerTest, destructIntervalTimer) {
    // This code isn't exception safe, but we'd rather keep the code
    // simpler and more readable as this is only for tests and if it throws
    // the program would immediately terminate anyway.

    // The call back function will not be called after the timer is
    // destroyed.
    //
    // There are two timers:
    //  itimer_counter (A)
    //   (Calls TimerCallBackCounter)
    //     - increments internal counter in callback function
    //  itimer_canceller (B)
    //   (Calls TimerCallBackCancelDeleter)
    //     - first time of callback, it stores the counter value of
    //       callback_canceller and destroys itimer_counter
    //     - second time of callback, it compares the counter value of
    //       callback_canceller with stored value
    //       if they are same the timer was not called; expected result
    //       if they are different the timer was called after destroyed
    //
    //     0  100  200  300  400  500  600 (ms)
    // (A) i--------+----x
    //                   ^
    //                   |destroy itimer_counter
    // (B) i-------------+--------------s
    //                                  ^stop io_service
    //                                   and check if itimer_counter have been
    //                                   stopped

    // itimer_counter will be deleted in TimerCallBackCancelDeleter
    IntervalTimer* itimer_counter = new IntervalTimer(io_service_);
    IntervalTimer itimer_canceller(io_service_);
    timer_cancel_success_ = false;
    TimerCallBackCounter callback_canceller(this);
    itimer_counter->setup(callback_canceller, 200);
    itimer_canceller.setup(
        TimerCallBackCancelDeleter(this, itimer_counter, callback_canceller),
        300);
    io_service_.run();
    EXPECT_TRUE(timer_cancel_success_);
}

TEST_F(IntervalTimerTest, cancel) {
    // Similar to destructIntervalTimer test, but the first timer explicitly
    // cancels itself on first callback.
    IntervalTimer itimer_counter(io_service_);
    IntervalTimer itimer_watcher(io_service_);
    unsigned int counter = 0;
    itimer_counter.setup(TimerCallBackCanceller(counter, itimer_counter), 100);
    itimer_watcher.setup(TimerCallBack(this), 200);
    io_service_.run();
    EXPECT_EQ(1, counter);
    EXPECT_EQ(0, itimer_counter.getInterval());

    // canceling an already canceled timer shouldn't cause any surprise.
    EXPECT_NO_THROW(itimer_counter.cancel());
}

TEST_F(IntervalTimerTest, overwriteIntervalTimer) {
    // Calling setup() multiple times updates call back function and interval.
    //
    // There are two timers:
    //  itimer (A)
    //   (Calls TimerCallBackCounter / TimerCallBack)
    //     - increments internal counter in callback function
    //       (TimerCallBackCounter)
    //       interval: 300 milliseconds
    //     - io_service_.stop() (TimerCallBack)
    //       interval: 100 milliseconds
    //  itimer_overwriter (B)
    //   (Calls TimerCallBackOverwriter)
    //     - first time of callback, it calls setup() to change call back
    //       function to TimerCallBack and interval of itimer to 100
    //       milliseconds
    //       after 300 + 100 milliseconds from the beginning of this test,
    //       TimerCallBack() will be called and io_service_ stops.
    //     - second time of callback, it means the test fails.
    //
    //     0  100  200  300  400  500  600  700  800 (ms)
    // (A) i-------------+----C----s
    //                        ^    ^stop io_service
    //                        |change call back function
    // (B) i------------------+-------------------S
    //                                            ^(stop io_service on fail)
    //

    IntervalTimer itimer(io_service_);
    IntervalTimer itimer_overwriter(io_service_);
    // store start time
    boost::posix_time::ptime start;
    start = boost::posix_time::microsec_clock::universal_time();
    itimer.setup(TimerCallBackCounter(this), 300);
    itimer_overwriter.setup(TimerCallBackOverwriter(this, itimer), 400);
    io_service_.run();
    // reaches here after timer expired
    // if interval is updated, it takes
    //   400 milliseconds for TimerCallBackOverwriter
    //   + 100 milliseconds for TimerCallBack (stop)
    //   = 500 milliseconds.
    // otherwise (test fails), it takes
    //   400 milliseconds for TimerCallBackOverwriter
    //   + 400 milliseconds for TimerCallBackOverwriter (stop)
    //   = 800 milliseconds.
    // delta: difference between elapsed time and 400 + 100 milliseconds
    boost::posix_time::time_duration delta =
        (boost::posix_time::microsec_clock::universal_time() - start)
         - boost::posix_time::millisec(400 + 100);
    if (delta.is_negative()) {
        delta.invert_sign();
    }
    // expect callback function is updated: TimerCallBack is called
    EXPECT_TRUE(timer_called_);
    // expect interval is updated
    EXPECT_TRUE(delta < TIMER_MARGIN_MSEC);
}
