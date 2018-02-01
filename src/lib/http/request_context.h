// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_CONTEXT_H
#define HTTP_REQUEST_CONTEXT_H

#include <http/header_context.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace isc {
namespace http {

/// @brief HTTP request context.
///
/// The context is used by the @ref HttpRequestParser to store parsed
/// data. This data is later used to create an instance of the
/// @ref HttpRequest or its derivation.
struct HttpRequestContext {
    /// @brief HTTP request method.
    std::string method_;
    /// @brief HTTP request URI.
    std::string uri_;
    /// @brief HTTP major version number.
    unsigned int http_version_major_;
    /// @brief HTTP minor version number.
    unsigned int http_version_minor_;
    /// @brief Collection of HTTP headers.
    std::vector<HttpHeaderContext> headers_;
    /// @brief HTTP request body.
    std::string body_;
};

/// @brief Pointer to the @ref HttpRequestContext.
typedef boost::shared_ptr<HttpRequestContext> HttpRequestContextPtr;

} // namespace http
} // namespace isc

#endif
