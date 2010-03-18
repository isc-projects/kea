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

#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <cassert>
#include <iostream>

#include <boost/foreach.hpp>
#ifdef HAVE_BOOSTLIB
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#endif  // HAVE_BOOSTLIB

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include "spec_config.h"
#include "common.h"
#include "auth_srv.h"

using namespace std;

#ifdef HAVE_BOOSTLIB
using namespace boost::asio;
using ip::udp;
using ip::tcp;
#endif  // HAVE_BOOSTLIB

using namespace isc::data;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::dns;

namespace {

bool verbose_mode = false;

const string PROGRAM = "Auth";
const char* DNSPORT = "5300";

/* need global var for config/command handlers.
 * todo: turn this around, and put handlers in the authserver
 * class itself? */
AuthSrv *auth_server;
#ifdef HAVE_BOOSTLIB
// TODO: this should be a property of AuthSrv, and AuthSrv needs
// a stop() method (so the shutdown command can be handled)
boost::asio::io_service io_service_;
#else
bool running;
#endif  // HAVE_BOOSTLIB

ElementPtr
my_config_handler(ElementPtr new_config) {
    return auth_server->updateConfig(new_config);
}

ElementPtr
my_command_handler(const string& command, const ElementPtr args) {
    ElementPtr answer = createAnswer();

    if (command == "print_message") {
        cout << args << endl;
        /* let's add that message to our answer as well */
        answer->get("result")->add(args);
    } else if (command == "shutdown") {
#ifdef HAVE_BOOSTLIB
        io_service_.stop();
#else
        running = false;
#endif  // HAVE_BOOSTLIB
    }
    
    return answer;
}

#ifdef HAVE_BOOSTLIB
//
// Helper classes for asynchronous I/O using boost::asio
//
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
                   boost::bind(&TCPClient::headerRead, this,
                               placeholders::error,
                               placeholders::bytes_transferred));
    }

    tcp::socket& getSocket() { return (socket_); }

    void headerRead(const boost::system::error_code& error,
                    size_t bytes_transferred)
    {
        if (!error) {
            InputBuffer dnsbuffer(data_, bytes_transferred);

            uint16_t msglen = dnsbuffer.readUint16();
            async_read(socket_, boost::asio::buffer(data_, msglen),

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
                                            response_renderer_, false)) {
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

    void responseWrite(const boost::system::error_code& error) {
        if (!error) {
                async_write(socket_,
                            boost::asio::buffer(response_buffer_.getData(),
                                                response_buffer_.getLength()),
                        boost::bind(&TCPClient::handleWrite, this,
                                    placeholders::error));
        } else {
            delete this;
        }
    }

    void handleWrite(const boost::system::error_code& error) {
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

class TCPServer {
public:
    TCPServer(io_service& io_service, int af, short port) :
        io_service_(io_service), acceptor_(io_service_),
        listening_(new TCPClient(io_service_))
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
                      const boost::system::error_code& error)
    {
        if (!error) {
            assert(new_client == listening_);
            new_client->start();
            listening_ = new TCPClient(io_service_);
            acceptor_.async_accept(listening_->getSocket(),
                                   boost::bind(&TCPServer::handleAccept,
                                               this, listening_,
                                               placeholders::error));
        } else {
            delete new_client;
        }
    }

private:
    io_service& io_service_;
    tcp::acceptor acceptor_;
    TCPClient* listening_;
};

class UDPServer {
public:
    UDPServer(io_service& io_service, int af, short port) :
        io_service_(io_service),
        socket_(io_service, af == AF_INET6 ? udp::v6() : udp::v4()),
        response_buffer_(0),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE)
    {
        // Set v6-only (we use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (af == AF_INET6) {
            socket_.set_option(boost::asio::ip::v6_only(true));
            socket_.bind(udp::endpoint(udp::v6(), port));
        } else {
            socket_.bind(udp::endpoint(udp::v4(), port));
        }
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
                                            response_renderer_, true)) {
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

    void sendCompleted(const boost::system::error_code& error UNUSED_PARAM,
                       size_t bytes_sent UNUSED_PARAM)
    {
        // Even if error occurred there's nothing to do.  Simply handle
        // the next request.
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

void
run_server(const char* port, const bool use_ipv4, const bool use_ipv6,
           AuthSrv* srv UNUSED_PARAM)
{
    ServerSet servers;
    short portnum = atoi(port);

    if (use_ipv4) {
        servers.udp4_server = new UDPServer(io_service_, AF_INET, portnum);
        servers.tcp4_server = new TCPServer(io_service_, AF_INET, portnum);
    }
    if (use_ipv6) {
        servers.udp6_server = new UDPServer(io_service_, AF_INET6, portnum);
        servers.tcp6_server = new TCPServer(io_service_, AF_INET6, portnum);
    }

    cout << "Server started." << endl;
    io_service_.run();
}
#else  // !HAVE_BOOSTLIB
struct SocketSet {
    SocketSet() : ups4(-1), tps4(-1), ups6(-1), tps6(-1) {}
    ~SocketSet() {
        if (ups4 >= 0) {
            close(ups4);
        }
        if (tps4 >= 0) {
            close(tps4);
        }
        if (ups6 >= 0) {
            close(ups6);
        }
        if (tps4 >= 0) {
            close(tps6);
        }
    }
    int ups4, tps4, ups6, tps6;
};

int
getUDPSocket(int af, const char* port) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = af;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_UDP;

    int error = getaddrinfo(NULL, port, &hints, &res);
    if (error != 0) {
        isc_throw(FatalError, "getaddrinfo failed: " << gai_strerror(error));
    }

    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (s < 0) {
        isc_throw(FatalError, "failed to open socket");
    }

    if (af == AF_INET6) {
        int on = 1;
        if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)) < 0) {
            cerr << "couldn't set IPV6_V6ONLY socket option" << endl;
            // proceed anyway
        }
    }

    if (bind(s, res->ai_addr, res->ai_addrlen) < 0) {
        isc_throw(FatalError, "binding socket failure");
    }

    return (s);
}

