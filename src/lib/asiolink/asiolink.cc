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

#include <asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/tcpdns.h>
#include <asiolink/internal/udpdns.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asiolink {

IOAddress::IOAddress(const string& address_str)
    // XXX: we cannot simply construct the address in the initialization list
    // because we'd like to throw our own exception on failure.
{
    error_code err;
    asio_address_ = ip::address::from_string(address_str, err);
    if (err) {
        isc_throw(IOError, "Failed to convert string to address '"
                  << address_str << "': " << err.message());
    }
}

IOAddress::IOAddress(const ip::address& asio_address) :
    asio_address_(asio_address)
{}

string
IOAddress::toText() const {
    return (asio_address_.to_string());
}

short
IOAddress::getFamily() const {
    if (asio_address_.is_v4()) {
        return (AF_INET);
    } else {
        return (AF_INET6);
    }
}

const IOEndpoint*
IOEndpoint::create(const int protocol, const IOAddress& address,
                   const unsigned short port)
{
    if (protocol == IPPROTO_UDP) {
        return (new UDPEndpoint(address, port));
    } else if (protocol == IPPROTO_TCP) {
        return (new TCPEndpoint(address, port));
    }
    isc_throw(IOError,
              "IOEndpoint creation attempt for unsupported protocol: " <<
              protocol);
}

IOMessage::IOMessage(const void* data, const size_t data_size,
                     const IOSocket& io_socket,
                     const IOEndpoint& remote_endpoint) :
    data_(data), data_size_(data_size), io_socket_(io_socket),
    remote_endpoint_(remote_endpoint)
{}

IOQuery::IOQuery(IOService& io_service) : io_service_(io_service) {}

void
IOQuery::sendQuery(const IOMessage& io_message,
                   const Question& question, MessageRenderer& renderer,
                   BasicServer* completer)
{
    error_code err;
    // XXX: hard-code the address for now:
    const ip::address addr = ip::address::from_string("192.168.1.12", err);

    // XXX: eventually we will need to be able to determine whether
    // the message should be sent via TCP or UDP, or sent initially via
    // UDP and then fall back to TCP on failure, but for the moment
    // we're only going to handle UDP.
    UDPQuery* query = new UDPQuery(io_service_.get_io_service(), io_message,
                                   question, addr, renderer, completer);
    (*query)();
}

class IOServiceImpl {
public:
    IOServiceImpl(const char& port,
                  const ip::address* v4addr, const ip::address* v6addr,
                  IOCallback* checkin, DNSLookup* lookup,
                  DNSAnswer* answer);
    asio::io_service io_service_;

    typedef boost::shared_ptr<UDPServer> UDPServerPtr;
    typedef boost::shared_ptr<TCPServer> TCPServerPtr;
    UDPServerPtr udp4_server_;
    UDPServerPtr udp6_server_;
    TCPServerPtr tcp4_server_;
    TCPServerPtr tcp6_server_;
};

IOServiceImpl::IOServiceImpl(const char& port,
                             const ip::address* const v4addr,
                             const ip::address* const v6addr,
                             IOCallback* checkin,
                             DNSLookup* lookup,
                             DNSAnswer* answer) :
    udp4_server_(UDPServerPtr()), udp6_server_(UDPServerPtr()),
    tcp4_server_(TCPServerPtr()), tcp6_server_(TCPServerPtr())
{
    uint16_t portnum;
    try {
        // XXX: SunStudio with stlport4 doesn't reject some invalid
        // representation such as "-1" by lexical_cast<uint16_t>, so
        // we convert it into a signed integer of a larger size and perform
        // range check ourselves.
        const int32_t portnum32 = boost::lexical_cast<int32_t>(&port);
        if (portnum32 < 0 || portnum32 > 65535) {
            isc_throw(IOError, "Invalid port number '" << &port);
        }
        portnum = portnum32;
    } catch (const boost::bad_lexical_cast& ex) {
        isc_throw(IOError, "Invalid port number '" << &port << "': " <<
                  ex.what());
    }

    try {
        if (v4addr != NULL) {
            udp4_server_ = UDPServerPtr(new UDPServer(io_service_,
                                                      *v4addr, portnum,
                                                      checkin, lookup, answer));
            (*udp4_server_)();
            tcp4_server_ = TCPServerPtr(new TCPServer(io_service_,
                                                      *v4addr, portnum,
                                                      checkin, lookup, answer));
            (*tcp4_server_)();
        }
        if (v6addr != NULL) {
            udp6_server_ = UDPServerPtr(new UDPServer(io_service_,
                                                      *v6addr, portnum,
                                                      checkin, lookup, answer));
            (*udp6_server_)();
            tcp6_server_ = TCPServerPtr(new TCPServer(io_service_,
                                                      *v6addr, portnum,
                                                      checkin, lookup, answer));
            (*tcp6_server_)();
        }
    } catch (const asio::system_error& err) {
        // We need to catch and convert any ASIO level exceptions.
        // This can happen for unavailable address, binding a privilege port
        // without the privilege, etc.
        isc_throw(IOError, "Failed to initialize network servers: " <<
                  err.what());
    }
}

IOService::IOService(const char& port, const char& address,
                     IOCallback* checkin,
                     DNSLookup* lookup,
                     DNSAnswer* answer) :
    impl_(NULL)
{
    error_code err;
    const ip::address addr = ip::address::from_string(&address, err);
    if (err) {
        isc_throw(IOError, "Invalid IP address '" << &address << "': "
                  << err.message());
    }

    impl_ = new IOServiceImpl(port,
                              addr.is_v4() ? &addr : NULL,
                              addr.is_v6() ? &addr : NULL,
                              checkin, lookup, answer);
}

IOService::IOService(const char& port,
                     const bool use_ipv4, const bool use_ipv6,
                     IOCallback* checkin,
                     DNSLookup* lookup,
                     DNSAnswer* answer) :
    impl_(NULL)
{
    const ip::address v4addr_any = ip::address(ip::address_v4::any());
    const ip::address* const v4addrp = use_ipv4 ? &v4addr_any : NULL; 
    const ip::address v6addr_any = ip::address(ip::address_v6::any());
    const ip::address* const v6addrp = use_ipv6 ? &v6addr_any : NULL;
    impl_ = new IOServiceImpl(port, v4addrp, v6addrp, checkin, lookup, answer);
}

IOService::~IOService() {
    delete impl_;
}

void
IOService::run() {
    impl_->io_service_.run();
}

void
IOService::stop() {
    impl_->io_service_.stop();
}

asio::io_service&
IOService::get_io_service() {
    return (impl_->io_service_);
}

}
