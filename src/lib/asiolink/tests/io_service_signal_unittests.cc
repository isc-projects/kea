// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service_signal.h>
#include <asiolink/testutils/timed_signal.h>

#include <gtest/gtest.h>

#include <functional>
#include <queue>

using namespace isc::asiolink::test;
namespace ph = std::placeholders;

namespace isc {
namespace asiolink {

/// @brief Test fixture for testing the use of IO service signals.
///
/// This fixture is exercises IO service signaling.
class IOSignalTest : public ::testing::Test {
public:
    /// @brief IOService instance to process IO.
    asiolink::IOServicePtr io_service_;

    /// @brief Failsafe timer to ensure test(s) do not hang.
    isc::asiolink::IntervalTimer test_timer_;

    /// @brief Maximum time should be allowed to run.
    int test_time_ms_;

    /// @brief IOSignalSet object.
    IOSignalSetPtr io_signal_set_;

    /// @brief Vector to record the signal values received.
    std::vector<int> processed_signals_;

    /// @brief The number of signals that must be received to stop the test.
    int stop_at_count_;

    /// @brief Boolean which causes IOSignalHandler to throw if true.
    bool handler_throw_error_;

    /// @brief Constructor.
    IOSignalTest() :
        io_service_(new asiolink::IOService()), test_timer_(*io_service_),
        test_time_ms_(0), io_signal_set_(),
        processed_signals_(), stop_at_count_(0), handler_throw_error_(false) {

        io_signal_set_.reset(new IOSignalSet(io_service_,
                                             std::bind(&IOSignalTest::processSignal,
                                                       this, ph::_1)));
    }

    /// @brief Destructor.
    ~IOSignalTest() {
        io_signal_set_.reset();
        // Make sure the cancel handler for the IOSignalSet is called.
        io_service_->poll();
    }

    /// @brief Method used as the IOSignalSet handler.
    ///
    /// Records the value of the given signal and checks if the desired
    /// number of signals have been received.  If so, the IOService is
    /// stopped which will cause IOService::run() to exit, returning control
    /// to the test.
    ///
    /// @param signum signal number.
    void processSignal(int signum) {
        // Remember the signal we got.
        processed_signals_.push_back(signum);

        // If the flag is on, force a throw to test error handling.
        if (handler_throw_error_) {
            handler_throw_error_ = false;
            isc_throw(BadValue, "processSignal throwing simulated error");
        }

        // If we've hit the number we want stop the IOService. This will cause
        // run to exit.
        if (processed_signals_.size() >= stop_at_count_) {
            io_service_->stop();
        }
    }

    /// @brief Sets the failsafe timer for the test to the given time.
    ///
    /// @param  test_time_ms maximum time in milliseconds the test should
    /// be allowed to run.
    void setTestTime(int test_time_ms) {
        // Fail safe shutdown
        test_time_ms_ = test_time_ms;
        test_timer_.setup(std::bind(&IOSignalTest::testTimerHandler, this),
                          test_time_ms_, asiolink::IntervalTimer::ONE_SHOT);
    }

