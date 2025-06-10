// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/http_command_config.h>
#include <http/basic_auth_config.h>
#include <util/filesystem.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
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

/// @brief Test fixture for HTTP control socket configuration.
class HttpCommandConfigTest : public LogContentTest {
public:
    /// @brief Constructor.
    HttpCommandConfigTest() : http_config_() {
        HttpCommandConfig::DEFAULT_SOCKET_ADDRESS = IOAddress("127.0.0.1");
        HttpCommandConfig::DEFAULT_SOCKET_PORT = 8000;
        HttpCommandConfig::DEFAULT_AUTHENTICATION_REALM = "";
        file::PathChecker::enableEnforcement(true);
    }

    /// @brief Destructor.
    ~HttpCommandConfigTest() {
        HttpCommandConfig::DEFAULT_SOCKET_ADDRESS = IOAddress("127.0.0.1");
        HttpCommandConfig::DEFAULT_SOCKET_PORT = 8000;
        HttpCommandConfig::DEFAULT_AUTHENTICATION_REALM = "";
        file::PathChecker::enableEnforcement(true);
    }

    /// @brief HTTP control socket configuration.
    HttpCommandConfigPtr http_config_;
};

// This test verifies the default HTTP control socket configuration.
TEST_F(HttpCommandConfigTest, default) {
    // "Default" config should throw since security is enabled.
    ElementPtr json = Element::createMap();
    ASSERT_THROW_MSG(http_config_.reset(new HttpCommandConfig(json)),
                     DhcpConfigError, "Unsecured HTTP control channel (:0:0)");

    // Turn off security enforcment. Configuration will succeed but we
    // should see WARN logs.
    file::PathChecker::enableEnforcement(false);
    ASSERT_NO_THROW_LOG(http_config_.reset(new HttpCommandConfig(json)));

    // Check default values.
    EXPECT_EQ("http", http_config_->getSocketType());
    EXPECT_EQ("127.0.0.1", http_config_->getSocketAddress().toText());
    EXPECT_EQ(8000, http_config_->getSocketPort());
    EXPECT_TRUE(http_config_->getHttpHeaders().empty());
    EXPECT_FALSE(http_config_->getAuthConfig());
    EXPECT_EQ("", http_config_->getTrustAnchor());
    EXPECT_EQ("", http_config_->getCertFile());
    EXPECT_EQ("", http_config_->getKeyFile());
    EXPECT_TRUE(http_config_->getCertRequired());
    EXPECT_TRUE(http_config_->getEmulateAgentResponse());

    // Check unparse.
    string expected = R"(
        {
            "socket-type": "http",
            "socket-address": "127.0.0.1",
            "socket-port": 8000
        }
    )";
    runToElementTest(expected, *http_config_);

    ASSERT_EQ(1, countFile("COMMAND_HTTP_SOCKET_SECURITY_WARN command socket"
                           " configuration is NOT SECURE: {  }"));

    // Change class defaults.
    HttpCommandConfig::DEFAULT_SOCKET_ADDRESS = IOAddress("::1");
    HttpCommandConfig::DEFAULT_SOCKET_PORT = 8080;
    ASSERT_NO_THROW_LOG(http_config_.reset(new HttpCommandConfig(json)));
    EXPECT_EQ("::1", http_config_->getSocketAddress().toText());
    EXPECT_EQ(8080, http_config_->getSocketPort());

    ASSERT_EQ(2, countFile("COMMAND_HTTP_SOCKET_SECURITY_WARN command socket"
                           " configuration is NOT SECURE: {  }"));
}

