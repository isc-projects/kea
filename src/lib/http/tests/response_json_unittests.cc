// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <http/response_json.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc::data;
using namespace isc::http;

namespace {

class HttpResponseJsonTest : public ::testing::Test {
public:

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

    void testGenericResponse(const HttpStatusCode& status_code,
                             const std::string& status_message) {
        HttpResponseJson response(HttpVersion(1, 0), status_code);
        std::ostringstream status_message_json;
        status_message_json << "{ \"result\": "
                            << static_cast<uint16_t>(status_code)
                            << ", \"text\": "
                            << "\"" << status_message << "\" }";
        std::ostringstream response_string;
        response_string <<
            "HTTP/1.0 " << static_cast<uint16_t>(status_code) << " "
            << status_message << "\r\n"
            "Content-Type: application/json\r\n";

        if (HttpResponse::isClientError(status_code) ||
            HttpResponse::isServerError(status_code)) {
            response_string << "Content-Length: " << status_message_json.str().size()
                            << "\r\n";
        }

        response_string << "\r\n";

        if (HttpResponse::isClientError(status_code) ||
            HttpResponse::isServerError(status_code)) {
            response_string << status_message_json.str();
        }

        EXPECT_EQ(response_string.str(), response.toString());
    }

    ConstElementPtr json_;
    std::string json_string_;
    std::string json_string_from_json_;

};

TEST_F(HttpResponseJsonTest, responseWithContent) {
    HttpResponseJson response(HttpVersion(1, 1), HttpStatusCode::OK);
    ASSERT_NO_THROW(response.setBodyAsJson(json_));

    std::ostringstream response_string;
    response_string <<
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: " << json_string_from_json_.length()
                    << "\r\n\r\n" << json_string_from_json_;
    EXPECT_EQ(response_string.str(), response.toString());
}

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
    testGenericResponse(HttpStatusCode::INTERNAL_SERVER_ERROR,
                        "Internal Server Error");
    testGenericResponse(HttpStatusCode::NOT_IMPLEMENTED, "Not Implemented");
    testGenericResponse(HttpStatusCode::BAD_GATEWAY, "Bad Gateway");
    testGenericResponse(HttpStatusCode::SERVICE_UNAVAILABLE,
                        "Service Unavailable");
}

}
