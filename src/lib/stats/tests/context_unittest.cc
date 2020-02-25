// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stats/context.h>
#include <gtest/gtest.h>
#include <util/boost_time_utils.h>
#include <string>

using namespace isc::data;
using namespace isc::stats;
using namespace boost::posix_time;
using namespace std;

// Basic test that checks get, add, del methods
TEST(ContextTest, basic) {

    // Let's create a couple observations. Using floating point,
    // as they're easiest to initialize.
    ObservationPtr a(new Observation("alpha", 1.11));
    ObservationPtr b(new Observation("beta", 2.22));
    ObservationPtr c(new Observation("gamma", 3.33));
    string expected_a = a->getJSON()->str();
    string expected_b = b->getJSON()->str();
    string expected_c = c->getJSON()->str();


    // Context where we will store the observations.
    StatContext ctx;

    // By default the context does not hold any statistics.
    EXPECT_EQ(0, ctx.size());

    // It should be possible to add 'a' statistic
    EXPECT_NO_THROW(ctx.add(a));

    // We can't add a duplicate.
    EXPECT_THROW(ctx.add(a), DuplicateStat);

    // It should be ok to add other statistics
    EXPECT_NO_THROW(ctx.add(b));
    EXPECT_NO_THROW(ctx.add(c));

    // By now we should have 3 statistics recorded
    EXPECT_EQ(3, ctx.size());

    // Let's try to retrieve them
    ObservationPtr from_ctx;
    EXPECT_NO_THROW(from_ctx = ctx.get("alpha"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(expected_a, from_ctx->getJSON()->str());

    EXPECT_NO_THROW(from_ctx = ctx.get("beta"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(expected_b, from_ctx->getJSON()->str());

    EXPECT_NO_THROW(from_ctx = ctx.get("gamma"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(expected_c, from_ctx->getJSON()->str());

    // Let's try to retrieve non-existing stat
    EXPECT_NO_THROW(from_ctx = ctx.get("delta"));
    EXPECT_FALSE(from_ctx);

    // Now delete one of the stats...
    EXPECT_TRUE(ctx.del("beta"));

    // ... and check that it's really gone.
    EXPECT_FALSE(ctx.get("beta"));

    // Attempt to delete non-existing stat should fail.
    EXPECT_FALSE(ctx.del("beta"));

    ConstElementPtr result;
    EXPECT_NO_THROW(result = ctx.getAll());

    ASSERT_TRUE(result);
    ElementPtr expected_result = Element::createMap();
    expected_result->set("alpha", a->getJSON());
    expected_result->set("gamma", c->getJSON());
    EXPECT_EQ(result->str(), expected_result->str());

    // Reset all statistics.
    EXPECT_NO_THROW(ctx.resetAll());

    EXPECT_NO_THROW(from_ctx = ctx.get("alpha"));
    ASSERT_TRUE(from_ctx);
    EXPECT_NE(expected_a, from_ctx->getJSON()->str());
    EXPECT_EQ(0.0, a->getFloat().first);

    EXPECT_NO_THROW(from_ctx = ctx.get("gamma"));
    ASSERT_TRUE(from_ctx);
    EXPECT_NE(expected_c, from_ctx->getJSON()->str());
    EXPECT_EQ(0.0, c->getFloat().first);

    // Set sample count for all statistics
    EXPECT_NO_THROW(ctx.setMaxSampleCountAll(50));

    EXPECT_NO_THROW(from_ctx = ctx.get("alpha"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(from_ctx->getMaxSampleCount().second, 50);

    EXPECT_NO_THROW(from_ctx = ctx.get("gamma"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(from_ctx->getMaxSampleCount().second, 50);

    // Set sample age for all statistics
    EXPECT_NO_THROW(ctx.setMaxSampleAgeAll(millisec::time_duration(0, 4, 5, 3)));

    EXPECT_NO_THROW(from_ctx = ctx.get("alpha"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(from_ctx->getMaxSampleAge().second, millisec::time_duration(0, 4, 5, 3));

    EXPECT_NO_THROW(from_ctx = ctx.get("gamma"));
    ASSERT_TRUE(from_ctx);
    EXPECT_EQ(from_ctx->getMaxSampleAge().second, millisec::time_duration(0, 4, 5, 3));

    // Clear all statistics.
    EXPECT_NO_THROW(ctx.clear());
    EXPECT_EQ(0, ctx.size());
}

