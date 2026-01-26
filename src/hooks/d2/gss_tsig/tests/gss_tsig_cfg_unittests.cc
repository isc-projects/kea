// Copyright (C) 2021-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gss_tsig_cfg.h>
#include <cc/command_interpreter.h>
#include <managed_key.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <stats/stats_mgr.h>
#include <stats/testutils/stats_test_utils.h>
#include <gtest/gtest.h>
#include <limits>

using namespace std;
using namespace isc;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::gss_tsig;
using namespace isc::stats;
using namespace isc::stats::test;
using namespace isc::test;

namespace {

/// @brief Test structure used to verify configuration parser.
///
/// If any of the int32_t values is -1, the default value is expected.
struct ConfigSet {
    /// @brief The global tkey-lifetime value.
    int32_t global_tkey_lifetime_;
    /// @brief The server tkey-lifetime value.
    int32_t server_tkey_lifetime_;
    /// @brief The global rekey-interval value.
    int32_t global_rekey_;
    /// @brief The server rekey-interval value.
    int32_t server_rekey_;
    /// @brief The global retry-interval value.
    int32_t global_retry_;
    /// @brief The server renew-interval value.
    int32_t server_retry_;
    /// @brief The flag which indicates is a server should be added to the
    /// configuration.
    bool add_server_;
    /// @brief The flag which indicates if the parser is expected to throw
    /// because of incompatible values.
    bool expect_throw_;
    /// @brief The exception message to check if an error is detected.
    string expected_message_;
};

/// @brief Function which checks if the configured values are accepted.
/// The ConfigSet.add_server_ indicates if a server configuration should be
/// added even if there is no parameter explicitly configured for the server
/// (using the default values). If any of ConfigSet.global_tkey_lifetime_,
/// ConfigSet.server_tkey_lifetime_, ConfigSet.global_rekey_,
/// ConfigSet.server_rekey_, ConfigSet.global_retry_, ConfigSet.server_retry_
/// is -1, then the respective parameter is omitted and the default values are
/// expected. The ConfigSet.expect_throw_ indicates if the parser is expected to
/// throw exception for the respective configuration. If an exception is thrown,
/// the ConfigSet.expected_message_ is verified to match exception message.
/// Tested dependency between parameters:
///    tkey-lifetime > rekey-interval > retry-interval
///
/// x = explicitly set
/// 0 = using default
/// - = does not matter (using default)
///
/// Dependency between tkey-lifetime and rekey-interval:
///
/// 0000-- <- relevant for rekey-interval > retry-interval also
/// x000--
/// 0x00--
/// xx00--
///
/// 00x0-- <- relevant for rekey-interval > retry-interval also
/// x0x0--
/// 0xx0--
/// xxx0-- <- twice (server rekey-interval vs global and server tkey-lifetime)
///
/// 000x-- <- relevant for rekey-interval > retry-interval also
/// x00x--
/// 0x0x--
/// xx0x--
///
/// 00xx-- <- relevant for rekey-interval > retry-interval also
/// 10xx--
/// 0xxx--
/// xxxx--
///
/// Dependency between rekey-interval and retry-interval
///
/// --0000 <- already checked before
/// --x000 <- already checked before
/// --0x00 <- already checked before
/// --xx00 <- already checked before
///
/// --00x0
/// --x0x0
/// --0xx0
/// --xxx0 <- twice (server retry-interval vs global and server rekey-interval)
///
/// --000x
/// --x00x
/// --0x0x
/// --xx0x
///
/// --00xx
/// --x0xx
/// --0xxx
/// --xxxx
///
/// Total 16 + 12 + 2 = 30 cases.
void checkConfig(const ConfigSet& config_set) {
    stringstream ss;
    ss << "{ \"gss-replay-flag\": true";
    ss << ", \"gss-sequence-flag\": false";
    ss << ", \"fallback\": false";
    if (config_set.global_tkey_lifetime_ != -1) {
        ss << ", \"tkey-lifetime\": " << config_set.global_tkey_lifetime_;
    }
    if (config_set.global_rekey_ != -1) {
        ss << ", \"rekey-interval\": " << config_set.global_rekey_;
    }
    if (config_set.global_retry_ != -1) {
        ss << ", \"retry-interval\": " << config_set.global_retry_;
    }
    if (config_set.add_server_ || (config_set.server_tkey_lifetime_ != -1) ||
        (config_set.server_rekey_ != -1) || (config_set.server_retry_ != -1)) {
        ss << ", \"servers\": [ { \"id\": \"foo\", ";
        ss << "\"ip-address\": \"2001:db8::1\", ";
        ss << "\"server-principal\": \"DNS/server.example.org@REALM\"";
        if (config_set.server_tkey_lifetime_ != -1) {
            ss << ", \"tkey-lifetime\": " << config_set.server_tkey_lifetime_;
        }
        if (config_set.server_rekey_ != -1) {
            ss << ", \"rekey-interval\": " << config_set.server_rekey_;
        }
        if (config_set.server_retry_ != -1) {
            ss << ", \"retry-interval\": " << config_set.server_retry_;
        }
        ss << " } ]";
    }
    ss << " }";
    string config = ss.str();
    ss << " server: " << config_set.add_server_
       << " throw: " << config_set.expect_throw_
       << " global tkey lifetime: " << config_set.global_tkey_lifetime_
       << " server tkey lifetime: " << config_set.server_tkey_lifetime_
       << " global rekey: " << config_set.global_rekey_
       << " server rekey: " << config_set.server_rekey_
       << " global retry: " << config_set.global_retry_
       << " server retry: " << config_set.server_retry_
       << " message: " << config_set.expected_message_;
    SCOPED_TRACE(ss.str());
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    if (config_set.expect_throw_) {
        EXPECT_THROW_MSG(cfg.configure(json), BadValue,
                         config_set.expected_message_);
    } else {
        EXPECT_NO_THROW(cfg.configure(json));
    }
}

/// @brief Check the DNS server.
TEST(GssTsigCfgTest, dnsServer) {
    // Constructor.
    DnsServerPtr srv;
    string id("bar");
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, { }, addr)));
    ASSERT_TRUE(srv);
    EXPECT_EQ(id, srv->getID());
    EXPECT_EQ(addr, srv->getIpAddress());
    EXPECT_EQ(53, srv->getPort());

    // ID.
    id = "foo";
    ASSERT_NO_THROW(srv->setID(id));
    EXPECT_EQ(id, srv->getID());

    // Server infos.
    EXPECT_TRUE(srv->getServerInfos().empty());
    DnsServerInfoPtr info;
    ASSERT_NO_THROW(info.reset(new DnsServerInfo("", addr)));
    ASSERT_TRUE(info);
    srv->addServerInfo(info);
    ASSERT_EQ(1, srv->getServerInfos().size());
    DnsServerInfoPtr got;
    ASSERT_NO_THROW(got = srv->getServerInfos().at(0));
    EXPECT_EQ(info, got);
    srv->clearServerInfos();
    EXPECT_TRUE(srv->getServerInfos().empty());

    // DNS server principal.
    EXPECT_EQ("", srv->getServerPrincipal());
    srv->setServerPrincipal("DNS/example.nil@EXAMPLE.NIL");
    EXPECT_EQ("DNS/example.nil@EXAMPLE.NIL", srv->getServerPrincipal());

    // GSS-TSIG key suffix.
    EXPECT_EQ("", srv->getKeyNameSuffix());
    srv->setKeyNameSuffix("foo-example.nil");
    EXPECT_EQ("foo-example.nil.", srv->getKeyNameSuffix());
    EXPECT_NO_THROW(srv->buildKeyNameSuffix());
    EXPECT_EQ("sig-example.nil.", srv->getKeyNameSuffix());

    // client/credentials principal.
    EXPECT_EQ("", srv->getClientPrincipal());
    srv->setClientPrincipal("DHCP/example.nil@EXAMPLE.NIL");
    EXPECT_EQ("DHCP/example.nil@EXAMPLE.NIL", srv->getClientPrincipal());

    // GSS (anti) replay flag.
    EXPECT_TRUE(srv->getGssReplayFlag());
    srv->setGssReplayFlag(false);
    EXPECT_FALSE(srv->getGssReplayFlag());

    // GSS sequence flag.
    EXPECT_FALSE(srv->getGssSequenceFlag());
    srv->setGssSequenceFlag(true);
    EXPECT_TRUE(srv->getGssSequenceFlag());

    // TKEY lifetime.
    EXPECT_EQ(3600, srv->getKeyLifetime());
    srv->setKeyLifetime(7200);
    EXPECT_EQ(7200, srv->getKeyLifetime());

    // Rekey interval.
    EXPECT_EQ(2700, srv->getRekeyInterval());
    srv->setRekeyInterval(5400);
    EXPECT_EQ(5400, srv->getRekeyInterval());

    // Retry interval.
    EXPECT_EQ(120, srv->getRetryInterval());
    srv->setRetryInterval(240);
    EXPECT_EQ(240, srv->getRetryInterval());

    // TKEY protocol.
    EXPECT_EQ(IOFetch::TCP, srv->getKeyProto());
    srv->setKeyProto(IOFetch::UDP);
    EXPECT_EQ(IOFetch::UDP, srv->getKeyProto());

    // Fallback.
    EXPECT_FALSE(srv->getFallback());
    srv->setFallback(true);
    EXPECT_TRUE(srv->getFallback());

    // Port.
    DnsServerPtr srv2(new DnsServer(id, { }, addr, 1234));
    ASSERT_TRUE(srv2);
    EXPECT_EQ(addr, srv2->getIpAddress());
    EXPECT_EQ(1234, srv2->getPort());

    // TKEY exchange timeout.
    EXPECT_EQ(3000, srv->getExchangeTimeout());
    srv->setExchangeTimeout(5000);
    EXPECT_EQ(5000, srv->getExchangeTimeout());

    // User context.
    ConstElementPtr user_ctx = srv->getContext();
    EXPECT_FALSE(user_ctx);
    string user_ctx_str = "{ \"foo\": 123 }";
    srv->setContext(Element::fromJSON(user_ctx_str));
    user_ctx = srv->getContext();
    ASSERT_TRUE(user_ctx);
    EXPECT_EQ(user_ctx_str, user_ctx->str());

    // toElement.
    ElementPtr expected = Element::createMap();
    expected->set("id",  Element::create(id));
    expected->set("user-context", user_ctx);
    expected->set("ip-address", Element::create(string("192.1.2.3")));
    expected->set("port", Element::create(53));
    expected->set("server-principal",
                  Element::create(string("DNS/example.nil@EXAMPLE.NIL")));
    expected->set("key-name-suffix",
                  Element::create(string("sig-example.nil.")));
    expected->set("client-principal",
                  Element::create(string("DHCP/example.nil@EXAMPLE.NIL")));
    expected->set("gss-replay-flag", Element::create(false));
    expected->set("gss-sequence-flag", Element::create(true));
    expected->set("tkey-lifetime", Element::create(7200));
    expected->set("rekey-interval", Element::create(5400));
    expected->set("retry-interval", Element::create(240));
    expected->set("tkey-protocol", Element::create(string("UDP")));
    expected->set("fallback", Element::create(true));
    expected->set("exchange-timeout", Element::create(5000));
    runToElementTest<DnsServer>(expected, *srv);

    // Stats.
    id = "foobar";
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, { }, addr)));
    checkStat(StatsMgr::generateName("server", id, "tkey-sent"), 0);
    checkStat(StatsMgr::generateName("server", id, "tkey-success"), 0);
    checkStat(StatsMgr::generateName("server", id, "tkey-timeout"), 0);
    checkStat(StatsMgr::generateName("server", id, "tkey-error"), 0);
    srv.reset();
    checkNoStat(StatsMgr::generateName("server", id, "tkey-sent"));
    checkNoStat(StatsMgr::generateName("server", id, "tkey-success"));
    checkNoStat(StatsMgr::generateName("server", id, "tkey-timeout"));
    checkNoStat(StatsMgr::generateName("server", id, "tkey-error"));
}

