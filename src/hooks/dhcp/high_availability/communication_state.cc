// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <communication_state.h>
#include <ha_log.h>
#include <ha_service_states.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_int.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <http/date_time.h>
#include <util/boost_time_utils.h>
#include <util/multi_threading_mgr.h>

#include <boost/pointer_cast.hpp>

#include <functional>
#include <limits>
#include <sstream>
#include <utility>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace isc::log;
using namespace isc::util;

using namespace boost::posix_time;
using namespace std;

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
      my_time_at_skew_(), partner_time_at_skew_(),
      analyzed_messages_count_(0), unsent_update_count_(0),
      partner_unsent_update_count_{0, 0}, mutex_(new mutex()) {
}

CommunicationState::~CommunicationState() {
    stopHeartbeat();
}

void
CommunicationState::modifyPokeTime(const long secs) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        poke_time_ += boost::posix_time::seconds(secs);
    } else {
        poke_time_ += boost::posix_time::seconds(secs);
    }
}

int
CommunicationState::getPartnerState() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (partner_state_);
    } else {
        return (partner_state_);
    }
}

void
CommunicationState::setPartnerState(const std::string& state) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        setPartnerStateInternal(state);
    } else {
        setPartnerStateInternal(state);
    }
}

void
CommunicationState::setPartnerStateInternal(const std::string& state) {
    try {
        partner_state_ = stringToState(state);
    } catch (...) {
        isc_throw(BadValue, "unsupported HA partner state returned "
                  << state);
    }
}

std::set<std::string>
CommunicationState::getPartnerScopes() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (partner_scopes_);
    } else {
        return (partner_scopes_);
    }
}

void
CommunicationState::setPartnerScopes(ConstElementPtr new_scopes) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        setPartnerScopesInternal(new_scopes);
    } else {
        setPartnerScopesInternal(new_scopes);
    }
}

void
CommunicationState::setPartnerScopesInternal(ConstElementPtr new_scopes) {
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
                                   const std::function<void()>& heartbeat_impl) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        startHeartbeatInternal(interval, heartbeat_impl);
    } else {
        startHeartbeatInternal(interval, heartbeat_impl);
    }
}

void
CommunicationState::startHeartbeatInternal(const long interval,
                                           const std::function<void()>& heartbeat_impl) {
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
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        stopHeartbeatInternal();
    } else {
        stopHeartbeatInternal();
    }
}

void
CommunicationState::stopHeartbeatInternal() {
    if (timer_) {
        timer_->cancel();
        timer_.reset();
        interval_ = 0;
        heartbeat_impl_ = 0;
    }
}

bool
CommunicationState::isHeartbeatRunning() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (static_cast<bool>(timer_));
    } else {
        return (static_cast<bool>(timer_));
    }
}

boost::posix_time::time_duration
CommunicationState::updatePokeTime() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (updatePokeTimeInternal());
    } else {
        return (updatePokeTimeInternal());
    }
}

boost::posix_time::time_duration
CommunicationState::updatePokeTimeInternal() {
    // Remember previous poke time.
    boost::posix_time::ptime prev_poke_time = poke_time_;
    // Set poke time to the current time.
    poke_time_ = boost::posix_time::microsec_clock::universal_time();
    return (poke_time_ - prev_poke_time);
}

void
CommunicationState::poke() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        pokeInternal();
    } else {
        pokeInternal();
    }
}

void
CommunicationState::pokeInternal() {
    // Update poke time and compute duration.
    boost::posix_time::time_duration duration_since_poke = updatePokeTimeInternal();

    // If we have been tracking the DHCP messages directed to the partner,
    // we need to clear any gathered information because the connection
    // seems to be (re)established.
    clearConnectingClients();
    analyzed_messages_count_ = 0;

    if (timer_) {
        // Check the duration since last poke. If it is less than a second, we don't
        // want to reschedule the timer. In order to avoid the overhead of
        // re-scheduling the timer too frequently we reschedule it only if the
        // duration is 1s or more. This matches the time resolution for heartbeats.
        if (duration_since_poke.total_seconds() > 0) {
            // A poke causes the timer to be re-scheduled to prevent it
            // from triggering a heartbeat shortly after confirming the
            // connection is ok.
            startHeartbeatInternal();
        }
    }
}

int64_t
CommunicationState::getDurationInMillisecs() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (getDurationInMillisecsInternal());
    } else {
        return (getDurationInMillisecsInternal());
    }
}

int64_t
CommunicationState::getDurationInMillisecsInternal() const {
    ptime now = boost::posix_time::microsec_clock::universal_time();
    time_duration duration = now - poke_time_;
    return (duration.total_milliseconds());
}

