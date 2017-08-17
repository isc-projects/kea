// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/request.h>
#include <http/http_types.h>
#include <http/tests/request_test.h>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>
#include <utility>

using namespace isc::http;
using namespace isc::http::test;

namespace {

typedef HttpRequestTestBase<HttpRequest> HttpRequestTest;

TEST_F(HttpRequestTest, minimal) {
    setContextBasics("GET", "/isc/org", HttpVersion(1, 1));
    ASSERT_NO_THROW(request_.create());

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/isc/org", request_.getUri());
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);

    EXPECT_THROW(request_.getHeaderValue("Content-Length"),
                 HttpRequestNonExistingHeader);
}

TEST_F(HttpRequestTest, includeHeaders) {
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", "1024");
    addHeaderToContext("Content-Type", "application/json");
    ASSERT_NO_THROW(request_.create());

    EXPECT_EQ(HttpRequest::Method::HTTP_POST, request_.getMethod());
    EXPECT_EQ("/isc/org", request_.getUri());
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(0, request_.getHttpVersion().minor_);

    std::string content_type;
    ASSERT_NO_THROW(content_type = request_.getHeaderValue("Content-Type"));
    EXPECT_EQ("application/json", content_type);

    uint64_t content_length;
    ASSERT_NO_THROW(
        content_length = request_.getHeaderValueAsUint64("Content-Length")
    );
    EXPECT_EQ(1024, content_length);
}

TEST_F(HttpRequestTest, requiredMethods) {
    request_.requireHttpMethod(HttpRequest::Method::HTTP_GET);
    request_.requireHttpMethod(HttpRequest::Method::HTTP_POST);

    setContextBasics("GET", "/isc/org", HttpVersion(1, 1));

    ASSERT_NO_THROW(request_.create());

    request_.context()->method_ = "POST";
    ASSERT_NO_THROW(request_.create());

    request_.context()->method_ = "PUT";
    EXPECT_THROW(request_.create(), HttpRequestError);
}

TEST_F(HttpRequestTest, requiredHttpVersion) {
    request_.requireHttpVersion(HttpVersion(1, 0));
    request_.requireHttpVersion(HttpVersion(1, 1));

    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    EXPECT_NO_THROW(request_.create());

    setContextBasics("POST", "/isc/org", HttpVersion(1, 1));
    EXPECT_NO_THROW(request_.create());

    setContextBasics("POST", "/isc/org", HttpVersion(2, 0));
    EXPECT_THROW(request_.create(), HttpRequestError);
}

TEST_F(HttpRequestTest, requiredHeader) {
    request_.requireHeader("Content-Length");
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));

    ASSERT_THROW(request_.create(), HttpRequestError);

    addHeaderToContext("Content-Type", "application/json");
    ASSERT_THROW(request_.create(), HttpRequestError);

    addHeaderToContext("Content-Length", "2048");
    EXPECT_NO_THROW(request_.create());
}

TEST_F(HttpRequestTest, requiredHeaderValue) {
    request_.requireHeaderValue("Content-Type", "application/json");
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Type", "text/html");

    ASSERT_THROW(request_.create(), HttpRequestError);

    addHeaderToContext("Content-Type", "application/json");

    EXPECT_NO_THROW(request_.create());
}

TEST_F(HttpRequestTest, notCreated) {
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Type", "text/html");
    addHeaderToContext("Content-Length", "1024");

    EXPECT_THROW(static_cast<void>(request_.getMethod()), HttpRequestError);
    EXPECT_THROW(static_cast<void>(request_.getHttpVersion()),
                 HttpRequestError);
    EXPECT_THROW(static_cast<void>(request_.getUri()), HttpRequestError);
    EXPECT_THROW(static_cast<void>(request_.getHeaderValue("Content-Type")),
                 HttpRequestError);
    EXPECT_THROW(static_cast<void>(request_.getHeaderValueAsUint64("Content-Length")),
                 HttpRequestError);
    EXPECT_THROW(static_cast<void>(request_.getBody()), HttpRequestError);

    ASSERT_NO_THROW(request_.finalize());

    EXPECT_NO_THROW(static_cast<void>(request_.getMethod()));
    EXPECT_NO_THROW(static_cast<void>(request_.getHttpVersion()));
    EXPECT_NO_THROW(static_cast<void>(request_.getUri()));
    EXPECT_NO_THROW(static_cast<void>(request_.getHeaderValue("Content-Type")));
    EXPECT_NO_THROW(
        static_cast<void>(request_.getHeaderValueAsUint64("Content-Length"))
    );
    EXPECT_NO_THROW(static_cast<void>(request_.getBody()));
}

TEST_F(HttpRequestTest, getBody) {
    std::string json_body = "{ \"param1\": \"foo\" }";

    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body.length());

    request_.context()->body_ = json_body;

    ASSERT_NO_THROW(request_.finalize());

    EXPECT_EQ(json_body, request_.getBody());
}

TEST_F(HttpRequestTest, requiresBody) {
    ASSERT_FALSE(request_.requiresBody());
    request_.requireHeader("Content-Length");
    EXPECT_TRUE(request_.requiresBody());
}

}
