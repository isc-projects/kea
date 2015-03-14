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

#ifndef NSAS_RANDOM_NUMBER_GENERATOR_H
#define NSAS_RANDOM_NUMBER_GENERATOR_H

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

#include <exceptions/exceptions.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

namespace isc {
namespace util {
namespace random {

class InvalidLimits : public isc::BadValue {
public:
    InvalidLimits(const char* file, size_t line, const char* what) :
        isc::BadValue(file, line, what) {}
};

class SumNotOne : public isc::BadValue {
public:
    SumNotOne(const char* file, size_t line, const char* what) :
        isc::BadValue(file, line, what) {}
};

class InvalidProbValue : public isc::BadValue {
public:
    InvalidProbValue(const char* file, size_t line, const char* what) :
        isc::BadValue(file, line, what) {}
};



/// \brief Uniform random integer generator
///
/// Generate uniformly distributed integers in range of [min, max]
class UniformRandomIntegerGenerator{
public:
    /// \brief Constructor
    ///
    /// \param min The minimum number in the range
    /// \param max The maximum number in the range
    UniformRandomIntegerGenerator(int min, int max):
        min_(std::min(min, max)), max_(std::max(min, max)),
        dist_(min_, max_), generator_(rng_, dist_)
    {
        // To preserve the restriction of the underlying uniform_int class (and
        // to retain compatibility with earlier versions of the class), we will
        // abort if the minimum and maximum given are the wrong way round.
        if (min > max) {
            isc_throw(InvalidLimits, "minimum limit is greater than maximum "
                      "when initializing UniformRandomIntegerGenerator");
        }

        // Init with the current time
        rng_.seed(time(NULL));
    }

    /// \brief Generate uniformly distributed integer
    int operator()() { return generator_(); }
private:
    /// Hide default and copy constructor
    UniformRandomIntegerGenerator();///< Default constructor
    UniformRandomIntegerGenerator(const UniformRandomIntegerGenerator&); ///< Copy constructor

    int min_;                       ///< The minimum integer that can generate
    int max_;                       ///< The maximum integer that can generate
    boost::uniform_int<> dist_;     ///< Distribute uniformly.
    boost::mt19937 rng_;            ///< Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random number generator
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > generator_; ///< Uniform generator
};

/// \brief Weighted random integer generator
///
/// Generate random integers according different probabilities
class WeightedRandomIntegerGenerator {
public:
    /// \brief Constructor
    ///
    /// \param probabilities The probabilities for all the integers, the probability must be 
    /// between 0 and 1.0, the sum of probabilities must be equal to 1.
    /// For example, if the probabilities contains the following values:
    /// 0.5 0.3 0.2, the 1st integer will be generated more frequently than the
    /// other integers and the probability is proportional to its value.
    /// \param min The minimum integer that generated, other integers will be 
    /// min, min + 1, ..., min + probabilities.size() - 1
    WeightedRandomIntegerGenerator(const std::vector<double>& probabilities,
        size_t min = 0):
        dist_(0, 1.0), uniform_real_gen_(rng_, dist_), min_(min)
    {
        // The probabilities must be valid.  Checking is quite an expensive
        // operation, so is only done in a debug build.
        assert(areProbabilitiesValid(probabilities));

        // Calculate the partial sum of probabilities
        std::partial_sum(probabilities.begin(), probabilities.end(),
                                     std::back_inserter(cumulative_));
        // Init with the current time
        rng_.seed(time(NULL));
    }

    /// \brief Default constructor
    ///
    WeightedRandomIntegerGenerator():
        dist_(0, 1.0), uniform_real_gen_(rng_, dist_), min_(0)
    {
    }

    /// \brief Reset the probabilities
    ///
    /// Change the weights of each integers
    /// \param probabilities The probabilities for all the integers
    /// \param min The minimum integer that generated
    void reset(const std::vector<double>& probabilities, size_t min = 0)
    {
        // The probabilities must be valid.
        assert(areProbabilitiesValid(probabilities));

        // Reset the cumulative sum
        cumulative_.clear();

        // Calculate the partial sum of probabilities
        std::partial_sum(probabilities.begin(), probabilities.end(),
                                     std::back_inserter(cumulative_));

        // Reset the minimum integer
        min_ = min;
    }

    /// \brief Generate weighted random integer
    size_t operator()()
    {
        return std::lower_bound(cumulative_.begin(), cumulative_.end(), uniform_real_gen_()) 
            - cumulative_.begin() + min_;
    }

private:
    /// \brief Check the validation of probabilities vector
    ///
    /// The probability must be in range of [0, 1.0] and the sum must be equal
    /// to 1.0.  Empty probabilities are also valid.
    ///
    /// Checking the probabilities is quite an expensive operation, so it is
    /// only done during a debug build (via a call through assert()).  However,
    /// instead of letting assert() call abort(), if this method encounters an
    /// error, an exception is thrown.  This makes unit testing somewhat easier.
    ///
    /// \param probabilities Vector of probabilities.
    bool areProbabilitiesValid(const std::vector<double>& probabilities) const
    {
        typedef std::vector<double>::const_iterator Iterator;
        double sum = probabilities.empty() ? 1.0 : 0.0;
        for(Iterator it = probabilities.begin(); it != probabilities.end(); ++it){
            //The probability must be in [0, 1.0]
            if(*it < 0.0 || *it > 1.0) {
                isc_throw(InvalidProbValue,
                          "probability must be in the range 0..1");
            }

            sum += *it;
        }

        double epsilon = 0.0001;
        // The sum must be equal to 1
       if (std::fabs(sum - 1.0) >= epsilon) {
           isc_throw(SumNotOne, "Sum of probabilities is not equal to 1");
       }

       return true;
    }

    std::vector<double> cumulative_;    ///< Partial sum of the probabilities
    boost::mt19937 rng_;                ///< Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random number generator 
    boost::uniform_real<> dist_;        ///< Uniformly distributed real numbers

    // Shortcut typedef
    // This typedef is placed directly before its use, as the sunstudio
    // compiler could not handle it being anywhere else (don't know why)
    typedef boost::variate_generator<boost::mt19937&, boost::uniform_real<> > UniformRealGenerator;
    UniformRealGenerator uniform_real_gen_;     ///< Uniformly distributed random real numbers generator

    size_t min_;                                ///< The minimum integer that will be generated
};

}   // namespace random
}   // namespace util
}   // namespace isc

#endif//NSAS_RANDOM_NUMBER_GENERATOR_H
