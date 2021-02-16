// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_socket.h>
#include <http/client.h>
#include <http/http_log.h>
#include <http/http_messages.h>
#include <http/response_json.h>
#include <http/response_parser.h>
#include <util/multi_threading_mgr.h>
#include <util/unlock_guard.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>

#include <atomic>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief Maximum size of the HTTP message that can be logged.
///
/// The part of the HTTP message beyond this value is truncated.
constexpr size_t MAX_LOGGED_MESSAGE_SIZE = 1024;

/// @brief TCP / TLS socket callback function type.
typedef std::function<void(boost::system::error_code ec, size_t length)>
SocketCallbackFunction;

/// @brief Socket callback class required by the TCPSocket and TLSSocket APIs.
///
/// Its function call operator ignores callbacks invoked with "operation aborted"
/// error codes. Such status codes are generated when the posted IO operations
/// are canceled.
class SocketCallback {
public:

    /// @brief Constructor.
    ///
    /// Stores pointer to a callback function provided by a caller.
    ///
    /// @param socket_callback Pointer to a callback function.
    SocketCallback(SocketCallbackFunction socket_callback)
        : callback_(socket_callback) {
    }

    /// @brief Function call operator.
    ///
    /// Invokes the callback for all error codes except "operation aborted".
    ///
    /// @param ec Error code.
    /// @param length Length of the data transmitted over the socket.
    void operator()(boost::system::error_code ec, size_t length = 0) {
        if (ec.value() == boost::asio::error::operation_aborted) {
            return;
        }
        callback_(ec, length);
    }

private:

    /// @brief Holds pointer to a supplied callback.
    SocketCallbackFunction callback_;

};

class ConnectionPool;

/// @brief Shared pointer to a connection pool.
typedef boost::shared_ptr<ConnectionPool> ConnectionPoolPtr;

/// @brief Client side HTTP connection to the server.
///
/// Each connection is established with a unique destination identified by the
/// specified URL. Multiple requests to the same destination can be sent over
/// the same connection, if the connection is persistent. If the server closes
/// the TCP connection (e.g. after sending a response), the connection can
/// be re-established (using the same @c Connection object).
///
/// If new request is created while the previous request is still in progress,
/// the new request is stored in the FIFO queue. The queued requests to the
/// particular URL are sent to the server when the current transaction ends.
///
/// The communication over the transport socket is asynchronous. The caller is
/// notified about the completion of the transaction via a callback that the
/// caller supplies when initiating the transaction.
class Connection : public boost::enable_shared_from_this<Connection> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used for the connection.
    /// @param context TLS context to be used for the connection.
    /// @param conn_pool Back pointer to the connection pool to which this
    /// connection belongs.
    /// @param url URL associated with this connection.
    explicit Connection(IOService& io_service,
                        const TlsContextPtr& context,
                        const ConnectionPoolPtr& conn_pool,
                        const Url& url);

    /// @brief Destructor.
    ~Connection();

    /// @brief Starts new asynchronous transaction (HTTP request and response).
    ///
    /// This method expects that all pointers provided as argument are non-null.
    ///
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response is stored.
    /// The caller should create a response object of the type which matches the
    /// content type expected by the caller, e.g. HttpResponseJson when JSON
    /// content type is expected to be received.
    /// @param request_timeout Request timeout in milliseconds.
    /// @param callback Pointer to the callback function to be invoked when the
    /// transaction completes.
    /// @param connect_callback Pointer to the callback function to be invoked
    /// when the client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the callback function to be invoked
    /// when the client closes the socket to the server.
    void doTransaction(const HttpRequestPtr& request,
                       const HttpResponsePtr& response,
                       const long request_timeout,
                       const HttpClient::RequestHandler& callback,
                       const HttpClient::ConnectHandler& connect_callback,
                       const HttpClient::HandshakeHandler& handshake_callback,
                       const HttpClient::CloseHandler& close_callback);

    /// @brief Closes the socket and cancels the request timer.
    void close();

    /// @brief Checks if a transaction has been initiated over this connection.
    ///
    /// @return true if transaction has been initiated, false otherwise.
    bool isTransactionOngoing() const;

    /// @brief Checks if a socket descriptor belongs to this connection.
    ///
    /// @param socket_fd socket descriptor to check
    ///
    /// @return True if the socket fd belongs to this connection.
    bool isMySocket(int socket_fd) const;

    /// @brief Checks and logs if premature transaction timeout is suspected.
    ///
    /// There are cases when the premature timeout occurs, e.g. as a result of
    /// moving system clock, during the transaction. In such case, the
    /// @c terminate function is called which resets the transaction state but
    /// the transaction handlers may be already waiting for the execution.
    /// Each such handler should call this function to check if the transaction
    /// it is participating in is still alive. If it is not, it should simply
    /// return. This method also logs such situation.
    ///
    /// @param transid identifier of the transaction for which the handler
    /// is being invoked. It is compared against the current transaction
    /// id for this connection.
    ///
    /// @return true if the premature timeout is suspected, false otherwise.
    bool checkPrematureTimeout(const uint64_t transid);

