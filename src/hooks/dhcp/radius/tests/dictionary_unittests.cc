// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
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
        static_cast<void>(remove(TEST_FILE));
    }

    /// @brief Parse a line.
    ///
    /// @param line line to parse.
    /// @param before vendor id on input (default to 0).
    /// @param after expected vendor id on output (default to 0).
    /// @param depth recursion depth.
    void parseLine(const string& line, uint32_t before = 0,
                   uint32_t after = 0, unsigned int depth = 0) {
        istringstream is(line + "\n");
        uint32_t vendor = before;
        AttrDefs::instance().readDictionary(is, vendor, depth);
        EXPECT_EQ(after, vendor);
    }

    /// @brief Parse a list of lines.
    ///
    /// @param lines list of lines.
    /// @param before vendor id on input (default to 0).
    /// @param after expected vendor id on output (default to 0).
    /// @param depth recursion depth.
    void parseLines(const list<string>& lines, uint32_t before = 0,
                   uint32_t after = 0, unsigned int depth = 0) {
        string content;
        for (auto const& line : lines) {
            content += line + "\n";
        }
        istringstream is(content);
        uint32_t vendor = before;
        AttrDefs::instance().readDictionary(is, vendor, depth);
        EXPECT_EQ(after, vendor);
    }

    /// @brief writes specified content to a file.
    ///
    /// @param file_name name of file to be written.
    /// @param content content to be written to file.
    void writeFile(const std::string& file_name, const std::string& content) {
        static_cast<void>(remove(file_name.c_str()));
        ofstream out(file_name.c_str(), ios::trunc);
        EXPECT_TRUE(out.is_open());
        out << content;
        out.close();
    }

    /// Name of a dictionary file used during tests.
    static const char* TEST_FILE;
};

const char* DictionaryTest::TEST_FILE  = "test-dictionary";

