// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp6.h>

#include <hooks/server_hooks.h>
#include <hooks/hooks_manager.h>

#include <cstring>
#include <limits>
#include <vector>
#include <stdint.h>
#include <string.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::hooks;

namespace {

/// Structure that holds registered hook indexes
struct AllocEngineHooks {
    int hook_index_lease4_select_; ///< index for "lease4_receive" hook point
    int hook_index_lease4_renew_;  ///< index for "lease4_renew" hook point
    int hook_index_lease6_select_; ///< index for "lease6_receive" hook point
    int hook_index_lease6_renew_;  ///< index for "lease6_renew" hook point
    int hook_index_lease6_rebind_; ///< index for "lease6_rebind" hook point

    /// Constructor that registers hook points for AllocationEngine
    AllocEngineHooks() {
        hook_index_lease4_select_ = HooksManager::registerHook("lease4_select");
        hook_index_lease4_renew_  = HooksManager::registerHook("lease4_renew");
        hook_index_lease6_select_ = HooksManager::registerHook("lease6_select");
        hook_index_lease6_renew_   = HooksManager::registerHook("lease6_renew");
        hook_index_lease6_rebind_   = HooksManager::registerHook("lease6_rebind");
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

AllocEngine::ClientContext4::ClientContext4()
    : subnet_(), clientid_(), hwaddr_(),
      requested_address_(IOAddress::IPV4_ZERO_ADDRESS()),
      fwd_dns_update_(false), rev_dns_update_(false),
      hostname_(""), callout_handle_(), fake_allocation_(false),
      old_lease_(), host_(), interrupt_processing_(false) {
}

bool
AllocEngine::ClientContext4::myLease(const Lease4& lease) const {
    if ((!hwaddr_ && lease.hwaddr_) || (hwaddr_ && !lease.hwaddr_)) {
        return (false);
    }

    if ((hwaddr_ && lease.hwaddr_) && (hwaddr_->hwaddr_ != lease.hwaddr_->hwaddr_)) {
        return (false);
    }

    if ((!clientid_ && lease.client_id_) || (clientid_ && !lease.client_id_)) {
        return (false);
    }

    if ((clientid_ && lease.client_id_) && (*clientid_ != *lease.client_id_)) {
        return (false);
    }

    return (true);
}

AllocEngine::IterativeAllocator::IterativeAllocator(Lease::Type lease_type)
    :Allocator(lease_type) {
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
        next = IOAddress::increase(last); // basically addr++
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

AllocEngine::AllocatorPtr AllocEngine::getAllocator(Lease::Type type) {
    std::map<Lease::Type, AllocatorPtr>::const_iterator alloc = allocators_.find(type);

    if (alloc == allocators_.end()) {
        isc_throw(BadValue, "No allocator initialized for pool type "
                  << Lease::typeToText(type));
    }
    return (alloc->second);
}

// ##########################################################################
// #    DHCPv6 lease allocation code starts here.
// ##########################################################################

Lease6Collection
AllocEngine::allocateLeases6(ClientContext6& ctx) {

    try {
        if (!ctx.subnet_) {
            isc_throw(InvalidOperation, "Subnet is required for IPv6 lease allocation");
        } else
        if (!ctx.duid_) {
            isc_throw(InvalidOperation, "DUID is mandatory for IPv6 lease allocation");
        }

        // Check which host reservation mode is supported in this subnet.
        Subnet::HRMode hr_mode = ctx.subnet_->getHostReservationMode();

        // Check if there's a host reservation for this client. Attempt to get
        // host info only if reservations are not disabled.
        if (hr_mode != Subnet::HR_DISABLED) {

            ctx.host_ = HostMgr::instance().get6(ctx.subnet_->getID(), ctx.duid_,
                                                 ctx.hwaddr_);
        } else {
            // Let's explicitly set it to NULL if reservations are disabled.
            ctx.host_.reset();
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
        // Case 4/catch-all. if there are no leases and no reservations...
        //       assign new leases
        //
        // We could implement those checks as nested ifs, but the performance
        // gain would be minimal and the code readibility loss would be substantial.
        // Hence independent checks.

        // Case 1: There are no leases and there's a reservation for this host.
        if (leases.empty() && ctx.host_) {

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

        // Case 2: There are existing leases and there are no reservations.
        //
        // There is at least one lease for this client and there are no reservations.
        // We will return these leases for the client, but we may need to update
        // FQDN information.
        } else if (!leases.empty() && !ctx.host_) {

            // Check if the existing leases are reserved for someone else.
            // If they're not, we're ok to keep using them.
            removeNonmatchingReservedLeases6(ctx, leases);

            if (!leases.empty()) {
                // Return old leases so the server can see what has changed.
                return (updateFqdnData(ctx, leases));
            }

            // If leases are empty at this stage, it means that we used to have
            // leases for this client, but we checked and those leases are reserved
            // for someone else, so we lost them. We will need to continue and
            // will finally end up in case 4 (no leases, no reservations), so we'll
            // assign something new.

        // Case 3: There are leases and there are reservations.
        } else if (!leases.empty() && ctx.host_) {

            // First, check if have leases matching reservations, and add new
            // leases if we don't have them.
            allocateReservedLeases6(ctx, leases);

            // leases now contain both existing and new leases that were created
            // from reservations.

            // Second, let's remove leases that are reserved for someone else.
            // This applies to any existing leases. This will not happen frequently,
            // but it may happen with the following chain of events:
            // 1. client A gets address X;
            // 2. reservation for client B for address X is made by a administrator;
            // 3. client A reboots
            // 4. client A requests the address (X) he got previously
            removeNonmatchingReservedLeases6(ctx, leases);

            // leases now contain existing and new leases, but we removed those
            // leases that are reserved for someone else (non-matching reserved).

            // There's one more check to do. Let's remove leases that are not
            // matching reservations, i.e. if client X has address A, but there's
            // a reservation for address B, we should release A and reassign B.
            // Caveat: do this only if we have at least one reserved address.
            removeNonreservedLeases6(ctx, leases);

            // All checks are done. Let's hope we have some leases left.

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

        // Case 4/catch-all: One of the following is true:
        // - we don't have leases and there are no reservations
        // - we used to have leases, but we lost them, because they are now
        //   reserved for someone else
        // - we have a reservation, but it is not usable yet, because the address
        //   is still used by someone else
        //
        // In any case, we need to go through normal lease assignment process
        // for now. This is also a catch-all or last resort approach, when we
        // couldn't find any reservations (or couldn't use them).

        leases = allocateUnreservedLeases6(ctx);

        if (!leases.empty()) {
            return (leases);
        }

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
        hint = ctx.hints_[0].first;
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
                // no longer usable and we need to continue the regular
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

    // The hint was useless (it was not provided at all, was used by someone else,
    // was out of pool or reserved for someone else). Search the pool until first
    // of the following occurs:
    // - we find a free address
    // - we find an address for which the lease has expired
    // - we exhaust number of tries
    //
    /// @todo: We used to use hardcoded number of attempts (100). Now we dynamically
    /// calculate the number of possible leases in all pools in this subnet and
    /// try that number of times at most. It would be useful to that value if
    /// attempts_, specified by the user could override that value (and keep
    /// dynamic if they're set to 0).
    uint32_t max_attempts = ctx.subnet_->getPoolCapacity(ctx.type_);
    for (uint32_t i = 0; i < max_attempts; ++i)
    {
        IOAddress candidate = allocator->pickAddress(ctx.subnet_, ctx.duid_, hint);

        /// In-pool reservations: Check if this address is reserved for someone
        /// else. There is no need to check for whom it is reserved, because if
        /// it has been reserved for us we would have already allocated a lease.
        if (hr_mode == Subnet::HR_ALL &&
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
            /// @todo: verify that the pool is non-null
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

                leases.push_back(lease);
                return (leases);
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

                leases.push_back(existing);
                return (leases);
            }
        }
    }

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

        // Check if already have this lease on the existing_leases list.
        for (Lease6Collection::const_iterator l = existing_leases.begin();
             l != existing_leases.end(); ++l) {

            // Ok, we already have a lease for this reservation and it's usable
            if (((*l)->addr_ == addr) && (*l)->valid_lft_ != 0) {
                return;
            }
        }

        // If there's a lease for this address, let's not create it.
        // It doesn't matter whether it is for this client or for someone else.
        if (!LeaseMgrFactory::instance().getLease6(ctx.type_, addr)) {
            // Ok, let's create a new lease...
            Lease6Ptr lease = createLease6(ctx, addr, prefix_len);

            // ... and add it to the existing leases list.
            existing_leases.push_back(lease);

            if (ctx.type_ == Lease::TYPE_NA) {
                LOG_INFO(dhcpsrv_logger, DHCPSRV_HR_RESERVED_ADDR_GRANTED)
                    .arg(addr.toText()).arg(ctx.duid_->toText());
            } else {
                LOG_INFO(dhcpsrv_logger, DHCPSRV_HR_RESERVED_PREFIX_GRANTED)
                    .arg(addr.toText()).arg(static_cast<int>(prefix_len))
                    .arg(ctx.duid_->toText());
            }

            // We found a lease for this client and this IA. Let's return.
            // Returning after the first lease was assigned is useful if we
            // have multiple reservations for the same client. If the client
            // sends 2 IAs, the first time we call allocateReservedLeases6 will
            // use the first reservation and return. The second time, we'll
            // go over the first reservation, but will discover that there's
            // a lease corresponding to it and will skip it and then pick
            // the second reservation and turn it into the lease. This approach
            // would work for any number of reservations.
            return;
        }
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
        if (ctx.type_ == Lease::TYPE_NA) {
            LOG_INFO(dhcpsrv_logger, DHCPSRV_HR_REVOKED_ADDR6_LEASE)
                .arg((*candidate)->addr_.toText()).arg(ctx.duid_->toText())
                .arg(host->getIdentifierAsText());
        } else {
            LOG_INFO(dhcpsrv_logger, DHCPSRV_HR_REVOKED_PREFIX6_LEASE)
                .arg((*candidate)->addr_.toText())
                .arg(static_cast<int>((*candidate)->prefixlen_))
                .arg(ctx.duid_->toText())
                .arg(host->getIdentifierAsText());
        }

        // Remove this lease from LeaseMgr
        LeaseMgrFactory::instance().deleteLease((*candidate)->addr_);

        // In principle, we could trigger a hook here, but we will do this
        // only if we get serious complaints from actual users. We want the
        // conflict resolution procedure to really work and user libraries
        // should not interfere with it.

        // Add this to the list of removed leases.
        ctx.old_leases_.push_back(*candidate);

        // Let's remove this candidate from existing leases
        removeLeases(existing_leases, (*candidate)->addr_);
    }
}

bool
AllocEngine::removeLeases(Lease6Collection& container, const asiolink::IOAddress& addr) {

    bool removed = false;
    for (Lease6Collection::iterator lease = container.begin();
         lease != container.end(); ++lease) {
        if ((*lease)->addr_ == addr) {
            lease->reset();
            removed = true;
        }
    }

    // Remove all elements that have NULL value
    container.erase(std::remove(container.begin(), container.end(), Lease6Ptr()),
                    container.end());

    return (removed);
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

    // This is officially not scary code anymore. iterates and marks specified
    // leases for deletion, by setting appropriate pointers to NULL.
    for (Lease6Collection::iterator lease = existing_leases.begin();
         lease != existing_leases.end(); ++lease) {
        IPv6Resrv resv(ctx.type_ == Lease::TYPE_NA ? IPv6Resrv::TYPE_NA : IPv6Resrv::TYPE_PD,
                       (*lease)->addr_, (*lease)->prefixlen_);
        if (!ctx.host_->hasReservation(resv)) {
            // We have reservations, but not for this lease. Release it.

            // Remove this lease from LeaseMgr
            LeaseMgrFactory::instance().deleteLease((*lease)->addr_);

            /// @todo: Probably trigger a hook here

            // Add this to the list of removed leases.
            ctx.old_leases_.push_back(*lease);

            // Set this pointer to NULL. The pointer is still valid. We're just
            // setting the Lease6Ptr to NULL value. We'll remove all NULL
            // pointers once the loop is finished.
            lease->reset();

            if (--total == 1) {
                // If there's only one lease left, break the loop.
                break;
            }
        }

    }

    // Remove all elements that we previously marked for deletion (those that
    // have NULL value).
    existing_leases.erase(std::remove(existing_leases.begin(),
        existing_leases.end(), Lease6Ptr()), existing_leases.end());
}

Lease6Ptr
AllocEngine::reuseExpiredLease(Lease6Ptr& expired, ClientContext6& ctx,
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

Lease6Collection
AllocEngine::renewLeases6(ClientContext6& ctx) {
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
        } else {
            // Host reservations disabled? Then explicitly set host to NULL
            ctx.host_.reset();
        }

        // Check if there are any leases for this client.
        Lease6Collection leases = LeaseMgrFactory::instance()
            .getLeases6(ctx.type_, *ctx.duid_, ctx.iaid_, ctx.subnet_->getID());

        if (!leases.empty()) {
            // Check if the existing leases are reserved for someone else.
            // If they're not, we're ok to keep using them.
            removeNonmatchingReservedLeases6(ctx, leases);
        }

        if (ctx.host_) {
            // If we have host reservation, allocate those leases.
            allocateReservedLeases6(ctx, leases);

            // There's one more check to do. Let's remove leases that are not
            // matching reservations, i.e. if client X has address A, but there's
            // a reservation for address B, we should release A and reassign B.
            // Caveat: do this only if we have at least one reserved address.
            removeNonreservedLeases6(ctx, leases);
        }

        // If we happen to removed all leases, get something new for this guy.
        // Depending on the configuration, we may enable or disable granting
        // new leases during renewals. This is controlled with the
        // allow_new_leases_in_renewals_ field.
        if (leases.empty() && ctx.allow_new_leases_in_renewals_) {
            leases = allocateUnreservedLeases6(ctx);
        }

        // Extend all existing leases that passed all checks.
        for (Lease6Collection::iterator l = leases.begin(); l != leases.end(); ++l) {
            extendLease6(ctx, *l);
        }

        return (leases);

    } catch (const isc::Exception& e) {

        // Some other error, return an empty lease.
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_RENEW6_ERROR).arg(e.what());
    }

    return (Lease6Collection());
}

void
AllocEngine::extendLease6(ClientContext6& ctx, Lease6Ptr lease) {

    if (!lease || !ctx.subnet_) {
        return;
    }

    // Check if the lease still belongs to the subnet. If it doesn't,
    // we'll need to remove it.
    if ((lease->type_ != Lease::TYPE_PD) && !ctx.subnet_->inRange(lease->addr_)) {
        // Oh dear, the lease is no longer valid. We need to get rid of it.

        // Remove this lease from LeaseMgr
        LeaseMgrFactory::instance().deleteLease(lease->addr_);

        // Add it to the removed leases list.
        ctx.old_leases_.push_back(lease);

        return;
    }

    // Keep the old data in case the callout tells us to skip update.
    Lease6 old_data = *lease;

    lease->preferred_lft_ = ctx.subnet_->getPreferred();
    lease->valid_lft_ = ctx.subnet_->getValid();
    lease->t1_ = ctx.subnet_->getT1();
    lease->t2_ = ctx.subnet_->getT2();
    lease->cltt_ = time(NULL);
    lease->hostname_ = ctx.hostname_;
    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hwaddr_ = ctx.hwaddr_;

    bool skip = false;
    // Get the callouts specific for the processed message and execute them.
    int hook_point = ctx.query_->getType() == DHCPV6_RENEW ?
        Hooks.hook_index_lease6_renew_ : Hooks.hook_index_lease6_rebind_;
    if (HooksManager::calloutsPresent(hook_point)) {
        CalloutHandlePtr callout_handle = ctx.callout_handle_;

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass the original packet
        callout_handle->setArgument("query6", ctx.query_);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Pass the IA option to be sent in response
        if (lease->type_ == Lease::TYPE_NA) {
            callout_handle->setArgument("ia_na", ctx.ia_rsp_);
        } else {
            callout_handle->setArgument("ia_pd", ctx.ia_rsp_);
        }

        // Call all installed callouts
        HooksManager::callCallouts(hook_point, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        if (callout_handle->getSkip()) {
            skip = true;
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE6_EXTEND_SKIP)
                .arg(ctx.query_->getName());
        }
    }

    if (!skip) {
        LeaseMgrFactory::instance().updateLease6(lease);
    } else {
        // Copy back the original date to the lease. For MySQL it doesn't make
        // much sense, but for memfile, the Lease6Ptr points to the actual lease
        // in memfile, so the actual update is performed when we manipulate
        // fields of returned Lease6Ptr, the actual updateLease6() is no-op.
        *lease = old_data;
    }
}

Lease6Collection
AllocEngine::updateFqdnData(ClientContext6& ctx, const Lease6Collection& leases) {
    Lease6Collection updated_leases;
    for (Lease6Collection::const_iterator lease_it = leases.begin();
         lease_it != leases.end(); ++lease_it) {
        Lease6Ptr lease(new Lease6(**lease_it));
        lease->fqdn_fwd_ = ctx.fwd_dns_update_;
        lease->fqdn_rev_ = ctx.rev_dns_update_;
        lease->hostname_ = ctx.hostname_;
        if (!ctx.fake_allocation_ &&
            ((lease->fqdn_fwd_ != (*lease_it)->fqdn_fwd_) ||
             (lease->fqdn_rev_ != (*lease_it)->fqdn_rev_) ||
             (lease->hostname_ != (*lease_it)->hostname_))) {
            ctx.changed_leases_.push_back(*lease_it);
            LeaseMgrFactory::instance().updateLease6(lease);
        }
        updated_leases.push_back(lease);
    }
    return (updated_leases);
}

} // end of isc::dhcp namespace
} // end of isc namespace

// ##########################################################################
// #    DHCPv4 lease allocation code starts here.
// ##########################################################################

namespace {

bool
addressReserved(const IOAddress& address, const AllocEngine::ClientContext4& ctx) {
    ConstHostPtr host = HostMgr::instance().get4(ctx.subnet_->getID(), address);
    HWAddrPtr host_hwaddr;
    if (host) {
        host_hwaddr = host->getHWAddress();
        if (ctx.hwaddr_ && host_hwaddr) {
            /// @todo Use the equality operators for HWAddr class.
            /// Currently, this is impossible because the HostMgr uses the
            /// HTYPE_ETHER type, whereas the unit tests may use other types
            /// which HostMgr doesn't support yet.
            return (host_hwaddr->hwaddr_ != ctx.hwaddr_->hwaddr_);

        } else {
            return (true);

        }
    }
    return (false);
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

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

    Lease4Ptr new_lease;

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
    /// the API change is done with a separate ticket (#3709).
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

    try {
        if (!subnet) {
            isc_throw(BadValue, "Can't allocate IPv4 address without subnet");
        }

        if (!hwaddr) {
            isc_throw(BadValue, "HWAddr must be defined");
        }

        ctx.host_ = HostMgr::instance().get4(subnet->getID(), hwaddr);

        new_lease = ctx.fake_allocation_ ? discoverLease4(ctx) : requestLease4(ctx);
        if (!new_lease) {
            // Unable to allocate an address, return an empty lease.
            LOG_WARN(dhcpsrv_logger, DHCPSRV_ADDRESS4_ALLOC_FAIL).arg(attempts_);
        }

    } catch (const isc::Exception& e) {
        // Some other error, return an empty lease.
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_ADDRESS4_ALLOC_ERROR).arg(e.what());
    }

