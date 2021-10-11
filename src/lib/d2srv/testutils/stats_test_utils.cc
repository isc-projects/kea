// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>

#include <d2srv/d2_stats.h>
#include <d2srv/testutils/stats_test_utils.h>

using namespace isc::data;
using namespace isc::stats;
using namespace std;

namespace isc {
namespace d2 {
namespace test {

D2StatTest::D2StatTest() {
    StatsMgr::instance().removeAll();
    D2Stats::init();
}

D2StatTest::~D2StatTest() {
    StatsMgr::instance().removeAll();
}

void
checkStats(const string& key_name, const StatMap& expected_stats) {
    StatMap key_stats;
    for (const auto& it : expected_stats) {
        const string& stat_name =
            StatsMgr::generateName("key", key_name, it.first);
        key_stats[stat_name] = it.second;
    }
    checkStats(key_stats);
}

}
}
}
