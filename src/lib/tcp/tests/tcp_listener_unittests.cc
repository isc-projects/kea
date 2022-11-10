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

/// @brief Describes stream message sent over a connection.
class AuditEntry {
public:
    enum Direction {
        INBOUND,  // data received
        OUTBOUND  // data sent
    };

    /// @brief Constructor
    ///
    /// @param connection_id Id of the client to whom the entry pertains
    /// @param direction INBOUND for data received, OUTBOUND for data sent
    /// @param data string form of the data involved
    AuditEntry(size_t connection_id, const AuditEntry::Direction& direction, const std::string& data)
        : connection_id_(connection_id), direction_(direction), data_(data) {
    }

    /// @brief Equality operator.
    ///
    /// @param other value to be compared.
    bool operator==(const AuditEntry& other) const {
        return ((connection_id_ == other.connection_id_) &&
                (direction_ == other.direction_) &&
                (data_ == other.data_));
    }

    /// @brief Unique client identifier.
    size_t connection_id_;

    /// @brief Indicates which direction the data traveled
    Direction direction_;

    /// @brief Contains the data sent or received.
    std::string data_;
};

std::ostream&
operator<<(std::ostream& os, const AuditEntry& entry) {
    os << "{ " << entry.connection_id_ << ", "
       << (entry.direction_ == AuditEntry::INBOUND ? "I" : "O") << ", "
       << entry.data_ << " }";
    return (os);
}

/// @brief Contains the data receipt/transmission history for an arbitrary number
/// of connections.
class AuditTrail {
public:
    /// @brief Adds an entry to the audit trail.
    ///
    /// @param connection_id Id of the client to whom the entry pertains
    /// @param direction INBOUND for data received, OUTBOUND for data sent
    /// @param data string form of the data involved
    void addEntry(size_t connection_id, const AuditEntry::Direction& direction, const std::string& data) {
        // will need a mutex
        entries_.push_back(AuditEntry(connection_id, direction, data));
    }

    /// @brief Returns a list of AuditEntry(s) for a given connection.
    ///
    /// @param connection_id Id of the desired connection
    /// @return A list of entries for the connection or an empty list if none are found.
    std::list<AuditEntry> getConnectionTrail(size_t connection_id) {
        std::list<AuditEntry> conn_entries;
        for (auto entry_it = entries_.begin(); entry_it != entries_.end(); ++entry_it) {
            if ((*entry_it).connection_id_ == connection_id) {
                conn_entries.push_back(*entry_it);
            }
        }

        return (conn_entries);
    }

    /// @brief Dumps the audit trail as a string.
    std::string dump() {
        std::stringstream ss;
        for (auto entry_it = entries_.begin(); entry_it != entries_.end(); ++entry_it) {
            ss << (*entry_it) << std::endl;
        }

        return (ss.str());
    }

    /// @brief Contains the audit entries.
    std::list<AuditEntry> entries_;
};

/// @brief Defines a pointer to an AuditTrail
typedef boost::shared_ptr<AuditTrail> AuditTrailPtr;

/// @brief Derivation of TcpConnection used for testing.
class TcpTestConnection : public TcpConnection {
public:
    /// @brief Constructor
    TcpTestConnection(IOService& io_service,
                      const TcpConnectionAcceptorPtr& acceptor,
                      const TlsContextPtr& tls_context,
                      TcpConnectionPool& connection_pool,
                      const TcpConnectionAcceptorCallback& acceptor_callback,
                      const TcpConnectionFilterCallback& filter_callback,
                      const long idle_timeout,
                      size_t connection_id,
                      AuditTrailPtr audit_trail)
     : TcpConnection(io_service, acceptor, tls_context, connection_pool,
                     acceptor_callback, filter_callback, idle_timeout),
                     connection_id_(connection_id), audit_trail_(audit_trail) {
    }

    /// @brief Creats a new empty request ready to receive data.
    virtual TcpRequestPtr createRequest() {
        return (TcpStreamRequestPtr(new TcpStreamRequest()));
    }

