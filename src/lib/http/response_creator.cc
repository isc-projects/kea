// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/response_creator.h>

namespace isc {
namespace http {

HttpResponsePtr
HttpResponseCreator::createHttpResponse(const ConstHttpRequestPtr& request) {
    if (!request) {
        isc_throw(HttpResponseError, "internal server error: HTTP request is null");
    }

    if (!request->isFinalized()) {
        return (createStockBadRequest(request));
    }

    return (createDynamicHttpResponse(request));
}

}
}
