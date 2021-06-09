// Copyright (C) 2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <eval/dependency.h>
#include <eval/eval_context.h>
#include <eval/token.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture for testing dependency.
///
/// This class provides several convenience objects to be used during testing
/// of the dependency of classification expressions.
class DependencyTest : public ::testing::Test {
public:
    /// @brief Constructor
    DependencyTest() : result_(true) {
    }

    /// @brief Destructor
    ///
    /// Reset expression and result.
    ~DependencyTest() {
        e_.reset();
        result_ = false;
    }

    ExpressionPtr e_; ///< An expression

    bool result_; ///< A decision
};

// This checks the null expression: it should return false.
TEST_F(DependencyTest, nullExpr) {
    TokenPtr token;
    ASSERT_NO_THROW(result_ = dependOnClass(token, "foobar"));
    EXPECT_FALSE(result_);
    ASSERT_NO_THROW(result_ = dependOnClass(e_, "foobar"));
    EXPECT_FALSE(result_);
}

// This checks the empty expression: it should return false.
TEST_F(DependencyTest, emptyExpr) {
    e_.reset(new Expression());
    ASSERT_NO_THROW(result_ = dependOnClass(e_, "foobar"));
    EXPECT_FALSE(result_);
}

// This checks the { "true" } expression: it should return false.
TEST_F(DependencyTest, trueExpr) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    ASSERT_NO_THROW(result_ = dependOnClass(ttrue, "foobar"));
    EXPECT_FALSE(result_);
    e_.reset(new Expression());
    e_->push_back(ttrue);
    ASSERT_NO_THROW(result_ = dependOnClass(e_, "foobar"));
    EXPECT_FALSE(result_);
}

// This checks the { member('not-matching') } expression:
// it should return false.
TEST_F(DependencyTest, notMatching) {
    TokenPtr notmatching;
    ASSERT_NO_THROW(notmatching.reset(new TokenMember("not-matching")));
    ASSERT_NO_THROW(result_ = dependOnClass(notmatching, "foobar"));
    EXPECT_FALSE(result_);
    e_.reset(new Expression());
    e_->push_back(notmatching);
    ASSERT_NO_THROW(result_ = dependOnClass(e_, "foobar"));
    EXPECT_FALSE(result_);
}

// This checks the { member('foobar') } expression: it should return true.
TEST_F(DependencyTest, matching) {
    TokenPtr matching;
    ASSERT_NO_THROW(matching.reset(new TokenMember("foobar")));
    ASSERT_NO_THROW(result_ = dependOnClass(matching, "foobar"));
    EXPECT_TRUE(result_);
    e_.reset(new Expression());
    e_->push_back(matching);
    result_ = false;
    ASSERT_NO_THROW(result_ = dependOnClass(e_, "foobar"));
    EXPECT_TRUE(result_);
}

};
