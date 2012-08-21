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
    void inc(const Rcode rcode) {
        rcode_counter_.inc(rcode.getCode());
    }
    void inc(const std::string& zone,
             const AuthCounters::PerZoneCounterType type);
    isc::data::ElementPtr getStatistics() const;
    void registerStatisticsValidator
    (AuthCounters::validator_type validator);
    // Currently for testing purpose only
    uint64_t getCounter(const AuthCounters::ServerCounterType type) const;
    uint64_t getCounter(const Opcode opcode) const {
        return (opcode_counter_.get(opcode.getCode()));
    }
    uint64_t getCounter(const Rcode rcode) const {
        return (rcode_counter_.get(rcode.getCode()));
    }
private:
    Counter server_counter_;
    Counter opcode_counter_;
    static const size_t NUM_OPCODES = 16;
    Counter rcode_counter_;
    static const size_t NUM_RCODES = 17;
    CounterDictionary per_zone_counter_;
    AuthCounters::validator_type validator_;
};

AuthCountersImpl::AuthCountersImpl() :
    // initialize counter
    // size of server_counter_: AuthCounters::SERVER_COUNTER_TYPES
    // size of per_zone_counter_: AuthCounters::PER_ZONE_COUNTER_TYPES
    server_counter_(AuthCounters::SERVER_COUNTER_TYPES),
    opcode_counter_(NUM_OPCODES), rcode_counter_(NUM_RCODES),
    per_zone_counter_(AuthCounters::PER_ZONE_COUNTER_TYPES)
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

isc::data::ElementPtr
AuthCountersImpl::getStatistics() const {
    std::stringstream statistics_string;
    statistics_string << "{ \"queries.udp\": "
                      << server_counter_.get(AuthCounters::SERVER_UDP_QUERY)
                      << ", \"queries.tcp\": "
                      << server_counter_.get(AuthCounters::SERVER_TCP_QUERY);
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
    // Insert non 0 Rcode counters.
    for (int i = 0; i < NUM_RCODES; ++i) {
        const Counter::Type counter = rcode_counter_.get(i);
        if (counter != 0) {
            // The counter item name should be derived lower-cased textual
            // representation of the code.
            std::string rcode_txt = Rcode(i).toText();
            std::transform(rcode_txt.begin(), rcode_txt.end(),
                           rcode_txt.begin(), ::tolower);
            statistics_string << ", \"rcode." << rcode_txt << "\": "
                              << counter;
        }
    }
    statistics_string <<   "}";

    isc::data::ElementPtr statistics_element =
        isc::data::Element::fromJSON(statistics_string);
    // validate the statistics data before send
    if (validator_) {
        if (!validator_(
                 static_cast<isc::data::ConstElementPtr>(statistics_element)))
        {
            LOG_ERROR(auth_logger, AUTH_INVALID_STATISTICS_DATA);
            return (isc::data::ElementPtr());
        }
    }
    return (statistics_element);
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

void
AuthCounters::inc(const Rcode rcode) {
    impl_->inc(rcode);
}

isc::data::ElementPtr
AuthCounters::getStatistics() const {
    return (impl_->getStatistics());
}

uint64_t
AuthCounters::getCounter(const AuthCounters::ServerCounterType type) const {
    return (impl_->getCounter(type));
}

uint64_t
AuthCounters::getCounter(const Opcode opcode) const {
    return (impl_->getCounter(opcode));
}

uint64_t
AuthCounters::getCounter(const Rcode rcode) const {
    return (impl_->getCounter(rcode));
}

void
AuthCounters::registerStatisticsValidator
    (AuthCounters::validator_type validator) const
{
    return (impl_->registerStatisticsValidator(validator));
}
