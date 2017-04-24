// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <set>

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
class Connection {
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
               const SentResponseCallback& sent_response_callback)
        : socket_(unix_socket), custom_response_(custom_response),
          sent_response_callback_(sent_response_callback) {
       socket_->async_read_some(boost::asio::buffer(&raw_buf_[0], raw_buf_.size()),
           boost::bind(&Connection::readHandler, this, _1, _2));
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

        // Invoke callback function to notify that the response has been sent.
        sent_response_callback_();
    }

    /// @brief Closes the socket.
    void stop() {
        socket_->close();
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
                                           const long test_timeout,
                                           const std::string& custom_response)
    : io_service_(io_service),
      server_endpoint_(socket_file_path),
      server_acceptor_(io_service_.get_io_service()),
      test_timer_(io_service_),
      custom_response_(custom_response),
      connection_pool_(new ConnectionPool(io_service)) {
    test_timer_.setup(boost::bind(&TestServerUnixSocket::timeoutHandler, this),
                      test_timeout, IntervalTimer::ONE_SHOT);
}

TestServerUnixSocket::~TestServerUnixSocket() {
    connection_pool_->stopAll();
}

void
TestServerUnixSocket::bindServerSocket() {
    server_acceptor_.open();
    server_acceptor_.bind(server_endpoint_);
    server_acceptor_.listen();
    accept();
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
        boost::bind(&TestServerUnixSocket::acceptHandler, this, _1));
}

void
TestServerUnixSocket::timeoutHandler() {
    ADD_FAILURE() << "Timeout occurred while running the test!";
    io_service_.stop();
}

size_t
TestServerUnixSocket::getResponseNum() const {
    return (connection_pool_->getResponseNum());
}


} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc
