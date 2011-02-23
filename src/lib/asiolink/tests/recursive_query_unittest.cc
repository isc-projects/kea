// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/socket.h>
#include <sys/time.h>

#include <string.h>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/tests/unittest_util.h>
#include <dns/rcode.h>

#include <dns/buffer.h>
#include <dns/message.h>

// IMPORTANT: We shouldn't directly use ASIO definitions in this test.
// In particular, we must not include asio.hpp in this file.
// The asiolink module is primarily intended to be a wrapper that hide the
// details of the underlying implementations.  We need to test the wrapper
// level behaviors.  In addition, some compilers reject to compile this file
// if we include asio.hpp unless we specify a special compiler option.
// If we need to test something at the level of underlying ASIO and need
// their definition, that test should go to asiolink/internal/tests.
#include <asiolink/recursive_query.h>
#include <asiolink/io_socket.h>
#include <asiolink/io_service.h>
#include <asiolink/io_message.h>
#include <asiolink/io_error.h>
#include <asiolink/dns_lookup.h>
#include <asiolink/simple_callback.h>

using isc::UnitTestUtil;
using namespace std;
using namespace asiolink;
using namespace isc::dns;

namespace {
const char* const TEST_SERVER_PORT = "53535";
const char* const TEST_CLIENT_PORT = "53536";
const char* const TEST_IPV6_ADDR = "::1";
const char* const TEST_IPV4_ADDR = "127.0.0.1";
// This data is intended to be valid as a DNS/TCP-like message: the first
// two octets encode the length of the rest of the data.  This is crucial
// for the tests below.
const uint8_t test_data[] = {0, 4, 1, 2, 3, 4};

// This function returns an addrinfo structure for use by tests, using
// different addresses and ports depending on whether we're testing
// IPv4 or v6, TCP or UDP, and client or server operation.
struct addrinfo*
resolveAddress(const int family, const int protocol, const bool client) {
    const char* const addr = (family == AF_INET6) ?
        TEST_IPV6_ADDR : TEST_IPV4_ADDR;
    const char* const port = client ? TEST_CLIENT_PORT : TEST_SERVER_PORT;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = (protocol == IPPROTO_UDP) ? SOCK_DGRAM : SOCK_STREAM;
    hints.ai_protocol = protocol;
    hints.ai_flags = AI_NUMERICSERV;

    struct addrinfo* res;
    const int error = getaddrinfo(addr, port, &hints, &res);
    if (error != 0) {
        isc_throw(IOError, "getaddrinfo failed: " << gai_strerror(error));
    }

    return (res);
}

// This fixture is a framework for various types of network operations
// using the ASIO interfaces.  Each test case creates an IOService object,
// opens a local "client" socket for testing, sends data via the local socket
// to the service that would run in the IOService object.
// A mock callback function (an ASIOCallBack object) is registered with the
// IOService object, so the test code should be able to examine the data
// received on the server side.  It then checks the received data matches
// expected parameters.
// If initialization parameters of the IOService should be modified, the test
// case can do it using the setDNSService() method.
// Note: the set of tests in RecursiveQueryTest use actual network services and may
// involve undesirable side effects such as blocking.
class RecursiveQueryTest : public ::testing::Test {
protected:
    RecursiveQueryTest();
    ~RecursiveQueryTest() {
        if (res_ != NULL) {
            freeaddrinfo(res_);
        }
        if (sock_ != -1) {
            close(sock_);
        }
        delete dns_service_;
        delete callback_;
        delete io_service_;
    }

    // Send a test UDP packet to a mock server
    void sendUDP(const int family) {
        res_ = resolveAddress(family, IPPROTO_UDP, false);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        const int cc = sendto(sock_, test_data, sizeof(test_data), 0,
                              res_->ai_addr, res_->ai_addrlen);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected sendto result: " << cc);
        }
        io_service_->run();
    }

