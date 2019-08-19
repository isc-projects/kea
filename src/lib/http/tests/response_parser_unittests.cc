// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <http/response_json.h>
#include <http/response_parser.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::http;

namespace {

/// @brief Test fixture class for @ref HttpResponseParser.
class HttpResponseParserTest : public ::testing::Test {
public:

    /// @brief Creates HTTP response string.
    ///
    /// @param preamble A string including HTTP response's first line
    /// and all headers except "Content-Length".
    /// @param payload A string containing HTTP response payload.
    std::string createResponseString(const std::string& preamble,
                                     const std::string& payload) {
        std::ostringstream s;
        s << preamble;
        s << "Content-Length: " << payload.length() << "\r\n\r\n"
          << payload;
        return (s.str());
    }

    /// @brief Parses the HTTP response and checks that parsing was
    /// successful.
    ///
    /// @param http_resp HTTP response string.
    void doParse(const std::string& http_resp) {
        HttpResponseParser parser(response_);
        ASSERT_NO_THROW(parser.initModel());

        parser.postBuffer(&http_resp[0], http_resp.size());
        ASSERT_NO_THROW(parser.poll());

        ASSERT_FALSE(parser.needData());
        ASSERT_TRUE(parser.httpParseOk());
        EXPECT_TRUE(parser.getErrorMessage().empty());
    }

    /// @brief Tests that parsing fails when malformed HTTP response
    /// is received.
    ///
    /// @param http_resp HTTP response string.
    void testInvalidHttpResponse(const std::string& http_resp) {
        HttpResponseParser parser(response_);
        ASSERT_NO_THROW(parser.initModel());

        parser.postBuffer(&http_resp[0], http_resp.size());
        ASSERT_NO_THROW(parser.poll());

        EXPECT_FALSE(parser.needData());
        EXPECT_FALSE(parser.httpParseOk());
        EXPECT_FALSE(parser.getErrorMessage().empty());
    }

    /// @brief Tests that the response specified with (header, body) can
    ///        be parsed properly.
    ///
    /// @param header specifies the header of the response to be parsed
    /// @param json specifies the body of the response (JSON in text format) to be parsed
    /// @param expect_success whether the parsing is expected to be successful
    ///
    /// @return a parser that parsed the response for further inspection
    HttpResponseJson testResponseWithJson(const std::string& header,
                                          const std::string& json,
                                          bool expect_success = true) {
        std::string http_resp = createResponseString(header, json);

        // Create HTTP response which accepts JSON as a body.
        HttpResponseJson response;

        // Create a parser and make it use the response we created.
        HttpResponseParser parser(response);
        EXPECT_NO_THROW(parser.initModel());

        // Simulate receiving HTTP response in chunks.
        const unsigned chunk_size = 10;
        while (!http_resp.empty()) {
            size_t chunk = http_resp.size() % chunk_size;
            if (chunk == 0) {
                chunk = chunk_size;
            }

            parser.postBuffer(&http_resp[0], chunk);
            http_resp.erase(0, chunk);
            parser.poll();
            if (chunk < chunk_size) {
                EXPECT_TRUE(parser.needData());
                if (!parser.needData()) {
                    ADD_FAILURE() << "Parser completed prematurely";
                    return (response);
                }
            }
        }

        if (expect_success) {
            // Parser should have parsed the response and should expect no more data.
            EXPECT_FALSE(parser.needData());
            // Parsing should be successful.
            EXPECT_TRUE(parser.httpParseOk()) << parser.getErrorMessage();
            // There should be no error message.
            EXPECT_TRUE(parser.getErrorMessage().empty());
        }

        return (response);
    }

