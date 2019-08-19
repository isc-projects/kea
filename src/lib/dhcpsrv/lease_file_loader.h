// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_FILE_LOADER_H
#define LEASE_FILE_LOADER_H

#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <util/versioned_csv_file.h>
#include <dhcpsrv/sanity_checker.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Utility class to manage bulk of leases in the lease files.
///
/// This class exposes methods which allow for bulk loading leases from
/// the lease file and dumping the leases held in memory into the
/// lease file. There are two major use cases for this class:
/// - load leases by the DHCP server when the server starts up or
///   reloads configuration,
/// - an application performing a lease file cleanup rewrites the whole
///   lease file to remove the redundant lease entries.
///
/// In the former case, this class is used by the @c MemFile_LeaseMgr.
/// In the latter case, this class is used by the standalone application
/// which reads the whole lease file into memory (storage) and then
/// dumps the leases held in the storage to another file.
///
/// The methods in this class are templated so as they can be used both
/// with the @c Lease4Storage and @c Lease6Storage to process the DHCPv4
/// and DHCPv6 leases respectively.
///
class LeaseFileLoader {
public:

    /// @brief Load leases from the lease file into the specified storage.
    ///
    /// This method iterates over the entries in the lease file in the
    /// CSV format, creates @c Lease4 or @c Lease6 objects and inserts
    /// them into the storage to which reference is specified as an
    /// argument. If there are multiple entries for the particular lease
    /// in the lease file the entries further in the lease file override
    /// the previous entries.
    ///
    /// If the method finds the entry with the valid lifetime of 0 it
    /// means that the particular lease was released and the method
    /// removes an existing lease from the container.
    ///
    /// @param lease_file A reference to the @c CSVLeaseFile4 or
    /// @c CSVLeaseFile6 object representing the lease file. The file
    /// doesn't need to be open because the method re-opens the file.
    /// @param storage A reference to the container to which leases
    /// should be inserted.
    /// @param max_errors Maximum number of corrupted leases in the
    /// lease file. The method will skip corrupted leases but after
    /// exceeding the specified number of errors it will throw an
    /// exception. A value of 0 (default) disables the limit check.
    /// @param close_file_on_exit A boolean flag which indicates if
    /// the file should be closed after it has been successfully parsed.
    /// One case when the file is not opened is when the server starts
    /// up, reads the leases in the file and then leaves the file open
    /// for writing future lease updates.
    /// @tparam LeaseObjectType A @c Lease4 or @c Lease6.
    /// @tparam LeaseFileType A @c CSVLeaseFile4 or @c CSVLeaseFile6.
    /// @tparam StorageType A @c Lease4Storage or @c Lease6Storage.
    ///
    /// @throw isc::util::CSVFileError when the maximum number of errors
    /// has been exceeded.
    template<typename LeaseObjectType, typename LeaseFileType,
             typename StorageType>
    static void load(LeaseFileType& lease_file, StorageType& storage,
                     const uint32_t max_errors = 0,
                     const bool close_file_on_exit = true) {

        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LEASE_FILE_LOAD)
            .arg(lease_file.getFilename());

        // Reopen the file, as we don't know whether the file is open
        // and we also don't know its current state.
        lease_file.close();
        lease_file.open();

        // Create lease sanity checker if checking is enabled.
        boost::scoped_ptr<SanityChecker> lease_checker;
        if (SanityChecker::leaseCheckingEnabled(false)) {
            // Since lease file is loaded during the configuration,
            // we have to use staging config, rather than current
            // config for this (false = staging).
            lease_checker.reset(new SanityChecker());
        }

        boost::shared_ptr<LeaseObjectType> lease;
        // Track the number of corrupted leases.
        uint32_t errcnt = 0;
        while (true) {
            // Unable to parse the lease.
            if (!lease_file.next(lease)) {
                LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LEASE_LOAD_ROW_ERROR)
                            .arg(lease_file.getReads())
                            .arg(lease_file.getReadMsg());

                // A value of 0 indicates that we don't return
                // until the whole file is parsed, even if errors occur.
                // Otherwise, check if we have exceeded the maximum number
                // of errors and throw an exception if we have.
                if (max_errors && (++errcnt > max_errors)) {
                    // If we break parsing the CSV file because of too many
                    // errors, it doesn't make sense to keep the file open.
                    // This is because the caller wouldn't know where we
                    // stopped parsing and where the internal file pointer
                    // is. So, there are probably no cases when the caller
                    // would continue to use the open file.
                    lease_file.close();
                    isc_throw(util::CSVFileError, "exceeded maximum number of"
                              " failures " << max_errors << " to read a lease"
                              " from the lease file "
                              << lease_file.getFilename());
                }
                // Skip the corrupted lease.
                continue;
            }

