// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>
#include <array>
#include <functional>
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
        void operator()(boost::system::error_code ec, size_t length = 0);

    private:
        /// @brief Supplied callback.
        SocketCallbackFunction callback_;
    };

protected:

    class Transaction;

    /// @brief Shared pointer to the @c Transaction.
    typedef boost::shared_ptr<Transaction> TransactionPtr;

    /// @brief Represents a single exchange of the HTTP messages.
    ///
    /// In HTTP/1.1 multiple HTTP message exchanges may be conducted
    /// over the same persistent connection before the connection is
    /// closed. Since ASIO handlers for these exchanges may be sometimes
    /// executed out of order, there is a need to associate the states of
    /// the exchanges with the appropriate ASIO handlers. This object
    /// represents such state and includes: received request, request
    /// parser (being in the particular state of parsing), input buffer
    /// and the output buffer.
    ///
    /// The new @c Transaction instance is created when the connection
    /// is established and the server starts receiving the HTTP request.
    /// The shared pointer to the created transaction is passed between
    /// the asynchronous handlers. Therefore, as long as the asynchronous
    /// communication is conducted the instance of the transaction is
    /// held by the IO service which runs the handlers. The transaction
    /// instance exists as long as the asynchronous handlers for the
    /// given request/response exchange are executed. When the server
    /// responds to the client and all corresponding IO handlers are
    /// invoked the transaction is automatically destroyed.
    ///
    /// The timeout may occur anytime during the transaction. In such
    /// cases, a new transaction instance is created to send the
    /// HTTP 408 (timeout) response to the client. Creation of the
    /// new transaction for the timeout response is necessary because
    /// there may be some asynchronous handlers scheduled by the
    /// original transaction which rely on the original transaction's
    /// state. The timeout response's state is held within the new
    /// transaction spawned from the original transaction.
    class Transaction {
    public:

        /// @brief Constructor.
        ///
        /// @param response_creator Pointer to the response creator being
        /// used for generating a response from the request.
        /// @param request Pointer to the HTTP request. If the request is
        /// null, the constructor creates new request instance using the
        /// provided response creator.
        Transaction(const HttpResponseCreatorPtr& response_creator,
                    const HttpRequestPtr& request = HttpRequestPtr());

        /// @brief Creates new transaction instance.
        ///
        /// It is called when the HTTP server has just scheduled asynchronous
        /// reading of the HTTP message.
        ///
        /// @param response_creator Pointer to the response creator to be passed
        /// to the transaction's constructor.
        ///
        /// @return Pointer to the created transaction instance.
        static TransactionPtr create(const HttpResponseCreatorPtr& response_creator);

        /// @brief Creates new transaction from the current transaction.
        ///
        /// This method creates new transaction and inherits the request
        /// from the existing transaction. This is used when the timeout
        /// occurs during the messages exchange. The server creates the new
        /// transaction to handle the timeout but this new transaction must
        /// include the request instance so as HTTP version information can
        /// be inferred from it while sending the timeout response. The
        /// HTTP version information should match between the request and
        /// the response.
        ///
        /// @param response_creator Pointer to the response creator.
        /// @param transaction Existing transaction from which the request
        /// should be inherited. If the transaction is null, the new (dummy)
        /// request is created for the new transaction.
        static TransactionPtr spawn(const HttpResponseCreatorPtr& response_creator,
                                    const TransactionPtr& transaction);

        /// @brief Returns request instance associated with the transaction.
        HttpRequestPtr getRequest() const {
            return (request_);
        }

        /// @brief Returns parser instance associated with the transaction.
        HttpRequestParserPtr getParser() const {
            return (parser_);
        }

        /// @brief Returns pointer to the first byte of the input buffer.
        char* getInputBufData() {
            return (input_buf_.data());
        }

        /// @brief Returns input buffer size.
        size_t getInputBufSize() const {
            return (input_buf_.size());
        }

        /// @brief Checks if the output buffer contains some data to be
        /// sent.
        ///
        /// @return true if the output buffer contains data to be sent,
        /// false otherwise.
        bool outputDataAvail() const {
            return (!output_buf_.empty());
        }

        /// @brief Returns pointer to the first byte of the output buffer.
        const char* getOutputBufData() const {
            return (output_buf_.data());
        }

        /// @brief Returns size of the output buffer.
        size_t getOutputBufSize() const {
            return (output_buf_.size());
        }

        /// @brief Replaces output buffer contents with new contents.
        ///
        /// @param response New contents for the output buffer.
        void setOutputBuf(const std::string& response) {
            output_buf_ = response;
        }

        /// @brief Erases n bytes from the beginning of the output buffer.
        ///
        /// @param length Number of bytes to be erased.
        void consumeOutputBuf(const size_t length) {
            output_buf_.erase(0, length);
        }

    private:

        /// @brief Pointer to the request received over this connection.
        HttpRequestPtr request_;

        /// @brief Pointer to the HTTP request parser.
        HttpRequestParserPtr parser_;

        /// @brief Buffer for received data.
        std::array<char, 32768> input_buf_;

        /// @brief Buffer used for outbound data.
        std::string output_buf_;
    };

