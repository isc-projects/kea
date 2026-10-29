// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>

#include <rbac/rbac_acl.h>

using namespace isc;
using namespace isc::data;
using namespace isc::rbac;
using namespace std;

namespace {

/// @brief Test fixture for checking RBAC access control lists.
class AclTest : public ::testing::Test {
public:

    /// @brief Constructor.
    AclTest() {
        aclTable.clear();
        Acl::initTable();
        apiTable.clear();
    }

    /// @brief Destructor.
    virtual ~AclTest() {
        aclTable.clear();
        apiTable.clear();
    }
};

/// @brief This test verifies that commands access control list works
/// as expected.
TEST_F(AclTest, commands) {
    set<string> commands = { "foo", "bar" };
    AclPtr acl(new CommandsAcl(commands));
    ASSERT_TRUE(acl);
    EXPECT_EQ("commands", acl->getClassName());
    boost::shared_ptr<CommandsAcl> nacl =
        boost::dynamic_pointer_cast<CommandsAcl>(acl);
    ASSERT_TRUE(nacl);
    set<string> got = nacl->getCommands();
    EXPECT_EQ(got, commands);
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));
    ASSERT_NO_THROW(nacl->add("foo"));
    EXPECT_EQ(2U, nacl->getCommands().size());
    ASSERT_NO_THROW(nacl->add("xyz"));
    EXPECT_EQ(3U, nacl->getCommands().size());
    EXPECT_TRUE(acl->match("xyz"));
}

/// @brief This test verifies that all access control list works as expected.
TEST_F(AclTest, all) {
    AclPtr acl(new AllAcl());
    ASSERT_TRUE(acl);
    EXPECT_EQ("all", acl->getClassName());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_TRUE(acl->match("xyz"));
    EXPECT_TRUE(acl->match("-e-v-e-r-y-t-h-i-n-g-"));

    // Get the ALL ACL from the table.
    acl = aclTable["ALL"];
    ASSERT_TRUE(acl);
    EXPECT_EQ("all", acl->getClassName());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_TRUE(acl->match("xyz"));
    EXPECT_TRUE(acl->match("-e-v-e-r-y-t-h-i-n-g-"));
}

/// @brief This test verifies that none access control list works as expected.
TEST_F(AclTest, none) {
    AclPtr acl(new NoneAcl());
    ASSERT_TRUE(acl);
    EXPECT_EQ("none", acl->getClassName());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_FALSE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));
    EXPECT_FALSE(acl->match("-e-v-e-r-y-t-h-i-n-g-"));

    // Get the NONE ACL from the table.
    acl = aclTable["NONE"];
    ASSERT_TRUE(acl);
    EXPECT_EQ("none", acl->getClassName());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_FALSE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));
    EXPECT_FALSE(acl->match("-e-v-e-r-y-t-h-i-n-g-"));
}

/// @brief This test verifies that alias access control list works as expected.
TEST_F(AclTest, alias) {
    set<string> commands = { "foo", "bar" };
    AclPtr acl0(new CommandsAcl(commands));
    AclPtr acl;
    EXPECT_THROW_MSG(acl.reset(new AliasAcl("bad", AclPtr())), Unexpected,
                     "null acl in alias");
    EXPECT_NO_THROW(acl.reset(new AliasAcl("my-alias", acl0)));
    ASSERT_TRUE(acl);
    EXPECT_EQ("alias", acl->getClassName());
    boost::shared_ptr<AliasAcl> aacl =
        boost::dynamic_pointer_cast<AliasAcl>(acl);
    ASSERT_TRUE(aacl);
    EXPECT_EQ("my-alias", aacl->getName());
    AclPtr got = aacl->getAcl();
    ASSERT_TRUE(got);
    EXPECT_EQ(got->getClassName(), acl0->getClassName());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));
}

/// @brief This test verifies that not access control list works as expected.
TEST_F(AclTest, not) {
    set<string> commands = { "foo", "bar" };
    AclPtr acl0(new CommandsAcl(commands));
    AclPtr acl;
    EXPECT_THROW_MSG(acl.reset(new NotAcl(AclPtr())), Unexpected,
                     "null acl in not");
    EXPECT_NO_THROW(acl.reset(new NotAcl(acl0)));
    ASSERT_TRUE(acl);
    EXPECT_EQ("not", acl->getClassName());
    boost::shared_ptr<NotAcl> nacl =
        boost::dynamic_pointer_cast<NotAcl>(acl);
    ASSERT_TRUE(nacl);
    AclPtr got = nacl->getAcl();
    ASSERT_TRUE(got);
    EXPECT_EQ(got->getClassName(), acl0->getClassName());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_FALSE(acl->match("bar"));
    EXPECT_TRUE(acl->match("xyz"));
}

