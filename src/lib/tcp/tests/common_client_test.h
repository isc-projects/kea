// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMON_CLIENT_TEST_H
#define COMMON_CLIENT_TEST_H

namespace isc {
namespace tcp {
namespace test {

/// @brief IP address to which TCP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to whch TCP service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which TCP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Completion checker.
///
/// Messages are by 2 byte length header and data of this length.
///
/// @param response Response to check.
/// @param error_msg Reference to the error message.
/// @return status (0 not complete, > 0 complete, < 0 error).
static int
TestCompleteCheck(const WireDataPtr& response, std::string& error_msg) {
    if (!response) {
        error_msg = "response is null";
        return (-1);
    }
    size_t length = response->size();
    if (length < 2) {
        return (-2);
    }
    const std::vector<uint8_t>& content = *response;
    size_t wanted = (content[0] << 8) | content[1];
    if (wanted + 2 == response->size()) {
        // Complete.
        return (1);
    } else if (wanted + 2 > response->size()) {
        // Not complete.
        return (0);
    } else {
        // Overrun.
        error_msg = "overrun";
        return (-3);
    }
}

/// @brief Derivation of TcpResponse used for testing.
class TcpTestResponse : public TcpResponse {
public:
    /// @brief Constructor.
    TcpTestResponse(const WireData& data) {
        wire_data_ = data;
    }

    /// Destructor.
    virtual ~TcpTestResponse() = default;

    /// @brief Packs the response content into wire data buffer.
    virtual void pack() {
    }
};

/// @brief Defines a smart pointer to a TcpTestResponse.
typedef boost::shared_ptr<TcpTestResponse> TcpTestResponsePtr;

/// @brief Derivation of TcpConnection used for testing.
class TcpTestConnection : public TcpConnection {
public:
    /// @brief Constructor.
    TcpTestConnection(const IOServicePtr& io_service,
                      const TcpConnectionAcceptorPtr& acceptor,
                      const TlsContextPtr& tls_context,
                      TcpConnectionPool& connection_pool,
                      const TcpConnectionAcceptorCallback& acceptor_callback,
                      const TcpConnectionFilterCallback& filter_callback,
                      const long idle_timeout)
     : TcpConnection(io_service, acceptor, tls_context, connection_pool,
                     acceptor_callback, filter_callback, idle_timeout) {
    }

    /// @brief Creates a new empty request ready to receive data.
    virtual TcpRequestPtr createRequest() {
        return (TcpStreamRequestPtr(new TcpStreamRequest()));
    }

    /// @brief Processes a completely received request.
    ///
    /// Forms and sends a response.
    ///
    /// @param request Request to process.
    virtual void requestReceived(TcpRequestPtr request) {
        TcpStreamRequestPtr stream_req = boost::dynamic_pointer_cast<TcpStreamRequest>(request);
        if (!stream_req) {
            isc_throw(isc::Unexpected, "request not a TcpStreamRequest");
        }

        // Unpack the request.
        stream_req->unpack();
        std::string request_str = stream_req->getRequestString();

        // Create the response.
        std::string response_str;

        if (request_str.find("Malformed", 0) != std::string::npos) {
            TcpTestResponsePtr response;
            WireData bad = { 0, 0, 0, 0 };
            response.reset(new TcpTestResponse(bad));
            asyncSendResponse(response);
            return;
        } else if (request_str.find("Partial", 0) != std::string::npos) {
            TcpTestResponsePtr response;
            WireData bad = { 1, 0, 0, 0 };
            response.reset(new TcpTestResponse(bad));
            asyncSendResponse(response);
            return;
        } else {
            response_str = request_str;
        }
        std::ostringstream os;


        // Ship the response if it's not empty.
        TcpStreamResponsePtr response;
        if (!response_str.empty()) {
            response.reset(new TcpStreamResponse());
            response->setResponseData(response_str);
            response->pack();
            asyncSendResponse(response);
        }
    }

