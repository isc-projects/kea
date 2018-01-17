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

#include <dhcpsrv/benchmarks/generic_lease_mgr_benchmark.h>

#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/testutils/cql_schema.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using isc::asiolink::IOAddress;
using isc::dhcp::test::createCqlSchema;
using isc::dhcp::test::destroyCqlSchema;
using isc::dhcp::test::validCqlConnectionString;

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::cerr;
using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::stringstream;
using std::to_string;
using std::vector;

namespace isc {
namespace dhcp {
namespace bench {

GenericLeaseMgrBenchmark::GenericLeaseMgrBenchmark() : lmptr_(NULL) {
}

GenericLeaseMgrBenchmark::~GenericLeaseMgrBenchmark() {
}

void
GenericLeaseMgrBenchmark::ReentrantSetUp4(::benchmark::State& state,
                                              size_t const& lease_count) {
    state.PauseTiming();
    SetUp(state);
    prepareLeases4(lease_count);
    state.ResumeTiming();
}

void
GenericLeaseMgrBenchmark::ReentrantSetUpWithInserts4(
    ::benchmark::State& state, size_t const& lease_count) {
    state.PauseTiming();
    SetUp(state);
    prepareLeases4(lease_count);
    insertLeases4();
    state.ResumeTiming();
}

void
GenericLeaseMgrBenchmark::ReentrantSetUp6(::benchmark::State& state,
                                              size_t const& lease_count) {
    state.PauseTiming();
    SetUp(state);
    prepareLeases6(lease_count);
    state.ResumeTiming();
}

void
GenericLeaseMgrBenchmark::ReentrantSetUpWithInserts6(
    ::benchmark::State& state, size_t const& lease_count) {
    state.PauseTiming();
    SetUp(state);
    prepareLeases6(lease_count);
    insertLeases6();
    state.ResumeTiming();
}

void
GenericLeaseMgrBenchmark::prepareLeases4(size_t const& lease_count) {
    leases4_.clear();
    for (size_t i = 0x0001u; i < 0x0001u + lease_count; ++i) {
        Lease4Ptr lease(new Lease4());
        lease->addr_ = IOAddress(i);
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, i), HTYPE_ETHER));
        lease->client_id_ =
            ClientIdPtr(new ClientId(vector<uint8_t>(8, 2 * i)));
        lease->valid_lft_ = i;
        lease->cltt_ = i;
        lease->subnet_id_ = i;
        lease->fqdn_rev_ = (i % 2) ? true : false;
        lease->fqdn_fwd_ = (i % 2) ? true : false;
        lease->hostname_ = to_string(i) + ".host.com";
        leases4_.push_back(lease);
    }
}

void
GenericLeaseMgrBenchmark::insertLeases4() {
    for (Lease4Ptr const& lease : leases4_) {
        lmptr_->addLease(lease);
    }
}

void
GenericLeaseMgrBenchmark::updateLeases4() {
    for (Lease4Ptr const& lease : leases4_) {
        lmptr_->updateLease4(lease);
    }
}

void
GenericLeaseMgrBenchmark::getLease4_address() {
    for (Lease4Ptr const& lease : leases4_) {
        lmptr_->getLease4(lease->addr_);
    }
}

void
GenericLeaseMgrBenchmark::getLease4_hwaddr() {
    for (Lease4Ptr const& lease : leases4_) {
        const Lease4Collection collection = lmptr_->getLease4(*lease->hwaddr_);
    }
}

void
GenericLeaseMgrBenchmark::getLease4_hwaddr_subnetid() {
    for (Lease4Ptr const& lease : leases4_) {
        lmptr_->getLease4(*lease->hwaddr_, lease->subnet_id_);
    }
}

void
GenericLeaseMgrBenchmark::getLease4_clientid() {
    for (Lease4Ptr const& lease : leases4_) {
        lmptr_->getLease4(*lease->client_id_);
    }
}

void
GenericLeaseMgrBenchmark::getLease4_clientid_subnetid() {
    for (Lease4Ptr const& lease : leases4_) {
        lmptr_->getLease4(*lease->client_id_, lease->subnet_id_);
    }
}

void
GenericLeaseMgrBenchmark::getExpiredLeases4() {
    Lease4Collection expired_leases;
    lmptr_->getExpiredLeases4(expired_leases, leases4_.size());
}

/*
 *  Calls that aren't measured:
 *      * deleteLease(const Lease4Ptr& lease);
 *      * deleteLease(const Lease6Ptr& lease);
 *      * deleteExpiredReclaimedLeases4(const uint32_t secs);
 */

void
GenericLeaseMgrBenchmark::prepareLeases6(size_t const& lease_count) {
    if (lease_count > 0xfffdu) {
        cerr << "lease_count <= 0xfffd or change address generation in "
                "GenericLeaseMgrBenchmark::prepareLeases6()"
             << endl;
    }
    leases6_.clear();
    for (size_t i = 0x0001u; i < 0x0001u + lease_count; ++i) {
        stringstream ss;
        string n_lease;
        ss << std::hex << i;
        ss >> n_lease;
        const string prefix = string("2001:db8::") + n_lease;
        Lease6Ptr lease(new Lease6());
        lease->addr_ = IOAddress(prefix);
        lease->t1_ = i;
        lease->t2_ = i;
        lease->type_ = static_cast<Lease::Type>(i % 3);  // NA, TA or PD
        lease->prefixlen_ = i % 128;
        lease->iaid_ = i;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, i)));
        lease->preferred_lft_ = i;
        lease->valid_lft_ = i;
        lease->cltt_ = i;
        lease->subnet_id_ = i;
        lease->fqdn_fwd_ = (i % 2 == 0) ? true : false;
        lease->fqdn_rev_ = (i % 2 == 0) ? true : false;
        lease->hostname_ = n_lease + ".host.com";
        leases6_.push_back(lease);
    }
}

void
GenericLeaseMgrBenchmark::insertLeases6() {
    for (Lease6Ptr const& lease : leases6_) {
        lmptr_->addLease(lease);
    }
}

void
GenericLeaseMgrBenchmark::updateLeases6() {
    for (Lease6Ptr const& lease : leases6_) {
        lmptr_->updateLease6(lease);
    }
}

void
GenericLeaseMgrBenchmark::getLease6_type_address() {
    for (Lease6Ptr const& lease : leases6_) {
        lmptr_->getLease6(lease->type_, lease->addr_);
    }
}

void
GenericLeaseMgrBenchmark::getLease6_type_duid_iaid() {
    for (Lease6Ptr const& lease : leases6_) {
        lmptr_->getLeases6(lease->type_, *lease->duid_, lease->iaid_);
    }
}

void
GenericLeaseMgrBenchmark::getLease6_type_type_duid_iaid_subnetid() {
    for (Lease6Ptr const& lease : leases6_) {
        lmptr_->getLease6(lease->type_, *lease->duid_, lease->iaid_,
                          lease->subnet_id_);
    }
}

void
GenericLeaseMgrBenchmark::getExpiredLeases6() {
    Lease6Collection expired_leases;
    lmptr_->getExpiredLeases6(expired_leases, leases6_.size());
}

/*
 *   Calls that aren't measured:
 *      * deleteLease(const Lease4Ptr& lease);
 *      * deleteLease(const Lease6Ptr& lease);
 *      * deleteExpiredReclaimedLeases6(const uint32_t secs);
 */

}  // namespace bench
}  // namespace dhcp
}  // namespace isc
