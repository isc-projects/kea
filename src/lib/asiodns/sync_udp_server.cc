// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <asio.hpp>
#include <asio/error.hpp>

#include "sync_udp_server.h"
#include "logger.h"

#include <asiolink/dummy_io_cb.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>

#include <boost/bind.hpp>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls
#include <errno.h>

using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace asiodns {

SyncUDPServer::SyncUDPServer(asio::io_service& io_service, const int fd,
                             const int af, asiolink::SimpleCallback* checkin,
                             DNSLookup* lookup, DNSAnswer* answer) :
    output_buffer_(new isc::util::OutputBuffer(0)),
    query_(new isc::dns::Message(isc::dns::Message::PARSE)),
    answer_(new isc::dns::Message(isc::dns::Message::RENDER)),
    io_(io_service), checkin_callback_(checkin), lookup_callback_(lookup),
    answer_callback_(answer), stopped_(false)
{
    if (af != AF_INET && af != AF_INET6) {
        isc_throw(InvalidParameter, "Address family must be either AF_INET "
                  "or AF_INET6, not " << af);
    }
    LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_FD_ADD_UDP).arg(fd);
    try {
        socket_.reset(new asio::ip::udp::socket(io_service));
        socket_->assign(af == AF_INET6 ? asio::ip::udp::v6() :
                        asio::ip::udp::v4(), fd);
    } catch (const std::exception& exception) {
        // Whatever the thing throws, it is something from ASIO and we
        // convert it
        isc_throw(IOError, exception.what());
    }
}

void
SyncUDPServer::scheduleRead() {
    socket_->async_receive_from(asio::buffer(data_, MAX_LENGTH), sender_,
                                boost::bind(&SyncUDPServer::handleRead, this,
                                            _1, _2));
}

void
SyncUDPServer::handleRead(const asio::error_code& ec, const size_t length) {
    // Abort on fatal errors
    if (ec) {
        using namespace asio::error;
        if (ec.value() != would_block && ec.value() != try_again &&
            ec.value() != interrupted) {
            return;
        }
    }
    // Some kind of interrupt, spurious wakeup, or like that. Just try reading
    // again.
    if (ec || length == 0) {
        scheduleRead();
        return;
    }
    // OK, we have a real packet of data. Let's dig into it!

    // XXX: This is taken (and ported) from UDPSocket class. What the hell does
    // it really mean?

    // The UDP socket class has been extended with asynchronous functions
    // and takes as a template parameter a completion callback class.  As
    // UDPServer does not use these extended functions (only those defined
    // in the IOSocket base class) - but needs a UDPSocket to get hold of
    // the underlying Boost UDP socket - DummyIOCallback is used.  This
    // provides the appropriate operator() but is otherwise functionless.
    UDPSocket<DummyIOCallback> socket(*socket_);
    UDPEndpoint endpoint(sender_);
    IOMessage message(data_, length, socket, endpoint);
    if (checkin_callback_ != NULL) {
        (*checkin_callback_)(message);
        if (stopped_) {
            return;
        }
    }

    // If we don't have a DNS Lookup provider, there's no point in
    // continuing; we exit the coroutine permanently.
    if (lookup_callback_ == NULL) {
        scheduleRead();
        return;
    }

    // Make sure the buffers are fresh.  Note that we don't touch query_
    // because it's supposed to be cleared in lookup_callback_.  We should
    // eventually even remove this member variable (and remove it from
    // the lookup_callback_ interface, but until then, any callback
    // implementation should be careful that it's the responsibility of
    // the callback implementation.  See also #2239).
    output_buffer_->clear();
    answer_->clear(isc::dns::Message::RENDER);

    // Mark that we don't have an answer yet.
    done_ = false;
    resume_called_ = false;

    // Call the actual lookup
    (*lookup_callback_)(message, query_, answer_, output_buffer_, this);

    if (!resume_called_) {
        isc_throw(isc::Unexpected,
                  "No resume called from the lookup callback");
    }

    if (stopped_) {
        return;
    }

    if (done_) {
        // Good, there's an answer.
        // Call the answer callback to render it.
        (*answer_callback_)(message, query_, answer_, output_buffer_);

        if (stopped_) {
            return;
        }

        socket_->send_to(asio::buffer(output_buffer_->getData(),
                                      output_buffer_->getLength()),
                         sender_);
    }

    // And schedule handling another socket.
    scheduleRead();
}

void
SyncUDPServer::operator()(asio::error_code, size_t) {
    // To start the server, we just schedule reading of data when they
    // arrive.
    scheduleRead();
}

/// Stop the UDPServer
void
SyncUDPServer::stop() {
    /// Using close instead of cancel, because cancel
    /// will only cancel the asynchornized event already submitted
    /// to io service, the events post to io service after
    /// cancel still can be scheduled by io service, if
    /// the socket is cloesed, all the asynchronized event
    /// for it won't be scheduled by io service not matter it is
    /// submit to io serice before or after close call. And we will
    //. get bad_descriptor error
    socket_->close();
    stopped_ = true;
}

/// Post this coroutine on the ASIO service queue so that it will
/// resume processing where it left off.  The 'done' parameter indicates
/// whether there is an answer to return to the client.
void
SyncUDPServer::resume(const bool done) {
    resume_called_ = true;
    done_ = done;
}

bool
SyncUDPServer::hasAnswer() {
    return (done_);
}

} // namespace asiodns
} // namespace isc
