// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <util/signal_set.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <util/unittests/test_exceptions.h>
#include <signal.h>

namespace {

using namespace isc;
using namespace isc::util;

/// @brief Test fixture class for @c isc::util::SignalSet class.
///
/// This class contains a handler function which records the signal
/// being handled. It allows for checking whether the signal set
/// has invoked the handler for the expected signal.
class SignalSetTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Resets the signal sets and variables being modified by the
    /// signal handler function.
    SignalSetTest()
        : signal_set_(),
          secondary_signal_set_(),
          onreceipt_trues_(0) {
        handler_calls_ = 0;
        signum_ = -1;
    }

    /// @brief Destructor.
    ///
    /// Uninstalls the signals from the signal sets.
    ~SignalSetTest() {
        if (signal_set_) {
            signal_set_->clear();
        }
        if (secondary_signal_set_) {
            secondary_signal_set_->clear();
        }
    }

    /// @brief Deferred processing signal handler used by unit tests.
    ///
    /// @param signum Signal being handled.
    static void testHandler(int signum) {
        signum_ = signum;
        ++handler_calls_;
    }

    /// @brief Immediate processing signal handler used by unit tests.
    ///
    /// The handler processes only SIGHUP.  All others will pass through.
    ///
    /// @param signum Signal being handled.
    /// @return Boolean true if the handler has processed the signal, false
    /// otherwise.
    bool onReceiptHandler(int signum) {
        if (signum == SIGHUP) {
            ++onreceipt_trues_;
            return (true);
        }

        return (false);
    }

    /// @brief Number of handler calls so far.
    static int handler_calls_;
    /// @brief The last signal handled.
    static int signum_;
    /// @brief Test signal set object.
    SignalSetPtr signal_set_;
    /// @brief Second signal set object.
    SignalSetPtr secondary_signal_set_;
    /// @brief Number of true returns from onReceiptHandler so far.
    int onreceipt_trues_;
};

int SignalSetTest::handler_calls_ = 0;
int SignalSetTest::signum_ = -1;

/// Check that the signals are recorded by the signal handlers.
TEST_F(SignalSetTest, twoSignals) {
    // Register handlers for two signals.
    ASSERT_NO_THROW(signal_set_.reset(new SignalSet(SIGHUP, SIGINT)));
    // Send SIGHUP signal to the process.
    ASSERT_EQ(0, raise(SIGHUP));
    // The SIGHUP should be the next one in the queue to be handled.
    EXPECT_EQ(SIGHUP, signal_set_->getNext());
    // But, no handlers should have been called yet.
    EXPECT_EQ(0, handler_calls_);
    // Send a different signal.
    ASSERT_EQ(0, raise(SIGINT));
    // The SIGHUP hasn't been handled yet so it should still be the first
    // one in the queue.
    EXPECT_EQ(SIGHUP, signal_set_->getNext());
    // No handlers have been called yet.
    EXPECT_EQ(0, handler_calls_);
    // Raise another SIGHUP before the first one has been handled. The
    // second one should be dropped.
    ASSERT_EQ(0, raise(SIGHUP));
    // Execute the first handler (for SIGHUP).
    signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler, _1));
    // The handler should have been called once and the signal
    // handled should be SIGHUP.
    EXPECT_EQ(1, handler_calls_);
    EXPECT_EQ(SIGHUP, signum_);
    // Next signal to be handled should be SIGINT.
    EXPECT_EQ(SIGINT, signal_set_->getNext());
    signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler, _1));
    EXPECT_EQ(2, handler_calls_);
    EXPECT_EQ(SIGINT, signum_);
    // There should be no more waiting handlers.
    EXPECT_EQ(-1, signal_set_->getNext());
    // Make sure that signals can be unregistered.
    EXPECT_NO_THROW(signal_set_->remove(SIGHUP));
    EXPECT_NO_THROW(signal_set_->remove(SIGINT));
}

/// Check that the signal set can only handle signals owned by it.
TEST_F(SignalSetTest, twoSignalSets) {
    // Register handler for SIGHUP in the first signal set.
    signal_set_.reset(new SignalSet(SIGHUP));
    // Register handler for SIGINT in the second signal set.
    secondary_signal_set_.reset(new SignalSet(SIGINT));
    // Send SIGHUP.
    ASSERT_EQ(0, raise(SIGHUP));
    // Send SIGINT.
    ASSERT_EQ(0, raise(SIGINT));
    // Although the SIGHUP is the first signal received by the process
    // it is not owned by the secondary signal set. The first signal
    // to be handled by the secondary signal set is SIGINT.
    EXPECT_EQ(SIGINT, secondary_signal_set_->getNext());
    // The signal set owns SIGHUP so it should be the next to handle.
    EXPECT_EQ(SIGHUP, signal_set_->getNext());
    // Handle next signal owned by the secondary signal set.
    secondary_signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler,
                                                  _1));
    EXPECT_EQ(1, handler_calls_);
    EXPECT_EQ(SIGINT, signum_);
    // No more signals to be handled for this signal set.
    EXPECT_EQ(-1, secondary_signal_set_->getNext());
    // Handle next signal owned by the signal set.
    signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler, _1));
    EXPECT_EQ(2, handler_calls_);
    EXPECT_EQ(SIGHUP, signum_);
    // No more signals to be handled by this signal set.
    EXPECT_EQ(-1, signal_set_->getNext());
}

