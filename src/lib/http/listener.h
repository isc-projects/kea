// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_LISTENER_H
#define HTTP_LISTENER_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/crypto_tls.h>
#include <exceptions/exceptions.h>
#include <http/response_creator_factory.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>

namespace isc {
namespace http {

/// @brief A generic error raised by the @ref HttpListener class.
class HttpListenerError : public Exception {
public:
    HttpListenerError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief HttpListener implementation.
class HttpListenerImpl;

/// @brief HTTP listener.
///
/// This class is an entry point to the use of HTTP services in Kea.
/// It creates a transport acceptor service on the specified address and
/// port and listens to the incoming HTTP connections. The constructor
/// receives a pointer to the implementation of the
/// @ref HttpResponseCreatorFactory, which is used by the @ref HttpListener
/// to create/retrieve an instance of the @ref HttpResponseCreator when the
/// new HTTP response needs to be generated. The @ref HttpResponseCreator
/// creates an object derived from the @ref HttpResponse class, encapsulating
/// a HTTP response following some specific rules, e.g. having
/// "application/json" content type.
///
/// When the listener is started it creates an instance of a @ref HttpConnection
/// and stores them in the pool of active connections. The @ref HttpConnection
/// is responsible for managing the next connection received and receiving the
/// HTTP request and sending appropriate response. The listener can handle
/// many HTTP connections simultaneously.
///
/// When the @ref HttpListener::stop is invoked, all active connections are
/// closed and the listener stops accepting new connections.
class HttpListener {
public:

    /// @brief HTTP request timeout value.
    struct RequestTimeout {
        /// @brief Constructor.
        ///
        /// @param value Request timeout value in milliseconds.
        explicit RequestTimeout(long value)
            : value_(value) {
        }
        long value_; ///< Request timeout value specified.
    };

    /// @brief Idle connection timeout.
    struct IdleTimeout {
        /// @brief Constructor.
        ///
        /// @param value Connection idle timeout value in milliseconds.
        explicit IdleTimeout(long value)
            : value_(value) {
        }
        long value_; ///< Connection idle timeout value specified.
    };

    /// @brief Constructor.
    ///
    /// This constructor creates new server endpoint using the specified IP
    /// address and port. It also validates other specified parameters.
    ///
    /// This constructor does not start accepting new connections! To start
    /// accepting connections run @ref HttpListener::start.
    ///
    /// @param io_service IO service to be used by the listener.
    /// @param server_address Address on which the HTTP service should run.
    /// @param server_port Port number on which the HTTP service should run.
    /// @param tls_context TLS context.
    /// @param creator_factory Pointer to the caller-defined
    /// @ref HttpResponseCreatorFactory derivation which should be used to
    /// create @ref HttpResponseCreator instances.
    /// @param request_timeout Timeout after which the HTTP Request Timeout
    /// is generated.
    /// @param idle_timeout Timeout after which an idle persistent HTTP
    /// connection is closed by the server.
    ///
    /// @throw HttpListenerError when any of the specified parameters is
    /// invalid.
    HttpListener(asiolink::IOService& io_service,
                 const asiolink::IOAddress& server_address,
                 const unsigned short server_port,
                 const asiolink::TlsContextPtr& tls_context,
                 const HttpResponseCreatorFactoryPtr& creator_factory,
                 const RequestTimeout& request_timeout,
                 const IdleTimeout& idle_timeout);

    /// @brief Destructor.
    ///
    /// Stops all active connections and closes transport acceptor service.
    ~HttpListener();

    /// @brief Returns local address on which server is listening.
    asiolink::IOAddress getLocalAddress() const;

    /// @brief Returns local port on which server is listening.
    uint16_t getLocalPort() const;

    /// @brief Starts accepting new connections.
    ///
    /// This method starts accepting and handling new HTTP connections on
    /// the IP address and port number specified in the constructor.
    ///
    /// If the method is invoked successfully, it must not be invoked again
    /// until @ref HttpListener::stop is called.
    ///
    /// @throw HttpListenerError if an error occurred.
    void start();

    /// @brief Stops all active connections and shuts down the service.
    void stop();

protected:

    /// @brief Pointer to the implementation of the @ref HttpListener.
    boost::shared_ptr<HttpListenerImpl> impl_;
};

/// @brief Pointer to the @ref HttpListener.
typedef boost::shared_ptr<HttpListener> HttpListenerPtr;

/// @brief Pointer to the const @ref HttpListener.
typedef boost::shared_ptr<const HttpListener> ConstHttpListenerPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif
