// Copyright (C) 2012-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcp/option_custom.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <util/encode/hex.h>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

#include <time.h>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace isc {
namespace dhcp {

IOServicePtr LeaseMgr::io_service_ = IOServicePtr();

LeasePageSize::LeasePageSize(const size_t page_size)
    : page_size_(page_size) {

    if (page_size_ == 0) {
        isc_throw(OutOfRange, "page size of retrieved leases must not be 0");
    }

    if (page_size_ > std::numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "page size of retrieved leases must not be greater than "
                  << std::numeric_limits<uint32_t>::max());
    }
}

Lease6Ptr
LeaseMgr::getLease6(Lease::Type type, const DUID& duid,
                    uint32_t iaid, SubnetID subnet_id) const {
    Lease6Collection col = getLeases6(type, duid, iaid, subnet_id);

    if (col.size() > 1) {
        isc_throw(MultipleRecords, "More than one lease found for type "
                  << static_cast<int>(type) << ", duid "
                  << duid.toText() << ", iaid " << iaid
                  << " and subnet-id " << subnet_id);
    }
    if (col.empty()) {
        return (Lease6Ptr());
    }
    return (*col.begin());
}

void
LeaseMgr::recountLeaseStats4() {
    using namespace stats;

    StatsMgr& stats_mgr = StatsMgr::instance();

    LeaseStatsQueryPtr query = startLeaseStatsQuery4();
    if (!query) {
        /// NULL means not backend does not support recounting.
        return;
    }

    // Zero out the global stats.
    // Cumulative counters ("reclaimed-declined-addresses", "reclaimed-leases",
    // "cumulative-assigned-addresses") never get zeroed.
    int64_t zero = 0;
    stats_mgr.setValue("declined-addresses", zero);

    // Create if it does not exit reclaimed declined leases global stats.
    if (!stats_mgr.getObservation("reclaimed-declined-addresses")) {
        stats_mgr.setValue("reclaimed-declined-addresses", zero);
    }

    // Create if it does not exit reclaimed leases global stats.
    if (!stats_mgr.getObservation("reclaimed-leases")) {
        stats_mgr.setValue("reclaimed-leases", zero);
    }

    // Create if it does not exit cumulative global stats.
    if (!stats_mgr.getObservation("cumulative-assigned-addresses")) {
        stats_mgr.setValue("cumulative-assigned-addresses", zero);
    }

    // Clear subnet level stats.  This ensures we don't end up with corner
    // cases that leave stale values in place.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();

    for (Subnet4Collection::const_iterator subnet = subnets->begin();
         subnet != subnets->end(); ++subnet) {
        SubnetID subnet_id = (*subnet)->getID();
        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "assigned-addresses"),
                           zero);

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "declined-addresses"),
                           zero);

        if (!stats_mgr.getObservation(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-declined-addresses"))) {
            stats_mgr.setValue(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-declined-addresses"),
                zero);
        }

        if (!stats_mgr.getObservation(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-leases"))) {
            stats_mgr.setValue(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-leases"),
                zero);
        }
    }

    // Get counts per state per subnet. Iterate over the result set
    // updating the subnet and global values.
    LeaseStatsRow row;
    while (query->getNextRow(row)) {
        if (row.lease_state_ == Lease::STATE_DEFAULT) {
            // Add to subnet level value.
            stats_mgr.addValue(StatsMgr::generateName("subnet", row.subnet_id_,
                                                      "assigned-addresses"),
                               row.state_count_);
        } else if (row.lease_state_ == Lease::STATE_DECLINED) {
            // Set subnet level value.
            stats_mgr.setValue(StatsMgr::generateName("subnet", row.subnet_id_,
                                                      "declined-addresses"),
                               row.state_count_);

            // Add to the global value.
            stats_mgr.addValue("declined-addresses", row.state_count_);

            // Add to subnet level value.
            // Declined leases also count as assigned.
            stats_mgr.addValue(StatsMgr::generateName("subnet", row.subnet_id_,
                                                      "assigned-addresses"),
                               row.state_count_);
        }
    }
}

