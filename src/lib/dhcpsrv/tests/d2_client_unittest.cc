// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc;

namespace {

/// @brief Checks constructors and accessors of D2ClientConfig.
TEST(D2ClientConfigTest, constructorsAndAccessors) {
    D2ClientConfigPtr d2_client_config;

    // Verify default constructor creates a disabled instance.
    ASSERT_NO_THROW(d2_client_config.reset(new D2ClientConfig()));
    EXPECT_FALSE(d2_client_config->getEnableUpdates());

    // Verify the enable-updates can be toggled.
    d2_client_config->enableUpdates(true);
    EXPECT_TRUE(d2_client_config->getEnableUpdates());
    d2_client_config->enableUpdates(false);
    EXPECT_FALSE(d2_client_config->getEnableUpdates());

    d2_client_config.reset();

    bool enable_updates = true;
    isc::asiolink::IOAddress server_ip("127.0.0.1");
    size_t server_port = 477;
    isc::asiolink::IOAddress sender_ip("127.0.0.1");
    size_t sender_port = 478;
    size_t max_queue_size = 2048;
    dhcp_ddns::NameChangeProtocol ncr_protocol = dhcp_ddns::NCR_UDP;
    dhcp_ddns::NameChangeFormat ncr_format = dhcp_ddns::FMT_JSON;
    bool always_include_fqdn = true;
    bool override_no_update = true;
    bool override_client_update = true;
    bool replace_client_name = true;
    std::string generated_prefix = "the_prefix";
    std::string qualifying_suffix = "the.suffix.";

    // Verify that we can construct a valid, enabled instance.
    ASSERT_NO_THROW(d2_client_config.reset(new
                                           D2ClientConfig(enable_updates,
                                                          server_ip,
                                                          server_port,
                                                          sender_ip,
                                                          sender_port,
                                                          max_queue_size,
                                                          ncr_protocol,
                                                          ncr_format,
                                                          always_include_fqdn,
                                                          override_no_update,
                                                         override_client_update,
                                                          replace_client_name,
                                                          generated_prefix,
                                                          qualifying_suffix)));

    ASSERT_TRUE(d2_client_config);

    // Verify that the accessors return the expected values.
    EXPECT_EQ(d2_client_config->getEnableUpdates(), enable_updates);

    EXPECT_EQ(d2_client_config->getServerIp(), server_ip);
    EXPECT_EQ(d2_client_config->getServerPort(), server_port);
    EXPECT_EQ(d2_client_config->getSenderIp(), sender_ip);
    EXPECT_EQ(d2_client_config->getSenderPort(), sender_port);
    EXPECT_EQ(d2_client_config->getMaxQueueSize(), max_queue_size);
    EXPECT_EQ(d2_client_config->getNcrProtocol(), ncr_protocol);
    EXPECT_EQ(d2_client_config->getNcrFormat(), ncr_format);
    EXPECT_EQ(d2_client_config->getAlwaysIncludeFqdn(), always_include_fqdn);
    EXPECT_EQ(d2_client_config->getOverrideNoUpdate(), override_no_update);
    EXPECT_EQ(d2_client_config->getOverrideClientUpdate(),
              override_client_update);
    EXPECT_EQ(d2_client_config->getReplaceClientName(), replace_client_name);
    EXPECT_EQ(d2_client_config->getGeneratedPrefix(), generated_prefix);
    EXPECT_EQ(d2_client_config->getQualifyingSuffix(), qualifying_suffix);

    // Verify that toText called by << operator doesn't bomb.
    ASSERT_NO_THROW(std::cout << "toText test:" << std::endl <<
                    *d2_client_config << std::endl);

    // Verify that constructor does not allow use of NCR_TCP.
    /// @todo obviously this becomes invalid once TCP is supported.
    ASSERT_THROW(d2_client_config.reset(new
                                        D2ClientConfig(enable_updates,
                                                       server_ip,
                                                       server_port,
                                                       sender_ip,
                                                       sender_port,
                                                       max_queue_size,
                                                       dhcp_ddns::NCR_TCP,
                                                       ncr_format,
                                                       always_include_fqdn,
                                                       override_no_update,
                                                       override_client_update,
                                                       replace_client_name,
                                                       generated_prefix,
                                                       qualifying_suffix)),
                 D2ClientError);

    /// @todo if additional validation is added to ctor, this test needs to
    /// expand accordingly.
}

/// @brief Tests the equality and inequality operators of D2ClientConfig.
TEST(D2ClientConfigTest, equalityOperator) {
    D2ClientConfigPtr ref_config;
    D2ClientConfigPtr test_config;

    isc::asiolink::IOAddress ref_address("127.0.0.1");
    isc::asiolink::IOAddress test_address("127.0.0.2");

    // Create an instance to use as a reference.
    ASSERT_NO_THROW(ref_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(ref_config);

    // Check a configuration that is identical to reference configuration.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_TRUE(*ref_config == *test_config);
    EXPECT_FALSE(*ref_config != *test_config);

    // Check a configuration that differs only by enable flag.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(false,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by server ip.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    test_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by server port.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 333, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by sender ip.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, test_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by sender port.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 333, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by max queue size.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 2048,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by always_include_fqdn.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    false, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by override_no_update.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, false, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by override_client_update.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, false, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by replace_client_name.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, false,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by generated_prefix.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "bogus", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by qualifying_suffix.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477, ref_address, 478, 1024,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true,
                    "pre-fix", "bogus")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);
}