/// @build Check buildServerInfo with any domain.
TEST(GssTsigCfgTest, buildServerInfo) {
    // DnsServer
    DnsServerPtr srv;
    const string& id("foo");
    set<string> domains;
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
    ASSERT_TRUE(srv);

    // D2 config with two matching servers.
    string config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] },\n"
        "\"reverse-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"2.0.192.in-addr.arpa.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] } }\n";

    // Parse the D2 config.
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(ctx);

    // Check the buildServerInfo method.
    EXPECT_THROW_MSG(srv->buildServerInfo(D2CfgContextPtr()), D2CfgError,
                     "empty D2 config");
    ASSERT_NO_THROW(srv->buildServerInfo(ctx));
    const DnsServerInfoStorage& infos = srv->getServerInfos();
    ASSERT_EQ(2, infos.size());
    DnsServerInfoPtr info1;
    ASSERT_NO_THROW(info1 = infos.at(0));
    ASSERT_TRUE(info1);
    EXPECT_EQ(addr, info1->getIpAddress());
    EXPECT_EQ(53, info1->getPort());
    DnsServerInfoPtr info2;
    ASSERT_NO_THROW(info2 = infos.at(1));
    ASSERT_TRUE(info2);
    EXPECT_EQ(addr, info2->getIpAddress());
    EXPECT_EQ(53, info2->getPort());
    EXPECT_NE(info1, info2);

    // buildServerInfo can be called only once.
    EXPECT_THROW_MSG(srv->buildServerInfo(ctx), D2CfgError,
                     "server info list is not empty");
}

