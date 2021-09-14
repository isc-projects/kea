// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the top-level component of kea-dhcp-ddns.

#include <config.h>

#include <d2srv/d2_stats.h>
#include <d2srv/d2_tsig_key.h>
#include <stats/stats_mgr.h>

using namespace isc::dns;
using namespace isc::stats;
using namespace std;

namespace isc {
namespace d2 {

D2TsigKey::D2TsigKey(const std::string& key_spec) : TSIGKey(key_spec) {
    initStats();
}

D2TsigKey::D2TsigKey(const Name& key_name, const Name& algorithm_name,
                     const void* secret, size_t secret_len, size_t digestbits)
    : TSIGKey(key_name, algorithm_name, secret, secret_len, digestbits) {
    initStats();
}

D2TsigKey::~D2TsigKey() {
    removeStats();
}

void
D2TsigKey::initStats() {
    StatsMgr& stats_mgr = StatsMgr::instance();
    const string& kname = getKeyName().toText();
    for (const auto& name : D2Stats::key) {
        const string& sname = StatsMgr::generateName("key", kname, name);
        stats_mgr.setValue(sname, static_cast<int64_t>(0));
    }
}

void
D2TsigKey::removeStats() {
    StatsMgr& stats_mgr = StatsMgr::instance();
    const string& kname = getKeyName().toText();
    for (const auto& name : D2Stats::key) {
        string sname = StatsMgr::generateName("key", kname, name);
        stats_mgr.del(sname);
    }
}

void
D2TsigKey::resetStats() {
    StatsMgr& stats_mgr = StatsMgr::instance();
    const string& kname = getKeyName().toText();
    for (const auto& name : D2Stats::key) {
        string sname = StatsMgr::generateName("key", kname, name);
        stats_mgr.reset(sname);
    }
}

TSIGContextPtr
D2TsigKey::createContext() {
    return (TSIGContextPtr(new TSIGContext(*this)));
}

} // namespace d2
} // namespace isc
