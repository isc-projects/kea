// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <communication_state.h>
#include <exceptions/exceptions.h>
#include <ha_service_states.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_int.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <http/date_time.h>
#include <util/boost_time_utils.h>
#include <boost/bind.hpp>
#include <boost/pointer_cast.hpp>
#include <sstream>
#include <utility>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace boost::posix_time;

namespace {

/// @brief Warning is issued if the clock skew exceeds this value.
constexpr long WARN_CLOCK_SKEW = 30;

/// @brief HA service terminates if the clock skew exceeds this value.
constexpr long TERM_CLOCK_SKEW = 60;

/// @brief Minimum time between two consecutive clock skew warnings.
constexpr long MIN_TIME_SINCE_CLOCK_SKEW_WARN = 60;

}

namespace isc {
namespace ha {

CommunicationState::CommunicationState(const IOServicePtr& io_service,
                                       const HAConfigPtr& config)
    : io_service_(io_service), config_(config), timer_(), interval_(0),
      poke_time_(boost::posix_time::microsec_clock::universal_time()),
      heartbeat_impl_(0), partner_state_(-1), partner_scopes_(),
      clock_skew_(0, 0, 0, 0), last_clock_skew_warn_(),
      my_time_at_skew_(), partner_time_at_skew_() {
}

CommunicationState::~CommunicationState() {
    stopHeartbeat();
}

void
CommunicationState::setPartnerState(const std::string& state) {
    try {
        partner_state_ = stringToState(state);

    } catch (...) {
        isc_throw(BadValue, "unsupported HA partner state returned "
                  << state);
    }
}

void
CommunicationState::setPartnerScopes(ConstElementPtr new_scopes) {
    if (!new_scopes || (new_scopes->getType() != Element::list)) {
        isc_throw(BadValue, "unable to record partner's HA scopes because"
                  " the received value is not a valid JSON list");
    }

    std::set<std::string> partner_scopes;
    for (auto i = 0; i < new_scopes->size(); ++i) {
        auto scope = new_scopes->get(i);
        if (scope->getType() != Element::string) {
            isc_throw(BadValue, "unable to record partner's HA scopes because"
                      " the received scope value is not a valid JSON string");
        }
        auto scope_str = scope->stringValue();
        if (!scope_str.empty()) {
            partner_scopes.insert(scope_str);
        }
    }
    partner_scopes_ = partner_scopes;
}

void
CommunicationState::startHeartbeat(const long interval,
                                   const boost::function<void()>& heartbeat_impl) {
    startHeartbeatInternal(interval, heartbeat_impl);
}

void
CommunicationState::startHeartbeatInternal(const long interval,
                                           const boost::function<void()>& heartbeat_impl) {
    bool settings_modified = false;

    // If we're setting the heartbeat for the first time, it should
    // be non-null.
    if (heartbeat_impl) {
        settings_modified = true;
        heartbeat_impl_ = heartbeat_impl;

    } else if (!heartbeat_impl_) {
        // The heartbeat is re-scheduled but we have no historic implementation
        // pointer we could re-use. This is a programmatic issue.
        isc_throw(BadValue, "unable to start heartbeat when pointer"
                  " to the heartbeat implementation is not specified");
    }

    // If we're setting the heartbeat for the first time, the interval
    // should be greater than 0.
    if (interval != 0) {
        settings_modified |= (interval_ != interval);
        interval_ = interval;

    } else if (interval_ <= 0) {
        // The heartbeat is re-scheduled but we have no historic interval
        // which we could re-use. This is a programmatic issue.
        heartbeat_impl_ = 0;
        isc_throw(BadValue, "unable to start heartbeat when interval"
                  " for the heartbeat timer is not specified");
    }

    if (!timer_) {
        timer_.reset(new IntervalTimer(*io_service_));
    }

    if (settings_modified) {
        timer_->setup(heartbeat_impl_, interval_, IntervalTimer::ONE_SHOT);
    }
}

void
CommunicationState::stopHeartbeat() {
    if (timer_) {
        timer_->cancel();
        timer_.reset();
        interval_ = 0;
        heartbeat_impl_ = 0;
    }
}

void
CommunicationState::poke() {
    // Remember previous poke time.
    boost::posix_time::ptime prev_poke_time = poke_time_;
    // Set poke time to the current time.
    poke_time_ = boost::posix_time::microsec_clock::universal_time();

    // If we have been tracking the unanswered DHCP messages directed to the
    // partner, we need to clear any gathered information because the connection
    // seems to be (re)established.
    clearUnackedClients();

    if (timer_) {
        // Check the duration since last poke. If it is less than a second, we don't
        // want to reschedule the timer. The only case when the poke time duration is
        // lower than 1s is when we're performing lease updates. In order to avoid the
        // overhead of re-scheduling the timer too frequently we reschedule it only if the
        // duration is 1s or more. This matches the time resolution for heartbeats.
        boost::posix_time::time_duration duration_since_poke = poke_time_ - prev_poke_time;
        if (duration_since_poke.total_seconds() > 0) {
            // A poke causes the timer to be re-scheduled to prevent it
            // from triggering a heartbeat shortly after confirming the
            // connection is ok, based on the lease update or another
            // command.
            startHeartbeatInternal();
        }
    }
}

int64_t
CommunicationState::getDurationInMillisecs() const {
    ptime now = boost::posix_time::microsec_clock::universal_time();
    time_duration duration = now - poke_time_;
    return (duration.total_milliseconds());
}

bool
CommunicationState::isCommunicationInterrupted() const {
    return (getDurationInMillisecs() > config_->getMaxResponseDelay());
}

bool
CommunicationState::clockSkewShouldWarn() {
    // First check if the clock skew is beyond the threshold.
    if (isClockSkewGreater(WARN_CLOCK_SKEW)) {

        // In order to prevent to frequent warnings we provide a gating mechanism
        // which doesn't allow for issuing a warning earlier than 60 seconds after
        // the previous one.

        // Find the current time and the duration since last warning.
        ptime now = boost::posix_time::microsec_clock::universal_time();
        time_duration since_warn_duration = now - last_clock_skew_warn_;

        // If the last warning was issued more than 60 seconds ago or it is a
        // first warning, we need to update the last warning timestamp and return
        // true to indicate that new warning should be issued.
        if (last_clock_skew_warn_.is_not_a_date_time() ||
            (since_warn_duration.total_seconds() > MIN_TIME_SINCE_CLOCK_SKEW_WARN)) {
            last_clock_skew_warn_ = now;
            return (true);
        }
    }

    // The warning should not be issued.
    return (false);
}

bool
CommunicationState::clockSkewShouldTerminate() const {
    // Issue a warning if the clock skew is greater than 60s.
    return (isClockSkewGreater(TERM_CLOCK_SKEW));
}

bool
CommunicationState::isClockSkewGreater(const long seconds) const {
    return ((clock_skew_.total_seconds() > seconds) ||
            (clock_skew_.total_seconds() < -seconds));
}

void
CommunicationState::setPartnerTime(const std::string& time_text) {
    partner_time_at_skew_ = HttpDateTime().fromRfc1123(time_text).getPtime();
    my_time_at_skew_ = HttpDateTime().getPtime();
    clock_skew_ = partner_time_at_skew_ - my_time_at_skew_;
}

std::string
CommunicationState::logFormatClockSkew() const {
    std::ostringstream os;

    if ((my_time_at_skew_.is_not_a_date_time()) ||
        (partner_time_at_skew_.is_not_a_date_time())) {
        // Guard against being called before times have been set.
        // Otherwise we'll get out-range exceptions.
        return ("skew not initialized");
    }

    // Note HttpTime resolution is only to seconds, so we use fractional
    // precision of zero when logging.
    os << "my time: " << util::ptimeToText(my_time_at_skew_, 0)
       << ", partner's time: " << util::ptimeToText(partner_time_at_skew_, 0)
       << ", partner's clock is ";

    // If negative clock skew, the partner's time is behind our time.
    if (clock_skew_.is_negative()) {
        os << clock_skew_.invert_sign().total_seconds() << "s behind";
    } else {
        // Partner's time is ahead of ours.
        os << clock_skew_.total_seconds() << "s ahead";
    }

    return (os.str());
}

CommunicationState4::CommunicationState4(const IOServicePtr& io_service,
                                         const HAConfigPtr& config)
    : CommunicationState(io_service, config), unacked_clients_() {
}

void
CommunicationState4::analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message) {
    // The DHCP message must successfully cast to a Pkt4 object.
    Pkt4Ptr msg = boost::dynamic_pointer_cast<Pkt4>(message);
    if (!msg) {
        isc_throw(BadValue, "DHCP message to be analyzed is not a DHCPv4 message");
    }

    // Check value of the "secs" field by comparing it with the configured
    // threshold.
    uint16_t secs = msg->getSecs();

    // It was observed that some Windows clients may send swapped bytes in the
    // "secs" field. When the second byte is 0 and the first byte is non-zero
    // we consider bytes to be swapped and so we correct them.
    if ((secs > 255) && ((secs & 0xFF) == 0)) {
        secs = ((secs >> 8) | (secs << 8));
    }

    // Check the value of the "secs" field. If it is below the threshold there
    // is nothing to do. The "secs" field holds a value in seconds, hence we
    // have to multiple by 1000 to get a value in milliseconds.
    if (secs * 1000 <= config_->getMaxAckDelay()) {
        return;
    }

    // The "secs" value is above the threshold so we should count it as unacked
    // request, but we will first have to check if there is such request already
    // recorded.
    auto existing_requests = unacked_clients_.equal_range(msg->getHWAddr()->hwaddr_);

    // Client identifier will be stored together with the hardware address. It
    // may remain empty if the client hasn't specified it.
    std::vector<uint8_t> client_id;
    OptionPtr opt_client_id = msg->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt_client_id) {
        client_id = opt_client_id->getData();
    }

