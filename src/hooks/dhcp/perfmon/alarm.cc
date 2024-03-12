// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/dhcp6.h>
#include <exceptions/exceptions.h>
#include <alarm.h>

using namespace isc::dhcp;
using namespace boost::posix_time;

namespace isc {
namespace perfmon {

Alarm::Alarm(uint16_t family,
             uint8_t query_type,
             uint8_t response_type,
             const std::string& start_event_label,
             const std::string& stop_event_label,
             dhcp::SubnetID subnet_id,
             const Duration& low_water,
             const Duration& high_water,
             bool enabled /* = true */)
    : DurationKey(family, query_type, response_type, start_event_label, stop_event_label, subnet_id),
      low_water_(low_water),
      high_water_(high_water),
      state_(enabled ? CLEAR : DISABLED),
      stos_time_(PktEvent::now()),
      last_high_water_report_(PktEvent::EMPTY_TIME()) {
    if (low_water >= high_water_) {
        isc_throw(BadValue, "low water: " << low_water_
                   << ", must be less than high water: " << high_water_);
    }
}

Alarm::Alarm(const DurationKey& key,
             const Duration& low_water,
             const Duration& high_water,
             bool enabled /* = true */)
    : DurationKey(key),
      low_water_(low_water),
      high_water_(high_water),
      state_(enabled ? CLEAR : DISABLED),
      stos_time_(PktEvent::now()),
      last_high_water_report_(PktEvent::EMPTY_TIME()) {
    if (low_water >= high_water_) {
        isc_throw(BadValue, "low water: " << low_water_
                   << ", must be less than high water: " << high_water_);
    }
}

void
Alarm::setLowWater(const Duration& low_water) {
    if (low_water >= high_water_) {
        isc_throw(BadValue, "low water: " << low_water
                  << ", must be less than high water: " << high_water_);
    }

    low_water_ = low_water;
}

void
Alarm::setHighWater(const Duration& high_water) {
    if (high_water <= low_water_) {
        isc_throw(BadValue, "high water: " << high_water
                  << ", must be greater than low water: " << low_water_);
    }

    high_water_ = high_water;
}

void
Alarm::setState(State state) {
    state_ = state;
    stos_time_ = PktEvent::now();
    last_high_water_report_ = PktEvent::EMPTY_TIME();
}

void
Alarm::clear() {
    setState(CLEAR);
}

void
Alarm::disable() {
    setState(DISABLED);
}

bool
Alarm::checkSample(const Duration& sample, const Duration& report_interval) {
    if (state_ == DISABLED) {
        isc_throw(InvalidOperation, "Alarm::checkSample() "
                  "- should not be called when alarm is DISABLED");
    }

    // Low water subceeded?
    if (sample < low_water_) {
        // If the alarm is currently triggered, transition to CLEAR
        // state and return true to signal reportable condition.
        if (state_ == TRIGGERED) {
            setState(CLEAR);
            return (true);
        }

        // Nothing to report.
        return (false);
    }

    // High water exceeded?
    if (sample > high_water_) {
        // If the alarm isn't yet triggered, transition to the TRIGGERED state.
        if (state_ != TRIGGERED) {
            setState(TRIGGERED);
        }
    }

    // If we're triggered and have not yet reported it or it is time to report again,
    // update the report time and return true.
    if (state_ == TRIGGERED) {
        auto now = PktEvent::now();
        if ((last_high_water_report_ == PktEvent::EMPTY_TIME()) ||
            ((now - last_high_water_report_) > report_interval)) {
            last_high_water_report_ = now;
            return (true);
        }
    }

    // Nothing to report.
    return (false);
}

} // end of namespace perfmon
} // end of namespace isc
