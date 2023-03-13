// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/tracking_lease_mgr.h>
#include <util/multi_threading_mgr.h>
#include <boost/tuple/tuple.hpp>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

TrackingLeaseMgr::TrackingLeaseMgr()
    : LeaseMgr(), callbacks_(new TrackingLeaseMgr::CallbackContainer()) {
}

bool
TrackingLeaseMgr::tryLock(const LeasePtr& lease) {
    // Try inserting a lease. If such a lease already exists in the set, return false.
    auto result = locked_leases_.insert(lease->addr_);
    return (result.second);
}

void
TrackingLeaseMgr::unlock(const LeasePtr& lease) {
    // Remove the locked lease from the set.
    locked_leases_.erase(lease->addr_);
}

bool
TrackingLeaseMgr::isLocked(const LeasePtr& lease) {
    return (locked_leases_.find(lease->addr_) != locked_leases_.end());
}

void
TrackingLeaseMgr::trackAddLease(const LeasePtr& lease, bool mt_safe) {
    runCallbacks(TRACK_ADD_LEASE, lease, mt_safe);
}

void
TrackingLeaseMgr::trackUpdateLease(const LeasePtr& lease, bool mt_safe) {
    runCallbacks(TRACK_UPDATE_LEASE, lease, mt_safe);
}

void
TrackingLeaseMgr::trackDeleteLease(const LeasePtr& lease, bool mt_safe) {
    runCallbacks(TRACK_DELETE_LEASE, lease, mt_safe);
}

void
TrackingLeaseMgr::registerCallback(TrackingLeaseMgr::CallbackType type,
                                   std::string owner,
                                   SubnetID subnet_id,
                                   Lease::Type lease_type,
                                   TrackingLeaseMgr::CallbackFn callback_fn) {
    // The first index filters the callbacks by type and subnet_id.
    auto& idx = callbacks_->get<0>();
    auto range = idx.equal_range(boost::make_tuple(type, subnet_id, lease_type));
    if (range.first != range.second) {
        // Make sure that the callback for this owner does not exist.
        if (std::find_if(range.first, range.second,
                         [&owner] (const Callback& cb) -> bool {
                             return (cb.owner == owner);
                         }) != range.second) {
            isc_throw(InvalidOperation, "the callback owned by the " << owner
                      << ", for subnet ID " << subnet_id
                      << ", and lease type " << Lease::typeToText(lease_type)
                      << " has already been registered in the lease manager");
        }
    }
    TrackingLeaseMgr::Callback callback{type, owner, subnet_id, lease_type, callback_fn};
    callbacks_->insert(callback);
}

void
TrackingLeaseMgr::registerCallback(TrackingLeaseMgr::CallbackType type,
                                   std::string owner,
                                   Lease::Type lease_type,
                                   TrackingLeaseMgr::CallbackFn callback_fn) {
    registerCallback(type, owner, SUBNET_ID_GLOBAL, lease_type, callback_fn);
}

void
TrackingLeaseMgr::unregisterCallbacks(SubnetID subnet_id, Lease::Type lease_type) {
    // The second index filters the callbacks by the subnet identifier and
    // the lease type.
    auto& idx = callbacks_->get<1>();
    auto range = idx.equal_range(boost::make_tuple(subnet_id, lease_type));
    if (range.first != range.second) {
        idx.erase(range.first, range.second);
    }
}

void
TrackingLeaseMgr::unregisterAllCallbacks() {
    callbacks_->clear();
}

bool
TrackingLeaseMgr::hasCallbacks() const {
    return (!callbacks_->empty());
}

std::string
TrackingLeaseMgr::callbackTypeToString(CallbackType type) {
    switch (type) {
    case TrackingLeaseMgr::TRACK_ADD_LEASE:
        return ("add_lease");
    case TrackingLeaseMgr::TRACK_UPDATE_LEASE:
        return ("update_lease");
    case TrackingLeaseMgr::TRACK_DELETE_LEASE:
        return ("delete_lease");
    default:
        return ("unknown");
    }
}

void
TrackingLeaseMgr::runCallbacks(TrackingLeaseMgr::CallbackType type, const LeasePtr& lease,
                               bool mt_safe) {
    runCallbacksForSubnetID(type, SUBNET_ID_GLOBAL, lease, mt_safe);
    runCallbacksForSubnetID(type, lease->subnet_id_, lease, mt_safe);
}

void
TrackingLeaseMgr::runCallbacksForSubnetID(CallbackType type, SubnetID subnet_id,
                                          const LeasePtr& lease, bool mt_safe) {
    // The first index filters by callback type and subnet_id.
    auto& idx = callbacks_->get<0>();
    auto cbs = idx.equal_range(boost::make_tuple(type, subnet_id, lease->getType()));
    if (cbs.first == cbs.second) {
        return;
    }
    for (auto it = cbs.first; it != cbs.second; ++it) {
        auto cb = *it;
        try {
            cb.fn(lease, mt_safe);
        } catch (const std::exception& ex) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_LEASE_MGR_CALLBACK_EXCEPTION)
                .arg(callbackTypeToString(type))
                .arg(subnet_id)
                .arg(lease->addr_.toText())
                .arg(ex.what());
        } catch (...) {
            LOG_WARN(dhcpsrv_logger, DHCPSRV_LEASE_MGR_CALLBACK_UNKNOWN_EXCEPTION)
                .arg(callbackTypeToString(type))
                .arg(subnet_id)
                .arg(lease->addr_.toText());
        }
    }
}


} // end of namespace isc::dhcp
} // end of namespace isc
