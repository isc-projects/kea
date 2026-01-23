// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the attribute,
/// attribute collection and config attribute collection classes.

#include <config.h>

#include <client_exchange.h>
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
using namespace isc::test;
using namespace std;
using namespace std::chrono;

namespace {

// Verify the async constructor.
TEST(TestExchange, async) {
    ExchangePtr exchange;
    IOServicePtr io_service;
    MessagePtr msg;
    Servers servers;

    // No IO service.
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler()),
                     BadValue, "null IO service");

    // No message.
    io_service.reset(new IOService());
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler()),
                     BadValue, "null request");

    // No servers.
    uint8_t code = PW_ACCOUNTING_REQUEST;
    vector<uint8_t> auth;
    AttributesPtr attrs;
    string secret = "foobar";
    ASSERT_NO_THROW_LOG(msg.reset(new Message(code, 0, auth, secret, attrs)));
    EXPECT_THROW_MSG(Exchange::create(io_service, msg, 0, servers,
                                      Exchange::Handler()),
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
                                      Exchange::Handler()),
                     BadValue, "null handler");

    // No error.
    auto handler = [] (const ExchangePtr) { };
    ASSERT_NO_THROW_LOG(exchange = Exchange::create(io_service, msg, 0,
                                                    servers, handler));

    // Check exchange.
    ASSERT_TRUE(exchange);
    // getId returns a random value.
    EXPECT_EQ(ERROR_RC, exchange->getRC());
    MessagePtr request = exchange->getRequest();
    ASSERT_TRUE(request);
    EXPECT_EQ(request, msg);
    MessagePtr response = exchange->getResponse();
    EXPECT_FALSE(response);

    // As a best practice, call any remaining handlers.
    io_service->stopAndPoll();
}

// Verify the sync constructor.
TEST(TestExchange, sync) {
    ExchangePtr exchange;
    MessagePtr msg;
    Servers servers;

    // No message.
    EXPECT_THROW_MSG(Exchange::create(msg, 0, servers), BadValue,
                     "null request");

    // No servers.
    uint8_t code = PW_ACCESS_REQUEST;
    vector<uint8_t> auth;
    AttributesPtr attrs;
    string secret = "foobar";
    ASSERT_NO_THROW_LOG(msg.reset(new Message(code, 0, auth, secret, attrs)));
    EXPECT_THROW_MSG(Exchange::create(msg, 0, servers), BadValue,
                     "no server");

    // No error.
    ServerPtr server;
    IOAddress addr("127.0.0.1");
    TlsContextPtr tls_context;
    ASSERT_NO_THROW_LOG(server.reset(new Server(addr, 11645, addr, tls_context,
                                                secret, 0)));
    ASSERT_TRUE(server);
    servers.push_back(server);
    ASSERT_NO_THROW_LOG(exchange = Exchange::create(msg, 0, servers));

    // Check exchange.
    ASSERT_TRUE(exchange);
    // getId returns a random value.
    EXPECT_EQ(ERROR_RC, exchange->getRC());
    MessagePtr request = exchange->getRequest();
    ASSERT_TRUE(request);
    EXPECT_EQ(request, msg);
    MessagePtr response = exchange->getResponse();
    EXPECT_FALSE(response);
}

/// Test Exchange class.
class TestExchange : public UdpExchange {
public:
    /// Constructor.
    ///
    TestExchange(const asiolink::IOServicePtr io_service,
                 const MessagePtr& request,
                 unsigned maxretries,
                 const Servers& servers,
                 Exchange::Handler handler)
        : UdpExchange(io_service, request, maxretries, servers, handler) {
    }

    /// Visible members.
    using Exchange::identifier_;
    using Exchange::sync_;
    using Exchange::rc_;
    using Exchange::received_;
    using UdpExchange::started_;
    using UdpExchange::terminated_;
    using UdpExchange::start_time_;
    using UdpExchange::socket_;
    using UdpExchange::ep_;
    using UdpExchange::timer_;
    using UdpExchange::server_;
    using UdpExchange::idx_;
    using UdpExchange::sent_;
    using UdpExchange::buffer_;
    using UdpExchange::size_;
    using UdpExchange::retries_;
    using UdpExchange::postponed_;

