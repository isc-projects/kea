// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>

#include <rbac/rbac.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace isc::rbac;
using namespace std;

namespace {

/// @brief Test fixture for checking RBAC role configs.
class RoleConfigTest : public ::testing::Test {
public:

    /// @brief Constructor.
    RoleConfigTest() {
        roleConfigTable.clear();
        aclTable.clear();
        Acl::initTable();
        apiTable.clear();
    }

    /// @brief Destructor.
    virtual ~RoleConfigTest() {
        roleConfigTable.clear();
        aclTable.clear();
        apiTable.clear();
    }
};

/// @brief This test verifies that role config object works as expected.
TEST_F(RoleConfigTest, basic) {
    RoleConfigPtr rc;
    AclPtr accept(new AllAcl());
    AclPtr reject(new NoneAcl());
    ResponseFilterList rfl;
    EXPECT_NO_THROW(rc.reset(new RoleConfig("foo", accept, reject,
                                            true, false, rfl)));
    ASSERT_TRUE(rc);
    EXPECT_EQ("foo", rc->name_);
    ASSERT_TRUE(rc->accept_);
    EXPECT_EQ("all", rc->accept_->getClassName());
    ASSERT_TRUE(rc->reject_);
    EXPECT_EQ("none", rc->reject_->getClassName());
    EXPECT_TRUE(rc->others_);
    EXPECT_FALSE(rc->preference_);
    EXPECT_TRUE(rc->response_filters_.empty());

    EXPECT_NO_THROW(rc.reset(new RoleConfig("bar", AclPtr(), AclPtr(),
                                            false, true, rfl)));
    ASSERT_TRUE(rc);
    EXPECT_EQ("bar", rc->name_);
    EXPECT_FALSE(rc->accept_);
    EXPECT_FALSE(rc->reject_);
    EXPECT_FALSE(rc->others_);
    EXPECT_TRUE(rc->preference_);
    EXPECT_TRUE(rc->response_filters_.empty());
}

/// @brief This test verifies that others member works as expected.
TEST_F(RoleConfigTest, others) {
    RoleConfigPtr rc(new RoleConfig("foo", AclPtr(), AclPtr(), false,
                                    true, ResponseFilterList()));
    ASSERT_TRUE(rc);
    EXPECT_FALSE(rc->match("bar"));
    EXPECT_FALSE(rc->match("any command"));

    rc->others_ = true;
    EXPECT_TRUE(rc->match("bar"));
    EXPECT_TRUE(rc->match("any command"));
}

/// @brief This test verifies that preference member works as expected.
TEST_F(RoleConfigTest, preference) {
    RoleConfigPtr rc(new RoleConfig("foo", AclPtr(new AllAcl()),
                                    AclPtr(new AllAcl()), false, true,
                                    ResponseFilterList()));
    ASSERT_TRUE(rc);
    EXPECT_TRUE(rc->match("bar"));
    EXPECT_TRUE(rc->match("any command"));

    rc->preference_ = false;
    EXPECT_FALSE(rc->match("bar"));
    EXPECT_FALSE(rc->match("any command"));
}

/// @brief This test verifies that the role config table works as expected.
TEST_F(RoleConfigTest, table) {
    ASSERT_TRUE(roleConfigTable.empty());

    RoleConfigPtr rc(new RoleConfig("all", AclPtr(new AllAcl()),
                                    AclPtr(new NoneAcl()), true, true,
                                    ResponseFilterList()));
    ASSERT_TRUE(rc);
    EXPECT_FALSE(RoleConfig::getConfig("all"));
    roleConfigTable["all"] = rc;
    RoleConfigPtr got = RoleConfig::getConfig("all");
    ASSERT_TRUE(got);
    EXPECT_EQ(got->name_, rc->name_);
}

/// @brief This test verifies that the role config parsing works as expected.
TEST_F(RoleConfigTest, parse) {
    ElementPtr cfg;
    string expected = "parse null role config";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    expected = "role config is not a map";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    // Keywords.
    cfg = Element::createMap();
    cfg->set("name", Element::create(1));
    expected = "'name' parameter is not a string";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), DhcpConfigError, expected);

    cfg->set("name", Element::create(string("foo")));
    cfg->set("accept-commands", Element::create(true));
    expected = "access control list is not a string or a map";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    cfg->set("accept-commands", Element::create(string("ALL")));
    cfg->set("reject-commands", Element::create(3.14));
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    cfg->set("reject-commands", Element::create(string("NONE")));
    cfg->set("other-commands", Element::create(false));
    expected = "'other-commands' parameter is not a string";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), DhcpConfigError, expected);

    cfg->remove("other-commands");
    cfg->set("list-match-first", Element::create(true));
    expected = "'list-match-first' parameter is not a string";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), DhcpConfigError, expected);

    cfg->remove("list-match-first");
    cfg->set("response-filters", Element::create(0.));
    expected = "'response-filters' parameter is not a list";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), DhcpConfigError, expected);

    cfg->remove("response-filters");
    cfg->set("comment", Element::create(string("a comment")));
    cfg->set("bad", Element::create(string("unknown parameter")));
    expected = "spurious 'bad' parameter";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), DhcpConfigError, expected);

    // Name.
    cfg->remove("bad");
    RoleConfigPtr rc;
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg));
    ASSERT_TRUE(rc);
    EXPECT_EQ("foo", rc->name_);

    expected = "spurious 'name' parameter for bar role";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg, "bar"), BadValue, expected);

    cfg = Element::createMap();
    rc.reset();
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg, "bar"));
    ASSERT_TRUE(rc);
    EXPECT_EQ("bar", rc->name_);

    expected = "'name' parameter is required in {  }";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    // ACLs.
    cfg->set("name", Element::create(string("foo")));
    cfg->set("accept-commands", Element::create(string("ALL")));
    cfg->set("reject-commands", Element::create(string("NONE")));
    rc.reset();
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg));
    ASSERT_TRUE(rc);
    EXPECT_EQ("foo", rc->name_);
    ASSERT_TRUE(rc->accept_);
    EXPECT_EQ("all", rc->accept_->getClassName());
    ASSERT_TRUE(rc->reject_);
    EXPECT_EQ("none", rc->reject_->getClassName());
    EXPECT_FALSE(rc->others_);
    EXPECT_TRUE(rc->preference_);

    // Other commands.
    cfg->set("other-commands", Element::create(string("foobar")));
    expected = "other-commands 'foobar' is not 'accept' or 'reject'";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    cfg->set("other-commands", Element::create(string("accept")));
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg));
    ASSERT_TRUE(rc);
    EXPECT_TRUE(rc->others_);

    cfg->set("other-commands", Element::create(string("reject")));
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg));
    ASSERT_TRUE(rc);
    EXPECT_FALSE(rc->others_);

    // Preference.
    cfg->set("list-match-first", Element::create(string("foobar")));
    expected = "list-match-first 'foobar' is not 'accept' or 'reject'";
    EXPECT_THROW_MSG(RoleConfig::parse(cfg), BadValue, expected);

    cfg->set("list-match-first", Element::create(string("accept")));
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg));
    ASSERT_TRUE(rc);
    EXPECT_TRUE(rc->preference_);

    cfg->set("list-match-first", Element::create(string("reject")));
    EXPECT_NO_THROW(rc = RoleConfig::parse(cfg));
    ASSERT_TRUE(rc);
    EXPECT_FALSE(rc->preference_);
}

