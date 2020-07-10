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
    BasicHttpAuthPtr ba;
    EXPECT_THROW(ba.reset(new BasicHttpAuth("foo:bar", "")), BadValue);
}

// Test that secret without a colon is rejected.
TEST(BasicHttpAuthTest, secretNoColon) {
    BasicHttpAuthPtr ba;
    EXPECT_THROW(ba.reset(new BasicHttpAuth("foo-bar")), BadValue);
}

// Test that valid user and password work.
TEST(BasicHttpAuthTest, user) {
    BasicHttpAuthPtr ba;
    EXPECT_NO_THROW(ba.reset(new BasicHttpAuth("foo", "bar")));
    ASSERT_TRUE(ba);
    EXPECT_EQ("foo:bar", ba->getSecret());
    EXPECT_EQ("Zm9vOmJhcg==", ba->getCredential());
}

// Test that valid secret work.
TEST(BasicHttpAuthTest, secret) {
    BasicHttpAuthPtr ba;
    EXPECT_NO_THROW(ba.reset(new BasicHttpAuth("foo:bar")));
    ASSERT_TRUE(ba);
    EXPECT_EQ("foo:bar", ba->getSecret());
    EXPECT_EQ("Zm9vOmJhcg==", ba->getCredential());
}

// Test that secret is encoded in UTF-8.
TEST(BasicHttpAuthTest, utf8) {
    BasicHttpAuthPtr ba;
    EXPECT_NO_THROW(ba.reset(new BasicHttpAuth("foo\n", "b\ar")));
    ASSERT_TRUE(ba);
    EXPECT_EQ("foo\n:b\ar", ba->getSecret());
    EXPECT_EQ("Zm9vCjpiB3I=", ba->getCredential());
}

} // end of anonymous namespace
