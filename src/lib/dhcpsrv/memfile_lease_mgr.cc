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

#include <config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_file_loader.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <exceptions/exceptions.h>
#include <util/pid_file.h>
#include <util/process_spawn.h>
#include <util/signal_set.h>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <limits>
#include <sstream>

namespace {

/// @brief Maximum number of errors to read the leases from the lease file.
const uint32_t MAX_LEASE_ERRORS = 100;

/// @brief A name of the environmental variable specifying the kea-lfc
/// program location.
///
/// This variable can be set by tests to point to the location of the
/// kea-lfc program within a build directory. If this variable is not
/// set, the backend will use the location of the kea-lfc in the
/// Kea installation directory.
const char* KEA_LFC_EXECUTABLE_ENV_NAME = "KEA_LFC_EXECUTABLE";

} // end of anonymous namespace

using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Represents a configuration for Lease File Cleanup.
///
/// This class is solely used by the @c Memfile_LeaseMgr as a configuration
/// information storage for %Lease File Cleanup. Internally, it creates
/// the interval timer and assigns a callback function (pointer to which is
/// passed in the constructor), which will be called at the specified
/// intervals to perform the cleanup. It is also responsible for creating
/// and maintaing the object which is used to spawn the new process which
/// executes the @c kea-lfc program.
///
/// This functionality is enclosed in a separate class so as the implementation
/// details are not exposed in the @c Memfile_LeaseMgr header file and
/// to maintain a single place with the LFC configuration, instead of multiple
/// members and functions scattered in the @c Memfile_LeaseMgr class.
class LFCSetup {
public:

    /// @brief Constructor.
    ///
    /// Assigns a pointer to the function triggered to perform the cleanup.
    /// This pointer should point to the appropriate method of the
    /// @c Memfile_LeaseMgr class.
    ///
    /// @param callback A pointer to the callback function.
    /// @param io_service An io service used to create the interval timer.
    LFCSetup(asiolink::IntervalTimer::Callback callback,
             asiolink::IOService& io_service);

    /// @brief Sets the new configuration for the %Lease File Cleanup.
    ///
    /// @param lfc_interval An interval in seconds at which the cleanup should
    /// be performed.
    /// @param lease_file4 A pointer to the DHCPv4 lease file to be cleaned up
    /// or NULL. If this is NULL, the @c lease_file6 must be non-null.
    /// @param lease_file6 A pointer to the DHCPv6 lease file to be cleaned up
    /// or NULL. If this is NULL, the @c lease_file4 must be non-null.
    void setup(const uint32_t lfc_interval,
               const boost::shared_ptr<CSVLeaseFile4>& lease_file4,
               const boost::shared_ptr<CSVLeaseFile6>& lease_file6);

    /// @brief Spawns a new process.
    void execute();

    /// @brief Returns interval at which the cleanup is performed.
    ///
    /// @return Interval in milliseconds.
    long getInterval() const;

    /// @brief Checks if the lease file cleanup is in progress.
    ///
    /// @return true if the lease file cleanup is being executed.
    bool isRunning() const;

    /// @brief Returns exit code of the last completed cleanup.
    int getExitStatus() const;

private:

    /// @brief Interval timer for LFC.
    asiolink::IntervalTimer timer_;

    /// @brief A pointer to the @c ProcessSpawn object used to execute
    /// the LFC.
    boost::scoped_ptr<util::ProcessSpawn> process_;

    /// @brief A pointer to the callback function executed by the timer.
    asiolink::IntervalTimer::Callback callback_;

    /// @brief A PID of the last executed LFC process.
    pid_t pid_;
};

LFCSetup::LFCSetup(asiolink::IntervalTimer::Callback callback,
                   asiolink::IOService& io_service)
    : timer_(io_service), process_(), callback_(callback), pid_(0) {
}

