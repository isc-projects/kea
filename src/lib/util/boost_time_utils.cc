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

#include <util/boost_time_utils.h>

std::string
isc::util::ptimeToText(boost::posix_time::ptime t) {
    boost::gregorian::date d = t.date();
    std::stringstream s;
    s << d.year() << "-" << d.month() << "-" << d.day();
    s << " " << durationToText(t.time_of_day());
    return (s.str());
}

std::string
isc::util::durationToText(boost::posix_time::time_duration dur) {
    std::stringstream s;
    s << std::setw(2) << std::setfill('0') << dur.hours()
      << ":" << std::setw(2) << std::setfill('0') << dur.minutes()
      << ":" << std::setw(2) << std::setfill('0') << dur.seconds()
      << "." << std::setw(boost::posix_time::time_duration::num_fractional_digits())
      << std::setfill('0')
      << dur.fractional_seconds();

    return (s.str());
}