private:

    /// @brief Starts new asynchronous transaction (HTTP request and response).
    ///
    /// Should be called in a thread safe context.
    ///
    /// This method expects that all pointers provided as argument are non-null.
    ///
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response is stored.
    /// The caller should create a response object of the type which matches the
    /// content type expected by the caller, e.g. HttpResponseJson when JSON
    /// content type is expected to be received.
    /// @param request_timeout Request timeout in milliseconds.
    /// @param callback Pointer to the callback function to be invoked when the
    /// transaction completes.
    /// @param connect_callback Pointer to the callback function to be invoked
    /// when the client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the callback function to be invoked
    /// when the client closes the socket to the server.
    void doTransactionInternal(const HttpRequestPtr& request,
                               const HttpResponsePtr& response,
                               const long request_timeout,
                               const HttpClient::RequestHandler& callback,
                               const HttpClient::ConnectHandler& connect_callback,
                               const HttpClient::HandshakeHandler& handshake_callback,
                               const HttpClient::CloseHandler& close_callback);

    /// @brief Closes the socket and cancels the request timer.
    ///
    /// Should be called in a thread safe context.
    void closeInternal();

    /// @brief Checks and logs if premature transaction timeout is suspected.
    ///
    /// Should be called in a thread safe context.
    ///
    /// There are cases when the premature timeout occurs, e.g. as a result of
    /// moving system clock, during the transaction. In such case, the
    /// @c terminate function is called which resets the transaction state but
    /// the transaction handlers may be already waiting for the execution.
    /// Each such handler should call this function to check if the transaction
    /// it is participating in is still alive. If it is not, it should simply
    /// return. This method also logs such situation.
    ///
    /// @param transid identifier of the transaction for which the handler
    /// is being invoked. It is compared against the current transaction
    /// id for this connection.
    ///
    /// @return true if the premature timeout is suspected, false otherwise.
    bool checkPrematureTimeoutInternal(const uint64_t transid);

    /// @brief Resets the state of the object.
    ///
    /// Should be called in a thread safe context.
    ///
    /// In particular, it removes instances of objects provided for the previous
    /// transaction by a caller. It doesn't close the socket, though.
    void resetState();

    /// @brief Performs tasks required after receiving a response or after an
    /// error.
    ///
    /// This method triggers user's callback, resets the state of the connection
    /// and initiates next transaction if there is any transaction queued for the
    /// URL associated with this connection.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param parsing_error Message parsing error.
    void terminate(const boost::system::error_code& ec,
                   const std::string& parsing_error = "");

    /// @brief Performs tasks required after receiving a response or after an
    /// error.
    ///
    /// Should be called in a thread safe context.
    ///
    /// This method triggers user's callback, resets the state of the connection
    /// and initiates next transaction if there is any transaction queued for the
    /// URL associated with this connection.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param parsing_error Message parsing error.
    void terminateInternal(const boost::system::error_code& ec,
                           const std::string& parsing_error = "");

    /// @brief Run parser and check if more data is needed.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param length Number of bytes received.
    ///
    /// @return true if more data is needed, false otherwise.
    bool runParser(const boost::system::error_code& ec, size_t length);

    /// @brief Run parser and check if more data is needed.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param length Number of bytes received.
    ///
    /// @return true if more data is needed, false otherwise.
    bool runParserInternal(const boost::system::error_code& ec, size_t length);

    /// @brief This method schedules timer or reschedules existing timer.
    ///
    /// @param request_timeout New timer interval in milliseconds.
    void scheduleTimer(const long request_timeout);

    /// @brief Asynchronously performs the TLS handshake.
    ///
    /// @param transid Current transaction id.
    void doHandshake(const uint64_t transid);

    /// @brief Asynchronously sends data over the socket.
    ///
    /// The data sent over the socket are stored in the @c buf_.
    ///
    /// @param transid Current transaction id.
    void doSend(const uint64_t transid);

    /// @brief Asynchronously receives data over the socket.
    ///
    /// The data received over the socket are store into the @c input_buf_.
    ///
    /// @param transid Current transaction id.
    void doReceive(const uint64_t transid);

    /// @brief Local callback invoked when the connection is established.
    ///
    /// If the connection is successfully established, this callback will start
    /// to asynchronously send the request over the socket or perform the
    /// TLS handshake with the server.
    ///
    /// @param Pointer to the callback to be invoked when client connects to
    /// the server.
    /// @param transid Current transaction id.
    /// @param ec Error code being a result of the connection attempt.
    void connectCallback(HttpClient::ConnectHandler connect_callback,
                         const uint64_t transid,
                         const boost::system::error_code& ec);

    /// @brief Local callback invoked when the handshake is performed.
    ///
    /// If the handshake is successfully performed, this callback will start
    /// to asynchronously send the request over the socket.
    ///
    /// @param Pointer to the callback to be invoked when client performs
    /// the TLS handshake with the server.
    /// @param transid Current transaction id.
    /// @param ec Error code being a result of the connection attempt.
    void handshakeCallback(HttpClient::HandshakeHandler handshake_callback,
                           const uint64_t transid,
                           const boost::system::error_code& ec);

    /// @brief Local callback invoked when an attempt to send a portion of data
    /// over the socket has ended.
    ///
    /// The portion of data that has been sent is removed from the buffer. If all
    /// data from the buffer were sent, the callback will start to asynchronously
    /// receive a response from the server.
    ///
    /// @param transid Current transaction id.
    /// @param ec Error code being a result of sending the data.
    /// @param length Number of bytes sent.
    void sendCallback(const uint64_t transid, const boost::system::error_code& ec,
                      size_t length);

    /// @brief Local callback invoked when an attempt to receive a portion of data
    /// over the socket has ended.
    ///
    /// @param transid Current transaction id.
    /// @param ec Error code being a result of receiving the data.
    /// @param length Number of bytes received.
    void receiveCallback(const uint64_t transid, const boost::system::error_code& ec,
                         size_t length);

    /// @brief Local callback invoked when request timeout occurs.
    void timerCallback();

    /// @brief Local callback invoked when the connection is closed.
    ///
    /// Invokes the close callback (if one), passing in the socket's
    /// descriptor, when the connection's socket about to be closed.
    /// The callback invocation is wrapped in a try-catch to ensure
    /// exception safety.
    ///
    /// @param clear dictates whether or not the callback is discarded
    /// after invocation. Defaults to false.
    void closeCallback(const bool clear = false);

    /// @brief Pointer to the connection pool owning this connection.
    ///
    /// This is a weak pointer to avoid circular dependency between the
    /// Connection and ConnectionPool.
    boost::weak_ptr<ConnectionPool> conn_pool_;

    /// @brief URL for this connection.
    Url url_;

    /// @brief TCP socket to be used for this connection.
    std::unique_ptr<TCPSocket<SocketCallback> > tcp_socket_;

    /// @brief TLS socket to be used for this connection.
    std::unique_ptr<TLSSocket<SocketCallback> > tls_socket_;

    /// @brief Interval timer used for detecting request timeouts.
    IntervalTimer timer_;

    /// @brief Holds currently sent request.
    HttpRequestPtr current_request_;

    /// @brief Holds pointer to an object where response is to be stored.
    HttpResponsePtr current_response_;

    /// @brief Pointer to the HTTP response parser.
    HttpResponseParserPtr parser_;

    /// @brief User supplied callback.
    HttpClient::RequestHandler current_callback_;

    /// @brief Output buffer.
    std::string buf_;

    /// @brief Input buffer.
    std::array<char, 32768> input_buf_;

    /// @brief Identifier of the current transaction.
    uint64_t current_transid_;

    /// @brief User supplied handshake callback.
    HttpClient::HandshakeHandler handshake_callback_;

    /// @brief User supplied close callback.
    HttpClient::CloseHandler close_callback_;

    /// @brief Flag to indicate that a transaction is running.
    std::atomic<bool> started_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

