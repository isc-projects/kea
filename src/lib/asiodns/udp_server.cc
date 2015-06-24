// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <unistd.h>             // for some IPC/network system calls
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

#include <boost/shared_array.hpp>

#include <asio.hpp>
#include <asio/error.hpp>
#include <asiolink/dummy_io_cb.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>
#include "udp_server.h"
#include "logger.h"

#include <dns/opcode.h>

// Avoid 'using namespace asio' (see tcp_server.cc)
using asio::io_service;
using asio::socket_base;
using asio::buffer;
using asio::ip::udp;
using asio::ip::address;

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::asiolink;

namespace isc {
namespace asiodns {

/*
 * Some of the member variables here are shared_ptrs and some are
 * auto_ptrs. There will be one instance of Data for the lifetime
 * of packet. The variables that are state only for a single packet
 * use auto_ptr, as it is more lightweight. In the case of shared
 * configuration (eg. the callbacks, socket), we use shared_ptrs.
 */
struct UDPServer::Data {
    /*
     * Constructors from parameters passed to UDPServer constructor.
     * This instance will not be used to retrieve and answer the actual
     * query, it will only hold parameters until we wait for the
     * first packet. But we do initialize the socket in here.
     */
    Data(io_service& io_service, const address& addr, const uint16_t port,
         DNSLookup* lookup, DNSAnswer* answer) :
        io_(io_service), bytes_(0), done_(false),
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
        socket_->bind(udp::endpoint(addr, port));
    }
    Data(io_service& io_service, int fd, int af,
         DNSLookup* lookup, DNSAnswer* answer) :
         io_(io_service), bytes_(0), done_(false),
         lookup_callback_(lookup),
         answer_callback_(answer)
    {
        if (af != AF_INET && af != AF_INET6) {
            isc_throw(InvalidParameter, "Address family must be either AF_INET"
                      " or AF_INET6, not " << af);
        }
        LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_FD_ADD_UDP).arg(fd);
        try {
            socket_.reset(new udp::socket(io_service));
            socket_->assign(af == AF_INET6 ? udp::v6() : udp::v4(), fd);
        } catch (const std::exception& exception) {
            // Whatever the thing throws, it is something from ASIO and we
            // convert it
            isc_throw(IOError, exception.what());
        }
    }

    /*
     * Copy constructor. Default one would probably do, but it is unnecessary
     * to copy many of the member variables every time we fork to handle
     * another packet.
     *
     * We also allocate data for receiving the packet here.
     */
    Data(const Data& other) :
        io_(other.io_), socket_(other.socket_), bytes_(0), done_(false),
        lookup_callback_(other.lookup_callback_),
        answer_callback_(other.answer_callback_)
    {
        // Instantiate the data buffer and endpoint that will
        // be used by the asynchronous receive call.
        data_.reset(new char[MAX_LENGTH]);
        sender_.reset(new udp::endpoint());
    }

    // The ASIO service object
    asio::io_service& io_;

    // Class member variables which are dynamic, and changes to which
    // need to accessible from both sides of a coroutine fork or from
    // outside of the coroutine (i.e., from an asynchronous I/O call),
    // should be declared here as pointers and allocated in the
    // constructor or in the coroutine.  This allows state information
    // to persist when an individual copy of the coroutine falls out
    // scope while waiting for an event, *so long as* there is another
    // object that is referencing the same data.  As a side-benefit, using
    // pointers also reduces copy overhead for coroutine objects.
    //
    // Note: Currently these objects are allocated by "new" in the
    // constructor, or in the function operator while processing a query.
    // Repeated allocations from the heap for every incoming query is
    // clearly a performance issue; this must be optimized in the future.
    // The plan is to have a structure pre-allocate several "Data"
    // objects which can be pulled off a free list and placed on an in-use
    // list whenever a query comes in.  This will serve the dual purpose
    // of improving performance and guaranteeing that state information
    // will *not* be destroyed when any one instance of the coroutine
    // falls out of scope while waiting for an event.
    //
    // Socket used to for listen for queries.  Created in the
    // constructor and stored in a shared_ptr because socket objects
    // are not copyable.
    boost::shared_ptr<asio::ip::udp::socket> socket_;

    // The ASIO-internal endpoint object representing the client
    std::auto_ptr<asio::ip::udp::endpoint> sender_;

    // \c IOMessage and \c Message objects to be passed to the
    // DNS lookup and answer providers
    std::auto_ptr<asiolink::IOMessage> io_message_;

    // The original query as sent by the client
    isc::dns::MessagePtr query_message_;

    // The response message we are building
    isc::dns::MessagePtr answer_message_;

    // The buffer into which the response is written
    isc::util::OutputBufferPtr respbuf_;

    // The buffer into which the query packet is written
    boost::shared_array<char> data_;

    // State information that is entirely internal to a given instance
    // of the coroutine can be declared here.
    size_t bytes_;
    bool done_;

    // Callback functions provided by the caller
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;

    std::auto_ptr<IOEndpoint> peer_;
    std::auto_ptr<IOSocket> iosock_;
};

