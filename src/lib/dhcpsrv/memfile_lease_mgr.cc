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

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <exceptions/exceptions.h>

#include <iostream>

using namespace isc::dhcp;

Memfile_LeaseMgr::Memfile_LeaseMgr(const ParameterMap& parameters)
    : LeaseMgr(parameters) {
    LOG_WARN(dhcpsrv_logger, DHCPSRV_MEMFILE_WARNING);
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
}

bool
Memfile_LeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ADD_ADDR4).arg(lease->addr_.toText());

    if (getLease4(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }
    storage4_.insert(lease);
    return (true);
}

bool
Memfile_LeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ADD_ADDR6).arg(lease->addr_.toText());

    if (getLease6(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }
    storage6_.insert(lease);
    return (true);
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_ADDR4).arg(addr.toText());

    typedef Lease4Storage::nth_index<0>::type SearchIndex;
    const SearchIndex& idx = storage4_.get<0>();
    Lease4Storage::iterator l = idx.find(addr);
    if (l == storage4_.end()) {
        return (Lease4Ptr());
    } else {
        return (Lease4Ptr(new Lease4(**l)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_HWADDR).arg(hwaddr.toText());
    typedef Lease4Storage::nth_index<0>::type SearchIndex;
    Lease4Collection collection;
    const SearchIndex& idx = storage4_.get<0>();
    for(SearchIndex::const_iterator lease = idx.begin();
        lease != idx.end(); ++lease) {

        // Every Lease4 has a hardware address, so we can compare it
        if((* lease)->hwaddr_ == hwaddr.hwaddr_) {
            collection.push_back((* lease));
        }
    }

    return (collection);
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_SUBID_HWADDR).arg(subnet_id)
        .arg(hwaddr.toText());

    // We are going to use index #1 of the multi index container.
    // We define SearchIndex locally in this function because
    // currently only this function uses this index.
    typedef Lease4Storage::nth_index<1>::type SearchIndex;
    // Get the index.
    const SearchIndex& idx = storage4_.get<1>();
    // Try to find the lease using HWAddr and subnet id.
    SearchIndex::const_iterator lease =
        idx.find(boost::make_tuple(hwaddr.hwaddr_, subnet_id));
    // Lease was not found. Return empty pointer to the caller.
    if (lease == idx.end()) {
        return (Lease4Ptr());
    }

    // Lease was found. Return it to the caller.
    return (Lease4Ptr(new Lease4(**lease)));
}

Lease4Collection
Memfile_LeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_CLIENTID).arg(clientid.toText());
    typedef Memfile_LeaseMgr::Lease4Storage::nth_index<0>::type SearchIndex;
    Lease4Collection collection;
    const SearchIndex& idx = storage4_.get<0>();
    for(SearchIndex::const_iterator lease = idx.begin();
        lease != idx.end(); ++ lease) {

        // client-id is not mandatory in DHCPv4. There can be a lease that does
        // not have a client-id. Dereferencing null pointer would be a bad thing
        if((*lease)->client_id_ && *(*lease)->client_id_ == clientid) {
            collection.push_back((* lease));
        }
    }

    return (collection);
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const ClientId& client_id,
                            const HWAddr& hwaddr,
                            SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_CLIENTID_HWADDR_SUBID).arg(client_id.toText())
                                                        .arg(hwaddr.toText())
                                                        .arg(subnet_id);

    // We are going to use index #3 of the multi index container.
    // We define SearchIndex locally in this function because
    // currently only this function uses this index.
    typedef Lease4Storage::nth_index<3>::type SearchIndex;
    // Get the index.
    const SearchIndex& idx = storage4_.get<3>();
    // Try to get the lease using client id, hardware address and subnet id.
    SearchIndex::const_iterator lease =
        idx.find(boost::make_tuple(client_id.getClientId(), hwaddr.hwaddr_,
                                   subnet_id));

    if (lease == idx.end()) {
        // Lease was not found. Return empty pointer to the caller.
        return (Lease4Ptr());
    }

    // Lease was found. Return it to the caller.
    return (*lease);
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const ClientId& client_id,
                            SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_SUBID_CLIENTID).arg(subnet_id)
              .arg(client_id.toText());

    // We are going to use index #2 of the multi index container.
    // We define SearchIndex locally in this function because
    // currently only this function uses this index.
    typedef Lease4Storage::nth_index<2>::type SearchIndex;
    // Get the index.
    const SearchIndex& idx = storage4_.get<2>();
    // Try to get the lease using client id and subnet id.
    SearchIndex::const_iterator lease =
        idx.find(boost::make_tuple(client_id.getClientId(), subnet_id));
    // Lease was not found. Return empty pointer to the caller.
    if (lease == idx.end()) {
        return (Lease4Ptr());
    }
    // Lease was found. Return it to the caller.
    return (Lease4Ptr(new Lease4(**lease)));
}

