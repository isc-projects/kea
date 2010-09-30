// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asiolink.h>
#include <internal/coroutine.h>
#include <internal/udpdns.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asiolink {
IOAddress
UDPEndpoint::getAddress() const {
    return (asio_endpoint_.address());
}

uint16_t
UDPEndpoint::getPort() const {
    return (asio_endpoint_.port());
}

short
UDPEndpoint::getProtocol() const {
    return (asio_endpoint_.protocol().protocol());
}

short
UDPEndpoint::getFamily() const {
    return (asio_endpoint_.protocol().family());
}

int
UDPSocket::getNative() const {
    return (socket_.native());
}

int
UDPSocket::getProtocol() const {
    return (IPPROTO_UDP);
}

UDPServer::UDPServer(io_service& io_service,
                     const ip::address& addr, const uint16_t port,
                     CheckinProvider* checkin, DNSProvider* process) :
    checkin_callback_(checkin), dns_callback_(process)
{
    // Wwe use a different instantiation for v4,
    // otherwise asio will bind to both v4 and v6
    if (addr.is_v6()) {
        socket_.reset(new udp::socket(io_service, udp::v6()));
        socket_->set_option(socket_base::reuse_address(true));
        socket_->set_option(asio::ip::v6_only(true));
        socket_->bind(udp::endpoint(udp::v6(), port));
    } else {
        socket_.reset(new udp::socket(io_service, udp::v4()));
        socket_->set_option(socket_base::reuse_address(true));
        socket_->bind(udp::endpoint(udp::v6(), port));
    }
}

void
UDPServer::operator()(error_code ec, size_t length) {
    CORO_REENTER (this) for (;;) {
        // Instantiate the data buffer that will be used by the
        // asynchronous read calls.
        data_ = boost::shared_ptr<char>(new char[MAX_LENGTH]);
        sender_.reset(new udp::endpoint());

        do {
            CORO_YIELD socket_->async_receive_from(asio::buffer(data_.get(),
                                                                MAX_LENGTH),
                                              *sender_, *this);
        } while (ec || length == 0);

        bytes_ = length;
        CORO_FORK UDPServer(*this)();
        if (is_parent()) {
            continue;
        }

        // Perform any necessary operations prior to processing
        // an incoming packet (e.g., checking for queued
        // configuration messages).
        //
        // (XXX: it may be a performance issue to have this
        // called for every single incoming packet; we may wish to
        // throttle it somehow in the future.)
        if (checkin_callback_ != NULL) {
            (*checkin_callback_)();
        }

        // Stop here if we don't have a DNS callback function
        if (dns_callback_ == NULL) {
            CORO_YIELD return;
        }

        // Instantialize objects that will be needed by the
        // DNS callback function and the async write.
        dns_message_.reset(new Message(Message::PARSE));
        response_.reset(new OutputBuffer(0));
        renderer_.reset(new MessageRenderer(*response_));
        io_socket_.reset(new UDPSocket(*socket_));
        io_endpoint_.reset(new UDPEndpoint(*sender_));
        io_message_.reset(new IOMessage(data_.get(), bytes_,
                                        *io_socket_,
                                        *io_endpoint_));

        // Process the DNS message
        if (! (*dns_callback_)(*io_message_, *dns_message_, *renderer_))
        {
            CORO_YIELD return;
        }

        CORO_YIELD socket_->async_send_to(asio::buffer(response_->getData(),
                                                       response_->getLength()),
                                     *sender_, *this);
    }
}

}