/// @build Check buildServerInfo with two configured domains.
TEST(GssTsigCfgTest, buildServerInfoTwo) {
    // DnsServer
    DnsServerPtr srv;
    const string& id("foo");
    set<string> domains = { "foo.example.com.", "2.0.192.in-addr.arpa." };
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
    ASSERT_TRUE(srv);

    // D2 config with two matching servers.
    string config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] },\n"
        "\"reverse-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"2.0.192.in-addr.arpa.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] } }\n";

    // Parse the D2 config.
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(ctx);

    // Check the buildServerInfo method.
    ASSERT_NO_THROW(srv->buildServerInfo(ctx));
    const DnsServerInfoStorage& infos = srv->getServerInfos();
    ASSERT_EQ(2, infos.size());
    DnsServerInfoPtr info1;
    ASSERT_NO_THROW(info1 = infos.at(0));
    ASSERT_TRUE(info1);
    EXPECT_EQ(addr, info1->getIpAddress());
    EXPECT_EQ(53, info1->getPort());
    DnsServerInfoPtr info2;
    ASSERT_NO_THROW(info2 = infos.at(1));
    ASSERT_TRUE(info2);
    EXPECT_EQ(addr, info2->getIpAddress());
    EXPECT_EQ(53, info2->getPort());
    EXPECT_NE(info1, info2);
}

/// @build Check buildServerInfo with one configured domain.
TEST(GssTsigCfgTest, buildServerInfoOneDomain) {
    // DnsServer
    DnsServerPtr srv;
    const string& id("foo");
    set<string> domains = { "foo.example.com." };
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
    ASSERT_TRUE(srv);

    // D2 config with two matching servers.
    string config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] },\n"
        "\"reverse-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"2.0.192.in-addr.arpa.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] } }\n";

    // Parse the D2 config.
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(ctx);

    // Check the buildServerInfo method.
    ASSERT_NO_THROW(srv->buildServerInfo(ctx));
    const DnsServerInfoStorage& infos = srv->getServerInfos();
    ASSERT_EQ(1, infos.size());
    DnsServerInfoPtr info;
    ASSERT_NO_THROW(info = infos.at(0));
    ASSERT_TRUE(info);
    EXPECT_EQ(addr, info->getIpAddress());
    EXPECT_EQ(53, info->getPort());
}

/// @build Check buildServerInfo with no server.
TEST(GssTsigCfgTest, buildServerInfoNoServer) {
    // DnsServer
    DnsServerPtr srv;
    const string& id("foo");
    set<string> domains;
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
    ASSERT_TRUE(srv);

    // D2 config with one not matching server.
    string config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.4\" } ] } ] } }\n";

    // Parse the D2 config.
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(ctx);
    EXPECT_THROW_MSG(srv->buildServerInfo(ctx), NotFound,
                     "server info can't be found");
}

/// @build Check buildServerInfo with no domain.
TEST(GssTsigCfgTest, buildServerInfoNoDomain) {
    // DnsServer
    DnsServerPtr srv;
    const string& id("foo");
    set<string> domains = { "foo.example.com.", "bar.example.com." };
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
    ASSERT_TRUE(srv);

    // D2 config with two matching servers.
    string config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] },\n"
        "\"reverse-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"2.0.192.in-addr.arpa.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] } }\n";

    // Parse the D2 config.
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(ctx);
    EXPECT_THROW_MSG(srv->buildServerInfo(ctx), NotFound,
                     "domain 'bar.example.com.' can't be found");
}

/// @brief Check the config.
TEST(GssTsigCfgTest, config) {
    // Constructor.
    GssTsigCfg cfg;
    EXPECT_TRUE(cfg.getServerList().empty());
    EXPECT_TRUE(cfg.getServerRevMap().empty());

    // Get server.
    DnsServerInfoPtr info;
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(info.reset(new DnsServerInfo("", addr)));
    ASSERT_TRUE(info);
    EXPECT_FALSE(cfg.getServer(info));

    // client key table specification.
    EXPECT_EQ("", cfg.getClientKeyTab());
    cfg.setClientKeyTab("FILE:/tmp/mykeytab");
    EXPECT_EQ("FILE:/tmp/mykeytab", cfg.getClientKeyTab());

    // credentials cache specification.
    EXPECT_EQ("", cfg.getCredsCache());
    cfg.setCredsCache("KCM:");
    EXPECT_EQ("KCM:", cfg.getCredsCache());

    // maximum tkey lifetime.
    EXPECT_EQ(0, cfg.getMaxKeyLifetime());
    cfg.setMaxKeyLifetime(12345);
    EXPECT_EQ(12345, cfg.getMaxKeyLifetime());
}

