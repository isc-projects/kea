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

#include <string.h>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/tests/unittest_util.h>

#include <dns/buffer.h>
#include <dns/message.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/tcpdns.h>
#include <asiolink/internal/udpdns.h>

#include <asio.hpp>

using isc::UnitTestUtil;
using namespace std;
using namespace asiolink;
using namespace isc::dns;
using namespace asio;
using asio::ip::udp;

namespace {
const char* const TEST_SERVER_PORT = "53535";
const char* const TEST_CLIENT_PORT = "53536";
const char* const TEST_IPV6_ADDR = "::1";
const char* const TEST_IPV4_ADDR = "127.0.0.1";
// This data is intended to be valid as a DNS/TCP-like message: the first
// two octets encode the length of the rest of the data.  This is crucial
// for the tests below.
const uint8_t test_data[] = {0, 4, 1, 2, 3, 4};

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

TEST(IOAddressTest, fromText) {
    IOAddress io_address_v4("192.0.2.1");
    EXPECT_EQ("192.0.2.1", io_address_v4.toText());

    IOAddress io_address_v6("2001:db8::1234");
    EXPECT_EQ("2001:db8::1234", io_address_v6.toText());

    // bogus IPv4 address-like input
    EXPECT_THROW(IOAddress("192.0.2.2.1"), IOError);

    // bogus IPv4 address-like input: out-of-range octet
    EXPECT_THROW(IOAddress("192.0.2.300"), IOError);

    // bogus IPv6 address-like input
    EXPECT_THROW(IOAddress("2001:db8:::1234"), IOError);

    // bogus IPv6 address-like input
    EXPECT_THROW(IOAddress("2001:db8::efgh"), IOError);
}

TEST(IOEndpointTest, createUDPv4) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.1"), 5300);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(5300, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_UDP, ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv4) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.1"), 5301);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    EXPECT_EQ(5301, ep->getPort());
    EXPECT_EQ(AF_INET, ep->getFamily());
    EXPECT_EQ(AF_INET, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_TCP, ep->getProtocol());
}

TEST(IOEndpointTest, createUDPv6) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::1234"), 5302);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5302, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_UDP, ep->getProtocol());
}

TEST(IOEndpointTest, createTCPv6) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("2001:db8::1234"), 5303);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    EXPECT_EQ(5303, ep->getPort());
    EXPECT_EQ(AF_INET6, ep->getFamily());
    EXPECT_EQ(AF_INET6, ep->getAddress().getFamily());
    EXPECT_EQ(IPPROTO_TCP, ep->getProtocol());
}

TEST(IOEndpointTest, createIPProto) {
    EXPECT_THROW(IOEndpoint::create(IPPROTO_IP, IOAddress("192.0.2.1"),
                                    5300)->getAddress().toText(),
                 IOError);
}

TEST(IOSocketTest, dummySockets) {
    EXPECT_EQ(IPPROTO_UDP, DummySocket(IPPROTO_UDP).getProtocol());
    EXPECT_EQ(IPPROTO_TCP, DummySocket(IPPROTO_TCP).getProtocol());
    EXPECT_EQ(-1, DummySocket(IPPROTO_UDP).getNative());
    EXPECT_EQ(-1, DummySocket(IPPROTO_TCP).getNative());
}

TEST(IOServiceTest, badPort) {
    IOService io_service;
    EXPECT_THROW(DNSService(io_service, *"65536", true, false, NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *"5300.0", true, false, NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *"-1", true, false, NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *"domain", true, false, NULL, NULL, NULL), IOError);
}

TEST(IOServiceTest, badAddress) {
    IOService io_service;
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"192.0.2.1.1", NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"2001:db8:::1", NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"localhost", NULL, NULL, NULL), IOError);
}

