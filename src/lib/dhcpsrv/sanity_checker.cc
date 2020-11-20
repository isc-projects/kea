// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>

#include <dhcpsrv/sanity_checker.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <sstream>

namespace isc {
namespace dhcp {

bool SanityChecker::leaseCheckingEnabled(bool current) {
    SrvConfigPtr cfg;
    if (current) {
        cfg = CfgMgr::instance().getCurrentCfg();
    } else {
        cfg = CfgMgr::instance().getStagingCfg();
    }

    if (cfg) {
        CfgConsistencyPtr sanity = cfg->getConsistency();
        return (sanity && (sanity->getLeaseSanityCheck() != CfgConsistency::LEASE_CHECK_NONE));
    }

    return (false);
}

void SanityChecker::checkLease(Lease4Ptr& lease, bool current) {
    SrvConfigPtr cfg;
    if (current) {
        cfg = CfgMgr::instance().getCurrentCfg();
    } else {
        cfg = CfgMgr::instance().getStagingCfg();
    }

    CfgConsistencyPtr sanity = cfg->getConsistency();
    if (sanity->getLeaseSanityCheck() == CfgConsistency::LEASE_CHECK_NONE) {
        // No sense going farther.
        return;
    }

    CfgSubnets4Ptr subnets = cfg->getCfgSubnets4();
    checkLeaseInternal(lease, sanity, subnets);
}

void SanityChecker::checkLease(Lease6Ptr& lease, bool current) {
    // We only check IA_NAs currently.
    if (lease->type_ != Lease::TYPE_NA) {
        return;
    }

    SrvConfigPtr cfg;
    if (current) {
        cfg = CfgMgr::instance().getCurrentCfg();
    } else {
        cfg = CfgMgr::instance().getStagingCfg();
    }
    CfgConsistencyPtr sanity = cfg->getConsistency();
    if (sanity->getLeaseSanityCheck() == CfgConsistency::LEASE_CHECK_NONE) {
        // No sense going farther.
        return;
    }

    CfgSubnets6Ptr subnets = cfg->getCfgSubnets6();
    checkLeaseInternal(lease, sanity, subnets);
}

template<typename LeasePtrType, typename SubnetsType>
void SanityChecker::checkLeaseInternal(LeasePtrType& lease, const CfgConsistencyPtr& checks,
                               const SubnetsType& subnets) {

    auto subnet = subnets->getBySubnetId(lease->subnet_id_);
    if (subnet && subnet->inRange(lease->addr_)) {

        // If the subnet is defined and the address is in range, we're good.

        return;
    }

    // Ok, if we got here, that means that either we did not find a subnet
    // of found it, but it wasn't the right subnet.
    SubnetID id = findSubnetId(lease, subnets);

    // Prepare a message in the case the check fails.
    std::ostringstream msg;
    if (id != 0) {
        msg << "the lease should have subnet-id " << id;
    } else {
        msg << "the lease IP address did not belong to a configured subnet";
    }

    switch (checks->getLeaseSanityCheck()) {
    case CfgConsistency::LEASE_CHECK_WARN:
        if (lease->subnet_id_ != id) {
            // Print a warning, but return the lease as is.
            LOG_WARN(dhcpsrv_logger, DHCPSRV_LEASE_SANITY_FAIL)
                .arg(lease->addr_.toText())
                .arg(lease->subnet_id_)
                .arg(msg.str());
        }
        break;

    case CfgConsistency::LEASE_CHECK_FIX:
        if (lease->subnet_id_ != id) {

            // If there is a better subnet, use it.
            if (id != 0) {
                LOG_INFO(dhcpsrv_logger, DHCPSRV_LEASE_SANITY_FIXED)
                    .arg(lease->addr_.toText())
                    .arg(lease->subnet_id_)
                    .arg(id);
                lease->subnet_id_ = id;
            } else {
                // If not, return the lease as is.
                LOG_WARN(dhcpsrv_logger, DHCPSRV_LEASE_SANITY_FAIL)
                    .arg(lease->addr_.toText())
                    .arg(lease->subnet_id_)
                    .arg(msg.str());
            }
        }
        break;

    case CfgConsistency::LEASE_CHECK_FIX_DEL:
        if (lease->subnet_id_ != id) {

            // If there is a better subnet, use it.
            if (id != 0) {
                LOG_INFO(dhcpsrv_logger, DHCPSRV_LEASE_SANITY_FIXED)
                    .arg(lease->addr_.toText())
                    .arg(lease->subnet_id_)
                    .arg(id);
                lease->subnet_id_ = id;
                break;
            } else {
                // If not, delete the lease.
                LOG_INFO(dhcpsrv_logger, DHCPSRV_LEASE_SANITY_FAIL_DISCARD)
                    .arg(lease->addr_.toText())
                    .arg(lease->subnet_id_)
                    .arg(msg.str());
                lease.reset();
            }

        }
        break;

    case CfgConsistency::LEASE_CHECK_DEL:
        if (lease->subnet_id_ != id) {
            LOG_INFO(dhcpsrv_logger, DHCPSRV_LEASE_SANITY_FAIL_DISCARD)
                .arg(lease->addr_.toText())
                .arg(lease->subnet_id_)
                .arg(msg.str());
            lease.reset();
        }
        break;

    default:
        // Shouldn't get here but some compilers and analyzers
        // complain.  We'll we treat it as NONE and return the 
        // lease as-is.
        break;

    }

    // Additional checks may be implemented in the future here.

    /// @todo: add a check if the address is within specified dynamic pool
    /// if not, check if the address is reserved.
}

template<typename LeaseType, typename SubnetsType>
SubnetID SanityChecker::findSubnetId(const LeaseType& lease, const SubnetsType& subnets) {
    auto subnet = subnets->selectSubnet(lease->addr_);
    if (!subnet) {
        return (0);
    }

    return (subnet->getID());
}

};
};
