// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stats/context.h>
#include <gtest/gtest.h>

using namespace isc::stats;

// Basic test that checks get, add, del methods
TEST(ContextTest, basic) {

    // Let's create a couple observations. Using floating point,
    // as they're easiest to initialize.
    ObservationPtr a(new Observation("alpha", 1.11));
    ObservationPtr b(new Observation("beta", 2.22));
    ObservationPtr c(new Observation("gamma", 3.33));

    // Context where we will store the observations.
    StatContext ctx;

    // By default the context does not hold any statistics.
    EXPECT_EQ(0, ctx.stats_.size());
    EXPECT_TRUE(ctx.stats_.empty());

    // It should be possible to add 'a' statistic
    EXPECT_NO_THROW(ctx.add(a));

    // We can't add a duplicate.
    EXPECT_THROW(ctx.add(a), DuplicateStat);

    // It should be ok to add other statistics
    EXPECT_NO_THROW(ctx.add(b));
    EXPECT_NO_THROW(ctx.add(c));

    // By now we should have 3 statistics recorded
    EXPECT_EQ(3, ctx.stats_.size());
    EXPECT_FALSE(ctx.stats_.empty());

    // Let's try to retrieve them
    ObservationPtr from_ctx;
    EXPECT_NO_THROW(from_ctx = ctx.get("alpha"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(a->getJSON()->str(), from_ctx->getJSON()->str());

    EXPECT_NO_THROW(from_ctx = ctx.get("beta"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(b->getJSON()->str(), from_ctx->getJSON()->str());

    EXPECT_NO_THROW(from_ctx = ctx.get("gamma"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(c->getJSON()->str(), from_ctx->getJSON()->str());

    // Let's try to retrieve non-existing stat
    EXPECT_NO_THROW(from_ctx = ctx.get("delta"));
    EXPECT_FALSE(from_ctx);

    // Now delete one of the stats...
    EXPECT_TRUE(ctx.del("beta"));

    // ... and check that it's really gone.
    EXPECT_FALSE(ctx.get("beta"));

    // Attempt to delete non-existing stat should fail.
    EXPECT_FALSE(ctx.del("beta"));
}

