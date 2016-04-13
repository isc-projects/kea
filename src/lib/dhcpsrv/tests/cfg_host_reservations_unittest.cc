// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_host_reservations.h>
#include <dhcpsrv/host.h>
#include <gtest/gtest.h>
#include <algorithm>

using namespace isc;
using namespace isc::dhcp;

namespace {

/// @brief Checks if specified identifier has been added.
///
/// @param cfg Object holding current configuration.
/// @param id Identifier type which presence should be checked.
bool
identifierAdded(const CfgHostReservations& cfg, const Host::IdentifierType& id) {
    CfgHostReservations::IdentifierTypes types = cfg.getIdentifierTypes();
    return (std::find(types.begin(), types.end(), id) != types.end());
}

// This test checks default configuration.
TEST(CfgHostReservationsTest, defaults) {
    CfgHostReservations cfg;
    EXPECT_TRUE(cfg.getIdentifierTypes().empty());
}

// This test verifies that identifier types can be added into an
// ordered collection and then removed.
TEST(CfgHostReservationsTest, addIdentifier) {
    CfgHostReservations cfg;

    // Only HW address added.
    ASSERT_NO_THROW(cfg.addIdentifierType("hw-address"));
    EXPECT_TRUE(identifierAdded(cfg, Host::IDENT_HWADDR));
    EXPECT_FALSE(identifierAdded(cfg, Host::IDENT_DUID));
    EXPECT_FALSE(identifierAdded(cfg, Host::IDENT_CIRCUIT_ID));

    // HW address and DUID should be present.
    ASSERT_NO_THROW(cfg.addIdentifierType("duid"));
    EXPECT_TRUE(identifierAdded(cfg, Host::IDENT_HWADDR));
    EXPECT_TRUE(identifierAdded(cfg, Host::IDENT_DUID));
    EXPECT_FALSE(identifierAdded(cfg, Host::IDENT_CIRCUIT_ID));

    // All three identifiers should be present now.
    ASSERT_NO_THROW(cfg.addIdentifierType("circuit-id"));
    EXPECT_TRUE(identifierAdded(cfg, Host::IDENT_HWADDR));
    EXPECT_TRUE(identifierAdded(cfg, Host::IDENT_DUID));
    EXPECT_TRUE(identifierAdded(cfg, Host::IDENT_CIRCUIT_ID));

    // Let's clear and make sure no identifiers are present.
    ASSERT_NO_THROW(cfg.clear());
    EXPECT_TRUE(cfg.getIdentifierTypes().empty());
}

} // end of anonymous namespace
