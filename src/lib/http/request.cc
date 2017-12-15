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
    : required_methods_(),required_versions_(), required_headers_(),
      created_(false), finalized_(false), method_(Method::HTTP_METHOD_UNKNOWN),
      headers_(), context_(new HttpRequestContext()) {
}

HttpRequest::~HttpRequest() {
}

void
HttpRequest::requireHttpMethod(const HttpRequest::Method& method) {
    required_methods_.insert(method);
}

void
HttpRequest::requireHttpVersion(const HttpVersion& version) {
    required_versions_.insert(version);
}

void
HttpRequest::requireHeader(const std::string& header_name) {
    // Empty value denotes that the header is required but no specific
    // value is expected.
    HttpHeaderPtr hdr(new HttpHeader(header_name));
    required_headers_[hdr->getLowerCaseName()] = hdr;
}

void
HttpRequest::requireHeaderValue(const std::string& header_name,
                                const std::string& header_value) {
    HttpHeaderPtr hdr(new HttpHeader(header_name, header_value));
    required_headers_[hdr->getLowerCaseName()] = hdr;
}

bool
HttpRequest::requiresBody() const {
    // If Content-Length is required the body must exist too. There may
    // be probably some cases when Content-Length is not provided but
    // the body is provided. But, probably not in our use cases.
    // Use lower case header name because this is how it is indexed in
    // the storage.
    return (required_headers_.find("content-length") != required_headers_.end());
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

        // Check if the HTTP version is allowed for this request.
        if (!inRequiredSet(HttpVersion(context_->http_version_major_,
                                       context_->http_version_minor_),
                           required_versions_)) {
            isc_throw(BadValue, "use of HTTP version "
                      << context_->http_version_major_ << "."
                      << context_->http_version_minor_
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

    // In this specific case, we don't need to do anything because the
    // body is retrieved from the context object directly. We also don't
    // know what type of body we have received. Derived classes should
    // override this method and handle various types of bodies.
    finalized_ = true;
}

void
HttpRequest::reset() {
    created_ = false;
    finalized_ = false;
    method_ = HttpRequest::Method::HTTP_METHOD_UNKNOWN;
    headers_.clear();
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

HttpVersion
HttpRequest::getHttpVersion() const {
    checkCreated();
    return (HttpVersion(context_->http_version_major_,
                        context_->http_version_minor_));
}

HttpHeaderPtr
HttpRequest::getHeader(const std::string& header_name) const {
    HttpHeaderPtr http_header = getHeaderSafe(header_name);

    // No such header.
    if (!http_header) {
        isc_throw(HttpRequestNonExistingHeader, header_name << " HTTP header"
                  " not found in the request");
    }

    // Header found.
    return (http_header);
}

HttpHeaderPtr
HttpRequest::getHeaderSafe(const std::string& header_name) const {
    checkCreated();

    HttpHeader hdr(header_name);
    auto header_it = headers_.find(hdr.getLowerCaseName());
    if (header_it != headers_.end()) {
        return (header_it->second);
    }

    // Header not found. Return null pointer.
    return (HttpHeaderPtr());
}

std::string
HttpRequest::getHeaderValue(const std::string& header_name) const {
    return (getHeader(header_name)->getValue());
}

uint64_t
HttpRequest::getHeaderValueAsUint64(const std::string& header_name) const {
    try {
        return (getHeader(header_name)->getUint64Value());

    } catch (const std::exception& ex) {
        // The specified header does exist, but the value is not a number.
        isc_throw(HttpRequestError, ex.what());
    }
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

void
HttpRequest::checkCreated() const {
    if (!created_) {
        isc_throw(HttpRequestError, "unable to retrieve values of HTTP"
                  " request because the HttpRequest::create() must be"
                  " called first. This is a programmatic error");
    }
}

void
HttpRequest::checkFinalized() const {
    if (!finalized_) {
        isc_throw(HttpRequestError, "unable to retrieve body of HTTP"
                  " request because the HttpRequest::finalize() must be"
                  " called first. This is a programmatic error");
    }
}

template<typename T>
bool
HttpRequest::inRequiredSet(const T& element,
                           const std::set<T>& element_set) const {
    return (element_set.empty() || element_set.count(element) > 0);
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
