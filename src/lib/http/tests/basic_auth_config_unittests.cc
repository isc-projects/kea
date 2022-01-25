// Copyright (C) 2020-2022 Internet Systems Consortium, Inc. ("ISC")
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

string data_dir(DATA_DIR);

// Test that basic auth client works as expected.
TEST(BasicHttpAuthClientTest, basic) {
    // Create a client.
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    BasicHttpAuthClient client("foo", "bar", ctx);

    // Check it.
    EXPECT_EQ("foo", client.getUser());
    EXPECT_EQ("", client.getUserFile());
    EXPECT_EQ("bar", client.getPassword());
    EXPECT_EQ("", client.getPasswordFile());
    EXPECT_FALSE(client.getPasswordFileOnly());
    EXPECT_TRUE(ctx->equals(*client.getContext()));

    // Check toElement.
    ElementPtr expected = Element::createMap();
    expected->set("user", Element::create(string("foo")));
    expected->set("password", Element::create(string("bar")));
    expected->set("user-context", ctx);
    runToElementTest<BasicHttpAuthClient>(expected, client);
}

// Test that basic auth client with files works as expected.
TEST(BasicHttpAuthClientTest, basicFiles) {
    // Create a client.
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    BasicHttpAuthClient client("", "foo", "", "bar", false, ctx);

    // Check it.
    EXPECT_EQ("", client.getUser());
    EXPECT_EQ("foo", client.getUserFile());
    EXPECT_EQ("", client.getPassword());
    EXPECT_EQ("bar", client.getPasswordFile());
    EXPECT_FALSE(client.getPasswordFileOnly());
    EXPECT_TRUE(ctx->equals(*client.getContext()));

    // Check toElement.
    ElementPtr expected = Element::createMap();
    expected->set("user-file", Element::create(string("foo")));
    expected->set("password-file", Element::create(string("bar")));
    expected->set("user-context", ctx);
    runToElementTest<BasicHttpAuthClient>(expected, client);
}

// Test that basic auth client with one file works as expected.
TEST(BasicHttpAuthClientTest, basicOneFile) {
    // Create a client.
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    BasicHttpAuthClient client("", "", "", "foobar", true, ctx);

    // Check it.
    EXPECT_EQ("", client.getUser());
    EXPECT_EQ("", client.getUserFile());
    EXPECT_EQ("", client.getPassword());
    EXPECT_EQ("foobar", client.getPasswordFile());
    EXPECT_TRUE(client.getPasswordFileOnly());
    EXPECT_TRUE(ctx->equals(*client.getContext()));

    // Check toElement.
    ElementPtr expected = Element::createMap();
    expected->set("password-file", Element::create(string("foobar")));
    expected->set("user-context", ctx);
    runToElementTest<BasicHttpAuthClient>(expected, client);
}

