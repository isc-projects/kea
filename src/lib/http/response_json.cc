// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/response_json.h>

using namespace isc::data;

namespace isc {
namespace http {

HttpResponseJson::HttpResponseJson(const HttpVersion& version,
                                   const HttpStatusCode& status_code)
    : HttpResponse(version, status_code) {
    addHeader("Content-Type", "application/json");
    setGenericBody(status_code);
}

void
HttpResponseJson::setGenericBody(const HttpStatusCode& status_code) {
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
    std::ostringstream s;
    setBody(json_body->str());
}


} // namespace http
} // namespace isc
