// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/alloc_engine_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/shared_network.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <dhcpsrv/callout_handle_store.h>
#include <stats/stats_mgr.h>
#include <util/stopwatch.h>
#include <hooks/server_hooks.h>
#include <hooks/hooks_manager.h>

#include <boost/foreach.hpp>

#include <algorithm>
#include <cstring>
#include <sstream>
#include <limits>
#include <vector>
#include <stdint.h>
#include <string.h>
#include <utility>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::hooks;
using namespace isc::stats;

namespace {

/// Structure that holds registered hook indexes
struct AllocEngineHooks {
    int hook_index_lease4_select_; ///< index for "lease4_receive" hook point
    int hook_index_lease4_renew_;  ///< index for "lease4_renew" hook point
    int hook_index_lease4_expire_; ///< index for "lease4_expire" hook point
    int hook_index_lease4_recover_;///< index for "lease4_recover" hook point
    int hook_index_lease6_select_; ///< index for "lease6_receive" hook point
    int hook_index_lease6_renew_;  ///< index for "lease6_renew" hook point
    int hook_index_lease6_rebind_; ///< index for "lease6_rebind" hook point
    int hook_index_lease6_expire_; ///< index for "lease6_expire" hook point
    int hook_index_lease6_recover_;///< index for "lease6_recover" hook point

    /// Constructor that registers hook points for AllocationEngine
    AllocEngineHooks() {
        hook_index_lease4_select_ = HooksManager::registerHook("lease4_select");
        hook_index_lease4_renew_  = HooksManager::registerHook("lease4_renew");
        hook_index_lease4_expire_ = HooksManager::registerHook("lease4_expire");
        hook_index_lease4_recover_= HooksManager::registerHook("lease4_recover");
        hook_index_lease6_select_ = HooksManager::registerHook("lease6_select");
        hook_index_lease6_renew_  = HooksManager::registerHook("lease6_renew");
        hook_index_lease6_rebind_ = HooksManager::registerHook("lease6_rebind");
        hook_index_lease6_expire_ = HooksManager::registerHook("lease6_expire");
        hook_index_lease6_recover_= HooksManager::registerHook("lease6_recover");
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
AllocEngine::IterativeAllocator::increaseAddress(const isc::asiolink::IOAddress& address,
                                                 bool prefix,
                                                 const uint8_t prefix_len) {
    if (!prefix) {
        return (IOAddress::increase(address));
    } else {
        return (increasePrefix(address, prefix_len));
    }
}

isc::asiolink::IOAddress
AllocEngine::IterativeAllocator::pickAddress(const SubnetPtr& subnet,
                                             const ClientClasses& client_classes,
                                             const DuidPtr&,
                                             const IOAddress&) {

    // Is this prefix allocation?
    bool prefix = pool_type_ == Lease::TYPE_PD;
    uint8_t prefix_len = 0;

    // Let's get the last allocated address. It is usually set correctly,
    // but there are times when it won't be (like after removing a pool or
    // perhaps restarting the server).
    IOAddress last = subnet->getLastAllocated(pool_type_);
    bool valid = true;
    bool retrying = false;

    const PoolCollection& pools = subnet->getPools(pool_type_);

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

        last = (*it)->getLastAllocated();
        valid = (*it)->isLastAllocatedValid();
        if (!valid && (last == (*it)->getFirstAddress())) {
            // Pool was (re)initialized
            (*it)->setLastAllocated(last);
            subnet->setLastAllocated(pool_type_, last);
            return (last);
        }
        // still can be bogus
        if (valid && !(*it)->inRange(last)) {
            valid = false;
            (*it)->resetLastAllocated();
            (*it)->setLastAllocated((*it)->getFirstAddress());
        }

        if (valid) {
            // Ok, we have a pool that the last address belonged to, let's use it.
            if (prefix) {
                Pool6Ptr pool6 = boost::dynamic_pointer_cast<Pool6>(*it);

                if (!pool6) {
                    // Something is gravely wrong here
                    isc_throw(Unexpected, "Wrong type of pool: "
                              << (*it)->toText()
                              << " is not Pool6");
                }
                // Get the prefix length
                prefix_len = pool6->getLength();
            }

            IOAddress next = increaseAddress(last, prefix, prefix_len);
            if ((*it)->inRange(next)) {
                // the next one is in the pool as well, so we haven't hit
                // pool boundary yet
                (*it)->setLastAllocated(next);
                subnet->setLastAllocated(pool_type_, next);
                return (next);
            }

            valid = false;
            (*it)->resetLastAllocated();
        }
        // We hit pool boundary, let's try to jump to the next pool and try again
        ++it;
        retrying = true;
    }

    // Let's rewind to the beginning.
    for (it = first; it != pools.end(); ++it) {
        if ((*it)->clientSupported(client_classes)) {
            (*it)->setLastAllocated((*it)->getFirstAddress());
            (*it)->resetLastAllocated();
        }
    }

    // ok to access first element directly. We checked that pools is non-empty
    last = (*first)->getLastAllocated();
    (*first)->setLastAllocated(last);
    subnet->setLastAllocated(pool_type_, last);
    return (last);
}

AllocEngine::HashedAllocator::HashedAllocator(Lease::Type lease_type)
    :Allocator(lease_type) {
    isc_throw(NotImplemented, "Hashed allocator is not implemented");
}


isc::asiolink::IOAddress
AllocEngine::HashedAllocator::pickAddress(const SubnetPtr&,
                                          const ClientClasses&,
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
                                          const ClientClasses&,
                                          const DuidPtr&,
                                          const IOAddress&) {
    isc_throw(NotImplemented, "Random allocator is not implemented");
}


AllocEngine::AllocEngine(AllocType engine_type, uint64_t attempts,
                         bool ipv6)
    : attempts_(attempts), incomplete_v4_reclamations_(0),
      incomplete_v6_reclamations_(0) {

    // Choose the basic (normal address) lease type
    Lease::Type basic_type = ipv6 ? Lease::TYPE_NA : Lease::TYPE_V4;

    // Initialize normal address allocators
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

    // If this is IPv6 allocation engine, initialize also temporary addrs
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

} // end of namespace isc::dhcp
} // end of namespace isc

namespace {

/// @brief Checks if the specified address belongs to one of the subnets
/// within a shared network.
///
/// @param ctx Client context. Current subnet may be modified by this
/// function when it belongs to a shared network.
/// @param lease_type Type of the lease.
/// @param address IPv6 address or prefix to be checked.
/// @param check_subnet if true only subnets are checked else both subnets
/// and pools are checked
///
/// @return true if address belongs to a pool in a selected subnet or in
/// a pool within any of the subnets belonging to the current shared network.
bool
inAllowedPool(AllocEngine::ClientContext6& ctx, const Lease::Type& lease_type,
              const IOAddress& address, bool check_subnet) {
    // If the subnet belongs to a shared network we will be iterating
    // over the subnets that belong to this shared network.
    Subnet6Ptr current_subnet = ctx.subnet_;
    while (current_subnet) {

        if (current_subnet->clientSupported(ctx.query_->getClasses())) {
            if (check_subnet) {
                if (current_subnet->inPool(lease_type, address)) {
                    return (true);
                }
            } else {
                if (current_subnet->inPool(lease_type, address,
                                           ctx.query_->getClasses())) {
                    return (true);
                }
            }
        }

        current_subnet = current_subnet->getNextSubnet(ctx.subnet_);
    }

    return (false);
}

}


// ##########################################################################
// #    DHCPv6 lease allocation code starts here.
// ##########################################################################

namespace isc {
namespace dhcp {

AllocEngine::ClientContext6::ClientContext6()
    : query_(), fake_allocation_(false), subnet_(), host_subnet_(), duid_(),
      hwaddr_(), host_identifiers_(), hosts_(), fwd_dns_update_(false),
      rev_dns_update_(false), hostname_(), callout_handle_(), ias_() {
}

AllocEngine::ClientContext6::ClientContext6(const Subnet6Ptr& subnet,
                                            const DuidPtr& duid,
                                            const bool fwd_dns,
                                            const bool rev_dns,
                                            const std::string& hostname,
                                            const bool fake_allocation,
                                            const Pkt6Ptr& query,
                                            const CalloutHandlePtr& callout_handle)
    : query_(query), fake_allocation_(fake_allocation), subnet_(subnet),
      duid_(duid), hwaddr_(), host_identifiers_(), hosts_(),
      fwd_dns_update_(fwd_dns), rev_dns_update_(rev_dns), hostname_(hostname),
      callout_handle_(callout_handle), allocated_resources_(), new_leases_(),
      ias_() {

    // Initialize host identifiers.
    if (duid) {
        addHostIdentifier(Host::IDENT_DUID, duid->getDuid());
    }
}

AllocEngine::ClientContext6::IAContext::IAContext()
    : iaid_(0), type_(Lease::TYPE_NA), hints_(), old_leases_(),
      changed_leases_(), ia_rsp_() {
}

void
AllocEngine::ClientContext6::
IAContext::addHint(const asiolink::IOAddress& prefix,
                   const uint8_t prefix_len) {
    hints_.push_back(std::make_pair(prefix, prefix_len));
}

void
AllocEngine::ClientContext6::
addAllocatedResource(const asiolink::IOAddress& prefix,
                     const uint8_t prefix_len) {
    static_cast<void>(allocated_resources_.insert(std::make_pair(prefix,
                                                                 prefix_len)));
}

bool
AllocEngine::ClientContext6::
isAllocated(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const {
    return (static_cast<bool>
            (allocated_resources_.count(std::make_pair(prefix, prefix_len))));
}

ConstHostPtr
AllocEngine::ClientContext6::currentHost() const {
    Subnet6Ptr subnet = host_subnet_ ? host_subnet_ : subnet_;
    if (subnet) {
        SubnetID id = (subnet_->getHostReservationMode() == Network::HR_GLOBAL ?
                       SUBNET_ID_GLOBAL : subnet->getID());

        auto host = hosts_.find(id);
        if (host != hosts_.cend()) {
            return (host->second);
        }
    }

    return (ConstHostPtr());
}

ConstHostPtr
AllocEngine::ClientContext6::globalHost() const {
    Subnet6Ptr subnet = host_subnet_ ? host_subnet_ : subnet_;
    if (subnet && subnet_->getHostReservationMode() == Network::HR_GLOBAL) {
        auto host = hosts_.find(SUBNET_ID_GLOBAL);
        if (host != hosts_.cend()) {
            return (host->second);
        }
    }

    return (ConstHostPtr());
}

bool
AllocEngine::ClientContext6::hasGlobalReservation(const IPv6Resrv& resv) const {
    ConstHostPtr ghost = globalHost();
    return (ghost && ghost->hasReservation(resv));
}

void AllocEngine::findReservation(ClientContext6& ctx) {
    ctx.hosts_.clear();

    // If there is no subnet, there is nothing to do.
    if (!ctx.subnet_) {
        return;
    }

    auto subnet = ctx.subnet_;

    std::map<SubnetID, ConstHostPtr> host_map;
    SharedNetwork6Ptr network;
    subnet->getSharedNetwork(network);

    if (subnet->getHostReservationMode() == Network::HR_GLOBAL) {
        ConstHostPtr ghost = findGlobalReservation(ctx);
        if (ghost) {
            ctx.hosts_[SUBNET_ID_GLOBAL] = ghost;

            // @todo In theory, to support global as part of HR_ALL,
            //  we would just keep going, instead of returning.
            return;
        }
    }

    // If the subnet belongs to a shared network it is usually going to be
    // more efficient to make a query for all reservations for a particular
    // client rather than a query for each subnet within this shared network.
    // The only case when it is going to be less efficient is when there are
    // more host identifier types in use than subnets within a shared network.
    // As it breaks RADIUS use of host caching this can be disabled by the
    // host manager.
    const bool use_single_query = network &&
        !HostMgr::instance().getDisableSingleQuery() &&
        (network->getAllSubnets()->size() > ctx.host_identifiers_.size());

    if (use_single_query) {
        for (auto id_pair : ctx.host_identifiers_) {
            ConstHostCollection hosts = HostMgr::instance().getAll(id_pair.first,
                                                                   &id_pair.second[0],
                                                                   id_pair.second.size());
            // Store the hosts in the temporary map, because some hosts may
            // belong to subnets outside of the shared network. We'll need
            // to eliminate them.
            for (auto host = hosts.begin(); host != hosts.end(); ++host) {
                if ((*host)->getIPv6SubnetID()) {
                    host_map[(*host)->getIPv6SubnetID()] = *host;
                }
            }
        }
    }

    // We can only search for the reservation if a subnet has been selected.
    while (subnet) {

        // Only makes sense to get reservations if the client has access
        // to the class and host reservations are enabled.
        if (subnet->clientSupported(ctx.query_->getClasses()) &&
            (subnet->getHostReservationMode() != Network::HR_DISABLED)) {
            // Iterate over configured identifiers in the order of preference
            // and try to use each of them to search for the reservations.
            for (auto id_pair : ctx.host_identifiers_) {
                if (use_single_query) {
                    if (host_map.count(subnet->getID()) > 0) {
                        ctx.hosts_[subnet->getID()] = host_map[subnet->getID()];
                    }

                } else {
                    // Attempt to find a host using a specified identifier.
                    ConstHostPtr host = HostMgr::instance().get6(subnet->getID(),
                                                                 id_pair.first,
                                                                 &id_pair.second[0],
                                                                 id_pair.second.size());
                    // If we found matching host for this subnet.
                    if (host) {
                        ctx.hosts_[subnet->getID()] = host;
                        break;
                    }
                }
            }

        }

        // We need to get to the next subnet if this is a shared network. If it
        // is not (a plain subnet), getNextSubnet will return NULL and we're
        // done here.
        subnet = subnet->getNextSubnet(ctx.subnet_, ctx.query_->getClasses());
    }
}

ConstHostPtr
AllocEngine::findGlobalReservation(ClientContext6& ctx) {
    ConstHostPtr host;
    BOOST_FOREACH(const IdentifierPair& id_pair, ctx.host_identifiers_) {
        // Attempt to find a host using a specified identifier.
        host = HostMgr::instance().get6(SUBNET_ID_GLOBAL, id_pair.first,
                                        &id_pair.second[0], id_pair.second.size());

        // If we found matching global host we're done.
        if (host) {
            break;
        }
    }

    return (host);
}


Lease6Collection
AllocEngine::allocateLeases6(ClientContext6& ctx) {

    try {
        if (!ctx.subnet_) {
            isc_throw(InvalidOperation, "Subnet is required for IPv6 lease allocation");
        } else
        if (!ctx.duid_) {
            isc_throw(InvalidOperation, "DUID is mandatory for IPv6 lease allocation");
        }

        // Check if there are existing leases for that shared network and
        // DUID/IAID.
        Subnet6Ptr subnet = ctx.subnet_;
        Lease6Collection all_leases =
            LeaseMgrFactory::instance().getLeases6(ctx.currentIA().type_,
                                                   *ctx.duid_,
                                                   ctx.currentIA().iaid_);

        // Iterate over the leases and eliminate those that are outside of
        // our shared network.
        Lease6Collection leases;
        while (subnet) {
            for (auto l : all_leases) {
                if ((l)->subnet_id_ == subnet->getID()) {
                    leases.push_back(l);
                }
            }

            subnet = subnet->getNextSubnet(ctx.subnet_);
        }

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

        // Case 1: There are no leases and there's a reservation for this host.
        if (leases.empty() && !ctx.hosts_.empty()) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_ALLOC_NO_LEASES_HR)
                .arg(ctx.query_->getLabel());

            // Try to allocate leases that match reservations. Typically this will
            // succeed, except cases where the reserved addresses are used by
            // someone else.
            allocateReservedLeases6(ctx, leases);

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
        } else if (!leases.empty() && ctx.hosts_.empty()) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_ALLOC_LEASES_NO_HR)
                .arg(ctx.query_->getLabel());

