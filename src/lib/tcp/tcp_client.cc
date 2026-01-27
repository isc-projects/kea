// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service_thread_pool.h>
#include <asiolink/tls_socket.h>
#include <tcp/tcp_client.h>
#include <tcp/tcp_log.h>
#include <tcp/tcp_messages.h>
#include <util/boost_time_utils.h>
#include <util/str.h>
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
#include <thread>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::tcp;
using namespace isc::util;
using namespace boost::posix_time;

namespace ph = std::placeholders;

namespace {

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

/// @brief Client side TCP connection to the server.
///
/// Each connection is established with a unique destination identified by the
/// specified address and TLS context. Multiple requests to the same
/// destination can be sent over the same connection, if the connection is
/// persistent. If the server closes the TCP connection (e.g. after sending
/// a response), the connection is closed.
///
/// If new request is created while the previous request is still in progress,
/// the new request is stored in the FIFO queue. The queued requests to the
/// particular address are sent to the server when the current transaction ends.
///
/// The communication over the transport socket is asynchronous. The caller is
/// notified about the completion of the transaction via a callback that the
/// caller supplies when initiating the transaction.
class Connection : public boost::enable_shared_from_this<Connection> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used for the connection.
    /// @param tls_context TLS context to be used for the connection.
    /// @param conn_pool Back pointer to the connection pool to which this
    /// connection belongs.
    /// @param address Address associated with this connection.
    /// @param port Port associated with this connection.
    explicit Connection(const IOServicePtr& io_service,
                        const TlsContextPtr& tls_context,
                        const ConnectionPoolPtr& conn_pool,
                        const IOAddress& address,
                        const uint16_t port);

    /// @brief Destructor.
    ~Connection();

    /// @brief Starts new asynchronous transaction (TCP request and response).
    ///
    /// This method expects that all pointers provided as argument are non-null.
    ///
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response is stored.
    /// @param persistent Flag to make the connection persistent.
    /// @param request_timeout Request timeout in milliseconds.
    /// @param complete_check Pointer to the completion checker.
    /// @param callback Pointer to the callback function to be invoked when the
    /// transaction completes.
    /// @param connect_callback Pointer to the callback function to be invoked
    /// when the client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the callback function to be invoked
    /// when the client closes the socket to the server.
    void doTransaction(const WireDataPtr& request,
                       const WireDataPtr& response,
                       const bool persistent,
                       const long request_timeout,
                       const TcpClient::CompleteCheck& complete_check,
                       const TcpClient::RequestHandler& callback,
                       const TcpClient::ConnectHandler& connect_callback,
                       const TcpClient::HandshakeHandler& handshake_callback,
                       const TcpClient::CloseHandler& close_callback);

    /// @brief Closes the socket and cancels the request timer.
    void close();

    /// @brief Checks if a transaction has been initiated over this connection.
    ///
    /// @return true if transaction has been initiated, false otherwise.
    bool isTransactionOngoing() const {
        return (started_);
    }

    /// @brief Checks if the socket has been closed.
    ///
    /// @return true if the socket has been closed.
    bool isClosed() const {
        return (closed_);
    }

    /// @brief Checks if the peer has closed the idle socket at its side.
    ///
    /// If the socket is open but is not usable the peer has closed
    /// the socket at its side so we close it.
    void isClosedByPeer();

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

    /// @brief Starts new asynchronous transaction (TCP request and response).
    ///
    /// Should be called in a thread safe context.
    ///
    /// This method expects that all pointers provided as argument are non-null.
    ///
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response is stored.
    /// @param request_timeout Request timeout in milliseconds.
    /// @param complete_check Pointer to the completion checker.
    /// @param persistent Flag to make the connection persistent.
    /// @param callback Pointer to the callback function to be invoked when the
    /// transaction completes.
    /// @param connect_callback Pointer to the callback function to be invoked
    /// when the client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the callback function to be invoked
    /// when the client closes the socket to the server.
    void doTransactionInternal(const WireDataPtr& request,
                               const WireDataPtr& response,
                               const bool persistent,
                               const long request_timeout,
                               const TcpClient::CompleteCheck& complete_check,
                               const TcpClient::RequestHandler& callback,
                               const TcpClient::ConnectHandler& connect_callback,
                               const TcpClient::HandshakeHandler& handshake_callback,
                               const TcpClient::CloseHandler& close_callback);

    /// @brief Closes the socket and cancels the request timer.
    ///
    /// Should be called in a thread safe context.
    void closeInternal();

    /// @brief Checks if the peer has closed the socket at its side.
    ///
    /// Should be called in a thread safe context.
    ///
    /// If the socket is open but is not usable the peer has closed
    /// the socket at its side so we close it.
    void isClosedByPeerInternal();

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
    /// address associated with this connection.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param error_msg Message error.
    void terminate(const boost::system::error_code& ec,
                   const std::string& error_msg = "");

    /// @brief Performs tasks required after receiving a response or after an
    /// error.
    ///
    /// Should be called in a thread safe context.
    ///
    /// This method triggers user's callback, resets the state of the connection
    /// and initiates next transaction if there is any transaction queued for the
    /// address associated with this connection.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param parsing_error Message parsing error.
    void terminateInternal(const boost::system::error_code& ec,
                           const std::string& error_msg = "");

    /// @brief Run completion checker and check if more data is needed.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param length Number of bytes received.
    ///
    /// @return true if more data is needed, false otherwise.
    bool runCompleteCheck(const boost::system::error_code& ec, size_t length);

    /// @brief Run completion checker and check if more data is needed.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @param ec Error code received as a result of the IO operation.
    /// @param length Number of bytes received.
    ///
    /// @return true if more data is needed, false otherwise.
    bool runCompleteCheckInternal(const boost::system::error_code& ec, size_t length);

    /// @brief This method schedules timer or reschedules existing timer.
    ///
    /// @param request_timeout New timer interval in milliseconds.
    void scheduleTimer(const long request_timeout);

