// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/reservation_modes_parser.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief Test fixture class for @c HostReservationModesParser
class HostReservationModesParserTest : public ::testing::Test {
protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

};

void
HostReservationModesParserTest::SetUp() {
    CfgMgr::instance().clear();
}

void
HostReservationModesParserTest::TearDown() {
    CfgMgr::instance().clear();
}

// Verifies that HostReservationModesParser handles
// expected valid reservation-modes content
TEST_F(HostReservationModesParserTest, validContent) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "queue disabled",
        "{ \n"
        "   \"enable-queue\": false \n"
        "} \n"
        },
        {
        "queue disabled, arbitrary content allowed",
        "{ \n"
        "   \"enable-queue\": false, \n"
        "   \"foo\": \"bogus\", \n"
        "   \"random-int\" : 1234 \n"
        "} \n"
        },
        {
        "queue enabled, with queue-type",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\" \n"
        "} \n"
        },
        {
        "queue enabled with queue-type and arbitrary content",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\", \n"
        "   \"foo\": \"bogus\", \n"
        "   \"random-int\" : 1234 \n"
        "} \n"
        }
    };

    // Iterate over the valid scenarios and verify they succeed.
    ConstElementPtr config_elems;
    Network::HRMode reservation_modes;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            // Construct the config JSON
            ASSERT_NO_THROW(config_elems = Element::fromJSON(scenario.json_))
                            << "invalid JSON, test is broken";

            // Parsing config into a reservation modes parser should succeed.
            HostReservationModesParser parser;
            try {
                reservation_modes = parser.parse(config_elems);
            } catch (const std::exception& ex) {
                ADD_FAILURE() << "parser threw an exception: " << ex.what();
            }

            // Verify the resultant reservation-modes.
            ASSERT_TRUE(reservation_modes);
        }
    }
}

// Verifies that HostReservationModesParser correctly catches
// invalid reservation-modes content
TEST_F(HostReservationModesParserTest, invalidContent) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "enable-queue missing",
        "{ \n"
        "   \"enable-type\": \"some-type\" \n"
        "} \n"
        },
        {
        "enable-queue not boolean",
        "{ \n"
        "   \"enable-queue\": \"always\" \n"
        "} \n"
        },
        {
        "queue enabled, type missing",
        "{ \n"
        "   \"enable-queue\": true \n"
        "} \n"
        },
        {
        "queue enabled, type not a string",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": 7777 \n"
        "} \n"
        }
    };

    // Iterate over the invalid scenarios and verify they throw exception.
    ConstElementPtr config_elems;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            // Construct the config JSON
            ASSERT_NO_THROW(config_elems = Element::fromJSON(scenario.json_))
                            << "invalid JSON, test is broken";

            // Parsing config into a reservation modes parser should succeed.
            HostReservationModesParser parser;
            EXPECT_THROW(parser.parse(config_elems), DhcpConfigError);
        }
    }
}

}; // anonymous namespace