bool
CommunicationState::isCommunicationInterrupted() const {
    return (getDurationInMillisecs() > config_->getMaxResponseDelay());
}

size_t
CommunicationState::getAnalyzedMessagesCount() const {
    return (analyzed_messages_count_);
}

bool
CommunicationState::clockSkewShouldWarn() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (clockSkewShouldWarnInternal());
    } else {
        return (clockSkewShouldWarnInternal());
    }
}

bool
CommunicationState::clockSkewShouldWarnInternal() {
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
            LOG_WARN(ha_logger, HA_HIGH_CLOCK_SKEW)
                     .arg(logFormatClockSkewInternal());
            return (true);
        }
    }

    // The warning should not be issued.
    return (false);
}

bool
CommunicationState::clockSkewShouldTerminate() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        // Issue a warning if the clock skew is greater than 60s.
        return (clockSkewShouldTerminateInternal());
    } else {
        return (clockSkewShouldTerminateInternal());
    }
}

bool
CommunicationState::clockSkewShouldTerminateInternal() const {
    if (isClockSkewGreater(TERM_CLOCK_SKEW)) {
        LOG_ERROR(ha_logger, HA_HIGH_CLOCK_SKEW_CAUSES_TERMINATION)
                  .arg(logFormatClockSkewInternal());
        return (true);
    }

    return (false);
}

bool
CommunicationState::isClockSkewGreater(const long seconds) const {
    return ((clock_skew_.total_seconds() > seconds) ||
            (clock_skew_.total_seconds() < -seconds));
}

void
CommunicationState::setPartnerTime(const std::string& time_text) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        setPartnerTimeInternal(time_text);
    } else {
        setPartnerTimeInternal(time_text);
    }
}

void
CommunicationState::setPartnerTimeInternal(const std::string& time_text) {
    partner_time_at_skew_ = HttpDateTime().fromRfc1123(time_text).getPtime();
    my_time_at_skew_ = HttpDateTime().getPtime();
    clock_skew_ = partner_time_at_skew_ - my_time_at_skew_;
}

std::string
CommunicationState::logFormatClockSkew() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (logFormatClockSkewInternal());
    } else {
        return (logFormatClockSkewInternal());
    }
}

std::string
CommunicationState::logFormatClockSkewInternal() const {
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

ElementPtr
CommunicationState::getReport() const {
    auto report = Element::createMap();

    auto in_touch = (getPartnerState() > 0);
    report->set("in-touch", Element::create(in_touch));

    auto age = in_touch ? static_cast<long long int>(getDurationInMillisecs() / 1000) : 0;
    report->set("age", Element::create(age));

    try {
        report->set("last-state", Element::create(stateToString(getPartnerState())));

    } catch (...) {
        report->set("last-state", Element::create(std::string()));
    }

    auto list = Element::createList();
    for (auto scope : getPartnerScopes()) {
        list->add(Element::create(scope));
    }
    report->set("last-scopes", list);
    report->set("communication-interrupted",
                Element::create(isCommunicationInterrupted()));
    report->set("connecting-clients", Element::create(static_cast<long long>(getConnectingClientsCount())));
    report->set("unacked-clients", Element::create(static_cast<long long>(getUnackedClientsCount())));

    long long unacked_clients_left = 0;
    if (isCommunicationInterrupted() && (config_->getMaxUnackedClients() >= getUnackedClientsCount())) {
        unacked_clients_left = static_cast<long long>(config_->getMaxUnackedClients() -
                                                      getUnackedClientsCount() + 1);
    }
    report->set("unacked-clients-left", Element::create(unacked_clients_left));
    report->set("analyzed-packets", Element::create(static_cast<long long>(getAnalyzedMessagesCount())));

    return (report);
}

uint64_t
CommunicationState::getUnsentUpdateCount() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (unsent_update_count_);
    } else {
        return (unsent_update_count_);
    }
}

void
CommunicationState::increaseUnsentUpdateCount() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        increaseUnsentUpdateCountInternal();
    } else {
        increaseUnsentUpdateCountInternal();
    }
}

void
CommunicationState::increaseUnsentUpdateCountInternal() {
    // Protect against setting the incremented value to zero.
    // The zero value is reserved for a server startup.
    if (unsent_update_count_ < std::numeric_limits<uint64_t>::max()) {
        ++unsent_update_count_;
    } else {
        unsent_update_count_ = 1;
    }
}

bool
CommunicationState::hasPartnerNewUnsentUpdates() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (hasPartnerNewUnsentUpdatesInternal());
    } else {
        return (hasPartnerNewUnsentUpdatesInternal());
    }
}

