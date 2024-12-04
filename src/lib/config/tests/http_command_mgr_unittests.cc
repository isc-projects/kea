// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/testutils/test_tls.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/http_command_mgr.h>
#include <dhcp/iface_mgr.h>
#include <http/response.h>
#include <http/response_parser.h>
#include <http/testutils/test_http_client.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <list>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace isc::util;
using namespace std;
using namespace boost::asio::ip;
namespace ph = std::placeholders;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Test fixture class for @ref CmdHttpListener.
class HttpCommandMgrTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Resets state, starts test timer which detects timeouts,
    /// initializes HTTP control socket config.
    HttpCommandMgrTest()
        : io_service_(new IOService()), test_timer_(io_service_), client_(),
          http_config_() {
        resetState(io_service_);
        test_timer_.setup(std::bind(&HttpCommandMgrTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
        HttpCommandMgr::instance().setIOService(io_service_);

        // Initializes the HTTP control socket config.
        ElementPtr config  = Element::createMap();
        config->set("socket-address", Element::create(SERVER_ADDRESS));
        config->set("socket-port", Element::create(SERVER_PORT));
        http_config_.reset(new HttpCommandConfig(config));

        // Register the foo command.
        CommandMgr::instance().registerCommand("foo", fooHandler);
    }

    /// @brief Destructor.
    ///
    /// Closes HTTP client, cancels timer, resets state.
    virtual ~HttpCommandMgrTest() {
        if (client_) {
            client_->close();
        }
        test_timer_.cancel();
        resetState();
        IfaceMgr::instance().deleteAllExternalSockets();
        io_service_->stopAndPoll();
    }

    /// @brief Resets state.
    ///
    /// @param io_service The IO service of the @c HttpCommandMgr.
    void resetState(IOServicePtr io_service = IOServicePtr()) {
        // Deregisters commands.
        config::CommandMgr::instance().deregisterAll();

        if (HttpCommandMgr::instance().getHttpListener()) {
            HttpCommandMgr::instance().closeCommandSockets();
        }
        if (io_service) {
            HttpCommandMgr::instance().setIOService(io_service);
        } else {
            io_service_->stopAndPoll();
            HttpCommandMgr::instance().setIOService(IOServicePtr());
        }
        HttpCommandMgr::instance().addExternalSockets(true);
    }

    /// @brief Constructs a complete HTTP POST given a request body.
    ///
    /// @param request_body string containing the desired request body.
    ///
    /// @return string containing the constructed POST.
    std::string buildPostStr(const std::string& request_body) {
        // Create the command string.
        std::stringstream ss;
        ss << "POST /foo/bar HTTP/1.1\r\n"
              "Content-Type: application/json\r\n"
              "Content-Length: "
              << request_body.size() << "\r\n\r\n"
              << request_body;
        return (ss.str());
    }

    /// @brief Initiates a command via a new HTTP client.
    ///
    /// This method creates a TestHttpClient instance, and starts a
    /// request based on the given command.
    ///
    /// @param request_body JSON String containing the API command
    /// to be sent.
    void startRequest(const std::string& request_body = "{ }") {
        std::string request_str = buildPostStr(request_body);

        // Instantiate the client.
        if (!client_) {
            client_.reset(new TestHttpClient(io_service_, SERVER_ADDRESS,
                                             SERVER_PORT));
        }

        // Start the request.  Note, nothing happens until the IOService runs.
        client_->startRequest(request_str);
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void timeoutHandler(const bool fail_on_timeout) {
        if (fail_on_timeout) {
            ADD_FAILURE() << "Timeout occurred while running the test!";
        }
        io_service_->stop();
    }

    /// @brief Runs IO service.
    void runIOService() {
        EXPECT_TRUE(client_);
        // Run until a client stops the service or an error occurs.
        io_service_->run();
        EXPECT_TRUE(client_ && client_->receiveDone());
    }

    /// @brief Create an HttpResponse from a response string.
    ///
    /// @param response_str a string containing the whole HTTP
    /// response received.
    ///
    /// @return An HttpResponse constructed by parsing the response string.
    HttpResponsePtr parseResponse(const std::string response_str) {
        HttpResponsePtr hr(new HttpResponse());
        HttpResponseParser parser(*hr);
        parser.initModel();
        parser.postBuffer(&response_str[0], response_str.size());
        parser.poll();
        if (!parser.httpParseOk()) {
            isc_throw(Unexpected, "response_str: '" << response_str
                      << "' failed to parse: " << parser.getErrorMessage());
        }

        return (hr);
    }

    /// @brief "foo" command handler.
    ///
    /// The command needs no arguments and returns a response
    /// with a body containing:
    ///
    /// "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]"
    ///
    /// @return Returns response with a single string "bar".
    static ConstElementPtr fooHandler(const string&, const ConstElementPtr&) {
        ElementPtr arguments = Element::createList();
        arguments->add(Element::create("bar"));
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    /// @brief IO service used to drive the test and test clients.
    IOServicePtr io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Client connection.
    boost::shared_ptr<BaseTestHttpClient> client_;

    /// @brief HTTP control socket config.
    HttpCommandConfigPtr http_config_;
};

/// Verifies the configure and close of HttpCommandMgr.
TEST_F(HttpCommandMgrTest, basic) {
    // Make sure we can create one.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    auto listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);

    // Verify the getters do what we expect.
    EXPECT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    EXPECT_EQ(SERVER_PORT, listener->getLocalPort());

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // Make sure we can call stop again without problems.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());

    // We should be able to restart it.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Close it with postponed garbage collection.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSocket(HttpSocketInfoPtr(), false));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());
}

/// Verifies the use external socket flag of HttpCommandMgr.
TEST_F(HttpCommandMgrTest, useExternal) {
    // Default is to use external sockets.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    auto listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);
    int fd = listener->getNative();
    EXPECT_NE(-1, fd);
    EXPECT_TRUE(IfaceMgr::instance().isExternalSocket(fd));
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());

    // Change to no external sockets.
    HttpCommandMgr::instance().addExternalSockets(false);

    // Retry: now the listener is not added as an external socket
    // to the interface manager.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);
    fd = listener->getNative();
    EXPECT_NE(-1, fd);
    EXPECT_FALSE(IfaceMgr::instance().isExternalSocket(fd));
}

/// Verifies the configure and close of HttpCommandMgr with TLS.
TEST_F(HttpCommandMgrTest, basicTls) {
    // Setup TLS for the manager.
    string ca_dir(string(TEST_CA_DIR));
    http_config_->setSocketType("https");
    http_config_->setTrustAnchor(ca_dir + string("/kea-ca.crt"));
    http_config_->setCertFile(ca_dir + string("/kea-server.crt"));
    http_config_->setKeyFile(ca_dir + string("/kea-server.key"));

    // Make sure we can create one.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    auto listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);

    // Verify the getters do what we expect.
    EXPECT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    EXPECT_EQ(SERVER_PORT, listener->getLocalPort());

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // Make sure we can call stop again without problems.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());

    // We should be able to restart it.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Close it with postponed garbage collection.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSocket(HttpSocketInfoPtr(), false));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());
}

/// Verifies the use external socket flag of HttpCommandMgr with TLS.
TEST_F(HttpCommandMgrTest, useExternalTls) {
    string ca_dir(string(TEST_CA_DIR));
    // Setup TLS for the manager.
    http_config_->setSocketType("https");
    http_config_->setTrustAnchor(ca_dir + string("/kea-ca.crt"));
    http_config_->setCertFile(ca_dir + string("/kea-server.crt"));
    http_config_->setKeyFile(ca_dir + string("/kea-server.key"));

    // Default is to use external sockets.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    auto listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);
    int fd = listener->getNative();
    EXPECT_NE(-1, fd);
    EXPECT_TRUE(IfaceMgr::instance().isExternalSocket(fd));
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().closeCommandSockets());

    // Change to no external sockets.
    HttpCommandMgr::instance().addExternalSockets(false);

    // Retry: now the listener is not added as an external socket
    // to the interface manager.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);
    fd = listener->getNative();
    EXPECT_NE(-1, fd);
    EXPECT_FALSE(IfaceMgr::instance().isExternalSocket(fd));
}

// This test verifies that an HTTP connection can be established and used to
// transmit an HTTP request and receive the response.
TEST_F(HttpCommandMgrTest, command) {
    // Configure.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Now let's send a "foo" command.  This should create a client, connect
    // to our listener, post our request and retrieve our reply.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ASSERT_TRUE(client_);
    ASSERT_NO_THROW(runIOService());
    ASSERT_TRUE(client_);

    // Parse the response into an HttpResponse.
    HttpResponsePtr hr;
    ASSERT_NO_THROW_LOG(hr = parseResponse(client_->getResponse()));

    // We should have a response from our command handler.
    EXPECT_EQ(hr->getBody(), "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]");
}

// This test verifies that an HTTP connection can be established and used to
// transmit an HTTP request and receive the response (no external sockets).
TEST_F(HttpCommandMgrTest, commandNoExternal) {
    // Change to no external sockets.
    HttpCommandMgr::instance().addExternalSockets(false);

    // Configure.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Now let's send a "foo" command.  This should create a client, connect
    // to our listener, post our request and retrieve our reply.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ASSERT_TRUE(client_);
    ASSERT_NO_THROW(runIOService());
    ASSERT_TRUE(client_);

    // Parse the response into an HttpResponse.
    HttpResponsePtr hr;
    ASSERT_NO_THROW_LOG(hr = parseResponse(client_->getResponse()));

    // We should have a response from our command handler.
    EXPECT_EQ(hr->getBody(), "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]");
}

// This test verifies that an HTTPS connection can be established and used to
// transmit an HTTPS request and receive the response.
TEST_F(HttpCommandMgrTest, commandTls) {
    // Setup TLS for the manager.
    string ca_dir(string(TEST_CA_DIR));
    http_config_->setSocketType("https");
    http_config_->setTrustAnchor(ca_dir + string("/kea-ca.crt"));
    http_config_->setCertFile(ca_dir + string("/kea-server.crt"));
    http_config_->setKeyFile(ca_dir + string("/kea-server.key"));

    // Configure.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Create a HTTPS test client.
    TlsContextPtr client_tls_context;
    configClient(client_tls_context);
    client_.reset(new TestHttpsClient(io_service_, client_tls_context,
                                      SERVER_ADDRESS, SERVER_PORT));

    // Now let's send a "foo" command.  This should create a client, connect
    // to our listener, post our request and retrieve our reply.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ASSERT_TRUE(client_);
    ASSERT_NO_THROW(runIOService());
    ASSERT_TRUE(client_);

    // Parse the response into an HttpResponse.
    HttpResponsePtr hr;
    ASSERT_NO_THROW_LOG(hr = parseResponse(client_->getResponse()));

    // We should have a response from our command handler.
    EXPECT_EQ(hr->getBody(), "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]");
}

// This test verifies that an HTTPS connection can be established and used to
// transmit an HTTPS request and receive the response (no external sockets).
TEST_F(HttpCommandMgrTest, commandNoExternalTls) {
    // Change to no external sockets.
    HttpCommandMgr::instance().addExternalSockets(false);

    // Setup TLS for the manager.
    string ca_dir(string(TEST_CA_DIR));
    http_config_->setSocketType("https");
    http_config_->setTrustAnchor(ca_dir + string("/kea-ca.crt"));
    http_config_->setCertFile(ca_dir + string("/kea-server.crt"));
    http_config_->setKeyFile(ca_dir + string("/kea-server.key"));

    // Configure.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().openCommandSocket(http_config_->toElement()));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Create a HTTPS test client.
    TlsContextPtr client_tls_context;
    configClient(client_tls_context);
    client_.reset(new TestHttpsClient(io_service_, client_tls_context,
                                      SERVER_ADDRESS, SERVER_PORT));

    // Now let's send a "foo" command.  This should create a client, connect
    // to our listener, post our request and retrieve our reply.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ASSERT_TRUE(client_);
    ASSERT_NO_THROW(runIOService());
    ASSERT_TRUE(client_);

    // Parse the response into an HttpResponse.
    HttpResponsePtr hr;
    ASSERT_NO_THROW_LOG(hr = parseResponse(client_->getResponse()));

    // We should have a response from our command handler.
    EXPECT_EQ(hr->getBody(), "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]");
}

} // end of anonymous namespace