// Test that basic auth configuration works as expected.
TEST(BasicHttpAuthConfigTest, basic) {
    // Create a configuration.
    BasicHttpAuthConfig config;

    // Initial configuration is empty.
    EXPECT_TRUE(config.empty());
    EXPECT_TRUE(config.getRealm().empty());
    EXPECT_TRUE(config.getDirectory().empty());
    EXPECT_TRUE(config.getClientList().empty());
    EXPECT_TRUE(config.getCredentialMap().empty());

    // Set the realm, directory and user context.
    EXPECT_NO_THROW(config.setRealm("my-realm"));
    EXPECT_EQ("my-realm", config.getRealm());
    EXPECT_NO_THROW(config.setDirectory("/tmp"));
    EXPECT_EQ("/tmp", config.getDirectory());
    ConstElementPtr horse = Element::fromJSON("{ \"value\": \"a horse\" }");
    EXPECT_NO_THROW(config.setContext(horse));
    EXPECT_TRUE(horse->equals(*config.getContext()));

    // Add rejects user id with embedded ':'.
    EXPECT_THROW(config.add("foo:", "", "bar", ""), BadValue);

    // Add a client.
    EXPECT_TRUE(config.empty());
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    EXPECT_NO_THROW(config.add("foo", "", "bar", "", false, ctx));
    EXPECT_FALSE(config.empty());

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
    ElementPtr expected = Element::createMap();
    ElementPtr clients = Element::createList();
    ElementPtr elem = Element::createMap();
    elem->set("user", Element::create(string("foo")));
    elem->set("password", Element::create(string("bar")));
    elem->set("user-context", ctx);
    clients->add(elem);
    expected->set("type", Element::create(string("basic")));
    expected->set("realm", Element::create(string("my-realm")));
    expected->set("directory", Element::create(string("/tmp")));
    expected->set("user-context", horse);
    expected->set("clients", clients);
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // Add a second client and test it.
    EXPECT_NO_THROW(config.add("test", "", "123\xa3", ""));
    ASSERT_EQ(2, config.getClientList().size());
    EXPECT_EQ("foo", config.getClientList().front().getUser());
    EXPECT_EQ("test", config.getClientList().back().getUser());
    ASSERT_NE(0, config.getCredentialMap().count("dGVzdDoxMjPCow=="));

    // Check clear.
    config.clear();
    EXPECT_TRUE(config.empty());
    expected->set("clients", Element::createList());
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // Add clients again.
    EXPECT_NO_THROW(config.add("test", "", "123\xa3", ""));
    EXPECT_NO_THROW(config.add("foo", "", "bar", "", false, ctx));

    // Check that toElement keeps add order.
    ElementPtr elem0 = Element::createMap();
    elem0->set("user", Element::create(string("test")));
    elem0->set("password", Element::create(string("123\xa3")));
    clients = Element::createList();
    clients->add(elem0);
    clients->add(elem);
    expected->set("clients", clients);
    runToElementTest<BasicHttpAuthConfig>(expected, config);
}

// Test that basic auth configuration with files works as expected.
TEST(BasicHttpAuthConfigTest, basicFiles) {
    // Create a configuration.
    BasicHttpAuthConfig config;

    // Set the realm, directory and user context.
    EXPECT_NO_THROW(config.setRealm("my-realm"));
    EXPECT_EQ("my-realm", config.getRealm());
    EXPECT_NO_THROW(config.setDirectory(data_dir));
    EXPECT_EQ(data_dir, config.getDirectory());
    ConstElementPtr horse = Element::fromJSON("{ \"value\": \"a horse\" }");
    EXPECT_NO_THROW(config.setContext(horse));
    EXPECT_TRUE(horse->equals(*config.getContext()));

    // ':' in user id check is done during parsing

    // Add a client.
    EXPECT_TRUE(config.empty());
    ConstElementPtr ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    EXPECT_NO_THROW(config.add("foo", "", "", "hiddenp", false, ctx));
    EXPECT_FALSE(config.empty());

    // Check the client.
    ASSERT_EQ(1, config.getClientList().size());
    const BasicHttpAuthClient& client = config.getClientList().front();
    EXPECT_EQ("foo", client.getUser());
    EXPECT_EQ("", client.getUserFile());
    EXPECT_EQ("", client.getPassword());
    EXPECT_EQ("hiddenp", client.getPasswordFile());
    EXPECT_FALSE(client.getPasswordFileOnly());
    EXPECT_TRUE(ctx->equals(*client.getContext()));

    // Check toElement.
    ElementPtr expected = Element::createMap();
    ElementPtr clients = Element::createList();
    ElementPtr elem = Element::createMap();
    elem->set("user", Element::create(string("foo")));
    elem->set("password-file", Element::create(string("hiddenp")));
    elem->set("user-context", ctx);
    clients->add(elem);
    expected->set("type", Element::create(string("basic")));
    expected->set("realm", Element::create(string("my-realm")));
    expected->set("directory", Element::create(data_dir));
    expected->set("user-context", horse);
    expected->set("clients", clients);
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // Add a second client and test it.
    EXPECT_NO_THROW(config.add("", "hiddenu", "", "hiddenp"));
    ASSERT_EQ(2, config.getClientList().size());
    EXPECT_EQ("foo", config.getClientList().front().getUser());
    EXPECT_EQ("hiddenu", config.getClientList().back().getUserFile());

    // Check clear.
    config.clear();
    EXPECT_TRUE(config.empty());
    expected->set("clients", Element::createList());
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // Add clients again.
    EXPECT_NO_THROW(config.add("", "hiddenu", "", "hiddenp"));
    EXPECT_NO_THROW(config.add("foo", "", "", "hiddenp", false, ctx));

    // Check that toElement keeps add order.
    ElementPtr elem0 = Element::createMap();
    elem0->set("user-file", Element::create(string("hiddenu")));
    elem0->set("password-file", Element::create(string("hiddenp")));
    clients = Element::createList();
    clients->add(elem0);
    clients->add(elem);
    expected->set("clients", clients);
    runToElementTest<BasicHttpAuthConfig>(expected, config);
}

