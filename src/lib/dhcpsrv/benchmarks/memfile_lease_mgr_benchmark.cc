// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/benchmarks/generic_lease_mgr_benchmark.h>
#include <dhcpsrv/benchmarks/parameters.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/testutils/lease_file_io.h>

using namespace isc::dhcp;
using namespace isc::dhcp::bench;
using namespace isc::dhcp::test;
using namespace std;

namespace {

/// @brief This is a fixture class used for benchmarking Memfile lease backend
class MemfileLeaseMgrBenchmark : public GenericLeaseMgrBenchmark {
public:
    /// @brief Constructor
    ///
    /// Sets the files used for writing lease files.
    MemfileLeaseMgrBenchmark() : io4_(""), io6_("") {
    }

    /// @brief Setup routine.
    ///
    /// Removes any files left over from earlier test, destroys any existing
    /// lease manager, and then starts a new memfile lease manager.
    /// The state parameter is ignored.
    void SetUp(::benchmark::State const&) override {

        io4_ = LeaseFileIO(getLeaseFilePath("leasefile4_0.csv"));
        io6_ = LeaseFileIO(getLeaseFilePath("leasefile6_0.csv"));

        // Remove lease files and products of Lease File Cleanup.
        removeFiles(getLeaseFilePath("leasefile4_0.csv"));
        removeFiles(getLeaseFilePath("leasefile6_0.csv"));

        try {
            LeaseMgrFactory::destroy();
            startBackend(V4);
        } catch (...) {
            std::cerr << "ERROR: unable to start memfile backend." << std::endl;
            throw;
        }
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    void SetUp(::benchmark::State& s) override {
        ::benchmark::State const& cs = s;
        SetUp(cs);
    }

    /// @brief Creates instance of the backend.
    ///
    /// @param u Universe (v4 or V6).
    void startBackend(Universe u) {
        try {
            LeaseMgrFactory::create(getConfigString(u));
        } catch (...) {
            std::cerr << "*** ERROR: unable to create instance of the Memfile "
                      << "lease database backend." << std::endl;
            throw;
        }
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    /// @brief Returns the configuration string for the backend.
    ///
    /// This string configures the @c LeaseMgrFactory to create the memfile
    /// backend and use leasefile4_0.csv and leasefile6_0.csv files as
    /// storage for leases.
    ///
    /// @param no_universe Indicates whether universe parameter should be
    /// included (false), or not (true).
    ///
    /// @return Configuration string for @c LeaseMgrFactory.
    static std::string getConfigString(Universe u) {
        std::ostringstream s;
        s << "type=memfile " << (u == V4 ? "universe=4 " : "universe=6 ")
          << "name=" << getLeaseFilePath(u == V4 ? "leasefile4_0.csv" : "leasefile6_0.csv")
          << " lfc-interval=0";
        return (s.str());
    }

    /// @brief Return path to the lease file used by unit tests.
    ///
    /// @param filename Name of the lease file appended to the path to the
    /// directory where test data is held.
    ///
    /// @return Full path to the lease file.
    static std::string getLeaseFilePath(const std::string& filename) {
        std::ostringstream s;
        s << TEST_DATA_BUILDDIR << "/" << filename;
        return (s.str());
    }

    /// @brief Remove files being products of Lease File Cleanup.
    ///
    /// @param base_name Path to the lease file name. This file is removed
    /// and all files which names are created from this name (having specific
    /// suffixes used by Lease File Cleanup mechanism).
    void removeFiles(const std::string& base_name) const {
        // Generate suffixes and append them to the base name. The
        // resulting file names are the ones that may exist as a
        // result of LFC.
        for (int i = static_cast<int>(Memfile_LeaseMgr::FILE_CURRENT);
             i <= static_cast<int>(Memfile_LeaseMgr::FILE_FINISH); ++i) {
            Memfile_LeaseMgr::LFCFileType type = static_cast<Memfile_LeaseMgr::LFCFileType>(i);
            LeaseFileIO io(Memfile_LeaseMgr::appendSuffix(base_name, type));
            io.removeFile();
        }
    }

    /// @brief Cleans up after the test.
    ///
    /// Rolls back any uncommitted operation (really a no-op for memfile as it
    /// does not support transactions), then destroys the lease manager
    /// and finally cleans up the files.
    void TearDown(::benchmark::State const&) override {
        try {
            lmptr_->rollback();
        } catch (...) {
            std::cerr << "WARNING: rollback has failed. This is surprising as "
                      << "memfile doesn't support rollback." << std::endl;
        }

        LeaseMgrFactory::destroy();

        // Remove lease files and products of Lease File Cleanup.
        removeFiles(getLeaseFilePath("leasefile4_0.csv"));
        removeFiles(getLeaseFilePath("leasefile6_0.csv"));
    }

    void TearDown(::benchmark::State& s) override {
        ::benchmark::State const& cs = s;
        TearDown(cs);
    }

    /// @brief Object providing access to v4 lease IO.
    LeaseFileIO io4_;

    /// @brief Object providing access to v6 lease IO.
    LeaseFileIO io6_;
};

// Defines a benchmark that measures IPv4 leases insertion.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, insertLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUp4(state, lease_count);
        benchInsertLeases4();
    }
}

// Defines a benchmark that measures IPv4 leases update.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, updateLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchUpdateLeases4();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by address.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease4_address)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_address();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by hardware address.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease4_hwaddr)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_hwaddr();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by hardware address
// and subnet-id.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease4_hwaddr_subnetid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_hwaddr_subnetid();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by client-id.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease4_clientid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_clientid();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by client-id and
// subnet-id.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease4_clientid_subnetid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_clientid_subnetid();
    }
}

