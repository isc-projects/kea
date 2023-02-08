// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
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

void
LeaseMgr::setExtendedInfoTablesEnabled(const DatabaseConnection::ParameterMap& parameters) {
    std::string extended_info_tables;
    try {
        extended_info_tables = parameters.at("extended-info-tables");
    } catch (const exception&) {
        extended_info_tables = "false";
    }
    // If extended_info_tables is 'true' we will enable them.
    if (extended_info_tables == "true") {
        setExtendedInfoTablesEnabled(true);
    }
}

bool
LeaseMgr::upgradeLease4ExtendedInfo(const Lease4Ptr& lease,
                                    CfgConsistency::ExtendedInfoSanity check) {
    static OptionDefinitionPtr rai_def;

    bool changed = false;
    if (!lease) {
        return (changed);
    }

    if (check == CfgConsistency::EXTENDED_INFO_CHECK_NONE) {
        return (changed);
    }

    ConstElementPtr user_context = lease->getContext();
    if (!user_context) {
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

    ConstElementPtr isc;
    ConstElementPtr extended_info;
    ElementPtr mutable_user_context;
    ElementPtr mutable_isc;
    string verifying = "";
    bool removed_extended_info = false;

    try {
        verifying = "user context";
        if (user_context->getType() != Element::map) {
            isc_throw(BadValue, "user context is not a map");
        }
        if (user_context->empty()) {
            changed = true;
            lease->setContext(ConstElementPtr());
            return (changed);
        }

        verifying = "isc";
        isc = user_context->get("ISC");
        if (!isc) {
            return (changed);
        }
        mutable_user_context =
            boost::const_pointer_cast<Element>(user_context);
        if (!mutable_user_context) {
            // Should not happen...
            mutable_user_context = copy(user_context, 0);
            lease->setContext(mutable_user_context);
        }

        if (isc->getType() != Element::map) {
            isc_throw(BadValue, "ISC entry is not a map");
        }
        if (isc->empty()) {
            changed = true;
            mutable_user_context->remove("ISC");
            if (mutable_user_context->empty()) {
                lease->setContext(ConstElementPtr());
            }
            return (changed);
        }

        verifying = "relay-agent-info";
        extended_info = isc->get("relay-agent-info");
        if (!extended_info) {
            return (changed);
        }
        mutable_isc = boost::const_pointer_cast<Element>(isc);
        if (!mutable_isc) {
            // Should not happen...
            mutable_isc = copy(isc, 0);
            mutable_user_context->set("ISC", mutable_isc);
        }

        if (extended_info->getType() == Element::string) {
            // Upgrade
            changed = true;
            ElementPtr upgraded = Element::createMap();
            upgraded->set("sub-options", extended_info);
            mutable_isc->set("relay-agent-info", upgraded);

            // Try to decode sub-options.
            verifying = "rai";
            string rai_hex = extended_info->stringValue();
            vector<uint8_t> rai_data;
            str::decodeFormattedHexString(rai_hex, rai_data);
            OptionCustomPtr rai(new OptionCustom(*rai_def, Option::V4, rai_data));
            if (!rai) {
                isc_throw(BadValue, "can't create RAI option");
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

            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_LEASE4_EXTENDED_INFO_UPGRADED)
                .arg(lease->addr_.toText());
            return (changed);
        } else if (extended_info->getType() != Element::map) {
            mutable_isc->remove("relay-agent-info");
            removed_extended_info = true;
            isc_throw(BadValue, "relay-agent-info is not a map or a string");
        }

        if (check == CfgConsistency::EXTENDED_INFO_CHECK_FIX) {
            return (changed);
        }

        // Try to decode sub-options.
        ConstElementPtr sub_options = extended_info->get("sub-options");
        if (sub_options) {
            verifying = "sub-options";
            if (sub_options->getType() != Element::string) {
                mutable_isc->remove("relay-agent-info");
                removed_extended_info = true;
                isc_throw(BadValue, "sub-options is not a string");
            }
            string rai_hex = sub_options->stringValue();
            vector<uint8_t> rai_data;
            str::decodeFormattedHexString(rai_hex, rai_data);
        }

        ConstElementPtr remote_id = extended_info->get("remote-id");
        if (remote_id) {
            verifying = "remote-id";
            if (remote_id->getType() != Element::string) {
                mutable_isc->remove("relay-agent-info");
                removed_extended_info = true;
                isc_throw(BadValue, "remote-id is not a string");
            }
            string remote_id_hex = remote_id->stringValue();
            vector<uint8_t> remote_id_data;
            encode::decodeHex(remote_id_hex, remote_id_data);
            if (remote_id_data.empty()) {
                mutable_isc->remove("relay-agent-info");
                removed_extended_info = true;
                isc_throw(BadValue, "remote-id is empty");
            }
        }

        ConstElementPtr relay_id = extended_info->get("relay-id");
        if (relay_id) {
            verifying = "relay-id";
            if (relay_id->getType() != Element::string) {
                mutable_isc->remove("relay-agent-info");
                removed_extended_info = true;
                isc_throw(BadValue, "relay-id is not a string");
            }
            string relay_id_hex = relay_id->stringValue();
            vector<uint8_t> relay_id_data;
            encode::decodeHex(relay_id_hex, relay_id_data);
            if (relay_id_data.empty()) {
                mutable_isc->remove("relay-agent-info");
                removed_extended_info = true;
                isc_throw(BadValue, "relay-id is empty");
            }
        }

        if (check != CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC) {
            return (changed);
        }

        verifying = "relay-agent-info";
        for (auto elem : extended_info->mapValue()) {
            if ((elem.first != "sub-options") &&
                (elem.first != "remote-id") &&
                (elem.first != "relay-id") &&
                (elem.first != "comment")) {
                mutable_isc->remove("relay-agent-info");
                removed_extended_info = true;
                isc_throw(BadValue, "spurious '" << elem.first <<
                          "' entry in relay-agent-info");
            }
        }

        return (changed);
    } catch (const exception& ex) {
        ostringstream err;
        err << "in " << verifying << " a problem was found: " << ex.what();
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL)
            .arg(lease->addr_.toText())
            .arg(err.str());

        changed = true;
        if (verifying == "user context") {
            lease->setContext(ConstElementPtr());
        } else if (verifying == "isc") {
            mutable_user_context->remove("ISC");
            if (mutable_user_context->empty()) {
                lease->setContext(ConstElementPtr());
            }
        } else {
            if (!removed_extended_info) {
                mutable_isc->remove("relay-agent-info");
            }
            if (mutable_isc->empty()) {
                mutable_user_context->remove("ISC");
                if (mutable_user_context->empty()) {
                    lease->setContext(ConstElementPtr());
                }
            }
        }
        return (changed);
    }
}

