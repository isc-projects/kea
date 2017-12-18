// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <http/http_message.h>
#include <http/request_context.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace isc {
namespace http {

/// @brief Generic exception thrown by @ref HttpRequest class.
class HttpRequestError : public HttpMessageError {
public:
    HttpRequestError(const char* file, size_t line, const char* what) :
        HttpMessageError(file, line, what) { };
};

/// @brief Exception thrown when attempt is made to retrieve a
/// non-existing header.
class HttpRequestNonExistingHeader : public HttpRequestError {
public:
    HttpRequestNonExistingHeader(const char* file, size_t line,
                                 const char* what) :
        HttpRequestError(file, line, what) { };
};

class HttpRequest;

/// @brief Pointer to the @ref HttpRequest object.
typedef boost::shared_ptr<HttpRequest> HttpRequestPtr;

/// @brief Pointer to the const @ref HttpRequest object.
typedef boost::shared_ptr<const HttpRequest> ConstHttpRequestPtr;

/// @brief Represents HTTP request message.
///
/// This object represents parsed HTTP message. The @ref HttpRequestContext
/// contains raw data used as input for this object. This class interprets the
/// data. In particular, it verifies that the appropriate method, HTTP version,
/// and headers were used. The derivations of this class provide specializations
/// and specify the HTTP methods, versions and headers supported/required in
/// the specific use cases.
///
/// For example, the @ref PostHttpRequest class derives from @ref HttpRequest
/// and it requires that parsed messages use POST method. The
/// @ref PostHttpRequestJson, which derives from @ref PostHttpRequest requires
/// that the POST message includes body holding a JSON structure and provides
/// methods to parse the JSON body.
class HttpRequest : public HttpMessage {
public:

    /// @brief HTTP methods.
    enum class Method {
        HTTP_GET,
        HTTP_POST,
        HTTP_HEAD,
        HTTP_PUT,
        HTTP_DELETE,
        HTTP_OPTIONS,
        HTTP_CONNECT,
        HTTP_METHOD_UNKNOWN
    };

    /// @brief Constructor.
    ///
    /// Creates new context (@ref HttpRequestContext).
    HttpRequest();

    /// @brief Returns reference to the @ref HttpRequestContext.
    ///
    /// The context holds intermediate data for creating a request. The request
    /// parser stores parsed raw data in the context. When parsing is finished,
    /// the data are validated and committed into the @ref HttpRequest.
    ///
    /// @return Pointer to the underlying @ref HttpRequestContext.
    const HttpRequestContextPtr& context() const {
        return (context_);
    }

    /// @brief Specifies an HTTP method allowed for the request.
    ///
    /// Allowed methods must be specified prior to calling @ref create method.
    /// If no method is specified, all methods are supported.
    ///
    /// @param method HTTP method allowed for the request.
    void requireHttpMethod(const HttpRequest::Method& method);

    /// @brief Reads parsed request from the @ref HttpRequestContext, validates
    /// the request and stores parsed information.
    ///
    /// This method must be called before retrieving parsed data using accessors
    /// such as @ref getMethod, @ref getUri etc.
    ///
    /// This method doesn't parse the HTTP request body.
    ///
    /// @throw HttpRequestError if the parsed request doesn't meet the specified
    /// requirements for it.
    virtual void create();

    /// @brief Complete parsing of the HTTP request or create outbound HTTP request.
    ///
    /// HTTP request parsing is performed in two stages: HTTP headers, then
    /// request body. The @ref create method parses HTTP headers. Once this is
    /// done, the caller can check if the "Content-Length" was specified and use
    /// it's value to determine the size of the body which is parsed in the
    /// second stage.
    ///
    /// This method generally performs the body parsing, but if it determines
    /// that the @ref create method hasn't been called, it calls @ref create
    /// before parsing the body.
    ///
    /// For the outbound (client) request, this method must be called after
    /// setting all required values in the request context. The Content-Length
    /// is generally not explicitly set by the caller in this case. This method
    /// computes the value of the Content-Length and inserts the suitable header
    /// when it finds non-empty body.
    ///
    /// The derivations must call @ref create if it hasn't been called prior to
    /// calling this method. It must set @ref finalized_ to true if the call
    /// to @ref finalize was successful.
    virtual void finalize();

    /// @brief Reset the state of the object.
    virtual void reset();

    /// @brief Returns HTTP method of the request.
    Method getMethod() const;

    /// @brief Returns HTTP request URI.
    std::string getUri() const;


    /// @brief Returns HTTP message body as string.
    std::string getBody() const;

    /// @brief Returns HTTP message as text.
    ///
    /// This method is called to generate the outbound HTTP message. Make
    /// sure to call @c finalize prior to calling this method.
    virtual std::string toString() const;


    /// @brief Checks if the client has requested persistent connection.
    ///
    /// For the HTTP/1.0 case, the connection is persistent if the client has
    /// included Connection: keep-alive header. For the HTTP/1.1 case, the
    /// connection is assumed to be persistent unless Connection: close header
    /// has been included.
    ///
    /// @return true if the client has requested persistent connection, false
    /// otherwise.
    bool isPersistent() const;

protected:

    /// @brief Converts HTTP method specified in textual format to @ref Method.
    ///
    /// @param method HTTP method specified in the textual format. This value
    /// is case insensitive.
    ///
    /// @return HTTP method as enum.
    /// @throw HttpRequestError if unknown method specified.
    Method methodFromString(std::string method) const;

    /// @brief Converts HTTP method to string.
    ///
    /// @param method HTTP method specified as enum.
    ///
    /// @return HTTP method as string.
    std::string methodToString(const HttpRequest::Method& method) const;

    /// @brief Set of required HTTP methods.
    ///
    /// If the set is empty, all methods are allowed.
    std::set<Method> required_methods_;

    /// @brief HTTP method of the request.
    Method method_;

    /// @brief Pointer to the @ref HttpRequestContext holding parsed
    /// data.
    HttpRequestContextPtr context_;
};

}
}

#endif
