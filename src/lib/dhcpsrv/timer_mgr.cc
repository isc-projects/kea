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

#include <asio.hpp>
#include <asiolink/io_service.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>
#include <util/threads/sync.h>
#include <util/threads/thread.h>
#include <util/watch_socket.h>
#include <boost/bind.hpp>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::util;
using namespace isc::util::thread;

namespace {

/// @brief Simple RAII object setting value to true while in scope.
///
/// This class is useful to temporarly set the value to true and
/// automatically reset it to false when the object is destroyed
/// as a result of return or exception.
class ScopedTrue {
public:

    /// @brief Constructor.
    ///
    /// Sets the boolean value to true.
    ///
    /// @param value reference to the value to be set to true.
    ScopedTrue(bool& value, Mutex& mutex)
        : value_(value), mutex_(mutex) {
        Mutex::Locker lock(mutex_);
        value_ = true;
    }

    /// @brief Destructor.
    ///
    /// Sets the value to false.
    ~ScopedTrue() {
        Mutex::Locker lock(mutex_);
        value_ = false;
    }

private:

    /// @brief Reference to the controlled value.
    bool& value_;

    /// @brief Mutex to be used to lock while performing write
    /// operations.
    Mutex& mutex_;
};

/// @brief Structure holding information for a single timer.
///
/// This structure holds the instance of the watch socket being used to
/// signal that the timer is "ready". It also holds the instance of the
/// interval timer and other parameters pertaining to it.
struct TimerInfo {
    /// @brief Instance of the watch socket.
    util::WatchSocket watch_socket_;

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
        : watch_socket_(),
          interval_timer_(io_service),
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

    /// @brief Returns a reference to IO service used by the @c TimerMgr.
    asiolink::IOService& getIOService() const {
        return (*io_service_);
    }

    /// @brief Registers new timers in the @c TimerMgr.
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
    /// @param timer_name Name of the timer to be unregistered.
    ///
    /// @throw BadValue if the specified timer hasn't been registered.
    void unregisterTimer(const std::string& timer_name);

    /// @brief Unregisters all timers.
    ///
    /// This method must be explicitly called prior to termination of the
    /// process.
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

    /// @brief Checks if the thread is running.
    ///
    /// @return true if the thread is running.
    bool threadRunning() const;

    /// @brief Starts thread.
    void createThread();

    /// @brief Stops thread gracefully.
    ///
    /// This methods unblocks worker thread if it is blocked waiting for
    /// any handlers and stops it. Outstanding handlers are later executed
    /// in the main thread and all watch sockets are cleared.
    ///
    /// @param run_pending_callbacks Indicates if the pending callbacks
    /// should be executed (if true).
    void controlledStopThread(const bool run_pending_callbacks);

private:

    /// @name Internal callbacks.
    //@{
    ///
    /// @brief Callback function to be executed for each interval timer when
    /// its scheduled interval elapses.
    ///
    /// This method marks the @c util::Watch socket associated with the
    /// timer as ready (writes data to a pipe). This method will block until
    /// @c TimerMgr::ifaceMgrCallback is executed from the main thread by the
    /// @c IfaceMgr.
    ///
    /// @param timer_name Unique timer name to be passed to the callback.
    void timerCallback(const std::string& timer_name);

    /// @brief Callback function installed on the @c IfaceMgr and associated
    /// with the particular timer.
    ///
    /// This callback function is executed by the @c IfaceMgr when the data
    /// over the specific @c util::WatchSocket is received. This method clears
    /// the socket (reads the data from the pipe) and executes the callback
    /// supplied when the timer was registered.
    ///
    /// @param timer_name Unique timer name.
    void ifaceMgrCallback(const std::string& timer_name);

    //@}

    /// @name Methods to handle ready sockets.
    //@{
    ///
    /// @brief Clear ready sockets and optionally run callbacks.
    ///
    /// This method is called by the @c TimerMgr::stopThread method
    /// to clear watch sockets which may be marked as ready. It will
    /// also optionally run callbacks installed for the timers which
    /// marked sockets as ready.
    ///
    /// @param run_pending_callbacks Indicates if the callbacks should
    /// be executed for the sockets being cleared (if true).
    void clearReadySockets(const bool run_pending_callbacks);

