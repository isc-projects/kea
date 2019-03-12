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

#ifndef GENERIC_LEASE_MGR_BENCHMARK_H
#define GENERIC_LEASE_MGR_BENCHMARK_H

#include <benchmark/benchmark.h>

#include <dhcpsrv/lease_mgr.h>

namespace isc {
namespace dhcp {
namespace bench {

/// @brief A base class for a fixture for specific lease manager benchmarks
class GenericLeaseMgrBenchmark : public benchmark::Fixture {
public:
    /// Specifies the IP protocol family to be bested.
    enum Universe { V4, V6 };

    /// Constructor
    GenericLeaseMgrBenchmark();

    /// Virtual destructor
    virtual ~GenericLeaseMgrBenchmark();

    /// @brief set up code for initializing IPv4 version of a benchmark
    ///
    /// @param state state to be passed to SetUp
    /// @param lease_count number of leases to be tested
    void setUp4(::benchmark::State& state, size_t const& lease_count);

    /// @brief set up code (with lease preinsertion) for initializing IPv4
    /// version of a benchmark.
    ///
    /// @param state state to be passed to SetUp
    /// @param lease_count number of leases to be tested
    void setUpWithInserts4(::benchmark::State& state, size_t const& lease_count);

    /// @brief set up code for initializing IPv6 version of a benchmark
    ///
    /// @param state state to be passed to SetUp
    /// @param lease_count number of leases to be tested
    void setUp6(::benchmark::State& state, size_t const& lease_count);

    /// @brief set up code (with lease preinsertion) for initializing IPv6
    /// version of a benchmark.
    ///
    /// @param state state to be passed to SetUp
    /// @param lease_count number of leases to be tested
    void setUpWithInserts6(::benchmark::State& state, size_t const& lease_count);

    /// @brief Prepares specified number of IPv4 leases
    ///
    /// The leases are stored in leases4_ container.
    /// @param lease_count specifies the number of leases to be created.
    void prepareLeases4(size_t const& lease_count);

    /// @brief This step inserts all IPv4 leases stored in lease4_ into the LeaseMgr.
    void benchInsertLeases4();

    /// @brief This step updates all IPv4 leases stored in lease4_ in the LeaseMgr.
    void benchUpdateLeases4();

    /// @brief This step retrieves IPv4 leases by IP address.
    void benchGetLease4_address();

    /// @brief This step retrieves IPv4 leases by hardware address.
    void benchGetLease4_hwaddr();

    /// @brief This step retrieves IPv4 leases by (hwaddr, subnet-id) tuple.
    void benchGetLease4_hwaddr_subnetid();

    /// @brief This step retrieves IPv4 leases by client-id.
    void benchGetLease4_clientid();

    /// @brief This step retrieves IPv4 leases by (client-id, subnet-id) tuple.
    void benchGetLease4_clientid_subnetid();

    /// @brief This step retrieves all expired IPv4 leases.
    void benchGetExpiredLeases4();

    /// @brief Prepares specified number of IPv6 leases
    ///
    /// The leases are stored in leases6_ container.
    /// @param lease_count specifies the number of leases to be created.
    void prepareLeases6(size_t const& lease_count);

    /// @brief This step inserts all IPv6 leases stored in lease6_ into the LeaseMgr.
    void benchInsertLeases6();

    /// @brief This step updates all IPv6 leases stored in lease6_ in the LeaseMgr.
    void benchUpdateLeases6();

    /// @brief This step retrieves IPv6 leases by IP address.
    void benchGetLease6_type_address();

    /// @brief This step retrieves IPv6 leases by (type, duid, iaid) tuple.
    void benchGetLease6_type_duid_iaid();

    /// @brief This step retrieves IPv6 leases by (type, duid, iaid, subnet-id) tuple.
    void benchGetLease6_type_duid_iaid_subnetid();

    /// @brief This step retrieves all expired IPv6 leases.
    void benchGetExpiredLeases6();

    /// Pointer to the lease manager being under evaluation.
    LeaseMgr* lmptr_;

    /// List of IPv4 leases (useful during benchmarks)
    Lease4Collection leases4_;

    /// List of IPv6 leases (useful during benchmarks)
    Lease6Collection leases6_;
};

}  // namespace bench
}  // namespace dhcp
}  // namespace isc

#endif