/// @brief Checks the D2ClientMgr constructor.
TEST(D2ClientMgr, constructor) {
    D2ClientMgrPtr d2_client_mgr;

    // Verify we can construct with the default constructor.
    ASSERT_NO_THROW(d2_client_mgr.reset(new D2ClientMgr()));

    // After construction, D2 configuration should be disabled.
    // Fetch it and verify this is the case.
    D2ClientConfigPtr original_config = d2_client_mgr->getD2ClientConfig();
    ASSERT_TRUE(original_config);
    EXPECT_FALSE(original_config->getEnableUpdates());

    // Make sure convenience method agrees.
    EXPECT_FALSE(d2_client_mgr->ddnsEnabled());
}

/// @brief Checks passing the D2ClientMgr a valid D2 client configuration.
/// @todo Once NameChangeSender is integrated, this test needs to expand, and
/// additional scenario tests will need to be written.
TEST(D2ClientMgr, validConfig) {
    D2ClientMgrPtr d2_client_mgr;

    // Construct the manager and fetch its initial configuration.
    ASSERT_NO_THROW(d2_client_mgr.reset(new D2ClientMgr()));
    D2ClientConfigPtr original_config = d2_client_mgr->getD2ClientConfig();
    ASSERT_TRUE(original_config);

    // Verify that we cannot set the config to an empty pointer.
    D2ClientConfigPtr new_cfg;
    ASSERT_THROW(d2_client_mgr->setD2ClientConfig(new_cfg), D2ClientError);

    // Create a new, enabled config.
    ASSERT_NO_THROW(new_cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  true, true, true, true,
                                  "pre-fix", "suf-fix")));

    // Verify that we can assign a new, non-empty configuration.
    ASSERT_NO_THROW(d2_client_mgr->setD2ClientConfig(new_cfg));

    // Verify that we can fetch the newly assigned configuration.
    D2ClientConfigPtr updated_config = d2_client_mgr->getD2ClientConfig();
    ASSERT_TRUE(updated_config);
    EXPECT_TRUE(updated_config->getEnableUpdates());

    // Make sure convenience method agrees with the updated configuration.
    EXPECT_TRUE(d2_client_mgr->ddnsEnabled());

    // Make sure the configuration we fetched is the one  we assigned,
    // and not the original configuration.
    EXPECT_EQ(*new_cfg, *updated_config);
    EXPECT_NE(*original_config, *updated_config);
}


