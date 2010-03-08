// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <stdlib.h>

#include <set>
#include <iostream>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/rrset.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include "common.h"
#include "config.h"
#include "auth_srv.h"

#include <boost/foreach.hpp>

using namespace std;

using namespace boost::asio;
using ip::udp;
using ip::tcp;

using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::dns;

namespace {
const string PROGRAM = "Auth";
const short DNSPORT = 5300;
}

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the authserver
 * class itself? */
namespace {
AuthSrv *auth_server;
}

//
// Helper classes for asynchronous I/O using boost::asio
//
namespace {
class Completed {
public:
    Completed(size_t len) : len_(len) {}
    bool operator()(const boost::system::error_code& error,
                    size_t bytes_transferred) const
    {
        return (error != 0 || bytes_transferred >= len_);
    }
private:
    size_t len_;
};

class TCPClient {
public:
    TCPClient(io_service& io_service) :
        socket_(io_service),
        response_buffer_(0),
        responselen_buffer_(TCP_MESSAGE_LENGTHSIZE),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE)
    {}

    void start() {
        async_read(socket_, boost::asio::buffer(data_, TCP_MESSAGE_LENGTHSIZE),
                   Completed(TCP_MESSAGE_LENGTHSIZE),
                   boost::bind(&TCPClient::headerRead, this,
                               placeholders::error,
                               placeholders::bytes_transferred));
    }

    tcp::socket& getSocket() { return (socket_); }

    void headerRead(const boost::system::error_code& error,
                    size_t bytes_transferred)
    {
        if (!error) {
            assert(bytes_transferred == TCP_MESSAGE_LENGTHSIZE);
            InputBuffer dnsbuffer(data_, TCP_MESSAGE_LENGTHSIZE);

            uint16_t msglen = dnsbuffer.readUint16();
            async_read(socket_, boost::asio::buffer(data_, msglen),
                       Completed(msglen),
                       boost::bind(&TCPClient::requestRead, this,
                                   placeholders::error,
                                   placeholders::bytes_transferred));
        } else {
            delete this;
        }
    }

