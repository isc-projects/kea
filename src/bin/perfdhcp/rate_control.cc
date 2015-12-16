// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include "rate_control.h"

namespace isc {
namespace perfdhcp {

using namespace boost::posix_time;

RateControl::RateControl()
    : send_due_(currentTime()), last_sent_(currentTime()),
      aggressivity_(1), rate_(0), late_sent_(false) {
}

RateControl::RateControl(const int rate, const int aggressivity)
    : send_due_(currentTime()), last_sent_(currentTime()),
      aggressivity_(aggressivity), rate_(rate), late_sent_(false) {
    if (aggressivity_ < 1) {
        isc_throw(isc::BadValue, "invalid value of aggressivity "
                  << aggressivity << ", expected value is greater than 0");
    }
    if (rate_ < 0) {
        isc_throw(isc::BadValue, "invalid value of rate " << rate
                  << ", expected non-negative value");
    }
}

uint64_t
RateControl::getOutboundMessageCount() {

    // We need calculate the due time for sending next set of messages.
    updateSendDue();

    // Get current time. If we are behind due time, we have to calculate
    // how many messages to send to catch up with the rate.
    ptime now = currentTime();
    if (now >= send_due_) {
        // Reset number of exchanges.
        uint64_t due_exchanges = 0;
        // If rate is specified from the command line we have to
        // synchronize with it.
        if (getRate() != 0) {
            time_period period(send_due_, now);
            time_duration duration = period.length();
            // due_factor indicates the number of seconds that
            // sending next chunk of packets will take.
            double due_factor =
                static_cast<double>(duration.fractional_seconds()) /
                static_cast<double>(time_duration::ticks_per_second());
            due_factor += static_cast<double>(duration.total_seconds());
            // Multiplying due_factor by expected rate gives the number
            // of exchanges to be initiated.
            due_exchanges = static_cast<uint64_t>(due_factor * getRate());
            // We want to make sure that at least one packet goes out.
            if (due_exchanges == 0) {
                due_exchanges = 1;
            }
            // We should not exceed aggressivity as it could have been
            // restricted from command line.
            if (due_exchanges > getAggressivity()) {
                due_exchanges = getAggressivity();
            }
        } else {
            // Rate is not specified so we rely on aggressivity
            // which is the number of packets to be sent in
            // one chunk.
            due_exchanges = getAggressivity();
        }
        return (due_exchanges);
    }
    return (0);
}

boost::posix_time::ptime
RateControl::currentTime() {
    return (microsec_clock::universal_time());
}

void
RateControl::updateSendDue() {
    // There is no sense to update due time if the current due time is in the
    // future. The due time is calculated as a duration between the moment
    // when the last message of the given type was sent and the time when
    // next one is supposed to be sent based on a given rate. The former value
    // will not change until we send the next message, which we don't do
    // until we reach the due time.
    if (send_due_ > currentTime()) {
        return;
    }
    // This is initialized in the class constructor, so if it is not initialized
    // it is a programmatic error.
    if (last_sent_.is_not_a_date_time()) {
        isc_throw(isc::Unexpected, "timestamp of the last sent packet not"
                  " initialized");
    }
    // If rate was not specified we will wait just one clock tick to
    // send next packet. This simulates best effort conditions.
    long duration = 1;
    if (getRate() != 0) {
        // We use number of ticks instead of nanoseconds because
        // nanosecond resolution may not be available on some
        // machines. Number of ticks guarantees the highest possible
        // timer resolution.
        duration = time_duration::ticks_per_second() / getRate();
    }
    // Calculate due time to initiate next chunk of exchanges.
    send_due_ = last_sent_ + time_duration(0, 0, 0, duration);
    if (send_due_ > currentTime()) {
        late_sent_ = true;
    } else {
        late_sent_ = false;
    }
}

void
RateControl::setAggressivity(const int aggressivity) {
    if (aggressivity < 1) {
        isc_throw(isc::BadValue, "invalid value of aggressivity "
                  << aggressivity << ", expected value is greater than 0");
    }
    aggressivity_ = aggressivity;
}

void
RateControl::setRate(const int rate) {
    if (rate < 0) {
        isc_throw(isc::BadValue, "invalid value of rate " << rate
                  << ", expected non-negative value");
    }
    rate_ = rate;
}

void
RateControl::setRelativeDue(const int offset) {
    send_due_ = offset > 0 ?
        currentTime() + seconds(abs(offset)) :
        currentTime() - seconds(abs(offset));
}

void
RateControl::updateSendTime() {
    last_sent_ = currentTime();
}

} // namespace perfdhcp
} // namespace isc
