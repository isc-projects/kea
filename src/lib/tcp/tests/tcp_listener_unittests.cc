// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <cc/data.h>
#include <tcp/tcp_listener.h>
#include <tcp_test_client.h>
#include <util/multi_threading_mgr.h>

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <list>
#include <sstream>
#include <string>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::tcp;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to whch HTTP service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Implementation of the TCPListener used in tests.
///
/// Implements simple stream in/out listener.
class TcpTestListener : public TcpListener {
public:

    TcpTestListener(IOService& io_service,
                    const IOAddress& server_address,
                    const unsigned short server_port,
                    const TlsContextPtr& tls_context,
                    const IdleTimeout& idle_timeout)
        : TcpListener(io_service, server_address, server_port,
                      tls_context, idle_timeout) {
    }

protected:

    /// @brief Creates an instance of the @c TcpConnection.
    ///
    /// This method is virtual so as it can be overridden when customized
    /// connections are to be used, e.g. in case of unit testing.
    ///
    /// @param callback Callback invoked when new connection is accepted.
    /// @return Pointer to the created connection.
    virtual TcpConnectionPtr createConnection(const TcpConnectionAcceptorCallback& callback) {
        TcpConnectionPtr
            conn(new TcpConnection(io_service_, acceptor_,
                                   tls_context_, connections_,
                                   callback, idle_timeout_));
        return (conn);
    }
};

/// @brief Test fixture class for @ref TcpListener.
class TcpListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    TcpListenerTest()
        : io_service_(), test_timer_(io_service_), run_io_service_timer_(io_service_), clients_() {
        test_timer_.setup(std::bind(&TcpListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active HTTP clients.
    virtual ~TcpListenerTest() {
        for (auto client = clients_.begin(); client != clients_.end();
             ++client) {
            (*client)->close();
        }
    }

    /// @brief Connect to the endpoint.
    ///
    /// This method creates TcpTestClient instance and retains it in the clients_
    /// list.
    ///
    /// @param request String containing the HTTP request to be sent.
    void startRequest(const std::string& request) {
        TcpTestClientPtr client(new TcpTestClient(io_service_));
        clients_.push_back(client);
        clients_.back()->startRequest(request);
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
        io_service_.stop();
    }

    /// @brief Runs IO service with optional timeout.
    ///
    /// @param timeout Optional value specifying for how long the io service
    /// should be ran.
    void runIOService(long timeout = 0) {
        io_service_.get_io_service().reset();

        if (timeout > 0) {
            run_io_service_timer_.setup(std::bind(&TcpListenerTest::timeoutHandler,
                                                  this, false),
                                        timeout, IntervalTimer::ONE_SHOT);
        }
        io_service_.run();
        io_service_.get_io_service().reset();
        io_service_.poll();
    }

#if 0
    /// @brief Tests that HTTP request timeout status is returned when the
    /// server does not receive the entire request.
    ///
    /// @param request Partial request for which the parser will be waiting for
    /// the next chunks of data.
    void testRequestTimeout(const std::string& request) {
        // Open the listener with the Request Timeout of 1 sec and post the
        // partial request.
        TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(),
                              factory_, TcpListener::RequestTimeout(1000),
                              TcpListener::IdleTimeout(IDLE_TIMEOUT));
        ASSERT_NO_THROW(listener.start());
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        TcpTestClientPtr client = *clients_.begin();
        ASSERT_TRUE(client);

        // Build the reference response.
        std::ostringstream expected_response;
        expected_response
            << "HTTP/" << expected_version.major_ << "." << expected_version.minor_
            << " 408 Request Timeout\r\n"
            "Content-Length: 44\r\n"
            "Content-Type: application/json\r\n"
            "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
            "\r\n"
            "{ \"result\": 408, \"text\": \"Request Timeout\" }";

        // The server should wait for the missing part of the request for 1 second.
        // The missing part never arrives so the server should respond with the
        // HTTP Request Timeout status.
        EXPECT_EQ(expected_response.str(), client->getResponse());
    }

    /// @brief Tests various cases when unexpected data is passed to the
    /// socket write handler.
    ///
    /// This test uses the custom listener and the test specific derivations of
    /// the @c TcpConnection class to enforce injection of the unexpected
    /// data to the socket write callback. The two example applications of
    /// this test are:
    /// - injecting greater length value than the output buffer size,
    /// - replacing the transaction with another transaction.
    ///
    /// It is expected that the socket write callback deals gracefully with
    /// those situations.
    ///
    /// @tparam TcpConnectionType Test specific derivation of the
    /// @c TcpConnection class.
    template<typename TcpConnectionType>
    void testWriteBufferIssues() {
        // The HTTP/1.1 requests are by default persistent.
        std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";

        // Use custom listener and the specialized connection object.
        TcpListenerCustom<TcpConnectionType>
            listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                     TlsContextPtr(), factory_,
                     TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                     TcpListener::IdleTimeout(IDLE_TIMEOUT));

        ASSERT_NO_THROW(listener.start());

        // Send the request.
        ASSERT_NO_THROW(startRequest(request));

        // Injecting unexpected data should not result in an exception.
        ASSERT_NO_THROW(runIOService());

        ASSERT_EQ(1, clients_.size());
        TcpTestClientPtr client = *clients_.begin();
        ASSERT_TRUE(client);
    }
#endif

    /// @brief IO service used in the tests.
    IOService io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<TcpTestClientPtr> clients_;
};

