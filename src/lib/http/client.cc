// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tcp_socket.h>
#include <http/client.h>
#include <http/response_json.h>
#include <http/response_parser.h>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>
#include <array>
#include <map>
#include <queue>

#include <iostream>

using namespace isc;
using namespace isc::asiolink;
using namespace http;

namespace {

/// @brief TCP socket callback function type.
typedef boost::function<void(boost::system::error_code ec, size_t length)>
SocketCallbackFunction;

/// @brief Socket callback class required by the TCPSocket API.
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
    //// @param socket_callback Pointer to a callback function.
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
/// The communication over the TCP socket is asynchronous. The caller is notified
/// about the completion of the transaction via a callback that the caller supplies
/// when initiating the transaction.
class Connection : public boost::enable_shared_from_this<Connection> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used for the connection.
    /// @param conn_pool Back pointer to the connection pool to which this connection
    /// belongs.
    /// @param url URL associated with this connection.
    explicit Connection(IOService& io_service, const ConnectionPoolPtr& conn_pool,
                        const Url& url);

    /// @brief Destructor.
    ~Connection();

    /// @brief Starts new asynchronous transaction (HTTP request and response).
    ///
    /// This method expects that all pointers provided as argument are non-null.
    ///
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response is stored. The
    /// caller should create a response object of the type which matches the content
    /// type expected by the caller, e.g. HttpResponseJson when JSON content type
    /// is expected to be received.
    /// @param request_timeout Request timeout in milliseconds.
    /// @param callback Pointer to the callback function to be invoked when the
    /// transaction completes.
    void doTransaction(const HttpRequestPtr& request, const HttpResponsePtr& response,
                       const long request_timeout, const HttpClient::RequestHandler& callback);

    /// @brief Closes the socket and cancels the request timer.
    void close();

    /// @brief Checks if a transaction has been initiated over this connection.
    ///
    /// @return true if transaction has been initiated, false otherwise.
    bool isTransactionOngoing() const;

private:

    /// @brief Resets the state of the object.
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

    /// @brief Asynchronously sends data over the socket.
    ///
    /// The data sent over the socket are stored in the @c buf_.
    void doSend();

    /// @brief Asynchronously receives data over the socket.
    ///
    /// The data received over the socket are store into the @c input_buf_.
    void doReceive();

    /// @brief Local callback invoked when the connection is established.
    ///
    /// If the connection is successfully established, this callback will start
    /// to asynchronously send the request over the socket.
    ///
    /// @param request_timeout Request timeout specified for this transaction.
    /// @param ec Error code being a result of the connection attempt.
    void connectCallback(const long request_timeout,
                         const boost::system::error_code& ec);

    /// @brief Local callback invoked when an attempt to send a portion of data
    /// over the socket has ended.
    ///
    /// The portion of data that has been sent is removed from the buffer. If all
    /// data from the buffer were sent, the callback will start to asynchronously
    /// receive a response from the server.
    ///
    /// @param ec Error code being a result of sending the data.
    /// @param length Number of bytes sent.
    void sendCallback(const boost::system::error_code& ec, size_t length);

    /// @brief Local callback invoked when an attempt to receive a portion of data
    /// over the socket has ended.
    ///
    /// @param ec Error code being a result of receiving the data.
    /// @param length Number of bytes received.
    void receiveCallback(const boost::system::error_code& ec, size_t length);

    /// @brief Local callback invoked when request timeout occurs.
    void timerCallback();

    /// @brief Pointer to the connection pool owning this connection.
    ///
    /// This is a weak pointer to avoid circular dependency between the
    /// Connection and ConnectionPool.
    boost::weak_ptr<ConnectionPool> conn_pool_;

    /// @brief URL for this connection.
    Url url_;

    /// @brief Socket to be used for this connection.
    TCPSocket<SocketCallback> socket_;

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
    std::array<char, 4096> input_buf_;
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
        : io_service_(io_service), conns_(), queue_() {
    }

