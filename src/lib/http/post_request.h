// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_POST_REQUEST_H
#define HTTP_POST_REQUEST_H

#include <http/request.h>

namespace isc {
namespace http {

/// @brief Represents HTTP POST request.
///
/// Instructs the parent class to require:
/// - HTTP POST message type,
/// - Content-Length header,
/// - Content-Type header.
class PostHttpRequest : public HttpRequest {
public:

    /// @brief Constructor.
    PostHttpRequest();
};

} // namespace http
} // namespace isc

#endif
