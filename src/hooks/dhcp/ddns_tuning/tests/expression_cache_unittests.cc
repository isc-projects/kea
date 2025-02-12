// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible option.

#include <config.h>
#include <ddns_tuning.h>
#include <ddns_tuning_log.h>
#include <asiolink/io_address.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <eval/eval_context.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::hooks;
using namespace isc::ddns_tuning;
using namespace isc::test;
using namespace boost::posix_time;

namespace {

/// @brief ExpressionCache derivation that allows flush time to be modified.
class TestExpressionCache : public ExpressionCache {
public:
    /// @brief Constructor
    TestExpressionCache () {
    }

    /// @brief Destructor
    virtual ~TestExpressionCache() {
    }

    /// @brief Adjusts the last flush time by the given amount.
    ///
    /// @param offset signed value in seconds to add to cache's last
    /// flush time value
    void tweakLastFlushTime(int offset) {
        setModificationTime(getLastFlushTime() + seconds(offset));
    }
};

/// @brief Test fixture for testing ExpressionCache.
class ExpressionCacheTest : public ::testing::Test {
public:
    /// @brief Constructor
    ExpressionCacheTest () {
    }

    /// @brief Destructor
    virtual ~ExpressionCacheTest() {
    }

    /// @brief Verifies construction of an ExpressionCache.
    void testConstruction() {
        // We use a BaseStampedElement to get the current time to ensure we
        // are using the same time perspective (currently local) as StampedElements do.
        BaseStampedElement now;
        ptime start_time = now.getModificationTime();

        // Create a new cache.
        TestExpressionCache expressions;

        // Verify that last_flush_time_ has been set and that the
        // cache has no entries.
        ptime last_flush_time = expressions.getLastFlushTime();
        EXPECT_GE(last_flush_time, start_time);
        EXPECT_EQ(expressions.size(), 0);

        // Verify that looking for an entry in an empty cache
        // gracefully finds nothing.
        ExpressionPtr fetched_exp;
        EXPECT_FALSE(expressions.findExpression(999, fetched_exp));
        EXPECT_FALSE(fetched_exp);
    }

    /// @brief Verifies that invalid DHCPv4 expressions are rejected gracefully
    void testInvalidExpressions4() {
        // Create a new cache.
        TestExpressionCache expressions;

        // An invalid keyword should fail.
        std::string expression_str("bogus");
        ASSERT_THROW_MSG(expressions.parseAndCacheExpression(1, expression_str, AF_INET), BadValue,
                         "error parsing expression: [bogus] : <string>:1.1: Invalid character: b");

        // Valid V4 should not be valid v6.
        expression_str = "addrtotext(relay6[0].linkaddr)";
        ASSERT_THROW_MSG(expressions.parseAndCacheExpression(1, expression_str, AF_INET), BadValue,
                         "error parsing expression: [addrtotext(relay6[0].linkaddr)] :"
                         " <string>:1.19: Nest level invalid for DHCPv4 packets");

        EXPECT_EQ(expressions.size(), 0);
    }

    /// @brief Verifies that valid DHCPv4 expressions are cached correctly.
    void testValidExpressions4() {
        // Create a new cache.
        TestExpressionCache expressions;

        // Define some expression strings, including a empty one.
        std::vector<std::string> expression_strs {
            "option[host-name].hex + '.sample.com'",
            "addrtotext(pkt4.yiaddr)",
            "",
            "'literal'"
        };

        // Verify that we can cache valid expressions.
        int id = 1;
        for (auto const& expression_str : expression_strs) {
            ExpressionPtr expression;
            ASSERT_NO_THROW_LOG(expression = expressions.parseAndCacheExpression(id, expression_str, AF_INET));
            ASSERT_TRUE(expression);
            EXPECT_EQ(expression->empty(), expression_str.empty());
            EXPECT_EQ(expressions.size(), id);

            // Verify we can retrieve the cached expression.
            ExpressionPtr fetched_expression;
            ASSERT_TRUE(expressions.findExpression(id, fetched_expression));
            EXPECT_EQ(fetched_expression, expression);
            ++id;
        }
    }

    /// @brief Verifies that invalid DHCPv6 expressions are rejected gracefully
    void testInvalidExpressions6() {
        // Create a new cache.
        TestExpressionCache expressions;

        // An invalid keyword should fail.
        std::string expression_str("bogus");
        ASSERT_THROW_MSG(expressions.parseAndCacheExpression(1, expression_str, AF_INET6), BadValue,
                         "error parsing expression: [bogus] : <string>:1.1: Invalid character: b");

        // Valid V4 should not be valid v6.
        expression_str = "addrtotext(pkt4.yiaddr)";
        ASSERT_THROW_MSG(expressions.parseAndCacheExpression(1, expression_str, AF_INET6), BadValue,
                         "error parsing expression: [addrtotext(pkt4.yiaddr)] :"
                         " <string>:1.12-15: pkt4 can only be used in DHCPv4.");

        EXPECT_EQ(expressions.size(), 0);
    }

