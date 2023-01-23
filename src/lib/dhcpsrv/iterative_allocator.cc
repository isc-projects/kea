// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/iterative_allocator.h>
#include <exceptions/exceptions.h>
#include <boost/pointer_cast.hpp>
#include <cstring>

using namespace isc::asiolink;
using namespace std;

namespace isc {
namespace dhcp {

IterativeAllocator::IterativeAllocator(Lease::Type type,
                                       const WeakSubnetPtr& subnet)
    : Allocator(type, subnet) {
}

isc::asiolink::IOAddress
IterativeAllocator::increasePrefix(const IOAddress& prefix,
                                   const uint8_t prefix_len) {
    if (!prefix.isV6()) {
        isc_throw(BadValue, "Prefix operations are for IPv6 only (attempted to "
                  "increase prefix " << prefix << ")");
    }

    // Get a buffer holding an address.
    const std::vector<uint8_t>& vec = prefix.toBytes();

    if (prefix_len < 1 || prefix_len > 128) {
        isc_throw(BadValue, "Cannot increase prefix: invalid prefix length: "
                  << prefix_len);
    }

    uint8_t n_bytes = (prefix_len - 1)/8;
    uint8_t n_bits = 8 - (prefix_len - n_bytes*8);
    uint8_t mask = 1 << n_bits;

    // Explanation: n_bytes specifies number of full bytes that are in-prefix.
    // They can also be used as an offset for the first byte that is not in
    // prefix. n_bits specifies number of bits on the last byte that is
    // (often partially) in prefix. For example for a /125 prefix, the values
    // are 15 and 3, respectively. Mask is a bitmask that has the least
    // significant bit from the prefix set.

    uint8_t packed[V6ADDRESS_LEN];

    // Copy the address. It must be V6, but we already checked that.
    memcpy(packed, &vec[0], V6ADDRESS_LEN);

    // Can we safely increase only the last byte in prefix without overflow?
    if (packed[n_bytes] + uint16_t(mask) < 256u) {
        packed[n_bytes] += mask;
        return (IOAddress::fromBytes(AF_INET6, packed));
    }

    // Overflow (done on uint8_t, but the sum is greater than 255)
    packed[n_bytes] += mask;

    // Deal with the overflow. Start increasing the least significant byte
    for (int i = n_bytes - 1; i >= 0; --i) {
        ++packed[i];
        // If we haven't overflowed (0xff->0x0) the next byte, then we are done
        if (packed[i] != 0) {
            break;
        }
    }

    return (IOAddress::fromBytes(AF_INET6, packed));
}

IOAddress
IterativeAllocator::increaseAddress(const IOAddress& address,
                                    bool prefix,
                                    const uint8_t prefix_len) {
    if (!prefix) {
        return (IOAddress::increase(address));
    } else {
        return (increasePrefix(address, prefix_len));
    }
}

IOAddress
IterativeAllocator::pickAddressInternal(const ClientClasses& client_classes,
                                        const DuidPtr&,
                                        const IOAddress&) {
    // Let's get the last allocated address. It is usually set correctly,
    // but there are times when it won't be (like after removing a pool or
    // perhaps restarting the server).
    IOAddress last = getSubnetState()->getLastAllocated();
    bool valid = true;
    bool retrying = false;

    const PoolCollection& pools = subnet_.lock()->getPools(pool_type_);

    if (pools.empty()) {
        isc_throw(AllocFailed, "No pools defined in selected subnet");
    }

    // first we need to find a pool the last address belongs to.
    PoolCollection::const_iterator it;
    PoolCollection::const_iterator first = pools.end();
    PoolPtr first_pool;
    for (it = pools.begin(); it != pools.end(); ++it) {
        if (!(*it)->clientSupported(client_classes)) {
            continue;
        }
        if (first == pools.end()) {
            first = it;
        }
        if ((*it)->inRange(last)) {
            break;
        }
    }

    // Caller checked this cannot happen
    if (first == pools.end()) {
        isc_throw(AllocFailed, "No allowed pools defined in selected subnet");
    }

    // last one was bogus for one of several reasons:
    // - we just booted up and that's the first address we're allocating
    // - a subnet was removed or other reconfiguration just completed
    // - perhaps allocation algorithm was changed
    // - last pool does not allow this client
    if (it == pools.end()) {
        it = first;
    }

    for (;;) {
        // Trying next pool
        if (retrying) {
            for (; it != pools.end(); ++it) {
                if ((*it)->clientSupported(client_classes)) {
                    break;
                }
            }
            if (it == pools.end()) {
                // Really out of luck today. That was the last pool.
                break;
            }
        }

        last = getPoolState(*it)->getLastAllocated();
        valid = getPoolState(*it)->isLastAllocatedValid();
        if (!valid && (last == (*it)->getFirstAddress())) {
            // Pool was (re)initialized
            getPoolState(*it)->setLastAllocated(last);
            getSubnetState()->setLastAllocated(last);
            return (last);
        }
        // still can be bogus
        if (valid && !(*it)->inRange(last)) {
            valid = false;
            getPoolState(*it)->resetLastAllocated();
            getPoolState(*it)->setLastAllocated((*it)->getFirstAddress());
        }

        if (valid) {
            IOAddress next = increaseAddress(last, false, 0);
            if ((*it)->inRange(next)) {
                // the next one is in the pool as well, so we haven't hit
                // pool boundary yet
                getPoolState(*it)->setLastAllocated(next);
                getSubnetState()->setLastAllocated(next);
                return (next);
            }

            valid = false;
            getPoolState(*it)->resetLastAllocated();
        }
        // We hit pool boundary, let's try to jump to the next pool and try again
        ++it;
        retrying = true;
    }

    // Let's rewind to the beginning.
    for (it = first; it != pools.end(); ++it) {
        if ((*it)->clientSupported(client_classes)) {
            getPoolState(*it)->setLastAllocated((*it)->getFirstAddress());
            getPoolState(*it)->resetLastAllocated();
        }
    }

    // ok to access first element directly. We checked that pools is non-empty
    last = getPoolState(*first)->getLastAllocated();
    getPoolState(*first)->setLastAllocated(last);
    getSubnetState()->setLastAllocated(last);
    return (last);
}

IOAddress
IterativeAllocator::pickPrefixInternal(const ClientClasses& client_classes,
                                       Pool6Ptr& pool6,
                                       const DuidPtr&,
                                       PrefixLenMatchType prefix_length_match,
                                       const IOAddress&,
                                       uint8_t hint_prefix_length) {
    uint8_t prefix_len = 0;

    // Let's get the last allocated prefix. It is usually set correctly,
    // but there are times when it won't be (like after removing a pool or
    // perhaps restarting the server).
    IOAddress last = getSubnetState()->getLastAllocated();
    bool valid = true;
    bool retrying = false;

    const PoolCollection& pools = subnet_.lock()->getPools(pool_type_);

    if (pools.empty()) {
        isc_throw(AllocFailed, "No pools defined in selected subnet");
    }

    // first we need to find a pool the last prefix belongs to.
    PoolCollection::const_iterator it;
    PoolCollection::const_iterator first = pools.end();
    PoolPtr first_pool;
    for (it = pools.begin(); it != pools.end(); ++it) {
        if (!(*it)->clientSupported(client_classes)) {
            continue;
        }
        if (!Allocator::isValidPrefixPool(prefix_length_match, *it,
                                          hint_prefix_length)) {
            continue;
        }
        if (first == pools.end()) {
            first = it;
        }
        if ((*it)->inRange(last)) {
            break;
        }
    }

    // Caller checked this cannot happen
    if (first == pools.end()) {
        isc_throw(AllocFailed, "No allowed pools defined in selected subnet");
    }

    // last one was bogus for one of several reasons:
    // - we just booted up and that's the first prefix we're allocating
    // - a subnet was removed or other reconfiguration just completed
    // - perhaps allocation algorithm was changed
    // - last pool does not allow this client
    if (it == pools.end()) {
        it = first;
    }

    for (;;) {
        // Trying next pool
        if (retrying) {
            for (; it != pools.end(); ++it) {
                if ((*it)->clientSupported(client_classes)) {
                    if (!Allocator::isValidPrefixPool(prefix_length_match, *it,
                                                      hint_prefix_length)) {
                        continue;
                    }
                    break;
                }
            }
            if (it == pools.end()) {
                // Really out of luck today. That was the last pool.
                break;
            }
        }

        last = getPoolState(*it)->getLastAllocated();
        valid = getPoolState(*it)->isLastAllocatedValid();
        if (!valid && (last == (*it)->getFirstAddress())) {
            // Pool was (re)initialized
            getPoolState(*it)->setLastAllocated(last);
            getSubnetState()->setLastAllocated(last);

            pool6 = boost::dynamic_pointer_cast<Pool6>(*it);

            if (!pool6) {
                // Something is gravely wrong here
                isc_throw(Unexpected, "Wrong type of pool: "
                          << (*it)->toText()
                          << " is not Pool6");
            }

            return (last);
        }
        // still can be bogus
        if (valid && !(*it)->inRange(last)) {
            valid = false;
            getPoolState(*it)->resetLastAllocated();
            getPoolState(*it)->setLastAllocated((*it)->getFirstAddress());
        }

        if (valid) {
            // Ok, we have a pool that the last prefix belonged to, let's use it.
            pool6 = boost::dynamic_pointer_cast<Pool6>(*it);
            if (!pool6) {
                // Something is gravely wrong here
                isc_throw(Unexpected, "Wrong type of pool: "
                          << (*it)->toText()
                          << " is not Pool6");
            }

            // Get the prefix length
            prefix_len = pool6->getLength();

            IOAddress next = increaseAddress(last, true, prefix_len);
            if ((*it)->inRange(next)) {
                // the next one is in the pool as well, so we haven't hit
                // pool boundary yet
                getPoolState(*it)->setLastAllocated(next);
                getSubnetState()->setLastAllocated(next);
                return (next);
            }

            valid = false;
            getPoolState(*it)->resetLastAllocated();
        }
        // We hit pool boundary, let's try to jump to the next pool and try again
        ++it;
        retrying = true;
    }

    // Let's rewind to the beginning.
    for (it = first; it != pools.end(); ++it) {
        if ((*it)->clientSupported(client_classes)) {
            if (!Allocator::isValidPrefixPool(prefix_length_match, *it,
                                              hint_prefix_length)) {
                continue;
            }
            getPoolState(*it)->setLastAllocated((*it)->getFirstAddress());
            getPoolState(*it)->resetLastAllocated();
        }
    }

    // ok to access first element directly. We checked that pools is non-empty
    last = getPoolState(*first)->getLastAllocated();
    getPoolState(*first)->setLastAllocated(last);
    getSubnetState()->setLastAllocated(last);

    pool6 = boost::dynamic_pointer_cast<Pool6>(*first);
    if (!pool6) {
        // Something is gravely wrong here
        isc_throw(Unexpected, "Wrong type of pool: "
                  << (*it)->toText()
                  << " is not Pool6");
    }
    return (last);
}

SubnetIterativeAllocationStatePtr
IterativeAllocator::getSubnetState() const {
    auto subnet = subnet_.lock();
    if (!subnet->getAllocationState(pool_type_)) {
        subnet->setAllocationState(pool_type_, SubnetIterativeAllocationState::create(subnet));
    }
    return (boost::dynamic_pointer_cast<SubnetIterativeAllocationState>(subnet->getAllocationState(pool_type_)));
}

PoolIterativeAllocationStatePtr
IterativeAllocator::getPoolState(const PoolPtr& pool) const {
    if (!pool->getAllocationState()) {
        pool->setAllocationState(PoolIterativeAllocationState::create(pool));
    }
    return (boost::dynamic_pointer_cast<PoolIterativeAllocationState>(pool->getAllocationState()));
}

} // end of namespace isc::dhcp
} // end of namespace isc
