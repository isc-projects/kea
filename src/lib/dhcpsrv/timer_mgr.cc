// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>
#include <util/multi_threading_mgr.h>

#include <boost/scoped_ptr.hpp>

#include <exception>
#include <functional>
#include <map>
#include <mutex>
#include <ostream>
#include <string>
#include <utility>

#include <stddef.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::util;

namespace {

/// @brief Structure holding information for a single timer.
///
/// This structure holds the instance of the watch socket being used to
/// signal that the timer is "ready". It also holds the instance of the
/// interval timer and other parameters pertaining to it.
struct TimerInfo {
    /// @brief Instance of the interval timer.
    asiolink::IntervalTimer interval_timer_;

    /// @brief Holds the pointer to the callback supplied when registering
    /// the timer.
    asiolink::IntervalTimer::Callback user_callback_;

    /// @brief Interval timer interval supplied during registration.
    long interval_;

    /// @brief Interval timer scheduling mode supplied during registration.
    asiolink::IntervalTimer::Mode scheduling_mode_;

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service to be used by the
    /// interval timer created.
    /// @param user_callback Pointer to the callback function supplied
    /// during the timer registration.
    /// @param interval Timer interval in milliseconds.
    /// @param mode Interval timer scheduling mode.
    TimerInfo(asiolink::IOService& io_service,
              const asiolink::IntervalTimer::Callback& user_callback,
              const long interval,
              const asiolink::IntervalTimer::Mode& mode)
        : interval_timer_(io_service),
          user_callback_(user_callback),
          interval_(interval),
          scheduling_mode_(mode) { };
};

}

namespace isc {
namespace dhcp {

/// @brief A type definition for the pointer to @c TimerInfo structure.
typedef boost::shared_ptr<TimerInfo> TimerInfoPtr;

/// @brief A type definition for the map holding timers configuration.
typedef std::map<std::string, TimerInfoPtr> TimerInfoMap;

/// @brief Implementation of the @c TimerMgr
class TimerMgrImpl {
public:

    /// @brief Constructor.
    TimerMgrImpl();

    /// @brief Sets IO service to be used by the Timer Manager.
    ///
    /// @param io_service Pointer to the new IO service.
    void setIOService(const IOServicePtr& io_service);

    /// @brief Registers new timer in the @c TimerMgr.
    ///
    /// @param timer_name Unique name for the timer.
    /// @param callback Pointer to the callback function to be invoked
    /// when the timer elapses, e.g. function processing expired leases
    /// in the DHCP server.
    /// @param interval Timer interval in milliseconds.
    /// @param scheduling_mode Scheduling mode of the timer as described in
    /// @c asiolink::IntervalTimer::Mode.
    ///
    /// @throw BadValue if the timer name is invalid or duplicate.
    void registerTimer(const std::string& timer_name,
                       const asiolink::IntervalTimer::Callback& callback,
                       const long interval,
                       const asiolink::IntervalTimer::Mode& scheduling_mode);


    /// @brief Unregisters specified timer.
    ///
    /// This method cancels the timer if it is setup and removes the timer
    /// from the internal collection of timers.
    ///
    /// @param timer_name Name of the timer to be unregistered.
    ///
    /// @throw BadValue if the specified timer hasn't been registered.
    void unregisterTimer(const std::string& timer_name);

    /// @brief Unregisters all timers.
    ///
    /// This method must be explicitly called prior to termination of the
    /// process.
    void unregisterTimers();

    /// @brief Checks if the timer with a specified name has been registered.
    ///
    /// @param timer_name Name of the timer.
    /// @return true if the timer with the specified name has been registered,
    /// false otherwise.
    bool isTimerRegistered(const std::string& timer_name);

    /// @brief Returns the number of registered timers.
    size_t timersCount() const;

    /// @brief Schedules the execution of the interval timer.
    ///
    /// This method schedules the timer, i.e. the callback will be executed
    /// after specified interval elapses. The interval has been specified
    /// during timer registration. Depending on the mode selected during the
    /// timer registration, the callback will be executed once after it has
    /// been scheduled or until it is cancelled. Though, in the former case
    /// the timer can be re-scheduled in the callback function.
    ///
    /// @param timer_name Unique timer name.
    ///
    /// @throw BadValue if the timer hasn't been registered.
    void setup(const std::string& timer_name);

    /// @brief Cancels the execution of the interval timer.
    ///
    /// @param timer_name Unique timer name.
    ///
    /// @throw BadValue if the timer hasn't been registered.
    void cancel(const std::string& timer_name);

private:

    /// @name Internal methods called while holding the mutex in multi threading
    /// mode.

    /// @brief Registers new timer in the @c TimerMgr.
    ///
    /// @param timer_name Unique name for the timer.
    /// @param callback Pointer to the callback function to be invoked
    /// when the timer elapses, e.g. function processing expired leases
    /// in the DHCP server.
    /// @param interval Timer interval in milliseconds.
    /// @param scheduling_mode Scheduling mode of the timer as described in
    /// @c asiolink::IntervalTimer::Mode.
    ///
    /// @throw BadValue if the timer name is invalid or duplicate.
    void registerTimerInternal(const std::string& timer_name,
                               const asiolink::IntervalTimer::Callback& callback,
                               const long interval,
                               const asiolink::IntervalTimer::Mode& scheduling_mode);


