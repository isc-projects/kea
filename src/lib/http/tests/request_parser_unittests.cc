// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <http/http_types.h>
#include <http/request_parser.h>
#include <http/post_request_json.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc::data;
using namespace isc::http;

namespace {

/// @brief Test fixture class for @ref HttpRequestParser.
class HttpRequestParserTest : public ::testing::Test {
public:

    /// @brief Creates HTTP request string.
    ///
    /// @param preamble A string including HTTP request's first line
    /// and all headers except "Content-Length".
    /// @param payload A string containing HTTP request payload.
    std::string createRequestString(const std::string& preamble,
                                    const std::string& payload) {
        std::ostringstream s;
        s << preamble;
        s << "Content-Length: " << payload.length() << "\r\n\r\n"
          << payload;
        return (s.str());
    }

    /// @brief Parses the HTTP request and checks that parsing was
    /// successful.
    ///
    /// @param http_req HTTP request string.
    void doParse(const std::string& http_req) {
        HttpRequestParser parser(request_);
        ASSERT_NO_THROW(parser.initModel());

        parser.postBuffer(&http_req[0], http_req.size());
        ASSERT_NO_THROW(parser.poll());

        ASSERT_FALSE(parser.needData());
        ASSERT_TRUE(parser.httpParseOk());
        EXPECT_TRUE(parser.getErrorMessage().empty());
    }

    /// @brief Tests that parsing fails when malformed HTTP request
    /// is received.
    ///
    /// @param http_req HTTP request string.
    void testInvalidHttpRequest(const std::string& http_req) {
        HttpRequestParser parser(request_);
        ASSERT_NO_THROW(parser.initModel());

        parser.postBuffer(&http_req[0], http_req.size());
        ASSERT_NO_THROW(parser.poll());

        EXPECT_FALSE(parser.needData());
        EXPECT_FALSE(parser.httpParseOk());
        EXPECT_FALSE(parser.getErrorMessage().empty());
    }