// This test verifies direct error cases.
TEST_F(HttpCommandConfigTest, errors) {
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
            R"( { "socket-type": "unix" } )",
            "unsupported 'socket-type' 'unix' not 'http' or 'https'"
        },
        {
            "unsupported socket-name",
            R"( { "socket-name": "::1" } )",
            "parameter 'socket-name' is not supported by HTTP control sockets"
        },
        {
            "bad socket-address type",
            R"( { "socket-address": 8000 } )",
            "invalid type specified for parameter 'socket-address' "
            "(<string>:1:22)"
        },
        {
            "bad address",
            R"( { "socket-address": ":::" } )",
            "failed to convert ':::' to address: "
            "Failed to convert string to address ':::': Invalid argument "
            "(<string>:1:22)"
        },
        {
            "bad socket-port type",
            R"( { "socket-port": "8000" } )",
            "invalid type specified for parameter 'socket-port' "
            "(<string>:1:19)"
        },
        {
            "socket-port negative",
            R"( { "socket-port": -1 } )",
            "out of range value -1 specified for parameter 'socket-port' "
            "(<string>:1:19)"
        },
        {
            "bad authentication type",
            R"( { "authentication": "none" } )",
            "invalid type specified for parameter 'authentication' "
            "(<string>:1:22)"
        },
        // Authentication parsing failures are checked at another place.
        {
            "bad trust-anchor type",
            R"( { "trust-anchor": false } )",
            "invalid type specified for parameter 'trust-anchor' "
            "(<string>:1:20)"
        },
        {
            "bad cert-file type",
            R"( { "cert-file": false } )",
            "invalid type specified for parameter 'cert-file' "
            "(<string>:1:17)"
        },
        {
            "bad key-file type",
            R"( { "key-file": false } )",
            "invalid type specified for parameter 'key-file' "
            "(<string>:1:16)"
        },
        {
            "bad cert-required type",
            R"( { "cert-required": 0 } )",
            "invalid type specified for parameter 'cert-required' "
            "(<string>:1:21)"
        },
        {
            "https requires TLS",
            R"( { "socket-type": "https" } )",
            "no TLS setup for a HTTPS control socket"
        },
        {
            "missing trust-anchor",
            R"( { "cert-file": "foo" } )",
            "trust-anchor parameter is missing or empty:"
            " all or none of TLS parameters must be set"
        },
        {
            "empty trust-anchor",
            R"( { "trust-anchor": "", "cert-file": "foo" } )",
            "trust-anchor parameter is missing or empty:"
            " all or none of TLS parameters must be set"
        },
        {
            "missing cert-file",
            R"( { "trust-anchor": "foo" } )",
            "cert-file parameter is missing or empty:"
            " all or none of TLS parameters must be set"
        },
        {
            "empty cert-file",
            R"( { "trust-anchor": "foo", "cert-file": "" } )",
            "cert-file parameter is missing or empty:"
            " all or none of TLS parameters must be set"
        },
        {
            "missing key-file",
            R"( { "trust-anchor": "foo", "cert-file": "bar" } )",
            "key-file parameter is missing or empty:"
            " all or none of TLS parameters must be set"
        },
        {
            "empty key-file",
            R"( {
                        "trust-anchor": "foo",
                        "cert-file": "bar",
                        "key-file": ""
                     } )",
            "key-file parameter is missing or empty:"
            " all or none of TLS parameters must be set"
        }
    };
    for (auto const& s : scenarios) {
        SCOPED_TRACE(s.title);
        ElementPtr json;
        ASSERT_NO_THROW(json = Element::fromJSON(s.input));
        EXPECT_THROW_MSG(http_config_.reset(new HttpCommandConfig(json)),
                         DhcpConfigError, s.msg);
    }
}

// This test verifies a HTTP control socket configuration with HTTP headers
// can be parsed and unparsed.
TEST_F(HttpCommandConfigTest, headers) {
    // Disable security enforcement.
    file::PathChecker::enableEnforcement(false);
    // Configure with HTTP headers.
    string config = R"(
    {
        "http-headers": [
            {
                "name": "Strict-Transport-Security",
                "value": "max-age=31536000"
            },
            {
                "name": "Foo",
                "value": "bar"
            }
        ]
    })";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW(http_config_.reset(new HttpCommandConfig(json)));

    // Verify HTTP headers.
    auto headers = http_config_->getHttpHeaders();
    ASSERT_EQ(2, headers.size());
    EXPECT_EQ("Strict-Transport-Security", headers[0].name_);
    EXPECT_EQ("max-age=31536000", headers[0].value_);
    EXPECT_EQ("Foo", headers[1].name_);
    EXPECT_EQ("bar", headers[1].value_);

    // Check unparse.
    string expected = R"(
    {
        "socket-type": "http",
        "socket-address": "127.0.0.1",
        "socket-port": 8000,
        "http-headers": [
            {
                "name": "Strict-Transport-Security",
                "value": "max-age=31536000"
            },
            {
                "name": "Foo",
                "value": "bar"
            }
        ]
    })";
    runToElementTest(expected, *http_config_);

    // Should have security WARN log.
    ASSERT_EQ(1, countFile("COMMAND_HTTP_SOCKET_SECURITY_WARN command socket"
                           " configuration is NOT SECURE: { \"http-headers\": "
                           "[ { \"name\": \"Strict-Transport-Security\", \"value\":"
                           " \"max-age=31536000\" }, { \"name\": \"Foo\", \"value\": \"bar\""
                           " } ] }"));
}

