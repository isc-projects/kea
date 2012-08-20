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

#include <string>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "benchmark.h"

/// @brief Structure of the Lease4 that is kept in memory
struct Lease4 {
    uint32_t addr; /// IPv4 address
    std::vector<uint8_t> hwaddr; /// hardware address
    std::vector<uint8_t> client_id; /// client-identifier
    uint32_t valid_lft; /// valid lifetime timestamp
    uint32_t recycle_time; /// timer for keeping lease after expiration/release
                           /// (currently not used)
    time_t cltt; /// client last transmission time
    uint32_t pool_id; /// ID of the pool the lease belongs to
    bool fixed; /// is this lease fixed?
    std::string hostname; /// client hostname (may be empty)
    bool fqdn_fwd; /// did we do AAAA update for this lease?
    bool fqdn_rev; /// did we do PTR update for this lease?
    std::string options; /// additional options stored with this lease
                         /// (currently not used)
    std::string comments; /// comments on that lease
                          /// (currently not used)
};

/// Pointer to a Lease4 structure
typedef boost::shared_ptr<Lease4> Lease4Ptr;

/// an implementation of in-memory+file database
/// The actual implementation is in memfile_ubench.cc
class memfile_LeaseMgr;

/// @brief In-memory + file micro-benchmark.
///
/// That is a specific backend implementation. See \ref uBenchmark class for
/// detailed explanation of its operations. This class uses custom in-memory
/// pseudo-database and external write-only lease file. That approach simulates
/// modernized model of ISC DHCP4. It uses standard STL maps together with
/// shared_ptr from boost library. The "database" is implemented in the Lease
/// Manager (see \ref LeaseMgr in memfile_ubench.cc). All lease changes are
/// appended to the end of the file, speeding up the process.
class memfile_uBenchmark: public uBenchmark {
public:

    /// @brief The sole memfile benchmark constructor.
    ///
    /// @param filename name of the write-only lease file
    /// @param num_iterations number of iterations
    /// @param sync should fsync() be called after every file write?
    /// @param verbose would you like extra logging?
    memfile_uBenchmark(const std::string& filename,
                       uint32_t num_iterations, bool sync, bool verbose);

    /// @brief Prints backend info.
    virtual void printInfo();

    /// @brief Spawns lease manager that create empty lease file, initializes
    ///        empty STL maps.
    virtual void connect();

    /// @brief Delete lease manager that closes lease file.
    virtual void disconnect();

    /// @brief Creates new leases.
    ///
    /// See uBenchmark::createLease4Test() for detailed explanation.
    virtual void createLease4Test();

    /// @brief Searches for existing leases.
    ///
    /// See uBenchmark::searchLease4Test() for detailed explanation.
    virtual void searchLease4Test();

    /// @brief Updates existing leases.
    ///
    /// See uBenchmark::updateLease4Test() for detailed explanation.
    virtual void updateLease4Test();

    /// @brief Deletes existing leases.
    ///
    /// See uBenchmark::deleteLease4Test() for detailed explanation.
    virtual void deleteLease4Test();

protected:

    /// Lease Manager (concrete backend implementation, based on STL maps)
    memfile_LeaseMgr * LeaseMgr_;

    /// Name of the lease file.
    std::string Filename_;
};
