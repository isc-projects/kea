// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_TEST_CLIENT_H
#define TCP_TEST_CLIENT_H

#include <cc/data.h>
#include <asiolink/tcp_socket.h>
#include <asiolink/tls_socket.h>
#include <asiolink/testutils/test_tls.h>
#include <tcp/tcp_connection.h>
#include <tcp/tcp_stream_msg.h>
#include <boost/asio/read.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gtest/gtest.h>

/// @brief Entity which can connect to the TCP server endpoint with or
/// or without TLS.
class TcpTestClient : public boost::noncopyable {

private:
    /// @brief Type of the function implementing a callback invoked by the
    /// @c SocketCallback functor.
    typedef std::function<void(boost::system::error_code ec, size_t length)>
    SocketCallbackFunction;

    /// @brief Functor associated with the socket object.
    ///
    /// This functor calls a callback function specified in the constructor.
    class SocketCallback {
    public:

        /// @brief Constructor.
        ///
        /// @param socket_callback Callback to be invoked by the functor upon
        /// an event associated with the socket.
        SocketCallback(SocketCallbackFunction socket_callback)
            : callback_(socket_callback) {
        }

        /// @brief Operator called when event associated with a socket occurs.
        ///
        /// This operator returns immediately when received error code is
        /// @c boost::system::error_code is equal to
        /// @c boost::asio::error::operation_aborted, i.e. the callback is not
        /// invoked.
        ///
        /// @param ec Error code.
        /// @param length Data length.
        void operator()(boost::system::error_code ec, size_t length = 0) {
            if (ec.value() == boost::asio::error::operation_aborted) {
                return;
            }

            callback_(ec, length);
        }

    private:
        /// @brief Supplied callback.
        SocketCallbackFunction callback_;
    };

public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// start() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error or completion.
    /// @param done_callback Function cient should invoke when it has finished
    /// all its requests or failed.
    /// @param tls_context
    /// @param server_address string containing the IP address of the server.
    /// @param port port number of the server.
    explicit TcpTestClient(isc::asiolink::IOService& io_service,
                           std::function<void()> done_callback,
                           isc::asiolink::TlsContextPtr tls_context =
                                isc::asiolink::TlsContextPtr(),
                           const std::string& server_address = "127.0.0.1",
                           uint16_t port = 18123)
        : io_service_(io_service.get_io_service()),
          tls_context_(tls_context),
          tcp_socket_(), tls_socket_(),
          done_callback_(done_callback),
          server_address_(server_address), server_port_(port),
          buf_(), response_(),
          receive_done_(false), expected_eof_(false), handshake_failed_(false) {
        if (!tls_context_) {
            tcp_socket_.reset(new isc::asiolink::TCPSocket<SocketCallback>(io_service));
        } else {
            tls_socket_.reset(new isc::asiolink::TLSSocket<SocketCallback>(io_service,
                                                                           tls_context));
        }
    }

    bool useTls() {
        return (!!tls_context_);
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    virtual ~TcpTestClient() {
        close();
    }

    /// @brief Connect to the listener and initiate request processing.
    ///
    /// Upon successful connection, carry out the TLS handshake. If the handshake
    /// completes successful start sending requests.
    void start() {
        isc::asiolink::TCPEndpoint endpoint(boost::asio::ip::address::from_string(server_address_), server_port_);
        SocketCallback socket_cb(
            [this](boost::system::error_code ec, size_t /*length */) {
                receive_done_ = false;
                expected_eof_ = false;
                handshake_failed_ = false;
                if (ec) {
                    // One would expect that open wouldn't return
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
                    }
                }

            if (useTls()) {
                SocketCallback socket_cb(
                    [this](boost::system::error_code ec, size_t /*length */) {
                        if (ec) {
                            handshake_failed_ = true;
                            done_callback_();
                        } else {
                            sendNextRequest();
                        }
                });

                tls_socket_->handshake(socket_cb);
            } else {
                sendNextRequest();
            }
        });

        if (useTls()) {
            tls_socket_->open(&endpoint, socket_cb);
        } else {
            tcp_socket_->open(&endpoint, socket_cb);
        }
    }

    /// @brief Send request specified in textual format.
    ///
    /// @param request request in the textual format.
    void startRequest(const std::string& request) {
        requests_to_send_.push_back(request);
        start();
    }

    /// @brief Send request specified in textual format.
    ///
    /// @param request request in the textual format.
    void startRequests(const std::list<std::string>& requests) {
        requests_to_send_ = requests;
        start();
    }