    /// @brief Asynchronously performs the TLS handshake.
    ///
    /// The TLS handshake is performed once on TLS sockets.
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
    void connectCallback(TcpClient::ConnectHandler connect_callback,
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
    void handshakeCallback(TcpClient::HandshakeHandler handshake_callback,
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
    void receiveCallback(const uint64_t transid,
                         const boost::system::error_code& ec,
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

    /// @brief A reference to the IOService that drives socket IO.
    IOServicePtr io_service_;

    /// @brief Pointer to the connection pool owning this connection.
    ///
    /// This is a weak pointer to avoid circular dependency between the
    /// Connection and ConnectionPool.
    boost::weak_ptr<ConnectionPool> conn_pool_;

    /// @brief Address for this connection.
    IOAddress address_;

    /// @brief Port for this connection.
    uint16_t port_;

    /// @brief TLS context for this connection.
    TlsContextPtr tls_context_;

    /// @brief TCP socket to be used for this connection.
    std::shared_ptr<TCPSocket<SocketCallback>> tcp_socket_;

    /// @brief TLS socket to be used for this connection.
    std::shared_ptr<TLSSocket<SocketCallback>> tls_socket_;

    /// @brief Interval timer used for detecting request timeouts.
    IntervalTimerPtr timer_;

    /// @brief Holds currently sent request.
    WireDataPtr current_request_;

    /// @brief Holds pointer to an object where response is to be stored.
    WireDataPtr current_response_;

    /// @brief Holds persistent flag.
    bool current_persistent_;

    /// @brief Response complete flag.
    bool current_response_complete_;

    /// @brief User supplied completion checker.
    TcpClient::CompleteCheck current_complete_check_;

    /// @brief User supplied callback.
    TcpClient::RequestHandler current_callback_;

    /// @brief Output buffer.
    std::vector<uint8_t>  buf_;

    /// @brief Input buffer.
    std::array<uint8_t, 32768> input_buf_;

    /// @brief Identifier of the current transaction.
    uint64_t current_transid_;

    /// @brief User supplied handshake callback.
    TcpClient::HandshakeHandler handshake_callback_;

    /// @brief User supplied close callback.
    TcpClient::CloseHandler close_callback_;

    /// @brief Flag to indicate that a transaction is running.
    std::atomic<bool> started_;

    /// @brief Flag to indicate that the TLS handshake has to be performed.
    std::atomic<bool> need_handshake_;

    /// @brief Flag to indicate that the socket was closed.
    std::atomic<bool> closed_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

/// @brief Shared pointer to the connection.
typedef boost::shared_ptr<Connection> ConnectionPtr;

/// @brief Connection pool for managing multiple connections.
///
/// Connection pool creates and destroys address destinations. It manages
/// connections to and requests for addresses. Each time a request is
/// submitted for an address, it assigns it to an available idle connection,
/// or if no idle connections are available, pushes the request on the queue
/// for that address.
class ConnectionPool : public boost::enable_shared_from_this<ConnectionPool> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service to be used by the
    /// connections.
    /// @param max_addr_connections maximum number of concurrent
    /// connections allowed per address.
    explicit ConnectionPool(const IOServicePtr& io_service, size_t max_addr_connections)
        : io_service_(io_service), destinations_(), pool_mutex_(),
          max_addr_connections_(max_addr_connections) {
    }

    /// @brief Destructor.
    ///
    /// Closes all connections.
    ~ConnectionPool() {
        closeAll();
    }

    /// @brief Process next queued request for the given address and TLS context.
    ///
    /// @param address Address for which next queued request should be processed.
    /// @param port Port for which next queued request should be processed.
    /// @param tls_context TLS context for which next queued request
    /// should be processed.
    void processNextRequest(const IOAddress& address,
                            const uint16_t port,
                            const TlsContextPtr& tls_context) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(pool_mutex_);
            return (processNextRequestInternal(address, port, tls_context));
        } else {
            return (processNextRequestInternal(address, port, tls_context));
        }
    }

    /// @brief Schedule processing of next queued request.
    ///
    /// @param address Address for which next queued request should be processed.
    /// @param port Port for which next queued request should be processed.
    /// @param tls_context TLS context for which next queued request
    /// should be processed.
    void postProcessNextRequest(const IOAddress& address,
                                const uint16_t port,
                                const TlsContextPtr& tls_context) {
        io_service_->post(std::bind(&ConnectionPool::processNextRequest,
                                    shared_from_this(),
                                    address, port,
                                    tls_context));
    }

    /// @brief Queue next request for sending to the server.
    ///
    /// A new transaction is started immediately, if there is no other request
    /// in progress for the given address. Otherwise, the request is queued.
    ///
    /// @param address Destination address where the request should be sent.
    /// @param port Destination port where the request should be sent.
    /// @param tls_context TLS context to be used for the connection.
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response should be
    /// stored.
    /// @param persistent Flag to make the connection persistent.
    /// @param request_timeout Requested timeout for the transaction in
    /// milliseconds.
    /// @param complete_check Pointer to the completion checker.
    /// @param request_callback Pointer to the user callback to be invoked when the
    /// transaction ends.
    /// @param connect_callback Pointer to the user callback to be invoked when the
    /// client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the user callback to be invoked when the
    /// client closes the connection to the server.
    void queueRequest(const IOAddress& address,
                      const uint16_t port,
                      const TlsContextPtr& tls_context,
                      const WireDataPtr& request,
                      const WireDataPtr& response,
                      const bool persistent,
                      const long request_timeout,
                      const TcpClient::CompleteCheck& complete_check,
                      const TcpClient::RequestHandler& request_callback,
                      const TcpClient::ConnectHandler& connect_callback,
                      const TcpClient::HandshakeHandler& handshake_callback,
                      const TcpClient::CloseHandler& close_callback) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(pool_mutex_);
            return (queueRequestInternal(address, port, tls_context,
                                         request, response, persistent,
                                         request_timeout, complete_check,
                                         request_callback, connect_callback,
                                         handshake_callback, close_callback));
        } else {
            return (queueRequestInternal(address, port, tls_context,
                                         request, response, persistent,
                                         request_timeout, complete_check,
                                         request_callback, connect_callback,
                                         handshake_callback, close_callback));
        }
    }

    /// @brief Closes all addresses and removes associated information from
    /// the connection pool.
    void closeAll() {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(pool_mutex_);
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
            std::lock_guard<std::mutex> lk(pool_mutex_);
            closeIfOutOfBandInternal(socket_fd);
        } else {
            closeIfOutOfBandInternal(socket_fd);
        }
    }

