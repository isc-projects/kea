// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>
#include <dhcp4/parser_context.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>

using namespace isc::data;
using namespace isc::test;
using namespace std;

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
    EXPECT_EQ(a->str(), b->str());
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
void testParser(const std::string& txt, Parser4Context::ParserType parser_type,
                bool compare = true) {
    ConstElementPtr test_json;

    ASSERT_NO_THROW({
            try {
                Parser4Context ctx;
                test_json = ctx.parseString(txt, parser_type);
            } catch (const std::exception &e) {
                cout << "EXCEPTION: " << e.what() << endl;
                throw;
            }

    });

    if (!compare) {
        return;
    };

    // Now compare if both representations are the same.
    ElementPtr reference_json;
    ASSERT_NO_THROW(reference_json = Element::fromJSON(txt, true));
    compareJSON(reference_json, test_json);
}

TEST(ParserTest, mapInMap) {
    string txt = "{ \"xyzzy\": { \"foo\": 123, \"baz\": 456 } }";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, listInList) {
    string txt = "[ [ \"Britain\", \"Wales\", \"Scotland\" ], "
                 "[ \"Pomorze\", \"Wielkopolska\", \"Tatry\"] ]";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, nestedMaps) {
    string txt = "{ \"europe\": { \"UK\": { \"London\": { \"street\": \"221B Baker\" }}}}";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, nestedLists) {
    string txt = "[ \"half\", [ \"quarter\", [ \"eighth\", [ \"sixteenth\" ]]]]";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, listsInMaps) {
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelgeuse\" ], "
                    "\"cygnus\": [ \"deneb\", \"albireo\"] } }";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, mapsInLists) {
    string txt = "[ { \"body\": \"earth\", \"gravity\": 1.0 },"
                 " { \"body\": \"mars\", \"gravity\": 0.376 } ]";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, types) {
    string txt = "{ \"string\": \"foo\","
                   "\"integer\": 42,"
                   "\"boolean\": true,"
                   "\"map\": { \"foo\": \"bar\" },"
                   "\"list\": [ 1, 2, 3 ],"
                   "\"null\": null }";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, keywordJSON) {
    string txt = "{ \"name\": \"user\","
                   "\"type\": \"password\","
                   "\"user\": \"name\","
                   "\"password\": \"type\" }";
    testParser(txt, Parser4Context::PARSER_JSON);
}

TEST(ParserTest, keywordDhcp4) {
     string txt = "{ \"Dhcp4\": { \"interfaces-config\": {"
                  " \"interfaces\": [ \"type\", \"htype\" ] },\n"
                  "\"rebind-timer\": 2000, \n"
                  "\"renew-timer\": 1000, \n"
                  "\"subnet4\": [ { "
                  "  \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
                  "  \"subnet\": \"192.0.2.0/24\", "
                  "  \"interface\": \"test\" } ],\n"
                   "\"valid-lifetime\": 4000 } }";
     testParser(txt, Parser4Context::PARSER_DHCP4);
}

// Tests if bash (#) comments are supported. That's the only comment type that
// was supported by the old parser.
TEST(ParserTest, bashComments) {
    string txt= "{ \"Dhcp4\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "# this is a comment\n"
                "\"rebind-timer\": 2000, \n"
                "# lots of comments here\n"
                "# and here\n"
                "\"renew-timer\": 1000, \n"
                "\"subnet4\": [ { "
                "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
                "    \"subnet\": \"192.0.2.0/24\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser4Context::PARSER_DHCP4, false);
}

// Tests if C++ (//) comments can start anywhere, not just in the first line.
TEST(ParserTest, cppComments) {
    string txt= "{ \"Dhcp4\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"rebind-timer\": 2000, // everything after // is ignored\n"
                "\"renew-timer\": 1000, // this will be ignored, too\n"
                "\"subnet4\": [ { "
                "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
                "    \"subnet\": \"192.0.2.0/24\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser4Context::PARSER_DHCP4, false);
}

