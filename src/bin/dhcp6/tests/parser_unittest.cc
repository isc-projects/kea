// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp6/parser_context.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <testutils/io_utils.h>
#include <testutils/log_utils.h>
#include <testutils/test_to_element.h>
#include <testutils/user_context_utils.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <fstream>
#include <set>

#include <boost/algorithm/string.hpp>

using namespace isc::data;
using namespace std;
using namespace isc::test;

namespace isc {
namespace dhcp {
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
void testParser(const std::string& txt, Parser6Context::ParserType parser_type,
    bool compare = true) {
    SCOPED_TRACE("\n=== tested config ===\n" + txt + "=====================");

    ConstElementPtr test_json;
    ASSERT_NO_THROW({
            try {
                Parser6Context ctx;
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

TEST(ParserTest, mapInMap) {
    string txt = "{ \"xyzzy\": { \"foo\": 123, \"baz\": 456 } }";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, listInList) {
    string txt = "[ [ \"Britain\", \"Wales\", \"Scotland\" ], "
                 "[ \"Pomorze\", \"Wielkopolska\", \"Tatry\"] ]";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, nestedMaps) {
    string txt = "{ \"europe\": { \"UK\": { \"London\": { \"street\": \"221B Baker\" }}}}";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, nestedLists) {
    string txt = "[ \"half\", [ \"quarter\", [ \"eighth\", [ \"sixteenth\" ]]]]";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, listsInMaps) {
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelgeuse\" ], "
                    "\"cygnus\": [ \"deneb\", \"albireo\"] } }";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, mapsInLists) {
    string txt = "[ { \"body\": \"earth\", \"gravity\": 1.0 },"
                 " { \"body\": \"mars\", \"gravity\": 0.376 } ]";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, types) {
    string txt = "{ \"string\": \"foo\","
                   "\"integer\": 42,"
                   "\"boolean\": true,"
                   "\"map\": { \"foo\": \"bar\" },"
                   "\"list\": [ 1, 2, 3 ],"
                   "\"null\": null }";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, keywordJSON) {
    string txt = "{ \"name\": \"user\","
                   "\"type\": \"password\","
                   "\"user\": \"name\","
                   "\"password\": \"type\" }";
    testParser(txt, Parser6Context::PARSER_JSON);
}

TEST(ParserTest, keywordDhcp6) {
     string txt = "{ \"Dhcp6\": { \"interfaces-config\": {"
                  " \"interfaces\": [ \"type\", \"htype\" ] },\n"
                  "\"preferred-lifetime\": 3000,\n"
                  "\"rebind-timer\": 2000, \n"
                  "\"renew-timer\": 1000, \n"
                  "\"subnet6\": [ { "
                  "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                  "    \"subnet\": \"2001:db8:1::/48\", "
                  "    \"interface\": \"test\" } ],\n"
                   "\"valid-lifetime\": 4000 } }";
     testParser(txt, Parser6Context::PARSER_DHCP6);
}

// Tests if bash (#) comments are supported. That's the only comment type that
// was supported by the old parser.
TEST(ParserTest, bashComments) {
    string txt= "{ \"Dhcp6\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"preferred-lifetime\": 3000,\n"
                "# this is a comment\n"
                "\"rebind-timer\": 2000, \n"
                "# lots of comments here\n"
                "# and here\n"
                "\"renew-timer\": 1000, \n"
                "\"subnet6\": [ { "
                "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                "    \"subnet\": \"2001:db8:1::/48\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser6Context::PARSER_DHCP6);
}

// Tests if C++ (//) comments can start anywhere, not just in the first line.
TEST(ParserTest, cppComments) {
    string txt= "{ \"Dhcp6\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"preferred-lifetime\": 3000, // this is a comment \n"
                "\"rebind-timer\": 2000, // everything after // is ignored\n"
                "\"renew-timer\": 1000, // this will be ignored, too\n"
                "\"subnet6\": [ { "
                "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                "    \"subnet\": \"2001:db8:1::/48\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser6Context::PARSER_DHCP6, false);
}

// Tests if bash (#) comments can start anywhere, not just in the first line.
TEST(ParserTest, bashCommentsInline) {
    string txt= "{ \"Dhcp6\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"preferred-lifetime\": 3000, # this is a comment \n"
                "\"rebind-timer\": 2000, # everything after # is ignored\n"
                "\"renew-timer\": 1000, # this will be ignored, too\n"
                "\"subnet6\": [ { "
                "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                "    \"subnet\": \"2001:db8:1::/48\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser6Context::PARSER_DHCP6, false);
}

// Tests if multi-line C style comments are handled correctly.
TEST(ParserTest, multilineComments) {
    string txt= "{ \"Dhcp6\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"preferred-lifetime\": 3000, /* this is a C style comment\n"
                "that\n can \n span \n multiple \n lines */ \n"
                "\"rebind-timer\": 2000,\n"
                "\"renew-timer\": 1000, \n"
                "\"subnet6\": [ { "
                "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                "    \"subnet\": \"2001:db8:1::/48\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser6Context::PARSER_DHCP6, false);
}

// Tests if embedded comments are handled correctly.
TEST(ParserTest, embbededComments) {
    string txt= "{ \"Dhcp6\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"comment\": \"a comment\",\n"
                "\"preferred-lifetime\": 3000,\n"
                "\"rebind-timer\": 2000,\n"
                "\"renew-timer\": 1000, \n"
                "\"subnet6\": [ { "
                "    \"user-context\": { \"comment\": \"indirect\" },"
                "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                "    \"subnet\": \"2001:db8:1::/48\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"user-context\": { \"compatible\": true },"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser6Context::PARSER_DHCP6, false);
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

    cout << "Parsing file " << fname << "(" << decommented << ")" << endl;

    EXPECT_NO_THROW_LOG(json = Element::fromJSONFile(decommented, true));
    reference_json = moveComments(json);

    // remove the temporary file
    EXPECT_NO_THROW(::remove(decommented.c_str()));

    EXPECT_NO_THROW(
    try {
        Parser6Context ctx;
        test_json = ctx.parseFile(fname, Parser6Context::PARSER_DHCP6);
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
// the second time with Parser6. Both JSON trees are then compared.
TEST(ParserTest, file) {
    vector<string> configs;
    configs.push_back("advanced.json");
    configs.push_back("all-keys.json");
    configs.push_back("all-options.json");
    configs.push_back("backends.json");
    configs.push_back("classify.json");
    configs.push_back("classify2.json");
    configs.push_back("comments.json");
    configs.push_back("dhcpv4-over-dhcpv6.json");
    configs.push_back("duid.json");
    configs.push_back("global-reservations.json");
    configs.push_back("hooks.json");
    configs.push_back("iPXE.json");
    configs.push_back("leases-expiration.json");
    configs.push_back("multiple-options.json");
    configs.push_back("mysql-reservations.json");
    configs.push_back("pgsql-reservations.json");
    configs.push_back("reservations.json");
    configs.push_back("several-subnets.json");
    configs.push_back("shared-network.json");
    configs.push_back("simple.json");
    configs.push_back("softwire46.json");
    configs.push_back("stateless.json");
    configs.push_back("with-ddns.json");

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i]);
    }
}

// This test loads the all-keys.json file and checks global parameters.
TEST(ParserTest, globalParameters) {
    ConstElementPtr json;
    Parser6Context ctx;
    string fname = string(CFG_EXAMPLES) + "/" + "all-keys.json";
    EXPECT_NO_THROW(json = ctx.parseFile(fname, Parser6Context::PARSER_DHCP6));
    EXPECT_NO_THROW(json = json->get("Dhcp6"));
    SimpleParser6 parser;
    EXPECT_NO_THROW(parser.checkKeywords(parser.GLOBAL6_PARAMETERS, json));
}

/// @brief Tests error conditions in Dhcp6Parser
///
/// @param txt text to be parsed
/// @param parser_type type of the parser to be used in the test
/// @param msg expected content of the exception
void testError(const std::string& txt,
               Parser6Context::ParserType parser_type,
               const std::string& msg) {
    SCOPED_TRACE("\n=== tested config ===\n" + txt + "=====================");

    try {
        Parser6Context ctx;
        ConstElementPtr parsed = ctx.parseString(txt, parser_type);
        FAIL() << "Expected Dhcp6ParseError but nothing was raised (expected: "
               << msg << ")";
    }
    catch (const Dhcp6ParseError& ex) {
        EXPECT_EQ(msg, ex.what());
    }
    catch (...) {
        FAIL() << "Expected Dhcp6ParseError but something else was raised";
    }
}

// Verify that error conditions are handled correctly.
TEST(ParserTest, errors) {
    // no input
    testError("", Parser6Context::PARSER_JSON,
              "<string>:1.1: syntax error, unexpected end of file");
    testError(" ", Parser6Context::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\n", Parser6Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("\t", Parser6Context::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\r", Parser6Context::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");

    // comments
    testError("# nothing\n",
              Parser6Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError(" #\n",
              Parser6Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("// nothing\n",
              Parser6Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* nothing */\n",
              Parser6Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n",
              Parser6Context::PARSER_JSON,
              "<string>:3.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n\n",
              Parser6Context::PARSER_JSON,
              "<string>:4.1: syntax error, unexpected end of file");
    testError("/* nothing\n",
              Parser6Context::PARSER_JSON,
              "Comment not closed. (/* in line 1");
    testError("\n\n\n/* nothing\n",
              Parser6Context::PARSER_JSON,
              "Comment not closed. (/* in line 4");
    testError("{ /* */*/ }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.3-8: Invalid character: *");
    testError("{ /* // *// }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.3-11: Invalid character: /");
    testError("{ /* // *///  }\n",
              Parser6Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting }");

    // includes
    testError("<?\n",
              Parser6Context::PARSER_JSON,
              "Directive not closed.");
    testError("<?include\n",
              Parser6Context::PARSER_JSON,
              "Directive not closed.");
    string file = string(CFG_EXAMPLES) + "/" + "stateless.json";
    testError("<?include \"" + file + "\"\n",
              Parser6Context::PARSER_JSON,
              "Directive not closed.");
    testError("<?include \"/foo/bar\" ?>/n",
              Parser6Context::PARSER_JSON,
              "Can't open include file /foo/bar");

    // JSON keywords
    testError("{ \"foo\": True }",
              Parser6Context::PARSER_JSON,
              "<string>:1.10-13: JSON true reserved keyword is lower case only");
    testError("{ \"foo\": False }",
              Parser6Context::PARSER_JSON,
              "<string>:1.10-14: JSON false reserved keyword is lower case only");
    testError("{ \"foo\": NULL }",
              Parser6Context::PARSER_JSON,
              "<string>:1.10-13: JSON null reserved keyword is lower case only");
    testError("{ \"foo\": Tru }",
              Parser6Context::PARSER_JSON,
              "<string>:1.10: Invalid character: T");
    testError("{ \"foo\": nul }",
              Parser6Context::PARSER_JSON,
              "<string>:1.10: Invalid character: n");

    // numbers
    testError("123",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1-3: syntax error, unexpected integer, "
              "expecting {");
    testError("-456",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1-4: syntax error, unexpected integer, "
              "expecting {");
    testError("-0001",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1-5: syntax error, unexpected integer, "
              "expecting {");
    testError("1234567890123456789012345678901234567890",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-40: Failed to convert "
              "1234567890123456789012345678901234567890"
              " to an integer.");
    testError("-3.14e+0",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1-8: syntax error, unexpected floating point, "
              "expecting {");
    testError("1e50000",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-7: Failed to convert 1e50000 "
              "to a floating point.");

    // strings
    testError("\"aabb\"",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1-6: syntax error, unexpected constant string, "
              "expecting {");
    testError("{ \"aabb\"err",
              Parser6Context::PARSER_JSON,
              "<string>:1.9: Invalid character: e");
    testError("{ err\"aabb\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.3: Invalid character: e");
    testError("\"a\n\tb\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-6 (near 2): Invalid control in \"a\n\tb\"");
    testError("\"a\n\\u12\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-8 (near 2): Invalid control in \"a\n\\u12\"");
    testError("\"a\\n\\tb\"",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1-8: syntax error, unexpected constant string, "
              "expecting {");
    testError("\"a\\x01b\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-8 (near 3): Bad escape in \"a\\x01b\"");
    testError("\"a\\u0162\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-9 (near 4): Unsupported unicode escape "
              "in \"a\\u0162\"");
    testError("\"a\\u062z\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-9 (near 3): Bad escape in \"a\\u062z\"");
    testError("\"abc\\\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-6 (near 6): Overflow escape in \"abc\\\"");
    testError("\"a\\u006\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-8 (near 3): Overflow unicode escape "
              "in \"a\\u006\"");
    testError("\"\\u\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-4 (near 2): Overflow unicode escape in \"\\u\"");
    testError("\"\\u\x02\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-5 (near 2): Bad escape in \"\\u\x02\"");
    testError("\"\\u\\\"foo\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-5 (near 2): Bad escape in \"\\u\\\"...");
    testError("\"\x02\\u\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1-5 (near 1): Invalid control in \"\x02\\u\"");

    // from data_unittest.c
    testError("\\a",
              Parser6Context::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\",
              Parser6Context::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\\"\\\"",
              Parser6Context::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");

    // want a map
    testError("[]\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("[]\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("{ 123 }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting }");
    testError("{ 123 }\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting Dhcp6");
    testError("{ \"foo\" }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.9: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"foo\" }\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting Dhcp6");
    testError("{ \"foo\":null }\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting Dhcp6");
    testError("{ \"Logging\":null }\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.3-11: syntax error, unexpected constant string, "
              "expecting Dhcp6");
    testError("{ \"Dhcp6\" }\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:1.11: syntax error, unexpected }, "
              "expecting :");
    testError("{}{}\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected {, "
              "expecting end of file");

    // duplicate in map
    testError("{ \"foo\": 1, \"foo\": true }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1:13: duplicate foo entries in "
              "JSON map (previous at <string>:1:10)");

    // bad commas
    testError("{ , }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ , \"foo\":true }\n",
              Parser6Context::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");

    // bad type
    testError("{ \"Dhcp6\":{\n"
              "  \"preferred-lifetime\":false }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:2.24-28: syntax error, unexpected boolean, "
              "expecting integer");

    // unknown keyword
    testError("{ \"Dhcp6\":{\n"
              " \"preferred_lifetime\":600 }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:2.2-21: got unexpected keyword "
              "\"preferred_lifetime\" in Dhcp6 map.");

    // missing parameter
    testError("{ \"name\": \"foo\",\n"
              "  \"code\": 123 }\n",
              Parser6Context::PARSER_OPTION_DEF,
              "missing parameter 'type' (<string>:1:1) "
              "[option-def map between <string>:1:1 and <string>:2:15]");

    // user context and embedded comments
    testError("{ \"Dhcp6\":{\n"
              "  \"comment\": true,\n"
              "  \"preferred-lifetime\": 600 }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:2.14-17: syntax error, unexpected boolean, "
              "expecting constant string");

    testError("{ \"Dhcp6\":{\n"
              "  \"user-context\": \"a comment\",\n"
              "  \"preferred-lifetime\": 600 }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:2.19-29: syntax error, unexpected constant string, "
              "expecting {");

    testError("{ \"Dhcp6\":{\n"
              "  \"comment\": \"a comment\",\n"
              "  \"comment\": \"another one\",\n"
              "  \"preferred-lifetime\": 600 }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:3)");

    testError("{ \"Dhcp6\":{\n"
              "  \"user-context\": { \"version\": 1 },\n"
              "  \"user-context\": { \"one\": \"only\" },\n"
              "  \"preferred-lifetime\": 600 }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:3.3-16: duplicate user-context entries "
              "(previous at <string>:2:19)");

    testError("{ \"Dhcp6\":{\n"
              "  \"user-context\": { \"comment\": \"indirect\" },\n"
              "  \"comment\": \"a comment\",\n"
              "  \"preferred-lifetime\": 600 }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:19)");

    // duplicate Dhcp6 entries
    testError("{ \"Dhcp6\":{\n"
              "  \"comment\": \"first\" },\n"
              "  \"Dhcp6\":{\n"
              "  \"comment\": \"second\" }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:3.3-9: syntax error, unexpected Dhcp6, expecting \",\" or }");

    // duplicate of not string entries
    testError("{ \"Dhcp6\":{\n"
              " \"subnet6\": [],\n"
              " \"subnet6\": [] }}\n",
              Parser6Context::PARSER_DHCP6,
              "<string>:3:2: duplicate subnet6 entries in "
              "Dhcp6 map (previous at <string>:2:2)");

    // duplicate of string entries
    testError("{ \"data\": \"foo\",\n"
              " \"data\": \"bar\" }\n",
              Parser6Context::PARSER_OPTION_DATA,
              "<string>:2:2: duplicate data entries in "
              "option-data map (previous at <string>:1:11)");
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
            Parser6Context ctx;
            result = ctx.parseString(json, Parser6Context::PARSER_JSON);
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
        Parser6Context ctx;
        result = ctx.parseString(json, Parser6Context::PARSER_JSON);
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
    Parser6Context ctx;
    ElementPtr json;
    EXPECT_NO_THROW(json = ctx.parseFile(fname, Parser6Context::PARSER_DHCP6));
    ASSERT_TRUE(json);
    list->add(json);
}

// This test checks that all map entries are in the example files.
TEST(ParserTest, mapEntries) {
    // Type of keyword set.
    typedef set<string> KeywordSet;

    // Get keywords from the syntax file (dhcp6_parser.yy).
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
    loadFile(sample_dir + "advanced.json", sample_json);
    loadFile(sample_dir + "all-keys.json", sample_json);
    loadFile(sample_dir + "duid.json", sample_json);
    loadFile(sample_dir + "reservations.json", sample_json);
    loadFile(sample_dir + "all-keys-netconf.json", sample_json);
    KeywordSet sample_keys = {
        "hosts-database",
        "reservation-mode"
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
    auto print_keys = [](const KeywordSet& keys) {
        string s = "{";
        bool first = true;
        for (auto key : keys) {
            if (first) {
                first = false;
                s += " ";
            } else {
                s += ", ";
            }
            s += "\"" + key + "\"";
        }
        return (s + " }");
    };
    EXPECT_EQ(syntax_keys, sample_keys)
        << "syntax has: " << print_keys(syntax_keys) << endl
        << "sample has: " << print_keys(sample_keys) << endl;
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
    Parser6Context ctx;
    EXPECT_THROW(ctx.parseString(before + after,
                                 Parser6Context::PARSER_DHCP6),
                 Dhcp6ParseError) << "config: " << config;
}

// This test checks that duplicate entries make parsing to fail.
TEST(ParserTest, duplicateMapEntries) {
    // Get the config to work with from the all keys file.
    string sample_fname(CFG_EXAMPLES);
    sample_fname += "/all-keys.json";
    Parser6Context ctx;
    ElementPtr sample_json;
    EXPECT_NO_THROW(sample_json =
        ctx.parseFile(sample_fname, Parser6Context::PARSER_DHCP6));
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
        string log = "DHCP6_CONFIG_SYNTAX_WARNING configuration syntax ";
        log += "warning: " + loc;
        log += ": Extraneous comma. ";
        log += "A piece of configuration may have been omitted.";
        addString(log);
    }
};

// Test that trailing commas are allowed.
TEST_F(TrailingCommasTest, tests) {
    string txt(R"({
  "Dhcp6": {
    "control-socket": {
      "socket-name": "/tmp/kea-dhcp6-ctrl.sock",
      "socket-type": "unix",
    },
    "hooks-libraries": [
      {
        "library": "/usr/local/lib/kea/hooks/libdhcp_dummy.so",
      },
    ],
    "interfaces-config": {
      "interfaces": [
        "eth0",
      ],
    },
    "lease-database": {
      "name": "/tmp/kea-dhcp6.csv",
      "persist": true,
      "type": "memfile",
    },
    "loggers": [
      {
        "debuglevel": 99,
        "name": "kea-dhcp6",
        "output_options": [
          {
            "output": "stdout",
          },
        ],
        "severity": "DEBUG",
      },
    ],
    "multi-threading": {
      "enable-multi-threading": false,
      "packet-queue-size": 0,
      "thread-pool-size": 0
    },
    "subnet6": [
      {
        "pools": [
          {
            "pool": "2001:db8:1::/64",
          },
        ],
        "subnet": "2001:db8:1::/64",
      },
    ],
  },
})");
    testParser(txt, Parser6Context::PARSER_DHCP6, false);

    addLog("<string>:5.28");
    addLog("<string>:9.63");
    addLog("<string>:10.8");
    addLog("<string>:14.15");
    addLog("<string>:15.8");
    addLog("<string>:20.24");
    addLog("<string>:28.31");
    addLog("<string>:29.12");
    addLog("<string>:31.28");
    addLog("<string>:32.8");
    addLog("<string>:43.38");
    addLog("<string>:44.12");
    addLog("<string>:46.36");
    addLog("<string>:47.8");
    addLog("<string>:48.6");
    addLog("<string>:49.4");
    EXPECT_TRUE(checkFile());

    // Test with many consecutive commas.
    boost::replace_all(txt, ",", ",,,,");
    testParser(txt, Parser6Context::PARSER_DHCP6, false);
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
