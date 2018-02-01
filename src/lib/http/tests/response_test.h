// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_TEST_H
#define HTTP_RESPONSE_TEST_H

#include <http/http_types.h>
#include <http/response.h>
#include <boost/lexical_cast.hpp>
#include <cstdint>

namespace isc {
namespace http {
namespace test {

/// @brief Base class for test HTTP response.
template<typename HttpResponseType>
class TestHttpResponseBase : public HttpResponseType {
public:

    /// @brief Constructor.
    ///
    /// @param version HTTP version for the response.
    /// @param status_code HTTP status code.
    TestHttpResponseBase(const HttpVersion& version,
                         const HttpStatusCode& status_code)
        : HttpResponseType(version, status_code) {
    }

    /// @brief Returns fixed header value.
    ///
    /// Including fixed header value in the response makes the
    /// response deterministic, which is critical for the unit
    /// tests.
    virtual std::string getDateHeaderValue() const {
        return ("Tue, 19 Dec 2016 18:53:35 GMT");
    }

    /// @brief Returns date header value.
    std::string generateDateHeaderValue() const {
        return (HttpResponseType::getDateHeaderValue());
    }

    /// @brief Sets custom content length.
    ///
    /// @param content_length Content length value.
    void setContentLength(const uint64_t content_length) {
        HttpHeaderPtr length_header(new HttpHeader("Content-Length",
                                                   boost::lexical_cast<std::string>
                                                   (content_length)));
        HttpResponseType::headers_["content-length"] = length_header;
    }
};

} // namespace test
} // namespace http
} // namespace isc

#endif