    void requestRead(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error) {
            InputBuffer dnsbuffer(data_, bytes_transferred);
            if (auth_server->processMessage(dnsbuffer, dns_message_,
                                            response_renderer_, false) == 0) {
                responselen_buffer_.writeUint16(response_buffer_.getLength());
                async_write(socket_,
                            boost::asio::buffer(
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

    void responseWrite(const boost::system::error_code& error)
    {
        if (!error) {
                async_write(socket_,
                            boost::asio::buffer(response_buffer_.getData(),
                                                response_buffer_.getLength()),
                        boost::bind(&TCPClient::handleWrite, this,
                                    placeholders::error));
        }
    }

    void handleWrite(const boost::system::error_code& error)
    {
        if (!error) {
            start();            // handle next request, if any.
      } else {
            delete this;
      }
    }

private:
    tcp::socket socket_;
    OutputBuffer response_buffer_;
    OutputBuffer responselen_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    enum { MAX_LENGTH = 65535 };
    static const size_t TCP_MESSAGE_LENGTHSIZE = 2;
    char data_[MAX_LENGTH];
};

class TCPServer
{
public:
    TCPServer(io_service& io_service, int af, short port) :
        io_service_(io_service),
        acceptor_(io_service,
                  tcp::endpoint(af == AF_INET6 ? tcp::v6() : tcp::v4(), port))
    {
        TCPClient* new_client = new TCPClient(io_service_);
        // XXX: isn't the following exception free?  Need to check it.
        acceptor_.async_accept(new_client->getSocket(),
                               boost::bind(&TCPServer::handleAccept, this,
                                           new_client, placeholders::error));
    }

    void handleAccept(TCPClient* new_client,
                      const boost::system::error_code& error)
    {
        if (!error) {
            new_client->start();
            new_client = new TCPClient(io_service_);
            acceptor_.async_accept(new_client->getSocket(),
                                   boost::bind(&TCPServer::handleAccept,
                                               this, new_client,
                                               placeholders::error));
        } else {
            delete new_client;
        }
    }

private:
    io_service& io_service_;
    tcp::acceptor acceptor_;
};

class UDPServer {
public:
    UDPServer(io_service& io_service, int af, short port) :
        io_service_(io_service),
        socket_(io_service,
                udp::endpoint(af == AF_INET6 ? udp::v6() : udp::v4(), port)),
        response_buffer_(0),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE)
    {
        startReceive();
    }

    void handleRequest(const boost::system::error_code& error,
                       size_t bytes_recvd)
    {
        if (!error && bytes_recvd > 0) {
            InputBuffer request_buffer(data_, bytes_recvd);

            dns_message_.clear(Message::PARSE);
            response_renderer_.clear();
            if (auth_server->processMessage(request_buffer, dns_message_,
                                            response_renderer_, true) == 0) {
                socket_.async_send_to(
                    boost::asio::buffer(response_buffer_.getData(),
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

    void sendCompleted(const boost::system::error_code& error,
                       size_t bytes_sent)
    {
        startReceive();
    }
private:
    void startReceive() {
        socket_.async_receive_from(
            boost::asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::handleRequest, this,
                        placeholders::error,
                        placeholders::bytes_transferred));
    }

private:
    io_service& io_service_;
    udp::socket socket_;
    OutputBuffer response_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    udp::endpoint sender_endpoint_;
    enum { MAX_LENGTH = 4096 };
    char data_[MAX_LENGTH];
};
}

static void
usage() {
    cerr << "Usage: b10-auth [-p port] [-4|-6]" << endl;
    exit(1);
}

ElementPtr
my_config_handler(ElementPtr new_config)
{
    auth_server->updateConfig(new_config);
    return createAnswer(0);
}

ElementPtr
my_command_handler(const string& command, const ElementPtr args) {
    ElementPtr answer = createAnswer(0);

    cout << "[XX] Handle command: " << endl << command << endl;
    if (command == "print_message") 
    {
        cout << args << endl;
        /* let's add that message to our answer as well */
        answer->get("result")->add(args);
    }
    return answer;
}

int
main(int argc, char* argv[]) {
    int ch;
    short port = DNSPORT;
    bool ipv4_only = false, ipv6_only = false;
    bool use_ipv4 = false, use_ipv6 = false;
    UDPServer* udp4_server = NULL;
    UDPServer* udp6_server = NULL;
    TCPServer* tcp4_server = NULL;
    TCPServer* tcp6_server = NULL;

    while ((ch = getopt(argc, argv, "46p:")) != -1) {
        switch (ch) {
        case '4':
            ipv4_only = true;
            break;
        case '6':
            ipv6_only = true;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0) {
        usage();
    }

    if (ipv4_only && ipv6_only) {
        cerr << "-4 and -6 can't coexist" << endl;
        usage();
    }
    if (!ipv6_only) {
        use_ipv4 = true;
    }
    if (!ipv4_only) {
        use_ipv4 = true;
    }

    auth_server = new AuthSrv;

    // initialize command channel
    int ret = 0;
    try {
        string specfile;
        if (getenv("B10_FROM_SOURCE")) {
            specfile = string(getenv("B10_FROM_SOURCE")) +
                "/src/bin/auth/auth.spec";
        } else {
            specfile = string(AUTH_SPECFILE_LOCATION);
        }
        ModuleCCSession cs = ModuleCCSession(specfile, my_config_handler,
                                             my_command_handler);

        // XXX: in this prototype code we'll ignore any message on the command
        // channel.

        boost::asio::io_service io_service;
        if (use_ipv4) {
            udp4_server = new UDPServer(io_service, AF_INET, port);
            tcp4_server = new TCPServer(io_service, AF_INET, port);
        }
        if (use_ipv6) {
            udp6_server = new UDPServer(io_service, AF_INET6, port);
            tcp6_server = new TCPServer(io_service, AF_INET6, port);
        }

        cout << "Server started." << endl;
        io_service.run();
    } catch (const std::exception& ex) {
        cerr << ex.what() << endl;
        ret = 1;
    }

    delete udp4_server;
    delete tcp4_server;
    delete udp6_server;
    delete tcp6_server;

    delete auth_server;
    return (ret);
}