/// @brief Tests that analyzeFqdn detects invalid combination of both the
/// client S and N flags set to true.
TEST(D2ClientMgr, analyzeFqdnInvalidCombination) {
    D2ClientMgr mgr;
    bool server_s = false;
    bool server_n = false;

    // Create disabled configuration.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig()));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_FALSE(mgr.ddnsEnabled());

    // client S=1 N=1 is invalid.  analyzeFqdn should throw.
    ASSERT_THROW(mgr.analyzeFqdn(true, true, server_s, server_n),
                 isc::BadValue);

    // Create enabled configuration with all controls off (no overrides).
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, false, false,
                                  "pre-fix", "suf-fix")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(mgr.ddnsEnabled());

    // client S=1 N=1 is invalid.  analyzeFqdn should throw.
    ASSERT_THROW(mgr.analyzeFqdn(true, true, server_s, server_n),
                 isc::BadValue);
}

/// @brief Tests that analyzeFqdn generates correct server S and N flags when
/// updates are enabled and all overrides are off.
TEST(D2ClientMgr, analyzeFqdnEnabledNoOverrides) {
    D2ClientMgr mgr;
    bool server_s = false;
    bool server_n = false;

    // Create enabled configuration with all controls off (no overrides).
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, false, false,
                                  "pre-fix", "suf-fix")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_FALSE(cfg->getOverrideClientUpdate());
    ASSERT_FALSE(cfg->getOverrideNoUpdate());

    // client S=0 N=0 means client wants to do forward update.
    // server S should be 0 (server is not doing forward updates)
    // and server N should be 0 (server doing reverse updates)
    mgr.analyzeFqdn(false, false, server_s, server_n);
    EXPECT_FALSE(server_s);
    EXPECT_FALSE(server_n);

    // client S=1 N=0 means client wants server to do forward update.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    mgr.analyzeFqdn(true, false, server_s, server_n);
    EXPECT_TRUE(server_s);
    EXPECT_FALSE(server_n);


    // client S=0 N=1 means client wants no one to do forward updates.
    // server S should be 0 (server is  not forward updates)
    // and server N should be 1 (server is not doing any updates)
    mgr.analyzeFqdn(false, true, server_s, server_n);
    EXPECT_FALSE(server_s);
    EXPECT_TRUE(server_n);
}

/// @brief Tests that analyzeFqdn generates correct server S and N flags when
/// updates are enabled and override-no-update is on.
TEST(D2ClientMgr, analyzeFqdnEnabledOverrideNoUpdate) {
    D2ClientMgr mgr;
    bool server_s = false;
    bool server_n = false;

    // Create enabled configuration with OVERRIDE_NO_UPDATE on.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, true, false, false,
                                  "pre-fix", "suf-fix")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_TRUE(cfg->getOverrideNoUpdate());
    ASSERT_FALSE(cfg->getOverrideClientUpdate());

    // client S=0 N=0 means client wants to do forward update.
    // server S should be 0 (server is not doing forward updates)
    // and server N should be 0 (server is doing reverse updates)
    mgr.analyzeFqdn(false, false, server_s, server_n);
    EXPECT_FALSE(server_s);
    EXPECT_FALSE(server_n);

    // client S=1 N=0 means client wants server to do forward update.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    mgr.analyzeFqdn(true, false, server_s, server_n);
    EXPECT_TRUE(server_s);
    EXPECT_FALSE(server_n);

    // client S=0 N=1 means client wants no one to do forward updates.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server is doing updates)
    mgr.analyzeFqdn(false, true, server_s, server_n);
    EXPECT_TRUE(server_s);
    EXPECT_FALSE(server_n);
}

