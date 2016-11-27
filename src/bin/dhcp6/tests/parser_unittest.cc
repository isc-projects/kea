// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <cc/data.h>
#include <dhcp6/parser_context.h>

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

void testParser(const std::string& txt, Parser6Context::ParserType parser_type) {
    ElementPtr reference_json;
    ConstElementPtr test_json;

    ASSERT_NO_THROW(reference_json = Element::fromJSON(txt, true));
    ASSERT_NO_THROW({
            try {
        Parser6Context ctx;
        test_json = ctx.parseString(txt, parser_type);
            } catch (const std::exception &e) {
                cout << "EXCEPTION: " << e.what() << endl;
                throw;
            }

    });

    // Now compare if both representations are the same.
    compareJSON(reference_json, test_json);
}

void testParser2(const std::string& txt, Parser6Context::ParserType parser_type) {
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
    /// @todo: Implement actual validation here. since the original
    /// Element::fromJSON does not support several comment types, we don't
    /// have anything to compare with.
    /// std::cout << "Original text:" << txt << endl;
    /// std::cout << "Parsed text  :" << test_json->str() << endl;
}

TEST(ParserTest, mapInMap) {
    string txt = "{ \"xyzzy\": { \"foo\": 123, \"baz\": 456 } }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, listInList) {
    string txt = "{ \"countries\": [ [ \"Britain\", \"Wales\", \"Scotland\" ], "
                                    "[ \"Pomorze\", \"Wielkopolska\", \"Tatry\"] ] }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, nestedMaps) {
    string txt = "{ \"europe\": { \"UK\": { \"London\": { \"street\": \"221B Baker\" }}}}";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, nestedLists) {
    string txt = "{ \"unity\": [ \"half\", [ \"quarter\", [ \"eighth\", [ \"sixteenth\" ]]]] }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, listsInMaps) {
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelguese\" ], "
                    "\"cygnus\": [ \"deneb\", \"albireo\"] } }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, mapsInLists) {
    string txt = "{ \"solar-system\": [ { \"body\": \"earth\", \"gravity\": 1.0 },"
                                      " { \"body\": \"mars\", \"gravity\": 0.376 } ] }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, types) {
    string txt = "{ \"string\": \"foo\","
                   "\"integer\": 42,"
                   "\"boolean\": true,"
                   "\"map\": { \"foo\": \"bar\" },"
                   "\"list\": [ 1, 2, 3 ],"
                   "\"null\": null }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
}

TEST(ParserTest, keywordJSON) {
    string txt = "{ \"name\": \"user\","
                   "\"type\": \"password\","
                   "\"user\": \"name\","
                   "\"password\": \"type\" }";
    testParser(txt, Parser6Context::PARSER_GENERIC_JSON);
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
     testParser2(txt, Parser6Context::PARSER_DHCP6);
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
    testParser2(txt, Parser6Context::PARSER_DHCP6);
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
    testParser2(txt, Parser6Context::PARSER_DHCP6);
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
    testParser2(txt, Parser6Context::PARSER_DHCP6);
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
    testParser2(txt, Parser6Context::PARSER_DHCP6);
}


void testFile(const std::string& fname, bool print) {
    ElementPtr reference_json;
    ConstElementPtr test_json;

    cout << "Attempting to load file " << fname << endl;

    EXPECT_NO_THROW(reference_json = Element::fromJSONFile(fname, true));

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

    compareJSON(reference_json, test_json, print);


}

// This test loads all available existing files. Each config is loaded
// twice: first with the existing Element::fromJSONFile() and then
// the second time with Parser6. Both JSON trees are then compared.
TEST(ParserTest, file) {
    vector<string> configs;
    configs.push_back("advanced.json");
    configs.push_back("backends.json");
    configs.push_back("classify.json");
    configs.push_back("dhcpv4-over-dhcpv6.json");
    configs.push_back("duid.json");
    configs.push_back("hooks.json");
    configs.push_back("leases-expiration.json");
    configs.push_back("multiple-options.json");
    configs.push_back("mysql-reservations.json");
    configs.push_back("pgsql-reservations.json");
    configs.push_back("reservations.json");
    configs.push_back("several-subnets.json");
    configs.push_back("simple.json");
    configs.push_back("stateless.json");

    for (int i = 0; i<configs.size(); i++) {
        testFile(string(CFG_EXAMPLES) + "/" + configs[i], false);
    }
}

void testError(const std::string& txt,
               Parser6Context::ParserType parser_type,
               const std::string& msg)
{
    try {
        Parser6Context ctx;
        ConstElementPtr parsed = ctx.parseString(txt, parser_type);
        FAIL() << "Expected Dhcp6ParseError but nothing was raised";
    }
    catch (const Dhcp6ParseError& ex) {
        EXPECT_EQ(msg, ex.what());
    }
    catch (...) {
        FAIL() << "Expected Dhcp6ParseError but something else was raised";
    }
}

// Check lexer errors
TEST(ParserTest, lexerErrors) {
    testError("",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:1.1: syntax error, unexpected end of file, "
              "expecting {");
    testError(" ",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:1.2: syntax error, unexpected end of file, "
              "expecting {");
    testError("\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting {");
    testError("# nothing\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting {");
    testError(" #\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting {");
    testError("// nothing\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting {");
    testError("/* nothing */\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:2.1: syntax error, unexpected end of file, "
              "expecting {");
    testError("/* no\nthing */\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:3.1: syntax error, unexpected end of file, "
              "expecting {");
    testError("/* no\nthing */\n\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "<string>:4.1: syntax error, unexpected end of file, "
              "expecting {");
    testError("/* nothing\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "Comment not closed. (/* in line 1");
    fprintf(stderr, "got 124?\n");
    testError("/**/\n\n\n/* nothing\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "Comment not closed. (/* in line 4");
    testError("<?\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "Directive not closed.");
    testError("<?include\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "Directive not closed.");
    string file = string(CFG_EXAMPLES) + "/" + "stateless.json";
    fprintf(stderr, "doing include\n");
    testError("<?include \"" + file + "\"\n",
              Parser6Context::PARSER_GENERIC_JSON,
              "Directive not closed.");
}

};