    /// @brief Instance of the HttpRequest used by the unit tests.
    HttpRequest request_;
};

// Test test verifies that an HTTP request including JSON body is parsed
// successfully.
TEST_F(HttpRequestParserTest, postHttpRequestWithJson) {
    std::string http_req = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n";
    std::string json = "{ \"service\": \"dhcp4\", \"command\": \"shutdown\" }";

    http_req = createRequestString(http_req, json);

    // Create HTTP request which accepts POST method and JSON as a body.
    PostHttpRequestJson request;

    // Create a parser and make it use the request we created.
    HttpRequestParser parser(request);
    ASSERT_NO_THROW(parser.initModel());

    // Simulate receiving HTTP request in chunks.
    for (size_t i = 0; i < http_req.size(); i += http_req.size() / 10) {
        bool done = false;
        // Get the size of the data chunk. 
        size_t chunk = http_req.size() / 10;
        // When we're near the end of the data stream, the chunk length may
        // vary.
        if (i + chunk > http_req.size()) {
            chunk = http_req.size() - i;
            done = true;
        }
        // Feed the parser with a data chunk and parse it.
        parser.postBuffer(&http_req[i], chunk);
        parser.poll();
        if (!done) {
            ASSERT_TRUE(parser.needData());
        }
    }

    // Parser should have parsed the request and should expect no more data.
    ASSERT_FALSE(parser.needData());
    // Parsing should be successful.
    ASSERT_TRUE(parser.httpParseOk());
    // There should be no error message.
    EXPECT_TRUE(parser.getErrorMessage().empty());

    // Verify parsed headers etc.
    EXPECT_EQ(HttpRequest::Method::HTTP_POST, request.getMethod());
    EXPECT_EQ("/foo/bar", request.getUri());
    EXPECT_EQ("application/json", request.getHeaderValue("Content-Type"));
    EXPECT_EQ(json.length(), request.getHeaderValueAsUint64("Content-Length"));
    EXPECT_EQ(1, request.getHttpVersion().major_);
    EXPECT_EQ(0, request.getHttpVersion().minor_);

    // Try to retrieve values carried in JSON payload.
    ConstElementPtr json_element;
    ASSERT_NO_THROW(json_element = request.getJsonElement("service"));
    EXPECT_EQ("dhcp4", json_element->stringValue());

    ASSERT_NO_THROW(json_element = request.getJsonElement("command"));
    EXPECT_EQ("shutdown", json_element->stringValue());
}

// This test verifies that extraneous data in the request will not cause
// an error if "Content-Length" value refers to the length of the valid
// part of the request.
TEST_F(HttpRequestParserTest, extraneousDataInRequest) {
    std::string http_req = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n";
    std::string json = "{ \"service\": \"dhcp4\", \"command\": \"shutdown\" }";

    // Create valid request;
    http_req = createRequestString(http_req, json);

    // Add some garbage at the end.
    http_req += "some stuff which, if parsed, will cause errors";

    // Create HTTP request which accepts POST method and JSON as a body.
    PostHttpRequestJson request;

    // Create a parser and make it use the request we created.
    HttpRequestParser parser(request);
    ASSERT_NO_THROW(parser.initModel());

    // Feed the parser with the request containing some garbage at the end.
    parser.postBuffer(&http_req[0], http_req.size());
    ASSERT_NO_THROW(parser.poll());

    // The parser should only parse the valid part of the request as indicated
    // by the Content-Length.
    ASSERT_FALSE(parser.needData());
    ASSERT_TRUE(parser.httpParseOk());
    // There should be no error message.
    EXPECT_TRUE(parser.getErrorMessage().empty());

    // Do another poll() to see if the parser will parse the garbage. We
    // expect that it doesn't.
    ASSERT_NO_THROW(parser.poll());
    EXPECT_FALSE(parser.needData());
    EXPECT_TRUE(parser.httpParseOk());
    EXPECT_TRUE(parser.getErrorMessage().empty());
}


// This test verifies that LWS is parsed correctly. The LWS marks line breaks
// in the HTTP header values.
TEST_F(HttpRequestParserTest, getLWS) {
    // "User-Agent" header contains line breaks with whitespaces in the new
    // lines to mark continuation of the header value.
    std::string http_req = "GET /foo/bar HTTP/1.1\r\n"
        "Content-Type: text/html\r\n"
        "User-Agent: Kea/1.2 Command \r\n"
        " Control \r\n"
        "\tClient\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    // Verify parsed values.
    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ("text/html", request_.getHeaderValue("Content-Type"));
    EXPECT_EQ("Kea/1.2 Command Control Client",
              request_.getHeaderValue("User-Agent"));
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);
}

// This test verifies that the HTTP request with no headers is
// parsed correctly.
TEST_F(HttpRequestParserTest, noHeaders) {
    std::string http_req = "GET /foo/bar HTTP/1.1\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    // Verify the values.
    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);
}

// This test verifies that the HTTP method can be specified in lower
// case.
TEST_F(HttpRequestParserTest, getLowerCase) {
    std::string http_req = "get /foo/bar HTTP/1.1\r\n"
        "Content-Type: text/html\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ("text/html", request_.getHeaderValue("Content-Type"));
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);
}

// This test verifies that headers are case insensitive.
TEST_F(HttpRequestParserTest, headersCaseInsensitive) {
    std::string http_req = "get /foo/bar HTTP/1.1\r\n"
        "Content-type: text/html\r\n"
        "connection: keep-Alive\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ("text/html", request_.getHeader("Content-Type")->getValue());
    EXPECT_EQ("keep-alive", request_.getHeader("Connection")->getLowerCaseValue());
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);
}

// This test verifies that other value of the HTTP version can be
// specified in the request.
TEST_F(HttpRequestParserTest, http20) {
    std::string http_req = "get /foo/bar HTTP/2.0\r\n"
        "Content-Type: text/html\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ("text/html", request_.getHeaderValue("Content-Type"));
    EXPECT_EQ(2, request_.getHttpVersion().major_);
    EXPECT_EQ(0, request_.getHttpVersion().minor_);
}

