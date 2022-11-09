// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <tcp/tcp_stream_msg.h>
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

/// @brief IP address to which service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to whch service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_REQUEST_TIMEOUT = 200;

/// @brief Connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

class TcpTestConnection : public TcpConnection {
public:
    TcpTestConnection(IOService& io_service,
                      const TcpConnectionAcceptorPtr& acceptor,
                      const TlsContextPtr& tls_context,
                      TcpConnectionPool& connection_pool,
                      const TcpConnectionAcceptorCallback& acceptor_callback,
                      const TcpConnectionFilterCallback& filter_callback,
                      const long idle_timeout)
     : TcpConnection(io_service, acceptor, tls_context, connection_pool,
                     acceptor_callback, filter_callback, idle_timeout) {
    }

    virtual TcpRequestPtr createRequest() {
        return (TcpStreamRequestPtr(new TcpStreamRequest()));
    }

    virtual void requestReceived(TcpRequestPtr request) {
        TcpStreamRequestPtr req = boost::dynamic_pointer_cast<TcpStreamRequest>(request);
        if (!req) {
            isc_throw(isc::Unexpected, "request not a TcpStreamRequest");
        }

        req->unpack();
        auto request_str = req->getRequestString();
        std::ostringstream os;
        if (request_str == "I am done") {
            os << "good bye";
        } else {
            os << "echo " << request_str;
        }

        TcpStreamResponsePtr resp(new TcpStreamResponse());
        resp->setResponseData(os.str());
        resp->pack();
        asyncSendResponse(resp);
    }
};

/// @brief Implementation of the TCPListener used in tests.
///
/// Implements simple stream in/out listener.
class TcpTestListener : public TcpListener {
public:

