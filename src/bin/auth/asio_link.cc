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

#include <asio_link.h>

#include "coroutine.h"
#include "yield.h"

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asio_link {

// Constructors and destructors for the callback provider base classes.
DNSProvider::DNSProvider() {}
DNSProvider::~DNSProvider() {}

bool
DNSProvider::operator()(const IOMessage& io_message,
                        isc::dns::Message& dns_message,
                        isc::dns::MessageRenderer& renderer) const
{
    return (false);
}

CheckinProvider::CheckinProvider() {}
CheckinProvider::~CheckinProvider() {}

void
CheckinProvider::operator()(void) const {}


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

// Note: this implementation is optimized for the case where this object
// is created from an ASIO endpoint object in a receiving code path
// by avoiding to make a copy of the base endpoint.  For TCP it may not be
// a bug deal, but when we receive UDP packets at a high rate, the copy
// overhead might be significant.
class TCPEndpoint : public IOEndpoint {
public:
    TCPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new tcp::endpoint(ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}
    TCPEndpoint(const tcp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}
        
    ~TCPEndpoint() { delete asio_endpoint_placeholder_; }
    virtual IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }
private:
    const tcp::endpoint* asio_endpoint_placeholder_;
    const tcp::endpoint& asio_endpoint_;
};

class UDPEndpoint : public IOEndpoint {
public:
    UDPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new udp::endpoint(ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}
    UDPEndpoint(const udp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}
    ~UDPEndpoint() { delete asio_endpoint_placeholder_; }
    virtual IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }
private:
    const udp::endpoint* asio_endpoint_placeholder_;
    const udp::endpoint& asio_endpoint_;
};

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

class TCPSocket : public IOSocket {
private:
    TCPSocket(const TCPSocket& source);
    TCPSocket& operator=(const TCPSocket& source);
public:
    TCPSocket(tcp::socket& socket) : socket_(socket) {}
    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_TCP); }
private:
    tcp::socket& socket_;
};

class UDPSocket : public IOSocket {
private:
    UDPSocket(const UDPSocket& source);
    UDPSocket& operator=(const UDPSocket& source);
public:
    UDPSocket(udp::socket& socket) : socket_(socket) {}
    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_UDP); }
private:
    udp::socket& socket_;
};

class DummySocket : public IOSocket {
private:
    DummySocket(const DummySocket& source);
    DummySocket& operator=(const DummySocket& source);
public:
    DummySocket(const int protocol) : protocol_(protocol) {}
    virtual int getNative() const { return (-1); }
    virtual int getProtocol() const { return (protocol_); }
private:
    const int protocol_;
};

IOSocket&
IOSocket::getDummyUDPSocket() {
    static DummySocket socket(IPPROTO_UDP);
    return (socket);
}

IOSocket&
IOSocket::getDummyTCPSocket() {
    static DummySocket socket(IPPROTO_TCP);
    return (socket);
}

IOMessage::IOMessage(const void* data, const size_t data_size,
                     IOSocket& io_socket, const IOEndpoint& remote_endpoint) :
    data_(data), data_size_(data_size), io_socket_(io_socket),
    remote_endpoint_(remote_endpoint)
{}

