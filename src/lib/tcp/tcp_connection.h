// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <tcp/tcp_connection_acceptor.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>

#include <array>
#include <functional>
#include <string>

namespace isc {
namespace tcp {

class TcpRequest {
public:
    /// @brief Constructor.
    TcpRequest(){};

    /// @brief Returns pointer to the first byte of the input buffer.
    char* getInputBufData() {
        return (input_buf_.data());
    }

    /// @brief Returns input buffer size (i.e. capacity).
    size_t getInputBufSize() const {
        return (input_buf_.size());
    }

private:
    /// @brief Buffer for received data.
    std::array<char, 32768> input_buf_;
};

typedef boost::shared_ptr<TcpRequest> TcpRequestPtr;

typedef util::OutputBuffer TcpResponse;
typedef boost::shared_ptr<TcpResponse> TcpResponsePtr;


/// @brief Generic error reported within @ref TcpConnection class.
class TcpConnectionError : public Exception {
public:
    TcpConnectionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Forward declaration to the @ref TcpConnectionPool.
///
/// This declaration is needed because we don't include the header file
/// declaring @ref TcpConnectionPool to avoid circular inclusion.
class TcpConnectionPool;

class TcpConnection;
/// @brief Pointer to the @ref TcpConnection.
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

/// @brief Accepts and handles a single TCP connection.
class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
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

public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the connection.
    /// @param acceptor Pointer to the TCP acceptor object used to listen for
    /// new TCP connections.
    /// @param tls_context TLS context.
    /// @param connection_pool Connection pool in which this connection is
    /// stored.
    /// @param response_creator Pointer to the response creator object used to
    /// create TCP response from the TCP request received.
    /// @param callback Callback invoked when new connection is accepted.
    /// @param request_timeout Configured timeout for a TCP request.
    /// @param idle_timeout Timeout after which persistent TCP connection is
    /// closed by the server.
    TcpConnection(asiolink::IOService& io_service,
                   const TcpConnectionAcceptorPtr& acceptor,
                   const asiolink::TlsContextPtr& tls_context,
                   TcpConnectionPool& connection_pool,
                   const TcpConnectionAcceptorCallback& callback,
                   const long request_timeout,
                   const long idle_timeout);

    /// @brief Destructor.
    ///
    /// Closes current connection.
    virtual ~TcpConnection();

    /// @brief Asynchronously accepts new connection.
    ///
    /// When the connection is established successfully, the timeout timer is
    /// setup and the asynchronous handshake with client is performed.
    void asyncAccept();

    /// @brief Shutdown the socket.
    void shutdown();

    /// @brief Closes the socket.
    void close();

    /// @brief Asynchronously performs TLS handshake.
    ///
    /// When the handshake is performed successfully or skipped because TLS
    /// was not enabled, the asynchronous read from the socket is started.
    void doHandshake();

    /// @brief Starts asynchronous read from the socket.
    ///
    /// The data received over the socket are supplied to the TCP parser until
    /// the parser signals that the entire request has been received or until
    /// the parser signals an error. In the former case the server creates an
    /// TCP response using supplied response creator object.
    ///
    /// In case of error the connection is stopped.
    ///
    /// @param request Pointer to the request for which the read
    /// operation should be performed. It defaults to null pointer which
    /// indicates that this function should create new request.
    void doRead(TcpRequestPtr request = TcpRequestPtr());

protected:

    /// @brief Starts asynchronous write to the socket.
    ///
    /// The @c output_buf_ must contain the data to be sent.
    ///
    /// In case of error the connection is stopped.
    ///
    /// @param request Pointer to the request for which the write
    /// operation should be performed.
    void doWrite(TcpResponsePtr response);

    /// @brief Sends TCP response asynchronously.
    ///
    /// Internally it calls @ref TcpConnection::doWrite to send the data.
    ///
    /// @param response Pointer to the TCP response to be sent.
    /// @param request Pointer to the request.
    void asyncSendResponse(TcpResponsePtr response);

    /// @brief Local callback invoked when new connection is accepted.
    ///
    /// It invokes external (supplied via constructor) acceptor callback. If
    /// the acceptor is not opened it returns immediately. If the connection
    /// is accepted successfully the @ref TcpConnection::doRead or
    /// @ref TcpConnection::doHandshake is called.
    ///
    /// @param ec Error code.
    void acceptorCallback(const boost::system::error_code& ec);

    /// @brief Local callback invoked when TLS handshake is performed.
    ///
    /// If the handshake is performed successfully the @ref
    /// TcpConnection::doRead is called.
    ///
    /// @param ec Error code.
    void handshakeCallback(const boost::system::error_code& ec);

    /// @brief Callback invoked when new data is received over the socket.
    ///
    /// This callback supplies the data to the TCP parser and continues
    /// parsing. When the parser signals end of the TCP request the callback
    /// prepares a response and starts asynchronous send over the socket.
    ///
    /// @param request Pointer to the request for which the callback
    /// is invoked.
    /// @param ec Error code.
    /// @param length Length of the received data.
    void socketReadCallback(TcpRequestPtr request,
                            boost::system::error_code ec,
                            size_t length);

    /// @brief Callback invoked when data is sent over the socket.
    ///
    /// @param request Pointer to the request for which the callback
    /// is invoked.
    /// @param ec Error code.
    /// @param length Length of the data sent.
    virtual void socketWriteCallback(TcpResponsePtr request,
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

#if 0
    /// @brief Reset timer for detecting request timeouts.
    //
    /// @param request Pointer to the request to be guarded by the timeout.
    void setupRequestTimer(TcpRequestPtr request = TcpRequestPtr());
#endif

    /// @brief Reset timer for detecting idle timeout in persistent connections.
    void setupIdleTimer();

#if 0
    /// @brief Callback invoked when the TCP Request Timeout occurs.
    ///
    /// This callback creates TCP response with Request Timeout error code
    /// and sends it to the client.
    ///
    /// @param request Pointer to the request for which timeout occurs.
    void requestTimeoutCallback(TcpRequestPtr request);
#endif

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

    /// @brief Timeout after which the persistent TCP connection is shut
    /// down by the server.
    long idle_timeout_;

    /// @brief TCP socket used by this connection.
    std::unique_ptr<asiolink::TCPSocket<SocketCallback> > tcp_socket_;

    /// @brief TLS socket used by this connection.
    std::unique_ptr<asiolink::TLSSocket<SocketCallback> > tls_socket_;

    /// @brief Pointer to the TCP acceptor used to accept new connections.
    TcpConnectionAcceptorPtr acceptor_;

    /// @brief Connection pool holding this connection.
    TcpConnectionPool& connection_pool_;

    /// @brief External TCP acceptor callback.
    TcpConnectionAcceptorCallback acceptor_callback_;
};

} // end of namespace isc::tcp
} // end of namespace isc

#endif
