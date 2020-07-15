// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_CHRONO_TIME_UTILS_H
#define KEA_CHRONO_TIME_UTILS_H

#include <chrono>
#include <string>

namespace isc {
namespace util {

/// @brief The number of digits of fractional seconds supplied by the
/// underlying class, std::chrono::time_point. Typically 6 = microseconds.
const size_t MAX_FSECS_PRECISION = 6;

/// @brief Converts chrono time point structure to text
///
/// This is Kea implementation for converting time point to strings.
/// @param t time point value to convert to text
/// @param fsecs_precision number of digits of precision for fractional seconds.
/// Zero omits the value.
///
/// @return a string representing time
std::string clockToText(std::chrono::system_clock::time_point t,
                        size_t fsecs_precision = MAX_FSECS_PRECISION);

/// @brief Converts StatsDuration to text
///
/// See @ref clockToText for explanation why we chose our own implementation.
/// @tparam Duration duration type instance for instance
/// @c std::chrono::system_clock::duration.
/// @param dur duration value to convert to text
/// @param fsecs_precision number of digits of precision for fractional seconds.
/// Zero omits the value.
///
/// @return a string representing time
template<typename Duration>
std::string durationToText(Duration dur,
                           size_t fsecs_precision = MAX_FSECS_PRECISION);

} // end of isc::util namespace
} // end of isc namespace

#endif