void
LFCSetup::setup(const uint32_t lfc_interval,
                const boost::shared_ptr<CSVLeaseFile4>& lease_file4,
                const boost::shared_ptr<CSVLeaseFile6>& lease_file6) {

    // If LFC is enabled, we have to setup the interval timer and prepare for
    // executing the kea-lfc process.
    if (lfc_interval > 0) {
        std::string executable;
        char* c_executable = getenv(KEA_LFC_EXECUTABLE_ENV_NAME);
        if (c_executable == NULL) {
            executable = KEA_LFC_EXECUTABLE;

        } else {
            executable = c_executable;
        }

        // Set the timer to call callback function periodically.
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_SETUP).arg(lfc_interval);
        // Multiple the lfc_interval value by 1000 as this value specifies
        // a timeout in seconds, whereas the setup() method expects the
        // timeout in milliseconds.
        timer_.setup(callback_, lfc_interval * 1000);

        // Start preparing the command line for kea-lfc.

        // Gather the base file name.
        std::string lease_file = lease_file4 ? lease_file4->getFilename() :
            lease_file6->getFilename();

        // Create the other names by appending suffixes to the base name.
        util::ProcessArgs args;
        // Universe: v4 or v6.
        args.push_back(lease_file4 ? "-4" : "-6");
        // Previous file.
        args.push_back("-x");
        args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                      Memfile_LeaseMgr::FILE_PREVIOUS));
        // Input file.
        args.push_back("-i");
        args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                      Memfile_LeaseMgr::FILE_INPUT));
        // Output file.
        args.push_back("-o");
        args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                      Memfile_LeaseMgr::FILE_OUTPUT));
        // Finish file.
        args.push_back("-f");
        args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                      Memfile_LeaseMgr::FILE_FINISH));
        // PID file.
        args.push_back("-p");
        args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                      Memfile_LeaseMgr::FILE_PID));

        // The configuration file is currently unused.
        args.push_back("-c");
        args.push_back("ignored-path");

        // Create the process (do not start it yet).
        process_.reset(new util::ProcessSpawn(executable, args));
    }
}

long
LFCSetup::getInterval() const {
    return (timer_.getInterval());
}

void
LFCSetup::execute() {
    try {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_EXECUTE)
            .arg(process_->getCommandLine());
        pid_ = process_->spawn();

    } catch (const ProcessSpawnError&) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_SPAWN_FAIL);
    }
}

bool
LFCSetup::isRunning() const {
    return (process_ && process_->isRunning(pid_));
}

int
LFCSetup::getExitStatus() const {
    if (!process_) {
        isc_throw(InvalidOperation, "unable to obtain LFC process exit code: "
                  " the process is NULL");
    }
    return (process_->getExitStatus(pid_));
}


