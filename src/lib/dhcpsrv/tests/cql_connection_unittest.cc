// Copyright (C) 2017 Deutsche Telekom AG.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/cql_exchange.h>

#include <cstring>

#include <boost/any.hpp>

#include <gtest/gtest.h>

namespace {

using isc::dhcp::CqlTaggedStatement;
using isc::dhcp::StatementMap;
using isc::dhcp::StatementTag;
using isc::dhcp::StatementTagHash;
using isc::dhcp::exchangeType;

class CqlConnectionTest {
public:
    /// @brief Constructor
    CqlConnectionTest() {
    }

    /// @brief Destructor
    virtual ~CqlConnectionTest() {
    }
};

/// @brief Check that the key is properly hashed for StatementMap.
TEST(CqlConnection, statementMapHash) {
    // Build std::strings to prevent optimizations on underlying C string.
    std::string tag1_s = "same";
    std::string tag2_s = "same";
    StatementTag tag1 = tag1_s.c_str();
    StatementTag tag2 = tag2_s.c_str();
    StatementMap map;

    // Make sure addresses are different.
    EXPECT_NE(tag1, tag2);

    // Insert two entries with the same key value.
    map.insert({tag1, CqlTaggedStatement(tag1, "your fancy select here")});
    map.insert({tag2, CqlTaggedStatement(tag2, "DELETE FROM world.evil")});

    // Make sure the first one was overwritten.
    char const* const tag1_text = map.find(tag1)->second.text_;
    char const* const tag2_text = map.find(tag2)->second.text_;
    EXPECT_TRUE(tag1_text);
    EXPECT_TRUE(tag2_text);
    ASSERT_EQ(std::strcmp(tag1_text, tag2_text), 0);
    ASSERT_EQ(map.size(), 1u);
}

/// @brief Check anything related to exchange types.
TEST(CqlConnection, exchangeTypeCoverage) {
    // Check that const and non-const are supported and both point to the same
    // exchange type.
    int i = 1;

    // non-const
    int* pi = &i;
    boost::any bi(pi);

    // const
    int* const cpi = &i;
    boost::any bci(cpi);

    ASSERT_EQ(exchangeType(bi), exchangeType(bci));
}

}  // namespace

