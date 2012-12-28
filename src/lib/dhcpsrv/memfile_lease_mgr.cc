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

#include <dhcpsrv/memfile_lease_mgr.h>
#include <exceptions/exceptions.h>

#include <iostream>

using namespace isc::dhcp;

Memfile_LeaseMgr::Memfile_LeaseMgr(const ParameterMap& parameters)
    : LeaseMgr(parameters) {
    std::cout << "Warning: Using memfile database backend. It is usable for limited"
              << " testing only. Leases will be lost after restart." << std::endl;
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
}

bool Memfile_LeaseMgr::addLease(const Lease4Ptr& lease) {
    if (getLease4(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }
    storage4_.insert(lease);
    return (true);
}

bool Memfile_LeaseMgr::addLease(const Lease6Ptr& lease) {
    if (getLease6(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }
    storage6_.insert(lease);
    return (true);
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    Lease4Storage::iterator l = storage4_.find(addr);
    if (l == storage4_.end()) {
        return (Lease4Ptr());
    } else {
        return (*l);
    }
}

Lease4Collection Memfile_LeaseMgr::getLease4(const HWAddr& ) const {
    isc_throw(NotImplemented, "getLease4(HWaddr x) method not implemented yet");
    return (Lease4Collection());
}

Lease4Ptr Memfile_LeaseMgr::getLease4(const HWAddr& hwaddr,
                                      SubnetID id) const {
    Lease4Storage::iterator l;
    for (l = storage4_.begin(); l != storage4_.end(); ++l) {
        if ( ((*l)->hwaddr_ == hwaddr) &&
             ((*l)->subnet_id_ == id)) {
            return (*l);
        }
    }

    // not found
    return (Lease4Ptr());
}


Lease4Ptr Memfile_LeaseMgr::getLease4(const ClientId& client_id,
                                      SubnetID subnet_id) const {
    Lease4Storage::iterator l;
    for (l = storage4_.begin(); l != storage4_.end(); ++l) {
        if ( (*(*l)->client_id_ == client_id) &&
             ((*l)->subnet_id_ == subnet_id)) {
            return (*l);
        }
    }

    // not found
    return (Lease4Ptr());
}

Lease4Collection Memfile_LeaseMgr::getLease4(const ClientId& ) const {
    isc_throw(NotImplemented, "getLease4(ClientId) not implemented");
}

Lease6Ptr Memfile_LeaseMgr::getLease6(const isc::asiolink::IOAddress& addr) const {
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end()) {
        return (Lease6Ptr());
    } else {
        return (*l);
    }
}

Lease6Collection Memfile_LeaseMgr::getLease6(const DUID& , uint32_t ) const {
    return (Lease6Collection());
}

Lease6Ptr Memfile_LeaseMgr::getLease6(const DUID& duid, uint32_t iaid,
                                      SubnetID subnet_id) const {
    /// @todo: Slow, naive implementation. Write it using additional indexes
    for (Lease6Storage::iterator l = storage6_.begin(); l != storage6_.end(); ++l) {
        if ( (*((*l)->duid_) == duid) &&
             ( (*l)->iaid_ == iaid) &&
             ( (*l)->subnet_id_ == subnet_id)) {
            return (*l);
        }
    }
    return (Lease6Ptr());
}

void Memfile_LeaseMgr::updateLease4(const Lease4Ptr& ) {
}

void Memfile_LeaseMgr::updateLease6(const Lease6Ptr& ) {

}

bool Memfile_LeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
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

std::string Memfile_LeaseMgr::getDescription() const {
    return (std::string("This is a dummy memfile backend implementation.\n"
                        "It does not offer any useful lease management and its only\n"
                        "purpose is to test abstract lease manager API."));
}

void
Memfile_LeaseMgr::commit() {
}

void
Memfile_LeaseMgr::rollback() {
}