            // Check if the existing leases are reserved for someone else.
            // If they're not, we're ok to keep using them.
            removeNonmatchingReservedLeases6(ctx, leases);

            leases = updateLeaseData(ctx, leases);

            // If leases are empty at this stage, it means that we used to have
            // leases for this client, but we checked and those leases are reserved
            // for someone else, so we lost them. We will need to continue and
            // will finally end up in case 4 (no leases, no reservations), so we'll
            // assign something new.

        // Case 3: There are leases and there are reservations.
        } else if (!leases.empty() && !ctx.hosts_.empty()) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_ALLOC_LEASES_HR)
                .arg(ctx.query_->getLabel());

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

        if (leases.empty()) {
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

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_ALLOC_UNRESERVED)
                .arg(ctx.query_->getLabel());

            leases = allocateUnreservedLeases6(ctx);
        }

        if (!leases.empty()) {
            // If there are any leases allocated, let's store in them in the
            // IA context so as they are available when we process subsequent
            // IAs.
            BOOST_FOREACH(Lease6Ptr lease, leases) {
                ctx.addAllocatedResource(lease->addr_, lease->prefixlen_);
                ctx.new_leases_.push_back(lease);
            }
            return (leases);
        }


    } catch (const isc::Exception& e) {

        // Some other error, return an empty lease.
        LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V6_ALLOC_ERROR)
            .arg(ctx.query_->getLabel())
            .arg(e.what());
    }

    return (Lease6Collection());
}

Lease6Collection
AllocEngine::allocateUnreservedLeases6(ClientContext6& ctx) {

    AllocatorPtr allocator = getAllocator(ctx.currentIA().type_);

    if (!allocator) {
        isc_throw(InvalidOperation, "No allocator specified for "
                  << Lease6::typeToText(ctx.currentIA().type_));
    }

    Lease6Collection leases;

    IOAddress hint = IOAddress::IPV6_ZERO_ADDRESS();
    if (!ctx.currentIA().hints_.empty()) {
        /// @todo: We support only one hint for now
        hint = ctx.currentIA().hints_[0].first;
    }

    Subnet6Ptr original_subnet = ctx.subnet_;
    Subnet6Ptr subnet = ctx.subnet_;

    Pool6Ptr pool;

    CalloutHandle::CalloutNextStep callout_status = CalloutHandle::NEXT_STEP_CONTINUE;

    while (subnet) {

        if (!subnet->clientSupported(ctx.query_->getClasses())) {
            subnet = subnet->getNextSubnet(original_subnet);
            continue;
        }

        ctx.subnet_ = subnet;

        // check if the hint is in pool and is available
        // This is equivalent of subnet->inPool(hint), but returns the pool
        pool = boost::dynamic_pointer_cast<Pool6>
            (subnet->getPool(ctx.currentIA().type_, ctx.query_->getClasses(),
                             hint));

        // check if the pool is allowed
        if (pool && !pool->clientSupported(ctx.query_->getClasses())) {
            pool.reset();
        }

        if (pool) {

            // Check which host reservation mode is supported in this subnet.
            Network::HRMode hr_mode = subnet->getHostReservationMode();

            /// @todo: We support only one hint for now
            Lease6Ptr lease =
                LeaseMgrFactory::instance().getLease6(ctx.currentIA().type_, hint);
            if (!lease) {

                // In-pool reservations: Check if this address is reserved for someone
                // else. There is no need to check for whom it is reserved, because if
                // it has been reserved for us we would have already allocated a lease.

                ConstHostPtr host;
                if (hr_mode != Network::HR_DISABLED) {
                    host = HostMgr::instance().get6(subnet->getID(), hint);
                }

                if (!host) {
                    // If the in-pool reservations are disabled, or there is no
                    // reservation for a given hint, we're good to go.

                    // The hint is valid and not currently used, let's create a
                    // lease for it
                    lease = createLease6(ctx, hint, pool->getLength(), callout_status);

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
                } else {
                    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                              ALLOC_ENGINE_V6_HINT_RESERVED)
                        .arg(ctx.query_->getLabel())
                        .arg(hint.toText());
                }

            } else {

                // If the lease is expired, we may likely reuse it, but...
                if (lease->expired()) {

                    ConstHostPtr host;
                    if (hr_mode != Network::HR_DISABLED) {
                        host = HostMgr::instance().get6(subnet->getID(), hint);
                    }

                    // Let's check if there is a reservation for this address.
                    if (!host) {

                        // Copy an existing, expired lease so as it can be returned
                        // to the caller.
                        Lease6Ptr old_lease(new Lease6(*lease));
                        ctx.currentIA().old_leases_.push_back(old_lease);

                        /// We found a lease and it is expired, so we can reuse it
                        lease = reuseExpiredLease(lease, ctx, pool->getLength(),
                                                  callout_status);

                        /// @todo: We support only one lease per ia for now
                        leases.push_back(lease);
                        return (leases);

                    } else {
                        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                                  ALLOC_ENGINE_V6_EXPIRED_HINT_RESERVED)
                            .arg(ctx.query_->getLabel())
                            .arg(hint.toText());
                    }
                }
            }
        }

        subnet = subnet->getNextSubnet(original_subnet);
    }

    uint64_t total_attempts = 0;

    // Need to check if the subnet belongs to a shared network. If so,
    // we might be able to find a better subnet for lease allocation,
    // for which it is more likely that there are some leases available.
    // If we stick to the selected subnet, we may end up walking over
    // the entire subnet (or more subnets) to discover that the pools
    // have been exhausted. Using a subnet from which a lease was
    // assigned most recently is an optimization which increases
    // the likelyhood of starting from the subnet which pools are not
    // exhausted.
    SharedNetwork6Ptr network;
    original_subnet->getSharedNetwork(network);
    if (network) {
        // This would try to find a subnet with the same set of classes
        // as the current subnet, but with the more recent "usage timestamp".
        // This timestamp is only updated for the allocations made with an
        // allocator (unreserved lease allocations), not the static
        // allocations or requested addresses.
        original_subnet = network->getPreferredSubnet(original_subnet, ctx.currentIA().type_);
    }

    ctx.subnet_ = subnet = original_subnet;

    while (subnet) {

        if (!subnet->clientSupported(ctx.query_->getClasses())) {
            subnet = subnet->getNextSubnet(original_subnet);
            continue;
        }

        // The hint was useless (it was not provided at all, was used by someone else,
        // was out of pool or reserved for someone else). Search the pool until first
        // of the following occurs:
        // - we find a free address
        // - we find an address for which the lease has expired
        // - we exhaust number of tries
        uint64_t possible_attempts =
            subnet->getPoolCapacity(ctx.currentIA().type_,
                                    ctx.query_->getClasses());
        // Try next subnet if there is no chance to get something
        if (possible_attempts == 0) {
            subnet = subnet->getNextSubnet(original_subnet);
            continue;
        }
        uint64_t max_attempts = (attempts_ > 0 ? attempts_  : possible_attempts);
        Network::HRMode hr_mode = subnet->getHostReservationMode();

        // Set the default status code in case the lease6_select callouts
        // do not exist and the callout handle has a status returned by
        // any of the callouts already invoked for this packet.
        if (ctx.callout_handle_) {
            ctx.callout_handle_->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        }

        for (uint64_t i = 0; i < max_attempts; ++i) {

            ++total_attempts;

            IOAddress candidate = allocator->pickAddress(subnet,
                                                         ctx.query_->getClasses(),
                                                         ctx.duid_,
                                                         hint);

            /// In-pool reservations: Check if this address is reserved for someone
            /// else. There is no need to check for whom it is reserved, because if
            /// it has been reserved for us we would have already allocated a lease.
            if (hr_mode == Network::HR_ALL &&
                HostMgr::instance().get6(subnet->getID(), candidate)) {

                // Don't allocate.
                continue;
            }

            // The first step is to find out prefix length. It is 128 for
            // non-PD leases.
            uint8_t prefix_len = 128;
            if (ctx.currentIA().type_ == Lease::TYPE_PD) {
                pool = boost::dynamic_pointer_cast<Pool6>(
                        subnet->getPool(ctx.currentIA().type_,
                                        ctx.query_->getClasses(),
                                        candidate));
                if (pool) {
                    prefix_len = pool->getLength();
                }
            }

            Lease6Ptr existing = LeaseMgrFactory::instance().getLease6(ctx.currentIA().type_,
                                                                   candidate);
            if (!existing) {

                // there's no existing lease for selected candidate, so it is
                // free. Let's allocate it.

                ctx.subnet_ = subnet;
                Lease6Ptr lease = createLease6(ctx, candidate, prefix_len, callout_status);
                if (lease) {
                    // We are allocating a new lease (not renewing). So, the
                    // old lease should be NULL.
                    ctx.currentIA().old_leases_.clear();

                    leases.push_back(lease);
                    return (leases);

                } else if (ctx.callout_handle_ &&
                           (callout_status != CalloutHandle::NEXT_STEP_CONTINUE)) {
                    // Don't retry when the callout status is not continue.
                    break;
                }

                // Although the address was free just microseconds ago, it may have
                // been taken just now. If the lease insertion fails, we continue
                // allocation attempts.
            } else {
                if (existing->expired()) {
                    // Copy an existing, expired lease so as it can be returned
                    // to the caller.
                    Lease6Ptr old_lease(new Lease6(*existing));
                    ctx.currentIA().old_leases_.push_back(old_lease);

                    ctx.subnet_ = subnet;
                    existing = reuseExpiredLease(existing, ctx, prefix_len,
                                                 callout_status);

                    leases.push_back(existing);
                    return (leases);
                }
            }
        }

        subnet = subnet->getNextSubnet(original_subnet);
    }

    // Unable to allocate an address, return an empty lease.
    LOG_WARN(alloc_engine_logger, ALLOC_ENGINE_V6_ALLOC_FAIL)
        .arg(ctx.query_->getLabel())
        .arg(total_attempts);

    // We failed to allocate anything. Let's return empty collection.
    return (Lease6Collection());
}

void
AllocEngine::allocateReservedLeases6(ClientContext6& ctx,
                                     Lease6Collection& existing_leases) {

    // If there are no reservations or the reservation is v4, there's nothing to do.
    if (ctx.hosts_.empty()) {
        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V6_ALLOC_NO_V6_HR)
            .arg(ctx.query_->getLabel());
        return;
    }

    if (allocateGlobalReservedLeases6(ctx, existing_leases)) {
        // global reservation provided the lease, we're done
        return;
    }

    // Let's convert this from Lease::Type to IPv6Reserv::Type
    IPv6Resrv::Type type = ctx.currentIA().type_ == Lease::TYPE_NA ?
        IPv6Resrv::TYPE_NA : IPv6Resrv::TYPE_PD;

    // We want to avoid allocating new lease for an IA if there is already
    // a valid lease for which client has reservation. So, we first check if
    // we already have a lease for a reserved address or prefix.
    BOOST_FOREACH(const Lease6Ptr& lease, existing_leases) {
        if ((lease->valid_lft_ != 0)) {
            if ((ctx.hosts_.count(lease->subnet_id_) > 0) &&
                ctx.hosts_[lease->subnet_id_]->hasReservation(makeIPv6Resrv(*lease))) {
                // We found existing lease for a reserved address or prefix.
                // We'll simply extend the lifetime of the lease.
                LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                          ALLOC_ENGINE_V6_ALLOC_HR_LEASE_EXISTS)
                    .arg(ctx.query_->getLabel())
                    .arg(lease->typeToText(lease->type_))
                    .arg(lease->addr_.toText());

                // Besides IP reservations we're also going to return other reserved
                // parameters, such as hostname. We want to hand out the hostname value
                // from the same reservation entry as IP addresses. Thus, let's see if
                // there is any hostname reservation.
                if (!ctx.host_subnet_) {
                    SharedNetwork6Ptr network;
                    ctx.subnet_->getSharedNetwork(network);
                    if (network) {
                        // Remember the subnet that holds this preferred host
                        // reservation. The server will use it to return appropriate
                        // FQDN, classes etc.
                        ctx.host_subnet_ = network->getSubnet(lease->subnet_id_);
                        ConstHostPtr host = ctx.hosts_[lease->subnet_id_];
                        // If there is a hostname reservation here we should stick
                        // to this reservation. By updating the hostname in the
                        // context we make sure that the database is updated with
                        // this new value and the server doesn't need to do it and
                        // its processing performance is not impacted by the hostname
                        // updates.
                        if (host && !host->getHostname().empty()) {
                            // We have to determine whether the hostname is generated
                            // in response to client's FQDN or not. If yes, we will
                            // need to qualify the hostname. Otherwise, we just use
                            // the hostname as it is specified for the reservation.
                            OptionPtr fqdn = ctx.query_->getOption(D6O_CLIENT_FQDN);
                            ctx.hostname_ = CfgMgr::instance().getD2ClientMgr().
                                qualifyName(host->getHostname(), static_cast<bool>(fqdn));
                        }
                    }
                }

                // If this is a real allocation, we may need to extend the lease
                // lifetime.
                if (!ctx.fake_allocation_ && conditionalExtendLifetime(*lease)) {
                    LeaseMgrFactory::instance().updateLease6(lease);
                }
                return;
            }
        }
    }

    // There is no lease for a reservation in this IA. So, let's now iterate
    // over reservations specified and try to allocate one of them for the IA.

    Subnet6Ptr subnet = ctx.subnet_;

    while (subnet) {

        SubnetID subnet_id = subnet->getID();

        // No hosts for this subnet or the subnet not supported.
        if (!subnet->clientSupported(ctx.query_->getClasses()) ||
            ctx.hosts_.count(subnet_id) == 0) {
            subnet = subnet->getNextSubnet(ctx.subnet_);
            continue;
        }

        ConstHostPtr host = ctx.hosts_[subnet_id];

        // Get the IPv6 reservations of specified type.
        const IPv6ResrvRange& reservs = host->getIPv6Reservations(type);
        BOOST_FOREACH(IPv6ResrvTuple type_lease_tuple, reservs) {
            // We do have a reservation for address or prefix.
            const IOAddress& addr = type_lease_tuple.second.getPrefix();
            uint8_t prefix_len = type_lease_tuple.second.getPrefixLen();

            // We have allocated this address/prefix while processing one of the
            // previous IAs, so let's try another reservation.
            if (ctx.isAllocated(addr, prefix_len)) {
                continue;
            }

            // If there's a lease for this address, let's not create it.
            // It doesn't matter whether it is for this client or for someone else.
            if (!LeaseMgrFactory::instance().getLease6(ctx.currentIA().type_,
                                                   addr)) {

                // Let's remember the subnet from which the reserved address has been
                // allocated. We'll use this subnet for allocating other reserved
                // resources.
                ctx.subnet_ = subnet;

                if (!ctx.host_subnet_) {
                    ctx.host_subnet_ = subnet;
                    if (!host->getHostname().empty()) {
                        // If there is a hostname reservation here we should stick
                        // to this reservation. By updating the hostname in the
                        // context we make sure that the database is updated with
                        // this new value and the server doesn't need to do it and
                        // its processing performance is not impacted by the hostname
                        // updates.

                        // We have to determine whether the hostname is generated
                        // in response to client's FQDN or not. If yes, we will
                        // need to qualify the hostname. Otherwise, we just use
                        // the hostname as it is specified for the reservation.
                        OptionPtr fqdn = ctx.query_->getOption(D6O_CLIENT_FQDN);
                        ctx.hostname_ = CfgMgr::instance().getD2ClientMgr().
                            qualifyName(host->getHostname(), static_cast<bool>(fqdn));
                    }
                }

                // Ok, let's create a new lease...
                CalloutHandle::CalloutNextStep callout_status = CalloutHandle::NEXT_STEP_CONTINUE;
                Lease6Ptr lease = createLease6(ctx, addr, prefix_len, callout_status);

                // ... and add it to the existing leases list.
                existing_leases.push_back(lease);


                if (ctx.currentIA().type_ == Lease::TYPE_NA) {
                    LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_HR_ADDR_GRANTED)
                        .arg(addr.toText())
                        .arg(ctx.query_->getLabel());
                } else {
                    LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_HR_PREFIX_GRANTED)
                        .arg(addr.toText())
                        .arg(static_cast<int>(prefix_len))
                        .arg(ctx.query_->getLabel());
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

        subnet = subnet->getNextSubnet(ctx.subnet_);
    }
}

