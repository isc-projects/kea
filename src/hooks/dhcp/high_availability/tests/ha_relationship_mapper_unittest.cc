// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_config.h>
#include <ha_relationship_mapper.h>
#include <exceptions/exceptions.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::ha;

namespace {

/// Tests associating objects with relationships and fetching them by the
/// partner names.
TEST(HARelationshipMapper, mapGet) {
    HARelationshipMapper<HAConfig> mapper;

    auto rel1 = HAConfig::create();
    auto rel2 = HAConfig::create();
    EXPECT_NO_THROW(mapper.map("server1", rel1));
    EXPECT_NO_THROW(mapper.map("server2", rel1));
    EXPECT_NO_THROW(mapper.map("server3", rel2));
    EXPECT_NO_THROW(mapper.map("server4", rel2));

    EXPECT_EQ(rel1, mapper.get("server1"));
    EXPECT_EQ(rel1, mapper.get("server2"));
    EXPECT_EQ(rel2, mapper.get("server3"));
    EXPECT_EQ(rel2, mapper.get("server4"));

    EXPECT_FALSE(mapper.get("server5"));
}

/// Tests getting a sole mapped object.
TEST(HARelationshipMapper, mapGetOne) {
    HARelationshipMapper<HAConfig> mapper;

    auto rel1 = HAConfig::create();
    EXPECT_NO_THROW(mapper.map("server1", rel1));
    EXPECT_NO_THROW(mapper.map("server2", rel1));

    EXPECT_EQ(rel1, mapper.get());
}

// Test getting all objects as a vector.
TEST(HARelationshipMapper, mapGetAll) {
    HARelationshipMapper<HAConfig> mapper;

    auto rel1 = HAConfig::create();
    auto rel2 = HAConfig::create();
    EXPECT_NO_THROW(mapper.map("server1", rel1));
    EXPECT_NO_THROW(mapper.map("server2", rel1));
    EXPECT_NO_THROW(mapper.map("server3", rel2));
    EXPECT_NO_THROW(mapper.map("server4", rel2));

    auto const& all = mapper.getAll();
    EXPECT_EQ(2, all.size());
    EXPECT_EQ(rel1, all[0]);
    EXPECT_EQ(rel2, all[1]);
}

/// Tests that the same server can't be associated with many relationships.
TEST(HARelationshipMapper, existingMappingError) {
    HARelationshipMapper<HAConfig> mapper;

    auto rel1 = HAConfig::create();
    auto rel2 = HAConfig::create();
    EXPECT_NO_THROW(mapper.map("server1", rel1));
    EXPECT_THROW(mapper.map("server1", rel2), InvalidOperation);
}

/// Tests checking if the mapper holds multiple instances.
TEST(HARelationshipMapper, hasMultiple) {
    HARelationshipMapper<HAConfig> mapper;
    EXPECT_FALSE(mapper.hasMultiple());

    auto rel1 = HAConfig::create();
    EXPECT_NO_THROW(mapper.map("server1", rel1));
    EXPECT_FALSE(mapper.hasMultiple());

    auto rel2 = HAConfig::create();
    EXPECT_NO_THROW(mapper.map("server2", rel2));
    EXPECT_TRUE(mapper.hasMultiple());
}


} // end of anonymous namespace
