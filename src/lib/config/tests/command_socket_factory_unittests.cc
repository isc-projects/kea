// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <cc/data.h>
#include <config/command_mgr.h>
#include <config/command_socket.h>
#include <config/command_socket_factory.h>
#include <cstdio>
#include <cstdlib>

using namespace isc::config;
using namespace isc::data;

// Test class for Command Manager
class CommandSocketFactoryTest : public ::testing::Test {
public:

    /// Default constructor
    CommandSocketFactoryTest()
        :SOCKET_NAME(getSocketPath()) {

        // Remove any stale socket files
        static_cast<void>(remove(SOCKET_NAME.c_str()));
    }

    /// Default destructor
    ~CommandSocketFactoryTest() {

        // Remove any stale socket files
        static_cast<void>(remove(SOCKET_NAME.c_str()));
    }

    /// @brief Returns socket path (using either hardcoded path or env variable)
    /// @return path to the unix socket
    std::string getSocketPath() {

        std::string socket_path;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path = std::string(env) + "/test-socket";
        } else {
            socket_path = std::string(TEST_DATA_BUILDDIR) + "/test-socket";
        }
        return (socket_path);
    }

    std::string SOCKET_NAME;
};

// This test verifies that a Unix socket can be opened properly and that input
// parameters (socket-type and socket-name) are verified.
TEST_F(CommandSocketFactoryTest, unixCreate) {
    // Null pointer is obviously a bad idea.
    EXPECT_THROW(CommandSocketFactory::create(ConstElementPtr()),
                 isc::config::BadSocketInfo);

    // So is passing no parameters.
    ElementPtr socket_info = Element::createMap();
    EXPECT_THROW(CommandSocketFactory::create(socket_info),
                 isc::config::BadSocketInfo);

    // We don't support ipx sockets
    socket_info->set("socket-type", Element::create("ipx"));
    EXPECT_THROW(CommandSocketFactory::create(socket_info),
                 isc::config::BadSocketInfo);

    socket_info->set("socket-type", Element::create("unix"));
    EXPECT_THROW(CommandSocketFactory::create(socket_info),
                 isc::config::BadSocketInfo);

    socket_info->set("socket-name", Element::create(SOCKET_NAME));
    CommandSocketPtr sock;
    EXPECT_NO_THROW(sock = CommandSocketFactory::create(socket_info));
    ASSERT_TRUE(sock);
    EXPECT_NE(-1, sock->getFD());

    // It should be possible to close the socket.
    EXPECT_NO_THROW(sock->close());
}

// This test checks that when unix path is too long, the socket cannot be opened.
TEST_F(CommandSocketFactoryTest, unixCreateTooLong) {
    ElementPtr socket_info = Element::fromJSON("{ \"socket-type\": \"unix\","
        "\"socket-name\": \"/tmp/toolongtoolongtoolongtoolongtoolongtoolong"
        "toolongtoolongtoolongtoolongtoolongtoolongtoolongtoolongtoolong"
        "\" }");

    EXPECT_THROW(CommandSocketFactory::create(socket_info), SocketError);
}
