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

#ifndef UDP_SERVER_H
#define UDP_SERVER_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/simple_callback.h>
#include <asiodns/dns_answer.h>
#include <asiodns/dns_lookup.h>
#include <asiodns/dns_server.h>

#include <coroutine.h>

namespace isc {
namespace asiodns {

//
// Asynchronous UDP server coroutine
//
///
/// \brief This class implements the coroutine to handle UDP
///        DNS query event. As such, it is both a \c DNSServer and
///        a \c coroutine
///
class UDPServer : public virtual DNSServer, public virtual coroutine {
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
    UDPServer(asio::io_service& io_service, int fd, int af,
              isc::asiolink::SimpleCallback* checkin = NULL,
              DNSLookup* lookup = NULL, DNSAnswer* answer = NULL);

    /// \brief The function operator
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);

    /// \brief Calls the lookup callback
    void asyncLookup();

    /// \brief Stop the running server
    /// \note once the server stopped, it can't restart
    void stop();

    /// \brief Resume operation
    ///
    /// \param done Set this to true if the lookup action is done and
    ///        we have an answer
    void resume(const bool done);

    /// \brief Clones the object
    ///
    /// \return a newly allocated copy of this object
    DNSServer* clone() {
        UDPServer* s = new UDPServer(*this);
        return (s);
    }

private:
    enum { MAX_LENGTH = 4096 };

    /**
     * \brief Internal state and data.
     *
     * We use the pimple design pattern, but not because we need to hide
     * internal data. This class and whole header is for private use anyway.
     * It turned out that UDPServer is copied a lot, because it is a coroutine.
     * This way the overhead of copying is lower, we copy only one shared
     * pointer instead of about 10 of them.
     */
    struct Data;
    boost::shared_ptr<Data> data_;
};

} // namespace asiodns
} // namespace isc
#endif // UDP_SERVER_H
