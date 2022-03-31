// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/post_request_json.h>

using namespace isc::data;

namespace isc {
namespace http {

PostHttpRequestJson::PostHttpRequestJson()
    : PostHttpRequest(), json_() {
    requireHeaderValue("Content-Type", "application/json");
}

PostHttpRequestJson::PostHttpRequestJson(const Method& method, const std::string& uri,
                                         const HttpVersion& version,
                                         const HostHttpHeader& host_header,
                                         const BasicHttpAuthPtr& basic_auth)
    : PostHttpRequest(method, uri, version, host_header, basic_auth) {
    requireHeaderValue("Content-Type", "application/json");
    context()->headers_.push_back(HttpHeaderContext("Content-Type", "application/json"));
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

void
PostHttpRequestJson::setBodyAsJson(const data::ConstElementPtr& body) {
    if (body) {
        context_->body_ = body->str();
        json_ = body;

    } else {
        context_->body_.clear();
    }
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
           ElementPtr json = Element::fromJSON(context_->body_);
           if (!remote_.empty() && (json->getType() == Element::map)) {
               json->set("remote-address", Element::create(remote_));
           }
           json_ = json;
       }
    } catch (const std::exception& ex) {
        isc_throw(HttpRequestJsonError, "unable to parse the body of the HTTP"
                  " request: " << ex.what());
    }
}

} // namespace http
} // namespace isc