Memfile_LeaseMgr::Memfile_LeaseMgr(const ParameterMap& parameters)
    : LeaseMgr(parameters),
      lfc_setup_(new LFCSetup(boost::bind(&Memfile_LeaseMgr::lfcCallback, this),
                              *getIOService()))
    {
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
        lfcSetup();
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

std::string
Memfile_LeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "Memfile backend " << MAJOR_VERSION;
    tmp << "." << MINOR_VERSION;
    return (tmp.str());
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

    const Lease4StorageAddressIndex& idx = storage4_.get<AddressIndexTag>();
    Lease4StorageAddressIndex::iterator l = idx.find(addr);
    if (l == idx.end()) {
        return (Lease4Ptr());
    } else {
        return (Lease4Ptr(new Lease4(**l)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_HWADDR).arg(hwaddr.toText());
    Lease4Collection collection;
    const Lease4StorageAddressIndex& idx = storage4_.get<AddressIndexTag>();
    for(Lease4StorageAddressIndex::const_iterator lease = idx.begin();
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

    // Get the index by HW Address and Subnet Identifier.
    const Lease4StorageHWAddressSubnetIdIndex& idx =
        storage4_.get<HWAddressSubnetIdIndexTag>();
    // Try to find the lease using HWAddr and subnet id.
    Lease4StorageHWAddressSubnetIdIndex::const_iterator lease =
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
    Lease4Collection collection;
    const Lease4StorageAddressIndex& idx = storage4_.get<AddressIndexTag>();
    for(Lease4StorageAddressIndex::const_iterator lease = idx.begin();
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

    // Get the index by client id, HW address and subnet id.
    const Lease4StorageClientIdHWAddressSubnetIdIndex& idx =
        storage4_.get<ClientIdHWAddressSubnetIdIndexTag>();
    // Try to get the lease using client id, hardware address and subnet id.
    Lease4StorageClientIdHWAddressSubnetIdIndex::const_iterator lease =
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

    // Get the index by client and subnet id.
    const Lease4StorageClientIdSubnetIdIndex& idx =
        storage4_.get<ClientIdSubnetIdIndexTag>();
    // Try to get the lease using client id and subnet id.
    Lease4StorageClientIdSubnetIdIndex::const_iterator lease =
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

    // Get the index by DUID, IAID, lease type.
    const Lease6StorageDuidIaidTypeIndex& idx = storage6_.get<DuidIaidTypeIndexTag>();
    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<Lease6StorageDuidIaidTypeIndex::const_iterator,
              Lease6StorageDuidIaidTypeIndex::const_iterator> l =
        idx.equal_range(boost::make_tuple(duid.getDuid(), iaid, type));
    Lease6Collection collection;
    for(Lease6StorageDuidIaidTypeIndex::const_iterator lease =
            l.first; lease != l.second; ++lease) {
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

    // Get the index by DUID, IAID, lease type.
    const Lease6StorageDuidIaidTypeIndex& idx = storage6_.get<DuidIaidTypeIndexTag>();
    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<Lease6StorageDuidIaidTypeIndex::const_iterator,
              Lease6StorageDuidIaidTypeIndex::const_iterator> l =
        idx.equal_range(boost::make_tuple(duid.getDuid(), iaid, type));
    Lease6Collection collection;
    for(Lease6StorageDuidIaidTypeIndex::const_iterator lease =
            l.first; lease != l.second; ++lease) {
        // Filter out the leases which subnet id doesn't match.
        if((*lease)->subnet_id_ == subnet_id) {
            collection.push_back(Lease6Ptr(new Lease6(**lease)));
        }
    }

    return (collection);
}

void
Memfile_LeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                                    const size_t max_leases) const {
    // Obtain the index which segragates leases by state and time.
    const Lease6StorageExpirationIndex& index = storage6_.get<ExpirationIndexTag>();

    // Retrieve leases which are not reclaimed and which haven't expired. The
    // 'less-than' operator will be used for both components of the index. So,
    // for the 'state' 'false' is less than 'true'. Also the leases with
    // expiration time lower than current time will be returned.
    Lease6StorageExpirationIndex::const_iterator ub =
        index.upper_bound(boost::make_tuple(false, time(NULL)));

    // Copy only the number of leases indicated by the max_leases parameter.
    for (Lease6StorageExpirationIndex::const_iterator lease = index.begin();
         (lease != ub) && ((max_leases == 0) || (std::distance(index.begin(), lease) <
                                                 max_leases));
         ++lease) {
        expired_leases.push_back(Lease6Ptr(new Lease6(**lease)));
    }
}

void
Memfile_LeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                                    const size_t max_leases) const {
    // Obtain the index which segragates leases by state and time.
    const Lease4StorageExpirationIndex& index = storage4_.get<ExpirationIndexTag>();

    // Retrieve leases which are not reclaimed and which haven't expired. The
    // 'less-than' operator will be used for both components of the index. So,
    // for the 'state' 'false' is less than 'true'. Also the leases with
    // expiration time lower than current time will be returned.
    Lease4StorageExpirationIndex::const_iterator ub =
        index.upper_bound(boost::make_tuple(false, time(NULL)));

    // Copy only the number of leases indicated by the max_leases parameter.
    for (Lease4StorageExpirationIndex::const_iterator lease = index.begin();
         (lease != ub) && ((max_leases == 0) || (std::distance(index.begin(), lease) <
                                                 max_leases));
         ++lease) {
        expired_leases.push_back(Lease4Ptr(new Lease4(**lease)));
    }
}

void
Memfile_LeaseMgr::updateLease4(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR4).arg(lease->addr_.toText());

    // Obtain 'by address' index.
    Lease4StorageAddressIndex& index = storage4_.get<AddressIndexTag>();

    // Lease must exist if it is to be updated.
    Lease4StorageAddressIndex::const_iterator lease_it = index.find(lease->addr_);
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

    // Use replace() to re-index leases.
    index.replace(lease_it, Lease4Ptr(new Lease4(*lease)));
}

void
Memfile_LeaseMgr::updateLease6(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR6).arg(lease->addr_.toText());

    // Obtain 'by address' index.
    Lease6StorageAddressIndex& index = storage6_.get<AddressIndexTag>();

    // Lease must exist if it is to be updated.
    Lease6StorageAddressIndex::const_iterator lease_it = index.find(lease->addr_);
    if (lease_it == index.end()) {
        isc_throw(NoSuchLease, "failed to update the lease with address "
                  << lease->addr_ << " - no such lease");
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V6)) {
        lease_file6_->append(*lease);
    }

    // Use replace() to re-index leases.
    index.replace(lease_it, Lease6Ptr(new Lease6(*lease)));
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

void
Memfile_LeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    deleteExpiredReclaimedLeases<Lease4StorageExpirationIndex, Lease4>(secs, V4, storage4_,
                                                                       lease_file4_);
}

