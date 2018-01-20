// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_POST_REQUEST_H
#define HTTP_POST_REQUEST_H

#include <http/request.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace http {

class PostHttpRequest;

/// @brief Pointer to @ref PostHttpRequest.
typedef boost::shared_ptr<PostHttpRequest> PostHttpRequestPtr;
/// @brief Pointer to const @ref PostHttpRequest.
typedef boost::shared_ptr<const PostHttpRequest> ConstPostHttpRequestPtr;

/// @brief Represents HTTP POST request.
///
/// Instructs the parent class to require:
/// - HTTP POST message type,
/// - Content-Length header,
/// - Content-Type header.
class PostHttpRequest : public HttpRequest {
public:

    /// @brief Constructor for inbound HTTP request.
    PostHttpRequest();

    /// @brief Constructor for outbound HTTP request.
    ///
    /// @param method HTTP method, e.g. POST.
    /// @param uri URI.
    /// @param version HTTP version.
    PostHttpRequest(const Method& method, const std::string& uri, const HttpVersion& version);

};


} // namespace http
} // namespace isc

#endif
