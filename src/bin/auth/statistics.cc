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

#include <auth/statistics.h>

#include <cc/data.h>
#include <cc/session.h>

#include <sstream>
#include <iostream>

// TODO: We need a namespace ("auth_server"?) to hold
// AuthSrv and QueryCounters.

class QueryCountersImpl {
private:
    // prohibit copy
    QueryCountersImpl(const QueryCountersImpl& source);
    QueryCountersImpl& operator=(const QueryCountersImpl& source);
public:
    // References verbose_mode flag in AuthSrvImpl
    // TODO: Fix this short term workaround for logging
    // after we have logging framework
    QueryCountersImpl(const bool& verbose_mode);
    ~QueryCountersImpl();
    void inc(const QueryCounters::QueryCounterType type);
    bool submitStatistics() const;
    void setStatsSession(isc::cc::AbstractSession* stats_session);
    // Currently for testing purpose only
    const std::vector<uint64_t>& getCounters() const;
private:
    std::vector<uint64_t> counters_;
    isc::cc::AbstractSession* stats_session_;
    const bool& verbose_mode_;
};

QueryCountersImpl::QueryCountersImpl(const bool& verbose_mode) :
    // initialize counter
    // size: QueryCounters::COUNTER_TYPES, initial value: 0
    counters_(QueryCounters::COUNTER_TYPES, 0),
    stats_session_(NULL),
    verbose_mode_(verbose_mode)
{}

QueryCountersImpl::~QueryCountersImpl()
{}

void
QueryCountersImpl::inc(const QueryCounters::QueryCounterType type)
{
    try {
        ++counters_.at(type);
    } catch (std::out_of_range) {
        isc_throw(isc::InvalidParameter, "Unknown counter type: " << type);
    }
}

bool
QueryCountersImpl::submitStatistics() const {
    if (stats_session_ == NULL) {
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "session interface for statistics"
                      << " is not available" << std::endl;
        }
        return (false);
    }
    std::stringstream strstats;
    strstats << "{\"command\": [\"set\","
             <<   "{ \"stats_data\": "
             <<     "{ \"auth.queries.udp\": "
             <<     counters_.at(QueryCounters::COUNTER_UDP)
             <<     ", \"auth.queries.tcp\": "
             <<     counters_.at(QueryCounters::COUNTER_TCP)
             <<   " }"
             <<   "}"
             << "]}";
    isc::data::ConstElementPtr set_stats =
        isc::data::Element::fromJSON(strstats);
    try {
        // group_{send,recv}msg() can throw an exception when encountering
        // an error, and group_recvmsg() will throw an exception on timeout.
        // We don't want to kill the main server just due to this, so we
        // handle them here.
        const int seq = stats_session_->group_sendmsg(set_stats, "Stats");
        isc::data::ConstElementPtr env, answer;
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "send statistics data" << std::endl;
        }
        // TODO: parse and check response from statistics module
        // currently it just returns empty message
        stats_session_->group_recvmsg(env, answer, false, seq);
    } catch (const isc::cc::SessionError& ex) {
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "communication error in sending statistics data: "
                      << ex.what() << std::endl;
        }
        return (false);
    } catch (const isc::cc::SessionTimeout& ex) {
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "timeout happened while sending statistics data: "
                      << ex.what() << std::endl;
        }
        return (false);
    }
    return (true);
}

void
QueryCountersImpl::setStatsSession(isc::cc::AbstractSession* stats_session) {
    stats_session_ = stats_session;
}

// Currently for testing purpose only
const std::vector<uint64_t>&
QueryCountersImpl::getCounters() const {
    return (counters_);
}

QueryCounters::QueryCounters(const bool& verbose_mode) :
    impl_(new QueryCountersImpl(verbose_mode))
{}

QueryCounters::~QueryCounters() {
    delete impl_;
}

void
QueryCounters::inc(const QueryCounters::QueryCounterType type) {
    impl_->inc(type);
}

bool
QueryCounters::submitStatistics() const {
    return (impl_->submitStatistics());
}

void
QueryCounters::setStatsSession(isc::cc::AbstractSession* stats_session) {
    impl_->setStatsSession(stats_session);
}

const std::vector<uint64_t>&
QueryCounters::getCounters() const {
    return (impl_->getCounters());
}