// This test verifies that HTTP connection can be established and used to
// transmit HTTP request and receive a response.
TEST_F(TcpListenerTest, listen) {
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), TcpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    listener.stop();
    io_service_.poll();
}

#if 0
// This test verifies that persistent HTTP connection can be established when
// "Connection: Keep-Alive" header value is specified.
TEST_F(TcpListenerTest, keepAlive) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());

    // Send the request with the keep-alive header.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // We have sent keep-alive header so we expect that the connection with
    // the server remains active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Test that we can send another request via the same connection. This time
    // it lacks the keep-alive header, so the server should close the connection
    // after sending the response.
    request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    // Send request reusing the existing connection.
    ASSERT_NO_THROW(client->sendRequest(request));
    ASSERT_NO_THROW(runIOService());

    // Connection should have been closed by the server.
    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that persistent HTTP connection is established by default
// when HTTP/1.1 is in use.
TEST_F(TcpListenerTest, persistentConnection) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());

    // Send the first request.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // HTTP/1.1 connection is persistent by default.
    ASSERT_TRUE(client->isConnectionAlive());

    // Test that we can send another request via the same connection. This time
    // it includes the "Connection: close" header which instructs the server to
    // close the connection after responding.
    request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: close\r\n\r\n"
        "{ }";

    // Send request reusing the existing connection.
    ASSERT_NO_THROW(client->sendRequest(request));
    ASSERT_NO_THROW(runIOService());

    // Connection should have been closed by the server.
    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that "keep-alive" connection is closed by the server after
// an idle time.
TEST_F(TcpListenerTest, keepAliveTimeout) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    // Specify the idle timeout of 500ms.
    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(500));

    ASSERT_NO_THROW(listener.start());

    // Send the request with the keep-alive header.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // We have sent keep-alive header so we expect that the connection with
    // the server remains active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Run IO service for 1000ms. The idle time is set to 500ms, so the connection
    // should be closed by the server while we wait here.
    runIOService(1000);

    // Make sure the connection has been closed.
    EXPECT_TRUE(client->isConnectionClosed());

    // Check if we can re-establish the connection and send another request.
    clients_.clear();
    request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    client = *clients_.begin();
    ASSERT_TRUE(client);

    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that persistent connection is closed by the server after
// an idle time.
TEST_F(TcpListenerTest, persistentConnectionTimeout) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    // Specify the idle timeout of 500ms.
    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(500));

    ASSERT_NO_THROW(listener.start());

    // Send the request.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // The connection should remain active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Run IO service for 1000ms. The idle time is set to 500ms, so the connection
    // should be closed by the server while we wait here.
    runIOService(1000);

    // Make sure the connection has been closed.
    EXPECT_TRUE(client->isConnectionClosed());

    // Check if we can re-establish the connection and send another request.
    clients_.clear();
    request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: close\r\n\r\n"
        "{ }";

    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    client = *clients_.begin();
    ASSERT_TRUE(client);

    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that HTTP/1.1 connection remains open even if there is an
