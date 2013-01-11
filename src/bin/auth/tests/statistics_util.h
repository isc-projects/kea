// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __AUTH_STATISTICS_UTIL_H
#define __AUTH_STATISTICS_UTIL_H 1

#include <cc/data.h>

namespace isc {
namespace auth {
namespace unittest {

// Test if the counters has expected values specified in expect and the others
// are zero.
void
checkStatisticsCounters(const isc::data::ConstElementPtr counters,
                        const std::map<std::string, int>& expect);

} // end of unittest
} // end of auth
} // end of isc

#endif  // __AUTH_STATISTICS_UTIL_H

// Local Variables:
// mode: c++
// End:
