// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/lease.h>
#include <testutils/multi_threading_utils.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

/// @brief Derivation of the @c SubnetAllocationState with protected
/// members and method exposed.
class NakedSubnetAllocationState : public SubnetAllocationState {
public:

    using SubnetAllocationState::setCurrentAllocatedTimeInternal;
    using SubnetAllocationState::last_allocated_time_;

};

// Tests initialization of the SubnetAllocationState.
TEST(SubnetAllocationState, constructor) {
    SubnetAllocationState state;
    EXPECT_TRUE(state.getLastAllocatedTime(Lease::TYPE_V4).is_neg_infinity());
    EXPECT_TRUE(state.getLastAllocatedTime(Lease::TYPE_NA).is_neg_infinity());
    EXPECT_TRUE(state.getLastAllocatedTime(Lease::TYPE_TA).is_neg_infinity());
    EXPECT_TRUE(state.getLastAllocatedTime(Lease::TYPE_PD).is_neg_infinity());
}

// Tests that the explicitly initialized allocation time can be retrieved
// for each lease type.
TEST(SubnetAllocationState, getLastAllocatedTime) {
    NakedSubnetAllocationState state;
    date gdate(greg_year(2002), greg_month(1), greg_day(20));

    time_duration tm_v4(22, 59, 59, 0);
    ptime time_v4 = ptime(gdate, tm_v4);

    time_duration tm_na(12, 59, 59, 0);
    ptime time_na = ptime(gdate, tm_na);

    time_duration tm_ta(14, 59, 59, 0);
    ptime time_ta = ptime(gdate, tm_ta);

    time_duration tm_pd(16, 59, 59, 0);
    ptime time_pd = ptime(gdate, tm_pd);

    state.last_allocated_time_[Lease::TYPE_V4] = time_v4;
    state.last_allocated_time_[Lease::TYPE_NA] = time_na;
    state.last_allocated_time_[Lease::TYPE_TA] = time_ta;
    state.last_allocated_time_[Lease::TYPE_PD] = time_pd;

    EXPECT_EQ(time_v4, state.getLastAllocatedTime(Lease::TYPE_V4));
    EXPECT_EQ(time_na, state.getLastAllocatedTime(Lease::TYPE_NA));
    EXPECT_EQ(time_ta, state.getLastAllocatedTime(Lease::TYPE_TA));
    EXPECT_EQ(time_pd, state.getLastAllocatedTime(Lease::TYPE_PD));
}

// Tests that the explicitly initialized allocation time can be retrieved
// for each lease type. Multi threaded variant.
TEST(SubnetAllocationState, getLastAllocatedTimeMultiThreading) {
    MultiThreadingTest mt(true);

    NakedSubnetAllocationState state;
    date gdate(greg_year(2002), greg_month(1), greg_day(20));

    time_duration tm_v4(22, 59, 59, 0);
    ptime time_v4 = ptime(gdate, tm_v4);

    time_duration tm_na(12, 59, 59, 0);
    ptime time_na = ptime(gdate, tm_na);

    time_duration tm_ta(14, 59, 59, 0);
    ptime time_ta = ptime(gdate, tm_ta);

    time_duration tm_pd(16, 59, 59, 0);
    ptime time_pd = ptime(gdate, tm_pd);

    state.last_allocated_time_[Lease::TYPE_V4] = time_v4;
    state.last_allocated_time_[Lease::TYPE_NA] = time_na;
    state.last_allocated_time_[Lease::TYPE_TA] = time_ta;
    state.last_allocated_time_[Lease::TYPE_PD] = time_pd;

    EXPECT_EQ(time_v4, state.getLastAllocatedTime(Lease::TYPE_V4));
    EXPECT_EQ(time_na, state.getLastAllocatedTime(Lease::TYPE_NA));
    EXPECT_EQ(time_ta, state.getLastAllocatedTime(Lease::TYPE_TA));
    EXPECT_EQ(time_pd, state.getLastAllocatedTime(Lease::TYPE_PD));
}

// Test that current allocation time is set for an IPv4 lease.
TEST(SubnetAllocationState, setCurrentAllocatedTimeV4) {
    NakedSubnetAllocationState state;

    state.setCurrentAllocatedTimeInternal(Lease::TYPE_V4);
    auto time_v4 = state.getLastAllocatedTime(Lease::TYPE_V4);
    auto duration = time_v4 - microsec_clock::universal_time();
    EXPECT_LT(duration.seconds(), 10);
}

// Test that current allocation time is set for an IPv6 address.
TEST(SubnetAllocationState, setCurrentAllocatedTimeNA) {
    NakedSubnetAllocationState state;

    state.setCurrentAllocatedTimeInternal(Lease::TYPE_NA);
    auto time_na = state.getLastAllocatedTime(Lease::TYPE_NA);
    auto duration = time_na - microsec_clock::universal_time();
    EXPECT_LT(duration.seconds(), 10);
}

// Test that current allocation time is set for an IPv6 temporary address.
TEST(SubnetAllocationState, setCurrentAllocatedTimeTA) {
    NakedSubnetAllocationState state;

    state.setCurrentAllocatedTimeInternal(Lease::TYPE_TA);
    auto time_ta = state.getLastAllocatedTime(Lease::TYPE_TA);
    auto duration = time_ta - microsec_clock::universal_time();
    EXPECT_LT(duration.seconds(), 10);
}

// Test that current allocation time is set for a delegated prefix.
TEST(SubnetAllocationState, setCurrentAllocatedTimePD) {
    NakedSubnetAllocationState state;

    state.setCurrentAllocatedTimeInternal(Lease::TYPE_PD);
    auto time_pd = state.getLastAllocatedTime(Lease::TYPE_PD);
    auto duration = time_pd - microsec_clock::universal_time();
    EXPECT_LT(duration.seconds(), 10);
}

} // end of anonymous namespace