/// @brief This test verifies that and access control list works as expected.
TEST_F(AclTest, and) {
    AclList acll;
    acll.push_back(AclPtr());
    AclPtr acl;
    EXPECT_THROW_MSG(acl.reset(new AndAcl(acll)), Unexpected,
                     "null acl in and");
    acll.clear();
    EXPECT_NO_THROW(acl.reset(new AndAcl(acll)));
    ASSERT_TRUE(acl);
    EXPECT_EQ("and", acl->getClassName());
    boost::shared_ptr<AndAcl> aacl =
        boost::dynamic_pointer_cast<AndAcl>(acl);
    ASSERT_TRUE(aacl);
    AclList got = aacl->getAcls();
    EXPECT_TRUE(got.empty());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_TRUE(acl->match("xyz"));
    EXPECT_TRUE(acl->match("-e-v-e-r-y-t-h-i-n-g-"));

    set<string> commands1 = { "foo", "bar" };
    AclPtr acl1(new CommandsAcl(commands1));
    ASSERT_TRUE(acl1);
    EXPECT_NO_THROW(aacl->add(acl1));
    EXPECT_EQ(1U, aacl->getAcls().size());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));

    set<string> commands2 = { "foo", "xyz" };
    AclPtr acl2(new CommandsAcl(commands2));
    ASSERT_TRUE(acl2);

    acll.push_back(acl1);
    acll.push_back(acl2);
    EXPECT_NO_THROW(acl.reset(new AndAcl(acll)));
    ASSERT_TRUE(acl);
    aacl = boost::dynamic_pointer_cast<AndAcl>(acl);
    ASSERT_TRUE(aacl);
    EXPECT_EQ(2U, aacl->getAcls().size());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_FALSE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));
    EXPECT_FALSE(acl->match("abc"));
}

/// @brief This test verifies that or access control list works as expected.
TEST_F(AclTest, or) {
    AclList acll;
    acll.push_back(AclPtr());
    AclPtr acl;
    EXPECT_THROW_MSG(acl.reset(new OrAcl(acll)), Unexpected,
                     "null acl in or");
    acll.clear();
    EXPECT_NO_THROW(acl.reset(new OrAcl(acll)));
    ASSERT_TRUE(acl);
    EXPECT_EQ("or", acl->getClassName());
    boost::shared_ptr<OrAcl> oacl =
        boost::dynamic_pointer_cast<OrAcl>(acl);
    ASSERT_TRUE(oacl);
    AclList got = oacl->getAcls();
    EXPECT_TRUE(got.empty());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_FALSE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));
    EXPECT_FALSE(acl->match("-e-v-e-r-y-t-h-i-n-g-"));

    set<string> commands1 = { "foo", "bar" };
    AclPtr acl1(new CommandsAcl(commands1));
    ASSERT_TRUE(acl1);
    EXPECT_NO_THROW(oacl->add(acl1));
    EXPECT_EQ(1U, oacl->getAcls().size());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_FALSE(acl->match("xyz"));

    set<string> commands2 = { "foo", "xyz" };
    AclPtr acl2(new CommandsAcl(commands2));
    ASSERT_TRUE(acl2);

    acll.push_back(acl1);
    acll.push_back(acl2);
    EXPECT_NO_THROW(acl.reset(new OrAcl(acll)));
    ASSERT_TRUE(acl);
    oacl = boost::dynamic_pointer_cast<OrAcl>(acl);
    ASSERT_TRUE(oacl);
    EXPECT_EQ(2U, oacl->getAcls().size());
    EXPECT_TRUE(acl->match("foo"));
    EXPECT_TRUE(acl->match("bar"));
    EXPECT_TRUE(acl->match("xyz"));
    EXPECT_FALSE(acl->match("abc"));
}

/// @brief This test verifies that access access control list works as expected.
TEST_F(AclTest, access) {
    ASSERT_NO_THROW(Api::fillApiTable(string(API_DIR)));

    AclPtr acl(new AccessAcl("read"));
    ASSERT_TRUE(acl);
    EXPECT_EQ("access", acl->getClassName());
    boost::shared_ptr<AccessAcl> aacl =
        boost::dynamic_pointer_cast<AccessAcl>(acl);
    ASSERT_TRUE(aacl);
    EXPECT_EQ("read", aacl->getAccess());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_TRUE(acl->match("list-commands"));
    EXPECT_TRUE(acl->match("lease4-get"));
    EXPECT_FALSE(acl->match("lease6-add"));

    // Get the WRITE ACL from the table.
    acl = aclTable["WRITE"];
    ASSERT_TRUE(acl);
    EXPECT_EQ("access", acl->getClassName());
    aacl = boost::dynamic_pointer_cast<AccessAcl>(acl);
    ASSERT_TRUE(aacl);
    EXPECT_EQ("write", aacl->getAccess());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_FALSE(acl->match("list-commands"));
    EXPECT_FALSE(acl->match("lease6-get"));
    EXPECT_TRUE(acl->match("lease4-add"));
}