//
// Asynchronous TCP server coroutine
//
class TCPServer : public coroutine {
public:
    explicit TCPServer(io_service& io_service,
                       const ip::address& addr, const uint16_t port, 
                       CheckinProvider* checkin = NULL,
                       DNSProvider* process = NULL) :
        checkin_callback_(checkin), dns_callback_(process)
    {

        tcp::endpoint endpoint(addr, port);
        acceptor_.reset(new tcp::acceptor(io_service));
        acceptor_->open(endpoint.protocol());
        // Set v6-only (we use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (addr.is_v6()) {
            acceptor_->set_option(ip::v6_only(true));
        }
        acceptor_->set_option(tcp::acceptor::reuse_address(true));
        acceptor_->bind(endpoint);
        acceptor_->listen();
    }

    void operator()(error_code ec = error_code(), size_t length = 0) {
        if (ec) {
            return;
        }

        reenter (this) {
            do {
                socket_.reset(new tcp::socket(acceptor_->get_io_service()));
                yield acceptor_->async_accept(*socket_, *this);
                fork TCPServer(*this)();
            } while (is_parent());

            // Perform any necessary operations prior to processing
            // an incoming packet (e.g., checking for queued
            // configuration messages).
            if (checkin_callback_ != NULL) {
                (*checkin_callback_)();
            }

            // Instantiate the data buffer that will be used by the
            // asynchronous read calls.
            // data_.reset(new boost::array<char, MAX_LENGTH>);
            data_ = boost::shared_ptr<char>(new char[MAX_LENGTH]);

            yield async_read(*socket_,
                             asio::buffer(data_.get(), TCP_MESSAGE_LENGTHSIZE),
                             *this);

            yield {
                InputBuffer dnsbuffer((const void *) data_.get(), length);
                uint16_t msglen = dnsbuffer.readUint16();
                async_read(*socket_, asio::buffer(data_.get(), msglen), *this);
            }

            // Stop here if we don't have a DNS callback function
            if (dns_callback_ == NULL) {
                yield return;
            }

            // Instantiate the objects that will be used by the
            // asynchronous write calls.
            dns_message_.reset(new Message(Message::PARSE));
            response_.reset(new OutputBuffer(0));
            responselen_buffer_.reset(new OutputBuffer(TCP_MESSAGE_LENGTHSIZE));
            renderer_.reset(new MessageRenderer(*response_));
            io_socket_.reset(new TCPSocket(*socket_));
            io_endpoint_.reset(new TCPEndpoint(socket_->remote_endpoint()));
            io_message_.reset(new IOMessage(data_.get(), length, *io_socket_,
                                            *io_endpoint_));

            // Process the DNS message
            if (! (*dns_callback_)(*io_message_, *dns_message_, *renderer_)) {
                yield return;
            }

            responselen_buffer_->writeUint16(response_->getLength());
            yield async_write(*socket_,
                              asio::buffer(responselen_buffer_->getData(),
                                           responselen_buffer_->getLength()),
                              *this);
            yield async_write(*socket_,
                              asio::buffer(response_->getData(),
                                           response_->getLength()),
                              *this);
        }
    }

private:
    enum { MAX_LENGTH = 65535 };
    static const size_t TCP_MESSAGE_LENGTHSIZE = 2;

    // All class member variables which are expected to persist across
    // multiple invocations of the coroutine must be declared here as
    // shared pointers, and instantiated in the constructor or in the
    // coroutine itself.  When the coroutine is deleted, its destructor
    // will free the memory.
    boost::shared_ptr<tcp::acceptor> acceptor_;
    boost::shared_ptr<tcp::socket> socket_;
    boost::shared_ptr<OutputBuffer> response_;
    boost::shared_ptr<OutputBuffer> responselen_buffer_;
    boost::shared_ptr<MessageRenderer> renderer_;
    boost::shared_ptr<Message> dns_message_;
    boost::shared_ptr<IOMessage> io_message_;
    boost::shared_ptr<TCPSocket> io_socket_;
    boost::shared_ptr<TCPEndpoint> io_endpoint_;
    boost::shared_ptr<char> data_;

    // Callbacks
    const CheckinProvider* checkin_callback_;
    const DNSProvider* dns_callback_;
};

