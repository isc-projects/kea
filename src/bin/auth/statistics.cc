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
#include <auth/auth_log.h>

#include <dns/opcode.h>

#include <cc/data.h>
#include <cc/session.h>

#include <statistics/counter.h>
#include <statistics/counter_dict.h>

#include <algorithm>
#include <cctype>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

#include <boost/noncopyable.hpp>

using namespace isc::dns;
using namespace isc::auth;
using namespace isc::statistics;

// TODO: We need a namespace ("auth_server"?) to hold
// AuthSrv and AuthCounters.

// TODO: Make use of wrappers like isc::dns::Opcode
// for counter item type.

class AuthCountersImpl : boost::noncopyable {
public:
    AuthCountersImpl();
    ~AuthCountersImpl();
    void inc(const AuthCounters::ServerCounterType type);
    void inc(const Opcode opcode) {
        opcode_counter_.inc(opcode.getCode());
    }
    void inc(const std::string& zone,
             const AuthCounters::PerZoneCounterType type);
    bool submitStatistics() const;
    void setStatisticsSession(isc::cc::AbstractSession* statistics_session);
    void registerStatisticsValidator
    (AuthCounters::validator_type validator);
    // Currently for testing purpose only
    uint64_t getCounter(const AuthCounters::ServerCounterType type) const;
    uint64_t getCounter(const Opcode opcode) const {
        return (opcode_counter_.get(opcode.getCode()));
    }
private:
    Counter server_counter_;
    Counter opcode_counter_;
    static const size_t NUM_OPCODES = 16;
    CounterDictionary per_zone_counter_;
    isc::cc::AbstractSession* statistics_session_;
    AuthCounters::validator_type validator_;
};

AuthCountersImpl::AuthCountersImpl() :
    // initialize counter
    // size of server_counter_: AuthCounters::SERVER_COUNTER_TYPES
    // size of per_zone_counter_: AuthCounters::PER_ZONE_COUNTER_TYPES
    server_counter_(AuthCounters::SERVER_COUNTER_TYPES),
    opcode_counter_(NUM_OPCODES),
    per_zone_counter_(AuthCounters::PER_ZONE_COUNTER_TYPES),
    statistics_session_(NULL)
{
    per_zone_counter_.addElement("_SERVER_");
}

AuthCountersImpl::~AuthCountersImpl()
{}

void
AuthCountersImpl::inc(const AuthCounters::ServerCounterType type) {
    server_counter_.inc(type);
}

void
AuthCountersImpl::inc(const std::string& zone,
                      const AuthCounters::PerZoneCounterType type)
{
    per_zone_counter_[zone].inc(type);
}

bool
AuthCountersImpl::submitStatistics() const {
    if (statistics_session_ == NULL) {
        LOG_ERROR(auth_logger, AUTH_NO_STATS_SESSION);
        return (false);
    }
    std::stringstream statistics_string;
    statistics_string << "{\"command\": [\"set\","
                      <<   "{ \"owner\": \"Auth\","
                      <<   "  \"data\":"
                      <<     "{ \"queries.udp\": "
                      <<     server_counter_.get(AuthCounters::SERVER_UDP_QUERY)
                      <<     ", \"queries.tcp\": "
                      <<     server_counter_.get(
                          AuthCounters::SERVER_TCP_QUERY);
    // Insert non 0 Opcode counters.
    for (int i = 0; i < NUM_OPCODES; ++i) {
        const Counter::Type counter = opcode_counter_.get(i);
        if (counter != 0) {
            // The counter item name should be derived lower-cased textual
            // representation of the code.
            std::string opcode_txt = Opcode(i).toText();
            std::transform(opcode_txt.begin(), opcode_txt.end(),
                           opcode_txt.begin(), ::tolower);
            statistics_string << ", \"opcode." << opcode_txt << "\": "
                              << counter;
        }
    }
    statistics_string <<   " }"
                      <<   "}"
                      << "]}";
    isc::data::ConstElementPtr statistics_element =
        isc::data::Element::fromJSON(statistics_string);
    // validate the statistics data before send
    if (validator_) {
        if (!validator_(
                statistics_element->get("command")->get(1)->get("data"))) {
            LOG_ERROR(auth_logger, AUTH_INVALID_STATISTICS_DATA);
            return (false);
        }
    }
    try {
        // group_{send,recv}msg() can throw an exception when encountering
        // an error, and group_recvmsg() will throw an exception on timeout.
        // We don't want to kill the main server just due to this, so we
        // handle them here.
        const int seq =
            statistics_session_->group_sendmsg(statistics_element, "Stats");
        isc::data::ConstElementPtr env, answer;
        // TODO: parse and check response from statistics module
        // currently it just returns empty message
        statistics_session_->group_recvmsg(env, answer, false, seq);
    } catch (const isc::cc::SessionError& ex) {
        LOG_ERROR(auth_logger, AUTH_STATS_COMMS).arg(ex.what());
        return (false);
    } catch (const isc::cc::SessionTimeout& ex) {
        LOG_ERROR(auth_logger, AUTH_STATS_TIMEOUT).arg(ex.what());
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

void
AuthCountersImpl::registerStatisticsValidator
    (AuthCounters::validator_type validator)
{
    validator_ = validator;
}

// Currently for testing purpose only
uint64_t
AuthCountersImpl::getCounter(const AuthCounters::ServerCounterType type) const {
    return (server_counter_.get(type));
}

AuthCounters::AuthCounters() : impl_(new AuthCountersImpl())
{}

AuthCounters::~AuthCounters() {}

void
AuthCounters::inc(const AuthCounters::ServerCounterType type) {
    impl_->inc(type);
}

void
AuthCounters::inc(const Opcode opcode) {
    impl_->inc(opcode);
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
AuthCounters::getCounter(const AuthCounters::ServerCounterType type) const {
    return (impl_->getCounter(type));
}

uint64_t
AuthCounters::getCounter(const Opcode opcode) const {
    return (impl_->getCounter(opcode));
}

void
AuthCounters::registerStatisticsValidator
    (AuthCounters::validator_type validator) const
{
    return (impl_->registerStatisticsValidator(validator));
}
