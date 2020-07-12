// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/basic_auth.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::http;

namespace {

// Test that user name with a colon is rejected.
TEST(BasicHttpAuthTest, userColon) {
    BasicHttpAuthPtr basic_auth;
    EXPECT_THROW(basic_auth.reset(new BasicHttpAuth("foo:bar", "")), BadValue);
}

// Test that secret without a colon is rejected.
TEST(BasicHttpAuthTest, secretNoColon) {
    BasicHttpAuthPtr basic_auth;
    EXPECT_THROW(basic_auth.reset(new BasicHttpAuth("foo-bar")), BadValue);
}

// Test that valid user and password work.
TEST(BasicHttpAuthTest, user) {
    BasicHttpAuthPtr basic_auth;
    EXPECT_NO_THROW(basic_auth.reset(new BasicHttpAuth("foo", "bar")));
    ASSERT_TRUE(basic_auth);
    EXPECT_EQ("foo:bar", basic_auth->getSecret());
    EXPECT_EQ("Zm9vOmJhcg==", basic_auth->getCredential());
}

// Test that valid secret work.
TEST(BasicHttpAuthTest, secret) {
    BasicHttpAuthPtr basic_auth;
    EXPECT_NO_THROW(basic_auth.reset(new BasicHttpAuth("foo:bar")));
    ASSERT_TRUE(basic_auth);
    EXPECT_EQ("foo:bar", basic_auth->getSecret());
    EXPECT_EQ("Zm9vOmJhcg==", basic_auth->getCredential());
}

// Test that secret is encoded in UTF-8.
TEST(BasicHttpAuthTest, utf8) {
    BasicHttpAuthPtr basic_auth;
    EXPECT_NO_THROW(basic_auth.reset(new BasicHttpAuth("foo\n", "b\ar")));
    ASSERT_TRUE(basic_auth);
    EXPECT_EQ("foo\n:b\ar", basic_auth->getSecret());
    EXPECT_EQ("Zm9vCjpiB3I=", basic_auth->getCredential());
}

// Test that a header context for basic HTTP authentication can be created.
TEST(BasicHttpAuthTest, headerContext) {
    BasicHttpAuthPtr basic_auth;
    EXPECT_NO_THROW(basic_auth.reset(new BasicHttpAuth("foo", "bar")));
    ASSERT_TRUE(basic_auth);
    BasicAuthHttpHeaderContext ctx(*basic_auth);
    EXPECT_EQ("Authorization", ctx.name_);
    EXPECT_EQ("Basic Zm9vOmJhcg==", ctx.value_);
}

} // end of anonymous namespace
