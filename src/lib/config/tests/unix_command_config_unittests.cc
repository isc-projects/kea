// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/unix_command_config.h>
#include <util/filesystem.h>
#include <testutils/gtest_utils.h>
#include <testutils/env_var_wrapper.h>

using namespace isc;
using namespace isc::config;
using namespace isc::test;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Test fixture for UNIX control socket configuration.
class UnixCommandConfigTest : public ::testing::Test {
public:
    /// @brief Constructor.
    UnixCommandConfigTest() {
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

} // end of anonymous namespace