    /// @brief Clears a socket and optionally runs a callback.
    ///
    /// This method clears the ready socket pointed to by the specified
    /// iterator. If the @c run_callback is set, the callback will
    /// also be executed.
    ///
    /// @param timer_info_iterator Iterator pointing to the timer
    /// configuration structure.
    /// @param run_callback Boolean value indicating if the callback
    /// should be executed for the socket being cleared (if true).
    ///
    /// @tparam Iterator Iterator pointing to the timer configuration
    /// structure.
    template<typename Iterator>
    void handleReadySocket(Iterator timer_info_iterator, const bool run_callback);

    //@}

    /// @brief Blocking wait for the socket to be cleared.
    void waitForSocketClearing(WatchSocket& watch_socket);

    /// @brief Signals that a watch socket has been cleared.
    void signalSocketClearing();

    /// @brief Pointer to the @c IfaceMgr.
    IfaceMgrPtr iface_mgr_;

    /// @brief Pointer to the io service.
    asiolink::IOServicePtr io_service_;

    /// @brief Pointer to the worker thread.
    ///
    /// This is initially set to NULL until the thread is started using the
    /// @c TimerMgr::startThread. The @c TimerMgr::stopThread sets it back
    /// to NULL.
    boost::shared_ptr<util::thread::Thread> thread_;

    /// @brief Mutex used to synchronize main thread and the worker thread.
    util::thread::Mutex mutex_;

    /// @brief Conditional variable used to synchronize main thread and
    /// worker thread.
    util::thread::CondVar cond_var_;

    /// @brief Boolean value indicating if the thread is being stopped.
    bool stopping_;

    /// @brief Holds mapping of the timer name to the watch socket, timer
    /// instance and other parameters pertaining to the timer.
    ///
    /// Each registered timer has a unique name which is used as a key to
    /// the map. The timer is associated with an instance of the @c WatchSocket
    /// which is marked ready when the interval for the particular elapses.
    TimerInfoMap registered_timers_;
};

TimerMgrImpl::TimerMgrImpl() :
    iface_mgr_(IfaceMgr::instancePtr()), io_service_(new IOService()), thread_(),
    mutex_(), cond_var_(), stopping_(false), registered_timers_() {
}

void
TimerMgrImpl::registerTimer(const std::string& timer_name,
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

    // Must not register new timer when the worker thread is running. Note
    // that worker thread is using IO service and trying to register a new
    // timer while IO service is being used would result in hang.
    if (thread_) {
        isc_throw(InvalidOperation, "unable to register new timer when the"
                  " timer manager's worker thread is running");
    }

    // Create a structure holding the configuration for the timer. It will
    // create the instance if the IntervalTimer and WatchSocket. It will
    // also hold the callback, interval and scheduling mode parameters.
    // This may throw a WatchSocketError if the socket creation fails.
    TimerInfoPtr timer_info(new TimerInfo(getIOService(), callback,
                                          interval, scheduling_mode));

    // Register the WatchSocket in the IfaceMgr and register our own callback
    // to be executed when the data is received over this socket. The only time
    // this may fail is when the socket failed to open which would have caused
    // an exception in the previous call. So we should be safe here.
    iface_mgr_->addExternalSocket(timer_info->watch_socket_.getSelectFd(),
                                  boost::bind(&TimerMgrImpl::ifaceMgrCallback,
                                              this, timer_name));

    // Actually register the timer.
    registered_timers_.insert(std::pair<std::string, TimerInfoPtr>(timer_name,
                                                                   timer_info));
}

void
TimerMgrImpl::unregisterTimer(const std::string& timer_name) {

    if (thread_) {
        isc_throw(InvalidOperation, "unable to unregister timer "
                  << timer_name << " while worker thread is running");
    }

    // Find the timer with specified name.
    TimerInfoMap::iterator timer_info_it = registered_timers_.find(timer_name);

    // Check if the timer has been registered.
    if (timer_info_it == registered_timers_.end()) {
        isc_throw(BadValue, "unable to unregister non existing timer '"
                  << timer_name << "'");
    }

    // Cancel any pending asynchronous operation and stop the timer.
    cancel(timer_name);

    const TimerInfoPtr& timer_info = timer_info_it->second;

    // Unregister the watch socket from the IfaceMgr.
    iface_mgr_->deleteExternalSocket(timer_info->watch_socket_.getSelectFd());

    // Remove the timer.
    registered_timers_.erase(timer_info_it);
}

void
TimerMgrImpl::unregisterTimers() {
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
        unregisterTimer(timer_info_it->first);
    }
}