    // Send a test TCP packet to a mock server
    void sendTCP(const int family) {
        res_ = resolveAddress(family, IPPROTO_TCP, false);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        if (connect(sock_, res_->ai_addr, res_->ai_addrlen) < 0) {
            isc_throw(IOError, "failed to connect to the test server");
        }
        const int cc = send(sock_, test_data, sizeof(test_data), 0);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected send result: " << cc);
        }
        io_service_->run();
    }

    // Receive a UDP packet from a mock server; used for testing
    // recursive lookup.  The caller must place a RecursiveQuery 
    // on the IO Service queue before running this routine.
    void recvUDP(const int family, void* buffer, size_t& size) {
        res_ = resolveAddress(family, IPPROTO_UDP, true);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }

        if (bind(sock_, res_->ai_addr, res_->ai_addrlen) < 0) {
            isc_throw(IOError, "bind failed: " << strerror(errno));
        }

        // The IO service queue should have a RecursiveQuery object scheduled
        // to run at this point.  This call will cause it to begin an
        // async send, then return.
        io_service_->run_one();

        // ... and this one will block until the send has completed
        io_service_->run_one();

        // Now we attempt to recv() whatever was sent.
        // XXX: there's no guarantee the receiving socket can immediately get
        // the packet.  Normally we can perform blocking recv to wait for it,
        // but in theory it's even possible that the packet is lost.
        // In order to prevent the test from hanging in such a worst case
        // we add an ad hoc timeout.
        const struct timeval timeo = { 10, 0 };
        int recv_options = 0;
        if (setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, &timeo,
                       sizeof(timeo))) {
            if (errno == ENOPROTOOPT) {
                // Workaround for Solaris: it doesn't accept SO_RCVTIMEO
                // with the error of ENOPROTOOPT.  Since this is a workaround
                // for rare error cases anyway, we simply switch to the
                // "don't wait" mode.  If we still find an error in recv()
                // can happen often we'll consider a more complete solution.
                recv_options = MSG_DONTWAIT;
            } else {
                isc_throw(IOError, "set RCVTIMEO failed: " << strerror(errno));
            }
        }
        const int ret = recv(sock_, buffer, size, recv_options);
        if (ret < 0) {
            isc_throw(IOError, "recvfrom failed: " << strerror(errno));
        }
        
        // Pass the message size back via the size parameter
        size = ret;
    }


    // Set up an IO Service queue using the specified address
    void setDNSService(const char& address) {
        delete dns_service_;
        dns_service_ = NULL;
        delete io_service_;
        io_service_ = new IOService();
        callback_ = new ASIOCallBack(this);
        dns_service_ = new DNSService(*io_service_, *TEST_SERVER_PORT, address, callback_, NULL, NULL);
    }

    // Set up an IO Service queue using the "any" address, on IPv4 if
    // 'use_ipv4' is true and on IPv6 if 'use_ipv6' is true.
    void setDNSService(const bool use_ipv4, const bool use_ipv6) {
        delete dns_service_;
        dns_service_ = NULL;
        delete io_service_;
        io_service_ = new IOService();
        callback_ = new ASIOCallBack(this);
        dns_service_ = new DNSService(*io_service_, *TEST_SERVER_PORT, use_ipv4, use_ipv6, callback_,
                                      NULL, NULL);
    }

    // Set up empty DNS Service
    // Set up an IO Service queue without any addresses
    void setDNSService() {
        delete dns_service_;
        dns_service_ = NULL;
        delete io_service_;
        io_service_ = new IOService();
        callback_ = new ASIOCallBack(this);
        dns_service_ = new DNSService(*io_service_, callback_, NULL, NULL);
    }

    // Run a simple server test, on either IPv4 or IPv6, and over either
    // UDP or TCP.  Calls the sendUDP() or sendTCP() methods, which will
    // start the IO Service queue.  The UDPServer or TCPServer that was
    // created by setIOService() will receive the test packet and issue a
    // callback, which enables us to check that the data it received
    // matches what we sent.
    void doTest(const int family, const int protocol) {
        if (protocol == IPPROTO_UDP) {
            sendUDP(family);
        } else {
            sendTCP(family);
        }

        // There doesn't seem to be an effective test for the validity of
        // 'native'.
        // One thing we are sure is it must be different from our local socket.
        EXPECT_NE(sock_, callback_native_);
        EXPECT_EQ(protocol, callback_protocol_);
        EXPECT_EQ(family == AF_INET6 ? TEST_IPV6_ADDR : TEST_IPV4_ADDR,
                  callback_address_);

        const uint8_t* expected_data =
            protocol == IPPROTO_UDP ? test_data : test_data + 2;
        const size_t expected_datasize =
            protocol == IPPROTO_UDP ? sizeof(test_data) :
            sizeof(test_data) - 2;
        EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &callback_data_[0],
                            callback_data_.size(),
                            expected_data, expected_datasize);
    }

