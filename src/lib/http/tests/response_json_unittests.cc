// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <http/http_types.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;

namespace {

/// @brief Response type used in tests.
typedef TestHttpResponseBase<HttpResponseJson> TestHttpResponseJson;

/// @brief Test fixture class for @ref HttpResponseJson.
class HttpResponseJsonTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Initializes the following class members:
    /// - json_string_ - which is a pretty formatted JSON content,
    /// - json_ - A structure of Element objects representing the JSON,
    /// - json_string_from_json_ - which is a JSON text converted back from
    ///   the json_ data structure. It is the same content as json_string_
    ///   but has different whitespaces.
    HttpResponseJsonTest()
        : json_(), json_string_(), json_string_from_json_() {
        json_string_ =
            "["
            "  {"
            "    \"pid\": 8080,"
            "    \"status\": 10,"
            "    \"comment\": \"Nice comment from 8080\""
            "  },"
            "  {"
            "    \"pid\": 8081,"
            "    \"status\": 12,"
            "    \"comment\": \"A comment from 8081\""
            "  }"
            "]";

        json_ = Element::fromJSON(json_string_);
        json_string_from_json_ = json_->str();
    }

    /// @brief Test that the response format is correct.
    ///
    /// @param status_code HTTP status code for which the response should
    /// be tested.
    /// @param status_message HTTP status message.
    void testGenericResponse(const HttpStatusCode& status_code,
                             const std::string& status_message) {
        TestHttpResponseJson response(HttpVersion(1, 0), status_code);
        ASSERT_NO_THROW(response.finalize());
        std::ostringstream status_message_json;
        // Build the expected content.
        status_message_json << "{ \"result\": "
                            << static_cast<uint16_t>(status_code)
                            << ", \"text\": "
                            << "\"" << status_message << "\" }";
        std::ostringstream response_string;
        response_string <<
            "HTTP/1.0 " << static_cast<uint16_t>(status_code) << " "
            << status_message << "\r\n";

        // The content must only be generated for error codes.
        if (HttpResponse::isClientError(status_code) ||
            HttpResponse::isServerError(status_code)) {
            response_string << "Content-Length: " << status_message_json.str().size()
                            << "\r\n";
        } else {
            response_string << "Content-Length: 0\r\n";
        }

        // Content-Type and Date are automatically included.
        response_string << "Content-Type: application/json\r\n"
            "Date: " << response.getDateHeaderValue() << "\r\n\r\n";

        if (HttpResponse::isClientError(status_code) ||
            HttpResponse::isServerError(status_code)) {
            response_string << status_message_json.str();
        }

        // Check that the output is as expected.
        EXPECT_EQ(response_string.str(), response.toString());
    }

    /// @brief JSON content represented as structure of Element objects.
    ConstElementPtr json_;

    /// @brief Pretty formatted JSON content.
    std::string json_string_;

    /// @brief JSON content parsed back from json_ structure.
    std::string json_string_from_json_;

};

// Test that the response with custom JSON content is generated properly.
TEST_F(HttpResponseJsonTest, responseWithContent) {
    TestHttpResponseJson response(HttpVersion(1, 1), HttpStatusCode::OK);
    ASSERT_NO_THROW(response.setBodyAsJson(json_));
    ASSERT_NO_THROW(response.finalize());

    std::ostringstream response_string;
    response_string <<
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: " << json_string_from_json_.length() << "\r\n"
        "Content-Type: application/json\r\n"
        "Date: " << response.getDateHeaderValue() << "\r\n\r\n"
                    << json_string_from_json_;
    EXPECT_EQ(response_string.str(), response.toString());
}

// Test that generic responses are created properly.
TEST_F(HttpResponseJsonTest, genericResponse) {
    testGenericResponse(HttpStatusCode::OK, "OK");
    testGenericResponse(HttpStatusCode::CREATED, "Created");
    testGenericResponse(HttpStatusCode::ACCEPTED, "Accepted");
    testGenericResponse(HttpStatusCode::NO_CONTENT, "No Content");
    testGenericResponse(HttpStatusCode::MULTIPLE_CHOICES,
                        "Multiple Choices");
    testGenericResponse(HttpStatusCode::MOVED_PERMANENTLY,
                        "Moved Permanently");
    testGenericResponse(HttpStatusCode::MOVED_TEMPORARILY,
                        "Moved Temporarily");
    testGenericResponse(HttpStatusCode::NOT_MODIFIED, "Not Modified");
    testGenericResponse(HttpStatusCode::BAD_REQUEST, "Bad Request");
    testGenericResponse(HttpStatusCode::UNAUTHORIZED, "Unauthorized");
    testGenericResponse(HttpStatusCode::FORBIDDEN, "Forbidden");
    testGenericResponse(HttpStatusCode::NOT_FOUND, "Not Found");
    testGenericResponse(HttpStatusCode::REQUEST_TIMEOUT, "Request Timeout");
    testGenericResponse(HttpStatusCode::INTERNAL_SERVER_ERROR,
                        "Internal Server Error");
    testGenericResponse(HttpStatusCode::NOT_IMPLEMENTED, "Not Implemented");
    testGenericResponse(HttpStatusCode::BAD_GATEWAY, "Bad Gateway");
    testGenericResponse(HttpStatusCode::SERVICE_UNAVAILABLE,
                        "Service Unavailable");
}

}