    /// @brief Destructor.
    ///
    /// Closes all connections.
    ~ConnectionPool() {
        closeAll();
    }

    /// @brief Returns next queued request for the given URL.
    ///
    /// @param url URL for which next queued request should be retrieved.
    /// @param [out] request Pointer to the queued request.
    /// @param [out] response Pointer to the object into which response should
    /// be stored.
    /// @param request_timeout Requested timeout for the transaction.
    /// @param callback Pointer to the user callback for this request.
    ///
    /// @return true if the request for the given URL has been retrieved,
    /// false if there are no more requests queued for this URL.
    bool getNextRequest(const Url& url,
                        HttpRequestPtr& request,
                        HttpResponsePtr& response,
                        long& request_timeout,
                        HttpClient::RequestHandler& callback) {
        // Check if there is a queue for this URL. If there is no queue, there
        // is no request queued either.
        auto it = queue_.find(url);
        if (it != queue_.end()) {
            // If the queue is non empty, we take the oldest request.
            if (!it->second.empty()) {
                RequestDescriptor desc = it->second.front();
                it->second.pop();
                request = desc.request_;
                response = desc.response_;
                request_timeout = desc.request_timeout_,
                callback = desc.callback_;
                return (true);
            }
        }

        return (false);
    }

    /// @brief Queue next request for sending to the server.
    ///
    /// A new transaction is started immediatelly, if there is no other request
    /// in progress for the given URL. Otherwise, the request is queued.
    ///
    /// @param url Destination where the request should be sent.
    /// @param request Pointer to the request to be sent to the server.
    /// @param response Pointer to the object into which the response should be
    /// stored.
    /// @param request_timeout Requested timeout for the transaction in
    /// milliseconds.
    /// @param callback Pointer to the user callback to be invoked when the
    /// transaction ends.
    void queueRequest(const Url& url,
                      const HttpRequestPtr& request,
                      const HttpResponsePtr& response,
                      const long request_timeout,
                      const HttpClient::RequestHandler& callback) {
        auto it = conns_.find(url);
        if (it != conns_.end()) {
            ConnectionPtr conn = it->second;
            // There is a connection for this URL already. Check if it is idle.
            if (conn->isTransactionOngoing()) {
                // Connection is busy, so let's queue the request.
                queue_[url].push(RequestDescriptor(request, response,
                                                   request_timeout,
                                                   callback));

            } else {
                // Connection is idle, so we can start the transaction.
                conn->doTransaction(request, response, request_timeout,
                                    callback);
            }

        } else {
            // There is no connection with this destination yet. Let's create
            // it and start the transaction.
            ConnectionPtr conn(new Connection(io_service_, shared_from_this(),
                                              url));
            conn->doTransaction(request, response, request_timeout, callback);
            conns_[url] = conn;
        }
    }