private:

    /// @brief Process next queued request for the given address and TLS context.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param address Address for which next queued request should be retrieved.
    /// @param port Port for which next queued request should be retrieved.
    /// @param tls_context TLS context for which next queued request
    /// should be processed.
    void processNextRequestInternal(const IOAddress& address,
                                    const uint16_t port,
                                    const TlsContextPtr& tls_context) {
        // Check if there is a queue for this address. If there is no queue,
        // there is no request queued either.
        DestinationPtr destination = findDestination(address, port, tls_context);
        if (destination) {
            // Remove closed connections.
            destination->garbageCollectConnections();
            if (!destination->queueEmpty()) {
                // We have at least one queued request. Do we have an
                // idle connection?
                ConnectionPtr connection = destination->getIdleConnection();
                if (!connection) {
                    // No idle connections.
                    if (destination->connectionsFull()) {
                        return;
                    }
                    // Room to make another connection with this destination,
                    // so make one.
                    connection.reset(new Connection(io_service_,
                                                    tls_context,
                                                    shared_from_this(),
                                                    address, port));
                    destination->addConnection(connection);
                }

                // Dequeue the oldest request and start a transaction for it using
                // the idle connection.
                RequestDescriptor desc = destination->popNextRequest();
                connection->doTransaction(desc.request_,
                                          desc.response_,
                                          desc.persistent_,
                                          desc.request_timeout_,
                                          desc.complete_check_,
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
    /// in progress for the given address. Otherwise, the request is queued.
    ///
    /// This method should be called in a thread safe context.
    ///
    /// @param address Destination address where the request should be sent.
    /// @param port Destination port where the request should be sent.
    /// @param tls_context TLS context to be used for the connection.
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response should be
    /// stored.
    /// @param persistent Flag to make the connection persistent.
    /// @param request_timeout Requested timeout for the transaction in
    /// milliseconds.
    /// @param complete_check Pointer to the completion checker.
    /// @param request_callback Pointer to the user callback to be invoked when the
    /// transaction ends.
    /// @param connect_callback Pointer to the user callback to be invoked when the
    /// client connects to the server.
    /// @param handshake_callback Optional callback invoked when the client
    /// performs the TLS handshake with the server.
    /// @param close_callback Pointer to the user callback to be invoked when the
    /// client closes the connection to the server.
    void queueRequestInternal(const IOAddress& address,
                              const uint16_t port,
                              const TlsContextPtr& tls_context,
                              const WireDataPtr& request,
                              const WireDataPtr& response,
                              const bool persistent,
                              const long request_timeout,
                              const TcpClient::CompleteCheck& complete_check,
                              const TcpClient::RequestHandler& request_callback,
                              const TcpClient::ConnectHandler& connect_callback,
                              const TcpClient::HandshakeHandler& handshake_callback,
                              const TcpClient::CloseHandler& close_callback) {
        ConnectionPtr connection;
        // Find the destination for the requested address.
        DestinationPtr destination = findDestination(address, port, tls_context);
        if (destination) {
            // Remove closed connections.
            destination->garbageCollectConnections();
            // Found it, look for an idle connection.
            connection = destination->getIdleConnection();
        } else {
            // Doesn't exist yet so it's a new destination.
            destination = addDestination(address, port, tls_context);
        }

        if (!connection) {
            if (destination->connectionsFull()) {
                // All connections busy, queue it.
                destination->pushRequest(RequestDescriptor(request,
                                                           response,
                                                           persistent,
                                                           request_timeout,
                                                           complete_check,
                                                           request_callback,
                                                           connect_callback,
                                                           handshake_callback,
                                                           close_callback));
                return;
            }

            // Room to make another connection with this destination, so make one.
            connection.reset(new Connection(io_service_, tls_context,
                                            shared_from_this(),
                                            address, port));
            destination->addConnection(connection);
        }

        // Use the connection to start the transaction.
        connection->doTransaction(request, response, persistent,
                                  request_timeout, complete_check,
                                  request_callback, connect_callback,
                                  handshake_callback, close_callback);
    }

    /// @brief Closes all connections for all addresses and removes associated
    /// information from the connection pool.
    ///
    /// This method should be called in a thread safe context.
    void closeAllInternal() {
        for (auto const& destination : destinations_) {
            destination.second->closeAllConnections();
        }

        destinations_.clear();
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
        for (auto const& destination : destinations_) {
            // First we look for a connection with the socket.
            ConnectionPtr connection = destination.second->findBySocketFd(socket_fd);
            if (connection) {
                if (!connection->isTransactionOngoing()) {
                    // Socket has no transaction, so any ready event is
                    // out-of-band (other end probably closed), so
                    // let's close it.  Note we do not remove any queued
                    // requests, as this might somehow be occurring in
                    // between them.
                    destination.second->closeConnection(connection);
                }

                return;
            }
        }
    }

    /// @brief Request descriptor holds parameters associated with the
    /// particular request.
    struct RequestDescriptor {
        /// @brief Constructor.
        ///
        /// @param request Pointer to the request to be sent.
        /// @param response Pointer to the object into which the response will
        /// be stored.
        /// @param persistent Flag to make the connection persistent.
        /// @param request_timeout Requested timeout for the transaction.
        /// @param complete_check Pointer to the completion checker.
        /// @param callback Pointer to the user callback.
        /// @param connect_callback pointer to the user callback to be invoked
        /// when the client connects to the server.
        /// @param handshake_callback Optional callback invoked when the client
        /// performs the TLS handshake with the server.
        /// @param close_callback pointer to the user callback to be invoked
        /// when the client closes the connection to the server.
        RequestDescriptor(const WireDataPtr& request,
                          const WireDataPtr& response,
                          const bool persistent,
                          const long& request_timeout,
                          const TcpClient::CompleteCheck& complete_check,
                          const TcpClient::RequestHandler& callback,
                          const TcpClient::ConnectHandler& connect_callback,
                          const TcpClient::HandshakeHandler& handshake_callback,
                          const TcpClient::CloseHandler& close_callback)
            : request_(request),
              response_(response),
              persistent_(persistent),
              request_timeout_(request_timeout),
              complete_check_(complete_check),
              callback_(callback),
              connect_callback_(connect_callback),
              handshake_callback_(handshake_callback),
              close_callback_(close_callback) {
        }

        /// @brief Holds pointer to the request.
        WireDataPtr request_;

        /// @brief Holds pointer to the response.
        WireDataPtr response_;

        /// @brief Hold the persistent flag.
        bool persistent_;

        /// @brief Holds requested timeout value.
        long request_timeout_;

        /// @brief Holds pointer to the completion checker.
        TcpClient::CompleteCheck complete_check_;

        /// @brief Holds pointer to the user callback.
        TcpClient::RequestHandler callback_;

        /// @brief Holds pointer to the user callback for connect.
        TcpClient::ConnectHandler connect_callback_;

        /// @brief Holds pointer to the user callback for handshake.
        TcpClient::HandshakeHandler handshake_callback_;

        /// @brief Holds pointer to the user callback for close.
        TcpClient::CloseHandler close_callback_;
    };

    /// @brief Structure holding address, port and TLS context.
    struct DestinationDescriptor {
        // Constructor.
        DestinationDescriptor(const IOAddress& address,
                              const uint16_t port,
                              const TlsContextPtr& tls_context)
            : address_(address), port_(port), tls_context_(tls_context) {
        }

        // Members.
        IOAddress address_;
        uint16_t port_;
        TlsContextPtr tls_context_;

        // Compare method.
        bool operator<(const DestinationDescriptor& other) const {
            return ((address_ < other.address_) ||
                    ((address_ == other.address_) && (port_ < other.port_)) ||
                    ((address_ == other.address_) && (port_ == other.port_) &&
                     (tls_context_ < other.tls_context_)));
        }
    };

    /// @brief Encapsulates connections and requests for a given address.
    class Destination {
    public:
        /// @brief Number of queued requests allowed without warnings being emitted.
        const size_t QUEUE_SIZE_THRESHOLD = 2048;
        /// @brief Interval between queue size warnings.
        const int QUEUE_WARN_SECS = 5;

        /// @brief Constructor
        ///
        /// @param address server address of this destination
        /// @param port server port of this destination
        /// @param tls_context server TLS context of this destination
        /// @param max_connections maximum number of concurrent connections
        /// allowed for in the list address,
        Destination(IOAddress const& address,
                    uint16_t const port,
                    TlsContextPtr tls_context,
                    size_t max_connections)
            : address_(address), port_(port), tls_context_(tls_context),
              max_connections_(max_connections), connections_(), queue_(),
              last_queue_warn_time_(min_date_time), last_queue_size_(0) {
        }

        /// @brief Destructor
        ~Destination() {
            closeAllConnections();
        }

        /// @brief Adds a new connection
        ///
        /// @param connection the connection to add
        ///
        /// @throw BadValue if the maximum number of connections already
        /// exist.
        /// @note This should be called in a thread safe context.
        void addConnection(ConnectionPtr connection) {
            if (connectionsFull()) {
                isc_throw(BadValue, "address: " << address_.toText()
                      << ", already at maximum connections: "
                      << max_connections_);
            }

            connections_.push_back(connection);
        }

        /// @brief Closes a connection and removes it from the list.
        ///
        /// @param connection the connection to remove
        /// @note This should be called in a thread safe context.
        void closeConnection(ConnectionPtr connection) {
            for (auto it = connections_.begin(); it != connections_.end(); ++it) {
                if (*it == connection) {
                    (*it)->close();
                    connections_.erase(it);
                    break;
                }
            }
        }

        /// @brief Closes all connections and clears the list.
        /// @note This should be called in a thread safe context.
        void closeAllConnections() {
            // Flush the queue.
            while (!queue_.empty()) {
                queue_.pop();
            }

            for (auto const& connection : connections_) {
                connection->close();
            }

            connections_.clear();
        }

        /// @brief Removes closed connections.
        ///
        /// This method should be called before @ref getIdleConnection.
        ///
        /// In a first step it closes not usable idle connections
        /// (idle means no current transaction and not closed,
        /// usable means the peer side did not close it at that time).
        /// In a second step it removes (collects) closed connections.
        ///
        /// @note a connection is closed when the transaction is finished
        /// and the connection is persistent, or when the connection was
        /// idle and the first step of the garbage collector detects that
        /// it was closed by peer, so is not usable.
        ///
        /// @note there are two races here:
        ///  - the peer side closes the connection after the first step
        ///  - a not persistent connection finishes its transaction and
        ///    closes
        /// The second race is avoided by setting the closed flag before
        /// the started flag and by unconditionally posting a process next
        /// request action.
        ///
        /// @note This should be called in a thread safe context.
        void garbageCollectConnections() {
            for (auto it = connections_.begin(); it != connections_.end();) {
                (*it)->isClosedByPeer();
                if (!(*it)->isClosed()) {
                    ++it;
                } else {
                    it = connections_.erase(it);
                }
            }
        }

        /// @brief Finds the first idle connection.
        ///
        /// Iterates over the existing connections and returns the
        /// first connection which is not currently in a transaction and
        /// is not closed.
        ///
        /// @note @ref garbageCollectConnections should be called before.
        /// This removes connections which were closed at that time.
        ///
        /// @return The first idle connection or an empty pointer if
        /// all connections are busy or closed.
        ConnectionPtr getIdleConnection() {
            for (auto const& connection : connections_) {
                if (!connection->isTransactionOngoing() &&
                    !connection->isClosed()) {
                    return (connection);
                }
            }

            return (ConnectionPtr());
        }

        /// @brief Find a connection by its socket descriptor.
        ///
        /// @param socket_fd socket descriptor to find
        ///
        /// @return The connection or an empty pointer if no matching
        /// connection exists.
        ConnectionPtr findBySocketFd(int socket_fd) {
            for (auto const& connection : connections_) {
                if (connection->isMySocket(socket_fd)) {
                    return (connection);
                }
            }

            return (ConnectionPtr());
        }

        /// @brief Indicates if there are no connections in the list.
        ///
        /// @return true if the list is empty.
        bool connectionsEmpty() {
            return (connections_.empty());
        }

        /// @brief Indicates if list contains the maximum number.
        ///
        /// @return true if the list is full.
        bool connectionsFull() {
            return (connections_.size() >= max_connections_);
        }

        /// @brief Fetches the number of connections in the list.
        ///
        /// @return the number of connections in the list.
        size_t connectionCount() {
            return (connections_.size());
        }

        /// @brief Fetches the maximum number of connections.
        ///
        /// @return the maxim number of connections.
        size_t getMaxConnections() const {
            return (max_connections_);
        }

        /// @brief Indicates if request queue is empty.
        ///
        /// @return true if there are no requests queued.
        bool queueEmpty() const {
            return (queue_.empty());
        }

        /// @brief Adds a request to the end of the request queue.
        ///
        /// If the size of the queue exceeds a threshold and appears
        /// to be growing it will emit a warning log.
        ///
        /// @param desc RequestDescriptor to queue.
        void pushRequest(RequestDescriptor const& desc) {
            queue_.push(desc);
            size_t size = queue_.size();
            // If the queue size is larger than the threshold and growing,
            // issue a periodic warning.
            if ((size > QUEUE_SIZE_THRESHOLD) && (size > last_queue_size_)) {
                ptime now = microsec_clock::universal_time();
                if ((now - last_queue_warn_time_) > seconds(QUEUE_WARN_SECS)) {
                    LOG_WARN(tcp_logger, TCP_CLIENT_QUEUE_SIZE_GROWING)
                        .arg(address_.toText())
                        .arg(port_)
                        .arg(size);
                    // Remember the last time we warned.
                    last_queue_warn_time_ = now;
                }
            }

            // Remember the previous size.
            last_queue_size_ = size;
        }

        /// @brief Removes a request from the front of the request queue.
        ///
        /// @return desc RequestDescriptor of the removed request.
        RequestDescriptor popNextRequest() {
            if (queue_.empty()) {
                isc_throw(InvalidOperation, "cannot pop, queue is empty");
            }

            RequestDescriptor desc = queue_.front();
            queue_.pop();
            return (desc);
        }

    private:
        /// @brief Address supported by this destination.
        IOAddress address_;

        /// @brief Port supported by this destination.
        uint16_t port_;

        /// @brief TLS context to use with this destination.
        TlsContextPtr tls_context_;

        /// @brief Maximum number of concurrent connections for this destination.
        size_t max_connections_;

        /// @brief List of concurrent connections.
        std::list<ConnectionPtr> connections_;

        /// @brief Holds the queue of request for this destination.
        std::queue<RequestDescriptor> queue_;

        /// @brief Time the last queue size warning was issued.
        ptime last_queue_warn_time_;

        /// @brief Size of the queue after last push.
        size_t last_queue_size_;
    };

    /// @brief Pointer to a Destination.
    typedef boost::shared_ptr<Destination> DestinationPtr;

    /// @brief Creates a new destination for the given address and TLS context.
    ///
    /// @param address Address of the new destination.
    /// @param port Port of the new destination.
    /// @param tls_context TLS context for the new destination.
    ///
    /// @return Pointer to the newly created destination.
    /// @note Must be called from within a thread-safe context.
    DestinationPtr addDestination(const IOAddress& address,
                                  const uint16_t port,
                                  const TlsContextPtr& tls_context) {
        DestinationDescriptor desc(address, port, tls_context);
        DestinationPtr destination(new Destination(address, port, tls_context,
                                                   max_addr_connections_));
        destinations_[desc] = destination;
        return (destination);
    }

    /// @brief Fetches a destination by address and TLS context.
    ///
    /// @param address Address of the destination desired.
    /// @param port Port of the destination desired.
    /// @param tls_context TLS context for the destination desired.
    ///
    /// @return pointer the desired destination, empty pointer
    /// if the destination does not exist.
    /// @note Must be called from within a thread-safe context.
    DestinationPtr findDestination(const IOAddress& address,
                                   const uint16_t port,
                                   const TlsContextPtr& tls_context) const {
        DestinationDescriptor desc(address, port, tls_context);
        auto it = destinations_.find(desc);
        if (it != destinations_.end()) {
            return (it->second);
        }

        return (DestinationPtr());
    }

    /// @brief Removes a destination by address and TLS context.
    ///
    /// Closes all of the destination's connections and
    /// discards all of its queued requests while removing
    /// the destination from the list of known destinations.
    ///
    /// @note not used yet.
    ///
    /// @param address Address of the destination to be removed.
    /// @param port Port of the destination desired.
    /// @param tls_context TLS context for the destination to be removed.
    /// @note Must be called from within a thread-safe context.
    void removeDestination(const IOAddress& address,
                           const uint16_t port,
                           const TlsContextPtr& tls_context) {
        DestinationDescriptor desc(address, port, tls_context);
        auto it = destinations_.find(desc);
        if (it != destinations_.end()) {
            it->second->closeAllConnections();
            destinations_.erase(it);
        }
    }

    /// @brief A pointer to the IOService that drives socket IO.
    IOServicePtr io_service_;

    /// @brief Map of Destinations by address and TLS context.
    std::map<DestinationDescriptor, DestinationPtr> destinations_;

    /// @brief Mutex to protect the internal state.
    std::mutex pool_mutex_;

    /// @brief Maximum number of connections per address and TLS context.
    size_t max_addr_connections_;
};

Connection::Connection(const IOServicePtr& io_service,
                       const TlsContextPtr& tls_context,
                       const ConnectionPoolPtr& conn_pool,
                       const IOAddress& address,
                       const uint16_t port)
    : io_service_(io_service), conn_pool_(conn_pool), address_(address),
      port_(port), tls_context_(tls_context), tcp_socket_(), tls_socket_(),
      timer_(new IntervalTimer(io_service)), current_request_(),
      current_response_(), current_persistent_(false),
      current_response_complete_(false), current_complete_check_(),
      current_callback_(), buf_(), input_buf_(), current_transid_(0),
      close_callback_(), started_(false), need_handshake_(false),
      closed_(false) {
    if (!tls_context) {
        tcp_socket_.reset(new asiolink::TCPSocket<SocketCallback>(io_service));
    } else {
        tls_socket_.reset(new asiolink::TLSSocket<SocketCallback>(io_service,
                                                                  tls_context));
        need_handshake_ = true;
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
    current_persistent_ = false;
    current_response_complete_ = false;
    current_callback_ = TcpClient::RequestHandler();
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
            LOG_ERROR(tcp_logger, TCP_CLIENT_CONNECTION_CLOSE_CALLBACK_FAILED);
        }
    }

    if (clear) {
        close_callback_ = TcpClient::CloseHandler();
    }
}

void
Connection::isClosedByPeer() {
    // This method applies only to idle connections.
    if (started_ || closed_) {
        return;
    }
    // This code was guarded by a lock so keep this.
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        isClosedByPeerInternal();
    } else {
        isClosedByPeerInternal();
    }
}

void
Connection::isClosedByPeerInternal() {
    // If the socket is open we check if it is possible to transmit
    // the data over this socket by reading from it with message
    // peeking. If the socket is not usable, we close it and then
    // re-open it. There is a narrow window of time between checking
    // the socket usability and actually transmitting the data over
    // this socket, when the peer may close the connection. In this
    // case we'll need to re-transmit but we don't handle it here.
    if (tcp_socket_) {
        if (tcp_socket_->getASIOSocket().is_open() &&
            !tcp_socket_->isUsable()) {
            closeCallback();
            closed_ = true;
            tcp_socket_->close();
        }
    } else if (tls_socket_) {
        if (tls_socket_->getASIOSocket().is_open() &&
            !tls_socket_->isUsable()) {
            closeCallback();
            closed_ = true;
            tls_socket_->close();
        }
    } else {
        isc_throw(Unexpected, "internal error: can't find the sending socket");
    }
}

void
Connection::doTransaction(const WireDataPtr& request,
                          const WireDataPtr& response,
                          const bool persistent,
                          const long request_timeout,
                          const TcpClient::CompleteCheck& complete_check,
                          const TcpClient::RequestHandler& callback,
                          const TcpClient::ConnectHandler& connect_callback,
                          const TcpClient::HandshakeHandler& handshake_callback,
                          const TcpClient::CloseHandler& close_callback) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        doTransactionInternal(request, response, persistent, request_timeout,
                              complete_check, callback, connect_callback,
                              handshake_callback, close_callback);
    } else {
        doTransactionInternal(request, response, persistent, request_timeout,
                              complete_check, callback, connect_callback,
                              handshake_callback, close_callback);
    }
}

