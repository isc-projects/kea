// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the HTTP client.
    explicit HttpClient(asiolink::IOService& io_service);

    /// @brief Queues new asynchronous HTTP request.
    ///
    /// The client creates one connection for the specified URL. If the connection
    /// with the particular destination already exists, it will be re-used for the
    /// new transaction scheduled with this call. If another transaction is still
    /// in progress, the new transaction is queued. The queued transactions are
    /// started in the FIFO order one after another. If the connection is idle or
    /// the connection doesn't exist, the new transaction is started immediatelly.
    ///
    /// The existing connection is tested before it is used for the new transaction
    /// by attempting to read (with message peeking) from the open TCP socket. If the
    /// read attempt is successful, the client will transmit the HTTP request to
    /// the server using this connection. It is possible that the server closes the
    /// connection between the connection test and sending the request. In such case,
    /// an error will be returned and the caller will need to try re-sending the
    /// request.
    ///
    /// If the connection test fails, the client will close the socket and reconnect
    /// to the server prior to sending the request.
    ///
    /// Pointers to the request and response objects are provided as arguments of
    /// this method. These pointers should have appropriate types derived from the
    /// @ref HttpRequest and @ref HttpResponse classes. For example, if the request
    /// has content type "application/json", a pointer to the
    /// @ref HttpResponseJson should be passed. In this case, the response type
    /// should be @ref HttpResponseJson. These types are used to validate both the
    /// request provided by the caller and the response received from the server.
    ///
    /// The callback function provided by the caller is invoked when the transaction
    /// terminates, i.e. when the server has responded or when an error occured. The
    /// callback is expected to be exception safe, but the client internally guards
    /// against exceptions thrown by the callback.
    ///
    /// The first argument of the callback indicates an IO error during communication
    /// with the server. If the communication is successful the error code of 0 is
    /// returned. However, in this case it is still possible that the transaction is
    /// unsuccessful due to HTTP response parsing error, e.g. invalid content type,
    /// malformed response etc. Such errors are indicated via third argument.
    ///
    /// If message parsing was successful the second argument of the callback contains
    /// a pointer to the parsed response (the same pointer as provided by the caller
    /// as the argument). If parsing was unsuccessful, the null pointer is returned.
    ///
    /// The default timeout for the transaction is set to 10 seconds (10 000 ms). This
    /// variant of the method doesn't allow for specifying a custom timeout. If the
    /// timeout occurs, the callback is invoked with the error code of
    /// @c boost::asio::error::timed_out.
    ///
    /// @param url URL where the request should be send.
    /// @param request Pointer to the object holding a request.
    /// @param response Pointer to the object where response should be stored.
    /// @param callback Pointer to the user callback function.
    ///
    /// @throw HttpClientError If invalid arguments were provided.
    void asyncSendRequest(const Url& url,
                          const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const RequestHandler& callback);

    /// @brief Queues new asynchronous HTTP request with timeout.
    ///
    /// @param url URL where the request should be send.
    /// @param request Pointer to the object holding a request.
    /// @param response Pointer to the object where response should be stored.
    /// @param request_timeout Timeout for the transaction in milliseconds.
    /// @param callback Pointer to the user callback function.
    ///
    /// @throw HttpClientError If invalid arguments were provided.
    void asyncSendRequest(const Url& url,
                          const HttpRequestPtr& request,
                          const HttpResponsePtr& response,
                          const RequestTimeout& request_timeout,
                          const RequestHandler& callback);

    /// @brief Closes all connections.
    void stop();

private:

    /// @brief Pointer to the HTTP client implementation.
    boost::shared_ptr<HttpClientImpl> impl_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
