// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <gtest/gtest.h>
#include <util/unittests/test_exceptions.h>

#include <asio.hpp>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_error.h>
#include <asiodns/udp_server.h>
#include <asiodns/sync_udp_server.h>
#include <asiodns/tcp_server.h>
#include <asiodns/dns_answer.h>
#include <asiodns/dns_lookup.h>
#include <string>
#include <cstring>
#include <cerrno>
#include <csignal>
#include <unistd.h> //for alarm

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <sys/types.h>
#include <sys/socket.h>

/// The following tests focus on stop interface for udp and
/// tcp server, there are lots of things can be shared to test
/// both tcp and udp server, so they are in the same unittest

/// The general work flow for dns server, is that wait for user
/// query, once get one query, we will check the data is valid or
/// not, if it passed, we will try to loop up the question, then
/// compose the answer and finally send it back to user. The server
/// may be stopped at any point during this porcess, so the test strategy
/// is that we define 5 stop point and stop the server at these
/// 5 points, to check whether stop is successful
/// The 5 test points are :
///   Before the server start to run
///   After we get the query and check whether it's valid
///   After we lookup the query
///   After we compose the answer
///   After user gets the final result.

/// The standard about whether we stop the server successfully or not
/// is based on the fact that if the server is still running, the io
/// service won't quit since it will wait for some asynchronized event for
/// server. So if the io service block function run returns we assume
/// that the server is stopped. To avoid stop interface failure which
/// will block followed tests, using alarm signal to stop the blocking
/// io service
///
/// The whole test context including one server and one client, and
/// five stop checkpoints, we call them ServerStopper exclude the first
/// stop point. Once the unittest fired, the client will send message
/// to server, and the stopper may stop the server at the checkpoint, then
/// we check the client get feedback or not. Since there is no DNS logic
/// involved so the message sending between client and server is plain text
/// And the valid checker, question lookup and answer composition are dummy.

using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace asio;

namespace {
const char* const server_ip = "::1";
const int server_port = 5553;
const char* const server_port_str = "5553";
//message client send to udp server, which isn't dns package
//just for simple testing
const char* const query_message = "Kea is awesome";

// \brief provide capacity to derived class the ability
// to stop DNSServer at certain point
class ServerStopper {
    public:
        ServerStopper() : server_to_stop_(NULL) {}
        virtual ~ServerStopper(){}

        void setServerToStop(DNSServer& server) {
            server_to_stop_ = &server;
        }

        void stopServer() const {
            if (server_to_stop_) {
                server_to_stop_->stop();
            }
        }

    private:
        DNSServer* server_to_stop_;
};

// \brief no lookup logic at all,just provide a checkpoint to stop the server
class DummyLookup : public DNSLookup, public ServerStopper {
public:
    DummyLookup() :
        allow_resume_(true)
    { }
    virtual void operator()(const IOMessage& io_message,
            isc::dns::MessagePtr message,
            isc::dns::MessagePtr answer_message,
            isc::util::OutputBufferPtr buffer,
            DNSServer* server) const {
        stopServer();
        if (allow_resume_) {
            server->resume(true);
        }
    }
    // If you want it not to call resume, set this to false
    bool allow_resume_;
};

// \brief copy the data received from user to the answer part
//  provide checkpoint to stop server
class SimpleAnswer : public DNSAnswer, public ServerStopper {
    public:
        void operator()(const IOMessage& message,
                isc::dns::MessagePtr query_message,
                isc::dns::MessagePtr answer_message,
                isc::util::OutputBufferPtr buffer) const
        {
            //copy what we get from user
            buffer->writeData(message.getData(), message.getDataSize());
            stopServer();
        }

};

/// \brief Mixture of DummyLookup and SimpleAnswer: build the answer in the
/// lookup callback.  Used with SyncUDPServer.
class SyncDummyLookup : public DummyLookup {
public:
    virtual void operator()(const IOMessage& io_message,
                            isc::dns::MessagePtr message,
                            isc::dns::MessagePtr answer_message,
                            isc::util::OutputBufferPtr buffer,
                            DNSServer* server) const
    {
        buffer->writeData(io_message.getData(), io_message.getDataSize());
        stopServer();
        if (allow_resume_) {
            server->resume(true);
        }
    }
};

// \brief simple client, send one string to server and wait for response
//  in case, server stopped and client can't get response, there is a timer wait
//  for specified seconds (the value is just a estimate since server process logic is quite
//  simple, and all the intercommunication is local) then cancel the waiting.
class SimpleClient : public ServerStopper {
    public:
    static const size_t MAX_DATA_LEN = 256;
    SimpleClient(asio::io_service& service,
                 unsigned int wait_server_time_out)
    {
        wait_for_response_timer_.reset(new deadline_timer(service));
        received_data_ = new char[MAX_DATA_LEN];
        received_data_len_ = 0;
        wait_server_time_out_ = wait_server_time_out;
    }

