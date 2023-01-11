// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/testutils/test_tls.h>
#include <asiolink/io_service.h>
#include <tcp_test_listener.h>
#include <tcp_test_client.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::tcp;

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

/// @brief Test fixture class for @ref TcpListener that uses TLS.
class TlsListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    TlsListenerTest()
        : io_service_(), test_timer_(io_service_),
          run_io_service_timer_(io_service_),
          clients_(), clients_done_(0) {
        test_timer_.setup(std::bind(&TlsListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT,
                          IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active clients.
    virtual ~TlsListenerTest() {
        for (auto client : clients_) {
            client->close();
        }
    }

    /// @brief Fetch the server TLS context.
    TlsContextPtr serverContext() {
        TlsContextPtr tls_context;
        configServer(tls_context);
        return(tls_context);
    }

    /// @brief Fetch a client TLS context that works with the server context.
    TlsContextPtr clientContext() {
        TlsContextPtr tls_context;
        configClient(tls_context);
        return(tls_context);
    }

    /// @brief Create a new client.
    ///
    /// This method creates TcpTestClient instance and retains it in
    /// the clients_ list.
    /// @param tls_context TLS context to assign to the client.
    TcpTestClientPtr createClient(TlsContextPtr tls_context) {
        TcpTestClientPtr client(new TcpTestClient(io_service_,
                                    std::bind(&TlsListenerTest::clientDone, this),
                                    tls_context));
        clients_.push_back(client);
        return (client);
    }

    /// @brief Connect to the endpoint and send a request.
    ///
    /// This method creates TcpTestClient instance and retains it in
    /// the clients_ list.
    ///
    /// @param request String containing the request to be sent.
    /// @param tls_context TLS context to assign to the client.
    void startRequest(const std::string& request, TlsContextPtr tls_context) {
        ASSERT_TRUE(tls_context);
        TcpTestClientPtr client = createClient(tls_context);
        client->startRequest(request);
    }

    /// @brief Connect to the endpoint and send a list of requests.
    ///
    /// This method creates a TcpTestClient instance and initiates a
    /// series of requests.
    ///
    /// @param request String containing the request to be sent.
    /// @param tls_context TLS context to assign to the client.
    void startRequests(const std::list<std::string>& requests,
                       TlsContextPtr tls_context) {
        ASSERT_TRUE(tls_context);
        TcpTestClientPtr client = createClient(tls_context);
        client->startRequests(requests);
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
            run_io_service_timer_.setup(std::bind(&TlsListenerTest::timeoutHandler,
                                                  this, false),
                                        timeout,
                                        IntervalTimer::ONE_SHOT);
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
        if ((count++ % 2) ||
            (remote_endpoint.address().to_string() != SERVER_ADDRESS)) {
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

// This test verifies that a TLS connection can be established with a client
// with valid TLS credentials.
TEST_F(TlsListenerTest, listen) {
    const std::string request = "I am done";

    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request, clientContext()));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_TRUE(client->receiveDone());
    EXPECT_FALSE(client->expectedEof());

    // Verify the audit trail for the connection.
    // Sanity check to make sure we don't have more entries than we expect.
    ASSERT_EQ(listener.audit_trail_->entries_.size(), 2);

    // Create the list of expected entries.
    std::list<AuditEntry> expected_entries {
        { 1, AuditEntry::INBOUND, "I am done" },
        { 1, AuditEntry::OUTBOUND, "good bye" }
    };

    // Verify the audit trail.
    ASSERT_EQ(expected_entries, listener.audit_trail_->getConnectionTrail(1));

    listener.stop();
    io_service_.poll();
}

// This test verifies that a TLS connection is denied to a client
// with invalid TLS credentials.
TEST_F(TlsListenerTest, badClient) {
    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());

    TlsContextPtr bad_client_ctx;
    configSelf(bad_client_ctx);
    ASSERT_NO_THROW(startRequest("", bad_client_ctx));

    ASSERT_NO_THROW(runIOService());

    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_FALSE(client->receiveDone());

    // Either we failed during handshake or we EOF'd as expected.  OpenSSL fails
    // after handshake, Botan before it.
    EXPECT_TRUE(client->expectedEof() || client->handshakeFailed());
}

// This test verifies that a TLS connection can receive a complete
// message that spans multiple socket reads.
TEST_F(TlsListenerTest, splitReads) {
    const std::string request = "I am done";

    // Read at most one byte at a time.
    size_t read_max = 1;
    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(IDLE_TIMEOUT),
                             0,
                             read_max);

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request, clientContext()));
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