/// @brief Shared pointer to the connection.
typedef boost::shared_ptr<Connection> ConnectionPtr;

/// @brief Connection pool for managing multiple connections.
///
/// Connection pool creates and destroys connections. It holds pointers
/// to all created connections and can verify whether the particular
/// connection is currently busy or idle. If the connection is idle, it
/// uses this connection for new requests. If the connection is busy, it
/// queues new requests until the connection becomes available.
class ConnectionPool : public boost::enable_shared_from_this<ConnectionPool> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service to be used by the
    /// connections.
    explicit ConnectionPool(IOService& io_service)
        : io_service_(io_service), conns_(), queue_(), mutex_() {
    }

    /// @brief Destructor.
    ///
    /// Closes all connections.
    ~ConnectionPool() {
        closeAll();
    }

    /// @brief Process next queued request for the given URL.
    ///
    /// @param url URL for which next queued request should be processed.
    void processNextRequest(const Url& url) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            return (processNextRequestInternal(url));
        } else {
            return (processNextRequestInternal(url));
        }
    }

    /// @brief Queue next request for sending to the server.
    ///
    /// A new transaction is started immediately, if there is no other request
    /// in progress for the given URL. Otherwise, the request is queued.
    ///
    /// @param url Destination where the request should be sent.
    /// @param context TLS context to be used for the connection.
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response should be
    /// stored.
    /// @param request_timeout Requested timeout for the transaction in
    /// milliseconds.
    /// @param request_callback Pointer to the user callback to be invoked when the
    /// transaction ends.
    /// @param connect_callback Pointer to the user callback to be invoked when the
    /// client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the user callback to be invoked when the
    /// client closes the connection to the server.
    void queueRequest(const Url& url,
                      const TlsContextPtr& context,
                      const HttpRequestPtr& request,
                      const HttpResponsePtr& response,
                      const long request_timeout,
                      const HttpClient::RequestHandler& request_callback,
                      const HttpClient::ConnectHandler& connect_callback,
                      const HttpClient::HandshakeHandler& handshake_callback,
                      const HttpClient::CloseHandler& close_callback) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            return (queueRequestInternal(url, context, request, response,
                                         request_timeout, request_callback,
                                         connect_callback, handshake_callback,
                                         close_callback));
        } else {
            return (queueRequestInternal(url, context, request, response,
                                         request_timeout, request_callback,
                                         connect_callback, handshake_callback,
                                         close_callback));
        }
    }

    /// @brief Closes connection and removes associated information from the
    /// connection pool.
    ///
    /// @param url URL for which connection should be closed.
    void closeConnection(const Url& url) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            closeConnectionInternal(url);
        } else {
            closeConnectionInternal(url);
        }
    }

    /// @brief Closes all connections and removes associated information from
    /// the connection pool.
    void closeAll() {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            closeAllInternal();
        } else {
            closeAllInternal();
        }
    }

    /// @brief Closes a connection if it has an out-of-band socket event
    ///
    /// If the pool contains a connection using the given socket and that
    /// connection is currently in a transaction the method returns as this
    /// indicates a normal ready event.  If the connection is not in an
    /// ongoing transaction, then the connection is closed.
    ///
    /// This is method is intended to be used to detect and clean up then
    /// sockets that are marked ready outside of transactions. The most common
    /// case is the other end of the socket being closed.
    ///
    /// @param socket_fd socket descriptor to check
    void closeIfOutOfBand(int socket_fd) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            closeIfOutOfBandInternal(socket_fd);
        } else {
            closeIfOutOfBandInternal(socket_fd);
        }
    }

