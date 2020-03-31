// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/chrono_time_utils.h>
#include <sstream>
#include <iomanip>

using namespace std::chrono;

std::string
isc::util::clockToText(system_clock::time_point t, size_t fsecs_precision) {
    time_t tt = system_clock::to_time_t(t);
    struct tm tm;
    localtime_r(&tt, &tm);
    std::stringstream s;
    s << (tm.tm_year + 1900)
      << "-" << std::setw(2) << std::setfill('0') << (tm.tm_mon + 1)
      << "-" << std::setw(2) << std::setfill('0') << tm.tm_mday
      << " " << std::setw(2) << std::setfill('0') << tm.tm_hour
      << ":" << std::setw(2) << std::setfill('0') << tm.tm_min
      << ":" << std::setw(2) << std::setfill('0') << tm.tm_sec;

    // If the requested precision is less than the maximum native precision
    // we will divide the fractional seconds value by 10^(max - requested)
    if (fsecs_precision) {
        microseconds frac = t - system_clock::from_time_t(tt);
        auto fsecs = frac.count();
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

std::string
isc::util::durationToText(system_clock::duration dur, size_t fsecs_precision) {
    seconds unfrac = duration_cast<seconds>(dur);
    auto secs = unfrac.count();
    std::stringstream s;
    auto hours = secs / 3600;
    secs -= hours * 3600;
    s << std::setw(2) << std::setfill('0') << hours;
    auto mins = secs / 60;
    secs -= mins * 60;
    s << ":" << std::setw(2) << std::setfill('0') << mins
      << ":" << std::setw(2) << std::setfill('0') << secs;

    // If the requested precision is less than the maximum native precision
    // we will divide the fractional seconds value by 10^(max - requested)
    if (fsecs_precision) {
        microseconds frac = dur - unfrac;
        auto fsecs = frac.count();
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
