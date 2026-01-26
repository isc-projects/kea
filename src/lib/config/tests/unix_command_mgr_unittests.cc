// Copyright (C) 2015-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <cc/dhcp_config_error.h>
#include <config/command_mgr.h>
#include <config/testutils/socket_path.h>
#include <config/unix_command_mgr.h>
#include <testutils/gtest_utils.h>
#include <util/filesystem.h>

#include <string>
#include <sys/stat.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::config::test;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

// Test class for Unix Command Manager
class UnixCommandMgrTest : public ::testing::Test {
public:
    /// Default constructor
    UnixCommandMgrTest() : io_service_(new IOService()) {
        resetSocketPath();
        UnixCommandMgr::instance().setIOService(io_service_);
        UnixCommandMgr::instance().closeCommandSockets();
    }

    /// Default destructor
    virtual ~UnixCommandMgrTest() {
        UnixCommandMgr::instance().closeCommandSockets();
        resetSocketPath();
    }

    /// @brief Sets the path in which the socket can be created.
    /// @param explicit_path path to use as the hooks path.
    void setSocketTestPath(const std::string explicit_path = "") {
        UnixCommandConfig::getSocketPath(true,
                                         (!explicit_path.empty() ?
                                          explicit_path : TEST_DATA_BUILDDIR));

        auto path = UnixCommandConfig::getSocketPath();
        UnixCommandConfig::setSocketPathPerms(file::getPermissions(path));
    }

    /// @brief Resets the socket path to the default.
    void resetSocketPath() {
        UnixCommandConfig::getSocketPath(true);
        UnixCommandConfig::setSocketPathPerms();
    }

    /// @brief IO service used by these tests.
    IOServicePtr io_service_;
};

// This test verifies that a Unix socket can be opened properly and that input
// parameters (socket-type and socket-name) are verified.
TEST_F(UnixCommandMgrTest, unixCreate) {
    setSocketTestPath();

    // Null pointer is obviously a bad idea.
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(ConstElementPtr()),
                 BadSocketInfo);

    // So is passing no parameters.
    ElementPtr socket_info = Element::createMap();
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 DhcpConfigError);

    // We don't support ipx sockets
    socket_info->set("socket-type", Element::create("ipx"));
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 DhcpConfigError);

    socket_info->set("socket-type", Element::create("unix"));
    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 DhcpConfigError);

    socket_info->set("socket-name", Element::create("test_socket"));

    bool const too_long(SocketPath::isTooLong("test_socket"));
    if (too_long) {
        // "File name too long"
        EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info), SocketError);
        EXPECT_EQ(UnixCommandMgr::instance().getControlSocketFD(), -1);
        return;
    }

    EXPECT_NO_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info));
    EXPECT_GE(UnixCommandMgr::instance().getControlSocketFD(), 0);

    // It should be possible to close the socket.
    EXPECT_NO_THROW(UnixCommandMgr::instance().closeCommandSocket());
}

// This test checks that when unix path is too long, the socket cannot be opened.
TEST_F(UnixCommandMgrTest, unixCreateTooLong) {
    setSocketTestPath();

    ElementPtr socket_info = Element::fromJSON("{ \"socket-type\": \"unix\","
        "\"socket-name\": \"toolongtoolongtoolongtoolongtoolongtoolong"
        "toolongtoolongtoolongtoolongtoolongtoolongtoolongtoolongtoolong"
        "\" }");

    EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info),
                 SocketError);
}

// Verifies that a socket cannot be concurrently opened more than once.
// It should be reused instead.
TEST_F(UnixCommandMgrTest, exclusiveOpen) {
    setSocketTestPath();

    // Pass in valid parameters.
    ElementPtr socket_info = Element::createMap();
    socket_info->set("socket-type", Element::create("unix"));
    socket_info->set("socket-name", Element::create("test_socket"));

    bool const too_long(SocketPath::isTooLong("test_socket"));
    if (too_long) {
        // "File name too long"
        EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info), SocketError);
        EXPECT_EQ(UnixCommandMgr::instance().getControlSocketFD(), -1);
        return;
    }

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

// Verifies that a socket has group write permission.
TEST_F(UnixCommandMgrTest, groupWritable) {
    setSocketTestPath();

    // Pass in valid parameters.
    ElementPtr socket_info = Element::createMap();
    socket_info->set("socket-type", Element::create("unix"));
    socket_info->set("socket-name", Element::create("test_socket"));

    bool const too_long(SocketPath::isTooLong("test_socket"));
    if (too_long) {
        // "File name too long"
        EXPECT_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info), SocketError);
        EXPECT_EQ(UnixCommandMgr::instance().getControlSocketFD(), -1);
        return;
    }

    EXPECT_NO_THROW(UnixCommandMgr::instance().openCommandSocket(socket_info));
    EXPECT_GE(UnixCommandMgr::instance().getControlSocketFD(), 0);

    // Check permissions on the socket file.
    std::string socket = UnixCommandConfig::getSocketPath() + "/test_socket";
    EXPECT_TRUE(file::isSocket(socket));
    mode_t perms = file::getPermissions(socket);
    EXPECT_EQ(S_IWGRP, perms & S_IWGRP);
}
