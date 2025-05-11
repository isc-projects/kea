// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ping_context.h>
#include <ping_check_log.h>
#include <exceptions/exceptions.h>
#include <util/chrono_time_utils.h>
#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace std::chrono;

namespace isc {
namespace ping_check {

PingContext::PingContext(Lease4Ptr& lease, Pkt4Ptr& query,
                         uint32_t min_echos /* = 1 */,
                         uint32_t reply_timeout /* = 100 */,
                         ParkingLotHandlePtr& parking_lot /* = EMPTY_LOT() */)
    : min_echos_(min_echos),
      reply_timeout_(reply_timeout),
      echos_sent_(0),
      last_echo_sent_time_(EMPTY_TIME()),
      send_wait_start_(EMPTY_TIME()),
      next_expiry_(EMPTY_TIME()),
      created_time_(PingContext::now()),
      lease_(lease),
      query_(query),
      state_(NEW),
      parking_lot_(parking_lot) {
    if (!lease_) {
        isc_throw(BadValue, "PingContext ctor - lease cannot be empty");
    }

    if (!query_) {
        isc_throw(BadValue, "PingContext ctor - query cannot be empty");
    }

    if (getTarget() == IOAddress::IPV4_ZERO_ADDRESS()) {
        isc_throw(BadValue, "PingContext ctor - target address cannot be 0.0.0.0");
    }

    if (min_echos_ == 0) {
        isc_throw(BadValue, "PingContext ctor - min_echos must be greater than 0");
    }

    if (reply_timeout_ == 0) {
        isc_throw(BadValue, "PingContext ctor - reply_timeout must be greater than 0");
    }
}

PingContext::State
PingContext::stringToState(const std::string& state_str) {
    if (state_str == "NEW") {
        return (NEW);
    }

    if (state_str == "WAITING_TO_SEND") {
        return (WAITING_TO_SEND);
    }

    if (state_str == "SENDING") {
        return (SENDING);
    }

    if (state_str == "WAITING_FOR_REPLY") {
        return (WAITING_FOR_REPLY);
    }

    if (state_str == "TARGET_FREE") {
        return (TARGET_FREE);
    }

    if (state_str == "TARGET_IN_USE") {
        return (TARGET_IN_USE);
    }

    isc_throw(BadValue, "Invalid PingContext::State: '" << state_str << "'");
}

TimeStamp
PingContext::now() {
    return (time_point_cast<milliseconds>(std::chrono::system_clock::now()));
}

std::string
PingContext::stateToString(const PingContext::State& state) {
    std::string label = "";
    switch (state) {
    case NEW:
        label = "NEW";
        break;
    case WAITING_TO_SEND:
        label = "WAITING_TO_SEND";
        break;
    case SENDING:
        label = "SENDING";
        break;
    case WAITING_FOR_REPLY:
        label = "WAITING_FOR_REPLY";
        break;
    case TARGET_FREE:
        label = "TARGET_FREE";
        break;
    case TARGET_IN_USE:
        label = "TARGET_IN_USE";
        break;
    }

    return (label);
}

const IOAddress& PingContext::getTarget() const {
    return (lease_->addr_);
}

uint32_t
PingContext::getMinEchos() const {
    return (min_echos_);
}

void
PingContext::setMinEchos(uint32_t value) {
    min_echos_ = value;
}

uint32_t
PingContext::getReplyTimeout() const {
    return (reply_timeout_);
}

void
PingContext::setReplyTimeout(uint32_t value) {
    reply_timeout_ = value;
}

uint32_t
PingContext::getEchosSent() const {
    return (echos_sent_);
}

void
PingContext::setEchosSent(uint32_t value) {
    echos_sent_ = value;
}

const TimeStamp&
PingContext::getLastEchoSentTime() const {
    return (last_echo_sent_time_);
}

void
PingContext::setLastEchoSentTime(const TimeStamp& value) {
    last_echo_sent_time_ = value;
}

const TimeStamp&
PingContext::getSendWaitStart() const {
    return (send_wait_start_);
}

bool
PingContext::isWaitingToSend() const {
    return (state_ == WAITING_TO_SEND);
}

void
PingContext::setSendWaitStart(const TimeStamp& value) {
    send_wait_start_ = value;
}

const TimeStamp&
PingContext::getNextExpiry() const {
    return (next_expiry_);
}

bool
PingContext::isWaitingForReply() const {
    return (state_ == WAITING_FOR_REPLY);
}

void
PingContext::setNextExpiry(const TimeStamp& value) {
    next_expiry_ = value;
}

const TimeStamp&
PingContext::getCreatedTime() const {
    return (created_time_);
}

PingContext::State
PingContext::getState() const {
    return (state_);
}

void
PingContext::setState(const PingContext::State& value) {
    state_ = value;
}

Pkt4Ptr
PingContext::getQuery() const {
    return (query_);
}

Lease4Ptr
PingContext::getLease() const {
    return (lease_);
}

void
PingContext::beginWaitingToSend(const TimeStamp& begin_time /* = now() */) {
    state_ = WAITING_TO_SEND;
    send_wait_start_ = begin_time;
}

void
PingContext::beginWaitingForReply(const TimeStamp& begin_time /* = now() */) {
    ++echos_sent_;
    last_echo_sent_time_ = begin_time;
    next_expiry_ = begin_time + milliseconds(reply_timeout_);
    state_ = WAITING_FOR_REPLY;
}

} // end of namespace ping_check
} // end of namespace isc