// This test verifies a HTTP control socket configuration with authentication
// can be parsed and unparsed.
TEST_F(HttpCommandConfigTest, authentication) {
    // Configure with authentication.
    string config = R"(
    {
        "authentication": {
            "clients": [ {
                "user": "admin",
                "password": "foobar"
            } ]
        }
    })";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW(http_config_.reset(new HttpCommandConfig(json)));

    // Verify the authentication and its defaults.
    auto auth_config = http_config_->getAuthConfig();
    ASSERT_TRUE(auth_config);
    EXPECT_EQ("", auth_config->getRealm());
    BasicHttpAuthConfigPtr auth =
        boost::dynamic_pointer_cast<BasicHttpAuthConfig>(auth_config);
    ASSERT_TRUE(auth);

    // Verify that default realm is applied.
    HttpCommandConfig::DEFAULT_AUTHENTICATION_REALM = "FOO";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW(http_config_.reset(new HttpCommandConfig(json)));
    auth_config = http_config_->getAuthConfig();
    ASSERT_TRUE(auth_config);
    EXPECT_EQ("FOO", auth_config->getRealm());

    // Verify that default is applied only when not configured.
    config = R"(
    {
        "authentication": {
            "realm": "BAR",
            "clients": [ {
                "user": "admin",
                "password": "foobar"
            } ]
        }
    })";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW(http_config_.reset(new HttpCommandConfig(json)));
    auth_config = http_config_->getAuthConfig();
    ASSERT_TRUE(auth_config);
    EXPECT_EQ("BAR", auth_config->getRealm());

    // Check unparse.
    string expected = R"(
    {
        "socket-type": "http",
        "socket-address": "127.0.0.1",
        "socket-port": 8000,
        "authentication": {
            "type": "basic",
            "realm": "BAR",
            "directory": "",
            "clients": [ {
                "user": "admin",
                "password": "foobar"
            } ]
        }
    })";
    runToElementTest(expected, *http_config_);

    // Should be no security warnings.
    ASSERT_EQ(0, countFile("COMMAND_HTTP_SOCKET_SECURITY_WARN")); 
}

// This test verifies a HTTP control socket configuration with TLS can
// be parsed and unparsed.
TEST_F(HttpCommandConfigTest, tls) {
    // Configure with TLS.
    string config = R"(
    {
        "trust-anchor": "my ca",
        "cert-file": "my cert",
        "key-file": "my key",
        "cert-required": false
    })";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_NO_THROW(http_config_.reset(new HttpCommandConfig(json)));
    EXPECT_EQ("http", http_config_->getSocketType());
    EXPECT_EQ("127.0.0.1", http_config_->getSocketAddress().toText());
    EXPECT_EQ(8000, http_config_->getSocketPort());
    EXPECT_FALSE(http_config_->getAuthConfig());
    EXPECT_EQ("my ca", http_config_->getTrustAnchor());
    EXPECT_EQ("my cert", http_config_->getCertFile());
    EXPECT_EQ("my key", http_config_->getKeyFile());
    EXPECT_FALSE(http_config_->getCertRequired());
    EXPECT_TRUE(http_config_->getEmulateAgentResponse());

    // Check unparse.
    string expected = R"(
    {
        "socket-type": "http",
        "socket-address": "127.0.0.1",
        "socket-port": 8000,
        "trust-anchor": "my ca",
        "cert-file": "my cert",
        "key-file": "my key",
        "cert-required": false
    })";
    runToElementTest(expected, *http_config_);
}

} // end of anonymous namespace
