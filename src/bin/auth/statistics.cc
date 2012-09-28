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

namespace isc {
namespace auth {
namespace statistics {

// TODO: Make use of wrappers like isc::dns::Opcode
// for counter item type.

class CountersImpl : boost::noncopyable {
public:
    CountersImpl();
    ~CountersImpl();
    void inc(const Counters::ServerCounterType type);
    void inc(const Opcode opcode) {
        opcode_counter_.inc(opcode.getCode());
    }
    void inc(const Rcode rcode) {
        rcode_counter_.inc(rcode.getCode());
    }
    void inc(const std::string& zone, const Counters::PerZoneCounterType type);
    isc::data::ConstElementPtr getStatistics() const;
    void registerStatisticsValidator (Counters::validator_type validator);
    // Currently for testing purpose only
    uint64_t getCounter(const Counters::ServerCounterType type) const;
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
    Counters::validator_type validator_;
};

CountersImpl::CountersImpl() :
    // initialize counter
    // size of server_counter_: Counters::SERVER_COUNTER_TYPES
    // size of per_zone_counter_: Counters::PER_ZONE_COUNTER_TYPES
    server_counter_(Counters::SERVER_COUNTER_TYPES),
    opcode_counter_(NUM_OPCODES), rcode_counter_(NUM_RCODES),
    per_zone_counter_(Counters::PER_ZONE_COUNTER_TYPES)
{
    per_zone_counter_.addElement("_SERVER_");
}

CountersImpl::~CountersImpl()
{}

void
CountersImpl::inc(const Counters::ServerCounterType type) {
    server_counter_.inc(type);
}

void
CountersImpl::inc(const std::string& zone,
                  const Counters::PerZoneCounterType type)
{
    per_zone_counter_[zone].inc(type);
}

isc::data::ConstElementPtr
CountersImpl::getStatistics() const {
    std::stringstream statistics_string;
    statistics_string << "{ \"queries.udp\": "
                      << server_counter_.get(Counters::SERVER_UDP_QUERY)
                      << ", \"queries.tcp\": "
                      << server_counter_.get(Counters::SERVER_TCP_QUERY);
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
    statistics_string << "}";

    isc::data::ConstElementPtr statistics_element =
        isc::data::Element::fromJSON(statistics_string);
    // validate the statistics data before send
    if (validator_) {
        if (!validator_(statistics_element)) {
            LOG_ERROR(auth_logger, AUTH_INVALID_STATISTICS_DATA);
            return (isc::data::ElementPtr());
        }
    }
    return (statistics_element);
}

void
CountersImpl::registerStatisticsValidator
    (Counters::validator_type validator)
{
    validator_ = validator;
}

// Currently for testing purpose only
uint64_t
CountersImpl::getCounter(const Counters::ServerCounterType type) const {
    return (server_counter_.get(type));
}

Counters::Counters() : impl_(new CountersImpl())
{}

Counters::~Counters() {}

void
Counters::inc(const Counters::ServerCounterType type) {
    impl_->inc(type);
}

void
Counters::inc(const Opcode opcode) {
    impl_->inc(opcode);
}

void
Counters::inc(const Rcode rcode) {
    impl_->inc(rcode);
}

isc::data::ConstElementPtr
Counters::getStatistics() const {
    return (impl_->getStatistics());
}

uint64_t
Counters::getCounter(const Counters::ServerCounterType type) const {
    return (impl_->getCounter(type));
}

uint64_t
Counters::getCounter(const Opcode opcode) const {
    return (impl_->getCounter(opcode));
}

uint64_t
Counters::getCounter(const Rcode rcode) const {
    return (impl_->getCounter(rcode));
}

void
Counters::registerStatisticsValidator
    (Counters::validator_type validator) const
{
    return (impl_->registerStatisticsValidator(validator));
}

} // namespace statistics
} // namespace auth
} // namespace isc
