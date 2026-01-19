// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>
#include <cryptolink/crypto_hash.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/udp_socket.h>
#include <database/database_connection.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <radius_access.h>
#include <radius_accounting.h>
#include <radius_status.h>
#include <attribute_test.h>
#include <gtest/gtest.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <atomic>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// Fake server.
const char SERVER_ADDRESS[] = "127.0.0.1";
const unsigned short SERVER_AUTH_PORT = 11812;
const unsigned short SERVER_ACCT_PORT = 11813;

/// Configs.
const char* CONFIGS[] = {
    // CONFIGURATION 0
"{\n"
"    \"access\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 11812,\n"
"            \"secret\": \"foo\" } ] },\n"
"    \"accounting\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 11813,\n"
"            \"secret\": \"bar\" } ] },\n"
"    \"retries\": 0,\n"
"    \"timeout\": 1 }\n",
    // CONFIGURATION 1
"{\n"
"    \"access\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 21812,\n"
"            \"secret\": \"foo\"\n"
"        },{\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 11812,\n"
"            \"secret\": \"foo\" } ] },\n"
"    \"accounting\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 21813,\n"
"            \"secret\": \"bar\"\n"
"        },{\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 11813,\n"
"            \"secret\": \"bar\" } ] },\n"
"    \"retries\": 0,\n"
"    \"timeout\": 1 }\n"
};

/// @brief Class for callbacks.
class Callback {
public:

    /// @brief Constructor.
    ///
    /// @param error_code Reference to the error code.
    /// @param size Reference to the returned size.
    /// @param flag Reference to called flag.
    Callback(boost::system::error_code& error_code,
             size_t& size, atomic<bool>& flag)
        : error_code_(error_code), size_(size), called_(flag) { }

    /// @brief Callback.
    ///
    /// @param ec Error code.
    void operator()(boost::system::error_code ec) {
        error_code_ = ec;
        size_ = 0;
        called_ = true;
    }

    /// @brief Callback.
    ///
    /// @param ec Error code.
    /// @param size Size.
    void operator()(boost::system::error_code ec, size_t size) {
        error_code_ = ec;
        size_ = size;
        called_ = true;
    }

    /// @brief Error code.
    boost::system::error_code& error_code_;

    /// @brief Size.
    size_t& size_;

    /// @brief Called flag.
    atomic<bool>& called_;
};

/// @brief Test fixture for testing synchronous communication for
/// the radius library.
class StatusTest : public radius::test::AttributeTest {
public:

    /// @brief Thread pointer type.
    typedef boost::shared_ptr<thread> ThreadPtr;

    /// @brief Constructor.
    StatusTest() :
        radius::test::AttributeTest(),
        impl_(RadiusImpl::instance()), service_(new IOService()),
        server_socket_(service_->getInternalIOService()),
        receive_buffer_(4096), receive_error_code_(), received_(false),
        send_buffer_(), send_error_code_(), sent_(false),
        timer_(service_), timeout_(false), which_(""),
        send_attributes_(), result_(OK_RC), thread_(),
        handler_auth_(), handler_acct_(), finished_(false) {

        HostMgr::create();
        auto factory = [] (const isc::db::DatabaseConnection::ParameterMap&) {
            return (HostDataSourcePtr());
        };
        HostDataSourceFactory::registerFactory("cache", factory);

        impl_.reset();
        impl_.setIOService(service_);
        impl_.setIOContext(service_);
    }

    /// @brief Destructor
    virtual ~StatusTest() {
        stop();
        close();
        if (thread_) {
            thread_->join();
            thread_.reset();
        }

        // As a best practice, call any remaining handlers.
        service_->stopAndPoll();
        HostDataSourceFactory::deregisterFactory("cache");
    }

    /// @brief Poll the I/O service.
    /// From boost asio documentation: check if a handler is ready
    /// and when there is one execute it.
    void poll();

    /// @brief Open fake server socket.
    ///
    /// @param server_port UDP server port.
    void open(unsigned short server_port);

    /// @brief Close fake server socket.
    void close();

    /// @brief Timeout callback.
    void timeout();

    /// @brief Start timer.
    ///
    /// @param deadline Maximum time the test can run in milliseconds.
    void start(long deadline);

    /// @brief Stop timer.
    void stop();