    /// Visible methods.
    using UdpExchange::buildRequest;
    using UdpExchange::open;
    using UdpExchange::receivedHandler;
};

/// Type of shared pointers to test exchange objets.
typedef boost::shared_ptr<TestExchange> TestExchangePtr;


/// Test fixture for testing code of exchange class.
class ExchangeTest : public radius::test::AttributeTest {
public:
    // Constructor.
    ExchangeTest()
        : radius::test::AttributeTest (), io_service_(new IOService()),
          code_(0), secret_("foobar"), addr_("127.0.0.1"),
          port_(11460), timeout_(10), deadtime_(0), maxretries_(3),
          called_(false),
          handler_([this] (const ExchangePtr) { called_ = true; }) {
    }

    // Destructor.
    virtual ~ExchangeTest() {
        if (exchange_) {
            exchange_->shutdown();
        }
        servers_.clear();

        // As a best practice, call any remaining handlers before destroying the
        // IO context.
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
        ASSERT_NO_THROW_LOG(exchange_.reset(new TestExchange(io_service_,
                                                             request_,
                                                             maxretries_,
                                                             servers_,
                                                             handler_)));
        ASSERT_TRUE(exchange_);
    }

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

    // Handler.
    Exchange::Handler handler_;

    // Exchange.
    TestExchangePtr exchange_;
};

// Verify the buildRequest method.
TEST_F(ExchangeTest, buildRequest) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // server_ is required.
    EXPECT_THROW_MSG(exchange_->buildRequest(), Unexpected, "no server");
    exchange_->server_ = servers_[0];
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
TEST_F(ExchangeTest, buildRequest6) {
    code_ = PW_ACCOUNTING_REQUEST;
    createRequest();
    addr_ = IOAddress("::1");
    addServer();
    createExchange();

    // server_ is required.
    EXPECT_THROW_MSG(exchange_->buildRequest(), Unexpected, "no server");
    exchange_->server_ = servers_[0];
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
TEST_F(ExchangeTest, start) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Check initial state.
    ASSERT_FALSE(exchange_->identifier_.empty());
    ASSERT_FALSE(exchange_->sync_);
    ASSERT_FALSE(exchange_->server_);
    ASSERT_EQ(0, exchange_->idx_);
    ASSERT_FALSE(exchange_->started_);
    ASSERT_FALSE(exchange_->terminated_);
    ASSERT_EQ(ERROR_RC, exchange_->rc_);
    ASSERT_FALSE(exchange_->socket_);
    ASSERT_FALSE(exchange_->ep_);
    ASSERT_FALSE(exchange_->timer_);
    ASSERT_FALSE(exchange_->server_);
    ASSERT_EQ(0, exchange_->idx_);
    ASSERT_FALSE(exchange_->sent_);
    ASSERT_FALSE(exchange_->received_);
    ASSERT_TRUE(exchange_->buffer_.empty());
    ASSERT_EQ(0, exchange_->size_);
    ASSERT_EQ(0, exchange_->retries_);
    ASSERT_TRUE(exchange_->postponed_.empty());
    ASSERT_FALSE(called_);

    ASSERT_NO_THROW_LOG(exchange_->start());
    EXPECT_TRUE(exchange_->started_);
    ASSERT_NO_THROW_LOG(exchange_->shutdown());
}

