// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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
    return (std::find_if(begin, end,
                         std::bind1st(std::not_equal_to<int>(), 0))
            == end);
}

/// @brief Fill in specified range with a random data.
///
/// Make sure that random number generator is initialized
/// properly. Otherwise you will get a the same pseudo-random sequence
/// after every start of your process.  Calling srand() is enough. This
/// method uses default rand(), which is usually a LCG pseudo-random
/// number generator, so it is not suitable for security
/// purposes. Please get a decent PRNG implementation, like Mersene
/// twister, if you are doing anything related with security.
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