void
TimerMgrImpl::setup(const std::string& timer_name) {

   // Check if the specified timer exists.
   TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
   if (timer_info_it == registered_timers_.end()) {
       isc_throw(BadValue, "unable to setup timer '" << timer_name << "': "
                 "no such timer registered");
   }

   // Schedule the execution of the timer using the parameters supplied
   // during the registration.
   const TimerInfoPtr& timer_info = timer_info_it->second;
   IntervalTimer::Callback cb = boost::bind(&TimerMgrImpl::timerCallback, this,
                                            timer_name);
   timer_info->interval_timer_.setup(cb, timer_info->interval_,
                                     timer_info->scheduling_mode_);
}

void
TimerMgrImpl::cancel(const std::string& timer_name) {

    // Find the timer of our interest.
    TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it == registered_timers_.end()) {
        isc_throw(BadValue, "unable to cancel timer '" << timer_name << "': "
                  "no such timer registered");
    }
    // Cancel the timer.
    timer_info_it->second->interval_timer_.cancel();
    // Clear watch socket, if ready.
    timer_info_it->second->watch_socket_.clearReady();
}


bool
TimerMgrImpl::threadRunning() const {
    return (static_cast<bool>(thread_));
}

void
TimerMgrImpl::createThread() {
    thread_.reset(new Thread(boost::bind(&IOService::run, &getIOService())));
}

void
TimerMgrImpl::controlledStopThread(const bool run_pending_callbacks) {
    // Set the stopping flag to true while we're stopping. This will be
    // automatically reset to false when the function exits or exception
    // is thrown.
    ScopedTrue scoped_true(stopping_, mutex_);

    // Stop the IO Service. This will break the IOService::run executed in the
    // worker thread. The thread will now terminate.
    getIOService().stop();

    // Some of the watch sockets may be already marked as ready and
    // have some pending callbacks to be executed. If the caller
    // wants us to run the callbacks we clear the sockets and run
    // them. If pending callbacks shouldn't be executed, this will
    // only clear the sockets (which should be substantially faster).
    clearReadySockets(run_pending_callbacks);
    // Wait for the thread to terminate.
    thread_->wait();
    // Set the thread pointer to NULL to indicate that the thread is not running.
    thread_.reset();
    // IO Service has to be reset so as we can call run() on it again if we
    // desire (using the startThread()).
    getIOService().get_io_service().reset();
}

void
TimerMgrImpl::timerCallback(const std::string& timer_name) {
    // Find the specified timer setup.
    TimerInfoMap::iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it != registered_timers_.end()) {
        // We will mark watch socket ready - write data to a socket to
        // interrupt the execution of the select() function. This is
        // executed from the worker thread.
        const TimerInfoPtr& timer_info = timer_info_it->second;

        // This function is called from the worker thread and we don't want
        // the worker thread to get exceptions out of here. It is unlikely
        // that markReady() would cause any problems but theoretically
        // possible. Hence, we rather log an error and leave.
        try {
            timer_info->watch_socket_.markReady();

        } catch (const std::exception& ex) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_TIMERMGR_SOCKET_MARK_FAILED)
                .arg(timer_name)
                .arg(ex.what());

            // Do not wait for clearing the socket because we were unable
            // to mark it ready anyway.
            return;
        }

        // Blocking wait for the socket to be cleared on the other
        // end. This may be interrupted both if the socket is cleared
        // or if the stopThread() has been called on the TimerMgr.
        waitForSocketClearing(timer_info->watch_socket_);
    }
}

