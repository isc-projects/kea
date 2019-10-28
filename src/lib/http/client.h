// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <http/url.h>
#include <http/request.h>
#include <http/response.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <string>

namespace isc {
namespace http {

/// @brief A generic error raised by the @ref HttpClient class.
class HttpClientError : public Exception {
public:
    HttpClientError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class HttpClientImpl;

/// @brief HTTP client class.
///
/// This class implements an asynchronous HTTP client. The caller can schedule
/// transmission of the HTTP request using @ref HttpClient::asyncSendRequest
/// method. The caller specifies target URL for each request. The caller also
/// specifies a pointer to the @ref HttpRequest or derived class, holding a
/// request that should be transmitted to the destination. Such request must
/// be finalized, i.e. @ref HttpRequest::finalize method must be called prior
/// to sending it. The caller must also provide a pointer to the
/// @ref HttpResponse object or an object derived from it. The type of the
/// response object must match the expected content type to be returned in the
/// server's response. The last argument specified in this call is the pointer
/// to the callback function, which should be launched when the response is
/// received, an error occurs or when a timeout in the transmission is
/// signalled.
///
/// The HTTP client supports multiple simultaneous and persistent connections
/// with different destinations. The client determines if the connection is
/// persistent by looking into the Connection header and HTTP version of the
/// request. If the connection should be persistent the client doesn't
/// close the connection after sending a request and receiving a response from
/// the server. If the client is provided with the request to be sent to the
/// particular destination, but there is an ongoing communication with this
/// destination, e.g. as a result of sending previous request, the new
/// request is queued in the FIFO queue. When the previous request completes,
/// the next request in the queue for the particular URL will be initiated.
///
/// The client tests the persistent connection for usability before sending
/// a request by trying to read from the socket (with message peeking). If
/// the socket is usable the client uses it to transmit the request.
///
/// This classes exposes the underlying TCP socket's descriptor for each
/// connection via connect and close callbacks.  This is done to permit the
/// sockets to be monitored for IO readiness by external code that's something
/// other than boost::asio (e.g.select() or epoll()), and would thus otherwise
/// starve the client's IOService and cause a backlog of ready event handlers.
///
/// All errors are reported to the caller via the callback function supplied
/// to the @ref HttpClient::asyncSendRequest. The IO errors are communicated
/// via the @c boost::system::error code value. The response parsing errors
/// are returned via the 3rd parameter of the callback.
class HttpClient {
public:

    /// @brief HTTP request/response timeout value.
    struct RequestTimeout {
        /// @brief Constructor.
        ///
        /// @param value Reuqest/response timeout value in milliseconds.
        explicit RequestTimeout(long value)
            : value_(value) {
        }
        long value_; ///< Timeout value specified.
    };

    /// @brief Callback type used in call to @ref HttpClient::asyncSendRequest.
    typedef std::function<void(const boost::system::error_code&,
                               const HttpResponsePtr&,
                               const std::string&)> RequestHandler;

    /// @brief Optional handler invoked when client connects to the server.
    ///
    /// Returned boolean value indicates whether the client should continue
    /// connecting to the server (if true) or not (false).
    /// It is passed the IO error code along with the native socket handle of
    /// the connection's TCP socket.  The passed socket descriptor may be used
    /// to monitor the readiness of the events via select() or epoll().
    ///
    /// @note Beware that the IO error code can be set to "in progress"
    /// so a not null error code does not always mean the connect failed.
    typedef std::function<bool(const boost::system::error_code&, const int)> ConnectHandler;

    /// @brief Optional handler invoked when client closes the connection to the server.
    ///
    /// It is passed the native socket handler of the connection's TCP socket.
    typedef std::function<void(const int)> CloseHandler;

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the HTTP client.
    explicit HttpClient(asiolink::IOService& io_service);

