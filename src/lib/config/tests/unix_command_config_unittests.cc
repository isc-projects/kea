// Copyright (C) 2024-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/command_mgr.h>
#include <config/unix_command_config.h>
#include <http/basic_auth_config.h>
#include <util/filesystem.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <testutils/env_var_wrapper.h>
#include <testutils/log_utils.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace isc::test;
using namespace isc::util;
using namespace isc::dhcp::test;
using namespace std;

namespace {

/// @brief Test fixture for UNIX control socket configuration.
//class UnixCommandConfigTest : public ::testing::Test {
class UnixCommandConfigTest : public LogContentTest {
public:
    /// @brief Constructor.
    UnixCommandConfigTest() : unix_config_() {
        setSocketTestPath();
    }

    /// @brief Destructor.
    ~UnixCommandConfigTest() {
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

    /// @brief UNIX control socket configuration.
    UnixCommandConfigPtr unix_config_;
};

TEST(SocketPathTest, socketDir) {
    EnvVarWrapper env("KEA_CONTROL_SOCKET_DIR");
    env.setValue("");

    auto path = UnixCommandConfig::getSocketPath(true);
    ASSERT_EQ(path, std::string(CONTROL_SOCKET_DIR));

    env.setValue(TEST_DATA_BUILDDIR);
    path = UnixCommandConfig::getSocketPath(true);
    ASSERT_EQ(path, std::string(TEST_DATA_BUILDDIR));
}

// This test verifies the default UNIX control socket configuration.
TEST_F(UnixCommandConfigTest, default) {
    ElementPtr json = Element::createMap();
    ASSERT_THROW(unix_config_.reset(new UnixCommandConfig(json)), DhcpConfigError);
    json->set("socket-name", Element::create("name"));
    ASSERT_NO_THROW_LOG(unix_config_.reset(new UnixCommandConfig(json)));

    // Check default values.
    EXPECT_EQ("unix", unix_config_->getSocketType());
    EXPECT_EQ((UnixCommandConfig::getSocketPath() + "/name"),
              unix_config_->getSocketName());

    std::ostringstream os;
    os << "{ \"socket-type\": \"unix\", \"socket-name\": \""
       << UnixCommandConfig::getSocketPath()
       << "/name\" }";
    runToElementTest(os.str(), *unix_config_);
}

// This test verifies that removing the group execute on the parent directory
// still works for the owner.
TEST_F(UnixCommandConfigTest, group) {
    // Remove the group execute bit on the parent.
    setSocketTestPath();
    const std::string& path = UnixCommandConfig::getSocketPath();
    mode_t perms = file::getPermissions(path);
    EXPECT_EQ(0, ::chmod(path.c_str(), perms & ~S_IWGRP));

    ElementPtr json = Element::createMap();
    ASSERT_THROW(unix_config_.reset(new UnixCommandConfig(json)), DhcpConfigError);
    json->set("socket-name", Element::create("name"));
    ASSERT_NO_THROW_LOG(unix_config_.reset(new UnixCommandConfig(json)));

    // Check default values.
    EXPECT_EQ("unix", unix_config_->getSocketType());
    EXPECT_EQ((UnixCommandConfig::getSocketPath() + "/name"),
              unix_config_->getSocketName());

    std::ostringstream os;
    os << "{ \"socket-type\": \"unix\", \"socket-name\": \""
       << UnixCommandConfig::getSocketPath()
       << "/name\" }";
    runToElementTest(os.str(), *unix_config_);

    // Restore permissions for other tests?
    EXPECT_EQ(0, ::chmod(path.c_str(), perms));
}

// This test verifies direct error cases.
TEST_F(UnixCommandConfigTest, errors) {
    // Error scenarios.
    struct scenario {
        string title;
        string input;
        string msg;
    } scenarios[] = {
        {
            "bad type",
            "[ ]",
            "expected map type (<string>:1:2)"
        },
        {
            "bad socket-type type",
            R"( { "socket-type": 1 } )",
            "invalid type specified for parameter 'socket-type' "
            "(<string>:1:19)"
        },
        {
            "unsupported socket-type",
            R"( { "socket-type": "http" } )",
            "unsupported 'socket-type' 'http' not 'unix'"
        },
        {
            "unsupported socket-address",
            R"( { "socket-address": "::1" } )",
            "parameter 'socket-address' is not supported by UNIX control sockets"
        },
        {
            "bad socket-name type",
            R"( { "socket-name": 8000 } )",
            "invalid type specified for parameter 'socket-name' "
            "(<string>:1:19)"
        },
        {
            "bad socket-name path",
            R"( { "socket-name": "/tmp/mysocket" } )",
            "'socket-name' is invalid: invalid path specified: '/tmp',"
            " supported path is '" + UnixCommandConfig::getSocketPath() + "'"
        }
    };
    for (auto const& s : scenarios) {
        SCOPED_TRACE(s.title);
        ElementPtr json;
        ASSERT_NO_THROW(json = Element::fromJSON(s.input));
        EXPECT_THROW_MSG(unix_config_.reset(new UnixCommandConfig(json)),
                         DhcpConfigError, s.msg);
    }
}

// This test verifies security warning of invalid
// socket paths.
TEST_F(UnixCommandConfigTest, securityEnforcmentFalse) {
    file::PathChecker::enableEnforcement(false);
    std::string config = R"( { "socket-name": "/tmp/mysocket" } )";

    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW_LOG(unix_config_.reset(new UnixCommandConfig(json)));

    std::ostringstream oss;
    oss << "COMMAND_UNIX_SOCKET_PATH_SECURITY_WARNING unix socket path is NOT SECURE:"
        << " invalid path specified: '/tmp', supported path is '"
        << UnixCommandConfig::getSocketPath() <<  "'";

    EXPECT_EQ(1, countFile(oss.str()));
}

// This test verifies security warning of invalid
// socket path permissions.
TEST_F(UnixCommandConfigTest, securityEnforcmentFalsePermissions) {
    setSocketTestPath("/tmp");
    UnixCommandConfig::setSocketPathPerms(0);
    file::PathChecker::enableEnforcement(false);
    std::string config = R"( { "socket-name": "/tmp/mysocket" } )";

    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW_LOG(unix_config_.reset(new UnixCommandConfig(json)));

    std::ostringstream oss;
    oss << "COMMAND_UNIX_SOCKET_PERMISSIONS_SECURITY_WARNING"
        << " unix socket permissions are NOT SECURE: socket path:/tmp"
        << " does not exist or has more relaxed permissions than 0";

    EXPECT_EQ(1, countFile(oss.str()));
}


} // end of anonymous namespace
