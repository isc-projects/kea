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
#include <config/http_command_mgr.h>
#include <config/command_mgr.h>
#include <http/response.h>
#include <http/response_parser.h>
#include <http/tests/test_http_client.h>
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
    }

    /// @brief Resets state.
    ///
    /// @param io_service The IO service of the @c HttpCommandMgr.
    void resetState(IOServicePtr io_service = IOServicePtr()) {
        // Deregisters commands.
        config::CommandMgr::instance().deregisterAll();

        if (HttpCommandMgr::instance().getHttpListener()) {
            HttpCommandMgr::instance().close();
        }
        if (io_service) {
            HttpCommandMgr::instance().setIOService(io_service);
        } else {
            io_service_->stopAndPoll();
            HttpCommandMgr::instance().setIOService(IOServicePtr());
        }
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
        client_.reset(new TestHttpClient(io_service_, SERVER_ADDRESS,
                                         SERVER_PORT));

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

    /// @brief Create an HttpResponse from a response string.
    ///
    /// @param response_str a string containing the whole HTTP
    /// response received.
    ///
    /// @return An HttpResponse constructed from by parsing the
    /// response string.
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

    /// @brief IO service used in drive the test and test clients.
    IOServicePtr io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Client connection.
    TestHttpClientPtr client_;

    /// @brief HTTP control socket config.
    HttpCommandConfigPtr http_config_;
};

/// Verifies the configure and close of HttpCommandMgr.
TEST_F(HttpCommandMgrTest, basics) {
    // Make sure we can create one.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().configure(http_config_));
    auto listener = HttpCommandMgr::instance().getHttpListener();
    ASSERT_TRUE(listener);

    // Verify the getters do what we expect.
    EXPECT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    EXPECT_EQ(SERVER_PORT, listener->getLocalPort());

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().close());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // Make sure we can call stop again without problems.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().close());

    // We should be able to restart it.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().configure(http_config_));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Close it with postponed garbage collection.
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().close(false));
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());
    ASSERT_NO_THROW_LOG(HttpCommandMgr::instance().garbageCollectListeners());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());
}

#if 0
// This test verifies that an HTTP connection can be established and used to
// transmit an HTTP request and receive the response.
TEST_F(HttpCommandMgrTest, basicListenAndRespond) {

    // Create a listener.
    ASSERT_NO_THROW_LOG(listener_.reset(new HttpCommandMgr(IOAddress(SERVER_ADDRESS),
                                                           SERVER_PORT)));
    ASSERT_TRUE(listener_);

    // Start the listener and verify it's listening.
    ASSERT_NO_THROW_LOG(listener_->start());
    ASSERT_TRUE(listener_->isRunning());

    // Now let's send a "foo" command.  This should create a client, connect
    // to our listener, post our request and retrieve our reply.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ASSERT_TRUE(client_);
    ASSERT_NO_THROW(runIOService());
    ASSERT_TRUE(client_);

    // Parse the response into an HttpResponse.
    HttpResponsePtr hr;
    ASSERT_NO_THROW_LOG(hr = parseResponse(client_->getResponse()));

    // Without a command handler loaded, we should get an unsupported command response.
    EXPECT_EQ(hr->getBody(), "[ { \"result\": 2, \"text\": \"'foo' command not supported.\" } ]");

    // Now let's register the foo command handler.
    CommandMgr::instance().registerCommand("foo",
                                            std::bind(&HttpCommandMgrTest::fooCommandHandler,
                                                      this, ph::_1, ph::_2));
    // Try posting the foo command again.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ASSERT_TRUE(client_);

    // Parse the response.
    ASSERT_NO_THROW_LOG(hr = parseResponse(client_->getResponse()));

    // We should have a response from our command handler.
    EXPECT_EQ(hr->getBody(), "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]");

    // Make sure the listener is still listening.
    ASSERT_TRUE(listener_->isRunning());

    // Stop the listener then verify it has stopped.
    ASSERT_NO_THROW_LOG(listener_->stop());
    ASSERT_TRUE(listener_->isStopped());
}

// Check if a TLS listener can be created.
TEST_F(HttpCommandMgrTest, tls) {
    IOAddress address(SERVER_ADDRESS);
    uint16_t port = SERVER_PORT;
    TlsContextPtr context;
    configServer(context);

    // Make sure we can create the listener.
    ASSERT_NO_THROW_LOG(listener_.reset(new HttpCommandMgr(address, port, 1, context)));
    EXPECT_EQ(listener_->getAddress(), address);
    EXPECT_EQ(listener_->getPort(), port);
    EXPECT_EQ(listener_->getTlsContext(), context);
    EXPECT_TRUE(listener_->isStopped());

    // Make sure we can start it and it's listening.
    ASSERT_NO_THROW_LOG(listener_->start());
    ASSERT_TRUE(listener_->isRunning());

    // Stop it.
    ASSERT_NO_THROW_LOG(listener_->stop());
    ASSERT_TRUE(listener_->isStopped());
}
#endif

} // end of anonymous namespace
