// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <agent/parser_context.h>
#include <cc/dhcp_config_error.h>
#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>
#include <gtest/gtest.h>
#include <fstream>
#include <set>

using namespace isc::data;
using namespace isc::test;
using namespace std;

namespace isc {
namespace agent {
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

// This test checks if full config (with top level and Control-agent objects) can
// be parsed with syntactic checking (and as pure JSON).
TEST(ParserTest, keywordAgent) {
    string txt = "{ \"Control-agent\": {\n"
        "    \"http-host\": \"localhost\",\n"
        "    \"http-port\": 8000,\n"
        "    \"control-sockets\": {"
        "        \"dhcp4\": {"
        "            \"socket-type\": \"unix\","
        "            \"socket-name\": \"/tmp/kea4-ctrl-socket\""
        "        },"
        "        \"dhcp6\": {"
        "            \"socket-type\": \"unix\","
        "            \"socket-name\": \"/tmp/kea6-ctrl-socket\""
        "        },"
        "        \"d2\": {"
        "            \"socket-type\": \"unix\","
        "            \"socket-name\": \"/tmp/kea-ddns-ctrl-socket\""
        "        }"
        "    },"
        "    \"hooks-libraries\": ["
        "    {"
        "        \"library\": \"/opt/local/control-agent-commands.so\","
        "        \"parameters\": {"
        "            \"param1\": \"foo\""
        "        }"
        "    }"
        "   ]"
        "} }";
    // This is a full config, so we'll parse it as full config (PARSER_AGENT)
    testParser(txt, ParserContext::PARSER_AGENT);
    testParser(txt, ParserContext::PARSER_JSON);
}

// This test checks if simplified config (without top level and Control-agent
// objects) can be parsed with syntactic checking (and as pure JSON).
TEST(ParserTest, keywordSubAgent) {

    // This is similar to previous test, but note the lack of outer
    // map and Control-agent.
    string txt = "{\n"
        "    \"http-host\": \"localhost\",\n"
        "    \"http-port\": 8000,\n"
        "    \"control-sockets\": {"
        "        \"dhcp4\": {"
        "            \"socket-type\": \"unix\","
        "            \"socket-name\": \"/tmp/kea4-ctrl-socket\""
        "        },"
        "        \"dhcp6\": {"
        "            \"socket-type\": \"unix\","
        "            \"socket-name\": \"/tmp/kea6-ctrl-socket\""
        "        },"
        "        \"d2\": {"
        "            \"socket-type\": \"unix\","
        "            \"socket-name\": \"/tmp/kea-ddns-ctrl-socket\""
        "        }"
        "    },"
        "    \"hooks-libraries\": ["
        "    {"
        "        \"library\": \"/opt/local/control-agent-commands.so\","
        "        \"parameters\": {"
        "            \"param1\": \"foo\""
        "        }"
        "    }"
        "   ]"
        "}";

    // This is only a subset of full config, so we'll parse with PARSER_SUB_AGENT.
    testParser(txt, ParserContext::PARSER_SUB_AGENT);
    testParser(txt, ParserContext::PARSER_JSON);
}

// Tests if bash (#) comments are supported. That's the only comment type that
// was supported by the old parser.
TEST(ParserTest, bashComments) {
    string txt= "{ \"Control-agent\": {"
                "  \"http-host\": \"localhost\","
                "  \"http-port\": 9000,\n"
                "  \"control-sockets\": {\n"
                "    \"d2\": {\n"
                "# this is a comment\n"
                "\"socket-type\": \"unix\", \n"
                "# This socket is mine. I can name it whatever\n"
                "# I like, ok?\n"
                "\"socket-name\": \"Hector\" \n"
                "} } } }";
    testParser(txt, ParserContext::PARSER_AGENT);
}

// Tests if C++ (//) comments can start anywhere, not just in the first line.
TEST(ParserTest, cppComments) {
    string txt= "{ \"Control-agent\": {"
                "  \"http-host\": \"localhost\","
                "  \"http-port\": 9001, // the level is over 9000!\n"
                "  \"control-sockets\": {\n"
                "    // Let's try talking to D2. Sadly, it never talks"
                "    // to us back :( Maybe he doesn't like his name?\n"
                "    \"d2\": {"
                "\"socket-type\": \"unix\", \n"
                "\"socket-name\": \"Hector\" \n"
                "} } } }";

    testParser(txt, ParserContext::PARSER_AGENT, false);
}

// Tests if bash (#) comments can start anywhere, not just in the first line.
TEST(ParserTest, bashCommentsInline) {
    string txt= "{ \"Control-agent\": {"
                "  \"http-host\": \"localhost\","
                "  \"http-port\": 9000,\n"
                "  \"control-sockets\": {\n"
                "    \"d2\": {"
                "\"socket-type\": \"unix\", # Maybe Hector is not really a \n"
                "\"socket-name\": \"Hector\" # Unix process?\n"
                "# Oh no! He's a windows one and just pretending!\n"
                "} } } }";
    testParser(txt, ParserContext::PARSER_AGENT, false);
}

// Tests if multi-line C style comments are handled correctly.
TEST(ParserTest, multilineComments) {
    string txt= "{ \"Control-agent\": {"
                "  \"http-host\": \"localhost\","
                "  \"http-port\": 9000,\n"
                "  \"control-sockets\": {\n"
                "    \"dhcp4\": {\n"
                "        \"socket-type\": \"unix\"\n"
                "    }\n"
                "  /* Ok, forget about it. If Hector doesn't want to talk,\n"
                "     we won't talk to him either. We now have quiet days. */\n"
                "  /* \"d2\": {"
                "  \"socket-type\": \"unix\",\n"
                "\"socket-name\": \"Hector\"\n"
                "}*/ } } }";
    testParser(txt, ParserContext::PARSER_AGENT, false);
}

// Tests if embedded comments are handled correctly.
TEST(ParserTest, embbededComments) {
    string txt= "{ \"Control-agent\": {"
                "  \"comment\": \"a comment\","
                "  \"http-host\": \"localhost\","
                "  \"http-port\": 9000,\n"
                "  \"control-sockets\": {\n"
                "    \"dhcp4\": {\n"
                "        \"user-context\": { \"comment\": \"indirect\" },\n"
                "        \"socket-type\": \"unix\"\n"
                "    } },\n"
                "  \"user-context\": { \"compatible\": true }\n"
                "} }";
    testParser(txt, ParserContext::PARSER_AGENT, false);
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
        test_json = ctx.parseFile(fname, ParserContext::PARSER_AGENT);
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
// the second time with AgentParser. Both JSON trees are then compared.
// Hopefully the list of example configs will grow over time.
TEST(ParserTest, file) {
    vector<string> configs;
    configs.push_back("comments.json");
    configs.push_back("https.json");
    configs.push_back("simple.json");

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i]);
    }
}