/// @brief Check the DNS server containers.
TEST(GssTsigCfgTest, dnsServers) {
    GssTsigCfg cfg;
    DnsServerPtr srv;
    const string& id("foo");
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, { }, addr)));
    ASSERT_TRUE(srv);

    // Add 2 equivalent infos.
    DnsServerInfoPtr info1;
    ASSERT_NO_THROW(info1.reset(new DnsServerInfo("", addr)));
    ASSERT_TRUE(info1);
    srv->addServerInfo(info1);
    DnsServerInfoPtr info2;
    ASSERT_NO_THROW(info2.reset(new DnsServerInfo("", addr)));
    ASSERT_TRUE(info2);
    srv->addServerInfo(info2);

    // Check the server list.
    cfg.addServer(srv);
    EXPECT_EQ(1, cfg.getServerList().size());
    EXPECT_EQ(srv, cfg.getServerList().front());
    EXPECT_EQ(srv, cfg.getServer(id));
    EXPECT_FALSE(cfg.getServer("bar"));
}

/// @brief Build and check the server map.
TEST(GssTsigCfgTest, buildServerRevMap) {
    // Add a server.
    GssTsigCfg cfg;
    DnsServerPtr srv;
    const string& id("foo");
    IOAddress addr("192.1.2.3");
    ASSERT_NO_THROW(srv.reset(new DnsServer(id, { }, addr)));
    ASSERT_TRUE(srv);
    cfg.addServer(srv);

    // D2 config with two matching servers.
    string d2_config = "{\n"
        "\"forward-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"foo.example.com.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] },\n"
        "\"reverse-ddns\": {\n"
        " \"ddns-domains\": [ {\n"
        "  \"name\": \"2.0.192.in-addr.arpa.\",\n"
        "  \"dns-servers\": [ {\n"
        "   \"ip-address\": \"192.1.2.3\" } ] } ] } }\n";

    // Parse the D2 config.
    ConstElementPtr d2_json;
    ASSERT_NO_THROW(d2_json = Element::fromJSON(d2_config));
    D2CfgMgr mgr;
    ConstElementPtr answer = mgr.simpleParseConfig(d2_json);
    int rcode = -1;
    ConstElementPtr comment = parseAnswer(rcode, answer);
    if (rcode != CONTROL_RESULT_SUCCESS) {
        FAIL() << "d2 config parse failed: " << comment->str();
    }
    D2CfgContextPtr ctx = mgr.getD2CfgContext();
    ASSERT_TRUE(ctx);

    // Build the server reverse map.
    EXPECT_THROW(cfg.buildServerRevMap(D2CfgContextPtr()), D2CfgError);
    ASSERT_NO_THROW(cfg.buildServerRevMap(ctx));
    const DnsServerRevMap& rev_map = cfg.getServerRevMap();
    ASSERT_EQ(2, rev_map.size());
    for (auto const& it : rev_map) {
        DnsServerInfoPtr info = it.first;
        ASSERT_TRUE(info);
        EXPECT_EQ(addr, info->getIpAddress());
        EXPECT_EQ(53, info->getPort());
        EXPECT_EQ(srv, it.second);
    }

    // buildServerRevMap can be called only once.
    EXPECT_THROW_MSG(cfg.buildServerRevMap(ctx), D2CfgError,
                     "server reverse map is not empty");
}

/// @brief Check the configure method.
TEST(GssTsigCfgTest, configure) {
    string config = "{\n"
        "\"server-principal\": \"DNS/server.example.org@REALM\",\n"
        "\"client-principal\": \"DHCP/admin.example.org@REALM\",\n"
        "\"client-keytab\": \"FILE:/etc/krb5.keytab\",\n"
        "\"credentials-cache\": \"FILE:/etc/ccache\",\n"
        "\"gss-replay-flag\": false,\n"
        "\"gss-sequence-flag\": true,\n"
        "\"rekey-interval\": 5400,\n"
        "\"retry-interval\": 240,\n"
        "\"tkey-lifetime\": 7200,\n"
        "\"tkey-protocol\": \"UDP\",\n"
        "\"exchange-timeout\": 2000,\n"
        "\"servers\": [\n"
        " {\n"
        "  \"domain-names\": [ ],\n"
        "  \"id\": \"foo\",\n"
        "  \"ip-address\": \"192.0.2.1\",\n"
        "  \"server-principal\": \"DNS/server1.example.org@REALM\",\n"
        "  \"client-principal\": \"DHCP/admin1.example.org@REALM\",\n"
        "  \"gss-replay-flag\": true,\n"
        "  \"gss-sequence-flag\": false,\n"
        "  \"rekey-interval\": 64800,\n"
        "  \"retry-interval\": 2880,\n"
        "  \"tkey-lifetime\": 86400,\n"
        "  \"tkey-protocol\": \"UDP\",\n"
        "  \"exchange-timeout\": 4000\n"
        " },{\n"
        "  \"id\": \"bar\",\n"
        "  \"ip-address\": \"192.0.2.2\",\n"
        "  \"port\": 5300\n"
        " }\n"
        "]}\n";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    GssTsigCfg cfg;
    ASSERT_NO_THROW(cfg.configure(json));
    EXPECT_EQ("FILE:/etc/krb5.keytab", cfg.getClientKeyTab());
    EXPECT_EQ("FILE:/etc/ccache", cfg.getCredsCache());
    EXPECT_EQ(86400, cfg.getMaxKeyLifetime());
    const DnsServerList& servers = cfg.getServerList();
    ASSERT_EQ(2, servers.size());

    DnsServerPtr server;
    ASSERT_NO_THROW(server = servers.at(0));
    ASSERT_TRUE(server);
    EXPECT_EQ("foo", server->getID());
    EXPECT_EQ("192.0.2.1", server->getIpAddress().toText());
    EXPECT_EQ(53, server->getPort());
    EXPECT_EQ("DNS/server1.example.org@REALM", server->getServerPrincipal());
    EXPECT_EQ("sig-server1.example.org.", server->getKeyNameSuffix());
    EXPECT_EQ("DHCP/admin1.example.org@REALM", server->getClientPrincipal());
    EXPECT_TRUE(server->getGssReplayFlag());
    EXPECT_FALSE(server->getGssSequenceFlag());
    EXPECT_EQ(64800, server->getRekeyInterval());
    EXPECT_EQ(2880, server->getRetryInterval());
    EXPECT_EQ(86400, server->getKeyLifetime());
    EXPECT_EQ(IOFetch::UDP, server->getKeyProto());
    EXPECT_EQ(4000, server->getExchangeTimeout());

    ASSERT_NO_THROW(server = servers.at(1));
    ASSERT_TRUE(server);
    EXPECT_EQ("bar", server->getID());
    EXPECT_EQ("192.0.2.2", server->getIpAddress().toText());
    EXPECT_EQ(5300, server->getPort());
    EXPECT_EQ("DNS/server.example.org@REALM", server->getServerPrincipal());
    EXPECT_EQ("sig-server.example.org.", server->getKeyNameSuffix());
    EXPECT_EQ("DHCP/admin.example.org@REALM", server->getClientPrincipal());
    EXPECT_FALSE(server->getGssReplayFlag());
    EXPECT_TRUE(server->getGssSequenceFlag());
    EXPECT_EQ(5400, server->getRekeyInterval());
    EXPECT_EQ(240, server->getRetryInterval());
    EXPECT_EQ(7200, server->getKeyLifetime());
    EXPECT_EQ(IOFetch::UDP, server->getKeyProto());
    EXPECT_EQ(2000, server->getExchangeTimeout());
}

