// Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <database/backend_selector.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp4.h>

#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/get_config_unittest.h>

#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::db;
using namespace std;

namespace {

/// @brief Test fixture for testing external configuration merging
class Dhcp4CBTest : public GenericBackendTest {
protected:
    /// @brief Pre test set up
    /// Called prior to each test.  It creates two configuration backends
    /// that differ by host name ("db1" and "db2"). It then registers
    /// a backend factory that will return them rather than create
    /// new instances. The backends need to pre-exist so they can be
    /// populated prior to calling server configure.  It uses
    /// TestConfigBackend instances but with a type of "memfile" to pass
    /// parsing.  Doing it all here allows us to use ASSERTs if we feel like
    /// it.
    virtual void SetUp() {
        DatabaseConnection::ParameterMap params;
        params[std::string("type")] = std::string("memfile");
        params[std::string("host")] = std::string("db1");
        db1_.reset(new TestConfigBackendDHCPv4(params));

        params[std::string("host")] = std::string("db2");
        db2_.reset(new TestConfigBackendDHCPv4(params));

        ConfigBackendDHCPv4Mgr::instance().registerBackendFactory("memfile",
            [this](const DatabaseConnection::ParameterMap& params)
                -> ConfigBackendDHCPv4Ptr {
                    auto host = params.find("host");
                    if (host != params.end()) {
                        if (host->second == "db1") {
                            return (db1_);
                        } else if (host->second == "db2") {
                            return (db2_);
                        }
                    }

                    // Apparently we're looking for a new one.
                    return (TestConfigBackendDHCPv4Ptr(new TestConfigBackendDHCPv4(params)));
                });
    }

    /// @brief Clean up after each test
    virtual void TearDown() {
        // Unregister the factory to be tidy.
        ConfigBackendDHCPv4Mgr::instance().unregisterBackendFactory("memfile");
    }

public:

    /// Constructor
    Dhcp4CBTest()
    : rcode_(-1), db1_selector("db1"), db2_selector("db1")   {
        // Open port 0 means to not do anything at all. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.
        srv_.reset(new ControlledDhcpv4Srv(0));

        // Create fresh context.
        resetConfiguration();
    }

    /// Destructor
    virtual ~Dhcp4CBTest() {
        resetConfiguration();
    };

    /// @brief Reset configuration singletons.
    void resetConfiguration() {
        CfgMgr::instance().clear();
        ConfigBackendDHCPv4Mgr::destroy();
    }

    /// @brief Convenience method for running configuration
    ///
    /// This method does not throw, but signals errors using gtest macros.
    ///
    /// @param config text to be parsed as JSON
    /// @param expected_code expected code (see cc/command_interpreter.h)
    /// @param exp_error expected text error (check skipped if empty)
    void configure(std::string config, int expected_code,
                   std::string exp_error = "") {
        ConstElementPtr json;
        try {
            json = parseDHCP4(config, true);
        } catch(const std::exception& ex) {
            ADD_FAILURE() << "parseDHCP4 failed: " << ex.what();
        }

        ConstElementPtr status;
        ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
        ASSERT_TRUE(status);

        int rcode;
        ConstElementPtr comment = parseAnswerText(rcode, status);
        ASSERT_EQ(expected_code, rcode) << " comment: "
                    << comment->stringValue();

        string text;
        ASSERT_NO_THROW(text = comment->stringValue());

        if (expected_code != rcode) {
            std::cout << "Reported status: " << text << std::endl;
        }

        if ((rcode != 0)) {
            if (!exp_error.empty()) {
                ASSERT_EQ(exp_error, text);
            }
        }
    }

    boost::scoped_ptr<Dhcpv4Srv> srv_;  ///< DHCP4 server under test
    int rcode_;                         ///< Return code from element parsing
    ConstElementPtr comment_;           ///< Reason for parse fail

