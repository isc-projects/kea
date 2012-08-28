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

#ifndef __TCP_SERVER_H
#define __TCP_SERVER_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <asiolink/asiolink.h>
#include <coroutine.h>
#include "dns_server.h"
#include "dns_lookup.h"
#include "dns_answer.h"

namespace isc {
namespace asiodns {

/// \brief A TCP-specific \c DNSServer object.
///
/// This class inherits from both \c DNSServer and from \c coroutine,
/// defined in coroutine.h.
class TCPServer : public virtual DNSServer, public virtual coroutine {
public:
    /// \brief Constructor
    /// \param io_service the asio::io_service to work with
    /// \param fd the file descriptor of opened TCP socket
    /// \param af address family of the socket, either AF_INET or AF_INET6
    /// \param checkin the callbackprovider for non-DNS events
    /// \param lookup the callbackprovider for DNS lookup events
    /// \param answer the callbackprovider for DNS answer events
    /// \throw isc::InvalidParameter if af is neither AF_INET nor AF_INET6
    /// \throw isc::asiolink::IOError when a low-level error happens, like the
    ///     fd is not a valid descriptor or it can't be listened on.
    TCPServer(asio::io_service& io_service, int fd, int af,
              const isc::asiolink::SimpleCallback* checkin = NULL,
              const DNSLookup* lookup = NULL, const DNSAnswer* answer = NULL);

    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);
    void asyncLookup();
    void stop();
    void resume(const bool done);
    DNSServer* clone() {
        TCPServer* s = new TCPServer(*this);
        return (s);
    }

private:
    enum { MAX_LENGTH = 65535 };
    static const size_t TCP_MESSAGE_LENGTHSIZE = 2;

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
    // The plan is to have a structure pre-allocate several "server state"
    // objects which can be pulled off a free list and placed on an in-use
    // list whenever a query comes in.  This will serve the dual purpose
    // of improving performance and guaranteeing that state information
    // will *not* be destroyed when any one instance of the coroutine
    // falls out of scope while waiting for an event.
    //
    // An ASIO acceptor object to handle new connections.  Created in
    // the constructor.
    boost::shared_ptr<asio::ip::tcp::acceptor> acceptor_;

    // Socket used to for listen for queries.  Created in the
    // constructor and stored in a shared_ptr because socket objects
    // are not copyable.
    boost::shared_ptr<asio::ip::tcp::socket> socket_;

    // The buffer into which the response is written
    boost::shared_ptr<isc::util::OutputBuffer> respbuf_;

    // \c IOMessage and \c Message objects to be passed to the
    // DNS lookup and answer providers
    boost::shared_ptr<isc::asiolink::IOMessage> io_message_;
    isc::dns::MessagePtr query_message_;
    isc::dns::MessagePtr answer_message_;

    // The buffer into which the query packet is written
    boost::shared_array<char>data_;

    // State information that is entirely internal to a given instance
    // of the coroutine can be declared here.
    size_t bytes_;
    bool done_;

    // Callback functions provided by the caller
    const isc::asiolink::SimpleCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;

    boost::shared_ptr<isc::asiolink::IOEndpoint> peer_;
    boost::shared_ptr<isc::asiolink::IOSocket> iosock_;

    // Timer used to timeout on tcp connections
    // This is a shared pointer because we need to have something
    // that outlives the operator() call and is copyable (for CORO_FORK)
    // even though it is only set after fork
    boost::shared_ptr<asio::deadline_timer> timeout_;
};

} // namespace asiodns
} // namespace isc
#endif // __TCP_SERVER_H