// error in the message body.
TEST_F(TcpListenerTest, persistentConnectionBadBody) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 12\r\n\r\n"
        "{ \"a\": abc }";

    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());

    // Send the request.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ("HTTP/1.1 400 Bad Request\r\n"
              "Content-Length: 40\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n"
              "{ \"result\": 400, \"text\": \"Bad Request\" }",
              client->getResponse());

    // The connection should remain active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Make sure that we can send another request. This time we specify the
    // "close" connection-token to force the connection to close.
    request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: close\r\n\r\n"
        "{ }";

    // Send request reusing the existing connection.
    ASSERT_NO_THROW(client->sendRequest(request));
    ASSERT_NO_THROW(runIOService());

    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that the HTTP listener can't be started twice.
TEST_F(TcpListenerTest, startTwice) {
    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    EXPECT_THROW(listener.start(), TcpListenerError);
}

// This test verifies that Bad Request status is returned when the request
// is malformed.
TEST_F(TcpListenerTest, badRequest) {
    // Content-Type is wrong. This should result in Bad Request status.
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: foo\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ("HTTP/1.1 400 Bad Request\r\n"
              "Content-Length: 40\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n"
              "{ \"result\": 400, \"text\": \"Bad Request\" }",
              client->getResponse());
}

// This test verifies that NULL pointer can't be specified for the
// TcpResponseCreatorFactory.
TEST_F(TcpListenerTest, invalidFactory) {
    EXPECT_THROW(TcpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(),
                              TcpResponseCreatorFactoryPtr(),
                              TcpListener::IdleTimeout(IDLE_TIMEOUT)),
                 TcpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// Request Timeout.
TEST_F(TcpListenerTest, invalidRequestTimeout) {
    EXPECT_THROW(TcpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(), factory_,
                              TcpListener::IdleTimeout(IDLE_TIMEOUT)),
                 TcpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// idle persistent connection timeout.
TEST_F(TcpListenerTest, invalidIdleTimeout) {
    EXPECT_THROW(TcpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(), factory_,
                              TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                              TcpListener::IdleTimeout(0)),
                 TcpListenerError);
}

// This test verifies that listener can't be bound to the port to which
// other server is bound.
TEST_F(TcpListenerTest, addressInUse) {
    tcp::acceptor acceptor(io_service_.get_io_service());
    // Use other port than SERVER_PORT to make sure that this TCP connection
    // doesn't affect subsequent tests.
    tcp::endpoint endpoint(address::from_string(SERVER_ADDRESS),
                           SERVER_PORT + 1);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);

    // Listener should report an error when we try to start it because another
    // acceptor is bound to that port and address.
    TcpListener listener(io_service_, IOAddress(SERVER_ADDRESS),
                          SERVER_PORT + 1, TlsContextPtr(), factory_,
                          TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                          TcpListener::IdleTimeout(IDLE_TIMEOUT));
    EXPECT_THROW(listener.start(), TcpListenerError);
}

// This test verifies that injecting length value greater than the
// output buffer length to the socket write callback does not cause
// an exception.
TEST_F(TcpListenerTest, tooLongWriteBuffer) {
    testWriteBufferIssues<TcpConnectionLongWriteBuffer>();
}

// This test verifies that changing the transaction before calling
// the socket write callback does not cause an exception.
TEST_F(TcpListenerTest, transactionChangeDuringWrite) {
    testWriteBufferIssues<TcpConnectionTransactionChange>();
}

/// @brief Test fixture class for testing HTTP client.
class TcpClientTest : public TcpListenerTest {
public:

