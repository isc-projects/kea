// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/memfile_lease_limits.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

size_t
ClassLeaseCounter::getClassCount(const ClientClass& client_class, const Lease::Type& ltype) {
    ClassCountMap& leases_by_class = getCountMap(ltype);
    auto it = leases_by_class.find(client_class);
    if (it == leases_by_class.end()) {
        return (0);
    }

    // Return the lease count for the class.
    return(it->second);
}

void
ClassLeaseCounter::setClassCount(const ClientClass& client_class, size_t count,
                                 const Lease::Type& ltype) {
    ClassCountMap& leases_by_class = getCountMap(ltype);
    leases_by_class[client_class] = count;
}

void
ClassLeaseCounter::adjustClassCount(const ClientClass& client_class, int offset,
                                    const Lease::Type& ltype) {
    ClassCountMap& leases_by_class = getCountMap(ltype);
    auto it = leases_by_class.find(client_class);
    if (it == leases_by_class.end()) {
        // Not there yet, add it.
        leases_by_class[client_class] = offset < 0 ? 0 : offset;
    } else {
        size_t new_count = it->second + offset;
        if (offset < 0 && (new_count > it->second)) {
            // We rolled over, set it zero.  We should probably log this?
            it->second = 0;
        } else {
            it->second = new_count;
        }
    }
}


ConstElementPtr
ClassLeaseCounter::getLeaseClientClasses(LeasePtr lease) const {
    ConstElementPtr classes;
    auto ctx = lease->getContext();
    if (ctx) {
        // Look for ddns-tuning map within user-context.
        classes = ctx->get("classes");
        if (!classes) {
            // Return an empty list;
            return (Element::createList());
        }

        if (classes->getType() != Element::list) {
            isc_throw(Unexpected, "getLeaseClientClasses: "
                      << lease->toText() << " is not a list!");
        }
    }

    return (classes);
}

void
ClassLeaseCounter::adjustClassCounts(ConstElementPtr classes, int offset,
                                     const Lease::Type& ltype) {
    if (!classes) {
        return;
    }

    for (int i = 0; i < classes->size(); ++i) {
        std::string class_name = classes->get(i)->stringValue();
        adjustClassCount(class_name, offset, ltype);
    }
}

void
ClassLeaseCounter::addLease(LeasePtr lease) {
    if (!lease) {
        isc_throw(BadValue, "addLease(): lease cannot be empty");
    }

    ConstElementPtr classes = getLeaseClientClasses(lease);
    if (!classes) {
        return; // Lease limits isn't loaded.
    }

    // Add the new lease to its classes.
    if (lease->state_ == Lease::STATE_DEFAULT) {
        adjustClassCounts(classes, 1, lease->getType());
    }
}

void
ClassLeaseCounter::updateLease(LeasePtr new_lease, LeasePtr old_lease) {
    // Sanity checks.
    if (!new_lease) {
        isc_throw(BadValue, "updateLease(): new_lease cannot be empty");
    }

    if (!old_lease) {
        isc_throw(BadValue, "updateLease(): old_lease cannot be empty");
    }

    if (new_lease->getType() != old_lease->getType()) {
        // Leases cannot change type, but I don't know if we care?
        isc_throw(BadValue, "updateLease(): lease types do not match?");
    }

    ConstElementPtr new_classes = getLeaseClientClasses(new_lease);
    uint32_t new_state = new_lease->state_;

    ConstElementPtr old_classes = getLeaseClientClasses(old_lease);
    uint32_t old_state = old_lease->state_;

    // Did we change states or classes?
    if (old_state != new_state || old_classes != new_classes) {
        // Old classes are moving out of a counted state.
        if (old_state == Lease::STATE_DEFAULT) {
            adjustClassCounts(old_classes, -1, old_lease->getType());
        }

        // New classes are moving into a counted state.
        if (new_state == Lease::STATE_DEFAULT) {
            adjustClassCounts(new_classes, 1, new_lease->getType());
        }
    }
}

void
ClassLeaseCounter::removeLease(LeasePtr lease) {
    if (!lease) {
        isc_throw(BadValue, "removeLease(): lease cannot be empty");
    }

    ConstElementPtr classes = getLeaseClientClasses(lease);
    if (!classes) {
        return; // Lease limits isn't loaded.
    }

    // Remove the new lease to its classes.
    if (lease->state_ == Lease::STATE_DEFAULT) {
        adjustClassCounts(classes, -1, lease->getType());
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