/// @brief Tests error conditions in AgentParser
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
              ParserContext::PARSER_AGENT,
              "<string>:1.1-3: syntax error, unexpected integer, "
              "expecting {");
    testError("-456",
              ParserContext::PARSER_AGENT,
              "<string>:1.1-4: syntax error, unexpected integer, "
              "expecting {");
    testError("-0001",
              ParserContext::PARSER_AGENT,
              "<string>:1.1-5: syntax error, unexpected integer, "
              "expecting {");
    testError("1234567890123456789012345678901234567890",
              ParserContext::PARSER_JSON,
              "<string>:1.1-40: Failed to convert "
              "1234567890123456789012345678901234567890"
              " to an integer.");
    testError("-3.14e+0",
              ParserContext::PARSER_AGENT,
              "<string>:1.1-8: syntax error, unexpected floating point, "
              "expecting {");
    testError("1e50000",
              ParserContext::PARSER_JSON,
              "<string>:1.1-7: Failed to convert 1e50000 "
              "to a floating point.");

    // strings
    testError("\"aabb\"",
              ParserContext::PARSER_AGENT,
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
              "<string>:1.1-6 (near 2): Invalid control in \"a\n\tb\"");
    testError("\"a\n\\u12\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-8 (near 2): Invalid control in \"a\n\\u12\"");
    testError("\"a\\n\\tb\"",
              ParserContext::PARSER_AGENT,
              "<string>:1.1-8: syntax error, unexpected constant string, "
              "expecting {");
    testError("\"a\\x01b\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-8 (near 3): Bad escape in \"a\\x01b\"");
    testError("\"a\\u0162\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-9 (near 4): Unsupported unicode escape "
              "in \"a\\u0162\"");
    testError("\"a\\u062z\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-9 (near 3): Bad escape in \"a\\u062z\"");
    testError("\"abc\\\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-6 (near 6): Overflow escape in \"abc\\\"");
    testError("\"a\\u006\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-8 (near 3): Overflow unicode escape "
              "in \"a\\u006\"");
    testError("\"\\u\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-4 (near 2): Overflow unicode escape in \"\\u\"");
    testError("\"\\u\x02\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-5 (near 2): Bad escape in \"\\u\x02\"");
    testError("\"\\u\\\"foo\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-5 (near 2): Bad escape in \"\\u\\\"...");
    testError("\"\x02\\u\"",
              ParserContext::PARSER_JSON,
              "<string>:1.1-5 (near 1): Invalid control in \"\x02\\u\"");

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
              ParserContext::PARSER_AGENT,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("[]\n",
              ParserContext::PARSER_AGENT,
              "<string>:1.1: syntax error, unexpected [, "
              "expecting {");
    testError("{ 123 }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting }");
    testError("{ 123 }\n",
              ParserContext::PARSER_AGENT,
              "<string>:1.3-5: syntax error, unexpected integer, "
              "expecting Control-agent");
    testError("{ \"foo\" }\n",
              ParserContext::PARSER_JSON,
              "<string>:1.9: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"foo\" }\n",
              ParserContext::PARSER_AGENT,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting Control-agent");
    testError("{ \"foo\":null }\n",
              ParserContext::PARSER_AGENT,
              "<string>:1.3-7: syntax error, unexpected constant string, "
              "expecting Control-agent");
    testError("{ \"Logging\":null }\n",
              ParserContext::PARSER_AGENT,
              "<string>:1.3-11: syntax error, unexpected constant string, "
              "expecting Control-agent");
    testError("{ \"Control-agent\" }\n",
              ParserContext::PARSER_AGENT,
              "<string>:1.19: syntax error, unexpected }, "
              "expecting :");
    testError("{ \"Control-agent\":",
              ParserContext::PARSER_AGENT,
              "<string>:1.19: syntax error, unexpected end of file, "
              "expecting {");
    testError("{}{}\n",
              ParserContext::PARSER_JSON,
              "<string>:1.3: syntax error, unexpected {, "
              "expecting end of file");

    // duplicate in map
    testError("{ \"foo\": 1, \"foo\": true }\n",
              ParserContext::PARSER_JSON,
              "<string>:1:13: duplicate foo entries in "
              "JSON map (previous at <string>:1:10)");

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
    testError("{ \"Control-agent\":{\n"
              "  \"http-port\":false }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:2.15-19: syntax error, unexpected boolean, "
              "expecting integer");

    // unknown keyword
    testError("{ \"Control-agent\":{\n"
              " \"topping\": \"Mozzarella\" }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:2.2-10: got unexpected keyword "
              "\"topping\" in Control-agent map.");

    // user context and embedded comments
    testError("{ \"Control-agent\":{\n"
              "  \"comment\": true,\n"
              "  \"http-port\": 9000 }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:2.14-17: syntax error, unexpected boolean, "
              "expecting constant string");

    testError("{ \"Control-agent\":{\n"
              "  \"user-context\": \"a comment\",\n"
              "  \"http-port\": 9000 }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:2.19-29: syntax error, unexpected constant string, "
              "expecting {");

    testError("{ \"Control-agent\":{\n"
              "  \"comment\": \"a comment\",\n"
              "  \"comment\": \"another one\",\n"
              "  \"http-port\": 9000 }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:3)");

    testError("{ \"Control-agent\":{\n"
              "  \"user-context\": { \"version\": 1 },\n"
              "  \"user-context\": { \"one\": \"only\" },\n"
              "  \"http-port\": 9000 }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:3.3-16: duplicate user-context entries "
              "(previous at <string>:2:19)");

    testError("{ \"Control-agent\":{\n"
              "  \"user-context\": { \"comment\": \"indirect\" },\n"
              "  \"comment\": \"a comment\",\n"
              "  \"http-port\": 9000 }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:3.3-11: duplicate user-context/comment entries "
              "(previous at <string>:2:19)");

    // duplicate Control-agent entries
    testError("{ \"Control-agent\":{\n"
              "  \"comment\": \"first\" },\n"
              "  \"Control-agent\":{\n"
              "  \"comment\": \"second\" }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:2.23: syntax error, unexpected \",\", expecting }");

    // duplicate of not string entries
    testError("{ \"Control-agent\":{\n"
              " \"http-port\": 8000,\n"
              " \"http-port\": 8001 }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:3:2: duplicate http-port entries in "
              "Control-agent map (previous at <string>:2:15)");

    // duplicate of string entries
    testError("{ \"Control-agent\":{\n"
              " \"http-host\": \"127.0.0.1\",\n"
              " \"http-host\": \"::1\" }}\n",
              ParserContext::PARSER_AGENT,
              "<string>:3:2: duplicate http-host entries in "
              "Control-agent map (previous at <string>:2:15)");
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

/// @brief Load a file into a JSON element.
///
/// @param fname The name of the file to load.
/// @param list The JSON element list to add the parsing result to.
void loadFile(const string& fname, ElementPtr list) {
    ParserContext ctx;
    ElementPtr json;
    EXPECT_NO_THROW(json = ctx.parseFile(fname, ParserContext::PARSER_AGENT));
    ASSERT_TRUE(json);
    list->add(json);
}

// This test checks that all map entries are in the sample file.
TEST(ParserTest, mapEntries) {
    // Type of keyword set.
    typedef set<string> KeywordSet;

    // Get keywords from the syntax file (agent_parser.yy).
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

    // Get keywords from the sample files
    string sample_dir(CFG_EXAMPLES);
    sample_dir += "/";
    ElementPtr sample_json = Element::createList();
    loadFile(sample_dir + "https.json", sample_json);
    loadFile(sample_dir + "simple.json", sample_json);
    KeywordSet sample_keys;
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
    ParserContext ctx;
    EXPECT_THROW(ctx.parseString(before + after,
                                 ParserContext::PARSER_AGENT),
                 ParseError) << "config: " << config;
}

// This test checks that duplicate entries make parsing to fail.
TEST(ParserTest, duplicateMapEntries) {
    // Get the config to work with from the sample file.
    string sample_fname(CFG_EXAMPLES);
    sample_fname += "/simple.json";
    ParserContext ctx;
    ElementPtr sample_json;
    EXPECT_NO_THROW(sample_json =
        ctx.parseFile(sample_fname, ParserContext::PARSER_AGENT));
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

}
}
}
