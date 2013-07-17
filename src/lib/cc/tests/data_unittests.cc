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

#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/assign/std/vector.hpp>
#include <climits>

#include <cc/data.h>

using namespace isc::data;

#include <sstream>
#include <iostream>
using std::oct;
#include <iomanip>
using std::setfill;
using std::setw;
using std::string;

namespace {
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

TEST(Element, TypeNameConversion) {
    EXPECT_EQ(Element::integer, Element::nameToType("integer"));
    EXPECT_EQ(Element::real, Element::nameToType("real"));
    EXPECT_EQ(Element::boolean, Element::nameToType("boolean"));
    EXPECT_EQ(Element::string, Element::nameToType("string"));
    EXPECT_EQ(Element::list, Element::nameToType("list"));
    EXPECT_EQ(Element::map, Element::nameToType("map"));
    EXPECT_EQ(Element::null, Element::nameToType("null"));
    EXPECT_EQ(Element::any, Element::nameToType("any"));
    EXPECT_THROW(Element::nameToType("somethingunknown"), TypeError);

    EXPECT_EQ("integer", Element::typeToName(Element::integer));
    EXPECT_EQ("real", Element::typeToName(Element::real));
    EXPECT_EQ("boolean", Element::typeToName(Element::boolean));
    EXPECT_EQ("string", Element::typeToName(Element::string));
    EXPECT_EQ("list", Element::typeToName(Element::list));
    EXPECT_EQ("map", Element::typeToName(Element::map));
    EXPECT_EQ("null", Element::typeToName(Element::null));
    EXPECT_EQ("any", Element::typeToName(Element::any));
    EXPECT_EQ("unknown", Element::typeToName((Element::types)123));
}

TEST(Element, from_and_to_json) {
    // a set of inputs that are the same when converted to json and
    // back to a string (tests for inputs that have equivalent, but
    // different string representations when converted back are below)
    ConstElementPtr el;
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
    sv.push_back("8.23");
    sv.push_back("123.456");
    sv.push_back("null");
    sv.push_back("-1");
    sv.push_back("-1.234");
    sv.push_back("-123.456");
    // We should confirm that our string handling is 8-bit clean.
    // At one point we were using char-length data and comparing to EOF,
    // which means that character '\xFF' would not parse properly.
    sv.push_back("\"\xFF\"");

    BOOST_FOREACH(const std::string& s, sv) {
        // test << operator, which uses Element::str()
        std::ostringstream stream;
        el = Element::fromJSON(s);
        stream << *el;
        EXPECT_EQ(s, stream.str());

        // test toWire(ostream), which should also be the same now
        std::ostringstream wire_stream;
        el->toWire(wire_stream);
        EXPECT_EQ(s, wire_stream.str());
    }

    // some parse errors
    try {
        Element::fromJSON("{1}");
    } catch (const isc::data::JSONError& pe) {
        std::string s = std::string(pe.what());
        EXPECT_EQ("String expected in <string>:1:3", s);
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
    sv.push_back("nul");
    sv.push_back("hello\"foobar\"");
    sv.push_back("\"foobar\"hello");
    sv.push_back("[]hello");
    sv.push_back("{}hello");
    // String not delimited correctly
    sv.push_back("\"hello");
    sv.push_back("hello\"");


    BOOST_FOREACH(std::string s, sv) {
        EXPECT_THROW(el = Element::fromJSON(s), isc::data::JSONError);
    }

    // some json specific format tests, here the str() output is
    // different from the string input
    EXPECT_EQ("100", Element::fromJSON("+100")->str());
    EXPECT_EQ("100", Element::fromJSON("1e2")->str());
    EXPECT_EQ("100", Element::fromJSON("+1e2")->str());
    EXPECT_EQ("-100", Element::fromJSON("-1e2")->str());

    EXPECT_NO_THROW({
       EXPECT_EQ("9223372036854775807", Element::fromJSON("9223372036854775807")->str());
    });
    EXPECT_NO_THROW({
       EXPECT_EQ("-9223372036854775808", Element::fromJSON("-9223372036854775808")->str());
    });
    EXPECT_THROW({
       EXPECT_NE("9223372036854775808", Element::fromJSON("9223372036854775808")->str());
    }, JSONError);

    EXPECT_EQ("0.01", Element::fromJSON("1e-2")->str());
    EXPECT_EQ("0.01", Element::fromJSON(".01")->str());
    EXPECT_EQ("-0.01", Element::fromJSON("-1e-2")->str());
    EXPECT_EQ("1.2", Element::fromJSON("1.2")->str());
    EXPECT_EQ("1", Element::fromJSON("1.0")->str());
    EXPECT_EQ("120", Element::fromJSON("1.2e2")->str());
    EXPECT_EQ("100", Element::fromJSON("1.0e2")->str());
    EXPECT_EQ("100", Element::fromJSON("1.0E2")->str());
    EXPECT_EQ("0.01", Element::fromJSON("1.0e-2")->str());
    EXPECT_EQ("0.012", Element::fromJSON("1.2e-2")->str());
    EXPECT_EQ("0.012", Element::fromJSON("1.2E-2")->str());
    EXPECT_EQ("null", Element::fromJSON("Null")->str());
    EXPECT_EQ("null", Element::fromJSON("NULL")->str());
    EXPECT_EQ("false", Element::fromJSON("False")->str());
    EXPECT_EQ("false", Element::fromJSON("FALSE")->str());
    EXPECT_EQ("true", Element::fromJSON("True")->str());
    EXPECT_EQ("true", Element::fromJSON("TRUE")->str());
    EXPECT_EQ("\"\"", Element::fromJSON("  \n \t \r \f \b \"\" \n \f \t \r \b")->str());
    EXPECT_EQ("{  }", Element::fromJSON("{  \n  \r \t  \b \f }")->str());
    EXPECT_EQ("[  ]", Element::fromJSON("[  \n  \r \f \t  \b  ]")->str());

    // number overflows
    EXPECT_THROW(Element::fromJSON("12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1.1e12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("-1.1e12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1e12345678901234567890")->str(), JSONError);
    EXPECT_THROW(Element::fromJSON("1e50000")->str(), JSONError);
    // number underflow
    // EXPECT_THROW(Element::fromJSON("1.1e-12345678901234567890")->str(), JSONError);

}

template <typename T>
void
testGetValueInt() {
    T el;
    int64_t i;
    int32_t i32;
    long l;
    long long ll;
    double d;
    bool b;
    std::string s;
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;

    el = Element::create(1);
    EXPECT_NO_THROW(el->intValue());
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);
    EXPECT_TRUE(el->getValue(i));
    EXPECT_FALSE(el->getValue(d));
    EXPECT_FALSE(el->getValue(b));
    EXPECT_FALSE(el->getValue(s));
    EXPECT_FALSE(el->getValue(v));
    EXPECT_FALSE(el->getValue(m));
    EXPECT_EQ(1, i);

    el = Element::create(9223372036854775807LL);
    EXPECT_NO_THROW(el->intValue());
    EXPECT_TRUE(el->getValue(i));
    EXPECT_EQ(9223372036854775807LL, i);

    ll = 9223372036854775807LL;
    el = Element::create(ll);
    EXPECT_NO_THROW(el->intValue());
    EXPECT_TRUE(el->getValue(i));
    EXPECT_EQ(ll, i);

    i32 = 2147483647L;
    el = Element::create(i32);
    EXPECT_NO_THROW(el->intValue());
    EXPECT_TRUE(el->getValue(i));
    EXPECT_EQ(i32, i);

    l = 2147483647L;
    el = Element::create(l);
    EXPECT_NO_THROW(el->intValue());
    EXPECT_TRUE(el->getValue(i));
    EXPECT_EQ(l, i);
}

template <typename T>
void
testGetValueDouble() {
    T el;
    int64_t i;
    double d;
    bool b;
    std::string s;
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;

    el = Element::create(1.1);
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_NO_THROW(el->doubleValue());
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);
    EXPECT_FALSE(el->getValue(i));
    EXPECT_TRUE(el->getValue(d));
    EXPECT_FALSE(el->getValue(b));
    EXPECT_FALSE(el->getValue(s));
    EXPECT_FALSE(el->getValue(v));
    EXPECT_FALSE(el->getValue(m));
    EXPECT_EQ(1.1, d);
}

template <typename T>
void
testGetValueBool() {
    T el;
    int64_t i;
    double d;
    bool b;
    std::string s;
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;

    el = Element::create(true);
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_NO_THROW(el->boolValue());
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);
    EXPECT_FALSE(el->getValue(i));
    EXPECT_FALSE(el->getValue(d));
    EXPECT_TRUE(el->getValue(b));
    EXPECT_FALSE(el->getValue(s));
    EXPECT_FALSE(el->getValue(v));
    EXPECT_FALSE(el->getValue(m));
    EXPECT_EQ(true, b);
}

template <typename T>
void
testGetValueString() {
    T el;
    int64_t i;
    double d;
    bool b;
    std::string s;
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;

    el = Element::create("foo");
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_NO_THROW(el->stringValue());
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_THROW(el->mapValue(), TypeError);
    EXPECT_FALSE(el->getValue(i));
    EXPECT_FALSE(el->getValue(d));
    EXPECT_FALSE(el->getValue(b));
    EXPECT_TRUE(el->getValue(s));
    EXPECT_FALSE(el->getValue(v));
    EXPECT_FALSE(el->getValue(m));
    EXPECT_EQ("foo", s);
}

template <typename T>
void
testGetValueList() {
    T el;
    int64_t i;
    double d;
    bool b;
    std::string s;
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;

    el = Element::createList();
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_NO_THROW(el->listValue());
    EXPECT_THROW(el->mapValue(), TypeError);
    EXPECT_FALSE(el->getValue(i));
    EXPECT_FALSE(el->getValue(d));
    EXPECT_FALSE(el->getValue(b));
    EXPECT_FALSE(el->getValue(s));
    EXPECT_TRUE(el->getValue(v));
    EXPECT_FALSE(el->getValue(m));
    EXPECT_EQ("[  ]", el->str());
}

template <typename T>
void
testGetValueMap() {
    T el;
    int64_t i;
    double d;
    bool b;
    std::string s;
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;

    el = Element::createMap();
    EXPECT_THROW(el->intValue(), TypeError);
    EXPECT_THROW(el->doubleValue(), TypeError);
    EXPECT_THROW(el->boolValue(), TypeError);
    EXPECT_THROW(el->stringValue(), TypeError);
    EXPECT_THROW(el->listValue(), TypeError);
    EXPECT_NO_THROW(el->mapValue());
    EXPECT_FALSE(el->getValue(i));
    EXPECT_FALSE(el->getValue(d));
    EXPECT_FALSE(el->getValue(b));
    EXPECT_FALSE(el->getValue(s));
    EXPECT_FALSE(el->getValue(v));
    EXPECT_TRUE(el->getValue(m));
    EXPECT_EQ("{  }", el->str());
}

TEST(Element, create_and_value_throws) {
    // this test checks whether elements throw exceptions if the
    // incorrect type is requested
    ElementPtr el;
    ConstElementPtr cel;
    int64_t i = 0;
    double d = 0.0;
    bool b = false;
    std::string s("asdf");
    std::vector<ConstElementPtr> v;
    std::map<std::string, ConstElementPtr> m;
    ConstElementPtr tmp;

    testGetValueInt<ElementPtr>();
    testGetValueInt<ConstElementPtr>();

    el = Element::create(1);
    i = 2;
    EXPECT_TRUE(el->setValue(i));
    EXPECT_EQ(2, el->intValue());
    EXPECT_FALSE(el->setValue(d));
    EXPECT_FALSE(el->setValue(b));
    EXPECT_FALSE(el->setValue(s));
    EXPECT_FALSE(el->setValue(v));
    EXPECT_FALSE(el->setValue(m));
    EXPECT_THROW(el->get(1), TypeError);
    EXPECT_THROW(el->set(1, el), TypeError);
    EXPECT_THROW(el->add(el), TypeError);
    EXPECT_THROW(el->remove(1), TypeError);
    EXPECT_THROW(el->size(), TypeError);
    EXPECT_THROW(el->get("foo"), TypeError);
    EXPECT_THROW(el->set("foo", el), TypeError);
    EXPECT_THROW(el->remove("foo"), TypeError);
    EXPECT_THROW(el->contains("foo"), TypeError);
    EXPECT_FALSE(el->find("foo", tmp));

    testGetValueDouble<ElementPtr>();
    testGetValueDouble<ConstElementPtr>();

    el = Element::create(1.1);
    d = 2.2;
    EXPECT_TRUE(el->setValue(d));
    EXPECT_EQ(2.2, el->doubleValue());
    EXPECT_FALSE(el->setValue(i));
    EXPECT_FALSE(el->setValue(b));
    EXPECT_FALSE(el->setValue(s));
    EXPECT_FALSE(el->setValue(v));
    EXPECT_FALSE(el->setValue(m));
    EXPECT_THROW(el->get(1), TypeError);
    EXPECT_THROW(el->set(1, el), TypeError);
    EXPECT_THROW(el->add(el), TypeError);
    EXPECT_THROW(el->remove(1), TypeError);
    EXPECT_THROW(el->size(), TypeError);
    EXPECT_THROW(el->get("foo"), TypeError);
    EXPECT_THROW(el->set("foo", el), TypeError);
    EXPECT_THROW(el->remove("foo"), TypeError);
    EXPECT_THROW(el->contains("foo"), TypeError);
    EXPECT_FALSE(el->find("foo", tmp));

    testGetValueBool<ElementPtr>();
    testGetValueBool<ConstElementPtr>();

    el = Element::create(true);
    b = false;
    EXPECT_TRUE(el->setValue(b));
    EXPECT_FALSE(el->boolValue());
    EXPECT_FALSE(el->setValue(i));
    EXPECT_FALSE(el->setValue(d));
    EXPECT_FALSE(el->setValue(s));
    EXPECT_FALSE(el->setValue(v));
    EXPECT_FALSE(el->setValue(m));
    EXPECT_THROW(el->get(1), TypeError);
    EXPECT_THROW(el->set(1, el), TypeError);
    EXPECT_THROW(el->add(el), TypeError);
    EXPECT_THROW(el->remove(1), TypeError);
    EXPECT_THROW(el->size(), TypeError);
    EXPECT_THROW(el->get("foo"), TypeError);
    EXPECT_THROW(el->set("foo", el), TypeError);
    EXPECT_THROW(el->remove("foo"), TypeError);
    EXPECT_THROW(el->contains("foo"), TypeError);
    EXPECT_FALSE(el->find("foo", tmp));

    testGetValueString<ElementPtr>();
    testGetValueString<ConstElementPtr>();

    el = Element::create("foo");
    s = "bar";
    EXPECT_TRUE(el->setValue(s));
    EXPECT_EQ("bar", el->stringValue());
    EXPECT_FALSE(el->setValue(i));
    EXPECT_FALSE(el->setValue(b));
    EXPECT_FALSE(el->setValue(d));
    EXPECT_FALSE(el->setValue(v));
    EXPECT_FALSE(el->setValue(m));
    EXPECT_THROW(el->get(1), TypeError);
    EXPECT_THROW(el->set(1, el), TypeError);
    EXPECT_THROW(el->add(el), TypeError);
    EXPECT_THROW(el->remove(1), TypeError);
    EXPECT_THROW(el->size(), TypeError);
    EXPECT_THROW(el->get("foo"), TypeError);
    EXPECT_THROW(el->set("foo", el), TypeError);
    EXPECT_THROW(el->remove("foo"), TypeError);
    EXPECT_THROW(el->contains("foo"), TypeError);
    EXPECT_FALSE(el->find("foo", tmp));

    testGetValueList<ElementPtr>();
    testGetValueList<ConstElementPtr>();

    el = Element::createList();
    v.push_back(Element::create(1));
    EXPECT_TRUE(el->setValue(v));
    EXPECT_EQ("[ 1 ]", el->str());

    testGetValueMap<ElementPtr>();
    testGetValueMap<ConstElementPtr>();

    el = Element::createMap();
    EXPECT_NO_THROW(el->set("foo", Element::create("bar")));
    EXPECT_EQ("{ \"foo\": \"bar\" }", el->str());
}

// Helper for escape check; it puts the given string in a StringElement,
// then checks for the following conditions:
// stringValue() must be same as input
// toJSON() output must be escaped
// fromJSON() on the previous output must result in original input
void
escapeHelper(const std::string& input, const std::string& expected) {
    StringElement str_element = StringElement(input);
    EXPECT_EQ(input, str_element.stringValue());
    std::stringstream os;
    str_element.toJSON(os);
    EXPECT_EQ(expected, os.str());
    ElementPtr str_element2 = Element::fromJSON(os.str());
    EXPECT_EQ(str_element.stringValue(), str_element2->stringValue());
}

TEST(Element, escape) {
    // Test whether quotes are escaped correctly when creating direct
    // String elements.
    escapeHelper("foo\"bar", "\"foo\\\"bar\"");
    escapeHelper("foo\\bar", "\"foo\\\\bar\"");
    escapeHelper("foo\bbar", "\"foo\\bbar\"");
    escapeHelper("foo\fbar", "\"foo\\fbar\"");
    escapeHelper("foo\nbar", "\"foo\\nbar\"");
    escapeHelper("foo\rbar", "\"foo\\rbar\"");
    escapeHelper("foo\tbar", "\"foo\\tbar\"");
    // Bad escapes
    EXPECT_THROW(Element::fromJSON("\\a"), JSONError);
    EXPECT_THROW(Element::fromJSON("\\"), JSONError);
    // Can't have escaped quotes outside strings
    EXPECT_THROW(Element::fromJSON("\\\"\\\""), JSONError);
    // Inside strings is OK
    EXPECT_NO_THROW(Element::fromJSON("\"\\\"\\\"\""));
    // A whitespace test
    EXPECT_NO_THROW(Element::fromJSON("\"  \n  \r \t \f  \n \n    \t\""));
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
    EXPECT_EQ(32, el->get(2)->intValue());

    // boundary condition tests for set()
    el->set(2, Element::create(0)); // update the last entry of the list
    EXPECT_EQ(0, el->get(2)->intValue());
    // attempt of set beyond the range of list should trigger an exception.
    EXPECT_ANY_THROW(el->set(3, Element::create(0)));
}

TEST(Element, MapElement) {
    // this function checks the specific functions for ListElements
    ElementPtr el = Element::fromJSON("{ \"name\": \"foo\", \"value1\": \"bar\", \"value2\": { \"number\": 42 } }");
    ConstElementPtr el2;

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
    EXPECT_EQ("bar", el2->stringValue());
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

    // A one-byte longer tag should still be allowed
    long_maptag.push_back('f');
    el = Element::fromJSON("{ \"" + long_maptag + "\": \"bar\"}");
    el->set(long_maptag, Element::create("bar"));
    EXPECT_EQ("bar", el->find(long_maptag)->stringValue());

}

TEST(Element, to_and_from_wire) {
    // Wire format is now plain JSON.
    EXPECT_EQ("1", Element::create(1)->toWire());
    EXPECT_EQ("1.1", Element::create(1.1)->toWire());
    EXPECT_EQ("true", Element::create(true)->toWire());
    EXPECT_EQ("false", Element::create(false)->toWire());
    EXPECT_EQ("null", Element::create()->toWire());
    EXPECT_EQ("\"a string\"", Element::create("a string")->toWire());
    EXPECT_EQ("[ \"a\", \"list\" ]", Element::fromJSON("[ \"a\", \"list\" ]")->toWire());
    EXPECT_EQ("{ \"a\": \"map\" }", Element::fromJSON("{ \"a\": \"map\" }")->toWire());

    EXPECT_EQ("1", Element::fromWire("1")->str());

    std::stringstream ss;
    ss << "1";
    EXPECT_EQ("1", Element::fromWire(ss, 1)->str());

    // Some malformed JSON input
    EXPECT_THROW(Element::fromJSON("{ "), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\" "), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\": "), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\": \"b\""), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\": {"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\": {}"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\": []"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\": [ }"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{\":"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("]"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("[ 1, 2, }"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("[ 1, 2, {}"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("[ 1, 2, { ]"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("[ "), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{{}}"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{[]}"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("{ \"a\", \"b\" }"), isc::data::JSONError);
    EXPECT_THROW(Element::fromJSON("[ \"a\": \"b\" ]"), isc::data::JSONError);
}

ConstElementPtr
efs(const std::string& str) {
    return (Element::fromJSON(str));
}

TEST(Element, equals) {
    EXPECT_EQ(*efs("1"), *efs("1"));
    EXPECT_NE(*efs("1"), *efs("2"));
    EXPECT_NE(*efs("1"), *efs("\"1\""));
    EXPECT_NE(*efs("1"), *efs("[]"));
    EXPECT_NE(*efs("1"), *efs("True"));
    EXPECT_NE(*efs("1"), *efs("{}"));

    EXPECT_EQ(*efs("1.1"), *efs("1.1"));
    EXPECT_NE(*efs("1.0"), *efs("1"));
    EXPECT_NE(*efs("1.1"), *efs("\"1\""));
    EXPECT_NE(*efs("1.1"), *efs("[]"));
    EXPECT_NE(*efs("1.1"), *efs("True"));
    EXPECT_NE(*efs("1.1"), *efs("{}"));

    EXPECT_EQ(*efs("True"), *efs("True"));
    EXPECT_NE(*efs("True"), *efs("False"));
    EXPECT_NE(*efs("True"), *efs("1"));
    EXPECT_NE(*efs("True"), *efs("\"1\""));
    EXPECT_NE(*efs("True"), *efs("[]"));
    EXPECT_NE(*efs("True"), *efs("{}"));

    EXPECT_EQ(*efs("\"foo\""), *efs("\"foo\""));
    EXPECT_NE(*efs("\"foo\""), *efs("\"bar\""));
    EXPECT_NE(*efs("\"foo\""), *efs("1"));
    EXPECT_NE(*efs("\"foo\""), *efs("\"1\""));
    EXPECT_NE(*efs("\"foo\""), *efs("True"));
    EXPECT_NE(*efs("\"foo\""), *efs("[]"));
    EXPECT_NE(*efs("\"foo\""), *efs("{}"));

    EXPECT_EQ(*efs("[]"), *efs("[]"));
    EXPECT_EQ(*efs("[ 1, 2, 3 ]"), *efs("[ 1, 2, 3 ]"));
    EXPECT_EQ(*efs("[ \"a\", [ True, 1], 2.2 ]"), *efs("[ \"a\", [ True, 1], 2.2 ]"));
    EXPECT_NE(*efs("[ \"a\", [ True, 1], 2.2 ]"), *efs("[ \"a\", [ True, 2], 2.2 ]"));
    EXPECT_NE(*efs("[]"), *efs("[1]"));
    EXPECT_NE(*efs("[]"), *efs("1"));
    EXPECT_NE(*efs("[]"), *efs("\"1\""));
    EXPECT_NE(*efs("[]"), *efs("{}"));

    EXPECT_EQ(*efs("{}"), *efs("{}"));
    EXPECT_EQ(*efs("{ \"foo\": \"bar\" }"), *efs("{ \"foo\": \"bar\" }"));
    EXPECT_EQ(*efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }"), *efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }"));
    EXPECT_NE(*efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }"), *efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar2\" } }"));
    EXPECT_NE(*efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\" ], \"item3\": { \"foo\": \"bar\" } }"), *efs("{ \"item1\": 1, \"item2\": [ \"a\", \"list\", 1 ], \"item3\": { \"foo\": \"bar\" } }"));
    EXPECT_NE(*efs("{ \"foo\": \"bar\" }"), *efs("1"));
    EXPECT_NE(*efs("{ \"foo\": \"bar\" }"), *efs("\"1\""));
    EXPECT_NE(*efs("{ \"foo\": \"bar\" }"), *efs("[]"));
    EXPECT_NE(*efs("{ \"foo\": \"bar\" }"), *efs("{}"));
    EXPECT_NE(*efs("{ \"foo\": \"bar\" }"), *efs("{ \"something\": \"different\" }"));

    EXPECT_EQ(*efs("null"), *Element::create());
}

