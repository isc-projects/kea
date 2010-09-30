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
class UDPServer : public coroutine {
public:
    explicit UDPServer(asio::io_service& io_service,
                       const asio::ip::address& addr, const uint16_t port,
                       CheckinProvider* checkin = NULL,
                       DNSProvider* process = NULL);
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);

private:
    enum { MAX_LENGTH = 4096 };

    // As mentioned in the comments to TCPServer, class member variables
    // which are dynamic, and changes to which are expected to be
    // accessible from both sides of a coroutine fork, should be
    // declared here as shared pointers and allocated in the
    // constructor or in the coroutine.
    boost::shared_ptr<asio::ip::udp::socket> socket_;
    boost::shared_ptr<asio::ip::udp::endpoint> sender_;
    boost::shared_ptr<isc::dns::OutputBuffer> response_;
    boost::shared_ptr<isc::dns::MessageRenderer> renderer_;
    boost::shared_ptr<isc::dns::Message> dns_message_;
    boost::shared_ptr<UDPEndpoint> io_endpoint_;
    boost::shared_ptr<IOMessage> io_message_;
    boost::shared_ptr<UDPSocket> io_socket_;
    boost::shared_ptr<char> data_;
    size_t bytes_;

    // Callbacks
    const CheckinProvider* checkin_callback_;
    const DNSProvider* dns_callback_;
};

}

#endif // __UDPDNS_H

// Local Variables: 
// mode: c++
// End: 
