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

#ifndef NDEBUG
// Test of the constructor
TEST_F(UniformRandomIntegerGeneratorTest, Constructor) {
    // The range must be min<=max
    ASSERT_DEATH(UniformRandomIntegerGenerator(3, 2), "");
}
#endif

// Test of the generated integers are in the range [min, max]
TEST_F(UniformRandomIntegerGeneratorTest, IntegerRange) {
    vector<int> numbers;

    // Generate a lot of random integers
    for(int i = 0; i < max()*10; ++i){
        numbers.push_back(gen());
    }

    // Remove the duplicated values
    sort(numbers.begin(), numbers.end());
    vector<int>::iterator it = unique(numbers.begin(), numbers.end());

    // make sure the numbers are in range [min, max]
    ASSERT_EQ(it - numbers.begin(), max() - min() + 1); 
}


/// \brief Test Fixture Class for weighted random number generator
class WeightedRandomIntegerGeneratorTest : public ::testing::Test {
public:
    WeightedRandomIntegerGeneratorTest()
    { }

    virtual ~WeightedRandomIntegerGeneratorTest()
    { }
};

// Test of the weighted random number generator constructor
TEST_F(WeightedRandomIntegerGeneratorTest, Constructor) 
{
    vector<double> probabilities;

    // If no probabilities is provided, the smallest integer will always be generated
    WeightedRandomIntegerGenerator gen(probabilities, 123);
    for(int i = 0; i < 100; ++i){
        ASSERT_EQ(gen(), 123);
    }

#ifndef NDEBUG
    //The probability must be >= 0
    probabilities.push_back(-0.1);
    probabilities.push_back(1.1);
    ASSERT_DEATH(WeightedRandomIntegerGenerator gen2(probabilities), "");

    //The probability must be <= 1.0
    probabilities.clear();
    probabilities.push_back(0.1);
    probabilities.push_back(1.1);
    ASSERT_DEATH(WeightedRandomIntegerGenerator gen3(probabilities), "");

    //The sum must be equal to 1.0
    probabilities.clear();
    probabilities.push_back(0.2);
    probabilities.push_back(0.9);
    ASSERT_DEATH(WeightedRandomIntegerGenerator gen4(probabilities), "");

    //The sum must be equal to 1.0
    probabilities.clear();
    probabilities.push_back(0.3);
    probabilities.push_back(0.2);
    probabilities.push_back(0.1);
    ASSERT_DEATH(WeightedRandomIntegerGenerator gen5(probabilities), "");
#endif
}

// Test the randomization of the generator
TEST_F(WeightedRandomIntegerGeneratorTest, WeightedRandomization) 
{
    {
        vector<double> probabilities;
        probabilities.push_back(0.5);
        probabilities.push_back(0.5);

        // Uniformly generated integers
        WeightedRandomIntegerGenerator gen(probabilities);
        int c1 = 0;
        int c2 = 0;
        for(int i = 0; i < 100000; ++i){
            int n = gen();
            if(n == 0) ++c1;
            else if(n == 1) ++c2;
        }
        // The probabilities should almost equal
        ASSERT_EQ(1, (int)(c1*1.0/c2 + 0.5));
    }

    {
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        probabilities.push_back(0.2);
        probabilities.push_back(0.8);
        WeightedRandomIntegerGenerator gen(probabilities);
        for(int i = 0; i < 100000; ++i){
            int n = gen();
            if(n == 0) ++c1;
            else if(n == 1) ++c2;
        }
        // The 2nd integer count should be 4 times of 1st one
        ASSERT_EQ(4, (int)(c2*1.0/c1 + 0.5));
    }

    {
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        probabilities.push_back(0.8);
        probabilities.push_back(0.2);
        WeightedRandomIntegerGenerator gen(probabilities);
        for(int i = 0; i < 100000; ++i){
            int n = gen();
            if(n == 0) ++c1;
            else if(n == 1) ++c2;
        }
        // The 1st integer count should be 4 times of 2nd one
        ASSERT_EQ(4, (int)(c1*1.0/c2 + 0.5));
    }

    {
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        probabilities.push_back(0.5);
        probabilities.push_back(0.25);
        probabilities.push_back(0.25);
        WeightedRandomIntegerGenerator gen(probabilities);
        for(int i = 0; i < 100000; ++i){
            int n = gen();
            if(n == 0) ++c1;
            else if(n == 1) ++c2;
            else if(n == 2) ++c3;
        }
        // The 1st integer count should be double of 2nd one
        ASSERT_EQ(2, (int)(c1*1.0/c2 + 0.5));
        // The 1st integer count should be double of 3rd one
        ASSERT_EQ(2, (int)(c1*1.0/c3 + 0.5));
    }
}

// Test the reset function of generator
TEST_F(WeightedRandomIntegerGeneratorTest, ResetProbabilities) 
{
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        probabilities.push_back(0.8);
        probabilities.push_back(0.2);
        WeightedRandomIntegerGenerator gen(probabilities);
        for(int i = 0; i < 100000; ++i){
            int n = gen();
            if(n == 0) ++c1;
            else if(n == 1) ++c2;
        }
        // The 1st integer count should be 4 times of 2nd one
        ASSERT_EQ(4, (int)(c1*1.0/c2 + 0.5));

        // Reset the probabilities
        probabilities.clear();
        c1 = c2 = 0;
        probabilities.push_back(0.2);
        probabilities.push_back(0.8);
        gen.reset(probabilities);
        for(int i = 0; i < 100000; ++i){
            int n = gen();
            if(n == 0) ++c1;
            else if(n == 1) ++c2;
        }
        // The 2nd integer count should be 4 times of 1st one
        ASSERT_EQ(4, (int)(c2*1.0/c1 + 0.5));
}

} // namespace nsas
} // namespace isc