    /// @brief Queues new asynchronous HTTP request.
    ///
    /// The client creates one connection for the specified URL. If the
    /// connection with the particular destination already exists, it will be
    /// re-used for the new transaction scheduled with this call. If another
    /// transaction is still in progress, the new transaction is queued. The
    /// queued transactions are started in the FIFO order one after another. If
    /// the connection is idle or the connection doesn't exist, the new
    /// transaction is started immediatelly.
    ///
    /// The existing connection is tested before it is used for the new
    /// transaction by attempting to read (with message peeking) from the open
    /// TCP socket. If the read attempt is successful, the client will transmit
    /// the HTTP request to the server using this connection. It is possible
    /// that the server closes the connection between the connection test and
    /// sending the request. In such case, an error will be returned and the
    /// caller will need to try re-sending the request.
    ///
    /// If the connection test fails, the client will close the socket and
    /// reconnect to the server prior to sending the request.
    ///
    /// Pointers to the request and response objects are provided as arguments
    /// of this method. These pointers should have appropriate types derived
    /// from the @ref HttpRequest and @ref HttpResponse classes. For example,
    /// if the request has content type "application/json", a pointer to the
    /// @ref HttpResponseJson should be passed. In this case, the response type
    /// should be @ref HttpResponseJson. These types are used to validate both
    /// the request provided by the caller and the response received from the
    /// server.
    ///
    /// The callback function provided by the caller is invoked when the
    /// transaction terminates, i.e. when the server has responded or when an
    /// error occured. The callback is expected to be exception safe, but the
    /// client internally guards against exceptions thrown by the callback.
    ///
    /// The first argument of the callback indicates an IO error during
    /// communication with the server. If the communication is successful the
    /// error code of 0 is returned. However, in this case it is still possible
    /// that the transaction is unsuccessful due to HTTP response parsing error,
    /// e.g. invalid content type, malformed response etc. Such errors are
    /// indicated via third argument.
    ///
    /// If message parsing was successful the second argument of the callback
    /// contains a pointer to the parsed response (the same pointer as provided
    ///by the caller as the argument). If parsing was unsuccessful, the null
    /// pointer is returned.
    ///
    /// The default timeout for the transaction is set to 10 seconds
    /// (10 000 ms). If the timeout occurs, the callback is invoked with the
    /// error code of @c boost::asio::error::timed_out.
    /// The timeout covers both the connect and the transaction phases
    /// so when connecting to the server takes too long (e.g. with a
    /// misconfigured firewall) the timeout is triggered. The connect
    /// callback can be used to recognize this condition.
    ///
    /// @param url URL where the request should be send.
    /// @param request Pointer to the object holding a request.
    /// @param response Pointer to the object where response should be stored.
    /// @param request_callback Pointer to the user callback function invoked
    /// when transaction ends.
    /// @param request_timeout Timeout for the transaction in milliseconds.
    /// @param connect_callback Optional callback invoked when the client
    /// connects to the server.
    /// @param close_callback Optional callback invoked when the client
    /// closes the connection to the server.
    ///
    /// @throw HttpClientError If invalid arguments were provided.
    void asyncSendRequest(const Url& url,
                          const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const RequestHandler& request_callback,
                          const RequestTimeout& request_timeout =
                          RequestTimeout(10000),
                          const ConnectHandler& connect_callback =
                          ConnectHandler(),
                          const CloseHandler& close_callback =
                          CloseHandler());

    /// @brief Closes all connections.
    void stop();

    /// @brief Closes a connection if it has an out-of-bandwidth socket event
    ///
    /// If the  client owns a connection using the given socket and that
    /// connection is currently in a transaction the method returns as this
    /// indicates a normal ready event.  If the connection is not in an
    /// ongoing transaction, then the connection is closed.
    ///
    /// This is method is intended to be used to detect and clean up then
    /// sockets that are marked ready outside of transactions. The most comman
    /// case is the other end of the socket being closed.
    ///
    /// @param socket_fd socket descriptor to check
    void closeIfOutOfBandwidth(int socket_fd);

private:

    /// @brief Pointer to the HTTP client implementation.
    boost::shared_ptr<HttpClientImpl> impl_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