void
Connection::doTransactionInternal(const WireDataPtr& request,
                                  const WireDataPtr& response,
                                  const bool persistent,
                                  const long request_timeout,
                                  const TcpClient::CompleteCheck& complete_check,
                                  const TcpClient::RequestHandler& callback,
                                  const TcpClient::ConnectHandler& connect_callback,
                                  const TcpClient::HandshakeHandler& handshake_callback,
                                  const TcpClient::CloseHandler& close_callback) {
    try {
        started_ = true;
        current_request_ = request;
        current_response_ = response;
        current_persistent_ = persistent;
        current_complete_check_ = complete_check;
        current_callback_ = callback;
        handshake_callback_ = handshake_callback;
        close_callback_ = close_callback;

        // Starting new transaction. Generate new transaction id.
        ++current_transid_;

        buf_ = *request;

        size_t to_dump = request->size();
        bool truncated = false;
        if (to_dump > 100) {
            to_dump = 100;
            truncated = true;
        }
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  TCP_CLIENT_REQUEST_SEND)
            .arg(str::dumpAsHex(request->data(), to_dump) +
                 (truncated ? "..." : ""))
            .arg(address_.toText())
            .arg(port_);

        // Setup request timer.
        scheduleTimer(request_timeout);

        /// @todo We're getting a hostname but in fact it is expected to be an IP address.
        /// We should extend the TCPEndpoint to also accept names. Currently, it will fall
        /// over for names.
        TCPEndpoint endpoint(address_, port_);
        SocketCallback socket_cb(std::bind(&Connection::connectCallback,
                                           shared_from_this(),
                                           connect_callback,
                                           current_transid_,
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
        isc_throw(Unexpected, "internal error: can't find a socket to open");

    } catch (const std::exception& ex) {
        // Re-throw with the expected exception type.
        isc_throw(TcpClientError, ex.what());
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

    closed_ = true;
    timer_->cancel();
    if (tcp_socket_) {
        tcp_socket_->close();
    }
    if (tls_socket_) {
        tls_socket_->close();
    }

    resetState();
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
        LOG_WARN(tcp_logger, TCP_CLIENT_PREMATURE_CONNECTION_TIMEOUT_OCCURRED)
                .arg(isTransactionOngoing())
                .arg(transid)
                .arg(current_transid_);
        return (true);
    }

    return (false);
}

void
Connection::terminate(const boost::system::error_code& ec,
                      const std::string& error_msg) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        terminateInternal(ec, error_msg);
    } else {
        terminateInternal(ec, error_msg);
    }
}

