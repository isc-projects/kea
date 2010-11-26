// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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
#include <boost/shared_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

#include "random_number_generator.h"

namespace isc {
namespace nsas {

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

    int gen() { return gen_(); }
    int max() const { return max_; }
    int min() const { return min_; }

private:
    UniformRandomIntegerGenerator gen_;

    const static int min_ = 1;
    const static int max_ = 10;
};

// Test of the constructor
TEST_F(UniformRandomIntegerGeneratorTest, Constructor) {
    //The range must be min<=max
    ASSERT_DEATH(UniformRandomIntegerGenerator(3, 2), "");
}

// Test of the generated integers are in the range [min, max]
TEST_F(UniformRandomIntegerGeneratorTest, IntegerRange) {
    vector<int> numbers;

    //Generate a lot of random integers
    for(int i = 0; i < max()*10; ++i){
        numbers.push_back(gen());
    }

    //Remove the duplicated values
    sort(numbers.begin(), numbers.end());
    vector<int>::iterator it = unique(numbers.begin(), numbers.end());

    //make sure the numbers are in range [min, max]
    ASSERT_EQ(it - numbers.begin(), max() - min() + 1); 
}

} // namespace nsas
} // namespace isc
