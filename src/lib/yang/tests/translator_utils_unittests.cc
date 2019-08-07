// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/tests/yang_configs.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::yang;
using namespace isc::yang::test;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

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

    // Get a translator object to play with.
    S_Connection conn(new Connection("utils unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Fill the test module.
    string xpath;
    S_Val s_val;

    // Create a list.
    xpath = "/keatest-module:container/list";
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/string";
    s_val.reset(new Val("str", SR_STRING_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/boolean";
    s_val.reset(new Val(true, SR_BOOL_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/ui8";
    uint8_t u8(8);
#ifdef HAVE_POST_0_7_7_SYSREPO
    s_val.reset(new Val(u8));
#else
    s_val.reset(new Val(u8, SR_UINT8_T));
#endif
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/ui16";
    uint16_t u16(16);
#ifdef HAVE_POST_0_7_7_SYSREPO
    s_val.reset(new Val(u16));
#else
    s_val.reset(new Val(u16, SR_UINT16_T));
#endif
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/ui32";
    uint32_t u32(32);
#ifdef HAVE_POST_0_7_7_SYSREPO
    s_val.reset(new Val(u32));
#else
    s_val.reset(new Val(u32, SR_UINT32_T));
#endif
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/i8";
    int8_t s8(8);
#ifdef HAVE_POST_0_7_7_SYSREPO
    s_val.reset(new Val(s8));
#else
    s_val.reset(new Val(s8, SR_INT8_T));
#endif
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/i16";
    int16_t s16(16);
#ifdef HAVE_POST_0_7_7_SYSREPO
    s_val.reset(new Val(s16));
#else
    s_val.reset(new Val(s16, SR_INT16_T));
#endif
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/i32";
    int32_t s32(32);
#ifdef HAVE_POST_0_7_7_SYSREPO
    s_val.reset(new Val(s32));
#else
    s_val.reset(new Val(s32, SR_INT32_T));
#endif
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/id_ref";
    s_val.reset(new Val("keatest-module:id_1", SR_IDENTITYREF_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    xpath = "/keatest-module:main/enum";
    s_val.reset(new Val("maybe", SR_ENUM_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    // Binary.
    xpath = "/keatest-module:main/raw";
    s_val.reset(new Val("Zm9vYmFy", SR_BINARY_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));

    // Get it.
    YangRepr repr(testModel);
    YRTree tree;
    EXPECT_NO_THROW(tree = repr.get(sess));

    // Verify.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));
}

// This test verifies that errors are handled properly.
TEST(YangReprTrest, getTestErrors) {
    // Get a translator object to play with.
    S_Connection conn(new Connection("utils unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Get it.
    YangRepr repr(testModel);
    YRTree tree;
    EXPECT_NO_THROW(repr.set(testTree, sess));

    // Verify.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));

    // Some error messages will be displayed.
    cout << "Some error messages will be displayed. Please ignore." << endl;

    // Change a path.
    YRTree badpath = testTree;
    badpath[14].xpath_ = "/keatest-module:kernel-module"; // removed final 's'
    EXPECT_FALSE(repr.verify(badpath, sess, cerr));

    // Change a value.
    YRTree badvalue = testTree;
    badvalue[3].value_ = "Str"; // was "str"
    EXPECT_FALSE(repr.verify(badvalue, sess, cerr));

    // Change a type.
    YRTree badtype = testTree;
    badtype[10].type_ = SR_UINT32_T; // was SR_INT32_T
    EXPECT_FALSE(repr.verify(badtype, sess, cerr));

    // Add a record at the end.
    YRTree badmissing = testTree;
    const string& xpathpc = "/keatest-module:presence-container";
    badmissing.push_back(YRItem(xpathpc, "", SR_CONTAINER_PRESENCE_T, false));
    EXPECT_FALSE(repr.verify(badmissing, sess, cerr));

    // Delete last record.
    YRTree badextra = testTree;
    badextra.pop_back();
    EXPECT_FALSE(repr.verify(badextra, sess, cerr));
}

// Test set with test module.
TEST(YangReprTest, setTest) {
    // Get a translator object to play with.
    S_Connection conn(new Connection("utils unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

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
    // Get a translator object to play with.
    S_Connection conn(new Connection("utils unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));

    // Get it.
    YangRepr repr(model);

    EXPECT_NO_THROW(repr.set(tree, sess))
        << " for model " << model;
    bool result = false;
    EXPECT_NO_THROW(result = repr.verify(tree, sess, cerr))
        << " for model " << model;
    EXPECT_TRUE(result);
}

// This is test environment sanity check. It verifies that all configuration
// defined in yang_configs.h are sane.
TEST(YangReprTest, verifyConfigs) {
    for (auto x : test_configs) {
        sanityCheckConfig(x.first, x.second);
    }
}

}; // end of anonymous namespace