bool
CommunicationState::hasPartnerNewUnsentUpdatesInternal() const {
    return (partner_unsent_update_count_.second > 0 &&
            (partner_unsent_update_count_.first != partner_unsent_update_count_.second));
}

void
CommunicationState::setPartnerUnsentUpdateCount(uint64_t unsent_update_count) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        setPartnerUnsentUpdateCountInternal(unsent_update_count);
    } else {
        setPartnerUnsentUpdateCountInternal(unsent_update_count);
    }
}

void
CommunicationState::setPartnerUnsentUpdateCountInternal(uint64_t unsent_update_count) {
    partner_unsent_update_count_.first = partner_unsent_update_count_.second;
    partner_unsent_update_count_.second = unsent_update_count;
}

CommunicationState4::CommunicationState4(const IOServicePtr& io_service,
                                         const HAConfigPtr& config)
    : CommunicationState(io_service, config), connecting_clients_() {
}

void
CommunicationState4::analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        analyzeMessageInternal(message);
    } else {
        analyzeMessageInternal(message);
    }
}

void
CommunicationState4::analyzeMessageInternal(const boost::shared_ptr<dhcp::Pkt>& message) {
    // The DHCP message must successfully cast to a Pkt4 object.
    Pkt4Ptr msg = boost::dynamic_pointer_cast<Pkt4>(message);
    if (!msg) {
        isc_throw(BadValue, "DHCP message to be analyzed is not a DHCPv4 message");
    }

    ++analyzed_messages_count_;

    // Check value of the "secs" field by comparing it with the configured
    // threshold.
    uint16_t secs = msg->getSecs();

    // It was observed that some Windows clients may send swapped bytes in the
    // "secs" field. When the second byte is 0 and the first byte is non-zero
    // we consider bytes to be swapped and so we correct them.
    if ((secs > 255) && ((secs & 0xFF) == 0)) {
        secs = ((secs >> 8) | (secs << 8));
    }

    // Check the value of the "secs" field. The "secs" field holds a value in
    // seconds, hence we have to multiple by 1000 to get a value in milliseconds.
    // If the secs value is above the threshold, it means that the current
    // client should be considered unacked.
    auto unacked = (secs * 1000 > config_->getMaxAckDelay());

    // Client identifier will be stored together with the hardware address. It
    // may remain empty if the client hasn't specified it.
    std::vector<uint8_t> client_id;
    OptionPtr opt_client_id = msg->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt_client_id) {
        client_id = opt_client_id->getData();
    }

    bool log_unacked = false;

    // Check if the given client was already recorded.
    auto& idx = connecting_clients_.get<0>();
    auto existing_request = idx.find(boost::make_tuple(msg->getHWAddr()->hwaddr_, client_id));
    if (existing_request != idx.end()) {
        // If the client was recorded and was not considered unacked
        // but it should be considered unacked as a result of processing
        // this packet, let's update the recorded request to mark the
        // client unacked.
        if (!existing_request->unacked_ && unacked) {
            ConnectingClient4 connecting_client{ msg->getHWAddr()->hwaddr_, client_id, unacked };
            idx.replace(existing_request, connecting_client);
            log_unacked = true;
        }

    } else {
        // This is the first time we see the packet from this client. Let's
        // record it.
        ConnectingClient4 connecting_client{ msg->getHWAddr()->hwaddr_, client_id, unacked };
        idx.insert(connecting_client);
        log_unacked = unacked;

        if (!unacked) {
            // This is the first time we see this client after getting into the
            // communication interrupted state. But, this client hasn't been
            // yet trying log enough to be considered unacked.
            LOG_INFO(ha_logger, HA_COMMUNICATION_INTERRUPTED_CLIENT4)
                .arg(message->getLabel());
        }
    }

    // Only log the first time we detect a client is unacked.
    if (log_unacked) {
        unsigned unacked_left = 0;
        unsigned unacked_total = connecting_clients_.get<1>().count(true);
        if (config_->getMaxUnackedClients() >= unacked_total) {
            unacked_left = config_->getMaxUnackedClients() - unacked_total + 1;
        }
        LOG_INFO(ha_logger, HA_COMMUNICATION_INTERRUPTED_CLIENT4_UNACKED)
            .arg(message->getLabel())
            .arg(unacked_total)
            .arg(unacked_left);
    }
}

bool
CommunicationState4::failureDetected() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (failureDetectedInternal());
    } else {
        return (failureDetectedInternal());
    }
}

