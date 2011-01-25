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

#include <auth/statistics.h>

#include <cc/data.h>
#include <cc/session.h>

#include <sstream>
#include <iostream>

// TODO: We need a namespace ("auth_server"?) to hold
// AuthSrv and AuthCounters.

class AuthCountersImpl {
private:
    // prohibit copy
    AuthCountersImpl(const AuthCountersImpl& source);
    AuthCountersImpl& operator=(const AuthCountersImpl& source);
public:
    // References verbose_mode flag in AuthSrvImpl
    // TODO: Fix this short term workaround for logging
    // after we have logging framework
    AuthCountersImpl(const bool& verbose_mode);
    ~AuthCountersImpl();
    void inc(const AuthCounters::CounterType type);
    bool submitStatistics() const;
    void setStatisticsSession(isc::cc::AbstractSession* statistics_session);
    // Currently for testing purpose only
    uint64_t getCounter(const AuthCounters::CounterType type) const;
private:
    std::vector<uint64_t> counters_;
    isc::cc::AbstractSession* statistics_session_;
    const bool& verbose_mode_;
};

AuthCountersImpl::AuthCountersImpl(const bool& verbose_mode) :
    // initialize counter
    // size: AuthCounters::COUNTER_TYPES, initial value: 0
    counters_(AuthCounters::COUNTER_TYPES, 0),
    statistics_session_(NULL),
    verbose_mode_(verbose_mode)
{}

AuthCountersImpl::~AuthCountersImpl()
{}

void
AuthCountersImpl::inc(const AuthCounters::CounterType type) {
    ++counters_.at(type);
}

bool
AuthCountersImpl::submitStatistics() const {
    if (statistics_session_ == NULL) {
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "session interface for statistics"
                      << " is not available" << std::endl;
        }
        return (false);
    }
    std::stringstream statistics_string;
    statistics_string << "{\"command\": [\"set\","
                      <<   "{ \"stats_data\": "
                      <<     "{ \"auth.queries.udp\": "
                      <<     counters_.at(AuthCounters::COUNTER_UDP_QUERY)
                      <<     ", \"auth.queries.tcp\": "
                      <<     counters_.at(AuthCounters::COUNTER_TCP_QUERY)
                      <<   " }"
                      <<   "}"
                      << "]}";
    isc::data::ConstElementPtr statistics_element =
        isc::data::Element::fromJSON(statistics_string);
    try {
        // group_{send,recv}msg() can throw an exception when encountering
        // an error, and group_recvmsg() will throw an exception on timeout.
        // We don't want to kill the main server just due to this, so we
        // handle them here.
        const int seq =
            statistics_session_->group_sendmsg(statistics_element, "Stats");
        isc::data::ConstElementPtr env, answer;
        if (verbose_mode_) {
            std::cerr << "[b10-auth] "
                      << "send statistics data" << std::endl;
        }
        // TODO: parse and check response from statistics module
        // currently it just returns empty message
        statistics_session_->group_recvmsg(env, answer, false, seq);
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
AuthCountersImpl::setStatisticsSession
    (isc::cc::AbstractSession* statistics_session)
{
    statistics_session_ = statistics_session;
}

// Currently for testing purpose only
uint64_t
AuthCountersImpl::getCounter(const AuthCounters::CounterType type) const {
    return (counters_.at(type));
}

AuthCounters::AuthCounters(const bool& verbose_mode) :
    impl_(new AuthCountersImpl(verbose_mode))
{}

AuthCounters::~AuthCounters() {
    delete impl_;
}

void
AuthCounters::inc(const AuthCounters::CounterType type) {
    impl_->inc(type);
}

bool
AuthCounters::submitStatistics() const {
    return (impl_->submitStatistics());
}

void
AuthCounters::setStatisticsSession
    (isc::cc::AbstractSession* statistics_session)
{
    impl_->setStatisticsSession(statistics_session);
}

uint64_t
AuthCounters::getCounter(const AuthCounters::CounterType type) const {
    return (impl_->getCounter(type));
}
