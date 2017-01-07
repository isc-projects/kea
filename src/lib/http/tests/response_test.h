// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_TEST_H
#define HTTP_RESPONSE_TEST_H

#include <http/http_types.h>
#include <http/response.h>

namespace isc {
namespace http {
namespace test {

template<typename HttpResponseType>
class TestHttpResponseBase : public HttpResponseType {
public:

    TestHttpResponseBase(const HttpVersion& version, const HttpStatusCode& status_code)
        : HttpResponseType(version, status_code) {
    }

    virtual std::string getDateHeaderValue() const {
        return ("Tue, 19 Dec 2016 18:53:35 GMT");
    }

    std::string generateDateHeaderValue() const {
        return (HttpResponseType::getDateHeaderValue());
    }
};

} // namespace test
} // namespace http
} // namespace isc

#endif
