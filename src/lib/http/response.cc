// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/date_time.h>
#include <http/response.h>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/time_facet.hpp>
#include <sstream>

using namespace boost::local_time;
using namespace isc::http;

namespace {

/// @brief A map of status codes to status names.
const std::map<HttpStatusCode, std::string> status_code_to_description = {
    { HttpStatusCode::OK, "OK" },
    { HttpStatusCode::CREATED, "Created" },
    { HttpStatusCode::ACCEPTED, "Accepted" },
    { HttpStatusCode::NO_CONTENT, "No Content" },
    { HttpStatusCode::MULTIPLE_CHOICES, "Multiple Choices" },
    { HttpStatusCode::MOVED_PERMANENTLY, "Moved Permanently" },
    { HttpStatusCode::MOVED_TEMPORARILY, "Moved Temporarily" },
    { HttpStatusCode::NOT_MODIFIED, "Not Modified" },
    { HttpStatusCode::BAD_REQUEST, "Bad Request" },
    { HttpStatusCode::UNAUTHORIZED, "Unauthorized" },
    { HttpStatusCode::FORBIDDEN, "Forbidden" },
    { HttpStatusCode::NOT_FOUND, "Not Found" },
    { HttpStatusCode::REQUEST_TIMEOUT, "Request Timeout" },
    { HttpStatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error" },
    { HttpStatusCode::NOT_IMPLEMENTED, "Not Implemented" },
    { HttpStatusCode::BAD_GATEWAY, "Bad Gateway" },
    { HttpStatusCode::SERVICE_UNAVAILABLE, "Service Unavailable" }
};

/// @brief New line (CRLF).
const std::string crlf = "\r\n";

}

namespace isc {
namespace http {

HttpResponse::HttpResponse()
    : HttpMessage(INBOUND), context_(new HttpResponseContext()) {
}

HttpResponse::HttpResponse(const HttpVersion& version,
                           const HttpStatusCode& status_code,
                           const CallSetGenericBody& generic_body)
    : HttpMessage(OUTBOUND), context_(new HttpResponseContext()) {
    context_->http_version_major_ = version.major_;
    context_->http_version_minor_ = version.minor_;
    context_->status_code_ = static_cast<unsigned int>(status_code);

    if (generic_body.set_) {
        // This currently does nothing, but it is useful to have it here as
        // an example how to implement it in the derived classes.
        setGenericBody(status_code);
    }
}

void
HttpResponse::create() {
    try {
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

        if (getDirection() == HttpMessage::OUTBOUND) {
            HttpHeaderPtr length_header(new HttpHeader("Content-Length", boost::lexical_cast<std::string>
                                                       (context_->body_.length())));
            headers_["content-length"] = length_header;

            HttpHeaderPtr date_header(new HttpHeader("Date", getDateHeaderValue()));;
            headers_["date"] = date_header;
        }

        // Iterate over required headers and check that they exist
        // in the HTTP response.
        for (auto req_header = required_headers_.begin();
             req_header != required_headers_.end();
             ++req_header) {
            auto header = headers_.find(req_header->first);
            if (header == headers_.end()) {
                isc_throw(BadValue, "required header " << req_header->first
                          << " not found in the HTTP response");
            } else if (!req_header->second->getValue().empty() &&
                       !header->second->isValueEqual(req_header->second->getValue())) {
                // If specific value is required for the header, check
                // that the value in the HTTP response matches it.
                isc_throw(BadValue, "required header's " << header->first
                          << " value is " << req_header->second->getValue()
                          << ", but " << header->second->getValue() << " was found");
            }
        }

    } catch (const std::exception& ex) {
        // Reset the state of the object if we failed at any point.
        reset();
        isc_throw(HttpResponseError, ex.what());
    }

    // All ok.
    created_ = true;
}

void
HttpResponse::finalize() {
    if (!created_) {
        create();
    }

    finalized_ = true;
}

void
HttpResponse::reset() {
    created_ = false;
    finalized_ = false;
    headers_.clear();
}

HttpStatusCode
HttpResponse::getStatusCode() const {
    checkCreated();
    return (static_cast<HttpStatusCode>(context_->status_code_));
}

std::string
HttpResponse::getStatusPhrase() const {
    checkCreated();
    return (context_->phrase_);
}

std::string
HttpResponse::getBody() const {
    checkFinalized();
    return (context_->body_);
}

bool
HttpResponse::isClientError(const HttpStatusCode& status_code) {
    // Client errors have status codes of 4XX.
    uint16_t c = statusCodeToNumber(status_code);
    return ((c >= 400) && (c < 500));
}

bool
HttpResponse::isServerError(const HttpStatusCode& status_code) {
    // Server errors have status codes of 5XX.
    uint16_t c = statusCodeToNumber(status_code);
    return ((c >= 500) && (c < 600));
}

std::string
HttpResponse::statusCodeToString(const HttpStatusCode& status_code) {
    auto status_code_it = status_code_to_description.find(status_code);
    if (status_code_it == status_code_to_description.end()) {
        isc_throw(HttpResponseError, "internal server error: no HTTP status"
                  " description for the given status code "
                  << static_cast<uint16_t>(status_code));
    }
    return (status_code_it->second);
}

uint16_t
HttpResponse::statusCodeToNumber(const HttpStatusCode& status_code) {
    return (static_cast<uint16_t>(status_code));
}

std::string
HttpResponse::getDateHeaderValue() const {
    // This returns current time in the recommended format.
    HttpDateTime date_time;
    return (date_time.rfc1123Format());
}

std::string
HttpResponse::toBriefString() const {
    checkFinalized();

    std::ostringstream s;
    // HTTP version number and status code.
    s << "HTTP/" << http_version_.major_ << "." << http_version_.minor_;
    s << " " << context_->status_code_;
    s << " " << statusCodeToString(static_cast<HttpStatusCode>(context_->status_code_));
    return (s.str());
}

std::string
HttpResponse::toString() const {

    std::ostringstream s;
    // HTTP version number and status code.
    s << toBriefString() << crlf;

    for (auto header_it = headers_.cbegin(); header_it != headers_.cend();
         ++header_it) {
        s << header_it->second->getName() << ": " << header_it->second->getValue()
          << crlf;
    }

    s << crlf;

    // Include message body.
    s << getBody();

    return (s.str());
}

} // namespace http
} // namespace isc