void
Memfile_LeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    deleteExpiredReclaimedLeases<Lease6StorageExpirationIndex, Lease6>(secs, V6, storage6_,
                                                                       lease_file6_);
}

template<typename IndexType, typename LeaseType, typename StorageType,
         typename LeaseFileType>
void
Memfile_LeaseMgr::deleteExpiredReclaimedLeases(const uint32_t secs,
                                               const Universe& universe,
                                               StorageType& storage,
                                               LeaseFileType& lease_file) const {
    // Obtain the index which segragates leases by state and time.
    IndexType& index = storage.template get<ExpirationIndexTag>();

    // This returns the first element which is greater than the specified
    // tuple (true, time(NULL) - secs). However, the range between the
    // beginnng of the index and returned element also includes all the
    // elements for which the first value is false (lease state is NOT
    // reclaimed), because false < true. All elements between the
    // beginning of the index and the element returned, for which the
    // first value is true, represent the reclaimed leases which should
    // be deleted, because their expiration time + secs has occured earlier
    // than current time.
    typename IndexType::const_iterator upper_limit =
        index.upper_bound(boost::make_tuple(true, time(NULL) - secs));

    // Now, we have to exclude all elements of the index which represent
    // leases in the state other than reclaimed - with the first value
    // in the index equal to false. Note that elements in the index are
    // ordered from the lower to the higher ones. So, all elements with
    // the first value of false are placed before the elements with the
    // value of true. Hence, we have to find the first element which
    // contains value of true. The time value is the lowest possible.
    typename IndexType::const_iterator lower_limit =
        index.upper_bound(boost::make_tuple(true, std::numeric_limits<int64_t>::min()));

    // If there are some elements in this range, delete them.
    uint64_t num_leases = static_cast<uint64_t>(std::distance(lower_limit, upper_limit));
    if (num_leases > 0) {

        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED_START)
            .arg(num_leases);

        // If lease persistence is enabled, we also have to mark leases
        // as deleted in the lease file. We do this by setting the
        // lifetime to 0.
        if (persistLeases(universe)) {
            for (typename IndexType::const_iterator lease = lower_limit;
                 lease != upper_limit; ++lease) {
                // Copy lease to not affect the lease in the container.
                LeaseType lease_copy(**lease);
                // Set the valid lifetime to 0 to indicate the removal
                // of the lease.
                lease_copy.valid_lft_ = 0;
                lease_file->append(lease_copy);
            }
        }

        // Erase leases from memory.
        index.erase(lower_limit, upper_limit);
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
    case FILE_PID:
        name += ".pid";
        break;
    default:
        // Do not append any suffix for the FILE_CURRENT.
        ;
    }

    return (name);
}


uint32_t
Memfile_LeaseMgr::getIOServiceExecInterval() const {
    return (static_cast<uint32_t>(lfc_setup_->getInterval() / 1000));
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
    } catch (const Exception&) {
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
    } catch (const Exception&) {
        lease_file = getDefaultLeaseFilePath(u);
    }
    return (lease_file);
}

