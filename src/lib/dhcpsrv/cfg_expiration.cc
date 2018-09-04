// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfg_expiration.h>
#include <exceptions/exceptions.h>
#include <limits>

using namespace isc::data;

namespace isc {
namespace dhcp {

// Default values
const uint16_t CfgExpiration::DEFAULT_RECLAIM_TIMER_WAIT_TIME = 10;
const uint16_t CfgExpiration::DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 25;
const uint32_t CfgExpiration::DEFAULT_HOLD_RECLAIMED_TIME = 3600;
const uint32_t CfgExpiration::DEFAULT_MAX_RECLAIM_LEASES = 100;
const uint16_t CfgExpiration::DEFAULT_MAX_RECLAIM_TIME = 250;
const uint16_t CfgExpiration::DEFAULT_UNWARNED_RECLAIM_CYCLES = 5;

// Maximum values.
const uint16_t CfgExpiration::LIMIT_RECLAIM_TIMER_WAIT_TIME =
    std::numeric_limits<uint16_t>::max();
const uint16_t CfgExpiration::LIMIT_FLUSH_RECLAIMED_TIMER_WAIT_TIME =
    std::numeric_limits<uint16_t>::max();
const uint32_t CfgExpiration::LIMIT_HOLD_RECLAIMED_TIME =
    std::numeric_limits<uint32_t>::max();
const uint32_t CfgExpiration::LIMIT_MAX_RECLAIM_LEASES =
    std::numeric_limits<uint32_t>::max();
const uint16_t CfgExpiration::LIMIT_MAX_RECLAIM_TIME = 10000;
const uint16_t CfgExpiration::LIMIT_UNWARNED_RECLAIM_CYCLES =
    std::numeric_limits<uint16_t>::max();

// Timers' names
const std::string CfgExpiration::RECLAIM_EXPIRED_TIMER_NAME =
    "reclaim-expired-leases";

const std::string CfgExpiration::FLUSH_RECLAIMED_TIMER_NAME =
    "flush-reclaimed-leases";

CfgExpiration::CfgExpiration(const bool test_mode)
    : reclaim_timer_wait_time_(DEFAULT_RECLAIM_TIMER_WAIT_TIME),
      flush_reclaimed_timer_wait_time_(DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME),
      hold_reclaimed_time_(DEFAULT_HOLD_RECLAIMED_TIME),
      max_reclaim_leases_(DEFAULT_MAX_RECLAIM_LEASES),
      max_reclaim_time_(DEFAULT_MAX_RECLAIM_TIME),
      unwarned_reclaim_cycles_(DEFAULT_UNWARNED_RECLAIM_CYCLES),
      timer_mgr_(TimerMgr::instance()),
      test_mode_(test_mode) {
}

void
CfgExpiration::setReclaimTimerWaitTime(const int64_t reclaim_timer_wait_time) {
    rangeCheck(reclaim_timer_wait_time, LIMIT_RECLAIM_TIMER_WAIT_TIME,
               "reclaim-timer-wait-time");
    reclaim_timer_wait_time_ = reclaim_timer_wait_time;
}

void
CfgExpiration::setFlushReclaimedTimerWaitTime(const int64_t flush_reclaimed_wait_time) {
    rangeCheck(flush_reclaimed_wait_time, LIMIT_FLUSH_RECLAIMED_TIMER_WAIT_TIME,
               "flush-reclaimed-timer-wait-time");
    flush_reclaimed_timer_wait_time_ = flush_reclaimed_wait_time;
}

void
CfgExpiration::setHoldReclaimedTime(const int64_t hold_reclaimed_time) {
    rangeCheck(hold_reclaimed_time, LIMIT_HOLD_RECLAIMED_TIME, "hold-reclaimed-time");
    hold_reclaimed_time_ = hold_reclaimed_time;
}

void
CfgExpiration::setMaxReclaimLeases(const int64_t max_reclaim_leases) {
    rangeCheck(max_reclaim_leases, LIMIT_MAX_RECLAIM_LEASES, "max-reclaim-leases");
    max_reclaim_leases_ = max_reclaim_leases;
}

void
CfgExpiration::setMaxReclaimTime(const int64_t max_reclaim_time) {
    rangeCheck(max_reclaim_time, LIMIT_MAX_RECLAIM_TIME, "max-reclaim-time");
    max_reclaim_time_ = max_reclaim_time;
}

void
CfgExpiration::setUnwarnedReclaimCycles(const int64_t unwarned_reclaim_cycles) {
    rangeCheck(unwarned_reclaim_cycles, LIMIT_UNWARNED_RECLAIM_CYCLES,
               "unwarned-reclaim-cycles");
    unwarned_reclaim_cycles_ = unwarned_reclaim_cycles;
}

void
CfgExpiration::rangeCheck(const int64_t value, const uint64_t max_value,
                          const std::string& config_parameter_name) const {
    if (value < 0) {
        isc_throw(OutOfRange, "value for configuration parameter '"
                  << config_parameter_name << "' must not be negative");

    } else if (value > max_value) {
        isc_throw(OutOfRange, "out range value '" << value << "' for configuration"
                  " parameter '" << config_parameter_name << "', expected maximum"
                  " value of '" << max_value << "'");
    }
}

ElementPtr
CfgExpiration::toElement() const {
    ElementPtr result = Element::createMap();
    // Set reclaim-timer-wait-time
    result->set("reclaim-timer-wait-time",
                Element::create(static_cast<long long>
                                (reclaim_timer_wait_time_)));
    // Set flush-reclaimed-timer-wait-time
    result->set("flush-reclaimed-timer-wait-time",
                Element::create(static_cast<long long>
                                (flush_reclaimed_timer_wait_time_)));
    // Set hold-reclaimed-time
    result->set("hold-reclaimed-time",
                Element::create(static_cast<long long>
                                (hold_reclaimed_time_)));
    // Set max-reclaim-leases
    result->set("max-reclaim-leases",
                Element::create(static_cast<long long>
                                (max_reclaim_leases_)));
    // Set max-reclaim-time
    result->set("max-reclaim-time",
                Element::create(static_cast<long long>
                                (max_reclaim_time_)));
    // Set unwarned-reclaim-cycles
    result->set("unwarned-reclaim-cycles",
                Element::create(static_cast<long long>
                                (unwarned_reclaim_cycles_)));
    return (result);
}

}
}