bool
LeaseMgr::upgradeLease6ExtendedInfo(const Lease6Ptr& lease,
                                    CfgConsistency::ExtendedInfoSanity check) {
    bool changed = false;
    if (!lease) {
        return (changed);
    }

    if (check == CfgConsistency::EXTENDED_INFO_CHECK_NONE) {
        return (changed);
    }

    ConstElementPtr user_context = lease->getContext();
    if (!user_context) {
        return (changed);
    }

    ConstElementPtr isc;
    ConstElementPtr relay_info;
    ElementPtr mutable_user_context;
    ElementPtr mutable_isc;
    string verifying = "";
    bool removed_relay_info = false;
    bool upgraded = false;
    bool have_both = false;
    int i = -1;

    try {
        verifying = "user context";
        if (user_context->getType() != Element::map) {
            isc_throw(BadValue, "user context is not a map");
        }
        if (user_context->empty()) {
            changed = true;
            lease->setContext(ConstElementPtr());
            return (changed);
        }

        verifying = "isc";
        isc = user_context->get("ISC");
        if (!isc) {
            return (changed);
        }
        mutable_user_context =
            boost::const_pointer_cast<Element>(user_context);
        if (!mutable_user_context) {
            // Should not happen...
            mutable_user_context = copy(user_context, 0);
            lease->setContext(mutable_user_context);
        }

        if (isc->getType() != Element::map) {
            isc_throw(BadValue, "ISC entry is not a map");
        }
        if (isc->empty()) {
            changed = true;
            mutable_user_context->remove("ISC");
            if (mutable_user_context->empty()) {
                lease->setContext(ConstElementPtr());
            }
            return (changed);
        }
        mutable_isc = boost::const_pointer_cast<Element>(isc);
        if (!mutable_isc) {
            // Should not happen...
            mutable_isc = copy(isc, 0);
            mutable_user_context->set("ISC", mutable_isc);
        }

        relay_info = mutable_isc->get("relays");
        if (relay_info && isc->contains("relay-info")) {
            changed = true;
            mutable_isc->remove("relays");
            have_both = true;
            relay_info.reset();
        }
        if (relay_info) {
            // Upgrade
            changed = true;
            upgraded = true;
            verifying = "relays";
            mutable_isc->set("relay-info", relay_info);
            mutable_isc->remove("relays");

            if (relay_info->getType() != Element::list) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "relays is not a list");
            }
            if (relay_info->empty()) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "relays is empty");
            }

            verifying = "relay";
            for (i = 0; i < relay_info->size(); ++i) {
                ElementPtr relay = relay_info->getNonConst(i);
                if (!relay) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "null relay#" << i);
                }
                if (relay->getType() != Element::map) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "relay#" << i << " is not a map");
                }

                // Try to decode options.
                ConstElementPtr options = relay->get("options");
                if (!options) {
                    continue;
                }

                verifying = "options";
                if (options->getType() != Element::string) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "options is not a string");
                }
                string options_hex = options->stringValue();
                vector<uint8_t> options_data;
                str::decodeFormattedHexString(options_hex, options_data);
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
            }
        }

        verifying = (upgraded ? "relays" : "relay-info");
        i = -1;
        relay_info = mutable_isc->get("relay-info");
        if (!relay_info) {
            return (changed);
        }
        if (!upgraded && (relay_info->getType() != Element::list)) {
            mutable_isc->remove("relay-info");
            removed_relay_info = true;
            isc_throw(BadValue, "relay-info is not a list");
        }
        if (!upgraded && relay_info->empty()) {
            mutable_isc->remove("relay-info");
            removed_relay_info = true;
            isc_throw(BadValue, "relay-info is empty");
        }

        verifying = "relay";
        for (i = 0; i < relay_info->size(); ++i) {
            ElementPtr relay = relay_info->getNonConst(i);
            if (!upgraded && !relay) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "null relay#" << i);
            }
            if (!upgraded && (relay->getType() != Element::map)) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "relay#" << i << " is not a map");
            }

            ConstElementPtr options = relay->get("options");
            if (!upgraded && options) {
                // Try to decode options.
                verifying = "options";
                if (options->getType() != Element::string) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "options is not a string");
                }
                string options_hex = options->stringValue();
                vector<uint8_t> options_data;
                str::decodeFormattedHexString(options_hex, options_data);
                OptionCollection opts;
                LibDHCP::unpackOptions6(options_data, DHCP6_OPTION_SPACE, opts);
            }
            if (check == CfgConsistency::EXTENDED_INFO_CHECK_FIX) {
                continue;
            }

            verifying = "link";
            ConstElementPtr link_addr = relay->get("link");
            if (!link_addr) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "no link");
            }
            if (link_addr->getType() != Element::string) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "link is not a string");
            }
            IOAddress laddr(link_addr->stringValue());
            if (!laddr.isV6()) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "link is not an IPv6 address");
            }

            ConstElementPtr remote_id = relay->get("remote-id");
            if (!upgraded && remote_id) {
                verifying = "remote-id";
                if (remote_id->getType() != Element::string) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "remote-id is not a string");
                }
                string remote_id_hex = remote_id->stringValue();
                vector<uint8_t> remote_id_data;
                encode::decodeHex(remote_id_hex, remote_id_data);
                if (remote_id_data.empty()) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "remote-id is empty");
                }
            }

            ConstElementPtr relay_id = relay->get("relay-id");
            if (!upgraded && relay_id) {
                verifying = "relay-id";
                if (relay_id->getType() != Element::string) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "relay-id is not a string");
                }
                string relay_id_hex = relay_id->stringValue();
                vector<uint8_t> relay_id_data;
                encode::decodeHex(relay_id_hex, relay_id_data);
                if (relay_id_data.empty()) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "relay-id is empty");
                }
            }

            if (check != CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC) {
                continue;
            }

            verifying = "peer";
            ConstElementPtr peer_addr = relay->get("peer");
            if (!peer_addr) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "no peer");
            }
            if (peer_addr->getType() != Element::string) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "peer is not a string");
            }
            IOAddress paddr(peer_addr->stringValue());
            if (!paddr.isV6()) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "peer is not an IPv6 address");
            }

            verifying = "hop";
            ConstElementPtr hop = relay->get("hop");
            if (!hop) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "no hop");
            }
            if (hop->getType() != Element::integer) {
                mutable_isc->remove("relay-info");
                removed_relay_info = true;
                isc_throw(BadValue, "hop is not an integer");
            }

            verifying = (upgraded ? "relays" : "relay-info");
            for (auto elem : relay->mapValue()) {
                if ((elem.first != "hop") &&
                    (elem.first != "link") &&
                    (elem.first != "peer") &&
                    (elem.first != "options") &&
                    (elem.first != "remote-id") &&
                    (elem.first != "relay-id") &&
                    (elem.first != "comment")) {
                    mutable_isc->remove("relay-info");
                    removed_relay_info = true;
                    isc_throw(BadValue, "spurious '" << elem.first << "' entry");
                }
            }
        }

        if (upgraded) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED)
                .arg(lease->addr_.toText());
        }

        return (changed);
    } catch (const exception& ex) {
        ostringstream err;
        err << "in " << verifying;
        if (i >= 0) {
            err << " [relay#" << i << "]";
        }
        err << " a problem was found: " << ex.what();
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL)
            .arg(lease->addr_.toText())
            .arg(err.str());

        changed = true;
        have_both = !have_both;
        if (verifying == "user context") {
            lease->setContext(ConstElementPtr());
        } else if (verifying == "isc") {
            mutable_user_context->remove("ISC");
            if (mutable_user_context->empty()) {
                lease->setContext(ConstElementPtr());
            }
        } else {
            if (!removed_relay_info) {
                mutable_isc->remove("relay-info");
            }
            if (mutable_isc->empty()) {
                mutable_user_context->remove("ISC");
                if (mutable_user_context->empty()) {
                    lease->setContext(ConstElementPtr());
                }
            }
        }
        return (changed);
    }
}

void
LeaseMgr::extractLease4ExtendedInfo(const Lease4Ptr& lease,
                                    bool ignore_errors) {
    if (!lease) {
        return;
    }

    ConstElementPtr user_context = lease->getContext();
    if (!user_context) {
        return;
    }
    if (user_context->getType() != Element::map) {
        if (ignore_errors) {
            return;
        }
        isc_throw(BadValue, "user context is not a map");
    }
    if (user_context->empty()) {
        return;
    }

    ConstElementPtr isc = user_context->get("ISC");
    if (!isc) {
        return;
    }
    if (isc->getType() != Element::map) {
        if (ignore_errors) {
            return;
        }
        isc_throw(BadValue, "ISC entry is not a map");
    }
    if (isc->empty()) {
        return;
    }

    ConstElementPtr extended_info = isc->get("relay-agent-info");
    if (!extended_info) {
        return;
    }
    if (extended_info->getType() != Element::map) {
        if (ignore_errors) {
            return;
        }
        isc_throw(BadValue, "relay-agent-info is not a map");
    }
    if (extended_info->empty()) {
        return;
    }

    ConstElementPtr relay_id = extended_info->get("relay-id");
    if (relay_id) {
        if (relay_id->getType() == Element::string) {
            vector<uint8_t> bytes;
            try {
                encode::decodeHex(relay_id->stringValue(), bytes);
            } catch (...) {
                // Decode failed
                if (!ignore_errors) {
                    throw;
                }
            }
            lease->relay_id_ = bytes;
        } else if (!ignore_errors) {
            isc_throw(BadValue, "relay-id entry is not a string");
        }
    }

    ConstElementPtr remote_id = extended_info->get("remote-id");
    if (remote_id) {
        if (remote_id->getType() == Element::string) {
            vector<uint8_t> bytes;
            try {
                encode::decodeHex(remote_id->stringValue(), bytes);
            } catch (...) {
                // Decode failed
                if (!ignore_errors) {
                    throw;
                }
            }
            lease->remote_id_ = bytes;
        } else if (!ignore_errors) {
            isc_throw(BadValue, "remote-id entry is not a string");
        }
    }
}

