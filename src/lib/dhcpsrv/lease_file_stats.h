// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_FILE_STATS_H
#define LEASE_FILE_STATS_H

namespace isc {
namespace dhcp {

/// @brief Provides statistics for leases.
///
/// This class provides a common space for statistics that we wish
/// to keep about leases.  Currently this is for use with lease files
/// but it may be expanded in the future.
class LeaseFileStats {
public:
    /// @brief Constructor
    ///
    /// Initializes the stats variables to zeros
    LeaseFileStats() {
        clearStatistics();
    }

    /// @brief Destructor
    ~LeaseFileStats() {
    }

    /// @brief Gets the number of attempts to read a lease
    uint32_t getReads() const {
        return (reads_);
    }

    /// @brief Gets the number of leases read
    uint32_t getReadLeases() const {
        return (read_leases_);
    }

    /// @brief Gets the number of errors when reading leases
    uint32_t getReadErrs() const {
        return (read_errs_);
    }

    /// @brief Gets the number of attempts to write a lease
    uint32_t getWrites() const {
        return (writes_);
    }

    /// @brief Gets the number of leases written
    uint32_t getWriteLeases() const {
        return (write_leases_);
    }

    /// @brief Gets the number of errors when writing leases
    uint32_t getWriteErrs() const {
        return (write_errs_);
    }

    /// @brief Clears the statistics
    void clearStatistics() {
        reads_        = 0;
        read_leases_  = 0;
        read_errs_    = 0;
        writes_       = 0;
        write_leases_ = 0;
        write_errs_   = 0;
    }

protected:
    /// @brief Number of attempts to read a lease
    uint32_t reads_;

    /// @brief Number of leases read
    uint32_t read_leases_;

    /// @brief Number of errors when reading
    uint32_t read_errs_;

    /// @brief Number of attempts to write a lease
    uint32_t writes_;

    /// @brief Number of lease written
    uint32_t write_leases_;

    /// @brief Number of errors when writing
    uint32_t write_errs_;
};

}  // namespace dhcp
}  // namespace isc

#endif // LEASE_FILE_STATS_H
