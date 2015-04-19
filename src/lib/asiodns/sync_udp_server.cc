// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_ASIODNS_EXPORT

#include <config.h>

#include <asio.hpp>
#include <asio/error.hpp>

#include "sync_udp_server.h"
#include "logger.h"

#include <asiolink/dummy_io_cb.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>

#include <boost/bind.hpp>

#include <cassert>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls
#include <errno.h>

using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace asiodns {

SyncUDPServerPtr
SyncUDPServer::create(asio::io_service& io_service, const int fd,
                      const int af, DNSLookup* lookup)
{
    return (SyncUDPServerPtr(new SyncUDPServer(io_service, fd, af, lookup)));
}

SyncUDPServer::SyncUDPServer(asio::io_service& io_service, const int fd,
                             const int af, DNSLookup* lookup) :
    output_buffer_(new isc::util::OutputBuffer(0)),
    query_(new isc::dns::Message(isc::dns::Message::PARSE)),
    udp_endpoint_(sender_), lookup_callback_(lookup),
    resume_called_(false), done_(false), stopped_(false)
{
    if (af != AF_INET && af != AF_INET6) {
        isc_throw(InvalidParameter, "Address family must be either AF_INET "
                  "or AF_INET6, not " << af);
    }
    if (!lookup) {
        isc_throw(InvalidParameter, "null lookup callback given to "
                  "SyncUDPServer");
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
    udp_socket_.reset(new UDPSocket<DummyIOCallback>(*socket_));
}

void
SyncUDPServer::scheduleRead() {
    socket_->async_receive_from(
        asio::mutable_buffers_1(data_, MAX_LENGTH), sender_,
        boost::bind(&SyncUDPServer::handleRead, shared_from_this(), _1, _2));
}

void
SyncUDPServer::handleRead(const asio::error_code& ec, const size_t length) {
    if (stopped_) {
        // stopped_ can be set to true only after the socket object is closed.
        // checking this would also detect premature destruction of 'this'
        // object.
        assert(socket_ && !socket_->is_open());
        return;
    }
    if (ec) {
        using namespace asio::error;
        const asio::error_code::value_type err_val = ec.value();

        // See TCPServer::operator() for details on error handling.
        if (err_val == operation_aborted || err_val == bad_descriptor) {
            return;
        }
        if (err_val != would_block && err_val != try_again &&
            err_val != interrupted) {
            LOG_ERROR(logger, ASIODNS_UDP_SYNC_RECEIVE_FAIL).arg(ec.message());
        }
    }
    if (ec || length == 0) {
        scheduleRead();
        return;
    }
    // OK, we have a real packet of data. Let's dig into it!

    // Make sure the buffers are fresh.  Note that we don't touch query_
    // because it's supposed to be cleared in lookup_callback_.  We should
    // eventually even remove this member variable (and remove it from
    // the lookup_callback_ interface, but until then, any callback
    // implementation should be careful that it's the responsibility of
    // the callback implementation.  See also #2239).
    output_buffer_->clear();

    // Mark that we don't have an answer yet.
    done_ = false;
    resume_called_ = false;

    // Call the actual lookup
    const IOMessage message(data_, length, *udp_socket_, udp_endpoint_);
    (*lookup_callback_)(message, query_, answer_, output_buffer_, this);

    if (!resume_called_) {
        isc_throw(isc::Unexpected,
                  "No resume called from the lookup callback");
    }

    if (done_) {
        // Good, there's an answer.
        socket_->send_to(asio::const_buffers_1(output_buffer_->getData(),
                                               output_buffer_->getLength()),
                         sender_, 0, ec_);
        if (ec_) {
            LOG_ERROR(logger, ASIODNS_UDP_SYNC_SEND_FAIL).
                      arg(sender_.address().to_string()).arg(ec_.message());
        }
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
    /// will only cancel the asynchronized event already submitted
    /// to io service, the events post to io service after
    /// cancel still can be scheduled by io service, if
    /// the socket is closed, all the asynchronized event
    /// for it won't be scheduled by io service not matter it is
    /// submit to io service before or after close call. And we will
    /// get bad_descriptor error.
    socket_->close(ec_);
    stopped_ = true;
    if (ec_) {
        LOG_ERROR(logger, ASIODNS_SYNC_UDP_CLOSE_FAIL).arg(ec_.message());
    }
}

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
