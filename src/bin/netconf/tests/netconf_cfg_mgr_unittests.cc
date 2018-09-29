// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <netconf/netconf_cfg_mgr.h>
#ifdef notyet
#include <netconf/parser_context.h>
#endif
#include <exceptions/exceptions.h>
#include <process/testutils/d_test_stubs.h>
#include <process/d_cfg_mgr.h>
#include <netconf/tests/test_libraries.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::netconf;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;

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
    ASSERT_NO_THROW(cfg_mgr.reset(new NetconfCfgMgr()));

    // Verify that the context can be retrieved and is not null.
    NetconfCfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr->getNetconfCfgContext());
    EXPECT_TRUE(context);

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());
}

// Tests if getContext can be retrieved.
TEST(NetconfCfgMgr, getContext) {
    NetconfCfgMgr cfg_mgr;

    NetconfCfgContextPtr ctx;
    ASSERT_NO_THROW(ctx = cfg_mgr.getNetconfCfgContext());
    ASSERT_TRUE(ctx);
}

// Tests if copied context retains all parameters.
TEST(NetconfCfgMgr, contextCopy) {

    NetconfCfgContext ctx;

    HooksConfig& libs = ctx.getHooksConfig();
    string exp_name("testlib1.so");
    ConstElementPtr exp_param(new StringElement("myparam"));
    libs.add(exp_name, exp_param);

    // Make a copy.
    DCfgContextBasePtr copy_base(ctx.clone());
    NetconfCfgContextPtr copy = boost::dynamic_pointer_cast<NetconfCfgContext>(copy_base);
    ASSERT_TRUE(copy);

    // Check hook libs
    const HookLibsCollection& libs2 = copy->getHooksConfig().get();
    ASSERT_EQ(1, libs2.size());
    EXPECT_EQ(exp_name, libs2[0].first);
    ASSERT_TRUE(libs2[0].second);
    EXPECT_EQ(exp_param->str(), libs2[0].second->str());
}


// Tests if the context can store and retrieve hook libs information.
TEST(NetconfCfgMgr, contextHookParams) {
    NetconfCfgContext ctx;

    // By default there should be no hooks.
    HooksConfig& libs = ctx.getHooksConfig();
    EXPECT_TRUE(libs.get().empty());

    libs.add("libone.so", ConstElementPtr());
    libs.add("libtwo.so", Element::fromJSON("{\"foo\": true}"));
    libs.add("libthree.so", Element::fromJSON("{\"bar\": 42}"));

    const HooksConfig& stored_libs = ctx.getHooksConfig();
    EXPECT_EQ(3, stored_libs.get().size());

    // @todo add a == operator to HooksConfig
    EXPECT_EQ(libs.get(), stored_libs.get());
}

