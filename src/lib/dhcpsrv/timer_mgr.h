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
#include <asiolink/io_service.h>
#include <util/watch_socket.h>
#include <boost/noncopyable.hpp>
#include <map>
#include <string>

namespace isc {
namespace dhcp {

class TimerMgr : public boost::noncopyable {
public:

    static TimerMgr& instance();

    void registerTimer(const std::string& timer_name,
                       const asiolink::IntervalTimer::Callback& callback,
                       const long interval,
                       const asiolink::IntervalTimer::Mode& scheduling_mode);

    void deregisterTimer(const std::string& timer_name);

    void setup(const std::string& timer_name);

    asiolink::IOService& getIOService() const {
        return (*io_service_);
    }

private:

    /// @brief Private default constructor.
    ///
    /// The @c TimerMgr is a singleton class which instance must be created
    /// using the @c TimerMgr::instance method. Private constructor enforces
    /// construction via @c TimerMgr::instance.
    TimerMgr();

    /// @brief Callback function to be executed for each interval timer when
    /// its scheduled interval elapses.
    ///
    /// @param timer_name Unique timer name to be passed to the callback.
    void localCallback(const std::string& timer_name) const;

    /// @brief Holds the pointer to the io service object.
    asiolink::IOServicePtr io_service_;

    /// @brief Structure holding information for a single timer.
    ///
    /// This structure holds the instance of the watch socket being used to
    /// signal that the timer is "ready". It also holds the instance of the
    /// interval timer.
    struct TimerInfo {
        /// @brief Instance of the watch socket.
        util::WatchSocket watch_socket_;

        /// @brief Instance of the interval timer.
        asiolink::IntervalTimerPtr interval_timer_;

        asiolink::IntervalTimer::Callback callback_;

        long interval_;

        asiolink::IntervalTimer::Mode scheduling_mode_;

        TimerInfo(const util::WatchSocket& watch_socket,
                  const asiolink::IntervalTimerPtr& interval_timer,
                  const asiolink::IntervalTimer::Callback& callback,
                  const long interval,
                  const asiolink::IntervalTimer::Mode& mode)
            : watch_socket_(watch_socket),
              interval_timer_(interval_timer),
              callback_(callback),
              interval_(interval),
              scheduling_mode_(mode) { };
    };

    typedef std::map<std::string, TimerInfo> TimerInfoMap;

    /// @brief Holds mapping of the timer name to the watch socket and timer
    /// instance.
    ///
    /// Each registered timer has a unique name which is used as a key to
    /// the map. The timer is associated with an instance of the @c WatchSocket
    /// which is marked ready when the interval for the particular elapses.
    std::map<std::string, TimerInfo> registered_timers_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // TIMER_MGR_H