void
Connection::terminateInternal(const boost::system::error_code& ec,
                              const std::string& error_msg) {
    WireDataPtr response;
    if (isTransactionOngoing()) {

        timer_->cancel();
        if (tcp_socket_) {
            tcp_socket_->cancel();
        }
        if (tls_socket_) {
            tls_socket_->cancel();
        }

        if (!ec && current_response_complete_) {
            response = current_response_;

            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                      TCP_CLIENT_SERVER_RESPONSE_RECEIVED)
                .arg(address_.toText())
                .arg(port_);
        } else {
            std::string err = error_msg.empty() ? ec.message() : error_msg;

            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                      TCP_CLIENT_BAD_SERVER_RESPONSE_RECEIVED)
                .arg(address_.toText())
                .arg(port_)
                .arg(err);

            // Only log the details if we have received anything.
            if (!error_msg.empty() && !current_response_->empty()) {
                size_t to_dump = current_response_->size();
                bool truncated = false;
                if (to_dump > 100) {
                    to_dump = 100;
                    truncated = true;
                }
                LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC_DATA,
                          TCP_CLIENT_BAD_SERVER_RESPONSE_RECEIVED_DETAILS)
                    .arg(address_.toText())
                    .arg(port_)
                    .arg(str::dumpAsHex(current_response_->data(), to_dump) +
                         (truncated ? "..." : ""));
            }
        }

        try {
            // The callback should take care of its own exceptions but one
            // never knows.
            if (MultiThreadingMgr::instance().getMode()) {
                UnlockGuard<std::mutex> lock(mutex_);
                current_callback_(ec, response, error_msg);
            } else {
                current_callback_(ec, response, error_msg);
            }
        } catch (...) {
        }

        // If we're not requesting connection persistence or the
        // connection has timed out, we should close the socket.
        if (!closed_ &&
            (!current_persistent_ || (ec == boost::asio::error::timed_out))) {
            closeInternal();
        }

        resetState();
    }

    // Check if there are any requests queued for this destination and start
    // another transaction if there is at least one.
    ConnectionPoolPtr conn_pool = conn_pool_.lock();
    if (conn_pool) {
        conn_pool->postProcessNextRequest(address_, port_, tls_context_);
    }
}