void
TimerMgrImpl::ifaceMgrCallback(const std::string& timer_name) {
    // Find the specified timer setup.
    TimerInfoMap::iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it != registered_timers_.end()) {
        // We're executing a callback function from the Interface Manager.
        // This callback function is executed when the call to select() is
        // interrupted as a result of receiving some data over the watch
        // socket. We have to clear the socket which has been marked as
        // ready. Then execute the callback function supplied by the
        // TimerMgr user to perform custom actions on the expiration of
        // the given timer.
        handleReadySocket(timer_info_it, true);
    }
}

void
TimerMgrImpl::clearReadySockets(const bool run_pending_callbacks) {
    for (TimerInfoMap::iterator timer_info_it = registered_timers_.begin();
         timer_info_it != registered_timers_.end(); ++timer_info_it) {
        handleReadySocket(timer_info_it, run_pending_callbacks);
   }
}

template<typename Iterator>
void
TimerMgrImpl::handleReadySocket(Iterator timer_info_iterator,
                            const bool run_callback) {
    if (run_callback) {
        // Running user-defined operation for the timer. Logging it
        // on the slightly lower debug level as there may be many
        // such traces.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_TIMERMGR_RUN_TIMER_OPERATION)
            .arg(timer_info_iterator->first);

        std::string error_string;
        try {
            timer_info_iterator->second->user_callback_();

        } catch (const std::exception& ex){
            error_string = ex.what();

        } catch (...) {
            error_string = "unknown reason";
        }

        // Exception was thrown. Log an error.
        if (!error_string.empty()) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_TIMERMGR_CALLBACK_FAILED)
                .arg(timer_info_iterator->first)
                .arg(error_string);
        }
    }

    try {
        // This shouldn't really fail, but if it does we want to log an
        // error and make sure that the thread is not stuck waiting for
        // the socket to clear.
        timer_info_iterator->second->watch_socket_.clearReady();

    } catch (const std::exception& ex) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_TIMERMGR_SOCKET_CLEAR_FAILED)
            .arg(timer_info_iterator->first)
            .arg(ex.what());
    }

    // Whether it succeeded or not, clear the socket to make sure that
    // the worker thread is not stuck waiting for the main thread.
    signalSocketClearing();
}

void
TimerMgrImpl::waitForSocketClearing(WatchSocket& watch_socket) {
    // Waiting for the specific socket to be cleared.
    while (watch_socket.isReady()) {
        Mutex::Locker lock(mutex_);
        // If stopThread has been called there is no sense to further
        // wait for the socket clearing. Leave from here to unblock the
        // worker thread.
        if (stopping_) {
            break;
        }
        cond_var_.wait(mutex_);
    }
}

void
TimerMgrImpl::signalSocketClearing() {
    cond_var_.signal();
}

TimerMgr&
TimerMgr::instance() {
    static TimerMgr timer_mgr;
    return (timer_mgr);
}

TimerMgr::TimerMgr()
    : impl_(new TimerMgrImpl()) {
}

TimerMgr::~TimerMgr() {
    stopThread();
    unregisterTimers();
    delete impl_;
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
TimerMgr::startThread() {
    // Do not start the thread if the thread is already there.
    if (!impl_->threadRunning()) {
        // Only log it if we really start the thread.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_TIMERMGR_START_THREAD);

        impl_->createThread();
    }
}

void
TimerMgr::stopThread(const bool run_pending_callbacks) {
    // If thread is not running, this is no-op.
    if (impl_->threadRunning()) {
        // Only log it if we really have something to stop.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_TIMERMGR_STOP_THREAD);

        impl_->controlledStopThread(run_pending_callbacks);
    }
}
IOService&
TimerMgr::getIOService() const {
    return (impl_->getIOService());
}


} // end of namespace isc::dhcp
} // end of namespace isc