bool
CommunicationState4::failureDetectedInternal() const {
    return ((config_->getMaxUnackedClients() == 0) ||
            (connecting_clients_.get<1>().count(true) >
             config_->getMaxUnackedClients()));
}

size_t
CommunicationState4::getConnectingClientsCount() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (connecting_clients_.size());
    } else {
        return (connecting_clients_.size());
    }
}

size_t
CommunicationState4::getUnackedClientsCount() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (connecting_clients_.get<1>().count(true));
    } else {
        return (connecting_clients_.get<1>().count(true));
    }
}

void
CommunicationState4::clearConnectingClients() {
    connecting_clients_.clear();
}

CommunicationState6::CommunicationState6(const IOServicePtr& io_service,
                                         const HAConfigPtr& config)
    : CommunicationState(io_service, config), connecting_clients_() {
}

void
CommunicationState6::analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        analyzeMessageInternal(message);
    } else {
        analyzeMessageInternal(message);
    }
}

void
CommunicationState6::analyzeMessageInternal(const boost::shared_ptr<dhcp::Pkt>& message) {
    // The DHCP message must successfully cast to a Pkt6 object.
    Pkt6Ptr msg = boost::dynamic_pointer_cast<Pkt6>(message);
    if (!msg) {
        isc_throw(BadValue, "DHCP message to be analyzed is not a DHCPv6 message");
    }

    ++analyzed_messages_count_;

    // Check the value of the "elapsed time" option. If it is below the threshold
    // there is nothing to do. The "elapsed time" option holds the time in
    // 1/100 of second, hence we have to multiply by 10 to get a value in milliseconds.
    OptionUint16Ptr elapsed_time = boost::dynamic_pointer_cast<
        OptionUint16>(msg->getOption(D6O_ELAPSED_TIME));
    auto unacked = (elapsed_time && elapsed_time->getValue() * 10 > config_->getMaxAckDelay());

    // Get the DUID of the client to see if it hasn't been recorded already.
    OptionPtr duid = msg->getOption(D6O_CLIENTID);
    if (!duid) {
        return;
    }

    bool log_unacked = false;

    // Check if the given client was already recorded.
    auto& idx = connecting_clients_.get<0>();
    auto existing_request = idx.find(duid->getData());
    if (existing_request != idx.end()) {
        // If the client was recorded and was not considered unacked
        // but it should be considered unacked as a result of processing
        // this packet, let's update the recorded request to mark the
        // client unacked.
        if (!existing_request->unacked_ && unacked) {
            ConnectingClient6 connecting_client{ duid->getData(), unacked };
            idx.replace(existing_request, connecting_client);
            log_unacked = true;
        }

    } else {
        // This is the first time we see the packet from this client. Let's
        // record it.
        ConnectingClient6 connecting_client{ duid->getData(), unacked };
        idx.insert(connecting_client);
        log_unacked = unacked;

        if (!unacked) {
            // This is the first time we see this client after getting into the
            // communication interrupted state. But, this client hasn't been
            // yet trying log enough to be considered unacked.
            LOG_INFO(ha_logger, HA_COMMUNICATION_INTERRUPTED_CLIENT6)
                .arg(message->getLabel());
        }
    }

    // Only log the first time we detect a client is unacked.
    if (log_unacked) {
        unsigned unacked_left = 0;
        unsigned unacked_total = connecting_clients_.get<1>().count(true);
        if (config_->getMaxUnackedClients() >= unacked_total) {
            unacked_left = config_->getMaxUnackedClients() - unacked_total + 1;
        }
        LOG_INFO(ha_logger, HA_COMMUNICATION_INTERRUPTED_CLIENT6_UNACKED)
            .arg(message->getLabel())
            .arg(unacked_total)
            .arg(unacked_left);
    }
}

bool
CommunicationState6::failureDetected() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (failureDetectedInternal());
    } else {
        return (failureDetectedInternal());
    }
}

bool
CommunicationState6::failureDetectedInternal() const {
    return ((config_->getMaxUnackedClients() == 0) ||
            (connecting_clients_.get<1>().count(true) >
             config_->getMaxUnackedClients()));
}

size_t
CommunicationState6::getConnectingClientsCount() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (connecting_clients_.size());
    } else {
        return (connecting_clients_.size());
    }
}

size_t
CommunicationState6::getUnackedClientsCount() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (connecting_clients_.get<1>().count(true));
    } else {
        return (connecting_clients_.get<1>().count(true));
    }
}

void
CommunicationState6::clearConnectingClients() {
    connecting_clients_.clear();
}

} // end of namespace isc::ha
} // end of namespace isc
