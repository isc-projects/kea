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

#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>
#include <boost/bind.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asio_link.h>

#include <auth/auth_srv.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asio_link {
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
// Helper classes for asynchronous I/O using asio
//
class TCPClient {
public:
    TCPClient(AuthSrv* auth_server, io_service& io_service) :
        auth_server_(auth_server),
        socket_(io_service),
        io_socket_(socket_),
        response_buffer_(0),
        responselen_buffer_(TCP_MESSAGE_LENGTHSIZE),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE),
        custom_callback_(NULL)
    {}

    void start() {
        // Check for queued configuration commands
        if (auth_server_ != NULL &&
            auth_server_->configSession()->hasQueuedMsgs()) {
            auth_server_->configSession()->checkCommand();
        }
        async_read(socket_, asio::buffer(data_, TCP_MESSAGE_LENGTHSIZE),
                   boost::bind(&TCPClient::headerRead, this,
                               placeholders::error,
                               placeholders::bytes_transferred));
    }

    ip::tcp::socket& getSocket() { return (socket_); }

    void headerRead(const asio::error_code& error,
                    size_t bytes_transferred)
    {
        if (!error) {
            InputBuffer dnsbuffer(data_, bytes_transferred);

            uint16_t msglen = dnsbuffer.readUint16();
            async_read(socket_, asio::buffer(data_, msglen),
                       boost::bind(&TCPClient::requestRead, this,
                                   placeholders::error,
                                   placeholders::bytes_transferred));
        } else {
            delete this;
        }
    }

    void requestRead(const asio::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error) {
            const TCPEndpoint remote_endpoint(socket_.remote_endpoint());
            const IOMessage io_message(data_, bytes_transferred, io_socket_,
                                       remote_endpoint);
            // currently, for testing purpose only
            if (custom_callback_ != NULL) {
                (*custom_callback_)(io_message);
                start();
                return;
            }

            if (auth_server_->processMessage(io_message, dns_message_,
                                             response_renderer_)) {
                responselen_buffer_.writeUint16(
                    response_buffer_.getLength());
                async_write(socket_,
                            asio::buffer(
                                responselen_buffer_.getData(),
                                responselen_buffer_.getLength()),
                            boost::bind(&TCPClient::responseWrite, this,
                                        placeholders::error));
            } else {
                delete this;
            }
        } else {
            delete this;
        }
    }

    void responseWrite(const asio::error_code& error) {
        if (!error) {
                async_write(socket_,
                            asio::buffer(response_buffer_.getData(),
                                         response_buffer_.getLength()),
                            boost::bind(&TCPClient::handleWrite, this,
                                        placeholders::error));
        } else {
            delete this;
        }
    }

    void handleWrite(const asio::error_code& error) {
        if (!error) {
            start();            // handle next request, if any.
      } else {
            delete this;
      }
    }

    // Currently this is for tests only
    void setCallBack(const IOService::IOCallBack* callback) {
        custom_callback_ = callback;
    }

private:
    AuthSrv* auth_server_;
    tcp::socket socket_;
    TCPSocket io_socket_;
    OutputBuffer response_buffer_;
    OutputBuffer responselen_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    enum { MAX_LENGTH = 65535 };
    static const size_t TCP_MESSAGE_LENGTHSIZE = 2;
    char data_[MAX_LENGTH];

    // currently, for testing purpose only.
    const IOService::IOCallBack* custom_callback_;
};

class TCPServer {
public:
    TCPServer(AuthSrv* auth_server, io_service& io_service,
              int af, short port) :
        auth_server_(auth_server), io_service_(io_service),
        acceptor_(io_service_), listening_(new TCPClient(auth_server_,
                                                         io_service_)),
        custom_callback_(NULL)
    {
        tcp::endpoint endpoint(af == AF_INET6 ? tcp::v6() : tcp::v4(), port);
        acceptor_.open(endpoint.protocol());
        // Set v6-only (we use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (af == AF_INET6) {
            acceptor_.set_option(ip::v6_only(true));
        }
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();
        acceptor_.async_accept(listening_->getSocket(),
                               boost::bind(&TCPServer::handleAccept, this,
                                           listening_, placeholders::error));
    }

    ~TCPServer() { delete listening_; }

    void handleAccept(TCPClient* new_client,
                      const asio::error_code& error)
    {
        if (!error) {
            assert(new_client == listening_);
            new_client->setCallBack(custom_callback_);
            new_client->start();
            listening_ = new TCPClient(auth_server_, io_service_);
            acceptor_.async_accept(listening_->getSocket(),
                                   boost::bind(&TCPServer::handleAccept,
                                               this, listening_,
                                               placeholders::error));
        } else {
            delete new_client;
        }
    }

    // Currently this is for tests only
    void setCallBack(const IOService::IOCallBack* callback) {
        custom_callback_ = callback;
    }

private:
    AuthSrv* auth_server_;
    io_service& io_service_;
    tcp::acceptor acceptor_;
    TCPClient* listening_;

    // currently, for testing purpose only.
    const IOService::IOCallBack* custom_callback_;
};