public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the connection.
    /// @param acceptor Pointer to the TCP acceptor object used to listen for
    /// new HTTP connections.
    /// @param tls_context TLS context.
    /// @param connection_pool Connection pool in which this connection is
    /// stored.
    /// @param response_creator Pointer to the response creator object used to
    /// create HTTP response from the HTTP request received.
    /// @param callback Callback invoked when new connection is accepted.
    /// @param request_timeout Configured timeout for a HTTP request.
    /// @param idle_timeout Timeout after which persistent HTTP connection is
    /// closed by the server.
    HttpConnection(asiolink::IOService& io_service,
                   const HttpAcceptorPtr& acceptor,
                   const asiolink::TlsContextPtr& tls_context,
                   HttpConnectionPool& connection_pool,
                   const HttpResponseCreatorPtr& response_creator,
                   const HttpAcceptorCallback& callback,
                   const long request_timeout,
                   const long idle_timeout);

    /// @brief Destructor.
    ///
    /// Closes current connection.
    virtual ~HttpConnection();

    /// @brief Asynchronously accepts new connection.
    ///
    /// When the connection is established successfully, the timeout timer is
    /// setup and the asynchronous handshake with client is performed.
    void asyncAccept();

    /// @brief Shutdown the socket.
    void shutdown();

    /// @brief Closes the socket.
    void close();

    /// @brief Records connection parameters into the HTTP request.
    ///
    /// @param request Pointer to the HTTP request.
    void recordParameters(const HttpRequestPtr& request) const;

    /// @brief Asynchronously performs TLS handshake.
    ///
    /// When the handshake is performed successfully or skipped because TLS
    /// was not enabled, the asynchronous read from the socket is started.
    void doHandshake();

    /// @brief Starts asynchronous read from the socket.
    ///
    /// The data received over the socket are supplied to the HTTP parser until
    /// the parser signals that the entire request has been received or until
    /// the parser signals an error. In the former case the server creates an
    /// HTTP response using supplied response creator object.
    ///
    /// In case of error the connection is stopped.
    ///
    /// @param transaction Pointer to the transaction for which the read
    /// operation should be performed. It defaults to null pointer which
    /// indicates that this function should create new transaction.
    void doRead(TransactionPtr transaction = TransactionPtr());

