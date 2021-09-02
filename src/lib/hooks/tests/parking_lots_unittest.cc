// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/parking_lots.h>
#include <boost/weak_ptr.hpp>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::hooks;

namespace {

// Defines a pointer to a string. The tests use shared pointers
// as parked objects to ensure key matching works correctly with
// them.  We're doing this because real-world use parked objects
// are typically pointers to packets.
typedef boost::shared_ptr<std::string> StringPtr;

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

    EXPECT_EQ(0, parking_lot0->size());
    EXPECT_EQ(0, parking_lot1->size());
    EXPECT_EQ(0, parking_lot2->size());

    EXPECT_FALSE(parking_lot0 == parking_lot1);
    EXPECT_TRUE(parking_lot0 == parking_lot2);

    ASSERT_NO_THROW(parking_lots.clear());

    ParkingLotPtr parking_lot3 = parking_lots.getParkingLotPtr(1);
    ASSERT_TRUE(parking_lot3);

    EXPECT_FALSE(parking_lot3 == parking_lot0);
}

// Verify that an object can be parked.
TEST(ParkingLotsTest, park) {
    ParkingLot parking_lot;

    // Create object to park.
    StringPtr parked_object(new std::string("foo"));

    // Verify that we can park an object that has not been parked.
    ASSERT_NO_THROW(parking_lot.park(parked_object, [] {}));

    EXPECT_EQ(1, parking_lot.size());

    // Verify that we cannot park an object that has been parked
    EXPECT_THROW(parking_lot.park(parked_object, [] {}),
                 InvalidOperation);
}

// Verify that an object can be referenced.
TEST(ParkingLotsTest, reference) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    // Create an object.
    StringPtr parked_object(new std::string("foo"));

    // Cannot reference an object that has not been parked.
    ASSERT_THROW(parking_lot_handle->reference(parked_object),
                 InvalidOperation);

    // Park the object.
    ASSERT_NO_THROW(parking_lot->park(parked_object, [] {}));

    EXPECT_EQ(1, parking_lot->size());

    // Reference the object. Reference count should one.
    int ref_count = 0;
    ASSERT_NO_THROW(ref_count = parking_lot_handle->reference(parked_object));
    ASSERT_EQ(1, ref_count);

    // Reference the object again. Reference count should two.
    ASSERT_NO_THROW(ref_count = parking_lot_handle->reference(parked_object));
    ASSERT_EQ(2, ref_count);

    EXPECT_EQ(1, parking_lot->size());
}

// Test that object can be parked and then unparked.
TEST(ParkingLotsTest, unpark) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    StringPtr parked_object(new std::string("foo"));

    // Unparking should return false if the object isn't parked.
    EXPECT_FALSE(parking_lot->unpark(parked_object));

    EXPECT_EQ(0, parking_lot->size());

    // This flag will indicate if the callback has been called.
    bool unparked = false;

    ASSERT_NO_THROW(parking_lot->park(parked_object, [&unparked] {
        unparked = true;
    }));

    EXPECT_EQ(1, parking_lot->size());

    // Reference the parked object twice because we're going to test that
    // reference counting works fine.
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));

    EXPECT_EQ(1, parking_lot->size());

    // Try to unpark the object. It should decrease the reference count, but not
    // unpark the packet yet.
    EXPECT_TRUE(parking_lot_handle->unpark(parked_object));
    EXPECT_FALSE(unparked);

    EXPECT_EQ(1, parking_lot->size());

    // Try to unpark the object. This time it should be successful, because the
    // reference count goes to 0.
    EXPECT_TRUE(parking_lot_handle->unpark(parked_object));
    EXPECT_TRUE(unparked);

    EXPECT_EQ(0, parking_lot->size());

    // Calling unpark again should return false to indicate that the object is
    // not parked.
    EXPECT_FALSE(parking_lot_handle->unpark(parked_object));

    EXPECT_EQ(0, parking_lot->size());
}

// Test that parked object can be dropped.
TEST(ParkingLotsTest, drop) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    StringPtr parked_object(new std::string("foo"));

    // This flag will indicate if the callback has been called.
    bool unparked = false;
    ASSERT_NO_THROW(parking_lot->park(parked_object, [&unparked] {
        unparked = true;
    }));

    EXPECT_EQ(1, parking_lot->size());

    // Reference object twice to test that dropping the packet ignores
    // reference counting.
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));

    // Drop parked object. The callback should not be invoked.
    EXPECT_TRUE(parking_lot_handle->drop(parked_object));
    EXPECT_FALSE(unparked);

    EXPECT_EQ(0, parking_lot->size());

    // Expect that an attempt to unpark return false, as the object
    // has been dropped.
    EXPECT_FALSE(parking_lot_handle->unpark(parked_object));
}