bool
AllocEngine::allocateGlobalReservedLeases6(ClientContext6& ctx,
                                           Lease6Collection& existing_leases) {
    // Get the global host
    ConstHostPtr ghost = ctx.globalHost();
    if (!ghost) {
        return (false);
    }

    // We want to avoid allocating a new lease for an IA if there is already
    // a valid lease for which client has reservation. So, we first check if
    // we already have a lease for a reserved address or prefix.
    BOOST_FOREACH(const Lease6Ptr& lease, existing_leases) {
        if ((lease->valid_lft_ != 0) &&
            (ghost->hasReservation(makeIPv6Resrv(*lease)))) {
            // We found existing lease for a reserved address or prefix.
            // We'll simply extend the lifetime of the lease.
            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_ALLOC_HR_LEASE_EXISTS)
                    .arg(ctx.query_->getLabel())
                    .arg(lease->typeToText(lease->type_))
                    .arg(lease->addr_.toText());

            // Besides IP reservations we're also going to return other reserved
            // parameters, such as hostname. We want to hand out the hostname value
            // from the same reservation entry as IP addresses. Thus, let's see if
            // there is any hostname reservation.
            if (!ghost->getHostname().empty()) {
                    // We have to determine whether the hostname is generated
                    // in response to client's FQDN or not. If yes, we will
                    // need to qualify the hostname. Otherwise, we just use
                    // the hostname as it is specified for the reservation.
                    OptionPtr fqdn = ctx.query_->getOption(D6O_CLIENT_FQDN);
                    ctx.hostname_ = CfgMgr::instance().getD2ClientMgr().
                                    qualifyName(ghost->getHostname(), static_cast<bool>(fqdn));
            }

            // If this is a real allocation, we may need to extend the lease
            // lifetime.
            if (!ctx.fake_allocation_ && conditionalExtendLifetime(*lease)) {
                LeaseMgrFactory::instance().updateLease6(lease);
            }

            return(true);
        }
    }

    // There is no lease for a reservation in this IA. So, let's now iterate
    // over reservations specified and try to allocate one of them for the IA.

    // Let's convert this from Lease::Type to IPv6Reserv::Type
    IPv6Resrv::Type type = ctx.currentIA().type_ == Lease::TYPE_NA ?
        IPv6Resrv::TYPE_NA : IPv6Resrv::TYPE_PD;

    const IPv6ResrvRange& reservs = ghost->getIPv6Reservations(type);
    BOOST_FOREACH(IPv6ResrvTuple type_lease_tuple, reservs) {
        // We do have a reservation for address or prefix.
        const IOAddress& addr = type_lease_tuple.second.getPrefix();
        uint8_t prefix_len = type_lease_tuple.second.getPrefixLen();

        // We have allocated this address/prefix while processing one of the
        // previous IAs, so let's try another reservation.
        if (ctx.isAllocated(addr, prefix_len)) {
            continue;
        }

        // If there's a lease for this address, let's not create it.
        // It doesn't matter whether it is for this client or for someone else.
        if (!LeaseMgrFactory::instance().getLease6(ctx.currentIA().type_, addr)) {

            if (!ghost->getHostname().empty()) {
                // If there is a hostname reservation here we should stick
                // to this reservation. By updating the hostname in the
                // context we make sure that the database is updated with
                // this new value and the server doesn't need to do it and
                // its processing performance is not impacted by the hostname
                // updates.

                // We have to determine whether the hostname is generated
                // in response to client's FQDN or not. If yes, we will
                // need to qualify the hostname. Otherwise, we just use
                // the hostname as it is specified for the reservation.
                OptionPtr fqdn = ctx.query_->getOption(D6O_CLIENT_FQDN);
                ctx.hostname_ = CfgMgr::instance().getD2ClientMgr().
                                qualifyName(ghost->getHostname(), static_cast<bool>(fqdn));
            }

            // Ok, let's create a new lease...
            CalloutHandle::CalloutNextStep callout_status = CalloutHandle::NEXT_STEP_CONTINUE;
            Lease6Ptr lease = createLease6(ctx, addr, prefix_len, callout_status);

            // ... and add it to the existing leases list.
            existing_leases.push_back(lease);

            if (ctx.currentIA().type_ == Lease::TYPE_NA) {
                    LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_HR_ADDR_GRANTED)
                        .arg(addr.toText())
                        .arg(ctx.query_->getLabel());
            } else {
                LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_HR_PREFIX_GRANTED)
                        .arg(addr.toText())
                        .arg(static_cast<int>(prefix_len))
                        .arg(ctx.query_->getLabel());
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
            return (true);
        }
    }

    return(false);
}

void
AllocEngine::removeNonmatchingReservedLeases6(ClientContext6& ctx,
                                              Lease6Collection& existing_leases) {
    // If there are no leases (so nothing to remove) just return.
    if (existing_leases.empty() || !ctx.subnet_) {
        return;
    }
    // If host reservation is disabled (so there are no reserved leases)
    // use the simplified version.
    if (ctx.subnet_->getHostReservationMode() == Network::HR_DISABLED) {
        removeNonmatchingReservedNoHostLeases6(ctx, existing_leases);
        return;
    }

    // We need a copy, so we won't be iterating over a container and
    // removing from it at the same time. It's only a copy of pointers,
    // so the operation shouldn't be that expensive.
    Lease6Collection copy = existing_leases;

    BOOST_FOREACH(const Lease6Ptr& candidate, copy) {
        // If we have reservation we should check if the reservation is for
        // the candidate lease. If so, we simply accept the lease.
        IPv6Resrv resv = makeIPv6Resrv(*candidate);
        if ((ctx.hasGlobalReservation(resv)) ||
            ((ctx.hosts_.count(candidate->subnet_id_) > 0) &&
             (ctx.hosts_[candidate->subnet_id_]->hasReservation(resv)))) {
            // We have a subnet reservation
            continue;
        }

        // The candidate address doesn't appear to be reserved for us.
        // We have to make a bit more expensive operation here to retrieve
        // the reservation for the candidate lease and see if it is
        // reserved for someone else.
        ConstHostPtr host = HostMgr::instance().get6(ctx.subnet_->getID(),
                                                     candidate->addr_);
        // If lease is not reserved to someone else, it means that it can
        // be allocated to us from a dynamic pool, but we must check if
        // this lease belongs to any pool. If it does, we can proceed to
        // checking the next lease.
        if (!host && inAllowedPool(ctx, candidate->type_,
                                   candidate->addr_, false)) {
            continue;
        }

        if (host) {
            // Ok, we have a problem. This host has a lease that is reserved
            // for someone else. We need to recover from this.
            if (ctx.currentIA().type_ == Lease::TYPE_NA) {
                LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_REVOKED_ADDR_LEASE)
                    .arg(candidate->addr_.toText()).arg(ctx.duid_->toText())
                    .arg(host->getIdentifierAsText());
            } else {
                LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_REVOKED_PREFIX_LEASE)
                    .arg(candidate->addr_.toText())
                    .arg(static_cast<int>(candidate->prefixlen_))
                    .arg(ctx.duid_->toText())
                    .arg(host->getIdentifierAsText());
            }
        }

        // Remove this lease from LeaseMgr as it is reserved to someone
        // else or doesn't belong to a pool.
        LeaseMgrFactory::instance().deleteLease(candidate->addr_);

        // Update DNS if needed.
        queueNCR(CHG_REMOVE, candidate);

        // Need to decrease statistic for assigned addresses.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", candidate->subnet_id_,
                                   ctx.currentIA().type_ == Lease::TYPE_NA ?
                                   "assigned-nas" : "assigned-pds"),
            static_cast<int64_t>(-1));

        // In principle, we could trigger a hook here, but we will do this
        // only if we get serious complaints from actual users. We want the
        // conflict resolution procedure to really work and user libraries
        // should not interfere with it.

        // Add this to the list of removed leases.
        ctx.currentIA().old_leases_.push_back(candidate);

        // Let's remove this candidate from existing leases
        removeLeases(existing_leases, candidate->addr_);
    }
}

void
AllocEngine::removeNonmatchingReservedNoHostLeases6(ClientContext6& ctx,
                                                    Lease6Collection& existing_leases) {
    // We need a copy, so we won't be iterating over a container and
    // removing from it at the same time. It's only a copy of pointers,
    // so the operation shouldn't be that expensive.
    Lease6Collection copy = existing_leases;

    BOOST_FOREACH(const Lease6Ptr& candidate, copy) {
        // Lease can be allocated to us from a dynamic pool, but we must
        // check if this lease belongs to any allowed pool. If it does,
        // we can proceed to checking the next lease.
        if (inAllowedPool(ctx, candidate->type_,
                          candidate->addr_, false)) {
            continue;
        }

        // Remove this lease from LeaseMgr as it doesn't belong to a pool.
        LeaseMgrFactory::instance().deleteLease(candidate->addr_);

        // Update DNS if needed.
        queueNCR(CHG_REMOVE, candidate);

        // Need to decrease statistic for assigned addresses.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", candidate->subnet_id_,
                                   ctx.currentIA().type_ == Lease::TYPE_NA ?
                                   "assigned-nas" : "assigned-pds"),
            static_cast<int64_t>(-1));

        // Add this to the list of removed leases.
        ctx.currentIA().old_leases_.push_back(candidate);

        // Let's remove this candidate from existing leases
        removeLeases(existing_leases, candidate->addr_);
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
    if (existing_leases.empty()) {
        return;
    }

    // This is the total number of leases. We should not remove the last one.
    int total = existing_leases.size();

    // This is officially not scary code anymore. iterates and marks specified
    // leases for deletion, by setting appropriate pointers to NULL.
    for (Lease6Collection::iterator lease = existing_leases.begin();
         lease != existing_leases.end(); ++lease) {

        // If there is reservation for this keep it.
        IPv6Resrv resv = makeIPv6Resrv(*(*lease));
        if (ctx.hasGlobalReservation(resv) ||
            ((ctx.hosts_.count((*lease)->subnet_id_) > 0) &&
             (ctx.hosts_[(*lease)->subnet_id_]->hasReservation(resv)))) {
            continue;
        }

        // We have reservations, but not for this lease. Release it.
        // Remove this lease from LeaseMgr
        LeaseMgrFactory::instance().deleteLease((*lease)->addr_);

        // Update DNS if required.
        queueNCR(CHG_REMOVE, *lease);

        // Need to decrease statistic for assigned addresses.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", (*lease)->subnet_id_,
                                   ctx.currentIA().type_ == Lease::TYPE_NA ?
                                   "assigned-nas" : "assigned-pds"),
            static_cast<int64_t>(-1));

        /// @todo: Probably trigger a hook here

        // Add this to the list of removed leases.
        ctx.currentIA().old_leases_.push_back(*lease);

        // Set this pointer to NULL. The pointer is still valid. We're just
        // setting the Lease6Ptr to NULL value. We'll remove all NULL
        // pointers once the loop is finished.
        lease->reset();

        if (--total == 1) {
            // If there's only one lease left, break the loop.
            break;
        }

    }

    // Remove all elements that we previously marked for deletion (those that
    // have NULL value).
    existing_leases.erase(std::remove(existing_leases.begin(),
        existing_leases.end(), Lease6Ptr()), existing_leases.end());
}