    /// @brief Processes a response once it has been sent.
    ///
    /// Returns true, signifying that the connection should start
    /// the idle timer.
    ///
    /// @param response Response that was sent to the remote endpoint.
    virtual bool responseSent(TcpResponsePtr response) {
        return (true);
    }
};

/// @brief Defines a shared pointer to a TcpTestConnection.
typedef boost::shared_ptr<TcpTestConnection> TcpTestConnectionPtr;

/// @brief Implementation of the TCPListener used in tests.
///
/// Implements simple stream in/out listener.
class TcpTestListener : public TcpListener {
public:
    /// @brief Constructor
    TcpTestListener(const IOServicePtr& io_service,
                    const IOAddress& server_address,
                    const unsigned short server_port,
                    const TlsContextPtr& tls_context,
                    const IdleTimeout& idle_timeout,
                    const TcpConnectionFilterCallback& filter_callback = 0,
                    const size_t read_max = 32 * 1024)
        : TcpListener(io_service, server_address, server_port,
                      tls_context, idle_timeout, filter_callback),
          read_max_(read_max) {
    }

protected:
    /// @brief Creates an instance of the @c TcpConnection.
    ///
    /// @param callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    /// @return Pointer to the created connection.
    virtual TcpConnectionPtr createConnection(
            const TcpConnectionAcceptorCallback& acceptor_callback,
            const TcpConnectionFilterCallback& connection_filter) {
        return(createTestConnection(acceptor_callback, connection_filter));
    }

    /// @brief Creates an instance of the @c TcpTestConnection.
    ///
    /// @param acceptor_callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    /// @param callback invoked by requestReceived() to build a response
    ///
    /// @return Pointer to the created connection.
    virtual TcpTestConnectionPtr createTestConnection(
            const TcpConnectionAcceptorCallback& acceptor_callback,
            const TcpConnectionFilterCallback& connection_filter) {
        TcpTestConnectionPtr conn(new TcpTestConnection(io_service_,
                                                        acceptor_,
                                                        tls_context_,
                                                        connections_,
                                                        acceptor_callback,
                                                        connection_filter,
                                                        idle_timeout_));
        conn->setReadMax(read_max_);
        return (conn);
    }

