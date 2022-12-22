// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <tcp/tcp_connection_acceptor.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>

#include <array>
#include <functional>
#include <string>
#include <iostream>

#include <mutex>

namespace isc {
namespace tcp {

/// @brief Defines a data structure for storing raw bytes of data on the wire.
typedef std::vector<uint8_t> WireData;
typedef boost::shared_ptr<WireData> WireDataPtr;

/// @brief Base class for TCP messages.
class TcpMessage {
public:
    /// @brief Destructor
    virtual ~TcpMessage(){
    };

    /// @brief Returns pointer to the first byte of the wire data.
    /// @throw InvalidOperation if wire data is empty (i.e. getWireDataSize() == 0).
    /// @return Constant raw pointer to the data.
    const uint8_t* getWireData() const {
        if (wire_data_.empty()) {
            isc_throw(InvalidOperation, "TcpMessage::getWireData() - cannot access empty wire data");
        }

        return (wire_data_.data());
    }

    /// @brief Returns current size of the wire data.
    size_t getWireDataSize() const {
        return (wire_data_.size());
    }

protected:
    /// @brief Buffer used for data in wire format data.
    WireData wire_data_;
};

/// @brief Abstract class used to receive an inbound message.
class TcpRequest : public TcpMessage {
public:
    /// @brief Destructor
    virtual ~TcpRequest(){};

    /// @brief Adds data to an incomplete request
    ///
    /// @param buf A pointer to the buffer holding the data.
    /// @param nbytes Size of the data within the buffer.
    /// @return number of bytes posted (consumed)
    virtual size_t postBuffer(const void* buf, const size_t nbytes) = 0;

    /// @brief Returns true if the request is incomplete.
    ///
    /// @return true if the request is incomplete.
    virtual bool needData() const = 0;

    /// @brief Returns request contents formatted for log output
    ///
    /// @param limit Maximum length of the buffer to be output. If the limit is 0,
    /// the length of the output is unlimited.
    /// @return Textual representation of the input buffer.
    virtual std::string logFormatRequest(const size_t limit = 0) const = 0;

    /// @brief Unpacks wire data once the message has been completely received.
    virtual void unpack() = 0;

private:

    /// @brief Exception safe wrapper around logForamteRequest
    ///
    /// @param limit Maximum length of the buffer to be output. If the limit is 0,
    /// the length of the output is unlimited.
    /// @return Textual representation of the input buffer.
    std::string logFormatRequestSafe(const size_t limit = 0) const;
};

/// @brief Defines a smart pointer to a TcpRequest.
typedef boost::shared_ptr<TcpRequest> TcpRequestPtr;

/// @brief Abstract class used to create and send an outbound response.
class TcpResponse : public TcpMessage {
public:
    /// @brief Constructor
    TcpResponse()
    : send_in_progress_(false) {};

    /// @brief Destructor
    virtual ~TcpResponse() {};

    /// @brief Checks if the output buffer contains some data to be
    /// sent.
    ///
    /// @return true if the output buffer contains data to be sent,
    /// false otherwise.
    bool wireDataAvail() const {
        return (!wire_data_.empty());
    }

    /// @brief Prepares the wire data content for writing.
    virtual void pack() = 0;

    /// @brief Erases n bytes from the beginning of the wire data.
    ///
    /// @param length Number of bytes to be erased.
    virtual void consumeWireData(const size_t length);

    bool sendInProgress() {
        return (send_in_progress_);
    }

private:
    /// @brief Returns true once wire data consumption has begun.
    bool send_in_progress_;
};

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

/// @brief Type of the callback for filtering new connections by ip address.
typedef std::function<bool(const boost::asio::ip::tcp::endpoint&)> TcpConnectionFilterCallback;

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
    /// @param acceptor_callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked prior to handshake which can be
    /// used to qualify and reject connections
    /// @param idle_timeout Timeout after which a TCP connection is
    /// closed by the server.
    /// @param read_max maximum size of a single socket read.  Defaults to 32K.
    TcpConnection(asiolink::IOService& io_service,
                  const TcpConnectionAcceptorPtr& acceptor,
                  const asiolink::TlsContextPtr& tls_context,
                  TcpConnectionPool& connection_pool,
                  const TcpConnectionAcceptorCallback& acceptor_callback,
                  const TcpConnectionFilterCallback& connection_filter,
                  const long idle_timeout,
                  const size_t read_max = 32768);

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
    virtual void shutdown();

    /// @brief Closes the socket.
    virtual void close();

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

