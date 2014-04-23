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

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <exceptions/exceptions.h>

#include <iostream>

using namespace isc::dhcp;

Memfile_LeaseMgr::Memfile_LeaseMgr(const ParameterMap& parameters)
    : LeaseMgr(parameters) {
    // Check the universe and use v4 file or v6 file.
    std::string universe = getParameter("universe");
    if (universe == "4") {
        std::string file4 = initLeaseFilePath(V4);
        if (!file4.empty()) {
            lease_file4_.reset(new CSVLeaseFile4(file4));
            lease_file4_->open();
            load4();
        }
    } else {
        std::string file6 = initLeaseFilePath(V6);
        if (!file6.empty()) {
            lease_file6_.reset(new CSVLeaseFile6(file6));
            lease_file6_->open();
            load6();
        }
    }

    // If lease persistence have been disabled for both v4 and v6,
    // issue a warning. It is ok not to write leases to disk when
    // doing testing, but it should not be done in normal server
    // operation.
    if (!persistLeases(V4) && !persistLeases(V6)) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_MEMFILE_NO_STORAGE);
    }
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
    if (lease_file4_) {
        lease_file4_->close();
        lease_file4_.reset();
    }
    if (lease_file6_) {
        lease_file6_->close();
        lease_file6_.reset();
    }
}

bool
Memfile_LeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ADD_ADDR4).arg(lease->addr_.toText());

    if (getLease4(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V4)) {
        lease_file4_->append(*lease);
    }

    storage4_.insert(lease);
    return (true);
}

