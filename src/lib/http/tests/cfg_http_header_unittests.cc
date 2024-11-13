// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/cfg_http_header.h>
#include <gtest/gtest.h>

using namespace isc::data;
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
    EXPECT_EQ(expected, toElement(headers)->str());
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
    ASSERT_NO_THROW(unparsed = toElement(headers));
    EXPECT_TRUE(json->equals(*unparsed));
}

}
