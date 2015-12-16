// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <d_test_stubs.h>
#include <d2/io_service_signal.h>

#include <gtest/gtest.h>

#include <queue>

namespace isc {
namespace d2 {

/// @brief Test fixture for testing the use of IOSignals.
///
/// This fixture is exercises IOSignaling as it is intended to be used in
/// an application in conjuction with util::SignalSet.
class IOSignalTest : public ::testing::Test {
public:
    /// @brief IOService instance to process IO.
    asiolink::IOServicePtr io_service_;
    /// @brief Failsafe timer to ensure test(s) do not hang.
    isc::asiolink::IntervalTimer test_timer_;
    /// @brief Maximum time should be allowed to run.
    int test_time_ms_;

    /// @brief SignalSet object so we can catch real signals.
    util::SignalSetPtr signal_set_;

    /// @brief IOSignalQueue so we can generate IOSignals.
    IOSignalQueuePtr io_signal_queue_;

    /// @brief Vector to record the signal values received.
    std::vector<int> processed_signals_;
    /// @brief The number of signals that must be received to stop the test.
    int stop_at_count_;
    /// @brief Boolean which causes IOSignalHandler to throw if true.
    bool handler_throw_error_;

    /// @brief Constructor
    IOSignalTest() :
        io_service_(new asiolink::IOService()), test_timer_(*io_service_),
        test_time_ms_(0), signal_set_(),
        io_signal_queue_(new IOSignalQueue(io_service_)),
        processed_signals_(), stop_at_count_(0), handler_throw_error_(false) {
    }

    /// @brief Destructor
    ~IOSignalTest() {
        if (signal_set_) {
            signal_set_->clear();
        }

        // clear the on-receipt handler
        util::SignalSet::clearOnReceiptHandler();
    }

    /// @brief On-receipt signal handler used by unit tests.
    ///
    /// This function is registered with SignalSet as the "on-receipt" handler.
    /// When an OS signal is caught it schedules an IOSignal.
    ///
    /// @param signum Signal being handled.
    bool onReceiptHandler(int signum) {
        // Queue up a signal binging processSignal instance method as the
        // IOSignalHandler.
        io_signal_queue_->pushSignal(signum,
                                  boost::bind(&IOSignalTest::processSignal,
                                              this, _1));

        // Return true so SignalSet knows the signal has been consumed.
        return (true);
    }

    /// @brief Method used as the IOSignalHandler.
    ///
    /// Records the value of the given signal and checks if the desired
    /// number of signals have been received.  If so, the IOService is
    /// stopped which will cause IOService::run() to exit, returning control
    /// to the test.
    ///
    /// @param sequence_id id of the IOSignal received
    void processSignal(IOSignalId sequence_id) {
        // Pop the signal instance off the queue.  This should make us
        // the only one holding it, so when we leave it should be freed.
        IOSignalPtr signal = io_signal_queue_->popSignal(sequence_id);

        // Remember the signal we got.
        processed_signals_.push_back(signal->getSignum());

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
        test_timer_.setup(boost::bind(&IOSignalTest::testTimerHandler,
                                      this),
                          test_time_ms_, asiolink::IntervalTimer::ONE_SHOT);
    }

