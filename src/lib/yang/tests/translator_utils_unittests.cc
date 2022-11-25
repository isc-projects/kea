// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <testutils/gtest_utils.h>
#include <yang/testutils/translator_test.h>
#include <yang/tests/sysrepo_setup.h>
#include <yang/tests/yang_configs.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace libyang;
using namespace sysrepo;

namespace {

// Test LeafBaseType print.
TEST(YangReprTest, type) {
    ostringstream os;

    // Verify that string is "string" (vs a number).
    LeafBaseType t(LeafBaseType::String);
    os << t;
    EXPECT_EQ("string", os.str());
    os.str("");

    // Compiler does not let to create an invalid value...
}

// Test YangReprItem basic stuff.
TEST(YangReprTest, item) {
    // An item.
    YRItem item1("/foo", "bar", LeafBaseType::String, true);
    EXPECT_EQ("/foo", item1.xpath_);
    EXPECT_EQ("bar", item1.value_);
    EXPECT_TRUE(item1.settable_);

    // EXPECT_EQ doesn't work. Tries to << into a stringstream.
    EXPECT_TRUE(LeafBaseType::String == item1.type_);

    // Another one.
    YRItem item2("/foo", "bar", LeafBaseType::String, false);
    EXPECT_EQ("/foo", item2.xpath_);
    EXPECT_EQ("bar", item2.value_);
    EXPECT_FALSE(item2.settable_);

    // EXPECT_EQ doesn't work. Tries to << into a stringstream.
    EXPECT_TRUE(LeafBaseType::String == item2.type_);

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
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);

    // Cleanup.
    EXPECT_NO_THROW_LOG(sess.deleteItem("/keatest-module:container"));
    EXPECT_NO_THROW_LOG(sess.applyChanges());
    EXPECT_NO_THROW_LOG(sess.deleteItem("/keatest-module:main"));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    // Fill the test module.
    string xpath;
    string value;

    xpath = "/keatest-module:main/string";
    value = "str";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/boolean";
    value = "true";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/ui8";
    uint8_t u8(8);
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/ui16";
    uint16_t u16(16);
    value = to_string(u16);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/ui32";
    uint32_t u32(32);
    value = to_string(u32);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/ui64";
    uint64_t u64(64);
    value = to_string(u64);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/i8";
    int8_t s8(8);
    value = to_string(s8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/i16";
    int16_t s16(16);
    value = to_string(s16);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/i32";
    int32_t s32(32);
    value = to_string(s32);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/i64";
    int64_t s64(64);
    value = to_string(s64);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/id_ref";
    value = "keatest-module:id_1";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    xpath = "/keatest-module:main/enum";
    value = "maybe";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    // Binary.
    xpath = "/keatest-module:main/raw";
    value = "Zm9vYmFy";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    // Get it.
    YangRepr repr(testModel);
    YRTree tree;
    EXPECT_NO_THROW_LOG(tree = repr.get(sess));

    // Verify.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));
}

// This test verifies that errors are handled properly.
TEST(YangReprTrest, getTestErrors) {
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);

    // Cleanup.
    EXPECT_NO_THROW_LOG(sess.deleteItem("/keatest-module:container"));
    EXPECT_NO_THROW_LOG(sess.applyChanges());
    EXPECT_NO_THROW_LOG(sess.deleteItem("/keatest-module:main"));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    // Get it.
    YangRepr repr(testModel);
    YRTree tree;
    EXPECT_NO_THROW_LOG(repr.set(testTree, sess));

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

    // Change a type from LeafBaseType::Int32 to LeafBaseType::Uint32.
    YRTree badtype = testTree;
    xpath = "/keatest-module:main/i32";
    badtype.at(xpath).type_ = LeafBaseType::Uint32;
    EXPECT_FALSE(repr.verify(badtype, sess, cerr));

    // Delete last record.
    YRTree badextra = testTree;
    badextra.erase("/keatest-module:kernel-modules");
    EXPECT_FALSE(repr.verify(badextra, sess, cerr));
}

// Test set with test module.
TEST(YangReprTest, setTest) {
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);

    // Cleanup.
    EXPECT_NO_THROW_LOG(sess.deleteItem("/keatest-module:container"));
    EXPECT_NO_THROW_LOG(sess.applyChanges());
    EXPECT_NO_THROW_LOG(sess.deleteItem("/keatest-module:main"));
    EXPECT_NO_THROW_LOG(sess.applyChanges());

    // Set the module content.
    YangRepr repr(testModel);
    EXPECT_NO_THROW_LOG(repr.set(testTree, sess));

    // Verify it.
    EXPECT_TRUE(repr.verify(testTree, sess, cerr));
}

/// @brief Tests specified configuration.
///
/// Configuration is set and then verified using YangRepr object.
///
/// @param model name of the model to be verified against.
/// @param tree tree to be verified.
void sanityCheckConfig(const string& model, const YRTree& tree) {
    SCOPED_TRACE("\n* Tested model: " + model);
    SysrepoSetup::cleanSharedMemory();

    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);

    // Cleanup.
    Translator translator(sess, model);
    if (model == "keatest-module") {
        translator.deleteItem("/keatest-module:container");
        translator.deleteItem("/keatest-module:kernel-modules");
        translator.deleteItem("/keatest-module:list");
        translator.deleteItem("/keatest-module:main");
        translator.deleteItem("/keatest-module:presence-container");
    } else {
        string toplevel_node("config");
        if (model == IETF_DHCPV6_SERVER) {
            toplevel_node = "server";
        }
        EXPECT_NO_THROW_LOG(translator.deleteItem("/" + model + ":" + toplevel_node));
    }

    // Get it.
    YangRepr repr(model);

    EXPECT_NO_THROW_LOG(repr.set(tree, sess));
    bool result = false;
    EXPECT_NO_THROW_LOG(result = repr.verify(tree, sess, cerr));
    EXPECT_TRUE(result);
}

// This is test environment sanity check. It verifies that all configuration
// defined in yang_configs.h are sane.
TEST(YangReprTest, verifyConfigs) {
    for (auto x : TEST_CONFIGS) {
        sanityCheckConfig(x.first, x.second);
    }
}

}  // namespace
