// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <testutils/gtest_utils.h>

#include <rbac/rbac.h>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::rbac;
using namespace std;

namespace {

/// @brief Test fixture for checking RBAC response filters.
class ResponseFilterTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ResponseFilterTest() {
        responseFilterTable.clear();
        ResponseFilter::initResponseFilterTable();
    }

    /// @brief Destructor.
    virtual ~ResponseFilterTest() {
        responseFilterTable.clear();
    }
};

/// @brief This test verifies that the table works as expected.
TEST_F(ResponseFilterTest, table) {
    EXPECT_EQ(2U, responseFilterTable.size());
}

/// @brief This test verifies that noop response filter works as expected.
TEST_F(ResponseFilterTest, noop) {
    RoleConfigPtr rc(new RoleConfig("my-role", AclPtr(), AclPtr(),
                                    true, true, ResponseFilterList()));
    ASSERT_TRUE(rc);
    ResponseFilterPtr rf(new NoopResponseFilter());
    ASSERT_TRUE(rf);
    EXPECT_EQ("noop", rf->getName());
    EXPECT_FALSE(rf->filter("foo", *rc, ConstElementPtr()));

    // Get the noop response filter from the table.
    rf = responseFilterTable["noop"];
    ASSERT_TRUE(rf);
    EXPECT_EQ("noop", rf->getName());
    EXPECT_FALSE(rf->filter("bar", *rc, ConstElementPtr()));
}

/// @brief This test verifies that list-commands response filter works
/// as expected.
TEST_F(ResponseFilterTest, listCommands) {
    // Response filter
    ResponseFilterPtr rf(new ListCommandsResponseFilter());
    ASSERT_TRUE(rf);
    EXPECT_EQ("list-commands", rf->getName());
    ResponseFilterList rfl;
    rfl.push_back(rf);

    // Get it from the table too.
    ResponseFilterPtr got = responseFilterTable["list-commands"];
    ASSERT_TRUE(got);
    EXPECT_EQ("list-commands", got->getName());

    // Role config.
    set<string> commands = { "foo", "bar", "xyz" };
    AclPtr accept(new CommandsAcl(commands));
    RoleConfigPtr rc(new RoleConfig("my-role", accept, AclPtr(),
                                    false, true, rfl));
    ASSERT_TRUE(rc);

    // Build a list-commands answer.
    ElementPtr answer = Element::createMap();
    ElementPtr result = Element::create(CONTROL_RESULT_SUCCESS);
    answer->set(CONTROL_RESULT, result);
    ElementPtr args = Element::createList();
    answer->set(CONTROL_ARGUMENTS, args);
    args->add(Element::create(string("list-commands")));
    args->add(Element::create(string("foo")));
    args->add(Element::create(string("bar")));
    string expected = answer->str();
    args->add(Element::create(string("abc")));
    args->add(Element::create(string("def")));
    ConstElementPtr answer1 = data::copy(answer);

    // Tests.
    EXPECT_FALSE(rf->filter("foo", *rc, ConstElementPtr()));
    EXPECT_FALSE(rf->filter("list-commands", *rc, ConstElementPtr()));
    EXPECT_FALSE(rf->filter("list-commands", *rc, Element::createList()));
    string arguments = "{ \"foo\": \"bar\" }";
    ConstElementPtr json = Element::fromJSON(arguments);
    EXPECT_FALSE(rf->filter("list-commands", *rc, json));
    arguments = "{ \"arguments\": { } }";
    json = Element::fromJSON(arguments);
    EXPECT_FALSE(rf->filter("list-commands", *rc, json));
    arguments = "{ \"arguments\": [ ] }";
    json = Element::fromJSON(arguments);
    EXPECT_FALSE(rf->filter("list-commands", *rc, json));

    EXPECT_TRUE(rf->filter("list-commands", *rc, answer));
    EXPECT_EQ(expected, answer->str());
    EXPECT_TRUE(rc->filter("list-commands", answer1));
    EXPECT_EQ(expected, answer1->str());
}

/// @brief This test verifies that response filter parsing works as expected.
TEST_F(ResponseFilterTest, parse) {
    ElementPtr cfg;
    string expected = "parse null response filter list";
    EXPECT_THROW_MSG(ResponseFilter::parse(cfg), BadValue, expected);

    cfg = Element::createMap();
    expected = "response filter list is not a list";
    EXPECT_THROW_MSG(ResponseFilter::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    cfg->add(Element::create(1));
    expected = "response filter name is not a string";
    EXPECT_THROW_MSG(ResponseFilter::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    cfg->add(Element::create(string()));
    expected = "response filter name is empty";
    EXPECT_THROW_MSG(ResponseFilter::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    cfg->add(Element::create(string("foo")));
    expected = "unknown response filter 'foo'";
    EXPECT_THROW_MSG(ResponseFilter::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    cfg->add(Element::create(string("noop")));
    cfg->add(Element::create(string("list-commands")));
    ResponseFilterList rfl;
    EXPECT_NO_THROW(rfl = ResponseFilter::parse(cfg));
    ASSERT_EQ(2U, rfl.size());
    ResponseFilterPtr rf = rfl.front();
    ASSERT_TRUE(rf);
    EXPECT_EQ("noop", rf->getName());
    rf = rfl.back();
    ASSERT_TRUE(rf);
    EXPECT_EQ("list-commands", rf->getName());
}

} // end of anonymous namespace
