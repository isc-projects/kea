// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/adaptor_host.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Verifies that quoteIdentifier does not touch an identifier which
// has a type different from flex-d.
TEST(AdaptorHostTest, notFlexId) {
    string config = "{\n"
        " \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        " \"ip-address\": \"192.0.2.201\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorHost::quoteIdentifier(json));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies that quoteIdentifier does not touch a  flex-id identifier
// without quotes.
TEST(AdaptorHostTest, noQuote) {
    string config = "{\n"
        " \"flex-id\": \"s0mEVaLue\",\n"
        " \"ip-address\": \"192.0.2.206\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorHost::quoteIdentifier(json));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies that quoteIdentifier removes quotes from a flex-id identifier.
TEST(AdaptorHostTest, quotes) {
    string config = "{\n"
        " \"flex-id\": \"'somevalue'\",\n"
        " \"ip-addresses\": \"2001:db8:1:cafe::2\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorHost::quoteIdentifier(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr id = json->get("flex-id");
    ASSERT_TRUE(id);
    ASSERT_EQ(Element::string, id->getType());
    EXPECT_EQ("73:6f:6d:65:76:61:6c:75:65", id->stringValue());
}

// Verifies that quoteIdentifier removes quotes from a flex-id identifier
// but does not interpret a quote in the middle.
TEST(AdaptorHostTest, extraQuote) {
    string config = "{\n"
        " \"flex-id\": \"'some'value'\",\n"
        " \"ip-addresses\": \"2001:db8:1:cafe::2\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorHost::quoteIdentifier(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr id = json->get("flex-id");
    ASSERT_TRUE(id);
    ASSERT_EQ(Element::string, id->getType());
    EXPECT_EQ("73:6f:6d:65:27:76:61:6c:75:65", id->stringValue());
}

// Verifies that quoteIdentifier works on not standard characters too.
TEST(AdaptorHostTest, notStandard) {
    string config = "{\n"
        " \"flex-id\": \"'some\\\"value'\",\n"
        " \"ip-addresses\": \"2001:db8:1:cafe::2\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorHost::quoteIdentifier(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr id = json->get("flex-id");
    ASSERT_TRUE(id);
    ASSERT_EQ(Element::string, id->getType());
    EXPECT_EQ("73:6f:6d:65:22:76:61:6c:75:65", id->stringValue());
}

// Verifies that quoteIdentifier works on not standard characters too
// even without quotes.
TEST(AdaptorHostTest, notQuoted) {
    string config = "{\n"
        " \"flex-id\": \"some\\\"value\",\n"
        " \"ip-addresses\": \"2001:db8:1:cafe::2\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorHost::quoteIdentifier(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr id = json->get("flex-id");
    ASSERT_TRUE(id);
    ASSERT_EQ(Element::string, id->getType());
    EXPECT_EQ("73:6f:6d:65:22:76:61:6c:75:65", id->stringValue());
}

}  // namespace
