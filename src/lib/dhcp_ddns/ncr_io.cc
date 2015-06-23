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

#include <dhcp_ddns/dhcp_ddns_log.h>
#include <dhcp_ddns/ncr_io.h>

#include <asio.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace isc {
namespace dhcp_ddns {

NameChangeProtocol stringToNcrProtocol(const std::string& protocol_str) {
    if (boost::iequals(protocol_str, "UDP")) {
        return (NCR_UDP);
    }

    if (boost::iequals(protocol_str, "TCP")) {
        return (NCR_TCP);
    }

    isc_throw(BadValue,
              "Invalid NameChangeRequest protocol: " << protocol_str);
}

std::string ncrProtocolToString(NameChangeProtocol protocol) {
    switch (protocol) {
    case NCR_UDP:
        return ("UDP");
    case NCR_TCP:
        return ("TCP");
    default:
        break;
    }

    std::ostringstream stream;
    stream  << "UNKNOWN(" << protocol << ")";
    return (stream.str());
}


//************************** NameChangeListener ***************************

NameChangeListener::NameChangeListener(RequestReceiveHandler&
                                       recv_handler)
    : listening_(false), io_pending_(false), recv_handler_(recv_handler) {
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
        isc_throw(NcrListenerOpenError, "Open failed: " << ex.what());
    }

    // Set our status to listening.
    setListening(true);

    // Start the first asynchronous receive.
    try {
        receiveNext();
    } catch (const isc::Exception& ex) {
        stopListening();
        isc_throw(NcrListenerReceiveError, "doReceive failed: " << ex.what());
    }
}

void
NameChangeListener::receiveNext() {
    io_pending_ = true;
    doReceive();
}

void
NameChangeListener::stopListening() {
    try {
        // Call implementation dependent close.
        close();
    } catch (const isc::Exception &ex) {
        // Swallow exceptions. If we have some sort of error we'll log
        // it but we won't propagate the throw.
        LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_LISTEN_CLOSE_ERROR)
                  .arg(ex.what());
    }

    // Set it false, no matter what.  This allows us to at least try to
    // re-open via startListening().
    setListening(false);
}

void
NameChangeListener::invokeRecvHandler(const Result result,
                                      NameChangeRequestPtr& ncr) {
    // Call the registered application layer handler.
    // Surround the invocation with a try-catch. The invoked handler is
    // not supposed to throw, but in the event it does we will at least
    // report it.
    try {
        io_pending_ = false;
        recv_handler_(result, ncr);
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_UNCAUGHT_NCR_RECV_HANDLER_ERROR)
                  .arg(ex.what());
    }

    // Start the next IO layer asynchronous receive.
    // In the event the handler above intervened and decided to stop listening
    // we need to check that first.
    if (amListening()) {
        try {
            receiveNext();
        } catch (const isc::Exception& ex) {
            // It is possible though unlikely, for doReceive to fail without
            // scheduling the read. While, unlikely, it does mean the callback
            // will not get called with a failure. A throw here would surface
            // at the IOService::run (or run variant) invocation.  So we will
            // close the window by invoking the application handler with
            // a failed result, and let the application layer sort it out.
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_RECV_NEXT_ERROR)
                      .arg(ex.what());

            // Call the registered application layer handler.
            // Surround the invocation with a try-catch. The invoked handler is
            // not supposed to throw, but in the event it does we will at least
            // report it.
            NameChangeRequestPtr empty;
            try {
                io_pending_ = false;
                recv_handler_(ERROR, empty);
            } catch (const std::exception& ex) {
                LOG_ERROR(dhcp_ddns_logger,
                          DHCP_DDNS_UNCAUGHT_NCR_RECV_HANDLER_ERROR)
                          .arg(ex.what());
            }
        }
    }
}

//************************* NameChangeSender ******************************

NameChangeSender::NameChangeSender(RequestSendHandler& send_handler,
                                   size_t send_queue_max)
    : sending_(false), send_handler_(send_handler),
      send_queue_max_(send_queue_max), io_service_(NULL) {

    // Queue size must be big enough to hold at least 1 entry.
    setQueueMaxSize(send_queue_max);
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
        // Remember io service we're given.
        io_service_ = &io_service;
        open(io_service);
    } catch (const isc::Exception& ex) {
        stopSending();
        isc_throw(NcrSenderOpenError, "Open failed: " << ex.what());
    }

    // Set our status to sending.
    setSending(true);

    // If there's any queued already.. we'll start sending.
    sendNext();
}

