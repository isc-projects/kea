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

#include <cryptolink/crypto_hash.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/udp_socket.h>
#include <database/database_connection.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <radius_request.h>
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
class RequestTest : public radius::test::AttributeTest {
public:

    /// @brief Thread pointer type.
    typedef boost::shared_ptr<thread> ThreadPtr;

    /// @brief Constructor.
    RequestTest() :
        radius::test::AttributeTest(),
        impl_(RadiusImpl::instance()), service_(new IOService()),
        server_socket_(service_->getInternalIOService()),
        receive_buffer_(4096), receive_error_code_(), received_(false),
        send_buffer_(), send_error_code_(), sent_(false),
        timer_(service_), timeout_(false), which_(""),
        subnet_id_(SUBNET_ID_UNUSED), send_attributes_(),
        result_(OK_RC), received_attributes_(), thread_(),
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
    virtual ~RequestTest() {
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

    /// @brief Done authentication handler.
    ///
    /// @param handler Handler to the RadiusAsyncAuth.
    void doneAuth(int result, AttributesPtr received);

    /// @brief Done accounting handler.
    ///
    /// @param handler Handler to the RadiusAsyncAcct.
    void doneAcct(int result);

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

    /// @brief Subnet ID (aka client/NAS port).
    uint32_t subnet_id_;

    /// @brief Attributes to send.
    AttributesPtr send_attributes_;

    /// @brief Request result.
    int result_;

    /// @brief Received attributes.
    AttributesPtr received_attributes_;

    /// @brief Thread.
    ThreadPtr thread_;

    /// @brief Handler for authentication.
    RequestAuthPtr handler_auth_;

    /// @brief Handler for accounting..
    RequestAcctPtr handler_acct_;

    /// @brief Finished flag.
    atomic<bool> finished_;
};

void
RequestTest::poll() {
    service_->poll();
#ifdef REQUEST_SYNC_TEST
    usleep(1000);
#else
    EXPECT_NO_THROW(IfaceMgr::instance().receive4(0, 1000));
#endif
}

void
RequestTest::open(unsigned short server_port) {
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
RequestTest::close() {
    if (server_socket_.is_open()) {
        EXPECT_NO_THROW(server_socket_.close());
    }
}

void
RequestTest::timeout() {
    timeout_ = true;
    FAIL() << "timeout";
}

void
RequestTest::start(long deadline) {
    timer_.setup(std::bind(&RequestTest::timeout, this),
                 deadline, IntervalTimer::ONE_SHOT);
}

void
RequestTest::stop() {
    timer_.cancel();
}

void
RequestTest::doneAuth(int result, AttributesPtr received) {
    result_ = result;
    received_attributes_ = received;
    finished_ = true;
}

void
RequestTest::doneAcct(int result) {
    result_ = result;
    finished_ = true;
}

void
RequestTest::run() {
    if (which_ == "access") {
        handler_auth_.reset(new RequestAuth(subnet_id_,
                                send_attributes_,
                                std::bind(&RequestTest::doneAuth,
                                          this, ph::_1, ph::_2)));
        handler_auth_->start();
    } else if (which_ == "accounting") {
        handler_acct_.reset(new RequestAcct(subnet_id_,
                                send_attributes_,
                                std::bind(&RequestTest::doneAcct,
                                          this, ph::_1)));
        handler_acct_->start();
    } else {
        FAIL() << "which is not 'access' nor 'accounting'";
    }
}

/// Verify return code to text translation.
TEST_F(RequestTest, exchangeRCtoText) {
    EXPECT_EQ("error -3", exchangeRCtoText(-3));
    EXPECT_EQ("bad response", exchangeRCtoText(BADRESP_RC));   // -2
    EXPECT_EQ("error", exchangeRCtoText(ERROR_RC));            // -1
    EXPECT_EQ("ok", exchangeRCtoText(OK_RC));                  // 0
    EXPECT_EQ("timeout", exchangeRCtoText(TIMEOUT_RC));        // 1
    EXPECT_EQ("reject", exchangeRCtoText(REJECT_RC));          // 2
    EXPECT_EQ("unknown 4", exchangeRCtoText(4));
}

/// Verify subnet ID to NAS port remap.
TEST_F(RequestTest, getNASPort) {
    // No remap.
    EXPECT_EQ(44, getNASPort(44));

    // Default.
    impl_.remap_[SUBNET_ID_DEFAULT] = 2;
    EXPECT_EQ(2, getNASPort(44));

    // Specific/matching remap entry.
    impl_.remap_[44] = 3;
    EXPECT_EQ(3, getNASPort(44));
}

/// Verify what happens when there is no listening authentication server at all.
TEST_F(RequestTest, noAuthServer) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    EXPECT_FALSE(received_attributes_);
    EXPECT_EQ(TIMEOUT_RC, result_);
}

/// Verify what happens when there is no listening accounting server at all.
TEST_F(RequestTest, noAcctServer) {
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

    // Launch request handler i.e. the client code to test.
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
TEST_F(RequestTest, noAuthResponse) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    EXPECT_FALSE(received_attributes_);
    EXPECT_EQ(TIMEOUT_RC, result_);

    // Check received request.
    receive_buffer_.resize(size);
    ASSERT_LE(20, size);
    EXPECT_EQ(PW_ACCESS_REQUEST, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    ASSERT_LE(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(38, size);
    uint8_t expected[] = {
        0x01, // User-Name
        0x06, // length
        0x75, 0x73, 0x65, 0x72, // "user"
        0x05, // NAS-Port
        0x06, // length
        0x00, 0x00, 0x00, 0x01, // 1
        0x04, // NAS-IP-Address
        0x06, // length
        0x7f, 0x00, 0x00, 0x01 // 127.0.0.1
    };
    size_t expected_len = size - AUTH_HDR_LEN;
    if (expected_len > sizeof(expected)) {
        expected_len = sizeof(expected);
    }
    EXPECT_EQ(0, memcmp(expected,
                        &receive_buffer_[AUTH_HDR_LEN],
                        expected_len));
}

/// Verify what happens when no response is sent.
TEST_F(RequestTest, noAcctResponse) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    EXPECT_EQ(PW_ACCOUNTING_REQUEST, receive_buffer_[0]);
    uint16_t length = (receive_buffer_[2] << 8) | receive_buffer_[3];
    ASSERT_LE(length, size);
    EXPECT_GE(4096, length);

    // Check attributes.
    EXPECT_EQ(44, size);
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
        0x04, // NAS-IP-Address
        0x06, // length
        0x7f, 0x00, 0x00, 0x01 // 127.0.0.1
    };
    size_t expected_len = size - AUTH_HDR_LEN;
    if (expected_len > sizeof(expected)) {
        expected_len = sizeof(expected);
    }
    EXPECT_EQ(0, memcmp(expected,
                        &receive_buffer_[AUTH_HDR_LEN],
                        expected_len));

    // Check authenticator.
    vector<unsigned char> auth_input(size + 3);
    memmove(&auth_input[0], &receive_buffer_[0], size);
    memset(&auth_input[4], 0, AUTH_VECTOR_LEN);
    auth_input[size] = 'b';
    auth_input[size + 1] = 'a';
    auth_input[size + 2] = 'r';
    OutputBuffer auth_output(AUTH_VECTOR_LEN);
    digest(&auth_input[0], size + 3, isc::cryptolink::MD5,
           auth_output, AUTH_VECTOR_LEN);
    EXPECT_EQ(0, memcmp(auth_output.getData(),
                        &receive_buffer_[4],
                        AUTH_VECTOR_LEN));
}

/// Verify what happens with Access-Accept response.
TEST_F(RequestTest, accept) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

/// Verify what happens with Accounting-Response response.
TEST_F(RequestTest, response) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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

/// Verify what happens with bad Access-Accept response.
TEST_F(RequestTest, badAccept) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

/// Verify what happens with bad Accounting-Response response.
TEST_F(RequestTest, badResponse) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
TEST_F(RequestTest, shortAuth) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    EXPECT_FALSE(received_attributes_);
    EXPECT_EQ(BADRESP_RC, result_);
}