/// @brief This test verifies that hook access control list works as expected.
TEST_F(AclTest, hook) {
    ASSERT_NO_THROW(Api::fillApiTable(string(API_DIR)));

    AclPtr acl(new HookAcl("lease_cmds"));
    ASSERT_TRUE(acl);
    EXPECT_EQ("hook", acl->getClassName());
    boost::shared_ptr<HookAcl> hacl =
        boost::dynamic_pointer_cast<HookAcl>(acl);
    ASSERT_TRUE(hacl);
    EXPECT_EQ("lease_cmds", hacl->getHook());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_FALSE(acl->match("list-commands"));
    EXPECT_TRUE(acl->match("lease4-get"));
    EXPECT_TRUE(acl->match("lease6-add"));
}

/// @brief This test verifies that the access control list table works
/// as expected.
TEST_F(AclTest, table) {
    /// ALL, NONE, READ and WRITE.
    EXPECT_EQ(4U, aclTable.size());

    set<string> commands = { "foo", "bar" };
    AclPtr acl(new CommandsAcl(commands));
    ASSERT_TRUE(acl);

    ASSERT_EQ(0U, aclTable.count("foobar"));
    aclTable["foobar"] = acl;
    EXPECT_EQ(5U, aclTable.size());
    EXPECT_EQ(1U, aclTable.count("foobar"));

    AclPtr got = aclTable["foobar"];
    ASSERT_TRUE(got);
    EXPECT_EQ("commands", got->getClassName());
}

/// @brief This test verifies that the access control list name parsing
/// works as expected.
TEST_F(AclTest, parseName) {
    ElementPtr cfg;
    string expected = "parse null access control list";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg = Element::createList();
    expected = "access control list is not a string or a map";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg = Element::create(string("foobar"));
    expected = "unknown access control list name 'foobar'";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    set<string> commands = { "foo", "bar" };
    AclPtr nacl(new CommandsAcl(commands));
    ASSERT_TRUE(nacl);
    aclTable["foobar"] = nacl;
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("commands", acl->getClassName());
}

/// @brief This test verifies that the access control list not literal parsing
/// works as expected.
TEST_F(AclTest, parseNot) {
    ElementPtr cfg = Element::createMap();
    cfg->set("not", Element::create(string("ALL")));
    cfg->set("comment", Element::create(string("not ALL is NONE")));
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("not", acl->getClassName());
}

/// @brief This test verifies that the access control list commands literal
/// parsing works as expected.
TEST_F(AclTest, parseCommands) {
    ASSERT_NO_THROW(Api::fillApiTable(string(API_DIR)));

    ElementPtr cfg = Element::createMap();
    cfg->set("commands", Element::create(string("foo")));
    string expected = "commands access control list is not a list";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    ElementPtr list = Element::createList();
    cfg->set("commands", list);
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("commands", acl->getClassName());

    cfg->set("not", Element::create(string("READ")));
    expected = "spurious 'not' entry in ";
    expected += "{ \"commands\": [  ], \"not\": \"READ\" }";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    acl.reset();
    cfg->remove("not");
    list->add(Element::create(1));
    expected = "commands access control list item is not a string";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    list = Element::createList();
    list->add(Element::create(string("foobar")));
    cfg->set("commands", list);
    expected = "unknown command 'foobar'";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    list = Element::createList();
    list->add(Element::create(string("list-commands")));
    list->add(Element::create(string("status-get")));
    cfg->set("commands", list);
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("commands", acl->getClassName());
    EXPECT_FALSE(acl->match("foo"));
    EXPECT_TRUE(acl->match("list-commands"));
    EXPECT_TRUE(acl->match("status-get"));
    EXPECT_FALSE(acl->match("lease4-get"));
}

/// @brief This test verifies that the access control list access literal
/// parsing works as expected.
TEST_F(AclTest, parseAccess) {
    ASSERT_NO_THROW(Api::fillApiTable(string(API_DIR)));

    ElementPtr cfg = Element::createMap();
    cfg->set("access", Element::create(true));
    string expected = "access access control list is not a string";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(string()));
    expected = "access control list access is empty";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(string("foobar")));
    expected = "unknown access 'foobar'";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg->set("access", Element::create(string("read")));
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("access", acl->getClassName());
}

