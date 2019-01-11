// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DOUBLES_H
#define DOUBLES_H

#include <complex>

namespace isc {
namespace util {

/// @brief Tests two doubles for equivalence within a given tolerance.
///
/// @param a comparison operand one
/// @param b comparison operand two
/// @param tolerance the amount by which the two values may differ and
/// still be considered "equal".
/// @return True if the two values differ by less than the tolerance.
inline bool areDoublesEquivalent(double a, double b, double tolerance=0.000001) {
    return(std::abs(a - b) < tolerance);
}

} // namespace util
} // namespace isc

#endif // DOUBLES_H
