// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the attribute,
/// attribute collection and config attribute collection classes.

#include <config.h>

#include <client_attribute.h>
#include <radius_parsers.h>
#include <attribute_test.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>
#include <glob.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::radius::test;
using namespace isc::test;

namespace {

// Test if AttrDefs behaves like a singleton.
TEST(AttrDefsTest, singleton) {
    AttrDefs& instance(AttrDefs::instance());
    AttrDefs& instance2(AttrDefs::instance());
    EXPECT_EQ(&instance, &instance2);
    EXPECT_FALSE(std::is_copy_constructible<AttrDefs>::value);
}

/// @brief Test fixture for testing code reading dictionary.
class DictionaryTest : public ::testing::Test {
public:
    /// @brief Constructor.
    DictionaryTest() {
        AttrDefs::instance().clear();
    }

    /// @brief Destructor.
    virtual ~DictionaryTest() {
        AttrDefs::instance().clear();
    }

    /// @brief Parse a line.
    ///
    /// @param line line to parse.
    void parseLine(const string& line) {
        istringstream is(line + "\n");
        AttrDefs::instance().readDictionary(is);
    }

    /// @brief Parse a list of lines.
    ///
    /// @param lines list of lines.
    void parseLines(const list<string>& lines) {
        string content;
        for (auto const& line : lines) {
            content += line + "\n";
        }
        istringstream is(content);
        AttrDefs::instance().readDictionary(is);
    }
};

// Verifies standards definitions can be read from the dictionary.
TEST_F(DictionaryTest, standard) {
    ASSERT_NO_THROW_LOG(AttrDefs::instance().readDictionary(TEST_DICTIONARY));
}

// Verifies parseLine internal routine.
TEST_F(DictionaryTest, parseLine) {
    EXPECT_NO_THROW_LOG(parseLine(""));
    EXPECT_NO_THROW_LOG(parseLine("#"));
    EXPECT_NO_THROW_LOG(parseLine("# comment"));
    EXPECT_NO_THROW_LOG(parseLine("#comment_glued_to_hash"));
    EXPECT_NO_THROW_LOG(parseLine("##"));
    EXPECT_NO_THROW_LOG(parseLine("## comment"));
    EXPECT_NO_THROW_LOG(parseLine("##comment_glued_to_hash"));
    EXPECT_NO_THROW_LOG(parseLine("ATTRIBUTE User-Name 1 string"));
    EXPECT_NO_THROW_LOG(parseLine("ATTRIBUTE\tUser-Name\t1\tstring"));
    EXPECT_NO_THROW_LOG(parseLine("ATTRIBUTE NAS-Port-Id 5 integer"));
    EXPECT_NO_THROW_LOG(parseLine("VALUE NAS-Port-Id My-Port-Id 1"));
    EXPECT_NO_THROW_LOG(parseLine("VALUE\tNAS-Port-Id\tMy-Port-Id\t1"));
    EXPECT_NO_THROW_LOG(parseLine("ATTRIBUTE User-Name 1000 foobar"));

    EXPECT_THROW_MSG(parseLine("ATTRIBUTE"), BadValue,
                     "expected 4 tokens, got 1 at line 1");
    EXPECT_THROW_MSG(parseLine("ATTRIBUTE My-Attribute"), BadValue,
                     "expected 4 tokens, got 2 at line 1");
    EXPECT_THROW_MSG(parseLine("ATTRIBUTE My-Attribute 3477"), BadValue,
                     "expected 4 tokens, got 3 at line 1");
    EXPECT_THROW_MSG(parseLine("ATTRIBUTE My-Attribute Non-Integer string"),
                     BadValue,
                     "can't parse attribute type Non-Integer at line 1");
    EXPECT_THROW_MSG(parseLine("ATTRIBUTE My-Attribute 185 datatype"),
                     BadValue,
                     "unknown AttrValueType name datatype at line 1");
    EXPECT_THROW_MSG(parseLine("VALUE"), BadValue,
                     "expected 4 tokens, got 1 at line 1");
    EXPECT_THROW_MSG(parseLine("VALUE My-Attribute"), BadValue,
                     "expected 4 tokens, got 2 at line 1");
    EXPECT_THROW_MSG(parseLine("VALUE My-Attribute My-Value"), BadValue,
                     "expected 4 tokens, got 3 at line 1");
    EXPECT_THROW_MSG(parseLine("VALUE My-Attribute My-Value 1"), BadValue,
                     "unknown attribute 'My-Attribute' at line 1");
    EXPECT_THROW_MSG(parseLine("VENDOR my-vendor 4417"), BadValue,
                     "unknown dictionary entry 'VENDOR' at line 1");
}

// Verifies sequences attribute of (re)definitions.
TEST_F(DictionaryTest, parseLines) {
    // Redefine the same attribute is allowed.
    list<string> same = {
        "ATTRIBUTE User-Name 1 string",
        "ATTRIBUTE User-Name 1 string"
    };
    EXPECT_NO_THROW_LOG(parseLines(same));

    // Define an alias name is allowed.
    list<string> alias = {
        "ATTRIBUTE User-Password 2 string",
        "ATTRIBUTE Password 2 string"
    };
    EXPECT_NO_THROW_LOG(parseLines(alias));

    // Redefine with a different type is not allowed.
    list<string> new_type = {
        "ATTRIBUTE Service-Type 6 integer",
        "ATTRIBUTE Service-Type 66 integer"
    };
    string expected = "Illegal attribute redefinition of 'Service-Type' ";
    expected += "type 6 value type integer by 66 integer at line 2";
    EXPECT_THROW_MSG(parseLines(new_type), BadValue, expected);

    // Redefine with a different value type is not allowed.
    list<string> new_value_type = {
        "ATTRIBUTE Service-Type 6 integer",
        "ATTRIBUTE Service-Type 6 string"
    };
    expected = "Illegal attribute redefinition of 'Service-Type' ";
    expected += "type 6 value type integer by 6 string at line 2";
    EXPECT_THROW_MSG(parseLines(new_value_type), BadValue, expected);
}

// Verifies integer constant definitions.
TEST_F(DictionaryTest, integerConstant) {
    // Attribute must be an integer one.
    list<string> not_integer_attr = {
        "ATTRIBUTE User-Name 1 string",
        "VALUE User-Name My-Value 1"
    };
    string expected = "attribute 'User-Name' is not an integer attribute";
    expected += " at line 2";
    EXPECT_THROW_MSG(parseLines(not_integer_attr), BadValue, expected);

    // Value must be an integer.
    list<string> not_integer_val = {
        "ATTRIBUTE Acct-Status-Type 40 integer",
        "VALUE Acct-Status-Type My-Value Non-Integer"
    };
    EXPECT_THROW_MSG(parseLines(not_integer_val), BadValue,
                     "can't parse integer value Non-Integer at line 2");

    // Positive case.
    list<string> positive = {
        "ATTRIBUTE Acct-Status-Type 40 integer",
        "VALUE Acct-Status-Type Start 1"
    };
    EXPECT_NO_THROW_LOG(parseLines(positive));

    // Redefine the same integer constant.
    list<string> same = {
        "ATTRIBUTE Acct-Status-Type 40 integer",
        "VALUE Acct-Status-Type Start 1",
        "VALUE Acct-Status-Type Start 1"
    };
    EXPECT_NO_THROW_LOG(parseLines(same));

    // Redefine with a different value is not allowed.
    list<string> new_value = {
        "ATTRIBUTE Acct-Status-Type 40 integer",
        "VALUE Acct-Status-Type Start 1",
        "VALUE Acct-Status-Type Start 2"
    };
    expected = "Illegal integer constant redefinition of ";
    expected += "'Start' for attribute 'Acct-Status-Type' value 1 by 2";
    expected += " at line 3";
    EXPECT_THROW_MSG(parseLines(new_value), BadValue, expected);
}

// Verifies errors from bad dictionary files.
TEST_F(DictionaryTest, badFile) {
    string expected = "can't open dictionary '/does-not-exist': ";
    expected += "No such file or directory";
    EXPECT_THROW_MSG(AttrDefs::instance().readDictionary("/does-not-exist"),
                     BadValue, expected);
}

// Definitions of Standard attributes used by the hook.

// Verifies that the dictionary correctly defines used standard attributes.
TEST_F(DictionaryTest, hookAttributes) {
    ASSERT_NO_THROW_LOG(AttrDefs::instance().readDictionary(TEST_DICTIONARY));
    EXPECT_NO_THROW_LOG(AttrDefs::instance().
        checkStandardDefs(RadiusConfigParser::USED_STANDARD_ATTR_DEFS));
}

namespace {

// RAII device freeing the glob buffer when going out of scope.
struct Glob {
    Glob(const string& path_regex) {
        glob(path_regex.c_str(), 0, 0, &glob_buffer_);
    }