// Test that parked lots can be cleared.
TEST(ParkingLotsTest, clear) {
    ParkingLotsPtr parking_lots = boost::make_shared<ParkingLots>();
    ParkingLotPtr parking_lot = parking_lots->getParkingLotPtr(1234);
    ASSERT_TRUE(parking_lot);
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    boost::shared_ptr<std::string> parked_object =
        boost::make_shared<std::string>("foo");
    boost::weak_ptr<std::string> weak_parked_object(parked_object);

    // This flag will indicate if the callback has been called.
    bool unparked = false;
    ASSERT_NO_THROW(parking_lot->park(parked_object, [&unparked] {
        unparked = true;
    }));

    // Reference object twice to test that clearing the parking lots
    // ignores reference counting.
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));
    ASSERT_NO_THROW(parking_lot_handle->reference(parked_object));

    // Drop reference on objects.
    parking_lot.reset();
    parking_lot_handle.reset();
    parked_object.reset();

    // The parked object is still alive.
    EXPECT_FALSE(weak_parked_object.expired());

    // Clear the parking lots.
    ASSERT_NO_THROW(parking_lots->clear());

    // The callback should not be invoked.
    EXPECT_FALSE(unparked);

    // The parked object was destroyed.
    EXPECT_TRUE(weak_parked_object.expired());
}

// Verify that an object can be dereferenced.
TEST(ParkingLotsTest, dereference) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    // Create an object.
    StringPtr parked_object(new std::string("foo"));

    // Verify that an object that hasn't been parked, cannot be
    // dereferenced.
    ASSERT_THROW(parking_lot_handle->dereference(parked_object),
                 InvalidOperation);

    // Park the object.
    // This flag will indicate if the callback has been called.
    bool unparked = false;
    ASSERT_NO_THROW(parking_lot->park(parked_object, [&unparked] {
        unparked = true;
    }));

    EXPECT_EQ(1, parking_lot->size());

    // Reference the parked object twice.
    int ref_count = 0;
    ASSERT_NO_THROW(ref_count = parking_lot_handle->reference(parked_object));
    ASSERT_EQ(1, ref_count);
    ASSERT_NO_THROW(ref_count = parking_lot_handle->reference(parked_object));
    ASSERT_EQ(2, ref_count);

    EXPECT_EQ(1, parking_lot->size());

    // Try to dereference the object. It should decrease the reference count,
    // but not unpark the packet or invoke the callback.
    ASSERT_NO_THROW(ref_count = parking_lot_handle->dereference(parked_object));
    ASSERT_EQ(1, ref_count);
    EXPECT_FALSE(unparked);

    EXPECT_EQ(1, parking_lot->size());

    // Try to dereference the object. It should decrease the reference count,
    // but not unpark the packet or invoke the callback.
    ASSERT_NO_THROW(ref_count = parking_lot_handle->dereference(parked_object));
    ASSERT_EQ(0, ref_count);
    EXPECT_FALSE(unparked);

    EXPECT_EQ(1, parking_lot->size());

    // Try to dereference the object. It should decrement to -1
    // but not unpark the packet or invoke the callback.
    ASSERT_NO_THROW(ref_count = parking_lot_handle->dereference(parked_object));
    EXPECT_EQ(-1, ref_count);
    EXPECT_FALSE(unparked);

    EXPECT_EQ(1, parking_lot->size());

    // Calling unpark should invoke the callback.
    ASSERT_TRUE(parking_lot_handle->unpark(parked_object));
    EXPECT_TRUE(unparked);

    EXPECT_EQ(0, parking_lot->size());
}

// Verify that parked objects are correctly distinguished from
// one another.
TEST(ParkingLotsTest, multipleObjects) {
    ParkingLotPtr parking_lot = boost::make_shared<ParkingLot>();
    ParkingLotHandlePtr parking_lot_handle =
        boost::make_shared<ParkingLotHandle>(parking_lot);

    // Create an object and park it.
    StringPtr object_one(new std::string("one"));
    int unparked_one = 0;
    ASSERT_NO_THROW(parking_lot->park(object_one, [&unparked_one] {
        ++unparked_one;
    }));

    // Create a second object and park it.
    StringPtr object_two(new std::string("two"));
    int unparked_two = 0;
    ASSERT_NO_THROW(parking_lot->park(object_two, [&unparked_two] {
        ++unparked_two;
    }));

    EXPECT_EQ(2, parking_lot->size());

    // Create a third object but don't park it.
    StringPtr object_three(new std::string("three"));

    // Try to unpark object_three. It should fail, and no callbacks
    // should get invoked.
    EXPECT_FALSE(parking_lot_handle->unpark(object_three));
    EXPECT_EQ(unparked_one, 0);
    EXPECT_EQ(unparked_two, 0);

    EXPECT_EQ(2, parking_lot->size());

    // Unpark object one.  It should succeed and its callback should
    // get invoked.
    EXPECT_TRUE(parking_lot_handle->unpark(object_one));
    EXPECT_EQ(unparked_one, 1);
    EXPECT_EQ(unparked_two, 0);

    EXPECT_EQ(1, parking_lot->size());

    // Unpark object two.  It should succeed and its callback should
    // get invoked.
    EXPECT_TRUE(parking_lot_handle->unpark(object_two));
    EXPECT_EQ(unparked_one, 1);
    EXPECT_EQ(unparked_two, 1);

    EXPECT_EQ(0, parking_lot->size());
}

}
