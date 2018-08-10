// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @brief Basic environment tests for netconf


#include <sysrepo-cpp/Session.h>
#include <gtest/gtest.h>

class NetconfTest : public ::testing::Test {
public:

    NetconfTest() {}

};

// This test checks if a session to sysrepo can be established.
// It uses sysrepo code directly, so it's a sanity check for the
// environment. Doesn't test any Kea code.
TEST_F(NetconfTest, environmentSanity) {

    S_Connection conn;

    ASSERT_NO_THROW(conn.reset(new Connection("kea-netconf")));

    S_Session sess;

    ASSERT_NO_THROW(sess.reset(new Session(conn)));
}
