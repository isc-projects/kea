// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius.h>
#include <asiolink/tcp_acceptor.h>
#include <asiolink/testutils/test_tls.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <attribute_test.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::tcp;
using namespace isc::test;
using namespace std;
using namespace std::chrono;
namespace ph = std::placeholders;
namespace ba = boost::asio::ip;

namespace {

// Verify the factory with TCP.
TEST(TestTcpExchange, tcpFactory) {
    ExchangePtr exchange;
    IOServicePtr io_service;
    MessagePtr msg;
    Servers servers;

    // No message.
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler(), PW_PROTO_TCP),
                     BadValue, "null request");

    // No servers.
    uint8_t code = PW_ACCOUNTING_REQUEST;
    vector<uint8_t> auth;
    AttributesPtr attrs;
    string secret = "foobar";
    ASSERT_NO_THROW_LOG(msg.reset(new Message(code, 0, auth, secret, attrs)));
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler(), PW_PROTO_TCP),
                     BadValue, "no server");

    // No handler.
    ServerPtr server;
    IOAddress addr("127.0.0.1");
    TlsContextPtr tls_context;
    ASSERT_NO_THROW_LOG(server.reset(new Server(addr, 11646, addr, tls_context,
                                                secret, 0)));
    ASSERT_TRUE(server);
    servers.push_back(server);
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler(), PW_PROTO_TCP),
                     BadValue, "null handler");

    // No error (note that the IOservice is unused).
    auto handler = [] (const ExchangePtr) { };
    ASSERT_NO_THROW_LOG(exchange = Exchange::create(io_service, msg, 0,
                                                    servers, handler,
                                                    PW_PROTO_TCP));

    // Check exchange.
    ASSERT_TRUE(exchange);
    // getId returns a random value.
    EXPECT_EQ(ERROR_RC, exchange->getRC());
    MessagePtr request = exchange->getRequest();
    ASSERT_TRUE(request);
    EXPECT_EQ(request, msg);
    MessagePtr response = exchange->getResponse();
    EXPECT_FALSE(response);

    // Verify it is an TCP Exchange.
    EXPECT_TRUE(boost::dynamic_pointer_cast<TcpExchange>(exchange));
}

// Verify the factory with TLS.
TEST(TestTcpExchange, tlsFactory) {
    ExchangePtr exchange;
    IOServicePtr io_service;
    MessagePtr msg;
    Servers servers;

    // No message.
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler(), PW_PROTO_TLS),
                     BadValue, "null request");

    // No servers.
    uint8_t code = PW_ACCOUNTING_REQUEST;
    vector<uint8_t> auth;
    AttributesPtr attrs;
    string secret = "foobar";
    ASSERT_NO_THROW_LOG(msg.reset(new Message(code, 0, auth, secret, attrs)));
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler(), PW_PROTO_TLS),
                     BadValue, "no server");

    // No handler.
    ServerPtr server;
    IOAddress addr("127.0.0.1");
    TlsContextPtr tls_context;
    asiolink::test::configClient(tls_context);
    ASSERT_NO_THROW_LOG(server.reset(new Server(addr, 11646, addr, tls_context,
                                                secret, 0)));
    ASSERT_TRUE(server);
    servers.push_back(server);
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler(), PW_PROTO_TLS),
                     BadValue, "null handler");

    // No error (note that the IOservice is unused).
    auto handler = [] (const ExchangePtr) { };
    ASSERT_NO_THROW_LOG(exchange = Exchange::create(io_service, msg, 0,
                                                    servers, handler,
                                                    PW_PROTO_TLS));

    // Check exchange.
    ASSERT_TRUE(exchange);
    // getId returns a random value.
    EXPECT_EQ(ERROR_RC, exchange->getRC());
    MessagePtr request = exchange->getRequest();
    ASSERT_TRUE(request);
    EXPECT_EQ(request, msg);
    MessagePtr response = exchange->getResponse();
    EXPECT_FALSE(response);

    // Verify it is an TCP Exchange.
    EXPECT_TRUE(boost::dynamic_pointer_cast<TcpExchange>(exchange));
}

/// Test Exchange class.
class TestExchange : public TcpExchange {
public:
    /// Constructor.
    ///
    TestExchange(const MessagePtr& request,
                 unsigned maxretries,
                 const Servers& servers,
                 Exchange::Handler handler)
        : TcpExchange(request, maxretries, servers, handler) {
    }

    /// Visible members.
    using Exchange::identifier_;
    using Exchange::sync_;
    using Exchange::rc_;
    using Exchange::sent_;
    using Exchange::received_;
    using TcpExchange::start_time_;
    using TcpExchange::server_;

    /// Visible methods.
    using TcpExchange::buildRequest;
    using TcpExchange::RequestHandler;
};

/// Type of shared pointers to test exchange objets.
typedef boost::shared_ptr<TestExchange> TestExchangePtr;

