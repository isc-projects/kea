// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <d2/d2_log.h>
#include <d2/d2_queue_mgr.h>
#include <dhcp_ddns/ncr_udp.h>

namespace isc {
namespace d2 {

// Makes constant visible to Google test macros.
const size_t D2QueueMgr::MAX_QUEUE_DEFAULT;

D2QueueMgr::D2QueueMgr(isc::asiolink::IOService& io_service,
                       const size_t max_queue_size)
    : io_service_(io_service), max_queue_size_(max_queue_size),
      mgr_state_(NOT_INITTED) {
    // Use setter to do validation.
    setMaxQueueSize(max_queue_size);
}

D2QueueMgr::~D2QueueMgr() {
    // clean up
    try {
        stopListening();
    } catch (...) {
        // This catch is strictly for safety's sake, in case a future
        // implementation isn't tidy or careful. 
    }
}

void
D2QueueMgr::operator()(const dhcp_ddns::NameChangeListener::Result result,
                       dhcp_ddns::NameChangeRequestPtr& ncr) {
    // Note that error conditions must be handled here without throwing
    // exceptions. Remember this is the application level "link" in the
    // callback chain.  Throwing an exception here will "break" the
    // io_service "run" we are operating under.  With that in mind,
    // if we hit a problem, we will stop the listener transition to
    // the appropriate stopped state.  Upper layer(s) must monitor our
    // state as well as our queue size.

    // If the receive was successful, attempt to queue the request.
    if (result == dhcp_ddns::NameChangeListener::SUCCESS) {
        if (getQueueSize() < getMaxQueueSize()) {
            // There's room on the queue, add to the end
            enqueue(ncr);
            return;
        }

        // Queue is full, stop the listener.
        stopListening(STOPPED_QUEUE_FULL);
        LOG_ERROR(dctl_logger, DHCP_DDNS_QUEUE_MGR_QUEUE_FULL)
                  .arg(max_queue_size_);
    } else {
        // Receive failed, stop the listener.
        stopListening(STOPPED_RECV_ERROR);
        LOG_ERROR(dctl_logger, DHCP_DDNS_QUEUE_MGR_RECV_ERROR);
    }
}

void
D2QueueMgr::initUDPListener(const isc::asiolink::IOAddress& ip_address,
                            const uint32_t port,
                            const dhcp_ddns::NameChangeFormat format,
                            const bool reuse_address) {

    if (listener_) {
        isc_throw(D2QueueMgrError,
                  "D2QueueMgr listener is already initialized");
    }

    // Instantiate a UDP listener and set state to INITTED.
    // Note UDP listener constructor does not throw.
    listener_.reset(new dhcp_ddns::
                    NameChangeUDPListener(ip_address, port, format, *this,
                                          reuse_address));
    mgr_state_ = INITTED;
}

void
D2QueueMgr::startListening() {
    // We can't listen if we haven't initialized the listener yet.
    if (!listener_) {
        isc_throw(D2QueueMgrError, "D2QueueMgr "
                  "listener is not initialized, cannot start listening");
    }

    // If we are already listening, we do not want to "reopen" the listener
    // and really we shouldn't be trying.
    if (mgr_state_ == RUNNING) {
        isc_throw(D2QueueMgrError, "D2QueueMgr "
                  "cannot call startListening from the RUNNING state");
    }

    // Instruct the listener to start listening and set state accordingly.
    try {
        listener_->startListening(io_service_);
        mgr_state_ = RUNNING;
    } catch (const isc::Exception& ex) {
        isc_throw(D2QueueMgrError, "D2QueueMgr listener start failed: "
                  << ex.what());
    }
}

void
D2QueueMgr::stopListening(const State stop_state) {
    // Note, stopListening is guaranteed not to throw.
    if (listener_) {
        listener_->stopListening();
    }

    // Enforce only valid "stop" states.
    if (stop_state != STOPPED && stop_state != STOPPED_QUEUE_FULL &&
        stop_state != STOPPED_RECV_ERROR) {
        // This is purely a programmatic error and should never happen.
        isc_throw(D2QueueMgrError, "D2QueueMgr invalid value for stop state: "
                  << stop_state);
    }

    mgr_state_ = stop_state;
}

void
D2QueueMgr::removeListener() {
    // Force our managing layer(s) to stop us properly first.
    if (mgr_state_ == RUNNING) {
        isc_throw(D2QueueMgrError,
                  "D2QueueMgr cannot delete listener while state is RUNNING");
    }

    listener_.reset();
    mgr_state_ = NOT_INITTED;
}

const dhcp_ddns::NameChangeRequestPtr&
D2QueueMgr::peek() const {
    if (getQueueSize() ==  0) {
        isc_throw(D2QueueMgrQueueEmpty,
                  "D2QueueMgr peek attempted on an empty queue");
    }

    return (ncr_queue_.front());
}

const dhcp_ddns::NameChangeRequestPtr&
D2QueueMgr::peekAt(const size_t index) const {
    if (index >= getQueueSize()) {
        isc_throw(D2QueueMgrInvalidIndex,
                  "D2QueueMgr peek beyond end of queue attempted"
                  << " index: " << index << " queue size: " << getQueueSize());
    }

    return (ncr_queue_.at(index));
}

void
D2QueueMgr::dequeueAt(const size_t index) {
    if (index >= getQueueSize()) {
        isc_throw(D2QueueMgrInvalidIndex,
                  "D2QueueMgr dequeue beyond end of queue attempted"
                  << " index: " << index << " queue size: " << getQueueSize());
    }

    RequestQueue::iterator pos = ncr_queue_.begin() + index;
    ncr_queue_.erase(pos);
}


void
D2QueueMgr::dequeue() {
    if (getQueueSize() ==  0) {
        isc_throw(D2QueueMgrQueueEmpty,
                  "D2QueueMgr dequeue attempted on an empty queue");
    }

    ncr_queue_.pop_front();
}

void
D2QueueMgr::enqueue(dhcp_ddns::NameChangeRequestPtr& ncr) {
    ncr_queue_.push_back(ncr);
}

void
D2QueueMgr::clearQueue() {
    ncr_queue_.clear();
}

void
D2QueueMgr::setMaxQueueSize(const size_t new_queue_max) {
    if (new_queue_max < 1) {
        isc_throw(D2QueueMgrError,
                  "D2QueueMgr maximum queue size must be greater than zero");
    }

    if (new_queue_max < getQueueSize()) {
        isc_throw(D2QueueMgrError, "D2QueueMgr maximum queue size value cannot"
                  " be less than the current queue size :" << getQueueSize());
    }

    max_queue_size_ = new_queue_max;
}

} // namespace isc::d2
} // namespace isc
