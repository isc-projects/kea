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

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <boost/bind.hpp>

#include <asio.hpp>
#include <asio/deadline_timer.hpp>

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <log/dummylog.h>
#include <dns/opcode.h>
#include <dns/rcode.h>

#include <asiolink.h>
#include <internal/coroutine.h>
#include <internal/udpdns.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;
using isc::log::dlog;

using namespace std;
using namespace isc::dns;

namespace asiolink {

/*
 * Some of the member variables here are shared_ptrs and some are
 * auto_ptrs. There will be one instance of Data for the lifetime
 * of packet. The variables that are state only for a single packet
 * use auto_ptr, as it is more lightweight. In the case of shared
 * configuration (eg. the callbacks, socket), we use shared_ptrs.
 */
struct UDPServer::Data {
    /*
     * Constructor from parameters passed to UDPServer constructor.
     * This instance will not be used to retrieve and answer the actual
     * query, it will only hold parameters until we wait for the
     * first packet. But we do initialize the socket in here.
     */
    Data(io_service& io_service, const ip::address& addr, const uint16_t port,
        SimpleCallback* checkin, DNSLookup* lookup, DNSAnswer* answer) :
        io_(io_service), done_(false), checkin_callback_(checkin),
        lookup_callback_(lookup), answer_callback_(answer)
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

    /*
     * Copy constructor. Default one would probably do, but it is unnecessary
     * to copy many of the member variables every time we fork to handle
     * another packet.
     *
     * We also allocate data for receiving the packet here.
     */
    Data(const Data& other) :
        io_(other.io_), socket_(other.socket_), done_(false),
        checkin_callback_(other.checkin_callback_),
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
    isc::dns::OutputBufferPtr respbuf_;

    // The buffer into which the query packet is written
    boost::shared_array<char> data_;

    // State information that is entirely internal to a given instance
    // of the coroutine can be declared here.
    size_t bytes_;
    bool done_;

    // Callback functions provided by the caller
    const SimpleCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;

    std::auto_ptr<IOEndpoint> peer_;
    std::auto_ptr<IOSocket> iosock_;
};

/// The following functions implement the \c UDPServer class.
///
/// The constructor. It just creates new internal state object
/// and lets it handle the initialization.
UDPServer::UDPServer(io_service& io_service, const ip::address& addr,
    const uint16_t port, SimpleCallback* checkin, DNSLookup* lookup,
    DNSAnswer* answer) :
    data_(new Data(io_service, addr, port, checkin, lookup, answer))
{ }

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
UDPServer::operator()(error_code ec, size_t length) {
    /// Because the coroutine reeentry block is implemented as
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
        data_->iosock_.reset(new UDPSocket(*data_->socket_));
        data_->io_message_.reset(new IOMessage(data_->data_.get(),
            data_->bytes_, *data_->iosock_, *data_->peer_));

        // Perform any necessary operations prior to processing an incoming
        // query (e.g., checking for queued configuration messages).
        //
        // (XXX: it may be a performance issue to check in for every single
        // incoming query; we may wish to throttle this in the future.)
        if (data_->checkin_callback_ != NULL) {
            (*data_->checkin_callback_)(*data_->io_message_);
        }

        // If we don't have a DNS Lookup provider, there's no point in
        // continuing; we exit the coroutine permanently.
        if (data_->lookup_callback_ == NULL) {
            CORO_YIELD return;
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

        dlog("[XX] got an answer");

        // The 'done_' flag indicates whether we have an answer
        // to send back.  If not, exit the coroutine permanently.
        if (!data_->done_) {
            CORO_YIELD return;
        }

        // Call the DNS answer provider to render the answer into
        // wire format
        (*data_->answer_callback_)(*data_->io_message_, data_->query_message_,
            data_->answer_message_, data_->respbuf_);

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point
        // (though we have nothing further to do, so the coroutine
        // will simply exit at that time).
        CORO_YIELD data_->socket_->async_send_to(
            buffer(data_->respbuf_->getData(), data_->respbuf_->getLength()),
            *data_->sender_, *this);
    }
}

/// Call the DNS lookup provider.  (Expected to be called by the
/// AsyncLookup<UDPServer> handler.)
void
UDPServer::asyncLookup() {
    (*data_->lookup_callback_)(*data_->io_message_,
        data_->query_message_, data_->answer_message_, data_->respbuf_, this);
}

/// Post this coroutine on the ASIO service queue so that it will
/// resume processing where it left off.  The 'done' parameter indicates
/// whether there is an answer to return to the client.
void
UDPServer::resume(const bool done) {
    data_->done_ = done;
    data_->io_.post(*this);
}

bool
UDPServer::hasAnswer() {
    return (data_->done_);
}

// Private UDPQuery data (see internal/udpdns.h for reasons)
struct UDPQuery::PrivateData {
    // Socket we send query to and expect reply from there
    udp::socket socket;
    // Where was the query sent
    udp::endpoint remote;
    // What we ask the server
    Question question;
    // We will store the answer here
    OutputBufferPtr buffer;
    OutputBufferPtr msgbuf;
    // Temporary buffer for answer
    boost::shared_array<char> data;
    // This will be called when the data arrive or timeouts
    Callback* callback;
    // Did we already stop operating (data arrived, we timed out, someone
    // called stop). This can be so when we are cleaning up/there are
    // still pointers to us.
    bool stopped;
    // Timer to measure timeouts.
    deadline_timer timer;
    // How many milliseconds are we willing to wait for answer?
    int timeout;