template<typename LeaseObjectType, typename LeaseFileType, typename StorageType>
void Memfile_LeaseMgr::loadLeasesFromFiles(const std::string& filename,
                                           boost::shared_ptr<LeaseFileType>& lease_file,
                                           StorageType& storage) {
    // Check if the instance of the LFC is running right now. If it is
    // running, we refuse to load leases as the LFC may be writing to the
    // lease files right now. When the user retries server configuration
    // it should go through.
    /// @todo Consider applying a timeout for an LFC and retry when this
    /// timeout elapses.
    PIDFile pid_file(appendSuffix(filename, FILE_PID));
    if (pid_file.check()) {
        isc_throw(DbOpenError, "unable to load leases from files while the "
                  "lease file cleanup is in progress");
    }

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
                                           MAX_LEASE_ERRORS, false);
}


bool
Memfile_LeaseMgr::isLFCRunning() const {
    return (lfc_setup_->isRunning());
}

int
Memfile_LeaseMgr::getLFCExitStatus() const {
    return (lfc_setup_->getExitStatus());
}

void
Memfile_LeaseMgr::lfcCallback() {
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_START);

    // Check if we're in the v4 or v6 space and use the appropriate file.
    if (lease_file4_) {
        lfcExecute(lease_file4_);

    } else if (lease_file6_) {
        lfcExecute(lease_file6_);
    }
}

void
Memfile_LeaseMgr::lfcSetup() {
    std::string lfc_interval_str = "0";
    try {
        lfc_interval_str = getParameter("lfc-interval");
    } catch (const std::exception&) {
        // Ignore and default to 0.
    }

    uint32_t lfc_interval = 0;
    try {
        lfc_interval = boost::lexical_cast<uint32_t>(lfc_interval_str);
    } catch (boost::bad_lexical_cast&) {
        isc_throw(isc::BadValue, "invalid value of the lfc-interval "
                  << lfc_interval_str << " specified");
    }

    if (lfc_interval > 0) {
        lfc_setup_->setup(lfc_interval, lease_file4_, lease_file6_);
    }
}

template<typename LeaseFileType>
void Memfile_LeaseMgr::lfcExecute(boost::shared_ptr<LeaseFileType>& lease_file) {
    bool do_lfc = true;

    // Check the status of the LFC instance.
    // If the finish file exists or the copy of the lease file exists it
    // is an indication that another LFC instance may be in progress or
    // may be stalled. In that case we don't want to rotate the current
    // lease file to avoid overriding the contents of the existing file.
    CSVFile lease_file_finish(appendSuffix(lease_file->getFilename(), FILE_FINISH));
    CSVFile lease_file_copy(appendSuffix(lease_file->getFilename(), FILE_INPUT));
    if (!lease_file_finish.exists() && !lease_file_copy.exists()) {
        // Close the current file so as we can move it to the copy file.
        lease_file->close();
        // Move the current file to the copy file. Remember the result
        // because we don't want to run LFC if the rename failed.
        do_lfc = (rename(lease_file->getFilename().c_str(),
                         lease_file_copy.getFilename().c_str()) == 0);

        if (!do_lfc) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_LEASE_FILE_RENAME_FAIL)
                .arg(lease_file->getFilename())
                .arg(lease_file_copy.getFilename())
                .arg(strerror(errno));
        }

        // Regardless if we successfully moved the current file or not,
        // we need to re-open the current file for the server to write
        // new lease updates. If the file has been successfully moved,
        // this will result in creation of the new file. Otherwise,
        // an existing file will be opened.
        try {
            lease_file->open(true);

        } catch (const CSVFileError& ex) {
            // If we're unable to open the lease file this is a serious
            // error because the server will not be able to persist
            // leases.
            /// @todo We need to better address this error. It should
            /// trigger an alarm (once we have a monitoring system in
            /// place) so as an administrator can correct it. In
            /// practice it should be very rare that this happens and
            /// is most likely related to a human error, e.g. changing
            /// file permissions.
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_LEASE_FILE_REOPEN_FAIL)
                .arg(lease_file->getFilename())
                .arg(ex.what());
            // Reset the pointer to the file so as the backend doesn't
            // try to write leases to disk.
            lease_file.reset();
            do_lfc = false;
        }
    }
    // Once the files have been rotated, or untouched if another LFC had
    // not finished, a new process is started.
    if (do_lfc) {
        lfc_setup_->execute();
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