private:

    /// @brief Process next queued request for the given URL.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param url URL for which next queued request should be retrieved.
    void processNextRequestInternal(const Url& url) {
        // Check if there is a queue for this URL. If there is no queue, there
        // is no request queued either.
        auto it = queue_.find(url);
        if (it != queue_.end()) {
            // If the queue is non empty, we take the oldest request.
            if (!it->second.empty()) {
                RequestDescriptor desc = it->second.front();
                it->second.pop();
                desc.conn_->doTransaction(desc.request_, desc.response_,
                                          desc.request_timeout_,
                                          desc.callback_,
                                          desc.connect_callback_,
                                          desc.handshake_callback_,
                                          desc.close_callback_);
            }
        }
    }

    /// @brief Queue next request for sending to the server.
    ///
    /// A new transaction is started immediately, if there is no other request
    /// in progress for the given URL. Otherwise, the request is queued.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param url Destination where the request should be sent.
    /// @param context TLS context to be used for the connection.
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response should be
    /// stored.
    /// @param request_timeout Requested timeout for the transaction in
    /// milliseconds.
    /// @param request_callback Pointer to the user callback to be invoked when the
    /// transaction ends.
    /// @param connect_callback Pointer to the user callback to be invoked when the
    /// client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the user callback to be invoked when the
    /// client closes the connection to the server.
    void queueRequestInternal(const Url& url,
                              const TlsContextPtr& context,
                              const HttpRequestPtr& request,
                              const HttpResponsePtr& response,
                              const long request_timeout,
                              const HttpClient::RequestHandler& request_callback,
                              const HttpClient::ConnectHandler& connect_callback,
                              const HttpClient::HandshakeHandler& handshake_callback,
                              const HttpClient::CloseHandler& close_callback) {
        auto it = conns_.find(url);
        if (it != conns_.end()) {
            ConnectionPtr conn = it->second;
            // There is a connection for this URL already. Check if it is idle.
            if (conn->isTransactionOngoing()) {
                // Connection is busy, so let's queue the request.
                queue_[url].push(RequestDescriptor(conn, request, response,
                                                   request_timeout,
                                                   request_callback,
                                                   connect_callback,
                                                   handshake_callback,
                                                   close_callback));
            } else {
                // Connection is idle, so we can start the transaction.
                conn->doTransaction(request, response, request_timeout,
                                    request_callback, connect_callback,
                                    handshake_callback, close_callback);
            }
        } else {
            // There is no connection with this destination yet. Let's create
            // it and start the transaction.
            ConnectionPtr conn(new Connection(io_service_,
                                              context,
                                              shared_from_this(),
                                              url));
            conn->doTransaction(request, response, request_timeout,
                                request_callback, connect_callback,
                                handshake_callback, close_callback);
            conns_[url] = conn;
        }
    }

    /// @brief Closes connection and removes associated information from the
    /// connection pool.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param url URL for which connection should be closed.
    void closeConnectionInternal(const Url& url) {
        // Close connection for the specified URL.
        auto conns_it = conns_.find(url);
        if (conns_it != conns_.end()) {
            conns_it->second->close();
            conns_.erase(conns_it);
        }

        // Remove requests from the queue.
        auto queue_it = queue_.find(url);
        if (queue_it != queue_.end()) {
            queue_.erase(queue_it);
        }
    }

    /// @brief Closes all connections and removes associated information from
    /// the connection pool.
    ///
    /// This method should be called in a thread safe context.
    void closeAllInternal() {
        for (auto conns_it = conns_.begin(); conns_it != conns_.end();
             ++conns_it) {
            conns_it->second->close();
        }

        conns_.clear();
        queue_.clear();
    }

    /// @brief Closes a connection if it has an out-of-band socket event
    ///
    /// If the pool contains a connection using the given socket and that
    /// connection is currently in a transaction the method returns as this
    /// indicates a normal ready event.  If the connection is not in an
    /// ongoing transaction, then the connection is closed.
    ///
    /// This is method is intended to be used to detect and clean up then
    /// sockets that are marked ready outside of transactions. The most common
    /// case is the other end of the socket being closed.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param socket_fd socket descriptor to check
    void closeIfOutOfBandInternal(int socket_fd) {
        // First we look for a connection with the socket.
        for (auto conns_it = conns_.begin(); conns_it != conns_.end();
             ++conns_it) {

            if (!conns_it->second->isMySocket(socket_fd)) {
                // Not this connection.
                continue;
            }

            if (conns_it->second->isTransactionOngoing()) {
                // Matches but is in a transaction, all is well.
                return;
            }

            // Socket has no transaction, so any ready event is
            // out-of-band (other end probably closed), so
            // let's close it.  Note we do not remove any queued
            // requests, as this might somehow be occurring in
            // between them.
            conns_it->second->close();
            conns_.erase(conns_it);
            break;
        }
    }

    /// @brief Holds reference to the IO service.
    IOService& io_service_;

    /// @brief Holds mapping of URLs to connections.
    std::map<Url, ConnectionPtr> conns_;

    /// @brief Request descriptor holds parameters associated with the
    /// particular request.
    struct RequestDescriptor {
        /// @brief Constructor.
        ///
        /// @param conn Pointer to the connection.
        /// @param request Pointer to the request to be sent.
        /// @param response Pointer to the object into which the response will
        /// be stored.
        /// @param request_timeout Requested timeout for the transaction.
        /// @param callback Pointer to the user callback.
        /// @param connect_callback pointer to the user callback to be invoked
        /// when the client connects to the server.
        /// @param handshake_callback Optional callback invoked when the client
        /// performs the TLS handshake with the server.
        /// @param close_callback pointer to the user callback to be invoked
        /// when the client closes the connection to the server.
        RequestDescriptor(const ConnectionPtr& conn,
                          const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const long& request_timeout,
                          const HttpClient::RequestHandler& callback,
                          const HttpClient::ConnectHandler& connect_callback,
                          const HttpClient::HandshakeHandler& handshake_callback,
                          const HttpClient::CloseHandler& close_callback)
            : conn_(conn), request_(request), response_(response),
              request_timeout_(request_timeout), callback_(callback),
              connect_callback_(connect_callback),
              handshake_callback_(handshake_callback),
              close_callback_(close_callback) {
        }

        /// @brief Holds the connection.
        ConnectionPtr conn_;

        /// @brief Holds pointer to the request.
        HttpRequestPtr request_;

        /// @brief Holds pointer to the response.
        HttpResponsePtr response_;

        /// @brief Holds requested timeout value.
        long request_timeout_;

        /// @brief Holds pointer to the user callback.
        HttpClient::RequestHandler callback_;

        /// @brief Holds pointer to the user callback for connect.
        HttpClient::ConnectHandler connect_callback_;

        /// @brief Holds pointer to the user callback for handshake.
        HttpClient::HandshakeHandler handshake_callback_;

        /// @brief Holds pointer to the user callback for close.
        HttpClient::CloseHandler close_callback_;
    };

    /// @brief Holds the queue of requests for different URLs.
    std::map<Url, std::queue<RequestDescriptor> > queue_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

