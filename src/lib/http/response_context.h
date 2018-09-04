// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CONTEXT_H
#define HTTP_RESPONSE_CONTEXT_H

#include <http/header_context.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace isc {
namespace http {

/// @brief HTTP response context.
///
/// This context is used by the @c HttpResponseParser to store parsed
/// data. This data is later used to create an instance of the
/// @c HttpResponse or its derivation.
struct HttpResponseContext {
    /// @brief HTTP major version number.
    unsigned int http_version_major_;
    /// @brief HTTP minor version number.
    unsigned int http_version_minor_;
    /// @brief HTTP status code.
    unsigned int status_code_;
    /// @brief HTTP status phrase.
    std::string phrase_;
    /// @brief Collection of HTTP headers.
    std::vector<HttpHeaderContext> headers_;
    /// @brief HTTP request body.
    std::string body_;
};

/// @brief Pointer to the @ref HttpResponseContext.
typedef boost::shared_ptr<HttpResponseContext> HttpResponseContextPtr;

} // end of namespace http
} // end of namespace isc

#endif // endif HTTP_RESPONSE_CONTEXT_H