    ~Glob() {
        globfree(&glob_buffer_);
    }

    glob_t glob_buffer_;
};

} // end of anonymous namespace.

// Disabled by default. You can temporarily enable it to run the parser on all
// dictionaries in the /usr/share/freeradius directory.
TEST_F(DictionaryTest, DISABLED_readDictionaries) {
    const string path_regex("/usr/share/freeradius/*");
    Glob g(path_regex);
    AttrDefs& defs(AttrDefs::instance());
    for (size_t i = 0; i < g.glob_buffer_.gl_pathc; ++i) {
        const string file_name(g.glob_buffer_.gl_pathv[i]);
        SCOPED_TRACE(file_name);
        EXPECT_NO_THROW_LOG(defs.readDictionary(file_name));
    }
}

// Verifies attribute definitions.
TEST_F(AttributeTest, attrDefs) {
    AttrDefPtr def;

    // getByType.
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(1));
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ("User-Name", def->name_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    def.reset();

    // Type 0 is reserved.
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(0));
    EXPECT_FALSE(def);
    def.reset();

    // getByName.
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("User-Name"));
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ("User-Name", def->name_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    def.reset();

    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("Does-not-exist"));
    EXPECT_FALSE(def);
    def.reset();

    // getName.
    string name;
    ASSERT_NO_THROW(name = AttrDefs::instance().getName(1));
    EXPECT_EQ("User-Name", name);
    name.clear();
    ASSERT_NO_THROW(name = AttrDefs::instance().getName(252));
    EXPECT_EQ("Attribute-252", name);

    // add (new).
    AttrDefPtr def1(new AttrDef(252, "Foo-Bar", PW_TYPE_IPADDR));
    ASSERT_NO_THROW(AttrDefs::instance().add(def1));
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(252));
    ASSERT_TRUE(def);
    EXPECT_EQ(252, def->type_);
    EXPECT_EQ("Foo-Bar", def->name_);
    EXPECT_EQ(PW_TYPE_IPADDR, def->value_type_);
    def.reset();
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("Foo-Bar"));
    ASSERT_TRUE(def);
    EXPECT_EQ(252, def->type_);
    EXPECT_EQ("Foo-Bar", def->name_);
    EXPECT_EQ(PW_TYPE_IPADDR, def->value_type_);
    def.reset();

    // add (alias).
    EXPECT_EQ("Reply-Message", AttrDefs::instance().getName(18));
    AttrDefPtr def2(new AttrDef(18, "Error-Message", PW_TYPE_STRING));
    ASSERT_NO_THROW(AttrDefs::instance().add(def2));
    AttrDefPtr got = AttrDefs::instance().getByName("Error-Message");
    ASSERT_TRUE(got);
    EXPECT_EQ(18, got->type_);
    EXPECT_EQ(PW_TYPE_STRING, got->value_type_);

    // add (change type).
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("User-Password"));
    ASSERT_TRUE(def);
    EXPECT_EQ(2, def->type_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    AttrDefPtr def3(new AttrDef(17, "User-Password", PW_TYPE_STRING));
    string expected = "Illegal attribute redefinition of ";
    expected += "'User-Password' type 2 value type string by 17 string";
    EXPECT_THROW_MSG(AttrDefs::instance().add(def3), BadValue, expected);

    // add (change value type).
    AttrDefPtr def4(new AttrDef(2, "User-Password", PW_TYPE_INTEGER));
    expected = "Illegal attribute redefinition of 'User-Password' ";
    expected += "type 2 value type string by 2 integer";
    EXPECT_THROW_MSG(AttrDefs::instance().add(def4), BadValue, expected);

    // add (change name and value type).
    AttrDefPtr def5(new AttrDef(2, "Password", PW_TYPE_INTEGER));
    expected = "Illegal attribute redefinition of 'User-Password' ";
    expected += "type 2 value type string by 'Password' 2 integer";
    EXPECT_THROW_MSG(AttrDefs::instance().add(def5), BadValue, expected);

    // clear.
    ASSERT_NO_THROW(AttrDefs::instance().clear());
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(1));
    EXPECT_FALSE(def);
    def.reset();
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("Foo-Bar"));
    EXPECT_FALSE(def);
}

} // end of anonymous namespace
