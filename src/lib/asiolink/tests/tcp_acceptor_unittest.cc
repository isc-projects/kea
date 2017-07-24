// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/tcp_acceptor.h>
#include <asiolink/tcp_endpoint.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <list>
#include <netinet/in.h>
#include <string>

using namespace isc::asiolink;

namespace {

/// @brief Local server address used for testing.
const char SERVER_ADDRESS[] = "127.0.0.1";

/// @brief Local server port used for testing.
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout in ms.
const long TEST_TIMEOUT = 10000;

/// @brief Simple class representing TCP socket callback.
class SocketCallback {
public:

    /// @brief Implements callback for the asynchronous operation on the socket.
    ///
    /// This callback merely checks if error has occurred and reports this
    /// error. It does nothing in case of success.
    ///
    /// @param ec Error code.
    /// @param length Length of received data.
    void operator()(boost::system::error_code ec, size_t length = 0) {
        if (ec) {
            ADD_FAILURE() << "error occurred for a socket: " << ec.message();
        }
    }

};

/// @brief Entity which can connect to the TCP server endpoint and close the
/// connection.
class TCPClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error.
    explicit TCPClient(IOService& io_service)
        : io_service_(io_service.get_io_service()), socket_(io_service_) {
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    ~TCPClient() {
        close();
    }

    /// @brief Connect to the test server address and port.
    ///
    /// This method asynchronously connects to the server endpoint and uses the
    /// connectHandler as a callback function.
    void connect() {
        boost::asio::ip::tcp::endpoint
            endpoint(boost::asio::ip::address::from_string(SERVER_ADDRESS),
                     SERVER_PORT);
        socket_.async_connect(endpoint,
                              boost::bind(&TCPClient::connectHandler, this,_1));
    }

    /// @brief Callback function for connect().
    ///
    /// This function stops the IO service upon error.
    ///
    /// @param ec Error code.
    void connectHandler(const boost::system::error_code& ec) {
        if (ec) {
            // One would expect that async_connect wouldn't return EINPROGRESS
            // error code, but simply wait for the connection to get
            // established before the handler is invoked. It turns out, however,
            // that on some OSes the connect handler may receive this error code
            // which doesn't necessarily indicate a problem. Making an attempt
            // to write and read from this socket will typically succeed. So,
            // we ignore this error.
            if (ec.value() != boost::asio::error::in_progress) {
                ADD_FAILURE() << "error occurred while connecting: "
                              << ec.message();
                io_service_.stop();
            }
        }
    }

    /// @brief Close connection.
    void close() {
        socket_.close();
    }

private:

    /// @brief Holds reference to the IO service.
    boost::asio::io_service& io_service_;

    /// @brief A socket used for the connection.
    boost::asio::ip::tcp::socket socket_;

};

/// @brief Pointer to the TCPClient.
typedef boost::shared_ptr<TCPClient> TCPClientPtr;

/// @brief A signature of the function implementing callback for the
/// TCPAcceptor.
typedef boost::function<void(const boost::system::error_code&)> TCPAcceptorCallback;

/// @brief TCPAcceptor using TCPAcceptorCallback.
typedef TCPAcceptor<TCPAcceptorCallback> TestTCPAcceptor;

/// @brief Implements asynchronous TCP acceptor service.
///
/// It creates a new socket into which connection is accepted. The socket
/// is retained until class instance exists.
class Acceptor {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service.
    /// @param acceptor Reference to the TCP acceptor on which asyncAccept
    /// will be called.
    /// @param callback Callback function for the asyncAccept.
    explicit Acceptor(IOService& io_service, TestTCPAcceptor& acceptor,
                      const TCPAcceptorCallback& callback)
        : socket_(io_service), acceptor_(acceptor), callback_(callback) {
    }

    /// @brief Destructor.
    ///
    /// Closes socket.
    ~Acceptor() {
        socket_.close();
    }

    /// @brief Asynchronous accept new connection.
    void accept() {
        acceptor_.asyncAccept(socket_, callback_);
    }

    /// @brief Close connection.
    void close() {
        socket_.close();
    }

private:

    /// @brief Socket into which connection is accepted.
    TCPSocket<SocketCallback> socket_;

    /// @brief Reference to the TCPAcceptor on which asyncAccept is called.
    TestTCPAcceptor& acceptor_;

