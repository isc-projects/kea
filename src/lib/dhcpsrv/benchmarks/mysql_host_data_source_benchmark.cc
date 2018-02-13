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
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/testutils/mysql_schema.h>

#include <iostream>

using isc::dhcp::bench::GenericHostDataSourceBenchmark;
using isc::dhcp::test::createMySQLSchema;
using isc::dhcp::test::destroyMySQLSchema;
using isc::dhcp::HostDataSourceFactory;
using isc::dhcp::test::validMySQLConnectionString;
using std::cerr;
using std::endl;

namespace {

class MySqlHostDataSourceBenchmark : public GenericHostDataSourceBenchmark {
public:
    void SetUp(::benchmark::State const&) override {
        destroyMySQLSchema(false);
        createMySQLSchema(false);
        try {
            HostDataSourceFactory::destroy();
            HostDataSourceFactory::create(validMySQLConnectionString());
        } catch (...) {
            cerr << "ERROR: unable to open database" << endl;
            throw;
        }
        hdsptr_ = HostDataSourceFactory::getHostDataSourcePtr();
    }

    void TearDown(::benchmark::State const&) override {
        try {
            hdsptr_->rollback();
        } catch (...) {
            cerr << "WARNING: rollback has failed, this is expected if database"
                    " is opened in read-only mode, continuing..."
                 << endl;
        }
        HostDataSourceFactory::destroy();
        destroyMySQLSchema(false);
    }
};

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, insertHosts)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUp(state, host_count);
        insertHosts();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, updateHosts)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        updateHosts();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, getAllByHWAddrDuid)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGetAllByHWAddrDuid();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, getAll)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGetAll();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, getAllv4Resv)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        getAllv4Resv();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get4BySubnetHWAddrDuid)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet4BySubnetHWAddrDuid();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get4IdentifierSubnetId)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet4IdentifierSubnetId();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get4SubnetIdv4Resrv)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet4SubnetIdv4Resrv();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get6SubnetIdDuidHWAddr)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6SubnetIdDuidHWAddr();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get6IdentifierSubnetId)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6IdentifierSubnetId();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get6SubnetIdAddr)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6SubnetIdAddr();
    }
}

BENCHMARK_DEFINE_F(MySqlHostDataSourceBenchmark, get6Prefix)(benchmark::State& state) {
    const size_t host_count = state.range(0);
    while (state.KeepRunning()) {
        setUpWithInserts(state, host_count);
        benchGet6Prefix();
    }
}

constexpr size_t MIN_HOST_COUNT = 512;
constexpr size_t MAX_HOST_COUNT = 0xfffd;
constexpr benchmark::TimeUnit UNIT = benchmark::kMicrosecond;

BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, insertHosts)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, updateHosts)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, getAllByHWAddrDuid)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, getAll)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, getAllv4Resv)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get4BySubnetHWAddrDuid)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get4IdentifierSubnetId)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get4SubnetIdv4Resrv)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get6SubnetIdDuidHWAddr)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get6IdentifierSubnetId)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get6SubnetIdAddr)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlHostDataSourceBenchmark, get6Prefix)->Range(MIN_HOST_COUNT, MAX_HOST_COUNT)->Unit(UNIT);

}  // namespace