// Tests if bash (#) comments can start anywhere, not just in the first line.
TEST(ParserTest, bashCommentsInline) {
    string txt= "{ \"Dhcp4\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"rebind-timer\": 2000, # everything after # is ignored\n"
                "\"renew-timer\": 1000, # this will be ignored, too\n"
                "\"subnet4\": [ { "
                "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
                "    \"subnet\": \"192.0.2.0/24\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser4Context::PARSER_DHCP4, false);
}

// Tests if multi-line C style comments are handled correctly.
TEST(ParserTest, multilineComments) {
    string txt= "{ \"Dhcp4\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "   /* this is a C style comment\n"
                "that\n can \n span \n multiple \n lines */ \n"
                "\"rebind-timer\": 2000,\n"
                "\"renew-timer\": 1000, \n"
                "\"subnet4\": [ { "
                "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
                "    \"subnet\": \"192.0.2.0/24\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser4Context::PARSER_DHCP4, false);
}

// Tests if embedded comments are handled correctly.
TEST(ParserTest, embbededComments) {
    string txt= "{ \"Dhcp4\": { \"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "},\n"
                "\"comment\": \"a comment\",\n"
                "\"rebind-timer\": 2000,\n"
                "\"renew-timer\": 1000, \n"
                "\"subnet4\": [ { "
                "    \"user-context\": { \"comment\": \"indirect\" },"
                "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
                "    \"subnet\": \"192.0.2.0/24\", "
                "    \"interface\": \"eth0\""
                " } ],"
                "\"user-context\": { \"compatible\": true },"
                "\"valid-lifetime\": 4000 } }";
    testParser(txt, Parser4Context::PARSER_DHCP4, false);
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

    EXPECT_NO_THROW(json = Element::fromJSONFile(decommented, true));
    reference_json = moveComments(json);

    // remove the temporary file
    EXPECT_NO_THROW(::remove(decommented.c_str()));

    EXPECT_NO_THROW(
    try {
        Parser4Context ctx;
        test_json = ctx.parseFile(fname, Parser4Context::PARSER_DHCP4);
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
// the second time with Parser4. Both JSON trees are then compared.
TEST(ParserTest, file) {
    vector<string> configs = { "advanced.json" ,
                               "all-keys-current.json",
                               "backends.json",
                               "cassandra.json",
                               "classify.json",
                               "classify2.json",
                               "comments.json",
                               "dhcpv4-over-dhcpv6.json",
                               "global-reservations.json",
                               "hooks.json",
                               "leases-expiration.json",
                               "multiple-options.json",
                               "mysql-reservations.json",
                               "pgsql-reservations.json",
                               "reservations.json",
                               "several-subnets.json",
                               "shared-network.json",
                               "single-subnet.json",
                               "with-ddns.json" };

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i]);
    }
}

// This test loads the all-keys.json file and check global parameters.
TEST(ParserTest, globalParameters) {
    ConstElementPtr json;
    Parser4Context ctx;
    string fname = string(CFG_EXAMPLES) + "/" + "all-keys-current.json";
    EXPECT_NO_THROW(json = ctx.parseFile(fname, Parser4Context::PARSER_DHCP4));
    EXPECT_NO_THROW(json = json->get("Dhcp4"));
    SimpleParser4 parser;
    EXPECT_NO_THROW(parser.checkKeywords(parser.GLOBAL4_PARAMETERS, json));
}

// Basic test that checks if it's possible to specify outbound-interface.
TEST(ParserTest, outboundIface) {
    std::string fname = string(CFG_EXAMPLES) + "/" + "advanced.json";
    Parser4Context ctx;
    ConstElementPtr test_json = ctx.parseFile(fname, Parser4Context::PARSER_DHCP4);

    ConstElementPtr tmp;
    tmp = test_json->get("Dhcp4");
    ASSERT_TRUE(tmp);

    tmp = tmp->get("interfaces-config");
    ASSERT_TRUE(tmp);

    tmp = tmp->get("outbound-interface");
    ASSERT_TRUE(tmp);
    EXPECT_EQ(Element::string, tmp->getType());
    EXPECT_EQ("use-routing", tmp->stringValue());
}

