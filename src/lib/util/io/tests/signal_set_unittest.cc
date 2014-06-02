// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <util/io/signal_set.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <signal.h>

namespace {

using namespace isc;
using namespace isc::util::io;

class SignalSetTest : public ::testing::Test {
public:

    SignalSetTest() {
        handler_calls_ = 0;
        signum_ = -1;
    }

    ~SignalSetTest() {
        if (signal_set_) {
            signal_set_->clear();
        }
    }

    void handleNext() {
        signal_set_->handleNext(boost::bind(&SignalSetTest::testHandler, _1));
    }

    static void testHandler(int signum) {
        signum_ = signum;
        ++handler_calls_;
    }

    static int handler_calls_;
    static int signum_;
    boost::shared_ptr<SignalSet> signal_set_;

};

int SignalSetTest::handler_calls_ = 0;
int SignalSetTest::signum_ = -1;

TEST_F(SignalSetTest, twoSignals) {
    // Register handlers for two signals.
    signal_set_.reset(new SignalSet(SIGHUP, SIGINT));
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
    handleNext();
    // The handler should have been called once and the signal
    // handled should be SIGHUP.
    EXPECT_EQ(1, handler_calls_);
    EXPECT_EQ(SIGHUP, signum_);
    // Next signal to be handled should be SIGINT.
    EXPECT_EQ(SIGINT, signal_set_->getNext());
    handleNext();
    EXPECT_EQ(2, handler_calls_);
    EXPECT_EQ(SIGINT, signum_);
    // There should be no more waiting handlers.
    EXPECT_EQ(-1, signal_set_->getNext());
    // Make sure that signals can be unregistered.
    EXPECT_NO_THROW(signal_set_->remove(SIGHUP));
    EXPECT_NO_THROW(signal_set_->remove(SIGINT));
}


} // end of anonymous namespace