Connection::Connection(IOService& io_service,
                       const TlsContextPtr& context,
                       const ConnectionPoolPtr& conn_pool,
                       const Url& url)
    : conn_pool_(conn_pool), url_(url), tcp_socket_(), tls_socket_(),
      timer_(io_service), current_request_(), current_response_(),
      parser_(), current_callback_(), buf_(), input_buf_(),
      current_transid_(0), close_callback_(), started_(false) {
    if (!context) {
        tcp_socket_.reset(new asiolink::TCPSocket<SocketCallback>(io_service));
    } else {
        tls_socket_.reset(new asiolink::TLSSocket<SocketCallback>(io_service,
                                                                  context));
    }
}

Connection::~Connection() {
    close();
}

void
Connection::resetState() {
    started_ = false;
    current_request_.reset();
    current_response_.reset();
    parser_.reset();
    current_callback_ = HttpClient::RequestHandler();
}

void
Connection::closeCallback(const bool clear) {
    if (close_callback_) {
        try {
            if (tcp_socket_) {
                close_callback_(tcp_socket_->getNative());
            } else if (tls_socket_) {
                close_callback_(tls_socket_->getNative());
            } else {
                isc_throw(Unexpected,
                          "internal error: can't find a socket to close");
            }
        } catch (...) {
            LOG_ERROR(http_logger, HTTP_CONNECTION_CLOSE_CALLBACK_FAILED);
        }
    }

    if (clear) {
        close_callback_ = HttpClient::CloseHandler();
    }
}

void
Connection::doTransaction(const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const long request_timeout,
                          const HttpClient::RequestHandler& callback,
                          const HttpClient::ConnectHandler& connect_callback,
                          const HttpClient::HandshakeHandler& handshake_callback,
                          const HttpClient::CloseHandler& close_callback) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        doTransactionInternal(request, response, request_timeout,
                              callback, connect_callback, handshake_callback,
                              close_callback);
    } else {
        doTransactionInternal(request, response, request_timeout,
                              callback, connect_callback, handshake_callback,
                              close_callback);
    }
}

