// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/stopwatch.h>
#include <util/stopwatch_impl.h>

namespace isc {
namespace util {

using namespace boost::posix_time;

Stopwatch::Stopwatch(const bool autostart)
    : impl_(new StopwatchImpl()) {
    // If the autostart has been specified, invoke start.
    if (autostart) {
        start();
    }
}

Stopwatch::~Stopwatch() {
    delete impl_;
}

void
Stopwatch::start() {
    impl_->start();
}

void
Stopwatch::stop() {
    impl_->stop();
}

void
Stopwatch::reset() {
    impl_->reset();
}

boost::posix_time::time_duration
Stopwatch::getLastDuration() const {
    return (impl_->getLastDuration());
}

boost::posix_time::time_duration
Stopwatch::getTotalDuration() const {
    return (impl_->getTotalDuration());
}

long
Stopwatch::getLastMilliseconds() const {
    return (getLastDuration().total_milliseconds());
}

long
Stopwatch::getTotalMilliseconds() const {
    return (getTotalDuration().total_milliseconds());
}

long
Stopwatch::getLastMicroseconds() const {
    return (getLastDuration().total_microseconds());
}

long
Stopwatch::getTotalMicroseconds() const {
    return (getTotalDuration().total_microseconds());
}

std::string
Stopwatch::logFormatLastDuration() const {
    return (StopwatchImpl::logFormat(getLastDuration()));
}

std::string
Stopwatch::logFormatTotalDuration() const {
    return (StopwatchImpl::logFormat(getTotalDuration()));
}

} // end of isc::util
} // end of isc