LeaseStatsQuery::LeaseStatsQuery()
    : first_subnet_id_(0), last_subnet_id_(0), select_mode_(ALL_SUBNETS) {
}

LeaseStatsQuery::LeaseStatsQuery(const SubnetID& subnet_id)
    : first_subnet_id_(subnet_id), last_subnet_id_(0),
    select_mode_(SINGLE_SUBNET) {

    if (first_subnet_id_ == 0) {
        isc_throw(BadValue, "LeaseStatsQuery: subnet_id_ must be > 0");
    }
}

LeaseStatsQuery::LeaseStatsQuery(const SubnetID& first_subnet_id,
                                 const SubnetID& last_subnet_id)
    : first_subnet_id_(first_subnet_id), last_subnet_id_(last_subnet_id),
    select_mode_(SUBNET_RANGE) {

    if (first_subnet_id_ == 0) {
        isc_throw(BadValue, "LeaseStatsQuery: first_subnet_id_ must be > 0");
    }

    if (last_subnet_id_ == 0) {
        isc_throw(BadValue, "LeaseStatsQuery: last_subnet_id_ must be > 0");
    }

    if (last_subnet_id_ <= first_subnet_id_) {
        isc_throw(BadValue,
                  "LeaseStatsQuery: last_subnet_id_must be > first_subnet_id_");
    }
}

LeaseStatsQueryPtr
LeaseMgr::startLeaseStatsQuery4() {
    return(LeaseStatsQueryPtr());
}

LeaseStatsQueryPtr
LeaseMgr::startSubnetLeaseStatsQuery4(const SubnetID& /* subnet_id */) {
    return(LeaseStatsQueryPtr());
}

LeaseStatsQueryPtr
LeaseMgr::startSubnetRangeLeaseStatsQuery4(const SubnetID& /* first_subnet_id */,
                                           const SubnetID& /* last_subnet_id */) {
    return(LeaseStatsQueryPtr());
}

bool
LeaseStatsQuery::getNextRow(LeaseStatsRow& /*row*/) {
    return (false);
}

void
LeaseMgr::recountLeaseStats6() {
    using namespace stats;

    StatsMgr& stats_mgr = StatsMgr::instance();

    LeaseStatsQueryPtr query = startLeaseStatsQuery6();
    if (!query) {
        /// NULL means not backend does not support recounting.
        return;
    }

    // Zero out the global stats.
    // Cumulative counters ("reclaimed-declined-addresses", "reclaimed-leases",
    // "cumulative-assigned-nas", "cumulative-assigned-pds") never get zeroed.
    int64_t zero = 0;
    stats_mgr.setValue("declined-addresses", zero);

    if (!stats_mgr.getObservation("reclaimed-declined-addresses")) {
        stats_mgr.setValue("reclaimed-declined-addresses", zero);
    }

    if (!stats_mgr.getObservation("reclaimed-leases")) {
        stats_mgr.setValue("reclaimed-leases", zero);
    }

    // Create if it does not exit cumulative nas global stats.
    if (!stats_mgr.getObservation("cumulative-assigned-nas")) {
        stats_mgr.setValue("cumulative-assigned-nas", zero);
    }

    // Create if it does not exit cumulative pds global stats.
    if (!stats_mgr.getObservation("cumulative-assigned-pds")) {
        stats_mgr.setValue("cumulative-assigned-pds", zero);
    }

    // Clear subnet level stats.  This ensures we don't end up with corner
    // cases that leave stale values in place.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();

    for (Subnet6Collection::const_iterator subnet = subnets->begin();
         subnet != subnets->end(); ++subnet) {
        SubnetID subnet_id = (*subnet)->getID();
        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "assigned-nas"),
                           zero);

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "declined-addresses"),
                           zero);

        if (!stats_mgr.getObservation(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-declined-addresses"))) {
            stats_mgr.setValue(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-declined-addresses"),
                zero);
        }

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "assigned-pds"),
                           zero);

        if (!stats_mgr.getObservation(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-leases"))) {
            stats_mgr.setValue(
                StatsMgr::generateName("subnet", subnet_id,
                                       "reclaimed-leases"),
                zero);
        }
    }

    // Get counts per state per subnet. Iterate over the result set
    // updating the subnet and global values.
    LeaseStatsRow row;
    while (query->getNextRow(row)) {
        switch(row.lease_type_) {
            case Lease::TYPE_NA:
                if (row.lease_state_ == Lease::STATE_DEFAULT) {
                    // Add to subnet level value.
                    stats_mgr.addValue(StatsMgr::
                                       generateName("subnet", row.subnet_id_,
                                                    "assigned-nas"),
                                       row.state_count_);
                } else if (row.lease_state_ == Lease::STATE_DECLINED) {
                    // Set subnet level value.
                    stats_mgr.setValue(StatsMgr::
                                       generateName("subnet", row.subnet_id_,
                                                    "declined-addresses"),
                                       row.state_count_);

                    // Add to the global value.
                    stats_mgr.addValue("declined-addresses", row.state_count_);

                    // Add to subnet level value.
                    // Declined leases also count as assigned.
                    stats_mgr.addValue(StatsMgr::
                                       generateName("subnet", row.subnet_id_,
                                                    "assigned-nas"),
                                       row.state_count_);
                }
                break;

            case Lease::TYPE_PD:
                if (row.lease_state_ == Lease::STATE_DEFAULT) {
                    // Set subnet level value.
                    stats_mgr.setValue(StatsMgr::
                                       generateName("subnet", row.subnet_id_,
                                                    "assigned-pds"),
                                       row.state_count_);
                }
                break;

            default:
                // We dont' support TYPE_TAs yet
                break;
        }
    }
}