//
// Asynchronous UDP server coroutine
//
class UDPServer : public coroutine {
public:
    explicit UDPServer(io_service& io_service,
                       const ip::address& addr, const uint16_t port,
                       CheckinProvider* checkin = NULL,
                       DNSProvider* process = NULL) :
        checkin_callback_(checkin), dns_callback_(process)
    {
        // Wwe use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (addr.is_v6()) {
            socket_.reset(new udp::socket(io_service, udp::v6()));
            socket_->set_option(socket_base::reuse_address(true));
            socket_->set_option(asio::ip::v6_only(true));
            socket_->bind(udp::endpoint(udp::v6(), port));
        } else {
            socket_.reset(new udp::socket(io_service, udp::v4()));
            socket_->set_option(socket_base::reuse_address(true));
            socket_->bind(udp::endpoint(udp::v6(), port));
        }
    }

    void operator()(error_code ec = error_code(), size_t length = 0) {
        reenter (this) for (;;) {
            // Instantiate the data buffer that will be used by the
            // asynchronous read calls.
            // data_.reset(new boost::array<char, MAX_LENGTH>);
            data_ = boost::shared_ptr<char>(new char[MAX_LENGTH]);
            sender_.reset(new udp::endpoint());
            yield socket_->async_receive_from(asio::buffer(data_.get(),
                                                           MAX_LENGTH),
                                              *sender_, *this);
            if (ec || length == 0) {
                yield continue;
            }

            bytes_ = length;
            fork UDPServer(*this)();
            if (is_child()) {
                // Perform any necessary operations prior to processing
                // an incoming packet (e.g., checking for queued
                // configuration messages).
                if (checkin_callback_ != NULL) {
                    (*checkin_callback_)();
                }

                // Stop here if we don't have a DNS callback function
                if (dns_callback_ == NULL) {
                    yield return;
                }
    
                // Instantiate the objects that will be used by the
                // asynchronous write calls.
                dns_message_.reset(new Message(Message::PARSE));
                response_.reset(new OutputBuffer(0));
                renderer_.reset(new MessageRenderer(*response_));
                io_socket_.reset(new UDPSocket(*socket_));
                io_endpoint_.reset(new UDPEndpoint(*sender_));
                io_message_.reset(new IOMessage(data_.get(), bytes_,
                                                *io_socket_,
                                                *io_endpoint_));

                // Process the DNS message
                if (! (*dns_callback_)(*io_message_, *dns_message_, *renderer_))
                {
                    yield return;
                }

                yield socket_->async_send_to(asio::buffer(response_->getData(),
                                                        response_->getLength()),
                                             *sender_, *this);
            }
        }
    }

private:
    enum { MAX_LENGTH = 4096 };

    boost::shared_ptr<udp::socket> socket_;
    boost::shared_ptr<udp::endpoint> sender_;
    boost::shared_ptr<UDPEndpoint> io_endpoint_;
    boost::shared_ptr<OutputBuffer> response_;
    boost::shared_ptr<MessageRenderer> renderer_;
    boost::shared_ptr<Message> dns_message_;
    boost::shared_ptr<IOMessage> io_message_;
    boost::shared_ptr<UDPSocket> io_socket_;
    boost::shared_ptr<char> data_;
    size_t bytes_;

    // Callbacks
    const CheckinProvider* checkin_callback_;
    const DNSProvider* dns_callback_;
};

class IOServiceImpl {
public:
    IOServiceImpl(const char& port,
                  const ip::address* v4addr, const ip::address* v6addr,
                  CheckinProvider* checkin, DNSProvider* process);
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
                             CheckinProvider* checkin, DNSProvider* process) :
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
                                                      checkin, process));
            (*udp4_server_)();
            tcp4_server_ = TCPServerPtr(new TCPServer(io_service_,
                                                      *v4addr, portnum,
                                                      checkin, process));
            (*tcp4_server_)();
        }
        if (v6addr != NULL) {
            udp6_server_ = UDPServerPtr(new UDPServer(io_service_,
                                                      *v6addr, portnum,
                                                      checkin, process));
            (*udp6_server_)();
            tcp6_server_ = TCPServerPtr(new TCPServer(io_service_,
                                                      *v6addr, portnum,
                                                      checkin, process));
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
                     CheckinProvider* checkin, DNSProvider* process) :
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
                              checkin, process);
}

IOService::IOService(const char& port,
                     const bool use_ipv4, const bool use_ipv6,
                     CheckinProvider* checkin, DNSProvider* process) :
    impl_(NULL)
{
    const ip::address v4addr_any = ip::address(ip::address_v4::any());
    const ip::address* const v4addrp = use_ipv4 ? &v4addr_any : NULL; 
    const ip::address v6addr_any = ip::address(ip::address_v6::any());
    const ip::address* const v6addrp = use_ipv6 ? &v6addr_any : NULL;
    impl_ = new IOServiceImpl(port, v4addrp, v6addrp,
                              checkin, process);
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
