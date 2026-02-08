// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius_status.h>
#include <radius_tls.h>
#include <util/multi_threading_mgr.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace radius {

RadiusTls::RadiusTls() : RadiusService("tls") {
}

void
RadiusTls::setIdleTimer() {
    MultiThreadingLock lock(idle_timer_mutex_);
    cancelIdleTimer();
    if (idle_timer_interval_ <= 0) {
        return;
    }
    // Cope to one day.
    long secs = idle_timer_interval_;
    if (secs > 24*60*60) {
        secs = 24*60*60;
    }
    idle_timer_.reset(new IntervalTimer(RadiusImpl::instance().getIOContext()));
    idle_timer_->setup(RadiusTls::IdleTimerCallback,
                       secs * 1000, IntervalTimer::REPEATING);
}

void
RadiusTls::IdleTimerCallback() {
    AttributesPtr send_attrs;
    RadiusTlsStatusPtr handler(new RadiusTlsStatus(send_attrs, 0));
    handler->start();
}

} // end of namespace isc::radius
} // end of namespace isc
