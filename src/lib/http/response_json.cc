// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/response_json.h>
#include <map>

using namespace isc::data;

namespace isc {
namespace http {

HttpResponseJson::HttpResponseJson()
    : HttpResponse() {
    context()->headers_.push_back(HttpHeaderContext("Content-Type", "application/json"));
}


HttpResponseJson::HttpResponseJson(const HttpVersion& version,
                                   const HttpStatusCode& status_code,
                                   const CallSetGenericBody& generic_body)
    : HttpResponse(version, status_code, CallSetGenericBody::no()) {
    context()->headers_.push_back(HttpHeaderContext("Content-Type", "application/json"));
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
HttpResponseJson::finalize() {
    if (!created_) {
        create();
    }

    // Parse JSON body and store.
    parseBodyAsJson();
    finalized_ = true;
}

void
HttpResponseJson::reset() {
    HttpResponse::reset();
    json_.reset();
}

ConstElementPtr
HttpResponseJson::getBodyAsJson() const {
    checkFinalized();
    return (json_);
}

void
HttpResponseJson::setBodyAsJson(const ConstElementPtr& json_body) {
    if (json_body) {
        context()->body_ = json_body->str();

    } else {
        context()->body_.clear();
    }

    json_ = json_body;
}

ConstElementPtr
HttpResponseJson::getJsonElement(const std::string& element_name) const {
    try {
        ConstElementPtr body = getBodyAsJson();
        if (body) {
            const std::map<std::string, ConstElementPtr>& map_value = body->mapValue();
            auto map_element = map_value.find(element_name);
            if (map_element != map_value.end()) {
                return (map_element->second);
            }
        }

    } catch (const std::exception& ex) {
        isc_throw(HttpResponseJsonError, "unable to get JSON element "
                  << element_name << ": " << ex.what());
    }
    return (ConstElementPtr());
}

void
HttpResponseJson::parseBodyAsJson() {
   try {
       // Only parse the body if it hasn't been parsed yet.
       if (!json_ && !context_->body_.empty()) {
           json_ = Element::fromJSON(context_->body_);
       }
    } catch (const std::exception& ex) {
        isc_throw(HttpResponseJsonError, "unable to parse the body of the HTTP"
                  " response: " << ex.what());
    }
}

} // namespace http
} // namespace isc
