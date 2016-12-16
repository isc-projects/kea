// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_JSON_H
#define HTTP_RESPONSE_JSON_H

#include <cc/data.h>
#include <http/response.h>

namespace isc {
namespace http {

class HttpResponseJson : public HttpResponse {
public:

    HttpResponseJson(const HttpVersion& version,
                     const HttpStatusCode& status_code);

    virtual void setGenericBody(const HttpStatusCode& status_code);

    virtual void setBodyAsJson(const data::ConstElementPtr& json_body);

};

}
}

#endif
