// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/classify.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;

// Trivial test for now as ClientClass is a std::string.
TEST(ClassifyTest, ClientClass) {

    ClientClass x("foo");
    EXPECT_EQ("foo", x);

    x = "baz";
    EXPECT_EQ("baz", x);
}

// Checks if ClientClasses object is able to store classes' names and then
// properly return values of contains() method.
TEST(ClassifyTest, ClientClasses) {
    ClientClasses classes;

    EXPECT_FALSE(classes.contains(""));
    EXPECT_FALSE(classes.contains("alpha"));
    EXPECT_FALSE(classes.contains("beta"));
    EXPECT_FALSE(classes.contains("gamma"));
    classes.insert("beta");
    EXPECT_FALSE(classes.contains(""));
    EXPECT_FALSE(classes.contains("alpha"));
    EXPECT_TRUE (classes.contains("beta"));
    EXPECT_FALSE(classes.contains("gamma"));

    classes.insert("alpha");
    classes.insert("gamma");
    EXPECT_TRUE (classes.contains("alpha"));
    EXPECT_TRUE (classes.contains("beta"));
    EXPECT_TRUE (classes.contains("gamma"));

    // Copy Constructor and equality operators.
    ClientClasses classes2(classes);
    EXPECT_EQ(classes, classes2);

    // A bigger than B
    classes.insert("zeta");
    EXPECT_NE(classes, classes2);

    // A and B equal again.
    classes2.insert("zeta");
    EXPECT_EQ(classes, classes2);

    // B bigger than A.
    classes2.insert("chi");
    EXPECT_NE(classes, classes2);

    // Order matters.
    ClientClasses classes3;
    classes3.insert("alpha");
    classes3.insert("gamma");
    classes3.insert("beta");
    classes3.insert("zeta");
    EXPECT_EQ(classes3.size(), classes.size());
    EXPECT_NE(classes3, classes);
}

// Check if ClientClasses object can be created from the string of comma
// separated values.
TEST(ClassifyTest, ClientClassesFromString) {
    {
        ClientClasses classes("alpha, beta, gamma");
        EXPECT_EQ(3, classes.size());
        EXPECT_FALSE(classes.contains(""));
        EXPECT_TRUE(classes.contains("alpha"));
        EXPECT_TRUE(classes.contains("beta"));
        EXPECT_TRUE(classes.contains("gamma"));
    }

    {
        ClientClasses classes("alpha, , beta ,");
        EXPECT_EQ(2, classes.size());
        EXPECT_TRUE(classes.contains("alpha"));
        EXPECT_FALSE(classes.contains(""));
        EXPECT_TRUE(classes.contains("beta"));
    }

    {
        ClientClasses classes("");
        EXPECT_TRUE(classes.empty());
    }

    {
        ClientClasses classes("    ");
        EXPECT_TRUE(classes.empty());
    }

    {
        ClientClasses classes(", ,, ,");
        EXPECT_TRUE(classes.empty());
    }
}

// Check if one can iterate over a ClientClasses object
TEST(ClassifyTest, ClientClassesIterator) {
    ClientClasses classes("alpha, beta, gamma");
    size_t count = 0;
    bool seenalpha = false;
    bool seenbeta = false;
    bool seengamma = false;
    bool seendelta = false;
    for (auto const& it : classes) {
        ++count;
        if (it == "alpha") {
            seenalpha = true;
        } else if (it == "beta") {
            seenbeta = true;
        } else if (it == "gamma") {
            seengamma = true;
        } else if (it == "delta") {
            seendelta = true;
        } else {
            ADD_FAILURE() << "Got unexpected " << it;
        }
    }
    EXPECT_EQ(count, classes.size());
    EXPECT_TRUE(seenalpha);
    EXPECT_TRUE(seenbeta);
    EXPECT_TRUE(seengamma);
    EXPECT_FALSE(seendelta);
}

// Check that the ClientClasses::toText function returns
// correct values.
TEST(ClassifyTest, ClientClassesToText) {
    // No classes.
    ClientClasses classes;
    EXPECT_TRUE(classes.toText().empty());

    // Insert single class name and see if it doesn't include spurious
    // comma after it.
    classes.insert("alpha");
    EXPECT_EQ("alpha", classes.toText());

    // Insert next class name and see that both classes are present.
    classes.insert("gamma");
    EXPECT_EQ("alpha, gamma", classes.toText());

    // Insert third class and make sure they get ordered in insert order.
    classes.insert("beta");
    EXPECT_EQ("alpha, gamma, beta", classes.toText());

    // Check non-standard separator.
    EXPECT_EQ("alpha.gamma.beta", classes.toText("."));
}

