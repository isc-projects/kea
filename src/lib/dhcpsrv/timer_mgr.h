// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TIMER_MGR_H
#define TIMER_MGR_H

#include <asiolink/interval_timer.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of the @c TimerMgr implementation.
class TimerMgrImpl;

typedef boost::shared_ptr<TimerMgrImpl> TimerMgrImplPtr;

/// @brief Forward declaration of the @c TimerMgr.
class TimerMgr;

/// @brief Type definition of the shared pointer to @c TimerMgr.
typedef boost::shared_ptr<TimerMgr> TimerMgrPtr;

/// @brief Manages a pool of asynchronous interval timers.
///
/// This class holds a pool of asynchronous interval timers.
///
/// This class is useful for performing periodic actions at the specified
/// intervals, e.g. act upon expired leases (leases reclamation) or
/// return declined leases back to the address pool. Other applications
/// may be added in the future.
///
/// The @c TimerMgr is a singleton, thus its instance is available from
/// different places in the server code. This is convenient because timers
/// can be installed by different configuration parsers or they can be
/// re-scheduled from the callback functions.
///
/// The timer is registered using the @c TimerMgr::registerTimer method.
/// Each registered timer has a unique name. It is not possible to register
/// multiple timers with the same name. Each registered timer is associated
/// with the callback function supplied by the caller. This callback function
/// performs the tasks to be executed periodically according to the timer's
/// interval.
///
/// The registered timer's interval does not begin to elapse until the
/// @c TimerMgr::setup method is called for it.
///
/// Before the @c TimerMgr can be used the server process must call
/// @c TimerMgr::setIOService to associate the manager with the IO service
/// that the server is using to its run tasks.
///
/// @note Only scheduling new timer (calling @ref setup) and canceling existing
/// timer (calling @ref cancel) are thread safe.
/// Registering new timers (calling @ref registerTimer) and unregistering
/// existing timers (calling @ref unregisterTimer) must be handled before
/// starting processing threads.
class TimerMgr : public boost::noncopyable {
public:

    /// @brief Returns pointer to the sole instance of the @c TimerMgr.
    static const TimerMgrPtr& instance();

    /// @brief Destructor.
    ///
    /// Stops the worker thread if it is running and unregisters any
    /// registered timers.
    ~TimerMgr();

    /// @brief Sets IO service to be used by the Timer Manager.
    ///
    /// @param io_service Pointer to the new IO service.
    void setIOService(const asiolink::IOServicePtr& io_service);

    /// @name Registering, unregistering and scheduling the timers.
    //@{

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
    /// This method cancels the timer if it is setup and removes it from the
    /// internal collection of timers.
    ///
    /// @param timer_name Name of the timer to be unregistered.
    ///
    /// @throw BadValue if the specified timer hasn't been registered.
    void unregisterTimer(const std::string& timer_name);

    /// @brief Unregisters all timers.
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
    /// This method has no effect if the timer hasn't been scheduled with
    /// the @c TimerMgr::setup method.
    ///
    /// @param timer_name Unique timer name.
    ///
    /// @throw BadValue if the timer hasn't been registered.
    void cancel(const std::string& timer_name);

    //@}

private:

    /// @brief Private default constructor.
    ///
    /// The @c TimerMgr is a singleton class which instance must be created
    /// using the @c TimerMgr::instance method. Private constructor enforces
    /// construction via @c TimerMgr::instance.
    TimerMgr();

    /// @brief The @c TimerMgr implementation.
    TimerMgrImplPtr impl_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // TIMER_MGR_H
