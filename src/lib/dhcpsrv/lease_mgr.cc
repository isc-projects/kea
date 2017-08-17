// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
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


using namespace std;

namespace isc {
namespace dhcp {

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
    int64_t zero = 0;
    stats_mgr.setValue("declined-addresses", zero);
    stats_mgr.setValue("reclaimed-declined-addresses", zero);
    stats_mgr.setValue("reclaimed-leases", zero);

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

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "reclaimed-declined-addresses"),
                           zero);

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "reclaimed-leases"),
                           zero);
    }

    // Get counts per state per subnet. Iterate over the result set
    // updating the subnet and global values.
    LeaseStatsRow row;
    while (query->getNextRow(row)) {
        if (row.lease_state_ == Lease::STATE_DEFAULT) {
            // Set subnet level value.
            stats_mgr.setValue(StatsMgr::generateName("subnet", row.subnet_id_,
                                                      "assigned-addresses"),
                               row.state_count_);
        } else if (row.lease_state_ == Lease::STATE_DECLINED) {
            // Set subnet level value.
            stats_mgr.setValue(StatsMgr::generateName("subnet", row.subnet_id_,
                                                      "declined-addresses"),
                               row.state_count_);

            // Add to the global value.
            stats_mgr.addValue("declined-addresses", row.state_count_);
        }
    }
}

LeaseStatsQueryPtr
LeaseMgr::startLeaseStatsQuery4() {
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

    // Zero out the global stats. (Ok, so currently there's only one
    // that should be cleared.  "reclaimed-declined-addresses" never
    // gets zeroed. @todo discuss with Tomek the rational of not
    // clearing it when we clear the rest.
    int64_t zero = 0;
    stats_mgr.setValue("declined-addresses", zero);
    stats_mgr.setValue("reclaimed-declined-addresses", zero);
    stats_mgr.setValue("reclaimed-leases", zero);

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

        stats_mgr.setValue(StatsMgr::
                           generateName("subnet", subnet_id,
                                        "reclaimed-declined-addresses"),
                           zero);

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "assigned-pds"),
                           zero);

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "reclaimed-leases"),
                           zero);
    }

    // Get counts per state per subnet. Iterate over the result set
    // updating the subnet and global values.
    LeaseStatsRow row;
    while (query->getNextRow(row)) {
        switch(row.lease_type_) {
            case Lease::TYPE_NA:
                if (row.lease_state_ == Lease::STATE_DEFAULT) {
                    // Set subnet level value.
                    stats_mgr.setValue(StatsMgr::
                                       generateName("subnet", row.subnet_id_,
                                                    "assigned-nas"),
                                       row.state_count_);
                } if (row.lease_state_ == Lease::STATE_DECLINED) {
                    // Set subnet level value.
                    stats_mgr.setValue(StatsMgr::
                                       generateName("subnet", row.subnet_id_,
                                                    "declined-addresses"),
                                       row.state_count_);

                    // Add to the global value.
                    stats_mgr.addValue("declined-addresses", row.state_count_);
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

std::string
LeaseMgr::getDBVersion() {
    isc_throw(NotImplemented, "LeaseMgr::getDBVersion() called");
}

} // namespace isc::dhcp
} // namespace isc
