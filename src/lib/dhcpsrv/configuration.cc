// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/configuration.h>
#include <sstream>

namespace isc {
namespace dhcp {

Configuration::Configuration()
    : sequence_(0) {
}

Configuration::Configuration(uint32_t sequence)
    : sequence_(sequence) {
}

std::string
Configuration::getConfigSummary(const uint32_t selection) const {
    std::ostringstream s;
    size_t subnets_num;
    if ((selection & CFGSEL_SUBNET4) == CFGSEL_SUBNET4) {
        subnets_num = CfgMgr::instance().getSubnets4()->size();
        if (subnets_num > 0) {
            s << "added IPv4 subnets: " << subnets_num;
        } else {
            s << "no IPv4 subnets!";
        }
        s << "; ";
    }

    if ((selection & CFGSEL_SUBNET6) == CFGSEL_SUBNET6) {
        subnets_num = CfgMgr::instance().getSubnets6()->size();
        if (subnets_num > 0) {
            s << "added IPv6 subnets: " << subnets_num;
        } else {
            s << "no IPv6 subnets!";
        }
        s << "; ";
    }

    if ((selection & CFGSEL_DDNS) == CFGSEL_DDNS) {
        bool ddns_enabled = CfgMgr::instance().ddnsEnabled();
        s << "DDNS: " << (ddns_enabled ? "enabled" : "disabled") << "; ";
    }

    if (s.tellp() == static_cast<std::streampos>(0)) {
        s << "no config details available";
    }

    std::string summary = s.str();
    size_t last_separator_pos = summary.find_last_of(";");
    if (last_separator_pos == summary.length() - 2) {
        summary.erase(last_separator_pos);
    }
    return (summary);
}

bool
Configuration::sequenceEquals(const Configuration& other) {
    return (getSequence() == other.getSequence());
}

}
}
