// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>

#include <cc/data.h>
#include <d2/parser_context.h>
#include <d2/tests/parser_unittest.h>
#include <testutils/io_utils.h>
#include <testutils/log_utils.h>
#include <testutils/test_to_element.h>
#include <testutils/user_context_utils.h>

#include <gtest/gtest.h>

#include <fstream>
#include <set>

#include <boost/algorithm/string.hpp>

#include "test_data_files_config.h"

using namespace isc::data;
using namespace isc::test;
using namespace std;

namespace isc {
namespace d2 {
namespace test {

/// @brief compares two JSON trees
///
/// If differences are discovered, gtest failure is reported (using EXPECT_EQ)
///
/// @param a first to be compared
/// @param b second to be compared
void compareJSON(ConstElementPtr a, ConstElementPtr b) {
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    EXPECT_EQ(a->str(), b->str())
#ifdef HAVE_CREATE_UNIFIED_DIFF
        << "\nDiff:\n" << generateDiff(prettyPrint(a), prettyPrint(b)) << "\n"
#endif
    ;
}

/// @brief Tests if the input string can be parsed with specific parser
///
/// The input text will be passed to bison parser of specified type.
/// Then the same input text is passed to legacy JSON parser and outputs
/// from both parsers are compared. The legacy comparison can be disabled,
/// if the feature tested is not supported by the old parser (e.g.
/// new comment styles)
///
/// @param txt text to be compared
/// @param parser_type bison parser type to be instantiated
/// @param compare whether to compare the output with legacy JSON parser
void testParser(const std::string& txt, D2ParserContext::ParserType parser_type,
    bool compare = true) {
    SCOPED_TRACE("\n=== tested config ===\n" + txt + "=====================");

    ConstElementPtr test_json;
    ASSERT_NO_THROW({
            try {
                D2ParserContext ctx;
                test_json = ctx.parseString(txt, parser_type);
            } catch (const std::exception &e) {
                cout << "EXCEPTION: " << e.what() << endl;
                throw;
            }

    });

    if (!compare) {
        return;
    }

    // Now compare if both representations are the same.
    ElementPtr reference_json;
    ASSERT_NO_THROW(reference_json = Element::fromJSON(txt, true));
    compareJSON(reference_json, test_json);
}

// Generic JSON parsing tests
TEST(ParserTest, mapInMap) {
    string txt = "{ \"xyzzy\": { \"foo\": 123, \"baz\": 456 } }";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, listInList) {
    string txt = "[ [ \"Britain\", \"Wales\", \"Scotland\" ], "
                 "[ \"Pomorze\", \"Wielkopolska\", \"Tatry\"] ]";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, nestedMaps) {
    string txt = "{ \"europe\": { \"UK\": { \"London\": { \"street\": \"221B Baker\" }}}}";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, nestedLists) {
    string txt = "[ \"half\", [ \"quarter\", [ \"eighth\", [ \"sixteenth\" ]]]]";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, listsInMaps) {
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelgeuse\" ], "
                    "\"cygnus\": [ \"deneb\", \"albireo\"] } }";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, mapsInLists) {
    string txt = "[ { \"body\": \"earth\", \"gravity\": 1.0 },"
                 " { \"body\": \"mars\", \"gravity\": 0.376 } ]";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, types) {
    string txt = "{ \"string\": \"foo\","
                   "\"integer\": 42,"
                   "\"boolean\": true,"
                   "\"map\": { \"foo\": \"bar\" },"
                   "\"list\": [ 1, 2, 3 ],"
                   "\"null\": null }";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

TEST(ParserTest, keywordJSON) {
    string txt = "{ \"name\": \"user\","
                   "\"type\": \"password\","
                   "\"user\": \"name\","
                   "\"password\": \"type\" }";
    testParser(txt, D2ParserContext::PARSER_JSON);
}

// PARSER_DHCPDDNS parser tests
TEST(ParserTest, keywordDhcpDdns) {
    string txt =
        "{ \"DhcpDdns\" : \n"
           "{ \n"
            " \"ip-address\": \"192.168.77.1\", \n"
            " \"port\": 777 , \n "
            " \"ncr-protocol\": \"UDP\", \n"
            " \"tsig-keys\": [], \n"
            " \"forward-ddns\" : {}, \n"
            " \"reverse-ddns\" : {} \n"
            "} \n"
         "} \n";
     testParser(txt, D2ParserContext::PARSER_DHCPDDNS);
}

// Tests if bash (#) comments are supported. That's the only comment type that
// was supported by the old parser.
TEST(ParserTest, bashComments) {
    string txt =
        "{ \"DhcpDdns\" : \n"
           "{ \n"
            " \"ip-address\": \"192.168.77.1\", \n"
            "# this is a comment\n"
            " \"port\": 777, \n "
            " \"ncr-protocol\": \"UDP\", \n"
            "# lots of comments here\n"
            "# and here\n"
            "\"tsig-keys\": [], \n"
            "\"forward-ddns\" : {}, \n"
            "\"reverse-ddns\" : {} \n"
            "} \n"
         "} \n";
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS);
}

// Tests if C++ (//) comments can start anywhere, not just in the first line.
TEST(ParserTest, cppComments) {
    string txt =
        "{ \"DhcpDdns\" : \n"
           "{ \n"
            " \"ip-address\": \"192.168.77.1\", \n"
            " \"port\": 777, // this is a comment \n"
            " \"ncr-protocol\": \"UDP\", // everything after // is ignored\n"
            "\"tsig-keys\": [], // this will be ignored, too\n"
            "\"forward-ddns\" : {}, \n"
            "\"reverse-ddns\" : {} \n"
            "} \n"
         "} \n";
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS, false);
}

// Tests if bash (#) comments can start anywhere, not just in the first line.
TEST(ParserTest, bashCommentsInline) {
    string txt =
        "{ \"DhcpDdns\" : \n"
           "{ \n"
            " \"ip-address\": \"192.168.77.1\", \n"
            " \"port\": 777, # this is a comment \n"
            " \"ncr-protocol\": \"UDP\", # everything after # is ignored\n"
            "\"tsig-keys\": [], # this will be ignored, too\n"
            "\"forward-ddns\" : {}, \n"
            "\"reverse-ddns\" : {} \n"
            "} \n"
         "} \n";
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS, false);
}

// Tests if multi-line C style comments are handled correctly.
TEST(ParserTest, multilineComments) {
    string txt =
        "{ \"DhcpDdns\" : \n"
           "{ \n"
            " \"ip-address\": \"192.168.77.1\", \n"
            " \"port\": 777, /* this is a C style comment\n"
            "that\n can \n span \n multiple \n lines */ \n"
            " \"ncr-protocol\": \"UDP\", \n"
            "\"tsig-keys\": [], \n"
            "\"forward-ddns\" : {}, \n"
            "\"reverse-ddns\" : {} \n"
            "} \n"
         "} \n";
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS, false);
}