Lease6Ptr
AllocEngine::reuseExpiredLease(Lease6Ptr& expired, ClientContext6& ctx,
                               uint8_t prefix_len,
                               CalloutHandle::CalloutNextStep& callout_status) {

    if (!expired->expired()) {
        isc_throw(BadValue, "Attempt to recycle lease that is still valid");
    }

    if (expired->type_ != Lease::TYPE_PD) {
        prefix_len = 128; // non-PD lease types must be always /128
    }

    if (!ctx.fake_allocation_) {
        // The expired lease needs to be reclaimed before it can be reused.
        // This includes declined leases for which probation period has
        // elapsed.
        reclaimExpiredLease(expired, ctx.callout_handle_);
    }

    // address, lease type and prefixlen (0) stay the same
    expired->iaid_ = ctx.currentIA().iaid_;
    expired->duid_ = ctx.duid_;
    expired->preferred_lft_ = ctx.subnet_->getPreferred();
    expired->valid_lft_ = ctx.subnet_->getValid();
    expired->t1_ = ctx.subnet_->getT1();
    expired->t2_ = ctx.subnet_->getT2();
    expired->cltt_ = time(NULL);
    expired->subnet_id_ = ctx.subnet_->getID();
    expired->hostname_ = ctx.hostname_;
    expired->fqdn_fwd_ = ctx.fwd_dns_update_;
    expired->fqdn_rev_ = ctx.rev_dns_update_;
    expired->prefixlen_ = prefix_len;
    expired->state_ = Lease::STATE_DEFAULT;

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA,
              ALLOC_ENGINE_V6_REUSE_EXPIRED_LEASE_DATA)
        .arg(ctx.query_->getLabel())
        .arg(expired->toText());

    // Let's execute all callouts registered for lease6_select
    if (ctx.callout_handle_ &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease6_select_)) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(ctx.callout_handle_);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(ctx.query_);

        // Pass necessary arguments

        // Pass the original packet
        ctx.callout_handle_->setArgument("query6", ctx.query_);

        // Subnet from which we do the allocation
        ctx.callout_handle_->setArgument("subnet6", ctx.subnet_);

        // Is this solicit (fake = true) or request (fake = false)
        ctx.callout_handle_->setArgument("fake_allocation", ctx.fake_allocation_);

        // The lease that will be assigned to a client
        ctx.callout_handle_->setArgument("lease6", expired);

        // Call the callouts
        HooksManager::callCallouts(hook_index_lease6_select_, *ctx.callout_handle_);

        callout_status = ctx.callout_handle_->getStatus();

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_status == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_SELECT_SKIP);
            return (Lease6Ptr());
        }

        /// DROP status does not make sense here:
        /// In general as the lease cannot be dropped the DROP action
        /// has no object so SKIP is the right "cancel" status and
        /// DROP should not be a synonym as it introduces ambiguity.

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handed to it.
        ctx.callout_handle_->getArgument("lease6", expired);
    }

    if (!ctx.fake_allocation_) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease6(expired);

        // If the lease is in the current subnet we need to account
        // for the re-assignment of The lease.
        if (ctx.subnet_->inPool(ctx.currentIA().type_, expired->addr_)) {
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", ctx.subnet_->getID(),
                                       ctx.currentIA().type_ == Lease::TYPE_NA ?
                                       "assigned-nas" : "assigned-pds"),
                static_cast<int64_t>(1));
        }
    }

    // We do nothing for SOLICIT. We'll just update database when
    // the client gets back to us with REQUEST message.

    // it's not really expired at this stage anymore - let's return it as
    // an updated lease
    return (expired);
}

Lease6Ptr AllocEngine::createLease6(ClientContext6& ctx,
                                    const IOAddress& addr,
                                    uint8_t prefix_len,
                                    CalloutHandle::CalloutNextStep& callout_status) {

    if (ctx.currentIA().type_ != Lease::TYPE_PD) {
        prefix_len = 128; // non-PD lease types must be always /128
    }

    Lease6Ptr lease(new Lease6(ctx.currentIA().type_, addr, ctx.duid_,
                               ctx.currentIA().iaid_, ctx.subnet_->getPreferred(),
                               ctx.subnet_->getValid(), ctx.subnet_->getT1(),
                               ctx.subnet_->getT2(), ctx.subnet_->getID(),
                               ctx.hwaddr_, prefix_len));

    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hostname_ = ctx.hostname_;

    // Let's execute all callouts registered for lease6_select
    if (ctx.callout_handle_ &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease6_select_)) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(ctx.callout_handle_);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(ctx.query_);

        // Pass necessary arguments

        // Pass the original packet
        ctx.callout_handle_->setArgument("query6", ctx.query_);

        // Subnet from which we do the allocation
        ctx.callout_handle_->setArgument("subnet6", ctx.subnet_);

        // Is this solicit (fake = true) or request (fake = false)
        ctx.callout_handle_->setArgument("fake_allocation", ctx.fake_allocation_);
        ctx.callout_handle_->setArgument("lease6", lease);

        // This is the first callout, so no need to clear any arguments
        HooksManager::callCallouts(hook_index_lease6_select_, *ctx.callout_handle_);

        callout_status = ctx.callout_handle_->getStatus();

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_status == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_SELECT_SKIP);
            return (Lease6Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handed to it.
        ctx.callout_handle_->getArgument("lease6", lease);
    }

    if (!ctx.fake_allocation_) {
        // That is a real (REQUEST) allocation
        bool status = LeaseMgrFactory::instance().addLease(lease);

        if (status) {
            // The lease insertion succeeded - if the lease is in the
            // current subnet lets bump up the statistic.
            if (ctx.subnet_->inPool(ctx.currentIA().type_, addr)) {
                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", ctx.subnet_->getID(),
                                           ctx.currentIA().type_ == Lease::TYPE_NA ?
                                           "assigned-nas" : "assigned-pds"),
                    static_cast<int64_t>(1));
            }

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
                             ctx.currentIA().type_, addr);
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

        // Check if there are any leases for this client.
        Subnet6Ptr subnet = ctx.subnet_;
        Lease6Collection leases;
        while (subnet) {
            Lease6Collection leases_subnet =
                LeaseMgrFactory::instance().getLeases6(ctx.currentIA().type_,
                                                       *ctx.duid_,
                                                       ctx.currentIA().iaid_,
                                                       subnet->getID());
            leases.insert(leases.end(), leases_subnet.begin(), leases_subnet.end());

            subnet = subnet->getNextSubnet(ctx.subnet_);
        }


        if (!leases.empty()) {
            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_RENEW_REMOVE_RESERVED)
                .arg(ctx.query_->getLabel());

            // Check if the existing leases are reserved for someone else.
            // If they're not, we're ok to keep using them.
            removeNonmatchingReservedLeases6(ctx, leases);
        }

        if (!ctx.hosts_.empty()) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_RENEW_HR)
                .arg(ctx.query_->getLabel());

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
        if (leases.empty()) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_EXTEND_ALLOC_UNRESERVED)
                .arg(ctx.query_->getLabel());

            leases = allocateUnreservedLeases6(ctx);
        }

        // Extend all existing leases that passed all checks.
        for (Lease6Collection::iterator l = leases.begin(); l != leases.end(); ++l) {
            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE_DETAIL,
                      ALLOC_ENGINE_V6_EXTEND_LEASE)
                .arg(ctx.query_->getLabel())
                .arg((*l)->typeToText((*l)->type_))
                .arg((*l)->addr_);
            extendLease6(ctx, *l);
        }

        if (!leases.empty()) {
            // If there are any leases allocated, let's store in them in the
            // IA context so as they are available when we process subsequent
            // IAs.
            BOOST_FOREACH(Lease6Ptr lease, leases) {
                ctx.addAllocatedResource(lease->addr_, lease->prefixlen_);
                ctx.new_leases_.push_back(lease);
            }
        }

        return (leases);

    } catch (const isc::Exception& e) {

        // Some other error, return an empty lease.
        LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V6_EXTEND_ERROR)
            .arg(ctx.query_->getLabel())
            .arg(e.what());
    }

    return (Lease6Collection());
}

void
AllocEngine::extendLease6(ClientContext6& ctx, Lease6Ptr lease) {

    if (!lease || !ctx.subnet_) {
        return;
    }

    // It is likely that the lease for which we're extending the lifetime doesn't
    // belong to the current but a sibling subnet.
    if (ctx.subnet_->getID() != lease->subnet_id_) {
        SharedNetwork6Ptr network;
        ctx.subnet_->getSharedNetwork(network);
        if (network) {
            Subnet6Ptr subnet = network->getSubnet(SubnetID(lease->subnet_id_));
            // Found the actual subnet this lease belongs to. Stick to this
            // subnet.
            if (subnet) {
                ctx.subnet_ = subnet;
            }
        }
    }

    // If the lease is not global and it is either out of range (NAs only) or it
    // is not permitted by subnet client classification, delete it.
    if (!(ctx.hasGlobalReservation(makeIPv6Resrv(*lease))) &&
        (((lease->type_ != Lease::TYPE_PD) && !ctx.subnet_->inRange(lease->addr_)) ||
        !ctx.subnet_->clientSupported(ctx.query_->getClasses()))) {
        // Oh dear, the lease is no longer valid. We need to get rid of it.

        // Remove this lease from LeaseMgr
        LeaseMgrFactory::instance().deleteLease(lease->addr_);

        // Updated DNS if required.
        queueNCR(CHG_REMOVE, lease);

        // Need to decrease statistic for assigned addresses.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", ctx.subnet_->getID(), "assigned-nas"),
            static_cast<int64_t>(-1));

        // Add it to the removed leases list.
        ctx.currentIA().old_leases_.push_back(lease);

        return;
    }

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA,
              ALLOC_ENGINE_V6_EXTEND_LEASE_DATA)
        .arg(ctx.query_->getLabel())
        .arg(lease->toText());

    // Keep the old data in case the callout tells us to skip update.
    Lease6Ptr old_data(new Lease6(*lease));

    lease->preferred_lft_ = ctx.subnet_->getPreferred();
    lease->valid_lft_ = ctx.subnet_->getValid();
    lease->t1_ = ctx.subnet_->getT1();
    lease->t2_ = ctx.subnet_->getT2();
    lease->hostname_ = ctx.hostname_;
    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hwaddr_ = ctx.hwaddr_;
    lease->state_ = Lease::STATE_DEFAULT;

    // Extend lease lifetime if it is time to extend it.
    conditionalExtendLifetime(*lease);

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA,
              ALLOC_ENGINE_V6_EXTEND_NEW_LEASE_DATA)
        .arg(ctx.query_->getLabel())
        .arg(lease->toText());

    bool skip = false;
    // Get the callouts specific for the processed message and execute them.
    int hook_point = ctx.query_->getType() == DHCPV6_RENEW ?
        Hooks.hook_index_lease6_renew_ : Hooks.hook_index_lease6_rebind_;
    if (HooksManager::calloutsPresent(hook_point)) {
        CalloutHandlePtr callout_handle = ctx.callout_handle_;

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(ctx.query_);

        // Pass the original packet
        callout_handle->setArgument("query6", ctx.query_);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Pass the IA option to be sent in response
        if (lease->type_ == Lease::TYPE_NA) {
            callout_handle->setArgument("ia_na", ctx.currentIA().ia_rsp_);
        } else {
            callout_handle->setArgument("ia_pd", ctx.currentIA().ia_rsp_);
        }

        // Call all installed callouts
        HooksManager::callCallouts(hook_point, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            skip = true;
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE6_EXTEND_SKIP)
                .arg(ctx.query_->getName());
        }

        /// DROP status does not make sense here.
    }

    if (!skip) {
        // If the lease we're renewing has expired, we need to reclaim this
        // lease before we can renew it.
        if (old_data->expired()) {
            reclaimExpiredLease(old_data, ctx.callout_handle_);

            // If the lease is in the current subnet we need to account
            // for the re-assignment of The lease.
            if (ctx.subnet_->inPool(ctx.currentIA().type_, old_data->addr_)) {
                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", ctx.subnet_->getID(),
                                       ctx.currentIA().type_ == Lease::TYPE_NA ?
                                       "assigned-nas" : "assigned-pds"),
                    static_cast<int64_t>(1));
            }
        } else {
            if (!lease->hasIdenticalFqdn(*old_data)) {
                // We're not reclaiming the lease but since the FQDN has changed
                // we have to at least send NCR.
                queueNCR(CHG_REMOVE, old_data);
            }
        }

        // Now that the lease has been reclaimed, we can go ahead and update it
        // in the lease database.
        LeaseMgrFactory::instance().updateLease6(lease);

    } else {
        // Copy back the original date to the lease. For MySQL it doesn't make
        // much sense, but for memfile, the Lease6Ptr points to the actual lease
        // in memfile, so the actual update is performed when we manipulate
        // fields of returned Lease6Ptr, the actual updateLease6() is no-op.
        *lease = *old_data;
    }

    // Add the old lease to the changed lease list. This allows the server
    // to make decisions regarding DNS updates.
    ctx.currentIA().changed_leases_.push_back(old_data);
}


Lease6Collection
AllocEngine::updateLeaseData(ClientContext6& ctx, const Lease6Collection& leases) {
    Lease6Collection updated_leases;
    bool remove_queued = false;
    for (Lease6Collection::const_iterator lease_it = leases.begin();
         lease_it != leases.end(); ++lease_it) {
        Lease6Ptr lease(new Lease6(**lease_it));
        lease->fqdn_fwd_ = ctx.fwd_dns_update_;
        lease->fqdn_rev_ = ctx.rev_dns_update_;
        lease->hostname_ = ctx.hostname_;
        if (!ctx.fake_allocation_) {

            if (lease->state_ == Lease::STATE_EXPIRED_RECLAIMED) {
                // Transition lease state to default (aka assigned)
                lease->state_ = Lease::STATE_DEFAULT;

                // If the lease is in the current subnet we need to account
                // for the re-assignment of The lease.
                if (inAllowedPool(ctx, ctx.currentIA().type_,
                                  lease->addr_, true)) {
                    StatsMgr::instance().addValue(
                        StatsMgr::generateName("subnet", lease->subnet_id_,
                                               ctx.currentIA().type_ == Lease::TYPE_NA ?
                                               "assigned-nas" : "assigned-pds"),
                        static_cast<int64_t>(1));
                }
            }

            bool fqdn_changed = ((lease->type_ != Lease::TYPE_PD) &&
                                 !(lease->hasIdenticalFqdn(**lease_it)));

            if (conditionalExtendLifetime(*lease) || fqdn_changed) {
                ctx.currentIA().changed_leases_.push_back(*lease_it);
                LeaseMgrFactory::instance().updateLease6(lease);

                // If the FQDN differs, remove existing DNS entries.
                // We only need one remove.
                if (fqdn_changed && !remove_queued) {
                    queueNCR(CHG_REMOVE, *lease_it);
                    remove_queued = true;
                }
            }
        }

        updated_leases.push_back(lease);
    }

    return (updated_leases);
}

