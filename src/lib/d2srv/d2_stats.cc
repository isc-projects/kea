// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the top-level component of kea-dhcp-ddns.

#include <config.h>

#include <d2srv/d2_stats.h>
#include <stats/stats_mgr.h>

using namespace std;
using namespace isc::stats;

namespace isc {
namespace d2 {

const list<string>
D2Stats::ncr = {
    "ncr-received",
    "ncr-invalid",
    "ncr-error"
};

const list<string>
D2Stats::update = {
    "update-sent",
    "update-signed",
    "update-unsigned",
    "update-success",
    "update-timeout",
    "update-error"
};

const list<string>
D2Stats::key = {
    "update-sent",
    "update-success",
    "update-timeout",
    "update-error"
};

void
D2Stats::init() {
    StatsMgr& stats_mgr = isc::stats::StatsMgr::instance();
    stats_mgr.setMaxSampleCountDefault(0);
    for (const auto& name : D2Stats::ncr) {
        stats_mgr.setValue(name, static_cast<int64_t>(0));
    }
    for (const auto& name : D2Stats::update) {
        stats_mgr.setValue(name, static_cast<int64_t>(0));
    }
};

} // namespace d2
} // namespace isc