// Verifies standards definitions can be read from the dictionary.
TEST_F(DictionaryTest, standard) {
    uint32_t vendor = 0;
    ASSERT_NO_THROW_LOG(AttrDefs::instance().readDictionary(TEST_DICTIONARY,
                                                            vendor));
    EXPECT_EQ(0, vendor);
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

    EXPECT_THROW_MSG(parseLine("$INCLUDE"), BadValue,
                     "expected 2 tokens, got 1 at line 1");
    EXPECT_THROW_MSG(parseLine("$INCLUDE foo bar"), BadValue,
                     "expected 2 tokens, got 3 at line 1");
    EXPECT_THROW_MSG(parseLine("VENDOR my-vendor"), BadValue,
                     "expected 3 tokens, got 2 at line 1");
    EXPECT_THROW_MSG(parseLine("VENDOR my-vendor 44 17"), BadValue,
                     "expected 3 tokens, got 4 at line 1");
    EXPECT_THROW_MSG(parseLine("VENDOR my-vendor 0"), BadValue,
                     "0 is reserved at line 1");
    EXPECT_THROW_MSG(parseLine("BEGIN-VENDOR"), BadValue,
                     "expected 2 tokens, got 1 at line 1");
    EXPECT_THROW_MSG(parseLine("BEGIN-VENDOR  my-vendor 1"), BadValue,
                     "expected 2 tokens, got 3 at line 1");
    EXPECT_THROW_MSG(parseLine("END-VENDOR", 1), BadValue,
                     "expected 2 tokens, got 1 at line 1");
    EXPECT_THROW_MSG(parseLine("END-VENDOR  my-vendor 1", 1), BadValue,
                     "expected 2 tokens, got 3 at line 1");

    EXPECT_THROW_MSG(parseLine("BEGIN-TLV my-vendor"), BadValue,
                     "unknown dictionary entry 'BEGIN-TLV' at line 1");
    EXPECT_THROW_MSG(parseLine("END-TLV my-vendor"), BadValue,
                     "unknown dictionary entry 'END-TLV' at line 1");
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

    // Only the attribute 26 (Vendor-Specific) can have the vsa data type.
    list<string> bad_vsa = {
        "ATTRIBUTE Attr126 126 vsa"
    };
    expected = "only Vendor-Specific (26) attribute can have ";
    expected += "the vsa data type at line 1";
    EXPECT_THROW_MSG(parseLines(bad_vsa), BadValue, expected);

    list<string> vsa = {
        "ATTRIBUTE Attr26 26 vsa"
    };
    EXPECT_NO_THROW_LOG(parseLines(vsa));
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

// Verifies vendor id definitions.
TEST_F(DictionaryTest, vendorId) {
    // Value must be an integer.
    list<string> not_integer_val = {
        "VENDOR My-Value Non-Integer"
    };
    EXPECT_THROW_MSG(parseLines(not_integer_val), BadValue,
                     "can't parse integer value Non-Integer at line 1");

    // Positive case.
    list<string> positive = {
        "VENDOR ISC 2495"
    };
    EXPECT_NO_THROW_LOG(parseLines(positive));

    // Redefine the same vendor id.
    list<string> same = {
        "VENDOR ISC 2495",
        "VENDOR ISC 2495"
    };
    EXPECT_NO_THROW_LOG(parseLines(same));

    // Redefine with a different value is not allowed.
    list<string> new_value = {
        "VENDOR ISC 2495",
        "VENDOR ISC 24950",
    };
    string expected = "Illegal vendor id redefinition of ";
    expected += "'ISC' value 2495 by 24950 at line 2";
    EXPECT_THROW_MSG(parseLines(new_value), BadValue, expected);
}

// Verifies begin and end vendor entries.
TEST_F(DictionaryTest, beginEndVendor) {
    // Begin already open.
    list<string> begin_unknown = {
        "BEGIN-VENDOR foo"
    };
    string expected =  "unsupported embedded begin vendor, ";
    expected += "1 is still open at line 1";
    EXPECT_THROW_MSG(parseLines(begin_unknown, 1), BadValue, expected);
    // Value must be a known name or integer.
    EXPECT_THROW_MSG(parseLines(begin_unknown), BadValue,
                     "can't parse integer value foo at line 1");
    // End not yet open.
    list<string> end_unknown = {
        "END-VENDOR foo"
    };
    EXPECT_THROW_MSG(parseLines(end_unknown), BadValue,
                     "no matching begin vendor at line 1");
    EXPECT_THROW_MSG(parseLines(end_unknown, 1), BadValue,
                     "can't parse integer value foo at line 1");
    // 0 is reserved.
    list<string> begin0 = {
        "BEGIN-VENDOR 0"
    };
    EXPECT_THROW_MSG(parseLines(begin0), BadValue,
                     "0 is reserved at line 1");

    // Positive using a name.
    list<string> positive = {
        "VENDOR DSL-Forum 3561",
        "BEGIN-VENDOR DSL-Forum",
        "ATTRIBUTE Agent-Circuit-Id 1 string"
    };
    EXPECT_NO_THROW_LOG(parseLines(positive, 0, 3561));
    auto aci = AttrDefs::instance().getByName("Agent-Circuit-Id", 3561);
    ASSERT_TRUE(aci);
    EXPECT_EQ(1, aci->type_);
    EXPECT_EQ(PW_TYPE_STRING, aci->value_type_);
    EXPECT_EQ("Agent-Circuit-Id", aci->name_);
    EXPECT_EQ(3561, aci->vendor_);

    // Positive using an integer.
    list<string> positive_n = {
        "BEGIN-VENDOR 3561",
        "ATTRIBUTE Actual-Data-Rate-Upstream 129 integer"
    };
    EXPECT_NO_THROW_LOG(parseLines(positive_n, 0, 3561));
    auto adru =  AttrDefs::instance().getByType(129, 3561);
    ASSERT_TRUE(adru);
    EXPECT_EQ(129, adru->type_);
    EXPECT_EQ(PW_TYPE_INTEGER, adru->value_type_);
    EXPECT_EQ("Actual-Data-Rate-Upstream", adru->name_);
    EXPECT_EQ(3561, adru->vendor_);

    // End using a name.
    list<string> end_name = {
        "END-VENDOR DSL-Forum"
    };
    EXPECT_NO_THROW_LOG(parseLines(end_name, 3561, 0));

    // End using an integer.
    list<string> end_int = {
        "END-VENDOR 3561"
        };
    EXPECT_NO_THROW_LOG(parseLines(end_int, 3561, 0));

    // Not matching.
    list<string> no_match = {
        "BEGIN-VENDOR 1234",
        "END-VENDOR 2345"
    };
    expected = "begin vendor 1234 and end vendor 2345 do not match at line 2";
    EXPECT_THROW_MSG(parseLines(no_match), BadValue, expected);
}

// Verifies errors from bad dictionary files.
TEST_F(DictionaryTest, badFile) {
    string expected = "can't open dictionary '/does-not-exist': ";
    expected += "No such file or directory";
    uint32_t vendor = 0;
    EXPECT_THROW_MSG(AttrDefs::instance().readDictionary("/does-not-exist",
                                                         vendor),
                     BadValue, expected);
    EXPECT_EQ(0, vendor);
    list<string> bad_include = {
        "$INCLUDE /does-not-exist"
    };
    expected += " at line 1";
    EXPECT_THROW_MSG(parseLines(bad_include), BadValue, expected);
}

// Definitions of Standard attributes used by the hook.

// Verifies that the dictionary correctly defines used standard attributes.
TEST_F(DictionaryTest, hookAttributes) {
    uint32_t vendor = 0;
    ASSERT_NO_THROW_LOG(AttrDefs::instance().readDictionary(TEST_DICTIONARY,
                                                            vendor));
    EXPECT_EQ(0, vendor);
    EXPECT_NO_THROW_LOG(AttrDefs::instance().
        checkStandardDefs(RadiusConfigParser::USED_STANDARD_ATTR_DEFS));
}

// Verifies the $INCLUDE entry.
TEST_F(DictionaryTest, include) {
    list<string> include;
    include.push_back("# Including the dictonary");
    include.push_back(string("$INCLUDE ") + string(TEST_DICTIONARY));
    include.push_back("# Dictionary included");
    include.push_back("VENDOR ISC 2495");
    EXPECT_NO_THROW_LOG(parseLines(include));
    EXPECT_NO_THROW_LOG(AttrDefs::instance().
        checkStandardDefs(RadiusConfigParser::USED_STANDARD_ATTR_DEFS));
    auto isc = AttrDefs::instance().getByName(PW_VENDOR_SPECIFIC, "ISC");
    ASSERT_TRUE(isc);
    EXPECT_EQ(2495, isc->value_);

    // max depth is 5.
    EXPECT_THROW_MSG(parseLines(include, 0, 0, 4), BadValue,
                     "Too many nested $INCLUDE at line 2");
}

// Verifies the $INCLUDE entry can't eat the stack.
TEST_F(DictionaryTest, includeLimit) {
    string include = "$INCLUDE " + string(TEST_FILE) + "\n";
    writeFile(TEST_FILE, include);
    string expected = "Too many nested $INCLUDE ";
    expected += "at line 1 in dictionary 'test-dictionary', ";
    expected += "at line 1 in dictionary 'test-dictionary', ";
    expected += "at line 1 in dictionary 'test-dictionary', ";
    expected += "at line 1 in dictionary 'test-dictionary', ";
    expected += "at line 1";
    EXPECT_THROW_MSG(parseLine(string("$INCLUDE ") + string(TEST_FILE)),
                     BadValue, expected);
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
    uint32_t vendor = 0;
    for (size_t i = 0; i < g.glob_buffer_.gl_pathc; ++i) {
        const string file_name(g.glob_buffer_.gl_pathv[i]);
        SCOPED_TRACE(file_name);
        EXPECT_NO_THROW_LOG(defs.readDictionary(file_name, vendor));
    }
    EXPECT_EQ(0, vendor);
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
    EXPECT_EQ(0, def->vendor_);
    def.reset();

    // Type 0 is reserved.
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(0));
    EXPECT_FALSE(def);
    def.reset();

    // Only vendor 0 i.e. no vendor was populated.
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(1, 1234));
    EXPECT_FALSE(def);
    def.reset();

    // getByName.
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("User-Name"));
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ("User-Name", def->name_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    EXPECT_EQ(0, def->vendor_);
    def.reset();

    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("Does-not-exist"));
    EXPECT_FALSE(def);
    def.reset();

    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("User-Name", 1234));
    EXPECT_FALSE(def);
    def.reset();

    // getName.
    string name;
    ASSERT_NO_THROW(name = AttrDefs::instance().getName(1));
    EXPECT_EQ("User-Name", name);
    name.clear();
    ASSERT_NO_THROW(name = AttrDefs::instance().getName(252));
    EXPECT_EQ("Attribute-252", name);
    name.clear();
    ASSERT_NO_THROW(name = AttrDefs::instance().getName(1, 1234));
    EXPECT_EQ("Attribute-1", name);
    name.clear();

    // add (new).
    AttrDefPtr def1(new AttrDef(252, "Foo-Bar", PW_TYPE_IPADDR));
    ASSERT_NO_THROW(AttrDefs::instance().add(def1));
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(252));
    ASSERT_TRUE(def);
    EXPECT_EQ(252, def->type_);
    EXPECT_EQ("Foo-Bar", def->name_);
    EXPECT_EQ(PW_TYPE_IPADDR, def->value_type_);
    EXPECT_EQ(0, def->vendor_);
    def.reset();
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("Foo-Bar"));
    ASSERT_TRUE(def);
    EXPECT_EQ(252, def->type_);
    EXPECT_EQ("Foo-Bar", def->name_);
    EXPECT_EQ(PW_TYPE_IPADDR, def->value_type_);
    EXPECT_EQ(0, def->vendor_);
    def.reset();

    // add (alias).
    EXPECT_EQ("Reply-Message", AttrDefs::instance().getName(18));
    AttrDefPtr def2(new AttrDef(18, "Error-Message", PW_TYPE_STRING));
    ASSERT_NO_THROW(AttrDefs::instance().add(def2));
    AttrDefPtr got = AttrDefs::instance().getByName("Error-Message");
    ASSERT_TRUE(got);
    EXPECT_EQ(18, got->type_);
    EXPECT_EQ(PW_TYPE_STRING, got->value_type_);
    EXPECT_EQ(0, got->vendor_);
    def.reset();

    // add (vendor).
    AttrDefPtr defv(new AttrDef(1, "Agent-Circuit-Id", PW_TYPE_STRING, 3561));
    ASSERT_NO_THROW(AttrDefs::instance().add(defv));
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(1, 3561));
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ("Agent-Circuit-Id", def->name_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    EXPECT_EQ(3561, def->vendor_);
    def.reset();
    ASSERT_NO_THROW(def =
        AttrDefs::instance().getByName("Agent-Circuit-Id", 3561));
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ("Agent-Circuit-Id", def->name_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    EXPECT_EQ(3561, def->vendor_);
    def.reset();
    ASSERT_NO_THROW(name = AttrDefs::instance().getName(1, 3561));
    EXPECT_EQ("Agent-Circuit-Id", name);
    name.clear();

    // add (change type).
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("User-Password"));
    ASSERT_TRUE(def);
    EXPECT_EQ(2, def->type_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    EXPECT_EQ(0, def->vendor_);
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

    // Same with vendor.
    ASSERT_NO_THROW(def =
        AttrDefs::instance().getByName("Agent-Circuit-Id", 3561));
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);
    EXPECT_EQ(3561, def->vendor_);
    AttrDefPtr def3v(new AttrDef(2, "Agent-Circuit-Id", PW_TYPE_STRING, 3561));
    expected = "Illegal attribute redefinition of 'Agent-Circuit-Id' ";
    expected += "vendor 3561 type 1 value type string by 2 string";
    EXPECT_THROW_MSG(AttrDefs::instance().add(def3v), BadValue, expected);
    AttrDefPtr def4v(new AttrDef(1, "Agent-Circuit-Id", PW_TYPE_INTEGER, 3561));
    expected = "Illegal attribute redefinition of 'Agent-Circuit-Id' ";
    expected += "vendor 3561 type 1 value type string by 1 integer";
    EXPECT_THROW_MSG(AttrDefs::instance().add(def4v), BadValue, expected);
    AttrDefPtr def5v(new AttrDef(1, "Agent-Remote-Id", PW_TYPE_INTEGER, 3561));
    expected = "Illegal attribute redefinition of 'Agent-Circuit-Id' ";
    expected += "vendor 3561 type 1 value type string by ";
    expected += "'Agent-Remote-Id' 1 integer";
    EXPECT_THROW_MSG(AttrDefs::instance().add(def5v), BadValue, expected);

    // clear.
    ASSERT_NO_THROW(AttrDefs::instance().clear());
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(1));
    EXPECT_FALSE(def);
    def.reset();
    ASSERT_NO_THROW(def = AttrDefs::instance().getByType(1, 3561));
    EXPECT_FALSE(def);
    def.reset();
    ASSERT_NO_THROW(def = AttrDefs::instance().getByName("Foo-Bar"));
    EXPECT_FALSE(def);
}

} // end of anonymous namespace
