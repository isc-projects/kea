// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
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

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Implementation of the @c NetworkState class.
class NetworkStateImpl : public boost::enable_shared_from_this<NetworkStateImpl>,
                         public CfgToElement {
public:

    /// @brief Constructor.
    NetworkStateImpl() : globally_disabled_(false), disabled_subnets_(),
          disabled_networks_(), timer_mgr_(TimerMgr::instance()),
          disabled_by_origin_(), disabled_by_db_connection_(0) {
    }

    /// @brief Destructor.
    ~NetworkStateImpl() {
        for (auto const& origin : disabled_by_origin_) {
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

    /// @brief Reset internal counters for a database connection origin.
    ///
    /// @note The dhcp service will remain disabled until all flags are cleared.
    void resetForDbConnection() {
        disabled_by_db_connection_ = 0;
        if (disabled_by_origin_.empty()) {
            globally_disabled_ = false;
        }
    }

    /// @brief Reset origin for local commands.
    ///
    /// @note The dhcp service will remain disabled until all flags are cleared.
    void resetForLocalCommands() {
        auto disabled_by_origin = disabled_by_origin_;
        for (auto const& origin : disabled_by_origin) {
            if (origin >= NetworkState::HA_LOCAL_COMMAND &&
                origin < NetworkState::HA_REMOTE_COMMAND) {
                disabled_by_origin_.erase(origin);
            }
        }
        if (disabled_by_origin_.empty() && disabled_by_db_connection_ == 0) {
            globally_disabled_ = false;
        }
    }

    /// @brief Reset origin for remote commands.
    ///
    /// @note The dhcp service will remain disabled until all flags are cleared.
    void resetForRemoteCommands() {
        auto disabled_by_origin = disabled_by_origin_;
        for (auto const& origin : disabled_by_origin) {
            if (origin >= NetworkState::HA_REMOTE_COMMAND &&
                origin < NetworkState::DB_CONNECTION) {
                disabled_by_origin_.erase(origin);
            }
        }
        if (disabled_by_origin_.empty() && disabled_by_db_connection_ == 0) {
            globally_disabled_ = false;
        }
    }

    /// @brief Enables DHCP service for an origin.
    ///
    /// If delayed enabling DHCP service has been scheduled, it cancels it.
    ///
    /// @param origin The origin of the state transition.
    void delayedEnable(unsigned int origin) {
        setDisableService(false, origin);
        destroyTimer(origin);
    }

    /// @brief Creates a timer counting the time when @c delayedEnable should be
    /// automatically called.
    ///
    /// If the timer has been already scheduled, it is destroyed and replaced
    /// with a new timer.
    ///
    /// @param seconds Number of seconds to elapse before the @c delayedEnable is
    /// called.
    /// @param origin The origin of the state transition.
    void createTimer(const unsigned int seconds, unsigned int origin) {
        destroyTimer(origin);
        if (origin == NetworkState::DB_CONNECTION) {
            isc_throw(BadValue, "DB connection does not support delayed enable");
        }
        auto timer_name = getTimerName(origin);
        timer_mgr_->registerTimer(timer_name,
                                  std::bind(&NetworkStateImpl::delayedEnable,
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

    /// @brief The network state as Element.
    ///
    /// @return The network state as Element.
    virtual ElementPtr toElement() const {
        ElementPtr result = Element::createMap();
        result->set("globally-disabled", Element::create(globally_disabled_));
        result->set("disabled-by-db-connection", Element::create(disabled_by_db_connection_ != 0));
        bool disabled_by_user = false;
        ElementPtr local_origin = Element::createList();
        ElementPtr remote_origin = Element::createList();
        std::set<unsigned int> ordered(disabled_by_origin_.begin(), disabled_by_origin_.end());
        for (auto const& origin : ordered) {
            if (origin == NetworkState::USER_COMMAND) {
                disabled_by_user = true;
            }
            if (origin >= NetworkState::HA_LOCAL_COMMAND && origin < NetworkState::HA_REMOTE_COMMAND) {
                local_origin->add(Element::create(origin));
            }
            if (origin >= NetworkState::HA_REMOTE_COMMAND && origin < NetworkState::DB_CONNECTION) {
                remote_origin->add(Element::create(origin));
            }
        }
        result->set("disabled-by-user", Element::create(disabled_by_user));
        result->set("disabled-by-local-command", local_origin);
        result->set("disabled-by-remote-command", remote_origin);

        return (result);
    }

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

NetworkState::NetworkState()
    : impl_(new NetworkStateImpl()), mutex_(new std::mutex()) {
}

void
NetworkState::disableService(unsigned int origin) {
    MultiThreadingLock lock(*mutex_);
    impl_->setDisableService(true, origin);
}

void
NetworkState::enableService(unsigned int origin) {
    MultiThreadingLock lock(*mutex_);
    impl_->delayedEnable(origin);
}

void
NetworkState::resetForDbConnection() {
    MultiThreadingLock lock(*mutex_);
    impl_->resetForDbConnection();
}

void
NetworkState::resetForLocalCommands() {
    MultiThreadingLock lock(*mutex_);
    impl_->resetForLocalCommands();
}

void
NetworkState::resetForRemoteCommands() {
    MultiThreadingLock lock(*mutex_);
    impl_->resetForRemoteCommands();
}

void
NetworkState::delayedEnableService(const unsigned int seconds, unsigned int origin) {
    MultiThreadingLock lock(*mutex_);
    impl_->createTimer(seconds, origin);
}

bool
NetworkState::isServiceEnabled() const {
    MultiThreadingLock lock(*mutex_);
    return (!impl_->globally_disabled_);
}

bool
NetworkState::isDelayedEnableService() const {
    for (auto const& origin : impl_->disabled_by_origin_) {
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

ElementPtr NetworkState::toElement() const {
    MultiThreadingLock lock(*mutex_);
    return (impl_->toElement());
}

} // end of namespace isc::dhcp
} // end of namespace isc
