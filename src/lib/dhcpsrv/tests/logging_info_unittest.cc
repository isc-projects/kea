// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/logging_info.h>
#include <gtest/gtest.h>

using namespace isc::dhcp;

namespace {

// Checks if two destinations can be compared for equality.
TEST(LoggingDestintaion, equals) {
    LoggingDestination dest1;
    LoggingDestination dest2;

    EXPECT_TRUE(dest1.equals(dest2));

    dest1.output_ = "stderr";
    EXPECT_FALSE(dest1.equals(dest2));

    dest2.output_ = "stdout";
    EXPECT_FALSE(dest1.equals(dest2));

    dest2.output_ = "stderr";
    EXPECT_TRUE(dest1.equals(dest2));

    dest1.maxver_ = 10;
    dest2.maxver_ = 5;
    EXPECT_FALSE(dest1.equals(dest2));

    dest2.maxver_ = 10;
    EXPECT_TRUE(dest1.equals(dest2));

    dest1.maxsize_ = 64;
    dest2.maxsize_ = 32;
    EXPECT_FALSE(dest1.equals(dest2));

    dest1.maxsize_ = 32;
    EXPECT_TRUE(dest1.equals(dest2));
}

/// @brief Test fixture class for testing @c LoggingInfo.
class LoggingInfoTest : public ::testing::Test {
public:

    /// @brief Setup the test.
    virtual void SetUp() {
        CfgMgr::instance().setVerbose(false);
    }

    /// @brief Clear after the test.
    virtual void TearDown() {
        CfgMgr::instance().setVerbose(false);
    }
};

// Checks if default logging configuration is correct.
TEST_F(LoggingInfoTest, defaults) {
    LoggingInfo info_non_verbose;
    EXPECT_EQ("kea", info_non_verbose.name_);
    EXPECT_EQ(isc::log::INFO, info_non_verbose.severity_);
    EXPECT_EQ(0, info_non_verbose.debuglevel_);

    ASSERT_EQ(1, info_non_verbose.destinations_.size());
    EXPECT_EQ("stdout", info_non_verbose.destinations_[0].output_);

    CfgMgr::instance().setVerbose(true);
    LoggingInfo info_verbose;
    EXPECT_EQ("kea", info_verbose.name_);
    EXPECT_EQ(isc::log::DEBUG, info_verbose.severity_);
    EXPECT_EQ(99, info_verbose.debuglevel_);

    ASSERT_EQ(1, info_verbose.destinations_.size());
    EXPECT_EQ("stdout", info_verbose.destinations_[0].output_);
}

// Checks if (in)equality operators work for LoggingInfo.
TEST_F(LoggingInfoTest, equalityOperators) {
    LoggingInfo info1;
    LoggingInfo info2;

    // Initially, both objects are the same.
    EXPECT_TRUE(info1 == info2);

    // Differ by name.
    info1.name_ = "foo";
    info2.name_ = "bar";
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

    // Names equal.
    info2.name_ = "foo";
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Differ by severity.
    info1.severity_ = isc::log::DEBUG;
    info2.severity_ = isc::log::INFO;
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

    // Severities equal.
    info2.severity_ = isc::log::DEBUG;
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Differ by debug level.
    info1.debuglevel_ = 99;
    info2.debuglevel_ = 1;
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

    // Debug level equal.
    info2.debuglevel_ = 99;
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Create two different desinations.
    LoggingDestination dest1;
    LoggingDestination dest2;
    dest1.output_ = "foo";
    dest2.output_ = "bar";

    // Push destinations in some order to info1.
    info1.destinations_.push_back(dest1);
    info1.destinations_.push_back(dest2);

    // Push in reverse order to info2. Order shouldn't matter.
    info2.destinations_.push_back(dest2);
    info2.destinations_.push_back(dest1);

    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Change one of the destinations.
    LoggingDestination dest3;
    dest3.output_ = "foobar";

    info2.destinations_[2] = dest3;

    // The should now be unequal.
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

}

} // end of anonymous namespace
