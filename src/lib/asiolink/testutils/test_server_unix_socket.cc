// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <set>
#include <sstream>

using namespace boost::asio::local;

namespace isc {
namespace asiolink {
namespace test {

/// @brief ASIO unix domain socket.
typedef stream_protocol::socket UnixSocket;

/// @brief Pointer to the ASIO unix domain socket.
typedef boost::shared_ptr<UnixSocket> UnixSocketPtr;

/// @brief Callback function invoked when response is sent from the server.
typedef std::function<void()> SentResponseCallback;

/// @brief Connection to the server over unix domain socket.
///
/// It reads the data over the socket, sends responses and closes a socket.
class Connection : public boost::enable_shared_from_this<Connection> {
public:

    /// @brief Constructor.
    ///
    /// It starts asynchronous read operation.
    ///
    /// @param unix_socket Pointer to the unix domain socket into which
    /// connection has been accepted.
    /// @param custom_response Custom response that the server should send.
    /// @param sent_response_callback Callback function to be invoked when
    /// server sends a response.
    Connection(const UnixSocketPtr& unix_socket,
               const std::string custom_response,
               SentResponseCallback sent_response_callback)
        : socket_(unix_socket), custom_response_(custom_response),
          sent_response_callback_(sent_response_callback) {
    }

    /// @brief Starts asynchronous read from the socket.
    void start() {
       socket_->async_read_some(boost::asio::buffer(&raw_buf_[0], raw_buf_.size()),
           boost::bind(&Connection::readHandler, shared_from_this(),
                       boost::asio::placeholders::error,
                       boost::asio::placeholders::bytes_transferred));
    }

    /// @brief Closes the socket.
    void stop() {
        try {
            socket_->close();

        } catch (...) {
            // ignore errors when closing the socket.
        }
    }

    /// @brief Handler invoked when data have been received over the socket.
    ///
    /// This is the handler invoked when the data have been received over the
    /// socket. If custom response has been specified, this response is sent
    /// back to the client. Otherwise, the handler echoes back the request
    /// and prepends the word "received ". Finally, it calls a custom
    /// callback function (specified in the constructor) to notify that the
    /// response has been sent over the socket.
    ///
    /// @param bytes_transferred Number of bytes received.
    void
    readHandler(const boost::system::error_code& ec,
                size_t bytes_transferred) {
        // This is most likely due to the abort.
        if (ec) {
            // An error occurred so let's close the socket.
            stop();
            return;
        }

        if (!custom_response_.empty()) {
            boost::asio::write(*socket_,
               boost::asio::buffer(custom_response_.c_str(), custom_response_.size()));

        } else {
            std::string received(&raw_buf_[0], bytes_transferred);
            std::string response("received " + received);
            boost::asio::write(*socket_,
                boost::asio::buffer(response.c_str(), response.size()));
        }

        /// @todo We're taking simplistic approach and send a response right away
        /// after receiving data over the socket. Therefore, after responding we
        /// do not schedule another read. We could extend this logic slightly to
        /// parse the received data and see when we've got enough data before we
        /// send a response. However, the current unit tests don't really require
        /// that.

        // Invoke callback function to notify that the response has been sent.
        sent_response_callback_();
    }

private:

    /// @brief Pointer to the unix domain socket.
    UnixSocketPtr socket_;

    /// @brief Custom response to be sent to the client.
    std::string custom_response_;

    /// @brief Receive buffer.
    std::array<char, 1024> raw_buf_;

    /// @brief Pointer to the callback function to be invoked when response
    /// has been sent.
    SentResponseCallback sent_response_callback_;

};

/// @brief Pointer to a Connection object.
typedef boost::shared_ptr<Connection> ConnectionPtr;

/// @brief Connection pool.
///
/// Holds all connections established with the server and gracefully
/// terminates these connections.
class ConnectionPool {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service.
    ConnectionPool(IOService& io_service)
        : io_service_(io_service), connections_(), next_socket_(),
          response_num_(0) {
    }

    /// @brief Destructor.
    ~ConnectionPool() {
        stopAll();
    }

    /// @brief Creates new unix domain socket and returns it.
    ///
    /// This convenience method creates a socket which can be used to accept
    /// new connections. If such socket already exists, it is returned.
    ///
    /// @return Pointer to the socket.
    UnixSocketPtr getSocket() {
        if (!next_socket_) {
            next_socket_.reset(new UnixSocket(io_service_.get_io_service()));
        }
        return (next_socket_);
    }

