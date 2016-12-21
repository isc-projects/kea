// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/request.h>
#include <http/response.h>
#include <http/response_creator.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc::http;
using namespace isc::http::test;

namespace {

typedef TestHttpResponseBase<HttpResponseJson> Response;
typedef boost::shared_ptr<Response> ResponsePtr;

class TestHttpResponseCreator : public HttpResponseCreator {
private:

    virtual HttpResponsePtr
    createStockBadRequest(const ConstHttpRequestPtr& request) const {
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        ResponsePtr response(new Response(http_version,
                                          HttpStatusCode::BAD_REQUEST));
        return (response);
    }

    virtual HttpResponsePtr
    createDynamicHttpResponse(const ConstHttpRequestPtr& request) {
        ResponsePtr response(new Response(request->getHttpVersion(),
                                          HttpStatusCode::OK));
        return (response);
    }
};

TEST(HttpResponseCreatorTest, badRequest) {
    HttpResponsePtr response;
    HttpRequestPtr request(new HttpRequest());
    TestHttpResponseCreator creator;
    ASSERT_NO_THROW(response = creator.createHttpResponse(request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/0.0 400 Bad Request\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "Content-Length: 40\r\n\r\n"
              "{ \"result\": 400, \"text\": \"Bad Request\" }", response->toString());
}

TEST(HttpResponseCreatorTest, goodRequest) {
    HttpResponsePtr response;
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    ASSERT_NO_THROW(request->finalize());

    TestHttpResponseCreator creator;
    ASSERT_NO_THROW(response = creator.createHttpResponse(request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 200 OK\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n\r\n",
              response->toString());
}

}
