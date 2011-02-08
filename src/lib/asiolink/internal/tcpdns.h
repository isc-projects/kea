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

#ifndef __TCPDNS_H
#define __TCPDNS_H 1

#include <config.h>


#include <asio.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/coroutine.h>

// This file contains TCP-specific implementations of generic classes 
// defined in asiolink.h.  It is *not* intended to be part of the public
// API.

namespace asiolink {
/// \brief The \c TCPEndpoint class is a concrete derived class of
/// \c IOEndpoint that represents an endpoint of a TCP connection.
///
/// In the current implementation, an object of this class is always
/// instantiated within the wrapper routines.  Applications are expected to
/// get access to the object via the abstract base class, \c IOEndpoint.
/// This design may be changed when we generalize the wrapper interface.
///
/// Note: this implementation is optimized for the case where this object
/// is created from an ASIO endpoint object in a receiving code path
/// by avoiding to make a copy of the base endpoint.  For TCP it may not be
/// a big deal, but when we receive UDP packets at a high rate, the copy
/// overhead might be significant.
class TCPEndpoint : public IOEndpoint {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// \brief Constructor from a pair of address and port.
    ///
    /// \param address The IP address of the endpoint.
    /// \param port The TCP port number of the endpoint.
    TCPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new asio::ip::tcp::endpoint(
                asio::ip::address::from_string(address.toText()), port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from an ASIO TCP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c tcp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the TCP endpoint.
    TCPEndpoint(const asio::ip::tcp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}

    /// \brief The destructor.
    ~TCPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }

    uint16_t getPort() const {
        return (asio_endpoint_.port());
    }

    short getProtocol() const {
        return (asio_endpoint_.protocol().protocol());
    }

    short getFamily() const {
        return (asio_endpoint_.protocol().family());
    }

    // This is not part of the exosed IOEndpoint API but allows
    // direct access to the ASIO implementation of the endpoint
    const asio::ip::tcp::endpoint& getASIOEndpoint() const {
        return (asio_endpoint_);
    }

private:
    const asio::ip::tcp::endpoint* asio_endpoint_placeholder_;
    const asio::ip::tcp::endpoint& asio_endpoint_;
};

/// \brief The \c TCPSocket class is a concrete derived class of
/// \c IOSocket that represents a TCP socket.
///
/// In the current implementation, an object of this class is always
/// instantiated within the wrapper routines.  Applications are expected to
/// get access to the object via the abstract base class, \c IOSocket.
/// This design may be changed when we generalize the wrapper interface.
class TCPSocket : public IOSocket {
private:
    TCPSocket(const TCPSocket& source);
    TCPSocket& operator=(const TCPSocket& source);
public:
    /// \brief Constructor from an ASIO TCP socket.
    ///
    /// \param socket The ASIO representation of the TCP socket.
    TCPSocket(asio::ip::tcp::socket& socket) : socket_(socket) {}

    int getNative() const { return (socket_.native()); }
    int getProtocol() const { return (IPPROTO_TCP); }

private:
    asio::ip::tcp::socket& socket_;
};

/// \brief A TCP-specific \c DNSServer object.
///
/// This class inherits from both \c DNSServer and from \c coroutine,
/// defined in coroutine.h. 
class TCPServer : public virtual DNSServer, public virtual coroutine {
public:
    explicit TCPServer(asio::io_service& io_service,
                       const asio::ip::address& addr, const uint16_t port, 
                       const SimpleCallback* checkin = NULL,
                       const DNSLookup* lookup = NULL,
                       const DNSAnswer* answer = NULL);

    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);
    void asyncLookup();
    void resume(const bool done);
    bool hasAnswer() { return (done_); }
    int value() { return (get_value()); }

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
    boost::shared_ptr<isc::dns::OutputBuffer> respbuf_;

    // \c IOMessage and \c Message objects to be passed to the
    // DNS lookup and answer providers
    boost::shared_ptr<asiolink::IOMessage> io_message_;
    isc::dns::MessagePtr query_message_;
    isc::dns::MessagePtr answer_message_;

    // The buffer into which the query packet is written
    boost::shared_array<char>data_;

    // State information that is entirely internal to a given instance
    // of the coroutine can be declared here.
    size_t bytes_;
    bool done_;

    // Callback functions provided by the caller
    const SimpleCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;

    boost::shared_ptr<IOEndpoint> peer_;
    boost::shared_ptr<IOSocket> iosock_;
};

}

#endif // __TCPDNS_H

// Local Variables: 
// mode: c++
// End: 
