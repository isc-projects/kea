// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>

#include <cstring>
#include <vector>
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

    // Start increasing the least significant byte
    for (int i = len - 1; i >= 0; --i) {
        ++packed[i];
        // if we haven't overflowed (0xff -> 0x0), than we are done
        if (packed[i] != 0) {
            break;
        }
    }

    return (IOAddress::fromBytes(addr.getFamily(), packed));
}


isc::asiolink::IOAddress
AllocEngine::IterativeAllocator::pickAddress(const SubnetPtr& subnet,
                                             const DuidPtr&,
                                             const IOAddress&) {

    // Let's get the last allocated address. It is usually set correctly,
    // but there are times when it won't be (like after removing a pool or
    // perhaps restaring the server).
    IOAddress last = subnet->getLastAllocated();

    const PoolCollection& pools = subnet->getPools();

    if (pools.empty()) {
        isc_throw(AllocFailed, "No pools defined in selected subnet");
    }

    // first we need to find a pool the last address belongs to.
    PoolCollection::const_iterator it;
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
AllocEngine::HashedAllocator::pickAddress(const SubnetPtr&,
                                          const DuidPtr&,
                                          const IOAddress&) {
    isc_throw(NotImplemented, "Hashed allocator is not implemented");
}

AllocEngine::RandomAllocator::RandomAllocator()
    :Allocator() {
    isc_throw(NotImplemented, "Random allocator is not implemented");
}


isc::asiolink::IOAddress
AllocEngine::RandomAllocator::pickAddress(const SubnetPtr&,
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

    try {
        // That check is not necessary. We create allocator in AllocEngine
        // constructor
        if (!allocator_) {
            isc_throw(InvalidOperation, "No allocator selected");
        }

        if (!subnet) {
            isc_throw(InvalidOperation, "Subnet is required for allocation");
        }

        if (!duid) {
            isc_throw(InvalidOperation, "DUID is mandatory for allocation");
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
                Lease6Ptr lease = createLease6(subnet, duid, iaid, hint, fake_allocation);

                // It can happen that the lease allocation failed (we could have lost
                // the race condition. That means that the hint is lo longer usable and
                // we need to continue the regular allocation path.
                if (lease) {
                    return (lease);
                }
            } else {
                if (existing->expired()) {
                    return (reuseExpiredLease(existing, subnet, duid, iaid,
                                              fake_allocation));
                }

            }
        }

        // Hint is in the pool but is not available. Search the pool until first of
        // the following occurs:
        // - we find a free address
        // - we find an address for which the lease has expired
        // - we exhaust number of tries
        //
        // @todo: Current code does not handle pool exhaustion well. It will be
        // improved. Current problems:
        // 1. with attempts set to too large value (e.g. 1000) and a small pool (e.g.
        // 10 addresses), we will iterate over it 100 times before giving up
        // 2. attempts 0 mean unlimited (this is really UINT_MAX, not infinite)
        // 3. the whole concept of infinite attempts is just asking for infinite loop
        // We may consider some form or reference counting (this pool has X addresses
        // left), but this has one major problem. We exactly control allocation
        // moment, but we currently do not control expiration time at all

        unsigned int i = attempts_;
        do {
            IOAddress candidate = allocator_->pickAddress(subnet, duid, hint);

            /// @todo: check if the address is reserved once we have host support
            /// implemented

            Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(candidate);
            if (!existing) {
                // there's no existing lease for selected candidate, so it is
                // free. Let's allocate it.
                Lease6Ptr lease = createLease6(subnet, duid, iaid, candidate,
                                              fake_allocation);
                if (lease) {
                    return (lease);
                }

                // Although the address was free just microseconds ago, it may have
                // been taken just now. If the lease insertion fails, we continue
                // allocation attempts.
            } else {
                if (existing->expired()) {
                    return (reuseExpiredLease(existing, subnet, duid, iaid,
                                              fake_allocation));
                }
            }

            // Continue trying allocation until we run out of attempts
            // (or attempts are set to 0, which means infinite)
            --i;
        } while ((i > 0) || !attempts_);

        // Unable to allocate an address, return an empty lease.
        LOG_WARN(dhcpsrv_logger, DHCPSRV_ADDRESS6_ALLOC_FAIL).arg(attempts_);

    } catch (const isc::Exception& e) {

        // Some other error, return an empty lease.
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_ADDRESS6_ALLOC_ERROR).arg(e.what());
    }

    return (Lease6Ptr());
}