/// @brief Tests that analyzeFqdn generates correct server S and N flags when
/// updates are enabled and override-client-update is on.
TEST(D2ClientMgr, analyzeFqdnEnabledOverrideClientUpdate) {
    D2ClientMgr mgr;
    bool server_s = false;
    bool server_n = false;

    // Create enabled configuration with OVERRIDE_CLIENT_UPDATE on.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "pre-fix", "suf-fix")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_FALSE(cfg->getOverrideNoUpdate());
    ASSERT_TRUE(cfg->getOverrideClientUpdate());

    // client S=0 N=0 means client wants to do forward update.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    mgr.analyzeFqdn(false, false, server_s, server_n);
    EXPECT_TRUE(server_s);
    EXPECT_FALSE(server_n);

    // client S=1 N=0 means client wants server to do forward update.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    mgr.analyzeFqdn(true, false, server_s, server_n);
    EXPECT_TRUE(server_s);
    EXPECT_FALSE(server_n);

    // client S=0 N=1 means client wants no one to do forward updates.
    // server S should be 0 (server is  not forward updates)
    // and server N should be 1 (server is not doing any updates)
    mgr.analyzeFqdn(false, true, server_s, server_n);
    EXPECT_FALSE(server_s);
    EXPECT_TRUE(server_n);
}

/// @brief Verifies the adustFqdnFlags template with Option4ClientFqdn objects.
/// Ensures that the method can set the N, S, and O flags properly.
/// Other permutations are covered by analyzeFqdnFlag tests.
TEST(D2ClientMgr, adjustFqdnFlagsV4) {
    D2ClientMgr mgr;
    Option4ClientFqdnPtr request;
    Option4ClientFqdnPtr response;

    // Create enabled configuration and override-no-update on.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, true, false, false,
                                  "pre-fix", "suf-fix")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_TRUE(cfg->getOverrideNoUpdate());
    ASSERT_FALSE(cfg->getOverrideClientUpdate());

    // client S=0 N=0 means client wants to do forward update.
    // server S should be 0 (server is not doing forward updates)
    // and server N should be 0 (server is doing reverse updates)
    // and server O should be 0
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));
    response->resetFlags();

    mgr.adjustFqdnFlags<Option4ClientFqdn>(*request, *response);
    EXPECT_FALSE(response->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(response->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_FALSE(response->getFlag(Option4ClientFqdn::FLAG_O));

    // client S=1 N=0 means client wants server to do forward update.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    // and server O should be 0
    request.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S,
                                        Option4ClientFqdn::RCODE_CLIENT(),
                                        "", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));
    response->resetFlags();

    mgr.adjustFqdnFlags<Option4ClientFqdn>(*request, *response);
    EXPECT_TRUE(response->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(response->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_FALSE(response->getFlag(Option4ClientFqdn::FLAG_O));

    // client S=0 N=1 means client wants no one to do updates
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    // and O should be 1 (overriding client S)
    request.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_N,
                                        Option4ClientFqdn::RCODE_CLIENT(),
                                        "", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));
    response->resetFlags();

    mgr.adjustFqdnFlags<Option4ClientFqdn>(*request, *response);
    EXPECT_TRUE(response->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(response->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_TRUE(response->getFlag(Option4ClientFqdn::FLAG_O));
}

/// @brief Verified the getUpdateDirections template method with
/// Option4ClientFqdn objects.
TEST(D2ClientMgr, updateDirectionsV4) {
    D2ClientMgr mgr;
    Option4ClientFqdnPtr response;

    bool do_forward = false;
    bool do_reverse = false;

    // Response S=0, N=0 should mean do reverse only.
    response.reset(new Option4ClientFqdn(0,
                                         Option4ClientFqdn::RCODE_CLIENT(),
                                         "", Option4ClientFqdn::PARTIAL));
    mgr.getUpdateDirections(*response, do_forward, do_reverse);
    EXPECT_FALSE(do_forward);
    EXPECT_TRUE(do_reverse);

    // Response S=0, N=1 should mean don't do either.
    response.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_N,
                                         Option4ClientFqdn::RCODE_CLIENT(),
                                         "", Option4ClientFqdn::PARTIAL));
    mgr.getUpdateDirections(*response, do_forward, do_reverse);
    EXPECT_FALSE(do_forward);
    EXPECT_FALSE(do_reverse);

    // Response S=1, N=0 should mean do both.
    response.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S,
                                         Option4ClientFqdn::RCODE_CLIENT(),
                                         "", Option4ClientFqdn::PARTIAL));
    mgr.getUpdateDirections(*response, do_forward, do_reverse);
    EXPECT_TRUE(do_forward);
    EXPECT_TRUE(do_reverse);

    // Response S=1, N=1 isn't possible.
}

