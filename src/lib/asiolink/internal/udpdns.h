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

#ifndef __UDPDNS_H
#define __UDPDNS_H 1

#include <config.h>

#include <asio.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/coroutine.h>

// This file contains UDP-specific implementations of generic classes 
// defined in asiolink.h.  It is *not* intended to be part of the public
// API.

namespace asiolink {
// Note: this implementation is optimized for the case where this object
// is created from an ASIO endpoint object in a receiving code path
// by avoiding to make a copy of the base endpoint.  Otherwise, when we
// receive UDP packets at a high rate, the copy overhead might be significant.
class UDPEndpoint : public IOEndpoint {
public:
    UDPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new asio::ip::udp::endpoint(asio::ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}
    UDPEndpoint(const asio::ip::udp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}
        
    ~UDPEndpoint() { delete asio_endpoint_placeholder_; }

    inline IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }

    inline uint16_t getPort() const {
        return (asio_endpoint_.port());
    }

    inline short getProtocol() const {
        return (asio_endpoint_.protocol().protocol());
    }

    inline short getFamily() const {
        return (asio_endpoint_.protocol().family());
    }

    // This is not part of the exosed IOEndpoint API but allows
    // direct access to the ASIO implementation of the endpoint
    inline const asio::ip::udp::endpoint& getASIOEndpoint() const {
        return (asio_endpoint_);
    }

private:
    const asio::ip::udp::endpoint* asio_endpoint_placeholder_;
    const asio::ip::udp::endpoint& asio_endpoint_;
};

class UDPSocket : public IOSocket {
private:
    UDPSocket(const UDPSocket& source);
    UDPSocket& operator=(const UDPSocket& source);
public:
    UDPSocket(asio::ip::udp::socket& socket) : socket_(socket) {}

    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_UDP); }

private:
    asio::ip::udp::socket& socket_;
};

//
// Asynchronous UDP server coroutine
//
class UDPServer : public virtual DNSServer, public virtual coroutine {
public:
    explicit UDPServer(asio::io_service& io_service,
                       const asio::ip::address& addr, const uint16_t port,
                       SimpleCallback* checkin = NULL,
                       DNSLookup* lookup = NULL,
                       DNSAnswer* answer = NULL);

    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);

    void asyncLookup();
    void resume(const bool done);
    bool hasAnswer() { return (done_); }
    int value() { return (get_value()); }

    DNSServer* clone() {
        UDPServer* s = new UDPServer(*this);
        return (s);
    }

private:
    enum { MAX_LENGTH = 4096 };

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
    // Socket used to for listen for queries.  Created in the
    // constructor and stored in a shared_ptr because socket objects
    // are not copyable.
    boost::shared_ptr<asio::ip::udp::socket> socket_;

    // The ASIO-enternal endpoint object representing the client
    boost::shared_ptr<asio::ip::udp::endpoint> sender_;

    // \c IOMessage and \c Message objects to be passed to the
    // DNS lookup and answer providers
    boost::shared_ptr<asiolink::IOMessage> io_message_;
    isc::dns::MessagePtr message_;

    // The buffer into which the response is written
    isc::dns::OutputBufferPtr respbuf_;
    
    // The buffer into which the query packet is written
    boost::shared_ptr<char> data_;

    // State information that is entirely internal to a given instance
    // of the coroutine can be declared here.
    size_t bytes_;
    bool done_;

    // Callback functions provided by the caller
    const SimpleCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;
};

//
// Asynchronous UDP coroutine for upstream queries
//
class UDPQuery : public coroutine {
public:
    explicit UDPQuery(asio::io_service& io_service,
                      const isc::dns::Question& q,
                      const IOAddress& addr, uint16_t port,
                      isc::dns::OutputBufferPtr buffer,
                      DNSServer* server);
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0); 
private:
    enum { MAX_LENGTH = 4096 };

    // The \c UDPQuery coroutine never forks, but it is copied whenever
    // it calls an async_*() function, so it's best to keep copy overhead
    // small by using pointers or references when possible.  However, this
    // is not always possible.
    //
    // Socket used to for upstream queries. Created in the
    // constructor and stored in a shared_ptr because socket objects
    // are not copyable.
    boost::shared_ptr<asio::ip::udp::socket> socket_;

    // The remote endpoint.  Instantiated in the constructor.  Not
    // stored as a shared_ptr because copy overhead of an endpoint
    // object is no larger than that of a shared_ptr.
    asio::ip::udp::endpoint remote_;

    // The question being answered.  Copied rather than referenced
    // because the object that created it is not guaranteed to persist.
    isc::dns::Question question_;

    // The output buffer supplied by the caller.  The resposne frmo
    // the upstream server will be copied here.
    isc::dns::OutputBufferPtr buffer_;;

    // These are allocated for each new query and are stored as
    // shared pointers to minimize copy overhead.
    isc::dns::OutputBufferPtr msgbuf_;
    boost::shared_array<char> data_;

    // The UDP or TCP Server object from which the query originated.
    // Note: Using a shared_ptr for this can cause problems when
    // control is being transferred from this coroutine to the server;
    // the reference count can drop to zero and cause the server to be
    // destroyed before it executes.  Consequently in this case it's
    // safer to use a raw pointer.
    DNSServer* server_;
};
}


#endif // __UDPDNS_H

// Local Variables: 
// mode: c++
// End: 