    /// @brief Done handler.
    ///
    /// @param result The result of the request.
    void done(int result);

    /// @brief Run a request handler i.e. the client part.
    /// The server side is simulated by the individual test code.
    void run();

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    /// @brief IO service.
    IOServicePtr service_;

    /// @brief Fake server socket (ASIO because asiolink has no bind()).
    boost::asio::ip::udp::socket server_socket_;

    /// @brief Receive buffer.
    vector<uint8_t> receive_buffer_;

    /// @brief Receive error code.
    boost::system::error_code receive_error_code_;

    /// @brief Received flag.
    atomic<bool> received_;

    /// @brief Send buffer.
    vector<uint8_t> send_buffer_;

    /// @brief Send error code.
    boost::system::error_code send_error_code_;

    /// @brief Sent flag.
    atomic<bool> sent_;

    /// @brief Timer for timeout.
    IntervalTimer timer_;

    /// @brief Timeout flag.
    atomic<bool> timeout_;

    /// @brief Fake server type: Authentication ("access") or
    /// Accounting ("accounting").
    string which_;

    /// @brief Attributes to send.
    AttributesPtr send_attributes_;

    /// @brief Request result.
    int result_;

    /// @brief Thread.
    ThreadPtr thread_;

    /// @brief Handler for authentication.
    RadiusAuthStatusPtr handler_auth_;

    /// @brief Handler for accounting..
    RadiusAcctStatusPtr handler_acct_;

    /// @brief Finished flag.
    atomic<bool> finished_;
};

void
StatusTest::poll() {
    service_->poll();
    EXPECT_NO_THROW(IfaceMgr::instance().receive4(0, 1000));
}

void
StatusTest::open(unsigned short server_port) {
    // Get the socket.
    boost::system::error_code ec;
    server_socket_.open(boost::asio::ip::udp::v4(), ec);
    ASSERT_FALSE(ec);

    // Get the address.
    boost::asio::ip::address server_address =
        boost::asio::ip::make_address(SERVER_ADDRESS, ec);
    ASSERT_FALSE(ec);

    // Get the endpoint.
    boost::asio::ip::udp::endpoint server_endpoint =
        boost::asio::ip::udp::endpoint(server_address, server_port);

    // Bind the socket.
    server_socket_.bind(server_endpoint, ec);
    if (ec) {
        FAIL() << "bind failed: " << ec.message();
    }
}

void
StatusTest::close() {
    if (server_socket_.is_open()) {
        EXPECT_NO_THROW(server_socket_.close());
    }
}

void
StatusTest::timeout() {
    timeout_ = true;
    FAIL() << "timeout";
}

void
StatusTest::start(long deadline) {
    timer_.setup(std::bind(&StatusTest::timeout, this),
                 deadline, IntervalTimer::ONE_SHOT);
}

void
StatusTest::stop() {
    timer_.cancel();
}

void
StatusTest::done(int result) {
    result_ = result;
    finished_ = true;
}

void
StatusTest::run() {
    if (which_ == "access") {
        handler_auth_.reset(new RadiusAuthStatus(send_attributes_,
                                                 std::bind(&StatusTest::done,
                                                           this, ph::_1)));
        handler_auth_->start();
    } else if (which_ == "accounting") {
        handler_acct_.reset(new RadiusAcctStatus(send_attributes_,
                                                 std::bind(&StatusTest::done,
                                                           this, ph::_1)));
        handler_acct_->start();
    } else {
        FAIL() << "which is not 'access' nor 'accounting'";
    }
}

/// Verify what happens when there is no listening authentication server at all.
TEST_F(StatusTest, noAuthServer) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!finished_ && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_FALSE(timeout_);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(TIMEOUT_RC, result_);
}

/// Verify what happens when there is no listening accounting server at all.
TEST_F(StatusTest, noAcctServer) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!finished_ && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_FALSE(timeout_);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(TIMEOUT_RC, result_);
}

