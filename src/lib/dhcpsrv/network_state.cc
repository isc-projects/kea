// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/multi_threading_mgr.h>
#include <boost/enable_shared_from_this.hpp>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Implementation of the @c NetworkState class.
class NetworkStateImpl : public boost::enable_shared_from_this<NetworkStateImpl> {
public:

    /// @brief Constructor.
    NetworkStateImpl(const NetworkState::ServerType& server_type)
        : server_type_(server_type), globally_disabled_(false),
          disabled_subnets_(), disabled_networks_(),
          timer_mgr_(TimerMgr::instance()), disabled_by_origin_(),
          disabled_by_db_connection_(0) {
    }

    /// @brief Destructor.
    ~NetworkStateImpl() {
        for (auto origin : disabled_by_origin_) {
            destroyTimer(origin);
        }
    }

    /// @brief Sets appropriate disabled or enabled DHCP service state for the
    /// respective origin.
    ///
    /// @note If any of the user commands, HA internal commands or connection
    /// recovery processes disable the dhcp service, the service will remain
    /// disabled until all flags are cleared.
    /// In the case of the connection recovery a reference count is used
    /// internally, so that all connections must be restored before enabling
    /// the network state.
    ///
    /// @param disable The value of the flag used to perform the transition.
    /// @param origin The origin of the state transition.
    void setDisableService(const bool disable, unsigned int origin) {
        if (disable) {
            // Disable the service for any flag.
            globally_disabled_ = true;
            if (origin == NetworkState::DB_CONNECTION) {
                ++disabled_by_db_connection_;
            } else {
                disabled_by_origin_.insert(origin);
            }
        } else {
            if (origin == NetworkState::DB_CONNECTION) {
                // Never go below 0 (using unsigned type).
                // This should never happen anyway.
                if (disabled_by_db_connection_) {
                    --disabled_by_db_connection_;
                }
            } else {
                disabled_by_origin_.erase(origin);
            }
            // Enable the service only if all flags have been cleared.
            if (disabled_by_origin_.empty() && disabled_by_db_connection_ == 0) {
                globally_disabled_ = false;
            }
        }
    }

    /// @brief Reset internal counters for a specific origin.
    ///
    /// @note The dhcp service will remain disabled until all flags are cleared.
    ///
    /// @param origin The origin of the state transition.
    void reset(unsigned int origin) {
        if (origin == NetworkState::DB_CONNECTION) {
            disabled_by_db_connection_ = 0;
        } else {
            disabled_by_origin_.erase(origin);
        }
        // Enable the service only if all flags have been cleared.
        if (disabled_by_origin_.empty() && disabled_by_db_connection_ == 0) {
            globally_disabled_ = false;
        }
    }

    /// @brief Enables DHCP service globally and per scopes.
    ///
    /// If delayed enabling DHCP service has been scheduled, it cancels it.
    ///
    /// @param origin The origin of the state transition.
    void enableAll(unsigned int origin) {
        setDisableService(false, origin);

        /// @todo Enable service for all subnets and networks here.

        destroyTimer(origin);
    }

    /// @brief Creates a timer counting the time when @c enableAll should be
    /// automatically called.
    ///
    /// If the timer has been already scheduled, it is destroyed and replaced
    /// with a new timer.
    ///
    /// @param seconds Number of seconds to elapse before the @c enableAll is
    /// called.
    /// @param origin The origin of the state transition.
    void createTimer(const unsigned int seconds, unsigned int origin) {
        destroyTimer(origin);
        if (origin == NetworkState::DB_CONNECTION) {
            isc_throw(BadValue, "DB connection does not support delayed enable");
        }
        auto timer_name = getTimerName(origin);
        timer_mgr_->registerTimer(timer_name,
                                  std::bind(&NetworkStateImpl::enableAll,
                                            shared_from_this(), origin),
                                  seconds * 1000,
                                  asiolink::IntervalTimer::ONE_SHOT);
        timer_mgr_->setup(timer_name);
    }

    /// @brief Destroys a timer if present.
    ///
    /// @param origin The origin of the state transition.
    void destroyTimer(unsigned int origin) {
        if (origin == NetworkState::DB_CONNECTION) {
            return;
        }
        auto timer_name = getTimerName(origin);
        if (timer_mgr_->isTimerRegistered(timer_name)) {
            timer_mgr_->unregisterTimer(timer_name);
        }
    }

    /// @brief Creates a unique timer name from the origin.
    ///
    /// @param origin The origin of the state transition.
    /// @return Unique timer name for the origin.
    std::string getTimerName(unsigned int origin) const {
        std::ostringstream timer_name;
        timer_name << "network-state-timer-" << origin;
        return (timer_name.str());
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

    /// @brief A set of requests to disable the service by origin.
    std::unordered_set<unsigned int> disabled_by_origin_;

    /// @brief Flag which indicates the state has been disabled by a DB
    /// connection loss.
    uint32_t disabled_by_db_connection_;
};

NetworkState::NetworkState(const NetworkState::ServerType& server_type)
    : impl_(new NetworkStateImpl(server_type)), mutex_(new std::mutex()) {
}

void
NetworkState::disableService(unsigned int origin) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        impl_->setDisableService(true, origin);
    } else {
        impl_->setDisableService(true, origin);
    }
}

void
NetworkState::enableService(unsigned int origin) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        impl_->setDisableService(false, origin);
    } else {
        impl_->setDisableService(false, origin);
    }
}

void
NetworkState::reset(unsigned int origin) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        impl_->reset(origin);
    } else {
        impl_->reset(origin);
    }
}

void
NetworkState::enableAll(unsigned int origin) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        impl_->enableAll(origin);
    } else {
        impl_->enableAll(origin);
    }
}

void
NetworkState::delayedEnableAll(const unsigned int seconds, unsigned int origin) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        impl_->createTimer(seconds, origin);
    } else {
        impl_->createTimer(seconds, origin);
    }
}

bool
NetworkState::isServiceEnabled() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(*mutex_);
        return (!impl_->globally_disabled_);
    } else {
        return (!impl_->globally_disabled_);
    }
}

bool
NetworkState::isDelayedEnableAll() const {
    for (auto origin : impl_->disabled_by_origin_) {
        if (TimerMgr::instance()->isTimerRegistered(impl_->getTimerName(origin))) {
            return (true);
        }
    }
    return (false);
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
