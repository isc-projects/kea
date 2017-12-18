// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/request.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

namespace isc {
namespace http {

HttpRequest::HttpRequest()
    : HttpMessage(), required_methods_(),
      method_(Method::HTTP_METHOD_UNKNOWN),
      context_(new HttpRequestContext()) {
}

void
HttpRequest::requireHttpMethod(const HttpRequest::Method& method) {
    required_methods_.insert(method);
}

void
HttpRequest::create() {
    try {
        // The RequestParser doesn't validate the method name. Thus, this
        // may throw an exception. But, we're fine with lower case names,
        // e.g. get, post etc.
        method_ = methodFromString(context_->method_);

        // Check if the method is allowed for this request.
        if (!inRequiredSet(method_, required_methods_)) {
            isc_throw(BadValue, "use of HTTP " << methodToString(method_)
                      << " not allowed");
        }

        http_version_.major_ = context_->http_version_major_;
        http_version_.minor_ = context_->http_version_minor_;

        // Check if the HTTP version is allowed for this request.
        if (!inRequiredSet(http_version_, required_versions_)) {
            isc_throw(BadValue, "use of HTTP version "
                      << http_version_.major_ << "."
                      << http_version_.minor_
                      << " not allowed");
        }

        // Copy headers from the context.
        for (auto header = context_->headers_.begin();
             header != context_->headers_.end();
             ++header) {
            HttpHeaderPtr hdr(new HttpHeader(header->name_, header->value_));
            headers_[hdr->getLowerCaseName()] = hdr;
        }

        if (!context_->body_.empty() && (headers_.count("content-length") == 0)) {
            HttpHeaderPtr hdr(new HttpHeader("Content-Length",
                                             boost::lexical_cast<std::string>(context_->body_.length())));
            headers_["content-length"] = hdr;
        }

        // Iterate over required headers and check that they exist
        // in the HTTP request.
        for (auto req_header = required_headers_.begin();
             req_header != required_headers_.end();
             ++req_header) {
            auto header = headers_.find(req_header->first);
            if (header == headers_.end()) {
                isc_throw(BadValue, "required header " << req_header->first
                          << " not found in the HTTP request");
            } else if (!req_header->second->getValue().empty() &&
                       !header->second->isValueEqual(req_header->second->getValue())) {
                // If specific value is required for the header, check
                // that the value in the HTTP request matches it.
                isc_throw(BadValue, "required header's " << header->first
                          << " value is " << req_header->second->getValue()
                          << ", but " << header->second->getValue() << " was found");
            }
        }

    } catch (const std::exception& ex) {
        // Reset the state of the object if we failed at any point.
        reset();
        isc_throw(HttpRequestError, ex.what());
    }

    // All ok.
    created_ = true;
}

void
HttpRequest::finalize() {
    if (!created_) {
        create();
    }

    // Copy the body from the context. Derive classes may further
    // interpret the body contents, e.g. against the Content-Type.
    body_ = context_->body_;
    finalized_ = true;
}

void
HttpRequest::reset() {
    created_ = false;
    finalized_ = false;
    method_ = HttpRequest::Method::HTTP_METHOD_UNKNOWN;
    headers_.clear();
    body_.clear();
}

HttpRequest::Method
HttpRequest::getMethod() const {
    checkCreated();
    return (method_);
}

std::string
HttpRequest::getUri() const {
    checkCreated();
    return (context_->uri_);
}

std::string
HttpRequest::getBody() const {
    checkFinalized();
    return (context_->body_);
}

std::string
HttpRequest::toString() const {
    checkFinalized();

    std::ostringstream s;
    s << methodToString(getMethod()) << " " << getUri() << " HTTP/" <<
        getHttpVersion().major_ << "." << getHttpVersion().minor_ << "\r\n";

    for (auto header_it = headers_.cbegin(); header_it != headers_.cend();
         ++header_it) {
        s << header_it->second->getName() << ": " << header_it->second->getValue()
          << "\r\n";
    }

    s << "\r\n";

    s << getBody();

    return (s.str());
}

bool
HttpRequest::isPersistent() const {
    HttpHeaderPtr conn = getHeaderSafe("connection");
    std::string conn_value;
    if (conn) {
        conn_value = conn->getLowerCaseValue();
    }

    HttpVersion ver = getHttpVersion();

    return (((ver == HttpVersion::HTTP_10()) && (conn_value == "keep-alive")) ||
            ((HttpVersion::HTTP_10() < ver) && (conn_value.empty() || (conn_value != "close"))));
}

HttpRequest::Method
HttpRequest::methodFromString(std::string method) const {
    boost::to_upper(method);
    if (method == "GET") {
        return (Method::HTTP_GET);
    } else if (method == "POST") {
        return (Method::HTTP_POST);
    } else if (method == "HEAD") {
        return (Method::HTTP_HEAD);
    } else if (method == "PUT") {
        return (Method::HTTP_PUT);
    } else if (method == "DELETE") {
        return (Method::HTTP_DELETE);
    } else if (method == "OPTIONS") {
        return (Method::HTTP_OPTIONS);
    } else if (method == "CONNECT") {
        return (Method::HTTP_CONNECT);
    } else {
        isc_throw(HttpRequestError, "unknown HTTP method " << method);
    }
}

std::string
HttpRequest::methodToString(const HttpRequest::Method& method) const {
    switch (method) {
    case Method::HTTP_GET:
        return ("GET");
    case Method::HTTP_POST:
        return ("POST");
    case Method::HTTP_HEAD:
        return ("HEAD");
    case Method::HTTP_PUT:
        return ("PUT");
    case Method::HTTP_DELETE:
        return ("DELETE");
    case Method::HTTP_OPTIONS:
        return ("OPTIONS");
    case Method::HTTP_CONNECT:
        return ("CONNECT");
    default:
        return ("unknown HTTP method");
    }
}

}
}
