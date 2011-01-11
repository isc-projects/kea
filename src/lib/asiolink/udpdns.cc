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
#include <asio/deadline_timer.hpp>

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
        peer_.reset(new UDPEndpoint(*sender_));
        iosock_.reset(new UDPSocket(*socket_));
        io_message_.reset(new IOMessage(data_.get(), bytes_, *iosock_, *peer_));

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

        dlog("[XX] got an answer");

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
    bool done = false;

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

    while (!done) {
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

        // Initial naive resolver:
        // The answer may be one of
        // - the final result
        // - a delegation
        // - an error
        // (there are more options but this is a start)
        Message incoming(Message::PARSE);
        InputBuffer ibuf(data_->data.get(), length);
        incoming.fromWire(ibuf);
        if (incoming.getRcode() == Rcode::NOERROR()) {
            if (incoming.getRRCount(Message::SECTION_ANSWER) > 0) {
                dlog("[XX] this looks like the final result");
                // stop and copy the full data (with the code we
                // already had, by providing the current buffer to
                // the answerprovider (we should revisit that part)
                done = true;
            } else {
                dlog("[XX] this looks like a delegation");
                // ok we need to do some more processing.
                // the ns list should contain all nameservers
                // while the additional may contain addresses for
                // them.
                // this needs to tie into NSAS of course
                // for this very first mockup, hope there is an
                // address in additional and just use that

                // send query to the first address
                bool found_address = false;
                for (RRsetIterator rrsi = incoming.beginSection(Message::SECTION_ADDITIONAL);
                     rrsi != incoming.endSection(Message::SECTION_ADDITIONAL) && !found_address;
                     rrsi++) {
                    ConstRRsetPtr rrs = *rrsi;
                    if (rrs->getType() == RRType::A()) {
                        // found address
                        RdataIteratorPtr rdi = rrs->getRdataIterator();
                        // just use the first
                        if (!rdi->isLast()) {
                            std::string addr_str = rdi->getCurrent().toText();
                            dlog("[XX] first address found: " + addr_str);
                            // now we have one address, simply
                            // resend that exact same query
                            // to that address and yield, when it
                            // returns, loop again.
                            //ip::address addr = 
                            data_->remote.address(ip::address::from_string(addr_str));
                            found_address = true;
                        }
                    }
                }
                if (found_address) {
                    // restart loop
                } else {
                    dlog("[XX] no ready-made addresses in additional. need nsas.");
                    // this will result in answering with the delegation. oh well
                    done = true;
                }
            }
        } else if (false) {
            dlog("[XX] this looks like an error");
            // like for a final answer, stop and pass on the
            // last buffer for now.
            done = true;
        }
    }

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
