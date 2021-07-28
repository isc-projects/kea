// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/netconf_cfg_mgr.h>
#include <netconf/parser_context.h>
#include <exceptions/exceptions.h>
#include <cc/command_interpreter.h>
#include <process/testutils/d_test_stubs.h>
#include <process/d_cfg_mgr.h>
#include <yang/yang_models.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <netconf/tests/test_libraries.h>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::netconf;
using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::process;
using namespace isc::yang;

namespace  {

/// @brief Almost regular netconf CfgMgr with internal parse method exposed.
class NakedNetconfCfgMgr : public NetconfCfgMgr {
public:
    using NetconfCfgMgr::parse;
};

// Tests construction of NetconfCfgMgr class.
TEST(NetconfCfgMgr, construction) {
    boost::scoped_ptr<NetconfCfgMgr> cfg_mgr;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW_LOG(cfg_mgr.reset(new NetconfCfgMgr()));

    // Verify that the context can be retrieved and is not null.
    NetconfConfigPtr context;
    ASSERT_NO_THROW_LOG(context = cfg_mgr->getNetconfConfig());
    EXPECT_TRUE(context);

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());
}

// Tests if getContext can be retrieved.
TEST(NetconfCfgMgr, getContext) {
    NetconfCfgMgr cfg_mgr;

    NetconfConfigPtr ctx;
    ASSERT_NO_THROW_LOG(ctx = cfg_mgr.getNetconfConfig());
    ASSERT_TRUE(ctx);
}

// Tests if context can store and retrieve managed server information.
TEST(NetconfCfgMgr, contextServer) {

    NetconfConfig ctx;

    // Check managed server parameters.
    // By default, there are no server stored.
    ASSERT_TRUE(ctx.getCfgServersMap());
    EXPECT_EQ(0, ctx.getCfgServersMap()->size());

    CfgControlSocketPtr
        socket1(new CfgControlSocket(CfgControlSocket::Type::UNIX,
                                     "socket1",
                                     Url("http://127.0.0.1:8000/")));
    CfgServerPtr server1(new CfgServer("model1", socket1));
    CfgControlSocketPtr
        socket2(new CfgControlSocket(CfgControlSocket::Type::UNIX,
                                     "socket2",
                                     Url("http://127.0.0.1:8000/")));
    CfgServerPtr server2(new CfgServer("model2", socket2));
    CfgControlSocketPtr
        socket3(new CfgControlSocket(CfgControlSocket::Type::UNIX,
                                     "socket3",
                                     Url("http://127.0.0.1:8000/")));
    CfgServerPtr server3(new CfgServer("model3", socket3));
    CfgControlSocketPtr
        socket4(new CfgControlSocket(CfgControlSocket::Type::UNIX,
                                     "socket4",
                                     Url("http://127.0.0.1:8000/")));
    CfgServerPtr server4(new CfgServer("model4", socket4));

    // Ok, now set the server for D2
    EXPECT_NO_THROW(ctx.getCfgServersMap()->insert(make_pair("d2", server1)));

    // Now check the values returned
    EXPECT_EQ(1, ctx.getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx.getCfgServersMap()->at("d2"));
    EXPECT_EQ(server1, ctx.getCfgServersMap()->at("d2"));
    EXPECT_THROW(ctx.getCfgServersMap()->at("dhcp4"), std::out_of_range);

    // Now set the v6 server and sanity check again
    EXPECT_NO_THROW(ctx.getCfgServersMap()->insert(make_pair("dhcp6", server2)));

    // Should be possible to retrieve two servers
    EXPECT_EQ(2, ctx.getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx.getCfgServersMap()->at("dhcp6"));
    EXPECT_EQ(server1, ctx.getCfgServersMap()->at("d2"));
    EXPECT_EQ(server2, ctx.getCfgServersMap()->at("dhcp6"));

    // Finally, set all servers.
    EXPECT_NO_THROW(ctx.getCfgServersMap()->insert(make_pair("dhcp4", server3)));
    EXPECT_NO_THROW(ctx.getCfgServersMap()->insert(make_pair("ca", server4)));
    EXPECT_EQ(4, ctx.getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx.getCfgServersMap()->at("dhcp4"));
    ASSERT_NO_THROW_LOG(ctx.getCfgServersMap()->at("ca"));
    EXPECT_EQ(server3, ctx.getCfgServersMap()->at("dhcp4"));
    EXPECT_EQ(server4, ctx.getCfgServersMap()->at("ca"));
}

