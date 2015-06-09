// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/random/random_number_generator.h>
#include <util/unittests/test_exceptions.h>

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

#include <iostream>


namespace isc {
namespace util {
namespace random {

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

// Some validation tests will incur performance penalty, so the tests are
// made only in "debug" version with assert(). But if NDEBUG is defined
// the tests will be failed since assert() is non-op in non-debug version.
// The "#ifndef NDEBUG" is added to make the tests be performed only in
// non-debug environment.
// Note: the death test is not supported by all platforms.  We need to
// compile tests using it selectively.
#if !defined(NDEBUG)
// Test of the constructor
TEST_F(UniformRandomIntegerGeneratorTest, Constructor) {
    // The range must be min<=max
    ASSERT_THROW_WITH(UniformRandomIntegerGenerator(3, 2), InvalidLimits,
                      "minimum limit is greater than maximum "
                      "when initializing UniformRandomIntegerGenerator");
}
#endif

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

/// \brief Test Fixture Class for weighted random number generator
class WeightedRandomIntegerGeneratorTest : public ::testing::Test {
public:
    WeightedRandomIntegerGeneratorTest()
    { }

    virtual ~WeightedRandomIntegerGeneratorTest()
    { }
};

// Test of the weighted random number generator constructor
TEST_F(WeightedRandomIntegerGeneratorTest, Constructor) {
    vector<double> probabilities;

    // If no probabilities is provided, the smallest integer will always
    // be generated
    WeightedRandomIntegerGenerator gen(probabilities, 123);
    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(gen(), 123);
    }

/// Some validation tests will incur performance penalty, so the tests are
/// made only in "debug" version with assert(). But if NDEBUG is defined
/// the tests will be failed since assert() is non-op in non-debug version.
/// The "#ifndef NDEBUG" is added to make the tests be performed only in
/// non-debug environment.
#if !defined(NDEBUG)
    //The probability must be >= 0
    probabilities.push_back(-0.1);
    probabilities.push_back(1.1);
    ASSERT_THROW_WITH(WeightedRandomIntegerGenerator gen2(probabilities),
                      InvalidProbValue,
                      "probability must be in the range 0..1");

    //The probability must be <= 1.0
    probabilities.clear();
    probabilities.push_back(0.1);
    probabilities.push_back(1.1);
    ASSERT_THROW_WITH(WeightedRandomIntegerGenerator gen3(probabilities),
                      InvalidProbValue,
                      "probability must be in the range 0..1");

    //The sum must be equal to 1.0
    probabilities.clear();
    probabilities.push_back(0.2);
    probabilities.push_back(0.9);
    ASSERT_THROW_WITH(WeightedRandomIntegerGenerator gen4(probabilities),
                      SumNotOne,
                      "Sum of probabilities is not equal to 1");

