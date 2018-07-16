// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <http/http_acceptor.h>
#include <http/request_parser.h>
#include <http/response_creator_factory.h>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>
#include <array>
#include <string>

namespace isc {
namespace http {

/// @brief Generic error reported within @ref HttpConnection class.
class HttpConnectionError : public Exception {
public:
    HttpConnectionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Forward declaration to the @ref HttpConnectionPool.
///
/// This declaration is needed because we don't include the header file
/// declaring @ref HttpConnectionPool to avoid circular inclusion.
class HttpConnectionPool;

class HttpConnection;
/// @brief Pointer to the @ref HttpConnection.
typedef boost::shared_ptr<HttpConnection> HttpConnectionPtr;

/// @brief Accepts and handles a single HTTP connection.
class HttpConnection : public boost::enable_shared_from_this<HttpConnection> {
private:

    /// @brief Type of the function implementing a callback invoked by the
    /// @c SocketCallback functor.
    typedef boost::function<void(boost::system::error_code ec, size_t length)>
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
        void operator()(boost::system::error_code ec, size_t length = 0);

    private:
        /// @brief Supplied callback.
        SocketCallbackFunction callback_;
    };


public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the connection.
    /// @param acceptor Reference to the TCP acceptor object used to listen for
    /// new HTTP connections.
    /// @param connection_pool Connection pool in which this connection is
    /// stored.
    /// @param response_creator Pointer to the response creator object used to
    /// create HTTP response from the HTTP request received.
    /// @param callback Callback invoked when new connection is accepted.
    /// @param request_timeout Configured timeout for a HTTP request.
    /// @param idle_timeout Timeout after which persistent HTTP connection is
    /// closed by the server.
    HttpConnection(asiolink::IOService& io_service,
                   HttpAcceptor& acceptor,
                   HttpConnectionPool& connection_pool,
                   const HttpResponseCreatorPtr& response_creator,
                   const HttpAcceptorCallback& callback,
                   const long request_timeout,
                   const long idle_timeout);

    /// @brief Destructor.
    ///
    /// Closes current connection.
    ~HttpConnection();

    /// @brief Asynchronously accepts new connection.
    ///
    /// When the connection is established successfully, the timeout timer is
    /// setup and the asynchronous read from the socket is started.
    void asyncAccept();

    /// @brief Closes the socket.
    void close();

    /// @brief Starts asynchronous read from the socket.
    ///
    /// The data received over the socket are supplied to the HTTP parser until
    /// the parser signals that the entire request has been received or until
    /// the parser signals an error. In the former case the server creates an
    /// HTTP response using supplied response creator object.
    ///
    /// In case of error the connection is stopped.
    void doRead();

private:

    /// @brief Starts asynchronous write to the socket.
    ///
    /// The @c output_buf_ must contain the data to be sent.
    ///
    /// In case of error the connection is stopped.
    void doWrite();

    /// @brief Sends HTTP response asynchronously.
    ///
    /// Internally it calls @ref HttpConnection::doWrite to send the data.
    ///
    /// @param response Pointer to the HTTP response to be sent.
    void asyncSendResponse(const ConstHttpResponsePtr& response);

    /// @brief Local callback invoked when new connection is accepted.
    ///
    /// It invokes external (supplied via constructor) acceptor callback. If
    /// the acceptor is not opened it returns immediately. If the connection
    /// is accepted successfully the @ref HttpConnection::doRead is called.
    ///
    /// @param ec Error code.
    void acceptorCallback(const boost::system::error_code& ec);

    /// @brief Callback invoked when new data is received over the socket.
    ///
    /// This callback supplies the data to the HTTP parser and continues
    /// parsing. When the parser signals end of the HTTP request the callback
    /// prepares a response and starts asynchronous send over the socket.
    ///
    /// @param ec Error code.
    /// @param length Length of the received data.
    void socketReadCallback(boost::system::error_code ec,
                            size_t length);

    /// @brief Callback invoked when data is sent over the socket.
    ///
    /// @param ec Error code.
    /// @param length Length of the data sent.
    void socketWriteCallback(boost::system::error_code ec,
                             size_t length);

    /// @brief Reinitializes request processing state after sending a response.
    ///
    /// This method is only called for persistent connections, when the response
    /// to a previous command has been sent. It initializes the state machine to
    /// be able to process the next request. It also sets the persistent connection
    /// idle timer to monitor the connection timeout.
    void reinitProcessingState();

    /// @brief Reset timer for detecting request timeouts.
    void setupRequestTimer();

    /// @brief Reset timer for detecing idle timeout in persistent connections.
    void setupIdleTimer();

    /// @brief Callback invoked when the HTTP Request Timeout occurs.
    ///
    /// This callback creates HTTP response with Request Timeout error code
    /// and sends it to the client.
    void requestTimeoutCallback();

    void idleTimeoutCallback();

    /// @brief Stops current connection.
    void stopThisConnection();

    /// @brief returns remote address in textual form
    std::string getRemoteEndpointAddressAsText() const;

    /// @brief Timer used to detect Request Timeout.
    asiolink::IntervalTimer request_timer_;

    /// @brief Configured Request Timeout in milliseconds.
    long request_timeout_;

    /// @brief Timeout after which the persistent HTTP connection is closed
    /// by the server.
    long idle_timeout_;

    /// @brief Socket used by this connection.
    asiolink::TCPSocket<SocketCallback> socket_;

    /// @brief Reference to the TCP acceptor used to accept new connections.
    HttpAcceptor& acceptor_;

    /// @brief Connection pool holding this connection.
    HttpConnectionPool& connection_pool_;

    /// @brief Pointer to the @ref HttpResponseCreator object used to create
    /// HTTP responses.
    HttpResponseCreatorPtr response_creator_;

    /// @brief Pointer to the request received over this connection.
    HttpRequestPtr request_;

    /// @brief Pointer to the HTTP request parser.
    HttpRequestParserPtr parser_;

    /// @brief External TCP acceptor callback.
    HttpAcceptorCallback acceptor_callback_;

    /// @brief Buffer for received data.
    std::array<char, 32768> buf_;

    /// @brief Buffer used for outbound data.
    std::string output_buf_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