void
Connection::doTransactionInternal(const HttpRequestPtr& request,
                                  const HttpResponsePtr& response,
                                  const long request_timeout,
                                  const HttpClient::RequestHandler& callback,
                                  const HttpClient::ConnectHandler& connect_callback,
                                  const HttpClient::HandshakeHandler& handshake_callback,
                                  const HttpClient::CloseHandler& close_callback) {
    try {
        started_ = true;
        current_request_ = request;
        current_response_ = response;
        parser_.reset(new HttpResponseParser(*current_response_));
        parser_->initModel();
        current_callback_ = callback;
        handshake_callback_ = handshake_callback;
        close_callback_ = close_callback;

        // Starting new transaction. Generate new transaction id.
        ++current_transid_;

        buf_ = request->toString();

        // If the socket is open we check if it is possible to transmit the data
        // over this socket by reading from it with message peeking. If the socket
        // is not usable, we close it and then re-open it. There is a narrow window of
        // time between checking the socket usability and actually transmitting the
        // data over this socket, when the peer may close the connection. In this
        // case we'll need to re-transmit but we don't handle it here.
        if (tcp_socket_) {
            if (tcp_socket_->getASIOSocket().is_open() &&
                !tcp_socket_->isUsable()) {
                closeCallback();
                tcp_socket_->close();
            }
        } else if (tls_socket_) {
            if (tls_socket_->getASIOSocket().is_open() &&
                !tls_socket_->isUsable()) {
                closeCallback();
                tls_socket_->close();
            }
        } else {
            isc_throw(Unexpected,
                      "internal error: can't find the sending socket");
        }

        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  HTTP_CLIENT_REQUEST_SEND)
            .arg(request->toBriefString())
            .arg(url_.toText());

        LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                  HTTP_CLIENT_REQUEST_SEND_DETAILS)
            .arg(url_.toText())
            .arg(HttpMessageParserBase::logFormatHttpMessage(request->toString(),
                                                             MAX_LOGGED_MESSAGE_SIZE));

        // Setup request timer.
        scheduleTimer(request_timeout);

        /// @todo We're getting a hostname but in fact it is expected to be an IP address.
        /// We should extend the TCPEndpoint to also accept names. Currently, it will fall
        /// over for names.
        TCPEndpoint endpoint(url_.getStrippedHostname(),
                             static_cast<unsigned short>(url_.getPort()));
        SocketCallback socket_cb(std::bind(&Connection::connectCallback, shared_from_this(),
                                           connect_callback, current_transid_,
                                           ph::_1));

        // Establish new connection or use existing connection.
        if (tcp_socket_) {
            tcp_socket_->open(&endpoint, socket_cb);
            return;
        }
        if (tls_socket_) {
            tls_socket_->open(&endpoint, socket_cb);
            return;
        }

        // Should never reach this point.
        isc_throw(Unexpected,
                  "internal error: can't find a socket to open");

    } catch (const std::exception& ex) {
        // Re-throw with the expected exception type.
        isc_throw(HttpClientError, ex.what());
    }
}

void
Connection::close() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (closeInternal());
    } else {
        return (closeInternal());
    }
}

void
Connection::closeInternal() {
    // Pass in true to discard the callback.
    closeCallback(true);

    timer_.cancel();
    if (tcp_socket_) {
        tcp_socket_->close();
    }
    if (tls_socket_) {
        tls_socket_->close();
    }

    resetState();
}

bool
Connection::isTransactionOngoing() const {
    return (started_);
}

bool
Connection::isMySocket(int socket_fd) const {
    if (tcp_socket_) {
        return (tcp_socket_->getNative() == socket_fd);
    } else if (tls_socket_) {
        return (tls_socket_->getNative() == socket_fd);
    }
    // Should never reach this point.
    std::cerr << "internal error: can't find my socket\n";
    return (false);
}

bool
Connection::checkPrematureTimeout(const uint64_t transid) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (checkPrematureTimeoutInternal(transid));
    } else {
        return (checkPrematureTimeoutInternal(transid));
    }
}

bool
Connection::checkPrematureTimeoutInternal(const uint64_t transid) {
    // If there is no transaction but the handlers are invoked it means
    // that the last transaction in the queue timed out prematurely.
    // Also, if there is a transaction in progress but the ID of that
    // transaction doesn't match the one associated with the handler it,
    // also means that the transaction timed out prematurely.
    if (!isTransactionOngoing() || (transid != current_transid_)) {
        LOG_WARN(http_logger, HTTP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED);
        return (true);
    }
    return (false);
}

void
Connection::terminate(const boost::system::error_code& ec,
                      const std::string& parsing_error) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        terminateInternal(ec, parsing_error);
    } else {
        terminateInternal(ec, parsing_error);
    }
}

void
Connection::terminateInternal(const boost::system::error_code& ec,
                              const std::string& parsing_error) {
    HttpResponsePtr response;

    if (isTransactionOngoing()) {

        timer_.cancel();
        if (tcp_socket_) {
            tcp_socket_->cancel();
        }
        if (tls_socket_) {
            tls_socket_->cancel();
        }

        if (!ec && current_response_->isFinalized()) {
            response = current_response_;

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_SERVER_RESPONSE_RECEIVED)
                .arg(url_.toText());

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                      HTTP_SERVER_RESPONSE_RECEIVED_DETAILS)
                .arg(url_.toText())
                .arg(parser_ ?
                     parser_->getBufferAsString(MAX_LOGGED_MESSAGE_SIZE) :
                     "[HttpResponseParser is null]");

        } else {
            std::string err = parsing_error.empty() ? ec.message() :
                                                      parsing_error;

            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_BAD_SERVER_RESPONSE_RECEIVED)
                .arg(url_.toText())
                .arg(err);

            // Only log the details if we have received anything and tried
            // to parse it.
            if (!parsing_error.empty()) {
                LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                          HTTP_BAD_SERVER_RESPONSE_RECEIVED_DETAILS)
                    .arg(url_.toText())
                    .arg(parser_ ?
                         parser_->getBufferAsString(MAX_LOGGED_MESSAGE_SIZE) :
                         "[HttpResponseParser is null]");
            }
        }

        try {
            // The callback should take care of its own exceptions but one
            // never knows.
            if (MultiThreadingMgr::instance().getMode()) {
                UnlockGuard<std::mutex> lock(mutex_);
                current_callback_(ec, response, parsing_error);
            } else {
                current_callback_(ec, response, parsing_error);
            }
        } catch (...) {
        }

        // If we're not requesting connection persistence or the connection has timed out,
        // we should close the socket. We're going to reconnect for the next transaction.
        if (!current_request_->isPersistent() || (ec == boost::asio::error::timed_out)) {
            closeInternal();
        }

        resetState();
    }

    // Check if there are any requests queued for this connection and start
    // another transaction if there is at least one.
    ConnectionPoolPtr conn_pool = conn_pool_.lock();
    if (conn_pool) {
        if (MultiThreadingMgr::instance().getMode()) {
            UnlockGuard<std::mutex> lock(mutex_);
            conn_pool->processNextRequest(url_);
        } else {
            conn_pool->processNextRequest(url_);
        }
    }
}