/// @brief Check configure requires a map.
TEST(GssTsigCfgTest, configureNoMap) {
    ElementPtr json;
    GssTsigCfg cfg;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue,
                     "gss_tsig parameters entry is mandatory");
    json = Element::createList();
    EXPECT_THROW_MSG(cfg.configure(json), BadValue,
                     "gss_tsig parameters entry must be a map");
}

/// @brief Check configure fails on unknown keywords.
TEST(GssTsigCfgTest, configureUnknown) {
    string config = "{ \"dns-servers\": [ ] }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    string expected = "gss_tsig spurious 'dns-servers' parameter (<string>:1:2)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"address\": \"192.1.2.3\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server spurious 'address' parameter (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);
}

/// @brief Check configure fails on parameters without expected types.
TEST(GssTsigCfgTest, configureUnexpectedType) {
    string config = "{ \"server-principal\": 100 }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    string expected = "gss_tsig 'server-principal' parameter is not a string";
    string location = " (<string>:1:2)";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"client-principal\": 200 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'client-principal' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"client-keytab\": 300 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'client-keytab' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"credentials-cache\": 400 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'credentials-cache' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"gss-replay-flag\": 1 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'gss-replay-flag' parameter is not a boolean";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"gss-sequence-flag\": \"off\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'gss-sequence-flag' parameter is not a boolean";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"tkey-lifetime\": \"3600\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'tkey-lifetime' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"rekey-interval\": \"2700\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'rekey-interval' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"retry-interval\": \"120\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'retry-interval' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"tkey-protocol\": 500 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'tkey-protocol' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"exchange-timeout\": false }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'exchange-timeout' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"user-context\": [ ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'user-context' parameter is not a map";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"comment\": true }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'comment' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": { } }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig 'servers' parameter is not a list";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": 123 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'id' parameter is not a string";
    location = " (<string>:1:17)";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"domain-names\": false } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'domain-names' parameter is not a list";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"domain-names\": [ true ] } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'domain-names' list ";
    expected += "must contain only strings (<string>:1:49)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"ip-address\": [ ] } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'ip-address' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"port\": \"53\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'port' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    string prefix = "{ \"servers\": [ { \"ip-address\": \"2001:db8::1\",";
    config = prefix + " \"server-principal\": 100 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'server-principal' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"client-principal\": 200 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'client-principal' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"gss-replay-flag\": \"on\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'gss-replay-flag' parameter is not a boolean";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"gss-sequence-flag\": 0 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'gss-sequence-flag' parameter ";
    expected += "is not a boolean";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"tkey-lifetime\": \"3600\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'tkey-lifetime' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"rekey-interval\": \"2700\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'rekey-interval' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"retry-interval\": \"120\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'retry-interval' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"tkey-protocol\": 500 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'tkey-protocol' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"exchange-timeout\": false } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'exchange-timeout' parameter is not an integer";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"user-context\": [ ] } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'user-context' parameter is not a map";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"comment\": true } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig server 'comment' parameter is not a string";
    expected += location;
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);
}

/// @brief Check configure fails on not well formed parameters.
TEST(GssTsigCfgTest, configureBadParameter) {
    string config = "{ \"tkey-lifetime\": -1 }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    string expected = "'tkey-lifetime' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:20)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    string prefix = "{ \"servers\": [ { \"id\": \"foo\", ";
    prefix += "\"ip-address\": \"2001:db8::1\", ";
    prefix += "\"server-principal\": \"DNS/server.example.org@REALM\",";

    config = "{ \"tkey-lifetime\": 4294967296 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"tkey-lifetime\": -1 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'tkey-lifetime' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:129)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"tkey-lifetime\": 4294967296 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"rekey-interval\": -1 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'rekey-interval' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:21)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"rekey-interval\": 4294967296 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"rekey-interval\": -1 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'rekey-interval' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:130)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"rekey-interval\": 4294967296 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"retry-interval\": -1 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'retry-interval' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:21)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"retry-interval\": 4294967296 }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"retry-interval\": -1 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'retry-interval' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:130)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"retry-interval\": 4294967296 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"tkey-protocol\": \"udp\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'tkey-protocol' parameter must be UDP or TCP (<string>:1:20)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"tkey-protocol\": \"udp\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'tkey-protocol' parameter must be UDP or TCP (<string>:1:129)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"exchange-timeout\": -1 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'exchange-timeout' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:132)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = prefix + " \"exchange-timeout\": 4294967296 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'exchange-timeout' parameter is out of range ";
    expected += "[0..4294967295] (<string>:1:132)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'id' parameter must be not empty in ";
    expected += "gss_tsig server entry (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"foobar\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server entry: ";
    expected += "Failed to convert string to address 'foobar': ";
    expected += "Invalid argument (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"port\": -1 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server entry: ";
    expected += "The 'port' value (-1) is not within expected range: ";
    expected += "(0 - 65535) (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"port\": 65536 } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server entry: ";
    expected += "The 'port' value (65536) is not within expected range: ";
    expected += "(0 - 65535) (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"server-principal\": \"DNS/@REALM\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server entry: ";
    expected += "can't get the GSS-TSIG key name suffix from ";
    expected += "the DNS server principal 'DNS/@REALM' (<string>:1:80)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\" } ], ";
    config += "\"server-principal\": \"DNS/@REALM\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server-principal parameter: ";
    expected += "can't get the GSS-TSIG key name suffix from ";
    expected += "the DNS server principal 'DNS/@REALM' (<string>:1:84)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"server-principal\": \"DNS/";
    config += "012345678901234567890123456789";
    config += "012345678901234567890123456789";
    config += "012345678901234567890123456789@REALM\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server entry: ";
    expected += "check of the GSS-TSIG key name suffix 'sig-";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789' ";
    expected += "failed: label is too long in 1234567890.sig-";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789 (<string>:1:80)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\" } ], ";
    config += "\"server-principal\": \"DNS/";
    config += "012345678901234567890123456789";
    config += "012345678901234567890123456789";
    config += "012345678901234567890123456789@REALM\" }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "gss_tsig bad server-principal parameter: ";
    expected += "check of the GSS-TSIG key name suffix 'sig-";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789' ";
    expected += "failed: label is too long in 1234567890.sig-";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789";
    expected += "012345678901234567890123456789 (<string>:1:84)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    // There are other possible errors from DNS, e.g. too many labels.
}