/// @brief Tests the qualifyName method's ability to construct FQDNs
TEST(D2ClientMgr, qualifyName) {
    D2ClientMgr mgr;

    // Create enabled configuration.
    D2ClientConfigPtr cfg;

    //append suffix and dot
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));

    // Verify that the qualifying suffix gets appended with trailing dot added.
    std::string partial_name = "somehost";
    std::string qualified_name = mgr.qualifyName(partial_name, true);
    EXPECT_EQ("somehost.suffix.com.", qualified_name);


        //append suffix but dot
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    partial_name = "somehost";
    qualified_name = mgr.qualifyName(partial_name, false); //false means no dot
    EXPECT_EQ("somehost.suffix.com", qualified_name);


        //append no suffix and not dot
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "prefix", ""))); //empty suffix
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    partial_name = "somehost";
    qualified_name = mgr.qualifyName(partial_name, false); //false means no dot
    EXPECT_EQ("somehost", qualified_name);

    // Verify that the qualifying suffix gets appended with trailing dot added.
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "prefix", "hasdot.com.")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));

    // Verify that the qualifying suffix gets appended without dot added.
    qualified_name = mgr.qualifyName(partial_name, true);
    EXPECT_EQ("somehost.hasdot.com.", qualified_name);

    // Verify that the qualifying suffix gets appended without an
    // extraneous dot when partial_name ends with a "."
    qualified_name = mgr.qualifyName("somehost.", true);
    EXPECT_EQ("somehost.hasdot.com.", qualified_name);

    // Reconfigure to a "" suffix
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "prefix", "")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));

    // Verify that a name with a trailing dot does not get an extraneous
    // dot when the suffix is blank
    qualified_name = mgr.qualifyName("somehost.", true);
    EXPECT_EQ("somehost.", qualified_name);

    // Verify that a name with no trailing dot gets just a dot when the
    // suffix is blank
    qualified_name = mgr.qualifyName("somehost", true);
    EXPECT_EQ("somehost.", qualified_name);

    // Verify that a name with no trailing dot does not get dotted when the
    // suffix is blank and trailing dot is false
    qualified_name = mgr.qualifyName("somehost", false);
    EXPECT_EQ("somehost", qualified_name);

    // Verify that a name with trailing dot gets "undotted" when the
    // suffix is blank and trailing dot is false
    qualified_name = mgr.qualifyName("somehost.", false);
    EXPECT_EQ("somehost", qualified_name);

}


/// @brief Tests the generateFdqn method's ability to construct FQDNs
TEST(D2ClientMgr, generateFqdn) {
    D2ClientMgr mgr;

    // Create enabled configuration.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, true, false,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));

    // Verify that it works with an IPv4 address.
    asiolink::IOAddress v4address("192.0.2.75");
    EXPECT_EQ("prefix-192-0-2-75.suffix.com.", mgr.generateFqdn(v4address,true));

    // Verify that it works with an IPv6 address.
    asiolink::IOAddress v6address("2001:db8::2");
    EXPECT_EQ("prefix-2001-db8--2.suffix.com.", mgr.generateFqdn(v6address,true));

    // Create a disabled config.
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig()));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));

    // Verify names generate properly with a disabled configuration.
    EXPECT_EQ("myhost-192-0-2-75.", mgr.generateFqdn(v4address,true));
    EXPECT_EQ("myhost-2001-db8--2.", mgr.generateFqdn(v6address,true));
}