protected:
    // This is a nonfunctional mockup of a DNSServer object.  Its purpose
    // is to resume after a recursive query or other asynchronous call
    // has completed.
    class MockServer : public DNSServer {
    public:
        explicit MockServer(IOService& io_service,
                            SimpleCallback* checkin = NULL,
                            DNSLookup* lookup = NULL,
                            DNSAnswer* answer = NULL) :
            io_(io_service),
            message_(new Message(Message::PARSE)),
            answer_message_(new Message(Message::RENDER)),
            respbuf_(new OutputBuffer(0)),
            checkin_(checkin), lookup_(lookup), answer_(answer)
        {}

        void operator()(asio::error_code ec = asio::error_code(),
                        size_t length = 0)
        {}

        void resume(const bool) {
          // should never be called in our tests
        }

        DNSServer* clone() {
            MockServer* s = new MockServer(*this);
            return (s);
        }

        inline void asyncLookup() {
            if (lookup_) {
                (*lookup_)(*io_message_, message_, answer_message_,
                           respbuf_, this);
            }
        }

    protected:
        IOService& io_;
        bool done_;

    private:
        // Currently unused; these will be used for testing
        // asynchronous lookup calls via the asyncLookup() method
        boost::shared_ptr<asiolink::IOMessage> io_message_;
        isc::dns::MessagePtr message_;
        isc::dns::MessagePtr answer_message_;
        isc::dns::OutputBufferPtr respbuf_;

        // Callback functions provided by the caller
        const SimpleCallback* checkin_;
        const DNSLookup* lookup_;
        const DNSAnswer* answer_;
    };

    // This version of mock server just stops the io_service when it is resumed
    class MockServerStop : public MockServer {
        public:
            explicit MockServerStop(IOService& io_service, bool* done) :
                MockServer(io_service),
                done_(done)
            {}

            void resume(const bool done) {
                *done_ = done;
                io_.stop();
            }

            DNSServer* clone() {
                return (new MockServerStop(*this));
            }
        private:
            bool* done_;
    };

    // This version of mock server just stops the io_service when it is resumed
    // the second time. (Used in the clientTimeout test, where resume
    // is called initially with the error answer, and later when the
    // lookup times out, it is called without an answer to send back)
    class MockServerStop2 : public MockServer {
        public:
            explicit MockServerStop2(IOService& io_service,
                                     bool* done1, bool* done2) :
                MockServer(io_service),
                done1_(done1),
                done2_(done2),
                stopped_once_(false)
            {}

            void resume(const bool done) {
                if (stopped_once_) {
                    *done2_ = done;
                    io_.stop();
                } else {
                    *done1_ = done;
                    stopped_once_ = true;
                }
            }

            DNSServer* clone() {
                return (new MockServerStop2(*this));
            }
        private:
            bool* done1_;
            bool* done2_;
            bool stopped_once_;
    };