// Tests if embedded comments are handled correctly.
TEST(ParserTest, embbededComments) {
    string txt =
        "{ \"DhcpDdns\" : \n"
           "{ \n"
            "\"comment\": \"a comment\",\n"
            " \"ip-address\": \"192.168.77.1\", \n"
            " \"port\": 777, \n "
            " \"ncr-protocol\": \"UDP\", \n"
            "\"tsig-keys\" : [ { \n"
            "    \"name\" : \"d2.md5.key\", \n"
            "    \"user-context\" : { \"comment\" : \"indirect\" } } ], \n"
            "\"forward-ddns\" : {}, \n"
            "\"reverse-ddns\" : {}, \n"
            "\"user-context\": { \"compatible\": true }"
            "} \n"
         "} \n";
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS, false);
}

/// @brief Loads specified example config file
///
/// This test loads specified example file twice: first, using the legacy
/// JSON file and then second time using bison parser. Two created Element
/// trees are then compared. The input is decommented before it is passed
/// to legacy parser (as legacy support for comments is very limited).
///
/// @param fname name of the file to be loaded
void testFile(const std::string& fname) {
    ElementPtr json;
    ElementPtr reference_json;
    ConstElementPtr test_json;

    string decommented = decommentJSONfile(fname);

    cout << "Parsing file " << fname << " (" << decommented << ")" << endl;

    ASSERT_NO_THROW(json = Element::fromJSONFile(decommented, true));
    reference_json = moveComments(json);

    // remove the temporary file
    EXPECT_NO_THROW(::remove(decommented.c_str()));

    EXPECT_NO_THROW(
    try {
        D2ParserContext ctx;
        test_json = ctx.parseFile(fname, D2ParserContext::PARSER_DHCPDDNS);
    } catch (const std::exception &x) {
        cout << "EXCEPTION: " << x.what() << endl;
        throw;
    });

    ASSERT_TRUE(reference_json);
    ASSERT_TRUE(test_json);

    compareJSON(reference_json, test_json);
}

