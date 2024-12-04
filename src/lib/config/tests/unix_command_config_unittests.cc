// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/command_mgr.h>
#include <config/unix_command_config.h>
#include <http/basic_auth_config.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace isc::test;
using namespace std;

namespace {

/// @brief Test fixture for UNIX control socket configuration.
class UnixCommandConfigTest : public ::testing::Test {
public:
    /// @brief Constructor.
    UnixCommandConfigTest() : unix_config_() {
    }

    /// @brief Destructor.
    ~UnixCommandConfigTest() {
    }

    /// @brief UNIX control socket configuration.
    UnixCommandConfigPtr unix_config_;
};

// This test verifies the default UNIX control socket configuration.
TEST_F(UnixCommandConfigTest, default) {
    ElementPtr json = Element::createMap();
    ASSERT_THROW(unix_config_.reset(new UnixCommandConfig(json)), BadSocketInfo);
    json->set("socket-name", Element::create("name"));
    ASSERT_NO_THROW_LOG(unix_config_.reset(new UnixCommandConfig(json)));

    // Check default values.
    EXPECT_EQ("unix", unix_config_->getSocketType());
    EXPECT_EQ("name", unix_config_->getSocketName());

    // Check unparse.
    string expected = R"(
        {
            "socket-type": "unix",
            "socket-name": "name"
        }
    )";
    runToElementTest(expected, *unix_config_);
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

} // end of anonymous namespace
