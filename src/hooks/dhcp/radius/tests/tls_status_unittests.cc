// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cryptolink/crypto_hash.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_socket.h>
#include <asiolink/testutils/test_tls.h>
#include <database/database_connection.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <radius.h>
#include <radius_status.h>
#include <attribute_test.h>
#include <gtest/gtest.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <atomic>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::util;
namespace ph = std::placeholders;
namespace ba = boost::asio::ip;

namespace {

/// Fake server.
const char SERVER_ADDRESS[] = "127.0.0.1";
const unsigned short SERVER_PORT = 12083;

/// Configs.
const char* CONFIGS[] = {
    // CONFIGURATION 0
"{\n"
"    \"access\": {\n"
"        \"enabled\": true\n"
"    },\n"
"    \"accounting\": {\n"
"        \"enabled\": true\n"
"    },\n"
"    \"common-tls\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 12083,\n"
"            \"trust-anchor\": \"" TEST_CA_DIR "\",\n"
"            \"cert-file\": \"" TEST_CA_DIR "/kea-client.crt\",\n"
"            \"key-file\": \"" TEST_CA_DIR "/kea-client.key\"\n"
"        } ]\n"
"    },\n"
"    \"protocol\": \"TLS\",\n"
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
class TlsStatusTest : public radius::test::AttributeTest {
public:

    /// @brief Thread pointer type.
    typedef boost::shared_ptr<thread> ThreadPtr;

    /// @brief Constructor.
    TlsStatusTest() :
        radius::test::AttributeTest(),
        impl_(RadiusImpl::instance()), service_(new IOService()),
        server_ep_(ba::tcp::v4(), SERVER_PORT), server_ctx_(),
        acceptor_(service_->getInternalIOService(), server_ep_),
        server_(), accept_error_code_(), accepted_(false),
        handshake_error_code_(), handshake_(false),
        receive_buffer_(4096), receive_error_code_(), received_(false),
        send_buffer_(), send_error_code_(), sent_(false),
        timer_(service_), timeout_(false),
        send_attributes_(), result_(OK_RC), thread_(),
        handler_(), finished_(false) {

        acceptor_.set_option(ba::tcp::acceptor::reuse_address(true));
        asiolink::test::configServer(server_ctx_);
        server_.reset(new TlsStreamImpl(service_->getInternalIOService(),
                                        server_ctx_->getContext()));
        HostMgr::create();
        auto factory = [] (const isc::db::DatabaseConnection::ParameterMap&) {
            return (HostDataSourcePtr());
        };
        HostDataSourceFactory::registerFactory("cache", factory);

        impl_.reset();
        impl_.setIOService(service_);
        impl_.setIOContext(service_);
        impl_.tcp_client_.reset(new isc::tcp::TcpClient(service_, false, 0));
    }

    /// @brief Destructor
    virtual ~TlsStatusTest() {
        timer_stop();
        server_close();
        if (thread_) {
            thread_->join();
            thread_.reset();
        }

        // As a best practice, call any remaining handlers.
        service_->stopAndPoll();
        HostDataSourceFactory::deregisterFactory("cache");
    }

    // Accept callback.
    void acceptCallback(const boost::system::error_code& ec) {
        accepted_ = true;
        accept_error_code_ = ec;
    }

    // Handshake callback.
    void handshakeCallback(const boost::system::error_code& ec) {
        handshake_ = true;
        handshake_error_code_ =  ec;
    }

    /// @brief Poll the I/O service.
    ///
    /// From boost asio documentation: check if a handler is ready
    /// and when there is one execute it.
    void poll();

    /// @brief Fake server accept new connection on the socket.
    void server_accept();

    /// @brief Fake server handshake.
    void server_handshake();

    /// @brief Close fake server socket and acceptor.
    void server_close();

    /// @brief Timeout callback.
    void timeout();

    /// @brief Start timer.
    ///
    /// @param deadline Maximum time the test can run in milliseconds.
    void timer_start(long deadline);

    /// @brief Stop timer.
    void timer_stop();

    /// @brief Done handler.
    ///
    /// @param result The result of the request.
    void done(int result);

    /// @brief Run a request handler i.e. the client part.
    ///
    /// The server side is simulated by the individual test code.
    void run();

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    /// @brief IO service.
    IOServicePtr service_;

    /// @brief Fake server endpoint.
    ba::tcp::endpoint server_ep_;

    /// @brief Fake server TLS context.
    TlsContextPtr server_ctx_;

    /// @brief Fake server acceptor.
    ba::tcp::acceptor acceptor_;

    /// @brief Fake server socket.
    boost::scoped_ptr<TlsStreamImpl> server_;

     /// @brief Accept error code.
    boost::system::error_code accept_error_code_;

    /// @brief Accepted flag.
    atomic<bool> accepted_;

    /// @brief Handshake error code.
    boost::system::error_code handshake_error_code_;

    /// @brief Handshake flag.
    atomic<bool> handshake_;

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

    /// @brief Attributes to send.
    AttributesPtr send_attributes_;

    /// @brief Request result.
    int result_;

    /// @brief Thread.
    ThreadPtr thread_;

    /// @brief Handler.
    RadiusTlsStatusPtr handler_;

    /// @brief Finished flag.
    atomic<bool> finished_;
};

void
TlsStatusTest::poll() {
    service_->poll();
}

void
TlsStatusTest::server_accept() {
    // Accept new connection on the fake server socket.
    acceptor_.async_accept(server_->lowest_layer(),
                           std::bind(&TlsStatusTest::acceptCallback,
                                     this, ph::_1));
}

void
TlsStatusTest::server_handshake() {
    server_->async_handshake(roleToImpl(TlsRole::SERVER),
                             std::bind(&TlsStatusTest::handshakeCallback,
                                       this, ph::_1));
}

void
TlsStatusTest::server_close() {
    if (server_) {
        EXPECT_NO_THROW(server_->lowest_layer().close());
    }
    server_.reset();
    acceptor_.close();
}

void
TlsStatusTest::timeout() {
    timeout_ = true;
    FAIL() << "timeout";
}

void
TlsStatusTest::timer_start(long deadline) {
    timer_.setup(std::bind(&TlsStatusTest::timeout, this),
                 deadline, IntervalTimer::ONE_SHOT);
}

void
TlsStatusTest::timer_stop() {
    timer_.cancel();
}

void
TlsStatusTest::done(int result) {
    result_ = result;
    finished_ = true;
}

void
TlsStatusTest::run() {
    handler_.reset(new RadiusTlsStatus(send_attributes_,
                                       std::bind(&TlsStatusTest::done,
                                                 this, ph::_1)));
    handler_->start();
}

/// Verify what happens when there is no listening server at all.
TEST_F(TlsStatusTest, noServer) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    timer_start(1500);

    // Busy loop.
    while (!finished_ && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_FALSE(timeout_);

    // Done.
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(TIMEOUT_RC, result_);
}

/// Verify what happens when no response is sent.
TEST_F(TlsStatusTest, noResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Start timer for 1.5s timeout.
    timer_start(1500);

    // Accept server socket.
    server_accept();

    // Launch request handler i.e. the client code to test.
    run();

    // Wait for the connection to be established.
    while (!accepted_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(accept_error_code_);

    // Perform handshake.
    server_handshake();
    while (!handshake_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(handshake_error_code_);

    // Push a receiver on the socket.
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_->async_read_some(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        receive_callback);

    // Busy loop.
    while ((!received_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(received_);
    EXPECT_FALSE(timeout_);

    // Done.
    timer_stop();
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
TEST_F(TlsStatusTest, accept) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Start timer for 1.5s timeout.
    timer_start(1500);

    // Accept server socket.
    server_accept();

    // Launch request handler i.e. the client code to test.
    run();

    // Wait for the connection to be established.
    while (!accepted_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(accept_error_code_);

    // Perform handshake.
    server_handshake();
    while (!handshake_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(handshake_error_code_);

    // Push a receiver on the socket.
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_->async_read_some(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        receive_callback);

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
    vector<unsigned char> auth_input(size + 6);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'r';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'd';
    auth_input[size + 3] = 's';
    auth_input[size + 4] = 'e';
    auth_input[size + 5] = 'c';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 6, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    boost::asio::async_write(*server_,
                             boost::asio::buffer(&send_buffer_[0], size),
                             send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with Access-Reject response.
TEST_F(TlsStatusTest, reject) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Start timer for 1.5s timeout.
    timer_start(1500);

    // Accept server socket.
    server_accept();

    // Launch request handler i.e. the client code to test.
    run();

    // Wait for the connection to be established.
    while (!accepted_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(accept_error_code_);

    // Perform handshake.
    server_handshake();
    while (!handshake_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(handshake_error_code_);

    // Push a receiver on the socket.
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_->async_read_some(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        receive_callback);

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
    send_buffer_[0] = PW_ACCESS_REJECT;   // Access-Reject.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 6);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'r';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'd';
    auth_input[size + 3] = 's';
    auth_input[size + 4] = 'e';
    auth_input[size + 5] = 'c';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 6, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    boost::asio::async_write(*server_,
                             boost::asio::buffer(&send_buffer_[0], size),
                             send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with Accounting-Response response.
TEST_F(TlsStatusTest, response) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Start timer for 1.5s timeout.
    timer_start(1500);

    // Accept server socket.
    server_accept();

    // Launch request handler i.e. the client code to test.
    run();

    // Wait for the connection to be established.
    while (!accepted_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(accept_error_code_);

    // Perform handshake.
    server_handshake();
    while (!handshake_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(handshake_error_code_);

    // Push a receiver on the socket.
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_->async_read_some(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        receive_callback);

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Accounting-Response.
    send_buffer_[1] = receive_buffer_[1];      // Copy id.
    send_buffer_[2] = size >> 8;               // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);

    // Compute the authenticator.
    vector<unsigned char> auth_input(size + 6);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'r';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'd';
    auth_input[size + 3] = 's';
    auth_input[size + 4] = 'e';
    auth_input[size + 5] = 'c';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 6, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    boost::asio::async_write(*server_,
                             boost::asio::buffer(&send_buffer_[0], size),
                             send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}

/// Verify what happens with error Accounting-Response response.
/// Should log a RADIUS_ACCOUNTING_STATUS_ERROR with
/// Accounting-Response (5) with Error-Cause=Unsupported-Extension
TEST_F(TlsStatusTest, errorResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Start timer for 1.5s timeout.
    timer_start(1500);

    // Accept server socket.
    server_accept();

    // Launch request handler i.e. the client code to test.
    run();

    // Wait for the connection to be established.
    while (!accepted_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(accept_error_code_);

    // Perform handshake.
    server_handshake();
    while (!handshake_) {
        ASSERT_FALSE(timeout_);
        poll();
    }
    ASSERT_FALSE(handshake_error_code_);

    // Push a receiver on the socket.
    size_t size = 0;
    Callback receive_callback(receive_error_code_, size, received_);
    server_->async_read_some(
        boost::asio::buffer(&receive_buffer_[0], receive_buffer_.size()),
        receive_callback);

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Accounting-Response.
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
    vector<unsigned char> auth_input(size + 6);
    memmove(&auth_input[0], &send_buffer_[0], size);
    auth_input[size] = 'r';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'd';
    auth_input[size + 3] = 's';
    auth_input[size + 4] = 'e';
    auth_input[size + 5] = 'c';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 6, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    memmove(&send_buffer_[4], auth_output.getData(), AUTH_VECTOR_LEN);

    // Push a sender on the socket.
    size_t sent_size = 0;
    Callback send_callback(send_error_code_, sent_size, sent_);
    boost::asio::async_write(*server_,
                             boost::asio::buffer(&send_buffer_[0], size),
                             send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size, sent_size);

    // Done.
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(OK_RC, result_);
}
#if 0
/// Verify what happens with bad Access-Accept response.
TEST_F(TlsStatusTest, badAccept) {
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

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    timer_start(1500);

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
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad Accounting-Response response.
TEST_F(TlsStatusTest, badResponse) {
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

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    timer_start(1500);

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Accounting-Response.
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
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad (too short) response.
TEST_F(TlsStatusTest, shortAuth) {
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

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    timer_start(1500);

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
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad (too short) response.
TEST_F(TlsStatusTest, shortAcct) {
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

    // Launch request handler i.e. the client code to test.
    run();

    // Start timer for 1.5s timeout.
    timer_start(1500);

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Accounting-Response.
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
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify that access IdleTimerCallback works as expected.
TEST_F(TlsStatusTest, accessIdleTimerCallback) {
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
    timer_start(1500);

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
TEST_F(TlsStatusTest, accountingIdleTimerCallback) {
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
    timer_start(1500);

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
TEST_F(TlsStatusTest, accessIdleTimer) {
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
    timer_start(2500);

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
TEST_F(TlsStatusTest, accountingIdleTimer) {
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
    timer_start(2500);

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
#endif
} // end of anonymous namespace