void
Connection::scheduleTimer(const long request_timeout) {
    if (request_timeout > 0) {
        timer_->setup(std::bind(&Connection::timerCallback, this), request_timeout,
                      IntervalTimer::ONE_SHOT);
    }
}

void
Connection::doHandshake(const uint64_t transid) {
    // Skip the handshake if it is not needed.
    if (!need_handshake_) {
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
Connection::connectCallback(TcpClient::ConnectHandler connect_callback,
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
Connection::handshakeCallback(TcpClient::ConnectHandler handshake_callback,
                              const uint64_t transid,
                              const boost::system::error_code& ec) {
    need_handshake_ = false;
    if (checkPrematureTimeout(transid)) {
        return;
    }

    // Run user defined handshake callback if specified.
    if (handshake_callback) {
        // If the user defined callback indicates that the connection
        // should not be continued.
        if (tls_socket_) {
            if (!handshake_callback(ec, tls_socket_->getNative())) {
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
    scheduleTimer(timer_->getInterval());

    // If any data have been sent, remove it from the buffer and only leave the
    // portion that still has to be sent.
    if (length > 0) {
        if (length >= buf_.size()) {
            buf_.clear();
        } else {
            buf_.erase(buf_.begin(), buf_.begin() + length);
        }
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
        }
        if ((ec.value() != boost::asio::error::try_again) &&
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
    scheduleTimer(timer_->getInterval());

    if (runCompleteCheck(ec, length)) {
        doReceive(transid);
    }
}

bool
Connection::runCompleteCheck(const boost::system::error_code& ec, size_t length) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (runCompleteCheckInternal(ec, length));
    } else {
        return (runCompleteCheckInternal(ec, length));
    }
}

bool
Connection::runCompleteCheckInternal(const boost::system::error_code& ec,
                                     size_t length) {
    // If we have received any data, let's store it.
    if (length != 0) {
        current_response_->insert(current_response_->end(),
                                  input_buf_.begin(),
                                  input_buf_.begin() + length);
    }

    // If data is still needed, let's schedule another receive.
    int status = -1;
    std::string err = "";
    if (current_complete_check_) {
        status = current_complete_check_(current_response_, err);
    } else {
        err = "Internal error: no completion checker?";
    }
    if (status == 0) {
        return (true);
    } else if (status > 0) {
        // No more data needed.
        current_response_complete_ = true;
        terminateInternal(ec);
    } else {
        // Error case.
        terminateInternal(ec, err);
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
namespace tcp {

/// @brief TcpClient implementation.
class TcpClientImpl {
public:
    /// @brief Constructor.
    ///
    /// If single-threading:
    /// - Creates the connection pool passing in the caller's IOService
    /// and a maximum number of connections per address value of 1.
    /// If multi-threading:
    /// - Creates a private IOService
    /// - Creates a thread pool with the thread_pool_size threads
    /// - Creates the connection pool passing the private IOService
    /// and the thread_pool_size as the maximum number of connections
    /// per URL.
    ///
    /// @param io_service IOService that will drive connection IO in single
    /// threaded mode.  (Currently ignored in multi-threaded mode)
    /// @param thread_pool_size maximum number of concurrent threads
    /// Internally this also sets the maximum number of concurrent connections
    /// per address.
    /// @param defer_thread_start When true, starting of the pool threads is
    /// deferred until a subsequent call to @ref start(). In this case the
    /// pool's operational state after construction is STOPPED.  Otherwise,
    /// the thread pool threads will be created and started, with the
    /// operational state being RUNNING.  Applicable only when thread-pool size
    /// is greater than zero.
    TcpClientImpl(const IOServicePtr& io_service, size_t thread_pool_size = 0,
                   bool defer_thread_start = false)
        : thread_pool_size_(thread_pool_size), thread_pool_() {
        if (thread_pool_size_ > 0) {
            // Create our own private IOService.
            thread_io_service_.reset(new IOService());

            // Create the connection pool. Note that we use the thread_pool_size
            // as the maximum connections per address.
            conn_pool_.reset(new ConnectionPool(thread_io_service_, thread_pool_size_));

            // Create the thread pool.
            thread_pool_.reset(new IoServiceThreadPool(thread_io_service_, thread_pool_size_,
                                                       defer_thread_start));

            LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC,
                      TCP_CLIENT_MT_STARTED)
                .arg(thread_pool_size_);
        } else {
            // Single-threaded mode: use the caller's IOService,
            // one connection per address.
            conn_pool_.reset(new ConnectionPool(io_service, 1));
        }
    }

    /// @brief Destructor
    ///
    /// Calls stop().
    ~TcpClientImpl() {
        stop();
    }

    /// @brief Check if the current thread can perform thread pool state
    /// transition.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPermissions() {
        if (thread_pool_) {
            thread_pool_->checkPausePermissions();
        }
    }

    /// @brief Starts running the client's thread pool, if multi-threaded.
    void start() {
        if (thread_pool_) {
            thread_pool_->run();
        }
    }

    /// @brief Close all connections, and if multi-threaded, stops the client's
    /// thread pool.
    void stop() {
        // Close all the connections.
        conn_pool_->closeAll();

        // Stop the thread pool.
        if (thread_pool_) {
            thread_pool_->stop();
        }

        if (thread_io_service_) {
            thread_io_service_->stopAndPoll();
            thread_io_service_->stop();
        }
    }

    /// @brief Pauses the client's thread pool.
    ///
    /// Suspends thread pool event processing.
    /// @throw InvalidOperation if the thread pool does not exist.
    void pause() {
        if (!thread_pool_) {
            isc_throw(InvalidOperation, "TcpClient::pause - no thread pool");
        }

        // Pause the thread pool.
        thread_pool_->pause();
    }

    /// @brief Resumes running the client's thread pool.
    ///
    /// Resumes thread pool event processing.
    /// @throw InvalidOperation if the thread pool does not exist.
    void resume() {
        if (!thread_pool_) {
            isc_throw(InvalidOperation, "TcpClient::resume - no thread pool");
        }

        // Resume running the thread pool.
        thread_pool_->run();
    }

    /// @brief Indicates if the thread pool is running.
    ///
    /// @return True if the thread pool exists and it is in the RUNNING state,
    /// false otherwise.
    bool isRunning() {
        if (thread_pool_) {
            return (thread_pool_->isRunning());
        }

        return (false);
    }

    /// @brief Indicates if the thread pool is stopped.
    ///
    /// @return True if the thread pool exists and it is in the STOPPED state,
    /// false otherwise.
    bool isStopped() {
        if (thread_pool_) {
            return (thread_pool_->isStopped());
        }

        return (false);
    }

    /// @brief Indicates if the thread pool is paused.
    ///
    /// @return True if the thread pool exists and it is in the PAUSED state,
    /// false otherwise.
    bool isPaused() {
        if (thread_pool_) {
            return (thread_pool_->isPaused());
        }

        return (false);
    }

    /// @brief Fetches the internal IOService used in multi-threaded mode.
    ///
    /// @return A pointer to the IOService, or an empty pointer when
    /// in single-threaded mode.
    asiolink::IOServicePtr getThreadIOService() {
        return (thread_io_service_);
    };

    /// @brief Fetches the maximum size of the thread pool.
    ///
    /// @return the maximum size of the thread pool.
    uint16_t getThreadPoolSize() {
        return (thread_pool_size_);
    }

    /// @brief Fetches the number of threads in the pool.
    ///
    /// @return the number of running threads.
    uint16_t getThreadCount() {
        if (!thread_pool_) {
            return (0);
        }
        return (thread_pool_->getThreadCount());
    }

    /// @brief Holds a pointer to the connection pool.
    ConnectionPoolPtr conn_pool_;

private:

    /// @brief Maxim number of threads in the thread pool.
    size_t thread_pool_size_;

    /// @brief Pointer to private IOService used in multi-threaded mode.
    asiolink::IOServicePtr thread_io_service_;

    /// @brief Pool of threads used to service connections in multi-threaded
    /// mode.
    IoServiceThreadPoolPtr thread_pool_;
};

TcpClient::TcpClient(const IOServicePtr& io_service, bool multi_threading_enabled,
                       size_t thread_pool_size, bool defer_thread_start) {
    if (!multi_threading_enabled && thread_pool_size) {
        isc_throw(InvalidOperation,
                  "TcpClient thread_pool_size must be zero "
                  "when Kea core multi-threading is disabled");
    }

    impl_.reset(new TcpClientImpl(io_service, thread_pool_size,
                                   defer_thread_start));
}

TcpClient::~TcpClient() {
    impl_->stop();
}

void
TcpClient::asyncSendRequest(const IOAddress& address,
                            const uint16_t port,
                            const TlsContextPtr& tls_context,
                            const WireDataPtr& request,
                            const WireDataPtr& response,
                            const bool persistent,
                            const TcpClient::CompleteCheck& complete_check,
                            const TcpClient::RequestHandler& request_callback,
                            const TcpClient::RequestTimeout& request_timeout,
                            const TcpClient::ConnectHandler& connect_callback,
                            const TcpClient::HandshakeHandler& handshake_callback,
                            const TcpClient::CloseHandler& close_callback) {
    if (!request) {
        isc_throw(TcpClientError, "TCP request must not be null");
    }

    if (!response) {
        isc_throw(TcpClientError, "TCP response must not be null");
    }

    if (!complete_check) {
        isc_throw(TcpClientError, "TCP response completion checker must not be null");
    }

    if (!request_callback) {
        isc_throw(TcpClientError, "callback for TCP transaction must not be null");
    }

    impl_->conn_pool_->queueRequest(address, port, tls_context,
                                    request, response, persistent,
                                    request_timeout.value_,
                                    complete_check,
                                    request_callback, connect_callback,
                                    handshake_callback, close_callback);
}

void
TcpClient::closeIfOutOfBand(int socket_fd) {
    return (impl_->conn_pool_->closeIfOutOfBand(socket_fd));
}

void
TcpClient::start() {
    impl_->start();
}

void
TcpClient::checkPermissions() {
    impl_->checkPermissions();
}

void
TcpClient::pause() {
    impl_->pause();
}

void
TcpClient::resume() {
    impl_->resume();
}

void
TcpClient::stop() {
    impl_->stop();
}

const IOServicePtr
TcpClient::getThreadIOService() const {
    return (impl_->getThreadIOService());
}

uint16_t
TcpClient::getThreadPoolSize() const {
    return (impl_->getThreadPoolSize());
}

uint16_t
TcpClient::getThreadCount() const {
    return (impl_->getThreadCount());
}

bool
TcpClient::isRunning() {
    return (impl_->isRunning());
}

bool
TcpClient::isStopped() {
    return (impl_->isStopped());
}

bool
TcpClient::isPaused() {
    return (impl_->isPaused());
}

} // end of namespace isc::tcp
} // end of namespace isc