// Tests if the context can store and retrieve hook libs information.
TEST(NetconfCfgMgr, contextHookParams) {
    NetconfConfig ctx;

    // By default there should be no hooks.
    HooksConfig& libs = ctx.getHooksConfig();
    EXPECT_TRUE(libs.get().empty());

    libs.add("libone.so", ConstElementPtr());
    libs.add("libtwo.so", Element::fromJSON("{\"foo\": true}"));
    libs.add("libthree.so", Element::fromJSON("{\"bar\": 42}"));

    const HooksConfig& stored_libs = ctx.getHooksConfig();
    EXPECT_EQ(3, stored_libs.get().size());

    EXPECT_EQ(libs.get(), stored_libs.get());
}

// Tests if the context can store and retrieve globals.
TEST(NetconfCfgMgr, contextGlobals) {
    NetconfConfig ctx;

    // By default there should be no globals.
    ConstElementPtr globals = ctx.getConfiguredGlobals();
    ASSERT_TRUE(globals);
    ASSERT_EQ(Element::map, globals->getType());
    EXPECT_EQ(0, globals->mapValue().size());

    // Attempting to extract globals from a non-map should throw.
    ASSERT_THROW(ctx.extractConfiguredGlobals(Element::create(777)), BadValue);

    // Now let's create a configuration from which to extract global scalars.
    // Extraction (currently) has no business logic, so the elements we use
    // can be arbitrary.
    ConstElementPtr global_cfg;
    string global_cfg_str =
    "{\n"
    " \"astring\": \"okay\",\n"
    " \"amap\": { \"not-this\":777, \"not-that\": \"poo\" },\n"
    " \"anint\": 444,\n"
    " \"alist\": [ 1, 2, 3 ],\n"
    " \"abool\": true\n"
        "}\n";
    ASSERT_NO_THROW_LOG(global_cfg = Element::fromJSON(global_cfg_str));

    // Extract globals from the config.
    ASSERT_NO_THROW_LOG(ctx.extractConfiguredGlobals(global_cfg));

    // Now see if the extract was correct.
    globals = ctx.getConfiguredGlobals();
    ASSERT_TRUE(globals);
    ASSERT_EQ(Element::map, globals->getType());
    EXPECT_NE(0, globals->mapValue().size());

    // Maps and lists should be excluded.
    for (auto it : globals->mapValue()) {
        if (it.first == "astring") {
            ASSERT_EQ(Element::string, it.second->getType());
            EXPECT_EQ("okay", it.second->stringValue());
        } else if (it.first == "anint") {
            ASSERT_EQ(Element::integer, it.second->getType());
            EXPECT_EQ(444, it.second->intValue());
        } else if (it.first == "abool") {
            ASSERT_EQ(Element::boolean, it.second->getType());
            EXPECT_TRUE(it.second->boolValue());
        } else {
            ADD_FAILURE() << "unexpected element found:" << it.first;
        }
    }
}

