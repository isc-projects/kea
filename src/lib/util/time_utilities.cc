// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <sys/time.h>

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <time.h>

#include <exceptions/exceptions.h>

#include <util/time_utilities.h>

using namespace std;

namespace {
int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

inline bool
isLeap(const int y) {
    return ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0);
}

unsigned int
yearSecs(const int year) {
    return ((isLeap(year) ? 366 : 365 ) * 86400);
}

unsigned int
monthSecs(const int month, const int year) {
    return ((days[month] + ((month == 1 && isLeap(year)) ? 1 : 0 )) * 86400);
}
}

namespace isc {
namespace util {

string
timeToText64(uint64_t value) {
    struct tm tm;
    unsigned int secs;

    // We cannot rely on gmtime() because time_t may not be of 64 bit
    // integer.  The following conversion logic is borrowed from BIND 9.
    tm.tm_year = 70;
    while ((secs = yearSecs(tm.tm_year + 1900)) <= value) {
        value -= secs;
        ++tm.tm_year;
        if (tm.tm_year + 1900 > 9999) {
            isc_throw(InvalidTime,
                      "Time value out of range (year > 9999): " <<
                      tm.tm_year + 1900);
        }
    }
    tm.tm_mon = 0;
    while ((secs = monthSecs(tm.tm_mon, tm.tm_year + 1900)) <= value) {
        value -= secs;
        tm.tm_mon++;
    }
    tm.tm_mday = 1;
    while (86400 <= value) {
        value -= 86400;
        ++tm.tm_mday;
    }
    tm.tm_hour = 0;
    while (3600 <= value) {
        value -= 3600;
        ++tm.tm_hour;
    }
    tm.tm_min = 0;
    while (60 <= value) {
        value -= 60;
        ++tm.tm_min;
    }
    tm.tm_sec = value;    // now t < 60, so this substitution is safe.

    ostringstream oss;
    oss << setfill('0')
        << setw(4) << tm.tm_year + 1900
        << setw(2) << tm.tm_mon + 1
        << setw(2) << tm.tm_mday
        << setw(2) << tm.tm_hour
        << setw(2) << tm.tm_min
        << setw(2) << tm.tm_sec;
    return (oss.str());
}

// timeToText32() below uses the current system time.  To test it with
// unusual current time values we introduce the following function pointer;
// when it's non NULL, we call it to get the (normally faked) current time.
// Otherwise we use the standard gettimeofday(2).  This hook is specifically
// intended for testing purposes, so, even if it's visible outside of this
// library, it's not even declared in a header file.
namespace detail {
int64_t (*gettimeFunction)() = NULL;

int64_t
gettimeWrapper() {
    if (gettimeFunction != NULL) {
        return (gettimeFunction());
    }

    struct timeval now;
    gettimeofday(&now, NULL);

    return (static_cast<int64_t>(now.tv_sec));
}
}

string
timeToText32(const uint32_t value) {
    // We first adjust the time to the closest epoch based on the current time.
    // Note that the following variables must be signed in order to handle
    // time until year 2038 correctly.
    const int64_t start = detail::gettimeWrapper() - 0x7fffffff;
    int64_t base = 0;
    int64_t t;
    while ((t = (base + value)) < start) {
        base += 0x100000000LL;
    }

    // Then convert it to text.
    return (timeToText64(t));
}

namespace {
const size_t DATE_LEN = 14;      // YYYYMMDDHHmmSS

inline void
checkRange(const int min, const int max, const int value,
           const string& valname)
{
    if ((value >= min) && (value <= max)) {
        return;
    }
    isc_throw(InvalidTime, "Invalid " << valname << " value: " << value);
}
}

uint64_t
timeFromText64(const string& time_txt) {
    // Confirm the source only consists digits.  sscanf() allows some
    // minor exceptions.
    for (string::size_type i = 0; i < time_txt.length(); ++i) {
        if (!isdigit(time_txt.at(i))) {
            isc_throw(InvalidTime, "Couldn't convert non-numeric time value: "
                      << time_txt);
        }
    }

    int year, month, day, hour, minute, second;
    if (time_txt.length() != DATE_LEN ||
        sscanf(time_txt.c_str(), "%4d%2d%2d%2d%2d%2d",
               &year, &month, &day, &hour, &minute, &second) != 6)
    {
        isc_throw(InvalidTime, "Couldn't convert time value: " << time_txt);
    }

    checkRange(1970, 9999, year, "year");
    checkRange(1, 12, month, "month");
    checkRange(1, days[month - 1] + ((month == 2 && isLeap(year)) ? 1 : 0),
            day, "day");
    checkRange(0, 23, hour, "hour");
    checkRange(0, 59, minute, "minute");
    checkRange(0, 60, second, "second"); // 60 == leap second.

    uint64_t timeval = second + (60 * minute) + (3600 * hour) +
        ((day - 1) * 86400);
    for (int m = 0; m < (month - 1); ++m) {
            timeval += days[m] * 86400;
    }
    if (isLeap(year) && month > 2) {
            timeval += 86400;
    }
    for (int y = 1970; y < year; ++y) {
        timeval += ((isLeap(y) ? 366 : 365 ) * 86400);
    }

    return (timeval);
}

uint32_t
timeFromText32(const string& time_txt) {
    // The implicit conversion from uint64_t to uint32_t should just work here,
    // because we only need to drop higher 32 bits.
    return (timeFromText64(time_txt));
}

}
}
