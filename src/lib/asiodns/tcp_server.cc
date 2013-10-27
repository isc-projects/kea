// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/buffer.h>

#include <asio.hpp>
#include <asiolink/dummy_io_cb.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/tcp_socket.h>
#include <asiodns/tcp_server.h>
#include <asiodns/logger.h>

#include <boost/shared_array.hpp>

#include <cassert>
#include <unistd.h>             // for some IPC/network system calls
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

// Note: we intentionally avoid 'using namespace asio' to avoid conflicts with
// std:: definitions in C++11.
using asio::io_service;
using asio::buffer;
using asio::const_buffer;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::asiolink;

namespace isc {
namespace asiodns {

/// The following functions implement the \c TCPServer class.
///
/// The constructor
TCPServer::TCPServer(io_service& io_service, int fd, int af,
                     const DNSLookup* lookup,
                     const DNSAnswer* answer) :
    io_(io_service), done_(false),
    lookup_callback_(lookup),
    answer_callback_(answer)
{
    if (af != AF_INET && af != AF_INET6) {
        isc_throw(InvalidParameter, "Address family must be either AF_INET "
                  "or AF_INET6, not " << af);
    }
    LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_FD_ADD_TCP).arg(fd);

    try {
        acceptor_.reset(new tcp::acceptor(io_service));
        acceptor_->assign(af == AF_INET6 ? tcp::v6() : tcp::v4(), fd);
        acceptor_->listen();
    } catch (const std::exception& exception) {
        // Whatever the thing throws, it is something from ASIO and we convert
        // it
        isc_throw(IOError, exception.what());
    }
    // Set it to some value. It should be set to the right one
    // immediately, but set it to something non-zero just in case.
    tcp_recv_timeout_.reset(new size_t(5000));
}

namespace {
// Called by the timeout_ deadline timer if the client takes too long.
// If not aborted, cancels the given socket
// (in which case TCPServer::operator() will be called to continue,
// with an 'aborted' error code.)
void doTimeOut(boost::shared_ptr<asio::ip::tcp::socket> socket,
               const asio::error_code& error)
{
    if (error != asio::error::operation_aborted) {
        socket->cancel();
    }
}
}

void
TCPServer::operator()(asio::error_code ec, size_t length) {
    /// Because the coroutine reentry block is implemented as
    /// a switch statement, inline variable declarations are not
    /// permitted.  Certain variables used below can be declared here.

    boost::array<const_buffer,2> bufs;
    OutputBuffer lenbuf(TCP_MESSAGE_LENGTHSIZE);

    CORO_REENTER (this) {
        do {
            /// Create a socket to listen for connections (no-throw operation)
            socket_.reset(new tcp::socket(acceptor_->get_io_service()));

            /// Wait for new connections. In the event of non-fatal error,
            /// try again
            do {
                CORO_YIELD acceptor_->async_accept(*socket_, *this);
                if (ec) {
                    using namespace asio::error;
                    const asio::error_code::value_type err_val = ec.value();
                    // The following two cases can happen when this server is
                    // stopped: operation_aborted in case it's stopped after
                    // starting accept().  bad_descriptor in case it's stopped
                    // even before starting.  In these cases we should simply
                    // stop handling events.
                    if (err_val == operation_aborted ||
                        err_val == bad_descriptor) {
                        return;
                    }
                    // Other errors should generally be temporary and we should
                    // keep waiting for new connections.  We log errors that
                    // should really be rare and would only be caused by an
                    // internal erroneous condition (not an odd remote
                    // behavior).
                    if (err_val != would_block && err_val != try_again &&
                        err_val != connection_aborted &&
                        err_val != interrupted) {
                        LOG_ERROR(logger, ASIODNS_TCP_ACCEPT_FAIL).
                            arg(ec.message());
                    }
                }
            } while (ec);

            /// Fork the coroutine by creating a copy of this one and
            /// scheduling it on the ASIO service queue.  The parent
            /// will continue listening for DNS connections while the child
            /// handles the one that has just arrived.
            CORO_FORK io_.post(TCPServer(*this));
        } while (is_parent());

        // From this point, we'll simply return on error, which will
        // immediately trigger destroying this object, cleaning up all
        // resources including any open sockets.

        /// Instantiate the data buffer that will be used by the
        /// asynchronous read call.
        data_.reset(new char[MAX_LENGTH]);

        /// Start a timer to drop the connection if it is idle.  note that
        // we pass a shared_ptr of the socket object so that it won't be
        // destroyed at least until the timeout callback (including abort)
        // is called.
        if (*tcp_recv_timeout_ > 0) {
            timeout_.reset(new asio::deadline_timer(io_)); // shouldn't throw
            timeout_->expires_from_now( // consider any exception fatal.
                boost::posix_time::milliseconds(*tcp_recv_timeout_));
            timeout_->async_wait(boost::bind(&doTimeOut, socket_,
                                             asio::placeholders::error));
        }

        /// Read the message, in two parts.  First, the message length:
        CORO_YIELD async_read(*socket_, asio::buffer(data_.get(),
                              TCP_MESSAGE_LENGTHSIZE), *this);
        if (ec) {
            LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_TCP_READLEN_FAIL).
                arg(ec.message());
            return;
        }

        /// Now read the message itself. (This is done in a different scope
        /// to allow inline variable declarations.)
        CORO_YIELD {
            InputBuffer dnsbuffer(data_.get(), length);
            const uint16_t msglen = dnsbuffer.readUint16();
            async_read(*socket_, asio::buffer(data_.get(), msglen), *this);
        }
        if (ec) {
            LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_TCP_READDATA_FAIL).
                arg(ec.message());
            return;
        }