class UDPServer {
public:
    UDPServer(AuthSrv* auth_server, io_service& io_service,
              int af, short port) :
        auth_server_(auth_server),
        io_service_(io_service),
        socket_(io_service, af == AF_INET6 ? udp::v6() : udp::v4()),
        io_socket_(socket_),
        response_buffer_(0),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE),
        custom_callback_(NULL)
    {
        // Set v6-only (we use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (af == AF_INET6) {
            socket_.set_option(asio::ip::v6_only(true));
            socket_.bind(udp::endpoint(udp::v6(), port));
        } else {
            socket_.bind(udp::endpoint(udp::v4(), port));
        }
        startReceive();
    }

    void handleRequest(const asio::error_code& error,
                       size_t bytes_recvd)
    {
        // Check for queued configuration commands
        if (auth_server_ != NULL &&
            auth_server_->configSession()->hasQueuedMsgs()) {
            auth_server_->configSession()->checkCommand();
        }
        if (!error && bytes_recvd > 0) {
            const UDPEndpoint remote_endpoint(sender_endpoint_);
            const IOMessage io_message(data_, bytes_recvd, io_socket_,
                                       remote_endpoint);
            // currently, for testing purpose only
            if (custom_callback_ != NULL) {
                (*custom_callback_)(io_message);
                startReceive();
                return;
            }

            dns_message_.clear(Message::PARSE);
            response_renderer_.clear();
            if (auth_server_->processMessage(io_message, dns_message_,
                                             response_renderer_)) {
                socket_.async_send_to(
                    asio::buffer(response_buffer_.getData(),
                                        response_buffer_.getLength()),
                    sender_endpoint_,
                    boost::bind(&UDPServer::sendCompleted,
                                this,
                                placeholders::error,
                                placeholders::bytes_transferred));
            } else {
                startReceive();
            }
        } else {
            startReceive();
        }
    }

    void sendCompleted(const asio::error_code& error UNUSED_PARAM,
                       size_t bytes_sent UNUSED_PARAM)
    {
        // Even if error occurred there's nothing to do.  Simply handle
        // the next request.
        startReceive();
    }

    // Currently this is for tests only
    void setCallBack(const IOService::IOCallBack* callback) {
        custom_callback_ = callback;
    }
private:
    void startReceive() {
        socket_.async_receive_from(
            asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::handleRequest, this,
                        placeholders::error,
                        placeholders::bytes_transferred));
    }

private:
    AuthSrv* auth_server_;
    io_service& io_service_;
    udp::socket socket_;
    UDPSocket io_socket_;
    OutputBuffer response_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    udp::endpoint sender_endpoint_;
    enum { MAX_LENGTH = 4096 };
    char data_[MAX_LENGTH];

    // currently, for testing purpose only.
    const IOService::IOCallBack* custom_callback_;
};

// This is a helper structure just to make the construction of IOServiceImpl
// exception safe.  If the constructor of {UDP/TCP}Server throws an exception,
// the destructor of this class will automatically perform the necessary
// cleanup.
struct ServerSet {
    ServerSet() : udp4_server(NULL), udp6_server(NULL),
                  tcp4_server(NULL), tcp6_server(NULL)
    {}
    ~ServerSet() {
        delete udp4_server;
        delete udp6_server;
        delete tcp4_server;
        delete tcp6_server;
    }
    UDPServer* udp4_server;
    UDPServer* udp6_server;
    TCPServer* tcp4_server;
    TCPServer* tcp6_server;
};

class IOServiceImpl {
public:
    IOServiceImpl(AuthSrv* auth_server, const char* port,
                  const bool use_ipv4, const bool use_ipv6);
    ~IOServiceImpl();
    asio::io_service io_service_;
    AuthSrv* auth_server_;
    UDPServer* udp4_server_;
    UDPServer* udp6_server_;
    TCPServer* tcp4_server_;
    TCPServer* tcp6_server_;

    // This member is used only for testing at the moment.
    IOService::IOCallBack callback_;
};

IOServiceImpl::IOServiceImpl(AuthSrv* auth_server, const char* const port,
                             const bool use_ipv4, const bool use_ipv6) :
    auth_server_(auth_server), udp4_server_(NULL), udp6_server_(NULL),
    tcp4_server_(NULL), tcp6_server_(NULL)
{
    ServerSet servers;
    short portnum = atoi(port);

    if (use_ipv4) {
        servers.udp4_server = new UDPServer(auth_server, io_service_,
                                            AF_INET, portnum);
        udp4_server_ = servers.udp4_server;
        servers.tcp4_server = new TCPServer(auth_server, io_service_,
                                            AF_INET, portnum);
        tcp4_server_ = servers.tcp4_server;
    }
    if (use_ipv6) {
        servers.udp6_server = new UDPServer(auth_server, io_service_,
                                            AF_INET6, portnum);
        udp6_server_ = servers.udp6_server;
        servers.tcp6_server = new TCPServer(auth_server, io_service_,
                                            AF_INET6, portnum);
        tcp6_server_ = servers.tcp6_server;
    }

    // Now we don't have to worry about exception, and need to make sure that
    // the server objects won't be accidentally cleaned up.
    servers.udp4_server = NULL;
    servers.udp6_server = NULL;
    servers.tcp4_server = NULL;
    servers.tcp6_server = NULL;
}

IOServiceImpl::~IOServiceImpl() {
    delete udp4_server_;
    delete udp6_server_;
    delete tcp4_server_;
    delete tcp6_server_;
}

IOService::IOService(AuthSrv* auth_server, const char* const port,
                     const bool use_ipv4, const bool use_ipv6) {
    impl_ = new IOServiceImpl(auth_server, port, use_ipv4, use_ipv6);
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
    return impl_->io_service_;
}

void
IOService::setCallBack(const IOCallBack callback) {
    impl_->callback_ = callback;
    if (impl_->udp4_server_ != NULL) {
        impl_->udp4_server_->setCallBack(&impl_->callback_);
    }
    if (impl_->udp6_server_ != NULL) {
        impl_->udp6_server_->setCallBack(&impl_->callback_);
    }
    if (impl_->tcp4_server_ != NULL) {
        impl_->tcp4_server_->setCallBack(&impl_->callback_);
    }
    if (impl_->tcp6_server_ != NULL) {
        impl_->tcp6_server_->setCallBack(&impl_->callback_);
    }
}
}