            // Lease was found and we successfully parsed it.
            if (lease) {
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL_DATA,
                          DHCPSRV_MEMFILE_LEASE_LOAD)
                    .arg(lease->toText());

                if (lease_checker)  {
                    // If the lease is insane the checker will reset the lease pointer.
                    // As lease file is loaded during the configuration, we have
                    // to use staging config, rather than current config for this
                    // (false = staging).
                    lease_checker->checkLease(lease, false);
                    if (!lease) {
                        continue;
                    }
                }

                // Check if this lease exists.
                typename StorageType::iterator lease_it =
                    storage.find(lease->addr_);
                // The lease doesn't exist yet. Insert the lease if
                // it has a positive valid lifetime.
                if (lease_it == storage.end()) {
                    if (lease->valid_lft_ > 0) {
                        storage.insert(lease);
                    }
                } else {
                    // The lease exists. If the new entry has a valid
                    // lifetime of 0 it is an indication to remove the
                    // existing entry. Otherwise, we update the lease.
                    if (lease->valid_lft_ == 0) {
                        storage.erase(lease_it);

                    } else {
                        // Use replace to re-index leases on update.
                        storage.replace(lease_it, lease);
                    }
                }

            } else {
                // Being here means that we hit the end of file.
                break;

            }
        }

        if (lease_file.needsConversion()) {
            LOG_WARN(dhcpsrv_logger,
                     (lease_file.getInputSchemaState()
                      == util::VersionedCSVFile::NEEDS_UPGRADE
                      ?  DHCPSRV_MEMFILE_NEEDS_UPGRADING
                      : DHCPSRV_MEMFILE_NEEDS_DOWNGRADING))
                     .arg(lease_file.getFilename())
                     .arg(lease_file.getSchemaVersion());
        }

        if (close_file_on_exit) {
            lease_file.close();
        }
    }

    /// @brief Write leases from the storage into a lease file
    ///
    /// This method iterates over the @c Lease4 or @c Lease6 object in the
    /// storage specified in the arguments and writes them to the file
    /// specified in the arguments.
    ///
    /// This method writes all entries in the storage to the file, it does
    /// not perform any checks for expiration or duplication.
    ///
    /// The order in which the entries will be written to the file depends
    /// on the first index in the multi-index container.  Currently that
    /// is the v4 or v6 IP address and they are written from lowest to highest.
    ///
    /// Before writing the method will close the file if it is open
    /// and reopen it for writing.  After completion it will close
    /// the file.
    ///
    /// @param lease_file A reference to the @c CSVLeaseFile4 or
    /// @c CSVLeaseFile6 object representing the lease file. The file
    /// doesn't need to be open because the method re-opens the file.
    /// @param storage A reference to the container from which leases
    /// should be written.
    ///
    /// @tparam LeaseObjectType A @c Lease4 or @c Lease6.
    /// @tparam LeaseFileType A @c CSVLeaseFile4 or @c CSVLeaseFile6.
    /// @tparam StorageType A @c Lease4Storage or @c Lease6Storage.
    template<typename LeaseObjectType, typename LeaseFileType,
             typename StorageType>
    static void write(LeaseFileType& lease_file, const StorageType& storage) {
        // Reopen the file, as we don't know whether the file is open
        // and we also don't know its current state.
        lease_file.close();
        lease_file.open();

        // Iterate over the storage area writing out the leases
        for (typename StorageType::const_iterator lease = storage.begin();
             lease != storage.end();
             ++lease) {
            try {
                lease_file.append(**lease);
            } catch (const isc::Exception&) {
                // Close the file
                lease_file.close();
                throw;
            }
        }

        // Close the file
        lease_file.close();
    }
};

}  // namespace dhcp
}  // namespace isc

#endif // LEASE_FILE_LOADER_H