    BackendSelector db1_selector; ///< BackendSelector by host for first config backend
    BackendSelector db2_selector; ///< BackendSelector by host for second config backend

    TestConfigBackendDHCPv4Ptr db1_; ///< First configuration backend instance
    TestConfigBackendDHCPv4Ptr db2_; ///< Second configuration backend instance
};

// This test verifies that externally configured globals are
// merged correctly into staging configuration.
TEST_F(Dhcp4CBTest, mergeGlobals) {
    string base_config =
        "{ \n"
        "    \"interfaces-config\": { \n"
        "        \"interfaces\": [\"*\" ] \n"
        "    }, \n"
        "    \"echo-client-id\": false, \n"
        "    \"decline-probation-period\": 7000, \n"
        "    \"valid-lifetime\": 1000, \n"
        "    \"rebind-timer\": 800, \n"
        "    \"server-hostname\": \"overwrite.me.com\", \n"
        "    \"config-control\": { \n"
        "       \"config-databases\": [ { \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db1\" \n"
        "           },{ \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db2\" \n"
        "           } \n"
        "       ] \n"
        "   } \n"
        "} \n";

    extractConfig(base_config);

    // Make some globals:
    StampedValuePtr server_hostname(new StampedValue("server-hostname", "isc.example.org"));
    StampedValuePtr decline_period(new StampedValue("decline-probation-period", Element::create(86400)));
    StampedValuePtr calc_tee_times(new StampedValue("calculate-tee-times", Element::create(bool(false))));
    StampedValuePtr t2_percent(new StampedValue("t2-percent", Element::create(0.75)));
    StampedValuePtr renew_timer(new StampedValue("renew-timer", Element::create(500)));
    StampedValuePtr mt_enabled(new StampedValue("multi-threading.enable-multi-threading", Element::create(true)));
    StampedValuePtr mt_pool_size(new StampedValue("multi-threading.thread-pool-size", Element::create(256)));

    // Let's add all of the globals to the second backend.  This will verify
    // we find them there.
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), server_hostname);
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), decline_period);
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), calc_tee_times);
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), t2_percent);
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), renew_timer);
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), mt_enabled);
    db2_->createUpdateGlobalParameter4(ServerSelector::ALL(), mt_pool_size);

    // Should parse and merge without error.
    ASSERT_NO_FATAL_FAILURE(configure(base_config, CONTROL_RESULT_SUCCESS, ""));

    // Verify the composite staging is correct.  (Remember that
    // CfgMgr::instance().commit() hasn't been called)
    SrvConfigPtr staging_cfg = CfgMgr::instance().getStagingCfg();

    // echo-client-id is set explicitly in the original config, meanwhile
    // the backend config does not set it, so the explicit value wins.
    EXPECT_FALSE(staging_cfg->getEchoClientId());

    // decline-probation-period is an explicit member that should come
    // from the backend.
    EXPECT_EQ(86400, staging_cfg->getDeclinePeriod());

    // Verify that the implicit globals from JSON are there.
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, "valid-lifetime",
                                                  Element::create(1000)));
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, "rebind-timer",
                                                  Element::create(800)));

    // Verify that the implicit globals from the backend are there.
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, server_hostname));
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, calc_tee_times));
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, t2_percent));
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, renew_timer));
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, mt_enabled));
    ASSERT_NO_FATAL_FAILURE(checkConfiguredGlobal(staging_cfg, mt_pool_size));
}