/// @brief Check configure fails on missing required parameters.
TEST(GssTsigCfgTest, configureRequired) {
    string config = "{ \"servers\": [ { } ] }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    string expected = "'id' parameter is required in ";
    expected += "gss_tsig server entry (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'id' parameter must be not empty in ";
    expected += "gss_tsig server entry (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'ip-address' parameter is required in ";
    expected += "gss_tsig server entry (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);

    config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\" } ] }";
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    expected = "'server-principal' parameter is required in ";
    expected += "gss_tsig server entry (<string>:1:17)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);
}

/// @brief Check configure fails on duplicate server ID.
TEST(GssTsigCfgTest, configureDuplicate) {
    string config = "{ \"server-principal\": \"DNS/example.org@REALM\", ";
    config += "\"servers\": [ { ";
    config += "\"id\": \"foo\", \"ip-address\": \"192.1.2.3\" }, {";
    config += "\"id\": \"foo\", \"ip-address\": \"192.1.2.4\" } ] }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    string expected = "'foo' id is already used in ";
    expected += "gss_tsig server entry (<string>:1:106)";
    EXPECT_THROW_MSG(cfg.configure(json), BadValue, expected);
}

/// @brief Check TKEY protocol default value.
TEST(GssTsigCfgTest, tkeyProtoDefault) {
    // Constructor default is TCP.
    string config = "{ \"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"server-principal\": \"DNS/server1.example.org@REALM\" } ] }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    ASSERT_NO_THROW(cfg.configure(json));
    EXPECT_EQ(3600, cfg.getMaxKeyLifetime());
    const DnsServerList& servers = cfg.getServerList();
    ASSERT_EQ(1, servers.size());

    DnsServerPtr server;
    ASSERT_NO_THROW(server = servers.at(0));
    EXPECT_EQ(IOFetch::TCP, server->getKeyProto());
}

/// @brief Check TKEY protocol global value.
TEST(GssTsigCfgTest, tkeyProtoGlobal) {
    // Global value is used when not override by a local value.
    string config = "{ \"tkey-protocol\": \"UDP\", ";
    config += "\"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"server-principal\": \"DNS/server1.example.org@REALM\" } ] }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    ASSERT_NO_THROW(cfg.configure(json));
    const DnsServerList& servers = cfg.getServerList();
    ASSERT_EQ(1, servers.size());

    DnsServerPtr server;
    ASSERT_NO_THROW(server = servers.at(0));
    EXPECT_EQ(IOFetch::UDP, server->getKeyProto());
}

/// @brief Check TKEY protocol local value.
TEST(GssTsigCfgTest, tkeyProtoLocal) {
    // Local value has precedence.
    string config = "{ \"tkey-protocol\": \"TCP\", ";
    config += "\"servers\": [ { \"id\": \"foo\", ";
    config += "\"ip-address\": \"2001:db8::1\", ";
    config += "\"server-principal\": \"DNS/server1.example.org@REALM\",";
    config += "\"tkey-protocol\": \"UDP\" } ] }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ASSERT_TRUE(json);
    GssTsigCfg cfg;
    ASSERT_NO_THROW(cfg.configure(json));
    const DnsServerList& servers = cfg.getServerList();
    ASSERT_EQ(1, servers.size());

    DnsServerPtr server;
    ASSERT_NO_THROW(server = servers.at(0));
    EXPECT_EQ(IOFetch::UDP, server->getKeyProto());
}

