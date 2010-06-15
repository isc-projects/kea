// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/assign/std/vector.hpp>

#include <data.h>

using namespace isc::data;

#include <iostream>
using std::oct;
#include <iomanip>
using std::setfill;
using std::setw;
using std::string;

TEST(Element, type) {
    // this tests checks whether the getType() function returns the
    // correct type
    IntElement int_el = IntElement(1);
    EXPECT_EQ(int_el.getType(), Element::integer);
    DoubleElement double_el = DoubleElement(1.0);
    EXPECT_EQ(double_el.getType(), Element::real);
    BoolElement bool_el = BoolElement(true);
    EXPECT_EQ(bool_el.getType(), Element::boolean);
    StringElement str_el = StringElement("foo");
    EXPECT_EQ(str_el.getType(), Element::string);
    ListElement list_el = ListElement();
    EXPECT_EQ(list_el.getType(), Element::list);
    MapElement map_el = MapElement();
    EXPECT_EQ(map_el.getType(), Element::map);

}

TEST(Element, from_and_to_json) {
    // this test checks whether the str() method returns the same
    // string that was used for creation
    ElementPtr el;
    std::vector<std::string> sv;

    sv.push_back("12");
    sv.push_back("1.1");
    sv.push_back("true");
    sv.push_back("false");
    sv.push_back("\"asdf\"");
    sv.push_back("null");
    sv.push_back("[ 1, 2, 3, 4 ]");
    sv.push_back("{ \"name\": \"foo\", \"value\": 47806 }");
    sv.push_back("[ { \"a\": 1, \"b\": \"c\" }, { \"a\": 2, \"b\": \"d\" } ]");

    BOOST_FOREACH(std::string s, sv) {
        // also test << operator, which uses Element::str()
        std::ostringstream stream;
        el = Element::fromJSON(s);
        stream << el;
        EXPECT_EQ(stream.str(), s);
    }

    // some parse errors
    try {
        Element::fromJSON("{1}");
    } catch (isc::data::JSONError pe) {
        std::string s = std::string(pe.what());
        EXPECT_EQ(s, "String expected in <string>:1:3");
    }
    
    sv.clear();
    sv.push_back("{1}");
    //ElementPtr ep = Element::fromJSON("\"aaa\nbbb\"err");
    //std::cout << ep << std::endl;
    sv.push_back("\n\nTru");
    sv.push_back("{ \n \"aaa\nbbb\"err:");
    sv.push_back("{ \t\n \"aaa\nbbb\"\t\n\n:\n True, \"\\\"");
    sv.push_back("{ \"a\": None}");
    sv.push_back("");
    BOOST_FOREACH(std::string s, sv) {
        
        EXPECT_THROW(el = Element::fromJSON(s), isc::data::JSONError);
    }

    // some json specific format tests, here the str() output is
    // different from the string input
    EXPECT_EQ("100", Element::fromJSON("1e2")->str());
    EXPECT_EQ("0.01", Element::fromJSON("1e-2")->str());
    EXPECT_EQ("1.2", Element::fromJSON("1.2")->str());
    EXPECT_EQ("1", Element::fromJSON("1.0")->str());
    EXPECT_EQ("120", Element::fromJSON("1.2e2")->str());
    EXPECT_EQ("100", Element::fromJSON("1.0e2")->str());
    EXPECT_EQ("0.01", Element::fromJSON("1.0e-2")->str());
    EXPECT_EQ("0.012", Element::fromJSON("1.2e-2")->str());

    EXPECT_THROW(Element::fromJSON("12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1.12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1.1e12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1e12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1e50000")->str(), JSONError);

}

TEST(Element, create_and_value_throws) {
    // this test checks whether elements throw exceptions if the
    // incorrect type is requested
    ElementPtr el;

    el = Element::create(1);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);

    el = Element::create(1.1);
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);

    el = Element::create(true);
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);

    el = Element::create("foo");
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);

    el = Element::createList();
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);

    el = Element::createMap();
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);

}