TEST(IOServiceTest, unavailableAddress) {
    IOService io_service;
    // These addresses should generally be unavailable as a valid local
    // address, although there's no guarantee in theory.
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"255.255.0.0", NULL, NULL, NULL), IOError);

    // Some OSes would simply reject binding attempt for an AF_INET6 socket
    // to an IPv4-mapped IPv6 address.  Even if those that allow it, since
    // the corresponding IPv4 address is the same as the one used in the
    // AF_INET socket case above, it should at least show the same result
    // as the previous one.
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"::ffff:255.255.0.0", NULL, NULL, NULL), IOError);
}

TEST(IOServiceTest, duplicateBind_v6) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv6, "any" address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, false, true, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, false, true, NULL, NULL, NULL), IOError);
    delete dns_service;

}

TEST(IOServiceTest, duplicateBind_v6_address) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv6, specific address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV6_ADDR, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV6_ADDR, NULL, NULL, NULL), IOError);
    delete dns_service;

}

TEST(IOServiceTest, duplicateBind_v4) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv4, "any" address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, true, false, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, true, false, NULL, NULL, NULL), IOError);
    delete dns_service;

}

TEST(IOServiceTest, duplicateBind_v4_address) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv4, specific address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV4_ADDR, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV4_ADDR, NULL, NULL, NULL), IOError);
    delete dns_service;
}

