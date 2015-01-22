// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/lease_mgr_factory.h>

#include <hooks/server_hooks.h>
#include <hooks/hooks_manager.h>

#include <cstring>
#include <vector>
#include <string.h>

using namespace isc::asiolink;
using namespace isc::hooks;

namespace {

/// Structure that holds registered hook indexes
struct AllocEngineHooks {
    int hook_index_lease4_select_; ///< index for "lease4_receive" hook point
    int hook_index_lease4_renew_;  ///< index for "lease4_renew" hook point
    int hook_index_lease6_select_; ///< index for "lease6_receive" hook point

    /// Constructor that registers hook points for AllocationEngine
    AllocEngineHooks() {
        hook_index_lease4_select_ = HooksManager::registerHook("lease4_select");
        hook_index_lease4_renew_  = HooksManager::registerHook("lease4_renew");
        hook_index_lease6_select_ = HooksManager::registerHook("lease6_select");
    }
};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
AllocEngineHooks Hooks;

}; // anonymous namespace

namespace isc {
namespace dhcp {

AllocEngine::IterativeAllocator::IterativeAllocator(Lease::Type lease_type)
    :Allocator(lease_type) {
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
AllocEngine::IterativeAllocator::increasePrefix(const isc::asiolink::IOAddress& prefix,
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

    // Brief explanation what happens here:
    // http://www.youtube.com/watch?v=NFQCYpIHLNQ

    uint8_t n_bytes = (prefix_len - 1)/8;
    uint8_t n_bits = 8 - (prefix_len - n_bytes*8);
    uint8_t mask = 1 << n_bits;

    // Longer explanation: n_bytes specifies number of full bytes that are
    // in-prefix. They can also be used as an offset for the first byte that
    // is not in prefix. n_bits specifies number of bits on the last byte that
    // is (often partially) in prefix. For example for a /125 prefix, the values
    // are 15 and 3, respectively. Mask is a bitmask that has the least
    // significant bit from the prefix set.

    uint8_t packed[V6ADDRESS_LEN];

    // Copy the address. It must be V6, but we already checked that.
    std::memcpy(packed, &vec[0], V6ADDRESS_LEN);

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


isc::asiolink::IOAddress
AllocEngine::IterativeAllocator::pickAddress(const SubnetPtr& subnet,
                                             const DuidPtr&,
                                             const IOAddress&) {

    // Is this prefix allocation?
    bool prefix = pool_type_ == Lease::TYPE_PD;

    // Let's get the last allocated address. It is usually set correctly,
    // but there are times when it won't be (like after removing a pool or
    // perhaps restarting the server).
    IOAddress last = subnet->getLastAllocated(pool_type_);

    const PoolCollection& pools = subnet->getPools(pool_type_);

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
        subnet->setLastAllocated(pool_type_, next);
        return (next);
    }

    // Ok, we have a pool that the last address belonged to, let's use it.

    IOAddress next("::");
    if (!prefix) {
        next = increaseAddress(last); // basically addr++
    } else {
        Pool6Ptr pool6 = boost::dynamic_pointer_cast<Pool6>(*it);
        if (!pool6) {
            // Something is gravely wrong here
            isc_throw(Unexpected, "Wrong type of pool: " << (*it)->toText()
                      << " is not Pool6");
        }
        // Get the next prefix
        next = increasePrefix(last, pool6->getLength());
    }
    if ((*it)->inRange(next)) {
        // the next one is in the pool as well, so we haven't hit pool boundary yet
        subnet->setLastAllocated(pool_type_, next);
        return (next);
    }

    // We hit pool boundary, let's try to jump to the next pool and try again
    ++it;
    if (it == pools.end()) {
        // Really out of luck today. That was the last pool. Let's rewind
        // to the beginning.
        next = pools[0]->getFirstAddress();
        subnet->setLastAllocated(pool_type_, next);
        return (next);
    }

    // there is a next pool, let's try first address from it
    next = (*it)->getFirstAddress();
    subnet->setLastAllocated(pool_type_, next);
    return (next);
}

AllocEngine::HashedAllocator::HashedAllocator(Lease::Type lease_type)
    :Allocator(lease_type) {
    isc_throw(NotImplemented, "Hashed allocator is not implemented");
}


isc::asiolink::IOAddress
AllocEngine::HashedAllocator::pickAddress(const SubnetPtr&,
                                          const DuidPtr&,
                                          const IOAddress&) {
    isc_throw(NotImplemented, "Hashed allocator is not implemented");
}

AllocEngine::RandomAllocator::RandomAllocator(Lease::Type lease_type)
    :Allocator(lease_type) {
    isc_throw(NotImplemented, "Random allocator is not implemented");
}


isc::asiolink::IOAddress
AllocEngine::RandomAllocator::pickAddress(const SubnetPtr&,
                                          const DuidPtr&,
                                          const IOAddress&) {
    isc_throw(NotImplemented, "Random allocator is not implemented");
}


AllocEngine::AllocEngine(AllocType engine_type, unsigned int attempts,
                         bool ipv6)
    :attempts_(attempts) {

    // Choose the basic (normal address) lease type
    Lease::Type basic_type = ipv6 ? Lease::TYPE_NA : Lease::TYPE_V4;

    // Initalize normal address allocators
    switch (engine_type) {
    case ALLOC_ITERATIVE:
        allocators_[basic_type] = AllocatorPtr(new IterativeAllocator(basic_type));
        break;
    case ALLOC_HASHED:
        allocators_[basic_type] = AllocatorPtr(new HashedAllocator(basic_type));
        break;
    case ALLOC_RANDOM:
        allocators_[basic_type] = AllocatorPtr(new RandomAllocator(basic_type));
        break;
    default:
        isc_throw(BadValue, "Invalid/unsupported allocation algorithm");
    }

    // If this is IPv6 allocation engine, initalize also temporary addrs
    // and prefixes
    if (ipv6) {
        switch (engine_type) {
        case ALLOC_ITERATIVE:
            allocators_[Lease::TYPE_TA] = AllocatorPtr(new IterativeAllocator(Lease::TYPE_TA));
            allocators_[Lease::TYPE_PD] = AllocatorPtr(new IterativeAllocator(Lease::TYPE_PD));
            break;
        case ALLOC_HASHED:
            allocators_[Lease::TYPE_TA] = AllocatorPtr(new HashedAllocator(Lease::TYPE_TA));
            allocators_[Lease::TYPE_PD] = AllocatorPtr(new HashedAllocator(Lease::TYPE_PD));
            break;
        case ALLOC_RANDOM:
            allocators_[Lease::TYPE_TA] = AllocatorPtr(new RandomAllocator(Lease::TYPE_TA));
            allocators_[Lease::TYPE_PD] = AllocatorPtr(new RandomAllocator(Lease::TYPE_PD));
            break;
        default:
            isc_throw(BadValue, "Invalid/unsupported allocation algorithm");
        }
    }

    // Register hook points
    hook_index_lease4_select_ = Hooks.hook_index_lease4_select_;
    hook_index_lease6_select_ = Hooks.hook_index_lease6_select_;
}

Lease6Collection
AllocEngine::allocateLeases6(ClientContext6& ctx) {

    try {
        if (!ctx.subnet_) {
            isc_throw(InvalidOperation, "Subnet is required for allocation");
        }

        if (!ctx.duid_) {
            isc_throw(InvalidOperation, "DUID is mandatory for allocation");
        }

        // Check which host reservation mode is supported in this subnet.
        Subnet::HRMode hr_mode = ctx.subnet_->getHostReservationMode();

        // Check if there's a host reservation for this client. Attempt to get
        // host info only if reservations are not disabled.
        if (hr_mode != Subnet::HR_DISABLED) {

            ctx.host_ = HostMgr::instance().get6(ctx.subnet_->getID(), ctx.duid_,
                                                 ctx.hwaddr_);
        }

        // Check if there are existing leases for that subnet/duid/iaid
        // combination.
        Lease6Collection leases =
            LeaseMgrFactory::instance().getLeases6(ctx.type_, *ctx.duid_, ctx.iaid_,
                                                   ctx.subnet_->getID());

        // Now do the checks:
        // Case 1. if there are no leases, and there are reservations...
        //   1.1. are the reserved addresses are used by someone else?
        //       yes: we have a problem
        //       no: assign them => done
        // Case 2. if there are leases and there are no reservations...
        //   2.1 are the leases reserved for someone else?
        //       yes: release them, assign something else
        //       no: renew them => done
        // Case 3. if there are leases and there are reservations...
        //   3.1 are the leases matching reservations?
        //       yes: renew them => done
        //       no: release existing leases, assign new ones based on reservations
        // Case 4. if there are no leases and no reservations...
        //       assign new leases
        //
        // We could implement those checks as nested ifs, but the performance
        // gain would be minimal and the code readibility loss would be substantial.
        // Hence independent checks.

        // Case 1: There are no leases and there's a reservation for this host.
        if ((hr_mode != Subnet::HR_DISABLED) && leases.empty() && ctx.host_) {

            // Try to allocate leases that match reservations. Typically this will
            // succeed, except cases where the reserved addresses are used by
            // someone else.
            allocateReservedLeases6(ctx, leases);

            // If we got at least one lease, we're good to go.
            if (!leases.empty()) {
                return (leases);
            }

            // If not, we'll need to continue and will eventually fall into case 4:
            // getting a regular lease. That could happen when we're processing
            // request from client X, there's a reserved address A for X, but
            // A is currently used by client Y. We can't immediately reassign A
            // from X to Y, because Y keeps using it, so X would send Decline right
            // away. Need to wait till Y renews, then we can release A, so it
            // will become available for X.
        }

        // Case 2: There are existing leases and there are no reservations.
        //
        // There is at least one lease for this client and there are no reservations.
        // We will return these leases for the client, but we may need to update
        // FQDN information.
        if (!leases.empty() && !ctx.host_) {

            // Check if the existing leases are reserved for someone else.
            // If they're not, we're ok to keep using them.
            removeNonmatchingReservedLeases6(ctx, leases);

            if (!leases.empty()) {
            // Return old leases so the server can see what has changed.
                return (updateFqdnData(leases, ctx.fwd_dns_update_,
                                       ctx.rev_dns_update_,
                                       ctx.hostname_, ctx.fake_allocation_));
            }

            // If leases is empty at this stage, it means that we used to have
            // leases for this client, but we checked and those leases are reserved
            // for someone else, so we lost them. We will need to continue and
            // will finally end up in case 4 (no leases, no reservations), so we'll
            // assign something new.
        }

        // Case 3: There are leases and there are reservations.
        if (!leases.empty() && ctx.host_) {

            // First, check if have leases matching reservations, and add new
            // leases if we don't have them.
            allocateReservedLeases6(ctx, leases);

            // leases now contain both existing and new leases that were created
            // from reservations.

            // Second, let's remove leases that are reserved for someone else.
            // This applies to any existing leases.
            removeNonmatchingReservedLeases6(ctx, leases);

            // leases now contain existing and new leases, but we removed those
            // leases that are reserved for someone else (non-matching reserved).

            // There's one more check to do. Let's remove leases that are not
            // matching reservations, i.e. if client X has address A, but there's
            // a reservation for address B, we should release A and reassign B.
            // Caveat: do this only if we have at least one reserved address.
            removeNonreservedLeases6(ctx, leases);

            // All checks are done. Let's hope we do have any leases left.

            // If we have any leases left, let's return them and we're done.
            if (!leases.empty()) {
                return (leases);
            }

            // If we don't have any leases at this stage, it means that we hit
            // one of the following cases:
            // - we have a reservation, but it's not for this IAID/ia-type and
            //   we had to return the address we were using
            // - we have a reservation for this iaid/ia-type, but the reserved
            //   address is currently used by someone else. We can't assign it
            //   yet.
            // - we had an address, but we just discovered that it's reserved for
            //   someone else, so we released it.
        }

        // Case 4: One of the following is true:
        // - we don't have leases and there are no reservations
        // - we used to have leases, but we lost them, because they are now
        //   reserved for someone else
        // - we have a reservation, but it is not usable yet, because the address
        //   is still used by someone else
        //
        // In any case, we need to go through normal lease assignment process
        // for now.

        leases = allocateUnreservedLeases6(ctx);

        return (leases);

        // Unable to allocate an address, return an empty lease.
        LOG_WARN(dhcpsrv_logger, DHCPSRV_ADDRESS6_ALLOC_FAIL).arg(attempts_);

    } catch (const isc::Exception& e) {

        // Some other error, return an empty lease.
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_ADDRESS6_ALLOC_ERROR).arg(e.what());
    }

    return (Lease6Collection());
}

Lease6Collection
AllocEngine::allocateUnreservedLeases6(ClientContext6& ctx) {

    AllocatorPtr allocator = getAllocator(ctx.type_);

    if (!allocator) {
        isc_throw(InvalidOperation, "No allocator specified for "
                  << Lease6::typeToText(ctx.type_));
    }


    // Check which host reservation mode is supported in this subnet.
    Subnet::HRMode hr_mode = ctx.subnet_->getHostReservationMode();

    Lease6Collection leases;

    IOAddress hint("::");
    if (!ctx.hints_.empty()) {
        /// @todo: We support only one hint for now
        hint = ctx.hints_[0];
    }

    // check if the hint is in pool and is available
    // This is equivalent of subnet->inPool(hint), but returns the pool
    Pool6Ptr pool = boost::dynamic_pointer_cast<
        Pool6>(ctx.subnet_->getPool(ctx.type_, hint, false));

    if (pool) {
        /// @todo: We support only one hint for now
        Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(ctx.type_, hint);
        if (!lease) {

            // In-pool reservations: Check if this address is reserved for someone
            // else. There is no need to check for whom it is reserved, because if
            // it has been reserved for us we would have already allocated a lease.

            ConstHostPtr host;
            if (hr_mode != Subnet::HR_DISABLED) {
                host = HostMgr::instance().get6(ctx.subnet_->getID(), hint);
            }

            if (!host) {
                // If the in-pool reservations are disabled, or there is no
                // reservation for a given hint, we're good to go.

                // The hint is valid and not currently used, let's create a
                // lease for it
                lease = createLease6(ctx, hint, pool->getLength());

                // It can happen that the lease allocation failed (we could
                // have lost the race condition. That means that the hint is
                // lo longer usable and we need to continue the regular
                // allocation path.
                if (lease) {

                    /// @todo: We support only one lease per ia for now
                    Lease6Collection collection;
                    collection.push_back(lease);
                    return (collection);
                }
            }
        } else {

            // If the lease is expired, we may likely reuse it, but...
            if (lease->expired()) {

                ConstHostPtr host;
                if (hr_mode != Subnet::HR_DISABLED) {
                    host = HostMgr::instance().get6(ctx.subnet_->getID(), hint);
                }

                // Let's check if there is a reservation for this address.
                if (!host) {

                    // Copy an existing, expired lease so as it can be returned
                    // to the caller.
                    Lease6Ptr old_lease(new Lease6(*lease));
                    ctx.old_leases_.push_back(old_lease);

                    /// We found a lease and it is expired, so we can reuse it
                    lease = reuseExpiredLease(lease, ctx, pool->getLength());

                    /// @todo: We support only one lease per ia for now
                    leases.push_back(lease);
                    return (leases);
                }
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
        IOAddress candidate = allocator->pickAddress(ctx.subnet_, ctx.duid_, hint);

        /// In-pool reservations: Check if this address is reserved for someone
        /// else. There is no need to check for whom it is reserved, because if
        /// it has been reserved for us we would have already allocated a lease.
        if (hr_mode == Subnet::HR_IN_POOL &&
            HostMgr::instance().get6(ctx.subnet_->getID(), candidate)) {

            // Don't allocate.
            continue;
        }

        // The first step is to find out prefix length. It is 128 for
        // non-PD leases.
        uint8_t prefix_len = 128;
        if (ctx.type_ == Lease::TYPE_PD) {
            Pool6Ptr pool = boost::dynamic_pointer_cast<Pool6>(
                ctx.subnet_->getPool(ctx.type_, candidate, false));
            prefix_len = pool->getLength();
        }

        Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(ctx.type_,
                                                                   candidate);
        if (!existing) {

            // there's no existing lease for selected candidate, so it is
            // free. Let's allocate it.

            Lease6Ptr lease = createLease6(ctx, candidate, prefix_len);
            if (lease) {
                // We are allocating a new lease (not renewing). So, the
                // old lease should be NULL.
                ctx.old_leases_.clear();

                Lease6Collection collection;
                collection.push_back(lease);
                return (collection);
            }

            // Although the address was free just microseconds ago, it may have
            // been taken just now. If the lease insertion fails, we continue
            // allocation attempts.
        } else {
            if (existing->expired()) {
                // Copy an existing, expired lease so as it can be returned
                // to the caller.
                Lease6Ptr old_lease(new Lease6(*existing));
                ctx.old_leases_.push_back(old_lease);

                existing = reuseExpiredLease(existing,
                                             ctx,
                                             prefix_len);
                Lease6Collection collection;
                collection.push_back(existing);
                return (collection);
            }
        }

        // Continue trying allocation until we run out of attempts
        // (or attempts are set to 0, which means infinite)
        --i;
    } while ((i > 0) || !attempts_);

    // We failed to allocate anything. Let's return empty collection.
    return (Lease6Collection());
}

void
AllocEngine::allocateReservedLeases6(ClientContext6& ctx, Lease6Collection& existing_leases) {

    // If there are no reservations or the reservation is v4, there's nothing to do.
    if (!ctx.host_ || !ctx.host_->hasIPv6Reservation()) {
        return;
    }

    // Let's convert this from Lease::Type to IPv6Reserv::Type
    IPv6Resrv::Type type = ctx.type_ == Lease::TYPE_NA ? IPv6Resrv::TYPE_NA : IPv6Resrv::TYPE_PD;

    // Get the IPv6 reservations of specified type.
    const IPv6ResrvRange& reservs = ctx.host_->getIPv6Reservations(type);

    if (std::distance(reservs.first, reservs.second) == 0) {
        // No reservations? We're done here.
        return;
    }

    for (IPv6ResrvIterator resv = reservs.first; resv != reservs.second; ++resv) {
        // We do have a reservation for addr.
        IOAddress addr = resv->second.getPrefix();
        uint8_t prefix_len = resv->second.getPrefixLen();

        // If there's a lease for this address, let's not create it.
        // It doesn't matter whether it is for this client or for someone else.
        if (LeaseMgrFactory::instance().getLease6(ctx.type_, addr)) {
            continue;
        }

        // Ok, let's create a new lease...
        Lease6Ptr lease = createLease6(ctx, addr, prefix_len);

        // ... and add it to the existing leases list.
        existing_leases.push_back(lease);
    }
}

void
AllocEngine::removeNonmatchingReservedLeases6(ClientContext6& ctx,
                                              Lease6Collection& existing_leases) {
    // If there are no leases (so nothing to remove) or
    // host reservation is disabled (so there are no reserved leases),
    // just return.
    if (existing_leases.empty() || !ctx.subnet_ ||
        (ctx.subnet_->getHostReservationMode() == Subnet::HR_DISABLED) ) {
        return;
    }

    // We need a copy, so we won't be iterating over a container and
    // removing from it at the same time. It's only a copy of pointers,
    // so the operation shouldn't be that expensive.
    Lease6Collection copy = existing_leases;

    for (Lease6Collection::const_iterator candidate = copy.begin();
         candidate != copy.end(); ++candidate) {

        ConstHostPtr host = HostMgr::instance().get6(ctx.subnet_->getID(),
                                                     (*candidate)->addr_);

        if (!host || (host == ctx.host_)) {
            // Not reserved or reserved for us. That's ok, let's check
            // the next lease.
            continue;
        }

        // Ok, we have a problem. This host has a lease that is reserved
        // for someone else. We need to recover from this.

        // Remove this lease from LeaseMgr
        LeaseMgrFactory::instance().deleteLease((*candidate)->addr_);

        /// @todo: Probably trigger a hook here

        // Add this to the list of removed leases.
        ctx.old_leases_.push_back(*candidate);

        // Let's remove this candidate from existing leases
        removeLeases(existing_leases, (*candidate)->addr_);
    }
}

bool
AllocEngine::removeLeases(Lease6Collection& container, const asiolink::IOAddress& addr) {

    for (Lease6Collection::iterator lease = container.begin();
         lease != container.end(); ++lease) {
        if ((*lease)->addr_ == addr) {
            container.erase(lease);
            return (true);
        }
    }

    return (false);
}

void
AllocEngine::removeNonreservedLeases6(ClientContext6& ctx,
                                      Lease6Collection& existing_leases) {
    // This method removes leases that are not reserved for this host.
    // It will keep at least one lease, though.
    if (existing_leases.empty() || !ctx.host_ || !ctx.host_->hasIPv6Reservation()) {
        return;
    }

    // This is the total number of leases. We should not remove the last one.
    int total = existing_leases.size();

    // This is tricky/scary code. It iterates and possibly deletes at the same time.
    for (Lease6Collection::iterator lease = existing_leases.begin();
         lease != existing_leases.end();) {
        IPv6Resrv resv(ctx.type_ == Lease::TYPE_NA ? IPv6Resrv::TYPE_NA : IPv6Resrv::TYPE_PD,
                       (*lease)->addr_, (*lease)->prefixlen_);
        if (ctx.host_->hasReservation(resv)) {
            // This is a lease for reserved address. Let's keep it.
            ++lease;
        } else {
            // We have reservations, but not for this lease. Release it.

            // Remove this lease from LeaseMgr
            LeaseMgrFactory::instance().deleteLease((*lease)->addr_);

            /// @todo: Probably trigger a hook here

            // Add this to the list of removed leases.
            ctx.old_leases_.push_back(*lease);

            // This is tricky part. We move lease to the next element and
            // then pass the old value to erase.
            existing_leases.erase(lease++);

            if (--total == 1) {
                // If there's only one lease left, return.
                return;
            }
        }

    }
}

Lease4Ptr
AllocEngine::allocateLease4(const SubnetPtr& subnet, const ClientIdPtr& clientid,
                            const HWAddrPtr& hwaddr, const IOAddress& hint,
                            const bool fwd_dns_update, const bool rev_dns_update,
                            const std::string& hostname, bool fake_allocation,
                            const isc::hooks::CalloutHandlePtr& callout_handle,
                            Lease4Ptr& old_lease) {

    // The NULL pointer indicates that the old lease didn't exist. It may
    // be later set to non NULL value if existing lease is found in the
    // database.
    old_lease.reset();

    try {

        // Set allocator.
        AllocatorPtr allocator = getAllocator(Lease::TYPE_V4);

        if (!subnet) {
            isc_throw(BadValue, "Can't allocate IPv4 address without subnet");
        }

        if (!hwaddr) {
            isc_throw(BadValue, "HWAddr must be defined");
        }

        /// @todo The context for lease allocation should really be created
        /// by the DHCPv4 server and passed to this function. The reason for
        /// this is that the server should retrieve the Host object for the
        /// client because the Host object contains the data not only useful
        /// for the address allocation but also hostname and DHCP options
        /// for the client. The Host object should be passed in the context.
        /// Making this change would require a change to the allocateLease4
        /// API which would in turn require lots of changes in unit tests.
        /// The ticket introducing a context and host reservation in the
        /// allocation engine is complex enough by itself to warrant that
        /// the API change is done with a separate ticket.
        ClientContext4 ctx;
        ctx.subnet_ = subnet;
        ctx.clientid_ = clientid;
        ctx.hwaddr_ = hwaddr;
        ctx.requested_address_ = hint;
        ctx.fwd_dns_update_ = fwd_dns_update;
        ctx.rev_dns_update_ = rev_dns_update;
        ctx.hostname_ = hostname;
        ctx.fake_allocation_ = fake_allocation;
        ctx.callout_handle_ = callout_handle;
        ctx.old_lease_ = old_lease;
        ctx.host_ = HostMgr::instance().get4(subnet->getID(), hwaddr);

        // If there is a reservation for this client we want to allocate the
        // reserved address to the client, rather than any other address.
        if (ctx.host_) {
            // In some cases the client doesn't supply any address, e.g. when
            // it sends a DHCPDISCOVER. In such cases, we use the reserved
            // address as a hint.
            if (ctx.requested_address_ == IOAddress("0.0.0.0")) {
                ctx.requested_address_ = ctx.host_->getIPv4Reservation();

            // If the client supplied an address we have to check if this
            // address is reserved for this client. If not, we will send
            // DHCPNAK to inform the client that we were not able to
            // assign a requested address. The fake allocation (DHCPDISCOVER
            // case) is an exception. In such case we treat the address
            // supplied by the client as a hint, but we may offer address
            // other than desired by the client. So, we don't return an
            // empty lease.
            } else if (!ctx.fake_allocation_ &&
                       (ctx.requested_address_ != ctx.host_->getIPv4Reservation())) {
                return (Lease4Ptr());
            }
        }

        // Check if the client has any leases in the lease database, using HW
        // address or client identifier.
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        Lease4Ptr existing = lease_mgr.getLease4(*hwaddr, ctx.subnet_->getID());
        if (!existing && clientid) {
            existing = lease_mgr.getLease4(*clientid, ctx.subnet_->getID());
        }

        // If client has a lease there are two choices. The server may need
        // to renew (no address change) the lease. Or, the server may need
        // to replace the lease with a different one. This is the case when
        // the server has a dynamically assigned lease but an administrator
        // has made a new reservation for the client for a different address.
        if (existing) {
            existing = reallocateClientLease(existing, ctx);
            // The interrupt_processing_ flag indicates that the lease
            // reallocation was not successful and that the allocation
            // engine should cease allocation process for this client.
            // This may occur when the client is trying to renew the
            // lease which is reserved for someone else. The server should
            // send DHCPNAK to indicate that the client should try to
            // start over the allocation process.
            if (ctx.interrupt_processing_) {
                old_lease = ctx.old_lease_;
                return (Lease4Ptr());

            // If we tried to reallocate the reserved lease we return
            // at this point regardless if reallocation failed or passed.
            // We also return when allocation passed, no matter if this
            // was a reserved address or not.
            } else  if (ctx.host_ || existing) {
                old_lease = ctx.old_lease_;
                return (existing);
            }
        }

        // There is no lease in the database for this client, so we will
        // proceed with a new allocation. We will try to allocate a
        // reserved address or an address from a dynamic pool if there is
        // no reservation.
        if (ctx.host_ || subnet->inPool(Lease::TYPE_V4, ctx.requested_address_)) {
            // If a client is requesting specific IP address, but the
            // reservation was made for a different address the server returns
            // NAK to the client. By returning NULL lease here we indicate to
            // the server that we're not able to fulfil client's request for the
            // particular IP address. We don't return NULL lease in case of the
            // fake allocation (DHCPDISCOVER) because in this case the address
            // supplied by the client is only a hint.
            if (!ctx.fake_allocation_ && ctx.host_ &&
                (ctx.requested_address_ != IOAddress("0.0.0.0")) &&
                (ctx.host_->getIPv4Reservation() != ctx.requested_address_)) {
                return (Lease4Ptr());
            }

            // The reserved address always takes precedence over an address
            // supplied by the client (renewed address or requested).
            const IOAddress& candidate = ctx.host_ ?
                ctx.host_->getIPv4Reservation() : ctx.requested_address_;

            // Once we picked an address we want to allocate, we have to check
            // if this address is available.
            existing = LeaseMgrFactory::instance().getLease4(candidate);
            if (!existing) {
                // The candidate address is currently unused. Let's create a
                // lease for it.
                Lease4Ptr lease = createLease4(subnet, clientid, hwaddr,
                                               candidate, fwd_dns_update,
                                               rev_dns_update,
                                               hostname, callout_handle,
                                               fake_allocation);

                // If we have allocated the lease let's return it. Also,
                // always return when tried to allocate reserved address,
                // regardless if allocation was successful or not. If it
                // was not successful, we will return a NULL pointer which
                // indicates to the server that it should send NAK to the
                // client.
                if (lease || ctx.host_) {
                    return (lease);
                }

            // There is a lease for this address in the lease database but
            // it is possible that the lease has expired, in which case
            // we will be able to reuse it.
            } else {
                if (existing->expired()) {
                    // Save the old lease, before reusing it.
                    old_lease.reset(new Lease4(*existing));
                    return (reuseExpiredLease(existing, ctx));

                // The existing lease is not expired (is in use by some
                // other client). If we are trying to get this lease because
                // the address has been reserved for the client we have no
                // choice but to return a NULL lease to indicate that the
                // allocation has failed.
                } else if (ctx.host_) {
                    return (Lease4Ptr());

                }

            }
        }

        // No address was requested, requested address was not in pool or the
        // allocation was not successful so far. Let's try to find a different
        // address for the client.  Search the pool until first of the following
        // occurs:
        // - we find a free address
        // - we find an address for which the lease has expired
        // - we exhaust the number of tries
        //
        /// @todo: Current code does not handle pool exhaustion well. It will be
        /// improved. Current problems:
        /// 1. with attempts set to too large value (e.g. 1000) and a small pool (e.g.
        /// 10 addresses), we will iterate over it 100 times before giving up
        /// 2. attempts 0 mean unlimited (this is really UINT_MAX, not infinite)
        /// 3. the whole concept of infinite attempts is just asking for infinite loop
        /// We may consider some form or reference counting (this pool has X addresses
        /// left), but this has one major problem. We exactly control allocation
        /// moment, but we currently do not control expiration time at all
        unsigned int i = attempts_;
        do {
            IOAddress candidate = allocator->pickAddress(subnet, clientid,
                                                         ctx.requested_address_);

            // Check if this address is reserved. There is no need to check for
            // whom it is reserved, because if it has been reserved for us we would
            // have already allocated a lease.
            if (HostMgr::instance().get4(subnet->getID(), candidate)) {
                // Don't allocate a reserved address.
                continue;
            }

            Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(candidate);
            if (!existing) {
                // there's no existing lease for selected candidate, so it is
                // free. Let's allocate it.
                Lease4Ptr lease = createLease4(subnet, clientid, hwaddr,
                                               candidate, fwd_dns_update,
                                               rev_dns_update, hostname,
                                               callout_handle, fake_allocation);
                if (lease) {
                    return (lease);
                }

                // Although the address was free just microseconds ago, it may have
                // been taken just now. If the lease insertion fails, we continue
                // allocation attempts.
            } else {
                if (existing->expired()) {
                    // Save old lease before reusing it.
                    old_lease.reset(new Lease4(*existing));
                    return (reuseExpiredLease(existing, ctx));
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

Lease4Ptr
AllocEngine::renewLease4(const Lease4Ptr& lease,
                         AllocEngine::ClientContext4& ctx) {
    if (!lease) {
        isc_throw(BadValue, "null lease specified for renewLease4");
    }

    // The ctx.host_ possibly contains a reservation for the client for which
    // we are renewing a lease. If this reservation exists, we assume that
    // there is no conflict in assigning the address to this client. Note
    // that the reallocateClientLease checks if the address reserved for
    // the client matches the address in the lease we're renewing here.
    if (!ctx.host_) {
        ConstHostPtr host = HostMgr::instance().get4(ctx.subnet_->getID(),
                                                     lease->addr_);
        // Do not renew the lease if:
        // - If address is reserved for someone else or ...
        // - renewed address doesn't belong to a pool.
        if ((host && ctx.hwaddr_ && (*host->getHWAddress() != *ctx.hwaddr_)) ||
            (!ctx.subnet_->inPool(Lease::TYPE_V4, lease->addr_))) {
            ctx.interrupt_processing_ = !ctx.fake_allocation_;
            return (Lease4Ptr());
        }

    }

    // Let's keep the old data. This is essential if we are using memfile
    // (the lease returned points directly to the lease4 object in the database)
    // We'll need it if we want to skip update (i.e. roll back renewal)
    /// @todo: remove this once #3083 is implemented
    Lease4 old_values = *lease;

    // Update the lease with the information from the context.
    updateLease4Information(lease, ctx);

    bool skip = false;
    // Execute all callouts registered for lease4_renew.
    if (HooksManager::getHooksManager().
        calloutsPresent(Hooks.hook_index_lease4_renew_)) {

        // Delete all previous arguments
        ctx.callout_handle_->deleteAllArguments();

        // Subnet from which we do the allocation. Convert the general subnet
        // pointer to a pointer to a Subnet4.  Note that because we are using
        // boost smart pointers here, we need to do the cast using the boost
        // version of dynamic_pointer_cast.
        Subnet4Ptr subnet4 = boost::dynamic_pointer_cast<Subnet4>(ctx.subnet_);

        // Pass the parameters
        ctx.callout_handle_->setArgument("subnet4", subnet4);
        ctx.callout_handle_->setArgument("clientid", ctx.clientid_);
        ctx.callout_handle_->setArgument("hwaddr", ctx.hwaddr_);

        // Pass the lease to be updated
        ctx.callout_handle_->setArgument("lease4", lease);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease4_renew_,
                                   *ctx.callout_handle_);

        // Callouts decided to skip the next processing step. The next
        // processing step would to actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        if (ctx.callout_handle_->getSkip()) {
            skip = true;
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE4_RENEW_SKIP);
        }
    }

    if (!ctx.fake_allocation_ && !skip) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease4(lease);
    }
    if (skip) {
        // Rollback changes (really useful only for memfile)
        /// @todo: remove this once #3083 is implemented
        *lease = old_values;
    }

    return (lease);
}

Lease6Ptr AllocEngine::reuseExpiredLease(Lease6Ptr& expired,
                                         ClientContext6& ctx,
                                         uint8_t prefix_len) {

    if (!expired->expired()) {
        isc_throw(BadValue, "Attempt to recycle lease that is still valid");
    }

    if (expired->type_ != Lease::TYPE_PD) {
        prefix_len = 128; // non-PD lease types must be always /128
    }

    // address, lease type and prefixlen (0) stay the same
    expired->iaid_ = ctx.iaid_;
    expired->duid_ = ctx.duid_;
    expired->preferred_lft_ = ctx.subnet_->getPreferred();
    expired->valid_lft_ = ctx.subnet_->getValid();
    expired->t1_ = ctx.subnet_->getT1();
    expired->t2_ = ctx.subnet_->getT2();
    expired->cltt_ = time(NULL);
    expired->subnet_id_ = ctx.subnet_->getID();
    expired->fixed_ = false;
    expired->hostname_ = ctx.hostname_;
    expired->fqdn_fwd_ = ctx.fwd_dns_update_;
    expired->fqdn_rev_ = ctx.rev_dns_update_;
    expired->prefixlen_ = prefix_len;

    /// @todo: log here that the lease was reused (there's ticket #2524 for
    /// logging in libdhcpsrv)

    // Let's execute all callouts registered for lease6_select
    if (ctx.callout_handle_ &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease6_select_)) {

        // Delete all previous arguments
        ctx.callout_handle_->deleteAllArguments();

        // Pass necessary arguments
        // Subnet from which we do the allocation
        ctx.callout_handle_->setArgument("subnet6", ctx.subnet_);

        // Is this solicit (fake = true) or request (fake = false)
        ctx.callout_handle_->setArgument("fake_allocation", ctx.fake_allocation_);

        // The lease that will be assigned to a client
        ctx.callout_handle_->setArgument("lease6", expired);

        // Call the callouts
        HooksManager::callCallouts(hook_index_lease6_select_, *ctx.callout_handle_);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (ctx.callout_handle_->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_SELECT_SKIP);
            return (Lease6Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        ctx.callout_handle_->getArgument("lease6", expired);
    }

    if (!ctx.fake_allocation_) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease6(expired);
    }

    // We do nothing for SOLICIT. We'll just update database when
    // the client gets back to us with REQUEST message.

    // it's not really expired at this stage anymore - let's return it as
    // an updated lease
    return (expired);
}

Lease4Ptr
AllocEngine::reuseExpiredLease(Lease4Ptr& expired,
                               AllocEngine::ClientContext4& ctx) {
    if (!expired) {
        isc_throw(BadValue, "null lease specified for reuseExpiredLease");
    }

    if (!ctx.subnet_) {
        isc_throw(BadValue, "null subnet specified for the reuseExpiredLease");
    }

    updateLease4Information(expired, ctx);
    expired->fixed_ = false;

    /// @todo: log here that the lease was reused (there's ticket #2524 for
    /// logging in libdhcpsrv)

    // Let's execute all callouts registered for lease4_select
    if (ctx.callout_handle_ &&  HooksManager::getHooksManager()
        .calloutsPresent(hook_index_lease4_select_)) {

        // Delete all previous arguments
        ctx.callout_handle_->deleteAllArguments();

        // Pass necessary arguments

        // Subnet from which we do the allocation. Convert the general subnet
        // pointer to a pointer to a Subnet4.  Note that because we are using
        // boost smart pointers here, we need to do the cast using the boost
        // version of dynamic_pointer_cast.
        Subnet4Ptr subnet4 = boost::dynamic_pointer_cast<Subnet4>(ctx.subnet_);
        ctx.callout_handle_->setArgument("subnet4", subnet4);

        // Is this solicit (fake = true) or request (fake = false)
        ctx.callout_handle_->setArgument("fake_allocation",
                                         ctx.fake_allocation_);

        // The lease that will be assigned to a client
        ctx.callout_handle_->setArgument("lease4", expired);

        // Call the callouts
        HooksManager::callCallouts(hook_index_lease4_select_, *ctx.callout_handle_);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (ctx.callout_handle_->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE4_SELECT_SKIP);
            return (Lease4Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        ctx.callout_handle_->getArgument("lease4", expired);
    }

    if (!ctx.fake_allocation_) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease4(expired);
    }

    // We do nothing for SOLICIT. We'll just update database when
    // the client gets back to us with REQUEST message.

    // it's not really expired at this stage anymore - let's return it as
    // an updated lease
    return (expired);
}

Lease4Ptr
AllocEngine::replaceClientLease(Lease4Ptr& lease, ClientContext4& ctx) {

    if (!lease) {
        isc_throw(BadValue, "null lease specified for replaceClientLease");
    }

    if (!ctx.subnet_) {
        isc_throw(BadValue, "null subnet specified for replaceClientLease");
    }

    if (ctx.requested_address_ == IOAddress("0.0.0.0")) {
        isc_throw(BadValue, "zero address specified for the"
                  " replaceClientLease");
    }

    // Remember the previous address for this lease.
    IOAddress prev_address = lease->addr_;

    if (!ctx.host_) {
        ConstHostPtr host = HostMgr::instance().get4(ctx.subnet_->getID(),
                                                     ctx.requested_address_);
        // If there is a reservation for the new address and the reservation
        // is made for another client, do not use this address.
        if (host && ctx.hwaddr_ && (*host->getHWAddress() != *ctx.hwaddr_)) {
            ctx.interrupt_processing_ = true;
            return (Lease4Ptr());
        }
        lease->addr_ = ctx.requested_address_;
    } else {
        lease->addr_ = ctx.host_->getIPv4Reservation();
    }

    updateLease4Information(lease, ctx);

    bool skip = false;
    // Execute callouts registered for lease4_select.
    if (ctx.callout_handle_ && HooksManager::getHooksManager()
        .calloutsPresent(hook_index_lease4_select_)) {

        // Delete all previous arguments.
        ctx.callout_handle_->deleteAllArguments();

        // Pass arguments.
        Subnet4Ptr subnet4 = boost::dynamic_pointer_cast<Subnet4>(ctx.subnet_);
        ctx.callout_handle_->setArgument("subnet4", subnet4);

        ctx.callout_handle_->setArgument("fake_allocation",
                                         ctx.fake_allocation_);

        ctx.callout_handle_->setArgument("lease4", lease);

        HooksManager::callCallouts(hook_index_lease4_select_,
                                   *ctx.callout_handle_);

        if (ctx.callout_handle_->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE4_SELECT_SKIP);
            return (Lease4Ptr());
        }

        // Let's use whatever callout returned.
        ctx.callout_handle_->getArgument("lease4", lease);

        // Callouts decided to skip the next processing step. The next
        // processing step would to actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        if (ctx.callout_handle_->getSkip()) {
            skip = true;
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE4_SELECT_SKIP);
        }
    }