private:
    class ASIOCallBack : public SimpleCallback {
    public:
        ASIOCallBack(RecursiveQueryTest* test_obj) : test_obj_(test_obj) {}
        void operator()(const IOMessage& io_message) const {
            test_obj_->callBack(io_message);
        }
    private:
        RecursiveQueryTest* test_obj_;
    };
    void callBack(const IOMessage& io_message) {
        callback_protocol_ = io_message.getSocket().getProtocol();
        callback_native_ = io_message.getSocket().getNative();
        callback_address_ =
            io_message.getRemoteEndpoint().getAddress().toText();
        callback_data_.assign(
            static_cast<const uint8_t*>(io_message.getData()),
            static_cast<const uint8_t*>(io_message.getData()) +
            io_message.getDataSize());
        io_service_->stop();
    }
protected:
    // We use a pointer for io_service_, because for some tests we
    // need to recreate a new one within one onstance of this class
    IOService* io_service_;
    DNSService* dns_service_;
    ASIOCallBack* callback_;
    int callback_protocol_;
    int callback_native_;
    string callback_address_;
    vector<uint8_t> callback_data_;
    int sock_;
    struct addrinfo* res_;
};

RecursiveQueryTest::RecursiveQueryTest() :
    dns_service_(NULL), callback_(NULL), sock_(-1), res_(NULL)
{
    io_service_ = new IOService();
    setDNSService(true, true);
}

TEST_F(RecursiveQueryTest, v6UDPSend) {
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v6TCPSend) {
    doTest(AF_INET6, IPPROTO_TCP);
}

TEST_F(RecursiveQueryTest, v4UDPSend) {
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v4TCPSend) {
    doTest(AF_INET, IPPROTO_TCP);
}