// Test that basic auth configuration parses.
TEST(BasicHttpAuthConfigTest, parse) {
    BasicHttpAuthConfig config;
    ElementPtr cfg;

    // No config is accepted.
    EXPECT_NO_THROW(config.parse(cfg));
    EXPECT_TRUE(config.empty());
    EXPECT_TRUE(config.getClientList().empty());
    EXPECT_TRUE(config.getCredentialMap().empty());
    ElementPtr expected = Element::createMap();
    expected->set("type", Element::create(string("basic")));
    expected->set("realm", Element::create(string("")));
    expected->set("directory", Element::create(string("")));
    expected->set("clients", Element::createList());
    runToElementTest<BasicHttpAuthConfig>(expected, config);

    // The config must be a map.
    cfg = Element::createList();
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "authentication must be a map (:0:0)");

    // The type must be present.
    cfg = Element::createMap();
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "type is required in authentication (:0:0)");

    // The type must be a string.
    cfg->set("type", Element::create(true));
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "type must be a string (:0:0)");

    // The type must be basic.
    cfg->set("type", Element::create(string("foobar")));
    string errmsg = "only basic HTTP authentication is supported: type is ";
    errmsg += "'foobar' not 'basic' (:0:0)";
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError, errmsg);
    cfg->set("type", Element::create(string("basic")));
    EXPECT_NO_THROW(config.parse(cfg));

    // The realm must be a string.
    cfg->set("realm", Element::createList());
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "realm must be a string (:0:0)");
    cfg->set("realm", Element::create(string("my-realm")));
    EXPECT_NO_THROW(config.parse(cfg));

    // The directory must be a string.
    cfg->set("directory", Element::createMap());
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "directory must be a string (:0:0)");
    cfg->set("directory", Element::create(data_dir));
    EXPECT_NO_THROW(config.parse(cfg));

    // The user context must be a map.
    ElementPtr ctx = Element::createList();
    cfg->set("user-context", ctx);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user-context must be a map (:0:0)");
    ctx = Element::fromJSON("{ \"value\": \"a horse\" }");
    cfg->set("user-context", ctx);
    EXPECT_NO_THROW(config.parse(cfg));

    // Clients must be a list.
    ElementPtr clients_cfg = Element::createMap();
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "clients must be a list (:0:0)");

    // The client config must be a map.
    clients_cfg = Element::createList();
    ElementPtr client_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "clients items must be maps (:0:0)");

    // The user parameter is mandatory in client config
    // without a password file.
    client_cfg = Element::createMap();
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user is required in clients items (:0:0)");

    // The user parameter must be a string.
    ElementPtr user_cfg = Element::create(1);
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must be a string (:0:0)");

    // The user parameter must not be empty.
    user_cfg = Element::create(string(""));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must not be empty (:0:0)");

    // The user parameter must not contain ':'.
    user_cfg = Element::create(string("foo:bar"));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must not contain a ':': 'foo:bar' (:0:0)");

    // The user-file parameter must be a string.
    ElementPtr user_file_cfg = Element::create(1);
    client_cfg = Element::createMap();
    client_cfg->set("user-file", user_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user-file must be a string (:0:0)");

    // The user and user-file parameters are incompatible.
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("user-file", user_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user (:0:0) and user-file (:0:0) are "
                     "mutually exclusive");

    // The user-file parameter must not be empty.
    user_file_cfg = Element::create(string("empty"));
    client_cfg = Element::createMap();
    client_cfg->set("user-file", user_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must not be empty from user-file "
                     "'empty' (:0:0)");

    // The user-file parameter must not contain ':'.
    user_file_cfg = Element::create(string("hiddens"));
    client_cfg = Element::createMap();
    client_cfg->set("user-file", user_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user must not contain a ':' from user-file "
                     "'hiddens' (:0:0)");

    // Password is not required.
    user_cfg = Element::create(string("foo"));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    ASSERT_EQ(1, config.getClientList().size());
    EXPECT_EQ("", config.getClientList().front().getPassword());
    config.clear();

    // The password parameter must be a string.
    ElementPtr password_cfg = Element::create(1);
    client_cfg = Element::createMap();
    client_cfg->set("password", password_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "password must be a string (:0:0)");

    // Empty password is accepted.
    password_cfg = Element::create(string(""));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    ASSERT_EQ(1, config.getClientList().size());
    EXPECT_EQ("", config.getClientList().front().getPassword());
    config.clear();

    // The password-file parameter must be a string.
    ElementPtr password_file_cfg = Element::create(1);
    client_cfg = Element::createMap();
    // user is not required when password-file is here.
    client_cfg->set("password-file", password_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "password-file must be a string (:0:0)");

    // The password and password-file parameters are incompatible.
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    client_cfg->set("password-file", password_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "password (:0:0) and password-file (:0:0) are "
                     "mutually exclusive");

    // Empty password-file is accepted.
    password_file_cfg = Element::create(string("empty"));
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password-file", password_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    ASSERT_EQ(1, config.getClientList().size());
    EXPECT_EQ("", config.getClientList().front().getPassword());
    config.clear();

    // password-file is enough.
    password_file_cfg = Element::create(string("hiddens"));
    client_cfg = Element::createMap();
    client_cfg->set("password-file", password_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    ASSERT_EQ(1, config.getClientList().size());
    EXPECT_EQ("test", config.getClientList().front().getPassword());
    config.clear();

    // password-file only requires a ':' in the content.
    password_file_cfg = Element::create(string("hiddenp"));
    client_cfg = Element::createMap();
    client_cfg->set("password-file", password_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "can't find the user id part in password-file "
                     "'hiddenp' (:0:0)");

    // User context must be a map.
    password_cfg = Element::create(string("bar"));
    ctx = Element::createList();
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    client_cfg->set("user-context", ctx);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_THROW_MSG(config.parse(cfg), DhcpConfigError,
                     "user-context must be a map (:0:0)");

    // Check a working not empty config.
    ctx = Element::fromJSON("{ \"foo\": \"bar\" }");
    client_cfg = Element::createMap();
    client_cfg->set("user", user_cfg);
    client_cfg->set("password", password_cfg);
    client_cfg->set("user-context", ctx);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    runToElementTest<BasicHttpAuthConfig>(cfg, config);

    // Check a working not empty config with files.
    config.clear();
    client_cfg = Element::createMap();
    user_file_cfg = Element::create(string("hiddenu"));
    client_cfg->set("user-file", user_file_cfg);
    client_cfg->set("password-file", password_file_cfg);
    clients_cfg = Element::createList();
    clients_cfg->add(client_cfg);
    cfg->set("clients", clients_cfg);
    EXPECT_NO_THROW(config.parse(cfg));
    runToElementTest<BasicHttpAuthConfig>(cfg, config);
}

} // end of anonymous namespace
