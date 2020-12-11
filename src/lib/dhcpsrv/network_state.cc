// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <boost/enable_shared_from_this.hpp>
#include <functional>
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
        : server_type_(server_type), globally_disabled_(false),
          disabled_subnets_(), disabled_networks_(),
          timer_mgr_(TimerMgr::instance()), disabled_by_command_(false),
          disabled_by_connection_(0), disabled_by_ha_(false) {
    }

    /// @brief Destructor.
    ~NetworkStateImpl() {
        destroyTimer();
    }

    /// @brief Globally disables or enables DHCP service.
    void setDisableService(const bool disable,
                           const NetworkState::ControllerType& type) {
        if (disable) {
            globally_disabled_ = true;
            switch (type) {
            case NetworkState::COMMAND:
                disabled_by_command_ = true;
                break;
            case NetworkState::CONNECTION:
                ++disabled_by_connection_;
                break;
            case NetworkState::HA:
                disabled_by_ha_ = true;
                break;
            }
        } else {
            switch (type) {
            case NetworkState::COMMAND:
                disabled_by_command_ = false;
                break;
            case NetworkState::CONNECTION:
                if (disabled_by_connection_) {
                    --disabled_by_connection_;
                }
                break;
            case NetworkState::HA:
                disabled_by_ha_ = false;
                break;
            }
            if (!disabled_by_command_ && disabled_by_connection_ == 0 &&
                !disabled_by_ha_) {
                globally_disabled_ = false;
            }
        }
    }

    /// @brief Reset internal counters.
    void resetInternalState(const NetworkState::ControllerType& type) {
        switch (type) {
        case NetworkState::COMMAND:
            disabled_by_command_ = false;
            break;
        case NetworkState::CONNECTION:
            disabled_by_connection_ = 0;
            break;
        case NetworkState::HA:
            disabled_by_ha_ = false;
            break;
        }
        if (!disabled_by_command_ && disabled_by_connection_ == 0 &&
            !disabled_by_ha_) {
            globally_disabled_ = false;
        }
    }

    /// @brief Enables DHCP service globally and per scopes.
    ///
    /// If delayed enabling DHCP service has been scheduled, it cancels it.
    void enableAll() {
        setDisableService(false, NetworkState::COMMAND);

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
                                  std::bind(&NetworkStateImpl::enableAll,
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

    /// @brief Flag which indicates the state has been disabled by a command.
    bool disabled_by_command_;

    /// @brief Flag which indicates the state has been disabled by a connection
    /// loss.
    uint32_t disabled_by_connection_;

    /// @brief Flag which indicates the state has been disabled by the HA lib.
    bool disabled_by_ha_;
};

NetworkState::NetworkState(const NetworkState::ServerType& server_type)
    : impl_(new NetworkStateImpl(server_type)) {
}

void
NetworkState::disableService(const ControllerType& type) {
    impl_->setDisableService(true, type);
}

void
NetworkState::enableService(const ControllerType& type) {
    impl_->setDisableService(false, type);
}

void
NetworkState::resetInternalState(const NetworkState::ControllerType& type) {
    impl_->resetInternalState(type);
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
