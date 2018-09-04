// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/parking_lots.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::hooks;

namespace {

// Test that it is possible to create and retrieve parking lots for
// specified hook points.
TEST(ParkingLotsTest, createGetParkingLot) {
    ParkingLots parking_lots;

    ParkingLotPtr parking_lot0 = parking_lots.getParkingLotPtr(1);
    ParkingLotPtr parking_lot1 = parking_lots.getParkingLotPtr(2);
    ParkingLotPtr parking_lot2 = parking_lots.getParkingLotPtr(1);

    ASSERT_TRUE(parking_lot0);
    ASSERT_TRUE(parking_lot1);
    ASSERT_TRUE(parking_lot2);

    EXPECT_FALSE(parking_lot0 == parking_lot1);
    EXPECT_TRUE(parking_lot0 == parking_lot2);

    ASSERT_NO_THROW(parking_lots.clear());

    ParkingLotPtr parking_lot3 = parking_lots.getParkingLotPtr(1);
    ASSERT_TRUE(parking_lot3);

    EXPECT_FALSE(parking_lot3 == parking_lot0);
}

// Test that object can't be parked if it hasn't been referenced on the
// parking lot.
TEST(ParkingLotTest, parkWithoutReferencing) {
    ParkingLot parking_lot;
    std::string parked_object = "foo";
    EXPECT_THROW(parking_lot.park(parked_object, [] {
    }), InvalidOperation);
}

// Test that object can be parked and then unparked.
TEST(ParkingLotTest, unpark) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    std::string parked_object = "foo";

    // Reference the parked object twice because we're going to test that
    // reference counting works fine.
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));

    // This flag will indicate if the callback has been called.
    bool unparked = false;
    ASSERT_NO_THROW(parking_lot->park(parked_object, [&unparked] {
        unparked = true;
    }));

    // Try to unpark the object. It should decrease the reference count, but not
    // unpark the packet yet.
    EXPECT_TRUE(parking_lot_handle->unpark(parked_object));
    EXPECT_FALSE(unparked);

    // Try to unpark the object. This time it should be successful, because the
    // reference count goes to 0.
    EXPECT_TRUE(parking_lot_handle->unpark(parked_object));
    EXPECT_TRUE(unparked);

    // Calling unpark again should return false to indicate that the object is
    // not parked.
    EXPECT_FALSE(parking_lot_handle->unpark(parked_object));
}

// Test that parked object can be dropped.
TEST(ParkingLotTest, drop) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    std::string parked_object = "foo";

    // Reference object twice to test that dropping the packet ignores
    // reference counting.
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));

    // This flag will indicate if the callback has been called.
    bool unparked = false;
    ASSERT_NO_THROW(parking_lot->park(parked_object, [&unparked] {
        unparked = true;
    }));

    // Drop parked object. The callback should not be invoked.
    EXPECT_TRUE(parking_lot_handle->drop(parked_object));
    EXPECT_FALSE(unparked);

    // Expect that an attempt to unpark return false, as the object
    // has been dropped.
    EXPECT_FALSE(parking_lot_handle->unpark(parked_object));
}

}