    /// @brief Verifies that valid DHCPv6 expressions are cached correctly.
    void testValidExpressions6() {
        // Create a new cache.
        TestExpressionCache expressions;

        // Define some expression strings, including a empty one.
        std::vector<std::string> expression_strs {
            "option[clientid].hex + '.sample.com'",
            "addrtotext(relay6[0].linkaddr)",
            "",
            "'literal'"
        };

        // Verify that we can cache valid expressions.
        int id = 1;
        for (auto const& expression_str : expression_strs) {
            ExpressionPtr expression;
            ASSERT_NO_THROW_LOG(expression = expressions.parseAndCacheExpression(id, expression_str, AF_INET6));
            ASSERT_TRUE(expression);
            EXPECT_EQ(expression->empty(), expression_str.empty());
            EXPECT_EQ(expressions.size(), id);

            // Verify we can retrieve the cached expression.
            ExpressionPtr fetched_expression;
            ASSERT_TRUE(expressions.findExpression(id, fetched_expression));
            EXPECT_EQ(fetched_expression, expression);
            ++id;
        }
    }

    /// @brief Verifies that null expression pointers can be cached.
    void testExpressionCacheNullExpressions() {
        // Create a new cache.
        TestExpressionCache expressions;
        EXPECT_EQ(expressions.size(), 0);

        // Verify that we can cache a null pointer expression.
        ExpressionPtr no_exp;
        ASSERT_NO_THROW_LOG(expressions.cacheExpression(1, no_exp));
        EXPECT_EQ(expressions.size(), 1);

        // Verify we can retrieve the cached null expression pointer.
        ExpressionPtr fetched_exp;
        ASSERT_TRUE(expressions.findExpression(1, fetched_exp));
        ASSERT_FALSE(fetched_exp);
    }

    /// @brief Verifies that the cache can be cleared correctly.
    void testFlushCache() {
        // Create a new cache.
        TestExpressionCache expressions;
        EXPECT_EQ(expressions.size(), 0);
        ptime last_flush_time = expressions.getLastFlushTime();

        // Now let's wind the clock back on last_flush_time.
        expressions.tweakLastFlushTime(-1000);
        EXPECT_LT(expressions.getLastFlushTime(), last_flush_time);
        last_flush_time = expressions.getLastFlushTime();

        std::vector<std::string> expression_strs { "'one'", "'two'", "'three'" };
        int id = 1;
        for (auto const& expression_str : expression_strs) {
            ExpressionPtr expression;
            ASSERT_NO_THROW_LOG(expression = expressions.parseAndCacheExpression(id, expression_str, AF_INET));
            ASSERT_TRUE(expression);
            EXPECT_EQ(expression->empty(), expression_str.empty());
            EXPECT_EQ(expressions.size(), id);
            ++id;
        }

        // Verify we can explicitly clear the cache.  Should be no entries
        // and last_flush_time should be updated.
        expressions.clear();
        EXPECT_GT(expressions.getLastFlushTime(), last_flush_time);
        EXPECT_EQ(expressions.size(), 0);
    }
};

TEST_F(ExpressionCacheTest, construction) {
    testConstruction();
}

TEST_F(ExpressionCacheTest, constructionMultiThreading) {
    MultiThreadingTest mt;
    testConstruction();
}

TEST_F(ExpressionCacheTest, invalidExpressions4) {
    testInvalidExpressions4();
}

TEST_F(ExpressionCacheTest, invalidExpressions4MultiThreading) {
    MultiThreadingTest mt;
    testInvalidExpressions4();
}

TEST_F(ExpressionCacheTest, validExpressions4) {
    testValidExpressions4();
}

TEST_F(ExpressionCacheTest, validExpressions4MultiThreading) {
    MultiThreadingTest mt;
    testValidExpressions4();
}

TEST_F(ExpressionCacheTest, invalidExpressions6) {
    testInvalidExpressions6();
}

TEST_F(ExpressionCacheTest, invalidExpressions6MultiThreading) {
    MultiThreadingTest mt;
    testInvalidExpressions6();
}

TEST_F(ExpressionCacheTest, validExpressions6) {
    testValidExpressions6();
}

TEST_F(ExpressionCacheTest, validExpressions6MultiThreading) {
    MultiThreadingTest mt;
    testValidExpressions6();
}

TEST_F(ExpressionCacheTest, expressionCacheNullExpressions) {
    testExpressionCacheNullExpressions();
}

TEST_F(ExpressionCacheTest, expressionCacheNullExpressionsMultiThreading) {
    MultiThreadingTest mt;
    testExpressionCacheNullExpressions();
}

TEST_F(ExpressionCacheTest, flushCache) {
    testFlushCache();
}

TEST_F(ExpressionCacheTest, flushCacheMultiThreading) {
    MultiThreadingTest mt;
    testFlushCache();
}

} // end of anonymous namespace