    PrivateData(io_service& service,
        const udp::socket::protocol_type& protocol, const Question &q,
        OutputBufferPtr b, Callback *c) :
        socket(service, protocol),
        question(q),
        buffer(b),
        msgbuf(new OutputBuffer(512)),
        callback(c),
        stopped(false),
        timer(service)
    { }
};

/// The following functions implement the \c UDPQuery class.
///
/// The constructor
UDPQuery::UDPQuery(io_service& io_service,
                   const Question& q, const IOAddress& addr, uint16_t port,
                   OutputBufferPtr buffer, Callback *callback, int timeout) :
    data_(new PrivateData(io_service,
        addr.getFamily() == AF_INET ? udp::v4() : udp::v6(), q, buffer,
        callback))
{
    data_->remote = UDPEndpoint(addr, port).getASIOEndpoint();
    data_->timeout = timeout;
}

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
UDPQuery::operator()(error_code ec, size_t length) {
    if (ec || data_->stopped) {
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
            msg.setHeaderFlag(Message::HEADERFLAG_RD);
            msg.addQuestion(data_->question);
            MessageRenderer renderer(*data_->msgbuf);
            msg.toWire(renderer);
            dlog("Sending " + msg.toText() + " to " +
                data_->remote.address().to_string());
        }


        // If we timeout, we stop, which will shutdown everything and
        // cancel all other attempts to run inside the coroutine
        if (data_->timeout != -1) {
            data_->timer.expires_from_now(boost::posix_time::milliseconds(
                data_->timeout));
            data_->timer.async_wait(boost::bind(&UDPQuery::stop, *this,
                TIME_OUT));
        }

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point.
        CORO_YIELD data_->socket.async_send_to(buffer(data_->msgbuf->getData(),
            data_->msgbuf->getLength()), data_->remote, *this);

        /// Allocate space for the response.  (XXX: This should be
        /// optimized by maintaining a free list of pre-allocated blocks)
        data_->data.reset(new char[MAX_LENGTH]);

        /// Begin an asynchronous receive, and yield.  When the receive
        /// completes, we will resume immediately after this point.
        CORO_YIELD data_->socket.async_receive_from(buffer(data_->data.get(),
            MAX_LENGTH), data_->remote, *this);
        // The message is not rendered yet, so we can't print it easilly
        dlog("Received response from " + data_->remote.address().to_string());

        /// Copy the answer into the response buffer.  (XXX: If the
        /// OutputBuffer object were made to meet the requirements of
        /// a MutableBufferSequence, then it could be written to directly
        /// by async_recieve_from() and this additional copy step would
        /// be unnecessary.)
        data_->buffer->writeData(data_->data.get(), length);

        /// We are done
        stop(SUCCESS);
    }
}

void
UDPQuery::stop(Result result) {
    if (!data_->stopped) {
        switch (result) {
            case TIME_OUT:
                dlog("Query timed out");
                break;
            case STOPPED:
                dlog("Query stopped");
                break;
            default:;
        }
        data_->stopped = true;
        data_->socket.cancel();
        data_->socket.close();
        data_->timer.cancel();
        if (data_->callback) {
            (*data_->callback)(result);
        }
    }
}

}