LeaseStatsQueryPtr
LeaseMgr::startLeaseStatsQuery6() {
    return(LeaseStatsQueryPtr());
}

LeaseStatsQueryPtr
LeaseMgr::startSubnetLeaseStatsQuery6(const SubnetID& /* subnet_id */) {
    return(LeaseStatsQueryPtr());
}

LeaseStatsQueryPtr
LeaseMgr::startSubnetRangeLeaseStatsQuery6(const SubnetID& /* first_subnet_id */,
                                           const SubnetID& /* last_subnet_id */) {
    return(LeaseStatsQueryPtr());
}

std::string
LeaseMgr::getDBVersion() {
    isc_throw(NotImplemented, "LeaseMgr::getDBVersion() called");
}

bool
LeaseMgr::upgradeLease4ExtendedInfo(const Lease4Ptr& lease) {
    static OptionDefinitionPtr rai_def;

    bool changed = false;
    if (!lease) {
        return (changed);
    }

    ConstElementPtr user_context = lease->getContext();
    if (!user_context || (user_context->getType() != Element::map)) {
        return (changed);
    }

    ConstElementPtr isc = user_context->get("ISC");
    if (!isc || (isc->getType() != Element::map)) {
        return (changed);
    }

    ConstElementPtr extended_info = isc->get("relay-agent-info");
    if (!extended_info || (extended_info->getType() != Element::string)) {
        return (changed);
    }

    if (!rai_def) {
        rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                        DHO_DHCP_AGENT_OPTIONS);
    }

    if (!rai_def) {
        // The definition is set when libdhcp++ is loaded so it is impossible
        // to not be able to get it... so should not happen!
        isc_throw(Unexpected, "can't find RAI option definition?!");
    }

    changed = true;
    ElementPtr mutable_isc = boost::const_pointer_cast<Element>(isc);
    if (!mutable_isc) {
        // Should not happen...
        mutable_isc = Element::createMap();
        ElementPtr mutable_user_context =
            boost::const_pointer_cast<Element>(user_context);
        if (!mutable_user_context) {
            // Should not happen...
            mutable_user_context = Element::createMap();
            lease->setContext(mutable_user_context);
        }
        mutable_user_context->set("ISC", mutable_isc);
    }
    ElementPtr upgraded = Element::createMap();
    upgraded->set("sub-options", extended_info);
    mutable_isc->set("relay-agent-info", upgraded);

    // Try to decode sub-options.
    string rai_hex = extended_info->stringValue();
    if ((rai_hex.size() < 3) || (rai_hex[0] != '0') || (rai_hex[1] != 'x')) {
        return (changed);
    }
    try {
        vector<uint8_t> rai_data;
        encode::decodeHex(rai_hex.substr(2), rai_data);
        OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4, rai_data));
        if (!rai) {
            return (changed);
        }

        OptionPtr remote_id = rai->getOption(RAI_OPTION_REMOTE_ID);
        if (remote_id) {
            vector<uint8_t> bytes = remote_id->toBinary(false);
            if (bytes.size() > 0) {
                upgraded->set("remote-id",
                              Element::create(encode::encodeHex(bytes)));
            }
        }

        OptionPtr relay_id = rai->getOption(RAI_OPTION_RELAY_ID);
        if (relay_id) {
            vector<uint8_t> bytes = relay_id->toBinary(false);
            if (bytes.size() > 0) {
                upgraded->set("relay-id",
                              Element::create(encode::encodeHex(bytes)));
            }
        }

        return (changed);
    } catch (...) {
        return (changed);
    }
}

