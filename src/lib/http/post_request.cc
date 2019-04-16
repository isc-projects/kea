// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/post_request.h>

namespace isc {
namespace http {

PostHttpRequest::PostHttpRequest()
    : HttpRequest() {
    requireHttpMethod(Method::HTTP_POST);
    requireHeader("Content-Length");
    requireHeader("Content-Type");
}

PostHttpRequest::PostHttpRequest(const Method& method, const std::string& uri,
                                 const HttpVersion& version,
                                 const HostHttpHeader& host_header)
    : HttpRequest(method, uri, version, host_header) {
    requireHttpMethod(Method::HTTP_POST);
    requireHeader("Content-Length");
    requireHeader("Content-Type");
}


} // namespace http
} // namespace isc
