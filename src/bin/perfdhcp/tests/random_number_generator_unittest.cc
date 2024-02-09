// Copyright (C) 2010-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfdhcp/random_number_generator.h>

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

#include <iostream>

using namespace isc;
using namespace isc::perfdhcp;
using namespace std;

/// \brief Test Fixture Class for uniform random number generator
///
/// The hard part for this test is how to test that the number is random?
/// and how to test that the number is uniformly distributed?
/// Or maybe we can trust the boost implementation
class UniformRandomIntegerGeneratorTest : public ::testing::Test {
public:
    UniformRandomIntegerGeneratorTest():
        gen_(min_, max_)
    {
    }
    virtual ~UniformRandomIntegerGeneratorTest(){}

    int gen() { return (gen_()); }
    int max() const { return (max_); }
    int min() const { return (min_); }

private:
    UniformRandomIntegerGenerator gen_;

    const static int min_ = 1;
    const static int max_ = 10;
};

// Test of the generated integers are in the range [min, max]
TEST_F(UniformRandomIntegerGeneratorTest, IntegerRange) {
    vector<int> numbers;

    // Generate a lot of random integers
    for (int i = 0; i < max()*10; ++i) {
        numbers.push_back(gen());
    }

    // Remove the duplicated values
    sort(numbers.begin(), numbers.end());
    vector<int>::iterator it = unique(numbers.begin(), numbers.end());

    // make sure the numbers are in range [min, max]
    ASSERT_EQ(it - numbers.begin(), max() - min() + 1);
}
