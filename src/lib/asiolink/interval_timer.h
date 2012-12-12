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

#ifndef ASIOLINK_INTERVAL_TIMER_H
#define ASIOLINK_INTERVAL_TIMER_H 1

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <asiolink/io_service.h>

namespace isc {
namespace asiolink {

class IntervalTimerImpl;

/// \brief The \c IntervalTimer class is a wrapper for the ASIO
/// \c asio::deadline_timer class.
///
/// This class is implemented to use \c asio::deadline_timer as interval
/// timer.
///
/// \c setup() sets a timer to expire on (now + interval) and a call back
/// function.
///
/// \c IntervalTimerImpl::callback() is called by the timer when it expires.
///
/// The function calls the call back function set by \c setup() and updates
/// the timer to expire in (now + interval) milliseconds.
/// The type of call back function is \c void(void).
///
/// The call back function will not be called if the instance of this class is
/// destroyed before the timer is expired.
///
/// Sample code:
/// \code
///  void function_to_call_back() {
///      // this function will be called periodically
///  }
///  int interval_in_milliseconds = 1000;
///  IOService io_service;
///
///  IntervalTimer intervalTimer(io_service);
///  intervalTimer.setup(function_to_call_back, interval_in_milliseconds);
///  io_service.run();
/// \endcode
class IntervalTimer {
public:
    /// \name The type of timer callback function
    typedef boost::function<void()> Callback;

    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IntervalTimer(const IntervalTimer& source);
    IntervalTimer& operator=(const IntervalTimer& source);
public:
    /// \brief The constructor with \c IOService.
    ///
    /// This constructor may throw a standard exception if
    /// memory allocation fails inside the method.
    /// This constructor may also throw \c asio::system_error.
    ///
    /// \param io_service A reference to an instance of IOService
    IntervalTimer(IOService& io_service);

    /// \brief The destructor.
    ///
    /// This destructor never throws an exception.
    ///
    /// On the destruction of this class the timer will be canceled
    /// inside \c asio::deadline_timer.
    ~IntervalTimer();
    //@}

    /// \brief Register timer callback function and interval.
    ///
    /// This function sets callback function and interval in milliseconds.
    /// Timer will actually start after calling \c IOService::run().
    ///
    /// \param cbfunc A reference to a function \c void(void) to call back
    /// when the timer is expired (should not be an empty functor)
    /// \param interval Interval in milliseconds (greater than 0)
    ///
    /// Note: IntervalTimer will not pass \c asio::error_code to
    /// call back function. In case the timer is canceled, the function
    /// will not be called.
    ///
    /// \throw isc::InvalidParameter cbfunc is empty
    /// \throw isc::BadValue interval is less than or equal to 0
    /// \throw isc::Unexpected internal runtime error
    void setup(const Callback& cbfunc, const long interval);

    /// Cancel the timer.
    ///
    /// If the timer has been set up, this method cancels any asynchronous
    /// events waiting on the timer and stops the timer itself.
    /// If the timer has already been canceled, this method effectively does
    /// nothing.
    ///
    /// This method never throws an exception.
    void cancel();

    /// Return the timer interval.
    ///
    /// This method returns the timer interval in milliseconds if it's running;
    /// if the timer has been canceled it returns 0.
    ///
    /// This method never throws an exception.
    long getInterval() const;

private:
    boost::shared_ptr<IntervalTimerImpl> impl_;
};

} // namespace asiolink
} // namespace isc
#endif // ASIOLINK_INTERVAL_TIMER_H
