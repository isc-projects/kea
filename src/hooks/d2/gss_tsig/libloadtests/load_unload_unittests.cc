// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the high availability hook library. In order to test
/// the load function, one must be able to pass it hook library
/// parameters. The the only way to populate these parameters is by
/// actually loading the library via HooksManager::loadLibraries().

#include <config.h>

#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <d2srv/d2_cfg_mgr.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <process/daemon.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::process;

namespace {

/// @brief Structure that holds registered hook indexes.
struct TestHooks {
    /// @brief Index of d2_srv_configured callout.
    int hook_index_d2_srv_configured_;

    /// @brief Constructor
    ///
    /// The constructor registers hook points for callout tests.
    TestHooks() {
        hook_index_d2_srv_configured_ =
            HooksManager::registerHook("d2_srv_configured");
    }
};

TestHooks testHooks;

/// @brief Test fixture for testing loading and unloading the GSS-TSIG library.
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor.
    LibLoadTest() {
        reset();
    }

    /// @brief Destructor.
    /// Removes files that may be left over from previous tests.
    virtual ~LibLoadTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests.
    virtual void reset() {
        HooksManager::unloadLibraries();
    }

    /// @brief Adds library/parameters to list of libraries to be loaded.
    void addLib(const std::string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Load all specified libraries.
    ///
    /// The libraries are stored in libraries_
    bool loadLibs() {
        return (HooksManager::loadLibraries(libraries_));
    }

    /// @brief Unloads all libraries.
    void unloadLibs() {
        EXPECT_NO_THROW(HooksManager::unloadLibraries());
    }

    /// @brief Return basic, valid GSS-TSIG configuration in JSON format.
    ElementPtr createValidJsonConfiguration() const {
        std::string config_text = "{ }";
        return (Element::fromJSON(config_text));
    }

    /// @brief Libraries.
    HookLibsCollection libraries_;
};

// Simple test that checks the library can be loaded in a D2 server.
TEST_F(LibLoadTest, validLoad) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with valid configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, createValidJsonConfiguration());

    // Library should load without issue.
    EXPECT_TRUE(loadLibs());
}

// Simple test that checks the library can be loaded and unloaded several times
// in a D2 server.
TEST_F(LibLoadTest, validLoads) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with valid configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, createValidJsonConfiguration());

    EXPECT_TRUE(loadLibs());
    unloadLibs();

    EXPECT_TRUE(loadLibs());
    unloadLibs();
}

// Verifies that an unknown parameter in an otherwise valid configuration
// is detected.
TEST_F(LibLoadTest, unknownParameterLoad) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    /// Add unknown element "foo" to valid config.
    ElementPtr config = createValidJsonConfiguration();
    config->set("foo", Element::create("bar"));

    // Add library with invalid configuration
    addLib(LIBDHCP_GSS_TSIG_SO, config);

    // The load should fail.
    EXPECT_FALSE(loadLibs());
}

// Verifies that a bad type parameter in an otherwise valid configuration
// is detected.
TEST_F(LibLoadTest, badTypeParameterLoad) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    /// Add servers with bad type to valid config.
    ElementPtr config = createValidJsonConfiguration();
    config->set("servers", Element::createMap());

    // Add library with invalid configuration
    addLib(LIBDHCP_GSS_TSIG_SO, config);

    // The load should fail.
    EXPECT_FALSE(loadLibs());
}

// Verifies that a bad parameter in an otherwise valid configuration
// is detected.
TEST_F(LibLoadTest, badParameterLoad) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    /// Add tkey-protocol with bad value to valid config.
    ElementPtr config = createValidJsonConfiguration();
    config->set("tkey-protocol", Element::create("FOO"));

    // Add library with invalid configuration
    addLib(LIBDHCP_GSS_TSIG_SO, config);

    // The load should fail.
    EXPECT_FALSE(loadLibs());
}