    TcpTestListener(IOService& io_service,
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
    /// This method is virtual so as it can be overridden when customized
    /// connections are to be used, e.g. in case of unit testing.
    ///
    /// @param callback Callback invoked when new connection is accepted.
    /// @return Pointer to the created connection.
    virtual TcpConnectionPtr createConnection(
            const TcpConnectionAcceptorCallback& acceptor_callback,
            const TcpConnectionFilterCallback& connection_filter) {
        TcpConnectionPtr conn(new TcpTestConnection(io_service_, acceptor_,
                                                    tls_context_, connections_,
                                                    acceptor_callback, connection_filter,
                                                    idle_timeout_));
        conn->setReadMax(read_max_);
        return (conn);
    }

    /// @brief Maximum size of a single socket read
    size_t read_max_;
};

/// @brief Test fixture class for @ref TcpListener.
class TcpListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    TcpListenerTest()
        : io_service_(), test_timer_(io_service_), run_io_service_timer_(io_service_),
         clients_(), clients_done_(0) {
        test_timer_.setup(std::bind(&TcpListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active clients.
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
    TcpTestClientPtr connectClient() {
        TcpTestClientPtr client(new TcpTestClient(io_service_,
                                    std::bind(&TcpListenerTest::clientDone, this)));
        clients_.push_back(client);
        client->connect();
        return (client);
    }

    /// @brief Connect to the endpoint and send a request.
    ///
    /// This method creates TcpTestClient instance and retains it in the clients_
    /// list.
    ///
    /// @param request String containing the request to be sent.
    void startRequest(const std::string& request) {
        TcpTestClientPtr client(new TcpTestClient(io_service_,
                                    std::bind(&TcpListenerTest::clientDone, this)));
        clients_.push_back(client);
        clients_.back()->startRequest(request);
    }

    void startRequests(const std::list<std::string>& requests) {
        TcpTestClientPtr client(new TcpTestClient(io_service_,
                                    std::bind(&TcpListenerTest::clientDone, this)));
        clients_.push_back(client);
        clients_.back()->startRequests(requests);
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

    /// @brief Callback function each client invokes when done.
    ///
    /// It stops the IO service when all clients are done.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void clientDone() {
        ++clients_done_;
        if (clients_done_ >= clients_.size()) {
            // They're all done or dead. Stop the service.
            io_service_.stop();
        }
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

    /// @brief Filter that denies every other connection.
    ///
    /// @param remote_endpoint_address ip address of the remote end of
    /// a connection.
    bool connectionFilter(const boost::asio::ip::tcp::endpoint& remote_endpoint) {
        static size_t count = 0;
        // If the address doesn't match, something hinky is going on, so
        // we'll reject them all.  If it does match, then cool, it works
        // as expected.
        if ((count++ % 2) || (remote_endpoint.address().to_string() != SERVER_ADDRESS)) {
            // Reject every other connection;
            return (false);
        }

        return (true);
    }

    /// @brief IO service used in the tests.
    IOService io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<TcpTestClientPtr> clients_;

    /// @brief Counts the number of clients that have reported as done.
    size_t clients_done_;
};

// This test verifies that A TCP connection can be established and used to
// transmit a streamed request and receive a streamed response.
TEST_F(TcpListenerTest, listen) {
    const std::string request = "I am done";

    TcpTestListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                             TlsContextPtr(), TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_TRUE(client->receiveDone());
    EXPECT_FALSE(client->expectedEof());

    listener.stop();
    io_service_.poll();
}

// This test verifies that A TCP connection can receive a complete
// message that spans multiple socket reads.
TEST_F(TcpListenerTest, splitReads) {
    const std::string request = "I am done";

    // Read at most one byte at a time.
    size_t read_max = 1;
    TcpTestListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                             TlsContextPtr(), TcpListener::IdleTimeout(IDLE_TIMEOUT), 0,
                             read_max);

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());

    // Fetch the client.
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_TRUE(client->receiveDone());
    EXPECT_FALSE(client->expectedEof());

    listener.stop();
    io_service_.poll();
}

// This test verifies that A TCP connection can be established and used to
// transmit a streamed request and receive a streamed response.
TEST_F(TcpListenerTest, idleTimeoutTest) {
    TcpTestListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                             TlsContextPtr(), TcpListener::IdleTimeout(SHORT_IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(connectClient());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // Tell the client expecting reading to fail with an EOF.
    ASSERT_NO_THROW(client->waitForEof());

    // Run until idle timer expires.
    ASSERT_NO_THROW(runIOService());
    EXPECT_FALSE(client->receiveDone());
    EXPECT_TRUE(client->expectedEof());

    listener.stop();
    io_service_.poll();
}

TEST_F(TcpListenerTest, multipleClientsListen) {
    const std::string request = "I am done";

    TcpTestListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                             TlsContextPtr(), TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    size_t num_clients = 5;
    for ( auto i = 0; i < num_clients; ++i ) {
        ASSERT_NO_THROW(startRequest(request));
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    for (auto client = clients_.begin(); client != clients_.end(); ++client) {
        EXPECT_TRUE((*client)->receiveDone());
        EXPECT_FALSE((*client)->expectedEof());
    }

    listener.stop();
    io_service_.poll();
}

// Verify that the listener handles multiple requests for multiple
// clients.
TEST_F(TcpListenerTest, multipleRequetsPerClients) {
    std::list<std::string>requests{ "one", "two", "three", "I am done"};

    TcpTestListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                             TlsContextPtr(), TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    size_t num_clients = 5;
    for ( auto i = 0; i < num_clients; ++i ) {
        ASSERT_NO_THROW(startRequests(requests));
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    std::list<std::string>expected_responses{ "echo one", "echo two", "echo three", "good bye"};
    for (auto client = clients_.begin(); client != clients_.end(); ++client) {
        EXPECT_TRUE((*client)->receiveDone());
        EXPECT_FALSE((*client)->expectedEof());
        EXPECT_EQ(expected_responses, (*client)->getResponses());
    }

    listener.stop();
    io_service_.poll();
}

// Verify that connection filtering can eliminate specific connections.
TEST_F(TcpListenerTest, filterClientsTest) {
    const std::string request = "I am done";

    TcpTestListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                             TlsContextPtr(), TcpListener::IdleTimeout(IDLE_TIMEOUT),
                             std::bind(&TcpListenerTest::connectionFilter, this, ph::_1));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    size_t num_clients = 5;
    for ( auto i = 0; i < num_clients; ++i ) {
        // Every other client sends nothing (i.e. waits for EOF) as
        // we expect the filter to reject them.
        if (i % 2 == 0) {
            ASSERT_NO_THROW(startRequest("I am done"));
        } else {
            ASSERT_NO_THROW(startRequest(""));
        }
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    size_t i = 0;
    for (auto client = clients_.begin(); client != clients_.end(); ++client) {
        if (i % 2 == 0) {
            // These clients should have been accepted and received responses.
            EXPECT_TRUE((*client)->receiveDone());
            EXPECT_FALSE((*client)->expectedEof());
        } else {
            // These clients should have been rejected and gotten EOF'd.
            EXPECT_FALSE((*client)->receiveDone());
            EXPECT_TRUE((*client)->expectedEof());
        }

        ++i;
    }

    listener.stop();
    io_service_.poll();
}

}