/// @brief Check renew and retry bad interval values.
TEST(GssTsigCfgTest, intervalsBadCase) {
    vector<ConfigSet> cases = {
        { -1, -1, -1, -1, -1, -1, false, false,
          "these are default values so this should not throw" },
        { -1, -1, -1, -1, -1, -1, true, false,
          "these are default values so this should not throw" },
        { 2700, -1, -1, -1, -1, -1, false, true,
          "the default 'rekey-interval' parameter must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { 2700, -1, -1, -1, -1, -1, true, true,
          "the default 'rekey-interval' parameter must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { -1, 2700, -1, -1, -1, -1, false, true,
          "the default 'rekey-interval' parameter must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:201): range [0..2700]" },
        { -1, 2700, -1, -1, -1, -1, true, true,
          "the default 'rekey-interval' parameter must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:201): range [0..2700]" },
        { 2700, 1800, -1, -1, -1, -1, false, true,
          "the default 'rekey-interval' parameter must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { 2700, 1800, -1, -1, -1, -1, true, true,
          "the default 'rekey-interval' parameter must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { -1, -1, 3600, -1, -1, -1, false, true,
          "the global 'rekey-interval' parameter (<string>:1:93) must be smaller than "
          "the default 'tkey-lifetime' parameter: range [0..3600]" },
        { -1, -1, 3600, -1, -1, -1, true, true,
          "the global 'rekey-interval' parameter (<string>:1:93) must be smaller than "
          "the default 'tkey-lifetime' parameter: range [0..3600]" },
        { 2700, -1, 3600, -1, -1, -1, false, true,
          "the global 'rekey-interval' parameter (<string>:1:116) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { 2700, -1, 3600, -1, -1, -1, true, true,
          "the global 'rekey-interval' parameter (<string>:1:116) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { -1, 1800, 2700, -1, -1, -1, false, true,
          "the global 'rekey-interval' parameter (<string>:1:93) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:225): range [0..1800]" },
        { -1, 1800, 2700, -1, -1, -1, true, true,
          "the global 'rekey-interval' parameter (<string>:1:93) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:225): range [0..1800]" },
        { 2700, 1800, 3600, -1, -1, -1, false, true,
          "the global 'rekey-interval' parameter (<string>:1:116) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { 2700, 1800, 3600, -1, -1, -1, true, true,
          "the global 'rekey-interval' parameter (<string>:1:116) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..2700]" },
        { 4800, 1800, 3600, -1, -1, -1, false, true,
          "the global 'rekey-interval' parameter (<string>:1:116) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:248): range [0..1800]" },
        { 4800, 1800, 3600, -1, -1, -1, true, true,
          "the global 'rekey-interval' parameter (<string>:1:116) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:248): range [0..1800]" },
        { -1, -1, -1, 3600, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:202) must be smaller than "
          "the default 'tkey-lifetime' parameter: range [0..3600]" },
        { -1, -1, -1, 3600, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:202) must be smaller than "
          "the default 'tkey-lifetime' parameter: range [0..3600]" },
        { 3600, -1, -1, 3600, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:225) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..3600]" },
        { 3600, -1, -1, 3600, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:225) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..3600]" },
        { -1, 3600, -1, 3600, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:225) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:201): range [0..3600]" },
        { -1, 3600, -1, 3600, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:225) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:201): range [0..3600]" },
        { 5400, 3600, -1, 6400, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:248) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:224): range [0..3600]" },
        { 5400, 3600, -1, 6400, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:248) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:224): range [0..3600]" },
        { -1, -1, 2700, 6400, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:226) must be smaller than "
          "the default 'tkey-lifetime' parameter: range [0..3600]" },
        { -1, -1, 2700, 6400, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:226) must be smaller than "
          "the default 'tkey-lifetime' parameter: range [0..3600]" },
        { 3600, -1, 2700, 6400, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:249) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..3600]" },
        { 3600, -1, 2700, 6400, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:249) must be smaller than "
          "the global 'tkey-lifetime' parameter (<string>:1:92): range [0..3600]" },
        { -1, 3600, 2700, 6400, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:249) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:225): range [0..3600]" },
        { -1, 3600, 2700, 6400, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:249) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:225): range [0..3600]" },
        { 3600, 2700, 2700, 3600, -1, -1, false, true,
          "the server 'rekey-interval' parameter (<string>:1:272) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:248): range [0..2700]" },
        { 3600, 2700, 2700, 3600, -1, -1, true, true,
          "the server 'rekey-interval' parameter (<string>:1:272) must be smaller than "
          "the server 'tkey-lifetime' parameter (<string>:1:248): range [0..2700]" },
        { -1, -1, -1, -1, 2700, -1, false, true,
          "the global 'retry-interval' parameter (<string>:1:93) must be smaller then "
          "the default 'rekey-interval' parameter (<string>:1:93): range [0..2700]" },
        { -1, -1, -1, -1, 2700, -1, true, true,
          "the global 'retry-interval' parameter (<string>:1:93) must be smaller then "
          "the default 'rekey-interval' parameter (<string>:1:93): range [0..2700]" },
        { -1, -1, 2700, -1, 2700, -1, false, true,
          "the global 'retry-interval' parameter (<string>:1:117) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:117): range [0..2700]" },
        { -1, -1, 2700, -1, 2700, -1, true, true,
          "the global 'retry-interval' parameter (<string>:1:117) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:117): range [0..2700]" },
        { -1, -1, -1, 900, 1800, -1, false, true,
          "the global 'retry-interval' parameter (<string>:1:93) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:93): range [0..900]" },
        { -1, -1, -1, 900, 1800, -1, true, true,
          "the global 'retry-interval' parameter (<string>:1:93) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:93): range [0..900]" },
        { -1, -1, 2700, 1800, 3600, -1, false, true,
          "the global 'retry-interval' parameter (<string>:1:117) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:117): range [0..2700]" },
        { -1, -1, 2700, 1800, 3600, -1, true, true,
          "the global 'retry-interval' parameter (<string>:1:117) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:117): range [0..2700]" },
        { -1, -1, 2700, 900, 1800, -1, false, true,
          "the global 'retry-interval' parameter (<string>:1:117) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:117): range [0..900]" },
        { -1, -1, 2700, 900, 1800, -1, true, true,
          "the global 'retry-interval' parameter (<string>:1:117) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:117): range [0..900]" },
        { -1, -1, -1, -1, -1, 2700, false, true,
          "the server 'retry-interval' parameter (<string>:1:202) must be smaller then "
          "the default 'rekey-interval' parameter (<string>:1:202): range [0..2700]" },
        { -1, -1, -1, -1, -1, 2700, true, true,
          "the server 'retry-interval' parameter (<string>:1:202) must be smaller then "
          "the default 'rekey-interval' parameter (<string>:1:202): range [0..2700]" },
        { -1, -1, 2700, -1, -1, 2700, false, true,
          "the server 'retry-interval' parameter (<string>:1:226) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:226): range [0..2700]" },
        { -1, -1, 2700, -1, -1, 2700, true, true,
          "the server 'retry-interval' parameter (<string>:1:226) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:226): range [0..2700]" },
        { -1, -1, -1, 900, -1, 1800, false, true,
          "the server 'retry-interval' parameter (<string>:1:225) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:225): range [0..900]" },
        { -1, -1, -1, 900, -1, 1800, true, true,
          "the server 'retry-interval' parameter (<string>:1:225) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:225): range [0..900]" },
        { -1, -1, 2700, 1800, -1, 3600, false, true,
          "the server 'retry-interval' parameter (<string>:1:250) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:250): range [0..1800]" },
        { -1, -1, 2700, 1800, -1, 3600, true, true,
          "the server 'retry-interval' parameter (<string>:1:250) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:250): range [0..1800]" },
        { -1, -1, -1, -1, 1800, 3600, false, true,
          "the server 'retry-interval' parameter (<string>:1:226) must be smaller then "
          "the default 'rekey-interval' parameter (<string>:1:226): range [0..2700]" },
        { -1, -1, -1, -1, 1800, 3600, true, true,
          "the server 'retry-interval' parameter (<string>:1:226) must be smaller then "
          "the default 'rekey-interval' parameter (<string>:1:226): range [0..2700]" },
        { -1, -1, 2700, -1, 1800, 3600, false, true,
          "the server 'retry-interval' parameter (<string>:1:250) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:250): range [0..2700]" },
        { -1, -1, 2700, -1, 1800, 3600, true, true,
          "the server 'retry-interval' parameter (<string>:1:250) must be smaller then "
          "the global 'rekey-interval' parameter (<string>:1:250): range [0..2700]" },
        { -1, -1, -1, 2700, 1800, 3600, false, true,
          "the server 'retry-interval' parameter (<string>:1:250) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:250): range [0..2700]" },
        { -1, -1, -1, 2700, 1800, 3600, true, true,
          "the server 'retry-interval' parameter (<string>:1:250) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:250): range [0..2700]" },
        { -1, -1, 2700, 1800, 1800, 2700, false, true,
          "the server 'retry-interval' parameter (<string>:1:274) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:274): range [0..1800]" },
        { -1, -1, 2700, 1800, 1800, 2700, true, true,
          "the server 'retry-interval' parameter (<string>:1:274) must be smaller then "
          "the server 'rekey-interval' parameter (<string>:1:274): range [0..1800]" },
    };
    for (auto const& config : cases) {
        checkConfig(config);
    }
}