    /// @brief Instance of the HttpResponse used by the unit tests.
    HttpResponse response_;
};

// Test test verifies that an HTTP response including JSON body is parsed
// successfully.
TEST_F(HttpResponseParserTest, responseWithJson) {
    std::string http_resp = "HTTP/1.1 408 Request Timeout\r\n"
        "Content-Type: application/json\r\n";
    std::string json = "{ \"result\": 0, \"text\": \"All ok\" }";

    HttpResponseJson response = testResponseWithJson(http_resp, json);

    // Verify HTTP version, status code and phrase.
    EXPECT_EQ(1, response.getHttpVersion().major_);
    EXPECT_EQ(1, response.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::REQUEST_TIMEOUT, response.getStatusCode());
    EXPECT_EQ("Request Timeout", response.getStatusPhrase());

    // Try to retrieve values carried in JSON payload.
    ConstElementPtr json_element;
    ASSERT_NO_THROW(json_element = response.getJsonElement("result"));
    EXPECT_EQ(0, json_element->intValue());

    ASSERT_NO_THROW(json_element = response.getJsonElement("text"));
    EXPECT_EQ("All ok", json_element->stringValue());
}

// This test verifies that extraneous data in the response will not cause
// an error if "Content-Length" value refers to the length of the valid
// part of the response.
TEST_F(HttpResponseParserTest, extraneousDataInResponse) {
    std::string http_resp = "HTTP/1.0 200 OK\r\n"
        "Content-Type: application/json\r\n";
    std::string json = "{ \"service\": \"dhcp4\", \"command\": \"shutdown\" }";

    // Create valid response.
    http_resp = createResponseString(http_resp, json);

    // Add some garbage at the end.
    http_resp += "some stuff which, if parsed, will cause errors";

    // Create HTTP response which accepts JSON as a body.
    HttpResponseJson response;

    // Create a parser and make it use the response we created.
    HttpResponseParser parser(response);
    ASSERT_NO_THROW(parser.initModel());

    // Feed the parser with the response containing some garbage at the end.
    parser.postBuffer(&http_resp[0], http_resp.size());
    ASSERT_NO_THROW(parser.poll());

    // The parser should only parse the valid part of the response as indicated
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

// This test verifies that LWS is parsed correctly. The LWS (linear white
// space) marks line breaks in the HTTP header values.
TEST_F(HttpResponseParserTest, getLWS) {
    // "User-Agent" header contains line breaks with whitespaces in the new
    // lines to mark continuation of the header value.
    std::string http_resp = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "User-Agent: Kea/1.2 Command \r\n"
        " Control \r\n"
        "\tClient\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_resp));

    // Verify parsed values.
    EXPECT_EQ(1, response_.getHttpVersion().major_);
    EXPECT_EQ(1, response_.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::OK, response_.getStatusCode());
    EXPECT_EQ("OK", response_.getStatusPhrase());
    EXPECT_EQ("text/html", response_.getHeaderValue("Content-Type"));
    EXPECT_EQ("Kea/1.2 Command Control Client",
              response_.getHeaderValue("User-Agent"));
}

// This test verifies that the HTTP response with no headers is
// parsed correctly.
TEST_F(HttpResponseParserTest, noHeaders) {
    std::string http_resp = "HTTP/1.1 204 No Content\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_resp));

    // Verify the values.
    EXPECT_EQ(1, response_.getHttpVersion().major_);
    EXPECT_EQ(1, response_.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::NO_CONTENT, response_.getStatusCode());
}

// This test verifies that headers are case insensitive.
TEST_F(HttpResponseParserTest, headersCaseInsensitive) {
    std::string http_resp = "HTTP/1.1 200 OK\r\n"
        "Content-type: text/html\r\n"
        "connection: clOSe\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_resp));

    EXPECT_EQ("text/html", response_.getHeader("Content-Type")->getValue());
    EXPECT_EQ("close", response_.getHeader("Connection")->getLowerCaseValue());
    EXPECT_EQ(1, response_.getHttpVersion().major_);
    EXPECT_EQ(1, response_.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::OK, response_.getStatusCode());
    EXPECT_EQ("OK", response_.getStatusPhrase());
}

// This test verifies that the header with no whitespace between the
// colon and header value is accepted.
TEST_F(HttpResponseParserTest, noHeaderWhitespace) {
    std::string http_resp = "HTTP/1.0 200 OK\r\n"
        "Content-Type:text/html\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_resp));

    EXPECT_EQ("text/html", response_.getHeaderValue("Content-Type"));
    EXPECT_EQ(1, response_.getHttpVersion().major_);
    EXPECT_EQ(0, response_.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::OK, response_.getStatusCode());
    EXPECT_EQ("OK", response_.getStatusPhrase());
}

// This test verifies that the header value preceded with multiple
// whitespaces is accepted.
TEST_F(HttpResponseParserTest, multipleLeadingHeaderWhitespaces) {
    std::string http_resp = "HTTP/1.0 200 OK\r\n"
        "Content-Type:     text/html\r\n\r\n";

    ASSERT_NO_FATAL_FAILURE(doParse(http_resp));

    EXPECT_EQ("text/html", response_.getHeaderValue("Content-Type"));
    EXPECT_EQ(1, response_.getHttpVersion().major_);
    EXPECT_EQ(0, response_.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::OK, response_.getStatusCode());
    EXPECT_EQ("OK", response_.getStatusPhrase());
}

// This test verifies that the response containing a typo in the
// HTTP version string causes parsing error.
TEST_F(HttpResponseParserTest, invalidHTTPString) {
    std::string http_resp = "HTLP/2.0 100 OK\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpResponse(http_resp);
}

// This test verifies that error is reported when the HTTP version
// string doesn't contain a slash character.
TEST_F(HttpResponseParserTest, invalidHttpVersionNoSlash) {
    std::string http_resp = "HTTP 1.1 100 OK\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpResponse(http_resp);
}

// This test verifies that error is reported when HTTP version string
// doesn't contain the minor version number.
TEST_F(HttpResponseParserTest, invalidHttpNoMinorVersion) {
    std::string http_resp = "HTTP/1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n";
    testInvalidHttpResponse(http_resp);
}

// This test verifies that error is reported when HTTP header name
// contains an invalid character.
TEST_F(HttpResponseParserTest, invalidHeaderName) {
    std::string http_resp = "HTTP/1.1 200 OK\r\n"
        "Content-;: text/html\r\n\r\n";
    testInvalidHttpResponse(http_resp);
}

// This test verifies that error is reported when HTTP header value
// is not preceded with the colon character.
TEST_F(HttpResponseParserTest, noColonInHttpHeader) {
    std::string http_resp = "HTTP/1.1 200 OK\r\n"
        "Content-Type text/html\r\n\r\n";
    testInvalidHttpResponse(http_resp);
}

// This test verifies that the HTTP response is formatted for logging.
TEST_F(HttpResponseParserTest, logFormatHttpMessage) {
    std::string message = "POST / HTTP/1.1\r\n"
        "Host: 127.0.0.1:8080\r\n"
        "User-Agent: curl/7.59.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 51\r\n\r\n"
        "{ \"command\": \"config-get\", \"service\": [ \"dhcp4\" ] }";

    // limit = 0 means no limit
    EXPECT_EQ(message, HttpResponseParser::logFormatHttpMessage(message, 0));

    // large enough limit should not cause the truncation.
    EXPECT_EQ(message, HttpResponseParser::logFormatHttpMessage(message, 1024));

    // Only 3 characters requested. The request should be truncated.
    EXPECT_EQ("POS.........\n(truncating HTTP message larger than 3 characters)\n",
              HttpResponseParser::logFormatHttpMessage(message, 3));
}

TEST_F(HttpResponseParserTest, parseEmptyResponse) {
    std::string http_resp = "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n";
    std::string json = "";

    http_resp = createResponseString(http_resp, json);

    ASSERT_NO_FATAL_FAILURE(doParse(http_resp));

    HttpResponseJson response = testResponseWithJson(http_resp, json);

    EXPECT_EQ("", response_.getBody());
    EXPECT_EQ(1, response_.getHttpVersion().major_);
    EXPECT_EQ(1, response_.getHttpVersion().minor_);
    EXPECT_EQ(HttpStatusCode::OK, response_.getStatusCode());
    EXPECT_EQ("OK", response_.getStatusPhrase());
}

}
