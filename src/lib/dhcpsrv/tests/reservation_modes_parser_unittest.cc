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
        uint8_t expected_result_;
    };

    std::vector<Scenario> scenarios = {
        {
        "reservation modes disabled",
        "{ \n"
        "   \"reservations-global\": false, \n"
        "   \"reservations-in-subnet\": false, \n"
        "   \"reservations-out-of-pool\": false \n"
        "} \n",
        Network::HR_DISABLED
        },
        {
        "reservation modes global enabled",
        "{ \n"
        "   \"reservations-global\": true, \n"
        "   \"reservations-in-subnet\": false, \n"
        "   \"reservations-out-of-pool\": false \n"
        "} \n",
        Network::HR_GLOBAL
        },
        {
        "reservation modes in-subnet enabled",
        "{ \n"
        "   \"reservations-global\": false, \n"
        "   \"reservations-in-subnet\": true, \n"
        "   \"reservations-out-of-pool\": false \n"
        "} \n",
        Network::HR_IN_SUBNET
        },
        {
        "reservation modes global and in-subnet enabled",
        "{ \n"
        "   \"reservations-global\": true, \n"
        "   \"reservations-in-subnet\": true, \n"
        "   \"reservations-out-of-pool\": false \n"
        "} \n",
        Network::HR_GLOBAL|Network::HR_IN_SUBNET
        },
        {
        "reservation modes out-of-pool enabled",
        "{ \n"
        "   \"reservations-global\": false, \n"
        "   \"reservations-in-subnet\": false, \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_OUT_OF_POOL
        },
        {
        "reservation modes global and out-of-pool enabled",
        "{ \n"
        "   \"reservations-global\": true, \n"
        "   \"reservations-in-subnet\": false, \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_GLOBAL|Network::HR_OUT_OF_POOL
        },
        {
        "reservation modes in-subnet and out-of-pool enabled",
        "{ \n"
        "   \"reservations-global\": false, \n"
        "   \"reservations-in-subnet\": true, \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_IN_SUBNET|Network::HR_OUT_OF_POOL
        },
        {
        "reservation modes global, in-subnet and out-of-pool enabled",
        "{ \n"
        "   \"reservations-global\": true, \n"
        "   \"reservations-in-subnet\": true, \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_GLOBAL|Network::HR_IN_SUBNET|Network::HR_OUT_OF_POOL
        },
        {
        "only global",
        "{ \n"
        "   \"reservations-global\": true \n"
        "} \n",
        Network::HR_GLOBAL
        },
        {
        "only in-subnet",
        "{ \n"
        "   \"reservations-in-subnet\": true \n"
        "} \n",
        Network::HR_IN_SUBNET
        },
        {
        "only out-of-pool",
        "{ \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_OUT_OF_POOL
        },
        {
        "only global and in-subnet",
        "{ \n"
        "   \"reservations-global\": true, \n"
        "   \"reservations-in-subnet\": true \n"
        "} \n",
        Network::HR_GLOBAL|Network::HR_IN_SUBNET
        },
        {
        "only global and out-of-pool",
        "{ \n"
        "   \"reservations-global\": true, \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_GLOBAL|Network::HR_OUT_OF_POOL
        },
        {
        "only in-subnet and out-of-pool",
        "{ \n"
        "   \"reservations-in-subnet\": true, \n"
        "   \"reservations-out-of-pool\": true \n"
        "} \n",
        Network::HR_IN_SUBNET|Network::HR_OUT_OF_POOL
        },
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
            ASSERT_EQ(scenario.expected_result_, reservation_modes);
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
        "global not boolean",
        "{ \n"
        "   \"reservations-global\": \"always\" \n"
        "} \n"
        },
        {
        "in-subnet not boolean",
        "{ \n"
        "   \"reservations-in-subnet\": \"always\" \n"
        "} \n"
        },
        {
        "out-of-pool not boolean",
        "{ \n"
        "   \"reservations-out-of-pool\": \"always\" \n"
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
