// Copyright (C) 2011-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

namespace isc {
namespace asiolink {

/// This class holds a call back function of asynchronous operations.
/// To ensure the object is alive while an asynchronous operation refers
/// to it, we use shared_ptr and enable_shared_from_this.
/// The object will be destructed in case IntervalTimer has been destructed
/// and no asynchronous operation refers to it.
/// Please follow the link to get an example:
/// http://think-async.com/asio/asio-1.4.8/doc/asio/tutorial/tutdaytime3.html#asio.tutorial.tutdaytime3.the_tcp_connection_class
class IntervalTimerImpl :
    public boost::enable_shared_from_this<IntervalTimerImpl>
{
private:
    // prohibit copy
    IntervalTimerImpl(const IntervalTimerImpl& source);
    IntervalTimerImpl& operator=(const IntervalTimerImpl& source);
public:
    IntervalTimerImpl(IOService& io_service);
    ~IntervalTimerImpl();
    void setup(const IntervalTimer::Callback& cbfunc, const long interval,
               const IntervalTimer::Mode& interval_mode
               = IntervalTimer::REPEATING);
    void callback(const boost::system::error_code& error);
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
    boost::asio::deadline_timer timer_;

    // Controls how the timer behaves after expiration.
    IntervalTimer::Mode mode_;

    // interval_ will be set to this value in destructor in order to detect
    // use-after-free type of bugs.
    static const long INVALIDATED_INTERVAL = -1;
};

IntervalTimerImpl::IntervalTimerImpl(IOService& io_service) :
    interval_(0), timer_(io_service.get_io_service()),
    mode_(IntervalTimer::REPEATING)
{}

IntervalTimerImpl::~IntervalTimerImpl() {
    interval_ = INVALIDATED_INTERVAL;
}

void
IntervalTimerImpl::setup(const IntervalTimer::Callback& cbfunc,
                         const long interval,
                         const IntervalTimer::Mode& mode)
{
    // Interval should not be less than 0.
    if (interval < 0) {
        isc_throw(isc::BadValue, "Interval should not be less than or "
                                 "equal to 0");
    }
    // Call back function should not be empty.
    if (cbfunc.empty()) {
        isc_throw(isc::InvalidParameter, "Callback function is empty");
    }
    cbfunc_ = cbfunc;
    interval_ = interval;
    mode_ = mode;

    // Set initial expire time.
    // At this point the timer is not running yet and will not expire.
    // After calling IOService::run(), the timer will expire.
    update();
}

void
IntervalTimerImpl::update() {
    try {
        // Update expire time to (current time + interval_).
        timer_.expires_from_now(boost::posix_time::millisec(interval_));
        // Reset timer.
        // Pass a function bound with a shared_ptr to this.
        timer_.async_wait(boost::bind(&IntervalTimerImpl::callback,
                                      shared_from_this(),
                                      boost::asio::placeholders::error));
    } catch (const boost::system::system_error& e) {
        isc_throw(isc::Unexpected, "Failed to update timer: " << e.what());
    } catch (const boost::bad_weak_ptr&) {
        // Can't happen. It means a severe internal bug.
        assert(0);
    }
}

void
IntervalTimerImpl::callback(const boost::system::error_code& ec) {
    assert(interval_ != INVALIDATED_INTERVAL);
    if (interval_ == 0 || ec) {
        // timer has been canceled. Do nothing.
    } else {
        // If we should repeat, set next expire time.
        if (mode_ == IntervalTimer::REPEATING) {
            update();
        }

        // Invoke the call back function.
        cbfunc_();
    }
}

IntervalTimer::IntervalTimer(IOService& io_service) :
    impl_(new IntervalTimerImpl(io_service))
{}

IntervalTimer::~IntervalTimer() {
    // Cancel the timer to make sure cbfunc_() will not be called any more.
    cancel();
}

void
IntervalTimer::setup(const Callback& cbfunc, const long interval,
                     const IntervalTimer::Mode& mode) {
    return (impl_->setup(cbfunc, interval, mode));
}

void
IntervalTimer::cancel() {
    impl_->cancel();
}

long
IntervalTimer::getInterval() const {
    return (impl_->getInterval());
}

} // namespace asiolink
} // namespace isc