/// @brief Tests adjustDomainName template method with Option4ClientFqdn
TEST(D2ClientMgr, adjustDomainNameV4) {
    D2ClientMgr mgr;
    Option4ClientFqdnPtr request;
    Option4ClientFqdnPtr response;

    // Create enabled configuration.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, false, false,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_FALSE(cfg->getReplaceClientName());

    // replace-client-name is false, client passes in empty fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));

    mgr.adjustDomainName<Option4ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, response->getDomainNameType());


    // replace-client-name is false, client passes in a partial fqdn
    // response should contain client's name plus the qualifying suffix.
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "myhost", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));

    mgr.adjustDomainName<Option4ClientFqdn>(*request, *response);
    EXPECT_EQ("myhost.suffix.com.", response->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, response->getDomainNameType());


    // replace-client-name is false, client passes in a full fqdn
    // response domain should not be altered.
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "myhost.example.com.",
                                         Option4ClientFqdn::FULL));
    response.reset(new Option4ClientFqdn(*request));
    mgr.adjustDomainName<Option4ClientFqdn>(*request, *response);
    EXPECT_EQ("myhost.example.com.", response->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, response->getDomainNameType());

    // Create enabled configuration.
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, false, true,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(cfg->getReplaceClientName());

    // replace-client-name is true, client passes in empty fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));

    mgr.adjustDomainName<Option4ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, response->getDomainNameType());

    // replace-client-name is true, client passes in a partial fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "myhost", Option4ClientFqdn::PARTIAL));
    response.reset(new Option4ClientFqdn(*request));

    mgr.adjustDomainName<Option4ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, response->getDomainNameType());


    // replace-client-name is true, client passes in a full fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                        "myhost.example.com.",
                                         Option4ClientFqdn::FULL));
    response.reset(new Option4ClientFqdn(*request));
    mgr.adjustDomainName<Option4ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, response->getDomainNameType());
}

/// @brief Tests adjustDomainName template method with Option6ClientFqdn
TEST(D2ClientMgr, adjustDomainNameV6) {
    D2ClientMgr mgr;
    Option6ClientFqdnPtr request;
    Option6ClientFqdnPtr response;

    // Create enabled configuration.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, false, false,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_FALSE(cfg->getReplaceClientName());

    // replace-client-name is false, client passes in empty fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option6ClientFqdn(0, "", Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));

    mgr.adjustDomainName<Option6ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, response->getDomainNameType());

    // replace-client-name is false, client passes in a partial fqdn
    // response should contain client's name plus the qualifying suffix.
    request.reset(new Option6ClientFqdn(0, "myhost",
                                        Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));

    mgr.adjustDomainName<Option6ClientFqdn>(*request, *response);
    EXPECT_EQ("myhost.suffix.com.", response->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, response->getDomainNameType());


    // replace-client-name is false, client passes in a full fqdn
    // response domain should not be altered.
    request.reset(new Option6ClientFqdn(0, "myhost.example.com.",
                                        Option6ClientFqdn::FULL));
    response.reset(new Option6ClientFqdn(*request));
    mgr.adjustDomainName<Option6ClientFqdn>(*request, *response);
    EXPECT_EQ("myhost.example.com.", response->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, response->getDomainNameType());

    // Create enabled configuration.
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, false, false, true,
                                  "prefix", "suffix.com")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(cfg->getReplaceClientName());

    // replace-client-name is true, client passes in empty fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option6ClientFqdn(0, "", Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));

    mgr.adjustDomainName<Option6ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, response->getDomainNameType());

    // replace-client-name is true, client passes in a partial fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option6ClientFqdn(0, "myhost",
                                        Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));

    mgr.adjustDomainName<Option6ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, response->getDomainNameType());


    // replace-client-name is true, client passes in a full fqdn
    // reponse domain should be empty/partial.
    request.reset(new Option6ClientFqdn(0, "myhost.example.com.",
                                        Option6ClientFqdn::FULL));
    response.reset(new Option6ClientFqdn(*request));
    mgr.adjustDomainName<Option6ClientFqdn>(*request, *response);
    EXPECT_EQ("", response->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, response->getDomainNameType());
}