// Verify open in the initial case.
TEST_F(ExchangeTest, openInit) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Check initial state.
    EXPECT_FALSE(exchange_->server_);
    EXPECT_EQ(0, exchange_->idx_);

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_TRUE(exchange_->server_);
    EXPECT_EQ(servers_[0], exchange_->server_);
    EXPECT_EQ(0, exchange_->idx_);
    EXPECT_TRUE(exchange_->sent_);
    ASSERT_TRUE(exchange_->ep_);
    EXPECT_TRUE(exchange_->timer_);
    EXPECT_EQ(addr_.toText(), exchange_->ep_->getAddress().toText());
    EXPECT_EQ(port_, exchange_->ep_->getPort());
    EXPECT_TRUE(exchange_->socket_);
    EXPECT_FALSE(exchange_->buffer_.empty());
    EXPECT_EQ(code_, exchange_->buffer_[0]);
    EXPECT_LT(AUTH_HDR_LEN, exchange_->size_);
    EXPECT_EQ(exchange_->size_, exchange_->buffer_.size());
    EXPECT_FALSE(called_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was not called.
    EXPECT_FALSE(called_);
}

// Verify open with next server being null.
TEST_F(ExchangeTest, openNullServer) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    ServerPtr null_server;
    servers_.push_back(null_server);
    createExchange();

    // Call open.
    EXPECT_THROW_MSG(exchange_->open(), Unexpected, "null server at 0");
}

// Verify open with next server in hold-down state.
TEST_F(ExchangeTest, openPostpone) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    deadtime_ = 60;
    addServer();
    createExchange();

    // Put the server in hold-down.
    ServerPtr server = servers_[0];
    ASSERT_TRUE(server);
    server->setDeadtimeEnd(steady_clock().now() + seconds(deadtime_));

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_EQ(1, exchange_->idx_);
    ASSERT_EQ(1, exchange_->postponed_.size());
    EXPECT_EQ(0, exchange_->postponed_.front());
}

// Verify open in second pass with no postponed servers.
TEST_F(ExchangeTest, openNoPostponed) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Put the exchange in the second pass,
    exchange_->idx_ = 1;
    ASSERT_EQ(servers_.size(), exchange_->idx_);
    ASSERT_TRUE(exchange_->postponed_.empty());

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_EQ(1, exchange_->idx_);
    EXPECT_FALSE(exchange_->terminated_);
    EXPECT_FALSE(called_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was called.
    EXPECT_TRUE(exchange_->terminated_);
    EXPECT_TRUE(called_);
}

// Verify open in second pass with bad postponed index.
TEST_F(ExchangeTest, openBadPostponed) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Put the exchange in the second pass,
    exchange_->idx_ = 1;
    ASSERT_EQ(servers_.size(), exchange_->idx_);

    // Add a bad index in the postponed list.
    exchange_->postponed_.push_back(10);

    // Call open.
    EXPECT_THROW_MSG(exchange_->open(), Unexpected,
                     "out of range server 10 >= 1");
}

// Verify open in second pass with null postponed server.
TEST_F(ExchangeTest, openNullPostponed) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    ServerPtr null_server;
    servers_.push_back(null_server);
    createExchange();

    // Put the exchange in the second pass,
    exchange_->idx_ = 1;
    ASSERT_EQ(servers_.size(), exchange_->idx_);

    // Add the null server to the postponed list.
    exchange_->postponed_.push_back(0);

    // Call open.
    EXPECT_THROW_MSG(exchange_->open(), Unexpected, "null server at 0");
}

// Verify open in second pass.
TEST_F(ExchangeTest, openPostponed) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Put the exchange in the second pass,
    exchange_->idx_ = 1;
    ASSERT_EQ(servers_.size(), exchange_->idx_);

    // Add the server to the postponed list.
    exchange_->postponed_.push_back(0);

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_TRUE(exchange_->server_);
    EXPECT_EQ(servers_[0], exchange_->server_);
    EXPECT_EQ(1, exchange_->idx_);
    EXPECT_TRUE(exchange_->sent_);
    EXPECT_TRUE(exchange_->timer_);
    ASSERT_TRUE(exchange_->ep_);
    EXPECT_EQ(addr_.toText(), exchange_->ep_->getAddress().toText());
    EXPECT_EQ(port_, exchange_->ep_->getPort());
    EXPECT_TRUE(exchange_->socket_);
    EXPECT_FALSE(exchange_->buffer_.empty());
    EXPECT_EQ(code_, exchange_->buffer_[0]);
    EXPECT_LT(AUTH_HDR_LEN, exchange_->size_);
    EXPECT_EQ(exchange_->size_, exchange_->buffer_.size());
    EXPECT_FALSE(called_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was not called.
    EXPECT_FALSE(called_);
}

