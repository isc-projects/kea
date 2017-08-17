// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/post_request_json.h>

using namespace isc::data;

namespace isc {
namespace http {

PostHttpRequestJson::PostHttpRequestJson()
    : PostHttpRequest(), json_() {
    requireHeaderValue("Content-Type", "application/json");
}

void
PostHttpRequestJson::finalize() {
    if (!created_) {
        create();
    }

    // Parse JSON body and store.
    parseBodyAsJson();
    finalized_ = true;
}

void
PostHttpRequestJson::reset() {
    PostHttpRequest::reset();
    json_.reset();
}

ConstElementPtr
PostHttpRequestJson::getBodyAsJson() const {
    checkFinalized();
    return (json_);
}

ConstElementPtr
PostHttpRequestJson::getJsonElement(const std::string& element_name) const {
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
        isc_throw(HttpRequestJsonError, "unable to get JSON element "
                  << element_name << ": " << ex.what());
    }
    return (ConstElementPtr());
}

void
PostHttpRequestJson::parseBodyAsJson() {
   try {
       // Only parse the body if it hasn't been parsed yet.
       if (!json_ && !context_->body_.empty()) {
           json_ = Element::fromJSON(context_->body_);
       }
    } catch (const std::exception& ex) {
        isc_throw(HttpRequestJsonError, "unable to parse the body of the HTTP"
                  " request: " << ex.what());
    }
}

} // namespace http
} // namespace isc
