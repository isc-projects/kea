// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_TEST_CLIENT_H
#define TCP_TEST_CLIENT_H

#include <cc/data.h>
#include <tcp/tcp_connection.h>
#include <boost/asio/read.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gtest/gtest.h>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::tcp;

/// @brief Entity which can connect to the TCP server endpoint.
class TcpTestClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error or completion.
    /// @param server_address string containing the IP address of the server.
    /// @param port port number of the server.
    explicit TcpTestClient(IOService& io_service,
                           std::function<void()> done_callback,
                           const std::string& server_address = "127.0.0.1",
                           uint16_t port = 18123)
        : io_service_(io_service.get_io_service()), socket_(io_service_), buf_(),
         response_(), done_callback_(done_callback), server_address_(server_address),
         server_port_(port), receive_done_(false), expected_eof_(true) {
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    ~TcpTestClient() {
        close();
    }

    /// @brief Connect to the listener.
    ///
    /// @param request request string to send.
    void connect() {
        tcp::endpoint endpoint(address::from_string(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this](const boost::system::error_code& ec) {
            receive_done_ = false;
            expected_eof_ = false;
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
                    done_callback_();
                    return;
                }
            }
        });
    }

    /// @brief Send request specified in textual format.
    ///
    /// @param request request in the textual format.
    void startRequest(const std::string& request) {
        tcp::endpoint endpoint(address::from_string(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this, request](const boost::system::error_code& ec) {
            receive_done_ = false;
            expected_eof_ = false;
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
                    done_callback_();
                    return;
                }
            }

            if (request.empty()) {
                waitForEof();
            } else {
                sendRequest(request);
            }
        });
    }

    /// @brief Send request specified in textual format.
    ///
    /// @param request request in the textual format.
    void startRequests(const std::list<std::string>& requests) {
        requests_to_send_ = requests;

        tcp::endpoint endpoint(address::from_string(server_address_), server_port_);
        socket_.async_connect(endpoint,
        [this](const boost::system::error_code& ec) {
            receive_done_ = false;
            expected_eof_ = false;
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
                    done_callback_();
                    return;
                }
            }

            sendNextRequest();
        });
    }

    /// @brief Sends the next request from the list of requests to send.
    void sendNextRequest() {
        // If there are any requests left to send, send them.
        if (!requests_to_send_.empty()) {
            std::string request = requests_to_send_.front();
            requests_to_send_.pop_front();
            sendRequest(request);
        }
    }

    /// @brief Send a stream request.
    ///
    /// @param request request data to send textual format.
    /// @param send_length  number of bytes to send.  If not zero, can be used
    /// to truncate the amount of data sent.
    void sendRequest(const std::string& request, const size_t send_length = 0) {
        // Prepend the length of the request.
        uint16_t size = static_cast<uint16_t>(request.size());
        WireData wire_request;
        if (!request.empty()) {
            wire_request.push_back(static_cast<uint8_t>((size & 0xff00U) >> 8));
            wire_request.push_back(static_cast<uint8_t>(size & 0x00ffU));
            wire_request.insert(wire_request.end(), request.begin(), request.end());
        }

        sendPartialRequest(wire_request, send_length);
    }

    /// @brief Wait for a server to close the connection.
    void waitForEof() {
        stream_response_.reset(new TcpStreamRequest());
        receivePartialResponse(true);
    }

    /// @brief Send part of the HTTP request.
    ///
    /// @param request part of the request to be sent.
    /// @param send_length  number of bytes to send.  If not zero, can be used
    /// to truncate the amount of data sent.
    void sendPartialRequest(WireData& wire_request, size_t send_length = 0) {
        if (!send_length) {
            send_length = wire_request.size();
        } else {
            ASSERT_LE(send_length, wire_request.size())
                      << "broken test, send_length exceeds wire size";
        }

        socket_.async_send(boost::asio::buffer(wire_request.data(), send_length),
                           [this, wire_request](const boost::system::error_code& ec,
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
                    done_callback_();
                    return;
                }
            }

            // Remove the part of the request which has been sent.
            if (bytes_transferred > 0 && (wire_request.size() <= bytes_transferred)) {
                wire_request.erase(wire_request.begin(), wire_request.begin() + bytes_transferred);
            }

            // Continue sending request data if there are still some data to be
            // sent.
            if (!wire_request.empty()) {
                sendPartialRequest(wire_request);
            } else {
                // Request has been sent. Start receiving response.
                receivePartialResponse();
            }
       });
    }

    /// @brief Receive response from the server.
    void receivePartialResponse(bool expect_eof = false) {
        socket_.async_read_some(boost::asio::buffer(buf_.data(), buf_.size()),
                                [this, expect_eof](const boost::system::error_code& ec,
                                       std::size_t bytes_transferred) {
            if (!stream_response_) {
                stream_response_.reset(new TcpStreamRequest());
            }

            if (ec) {
                // IO service stopped so simply return.
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;
                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again, make sure that there is no garbage
                    // in the bytes_transferred.
                    bytes_transferred = 0;
                } else if (ec.value() == boost::asio::error::eof && expect_eof)  {
                    expected_eof_ = true;
                    done_callback_();
                } else {
                    // Error occurred, bail...
                    ADD_FAILURE() << "error occurred while receiving TCP"
                        " response from the server: " << ec.message();
                    done_callback_();
                }
            }

            // Post received data to the current response.
            if (bytes_transferred > 0) {
                stream_response_->postBuffer(buf_.data(), bytes_transferred);
            }

            if (stream_response_->needData()) {
                // Response is incomplete, keep reading.
                receivePartialResponse();
            } else {
                // Response is complete, process it.
                responseReceived();
            }
        });
    }

    /// @brief Process a completed response received from the server.
    void responseReceived() {
        /// Unpack wire data into a string.
        ASSERT_NO_THROW(stream_response_->unpack());
        std::string response = stream_response_->getRequest();
        responses_received_.push_back(response);

        // Quit if server tells us "good bye".
        if (response.find("good bye", 0) != std::string::npos) {
            receive_done_ = true;
            done_callback_();
        }

        // Clear out for the next one.
        stream_response_.reset();
        sendNextRequest();
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

    /// @brief Returns true if the receive completed without error.
    ///
    /// @return True if the receive completed successfully, false
    /// otherwise.
    bool receiveDone() {
        return (receive_done_);
    }

    /// @brief Returns true if the receive ended with expected EOF
    ///
    /// @return True if the receive ended with EOF, false otherwise
    bool expectedEof() {
        return (expected_eof_);
    }

    /// @brief Returns the list of received responses.
    ///
    /// @return list of string responses.
    const std::list<std::string>& getResponses() {
        return (responses_received_);
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

    /// @brief Callback to invoke when the client has finished its work or
    /// failed.
    std::function<void()> done_callback_;

    /// @brief IP address of the server.
    std::string server_address_;

    /// @brief IP port of the server.
    uint16_t server_port_;

    /// @brief Set to true when the receive has completed successfully.
    bool receive_done_;

    /// @brief Set to true when the receive ended in EOF as expected.  In other
    /// words, the server closed the connection while we were reading as we
    /// expected it to do.
    bool expected_eof_;

    /// @brief Pointer to the server response currently being received.
    TcpStreamRequestPtr stream_response_;

    /// @brief List of string requests to send.
    std::list<std::string> requests_to_send_;

    /// @brief List of string responses received.
    std::list<std::string> responses_received_;
};

/// @brief Pointer to the TcpTestClient.
typedef boost::shared_ptr<TcpTestClient> TcpTestClientPtr;

#endif