void
AllocEngine::reclaimExpiredLeases6(const size_t max_leases, const uint16_t timeout,
                                   const bool remove_lease,
                                   const uint16_t max_unwarned_cycles) {

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V6_LEASES_RECLAMATION_START)
        .arg(max_leases)
        .arg(timeout);

    // Create stopwatch and automatically start it to measure the time
    // taken by the routine.
    util::Stopwatch stopwatch;

    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();

    // This value indicates if we have been able to deal with all expired
    // leases in this pass.
    bool incomplete_reclamation = false;
    Lease6Collection leases;
    // The value of 0 has a special meaning - reclaim all.
    if (max_leases > 0) {
        // If the value is non-zero, the caller has limited the number of
        // leases to reclaim. We obtain one lease more to see if there will
        // be still leases left after this pass.
        lease_mgr.getExpiredLeases6(leases, max_leases + 1);
        // There are more leases expired leases than we will process in this
        // pass, so we should mark it as an incomplete reclamation. We also
        // remove this extra lease (which we don't want to process anyway)
        // from the collection.
        if (leases.size() > max_leases) {
            leases.pop_back();
            incomplete_reclamation = true;
        }

    } else {
        // If there is no limitation on the number of leases to reclaim,
        // we will try to process all. Hence, we don't mark it as incomplete
        // reclamation just yet.
        lease_mgr.getExpiredLeases6(leases, max_leases);
    }

    // Do not initialize the callout handle until we know if there are any
    // lease6_expire callouts installed.
    CalloutHandlePtr callout_handle;
    if (!leases.empty() &&
        HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_lease6_expire_)) {
        callout_handle = HooksManager::createCalloutHandle();
    }

    size_t leases_processed = 0;
    BOOST_FOREACH(Lease6Ptr lease, leases) {

        try {
            // Reclaim the lease.
            reclaimExpiredLease(lease, remove_lease, callout_handle);
            ++leases_processed;

        } catch (const std::exception& ex) {
            LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V6_LEASE_RECLAMATION_FAILED)
                .arg(lease->addr_.toText())
                .arg(ex.what());
        }

        // Check if we have hit the timeout for running reclamation routine and
        // return if we have. We're checking it here, because we always want to
        // allow reclaiming at least one lease.
        if ((timeout > 0) && (stopwatch.getTotalMilliseconds() >= timeout)) {
            // Timeout. This will likely mean that we haven't been able to process
            // all leases we wanted to process. The reclamation pass will be
            // probably marked as incomplete.
            if (!incomplete_reclamation) {
                if (leases_processed < leases.size()) {
                    incomplete_reclamation = true;
                }
            }

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V6_LEASES_RECLAMATION_TIMEOUT)
                .arg(timeout);
            break;
        }
    }

    // Stop measuring the time.
    stopwatch.stop();

    // Mark completion of the lease reclamation routine and present some stats.
    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V6_LEASES_RECLAMATION_COMPLETE)
        .arg(leases_processed)
        .arg(stopwatch.logFormatTotalDuration());

    // Check if this was an incomplete reclamation and increase the number of
    // consecutive incomplete reclamations.
    if (incomplete_reclamation) {
        ++incomplete_v6_reclamations_;
        // If the number of incomplete reclamations is beyond the threshold, we
        // need to issue a warning.
        if ((max_unwarned_cycles > 0) &&
            (incomplete_v6_reclamations_ > max_unwarned_cycles)) {
            LOG_WARN(alloc_engine_logger, ALLOC_ENGINE_V6_LEASES_RECLAMATION_SLOW)
                .arg(max_unwarned_cycles);
            // We issued a warning, so let's now reset the counter.
            incomplete_v6_reclamations_ = 0;
        }

    } else {
        // This was a complete reclamation, so let's reset the counter.
        incomplete_v6_reclamations_ = 0;

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V6_NO_MORE_EXPIRED_LEASES);
    }
}

void
AllocEngine::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE)
        .arg(secs);

    uint64_t deleted_leases = 0;
    try {
        // Try to delete leases from the lease database.
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        deleted_leases = lease_mgr.deleteExpiredReclaimedLeases6(secs);

    } catch (const std::exception& ex) {
        LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_FAILED)
            .arg(ex.what());
    }

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_COMPLETE)
        .arg(deleted_leases);
}


void
AllocEngine::reclaimExpiredLeases4(const size_t max_leases, const uint16_t timeout,
                                   const bool remove_lease,
                                   const uint16_t max_unwarned_cycles) {

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V4_LEASES_RECLAMATION_START)
        .arg(max_leases)
        .arg(timeout);

    // Create stopwatch and automatically start it to measure the time
    // taken by the routine.
    util::Stopwatch stopwatch;

    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();

    // This value indicates if we have been able to deal with all expired
    // leases in this pass.
    bool incomplete_reclamation = false;
    Lease4Collection leases;
    // The value of 0 has a special meaning - reclaim all.
    if (max_leases > 0) {
        // If the value is non-zero, the caller has limited the number of
        // leases to reclaim. We obtain one lease more to see if there will
        // be still leases left after this pass.
        lease_mgr.getExpiredLeases4(leases, max_leases + 1);
        // There are more leases expired leases than we will process in this
        // pass, so we should mark it as an incomplete reclamation. We also
        // remove this extra lease (which we don't want to process anyway)
        // from the collection.
        if (leases.size() > max_leases) {
            leases.pop_back();
            incomplete_reclamation = true;
        }

    } else {
        // If there is no limitation on the number of leases to reclaim,
        // we will try to process all. Hence, we don't mark it as incomplete
        // reclamation just yet.
        lease_mgr.getExpiredLeases4(leases, max_leases);
    }


    // Do not initialize the callout handle until we know if there are any
    // lease4_expire callouts installed.
    CalloutHandlePtr callout_handle;
    if (!leases.empty() &&
        HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_lease4_expire_)) {
        callout_handle = HooksManager::createCalloutHandle();
    }

    size_t leases_processed = 0;
    BOOST_FOREACH(Lease4Ptr lease, leases) {

        try {
            // Reclaim the lease.
            reclaimExpiredLease(lease, remove_lease, callout_handle);
            ++leases_processed;

        } catch (const std::exception& ex) {
            LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V4_LEASE_RECLAMATION_FAILED)
                .arg(lease->addr_.toText())
                .arg(ex.what());
        }

        // Check if we have hit the timeout for running reclamation routine and
        // return if we have. We're checking it here, because we always want to
        // allow reclaiming at least one lease.
        if ((timeout > 0) && (stopwatch.getTotalMilliseconds() >= timeout)) {
            // Timeout. This will likely mean that we haven't been able to process
            // all leases we wanted to process. The reclamation pass will be
            // probably marked as incomplete.
            if (!incomplete_reclamation) {
                if (leases_processed < leases.size()) {
                    incomplete_reclamation = true;
                }
            }

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V4_LEASES_RECLAMATION_TIMEOUT)
                .arg(timeout);
            break;
        }
    }

    // Stop measuring the time.
    stopwatch.stop();

    // Mark completion of the lease reclamation routine and present some stats.
    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V4_LEASES_RECLAMATION_COMPLETE)
        .arg(leases_processed)
        .arg(stopwatch.logFormatTotalDuration());

    // Check if this was an incomplete reclamation and increase the number of
    // consecutive incomplete reclamations.
    if (incomplete_reclamation) {
        ++incomplete_v4_reclamations_;
        // If the number of incomplete reclamations is beyond the threshold, we
        // need to issue a warning.
        if ((max_unwarned_cycles > 0) &&
            (incomplete_v4_reclamations_ > max_unwarned_cycles)) {
            LOG_WARN(alloc_engine_logger, ALLOC_ENGINE_V4_LEASES_RECLAMATION_SLOW)
                .arg(max_unwarned_cycles);
            // We issued a warning, so let's now reset the counter.
            incomplete_v4_reclamations_ = 0;
        }

    } else {
        // This was a complete reclamation, so let's reset the counter.
        incomplete_v4_reclamations_ = 0;

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_NO_MORE_EXPIRED_LEASES);
    }
}

template<typename LeasePtrType>
void
AllocEngine::reclaimExpiredLease(const LeasePtrType& lease, const bool remove_lease,
                                 const CalloutHandlePtr& callout_handle) {
    reclaimExpiredLease(lease, remove_lease ? DB_RECLAIM_REMOVE : DB_RECLAIM_UPDATE,
                        callout_handle);
}

template<typename LeasePtrType>
void
AllocEngine::reclaimExpiredLease(const LeasePtrType& lease,
                                 const CalloutHandlePtr& callout_handle) {
    // This variant of the method is used by the code which allocates or
    // renews leases. It may be the case that the lease has already been
    // reclaimed, so there is nothing to do.
    if (!lease->stateExpiredReclaimed()) {
        reclaimExpiredLease(lease, DB_RECLAIM_LEAVE_UNCHANGED, callout_handle);
    }
}

void
AllocEngine::reclaimExpiredLease(const Lease6Ptr& lease,
                                 const DbReclaimMode& reclaim_mode,
                                 const CalloutHandlePtr& callout_handle) {

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V6_LEASE_RECLAIM)
        .arg(Pkt6::makeLabel(lease->duid_, lease->hwaddr_))
        .arg(lease->addr_.toText())
        .arg(static_cast<int>(lease->prefixlen_));

    // The skip flag indicates if the callouts have taken responsibility
    // for reclaiming the lease. The callout will set this to true if
    // it reclaims the lease itself. In this case the reclamation routine
    // will not update DNS nor update the database.
    bool skipped = false;
    if (callout_handle) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        callout_handle->deleteAllArguments();
        callout_handle->setArgument("lease6", lease);
        callout_handle->setArgument("remove_lease", reclaim_mode == DB_RECLAIM_REMOVE);

        HooksManager::callCallouts(Hooks.hook_index_lease6_expire_,
                                   *callout_handle);

        skipped = callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP;
    }

    /// DROP status does not make sense here.
    /// Not sure if we need to support every possible status everywhere.

    if (!skipped) {

        // Generate removal name change request for D2, if required.
        // This will return immediately if the DNS wasn't updated
        // when the lease was created.
        queueNCR(CHG_REMOVE, lease);

        // Let's check if the lease that just expired is in DECLINED state.
        // If it is, we need to perform a couple extra steps.
        bool remove_lease = (reclaim_mode == DB_RECLAIM_REMOVE);
        if (lease->state_ == Lease::STATE_DECLINED) {
            // Do extra steps required for declined lease reclamation:
            // - call the recover hook
            // - bump decline-related stats
            // - log separate message
            // There's no point in keeping a declined lease after its
            // reclamation. A declined lease doesn't have any client
            // identifying information anymore.  So we'll flag it for
            // removal unless the hook has set the skip flag.
            remove_lease = reclaimDeclined(lease);
        }

        if (reclaim_mode != DB_RECLAIM_LEAVE_UNCHANGED) {
            // Reclaim the lease - depending on the configuration, set the
            // expired-reclaimed state or simply remove it.
            LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
            reclaimLeaseInDatabase<Lease6Ptr>(lease, remove_lease,
                                              boost::bind(&LeaseMgr::updateLease6,
                                                          &lease_mgr, _1));
        }
    }

    // Update statistics.

    // Decrease number of assigned leases.
    if (lease->type_ == Lease::TYPE_NA) {
        // IA_NA
        StatsMgr::instance().addValue(StatsMgr::generateName("subnet",
                                                             lease->subnet_id_,
                                                             "assigned-nas"),
                                      int64_t(-1));

    } else if (lease->type_ == Lease::TYPE_PD) {
        // IA_PD
        StatsMgr::instance().addValue(StatsMgr::generateName("subnet",
                                                             lease->subnet_id_,
                                                             "assigned-pds"),
                                      int64_t(-1));

    }

    // Increase total number of reclaimed leases.
    StatsMgr::instance().addValue("reclaimed-leases", int64_t(1));

    // Increase number of reclaimed leases for a subnet.
    StatsMgr::instance().addValue(StatsMgr::generateName("subnet",
                                                         lease->subnet_id_,
                                                         "reclaimed-leases"),
                                  int64_t(1));
}

void
AllocEngine::reclaimExpiredLease(const Lease4Ptr& lease,
                                 const DbReclaimMode& reclaim_mode,
                                 const CalloutHandlePtr& callout_handle) {

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V4_LEASE_RECLAIM)
        .arg(Pkt4::makeLabel(lease->hwaddr_, lease->client_id_))
        .arg(lease->addr_.toText());

    // The skip flag indicates if the callouts have taken responsibility
    // for reclaiming the lease. The callout will set this to true if
    // it reclaims the lease itself. In this case the reclamation routine
    // will not update DNS nor update the database.
    bool skipped = false;
    if (callout_handle) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        callout_handle->setArgument("lease4", lease);
        callout_handle->setArgument("remove_lease", reclaim_mode == DB_RECLAIM_REMOVE);

        HooksManager::callCallouts(Hooks.hook_index_lease4_expire_,
                                   *callout_handle);

        skipped = callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP;
    }

    /// DROP status does not make sense here.
    /// Not sure if we need to support every possible status everywhere.

    if (!skipped) {

        // Generate removal name change request for D2, if required.
        // This will return immediately if the DNS wasn't updated
        // when the lease was created.
        queueNCR(CHG_REMOVE, lease);

        // Let's check if the lease that just expired is in DECLINED state.
        // If it is, we need to perform a couple extra steps.
        bool remove_lease = (reclaim_mode == DB_RECLAIM_REMOVE);
        if (lease->state_ == Lease::STATE_DECLINED) {
            // Do extra steps required for declined lease reclamation:
            // - call the recover hook
            // - bump decline-related stats
            // - log separate message
            // There's no point in keeping a declined lease after its
            // reclamation. A declined lease doesn't have any client
            // identifying information anymore.  So we'll flag it for
            // removal unless the hook has set the skip flag.
            remove_lease = reclaimDeclined(lease);
        }

        if (reclaim_mode != DB_RECLAIM_LEAVE_UNCHANGED) {
            // Reclaim the lease - depending on the configuration, set the
            // expired-reclaimed state or simply remove it.
            LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
            reclaimLeaseInDatabase<Lease4Ptr>(lease, remove_lease,
                                              boost::bind(&LeaseMgr::updateLease4,
                                                          &lease_mgr, _1));
        }
    }

    // Update statistics.

    // Decrease number of assigned addresses.
    StatsMgr::instance().addValue(StatsMgr::generateName("subnet",
                                                         lease->subnet_id_,
                                                         "assigned-addresses"),
                                  int64_t(-1));

    // Increase total number of reclaimed leases.
    StatsMgr::instance().addValue("reclaimed-leases", int64_t(1));

    // Increase number of reclaimed leases for a subnet.
    StatsMgr::instance().addValue(StatsMgr::generateName("subnet",
                                                         lease->subnet_id_,
                                                         "reclaimed-leases"),
                                  int64_t(1));
}

