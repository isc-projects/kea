// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/flq_allocator.h>
#include <dhcpsrv/ip_range_permutation.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <util/stopwatch.h>
#include <unordered_set>

using namespace isc::asiolink;
using namespace isc::util;
using namespace std;

namespace {
/// @brief An owner string used in the callbacks installed in
/// the lease manager.
const string FLQ_OWNER = "flq";
}

namespace isc {
namespace dhcp {

FreeLeaseQueueAllocator::FreeLeaseQueueAllocator(Lease::Type type, const WeakSubnetPtr& subnet)
    : Allocator(type, subnet), generator_() {
    random_device rd;
    generator_.seed(rd());
}

IOAddress
FreeLeaseQueueAllocator::pickAddressInternal(const ClientClasses& client_classes,
                                             const IdentifierBaseTypePtr&,
                                             const IOAddress&) {
    auto subnet = subnet_.lock();
    auto const& pools = subnet->getPools(pool_type_);
    if (pools.empty()) {
        // No pools, no allocation.
        return (pool_type_ == Lease::TYPE_V4 ? IOAddress::IPV4_ZERO_ADDRESS() : IOAddress::IPV6_ZERO_ADDRESS());
    }
    // Let's first iterate over the pools and identify the ones that
    // meet client class criteria and are not exhausted.
    std::vector<uint64_t> available;
    for (auto i = 0; i < pools.size(); ++i) {
        // Check if the pool is allowed for the client's classes.
        if (pools[i]->clientSupported(client_classes)) {
            // Get or create the pool state.
            auto pool_state = getPoolState(pools[i]);
            if (!pool_state->exhausted()) {
                // There are still available addresses in this pool.
                available.push_back(i);
            }
        }
    }
    if (available.empty()) {
        // No pool meets the client class criteria or all are exhausted.
        return (pool_type_ == Lease::TYPE_V4 ? IOAddress::IPV4_ZERO_ADDRESS() : IOAddress::IPV6_ZERO_ADDRESS());
    }
    // Get a random pool from the available ones.
    auto const& pool = pools[available[getRandomNumber(available.size() - 1)]];

    // Get or create the pool state.
    auto pool_state = getPoolState(pool);

    // The pool should still offer some leases.
    auto free_lease = pool_state->offerFreeLease();
    // It shouldn't happen, but let's be safe.
    if (!free_lease.isV4Zero() && !free_lease.isV6Zero()) {
        return (free_lease);
    }
    // No address available.
    return (pool_type_ == Lease::TYPE_V4 ? IOAddress::IPV4_ZERO_ADDRESS() : IOAddress::IPV6_ZERO_ADDRESS());
}

IOAddress
FreeLeaseQueueAllocator::pickPrefixInternal(const ClientClasses& client_classes,
                                            Pool6Ptr& pool6,
                                            const IdentifierBaseTypePtr&,
                                            PrefixLenMatchType prefix_length_match,
                                            const IOAddress&,
                                            uint8_t hint_prefix_length) {
    auto subnet = subnet_.lock();
    auto const& pools = subnet->getPools(pool_type_);
    if (pools.empty()) {
        // No pool, no allocation.
        return (IOAddress::IPV6_ZERO_ADDRESS());
    }
    // Let's first iterate over the pools and identify the ones that
    // meet client class criteria and are not exhausted.
    std::vector<uint64_t> available;
    for (auto i = 0; i < pools.size(); ++i) {
        // Check if the pool is allowed for the client's classes.
        if (pools[i]->clientSupported(client_classes)) {
            if (!Allocator::isValidPrefixPool(prefix_length_match, pools[i],
                                              hint_prefix_length)) {
                continue;
            }
            // Get or create the pool state.
            auto pool_state = getPoolState(pools[i]);
            if (!pool_state->exhausted()) {
                // There are still available prefixes in this pool.
                available.push_back(i);
            }
        }
    }
    if (available.empty()) {
        // No pool meets the client class criteria or all are exhausted.
        return (IOAddress::IPV6_ZERO_ADDRESS());
    }
    // Get a random pool from the available ones.
    auto const& pool = pools[available[getRandomNumber(available.size() - 1)]];
    pool6 = boost::dynamic_pointer_cast<Pool6>(pool);
    if (!pool6) {
        // Something is gravely wrong here
        isc_throw(Unexpected, "Wrong type of pool: "
                  << (pool)->toText()
                  << " is not Pool6");
    }
    // Get or create the pool state.
    auto pool_state = getPoolState(pool);
    // The pool should still offer some leases.
    auto free_lease = pool_state->offerFreeLease();
    // It shouldn't happen, but let's be safe.
    if (!free_lease.isV6Zero()) {
        return (free_lease);
    }
    // No prefix available.
    return (IOAddress::IPV6_ZERO_ADDRESS());
}

void
FreeLeaseQueueAllocator::initAfterConfigureInternal() {
    auto subnet = subnet_.lock();
    auto const& pools = subnet->getPools(pool_type_);
    if (pools.empty()) {
        // If there are no pools there is nothing to do.
        return;
    }
    Lease4Collection leases4;
    Lease6Collection leases6;
    switch (pool_type_) {
    case Lease::TYPE_V4:
        leases4 = LeaseMgrFactory::instance().getLeases4(subnet->getID());
        populateFreeAddressLeases(leases4, pools);
        break;
    case Lease::TYPE_NA:
    case Lease::TYPE_TA:
        leases6 = LeaseMgrFactory::instance().getLeases6(subnet->getID());
        populateFreeAddressLeases(leases6, pools);
        break;
    case Lease::TYPE_PD:
        leases6 = LeaseMgrFactory::instance().getLeases6(subnet->getID());
        populateFreePrefixDelegationLeases(leases6, pools);
        break;
    default:
        ;
    }
    // Install the callbacks for lease add, update and delete in the interface manager.
    // These callbacks will ensure that we have up-to-date free lease queue.
    auto& lease_mgr = LeaseMgrFactory::instance();
    lease_mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, FLQ_OWNER, subnet->getID(), pool_type_,
                               std::bind(&FreeLeaseQueueAllocator::addLeaseCallback, this,
                                         std::placeholders::_1));
    lease_mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, FLQ_OWNER, subnet->getID(), pool_type_,
                               std::bind(&FreeLeaseQueueAllocator::updateLeaseCallback, this,
                                         std::placeholders::_1));
    lease_mgr.registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, FLQ_OWNER, subnet->getID(), pool_type_,
                               std::bind(&FreeLeaseQueueAllocator::deleteLeaseCallback, this,
                                         std::placeholders::_1));
}

