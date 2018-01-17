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

#ifndef GENERIC_LEASE_MGR_BENCHMARK_H
#define GENERIC_LEASE_MGR_BENCHMARK_H

#include <benchmark/benchmark.h>

#include <dhcpsrv/lease_mgr.h>

namespace isc {
namespace dhcp {
namespace bench {

class GenericLeaseMgrBenchmark : public benchmark::Fixture {
public:
    enum Universe { V4, V6 };

    GenericLeaseMgrBenchmark();
    virtual ~GenericLeaseMgrBenchmark();

    void ReentrantSetUp4(::benchmark::State& state, size_t const& lease_count);
    void ReentrantSetUpWithInserts4(::benchmark::State& state,
                                    size_t const& lease_count);
    void ReentrantSetUp6(::benchmark::State& state, size_t const& lease_count);
    void ReentrantSetUpWithInserts6(::benchmark::State& state,
                                    size_t const& lease_count);
    void prepareLeases4(size_t const& lease_count);

    void insertLeases4();
    void updateLeases4();
    void getLease4_address();
    void getLease4_hwaddr();
    void getLease4_hwaddr_subnetid();
    void getLease4_clientid();
    void getLease4_clientid_subnetid();
    void getExpiredLeases4();

    void prepareLeases6(size_t const& lease_count);
    void insertLeases6();
    void updateLeases6();
    void getLease6_type_address();
    void getLease6_type_duid_iaid();
    void getLease6_type_type_duid_iaid_subnetid();
    void getExpiredLeases6();

    LeaseMgr* lmptr_;
    Lease4Collection leases4_;
    Lease6Collection leases6_;
};

}  // namespace bench
}  // namespace dhcp
}  // namespace isc

#endif
