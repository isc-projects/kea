// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <cc/data.h>
#include <dhcp4/parser_context.h>

using namespace isc::data;
using namespace std;

namespace {

void compareJSON(ConstElementPtr a, ConstElementPtr b, bool print = true) {
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    if (print) {
        // std::cout << "JSON A: -----" << endl << a->str() << std::endl;
        // std::cout << "JSON B: -----" << endl << b->str() << std::endl;
        // cout << "---------" << endl << endl;
    }
    EXPECT_EQ(a->str(), b->str());
}

void testParser(const std::string& txt, Parser4Context::ParserType parser_type) {
    ElementPtr reference_json;
    ConstElementPtr test_json;

    ASSERT_NO_THROW(reference_json = Element::fromJSON(txt, true));
    ASSERT_NO_THROW({
            try {
        Parser4Context ctx;
        test_json = ctx.parseString(txt, parser_type);
            } catch (const std::exception &e) {
                cout << "EXCEPTION: " << e.what() << endl;
                throw;
            }

    });

    // Now compare if both representations are the same.
    compareJSON(reference_json, test_json);
}

void testParser2(const std::string& txt, Parser4Context::ParserType parser_type) {
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
    /// @todo: Implement actual validation here. since the original
    /// Element::fromJSON does not support several comment types, we don't
    /// have anything to compare with.
    /// std::cout << "Original text:" << txt << endl;
    /// std::cout << "Parsed text  :" << test_json->str() << endl;
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
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelguese\" ], "
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
                  "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
                  "    \"subnet\": \"2001:db8:1::/48\", "
                  "    \"interface\": \"test\" } ],\n"
                   "\"valid-lifetime\": 4000 } }";
     testParser2(txt, Parser4Context::PARSER_DHCP4);
}

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
    testParser2(txt, Parser4Context::PARSER_DHCP4);
}

TEST(ParserTest, cComments) {
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
    testParser2(txt, Parser4Context::PARSER_DHCP4);
}

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
    testParser2(txt, Parser4Context::PARSER_DHCP4);
}

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
    testParser2(txt, Parser4Context::PARSER_DHCP4);
}


void testFile(const std::string& fname, bool print) {
    ElementPtr reference_json;
    ConstElementPtr test_json;

    cout << "Attempting to load file " << fname << endl;

    EXPECT_NO_THROW(reference_json = Element::fromJSONFile(fname, true));

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

    compareJSON(reference_json, test_json, print);


}

// This test loads all available existing files. Each config is loaded
// twice: first with the existing Element::fromJSONFile() and then
// the second time with Parser6. Both JSON trees are then compared.
TEST(ParserTest, file) {
    vector<string> configs;
    configs.push_back("backends.json");
    configs.push_back("classify.json");
    configs.push_back("dhcpv4-over-dhcpv6.json");
    configs.push_back("hooks.json");
    configs.push_back("leases-expiration.json");
    configs.push_back("multiple-options.json");
    configs.push_back("mysql-reservations.json");
    configs.push_back("pgsql-reservations.json");
    configs.push_back("reservations.json");
    configs.push_back("several-subnets.json");
    configs.push_back("single-subnet.json");

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i], false);
    }
}

void testError(const std::string& txt,
               Parser4Context::ParserType parser_type,
               const std::string& msg)
{
    try {
        Parser4Context ctx;
        ConstElementPtr parsed = ctx.parseString(txt, parser_type);
        FAIL() << "Expected Dhcp6ParseError but nothing was raised (expected: "
               << msg << ")";
    }
    catch (const Dhcp4ParseError& ex) {
        EXPECT_EQ(msg, ex.what());
    }
    catch (...) {
        FAIL() << "Expected Dhcp6ParseError but something else was raised";
    }
}

// Check errors
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

    // case sensitivity
    testError("{ \"foo\": True }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10: Invalid character: T");
    testError("{ \"foo\": NULL  }",
              Parser4Context::PARSER_JSON,
              "<string>:1.10: Invalid character: N");

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
    testError("\"a\\u0062\"",
              Parser4Context::PARSER_JSON,
              "<string>:1.1-9: Unsupported unicode escape in \"a\\u0062\"");
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
}

};
