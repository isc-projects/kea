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

#ifndef SYNC_UDP_SERVER_H
#define SYNC_UDP_SERVER_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include "dns_answer.h"
#include "dns_lookup.h"
#include "dns_server.h"

#include <dns/message.h>
#include <asiolink/simple_callback.h>
#include <util/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#include <stdint.h>

namespace isc {
namespace asiodns {

/// \brief An UDP server that doesn't asynchronous lookup handlers.
///
/// That means, the lookup handler must provide the answer right away.
/// This allows for implementation with less overhead, compared with
/// the UDPClass.
class SyncUDPServer : public DNSServer, public boost::noncopyable {
public:
    /// \brief Constructor
    /// \param io_service the asio::io_service to work with
    /// \param fd the file descriptor of opened UDP socket
    /// \param af address family, either AF_INET or AF_INET6
    /// \param checkin the callbackprovider for non-DNS events
    /// \param lookup the callbackprovider for DNS lookup events
    /// \param answer the callbackprovider for DNS answer events
    /// \throw isc::InvalidParameter if af is neither AF_INET nor AF_INET6
    /// \throw isc::asiolink::IOError when a low-level error happens, like the
    ///     fd is not a valid descriptor.
    SyncUDPServer(asio::io_service& io_service, const int fd, const int af,
                  isc::asiolink::SimpleCallback* checkin = NULL,
                  DNSLookup* lookup = NULL, DNSAnswer* answer = NULL);

    /// \brief Start the SyncUDPServer.
    ///
    /// This is the function operator to keep interface with other server
    /// classes. They need that because they're coroutines.
    virtual void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);

    /// \brief Calls the lookup callback
    virtual void asyncLookup() {
        isc_throw(Unexpected,
                  "SyncUDPServer doesn't support asyncLookup by design, use "
                  "UDPServer if you need it.");
    }

    /// \brief Stop the running server
    /// \note once the server stopped, it can't restart
    virtual void stop();

    /// \brief Resume operation
    ///
    /// Note that unlike other servers, this one expects it to be called
    /// directly from the lookup callback. If it isn't, the server will
    /// throw an Unexpected exception (probably to the event loop, which
    /// would usually lead to termination of the program, but that's OK,
    /// as it would be serious programmer error).
    ///
    /// \param done Set this to true if the lookup action is done and
    ///        we have an answer
    virtual void resume(const bool done);

    /// \brief Check if we have an answer
    ///
    /// \return true if we have an answer
    virtual bool hasAnswer();

    /// \brief Clones the object
    ///
    /// Since cloning is for the use of coroutines, the synchronous UDP server
    /// does not need to be cloned. Therefore supporting it would be needless
    /// work, and trying to clone it would be a programmer error anyway, this
    /// throws Unexpected.
    ///
    /// \return a newly allocated copy of this object
    virtual DNSServer* clone() {
        isc_throw(Unexpected, "SyncUDPServer can't be cloned.");
    }
private:
    // Internal state & buffers. We don't use the PIMPL idiom, as this class
    // isn't usually used directly anyway.

    // Maximum size of incoming UDP packet
    static const size_t MAX_LENGTH = 4096;
    // Buffer for incoming data
    uint8_t data_[MAX_LENGTH];
    // The buffer to render the output to and send it.
    // If it was OK to have just a buffer, not the wrapper class,
    // we could reuse the data_
    isc::util::OutputBufferPtr output_buffer_;
    // Objects to hold the query message and the answer
    isc::dns::MessagePtr query_, answer_;
    // The socket used for the communication
    std::auto_ptr<asio::ip::udp::socket> socket_;
    // The event loop we use
    asio::io_service& io_;
    // Place the socket puts the sender of a packet when it is received
    asio::ip::udp::endpoint sender_;
    // Callbacks
    const asiolink::SimpleCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;
    // Answers from the lookup callback (not sent directly, but signalled
    // through resume()
    bool resume_called_, done_;
    // This turns true when the server stops. Allows for not sending the
    // answer after we closed the socket.
    bool stopped_;

    // Auxiliary functions

    // Schedule next read on the socket. Just a wrapper around
    // socket_->async_read_from with the correct parameters.
    void scheduleRead();
    // Callback from the socket's read call (called when there's an error or
    // when a new packet comes).
    void handleRead(const asio::error_code& ec, const size_t length);
};

} // namespace asiodns
} // namespace isc
#endif // SYNC_UDP_SERVER_H