// Disabled because IPv4-mapped addresses don't seem to be working with
// the IOService constructor
TEST(IOServiceTest, DISABLED_IPv4MappedDuplicateBind) {
    IOService io_service;
    // Duplicate bind on IPv4-mapped IPv6 address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *"127.0.0.1", NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"::ffff:127.0.0.1", NULL, NULL, NULL), IOError);
    delete dns_service;

    // XXX:
    // Currently, this throws an "invalid argument" exception.  I have
    // not been able to get IPv4-mapped addresses to work.
    dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *"::ffff:127.0.0.1", NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"127.0.0.1", NULL, NULL, NULL), IOError);
    delete dns_service;
}

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
// Note: the set of tests in ASIOLinkTest use actual network services and may
// involve undesirable side effects such as blocking.
class ASIOLinkTest : public ::testing::Test {
protected:
    ASIOLinkTest();
    ~ASIOLinkTest() {
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

        // Now we attempt to recv() whatever was sent
        const int ret = recv(sock_, buffer, size, MSG_DONTWAIT);
        if (ret < 0) {
            isc_throw(IOError, "recvfrom failed");
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
    // created by setIOSerice() will receive the test packet and issue a
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
        explicit MockServer(asio::io_service& io_service,
                            const asio::ip::address& addr, const uint16_t port,
                            SimpleCallback* checkin = NULL,
                            DNSLookup* lookup = NULL,
                            DNSAnswer* answer = NULL) :
            io_(io_service),
            message_(new Message(Message::PARSE)),
            respbuf_(new OutputBuffer(0)),
            checkin_(checkin), lookup_(lookup), answer_(answer)
        {}

        void operator()(asio::error_code ec = asio::error_code(),
                        size_t length = 0)
        {}

        void resume(const bool done) {
            done_ = done;
            io_.post(*this);
        }

        DNSServer* clone() {
            MockServer* s = new MockServer(*this);
            return (s);
        }

        inline void asyncLookup() {
            if (lookup_) {
                (*lookup_)(*io_message_, message_, respbuf_, this);
            }
        }

    protected:
        asio::io_service& io_;
        bool done_;

    private:
        // Currently unused; these will be used for testing
        // asynchronous lookup calls via the asyncLookup() method
        boost::shared_ptr<asiolink::IOMessage> io_message_;
        isc::dns::MessagePtr message_;
        isc::dns::OutputBufferPtr respbuf_;

        // Callback functions provided by the caller
        const SimpleCallback* checkin_;
        const DNSLookup* lookup_;
        const DNSAnswer* answer_;
    };

    // This version of mock server just stops the io_service when it is resumed
    class MockServerStop : public MockServer {
        public:
            explicit MockServerStop(asio::io_service& io_service, bool* done) :
                MockServer(io_service, asio::ip::address(), 0),
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

private:
    class ASIOCallBack : public SimpleCallback {
    public:
        ASIOCallBack(ASIOLinkTest* test_obj) : test_obj_(test_obj) {}
        void operator()(const IOMessage& io_message) const {
            test_obj_->callBack(io_message);
        }
    private:
        ASIOLinkTest* test_obj_;
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
private:
    struct addrinfo* res_;
};

ASIOLinkTest::ASIOLinkTest() :
    dns_service_(NULL), callback_(NULL), sock_(-1), res_(NULL)
{
    io_service_ = new IOService();
    setDNSService(true, true);
}

TEST_F(ASIOLinkTest, v6UDPSend) {
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v6TCPSend) {
    doTest(AF_INET6, IPPROTO_TCP);
}

TEST_F(ASIOLinkTest, v4UDPSend) {
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v4TCPSend) {
    doTest(AF_INET, IPPROTO_TCP);
}

TEST_F(ASIOLinkTest, v6UDPSendSpecific) {
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

TEST_F(ASIOLinkTest, v6TCPSendSpecific) {
    setDNSService(*TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(ASIOLinkTest, v4UDPSendSpecific) {
    setDNSService(*TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v4TCPSendSpecific) {
    setDNSService(*TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(ASIOLinkTest, v6TCPOnly) {
    // Open only IPv6 TCP socket.  A subsequent attempt of establishing an
    // IPv4/TCP connection should fail.  See above for why we only test this
    // for TCP.
    setDNSService(false, true);
    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(ASIOLinkTest, v4TCPOnly) {
    setDNSService(true, false);
    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(ASIOLinkTest, recursiveSetupV4) {
    setDNSService(true, false);
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    EXPECT_NO_THROW(RecursiveQuery(*dns_service_, *TEST_IPV4_ADDR, port));
}

TEST_F(ASIOLinkTest, recursiveSetupV6) {
    setDNSService(false, true);
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    EXPECT_NO_THROW(RecursiveQuery(*dns_service_, *TEST_IPV6_ADDR, port));
}

// XXX:
// This is very inadequate unit testing.  It should be generalized into
// a routine that can do this with variable address family, address, and
// port, and with the various callbacks defined in such a way as to ensure
// full code coverage including error cases.
TEST_F(ASIOLinkTest, recursiveSend) {
    setDNSService(true, false);
    asio::io_service& io = io_service_->get_io_service();

    // Note: We use the test prot plus one to ensure we aren't binding
    // to the same port as the actual server
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    asio::ip::address addr = asio::ip::address::from_string(TEST_IPV4_ADDR);

    MockServer server(io, addr, port, NULL, NULL, NULL);
    RecursiveQuery rq(*dns_service_, *TEST_IPV4_ADDR, port);

    Question q(Name("example.com"), RRClass::IN(), RRType::TXT());
    OutputBufferPtr buffer(new OutputBuffer(0));
    rq.sendQuery(q, buffer, &server);

    char data[4096];
    size_t size = sizeof(data);
    EXPECT_NO_THROW(recvUDP(AF_INET, data, size));

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

void
receive_and_inc(udp::socket* socket, int* num) {
    (*num) ++;
    static char inbuff[512];
    socket->async_receive(asio::buffer(inbuff, 512),
        boost::bind(receive_and_inc, socket, num));
}

// Test it tries the correct amount of times before giving up
TEST_F(ASIOLinkTest, recursiveTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();
    asio::io_service& service = io_service_->get_io_service();

    // Prepare the socket
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    udp::socket socket(service, udp::v4());
    socket.set_option(socket_base::reuse_address(true));
    socket.bind(udp::endpoint(ip::address::from_string(TEST_IPV4_ADDR), port));
    // And count the answers
    int num = -1; // One is counted before the receipt of the first one
    receive_and_inc(&socket, &num);

    // Prepare the server
    bool done(true);
    MockServerStop server(service, &done);

    // Do the answer
    RecursiveQuery query(*dns_service_, *TEST_IPV4_ADDR, port, 10, 2);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    query.sendQuery(question, buffer, &server);

    // Run the test
    service.run();

    // The query should fail
    EXPECT_FALSE(done);
    EXPECT_EQ(3, num);
}

}