    virtual ~SimpleClient() {
        delete [] received_data_;
    }

    void setGetFeedbackCallback(boost::function<void()>& func) {
        get_response_call_back_ = func;
    }

    virtual void sendDataThenWaitForFeedback(const std::string& data)  = 0;
    virtual std::string getReceivedData() const = 0;

    void startTimer() {
        wait_for_response_timer_->cancel();
        wait_for_response_timer_->
            expires_from_now(boost::posix_time::
                             seconds(wait_server_time_out_));
        wait_for_response_timer_->
            async_wait(boost::bind(&SimpleClient::stopWaitingforResponse,
                                   this));
    }

    void cancelTimer() { wait_for_response_timer_->cancel(); }

    void getResponseCallBack(const asio::error_code& error, size_t
                             received_bytes)
    {
        cancelTimer();
        if (!error)
            received_data_len_ = received_bytes;
        if (!get_response_call_back_.empty()) {
            get_response_call_back_();
        }
        stopServer();
    }


    protected:
    virtual void stopWaitingforResponse() = 0;

    boost::shared_ptr<deadline_timer> wait_for_response_timer_;
    char* received_data_;
    size_t received_data_len_;
    boost::function<void()> get_response_call_back_;
    unsigned int wait_server_time_out_;
};



class UDPClient : public SimpleClient {
    public:
    //After 1 second without feedback client will stop wait
    static const unsigned int SERVER_TIME_OUT = 1;

    UDPClient(asio::io_service& service, const ip::udp::endpoint& server) :
        SimpleClient(service, SERVER_TIME_OUT)
    {
        server_ = server;
        socket_.reset(new ip::udp::socket(service));
        socket_->open(ip::udp::v6());
    }


    void sendDataThenWaitForFeedback(const std::string& data) {
        received_data_len_ = 0;
        socket_->send_to(buffer(data.c_str(), data.size() + 1), server_);
        socket_->async_receive_from(buffer(received_data_, MAX_DATA_LEN),
                                    received_from_,
                                    boost::bind(&SimpleClient::
                                                getResponseCallBack, this, _1,
                                                _2));
        startTimer();
    }

    virtual std::string getReceivedData() const {
        return (received_data_len_ == 0 ? std::string("") :
                                std::string(received_data_));
    }

    private:
    void stopWaitingforResponse() {
        socket_->close();
    }

    boost::shared_ptr<ip::udp::socket> socket_;
    ip::udp::endpoint server_;
    ip::udp::endpoint received_from_;
};


class TCPClient : public SimpleClient {
    public:
    // after 2 seconds without feedback client will stop wait,
    // this includes connect, send message and recevice message
    static const unsigned int SERVER_TIME_OUT = 2;
    TCPClient(asio::io_service& service, const ip::tcp::endpoint& server)
        : SimpleClient(service, SERVER_TIME_OUT),
          send_data_delay_(0), send_data_len_delay_(0)
    {
        server_ = server;
        socket_.reset(new ip::tcp::socket(service));
        socket_->open(ip::tcp::v6());
        send_delay_timer_.reset(new deadline_timer(service));
    }


    virtual void sendDataThenWaitForFeedback(const std::string &data) {
        received_data_len_ = 0;
        data_to_send_ = data;
        data_to_send_len_ = data.size() + 1;
        socket_->async_connect(server_, boost::bind(&TCPClient::connectHandler,
                                                    this, _1));
        startTimer();
    }

    virtual std::string getReceivedData() const {
        return (received_data_len_ == 0 ? std::string("") :
                                std::string(received_data_ + 2));
    }

    /// Set the delay before the data len is sent (in seconds)
    /// If this is non-zero, the actual data is never sent
    /// (it is used to test timeout, in which case the connection
    /// should have been closed by the other side anyway)
    void setSendDataLenDelay(size_t send_data_len_delay) {
        send_data_len_delay_ = send_data_len_delay;
    }

    /// Set the delay before the packet data itself is sent
    /// (in seconds)
    void setSendDataDelay(size_t send_data_delay) {
        send_data_delay_ = send_data_delay;
    }