int
getTCPSocket(int af, const char* port) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = af;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_TCP;

    int error = getaddrinfo(NULL, port, &hints, &res);
    if (error != 0) {
        isc_throw(FatalError, "getaddrinfo failed: " << gai_strerror(error));
    }

    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (s < 0) {
        isc_throw(FatalError, "failed to open socket");
    }

    int on = 1;
    if (af == AF_INET6) {
        if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)) < 0) {
            cerr << "couldn't set IPV6_V6ONLY socket option" << endl;
        }
        // proceed anyway
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        cerr << "couldn't set SO_REUSEADDR socket option" << endl;
    }

    if (bind(s, res->ai_addr, res->ai_addrlen) < 0) {
        isc_throw(FatalError, "binding socket failure");
    }

    if (listen(s, 100) < 0) {
        isc_throw(FatalError, "failed to listen on a TCP socket");
    }
    return (s);
}

void
processMessageUDP(const int fd, Message& dns_message,
                  MessageRenderer& response_renderer)
{
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    char recvbuf[4096];
    int cc;

    dns_message.clear(Message::PARSE);
    response_renderer.clear();
    if ((cc = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, sa, &sa_len)) > 0) {
        InputBuffer buffer(recvbuf, cc);
        if (auth_server->processMessage(buffer, dns_message, response_renderer,
                                        true)) {
            cc = sendto(fd, response_renderer.getData(),
                        response_renderer.getLength(), 0, sa, sa_len);
            if (cc != response_renderer.getLength()) {
                cerr << "UDP send error" << endl;
            }
        }
    } else if (verbose_mode) {
        cerr << "UDP receive error" << endl;
    }
}

// XXX: this function does not handle partial reads or partial writes,
//      and is VERY UNSAFE - will probably be removed or rewritten
void
processMessageTCP(const int fd, Message& dns_message,
                  MessageRenderer& response_renderer)
{
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    char sizebuf[2];
    int cc;

    int ts = accept(fd, sa, &sa_len);
    if (ts < 0) {
        if (verbose_mode) {
            cerr << "[XX] TCP accept failure:" << endl;
            return;
        }
    }

    if (verbose_mode) {
        cerr << "[XX] process TCP" << endl;
    }
    cc = recv(ts, sizebuf, 2, 0);
    if (cc < 0) {
        if (verbose_mode) {
            cerr << "[XX] TCP recv failure:" << endl;
        }
        close(ts);
        return;
    }
    if (verbose_mode) {
        cerr << "[XX] got: " << cc << endl;
    }
    uint16_t size, size_n;
    memcpy(&size_n, sizebuf, 2);
    size = ntohs(size_n);
    if (verbose_mode) {
        cerr << "[XX] got: " << size << endl;
    }

    vector<char> message_buffer;
    message_buffer.reserve(size);
    cc = 0;
    while (cc < size) {
        if (verbose_mode) {
            cerr << "[XX] cc now: " << cc << " of " << size << endl;
        }
        const int cc0 = recv(ts, &message_buffer[0] + cc, size - cc, 0);
        if (cc0 < 0) {
            if (verbose_mode) {
                cerr << "TCP receive error" << endl;
                close(ts);
                return;
            }
        }
        if (cc0 == 0) {
            // client closed connection
            close(ts);
            return;
        }
        cc += cc0;
    }

    InputBuffer buffer(&message_buffer[0], size);
    dns_message.clear(Message::PARSE);
    response_renderer.clear();
    if (auth_server->processMessage(buffer, dns_message, response_renderer,
                                    false)) {
        size = response_renderer.getLength();
        size_n = htons(size);
        if (send(ts, &size_n, 2, 0) == 2) {
            cc = send(ts, response_renderer.getData(),
                      response_renderer.getLength(), 0);
            if (cc == -1) {
                if (verbose_mode) {
                    cerr << "[AuthSrv] error in sending TCP response message" <<
                        endl;
                }
            } else {
                if (verbose_mode) {
                    cerr << "[XX] sent TCP response: " << cc << " bytes"
                         << endl;
                }
            }
        } else {
            if (verbose_mode) {
                cerr << "TCP send error" << endl;
            }
        }
    }
 
   // TODO: we don't check for more queries on the stream atm
    close(ts);
}

