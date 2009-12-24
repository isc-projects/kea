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

TEST(Element, type) {
    // this tests checks whether the get_type() function returns the
    // correct type
    IntElement int_el = IntElement(1);
    EXPECT_EQ(int_el.get_type(), Element::integer);
    DoubleElement double_el = DoubleElement(1.0);
    EXPECT_EQ(double_el.get_type(), Element::real);
    BoolElement bool_el = BoolElement(true);
    EXPECT_EQ(bool_el.get_type(), Element::boolean);
    StringElement str_el = StringElement("foo");
    EXPECT_EQ(str_el.get_type(), Element::string);
    std::vector<ElementPtr> v;
    ListElement list_el = ListElement(v);
    EXPECT_EQ(list_el.get_type(), Element::list);
    std::map<std::string, ElementPtr> m;
    MapElement map_el = MapElement(m);
    EXPECT_EQ(map_el.get_type(), Element::map);
}

TEST(Element, str) {
    // this test checks whether the str() method returns the same
    // string that was used for creation
    ElementPtr el;
    std::vector<std::string> sv;

    sv.push_back("12");
    sv.push_back("1.1");
    sv.push_back("True");
    sv.push_back("False");
    sv.push_back("\"asdf\"");
    sv.push_back("[ 1, 2, 3, 4 ]");
    sv.push_back("{\"name\": \"foo\", \"value\": 47806}");

    BOOST_FOREACH(std::string s, sv) {
        el = Element::create_from_string(s);
        EXPECT_EQ(el->str(), s);
    }
}

TEST(Element, create_and_value_throws) {
    // this test checks whether elements throw exceptions if the
    // incorrect type is requested
    ElementPtr el;

    el = Element::create(1);
    EXPECT_THROW(el->double_value(), TypeError);
    EXPECT_THROW(el->bool_value(), TypeError);
    EXPECT_THROW(el->string_value(), TypeError);
    EXPECT_THROW(el->list_value(), TypeError);
    EXPECT_THROW(el->map_value(), TypeError);

    el = Element::create(1.1);
    EXPECT_THROW(el->int_value(), TypeError);
    EXPECT_THROW(el->bool_value(), TypeError);
    EXPECT_THROW(el->string_value(), TypeError);
    EXPECT_THROW(el->list_value(), TypeError);
    EXPECT_THROW(el->map_value(), TypeError);

    el = Element::create(true);
    EXPECT_THROW(el->int_value(), TypeError);
    EXPECT_THROW(el->double_value(), TypeError);
    EXPECT_THROW(el->string_value(), TypeError);
    EXPECT_THROW(el->list_value(), TypeError);
    EXPECT_THROW(el->map_value(), TypeError);

    el = Element::create("foo");
    EXPECT_THROW(el->int_value(), TypeError);
    EXPECT_THROW(el->double_value(), TypeError);
    EXPECT_THROW(el->bool_value(), TypeError);
    EXPECT_THROW(el->list_value(), TypeError);
    EXPECT_THROW(el->map_value(), TypeError);

    std::vector<ElementPtr> v;
    el = Element::create(v);
    EXPECT_THROW(el->int_value(), TypeError);
    EXPECT_THROW(el->double_value(), TypeError);
    EXPECT_THROW(el->bool_value(), TypeError);
    EXPECT_THROW(el->string_value(), TypeError);
    EXPECT_THROW(el->map_value(), TypeError);

    std::map<std::string, ElementPtr> m;
    el = Element::create(m);
    EXPECT_THROW(el->int_value(), TypeError);
    EXPECT_THROW(el->double_value(), TypeError);
    EXPECT_THROW(el->bool_value(), TypeError);
    EXPECT_THROW(el->string_value(), TypeError);
    EXPECT_THROW(el->list_value(), TypeError);

}

TEST(Element, ListElement) {
    // this function checks the specific functions for ListElements
    ElementPtr el = Element::create_from_string("[ 1, \"bar\", 3 ]");
    EXPECT_EQ(el->get(0)->int_value(), 1);
    EXPECT_EQ(el->get(1)->string_value(), "bar");
    EXPECT_EQ(el->get(2)->int_value(), 3);

    el->set(0, Element::create_from_string("\"foo\""));
    EXPECT_EQ(el->get(0)->string_value(), "foo");

    el->add(Element::create(47806));
    EXPECT_EQ(el->get(3)->int_value(), 47806);

    el->remove(1);
    el->remove(1);
    EXPECT_EQ(el->str(), "[ \"foo\", 47806 ]");

    // hmm, it errors on EXPECT_THROW(el->get(3), std::out_of_range)
    EXPECT_ANY_THROW(el->get(3));

    el->add(Element::create(32));
    EXPECT_EQ(el->get(2)->int_value(), 32);
}

TEST(Element, MapElement) {
    // this function checks the specific functions for ListElements
    ElementPtr el = Element::create_from_string("{ \"name\": \"foo\", \"value1\": \"bar\", \"value2\": { \"number\": 42 } }");

    EXPECT_EQ(el->get("name")->string_value(), "foo");
    EXPECT_EQ(el->get("value2")->get_type(), Element::map);

    EXPECT_TRUE(is_null(el->get("value3")));

    el->set("value3", Element::create(47806));
    EXPECT_EQ(el->get("value3")->int_value(), 47806);

    el->remove("value3");
    EXPECT_TRUE(is_null(el->get("value3")));

    EXPECT_EQ(el->find("value2/number")->int_value(), 42);
   
    EXPECT_EQ(el->find("value1")->string_value(), "bar");
    EXPECT_EQ(el->find("value1/")->string_value(), "bar");
}