    /// @brief Appends newly received raw data to the given request.
    ///
    /// The input data is passed into the current request's postBuffer method.
    /// If the request is still incomplete, we return it and wait for more
    /// data to post.  Otherwise, the request is complete and it is passed into
    /// @ref TcpConnection::requestReceived() to be processed.  Upon return from
    /// that, a new request is created and returned to be used for the next
    /// read cycle.
    ///
    /// @param request request to which data should be posted.
    /// @param input_data raw data to post.
    ///
    /// @return Pointer to the request to use for the next read.
    TcpRequestPtr postData(TcpRequestPtr request, WireData& input_data);

    /// @brief Processes a request once it has been completely received.
    ///
    /// This function is called by @c postData() if the post results
    /// in a completion (i.e. request's needData() returns false).
    virtual void requestReceived(TcpRequestPtr request) = 0;

    /// @brief Creates a new, empty request.
    ///
    /// This function is called by @c postData(), following the completion
    /// of the current request, to create a new request for accepting the
    /// next data read.
    ///
    /// @return Pointer to the new request.
    virtual TcpRequestPtr createRequest() = 0;

    /// @brief Fetches the maximum number of bytes read during single socket
    /// read.
    /// @return Maximum number of bytes to read.
    size_t getReadMax() const {
        return (read_max_);
    }

    /// @brief Sets the maximum number of bytes read during single socket read.
    ///
    /// @param read_max maximum number of bytes to read.
    /// @throw BadValue if the parameter is not greater than zero.
    void setReadMax(const size_t read_max);

    /// @brief Determines behavior after a response has been sent.
    ///
    /// @param response Pointer to the response sent.
    /// @return True if the idle timer should be started.
    virtual bool responseSent(TcpResponsePtr response) = 0;

    /// @brief Returns an empty end point.
    ///
    /// @return an uninitialized endpoint.
    static const boost::asio::ip::tcp::endpoint& NO_ENDPOINT() {
        static boost::asio::ip::tcp::endpoint endpoint;
        return (endpoint);
    }

    /// @brief Fetches the remote endpoint for the connection's socket.
    ///
    /// @return A reference to the endpoint if the socket is open, otherwise
    /// NO_ENDPOINT.
    const boost::asio::ip::tcp::endpoint getRemoteEndpoint() const {
	return (remote_endpoint_);
    }

protected:

    /// @brief Starts asynchronous write to the socket.
    ///
    /// The @c output_buf_ must contain the data to be sent.
    ///
    /// In case of error the connection is stopped.
    ///
    /// @param response Pointer to the response to write
    /// operation should be performed.
    void doWrite(TcpResponsePtr response);

    /// @brief Sends TCP response asynchronously.
    ///
    /// Internally it calls @ref TcpConnection::doWrite to send the data.
    ///
    /// @param response Pointer to the TCP response to be sent.
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

    /// @brief Reset timer for detecting idle timeout in connections.
    void setupIdleTimer();

    /// @brief Callback invoked when the client has been idle.
    void idleTimeoutCallback();

    /// @brief Shuts down current connection.
    ///
    /// Copied from the next method @ref stopThisConnection
    virtual void shutdownConnection();

    /// @brief Stops current connection.
    virtual void stopThisConnection();

    /// @brief returns remote address in textual form
    std::string getRemoteEndpointAddressAsText() const;

    /// @brief Returns pointer to the first byte of the input buffer.
    ///
    /// @throw InvalidOperation if called when the buffer is empty.
    unsigned char* getInputBufData() {
        if (input_buf_.empty()) {
            isc_throw(InvalidOperation, "TcpConnection::getInputBufData() - cannot access empty buffer");
       }

        return (input_buf_.data());
    }

    /// @brief Returns input buffer size.
    size_t getInputBufSize() const {
        return (input_buf_.size());
    }

    /// @brief TLS context.
    asiolink::TlsContextPtr tls_context_;

    /// @brief Timeout after which the a TCP connection is shut
    /// down by the server.
    long idle_timeout_;

    /// @brief Timer used to detect idle Timeout.
    asiolink::IntervalTimer idle_timer_;

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

    /// @brief External callback for filtering connections by IP address.
    TcpConnectionFilterCallback connection_filter_;

    /// @brief Maximum bytes to read in a single socket read.
    size_t read_max_;

    /// @brief Buffer for a single socket read.
    WireData input_buf_;

    /// @brief Remote endpoint.
    boost::asio::ip::tcp::endpoint remote_endpoint_;
};

/// @brief Pointer to the @ref TcpConnection.
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

} // end of namespace isc::tcp
} // end of namespace isc

#endif