    /// @brief Sends the next request from the list of requests to send.
    void sendNextRequest() {
        // If there are any requests left to send, send them.
        if (!requests_to_send_.empty()) {
            std::string request = requests_to_send_.front();
            requests_to_send_.pop_front();
            if (request.empty()) {
                waitForEof();
            } else {
                sendRequest(request);
            }
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
        isc::tcp::WireData wire_request;
        if (!request.empty()) {
            wire_request.push_back(static_cast<uint8_t>((size & 0xff00U) >> 8));
            wire_request.push_back(static_cast<uint8_t>(size & 0x00ffU));
            wire_request.insert(wire_request.end(), request.begin(), request.end());
        }

        sendPartialRequest(wire_request, send_length);
    }

    /// @brief Wait for a server to close the connection.
    void waitForEof() {
        stream_response_.reset(new isc::tcp::TcpStreamRequest());
        receivePartialResponse(true);
    }

    /// @brief Send part of the request.
    ///
    /// @param request part of the request to be sent.
    /// @param send_length  number of bytes to send.  If not zero, can be used
    /// to truncate the amount of data sent.
    void sendPartialRequest(isc::tcp::WireData& wire_request, size_t send_length = 0) {
        if (!send_length) {
            send_length = wire_request.size();
        } else {
            ASSERT_LE(send_length, wire_request.size())
                      << "broken test, send_length exceeds wire size";
        }

        SocketCallback socket_cb(
            [this, wire_request](boost::system::error_code ec, size_t bytes_transferred) mutable {
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
                    wire_request.erase(wire_request.begin(),
                                       (wire_request.begin() + bytes_transferred));
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

        if (useTls())  {
            tls_socket_->asyncSend(static_cast<const void *>(wire_request.data()),
                                   send_length, socket_cb);
        } else {
            tcp_socket_->asyncSend(static_cast<const void *>(wire_request.data()),
                              send_length, socket_cb);
        }
    }

    /// @brief Receive response from the server.
    void receivePartialResponse(bool expect_eof = false) {
        SocketCallback socket_cb(
            [this, expect_eof](const boost::system::error_code& ec,
                               std::size_t bytes_transferred) {
                if (!stream_response_) {
                    stream_response_.reset(new isc::tcp::TcpStreamRequest());
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
                    } else if (expect_eof) {
                        expected_eof_ = true;
                        done_callback_();
                        return;
                    } else {
                        // Error occurred, bail...
                        ADD_FAILURE() << "client: " << this
                                      << " error occurred while receiving TCP"
                                      << " response from the server: " << ec.message();
                        done_callback_();
                        return;
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

        isc::asiolink::TCPEndpoint from;
        if (useTls())  {
            tls_socket_->asyncReceive(static_cast<void*>(buf_.data()), buf_.size(), 0,
                                      &from, socket_cb);
        } else {
            tcp_socket_->asyncReceive(static_cast<void*>(buf_.data()), buf_.size(), 0,
                                      &from, socket_cb);
        }
    }

    /// @brief Process a completed response received from the server.
    virtual void responseReceived() {
        /// Unpack wire data into a string.
        ASSERT_NO_THROW(stream_response_->unpack());
        std::string response = stream_response_->getRequestString();
        responses_received_.push_back(response);

        // Quit if server tells us "good bye".
        if (response.find("good bye", 0) != std::string::npos) {
            receive_done_ = true;
            done_callback_();
            return;
        }

        // Clear out for the next one.
        stream_response_.reset();
        sendNextRequest();
    }

    /// @brief Close connection.
    void close() {
        if (useTls())  {
            tls_socket_->close();
        } else {
            tcp_socket_->close();
        }
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

    bool handshakeFailed() {
        return(handshake_failed_);
    }

private:

    /// @brief Holds reference to the IO service.
    boost::asio::io_service& io_service_;

    /// @brief TLS context.
    isc::asiolink::TlsContextPtr tls_context_;

    /// @brief TCP socket used by this connection.
    std::unique_ptr<isc::asiolink::TCPSocket<SocketCallback> > tcp_socket_;

    /// @brief TLS socket used by this connection.
    std::unique_ptr<isc::asiolink::TLSSocket<SocketCallback> > tls_socket_;

    /// @brief Callback to invoke when the client has finished its work or
    /// failed.
    std::function<void()> done_callback_;

    /// @brief IP address of the server.
    std::string server_address_;

    /// @brief IP port of the server.
    uint16_t server_port_;

    /// @brief Buffer into which response is written.
    std::array<char, 8192> buf_;

    /// @brief Response in the textual format.
    std::string response_;

    /// @brief Set to true when the receive has completed successfully.
    bool receive_done_;

    /// @brief Set to true when the receive ended in EOF as expected.  In other
    /// words, the server closed the connection while we were reading as we
    /// expected it to do.
    bool expected_eof_;

    /// @brief Set to true if the TLS handshake failed.
    bool handshake_failed_;

    /// @brief Pointer to the server response currently being received.
    isc::tcp::TcpStreamRequestPtr stream_response_;

    /// @brief List of string requests to send.
    std::list<std::string> requests_to_send_;

    /// @brief List of string responses received.
    std::list<std::string> responses_received_;
};

/// @brief Pointer to the TcpTestClient.
typedef boost::shared_ptr<TcpTestClient> TcpTestClientPtr;

#endif
