// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STATS_TEST_UTILS_H
#define STATS_TEST_UTILS_H

#include <cc/data.h>
#include <stats/stats_mgr.h>

#include <gtest/gtest.h>

namespace isc {
namespace stats {
namespace test {

/// @brief Type of name x value for statistics.
typedef std::map<std::string, int64_t> StatMap;

/// @brief Compares a statistic to an expected value.
///
/// Attempt to fetch the named statistic from the StatsMgr and if
/// found, compare its observed value to the given value.
/// Fails if the stat is not found or if the values do not match.
///
/// @param name StatsMgr name for the statistic to check.
/// @param expected_value expected value of the statistic.
inline void checkStat(const std::string& name, const int64_t expected_value) {
    using namespace isc::stats;
    ObservationPtr obs = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(obs) << " stat: " << name << " not found ";
    ASSERT_EQ(expected_value, obs->getInteger().first)
        << " stat: " << name << " value wrong";
}

/// @brief Check if a statistic does not exists.
///
/// @param name StatsMgr name for the statistic to check.
inline void checkNoStat(const std::string& name) {
    using namespace isc::stats;
    EXPECT_FALSE(StatsMgr::instance().getObservation(name));
}

/// @brief Compares StatsMgr statistics against expected values.
///
/// Iterates over a list of statistic names and expected values, attempting
/// to fetch each from the StatsMgr and if found, compare its observed
/// value to the expected value. Fails if any of the expected stats are not
/// found or if the values do not match.
///
/// @param expected_stats Map of expected static names and values.
inline void checkStats(const StatMap& expected_stats) {
    for (const auto& it : expected_stats) {
        checkStat(it.first, it.second);
    }
}

}
}
}

#endif // STATS_TEST_UTILS_H
