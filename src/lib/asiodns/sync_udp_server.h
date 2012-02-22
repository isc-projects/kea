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

#ifndef __SYNC_UDP_SERVER_H
#define __SYNC_UDP_SERVER_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include "dns_answer.h"
#include "dns_lookup.h"
#include "dns_server.h"

#include <asiolink/simple_callback.h>
#include <exceptions.h>

#include <boost/noncopyable.hpp>

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
    /// \param addr the IP address to listen for queries on
    /// \param port the port to listen for queries on
    /// \param checkin the callbackprovider for non-DNS events
    /// \param lookup the callbackprovider for DNS lookup events
    /// \param answer the callbackprovider for DNS answer events
    explicit SyncUDPServer(asio::io_service& io_service,
                           const asio::ip::address& addr, const uint16_t port,
                           isc::asiolink::SimpleCallback* checkin = NULL,
                           DNSLookup* lookup = NULL,
                           DNSAnswer* answer = NULL);

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
    /// \return a newly allocated copy of this object
    virtual DNSServer* clone() {
        isc_throw(Unexpected, "SyncUDPServer can't be cloned.");
    }
private:
    static const size_t MAX_LENGTH = 4096;
    uint8_t data_[MAX_LENGTH];
    std::auto_ptr<asio::ip::udp::socket> socket_;
    asio::io_service& io_;
    asio::ip::udp::endpoint sender_;
    const asiolink::SimpleCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;
    bool resume_called_, done_;

    void scheduleRead();
    void handleRead(const asio::error_code& ec, const size_t length);
};

} // namespace asiodns
} // namespace isc
#endif // __SYNC_UDP_SERVER_H