    private:
    void stopWaitingforResponse() {
        socket_->close();
    }

    void connectHandler(const asio::error_code& error) {
        if (!error) {
            data_to_send_len_ = htons(data_to_send_len_);
            sleep(send_data_len_delay_);
            socket_->async_send(buffer(&data_to_send_len_, 2),
                                boost::bind(&TCPClient::sendMessageBodyHandler,
                                            this, _1, _2));
        }
    }

    void sendMessageBodyHandler(const asio::error_code& error,
                                size_t send_bytes)
    {
        if (!error && send_bytes == 2 && send_data_len_delay_ == 0) {
            // We cannot block here (such as by sleep(3)) since otherwise
            // the ASIO events may not reliably handled in the server side
            // as the test expects.  So we use async_wait, and make sure the
            // control will be given back to the IO service.
            if (send_data_delay_ > 0) {
                send_delay_timer_->expires_from_now(boost::posix_time::
                                                    seconds(send_data_delay_));
                send_delay_timer_->async_wait(
                    boost::bind(&TCPClient::sendMessageData, this));
                return;
            }
            sendMessageData();
        }
    }

    void sendMessageData() {
        socket_->async_send(buffer(data_to_send_.c_str(),
                                   data_to_send_.size() + 1),
                            boost::bind(&TCPClient::finishSendHandler, this,
                                        _1, _2));
    }

    void finishSendHandler(const asio::error_code& error, size_t send_bytes) {
        if (error) {
            getResponseCallBack(error, 0);
        } else if (send_bytes == data_to_send_.size() + 1) {
            socket_->async_receive(buffer(received_data_, MAX_DATA_LEN),
                   boost::bind(&SimpleClient::getResponseCallBack, this, _1,
                               _2));
        }
    }

    boost::shared_ptr<ip::tcp::socket> socket_;
    ip::tcp::endpoint server_;
    std::string data_to_send_;
    uint16_t data_to_send_len_;
    boost::shared_ptr<deadline_timer> send_delay_timer_;

    size_t send_data_delay_;
    size_t send_data_len_delay_;
};

// \brief provide the context which including two clients and
// two servers, UDP client will only communicate with UDP server, same for TCP
// client
//
// This is only the active part of the test. We run the test case four times, once
// for each type of initialization (once when giving it the address and port,
// once when giving the file descriptor) multiplied by once for each type of UDP
// server (UDPServer and SyncUDPServer), to ensure it works exactly the same.
template<class UDPServerClass>
class DNSServerTestBase : public::testing::Test {
    protected:
        DNSServerTestBase() :
            server_address_(ip::address::from_string(server_ip)),
            lookup_(new DummyLookup()),
            sync_lookup_(new SyncDummyLookup()),
            answer_(new SimpleAnswer()),
            udp_client_(new UDPClient(service,
                                      ip::udp::endpoint(server_address_,
                                                         server_port))),
            tcp_client_(new TCPClient(service,
                                      ip::tcp::endpoint(server_address_,
                                                        server_port)))
        {
            current_service = &service;
        }

        ~ DNSServerTestBase() {
            if (udp_server_) {
                udp_server_->stop();
            }
            if (tcp_server_) {
                tcp_server_->stop();
            }
            delete lookup_;
            delete sync_lookup_;
            delete answer_;
            delete udp_client_;
            delete tcp_client_;
            // No delete here. The service is not allocated by new, but as our
            // member. This only references it, so just cleaning the pointer.
            current_service = NULL;
        }

        void testStopServerByStopper(DNSServer& server, SimpleClient* client,
                                     ServerStopper* stopper)
        {
            static const unsigned int IO_SERVICE_TIME_OUT = 5;
            io_service_is_time_out = false;
            stopper->setServerToStop(server);
            server();
            client->sendDataThenWaitForFeedback(query_message);
            // Since thread hasn't been introduced into the tool box, using
            // signal to make sure run function will eventually return even
            // server stop failed
            void (*prev_handler)(int) =
                std::signal(SIGALRM, DNSServerTestBase::stopIOService);
            current_service = &service;
            alarm(IO_SERVICE_TIME_OUT);
            service.run();
            service.reset();
            //cancel scheduled alarm
            alarm(0);
            std::signal(SIGALRM, prev_handler);
        }

        static void stopIOService(int _no_use_parameter) {
            io_service_is_time_out = true;
            if (current_service != NULL) {
                current_service->stop();
            }
        }