/// @brief Tests error conditions in Dhcp4Parser
///
/// @param txt text to be parsed
/// @param parser_type type of the parser to be used in the test
/// @param msg expected content of the exception
void testError(const std::string& txt,
               Parser4Context::ParserType parser_type,
               const std::string& msg)
{
    try {
        Parser4Context ctx;
        ConstElementPtr parsed = ctx.parseString(txt, parser_type);
        FAIL() << "Expected Dhcp4ParseError but nothing was raised (expected: "
               << msg << ")";
    }
    catch (const Dhcp4ParseError& ex) {
        EXPECT_EQ(msg, ex.what());
    }
    catch (...) {
        FAIL() << "Expected Dhcp4ParseError but something else was raised";
    }
}

// Verify that error conditions are handled correctly.
TEST(ParserTest, errors) {
    // no input
    testError("", Parser4Context::PARSER_JSON,
              "<string>:1.1: syntax error, unexpected end of file");
    testError(" ", Parser4Context::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\n", Parser4Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("\t", Parser4Context::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\r", Parser4Context::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");

    // comments
    testError("# nothing\n",
              Parser4Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError(" #\n",
              Parser4Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("// nothing\n",
              Parser4Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* nothing */\n",
              Parser4Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n",
              Parser4Context::PARSER_JSON,
              "<string>:3.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n\n",
              Parser4Context::PARSER_JSON,
              "<string>:4.1: syntax error, unexpected end of file");
    testError("/* nothing\n",
              Parser4Context::PARSER_JSON,
              "Comment not closed. (/* in line 1");
    testError("\n\n\n/* nothing\n",
              Parser4Context::PARSER_JSON,
              "Comment not closed. (/* in line 4");
    testError("{ /* */*/ }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.3-8: Invalid character: *");
    testError("{ /* // *// }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.3-11: Invalid character: /");
    testError("{ /* // *///  }\n",
              Parser4Context::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting }");

    // includes
    testError("<?\n",
              Parser4Context::PARSER_JSON,
              "Directive not closed.");
    testError("<?include\n",
              Parser4Context::PARSER_JSON,
              "Directive not closed.");
    string file = string(CFG_EXAMPLES) + "/" + "single-subnet.json";
    testError("<?include \"" + file + "\"\n",
              Parser4Context::PARSER_JSON,
              "Directive not closed.");
    testError("<?include \"/foo/bar\" ?>/n",
              Parser4Context::PARSER_JSON,
              "Can't open include file /foo/bar");

    // JSON keywords
    testError("{ \"foo\": True }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10-13: JSON true reserved keyword is lower case only");
    testError("{ \"foo\": False }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10-14: JSON false reserved keyword is lower case only");
    testError("{ \"foo\": NULL }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10-13: JSON null reserved keyword is lower case only");
    testError("{ \"foo\": Tru }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10: Invalid character: T");
    testError("{ \"foo\": nul }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10: Invalid character: n");

    // numbers
    testError("123",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1-3: syntax error, unexpected integer, "
              "expecting {");
    testError("-456",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1-4: syntax error, unexpected integer, "
              "expecting {");
    testError("-0001",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1-5: syntax error, unexpected integer, "
              "expecting {");
    testError("1234567890123456789012345678901234567890",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-40: Failed to convert "
              "1234567890123456789012345678901234567890"
              " to an integer.");
    testError("-3.14e+0",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1-8: syntax error, unexpected floating point, "
              "expecting {");
    testError("1e50000",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-7: Failed to convert 1e50000 "
              "to a floating point.");

    // strings
    testError("\"aabb\"",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1-6: syntax error, unexpected constant string, "
              "expecting {");
    testError("{ \"aabb\"err",
              Parser4Context::PARSER_JSON,
              "<string>:1.9: Invalid character: e");
    testError("{ err\"aabb\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.3: Invalid character: e");
    testError("\"a\n\tb\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-6: Invalid control in \"a\n\tb\"");
    testError("\"a\\n\\tb\"",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1-8: syntax error, unexpected constant string, "
              "expecting {");
    testError("\"a\\x01b\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-8: Bad escape in \"a\\x01b\"");
    testError("\"a\\u0162\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-9: Unsupported unicode escape in \"a\\u0162\"");
    testError("\"a\\u062z\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-9: Bad escape in \"a\\u062z\"");
    testError("\"abc\\\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-6: Overflow escape in \"abc\\\"");

    // from data_unittest.c
    testError("\\a",
              Parser4Context::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\",
              Parser4Context::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\\"\\\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");

    // want a map
    testError("[]\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("[]\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("{ 123 }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting }");
    testError("{ 123 }\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.3-5: syntax error, unexpected integer");
    testError("{ \"foo\" }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.9: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"foo\" }\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.9: syntax error, unexpected }, expecting :");
    testError("{ \"foo\":null }\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.3-7: got unexpected keyword "
              "\"foo\" in toplevel map.");
    testError("{ \"Dhcp4\" }\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:1.11: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"Dhcp6\":[]\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting \",\" or }");
    testError("{}{}\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected {, "
              "expecting end of file");

    // bad commas
    testError("{ , }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ , \"foo\":true }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ \"foo\":true, }\n",
              Parser4Context::PARSER_JSON,
              "<string>:1.15: syntax error, unexpected }, "
              "expecting constant string");

    // bad type
    testError("{ \"Dhcp4\":{\n"
              "  \"valid-lifetime\":false }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:2.20-24: syntax error, unexpected boolean, "
              "expecting integer");

    // unknown keyword
    testError("{ \"Dhcp4\":{\n"
              " \"valid_lifetime\":600 }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:2.2-17: got unexpected keyword "
              "\"valid_lifetime\" in Dhcp4 map.");

    // missing parameter
    testError("{ \"name\": \"foo\",\n"
              "  \"code\": 123 }\n",
              Parser4Context::PARSER_OPTION_DEF,
              "missing parameter 'type' (<string>:1:1) "
              "[option-def map between <string>:1:1 and <string>:2:15]");

    // user context and embedded comments
    testError("{ \"Dhcp4\":{\n"
              "  \"comment\": true,\n"
              "  \"valid-lifetime\": 600 }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:2.14-17: syntax error, unexpected boolean, "
              "expecting constant string");

    testError("{ \"Dhcp4\":{\n"
              "  \"user-context\": \"a comment\",\n"
              "  \"valid-lifetime\": 600 }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:2.19-29: syntax error, unexpected constant string, "
              "expecting {");

    testError("{ \"Dhcp4\":{\n"
              "  \"comment\": \"a comment\",\n"
              "  \"comment\": \"another one\",\n"
              "  \"valid-lifetime\": 600 }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:3)");

    testError("{ \"Dhcp4\":{\n"
              "  \"user-context\": { \"version\": 1 },\n"
              "  \"user-context\": { \"one\": \"only\" },\n"
              "  \"valid-lifetime\": 600 }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:3.3-16: duplicate user-context entries "
              "(previous at <string>:2:19)");

    testError("{ \"Dhcp4\":{\n"
              "  \"user-context\": { \"comment\": \"indirect\" },\n"
              "  \"comment\": \"a comment\",\n"
              "  \"valid-lifetime\": 600 }}\n",
              Parser4Context::PARSER_DHCP4,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:19)");
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
            Parser4Context ctx;
            result = ctx.parseString(json, Parser4Context::PARSER_JSON);
        } catch (const std::exception &x) {
            cout << "EXCEPTION: " << x.what() << endl;
            throw;
        });
        ASSERT_EQ(Element::string, result->getType());
        EXPECT_EQ(ins, result->stringValue());
    }
}

// This test checks that all representations of a slash are recognized properly.
TEST(ParserTest, unicodeSlash) {
    // check the 4 possible encodings of solidus '/'
    ConstElementPtr result;
    string json = "\"/\\/\\u002f\\u002F\"";
    ASSERT_NO_THROW(
    try {
        Parser4Context ctx;
        result = ctx.parseString(json, Parser4Context::PARSER_JSON);
    } catch (const std::exception &x) {
        cout << "EXCEPTION: " << x.what() << endl;
        throw;
    });
    ASSERT_EQ(Element::string, result->getType());
    EXPECT_EQ("////", result->stringValue());
}

};
};
};
