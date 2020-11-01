// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CREATOR_H
#define HTTP_RESPONSE_CREATOR_H

#include <http/request.h>
#include <http/response.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace http {

class HttpResponseCreator;

/// @brief Pointer to the @ref HttpResponseCreator object.
typedef boost::shared_ptr<HttpResponseCreator> HttpResponseCreatorPtr;

/// @brief Specifies an interface for classes creating HTTP responses
/// from HTTP requests.
///
/// HTTP is designed to carry various content types. Most commonly
/// this is text/html. In Kea, the application/json content type is used
/// to carry control commands in JSON format. The libkea-http library is
/// meant to be generic and provide means for transferring different types
/// of content, depending on the use case.
///
/// This abstract class specifies a common interface for generating HTTP
/// responses from HTTP requests using specific content type and being
/// used in some specific context. Kea modules providing HTTP services need to
/// implement their specific derivations of the @ref HttpResponseCreator
/// class. These derivations use classes derived from @ref HttpRequest as
/// an input and classes derived from @ref HttpResponse as an output of
/// @c createHttpResponse method.
class HttpResponseCreator {
public:

    /// @brief Destructor.
    ///
    /// Classes with virtual functions need virtual destructors.
    virtual ~HttpResponseCreator() { };

    /// @brief Create HTTP response from HTTP request received.
    ///
    /// This class implements a generic logic for creating a HTTP response.
    /// Derived classes do not override this method. They merely implement
    /// the methods it calls.
    ///
    /// The request processing may generally fail at one of the two stages:
    /// parsing or interpretation of the parsed request. During the former
    /// stage the request's syntax is checked, i.e. HTTP version, URI,
    /// headers etc. During the latter stage the HTTP server checks if the
    /// request is valid within the specific context, e.g. valid HTTP version
    /// used, expected content type etc.
    ///
    /// In the @ref HttpRequest terms, the request has gone through the
    /// first stage if it is "finalized" (see @ref HttpRequest::finalize).
    /// This method accepts instances of both finalized and not finalized
    /// requests. If the request isn't finalized it indicates that
    /// the request parsing has failed. In such case, this method calls
    /// @c createStockBadRequest to generate a response with HTTP 400 status
    /// code. If the request is finalized, this method calls
    /// @c createDynamicHttpResponse to generate implementation specific
    /// response to the received request.
    ///
    /// This method is marked virtual final to prevent derived classes from
    /// overriding this method. Instead, the derived classes must implement
    /// protected methods which this method calls.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @return Pointer to the object encapsulating generated HTTP response.
    /// @throw HttpResponseError if request is a NULL pointer.
    virtual HttpResponsePtr
    createHttpResponse(HttpRequestPtr request) final;

    /// @brief Create a new request.
    ///
    /// This method creates an instance of the @ref HttpRequest or derived
    /// class. The type of the object is compatible with the instance of
    /// the @ref HttpResponseCreator implementation which creates it, i.e.
    /// can be used as an argument in the call to @ref createHttpResponse.
    ///
    /// @return Pointer to the new instance of the @ref HttpRequest.
    virtual HttpRequestPtr
    createNewHttpRequest() const = 0;

    /// @brief Creates implementation specific HTTP response.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @param status_code Status code of the response.
    /// @return Pointer to an object representing HTTP response.
    virtual HttpResponsePtr
    createStockHttpResponse(const HttpRequestPtr& request,
                            const HttpStatusCode& status_code) const = 0;

protected:

    /// @brief Creates implementation specific HTTP response.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @return Pointer to an object representing HTTP response.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) = 0;

};

} // namespace http
} // namespace isc

#endif