        bool serverStopSucceed() const {
            return (!io_service_is_time_out);
        }

        asio::io_service service;
        const ip::address server_address_;
        DummyLookup* lookup_;     // we need to replace it in some cases
        SyncDummyLookup*  const sync_lookup_;
        SimpleAnswer* const answer_;
        UDPClient*    const udp_client_;
        TCPClient*    const tcp_client_;
        boost::shared_ptr<UDPServerClass> udp_server_;
        boost::shared_ptr<TCPServer> tcp_server_;

        // To access them in signal handle function, the following
        // variables have to be static.
        static asio::io_service* current_service;
        static bool io_service_is_time_out;
};

// Initialization (by the file descriptor)
template<class UDPServerClass>
class FdInit : public DNSServerTestBase<UDPServerClass> {
private:
    // Opens the file descriptor for us
    // It uses the low-level C api, as it seems to be the easiest way to get
    // a raw file descriptor. It also is what the socket creator does and this
    // API is aimed to it.
    int getFd(int type) {
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = type;
        hints.ai_protocol = (type == SOCK_STREAM) ? IPPROTO_TCP : IPPROTO_UDP;
        hints.ai_flags = AI_NUMERICSERV | AI_NUMERICHOST;

        struct addrinfo* res;
        const int error = getaddrinfo(server_ip, server_port_str,
                                      &hints, &res);
        if (error != 0) {
            isc_throw(IOError, "getaddrinfo failed: " << gai_strerror(error));
        }

        int sock;
        const int on(1);
        // Go as far as you can and stop on failure
        // Create the socket
        // set the options
        // and bind it
        const bool failed((sock = socket(res->ai_family, res->ai_socktype,
                                         res->ai_protocol)) == -1 ||
                          setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on,
                                     sizeof(on)) == -1 ||
                          bind(sock, res->ai_addr, res->ai_addrlen) == -1);
        // No matter if it succeeded or not, free the address info
        freeaddrinfo(res);
        if (failed) {
            if (sock != -1) {
                close(sock);
            }
            return (-1);
        } else {
            return (sock);
        }
    }
protected:
    // Using SetUp here so we can ASSERT_*
    void SetUp() {
        const int fd_udp(getFd(SOCK_DGRAM));
        ASSERT_NE(-1, fd_udp) << strerror(errno);
        this->udp_server_ = createServer(fd_udp, AF_INET6);
        const int fd_tcp(getFd(SOCK_STREAM));
        ASSERT_NE(-1, fd_tcp) << strerror(errno);
        this->tcp_server_ =
            boost::shared_ptr<TCPServer>(new TCPServer(
                                             this->service, fd_tcp, AF_INET6,
                                             this->lookup_,
                                             this->answer_));
    }

    // A helper factory of the tested UDP server class: allow customization
    // by template specialization.
    boost::shared_ptr<UDPServerClass> createServer(int fd, int af) {
        return (boost::shared_ptr<UDPServerClass>(
                    new UDPServerClass(this->service, fd, af,
                                       this->lookup_,
                                       this->answer_)));
    }
};

// Specialization for SyncUDPServer.  It needs to use SyncDummyLookup.
template<>
boost::shared_ptr<SyncUDPServer>
FdInit<SyncUDPServer>::createServer(int fd, int af) {
    delete this->lookup_;
    this->lookup_ = new SyncDummyLookup;
    return (SyncUDPServer::create(this->service, fd, af, this->lookup_));
}

// This makes it the template as gtest wants it.
template<class Parent>
class DNSServerTest : public Parent { };

typedef ::testing::Types<FdInit<UDPServer>, FdInit<SyncUDPServer> >
    ServerTypes;
TYPED_TEST_CASE(DNSServerTest, ServerTypes);

// Some tests work only for SyncUDPServer, some others work only for
// (non Sync)UDPServer.  We specialize these tests.
typedef FdInit<UDPServer> AsyncServerTest;
typedef FdInit<SyncUDPServer> SyncServerTest;

typedef ::testing::Types<UDPServer, SyncUDPServer> UDPServerTypes;
TYPED_TEST_CASE(DNSServerTestBase, UDPServerTypes);

template<class UDPServerClass>
bool DNSServerTestBase<UDPServerClass>::io_service_is_time_out = false;
template<class UDPServerClass>
asio::io_service* DNSServerTestBase<UDPServerClass>::current_service(NULL);

