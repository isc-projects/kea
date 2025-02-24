// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// The load and unload callouts are exercised in ../libloadtests, which
/// actually uses the HooksManager to load and unload the library.

#include <config.h>

#include <asiolink/io_service.h>
#include <d2srv/d2_config.h>
#include <gss_tsig_api_utils.h>
#include <gss_tsig_impl.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <testutils/gss_tsig_dns_server.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::d2;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::hooks;
using namespace std;

extern "C" {
extern int select_key(CalloutHandle& handle);
}

namespace isc {
namespace gss_tsig {
extern GssTsigImplPtr impl;
}
}

namespace {

const long TEST_TIMEOUT = 5 * 100; // expressed in milliseconds.

/// @brief Test fixture for exercising flex-id library callouts
/// It fetches the CalloutManager and prepares stub packets that can be used in
/// tests.
class CalloutTest : public GssApiBaseTest {
public:
    /// @brief Constructor.
    CalloutTest() : io_service_(new IOService()), test_timer_(io_service_),
            co_manager_(new CalloutManager(1)), cfg_mgr_(new D2CfgMgr()) {
        impl.reset(new GssTsigImpl());
        string config = "{\n"
            "\"ip-address\": \"127.0.0.1\",\n"
            "\"port\": 53001,\n"
            "\"dns-server-timeout\" : 1000,\n"
            "\"forward-ddns\": {\n"
            " \"ddns-domains\": [\n"
            "  {\n"
            "   \"name\": \"secure.example.org.\",\n"
            "   \"dns-servers\": [\n"
            "    {\n"
            "     \"ip-address\": \"127.0.0.1\",\n"
            "     \"port\": 5376\n"
            "    }\n"
            "   ]\n"
            "  }\n"
            " ]\n"
            "},\n"
            "\"reverse-ddns\": {\n"
            " \"ddns-domains\": [\n"
            "  {\n"
            "   \"name\": \"0.0.127.in-addr.arpa.\",\n"
            "   \"dns-servers\": [\n"
            "    {\n"
            "     \"ip-address\": \"127.0.0.1\",\n"
            "     \"port\": 5376\n"
            "    }\n"
            "   ]\n"
            "  }\n"
            " ]\n"
            "}\n"
            "}\n";
        ConstElementPtr config_set = Element::fromJSON(config);
        cfg_mgr_->simpleParseConfig(config_set);
        string hook_config = "{\n"
            "\"server-principal\": \"DNS/blu.example.nil@EXAMPLE.NIL\",\n"
            "\"client-principal\": \"administrator@EXAMPLE.NIL\",\n"
            "\"tkey-lifetime\": 7200,\n"
            "\"tkey-protocol\": \"UDP\",\n"
            "\"servers\": [\n"
            " {\n"
            "  \"domain-names\": [ ],\n"
            "  \"id\": \"foo\",\n"
            "  \"ip-address\": \"127.0.0.1\",\n"
            "  \"port\": 5376,\n"
            "  \"tkey-lifetime\": 86400,\n"
            "  \"tkey-protocol\": \"UDP\"\n"
            " }\n"
            "]\n"
            "}\n";
        setKeytab();
        setAdministratorCCache();
        ConstElementPtr hook_config_set = Element::fromJSON(hook_config);
        impl->configure(hook_config_set);
        D2CfgContextPtr d2_config(cfg_mgr_->getD2CfgContext());
        impl->setIOService(io_service_);
        impl->finishConfigure(d2_config);
        EXPECT_NO_THROW(legacy_key_.reset(new TSIGKeyInfo("test_key",
                                                          TSIGKeyInfo::HMAC_MD5_STR,
                                                          "GWG/Xfbju4O2iXGqkSu4PQ==")));
        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(std::bind(&CalloutTest::testTimeoutHandler, this),
                          TEST_TIMEOUT);
        impl->start();
    }

    /// @brief Destructor.
    ~CalloutTest() {
        impl.reset();
        test_timer_.cancel();
        io_service_->stopAndPoll();
    }

    /// @brief Fetches the callout manager instance.
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

    /// @brief Handler invoked when test timeout is hit
    ///
    /// This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        io_service_->stop();
    }

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The timeout timer.
    asiolink::IntervalTimer test_timer_;

    /// @brief Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;

    /// @brief Config manager used to store DNS servers.
    boost::shared_ptr<D2CfgMgr> cfg_mgr_;

    /// @brief The TSIG Key (non GSS-TSIG key).
    TSIGKeyInfoPtr legacy_key_;

    /// @brief Dummy DNS server.
    boost::shared_ptr<DummyDNSServer> dns_server_;
};

