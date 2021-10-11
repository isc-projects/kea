// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_STATS_TEST_UTILS_H
#define D2_STATS_TEST_UTILS_H

#include <cc/data.h>
#include <d2srv/d2_stats.h>
#include <d2srv/d2_tsig_key.h>
#include <stats/testutils/stats_test_utils.h>

#include <gtest/gtest.h>

namespace isc {
namespace d2 {
namespace test {

/// @brief Import statistic test utils.
using isc::stats::test::StatMap;
using isc::stats::test::checkStat;
using isc::stats::test::checkStats;

/// @brief Test class with utility functions to test statistics.
class D2StatTest {
public:
    /// @brief Constructor.
    D2StatTest();

    /// @brief Destructor.
    virtual ~D2StatTest();
};

/// @brief Compares StatsMgr key statistics against expected values.
///
/// Prepend key part of names before calling checkStats simpler variant.
///
/// @param key_name Name of the key.
/// @param expected_stats Map of expected static names and values.
void checkStats(const std::string& key_name, const StatMap& expected_stats);

}
}
}

#endif // D2_STATS_TEST_UTILS_H
