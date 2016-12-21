// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/response.h>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/time_facet.hpp>
#include <sstream>

using namespace boost::local_time;
using namespace isc::http;

namespace {

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
    { HttpStatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error" },
    { HttpStatusCode::NOT_IMPLEMENTED, "Not Implemented" },
    { HttpStatusCode::BAD_GATEWAY, "Bad Gateway" },
    { HttpStatusCode::SERVICE_UNAVAILABLE, "Service Unavailable" }
};

const std::string crlf = "\r\n";

}

namespace isc {
namespace http {

HttpResponse::HttpResponse(const HttpVersion& version,
                           const HttpStatusCode& status_code)
    : http_version_(version), status_code_(status_code), headers_(),
      body_() {
    setGenericBody(status_code);
}

void
HttpResponse::setBody(const std::string& body) {
    body_ = body;
}

bool
HttpResponse::isClientError(const HttpStatusCode& status_code) {
    uint16_t c = statusCodeToNumber(status_code);
    return ((c >= 400) && (c < 500));
}

bool
HttpResponse::isServerError(const HttpStatusCode& status_code) {
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
    local_date_time t(local_sec_clock::local_time(time_zone_ptr()));
    std::stringstream s;
    local_time_facet* lf(new local_time_facet("%a, %d %b %Y %H:%M:%S GMT"));
    s.imbue(std::locale(s.getloc(), lf));
    s << t;

    return (s.str());
}

std::string
HttpResponse::toString() const {
    std::ostringstream s;
    s << "HTTP/" << http_version_.first << "." << http_version_.second;
    s << " " << static_cast<uint16_t>(status_code_);
    s << " " << statusCodeToString(status_code_) << crlf;

    for (auto header = headers_.cbegin(); header != headers_.cend();
         ++header) {
        s << header->first << ": " << header->second << crlf;
    }

    s << "Date: " << getDateHeaderValue() << crlf;

    if (!body_.empty()) {
        s << "Content-Length: " << body_.length() << crlf;
    }

    s << crlf;

    s << body_;

    return (s.str());
}

} // namespace http
} // namespace isc
