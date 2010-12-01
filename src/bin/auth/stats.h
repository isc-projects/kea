// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __STATS_H
#define __STATS_H 1

#include <boost/function.hpp>

#include <cc/session.h>

/// for asio_link::IntervalTimer::Callback
#include <auth/asio_link.h>

namespace statistics {

class CounterImpl;

/// \brief A query counter.
///
/// \c Counter is a query counter class. It holds query counter
/// and provide an interface to increment the counter.
/// This class also provides a function to send information to
/// statistics (b10-stats).
///
/// This class uses pimpl idiom and hides detailed implementation.
/// This class is constructed on startup of the server, so
/// construction overhead of this approach should be acceptable.
class Counter {
private:
    CounterImpl* impl_;
public:
    // Enum for the type of counter
    // COUNTER_UDP: counter for UDP queries
    // COUNTER_TCP: counter for TCP queries
    enum CounterType {
        COUNTER_UDP = 0,
        COUNTER_TCP = 1,
        COUNTER_TYPES = 2
    };
    /// The constructor.
    ///
    /// verbose_mode references verbose_mode_ of AuthSrvImpl
    Counter(const bool& verbose_mode);
    /// The destructor.
    ~Counter();

    /// \brief Increment the counter specified by the parameter
    ///
    /// \param type Type of a counter to increment
    /// usage: counter->inc(CounterType::COUNTER_DUP);
    /// 
    void inc(const CounterType type);

    /// \brief Get the function to send statistics information
    /// to Statistics module
    ///
    /// The returned function is inteneded to be called
    /// perioically.
    ///
    /// \return \c asio_link::IntervalTimer::Callback points
    /// to a function to send statistics
    asio_link::IntervalTimer::Callback getCallback();

    /// \brief Set the session to communicate with Statistics
    /// module
    ///
    /// \param stats_session A pointer to the session
    void setStatsSession(isc::cc::AbstractSession* stats_session);
};

} // statistics

#endif // __STATS_H
