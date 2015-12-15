// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/interval_timer.h>
#include <d2/d2_log.h>
#include <d2/io_service_signal.h>

namespace isc {
namespace d2 {

IOSignal::IOSignal (asiolink::IOService& io_service, int signum,
                    IOSignalHandler handler)
    : sequence_id_(nextSequenceId()), signum_(signum),
      timer_(new asiolink::IntervalTimer(io_service)) {
    // Valid handler is essential.
    if (!handler) {
        isc_throw(IOSignalError,
                  "IOSignal - handler cannot be null");
    }

    // Set up the timer as a one-shot which expires in 1 ms (intervals of 0
    // are invalid). This means that once control returns to IOService::run
    // the timer will have expired and its handler will be invoked.
    timer_->setup(TimerCallback(sequence_id_, handler), 1,
                  asiolink::IntervalTimer::ONE_SHOT);
}

IOSignal::~IOSignal() {
    if (timer_) {
        // In the unlikely event that the timer hasn't expired cancel it.
        timer_->cancel();
    }
}

IOSignal::
TimerCallback::TimerCallback(IOSignalId sequence_id, IOSignalHandler handler)
    : sequence_id_(sequence_id), handler_(handler) {
    if (!handler) {
        isc_throw(IOSignalError,
                  "IOSignal::TimerCallback - handler cannot be null");
    }
}

void
IOSignal::TimerCallback::operator()() {
    try {
        handler_(sequence_id_);
    } catch (const std::exception& ex) {
        // We log it and swallow it so we don't undermine IOService::run.
        LOG_ERROR(dctl_logger, DHCP_DDNS_SIGNAL_ERROR)
                  .arg(sequence_id_).arg(ex.what());
    }

    return;
}

IOSignalQueue::IOSignalQueue(asiolink::IOServicePtr& io_service)
    : io_service_(io_service), signals_() {
    if (!io_service_) {
        isc_throw(IOSignalError, "IOSignalQueue - io_serivce cannot be NULL");
    }
}

IOSignalQueue::~IOSignalQueue() {
    clear();
}

IOSignalId
IOSignalQueue::pushSignal(int signum, IOSignalHandler handler) {
    // Create the new signal.
    IOSignalPtr signal(new IOSignal(*io_service_, signum, handler));

    // Make sure the sequence_id isn't already in the queue.
    IOSignalId sequence_id = signal->getSequenceId();
    IOSignalMap::iterator it = signals_.find(sequence_id);
    if (it != signals_.end()) {
        // This really shouldn't happen unless we are in the weeds.
        isc_throw (IOSignalError, "pushSignal - "
                   "signal already exists for sequence_id: " << sequence_id);
    }

    //  Add the signal to the queue.
    signals_[sequence_id] = signal;
    return (sequence_id);
}

IOSignalPtr
IOSignalQueue::popSignal(IOSignalId sequence_id) {
    // Look for the signal in the queue.
    IOSignalMap::iterator it = signals_.find(sequence_id);
    if (it == signals_.end()) {
        // This really shouldn't happen unless we are in the weeds.
        isc_throw (IOSignalError, "popSignal - "
                   "signal not found for sequence_id: " << sequence_id);
    }

    // Save the signal so we can return it.
    IOSignalPtr signal = ((*it).second);

    // Delete it from the queue.
    signals_.erase(it);

    // Return the signal.
    return (signal);
}

void
IOSignalQueue::clear() {
    signals_.clear();
}

}; // end of isc::d2 namespace
}; // end of isc namespace
