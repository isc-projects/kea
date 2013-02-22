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

#include "statistics_util.h"

#include <gtest/gtest.h>

#include <string>
#include <map>

namespace {
void
flatten(std::map<std::string, int>& flat_map, const std::string& prefix,
        const isc::data::ConstElementPtr map_element)
{
    std::map<std::string, isc::data::ConstElementPtr> map =
        map_element->mapValue();
    for (std::map<std::string, isc::data::ConstElementPtr>::const_iterator
             i = map.begin(), e = map.end();
         i != e;
         ++i)
    {
        switch (i->second->getType()) {
            case isc::data::Element::map:
                flatten(flat_map, i->first + ".", i->second);
                break;
            case isc::data::Element::integer:
                flat_map[prefix + i->first] = i->second->intValue();
                break;
            default:
                FAIL() << "Element Parse Error";
        }
    }
}
}

namespace isc {
namespace auth {
namespace unittest {

void
checkStatisticsCounters(const isc::data::ConstElementPtr counters,
                        const std::map<std::string, int>& expect)
{
    std::map<std::string, int> stats_map;
    flatten(stats_map, "", counters);

    for (std::map<std::string, int>::const_iterator
            i = stats_map.begin(), e = stats_map.end();
            i != e;
            ++i)
    {
        const int value =
            expect.find(i->first) == expect.end() ?
                0 : expect.find(i->first)->second;
        EXPECT_EQ(value, i->second) << "Expected counter "
            << i->first << " = " << value << ", actual: "
            << i->second;
    }
}

} // end of unittest
} // end of auth
} // end of isc