// Verify open with error in send.
TEST_F(ExchangeTest, openSendError) {
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

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_TRUE(exchange_->server_);
    EXPECT_EQ(servers_[0], exchange_->server_);
    EXPECT_EQ(0, exchange_->idx_);
    EXPECT_TRUE(exchange_->sent_);
    EXPECT_FALSE(exchange_->ep_);
    EXPECT_FALSE(exchange_->timer_);
    EXPECT_FALSE(exchange_->socket_);
    EXPECT_EQ(0, exchange_->retries_);
    EXPECT_EQ(ERROR_RC, exchange_->rc_);
}

// Verify open puts on timeout a server on hold-down.
TEST_F(ExchangeTest, openHoldsDown) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    deadtime_ = 60;
    addServer();
    createExchange();

    // Set the exchange on last retry.
    ServerPtr server = servers_[0];
    exchange_->server_ = server;
    exchange_->retries_ = maxretries_;
    server->setDeadtimeEnd(exchange_->start_time_ - seconds(10));

    // Set the error code to timeout.
    exchange_->rc_ = TIMEOUT_RC;

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check server.
    auto dead_time_end = server->getDeadtimeEnd();
    EXPECT_EQ(exchange_->start_time_ + seconds(deadtime_), dead_time_end);
}

// Verify open tries next server after last retry.
TEST_F(ExchangeTest, openNextServer) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    // Add a second server.
    addServer();
    createExchange();

    // Set the exchange on last retry.
    exchange_->server_ = servers_[0];
    exchange_->retries_ = maxretries_;

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check next state.
    EXPECT_EQ(0, exchange_->retries_);
    EXPECT_FALSE(exchange_->server_);
    EXPECT_FALSE(exchange_->ep_);
    EXPECT_EQ(1, exchange_->idx_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was not called.
    EXPECT_FALSE(called_);
}

// Verify open terminates after the last retry of the last server.
TEST_F(ExchangeTest, openLastServer) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    // Add a second server.
    addServer();
    createExchange();

    // Set the exchange on last retry of last server.
    exchange_->server_ = servers_[1];
    exchange_->retries_ = maxretries_;
    exchange_->idx_ = 1;
    ASSERT_EQ(servers_.size(), exchange_->idx_ + 1);
    ASSERT_TRUE(exchange_->postponed_.empty());

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_EQ(2, exchange_->idx_);
    EXPECT_EQ(servers_.size(), exchange_->idx_);
    EXPECT_FALSE(exchange_->terminated_);
    EXPECT_FALSE(called_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was called.
    EXPECT_TRUE(exchange_->terminated_);
    EXPECT_TRUE(called_);
}

// Verify open in second pass tries next postponed server after last retry.
TEST_F(ExchangeTest, openNextPostponedServer) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    // Add a second server.
    addServer();
    createExchange();

    // Put the exchange in the second pass,
    exchange_->idx_ = 2;
    ASSERT_EQ(servers_.size(), exchange_->idx_);

    // Add servers to the postponed list.
    exchange_->postponed_.push_back(0);
    exchange_->postponed_.push_back(1);
    ASSERT_EQ(2, exchange_->postponed_.size());

    // Set the exchange on last retry.
    exchange_->server_ = servers_[0];
    exchange_->retries_ = maxretries_;

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check next state.
    EXPECT_EQ(0, exchange_->retries_);
    EXPECT_FALSE(exchange_->server_);
    EXPECT_FALSE(exchange_->ep_);
    EXPECT_EQ(2, exchange_->idx_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was not called.
    EXPECT_FALSE(called_);
}

