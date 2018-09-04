// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

namespace {

/// @brief Name of the timer used by the @c NetworkState class.
const std::string NETWORK_STATE_TIMER_NAME = "network-state-timer";

} // end of anonymous namespace

namespace isc {
namespace dhcp {

/// @brief Implementation of the @c NetworkState class.
class NetworkStateImpl : public boost::enable_shared_from_this<NetworkStateImpl> {
public:

    /// @brief Constructor.
    NetworkStateImpl(const NetworkState::ServerType& server_type)
        : server_type_(server_type), globally_disabled_(false), disabled_subnets_(),
          disabled_networks_(), timer_mgr_(TimerMgr::instance()) {
    }

    /// @brief Destructor.
    ~NetworkStateImpl() {
        destroyTimer();
    }

    /// @brief Globally disables or enables DHCP service.
    void setDisableService(const bool disable) {
        globally_disabled_ = disable;
    }

    /// @brief Enables DHCP service globally and per scopes.
    ///
    /// If delayed enabling DHCP service has been scheduled, it cancels it.
    void enableAll() {
        setDisableService(false);

        /// @todo Enable service for all subnets and networks here.

        destroyTimer();
    }

    /// @brief Creates a timer counting the time when @c enableAll should be
    /// automatically called.
    ///
    /// If the timer has been already scheduled, it is destroyed and replaced
    /// with a new timer.
    ///
    /// @param seconds Number of seconds to elapse before the @c enableAll is
    /// called.
    void createTimer(const unsigned int seconds) {
        destroyTimer();
        timer_mgr_->registerTimer(NETWORK_STATE_TIMER_NAME,
                                  boost::bind(&NetworkStateImpl::enableAll,
                                              shared_from_this()),
                                  seconds * 1000,
                                  asiolink::IntervalTimer::ONE_SHOT);
        timer_mgr_->setup(NETWORK_STATE_TIMER_NAME);
    }

    /// @brief Destroys a timer if present.
    void destroyTimer() {
        if (timer_mgr_->isTimerRegistered(NETWORK_STATE_TIMER_NAME)) {
            timer_mgr_->unregisterTimer(NETWORK_STATE_TIMER_NAME);
        }
    }

    /// @brief Server type.
    NetworkState::ServerType server_type_;

    /// @brief A flag indicating if DHCP service is globally disabled.
    bool globally_disabled_;

    /// @brief A list of subnets for which the DHCP service has been disabled.
    NetworkState::Subnets disabled_subnets_;

    /// @brief A list of networks for which the DHCP service has been disabled.
    NetworkState::Networks disabled_networks_;

    /// @brief A pointer to the common timer manager.
    ///
    /// This pointer is held here to make sure that the timer manager is not
    /// destroyed before an instance of this class is destroyed.
    TimerMgrPtr timer_mgr_;
};

NetworkState::NetworkState(const NetworkState::ServerType& server_type)
    : impl_(new NetworkStateImpl(server_type)) {
}

void
NetworkState::disableService() {
    impl_->setDisableService(true);
}

void
NetworkState::enableService() {
    impl_->setDisableService(false);
}

void
NetworkState::enableAll() {
    impl_->enableAll();
}

void
NetworkState::delayedEnableAll(const unsigned int seconds) {
    impl_->createTimer(seconds);
}

bool
NetworkState::isServiceEnabled() const {
    return (!impl_->globally_disabled_);
}

bool
NetworkState::isDelayedEnableAll() const {
    return (TimerMgr::instance()->isTimerRegistered(NETWORK_STATE_TIMER_NAME));
}

void
NetworkState::selectiveDisable(const NetworkState::Subnets&) {
    isc_throw(NotImplemented, "selectiveDisableService is not implemented");
}

void
NetworkState::selectiveDisable(const NetworkState::Networks&) {
    isc_throw(NotImplemented, "selectiveDisableService is not implemented");
}

void
NetworkState::selectiveEnable(const NetworkState::Subnets&) {
    isc_throw(NotImplemented, "selectiveEnableService is not implemented");
}

void
NetworkState::selectiveEnable(const NetworkState::Networks&) {
    isc_throw(NotImplemented, "selectiveEnableService is not implemented");
}


} // end of namespace isc::dhcp
} // end of namespace isc
