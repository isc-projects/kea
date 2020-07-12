// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/basic_auth_config.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace isc::test;
using namespace std;

namespace {

// Test that basic auth client works as expected.
TEST(BasicHttpAuthClientTest, basic) {
    // Create a client.
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    BasicHttpAuthClient client("foo", "bar", ctx);

    // Check it.
    EXPECT_EQ("foo", client.getUser());
    EXPECT_EQ("bar", client.getPassword());
    EXPECT_TRUE(ctx->equals(*client.getContext()));

    // Check toElement.
    ElementPtr expected = Element::createMap();
    expected->set("user", Element::create(string("foo")));
    expected->set("password", Element::create(string("bar")));
    expected->set("user-context", ctx);
    runToElementTest<BasicHttpAuthClient>(expected, client);
}

// Test that basic auth configuration works as expected.
TEST(BasicHttpAuthConfigTest, basic) {
    // Create a configuration.
    BasicHttpAuthConfig config;

    // Initial configuration is empty.
    EXPECT_TRUE(config.getClientList().empty());
    EXPECT_TRUE(config.getCredentialMap().empty());

    // Add rejects user id with embedded ':'.
    EXPECT_THROW(config.add("foo:", "bar"), BadValue);

    // Add a client.
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    EXPECT_NO_THROW(config.add("foo", "bar", ctx));

    // Check the client.
    ASSERT_EQ(1, config.getClientList().size());
    const BasicHttpAuthClient& client = config.getClientList().front();
    EXPECT_EQ("foo", client.getUser());
    EXPECT_EQ("bar", client.getPassword());
    EXPECT_TRUE(ctx->equals(*client.getContext()));

    // Check the credential.
    ASSERT_NE(0, config.getCredentialMap().count("Zm9vOmJhcg=="));
    string user;
    EXPECT_NO_THROW(user = config.getCredentialMap().at("Zm9vOmJhcg=="));
    EXPECT_EQ("foo", user);

    // Check toElement.
    ElementPtr expected = Element::createList();
    ElementPtr elem = Element::createMap();
    elem->set("user", Element::create(string("foo")));
    elem->set("password", Element::create(string("bar")));
    elem->set("user-context", ctx);
    expected->add(elem);
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // Add a second client and test it.
    EXPECT_NO_THROW(config.add("test", "123\xa3"));
    ASSERT_EQ(2, config.getClientList().size());
    EXPECT_EQ("foo", config.getClientList().front().getUser());
    EXPECT_EQ("test", config.getClientList().back().getUser());
    ASSERT_NE(0, config.getCredentialMap().count("dGVzdDoxMjPCow=="));

    // Check clear.
    config.clear();
    expected = Element::createList();
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // Add clients again.
    EXPECT_NO_THROW(config.add("test", "123\xa3"));
    EXPECT_NO_THROW(config.add("foo", "bar", ctx));

    // Check that toElement keeps add order.
    ElementPtr elem0 = Element::createMap();
    elem0->set("user", Element::create(string("test")));
    elem0->set("password", Element::create(string("123\xa3")));
    expected->add(elem0);
    expected->add(elem);
    runToElementTest<BasicHttpAuthConfig>(expected, config);
}

// Test that basic auth configuration parses.
TEST(BasicHttpAuthConfigTest, parse) {
    BasicHttpAuthConfig config;
    ElementPtr cfg;

    // No config is accepted.
    EXPECT_NO_THROW(config.parse(cfg));
    EXPECT_TRUE(config.getClientList().empty());
    EXPECT_TRUE(config.getCredentialMap().empty());
    runToElementTest<BasicHttpAuthConfig>(Element::createList(), config);

    // The config must be a list.
    cfg = Element::createMap();
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "basic-authentications must be a list (:0:0)");

    // The client config must be a map.
    cfg = Element::createList();
    ElementPtr client_cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "basic-authentications items must be maps (:0:0)");

    // The user parameter is mandatory in client config.
    client_cfg = Element::createMap();
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user is required in basic-authentications items (:0:0)");

    // The user parameter must be a string.
    ElementPtr user_cfg = Element::create(1);
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must be a string (:0:0)");

    // The user parameter must not be empty.
    user_cfg = Element::create(string(""));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must be not be empty (:0:0)");

    // The user parameter must not contain ':'.
    user_cfg = Element::create(string("foo:bar"));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must not contain a ':': 'foo:bar' (:0:0)");

    // Password is not required.
    user_cfg = Element::create(string("foo"));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    ASSERT_EQ(1, config.getClientList().size());
    EXPECT_EQ("", config.getClientList().front().getPassword());
    config.clear();

    // The password parameter must be a string.
    ElementPtr password_cfg = Element::create(1);
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "password must be a string (:0:0)");

    // Empty password is accepted.
    password_cfg = Element::create(string(""));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    ASSERT_EQ(1, config.getClientList().size());
    EXPECT_EQ("", config.getClientList().front().getPassword());
    config.clear();

    // User context must be a map.
    password_cfg = Element::create(string("bar"));
    ElementPtr ctx = Element::createList();
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    client_cfg->set("user-context", ctx);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user-context must be a map (:0:0)");

    // Check a working not empty config.
    ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    client_cfg->set("user-context", ctx);
    cfg = Element::createList();
    cfg->add(client_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    runToElementTest<BasicHttpAuthConfig>(cfg, config);
}

} // end of anonymous namespace
