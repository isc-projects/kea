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

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_file_loader.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <exceptions/exceptions.h>
#include <cstdio>
#include <iostream>
#include <sstream>

namespace {

/// @brief Maximum number of errors to read the leases from the lease file.
const uint32_t MAX_LEASE_ERRORS = 100;

} // end of anonymous namespace

using namespace isc::dhcp;
using namespace isc::util;

Memfile_LeaseMgr::Memfile_LeaseMgr(const ParameterMap& parameters)
    : LeaseMgr(parameters), lfc_timer_(*getIOService()) {
    // Check the universe and use v4 file or v6 file.
    std::string universe = getParameter("universe");
    if (universe == "4") {
        std::string file4 = initLeaseFilePath(V4);
        if (!file4.empty()) {
            loadLeasesFromFiles<Lease4, CSVLeaseFile4>(file4, lease_file4_,
                                                       storage4_);
        }
    } else {
        std::string file6 = initLeaseFilePath(V6);
        if (!file6.empty()) {
            loadLeasesFromFiles<Lease6, CSVLeaseFile6>(file6, lease_file6_,
                                                       storage6_);
        }
    }

    // If lease persistence have been disabled for both v4 and v6,
    // issue a warning. It is ok not to write leases to disk when
    // doing testing, but it should not be done in normal server
    // operation.
   if (!persistLeases(V4) && !persistLeases(V6)) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_MEMFILE_NO_STORAGE);

    } else  {
        initTimers();
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
        if ( (*(*lease)->hwaddr_) == hwaddr) {
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
    typedef Lease4Storage::nth_index<0>::type SearchIndex;
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
Memfile_LeaseMgr::appendSuffix(const std::string& file_name,
                               const LFCFileType& file_type) {
    std::string name(file_name);
    switch (file_type) {
    case FILE_INPUT:
        name += ".1";
        break;
    case FILE_PREVIOUS:
        name += ".2";
        break;
    case FILE_OUTPUT:
        name += ".output";
        break;
    case FILE_FINISH:
        name += ".completed";
        break;
    default:
        // Do not append any suffix for the FILE_CURRENT.
        ;
    }

    return (name);
}


uint32_t
Memfile_LeaseMgr::getIOServiceExecInterval() const {
    return (static_cast<uint32_t>(lfc_timer_.getInterval() / 1000));
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
Memfile_LeaseMgr::initTimers() {
    std::string lfc_interval_str = "0";
    try {
        lfc_interval_str = getParameter("lfc-interval");
    } catch (const std::exception& ex) {
        // Ignore and default to 0.
    }

    uint32_t lfc_interval = 0;
    try {
        lfc_interval = boost::lexical_cast<uint32_t>(lfc_interval_str);
    } catch (boost::bad_lexical_cast& ex) {
        isc_throw(isc::BadValue, "invalid value of the lfc-interval "
                  << lfc_interval_str << " specified");
    }

    if (lfc_interval > 0) {
        asiolink::IntervalTimer::Callback cb =
            boost::bind(&Memfile_LeaseMgr::lfcCallback, this);
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_SETUP).arg(lfc_interval);
        lfc_timer_.setup(cb, lfc_interval * 1000);
    }
}

void
Memfile_LeaseMgr::lfcCallback() {
    /// @todo Extend this method to spawn the new process which will
    /// perform the Lease File Cleanup in background.
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_START);

    // Check if we're in the v4 or v6 space and use the appropriate file.
    if (lease_file4_) {
        leaseFileCleanup(lease_file4_);

    } else if (lease_file6_) {
        leaseFileCleanup(lease_file6_);

    }
}

template<typename LeaseFileType>
void Memfile_LeaseMgr::
leaseFileCleanup(boost::shared_ptr<LeaseFileType>& lease_file) {
    CSVFile lease_file_copy(appendSuffix(lease_file->getFilename(), FILE_INPUT));
    if (!lease_file_copy.exists()) {
        lease_file->close();
        rename(lease_file->getFilename().c_str(),
               lease_file_copy.getFilename().c_str());
        lease_file.reset(new LeaseFileType(lease_file->getFilename()));
        lease_file->open();
    }
}

template<typename LeaseObjectType, typename LeaseFileType, typename StorageType>
void Memfile_LeaseMgr::
loadLeasesFromFiles(const std::string& filename,
                    boost::shared_ptr<LeaseFileType>& lease_file,
                    StorageType& storage) {
    storage.clear();

    // Load the leasefile.completed, if exists.
    lease_file.reset(new LeaseFileType(std::string(filename + ".completed")));
    if (lease_file->exists()) {
        LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                               MAX_LEASE_ERRORS);

    } else {
        // If the leasefile.completed doesn't exist, let's load the leases
        // from leasefile.2 and leasefile.1, if they exist.
        lease_file.reset(new LeaseFileType(appendSuffix(filename, FILE_PREVIOUS)));
        if (lease_file->exists()) {
            LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                                   MAX_LEASE_ERRORS);
        }

        lease_file.reset(new LeaseFileType(appendSuffix(filename, FILE_INPUT)));
        if (lease_file->exists()) {
            LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                                   MAX_LEASE_ERRORS);
        }
    }

    // Always load leases from the primary lease file. If the lease file
    // doesn't exist it will be created by the LeaseFileLoader. Note
    // that the false value passed as the last parameter to load
    // function causes the function to leave the file open after
    // it is parsed. This file will be used by the backend to record
    // future lease updates.
    lease_file.reset(new LeaseFileType(filename));
    LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                           MAX_LEASE_ERRORS, false);;
}
