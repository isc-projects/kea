// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/benchmarks/generic_host_data_source_benchmark.h>
#include <dhcpsrv/benchmarks/parameters.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/testutils/cql_schema.h>
#include <iostream>

using namespace isc::dhcp::bench;
using namespace isc::dhcp::test;
using namespace isc::dhcp;
using namespace std;

namespace {

/// @brief This is a fixture class used for benchmarking Cassandra host backend
class CqlHostDataSourceBenchmark : public GenericHostDataSourceBenchmark {
public:

    /// @brief Setup routine.
    ///
    /// It cleans up schema and recreates tables, then instantiates HostMgr
    void SetUp(::benchmark::State const&) override {
        destroyCqlSchema(false, true);
        createCqlSchema(false, true);
        try {
            HostDataSourceFactory::destroy();
            HostDataSourceFactory::create(validCqlConnectionString());
        } catch (...) {
            cerr << "ERROR: unable to open database" << endl;
            throw;
        }
        hdsptr_ = HostDataSourceFactory::getHostDataSourcePtr();
    }

    /// @brief Cleans up after the test.
    void TearDown(::benchmark::State const&) override {
        try {
            hdsptr_->rollback();
        } catch (...) {
            cerr << "WARNING: rollback has failed, this is expected if database"
                    " is opened in read-only mode, continuing..."
                 << endl;
        }
        HostDataSourceFactory::destroy();
        destroyCqlSchema(false, true);
    }
};

/// Defines steps necessary for conducting a benchmark that measures
/// hosts insertion.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, insertHosts)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUp(state, host_count);
        insertHosts();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts update.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, updateHosts)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        updateHosts();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by getAll(hw-addr, duid) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, getAllByHWAddrDuid)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGetAllByHWAddrDuid();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by getAll4(hw-addr, duid) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, getAll)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGetAll();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by getAll(v4-reservation) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, getAllv4Resv)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        getAllv4Resv();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get4(subnet-id, hw-addr, duid) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get4BySubnetHWAddrDuid)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet4BySubnetHWAddrDuid();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get4(identifier-type, identifier, subnet-id) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get4IdentifierSubnetId)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet4IdentifierSubnetId();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get4(subnet-id, v4-reservation) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get4SubnetIdv4Resrv)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet4SubnetIdv4Resrv();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get6(subnet-id, duid, hw-addr) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get6SubnetIdDuidHWAddr)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6SubnetIdDuidHWAddr();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get6(subnet-id, identifier-type, identifier) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get6IdentifierSubnetId)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6IdentifierSubnetId();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get6(subnet-id, ip-address) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get6SubnetIdAddr)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6SubnetIdAddr();
    }
}

/// Defines steps necessary for conducting a benchmark that measures
/// hosts retrieval by get6(ip-prefix, prefix-len) call.
BENCHMARK_DEFINE_F(CqlHostDataSourceBenchmark, get6Prefix)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6Prefix();
    }
}

/// Defines parameters necessary for running a benchmark that measures
/// hosts insertion.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, insertHosts)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts update.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, updateHosts)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by getAll(hw-addr, duid) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, getAllByHWAddrDuid)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by getAll4(hw-addr, duid) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, getAll)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by getAll(v4-reservation) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, getAllv4Resv)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get4(subnet-id, hw-addr, duid) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get4BySubnetHWAddrDuid)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get4(identifier-type, identifier, subnet-id) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get4IdentifierSubnetId)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get4(subnet-id, v4-reservation) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get4SubnetIdv4Resrv)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get6(subnet-id, duid, hw-addr) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get6SubnetIdDuidHWAddr)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get6(subnet-id, identifier-type, identifier) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get6IdentifierSubnetId)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get6(subnet-id, ip-address) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get6SubnetIdAddr)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

/// Defines parameters necessary for running a benchmark that measures
/// hosts retrieval by get6(ip-prefix, prefix-len) call.
BENCHMARK_REGISTER_F(CqlHostDataSourceBenchmark, get6Prefix)
    ->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

}  // namespace