/// @brief This test verifies that createReject works as expected.
TEST_F(RoleConfigTest, createReject) {
    HttpRequestPtr request;
    HttpStatusCode status_code = HttpStatusCode::FORBIDDEN;
    string expected = "null request";
    EXPECT_THROW_MSG(RoleConfig::createReject(request, status_code),
                     Unexpected, expected);

    request.reset(new HttpRequest());
    HttpResponseJsonPtr response;
    EXPECT_NO_THROW(response = RoleConfig::createReject(request, status_code));
    ASSERT_TRUE(response);
    EXPECT_EQ("HTTP/1.0 403 Forbidden", response->toBriefString());
    ConstElementPtr json = response->getBodyAsJson();
    ASSERT_TRUE(json);
    EXPECT_EQ("{ \"result\": 403, \"text\": \"Forbidden\" }", json->str());
}

/// @brief This test verifies that user1 extensive example parses.
TEST_F(RoleConfigTest, parseUser1) {
    string config = R"(
    {
        "name": "user1",
        "accept-commands":
        {
            "and": [
                "READ",
                { "not":
                    { "commands": [ "config-get" ] }
                }
            ]
        },
        "reject-commands": "ALL",
        "list-match-first": "accept"
    })";

    ConstElementPtr cfg;
    ASSERT_NO_THROW(cfg = Element::fromJSON(config));
    ASSERT_TRUE(cfg);
    Acl::initTable();
    Api::fillApiTable(string(API_DIR));
    RoleConfigPtr role;
    EXPECT_NO_THROW(role = RoleConfig::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_TRUE(role->match("status-get"));
    EXPECT_FALSE(role->match("config-get"));
    EXPECT_FALSE(role->match("config-set"));
}

