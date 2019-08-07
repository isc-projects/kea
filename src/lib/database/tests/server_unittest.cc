// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/server_collection.h>
#include <testutils/test_to_element.h>
#include <exceptions/exceptions.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::db;

namespace {

// Tests the constructor of the Server.
TEST(ServerTest, constructor) {
    ServerPtr server;

    ASSERT_NO_THROW(
        server = Server::create(ServerTag("xyz"), "my first server")
    );
    ASSERT_TRUE(server);
    EXPECT_EQ("xyz", server->getServerTagAsText());
    EXPECT_EQ("my first server", server->getDescription());
}

// Tests that too long description is rejected.
TEST(ServerTest, tooLongDescription) {
    EXPECT_THROW(Server::create(ServerTag("xyz"), std::string(65537, 'c')),
                 BadValue);
}

// Tests that toElement method returns expected JSON map.
TEST(ServerTest, toElement) {
    ServerPtr server1 = Server::create(ServerTag("foo"), "a server");
    std::string expected1 = "{"
        "\"server-tag\": \"foo\","
        "\"description\": \"a server\""
        " }";
    isc::test::runToElementTest<Server>(expected1, *server1);

    ServerPtr server2 = Server::create(ServerTag("bar"));
    std::string expected2= "{"
        "\"server-tag\": \"bar\","
        "\"description\": \"\""
        " }";
    isc::test::runToElementTest<Server>(expected2, *server2);
}

// Tests that it is possible to fetch server by tag from the collection.
TEST(ServerFetcherTest, getByTag) {
    ServerCollection servers;

    EXPECT_TRUE(servers.insert(Server::create(ServerTag("alpha"), "alpha description")).second);
    EXPECT_TRUE(servers.insert(Server::create(ServerTag("beta"), "beta description")).second);
    EXPECT_TRUE(servers.insert(Server::create(ServerTag("gamma"), "gamma description")).second);

    // Inserting an element with duplicated server tag should be unsuccessful.
    EXPECT_FALSE(servers.insert(Server::create(ServerTag("gamma"), "gamma 2 description")).second);

    auto alpha = ServerFetcher::get(servers, ServerTag("alpha"));
    ASSERT_TRUE(alpha);
    EXPECT_EQ("alpha", alpha->getServerTagAsText());
    EXPECT_EQ("alpha description", alpha->getDescription());

    auto beta = ServerFetcher::get(servers, ServerTag("beta"));
    ASSERT_TRUE(beta);
    EXPECT_EQ("beta", beta->getServerTagAsText());
    EXPECT_EQ("beta description", beta->getDescription());

    auto gamma = ServerFetcher::get(servers, ServerTag("gamma"));
    ASSERT_TRUE(gamma);
    EXPECT_EQ("gamma", gamma->getServerTagAsText());
    EXPECT_EQ("gamma description", gamma->getDescription());

    // Null pointer should be returned when a given server does not exist.
    EXPECT_FALSE(ServerFetcher::get(servers, ServerTag("non-existent")));
}

}