// This test verifies that externally configured option definitions
// merged correctly into staging configuration.
TEST_F(Dhcp4CBTest, mergeOptionDefs) {
    string base_config =
        "{ \n"
        "    \"option-def\": [ { \n"
        "        \"name\": \"one\", \n"
        "        \"code\": 1, \n"
        "        \"type\": \"ipv4-address\", \n"
        "        \"space\": \"isc\" \n"
        "     }, \n"
        "     { \n"
        "        \"name\": \"two\", \n"
        "        \"code\": 2, \n"
        "        \"type\": \"string\", \n"
        "        \"space\": \"isc\" \n"
        "     } \n"
        "   ], \n"
        "    \"config-control\": { \n"
        "       \"config-databases\": [ { \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db1\" \n"
        "           },{ \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db2\" \n"
        "           } \n"
        "       ] \n"
        "   } \n"
        "} \n";

    extractConfig(base_config);

    // Create option one replacement and add it to first backend.
    OptionDefinitionPtr def;
    def.reset(new OptionDefinition("one", 101, "isc", "uint16"));
    db1_->createUpdateOptionDef4(ServerSelector::ALL(), def);

    // Create option three and add it to first backend.
    def.reset(new OptionDefinition("three", 3, "isc", "string"));
    db1_->createUpdateOptionDef4(ServerSelector::ALL(), def);

    // Create option four and add it to second backend.
    def.reset(new OptionDefinition("four", 4, "isc", "string"));
    db2_->createUpdateOptionDef4(ServerSelector::ALL(), def);

    // Should parse and merge without error.
    ASSERT_NO_FATAL_FAILURE(configure(base_config, CONTROL_RESULT_SUCCESS, ""));

    // Verify the composite staging is correct.
    SrvConfigPtr staging_cfg = CfgMgr::instance().getStagingCfg();
    ConstCfgOptionDefPtr option_defs = staging_cfg->getCfgOptionDef();

    // Definition "one" from first backend should be there.
    OptionDefinitionPtr found_def = option_defs->get("isc", "one");
    ASSERT_TRUE(found_def);
    EXPECT_EQ(101, found_def->getCode());
    EXPECT_EQ(OptionDataType::OPT_UINT16_TYPE, found_def->getType());

    // Definition "two" from JSON config should be there.
    found_def = option_defs->get("isc", "two");
    ASSERT_TRUE(found_def);
    EXPECT_EQ(2, found_def->getCode());

    // Definition "three" from first backend should be there.
    found_def = option_defs->get("isc", "three");
    ASSERT_TRUE(found_def);
    EXPECT_EQ(3, found_def->getCode());

    // Definition "four" from first backend should not be there.
    found_def = option_defs->get("isc", "four");
    ASSERT_FALSE(found_def);
}

// This test verifies that externally configured options
// merged correctly into staging configuration.
TEST_F(Dhcp4CBTest, mergeOptions) {
    string base_config =
        "{ \n"
        "    \"option-data\": [ { \n"
        "        \"name\": \"dhcp-message\", \n"
        "        \"data\": \"0A0B0C0D\", \n"
        "        \"csv-format\": false \n"
        "     },{ \n"
        "        \"name\": \"host-name\", \n"
        "        \"data\": \"old.example.com\", \n"
        "        \"csv-format\": true \n"
        "     } \n"
        "    ], \n"
        "    \"config-control\": { \n"
        "       \"config-databases\": [ { \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db1\" \n"
        "           },{ \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db2\" \n"
        "           } \n"
        "       ] \n"
        "   } \n"
        "} \n";

    extractConfig(base_config);

    OptionDescriptorPtr opt;

    // Add host-name to the first backend.
    opt.reset(new OptionDescriptor(
              createOption<OptionString>(Option::V4, DHO_HOST_NAME,
                                         true, false, false,
                                         "new.example.com")));
    opt->space_name_ = DHCP4_OPTION_SPACE;
    db1_->createUpdateOption4(ServerSelector::ALL(), opt);

    // Add boot-file-name to the first backend.
    opt.reset(new OptionDescriptor(
              createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                         true, false, false,
                                         "my-boot-file")));
    opt->space_name_ = DHCP4_OPTION_SPACE;
    db1_->createUpdateOption4(ServerSelector::ALL(), opt);

    // Add boot-file-name to the second backend.
    opt.reset(new OptionDescriptor(
              createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                         true, false, false,
                                         "your-boot-file")));
    opt->space_name_ = DHCP4_OPTION_SPACE;
    db2_->createUpdateOption4(ServerSelector::ALL(), opt);

    // Should parse and merge without error.
    ASSERT_NO_FATAL_FAILURE(configure(base_config, CONTROL_RESULT_SUCCESS, ""));

    // Verify the composite staging is correct.
    SrvConfigPtr staging_cfg = CfgMgr::instance().getStagingCfg();

    // Option definition from JSON should be there.
    CfgOptionPtr options = staging_cfg->getCfgOption();

    // dhcp-message should come from the original config.
    OptionDescriptor found_opt =
        options->get(DHCP4_OPTION_SPACE, DHO_DHCP_MESSAGE);
    ASSERT_TRUE(found_opt.option_);
    EXPECT_EQ("0x0A0B0C0D", found_opt.option_->toHexString());

    // host-name should come from the first back end,
    // (overwriting the original).
    found_opt = options->get(DHCP4_OPTION_SPACE, DHO_HOST_NAME);
    ASSERT_TRUE(found_opt.option_);
    EXPECT_EQ("new.example.com", found_opt.option_->toString());

    // booth-file-name should come from the first back end.
    found_opt = options->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(found_opt.option_);
    EXPECT_EQ("my-boot-file", found_opt.option_->toString());
}