    /// @brief Maximum size of a single socket read
    size_t read_max_;
};

/// @brief Defines a pointer to a TcpTestListener.
typedef boost::shared_ptr<TcpTestListener> TcpTestListenerPtr;

/// @brief Test fixture class for @ref TcpListener.
class TcpListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    TcpListenerTest()
        : io_service_(new IOService()), test_timer_(io_service_),
          run_io_service_timer_(io_service_) {
        test_timer_.setup(std::bind(&TcpListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active TCP clients.
    virtual ~TcpListenerTest() {
        test_timer_.cancel();
        io_service_->stopAndPoll();
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

    /// @brief Runs IO service with optional timeout.
    ///
    /// @param timeout Optional value specifying for how long the io service
    /// should be ran.
    void runIOService(long timeout = 0) {
        io_service_->stop();
        io_service_->restart();

        if (timeout > 0) {
            run_io_service_timer_.setup(std::bind(&TcpListenerTest::timeoutHandler,
                                                  this, false),
                                        timeout, IntervalTimer::ONE_SHOT);
        }
        io_service_->run();
        io_service_->stopAndPoll(false);
    }

    /// @brief IO service used in the tests.
    IOServicePtr io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;
};

/// @brief Test fixture class for testing TCP client.
class BaseTcpClientTest : public TcpListenerTest {
public:

    /// @brief Constructor.
    BaseTcpClientTest()
        : TcpListenerTest(), listener_(), listener2_(), listener3_(),
          server_context_(), client_context_(), client_context2_() {
    }

    /// @brief Destructor.
    virtual ~BaseTcpClientTest() {
        listener_->stop();
        listener2_->stop();
        listener3_->stop();
        io_service_->stopAndPoll();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Creates TCP request.
    ///
    /// It includes a parameter with a specified value.
    ///
    /// @param parameter_name Parameter to be included.
    /// @param value Parameter value.
    template<typename ValueType>
    WireDataPtr createRequest(const std::string& parameter_name,
                                const ValueType& value) {
        std::ostringstream oss;
        oss << parameter_name << "=" << value;
        std::string data = oss.str();
        std::vector<uint8_t> content;
        content.resize(2 + data.size());
        content[0] = (data.size() >> 8) & 0xff;
        content[1] = data.size() & 0xff;
        memmove(&content[2], &data[0], content.size() - 2);
        WireDataPtr request(new WireData(content));
        return (request);
    }

    /// @brief Test that two consecutive requests can be sent over the same
    /// connection (if persistent, if not persistent two connections will
    /// be used).
    ///
    /// @param persistent Persistent flag.
    void testConsecutiveRequests(bool persistent) {
        // Start the server.
        ASSERT_NO_THROW(listener_->start());

        // Create a client and specify the server.
        TcpClient client(io_service_, false);
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        // Initiate request to the server.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                persistent, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Initiate another request to the destination.
        WireDataPtr request2 = createRequest("sequence", 2);
        WireDataPtr response2(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request2, response2,
                                                persistent, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that the received responses are different.
        ASSERT_TRUE(response1);
        ASSERT_TRUE(response2);
        EXPECT_NE(*response1, *response2);
    }

    /// @brief Test that the client can communicate with two different
    /// destinations simultaneously.
    void testMultipleDestinations() {
        // Start two servers running on different ports.
        ASSERT_NO_THROW(listener_->start());
        ASSERT_NO_THROW(listener2_->start());

        // Create the client. It will be communicating with the two servers.
        TcpClient client(io_service_, false);

        // Specify the addresses and ports of the servers.
        IOAddress address1("127.0.0.1");
        uint16_t port1 = 18123;
        IOAddress address2("::1");
        uint16_t port2 = 18124;

        // Create a request to the first server.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(address1, port1,
                                                client_context_,
                                                request1, response1,
                                                true, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Create a request to the second server.
        WireDataPtr request2 = createRequest("sequence", 2);
        WireDataPtr response2(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address2, port2,
                                                client_context_,
                                                request2, response2,
                                                true, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());

        // Make sure we have received two different responses.
        ASSERT_TRUE(response1);
        ASSERT_TRUE(response2);
        EXPECT_NE(*response1, *response2);
    }

    /// @brief Test that the client can communicate with the same destination
    /// address and port but with different TLS contexts too.
    void testMultipleTlsContexts() {
        // Start only one server.
        ASSERT_NO_THROW(listener_->start());

        // Create the client.
        TcpClient client(io_service_, false);

        // Specify the address and port of the server.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        // Create a request to the first server.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                true, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Create a request with the second TLS context.
        WireDataPtr request2 = createRequest("sequence", 2);
        WireDataPtr response2(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context2_,
                                                request2, response2,
                                                true, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());

        // Make sure we have received two different responses.
        ASSERT_TRUE(response1);
        ASSERT_TRUE(response2);
        EXPECT_NE(*response1, *response2);
    }

    /// @brief Test that idle connection can be resumed for second request.
    void testIdleConnection() {
        // Start the server that has short idle timeout. It closes the idle
        // connection after 200ms.
        ASSERT_NO_THROW(listener3_->start());

        // Create the client that will communicate with this server.
        TcpClient client(io_service_, false);

        // Specify the address and port of this server.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18125;

        // Create the first request.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                true, TestCompleteCheck,
            [this](const boost::system::error_code& ec, const WireDataPtr&,
                   const std::string&) {
                io_service_->stop();
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Run the IO service until the response is received.
        ASSERT_NO_THROW(runIOService());

        // Make sure the response has been received.
        ASSERT_TRUE(response1);
        EXPECT_EQ(request1->size(), response1->size());

        // Delay the generation of the second request by 2x server idle timeout.
        // This should be enough to cause the server to close the connection.
        ASSERT_NO_THROW(runIOService(SHORT_IDLE_TIMEOUT * 2));

        // Create another request.
        WireDataPtr request2 = createRequest("sequence", 2);
        WireDataPtr response2(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request2, response2,
                                                true, TestCompleteCheck,
            [this](const boost::system::error_code& ec, const WireDataPtr&,
                   const std::string&) {
                io_service_->stop();
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
            }));

        // Actually trigger the second request.
        ASSERT_NO_THROW(runIOService());

        // Make sure that the server has responded.
        ASSERT_TRUE(response2);
        EXPECT_EQ(request2->size(), response2->size());
        EXPECT_NE(*response1, *response2);
    }

    /// @brief This test verifies that the client returns IO error code when the
    /// server is unreachable.
    void testUnreachable () {
        // Create the client.
        TcpClient client(io_service_, false);

        // Specify the address and port of the server. This server is down.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        // Create the request.
        WireDataPtr request = createRequest("sequence", 1);
        WireDataPtr response(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request, response,
                                                true, TestCompleteCheck,
            [this](const boost::system::error_code& ec,
                   const WireDataPtr&,
                   const std::string&) {
                io_service_->stop();
                // The server should have returned an IO error.
                if (!ec) {
                    ADD_FAILURE() << "asyncSendRequest didn't fail";
                }
            }));

        // Actually trigger the request.
        ASSERT_NO_THROW(runIOService());
    }

    void testMalformedResponse() {
        // Start the server.
        ASSERT_NO_THROW(listener_->start());

        // Create the client.
        TcpClient client(io_service_, false);

        // Specify the address and port of the server.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        WireDataPtr request = createRequest("Malformed", "...");
        WireDataPtr response(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request, response,
                                                true, TestCompleteCheck,
            [this](const boost::system::error_code& ec,
                   const WireDataPtr& response,
                   const std::string& parsing_error) {
                io_service_->stop();
                // There should be no IO error (answer from the server is received).
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
                // The response object is null.
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
        ASSERT_NO_THROW(listener_->start());

        // Create the client.
        TcpClient client(io_service_, false);

        // Specify the address and port of the server.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        unsigned cb_num = 0;

        WireDataPtr request1 = createRequest("Partial", "...");
        WireDataPtr response1(new WireData());
        // This value will be set to true if the connection close callback is
        // invoked upon time out.
        auto connection_closed = false;
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                true, TestCompleteCheck,
            [this, &cb_num](const boost::system::error_code& ec,
                            const WireDataPtr& response,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_->stop();
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
        WireDataPtr request2 = createRequest("sequence", 1);
        WireDataPtr response2(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request2, response2,
                                                true, TestCompleteCheck,
            [this, &cb_num](const boost::system::error_code& /*ec*/,
                            const WireDataPtr&,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_->stop();
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
        ASSERT_NO_THROW(listener_->start());

        // Create the client.
        TcpClient client(io_service_, false);

        // Specify the address and port of the server.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        unsigned cb_num = 0;

        WireDataPtr request = createRequest("sequence", 1);
        WireDataPtr response(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request, response,
                                                true, TestCompleteCheck,
            [this, &cb_num](const boost::system::error_code& ec,
                            const WireDataPtr& response,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_->stop();
                }
                // In this particular case we know exactly the type of the
                // IO error returned, because the client explicitly sets this
                // error code.
                EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
                // There should be no response returned.
                EXPECT_FALSE(response);

            },
            TcpClient::RequestTimeout(100),

            // This callback is invoked upon an attempt to connect to the
            // server. The false value indicates to the TcpClient to not
            // try to send a request to the server. This simulates the
            // case of connect() taking very long and should eventually
            // cause the transaction to time out.
            [](const boost::system::error_code& /*ec*/, int) {
                return (false);
            }));

        // Create another request after the timeout. It should be handled ok.
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request, response,
                                                true, TestCompleteCheck,
            [this, &cb_num](const boost::system::error_code& /*ec*/,
                            const WireDataPtr&,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_->stop();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Tests the behavior of the TCP client when the premature
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
        ASSERT_NO_THROW(listener_->start());

        // Create the client.
        TcpClient client(io_service_, false);

        // Specify the address and port of the server.
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        // Generate first request.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());

        // Use very short timeout to make sure that it occurs before we actually
        // run the transaction.
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                true, TestCompleteCheck,
            [](const boost::system::error_code& ec,
               const WireDataPtr& response,
               const std::string&) {

            // In this particular case we know exactly the type of the
            // IO error returned, because the client explicitly sets this
            // error code.
            EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
            // There should be no response returned.
            EXPECT_FALSE(response);
        },
        TcpClient::RequestTimeout(1)));

        if (queue_two_requests) {
            WireDataPtr request2 = createRequest("sequence", 2);
            WireDataPtr response2(new WireData());
            ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                    client_context_,
                                                    request2, response2,
                                                    true, TestCompleteCheck,
                [](const boost::system::error_code& ec,
                   const WireDataPtr& response,
                   const std::string&) {

                // This second request should be successful.
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
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
        WireDataPtr request3 = createRequest("sequence", 3);
        WireDataPtr response3(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request3, response3,
                                                true, TestCompleteCheck,
                         [this](const boost::system::error_code& ec,
                                const WireDataPtr&,
                                const std::string&) {
            io_service_->stop();

            // Everything should be ok.
            if (ec) {
                ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
            }
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Tests that underlying TCP socket can be registered and
    /// unregistered via connection and close callbacks.
    ///
    /// It conducts to consecutive requests over the same client.
    ///
    /// @param persistent Persistent flag.
    void testConnectCloseCallbacks(bool persistent) {
        // Start the server.
        ASSERT_NO_THROW(listener_->start());

        // Create a client and specify the address and port of the server.
        TcpClient client(io_service_, false);
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        // Initiate request to the server.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());
        unsigned resp_num = 0;
        ExternalMonitor monitor(!!client_context_);

        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                persistent, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }

                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();

                }
            },
            TcpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Initiate another request to the destination.
        WireDataPtr request2 = createRequest("sequence", 2);
        WireDataPtr response2(new WireData());
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request2, response2,
                                                persistent, TestCompleteCheck,
            [this, &resp_num](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num > 1) {
                    io_service_->stop();
                }
                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
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

        // Make sure that the received responses are different.
        ASSERT_TRUE(response1);
        ASSERT_TRUE(response2);
        EXPECT_NE(*response1, *response2);

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
    /// @param persistent Persistent flag.
    void testCloseIfOutOfBand(bool persistent) {
        // Start the server.
        ASSERT_NO_THROW(listener_->start());

        // Create a client and specify the address and port of the server.
        TcpClient client(io_service_, false);
        asiolink::IOAddress address("127.0.0.1");
        uint16_t port = 18123;

        // Initiate request to the server.
        WireDataPtr request1 = createRequest("sequence", 1);
        WireDataPtr response1(new WireData());
        unsigned resp_num = 0;
        ExternalMonitor monitor(!!client_context_);

        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request1, response1,
                                                persistent, TestCompleteCheck,
            [this, &client, &resp_num, &monitor](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num == 1) {
                    io_service_->stop();
                }

                // We should have 1 connect.
                EXPECT_EQ(1, monitor.connect_cnt_);
                // We should have 1 handshake with TLS.
                if (client_context_) {
                    EXPECT_EQ(1, monitor.handshake_cnt_);
                }
                // We should have 0 closes
                EXPECT_EQ(0, monitor.close_cnt_);
                // We should have a valid fd.
                ASSERT_GT(monitor.registered_fd_, -1);
                int orig_fd = monitor.registered_fd_;

                // Test our socket for OOBness.
                client.closeIfOutOfBand(monitor.registered_fd_);

                // Since we're in a transaction, we should have no closes and
                // the same valid fd.
                EXPECT_EQ(0, monitor.close_cnt_);
                ASSERT_EQ(monitor.registered_fd_, orig_fd);

                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
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
        EXPECT_EQ(request1->size(), response1->size());

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
        WireDataPtr request2 = createRequest("sequence", 2);
        WireDataPtr response2(new WireData());
        resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(address, port,
                                                client_context_,
                                                request2, response2,
                                                persistent, TestCompleteCheck,
            [this, &client, &resp_num, &monitor](const boost::system::error_code& ec,
                              const WireDataPtr&,
                              const std::string&) {
                if (++resp_num == 1) {
                    io_service_->stop();
                }

                // We should have 2 connects.
                EXPECT_EQ(2, monitor.connect_cnt_);
                // We should have 2 handshakes when TLS is enabled.
                if (client_context_) {
                    EXPECT_EQ(2, monitor.handshake_cnt_);
                }
                // We should have 1 close.
                EXPECT_EQ(1, monitor.close_cnt_);
                // We should have a valid fd.
                ASSERT_GT(monitor.registered_fd_, -1);
                int orig_fd = monitor.registered_fd_;

                // Test our socket for OOBness.
                client.closeIfOutOfBand(monitor.registered_fd_);

                // Since we're in a transaction, we should have no closes and
                // the same valid fd.
                EXPECT_EQ(1, monitor.close_cnt_);
                ASSERT_EQ(monitor.registered_fd_, orig_fd);

                if (ec) {
                    ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
                }
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
        EXPECT_EQ(request2->size(), response2->size());
        EXPECT_NE(*response1, *response2);

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
        ///
        /// @param use_tls Use TLS flag.
        ExternalMonitor(bool use_tls = false)
            : use_tls_(use_tls), registered_fd_(-1), connect_cnt_(0),
              handshake_cnt_(0), close_cnt_(0) {
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
            if (use_tls_) {
                ++handshake_cnt_;
            } else {
                ADD_FAILURE() << "handshake callback handler is called";
            }
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

        /// @brief Use TLS flag.
        bool use_tls_;

        /// @brief Keeps track of socket currently "registered" for external monitoring.
        int registered_fd_;

        /// @brief Tracks how many times the connect callback is invoked.
        int connect_cnt_;

        /// @brief Tracks how many times the handshake callback is invoked.
        int handshake_cnt_;

        /// @brief Tracks how many times the close callback is invoked.
        int close_cnt_;
    };

    /// @brief Instance of the listener used in the tests.
    std::unique_ptr<TcpTestListener> listener_;

    /// @brief Instance of the second listener used in the tests.
    std::unique_ptr<TcpTestListener> listener2_;

    /// @brief Instance of the third listener used in the tests (with short idle
    /// timeout).
    std::unique_ptr<TcpTestListener> listener3_;

    /// @brief Server TLS context.
    TlsContextPtr server_context_;

    /// @brief Client TLS context.
    TlsContextPtr client_context_;

    /// @brief Alternate client TLS context.
    TlsContextPtr client_context2_;
};

}
}
}
#endif // COMMON_CLIENT_TEST_H