void
run_server(const char* port, const bool use_ipv4, const bool use_ipv6,
           AuthSrv* srv)
{
    SocketSet socket_set;
    fd_set fds_base;
    int nfds = -1;

    FD_ZERO(&fds_base);
    if (use_ipv4) {
        socket_set.ups4 = getUDPSocket(AF_INET, port);
        FD_SET(socket_set.ups4, &fds_base);
        nfds = max(nfds, socket_set.ups4);
        socket_set.tps4 = getTCPSocket(AF_INET, port);
        FD_SET(socket_set.tps4, &fds_base);
        nfds = max(nfds, socket_set.tps4);
    }
    if (use_ipv6) {
        socket_set.ups6 = getUDPSocket(AF_INET6, port);
        FD_SET(socket_set.ups6, &fds_base);
        nfds = max(nfds, socket_set.ups6);
        socket_set.tps6 = getTCPSocket(AF_INET6, port);
        FD_SET(socket_set.tps6, &fds_base);
        nfds = max(nfds, socket_set.tps6);
    }
    ++nfds;

    cout << "Server started." << endl;
    
    if (srv->configSession() == NULL) {
        isc_throw(FatalError, "Config session not initalized");
    }

    int ss = srv->configSession()->getSocket();
    Message dns_message(Message::PARSE);
    OutputBuffer resonse_buffer(0);
    MessageRenderer response_renderer(resonse_buffer);

    running = true;
    while (running) {
        fd_set fds = fds_base;
        FD_SET(ss, &fds);
        ++nfds;

        int n = select(nfds, &fds, NULL, NULL, NULL);
        if (n < 0) {
            if (errno != EINTR) {
                isc_throw(FatalError, "select error");
            }
            continue;
        }

        if (socket_set.ups4 >= 0 && FD_ISSET(socket_set.ups4, &fds)) {
            processMessageUDP(socket_set.ups4, dns_message, response_renderer);
        }
        if (socket_set.ups6 >= 0 && FD_ISSET(socket_set.ups6, &fds)) {
            processMessageUDP(socket_set.ups6, dns_message, response_renderer);
        }
        if (socket_set.tps4 >= 0 && FD_ISSET(socket_set.tps4, &fds)) {
            processMessageTCP(socket_set.tps4, dns_message, response_renderer);
        }
        if (socket_set.tps6 >= 0 && FD_ISSET(socket_set.tps6, &fds)) {
            processMessageTCP(socket_set.tps6, dns_message, response_renderer);
        }
        if (FD_ISSET(ss, &fds)) {
            srv->configSession()->checkCommand();
        }
    }
}
#endif // HAVE_BOOSTLIB

void
usage() {
    cerr << "Usage: b10-auth [-p port] [-4|-6]" << endl;
    exit(1);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    int ch;
    const char* port = DNSPORT;
    bool use_ipv4 = true, use_ipv6 = true;

    while ((ch = getopt(argc, argv, "46p:v")) != -1) {
        switch (ch) {
        case '4':
            // Note that -4 means "ipv4 only", we need to set "use_ipv6" here,
            // not "use_ipv4".  We could use something like "ipv4_only", but
            // we found the negatively named variable could confuse the code
            // logic.
            use_ipv6 = false;
            break;
        case '6':
            // The same note as -4 applies.
            use_ipv4 = false;
            break;
        case 'p':
            port = optarg;
            break;
        case 'v':
            verbose_mode = true;
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0) {
        usage();
    }

    if (!use_ipv4 && !use_ipv6) {
        cerr << "-4 and -6 can't coexist" << endl;
        usage();
    }

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

        auth_server = new AuthSrv;
        auth_server->setVerbose(verbose_mode);

#ifdef HAVE_BOOSTLIB
        ModuleCCSession cs(specfile, io_service_, my_config_handler,
                           my_command_handler);
#else
        ModuleCCSession cs(specfile, my_config_handler, my_command_handler);
#endif

        auth_server->setConfigSession(&cs);
        auth_server->updateConfig(ElementPtr());

        run_server(port, use_ipv4, use_ipv6, auth_server);
    } catch (const std::exception& ex) {
        cerr << ex.what() << endl;
        ret = 1;
    }

    delete auth_server;
    return (ret);
}