protected:

    /// @brief Starts asynchronous write to the socket.
    ///
    /// The @c output_buf_ must contain the data to be sent.
    ///
    /// In case of error the connection is stopped.
    ///
    /// @param transaction Pointer to the transaction for which the write
    /// operation should be performed.
    void doWrite(TransactionPtr transaction);

    /// @brief Sends HTTP response asynchronously.
    ///
    /// Internally it calls @ref HttpConnection::doWrite to send the data.
    ///
    /// @param response Pointer to the HTTP response to be sent.
    /// @param transaction Pointer to the transaction.
    void asyncSendResponse(const ConstHttpResponsePtr& response,
                           TransactionPtr transaction);

    /// @brief Local callback invoked when new connection is accepted.
    ///
    /// It invokes external (supplied via constructor) acceptor callback. If
    /// the acceptor is not opened it returns immediately. If the connection
    /// is accepted successfully the @ref HttpConnection::doRead or
    /// @ref HttpConnection::doHandshake is called.
    ///
    /// @param ec Error code.
    void acceptorCallback(const boost::system::error_code& ec);

    /// @brief Local callback invoked when TLS handshake is performed.
    ///
    /// If the handshake is performed successfully the @ref
    /// HttpConnection::doRead is called.
    ///
    /// @param ec Error code.
    void handshakeCallback(const boost::system::error_code& ec);

    /// @brief Callback invoked when new data is received over the socket.
    ///
    /// This callback supplies the data to the HTTP parser and continues
    /// parsing. When the parser signals end of the HTTP request the callback
    /// prepares a response and starts asynchronous send over the socket.
    ///
    /// @param transaction Pointer to the transaction for which the callback
    /// is invoked.
    /// @param ec Error code.
    /// @param length Length of the received data.
    void socketReadCallback(TransactionPtr transaction,
                            boost::system::error_code ec,
                            size_t length);

    /// @brief Callback invoked when data is sent over the socket.
    ///
    /// @param transaction Pointer to the transaction for which the callback
    /// is invoked.
    /// @param ec Error code.
    /// @param length Length of the data sent.
    virtual void socketWriteCallback(TransactionPtr transaction,
                                     boost::system::error_code ec,
                                     size_t length);

    /// @brief Callback invoked when TLS shutdown is performed.
    ///
    /// The TLS socket is unconditionally closed but the callback is called
    /// only when the peer has answered so the connection should be
    /// explicitly closed in all cases, i.e. do not rely on this handler.
    ///
    /// @param ec Error code (ignored).
    void shutdownCallback(const boost::system::error_code& ec);

    /// @brief Reset timer for detecting request timeouts.
    ///
    /// @param transaction Pointer to the transaction to be guarded by the timeout.
    void setupRequestTimer(TransactionPtr transaction = TransactionPtr());

    /// @brief Reset timer for detecting idle timeout in persistent connections.
    void setupIdleTimer();

    /// @brief Callback invoked when the HTTP Request Timeout occurs.
    ///
    /// This callback creates HTTP response with Request Timeout error code
    /// and sends it to the client.
    ///
    /// @param transaction Pointer to the transaction for which timeout occurs.
    void requestTimeoutCallback(TransactionPtr transaction);

    void idleTimeoutCallback();

    /// @brief Shuts down current connection.
    ///
    /// Copied from the next method @ref stopThisConnection
    void shutdownConnection();

    /// @brief Stops current connection.
    void stopThisConnection();

    /// @brief returns remote address in textual form
    std::string getRemoteEndpointAddressAsText() const;

    /// @brief Timer used to detect Request Timeout.
    asiolink::IntervalTimer request_timer_;

    /// @brief Configured Request Timeout in milliseconds.
    long request_timeout_;

    /// @brief TLS context.
    asiolink::TlsContextPtr tls_context_;

    /// @brief Timeout after which the persistent HTTP connection is shut
    /// down by the server.
    long idle_timeout_;

    /// @brief TCP socket used by this connection.
    std::unique_ptr<asiolink::TCPSocket<SocketCallback> > tcp_socket_;

    /// @brief TLS socket used by this connection.
    std::unique_ptr<asiolink::TLSSocket<SocketCallback> > tls_socket_;

    /// @brief Pointer to the TCP acceptor used to accept new connections.
    HttpAcceptorPtr acceptor_;

    /// @brief Connection pool holding this connection.
    HttpConnectionPool& connection_pool_;

    /// @brief Pointer to the @ref HttpResponseCreator object used to create
    /// HTTP responses.
    HttpResponseCreatorPtr response_creator_;

    /// @brief External TCP acceptor callback.
    HttpAcceptorCallback acceptor_callback_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