    if (ctx.old_lease_) {
        old_lease.reset(new Lease4(*ctx.old_lease_));
    }

    return (new_lease);
}

Lease4Ptr
AllocEngine::discoverLease4(AllocEngine::ClientContext4& ctx) {
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();

    Lease4Ptr client_lease = lease_mgr.getLease4(*ctx.hwaddr_, ctx.subnet_->getID());
    if (!client_lease && ctx.clientid_) {
        client_lease = lease_mgr.getLease4(*ctx.clientid_, ctx.subnet_->getID());
    }

    Lease4Ptr new_lease;
    if (ctx.host_) {
        new_lease = allocateOrReuseLease(ctx.host_->getIPv4Reservation(), ctx);
        if (new_lease) {
            if (client_lease) {
                ctx.old_lease_.reset(new Lease4(*client_lease));
            }
            return (new_lease);
        }
    }

    if (client_lease && !addressReserved(ctx.requested_address_, ctx) &&
        ctx.subnet_->inPool(Lease::TYPE_V4, ctx.requested_address_)) {
        return (renewLease4(client_lease, ctx));
    }

    if (!ctx.requested_address_.isV4Zero() && !addressReserved(ctx.requested_address_, ctx)) {
        if (ctx.subnet_->inPool(Lease::TYPE_V4, ctx.requested_address_)) {
            new_lease = allocateOrReuseLease(ctx.requested_address_, ctx);
            if (new_lease) {
                if (client_lease) {
                    ctx.old_lease_.reset(new Lease4(*client_lease));
                }
                return (new_lease);
            }
        }
    }

    AllocatorPtr allocator = getAllocator(Lease::TYPE_V4);
    const uint64_t max_attempts = ctx.subnet_->getPoolCapacity(Lease::TYPE_V4);
    for (uint64_t i = 0; i < max_attempts; ++i) {
        IOAddress candidate = allocator->pickAddress(ctx.subnet_, ctx.clientid_,
                                                     ctx.requested_address_);
        if (!addressReserved(candidate, ctx)) {
            new_lease = allocateOrReuseLease(candidate, ctx);
            if (new_lease) {
                return (new_lease);
            }
        }
    }

    return (Lease4Ptr());
}

Lease4Ptr
AllocEngine::requestLease4(AllocEngine::ClientContext4& ctx) {
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    Lease4Ptr client_lease = lease_mgr.getLease4(*ctx.hwaddr_, ctx.subnet_->getID());
    if (!client_lease && ctx.clientid_) {
        client_lease = lease_mgr.getLease4(*ctx.clientid_, ctx.subnet_->getID());
    }

    if (!ctx.requested_address_.isV4Zero()) {
        if (addressReserved(ctx.requested_address_, ctx)) {
            return (Lease4Ptr());
        }

    } else if (ctx.host_) {
        ctx.requested_address_ = ctx.host_->getIPv4Reservation();
    }

    if (!ctx.requested_address_.isV4Zero()) {
        Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(ctx.requested_address_);
        if (existing && !existing->expired()) {
            if (!ctx.myLease(*existing)) {
                return (Lease4Ptr());
            }

        }

        if (ctx.host_ && (ctx.host_->getIPv4Reservation() != ctx.requested_address_)) {
            existing = LeaseMgrFactory::instance().getLease4(ctx.host_->getIPv4Reservation());
            if (!existing || existing->expired()) {
                return (Lease4Ptr());
            }
        }
    }

    if (!ctx.subnet_->inPool(Lease4::TYPE_V4, ctx.requested_address_)) {
        if ((ctx.host_ && (ctx.host_->getIPv4Reservation() != ctx.requested_address_)) ||
            (!ctx.host_ && !ctx.requested_address_.isV4Zero())) {
            return (Lease4Ptr());
        }
    }

    if (client_lease) {
        if ((client_lease->addr_ == ctx.requested_address_) ||
            ctx.requested_address_.isV4Zero()) {
            return (renewLease4(client_lease, ctx));
        }
    }

    Lease4Ptr new_lease;
    if (!ctx.requested_address_.isV4Zero()) {
        new_lease = allocateOrReuseLease(ctx.requested_address_, ctx);
        if (new_lease) {
            if (client_lease && (client_lease->addr_ != new_lease->addr_)) {
                ctx.old_lease_ = client_lease;
                lease_mgr.deleteLease(client_lease->addr_);
            }
            return (new_lease);
        }
    }

    AllocatorPtr allocator = getAllocator(Lease::TYPE_V4);
    const uint64_t max_attempts = ctx.subnet_->getPoolCapacity(Lease::TYPE_V4);
    for (uint64_t i = 0; i < max_attempts; ++i) {
        IOAddress candidate = allocator->pickAddress(ctx.subnet_, ctx.clientid_,
                                                     ctx.requested_address_);
        if (!addressReserved(candidate, ctx)) {
            new_lease = allocateOrReuseLease(candidate, ctx);
            if (new_lease) {
                return (new_lease);
            }
        }
    }

    return (Lease4Ptr());
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

Lease4Ptr
AllocEngine::renewLease4(const Lease4Ptr& lease,
                         AllocEngine::ClientContext4& ctx) {
    if (!lease) {
        isc_throw(BadValue, "null lease specified for renewLease4");
    }

    // Let's keep the old data. This is essential if we are using memfile
    // (the lease returned points directly to the lease4 object in the database)
    // We'll need it if we want to skip update (i.e. roll back renewal)
    /// @todo: remove this once #3083 is implemented
    Lease4 old_values = *lease;
    ctx.old_lease_.reset(new Lease4(old_values));

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
AllocEngine::allocateOrReuseLease(const IOAddress& candidate, ClientContext4& ctx) {
    Lease4Ptr exist_lease = LeaseMgrFactory::instance().getLease4(candidate);
    if (exist_lease) {
        if (exist_lease->expired()) {
            ctx.old_lease_.reset(new Lease4(*exist_lease));
            return (reuseExpiredLease(exist_lease, ctx));
        }

    } else {
        return (createLease4(ctx.subnet_, ctx.clientid_,
                             ctx.hwaddr_, candidate, ctx.fwd_dns_update_,
                             ctx.rev_dns_update_, ctx.hostname_, ctx.callout_handle_,
                             ctx.fake_allocation_));
    }
    return (Lease4Ptr());
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

}; // end of isc::dhcp namespace
}; // end of isc namespace
