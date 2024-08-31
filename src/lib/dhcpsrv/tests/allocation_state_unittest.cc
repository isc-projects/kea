// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
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
    EXPECT_TRUE(state.getLastAllocatedTime().is_neg_infinity());
}

// Tests that the explicitly initialized allocation time can be retrieved.
TEST(SubnetAllocationState, getLastAllocatedTime) {
    NakedSubnetAllocationState state;
    date gdate(greg_year(2002), greg_month(1), greg_day(20));

    time_duration t(22, 59, 59, 0);
    ptime pt = ptime(gdate, t);

    state.last_allocated_time_= pt;

    EXPECT_EQ(pt, state.getLastAllocatedTime());
}

// Tests that the explicitly initialized allocation time can be retrieved.
// Multi threaded variant.
TEST(SubnetAllocationState, getLastAllocatedTimeMultiThreading) {
    MultiThreadingTest mt(true);

    NakedSubnetAllocationState state;
    date gdate(greg_year(2002), greg_month(1), greg_day(20));

    time_duration t(22, 59, 59, 0);
    ptime pt = ptime(gdate, t);

    state.last_allocated_time_ = pt;

    EXPECT_EQ(pt, state.getLastAllocatedTime());
}

// Test that current allocation time is set.
TEST(SubnetAllocationState, setCurrentAllocatedTime) {
    NakedSubnetAllocationState state;

    state.setCurrentAllocatedTimeInternal();
    auto pt = state.getLastAllocatedTime();
    auto duration = pt - microsec_clock::universal_time();
    EXPECT_LT(duration.seconds(), 10);
}

} // end of anonymous namespace