/// @brief Verifies the adustFqdnFlags template with Option6ClientFqdn objects.
/// Ensures that the method can set the N, S, and O flags properly.
/// Other permutations are covered by analyzeFqdnFlags tests.
TEST(D2ClientMgr, adjustFqdnFlagsV6) {
    D2ClientMgr mgr;
    Option6ClientFqdnPtr request;
    Option6ClientFqdnPtr response;

    // Create enabled configuration and override-no-update on.
    D2ClientConfigPtr cfg;
    ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  false, true, false, false,
                                  "pre-fix", "suf-fix")));
    ASSERT_NO_THROW(mgr.setD2ClientConfig(cfg));
    ASSERT_TRUE(mgr.ddnsEnabled());
    ASSERT_TRUE(cfg->getOverrideNoUpdate());
    ASSERT_FALSE(cfg->getOverrideClientUpdate());

    // client S=0 N=0 means client wants to do forward update.
    // server S should be 0 (server is not doing forward updates)
    // and server N should be 0 (server doing reverse updates)
    // and server O should be 0
    request.reset(new Option6ClientFqdn(0, "", Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));
    response->resetFlags();

    mgr.adjustFqdnFlags<Option6ClientFqdn>(*request, *response);
    EXPECT_FALSE(response->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(response->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_FALSE(response->getFlag(Option6ClientFqdn::FLAG_O));

    // client S=1 N=0 means client wants server to do forward update.
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    // and server O should be 0
    request.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                        "", Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));
    response->resetFlags();

    mgr.adjustFqdnFlags<Option6ClientFqdn>(*request, *response);
    EXPECT_TRUE(response->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(response->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_FALSE(response->getFlag(Option6ClientFqdn::FLAG_O));

    // client S=0 N=1 means client wants no one to do updates
    // server S should be 1 (server is doing forward updates)
    // and server N should be 0 (server doing updates)
    // and O should be 1 (overriding client S)
    request.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_N,
                                        "", Option6ClientFqdn::PARTIAL));
    response.reset(new Option6ClientFqdn(*request));
    response->resetFlags();

    mgr.adjustFqdnFlags<Option6ClientFqdn>(*request, *response);
    EXPECT_TRUE(response->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(response->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_TRUE(response->getFlag(Option6ClientFqdn::FLAG_O));
}

/// @brief Verified the getUpdateDirections template method with
/// Option6ClientFqdn objects.
TEST(D2ClientMgr, updateDirectionsV6) {
    D2ClientMgr mgr;
    Option6ClientFqdnPtr response;

    bool do_forward = false;
    bool do_reverse = false;

    // Response S=0, N=0 should mean do reverse only.
    response.reset(new Option6ClientFqdn(0,
                                         "", Option6ClientFqdn::PARTIAL));
    mgr.getUpdateDirections(*response, do_forward, do_reverse);
    EXPECT_FALSE(do_forward);
    EXPECT_TRUE(do_reverse);

    // Response S=0, N=1 should mean don't do either.
    response.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_N,
                                         "", Option6ClientFqdn::PARTIAL));
    mgr.getUpdateDirections(*response, do_forward, do_reverse);
    EXPECT_FALSE(do_forward);
    EXPECT_FALSE(do_reverse);

    // Response S=1, N=0 should mean do both.
    response.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                         "", Option6ClientFqdn::PARTIAL));
    mgr.getUpdateDirections(*response, do_forward, do_reverse);
    EXPECT_TRUE(do_forward);
    EXPECT_TRUE(do_reverse);

    // Response S=1, N=1 isn't possible.
}

} // end of anonymous namespace