    /// @todo There should be a callout for a deletion of an old lease.
    /// The lease4_release callout is in appropriate, because by definition
    /// it is invoked when DHCPRELEASE packet is received.

    if (!ctx.fake_allocation_ && !skip) {
        // We can't use LeaseMgr::updateLease because it identifies the
        // lease by an IP address. Instead, we have to delete an old
        // lease and add a new one.
        LeaseMgrFactory::instance().deleteLease(prev_address);
        LeaseMgrFactory::instance().addLease(lease);
    }

    return (lease);
}

Lease4Ptr
AllocEngine::reallocateClientLease(Lease4Ptr& lease,
                                   AllocEngine::ClientContext4& ctx) {
    // Save the old lease, before renewal.
    ctx.old_lease_.reset(new Lease4(*lease));

    /// The client's address will need to be modified in case if:
    /// - There is a reservation for the client (likely new one) and
    ///   the currently used address is different.
    /// - Client requested some IP address and the requested address
    ///   is different than the currently used one. Note that if this
    ///   is a DHCPDISCOVER the requested IP address is ignored when
    ///   it doesn't match the one in use.
    if ((ctx.host_ && (ctx.host_->getIPv4Reservation() != lease->addr_)) ||
        (!ctx.fake_allocation_ &&
         (ctx.requested_address_ != IOAddress("0.0.0.0")) &&
         (lease->addr_ != ctx.requested_address_))) {
        lease = replaceClientLease(lease, ctx);
        return (lease);

    } else {
        lease = renewLease4(lease, ctx);
        if (lease) {
            return (lease);
        }
    }

    return (Lease4Ptr());
}


Lease6Ptr AllocEngine::createLease6(ClientContext6& ctx,
                                    const IOAddress& addr,
                                    uint8_t prefix_len) {

    if (ctx.type_ != Lease::TYPE_PD) {
        prefix_len = 128; // non-PD lease types must be always /128
    }

    Lease6Ptr lease(new Lease6(ctx.type_, addr, ctx.duid_, ctx.iaid_,
                               ctx.subnet_->getPreferred(), ctx.subnet_->getValid(),
                               ctx.subnet_->getT1(), ctx.subnet_->getT2(),
                               ctx.subnet_->getID(), ctx.hwaddr_, prefix_len));

    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hostname_ = ctx.hostname_;

    // Let's execute all callouts registered for lease6_select
    if (ctx.callout_handle_ &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease6_select_)) {

        // Delete all previous arguments
        ctx.callout_handle_->deleteAllArguments();

        // Pass necessary arguments

        // Subnet from which we do the allocation
        ctx.callout_handle_->setArgument("subnet6", ctx.subnet_);

        // Is this solicit (fake = true) or request (fake = false)
        ctx.callout_handle_->setArgument("fake_allocation", ctx.fake_allocation_);
        ctx.callout_handle_->setArgument("lease6", lease);

        // This is the first callout, so no need to clear any arguments
        HooksManager::callCallouts(hook_index_lease6_select_, *ctx.callout_handle_);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (ctx.callout_handle_->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_SELECT_SKIP);
            return (Lease6Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        ctx.callout_handle_->getArgument("lease6", lease);
    }

    if (!ctx.fake_allocation_) {
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
        Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(
                             Lease::TYPE_NA, addr);
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
                                    const bool fwd_dns_update,
                                    const bool rev_dns_update,
                                    const std::string& hostname,
                                    const isc::hooks::CalloutHandlePtr& callout_handle,
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

    Lease4Ptr lease(new Lease4(addr, hwaddr, &local_copy[0], local_copy.size(),
                               subnet->getValid(), subnet->getT1(), subnet->getT2(),
                               now, subnet->getID()));

    // Set FQDN specific lease parameters.
    lease->fqdn_fwd_ = fwd_dns_update;
    lease->fqdn_rev_ = rev_dns_update;
    lease->hostname_ = hostname;

    // Let's execute all callouts registered for lease4_select
    if (callout_handle &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease4_select_)) {

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass necessary arguments

        // Subnet from which we do the allocation (That's as far as we can go
        // with using SubnetPtr to point to Subnet4 object. Users should not
        // be confused with dynamic_pointer_casts. They should get a concrete
        // pointer (Subnet4Ptr) pointing to a Subnet4 object.
        Subnet4Ptr subnet4 = boost::dynamic_pointer_cast<Subnet4>(subnet);
        callout_handle->setArgument("subnet4", subnet4);

        // Is this solicit (fake = true) or request (fake = false)
        callout_handle->setArgument("fake_allocation", fake_allocation);

        // Pass the intended lease as well
        callout_handle->setArgument("lease4", lease);

        // This is the first callout, so no need to clear any arguments
        HooksManager::callCallouts(hook_index_lease4_select_, *callout_handle);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_handle->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE4_SELECT_SKIP);
            return (Lease4Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        callout_handle->getArgument("lease4", lease);
    }

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

void
AllocEngine::updateLease4Information(const Lease4Ptr& lease,
                                     AllocEngine::ClientContext4& ctx) const {
    // This should not happen in theory.
    if (!lease) {
        isc_throw(BadValue, "null lease specified for updateLease4Information");
    }

    if (!ctx.subnet_) {
        isc_throw(BadValue, "null subnet specified for"
                  " updateLease4Information");
    }

    lease->subnet_id_ = ctx.subnet_->getID();
    lease->hwaddr_ = ctx.hwaddr_;
    lease->client_id_ = ctx.clientid_;
    lease->cltt_ = time(NULL);
    lease->t1_ = ctx.subnet_->getT1();
    lease->t2_ = ctx.subnet_->getT2();
    lease->valid_lft_ = ctx.subnet_->getValid();
    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hostname_ = ctx.hostname_;
}

Lease6Collection
AllocEngine::updateFqdnData(const Lease6Collection& leases,
                            const bool fwd_dns_update,
                            const bool rev_dns_update,
                            const std::string& hostname,
                            const bool fake_allocation) {
    Lease6Collection updated_leases;
    for (Lease6Collection::const_iterator lease_it = leases.begin();
         lease_it != leases.end(); ++lease_it) {
        Lease6Ptr lease(new Lease6(**lease_it));
        lease->fqdn_fwd_ = fwd_dns_update;
        lease->fqdn_rev_ = rev_dns_update;
        lease->hostname_ = hostname;
        if (!fake_allocation &&
            ((lease->fqdn_fwd_ != (*lease_it)->fqdn_fwd_) ||
             (lease->fqdn_rev_ != (*lease_it)->fqdn_rev_) ||
             (lease->hostname_ != (*lease_it)->hostname_))) {
            LeaseMgrFactory::instance().updateLease6(lease);
        }
        updated_leases.push_back(lease);
    }
    return (updated_leases);
}

AllocEngine::AllocatorPtr AllocEngine::getAllocator(Lease::Type type) {
    std::map<Lease::Type, AllocatorPtr>::const_iterator alloc = allocators_.find(type);

    if (alloc == allocators_.end()) {
        isc_throw(BadValue, "No allocator initialized for pool type "
                  << Lease::typeToText(type));
    }
    return (alloc->second);
}

AllocEngine::~AllocEngine() {
    // no need to delete allocator. smart_ptr will do the trick for us
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
