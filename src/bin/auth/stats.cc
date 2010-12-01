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

#include <boost/bind.hpp>

#include <auth/stats.h>

#include <cc/data.h>

#include <sstream>
#include <iostream>

namespace statistics {

class CounterImpl {
private:
    // prohibit copy
    CounterImpl(const CounterImpl& source);
    CounterImpl& operator=(const CounterImpl& source);
public:
    CounterImpl(const bool& verbose_mode);
    ~CounterImpl();
    void inc(const Counter::CounterType type);
    asio_link::IntervalTimer::Callback getCallback();
    void sendStats();
    void setStatsSession(isc::cc::AbstractSession* stats_session);
private:
    std::vector<uint64_t>* counters_;
    isc::cc::AbstractSession* stats_session_;
    const bool& verbose_mode_;
};

CounterImpl::CounterImpl(const bool& verbose_mode) :
    // initialize counter
    // size: Counter::COUNTER_TYPES, initial value: 0
    stats_session_(NULL),
    verbose_mode_(verbose_mode)
{
    counters_ = new std::vector<uint64_t>(Counter::COUNTER_TYPES, 0);
}

CounterImpl::~CounterImpl() {
    delete counters_;
}

void
CounterImpl::inc(const Counter::CounterType type) {
    ++counters_->at(type);
}

asio_link::IntervalTimer::Callback
CounterImpl::getCallback() {
    return (boost::bind(&CounterImpl::sendStats, this));
}

void
CounterImpl::sendStats() {
    if (stats_session_ == NULL) {
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "session interface for statistics"
                      << " is not available" << std::endl;
        }
        return;
    }
    std::stringstream strstats;
    strstats << "{\"command\": [\"set\","
             <<   "{ \"stats_data\": "
             <<     "{ \"auth.queries.udp\": "
             <<     counters_->at(Counter::COUNTER_UDP)
             <<     ", \"auth.queries.tcp\": "
             <<     counters_->at(Counter::COUNTER_TCP)
             <<   " }"
             <<   "}"
             << "]}";
    isc::data::ConstElementPtr set_stats =
        isc::data::Element::fromJSON(strstats);
    try {
        // group_recvmsg() will time out in MSGQ_DEFAULT_TIMEOUT.
        // On timeout or error, an exception will be thrown
        const int seq =
            stats_session_->group_sendmsg(set_stats, "Stats");
        isc::data::ConstElementPtr env, answer;
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "send statistics data to b10-stats"
                      << std::endl;
        }
        // TODO: parse and check response from b10-stats
        // currently it just returns empty message
        stats_session_->group_recvmsg(env, answer, false, seq);
    } catch (const isc::Exception& ex) {
        // catch the exception and do nothing.
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "failed to send statistics data to b10-stats: "
                      << ex.what() << std::endl;
        }
    }
    return;
}

void
CounterImpl::setStatsSession(isc::cc::AbstractSession* stats_session) {
    stats_session_ = stats_session;
}

Counter::Counter(const bool& verbose_mode) :
    impl_(new CounterImpl(verbose_mode))
{}

Counter::~Counter() {
    delete impl_;
}

asio_link::IntervalTimer::Callback
Counter::getCallback() {
    return (impl_->getCallback());
}

void
Counter::inc(const Counter::CounterType type) {
    impl_->inc(type);
}

void
Counter::setStatsSession(isc::cc::AbstractSession* stats_session) {
    impl_->setStatsSession(stats_session);
}

} // statistics