/// @brief This test verifies that user2 extensive example parses.
TEST_F(RoleConfigTest, parseUser2) {
    string config = R"(
    {
        "name": "user2",
        "accept-commands":
        {
            "and": [
                "READ",
                { "not":
                    { "commands": [ "config-get" ] }
                }
            ]
        },
        "other-commands": "reject"
    })";

    ConstElementPtr cfg;
    ASSERT_NO_THROW(cfg = Element::fromJSON(config));
    ASSERT_TRUE(cfg);
    Acl::initTable();
    Api::fillApiTable(string(API_DIR));
    RoleConfigPtr role;
    EXPECT_NO_THROW(role = RoleConfig::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_TRUE(role->match("status-get"));
    EXPECT_FALSE(role->match("config-get"));
    EXPECT_FALSE(role->match("config-set"));
}

/// @brief This test verifies that user3 extensive example parses.
TEST_F(RoleConfigTest, parseUser3) {
    string config = R"(
    {
        "name": "user3",
        "reject-commands":
        {
            "or": [
                "WRITE",
                { "commands": [ "config-get" ] }
            ]
        },
        "other-commands": "accept"
    })";

    ConstElementPtr cfg;
    ASSERT_NO_THROW(cfg = Element::fromJSON(config));
    ASSERT_TRUE(cfg);
    Acl::initTable();
    Api::fillApiTable(string(API_DIR));
    RoleConfigPtr role;
    EXPECT_NO_THROW(role = RoleConfig::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_TRUE(role->match("status-get"));
    EXPECT_FALSE(role->match("config-get"));
    EXPECT_FALSE(role->match("config-set"));
}

/// @brief This test verifies that user4 extensive example parses.
TEST_F(RoleConfigTest, parseUser4) {
    string config = R"(
    {
        "name": "user4",
        "accept-commands": "READ",
        "reject-commands": { "commands": [ "config-get" ] },
        "list-match-first": "reject"
    })";

    ConstElementPtr cfg;
    ASSERT_NO_THROW(cfg = Element::fromJSON(config));
    ASSERT_TRUE(cfg);
    Acl::initTable();
    Api::fillApiTable(string(API_DIR));
    RoleConfigPtr role;
    EXPECT_NO_THROW(role = RoleConfig::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_TRUE(role->match("status-get"));
    EXPECT_FALSE(role->match("config-get"));
    EXPECT_FALSE(role->match("config-set"));
}

} // end of anonymous namespace