void
NameChangeSender::stopSending() {
    // Set it send indicator to false, no matter what. This allows us to at 
    // least try to re-open via startSending(). Also, setting it false now, 
    // allows us to break sendNext() chain in invokeSendHandler.
    setSending(false);

    // If there is an outstanding IO to complete, attempt to process it.
    if (ioReady() && io_service_ != NULL) {
        try {
            runReadyIO();
        } catch (const std::exception& ex) {
            // Swallow exceptions. If we have some sort of error we'll log
            // it but we won't propagate the throw.
            LOG_ERROR(dhcp_ddns_logger,
                  DHCP_DDNS_NCR_FLUSH_IO_ERROR).arg(ex.what());
        }
    }

    try {
        // Call implementation dependent close.
        close();
    } catch (const isc::Exception &ex) {
        // Swallow exceptions. If we have some sort of error we'll log
        // it but we won't propagate the throw.
        LOG_ERROR(dhcp_ddns_logger,
                  DHCP_DDNS_NCR_SEND_CLOSE_ERROR).arg(ex.what());
    }

    io_service_ = NULL;
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
        isc_throw(NcrSenderQueueFull,
                  "send queue has reached maximum capacity: "
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
    if (!send_queue_.empty()) {
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
    // Surround the invocation with a try-catch. The invoked handler is
    // not supposed to throw, but in the event it does we will at least
    // report it.
    try {
        send_handler_(result, ncr_to_send_);
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_UNCAUGHT_NCR_SEND_HANDLER_ERROR)
                  .arg(ex.what());
    }

    // Clear the pending ncr pointer.
    ncr_to_send_.reset();

    // Set up the next send
    try {
        if (amSending()) {
            sendNext();
        }
    } catch (const isc::Exception& ex) {
        // It is possible though unlikely, for sendNext to fail without
        // scheduling the send. While, unlikely, it does mean the callback
        // will not get called with a failure. A throw here would surface
        // at the IOService::run (or run variant) invocation.  So we will
        // close the window by invoking the application handler with
        // a failed result, and let the application layer sort it out.
        LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_SEND_NEXT_ERROR)
                  .arg(ex.what());

        // Invoke the completion handler passing in failed result.
        // Surround the invocation with a try-catch. The invoked handler is
        // not supposed to throw, but in the event it does we will at least
        // report it.
        try {
            send_handler_(ERROR, ncr_to_send_);
        } catch (const std::exception& ex) {
            LOG_ERROR(dhcp_ddns_logger,
                      DHCP_DDNS_UNCAUGHT_NCR_SEND_HANDLER_ERROR).arg(ex.what());
        }
    }
}

void
NameChangeSender::skipNext() {
    if (!send_queue_.empty()) {
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

void
NameChangeSender::setQueueMaxSize(const size_t new_max) {
    if (new_max == 0) {
        isc_throw(NcrSenderError, "NameChangeSender:"
                  " queue size must be greater than zero");
    }

    send_queue_max_ = new_max;

}
const NameChangeRequestPtr&
NameChangeSender::peekAt(const size_t index) const {
    if (index >= getQueueSize()) {
        isc_throw(NcrSenderError,
                  "NameChangeSender::peekAt peek beyond end of queue attempted"
                  << " index: " << index << " queue size: " << getQueueSize());
    }

    return (send_queue_.at(index));
}


void
NameChangeSender::assumeQueue(NameChangeSender& source_sender) {
    if (source_sender.amSending()) {
        isc_throw(NcrSenderError, "Cannot assume queue:"
                  " source sender is actively sending");
    }

    if (amSending()) {
        isc_throw(NcrSenderError, "Cannot assume queue:"
                  " target sender is actively sending");
    }

    if (getQueueMaxSize() < source_sender.getQueueSize()) {
        isc_throw(NcrSenderError, "Cannot assume queue:"
                  " source queue count exceeds target queue max");
    }

    if (!send_queue_.empty()) {
        isc_throw(NcrSenderError, "Cannot assume queue:"
                  " target queue is not empty");
    }

    send_queue_.swap(source_sender.getSendQueue());
}

int
NameChangeSender::getSelectFd() {
    isc_throw(NotImplemented, "NameChangeSender::getSelectFd is not supported");
}

void
NameChangeSender::runReadyIO() {
    if (!io_service_) {
        isc_throw(NcrSenderError, "NameChangeSender::runReadyIO"
                  " sender io service is null");
    }

    // We shouldn't be here if IO isn't ready to execute.
    // By running poll we're gauranteed not to hang.
    /// @todo Trac# 3325 requests that asiolink::IOService provide a
    /// wrapper for poll().
    io_service_->get_io_service().poll_one();
}


} // namespace isc::dhcp_ddns
} // namespace isc
