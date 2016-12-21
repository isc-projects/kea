// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/date_time.h>
#include <http/http_types.h>
#include <http/response.h>
#include <http/tests/response_test.h>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace boost::posix_time;
using namespace isc::http;
using namespace isc::http::test;

namespace {

typedef TestHttpResponseBase<HttpResponse> TestHttpResponse;

class HttpResponseTest : public ::testing::Test {
public:

    void testResponse(const HttpStatusCode& status_code,
                      const std::string& status_message) {
        TestHttpResponse response(HttpVersion(1, 0), status_code);
        response.addHeader("Content-Type", "text/html");
        std::ostringstream response_string;
        response_string << "HTTP/1.0 " << static_cast<uint16_t>(status_code)
            << " " << status_message << "\r\n"
            << "Content-Type: text/html\r\n"
            << "Date: " << response.getDateHeaderValue() << "\r\n\r\n";

        EXPECT_EQ(response_string.str(), response.toString());
    }

};

TEST_F(HttpResponseTest, responseOK) {
    const std::string sample_body =
        "<html>"
        "<head><title>Kea page title</title></head>"
        "<body><h1>Some header</h1></body>"
        "</html>";

    TestHttpResponse response(HttpVersion(1, 0), HttpStatusCode::OK);
    response.addHeader("Content-Type", "text/html");
    response.addHeader("Host", "kea.example.org");
    response.setBody(sample_body);

    std::ostringstream response_string;
    response_string <<
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Host: kea.example.org\r\n"
        "Date: " << response.getDateHeaderValue() << "\r\n"
        "Content-Length: " << sample_body.length()
                    << "\r\n\r\n" << sample_body;
    EXPECT_EQ(response_string.str(), response.toString());
}

TEST_F(HttpResponseTest, genericResponse) {
    testResponse(HttpStatusCode::OK, "OK");
    testResponse(HttpStatusCode::CREATED, "Created");
    testResponse(HttpStatusCode::ACCEPTED, "Accepted");
    testResponse(HttpStatusCode::NO_CONTENT, "No Content");
    testResponse(HttpStatusCode::MULTIPLE_CHOICES, "Multiple Choices");
    testResponse(HttpStatusCode::MOVED_PERMANENTLY, "Moved Permanently");
    testResponse(HttpStatusCode::MOVED_TEMPORARILY, "Moved Temporarily");
    testResponse(HttpStatusCode::NOT_MODIFIED, "Not Modified");
    testResponse(HttpStatusCode::BAD_REQUEST, "Bad Request");
    testResponse(HttpStatusCode::UNAUTHORIZED, "Unauthorized");
    testResponse(HttpStatusCode::FORBIDDEN, "Forbidden");
    testResponse(HttpStatusCode::NOT_FOUND, "Not Found");
    testResponse(HttpStatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error");
    testResponse(HttpStatusCode::NOT_IMPLEMENTED, "Not Implemented");
    testResponse(HttpStatusCode::BAD_GATEWAY, "Bad Gateway");
    testResponse(HttpStatusCode::SERVICE_UNAVAILABLE, "Service Unavailable");
}

TEST_F(HttpResponseTest, isClientError) {
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::OK));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::CREATED));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::ACCEPTED));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::NO_CONTENT));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::MULTIPLE_CHOICES));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::MOVED_PERMANENTLY));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::MOVED_TEMPORARILY));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::NOT_MODIFIED));
    EXPECT_TRUE(HttpResponse::isClientError(HttpStatusCode::BAD_REQUEST));
    EXPECT_TRUE(HttpResponse::isClientError(HttpStatusCode::UNAUTHORIZED));
    EXPECT_TRUE(HttpResponse::isClientError(HttpStatusCode::FORBIDDEN));
    EXPECT_TRUE(HttpResponse::isClientError(HttpStatusCode::NOT_FOUND));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::INTERNAL_SERVER_ERROR));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::NOT_IMPLEMENTED));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::BAD_GATEWAY));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::SERVICE_UNAVAILABLE));
}

TEST_F(HttpResponseTest, isServerError) {
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::OK));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::CREATED));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::ACCEPTED));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::NO_CONTENT));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::MULTIPLE_CHOICES));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::MOVED_PERMANENTLY));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::MOVED_TEMPORARILY));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::NOT_MODIFIED));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::BAD_REQUEST));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::UNAUTHORIZED));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::FORBIDDEN));
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::NOT_FOUND));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::INTERNAL_SERVER_ERROR));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::NOT_IMPLEMENTED));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::BAD_GATEWAY));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::SERVICE_UNAVAILABLE));
}

TEST_F(HttpResponseTest, getDateHeaderValue) {
    TestHttpResponse response(HttpVersion(1, 0), HttpStatusCode::OK);
    std::string generated_date = response.generateDateHeaderValue();
    HttpDateTime parsed_time = HttpDateTime::fromRfc1123(generated_date);
    time_duration parsed_to_current =
        microsec_clock::universal_time() - parsed_time.getPtime();
    EXPECT_LT(parsed_to_current.seconds(), 10);
}

}
