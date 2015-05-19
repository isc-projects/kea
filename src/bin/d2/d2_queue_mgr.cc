// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <d2/d2_log.h>
#include <d2/d2_queue_mgr.h>
#include <dhcp_ddns/ncr_udp.h>

namespace isc {
namespace d2 {

// Makes constant visible to Google test macros.
const size_t D2QueueMgr::MAX_QUEUE_DEFAULT;

D2QueueMgr::D2QueueMgr(asiolink::IOServicePtr& io_service, const size_t max_queue_size)
    : io_service_(io_service), max_queue_size_(max_queue_size),
      mgr_state_(NOT_INITTED), target_stop_state_(NOT_INITTED) {
    if (!io_service_) {
        isc_throw(D2QueueMgrError, "IOServicePtr cannot be null");
    }

    // Use setter to do validation.
    setMaxQueueSize(max_queue_size);
}

D2QueueMgr::~D2QueueMgr() {
}

void
D2QueueMgr::operator()(const dhcp_ddns::NameChangeListener::Result result,
                       dhcp_ddns::NameChangeRequestPtr& ncr) {
    try {
        // Note that error conditions must be handled here without throwing
        // exceptions. Remember this is the application level "link" in the
        // callback chain.  Throwing an exception here will "break" the
        // io_service "run" we are operating under.  With that in mind,
        // if we hit a problem, we will stop the listener transition to
        // the appropriate stopped state.  Upper layer(s) must monitor our
        // state as well as our queue size.
        switch (result) {
        case dhcp_ddns::NameChangeListener::SUCCESS:
            // Receive was successful, attempt to queue the request.
            if (getQueueSize() < getMaxQueueSize()) {
                // There's room on the queue, add to the end
                enqueue(ncr);

                // Log that we got the request
                LOG_DEBUG(dhcp_to_d2_logger, DBGLVL_TRACE_DETAIL_DATA,
                          DHCP_DDNS_QUEUE_MGR_QUEUE_RECEIVE)
                          .arg(ncr->getRequestId());
                return;
            }

            // Queue is full, stop the listener.
            // Note that we can move straight to a STOPPED state as there
            // is no receive in progress.
            LOG_ERROR(dhcp_to_d2_logger, DHCP_DDNS_QUEUE_MGR_QUEUE_FULL)
                      .arg(max_queue_size_);
            stopListening(STOPPED_QUEUE_FULL);
            break;

        case dhcp_ddns::NameChangeListener::STOPPED:
            if (mgr_state_ == STOPPING) {
                // This is confirmation that the listener has stopped and its
                // callback will not be called again, unless its restarted.
                updateStopState();
            } else {
                // We should not get a receive complete status of stopped
                // unless we canceled the read as part of stopping. Therefore
                // this is unexpected so we will treat it as a receive error.
                // This is most likely an unforeseen programmatic issue.
                LOG_ERROR(dhcp_to_d2_logger, DHCP_DDNS_QUEUE_MGR_UNEXPECTED_STOP)
                          .arg(mgr_state_);
                stopListening(STOPPED_RECV_ERROR);
            }

            break;

        default:
            // Receive failed, stop the listener.
            // Note that we can move straight to a STOPPED state as there
            // is no receive in progress.
            LOG_ERROR(dhcp_to_d2_logger, DHCP_DDNS_QUEUE_MGR_RECV_ERROR);
            stopListening(STOPPED_RECV_ERROR);
            break;
        }
    } catch (const std::exception& ex) {
        // On the outside chance a throw occurs, let's log it and swallow it.
        LOG_ERROR(dhcp_to_d2_logger, DHCP_DDNS_QUEUE_MGR_UNEXPECTED_HANDLER_ERROR)
                  .arg(ex.what());
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
        listener_->startListening(*io_service_);
        mgr_state_ = RUNNING;
    } catch (const isc::Exception& ex) {
        isc_throw(D2QueueMgrError, "D2QueueMgr listener start failed: "
                  << ex.what());
    }

    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DHCP_DDNS_QUEUE_MGR_STARTED);
}

void
D2QueueMgr::stopListening(const State target_stop_state) {
    if (listener_) {
        // Enforce only valid "stop" states.
        // This is purely a programmatic error and should never happen.
        if (target_stop_state != STOPPED &&
            target_stop_state != STOPPED_QUEUE_FULL &&
            target_stop_state != STOPPED_RECV_ERROR) {
            isc_throw(D2QueueMgrError,
                      "D2QueueMgr invalid value for stop state: "
                      << target_stop_state);
        }

        // Remember the state we want to acheive.
        target_stop_state_ = target_stop_state;

        // Instruct the listener to stop.  If the listener reports that  it
        // has IO pending, then we transition to STOPPING to wait for the
        // cancellation event.  Otherwise, we can move directly to the targeted
        // state.
        listener_->stopListening();
        if (listener_->isIoPending()) {
            mgr_state_ = STOPPING;
        } else {
            updateStopState();
        }
    }
}

void
D2QueueMgr::updateStopState() {
    mgr_state_ = target_stop_state_;
    LOG_DEBUG(dctl_logger, DBGLVL_TRACE_BASIC, DHCP_DDNS_QUEUE_MGR_STOPPED);
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