/// @brief Netconf configurations used in tests.
const char* NETCONF_CONFIGS[] = {

    // configuration 0: empty (nothing specified)
    "{ }",

    // Configuration 1: global parameters only (no server, not hooks)
    "{\n"
    "    \"boot-update\": false,\n"
    "    \"subscribe-changes\": false,\n"
    "    \"validate-changes\": false\n"
    "}",

    // Configuration 2: 1 server
    "{\n"
    "    \"boot-update\": false,\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp4\": {\n"
    "            \"boot-update\": true,\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v4\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 3: all 4 servers
    "{\n"
    "    \"boot-update\": false,\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp4\": {\n"
    "            \"boot-update\": true,\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v4\"\n"
    "            }\n"
    "        },\n"
    "        \"dhcp6\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v6\"\n"
    "            }\n"
    "        },\n"
    "        \"d2\": {\n"
    "            \"subscribe-changes\": false,\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-d2\"\n"
    "            }\n"
    "        },\n"
    "        \"ca\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-ca\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 4: 1 server and hooks
    // Netconf is able to load hook libraries that augment its operation.
    // The primary functionality is the ability to add new commands.
    "{\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp4\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v4\"\n"
    "            }\n"
    "        }\n"
    "    },\n"
    "    \"hooks-libraries\": ["
    "        {"
    "          \"library\": \"%LIBRARY%\","
    "              \"parameters\": {\n"
    "              \"param1\": \"foo\"\n"
    "            }\n"
    "        }\n"
    "     ]\n"
    "}",

    // Configuration 5: 1 server (d2 only)
    "{\n"
    "    \"managed-servers\": {\n"
    "        \"d2\": {\n"
    "            \"subscribe-changes\": false,\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-d2\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 6: 1 server (dhcp6 only)
    "{\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp6\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v6\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 7: 2 servers with user contexts and comments
    "{\n"
    "    \"user-context\": { \"comment\": \"Indirect comment\" },\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp4\": {\n"
    "            \"comment\": \"dhcp4 server\",\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v4\"\n"
    "            }\n"
    "        },\n"
    "        \"dhcp6\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-name\": \"/tmp/socket-v6\",\n"
    "                \"user-context\": { \"version\": 1 }\n"
    "            }\n"
    "        }\n"
    "   }\n"
    "}",

    // Configuration 8: empty server with no control socket
    "{\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp4\": {\n"
    "            \"comment\": \"empty map not allowed\"\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 9: empty control socket
    "{\n"
    "    \"boot-update\": false,\n"
    "    \"subscribe-changes\": false,\n"
    "    \"validate-changes\": false,\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp4\": {\n"
    "            \"control-socket\": {\n"
    "                \"comment\": \"empty map not allowed\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 10: bad socket type
    "{\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp6\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-type\": \"tcp\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 11: invalid socket Url
    "{\n"
    "    \"managed-servers\": {\n"
    "        \"dhcp6\": {\n"
    "            \"control-socket\": {\n"
    "                \"socket-url\": \"bad\"\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}"
};

// Tests the handling of bad socket type. Can't use the fixture class
// because the Netconf parser does not allow bad socket types.
TEST(NetconfParser, badSocketType) {
    ConstElementPtr json;
    ParserContext parser;
    EXPECT_NO_THROW(json = parser.parseString(NETCONF_CONFIGS[10],
                                              ParserContext::PARSER_JSON));
    ConstElementPtr answer;
    NakedNetconfCfgMgr cfg_mgr;
    EXPECT_NO_THROW(answer = cfg_mgr.parse(json, false));
    int rcode = 0;
    string expected =
        "\"Unknown control socket type: tcp 'tcp' (<string>:5:32)\"";
    EXPECT_EQ(expected, parseAnswer(rcode, answer)->str());
    EXPECT_EQ(1, rcode);
}

/// @brief Class used for testing CfgMgr
class NetconfParserTest : public isc::process::ConfigParseTest {
public:

    /// @brief Tries to load input text as a configuration
    ///
    /// @param config text containing input configuration
    /// @param expected_answer expected result of configuration (0 = success)
    void configParse(const char* config, int expected_answer) {
        isc::netconf::ParserContext parser;
        ConstElementPtr json = parser.parseString(config, ParserContext::PARSER_SUB_NETCONF);

        EXPECT_NO_THROW(answer_ = cfg_mgr_.parse(json, false));
        EXPECT_TRUE(checkAnswer(expected_answer));
    }