/// @brief Check renew and retry good interval values.
TEST(GssTsigCfgTest, intervalsGoodCase) {
    vector<ConfigSet> cases = {
        { -1, -1, -1, -1, -1, -1, false, false, "" },
        { -1, -1, -1, -1, -1, -1, true, false, "" },
        { 5400, -1, -1, -1, -1, -1, false, false, "" },
        { 5400, -1, -1, -1, -1, -1, true, false, "" },
        { -1, 5400, -1, -1, -1, -1, false, false, "" },
        { -1, 5400, -1, -1, -1, -1, true, false, "" },
        { 5400, 7200, -1, -1, -1, -1, false, false, "" },
        { 5400, 7200, -1, -1, -1, -1, true, false, "" },
        { -1, -1, 1800, -1, -1, -1, false, false, "" },
        { -1, -1, 1800, -1, -1, -1, true, false, "" },
        { 5400, -1, 1800, -1, -1, -1, false, false, "" },
        { 5400, -1, 1800, -1, -1, -1, true, false, "" },
        { -1, 5400, 2700, -1, -1, -1, false, false, "" },
        { -1, 5400, 2700, -1, -1, -1, true, false, "" },
        { 5400, 2700, 1800, -1, -1, -1, false, false, "" },
        { 5400, 2700, 1800, -1, -1, -1, true, false, "" },
        { -1, -1, -1, 1800, -1, -1, false, false, "" },
        { -1, -1, -1, 1800, -1, -1, true, false, "" },
        { 5400, -1, -1, 3600, -1, -1, false, false, "" },
        { 5400, -1, -1, 3600, -1, -1, true, false, "" },
        { -1, 5400, -1, 3600, -1, -1, false, false, "" },
        { -1, 5400, -1, 3600, -1, -1, true, false, "" },
        { 5400, 7200, -1, 5400, -1, -1, false, false, "" },
        { 5400, 7200, -1, 5400, -1, -1, true, false, "" },
        { -1, -1, 2700, 1800, -1, -1, false, false, "" },
        { -1, -1, 2700, 1800, -1, -1, true, false, "" },
        { 5400, -1, 2700, 3600, -1, -1, false, false, "" },
        { 5400, -1, 2700, 3600, -1, -1, true, false, "" },
        { -1, 5400, 2700, 3600, -1, -1, false, false, "" },
        { -1, 5400, 2700, 3600, -1, -1, true, false, "" },
        { 3600, 2700, 2700, 1800, -1, -1, false, false, "" },
        { 3600, 2700, 2700, 1800, -1, -1, true, false, "" },
        { -1, -1, -1, -1, 1800, -1, false, false, "" },
        { -1, -1, -1, -1, 1800, -1, true, false, "" },
        { -1, -1, 2700, -1, 900, -1, false, false, "" },
        { -1, -1, 2700, -1, 900, -1, true, false, "" },
        { -1, -1, -1, 2700, 900, -1, false, false, "" },
        { -1, -1, -1, 2700, 900, -1, true, false, "" },
        { -1, -1, 2700, 1800, 900, -1, false, false, "" },
        { -1, -1, 2700, 1800, 900, -1, true, false, "" },
        { -1, -1, -1, -1, -1, 1800, false, false, "" },
        { -1, -1, -1, -1, -1, 1800, true, false, "" },
        { -1, -1, 2700, -1, -1, 1800, false, false, "" },
        { -1, -1, 2700, -1, -1, 1800, true, false, "" },
        { -1, -1, -1, 2700, -1, 1800, false, false, "" },
        { -1, -1, -1, 2700, -1, 1800, true, false, "" },
        { -1, -1, 1800, 2700, -1, 1800, false, false, "" },
        { -1, -1, 1800, 2700, -1, 1800, true, false, "" },
        { -1, -1, -1, -1, 900, 1800, false, false, "" },
        { -1, -1, -1, -1, 900, 1800, true, false, "" },
        { -1, -1, 2700, -1, 900, 1800, false, false, "" },
        { -1, -1, 2700, -1, 900, 1800, true, false, "" },
        { -1, -1, -1, 2700, 900, 1800, false, false, "" },
        { -1, -1, -1, 2700, 900, 1800, true, false, "" },
        { -1, -1, 2700, 900, 1800, 240, false, false, "" },
        { -1, -1, 2700, 900, 1800, 240, true, false, "" },
    };
    for (auto const& config : cases) {
        checkConfig(config);
    }
}

}
