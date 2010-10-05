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

#include <asiolink.h>
#include <internal/coroutine.h>
#include <internal/tcpdns.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asiolink {
/// The following functions provide TCP-specific concrete implementations
/// of the \c IOEndpoint and \c IOSocket classes.
///
/// \brief Returns the address of an endpoint
IOAddress
TCPEndpoint::getAddress() const {
    return (asio_endpoint_.address());
}

/// \brief Returns the port of an endpoint
uint16_t
TCPEndpoint::getPort() const {
    return (asio_endpoint_.port());
}

/// \brief Returns the protocol number of an endpoint.
short
TCPEndpoint::getProtocol() const {
    return (asio_endpoint_.protocol().protocol());
}

/// \brief Returns the address family of an endpoint.
short
TCPEndpoint::getFamily() const {
    return (asio_endpoint_.protocol().family());
}

/// \brief Returns the native socket descriptor for a socket.
int
TCPSocket::getNative() const {
    return (socket_.native());
}

/// \brief Returns the protocol number for a socket (since this 
/// is the TCP-specific implementation, that is always IPPROTO_TCP).
int
TCPSocket::getProtocol() const {
    return (IPPROTO_TCP);
}

/// The following functions implement the \c UDPServer class.
///
/// The constructor
TCPServer::TCPServer(io_service& io_service,
                     const ip::address& addr, const uint16_t port, 
                     const SimpleCallback* checkin,
                     const DNSLookup* lookup,
                     const DNSAnswer* answer) :
    io_(io_service), done_(false),
    checkin_callback_(checkin), lookup_callback_(lookup),
    answer_callback_(answer)
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

    lenbuf_.reset(new OutputBuffer(TCP_MESSAGE_LENGTHSIZE));
    respbuf_.reset(new OutputBuffer(0));
}

void
TCPServer::operator()(error_code ec, size_t length) {
    if (ec) {
        return;
    }

    /// Because the coroutine reeentry block is implemented as
    /// a switch statement, inline variable declarations are not
    /// permitted.  Certain variables used below can be declared here.
    boost::array<const_buffer,2> bufs;

    CORO_REENTER (this) {
        do {
            /// Create a socket to listen for connections
            socket_.reset(new tcp::socket(acceptor_->get_io_service()));

            /// Wait for new connections
            CORO_YIELD acceptor_->async_accept(*socket_, *this);

            /// Fork the coroutine by creating a copy of this one and
            /// scheduling it on the ASIO service queue.  The parent
            /// will continue listening for DNS connections while the
            /// handles the one that has just arrived.
            CORO_FORK io_.post(TCPServer(*this));
        } while (is_parent());

        /// Instantiate the data buffer that will be used by the
        /// asynchronous read call.
        data_ = boost::shared_ptr<char>(new char[MAX_LENGTH]);

        /// First, read the message length.
        CORO_YIELD async_read(*socket_, asio::buffer(data_.get(),
                              TCP_MESSAGE_LENGTHSIZE), *this);

        /// Now read the message itself. (This is done in a different scope
        /// to allow inline variable declarations.)
        CORO_YIELD {
            InputBuffer dnsbuffer((const void *) data_.get(), length);
            uint16_t msglen = dnsbuffer.readUint16();
            async_read(*socket_, asio::buffer(data_.get(), msglen), *this);
        }

        // Create an \c IOMessage object to store the query.
        peer_.reset(new TCPEndpoint(socket_->remote_endpoint()));
        iosock_.reset(new TCPSocket(*socket_));
        io_message_.reset(new IOMessage(data_.get(), length, *iosock_, *peer_));
        bytes_ = length;

        // Perform any necessary operations prior to processing the incoming
        // packet (e.g., checking for queued configuration messages).
        //
        // (XXX: it may be a performance issue to have this called for
        // every single incoming packet; we may wish to throttle it somehow
        // in the future.)
        if (checkin_callback_ != NULL) {
            (*checkin_callback_)(*io_message_);
        }

        // If we don't have a DNS Lookup provider, there's no point in
        // continuing; we exit the coroutine permanently.
        if (lookup_callback_ == NULL) {
            CORO_YIELD return;
        }

        // Reset or instantiate objects that will be needed by the
        // DNS lookup and the write call.
        respbuf_->clear();
        message_.reset(new Message(Message::PARSE));

        // Schedule a DNS lookup, and yield.  When the lookup is
        // finished, the coroutine will resume immediately after
        // this point.
        CORO_YIELD io_.post(AsyncLookup<TCPServer>(*this));

        // The 'done_' flag indicates whether we have an answer
        // to send back.  If not, exit the coroutine permanently.
        if (!done_) {
            CORO_YIELD return;
        }

        // Call the DNS answer provider to render the answer into
        // wire format
        (*answer_callback_)(*io_message_, message_, respbuf_);

        // Set up the response, beginning with two length bytes.
        lenbuf_->clear();
        lenbuf_->writeUint16(respbuf_->getLength());
        bufs[0] = buffer(lenbuf_->getData(), lenbuf_->getLength());
        bufs[1] = buffer(respbuf_->getData(), respbuf_->getLength());

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point
        // (though we have nothing further to do, so the coroutine
        // will simply exit at that time).
        CORO_YIELD async_write(*socket_, bufs, *this);
    }
}

/// Call the DNS lookup provider.  (Expected to be called by the
/// AsyncLookup<TCPServer> handler.)
void
TCPServer::asyncLookup() {
    (*lookup_callback_)(*io_message_, message_, respbuf_, this);
}

/// Post this coroutine on the ASIO service queue so that it will
/// resume processing where it left off.  The 'done' parameter indicates
/// whether there is an answer to return to the client.
void
TCPServer::resume(const bool done) {
    done_ = done;
    io_.post(*this);
}

}
