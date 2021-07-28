// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/adaptor.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Test that get context works as expected i.e. moves a comment into
// the user context creating it if not exists.
TEST(AdaptorTest, getContext) {
    // Empty.
    string config = "{\n"
        "}\n";
    ConstElementPtr json = Element::fromJSON(config);
    ConstElementPtr context;
    ASSERT_NO_THROW_LOG(context = Adaptor::getContext(json));
    EXPECT_FALSE(context);

    // No relevant.
    config = "{\n"
        " \"foo\": 1\n"
        "}\n";
    json = Element::fromJSON(config);
    ASSERT_NO_THROW_LOG(context = Adaptor::getContext(json));
    EXPECT_FALSE(context);

    // User context.
    config = "{\n"
        " \"foo\": 1,\n"
        " \"user-context\": { \"bar\": 2 }\n"
        "}\n";
    json = Element::fromJSON(config);
    ASSERT_NO_THROW_LOG(context = Adaptor::getContext(json));
    ASSERT_TRUE(context);
    EXPECT_EQ("{ \"bar\": 2 }", context->str());

    // Comment.
    config = "{\n"
        " \"foo\": 1,\n"
        " \"comment\": \"a comment\"\n"
        "}\n";
    json = Element::fromJSON(config);
    ASSERT_NO_THROW_LOG(context = Adaptor::getContext(json));
    ASSERT_TRUE(context);
    EXPECT_EQ("{ \"comment\": \"a comment\" }", context->str());

    // User context and comment.
    config = "{\n"
        " \"foo\": 1,\n"
        " \"user-context\": { \"bar\": 2 },\n"
        " \"comment\": \"a comment\"\n"
        "}\n";
    json = Element::fromJSON(config);
    ASSERT_NO_THROW_LOG(context = Adaptor::getContext(json));
    ASSERT_TRUE(context);
    EXPECT_EQ("{ \"bar\": 2, \"comment\": \"a comment\" }", context->str());

    // User context with conflicting comment and comment.
    config = "{\n"
        " \"foo\": 1,\n"
        " \"user-context\": {\n"
        "   \"bar\": 2,\n"
        "   \"comment\": \"conflicting\"\n"
        "  },\n"
        " \"comment\": \"a comment\"\n"
        "}\n";
    json = Element::fromJSON(config);
    ASSERT_NO_THROW_LOG(context = Adaptor::getContext(json));
    ASSERT_TRUE(context);
    EXPECT_EQ("{ \"bar\": 2, \"comment\": \"a comment\" }", context->str());
}

// Test that fromParent works as expected i.e. moves parameters from the
// parent to children and not overwrite them.
TEST(AdaptorTest, fromParent) {
    string config = "{\n"
        " \"param1\": 123,\n"
        " \"param2\": \"foo\",\n"
        " \"list\": [\n"
        "  {\n"
        "   \"param1\": 234\n"
        "  },{\n"
        "   \"another\": \"entry\"\n"
        "  }\n"
        " ]\n"
        "}\n";

    ConstElementPtr json = Element::fromJSON(config);
    EXPECT_NO_THROW(Adaptor::fromParent("param1", json, json->get("list")));
    EXPECT_NO_THROW(Adaptor::fromParent("param2", json, json->get("list")));
    EXPECT_NO_THROW(Adaptor::fromParent("param3", json, json->get("list")));

    string expected = "{\n"
        " \"param1\": 123,\n"
        " \"param2\": \"foo\",\n"
        " \"list\": [\n"
        "  {\n"
        "   \"param1\": 234,\n"
        "   \"param2\": \"foo\"\n"
        "  },{\n"
        "   \"another\": \"entry\",\n"
        "   \"param1\": 123,\n"
        "   \"param2\": \"foo\"\n"
        "  }\n"
        " ]\n"
        "}\n";
    EXPECT_TRUE(json->equals(*Element::fromJSON(expected)));
}

// Test that toParent works as expected i.e. moves parameters from children
// to the parent throwing when a value differs between two children.
TEST(AdaptorTest, toParent) {
    string config = "{\n"
        " \"list\": [\n"
        "  {\n"
        "   \"param2\": \"foo\",\n"
        "   \"param3\": 234,\n"
        "   \"param4\": true\n"
        "  },{\n"
        "   \"another\": \"entry\",\n"
        "   \"param2\": \"foo\",\n"
        "   \"param3\": 123,\n"
        "   \"param5\": false\n"
        "  }\n"
        " ]\n"
        "}\n";

    ElementPtr json = Element::fromJSON(config);
    EXPECT_NO_THROW(Adaptor::toParent("param1", json, json->get("list")));
    EXPECT_TRUE(json->equals(*Element::fromJSON(config)));

    string expected = "{\n"
        " \"param2\": \"foo\",\n"
        " \"list\": [\n"
        "  {\n"
        "   \"param3\": 234,\n"
        "   \"param4\": true\n"
        "  },{\n"
        "   \"another\": \"entry\",\n"
        "   \"param3\": 123,\n"
        "   \"param5\": false\n"
        "  }\n"
        " ]\n"
        "}\n";

    EXPECT_NO_THROW(Adaptor::toParent("param2",json, json->get("list")));
    EXPECT_TRUE(json->equals(*Element::fromJSON(expected)));

    // param[345] have different values so it should throw.
    EXPECT_THROW(Adaptor::toParent("param3",json, json->get("list")),
                 BadValue);
    EXPECT_THROW(Adaptor::toParent("param4",json, json->get("list")),
                 BadValue);
    EXPECT_THROW(Adaptor::toParent("param5",json, json->get("list")),
                 BadValue);
    // And not modify the value.
    EXPECT_TRUE(json->equals(*Element::fromJSON(expected)));
}

