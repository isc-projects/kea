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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <cstring>

#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/tests/unittest_util.h>
#include <dns/rcode.h>

#include <util/buffer.h>
#include <util/unittests/resolver.h>
#include <dns/message.h>
#include <dns/rdataclass.h>

#include <nsas/nameserver_address_store.h>
#include <cache/resolver_cache.h>
#include <resolve/resolve.h>

// IMPORTANT: We shouldn't directly use ASIO definitions in this test.
// In particular, we must not include asio.hpp in this file.
// The asiolink module is primarily intended to be a wrapper that hide the
// details of the underlying implementations.  We need to test the wrapper
// level behaviors.  In addition, some compilers reject to compile this file
// if we include asio.hpp unless we specify a special compiler option.
// If we need to test something at the level of underlying ASIO and need
// their definition, that test should go to asiolink/internal/tests.
#include <resolve/recursive_query.h>
#include <asiodns/dns_lookup.h>
#include <asiolink/io_socket.h>
#include <asiolink/io_service.h>
#include <asiolink/io_message.h>
#include <asiolink/io_error.h>
#include <asiolink/simple_callback.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::dns;
using namespace isc::util;
using boost::scoped_ptr;

namespace isc {
namespace asiodns {

// This is defined in recursive_query.cc, but not in header (it's not public
// function). So bring it in to be tested.
std::string
deepestDelegation(Name name, RRClass rrclass,
                  isc::cache::ResolverCache& cache);

}
}

