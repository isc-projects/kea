// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_host_operations.h>
#include <dhcpsrv/host.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>

using namespace isc;
using namespace isc::dhcp;

namespace {

/// @brief Checks if specified identifier is present.
///
/// @param cfg Object holding current configuration.
/// @param id Identifier type which presence should be checked.
/// @return true if specified identifier is present.
bool
identifierPresent(const CfgHostOperations& cfg, const Host::IdentifierType& id) {
    CfgHostOperations::IdentifierTypes types = cfg.getIdentifierTypes();
    return (std::find(types.begin(), types.end(), id) != types.end());
}

/// @brief Checks if specified identifier is at specified position.
///
/// @param cfg Object holding current configuration.
/// @param id Identifier type which presence should be checked.
/// @param pos Position at which the identifier is expected on the list.
/// @return true if specified identifier exists at specified position.
bool
identifierAtPosition(const CfgHostOperations& cfg, const Host::IdentifierType& id,
                     const size_t pos) {
    CfgHostOperations::IdentifierTypes types = cfg.getIdentifierTypes();
    if (types.size() > pos) {
        CfgHostOperations::IdentifierTypes::const_iterator type = types.begin();
        std::advance(type, pos);
        return (*type == id);
    }
    return (false);
}

// This test checks that the list of identifiers is initially
// empty.
TEST(CfgHostOperationsTest, defaults) {
    CfgHostOperations cfg;
    EXPECT_TRUE(cfg.getIdentifierTypes().empty());
}

// This test verifies that identifier types can be added into an
// ordered collection and then removed.
TEST(CfgHostOperationsTest, addIdentifier) {
    CfgHostOperations cfg;

    // Only HW address added.
    ASSERT_NO_THROW(cfg.addIdentifierType("hw-address"));
    EXPECT_TRUE(identifierAtPosition(cfg, Host::IDENT_HWADDR, 0));
    EXPECT_FALSE(identifierPresent(cfg, Host::IDENT_DUID));
    EXPECT_FALSE(identifierPresent(cfg, Host::IDENT_CIRCUIT_ID));

    // HW address and DUID should be present.
    ASSERT_NO_THROW(cfg.addIdentifierType("duid"));
    EXPECT_TRUE(identifierAtPosition(cfg, Host::IDENT_HWADDR, 0));
    EXPECT_TRUE(identifierAtPosition(cfg, Host::IDENT_DUID, 1));
    EXPECT_FALSE(identifierPresent(cfg, Host::IDENT_CIRCUIT_ID));

    // All three identifiers should be present now.
    ASSERT_NO_THROW(cfg.addIdentifierType("circuit-id"));
    EXPECT_TRUE(identifierAtPosition(cfg, Host::IDENT_HWADDR, 0));
    EXPECT_TRUE(identifierAtPosition(cfg, Host::IDENT_DUID, 1));
    EXPECT_TRUE(identifierAtPosition(cfg, Host::IDENT_CIRCUIT_ID, 2));

    // Let's clear and make sure no identifiers are present.
    ASSERT_NO_THROW(cfg.clearIdentifierTypes());
    EXPECT_TRUE(cfg.getIdentifierTypes().empty());
}

// This test verfies that the default DHCPv4 configuration is created
// as expected.
TEST(CfgHostOperationsTest, createConfig4) {
    CfgHostOperationsPtr cfg = CfgHostOperations::createConfig4();

    EXPECT_TRUE(identifierAtPosition(*cfg, Host::IDENT_HWADDR, 0));
    EXPECT_TRUE(identifierAtPosition(*cfg, Host::IDENT_DUID, 1));
    EXPECT_TRUE(identifierAtPosition(*cfg, Host::IDENT_CIRCUIT_ID, 2));
}

// This test verfies that the default DHCPv6 configuration is created
// as expected.
TEST(CfgHostOperationsTest, createConfig6) {
    CfgHostOperationsPtr cfg = CfgHostOperations::createConfig6();

    EXPECT_TRUE(identifierAtPosition(*cfg, Host::IDENT_HWADDR, 0));
    EXPECT_TRUE(identifierAtPosition(*cfg, Host::IDENT_DUID, 1));
    EXPECT_FALSE(identifierPresent(*cfg, Host::IDENT_CIRCUIT_ID));
}

} // end of anonymous namespace