// Defines a benchmark that measures retrieval of expired IPv4 leases.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getExpiredLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetExpiredLeases4();
    }
}

// Defines a benchmark that measures IPv6 leases insertion.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, insertLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUp6(state, lease_count);
        benchInsertLeases6();
    }
}

// Defines a benchmark that measures IPv6 leases update.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, updateLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchUpdateLeases6();
    }
}

// Defines a benchmark that measures IPv6 leases retrieval by type and address.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease6_type_address)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetLease6_type_address();
    }
}

// Defines a benchmark that measures IPv6 leases retrieval by type, duid and iaid.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease6_type_duid_iaid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetLease6_type_duid_iaid();
    }
}

// Defines a benchmark that measures IPv6 leases retrieval by lease type, duid, iaid
// and subnet-id.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getLease6_type_duid_iaid_subnetid)
                  (benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetLease6_type_duid_iaid_subnetid();
    }
}

// Defines a benchmark that measures retrieval of expired IPv6 leases.
BENCHMARK_DEFINE_F(MemfileLeaseMgrBenchmark, getExpiredLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetExpiredLeases6();
    }
}

/// The following macros define run parameters for previously defined
/// memfile benchmarks.

/// A benchmark that measures IPv4 leases insertion.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, insertLeases4)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 leases update.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, updateLeases4)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by IP address.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease4_address)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by hardware address.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease4_hwaddr)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by hardware address and a
/// subnet-id.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease4_hwaddr_subnetid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by client-id.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease4_clientid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by client-id and subnet-id.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease4_clientid_subnetid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures expired IPv4 leases retrieval.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getExpiredLeases4)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 leases insertion.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, insertLeases6)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 leases update.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, updateLeases6)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 lease retrieval by lease type and IP address.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease6_type_address)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 lease retrieval by lease type, duid and iaid.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease6_type_duid_iaid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 lease retrieval by lease type, duid, iaid and
/// subnet-id.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getLease6_type_duid_iaid_subnetid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures expired IPv6 leases retrieval.
BENCHMARK_REGISTER_F(MemfileLeaseMgrBenchmark, getExpiredLeases6)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

}  // namespace