namespace {
const char* const TEST_SERVER_PORT = "53535";
const char* const TEST_CLIENT_PORT = "53536";
const char* const TEST_IPV6_ADDR = "::1";
const char* const TEST_IPV4_ADDR = "127.0.0.1";
// This data is intended to be valid as a DNS/TCP-like message: the first
// two octets encode the length of the rest of the data.  This is crucial
// for the tests below.
const uint8_t test_data[] = {0, 4, 1, 2, 3, 4};

// This function returns an addrinfo structure for use by tests.
struct addrinfo*
resolveAddress(const int protocol, const char* const addr,
               const char* const port)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // let the address decide it.
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

// convenience shortcut of the other version using different addresses and
// ports depending on whether we're testing IPv4 or v6, TCP or UDP, and
// client or server operation.
struct addrinfo*
resolveAddress(const int family, const int protocol, const bool client) {
    return (resolveAddress(protocol,
                           (family == AF_INET6) ? TEST_IPV6_ADDR :
                           TEST_IPV4_ADDR,
                           client ? TEST_CLIENT_PORT : TEST_SERVER_PORT));
}

// A helper holder of addrinfo so we can safely release the resource
// either when leaving the defined scope either normally or due to exception.
struct ScopedAddrInfo {
    ScopedAddrInfo(struct addrinfo* res) : res_(res) {}
    ~ScopedAddrInfo() { freeaddrinfo(res_); }
    struct addrinfo* res_;
};

// Similar to ScopedAddrInfo but for socket FD.  It also supports the "release"
// operation so it can release the ownership of the FD.
// This is made non copyable to avoid making an accidental copy, which could
// result in duplicate close.
struct ScopedSocket : private boost::noncopyable {
    ScopedSocket() : s_(-1) {}
    ScopedSocket(int s) : s_(s) {}
    ~ScopedSocket() {
        if (s_ >= 0) {
            close(s_);
        }
    }
    void reset(int new_s) {
        if (s_ >= 0) {
            close(s_);
        }
        s_ = new_s;
    }
    int release() {
        int s = s_;
        s_ = -1;
        return (s);
    }
    int s_;
};

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
        // It would delete itself, but after the io_service_, which could
        // segfailt in case there were unhandled requests
        resolver_.reset();
    }

    void SetUp() {
        callback_.reset(new ASIOCallBack(this));
    }

    // Send a test UDP packet to a mock server
    void sendUDP(const int family) {
        ScopedAddrInfo sai(resolveAddress(family, IPPROTO_UDP, false));
        struct addrinfo* res = sai.res_;

        sock_.reset(socket(res->ai_family, res->ai_socktype,
                           res->ai_protocol));
        if (sock_.s_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        const int cc = sendto(sock_.s_, test_data, sizeof(test_data), 0,
                              res->ai_addr, res->ai_addrlen);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected sendto result: " << cc);
        }
        io_service_.run();
    }

    // Send a test TCP packet to a mock server
    void sendTCP(const int family) {
        ScopedAddrInfo sai(resolveAddress(family, IPPROTO_TCP, false));
        struct addrinfo* res = sai.res_;

        sock_.reset(socket(res->ai_family, res->ai_socktype,
                           res->ai_protocol));
        if (sock_.s_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        if (connect(sock_.s_, res->ai_addr, res->ai_addrlen) < 0) {
            isc_throw(IOError, "failed to connect to the test server");
        }
        const int cc = send(sock_.s_, test_data, sizeof(test_data), 0);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected send result: " << cc);
        }
        io_service_.run();
    }

    // Receive a UDP packet from a mock server; used for testing
    // recursive lookup.  The caller must place a RecursiveQuery
    // on the IO Service queue before running this routine.
    void recvUDP(const int family, void* buffer, size_t& size) {
        ScopedAddrInfo sai(resolveAddress(family, IPPROTO_UDP, true));
        struct addrinfo* res = sai.res_;

        sock_.reset(socket(res->ai_family, res->ai_socktype,
                           res->ai_protocol));
        if (sock_.s_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }

        if (bind(sock_.s_, res->ai_addr, res->ai_addrlen) < 0) {
            isc_throw(IOError, "bind failed: " << strerror(errno));
        }

        // The IO service queue should have a RecursiveQuery object scheduled
        // to run at this point.  This call will cause it to begin an
        // async send, then return.
        io_service_.run_one();

        // ... and this one will block until the send has completed
        io_service_.run_one();

        // Now we attempt to recv() whatever was sent.
        // XXX: there's no guarantee the receiving socket can immediately get
        // the packet.  Normally we can perform blocking recv to wait for it,
        // but in theory it's even possible that the packet is lost.
        // In order to prevent the test from hanging in such a worst case
        // we add an ad hoc timeout.
        const struct timeval timeo = { 10, 0 };
        int recv_options = 0;
        if (setsockopt(sock_.s_, SOL_SOCKET, SO_RCVTIMEO, &timeo,
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
        const int ret = recv(sock_.s_, buffer, size, recv_options);
        if (ret < 0) {
            isc_throw(IOError, "recvfrom failed: " << strerror(errno));
        }

        // Pass the message size back via the size parameter
        size = ret;
    }

    void
    addServer(const string& address, const char* const port, int protocol) {
        ScopedAddrInfo sai(resolveAddress(protocol, address.c_str(), port));
        struct addrinfo* res = sai.res_;
        const int family = res->ai_family;

        ScopedSocket sock(socket(res->ai_family, res->ai_socktype,
                                 res->ai_protocol));
        const int s = sock.s_;
        if (s < 0) {
            isc_throw(isc::Unexpected, "failed to open a test socket");
        }
        const int on = 1;
        if (family == AF_INET6) {
            if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)) ==
                -1) {
                isc_throw(isc::Unexpected,
                          "failed to set socket option(IPV6_V6ONLY)");
            }
        }
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
            isc_throw(isc::Unexpected,
                      "failed to set socket option(SO_REUSEADDR)");
        }
        if (bind(s, res->ai_addr, res->ai_addrlen) != 0) {
            isc_throw(isc::Unexpected, "failed to bind a test socket");
        }
        if (protocol == IPPROTO_TCP) {
            dns_service_->addServerTCPFromFD(sock.release(), family);
        } else {
            dns_service_->addServerUDPFromFD(sock.release(), family);
        }
    }

    // Set up an IO Service queue using the specified address
    void setDNSService(const string& address) {
        setDNSService();
        addServer(address, TEST_SERVER_PORT, IPPROTO_TCP);
        addServer(address, TEST_SERVER_PORT, IPPROTO_UDP);
    }

    // Set up an IO Service queue using the "any" address, on IPv4 if
    // 'use_ipv4' is true and on IPv6 if 'use_ipv6' is true.
    void setDNSService(const bool use_ipv4, const bool use_ipv6) {
        setDNSService();
        if (use_ipv6) {
            addServer("::", TEST_SERVER_PORT, IPPROTO_TCP);
            addServer("::", TEST_SERVER_PORT, IPPROTO_UDP);
        }
        if (use_ipv4) {
            addServer("0.0.0.0", TEST_SERVER_PORT, IPPROTO_TCP);
            addServer("0.0.0.0", TEST_SERVER_PORT, IPPROTO_UDP);
        }
    }

    // Set up empty DNS Service
    // Set up an IO Service queue without any addresses
    void setDNSService() {
        dns_service_.reset(new DNSService(io_service_, callback_.get(), NULL,
                                          NULL));
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
        EXPECT_NE(sock_.s_, callback_native_);
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
            done_(false),
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
        boost::shared_ptr<isc::asiolink::IOMessage> io_message_;
        isc::dns::MessagePtr message_;
        isc::dns::MessagePtr answer_message_;
        isc::util::OutputBufferPtr respbuf_;

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
        io_service_.stop();
    }
