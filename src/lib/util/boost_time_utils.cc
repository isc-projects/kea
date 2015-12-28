// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/boost_time_utils.h>
#include <sstream>
#include <iomanip>

std::string
isc::util::ptimeToText(boost::posix_time::ptime t) {
    boost::gregorian::date d = t.date();
    std::stringstream s;
    s << d.year()
      << "-" << std::setw(2) << std::setfill('0') << d.month().as_number()
      << "-" << std::setw(2) << std::setfill('0') << d.day()
      << " " << durationToText(t.time_of_day());
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