TEST(Element, removeIdentical) {
    ElementPtr a = Element::createMap();
    ConstElementPtr b = Element::createMap();
    ConstElementPtr c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1 }");
    b = Element::fromJSON("{ \"a\": 1 }");
    c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::createMap();
    c = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 3 ] }");
    c = Element::fromJSON("{ \"b\": [ 1, 2 ] }");
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::createMap();
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    c = Element::createMap();
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": 2, \"c\": 3 }");
    b = Element::fromJSON("{ \"c\": 3, \"b\": 2 }");
    c = Element::fromJSON("{ \"a\": 1 }");
    removeIdentical(a, b);
    EXPECT_EQ(*a, *c);

    EXPECT_THROW(removeIdentical(Element::create(1), Element::create(2)), TypeError);
}

TEST(Element, constRemoveIdentical) {
    ConstElementPtr a = Element::createMap();
    ConstElementPtr b = Element::createMap();
    ConstElementPtr c = Element::createMap();
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": 1 }");
    b = Element::fromJSON("{ \"a\": 1 }");
    c = Element::createMap();
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::createMap();
    c = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    c = Element::createMap();
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 2 ] }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": [ 1, 3 ] }");
    c = Element::fromJSON("{ \"b\": [ 1, 2 ] }");
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::createMap();
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    c = Element::createMap();
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    EXPECT_EQ(*removeIdentical(a, b), *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": 2, \"c\": 3 }");
    b = Element::fromJSON("{ \"c\": 3, \"b\": 2 }");
    c = Element::fromJSON("{ \"a\": 1 }");
    EXPECT_EQ(*removeIdentical(a, b), *c);

    EXPECT_THROW(removeIdentical(Element::create(1), Element::create(2)),
                 TypeError);
}

