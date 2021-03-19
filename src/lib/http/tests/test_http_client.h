// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_HTTP_CLIENT_H
#define TEST_HTTP_CLIENT_H

#include <cc/data.h>
#include <http/client.h>
#include <http/http_types.h>

#include <boost/asio/read.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gtest/gtest.h>

using namespace boost::asio::ip;
using namespace isc::asiolink;

/// @brief Entity which can connect to the HTTP server endpoint.
class TestHttpClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error or completion.
    /// @param server_address string containing the IP address of the server.
    /// @param port port number of the server.
    explicit TestHttpClient(IOService& io_service,
                            const std::string& server_address = "127.0.0.1",
                            uint16_t port = 18123)
        : io_service_(io_service.get_io_service()), socket_(io_service_),
          buf_(), response_(), server_address_(server_address),
          server_port_(port), receive_done_(false) {
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    ~TestHttpClient() {
        close();
    }

    /// @brief Send HTTP request specified in textual format.
    ///
    /// @param request HTTP request in the textual format.
    void startRequest(const std::string& request) {
        tcp::endpoint endpoint(address::from_string(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this, request](const boost::system::error_code& ec) {
            receive_done_ = false;
            if (ec) {
                // One would expect that async_connect wouldn't return
                // EINPROGRESS error code, but simply wait for the connection
                // to get established before the handler is invoked. It turns out,
                // however, that on some OSes the connect handler may receive this
                // error code which doesn't necessarily indicate a problem.
                // Making an attempt to write and read from this socket will
                // typically succeed. So, we ignore this error.
                if (ec.value() != boost::asio::error::in_progress) {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    io_service_.stop();
                    return;
                }
            }
            sendRequest(request);
        });
    }

    /// @brief Send HTTP request.
    ///
    /// @param request HTTP request in the textual format.
    void sendRequest(const std::string& request) {
        sendPartialRequest(request);
    }

    /// @brief Send part of the HTTP request.
    ///
    /// @param request part of the HTTP request to be sent.
    void sendPartialRequest(std::string request) {
        socket_.async_send(boost::asio::buffer(request.data(), request.size()),
                           [this, request](const boost::system::error_code& ec,
                                           std::size_t bytes_transferred) mutable {
            if (ec) {
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;

                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again make sure there is no garbage in the
                    // bytes_transferred.
                    bytes_transferred = 0;

                } else {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    io_service_.stop();
                    return;
                }
            }

            // Remove the part of the request which has been sent.
            if (bytes_transferred > 0 && (request.size() <= bytes_transferred)) {
                request.erase(0, bytes_transferred);
            }

            // Continue sending request data if there are still some data to be
            // sent.
            if (!request.empty()) {
                sendPartialRequest(request);

            } else {
                // Request has been sent. Start receiving response.
                response_.clear();
                receivePartialResponse();
            }
       });
    }

    /// @brief Receive response from the server.
    void receivePartialResponse() {
        socket_.async_read_some(boost::asio::buffer(buf_.data(), buf_.size()),
                                [this](const boost::system::error_code& ec,
                                       std::size_t bytes_transferred) {
            if (ec) {
                // IO service stopped so simply return.
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;

                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again, make sure that there is no garbage
                    // in the bytes_transferred.
                    bytes_transferred = 0;

                } else {
                    // Error occurred, bail...
                    ADD_FAILURE() << "error occurred while receiving HTTP"
                        " response from the server: " << ec.message();
                    io_service_.stop();
                }
            }

            if (bytes_transferred > 0) {
                response_.insert(response_.end(), buf_.data(),
                                 buf_.data() + bytes_transferred);
            }

            // Two consecutive new lines end the part of the response we're
            // expecting.
            if (response_.find("\r\n\r\n", 0) != std::string::npos) {
                receive_done_ = true;
                io_service_.stop();
            } else {
                receivePartialResponse();
            }
        });
    }

    /// @brief Checks if the TCP connection is still open.
    ///
    /// Tests the TCP connection by trying to read from the socket.
    /// Unfortunately expected failure depends on a race between the read
    /// and the other side close so to check if the connection is closed
    /// please use @c isConnectionClosed instead.
    ///
    /// @return true if the TCP connection is open.
    bool isConnectionAlive() {
        // Remember the current non blocking setting.
        const bool non_blocking_orig = socket_.non_blocking();
        // Set the socket to non blocking mode. We're going to test if the socket
        // returns would_block status on the attempt to read from it.
        socket_.non_blocking(true);

        // We need to provide a buffer for a call to read.
        char data[2];
        boost::system::error_code ec;
        boost::asio::read(socket_, boost::asio::buffer(data, sizeof(data)), ec);

        // Revert the original non_blocking flag on the socket.
        socket_.non_blocking(non_blocking_orig);

        // If the connection is alive we'd typically get would_block status code.
        // If there are any data that haven't been read we may also get success
        // status. We're guessing that try_again may also be returned by some
        // implementations in some situations. Any other error code indicates a
        // problem with the connection so we assume that the connection has been
        // closed.
        return (!ec || (ec.value() == boost::asio::error::try_again) ||
                (ec.value() == boost::asio::error::would_block));
    }

    /// @brief Checks if the TCP connection is already closed.
    ///
    /// Tests the TCP connection by trying to read from the socket.
    /// The read can block so this must be used to check if a connection
    /// is alive so to check if the connection is alive please always
    /// use @c isConnectionAlive.
    ///
    /// @return true if the TCP connection is closed.
    bool isConnectionClosed() {
        // Remember the current non blocking setting.
        const bool non_blocking_orig = socket_.non_blocking();
        // Set the socket to blocking mode. We're going to test if the socket
        // returns eof status on the attempt to read from it.
        socket_.non_blocking(false);

        // We need to provide a buffer for a call to read.
        char data[2];
        boost::system::error_code ec;
        boost::asio::read(socket_, boost::asio::buffer(data, sizeof(data)), ec);

        // Revert the original non_blocking flag on the socket.
        socket_.non_blocking(non_blocking_orig);

        // If the connection is closed we'd typically get eof status code.
        return (ec.value() == boost::asio::error::eof);
    }

    /// @brief Close connection.
    void close() {
        socket_.close();
    }

    /// @brief Returns the HTTP response string.
    ///
    /// @return string containing the response.
    std::string getResponse() const {
        return (response_);
    }

    /// @brief Returns true if the receive completed without error.
    ///
    /// @return True if the receive completed successfully, false
    /// otherwise.
    bool receiveDone() {
        return (receive_done_);
    }

private:

    /// @brief Holds reference to the IO service.
    boost::asio::io_service& io_service_;

    /// @brief A socket used for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// @brief Buffer into which response is written.
    std::array<char, 8192> buf_;

    /// @brief Response in the textual format.
    std::string response_;

    /// @brief IP address of the server.
    std::string server_address_;

    /// @brief IP port of the server.
    uint16_t server_port_;

    /// @brief Set to true when the receive has completed successfully.
    bool receive_done_;
};

/// @brief Pointer to the TestHttpClient.
typedef boost::shared_ptr<TestHttpClient> TestHttpClientPtr;

#endif
