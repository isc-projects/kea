// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "base64.h"
#include "buffer.h"
#include "messagerenderer.h"
#include "name.h"
#include "rrtype.h"
#include "rrttl.h"
#include "rdata.h"
#include "rdataclass.h"
#include <boost/lexical_cast.hpp>

#include <stdio.h>
#include <time.h>

#include "dnstime.h"

using namespace std;

namespace isc {
namespace dns {

enum {
    DATE_LEN = 14       // YYYYMMDDHHmmSS
};

string
DNSSECTimeToText(const time_t timeval)
{
    struct tm *t = gmtime(&timeval);

    ostringstream oss;
    oss << setfill('0')
        << setw(4) << t->tm_year + 1900
        << setw(2) << t->tm_mon + 1
        << setw(2) << t->tm_mday 
        << setw(2) << t->tm_hour
        << setw(2) << t->tm_min
        << setw(2) << t->tm_sec;
    return (oss.str());
}

static inline void
checkRange(int min, int max, int value, const string& valname) {
    if ((value >= min) && (value <= max)) {
        return;
    }
    ostringstream oss;
    oss << "Invalid " << valname << " value: " << value;
    dns_throw(InvalidTime, oss.str().c_str());
}

static int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static inline bool
isLeap(int y) {
    return ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0);
}

time_t
DNSSECTimeFromText(const string& time_txt)
{
    time_t timeval;

    // first try reading YYYYMMDDHHmmSS format
    int year, month, day, hour, minute, second;
    if (time_txt.length() != DATE_LEN ||
        sscanf(time_txt.c_str(), "%4d%2d%2d%2d%2d%2d",
               &year, &month, &day, &hour, &minute, &second) != 6)
    {
        ostringstream oss;
        oss << "Couldn't convert time value: " << time_txt;
        dns_throw(InvalidTime, oss.str().c_str());
    }

    checkRange(1970, 9999, year, "year");
    checkRange(1, 12, month, "month");
    checkRange(1, days[month - 1] + ((month == 2 && isLeap(year)) ? 1 : 0),
            day, "day");
    checkRange(0, 23, hour, "hour");
    checkRange(0, 59, minute, "minute");
    checkRange(0, 60, second, "second"); // 60 == leap second.

    timeval = second + (60 * minute) + (3600 * hour) + ((day - 1) * 86400);
    for (int m = 0; m < (month - 1); m++) {
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
}
}
