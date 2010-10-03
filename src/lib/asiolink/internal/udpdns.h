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

namespace asiolink {
// Note: this implementation is optimized for the case where this object
// is created from an ASIO endpoint object in a receiving code path
// by avoiding to make a copy of the base endpoint.  For TCP it may not be
// a big deal, but when we receive UDP packets at a high rate, the copy
// overhead might be significant.
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
    virtual IOAddress getAddress() const;
    virtual uint16_t getPort() const;
    virtual short getProtocol() const;
    virtual short getFamily() const;
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
    virtual int getNative() const;
    virtual int getProtocol() const;
private:
    asio::ip::udp::socket& socket_;
};

//
// Asynchronous UDP server coroutine
//
class UDPServer : public virtual IOServer, public virtual coroutine {
public:
    explicit UDPServer(asio::io_service& io_service,
                       const asio::ip::address& addr, const uint16_t port,
                       IOCallback* checkin = NULL,
                       DNSLookup* lookup = NULL,
                       DNSAnswer* answer = NULL);

    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);

    enum { MAX_LENGTH = 4096 };
    asio::ip::udp::endpoint peer;

    void doLookup();
    void resume(const bool done);
    bool hasAnswer() { return (done_); }
    int value() { return (get_value()); }

    IOServer* clone() {
        UDPServer* s = new UDPServer(*this);
        s->cloned_ = true;
        return (s);
    }

private:
    asio::io_service& io_;

    // Class member variables which are dynamic, and changes to which
    // need to accessible from both sides of a coroutine fork or from
    // outside of the coroutine (i.e., from an asynchronous I/O call),
    // should be declared here as pointers and allocated in the
    // constructor or in the coroutine.
    boost::shared_ptr<asio::ip::udp::socket> socket_;
    boost::shared_ptr<char> data_;
    boost::shared_ptr<asio::ip::udp::endpoint> sender_;
    boost::shared_ptr<asiolink::IOEndpoint> peer_;
    boost::shared_ptr<asiolink::IOSocket> iosock_;
    boost::shared_ptr<asiolink::IOMessage> io_message_;
    isc::dns::MessagePtr message_;
    isc::dns::OutputBufferPtr respbuf_;

    // State information that is entirely internal to a given instance
    // of the coroutine can be declared here.
    size_t bytes_;
    bool done_;

    // Callbacks
    const IOCallback* checkin_callback_;
    const DNSLookup* lookup_callback_;
    const DNSAnswer* answer_callback_;
};

//
// Asynchronous UDP coroutine for upstream queries
//
class UDPQuery : public coroutine {
public:
    explicit UDPQuery(asio::io_service& io_service,
                      const IOMessage& io_message,
                      const isc::dns::Question& q,
                      const asio::ip::address& addr,
                      isc::dns::OutputBufferPtr buffer,
                      IOServer* server);
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0); 
private:
    enum { MAX_LENGTH = 4096 };

    boost::shared_ptr<asio::ip::udp::socket> socket_;
    asio::ip::udp::endpoint remote_;
    isc::dns::Question question_;
    isc::dns::OutputBuffer msgbuf_;
    isc::dns::OutputBufferPtr buffer_;;
    boost::shared_array<char> data_;

    /// \brief The UDP or TCP Server object from which the query originated.
    // IOServerPtr server_;
    IOServer* server_;
};
}


#endif // __UDPDNS_H

// Local Variables: 
// mode: c++
// End: 
