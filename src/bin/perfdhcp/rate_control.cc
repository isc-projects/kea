// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfdhcp/rate_control.h>

#include <exceptions/exceptions.h>


namespace isc {
namespace perfdhcp {

using namespace boost::posix_time;

RateControl::RateControl()
    : rate_(0), total_pkts_sent_count_(0) {
}

RateControl::RateControl(const unsigned int rate)
    : rate_(rate), total_pkts_sent_count_(0) {
}

uint64_t
RateControl::getOutboundMessageCount(bool const waiting_to_exit /* = false */) {
    if (total_pkts_sent_count_ == 0) {
        start_time_ = currentTime();
        total_pkts_sent_count_ = 1;
        return 1;
    }

    // If rate is not limited, then each time send 1 packet.
    if (getRate() == 0) {
        return 1;
    }

    // If we've entered exit wait time's zone, stop sending.
    if (waiting_to_exit) {
        return 0;
    }

    // Estimate number of packets to sent. If we are behind of time we will
    // try to catch up to upkeep request rate by sending more packets in one cycle.
    auto now = currentTime();
    time_period period(start_time_, now);
    time_duration duration = period.length();
    uint64_t should_sent_pkts_count = static_cast<double>(getRate()) / static_cast<double>(time_duration::ticks_per_second()) * duration.ticks();
    if (should_sent_pkts_count <= total_pkts_sent_count_) {
        return 0;
    }
    auto pending_pkts_count = should_sent_pkts_count - total_pkts_sent_count_;

    // Reduce bursts to have more uniform traffic.
    if (pending_pkts_count > 3) {
        pending_pkts_count = 3;
    }
    total_pkts_sent_count_ += pending_pkts_count;

    return pending_pkts_count;
}

boost::posix_time::ptime
RateControl::currentTime() {
    return (microsec_clock::universal_time());
}

void
RateControl::setRate(const int rate) {
    if (rate < 0) {
        isc_throw(isc::BadValue, "invalid value of rate " << rate
                  << ", expected non-negative value");
    }
    rate_ = rate;
}

} // namespace perfdhcp
} // namespace isc