/// Test fixture for testing code of exchange class.
class TcpExchangeTest : public radius::test::AttributeTest {
public:
    // Constructor.
    TcpExchangeTest()
        : radius::test::AttributeTest (), impl_(RadiusImpl::instance()),
          io_service_(new IOService()),
          code_(0), secret_("foobar"), addr_("127.0.0.1"), port_(11460),
          timeout_(10), deadtime_(0), maxretries_(3), called_(false),
          accepted_(false), ec_(),
          handler_([this] (const ExchangePtr ex) { called_ = true; }) {
        impl_.reset();
        impl_.setIOService(io_service_);
        impl_.setIOContext(io_service_);
        impl_.proto_ = PW_PROTO_TCP;
        impl_.tcp_client_.reset(new TcpClient(io_service_, false, 0));
    }

    // Destructor.
    virtual ~TcpExchangeTest() {
        if (exchange_) {
            exchange_->shutdown();
        }
        servers_.clear();

        impl_.tcp_client_.reset();
        // As a best practice, call any remaining handlers before
        // destroying the IO context.
        io_service_->stopAndPoll();

        exchange_.reset();
        io_service_.reset();
        request_.reset();
        servers_.clear();
    }

    // Create request.
    void createRequest() {
        ASSERT_NO_THROW_LOG(request_.reset(new Message(code_, 0, auth_,
                                                       secret_, send_attrs_)));
        ASSERT_TRUE(request_);
    }

    // Add server.
    void addServer() {
        ServerPtr server;
        TlsContextPtr tls_context;
        ASSERT_NO_THROW_LOG(server.reset(new Server(addr_, port_, addr_,
                                                    tls_context, secret_,
                                                    timeout_, deadtime_)));
        ASSERT_TRUE(server);
        servers_.push_back(server);
        ASSERT_FALSE(servers_.empty());
    }

    // Create exchange.
    void createExchange() {
        ASSERT_NO_THROW_LOG(exchange_.reset(new TestExchange(request_,
                                                             maxretries_,
                                                             servers_,
                                                             handler_)));
        ASSERT_TRUE(exchange_);
    }

    // Accept callback.
    void acceptCallback(const boost::system::error_code& ec) {
        accepted_ = true;
        ec_ = ec;
    }

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    // IO service.
    IOServicePtr io_service_;

    // Request.
    MessagePtr request_;

    // Request code.
    uint8_t code_;

    // Request authenticator.
    vector<uint8_t> auth_;

    // Secret.
    string secret_;

    // Request attributes.
    AttributesPtr send_attrs_;

    // Servers.
    Servers servers_;

    // Address.
    IOAddress addr_;

    // Port.
    uint16_t port_;

    // Timeout.
    unsigned timeout_;

    // Deadtime.
    unsigned deadtime_;

    // Max retries.
    unsigned maxretries_;

    // Terminated flag: true if and only if the handler was called.
    bool called_;

    // Accepted flags: true if and only if the accept callback was called.
    bool accepted_;

    // Boost error code.
    boost::system::error_code ec_;

    // Handler.
    Exchange::Handler handler_;

    // Exchange.
    TestExchangePtr exchange_;
};

// Verify the buildRequest method.
TEST_F(TcpExchangeTest, buildRequest) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();
    EXPECT_NO_THROW_LOG(exchange_->buildRequest());

    // Check the to-be-sent message.
    MessagePtr msg = exchange_->sent_;
    ASSERT_TRUE(msg);
    EXPECT_EQ(code_, msg->getCode());
    AttributesPtr attrs = msg->getAttributes();
    ASSERT_TRUE(attrs);
    Attributes expected;
    expected.add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS,
                                       IOAddress("127.0.0.1")));
    EXPECT_TRUE(compare(expected, *attrs))
        << "expected: " << expected.toText() << "\n"
        << "got: " << attrs->toText() << "\n";
}

// Verify the buildRequest method for accounting and IPv6.
TEST_F(TcpExchangeTest, buildRequest6) {
    code_ = PW_ACCOUNTING_REQUEST;
    createRequest();
    addr_ = IOAddress("::1");
    addServer();
    createExchange();
    EXPECT_NO_THROW_LOG(exchange_->buildRequest());

    // Check the to-be-sent message.
    MessagePtr msg = exchange_->sent_;
    ASSERT_TRUE(msg);
    EXPECT_EQ(code_, msg->getCode());
    AttributesPtr attrs = msg->getAttributes();
    ASSERT_TRUE(attrs);
    Attributes expected;
    // Assume that there is less than one second delay in the test.
    expected.add(Attribute::fromInt(PW_ACCT_DELAY_TIME, 0));
    expected.add(Attribute::fromIpv6Addr(PW_NAS_IPV6_ADDRESS, addr_));
    EXPECT_TRUE(compare(expected, *attrs))
        << "expected: " << expected.toText() << "\n"
        << "got: " << attrs->toText() << "\n";
}