// Verify open in second pass terminates after the last retry of the last
// postponed server.
TEST_F(ExchangeTest, openLastPostponedServer) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    // Add a second server.
    addServer();
    createExchange();

    // Put the exchange in the second pass,
    exchange_->idx_ = 2;
    ASSERT_EQ(servers_.size(), exchange_->idx_);
    exchange_->postponed_.push_back(0);

    // Set the exchange on last retry of last server.
    exchange_->server_ = servers_[0];
    exchange_->retries_ = maxretries_;
    ASSERT_EQ(1, exchange_->postponed_.size());

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_EQ(2, exchange_->idx_);
    EXPECT_EQ(servers_.size(), exchange_->idx_);
    EXPECT_FALSE(exchange_->terminated_);
    EXPECT_FALSE(called_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was called.
    EXPECT_TRUE(exchange_->terminated_);
    EXPECT_TRUE(called_);
}

// Verify open retries.
TEST_F(ExchangeTest, openRetry) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Set the exchange to the first server.
    exchange_->server_ = servers_[0];

    // Set the endpoint.
    exchange_->ep_.reset(new UDPEndpoint(addr_, port_));

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_EQ(1, exchange_->retries_);
    EXPECT_TRUE(exchange_->sent_);
    EXPECT_TRUE(exchange_->timer_);
    ASSERT_TRUE(exchange_->ep_);
    EXPECT_EQ(addr_.toText(), exchange_->ep_->getAddress().toText());
    EXPECT_EQ(port_, exchange_->ep_->getPort());
    EXPECT_TRUE(exchange_->socket_);
    EXPECT_FALSE(exchange_->buffer_.empty());
    EXPECT_EQ(code_, exchange_->buffer_[0]);
    EXPECT_LT(AUTH_HDR_LEN, exchange_->size_);
    EXPECT_EQ(exchange_->size_, exchange_->buffer_.size());
    EXPECT_FALSE(called_);

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was not called.
    EXPECT_FALSE(called_);
}

// Verify open with error in retry.
TEST_F(ExchangeTest, openRetryError) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Set the exchange to the first server.
    exchange_->server_ = servers_[0];
    ASSERT_FALSE(exchange_->ep_);

    // Call open.
    ASSERT_NO_THROW_LOG(exchange_->open());

    // Check new state.
    EXPECT_EQ(1, exchange_->retries_);
    EXPECT_FALSE(exchange_->sent_);
    EXPECT_FALSE(exchange_->timer_);
    EXPECT_FALSE(exchange_->socket_);
    EXPECT_EQ(ERROR_RC, exchange_->rc_);
}

// Verify receivedHandler with null exchange.
TEST_F(ExchangeTest, receivedHandlerNull) {
    auto no_error = boost::system::error_code();
    EXPECT_THROW_MSG(TestExchange::receivedHandler(TestExchangePtr(), no_error, 0),
                     Unexpected,
                     "null exchange in receivedHandler");
}

// Verify receivedHandler on error.
TEST_F(ExchangeTest, receivedHandlerError) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    addServer();
    createExchange();

    // Call the handler with an error.
    auto ec = boost::asio::error::timed_out;
    EXPECT_NO_THROW_LOG(TestExchange::receivedHandler(exchange_, ec, 0));

    // Poll the I/O service.
    ASSERT_NO_THROW_LOG(io_service_->poll());

    // Terminate was not called.
    EXPECT_FALSE(called_);
}

// Verify receivedHandler removes servers from hold-down.
TEST_F(ExchangeTest, receivedHandlerNoHoldDown) {
    code_ = PW_ACCESS_REQUEST;
    createRequest();
    deadtime_ = 60;
    addServer();
    createExchange();

    // Put the server in hold-down.
    ServerPtr server = servers_[0];
    server->setDeadtimeEnd(steady_clock().now() + seconds(deadtime_));
    exchange_->server_ = server;

    // Call the handler.
    auto no_error = boost::system::error_code();
    exchange_->sent_ = request_;
    EXPECT_NO_THROW_LOG(TestExchange::receivedHandler(exchange_, no_error, 0));

    // Check the server.
    EXPECT_EQ(exchange_->start_time_, server->getDeadtimeEnd());
}

} // end of anonymous namespace