    /// @brief Replaces %LIBRARY% with specified library name
    ///
    /// @param config input config text (should contain "%LIBRARY%" string)
    /// @param lib_name %LIBRARY% will be replaced with that name
    /// @return configuration text with library name replaced
    string pathReplacer(const char* config, const char* lib_name) {
        string txt(config);
        txt.replace(txt.find("%LIBRARY%"), strlen("%LIBRARY%"), string(lib_name));
        return (txt);
    }

    /// Configuration Manager (used in tests)
    NakedNetconfCfgMgr cfg_mgr_;
};

// This test verifies if an empty config is handled properly. In practice such
// a config makes little sense, but perhaps it's ok for a default deployment.
TEST_F(NetconfParserTest, configParseEmpty) {
    configParse(NETCONF_CONFIGS[0], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(0, ctx->getCfgServersMap()->size());
}

// This test verifies if a config with only globals is handled properly.
TEST_F(NetconfParserTest, configParseGlobalOnly) {
    configParse(NETCONF_CONFIGS[1], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(0, ctx->getCfgServersMap()->size());
    ConstElementPtr globals = ctx->getConfiguredGlobals();
    ASSERT_TRUE(globals);
    string expected = "{ "
        "\"boot-update\": false, "
        "\"subscribe-changes\": false, "
        "\"validate-changes\": false }";
    EXPECT_EQ(expected, globals->str());
}

// Tests if an empty (i.e. without a control socket) can be configured.
// Note that the syntax required the server map to not be really empty.
TEST_F(NetconfParserTest, configParseEmptyCfgServer) {
    configParse(NETCONF_CONFIGS[8], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(1, ctx->getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("dhcp4"));
    CfgServerPtr server = ctx->getCfgServersMap()->at("dhcp4");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP4_SERVER, server->getModel());
    // Defaults.
    EXPECT_TRUE(server->getBootUpdate());
    EXPECT_TRUE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    EXPECT_FALSE(socket);
}

// This tests default values using a server with empty control socket
// Note that the syntax required the control socket map to not be really empty.
TEST_F(NetconfParserTest, configParseDefaults) {
    configParse(NETCONF_CONFIGS[9], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(1, ctx->getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("dhcp4"));
    CfgServerPtr server = ctx->getCfgServersMap()->at("dhcp4");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP4_SERVER, server->getModel());
    // Globals overwrite defaults.
    EXPECT_FALSE(server->getBootUpdate());
    EXPECT_FALSE(server->getSubscribeChanges());
    EXPECT_FALSE(server->getValidateChanges());
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);

    // Checking default.
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());
}

// Tests if a single DHCPv4 server can be configured.
TEST_F(NetconfParserTest, configParseServerDhcp4) {
    configParse(NETCONF_CONFIGS[2], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(1, ctx->getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("dhcp4"));
    CfgServerPtr server = ctx->getCfgServersMap()->at("dhcp4");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP4_SERVER, server->getModel());
    // Locals overwrite globals.
    EXPECT_TRUE(server->getBootUpdate());
    EXPECT_TRUE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-v4", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());
}

// Tests if a single D2 server can be configured.
TEST_F(NetconfParserTest, configParseServerD2) {
    configParse(NETCONF_CONFIGS[5], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(1, ctx->getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("d2"));
    CfgServerPtr server = ctx->getCfgServersMap()->at("d2");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP_DDNS, server->getModel());
    EXPECT_TRUE(server->getBootUpdate());
    EXPECT_FALSE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-d2", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());
}

// Tests if a single DHCPv6 server can be configured.
TEST_F(NetconfParserTest, configParseServerDhcp6) {
    configParse(NETCONF_CONFIGS[6], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(1, ctx->getCfgServersMap()->size());
    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("dhcp6"));
    CfgServerPtr server = ctx->getCfgServersMap()->at("dhcp6");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP6_SERVER, server->getModel());
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-v6", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());
}

