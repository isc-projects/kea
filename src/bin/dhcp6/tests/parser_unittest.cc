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

void compareJSON(ConstElementPtr a, ConstElementPtr b) {
    std::cout << a->str() << std::endl;
    std::cout << b->str() << std::endl;
    EXPECT_EQ(a->str(), b->str());
}

void testParser(const std::string& txt) {
    ElementPtr reference_json;
    ConstElementPtr test_json;

    EXPECT_NO_THROW(reference_json = Element::fromJSON(txt, true));
    EXPECT_NO_THROW({
        Parser6Context ctx;
        test_json = ctx.parseString(txt);
    });

    // Now compare if both representations are the same.
    compareJSON(reference_json, test_json);
}

TEST(ParserTest, mapInMap) {
    string txt = "{ \"Dhcp6\": { \"foo\": 123, \"baz\": 456 } }";
    testParser(txt);
}

TEST(ParserTest, listInList) {
    string txt = "{ \"countries\": [ [ \"Britain\", \"Wales\", \"Scotland\" ], "
                                    "[ \"Pomorze\", \"Wielkopolska\", \"Tatry\"] ] }";
    testParser(txt);
}

TEST(ParserTest, nestedMaps) {
    string txt = "{ \"europe\": { \"UK\": { \"London\": { \"street\": \"221B Baker\" }}}}";
    testParser(txt);
}

TEST(ParserTest, nestedLists) {
    string txt = "{ \"unity\": [ \"half\", [ \"quarter\", [ \"eighth\", [ \"sixteenth\" ]]]] }";
    testParser(txt);
}

TEST(ParserTest, listsInMaps) {
    string txt = "{ \"constellations\": { \"orion\": [ \"rigel\", \"betelguese\" ], "
                    "\"cygnus\": [ \"deneb\", \"albireo\"] } }";
    testParser(txt);
}

TEST(ParserTest, mapsInLists) {
    string txt = "{ \"solar-system\": [ { \"name\": \"earth\", \"gravity\": 1.0 },"
                                      " { \"name\": \"mars\", \"gravity\": 0.376 } ] }";
    testParser(txt);
}

TEST(ParserTest, types) {
    string txt = "{ \"string\": \"foo\","
                   "\"integer\": 42,"
                   "\"boolean\": true,"
                   "\"map\": { \"foo\": \"bar\" },"
                   "\"list\": [ 1, 2, 3 ],"
                   "\"null\": null }";
    testParser(txt);
}

};
