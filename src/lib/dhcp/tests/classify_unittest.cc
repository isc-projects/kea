// Copyright (C) 2011-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/classify.h>
#include <gtest/gtest.h>

using namespace isc::dhcp;

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
    for (ClientClasses::const_iterator it = classes.cbegin();
         it != classes.cend(); ++it) {
        ++count;
        if (*it == "alpha") {
            seenalpha = true;
        } else if (*it == "beta") {
            seenbeta = true;
        } else if (*it == "gamma") {
            seengamma = true;
        } else if (*it == "delta") {
            seendelta = true;
        } else {
            ADD_FAILURE() << "Got unexpected " << *it;
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
