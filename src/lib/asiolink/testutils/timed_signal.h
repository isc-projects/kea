// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TIMED_SIGNAL_H
#define TIMED_SIGNAL_H

#include <config.h>

#include <asiolink/interval_timer.h>
#include <signal.h>
#include <gtest/gtest.h>

namespace isc {
namespace asiolink {
namespace test {

/// @brief Implements a time-delayed signal
///
/// Given an IOService, a signal number, and a time period, this class will
/// send (raise) the signal to the current process.
class TimedSignal {
public:
    /// @brief Constructor
    ///
    /// @param io_service  IOService to run the timer
    /// @param signum OS signal value (e.g. SIGHUP, SIGUSR1 ...)
    /// @param milliseconds time in milliseconds to wait until the signal is
    /// raised.
    /// @param mode selects between a one-shot signal or a signal which repeats
    /// at "milliseconds" interval.
    TimedSignal(asiolink::IOService& io_service, int signum, int milliseconds,
                const asiolink::IntervalTimer::Mode& mode =
                asiolink::IntervalTimer::ONE_SHOT)
        : timer_(new asiolink::IntervalTimer(io_service)) {
        timer_->setup(SendSignalCallback(signum), milliseconds, mode);
    }

    /// @brief Cancels the given timer.
    void cancel() {
        if (timer_) {
            timer_->cancel();
        }
    }

    /// @brief Destructor.
    ~TimedSignal() {
        cancel();
    }

    /// @brief Callback for the TimeSignal's internal timer.
    class SendSignalCallback {
    public:

        /// @brief Constructor
        ///
        /// @param signum OS signal value of the signal to send
        SendSignalCallback(int signum) : signum_(signum) {
        }

        /// @brief Callback method invoked when the timer expires
        ///
        /// Calls raise with the given signal which should generate that
        /// signal to the given process.
        void operator()() {
            ASSERT_EQ(0, raise(signum_));
            return;
        }

    private:
        /// @brief Stores the OS signal value to send.
        int signum_;
    };

private:
    /// @brief Timer which controls when the signal is sent.
    asiolink::IntervalTimerPtr timer_;
};

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc

#endif // TIMED_SIGNAL_H
