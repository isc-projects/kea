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

#include <util/stopwatch_impl.h>
#include <iomanip>
#include <sstream>

namespace isc {
namespace util {

using namespace boost::posix_time;

StopwatchImpl::StopwatchImpl()
    : started_(false),
      last_start_(getCurrentTime()),
      last_stop_(last_start_),
      cumulative_time_(microseconds(0)) {
}

StopwatchImpl::~StopwatchImpl() {
}

void
StopwatchImpl::start() {
    // If stopwatch is "stopped", start it.
    if (!started_) {
        last_start_ = getCurrentTime();
        started_ = true;
    }
}

void
StopwatchImpl::stop() {
    // Is stopwatch is "started", stop it.
    if (started_) {
        last_stop_ = getCurrentTime();
        // Update the total time with the last measured duration.
        cumulative_time_ += last_stop_ - last_start_;
        started_ = false;
    }
}

void
StopwatchImpl::reset() {
    // Set last start and stop values to the current time. This is the
    // same as in the constructor. As a result the last duration will
    // be 0.
    last_start_ = getCurrentTime();
    last_stop_ = last_start_;
    // Set the total duration to 0.
    cumulative_time_ = microseconds(0);
    started_ = false;
}

time_duration
StopwatchImpl::getLastDuration() const {
    // If the stopwatch is started, the time measured is between the
    // start time and the current time. Otherwise, it is between the
    // start time and last stop.
    ptime end_time = started_ ? getCurrentTime() : last_stop_;
    return (end_time - last_start_);
}

time_duration
StopwatchImpl::getTotalDuration() const {
    // Get the total time recorded so far.
    time_duration total_duration = cumulative_time_;
    if (started_) {
        // If the stopwatch is started, add the duration between the
        // start time and current time.
        total_duration += (getCurrentTime() - last_start_);
    }
    return (total_duration);
}

std::string
StopwatchImpl::logFormat(const boost::posix_time::time_duration& duration) {
    std::ostringstream s;
    s << duration.total_milliseconds() << ".";
    s << std::setfill('0') << std::setw(3) << (duration.total_microseconds() % 1000)
      << " ms";
    return (s.str());
}

ptime
StopwatchImpl::getCurrentTime() const {
    return (microsec_clock::universal_time());
}


} // end of isc::util
} // end of isc
