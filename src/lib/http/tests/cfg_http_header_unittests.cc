// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/cfg_http_header.h>
#include <cc/simple_parser.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace std;

namespace {

// This test verifies copy to response.
TEST(CfgHttpHeaderTest, copy) {
    // Create a response.
    HttpResponse response(HttpVersion(1, 0), HttpStatusCode::OK);
    // Create a HSTS header.
    CfgHttpHeader hsts("Strict-Transport-Security", "max-age=31536000");
    // Create a random header.
    CfgHttpHeader foobar("Foo", "bar");
    // Add them to a collection.
    CfgHttpHeaders headers;
    headers.push_back(hsts);
    headers.push_back(foobar);
    // Copy headers to response.
    EXPECT_NO_THROW(copyHttpHeaders(headers, response));

    // Verify.
    auto const& got = response.context()->headers_;
    ASSERT_EQ(2, got.size());
    EXPECT_EQ("Strict-Transport-Security", got[0].name_);
    EXPECT_EQ("max-age=31536000", got[0].value_);
    EXPECT_EQ("Foo", got[1].name_);
    EXPECT_EQ("bar", got[1].value_);

    // Unparse.
    string expected = "[ ";
    expected += "{ \"name\": \"Strict-Transport-Security\", ";
    expected += "\"value\": \"max-age=31536000\" }, ";
    expected += "{ \"name\": \"Foo\", \"value\": \"bar\" } ]";
    EXPECT_EQ(expected, CfgHttpHeaderstoElement(headers)->str());
}

// This test verifies parse and toElement behavior.
TEST(CfgHttpHeaderTest, parse) {
    // Config.
    string config = "[\n"
        " {\n"
        " \"name\": \"Strict-Transport-Security\",\n"
        " \"value\": \"max-age=31536000\",\n"
        " \"user-context\": { \"comment\": \"HSTS header\" }\n"
        " },{\n"
        " \"name\": \"Foo\", \"value\": \"bar\"\n"
        " }\n"
        " ]\n";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    CfgHttpHeaders headers;
    ASSERT_NO_THROW(headers = parseCfgHttpHeaders(json));
    ASSERT_EQ(2, headers.size());
    EXPECT_EQ("Strict-Transport-Security", headers[0].name_);
    EXPECT_EQ("max-age=31536000", headers[0].value_);
    ConstElementPtr user_context = headers[0].getContext();
    ASSERT_TRUE(user_context);
    EXPECT_EQ("{ \"comment\": \"HSTS header\" }", user_context->str());
    EXPECT_EQ("Foo", headers[1].name_);
    EXPECT_EQ("bar", headers[1].value_);
    EXPECT_FALSE(headers[1].getContext());
    ConstElementPtr unparsed;
    ASSERT_NO_THROW(unparsed = CfgHttpHeaderstoElement(headers));
    EXPECT_TRUE(json->equals(*unparsed));
}

// This test verifies parse error cases.
TEST(CfgHttpHeaderTest, parseErrors) {
    // Scenarios.
    struct Scenario{
        string desc_;    // Description.
        string config_; // Configuration.
        string errmsg_; // Error message.
    };
    vector<Scenario> scenarios = {
        {
            "Not a list",
            "{ \"name\": \"Foo\", \"value\": \"bar\" }",
            "invalid type specified for parameter 'http-headers' "
            "(<string>:1:2)"
        },
        {
            "Not a map",
            "[ \"Foo\",  \"bar\" ]",
            "invalid type specified for 'http-headers' item (<string>:1:3)"
        },
        {
            "Unknown keyword",
            "[ { \"foo\": \"bar\" } ]",
            "spurious 'foo' parameter"
        },
        {
            "Bad name type",
            "[ { \"name\": 1 } ]",
            "'name' parameter is not a string"
        },
        {
            "Bad value type",
            "[ { \"value\": false } ]",
            "'value' parameter is not a string"
        },
        {
            "Bad user context type",
            "[ { \"user-context\": \"bad\" } ]",
            "'user-context' parameter is not a map"
        },
        {
            "Missing name",
            "[ { } ]",
            "missing 'name' parameter"
        },
        {
            "Missing value",
            "[ { \"name\": \"Foo\" } ]",
            "missing 'value' parameter"
        },
        {
            "Empty name",
            "[ { \"name\": \"\", \"value\": \"\" } ]",
            "empty 'name' parameter (<string>:1:13)"
        },
        {
            "Empty value",
            "[ { \"name\": \"Foo\", \"value\": \"\" } ]",
            "empty 'value' parameter (<string>:1:29)"
        }
    };

    // Iterate over Scenarios.
    ConstElementPtr json;
    CfgHttpHeaders headers;
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.desc_);
        {
            ASSERT_NO_THROW(json = Element::fromJSON(scenario.config_));
            try {
                headers = parseCfgHttpHeaders(json);
                ADD_FAILURE() << "exception is expected";
            } catch (const DhcpConfigError& ex) {
                EXPECT_EQ(scenario.errmsg_, ex.what());
            } catch (...) {
                ADD_FAILURE() << "DhcpConfigError is expected";
            }
        }
    }

    // No error cases.
    ConstElementPtr null_json;
    ASSERT_NO_THROW(headers = parseCfgHttpHeaders(null_json));
    EXPECT_TRUE(headers.empty());
    ConstElementPtr empty_json = Element::createList();
    ASSERT_NO_THROW(headers = parseCfgHttpHeaders(empty_json));
    EXPECT_TRUE(headers.empty());
}

}
