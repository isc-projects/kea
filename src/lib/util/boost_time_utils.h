// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_BOOST_TIME_UTILS_H
#define KEA_BOOST_TIME_UTILS_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace isc {
namespace util {

/// @brief Converts ptime structure to text
///
/// This is Kea implementation for converting ptime to strings.
/// It's a functional equivalent of boost::posix_time::to_simple_string. We do
/// not use it, though, because it would introduce unclear dependency on
/// boost_time_date library. First, we try to avoid depending on boost libraries
/// (we tend to use only the headers). Second, this dependency is system
/// specific, i.e. it is required on Ubuntu and FreeBSD, but doesn't seem to
/// be needed on OS X. Since the functionality needed is minor, we decided to
/// reimplement it on our own, rather than introduce extra dependencies.
/// This explanation also applies to @ref durationToText.
///
/// @return a string representing time
std::string ptimeToText(boost::posix_time::ptime t);

/// @brief Converts StatsDuration to text
///
/// This is Kea equivalent of boost::posix_time::to_simple_string(time_duration).
/// See @ref ptimeToText for explanation why we chose our own implementation.
///
/// @return a string representing time
std::string durationToText(boost::posix_time::time_duration dur);

}; // end of isc::util namespace
}; // end of isc namespace

#endif
