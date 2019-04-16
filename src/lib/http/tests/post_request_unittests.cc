// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/post_request.h>
#include <http/tests/request_test.h>
#include <gtest/gtest.h>

using namespace isc::http;
using namespace isc::http::test;

namespace {

/// @brief Test fixture class for @ref PostHttpRequest.
class PostHttpRequestTest : public HttpRequestTestBase<PostHttpRequest> {
public:

    /// @brief Constructor.
    PostHttpRequestTest()
        : HttpRequestTestBase<PostHttpRequest>(),
        json_body_("{ \"service\": \"dhcp4\", \"param1\": \"foo\" }") {
    }

    /// @brief Default value of the JSON body.
    std::string json_body_;
};

// This test verifies that PostHttpRequest class only accepts POST
// messages.
TEST_F(PostHttpRequestTest, requirePost) {
    // Use a GET method that is not supported.
    setContextBasics("GET", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");

    ASSERT_THROW(request_->create(), HttpRequestError);

    // Now use POST. It should be accepted.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");

    EXPECT_NO_THROW(request_->create());
}

// This test verifies that PostHttpRequest requires "Content-Length"
// header.
TEST_F(PostHttpRequestTest, requireContentType) {
    // No "Content-Type". It should fail.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());

    ASSERT_THROW(request_->create(), HttpRequestError);

    // There is "Content-Type". It should pass.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "text/html");

    EXPECT_NO_THROW(request_->create());

}

// This test verifies that PostHttpRequest requires "Content-Type"
// header.
TEST_F(PostHttpRequestTest, requireContentLength) {
    // No "Content-Length". It should fail.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Type", "text/html");

    ASSERT_THROW(request_->create(), HttpRequestError);

    // There is "Content-Length". It should pass.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");
}

}
