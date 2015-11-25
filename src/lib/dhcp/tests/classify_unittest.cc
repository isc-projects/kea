// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
    for (ClientClasses::const_iterator it = classes.begin();
         it != classes.end(); ++it) {
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
