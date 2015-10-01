// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/cfg_expiration.h>
#include <exceptions/exceptions.h>
#include <limits.h>

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

CfgExpiration::CfgExpiration()
    : reclaim_timer_wait_time_(DEFAULT_RECLAIM_TIMER_WAIT_TIME),
    flush_reclaimed_timer_wait_time_(DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME),
    hold_reclaimed_time_(DEFAULT_HOLD_RECLAIMED_TIME),
    max_reclaim_leases_(DEFAULT_MAX_RECLAIM_LEASES),
    max_reclaim_time_(DEFAULT_MAX_RECLAIM_TIME),
    unwarned_reclaim_cycles_(DEFAULT_UNWARNED_RECLAIM_CYCLES) {
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
                  << config_parameter_name << "' must not be negtive");

    } else if (value > max_value) {
        isc_throw(OutOfRange, "out range value '" << value << "' for configuration"
                  " parameter '" << config_parameter_name << "', expected maximum"
                  " value of '" << max_value << "'");
    }
}



}
}