// Check that the ClientClasses::toElement function returns
// correct values.
TEST(ClassifyTest, ClientClassesToElement) {
    // No classes.
    ClientClasses classes;
    EXPECT_TRUE(classes.toElement()->empty());

    // Insert single class name and see that it's there.
    classes.insert("alpha");
    EXPECT_EQ("[ \"alpha\" ]", classes.toElement()->str());

    // Insert next class name and see that both classes are present.
    classes.insert("gamma");
    EXPECT_EQ("[ \"alpha\", \"gamma\" ]", classes.toElement()->str());

    // Insert third class and make sure they get ordered in insert order.
    classes.insert("beta");
    EXPECT_EQ("[ \"alpha\", \"gamma\", \"beta\" ]", classes.toElement()->str());
}

// Check that selected class can be erased.
TEST(ClassifyTest, Erase) {
    ClientClasses classes;

    classes.insert("alpha");
    classes.insert("beta");
    EXPECT_TRUE(classes.contains("alpha"));
    EXPECT_TRUE(classes.contains("beta"));

    classes.erase("beta");
    EXPECT_TRUE(classes.contains("alpha"));
    EXPECT_FALSE(classes.contains("beta"));

    classes.erase("alpha");
    EXPECT_FALSE(classes.contains("alpha"));
    EXPECT_FALSE(classes.contains("beta"));
}

// Check that the ClientClasses::fromElement function.
TEST(ClassifyTest, ClientClassesFromElement) {
    // No classes.
    ClientClasses classes;
    EXPECT_TRUE(classes.toElement()->empty());

    ElementPtr cclasses_element;
    // Verify a empty element pointer is harmless.
    ASSERT_NO_THROW(classes.fromElement(cclasses_element));

    // Verify A non-list element is caught.
    cclasses_element = Element::create("bogus");
    ASSERT_THROW_MSG(classes.fromElement(cclasses_element), BadValue,
                    "not a List element");

    // Verify an empty list is harmless.
    cclasses_element = Element::createList();

    // Verify a empty element pointer is harmless.
    ASSERT_NO_THROW(classes.fromElement(cclasses_element));

    // Verify an invalid list is caught.
    cclasses_element->add(Element::create(123));
    ASSERT_THROW_MSG(classes.fromElement(cclasses_element), BadValue,
                    "elements of list must be valid strings");

    cclasses_element = Element::createList();
    cclasses_element->add(Element::create("one"));
    cclasses_element->add(Element::create("two"));

    // Verify a valid list works.
    ASSERT_NO_THROW(classes.fromElement(cclasses_element));
    EXPECT_TRUE(classes.contains("one"));
    EXPECT_TRUE(classes.contains("two"));

    // Verify a second invocation replaces the contents.
    cclasses_element = Element::createList();
    cclasses_element->add(Element::create("three"));
    ASSERT_NO_THROW(classes.fromElement(cclasses_element));
    EXPECT_FALSE(classes.contains("one"));
    EXPECT_FALSE(classes.contains("two"));
    EXPECT_TRUE(classes.contains("three"));

    // Verify another invocation with an empty pointer is harmless.
    cclasses_element.reset();
    ASSERT_NO_THROW(classes.fromElement(cclasses_element));
    EXPECT_TRUE(classes.contains("three"));

    // Verify another third invocation with an empty list
    // clears the contents.
    cclasses_element = Element::createList();
    ASSERT_NO_THROW(classes.fromElement(cclasses_element));
    EXPECT_TRUE(classes.empty());

    cclasses_element->add(Element::create("foo"));
    cclasses_element->add(Element::create("bar"));
    cclasses_element->add(Element::create("foo"));
    cclasses_element->add(Element::create("bar"));

    ASSERT_NO_THROW(classes.fromElement(cclasses_element));
    ASSERT_EQ(classes.size(), 2);
    auto cclass = classes.begin();
    EXPECT_EQ(*cclass, "foo");
    ++cclass;
    EXPECT_EQ(*cclass, "bar");
}

// Check that the ClientClasses::intersects function works.
TEST(ClassifyTest, ClientClassesIntersects) {
    ClientClasses classes1;
    ClientClasses classes2;

    EXPECT_FALSE(classes1.intersects(classes2));
    EXPECT_FALSE(classes2.intersects(classes1));

    classes1.insert("one");

    EXPECT_FALSE(classes1.intersects(classes2));
    EXPECT_FALSE(classes2.intersects(classes1));

    classes2.insert("two");
    classes2.insert("three");

    EXPECT_FALSE(classes1.intersects(classes2));
    EXPECT_FALSE(classes2.intersects(classes1));

    classes2.insert("one");

    EXPECT_TRUE(classes1.intersects(classes2));
    EXPECT_TRUE(classes2.intersects(classes1));
}
