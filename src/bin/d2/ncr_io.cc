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
#include <d2/ncr_io.h>

namespace isc {
namespace d2 {

//************************** NameChangeListener ***************************

NameChangeListener::NameChangeListener(RequestReceiveHandler&
                                       recv_handler)
    : listening_(false), recv_handler_(recv_handler) {
};

void
NameChangeListener::startListening(isc::asiolink::IOService& io_service) {
    if (amListening()) {
        // This amounts to a programmatic error.
        isc_throw(NcrListenerError, "NameChangeListener is already listening");
    }

    // Call implementation dependent open.
    try {
        open(io_service);
    } catch (const isc::Exception& ex) {
        stopListening();
        isc_throw(NcrListenerOpenError, "Open failed:" << ex.what());
    }

    // Set our status to listening.
    setListening(true);

    // Start the first asynchronous receive.
    try {
        doReceive();
    } catch (const isc::Exception& ex) {
        stopListening();
        isc_throw(NcrListenerReceiveError, "doReceive failed:" << ex.what());
    }
}

void
NameChangeListener::stopListening() {
    try {
        // Call implementation dependent close.
        close();
    } catch (const isc::Exception &ex) {
        // Swallow exceptions. If we have some sort of error we'll log
        // it but we won't propagate the throw.
        LOG_ERROR(dctl_logger, DHCP_DDNS_NCR_LISTEN_CLOSE_ERROR).arg(ex.what());
    }

    // Set it false, no matter what.  This allows us to at least try to
    // re-open via startListening().
    setListening(false);
}

void
NameChangeListener::invokeRecvHandler(const Result result,
                                      NameChangeRequestPtr& ncr) {
    // Call the registered application layer handler.
    recv_handler_(result, ncr);

    // Start the next IO layer asynchronous receive.
    // In the event the handler above intervened and decided to stop listening
    // we need to check that first.
    if (amListening()) {
        try {
            doReceive();
        } catch (const isc::Exception& ex) {
            // It is possible though unlikely, for doReceive to fail without
            // scheduling the read. While, unlikely, it does mean the callback
            // will not get called with a failure. A throw here would surface
            // at the IOService::run (or run variant) invocation.  So we will
            // close the window by invoking the application handler with
            // a failed result, and let the application layer sort it out.
            LOG_ERROR(dctl_logger, DHCP_DDNS_NCR_RECV_NEXT).arg(ex.what());
            NameChangeRequestPtr empty;
            recv_handler_(ERROR, empty);
        }
    }
}

//************************* NameChangeSender ******************************

NameChangeSender::NameChangeSender(RequestSendHandler& send_handler,
                                   size_t send_queue_max)
    : sending_(false), send_handler_(send_handler),
      send_queue_max_(send_queue_max) {

    // Queue size must be big enough to hold at least 1 entry.
    if (send_queue_max == 0) {
        isc_throw(NcrSenderError, "NameChangeSender constructor"
                  " queue size must be greater than zero");
    }
}

void
NameChangeSender::startSending(isc::asiolink::IOService& io_service) {
    if (amSending()) {
        // This amounts to a programmatic error.
        isc_throw(NcrSenderError, "NameChangeSender is already sending");
    }

    // Clear send marker.
    ncr_to_send_.reset();

    // Call implementation dependent open.
    try {
        open(io_service);
    } catch (const isc::Exception& ex) {
        stopSending();
        isc_throw(NcrSenderOpenError, "Open failed: " << ex.what());
    }

    // Set our status to sending.
    setSending(true);
}

void
NameChangeSender::stopSending() {
    try {
        // Call implementation dependent close.
        close();
    } catch (const isc::Exception &ex) {
        // Swallow exceptions. If we have some sort of error we'll log
        // it but we won't propagate the throw.
        LOG_ERROR(dctl_logger, DHCP_DDNS_NCR_SEND_CLOSE_ERROR).arg(ex.what());
    }

    // Set it false, no matter what.  This allows us to at least try to
    // re-open via startSending().
    setSending(false);
}

void
NameChangeSender::sendRequest(NameChangeRequestPtr& ncr) {
    if (!amSending()) {
        isc_throw(NcrSenderError, "sender is not ready to send");
    }

    if (!ncr) {
        isc_throw(NcrSenderError, "request to send is empty");
    }

    if (send_queue_.size() >= send_queue_max_) {
        isc_throw(NcrSenderQueueFull, "send queue has reached maximum capacity:"
                  << send_queue_max_ );
    }

    // Put it on the queue.
    send_queue_.push_back(ncr);

    // Call sendNext to schedule the next one to go.
    sendNext();
}

void
NameChangeSender::sendNext() {
    if (ncr_to_send_) {
        // @todo Not sure if there is any risk of getting stuck here but
        // an interval timer to defend would be good.
        // In reality, the derivation should ensure they timeout themselves
        return;
    }

    // If queue isn't empty, then get one from the front. Note we leave
    // it on the front of the queue until we successfully send it.
    if (send_queue_.size()) {
        ncr_to_send_ = send_queue_.front();

       // @todo start defense timer
       // If a send were to hang and we timed it out, then timeout
       // handler need to cycle thru open/close ?

       // Call implementation dependent send.
       doSend(ncr_to_send_);
    }
}

void
NameChangeSender::invokeSendHandler(const NameChangeSender::Result result) {
    // @todo reset defense timer
    if (result == SUCCESS) {
        // It shipped so pull it off the queue.
        send_queue_.pop_front();
    }

    // Invoke the completion handler passing in the result and a pointer
    // the request involved.
    send_handler_(result, ncr_to_send_);

    // Clear the pending ncr pointer.
    ncr_to_send_.reset();

    // Set up the next send
    try {
        sendNext();
    } catch (const isc::Exception& ex) {
        // It is possible though unlikely, for sendNext to fail without
        // scheduling the send. While, unlikely, it does mean the callback
        // will not get called with a failure. A throw here would surface
        // at the IOService::run (or run variant) invocation.  So we will
        // close the window by invoking the application handler with
        // a failed result, and let the application layer sort it out.
        LOG_ERROR(dctl_logger, DHCP_DDNS_NCR_SEND_NEXT).arg(ex.what());
        send_handler_(ERROR, ncr_to_send_);
    }
}

void
NameChangeSender::skipNext() {
    if (send_queue_.size()) {
        // Discards the request at the front of the queue.
        send_queue_.pop_front();
    }
}

void
NameChangeSender::clearSendQueue() {
    if (amSending()) {
        isc_throw(NcrSenderError, "Cannot clear queue while sending");
    }

    send_queue_.clear();
}

} // namespace isc::d2
} // namespace isc