// This test verifies that a TLS connection can be established and used to
// transmit a streamed request and receive a streamed response.
TEST_F(TlsListenerTest, idleTimeoutTest) {
    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(SHORT_IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    // Start a client with an empty request. Empty requests tell the client
    // to read without sending anything and expect the read to fail when
    // the listener idle times out the socket.
    ASSERT_NO_THROW(startRequest("", clientContext()));

    // Run until idle timer expires.
    ASSERT_NO_THROW(runIOService());

    ASSERT_EQ(1, clients_.size());
    TcpTestClientPtr client = *clients_.begin();
    EXPECT_FALSE(client->receiveDone());
    EXPECT_TRUE(client->expectedEof());

    listener.stop();
    io_service_.poll();
}

// This test verifies that TLS connections with multiple clients.
TEST_F(TlsListenerTest, multipleClientsListen) {
    const std::string request = "I am done";

    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    size_t num_clients = 5;
    for (auto i = 0; i < num_clients; ++i) {
        ASSERT_NO_THROW(startRequest(request, clientContext()));
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    size_t connection_id = 1;
    for (auto client : clients_) {
        EXPECT_TRUE(client->receiveDone());
        EXPECT_FALSE(client->expectedEof());
        // Create the list of expected entries.
        std::list<AuditEntry> expected_entries {
            { connection_id, AuditEntry::INBOUND, "I am done" },
            { connection_id, AuditEntry::OUTBOUND, "good bye" }
        };

        // Fetch the entries for this connection.
        auto entries = listener.audit_trail_->getConnectionTrail(connection_id);
        ASSERT_EQ(expected_entries, entries);
        ++connection_id;
    }

    listener.stop();
    io_service_.poll();
}

// Verify that the listener handles multiple requests for multiple
// clients.
TEST_F(TlsListenerTest, multipleRequetsPerClients) {
    std::list<std::string>requests{ "one", "two", "three", "I am done"};

    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    size_t num_clients = 5;
    for (auto i = 0; i < num_clients; ++i) {
        ASSERT_NO_THROW(startRequests(requests, clientContext()));
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    std::list<std::string>expected_responses{ "echo one", "echo two",
                                              "echo three", "good bye"};
    size_t connection_id = 1;
    for (auto client : clients_) {
        EXPECT_TRUE(client->receiveDone());
        EXPECT_FALSE(client->expectedEof());
        EXPECT_EQ(expected_responses, client->getResponses());

        // Verify the connection's audit trail.
        // Create the list of expected entries.
        std::list<AuditEntry> expected_entries {
            { connection_id, AuditEntry::INBOUND, "one" },
            { connection_id, AuditEntry::OUTBOUND, "echo one" },
            { connection_id, AuditEntry::INBOUND, "two" },
            { connection_id, AuditEntry::OUTBOUND, "echo two" },
            { connection_id, AuditEntry::INBOUND, "three" },
            { connection_id, AuditEntry::OUTBOUND, "echo three" },
            { connection_id, AuditEntry::INBOUND, "I am done" },
            { connection_id, AuditEntry::OUTBOUND, "good bye" }
        };

        // Fetch the entries for this connection.
        auto entries = listener.audit_trail_->getConnectionTrail(connection_id);
        ASSERT_EQ(expected_entries, entries);
        ++connection_id;
    }

    listener.stop();
    io_service_.poll();
}

// Verify that connection filtering can eliminate specific connections.
TEST_F(TlsListenerTest, filterClientsTest) {
    TcpTestListener listener(io_service_,
                             IOAddress(SERVER_ADDRESS),
                             SERVER_PORT,
                             serverContext(),
                             TcpListener::IdleTimeout(IDLE_TIMEOUT),
                             std::bind(&TlsListenerTest::connectionFilter, this, ph::_1));

    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    size_t num_clients = 5;
    for (auto i = 0; i < num_clients; ++i) {
        // Every other client sends nothing (i.e. waits for EOF) as
        // we expect the filter to reject them.
        if (i % 2 == 0) {
            ASSERT_NO_THROW(startRequest("I am done", clientContext()));
        } else {
            ASSERT_NO_THROW(startRequest("", clientContext()));
        }
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    size_t i = 0;
    for (auto client : clients_) {
        if (i % 2 == 0) {
            // These clients should have been accepted and received responses.
            EXPECT_TRUE(client->receiveDone());
            EXPECT_FALSE(client->expectedEof());
            EXPECT_FALSE(client->handshakeFailed());

            // Now verify the AuditTrail.
            // Create the list of expected entries.
            std::list<AuditEntry> expected_entries {
                { i+1, AuditEntry::INBOUND, "I am done" },
                { i+1, AuditEntry::OUTBOUND, "good bye" }
            };

            auto entries = listener.audit_trail_->getConnectionTrail(i+1);
            ASSERT_EQ(expected_entries, entries);

        } else {
            // Connection filtering closes the connection before the client
            // initiates the handshake, causing the subsequent handshake attempt
            // to fail.
            EXPECT_FALSE(client->receiveDone());
            EXPECT_FALSE(client->expectedEof());
            EXPECT_TRUE(client->handshakeFailed());

            // Verify connection recorded no audit entries.
            auto entries = listener.audit_trail_->getConnectionTrail(i+1);
            ASSERT_EQ(entries.size(), 0);
        }

        ++i;
    }

    listener.stop();
    io_service_.poll();
}

}
