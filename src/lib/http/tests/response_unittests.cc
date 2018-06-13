// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Response type used in tests.
typedef TestHttpResponseBase<HttpResponse> TestHttpResponse;

/// @brief Test fixture class for @ref HttpResponse.
class HttpResponseTest : public ::testing::Test {
public:

    /// @brief Checks if the format of the response is correct.
    ///
    /// @param status_code HTTP status code in the response.
    /// @param status_message HTTP status message in the response.
    void testResponse(const HttpStatusCode& status_code,
                      const std::string& status_message) {
        // Create the response. Because we're using derived class
        // it returns the fixed value of the Date header, which is
        // very useful in unit tests.
        TestHttpResponse response(HttpVersion(1, 0), status_code);
        response.context()->headers_.push_back(HttpHeaderContext("Content-Type", "text/html"));
        ASSERT_NO_THROW(response.finalize());
        std::ostringstream response_string;
        response_string << "HTTP/1.0 " << static_cast<uint16_t>(status_code)
            << " " << status_message;
        EXPECT_EQ(response_string.str(), response.toBriefString());

        response_string
            << "\r\nContent-Length: 0\r\n"
            << "Content-Type: text/html\r\n"
            << "Date: " << response.getDateHeaderValue() << "\r\n\r\n";
        EXPECT_EQ(response_string.str(), response.toString());
    }
};

// Test the case of HTTP OK message.
TEST_F(HttpResponseTest, responseOK) {
    // Include HTML body.
    const std::string sample_body =
        "<html>"
        "<head><title>Kea page title</title></head>"
        "<body><h1>Some header</h1></body>"
        "</html>";

    // Create the message and add some headers.
    TestHttpResponse response(HttpVersion(1, 0), HttpStatusCode::OK);
    response.context()->headers_.push_back(HttpHeaderContext("Content-Type", "text/html"));
    response.context()->headers_.push_back(HttpHeaderContext("Host", "kea.example.org"));
    response.context()->body_ = sample_body;
    ASSERT_NO_THROW(response.finalize());

    // Create a string holding expected response. Note that the Date
    // is a fixed value returned by the customized TestHttpResponse
    // class.
    std::ostringstream response_string;
    response_string <<
        "HTTP/1.0 200 OK\r\n"
        "Content-Length: " << sample_body.length() << "\r\n"
        "Content-Type: text/html\r\n"
        "Date: " << response.getDateHeaderValue() << "\r\n"
        "Host: kea.example.org\r\n\r\n" << sample_body;

    EXPECT_EQ(response_string.str(), response.toString());
}

// Test generic responses for various status codes.
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
    testResponse(HttpStatusCode::REQUEST_TIMEOUT, "Request Timeout");
    testResponse(HttpStatusCode::INTERNAL_SERVER_ERROR, "Internal Server Error");
    testResponse(HttpStatusCode::NOT_IMPLEMENTED, "Not Implemented");
    testResponse(HttpStatusCode::BAD_GATEWAY, "Bad Gateway");
    testResponse(HttpStatusCode::SERVICE_UNAVAILABLE, "Service Unavailable");
}

// Test if the class correctly identifies client errors.
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
    EXPECT_TRUE(HttpResponse::isClientError(HttpStatusCode::REQUEST_TIMEOUT));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::INTERNAL_SERVER_ERROR));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::NOT_IMPLEMENTED));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::BAD_GATEWAY));
    EXPECT_FALSE(HttpResponse::isClientError(HttpStatusCode::SERVICE_UNAVAILABLE));
}

// Test if the class correctly identifies server errors.
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
    EXPECT_FALSE(HttpResponse::isServerError(HttpStatusCode::REQUEST_TIMEOUT));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::INTERNAL_SERVER_ERROR));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::NOT_IMPLEMENTED));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::BAD_GATEWAY));
    EXPECT_TRUE(HttpResponse::isServerError(HttpStatusCode::SERVICE_UNAVAILABLE));
}

// Test that the generated time value, being included in the Date
// header, is correct.
TEST_F(HttpResponseTest, getDateHeaderValue) {
    // Create a response and retrieve the value to be included in the
    // Date header. This value should hold a current time in the
    // RFC1123 format.
    TestHttpResponse response(HttpVersion(1, 0), HttpStatusCode::OK);
    std::string generated_date = response.generateDateHeaderValue();

    // Use our date/time utilities to parse this value into the ptime.
    HttpDateTime parsed_time = HttpDateTime::fromRfc1123(generated_date);

    // Now that we have it converted back, we can check how far this
    // value is from the current time. To be on the safe side, we check
    // that it is not later than 10 seconds apart, rather than checking
    // it for equality. In fact, checking it for equality would almost
    // certainly cause an error. Especially on a virtual machine.
    time_duration parsed_to_current =
        microsec_clock::universal_time() - parsed_time.getPtime();
    EXPECT_LT(parsed_to_current.seconds(), 10);
}

}
