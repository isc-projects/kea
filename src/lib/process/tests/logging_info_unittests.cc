// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <process/daemon.h>
#include <process/logging_info.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc::process;
using namespace isc::test;
using namespace isc::data;

namespace {

// Checks if two destinations can be compared for equality.
TEST(LoggingDestination, equals) {
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

    /// @brief Constructor
    LoggingInfoTest() = default;

    /// @brief Destructor
    virtual ~LoggingInfoTest() = default;

    /// @brief Setup the test.
    virtual void SetUp() {
        Daemon::setVerbose(false);
    }

    /// @brief Clear after the test.
    virtual void TearDown() {
        Daemon::setVerbose(false);
    }
};

// Checks if default logging configuration is correct.
TEST_F(LoggingInfoTest, defaults) {

    // We now need to set the default logger explicitly.
    // Otherwise leftovers from previous tests that use DController
    // would leave the default logger set to TestBin.
    Daemon::setDefaultLoggerName("kea");

    LoggingInfo info_non_verbose;

    // The DStubTest framework sets up the default binary name to TestBin
    EXPECT_EQ("kea", info_non_verbose.name_);
    EXPECT_EQ(isc::log::INFO, info_non_verbose.severity_);
    EXPECT_EQ(0, info_non_verbose.debuglevel_);

    ASSERT_EQ(1, info_non_verbose.destinations_.size());
    EXPECT_EQ("stdout", info_non_verbose.destinations_[0].output_);

    std::string header = "{\n";
    std::string begin =
        "\"name\": \"kea\",\n"
        "\"output_options\": [ {\n"
        " \"output\": \"stdout\", \"flush\": true, \"pattern\": \"\" } ],\n"
        "\"severity\": \"";
    std::string dbglvl = "\",\n\"debuglevel\": ";
    std::string trailer = "\n}\n";
    std::string expected = header + begin + "INFO" + dbglvl + "0" + trailer;
    runToElementTest<LoggingInfo>(expected, info_non_verbose);

    // Add a user context
    std::string comment = "\"comment\": \"foo\"";
    std::string user_context = "{ " + comment + " }";
    std::string user_context_nl = "{\n" + comment + "\n}";
    EXPECT_FALSE(info_non_verbose.getContext());
    info_non_verbose.setContext(Element::fromJSON(user_context));
    ASSERT_TRUE(info_non_verbose.getContext());
    EXPECT_EQ(user_context, info_non_verbose.getContext()->str());
    expected = header;
    expected += "\"user-context\": " + user_context_nl + ",\n";
    expected += begin + "INFO" + dbglvl + "0" + trailer;
    runToElementTest<LoggingInfo>(expected, info_non_verbose);

    Daemon::setVerbose(true);
    LoggingInfo info_verbose;
    EXPECT_EQ("kea", info_verbose.name_);
    EXPECT_EQ(isc::log::DEBUG, info_verbose.severity_);
    EXPECT_EQ(99, info_verbose.debuglevel_);

    ASSERT_EQ(1, info_verbose.destinations_.size());
    EXPECT_EQ("stdout", info_verbose.destinations_[0].output_);

    EXPECT_EQ(10240000, info_verbose.destinations_[0].maxsize_);
    EXPECT_EQ(1, info_verbose.destinations_[0].maxver_);

    expected = header + begin + "DEBUG" + dbglvl + "99" + trailer;
    runToElementTest<LoggingInfo>(expected, info_verbose);

    // User comment again
    EXPECT_FALSE(info_verbose.getContext());
    info_verbose.setContext(Element::fromJSON(user_context));
    ASSERT_TRUE(info_verbose.getContext());
    EXPECT_EQ(user_context, info_verbose.getContext()->str());
    expected = header;
    expected += "\"user-context\": " + user_context_nl + ",\n";
    expected += begin + "DEBUG" + dbglvl + "99" + trailer;
    runToElementTest<LoggingInfo>(expected, info_verbose);
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

    // Create two different destinations.
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
