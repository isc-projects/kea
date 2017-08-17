// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/post_request.h>

namespace isc {
namespace http {

PostHttpRequest::PostHttpRequest()
    : HttpRequest() {
    requireHttpMethod(Method::HTTP_POST);
    requireHeader("Content-Length");
    requireHeader("Content-Type");
}

} // namespace http
} // namespace isc
