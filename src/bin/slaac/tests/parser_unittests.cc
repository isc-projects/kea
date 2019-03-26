// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>
#include <cc/data.h>
#include <slaac/parser_context.h>
#include <slaac/simple_parser.h>
#include <cc/dhcp_config_error.h>
#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>

using namespace isc::data;
using namespace isc::test;
using namespace std;

namespace isc {
namespace slaac {
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
void testParser(const std::string& txt, ParserContext::ParserType parser_type,
    bool compare = true) {
    ConstElementPtr test_json;

    ASSERT_NO_THROW({
            try {
                ParserContext ctx;
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
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, listInList) {
    string txt = "[ [ \"Britain\", \"Wales\", \"Scotland\" ], "
                 "[ \"Pomorze\", \"Wielkopolska\", \"Tatry\"] ]";
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, nestedMaps) {
    string txt = "{ \"europe\": { \"UK\": { \"London\": { \"street\": \"221B Baker\" }}}}";
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, nestedLists) {
    string txt = "[ \"half\", [ \"quarter\", [ \"eighth\", [ \"sixteenth\" ]]]]";
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, listsInMaps) {
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelgeuse\" ], "
                    "\"cygnus\": [ \"deneb\", \"albireo\"] } }";
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, mapsInLists) {
    string txt = "[ { \"body\": \"earth\", \"gravity\": 1.0 },"
                 " { \"body\": \"mars\", \"gravity\": 0.376 } ]";
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, types) {
    string txt = "{ \"string\": \"foo\","
                   "\"integer\": 42,"
                   "\"boolean\": true,"
                   "\"map\": { \"foo\": \"bar\" },"
                   "\"list\": [ 1, 2, 3 ],"
                   "\"null\": null }";
    testParser(txt, ParserContext::PARSER_JSON);
}

TEST(ParserTest, keywordJSON) {
    string txt = "{ \"name\": \"user\","
                   "\"type\": \"password\","
                   "\"user\": \"name\","
                   "\"password\": \"type\" }";
    testParser(txt, ParserContext::PARSER_JSON);
}

// This test checks if full config (with top level and Slaac objects) can
// be parsed with syntactic checking (and as pure JSON).
TEST(ParserTest, keywordSlaac) {
    string txt = "{ \"Slaac\": {\n"
        "    \"hop-limit\": 64,"
        "    \"managed-flag\": true,"
        "    \"other-flag\": true,"
        "    \"router-lifetime\": 9000,"
        "    \"reachable-time\": 3600,"
        "    \"retrans-timer\": 10,"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"ethX\" ]"
        "    },"
        "    \"source-ll-address\": false,"
        "    \"mtu\": 1500,"
        "    \"prefix-infos\": ["
        "        {"
        "            \"prefix\": \"2001:db8::/64\","
        "            \"on-link-flag\": true,"
        "            \"address-config-flag\": true,"
        "            \"valid-lifetime\": 86400,"
        "            \"preferred-lifetime\": 21600"
        "        }"
        "     ],"
        "    \"universal-ra\": { \"ietf\": { \"foo\": true } }"
        "} }";
    // This is a full config, so we'll parse it as full config (PARSER_SLAAC)
    testParser(txt, ParserContext::PARSER_SLAAC);
    testParser(txt, ParserContext::PARSER_JSON);
}

// This test checks if simplified config (without top level and Slaac
// objects) can be parsed with syntactic checking (and as pure JSON).
TEST(ParserTest, keywordSubSlaac) {

    // This is similar to previous test, but note the lack of outer
    // map and Slaac.
    string txt = "{\n"
        "    \"hop-limit\": 64,"
        "    \"managed-flag\": true,"
        "    \"other-flag\": true,"
        "    \"router-lifetime\": 9000,"
        "    \"reachable-time\": 3600,"
        "    \"retrans-timer\": 10,"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"ethX\" ]"
        "    },"
        "    \"source-ll-address\": false,"
        "    \"mtu\": 1500,"
        "    \"prefix-infos\": ["
        "        {"
        "            \"prefix\": \"2001:db8::/64\","
        "            \"on-link-flag\": true,"
        "            \"address-config-flag\": true,"
        "            \"valid-lifetime\": 86400,"
        "            \"preferred-lifetime\": 21600"
        "        }"
        "     ],"
        "    \"universal-ra\": { \"ietf\": { \"foo\": true } }"
        "}";

    // This is only a subset of full config, so we'll parse with PARSER_SUB_SLAAC.
    testParser(txt, ParserContext::PARSER_SUB_SLAAC);
    testParser(txt, ParserContext::PARSER_JSON);
}

// Tests if bash (#) comments are supported. That's the only comment type that
// was supported by the old parser.
TEST(ParserTest, bashComments) {
    string txt= "{ \"Slaac\": {"
                "  \"prefix-infos\": [\n"
                "    {\n"
                "      \"prefix\": \"foo\",\n"
                "# this is a comment\n"
                "\"valid-lifetime\": 7200, \n"
                "# This prefix is mine. I can prefer it whatever\n"
                "# I like, ok?\n"
                "\"preferred-lifetime\": 60 \n"
                "} ] } }";
    testParser(txt, ParserContext::PARSER_SLAAC);
}

// Tests if C++ (//) comments can start anywhere, not just in the first line.
TEST(ParserTest, cppComments) {
    string txt= "{ \"Slaac\": { // the level is over 9000!\n"
                "  \"prefix-infos\": [\n"
                "    {\n"
                "    // Let's try talking to D2. Sadly, it never talks"
                "    // to us back :( Maybe he doesn't like his name?\n"
                "      \"prefix\": \"foo\",\n"
                "\"valid-lifetime\": 7200, \n"
                "\"preferred-lifetime\": 60 \n"
                "} ] } }";
    testParser(txt, ParserContext::PARSER_SLAAC, false);
}

// Tests if bash (#) comments can start anywhere, not just in the first line.
TEST(ParserTest, bashCommentsInline) {
    string txt= "{ \"Slaac\": {"
                "  \"prefix-infos\": [\n"
                "    {\n"
                "      \"prefix\": \"foo\", # Unix process?\n"
                "\"valid-lifetime\": 7200, # Maybe Hector is not really a \n"
                "\"preferred-lifetime\": 60 \n"
                "# Oh no! He's a windows one and just pretending!\n"
                "} ] } }";
    testParser(txt, ParserContext::PARSER_SLAAC, false);
}

// Tests if multi-line C style comments are handled correctly.
TEST(ParserTest, multilineComments) {
    string txt= "{ \"Slaac\": {"
                "/*  \"hop-limit\": 64,"
                "   \"managed-flag\": true, */"
                "  \"prefix-infos\": [\n"
                "    {\n"
                "      \"prefix\": \"foo\",\n"
                "\"valid-lifetime\": 7200,\n"
                "  /* Ok, forget about it. If Hector doesn't want to talk,\n"
                "     we won't talk to him either. We now have quiet days. */\n"
                "\"preferred-lifetime\": 60 \n"
                "} ] } }";
    testParser(txt, ParserContext::PARSER_SLAAC, false);
}

// Tests if embedded comments are handled correctly.
TEST(ParserTest, embbededComments) {
    string txt= "{ \"Slaac\": {"
                "  \"comment\": \"a comment\","
                "  \"prefix-infos\": [\n"
                "    {\n"
                "      \"prefix\": \"foo\",\n"
                "        \"user-context\": { \"comment\": \"indirect\" },\n"
                "      \"valid-lifetime\": 7200,\n"
                "      \"preferred-lifetime\": 3600\n"
                "    }\n"
                "  ],\n"
                "  \"user-context\": { \"compatible\": true }\n"
                "} }";
    testParser(txt, ParserContext::PARSER_SLAAC, false);
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

    EXPECT_NO_THROW(json = Element::fromJSONFile(decommented, true));
    reference_json = moveComments(json);

    // remove the temporary file
    EXPECT_NO_THROW(::remove(decommented.c_str()));

    EXPECT_NO_THROW(
    try {
        ParserContext ctx;
        test_json = ctx.parseFile(fname, ParserContext::PARSER_SLAAC);
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
// the second time with SlaacParser. Both JSON trees are then compared.
// Hopefully the list of example configs will grow over time.
TEST(ParserTest, file) {
    vector<string> configs;
    configs.push_back("simple.json");

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i]);
    }
}

// This test loads the simple.json (todo: add all-keys.json) file and
// check global parameters.
TEST(ParserTest, globalParameters) {
    ConstElementPtr json;
    ParserContext ctx;
    string fname = string(CFG_EXAMPLES) + "/" + "simple.json";
    EXPECT_NO_THROW(json = ctx.parseFile(fname, ParserContext::PARSER_SLAAC));
    ASSERT_TRUE(json);
    EXPECT_NO_THROW(json = json->get("Slaac"));
    ASSERT_TRUE(json);
    SlaacSimpleParser parser;
    EXPECT_NO_THROW(parser.checkKeywords(parser.SLAAC_PARAMETERS, json));
}

/// @brief Tests error conditions in SlaacParser
///
/// @param txt text to be parsed
/// @param parser_type type of the parser to be used in the test
/// @param msg expected content of the exception
void testError(const std::string& txt,
               ParserContext::ParserType parser_type,
               const std::string& msg)
{
    try {
        ParserContext ctx;
        ConstElementPtr parsed = ctx.parseString(txt, parser_type);
        FAIL() << "Expected ParseError but nothing was raised (expected: "
               << msg << ")";
    }
    catch (const ParseError& ex) {
        EXPECT_EQ(msg, ex.what());
    }
    catch (...) {
        FAIL() << "Expected ParseError but something else was raised";
    }
}

// Verify that error conditions are handled correctly.
TEST(ParserTest, errors) {
    // no input
    testError("", ParserContext::PARSER_JSON,
              "<string>:1.1: syntax error, unexpected end of file");
    testError(" ", ParserContext::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\n", ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("\t", ParserContext::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");
    testError("\r", ParserContext::PARSER_JSON,
              "<string>:1.2: syntax error, unexpected end of file");

    // comments
    testError("# nothing\n",
              ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError(" #\n",
              ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("// nothing\n",
              ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* nothing */\n",
              ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n",
              ParserContext::PARSER_JSON,
              "<string>:3.1: syntax error, unexpected end of file");
    testError("/* no\nthing */\n\n",
              ParserContext::PARSER_JSON,
              "<string>:4.1: syntax error, unexpected end of file");
    testError("/* nothing\n",
              ParserContext::PARSER_JSON,
              "Comment not closed. (/* in line 1");
    testError("\n\n\n/* nothing\n",
              ParserContext::PARSER_JSON,
              "Comment not closed. (/* in line 4");
    testError("{ /* */*/ }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3-8: Invalid character: *");
    testError("{ /* // *// }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3-11: Invalid character: /");
    testError("{ /* // *///  }\n",
              ParserContext::PARSER_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting }");

    // includes
    testError("<?\n",
              ParserContext::PARSER_JSON,
              "Directive not closed.");
    testError("<?include\n",
              ParserContext::PARSER_JSON,
              "Directive not closed.");
    string file = string(CFG_EXAMPLES) + "/" + "simple.json";
    testError("<?include \"" + file + "\"\n",
              ParserContext::PARSER_JSON,
              "Directive not closed.");
    testError("<?include \"/foo/bar\" ?>/n",
              ParserContext::PARSER_JSON,
              "Can't open include file /foo/bar");

    // JSON keywords
    testError("{ \"foo\": True }",
              ParserContext::PARSER_JSON,
              "<string>:1.10-13: JSON true reserved keyword is lower case only");
    testError("{ \"foo\": False }",
              ParserContext::PARSER_JSON,
              "<string>:1.10-14: JSON false reserved keyword is lower case only");
    testError("{ \"foo\": NULL }",
              ParserContext::PARSER_JSON,
              "<string>:1.10-13: JSON null reserved keyword is lower case only");
    testError("{ \"foo\": Tru }",
              ParserContext::PARSER_JSON,
              "<string>:1.10: Invalid character: T");
    testError("{ \"foo\": nul }",
              ParserContext::PARSER_JSON,
              "<string>:1.10: Invalid character: n");

    // numbers
    testError("123",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1-3: syntax error, unexpected integer, "
              "expecting {");
    testError("-456",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1-4: syntax error, unexpected integer, "
              "expecting {");
    testError("-0001",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1-5: syntax error, unexpected integer, "
              "expecting {");
    testError("1234567890123456789012345678901234567890",
              ParserContext::PARSER_JSON,
              "<string>:1.1-40: Failed to convert "
              "1234567890123456789012345678901234567890"
              " to an integer.");
    testError("-3.14e+0",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1-8: syntax error, unexpected floating point, "
              "expecting {");
    testError("1e50000",
              ParserContext::PARSER_JSON,
              "<string>:1.1-7: Failed to convert 1e50000 "
              "to a floating point.");

    // strings
    testError("\"aabb\"",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1-6: syntax error, unexpected constant string, "
              "expecting {");
    testError("{ \"aabb\"err",
              ParserContext::PARSER_JSON,
              "<string>:1.9: Invalid character: e");
    testError("{ err\"aabb\"",
              ParserContext::PARSER_JSON,
              "<string>:1.3: Invalid character: e");
    testError("\"a\n\tb\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-6: Invalid control in \"a\n\tb\"");
    testError("\"a\\n\\tb\"",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1-8: syntax error, unexpected constant string, "
              "expecting {");
    testError("\"a\\x01b\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-8: Bad escape in \"a\\x01b\"");
    testError("\"a\\u0162\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-9: Unsupported unicode escape in \"a\\u0162\"");
    testError("\"a\\u062z\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-9: Bad escape in \"a\\u062z\"");
    testError("\"abc\\\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-6: Overflow escape in \"abc\\\"");

    // from data_unittest.c
    testError("\\a",
              ParserContext::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\",
              ParserContext::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");
    testError("\\\"\\\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1: Invalid character: \\");

    // want a map
    testError("[]\n",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("[]\n",
              ParserContext::PARSER_SLAAC,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("{ 123 }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting }");
    testError("{ 123 }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting Slaac");
    testError("{ \"foo\" }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.9: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"foo\" }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting Slaac");
    testError("{ \"foo\":null }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting Slaac");
    testError("{ \"Slaac\" }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:1.11: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"Slaac\":",
              ParserContext::PARSER_SLAAC,
              "<string>:1.11: syntax error, unexpected end of file, "
              "expecting {");
    testError("{}{}\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected {, "
              "expecting end of file");

    // bad commas
    testError("{ , }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ , \"foo\":true }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected \",\", "
              "expecting }");
    testError("{ \"foo\":true, }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.15: syntax error, unexpected }, "
              "expecting constant string");

    // bad type
    testError("{ \"Slaac\":{\n"
              "  \"prefix-infos\":false }}\n",
              ParserContext::PARSER_SLAAC,
              "<string>:2.18-22: syntax error, unexpected boolean, "
              "expecting [");

    // unknown keyword
    testError("{ \"Slaac\":{\n"
              " \"topping\": \"Mozarella\" }}\n",
              ParserContext::PARSER_SLAAC,
              "<string>:2.2-10: got unexpected keyword "
              "\"topping\" in Slaac map.");

    // user context and embedded comments
    testError("{ \"Slaac\":{\n"
              "  \"comment\": true } }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:2.14-17: syntax error, unexpected boolean, "
              "expecting constant string");

    testError("{ \"Slaac\":{\n"
              "  \"user-context\": \"a comment\" } }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:2.19-29: syntax error, unexpected constant string, "
              "expecting {");

    testError("{ \"Slaac\":{\n"
              "  \"comment\": \"a comment\",\n"
              "  \"comment\": \"another one\" } }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:3)");

    testError("{ \"Slaac\":{\n"
              "  \"user-context\": { \"version\": 1 },\n"
              "  \"user-context\": { \"one\": \"only\" } } }\n",
              ParserContext::PARSER_SLAAC,
              "<string>:3.3-16: duplicate user-context entries "
              "(previous at <string>:2:19)");

    testError("{ \"Slaac\":{\n"
              "  \"user-context\": { \"comment\": \"indirect\" },\n"
              "  \"comment\": \"a comment\" } }\n",
              ParserContext::PARSER_SLAAC,
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
            ParserContext ctx;
            result = ctx.parseString(json, ParserContext::PARSER_JSON);
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
        ParserContext ctx;
        result = ctx.parseString(json, ParserContext::PARSER_JSON);
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