// This tests if all 4 servers can be configured and makes sure the parser
// doesn't confuse them.
TEST_F(NetconfParserTest, configParse4Servers) {
    configParse(NETCONF_CONFIGS[3], 0);

    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(ctx);
    ASSERT_TRUE(ctx->getCfgServersMap());
    EXPECT_EQ(4, ctx->getCfgServersMap()->size());

    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("dhcp4"));
    CfgServerPtr server = ctx->getCfgServersMap()->at("dhcp4");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP4_SERVER, server->getModel());
    EXPECT_TRUE(server->getBootUpdate());
    EXPECT_TRUE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-v4", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());

    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("dhcp6"));
    server = ctx->getCfgServersMap()->at("dhcp6");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP6_SERVER, server->getModel());
    socket = server->getCfgControlSocket();
    EXPECT_FALSE(server->getBootUpdate());
    EXPECT_TRUE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-v6", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());

    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("d2"));
    server = ctx->getCfgServersMap()->at("d2");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_DHCP_DDNS, server->getModel());
    EXPECT_FALSE(server->getBootUpdate());
    EXPECT_FALSE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-d2", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());

    ASSERT_NO_THROW_LOG(ctx->getCfgServersMap()->at("ca"));
    server = ctx->getCfgServersMap()->at("ca");
    ASSERT_TRUE(server);
    EXPECT_EQ(KEA_CTRL_AGENT, server->getModel());
    EXPECT_FALSE(server->getBootUpdate());
    EXPECT_TRUE(server->getSubscribeChanges());
    EXPECT_TRUE(server->getValidateChanges());
    socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);
    EXPECT_EQ(CfgControlSocket::Type::STDOUT, socket->getType());
    EXPECT_EQ("/tmp/socket-ca", socket->getName());
    EXPECT_EQ("http://127.0.0.1:8000/", socket->getUrl().toText());

    // Check unparsing.
    string expected =  "{\n"
        "    \"Netconf\": {\n"
        "        \"boot-update\": false,\n"
        "        \"managed-servers\": {\n"
        "            \"dhcp4\": {\n"
        "                \"model\": \"kea-dhcp4-server\",\n"
        "                \"boot-update\": true,\n"
        "                \"subscribe-changes\": true,\n"
        "                \"validate-changes\": true,\n"
        "                \"control-socket\": {\n"
        "                    \"socket-type\": \"stdout\",\n"
        "                    \"socket-name\": \"/tmp/socket-v4\",\n"
        "                    \"socket-url\": \"http://127.0.0.1:8000/\"\n"
        "                }\n"
        "            },\n"
        "            \"dhcp6\": {\n"
        "                \"model\": \"kea-dhcp6-server\",\n"
        "                \"boot-update\": false,\n"
        "                \"subscribe-changes\": true,\n"
        "                \"validate-changes\": true,\n"
        "                \"control-socket\": {\n"
        "                    \"socket-type\": \"stdout\",\n"
        "                    \"socket-name\": \"/tmp/socket-v6\",\n"
        "                    \"socket-url\": \"http://127.0.0.1:8000/\"\n"
        "                }\n"
        "            },\n"
        "            \"d2\": {\n"
        "                \"model\": \"kea-dhcp-ddns\",\n"
        "                \"boot-update\": false,\n"
        "                \"subscribe-changes\": false,\n"
        "                \"validate-changes\": true,\n"
        "                \"control-socket\": {\n"
        "                    \"socket-type\": \"stdout\",\n"
        "                    \"socket-name\": \"/tmp/socket-d2\",\n"
        "                    \"socket-url\": \"http://127.0.0.1:8000/\"\n"
        "                }\n"
        "            },\n"
        "            \"ca\": {\n"
        "                \"model\": \"kea-ctrl-agent\",\n"
        "                \"boot-update\": false,\n"
        "                \"subscribe-changes\": true,\n"
        "                \"validate-changes\": true,\n"
        "                \"control-socket\": {\n"
        "                    \"socket-type\": \"stdout\",\n"
        "                    \"socket-name\": \"/tmp/socket-ca\",\n"
        "                    \"socket-url\": \"http://127.0.0.1:8000/\"\n"
        "                }\n"
        "            }\n"
        "        },\n"
        "        \"hooks-libraries\": [ ]\n"
        "    }\n"
        "}";
    isc::test::runToElementTest<NetconfConfig>(expected, *ctx);
}