// Test for modify (maps & insert).
TEST(AdaptorTest, modifyMapInsert) {
    string config = "{\n"
        " \"foo\": {\n"
        "   \"bar\": {\n"
        "}}}\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    string spath = "[ \"foo\", \"bar\" ]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"insert\",\n"
        "  \"key\": \"test\",\n"
        "  \"value\": 1234\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "{\n"
        " \"foo\": {\n"
        "   \"bar\": {\n"
        "     \"test\": 1234\n"
        "}}}\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

// Test for modify (maps & replace).
TEST(AdaptorTest, modifyMapReplace) {
    string config = "{\n"
        " \"foo\": {\n"
        "   \"bar\": {\n"
        "     \"test1\": 1234,\n"
        "     \"test2\": 1234\n"
        "}}}\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    string spath = "[ \"foo\", \"bar\" ]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"insert\",\n"
        "  \"key\": \"test1\",\n"
        "  \"value\": 5678\n"
        "},{\n"
        "  \"action\": \"replace\",\n"
        "  \"key\": \"test2\",\n"
        "  \"value\": 5678\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "{\n"
        " \"foo\": {\n"
        "   \"bar\": {\n"
        "     \"test1\": 1234,\n"
        "     \"test2\": 5678\n"
        "}}}\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

// Test for modify (maps & delete).
TEST(AdaptorTest, modifyMapDelete) {
    string config = "{\n"
        " \"foo\": {\n"
        "   \"bar\": {\n"
        "     \"test\": 1234\n"
        "}}}\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    string spath = "[ \"foo\", \"bar\" ]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"delete\",\n"
        "  \"key\": \"test\"\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "{\n"
        " \"foo\": {\n"
        "   \"bar\": {\n"
        "}}}\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

// Test for modify (lists & insert).
TEST(AdaptorTest, modifyListInsert) {
    string config = "[\n"
        "[{\n"
        " \"foo\": \"bar\"\n"
        "}]]\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    string spath = "[ 0, { \"key\": \"foo\", \"value\": \"bar\" }]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"insert\",\n"
        "  \"key\": \"test\",\n"
        "  \"value\": 1234\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "[\n"
        "[{\n"
        " \"foo\": \"bar\",\n"
        " \"test\": 1234\n"
        "}]]\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

// Test for modify (list all & insert).
TEST(AdaptorTest, modifyListAllInsert) {
    string config = "[\n"
        "{},\n"
        "{},\n"
        "{ \"test\": 1234 },\n"
        "]\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    string spath = "[ -1 ]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"insert\",\n"
        "  \"key\": \"test\",\n"
        "  \"value\": 5678\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "[\n"
        "{ \"test\": 5678 },\n"
        "{ \"test\": 5678 },\n"
        "{ \"test\": 1234 }\n"
        "]\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

TEST(AdaptorTest, modifyListDelete) {
    string config = "[[\n"
        "{\n"
        " \"foo\": \"bar\"\n"
        "},{\n"
        "},[\n"
        "0, 1, 2, 3\n"
        "]]]\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    string spath = "[ 0 ]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    // Put the positional first as it applies after previous actions...
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"delete\",\n"
        "  \"key\": 2\n"
        "},{\n"
        "  \"action\": \"delete\",\n"
        "  \"key\": { \"key\": \"foo\", \"value\": \"bar\" }\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "[[{}]]\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

TEST(AdaptorTest, modifyListAllDelete) {
    string config = "[[\n"
        "{\n"
        " \"foo\": \"bar\"\n"
        "},{\n"
        "},[\n"
        "0, 1, 2, 3\n"
        "]]]\n";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    // The main change from the previous unit test is key 0 -> -1 so
    // modify() applies the delete to all elements vs only the first one.
    string spath = "[ -1 ]";
    ConstElementPtr path;
    ASSERT_NO_THROW_LOG(path = Element::fromJSON(spath));
    // Put the positional first as it applies after previous actions...
    string sactions = "[\n"
        "{\n"
        "  \"action\": \"delete\",\n"
        "  \"key\": 2\n"
        "},{\n"
        "  \"action\": \"delete\",\n"
        "  \"key\": { \"key\": \"foo\", \"value\": \"bar\" }\n"
        "}]\n";
    ConstElementPtr actions;
    ASSERT_NO_THROW_LOG(actions = Element::fromJSON(sactions));
    string result = "[[{}]]\n";
    ConstElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(result));
    ASSERT_NO_THROW_LOG(Adaptor::modify(path, actions, json));
    EXPECT_TRUE(expected->equals(*json));
}

}; // end of anonymous namespace