void
AllocEngine::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE)
        .arg(secs);

    uint64_t deleted_leases = 0;
    try {
        // Try to delete leases from the lease database.
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        deleted_leases = lease_mgr.deleteExpiredReclaimedLeases4(secs);

    } catch (const std::exception& ex) {
        LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_FAILED)
            .arg(ex.what());
    }

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_COMPLETE)
        .arg(deleted_leases);
}

bool
AllocEngine::reclaimDeclined(const Lease4Ptr& lease) {

    if (!lease || (lease->state_ != Lease::STATE_DECLINED) ) {
        return (true);
    }

    if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_lease4_recover_)) {

        // Let's use a static callout handle. It will be initialized the first
        // time lease4_recover is called and will keep to that value.
        static CalloutHandlePtr callout_handle;
        if (!callout_handle) {
            callout_handle = HooksManager::createCalloutHandle();
        }

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass necessary arguments
        callout_handle->setArgument("lease4", lease);

        // Call the callouts
        HooksManager::callCallouts(Hooks.hook_index_lease4_recover_, *callout_handle);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE4_RECOVER_SKIP)
                .arg(lease->addr_.toText());
            return (false);
        }
    }

    LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V4_DECLINED_RECOVERED)
        .arg(lease->addr_.toText())
        .arg(lease->valid_lft_);

    StatsMgr& stats_mgr = StatsMgr::instance();

    // Decrease subnet specific counter for currently declined addresses
    stats_mgr.addValue(StatsMgr::generateName("subnet", lease->subnet_id_,
        "declined-addresses"), static_cast<int64_t>(-1));

    // Decrease global counter for declined addresses
    stats_mgr.addValue("declined-addresses", static_cast<int64_t>(-1));

    stats_mgr.addValue("reclaimed-declined-addresses", static_cast<int64_t>(1));

    stats_mgr.addValue(StatsMgr::generateName("subnet", lease->subnet_id_,
        "reclaimed-declined-addresses"), static_cast<int64_t>(1));

    // Note that we do not touch assigned-addresses counters. Those are
    // modified in whatever code calls this method.
    return (true);
}

bool
AllocEngine::reclaimDeclined(const Lease6Ptr& lease) {

    if (!lease || (lease->state_ != Lease::STATE_DECLINED) ) {
        return (true);
    }

    if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_lease6_recover_)) {

        // Let's use a static callout handle. It will be initialized the first
        // time lease6_recover is called and will keep to that value.
        static CalloutHandlePtr callout_handle;
        if (!callout_handle) {
            callout_handle = HooksManager::createCalloutHandle();
        }

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass necessary arguments
        callout_handle->setArgument("lease6", lease);

        // Call the callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_recover_, *callout_handle);

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE6_RECOVER_SKIP)
                .arg(lease->addr_.toText());
            return (false);
        }
    }

    LOG_INFO(alloc_engine_logger, ALLOC_ENGINE_V6_DECLINED_RECOVERED)
        .arg(lease->addr_.toText())
        .arg(lease->valid_lft_);

    StatsMgr& stats_mgr = StatsMgr::instance();

    // Decrease subnet specific counter for currently declined addresses
    stats_mgr.addValue(StatsMgr::generateName("subnet", lease->subnet_id_,
        "declined-addresses"), static_cast<int64_t>(-1));

    // Decrease global counter for declined addresses
    stats_mgr.addValue("declined-addresses", static_cast<int64_t>(-1));

    stats_mgr.addValue("reclaimed-declined-addresses", static_cast<int64_t>(1));

    stats_mgr.addValue(StatsMgr::generateName("subnet", lease->subnet_id_,
        "reclaimed-declined-addresses"), static_cast<int64_t>(1));

    // Note that we do not touch assigned-addresses counters. Those are
    // modified in whatever code calls this method.

    return (true);
}


template<typename LeasePtrType>
void AllocEngine::reclaimLeaseInDatabase(const LeasePtrType& lease,
                                         const bool remove_lease,
                                         const boost::function<void (const LeasePtrType&)>&
                                         lease_update_fun) const {

    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();

    // Reclaim the lease - depending on the configuration, set the
    // expired-reclaimed state or simply remove it.
    if (remove_lease) {
        lease_mgr.deleteLease(lease->addr_);

    } else if (!lease_update_fun.empty()) {
        // Clear FQDN information as we have already sent the
        // name change request to remove the DNS record.
        lease->hostname_.clear();
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = false;
        lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
        lease_update_fun(lease);

    } else {
        return;
    }

    // Lease has been reclaimed.
    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
              ALLOC_ENGINE_LEASE_RECLAIMED)
        .arg(lease->addr_.toText());
}


} // end of isc::dhcp namespace
} // end of isc namespace

// ##########################################################################
// #    DHCPv4 lease allocation code starts here.
// ##########################################################################

namespace {

/// @brief Check if the specific address is reserved for another client.
///
/// This function finds a host reservation for a given address and then
/// it verifies if the host identifier for this reservation is matching
/// a host identifier found for the current client. If it does not, the
/// address is assumed to be reserved for another client.
///
/// @param address An address for which the function should check if
/// there is a reservation for the different client.
/// @param ctx Client context holding the data extracted from the
/// client's message.
///
/// @return true if the address is reserved for another client.
bool
addressReserved(const IOAddress& address, const AllocEngine::ClientContext4& ctx) {
    if (ctx.subnet_ &&
        ((ctx.subnet_->getHostReservationMode() == Network::HR_ALL) ||
         ((ctx.subnet_->getHostReservationMode() == Network::HR_OUT_OF_POOL) &&
          (!ctx.subnet_->inPool(Lease::TYPE_V4, address))))) {
        ConstHostPtr host = HostMgr::instance().get4(ctx.subnet_->getID(), address);
        if (host) {
            for (auto id = ctx.host_identifiers_.cbegin(); id != ctx.host_identifiers_.cend();
                 ++id) {
                if (id->first == host->getIdentifierType()) {
                    return (id->second != host->getIdentifier());
                }
            }
            return (true);
        }
    }
    return (false);
}

/// @brief Check if the context contains the reservation for the
/// IPv4 address.
///
/// This convenience function checks if the context contains the reservation
/// for the IPv4 address. Note that some reservations may not assign a
/// static IPv4 address to the clients, but may rather reserve a hostname.
/// Allocation engine should check if the existing reservation is made
/// for the IPv4 address and if it is not, allocate the address from the
/// dynamic pool. The allocation engine uses this function to check if
/// the reservation is made for the IPv4 address.
///
/// @param [out] ctx Client context holding the data extracted from the
/// client's message.
///
/// @return true if the context contains the reservation for the IPv4 address.
bool
hasAddressReservation(AllocEngine::ClientContext4& ctx) {
    if (ctx.hosts_.empty()) {
        return (false);
    }

    Subnet4Ptr subnet = ctx.subnet_;
    while (subnet) {
        if (subnet->getHostReservationMode() == Network::HR_GLOBAL) {
            auto host = ctx.hosts_.find(SUBNET_ID_GLOBAL);
            return (host != ctx.hosts_.end() &&
                    !(host->second->getIPv4Reservation().isV4Zero()));
            // if we want global + other modes we would need to
            // return only if true, else continue
        }

        auto host = ctx.hosts_.find(subnet->getID());
        if ((host != ctx.hosts_.end()) &&
            !(host->second->getIPv4Reservation().isV4Zero()) &&
            ((subnet->getHostReservationMode() == Network::HR_ALL) ||
             ((subnet->getHostReservationMode() == Network::HR_OUT_OF_POOL) &&
              (!subnet->inPool(Lease::TYPE_V4, host->second->getIPv4Reservation()))))) {
            ctx.subnet_ = subnet;
            return (true);
        }

        // No address reservation found here, so let's try another subnet
        // within the same shared network.
        subnet = subnet->getNextSubnet(ctx.subnet_, ctx.query_->getClasses());
    }

    return (false);
}

/// @brief Finds existing lease in the database.
///
/// This function searches for the lease in the database which belongs to the
/// client requesting allocation. If the client has supplied the client
/// identifier this identifier is used to look up the lease. If the lease is
/// not found using the client identifier, an additional lookup is performed
/// using the HW address, if supplied. If the lease is found using the HW
/// address, the function also checks if the lease belongs to the client, i.e.
/// there is no conflict between the client identifiers.
///
/// @param [out] ctx Context holding data extracted from the client's message,
/// including the HW address and client identifier. The current subnet may be
/// modified by this function if it belongs to a shared network.
/// @param [out] client_lease A pointer to the lease returned by this function
/// or null value if no has been lease found.
void findClientLease(AllocEngine::ClientContext4& ctx, Lease4Ptr& client_lease) {
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();

    Subnet4Ptr original_subnet = ctx.subnet_;
    Subnet4Ptr subnet = ctx.subnet_;

    // Client identifier is optional. If it is specified, use it to try to find
    // client's lease.
    if (ctx.clientid_) {
        // Get all leases for this client identifier. When shared networks are
        // in use it is more efficient to make a single query rather than
        // multiple queries, one for each subnet.
        Lease4Collection leases_client_id = lease_mgr.getLease4(*ctx.clientid_);

        // Iterate over the subnets within the shared network to see if any client's
        // lease belongs to them.
        while (subnet) {

            // If client identifier has been supplied and the server wasn't
            // explicitly configured to ignore client identifiers for this subnet
            // check if there is a lease within this subnet.
            if (ctx.clientid_ && subnet->getMatchClientId()) {
                for (auto l = leases_client_id.begin(); l != leases_client_id.end(); ++l) {
                    if ((*l)->subnet_id_ == subnet->getID()) {
                        // Lease found, so stick to this lease.
                        client_lease = (*l);
                        ctx.subnet_ = subnet;
                        return;
                    }
                }
            }

            // Haven't found any lease in this subnet, so let's try another subnet
            // within the shared network.
            subnet = subnet->getNextSubnet(original_subnet, ctx.query_->getClasses());
        }
    }

    // If no lease found using the client identifier, try the lookup using
    // the HW address.
    if (!client_lease && ctx.hwaddr_) {

        // Rewind to the first subnet.
        subnet = original_subnet;

        // Get all leases for this HW address.
        Lease4Collection leases_hw_address = lease_mgr.getLease4(*ctx.hwaddr_);

        while (subnet) {
            ClientIdPtr client_id;
            if (subnet->getMatchClientId()) {
                client_id = ctx.clientid_;
            }

            // Try to find the lease that matches current subnet and belongs to
            // this client, so both HW address and client identifier match.
            for (Lease4Collection::const_iterator client_lease_it = leases_hw_address.begin();
                 client_lease_it != leases_hw_address.end(); ++client_lease_it) {
                Lease4Ptr existing_lease = *client_lease_it;
                if ((existing_lease->subnet_id_ == subnet->getID()) &&
                    existing_lease->belongsToClient(ctx.hwaddr_, client_id)) {
                    // Found the lease of this client, so return it.
                    client_lease = existing_lease;
                    // We got a lease but the subnet it belongs to may differ from
                    // the original subnet. Let's now stick to this subnet.
                    ctx.subnet_ = subnet;
                    return;
                }
            }

            // Haven't found any lease in this subnet, so let's try another subnet
            // within the shared network.
            subnet = subnet->getNextSubnet(original_subnet, ctx.query_->getClasses());
        }
    }
}

/// @brief Checks if the specified address belongs to one of the subnets
/// within a shared network.
///
/// @todo Update this function to take client classification into account.
/// @note client classification in pools (vs subnets) is checked
///
/// @param ctx Client context. Current subnet may be modified by this
/// function when it belongs to a shared network.
/// @param address IPv4 address to be checked.
///
/// @return true if address belongs to a pool in a selected subnet or in
/// a pool within any of the subnets belonging to the current shared network.
bool
inAllowedPool(AllocEngine::ClientContext4& ctx, const IOAddress& address) {
    // If the subnet belongs to a shared network we will be iterating
    // over the subnets that belong to this shared network.
    Subnet4Ptr current_subnet = ctx.subnet_;
    while (current_subnet) {

        if (current_subnet->inPool(Lease::TYPE_V4, address,
                                   ctx.query_->getClasses())) {
            // We found a subnet that this address belongs to, so it
            // seems that this subnet is the good candidate for allocation.
            // Let's update the selected subnet.
            ctx.subnet_ = current_subnet;
            return (true);
        }

        current_subnet = current_subnet->getNextSubnet(ctx.subnet_,
                                                       ctx.query_->getClasses());
    }

    return (false);
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

AllocEngine::ClientContext4::ClientContext4()
    : subnet_(), clientid_(), hwaddr_(),
      requested_address_(IOAddress::IPV4_ZERO_ADDRESS()),
      fwd_dns_update_(false), rev_dns_update_(false),
      hostname_(""), callout_handle_(), fake_allocation_(false),
      old_lease_(), new_lease_(), hosts_(), conflicting_lease_(),
      query_(), host_identifiers_() {
}

AllocEngine::ClientContext4::ClientContext4(const Subnet4Ptr& subnet,
                                            const ClientIdPtr& clientid,
                                            const HWAddrPtr& hwaddr,
                                            const asiolink::IOAddress& requested_addr,
                                            const bool fwd_dns_update,
                                            const bool rev_dns_update,
                                            const std::string& hostname,
                                            const bool fake_allocation)
    : subnet_(subnet), clientid_(clientid), hwaddr_(hwaddr),
      requested_address_(requested_addr),
      fwd_dns_update_(fwd_dns_update), rev_dns_update_(rev_dns_update),
      hostname_(hostname), callout_handle_(),
      fake_allocation_(fake_allocation), old_lease_(), new_lease_(),
      hosts_(), host_identifiers_() {

    // Initialize host identifiers.
    if (hwaddr) {
        addHostIdentifier(Host::IDENT_HWADDR, hwaddr->hwaddr_);
    }
}

ConstHostPtr
AllocEngine::ClientContext4::currentHost() const {
    if (subnet_) {
        SubnetID id = (subnet_->getHostReservationMode() == Network::HR_GLOBAL ?
                       SUBNET_ID_GLOBAL : subnet_->getID());

        auto host = hosts_.find(id);
        if (host != hosts_.cend()) {
            return (host->second);
        }
    }
    return (ConstHostPtr());
}

Lease4Ptr
AllocEngine::allocateLease4(ClientContext4& ctx) {
    // The NULL pointer indicates that the old lease didn't exist. It may
    // be later set to non NULL value if existing lease is found in the
    // database.
    ctx.old_lease_.reset();
    ctx.new_lease_.reset();

    // Before we start allocation process, we need to make sure that the
    // selected subnet is allowed for this client. If not, we'll try to
    // use some other subnet within the shared network. If there are no
    // subnets allowed for this client within the shared network, we
    // can't allocate a lease.
    Subnet4Ptr subnet = ctx.subnet_;
    if (subnet && !subnet->clientSupported(ctx.query_->getClasses())) {
        ctx.subnet_ = subnet->getNextSubnet(subnet, ctx.query_->getClasses());
    }

    try {
        if (!ctx.subnet_) {
            isc_throw(BadValue, "Can't allocate IPv4 address without subnet");
        }

        if (!ctx.hwaddr_) {
            isc_throw(BadValue, "HWAddr must be defined");
        }

        if (ctx.fake_allocation_) {
            return (discoverLease4(ctx));

        } else {
            ctx.new_lease_ = requestLease4(ctx);
        }

    } catch (const isc::Exception& e) {
        // Some other error, return an empty lease.
        LOG_ERROR(alloc_engine_logger, ALLOC_ENGINE_V4_ALLOC_ERROR)
            .arg(ctx.query_->getLabel())
            .arg(e.what());
    }

    return (ctx.new_lease_);
}

void
AllocEngine::findReservation(ClientContext4& ctx) {
    ctx.hosts_.clear();

    // If there is no subnet, there is nothing to do.
    if (!ctx.subnet_) {
        return;
    }

    auto subnet = ctx.subnet_;

    std::map<SubnetID, ConstHostPtr> host_map;
    SharedNetwork4Ptr network;
    subnet->getSharedNetwork(network);

    if (subnet->getHostReservationMode() == Network::HR_GLOBAL) {
        ConstHostPtr ghost = findGlobalReservation(ctx);
        if (ghost) {
            ctx.hosts_[SUBNET_ID_GLOBAL] = ghost;

            // @todo In theory, to support global as part of HR_ALL,
            //  we would just keep going, instead of returning.
            return;
        }
    }

    // If the subnet belongs to a shared network it is usually going to be
    // more efficient to make a query for all reservations for a particular
    // client rather than a query for each subnet within this shared network.
    // The only case when it is going to be less efficient is when there are
    // more host identifier types in use than subnets within a shared network.
    // As it breaks RADIUS use of host caching this can be disabled by the
    // host manager.
    const bool use_single_query = network &&
        !HostMgr::instance().getDisableSingleQuery() &&
        (network->getAllSubnets()->size() > ctx.host_identifiers_.size());

    if (use_single_query) {
        for (auto id_pair = ctx.host_identifiers_.begin();
             id_pair != ctx.host_identifiers_.end();
             ++id_pair) {
            ConstHostCollection hosts = HostMgr::instance().getAll(id_pair->first,
                                                                   &id_pair->second[0],
                                                                   id_pair->second.size());
            // Store the hosts in the temporary map, because some hosts may
            // belong to subnets outside of the shared network. We'll need
            // to eliminate them.
            for (auto host = hosts.begin(); host != hosts.end(); ++host) {
                if ((*host)->getIPv4SubnetID() > 0) {
                    host_map[(*host)->getIPv4SubnetID()] = *host;
                }
            }
        }
    }

    // We can only search for the reservation if a subnet has been selected.
    while (subnet) {

        // Only makes sense to get reservations if the client has access
        // to the class.
        if (subnet->clientSupported(ctx.query_->getClasses()) &&
            (subnet->getHostReservationMode() != Network::HR_DISABLED)) {
            // Iterate over configured identifiers in the order of preference
            // and try to use each of them to search for the reservations.
            BOOST_FOREACH(const IdentifierPair& id_pair, ctx.host_identifiers_) {
                if (use_single_query) {
                    if (host_map.count(subnet->getID()) > 0) {
                        ctx.hosts_[subnet->getID()] = host_map[subnet->getID()];
                        break;
                    }

                } else {
                    // Attempt to find a host using a specified identifier.
                    ConstHostPtr host = HostMgr::instance().get4(subnet->getID(),
                                                                 id_pair.first,
                                                                 &id_pair.second[0],
                                                                 id_pair.second.size());
                    // If we found matching host for this subnet.
                    if (host) {
                        ctx.hosts_[subnet->getID()] = host;
                        break;
                    }
                }
            }
        }

        // We need to get to the next subnet if this is a shared network. If it
        // is not (a plain subnet), getNextSubnet will return NULL and we're
        // done here.
        subnet = subnet->getNextSubnet(ctx.subnet_, ctx.query_->getClasses());
    }
}

ConstHostPtr
AllocEngine::findGlobalReservation(ClientContext4& ctx) {
    ConstHostPtr host;
    BOOST_FOREACH(const IdentifierPair& id_pair, ctx.host_identifiers_) {
        // Attempt to find a host using a specified identifier.
        host = HostMgr::instance().get4(SUBNET_ID_GLOBAL, id_pair.first,
                                        &id_pair.second[0], id_pair.second.size());

        // If we found matching global host we're done.
        if (host) {
            break;
        }
    }

    return (host);
}


Lease4Ptr
AllocEngine::discoverLease4(AllocEngine::ClientContext4& ctx) {
    // Find an existing lease for this client. This function will return true
    // if there is a conflict with existing lease and the allocation should
    // not be continued.
    Lease4Ptr client_lease;
    findClientLease(ctx, client_lease);

    // new_lease will hold the pointer to the lease that we will offer to the
    // caller.
    Lease4Ptr new_lease;

    CalloutHandle::CalloutNextStep callout_status = CalloutHandle::NEXT_STEP_CONTINUE;

    // Check if there is a reservation for the client. If there is, we want to
    // assign the reserved address, rather than any other one.
    if (hasAddressReservation(ctx)) {

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_DISCOVER_HR)
            .arg(ctx.query_->getLabel())
            .arg(ctx.currentHost()->getIPv4Reservation().toText());

        // If the client doesn't have a lease or the leased address is different
        // than the reserved one then let's try to allocate the reserved address.
        // Otherwise the address that the client has is the one for which it
        // has a reservation, so just renew it.
        if (!client_lease || (client_lease->addr_ != ctx.currentHost()->getIPv4Reservation())) {
            // The call below will return a pointer to the lease for the address
            // reserved to this client, if the lease is available, i.e. is not
            // currently assigned to any other client.
            // Note that we don't remove the existing client's lease at this point
            // because this is not a real allocation, we just offer what we can
            // allocate in the DHCPREQUEST time.
            new_lease = allocateOrReuseLease4(ctx.currentHost()->getIPv4Reservation(), ctx,
                                              callout_status);
            if (!new_lease) {
                LOG_WARN(alloc_engine_logger, ALLOC_ENGINE_V4_DISCOVER_ADDRESS_CONFLICT)
                    .arg(ctx.query_->getLabel())
                    .arg(ctx.currentHost()->getIPv4Reservation().toText())
                    .arg(ctx.conflicting_lease_ ? ctx.conflicting_lease_->toText() :
                         "(no lease info)");
            }

        } else {
            new_lease = renewLease4(client_lease, ctx);
        }
    }

    // Client does not have a reservation or the allocation of the reserved
    // address has failed, probably because the reserved address is in use
    // by another client. If the client has a lease, we will check if we can
    // offer this lease to the client. The lease can't be offered in the
    // situation when it is reserved for another client or when the address
    // is not in the dynamic pool. The former may be the result of adding the
    // new reservation for the address used by this client. The latter may
    // be due to the client using the reserved out-of-the pool address, for
    // which the reservation has just been removed.
    if (!new_lease && client_lease && inAllowedPool(ctx, client_lease->addr_) &&
        !addressReserved(client_lease->addr_, ctx)) {

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_OFFER_EXISTING_LEASE)
            .arg(ctx.query_->getLabel());

        new_lease = renewLease4(client_lease, ctx);
    }