protected:
    IOService io_service_;
    scoped_ptr<DNSService> dns_service_;
    scoped_ptr<isc::nsas::NameserverAddressStore> nsas_;
    isc::cache::ResolverCache cache_;
    scoped_ptr<ASIOCallBack> callback_;
    int callback_protocol_;
    int callback_native_;
    string callback_address_;
    vector<uint8_t> callback_data_;
    ScopedSocket sock_;
    boost::shared_ptr<isc::util::unittests::TestResolver> resolver_;
};

RecursiveQueryTest::RecursiveQueryTest() :
    dns_service_(NULL), callback_(NULL), callback_protocol_(0),
    callback_native_(-1), resolver_(new isc::util::unittests::TestResolver())
{
    nsas_.reset(new isc::nsas::NameserverAddressStore(resolver_));
}

TEST_F(RecursiveQueryTest, v6UDPSend) {
    setDNSService(true, true);
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v6TCPSend) {
    setDNSService(true, true);
    doTest(AF_INET6, IPPROTO_TCP);
}

TEST_F(RecursiveQueryTest, v4UDPSend) {
    setDNSService(true, true);
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v4TCPSend) {
    setDNSService(true, true);
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

    setDNSService(TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v6TCPSendSpecific) {
    setDNSService(TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(RecursiveQueryTest, v4UDPSendSpecific) {
    setDNSService(TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(RecursiveQueryTest, v4TCPSendSpecific) {
    setDNSService(TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(RecursiveQueryTest, v6AddServer) {
    setDNSService();
    addServer(TEST_IPV6_ADDR, TEST_SERVER_PORT, IPPROTO_TCP);
    doTest(AF_INET6, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(RecursiveQueryTest, v4AddServer) {
    setDNSService();
    addServer(TEST_IPV4_ADDR, TEST_SERVER_PORT, IPPROTO_TCP);
    doTest(AF_INET, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(RecursiveQueryTest, clearServers) {
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
                                   *nsas_, cache_,
                                   singleAddress(TEST_IPV4_ADDR, port),
                                   singleAddress(TEST_IPV4_ADDR, port)));
}

TEST_F(RecursiveQueryTest, recursiveSetupV6) {
    setDNSService(false, true);
    uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    EXPECT_NO_THROW(RecursiveQuery(*dns_service_,
                                   *nsas_, cache_,
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

    MockServer server(io_service_);
    RecursiveQuery rq(*dns_service_,
                      *nsas_, cache_,
                      singleAddress(TEST_IPV4_ADDR, port),
                      singleAddress(TEST_IPV4_ADDR, port));

    Question q(Name("example.com"), RRClass::IN(), RRType::TXT());
    Message query_message(Message::RENDER);
    isc::resolve::initResponseMessage(q, query_message);

    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    rq.forward(ConstMessagePtr(&query_message), answer, buffer, &server);

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
createTestSocket() {
    ScopedAddrInfo sai(resolveAddress(AF_INET, IPPROTO_UDP, true));
    struct addrinfo* res = sai.res_;

    ScopedSocket sock(socket(res->ai_family, res->ai_socktype,
                             res->ai_protocol));
    if (sock.s_ < 0) {
        isc_throw(IOError, "failed to open test socket");
    }
    if (bind(sock.s_, res->ai_addr, res->ai_addrlen) < 0) {
        isc_throw(IOError, "failed to bind test socket");
    }
    return (sock.release());
}

// Mock resolver callback for testing forward query.
class MockResolverCallback : public isc::resolve::ResolverInterface::Callback {
public:
    enum ResultValue {
        DEFAULT = 0,
        SUCCESS = 1,
        FAILURE = 2
    };

    MockResolverCallback(DNSServer* server):
        result(DEFAULT),
        server_(server->clone())
    {}

    ~MockResolverCallback() {
        delete server_;
    }

    void success(const isc::dns::MessagePtr response) {
        result = SUCCESS;
        server_->resume(true);
    }

    void failure() {
        result = FAILURE;
        server_->resume(false);
    }

    uint32_t result;
private:
    DNSServer* server_;
};

// Test query timeout, set query timeout is lower than client timeout
// and lookup timeout.
TEST_F(RecursiveQueryTest, forwardQueryTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    // Prepare the socket
    sock_.reset(createTestSocket());

    // Prepare the server
    bool done(true);
    MockServerStop server(io_service_, &done);

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    RecursiveQuery query(*dns_service_,
                         *nsas_, cache_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         10, 4000, 3000, 2);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    Message query_message(Message::RENDER);
    isc::resolve::initResponseMessage(question, query_message);

    boost::shared_ptr<MockResolverCallback> callback(new MockResolverCallback(&server));
    query.forward(ConstMessagePtr(&query_message), answer, buffer, &server, callback);
    // Run the test
    io_service_.run();
    EXPECT_EQ(callback->result, MockResolverCallback::FAILURE);
}

// If we set client timeout to lower than querytimeout, we should
// get a failure answer
// (no actual answer is given here yet. TODO the returned error message
// should be tested)
TEST_F(RecursiveQueryTest, forwardClientTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    sock_.reset(createTestSocket());

    // Prepare the server
    bool done1(true);
    MockServerStop server(io_service_, &done1);

    MessagePtr answer(new Message(Message::RENDER));

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    RecursiveQuery query(*dns_service_,
                         *nsas_, cache_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         1000, 10, 4000, 4);
    Question q(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    Message query_message(Message::RENDER);
    isc::resolve::initResponseMessage(q, query_message);

    boost::shared_ptr<MockResolverCallback> callback(new MockResolverCallback(&server));
    query.forward(ConstMessagePtr(&query_message), answer, buffer, &server, callback);
    // Run the test
    io_service_.run();
    EXPECT_EQ(callback->result, MockResolverCallback::FAILURE);
}

// If we set lookup timeout to lower than querytimeout, the lookup
// will fail.
TEST_F(RecursiveQueryTest, forwardLookupTimeout) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    // Prepare the socket
    sock_.reset(createTestSocket());

    // Prepare the server
    bool done(true);
    MockServerStop server(io_service_, &done);

    MessagePtr answer(new Message(Message::RENDER));

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    RecursiveQuery query(*dns_service_,
                         *nsas_, cache_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         1000, 4000, 10, 5);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));

    Message query_message(Message::RENDER);
    isc::resolve::initResponseMessage(question, query_message);

    boost::shared_ptr<MockResolverCallback> callback(new MockResolverCallback(&server));
    query.forward(ConstMessagePtr(&query_message), answer, buffer, &server, callback);
    // Run the test
    io_service_.run();
    EXPECT_EQ(callback->result, MockResolverCallback::FAILURE);
}

// Set everything very low and see if this doesn't cause weird
// behaviour
TEST_F(RecursiveQueryTest, lowtimeouts) {
    // Prepare the service (we do not use the common setup, we do not answer
    setDNSService();

    // Prepare the socket
    sock_.reset(createTestSocket());

    // Prepare the server
    bool done(true);
    MockServerStop server(io_service_, &done);

    MessagePtr answer(new Message(Message::RENDER));

    // Do the answer
    const uint16_t port = boost::lexical_cast<uint16_t>(TEST_CLIENT_PORT);
    RecursiveQuery query(*dns_service_,
                         *nsas_, cache_,
                         singleAddress(TEST_IPV4_ADDR, port),
                         singleAddress(TEST_IPV4_ADDR, port),
                         1, 1, 1, 1);
    Question question(Name("example.net"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));

    Message query_message(Message::RENDER);
    isc::resolve::initResponseMessage(question, query_message);

    boost::shared_ptr<MockResolverCallback> callback(new MockResolverCallback(&server));
    query.forward(ConstMessagePtr(&query_message), answer, buffer, &server, callback);
    // Run the test
    io_service_.run();
    EXPECT_EQ(callback->result, MockResolverCallback::FAILURE);
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

    MockServerStop server(io_service_, &done);
    vector<pair<string, uint16_t> > empty_vector;
    RecursiveQuery rq(*dns_service_, *nsas_, cache_, empty_vector,
                      empty_vector, 10000, 0);

    Question q(Name("www.isc.org"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    rq.resolve(q, answer, buffer, &server);
    io_service_.run();

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

    MockServerStop server(io_service_, &done);
    vector<pair<string, uint16_t> > empty_vector;
    RecursiveQuery rq(*dns_service_, *nsas_, cache_, empty_vector,
                      empty_vector, 10000, 0);

    Question q(Name("wwwdoesnotexist.isc.org"), RRClass::IN(), RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    rq.resolve(q, answer, buffer, &server);
    io_service_.run();

    // Check that the answer we got matches the one we wanted
    EXPECT_EQ(Rcode::NXDOMAIN(), answer->getRcode());
    EXPECT_EQ(0, answer->getRRCount(Message::SECTION_ANSWER));
}

// Test that we don't start at root when we have a lower NS cached.
TEST_F(RecursiveQueryTest, CachedNS) {
    setDNSService(true, true);

    // Check we have a reasonable fallback - if there's nothing of interest
    // in the cache, start at root.
    EXPECT_EQ(".", deepestDelegation(Name("www.somewhere.deep.example.org"),
                                     RRClass::IN(), cache_));

    // Prefill the cache. There's a zone with a NS and IP address for one
    // of them (to see that one is enough) and another deeper one, with NS,
    // but without IP.
    RRsetPtr nsUpper(new RRset(Name("example.org"), RRClass::IN(),
                               RRType::NS(), RRTTL(300)));
    nsUpper->addRdata(rdata::generic::NS(Name("ns.example.org")));
    nsUpper->addRdata(rdata::generic::NS(Name("ns2.example.org")));

    RRsetPtr nsLower(new RRset(Name("somewhere.deep.example.org"),
                               RRClass::IN(), RRType::NS(), RRTTL(300)));
    nsLower->addRdata(rdata::generic::NS(Name("ns.somewhere.deep.example.org"))
                      );

    RRsetPtr nsIp(new RRset(Name("ns2.example.org"), RRClass::IN(),
                            RRType::A(), RRTTL(300)));
    nsIp->addRdata(rdata::in::A("192.0.2.1"));

    // Make sure the test runs in the correct environment (we don't test
    // the cache, but we need it to unswer this way for the test, so we
    // just make sure)
    ASSERT_TRUE(cache_.update(nsUpper));
    ASSERT_TRUE(cache_.update(nsLower));
    ASSERT_TRUE(cache_.update(nsIp));
    RRsetPtr deepest(cache_.lookupDeepestNS(Name(
        "www.somewhere.deep.example.org"), RRClass::IN()));
    ASSERT_NE(RRsetPtr(), deepest);
    ASSERT_EQ(nsLower->getName(), deepest->getName());

    // Direct check of the function that chooses the delegation point
    // It should not use nsLower, because we don't have IP address for
    // that one. But it can choose nsUpper.
    EXPECT_EQ("example.org.",
              deepestDelegation(Name("www.somewhere.deep.example.org"),
              RRClass::IN(), cache_));

    // Now more complex and indirect test:
    // We ask it to resolve the name for us. It will pick up a delegation
    // point and ask NSAS for it. NSAS will in turn ask resolver for NS record
    // of the delegation point. We then pick it up from the fake resolver
    // and check it is the correct one. This checks the delegation point
    // travels safely trough the whole path there (it would be enough to check
    // it up to NSAS, but replacing NSAS is more complicated, so we just
    // include in the test as well for simplicity).

    // Prepare the recursive query
    vector<pair<string, uint16_t> > roots;
    roots.push_back(pair<string, uint16_t>("192.0.2.2", 53));

    RecursiveQuery rq(*dns_service_, *nsas_, cache_,
                      vector<pair<string, uint16_t> >(), roots);
    // Ask a question at the bottom. It should not use the lower NS, because
    // it would lead to a loop in NS. But it can use the nsUpper one, it has
    // an IP address and we can avoid asking root.
    Question q(Name("www.somewhere.deep.example.org"), RRClass::IN(),
               RRType::A());
    OutputBufferPtr buffer(new OutputBuffer(0));
    MessagePtr answer(new Message(Message::RENDER));
    // The server is here so we have something to pass there
    MockServer server(io_service_);
    rq.resolve(q, answer, buffer, &server);
    // We don't need to run the service in this test. We are interested only
    // in the place it starts resolving at

    // Look what is asked by NSAS - it should be our delegation point.
    EXPECT_NO_THROW(EXPECT_EQ(nsUpper->getName(),
                              (*resolver_)[0]->getName()) <<
                    "It starts resolving at the wrong place") <<
        "It does not ask NSAS anything, how does it know where to send?";
}

// TODO: add tests that check whether the cache is updated on succesfull
// responses, and not updated on failures.



}