Lease4Ptr
AllocEngine::allocateAddress4(const SubnetPtr& subnet,
                              const ClientIdPtr& clientid,
                              const HWAddrPtr& hwaddr,
                              const IOAddress& hint,
                              bool fake_allocation /* = false */ ) {

    try {
        // Allocator is always created in AllocEngine constructor and there is
        // currently no other way to set it, so that check is not really necessary.
        if (!allocator_) {
            isc_throw(InvalidOperation, "No allocator selected");
        }

        if (!subnet) {
            isc_throw(InvalidOperation, "Can't allocate IPv4 address without subnet");
        }

        if (!hwaddr) {
            isc_throw(InvalidOperation, "HWAddr must be defined");
        }

        // Check if there's existing lease for that subnet/clientid/hwaddr combination.
        Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(*hwaddr, subnet->getID());
        if (existing) {
            // We have a lease already. This is a returning client, probably after
            // its reboot.
            existing = renewLease4(subnet, clientid, hwaddr, existing, fake_allocation);
            if (existing) {
                return (existing);
            }

            // If renewal failed (e.g. the lease no longer matches current configuration)
            // let's continue the allocation process
        }

        if (clientid) {
            existing = LeaseMgrFactory::instance().getLease4(*clientid, subnet->getID());
            if (existing) {
                // we have a lease already. This is a returning client, probably after
                // its reboot.
                existing = renewLease4(subnet, clientid, hwaddr, existing, fake_allocation);
                // @todo: produce a warning. We haven't found him using MAC address, but
                // we found him using client-id
                if (existing) {
                    return (existing);
                }
            }
        }

        // check if the hint is in pool and is available
        if (subnet->inPool(hint)) {
            existing = LeaseMgrFactory::instance().getLease4(hint);
            if (!existing) {
                /// @todo: Check if the hint is reserved once we have host support
                /// implemented

                // The hint is valid and not currently used, let's create a lease for it
                Lease4Ptr lease = createLease4(subnet, clientid, hwaddr, hint, fake_allocation);

                // It can happen that the lease allocation failed (we could have lost
                // the race condition. That means that the hint is lo longer usable and
                // we need to continue the regular allocation path.
                if (lease) {
                    return (lease);
                }
            } else {
                if (existing->expired()) {
                    return (reuseExpiredLease(existing, subnet, clientid, hwaddr,
                                              fake_allocation));
                }

            }
        }

        // Hint is in the pool but is not available. Search the pool until first of
        // the following occurs:
        // - we find a free address
        // - we find an address for which the lease has expired
        // - we exhaust the number of tries
        //
        // @todo: Current code does not handle pool exhaustion well. It will be
        // improved. Current problems:
        // 1. with attempts set to too large value (e.g. 1000) and a small pool (e.g.
        // 10 addresses), we will iterate over it 100 times before giving up
        // 2. attempts 0 mean unlimited (this is really UINT_MAX, not infinite)
        // 3. the whole concept of infinite attempts is just asking for infinite loop
        // We may consider some form or reference counting (this pool has X addresses
        // left), but this has one major problem. We exactly control allocation
        // moment, but we currently do not control expiration time at all

        unsigned int i = attempts_;
        do {
            IOAddress candidate = allocator_->pickAddress(subnet, clientid, hint);

            /// @todo: check if the address is reserved once we have host support
            /// implemented

            Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(candidate);
            if (!existing) {
                // there's no existing lease for selected candidate, so it is
                // free. Let's allocate it.
                Lease4Ptr lease = createLease4(subnet, clientid, hwaddr, candidate,
                                              fake_allocation);
                if (lease) {
                    return (lease);
                }

                // Although the address was free just microseconds ago, it may have
                // been taken just now. If the lease insertion fails, we continue
                // allocation attempts.
            } else {
                if (existing->expired()) {
                    return (reuseExpiredLease(existing, subnet, clientid, hwaddr,
                                              fake_allocation));
                }
            }

            // Continue trying allocation until we run out of attempts
            // (or attempts are set to 0, which means infinite)
            --i;
        } while ((i > 0) || !attempts_);

        // Unable to allocate an address, return an empty lease.
        LOG_WARN(dhcpsrv_logger, DHCPSRV_ADDRESS4_ALLOC_FAIL).arg(attempts_);

    } catch (const isc::Exception& e) {

        // Some other error, return an empty lease.
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_ADDRESS4_ALLOC_ERROR).arg(e.what());
    }
    return (Lease4Ptr());
}

