// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/parsers/sanity_checks_parser.h>
#include <dhcpsrv/cfg_consistency.h>
#include <cc/data.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

void
SanityChecksParser::parse(SrvConfig& cfg, const ConstElementPtr& sanity_checks) {

    if (!sanity_checks) {
        return;
    }
    if (sanity_checks->getType() != Element::map) {
        isc_throw(DhcpConfigError, "sanity-checks is supposed to be a map");
    }

    // Subnet-id lease checker.
    ConstElementPtr checks = sanity_checks->get("lease-checks");
    if (checks) {
        if (checks->getType() != Element::string) {
            isc_throw(DhcpConfigError, "lease-checks must be a string");
        }
        std::string lc = checks->stringValue();
        CfgConsistency::LeaseSanity check;
        if (lc == "none") {
            check = CfgConsistency::LEASE_CHECK_NONE;
        } else if (lc == "warn") {
            check = CfgConsistency::LEASE_CHECK_WARN;
        } else if (lc == "fix") {
            check = CfgConsistency::LEASE_CHECK_FIX;
        } else if (lc == "fix-del") {
            check = CfgConsistency::LEASE_CHECK_FIX_DEL;
        } else if (lc == "del") {
            check = CfgConsistency::LEASE_CHECK_DEL;
        } else {
            isc_throw(DhcpConfigError, "Unsupported lease-checks value: " << lc
                      << ", supported values are: none, warn, fix, fix-del, del");
        }
        cfg.getConsistency()->setLeaseSanityCheck(check);
    }

    // Extended info lease checker.
    checks = sanity_checks->get("extended-info-checks");
    if (checks) {
        if (checks->getType() != Element::string) {
            isc_throw(DhcpConfigError, "extended-info-checks must be a string");
        }
        std::string exc = checks->stringValue();
        CfgConsistency::ExtendedInfoSanity check;
        if (exc == "none") {
            check = CfgConsistency::EXTENDED_INFO_CHECK_NONE;
        } else if (exc == "fix") {
            check = CfgConsistency::EXTENDED_INFO_CHECK_FIX;
        } else if (exc == "strict") {
            check = CfgConsistency::EXTENDED_INFO_CHECK_STRICT;
        } else if (exc == "pedantic") {
            check = CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC;
        } else {
            isc_throw(DhcpConfigError,
                      "Unsupported extended-info-checks value: " << exc
                      << ", supported values are: none, fix, strict, pedantic");
        }
        cfg.getConsistency()->setExtendedInfoSanityCheck(check);
    }

    // Additional sanity check fields will come in later here.
}

}
}