template<typename LeaseCollectionType>
void
FreeLeaseQueueAllocator::populateFreeAddressLeases(const LeaseCollectionType& leases,
                                                   const PoolCollection& pools) {
    auto subnet = subnet_.lock();
    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES)
        .arg(subnet->toText());

    Stopwatch stopwatch;

    // Let's iterate over the lease queue and index them with the
    // unordered_set. Also, elminate the expired leases and those
    // in the expired-reclaimed state.
    unordered_set<IOAddress, IOAddress::Hash> leased_addresses;
    for (auto const& lease : leases) {
        if ((lease->getType() == pool_type_) && (!lease->expired()) && (!lease->stateExpiredReclaimed())) {
            leased_addresses.insert(lease->addr_);
        }
    }
    // For each pool, check if the address is in the leases list.
    size_t free_lease_count = 0;
    for (auto const& pool : pools) {
        // Create the pool permutation so the resulting lease queue is no
        // particular order.
        IPRangePermutation perm(AddressRange(pool->getFirstAddress(), pool->getLastAddress()));
        auto pool_state = getPoolState(pool);
        auto done = false;
        while (!done) {
            auto address = perm.next(done);
            if (address.isV4Zero() || address.isV6Zero()) {
                continue;
            }
            if (leased_addresses.count(address) == 0) {
                // No lease for this address, so add it to the free leases queue.
                pool_state->addFreeLease(address);
            }
        }
        free_lease_count += pool_state->getFreeLeaseCount();
    }

    stopwatch.stop();

    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES_DONE)
        .arg(free_lease_count)
        .arg(subnet->toText())
        .arg(stopwatch.logFormatLastDuration());
}