    //The sum must be equal to 1.0
    probabilities.clear();
    probabilities.push_back(0.3);
    probabilities.push_back(0.2);
    probabilities.push_back(0.1);
    ASSERT_THROW_WITH(WeightedRandomIntegerGenerator gen5(probabilities),
                      SumNotOne,
                      "Sum of probabilities is not equal to 1");
#endif
}

// Test the randomization of the generator
TEST_F(WeightedRandomIntegerGeneratorTest, WeightedRandomization) {
    const int repeats = 100000;
    // We repeat the simulation for N=repeats times
    // for each probability p, its average is mu = N*p
    // variance sigma^2 = N * p * (1-p)
    // sigma = sqrt(N*2/9)
    // we should make sure that mu - 4sigma < count < mu + 4sigma
    // which means for 99.99366% of the time this should be true
    {
        double p = 0.5;
        vector<double> probabilities;
        probabilities.push_back(p);
        probabilities.push_back(p);

        // Uniformly generated integers
        WeightedRandomIntegerGenerator gen(probabilities);
        int c1 = 0;
        int c2 = 0;
        for (int i = 0; i < repeats; ++i){
            int n = gen();
            if (n == 0) {
                ++c1;
            } else if (n == 1) {
                ++c2;
            }
        }
        double mu = repeats * p;
        double sigma = sqrt(repeats * p * (1 - p));
        ASSERT_TRUE(fabs(c1 - mu) < 4*sigma);
        ASSERT_TRUE(fabs(c2 - mu) < 4*sigma);
    }

    {
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        double p1 = 0.2;
        double p2 = 0.8;
        probabilities.push_back(p1);
        probabilities.push_back(p2);
        WeightedRandomIntegerGenerator gen(probabilities);
        for (int i = 0; i < repeats; ++i) {
            int n = gen();
            if (n == 0) {
                ++c1;
            } else if (n == 1) {
                ++c2;
            }
        }
        double mu1 = repeats * p1;
        double mu2 = repeats * p2;
        double sigma1 = sqrt(repeats * p1 * (1 - p1));
        double sigma2 = sqrt(repeats * p2 * (1 - p2));
        ASSERT_TRUE(fabs(c1 - mu1) < 4*sigma1);
        ASSERT_TRUE(fabs(c2 - mu2) < 4*sigma2);
    }

    {
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        double p1 = 0.8;
        double p2 = 0.2;
        probabilities.push_back(p1);
        probabilities.push_back(p2);
        WeightedRandomIntegerGenerator gen(probabilities);
        for (int i = 0; i < repeats; ++i) {
            int n = gen();
            if (n == 0) {
                ++c1;
            } else if (n == 1) {
                ++c2;
            }
        }
        double mu1 = repeats * p1;
        double mu2 = repeats * p2;
        double sigma1 = sqrt(repeats * p1 * (1 - p1));
        double sigma2 = sqrt(repeats * p2 * (1 - p2));
        ASSERT_TRUE(fabs(c1 - mu1) < 4*sigma1);
        ASSERT_TRUE(fabs(c2 - mu2) < 4*sigma2);
    }

    {
        vector<double> probabilities;
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        double p1 = 0.5;
        double p2 = 0.25;
        double p3 = 0.25;
        probabilities.push_back(p1);
        probabilities.push_back(p2);
        probabilities.push_back(p3);
        WeightedRandomIntegerGenerator gen(probabilities);
        for (int i = 0; i < repeats; ++i){
            int n = gen();
            if (n == 0) {
                ++c1;
            } else if (n == 1) {
                ++c2;
            } else if (n == 2) {
                ++c3;
            }
        }
        double mu1 = repeats * p1;
        double mu2 = repeats * p2;
        double mu3 = repeats * p3;
        double sigma1 = sqrt(repeats * p1 * (1 - p1));
        double sigma2 = sqrt(repeats * p2 * (1 - p2));
        double sigma3 = sqrt(repeats * p3 * (1 - p3));
        ASSERT_TRUE(fabs(c1 - mu1) < 4*sigma1);
        ASSERT_TRUE(fabs(c2 - mu2) < 4*sigma2);
        ASSERT_TRUE(fabs(c3 - mu3) < 4*sigma3);
    }
}

// Test the reset function of generator
TEST_F(WeightedRandomIntegerGeneratorTest, ResetProbabilities) {
    const int repeats = 100000;
    vector<double> probabilities;
    int c1 = 0;
    int c2 = 0;
    double p1 = 0.8;
    double p2 = 0.2;
    probabilities.push_back(p1);
    probabilities.push_back(p2);
    WeightedRandomIntegerGenerator gen(probabilities);
    for (int i = 0; i < repeats; ++i) {
        int n = gen();
        if (n == 0) {
            ++c1;
        } else if (n == 1) {
            ++c2;
        }
    }
    double mu1 = repeats * p1;
    double mu2 = repeats * p2;
    double sigma1 = sqrt(repeats * p1 * (1 - p1));
    double sigma2 = sqrt(repeats * p2 * (1 - p2));
    ASSERT_TRUE(fabs(c1 - mu1) < 4*sigma1);
    ASSERT_TRUE(fabs(c2 - mu2) < 4*sigma2);

    // Reset the probabilities
    probabilities.clear();
    c1 = c2 = 0;
    p1 = 0.2;
    p2 = 0.8;
    probabilities.push_back(p1);
    probabilities.push_back(p2);
    gen.reset(probabilities);
    for (int i = 0; i < repeats; ++i) {
        int n = gen();
        if (n == 0) {
            ++c1;
        } else if (n == 1) {
            ++c2;
        }
    }
    mu1 = repeats * p1;
    mu2 = repeats * p2;
    sigma1 = sqrt(repeats * p1 * (1 - p1));
    sigma2 = sqrt(repeats * p2 * (1 - p2));
    ASSERT_TRUE(fabs(c1 - mu1) < 4*sigma1);
    ASSERT_TRUE(fabs(c2 - mu2) < 4*sigma2);
}

} // namespace random
} // namespace util
} // namespace isc
