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

#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

TimerMgr&
TimerMgr::instance() {
    static TimerMgr timer_mgr;
    return (timer_mgr);
}

TimerMgr::TimerMgr()
    : io_service_(new IOService()) {
}

void
TimerMgr::registerTimer(const std::string& timer_name,
                        const IntervalTimer::Callback& callback,
                        const long interval,
                        const IntervalTimer::Mode& scheduling_mode) {

    if (timer_name.empty()) {
        isc_throw(BadValue, "registered timer name must not be empty");
    }

    if (registered_timers_.find(timer_name) != registered_timers_.end()) {
        isc_throw(BadValue, "trying to register duplicate timer '"
                  << timer_name << "'");
    }

    WatchSocket watch_socket;
    IntervalTimerPtr interval_timer(new IntervalTimer(getIOService()));
    TimerInfo timer_info(watch_socket, interval_timer, callback, interval,
                         scheduling_mode);
    registered_timers_.insert(std::pair<std::string, TimerInfo>(timer_name, timer_info));
}

void
TimerMgr::deregisterTimer(const std::string& timer_name) {
}

void
TimerMgr::setup(const std::string& timer_name) {
   TimerInfoMap::const_iterator timer_info_it = registered_timers_.find(timer_name);
   if (timer_info_it == registered_timers_.end()) {
       isc_throw(BadValue, "unable to setup timer '" << timer_name << "': "
                 "no such timer registered");
   }

   const TimerInfo& timer_info = timer_info_it->second;
   timer_info.interval_timer_->setup(timer_info.callback_, timer_info.interval_,
                                     timer_info.scheduling_mode_);
}

void
TimerMgr::localCallback(const std::string& timer_name) const {
}



} // end of namespace isc::dhcp
} // end of namespace isc