void
Connection::scheduleTimer(const long request_timeout) {
    if (request_timeout > 0) {
        timer_.setup(std::bind(&Connection::timerCallback, this), request_timeout,
                     IntervalTimer::ONE_SHOT);
    }
}

void
Connection::doHandshake(const uint64_t transid) {
    // Skip the handshake if the socket is not a TLS one.
    if (!tls_socket_) {
        doSend(transid);
        return;
    }

    SocketCallback socket_cb(std::bind(&Connection::handshakeCallback,
                                       shared_from_this(),
                                       handshake_callback_,
                                       transid,
                                       ph::_1));
    try {
       tls_socket_->handshake(socket_cb);

    } catch (...) {
        terminate(boost::asio::error::not_connected);
    }
}

void
Connection::doSend(const uint64_t transid) {
    SocketCallback socket_cb(std::bind(&Connection::sendCallback,
                                       shared_from_this(),
                                       transid,
                                       ph::_1,
                                       ph::_2));
    try {
        if (tcp_socket_) {
            tcp_socket_->asyncSend(&buf_[0], buf_.size(), socket_cb);
            return;
        }
        if (tls_socket_) {
            tls_socket_->asyncSend(&buf_[0], buf_.size(), socket_cb);
            return;
        }
        // Should never reach this point.
        std::cerr << "internal error: can't find a socket to send to\n";
        isc_throw(Unexpected,
                  "internal error: can't find a socket to send to");

    } catch (...) {
        terminate(boost::asio::error::not_connected);
    }
}

void
Connection::doReceive(const uint64_t transid) {
    TCPEndpoint endpoint;
    SocketCallback socket_cb(std::bind(&Connection::receiveCallback,
                                       shared_from_this(),
                                       transid,
                                       ph::_1,
                                       ph::_2));

    try {
        if (tcp_socket_) {
            tcp_socket_->asyncReceive(static_cast<void*>(input_buf_.data()),
                                      input_buf_.size(), 0,
                                      &endpoint, socket_cb);
            return;
        }
        if (tls_socket_) {
            tls_socket_->asyncReceive(static_cast<void*>(input_buf_.data()),
                                      input_buf_.size(), 0,
                                      &endpoint, socket_cb);
            return;
        }
        // Should never reach this point.
        std::cerr << "internal error: can't find a socket to receive from\n";
        isc_throw(Unexpected,
                  "internal error: can't find a socket to receive from");

    } catch (...) {
        terminate(boost::asio::error::not_connected);
    }
}

void
Connection::connectCallback(HttpClient::ConnectHandler connect_callback,
                            const uint64_t transid,
                            const boost::system::error_code& ec) {
    if (checkPrematureTimeout(transid)) {
        return;
    }

    // Run user defined connect callback if specified.
    if (connect_callback) {
        // If the user defined callback indicates that the connection
        // should not be continued.
        if (tcp_socket_) {
            if (!connect_callback(ec, tcp_socket_->getNative())) {
                return;
            }
        } else if (tls_socket_) {
            if (!connect_callback(ec, tls_socket_->getNative())) {
                return;
            }
        } else {
            // Should never reach this point.
            std::cerr << "internal error: can't find a socket to connect\n";
        }
    }

    if (ec && (ec.value() == boost::asio::error::operation_aborted)) {
        return;

    // In some cases the "in progress" status code may be returned. It doesn't
    // indicate an error. Sending the request over the socket is expected to
    // be successful. Getting such status appears to be highly dependent on
    // the operating system.
    } else if (ec &&
        (ec.value() != boost::asio::error::in_progress) &&
        (ec.value() != boost::asio::error::already_connected)) {
        terminate(ec);

    } else {
        // Start the TLS handshake asynchronously.
        doHandshake(transid);
    }
}

void
Connection::handshakeCallback(HttpClient::ConnectHandler connect_callback,
                              const uint64_t transid,
                              const boost::system::error_code& ec) {
    if (checkPrematureTimeout(transid)) {
        return;
    }

    // Run user defined handshake callback if specified.
    if (handshake_callback_) {
        // If the user defined callback indicates that the connection
        // should not be continued.
        if (tls_socket_) {
            if (!handshake_callback_(ec, tls_socket_->getNative())) {
                return;
            }
        } else {
            // Should never reach this point.
            std::cerr << "internal error: can't find TLS socket\n";
        }
    }

    if (ec && (ec.value() == boost::asio::error::operation_aborted)) {
        return;
    } else if (ec) {
        terminate(ec);

    } else {
        // Start sending the request asynchronously.
        doSend(transid);
    }
}