// Verify exchange initial state and start.
TEST_F(TcpExchangeTest, start) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Check initial state.
    ASSERT_FALSE(exchange_->identifier_.empty());
    ASSERT_FALSE(exchange_->sync_);
    ASSERT_TRUE(exchange_->server_);
    ASSERT_EQ(ERROR_RC, exchange_->rc_);
    ASSERT_FALSE(exchange_->sent_);
    ASSERT_FALSE(exchange_->received_);
    ASSERT_FALSE(called_);

    ASSERT_NO_THROW_LOG(exchange_->start());
    EXPECT_TRUE(exchange_->sent_);
    EXPECT_FALSE(exchange_->received_);
    EXPECT_FALSE(called_);
}

// Verify start without a server.
TEST_F(TcpExchangeTest, noServer) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    ASSERT_NO_THROW_LOG(exchange_->start());

    // Poll the I/O service.
    for (unsigned i = 0; i < 10; ++i) {
        ASSERT_NO_THROW_LOG(io_service_->poll());
        if (called_) {
            break;
        }
    }
    EXPECT_TRUE(called_);
    EXPECT_EQ(ERROR_RC, exchange_->rc_);
}

// Verify start with a not-responding server.
TEST_F(TcpExchangeTest, timeout) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    timeout_ = 1;
    addServer();
    createExchange();

    ba::tcp::endpoint server_ep(ba::tcp::v4(), port_);
    ba::tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(ba::tcp::acceptor::reuse_address(true));
    ba::tcp::socket socket(io_service_->getInternalIOService());

    exchange_->start();
    // In fact it is not required to accept the connection but it is clearer.
    acceptor.async_accept(socket,
        std::bind(&TcpExchangeTest::acceptCallback, this, ph::_1));

    // Poll the I/O service.
    for (unsigned i = 0; i < 10; ++i) {
        if (called_ || ec_) {
            break;
        }
        io_service_->runOne();
    }
    socket.close();
    acceptor.close();
    EXPECT_TRUE(accepted_);
    EXPECT_FALSE(ec_);
    EXPECT_TRUE(called_);
    EXPECT_EQ(TIMEOUT_RC, exchange_->rc_);
}

// Verify start with a server closing new connections.
TEST_F(TcpExchangeTest, drop) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    timeout_ = 1;
    addServer();
    createExchange();

    ba::tcp::endpoint server_ep(ba::tcp::v4(), port_);
    ba::tcp::acceptor acceptor(io_service_->getInternalIOService(), server_ep);
    acceptor.set_option(ba::tcp::acceptor::reuse_address(true));
    ba::tcp::socket socket(io_service_->getInternalIOService());

    exchange_->start();
    acceptor.async_accept(socket,
        std::bind(&TcpExchangeTest::acceptCallback, this, ph::_1));

    // Poll the I/O service.
    for (unsigned i = 0; i < 10; ++i) {
        if (accepted_) {
            socket.close();
        }
        if (called_ || ec_) {
            break;
        }
        io_service_->runOne();
    }
    acceptor.close();
    EXPECT_TRUE(accepted_);
    EXPECT_FALSE(ec_);
    EXPECT_TRUE(called_);
    EXPECT_EQ(ERROR_RC, exchange_->rc_);
}

// Verify start with error in send.
TEST_F(TcpExchangeTest, sendError) {
    // Make the request encode to fail with too large message.
    send_attrs_.reset(new Attributes());
    string msg = "too too too too too too too too too too  too too ";
    msg += "too too too too too too too too too too  too too ";
    msg += "too too too too too too too too too too  too too ";
    msg += "too too too too too too too too too too  too too ";
    msg += "too too too too too too too too too too  too too long!!!";
    // Hard limit is 253 so be close but lower...
    EXPECT_EQ(252, msg.size());
    AttributePtr attr = Attribute::fromString(PW_REPLY_MESSAGE, msg);
    ASSERT_TRUE(attr);
    for (size_t i = 0; i < 16; ++i) {
        send_attrs_->add(attr);
    }
    send_attrs_->add(Attribute::fromString(PW_USER_PASSWORD, "foobar"));

    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Call start.
    ASSERT_NO_THROW_LOG(exchange_->start());

    // Check new state.
    EXPECT_TRUE(exchange_->sent_);
    EXPECT_EQ(ERROR_RC, exchange_->rc_);
}

// Verify RequestHandler with null exchange.
TEST_F(TcpExchangeTest, requestHandlerNull) {
    auto no_error = boost::system::error_code();
    WireDataPtr response;
    EXPECT_THROW_MSG(TestExchange::RequestHandler(TestExchangePtr(), no_error,
                                                  response, ""),
                     Unexpected,
                     "null exchange in RequestHandler");
}

// Verify RequestHandler on error.
TEST_F(TcpExchangeTest, requestHandlerError) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Call the handler with an error.
    auto ec = boost::asio::error::timed_out;
    WireDataPtr response;
    EXPECT_NO_THROW_LOG(TestExchange::RequestHandler(exchange_, ec,
                                                     response, "timeout"));
    EXPECT_TRUE(called_);
    EXPECT_EQ(TIMEOUT_RC, exchange_->rc_);
}

} // end of anonymous namespace
