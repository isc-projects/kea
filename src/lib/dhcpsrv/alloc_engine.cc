// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/lease_mgr_factory.h>

#include <cstring>

#include <string.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

AllocEngine::IterativeAllocator::IterativeAllocator()
    :Allocator() {
}

isc::asiolink::IOAddress
AllocEngine::IterativeAllocator::increaseAddress(const isc::asiolink::IOAddress& addr) {
    // Get a buffer holding an address.
    const std::vector<uint8_t>& vec = addr.toBytes();
    // Get the address length.
    const int len = vec.size();

    // Since the same array will be used to hold the IPv4 and IPv6
    // address we have to make sure that the size of the array
    // we allocate will work for both types of address.
    BOOST_STATIC_ASSERT(V4ADDRESS_LEN <= V6ADDRESS_LEN);
    uint8_t packed[V6ADDRESS_LEN];

    // Copy the address. It can be either V4 or V6.
    std::memcpy(packed, &vec[0], len);

    // Increase the address.
    for (int i = len - 1; i >= 0; --i) {
        ++packed[i];
        if (packed[i] != 0) {
            break;
        }
    }

    return (IOAddress::fromBytes(addr.getFamily(), packed));
}


isc::asiolink::IOAddress
AllocEngine::IterativeAllocator::pickAddress(const Subnet6Ptr& subnet,
                                             const DuidPtr&,
                                             const IOAddress&) {

    // Let's get the last allocated address. It is usually set correctly,
    // but there are times when it won't be (like after removing a pool or
    // perhaps restaring the server).
    IOAddress last = subnet->getLastAllocated();

    const Pool6Collection& pools = subnet->getPools();

    if (pools.empty()) {
        isc_throw(AllocFailed, "No pools defined in selected subnet");
    }

    // first we need to find a pool the last address belongs to.
    Pool6Collection::const_iterator it;
    for (it = pools.begin(); it != pools.end(); ++it) {
        if ((*it)->inRange(last)) {
            break;
        }
    }

    // last one was bogus for one of several reasons:
    // - we just booted up and that's the first address we're allocating
    // - a subnet was removed or other reconfiguration just completed
    // - perhaps allocation algorithm was changed
    if (it == pools.end()) {
        // ok to access first element directly. We checked that pools is non-empty
        IOAddress next = pools[0]->getFirstAddress();
        subnet->setLastAllocated(next);
        return (next);
    }

    // Ok, we have a pool that the last address belonged to, let's use it.

    IOAddress next = increaseAddress(last); // basically addr++
    if ((*it)->inRange(next)) {
        // the next one is in the pool as well, so we haven't hit pool boundary yet
        subnet->setLastAllocated(next);
        return (next);
    }

    // We hit pool boundary, let's try to jump to the next pool and try again
    ++it;
    if (it == pools.end()) {
        // Really out of luck today. That was the last pool. Let's rewind
        // to the beginning.
        next = pools[0]->getFirstAddress();
        subnet->setLastAllocated(next);
        return (next);
    }

    // there is a next pool, let's try first adddress from it
    next = (*it)->getFirstAddress();
    subnet->setLastAllocated(next);
    return (next);
}

AllocEngine::HashedAllocator::HashedAllocator()
    :Allocator() {
    isc_throw(NotImplemented, "Hashed allocator is not implemented");
}


isc::asiolink::IOAddress
AllocEngine::HashedAllocator::pickAddress(const Subnet6Ptr&,
                                             const DuidPtr&,
                                             const IOAddress&) {
    isc_throw(NotImplemented, "Hashed allocator is not implemented");
}

AllocEngine::RandomAllocator::RandomAllocator()
    :Allocator() {
    isc_throw(NotImplemented, "Random allocator is not implemented");
}


isc::asiolink::IOAddress
AllocEngine::RandomAllocator::pickAddress(const Subnet6Ptr&,
                                             const DuidPtr&,
                                             const IOAddress&) {
    isc_throw(NotImplemented, "Random allocator is not implemented");
}


