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
AllocEngine::allocateLeases6(const Subnet6Ptr& subnet, const DuidPtr& duid,
                             const uint32_t iaid, const IOAddress& hint,
                             Lease::Type type, const bool fwd_dns_update,
                             const bool rev_dns_update,
                             const std::string& hostname, bool fake_allocation,
                             const isc::hooks::CalloutHandlePtr& callout_handle,
                             Lease6Collection& old_leases, const HWAddrPtr& hwaddr) {

    try {
        AllocatorPtr allocator = getAllocator(type);

        if (!allocator) {
            isc_throw(InvalidOperation, "No allocator specified for "
                      << Lease6::typeToText(type));
        }

        if (!subnet) {
            isc_throw(InvalidOperation, "Subnet is required for allocation");
        }

        if (!duid) {
            isc_throw(InvalidOperation, "DUID is mandatory for allocation");
        }

        // Check if there's existing lease for that subnet/duid/iaid
        // combination.
        /// @todo: Make this generic (cover temp. addrs and prefixes)
        Lease6Collection existing = LeaseMgrFactory::instance().getLeases6(type,
                                    *duid, iaid, subnet->getID());

        // There is at least one lease for this client. We will return these
        // leases for the client, but we may need to update FQDN information.
        if (!existing.empty()) {
            // Return old leases so the server can see what has changed.
            old_leases = existing;
            return (updateFqdnData(existing, fwd_dns_update, rev_dns_update,
                                   hostname, fake_allocation));
        }

        // check if the hint is in pool and is available
        // This is equivalent of subnet->inPool(hint), but returns the pool
        Pool6Ptr pool = boost::dynamic_pointer_cast<
            Pool6>(subnet->getPool(type, hint, false));

        if (pool) {
            /// @todo: We support only one hint for now
            Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(type, hint);
            if (!lease) {
                /// @todo: check if the hint is reserved once we have host
                /// support implemented

                // The hint is valid and not currently used, let's create a
                // lease for it
                lease = createLease6(subnet, duid, iaid, hint,
                                     pool->getLength(), type,
                                     fwd_dns_update, rev_dns_update,
                                     hostname, hwaddr, callout_handle, fake_allocation);

                // It can happen that the lease allocation failed (we could
                // have lost the race condition. That means that the hint is
                // lo longer usable and we need to continue the regular
                // allocation path.
                if (lease) {
                    // We are allocating a new lease (not renewing). So, the
                    // old lease should be NULL.
                    old_leases.push_back(Lease6Ptr());

                    /// @todo: We support only one lease per ia for now
                    Lease6Collection collection;
                    collection.push_back(lease);
                    return (collection);
                }
            } else {
                if (lease->expired()) {
                    // Copy an existing, expired lease so as it can be returned
                    // to the caller.
                    Lease6Ptr old_lease(new Lease6(*lease));
                    old_leases.push_back(old_lease);

                    /// We found a lease and it is expired, so we can reuse it
                    lease = reuseExpiredLease(lease, subnet, duid, iaid,
                                              pool->getLength(),
                                              fwd_dns_update, rev_dns_update,
                                              hostname, callout_handle,
                                              fake_allocation);

                    /// @todo: We support only one lease per ia for now
                    Lease6Collection collection;
                    collection.push_back(lease);
                    return (collection);
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
            IOAddress candidate = allocator->pickAddress(subnet, duid, hint);

            /// @todo: check if the address is reserved once we have host support
            /// implemented

            // The first step is to find out prefix length. It is 128 for
            // non-PD leases.
            uint8_t prefix_len = 128;
            if (type == Lease::TYPE_PD) {
                Pool6Ptr pool = boost::dynamic_pointer_cast<Pool6>(
                    subnet->getPool(type, candidate, false));
                prefix_len = pool->getLength();
            }

            Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(type,
                                 candidate);
            if (!existing) {

                // there's no existing lease for selected candidate, so it is
                // free. Let's allocate it.

                Lease6Ptr lease = createLease6(subnet, duid, iaid, candidate,
                                               prefix_len, type, fwd_dns_update,
                                               rev_dns_update, hostname, hwaddr,
                                               callout_handle, fake_allocation);
                if (lease) {
                    // We are allocating a new lease (not renewing). So, the
                    // old lease should be NULL.
                    old_leases.push_back(Lease6Ptr());

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
                    old_leases.push_back(old_lease);

                    existing = reuseExpiredLease(existing, subnet, duid, iaid,
                                                 prefix_len, fwd_dns_update,
                                                 rev_dns_update, hostname,
                                                 callout_handle, fake_allocation);
                    Lease6Collection collection;
                    collection.push_back(existing);
                    return (collection);
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

    return (Lease6Collection());
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

        AllocatorPtr allocator = getAllocator(Lease::TYPE_V4);

        // Allocator is always created in AllocEngine constructor and there is
        // currently no other way to set it, so that check is not really necessary.
        if (!allocator) {
            isc_throw(InvalidOperation, "No allocator selected");
        }

        if (!subnet) {
            isc_throw(InvalidOperation, "Can't allocate IPv4 address without subnet");
        }

        if (!hwaddr) {
            isc_throw(InvalidOperation, "HWAddr must be defined");
        }

        // Build the processing context.
        Context4 ctx;
        ctx.subnet_ = subnet;
        ctx.clientid_ = clientid;
        ctx.hwaddr_ = hwaddr;
        ctx.hint_ = hint;
        ctx.fwd_dns_update_ = fwd_dns_update;
        ctx.rev_dns_update_ = rev_dns_update;
        ctx.hostname_ = hostname;
        ctx.fake_allocation_ = fake_allocation;
        ctx.callout_handle_ = callout_handle;
        ctx.old_lease_ = old_lease;
        ctx.host_ = HostMgr::instance().get4(subnet->getID(), hwaddr);

        if (ctx.host_) {
            if (ctx.hint_ == IOAddress("0.0.0.0")) {
                ctx.hint_ = ctx.host_->getIPv4Reservation();

            } else if (!ctx.fake_allocation_ &&
                       (ctx.hint_ != ctx.host_->getIPv4Reservation())) {
                return (Lease4Ptr());
            }
        }

        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        Lease4Ptr existing = lease_mgr.getLease4(*hwaddr, ctx.subnet_->getID());
        if (!existing && clientid) {
            existing = lease_mgr.getLease4(*clientid, ctx.subnet_->getID());
        }

        if (existing) {
            existing = reallocateClientLease(existing, ctx);
            if (ctx.host_ || existing) {
                old_lease = ctx.old_lease_;
                return (existing);
            }
        }

        // Check if we have a specific address we would like to allocate for the
        // client. It may either be an address which the client is currently
        // using, or it may be a administratively reserved address.
        if (ctx.host_ || subnet->inPool(Lease::TYPE_V4, hint)) {
            // If a client is requesting specific IP address, but the
            // reservation was made for a different address the server returns
            // NAK to the client. By returning NULL lease here we indicate to
            // the server that we're not able to fulfil client's request for the
            // particular IP address.
            if (!ctx.fake_allocation_ && ctx.host_ &&
                (hint != IOAddress("0.0.0.0")) &&
                (ctx.host_->getIPv4Reservation() != hint)) {
                return (Lease4Ptr());
            }

            // The reserved address always takes precedence over hints. But, if
            // there is no reservation, try to respect the client's hint.
            const IOAddress& candidate = ctx.host_ ?
                ctx.host_->getIPv4Reservation() : hint;

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

            } else {
                if (existing->expired()) {
                    // Save the old lease, before reusing it.
                    old_lease.reset(new Lease4(*existing));
                    return (reuseExpiredLease(existing, ctx));

                } else if (ctx.host_ && (ctx.host_->getIPv4Reservation() !=
                                         IOAddress("0.0.0.0"))) {
                    return (Lease4Ptr());

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
            IOAddress candidate = allocator->pickAddress(subnet, clientid, hint);

            /// @todo: check if the address is reserved once we have host support
            /// implemented

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
                         const AllocEngine::Context4& ctx) {
    if (!lease) {
        isc_throw(BadValue, "null lease specified for renewLease4");
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
                                         const Subnet6Ptr& subnet,
                                         const DuidPtr& duid,
                                         const uint32_t iaid,
                                         uint8_t prefix_len,
                                         const bool fwd_dns_update,
                                         const bool rev_dns_update,
                                         const std::string& hostname,
                                         const isc::hooks::CalloutHandlePtr& callout_handle,
                                         bool fake_allocation /*= false */ ) {

    if (!expired->expired()) {
        isc_throw(BadValue, "Attempt to recycle lease that is still valid");
    }

    if (expired->type_ != Lease::TYPE_PD) {
        prefix_len = 128; // non-PD lease types must be always /128
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
    expired->hostname_ = hostname;
    expired->fqdn_fwd_ = fwd_dns_update;
    expired->fqdn_rev_ = rev_dns_update;
    expired->prefixlen_ = prefix_len;

    /// @todo: log here that the lease was reused (there's ticket #2524 for
    /// logging in libdhcpsrv)

    // Let's execute all callouts registered for lease6_select
    if (callout_handle &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease6_select_)) {

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass necessary arguments
        // Subnet from which we do the allocation
        callout_handle->setArgument("subnet6", subnet);

        // Is this solicit (fake = true) or request (fake = false)
        callout_handle->setArgument("fake_allocation", fake_allocation);

        // The lease that will be assigned to a client
        callout_handle->setArgument("lease6", expired);

        // Call the callouts
        HooksManager::callCallouts(hook_index_lease6_select_, *callout_handle);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_handle->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_SELECT_SKIP);
            return (Lease6Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        callout_handle->getArgument("lease6", expired);
    }

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

Lease4Ptr
AllocEngine::reuseExpiredLease(Lease4Ptr& expired,
                               const AllocEngine::Context4& ctx) {
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
AllocEngine::replaceClientLease(Lease4Ptr& lease, const Context4& ctx) {
    if (!lease) {
        isc_throw(BadValue, "null lease specified for replaceClientLease");
    }

    if (!ctx.subnet_) {
        isc_throw(BadValue, "null subnet specified for replaceClientLease");
    }

    if (!ctx.host_) {
        isc_throw(BadValue, "null host specified for replaceClientLease");
    }

    if (ctx.hint_ == IOAddress("0.0.0.0")) {
        isc_throw(BadValue, "zero address specified for the"
                  " replaceClientLease");
    }

    IOAddress prev_address = lease->addr_;
    updateLease4Information(lease, ctx);
    lease->addr_ = ctx.host_->getIPv4Reservation();

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
    }

    if (!ctx.fake_allocation_) {
        LeaseMgrFactory::instance().deleteLease(prev_address);
        LeaseMgrFactory::instance().addLease(lease);
    }

    return (lease);
}

Lease4Ptr
AllocEngine::reallocateClientLease(Lease4Ptr& lease,
                                   AllocEngine::Context4& ctx) {
    // Save the old lease, before renewal.
    ctx.old_lease_.reset(new Lease4(*lease));

    if (ctx.host_ && ctx.host_->getIPv4Reservation() != lease->addr_) {
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


Lease6Ptr AllocEngine::createLease6(const Subnet6Ptr& subnet,
                                    const DuidPtr& duid,
                                    const uint32_t iaid,
                                    const IOAddress& addr,
                                    uint8_t prefix_len,
                                    const Lease::Type type,
                                    const bool fwd_dns_update,
                                    const bool rev_dns_update,
                                    const std::string& hostname,
                                    const HWAddrPtr& hwaddr,
                                    const isc::hooks::CalloutHandlePtr& callout_handle,
                                    bool fake_allocation /*= false */ ) {

    if (type != Lease::TYPE_PD) {
        prefix_len = 128; // non-PD lease types must be always /128
    }

    Lease6Ptr lease(new Lease6(type, addr, duid, iaid,
                               subnet->getPreferred(), subnet->getValid(),
                               subnet->getT1(), subnet->getT2(), subnet->getID(),
                               hwaddr, prefix_len));

    lease->fqdn_fwd_ = fwd_dns_update;
    lease->fqdn_rev_ = rev_dns_update;
    lease->hostname_ = hostname;

    // Let's execute all callouts registered for lease6_select
    if (callout_handle &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease6_select_)) {

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass necessary arguments

        // Subnet from which we do the allocation
        callout_handle->setArgument("subnet6", subnet);

        // Is this solicit (fake = true) or request (fake = false)
        callout_handle->setArgument("fake_allocation", fake_allocation);
        callout_handle->setArgument("lease6", lease);

        // This is the first callout, so no need to clear any arguments
        HooksManager::callCallouts(hook_index_lease6_select_, *callout_handle);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_handle->getSkip()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_SELECT_SKIP);
            return (Lease6Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        callout_handle->getArgument("lease6", lease);
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
                                     const AllocEngine::Context4& ctx) const {
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
