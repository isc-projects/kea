// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <http/http_types.h>
#include <http/post_request_json.h>
#include <http/tests/request_test.h>
#include <gtest/gtest.h>
#include <map>
#include <sstream>

using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;

namespace {

/// @brief Test fixture class for @ref PostHttpRequestJson.
class PostHttpRequestJsonTest :
        public HttpRequestTestBase<PostHttpRequestJson> {
public:

    /// @brief Constructor.
    PostHttpRequestJsonTest()
        : HttpRequestTestBase<PostHttpRequestJson>(),
        json_body_("{ \"service\": \"dhcp4\", \"param1\": \"foo\" }") {
    }

    /// @brief Sets new JSON body for the HTTP request context.
    ///
    /// If the body parameter is empty, it will use the value of
    /// @ref json_body_ member. Otherwise, it will assign the body
    /// provided as parameter.
    ///
    /// @param body new body value.
    void setBody(const std::string& body = "") {
        request_->context()->body_ = body.empty() ? json_body_ : body;
    }

    /// @brief Default value of the JSON body.
    std::string json_body_;
};

// This test verifies that PostHttpRequestJson class only accepts
// POST messages.
TEST_F(PostHttpRequestJsonTest, requiredPost) {
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
// header equal to "application/json".
TEST_F(PostHttpRequestJsonTest, requireContentTypeJson) {
    // Specify "Content-Type" other than "application/json".
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "text/html");

    ASSERT_THROW(request_->create(), HttpRequestError);

    // This time specify correct "Content-Type". It should pass.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");

    EXPECT_NO_THROW(request_->create());
}

// This test verifies that PostHttpRequest requires "Content-Length"
// header.
TEST_F(PostHttpRequestJsonTest, requireContentLength) {
    // "Content-Length" is not specified initially. It should fail.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Type", "text/html");

    ASSERT_THROW(request_->create(), HttpRequestError);

    // Specify "Content-Length". It should pass.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");
}

// This test verifies that JSON body can be retrieved from the
// HTTP request.
TEST_F(PostHttpRequestJsonTest, getBodyAsJson) {
    // Create HTTP POST request with JSON body.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");
    setBody();

    ASSERT_NO_THROW(request_->finalize());

    // Try to retrieve pointer to the root element of the JSON body.
    ConstElementPtr json = request_->getBodyAsJson();
    ASSERT_TRUE(json);

    // Iterate over JSON values and store them in a simple map.
    std::map<std::string, std::string> config_values;
    for (auto config_element = json->mapValue().begin();
         config_element != json->mapValue().end();
         ++config_element) {
        ASSERT_FALSE(config_element->first.empty());
        ASSERT_TRUE(config_element->second);
        config_values[config_element->first] = config_element->second->stringValue();
    }

    // Verify the values.
    EXPECT_EQ("dhcp4", config_values["service"]);
    EXPECT_EQ("foo", config_values["param1"]);
}

// This test verifies that an attempt to parse/retrieve malformed
// JSON structure will cause an exception.
TEST_F(PostHttpRequestJsonTest, getBodyAsJsonMalformed) {
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");
    // No colon before 123.
    setBody("{ \"command\" 123 }" );

    EXPECT_THROW(request_->finalize(), HttpRequestJsonError);
}

// This test verifies that NULL pointer is returned when trying to
// retrieve root element of the empty JSON structure.
TEST_F(PostHttpRequestJsonTest, getEmptyJsonBody) {
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");

    ASSERT_NO_THROW(request_->finalize());

    ConstElementPtr json = request_->getBodyAsJson();
    EXPECT_FALSE(json);
}

// This test verifies that the specific JSON element can be retrieved.
TEST_F(PostHttpRequestJsonTest, getJsonElement) {
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Length", json_body_.length());
    addHeaderToContext("Content-Type", "application/json");
    setBody();

    ASSERT_NO_THROW(request_->finalize());

    ConstElementPtr element;
    ASSERT_NO_THROW(element = request_->getJsonElement("service"));
    ASSERT_TRUE(element);
    EXPECT_EQ("dhcp4", element->stringValue());

    // An attempt to retrieve non-existing element should return NULL.
    EXPECT_FALSE(request_->getJsonElement("bar"));
}

// This test verifies that it is possible to create client side request
// containing JSON body.
TEST_F(PostHttpRequestJsonTest, clientRequest) {
    request_->setDirection(HttpMessage::OUTBOUND);

    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));
    addHeaderToContext("Content-Type", "application/json");

    ElementPtr json = Element::fromJSON(json_body_);
    request_->setBodyAsJson(json);

    // Commit and validate the data.
    ASSERT_NO_THROW(request_->finalize());

    std::ostringstream expected_request_text;
    expected_request_text << "POST /isc/org HTTP/1.0\r\n"
        "Content-Length: " << json->str().size() << "\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        << json->str();

    EXPECT_EQ(expected_request_text.str(), request_->toString());
}

}
