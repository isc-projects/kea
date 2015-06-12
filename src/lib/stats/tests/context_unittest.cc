// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <stats/context.h>
#include <gtest/gtest.h>
#include <util/unittests/test_exceptions.h>

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
    EXPECT_THROW_WITH(ctx.add(a), DuplicateStat, "Statistic named "
                      << a->getName() << " already exists.");

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