    /// @brief Unregisters specified timer.
    ///
    /// This method cancels the timer if it is setup and removes the timer
    /// from the internal collection of timers.
    ///
    /// @param timer_name Name of the timer to be unregistered.
    ///
    /// @throw BadValue if the specified timer hasn't been registered.
    void unregisterTimerInternal(const std::string& timer_name);

    /// @brief Unregisters all timers.
    ///
    /// This method must be explicitly called prior to termination of the
    /// process.
    void unregisterTimersInternal();

    /// @brief Schedules the execution of the interval timer.
    ///
    /// This method schedules the timer, i.e. the callback will be executed
    /// after specified interval elapses. The interval has been specified
    /// during timer registration. Depending on the mode selected during the
    /// timer registration, the callback will be executed once after it has
    /// been scheduled or until it is cancelled. Though, in the former case
    /// the timer can be re-scheduled in the callback function.
    ///
    /// @param timer_name Unique timer name.
    ///
    /// @throw BadValue if the timer hasn't been registered.
    void setupInternal(const std::string& timer_name);

    /// @brief Cancels the execution of the interval timer.
    ///
    /// @param timer_name Unique timer name.
    ///
    /// @throw BadValue if the timer hasn't been registered.
    void cancelInternal(const std::string& timer_name);

    /// @brief Callback function to be executed for each interval timer when
    /// its scheduled interval elapses.
    ///
    /// @param timer_name Unique timer name.
    void timerCallback(const std::string& timer_name);

    /// @brief Pointer to the io service.
    asiolink::IOServicePtr io_service_;

    /// @brief Holds mapping of the timer name to timer instance and other
    /// parameters pertaining to the timer.
    TimerInfoMap registered_timers_;

    /// @brief The mutex to protect the timer manager.
    boost::scoped_ptr<std::mutex> mutex_;
};

TimerMgrImpl::TimerMgrImpl() : io_service_(new IOService()),
    registered_timers_(), mutex_(new std::mutex) {
}

void
TimerMgrImpl::setIOService(const IOServicePtr& io_service) {
    if (!io_service) {
        isc_throw(BadValue, "IO service object must not be null for TimerMgr");
    }

    io_service_ = io_service;
}

void
TimerMgrImpl::registerTimer(const std::string& timer_name,
                            const IntervalTimer::Callback& callback,
                            const long interval,
                            const IntervalTimer::Mode& scheduling_mode) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        registerTimerInternal(timer_name, callback, interval, scheduling_mode);
    } else {
        registerTimerInternal(timer_name, callback, interval, scheduling_mode);
    }
}

void
TimerMgrImpl::registerTimerInternal(const std::string& timer_name,
                                    const IntervalTimer::Callback& callback,
                                    const long interval,
                                    const IntervalTimer::Mode& scheduling_mode) {
    // Timer name must not be empty.
    if (timer_name.empty()) {
        isc_throw(BadValue, "registered timer name must not be empty");
    }

    // Must not register two timers under the same name.
    if (registered_timers_.find(timer_name) != registered_timers_.end()) {
        isc_throw(BadValue, "trying to register duplicate timer '"
                  << timer_name << "'");
    }

    // Create a structure holding the configuration for the timer. It will
    // create the instance if the IntervalTimer. It will also hold the
    // callback, interval and scheduling mode parameters.
    TimerInfoPtr timer_info(new TimerInfo(*io_service_, callback,
                                          interval, scheduling_mode));

    // Actually register the timer.
    registered_timers_.insert(std::pair<std::string, TimerInfoPtr>(timer_name,
                                                                   timer_info));
}

void
TimerMgrImpl::unregisterTimer(const std::string& timer_name) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        unregisterTimerInternal(timer_name);
    } else {
        unregisterTimerInternal(timer_name);
    }
}

void
TimerMgrImpl::unregisterTimerInternal(const std::string& timer_name) {
    // Find the timer with specified name.
    TimerInfoMap::iterator timer_info_it = registered_timers_.find(timer_name);

    // Check if the timer has been registered.
    if (timer_info_it == registered_timers_.end()) {
        isc_throw(BadValue, "unable to unregister non existing timer '"
                  << timer_name << "'");
    }

    // Cancel any pending asynchronous operation and stop the timer.
    cancelInternal(timer_name);

    // Remove the timer.
    registered_timers_.erase(timer_info_it);
}

void
TimerMgrImpl::unregisterTimers() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        unregisterTimersInternal();
    } else {
        unregisterTimersInternal();
    }
}

