// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/request.h>
#include <http/date_time.h>
#include <http/http_header.h>
#include <http/http_types.h>
#include <http/tests/request_test.h>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>
#include <utility>

using namespace isc::http;
using namespace isc::http::test;

namespace {

/// @brief Test fixture class for @c HttpRequest class.
class HttpRequestTest : public HttpRequestTestBase<HttpRequest> {
public:

    /// @brief Tests connection persistence for the given HTTP version
    /// and header value.
    ///
    /// This method creates a dummy HTTP request and sets the specified
    /// version and header. Next, it returns the value if @c isPersistent
    /// method for this request. The unit test verifies this value for
    /// correctness.
    ///
    /// @param http_version HTTP version.
    /// @param http_header HTTP header to be included in the request. If
    /// the header has an empty value, it is not included.
    ///
    /// @return true if request indicates that connection is to be
    /// persistent.
    bool isPersistent(const HttpVersion& http_version,
                      const HttpHeader& http_header = HttpHeader("Connection")) {
        try {
            // We need to add some JSON body.
            std::string json_body = "{ \"param1\": \"foo\" }";

            // Set method, path, version and content length.
            setContextBasics("POST", "/isc/org", http_version);
            addHeaderToContext("Content-Length", json_body.length());

            // If additional header has been specified (typically "Connection"),
            // include it.
            if (!http_header.getValue().empty()) {
                addHeaderToContext(http_header.getName(), http_header.getValue());
            }
            // Attach JSON body.
            request_.context()->body_ = json_body;
            request_.create();

        } catch (...) {
            ADD_FAILURE() << "failed to create HTTP request while testing"
                " connection persistence";
        }

        return (request_.isPersistent());
    }

};

TEST_F(HttpRequestTest, minimal) {
    setContextBasics("GET", "/isc/org", HttpVersion(1, 1));
    ASSERT_NO_THROW(request_.create());

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/isc/org", request_.getUri());
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);

    EXPECT_THROW(request_.getHeaderValue("Content-Length"),
                 HttpMessageNonExistingHeader);
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

    EXPECT_THROW(static_cast<void>(request_.getMethod()), HttpMessageError);
    EXPECT_THROW(static_cast<void>(request_.getHttpVersion()),
                 HttpMessageError);
    EXPECT_THROW(static_cast<void>(request_.getUri()), HttpMessageError);
    EXPECT_THROW(static_cast<void>(request_.getHeaderValue("Content-Type")),
                 HttpMessageError);
    EXPECT_THROW(static_cast<void>(request_.getHeaderValueAsUint64("Content-Length")),
                 HttpMessageError);
    EXPECT_THROW(static_cast<void>(request_.getBody()), HttpMessageError);

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

TEST_F(HttpRequestTest, isPersistentHttp10) {
    // In HTTP 1.0 the connection is by default non-persistent.
    EXPECT_FALSE(isPersistent(HttpVersion(1, 0)));
}

TEST_F(HttpRequestTest, isPersistentHttp11) {
    // In HTTP 1.1 the connection is by default persistent.
    EXPECT_TRUE(isPersistent(HttpVersion(1, 1)));
}

TEST_F(HttpRequestTest, isPersistentHttp10KeepAlive) {
    // In HTTP 1.0 the client indicates that the connection is desired to be
    // persistent by including "Connection: keep-alive" header.
    EXPECT_TRUE(
        isPersistent(HttpVersion(1, 0), HttpHeader("Connection", "Keep-alive"))
    );
}

TEST_F(HttpRequestTest, isPersistentHttp11Close) {
    // In HTTP 1.1 the client would include "Connection: close" header if it
    // desires to close the connection.
    EXPECT_FALSE(
        isPersistent(HttpVersion(1, 1), HttpHeader("Connection", "close"))
    );
}

TEST_F(HttpRequestTest, clientRequest) {
    request_.setDirection(HttpMessage::OUTBOUND);
    setContextBasics("POST", "/isc/org", HttpVersion(1, 0));

    // Capture current date and time.
    HttpDateTime date_time;

    // Add headers.
    request_.context()->headers_.push_back(HttpHeaderContext("Date", date_time.rfc1123Format()));
    request_.context()->headers_.push_back(HttpHeaderContext("Content-Type", "text/html"));
    request_.context()->headers_.push_back(HttpHeaderContext("Accept", "text/html"));
    // Add a body.
    request_.context()->body_ = "<html></html>";
    // Commit and validate the data.
    ASSERT_NO_THROW(request_.finalize());

    // Check that the HTTP request in the textual format is correct. Note that
    // it should include "Content-Length", even though we haven't explicitly set
    // this header. It is dynamically computed from the body size.
    EXPECT_EQ("POST /isc/org HTTP/1.0\r\n"
              "Accept: text/html\r\n"
              "Content-Length: 13\r\n"
              "Content-Type: text/html\r\n"
              "Date: " + date_time.rfc1123Format() + "\r\n"
              "\r\n"
              "<html></html>",
              request_.toString());
}

TEST_F(HttpRequestTest, clientRequestNoBody) {
    setContextBasics("GET", "/isc/org", HttpVersion(1, 1));
    // Add headers.
    request_.context()->headers_.push_back(HttpHeaderContext("Content-Type", "text/html"));
    // Commit and validate the data.
    ASSERT_NO_THROW(request_.finalize());

    // Check that the HTTP request in the textual format is correct. Note that
    // there should be no Content-Length included, because the body is empty.
    EXPECT_EQ("GET /isc/org HTTP/1.1\r\n"
              "Content-Type: text/html\r\n"
              "\r\n",
              request_.toString());
}

TEST_F(HttpRequestTest, toBriefString) {
    // Create the request.
    setContextBasics("POST", "/isc/org", HttpVersion(1, 1));
    // Add headers.
    request_.context()->headers_.push_back(HttpHeaderContext("Content-Type", "application/json"));
    // Must be finalized before can be used.
    ASSERT_NO_THROW(request_.finalize());
    // Check that the brief string is correct.
    EXPECT_EQ("POST /isc/org HTTP/1.1", request_.toBriefString());
}

}