    /// @brief Constructor.
    TcpClientTest()
        : TcpListenerTest(),
          listener_(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                    TlsContextPtr(), factory_,
                    TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                    TcpListener::IdleTimeout(IDLE_TIMEOUT)),
          listener2_(io_service_, IOAddress(IPV6_SERVER_ADDRESS), SERVER_PORT + 1,
                     TlsContextPtr(), factory_,
                     TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                     TcpListener::IdleTimeout(IDLE_TIMEOUT)),
          listener3_(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT + 2,
                     TlsContextPtr(), factory_,
                     TcpListener::RequestTimeout(REQUEST_TIMEOUT),
                     TcpListener::IdleTimeout(SHORT_IDLE_TIMEOUT)) {
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    ~TcpClientTest() {
        listener_.stop();
        listener2_.stop();
        listener3_.stop();
        io_service_.poll();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Creates HTTP request with JSON body.
    ///
    /// It includes a JSON parameter with a specified value.
    ///
    /// @param parameter_name JSON parameter to be included.
    /// @param value JSON parameter value.
    /// @param version HTTP version to be used. Default is HTTP/1.1.
    template<typename ValueType>
    PostTcpRequestJsonPtr createRequest(const std::string& parameter_name,
                                         const ValueType& value) {
        // Body is a map with a specified parameter included.
        ElementPtr body = Element::createMap();
        body->set(parameter_name, Element::create(value));
        request->setBodyAsJson(body);
        try {
            request->finalize();

        } catch (const std::exception& ex) {
            ADD_FAILURE() << "failed to create request: " << ex.what();
        }

        return (request);
    }

    /// @brief Test that two consecutive requests can be sent over the same
    /// connection (if persistent, if not persistent two connections will
    /// be used).
    ///
    /// @param version HTTP version to be used.
    void testConsecutiveRequests() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create a client and specify the URL on which the server can be reached.
        TcpClient client(io_service_);
        Url url("http://127.0.0.1:18123");

        // Initiate request to the server.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1, version);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Initiate another request to the destination.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 2, version);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that the received responses are different. We check that by
        // comparing value of the sequence parameters.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief Test that the client can communicate with two different
    /// destinations simultaneously.
    void testMultipleDestinations() {
        // Start two servers running on different ports.
        ASSERT_NO_THROW(listener_.start());
        ASSERT_NO_THROW(listener2_.start());

        // Create the client. It will be communicating with the two servers.
        TcpClient client(io_service_);

        // Specify the URLs on which the servers are available.
        Url url1("http://127.0.0.1:18123");
        Url url2("http://[::1]:18124");

        // Create a request to the first server.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url1, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Create a request to the second server.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 2);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url2, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());

        // Make sure we have received two different responses.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief Test that the client can communicate with the same destination
    /// address and port but with different TLS contexts so
    void testMultipleTlsContexts() {
        // Start only one server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        TcpClient client(io_service_);

        // Specify the URL on which the server is available.
        Url url("http://127.0.0.1:18123");

        // Create a request to the first server.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            if (ec) {
                ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
            }
        }));

