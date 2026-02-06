// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
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

#include <attribute_test.h>
#include <cryptolink/crypto_hash.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_socket.h>
#include <asiolink/testutils/test_tls.h>
#include <database/database_connection.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <radius.h>
#include <radius_request.h>
#include <radius_tls.h>
#include <tcp/tcp_client.h>

#include <gtest/gtest.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <atomic>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::tcp;
using namespace isc::util;
namespace ph = std::placeholders;
namespace ba = boost::asio::ip;

namespace {

/// Fake server.
const char SERVER_ADDRESS[] = "::1";
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
"            \"name\": \"::1\",\n"
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
class TlsRequestTest : public radius::test::AttributeTest {
public:

    /// @brief Constructor.
    TlsRequestTest() :
        radius::test::AttributeTest(),
        impl_(RadiusImpl::instance()), service_(new IOService()),
        server_ep_(ba::make_address(SERVER_ADDRESS), SERVER_PORT),
        server_ctx_(), acceptor_(service_->getInternalIOService(), server_ep_),
        server_(), accept_error_code_(), accepted_(false),
        handshake_error_code_(), handshake_(false),
        receive_buffer_(4096), receive_error_code_(), received_(false),
        send_buffer_(), send_error_code_(), sent_(false),
        timer_(service_), timeout_(false), which_(""),
        subnet_id_(SUBNET_ID_UNUSED), send_attributes_(),
        result_(OK_RC), received_attributes_(),
        handler_auth_(), handler_acct_(), finished_(false) {

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

        impl_.tcp_client_.reset(new TcpClient(service_, false, 0));
    }

    /// @brief Destructor
    virtual ~TlsRequestTest() {
        timer_stop();
        server_close();

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
        handshake_error_code_ = ec;
    }

    /// @brief Poll the I/O service.
    /// From boost asio documentation: check if a handler is ready
    /// and when there is one execute it.
    void poll();

    /// @brief Fake server accept new connection on the socket.
    void server_accept();

    /// @brief Fake server handshake.
    void server_handshake();

    /// @brief Close fake server socket.
    void server_close();

    /// @brief Timeout callback.
    void timeout();

    /// @brief Start timer.
    ///
    /// @param deadline Maximum time the test can run in milliseconds.
    void timer_start(long deadline);

    /// @brief Stop timer.
    void timer_stop();

    /// @brief Done authentication handler.
    ///
    /// @param handler Handler to the RadiusAsyncAuth.
    void doneAuth(int result, AttributesPtr received);

    /// @brief Done accounting handler.
    ///
    /// @param handler Handler to the RadiusAsyncAcct.
    void doneAcct(int result);

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

    /// @brief Fake server type: Authentication ("access") or
    /// Accounting ("accounting").
    string which_;

    /// @brief Subnet ID (aka client/NAS port).
    uint32_t subnet_id_;

    /// @brief Attributes to send.
    AttributesPtr send_attributes_;

    /// @brief Request result.
    int result_;

    /// @brief Received attributes.
    AttributesPtr received_attributes_;

    /// @brief Handler for authentication.
    RadiusAsyncAuthPtr handler_auth_;

    /// @brief Handler for accounting..
    RadiusAsyncAcctPtr handler_acct_;

    /// @brief Finished flag.
    atomic<bool> finished_;
};

void
TlsRequestTest::poll() {
    service_->poll();
    EXPECT_NO_THROW(IfaceMgr::instance().receive4(0, 1000));
}

void
TlsRequestTest::server_accept() {
    // Accept new connection on the fake server socket.
    acceptor_.async_accept(server_->lowest_layer(),
                           std::bind(&TlsRequestTest::acceptCallback,
                                     this, ph::_1));
}

void
TlsRequestTest::server_handshake() {
    server_->async_handshake(roleToImpl(TlsRole::SERVER),
                             std::bind(&TlsRequestTest::handshakeCallback,
                                       this, ph::_1));
}

void
TlsRequestTest::server_close() {
    if (server_) {
        EXPECT_NO_THROW(server_->lowest_layer().close());
    }
    server_.reset();
    acceptor_.close();
}

void
TlsRequestTest::timeout() {
    timeout_ = true;
    FAIL() << "timeout";
}

void
TlsRequestTest::timer_start(long deadline) {
    timer_.setup(std::bind(&TlsRequestTest::timeout, this),
                 deadline, IntervalTimer::ONE_SHOT);
}

void
TlsRequestTest::timer_stop() {
    timer_.cancel();
}

void
TlsRequestTest::doneAuth(int result, AttributesPtr received) {
    result_ = result;
    received_attributes_ = received;
    finished_ = true;
}

void
TlsRequestTest::doneAcct(int result) {
    result_ = result;
    finished_ = true;
}

void
TlsRequestTest::run() {
    if (which_ == "access") {
        handler_auth_.reset(new RadiusAsyncAuth(subnet_id_,
                                send_attributes_,
                                std::bind(&TlsRequestTest::doneAuth,
                                          this, ph::_1, ph::_2)));
        handler_auth_->start();
    } else if (which_ == "accounting") {
        handler_acct_.reset(new RadiusAsyncAcct(subnet_id_,
                                send_attributes_,
                                std::bind(&TlsRequestTest::doneAcct,
                                          this, ph::_1)));
        handler_acct_->start();
    } else {
        FAIL() << "which is not 'access' nor 'accounting'";
    }
}

/// Verify what happens when there is no listening server at all.
TEST_F(TlsRequestTest, noServer) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    EXPECT_FALSE(received_attributes_);
    EXPECT_EQ(TIMEOUT_RC, result_);
}

