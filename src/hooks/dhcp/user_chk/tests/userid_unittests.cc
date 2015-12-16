// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Test invalid constructors.
TEST(UserIdTest, invalidConstructors) {
    // Verify that constructor does not allow empty id vector.
    std::vector<uint8_t> empty_bytes;
    ASSERT_THROW(UserId(UserId::HW_ADDRESS, empty_bytes), isc::BadValue);
    ASSERT_THROW(UserId(UserId::DUID, empty_bytes), isc::BadValue);

    // Verify that constructor does not allow empty id string.
    ASSERT_THROW(UserId(UserId::HW_ADDRESS, ""), isc::BadValue);
    ASSERT_THROW(UserId(UserId::DUID, ""), isc::BadValue);
}

/// @brief Test making and using HW_ADDRESS type UserIds
TEST(UserIdTest, hwAddress_type) {
    // Verify text label look up for HW_ADDRESS enum.
    EXPECT_EQ(std::string(UserId::HW_ADDRESS_STR),
              UserId::lookupTypeStr(UserId::HW_ADDRESS));

    // Verify enum look up for HW_ADDRESS text label.
    EXPECT_EQ(UserId::HW_ADDRESS,
              UserId::lookupType(UserId::HW_ADDRESS_STR));

    // Build a test address vector.
    uint8_t tmp[] = { 0x01, 0xFF, 0x02, 0xAC, 0x03, 0x0B, 0x07, 0x08 };
    std::vector<uint8_t> bytes(tmp, tmp + (sizeof(tmp)/sizeof(uint8_t)));

    // Verify construction from an HW_ADDRESS id type and address vector.
    UserIdPtr id;
    ASSERT_NO_THROW(id.reset(new UserId(UserId::HW_ADDRESS, bytes)));
    // Verify that the id can be fetched.
    EXPECT_EQ(id->getType(), UserId::HW_ADDRESS);
    EXPECT_TRUE(bytes == id->getId());

    // Check relational oeprators when a == b.
    UserIdPtr id2;
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::HW_ADDRESS, id->toText())));
    EXPECT_TRUE(*id == *id2);
    EXPECT_FALSE(*id != *id2);
    EXPECT_FALSE(*id < *id2);

    // Check relational oeprators when a < b.
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::HW_ADDRESS,
                                         "01FF02AC030B0709")));
    EXPECT_FALSE(*id == *id2);
    EXPECT_TRUE(*id != *id2);
    EXPECT_TRUE(*id < *id2);

    // Check relational oeprators when a > b.
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::HW_ADDRESS,
                                         "01FF02AC030B0707")));
    EXPECT_FALSE(*id == *id2);
    EXPECT_TRUE(*id != *id2);
    EXPECT_FALSE(*id < *id2);

    // Verify that colon delimiters are ok.
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::HW_ADDRESS,
                                         "01:FF:02:AC:03:0B:07:07")));
    EXPECT_FALSE(*id == *id2);
}

/// @brief Test making and using DUID type UserIds
TEST(UserIdTest, duid_type) {
    // Verify text label look up for DUID enum.
    EXPECT_EQ(std::string(UserId::DUID_STR),
              UserId::lookupTypeStr(UserId::DUID));

    // Verify enum look up for DUID text label.
    EXPECT_EQ(UserId::DUID,
              UserId::lookupType(UserId::DUID_STR));

    // Build a test DUID vector.
    uint8_t tmp[] = { 0x01, 0xFF, 0x02, 0xAC, 0x03, 0x0B, 0x07, 0x08 };
    std::vector<uint8_t> bytes(tmp, tmp + (sizeof(tmp)/sizeof(uint8_t)));

    // Verify construction from an DUID id type and address vector.
    UserIdPtr id;
    ASSERT_NO_THROW(id.reset(new UserId(UserId::DUID, bytes)));
    // Verify that the id can be fetched.
    EXPECT_EQ(id->getType(), UserId::DUID);
    EXPECT_TRUE(bytes == id->getId());

    // Check relational oeprators when a == b.
    UserIdPtr id2;
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::DUID, id->toText())));
    EXPECT_TRUE(*id == *id2);
    EXPECT_FALSE(*id != *id2);
    EXPECT_FALSE(*id < *id2);

    // Check relational oeprators when a < b.
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::DUID, "01FF02AC030B0709")));
    EXPECT_FALSE(*id == *id2);
    EXPECT_TRUE(*id != *id2);
    EXPECT_TRUE(*id < *id2);

    // Check relational oeprators when a > b.
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::DUID, "01FF02AC030B0707")));
    EXPECT_FALSE(*id == *id2);
    EXPECT_TRUE(*id != *id2);
    EXPECT_FALSE(*id < *id2);

    // Verify that colon delimiters are ok.
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::DUID,
                                         "01:FF:02:AC:03:0B:07:08")));
    EXPECT_TRUE(*id == *id2);
}

/// @brief Tests that UserIds of different types compare correctly.
TEST(UserIdTest, mixed_type_compare) {
    UserIdPtr hw, duid;
    // Create UserIds with different types, but same id data.
    ASSERT_NO_THROW(hw.reset(new UserId(UserId::HW_ADDRESS,
                                        "01FF02AC030B0709")));
    ASSERT_NO_THROW(duid.reset(new UserId(UserId::DUID,
                                          "01FF02AC030B0709")));

    // Verify that UserIdType influences logical comparators.
    EXPECT_FALSE(*hw == *duid);
    EXPECT_TRUE(*hw != *duid);
    EXPECT_TRUE(*hw < *duid);
}

} // end of anonymous namespace