    // Iterate over the requests we found so far and see if we have a match with
    // the client identifier (this includes empty client identifiers).
    for (auto r = existing_requests.first; r != existing_requests.second; ++r) {
        if (r->second == client_id) {
            // There is a match so we have already recorded this client as
            // unacked.
            return;
        }
    }

    // New unacked client detected, so record the required information.
    unacked_clients_.insert(std::make_pair(msg->getHWAddr()->hwaddr_, client_id));
}

bool
CommunicationState4::failureDetected() const {
    return ((config_->getMaxUnackedClients() == 0) ||
            (unacked_clients_.size() > config_->getMaxUnackedClients()));
}

void
CommunicationState4::clearUnackedClients() {
    unacked_clients_.clear();
}

CommunicationState6::CommunicationState6(const IOServicePtr& io_service,
                                         const HAConfigPtr& config)
    : CommunicationState(io_service, config), unacked_clients_() {
}

void
CommunicationState6::analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message) {
    // The DHCP message must successfully cast to a Pkt6 object.
    Pkt6Ptr msg = boost::dynamic_pointer_cast<Pkt6>(message);
    if (!msg) {
        isc_throw(BadValue, "DHCP message to be analyzed is not a DHCPv6 message");
    }

    // Check the value of the "elapsed time" option. If it is below the threshold
    // there is nothing to do. The "elapsed time" option holds the time in
    // 1/100 of second, hence we have to multiply by 10 to get a value in milliseconds.
    OptionUint16Ptr elapsed_time = boost::dynamic_pointer_cast<
        OptionUint16>(msg->getOption(D6O_ELAPSED_TIME));
    if (!elapsed_time || elapsed_time->getValue() * 10 <= config_->getMaxAckDelay()) {
        return;
    }

    // Get the DUID of the client to see if it hasn't been recorded already.
    OptionPtr duid = msg->getOption(D6O_CLIENTID);
    if (duid && unacked_clients_.count(duid->getData()) == 0) {
        // New unacked client detected, so record the required information.
        unacked_clients_.insert(duid->getData());
    }
}

bool
CommunicationState6::failureDetected() const {
    return ((config_->getMaxUnackedClients() == 0) ||
            (unacked_clients_.size() > config_->getMaxUnackedClients()));
}

void
CommunicationState6::clearUnackedClients() {
    unacked_clients_.clear();
}

} // end of namespace isc::ha
} // end of namespace isc