/// Verify what happens with bad (too short) response.
TEST_F(RequestTest, shortAcct) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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

/// Verify what happens with Access-Reject response.
TEST_F(RequestTest, reject) {
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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    EXPECT_EQ(REJECT_RC, result_);
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

/// Verify what happens with a backup authentication server.
TEST_F(RequestTest, accept2) {
    // Use CONFIGS[1].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[1]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "access";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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
    ASSERT_TRUE(received_attributes_);
    ASSERT_EQ(1, received_attributes_->size());
    ASSERT_EQ(1, received_attributes_->count(1));
    const ConstAttributePtr& attr = received_attributes_->get(1);
    ASSERT_TRUE(attr);
    EXPECT_EQ("User-Name='user'", attr->toText());
}

/// Verify what happens with a backup accounting server.
TEST_F(RequestTest, response2) {
    // Use CONFIGS[1].
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(CONFIGS[1]));
    ASSERT_NO_THROW(impl_.init(json));

    // Build request parameters.
    which_ = "accounting";
    subnet_id_ = 1;
    if (!send_attributes_) {
        send_attributes_.reset(new Attributes());
    }
    send_attributes_->add(Attribute::fromString(PW_USER_NAME, "user"));

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
#ifdef REQUEST_SYNC_TEST
    thread_.reset(new thread(std::bind(&RequestTest::run, this)));
#else
    run();
#endif

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

} // end of anonymous namespace
