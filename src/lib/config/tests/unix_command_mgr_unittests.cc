// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <testutils/sandbox.h>
#include <asiolink/io_service.h>
#include <cc/dhcp_config_error.h>
#include <config/command_mgr.h>
#include <config/unix_command_mgr.h>
#include <string>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace std;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

// Test class for Unix Command Manager
class UnixCommandMgrTest : public ::testing::Test {
public:
    isc::test::Sandbox sandbox;

    /// Default constructor
    UnixCommandMgrTest() : io_service_(new IOService()) {
        UnixCommandMgr::instance().setIOService(io_service_);
        UnixCommandMgr::instance().closeCommandSockets();
    }

    /// Default destructor
    virtual ~UnixCommandMgrTest() {
        UnixCommandMgr::instance().closeCommandSockets();
    }

    /// @brief Returns socket path (using either hardcoded path or env variable)
    /// @return path to the unix socket
    std::string getSocketPath() {
        std::string socket_path;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path = std::string(env) + "/test-socket";
        } else {
            socket_path = sandbox.join("test-socket");
        }
        return (socket_path);
    }

    /// @brief IO service used by these tests.
    IOServicePtr io_service_;
};

// This test verifies that a Unix socket can be opened properly and that input
// parameters (socket-type and socket-name) are verified.
TEST_F(UnixCommandMgrTest, unixCreate) {
    // Null pointer is obviously a bad idea.
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(ConstElementPtr()),
                 BadSocketInfo);

    // So is passing no parameters.
    ElementPtr socket_info = Element::createMap();
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 BadSocketInfo);

    // We don't support ipx sockets
    socket_info->set("socket-type", Element::create("ipx"));
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 DhcpConfigError);

    socket_info->set("socket-type", Element::create("unix"));
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 BadSocketInfo);

    socket_info->set("socket-name", Element::create(getSocketPath()));
    EXPECT_NO_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info));
    EXPECT_GE(UnixCommandMgr::instance().getControlSocketFD(), 0);

    // It should be possible to close the socket.
    EXPECT_NO_THROW(UnixCommandMgr::instance().closeCommandSocket());
}

// This test checks that when unix path is too long, the socket cannot be opened.
TEST_F(UnixCommandMgrTest, unixCreateTooLong) {
    ElementPtr socket_info = Element::fromJSON("{ \"socket-type\": \"unix\","
        "\"socket-name\": \"/tmp/toolongtoolongtoolongtoolongtoolongtoolong"
        "toolongtoolongtoolongtoolongtoolongtoolongtoolongtoolongtoolong"
        "\" }");

    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 SocketError);
}

// Verifies that a socket cannot be concurrently opened more than once.
// It should be reused instead.
TEST_F(UnixCommandMgrTest, exclusiveOpen) {
    // Pass in valid parameters.
    ElementPtr socket_info = Element::createMap();
    socket_info->set("socket-type", Element::create("unix"));
    socket_info->set("socket-name", Element::create(getSocketPath()));

    EXPECT_NO_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info));
    EXPECT_GE(UnixCommandMgr::instance().getControlSocketFD(), 0);
    int fd = UnixCommandMgr::instance().getControlSocketFD();

    // Should be able to open it twice (reuse).
    EXPECT_NO_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info));
    EXPECT_EQ(fd, UnixCommandMgr::instance().getControlSocketFD());

    // Now let's close it.
    EXPECT_NO_THROW(UnixCommandMgr::instance().closeCommandSockets());

    // Should be able to re-open it now.
    EXPECT_NO_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info));
    EXPECT_GE(UnixCommandMgr::instance().getControlSocketFD(), 0);

    // Now let's close it.
    EXPECT_NO_THROW(UnixCommandMgr::instance().closeCommandSocket());
}
