// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/server_tag.h>
#include <database/server_selector.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::db;

namespace {

// Check that server selector can be set to UNASSIGNED.
TEST(ServerSelectorTest, unassigned) {
    ServerSelector selector = ServerSelector::UNASSIGNED();
    EXPECT_EQ(ServerSelector::Type::UNASSIGNED, selector.getType());
    EXPECT_TRUE(selector.amUnassigned());
    EXPECT_TRUE(selector.hasNoTags());
    EXPECT_FALSE(selector.hasMultipleTags());
}

// Check that server selector can be set to ALL.
TEST(ServerSelectorTest, all) {
    ServerSelector selector = ServerSelector::ALL();
    EXPECT_EQ(ServerSelector::Type::ALL, selector.getType());
    EXPECT_FALSE(selector.amUnassigned());

    EXPECT_FALSE(selector.hasNoTags());
    auto tags = selector.getTags();
    EXPECT_EQ(1, tags.size());
    EXPECT_EQ(1, tags.count(ServerTag("all")));
    EXPECT_TRUE(selector.amAll());
    EXPECT_FALSE(selector.hasMultipleTags());
}

// Check that a single server can be selected.
TEST(ServerSelectorTest, one) {
    ServerSelector selector = ServerSelector::ONE("some-tag");
    EXPECT_EQ(ServerSelector::Type::SUBSET, selector.getType());
    EXPECT_FALSE(selector.amUnassigned());

    EXPECT_FALSE(selector.hasNoTags());
    auto tags = selector.getTags();
    ASSERT_EQ(1, tags.size());
    EXPECT_EQ(1, tags.count(ServerTag("some-tag")));
    EXPECT_FALSE(selector.hasMultipleTags());
}

// Check that multiple servers can be selected.
TEST(ServerSelectorTest, multiple) {
    ServerSelector selector = ServerSelector::MULTIPLE({ "tag1", "tag2", "tag3" });
    EXPECT_EQ(ServerSelector::Type::SUBSET, selector.getType());
    EXPECT_FALSE(selector.amUnassigned());

    EXPECT_FALSE(selector.hasNoTags());
    auto tags = selector.getTags();
    ASSERT_EQ(3, tags.size());
    EXPECT_EQ(1, tags.count(ServerTag("tag1")));
    EXPECT_EQ(1, tags.count(ServerTag("tag2")));
    EXPECT_EQ(1, tags.count(ServerTag("tag3")));
    EXPECT_TRUE(selector.hasMultipleTags());
}

// Check that server selector can be set to ANY.
TEST(ServerSelectorTest, any) {
    ServerSelector selector = ServerSelector::ANY();
    EXPECT_EQ(ServerSelector::Type::ANY, selector.getType());
    EXPECT_FALSE(selector.amUnassigned());

    EXPECT_TRUE(selector.hasNoTags());
}

}