/// The following functions implement the \c UDPServer class.
///
/// The constructor. It just creates new internal state object
/// and lets it handle the initialization.
UDPServer::UDPServer(io_service& io_service, int fd, int af,
                     DNSLookup* lookup,
                     DNSAnswer* answer) :
    data_(new Data(io_service, fd, af, lookup, answer))
{ }

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
UDPServer::operator()(asio::error_code ec, size_t length) {
    /// Because the coroutine reentry block is implemented as
    /// a switch statement, inline variable declarations are not
    /// permitted.  Certain variables used below can be declared here.

    CORO_REENTER (this) {
        do {
            /*
             * This is preparation for receiving a packet. We get a new
             * state object for the lifetime of the next packet to come.
             * It allocates the buffers to receive data into.
             */
            data_.reset(new Data(*data_));

            do {
                // Begin an asynchronous receive, then yield.
                // When the receive event is posted, the coroutine
                // will resume immediately after this point.
                CORO_YIELD data_->socket_->async_receive_from(
                    buffer(data_->data_.get(), MAX_LENGTH), *data_->sender_,
                    *this);

                // See TCPServer::operator() for details on error handling.
                if (ec) {
                    using namespace asio::error;
                    const asio::error_code::value_type err_val = ec.value();
                    if (err_val == operation_aborted ||
                        err_val == bad_descriptor) {
                        return;
                    }
                    if (err_val != would_block && err_val != try_again &&
                        err_val != interrupted) {
                        LOG_ERROR(logger, ASIODNS_UDP_RECEIVE_FAIL).
                            arg(ec.message());
                    }
                }

            } while (ec || length == 0);

            data_->bytes_ = length;

            /*
             * We fork the coroutine now. One (the child) will keep
             * the current state and handle the packet, then die and
             * drop ownership of the state. The other (parent) will just
             * go into the loop again and replace the current state with
             * a new one for a new object.
             *
             * Actually, both of the coroutines will be a copy of this
             * one, but that's just internal implementation detail.
             */
            CORO_FORK data_->io_.post(UDPServer(*this));
        } while (is_parent());

        // Create an \c IOMessage object to store the query.
        //
        // (XXX: It would be good to write a factory function
        // that would quickly generate an IOMessage object without
        // all these calls to "new".)
        data_->peer_.reset(new UDPEndpoint(*data_->sender_));

        // The UDP socket class has been extended with asynchronous functions
        // and takes as a template parameter a completion callback class.  As
        // UDPServer does not use these extended functions (only those defined
        // in the IOSocket base class) - but needs a UDPSocket to get hold of
        // the underlying Boost UDP socket - DummyIOCallback is used.  This
        // provides the appropriate operator() but is otherwise functionless.
        data_->iosock_.reset(
            new UDPSocket<DummyIOCallback>(*data_->socket_));

        data_->io_message_.reset(new IOMessage(data_->data_.get(),
            data_->bytes_, *data_->iosock_, *data_->peer_));

        // If we don't have a DNS Lookup provider, there's no point in
        // continuing; we exit the coroutine permanently.
        if (data_->lookup_callback_ == NULL) {
            return;
        }

        // Instantiate objects that will be needed by the
        // asynchronous DNS lookup and/or by the send call.
        data_->respbuf_.reset(new OutputBuffer(0));
        data_->query_message_.reset(new Message(Message::PARSE));
        data_->answer_message_.reset(new Message(Message::RENDER));

        // Schedule a DNS lookup, and yield.  When the lookup is
        // finished, the coroutine will resume immediately after
        // this point.
        CORO_YIELD data_->io_.post(AsyncLookup<UDPServer>(*this));

        // The 'done_' flag indicates whether we have an answer
        // to send back.  If not, exit the coroutine permanently.
        if (!data_->done_) {
            return;
        }

        // Call the DNS answer provider to render the answer into
        // wire format
        (*data_->answer_callback_)(*data_->io_message_, data_->query_message_,
            data_->answer_message_, data_->respbuf_);

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point
        // (though we have nothing further to do, so the coroutine
        // will simply exit at that time, after reporting an error if
        // there was one).
        CORO_YIELD data_->socket_->async_send_to(
            buffer(data_->respbuf_->getData(), data_->respbuf_->getLength()),
            *data_->sender_, *this);
        if (ec) {
            LOG_ERROR(logger, ASIODNS_UDP_ASYNC_SEND_FAIL).
                      arg(data_->sender_->address().to_string()).
                      arg(ec.message());
        }
    }
}

/// Call the DNS lookup provider.  (Expected to be called by the
/// AsyncLookup<UDPServer> handler.)
void
UDPServer::asyncLookup() {
    (*data_->lookup_callback_)(*data_->io_message_,
        data_->query_message_, data_->answer_message_, data_->respbuf_, this);
}

/// Stop the UDPServer
void
UDPServer::stop() {
    asio::error_code ec;

    /// Using close instead of cancel, because cancel
    /// will only cancel the asynchronized event already submitted
    /// to io service, the events post to io service after
    /// cancel still can be scheduled by io service, if
    /// the socket is closed, all the asynchronized event
    /// for it won't be scheduled by io service not matter it is
    /// submit to io service before or after close call. And we will
    //  get bad_descriptor error.
    data_->socket_->close(ec);
    if (ec) {
        LOG_ERROR(logger, ASIODNS_UDP_CLOSE_FAIL).arg(ec.message());
    }
}

/// Post this coroutine on the ASIO service queue so that it will
/// resume processing where it left off.  The 'done' parameter indicates
/// whether there is an answer to return to the client.
void
UDPServer::resume(const bool done) {
    data_->done_ = done;
    data_->io_.post(*this);  // this can throw, but can be considered fatal.
}

} // namespace asiodns
} // namespace isc
