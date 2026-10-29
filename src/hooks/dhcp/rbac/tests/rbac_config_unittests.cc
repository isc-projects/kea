// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>

#include <rbac/rbac.h>
#include <rbac/rbac_config.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::rbac;
using namespace std;

namespace {

/// @brief Test fixture for checking RBAC configurations.
class ConfigTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ConfigTest() {
        roleAssign.reset();
        aclTable.clear();
        apiTable.clear();
        roleConfigTable.clear();
        defaultRoleConfig.reset();
        unknownRoleConfig.reset();
    }

    /// @brief Destructor.
    virtual ~ConfigTest() {
        if (roleAssign) {
            roleAssign->setup(false);
        }
        roleAssign.reset();
        aclTable.clear();
        apiTable.clear();
        roleConfigTable.clear();
        defaultRoleConfig.reset();
        unknownRoleConfig.reset();
    }

    /// @brief Reset (to be used between multiple calls to parse).
    void reset() {
        if (roleAssign) {
            roleAssign->setup(false);
        }
        roleAssign.reset();
        aclTable.clear();
        apiTable.clear();
        roleConfigTable.clear();
        defaultRoleConfig.reset();
        unknownRoleConfig.reset();
        rbacConfig.init();
    }
};

/// @brief This test verifies that init works as expected.
TEST_F(ConfigTest, init) {
    EXPECT_TRUE(aclTable.empty());
    rbacConfig.init();
    EXPECT_EQ(".../share/kea/api", rbacConfig.getApiFiles());
    EXPECT_FALSE(rbacConfig.getRequireTls());
    EXPECT_EQ(4U, aclTable.size());

    rbacConfig.setApiFiles("/usr/local/share/kea/api");
    EXPECT_EQ("/usr/local/share/kea/api", rbacConfig.getApiFiles());
    rbacConfig.setRequireTls(true);
    EXPECT_TRUE(rbacConfig.getRequireTls());
}

/// @brief This test verifies that config parsing works as expected.
TEST_F(ConfigTest, parse) {
    rbacConfig.init();
    ElementPtr cfg;
    string expected = "null config";
    EXPECT_THROW_MSG(Config::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    expected = "config is not a map";
    EXPECT_THROW_MSG(Config::parse(cfg), BadValue, expected);

    // api-files is required.
    cfg = Element::createMap();
    expected = "missing 'api-files' parameter";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    // assign-role-method is required.
    cfg->set("api-files", Element::create(false));
    expected = "missing 'assign-role-method' parameter";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    // keywords.
    cfg->set("assign-role-method", Element::create(string("foobar")));
    expected = "'api-files' parameter is not a string";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->set("api-files", Element::create(string()));
    cfg->set("access-control-lists", Element::createMap());
    expected = "'access-control-lists' parameter is not a list";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->remove("access-control-lists");
    cfg->set("assign-role-method", Element::create(1));
    expected = "'assign-role-method' parameter is not a string";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->set("assign-role-method", Element::create(string()));
    cfg->set("commands", Element::createMap());
    expected = "'commands' parameter is not a list";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->remove("commands");
    cfg->set("default-role", Element::create(string("foobar")));
    expected = "'default-role' parameter is not a map";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->remove("default-role");
    cfg->set("require-tls", Element::create(0));
    expected = "'require-tls' parameter is not a boolean";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->remove("require-tls");
    cfg->set("roles", Element::createMap());
    expected = "'roles' parameter is not a list";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->remove("roles");
    cfg->set("comment", Element::create(string("a comment")));
    cfg->set("unknown-role", Element::create(false));
    expected = "'unknown-role' parameter is not a map";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);

    cfg->remove("unknown-role");
    cfg->set("bad", Element::create(string("unknown")));
    expected = "spurious 'bad' parameter";
    EXPECT_THROW_MSG(Config::parse(cfg), DhcpConfigError, expected);
}