    /// @brief Failsafe timer expiration handler.
    void testTimerHandler() {
        io_service_->stop();
        FAIL() << "Test Time: " << test_time_ms_ << " expired";
    }
};

// Used for constuctor tests.
void dummyHandler(IOSignalId) {
}

// Tests IOSignal constructor.
TEST(IOSignal, construction) {
    asiolink::IOServicePtr io_service(new asiolink::IOService());
    IOSignalPtr signal;
    IOSignalPtr signal2;

    // Verify that handler cannot be empty.
    ASSERT_THROW(signal.reset(new IOSignal(*io_service, SIGINT,
                                           IOSignalHandler())),
                 IOSignalError);

    // Verify constructor with valid arguments works.
    ASSERT_NO_THROW(signal.reset(new IOSignal(*io_service, SIGINT,
                                              dummyHandler)));
    // Verify sequence_id is set.
    EXPECT_EQ(IOSignal::nextSequenceId()-1, signal->getSequenceId());

    // Verify SIGINT is correct.
    EXPECT_EQ(SIGINT, signal->getSignum());

    // Make a second signal.
    ASSERT_NO_THROW(signal2.reset(new IOSignal(*io_service, SIGUSR1,
                                               dummyHandler)));

    // Verify sequence_id is not the same as the previous one.
    EXPECT_NE(signal2->getSequenceId(), signal->getSequenceId());

    // Verify that the signal value is correct.
    EXPECT_EQ(SIGUSR1, signal2->getSignum());
}

// Tests IOSignalQueue constructors and exercises queuing methods.
TEST(IOSignalQueue, constructionAndQueuing) {
    IOSignalQueuePtr queue;
    asiolink::IOServicePtr io_service;

    // Verify constructing with an empty IOService will throw.
    ASSERT_THROW(queue.reset(new IOSignalQueue(io_service)), IOSignalError);

    // Verify valid construction works.
    io_service.reset(new asiolink::IOService());
    ASSERT_NO_THROW(queue.reset(new IOSignalQueue(io_service)));

    // Verify an empty handler is not allowed.
    ASSERT_THROW(queue->pushSignal(SIGINT, IOSignalHandler()), IOSignalError);

    // Verify that we can queue valid entries.
    std::vector<IOSignalId> ids;
    ASSERT_NO_THROW(ids.push_back(queue->pushSignal(SIGINT, dummyHandler)));
    ASSERT_NO_THROW(ids.push_back(queue->pushSignal(SIGUSR1, dummyHandler)));
    ASSERT_NO_THROW(ids.push_back(queue->pushSignal(SIGUSR2, dummyHandler)));

    // Now verify that we can pop each one and what we pop is correct.
    // Verify popping it again, throws.  We'll do it in a non-sequential order.

    // Check the middle one.
    IOSignalPtr signal;
    ASSERT_NO_THROW(signal = queue->popSignal(ids[1]));
    ASSERT_TRUE(signal);
    EXPECT_EQ(ids[1], signal->getSequenceId());
    EXPECT_EQ(SIGUSR1, signal->getSignum());
    ASSERT_THROW(queue->popSignal(ids[1]), IOSignalError);

    // Check the first one.
    ASSERT_NO_THROW(signal = queue->popSignal(ids[0]));
    ASSERT_TRUE(signal);
    EXPECT_EQ(ids[0], signal->getSequenceId());
    EXPECT_EQ(SIGINT, signal->getSignum());
    ASSERT_THROW(queue->popSignal(ids[0]), IOSignalError);

    // Check the last one.
    ASSERT_NO_THROW(signal = queue->popSignal(ids[2]));
    ASSERT_TRUE(signal);
    EXPECT_EQ(ids[2], signal->getSequenceId());
    EXPECT_EQ(SIGUSR2, signal->getSignum());
    ASSERT_THROW(queue->popSignal(ids[2]), IOSignalError);

    // Now we will test clearing the queue.  Queue three signals.
    ids.clear();
    for (int i = 0; i < 3; ++i) {
        ASSERT_NO_THROW(ids.push_back(queue->pushSignal(SIGINT, dummyHandler)));
    }

    // Now clear the queue.
    ASSERT_NO_THROW(queue->clear());

    // We should not be able to dequeue any of them.
    for (int i = 0; i < 3; ++i) {
        ASSERT_THROW(queue->popSignal(ids[i]), IOSignalError);
    }
}

// Test the basic mechanics of IOSignal by handling one signal occurrence.
TEST_F(IOSignalTest, singleSignalTest) {
    // Set test fail safe.
    setTestTime(1000);

    // Register the onreceipt-handler with SignalSet.
    // We set this up to catch the actual signal.  The onreceipt handler
    // creates an IOSignal which should propagate the signal as a
    // IOService event.
    util::SignalSet::
    setOnReceiptHandler(boost::bind(&IOSignalTest::onReceiptHandler,
                                    this, _1));

    // Register to receive SIGINT.
    ASSERT_NO_THROW(signal_set_.reset(new util::SignalSet(SIGINT)));

    // Use TimedSignal to generate SIGINT 100 ms after we start IOService::run.
    TimedSignal sig_int(*io_service_, SIGINT, 100);

    // The first handler executed is the IOSignal's internal timer expirey
    // callback.
    io_service_->run_one();

    // The next handler executed is IOSignal's handler.
    io_service_->run_one();

    // Verify that we processed the signal.
    ASSERT_EQ(1, processed_signals_.size());

    // Now check that signal value is correct.
    EXPECT_EQ(SIGINT, processed_signals_[0]);
}


// Test verifies that signals can be delivered rapid-fire without falling over.
TEST_F(IOSignalTest, hammer) {
    // Set test fail safe.  We want to allow at least 100 ms per signal,
    // plus a bit more so 6 seconds ought to be enough.
    setTestTime(6000);

    // Register the onreceipt-handler with SignalSet, and register to receive
    // SIGINT.
    util::SignalSet::
    setOnReceiptHandler(boost::bind(&IOSignalTest::onReceiptHandler,
                                    this, _1));
    ASSERT_NO_THROW(signal_set_.reset(new util::SignalSet(SIGINT)));

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

    // Register the onreceipt-handler with SignalSet, and register to
    // receive SIGINT.
    util::SignalSet::
    setOnReceiptHandler(boost::bind(&IOSignalTest::onReceiptHandler,
                                    this, _1));
    ASSERT_NO_THROW(signal_set_.reset(new util::SignalSet(SIGINT)));

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

    // Register the onreceipt-handler with SignalSet, and register to
    // receive SIGINT, SIGUSR1, and SIGUSR2.
    util::SignalSet::
    setOnReceiptHandler(boost::bind(&IOSignalTest::onReceiptHandler,
                                    this, _1));
    ASSERT_NO_THROW(signal_set_.reset(new util::SignalSet(SIGINT, SIGUSR1,
                                      SIGUSR2)));

    // Stop the test after 21 signals.  Needs to be a multiple of 3.
    stop_at_count_ = 21;

    // User a repeating TimedSignal so we should generate a signal every 1 ms
    // until we hit our stop count.
    TimedSignal sig_1(*io_service_, SIGINT, 1,
                      asiolink::IntervalTimer::REPEATING);
    TimedSignal sig_2(*io_service_, SIGUSR1, 1,
                      asiolink::IntervalTimer::REPEATING);
    TimedSignal sig_3(*io_service_, SIGUSR2, 1,
                      asiolink::IntervalTimer::REPEATING);

    // Start processing IO.  This should continue until we stop either by
    // hitting the stop count or if things go wrong, max test time.
    io_service_->run();

    // Verify we received the expected number of signals.
    ASSERT_EQ(stop_at_count_, processed_signals_.size());

    // There is no gaurantee that the signals will always be delivered in the
    // order they are raised, but all of them should get delievered.  Loop
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
    EXPECT_EQ(sigint_cnt, (stop_at_count_/3));
    EXPECT_EQ(sigusr1_cnt, (stop_at_count_/3));
    EXPECT_EQ(sigusr2_cnt, (stop_at_count_/3));
}

}; // end of isc::d2 namespace
}; // end of isc namespace