bool
Memfile_LeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ADD_ADDR6).arg(lease->addr_.toText());

    if (getLease6(lease->type_, lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V6)) {
        lease_file6_->append(*lease);
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
        if ((*lease)->hwaddr_ == hwaddr.hwaddr_) {
            collection.push_back((*lease));
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
Memfile_LeaseMgr::getLease4(const ClientId& client_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_CLIENTID).arg(client_id.toText());
    typedef Memfile_LeaseMgr::Lease4Storage::nth_index<0>::type SearchIndex;
    Lease4Collection collection;
    const SearchIndex& idx = storage4_.get<0>();
    for(SearchIndex::const_iterator lease = idx.begin();
        lease != idx.end(); ++ lease) {

        // client-id is not mandatory in DHCPv4. There can be a lease that does
        // not have a client-id. Dereferencing null pointer would be a bad thing
        if((*lease)->client_id_ && *(*lease)->client_id_ == client_id) {
            collection.push_back((*lease));
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
Memfile_LeaseMgr::getLease6(Lease::Type type,
                            const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_ADDR6)
        .arg(addr.toText())
        .arg(Lease::typeToText(type));
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end() || !(*l) || ((*l)->type_ != type)) {
        return (Lease6Ptr());
    } else {
        return (Lease6Ptr(new Lease6(**l)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(Lease::Type type,
                            const DUID& duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_IAID_DUID)
        .arg(iaid)
        .arg(duid.toText())
        .arg(Lease::typeToText(type));

    // We are going to use index #1 of the multi index container.
    typedef Lease6Storage::nth_index<1>::type SearchIndex;
    // Get the index.
    const SearchIndex& idx = storage6_.get<1>();
    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<SearchIndex::iterator, SearchIndex::iterator> l =
        idx.equal_range(boost::make_tuple(duid.getDuid(), iaid, type));
    Lease6Collection collection;
    for(SearchIndex::iterator lease = l.first; lease != l.second; ++lease) {
        collection.push_back(Lease6Ptr(new Lease6(**lease)));
    }

    return (collection);
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(Lease::Type type,
                             const DUID& duid, uint32_t iaid,
                             SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_IAID_SUBID_DUID)
        .arg(iaid)
        .arg(subnet_id)
        .arg(duid.toText())
        .arg(Lease::typeToText(type));

    // We are going to use index #1 of the multi index container.
    typedef Lease6Storage::nth_index<1>::type SearchIndex;
    // Get the index.
    const SearchIndex& idx = storage6_.get<1>();
    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<SearchIndex::iterator, SearchIndex::iterator> l =
        idx.equal_range(boost::make_tuple(duid.getDuid(), iaid, type));
    Lease6Collection collection;
    for(SearchIndex::iterator lease = l.first; lease != l.second; ++lease) {
        // Filter out the leases which subnet id doesn't match.
        if((*lease)->subnet_id_ == subnet_id) {
            collection.push_back(Lease6Ptr(new Lease6(**lease)));
        }
    }

    return (collection);
}

void
Memfile_LeaseMgr::updateLease4(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR4).arg(lease->addr_.toText());

    Lease4Storage::iterator lease_it = storage4_.find(lease->addr_);
    if (lease_it == storage4_.end()) {
        isc_throw(NoSuchLease, "failed to update the lease with address "
                  << lease->addr_ << " - no such lease");
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V4)) {
        lease_file4_->append(*lease);
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
                  << lease->addr_ << " - no such lease");
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V6)) {
        lease_file6_->append(*lease);
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
            if (persistLeases(V4)) {
                // Copy the lease. The valid lifetime needs to be modified and
                // we don't modify the original lease.
                Lease4 lease_copy = **l;
                // Setting valid lifetime to 0 means that lease is being
                // removed.
                lease_copy.valid_lft_ = 0;
                lease_file4_->append(lease_copy);
            }
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
            if (persistLeases(V6)) {
                // Copy the lease. The lifetimes need to be modified and we
                // don't modify the original lease.
                Lease6 lease_copy = **l;
                // Setting lifetimes to 0 means that lease is being removed.
                lease_copy.valid_lft_ = 0;
                lease_copy.preferred_lft_ = 0;
                lease_file6_->append(lease_copy);
            }

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

std::string
Memfile_LeaseMgr::getDefaultLeaseFilePath(Universe u) const {
    std::ostringstream s;
    s << CfgMgr::instance().getDataDir() << "/kea-leases";
    s << (u == V4 ? "4" : "6");
    s << ".csv";
    return (s.str());
}

std::string
Memfile_LeaseMgr::getLeaseFilePath(Universe u) const {
    if (u == V4) {
        return (lease_file4_ ? lease_file4_->getFilename() : "");
    }

    return (lease_file6_ ? lease_file6_->getFilename() : "");
}

bool
Memfile_LeaseMgr::persistLeases(Universe u) const {
    // Currently, if the lease file IO is not created, it means that writes to
    // disk have been explicitly disabled by the administrator. At some point,
    // there may be a dedicated ON/OFF flag implemented to control this.
    if (u == V4 && lease_file4_) {
        return (true);
    }

    return (u == V6 && lease_file6_);
}

std::string
Memfile_LeaseMgr::initLeaseFilePath(Universe u) {
    std::string persist_val;
    try {
        persist_val = getParameter("persist");
    } catch (const Exception& ex) {
        // If parameter persist hasn't been specified, we use a default value
        // 'yes'.
        persist_val = "true";
    }
    // If persist_val is 'false' we will not store leases to disk, so let's
    // return empty file name.
    if (persist_val == "false") {
        return ("");

    } else if (persist_val != "true") {
        isc_throw(isc::BadValue, "invalid value 'persist="
                  << persist_val << "'");
    }

    std::string lease_file;
    try {
        lease_file = getParameter("name");
    } catch (const Exception& ex) {
        lease_file = getDefaultLeaseFilePath(u);
    }
    return (lease_file);
}

void
Memfile_LeaseMgr::load4() {
    // If lease file hasn't been opened, we are working in non-persistent mode.
    // That's fine, just leave.
    if (!persistLeases(V4)) {
        return;
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LEASES_RELOAD4)
        .arg(lease_file4_->getFilename());

    // Remove existing leases (if any). We will recreate them based on the
    // data on disk.
    storage4_.clear();

    Lease4Ptr lease;
    do {
        /// @todo Currently we stop parsing on first failure. It is possible
        /// that only one (or a few) leases are bad, so in theory we could
        /// continue parsing but that would require some error counters to
        /// prevent endless loops. That is enhancement for later time.
        if (!lease_file4_->next(lease)) {
            isc_throw(DbOperationError, "Failed to parse the DHCPv6 lease in"
                      " the lease file: " << lease_file4_->getReadMsg());
        }
        // If we got the lease, we update the internal container holding
        // leases. Otherwise, we reached the end of file and we leave.
        if (lease) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA,
                      DHCPSRV_MEMFILE_LEASE_LOAD4)
                .arg(lease->toText());
            loadLease4(lease);
        }
    } while (lease);
}

void
Memfile_LeaseMgr::loadLease4(Lease4Ptr& lease) {
    // Check if the lease already exists.
    Lease4Storage::iterator lease_it = storage4_.find(lease->addr_);
    // Lease doesn't exist.
    if (lease_it == storage4_.end()) {
        // Add the lease only if valid lifetime is greater than 0.
        // We use valid lifetime of 0 to indicate that lease should
        // be removed.
        if (lease->valid_lft_ > 0) {
           storage4_.insert(lease);
       }
    } else {
        // We use valid lifetime of 0 to indicate that the lease is
        // to be removed. In such case, erase the lease.
        if (lease->valid_lft_ == 0) {
            storage4_.erase(lease_it);

        } else {
            // Update existing lease.
            **lease_it = *lease;
        }
    }
}

void
Memfile_LeaseMgr::load6() {
    // If lease file hasn't been opened, we are working in non-persistent mode.
    // That's fine, just leave.
    if (!persistLeases(V6)) {
        return;
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LEASES_RELOAD6)
        .arg(lease_file6_->getFilename());

    // Remove existing leases (if any). We will recreate them based on the
    // data on disk.
    storage6_.clear();

    Lease6Ptr lease;
    do {
        /// @todo Currently we stop parsing on first failure. It is possible
        /// that only one (or a few) leases are bad, so in theory we could
        /// continue parsing but that would require some error counters to
        /// prevent endless loops. That is enhancement for later time.
        if (!lease_file6_->next(lease)) {
            isc_throw(DbOperationError, "Failed to parse the DHCPv6 lease in"
                      " the lease file: " << lease_file6_->getReadMsg());
        }
        // If we got the lease, we update the internal container holding
        // leases. Otherwise, we reached the end of file and we leave.
        if (lease) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA,
                      DHCPSRV_MEMFILE_LEASE_LOAD6)
                .arg(lease->toText());

            loadLease6(lease);
        }
    } while (lease);
}

void
Memfile_LeaseMgr::loadLease6(Lease6Ptr& lease) {
    // Check if the lease already exists.
    Lease6Storage::iterator lease_it = storage6_.find(lease->addr_);
    // Lease doesn't exist.
    if (lease_it == storage6_.end()) {
        // Add the lease only if valid lifetime is greater than 0.
        // We use valid lifetime of 0 to indicate that lease should
        // be removed.
        if (lease->valid_lft_ > 0) {
            storage6_.insert(lease);
       }
    } else {
        // We use valid lifetime of 0 to indicate that the lease is
        // to be removed. In such case, erase the lease.
        if (lease->valid_lft_ == 0) {
            storage6_.erase(lease_it);

        } else {
            // Update existing lease.
            **lease_it = *lease;
        }
    }

}