    /// @brief Starts new connection.
    ///
    /// The socket returned by the @ref ConnectionPool::getSocket is used to
    /// create new connection. Then, the @ref next_socket_ is reset, to force
    /// the @ref ConnectionPool::getSocket to generate a new socket for a
    /// next connection.
    ///
    /// @param custom_response Custom response to be sent to the client.
    void start(const std::string& custom_response) {
        ConnectionPtr conn(new Connection(next_socket_, custom_response, [this] {
            ++response_num_;
        }));
        conn->start();

        connections_.insert(conn);
        next_socket_.reset();
    }

    /// @brief Stops the given connection.
    ///
    /// @param conn Pointer to the connection to be stopped.
    void stop(const ConnectionPtr& conn) {
        conn->stop();
        connections_.erase(conn);
    }

    /// @brief Stops all connections.
    void stopAll() {
        for (auto conn = connections_.begin(); conn != connections_.end();
             ++conn) {
            (*conn)->stop();
        }
        connections_.clear();
    }

    /// @brief Returns number of responses sent so far.
    size_t getResponseNum() const {
        return (response_num_);
    }

private:

    /// @brief Reference to the IO service.
    IOService& io_service_;

    /// @brief Container holding established connections.
    std::set<ConnectionPtr> connections_;

    /// @brief Holds pointer to the generated socket.
    ///
    /// This socket will be used by the next connection.
    UnixSocketPtr next_socket_;

    /// @brief Holds the number of sent responses.
    size_t response_num_;
};


TestServerUnixSocket::TestServerUnixSocket(IOService& io_service,
                                           const std::string& socket_file_path,
                                           const std::string& custom_response)
    : io_service_(io_service),
      server_endpoint_(socket_file_path),
      server_acceptor_(io_service_.get_io_service()),
      test_timer_(io_service_),
      custom_response_(custom_response),
      connection_pool_(new ConnectionPool(io_service)),
      stopped_(false),
      running_(false) {
}

TestServerUnixSocket::~TestServerUnixSocket() {
    server_acceptor_.close();
}

void
TestServerUnixSocket::generateCustomResponse(const uint64_t response_size) {
    std::ostringstream s;
    s << "{";
    while (s.tellp() < response_size) {
        s << "\"param\": \"value\",";
    }
    s << "}";
    custom_response_ = s.str();
}

void
TestServerUnixSocket::startTimer(const long test_timeout) {
    test_timer_.setup(boost::bind(&TestServerUnixSocket::timeoutHandler, this),
                      test_timeout, IntervalTimer::ONE_SHOT);
}

void
TestServerUnixSocket::stopServer() {
    test_timer_.cancel();
    server_acceptor_.cancel();
    connection_pool_->stopAll();
}

void
TestServerUnixSocket::bindServerSocket(const bool use_thread) {
    server_acceptor_.open();
    server_acceptor_.bind(server_endpoint_);
    server_acceptor_.listen();
    accept();

    // When threads are in use, we need to post a handler which will be invoked
    // when the thread has already started and the IO service is running. The
    // main thread can move forward when it receives this signal from the handler.
    if (use_thread) {
        io_service_.post(boost::bind(&TestServerUnixSocket::signalRunning,
                                     this));
    }
}

void
TestServerUnixSocket::acceptHandler(const boost::system::error_code& ec) {
    if (ec) {
        return;
    }

    connection_pool_->start(custom_response_);
    accept();
}

void
TestServerUnixSocket::accept() {
    server_acceptor_.async_accept(*(connection_pool_->getSocket()),
        boost::bind(&TestServerUnixSocket::acceptHandler, this,
                    boost::asio::placeholders::error));
}

void
TestServerUnixSocket::signalRunning() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        running_ = true;
    }
    condvar_.notify_one();
}

void
TestServerUnixSocket::waitForRunning() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (!running_) {
        condvar_.wait(lock);
    }
}

void
TestServerUnixSocket::timeoutHandler() {
    ADD_FAILURE() << "Timeout occurred while running the test!";
    io_service_.stop();
    stopped_ = true;
}

size_t
TestServerUnixSocket::getResponseNum() const {
    return (connection_pool_->getResponseNum());
}

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc
