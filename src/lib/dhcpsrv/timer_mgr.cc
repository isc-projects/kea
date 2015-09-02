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
#include <boost/bind.hpp>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::util;
using namespace isc::util::thread;

namespace isc {
namespace dhcp {

TimerMgr&
TimerMgr::instance() {
    static TimerMgr timer_mgr;
    return (timer_mgr);
}

TimerMgr::TimerMgr()
    : thread_(), registered_timers_() {
}

TimerMgr::~TimerMgr() {
    // Stop the thread, but do not unregister any timers. Unregistering
    // the timers could cause static deinitialization fiasco between the
    // TimerMgr and IfaceMgr. By now, the caller should have unregistered
    // the timers.
    stopThread();
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
    TimerInfo timer_info(getIOService(), callback, interval, scheduling_mode);

    // Register the WatchSocket in the IfaceMgr and register our own callback
    // to be executed when the data is received over this socket. The only time
    // this may fail is when the socket failed to open which would have caused
    // an exception in the previous call. So we should be safe here.
    IfaceMgr::instance().addExternalSocket(timer_info.watch_socket_->getSelectFd(),
                                           boost::bind(&TimerMgr::ifaceMgrCallback,
                                                       this, timer_name));

    // Actually register the timer.
    registered_timers_.insert(std::pair<std::string, TimerInfo>(timer_name, timer_info));
}

void
TimerMgr::unregisterTimer(const std::string& timer_name) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_UNREGISTER_TIMER)
        .arg(timer_name);

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

    TimerInfo& timer_info = timer_info_it->second;

    // Unregister the watch socket from the IfaceMgr.
    IfaceMgr::instance().deleteExternalSocket(timer_info.watch_socket_->getSelectFd());

    // Remove the timer.
    registered_timers_.erase(timer_info_it);
}

void
TimerMgr::unregisterTimers() {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_UNREGISTER_ALL_TIMERS);

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
TimerMgr::setup(const std::string& timer_name) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_START_TIMER)
        .arg(timer_name);

   // Check if the specified timer exists.
   TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
   if (timer_info_it == registered_timers_.end()) {
       isc_throw(BadValue, "unable to setup timer '" << timer_name << "': "
                 "no such timer registered");
   }

   // Schedule the execution of the timer using the parameters supplied
   // during the registration.
   const TimerInfo& timer_info = timer_info_it->second;
   timer_info.interval_timer_->setup(boost::bind(&TimerMgr::timerCallback, this, timer_name),
                                     timer_info.interval_,
                                     timer_info.scheduling_mode_);
}

void
TimerMgr::cancel(const std::string& timer_name) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_TIMERMGR_STOP_TIMER)
        .arg(timer_name);

    // Find the timer of our interest.
    TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it == registered_timers_.end()) {
        isc_throw(BadValue, "unable to cancel timer '" << timer_name << "': "
                  "no such timer registered");
    }
    // Cancel the timer.
    timer_info_it->second.interval_timer_->cancel();
    // Clear watch socket, if ready.
    timer_info_it->second.watch_socket_->clearReady();
}

void
TimerMgr::startThread() {
    // Do not start the thread if the thread is already there.
    if (!thread_) {
        // Only log it if we really start the thread.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_TIMERMGR_START_THREAD);

        // The thread will simply run IOService::run(), which is a blocking call
        // to keep running handlers for all timers according to how they have
        // been scheduled.
        thread_.reset(new Thread(boost::bind(&IOService::run, &getIOService())));
    }
}

void
TimerMgr::stopThread() {
    // If thread is not running, this is no-op.
    if (thread_) {
        // Only log it if we really have something to stop.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_TIMERMGR_STOP_THREAD);

        // Stop the IO Service. This will break the IOService::run executed in the
        // worker thread. The thread will now terminate.
        getIOService().post(boost::bind(&IOService::stop, &getIOService()));
        // When the worker thread may be waiting on the call to
        // WatchSocket::markReady until main thread clears the socket.
        // To unblock the thread we have to clear all sockets to make
        // sure that the thread doesn't remain blocked.
        clearReadySockets();
        // Wait for the thread to terminate.
        thread_->wait();
        // Set the thread pointer to NULL to indicate that the thread is not running.
        thread_.reset();
        // IO Service has to be reset so as we can call run() on it again if we
        // desire (using the startThread()).
        getIOService().get_io_service().reset();
    }
}
IOService&
TimerMgr::getIOService() const {
    // The IO service is now created internally by the TimerMgr and we don't allow
    // overriding it with anything as there are currently no use cases for it.
    // It is possible that someone may want to obtain this instance to use it
    // for something else too, so we return a reference to a static object.
    // If we decide to allow setting the IO service object we will have to
    // replace this static object with a shared pointer allocated in the
    // class constructor.
    static asiolink::IOService io_service;
    return (io_service);
}


void
TimerMgr::timerCallback(const std::string& timer_name) {
    // Run callback. Value of true says "mark socket ready".
    watchSocketCallback(timer_name, true);
}

void
TimerMgr::ifaceMgrCallback(const std::string& timer_name) {
    // Run callback. Value of false says "clear ready socket".
    watchSocketCallback(timer_name, false);
}

void
TimerMgr::watchSocketCallback(const std::string& timer_name, const bool mark_ready) {
    // Find the specified timer setup.
    TimerInfoMap::iterator timer_info_it = registered_timers_.find(timer_name);
    if (timer_info_it != registered_timers_.end()) {
        TimerInfo& timer_info = timer_info_it->second;
        // This is 'true' when we're executing a callback for the elapsed timer.
        // It is supposed to mark watch socket ready - write data to a socket to
        // interrupt the execution of the select() function. This is executed
        // from the worker thrad and will likely block the thread until the socket
        // is cleared.
        if (mark_ready) {
            timer_info.watch_socket_->markReady();
        } else {

            // We're executing a callback function from the Interface Manager.
            // This callback function is executed when the call to select() is
            // interrupted as a result of receiving some data over the watch
            // socket. We have to clear the socket which has been marked as
            // ready. Then execute the callback function supplied by the
            // TimerMgr user to perform custom actions on the expiration of
            // the given timer.
            timer_info.watch_socket_->clearReady();

            // Running user-defined operation for the timer. Logging it
            // on the slightly lower debug level as there may be many
            // such traces.
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                      DHCPSRV_TIMERMGR_RUN_TIMER_OPERATION)
                .arg(timer_name);
            timer_info.user_callback_();
        }
    }
}

void
TimerMgr::clearReadySockets() {
    for (TimerInfoMap::iterator timer_info_it = registered_timers_.begin();
         timer_info_it != registered_timers_.end(); ++timer_info_it) {
        timer_info_it->second.watch_socket_->clearReady();
   }
}

} // end of namespace isc::dhcp
} // end of namespace isc