        // Create a request with the second TLS context.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 2);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            if (ec) {
                ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
            }
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());

        // Make sure we have received two different responses.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief Test that idle connection can be resumed for second request.
    void testIdleConnection() {
        // Start the server that has short idle timeout. It closes the idle
        // connection after 200ms.
        ASSERT_NO_THROW(listener3_.start());

        // Create the client that will communicate with this server.
        TcpClient client(io_service_);

        // Specify the URL of this server.
        Url url("http://127.0.0.1:18125");

        // Create the first request.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this](const boost::system::error_code& ec, const TcpResponsePtr&,
                   const std::string&) {
            io_service_.stop();
            EXPECT_FALSE(ec);
        }));

        // Run the IO service until the response is received.
        ASSERT_NO_THROW(runIOService());

        // Make sure the response has been received.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        // Delay the generation of the second request by 2x server idle timeout.
        // This should be enough to cause the server to close the connection.
        ASSERT_NO_THROW(runIOService(SHORT_IDLE_TIMEOUT * 2));

        // Create another request.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 2);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this](const boost::system::error_code& ec, const TcpResponsePtr&,
                   const std::string&) {
            io_service_.stop();
            EXPECT_FALSE(ec);
        }));

        // Actually trigger the second request.
        ASSERT_NO_THROW(runIOService());

        // Make sire that the server has responded.
        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        // Make sure that two different responses have been received.
        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief This test verifies that the client returns IO error code when the
    /// server is unreachable.
    void testUnreachable () {
        // Create the client.
        TcpClient client(io_service_);

        // Specify the URL of the server. This server is down.
        Url url("http://127.0.0.1:18123");

        // Create the request.
        PostTcpRequestJsonPtr request = createRequest("sequence", 1);
        TcpResponseJsonPtr response(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this](const boost::system::error_code& ec,
                   const TcpResponsePtr&,
                   const std::string&) {
            io_service_.stop();
            // The server should have returned an IO error.
            EXPECT_TRUE(ec);
        }));

        // Actually trigger the request.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Test that an error is returned by the client if the server
    /// response is malformed.
    void testMalformedResponse () {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        TcpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        // The response is going to be malformed in such a way that it holds
        // an invalid content type. We affect the content type by creating
        // a request that holds a JSON parameter requesting a specific
        // content type.
        PostTcpRequestJsonPtr request = createRequest("requested-content-type",
                                                       "text/html");
        TcpResponseJsonPtr response(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this](const boost::system::error_code& ec,
                   const TcpResponsePtr& response,
                   const std::string& parsing_error) {
            io_service_.stop();
            // There should be no IO error (answer from the server is received).
            EXPECT_FALSE(ec);
            // The response object is NULL because it couldn't be finalized.
            EXPECT_FALSE(response);
            // The message parsing error should be returned.
            EXPECT_FALSE(parsing_error.empty());
        }));

        // Actually trigger the request.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Test that client times out when it doesn't receive the entire
    /// response from the server within a desired time.
    void testClientRequestTimeout() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        TcpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        unsigned cb_num = 0;

        // Create the request which asks the server to generate a partial
        // (although well formed) response. The client will be waiting for the
        // rest of the response to be provided and will eventually time out.
        PostTcpRequestJsonPtr request1 = createRequest("partial-response", true);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        // This value will be set to true if the connection close callback is
        // invoked upon time out.
        auto connection_closed = false;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &cb_num](const boost::system::error_code& ec,
                            const TcpResponsePtr& response,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_.stop();
                }
                // In this particular case we know exactly the type of the
                // IO error returned, because the client explicitly sets this
                // error code.
                EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
                // There should be no response returned.
                EXPECT_FALSE(response);
            },
            TcpClient::RequestTimeout(100),
            TcpClient::ConnectHandler(),
            TcpClient::HandshakeHandler(),
            [&connection_closed](const int) {
                // This callback is called when the connection gets closed
                // by the client.
                connection_closed = true;
            })
        );

        // Create another request after the timeout. It should be handled ok.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 1);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &cb_num](const boost::system::error_code& /*ec*/,
                            const TcpResponsePtr&,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_.stop();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
        // Make sure that the client has closed the connection upon timeout.
        EXPECT_TRUE(connection_closed);
    }

    /// @brief Test that client times out when connection takes too long.
    void testClientConnectTimeout() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        TcpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        unsigned cb_num = 0;

        PostTcpRequestJsonPtr request = createRequest("sequence", 1);
        TcpResponseJsonPtr response(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this, &cb_num](const boost::system::error_code& ec,
                            const TcpResponsePtr& response,
                            const std::string&) {
            if (++cb_num > 1) {
                io_service_.stop();
            }
            // In this particular case we know exactly the type of the
            // IO error returned, because the client explicitly sets this
            // error code.
            EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
            // There should be no response returned.
            EXPECT_FALSE(response);

        }, TcpClient::RequestTimeout(100),

           // This callback is invoked upon an attempt to connect to the
           // server. The false value indicates to the TcpClient to not
           // try to send a request to the server. This simulates the
           // case of connect() taking very long and should eventually
           // cause the transaction to time out.
           [](const boost::system::error_code& /*ec*/, int) {
               return (false);
        }));

        // Create another request after the timeout. It should be handled ok.
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this, &cb_num](const boost::system::error_code& /*ec*/,
                            const TcpResponsePtr&,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_.stop();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Tests the behavior of the HTTP client when the premature
    /// timeout occurs.
    ///
    /// The premature timeout may occur when the system clock is moved
    /// during the transaction. This test simulates this behavior by
    /// starting new transaction and waiting for the timeout to occur
    /// before the IO service is ran. The timeout handler is invoked
    /// first and it resets the transaction state. This test verifies
    /// that the started transaction tears down gracefully after the
    /// transaction state is reset.
    ///
    /// There are two variants of this test. The first variant schedules
    /// one transaction before running the IO service. The second variant
    /// schedules two transactions prior to running the IO service. The
    /// second transaction is queued, so it is expected that it doesn't
    /// time out and it runs successfully.
    ///
    /// @param queue_two_requests Boolean value indicating if a single
    /// transaction should be queued (false), or two (true).
    void testClientRequestLateStart(const bool queue_two_requests) {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        TcpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        // Specify the TLS context of the server.
        TlsContextPtr tls_context;

        // Generate first request.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1);
        TcpResponseJsonPtr response1(new TcpResponseJson());

        // Use very short timeout to make sure that it occurs before we actually
        // run the transaction.
        ASSERT_NO_THROW(client.asyncSendRequest(url, tls_context,
                                                request1, response1,
            [](const boost::system::error_code& ec,
               const TcpResponsePtr& response,
               const std::string&) {

            // In this particular case we know exactly the type of the
            // IO error returned, because the client explicitly sets this
            // error code.
            EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
            // There should be no response returned.
            EXPECT_FALSE(response);
        }, TcpClient::RequestTimeout(1)));

        if (queue_two_requests) {
            PostTcpRequestJsonPtr request2 = createRequest("sequence", 2);
            TcpResponseJsonPtr response2(new TcpResponseJson());
            ASSERT_NO_THROW(client.asyncSendRequest(url, tls_context,
                                                    request2, response2,
                [](const boost::system::error_code& ec,
                   const TcpResponsePtr& response,
                   const std::string&) {

                // This second request should be successful.
                EXPECT_TRUE(ec.value() == 0);
                EXPECT_TRUE(response);
            }));
        }

        // This waits for 3ms to make sure that the timeout occurs before we
        // run the transaction. This leads to an unusual situation that the
        // transaction state is reset as a result of the timeout but the
        // transaction is alive. We want to make sure that the client can
        // gracefully deal with this situation.
        usleep(3000);

        // Run the transaction and hope it will gracefully tear down.
        ASSERT_NO_THROW(runIOService(100));

        // Now try to send another request to make sure that the client
        // is healthy.
        PostTcpRequestJsonPtr request3 = createRequest("sequence", 3);
        TcpResponseJsonPtr response3(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request3, response3,
                         [this](const boost::system::error_code& ec,
                                const TcpResponsePtr&,
                                const std::string&) {
            io_service_.stop();

            // Everything should be ok.
            EXPECT_TRUE(ec.value() == 0);
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Tests that underlying TCP socket can be registered and
    /// unregistered via connection and close callbacks.
    ///
    /// It conducts to consecutive requests over the same client.
    ///
    /// @param version HTTP version to be used.
    void testConnectCloseCallbacks() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create a client and specify the URL on which the server can be reached.
        TcpClient client(io_service_);
        Url url("http://127.0.0.1:18123");

        // Initiate request to the server.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1, version);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        unsigned resp_num = 0;
        ExternalMonitor monitor;

        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }

            EXPECT_FALSE(ec);
        },
            TcpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Initiate another request to the destination.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 2, version);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        },
            TcpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // We should have had 2 connect invocations, no closes
        // and a valid registered fd
        EXPECT_EQ(2, monitor.connect_cnt_);
        EXPECT_EQ(0, monitor.close_cnt_);
        EXPECT_GT(monitor.registered_fd_, -1);

        // Make sure that the received responses are different. We check that by
        // comparing value of the sequence parameters.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);
        EXPECT_NE(sequence1->intValue(), sequence2->intValue());

        // Stopping the client the close the connection.
        client.stop();

        // We should have had 2 connect invocations, 1 closes
        // and an invalid registered fd
        EXPECT_EQ(2, monitor.connect_cnt_);
        EXPECT_EQ(1, monitor.close_cnt_);
        EXPECT_EQ(-1, monitor.registered_fd_);
    }

    /// @brief Tests detection and handling out-of-band socket events
    ///
    /// It initiates a transaction and verifies that a mid-transaction call
    /// to TcpClient::closeIfOutOfBand() has no affect on the connection.
    /// After successful completion of the transaction, a second call to
    /// TcpClient::closeIfOutOfBand() is made. This should result in the
    /// connection being closed.
    /// This step is repeated to verify that after an OOB closure, transactions
    /// to the same destination can be processed.
    ///
    /// Lastly, we verify that TcpClient::stop() closes the connection correctly.
    ///
    /// @param version HTTP version to be used.
    void testCloseIfOutOfBand() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create a client and specify the URL on which the server can be reached.
        TcpClient client(io_service_);
        Url url("http://127.0.0.1:18123");

        // Initiate request to the server.
        PostTcpRequestJsonPtr request1 = createRequest("sequence", 1, version);
        TcpResponseJsonPtr response1(new TcpResponseJson());
        unsigned resp_num = 0;
        ExternalMonitor monitor;

        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &client, &resp_num, &monitor](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num == 1) {
                io_service_.stop();
            }

            EXPECT_EQ(1, monitor.connect_cnt_);      // We should have 1 connect.
            EXPECT_EQ(0, monitor.close_cnt_);        // We should have 0 closes
            ASSERT_GT(monitor.registered_fd_, -1);   // We should have a valid fd.
            int orig_fd = monitor.registered_fd_;

            // Test our socket for OOBness.
            client.closeIfOutOfBand(monitor.registered_fd_);

            // Since we're in a transaction, we should have no closes and
            // the same valid fd.
            EXPECT_EQ(0, monitor.close_cnt_);
            ASSERT_EQ(monitor.registered_fd_, orig_fd);

            EXPECT_FALSE(ec);
        },
            TcpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that we received a response.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);
        EXPECT_EQ(1, sequence1->intValue());

        // We should have had 1 connect invocations, no closes
        // and a valid registered fd
        EXPECT_EQ(1, monitor.connect_cnt_);
        EXPECT_EQ(0, monitor.close_cnt_);
        EXPECT_GT(monitor.registered_fd_, -1);

        // Test our socket for OOBness.
        client.closeIfOutOfBand(monitor.registered_fd_);

        // Since we're in a transaction, we should have no closes and
        // the same valid fd.
        EXPECT_EQ(1, monitor.close_cnt_);
        EXPECT_EQ(-1, monitor.registered_fd_);

        // Now let's do another request to the destination to verify that
        // we'll reopen the connection without issue.
        PostTcpRequestJsonPtr request2 = createRequest("sequence", 2, version);
        TcpResponseJsonPtr response2(new TcpResponseJson());
        resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &client, &resp_num, &monitor](const boost::system::error_code& ec,
                              const TcpResponsePtr&,
                              const std::string&) {
            if (++resp_num == 1) {
                io_service_.stop();
            }

            EXPECT_EQ(2, monitor.connect_cnt_);      // We should have 1 connect.
            EXPECT_EQ(1, monitor.close_cnt_);        // We should have 0 closes
            ASSERT_GT(monitor.registered_fd_, -1);   // We should have a valid fd.
            int orig_fd = monitor.registered_fd_;

            // Test our socket for OOBness.
            client.closeIfOutOfBand(monitor.registered_fd_);

            // Since we're in a transaction, we should have no closes and
            // the same valid fd.
            EXPECT_EQ(1, monitor.close_cnt_);
            ASSERT_EQ(monitor.registered_fd_, orig_fd);

            EXPECT_FALSE(ec);
        },
            TcpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that we received the second response.
        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);
        EXPECT_EQ(2, sequence2->intValue());

        // Stopping the client the close the connection.
        client.stop();

        // We should have had 2 connect invocations, 2 closes
        // and an invalid registered fd
        EXPECT_EQ(2, monitor.connect_cnt_);
        EXPECT_EQ(2, monitor.close_cnt_);
        EXPECT_EQ(-1, monitor.registered_fd_);
    }

    /// @brief Simulates external registery of Connection TCP sockets
    ///
    /// Provides methods compatible with Connection callbacks for connect
    /// and close operations.
    class ExternalMonitor {
    public:
        /// @brief Constructor
        ExternalMonitor()
            : registered_fd_(-1), connect_cnt_(0), close_cnt_(0) {
        }

        /// @brief Connect callback handler
        /// @param ec Error status of the ASIO connect
        /// @param tcp_native_fd socket descriptor to register
        bool connectHandler(const boost::system::error_code& ec, int tcp_native_fd) {
            ++connect_cnt_;
            if ((!ec || (ec.value() == boost::asio::error::in_progress))
                && (tcp_native_fd >= 0)) {
                registered_fd_ = tcp_native_fd;
                return (true);
            } else if ((ec.value() == boost::asio::error::already_connected)
                       && (registered_fd_ != tcp_native_fd)) {
                return (false);
            }

            // ec indicates an error, return true, so that error can be handled
            // by Connection logic.
            return (true);
        }

        /// @brief Handshake callback handler
        /// @param ec Error status of the ASIO connect
        bool handshakeHandler(const boost::system::error_code&, int) {
            ADD_FAILURE() << "handshake callback handler is called";
            // ec indicates an error, return true, so that error can be handled
            // by Connection logic.
            return (true);
        }

        /// @brief Close callback handler
        ///
        /// @param tcp_native_fd socket descriptor to register
        void closeHandler(int tcp_native_fd) {
            ++close_cnt_;
            EXPECT_EQ(tcp_native_fd, registered_fd_) << "closeHandler fd mismatch";
            if (tcp_native_fd >= 0) {
                registered_fd_ = -1;
            }
        }

        /// @brief Keeps track of socket currently "registered" for external monitoring.
        int registered_fd_;

        /// @brief Tracks how many times the connect callback is invoked.
        int connect_cnt_;

        /// @brief Tracks how many times the close callback is invoked.
        int close_cnt_;
    };

    /// @brief Instance of the listener used in the tests.
    TcpListener listener_;

    /// @brief Instance of the second listener used in the tests.
    TcpListener listener2_;

    /// @brief Instance of the third listener used in the tests (with short idle
    /// timeout).
    TcpListener listener3_;

};

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(TcpClientTest, consecutiveRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests());
}

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(TcpClientTest, consecutiveRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests());
}

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(TcpClientTest, closeBetweenRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests());
}

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(TcpClientTest, closeBetweenRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests());
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(TcpClientTest, multipleDestinations) {
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(TcpClientTest, multipleDestinationsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(TcpClientTest, multipleTlsContexts) {
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(TcpClientTest, multipleTlsContextsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that idle connection can be resumed for second request.
TEST_F(TcpClientTest, idleConnection) {
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// Test that idle connection can be resumed for second request.
TEST_F(TcpClientTest, idleConnectionMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(TcpClientTest, unreachable) {
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(TcpClientTest, unreachableMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(TcpClientTest, malformedResponse) {
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(TcpClientTest, malformedResponseMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(TcpClientTest, clientRequestTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(TcpClientTest, clientRequestTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// This test verifies the behavior of the HTTP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(TcpClientTest, clientRequestLateStartNoQueue) {
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the HTTP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(TcpClientTest, clientRequestLateStartNoQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the HTTP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(TcpClientTest, clientRequestLateStartQueue) {
    testClientRequestLateStart(true);
}

// This test verifies the behavior of the HTTP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(TcpClientTest, clientRequestLateStartQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(true);
}

// Test that client times out when connection takes too long.
TEST_F(TcpClientTest, clientConnectTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

// Test that client times out when connection takes too long.
TEST_F(TcpClientTest, clientConnectTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

/// Tests that connect and close callbacks work correctly.
TEST_F(TcpClientTest, connectCloseCallbacks) {
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks());
}

/// Tests that connect and close callbacks work correctly.
TEST_F(TcpClientTest, connectCloseCallbacksMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks());
}

/// Tests that TcpClient::closeIfOutOfBand works correctly.
TEST_F(TcpClientTest, closeIfOutOfBand) {
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand());
}

/// Tests that TcpClient::closeIfOutOfBand works correctly.
TEST_F(TcpClientTest, closeIfOutOfBandMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand());
}
#endif

}