    /// @brief Closes connection and removes associated information from the
    /// connection pool.
    ///
    /// @param url URL for which connection shuld be closed.
    void closeConnection(const Url& url) {
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
    void closeAll() {
        for (auto conns_it = conns_.begin(); conns_it != conns_.end();
             ++conns_it) {
            conns_it->second->close();
        }

        conns_.clear();
        queue_.clear();
    }

private:

    /// @brief Holds reference to the IO service.
    IOService& io_service_;

    /// @brief Holds mapping of URLs to connections.
    std::map<Url, ConnectionPtr> conns_;

    /// @brief Request descriptor holds parameters associated with the
    /// particular request.
    struct RequestDescriptor {
        /// @brief Constructor.
        ///
        /// @param request Pointer to the request to be sent.
        /// @param response Pointer to the object into which the response will
        /// be stored.
        /// @param request_timeout Requested timeout for the transaction.
        /// @param callback Pointer to the user callback.
        RequestDescriptor(const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const long request_timeout,
                          const HttpClient::RequestHandler& callback)
            : request_(request), response_(response),
              request_timeout_(request_timeout),
              callback_(callback) {
        }

        /// @brief Holds pointer to the request.
        HttpRequestPtr request_;
        /// @brief Holds pointer to the response.
        HttpResponsePtr response_;
        /// @brief Holds requested timeout value.
        long request_timeout_;
        /// @brief Holds pointer to the user callback.
        HttpClient::RequestHandler callback_;
    };

    /// @brief Holds the queue of requests for different URLs.
    std::map<Url, std::queue<RequestDescriptor> > queue_;
};

Connection::Connection(IOService& io_service,
                       const ConnectionPoolPtr& conn_pool,
                       const Url& url)
    : conn_pool_(conn_pool), url_(url), socket_(io_service), timer_(io_service),
      current_request_(), current_response_(), parser_(), current_callback_(),
      buf_(), input_buf_() {
}

Connection::~Connection() {
    close();
}

void
Connection::resetState() {
    current_request_.reset();
    current_response_.reset();
    parser_.reset();
    current_callback_ = HttpClient::RequestHandler();
}

void
Connection::doTransaction(const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const long request_timeout,
                          const HttpClient::RequestHandler& callback) {
    try {
        current_request_ = request;
        current_response_ = response;
        parser_.reset(new HttpResponseParser(*current_response_));
        parser_->initModel();
        current_callback_ = callback;

        buf_ = request->toString();

        // If the socket is open we check if it is possible to transmit the data
        // over this socket by reading from it with message peeking. If the socket
        // is not usable, we close it and then re-open it. There is a narrow window of
        // time between checking the socket usability and actually transmitting the
        // data over this socket, when the peer may close the connection. In this
        // case we'll need to re-transmit but we don't handle it here.
        if (socket_.getASIOSocket().is_open() && !socket_.isUsable()) {
            socket_.close();
        }

        /// @todo We're getting a hostname but in fact it is expected to be an IP address.
        /// We should extend the TCPEndpoint to also accept names. Currently, it will fall
        /// over for names.
        TCPEndpoint endpoint(url_.getHostname(), static_cast<unsigned short>(url_.getPort()));
        SocketCallback socket_cb(boost::bind(&Connection::connectCallback, shared_from_this(),
                                             request_timeout, _1));

        // Establish new connection or use existing connection.
        socket_.open(&endpoint, socket_cb);

    } catch (const std::exception& ex) {
        // Re-throw with the expected exception type.
        isc_throw(HttpClientError, ex.what());
    }
}

void
Connection::close() {
    timer_.cancel();
    socket_.close();
    resetState();
}

bool
Connection::isTransactionOngoing() const {
    return (static_cast<bool>(current_request_));
}

void
Connection::terminate(const boost::system::error_code& ec,
                      const std::string& parsing_error) {
    timer_.cancel();
    socket_.cancel();

    HttpResponsePtr response;

    if (!ec && current_response_->isFinalized()) {
        response = current_response_;
    }

    try {
        // The callback should take care of its own exceptions but one
        // never knows.
        current_callback_(ec, response, parsing_error);

    } catch (...) {
    }

    // If we're not requesting connection persistence, we should close the socket.
    // We're going to reconnect for the next transaction.
    if (!current_request_->isPersistent()) {
        close();
    }

    resetState();

    // Check if there are any requests queued for this connection and start
    // another transaction if there is at least one.
    HttpRequestPtr request;
    long request_timeout;
    HttpClient::RequestHandler callback;
    ConnectionPoolPtr conn_pool = conn_pool_.lock();
    if (conn_pool && conn_pool->getNextRequest(url_, request, response, request_timeout,
                                               callback)) {
        doTransaction(request, response, request_timeout, callback);
    }
}

void
Connection::doSend() {
    SocketCallback socket_cb(boost::bind(&Connection::sendCallback, shared_from_this(),
                                         _1, _2));
    socket_.asyncSend(&buf_[0], buf_.size(), socket_cb);
}

void
Connection::doReceive() {
    TCPEndpoint endpoint;
    SocketCallback socket_cb(boost::bind(&Connection::receiveCallback, shared_from_this(),
                                         _1, _2));
    socket_.asyncReceive(static_cast<void*>(input_buf_.data()), input_buf_.size(), 0,
                         &endpoint, socket_cb);
}

void
Connection::connectCallback(const long request_timeout, const boost::system::error_code& ec) {
    // In some cases the "in progress" status code may be returned. It doesn't
    // indicate an error. Sending the request over the socket is expected to
    // be successful. Getting such status appears to be highly dependent on
    // the operating system.
    if (ec &&
        (ec.value() != boost::asio::error::in_progress) &&
        (ec.value() != boost::asio::error::already_connected)) {
        terminate(ec);

    } else {
        // Setup request timer.
        timer_.setup(boost::bind(&Connection::timerCallback, this), request_timeout,
                     IntervalTimer::ONE_SHOT);
        // Start sending the request asynchronously.
        doSend();
    }
}

void
Connection::sendCallback(const boost::system::error_code& ec, size_t length) {
    if (ec) {
        // EAGAIN and EWOULDBLOCK don't really indicate an error. The length
        // should be 0 in this case but let's be sure.
        if ((ec.value() == boost::asio::error::would_block) ||
            (ec.value() == boost::asio::error::try_again)) {
            length = 0;

        } else {
            // Any other error should cause the transaction to terminate.
            terminate(ec);
        }
    }

    // If any data have been sent, remove it from the buffer and only leave the
    // portion that still has to be sent.
    if (length > 0) {
        buf_.erase(0, length);
    }

    // If there is no more data to be sent, start receiving a response. Otherwise,
    // continue sending.
    if (buf_.empty()) {
        doReceive();

    } else {
        doSend();
    }
}

void
Connection::receiveCallback(const boost::system::error_code& ec, size_t length) {
    if (ec) {
        // EAGAIN and EWOULDBLOCK don't indicate an error in this case. All
        // other errors should terminate the transaction.
        if ((ec.value() != boost::asio::error::try_again) &&
            (ec.value() != boost::asio::error::would_block)) {
            terminate(ec);

        } else {
            // For EAGAIN and EWOULDBLOCK the length should be 0 anyway, but let's
            // make sure.
            length = 0;
        }
    }

    // If we have received any data, let's feed the parser with it.
    if (length != 0) {
        parser_->postBuffer(static_cast<void*>(input_buf_.data()), length);
        parser_->poll();
    }

    // If the parser still needs data, let's schedule another receive.
    if (parser_->needData()) {
        doReceive();

    } else if (parser_->httpParseOk()) {
        // No more data needed and parsing has been successful so far. Let's
        // try to finalize the response parsing.
        try {
            current_response_->finalize();
            terminate(ec);

        } catch (const std::exception& ex) {
            // If there is an error here, we need to return the error message.
            terminate(ec, ex.what());
        }

    } else {
        // Parsing was unsuccessul. Let's pass the error message held in the
        // parser.
        terminate(ec, parser_->getErrorMessage());
    }
}

void
Connection::timerCallback() {
    // Request timeout occured.
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
HttpClient::asyncSendRequest(const Url& url, const HttpRequestPtr& request,
                             const HttpResponsePtr& response,
                             const HttpClient::RequestHandler& callback,
                             const HttpClient::RequestTimeout& request_timeout) {
    if (!url.isValid()) {
        isc_throw(HttpClientError, "invalid URL specified for the HTTP client");
    }

    if (!request) {
        isc_throw(HttpClientError, "HTTP request must not be null");
    }

    if (!response) {
        isc_throw(HttpClientError, "HTTP response must not be null");
    }

    if (!callback) {
        isc_throw(HttpClientError, "callback for HTTP transaction must not be null");
    }

    impl_->conn_pool_->queueRequest(url, request, response, request_timeout.value_,
                                    callback);
}

void
HttpClient::stop() {
    impl_->conn_pool_->closeAll();
}

} // end of namespace isc::http
} // end of namespace isc
