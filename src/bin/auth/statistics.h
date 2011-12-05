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

#ifndef __STATISTICS_H
#define __STATISTICS_H 1

#include <cc/session.h>
#include <stdint.h>
#include <boost/scoped_ptr.hpp>

class AuthCountersImpl;

/// \brief Set of query counters.
///
/// \c AuthCounters is set of query counters class. It holds query counters
/// and provides an interface to increment the counter of specified type
/// (e.g. UDP query, TCP query).
///
/// This class also provides a function to send statistics information to
/// statistics module.
///
/// This class is designed to be a part of \c AuthSrv.
/// Call \c setStatisticsSession() to set a session to communicate with
/// statistics module like Xfrin session.
/// Call \c inc() to increment a counter for specific type of query in
/// the query processing function. use \c enum \c CounterType to specify
/// the type of query.
/// Call \c submitStatistics() to submit statistics information to statistics
/// module with statistics_session, periodically or at a time the command
/// \c sendstats is received.
///
/// We may eventually want to change the structure to hold values that are
/// not counters (such as concurrent TCP connections), or seperate generic
/// part to src/lib to share with the other modules.
///
/// This class uses pimpl idiom and hides detailed implementation.
/// This class is constructed on startup of the server, so
/// construction overhead of this approach should be acceptable.
///
/// \todo Hold counters for each query types (Notify, Axfr, Ixfr, Normal)
/// \todo Consider overhead of \c AuthCounters::inc()
class AuthCounters {
private:
    boost::scoped_ptr<AuthCountersImpl> impl_;
public:
    // Enum for the type of counter
    enum ServerCounterType {
        SERVER_UDP_QUERY,       ///< SERVER_UDP_QUERY: counter for UDP queries
        SERVER_TCP_QUERY,       ///< SERVER_TCP_QUERY: counter for TCP queries
        SERVER_COUNTER_TYPES    ///< The number of defined counters
    };
    enum PerZoneCounterType {
        ZONE_UDP_QUERY,         ///< ZONE_UDP_QUERY: counter for UDP queries
        ZONE_TCP_QUERY,         ///< ZONE_TCP_QUERY: counter for TCP queries
        PER_ZONE_COUNTER_TYPES  ///< The number of defined counters
    };
    /// The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    AuthCounters();
    /// The destructor.
    ///
    /// This method never throws an exception.
    ///
    ~AuthCounters();

    /// \brief Increment the counter specified by the parameter.
    ///
    /// \param type Type of a counter to increment.
    ///
    /// \throw std::out_of_range \a type is unknown.
    ///
    /// usage: counter.inc(CounterType::COUNTER_UDP_QUERY);
    /// 
    void inc(const ServerCounterType type);

    /// \brief Submit statistics counters to statistics module.
    ///
    /// This method is desinged to be called periodically
    /// with \c asio_link::StatisticsSendTimer, or arbitrary
    /// by the command 'sendstats'.
    ///
    /// Note: Set the session to communicate with statistics module
    /// by \c setStatisticsSession() before calling \c submitStatistics().
    ///
    /// This method is mostly exception free (error conditions are
    /// represented via the return value). But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \return true on success, false on error.
    ///
    /// \todo Do not block message handling in auth_srv while submitting
    /// statistics data.
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
    /// \param statistics_session A pointer to the session
    ///
    void setStatisticsSession(isc::cc::AbstractSession* statistics_session);

    /// \brief Get a value of a counter in the AuthCounters.
    ///
    /// This function returns a value of the counter specified by \a type.
    /// This method never throws an exception.
    ///
    /// Note: Currently this function is for testing purpose only.
    ///
    /// \param type Type of a counter to get the value of
    ///
    /// \return the value of the counter specified by \a type.
    ///
    uint64_t getCounter(const AuthCounters::ServerCounterType type) const;
};

#endif // __STATISTICS_H

// Local Variables:
// mode: c++
// End:
