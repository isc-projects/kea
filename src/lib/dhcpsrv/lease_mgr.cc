// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>

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
using namespace isc::db;
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

} // namespace isc::dhcp
} // namespace isc