/// Verify what happens when no response is sent.
TEST_F(StatusTest, noAuthResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while ((!received_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(received_);
    EXPECT_FALSE(timeout_);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(TIMEOUT_RC, result_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_STATUS_SERVER, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    ASSERT_LE(length, size);
    EXPECT_GE(4096, length);
}

/// Verify what happens when no response is sent.
TEST_F(StatusTest, noAcctResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while ((!received_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(received_);
    EXPECT_FALSE(timeout_);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(TIMEOUT_RC, result_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_STATUS_SERVER, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    ASSERT_LE(length, size);
    EXPECT_GE(4096, length);
}

/// Verify what happens with Access-Accept response.
TEST_F(StatusTest, accept) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                  // header.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_ACCEPT;   // Access-Accept.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'f';
    auth_input[size + 1] = 'o';
    auth_input[size + 2] = 'o';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with Access-Reject response.
TEST_F(StatusTest, reject) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                  // header
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_REJECT;   // Access-Reject.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'f';
    auth_input[size + 1] = 'o';
    auth_input[size + 2] = 'o';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with Accounting-Response response.
TEST_F(StatusTest, response) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                       // header (no attributes).
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
    send_buffer_[1] = receive_buffer_[1];      // Copy id.
    send_buffer_[2] = size >> 8;               // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'b';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'r';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with error Accounting-Response response.
/// Should log a RADIUS_ACCOUNTING_STATUS_ERROR with
/// Accounting-Response (5) with Error-Cause=Unsupported-Extension
TEST_F(StatusTest, errorResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN + 2 + 4;               // header + Error-Cause attribute.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
    send_buffer_[1] = receive_buffer_[1];      // Copy id.
    send_buffer_[2] = size >> 8;               // Length.
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);
    // Error-Cause attribute.
    send_buffer_[AUTH_HDR_LEN] = 0x65;         // Error-Cause (101)
    send_buffer_[AUTH_HDR_LEN + 1] = 0x06;     // Length.
    send_buffer_[AUTH_HDR_LEN + 2] = 0x00;
    send_buffer_[AUTH_HDR_LEN + 3] = 0x00;
    send_buffer_[AUTH_HDR_LEN + 4] = 0x01;
    send_buffer_[AUTH_HDR_LEN + 5] = 0x96;     // Unsupported Extension (406).

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'b';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'r';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with bad Access-Accept response.
TEST_F(StatusTest, badAccept) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                  // header.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_ACCEPT;   // Access-Accept.
    // There are a lot of ways to get an error including this one.
    send_buffer_[1] = receive_buffer_[1] ^ 0x12;
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'f';
    auth_input[size + 1] = 'o';
    auth_input[size + 2] = 'o';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad Accounting-Response response.
TEST_F(StatusTest, badResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                       // header (no attributes).
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
    // There are a lot of ways to get an error including this one.
    send_buffer_[1] = receive_buffer_[1] ^ 21;
    send_buffer_[2] = size >> 8;               // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'b';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'r';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad (too short) response.
TEST_F(StatusTest, shortAuth) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                  // header.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_ACCEPT;   // Access-Accept.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'f';
    auth_input[size + 1] = 'o';
    auth_input[size + 2] = 'o';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    // Change the size.
    Callback send_callback(send_error_code_, sent_size, sent_);
    // Truncate the buffer.
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], 10),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(10, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad (too short) response.
TEST_F(StatusTest, shortAcct) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                       // header (no attributes).
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
    // There are a lot of ways to get an error including this one.
    send_buffer_[1] = receive_buffer_[1];      // Copy id.
    send_buffer_[2] = size >> 8;               // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'b';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'r';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    // Truncate the buffer.
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], 10),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(10, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with a backup authentication server.
TEST_F(StatusTest, accept2) {
    // Use CONFIGS[1].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[1]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                  // header.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_ACCEPT;   // Access-Accept.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'f';
    auth_input[size + 1] = 'o';
    auth_input[size + 2] = 'o';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with a backup accounting server.
TEST_F(StatusTest, response2) {
    // Use CONFIGS[1].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[1]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Sanity checks on the request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);

    // Build the response.
    size = AUTH_HDR_LEN;                       // header (no attributes).
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
    send_buffer_[1] = receive_buffer_[1];      // Copy id.
    send_buffer_[2] = size >> 8;               // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'b';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'r';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    server_socket_.async_send_to(boost::asio::buffer(&send_buffer_[0], size),
                                 client, send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify that access IdleTimerCallback works as expected.
TEST_F(StatusTest, accessIdleTimerCallback) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Call the access IdleTimerCallback.
    RadiusAccess::IdleTimerCallback();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_STATUS_SERVER, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    EXPECT_EQ(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(44, size);
    EXPECT_EQ(PW_MESSAGE_AUTHENTICATOR, receive_buffer_[AUTH_HDR_LEN]);
    EXPECT_EQ(AUTH_VECTOR_LEN + 2, receive_buffer_[AUTH_HDR_LEN + 1]);
    uint8_t expected[] = {
        0x04,                   // NAS-IP-Address
        0x06,                   // length
        0x7f, 0x00, 0x00, 0x01  // 127.0.0.1
    };
    EXPECT_EQ(0, memcmp(expected, &receive_buffer_[AUTH_HDR_LEN + 18], 6));
}

/// Verify that accounting IdleTimerCallback works as expected.
TEST_F(StatusTest, accountingIdleTimerCallback) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Call the accounting IdleTimerCallback.
    RadiusAccounting::IdleTimerCallback();

    // Start timer for 1.5s timeout.
    start(1500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_STATUS_SERVER, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    EXPECT_EQ(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(44, size);
    EXPECT_EQ(PW_MESSAGE_AUTHENTICATOR, receive_buffer_[AUTH_HDR_LEN]);
    EXPECT_EQ(AUTH_VECTOR_LEN + 2, receive_buffer_[AUTH_HDR_LEN + 1]);
    uint8_t expected[] = {
        0x04,                   // NAS-IP-Address
        0x06,                   // length
        0x7f, 0x00, 0x00, 0x01  // 127.0.0.1
    };
    EXPECT_EQ(0, memcmp(expected, &receive_buffer_[AUTH_HDR_LEN + 18], 6));
}

/// Verify that access idle timer works as expected.
TEST_F(StatusTest, accessIdleTimer) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));
    ASSERT_TRUE(impl_.auth_);
    impl_.auth_->idle_timer_interval_ = 1;

    // Open server socket.
    open(SERVER_AUTH_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Set the idle timer.
    impl_.auth_->setIdleTimer();

    // Start timer for 2.5s timeout.
    start(2500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_STATUS_SERVER, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    EXPECT_EQ(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(44, size);
    EXPECT_EQ(PW_MESSAGE_AUTHENTICATOR, receive_buffer_[AUTH_HDR_LEN]);
    EXPECT_EQ(AUTH_VECTOR_LEN + 2, receive_buffer_[AUTH_HDR_LEN + 1]);
    uint8_t expected[] = {
        0x04,                   // NAS-IP-Address
        0x06,                   // length
        0x7f, 0x00, 0x00, 0x01  // 127.0.0.1
    };
    EXPECT_EQ(0, memcmp(expected, &receive_buffer_[AUTH_HDR_LEN + 18], 6));
}

/// Verify that accounting idle timer works as expected.
TEST_F(StatusTest, accountingIdleTimer) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));
    ASSERT_TRUE(impl_.acct_);
    impl_.acct_->idle_timer_interval_ = 1;

    // Open server socket.
    open(SERVER_ACCT_PORT);

    // Push a receiver on it.
    boost::asio::ip::udp::endpoint client;
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_socket_.async_receive_from(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        client, receive_callback);

    // Set the idle timer.
    impl_.acct_->setIdleTimer();

    // Start timer for 2.5s timeout.
    start(2500);

    // Busy loop.
    while (!received_ && !timeout_) {
        poll();
    }

    ASSERT_TRUE(received_);
    ASSERT_FALSE(timeout_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_STATUS_SERVER, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    EXPECT_EQ(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(44, size);
    EXPECT_EQ(PW_MESSAGE_AUTHENTICATOR, receive_buffer_[AUTH_HDR_LEN]);
    EXPECT_EQ(AUTH_VECTOR_LEN + 2, receive_buffer_[AUTH_HDR_LEN + 1]);
    uint8_t expected[] = {
        0x04,                   // NAS-IP-Address
        0x06,                   // length
        0x7f, 0x00, 0x00, 0x01  // 127.0.0.1
    };
    EXPECT_EQ(0, memcmp(expected, &receive_buffer_[AUTH_HDR_LEN + 18], 6));
}

} // end of anonymous namespace