#ifdef notyet
/// Netconf configurations used in tests.
const char* NETCONF_CONFIGS[] = {

    // configuration 0: empty (nothing specified)
    "{ }",

    // Configuration 1: http parameters only (no control sockets, not hooks)
    "{  \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001\n"
    "}",

    // Configuration 2: http and 1 socket
    "{\n"
    "    \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001,\n"
    "    \"control-sockets\": {\n"
    "        \"dhcp4\": {\n"
    "            \"socket-name\": \"/tmp/socket-v4\"\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 3: http and all 3 sockets
    "{\n"
    "    \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001,\n"
    "    \"control-sockets\": {\n"
    "        \"dhcp4\": {\n"
    "            \"socket-name\": \"/tmp/socket-v4\"\n"
    "        },\n"
    "        \"dhcp6\": {\n"
    "            \"socket-name\": \"/tmp/socket-v6\"\n"
    "        },\n"
    "        \"d2\": {\n"
    "            \"socket-name\": \"/tmp/socket-d2\"\n"
    "        }\n"
    "   }\n"
    "}",

    // Configuration 4: http, 1 socket and hooks
    // CA is able to load hook libraries that augment its operation.
    // The primary functionality is the ability to add new commands.
    "{\n"
    "    \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001,\n"
    "    \"control-sockets\": {\n"
    "        \"dhcp4\": {\n"
    "            \"socket-name\": \"/tmp/socket-v4\"\n"
    "        }\n"
    "   },\n"
    "    \"hooks-libraries\": ["
    "        {"
    "          \"library\": \"%LIBRARY%\","
    "              \"parameters\": {\n"
    "              \"param1\": \"foo\"\n"
    "            }\n"
    "        }\n"
    "     ]\n"
    "}",

    // Configuration 5: http and 1 socket (d2 only)
    "{\n"
    "    \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001,\n"
    "    \"control-sockets\": {\n"
    "        \"d2\": {\n"
    "            \"socket-name\": \"/tmp/socket-d2\"\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 6: http and 1 socket (dhcp6 only)
    "{\n"
    "    \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001,\n"
    "    \"control-sockets\": {\n"
    "        \"dhcp6\": {\n"
    "            \"socket-name\": \"/tmp/socket-v6\"\n"
    "        }\n"
    "    }\n"
    "}",

    // Configuration 7: http and 2 sockets with user contexts and comments
    "{\n"
    "    \"user-context\": { \"comment\": \"Indirect comment\" },\n"
    "    \"http-host\": \"betelgeuse\",\n"
    "    \"http-port\": 8001,\n"
    "    \"control-sockets\": {\n"
    "        \"dhcp4\": {\n"
    "            \"comment\": \"dhcp4 socket\",\n"
    "            \"socket-name\": \"/tmp/socket-v4\"\n"
    "        },\n"
    "        \"dhcp6\": {\n"
    "            \"socket-name\": \"/tmp/socket-v6\",\n"
    "            \"user-context\": { \"version\": 1 }\n"
    "        }\n"
    "   }\n"
    "}"
};

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
// Sadly, our bison parser requires at last one parameter to be present.
// Until we determine whether we want the empty config to be allowed or not,
// this test remains disabled.
TEST_F(NetconfParserTest, DISABLED_configParseEmpty) {
    configParse(NETCONF_CONFIGS[0], 0);
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
    NetconfCfgContextPtr ctx = cfg_mgr_.getNetconfCfgContext();
    const HookLibsCollection libs = ctx->getHooksConfig().get();
    ASSERT_EQ(1, libs.size());
    EXPECT_EQ(string(BASIC_CALLOUT_LIBRARY), libs[0].first);
    ASSERT_TRUE(libs[0].second);
    EXPECT_EQ("{ \"param1\": \"foo\" }", libs[0].second->str());
}

// This test checks comments.
TEST_F(NetconfParserTest, comments) {
    configParse(NETCONF_CONFIGS[7], 0);
    NetconfCfgContextPtr netconf_ctx = cfg_mgr_.getNetconfCfgContext();
    ASSERT_TRUE(netconf_ctx);

    // Check global user context.
    ConstElementPtr ctx = netconf_ctx->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(1, ctx->size());
    ASSERT_TRUE(ctx->get("comment"));
    EXPECT_EQ("\"Indirect comment\"", ctx->get("comment")->str());

    // There is a DHCP4 control socket.
    ConstElementPtr socket4 = netconf_ctx->getControlSocketInfo("dhcp4");
    ASSERT_TRUE(socket4);

    // Check DHCP4 control socket user context.
    ConstElementPtr ctx4 = socket4->get("user-context");
    ASSERT_TRUE(ctx4);
    ASSERT_EQ(1, ctx4->size());
    ASSERT_TRUE(ctx4->get("comment"));
    EXPECT_EQ("\"dhcp4 socket\"", ctx4->get("comment")->str());

    // There is a DHCP6 control socket.
    ConstElementPtr socket6 = netconf_ctx->getControlSocketInfo("dhcp6");
    ASSERT_TRUE(socket6);

    // Check DHCP6 control socket user context.
    ConstElementPtr ctx6 = socket6->get("user-context");
    ASSERT_TRUE(ctx6);
    ASSERT_EQ(1, ctx6->size());
    ASSERT_TRUE(ctx6->get("version"));
    EXPECT_EQ("1", ctx6->get("version")->str());
}
#endif

}; // end of anonymous namespace
