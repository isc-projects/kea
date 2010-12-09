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

class QueryCountersImpl;

/// \brief Set of query counters.
///
/// \c QueryCounters is set of query counters class. It holds query counters
/// and provides an interface to increment the counter of specified
/// type (e.g. UDP query, TCP query).
///
/// This class also provides a function to send statistics information to
/// statistics module.
///
/// This class is designed to be a part of \c AuthSrv.
/// Call \c setStatsSession() to set a session to communicate with statistics
/// module like Xfrin session.
/// Call \c inc() to increment a counter for specific type of query in
/// the query processing function. use \c enum \c QueryCounterType to specify
/// the type of query.
/// Call \c submitStatistics() to submit statistics information to statistics
/// module with stats_session, periodically or at a time the command
/// \c sendstats is received.
///
/// This class uses pimpl idiom and hides detailed implementation.
/// This class is constructed on startup of the server, so
/// construction overhead of this approach should be acceptable.
///
/// \todo Hold counters for each query types (Notify, Axfr, Ixfr, Normal)
/// \todo Consider overhead of \c QueryCounters::inc()
class QueryCounters {
private:
    QueryCountersImpl* impl_;
public:
    // Enum for the type of counter
    enum QueryCounterType {
        COUNTER_UDP = 0,  ///< COUNTER_UDP: counter for UDP queries
        COUNTER_TCP = 1,  ///< COUNTER_TCP: counter for TCP queries
        COUNTER_TYPES = 2 ///< The number of defined counters
    };
    /// The constructor.
    ///
    /// \param verbose_mode reference to verbose_mode_ of AuthSrvImpl
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \todo Fix this short term workaround for logging
    /// after we have logging framework.
    ///
    QueryCounters(const bool& verbose_mode);
    /// The destructor.
    ///
    /// This method never throws an exception.
    ///
    ~QueryCounters();

    /// \brief Increment the counter specified by the parameter.
    ///
    /// \param type Type of a counter to increment.
    ///
    /// \throw isc::InvalidParameter the type is unknown.
    ///
    /// usage: counter.inc(QueryCounterType::COUNTER_UDP);
    /// 
    void inc(const QueryCounterType type);

    /// \brief Submit statistics counters to statistics module.
    ///
    /// This method is desinged to be called periodically
    /// with \c asio_link::StatisticsSendTimer, or arbitrary
    /// by the command 'sendstats'.
    ///
    /// Note: Set the session to communicate with statistics module
    /// by \c setStatsSession() before calling \c submitStatistics().
    ///
    /// This method is mostly exception free (error conditions are
    /// represented via the return value). But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \return true on success, false on error.
    ///
    /// \todo Do not block query handling while submitting statistics data.
    ///
    bool submitStatistics() const;

    /// \brief Set the session to communicate with Statistics
    /// module.
    ///
    /// This method never throws an exception.
    ///
    /// Note: this interface is tentative.  We'll revisit the ASIO and session
    /// frameworks, at which point the session will probably be passed on
    /// construction of the server.
    ///
    /// Ownership isn't transferred: the caller is responsible for keeping
    /// this object to be valid while the server object is working and for
    /// disconnecting the session and destroying the object when the server
    /// is shutdown.
    ///
    /// \param stats_session A pointer to the session
    ///
    void setStatsSession(isc::cc::AbstractSession* stats_session);

    /// \brief Get a reference to the counters in the QueryCounters.
    ///
    /// This function returns a refetence to the counters.
    /// This method never throws an exception.
    ///
    /// Note: Currently this function is for testing purpose only.
    /// This function should not be called except from tests.
    ///
    /// \return a reference to the counters.
    ///
    const std::vector<uint64_t>& getCounters() const;
};

#endif // __STATS_H

// Local Variables:
// mode: c++
// End:
