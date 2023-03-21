// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet.h>
#include <process/logging_info.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::process;
using namespace isc::util;

// Those are the tests for SrvConfig storage. Right now they are minimal,
// but the number is expected to grow significantly once we migrate more
// parameters from CfgMgr storage to SrvConfig storage.

namespace {

/// @brief Derivation of the @c ConfigBase not being @c SrvConfig.
///
/// This is used to verify that the appropriate error is returned
/// when other derivation of the @c ConfigBase than @c SrvConfig
/// is used.
class NonSrvConfig : public ConfigBase { };

/// @brief Number of IPv4 and IPv6 subnets to be created for a test.
const int TEST_SUBNETS_NUM = 3;

/// @brief Test fixture class for testing configuration data storage.
class SrvConfigTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Creates IPv4 and IPv6 subnets for unit test. The number of subnets
    /// is @c TEST_SUBNETS_NUM for IPv4 and IPv6 each.
    SrvConfigTest()
        : iface_mgr_test_config_(true),
          ref_dictionary_(new ClientClassDictionary()) {

        // Disable DDNS.
        enableD2Client(false);

        // Create IPv4 subnets.
        for (int i = 0; i < TEST_SUBNETS_NUM; ++i) {
            // Default triplet carried undefined value.
            Triplet<uint32_t> def_triplet;
            // Create a collection of subnets: 192.0.X.0/24 where X is
            // 0, 1, 2 etc.
            Subnet4Ptr subnet(new Subnet4(IOAddress(0xC0000000 | (i << 2)),
                                          24, def_triplet, def_triplet,
                                          4000));
            test_subnets4_.insert(subnet);
        }
        // Create IPv6 subnets.
        IOAddress prefix("2001:db8:1::");
        for (int i = 0; i < TEST_SUBNETS_NUM; ++i) {
            // This is a base prefix. All other prefixes will be created by
            // modifying this one.
            std::vector<uint8_t> prefix_bytes = prefix.toBytes();
            // Modify 5th byte of the prefix, so 2001:db8:1::0 becomes
            // 2001:db8:2::0 etc.
            ++prefix_bytes[5];
            prefix = IOAddress::fromBytes(prefix.getFamily(), &prefix_bytes[0]);
            Subnet6Ptr subnet(new Subnet6(prefix, 64, 1000, 2000, 3000, 4000));
            test_subnets6_.insert(subnet);
        }

        // Build our reference dictionary of client classes
        ref_dictionary_->addClass("cc1", ExpressionPtr(),
                                  "", false, false, CfgOptionPtr());
        ref_dictionary_->addClass("cc2", ExpressionPtr(),
                                  "", false, false, CfgOptionPtr());
        ref_dictionary_->addClass("cc3", ExpressionPtr(),
                                  "", false, false, CfgOptionPtr());
    }


    /// @brief Destructor.
    virtual ~SrvConfigTest() {
    }

    /// @brief Convenience function which adds IPv4 subnet to the configuration.
    ///
    /// @param index Index of the subnet in the @c test_subnets4_ collection
    /// which should be added to the configuration. The configuration is stored
    /// in the @ conf_ member. This value must be lower than
    /// @c TEST_SUBNETS_NUM.
    ///
    /// @todo Until the subnets configuration is migrated from the @c CfgMgr to
    /// the @c SrvConfig object, this function adds the subnet to the
    /// @c CfgMgr. Once, the subnet configuration is held in the
    /// @c SrvConfig this function must be modified to store the subnets in
    /// the @c conf_ object.
    void addSubnet4(const unsigned int index);

    /// @brief Convenience function which adds IPv6 subnet to the configuration.
    ///
    /// @param index Index of the subnet in the @c test_subnets6_ collection
    /// which should be added to the configuration. The configuration is stored
    /// in the @ conf_ member. This value must be lower than
    /// @c TEST_SUBNETS_NUM.
    ///
    /// @todo Until the subnets configuration is migrated from the @c CfgMgr to
    /// the @c SrvConfig object, this function adds the subnet to the
    /// @c CfgMgr. Once, the subnet configuration is held in the
    /// @c SrvConfig this function must be modified to store the subnets in
    /// @c conf_ object.
    void addSubnet6(const unsigned int index);

    /// @brief Enable/disable DDNS.
    ///
    /// @param enable A boolean value indicating if the DDNS should be
    /// enabled (true) or disabled (false).
    void enableD2Client(const bool enable);

    /// @brief Stores configuration.
    SrvConfig conf_;
    /// @brief A collection of IPv4 subnets used by unit tests.
    Subnet4Collection test_subnets4_;
    /// @brief A collection of IPv6 subnets used by unit tests.
    Subnet6Collection test_subnets6_;
    /// @brief Fakes interface configuration.
    isc::dhcp::test::IfaceMgrTestConfig iface_mgr_test_config_;

    /// @brief Client class dictionary with fixed content
    ClientClassDictionaryPtr ref_dictionary_;
};

void
SrvConfigTest::addSubnet4(const unsigned int index) {
    if (index >= TEST_SUBNETS_NUM) {
        FAIL() << "Subnet index " << index << "out of range (0.."
               << TEST_SUBNETS_NUM << "): unable to add IPv4 subnet";
    }
    // std::advance is not available for this iterator.
    auto it = test_subnets4_.begin();
    for (unsigned int i = 0; i < index; ++i, ++it) {
        ASSERT_FALSE(it == test_subnets4_.end());
    }
    conf_.getCfgSubnets4()->add(*it);
}

void
SrvConfigTest::addSubnet6(const unsigned int index) {
    if (index >= TEST_SUBNETS_NUM) {
        FAIL() << "Subnet index " << index << "out of range (0.."
               << TEST_SUBNETS_NUM << "): unable to add IPv6 subnet";
    }
    // std::advance is not available for this iterator.
    auto it = test_subnets6_.begin();
    for (unsigned int i = 0; i < index; ++i, ++it) {
        ASSERT_FALSE(it == test_subnets6_.end());
    }
    conf_.getCfgSubnets6()->add(*it);
}

void
SrvConfigTest::enableD2Client(const bool enable) {
    const D2ClientConfigPtr& d2_config = conf_.getD2ClientConfig();
    ASSERT_TRUE(d2_config);
    d2_config->enableUpdates(enable);
}

// Check that by default there are no logging entries
TEST_F(SrvConfigTest, basic) {
    EXPECT_TRUE(conf_.getLoggingInfo().empty());
}

// Check that SrvConfig can store logging information.
TEST_F(SrvConfigTest, loggingInfo) {
    LoggingInfo log1;
    log1.clearDestinations();
    log1.name_ = "foo";
    log1.severity_ = isc::log::WARN;
    log1.debuglevel_ = 77;

    LoggingDestination dest;
    dest.output_ = "some-logfile.txt";
    dest.maxver_ = 5;
    dest.maxsize_ = 2097152;

    log1.destinations_.push_back(dest);

    conf_.addLoggingInfo(log1);

    EXPECT_EQ("foo", conf_.getLoggingInfo()[0].name_);
    EXPECT_EQ(isc::log::WARN, conf_.getLoggingInfo()[0].severity_);
    EXPECT_EQ(77, conf_.getLoggingInfo()[0].debuglevel_);

    EXPECT_EQ("some-logfile.txt", conf_.getLoggingInfo()[0].destinations_[0].output_);
    EXPECT_EQ(5, conf_.getLoggingInfo()[0].destinations_[0].maxver_);
    EXPECT_EQ(2097152, conf_.getLoggingInfo()[0].destinations_[0].maxsize_);
}

// Check that the configuration summary including information about the status
// of DDNS is returned.
TEST_F(SrvConfigTest, summaryDDNS) {
    EXPECT_EQ("DDNS: disabled",
              conf_.getConfigSummary(SrvConfig::CFGSEL_DDNS));

    enableD2Client(true);
    EXPECT_EQ("DDNS: enabled",
              conf_.getConfigSummary(SrvConfig::CFGSEL_DDNS));

    enableD2Client(false);
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!; DDNS: disabled",
              conf_.getConfigSummary(SrvConfig::CFGSEL_ALL));
}

// Check that the configuration summary including information about added
// subnets is returned.
TEST_F(SrvConfigTest, summarySubnets) {
    EXPECT_EQ("no config details available",
              conf_.getConfigSummary(SrvConfig::CFGSEL_NONE));

    // Initially, there are no subnets added but it should be explicitly
    // reported when we query for information about the subnets.
    EXPECT_EQ("no IPv4 subnets!; no IPv6 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));

    // If we just want information about IPv4 subnets, there should be no
    // mention of IPv6 subnets, even though there are none added.
    EXPECT_EQ("no IPv4 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET4));

    // If we just want information about IPv6 subnets, there should be no
    // mention of IPv4 subnets, even though there are none added.
    EXPECT_EQ("no IPv6 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET6));

    // Add IPv4 subnet and make sure it is reported.
    addSubnet4(0);
    EXPECT_EQ("added IPv4 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET4));
    EXPECT_EQ("added IPv4 subnets: 1; no IPv6 subnets!",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));

    // Add IPv6 subnet and make sure it is reported.
    addSubnet6(0);
    EXPECT_EQ("added IPv6 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET6));
    EXPECT_EQ("added IPv4 subnets: 1; added IPv6 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));

    // Add one more subnet and make sure the bumped value is only
    // for IPv4, but not for IPv6.
    addSubnet4(1);
    EXPECT_EQ("added IPv4 subnets: 2; added IPv6 subnets: 1",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));
    EXPECT_EQ("added IPv4 subnets: 2",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET4));

    addSubnet6(1);
    EXPECT_EQ("added IPv4 subnets: 2; added IPv6 subnets: 2",
              conf_.getConfigSummary(SrvConfig::CFGSEL_SUBNET));
}

// Verifies that we can get and set the client class dictionary
TEST_F(SrvConfigTest, classDictionaryBasics) {
    ClientClassDictionaryPtr d1;
    SrvConfig conf(32);

    // Upon construction the dictionary should be empty.
    ASSERT_TRUE(d1 = conf.getClientClassDictionary());
    EXPECT_EQ(0, d1->getClasses()->size());

    // Verify we can replace it with a new dictionary.
    ASSERT_NO_THROW(conf.setClientClassDictionary(ref_dictionary_));
    ASSERT_TRUE(d1 = conf.getClientClassDictionary());
    EXPECT_EQ(ref_dictionary_->getClasses()->size(), d1->getClasses()->size());

    // Verify const fetcher works too.
    const ClientClassDictionaryPtr cd = conf.getClientClassDictionary();
    ASSERT_TRUE(cd);
    EXPECT_EQ(ref_dictionary_->getClasses()->size(), cd->getClasses()->size());
}

// This test verifies that RFC6842 (echo client-id) compatibility may be
// configured.
TEST_F(SrvConfigTest, echoClientId) {
    SrvConfig conf;

    // Check that the default is true
    EXPECT_TRUE(conf.getEchoClientId());

    // Check that it can be modified to false
    conf.setEchoClientId(false);
    EXPECT_FALSE(conf.getEchoClientId());

    // Check that the default value can be restored
    conf.setEchoClientId(true);
    EXPECT_TRUE(conf.getEchoClientId());

    // Check the other constructor has the same default
    SrvConfig conf1(1);
    EXPECT_TRUE(conf1.getEchoClientId());
}

// This test verifies that compatibility flags are correctly managed.
TEST_F(SrvConfigTest, compatibility) {
    SrvConfig conf;

    // Check that defaults are false.
    EXPECT_FALSE(conf.getLenientOptionParsing());
    EXPECT_FALSE(conf.getIgnoreServerIdentifier());
    EXPECT_FALSE(conf.getIgnoreRAILinkSelection());
    EXPECT_FALSE(conf.getExcludeFirstLast24());

    // Check that they can be modified to true.
    conf.setLenientOptionParsing(true);
    conf.setIgnoreServerIdentifier(true);
    conf.setIgnoreRAILinkSelection(true);
    conf.setExcludeFirstLast24(true);
    EXPECT_TRUE(conf.getLenientOptionParsing());
    EXPECT_TRUE(conf.getIgnoreServerIdentifier());
    EXPECT_TRUE(conf.getIgnoreRAILinkSelection());
    EXPECT_TRUE(conf.getExcludeFirstLast24());

    // Check that default values can be restored.
    conf.setLenientOptionParsing(false);
    conf.setIgnoreServerIdentifier(false);
    conf.setIgnoreRAILinkSelection(false);
    conf.setExcludeFirstLast24(false);
    EXPECT_FALSE(conf.getLenientOptionParsing());
    EXPECT_FALSE(conf.getIgnoreServerIdentifier());
    EXPECT_FALSE(conf.getIgnoreRAILinkSelection());
    EXPECT_FALSE(conf.getExcludeFirstLast24());

    // Check the other constructor has the same default.
    SrvConfig conf1(1);
    EXPECT_FALSE(conf1.getLenientOptionParsing());
    EXPECT_FALSE(conf.getIgnoreServerIdentifier());
    EXPECT_FALSE(conf1.getIgnoreRAILinkSelection());
    EXPECT_FALSE(conf1.getExcludeFirstLast24());
}

// This test verifies that host reservations lookup first flag can be configured.
TEST_F(SrvConfigTest, reservationsLookupFirst) {
    SrvConfig conf;

    // Check that the default is false
    EXPECT_FALSE(conf.getReservationsLookupFirst());

    // Check that it can be modified to true
    conf.setReservationsLookupFirst(true);
    EXPECT_TRUE(conf.getReservationsLookupFirst());

    // Check that the default value can be restored
    conf.setReservationsLookupFirst(false);
    EXPECT_FALSE(conf.getReservationsLookupFirst());

    // Check the other constructor has the same default
    SrvConfig conf1(1);
    EXPECT_FALSE(conf1.getReservationsLookupFirst());
}

// This test checks if entire configuration can be copied and that the sequence
// number is not affected.
TEST_F(SrvConfigTest, copy) {
    // Create two configurations with different sequence numbers.
    SrvConfig conf1(32);
    SrvConfig conf2(64);

    // Set logging information for conf1.
    LoggingInfo info;
    info.name_ = "foo";
    info.severity_ = isc::log::DEBUG;
    info.debuglevel_ = 64;
    info.destinations_.push_back(LoggingDestination());

    // Set interface configuration for conf1.
    conf1.getCfgIface()->use(AF_INET, "eth0");
    conf1.addLoggingInfo(info);

    // Add option definition.
    OptionDefinitionPtr def(new OptionDefinition("option-foo", 5, "isc", "string"));
    conf1.getCfgOptionDef()->add(def);

    // Add an option.
    OptionPtr option(new Option(Option::V6, 1000, OptionBuffer(10, 0xFF)));
    conf1.getCfgOption()->add(option, true, false, DHCP6_OPTION_SPACE);

    // Add a class dictionary
    conf1.setClientClassDictionary(ref_dictionary_);

    // Make sure both configurations are different.
    ASSERT_TRUE(conf1 != conf2);

    // Copy conf1 to conf2.
    ASSERT_NO_THROW(conf1.copy(conf2));

    // Now they should be equal.
    EXPECT_TRUE(conf1 == conf2);

    // But, their sequence numbers should be unequal.
    EXPECT_FALSE(conf1.sequenceEquals(conf2));
}

// This test checks that two configurations can be compared for (in)equality.
TEST_F(SrvConfigTest, equality) {
    SrvConfig conf1(32);
    SrvConfig conf2(64);

    // Initially, both objects should be equal, even though the configuration
    // sequences are not matching.
    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by logging information.
    LoggingInfo info1;
    LoggingInfo info2;
    info1.name_ = "foo";
    info2.name_ = "bar";

    conf1.addLoggingInfo(info1);
    conf2.addLoggingInfo(info2);

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf1.addLoggingInfo(info2);
    conf2.addLoggingInfo(info1);

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by interface configuration.
    conf1.getCfgIface()->use(AF_INET, "eth0");

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf2.getCfgIface()->use(AF_INET, "eth0");

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by option definitions.
    conf1.getCfgOptionDef()->
        add(OptionDefinitionPtr(new OptionDefinition("option-foo", 123, "isc",
                                                     "uint16_t")));

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf2.getCfgOptionDef()->
        add(OptionDefinitionPtr(new OptionDefinition("option-foo", 123, "isc",
                                                     "uint16_t")));
    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Differ by option data.
    OptionPtr option(new Option(Option::V6, 1000, OptionBuffer(1, 0xFF)));
    conf1.getCfgOption()->add(option, false, false, "isc");

    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    conf2.getCfgOption()->add(option, false, false, "isc");

    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);

    // Add a class dictionary to conf1
    conf1.setClientClassDictionary(ref_dictionary_);
    EXPECT_FALSE(conf1 == conf2);
    EXPECT_TRUE(conf1 != conf2);

    // Add same class dictionary to conf2
    conf2.setClientClassDictionary(ref_dictionary_);
    EXPECT_TRUE(conf1 == conf2);
    EXPECT_FALSE(conf1 != conf2);
}

// Verifies that we can get and set configured hooks libraries
TEST_F(SrvConfigTest, hooksLibraries) {
    SrvConfig conf(32);
    isc::hooks::HooksConfig& libraries = conf.getHooksConfig();

    // Upon construction configured hooks libraries should be empty.
    EXPECT_EQ(0, libraries.get().size());

    // Verify we can update it.
    ConstElementPtr elem0;
    libraries.add("foo", elem0);
    std::string config = "{ \"library\": \"bar\" }";
    ConstElementPtr elem1 = Element::fromJSON(config);
    libraries.add("bar", elem1);
    EXPECT_EQ(2, libraries.get().size());
    EXPECT_EQ(2, conf.getHooksConfig().get().size());

    // Try to copy
    SrvConfig copied(64);
    ASSERT_TRUE(conf != copied);
    ASSERT_NO_THROW(conf.copy(copied));
    ASSERT_TRUE(conf == copied);
    EXPECT_EQ(2, copied.getHooksConfig().get().size());

    EXPECT_TRUE(copied.getHooksConfig().equal(conf.getHooksConfig()));
}

// Verifies basic functions of configured global handling.
TEST_F(SrvConfigTest, configuredGlobals) {
    // Create an instance.
    SrvConfig conf(32);

    // The map of configured globals should be empty.
    ConstCfgGlobalsPtr srv_globals = conf.getConfiguredGlobals();
    ASSERT_TRUE(srv_globals);
    ASSERT_TRUE(srv_globals->valuesMap().empty());

    // Attempting to extract globals from a non-map should throw.
    ASSERT_THROW(conf.extractConfiguredGlobals(Element::create(777)), isc::BadValue);

    // Now let's create a configuration from which to extract global scalars.
    // Extraction (currently) has no business logic, so the elements we use
    // can be arbitrary when not scalar.
    ConstElementPtr global_cfg;
    std::string global_cfg_str =
    "{\n"
    " \"comment\": \"okay\",\n" // a string
    " \"amap\": { \"not-this\":777, \"not-that\": \"poo\" },\n"
    " \"valid-lifetime\": 444,\n" // an int
    " \"alist\": [ 1, 2, 3 ],\n"
    " \"store-extended-info\": true,\n" // a bool
    " \"t1-percent\": 1.234\n" // a real
    "}\n";
    ASSERT_NO_THROW(global_cfg = Element::fromJSON(global_cfg_str));

    // Extract globals from the config.
    ASSERT_NO_THROW(conf.extractConfiguredGlobals(global_cfg));

    // Now see if the extract was correct.
    srv_globals = conf.getConfiguredGlobals();
    ASSERT_FALSE(srv_globals->valuesMap().empty());

    // Maps and lists should be excluded.
    auto globals = srv_globals->valuesMap();
    for (auto global = globals.begin(); global != globals.end(); ++global) {
        if (global->first == "comment") {
            ASSERT_EQ(Element::string, global->second->getType());
            EXPECT_EQ("okay", global->second->stringValue());
        } else if (global->first == "valid-lifetime") {
            ASSERT_EQ(Element::integer, global->second->getType());
            EXPECT_EQ(444, global->second->intValue());
        } else if (global->first == "store-extended-info") {
            ASSERT_EQ(Element::boolean, global->second->getType());
            EXPECT_TRUE(global->second->boolValue());
        } else if (global->first == "t1-percent") {
            ASSERT_EQ(Element::real, global->second->getType());
            EXPECT_EQ(1.234, global->second->doubleValue());
        } else {
            ADD_FAILURE() << "unexpected element found:" << global->first;
        }
    }

    // Verify that using getConfiguredGlobal() to fetch an individual
    // parameters works.
    ConstElementPtr global;
    // We should find global "comment".
    ASSERT_NO_THROW(global = conf.getConfiguredGlobal("comment"));
    ASSERT_TRUE(global);
    ASSERT_EQ(Element::string, global->getType());
    EXPECT_EQ("okay", global->stringValue());

    // Not finding global "not-there" should throw.
    // without throwing.
    ASSERT_THROW(conf.getConfiguredGlobal("not-there"), isc::NotFound);
}

// Verifies that the toElement method works well (tests limited to
// direct parameters)
TEST_F(SrvConfigTest, unparse) {
    SrvConfig conf(32);
    std::string header4 = "{\n\"Dhcp4\": {\n";
    std::string header6 = "{\n\"Dhcp6\": {\n";

    std::string defaults = "\"decline-probation-period\": 0,\n";
    defaults += "\"interfaces-config\": { \"interfaces\": [ ],\n";
    defaults += " \"re-detect\": false },\n";
    defaults += "\"option-def\": [ ],\n";
    defaults += "\"option-data\": [ ],\n";
    defaults += "\"expired-leases-processing\": ";
    defaults += conf.getCfgExpiration()->toElement()->str() + ",\n";
    defaults += "\"lease-database\": { \"type\": \"memfile\" },\n";
    defaults += "\"hooks-libraries\": [ ],\n";
    defaults += "\"sanity-checks\": {\n";
    defaults += "    \"lease-checks\": \"none\",\n";
    defaults += "    \"extended-info-checks\": \"fix\"\n";
    defaults += "    },\n";
    defaults += "\"dhcp-ddns\": \n";

    defaults += conf.getD2ClientConfig()->toElement()->str() + ",\n";

    std::string defaults4 = "\"shared-networks\": [ ],\n";
    defaults4 += "\"subnet4\": [ ],\n";
    defaults4 += "\"host-reservation-identifiers\": ";
    defaults4 += "[ \"hw-address\", \"duid\", \"circuit-id\", \"client-id\" ],\n";

    std::string defaults6 = "\"relay-supplied-options\": [ \"65\" ],\n";
    defaults6 += "\"shared-networks\": [ ],\n";
    defaults6 += "\"subnet6\": [ ],\n";
    defaults6 += "\"server-id\": ";
    defaults6 += conf.getCfgDUID()->toElement()->str() + ",\n";
    defaults6 += "\"host-reservation-identifiers\": ";
    defaults6 += "[ \"hw-address\", \"duid\" ],\n";
    defaults6 += "\"dhcp4o6-port\": 0,\n";
    defaults6 += "\"mac-sources\": [ \"any\" ]\n";

    std::string params = "\"echo-client-id\": true,\n";
    params += "\"dhcp4o6-port\": 0\n";
    std::string trailer = "}\n}\n";

    // Verify DHCPv4
    CfgMgr::instance().setFamily(AF_INET);
    isc::test::runToElementTest<SrvConfig>
        (header4 + defaults + defaults4 + params + trailer, conf);

    // Verify DHCPv6
    CfgMgr::instance().setFamily(AF_INET6);
    isc::test::runToElementTest<SrvConfig>
        (header6 + defaults + defaults6 + trailer, conf);

    // Verify direct non-default parameters and configured globals
    CfgMgr::instance().setFamily(AF_INET);
    conf.setEchoClientId(false);
    conf.setDhcp4o6Port(6767);
    // Add compatibility flags.
    conf.setLenientOptionParsing(true);
    conf.setIgnoreRAILinkSelection(true);
    conf.setExcludeFirstLast24(true);
    params  = "\"compatibility\": {\n";
    params += " \"lenient-option-parsing\": true,\n";
    params += " \"ignore-rai-link-selection\": true,\n";
    params += " \"exclude-first-last-24\": true\n";
    params += "},\n";
    // Add "configured globals"
    conf.addConfiguredGlobal("renew-timer", Element::create(777));
    conf.addConfiguredGlobal("comment", Element::create("bar"));
    params += "\"echo-client-id\": false,\n";
    params += "\"dhcp4o6-port\": 6767,\n";
    params += "\"renew-timer\": 777,\n";
    params += "\"comment\": \"bar\"\n";
    isc::test::runToElementTest<SrvConfig>
        (header4 + defaults + defaults4 + params + trailer, conf);

    // Verify direct non-default parameters and configured globals
    CfgMgr::instance().setFamily(AF_INET6);
    // Add compatibility flag.
    conf.setIgnoreRAILinkSelection(false);
    conf.setExcludeFirstLast24(false);
    params  = ",\"compatibility\": {\n";
    params += " \"lenient-option-parsing\": true\n";
    params += "},\n";
    // Add "configured globals"
    params += "\"dhcp4o6-port\": 6767,\n";
    params += "\"renew-timer\": 777,\n";
    params += "\"comment\": \"bar\"\n";
    isc::test::runToElementTest<SrvConfig>
        (header6 + defaults + defaults6 + params + trailer, conf);
}

// Verifies that the toElement method does not miss host reservations
TEST_F(SrvConfigTest, unparseHR) {
    // DHCPv4 version
    CfgMgr::instance().setFamily(AF_INET);
    SrvConfig conf4(32);

    // Add a plain subnet
    Triplet<uint32_t> def_triplet;
    SubnetID p_id(1);
    Subnet4Ptr psubnet4(new Subnet4(IOAddress("192.0.1.0"), 24,
                                    def_triplet, def_triplet, 4000, p_id));
    conf4.getCfgSubnets4()->add(psubnet4);

    // Add a shared network
    SharedNetwork4Ptr network4(new SharedNetwork4("frog"));
    conf4.getCfgSharedNetworks4()->add(network4);

    // Add a shared subnet
    SubnetID s_id(100);
    Subnet4Ptr ssubnet4(new Subnet4(IOAddress("192.0.2.0"), 24,
                                    def_triplet, def_triplet, 4000, s_id));
    network4->add(ssubnet4);

    // Add a v4 global host reservation to the plain subnet
    HostPtr ghost4(new Host("AA:01:02:03:04:05", "hw-address",
                            SUBNET_ID_GLOBAL, SUBNET_ID_UNUSED,
                            IOAddress("192.0.3.1")));
    conf4.getCfgHosts()->add(ghost4);

    // Add a host reservation to the plain subnet
    HostPtr phost4(new Host("00:01:02:03:04:05", "hw-address",
                            p_id, SUBNET_ID_UNUSED, IOAddress("192.0.1.1")));
    conf4.getCfgHosts()->add(phost4);

    // Add a host reservation to the shared subnet
    HostPtr shost4(new Host("00:05:04:03:02:01", "hw-address",
                            s_id, SUBNET_ID_UNUSED, IOAddress("192.0.2.1")));
    conf4.getCfgHosts()->add(shost4);

    // Unparse the config
    ConstElementPtr unparsed4 = conf4.toElement();
    ASSERT_TRUE(unparsed4);
    ASSERT_EQ(Element::map, unparsed4->getType());

    // Get Dhcp4 entry
    ConstElementPtr dhcp4;
    ASSERT_NO_THROW(dhcp4 = unparsed4->get("Dhcp4"));
    ASSERT_TRUE(dhcp4);
    ASSERT_EQ(Element::map, dhcp4->getType());

    // Get global host reservations
    ConstElementPtr check;
    ASSERT_NO_THROW(check = dhcp4->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the global host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the reserved address
    ASSERT_NO_THROW(check = check->get("ip-address"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("192.0.3.1", check->stringValue());

    // Get plain subnets
    ASSERT_NO_THROW(check = dhcp4->get("subnet4"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 1
    ConstElementPtr sub;
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(p_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the reserved address
    ASSERT_NO_THROW(check = check->get("ip-address"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("192.0.1.1", check->stringValue());

    // Get shared networks
    ASSERT_NO_THROW(check = dhcp4->get("shared-networks"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared network
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its name is "frog"
    ASSERT_NO_THROW(sub = check->get("name"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::string, sub->getType());
    EXPECT_EQ("frog", sub->stringValue());

    // Get shared subnets
    ASSERT_NO_THROW(check = check->get("subnet4"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 100
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(s_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the reserved address
    ASSERT_NO_THROW(check = check->get("ip-address"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("192.0.2.1", check->stringValue());

    // DHCPv6 version
    CfgMgr::instance().setFamily(AF_INET6);
    SrvConfig conf6(32);

    // Add a plain subnet
    Subnet6Ptr psubnet6(new Subnet6(IOAddress("2001:db8:1::"), 64,
                                    1000, 2000, 3000, 4000, p_id));
    conf6.getCfgSubnets6()->add(psubnet6);

    // Add a shared network
    SharedNetwork6Ptr network6(new SharedNetwork6("frog"));
    conf6.getCfgSharedNetworks6()->add(network6);

    // Add a shared subnet
    Subnet6Ptr ssubnet6(new Subnet6(IOAddress("2001:db8:2::"), 64,
                                    1000, 2000, 3000, 4000, s_id));
    network6->add(ssubnet6);

    // Add a v6 global host reservation
    HostPtr ghost6(new Host("ff:b2:c3:d4:e5:f6", "duid", SUBNET_ID_UNUSED,
                            SUBNET_ID_GLOBAL, IOAddress::IPV4_ZERO_ADDRESS(),
                            "global.example.org"));
    conf6.getCfgHosts()->add(ghost6);

    // Add a host reservation to the plain subnet
    HostPtr phost6(new Host("a1:b2:c3:d4:e5:f6", "duid", SUBNET_ID_UNUSED,
                            p_id, IOAddress::IPV4_ZERO_ADDRESS(),
                            "foo.example.org"));

    conf6.getCfgHosts()->add(phost6);

    // Add a host reservation to the shared subnet
    HostPtr shost6(new Host("f6:e5:d4:c3:b2:a1", "duid", SUBNET_ID_UNUSED,
                            s_id, IOAddress::IPV4_ZERO_ADDRESS(),
                            "bar.example.org"));
    conf6.getCfgHosts()->add(shost6);

    // Unparse the config
    ConstElementPtr unparsed6 = conf6.toElement();
    ASSERT_TRUE(unparsed6);
    ASSERT_EQ(Element::map, unparsed6->getType());

    // Get Dhcp6 entry
    ConstElementPtr dhcp6;
    ASSERT_NO_THROW(dhcp6 = unparsed6->get("Dhcp6"));
    ASSERT_TRUE(dhcp6);
    ASSERT_EQ(Element::map, dhcp6->getType());

    // Get global host reservations
    ASSERT_NO_THROW(check = dhcp6->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the global host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the host name
    ASSERT_NO_THROW(check = check->get("hostname"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("global.example.org", check->stringValue());

    // Get plain subnets
    ASSERT_NO_THROW(check = dhcp6->get("subnet6"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 1
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(p_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the plain host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the host name
    ASSERT_NO_THROW(check = check->get("hostname"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("foo.example.org", check->stringValue());

    // Get shared networks
    ASSERT_NO_THROW(check = dhcp6->get("shared-networks"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared network
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its name is "frog"
    ASSERT_NO_THROW(sub = check->get("name"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::string, sub->getType());
    EXPECT_EQ("frog", sub->stringValue());

    // Get shared subnets
    ASSERT_NO_THROW(check = check->get("subnet6"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared subnet
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Its ID is 100
    ASSERT_NO_THROW(sub = check->get("id"));
    ASSERT_TRUE(sub);
    ASSERT_EQ(Element::integer, sub->getType());
    EXPECT_EQ(s_id, sub->intValue());

    // Get its host reservations
    ASSERT_NO_THROW(check = check->get("reservations"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::list, check->getType());
    EXPECT_EQ(1, check->size());

    // Get the shared host reservation
    ASSERT_NO_THROW(check = check->get(0));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Check the host name
    ASSERT_NO_THROW(check = check->get("hostname"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::string, check->getType());
    EXPECT_EQ("bar.example.org", check->stringValue());
}

// Verifies that the toElement method does not miss config control info
TEST_F(SrvConfigTest, unparseConfigControlInfo4) {
    // DHCPv4 version
    CfgMgr::instance().setFamily(AF_INET);
    SrvConfig conf4(32);

    // Unparse the config
    ConstElementPtr unparsed4 = conf4.toElement();
    ASSERT_TRUE(unparsed4);
    ASSERT_EQ(Element::map, unparsed4->getType());

    // Get Dhcp4 entry
    ConstElementPtr dhcp4;
    ASSERT_NO_THROW(dhcp4 = unparsed4->get("Dhcp4"));
    ASSERT_TRUE(dhcp4);
    ASSERT_EQ(Element::map, dhcp4->getType());

    // Config control should not be present.
    ConstElementPtr check;
    ASSERT_NO_THROW(check = dhcp4->get("config-control"));
    EXPECT_FALSE(check);

    // Now let's create the info and add it to the configuration
    ConfigControlInfoPtr info(new ConfigControlInfo());
    ASSERT_NO_THROW(info->addConfigDatabase("type=mysql"));
    ASSERT_NO_THROW(conf4.setConfigControlInfo(info));

    // Unparse the config again
    unparsed4 = conf4.toElement();
    ASSERT_NO_THROW(dhcp4 = unparsed4->get("Dhcp4"));
    ASSERT_TRUE(dhcp4);
    ASSERT_EQ(Element::map, dhcp4->getType());

    // Config control should be present.
    ASSERT_NO_THROW(check = dhcp4->get("config-control"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Unparse the info object and compare its elements to
    // that in unparsed config.  They should be equal.
    ElementPtr info_elem = info->toElement();
    EXPECT_TRUE(info_elem->equals(*check));
}

// Verifies that the toElement method does not miss config control info
TEST_F(SrvConfigTest, unparseConfigControlInfo6) {
    // DHCPv6 version
    CfgMgr::instance().setFamily(AF_INET6);
    SrvConfig conf6(32);

    // Unparse the config
    ConstElementPtr unparsed6 = conf6.toElement();
    ASSERT_TRUE(unparsed6);
    ASSERT_EQ(Element::map, unparsed6->getType());

    // Get Dhcp4 entry
    ConstElementPtr dhcp6;
    ASSERT_NO_THROW(dhcp6 = unparsed6->get("Dhcp6"));
    ASSERT_TRUE(dhcp6);
    ASSERT_EQ(Element::map, dhcp6->getType());

    // Config control should not be present.
    ConstElementPtr check;
    ASSERT_NO_THROW(check = dhcp6->get("config-control"));
    EXPECT_FALSE(check);

    // Now let's create the info and add it to the configuration
    ConfigControlInfoPtr info(new ConfigControlInfo());
    ASSERT_NO_THROW(info->addConfigDatabase("type=mysql"));
    ASSERT_NO_THROW(conf6.setConfigControlInfo(info));

    // Unparse the config again
    unparsed6 = conf6.toElement();
    ASSERT_NO_THROW(dhcp6 = unparsed6->get("Dhcp6"));
    ASSERT_TRUE(dhcp6);
    ASSERT_EQ(Element::map, dhcp6->getType());

    // Config control should be present.
    ASSERT_NO_THROW(check = dhcp6->get("config-control"));
    ASSERT_TRUE(check);
    ASSERT_EQ(Element::map, check->getType());

    // Unparse the info object and compare its elements to
    // that in unparsed config.  They should be equal.
    ElementPtr info_elem = info->toElement();
    EXPECT_TRUE(info_elem->equals(*check));
}

// Verifies that exception is thrown when instead of SrvConfig
// another derivation of ConfigBase is used in the call to
// merge.
TEST_F(SrvConfigTest, mergeBadCast) {
    SrvConfig srv_config;
    NonSrvConfig non_srv_config;
    ASSERT_THROW(srv_config.merge(non_srv_config), isc::InvalidOperation);
}

// This test verifies that globals from one SrvConfig
// can be merged into another. It verifies that values
// in the from-config override those in to-config which
// override those in GLOBAL4_DEFAULTS.
TEST_F(SrvConfigTest, mergeGlobals4) {
    // Set the family we're working with.
    CfgMgr::instance().setFamily(AF_INET);

    // Let's create the "existing" config we will merge into.
    SrvConfig cfg_to;

    // Set some explicit values.
    cfg_to.setDeclinePeriod(100);
    cfg_to.setEchoClientId(false);
    cfg_to.setDhcp4o6Port(777);
    cfg_to.setServerTag("not_this_server");

    // Add some configured globals
    cfg_to.addConfiguredGlobal("decline-probation-period", Element::create(300));
    cfg_to.addConfiguredGlobal("dhcp4o6-port", Element::create(888));

    // Now we'll create the config we'll merge from.
    SrvConfig cfg_from;

    // Set some explicit values. None of these should be preserved.
    cfg_from.setDeclinePeriod(200);
    cfg_from.setEchoClientId(true);
    cfg_from.setDhcp4o6Port(888);
    cfg_from.setServerTag("nor_this_server");
    cfg_from.setReservationsLookupFirst(true);

    // Add a configured global ip-reservations-unique. It should be populated
    // to the CfgDbAccess and CfgHosts.
    cfg_from.addConfiguredGlobal("ip-reservations-unique", Element::create(false));

    // Add some configured globals:
    cfg_to.addConfiguredGlobal("dhcp4o6-port", Element::create(999));
    cfg_to.addConfiguredGlobal("server-tag", Element::create("use_this_server"));
    cfg_to.addConfiguredGlobal("reservations-lookup-first", Element::create(true));

    // Now let's merge.
    ASSERT_NO_THROW(cfg_to.merge(cfg_from));

    // Make sure the explicit values are set correctly.

    // decline-probation-period should be the "to" configured value.
    EXPECT_EQ(300, cfg_to.getDeclinePeriod());

    // echo-client-id should be the preserved "to" member value.
    EXPECT_FALSE(cfg_to.getEchoClientId());

    //  dhcp4o6-port should be the "from" configured value.
    EXPECT_EQ(999, cfg_to.getDhcp4o6Port());

    //  server-tag port should be the "from" configured value.
    EXPECT_EQ("use_this_server", cfg_to.getServerTag().get());

    //  reservations-lookup-first should be the "from" configured value.
    EXPECT_TRUE(cfg_to.getReservationsLookupFirst());

    // ip-reservations-unique
    EXPECT_FALSE(cfg_to.getCfgDbAccess()->getIPReservationsUnique());

    // Next we check the explicitly "configured" globals.
    // The list should be all of the "to" + "from", with the
    // latter overwriting the former.
    std::string exp_globals =
        "{ \n"
        "   \"decline-probation-period\": 300,  \n"
        "   \"dhcp4o6-port\": 999,  \n"
        "   \"ip-reservations-unique\": false,  \n"
        "   \"server-tag\": \"use_this_server\",  \n"
        "   \"reservations-lookup-first\": true"
        "} \n";

    ConstElementPtr expected_globals;
    ASSERT_NO_THROW(expected_globals = Element::fromJSON(exp_globals))
                    << "exp_globals didn't parse, test is broken";

    EXPECT_TRUE(isEquivalent(expected_globals,
                             cfg_to.getConfiguredGlobals()->toElement()));
}

// This test verifies that globals from one SrvConfig
// can be merged into another. It verifies that values
// in the from-config override those in to-config which
// override those in GLOBAL6_DEFAULTS.
TEST_F(SrvConfigTest, mergeGlobals6) {
    // Set the family we're working with.
    CfgMgr::instance().setFamily(AF_INET6);

    // Let's create the "existing" config we will merge into.
    SrvConfig cfg_to;

    // Set some explicit values.
    cfg_to.setDeclinePeriod(100);
    cfg_to.setDhcp4o6Port(777);
    cfg_to.setServerTag("not_this_server");

    // Add some configured globals
    cfg_to.addConfiguredGlobal("decline-probation-period", Element::create(300));
    cfg_to.addConfiguredGlobal("dhcp4o6-port", Element::create(888));

    // Now we'll create the config we'll merge from.
    SrvConfig cfg_from;

    // Set some explicit values. None of these should be preserved.
    cfg_from.setDeclinePeriod(200);
    cfg_from.setEchoClientId(true);
    cfg_from.setDhcp4o6Port(888);
    cfg_from.setServerTag("nor_this_server");
    cfg_from.setReservationsLookupFirst(true);

    // Add a configured global ip-reservations-unique. It should be populated
    // to the CfgDbAccess and CfgHosts.
    cfg_from.addConfiguredGlobal("ip-reservations-unique", Element::create(false));

    // Add some configured globals:
    cfg_to.addConfiguredGlobal("dhcp4o6-port", Element::create(999));
    cfg_to.addConfiguredGlobal("server-tag", Element::create("use_this_server"));
    cfg_to.addConfiguredGlobal("reservations-lookup-first", Element::create(true));

    // Now let's merge.
    ASSERT_NO_THROW(cfg_to.merge(cfg_from));

    // Make sure the explicit values are set correctly.

    // decline-probation-period should be the "to" configured value.
    EXPECT_EQ(300, cfg_to.getDeclinePeriod());

    //  dhcp4o6-port should be the "from" configured value.
    EXPECT_EQ(999, cfg_to.getDhcp4o6Port());

    //  server-tag port should be the "from" configured value.
    EXPECT_EQ("use_this_server", cfg_to.getServerTag().get());

    //  reservations-lookup-first should be the "from" configured value.
    EXPECT_TRUE(cfg_to.getReservationsLookupFirst());

    // ip-reservations-unique
    EXPECT_FALSE(cfg_to.getCfgDbAccess()->getIPReservationsUnique());

    // Next we check the explicitly "configured" globals.
    // The list should be all of the "to" + "from", with the
    // latter overwriting the former.
    std::string exp_globals =
        "{ \n"
        "   \"decline-probation-period\": 300,  \n"
        "   \"dhcp4o6-port\": 999,  \n"
        "   \"ip-reservations-unique\": false,  \n"
        "   \"server-tag\": \"use_this_server\",  \n"
        "   \"reservations-lookup-first\": true"
        "} \n";

    ConstElementPtr expected_globals;
    ASSERT_NO_THROW(expected_globals = Element::fromJSON(exp_globals))
                    << "exp_globals didn't parse, test is broken";

    EXPECT_TRUE(isEquivalent(expected_globals,
                             cfg_to.getConfiguredGlobals()->toElement()));
}

// This test verifies that new list of client classes replaces and old list
// when server configuration is merged.
TEST_F(SrvConfigTest, mergeClientClasses) {
    // Let's create the "existing" config we will merge into.
    SrvConfig cfg_to;

    auto expression = boost::make_shared<Expression>();
    auto client_class = boost::make_shared<ClientClassDef>("foo", expression);
    cfg_to.getClientClassDictionary()->addClass(client_class);

    client_class = boost::make_shared<ClientClassDef>("bar", expression);
    cfg_to.getClientClassDictionary()->addClass(client_class);

    // Now we'll create the config we'll merge from.
    SrvConfig cfg_from;
    client_class = boost::make_shared<ClientClassDef>("baz", expression);
    cfg_from.getClientClassDictionary()->addClass(client_class);

    client_class = boost::make_shared<ClientClassDef>("abc", expression);
    cfg_from.getClientClassDictionary()->addClass(client_class);

    ASSERT_NO_THROW(cfg_to.merge(cfg_from));

    // The old classes should be replaced with new classes.
    EXPECT_FALSE(cfg_to.getClientClassDictionary()->findClass("foo"));
    EXPECT_FALSE(cfg_to.getClientClassDictionary()->findClass("bar"));
    EXPECT_TRUE(cfg_to.getClientClassDictionary()->findClass("baz"));
    EXPECT_TRUE(cfg_to.getClientClassDictionary()->findClass("abc"));
}

// This test verifies that client classes are not modified if the merged
// list of classes is empty.
TEST_F(SrvConfigTest, mergeEmptyClientClasses) {
    // Let's create the "existing" config we will merge into.
    SrvConfig cfg_to;

    auto expression = boost::make_shared<Expression>();
    auto client_class = boost::make_shared<ClientClassDef>("foo", expression);
    cfg_to.getClientClassDictionary()->addClass(client_class);

    client_class = boost::make_shared<ClientClassDef>("bar", expression);
    cfg_to.getClientClassDictionary()->addClass(client_class);

    // Now we'll create the config we'll merge from.
    SrvConfig cfg_from;

    ASSERT_NO_THROW(cfg_to.merge(cfg_from));

    // Empty list of classes should not replace an existing list.
    EXPECT_TRUE(cfg_to.getClientClassDictionary()->findClass("foo"));
    EXPECT_TRUE(cfg_to.getClientClassDictionary()->findClass("bar"));
}

// Validates SrvConfig::moveDdnsParams by ensuring that deprecated dhcp-ddns
// parameters are:
// 1. Translated to their global counterparts if they do not exist globally
// 2. Removed from the dhcp-ddns element
TEST_F(SrvConfigTest, moveDdnsParamsTest) {
    DdnsParamsPtr params;

    CfgMgr::instance().setFamily(AF_INET);

    struct Scenario {
        std::string description;
        std::string input_cfg;
        std::string exp_cfg;
    };

    std::vector<Scenario> scenarios {
        {
            "scenario 1, move with no global conflicts",
            // input_cfg
            "{\n"
            "   \"dhcp-ddns\": {\n"
            "       \"enable-updates\": true, \n"
            "       \"server-ip\" : \"192.0.2.0\",\n"
            "       \"server-port\" : 3432,\n"
            "       \"sender-ip\" : \"192.0.2.1\",\n"
            "       \"sender-port\" : 3433,\n"
            "       \"max-queue-size\" : 2048,\n"
            "       \"ncr-protocol\" : \"UDP\",\n"
            "       \"ncr-format\" : \"JSON\",\n"
            "       \"user-context\": { \"foo\": \"bar\" },\n"
            "       \"override-no-update\": true,\n"
            "       \"override-client-update\": false,\n"
            "       \"replace-client-name\": \"always\",\n"
            "       \"generated-prefix\": \"prefix\",\n"
            "       \"qualifying-suffix\": \"suffix.com.\",\n"
            "       \"hostname-char-set\": \"[^A-Z]\",\n"
            "       \"hostname-char-replacement\": \"x\"\n"
            "   }\n"
            "}\n",
            // exp_cfg
            "{\n"
            "   \"dhcp-ddns\": {\n"
            "       \"enable-updates\": true, \n"
            "       \"server-ip\" : \"192.0.2.0\",\n"
            "       \"server-port\" : 3432,\n"
            "       \"sender-ip\" : \"192.0.2.1\",\n"
            "       \"sender-port\" : 3433,\n"
            "       \"max-queue-size\" : 2048,\n"
            "       \"ncr-protocol\" : \"UDP\",\n"
            "       \"ncr-format\" : \"JSON\",\n"
            "       \"user-context\": { \"foo\": \"bar\" }\n"
            "   },\n"
            "   \"ddns-override-no-update\": true,\n"
            "   \"ddns-override-client-update\": false,\n"
            "   \"ddns-replace-client-name\": \"always\",\n"
            "   \"ddns-generated-prefix\": \"prefix\",\n"
            "   \"ddns-qualifying-suffix\": \"suffix.com.\",\n"
            "   \"hostname-char-set\": \"[^A-Z]\",\n"
            "   \"hostname-char-replacement\": \"x\"\n"
            "}\n"
        },
        {
            "scenario 2, globals already exist for all movable params",
            // input_cfg
            "{\n"
            "   \"dhcp-ddns\" : {\n"
            "       \"enable-updates\": true, \n"
            "       \"override-no-update\": true,\n"
            "       \"override-client-update\": true,\n"
            "       \"replace-client-name\": \"always\",\n"
            "       \"generated-prefix\": \"prefix\",\n"
            "       \"qualifying-suffix\": \"suffix.com.\",\n"
            "       \"hostname-char-set\": \"[^A-Z]\",\n"
            "       \"hostname-char-replacement\": \"x\"\n"
            "   },\n"
            "   \"ddns-override-no-update\": false,\n"
            "   \"ddns-override-client-update\": false,\n"
            "   \"ddns-replace-client-name\": \"when-present\",\n"
            "   \"ddns-generated-prefix\": \"org_prefix\",\n"
            "   \"ddns-qualifying-suffix\": \"org_suffix.com.\",\n"
            "   \"hostname-char-set\": \"[^a-z]\",\n"
            "   \"hostname-char-replacement\": \"y\"\n"
            "}\n",
            // exp_cfg
            "{\n"
            "   \"dhcp-ddns\" : {\n"
            "       \"enable-updates\": true\n"
            "   },\n"
            "   \"ddns-override-no-update\": false,\n"
            "   \"ddns-override-client-update\": false,\n"
            "   \"ddns-replace-client-name\": \"when-present\",\n"
            "   \"ddns-generated-prefix\": \"org_prefix\",\n"
            "   \"ddns-qualifying-suffix\": \"org_suffix.com.\",\n"
            "   \"hostname-char-set\": \"[^a-z]\",\n"
            "   \"hostname-char-replacement\": \"y\"\n"
            "}\n"
        },
        {
            "scenario 3, nothing to move",
            // input_cfg
            "{\n"
            "   \"dhcp-ddns\" : {\n"
            "       \"enable-updates\": true, \n"
            "       \"server-ip\" : \"192.0.2.0\",\n"
            "       \"server-port\" : 3432,\n"
            "       \"sender-ip\" : \"192.0.2.1\"\n"
            "   }\n"
            "}\n",
            // exp_output
            "{\n"
            "   \"dhcp-ddns\" : {\n"
            "       \"enable-updates\": true, \n"
            "       \"server-ip\" : \"192.0.2.0\",\n"
            "       \"server-port\" : 3432,\n"
            "       \"sender-ip\" : \"192.0.2.1\"\n"
            "   }\n"
            "}\n"
        }
    };

    for (auto scenario : scenarios) {
        SrvConfig conf(32);
        ElementPtr input_cfg;
        ConstElementPtr exp_cfg;
        {
            SCOPED_TRACE(scenario.description);
            // Parse the input cfg into a mutable Element map.
            ASSERT_NO_THROW(input_cfg = boost::const_pointer_cast<Element>
                            (Element::fromJSON(scenario.input_cfg)))
                            << "input_cfg didn't parse, test is broken";

            // Parse the expected cfg into an Element map.
            ASSERT_NO_THROW(exp_cfg = Element::fromJSON(scenario.exp_cfg))
                            << "exp_cfg didn't parse, test is broken";

            // Now call moveDdnsParams.
            ASSERT_NO_THROW(SrvConfig::moveDdnsParams(input_cfg));

            // Make sure the resultant configuration is as expected.
            EXPECT_TRUE(input_cfg->equals(*exp_cfg));
        }
    }
}

// Verifies that the scoped values for DDNS parameters can be fetched
// for a given Subnet4.
TEST_F(SrvConfigTest, getDdnsParamsTest4) {
    DdnsParamsPtr params;

    CfgMgr::instance().setFamily(AF_INET);
    SrvConfig conf(32);

    // This disables D2 connectivity. When it is false, updates
    // are off at all scopes, regardless of ddns-send-updates values.
    enableD2Client(false);

    // Disable sending updates globally.
    conf.addConfiguredGlobal("ddns-send-updates", Element::create(false));
    // Configure global host sanitizing.
    conf.addConfiguredGlobal("hostname-char-set", Element::create("[^A-Z]"));
    conf.addConfiguredGlobal("hostname-char-replacement", Element::create("x"));
    // Enable conflict resolution globally.
    conf.addConfiguredGlobal("ddns-use-conflict-resolution", Element::create(true));
    // Configure TTL percent globally.
    conf.addConfiguredGlobal("ddns-ttl-percent", Element::create(20.0));

    // Add a plain subnet
    Triplet<uint32_t> def_triplet;
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.1.0"), 24,
                                   def_triplet, def_triplet, 4000, SubnetID(1)));
    // In order to take advantage of the dynamic inheritance of global
    // parameters to a subnet we need to set a callback function for each
    // subnet to allow for fetching global parameters.
    subnet1->setFetchGlobalsFn([conf]() -> ConstCfgGlobalsPtr {
        return (conf.getConfiguredGlobals());
    });

    conf.getCfgSubnets4()->add(subnet1);

    // Add a shared network
    SharedNetwork4Ptr frognet(new SharedNetwork4("frog"));
    conf.getCfgSharedNetworks4()->add(frognet);

    // Add a shared subnet
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24,
                                   def_triplet, def_triplet, 4000, SubnetID(2)));

    // In order to take advantage of the dynamic inheritance of global
    // parameters to a subnet we need to set a callback function for each
    // subnet to allow for fetching global parameters.
    subnet2->setFetchGlobalsFn([conf]() -> ConstCfgGlobalsPtr {
        return (conf.getConfiguredGlobals());
    });

    frognet->add(subnet2);
    subnet2->setDdnsSendUpdates(true);
    subnet2->setDdnsOverrideNoUpdate(true);
    subnet2->setDdnsOverrideClientUpdate(true);
    subnet2->setDdnsReplaceClientNameMode(D2ClientConfig::RCM_ALWAYS);
    subnet2->setDdnsGeneratedPrefix("prefix");
    subnet2->setDdnsQualifyingSuffix("example.com.");
    subnet2->setHostnameCharSet("");
    subnet2->setDdnsUpdateOnRenew(true);
    subnet2->setDdnsUseConflictResolution(false);
    subnet2->setDdnsTtlPercent(Optional<double>(40.0));

    // Get DDNS params for subnet1.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet1));

    // Verify subnet1 values are right. Note, updates should be disabled.
    EXPECT_FALSE(params->getEnableUpdates());
    EXPECT_FALSE(params->getOverrideNoUpdate());
    EXPECT_FALSE(params->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, params->getReplaceClientNameMode());
    EXPECT_TRUE(params->getGeneratedPrefix().empty());
    EXPECT_TRUE(params->getQualifyingSuffix().empty());
    EXPECT_EQ("[^A-Z]", params->getHostnameCharSet());
    EXPECT_EQ("x", params->getHostnameCharReplacement());
    EXPECT_FALSE(params->getUpdateOnRenew());
    EXPECT_TRUE(params->getUseConflictResolution());
    EXPECT_FALSE(params->getTtlPercent().unspecified());
    EXPECT_EQ(20.0, params->getTtlPercent().get());

    // We inherited a non-blank hostname_char_set so we
    // should get a sanitizer instance.
    isc::util::str::StringSanitizerPtr sanitizer;
    ASSERT_NO_THROW(sanitizer = params->getHostnameSanitizer());
    EXPECT_TRUE(sanitizer);

    // Get DDNS params for subnet2.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet2));

    // Verify subnet2 values are right. Note, updates should be disabled,
    // because D2Client is disabled.
    EXPECT_FALSE(params->getEnableUpdates());
    EXPECT_TRUE(params->getOverrideNoUpdate());
    EXPECT_TRUE(params->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_ALWAYS, params->getReplaceClientNameMode());
    EXPECT_EQ("prefix", params->getGeneratedPrefix());
    EXPECT_EQ("example.com.", params->getQualifyingSuffix());
    EXPECT_EQ("", params->getHostnameCharSet());
    EXPECT_EQ("x", params->getHostnameCharReplacement());
    EXPECT_TRUE(params->getUpdateOnRenew());
    EXPECT_FALSE(params->getUseConflictResolution());
    EXPECT_FALSE(params->getTtlPercent().unspecified());
    EXPECT_EQ(40.0, params->getTtlPercent().get());

    // We have a blank hostname-char-set so we should not get a sanitizer instance.
    ASSERT_NO_THROW(sanitizer = params->getHostnameSanitizer());
    ASSERT_FALSE(sanitizer);

    // Enable D2Client.
    enableD2Client(true);

    // Make sure subnet1 updates are still disabled.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet1));
    EXPECT_FALSE(params->getEnableUpdates());

    // Make sure subnet2 updates are now enabled.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet2));
    EXPECT_TRUE(params->getEnableUpdates());

    // Enable sending updates globally.  This should inherit down subnet1.
    conf.addConfiguredGlobal("ddns-send-updates", Element::create(true));

    // Make sure subnet1 updates are now enabled.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet1));
    EXPECT_TRUE(params->getEnableUpdates());

    subnet1->setFetchGlobalsFn([]() -> ConstCfgGlobalsPtr {
        return (ConstCfgGlobalsPtr());
    });

    subnet2->setFetchGlobalsFn([]() -> ConstCfgGlobalsPtr {
        return (ConstCfgGlobalsPtr());
    });
}

// Verifies that the fallback values for DDNS parameters when
// no Subnet4 has been selected.  In theory, we should never want
// these values without a selected subnet.
TEST_F(SrvConfigTest, getDdnsParamsNoSubnetTest4) {
    DdnsParamsPtr params;

    CfgMgr::instance().setFamily(AF_INET);
    SrvConfig conf(32);

    // Enable D2 connectivity.
    enableD2Client(true);

    // Give all of the parameters a global value.
    conf.addConfiguredGlobal("ddns-send-updates", Element::create(true));
    conf.addConfiguredGlobal("ddns-override-no-update", Element::create(true));
    conf.addConfiguredGlobal("ddns-override-client-update", Element::create(true));
    conf.addConfiguredGlobal("ddns-replace-client-name", Element::create("always"));
    conf.addConfiguredGlobal("ddns-generated-prefix", Element::create("some_prefix"));
    conf.addConfiguredGlobal("ddns-qualifying-suffix", Element::create("example.com"));
    conf.addConfiguredGlobal("hostname-char-set", Element::create("[^A-Z]"));
    conf.addConfiguredGlobal("hostname-char-replacement", Element::create("x"));
    conf.addConfiguredGlobal("ddns-update-on-renew", Element::create(true));
    conf.addConfiguredGlobal("ddns-use-conflict-resolution", Element::create(false));
    conf.addConfiguredGlobal("ddns-ttl-percent", Element::create(77.0));

    // Get DDNS params for no subnet.
    Subnet4Ptr subnet4;
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet4));

    // Verify fallback values are right. Note, updates should be disabled.
    EXPECT_FALSE(params->getEnableUpdates());
    EXPECT_FALSE(params->getOverrideNoUpdate());
    EXPECT_FALSE(params->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, params->getReplaceClientNameMode());
    EXPECT_TRUE(params->getGeneratedPrefix().empty());
    EXPECT_TRUE(params->getQualifyingSuffix().empty());
    EXPECT_TRUE(params->getHostnameCharSet().empty());
    EXPECT_TRUE(params->getHostnameCharReplacement().empty());
    EXPECT_FALSE(params->getUpdateOnRenew());
    EXPECT_TRUE(params->getUseConflictResolution());
    EXPECT_TRUE(params->getTtlPercent().unspecified());
}

// Verifies that the scoped values for DDNS parameters can be fetched
// for a given Subnet6.
TEST_F(SrvConfigTest, getDdnsParamsTest6) {
    DdnsParamsPtr params;

    CfgMgr::instance().setFamily(AF_INET6);
    SrvConfig conf(32);

    // This disables D2 connectivity. When it is false, updates
    // are off at all scopes, regardless of ddns-send-updates values.
    enableD2Client(false);

    // Disable sending updates globally.
    conf.addConfiguredGlobal("ddns-send-updates", Element::create(false));
    // Configure global host sanitizing.
    conf.addConfiguredGlobal("hostname-char-set", Element::create("[^A-Z]"));
    conf.addConfiguredGlobal("hostname-char-replacement", Element::create("x"));
    // Enable conflict resolution globally.
    conf.addConfiguredGlobal("ddns-use-conflict-resolution", Element::create(true));
    // Configure TTL percent globally.
    conf.addConfiguredGlobal("ddns-ttl-percent", Element::create(25.0));

    // Add a plain subnet
    Triplet<uint32_t> def_triplet;
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 64,
                                   1000, 2000, 3000, 4000, SubnetID(1)));
    // In order to take advantage of the dynamic inheritance of global
    // parameters to a subnet we need to set a callback function for each
    // subnet to allow for fetching global parameters.
    subnet1->setFetchGlobalsFn([conf]() -> ConstCfgGlobalsPtr {
        return (conf.getConfiguredGlobals());
    });

    conf.getCfgSubnets6()->add(subnet1);

    // Add a shared network
    SharedNetwork6Ptr frognet(new SharedNetwork6("frog"));
    conf.getCfgSharedNetworks6()->add(frognet);

    // Add a shared subnet
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 64,
                                   1000, 2000, 3000, 4000, SubnetID(2)));

    // In order to take advantage of the dynamic inheritance of global
    // parameters to a subnet we need to set a callback function for each
    // subnet to allow for fetching global parameters.
    subnet2->setFetchGlobalsFn([conf]() -> ConstCfgGlobalsPtr {
        return (conf.getConfiguredGlobals());
    });

    frognet->add(subnet2);
    subnet2->setDdnsSendUpdates(true);
    subnet2->setDdnsOverrideNoUpdate(true);
    subnet2->setDdnsOverrideClientUpdate(true);
    subnet2->setDdnsReplaceClientNameMode(D2ClientConfig::RCM_ALWAYS);
    subnet2->setDdnsGeneratedPrefix("prefix");
    subnet2->setDdnsQualifyingSuffix("example.com.");
    subnet2->setHostnameCharSet("");
    subnet2->setDdnsUpdateOnRenew(true);
    subnet2->setDdnsUseConflictResolution(false);
    subnet2->setDdnsTtlPercent(Optional<double>(45.0));

    // Get DDNS params for subnet1.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet1));

    // Verify subnet1 values are right. Note, updates should be disabled.
    EXPECT_FALSE(params->getEnableUpdates());
    EXPECT_FALSE(params->getOverrideNoUpdate());
    EXPECT_FALSE(params->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, params->getReplaceClientNameMode());
    EXPECT_TRUE(params->getGeneratedPrefix().empty());
    EXPECT_TRUE(params->getQualifyingSuffix().empty());
    EXPECT_EQ("[^A-Z]", params->getHostnameCharSet());
    EXPECT_EQ("x", params->getHostnameCharReplacement());
    EXPECT_FALSE(params->getUpdateOnRenew());
    EXPECT_TRUE(params->getUseConflictResolution());
    EXPECT_FALSE(params->getTtlPercent().unspecified());
    EXPECT_EQ(25.0, params->getTtlPercent().get());

    // We inherited a non-blank hostname_char_set so we
    // should get a sanitizer instance.
    isc::util::str::StringSanitizerPtr sanitizer;
    ASSERT_NO_THROW(sanitizer = params->getHostnameSanitizer());
    EXPECT_TRUE(sanitizer);

    // Get DDNS params for subnet2.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet2));

    // Verify subnet2 values are right. Note, updates should be disabled,
    // because D2Client is disabled.
    EXPECT_FALSE(params->getEnableUpdates());
    EXPECT_TRUE(params->getOverrideNoUpdate());
    EXPECT_TRUE(params->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_ALWAYS, params->getReplaceClientNameMode());
    EXPECT_EQ("prefix", params->getGeneratedPrefix());
    EXPECT_EQ("example.com.", params->getQualifyingSuffix());
    EXPECT_EQ("", params->getHostnameCharSet());
    EXPECT_EQ("x", params->getHostnameCharReplacement());
    EXPECT_TRUE(params->getUpdateOnRenew());
    EXPECT_FALSE(params->getUseConflictResolution());
    EXPECT_FALSE(params->getTtlPercent().unspecified());
    EXPECT_EQ(45.0, params->getTtlPercent().get());

    // We have a blank hostname-char-set so we should not get a sanitizer instance.
    ASSERT_NO_THROW(sanitizer = params->getHostnameSanitizer());
    ASSERT_FALSE(sanitizer);

    // Enable D2Client.
    enableD2Client(true);

    // Make sure subnet1 updates are still disabled.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet1));
    EXPECT_FALSE(params->getEnableUpdates());

    // Make sure subnet2 updates are now enabled.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet2));
    EXPECT_TRUE(params->getEnableUpdates());

    // Enable sending updates globally.  This should inherit down subnet1.
    conf.addConfiguredGlobal("ddns-send-updates", Element::create(true));

    // Make sure subnet1 updates are now enabled.
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet1));
    EXPECT_TRUE(params->getEnableUpdates());

    subnet1->setFetchGlobalsFn([]() -> ConstCfgGlobalsPtr {
        return (ConstCfgGlobalsPtr());
    });

    subnet2->setFetchGlobalsFn([]() -> ConstCfgGlobalsPtr {
        return (ConstCfgGlobalsPtr());
    });
}

// Verifies that the fallback values for DDNS parameters when
// no Subnet6 has been selected.  In theory, we should never want
// these values without a selected subnet.
TEST_F(SrvConfigTest, getDdnsParamsNoSubnetTest6) {
    DdnsParamsPtr params;

    CfgMgr::instance().setFamily(AF_INET6);
    SrvConfig conf(32);

    // Enable D2 connectivity.
    enableD2Client(true);

    // Give all of the parameters a global value.
    conf.addConfiguredGlobal("ddns-send-updates", Element::create(true));
    conf.addConfiguredGlobal("ddns-override-no-update", Element::create(true));
    conf.addConfiguredGlobal("ddns-override-client-update", Element::create(true));
    conf.addConfiguredGlobal("ddns-replace-client-name", Element::create("always"));
    conf.addConfiguredGlobal("ddns-generated-prefix", Element::create("some_prefix"));
    conf.addConfiguredGlobal("ddns-qualifying-suffix", Element::create("example.com"));
    conf.addConfiguredGlobal("hostname-char-set", Element::create("[^A-Z]"));
    conf.addConfiguredGlobal("hostname-char-replacement", Element::create("x"));
    conf.addConfiguredGlobal("ddns-update-on-renew", Element::create(true));
    conf.addConfiguredGlobal("ddns-use-conflict-resolution", Element::create(false));
    conf.addConfiguredGlobal("ddns-ttl-percent", Element::create(77.0));

    // Get DDNS params for no subnet.
    Subnet6Ptr subnet6;
    ASSERT_NO_THROW(params = conf_.getDdnsParams(subnet6));

    // Verify fallback values are right. Note, updates should be disabled.
    EXPECT_FALSE(params->getEnableUpdates());
    EXPECT_FALSE(params->getOverrideNoUpdate());
    EXPECT_FALSE(params->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, params->getReplaceClientNameMode());
    EXPECT_TRUE(params->getGeneratedPrefix().empty());
    EXPECT_TRUE(params->getQualifyingSuffix().empty());
    EXPECT_TRUE(params->getHostnameCharSet().empty());
    EXPECT_TRUE(params->getHostnameCharReplacement().empty());
    EXPECT_FALSE(params->getUpdateOnRenew());
    EXPECT_TRUE(params->getUseConflictResolution());
    EXPECT_TRUE(params->getTtlPercent().unspecified());
}

// Verifies that adding multi threading settings works
TEST_F(SrvConfigTest, multiThreadingSettings) {
    SrvConfig conf(32);
    ElementPtr param = Element::createMap();
    param->set("enable-multi-threading", Element::create(true));
    conf.setDHCPMultiThreading(param);
    EXPECT_TRUE(isEquivalent(param, conf.getDHCPMultiThreading()));
}

// Verifies that sanityChecksLifetime works as expected.
TEST_F(SrvConfigTest, sanityChecksLifetime) {
    // First the overload checking the current config.
    // Note that lifetimes have a default so some cases here should not happen.
    {
        SCOPED_TRACE("no lifetime");

        SrvConfig conf(32);
        EXPECT_NO_THROW(conf.sanityChecksLifetime("valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("preferred-lifetime"));
    }

    {
        SCOPED_TRACE("lifetime only");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("preferred-lifetime"));
    }

    {
        SCOPED_TRACE("min-lifetime only");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("preferred-lifetime"));
    }

    {
        SCOPED_TRACE("max-lifetime only");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("preferred-lifetime"));
    }

    {
        SCOPED_TRACE("min-lifetime and max-lifetime but no lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1000));
        std::string msg = "have min-valid-lifetime and max-valid-lifetime ";
        msg += "but no valid-lifetime (default)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("valid-lifetime"),
                         isc::BadValue, msg);
        msg = "have min-preferred-lifetime and max-preferred-lifetime ";
        msg += "but no preferred-lifetime (default)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("all lifetime parameters");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(3000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime("preferred-lifetime"));
    }

    {
        SCOPED_TRACE("min-lifetime > max-lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        std::string msg = "the value of min-valid-lifetime (2000) is ";
        msg += "not less than max-valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of min-preferred-lifetime (1000) is ";
        msg += "not less than max-preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("min-lifetime > lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(500));
        std::string msg = "the value of min-valid-lifetime (2000) is ";
        msg += "not less than (default) valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of min-preferred-lifetime (1000) is ";
        msg += "not less than (default) preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime > max-lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        std::string msg = "the value of (default) valid-lifetime (2000) is ";
        msg += "not less than max-valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of (default) preferred-lifetime (1000) is ";
        msg += "not less than max-preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime not between min-lifetime and max-lifetime (too small)");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(500));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(250));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1000));
        std::string msg = "the value of (default) valid-lifetime (500) is ";
        msg += "not between min-valid-lifetime (1000) and ";
        msg += "max-valid-lifetime (2000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of (default) preferred-lifetime (250) is ";
        msg += "not between min-preferred-lifetime (500) and ";
        msg += "max-preferred-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime not between min-lifetime and max-lifetime (too large)");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(3000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1500));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1000));
        std::string msg = "the value of (default) valid-lifetime (3000) is ";
        msg += "not between min-valid-lifetime (1000) and ";
        msg += "max-valid-lifetime (2000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of (default) preferred-lifetime (1500) is ";
        msg += "not between min-preferred-lifetime (500) and ";
        msg += "max-preferred-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime("preferred-lifetime"),
                         isc::BadValue, msg);
    }

    // Second the overload checking an external config before merging.
    // We assume that the target config is correct as this was the case
    // when this overload is used, and this lowers the number of cases...

    SrvConfig target(10);
    target.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
    target.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
    target.addConfiguredGlobal("valid-lifetime", Element::create(2000));
    target.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
    target.addConfiguredGlobal("max-valid-lifetime", Element::create(3000));
    target.addConfiguredGlobal("max-preferred-lifetime", Element::create(1500));

    {
        SCOPED_TRACE("no lifetime");

        SrvConfig conf(32);
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target, "valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target,
                                                  "preferred-lifetime"));
    }

    {
        SCOPED_TRACE("lifetime only");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target, "valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target,
                                                  "preferred-lifetime"));
    }

    {
        SCOPED_TRACE("min-lifetime only");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target, "valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target,
                                                  "preferred-lifetime"));
    }

    {
        SCOPED_TRACE("max-lifetime only");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(3000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target, "valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target,
                                                  "preferred-lifetime"));
    }

    {
        SCOPED_TRACE("min-lifetime and max-lifetime but no lifetime");

        SrvConfig empty(10);
        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(3000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1500));
        std::string msg = "have min-valid-lifetime and ";
        msg += "max-valid-lifetime but no valid-lifetime (default)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(empty, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "have min-preferred-lifetime and ";
        msg += "max-preferred-lifetime but no preferred-lifetime (default)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(empty,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("all lifetime parameters");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(500));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(3000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(1500));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target, "valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target,
                                                  "preferred-lifetime"));
    }

    {
        SCOPED_TRACE("overwrite all lifetime parameters");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(100));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(50));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(200));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(100));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(300));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(150));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target, "valid-lifetime"));
        EXPECT_NO_THROW(conf.sanityChecksLifetime(target,
                                                  "preferred-lifetime"));
    }

    {
        SCOPED_TRACE("min-lifetime > max-lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        std::string msg = "the value of new min-valid-lifetime (2000) is ";
        msg += "not less than new max-valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new min-preferred-lifetime (1000) is ";
        msg += "not less than new max-preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("target min-lifetime > max-lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(500));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(250));
        std::string msg = "the value of previous min-valid-lifetime (1000) is ";
        msg += "not less than new max-valid-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of previous min-preferred-lifetime (500) is ";
        msg += "not less than new max-preferred-lifetime (250)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("min-lifetime > target max-lifetime");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(4000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(2000));
        std::string msg = "the value of new min-valid-lifetime (4000) is ";
        msg += "not less than previous max-valid-lifetime (3000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new min-preferred-lifetime (2000) is ";
        msg += "not less than previous max-preferred-lifetime (1500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("min-lifetime > lifetime");

        SrvConfig empty(10);
        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(500));
        std::string msg = "the value of new min-valid-lifetime (2000) is ";
        msg += "not less than new (default) valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(empty, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new min-preferred-lifetime (1000) is ";
        msg += "not less than new (default) preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(empty,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("target min-lifetime > lifetime");

        SrvConfig conf(32);
        SrvConfig target2(20);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(500));
        target2.addConfiguredGlobal("min-valid-lifetime", Element::create(2000));
        target2.addConfiguredGlobal("min-preferred-lifetime", Element::create(1000));
        std::string msg = "the value of previous min-valid-lifetime (2000) ";
        msg += "is not less than new (default) valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of previous min-preferred-lifetime (1000) ";
        msg += "is not less than new (default) preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("min-lifetime > target lifetime");

        SrvConfig conf(32);
        SrvConfig target2(20);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(1000));
        target2.addConfiguredGlobal("valid-lifetime", Element::create(1000));
        target2.addConfiguredGlobal("preferred-lifetime", Element::create(500));
        std::string msg = "the value of new min-valid-lifetime (2000) is ";
        msg += "not less than previous (default) valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new min-preferred-lifetime (1000) is ";
        msg += "not less than previous (default) preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime > max-lifetime");

        SrvConfig empty(10);
        SrvConfig conf(32);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        std::string msg = "the value of new (default) valid-lifetime (2000) ";
        msg += "is not less than new max-valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(empty, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new (default) preferred-lifetime (1000) ";
        msg += "is not less than new max-preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(empty,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("target lifetime > max-lifetime");

        SrvConfig conf(32);
        SrvConfig target2(20);
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        target2.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        target2.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        std::string msg = "the value of previous (default) valid-lifetime ";
        msg += "(2000) is not less than new max-valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of previous (default) preferred-lifetime ";
        msg += "(1000) is not less than new max-preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime > target max-lifetime");

        SrvConfig conf(32);
        SrvConfig target2(20);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(2000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(1000));
        target2.addConfiguredGlobal("max-valid-lifetime", Element::create(1000));
        target2.addConfiguredGlobal("max-preferred-lifetime", Element::create(500));
        std::string msg = "the value of new (default) valid-lifetime (2000) ";
        msg += "is not less than previous max-valid-lifetime (1000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new (default) preferred-lifetime (1000) ";
        msg += "is not less than previous max-preferred-lifetime (500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target2,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime not between min-lifetime and max-lifetime (too small)");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(500));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(250));
        std::string msg = "the value of new (default) valid-lifetime (500) ";
        msg += "is not between previous min-valid-lifetime (1000) and ";
        msg += "previous max-valid-lifetime (3000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new (default) preferred-lifetime (250) ";
        msg += "is not between previous min-preferred-lifetime (500) and ";
        msg += "previous max-preferred-lifetime (1500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime not between min-lifetime and max-lifetime (too large)");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("valid-lifetime", Element::create(4000));
        conf.addConfiguredGlobal("preferred-lifetime", Element::create(2000));
        std::string msg = "the value of new (default) valid-lifetime (4000) ";
        msg += "is not between previous min-valid-lifetime (1000) and ";
        msg += "previous max-valid-lifetime (3000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of new (default) preferred-lifetime (2000) ";
        msg += "is not between previous min-preferred-lifetime (500) and ";
        msg += "previous max-preferred-lifetime (1500)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime not between min-lifetime and max-lifetime (too low)");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(100));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(50));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(300));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(150));
        std::string msg = "the value of previous (default) valid-lifetime ";
        msg += "(2000) is not between new min-valid-lifetime (100) and ";
        msg += "new max-valid-lifetime (300)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of previous (default) preferred-lifetime ";
        msg += "(1000) is not between new min-preferred-lifetime (50) and ";
        msg += "new max-preferred-lifetime (150)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }

    {
        SCOPED_TRACE("lifetime not between min-lifetime and max-lifetime (too high)");

        SrvConfig conf(32);
        conf.addConfiguredGlobal("min-valid-lifetime", Element::create(10000));
        conf.addConfiguredGlobal("min-preferred-lifetime", Element::create(5000));
        conf.addConfiguredGlobal("max-valid-lifetime", Element::create(30000));
        conf.addConfiguredGlobal("max-preferred-lifetime", Element::create(15000));
        std::string msg = "the value of previous (default) valid-lifetime ";
        msg += "(2000) is not between new min-valid-lifetime (10000) and ";
        msg += "new max-valid-lifetime (30000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target, "valid-lifetime"),
                         isc::BadValue, msg);
        msg = "the value of previous (default) preferred-lifetime ";
        msg += "(1000) is not between new min-preferred-lifetime (5000) and ";
        msg += "new max-preferred-lifetime (15000)";
        EXPECT_THROW_MSG(conf.sanityChecksLifetime(target,
                                                   "preferred-lifetime"),
                         isc::BadValue, msg);
    }
}

} // end of anonymous namespace