// This test verifies that DHCP options fetched from the config backend
// encapsulate their suboptions.
TEST_F(Dhcp4CBTest, mergeOptionsWithSuboptions) {
    string base_config =
        "{ \n"
        "    \"option-def\": [ { \n"
        "        \"name\": \"vendor-suboption-1\", \n"
        "        \"code\": 1, \n"
        "        \"type\": \"string\", \n"
        "        \"space\": \"vendor-encapsulated-options-space\" \n"
        "    }], \n"
        "    \"config-control\": { \n"
        "       \"config-databases\": [ { \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db1\" \n"
        "           },{ \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db2\" \n"
        "           } \n"
        "       ] \n"
        "   } \n"
        "} \n";

    extractConfig(base_config);

    // Create option 43 instance and store it in the database.
    OptionDescriptorPtr opt;
    opt.reset(new OptionDescriptor(
              createEmptyOption(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS,
                                true, false)));
    opt->space_name_ = DHCP4_OPTION_SPACE;
    db1_->createUpdateOption4(ServerSelector::ALL(), opt);

    // Create option 43 suboption and store it in the database.
    opt.reset(new OptionDescriptor(
              createOption<OptionString>(Option::V4, 1, true, false, false,
                                         "http://server:8080")
          )
    );
    opt->space_name_ = VENDOR_ENCAPSULATED_OPTION_SPACE;
    db1_->createUpdateOption4(ServerSelector::ALL(), opt);

    // Fetch the configuration from the config backend.
    ASSERT_NO_FATAL_FAILURE(configure(base_config, CONTROL_RESULT_SUCCESS, ""));

    auto staging_cfg = CfgMgr::instance().getStagingCfg();

    // Make sure that option 43 has been fetched.
    auto found_opt_desc = staging_cfg->getCfgOption()->
        get(DHCP4_OPTION_SPACE, DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(found_opt_desc.option_);

    // Make sure that the option 43 contains its suboption.
    auto found_subopt = found_opt_desc.option_->getOption(1);
    EXPECT_TRUE(found_subopt);
}

// This test verifies that externally configured shared-networks are
// merged correctly into staging configuration.
TEST_F(Dhcp4CBTest, mergeSharedNetworks) {
    string base_config =
        "{ \n"
        "    \"interfaces-config\": { \n"
        "        \"interfaces\": [\"*\" ] \n"
        "    }, \n"
        "    \"valid-lifetime\": 4000, \n"
        "    \"config-control\": { \n"
        "       \"config-databases\": [ { \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db1\" \n"
        "           },{ \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db2\" \n"
        "           } \n"
        "       ] \n"
        "   }, \n"
        "   \"shared-networks\": [ { \n"
        "       \"name\": \"two\" \n"
        "   }] \n"
        "} \n";

    extractConfig(base_config);

    // Make a few networks
    SharedNetwork4Ptr network1(new SharedNetwork4("one"));
    SharedNetwork4Ptr network3(new SharedNetwork4("three"));

    // Add network1 to db1 and network3 to db2
    db1_->createUpdateSharedNetwork4(ServerSelector::ALL(), network1);
    db2_->createUpdateSharedNetwork4(ServerSelector::ALL(), network3);

    // Should parse and merge without error.
    ASSERT_NO_FATAL_FAILURE(configure(base_config, CONTROL_RESULT_SUCCESS, ""));

    // Verify the composite staging is correct.  (Remember that
    // CfgMgr::instance().commit() hasn't been called)
    SrvConfigPtr staging_cfg = CfgMgr::instance().getStagingCfg();

    CfgSharedNetworks4Ptr networks = staging_cfg->getCfgSharedNetworks4();
    SharedNetwork4Ptr staged_network;

    // SharedNetwork One should have been added from db1 config
    staged_network = networks->getByName("one");
    ASSERT_TRUE(staged_network);

    // Subnet2 should have come from the json config
    staged_network = networks->getByName("two");
    ASSERT_TRUE(staged_network);

    // Subnet3, which is in db2 should not have been merged.
    // We queried db1 first and the query returned data. In
    // other words, we iterate over the backends, asking for
    // data.  We use the first data, we find.
    staged_network = networks->getByName("three");
    ASSERT_FALSE(staged_network);
}

// This test verifies that externally configured subnets are
// merged correctly into staging configuration.
TEST_F(Dhcp4CBTest, mergeSubnets) {
    string base_config =
        "{ \n"
        "    \"interfaces-config\": { \n"
        "        \"interfaces\": [\"*\" ] \n"
        "    }, \n"
        "    \"valid-lifetime\": 4000, \n"
        "    \"config-control\": { \n"
        "       \"config-databases\": [ { \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db1\" \n"
        "           },{ \n"
        "               \"type\": \"memfile\", \n"
        "               \"host\": \"db2\" \n"
        "           } \n"
        "       ] \n"
        "   }, \n"
        "   \"subnet4\": [ \n"
        "   { \n"
        "       \"id\": 2,\n"
        "       \"subnet\": \"192.0.3.0/24\" \n"
        "   } ]\n"
        "} \n";

    extractConfig(base_config);

    // Make a few subnets
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.4.0"), 26, 1, 2, 3, SubnetID(3)));

    // Add subnet1 to db1 and subnet3 to db2
    db1_->createUpdateSubnet4(ServerSelector::ALL(), subnet1);
    db2_->createUpdateSubnet4(ServerSelector::ALL(), subnet3);

    // Should parse and merge without error.
    configure(base_config, CONTROL_RESULT_SUCCESS, "");

    // Verify the composite staging is correct.  (Remember that
    // CfgMgr::instance().commit() hasn't been called)

    SrvConfigPtr staging_cfg = CfgMgr::instance().getStagingCfg();

    CfgSubnets4Ptr subnets = staging_cfg->getCfgSubnets4();
    ConstSubnet4Ptr staged_subnet;

    // Subnet1 should have been added from db1 config
    staged_subnet = subnets->getBySubnetId(1);
    ASSERT_TRUE(staged_subnet);

    // Subnet2 should have come from the json config
    staged_subnet = subnets->getBySubnetId(2);
    ASSERT_TRUE(staged_subnet);

    // Subnet3, which is in db2 should not have been merged, since it is
    // first found, first used?
    staged_subnet = subnets->getBySubnetId(3);
    ASSERT_FALSE(staged_subnet);
}

}