Lease4Ptr AllocEngine::renewLease4(const SubnetPtr& subnet,
                                   const ClientIdPtr& clientid,
                                   const HWAddrPtr& hwaddr,
                                   const Lease4Ptr& lease,
                                   bool fake_allocation /* = false */) {

    lease->subnet_id_ = subnet->getID();
    lease->hwaddr_ = hwaddr->hwaddr_;
    lease->client_id_ = clientid;
    lease->cltt_ = time(NULL);
    lease->t1_ = subnet->getT1();
    lease->t2_ = subnet->getT2();
    lease->valid_lft_ = subnet->getValid();

    if (!fake_allocation) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease4(lease);
    }

    return (lease);
}

Lease6Ptr AllocEngine::reuseExpiredLease(Lease6Ptr& expired,
                                         const Subnet6Ptr& subnet,
                                         const DuidPtr& duid,
                                         uint32_t iaid,
                                         bool fake_allocation /*= false */ ) {

    if (!expired->expired()) {
        isc_throw(BadValue, "Attempt to recycle lease that is still valid");
    }

    // address, lease type and prefixlen (0) stay the same
    expired->iaid_ = iaid;
    expired->duid_ = duid;
    expired->preferred_lft_ = subnet->getPreferred();
    expired->valid_lft_ = subnet->getValid();
    expired->t1_ = subnet->getT1();
    expired->t2_ = subnet->getT2();
    expired->cltt_ = time(NULL);
    expired->subnet_id_ = subnet->getID();
    expired->fixed_ = false;
    expired->hostname_ = std::string("");
    expired->fqdn_fwd_ = false;
    expired->fqdn_rev_ = false;

    /// @todo: log here that the lease was reused (there's ticket #2524 for
    /// logging in libdhcpsrv)

    if (!fake_allocation) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease6(expired);
    }

    // We do nothing for SOLICIT. We'll just update database when
    // the client gets back to us with REQUEST message.

    // it's not really expired at this stage anymore - let's return it as
    // an updated lease
    return (expired);
}

Lease4Ptr AllocEngine::reuseExpiredLease(Lease4Ptr& expired,
                                         const SubnetPtr& subnet,
                                         const ClientIdPtr& clientid,
                                         const HWAddrPtr& hwaddr,
                                         bool fake_allocation /*= false */ ) {

    if (!expired->expired()) {
        isc_throw(BadValue, "Attempt to recycle lease that is still valid");
    }

    // address, lease type and prefixlen (0) stay the same
    expired->client_id_ = clientid;
    expired->hwaddr_ = hwaddr->hwaddr_;
    expired->valid_lft_ = subnet->getValid();
    expired->t1_ = subnet->getT1();
    expired->t2_ = subnet->getT2();
    expired->cltt_ = time(NULL);
    expired->subnet_id_ = subnet->getID();
    expired->fixed_ = false;
    expired->hostname_ = std::string("");
    expired->fqdn_fwd_ = false;
    expired->fqdn_rev_ = false;

    /// @todo: log here that the lease was reused (there's ticket #2524 for
    /// logging in libdhcpsrv)

    if (!fake_allocation) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease4(expired);
    }

    // We do nothing for SOLICIT. We'll just update database when
    // the client gets back to us with REQUEST message.

    // it's not really expired at this stage anymore - let's return it as
    // an updated lease
    return (expired);
}

Lease6Ptr AllocEngine::createLease6(const Subnet6Ptr& subnet,
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

Lease4Ptr AllocEngine::createLease4(const SubnetPtr& subnet,
                                    const DuidPtr& clientid,
                                    const HWAddrPtr& hwaddr,
                                    const IOAddress& addr,
                                    bool fake_allocation /*= false */ ) {
    if (!hwaddr) {
        isc_throw(BadValue, "Can't create a lease with NULL HW address");
    }
    time_t now = time(NULL);

    // @todo: remove this kludge after ticket #2590 is implemented
    std::vector<uint8_t> local_copy;
    if (clientid) {
        local_copy = clientid->getDuid();
    }

    Lease4Ptr lease(new Lease4(addr, &hwaddr->hwaddr_[0], hwaddr->hwaddr_.size(),
                               &local_copy[0], local_copy.size(), subnet->getValid(),
                               subnet->getT1(), subnet->getT2(), now,
                               subnet->getID()));

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
            return (Lease4Ptr());
        }
    } else {
        // That is only fake (DISCOVER) allocation

        // It is for OFFER only. We should not insert the lease into LeaseMgr,
        // but rather check that we could have inserted it.
        Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(addr);
        if (!existing) {
            return (lease);
        } else {
            return (Lease4Ptr());
        }
    }
}

AllocEngine::~AllocEngine() {
    // no need to delete allocator. smart_ptr will do the trick for us
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