// This test loads all available existing files. Each config is loaded
// twice: first with the existing Element::fromJSONFile() and then
// the second time with D2Parser. Both JSON trees are then compared.
TEST(ParserTest, file) {
    vector<string> configs;
    configs.push_back("all-keys.json");
    configs.push_back("all-keys-netconf.json");
    configs.push_back("comments.json");
    configs.push_back("gss-tsig.json");
    configs.push_back("sample1.json");
    configs.push_back("template.json");

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i]);
    }
}

/// @brief Tests error conditions in D2Parser
///
/// @param txt text to be parsed
/// @param parser_type type of the parser to be used in the test
/// @param msg expected content of the exception
void testError(const std::string& txt,
               D2ParserContext::ParserType parser_type,
               const std::string& msg) {
    SCOPED_TRACE("\n=== tested config ===\n" + txt + "=====================");

    try {
        D2ParserContext ctx;
        ConstElementPtr parsed = ctx.parseString(txt, parser_type);
        FAIL() << "Expected D2ParseError but nothing was raised (expected: "
               << msg << ")";
    }
    catch (const D2ParseError& ex) {
        EXPECT_EQ(msg, ex.what());
    }
    catch (...) {
        FAIL() << "Expected D2ParseError but something else was raised";
    }
}

// Verify that error conditions are handled correctly.
TEST(ParserTest, errors) {
    // no input
    testError("", D2ParserContext::PARSER_JSON,
              "<string>:1.1: syntax error, unexpected end of file");
    testError(" ", D2ParserContext::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\n", D2ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("\t", D2ParserContext::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\r", D2ParserContext::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");

    // comments
    testError("# nothing\n",
              D2ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError(" #\n",
              D2ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("// nothing\n",
              D2ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* nothing */\n",
              D2ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n",
              D2ParserContext::PARSER_JSON,
              "<string>:3.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n\n",
              D2ParserContext::PARSER_JSON,
              "<string>:4.1: syntax error, unexpected end of file");
    testError("/* nothing\n",
              D2ParserContext::PARSER_JSON,
              "Comment not closed. (/* in line 1");
    testError("\n\n\n/* nothing\n",
              D2ParserContext::PARSER_JSON,
              "Comment not closed. (/* in line 4");
    testError("{ /* */*/ }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3-8: Invalid character: *");
    testError("{ /* // *// }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3-11: Invalid character: /");
    testError("{ /* // *///  }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting }");

    // includes
    testError("<?\n",
              D2ParserContext::PARSER_JSON,
              "Directive not closed.");
    testError("<?include\n",
              D2ParserContext::PARSER_JSON,
              "Directive not closed.");
    string file = string(CFG_EXAMPLES) + "/" + "sample1.json";
    testError("<?include \"" + file + "\"\n",
              D2ParserContext::PARSER_JSON,
              "Directive not closed.");
    testError("<?include \"/foo/bar\" ?>/n",
              D2ParserContext::PARSER_JSON,
              "Can't open include file /foo/bar");

    // JSON keywords
    testError("{ \"foo\": True }",
              D2ParserContext::PARSER_JSON,
              "<string>:1.10-13: JSON true reserved keyword is lower case only");
    testError("{ \"foo\": False }",
              D2ParserContext::PARSER_JSON,
              "<string>:1.10-14: JSON false reserved keyword is lower case only");
    testError("{ \"foo\": NULL }",
              D2ParserContext::PARSER_JSON,
              "<string>:1.10-13: JSON null reserved keyword is lower case only");
    testError("{ \"foo\": Tru }",
              D2ParserContext::PARSER_JSON,
              "<string>:1.10: Invalid character: T");
    testError("{ \"foo\": nul }",
              D2ParserContext::PARSER_JSON,
              "<string>:1.10: Invalid character: n");

    // numbers
    testError("123",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-3: syntax error, unexpected integer, "
              "expecting {");
    testError("-456",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-4: syntax error, unexpected integer, "
              "expecting {");
    testError("-0001",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-5: syntax error, unexpected integer, "
              "expecting {");
    testError("1234567890123456789012345678901234567890",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-40: Failed to convert "
              "1234567890123456789012345678901234567890"
              " to an integer.");
    testError("-3.14e+0",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-8: syntax error, unexpected floating point, "
              "expecting {");
    testError("1e50000",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-7: Failed to convert 1e50000 "
              "to a floating point.");

    // strings
    testError("\"aabb\"",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-6: syntax error, unexpected constant string, "
              "expecting {");
    testError("{ \"aabb\"err",
              D2ParserContext::PARSER_JSON,
              "<string>:1.9: Invalid character: e");
    testError("{ err\"aabb\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: Invalid character: e");
    testError("\"a\n\tb\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-6 (near 2): Invalid control in \"a\n\tb\"");
    testError("\"a\n\\u12\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-8 (near 2): Invalid control in \"a\n\\u12\"");
    testError("\"a\\n\\tb\"",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-8: syntax error, unexpected constant string, "
              "expecting {");
    testError("\"a\\x01b\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-8 (near 3): Bad escape in \"a\\x01b\"");
    testError("\"a\\u0162\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-9 (near 4): Unsupported unicode escape "
              "in \"a\\u0162\"");
    testError("\"a\\u062z\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-9 (near 3): Bad escape in \"a\\u062z\"");
    testError("\"abc\\\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-6 (near 6): Overflow escape in \"abc\\\"");
    testError("\"a\\u006\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-8 (near 3): Overflow unicode escape "
              "in \"a\\u006\"");
    testError("\"\\u\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-4 (near 2): Overflow unicode escape in \"\\u\"");
    testError("\"\\u\x02\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-5 (near 2): Bad escape in \"\\u\x02\"");
    testError("\"\\u\\\"foo\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-5 (near 2): Bad escape in \"\\u\\\"...");
    testError("\"\x02\\u\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-5 (near 1): Invalid control in \"\x02\\u\"");

    // from data_unittest.c
    testError("\\a",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\\"\\\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");

    // want a map
    testError("[]\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("[]\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("{ 123 }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting }");
    testError("{ 123 }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting DhcpDdns");
    testError("{ \"foo\" }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.9: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"foo\" }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting DhcpDdns");
    testError("{ \"foo\":null }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting DhcpDdns");
    testError("{ \"Logging\":null }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.3-11: syntax error, unexpected constant string, "
              "expecting DhcpDdns");
    testError("{}{}\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected {, "
              "expecting end of file");

    // duplicate in map
    testError("{ \"foo\": 1, \"foo\": true }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1:13: duplicate foo entries in "
              "JSON map (previous at <string>:1:10)");

    // bad commas
    testError("{ , }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ , \"foo\":true }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");

    // bad type
    testError("{ \"DhcpDdns\":{\n"
              "  \"dns-server-timeout\":false }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:2.24-28: syntax error, unexpected boolean, "
              "expecting integer");

    // unknown keyword
    testError("{ \"DhcpDdns\":{\n"
              " \"totally-bogus\":600 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:2.2-16: got unexpected keyword "
              "\"totally-bogus\" in DhcpDdns map.");

    // user context and embedded comments
    testError("{ \"DhcpDdns\":{\n"
              "  \"comment\": true,\n"
              "  \"dns-server-timeout\": 1000 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:2.14-17: syntax error, unexpected boolean, "
              "expecting constant string");

    testError("{ \"DhcpDdns\":{\n"
              "  \"user-context\": \"a comment\",\n"
              "  \"dns-server-timeout\": 1000 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:2.19-29: syntax error, unexpected constant string, "
              "expecting {");

    testError("{ \"DhcpDdns\":{\n"
              "  \"comment\": \"a comment\",\n"
              "  \"comment\": \"another one\",\n"
              "  \"dns-server-timeout\": 1000 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:3)");

    testError("{ \"DhcpDdns\":{\n"
              "  \"user-context\": { \"version\": 1 },\n"
              "  \"user-context\": { \"one\": \"only\" },\n"
              "  \"dns-server-timeout\": 1000 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:3.3-16: duplicate user-context entries "
              "(previous at <string>:2:19)");

    testError("{ \"DhcpDdns\":{\n"
              "  \"user-context\": { \"comment\": \"indirect\" },\n"
              "  \"comment\": \"a comment\",\n"
              "  \"dns-server-timeout\": 1000 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:19)");

    // duplicate DhcpDdns entries
    testError("{ \"DhcpDdns\":{\n"
              "  \"comment\": \"first\" },\n"
              "  \"DhcpDdns\":{\n"
              "  \"comment\": \"second\" }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:3.3-12: syntax error, unexpected DhcpDdns, expecting \",\" or }");

    // duplicate of not string entries
    testError("{ \"DhcpDdns\":{\n"
              "  \"port\": 53001,\n"
              "  \"port\": 53002 }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:3:3: duplicate port entries in "
              "DhcpDdns map (previous at <string>:2:11)");

    // duplicate of string entries
    testError("{ \"DhcpDdns\":{\n"
              "  \"ip-address\": \"127.0.0.1\",\n"
              "  \"ip-address\": \"::1\" }}\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:3:3: duplicate ip-address entries in "
              "DhcpDdns map (previous at <string>:2:17)");
}

// Check unicode escapes
TEST(ParserTest, unicodeEscapes) {
    ConstElementPtr result;
    string json;

    // check we can reread output
    for (char c = -128; c < 127; ++c) {
        string ins(" ");
        ins[1] = c;
        ConstElementPtr e(new StringElement(ins));
        json = e->str();
        ASSERT_NO_THROW(
        try {
            D2ParserContext ctx;
            result = ctx.parseString(json, D2ParserContext::PARSER_JSON);
        } catch (const std::exception &x) {
            cout << "EXCEPTION: " << x.what() << endl;
            throw;
        });
        ASSERT_EQ(Element::string, result->getType());
        EXPECT_EQ(ins, result->stringValue());
    }
}

// This test checks that all representations of a slash is recognized properly.
TEST(ParserTest, unicodeSlash) {
    // check the 4 possible encodings of solidus '/'
    ConstElementPtr result;
    string json = "\"/\\/\\u002f\\u002F\"";
    ASSERT_NO_THROW(
    try {
        D2ParserContext ctx;
        result = ctx.parseString(json, D2ParserContext::PARSER_JSON);
    } catch (const std::exception &x) {
        cout << "EXCEPTION: " << x.what() << endl;
        throw;
    });
    ASSERT_EQ(Element::string, result->getType());
    EXPECT_EQ("////", result->stringValue());
}

/// @brief Load a file into a JSON element.
///
/// @param fname The name of the file to load.
/// @param list The JSON element list to add the parsing result to.
void loadFile(const string& fname, ElementPtr list) {
    D2ParserContext ctx;
    ElementPtr json;
    EXPECT_NO_THROW(json = ctx.parseFile(fname, D2ParserContext::PARSER_DHCPDDNS));
    ASSERT_TRUE(json);
    list->add(json);
}

// This test checks that all map entries are in the sample file.
TEST(ParserTest, mapEntries) {
    // Type of keyword set.
    typedef set<string> KeywordSet;

    // Get keywords from the syntax file (d2_parser.yy).
    ifstream syntax_file(SYNTAX_FILE);
    EXPECT_TRUE(syntax_file.is_open());
    string line;
    KeywordSet syntax_keys = { "user-context" };
    // Code setting the map entry.
    const string pattern = "ctx.stack_.back()->set(\"";
    while (getline(syntax_file, line)) {
        // Skip comments.
        size_t comment = line.find("//");
        if (comment <= pattern.size()) {
            continue;
        }
        if (comment != string::npos) {
            line.resize(comment);
        }
        // Search for the code pattern.
        size_t key_begin = line.find(pattern);
        if (key_begin == string::npos) {
            continue;
        }
        // Extract keywords.
        line = line.substr(key_begin + pattern.size());
        size_t key_end = line.find_first_of('"');
        EXPECT_NE(string::npos, key_end);
        string keyword = line.substr(0, key_end);
        // Ignore result when adding the keyword to the syntax keyword set.
        static_cast<void>(syntax_keys.insert(keyword));
    }
    syntax_file.close();

    // Get keywords from the example files.
    string sample_dir(CFG_EXAMPLES);
    sample_dir += "/";
    ElementPtr sample_json = Element::createList();
    loadFile(sample_dir + "all-keys.json", sample_json);
    loadFile(sample_dir + "all-keys-netconf.json", sample_json);
    KeywordSet sample_keys = {
        "hostname"
    };
    // Recursively extract keywords.
    static void (*extract)(ConstElementPtr, KeywordSet&) =
        [] (ConstElementPtr json, KeywordSet& set) {
            if (json->getType() == Element::list) {
                // Handle lists.
                for (auto elem : json->listValue()) {
                    extract(elem, set);
                }
            } else if (json->getType() == Element::map) {
                // Handle maps.
                for (auto elem : json->mapValue()) {
                    static_cast<void>(set.insert(elem.first));
                    // Skip entries with free content.
                    if ((elem.first != "user-context") &&
                        (elem.first != "parameters")) {
                        extract(elem.second, set);
                    }
                }
            }
        };
    extract(sample_json, sample_keys);

    // Compare.
    EXPECT_EQ(syntax_keys, sample_keys);
}

/// @brief Tests a duplicate entry.
///
/// The entry was duplicated by adding a new <name>DDDD entry.
/// An error is expected, usually it is a duplicate but there are
/// a few syntax errors when the syntax allows only one parameter.
///
/// @param json the JSON configuration with the duplicate entry.
void testDuplicate(ConstElementPtr json) {
    string config = json->str();
    size_t where = config.find("DDDD");
    ASSERT_NE(string::npos, where);
    string before = config.substr(0, where);
    string after = config.substr(where + 4, string::npos);
    D2ParserContext ctx;
    EXPECT_THROW(ctx.parseString(before + after,
                                 D2ParserContext::PARSER_DHCPDDNS),
                 D2ParseError) << "config: " << config;
}

// This test checks that duplicate entries make parsing to fail.
TEST(ParserTest, duplicateMapEntries) {
    // Get the config to work with from the sample file.
    string sample_fname(CFG_EXAMPLES);
    sample_fname += "/all-keys.json";
    D2ParserContext ctx;
    ElementPtr sample_json;
    EXPECT_NO_THROW(sample_json =
        ctx.parseFile(sample_fname, D2ParserContext::PARSER_DHCPDDNS));
    ASSERT_TRUE(sample_json);

    // Recursively check duplicates.
    static void (*test)(ElementPtr, ElementPtr, size_t&) =
        [] (ElementPtr config, ElementPtr json, size_t& cnt) {
            if (json->getType() == Element::list) {
                // Handle lists.
                for (auto elem : json->listValue()) {
                    test(config, elem, cnt);
                }
            } else if (json->getType() == Element::map) {
                // Handle maps.
                for (auto elem : json->mapValue()) {
                    // Skip entries with free content.
                    if ((elem.first == "user-context") ||
                        (elem.first == "parameters")) {
                        continue;
                    }

                    // Perform tests.
                    string dup = elem.first + "DDDD";
                    json->set(dup, elem.second);
                    testDuplicate(config);
                    json->remove(dup);
                    ++cnt;

                    // Recursive call.
                    ElementPtr mutable_json =
                        boost::const_pointer_cast<Element>(elem.second);
                    ASSERT_TRUE(mutable_json);
                    test(config, mutable_json, cnt);
                }
            }
        };
    size_t cnt = 0;
    test(sample_json, sample_json, cnt);
    cout << "checked " << cnt << " duplicated map entries\n";
}

/// @brief Test fixture for trailing commas.
class TrailingCommasTest : public isc::dhcp::test::LogContentTest {
public:
    /// @brief Add a log entry.
    ///
    /// @param loc Location of the trailing comma.
    void addLog(const string& loc) {
        string log = "DHCP_DDNS_CONFIG_SYNTAX_WARNING DHCP-DDNS server ";
        log += "configuration syntax warning: " + loc;
        log += ": Extraneous comma. ";
        log += "A piece of configuration may have been omitted.";
        addString(log);
    }
};

// Test that trailing commas are allowed.
TEST_F(TrailingCommasTest, tests) {
    string txt(R"({
  "DhcpDdns": {
    "forward-ddns": {},
    "ip-address": "127.0.0.1",
    "loggers": [
      {
        "name": "kea-dhcp-ddns",
        "output_options": [
          {
            "output": "stdout"
          },
        ],
        "severity": "DEBUG",
      },
    ],
    "port": 53001,
    "reverse-ddns": {},
    "tsig-keys": [
      {
        "algorithm": "HMAC-MD5",
        "name": "d2.md5.key",
        "secret": "sensitivejdPJI5QxlpnfQ==",
      },
    ]
  },
})");
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS, false);

    addLog("<string>:11.12");
    addLog("<string>:13.28");
    addLog("<string>:14.8");
    addLog("<string>:22.45");
    addLog("<string>:23.8");
    addLog("<string>:25.4");
    EXPECT_TRUE(checkFile());

    // Test with many consecutive commas.
    boost::replace_all(txt, ",", ",,,,");
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS, false);
}

}  // namespace test
}  // namespace d2
}  // namespace isc
