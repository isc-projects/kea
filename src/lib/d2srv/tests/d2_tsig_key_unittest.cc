// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <d2srv/d2_tsig_key.h>
#include <stats/stats_mgr.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace isc::d2;
using namespace isc::data;
using namespace isc::stats;
using namespace std;

namespace {

/// @brief Fixture class for TSIG key / DNS update statictics.
class D2TsigKeyTest : public ::testing::Test {
public:
    /// @brief Constructor.
    D2TsigKeyTest() {
        StatsMgr::instance();
        StatsMgr::instance().removeAll();
        StatsMgr::instance().setMaxSampleCountDefault(0);
    }

    /// @brief Destructor.
    ~D2TsigKeyTest() {
        StatsMgr::instance().removeAll();
        StatsMgr::instance().setMaxSampleCountDefault(0);
    }
};

/// @brief Check TSIG key life.
TEST_F(D2TsigKeyTest, key) {
    // Statistics names.
    ASSERT_EQ(5, D2TsigKey::keyStats.size());
    ASSERT_EQ(6, D2TsigKey::globalStats.size());

    // Get the statistics manager.
    StatsMgr& stat_mgr = StatsMgr::instance();
    ASSERT_EQ(0, stat_mgr.count());

    // Create a key.
    const string& key_spec = "foo.bar.::test";
    D2TsigKeyPtr key(new D2TsigKey(key_spec));
    EXPECT_EQ(5, stat_mgr.count());

    // Get the 'sent' statistics.
    const string& stat_name = "key[foo.bar.].sent";
    EXPECT_EQ(1, stat_mgr.getSize(stat_name));
    ObservationPtr stat = stat_mgr.getObservation(stat_name);
    ASSERT_TRUE(stat);
    IntegerSample sample;
    ASSERT_NO_THROW(sample = stat->getInteger());
    EXPECT_EQ(0, sample.first);

    // Increment the 'sent' statistics.
    stat_mgr.addValue(stat_name, static_cast<int64_t>(1));
    stat = stat_mgr.getObservation(stat_name);
    ASSERT_TRUE(stat);
    ASSERT_NO_THROW(sample = stat->getInteger());
    EXPECT_EQ(1, sample.first);

    // Reset the key statistics.
    ASSERT_NO_THROW(key->resetStats());
    stat = stat_mgr.getObservation(stat_name);
    ASSERT_TRUE(stat);
    ASSERT_NO_THROW(sample = stat->getInteger());
    EXPECT_EQ(0, sample.first);

    // Destroy the key: its stats are removed.
    key.reset();
    EXPECT_EQ(0, stat_mgr.count());
    stat = stat_mgr.getObservation(stat_name);
    EXPECT_FALSE(stat);
}

} // end of anonymous namespace