AllocEngine::AllocEngine(AllocType engine_type, unsigned int attempts)
    :attempts_(attempts) {
    switch (engine_type) {
    case ALLOC_ITERATIVE:
        allocator_ = boost::shared_ptr<Allocator>(new IterativeAllocator());
        break;
    case ALLOC_HASHED:
        allocator_ = boost::shared_ptr<Allocator>(new HashedAllocator());
        break;
    case ALLOC_RANDOM:
        allocator_ = boost::shared_ptr<Allocator>(new RandomAllocator());
        break;

    default:
        isc_throw(BadValue, "Invalid/unsupported allocation algorithm");
    }
}

Lease6Ptr
AllocEngine::allocateAddress6(const Subnet6Ptr& subnet,
                              const DuidPtr& duid,
                              uint32_t iaid,
                              const IOAddress& hint,
                              bool fake_allocation /* = false */ ) {

    // That check is not necessary. We create allocator in AllocEngine
    // constructor
    if (!allocator_) {
        isc_throw(InvalidOperation, "No allocator selected");
    }

    // check if there's existing lease for that subnet/duid/iaid combination.
    Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(*duid, iaid, subnet->getID());
    if (existing) {
        // we have a lease already. This is a returning client, probably after
        // his reboot.
        return (existing);
    }

    // check if the hint is in pool and is available
    if (subnet->inPool(hint)) {
        existing = LeaseMgrFactory::instance().getLease6(hint);
        if (!existing) {
            /// @todo: check if the hint is reserved once we have host support
            /// implemented

            // the hint is valid and not currently used, let's create a lease for it
            Lease6Ptr lease = createLease(subnet, duid, iaid, hint, fake_allocation);

            // It can happen that the lease allocation failed (we could have lost
            // the race condition. That means that the hint is lo longer usable and
            // we need to continue the regular allocation path.
            if (lease) {
                return (lease);
            }
        }
    }

    unsigned int i = attempts_;
    do {
        IOAddress candidate = allocator_->pickAddress(subnet, duid, hint);

        /// @todo: check if the address is reserved once we have host support
        /// implemented

        Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(candidate);
        // there's no existing lease for selected candidate, so it is
        // free. Let's allocate it.
        if (!existing) {
            Lease6Ptr lease = createLease(subnet, duid, iaid, candidate,
                                          fake_allocation);
            if (lease) {
                return (lease);
            }

            // Although the address was free just microseconds ago, it may have
            // been taken just now. If the lease insertion fails, we continue
            // allocation attempts.
        }

        // continue trying allocation until we run out of attempts
        // (or attempts are set to 0, which means infinite)
        --i;
    } while ( i || !attempts_);

    isc_throw(AllocFailed, "Failed to allocate address after " << attempts_
              << " tries");
}

Lease6Ptr AllocEngine::createLease(const Subnet6Ptr& subnet,
                                   const DuidPtr& duid,
                                   uint32_t iaid,
                                   const IOAddress& addr,
                                   bool fake_allocation /*= false */ ) {

    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr, duid, iaid,
                               subnet->getPreferred(), subnet->getValid(),
                               subnet->getT1(), subnet->getT2(), subnet->getID()));

    if (!fake_allocation) {
        // That is a real (REQUEST) allocation
        bool status = LeaseMgrFactory::instance().addLease(lease);

        if (status) {

            return (lease);
        } else {
            // One of many failures with LeaseMgr (e.g. lost connection to the
            // database, database failed etc.). One notable case for that
            // is that we are working in multi-process mode and we lost a race
            // (some other process got that address first)
            return (Lease6Ptr());
        }
    } else {
        // That is only fake (SOLICIT without rapid-commit) allocation

        // It is for advertise only. We should not insert the lease into LeaseMgr,
        // but rather check that we could have inserted it.
        Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(addr);
        if (!existing) {
            return (lease);
        } else {
            return (Lease6Ptr());
        }
    }
}

AllocEngine::~AllocEngine() {
    // no need to delete allocator. smart_ptr will do the trick for us
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
