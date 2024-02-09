// Copyright (C) 2010-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NSAS_RANDOM_NUMBER_GENERATOR_H
#define NSAS_RANDOM_NUMBER_GENERATOR_H

#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <vector>

#include <exceptions/exceptions.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

/// PLEASE DO NOT USE THIS IN CRYPTOGRAPHICALLY SENSITIVE CODE.

namespace isc {
namespace perfdhcp {

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
        // Init with the current time
        rng_.seed(time(0));
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

}   // namespace perfdhcp
}   // namespace isc

#endif//NSAS_RANDOM_NUMBER_GENERATOR_H
