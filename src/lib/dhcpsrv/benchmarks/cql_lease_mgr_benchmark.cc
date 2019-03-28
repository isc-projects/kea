// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2017 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <cql/testutils/cql_schema.h>

#include <dhcpsrv/benchmarks/generic_lease_mgr_benchmark.h>
#include <dhcpsrv/benchmarks/parameters.h>
#include <dhcpsrv/lease_mgr_factory.h>

using namespace isc::db::test;
using namespace isc::dhcp;
using namespace isc::dhcp::bench;
using namespace std;

namespace {

/// @brief This is a fixture class used for benchmarking Cassandra lease backend
class CqlLeaseMgrBenchmark : public GenericLeaseMgrBenchmark {
public:
    /// @brief Setup routine.
    ///
    /// It cleans up schema and recreates tables, then instantiates LeaseMgr
    void SetUp(::benchmark::State const&) override {
        // Ensure we have the proper schema with no transient data.
        createCqlSchema();
        try {
            LeaseMgrFactory::destroy();
            LeaseMgrFactory::create(validCqlConnectionString());
        } catch (...) {
            cerr << "ERROR: unable to open database" << endl;
            throw;
        }
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    void SetUp(::benchmark::State& s) override {
        ::benchmark::State const& cs = s;
        SetUp(cs);
    }

    /// @brief Cleans up after the test.
    void TearDown(::benchmark::State const&) override {
        try {
            lmptr_->rollback();
        } catch (...) {
            cerr << "WARNING: rollback has failed, this is expected if database"
                    " is opened in read-only mode, continuing..."
                 << endl;
        }
        LeaseMgrFactory::destroy();
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyCqlSchema();
    }

    void TearDown(::benchmark::State& s) override {
        ::benchmark::State const& cs = s;
        TearDown(cs);
    }
};

// Defines a benchmark that measures IPv4 leases insertion.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, insertLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUp4(state, lease_count);
        benchInsertLeases4();
    }
}

// Defines a benchmark that measures IPv4 leases update.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, updateLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchUpdateLeases4();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by address.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease4_address)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_address();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by hardware address.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease4_hwaddr)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_hwaddr();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by hardware address
// and subnet-id.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease4_hwaddr_subnetid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_hwaddr_subnetid();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by client-id.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease4_clientid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_clientid();
    }
}

// Defines a benchmark that measures IPv4 leases retrieval by client-id and
// subnet-id.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease4_clientid_subnetid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetLease4_clientid_subnetid();
    }
}

// Defines a benchmark that measures retrieval of expired IPv4 leases.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getExpiredLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts4(state, lease_count);
        benchGetExpiredLeases4();
    }
}

// Defines a benchmark that measures IPv6 leases insertion.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, insertLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUp6(state, lease_count);
        benchInsertLeases6();
    }
}

// Defines a benchmark that measures IPv6 leases update.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, updateLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchUpdateLeases6();
    }
}

// Defines a benchmark that measures IPv6 leases retrieval by type and address.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease6_type_address)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetLease6_type_address();
    }
}

// Defines a benchmark that measures IPv6 leases retrieval by type, duid and iaid.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease6_type_duid_iaid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetLease6_type_duid_iaid();
    }
}

// Defines a benchmark that measures IPv6 leases retrieval by lease type, duid, iaid
// and subnet-id.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getLease6_type_duid_iaid_subnetid)
                  (benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetLease6_type_duid_iaid_subnetid();
    }
}

// Defines a benchmark that measures retrieval of expired IPv6 leases.
BENCHMARK_DEFINE_F(CqlLeaseMgrBenchmark, getExpiredLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts6(state, lease_count);
        benchGetExpiredLeases6();
    }
}

/// The following macros define run parameters for previously defined
/// Cassandra benchmarks.

/// A benchmark that measures IPv4 leases insertion.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, insertLeases4)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 leases update.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, updateLeases4)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by IP address.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease4_address)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by hardware address.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease4_hwaddr)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by hardware address and a
/// subnet-id.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease4_hwaddr_subnetid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by client-id.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease4_clientid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv4 lease retrieval by client-id and subnet-id.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease4_clientid_subnetid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures expired IPv4 leases retrieval.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getExpiredLeases4)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 leases insertion.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, insertLeases6)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 leases update.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, updateLeases6)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 lease retrieval by lease type and IP address.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease6_type_address)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 lease retrieval by lease type, duid and iaid.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease6_type_duid_iaid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures IPv6 lease retrieval by lease type, duid, iaid and
/// subnet-id.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getLease6_type_duid_iaid_subnetid)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

/// A benchmark that measures expired IPv6 leases retrieval.
BENCHMARK_REGISTER_F(CqlLeaseMgrBenchmark, getExpiredLeases6)
    ->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

}  // namespace
