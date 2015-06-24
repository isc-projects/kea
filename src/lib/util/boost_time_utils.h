// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