    // The client doesn't have any lease or the lease can't be offered
    // because it is either reserved for some other client or the
    // address is not in the dynamic pool.
    // Let's use the client's hint (requested IP address), if the client
    // has provided it, and try to offer it. This address must not be
    // reserved for another client, and must be in the range of the
    // dynamic pool.
    if (!new_lease && !ctx.requested_address_.isV4Zero() &&
        inAllowedPool(ctx, ctx.requested_address_) &&
        !addressReserved(ctx.requested_address_, ctx)) {

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_OFFER_REQUESTED_LEASE)
            .arg(ctx.requested_address_.toText())
            .arg(ctx.query_->getLabel());

        new_lease = allocateOrReuseLease4(ctx.requested_address_, ctx,
                                          callout_status);
    }

    // The allocation engine failed to allocate all of the candidate
    // addresses. We will now use the allocator to pick the address
    // from the dynamic pool.
    if (!new_lease) {

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_OFFER_NEW_LEASE)
            .arg(ctx.query_->getLabel());

        new_lease = allocateUnreservedLease4(ctx);
    }

    // Some of the methods like reuseExpiredLease4 may set the old lease to point
    // to the lease which they remove/override. If it is not set, but we have
    // found that the client has the lease the client's lease is the one
    // to return as an old lease.
    if (!ctx.old_lease_ && client_lease) {
        ctx.old_lease_ = client_lease;
    }

    return (new_lease);
}

Lease4Ptr
AllocEngine::requestLease4(AllocEngine::ClientContext4& ctx) {
    // Find an existing lease for this client. This function will return true
    // if there is a conflict with existing lease and the allocation should
    // not be continued.
    Lease4Ptr client_lease;
    findClientLease(ctx, client_lease);

    // Obtain the sole instance of the LeaseMgr.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();

    // When the client sends the DHCPREQUEST, it should always specify the
    // address which it is requesting or renewing. That is, the client should
    // either use the requested IP address option or set the ciaddr. However,
    // we try to be liberal and allow the clients to not specify an address
    // in which case the allocation engine will pick a suitable address
    // for the client.
    if (!ctx.requested_address_.isV4Zero()) {
        // If the client has specified an address, make sure this address
        // is not reserved for another client. If it is, stop here because
        // we can't allocate this address.
        if (addressReserved(ctx.requested_address_, ctx)) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V4_REQUEST_ADDRESS_RESERVED)
                .arg(ctx.query_->getLabel())
                .arg(ctx.requested_address_.toText());

            return (Lease4Ptr());
        }

    } else if (hasAddressReservation(ctx)) {
        // The client hasn't specified an address to allocate, so the
        // allocation engine needs to find an appropriate address.
        // If there is a reservation for the client, let's try to
        // allocate the reserved address.
        ctx.requested_address_ = ctx.currentHost()->getIPv4Reservation();

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_REQUEST_USE_HR)
            .arg(ctx.query_->getLabel())
            .arg(ctx.requested_address_.toText());
    }

    if (!ctx.requested_address_.isV4Zero()) {
        // There is a specific address to be allocated. Let's find out if
        // the address is in use.
        Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(ctx.requested_address_);
        // If the address is in use (allocated and not expired), we check
        // if the address is in use by our client or another client.
        // If it is in use by another client, the address can't be
        // allocated.
        if (existing && !existing->expired() &&
            !existing->belongsToClient(ctx.hwaddr_, ctx.subnet_->getMatchClientId() ?
                                       ctx.clientid_ : ClientIdPtr())) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V4_REQUEST_IN_USE)
                .arg(ctx.query_->getLabel())
                .arg(ctx.requested_address_.toText());

            return (Lease4Ptr());
        }

        // If the client has a reservation but it is requesting a different
        // address it is possible that the client was offered this different
        // address because the reserved address is in use. We will have to
        // check if the address is in use.
        if (hasAddressReservation(ctx) &&
            (ctx.currentHost()->getIPv4Reservation() != ctx.requested_address_)) {
            existing =
                LeaseMgrFactory::instance().getLease4(ctx.currentHost()->getIPv4Reservation());
            // If the reserved address is not in use, i.e. the lease doesn't
            // exist or is expired, and the client is requesting a different
            // address, return NULL. The client should go back to the
            // DHCPDISCOVER and the reserved address will be offered.
            if (!existing || existing->expired()) {

                LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                          ALLOC_ENGINE_V4_REQUEST_INVALID)
                    .arg(ctx.query_->getLabel())
                    .arg(ctx.currentHost()->getIPv4Reservation().toText())
                    .arg(ctx.requested_address_.toText());

                return (Lease4Ptr());
            }
        }

        // The use of the out-of-pool addresses is only allowed when the requested
        // address is reserved for the client. If the address is not reserved one
        // and it doesn't belong to the dynamic pool, do not allocate it.
        if ((!hasAddressReservation(ctx) ||
             (ctx.currentHost()->getIPv4Reservation() != ctx.requested_address_)) &&
            !inAllowedPool(ctx, ctx.requested_address_)) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V4_REQUEST_OUT_OF_POOL)
                .arg(ctx.query_->getLabel())
                .arg(ctx.requested_address_);

            return (Lease4Ptr());
        }
    }

    // We have gone through all the checks, so we can now allocate the address
    // for the client.

    // If the client is requesting an address which is assigned to the client
    // let's just renew this address. Also, renew this address if the client
    // doesn't request any specific address.
    // Added extra checks: the address is reserved or belongs to the dynamic
    // pool for the case the pool class has changed before the request.
    if (client_lease) {
        if (((client_lease->addr_ == ctx.requested_address_) ||
             ctx.requested_address_.isV4Zero()) &&
            (hasAddressReservation(ctx) ||
             inAllowedPool(ctx, client_lease->addr_))) {

            LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                      ALLOC_ENGINE_V4_REQUEST_EXTEND_LEASE)
                .arg(ctx.query_->getLabel())
                .arg(ctx.requested_address_);

            return (renewLease4(client_lease, ctx));
        }
    }

    // new_lease will hold the pointer to the allocated lease if we allocate
    // successfully.
    Lease4Ptr new_lease;

    // The client doesn't have the lease or it is requesting an address
    // which it doesn't have. Let's try to allocate the requested address.
    if (!ctx.requested_address_.isV4Zero()) {

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_REQUEST_ALLOC_REQUESTED)
            .arg(ctx.query_->getLabel())
            .arg(ctx.requested_address_.toText());

        // The call below will return a pointer to the lease allocated
        // for the client if there is no lease for the requested address,
        // or the existing lease has expired. If the allocation fails,
        // e.g. because the lease is in use, we will return NULL to
        // indicate that we were unable to allocate the lease.
        CalloutHandle::CalloutNextStep callout_status = CalloutHandle::NEXT_STEP_CONTINUE;
        new_lease = allocateOrReuseLease4(ctx.requested_address_, ctx,
                                          callout_status);

    } else {

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_REQUEST_PICK_ADDRESS)
            .arg(ctx.query_->getLabel());

        // We will only get here if the client didn't specify which
        // address it wanted to be allocated. The allocation engine will
        // to pick the address from the dynamic pool.
        new_lease = allocateUnreservedLease4(ctx);
    }

    // If we allocated the lease for the client, but the client already had a
    // lease, we will need to return the pointer to the previous lease and
    // the previous lease needs to be removed from the lease database.
    if (new_lease && client_lease) {
        ctx.old_lease_ = Lease4Ptr(new Lease4(*client_lease));

        LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE,
                  ALLOC_ENGINE_V4_REQUEST_REMOVE_LEASE)
            .arg(ctx.query_->getLabel())
            .arg(client_lease->addr_.toText());

        lease_mgr.deleteLease(client_lease->addr_);

        // Need to decrease statistic for assigned addresses.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", client_lease->subnet_id_, "assigned-addresses"),
            static_cast<int64_t>(-1));
    }

    // Return the allocated lease or NULL pointer if allocation was
    // unsuccessful.
    return (new_lease);
}