TEST(Element, merge) {
    ElementPtr a = Element::createMap();
    ElementPtr b = Element::createMap();
    ConstElementPtr c = Element::createMap();
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("1");
    b = Element::createMap();
    EXPECT_THROW(merge(a, b), TypeError);

    a = Element::createMap();
    b = Element::fromJSON("{ \"a\": 1 }");
    c = Element::fromJSON("{ \"a\": 1 }");
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::createMap();
    b = Element::fromJSON("{ \"a\": 1 }");
    c = Element::fromJSON("{ \"a\": 1 }");
    merge(b, a);
    EXPECT_EQ(*b, *c);

    a = Element::fromJSON("{ \"a\": 1 }");
    b = Element::fromJSON("{ \"a\": 2 }");
    c = Element::fromJSON("{ \"a\": 2 }");
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1 }");
    b = Element::fromJSON("{ \"a\": 2 }");
    c = Element::fromJSON("{ \"a\": 1 }");
    merge(b, a);
    EXPECT_EQ(*b, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": { \"b\": \"d\" } }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    merge(b, a);
    EXPECT_EQ(*b, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": null }");
    c = Element::fromJSON("{  }");
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    b = Element::fromJSON("{ \"a\": null }");
    c = Element::fromJSON("{ \"a\": { \"b\": \"c\" } }");
    merge(b, a);
    EXPECT_EQ(*b, *c);

    // And some tests with multiple values
    a = Element::fromJSON("{ \"a\": 1, \"b\": true, \"c\": null }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": null, \"c\": \"a string\" }");
    c = Element::fromJSON("{ \"a\": 1, \"c\": \"a string\" }");
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": true, \"c\": null }");
    b = Element::fromJSON("{ \"a\": 1, \"b\": null, \"c\": \"a string\" }");
    c = Element::fromJSON("{ \"a\": 1, \"b\": true }");
    merge(b, a);
    EXPECT_EQ(*b, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": 2, \"c\": 3 }");
    b = Element::fromJSON("{ \"a\": 3, \"b\": 2, \"c\": 1 }");
    c = Element::fromJSON("{ \"a\": 3, \"b\": 2, \"c\": 1 }");
    merge(a, b);
    EXPECT_EQ(*a, *c);

    a = Element::fromJSON("{ \"a\": 1, \"b\": 2, \"c\": 3 }");
    b = Element::fromJSON("{ \"a\": 3, \"b\": 2, \"c\": 1 }");
    c = Element::fromJSON("{ \"a\": 1, \"b\": 2, \"c\": 3 }");
    merge(b, a);
    EXPECT_EQ(*b, *c);

}
}
