// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_globals.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

const std::map<std::string, int>
CfgGlobals::nameToIndex = {
    // Common parameters.
    { "valid-lifetime", VALID_LIFETIME },
    { "min-valid-lifetime", MIN_VALID_LIFETIME },
    { "max-valid-lifetime", MAX_VALID_LIFETIME },
    { "renew-timer", RENEW_TIMER },
    { "rebind-timer", REBIND_TIMER },
    { "decline-probation-period", DECLINE_PROBATION_PERIOD },
    { "dhcp4o6-port", DHCP4O6_PORT },
    { "comment", COMMENT },
    { "server-tag", SERVER_TAG },
    { "reservation-mode", RESERVATION_MODE },
    { "reservations-global", RESERVATIONS_GLOBAL },
    { "reservations-in-subnet", RESERVATIONS_IN_SUBNET },
    { "reservations-out-of-pool", RESERVATIONS_OUT_OF_POOL },
    { "calculate-tee-times", CALCULATE_TEE_TIMES },
    { "t1-percent", T1_PERCENT },
    { "t2-percent", T2_PERCENT },
    { "hostname-char-set", HOSTNAME_CHAR_SET },
    { "hostname-char-replacement", HOSTNAME_CHAR_REPLACEMENT },
    { "ddns-send-updates", DDNS_SEND_UPDATES },
    { "ddns-override-no-update", DDNS_OVERRIDE_NO_UPDATE },
    { "ddns-override-client-update", DDNS_OVERRIDE_CLIENT_UPDATE },
    { "ddns-replace-client-name", DDNS_REPLACE_CLIENT_NAME },
    { "ddns-generated-prefix", DDNS_GENERATED_PREFIX },
    { "ddns-qualifying-suffix", DDNS_QUALIFYING_SUFFIX },
    { "store-extended-info", STORE_EXTENDED_INFO },
    { "statistic-default-sample-count", STATISTIC_DEFAULT_SAMPLE_COUNT },
    { "statistic-default-sample-age", STATISTIC_DEFAULT_SAMPLE_AGE },
    { "cache-threshold", CACHE_THRESHOLD },
    { "cache-max-age", CACHE_MAX_AGE },
    { "early-global-reservations-lookup", EARLY_GLOBAL_RESERVATIONS_LOOKUP },
    { "ip-reservations-unique", IP_RESERVATIONS_UNIQUE },
    { "reservations-lookup-first", RESERVATIONS_LOOKUP_FIRST },
    { "ddns-update-on-renew", DDNS_UPDATE_ON_RENEW },
    { "ddns-use-conflict-resolution", DDNS_USE_CONFLICT_RESOLUTION },
    { "parked-packet-limit", PARKED_PACKET_LIMIT },

    // DHCPv4 specific parameters.
    { "echo-client-id", ECHO_CLIENT_ID },
    { "match-client-id", MATCH_CLIENT_ID },
    { "authoritative", AUTHORITATIVE },
    { "next-server", NEXT_SERVER },
    { "server-hostname", SERVER_HOSTNAME },
    { "boot-file-name", BOOT_FILE_NAME },

    // DHCPv6 specific parameters.
    { "data-directory", DATA_DIRECTORY },
    { "preferred-lifetime", PREFERRED_LIFETIME },
    { "min-preferred-lifetime", MIN_PREFERRED_LIFETIME },
    { "max-preferred-lifetime", MAX_PREFERRED_LIFETIME }
};

// Load time sanity check.
namespace {
struct CfgGlobalsChecks {
    CfgGlobalsChecks() {
        // Check the size for missing entries.
        if (CfgGlobals::nameToIndex.size() != CfgGlobals::SIZE) {
            isc_throw(Unexpected, "CfgGlobals::nameToIndex has "
                      << CfgGlobals::nameToIndex.size()
                      << " elements (expected " << CfgGlobals::SIZE << ")");
        }

        // Build the name vector.
        std::vector<std::string> names;
        names.resize(CfgGlobals::SIZE);
        for (auto it = CfgGlobals::nameToIndex.cbegin();
             it != CfgGlobals::nameToIndex.cend(); ++it) {
            int idx = it->second;
            if ((idx < 0) || (idx >= CfgGlobals::SIZE)) {
                isc_throw(Unexpected, "invalid index " << idx
                          << " for name " << it->first);
            }
            if (!names[idx].empty()) {
                isc_throw(Unexpected, "duplicated names for " << idx
                          << " got " << names[idx]);
            }
            names[idx] = it->first;
        }

        // No name should be empty.
        for (int idx = 0; idx < CfgGlobals::SIZE; ++idx) {
            if (names[idx].empty()) {
                isc_throw(Unexpected, "missing name for " << idx);
            }
        }
    }
};

CfgGlobalsChecks check;
} // end of anonymous namespace

CfgGlobals::CfgGlobals() : values_(SIZE) {
}

ConstElementPtr
CfgGlobals::get(const std::string& name) const {
    auto const& it = nameToIndex.find(name);
    if (it == nameToIndex.cend()) {
        isc_throw(NotFound, "invalid global parameter name '" << name << "'");
    }
    return (get(it->second));
}

ConstElementPtr
CfgGlobals::get(int index) const {
    if ((index < 0) || (index >= CfgGlobals::SIZE)) {
        isc_throw(OutOfRange, "invalid global parameter index " << index);
    }
    return (values_[index]);
}

void
CfgGlobals::set(const std::string& name, ConstElementPtr value) {
    auto const& it = nameToIndex.find(name);
    if (it == nameToIndex.cend()) {
        isc_throw(NotFound, "invalid global parameter name '" << name << "'");
    }
    set(it->second, value);
}

void
CfgGlobals::set(int index, ConstElementPtr value) {
    if ((index < 0) || (index >= CfgGlobals::SIZE)) {
        isc_throw(OutOfRange, "invalid global parameter index " << index);
    }
    values_[index] = value;
}

void
CfgGlobals::clear() {
    for (int idx = 0; idx < CfgGlobals::SIZE; ++idx) {
        if (values_[idx]) {
            values_[idx] = ConstElementPtr();
        }
    }
}

const CfgGlobals::MapType
CfgGlobals::valuesMap() const {
    MapType map;
    for (auto it = nameToIndex.cbegin(); it != nameToIndex.cend(); ++it) {
        int idx = it->second;
        ConstElementPtr value = values_[idx];
        if (value) {
            map.insert(make_pair(it->first, value));
        }
    }
    return (map);
}

ElementPtr
CfgGlobals::toElement() const {
    ElementPtr result = Element::createMap();
    for (auto it = nameToIndex.cbegin(); it != nameToIndex.cend(); ++it) {
        int idx = it->second;
        ConstElementPtr value = values_[idx];
        if (value) {
            result->set(it->first, value);
        }
    }
    return (result);
}

} // namespace isc::dhcp
} // namespace isc
