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
#include <dhcpsrv/srv_config.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <list>
#include <sstream>

using namespace isc::log;

namespace isc {
namespace dhcp {

SrvConfig::SrvConfig()
    : sequence_(0), cfg_option_def_(new CfgOptionDef()),
      cfg_option_(new CfgOption()) {
}

SrvConfig::SrvConfig(const uint32_t sequence)
    : sequence_(sequence), cfg_option_def_(new CfgOptionDef()),
      cfg_option_(new CfgOption()) {
}

std::string
SrvConfig::getConfigSummary(const uint32_t selection) const {
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
SrvConfig::sequenceEquals(const SrvConfig& other) {
    return (getSequence() == other.getSequence());
}

void
SrvConfig::copy(SrvConfig& new_config) const {
    // We will entirely replace loggers in the new configuration.
    new_config.logging_info_.clear();
    for (LoggingInfoStorage::const_iterator it = logging_info_.begin();
         it != logging_info_.end(); ++it) {
        new_config.addLoggingInfo(*it);
    }
    // Replace interface configuration.
    new_config.setCfgIface(cfg_iface_);
    // Replace option definitions.
    cfg_option_def_->copyTo(*new_config.cfg_option_def_);
    cfg_option_->copyTo(*new_config.cfg_option_);
}

void
SrvConfig::applyLoggingCfg() const {

    std::list<LoggerSpecification> specs;
    for (LoggingInfoStorage::const_iterator it = logging_info_.begin();
         it != logging_info_.end(); ++it) {
        specs.push_back(it->toSpec());
    }
    LoggerManager manager;
    manager.process(specs.begin(), specs.end());
}

bool
SrvConfig::equals(const SrvConfig& other) const {
    // If number of loggers is different, then configurations aren't equal.
    if (logging_info_.size() != other.logging_info_.size()) {
        return (false);
    }
    // Pass through all loggers and try to find the match for each of them
    // with the loggers from the other configuration. The order doesn't
    // matter so we can't simply compare the vectors.
    for (LoggingInfoStorage::const_iterator this_it =
             logging_info_.begin(); this_it != logging_info_.end();
         ++this_it) {
        bool match = false;
        for (LoggingInfoStorage::const_iterator other_it =
                 other.logging_info_.begin();
             other_it != other.logging_info_.end(); ++other_it) {
            if (this_it->equals(*other_it)) {
                match = true;
                break;
            }
        }
        // No match found for the particular logger so return false.
        if (!match) {
            return (false);
        }
    }
    // Logging information is equal between objects, so check other values.
    return ((cfg_iface_ == other.cfg_iface_) &&
            (*cfg_option_def_ == *other.cfg_option_def_) &&
            (*cfg_option_ == *other.cfg_option_));
}

}
}