TEST(Element, ListElement) {
    // this function checks the specific functions for ListElements
    ElementPtr el = Element::fromJSON("[ 1, \"bar\", 3 ]");
    EXPECT_EQ(el->get(0)->intValue(), 1);
    EXPECT_EQ(el->get(1)->stringValue(), "bar");
    EXPECT_EQ(el->get(2)->intValue(), 3);

    el->set(0, Element::fromJSON("\"foo\""));
    EXPECT_EQ(el->get(0)->stringValue(), "foo");

    el->add(Element::create(47806));
    EXPECT_EQ(el->get(3)->intValue(), 47806);

    el->remove(1);
    el->remove(1);
    EXPECT_EQ(el->str(), "[ \"foo\", 47806 ]");

    // hmm, it errors on EXPECT_THROW(el->get(3), std::out_of_range)
    EXPECT_ANY_THROW(el->get(3));

    el->add(Element::create(32));
    EXPECT_EQ(el->get(2)->intValue(), 32);
}

namespace {
const string long_maptag("0123456789abcdef1123456789abcdef2123456789abcdef"
                         "3123456789abcdef4123456789abcdef5123456789abcdef"
                         "6123456789abcdef7123456789abcdef8123456789abcdef"
                         "9123456789abcdefa123456789abcdefb123456789abcdef"
                         "c123456789abcdefd123456789abcdefe123456789abcdef"
                         "f123456789abcdef");
}

TEST(Element, MapElement) {
    // this function checks the specific functions for ListElements
    ElementPtr el = Element::fromJSON("{ \"name\": \"foo\", \"value1\": \"bar\", \"value2\": { \"number\": 42 } }");
    ElementPtr el2;
    
    EXPECT_EQ(el->get("name")->stringValue(), "foo");
    EXPECT_EQ(el->get("value2")->getType(), Element::map);

    EXPECT_TRUE(isNull(el->get("value3")));

    el->set("value3", Element::create(47806));
    EXPECT_EQ(el->get("value3")->intValue(), 47806);

    el->remove("value3");
    EXPECT_TRUE(isNull(el->get("value3")));

    EXPECT_EQ(el->find("value2/number")->intValue(), 42);
    EXPECT_TRUE(isNull(el->find("value2/nothing/")));
   
    EXPECT_EQ(el->find("value1")->stringValue(), "bar");
    EXPECT_EQ(el->find("value1/")->stringValue(), "bar");
    
    EXPECT_TRUE(el->find("value1", el2));
    EXPECT_FALSE(el->find("name/error", el2));

    // A map element whose (only) element has the maximum length of tag.
    string long_maptag("0123456789abcdef1123456789abcdef2123456789abcdef"
                       "3123456789abcdef4123456789abcdef5123456789abcdef"
                       "6123456789abcdef7123456789abcdef8123456789abcdef"
                       "9123456789abcdefa123456789abcdefb123456789abcdef"
                       "c123456789abcdefd123456789abcdefe123456789abcdef"
                       "f123456789abcde");
    
    EXPECT_EQ(255, long_maptag.length()); // check prerequisite
    el = Element::fromJSON("{ \"" + long_maptag + "\": \"bar\"}");
    EXPECT_EQ("bar", el->find(long_maptag)->stringValue());

    el = Element::createMap();
    el->set(long_maptag, Element::create("bar"));
    EXPECT_EQ("bar", el->find(long_maptag)->stringValue());

    // A one-byte longer tag should trigger an exception.
    long_maptag.push_back('f');
    EXPECT_THROW(Element::fromJSON("{ \"" + long_maptag +
                                           "\": \"bar\"}"),
                 JSONError);

    EXPECT_THROW(el->set(long_maptag, Element::create("bar")), TypeError);

}

TEST(Element, to_and_from_wire) {
    // Wire format is now plain JSON.
    ElementPtr el;
    EXPECT_EQ("1", Element::create(1)->toWire());
    EXPECT_EQ("1.1", Element::create(1.1)->toWire());
    EXPECT_EQ("true", Element::create(true)->toWire());
    EXPECT_EQ("false", Element::create(false)->toWire());
    EXPECT_EQ("null", Element::create()->toWire());
    EXPECT_EQ("\"a string\"", Element::create("a string")->toWire());
    EXPECT_EQ("[ \"a\", \"list\" ]", Element::fromJSON("[ \"a\", \"list\" ]")->toWire());
    EXPECT_EQ("{ \"a\": \"map\" }", Element::fromJSON("{ \"a\": \"map\" }")->toWire());

    EXPECT_EQ("1", Element::fromWire("1")->str());
}

ElementPtr efs(const std::string& str) {
    return Element::fromJSON(str);
}