// Check that each signal set removes only the signals that it has been used
// to register.
TEST_F(SignalSetTest, remove) {
    // Register handlers for SIGHUP using one signal set.
    ASSERT_NO_THROW(signal_set_.reset(new SignalSet(SIGHUP)));
    // Define another signal set and register a different signal.
    ASSERT_NO_THROW(secondary_signal_set_.reset(new SignalSet(SIGINT)));
    // The SIGHUP has been already registered with the other signal
    // set, so it should not be possible to register it again.
    ASSERT_THROW_WITH(secondary_signal_set_->add(SIGHUP), SignalSetError,
                      "attempt to register a duplicate signal " << SIGHUP);
    // It shouldn't be possible to remove the signal registered in a different
    // signal set.
    ASSERT_THROW_WITH(secondary_signal_set_->remove(SIGHUP), SignalSetError,
                      "failed to unregister signal " << SIGHUP
                      << ": this signal is not owned by the signal set");
    // Remove all signals from the first signal set. The signals registered
    // with the other signal signal set should be preserved.
    ASSERT_NO_THROW(signal_set_->clear());
    // Check indirectly that the SIGINT is still registered. An attempt to
    // register registered signal should result in failure.
    EXPECT_THROW_WITH(secondary_signal_set_->add(SIGINT), SignalSetError,
                      "attempt to register a duplicate signal "<< SIGINT);
    // But, we should be able to register SIGHUP.
    EXPECT_NO_THROW(secondary_signal_set_->add(SIGHUP));
}

/// Check that it is not possible to duplicate signals.
TEST_F(SignalSetTest, duplicates) {
    ASSERT_NO_THROW(signal_set_.reset(new SignalSet(SIGHUP)));
    // It shouldn't be possible to register the same signal.
    EXPECT_THROW_WITH(signal_set_->add(SIGHUP), SignalSetError,
                      "attempt to register a duplicate signal "<< SIGHUP);
    // But ok to register a different one.
    EXPECT_NO_THROW(signal_set_->add(SIGTERM));
    // Now, let's define other signal set.
    SignalSetPtr other;
    // SIGINT hasn't been registered in the first signal set
    // so it should be fine to register.
    ASSERT_NO_THROW(other.reset(new SignalSet(SIGINT)));
    // SIGHUP has been already registered in the first signal set so
    // an attempt to register it again should result in a failure.
    EXPECT_THROW_WITH(other->add(SIGHUP), SignalSetError,
                      "attempt to register a duplicate signal "<< SIGHUP);
}

/// Check that on-receipt processing works.
TEST_F(SignalSetTest, onReceiptTests) {
    // Install an on-receipt handler.
    SignalSet::setOnReceiptHandler(boost::bind(&SignalSetTest::onReceiptHandler,
                                               this, _1));
    // Create a SignalSet for SIGHUP and SIGUSR1.
    ASSERT_NO_THROW(signal_set_.reset(new SignalSet(SIGHUP, SIGUSR1)));

    // Generate SIGHUP, which the on-receipt handler should process.
    // Verify that the on-receipt handler processed the signal and that
    // no signals are pending.
    ASSERT_EQ(0, raise(SIGHUP));
    EXPECT_EQ(1, onreceipt_trues_);
    EXPECT_EQ(-1, signal_set_->getNext());

    // Generate SIGHUP, which the on-receipt handler should NOT process.
    // Verify the on-receipt handler did not the signal and that SIGUSR1
    // is pending.
    ASSERT_EQ(0, raise(SIGUSR1));
    EXPECT_EQ(1, onreceipt_trues_);
    EXPECT_EQ(SIGUSR1, signal_set_->getNext());

    // Verify we can process SIGUSR1 with the deferred handler.
    signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler, _1));
    EXPECT_EQ(1, handler_calls_);
    EXPECT_EQ(SIGUSR1, signum_);

    // Unregister the on-receipt handler.
    SignalSet::clearOnReceiptHandler();

    // Generate SIGHUP.
    // Verify that the on-receipt handler did not process the signal, and
    // that SIGHUP is pending.
    ASSERT_EQ(0, raise(SIGHUP));
    EXPECT_EQ(1, onreceipt_trues_);
    EXPECT_EQ(SIGHUP, signal_set_->getNext());

    // Verify we can process it with deferred handler.
    signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler, _1));
    EXPECT_EQ(2, handler_calls_);
    EXPECT_EQ(SIGHUP, signum_);
}

} // end of anonymous namespace