void
FreeLeaseQueueAllocator::populateFreePrefixDelegationLeases(const Lease6Collection& leases,
                                                            const PoolCollection& pools) {
    auto subnet = subnet_.lock();
    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES)
        .arg(subnet->toText());

    Stopwatch stopwatch;

    // Let's iterate over the lease queue and index them with the
    // unordered_set. Also, elminate the expired leases and those
    // in the expired-reclaimed state.
    unordered_set<IOAddress, IOAddress::Hash> leased_prefixes;
    for (auto const& lease : leases) {
        if ((lease->getType() == Lease::TYPE_PD) && (!lease->expired()) && (!lease->stateExpiredReclaimed())) {
            leased_prefixes.insert(lease->addr_);
        }
    }
    // For each pool, check if the prefix is in the leases list.
    size_t free_lease_count = 0;
    for (auto const& pool : pools) {
        auto pool6 = boost::dynamic_pointer_cast<Pool6>(pool);
        if (!pool6) {
            continue;
        }
        // Create the pool permutation so the resulting lease queue is no
        // particular order.
        IPRangePermutation perm(PrefixRange(pool->getFirstAddress(),
                                            pool->getLastAddress(),
                                            pool6->getLength()));
        auto pool_state = getPoolState(pool);
        auto done = false;
        while (!done) {
            auto prefix = perm.next(done);
            if (prefix.isV4Zero() || prefix.isV6Zero()) {
                continue;
            }
            if (leased_prefixes.count(prefix) == 0) {
                // No lease for this prefix, so add it to the free leases queue.
                pool_state->addFreeLease(prefix);
            }
        }
        free_lease_count += pool_state->getFreeLeaseCount();
    }

    stopwatch.stop();

    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES_DONE)
        .arg(free_lease_count)
        .arg(subnet->toText())
        .arg(stopwatch.logFormatLastDuration());
}

PoolFreeLeaseQueueAllocationStatePtr
FreeLeaseQueueAllocator::getPoolState(const PoolPtr& pool) const {
    if (!pool->getAllocationState()) {
        pool->setAllocationState(PoolFreeLeaseQueueAllocationState::create(pool));
    }
    return (boost::dynamic_pointer_cast<PoolFreeLeaseQueueAllocationState>(pool->getAllocationState()));
}

PoolPtr
FreeLeaseQueueAllocator::getLeasePool(const LeasePtr& lease) const {
    auto subnet = subnet_.lock();
    if (!subnet) {
        return (PoolPtr());
    }
    auto pool = subnet->getPool(pool_type_, lease->addr_, false);
    return (pool);
}

void
FreeLeaseQueueAllocator::addLeaseCallback(LeasePtr lease) {
    MultiThreadingLock lock(mutex_);
    addLeaseCallbackInternal(lease);
}

void
FreeLeaseQueueAllocator::addLeaseCallbackInternal(LeasePtr lease) {
    if (lease->expired()) {
        return;
    }
    auto pool = getLeasePool(lease);
    if (!pool) {
        return;
    }
    getPoolState(pool)->deleteFreeLease(lease->addr_);
}

void
FreeLeaseQueueAllocator::updateLeaseCallback(LeasePtr lease) {
    MultiThreadingLock lock(mutex_);
    updateLeaseCallbackInternal(lease);
}

void
FreeLeaseQueueAllocator::updateLeaseCallbackInternal(LeasePtr lease) {
    auto pool = getLeasePool(lease);
    if (!pool) {
        return;
    }
    auto pool_state = getPoolState(pool);
    if (lease->stateExpiredReclaimed() || (lease->expired())) {
        pool_state->addFreeLease(lease->addr_);
    } else {
        pool_state->deleteFreeLease(lease->addr_);
    }
}

void
FreeLeaseQueueAllocator::deleteLeaseCallback(LeasePtr lease) {
    MultiThreadingLock lock(mutex_);
    deleteLeaseCallbackInternal(lease);
}

void
FreeLeaseQueueAllocator::deleteLeaseCallbackInternal(LeasePtr lease) {
    auto pool = getLeasePool(lease);
    if (!pool) {
        return;
    }
    getPoolState(pool)->addFreeLease(lease->addr_);
}

uint64_t
FreeLeaseQueueAllocator::getRandomNumber(uint64_t limit) {
    // Take the short path if there is only one number to randomize from.
    if (limit == 0) {
        return (0);
    }
    std::uniform_int_distribution<uint64_t> dist(0, limit);
    return (dist(generator_));
}

} // end of namespace isc::dhcp
} // end of namespace isc