        // Create an \c IOMessage object to store the query.
        //
        // (XXX: It would be good to write a factory function
        // that would quickly generate an IOMessage object without
        // all these calls to "new".)
        peer_.reset(new TCPEndpoint(socket_->remote_endpoint(ec)));
        if (ec) {
            LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_TCP_GETREMOTE_FAIL).
                arg(ec.message());
            return;
        }

        // The TCP socket class has been extended with asynchronous functions
        // and takes as a template parameter a completion callback class.  As
        // TCPServer does not use these extended functions (only those defined
        // in the IOSocket base class) - but needs a TCPSocket to get hold of
        // the underlying Boost TCP socket - DummyIOCallback is used.  This
        // provides the appropriate operator() but is otherwise functionless.
        iosock_.reset(new TCPSocket<DummyIOCallback>(*socket_));
        io_message_.reset(new IOMessage(data_.get(), length, *iosock_,
                                        *peer_));

        // If we don't have a DNS Lookup provider, there's no point in
        // continuing; we exit the coroutine permanently.
        if (lookup_callback_ == NULL) {
            return;
        }

        // Reset or instantiate objects that will be needed by the
        // DNS lookup and the write call.
        respbuf_.reset(new OutputBuffer(0));
        query_message_.reset(new Message(Message::PARSE));
        answer_message_.reset(new Message(Message::RENDER));

        // Schedule a DNS lookup, and yield.  When the lookup is
        // finished, the coroutine will resume immediately after
        // this point.  On resume, this method should be called with its
        // default parameter values (because of the signature of post()'s
        // handler), so ec shouldn't indicate any error.
        CORO_YIELD io_.post(AsyncLookup<TCPServer>(*this));
        assert(!ec);

        // The 'done_' flag indicates whether we have an answer
        // to send back.  If not, exit the coroutine permanently.
        if (!done_) {
            // Explicitly close() isn't necessary for most cases. But for the
            // very connection, socket_ is shared with the original owner of
            // the server object and would stay open.
            // TODO: should we keep the connection open for a short time
            // to see if new requests come in?
            socket_->close(ec);
            if (ec) {
                LOG_DEBUG(logger, 0, ASIODNS_TCP_CLOSE_FAIL).arg(ec.message());
            }
            return;
        }

        // Call the DNS answer provider to render the answer into
        // wire format
        (*answer_callback_)(*io_message_, query_message_, answer_message_,
                            respbuf_);

        // Set up the response, beginning with two length bytes.
        lenbuf.writeUint16(respbuf_->getLength());
        bufs[0] = buffer(lenbuf.getData(), lenbuf.getLength());
        bufs[1] = buffer(respbuf_->getData(), respbuf_->getLength());

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point
        // (though we have nothing further to do, so the coroutine
        // will simply exit at that time).
        CORO_YIELD async_write(*socket_, bufs, *this);
        if (ec) {
            LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, ASIODNS_TCP_WRITE_FAIL).
                arg(ec.message());
        }

        // All done, cancel the timeout timer. if it throws, consider it fatal.
        timeout_->cancel();

        // TODO: should we keep the connection open for a short time
        // to see if new requests come in?
        socket_->close(ec);
        if (ec) {
            // close() should be unlikely to fail, but we've seen it fail once,
            // so we log the event (at the lowest level of debug).
            LOG_DEBUG(logger, 0, ASIODNS_TCP_CLOSE_FAIL).arg(ec.message());
        }
    }
}

/// Call the DNS lookup provider.  (Expected to be called by the
/// AsyncLookup<TCPServer> handler.)
void
TCPServer::asyncLookup() {
    (*lookup_callback_)(*io_message_, query_message_,
                        answer_message_, respbuf_, this);
}

void TCPServer::stop() {
    asio::error_code ec;

    /// we use close instead of cancel, with the same reason
    /// with udp server stop, refer to the udp server code

    acceptor_->close(ec);
    if (ec) {
        LOG_ERROR(logger, ASIODNS_TCP_CLOSE_ACCEPTOR_FAIL).arg(ec.message());
    }

    // User may stop the server even when it hasn't started to
    // run, in that case socket_ is empty
    if (socket_) {
        socket_->close(ec);
        if (ec) {
            LOG_ERROR(logger, ASIODNS_TCP_CLEANUP_CLOSE_FAIL).arg(ec.message());
        }
    }
}
/// Post this coroutine on the ASIO service queue so that it will
/// resume processing where it left off.  The 'done' parameter indicates
/// whether there is an answer to return to the client.
void
TCPServer::resume(const bool done) {
    done_ = done;

    // post() can throw due to memory allocation failure, but as like other
    // cases of the entire BIND 10 implementation, we consider it fatal and
    // let the exception be propagated.
    io_.post(*this);
}

} // namespace asiodns
} // namespace isc