/// @brief This test verifies that role assignment method parsing
/// works as expected.
TEST_F(ConfigTest, parseRoleAssign) {
    rbacConfig.init();
    ElementPtr cfg = Element::createMap();
    cfg->set("api-files", Element::create(string(API_DIR)));
    cfg->set("assign-role-method", Element::create(string("foobar")));
    string expected = "unknown role assignment keyword 'foobar'";
    EXPECT_THROW_MSG(Config::parse(cfg), BadValue, expected);

    cfg->set("assign-role-method", Element::create(string("cert-subject")));
    EXPECT_FALSE(roleAssign);
    EXPECT_NO_THROW(Config::parse(cfg));
    ASSERT_TRUE(roleAssign);
    EXPECT_EQ("subject", roleAssign->getName());
}

/// @brief This test verifies that require TLS flag parsing works as expected.
TEST_F(ConfigTest, parseRequireTls) {
    rbacConfig.init();
    ElementPtr cfg = Element::createMap();
    cfg->set("api-files", Element::create(string(API_DIR)));
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_FALSE(rbacConfig.getRequireTls());

    reset();
    cfg->set("require-tls", Element::create(true));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_TRUE(rbacConfig.getRequireTls());

    reset();
    cfg->set("require-tls", Element::create(false));
    cfg->set("assign-role-method", Element::create(string("cert-subject")));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_FALSE(rbacConfig.getRequireTls());

    reset();
    cfg->remove("require-tls");
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_TRUE(rbacConfig.getRequireTls());

    reset();
    cfg->set("assign-role-method", Element::create(string("cert-issuer")));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_TRUE(rbacConfig.getRequireTls());

    reset();
    cfg->set("assign-role-method",
             Element::create(string("basic-authentication")));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_FALSE(rbacConfig.getRequireTls());
}

/// @brief This test verifies that API files parsing works as expected.
TEST_F(ConfigTest, parseApiFiles) {
    rbacConfig.init();
    ElementPtr cfg = Element::createMap();
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    cfg->set("api-files", Element::create(string("/does/not/exist")));
    EXPECT_THROW(Config::parse(cfg), BadValue);

    EXPECT_TRUE(apiTable.empty());
    cfg->set("api-files", Element::create(string(API_DIR)));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_FALSE(apiTable.empty());
    EXPECT_TRUE(Api::getApiByName("list-commands"));
}

/// @brief This test verifies that commands parsing works as expected.
TEST_F(ConfigTest, parseCommands) {
    rbacConfig.init();
    ElementPtr cfg = Element::createMap();
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    cfg->set("api-files", Element::create(string(API_DIR)));
    EXPECT_NO_THROW(Config::parse(cfg));
    size_t before = apiTable.size();

    reset();
    ElementPtr commands = Element::createList();
    cfg->set("commands", commands);
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_EQ(before, apiTable.size());

    reset();
    commands->add(Element::create(string("foo")));
    commands->add(Element::create(string("bar")));
    EXPECT_THROW(Config::parse(cfg), BadValue);

    reset();
    commands = Element::createList();
    cfg->set("commands", commands);
    ElementPtr foo = Element::createMap();
    foo->set("name", Element::create(string("foo")));
    foo->set("access", Element::create(string("read")));
    commands->add(foo);
    ElementPtr bar = Element::createMap();
    bar->set("name", Element::create(string("bar")));
    bar->set("access", Element::create(string("write")));
    bar->set("hook", Element::create(string("my_test_hook_for_rbac")));
    commands->add(bar);
    EXPECT_EQ(0U, apiHooks.count("my_test_hook_for_rbac"));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_EQ(before + 2, apiTable.size());
    EXPECT_EQ(1U, apiHooks.count("my_test_hook_for_rbac"));
}

