// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/tests/yang_configs.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

// Test sr_type_t print.
TEST(YangReprTest, type) {
    ostringstream os;

    // Verify that string is "string" (vs a number).
    sr_type_t t = SR_STRING_T;
    os << t;
    EXPECT_EQ("string", os.str());
    os.str("");

    // Compiler does not let to create an invalid value...
}

// Test YangReprItem basic stuff.
TEST(YangReprTest, item) {
    // An item.
    YRItem item1("/foo", "bar", SR_STRING_T, true);
    EXPECT_EQ("/foo", item1.xpath_);
    EXPECT_EQ("bar", item1.value_);
    EXPECT_EQ(SR_STRING_T, item1.type_);
    EXPECT_TRUE(item1.settable_);

    // Another one.
    YRItem item2("/foo", "bar", SR_STRING_T, false);
    EXPECT_EQ("/foo", item2.xpath_);
    EXPECT_EQ("bar", item2.value_);
    EXPECT_EQ(SR_STRING_T, item2.type_);
    EXPECT_FALSE(item2.settable_);

    // Equality.
    EXPECT_TRUE(item1 == item2);
    EXPECT_TRUE(item2 == item1);
    EXPECT_FALSE(item1 != item2);
    EXPECT_FALSE(item2 != item1);
    EXPECT_EQ(item1, item2);
    EXPECT_EQ(item2, item1);
}

// Test get with test module.
TEST(YangReprTest, getTest) {
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Cleanup.
    EXPECT_NO_THROW(sess->delete_item("/keatest-module:container"));
    EXPECT_NO_THROW(sess->apply_changes());
    EXPECT_NO_THROW(sess->delete_item("/keatest-module:main"));
    EXPECT_NO_THROW(sess->apply_changes());

    // Fill the test module.
    string xpath;
    S_Val s_val;

    xpath = "/keatest-module:main/string";
    s_val.reset(new Val("str", SR_STRING_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/boolean";
    s_val.reset(new Val(true, SR_BOOL_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/ui8";
    uint8_t u8(8);
    s_val.reset(new Val(u8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/ui16";
    uint16_t u16(16);
    s_val.reset(new Val(u16));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/ui32";
    uint32_t u32(32);
    s_val.reset(new Val(u32));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/i8";
    int8_t s8(8);
    s_val.reset(new Val(s8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/i16";
    int16_t s16(16);
    s_val.reset(new Val(s16));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/i32";
    int32_t s32(32);
    s_val.reset(new Val(s32));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/id_ref";
    s_val.reset(new Val("keatest-module:id_1", SR_IDENTITYREF_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    xpath = "/keatest-module:main/enum";
    s_val.reset(new Val("maybe", SR_ENUM_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    // Binary.
    xpath = "/keatest-module:main/raw";
    s_val.reset(new Val("Zm9vYmFy", SR_BINARY_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(sess->apply_changes());

    // Get it.
    YangRepr repr(testModel);
    YRTree tree;
    EXPECT_NO_THROW(tree = repr.get(sess));

    // Verify.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));
}

// This test verifies that errors are handled properly.
TEST(YangReprTrest, getTestErrors) {
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Cleanup.
    EXPECT_NO_THROW(sess->delete_item("/keatest-module:container"));
    EXPECT_NO_THROW(sess->apply_changes());
    EXPECT_NO_THROW(sess->delete_item("/keatest-module:main"));
    EXPECT_NO_THROW(sess->apply_changes());

    // Get it.
    YangRepr repr(testModel);
    YRTree tree;
    EXPECT_NO_THROW(repr.set(testTree, sess));

    // Verify.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));

    // Change a path. Remove final 'm'.
    YRTree badpath = testTree;
    string xpath("/keatest-module:main/enum");
    YRItem node(badpath.at(xpath));
    node.xpath_ = "/keatest-module:main/enu";
    badpath.erase(xpath);
    badpath.emplace(xpath, node);
    EXPECT_FALSE(repr.verify(badpath, sess, cerr));

    // Change a value from "str" to "Str".
    YRTree badvalue = testTree;
    xpath = "/keatest-module:main/string";
    badvalue.at(xpath).value_ = "Str";
    EXPECT_FALSE(repr.verify(badvalue, sess, cerr));

    // Change a type from SR_INT32_T to SR_UINT32_T.
    YRTree badtype = testTree;
    xpath = "/keatest-module:main/i32";
    badtype.at(xpath).type_ = SR_UINT32_T;
    EXPECT_FALSE(repr.verify(badtype, sess, cerr));

    // Add a record at the end.
    YRTree badmissing = testTree;
    xpath = "/keatest-module:presence-container";
    badmissing.emplace(xpath, YRItem(xpath, "", SR_CONTAINER_PRESENCE_T, false));
    EXPECT_FALSE(repr.verify(badmissing, sess, cerr));

    // Delete last record.
    YRTree badextra = testTree;
    badextra.erase("/keatest-module:kernel-modules");
    EXPECT_FALSE(repr.verify(badextra, sess, cerr));
}

// Test set with test module.
TEST(YangReprTest, setTest) {
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Cleanup.
    EXPECT_NO_THROW(sess->delete_item("/keatest-module:container"));
    EXPECT_NO_THROW(sess->apply_changes());
    EXPECT_NO_THROW(sess->delete_item("/keatest-module:main"));
    EXPECT_NO_THROW(sess->apply_changes());

    // Set the module content.
    YangRepr repr(testModel);
    EXPECT_NO_THROW(repr.set(testTree, sess));

    // Verify it.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));
}

/// @brief Tests specified configuration.
///
/// Configuration is set and then verified using YangRepr object.
///
/// @param model name of the model to be verified against.
/// @param tree tree to be verified.
void sanityCheckConfig(const std::string& model, const YRTree& tree) {
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Cleanup.
    TranslatorBasic translator(sess, model);
    std::string toplevel_node("config");
    if (model == IETF_DHCPV6_SERVER) {
        toplevel_node = "server";
    }
    translator.delItem("/" + model + ":" + toplevel_node);

    // Get it.
    YangRepr repr(model);

    EXPECT_NO_THROW(repr.set(tree, sess))
        << " for model " << model;
    bool result = false;
    EXPECT_NO_THROW(result = repr.verify(tree, sess, cerr))
        << " for model " << model;
    EXPECT_TRUE(result)
        << " for model " << model;
}

// This is test environment sanity check. It verifies that all configuration
// defined in yang_configs.h are sane.
TEST(YangReprTest, verifyConfigs) {
    for (auto x : test_configs) {
        sanityCheckConfig(x.first, x.second);
    }
}

}  // namespace