TEST(Element, equals) {
    // why does EXPECT_EQ not work?
    EXPECT_TRUE(efs("1") == efs("1"));
    EXPECT_FALSE(efs("1") == efs("2"));
    EXPECT_FALSE(efs("1") == efs("\"1\""));
    EXPECT_FALSE(efs("1") == efs("[]"));
    EXPECT_FALSE(efs("1") == efs("True"));
    EXPECT_FALSE(efs("1") == efs("{}"));

    EXPECT_TRUE(efs("1.1") == efs("1.1"));
    EXPECT_FALSE(efs("1.0") == efs("1"));
    EXPECT_FALSE(efs("1.1") == efs("\"1\""));
    EXPECT_FALSE(efs("1.1") == efs("[]"));
    EXPECT_FALSE(efs("1.1") == efs("True"));
    EXPECT_FALSE(efs("1.1") == efs("{}"));

    EXPECT_TRUE(efs("True") == efs("True"));
    EXPECT_FALSE(efs("True") == efs("False"));
    EXPECT_FALSE(efs("True") == efs("1"));
    EXPECT_FALSE(efs("True") == efs("\"1\""));
    EXPECT_FALSE(efs("True") == efs("[]"));
    EXPECT_FALSE(efs("True") == efs("{}"));

    EXPECT_TRUE(efs("\"foo\"") == efs("\"foo\""));
    EXPECT_FALSE(efs("\"foo\"") == efs("\"bar\""));
    EXPECT_FALSE(efs("\"foo\"") == efs("1"));
    EXPECT_FALSE(efs("\"foo\"") == efs("\"1\""));
    EXPECT_FALSE(efs("\"foo\"") == efs("True"));
    EXPECT_FALSE(efs("\"foo\"") == efs("[]"));
    EXPECT_FALSE(efs("\"foo\"") == efs("{}"));

    EXPECT_TRUE(efs("[]") == efs("[]"));
    EXPECT_TRUE(efs("[ 1, 2, 3 ]") == efs("[ 1, 2, 3 ]"));
    EXPECT_TRUE(efs("[ \"a\", [ True, 1], 2.2 ]") == efs("[ \"a\", [ True, 1], 2.2 ]"));
    EXPECT_FALSE(efs("[ \"a\", [ True, 1], 2.2 ]") == efs("[ \"a\", [ True, 2], 2.2 ]"));
    EXPECT_FALSE(efs("[]") == efs("[1]"));
    EXPECT_FALSE(efs("[]") == efs("1"));
    EXPECT_FALSE(efs("[]") == efs("\"1\""));
    EXPECT_FALSE(efs("[]") == efs("{}"));

    EXPECT_TRUE(efs("{}") == efs("{}"));
    EXPECT_TRUE(efs("{ \"foo\": \"bar\" }") == efs("{ \"foo\": \"bar\" }"));
    EXPECT_TRUE(efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }") == efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }"));
    EXPECT_FALSE(efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }") == efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar2\" } }"));
    EXPECT_FALSE(efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }") == efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\", 1 ], \"item3\": { \"foo\": \"bar\" } }"));
    EXPECT_FALSE(efs("{ \"foo\": \"bar\" }") == efs("1"));
    EXPECT_FALSE(efs("{ \"foo\": \"bar\" }") == efs("\"1\""));
    EXPECT_FALSE(efs("{ \"foo\": \"bar\" }") == efs("[]"));
    EXPECT_FALSE(efs("{ \"foo\": \"bar\" }") == efs("{}"));
}

TEST(Element, removeIdentical) {
    ElementPtr a = Element::createMap();
    ElementPtr b = Element::createMap();
    ElementPtr c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": 1 }");
    b = Element::fromJSON("{ \"a\": 1 }");
    c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::createMap();
    c = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 3 ] }");
    c = Element::fromJSON("{ \"b\": [ 1, 2 ] }");
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::createMap();
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    removeIdentical(a, b);
    EXPECT_TRUE(a == c);
}

TEST(Element, merge)
{
    ElementPtr a = Element::createMap();
    ElementPtr b = Element::createMap();
    ElementPtr c = Element::createMap();
    merge(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("1");
    b = Element::createMap();
    EXPECT_THROW(merge(a, b), TypeError);

    a = Element::createMap();
    b = Element::fromJSON("{ \"a\": 1 }");
    c = Element::fromJSON("{ \"a\": 1 }");
    merge(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": 1 }");
    b = Element::fromJSON("{ \"a\": 2 }");
    c = Element::fromJSON("{ \"a\": 2 }");
    merge(a, b);
    EXPECT_TRUE(a == c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    merge(a, b);
    EXPECT_TRUE(a == c);

}
