// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/iterative_allocator.h>
#include <sflqtest_lease_mgr.h>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace dhcp {
namespace test {

SflqPool::SflqPool(asiolink::IOAddress start_address,
                   asiolink::IOAddress end_address,
                   SubnetID subnet_id,
                   Lease::Type lease_type /* = Lease::TYPE_V4 */,
                   uint8_t delegated_len /* = 1 */)
    : start_address_(start_address), end_address_(end_address),
      subnet_id_(subnet_id), lease_type_(lease_type),
      delegated_len_(delegated_len) {
    repopulateFreeLeases();
}

IOAddress
SflqPool::zeroAddress() {
    if (lease_type_ == Lease::TYPE_V4) {
        return (IOAddress::IPV4_ZERO_ADDRESS());
    }

    return (IOAddress::IPV6_ZERO_ADDRESS());
}

void
SflqPool::repopulateFreeLeases() {
    // Populate list of free leases with all addresses in
    // the pool.  For purposes of testing the SharedFlqAllocator
    // class we don't care about actual leases.
    IOAddress next_address = start_address_;
    free_addresses_.clear();
    while (next_address <= end_address_) {
        free_addresses_.push_back(next_address);
        next_address = IterativeAllocator::increaseAddress(next_address,
                                                           (lease_type_ == Lease::TYPE_PD),
                                                           delegated_len_);
    }
}

IOAddress
SflqPool::popFreeAddress() {
    if (free_addresses_.empty()) {
        return (zeroAddress());
    }

    IOAddress free_address = free_addresses_.front();
    free_addresses_.pop_front();
    return (free_address);
}

SflqPoolInfoPtr
SflqPool::toSflqPoolInfo() const {
    SflqPoolInfoPtr pi(new SflqPoolInfo());
    pi->lease_type_ = lease_type_;
    pi->start_address_ = start_address_;
    pi->end_address_ = end_address_;
    pi->delegated_len_ = delegated_len_;
    pi->subnet_id_ = subnet_id_;
    pi->free_leases_ = free_addresses_.size();;
    pi->created_ts_ = boost::posix_time::second_clock::local_time();
    pi->modified_ts_ = pi->created_ts_;
    return (pi);
}

TrackingLeaseMgrPtr
SflqTestLeaseMgr::factory(const DatabaseConnection::ParameterMap& params) {
    return (TrackingLeaseMgrPtr(new SflqTestLeaseMgr(params)));
}

SflqTestLeaseMgr::SflqTestLeaseMgr(const DatabaseConnection::ParameterMap& params)
    : ConcreteLeaseMgr(params) {
}

SflqTestLeaseMgr::~SflqTestLeaseMgr() {
}

bool
SflqTestLeaseMgr::sflqCreateFlqPool4(IOAddress start_address, IOAddress end_address,
                                     SubnetID subnet_id, bool recreate) {
    auto sflq_pool = findPool(start_address, end_address);
    if (sflq_pool) {
        if (recreate) {
            sflq_pool->repopulateFreeLeases();
            return (true);
        }

        return (false);
    }

    // Create the pool and add it to the list of pools.
    sflq_pool.reset(new SflqPool(start_address, end_address, subnet_id));
    sflq_pools_.push_back(sflq_pool);
    return(true);
}

IOAddress
SflqTestLeaseMgr::sflqPickFreeLease4(IOAddress start_address, IOAddress end_address) {
    auto sflq_pool = findPool(start_address, end_address);
    if (!sflq_pool) {
        return (IOAddress::IPV4_ZERO_ADDRESS());
    }

    return (sflq_pool->popFreeAddress());
}

bool
SflqTestLeaseMgr::sflqCreateFlqPool6(IOAddress start_address, IOAddress end_address,
                                     Lease::Type lease_type, uint8_t delegated_len,
                                     SubnetID subnet_id, bool recreate) {
    auto sflq_pool = findPool(start_address, end_address);
    if (sflq_pool) {
        if (recreate) {
            sflq_pool->repopulateFreeLeases();
            return (true);
        }

        return (false);
    }

    // Create the pool and add it to the list of pools.
    sflq_pool.reset(new SflqPool(start_address, end_address, subnet_id,
                                 lease_type, delegated_len));
    sflq_pools_.push_back(sflq_pool);
    return(true);
}

IOAddress
SflqTestLeaseMgr::sflqPickFreeLease6(IOAddress start_address, IOAddress end_address) {
    auto sflq_pool = findPool(start_address, end_address);
    if (!sflq_pool) {
        return (IOAddress::IPV6_ZERO_ADDRESS());
    }

    return (sflq_pool->popFreeAddress());
}

SflqPoolPtr
SflqTestLeaseMgr::findPool(IOAddress start_address, IOAddress end_address) {
    for (auto pool : sflq_pools_) {
        if (pool->start_address_ == start_address &&
            pool->end_address_ == end_address) {
            return (pool);
        }
    }

    return (SflqPoolPtr());
}

void
SflqTestLeaseMgr::repopulateFlqPools() {
    for (auto pool : sflq_pools_) {
        pool->repopulateFreeLeases();
    }
}

std::string
SflqTestLeaseMgr::getType() const {
    return (std::string("sflqtest"));
}

SflqPoolInfoCollectionPtr
SflqTestLeaseMgr::sflqPool4GetAll() {
    SflqPoolInfoCollectionPtr pools(new SflqPoolInfoCollection());
    for (auto pool : sflq_pools_) {
        pools->push_back(pool->toSflqPoolInfo());
    }

    return (pools);
}

SflqPoolInfoCollectionPtr
SflqTestLeaseMgr::sflqPool4Get(SubnetID subnet_id) {
    SflqPoolInfoCollectionPtr pools(new SflqPoolInfoCollection());
    for (auto pool : sflq_pools_) {
        if (pool->subnet_id_ == subnet_id) {
            pools->push_back(pool->toSflqPoolInfo());
        }
    }

    return (pools);
}

SflqPoolInfoCollectionPtr
SflqTestLeaseMgr::sflqPool4Get(IOAddress start_address, IOAddress end_address) {
    SflqPoolInfoCollectionPtr pools(new SflqPoolInfoCollection());
    for (auto pool : sflq_pools_) {
        if ((pool->start_address_ <= start_address && start_address <= pool->end_address_) ||
            (pool->start_address_ <= end_address && end_address <= pool->end_address_) ||
            (start_address < pool->start_address_ && pool->end_address_ < end_address))
            pools->push_back(pool->toSflqPoolInfo());
    }

    return (pools);
}

bool
SflqTestLeaseMgr::sflqPool4Del(IOAddress start_address, IOAddress end_address,
                               bool force /* = false */) {
    return(sflqPoolDel(start_address, end_address, force));
}

SflqPoolInfoCollectionPtr
SflqTestLeaseMgr::sflqPool6GetAll() {
    SflqPoolInfoCollectionPtr pools(new SflqPoolInfoCollection());
    for (auto pool : sflq_pools_) {
        pools->push_back(pool->toSflqPoolInfo());
    }

    return (pools);
}

SflqPoolInfoCollectionPtr
SflqTestLeaseMgr::sflqPool6Get(SubnetID subnet_id) {
    SflqPoolInfoCollectionPtr pools(new SflqPoolInfoCollection());
    for (auto pool : sflq_pools_) {
        if (pool->subnet_id_ == subnet_id) {
            pools->push_back(pool->toSflqPoolInfo());
        }
    }

    return (pools);
}

SflqPoolInfoCollectionPtr
SflqTestLeaseMgr::sflqPool6Get(IOAddress start_address, IOAddress end_address) {
    SflqPoolInfoCollectionPtr pools(new SflqPoolInfoCollection());
    for (auto pool : sflq_pools_) {
        if ((pool->start_address_ <= start_address && start_address <= pool->end_address_) ||
            (pool->start_address_ <= end_address && end_address <= pool->end_address_) ||
            (start_address < pool->start_address_ && pool->end_address_ < end_address))
            pools->push_back(pool->toSflqPoolInfo());
    }

    return (pools);
}

bool
SflqTestLeaseMgr::sflqPool6Del(IOAddress start_address, IOAddress end_address,
                               bool force /* = false */) {
    return(sflqPoolDel(start_address, end_address, force));
}

bool
SflqTestLeaseMgr::sflqPoolDel(IOAddress start_address, IOAddress end_address,
                              bool force) {
    auto pools = sflqPool6Get(start_address, end_address);
    if (pools->size() == 0) {
        return (false);
    }

    if (pools->size() > 1 && force == false) {
        // Overlapping pools, warn and bail.
        isc_throw(InvalidOperation, "Delete would affect "
                  << pools->size() << " overlapping pools");
    }

    auto pool = sflq_pools_.begin();
    while (pool != sflq_pools_.end()) {
        if ((*pool)->start_address_ == start_address &&
            (*pool)->end_address_ == end_address) {
            sflq_pools_.erase(pool);
            return (true);
        }
    }

    return (false);
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
