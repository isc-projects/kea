// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/random_allocator.h>
#include <dhcpsrv/subnet.h>
#include <algorithm>
#include <random>

using namespace isc::asiolink;
using namespace std;

namespace isc {
namespace dhcp {

RandomAllocator::RandomAllocator(Lease::Type type, const WeakSubnetPtr& subnet)
    : Allocator(type, subnet), generator_() {
    random_device rd;
    generator_.seed(rd());
}

IOAddress
RandomAllocator::pickAddressInternal(const ClientClasses& client_classes,
                                     const DuidPtr&,
                                     const IOAddress&) {
    auto subnet = subnet_.lock();
    auto pools = subnet->getPools(pool_type_);

    // Let's first iterate over the pools and identify the ones that
    // meet client class criteria. Then, segregate these pools into
    // the ones that still have available addresses and exhausted
    // ones.
    std::vector<uint64_t> available;
    std::vector<uint64_t> exhausted;
    for (auto i = 0; i < pools.size(); ++i) {
        // Check if the pool is allowed for the client's classes.
        if (pools[i]->clientSupported(client_classes)) {
            // Get or create the pool state.
            auto state = getPoolState(pools[i]);
            if (state->getPermutation()->exhausted()) {
                // Pool is exhausted. It means that all addresses from
                // this pool have been offered. It doesn't mean that
                // leases are allocated for all these addresses. It
                // only means that all have been picked from the pool.
                exhausted.push_back(i);
            } else {
                // There are still available addresses in this pool. It
                // means that not all of them have been offered.
                available.push_back(i);
            }
        }
    }
    // Find a suitable pool.
    PoolPtr pool;
    if (!available.empty()) {
        // There are pools with available addresses. Let's randomly
        // pick one of these pools and get next available address.
        pool = pools[available[getRandomNumber(available.size()-1)]];

    } else if (!exhausted.empty()) {
        // All pools have been exhausted. We will start offering the same
        // addresses from these pools. We need to reset the permutations
        // of the exhausted pools.
        for (auto e : exhausted) {
            getPoolState(pools[e])->getPermutation()->reset();
        }
        // Get random pool from those we just reset.
        pool = pools[exhausted[getRandomNumber(exhausted.size()-1)]];
    }

    // If pool has been found, let's get next address.
    if (pool) {
        auto done = false;
        return (getPoolState(pool)->getPermutation()->next(done));
    }

    // No pool available. There are no pools or client classes do
    // not match.
    return (IOAddress::IPV4_ZERO_ADDRESS());
}

IOAddress
RandomAllocator::pickPrefixInternal(const ClientClasses& client_classes,
                                    Pool6Ptr& pool6,
                                    const DuidPtr&,
                                    PrefixLenMatchType prefix_length_match,
                                    const IOAddress&,
                                    uint8_t hint_prefix_length) {
    auto subnet = subnet_.lock();
    auto pools = subnet->getPools(pool_type_);

    // Let's first iterate over the pools and identify the ones that
    // meet client class criteria. Then, segragate these pools into
    // the ones that still have available addresses and exhausted
    // ones.
    std::vector<uint64_t> available;
    std::vector<uint64_t> exhausted;
    for (auto i = 0; i < pools.size(); ++i) {
        // Check if the pool is allowed for the client's classes.
        if (pools[i]->clientSupported(client_classes)) {
            if (!Allocator::isValidPrefixPool(prefix_length_match, pools[i],
                                              hint_prefix_length)) {
                continue;
            }
            // Get or create the pool state.
            auto state = getPoolState(pools[i]);
            if (state->getPermutation()->exhausted()) {
                // Pool is exhausted. It means that all prefixes from
                // this pool have been offered. It doesn't mean that
                // leases are allocated for all these prefixes. It
                // only means that all have been picked from the pool.
                exhausted.push_back(i);
            } else {
                // There are still available prefixes in this pool. It
                // means that not all of them have been offered.
                available.push_back(i);
            }
        }
    }
    // Find a suitable pool.
    PoolPtr pool;
    if (!available.empty()) {
        // There are pools with available prefixes. Let's randomly
        // pick one of these pools and get next available prefix.
        pool = pools[available[getRandomNumber(available.size() - 1)]];

    } else if (!exhausted.empty()) {
        // All pools have been exhausted. We will start offering the same
        // prefixes from these pools. We need to reset the permutations
        // of the exhausted pools.
        for (auto e : exhausted) {
            getPoolState(pools[e])->getPermutation()->reset();
        }
        // Get random pool from those we just reset.
        pool = pools[exhausted[getRandomNumber(exhausted.size() - 1)]];
    }

    // If pool has been found, let's get next prefix.
    if (pool) {
        auto done = false;
        pool6 = boost::dynamic_pointer_cast<Pool6>(pool);

        if (!pool6) {
            // Something is gravely wrong here
            isc_throw(Unexpected, "Wrong type of pool: "
                      << (pool)->toText()
                      << " is not Pool6");
        }
        return (getPoolState(pool)->getPermutation()->next(done));
    }

    // No pool available. There are no pools or client classes do
    // not match.
    return (IOAddress::IPV6_ZERO_ADDRESS());
}

PoolRandomAllocationStatePtr
RandomAllocator::getPoolState(const PoolPtr& pool) const {
    if (!pool->getAllocationState()) {
        pool->setAllocationState(PoolRandomAllocationState::create(pool));
    }
    return (boost::dynamic_pointer_cast<PoolRandomAllocationState>(pool->getAllocationState()));
}

uint64_t
RandomAllocator::getRandomNumber(uint64_t limit) {
    // Take the short path if there is only one number to randomize from.
    if (limit == 0) {
        return 0;
    }
    std::uniform_int_distribution<uint64_t> dist(0, limit);
    return (dist(generator_));
}

} // end of namespace isc::dhcp
} // end of namespace isc
