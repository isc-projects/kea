// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace isc {
namespace dhcp {

/// @brief Implementation of the @c NetworkState class.
class NetworkStateImpl : public boost::enable_shared_from_this<NetworkStateImpl> {
public:

    /// @brief Constructor.
    NetworkStateImpl(const NetworkState::ServerType& server_type)
        : server_type_(server_type), globally_disabled_(false), disabled_subnets_(),
          disabled_networks_(), timer_present_(false), timer_mgr_(TimerMgr::instance()) {
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

    /// @brief Creates a timer couting the time when @c enableAll should be
    /// automatically called.
    ///
    /// If the timer has been already scheduled, it is destroyed and replaced
    /// with a new timer.
    ///
    /// @param seconds Number of seconds to elapse before the @c enableAll is
    /// called.
    void createTimer(const unsigned int seconds) {
        destroyTimer();
        timer_mgr_->registerTimer("network-state-timer",
                                  boost::bind(&NetworkStateImpl::enableAll,
                                              shared_from_this()),
                                  seconds * 1000,
                                  asiolink::IntervalTimer::ONE_SHOT);
        timer_mgr_->setup("network-state-timer");
        timer_present_ = true;
    }

    /// @brief Destroys a timer if present.
    void destroyTimer() {
        if (timer_present_) {
            timer_mgr_->unregisterTimer("network-state-timer");
            timer_present_ = false;
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

    /// @brief Boolean flag indicating if the delayed enabling of the DHCP service
    /// has been scheduled.
    bool timer_present_;

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
    return (impl_->timer_present_);
}

void
NetworkState::selectiveDisable(const NetworkState::Subnets& subnets) {
    isc_throw(NotImplemented, "selectiveDisableService is not implemented");
}

void
NetworkState::selectiveDisable(const NetworkState::Networks& networks) {
    isc_throw(NotImplemented, "selectiveDisableService is not implemented");
}

void
NetworkState::selectiveEnable(const NetworkState::Subnets& subnets) {
    isc_throw(NotImplemented, "selectiveEnableService is not implemented");
}

void
NetworkState::selectiveEnable(const NetworkState::Networks& networks) {
    isc_throw(NotImplemented, "selectiveEnableService is not implemented");
}


} // end of namespace isc::dhcp
} // end of namespace isc
