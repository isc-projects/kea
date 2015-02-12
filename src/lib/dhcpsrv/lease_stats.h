// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LEASE_STATS_H
#define LEASE_STATS_H

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

    /// @brief Gets the number of errors when writting leases
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

} // namespace isc::dhcp
} // namesapce isc

#endif // LEASE_STATS_H