bool
LeaseMgr::addExtendedInfo6(const Lease6Ptr& lease) {

    bool added = false;
    if (!lease) {
        return (added);
    }

    ConstElementPtr user_context = lease->getContext();
    if (!user_context || (user_context->getType() != Element::map) ||
        user_context->empty()) {
        return (added);
    }

    ConstElementPtr isc = user_context->get("ISC");
    if (!isc || (isc->getType() != Element::map) || isc->empty()) {
        return (added);
    }

    ConstElementPtr relay_info = isc->get("relay-info");
    if (!relay_info || (relay_info->getType() != Element::list) ||
        relay_info->empty()) {
        return (added);
    }

    for (int i = 0; i < relay_info->size(); ++i) {
        ConstElementPtr relay = relay_info->get(i);
        if (!relay || (relay->getType() != Element::map) || relay->empty()) {
            continue;
        }
        try {
            ConstElementPtr relay_id = relay->get("relay-id");
            if (relay_id) {
                string relay_id_hex = relay_id->stringValue();
                vector<uint8_t> relay_id_data;
                encode::decodeHex(relay_id_hex, relay_id_data);
                if (relay_id_data.empty()) {
                    continue;
                }
                addRelayId6(lease->addr_, relay_id_data);
                added = true;
            }

            ConstElementPtr remote_id = relay->get("remote-id");
            if (remote_id) {
                string remote_id_hex = remote_id->stringValue();
                vector<uint8_t> remote_id_data;
                encode::decodeHex(remote_id_hex, remote_id_data);
                if (remote_id_data.empty()) {
                    continue;
                }
                addRemoteId6(lease->addr_, remote_id_data);
                added = true;
            }
        } catch (const exception&) {
            continue;
        }
    }
    return (added);
}

} // namespace isc::dhcp
} // namespace isc
