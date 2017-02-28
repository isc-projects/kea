// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

HttpResponse::HttpResponse(const HttpVersion& version,
                           const HttpStatusCode& status_code,
                           const CallSetGenericBody& generic_body)
    : http_version_(version), status_code_(status_code), headers_(),
      body_() {
    if (generic_body.set_) {
        // This currently does nothing, but it is useful to have it here as
        // an example how to implement it in the derived classes.
        setGenericBody(status_code);
    }
}

void
HttpResponse::setBody(const std::string& body) {
    body_ = body;
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
    std::ostringstream s;
    // HTTP version number and status code.
    s << "HTTP/" << http_version_.major_ << "." << http_version_.minor_;
    s << " " << static_cast<uint16_t>(status_code_);
    s << " " << statusCodeToString(status_code_) << crlf;
    return (s.str());
}

std::string
HttpResponse::toString() const {
    std::ostringstream s;
    // HTTP version number and status code.
    s << toBriefString();

    // We need to at least insert "Date" header into the HTTP headers. This
    // method is const thus we can't insert it into the headers_ map. We'll
    // work on the copy of the map. Admittedly, we could just append "Date"
    // into the generated string but we prefer that headers are ordered
    // alphabetically.
    std::map<std::string, std::string> headers(headers_);

    // Update or add "Date" header.
    addHeaderInternal("Date", getDateHeaderValue(), headers);

    // Always add "Content-Length", perhaps equal to 0.
    addHeaderInternal("Content-Length", body_.length(), headers);

    // Include all headers.
    for (auto header = headers.cbegin(); header != headers.cend();
         ++header) {
        s << header->first << ": " << header->second << crlf;
    }

    s << crlf;

    // Include message body.
    s << body_;

    return (s.str());
}

} // namespace http
} // namespace isc