Lease4Ptr
AllocEngine::createLease4(const ClientContext4& ctx, const IOAddress& addr,
                          CalloutHandle::CalloutNextStep& callout_status) {
    if (!ctx.hwaddr_) {
        isc_throw(BadValue, "Can't create a lease with NULL HW address");
    }
    if (!ctx.subnet_) {
        isc_throw(BadValue, "Can't create a lease without a subnet");
    }

    time_t now = time(NULL);

    // @todo: remove this kludge?
    std::vector<uint8_t> local_copy;
    if (ctx.clientid_ && ctx.subnet_->getMatchClientId()) {
        local_copy = ctx.clientid_->getDuid();
    }
    const uint8_t* local_copy0 = local_copy.empty() ? 0 : &local_copy[0];

    Lease4Ptr lease(new Lease4(addr, ctx.hwaddr_, local_copy0, local_copy.size(),
                               ctx.subnet_->getValid(), ctx.subnet_->getT1(),
                               ctx.subnet_->getT2(),
                               now, ctx.subnet_->getID()));

    // Set FQDN specific lease parameters.
    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hostname_ = ctx.hostname_;

    // Let's execute all callouts registered for lease4_select
    if (ctx.callout_handle_ &&
        HooksManager::getHooksManager().calloutsPresent(hook_index_lease4_select_)) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(ctx.callout_handle_);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(ctx.query_);

        // Pass necessary arguments
        // Pass the original client query
        ctx.callout_handle_->setArgument("query4", ctx.query_);

        // Subnet from which we do the allocation (That's as far as we can go
        // with using SubnetPtr to point to Subnet4 object. Users should not
        // be confused with dynamic_pointer_casts. They should get a concrete
        // pointer (Subnet4Ptr) pointing to a Subnet4 object.
        Subnet4Ptr subnet4 = boost::dynamic_pointer_cast<Subnet4>(ctx.subnet_);
        ctx.callout_handle_->setArgument("subnet4", subnet4);

        // Is this solicit (fake = true) or request (fake = false)
        ctx.callout_handle_->setArgument("fake_allocation", ctx.fake_allocation_);

        // Pass the intended lease as well
        ctx.callout_handle_->setArgument("lease4", lease);

        // This is the first callout, so no need to clear any arguments
        HooksManager::callCallouts(hook_index_lease4_select_, *ctx.callout_handle_);

        callout_status = ctx.callout_handle_->getStatus();

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_status == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS, DHCPSRV_HOOK_LEASE4_SELECT_SKIP);
            return (Lease4Ptr());
        }

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handled to it.
        ctx.callout_handle_->getArgument("lease4", lease);
    }

    if (!ctx.fake_allocation_) {
        // That is a real (REQUEST) allocation
        bool status = LeaseMgrFactory::instance().addLease(lease);
        if (status) {

            // The lease insertion succeeded, let's bump up the statistic.
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", ctx.subnet_->getID(), "assigned-addresses"),
                static_cast<int64_t>(1));

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
    /// @todo: remove this?
    Lease4 old_values = *lease;
    ctx.old_lease_.reset(new Lease4(old_values));

    // Update the lease with the information from the context.
    updateLease4Information(lease, ctx);

    if (!ctx.fake_allocation_) {
        // If the lease is expired we have to reclaim it before
        // re-assigning it to the client. The lease reclamation
        // involves execution of hooks and DNS update.
        if (ctx.old_lease_->expired()) {
            reclaimExpiredLease(ctx.old_lease_, ctx.callout_handle_);

        }

        lease->state_ = Lease::STATE_DEFAULT;
    }

    bool skip = false;
    // Execute all callouts registered for lease4_renew.
    if (HooksManager::getHooksManager().
        calloutsPresent(Hooks.hook_index_lease4_renew_)) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(ctx.callout_handle_);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(ctx.query_);

        // Subnet from which we do the allocation. Convert the general subnet
        // pointer to a pointer to a Subnet4.  Note that because we are using
        // boost smart pointers here, we need to do the cast using the boost
        // version of dynamic_pointer_cast.
        Subnet4Ptr subnet4 = boost::dynamic_pointer_cast<Subnet4>(ctx.subnet_);

        // Pass the parameters. Note the clientid is passed only if match-client-id
        // is set. This is done that way, because the lease4-renew hook point is
        // about renewing a lease and the configuration parameter says the
        // client-id should be ignored. Hence no clientid value if match-client-id
        // is false.
        ctx.callout_handle_->setArgument("query4", ctx.query_);
        ctx.callout_handle_->setArgument("subnet4", subnet4);
        ctx.callout_handle_->setArgument("clientid", subnet4->getMatchClientId() ?
                                         ctx.clientid_ : ClientIdPtr());
        ctx.callout_handle_->setArgument("hwaddr", ctx.hwaddr_);

        // Pass the lease to be updated
        ctx.callout_handle_->setArgument("lease4", lease);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease4_renew_,
                                   *ctx.callout_handle_);

        // Callouts decided to skip the next processing step. The next
        // processing step would actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        if (ctx.callout_handle_->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            skip = true;
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE4_RENEW_SKIP);
        }

        /// DROP status does not make sense here.
    }

    if (!ctx.fake_allocation_ && !skip) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease4(lease);

        // We need to account for the re-assignment of The lease.
        if (ctx.old_lease_->expired() || ctx.old_lease_->state_ == Lease::STATE_EXPIRED_RECLAIMED) {
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", ctx.subnet_->getID(), "assigned-addresses"),
                static_cast<int64_t>(1));
        }
    }
    if (skip) {
        // Rollback changes (really useful only for memfile)
        /// @todo: remove this?
        *lease = old_values;
    }

    return (lease);
}

Lease4Ptr
AllocEngine::reuseExpiredLease4(Lease4Ptr& expired,
                                AllocEngine::ClientContext4& ctx,
                                CalloutHandle::CalloutNextStep& callout_status) {
    if (!expired) {
        isc_throw(BadValue, "null lease specified for reuseExpiredLease");
    }

    if (!ctx.subnet_) {
        isc_throw(BadValue, "null subnet specified for the reuseExpiredLease");
    }

    if (!ctx.fake_allocation_) {
        // The expired lease needs to be reclaimed before it can be reused.
        // This includes declined leases for which probation period has
        // elapsed.
        reclaimExpiredLease(expired, ctx.callout_handle_);
        expired->state_ = Lease::STATE_DEFAULT;
    }

    updateLease4Information(expired, ctx);

    LOG_DEBUG(alloc_engine_logger, ALLOC_ENGINE_DBG_TRACE_DETAIL_DATA,
              ALLOC_ENGINE_V4_REUSE_EXPIRED_LEASE_DATA)
        .arg(ctx.query_->getLabel())
        .arg(expired->toText());

    // Let's execute all callouts registered for lease4_select
    if (ctx.callout_handle_ &&  HooksManager::getHooksManager()
        .calloutsPresent(hook_index_lease4_select_)) {

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(ctx.query_);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(ctx.callout_handle_);

        // Pass necessary arguments
        // Pass the original client query
        ctx.callout_handle_->setArgument("query4", ctx.query_);

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

        callout_status = ctx.callout_handle_->getStatus();

        // Callouts decided to skip the action. This means that the lease is not
        // assigned, so the client will get NoAddrAvail as a result. The lease
        // won't be inserted into the database.
        if (callout_status == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_HOOKS,
                      DHCPSRV_HOOK_LEASE4_SELECT_SKIP);
            return (Lease4Ptr());
        }

        /// DROP status does not make sense here.

        // Let's use whatever callout returned. Hopefully it is the same lease
        // we handed to it.
        ctx.callout_handle_->getArgument("lease4", expired);
    }

    if (!ctx.fake_allocation_) {
        // for REQUEST we do update the lease
        LeaseMgrFactory::instance().updateLease4(expired);

        // We need to account for the re-assignment of The lease.
        StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", ctx.subnet_->getID(), "assigned-addresses"),
                static_cast<int64_t>(1));
    }

    // We do nothing for SOLICIT. We'll just update database when
    // the client gets back to us with REQUEST message.

    // it's not really expired at this stage anymore - let's return it as
    // an updated lease
    return (expired);
}

Lease4Ptr
AllocEngine::allocateOrReuseLease4(const IOAddress& candidate, ClientContext4& ctx,
                                   CalloutHandle::CalloutNextStep& callout_status) {
    ctx.conflicting_lease_.reset();

    Lease4Ptr exist_lease = LeaseMgrFactory::instance().getLease4(candidate);
    if (exist_lease) {
        if (exist_lease->expired()) {
            ctx.old_lease_ = Lease4Ptr(new Lease4(*exist_lease));
            return (reuseExpiredLease4(exist_lease, ctx, callout_status));

        } else {
            // If there is a lease and it is not expired, pass this lease back
            // to the caller in the context. The caller may need to know
            // which lease we're conflicting with.
            ctx.conflicting_lease_ = exist_lease;
        }

    } else {
        return (createLease4(ctx, candidate, callout_status));
    }
    return (Lease4Ptr());
}

Lease4Ptr
AllocEngine::allocateUnreservedLease4(ClientContext4& ctx) {
    Lease4Ptr new_lease;
    AllocatorPtr allocator = getAllocator(Lease::TYPE_V4);
    Subnet4Ptr subnet = ctx.subnet_;

    // Need to check if the subnet belongs to a shared network. If so,
    // we might be able to find a better subnet for lease allocation,
    // for which it is more likely that there are some leases available.
    // If we stick to the selected subnet, we may end up walking over
    // the entire subnet (or more subnets) to discover that the address
    // pools have been exhausted. Using a subnet from which an address
    // was assigned most recently is an optimization which increases
    // the likelihood of starting from the subnet which address pools
    // are not exhausted.
    SharedNetwork4Ptr network;
    ctx.subnet_->getSharedNetwork(network);
    if (network) {
        // This would try to find a subnet with the same set of classes
        // as the current subnet, but with the more recent "usage timestamp".
        // This timestamp is only updated for the allocations made with an
        // allocator (unreserved lease allocations), not the static
        // allocations or requested addresses.
        ctx.subnet_ = subnet = network->getPreferredSubnet(ctx.subnet_);
    }

    Subnet4Ptr original_subnet = subnet;

    uint64_t total_attempts = 0;
    while (subnet) {

        ClientIdPtr client_id;
        if (subnet->getMatchClientId()) {
            client_id = ctx.clientid_;
        }

        uint64_t possible_attempts =
            subnet->getPoolCapacity(Lease::TYPE_V4,
                                    ctx.query_->getClasses());
        uint64_t max_attempts = (attempts_ > 0 ? attempts_ : possible_attempts);
        // Skip trying if there is no chance to get something
        if (possible_attempts == 0) {
            max_attempts = 0;
        }

        CalloutHandle::CalloutNextStep callout_status = CalloutHandle::NEXT_STEP_CONTINUE;

        for (uint64_t i = 0; i < max_attempts; ++i) {
            IOAddress candidate = allocator->pickAddress(subnet,
                                                         ctx.query_->getClasses(),
                                                         client_id,
                                                         ctx.requested_address_);
            // If address is not reserved for another client, try to allocate it.
            if (!addressReserved(candidate, ctx)) {

                // The call below will return the non-NULL pointer if we
                // successfully allocate this lease. This means that the
                // address is not in use by another client.
                new_lease = allocateOrReuseLease4(candidate, ctx, callout_status);
                if (new_lease) {
                    return (new_lease);

                } else if (ctx.callout_handle_ &&
                           (callout_status != CalloutHandle::NEXT_STEP_CONTINUE)) {
                    // Don't retry when the callout status is not continue.
                    subnet.reset();
                    break;
                }
            }
            ++total_attempts;
        }

        // This pointer may be set to NULL if hooks set SKIP status.
        if (subnet) {
            subnet = subnet->getNextSubnet(original_subnet, ctx.query_->getClasses());

            if (subnet) {
                ctx.subnet_ = subnet;
            }
        }
    }

    // Unable to allocate an address, return an empty lease.
    LOG_WARN(alloc_engine_logger, ALLOC_ENGINE_V4_ALLOC_FAIL)
        .arg(ctx.query_->getLabel())
        .arg(total_attempts);

    return (new_lease);
}

void
AllocEngine::updateLease4Information(const Lease4Ptr& lease,
                                     AllocEngine::ClientContext4& ctx) const {
    lease->subnet_id_ = ctx.subnet_->getID();
    lease->hwaddr_ = ctx.hwaddr_;
    lease->client_id_ = ctx.subnet_->getMatchClientId() ? ctx.clientid_ : ClientIdPtr();
    lease->cltt_ = time(NULL);
    lease->t1_ = ctx.subnet_->getT1();
    lease->t2_ = ctx.subnet_->getT2();
    lease->valid_lft_ = ctx.subnet_->getValid();
    lease->fqdn_fwd_ = ctx.fwd_dns_update_;
    lease->fqdn_rev_ = ctx.rev_dns_update_;
    lease->hostname_ = ctx.hostname_;
}

bool
AllocEngine::conditionalExtendLifetime(Lease& lease) const {
    lease.cltt_ = time(NULL);
    return (true);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