    /// @brief Instance of the callback used for asyncAccept.
    TCPAcceptorCallback callback_;

};

/// @brief Pointer to the Acceptor object.
typedef boost::shared_ptr<Acceptor> AcceptorPtr;

/// @brief Test fixture class for TCPAcceptor.
///
/// This class provides means for creating new TCP connections, i.e. simulates
/// clients connecting to the servers via TCPAcceptor. It is possible to create
/// multiple simultaneous connections, which are retained by the test fixture
/// class and closed cleanly when the test fixture is destroyed.
class TCPAcceptorTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Besides initializing class members it also sets the test timer to guard
    /// against endlessly running IO service when TCP connections are
    /// unsuccessful.
    TCPAcceptorTest()
        : io_service_(), acceptor_(io_service_),
          asio_endpoint_(boost::asio::ip::address::from_string(SERVER_ADDRESS),
                         SERVER_PORT),
          endpoint_(asio_endpoint_), test_timer_(io_service_), connections_(),
          clients_(), connections_num_(0), aborted_connections_num_(0),
          max_connections_(1) {
        test_timer_.setup(boost::bind(&TCPAcceptorTest::timeoutHandler, this),
                                      TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    virtual ~TCPAcceptorTest() {
    }

    /// @brief Specifies how many new connections are expected before the IO
    /// service is stopped.
    ///
    /// @param max_connections Connections limit.
    void setMaxConnections(const unsigned int max_connections) {
        max_connections_ = max_connections;
    }

    /// @brief Create ASIO endpoint from the provided endpoint by retaining the
    /// IP address and modifying the port.
    ///
    /// This convenience method is useful to create new endpoint from the
    /// existing endpoint to test reusing IP address for multiple acceptors.
    /// The returned endpoint has the same IP address but different port.
    ///
    /// @param endpoint Source endpoint.
    ///
    /// @return New endpoint with the port number increased by 1.
    boost::asio::ip::tcp::endpoint
    createSiblingEndpoint(const boost::asio::ip::tcp::endpoint& endpoint) const {
        boost::asio::ip::tcp::endpoint endpoint_copy(endpoint);
        endpoint_copy.port(endpoint.port() + 1);
        return (endpoint_copy);
    }

    /// @brief Opens TCP acceptor and sets 'reuse address' option.
    void acceptorOpen() {
        acceptor_.open(endpoint_);
        acceptor_.setOption(TestTCPAcceptor::ReuseAddress(true));
    }

    /// @brief Starts accepting TCP connections.
    ///
    /// This method creates new Acceptor instance and calls accept() to start
    /// accepting new connections. The instance of the Acceptor object is
    /// retained in the connections_ list.
    void accept() {
        TCPAcceptorCallback cb = boost::bind(&TCPAcceptorTest::acceptHandler,
                                             this, _1);
        AcceptorPtr conn(new Acceptor(io_service_, acceptor_, cb));
        connections_.push_back(conn);
        connections_.back()->accept();
    }

    /// @brief Connect to the endpoint.
    ///
    /// This method creates TCPClient instance and retains it in the clients_
    /// list.
    void connect() {
        TCPClientPtr client(new TCPClient(io_service_));
        clients_.push_back(client);
        clients_.back()->connect();
    }

    /// @brief Callback function for asynchronous accept calls.
    ///
    /// It stops the IO service upon error or when the number of accepted
    /// connections reaches the max_connections_ value. Otherwise it calls
    /// accept() to start accepting next connections.
    ///
    /// @param ec Error code.
    void acceptHandler(const boost::system::error_code& ec) {
        if (ec) {
            if (ec.value() != boost::asio::error::operation_aborted) {
                ADD_FAILURE() << "error occurred while accepting connection: "
                              << ec.message();
            } else {
                ++aborted_connections_num_;
            }
            io_service_.stop();
        }

        // We have reached the maximum number of connections - end the test.
        if (++connections_num_ >= max_connections_) {
            io_service_.stop();
            return;
        }

        accept();
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    void timeoutHandler() {
        ADD_FAILURE() << "Timeout occurred while running the test!";
        io_service_.stop();
    }

    /// @brief IO service.
    IOService io_service_;

    /// @brief TCPAcceptor under test.
    TestTCPAcceptor acceptor_;

    /// @brief Server endpoint.
    boost::asio::ip::tcp::endpoint asio_endpoint_;

    /// @brief asiolink server endpoint (uses asio_endpoint_).
    TCPEndpoint endpoint_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief List of connections on the server side.
    std::list<AcceptorPtr> connections_;

    /// @brief List of client connections.
    std::list<TCPClientPtr> clients_;

    /// @brief Current number of established connections.
    unsigned int connections_num_;

    /// @brief Current number of aborted connections.
    unsigned int aborted_connections_num_;

    /// @brief Connections limit.
    unsigned int max_connections_;
};

// Test TCPAcceptor::asyncAccept.
TEST_F(TCPAcceptorTest, asyncAccept) {
    // Establish up to 10 connections.
    setMaxConnections(10);

    // Initialize acceptor.
    acceptorOpen();
    acceptor_.bind(endpoint_);
    acceptor_.listen();

    // Start accepting new connections.
    accept();

    // Create 10 new TCP connections (client side).
    for (unsigned int i = 0; i < 10; ++i) {
        connect();
    }

    // Run the IO service until we have accepted 10 connections, an error
    // or test timeout occurred.
    io_service_.run();

    // Make sure that all accepted connections have been recorded.
    EXPECT_EQ(10, connections_num_);
    EXPECT_EQ(10, connections_.size());
}

// Check that it is possible to set SO_REUSEADDR flag for the TCPAcceptor.
TEST_F(TCPAcceptorTest, reuseAddress) {
    // We need at least two acceptors using common address. Let's create the
    // second endpoint which has the same address but different port.
    boost::asio::ip::tcp::endpoint asio_endpoint2(createSiblingEndpoint(asio_endpoint_));
    TCPEndpoint endpoint2(asio_endpoint2);

    // Create and open two acceptors.
    TestTCPAcceptor acceptor1(io_service_);
    TestTCPAcceptor acceptor2(io_service_);
    ASSERT_NO_THROW(acceptor1.open(endpoint_));
    ASSERT_NO_THROW(acceptor2.open(endpoint2));

    // Set SO_REUSEADDR socket option so as acceptors can bind to the
    /// same address.
    ASSERT_NO_THROW(
        acceptor1.setOption(TestTCPAcceptor::ReuseAddress(true))
    );
    ASSERT_NO_THROW(
        acceptor2.setOption(TestTCPAcceptor::ReuseAddress(true))
    );
    ASSERT_NO_THROW(acceptor1.bind(endpoint_));
    ASSERT_NO_THROW(acceptor2.bind(endpoint2));

    // Create third acceptor, but don't set the SO_REUSEADDR. It should
    // refuse to bind.
    TCPEndpoint endpoint3(createSiblingEndpoint(asio_endpoint2));
    TestTCPAcceptor acceptor3(io_service_);
    ASSERT_NO_THROW(acceptor3.open(endpoint3));
    EXPECT_THROW(acceptor3.bind(endpoint_), boost::system::system_error);
}

// Test that TCPAcceptor::getProtocol returns IPPROTO_TCP.
TEST_F(TCPAcceptorTest, getProtocol) {
    EXPECT_EQ(IPPROTO_TCP, acceptor_.getProtocol());
}

// Test that TCPAcceptor::getNative returns valid socket descriptor.
TEST_F(TCPAcceptorTest, getNative) {
    // Initially the descriptor should be invalid (negative).
    ASSERT_LT(acceptor_.getNative(), 0);
    // Now open the socket and make sure the returned descriptor is now valid.
    ASSERT_NO_THROW(acceptorOpen());
    EXPECT_GE(acceptor_.getNative(), 0);
}

// macOS 10.12.3 has a bug which causes the connections to not enter
// the TIME-WAIT state and they never get closed.
#if !defined (OS_OSX)

// Test that TCPAcceptor::close works properly.
TEST_F(TCPAcceptorTest, close) {
    // Initialize acceptor.
    acceptorOpen();
    acceptor_.bind(endpoint_);
    acceptor_.listen();

    // Start accepting new connections.
    accept();

    // Create 10 new TCP connections (client side).
    for (unsigned int i = 0; i < 10; ++i) {
        connect();
    }

    // Close the acceptor before connections are accepted.
    acceptor_.close();

    // Run the IO service.
    io_service_.run();

    // The connections should have been aborted.
    EXPECT_EQ(1, connections_num_);
    EXPECT_EQ(1, aborted_connections_num_);
    EXPECT_EQ(1, connections_.size());
}

#endif

}