// Tests the handling of invalid socket URL.
TEST_F(NetconfParserTest, configParseInvalidSocketUrl) {
    configParse(NETCONF_CONFIGS[11], 1);
    int rcode = 0;
    string expected =
        "\"invalid control socket url: url bad lacks http or https scheme "
        "'bad' (<string>:5:31)\"";
    EXPECT_EQ(expected, parseAnswer(rcode, answer_)->str());
}

// This test checks that the config file with hook library specified can be
// loaded. This one is a bit tricky, because the parser sanity checks the lib
// name. In particular, it checks if such a library exists. Therefore we
// can't use NETCONF_CONFIGS[4] as is, but need to run it through path replacer.
TEST_F(NetconfParserTest, configParseHooks) {
    // Create the configuration with proper lib path.
    string cfg = pathReplacer(NETCONF_CONFIGS[4], BASIC_CALLOUT_LIBRARY);
    // The configuration should be successful.
    configParse(cfg.c_str(), 0);

    // The context now should have the library specified.
    NetconfConfigPtr ctx = cfg_mgr_.getNetconfConfig();
    const HookLibsCollection libs = ctx->getHooksConfig().get();
    ASSERT_EQ(1, libs.size());
    EXPECT_EQ(string(BASIC_CALLOUT_LIBRARY), libs[0].first);
    ASSERT_TRUE(libs[0].second);
    EXPECT_EQ("{ \"param1\": \"foo\" }", libs[0].second->str());
}

// This test checks comments.
TEST_F(NetconfParserTest, comments) {
    configParse(NETCONF_CONFIGS[7], 0);
    NetconfConfigPtr netconf_ctx = cfg_mgr_.getNetconfConfig();
    ASSERT_TRUE(netconf_ctx);

    // Check global user context.
    ConstElementPtr ctx = netconf_ctx->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(1, ctx->size());
    ASSERT_TRUE(ctx->get("comment"));
    EXPECT_EQ("\"Indirect comment\"", ctx->get("comment")->str());

    // There is a DHCP4 server.
    ASSERT_TRUE(netconf_ctx->getCfgServersMap());
    ASSERT_NO_THROW_LOG(netconf_ctx->getCfgServersMap()->at("dhcp4"));
    CfgServerPtr server = netconf_ctx->getCfgServersMap()->at("dhcp4");
    ASSERT_TRUE(server);

    // Check DHCP4 server user context.
    ConstElementPtr ctx4 = server->getContext();
    ASSERT_TRUE(ctx4);
    ASSERT_EQ(1, ctx4->size());
    ASSERT_TRUE(ctx4->get("comment"));
    EXPECT_EQ("\"dhcp4 server\"", ctx4->get("comment")->str());

    // There is a DHCP6 server.
    ASSERT_NO_THROW_LOG(netconf_ctx->getCfgServersMap()->at("dhcp6"));
    server = netconf_ctx->getCfgServersMap()->at("dhcp6");
    ASSERT_TRUE(server);

    // There is a DHCP6 control socket.
    CfgControlSocketPtr socket = server->getCfgControlSocket();
    ASSERT_TRUE(socket);

    // Check DHCP6 control socket user context.
    ConstElementPtr ctx6 = socket->getContext();
    ASSERT_TRUE(ctx6);
    ASSERT_EQ(1, ctx6->size());
    ASSERT_TRUE(ctx6->get("version"));
    EXPECT_EQ("1", ctx6->get("version")->str());
}

}  // namespace
