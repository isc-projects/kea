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

namespace isc {
namespace util {

/// @brief Converts ptime structure to text
/// @return a string representing time
std::string ptimeToText(boost::posix_time::ptime t);

/// @brief Converts StatsDuration to text
/// @return a string representing time
std::string durationToText(boost::posix_time::time_duration dur);

}; // end of isc::util namespace
}; // end of isc namespace

#endif
