// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/d2_client.h>
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

    d2_client_config.reset();

    bool enable_updates = true;
    isc::asiolink::IOAddress server_ip("127.0.0.1");
    size_t server_port = 477;
    dhcp_ddns::NameChangeProtocol ncr_protocol = dhcp_ddns::NCR_UDP;
    dhcp_ddns::NameChangeFormat ncr_format = dhcp_ddns::FMT_JSON;
    bool remove_on_renew = true;
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
                                                          ncr_protocol,
                                                          ncr_format,
                                                          remove_on_renew,
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
    EXPECT_EQ(d2_client_config->getNcrProtocol(), ncr_protocol);
    EXPECT_EQ(d2_client_config->getNcrFormat(), ncr_format);
    EXPECT_EQ(d2_client_config->getRemoveOnRenew(), remove_on_renew);
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
                                                       dhcp_ddns::NCR_TCP,
                                                       ncr_format,
                                                       remove_on_renew,
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
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(ref_config);

    // Check a configuration that is identical to reference configuration.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_TRUE(*ref_config == *test_config);
    EXPECT_FALSE(*ref_config != *test_config);

    // Check a configuration that differs only by enable flag.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(false,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by server ip.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    test_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by server port.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 333,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by remove_on_renew.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    false, true, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by always_include_fqdn.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, false, true, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by override_no_update.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, false, true, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by override_client_update.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, false, true,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by replace_client_name.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, false,
                    "pre-fix", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by generated_prefix.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
                    "bogus", "suf-fix")));
    ASSERT_TRUE(test_config);
    EXPECT_FALSE(*ref_config == *test_config);
    EXPECT_TRUE(*ref_config != *test_config);

    // Check a configuration that differs only by qualifying_suffix.
    ASSERT_NO_THROW(test_config.reset(new D2ClientConfig(true,
                    ref_address, 477,
                    dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                    true, true, true, true, true,
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
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  true, true, true, true, true,
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


} // end of anonymous namespace
