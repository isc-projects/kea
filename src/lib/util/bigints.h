// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file provides an interface towards bigint implementations.
// Currently, it uses the ones from boost::multiprecision, but if we ever want
// to swap it out, or implement our own, we can seamlessly do it in this header.

#ifndef UTIL_BIGINTS_H
#define UTIL_BIGINTS_H

#include <boost/multiprecision/cpp_int.hpp>

namespace isc {
namespace util {

using int128_t = boost::multiprecision::int128_t;

using uint128_t = boost::multiprecision::uint128_t;

}  // namespace util
}  // namespace isc

#endif  // UTIL_BIGINTS_H