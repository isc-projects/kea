// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>

#include <gtest/gtest.h>
#include <cc/data.h>
#include <d2/parser_context.h>
#include <d2/tests/parser_unittest.h>
#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>

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
void testParser(const std::string& txt, D2ParserContext::ParserType parser_type,
    bool compare = true) {
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
     testParser(txt, D2ParserContext::PARSER_DHCPDDNS);
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
     testParser(txt, D2ParserContext::PARSER_DHCPDDNS);
}

TEST(ParserTest, keywordControlAgent) {
    string txt = "{ \"Control-agent\": { } }";
    testParser(txt, D2ParserContext::PARSER_DHCPDDNS);
}

TEST(ParserTest, Logging) {
    string txt = "{ \"Logging\": { \n"
                 "    \"loggers\": [ \n"
                 "        { \n"
                 "            \"name\": \"kea-dhcp6\", \n"
                 "            \"output_options\": [ \n"
                 "                { \n"
                 "                    \"output\": \"stdout\" \n"
                 "                } \n"
                 "            ], \n"
                 "            \"debuglevel\": 0, \n"
                 "            \"severity\": \"INFO\" \n"
                 "        } \n"
                 "    ] }\n"
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

    EXPECT_NO_THROW(json = Element::fromJSONFile(decommented, true));
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
    configs.push_back("comments.json");
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
               const std::string& msg)
{
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
              "<string>:1.1-6: Invalid control in \"a\n\tb\"");
    testError("\"a\\n\\tb\"",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.1-8: syntax error, unexpected constant string, "
              "expecting {");
    testError("\"a\\x01b\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-8: Bad escape in \"a\\x01b\"");
    testError("\"a\\u0162\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-9: Unsupported unicode escape in \"a\\u0162\"");
    testError("\"a\\u062z\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-9: Bad escape in \"a\\u062z\"");
    testError("\"abc\\\"",
              D2ParserContext::PARSER_JSON,
              "<string>:1.1-6: Overflow escape in \"abc\\\"");

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
              "<string>:1.3-5: syntax error, unexpected integer");
    testError("{ \"foo\" }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.9: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"foo\" }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.9: syntax error, unexpected }, expecting :");
    testError("{ \"foo\":null }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.3-7: got unexpected keyword "
              "\"foo\" in toplevel map.");
    testError("{ \"Dhcp6\" }\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:1.11: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"Dhcp4\":[]\n",
              D2ParserContext::PARSER_DHCPDDNS,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting \",\" or }");
    testError("{}{}\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected {, "
              "expecting end of file");

    // bad commas
    testError("{ , }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ , \"foo\":true }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ \"foo\":true, }\n",
              D2ParserContext::PARSER_JSON,
              "<string>:1.15: syntax error, unexpected }, "
              "expecting constant string");

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

};
};
};
