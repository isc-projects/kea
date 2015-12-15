// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <user.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace user_chk;

namespace {

/// @brief Tests User construction variants.
/// Note, since all constructors accept or rely on UserId, invalid id
/// variants are tested under UserId not here.
TEST(UserTest, construction) {
    std::string test_address("01FF02AC030B0709");

    // Create a user id.
    UserIdPtr id;
    ASSERT_NO_THROW(id.reset(new UserId(UserId::HW_ADDRESS, test_address)));

    // Verify construction from a UserId.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(*id)));

    // Verify construction from an id type and an address vector.
    ASSERT_NO_THROW(user.reset(new User(UserId::HW_ADDRESS, id->getId())));
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, id->getId())));

    // Verify construction from an id type and an address string.
    ASSERT_NO_THROW(user.reset(new User(UserId::HW_ADDRESS, test_address)));
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, test_address)));
}

/// @brief Tests property map fundamentals.
TEST(UserTest, properties) {
    // Create a user.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, "01020304050607")));

    // Verify that we can add and retrieve a property.
    std::string value = "";
    EXPECT_NO_THROW(user->setProperty("one","1"));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_EQ("1", value);

    // Verify that we can update and then retrieve the property.
    EXPECT_NO_THROW(user->setProperty("one","1.0"));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_EQ("1.0", value);

    // Verify that we can remove and then NOT find the property.
    EXPECT_NO_THROW(user->delProperty("one"));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_TRUE(value.empty());

    // Verify that a blank property name is NOT permitted.
    EXPECT_THROW(user->setProperty("", "blah"), isc::BadValue);

    // Verify that a blank property value IS permitted.
    EXPECT_NO_THROW(user->setProperty("one", ""));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_TRUE(value.empty());

    PropertyMap map;
    map["one"]="1.0";
    map["two"]="2.0";

    ASSERT_NO_THROW(user->setProperties(map));

    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_EQ("1.0", value);

    EXPECT_NO_THROW(value = user->getProperty("two"));
    EXPECT_EQ("2.0", value);

    const PropertyMap& map2 = user->getProperties();
    EXPECT_TRUE(map2 == map);
}

} // end of anonymous namespace