Lease6Ptr
Memfile_LeaseMgr::getLease6(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_ADDR6).arg(addr.toText());

    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end()) {
        return (Lease6Ptr());
    } else {
        return (Lease6Ptr(new Lease6(**l)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLease6(const DUID& duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_IAID_DUID).arg(iaid).arg(duid.toText());

    return (Lease6Collection());
}

Lease6Ptr
Memfile_LeaseMgr::getLease6(const DUID& duid, uint32_t iaid,
                            SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_IAID_SUBID_DUID)
              .arg(iaid).arg(subnet_id).arg(duid.toText());

    // We are going to use index #1 of the multi index container.
    // We define SearchIndex locally in this function because
    // currently only this function uses this index.
    typedef Lease6Storage::nth_index<1>::type SearchIndex;
    // Get the index.
    const SearchIndex& idx = storage6_.get<1>();
    // Try to get the lease using the DUID, IAID and Subnet ID.
    SearchIndex::const_iterator lease =
        idx.find(boost::make_tuple(duid.getDuid(), iaid, subnet_id));
    // Lease was not found. Return empty pointer.
    if (lease == idx.end()) {
        return (Lease6Ptr());
    }
    // Lease was found, return it to the caller.
    return (Lease6Ptr(new Lease6(**lease)));
}

void
Memfile_LeaseMgr::updateLease4(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR4).arg(lease->addr_.toText());

    Lease4Storage::iterator lease_it = storage4_.find(lease->addr_);
    if (lease_it == storage4_.end()) {
        isc_throw(NoSuchLease, "failed to update the lease with address "
                  << lease->addr_.toText() << " - no such lease");
    }
    **lease_it = *lease;
}

void
Memfile_LeaseMgr::updateLease6(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR6).arg(lease->addr_.toText());

    Lease6Storage::iterator lease_it = storage6_.find(lease->addr_);
    if (lease_it == storage6_.end()) {
        isc_throw(NoSuchLease, "failed to update the lease with address "
                  << lease->addr_.toText() << " - no such lease");
    }
    **lease_it = *lease;
}

bool
Memfile_LeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_ADDR).arg(addr.toText());
    if (addr.isV4()) {
        // v4 lease
        Lease4Storage::iterator l = storage4_.find(addr);
        if (l == storage4_.end()) {
            // No such lease
            return (false);
        } else {
            storage4_.erase(l);
            return (true);
        }

    } else {
        // v6 lease
        Lease6Storage::iterator l = storage6_.find(addr);
        if (l == storage6_.end()) {
            // No such lease
            return (false);
        } else {
            storage6_.erase(l);
            return (true);
        }
    }
}

std::string
Memfile_LeaseMgr::getDescription() const {
    return (std::string("This is a dummy memfile backend implementation.\n"
                        "It does not offer any useful lease management and its only\n"
                        "purpose is to test abstract lease manager API."));
}

void
Memfile_LeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_COMMIT);
}

void
Memfile_LeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ROLLBACK);
}