TEST_F(RecursiveQueryTest, v6UDPSendSpecific) {
    // Explicitly set a specific address to be bound to the socket.
    // The subsequent test does not directly ensures the underlying socket
    // is bound to the expected address, but the success of the tests should
    // reasonably suggest it works as intended.
    // Specifying an address also implicitly means the service runs in a
    // single address-family mode.  In tests using TCP we can confirm that
    // by trying to make a connection and seeing a failure.  In UDP, it'd be
    // more complicated because we need to use a connected socket and catch
    // an error on a subsequent read operation.  We could do it, but for
    // simplicity we only tests the easier cases for now.

    setDNSService(*TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v6TCPSendSpecific) {
    setDNSService(*TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(RecursiveQueryTest, v4UDPSendSpecific) {
    setDNSService(*TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v4TCPSendSpecific) {
    setDNSService(*TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(RecursiveQueryTest, v6AddServer) {
    setDNSService();
    dns_service_->addServer(*TEST_SERVER_PORT, TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(RecursiveQueryTest, v4AddServer) {
    setDNSService();
    dns_service_->addServer(*TEST_SERVER_PORT, TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(RecursiveQueryTest, DISABLED_clearServers) {
    // FIXME: Enable when clearServers actually close the sockets
    //    See #388
    setDNSService();
    dns_service_->clearServers();

    EXPECT_THROW(sendTCP(AF_INET), IOError);
    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(RecursiveQueryTest, v6TCPOnly) {
    // Open only IPv6 TCP socket.  A subsequent attempt of establishing an
    // IPv4/TCP connection should fail.  See above for why we only test this
    // for TCP.
    setDNSService(false, true);
    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(RecursiveQueryTest, v4TCPOnly) {
    setDNSService(true, false);
    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

vector<pair<string, uint16_t> >
singleAddress(const string &address, uint16_t port) {
    vector<pair<string, uint16_t> > result;
    result.push_back(pair<string, uint16_t>(address, port));
    return (result);
}

TEST_F(RecursiveQueryTest, recursiveSetupV4) {
    setDNSService(true, false);
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    EXPECT_NO_THROW(RecursiveQuery(*dns_service_,
                                   singleAddress(TEST_IPV4_ADDR, port),
                                   singleAddress(TEST_IPV4_ADDR, port)));
}

TEST_F(RecursiveQueryTest, recursiveSetupV6) {
    setDNSService(false, true);
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    EXPECT_NO_THROW(RecursiveQuery(*dns_service_,
                                   singleAddress(TEST_IPV6_ADDR, port),
                                   singleAddress(TEST_IPV6_ADDR,port)));
}

// XXX:
// This is very inadequate unit testing.  It should be generalized into
// a routine that can do this with variable address family, address, and
// port, and with the various callbacks defined in such a way as to ensure
// full code coverage including error cases.
TEST_F(RecursiveQueryTest, forwarderSend) {
    setDNSService(true, false);

    // Note: We use the test prot plus one to ensure we aren't binding
    // to the same port as the actual server
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);

    MockServer server(*io_service_);
    RecursiveQuery rq(*dns_service_,
                      singleAddress(TEST_IPV4_ADDR, port),
                      singleAddress(TEST_IPV4_ADDR, port));

    Question q(Name("example.com"), RRClass::IN(), RRType::TXT());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    rq.resolve(q, answer, buffer, &server);

    char data[4096];
    size_t size = sizeof(data);
    ASSERT_NO_THROW(recvUDP(AF_INET, data, size));

    Message m(Message::PARSE);
    InputBuffer ibuf(data, size);

    // Make sure we can parse the message that was sent
    EXPECT_NO_THROW(m.parseHeader(ibuf));
    EXPECT_NO_THROW(m.fromWire(ibuf));

    // Check that the question sent matches the one we wanted
    QuestionPtr q2 = *m.beginQuestion();
    EXPECT_EQ(q.getName(), q2->getName());
    EXPECT_EQ(q.getType(), q2->getType());
    EXPECT_EQ(q.getClass(), q2->getClass());
}

int
createTestSocket()
{
    struct addrinfo* res_ = resolveAddress(AF_INET, IPPROTO_UDP, true);
    int sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
    if (sock_ < 0) {
        isc_throw(IOError, "failed to open test socket");
    }
    if (bind(sock_, res_->ai_addr, res_->ai_addrlen) < 0) {
        isc_throw(IOError, "failed to bind test socket");
    }
    return sock_;
}

int
setSocketTimeout(int sock_, size_t tv_sec, size_t tv_usec) {
    const struct timeval timeo = { tv_sec, tv_usec };
    int recv_options = 0;
    if (setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, &timeo, sizeof(timeo))) {
        if (errno == ENOPROTOOPT) { // see RecursiveQueryTest::recvUDP()
            recv_options = MSG_DONTWAIT;
        } else {
            isc_throw(IOError, "set RCVTIMEO failed: " << strerror(errno));
        }
    }
    return recv_options;
}

// try to read from the socket max time
// *num is incremented for every succesfull read
// returns true if it can read max times, false otherwise
bool tryRead(int sock_, int recv_options, size_t max, int* num) {
    size_t i = 0;
    do {
        char inbuff[512];
        if (recv(sock_, inbuff, sizeof(inbuff), recv_options) < 0) {
            return false;
        } else {
            ++i;
            ++*num;
        }
    } while (i < max);
    return true;
}


// Test it tries the correct amount of times before giving up
TEST_F(RecursiveQueryTest, forwardQueryTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    // Prepare the socket
    sock_ = createTestSocket();

    // Prepare the server
    bool done(true);
    MockServerStop server(*io_service_, &done);

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    RecursiveQuery query(*dns_service_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         10, 4000, 3000, 2);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    query.resolve(question, answer, buffer, &server);

    // Run the test
    io_service_->run();

    // Read up to 3 packets.  Use some ad hoc timeout to prevent an infinite
    // block (see also recvUDP()).
    int recv_options = setSocketTimeout(sock_, 10, 0);
    int num = 0;
    bool read_success = tryRead(sock_, recv_options, 3, &num);

    // The query should fail
    EXPECT_FALSE(done);
    EXPECT_EQ(3, num);
    EXPECT_TRUE(read_success);
}

// If we set client timeout to lower than querytimeout, we should
// get a failure answer, but still see retries
// (no actual answer is given here yet)
TEST_F(RecursiveQueryTest, forwardClientTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    sock_ = createTestSocket();

    // Prepare the server
    bool done1(true);
    bool done2(true);
    MockServerStop2 server(*io_service_, &done1, &done2);

    MessagePtr answer(new Message(Message::RENDER));

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    // Set it up to retry twice before client timeout fires
    // Since the lookup timer has not fired, it should retry
    // four times
    RecursiveQuery query(*dns_service_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         200, 480, 4000, 4);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    query.resolve(question, answer, buffer, &server);

    // Run the test
    io_service_->run();

    // we know it'll fail, so make it a shorter timeout
    int recv_options = setSocketTimeout(sock_, 1, 0);

    // Try to read 5 times
    int num = 0;
    bool read_success = tryRead(sock_, recv_options, 5, &num);

    // The query should fail, but we should have kept on trying
    EXPECT_TRUE(done1);
    EXPECT_FALSE(done2);
    EXPECT_EQ(5, num);
    EXPECT_TRUE(read_success);
}

// If we set lookup timeout to lower than querytimeout*retries, we should
// fail before the full amount of retries
TEST_F(RecursiveQueryTest, forwardLookupTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    // Prepare the socket
    sock_ = createTestSocket();

    // Prepare the server
    bool done(true);
    MockServerStop server(*io_service_, &done);

    MessagePtr answer(new Message(Message::RENDER));

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    // Set up the test so that it will retry 5 times, but the lookup
    // timeout will fire after only 3 normal timeouts
    RecursiveQuery query(*dns_service_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         200, 4000, 480, 5);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    query.resolve(question, answer, buffer, &server);

    // Run the test
    io_service_->run();

    int recv_options = setSocketTimeout(sock_, 1, 0);

    // Try to read 5 times, should stop after 3 reads
    int num = 0;
    bool read_success = tryRead(sock_, recv_options, 5, &num);

    // The query should fail
    EXPECT_FALSE(done);
    EXPECT_EQ(3, num);
    EXPECT_FALSE(read_success);
}

// as mentioned above, we need a more better framework for this,
// in addition to that, this sends out queries into the world
// (which we should catch somehow and fake replies for)
// for the skeleton code, it shouldn't be too much of a problem
// Ok so even we don't all have access to the DNS world right now,
// so disabling these tests too.
TEST_F(RecursiveQueryTest, DISABLED_recursiveSendOk) {
    setDNSService(true, false);
    bool done;
    
    MockServerStop server(*io_service_, &done);
    vector<pair<string, uint16_t> > empty_vector;
    RecursiveQuery rq(*dns_service_, empty_vector, empty_vector, 10000, 0);

    Question q(Name("www.isc.org"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    rq.resolve(q, answer, buffer, &server);
    io_service_->run();

    // Check that the answer we got matches the one we wanted
    EXPECT_EQ(Rcode::NOERROR(), answer->getRcode());
    ASSERT_EQ(1, answer->getRRCount(Message::SECTION_ANSWER));
    RRsetPtr a = *answer->beginSection(Message::SECTION_ANSWER);
    EXPECT_EQ(q.getName(), a->getName());
    EXPECT_EQ(q.getType(), a->getType());
    EXPECT_EQ(q.getClass(), a->getClass());
    EXPECT_EQ(1, a->getRdataCount());
}

// see comments at previous test
TEST_F(RecursiveQueryTest, DISABLED_recursiveSendNXDOMAIN) {
    setDNSService(true, false);
    bool done;
    
    MockServerStop server(*io_service_, &done);
    vector<pair<string, uint16_t> > empty_vector;
    RecursiveQuery rq(*dns_service_, empty_vector, empty_vector, 10000, 0);

    Question q(Name("wwwdoesnotexist.isc.org"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    rq.resolve(q, answer, buffer, &server);
    io_service_->run();

    // Check that the answer we got matches the one we wanted
    EXPECT_EQ(Rcode::NXDOMAIN(), answer->getRcode());
    EXPECT_EQ(0, answer->getRRCount(Message::SECTION_ANSWER));
}

}