// Test whether server stopped successfully after client get response
// client will send query and start to wait for response, once client
// get response, UDP server will be stopped, the io service won't quit
// if udp server doesn't stop successfully.
TYPED_TEST(DNSServerTest, stopUDPServerAfterOneQuery) {
    this->testStopServerByStopper(*this->udp_server_, this->udp_client_,
                                  this->udp_client_);
    EXPECT_EQ(query_message, this->udp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

// Test whether udp server stopped successfully before server start to serve
TYPED_TEST(DNSServerTest, stopUDPServerBeforeItStartServing) {
    this->udp_server_->stop();
    this->testStopServerByStopper(*this->udp_server_, this->udp_client_,
                                  this->udp_client_);
    EXPECT_EQ(std::string(""), this->udp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

// Test whether udp server stopped successfully during query lookup
TYPED_TEST(DNSServerTest, stopUDPServerDuringQueryLookup) {
    this->testStopServerByStopper(*this->udp_server_, this->udp_client_,
                                  this->lookup_);
    EXPECT_EQ(std::string(""), this->udp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

// Test whether UDP server stopped successfully during composing answer.
// Only works for (non-sync) server because SyncUDPServer doesn't use answer
// callback.
TEST_F(AsyncServerTest, stopUDPServerDuringPrepareAnswer) {
    testStopServerByStopper(*udp_server_, udp_client_, answer_);
    EXPECT_EQ(std::string(""), udp_client_->getReceivedData());
    EXPECT_TRUE(serverStopSucceed());
}

void
stopServerManyTimes(DNSServer *server, unsigned int times) {
    for (unsigned int i = 0; i < times; ++i) {
        server->stop();
    }
}

// Test whether udp server stop interface can be invoked several times without
// throw any exception
TYPED_TEST(DNSServerTest, stopUDPServerMoreThanOnce) {
    ASSERT_NO_THROW({
        boost::function<void()> stop_server_3_times
            = boost::bind(stopServerManyTimes, this->udp_server_.get(), 3);
        this->udp_client_->setGetFeedbackCallback(stop_server_3_times);
        this->testStopServerByStopper(*this->udp_server_,
                                      this->udp_client_, this->udp_client_);
        EXPECT_EQ(query_message, this->udp_client_->getReceivedData());
    });
    EXPECT_TRUE(this->serverStopSucceed());
}

TYPED_TEST(DNSServerTest, stopTCPServerAfterOneQuery) {
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->tcp_client_);
    EXPECT_EQ(query_message, this->tcp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

TYPED_TEST(DNSServerTest, TCPTimeoutOnLen) {
    this->tcp_server_->setTCPRecvTimeout(100);
    this->tcp_client_->setSendDataLenDelay(2);
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->tcp_client_);
    EXPECT_EQ("", this->tcp_client_->getReceivedData());
    EXPECT_FALSE(this->serverStopSucceed());
}

TYPED_TEST(DNSServerTest, TCPTimeout) {
    // set delay higher than timeout
    this->tcp_server_->setTCPRecvTimeout(100);
    this->tcp_client_->setSendDataDelay(2);
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->tcp_client_);
    EXPECT_EQ("", this->tcp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

TYPED_TEST(DNSServerTest, TCPNoTimeout) {
    // set delay lower than timeout
    this->tcp_server_->setTCPRecvTimeout(3000);
    this->tcp_client_->setSendDataDelay(1);
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->tcp_client_);
    EXPECT_EQ("Kea is awesome", this->tcp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

// Test whether tcp server stopped successfully before server start to serve
TYPED_TEST(DNSServerTest, stopTCPServerBeforeItStartServing) {
    this->tcp_server_->stop();
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->tcp_client_);
    EXPECT_EQ(std::string(""), this->tcp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}


// Test whether tcp server stopped successfully during query lookup
TYPED_TEST(DNSServerTest, stopTCPServerDuringQueryLookup) {
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->lookup_);
    EXPECT_EQ(std::string(""), this->tcp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}

// Test whether tcp server stopped successfully during composing answer
TYPED_TEST(DNSServerTest, stopTCPServerDuringPrepareAnswer) {
    this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                  this->answer_);
    EXPECT_EQ(std::string(""), this->tcp_client_->getReceivedData());
    EXPECT_TRUE(this->serverStopSucceed());
}


// Test whether tcp server stop interface can be invoked several times without
// throw any exception
TYPED_TEST(DNSServerTest, stopTCPServeMoreThanOnce) {
    ASSERT_NO_THROW({
        boost::function<void()> stop_server_3_times
            = boost::bind(stopServerManyTimes, this->tcp_server_.get(), 3);
        this->tcp_client_->setGetFeedbackCallback(stop_server_3_times);
        this->testStopServerByStopper(*this->tcp_server_, this->tcp_client_,
                                      this->tcp_client_);
        EXPECT_EQ(query_message, this->tcp_client_->getReceivedData());
    });
    EXPECT_TRUE(this->serverStopSucceed());
}

// It raises an exception when invalid address family is passed
// The parameter here doesn't mean anything
TYPED_TEST(DNSServerTestBase, invalidFamily) {
    // We abuse DNSServerTestBase for this test, as we don't need the
    // initialization.
    EXPECT_THROW_WITH(TCPServer(this->service, 0, AF_UNIX,
                                this->lookup_, this->answer_),
                      isc::InvalidParameter,
                      "Address family must be either AF_INET "
                      "or AF_INET6, not " << AF_UNIX);
}

TYPED_TEST(DNSServerTest, invalidFamilyUDP) {
    EXPECT_THROW_WITH(this->createServer(0, AF_UNIX), isc::InvalidParameter,
                      "Address family must be either AF_INET"
                      " or AF_INET6, not " << AF_UNIX);
}

// It raises an exception when invalid address family is passed
TYPED_TEST(DNSServerTestBase, invalidTCPFD) {
    // We abuse DNSServerTestBase for this test, as we don't need the
    // initialization.
    /*
     FIXME: The UDP server doesn't fail reliably with an invalid FD.
     We need to find a way to trigger it reliably (it seems epoll
     asio backend does fail as it tries to insert it right away, but
     not the others, maybe we could make it run this at last on epoll-based
     systems).
    EXPECT_THROW(UDPServer(service, -1, AF_INET, lookup_,
                           answer_), isc::asiolink::IOError);
    */
    EXPECT_THROW_WITH(TCPServer(this->service, -1, AF_INET,
                                this->lookup_, this->answer_),
                      isc::asiolink::IOError, strerror(EBADF));
}

TYPED_TEST(DNSServerTest, DISABLED_invalidUDPFD) {
    /*
     FIXME: The UDP server doesn't fail reliably with an invalid FD.
     We need to find a way to trigger it reliably (it seems epoll
     asio backend does fail as it tries to insert it right away, but
     not the others, maybe we could make it run this at least on epoll-based
     systems).
    */
    EXPECT_THROW(this->createServer(-1, AF_INET), isc::asiolink::IOError);
}

// Check it rejects some of the unsupported operations
TEST_F(SyncServerTest, unsupportedOps) {
    EXPECT_THROW_WITH(udp_server_->clone(), isc::Unexpected,
                      "SyncUDPServer can't be cloned.");
                      
    EXPECT_THROW_WITH(udp_server_->asyncLookup(), isc::Unexpected,
                      "SyncUDPServer doesn't support asyncLookup by "
                      "design, use UDPServer if you need it.");
}

// Check it rejects forgotten resume (eg. insists that it is synchronous)
TEST_F(SyncServerTest, mustResume) {
    lookup_->allow_resume_ = false;
    ASSERT_THROW_WITH(testStopServerByStopper(*udp_server_, udp_client_,
                                              lookup_),
                      isc::Unexpected,
                      "No resume called from the lookup callback");
}

// SyncUDPServer doesn't allow NULL lookup callback.
TEST_F(SyncServerTest, nullLookupCallback) {
    EXPECT_THROW_WITH(SyncUDPServer::create(service, 0, AF_INET, NULL),
                      isc::InvalidParameter, 
                      "null lookup callback given to SyncUDPServer");
}

TEST_F(SyncServerTest, resetUDPServerBeforeEvent) {
    // Reset the UDP server object after starting and before it would get
    // an event from io_service (in this case abort event).  The following
    // sequence confirms it's shut down immediately, and without any
    // disruption.

    // Since we'll stop the server run() should immediately return, and
    // it's very unlikely to cause hangup.  But we'll make very sure it
    // doesn't happen.
    const unsigned int IO_SERVICE_TIME_OUT = 5;
    (*udp_server_)();
    udp_server_->stop();
    udp_server_.reset();
    void (*prev_handler)(int) = std::signal(SIGALRM, stopIOService);
    current_service = &service;
    alarm(IO_SERVICE_TIME_OUT);
    service.run();
    alarm(0);
    std::signal(SIGALRM, prev_handler);
    EXPECT_FALSE(io_service_is_time_out);
}

}
