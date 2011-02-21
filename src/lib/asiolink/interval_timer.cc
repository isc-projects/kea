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

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>

#include <exceptions/exceptions.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>

#include <boost/bind.hpp>

namespace asiolink {

class IntervalTimerImpl {
private:
    // prohibit copy
    IntervalTimerImpl(const IntervalTimerImpl& source);
    IntervalTimerImpl& operator=(const IntervalTimerImpl& source);
public:
    IntervalTimerImpl(IOService& io_service);
    ~IntervalTimerImpl();
    void setup(const IntervalTimer::Callback& cbfunc, const long interval);
    void callback(const asio::error_code& error);
    void cancel() {
        timer_.cancel();
        interval_ = 0;
    }
    long getInterval() const { return (interval_); }
private:
    // a function to update timer_ when it expires
    void update();
    // a function to call back when timer_ expires
    IntervalTimer::Callback cbfunc_;
    // interval in milliseconds
    long interval_;
    // asio timer
    asio::deadline_timer timer_;
};

IntervalTimerImpl::IntervalTimerImpl(IOService& io_service) :
    interval_(0), timer_(io_service.get_io_service())
{}

IntervalTimerImpl::~IntervalTimerImpl()
{}

void
IntervalTimerImpl::setup(const IntervalTimer::Callback& cbfunc,
                         const long interval)
{
    // Interval should not be less than or equal to 0.
    if (interval <= 0) {
        isc_throw(isc::BadValue, "Interval should not be less than or "
                                 "equal to 0");
    }
    // Call back function should not be empty.
    if (cbfunc.empty()) {
        isc_throw(isc::InvalidParameter, "Callback function is empty");
    }
    cbfunc_ = cbfunc;
    interval_ = interval;
    // Set initial expire time.
    // At this point the timer is not running yet and will not expire.
    // After calling IOService::run(), the timer will expire.
    update();
    return;
}

void
IntervalTimerImpl::update() {
    if (interval_ == 0) {
        // timer has been canceled.  Do nothing.
        return;
    }
    try {
        // Update expire time to (current time + interval_).
        timer_.expires_from_now(boost::posix_time::millisec(interval_));
    } catch (const asio::system_error& e) {
        isc_throw(isc::Unexpected, "Failed to update timer");
    }
    // Reset timer.
    timer_.async_wait(boost::bind(&IntervalTimerImpl::callback, this, _1));
}

void
IntervalTimerImpl::callback(const asio::error_code& cancelled) {
    // Do not call cbfunc_ in case the timer was cancelled.
    // The timer will be canelled in the destructor of asio::deadline_timer.
    if (!cancelled) {
        cbfunc_();
        // Set next expire time.
        update();
    }
}

IntervalTimer::IntervalTimer(IOService& io_service) {
    impl_ = new IntervalTimerImpl(io_service);
}

IntervalTimer::~IntervalTimer() {
    delete impl_;
}

void
IntervalTimer::setup(const Callback& cbfunc, const long interval) {
    return (impl_->setup(cbfunc, interval));
}

void
IntervalTimer::cancel() {
    impl_->cancel();
}

long
IntervalTimer::getInterval() const {
    return (impl_->getInterval());
}

}
