// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <lease_update_backlog.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>

#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::ha;

namespace {

// This test verifies that lease updates can be pushed to the queue,
// retrieved from the queue.
TEST(LeaseUpdateBacklogTest, pushAndPop) {
    // Create the queue with limit of 5 lease updates.
    LeaseUpdateBacklog backlog(5);

    // Add 5 lease updates.
    for (auto i = 0; i < 5; ++i) {
        IOAddress address(i + 1);
        HWAddrPtr hwaddr = boost::make_shared<HWAddr>(std::vector<uint8_t>(6, static_cast<uint8_t>(i)),
                                                      HTYPE_ETHER);
        Lease4Ptr lease = boost::make_shared<Lease4>(address, hwaddr, ClientIdPtr(), 60, 0, 1);
        // Some lease updates have type "Add", some have type "Delete".
        ASSERT_TRUE(backlog.push(i % 2 ? LeaseUpdateBacklog::ADD : LeaseUpdateBacklog::DELETE, lease));
        EXPECT_FALSE(backlog.wasOverflown());
    }

    // Add 6th lease update. This should exceed the size limit.
    IOAddress address("192.0.2.0");
    HWAddrPtr hwaddr = boost::make_shared<HWAddr>(std::vector<uint8_t>(6, static_cast<uint8_t>(0xA)),
                                                  HTYPE_ETHER);
    Lease4Ptr lease = boost::make_shared<Lease4>(address, hwaddr, ClientIdPtr(), 60, 0, 1);
    ASSERT_FALSE(backlog.push(LeaseUpdateBacklog::ADD, lease));
    EXPECT_TRUE(backlog.wasOverflown());

    // Try to pop all lease updates.
    LeaseUpdateBacklog::OpType op_type;
    for (auto i = 0; i < 5; ++i) {
        auto lease = backlog.pop(op_type);
        ASSERT_TRUE(lease);
        ASSERT_EQ(i % 2 ? LeaseUpdateBacklog::ADD : LeaseUpdateBacklog::DELETE, op_type);
    }

    // When trying to pop from an empty queue it should return null pointer.
    lease = boost::dynamic_pointer_cast<Lease4>(backlog.pop(op_type));
    EXPECT_FALSE(lease);
    EXPECT_TRUE(backlog.wasOverflown());

    // Reset queue state.
    ASSERT_NO_THROW(backlog.clear());
    EXPECT_FALSE(backlog.wasOverflown());
}

// This test verifies that all lease updates can be removed.
TEST(LeaseUpdateBacklogTest, clear) {
    // Create the queue with limit of 5 lease updates.
    LeaseUpdateBacklog backlog(5);

    // Add 5 lease updates.
    for (auto i = 0; i < 3; ++i) {
        IOAddress address(i + 1);
        HWAddrPtr hwaddr = boost::make_shared<HWAddr>(std::vector<uint8_t>(6, static_cast<uint8_t>(i)),
                                                      HTYPE_ETHER);
        Lease4Ptr lease = boost::make_shared<Lease4>(address, hwaddr, ClientIdPtr(), 60, 0, 1);
        ASSERT_TRUE(backlog.push(LeaseUpdateBacklog::ADD, lease));
    }

    // Make sure all lease updates have been added.
    EXPECT_EQ(3, backlog.size());

    // Remove lease updates.
    ASSERT_NO_THROW(backlog.clear());

    // There should be no lease updates.
    EXPECT_EQ(0, backlog.size());
}

} // end of anonymous namespace