// Verifies that invalid d2_srv_configured callout d2_config parameter fail.
TEST_F(LibLoadTest, badD2ConfigCallout) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with valid configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, createValidJsonConfiguration());

    // Load the library.
    ASSERT_TRUE(loadLibs());

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_d2_srv_configured_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    D2CfgContextPtr d2_config;
    handle->setArgument("server_config", d2_config);

    // Execute the callout (the exception is not propagated).
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_d2_srv_configured_,
                                               *handle));

    // Expect an exception logged with error message:
    // gss_tsig d2_srv_configured: server_config is null
}

// Verifies that valid and empty config works with d2_srv_configured callout.
TEST_F(LibLoadTest, emptyCallout) {
    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with valid configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, createValidJsonConfiguration());

    // Load the library.
    ASSERT_TRUE(loadLibs());

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_d2_srv_configured_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    D2CfgContextPtr d2_config(new D2CfgContext());
    handle->setArgument("server_config", d2_config);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_d2_srv_configured_,
                                               *handle));

    // The configuration was accepted.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
}

// Verifies that mismatch between hook config and empty d2 config
// is detected.
TEST_F(LibLoadTest, badEmptyCallout) {
    // Create a hook config.
    string config = "{\n"
        "\"server-principal\": \"DNS/server.example.org@REALM\",\n"
        "\"servers\": [ {\n"
        "  \"id\": \"foo\",\n"
        "  \"ip-address\": \"192.0.2.1\"\n"
        " } ] }\n";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, json);

    // Load the library.
    ASSERT_TRUE(loadLibs());

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_d2_srv_configured_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    D2CfgContextPtr d2_config(new D2CfgContext());
    handle->setArgument("server_config", d2_config);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_d2_srv_configured_,
                                               *handle));

    // The configuration was rejected.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle->getStatus());
    string expected = "gss_tsig config mismatch: server info can't be found";
    string error;
    handle->getArgument("error", error);
    EXPECT_EQ(expected, error);
}

// Verifies that mismatch between hook config and d2 config
// is detected.
TEST_F(LibLoadTest, badCallout) {
    // D2 config with not matching server.
    string d2_config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\"\n"
        "   } ] } ] } }\n";
    ConstElementPtr d2_json;
    ASSERT_NO_THROW(d2_json = Element::fromJSON(d2_config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(d2_json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr d2_ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(d2_ctx);

    // Create a hook config.
    string config = "{\n"
        "\"server-principal\": \"DNS/server.example.org@REALM\",\n"
        "\"servers\": [ {\n"
        "  \"id\": \"foo\",\n"
        "  \"ip-address\": \"192.0.2.1\"\n"
        " } ] }\n";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, json);

    // Load the library.
    ASSERT_TRUE(loadLibs());

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_d2_srv_configured_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setArgument("server_config", d2_ctx);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_d2_srv_configured_,
                                               *handle));

    // The configuration was rejected.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle->getStatus());
    string expected = "gss_tsig config mismatch: server info can't be found";
    string error;
    handle->getArgument("error", error);
    EXPECT_EQ(expected, error);
}

// Verifies that hook config and d2 config work.
TEST_F(LibLoadTest, callout) {
    // D2 config with matching server.
    string d2_config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.0.2.1\"\n"
        "   } ] } ] } }\n";
    ConstElementPtr d2_json;
    ASSERT_NO_THROW(d2_json = Element::fromJSON(d2_config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(d2_json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr d2_ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(d2_ctx);

    // Create a hook config.
    string config = "{\n"
        "\"server-principal\": \"DNS/server.example.org@REALM\",\n"
        "\"servers\": [ {\n"
        "  \"id\": \"foo\",\n"
        "  \"ip-address\": \"192.0.2.1\"\n"
        " } ] }\n";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    // Set proc name.
    Daemon::setProcName("kea-dhcp-ddns");

    // Add library with configuration.
    addLib(LIBDHCP_GSS_TSIG_SO, json);

    // Load the library.
    ASSERT_TRUE(loadLibs());

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_d2_srv_configured_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setArgument("server_config", d2_ctx);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_d2_srv_configured_,
                                               *handle));

    // The configuration was accepted.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
}

} // end of anonymous namespace
