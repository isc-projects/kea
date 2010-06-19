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

#include <asio.hpp>
#include <boost/bind.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#if defined(HAVE_BOOST_PYTHON)
#define USE_XFROUT
#include <xfr/xfrout_client.h>
#endif

#include <asio_link.h>

#include "spec_config.h"        // for XFROUT.  should not be here.
#include "auth_srv.h"

using namespace asio;
using ip::udp;
using ip::tcp;

using namespace std;
using namespace isc::dns;
#ifdef USE_XFROUT
using namespace isc::xfr;
#endif

namespace {
// As a short term workaround, we have XFROUT specific code.  We should soon
// refactor the code with some abstraction so that we can separate this level
// details from the (AS)IO module.
#ifdef USE_XFROUT
//TODO. The sample way for checking axfr query, the code should be merged to auth server class
bool
check_axfr_query(char* const msg_data, const uint16_t msg_len) {
    if (msg_len < 15) {
        return false;
    }

    const uint16_t query_type = *(uint16_t *)(msg_data + (msg_len - 4));
    if ( query_type == 0xFC00) {
        return true;
    }
    
    return false;
}

//TODO. Send the xfr query to xfrout module, the code should be merged to auth server class
void
dispatch_axfr_query(const int tcp_sock, char const axfr_query[],
                    const uint16_t query_len)
{
    string path;
    if (getenv("B10_FROM_BUILD")) {
        path = string(getenv("B10_FROM_BUILD")) + "/auth_xfrout_conn";
    } else {
        path = UNIX_SOCKET_FILE;
    }
    
    XfroutClient xfr_client(path);
    try {
        xfr_client.connect();
        xfr_client.sendXfroutRequestInfo(tcp_sock, (uint8_t *)axfr_query,
                                         query_len);
        xfr_client.disconnect();
    }
    catch (const exception & err) {
        //if (verbose_mode)
        cerr << "error handle xfr query:" << err.what() << endl;
    }
}
#endif
}

namespace asio_link {
IOAddress::IOAddress(const string& address_str) :
    // XXX: we cannot simply construct the address in the initialization list
    // because we'd like to throw our own exception on failure.
    asio_address_placeholder_(new ip::address()),
    asio_address_(*asio_address_placeholder_)
{
    error_code err;
    const ip::address address = ip::address::from_string(address_str, err);
    if (err) {
        delete asio_address_placeholder_;
        isc_throw(IOError, "Failed to convert string to address '"
                  << address_str << "': " << err.message());
    }
    *asio_address_placeholder_ = address;
}

IOAddress::IOAddress(const ip::address& asio_address) :
    asio_address_placeholder_(NULL), asio_address_(asio_address)
{}

IOAddress::~IOAddress() {
    delete asio_address_placeholder_;
}

string
IOAddress::toText() const {
    return (asio_address_.to_string());
}

//
// Helper classes for asynchronous I/O using asio
//
class TCPClient {
public:
    TCPClient(AuthSrv* auth_server, io_service& io_service) :
        auth_server_(auth_server),
        socket_(io_service),
        response_buffer_(0),
        responselen_buffer_(TCP_MESSAGE_LENGTHSIZE),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE)
    {}

    void start() {
        // Check for queued configuration commands
        if (auth_server_->configSession()->hasQueuedMsgs()) {
            auth_server_->configSession()->checkCommand();
        }
        async_read(socket_, asio::buffer(data_, TCP_MESSAGE_LENGTHSIZE),
                   boost::bind(&TCPClient::headerRead, this,
                               placeholders::error,
                               placeholders::bytes_transferred));
    }

    tcp::socket& getSocket() { return (socket_); }

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
            InputBuffer dnsbuffer(data_, bytes_transferred);
#ifdef USE_XFROUT
            if (check_axfr_query(data_, bytes_transferred)) {
                dispatch_axfr_query(socket_.native(), data_, bytes_transferred); 
                // start to get new query ?
                start();
            } else {
#endif
#ifdef notyet
                IOMessage io_message(data_, bytes_transferred,
                                     remote_endpoint, socket);
                if (auth_server_->processMessage(IOMessage(message), ..)) {
                    //...
                    message.getIOService().
                }
#endif
                if (auth_server_->processMessage(dnsbuffer, dns_message_,
                                                response_renderer_, false)) {
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
#ifdef USE_XFROUT
            }
#endif
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

private:
    AuthSrv* auth_server_;
    tcp::socket socket_;
    OutputBuffer response_buffer_;
    OutputBuffer responselen_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    enum { MAX_LENGTH = 65535 };
    static const size_t TCP_MESSAGE_LENGTHSIZE = 2;
    char data_[MAX_LENGTH];
};

class TCPServer {
public:
    TCPServer(AuthSrv* auth_server, io_service& io_service,
              int af, short port) :
        auth_server_(auth_server), io_service_(io_service),
        acceptor_(io_service_), listening_(new TCPClient(auth_server_,
                                                         io_service_))
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

private:
    AuthSrv* auth_server_;
    io_service& io_service_;
    tcp::acceptor acceptor_;
    TCPClient* listening_;
};

class UDPServer {
public:
    UDPServer(AuthSrv* auth_server, io_service& io_service,
              int af, short port) :
        auth_server_(auth_server),
        io_service_(io_service),
        socket_(io_service, af == AF_INET6 ? udp::v6() : udp::v4()),
        response_buffer_(0),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE)
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
        if (auth_server_->configSession()->hasQueuedMsgs()) {
            auth_server_->configSession()->checkCommand();
        }
        if (!error && bytes_recvd > 0) {
            InputBuffer request_buffer(data_, bytes_recvd);

            dns_message_.clear(Message::PARSE);
            response_renderer_.clear();
            if (auth_server_->processMessage(request_buffer, dns_message_,
                                            response_renderer_, true)) {
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
    OutputBuffer response_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    udp::endpoint sender_endpoint_;
    enum { MAX_LENGTH = 4096 };
    char data_[MAX_LENGTH];
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
        servers.tcp4_server = new TCPServer(auth_server, io_service_,
                                            AF_INET, portnum);
    }
    if (use_ipv6) {
        servers.udp6_server = new UDPServer(auth_server, io_service_,
                                            AF_INET6, portnum);
        servers.tcp6_server = new TCPServer(auth_server, io_service_,
                                            AF_INET6, portnum);
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
}
