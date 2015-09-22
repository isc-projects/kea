// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

/// @brief Forward declaration of the @c TimerMgr.
class TimerMgr;

/// @brief Type definition of the shared pointer to @c TimerMgr.
typedef boost::shared_ptr<TimerMgr> TimerMgrPtr;

/// @brief Manages a pool of asynchronous interval timers for DHCP server.
///
/// This class holds a pool of asynchronous interval timers which are
/// capable of interrupting the blocking call to @c select() function in
/// the main threads of the DHCP servers. The main thread can then
/// timely execute the callback function associated with the particular
/// timer.
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
/// The @c TimerMgr uses worker thread to run the timers. The thread is
/// started and stopped using the @c TimerMgr::startThread and
/// @c TimerMgr::stopThread respectively. The thread calls the blocking
/// @c IOService::run. All the registered timers are associated with
/// this instance of the @c IOService that the thread is running.
/// When the timer elapses a generic callback function is executed
/// @c TimerMgr::timerCallback with the parameter giving the name
/// of the timer for which it has been executed.
///
/// Every registered timer is associated with an instance of the
/// @c util::WatchSocket object. The socket is registered in the
/// @c IfaceMgr as an "external" socket. When the generic callback
/// function is invoked for the timer, it obtains the instance of the
/// @c util::WatchSocket and marks it "ready". This call effectively
/// writes the data to a socket (pipe) which interrupts the call
/// to the @c select() function in the main thread. When the
/// @c IfaceMgr (in the main thread) detects data transmitted over
/// the external socket it will invoke a callback function
/// associated with this socket. This is the
/// @c TimerMgr::ifaceMgrCallback associated with the socket when the
/// timer is registered. This callback function is executed in the
/// main thread. It clears the socket, which unblocks the worker
/// thread. It also invokes the user callback function specified
/// for a given timer.
///
/// The @c TimerMgr::timerCallback function searches for the
/// registered timer for which it has been called. This may cause
/// race conditions between the worker thread and the main thread
/// if the latter is modifying the collection of the registered
/// timers. Therefore, the @c TimerMgr does not allow for
/// registering or unregistering the timers when the worker thread
/// is running. The worker thread must be stopped first.
/// It is possible to call @c TimerMgr::setup and @c TimerMgr::cancel
/// while the worker thread is running but this is considered
/// unreliable (may cause race conditions) except the case when the
/// @c TimerMgr::setup is called from the installed callback
/// function to reschedule the ONE_SHOT timer. This is thread safe
/// because the worker thread is blocked while the callback function
/// is executed.
///
/// The worker thread is blocked when it executes a generic callback
/// function in the @c TimerMgr, which marks the watch socket
/// associated with the elapsed timer as "ready". The thread waits
/// in the callback function until it is notified by the main thread
/// (via conditional variable), that one of the watch sockets has
/// been cleared. It then checks if the main thread cleared the
/// socket that the worker thread had set. It continues to block
/// if this was a different socket. It returns (unblocks) otherwise.
/// The main thread clears the socket when the @c IfaceMgr detects
/// that this socket has been marked ready by the worker thread.
/// This is triggered only when the @c IfaceMgr::receive4 or
/// @c IfaceMgr::receive6 is called. They are called in the main
/// loops of the DHCP servers, which are also responsible for
/// processing received packets. Therefore it may take some
/// time for the main loop to detect that the socket has been
/// marked ready, call appropriate handler for it and clear it.
/// In the mean time, the worker thread will remain blocked.
///
class TimerMgr : public boost::noncopyable {
public:

    /// @brief Returns pointer to the sole instance of the @c TimerMgr.
    static const TimerMgrPtr& instance();

    /// @brief Destructor.
    ///
    /// Stops the worker thread if it is running and unregisteres any
    /// registered timers.
    ~TimerMgr();

    /// @name Registering, unregistering and scheduling the timers.
    //@{

    /// @brief Registers new timers in the @c TimerMgr.
    ///
    /// This method must not be called while the worker thread is running,
    /// as it modifies the internal data structure holding registered
    /// timers, which is also accessed from the worker thread via the
    /// callback. Inserting new element to this data structure and
    /// reading it at the same time would yield undefined behavior.
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
    /// @throw InvalidOperation if the worker thread is running.
    void registerTimer(const std::string& timer_name,
                       const asiolink::IntervalTimer::Callback& callback,
                       const long interval,
                       const asiolink::IntervalTimer::Mode& scheduling_mode);

    /// @brief Unregisters specified timer.
    ///
    /// This method cancels the timer if it is setup. It removes the external
    /// socket from the @c IfaceMgr and closes it. It finally removes the
    /// timer from the internal collection of timers.
    ///
    /// This method must not be called while the worker thread is running,
    /// as it modifies the internal data structure holding registered
    /// timers, which is also accessed from the worker thread via the
    /// callback. Removing element from this data structure and
    /// reading it at the same time would yield undefined behavior.
    ///
    /// @param timer_name Name of the timer to be unregistered.
    ///
    /// @throw BadValue if the specified timer hasn't been registered.
    void unregisterTimer(const std::string& timer_name);

    /// @brief Unregisters all timers.
    void unregisterTimers();

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

    /// @name Starting and stopping the worker thread.
    //@{

    /// @brief Starts worker thread
    ///
    /// This method has no effect if the thread has already been started.
    void startThread();

    /// @brief Stops worker thread.
    ///
    /// When the thread is being stopped, it is possible that some of the
    /// timers have elapsed and marked their respective watch sockets
    /// as "ready", but the sockets haven't been yet cleared in the
    /// main thread and the installed callbacks haven't been executed.
    /// It is possible to control whether those pending callbacks should
    /// be executed or not before the call to @c stopThread ends.
    /// If the thread is being stopped as a result of the DHCP server
    /// reconfiguration running pending callback may take significant
    /// amount of time, e.g. when operations on the lease database are
    /// involved. If this is a concern, the function parameter should
    /// be left at its default value. In this case, however, it is
    /// important to note that callbacks installed on ONE_SHOT timers
    /// often reschedule the timer. If such callback is not executed
    /// the timer will have to be setup by the application when the
    /// thread is started again.
    ///
    /// Setting the @c run_pending_callbacks to true will guarantee
    /// that all callbacks for which the timers have already elapsed
    /// (and marked their watch sockets as ready) will be executed
    /// prior to the return from @c stopThread method. However, this
    /// should be avoided if the longer execution time of the
    /// @c stopThread function is a concern.
    ///
    /// This method has no effect if the thread is not running.
    ///
    /// @param run_pending_callbacks Indicates if the pending callbacks
    /// should be executed (if true).
    void stopThread(const bool run_pending_callbacks = false);

    //@}

    /// @brief Returns a reference to IO service used by the @c TimerMgr.
    asiolink::IOService& getIOService() const;

private:

    /// @brief Private default constructor.
    ///
    /// The @c TimerMgr is a singleton class which instance must be created
    /// using the @c TimerMgr::instance method. Private constructor enforces
    /// construction via @c TimerMgr::instance.
    TimerMgr();

    /// @brief Pointer to @c TimerMgr implementation.
    TimerMgrImpl* impl_;

};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // TIMER_MGR_H
