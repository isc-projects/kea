// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/response_creator.h>

namespace isc {
namespace http {

HttpResponsePtr
HttpResponseCreator::createHttpResponse(HttpRequestPtr request) {
    // This should never happen. This method must only be called with a
    // non null request, so we consider it unlikely internal server error.
    if (!request) {
        isc_throw(HttpResponseError, "internal server error: HTTP request is null");
    }

    // If not finalized, the request parsing failed. Generate HTTP 400.
    if (!request->isFinalized()) {
        return (createStockHttpResponse(request, HttpStatusCode::BAD_REQUEST));
    }

    // Message has been successfully parsed. Create implementation specific
    // response to this request.
    return (createDynamicHttpResponse(request));
}

}
}
