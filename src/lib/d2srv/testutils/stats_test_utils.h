// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STATS_TEST_UTILS_H
#define STATS_TEST_UTILS_H

#include <cc/data.h>
#include <d2srv/d2_stats.h>
#include <d2srv/d2_tsig_key.h>
#include <stats/stats_mgr.h>

#include <gtest/gtest.h>

namespace isc {
namespace d2 {
namespace test {

/// @brief Type of name x value for statistics.
typedef std::map<std::string, int64_t> StatMap;

/// @brief Test class with utility functions to test statistics.
class D2StatTest {
public:
    /// @brief Constructor.
    D2StatTest();

    /// @brief Destructor.
    virtual ~D2StatTest();

    /// @brief Compares a statistic to an expected value.
    ///
    /// Attempt to fetch the named statistic from the StatsMgr and if
    /// found, compare its observed value to the given value.
    /// Fails if the stat is not found or if the values do not match.
    ///
    /// @param name StatsMgr name for the statistic to check.
    /// @param expected_value expected value of the statistic.
    void checkStat(const std::string& name, const int64_t expected_value);

    /// @brief Compares StatsMgr statistics against expected values.
    ///
    /// Iterates over a list of statistic names and expected values, attempting
    /// to fetch each from the StatsMgr and if found, compare its observed
    /// value to the expected value. Fails if any of the expected stats are not
    /// found or if the values do not match.
    ///
    /// @param expected_stats Map of expected static names and values.
    void checkStats(const StatMap& expected_stats);

    /// @brief Compares StatsMgr key statistics against expected values.
    ///
    /// Prepend key part of names before calling checkStats simpler variant.
    ///
    /// @param key_name Name of the key.
    /// @param expected_stats Map of expected static names and values.
    void checkStats(const std::string& key_name, const StatMap& expected_stats);
};

}
}
}

#endif // STATS_TEST_UTILS_H
