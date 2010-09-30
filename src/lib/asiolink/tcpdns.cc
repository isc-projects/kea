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
#include <asio/ip/address.hpp>

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asiolink.h>
#include <internal/coroutine.h>
#include <internal/tcpdns.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asiolink {

IOAddress
TCPEndpoint::getAddress() const {
    return (asio_endpoint_.address());
}

uint16_t
TCPEndpoint::getPort() const {
    return (asio_endpoint_.port());
}

short
TCPEndpoint::getProtocol() const {
    return (asio_endpoint_.protocol().protocol());
}

short
TCPEndpoint::getFamily() const {
    return (asio_endpoint_.protocol().family());
}

int
TCPSocket::getNative() const {
    return (socket_.native());
}

int
TCPSocket::getProtocol() const {
    return (IPPROTO_TCP);
}

TCPServer::TCPServer(io_service& io_service,
                     const ip::address& addr, const uint16_t port, 
                     CheckinProvider* checkin, DNSProvider* process) :
    respbuf_(0), lenbuf_(TCP_MESSAGE_LENGTHSIZE),
    checkin_callback_(checkin), dns_callback_(process)
{
    tcp::endpoint endpoint(addr, port);
    acceptor_.reset(new tcp::acceptor(io_service));
    acceptor_->open(endpoint.protocol());
    // Set v6-only (we use a separate instantiation for v4,
    // otherwise asio will bind to both v4 and v6
    if (addr.is_v6()) {
        acceptor_->set_option(ip::v6_only(true));
    }
    acceptor_->set_option(tcp::acceptor::reuse_address(true));
    acceptor_->bind(endpoint);
    acceptor_->listen();
}

void
TCPServer::operator()(error_code ec, size_t length) {
    if (ec) {
        return;
    }

    bool done = false;
    CORO_REENTER (this) {
        do {
            socket_.reset(new tcp::socket(acceptor_->get_io_service()));
            CORO_YIELD acceptor_->async_accept(*socket_, *this);
            CORO_FORK TCPServer(*this)();
        } while (is_child());

        // Perform any necessary operations prior to processing an incoming
        // packet (e.g., checking for queued configuration messages).
        //
        // (XXX: it may be a performance issue to have this called for
        // every single incoming packet; we may wish to throttle it somehow
        // in the future.)
        if (checkin_callback_ != NULL) {
            (*checkin_callback_)();
        }

        // Instantiate the data buffer that will be used by the
        // asynchronous read call.
        data_ = boost::shared_ptr<char>(new char[MAX_LENGTH]);
        CORO_YIELD async_read(*socket_, asio::buffer(data_.get(),
                                                     TCP_MESSAGE_LENGTHSIZE),
                              *this);

        CORO_YIELD {
            InputBuffer dnsbuffer((const void *) data_.get(), length);
            uint16_t msglen = dnsbuffer.readUint16();
            async_read(*socket_, asio::buffer(data_.get(), msglen), *this);
        }

        // Stop here if we don't have a DNS callback function
        if (dns_callback_ == NULL) {
            CORO_YIELD return;
        }

        // Instantiate the objects that will be needed by the
        // DNS callback and the asynchronous write calls.
        respbuf_.clear();
        renderer_.reset(new MessageRenderer(respbuf_));

        // Process the DNS message.  (Must be done in a separate scope 
        // because CORO_REENTER is implemented with a switch statement
        // and inline variable declaration isn't allowed.)
        {
            TCPEndpoint peer(socket_->remote_endpoint());
            TCPSocket iosock(*socket_);
            IOMessage io_message(data_.get(), length, iosock, peer);
            Message message(Message::PARSE);
            done = (*dns_callback_)(io_message, message, *renderer_);
        }

        if (!done) {
            CORO_YIELD return;
        }

        CORO_YIELD {
            lenbuf_.clear();
            lenbuf_.writeUint16(respbuf_.getLength());
            boost::array<const_buffer,2> bufs;
            bufs[0] = buffer(lenbuf_.getData(), lenbuf_.getLength());
            bufs[1] = buffer(respbuf_.getData(), respbuf_.getLength());
            async_write(*socket_, bufs, *this);
        }
    }
}

}
