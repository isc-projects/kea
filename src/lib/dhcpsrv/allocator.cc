// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/allocator.h>
#include <dhcpsrv/lease_mgr_factory.h>

using namespace isc::util;

namespace isc {
namespace dhcp {

Allocator::Allocator(Lease::Type type, const WeakSubnetPtr& subnet)
    : pool_type_(type),
      subnet_id_(0),
      subnet_(subnet) {
    // Remember subnet ID in a separate variable. It may be needed in
    // the destructor where the subnet weak pointer is unavailable.
    subnet_id_ = subnet_.lock()->getID();
}

Allocator::~Allocator() {
    if (!LeaseMgrFactory::haveInstance()) {
        // If there is no lease manager instance, the callbacks are
        // gone already anyway.
        return;
    }
    // Remove the callbacks.
    auto& lease_mgr = LeaseMgrFactory::instance();
    lease_mgr.unregisterCallbacks(subnet_id_, pool_type_);
}

bool
Allocator::isValidPrefixPool(Allocator::PrefixLenMatchType prefix_length_match,
                                  PoolPtr pool, uint8_t hint_prefix_length) {
    auto pool6 = boost::dynamic_pointer_cast<Pool6>(pool);
    if (!pool6) {
        return (false);
    }

    if (!hint_prefix_length) {
        return (true);
    }

    if (prefix_length_match == Allocator::PREFIX_LEN_EQUAL &&
        pool6->getLength() != hint_prefix_length) {
        return (false);
    }

    if (prefix_length_match == Allocator::PREFIX_LEN_LOWER &&
        pool6->getLength() >= hint_prefix_length) {
        return (false);
    }

    if (prefix_length_match == Allocator::PREFIX_LEN_HIGHER &&
        pool6->getLength() <= hint_prefix_length) {
        return (false);
    }

    return (true);
}

}
}
