// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/sflq_allocator.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <util/stopwatch.h>
#include <limits>

using namespace isc::asiolink;
using namespace isc::util;
using namespace std;

namespace isc {
    bool sflq_in_use_ = false;
}

namespace isc {
namespace dhcp {

constexpr size_t SharedFlqAllocator::MAX_V4_POOL_SIZE;
constexpr size_t SharedFlqAllocator::MAX_V6_POOL_SIZE;

void
SharedFlqAllocator::setInUse(bool in_use) {
    sflq_in_use_ = in_use;
}

bool
SharedFlqAllocator::inUse() {
    return (sflq_in_use_);
}

SharedFlqAllocator::SharedFlqAllocator(Lease::Type type, const WeakSubnetPtr& subnet)
    : Allocator(type, subnet), generator_() {
    random_device rd;
    generator_.seed(rd());
}

void
SharedFlqAllocator::initAfterConfigureInternal() {
    auto subnet = subnet_.lock();
    auto const& pools = subnet->getPools(pool_type_);
    if (pools.empty()) {
        // If there are no pools there is nothing to do.
        return;
    }

    // Set static class flag marking at least one pool is using SFlq.
    setInUse(true);

    for (const auto& pool : pools) {
    switch (pool_type_) {
        case Lease::TYPE_V4:
            LeaseMgrFactory::instance().sflqCreateFlqPool4(pool->getFirstAddress(),
                                                           pool->getLastAddress(),
                                                           subnet->getID(), false);
            break;
        case Lease::TYPE_NA:
            LeaseMgrFactory::instance().sflqCreateFlqPool6(pool->getFirstAddress(),
                                                           pool->getLastAddress(),
                                                           Lease::TYPE_NA, 128,
                                                           subnet->getID(), false);
            break;
        case Lease::TYPE_PD: {
            auto pdpool = boost::dynamic_pointer_cast<Pool6>(pool);
            LeaseMgrFactory::instance().sflqCreateFlqPool6(pool->getFirstAddress(),
                                                           pool->getLastAddress(),
                                                           Lease::TYPE_PD, pdpool->getLength(),
                                                           subnet->getID(), false);
            break;
        }
        default:
            ;
        }
    }
}

IOAddress
SharedFlqAllocator::pickAddressInternal(const ClientClasses& client_classes,
                                        const IdentifierBaseTypePtr&,
                                        const IOAddress&) {
    // Let's  iterate over the subnet's pools and identify the ones that
    // meet client class criteria.
    auto subnet = subnet_.lock();
    auto const& pools = subnet->getPools(pool_type_);
    std::vector<PoolPtr> available;
    for (auto const& pool : pools) {
        // Check if the pool is allowed for the client's classes.
        if (pool->clientSupported(client_classes)) {
            available.push_back(pool);
        }
    }

    // Try each pool in random order.
    while (available.size()) {
        // Get a random pool from the available ones.
        auto offset = getRandomNumber(available.size() - 1);
        PoolPtr const pool = available[offset];
        switch (pool_type_) {
        case Lease::TYPE_V4: {
            // Ask the lease manager for a lease from the pool.
            auto free_lease = LeaseMgrFactory::instance()
                              .sflqPickFreeLease4(pool->getFirstAddress(),
                                                  pool->getLastAddress());
            if (!free_lease.isV4Zero()) {
                getSubnetState()->setLastAllocatedTime();
                return (free_lease);
            }

            break;
        }
        case Lease::TYPE_NA:{
            auto free_lease = LeaseMgrFactory::instance()
                              .sflqPickFreeLease6(pool->getFirstAddress(),
                                                  pool->getLastAddress());
            if (!free_lease.isV6Zero()) {
                getSubnetState()->setLastAllocatedTime();
                return (free_lease);
            }

            break;
        }
        case Lease::TYPE_PD:
            isc_throw(Unexpected, "pickAddressInternal called for Lease::TYPE_PD");
                break;
        default:
            isc_throw(Unexpected, "pickAddressInternal called for unknown lease type " << pool_type_);
            break;
        }

        // Remove the exhausted pool from the list then try another one.
        available.erase(available.begin() + offset);
    }

    // No address available.
    return (pool_type_ == Lease::TYPE_V4 ? IOAddress::IPV4_ZERO_ADDRESS()
                                         : IOAddress::IPV6_ZERO_ADDRESS());
}

IOAddress
SharedFlqAllocator::pickPrefixInternal(const ClientClasses& client_classes,
                                            Pool6Ptr& /* pool6 */,
                                            const IdentifierBaseTypePtr&,
                                            PrefixLenMatchType prefix_length_match,
                                            const IOAddress&,
                                            uint8_t hint_prefix_length) {
    // Let's  iterate over the subnet's pools and identify the ones that
    // meet client class criteria.
    auto subnet = subnet_.lock();
    auto const& pools = subnet->getPools(pool_type_);
    std::vector<PoolPtr> available;
    for (auto const& pool : pools) {
        // Check if the pool is allowed for the client's classes.
        if (pool->clientSupported(client_classes)) {
            if (!Allocator::isValidPrefixPool(prefix_length_match, pool,
                                              hint_prefix_length)) {
                continue;
            }

            available.push_back(pool);
        }
    }

    // Try each pool in random order.
    while (available.size()) {
        // Get a random pool from the available ones.
        auto offset = getRandomNumber(available.size() - 1);
        PoolPtr const pool = available[offset];
        switch(pool_type_) {
        case Lease::TYPE_V4:
            isc_throw(Unexpected, "pickPrefixInternal called for Lease::TYPE_V4");
            break;
        case Lease::TYPE_NA:
            isc_throw(Unexpected, "pickPrefixInternal called for Lease::TYPE_NA");
            break;
        case Lease::TYPE_PD:{
            // Ask the lease manager for a lease from the pool.
            auto free_lease = LeaseMgrFactory::instance()
                              .sflqPickFreeLease6(pool->getFirstAddress(),
                                                  pool->getLastAddress());
            if (!free_lease.isV6Zero()) {
                getSubnetState()->setLastAllocatedTime();
                return (free_lease);
            }
            }
            break;
        default:
            isc_throw(Unexpected, "pickPrefixInternal called for unknown lease type " << pool_type_);
            break;
        }

        // Remove the exhausted pool from the list then try another one.
        available.erase(available.begin() + offset);
    }

    // No address available.
    return (IOAddress::IPV6_ZERO_ADDRESS());
}

uint64_t
SharedFlqAllocator::getRandomNumber(uint64_t limit) {
    // Take the short path if there is only one number to randomize from.
    if (limit == 0) {
        return (0);
    }
    std::uniform_int_distribution<uint64_t> dist(0, limit);
    return (dist(generator_));
}

SubnetSflqAllocationStatePtr
SharedFlqAllocator::getSubnetState() const {
    auto subnet = subnet_.lock();
    if (!subnet->getAllocationState(pool_type_)) {
        subnet->setAllocationState(Lease::TYPE_V4,
                                   boost::make_shared<SubnetSflqAllocationState>());
    }

    SubnetSflqAllocationStatePtr state;
    state = boost::dynamic_pointer_cast<SubnetSflqAllocationState>
                                       (subnet->getAllocationState(pool_type_));
    if (!state) {
        isc_throw(Unexpected, "SharedFlqAllocator::getSubnetState - wrong allocation state type");
    }

    return (state);
}

void
SharedFlqAllocator::sanityChecksSflqAllocator4(Subnet4Ptr subnet) {
    for (auto const& pool : subnet->getPools(Lease::TYPE_V4)) {
        auto const& capacity(pool->getCapacity());
        if (capacity > MAX_V4_POOL_SIZE) {
            isc_throw(BadValue, "pool capacity " << capacity
                     << " exceeds limit of " << MAX_V4_POOL_SIZE
                     << " for shared-flq allocator on V4 pool "
                     << pool->toText());
        }
    }
}

void
SharedFlqAllocator::sanityChecksSflqAllocator6(Subnet6Ptr subnet) {
    if (subnet->getAllocatorType() == "shared-flq") {
        for (auto const& pool : subnet->getPools(Lease::TYPE_NA)) {
            auto const& capacity(pool->getCapacity());
            if (capacity > MAX_V6_POOL_SIZE) {
                isc_throw(BadValue, "pool capacity " << capacity
                          << " exceeds limit of " << MAX_V6_POOL_SIZE
                          << " for shared-flq allocator on V6 pool "
                          << pool->toText());
            }
        }
    }

    if (subnet->getPdAllocatorType() == "shared-flq") {
        for (auto const& pool : subnet->getPools(Lease::TYPE_PD)) {
            auto const& capacity(pool->getCapacity());
            if (capacity > MAX_V6_POOL_SIZE) {
                isc_throw(BadValue, "pool capacity " << capacity
                          << " exceeds limit of " << MAX_V6_POOL_SIZE
                          << " for shared-flq allocator on V6 pool "
                          << pool->toText());
            }
        }
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
