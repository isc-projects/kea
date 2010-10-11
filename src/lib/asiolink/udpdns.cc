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

#include <boost/bind.hpp>

#include <asio.hpp>

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
/// The following functions implement the \c UDPServer class.
///
/// The constructor
UDPServer::UDPServer(io_service& io_service,
                     const ip::address& addr, const uint16_t port,
                     SimpleCallback* checkin,
                     DNSLookup* lookup,
                     DNSAnswer* answer) :
    io_(io_service), done_(false),
    checkin_callback_(checkin),
    lookup_callback_(lookup),
    answer_callback_(answer)
{
    // We must use different instantiations for v4 and v6;
    // otherwise ASIO will bind to both
    udp proto = addr.is_v4() ? udp::v4() : udp::v6();
    socket_.reset(new udp::socket(io_service, proto));
    socket_->set_option(socket_base::reuse_address(true));
    if (addr.is_v6()) {
        socket_->set_option(asio::ip::v6_only(true));
    }
    socket_->bind(udp::endpoint(proto, port));
}

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
UDPServer::operator()(error_code ec, size_t length) {
    /// Because the coroutine reeentry block is implemented as
    /// a switch statement, inline variable declarations are not
    /// permitted.  Certain variables used below can be declared here.
    IOEndpoint* peer;
    IOSocket* iosock;

    CORO_REENTER (this) {
        do {
            // Instantiate the data buffer and endpoint that will
            // be used by the asynchronous receive call.
            data_.reset(new char[MAX_LENGTH]);
            sender_.reset(new udp::endpoint());

            do {
                // Begin an asynchronous receive, then yield.
                // When the receive event is posted, the coroutine
                // will resume immediately after this point.
                CORO_YIELD socket_->async_receive_from(buffer(data_.get(),
                                                              MAX_LENGTH),
                                                  *sender_, *this);
            } while (ec || length == 0);

            bytes_ = length;

            /// Fork the coroutine by creating a copy of this one and
            /// scheduling it on the ASIO service queue.  The parent
            /// will continue listening for DNS packets while the child
            /// processes the one that has just arrived.
            CORO_FORK io_.post(UDPServer(*this));
        } while (is_parent());

        // Create an \c IOMessage object to store the query.
        //
        // (XXX: It would be good to write a factory function
        // that would quickly generate an IOMessage object without
        // all these calls to "new".)
        peer = new UDPEndpoint(*sender_);
        iosock = new UDPSocket(*socket_);
        io_message_.reset(new IOMessage(data_.get(), bytes_, *iosock, *peer));

        // Perform any necessary operations prior to processing an incoming
        // query (e.g., checking for queued configuration messages).
        //
        // (XXX: it may be a performance issue to check in for every single
        // incoming query; we may wish to throttle this in the future.)
        if (checkin_callback_ != NULL) {
            (*checkin_callback_)(*io_message_);
        }

        // If we don't have a DNS Lookup provider, there's no point in
        // continuing; we exit the coroutine permanently.
        if (lookup_callback_ == NULL) {
            CORO_YIELD return;
        }

        // Instantiate objects that will be needed by the
        // asynchronous DNS lookup and/or by the send call.
        respbuf_.reset(new OutputBuffer(0));
        message_.reset(new Message(Message::PARSE));

        // Schedule a DNS lookup, and yield.  When the lookup is
        // finished, the coroutine will resume immediately after
        // this point.
        CORO_YIELD io_.post(AsyncLookup<UDPServer>(*this));

        // The 'done_' flag indicates whether we have an answer
        // to send back.  If not, exit the coroutine permanently.
        if (!done_) {
            CORO_YIELD return;
        }

        // Call the DNS answer provider to render the answer into
        // wire format
        (*answer_callback_)(*io_message_, message_, respbuf_);

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point
        // (though we have nothing further to do, so the coroutine
        // will simply exit at that time).
        CORO_YIELD socket_->async_send_to(buffer(respbuf_->getData(),
                                                 respbuf_->getLength()),
                                     *sender_, *this);
    }
}

/// Call the DNS lookup provider.  (Expected to be called by the
/// AsyncLookup<UDPServer> handler.)
void
UDPServer::asyncLookup() {
    (*lookup_callback_)(*io_message_, message_, respbuf_, this);
}

/// Post this coroutine on the ASIO service queue so that it will
/// resume processing where it left off.  The 'done' parameter indicates
/// whether there is an answer to return to the client.
void
UDPServer::resume(const bool done) {
    done_ = done;
    io_.post(*this);
}

/// The following functions implement the \c UDPQuery class.
///
/// The constructor
UDPQuery::UDPQuery(io_service& io_service,
                   const Question& q, const IOAddress& addr, uint16_t port,
                   OutputBufferPtr buffer, DNSServer* server) :
    question_(q), buffer_(buffer), server_(server->clone())
{
    udp proto = (addr.getFamily() == AF_INET) ? udp::v4() : udp::v6();
    socket_.reset(new udp::socket(io_service, proto));
    msgbuf_.reset(new OutputBuffer(512));
    remote_ = UDPEndpoint(addr, port).getASIOEndpoint();
}

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
UDPQuery::operator()(error_code ec, size_t length) {
    if (ec) {
        return;
    } 

    CORO_REENTER (this) {
        /// Generate the upstream query and render it to wire format
        /// This is done in a different scope to allow inline variable
        /// declarations.
        {
            Message msg(Message::RENDER);
            
            // XXX: replace with boost::random or some other suitable PRNG
            msg.setQid(0);
            msg.setOpcode(Opcode::QUERY());
            msg.setRcode(Rcode::NOERROR());
            msg.setHeaderFlag(MessageFlag::RD());
            msg.addQuestion(question_);
            MessageRenderer renderer(*msgbuf_);
            msg.toWire(renderer);
        }

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point.
        CORO_YIELD socket_->async_send_to(buffer(msgbuf_->getData(),
                                                 msgbuf_->getLength()),
                                           remote_, *this);

        /// Allocate space for the response.  (XXX: This should be
        /// optimized by maintaining a free list of pre-allocated blocks)
        data_.reset(new char[MAX_LENGTH]);

        /// Begin an asynchronous receive, and yield.  When the receive
        /// completes, we will resume immediately after this point.
        CORO_YIELD socket_->async_receive_from(buffer(data_.get(), MAX_LENGTH),
                                               remote_, *this);

        /// Copy the answer into the response buffer.  (XXX: If the
        /// OutputBuffer object were made to meet the requirements of
        /// a MutableBufferSequence, then it could be written to directly
        /// by async_recieve_from() and this additional copy step would
        /// be unnecessary.)
        buffer_->writeData(data_.get(), length);

        /// Signal the DNSServer object to resume processing.
        server_->resume(true);
    }
}

}