/// Verify what happens when no response is sent.
TEST_F(TlsRequestTest, noResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    EXPECT_EQ(PW_ACCOUNTING_REQUEST, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    ASSERT_LE(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(56, size);
    uint8_t expected[] = {
        0x01, // User-Name
        0x06, // length
        0x75, 0x73, 0x65, 0x72, // "user"
        0x05, // NAS-Port
        0x06, // length
        0x00, 0x00, 0x00, 0x01, // 1
        0x29, // Acct-Delay-Time
        0x06, // length
        0x00, 0x00, 0x00, 0x00, // 0
        0x5f, // NAS-IPv6-Address
        0x12, // length
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01 // ::1
    };
    size_t expected_len = size - AUTH_HDR_LEN;
    if (expected_len > sizeof(expected)) {
        expected_len = sizeof(expected);
    }
    EXPECT_EQ(0, memcmp(expected,
                        &receive_buffer_[AUTH_HDR_LEN],
                        expected_len));

    // Check authenticator.
    vector<unsigned char> auth_input(size + 6);
    memmove(&auth_input[0], &receive_buffer_[0], size);
    memset(&auth_input[4], 0, AUTH_VECTOR_LEN);
    auth_input[size] = 'r';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'd';
    auth_input[size + 3] = 's';
    auth_input[size + 4] = 'e';
    auth_input[size + 5] = 'c';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 6, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    EXPECT_EQ(0, memcmp(auth_output.getData(),
                        &receive_buffer_[4],
                        AUTH_VECTOR_LEN));
}

/// Verify what happens with Access-Accept response.
TEST_F(TlsRequestTest, accept) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    ASSERT_LE(26, size);

    // Build the response.
    size = AUTH_HDR_LEN + 2 + 4;          // header + User-Name attribute.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_ACCEPT;   // Access-Accept.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);
    // Copy the User-Name attribute.
    memmove(&send_buffer_[AUTH_HDR_LEN], &receive_buffer_[AUTH_HDR_LEN], 6);

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
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

/// Verify what happens with Accounting-Response response.
TEST_F(TlsRequestTest, response) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
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

/// Verify what happens with bad Access-Accept response.
TEST_F(TlsRequestTest, badAccept) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    ASSERT_LE(26, size);

    // Build the response.
    size = AUTH_HDR_LEN + 2 + 4;          // header + User-Name attribute.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_ACCEPT;   // Access-Accept.
    // There are a lot of ways to get an error including this one.
    send_buffer_[1] = receive_buffer_[1] ^ 0x12;
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);
    // Copy the User-Name attribute.
    memmove(&send_buffer_[AUTH_HDR_LEN], &receive_buffer_[AUTH_HDR_LEN], 6);

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
    EXPECT_EQ(BADRESP_RC, result_);
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

/// Verify what happens with bad Accounting-Response response.
TEST_F(TlsRequestTest, badResponse) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
    // There are a lot of ways to get an error including this one.
    send_buffer_[1] = receive_buffer_[1] ^ 21;
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
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad (too short) response.
TEST_F(TlsRequestTest, tooShort) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    send_buffer_[0] = PW_ACCOUNTING_RESPONSE;  // Access-Accept.
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
    // Truncate the buffer.
    boost::asio::async_write(*server_,
                             boost::asio::buffer(&send_buffer_[0], size - 2),
                             send_callback);

    // Second busy loop.
    while ((!sent_ || !finished_) && !timeout_) {
        poll();
    }

    EXPECT_TRUE(finished_);
    EXPECT_TRUE(sent_);
    EXPECT_FALSE(timeout_);
    EXPECT_EQ(size - 2, sent_size);

    // Done.
    timer_stop();
    service_->stopWork();

    // Check result.
    EXPECT_EQ(TIMEOUT_RC, result_);
}

/// Verify what happens with Access-Reject response.
TEST_F(TlsRequestTest, reject) {
    // Use CONFIGS[0].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[0]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
    ASSERT_LE(26, size);

    // Build the response.
    size = AUTH_HDR_LEN + 2 + 4;          // header + User-Name attribute.
    send_buffer_.resize(size);
    send_buffer_[0] = PW_ACCESS_REJECT;   // Access-Reject.
    send_buffer_[1] = receive_buffer_[1]; // Copy id.
    send_buffer_[2] = size >> 8;          // Length
    send_buffer_[3] = size & 0xff;
    // Copy the authenticator.
    memmove(&send_buffer_[4], &receive_buffer_[4], AUTH_VECTOR_LEN);
    // Copy the User-Name attribute.
    memmove(&send_buffer_[AUTH_HDR_LEN], &receive_buffer_[AUTH_HDR_LEN], 6);

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
    EXPECT_EQ(REJECT_RC, result_);
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

} // end of anonymous namespace