/// @brief This test verifies that the access control list hook literal
/// parsing works as expected.
TEST_F(AclTest, parseHook) {
    ASSERT_NO_THROW(Api::fillApiTable(string(API_DIR)));

    ElementPtr cfg = Element::createMap();
    cfg->set("hook", Element::create(123));
    string expected = "hook access control list is not a string";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg->set("hook", Element::create(string("foobar")));
    expected = "unknown hook 'foobar'";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg->set("hook", Element::create(string()));
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("hook", acl->getClassName());

    cfg->set("hook", Element::create(string("lease_cmds")));
    acl.reset();
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("hook", acl->getClassName());
}

/// @brief This test verifies that the parsing of a list of access control
/// lists works as expected.
TEST_F(AclTest, parseList) {
    ElementPtr cfg;
    string expected = "parse null list of access control lists";
    EXPECT_THROW_MSG(Acl::parseList(cfg), BadValue, expected);

    cfg = Element::createMap();
    expected = "list of access control lists is not a list";
    EXPECT_THROW_MSG(Acl::parseList(cfg), BadValue, expected);

    cfg = Element::createList();
    AclList acll;
    EXPECT_NO_THROW(acll = Acl::parseList(cfg));
    EXPECT_TRUE(acll.empty());

    ElementPtr elem1 = Element::create(string("ALL"));
    cfg->add(elem1);
    ElementPtr elem2 = Element::createMap();
    elem2->set("not", Element::create(string("NONE")));
    cfg->add(elem2);
    EXPECT_NO_THROW(acll = Acl::parseList(cfg));
    EXPECT_EQ(2U, acll.size());
}

/// @brief This test verifies that the access control list and literal
/// parsing works as expected.
TEST_F(AclTest, parseAnd) {
    ElementPtr cfg = Element::createMap();
    cfg->set("foo", Element::create(string("bar")));
    string expected = "unknown access control list keyword 'foo'";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    cfg = Element::createMap();
    ElementPtr list = Element::createList();
    ElementPtr elem1 = Element::create(string("ALL"));
    list->add(elem1);
    ElementPtr elem2 = Element::createMap();
    elem2->set("not", Element::create(string("NONE")));
    list->add(elem2);
    cfg->set("and", list);
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("and", acl->getClassName());
}

/// @brief This test verifies that the access control list or literal
/// parsing works as expected.
TEST_F(AclTest, parseOr) {
    ElementPtr cfg = Element::createMap();
    string expected = "bad access control list {  }";
    EXPECT_THROW_MSG(Acl::parse(cfg), BadValue, expected);

    ElementPtr list = Element::createList();
    ElementPtr elem1 = Element::create(string("ALL"));
    list->add(elem1);
    ElementPtr elem2 = Element::createMap();
    elem2->set("not", Element::create(string("NONE")));
    list->add(elem2);
    cfg->set("or", list);
    AclPtr acl;
    EXPECT_NO_THROW(acl = Acl::parse(cfg));
    ASSERT_TRUE(acl);
    EXPECT_EQ("or", acl->getClassName());
}

/// @brief This test verifies that the access control list definition
/// parsing works as expected.
TEST_F(AclTest, parseDefinition) {
    EXPECT_EQ(4U, aclTable.size());

    ElementPtr def;
    string expected = "null access control list definition";
    EXPECT_THROW_MSG(AliasAcl::parse(def), BadValue, expected);

    def = Element::createList();
    expected = "access control list definition is not a map";
    EXPECT_THROW_MSG(AliasAcl::parse(def), BadValue, expected);

    def = Element::createMap();
    def->set("one", Element::create(string("foo")));
    def->set("two", Element::create(string("bar")));
    expected = "access control list definition must have one entry";
    EXPECT_THROW_MSG(AliasAcl::parse(def), BadValue, expected);

    def = Element::createMap();
    def->set("", Element::create(string("foo")));
    expected = "access control list definition name is empty";
    EXPECT_THROW_MSG(AliasAcl::parse(def), BadValue, expected);

    def = Element::createMap();
    ElementPtr val = Element::createMap();
    def->set("foo", val);
    val->set("access", Element::create(string("write")));
    EXPECT_NO_THROW(AliasAcl::parse(def));
    EXPECT_EQ(5U, aclTable.size());
    EXPECT_EQ(1U, aclTable.count("foo"));

    val->set("access", Element::create(string("read")));
    expected = "access control list 'foo' is already defined";
    EXPECT_THROW_MSG(AliasAcl::parse(def), BadValue, expected);
}

} // end of anonymous namespace
