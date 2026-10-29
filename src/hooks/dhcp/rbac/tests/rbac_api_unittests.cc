// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>

#include <rbac/rbac_api.h>

using namespace isc;
using namespace isc::data;
using namespace isc::rbac;
using namespace std;

namespace {

/// @brief Test fixture for checking RBAC API commands.
class ApiTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ApiTest() {
        apiTable.clear();
    }

    /// @brief Destructor.
    virtual ~ApiTest() {
        apiTable.clear();
    }
};

/// @brief This test verifies that API command object works as expected.
TEST_F(ApiTest, basic) {
    ApiPtr api;
    EXPECT_NO_THROW(api.reset(new Api("foo", "bar", "xyz")));
    ASSERT_TRUE(api);
    EXPECT_EQ("foo", api->getName());
    EXPECT_EQ("bar", api->getAccess());
    EXPECT_EQ("xyz", api->getHook());

    api->setAccess("my-access");
    api->setHook("my-hook");
    EXPECT_EQ("my-access", api->getAccess());
    EXPECT_EQ("my-hook", api->getHook());
    api->setHook("");
    EXPECT_TRUE(api->getHook().empty());

    // Even it makes no sense empty strings are allowed for all parameters.
    ApiPtr empty;
    EXPECT_NO_THROW(empty.reset(new Api("", "", "")));
    ASSERT_TRUE(empty);
    EXPECT_TRUE(empty->getName().empty());
    EXPECT_TRUE(empty->getAccess().empty());
    EXPECT_TRUE(empty->getHook().empty());
}

/// @brief This test verifies that the API table works as expected.
TEST_F(ApiTest, table) {
    EXPECT_TRUE(apiTable.empty());

    ApiPtr api;
    EXPECT_NO_THROW(api.reset(new Api("foo", "bar", "xyz")));
    ASSERT_TRUE(api);
    apiTable.insert(api);
    EXPECT_EQ(1U, apiTable.size());
    ApiPtr got = Api::getApiByName("foo");
    ASSERT_TRUE(got);
    EXPECT_EQ(api->getName(), got->getName());
    EXPECT_EQ(api->getAccess(), got->getAccess());
    EXPECT_EQ(api->getHook(), got->getHook());
    EXPECT_FALSE(Api::getApiByName("bar"));
}

/// @brief This test verifies that API command parsing works as expected.
TEST_F(ApiTest, parse) {
    EXPECT_TRUE(apiTable.empty());

    ElementPtr cfg;
    string expected = "parse null command config";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    expected = "command config is not a map";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg = Element::createMap();
    expected = "'name' is required in command config";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("name", Element::create(1));
    expected = "command name is not a string";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("name", Element::create(string()));
    expected = "command name is empty";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("name", Element::create(string("foo")));
    expected = "'access' is required in command config";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(true));
    expected = "command access is not a string";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(string()));
    expected = "command access is empty";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(string("foo")));
    expected = "command access 'foo' is not 'read' or 'write'";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(string("read")));
    cfg->set("hook", Element::create(1.23));
    expected = "command hook is not a string";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    cfg->set("hook", Element::create(string()));
    cfg->set("foo", Element::create(string("bar")));
    expected = "command spurious keyword 'foo'";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);

    EXPECT_NO_THROW(Api::parse(cfg, true));
    EXPECT_EQ(1U, apiTable.size());
    ApiPtr got = Api::getApiByName("foo");
    ASSERT_TRUE(got);

    cfg->remove("foo");
    expected = "command 'foo' is already defined";
    EXPECT_THROW_MSG(Api::parse(cfg), BadValue, expected);
}

/// @brief This test verifies that fillApiTable works as expected.
TEST_F(ApiTest, fillApiTable) {
    EXPECT_TRUE(apiTable.empty());
    string expected = "fill API table from '/does/not/exist' failed ";
    expected += "with can't open directory '/does/not/exist': ";
    expected += "No such file or directory";
    EXPECT_THROW_MSG(Api::fillApiTable("/does/not/exist"), BadValue, expected);

    string file = string(API_DIR) + "/meson.build";
    expected = "fill API table from '";
    expected += file + "' failed with can't open directory '";
    expected += file + "': Not a directory";
    EXPECT_THROW_MSG(Api::fillApiTable(file), BadValue, expected);

    string parent = string(API_DIR) + "/..";
    expected = "can't fill API table from '";
    expected += parent + "': got no command config?";
    EXPECT_THROW_MSG(Api::fillApiTable(parent), BadValue, expected);

    EXPECT_TRUE(apiTable.empty());
    EXPECT_NO_THROW(Api::fillApiTable(string(API_DIR)));
}

} // end of anonymous namespace
