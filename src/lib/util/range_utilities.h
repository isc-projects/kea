// Copyright (C) 2012-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RANGE_UTIL_H
#define RANGE_UTIL_H 1

#include <stdlib.h>
#include <algorithm>
#include <functional>

// This header contains useful methods for conduction operations on
// a range of container elements. Currently the collection is limited,
// but it is expected to grow.

namespace isc {
namespace util {

/// @brief Checks if specified range in a container contains only zeros
///
/// @param begin beginning of the range
/// @param end end of the range
///
/// @return true if there are only zeroes, false otherwise
template <typename Iterator>
bool
isRangeZero(Iterator begin, Iterator end) {
    return (std::find_if(begin, end, [] (int x) { return (0 != x); })
            == end);
}

/// @brief Fill in specified range with a random data.
///
/// Make sure that random number generator is initialized
/// properly. Otherwise you will get the same pseudo-random sequence
/// after every start of your process.  Calling srand() is enough. This
/// method uses default rand(), which is usually a LCG pseudo-random
/// number generator, so it is not suitable for security
/// purposes. Please use cryptolink RNG if you are doing anything
/// related with security.
///
/// PRNG initialization is left out of this function on purpose. It may
/// be initialized to specific value on purpose, e.g. to repeat exactly
/// the same sequence in a test.
///
/// @param begin
/// @param end
template <typename Iterator>
void
fillRandom(Iterator begin, Iterator end) {
    for (Iterator x = begin; x != end; ++x) {
        *x = random();
    }
}

} // end of isc::util namespace
} // end of isc namespace

#endif  // RANGE_UTIL_H
