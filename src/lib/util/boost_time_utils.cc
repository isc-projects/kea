// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/boost_time_utils.h>
#include <sstream>
#include <iomanip>

std::string
isc::util::ptimeToText(boost::posix_time::ptime t, size_t fsecs_precision) {
    boost::gregorian::date d = t.date();
    std::stringstream s;
    s << d.year()
      << "-" << std::setw(2) << std::setfill('0') << d.month().as_number()
      << "-" << std::setw(2) << std::setfill('0') << d.day()
      << " " << durationToText(t.time_of_day(), fsecs_precision);
    return (s.str());
}

std::string
isc::util::durationToText(boost::posix_time::time_duration dur, size_t fsecs_precision) {
    std::stringstream s;
    s << std::setw(2) << std::setfill('0') << dur.hours()
      << ":" << std::setw(2) << std::setfill('0') << dur.minutes()
      << ":" << std::setw(2) << std::setfill('0') << dur.seconds();

    // If the requested precision is less than the maximum native precision
    // we will divide the fractional seconds value by 10^(max - requested)
    if (fsecs_precision) {
        size_t fsecs = dur.fractional_seconds();
        size_t width = MAX_FSECS_PRECISION;
        if (fsecs_precision < width) {
            for (auto i = 0; i < width - fsecs_precision; ++i) {
                fsecs /= 10;
            }

            width = fsecs_precision;
        }

        s << "." << std::setw(width)
          << std::setfill('0')
          << fsecs;
    }

    return (s.str());
}