TEST_F(CalloutTest, select_keyNoServerArgument) {
    CalloutHandle handle(getCalloutManager());
    ASSERT_THROW_MSG(select_key(handle), NoSuchArgument,
                     "unable to find argument with name current_server");
}

TEST_F(CalloutTest, select_keyNoTSIGKeyArgument) {
    CalloutHandle handle(getCalloutManager());
    handle.setArgument("current_server", DnsServerInfoPtr());
    ASSERT_THROW_MSG(select_key(handle), NoSuchArgument,
                     "unable to find argument with name tsig_key");
}

TEST_F(CalloutTest, select_keyNoGSSWithNoFallback) {
    CalloutHandle handle(getCalloutManager());
    DnsServerPtr server = impl->getServer("foo");
    ASSERT_TRUE(server);
    ASSERT_TRUE(server->getServerInfos().size());
    DnsServerInfoPtr info = server->getServerInfos()[0];
    handle.setArgument("current_server", info);
    handle.setArgument("tsig_key", legacy_key_->getTSIGKey());
    int ret = select_key(handle);
    ASSERT_EQ(ret, 0);
    // If no GSS-TSIG TKEY is available, the non GSS-TSIG key is not used and
    // the server is skipped by updating the callout status.
    ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_SKIP);
    D2TsigKeyPtr key;
    handle.getArgument("tsig_key", key);
    ASSERT_EQ(key, legacy_key_->getTSIGKey());
}

TEST_F(CalloutTest, select_keyNoGSSWithFallback) {
    CalloutHandle handle(getCalloutManager());
    DnsServerPtr server = impl->getServer("foo");
    ASSERT_TRUE(server);
    ASSERT_TRUE(server->getServerInfos().size());
    server->setFallback(true);
    DnsServerInfoPtr info = server->getServerInfos()[0];
    handle.setArgument("current_server", info);
    handle.setArgument("tsig_key", legacy_key_->getTSIGKey());
    int ret = select_key(handle);
    ASSERT_EQ(ret, 0);
    // If no GSS-TSIG TKEY is available, the non GSS-TSIG key is used.
    ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    D2TsigKeyPtr key;
    handle.getArgument("tsig_key", key);
    ASSERT_EQ(key, legacy_key_->getTSIGKey());
}

TEST_F(CalloutTest, select_keyGSSWithNoFallback) {
    CalloutHandle handle(getCalloutManager());
    dns_server_.reset(new DummyDNSServer(io_service_, true, true, false, true, false));
    dns_server_->start();
    io_service_->run();
    DnsServerPtr server = impl->getServer("foo");
    ASSERT_TRUE(server);
    ASSERT_TRUE(server->getServerInfos().size());
    DnsServerInfoPtr info = server->getServerInfos()[0];
    handle.setArgument("current_server", info);
    handle.setArgument("tsig_key", legacy_key_->getTSIGKey());
    int ret = select_key(handle);
    ASSERT_EQ(ret, 0);
    // If GSS-TSIG TKEY is available it is used instead on the non GSS-TSIG key.
    ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    D2TsigKeyPtr key;
    handle.getArgument("tsig_key", key);
    ASSERT_TRUE(key);
    ASSERT_NE(key, legacy_key_->getTSIGKey());
    ManagedKeyPtr mkey = boost::dynamic_pointer_cast<ManagedKey>(key);
    ASSERT_TRUE(mkey);
}

TEST_F(CalloutTest, select_keyGSSWithFallback) {
    CalloutHandle handle(getCalloutManager());
    dns_server_.reset(new DummyDNSServer(io_service_, true, true, false, true, false));
    dns_server_->start();
    io_service_->run();
    DnsServerPtr server = impl->getServer("foo");
    ASSERT_TRUE(server);
    ASSERT_TRUE(server->getServerInfos().size());
    server->setFallback(true);
    DnsServerInfoPtr info = server->getServerInfos()[0];
    handle.setArgument("current_server", info);
    handle.setArgument("tsig_key", legacy_key_->getTSIGKey());
    int ret = select_key(handle);
    ASSERT_EQ(ret, 0);
    // If GSS-TSIG TKEY is available it is used instead on the non GSS-TSIG key.
    ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    D2TsigKeyPtr key;
    handle.getArgument("tsig_key", key);
    ASSERT_TRUE(key);
    ASSERT_NE(key, legacy_key_->getTSIGKey());
    ManagedKeyPtr mkey = boost::dynamic_pointer_cast<ManagedKey>(key);
    ASSERT_TRUE(mkey);
}

}