    /// @brief Processes a completely received request.
    ///
    /// Adds the request to the audit trail, then forms and sends a response.
    /// If the request is "I am done", the response is "good bye" which should instruct
    /// the client to disconnect.
    ///
    /// @param request Request to process.
    virtual void requestReceived(TcpRequestPtr request) {
        TcpStreamRequestPtr req = boost::dynamic_pointer_cast<TcpStreamRequest>(request);
        if (!req) {
            isc_throw(isc::Unexpected, "request not a TcpStreamRequest");
        }

        req->unpack();
        auto request_str = req->getRequestString();
        audit_trail_->addEntry(connection_id_, AuditEntry::INBOUND, request_str);

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

    /// @brief Processes a response once it has been sent.
    ///
    /// Adds the response to the audit trail and returns true, signifying
    /// that the connection should start the idle timer.
    ///
    /// @param response Response that was sent to the remote endpoint.
    virtual bool responseSent(TcpResponsePtr response) {
        TcpStreamResponsePtr resp = boost::dynamic_pointer_cast<TcpStreamResponse>(response);
        if (!resp) {
            isc_throw(isc::Unexpected, "resp not a TcpStreamResponse");
        }

        audit_trail_->addEntry(connection_id_, AuditEntry::OUTBOUND, resp->getResponseString());
        return (true);
    }

private:
    /// @brief Id of this connection.
    size_t connection_id_;

    /// @brief Provides request/response history.
    AuditTrailPtr audit_trail_;
};

/// @brief Implementation of the TCPListener used in tests.
///
/// Implements simple stream in/out listener.
class TcpTestListener : public TcpListener {
public:
    /// @brief Constructor
    TcpTestListener(IOService& io_service,
                    const IOAddress& server_address,
                    const unsigned short server_port,
                    const TlsContextPtr& tls_context,
                    const IdleTimeout& idle_timeout,
                    const TcpConnectionFilterCallback& filter_callback = 0,
                    const size_t read_max = 32 * 1024)
        : TcpListener(io_service, server_address, server_port,
                      tls_context, idle_timeout, filter_callback),
                      read_max_(read_max), next_connection_id_(0),
                      audit_trail_(new AuditTrail()) {
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
        TcpConnectionPtr conn(new TcpTestConnection(io_service_, acceptor_, tls_context_,
                                                    connections_, acceptor_callback,
                                                    connection_filter, idle_timeout_,
                                                    ++next_connection_id_,  audit_trail_));
        conn->setReadMax(read_max_);
        return (conn);
    }

    /// @brief Maximum size of a single socket read
    size_t read_max_;

    /// @brief Id to use for the next connection.
    size_t next_connection_id_;

public:
    AuditTrailPtr audit_trail_;
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

    size_t connection_id = 1;
    for (auto client = clients_.begin(); client != clients_.end(); ++client) {
        EXPECT_TRUE((*client)->receiveDone());
        EXPECT_FALSE((*client)->expectedEof());
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
    size_t connection_id = 1;
    for (auto client = clients_.begin(); client != clients_.end(); ++client) {
        EXPECT_TRUE((*client)->receiveDone());
        EXPECT_FALSE((*client)->expectedEof());
        EXPECT_EQ(expected_responses, (*client)->getResponses());

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

            // Now verify the AuditTrail.
            // Create the list of expected entries.
            std::list<AuditEntry> expected_entries {
                { i+1, AuditEntry::INBOUND, "I am done" },
                { i+1, AuditEntry::OUTBOUND, "good bye" }
            };

            auto entries = listener.audit_trail_->getConnectionTrail(i+1);
            ASSERT_EQ(expected_entries, entries);

        } else {
            // These clients should have been rejected and gotten EOF'd.
            EXPECT_FALSE((*client)->receiveDone());
            EXPECT_TRUE((*client)->expectedEof());

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