bool
LeaseMgr::upgradeLease6ExtendedInfo(const Lease6Ptr& lease) {
    bool changed = false;
    if (!lease) {
        return (changed);
    }

    ConstElementPtr user_context = lease->getContext();
    if (!user_context || (user_context->getType() != Element::map)) {
        return (changed);
    }

    ConstElementPtr isc = user_context->get("ISC");
    if (!isc || (isc->getType() != Element::map)) {
        return (changed);
    }

    ConstElementPtr extended_info = isc->get("relays");
    if (!extended_info || (extended_info->getType() != Element::list)) {
        return (changed);
    }

    changed = true;
    ElementPtr mutable_isc = boost::const_pointer_cast<Element>(isc);
    if (!mutable_isc) {
        // Should not happen...
        mutable_isc = Element::createMap();
        ElementPtr mutable_user_context =
            boost::const_pointer_cast<Element>(user_context);
        if (!mutable_user_context) {
            // Should not happen...
            mutable_user_context = Element::createMap();
            lease->setContext(mutable_user_context);
        }
        mutable_user_context->set("ISC", mutable_isc);
    }
    ElementPtr upgraded = copy(extended_info, 0);
    mutable_isc->set("relay-info", upgraded);
    mutable_isc->remove("relays");

    for (int i = 0; i < upgraded->size(); ++i) {
        ElementPtr relay = upgraded->getNonConst(i);
        if (!relay || (relay->getType() != Element::map)) {
            // Junk entry so just return instead continue...
            return (changed);
        }

        // Try to decode options.
        ConstElementPtr options = relay->get("options");
        if (!options) {
            continue;
        }
        if (options->getType() != Element::string) {
            return (changed);
        }
        string options_hex = options->stringValue();
        if ((options_hex.size() < 3) || (options_hex[0] != '0') ||
            (options_hex[1] != 'x')) {
            return (changed);
        }
        try {
            vector<uint8_t> options_data;
            encode::decodeHex(options_hex.substr(2), options_data);
            OptionCollection opts;
            LibDHCP::unpackOptions6(options_data, DHCP6_OPTION_SPACE, opts);

            auto remote_id_it = opts.find(D6O_REMOTE_ID);
            if (remote_id_it != opts.end()) {
                OptionPtr remote_id = remote_id_it->second;
                if (remote_id) {
                    vector<uint8_t> bytes = remote_id->toBinary(false);
                    if (bytes.size() > 0) {
                        relay->set("remote-id",
                                   Element::create(encode::encodeHex(bytes)));
                    }
                }
            }

            auto relay_id_it = opts.find(D6O_RELAY_ID);
            if (relay_id_it != opts.end()) {
                OptionPtr relay_id = relay_id_it->second;
                if (relay_id) {
                    vector<uint8_t> bytes = relay_id->toBinary(false);
                    if (bytes.size() > 0) {
                        relay->set("relay-id",
                                   Element::create(encode::encodeHex(bytes)));
                    }
                }
            }
        } catch (...) {
            return (changed);
        }
    }

    return (changed);
}

} // namespace isc::dhcp
} // namespace isc
