// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/http_message.h>

namespace isc {
namespace http {

HttpMessage::HttpMessage(const HttpMessage::Direction& direction)
    : direction_(direction), required_versions_(),
      http_version_(HttpVersion::HTTP_10()), required_headers_(),
      created_(false), finalized_(false), headers_() {
}

HttpMessage::~HttpMessage() {
}

void
HttpMessage::requireHttpVersion(const HttpVersion& version) {
    required_versions_.insert(version);
}

void
HttpMessage::requireHeader(const std::string& header_name) {
    // Empty value denotes that the header is required but no specific
    // value is expected.
    HttpHeaderPtr hdr(new HttpHeader(header_name));
    required_headers_[hdr->getLowerCaseName()] = hdr;
}

void
HttpMessage::requireHeaderValue(const std::string& header_name,
                                const std::string& header_value) {
    HttpHeaderPtr hdr(new HttpHeader(header_name, header_value));
    required_headers_[hdr->getLowerCaseName()] = hdr;
}

bool
HttpMessage::requiresBody() const {
    // If Content-Length is required the body must exist too. There may
    // be probably some cases when Content-Length is not provided but
    // the body is provided. But, probably not in our use cases.
    // Use lower case header name because this is how it is indexed in
    // the storage.
    return (required_headers_.find("content-length") != required_headers_.end());
}

HttpVersion
HttpMessage::getHttpVersion() const {
    checkCreated();
    return (http_version_);
}

HttpHeaderPtr
HttpMessage::getHeader(const std::string& header_name) const {
    checkCreated();

    HttpHeader hdr(header_name);
    auto header_it = headers_.find(hdr.getLowerCaseName());
    if (header_it != headers_.end()) {
        return (header_it->second);
    }

    isc_throw(HttpMessageNonExistingHeader, header_name << " HTTP header"
              " not found in the request");
}

std::string
HttpMessage::getHeaderValue(const std::string& header_name) const {
    return (getHeader(header_name)->getValue());
}

uint64_t
HttpMessage::getHeaderValueAsUint64(const std::string& header_name) const {
    try {
        return (getHeader(header_name)->getUint64Value());

    } catch (const std::exception& ex) {
        // The specified header does exist, but the value is not a number.
        isc_throw(HttpMessageError, ex.what());
    }
}

void
HttpMessage::checkCreated() const {
    if (!created_) {
        isc_throw(HttpMessageError, "unable to retrieve values of HTTP"
                  " message because the HttpMessage::create() must be"
                  " called first. This is a programmatic error");
    }
}

void
HttpMessage::checkFinalized() const {
    if (!finalized_) {
        isc_throw(HttpMessageError, "unable to retrieve body of HTTP"
                  " message because the HttpMessage::finalize() must be"
                  " called first. This is a programmatic error");
    }
}

} // end of namespace isc::http
} // end of namespace isc
