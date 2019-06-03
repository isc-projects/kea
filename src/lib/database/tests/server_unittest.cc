// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/server.h>
#include <exceptions/exceptions.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::db;

namespace {

TEST(ServerTest, constructor) {
    ServerPtr server;

    ASSERT_NO_THROW(
        server = Server::create(ServerTag("xyz"), "my first server")
    );
    ASSERT_TRUE(server);
    EXPECT_EQ("xyz", server->getServerTag());
    EXPECT_EQ("my first server", server->getDescription());
}

TEST(ServerTest, tooLongDescription) {
    EXPECT_THROW(Server::create(ServerTag("xyz"), std::string(65537, 'c')),
                 BadValue);
}

}
