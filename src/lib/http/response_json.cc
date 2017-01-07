// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/response_json.h>

using namespace isc::data;

namespace isc {
namespace http {

HttpResponseJson::HttpResponseJson(const HttpVersion& version,
                                   const HttpStatusCode& status_code,
                                   const CallSetGenericBody& generic_body)
    : HttpResponse(version, status_code, CallSetGenericBody::no()) {
    addHeader("Content-Type", "application/json");
    // This class provides its own implementation of the setGenericBody.
    // We call it here unless the derived class calls this constructor
    // from its own constructor and indicates that we shouldn't set the
    // generic content in the body.
    if (generic_body.set_) {
        setGenericBody(status_code);
    }
}

void
HttpResponseJson::setGenericBody(const HttpStatusCode& status_code) {
    // Only generate the content for the client or server errors. For
    // other status codes (status OK in particular) the content should
    // be created using setBodyAsJson or setBody.
    if (isClientError(status_code) || isServerError(status_code)) {
        std::map<std::string, ConstElementPtr> map_elements;
        map_elements["result"] =
            ConstElementPtr(new IntElement(statusCodeToNumber(status_code)));
        map_elements["text"] =
            ConstElementPtr(new StringElement(statusCodeToString(status_code)));
        auto body = Element::createMap();
        body->setValue(map_elements);
        setBodyAsJson(body);
    }
}

void
HttpResponseJson::setBodyAsJson(const ConstElementPtr& json_body) {
    setBody(json_body->str());
}


} // namespace http
} // namespace isc