// This test verifies that the header with no whitespace between the
// colon and header value is accepted.
TEST_F(HttpRequestParserTest, noHeaderWhitespace) {
    std::string http_req = "get /foo/bar HTTP/1.0\r\n"
        "Content-Type:text/html\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ("text/html", request_.getHeaderValue("Content-Type"));
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(0, request_.getHttpVersion().minor_);
}

// This test verifies that the header value preceded with multiple
// whitespaces is accepted.
TEST_F(HttpRequestParserTest, multipleLeadingHeaderWhitespaces) {
    std::string http_req = "get /foo/bar HTTP/1.0\r\n"
        "Content-Type:     text/html\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    EXPECT_EQ(HttpRequest::Method::HTTP_GET, request_.getMethod());
    EXPECT_EQ("/foo/bar", request_.getUri());
    EXPECT_EQ("text/html", request_.getHeaderValue("Content-Type"));
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(0, request_.getHttpVersion().minor_);
}

// This test verifies that error is reported when unsupported HTTP
// method is used.
TEST_F(HttpRequestParserTest, unsupportedMethod) {
    std::string http_req = "POSTX /foo/bar HTTP/2.0\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that error is reported when URI contains
// an invalid character.
TEST_F(HttpRequestParserTest, invalidUri) {
    std::string http_req = "POST /foo/\r HTTP/2.0\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that the request containing a typo in the
// HTTP version string causes parsing error.
TEST_F(HttpRequestParserTest, invalidHTTPString) {
    std::string http_req = "POST /foo/ HTLP/2.0\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that error is reported when the HTTP version
// string doesn't contain a slash character.
TEST_F(HttpRequestParserTest, invalidHttpVersionNoSlash) {
    std::string http_req = "POST /foo/ HTTP 1.1\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that error is reported when HTTP version string
// doesn't contain the minor version number.
TEST_F(HttpRequestParserTest, invalidHttpNoMinorVersion) {
    std::string http_req = "POST /foo/ HTTP/1\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that error is reported when HTTP header name
// contains an invalid character.
TEST_F(HttpRequestParserTest, invalidHeaderName) {
    std::string http_req = "POST /foo/ HTTP/1.1\r\n"
        "Content-;: text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that error is reported when HTTP header value
// is not preceded with the colon character.
TEST_F(HttpRequestParserTest, noColonInHttpHeader) {
    std::string http_req = "POST /foo/ HTTP/1.1\r\n"
        "Content-Type text/html\r\n\r\n";
    testInvalidHttpRequest(http_req);
}

// This test verifies that the input buffer of the HTTP request can be
// retrieved as text formatted for logging.
TEST_F(HttpRequestParserTest, getBufferAsString) {
    std::string http_req = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n";

    // Create HTTP request.
    PostHttpRequestJson request;

    // Create a parser and make it use the request we created.
    HttpRequestParser parser(request);
    ASSERT_NO_THROW(parser.initModel());

    // Insert data into the request.
    ASSERT_NO_THROW(parser.postBuffer(&http_req[0], http_req.size()));

    // limit = 0 means no limit
    EXPECT_EQ(http_req, parser.getBufferAsString(0));

    // large enough limit should not cause the truncation.
    EXPECT_EQ(http_req, parser.getBufferAsString(1024));

    // Only 3 characters requested. The request should be truncated.
    EXPECT_EQ("POS.........\n(truncating HTTP message larger than 3 characters)\n",
              parser.getBufferAsString(3));
}

TEST_F(HttpRequestParserTest, parseEmptyRequest) {
    std::string http_req = "POST / HTTP/1.1\r\n"
        "Content-Type: application/json\r\n";
    std::string json = "";

    http_req = createRequestString(http_req, json);

    ASSERT_NO_FATAL_FAILURE(doParse(http_req));

    EXPECT_EQ(HttpRequest::Method::HTTP_POST, request_.getMethod());
    EXPECT_EQ("/", request_.getUri());
    EXPECT_EQ("", request_.getBody());
    EXPECT_EQ(1, request_.getHttpVersion().major_);
    EXPECT_EQ(1, request_.getHttpVersion().minor_);
}

}