void
Connection::sendCallback(const uint64_t transid,
                         const boost::system::error_code& ec,
                         size_t length) {
    if (checkPrematureTimeout(transid)) {
        return;
    }

    if (ec) {
        if (ec.value() == boost::asio::error::operation_aborted) {
            return;

        // EAGAIN and EWOULDBLOCK don't really indicate an error. The length
        // should be 0 in this case but let's be sure.
        } else if ((ec.value() == boost::asio::error::would_block) ||
            (ec.value() == boost::asio::error::try_again)) {
            length = 0;

        } else {
            // Any other error should cause the transaction to terminate.
            terminate(ec);
            return;
        }
    }

    // Sending is in progress, so push back the timeout.
    scheduleTimer(timer_.getInterval());

    // If any data have been sent, remove it from the buffer and only leave the
    // portion that still has to be sent.
    if (length > 0) {
        buf_.erase(0, length);
    }

    // If there is no more data to be sent, start receiving a response. Otherwise,
    // continue sending.
    if (buf_.empty()) {
        doReceive(transid);

    } else {
        doSend(transid);
    }
}

void
Connection::receiveCallback(const uint64_t transid,
                            const boost::system::error_code& ec,
                            size_t length) {
    if (checkPrematureTimeout(transid)) {
        return;
    }

    if (ec) {
        if (ec.value() == boost::asio::error::operation_aborted) {
            return;

        // EAGAIN and EWOULDBLOCK don't indicate an error in this case. All
        // other errors should terminate the transaction.
        } if ((ec.value() != boost::asio::error::try_again) &&
              (ec.value() != boost::asio::error::would_block)) {
            terminate(ec);
            return;

        } else {
            // For EAGAIN and EWOULDBLOCK the length should be 0 anyway, but let's
            // make sure.
            length = 0;
        }
    }

    // Receiving is in progress, so push back the timeout.
    scheduleTimer(timer_.getInterval());

    if (runParser(ec, length)) {
        doReceive(transid);
    }
}

bool
Connection::runParser(const boost::system::error_code& ec, size_t length) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (runParserInternal(ec, length));
    } else {
        return (runParserInternal(ec, length));
    }
}

bool
Connection::runParserInternal(const boost::system::error_code& ec,
                              size_t length) {
    // If we have received any data, let's feed the parser with it.
    if (length != 0) {
        parser_->postBuffer(static_cast<void*>(input_buf_.data()), length);
        parser_->poll();
    }

    // If the parser still needs data, let's schedule another receive.
    if (parser_->needData()) {
        return (true);

    } else if (parser_->httpParseOk()) {
        // No more data needed and parsing has been successful so far. Let's
        // try to finalize the response parsing.
        try {
            current_response_->finalize();
            terminateInternal(ec);

        } catch (const std::exception& ex) {
            // If there is an error here, we need to return the error message.
            terminateInternal(ec, ex.what());
        }

    } else {
        // Parsing was unsuccessful. Let's pass the error message held in the
        // parser.
        terminateInternal(ec, parser_->getErrorMessage());
    }

    return (false);
}

void
Connection::timerCallback() {
    // Request timeout occurred.
    terminate(boost::asio::error::timed_out);
}

}

namespace isc {
namespace http {

/// @brief HttpClient implementation.
class HttpClientImpl {
public:

    /// @brief Constructor.
    ///
    /// Creates new connection pool.
    HttpClientImpl(IOService& io_service)
        : conn_pool_(new ConnectionPool(io_service)) {
    }

    /// @brief Holds a pointer to the connection pool.
    ConnectionPoolPtr conn_pool_;

};

HttpClient::HttpClient(IOService& io_service)
    : impl_(new HttpClientImpl(io_service)) {
}

void
HttpClient::asyncSendRequest(const Url& url,
                             const TlsContextPtr& context,
                             const HttpRequestPtr& request,
                             const HttpResponsePtr& response,
                             const HttpClient::RequestHandler& request_callback,
                             const HttpClient::RequestTimeout& request_timeout,
                             const HttpClient::ConnectHandler& connect_callback,
                             const HttpClient::HandshakeHandler& handshake_callback,
                             const HttpClient::CloseHandler& close_callback) {
    if (!url.isValid()) {
        isc_throw(HttpClientError, "invalid URL specified for the HTTP client");
    }

    if (!request) {
        isc_throw(HttpClientError, "HTTP request must not be null");
    }

    if (!response) {
        isc_throw(HttpClientError, "HTTP response must not be null");
    }

    if (!request_callback) {
        isc_throw(HttpClientError, "callback for HTTP transaction must not be null");
    }

    impl_->conn_pool_->queueRequest(url, context, request, response,
                                    request_timeout.value_,
                                    request_callback, connect_callback,
                                    handshake_callback, close_callback);
}

void
HttpClient::closeIfOutOfBand(int socket_fd)  {
    return (impl_->conn_pool_->closeIfOutOfBand(socket_fd));
}

void
HttpClient::stop() {
    impl_->conn_pool_->closeAll();
}

} // end of namespace isc::http
} // end of namespace isc