    /// @brief Failsafe timer expiration handler.
    void testTimerHandler() {
        io_service_->stop();
        FAIL() << "Test Time: " << test_time_ms_ << " expired";
    }
};

// Test the basic mechanics of IOSignal by handling one signal occurrence.
TEST_F(IOSignalTest, singleSignalTest) {
    // Set test fail safe.
    setTestTime(1000);

    // Register to receive SIGINT.
    ASSERT_NO_THROW(io_signal_set_->add(SIGINT));

    // Use TimedSignal to generate SIGINT 100 ms after we start IOService::run.
    TimedSignal sig_int(*io_service_, SIGINT, 100);

    // The first handler executed is the IOSignal's internal timer expire
    // callback.
    io_service_->run_one();

    // The next handler executed is IOSignal's handler.
    io_service_->run_one();

    // Polling once to be sure.
    io_service_->poll();

    // Verify that we processed the signal.
    ASSERT_EQ(1, processed_signals_.size());

    // Now check that signal value is correct.
    EXPECT_EQ(SIGINT, processed_signals_[0]);

    // Set test fail safe.
    setTestTime(1000);

    // Unregister the receive of SIGINT.
    ASSERT_NO_THROW(io_signal_set_->remove(SIGINT));

    // Use TimedSignal to generate SIGINT 100 ms after we start IOService::run.
    TimedSignal sig_int_too_late(*io_service_, SIGINT, 100);

    // The first handler executed is the IOSignal's internal timer expire
    // callback.
    io_service_->run_one();

    // The next handler executed is IOSignal's handler.
    io_service_->run_one();

    // Polling once to be sure.
    io_service_->poll();

    // Verify that we did not process the signal.
    ASSERT_EQ(1, processed_signals_.size());
}

// Test verifies that signals can be delivered rapid-fire without falling over.
TEST_F(IOSignalTest, hammer) {
    // Set test fail safe.  We want to allow at least 100 ms per signal,
    // plus a bit more so 6 seconds ought to be enough.
    setTestTime(6000);

    // Register to receive SIGINT.
    ASSERT_NO_THROW(io_signal_set_->add(SIGINT));

    // Stop the test after 50 signals. This allows 100ms+ per signal
    // so even sluggish VMs should handle it.
    stop_at_count_ = 50;

    // User a repeating TimedSignal so we should generate a signal every 1 ms
    // until we hit our stop count.
    TimedSignal sig_int(*io_service_, SIGINT, 1,
                        asiolink::IntervalTimer::REPEATING);

    // Start processing IO.  This should continue until we stop either by
    // hitting the stop count or if things go wrong, max test time.
    io_service_->run();

    // Verify we received the expected number of signals.
    EXPECT_EQ(stop_at_count_, processed_signals_.size());

    // Now check that each signal value is correct. This is sort of a silly
    // check but it does ensure things didn't go off the rails somewhere.
    for (int i = 0; i < processed_signals_.size(); ++i) {
        EXPECT_EQ(SIGINT, processed_signals_[i]);
    }
}

// Verifies that handler exceptions are caught.
TEST_F(IOSignalTest, handlerThrow) {
    // Set test fail safe.
    setTestTime(1000);

    // Register to receive SIGINT.
    ASSERT_NO_THROW(io_signal_set_->add(SIGINT));

    // Set the stop after we've done at least 1 all the way through.
    stop_at_count_ = 1;

    // Use TimedSignal to generate SIGINT after we start IOService::run.
    TimedSignal sig_int(*io_service_, SIGINT, 100,
                        asiolink::IntervalTimer::REPEATING);

    // Set the test flag to cause the handler to throw an exception.
    handler_throw_error_ = true;

    // Start processing IO.  This should fail with the handler exception.
    ASSERT_NO_THROW(io_service_->run());

    // Verify that the we hit the throw block.  The flag will be false
    // we will have skipped the stop count check so number signals processed
    // is stop_at_count_ + 1.
    EXPECT_FALSE(handler_throw_error_);
    EXPECT_EQ(stop_at_count_ + 1, processed_signals_.size());
}

// Verifies that we can handle a mixed set of signals.
TEST_F(IOSignalTest, mixedSignals) {
    // Set test fail safe.
    setTestTime(1000);

    // Register to receive SIGINT, SIGUSR1, and SIGUSR2.
    ASSERT_NO_THROW(io_signal_set_->add(SIGINT));
    ASSERT_NO_THROW(io_signal_set_->add(SIGUSR1));
    ASSERT_NO_THROW(io_signal_set_->add(SIGUSR2));

    stop_at_count_ = 8;

    // User a repeating TimedSignal so we should generate a signal every 3, 5
    // and 7 ms until we hit our stop count.
    TimedSignal sig_1(*io_service_, SIGINT, 3,
                      asiolink::IntervalTimer::REPEATING);
    TimedSignal sig_2(*io_service_, SIGUSR1, 5,
                      asiolink::IntervalTimer::REPEATING);
    TimedSignal sig_3(*io_service_, SIGUSR2, 7,
                      asiolink::IntervalTimer::REPEATING);

    // Start processing IO.  This should continue until we stop either by
    // hitting the stop count or if things go wrong, max test time.
    io_service_->run();

    // Verify we received the expected number of signals.
    ASSERT_EQ(stop_at_count_, processed_signals_.size());

    // There is no guarantee that the signals will always be delivered in the
    // order they are raised, but all of them should get delivered.  Loop
    // through and tally them up.
    int sigint_cnt = 0;
    int sigusr1_cnt = 0;
    int sigusr2_cnt = 0;
    for (int i = 0; i < stop_at_count_; ++i) {
        switch (processed_signals_[i]) {
        case SIGINT:
            ++sigint_cnt;
            break;
        case SIGUSR1:
            ++sigusr1_cnt;
            break;
        case SIGUSR2:
            ++sigusr2_cnt;
            break;
        default:
            FAIL() << "Invalid signal value: "
                   << processed_signals_[i]
                   << " at i:" << i;
            break;
        }
    }

    // See if our counts are correct.
    EXPECT_EQ(sigint_cnt, 4);
    EXPECT_EQ(sigusr1_cnt, 2);
    EXPECT_EQ(sigusr2_cnt, 2);
}

} // namespace asiolink
} // namespace isc
