// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <gtest/gtest.h>

#include <set>

#include <boost/foreach.hpp>

#include <statistics/counter_dict.h>

enum CounterItems {
    ITEM1 = 0,
    ITEM2 = 1,
    ITEM3 = 2,
    NUMBER_OF_ITEMS = 3
};

using namespace isc::statistics;

TEST(CounterDictionaryCreateTest, invalidCounterSize) {
    // Creating counter with 0 elements will cause an isc::InvalidParameter
    // exception
    EXPECT_THROW(CounterDictionary counters(0), isc::InvalidParameter);
}

// This fixture is for testing CounterDictionary.
class CounterDictionaryTest : public ::testing::Test {
protected:
    CounterDictionaryTest() : counters(NUMBER_OF_ITEMS) {
        counters.addElement("test");
        counters.addElement("sub.test");
    }
    ~CounterDictionaryTest() {}

    CounterDictionary counters;
};

TEST_F(CounterDictionaryTest, initializeCheck) {
    // Check if the all counters are initialized with 0
    EXPECT_EQ(counters["test"].get(ITEM1), 0);
    EXPECT_EQ(counters["test"].get(ITEM2), 0);
    EXPECT_EQ(counters["test"].get(ITEM3), 0);
}

TEST_F(CounterDictionaryTest, getElement) {
    // Another member function to get counters for the element
    EXPECT_EQ(counters.getElement("test").get(ITEM1), 0);
    EXPECT_EQ(counters.getElement("test").get(ITEM2), 0);
    EXPECT_EQ(counters.getElement("test").get(ITEM3), 0);
}

TEST_F(CounterDictionaryTest, incrementCounterItem) {
    // Increment counters
    counters["test"].inc(ITEM1);
    counters["test"].inc(ITEM2);
    counters["test"].inc(ITEM2);
    counters["test"].inc(ITEM3);
    counters["test"].inc(ITEM3);
    counters["test"].inc(ITEM3);
    // Check if the counters have expected values
    EXPECT_EQ(counters["test"].get(ITEM1), 1);
    EXPECT_EQ(counters["test"].get(ITEM2), 2);
    EXPECT_EQ(counters["test"].get(ITEM3), 3);
    EXPECT_EQ(counters["sub.test"].get(ITEM1), 0);
    EXPECT_EQ(counters["sub.test"].get(ITEM2), 0);
    EXPECT_EQ(counters["sub.test"].get(ITEM3), 0);
}

TEST_F(CounterDictionaryTest, deleteElement) {
    // Ensure the element is accessible
    EXPECT_EQ(counters["test"].get(ITEM1), 0);
    EXPECT_EQ(counters["test"].get(ITEM2), 0);
    EXPECT_EQ(counters["test"].get(ITEM3), 0);
    // Delete the element
    counters.deleteElement("test");
    // Accessing to the deleted element will cause an isc::OutOfRange exception
    EXPECT_THROW(counters["test"].get(ITEM1), isc::OutOfRange);
    // Deleting an element which does not exist will cause an isc::OutOfRange
    //  exception
    EXPECT_THROW(counters.deleteElement("test"), isc::OutOfRange);
}

TEST_F(CounterDictionaryTest, invalidCounterItem) {
    // Incrementing out-of-bound counter will cause an isc::OutOfRange
    // exception
    EXPECT_THROW(counters["test"].inc(NUMBER_OF_ITEMS), isc::OutOfRange);
}

TEST_F(CounterDictionaryTest, uniquenessCheck) {
    // Adding an element which already exists will cause an isc::OutOfRange
    //  exception 
    EXPECT_THROW(counters.addElement("test"), isc::InvalidParameter);
}

TEST_F(CounterDictionaryTest, iteratorTest) {
    // Increment counters
    counters["test"].inc(ITEM1);
    counters["sub.test"].inc(ITEM2);
    counters["sub.test"].inc(ITEM2);

    // boolean values to check all of the elements can be accessed through
    // the iterator
    bool element_test_visited = false;
    bool element_sub_test_visited = false;
    // Walk through the elements with iterator
    // Check if the elements "test" and "sub.test" appears only once
    //  and the counters have expected value
    for (CounterDictionary::ConstIterator i = counters.begin(),
                                          e = counters.end();
         i != e;
         ++i
         )
    {
        const std::string& zone = *i;
        if (zone == "test" && element_test_visited == false) {
            element_test_visited = true;
            // Check if the counters have expected value
            EXPECT_EQ(counters[zone].get(ITEM1), 1);
            EXPECT_EQ(counters[zone].get(ITEM2), 0);
        } else if (zone == "sub.test" &&
                   element_sub_test_visited == false) {
            element_sub_test_visited = true;
            // Check if the counters have expected value
            EXPECT_EQ(counters[zone].get(ITEM1), 0);
            EXPECT_EQ(counters[zone].get(ITEM2), 2);
        } else {
            // Test fails when reaches here: the element is not expected or
            //  the element appeared twice
            FAIL() << "Unexpected iterator value";
        }
    }
    // Check if the "test" and "sub.test" is accessible
    EXPECT_TRUE(element_test_visited);
    EXPECT_TRUE(element_sub_test_visited);
}

TEST_F(CounterDictionaryTest, iteratorCopyTest) {
    // Increment counters
    counters["test"].inc(ITEM1);
    counters["sub.test"].inc(ITEM2);
    counters["sub.test"].inc(ITEM2);

    CounterDictionary::ConstIterator i1 = counters.begin();
    CounterDictionary::ConstIterator i2(i1);
    CounterDictionary::ConstIterator i3;
    i3 = i1;

    EXPECT_TRUE(i1 == i2);
    EXPECT_TRUE(i1 == i3);
    EXPECT_TRUE(i2 == i3);

    ++i2;
    EXPECT_TRUE(i1 != i2);
    EXPECT_TRUE(i1 == i3);
    EXPECT_TRUE(i2 != i3);

    ++i3;
    EXPECT_TRUE(i1 != i2);
    EXPECT_TRUE(i1 != i3);
    EXPECT_TRUE(i2 == i3);
}