void
TimerMgrImpl::unregisterTimersInternal() {
    // Copy the map holding timers configuration. This is required so as
    // we don't cut the branch which we're sitting on when we will be
    // erasing the timers. We're going to iterate over the register timers
    // and remove them with the call to unregisterTimer function. But this
    // function will remove them from the register_timers_ map. If we
    // didn't work on the copy here, our iterator would invalidate. The
    // TimerInfo structure is copyable and since it is using the shared
    // pointers the copy is not expensive. Also this function is called when
    // the process terminates so it is not critical for performance.
    TimerInfoMap registered_timers_copy(registered_timers_);

    // Iterate over the existing timers and unregister them.
    for (TimerInfoMap::iterator timer_info_it = registered_timers_copy.begin();
         timer_info_it != registered_timers_copy.end(); ++timer_info_it) {
        unregisterTimerInternal(timer_info_it->first);
    }
}

bool
TimerMgrImpl::isTimerRegistered(const std::string& timer_name) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (registered_timers_.find(timer_name) != registered_timers_.end());
    } else {
        return (registered_timers_.find(timer_name) != registered_timers_.end());
    }
}

size_t
TimerMgrImpl::timersCount() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (registered_timers_.size());
    } else {
        return (registered_timers_.size());
    }
}

void
TimerMgrImpl::setup(const std::string& timer_name) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        setupInternal(timer_name);
    } else {
        setupInternal(timer_name);
    }
}

void
TimerMgrImpl::setupInternal(const std::string& timer_name) {
   // Check if the specified timer exists.
   TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
   if (timer_info_it == registered_timers_.end()) {
       isc_throw(BadValue, "unable to setup timer '" << timer_name << "': "
                 "no such timer registered");
   }

   // Schedule the execution of the timer using the parameters supplied
   // during the registration.
   const TimerInfoPtr& timer_info = timer_info_it->second;
   IntervalTimer::Callback cb = std::bind(&TimerMgrImpl::timerCallback, this,
                                          timer_name);
   timer_info->interval_timer_.setup(cb, timer_info->interval_,
                                     timer_info->scheduling_mode_);
}

void
TimerMgrImpl::cancel(const std::string& timer_name) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        cancelInternal(timer_name);
    } else {
        cancelInternal(timer_name);
    }
}

void
TimerMgrImpl::cancelInternal(const std::string& timer_name) {
    // Find the timer of our interest.
    TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it == registered_timers_.end()) {
        isc_throw(BadValue, "unable to cancel timer '" << timer_name << "': "
                  "no such timer registered");
    }
    // Cancel the timer.
    timer_info_it->second->interval_timer_.cancel();
}

void
TimerMgrImpl::timerCallback(const std::string& timer_name) {
    // Find the specified timer setup.
    TimerInfoMap::iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it != registered_timers_.end()) {

        // Running user-defined operation for the timer. Logging it
        // on the slightly lower debug level as there may be many
        // such traces.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_TIMERMGR_RUN_TIMER_OPERATION)
            .arg(timer_info_it->first);

        std::string error_string;
        try {
            timer_info_it->second->user_callback_();

        } catch (const std::exception& ex){
            error_string = ex.what();

        } catch (...) {
            error_string = "unknown reason";
        }

        // Exception was thrown. Log an error.
        if (!error_string.empty()) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_TIMERMGR_CALLBACK_FAILED)
                .arg(timer_info_it->first)
                .arg(error_string);
        }
    }
}

const TimerMgrPtr&
TimerMgr::instance() {
    static TimerMgrPtr timer_mgr(new TimerMgr());
    return (timer_mgr);
}

TimerMgr::TimerMgr()
    : impl_(new TimerMgrImpl()) {
}

TimerMgr::~TimerMgr() {
    impl_->unregisterTimers();
}

void
TimerMgr::registerTimer(const std::string& timer_name,
                        const IntervalTimer::Callback& callback,
                        const long interval,
                        const IntervalTimer::Mode& scheduling_mode) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_REGISTER_TIMER)
        .arg(timer_name)
        .arg(interval);

    impl_->registerTimer(timer_name, callback, interval, scheduling_mode);
}

void
TimerMgr::unregisterTimer(const std::string& timer_name) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_UNREGISTER_TIMER)
        .arg(timer_name);

    impl_->unregisterTimer(timer_name);
}

void
TimerMgr::unregisterTimers() {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_UNREGISTER_ALL_TIMERS);

    impl_->unregisterTimers();
}

bool
TimerMgr::isTimerRegistered(const std::string& timer_name) {
    return (impl_->isTimerRegistered(timer_name));
}

size_t
TimerMgr::timersCount() const {
    return (impl_->timersCount());
}

void
TimerMgr::setup(const std::string& timer_name) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_START_TIMER)
        .arg(timer_name);

    impl_->setup(timer_name);
}

void
TimerMgr::cancel(const std::string& timer_name) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_STOP_TIMER)
        .arg(timer_name);

    impl_->cancel(timer_name);
}

void
TimerMgr::setIOService(const IOServicePtr& io_service) {
    impl_->setIOService(io_service);
}

} // end of namespace isc::dhcp
} // end of namespace isc