/// @brief This test verifies that access control lists parsing works as
/// expected.
TEST_F(ConfigTest, parseAccessControlLists) {
    rbacConfig.init();
    ElementPtr cfg = Element::createMap();
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    cfg->set("api-files", Element::create(string(API_DIR)));
    EXPECT_NO_THROW(Config::parse(cfg));
    size_t before = aclTable.size();

    reset();
    ElementPtr acls = Element::createList();
    cfg->set("access-control-lists", acls);
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_EQ(before, aclTable.size());

    reset();
    acls->add(Element::create(string("foo")));
    acls->add(Element::create(string("bar")));
    EXPECT_THROW(Config::parse(cfg), BadValue);

    reset();
    acls = Element::createList();
    cfg->set("access-control-lists", acls);
    ElementPtr foo = Element::createMap();
    foo->set("foo", Element::create(string("ALL")));
    acls->add(foo);
    ElementPtr bar = Element::createMap();
    ElementPtr acl = Element::createMap();
    acl->set("not", Element::create(string("ALL")));
    bar->set("bar", acl);
    acls->add(bar);
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_EQ(before + 2, aclTable.size());
}

/// @brief This test verifies that roles parsing works as expected.
TEST_F(ConfigTest, parseRoles) {
    rbacConfig.init();
    ElementPtr cfg = Element::createMap();
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    cfg->set("api-files", Element::create(string(API_DIR)));
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_TRUE(roleConfigTable.empty());

    reset();
    ElementPtr roles = Element::createList();
    cfg->set("roles", roles);
    roles->add(Element::create(string("foo")));
    EXPECT_THROW(Config::parse(cfg), BadValue);

    reset();
    roles = Element::createList();
    cfg->set("roles", roles);
    ElementPtr bad = Element::createMap();
    bad->set("name", Element::create(string()));
    roles->add(bad);
    string expected = "role config name is empty";
    EXPECT_THROW_MSG(Config::parse(cfg), BadValue, expected);

    reset();
    roles = Element::createList();
    cfg->set("roles", roles);
    ElementPtr foo = Element::createMap();
    foo->set("name", Element::create(string("foo")));
    // Leaving defaults so only the others value will matter.
    roles->add(foo);
    EXPECT_NO_THROW(Config::parse(cfg));
    EXPECT_FALSE(roleConfigTable.empty());

    reset();
    // Add twice will give an error.
    roles->add(foo);
    expected = "role 'foo' is already defined";
    EXPECT_THROW_MSG(Config::parse(cfg), BadValue, expected);
}

/// @brief This test verifies that default role parsing works as expected.
TEST_F(ConfigTest, parseDefaultRole) {
    rbacConfig.init();
    EXPECT_FALSE(defaultRoleConfig);
    ElementPtr cfg = Element::createMap();
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    cfg->set("api-files", Element::create(string(API_DIR)));
    EXPECT_NO_THROW(Config::parse(cfg));
    ASSERT_TRUE(defaultRoleConfig);
    EXPECT_EQ("default/reject", defaultRoleConfig->name_);
    EXPECT_TRUE(defaultRoleConfig->preference_);

    reset();
    ElementPtr role = Element::createMap();
    role->set("list-match-first", Element::create(string("reject")));
    cfg->set("default-role", role);
    EXPECT_NO_THROW(Config::parse(cfg));
    ASSERT_TRUE(defaultRoleConfig);
    EXPECT_EQ("default", defaultRoleConfig->name_);
    EXPECT_FALSE(defaultRoleConfig->preference_);
}

/// @brief This test verifies that unknown role parsing works as expected.
TEST_F(ConfigTest, parseUnknownRole) {
    rbacConfig.init();
    EXPECT_FALSE(unknownRoleConfig);
    ElementPtr cfg = Element::createMap();
    cfg->set("assign-role-method", Element::create(string("remote-address")));
    cfg->set("api-files", Element::create(string(API_DIR)));
    EXPECT_NO_THROW(Config::parse(cfg));
    ASSERT_TRUE(unknownRoleConfig);
    EXPECT_EQ("unknown/reject", unknownRoleConfig->name_);
    EXPECT_TRUE(unknownRoleConfig->preference_);

    reset();
    ElementPtr role = Element::createMap();
    role->set("list-match-first", Element::create(string("reject")));
    cfg->set("unknown-role", role);
    EXPECT_NO_THROW(Config::parse(cfg));
    ASSERT_TRUE(unknownRoleConfig);
    EXPECT_EQ("unknown", unknownRoleConfig->name_);
    EXPECT_FALSE(unknownRoleConfig->preference_);
}

} // end of anonymous namespace
